s1=serial('/dev/ttyUSB4','Baudrate',115200);
fopen(s1);
accX=0;accY=0;accZ=0;
str='';
sen=0;
j=1;
bg = [-0.6376 -1.9228 -0.325];
x =               [1                       % gyrox
                  0                       % gyroy
                  0                       % gyroz
                  0                     % qa
                  bg(1)                   % qb              
                  bg(2)% qc
                  bg(3)]
P = eye(7)*100 
Q = [[0 0 0 0 0 0 0]
     [0 0 0 0 0.01 0 0]
     [0 0 0 0 0 0.01 0]
     [0 0 0 0 0 0 0.01]
    [0,0, 0 ,0 ,6.4290e-05 ,0, 0],
        [ 0,0,0,0,0,9.0503e-05,0],
       [0,0,0,0,0,0, 8.3943e-05]];
R = [[ 8.3943e-05,0,0,0,0,0],
          [ 0, 9.0680e-5,0,0,0,0],
          [0,0,8.4107e-5,0,0,0],
          [ 0,0,0,1e-5,0,0],
          [ 0,0,0,0,1e-5,0],
          [0,0,0,0,0,1e-5]]
while(1)
    
    str=fscanf(s1);
    str1 = split(str, ' ');
    
    sen = str2double(str1);
    size(sen);
    w = [sen(1)  sen(2)  sen(3)] /180*pi
    y_full = [sen(4)  sen(5)  sen(6) sen(7)  sen(8)  sen(9)];
 s_trans = [[-x(2),-x(3),-x(4)];
            [x(1),-x(4),x(3)];
            [x(4), x(1), -x(2)];
            [-x(3), x(2),x(1)]];
 s_up = -s_trans*0.5*t;
%      
% %      
  A = [[eye(4), s_up];
      [zeros(3,4), eye(3)]];
% % 
  B = [s_trans*0.5*t; zeros(3)];
% % %predict route
% % 
  x = A*x + B*transpose(w)
%  P = A*P*transpose(A) +Q; 
% 
% Ca = [[-x(3) x(4) -x(1) x(2)];
%       [x(2) x(1) x(4) x(3)];
%       [x(1) -x(2) -x(3) x(4)]];
% Cm = [[x(4) x(3) x(2) x(1)];
%      [x(1) -x(2) x(3) -x(4)];
%      [-x(2) -x(1) x(4) x(3)]];
%       H_full =[[-2.*Ca zeros(3)]; [-2.*Cm zeros(3)]];
%       K_full = P*transpose(H_full)*(H_full*P*transpose(H_full) + R)^-1;
% %       y;
%       s_full = (transpose(y_full) - H_full*x);
% %     m = [ transpose(y) H*x];
%      x = x + K_full*s_full;
%      P = (eye(7) - K_full*H_full)*P 
   norm = sqrt(x(1)^2 + x(2)^2 + x(3)^2 + x(4)^2);
       x(1) = x(1)/norm;
       x(2) = x(2)/norm;
       x(3) = x(3)/norm;
       x(4) = x(4)/norm;
   [roll_estimated, pitch_estimated, yaw_estimated] = IMU_Quaternion2Euler(x(1), x(2), x(3), x(4));
end;