log_file_full = load('./data/EKF_stm32_test_p_45.txt');
starting_row =1;
end_row = 1000;
log_file_test  = log_file_full(starting_row:end_row,:);

N = max(size(log_file_test)); % Size of tested sample
T = 0.004815 % Sampling time
time = 0:T:(N-1)*T; % Time array
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Change unit of sensor values
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
gyro = log_file_test(:,1:3);        % unit: rad/s
acc  = log_file_test(:,4:6);       % unit: m/s^2
mag  = log_file_test(:,7:9);          % unit: gauss

bg = [-0.6376 -1.9228 -0.0325];
ba =  [ -372.6720  478  310.2080];
% acc(:,3) = acc(:,3) - 16384.0;
sigma_g = [0.0033    0.0352    0.0405]

% acc = (acc -  ba)/16384.0 ;
gyro = (gyro)/(180)*pi;
t = 0.002
mean_g = mean(gyro)
mean_g = mean(acc)


x =               [1                       % gyrox
                  0                       % gyroy
                  0                       % gyroz
                  0                     % qa
                  bg(1)                   % qb              
                  bg(2)% qc
                  bg(3)]
% P = eye(7)*100
% Q = eye(7);
% 
% R_full = eye(6)*0.0000001;
P = eye(7)*100 
Q = [[0 0 0 0 0 0 0]
     [0 0 0 0 0.01 0 0]
     [0 0 0 0 0 0.01 0]
     [0 0 0 0 0 0 0.01]
    [0,0, 0 ,0 ,6.4290e-06 ,0, 0],
        [ 0,0,0,0,0,9.0503e-06,0],
       [0,0,0,0,0,0, 8.3943e-06]];
R_full = [[ 8.3943e-06,0,0,0,0,0],
          [ 0, 9.0680e-6,0,0,0,0],
          [0,0,8.4107e-6,0,0,0],
          [ 0,0,0,1e-3,0,0],
          [ 0,0,0,0,1e-3,0],
          [0,0,0,0,0,1e-3]
       ];
 
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

Gx_estimated = zeros(N,1);
Gy_estimated = zeros(N,1);
Gz_estimated = zeros(N,1);
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
%    mag = A*(transpose(mag) - b);
%   size(mag)
%    mag = transpose(mag);
SOS =[ 
     1.0000   1.3085     1.0000    1.0000   -1.9382    0.9400
]
y1 = sosfilt(SOS,acc(:,1))/10
y2 = sosfilt(SOS,acc(:,2))/10
y3 = sosfilt(SOS,acc(:,3))/10
    
     
k = 1;
while( k < N)
     pitch_acc(k+1) = atan(y2(k)  /y3(k));
     roll_acc(k+1) = atan(-y1(k)/sqrt(y2(k)^2 + y3(k)^2));
     k = k +1;
end
figure;
subplot(3,1,1);
hold on;grid on;
 plot(time,roll_acc(1:N)*180/pi,'g');
legend( 'estimated');
title('Roll');

subplot(3,1,2);
hold on;grid on;

plot(time,pitch_acc(1:N)*180/pi,'g');
legend('estimated');
title('Pitch');
k = 1
y1-acc(:,1)


while k~=N

   
        [x, P] = EKF(x, t, P, Q, R_full, y1(k),y2(k), y3(k),...
                                            mag(k, 1), mag(k, 2), mag(k, 3),...
                                             gyro(k, 1), gyro(k, 2), gyro(k, 3)); 
%     
%      [x, P] = EKF(x, t, P, Q, R_full,acc(k,1),acc(k,2),acc(k,3),...
%                                             mag(k, 1), mag(k, 2), mag(k, 3),...
%                                             gyro(k, 1), gyro(k, 2), gyro(k, 3)); 
%      
     yaw_mag(k) = atan2(mag(k,2),mag(k,1))*180/pi;
     pitch_gyro(k+1) = pitch_gyro(k) + gyro(k,1)*t;
     roll_gyro(k+1) = roll_gyro(k) + gyro(k,2)*t;
     yaw_gyro(k+1) = yaw_gyro(k) + gyro(k,3)*t;
     
      pitch_acc(k+1) = atan(acc(k,2)  /acc(k,3));
      roll_acc(k+1) = atan(-acc(k,1)/sqrt(acc(k,2)^2 + acc(k,3)^2));
%      
     L =  mag(k,1)^2 + mag(k,2)^2;
     x_0 = mag(k,2)/(sqrt(2)*sqrt(L - mag(k,1)*sqrt(L)));
     x_3 = sqrt(L - mag(k,1)*sqrt(L))/sqrt(2*L);
     x_test  = [x_0 0 0 x_3];
     H = -2* [[x_test(4) x_test(3) x_test(2) x_test(1)];
     [x_test(1) -x_test(2) x_test(3) -x_test(4)];
     [-x_test(2) -x_test(1) x_test(4) x_test(3)]];  
 
     y_test = H*transpose(x_test);
  
%       s_test = transpose(y(3:6)) - y_test;
  
     [roll_estimated(k), pitch_estimated(k), yaw_estimated(k)] = IMU_Quaternion2Euler(x(1), x(2), x(3), x(4));
%      Pt(k) = trace(P);
     yaw_estimated(k) = yaw_estimated(k);
     pitch_estimated(k) = pitch_estimated(k);
%      if(roll_estimated(k) < 0)
%      roll_estimated(k) = -roll_estimated(k);
%      else
%          roll_estimated(k) = roll_estimated(k) - 180;
%      end
%      if(yaw_estimated(k) < 0)
%          yaw_estimated(k) = yaw_estimated(k) + 180;
%      end
    k = k+1;   
end

size(roll_estimated)
size(time)
% Plot estimated orientation and error
figure;
subplot(3,1,1);
hold on;grid on;
plot(time,pitch_estimated,'b');
 plot(time,roll_acc(1:N)*180/pi,'g');
legend( 'estimated');
title('Roll');

subplot(3,1,2);
hold on;grid on;

plot(time,roll_estimated,'b');
plot(time,pitch_acc(1:N)*180/pi,'g');
legend('estimated');
title('Pitch');

subplot(3,1,3);
hold on;grid on;
plot(time,yaw_mag,'r');
plot(time,yaw_estimated,'b');

legend('estimated');
title('Yaw');
