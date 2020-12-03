import serial
import io
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D 
import sys
import numpy as np
temp = []
temp1 = []
data = []
time = []
dt = 0.000512
currentSample = 0

file_data = open("magnet_calib_car.txt","w")
mag_data = []
with serial.Serial('COM8', 115200, timeout=1) as ser:
    while(len(data)<1000):
        try:
            value = ser.readline()
            print(value)
            temp = (value.decode().replace('\n','').replace('\x00','')).split(' ')
            temp1 = []
            
            for (i,value1) in enumerate(temp):
                temp1.append(float(value1))
            # data = np.array(data)
            data.append(temp1)
            print(len(data))
            string = ""
            for i in temp1:
                string += str(i) + " "
            file_data.write(string + "\n")
            #currentSample += dt
            #time.append(currentSample)
        except Exception as e:
            print(e)
data = np.array(data)
print(data.shape)
print(data)
