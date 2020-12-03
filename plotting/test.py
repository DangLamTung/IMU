import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QMainWindow, QGridLayout,QHBoxLayout, QListWidget,QMessageBox)
from PyQt5.Qt import Qt
from list_port import list_serial_ports
import serial
from time import sleep

ser = serial.Serial()

portName = "COM40" 
baudrate = 115200
def connectCOM():
    try:                     # replace this port name by yours!
        baudrate = 115200
        global ser,portName,detached, rl, connect_check
        ser = serial.Serial(portName,baudrate)
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
def list_clicked():
    global portName
    portName = list_widget.currentItem().text()
    connectCOM()
class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

    def keyPressEvent(self, event):

        if event.key() == Qt.Key_W:
            self.test_method(1)
        if event.key() == Qt.Key_A:
            self.test_method(2)
        if event.key() == Qt.Key_D:
            self.test_method(3)
        if event.key() == Qt.Key_S:
            self.test_method(4)
        if event.key() == Qt.Key_X:
            self.test_method(5)
    def test_method(self,command):
        global ser

        if(command == 1):
            ser.write(b'w') 
        if(command == 2):
            ser.write(b'a')
        if(command == 3):
            ser.write(b'd')
        if(command == 4):
            ser.write(b'x')
        if(command == 5):
            ser.write(b'z')
        sleep(0.05)
if __name__ == '__main__':
    app = QApplication(sys.argv)
    demo = MainWindow()
    list_widget = QListWidget()
    serial_list = list_serial_ports()
    ser = serial.Serial(serial_list[0],baudrate)
    list_widget.clicked.connect(list_clicked)
    ml = QGridLayout()

    # ml.addWidget(list_widget,0,1)
    # demo.setLayout(ml)
    demo.show()
    sys.exit(app.exec_())