log_file_full = load('./data/EKF_stm32_test_2.txt');
starting_row = 1;
end_row = 1000;
log_file_test  = log_file_full(starting_row:end_row,:);
N = max(size(log_file_test)); % Size of tested sample
T = 0.00635; % Sampling time
time = 0:T:(N-1)*T; % Time array


gyro = log_file_test(:,1:3);        % unit: rad/s
acc  = log_file_test(:,4:6);       % unit: m/s^2
size(gyro(:,1))

bGx = mean(gyro(:,1))
bGy = mean(gyro(:,2))
bGz = mean(gyro(:,3))

bAx = mean(acc(:,1))
bAy = mean(acc(:,2))
bAz = mean(acc(:,3)) + 1

sGx = (std(gyro(:,1))/16.4)^2
sGy = (std(gyro(:,2))/16.4)^2
sGz = (std(gyro(:,3))/16.4)^2

sAx = (std(gyro(:,1))/16384)^2
sAy = (std(gyro(:,2))/16384)^2
sAz = (std(gyro(:,3) + 16384 )/16384)^2