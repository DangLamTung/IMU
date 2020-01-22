log_file_full = load('EKF_acc_data.txt');
starting_row =1;
end_row = 4993;
log_file_test  = log_file_full(starting_row:end_row,:);

N = max(size(log_file_test)); % Size of tested sample
T = 0.03; % Sampling time
time = 0:T:(N-1)*T; % Time array
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Change unit of sensor values
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
gyro = log_file_test(:,1:3);        % unit: rad/s
acc  = log_file_test(:,4:6);       % unit: m/s^2
mag  = log_file_test(:,7:9);          % unit: gauss

bg = [-36.0826   11.4014  -12.5609];
ba =  [58.0127  -86.7915  801.4361];
% acc(:,3) = acc(:,3) - 16384.0;
sigma_g = [0.0033    0.0043    0.0023]

acc = (acc - ba)/16384.0;
gyro = (gyro - bg)/(16.4*180)*pi;

sigma_a = [0.0058    0.0033    0.0076];
bg = bg/(16.4*180)*pi;
t = 0.03
mean_g = mean(gyro)
mean_g = mean(acc)

x =               [1                       % gyrox
                  0                       % gyroy
                  0                       % gyroz
                  0]
z =               [1                       % gyrox
                  0                       % gyroy
                  0                       % gyroz
                  0]
% P = eye(7)*100
% Q = eye(7);
% 
% R_full = eye(6)*0.0000001;
P = eye(4)*100
Q = eye(4)*0.1
R = eye(4)*0.001

% R_full = [  sigma_a(1)  0  0 0 0 0 ;
%             0  sigma_a(2)  0 0 0 0 ;
%             0  0  sigma_a(3) 0 0 0 ;
%             0  0  0  5 0  0;
%             0  0  0  0  5  0;
%             0  0  0  0  0  5]
H = eye(4);
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

while k~=N
     w = [ gyro(k,1), gyro(k,2), gyro(k,3)];
     y = [acc(k,1),acc(k,2), acc(k,3)];
     
      norm_w = sqrt(w(1)^2 + w(2)^2 + w(3)^2);
     
%       y = [  mag(k,1),mag(k,2), mag(k,3)];
%      s_trans = [[-x(2),-x(3),-x(4)];
%            [x(1),-x(4),x(3)];
%            [x(4), x(1), -x(2)];
%            [-x(3), x(2),x(1)]];
% s_up = -s_trans*0.5*t;
     
     yaw_mag(k) = atan2(mag(k,2),mag(k,1))*180/pi;
     pitch_gyro(k+1) = pitch_gyro(k) + gyro(k,1)*t;
     roll_gyro(k+1) = roll_gyro(k) + gyro(k,2)*t;
     yaw_gyro(k+1) = yaw_gyro(k) + gyro(k,3)*t;
     
     pitch_acc(k+1) = atan(acc(k,2)  /acc(k,3));
     roll_acc(k+1) = atan(-acc(k,1)/sqrt(acc(k,2)^2 + acc(k,3)^2));
% 
s_trans = [[-x(2),-x(3),-x(4)];
           [x(1),-x(4),x(3)];
           [x(4), x(1), -x(2)];
           [-x(3), x(2),x(1)]];
s_up = -s_trans*0.5*t;



    A = [[eye(4)]];
    B = [s_trans*0.5*t];
%predict route

     x = A*x + B*transpose(w);
     P = A*P*transpose(A) +Q ;

     C_a = 2*[[-x(3) x(4) -x(1) x(2)];
          [x(2) x(1) x(4) x(3)];
          [x(1) -x(2) -x(3) x(4)]];
     R_a = [[2*x(2)*x(4) + 2*x(1)*x(3)];
          [2*x(3)*x(4) - 2*x(1)*x(2)];
          [x(1)^2 - x(2)^2 - x(3)^2 + x(4)^2]];
     f_a = transpose(R_a) - y;
     size(f_a);
     grad = transpose(C_a)*transpose(f_a);
     norm_g = sqrt(grad(1)^2 + grad(2)^2 + grad(3)^2 + grad(4)^2);
     z = z - 0.5*norm_w*0.03*grad/norm_g;
     
     K = P*transpose(H)*inv(H*P*transpose(P)+R)
     x = x + K*(z - H*x);
     P = (eye(4) - K*H)*P;
     
     norm = sqrt(x(1)^2 + x(2)^2 + x(3)^2 + x(4)^2); 
     x(1) = x(1)/norm;
     x(2) = x(2)/norm;
     x(3) = x(3)/norm;
     x(4) = x(4)/norm;
    
     [roll_estimated(k), pitch_estimated(k), yaw_estimated(k)] = IMU_Quaternion2Euler(x(1), x(2), x(3), x(4));
     k = k+1;
end
size(roll_estimated)
size(time)
% Plot estimated orientation and error
figure;
subplot(3,1,1);
hold on;grid on;


plot(time,yaw_estimated,'b');
plot(time,roll_acc(1:N)*180/pi,'g');
legend( 'estimated');
title('Roll');

subplot(3,1,2);
hold on;grid on;
plot(time,pitch_estimated,'b');
plot(time,pitch_acc(1:N)*180/pi,'g');
legend('estimated');
title('Pitch');

subplot(3,1,3);
hold on;grid on;
plot(time,yaw_mag,'r');
plot(time,roll_estimated,'b');
plot(time,yaw_quat(1:N),'g');
legend('estimated');
title('Yaw');