log_file_full = load('./data/EKF_stm32_2.txt');
starting_row =1;
end_row = 10000;
log_file_test  = log_file_full(starting_row:end_row,:);

N = max(size(log_file_test)); % Size of tested sample
T = 0.004815 % Sampling time
time = 0:T:(N-1)*T; % Time array
data = log_file_test(:,10:12);

% Plot estimated orientation and error
figure;
subplot(3,1,1);
hold on;grid on;
plot(time,data(:,1),'b');
legend( 'estimated');
title('Roll');

subplot(3,1,2);
hold on;grid on;

plot(time,data(:,2),'b');
legend( 'estimated');
title('Pitch');

subplot(3,1,3);
hold on;grid on;
plot(time,data(:,3),'b');
legend( 'estimated');
title('Yaw');