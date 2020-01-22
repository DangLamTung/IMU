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
dt = 0.003
currentSample = 0

file_data = open("./data/EKF_stm32_test_9.txt","w")
mag_data = []
with serial.Serial('/dev/' + str(sys.argv[1]), 115200, timeout=1) as ser:
    while(len(data)<1000):
        try:
            value = ser.readline()
            
            temp = (value.decode().replace('\n','').replace('\x00','')).split(' ')
            # print(temp)
            temp1 = []
            if(len(temp)==9):
                for (i,value1) in enumerate(temp):
                    temp1.append(float(value1))
            # data = np.array(data)
                data.append(temp1)
                print(len(data))
                string = ""
                for i in temp1:
                    string += str(i) + " "
                file_data.write(string + "\n")
            else:
                print("data error")
            #currentSample += dt
            #time.append(currentSample)
        except Exception as e:
            print(e)
data = np.array(data)
# print(data.shape)
# print(data)
# for i in data:
#     # file_data.write(i + "\n")   
#     print(i)         
# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')
# ax.scatter(M_x, M_y, M_z)

# ax.set_xlabel('X Label')
# ax.set_ylabel('Y Label')
# ax.set_zlabel('Z Label')

# plt.show()
