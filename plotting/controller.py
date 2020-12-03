from PyQt5.QtCore import (QCoreApplication, QObject, QRunnable, QThread,
                          QThreadPool, pyqtSignal, QPointF,QRectF,QLineF)
from PyQt5.QtWidgets import QApplication, QWidget, QMainWindow, QGridLayout,QHBoxLayout, QListWidget,QMessageBox
from PyQt5.QtGui import QPainter, QColor, QFont
import sys
from enum import Enum
from list_port import list_serial_ports
import serial
from time import sleep

class ReadLine:
    def __init__(self, s):
        self.buf = bytearray()
        self.s = s
    
    def readline(self):
        i = self.buf.find(b"\n")
        if i >= 0:
            r = self.buf[:i+1]
            self.buf = self.buf[i+1:]
            return r
        while True:
            i = max(1, min(2048, self.s.in_waiting))
            data = self.s.read(i)
            i = data.find(b"\n")
            if i >= 0:
                r = self.buf + data[:i+1]
                self.buf[0:] = data[i+1:]
                return r
            else:
                self.buf.extend(data)
                

ser = serial.Serial()
rl = ReadLine(ser)
portName = "COM40" 


def connectCOM():
    try:                     # replace this port name by yours!
        baudrate = 115200
        global ser,portName,detached, rl, connect_check
        ser = serial.Serial(portName,baudrate)
        rl = ReadLine(ser)
        alert = QMessageBox()
        connect_check = True
        alert.setText('Connect OK!')
        alert.exec_()
        # ser.open()

    except Exception as e: 
        print(e)
        alert = QMessageBox()
        alert.setText('Error connect COM!')
        alert.exec_()

def setPID(angle, velocity):
    global ser
    try: 
        values = []
        sleep(0.1)
        data = []
        data1 = []
        start = 's'
        end = 'e'
        CRC = ""
        value  = int(format(angle,'04'))
        value1 = int(format(velocity,'04'))
        value2 = int(format(0,'04'))
        value3 = int(format(0,'04'))

        esc1 = bin(value)
        esc2 = bin(value1)
        esc3 = bin(value2)
        esc4 = bin(value3)
    
        esc = '0b00000000000'
        esc = esc[2:(len(esc)-len(esc1)+2)]  + esc1[2:len(esc1)]
        # print(len(esc))   
        b1 = esc
        #value 2
        esc = '0b00000000000'
        esc = esc[2:(len(esc)-len(esc2)+2)]  + esc2[2:len(esc2)]
        b2 = esc
        #value 3
        esc = '0b00000000000'
        esc = esc[2:(len(esc)-len(esc3)+2)]  + esc3[2:len(esc3)]
        b3 = esc
        
        esc = '0b00000000000'
        esc = esc[2:(len(esc)-len(esc4)+2)]  + esc4[2:len(esc4)]
        b4 = esc 

        frame_check = (value + value1 + value2 + value3) %37
        data_frame = b1 + b2 + b3 + b4

        
        frame1 = '0b' + data_frame[0:8]
        frame2 = '0b' + data_frame[8:16]
        frame3 = '0b' + data_frame[16:24]
        frame4 = '0b' + data_frame[24:32]
        frame5 = '0b' + data_frame[32:40]
        frame6 = '0b' + data_frame[40:44] + '0000'
        


        data.append(int(frame1,2))
        data.append(int(frame2,2))
        data.append(int(frame3,2))
        data.append(int(frame4,2))
        data.append(int(frame5,2))
        data.append(int(frame6,2))
        data.append(frame_check)
        # print(data)
        ser.write(b's')
        for i in data:
            ser.write(bytes([i]))
            print(i)
        ser.write(b'e') 
    except Exception as e: 
        print(e)
        alert = QMessageBox()
        alert.setText('Error connect COM!')
        alert.exec_()
def list_clicked():
    global portName
    portName = list_widget.currentItem().text()
    connectCOM()
class Direction(Enum):
    Left = 0
    Right = 1
    Up = 2
    Down = 3

class Joystick(QWidget):
    def __init__(self, parent=None):
        super(Joystick, self).__init__(parent)
        self.setMinimumSize(100, 100)
        self.movingOffset = QPointF(0, 0)
        self.grabCenter = False
        self.__maxDistance = 50

    def paintEvent(self, event):
        painter = QPainter(self)
        bounds = QRectF(-self.__maxDistance, -self.__maxDistance, self.__maxDistance * 2, self.__maxDistance * 2).translated(self._center())
        painter.drawEllipse(bounds)
        painter.setBrush(QColor(0, 0, 255, 127))
        painter.drawEllipse(self._centerEllipse())

    def _centerEllipse(self):
        if self.grabCenter:
            return QRectF(-20, -20, 40, 40).translated(self.movingOffset)
        return QRectF(-20, -20, 40, 40).translated(self._center())

    def _center(self):
        return QPointF(self.width()/2, self.height()/2)


    def _boundJoystick(self, point):
        limitLine = QLineF(self._center(), point)
        if (limitLine.length() > self.__maxDistance):
            limitLine.setLength(self.__maxDistance)
        return limitLine.p2()

    def joystickDirection(self):
        if not self.grabCenter:
            return 0
        normVector = QLineF(self._center(), self.movingOffset)
        currentDistance = normVector.length()
        angle = int(normVector.angle())

        distance = int(currentDistance / self.__maxDistance * 0)
        setPID(angle, distance)
        return (Direction.Right, distance)


    def mousePressEvent(self, ev):
        self.grabCenter = self._centerEllipse().contains(ev.pos())
        return super().mousePressEvent(ev)

    def mouseReleaseEvent(self, event):
        self.grabCenter = False
        self.movingOffset = QPointF(0, 0)
        self.update()

    def mouseMoveEvent(self, event):
        if self.grabCenter:
            print("Moving")
            self.movingOffset = self._boundJoystick(event.pos())
            self.update()
        print(self.joystickDirection())

if __name__ == '__main__':
    # Create main application window
    app = QApplication([])
    mw = QMainWindow()
    mw.setWindowTitle('Joystick example')

    # Create and set widget layout
    # Main widget container
    cw = QWidget()
    ml = QGridLayout()
    list_widget = QListWidget()
    serial_list = list_serial_ports()
    for (i,ser_name) in enumerate(serial_list):
        list_widget.insertItem(i, ser_name)
    list_widget.clicked.connect(list_clicked)
    # ml.addWidget(list_widget)
    cw.setLayout(ml)
    mw.setCentralWidget(cw)

    # Create joystick 
    joystick = Joystick()

    # ml.addLayout(joystick.get_joystick_layout(),0,0)
    ml.addWidget(list_widget,0,1)
    ml.addWidget(joystick,0,0)
      
    mw.show()

    ## Start Qt event loop unless running in interactive mode or using pyside.
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QApplication.instance().exec_()