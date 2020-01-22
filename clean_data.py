import matplotlib.pyplot as plt
import numpy as np

file_data = open("./data/EKF_test_data2.txt","r")
file_data_w = open("./data/EKF_test_data2_.txt","w")

data = []
currentSample = 0
dt = 0.003
for l in file_data.readlines():
    temp = l.split(' ')
    if(len(temp)==14):
        file_data_w.write(l)
  