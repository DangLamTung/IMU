import matplotlib.pyplot as plt
import numpy as np

file_data = open("EKF_magnet.txt","r")


time = []
data = []

Acc_x = []
Acc_y = []
Acc_z = []

Gyro_x = []
Gyro_y = []
Gyro_z = []

Mag_x = []
Mag_y = []
Mag_z = []

currentSample = 0
dt = 0.003
for l in file_data.readlines():
    temp = l.split(' ')
    
    Acc_x.append(int(temp[0]))
    Acc_y.append(int(temp[2]))
    Acc_z.append(int(temp[3]))

    Gyro_x.append(int(temp[4]))
    Gyro_y.append(int(temp[5]))
    Gyro_z.append(int(temp[6]))

    Mag_x.append(float(temp[7]))
    Mag_y.append(float(temp[8]))
    Mag_z.append(float(temp[9]))
            # data = np.array(data)
    print(len(data))
print(Gyro_x.mean())
print(Gyro_x.mean())
print(Gyro_x.mean())

angle = np.array(angle)
print(angle.mean())
print(angle.std())
print(gyroY[np.where(gyroY<0)])

plt.scatter(time,pitch,label='giá trị accel_angle khi đã trừ offset',linewidth=1)

plt.scatter(time,gyro_angle,label='giá trị gyro_angle khi đã trừ offset',linewidth=1)
time.append(time[len(time)-1]+dt)
plt.plot(time,angle,'r-',label='giá trị dự đoán')
plt.legend()
plt.show()

