log_file_full = load('Kalman_data_test_2.txt');
starting_row = 1;
end_row = 9000;
log_file_test  = log_file_full(starting_row:end_row,:);
N = max(size(log_file_test)); % Size of tested sample
T = 0.00635; % Sampling time
time = 0:T:(N-1)*T; % Time array


gyro = log_file_test(:,1:3)/16.4;        % unit: rad/s
acc  = log_file_test(:,4:6)/16384;       % unit: m/s^2
mag  = log_file_test(:,7:9)

t = 0.00635
x =               [1                       % gyrox
                  0                       % gyroy
                  0                       % gyroz
                  0                     % qa
                  -0.0372                     % qb
                  -0.0309                      % qc
                  -0.0309];                     %
P = eye(7)*100
Q = [   0  0  0  0  0  0  0;
        0  0  0  0  0  0  0;
        0  0  0  0  0  0  0;
        0  0  0  0  0  0  0;
        0 0 0 0  0.0000374 0 0;
        0 0 0 0  0  0.0000354 0;
        0 0 0 0  0  0  0.0000153; ];
R = [  0.0178 ,0 ,0  ;
       0 ,0.0134 ,0  ;
       0 ,0, 0.0192  ]
R_full = [  -0.0483   0  0 0 0 0 ;
       0   -0.0566  0 0 0 0 ;
       0  0   -0.0586 0 0 0 ;
       0  0  0  0.072  0  0;
       0  0  0  0  0.0231  0;
       0  0  0  0  0  0.0155];
roll_estimated = zeros(N,1);
pitch_estimated = zeros(N,1);
yaw_estimated = zeros(N,1);
Gx_estimated = zeros(N,1);
Gy_estimated = zeros(N,1);
Gz_estimated = zeros(N,1);
Pt = zeros(N,1);
k = 1

while k~=N
    [x_k, P_plus_k] = EKF(x, t, P, Q, R_full,acc(k, 1), acc(k, 2), acc(k, 3),...
                                            mag(k, 1), mag(k, 2), mag(k, 3),...
                                            gyro(k, 1), gyro(k, 2), gyro(k, 3));
     [roll_estimated(k), pitch_estimated(k), yaw_estimated(k)] = IMU_Quaternion2Euler(x_k(2), x_k(3), x_k(4), x_k(1));
%      Pt(k) = trace(P);
        if(roll_estimated(k) > 0)
           roll_estimated(k) = roll_estimated(k) -180 ;
       
       else
         roll_estimated(k) = roll_estimated(k) ;
       end
       pitch_estimated(k) = pitch_estimated(k);
       yaw_estimated(k) = yaw_estimated(k);
     
%     if(yaw_estimated(k) > 180)
%         roll_estimated(k) = roll_estimated(k) - 180;
%     end
%     if(yaw_estimated(k) < -180)
%         roll_estimated(k) = roll_estimated(k) + 180;
%     end
    k = k+1;   
    x;
    Gx_estimated(k)     =  x(5);
    Gy_estimated(k)     =  x(6);
    Gz_estimated(k)     = x(7);
end

figure;
subplot(3,1,1);
hold on;grid on;
plot(time,roll_estimated,'b');
legend('estimated');
title('Roll');

subplot(3,1,2);
hold on;grid on;
plot(time,pitch_estimated,'b');
legend('estimated');
title('Pitch');

subplot(3,1,3);
hold on;grid on;
plot(time,yaw_estimated,'b');
legend('estimated');
title('Yaw');
