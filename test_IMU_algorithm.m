%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Calculating and validating the IMU algorithms
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% log_01.txt - log_02.txt:   alpha = 10 (/10000) * (0.01) * (...)
% log_03.txt - log_03.txt:   alpha = 1  (/10000) * (0.01) * (...)
% log_04.txt - log_06.txt:   alpha = 1 (/10000) * (0.001) * (...)

close all;
clear all;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read and extract data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
log_file_full = load('banxoay_480euler_500Hz/final/log_13.TXT');
starting_row = 1;
end_row = 30000;
log_file_test  = log_file_full(starting_row:end_row,:);

N = max(size(log_file_test)); % Size of tested sample
T = 0.002; % Sampling time
time = 0:T:(N-1)*T; % Time array

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Change unit of sensor values
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
gyro = log_file_test(:,4:6)*pi/180000;        % unit: rad/s
acc  = log_file_test(:,7:9)*9.81/10000;       % unit: m/s^2
mag  = log_file_test(:,10:12)/10000;          % unit: gauss

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Validate algorithms
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
addpath('algo/');
% Initialization
x_hat_plus_k_1 = [0                       % gyrox
                  0                       % gyroy
                  0                       % gyroz
                  0                       % qa
                  0                       % qb
                  0                       % qc
                  1];                     % qd
P_plus_k_1 = eye(7)*0.0001;
          
Q_k = [ 0.0000374  0  0  0  0  0  0;
        0  0.000354  0  0  0  0  0;
        0  0  0.0000153  0  0  0  0;
        0  0  0  0  0  0  0;
        0  0  0  0  0  0  0;
        0  0  0  0  0  0  0;
        0  0  0  0  0  0  0;];
	   
R_k = [ 0.0000374  0  0  0  0  0  0  0  0;
        0  0.000354  0  0  0  0  0  0  0;
        0  0  0.0000153  0  0  0  0  0  0;
        0  0  0  0.0000178  0  0  0  0  0;
        0  0  0  0  0.0000134  0  0  0  0;
        0  0  0  0  0  0.0000192  0  0  0;
        0  0  0  0  0  0  0.00000372  0  0;
        0  0  0  0  0  0  0  0.00000231  0;
        0  0  0  0  0  0  0  0  0.00000155];
          
tau_rx = 0.01;
tau_ry = 0.01;
tau_rz = 0.01;

ax_inertial = 0;
ay_inertial = 0;
az_inertial = 9.81;
mx_inertial = -0.171683422108236;
my_inertial = 0.035035590090210;
mz_inertial = 0.030100000000000;

k = 1;
Gx_estimated = zeros(N,1);
Gy_estimated = zeros(N,1);
Gz_estimated = zeros(N,1);
roll_estimated = zeros(N,1);
pitch_estimated = zeros(N,1);
yaw_estimated = zeros(N,1);
while k~=N
    [x_hat_plus_k, P_plus_k] = IMU_quat_EKF(acc(k, 1), acc(k, 2), acc(k, 3),...
                                            mag(k, 1), mag(k, 2), mag(k, 3),...
                                            gyro(k, 1), gyro(k, 2), gyro(k, 3),...
                                            x_hat_plus_k_1, P_plus_k_1, Q_k, R_k, T, tau_rx, tau_ry, tau_rz,...
                                            ax_inertial, ay_inertial, az_inertial,...
                                            mx_inertial, my_inertial, mz_inertial);

    Gx_estimated(k)     = x_hat_plus_k(1);
    Gy_estimated(k)     = x_hat_plus_k(2);
    Gz_estimated(k)     = x_hat_plus_k(3);

    [roll_estimated(k), pitch_estimated(k), yaw_estimated(k)] = ...
        IMU_Quaternion2Euler(x_hat_plus_k(4), x_hat_plus_k(5), x_hat_plus_k(6), x_hat_plus_k(7));

    
    x_hat_plus_k_1 = x_hat_plus_k;
    P_plus_k_1 = P_plus_k;

    k = k+1;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plot data and error
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read and extract reference data from commercial IMU and encoder
IMU = log_file_test(:,1:3)/1000;
ENC = (log_file_test(:,16:18) - 32000) * 360 / 10000;
ENC(:,2) = -ENC(:,2);
% ENC(:,3) = -ENC(:,3);

offset = IMU(1,:) - ENC(1,:);
error  = IMU - ENC;
error(:,1) = error(:,1) - offset(1); 
error(:,2) = error(:,2) - offset(2);
error(:,3) = error(:,3) - offset(3);

RMS_error = [norm(error(:,1))/sqrt(N);
             norm(error(:,2))/sqrt(N);
             norm(error(:,3))/sqrt(N)]

gain = 100;
figure;
subplot(3,1,1);
hold on;grid on;
plot(time,ENC(:,1),'r');
plot(time,IMU(:,1),'b');
plot(time,error(:,1)*gain,'g');
plot(time,log_file_test(:,4)/10000,'black');
legend('enc','imu','err*100','rate/10');
title('Roll');

subplot(3,1,2);
hold on;grid on;
plot(time,ENC(:,2),'r');
plot(time,IMU(:,2),'b');
plot(time,error(:,2)*gain,'g');
plot(time,log_file_test(:,5)/10000,'black');
legend('enc','imu','err*100','rate/10');
title('Pitch');

subplot(3,1,3);
hold on;grid on;
plot(time,ENC(:,3),'r');
plot(time,IMU(:,3),'b');
plot(time,error(:,3)*gain,'g');
plot(time,log_file_test(:,6)/10000,'black');
legend('enc','imu','err*100','rate/10');
title('Yaw');

% Plot estimated angular velocity and measured
figure;
subplot(3,1,1);
hold on;grid on;
plot(time,gyro(:,1),'r');
plot(time,Gx_estimated,'b');
legend('measured', 'estimated');
title('x-axis');

subplot(3,1,2);
hold on;grid on;
plot(time,gyro(:,2),'r');
plot(time,Gy_estimated,'b');
legend('measured', 'estimated');
title('y-axis');

subplot(3,1,3);
hold on;grid on;
plot(time,gyro(:,3),'r');
plot(time,Gz_estimated,'b');
legend('measured', 'estimated');
title('z-axis');


% Plot estimated orientation and error
error = zeros(N,3);
error = ENC - [roll_estimated, pitch_estimated, yaw_estimated];
figure;
subplot(3,1,1);
hold on;grid on;
plot(time,ENC(:,1),'r');
plot(time,roll_estimated,'b');
plot(time,error(:,1),'g');
legend('enc', 'estimated', 'error');
title('Roll');

subplot(3,1,2);
hold on;grid on;
plot(time,ENC(:,2),'r');
plot(time,pitch_estimated,'b');
plot(time,error(:,2),'g');
legend('enc', 'estimated', 'error');
title('Pitch');

subplot(3,1,3);
hold on;grid on;
plot(time,ENC(:,3),'r');
plot(time,yaw_estimated,'b');
plot(time,error(:,3),'g');
legend('enc', 'estimated', 'error');
title('Yaw');
