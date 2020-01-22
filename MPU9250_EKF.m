log_file_full = load('./data/EKF_stm32_test2_p.txt');
starting_row = 1;
end_row = 1000;
log_file_test  = log_file_full(starting_row:end_row,:);

N = max(size(log_file_test)); % Size of tested sample
T = 0.003; % Sampling time
time = 0:T:(N-1)*T; % Time array

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Change unit of sensor values
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
gyro = log_file_test(:,1:3);        % unit: rad/s
acc  = log_file_test(:,4:6);       % unit: m/s^2
mag  = log_file_test(:,7:9);        % unit: gauss
t = 0.00635;
bg = [-0.2639 -0.2873 -0.2661];
ba =  [ 0.0361  0.0352  0.0405];
% acc(:,3) = acc(:,3) - 16384.0;
sigma_g = [0.0033    0.0352    0.0405]

% acc = acc /16384.0 - ba;
% gyro = (gyro)/(16.4*180)*pi;

sigma_a = [0.0058    0.0033    0.0076];


mean(gyro)
mean(acc)

P = eye(7)*100 
Q = [[0 0 0 0 0 0 0]
     [0 0 0 0 0 0 0]
     [0 0 0 0 0 0 0]
     [0 0 0 0 0 0 0]
     [0 0 0 0 0.0001 0 0]
     [0 0 0 0 0 0.0001 0]
     [0 0 0 0 0 0 0.0001]];
R_full = [[0.0001 0 0 0 0 0]
          [0 0.0001 0 0 0 0]
          [0 0 0.0001 0 0 0]
          [0 0 0 0.00001 0 0]
          [0 0 0 0 0.00001 0]
          [0 0 0 0 0 0.00001]];

roll_estimated = zeros(N,1);
pitch_estimated = zeros(N,1);
yaw_estimated = zeros(N,1);
Gx_estimated = zeros(N,1);
Gy_estimated = zeros(N,1);
Gz_estimated = zeros(N,1);
Pt = zeros(N,1);
k = 1

% madgwick = log_file_test(:,10:13);

% % % 
   A =[[ 0.0044    0.0002   -0.0000]
       [0.0002    0.0045    0.0000]
      -[0.0000    0.0000    0.0053]];
% % % 
   b =[-41.2889
      94.2928
      2.2679];
   mag = A*(transpose(mag) - b);
%   size(mag)
   mag = transpose(mag);
%    
while k~=N
    [x, P] = EKF(x, t, P, Q, R_full,acc(k, 1), acc(k, 2), acc(k, 3),...
                                            mag(k, 1), mag(k, 2), mag(k, 3),...
                                            gyro(k, 1), gyro(k, 2), gyro(k, 3));
     [roll_estimated(k), pitch_estimated(k), yaw_estimated(k)] = IMU_Quaternion2Euler(x(1), x(2), x(3), x(4));
     yaw_mag(k) = atan2(mag(k,2),mag(k,1))*180/pi;
%      [roll_madgwick(k), pitch_madgwick(k), yaw_madgwick(k)] = IMU_Quaternion2Euler(madgwick(1), madgwick(2), madgwick(3), madgwick(4));
%      Pt(k) = trace(P);
        if(roll_estimated(k) > 0)
           roll_estimated(k) = roll_estimated(k);
       
       else
         roll_estimated(k) = roll_estimated(k) ;
       end
       pitch_estimated(k) = pitch_estimated(k);
     
     if(yaw_estimated(k) > 0)
        yaw_estimated(k) = 180 - yaw_estimated(k)  ;
     end
     if(yaw_estimated(k) < 0)
         yaw_estimated(k) = yaw_estimated(k) + 180;
     end
    k = k+1;   
    x;
    Gx_estimated(k)     =  x(5);
    Gy_estimated(k)     =  x(6);
    Gz_estimated(k)     =  x(7);

end

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

plot(time,yaw_estimated,'b');

legend('estimated');
title('Yaw');
