import serial
import io
import sys
import numpy as np
import struct
from threading import Thread
import threading

temp = []
temp1 = []
data = []
time = []
dt = 0.003
currentSample = 0

mag_data = []
value = []

def advance_uart():
    global value
    try:
        while True:
            value = ser.readline()
            print(value)
            b3 = value[12:16]
            b4 = value[16:20]
            b5 = value[20:24]
                
            temp = (b5[3] + b4[3] + b3[3]) % 37
            crc = value[24]
            
            # struct.unpack('f', b)
            if(crc == temp):
                # print("OK")
                for i in range(6):
                    b = value[4*i:4*(i+1)]
                    data.append(round(float(struct.unpack('f',b)[0]),3))
                print(data)
            time.sleep(100)
    except Exception as e:
        print("")
with serial.Serial('/dev/ttyUSB0', 115200, timeout=1) as ser:
    t1 = threading.Thread(target=advance_uart)
    t1.start()

#     i = 0
#     crc_error = 0
#     frame_error = 0
#     true_frame = 0

#     while i < 10000:
#         try:

#             data = []
            
#             i+=1
#             print(value)
#             if(len(value) == 26):
#                 true_frame = true_frame + 1
#                 # print(true_frame)
#             else:
#                 frame_error += 1
            
#                 # b.append()
#             # b1 = value[4:8]
#             # b2 = value[8:12]
            
            
#             else:
#                 print("not OK")
#                 crc_error += 1
#             # print(str(crc) + " vs " + str(temp))
#             # print(len(value))
#             # temp = (value.decode().replace('\n','').replace('\x00','')).split(' ')
            
#             #currentSample += dt
#             #time.append(currentSample)
            
#         except Exception as e:
#             print("")
#     print("frame error rate",frame_error/10000)
#     print("CRC error rate",crc_error/true_frame)
# data = np.array(data)

