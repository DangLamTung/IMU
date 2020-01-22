from numpy import *
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import serial
from time import sleep
import numpy as np
import crc8
import time
from PyQt5.QtWidgets import QApplication,QTabWidget, QWidget, QPushButton, QHBoxLayout,QVBoxLayout,QSlider,QLabel,QMessageBox,QListWidget,QTextEdit
# Create object serial port

### START QtApp #####
app = QtGui.QApplication([])            # you MUST do this once (initialize things)
####################
win = QWidget()
current_time = 0

plot_uart = pg.GraphicsLayoutWidget() # creates a window
p = plot_uart.addPlot(title="Roll")  # creates empty space for the plot in the window

plot_uart1 = pg.GraphicsLayoutWidget() # creates a window
p1 = plot_uart1.addPlot(title="Pitch")  # creates empty space for the plot in the window

plot_uart2 = pg.GraphicsLayoutWidget() # creates a window
p2 = plot_uart2.addPlot(title="Yaw")  # creates empty space for the plot in the window

plot_uart3 = pg.GraphicsLayoutWidget() # creates a window
p3 = plot_uart3.addPlot(title="Roll acc")  # creates empty space for the plot in the window

plot_uart4 = pg.GraphicsLayoutWidget() # creates a window
p4 = plot_uart4.addPlot(title="Pitch acc")  # creates empty space for the plot in the window

plot_uart5 = pg.GraphicsLayoutWidget() # creates a window
p5 = plot_uart5.addPlot(title="Yaw mag")  # creates empty space for the plot in the window


ser = serial.Serial()
portName = "COM40" 
detached = False
plot_control = False
def listToString(s):  
    
    # initialize an empty string 
    str1 = ""  
    
    # traverse in the string   
    for ele in s:  
        str1 += ele   
    
    # return string   
    return str1  

main_layout = QVBoxLayout()
main_layout_1 = QVBoxLayout()
def setPID_all():
    global ser
    try: 
        values = []
        sleep(0.05)
        data = []
        data1 = []
        start = 's'
        end = 'e'
        CRC = ""
        value = int(format(slider4.value(),'04'))

        esc1 = bin(value)
        esc2 = bin(value)
        esc3 = bin(value)
        esc4 = bin(value)
        
        esc = '0b00000000000'
        esc = esc[2:(len(esc)-len(esc1)+2)]  + esc1[2:len(esc1)]
        print(len(esc))   
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
        data_frame = b1+ b2 + b3 +b4

        
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
      


        # CRC = listToString(data1)
        # print(CRC)
        # hash.update(CRC)
        # print(hash.hexdigest())
        # data.append(int((esc[11:13] + ),2))

    
        # a = []

        

        # data.append(start)
        # values.append(bytearray("0000", 'ascii'))
        # values.append(bytearray(str(format(slider.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider1.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider2.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider3.value(),'04')), 'ascii'))

        # values.append(bytearray(str(format(slider4.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider5.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider6.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider7.value(),'04')), 'ascii'))
        ser.write(b's')
        for i in data:
            ser.write(bytes([i]))
            print(i)
        ser.write(b'e')   
       
    except Exception as e: 
        print(e)
        alert = QMessageBox()
        alert.setText('Error connect COM!')
        textEdit.setPlainText(str(e) + "\n")
        alert.exec_()
def setPID():
    global ser
    try: 
        values = []
        sleep(0.05)
        data = []
        data1 = []
        start = 's'
        end = 'e'
        CRC = ""
        value = int(format(slider.value(),'04'))
        value1 = int(format(slider1.value(),'04'))
        value2 = int(format(slider2.value(),'04'))
        value3 = int(format(slider3.value(),'04'))

        esc1 = bin(value)
        esc2 = bin(value1)
        esc3 = bin(value2)
        esc4 = bin(value3)
        
        esc = '0b00000000000'
        esc = esc[2:(len(esc)-len(esc1)+2)]  + esc1[2:len(esc1)]
        print(len(esc))   
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
        data_frame = b1+ b2 + b3 +b4

        
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
      


        # CRC = listToString(data1)
        # print(CRC)
        # hash.update(CRC)
        # print(hash.hexdigest())
        # data.append(int((esc[11:13] + ),2))

    
        # a = []

        

        # data.append(start)
        # values.append(bytearray("0000", 'ascii'))
        # values.append(bytearray(str(format(slider.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider1.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider2.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider3.value(),'04')), 'ascii'))

        # values.append(bytearray(str(format(slider4.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider5.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider6.value(),'04')), 'ascii'))
        # values.append(bytearray(str(format(slider7.value(),'04')), 'ascii'))
        ser.write(b's')
        for i in data:
            ser.write(bytes([i]))
            print(i)
        ser.write(b'e')   
       
    except Exception as e: 
        print(e)
        alert = QMessageBox()
        alert.setText('Error connect COM!')
        textEdit.setPlainText(str(e) + "\n")
        alert.exec_()
def startRun():
    global ser, plot_control
    plot_control = True

    

def stopRun():
    global ser, plot_control
    plot_control = False
    ser.write(b'd')

def connectCOM():
    try:                     # replace this port name by yours!
        baudrate = 115200
        global ser,portName,detached
        ser = serial.Serial(portName,baudrate)
        if detached:
            detached = False
        alert = QMessageBox()
        alert.setText('Connect OK!')
        # ser.open()

    except Exception as e: 
        print(e)
        alert = QMessageBox()
        alert.setText('Error connect COM!')
        textEdit.setPlainText(str(e) + "\n")
        alert.exec_()
def detachCOM():
    global ser,detached 
    detached = True
    ser.close()
def list_clicked():
    global portName
    portName = list_widget.currentItem().text()
def update_slider():
    setPID()
    label.setText("Motor 1 \n" + str(slider.value()))
    label1.setText("Motor 2 \n" + str(slider1.value()))
    label2.setText("Motor 3 \n" + str(slider2.value()))
    label3.setText("Motor 4 \n" + str(slider3.value()))
    label4.setText("Ki 2 \n" + str(slider4.value()))
    label5.setText("Kd 2 \n" + str(slider5.value()))
    label6.setText("Motor 1 \n" + str(slider6.value()))
    label7.setText("Motor 2 \n" + str(slider7.value()))  
slider = QSlider()
slider.setValue(1000)
slider.setMinimum(1000)
slider.setMaximum(2000)
slider.valueChanged.connect(update_slider)

slider1 = QSlider()
slider1.setValue(1000)
slider1.setMinimum(1000)
slider1.setMaximum(2000)
slider1.valueChanged.connect(update_slider)

slider2 = QSlider()
slider2.setValue(1000)
slider2.setMinimum(1000)
slider2.setMaximum(2000)
slider2.valueChanged.connect(update_slider)

slider3 = QSlider()
slider3.setValue(1000)
slider3.setMinimum(1000)
slider3.setMaximum(2000)
slider3.valueChanged.connect(update_slider)

slider4 = QSlider()
slider4.setValue(1000)
slider4.setMinimum(1000)
slider4.setMaximum(2000)
slider4.valueChanged.connect(setPID_all)

slider5 = QSlider()
slider5.setValue(0)
slider5.setMaximum(2000)
slider5.valueChanged.connect(update_slider)

slider6 = QSlider()
slider6.setValue(0)
slider6.setMaximum(2000)
slider6.valueChanged.connect(update_slider)

slider7 = QSlider()
slider7.setValue(0)
slider7.setMaximum(999)
slider7.valueChanged.connect(update_slider)
 # Will print '5'

layout = QHBoxLayout()
layout_inner = QHBoxLayout()
layout_inner1 = QHBoxLayout()
layout_inner2 = QVBoxLayout()

layout_value = QHBoxLayout()

label = QLabel("Motor 1")
label1 = QLabel("Motor 2")
label2 = QLabel("Motor 3")

label3 = QLabel("Motor 4")
label4 = QLabel("All motor")
label5 = QLabel("Kd 2")

label6 = QLabel("Motor 1")
label7 = QLabel("Motor 2")

label_duty1 = QLabel("Roll")
label_duty2 = QLabel("Pitch")
label_duty3 = QLabel("Yaw")
label_duty4 = QLabel("Time: ")

connect_button = QPushButton('Connect COM')
connect_button.clicked.connect(connectCOM)

detatch_button = QPushButton('Disconnect COM')
detatch_button.clicked.connect(detachCOM)

layout_inner2.addWidget(connect_button)
layout_inner2.addWidget(detatch_button)

list_widget = QListWidget()

list_widget.insertItem(0, "/dev/ttyUSB0" )
list_widget.insertItem(1, "/dev/ttyUSB1" )
list_widget.insertItem(2, "/dev/ttyUSB2" )
list_widget.insertItem(3, "/dev/ttyUSB3" )
list_widget.insertItem(4, "/dev/ttyUSB4" )
list_widget.insertItem(5, "/dev/ttyUSB5" )
list_widget.insertItem(6, "/dev/ttyUSB28" )
list_widget.insertItem(7, "/dev/ttyUSB27" )

list_widget.clicked.connect(list_clicked)
layout_inner.addWidget(list_widget)
layout_inner.addLayout(layout_inner2)

layout.addWidget(slider)
layout.addWidget(label)

layout.addWidget(slider1)
layout.addWidget(label1)

layout.addWidget(slider2)
layout.addWidget(label2)

layout.addWidget(slider3)
layout.addWidget(label3)

layout.addWidget(slider4)
layout.addWidget(label4)

layout.addWidget(slider5)
layout.addWidget(label5)

layout.addWidget(slider6)
layout.addWidget(label6)

layout.addWidget(slider7)
layout.addWidget(label7)

layout.addStretch(2)

layout.addLayout(layout_inner)


main_layout.addLayout(layout)

button = QPushButton('Set PID')
button.clicked.connect(setPID)

button1 = QPushButton('Start')
button1.clicked.connect(startRun)

button2 = QPushButton('Stop')
button2.clicked.connect(stopRun)

layout_inner1.addWidget(button)
layout_inner1.addWidget(button1)
layout_inner1.addWidget(button2)

textEdit = QTextEdit()

layout_value.addWidget(label_duty1)
layout_value.addWidget(label_duty2)
layout_value.addWidget(label_duty3)
layout_value.addWidget(label_duty4)

main_layout.addLayout(layout_inner1)
main_layout.addLayout(layout_value)

plot_batch = QVBoxLayout()
layout_plot = QHBoxLayout()
layout_plot.addWidget(plot_uart)
layout_plot.addWidget(plot_uart1)
layout_plot.addWidget(plot_uart2)

layout_plot1 = QHBoxLayout()
layout_plot1.addWidget(plot_uart3)
layout_plot1.addWidget(plot_uart4)
layout_plot1.addWidget(plot_uart5)

plot_batch.addLayout(layout_plot)
plot_batch.addLayout(layout_plot1)

main_layout.addLayout(plot_batch)

main_layout.addWidget(textEdit)

tabs = QTabWidget()
tab1 = QWidget()
tab2 = QWidget()

tab1.setLayout(main_layout)
tabs.addTab(tab1,"Tune")
main_layout_1.addWidget(tabs)
win.setLayout(main_layout_1)
win.show()

curve = p.plot()                        # create an empty "plot" (a curve to plot)
curve1 = p1.plot() 
curve2 = p2.plot() 
curve3 = p3.plot()                        # create an empty "plot" (a curve to plot)
curve4 = p4.plot() 
curve5 = p5.plot() 

windowWidth = 500                       # width of the window displaying the curve
Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr = -windowWidth                      # set first x position

Xm3 = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr3 = -windowWidth                      # set first x position

Xm1 = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr1 = -windowWidth      

Xm2 = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr2 = -windowWidth                          # set first x position

Xm4 = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr4 = -windowWidth                      # set first x position

Xm5 = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr5 = -windowWidth      

# Realtime data plot. Each time this function is called, the data display is updated
def update():
    global curve,curve1,curve2, ptr, ptr1, ptr2,ptr3, ptr4, ptr5, Xm, Xm1,Xm2, detached, plot_control ,current_time
    Xm[:-1] = Xm[1:]                      # shift data in the temporal mean 1 sample left
    Xm1[:-1] = Xm1[1:]
    Xm2[:-1] = Xm2[1:]
    Xm3[:-1] = Xm3[1:]                      # shift data in the temporal mean 1 sample left
    Xm4[:-1] = Xm4[1:]
    Xm5[:-1] = Xm5[1:]
    if(plot_control):
        value = ser.readline()                # read line (single value) from the s
    try:
        X =  (value.decode().replace('\x00','').replace('\x00','')).split(' ')
        x_ = []
        for i in X:
            x_.append(float(i))
        # print(x_)
        label_duty1.setText("Roll: " + str(x_[0]))
        label_duty2.setText("Pitch: " + str(x_[1]))
        label_duty3.setText("Yaw: " + str(x_[2]))
        Xm[-1] = x_[0]                 # vector containing the instantaneous values 
        Xm1[-1] = x_[1]
        Xm2[-1] = x_[2]
        Xm3[-1] = x_[3]                 # vector containing the instantaneous values 
        Xm4[-1] = x_[4]
        Xm5[-1] = x_[5] 
        if(len(x_)>3): 
            millis = int(round(time.time() * 1000)) - current_time
            current_time = int(round(time.time() * 1000))
            label_duty4.setText("Time: " + str(millis))    
    except Exception as e: 
        print(e)   
        textEdit.setPlainText(str(e) + "\n")
        Xm[-1] = Xm[0]
        Xm1[-1] = Xm1[0]
        Xm2[-1] = Xm2[0]
    #ser.close()


    ptr5 += 1                              # update x position for displaying the curve
    curve5.setData(Xm5)                     # set the curve with this data
    curve5.setPos(ptr5,0)    
    ptr4 += 1                              # update x position for displaying the curve
    curve4.setData(Xm4)                     # set the curve with this data
    curve4.setPos(ptr4,0)                   # set x position in the graph to 0
    ptr3 += 1                              # update x position for displaying the curve
    curve3.setData(Xm3)                     # set the curve with this data
    curve3.setPos(ptr3,0)                   # set x position in the graph to 0

    ptr2 += 1                              # update x position for displaying the curve
    curve2.setData(Xm2)                     # set the curve with this data
    curve2.setPos(ptr2,0)    
    ptr1 += 1                              # update x position for displaying the curve
    curve1.setData(Xm1)                     # set the curve with this data
    curve1.setPos(ptr1,0)                   # set x position in the graph to 0
    ptr += 1                              # update x position for displaying the curve
    curve.setData(Xm)                     # set the curve with this data
    curve.setPos(ptr,0)                   # set x position in the graph to 0
    QtGui.QApplication.processEvents()    # you MUST process the plot now


### MAIN PROGRAM #####    
# this is a brutal infinite loop calling your realtime data plot
while True: update()

### END QtApp ####
pg.QtGui.QApplication.exec_() 
