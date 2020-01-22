
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
function [x_k, P_plus_k] = EKF1(x,t,P,Q,R, Ax, Ay, Az, Mx, My, Mz, Gx, Gy, Gz)
    
w = [ Gx, Gy, Gz];
y =  [Ax, Ay, Az];

mag_norm = sqrt(Mx^2 + My^2 + Mz^2);
y_full = [Ax, Ay, Az,Mx/mag_norm,My/mag_norm,Mz/mag_norm];

s_trans = [[-x(2),-x(3),-x(4)];
           [x(1),-x(4),x(3)];
           [x(4), x(1), -x(2)];
           [-x(3), x(2),x(1)]];
s_up = -s_trans*0.5*t;



    A = [[eye(4)]];
    B = [s_trans*0.5*t];
%predict route

     x = A*x + B*transpose(w);
     P = A*P*transpose(A) +Q ;
% % %quaternion rotation matrix
% % Ca = [[-x(3) x(4) -x(1) x(2)];
      [x(2) x(1) x(4) x(3)];
      [x(1) -x(2) -x(3) x(4)]];
 Cm = [[x(4) x(3) x(2) x(1)];
     [x(1) -x(2) x(3) -x(4)];
     [-x(2) -x(1) x(4) x(3)]];
   H =[ [-2*Ca]];
   H_full =[ [-2*Ca ]; [2*Cm]];

%     K = P*transpose(H)/(H*P*transpose(H) + R);
    K_full = P*transpose(H_full)/(H_full*P*transpose(H_full) + R);
%       y;
    
%     s = (transpose(y) - H*x);
    s_full = (transpose(y_full) - H_full*x);
    m = [ transpose(y) H*x];
    a = K_full*s_full
     x = x + a;
     P = (eye(4) - K_full*H_full)*P ;
    norm = sqrt(x(1)^2 + x(2)^2 + x(3)^2 + x(4)^2);
    x(1) = x(1)/norm;
    x(2) = x(2)/norm;
    x(3) = x(3)/norm;
    x(4) = x(4)/norm;
    x_k = [x(1) x(2) x(3) x(4)];
    P_plus_k = P;
end

