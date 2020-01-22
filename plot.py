
# Import libraries
from numpy import *
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import serial
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


# Create object serial port
portName = "/dev/ttyUSB0"                      # replace this port name by yours!
baudrate = 115200
ser = serial.Serial(portName,baudrate)
rl = ReadLine(ser)
### START QtApp #####
app = QtGui.QApplication([])            # you MUST do this once (initialize things)
####################

win = pg.GraphicsWindow(title="Signal from serial port") # creates a window
p = win.addPlot(title="Realtime plot")  # creates empty space for the plot in the window
curve = p.plot()                        # create an empty "plot" (a curve to plot)

p1 = win.addPlot(title="Realtime plot")  # creates empty space for the plot in the window
curve1 = p1.plot()                        # create an empty "plot" (a curve to plot)

p2 = win.addPlot(title="Realtime plot")  # creates empty space for the plot in the window
curve2 = p2.plot()                        # create an empty "plot" (a curve to plot)

p3 = win.addPlot(title="Realtime plot")  # creates empty space for the plot in the window
curve3 = p3.plot()                        # create an empty "plot" (a curve to plot)


windowWidth = 500                       # width of the window displaying the curve
Xm = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr = -windowWidth                      # set first x position

Xm1 = linspace(0,0,windowWidth)          # create array that will contain the relevant time series     
ptr1 = -windowWidth   
from threading import Thread 
import time

# Define a function for the thread
def print_time( threadName, delay):
   count = 0
   while count < 5:
      time.sleep(delay)
      count += 1
      print("%s: %s" % ( threadName, time.ctime(time.time()) ))

t = Thread(target=print_time, args=("tung",1))
t.start()
# Realtime data plot. Each time this function is called, the data display is updated
def update():
    global curve, ptr,curve1, ptr1, Xm    
    Xm[:-1] = Xm[1:]                      # shift data in the temporal mean 1 sample left
    # if(len(Xm) < windowWidth):

    value = rl.readline()             # read line (single value) from the serial port
    try:
        X =  (value.decode().replace('\x00','').replace('\x00','')).split(' ')
        x_ = []
        for i in X:
            x_.append(float(i))  
        print(x_)
        Xm[-1] = x_[1]                 # vector containing the instantaneous values      
        ptr += 1                              # update x position for displaying the curve

        Xm1[-1] = x_[1]                 # vector containing the instantaneous values      
        ptr1 += 1     


    except Exception as e:
        print(e)
        Xm[-1] = 0
    curve.setData(Xm)                     # set the curve with this data
    curve.setPos(ptr,0)                   # set x position in the graph to 0

    QtGui.QApplication.processEvents()    # you MUST process the plot now 

### MAIN PROGRAM #####    
# this is a brutal infinite loop calling your realtime data plot
while True: update()

### END QtApp ####
pg.QtGui.QApplication.exec_() 
