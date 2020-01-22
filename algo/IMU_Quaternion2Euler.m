function [roll, pitch, yaw] = IMU_Quaternion2Euler(a, b, c, d)

	% roll (x-axis rotation)
	sinr = 2*(d*a + b * c);
	cosr = 1 - 2*(a*a + b * b);
	roll = atan2(sinr, cosr);

	% pitch (y-axis rotation)
	sinp = 2*( d*b - c*a);
    if (sinp >= 1)
        pitch = pi/2;  % use 90 degrees if out of range
    elseif (sinp <= -1)
        pitch = -pi/2; % use -90 degrees if out of range
    else
        pitch = asin(sinp);
    end
    
	% yaw (z-axis rotation)
	siny = 2*( d*c + a*b);
	cosy = 1 - 2*( b*b + c*c);  
	yaw = atan2(siny, cosy);
    
    roll = roll*180/pi;
    pitch = pitch*180/pi;
    yaw = yaw*180/pi;
end
