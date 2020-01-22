s1=serial('/dev/ttyUSB2','Baudrate',115200);
fopen(s1);
accX=0;accY=0;accZ=0;
str='';
sen=0;
j=1;
q = [1;0;0;0];

while(1)
    
    str=fscanf(s1);
    str1 = split(str, ' ');
    
    sen = str2double(str1);
    size(sen);
    a = [sen(4); sen(5) ; sen(6)];
    w = [sen(1); sen(2) ;sen(3)] /180*pi
        s_trans = [[-q(2),-q(3),-q(4)];
           [q(1),-q(4),q(3)];
           [q(4), q(1), -q(2)];
           [-q(3), q(2),q(1)]];
    s_up = s_trans*0.5;
    dq = s_up*w;

    f = [[(q(2)*q(4)-q(1)*q(3))];
        [(q(1)*q(2)+q(3)*q(4))];
        [(0.5 - q(2)*q(2) - q(3)*q(3))]];
    f = 2*f - a;
    J = [-2*q(3) 2*q(4) -2*q(1) 2*q(2);
        2*q(2) 2*q(1) 2*q(4) 2*q(3);
        0 -4*q(2) -4*q(3) 0];
    delta = transpose(J)*f;
     q = q + ( - 0.1*delta/sqrt(sum(delta.^2)));
    [roll_estimated, pitch_estimated, yaw_estimated] = IMU_Quaternion2Euler(q(1), q(2), q(3), q(4))

end