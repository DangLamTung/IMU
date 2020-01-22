log_file_full = load('./data/EKF_stm32_test_n.txt');
starting_row =1;
end_row = 10000;
log_file_test  = log_file_full(starting_row:end_row,:);

N = max(size(log_file_test)); % Size of tested sample
T = 0.0002 % Sampling time
time = 0:T:(N)*T; % Time array

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Change unit of sensor values
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
gyro = log_file_test(:,1:3);        % unit: rad/s
acc  = log_file_test(:,4:6);       % unit: m/s^2
mag  = log_file_test(:,7:9);          % unit: gauss

bg = [-8.386 -27.1210 1.7630];
ba =  [ -372.6720  478  310.2080];
% acc(:,3) = acc(:,3) - 16384.0;
sigma_g = [0.0033    0.0352    0.0405]

acc = (acc -  ba)/16384.0 ;
gyro = (gyro - bg)/(16.4*180)*pi;
dt = 0.0002
size(gyro)
mean_g = mean(gyro);
mean_g = mean(acc);



 
% R_full = [  sigma_a(1)  0  0 0 0 0 ;
%             0  sigma_a(2)  0 0 0 0 ;
%             0  0  sigma_a(3) 0 0 0 ;
%             0  0  0  5 0  0;
%             0  0  0  0  5  0;
%             0  0  0  0  0  5]
accx_estimated = zeros(N,1);
pitch_estimated = zeros(N,1);
yaw_estimated = zeros(N,1);

Pt = zeros(N,1);
k = 1

   A =[[  0.0046    0.0002    0.0000]
    [0.0002    0.0048   -0.0001]
    [0.0000   -0.0001    0.0048]];
% % % 
   b =[
  -39.3199
  119.0663
    7.1017];
   mag = A*(transpose(mag) - b);
%   size(mag)
   mag = transpose(mag);
SOS =[ 
       1.0000    1.7994    1.0000    1.0000   -1.9502    0.9514]
y1 = sosfilt(SOS,acc(:,1))*G(1);
y2 = sosfilt(SOS,acc(:,2))*G(1);
y3 = sosfilt(SOS,acc(:,3))*G(1);
k = 2
w = 0
w1 = 0
w2 = 0
while( k < N) 
     w = acc(k) - (-1.9502)*w1 - 0.9514*w2;
     y = w*1 + w1*1.7994 + 1*w2;
     w2 = w1;
     w1 = w;
     accx_estimated(k) = y*0.0003;
     k = k+1;
end

y = fft(acc(:,1));     
f = (0:length(y)-1)*500/length(y);
figure
plot(f,abs(y))
title('Magnitude')

y = fft(y1);     
f = (0:length(y)-1)*500/length(y);
figure
plot(f,abs(y))
title('Magnitude')

y = fft(gyro(:,1));     
f = (0:length(y)-1)*500/length(y);
figure
plot(f,abs(y))
title('Magnitude')

mean(accx_estimated - y1)