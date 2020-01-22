function [r,p,y] = LPF(y1,y2,y3,gx,gy,gz,mx,my,mz,r,p,y,dt)


alpha = 0.9

     pitch_acc= atan(y2  /y3)*180/pi;
     roll_acc = atan(-y1/sqrt(y2^2 + y3^2))*180/pi;
     yaw_mag = atan2(my,mx)*180/pi;

	 r = alpha*(r + dt*gx) + (1-alpha)*roll_acc;
	 p = alpha*(p + dt*gy) + (1-alpha)*pitch_acc;
	 y = alpha*(y + dt*gz) + (1-alpha)*yaw_mag;
end