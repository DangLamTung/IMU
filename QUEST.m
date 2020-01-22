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
%acc(:,3) = acc(:,3) - 16384.0;
sigma_g = [0.0033    0.0352    0.0405]

acc = (acc -  ba)/16384.0 ;
gyro = (gyro)/(180)*pi;

t = 0.002
mean_g = mean(gyro)
mean_g = mean(acc);

roll_estimated = zeros(N,1);
pitch_estimated = zeros(N,1);
yaw_estimated = zeros(N,1);


pitch_acc = zeros(N,1);
roll_acc = zeros(N,1);

mean_a = mean(acc(:,1))
q = [1;0;0;0];
N = 1000;
k = 1;
t = 0.00125;

while k~=N
      
    pitch_acc(k+1) = atan(acc(k,2)  /acc(k,3));
    roll_acc(k+1) = atan(-acc(k,1)/sqrt(acc(k,2)^2 + acc(k,3)^2));
      
    s_trans = [[-q(2),-q(3),-q(4)];
           [q(1),-q(4),q(3)];
           [q(4), q(1), -q(2)];
           [-q(3), q(2),q(1)]];
    s_up = s_trans*0.5;
     
    w = [gyro(k,1);gyro(k,2);gyro(k,3)];
    
    dq = s_up*w;
    a = [acc(k,1);acc(k,2);acc(k,3)];
    f = [[(q(2)*q(4)-q(1)*q(3))];
        [(q(1)*q(2)+q(3)*q(4))];
        [(0.5 - q(2)*q(2) - q(3)*q(3))]];
    f = 2*f - a;
    J = [-2*q(3) 2*q(4) -2*q(1) 2*q(2);
        2*q(2) 2*q(1) 2*q(4) 2*q(3);
        0 -4*q(2) -4*q(3) 0];
    delta = transpose(J)*f;
      q = (q  - 0.2*0.02* delta/sqrt(sum(delta.^2))) + 0.8*(dq )*t;
%       q = q + (dq )*t;
    [roll_estimated(k), pitch_estimated(k), yaw_estimated(k)] = IMU_Quaternion2Euler(q(1), q(2), q(3), q(4));
    roll_estimated(k);
    pitch_estimated(k);
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
% plot(time,yaw_mag,'r');
plot(time,yaw_estimated,'b');

legend('estimated');
title('Yaw');