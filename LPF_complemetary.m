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
roll_estimated = zeros(N,1);
pitch_estimated = zeros(N,1);
yaw_estimated = zeros(N,1);
yaw_mag = zeros(N,1);

pitch_gyro = zeros(N+1,1);
roll_gyro = zeros(N+1,1);
yaw_gyro = zeros(N+1,1);

pitch_acc = zeros(N,1);
roll_acc = zeros(N,1);

yaw_quat = zeros(N+1,1);

com_angle_r = zeros(N+1,1);
com_angle_p = zeros(N+1,1);
com_angle_y = zeros(N+1,1);
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
        1.0000   -1.6768    1.0000    1.0000   -1.9616    0.9630
    1.0000    1.0000         0    1.0000   -0.9628         0]
y1 = sosfilt(SOS,acc(:,1))/100;
y2 = sosfilt(SOS,acc(:,2))/100;
y3 = sosfilt(SOS,acc(:,3))/100;
k = 1
alpha = 0.99
r=0;
p=0;
y=0;
while( k < N) 
    [r,p,y] = LPF(acc(k,1),acc(k,2),acc(k,3),gyro(k,1),gyro(k,2),gyro(k,3),mag(k,1),mag(k,2),mag(k,3),r,p,y,0.0004);

	 com_angle_r(k+1) = r;
	 com_angle_p(k+1) = p;
	 com_angle_y(k+1) = y;
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

y = fft(com_angle_r);     
f = (0:length(y)-1)*500/length(y);
figure
plot(f,abs(y))
title('Magnitude')

figure;
subplot(3,1,1);
hold on;grid on;

 plot(time,com_angle_r,'g');
legend( 'estimated');
title('Roll');

subplot(3,1,2);
hold on;grid on;

plot(time,com_angle_p,'g');
legend('estimated');
title('Pitch');

subplot(3,1,3);
hold on;grid on;

plot(time,com_angle_y,'g');

legend('estimated');
title('Yaw');