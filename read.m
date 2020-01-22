clear all
% close all
clc

ax_max = 1003;
ax_min = -994;
ay_max = 1000;
ay_min = -997;
az_max = 1007;
az_min = -991;
acc_bias = [(ax_max+ax_min)/2, (ay_max+ay_min)/2, (az_max+az_min)/2];

% a = load('dulieu\banxoay_480euler_500Hz\still\log11.txt');
a = load('dulieu\banxoay_480euler_500Hz\rot\log25.txt');

T = 0.002;
N = max(size(a));
tt = 0:T:(N-1)*T;

gyro = a(:,4:6)*pi/180000;        % unit: rad/s
acc  = a(:,7:9)/10;               % unit: mg
mag  = a(:,10:12)/10;             % unit: mgauss

for i=1:N,
    acc(i,:)  = acc(i,:) - acc_bias;
end

% euler angle a = (phi, theta, psi)'
q = zeros(N,4);
b = zeros(N,3);
error = zeros(N,4);
qkMPE = zeros(N,4);


test_banxoay_480_500Hz;

