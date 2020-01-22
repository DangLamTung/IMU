function [x,P] = EKF(x,t,P,Q,R, Ax, Ay, Az, Gx, Gy, Gz)
    
w = [ Gx, Gy, Gz];
y_full =  [Ax, Ay, Az];

% %       y = [  mag(k,1),mag(k,2), mag(k,3)];
%       s_trans = [[-x(2),-x(3),-x(4)];
%                   [x(1),-x(4),x(3)];
%                   [x(4), x(1), -x(2)];
%                   [-x(3), x(2),x(1)]];
%  s_up = -s_trans*0.5*t;
% %      
% % %      
%   A = [[eye(4), s_up];
%       [zeros(3,4), eye(3)]];
% % % 
%   B = [s_trans*0.5*t; zeros(3)];
% % % %predict route
% % % 
%   x = A*x + B*transpose(w);
%   P = A*P*transpose(A) +Q; 
% % 
Ca = [[-x(3) x(4) -x(1) x(2)];
      [x(2) x(1) x(4) x(3)];
      [x(1) -x(2) -x(3) x(4)]];

      H_full =[[-2.*Ca zeros(3)]];
      K_full = P*transpose(H_full)*(H_full*P*transpose(H_full) + R)^-1;
%       y;
      s_full = (transpose(y_full) - H_full*x);
%     m = [ transpose(y) H*x];
     x = x + K_full*s_full;
     P = (eye(7) - K_full*H_full)*P 
       norm = sqrt(x(1)^2 + x(2)^2 + x(3)^2 + x(4)^2);
       x(1) = x(1)/norm;
       x(2) = x(2)/norm;
       x(3) = x(3)/norm;
       x(4) = x(4)/norm;

        
end

