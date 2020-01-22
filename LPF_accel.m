log_file_full = load('./data/EKF_drone11.txt');
starting_row =1;
end_row = 998;
log_file_test  = log_file_full(starting_row:end_row,:);

N = max(size(log_file_test)); % Size of tested sample
T = 0.004815; % Sampling time
time = 0:T:(N-1)*T; % Time array
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Change unit of sensor values
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
acc  = log_file_test(:,4:6);       % unit: m/s^2
SOS =[ 
   1.0000    2.0000    1.0000    1.0000   -1.1775    0.5197
    1.0000    1.0000         0    1.0000   -0.4747         0
]
y1 = sosfilt(SOS,acc(:,1))/16384/10^2;
y2 = sosfilt(SOS,acc(:,2))/16384/10^2;
y3 = sosfilt(SOS,acc(:,3))/16384/10^2;
    
y1
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