
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Extended Kalman filter function
% Input u_k_1: prior control signal
% Input y_meas: measurement data (gyroscope, 
%               accelerometer, magnetometer)
% Input x_hat_plus_k_1: prior estimation
% Input P_plus_k_1: prior covariance of estimation
%                   error
% Output x_hat_plus_k: posteriori estimation
% Output P_plus_k: posteriori covariance of estimation
%                  error
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [x_hat_plus_k, P_plus_k] = EKF(Ax, Ay, Az, Mx, My, Mz, Gx, Gy, Gz)
    
w = [ Gx, Gy, Gz];
y =  [Ax, Ay, Az];
mag_norm = sqrt(Mx^2 + My^2 + Mz^2);

y_full = [acc(k, 1), acc(k, 2), acc(k, 3),Mx/mag_norm,My/mag_norm,Mz/mag_norm];

s_trans = [[-x(2),-x(3),-x(4)];
           [x(1),-x(4),x(3)];
           [x(4), x(1), -x(2)];
           [-x(3), x(2),x(1)]];
s_up = -s_trans*0.5*t;

Ca = [[-x(3) x(4) -x(1) x(2)];
      [x(2) x(1) x(4) x(3)];
      [x(1) -x(2) -x(3) x(4)]];
 Cm = [[x(4) x(3) x(2) x(1)];
     [x(1) -x(2) x(3) -x(4)];
     [-x(2) -x(1) x(4) x(3)]];
   H =[[-2*Ca zeros(3)]];
   H_full =[[-2*Ca zeros(3)]; [-2*Cm zeros(3)]];

    A = [[eye(4), s_up];
          [zeros(3,4), eye(3)]];
    B = [s_trans*0.5*t; zeros(3)];
%predict route

     x = A*x + B*transpose(w);
     P = A*P*transpose(A) +Q ;

    K = P*transpose(H)/(H*P*transpose(H) + R);
    K_full = P*transpose(H_full)/(H_full*P*transpose(H_full) + R_full);
%       y;
    
    s = (transpose(y) - H*x);
    s_full = (transpose(y_full) - H_full*x);
    m = [ transpose(y) H*x];
     x = x + K_full*s_full;
     P = (eye(7) - K_full*H_full)*P ;
    norm = sqrt(x(1)^2 + x(2)^2 + x(3)^2 + x(4)^2);
    x(1) = x(1)/norm;
    x(2) = x(2)/norm;
    x(3) = x(3)/norm;
    x(4) = x(4)/norm;
    [roll_estimated(k), pitch_estimated(k), yaw_estimated(k)] = IMU_Quaternion2Euler(x(2), x(3), x(4), x(1));
%      Pt(k) = trace(P);
        if(roll_estimated(k) > 0)
           roll_estimated(k) = roll_estimated(k) - 180;
       
       else
         roll_estimated(k) = roll_estimated(k) + 180;
       end
       pitch_estimated(k) = -pitch_estimated(k);
       yaw_estimated(k) = yaw_estimated(k);
     
%     if(yaw_estimated(k) > 180)
%         roll_estimated(k) = roll_estimated(k) - 180;
%     end
%     if(yaw_estimated(k) < -180)
%         roll_estimated(k) = roll_estimated(k) + 180;
%     end
    k = k+1;   
    Gx_estimated(k)     = Gx_estimated(k-1) +gyro(k, 1)*t;
    Gy_estimated(k)     = Gy_estimated(k-1) +gyro(k, 2)*t;
    Gz_estimated(k)     = Gz_estimated(k-1) +gyro(k, 3)*t;
end

