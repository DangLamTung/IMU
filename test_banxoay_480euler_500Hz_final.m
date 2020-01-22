% close all
clear all
% log_01.txt - log_02.txt:   alpha = 10 (/10000) * (0.01) * (...)
% log_03.txt - log_03.txt:   alpha = 1  (/10000) * (0.01) * (...)
% log_04.txt - log_06.txt:   alpha = 1 (/10000) * (0.001) * (...)


a1 = load('/home/danglamtung/IMU_/banxoay_480euler_500Hz/final/log_31.TXT');
N1 = 100000;
N2 = 105000;
a  = a1(N1:N2,:);

N = max(size(a));
T = 0.002;
tt = 0:T:(N-1)*T;

% for i=1:N,
%     if a(i,1)>180000,
%         a(i,1) = a(i,1)-360000;
%     end
%     if a(i,2)>180000,
%         a(i,2) = a(i,2)-360000;
%     end
% %     if a(i,3)>180000,
% %         a(i,3) = a(i,3)-360000;
% %     end
% end

% a(:,3) = a(:,3) - a(1,3);

% EncRoll  = -(a(:,10) - 32000) * 360 / 10000;
% EncPitch = (a(:,11) - 32000) * 360 / 10000;
% EncYaw   = (a(:,12) - 32000) * 360 / 10000;
gain = 100;

IMU = a(:,1:3)/1000;
ENC = (a(:,16:18) - 32000) * 360 / 10000;
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

h1 = figure;
subplot(3,1,1);
hold on;grid on;
plot(tt,ENC(:,1),'r');
plot(tt,IMU(:,1),'b');
plot(tt,error(:,1)*gain,'g');
plot(tt,a(:,4)/10000,'black');
legend('enc','imu','err*100','rate/10')
title('Roll');

subplot(3,1,2);
hold on;grid on;
plot(tt,ENC(:,2),'r');
plot(tt,IMU(:,2),'b');
plot(tt,error(:,2)*gain,'g');
plot(tt,a(:,5)/10000,'black');
legend('enc','imu','err*100','rate/10')
title('Pitch');



subplot(3,1,3);
hold on;grid on;
plot(tt,ENC(:,3),'r');
plot(tt,IMU(:,3),'b');
plot(tt,error(:,3)*gain,'g');
plot(tt,a(:,6)/10000,'black');
legend('enc','imu','err*100','rate/10')
title('Yaw');

set(h1,'Position',[20 20 600 700]);

% sumw = a(:,4).^2 + a(:,5).^2 + a(:,6).^2;
% sumw = sqrt(sumw);
% figure
% plot(tt,sumw)
% 
% suma = a(:,7).^2 + a(:,8).^2 + a(:,9).^2;
% suma = sqrt(suma);
% figure
% plot(tt,suma)
% 
% Fs = 1000;
% L  = N;
% NFFT = 2^nextpow2(L); % Next power of 2 from length of y
% Y1 = fft(a(:,4),NFFT)/L;
% Y2 = fft(a(:,5),NFFT)/L;
% Y3 = fft(a(:,6),NFFT)/L;
% f = Fs/2*linspace(0,1,NFFT/2+1);

% Plot single-sided amplitude spectrum.
% figure;
% subplot(1,3,1);
% plot(f,2*abs(Y1(1:NFFT/2+1))); 
% grid on;
% title('Spectrum wx');
% xlabel('Frequency (Hz)');
% xlim([0 60]);
% ylabel('|Y(f)|')
% 
% subplot(1,3,2);
% plot(f,2*abs(Y2(1:NFFT/2+1))); 
% grid on;
% title('Spectrum wy')
% xlabel('Frequency (Hz)')
% xlim([0 60]);
% ylabel('|Y(f)|');
% 
% subplot(1,3,3);
% plot(f,2*abs(Y3(1:NFFT/2+1))); 
% grid on;
% title('Spectrum wz');
% xlabel('Frequency (Hz)');
% xlim([0 60]);
% ylabel('|Y(f)|');


