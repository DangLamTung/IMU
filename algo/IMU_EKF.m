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
function [x_hat_plus_k, P_plus_k] = IMU_EKF(u_k_1, y_meas, x_hat_plus_k_1, P_plus_k_1,...
                                            Q_k, R_k, T, tau_rx, tau_ry, tau_rz,...
                                            ax_inertial, ay_inertial, az_inertial,...
                                            mx_inertial, my_inertial, mz_inertial)
	assert(isa(u_k_1,'double') );
    assert(isa(y_meas,'double') );
    assert(all(size(y_meas)== [9 1]));
    assert(isa(x_hat_plus_k_1,'double') && isa(P_plus_k_1,'double'));
    assert(all(size(x_hat_plus_k_1)== [7 1]));
    assert(all(size(P_plus_k_1)== [7 7]));
    
    assert(isa(Q_k,'double') && isa(R_k,'double'));
    assert(all(size(Q_k)== [7 7]));
    assert(all(size(R_k)== [9 9]));
    
    assert(isa(T,'double') );
    assert(isa(tau_rx,'double') );
    assert(isa(tau_ry,'double') );
    assert(isa(tau_rz,'double') );
    assert(isa(ax_inertial,'double') && isa(ay_inertial,'double') && isa(az_inertial,'double') );
    assert(isa(mx_inertial,'double') && isa(my_inertial,'double') && isa(mz_inertial,'double') );


    % System state and measurement funtions
	% f1 = T*((-1/tau_rx)*x1 + w_rx) + x1;
	% f2 = T*((-1/tau_ry)*x2 + w_ry) + x2;
	% f3 = T*((-1/tau_rz)*x3 + w_rz) + x3;
	% f4 = T*(1/2)*( x1*x7 - x2*x6 + x3*x5) + x4;
	% f5 = T*(1/2)*( x1*x6 + x2*x7 - x3*x4) + x5;
	% f6 = T*(1/2)*(-x1*x5 + x2*x4 + x3*x7) + x6;
	% f7 = T*(1/2)*(-x1*x4 - x2*x5 - x3*x6) + x7;

	% ax_inertial = 0;
	% ay_inertial = 0;
	% az_inertial = 9.81;
	% mx_inertial = 25.97;
	% my_inertial = 9.25;
	% mz_inertial = -9.14;
	% yAE = [ 0; 0; 9.81];
	% yME = [ 25.97; 9.25; -9.14];
	% R = [ (x4^2-x5^2-x6^2+x7^2)  2*(x4*x5+x6*x7)         2*(x4*x6-x5*x7); 
	%		2*(x4*x5-x6*x7)        (-x4^2+x5^2-x6^2+x7^2)  2*(x5*x6+x4*x7);
	%		2*(x4*x6+x5*x7)        2*(x5*x6-x4*x7)         (-x4^2-x5^2+x6^2+x7^2)];
	% 
	% h1 = x1 + v1;
	% h2 = x2 + v2;
	% h3 = x3 + v3;
	% yAB = R*yAE + [v4; v5; v6]
	% h4 = yAB(1);
	% h5 = yAB(2);
	% h6 = yAB(3);
	% yMB = R*yME + [v7; v8; v9]
	% h7 = yMB(1);
	% h8 = yMB(2);
	% h9 = yMB(3);

	I = [ 1 0 0 0 0 0 0;
	      0 1 0 0 0 0 0;
	      0 0 1 0 0 0 0; 
	      0 0 0 1 0 0 0;
	      0 0 0 0 1 0 0;
	      0 0 0 0 0 1 0;
	      0 0 0 0 0 0 1];      

	% (a) Compute the following partial derivative matrices:
	x1 = x_hat_plus_k_1(1);
	x2 = x_hat_plus_k_1(2);
	x3 = x_hat_plus_k_1(3);
	x4 = x_hat_plus_k_1(4);
	x5 = x_hat_plus_k_1(5);
	x6 = x_hat_plus_k_1(6);
	x7 = x_hat_plus_k_1(7);
	u  = u_k_1;
	F = [ 1-T/tau_rx,          0,          0,         0,         0,         0,        0;
		          0,  1-T/tau_ry,          0,         0,         0,         0,        0;
		          0,          0,  1-T/tau_rz,         0,         0,         0,        0;
		   (T*x7)/2,  -(T*x6)/2,   (T*x5)/2,         1,  (T*x3)/2, -(T*x2)/2, (T*x1)/2;
		   (T*x6)/2,   (T*x7)/2,  -(T*x4)/2, -(T*x3)/2,         1,  (T*x1)/2, (T*x2)/2;
		  -(T*x5)/2,   (T*x4)/2,   (T*x7)/2,  (T*x2)/2, -(T*x1)/2,         1, (T*x3)/2;
		  -(T*x4)/2,  -(T*x5)/2,  -(T*x6)/2, -(T*x1)/2, -(T*x2)/2, -(T*x3)/2,        1];
    F = double(F);
    
	% (b) Perform the time update of the state estimate and estimation-error covariance as follows: 
	% P_minus_k = F*P_plus_k_1*F.' + L*Q_k*L.';
    P_minus_k = F*P_plus_k_1*F.' + Q_k;
	
    % v1=0; v2=0; v3=0; v4=0; v5=0; v6=0; v7=0; v8=0; v9=0; w_rx=0; w_ry=0; w_rz=0;
    % f1 = T*((-1/tau_rx)*x1 + w_rx) + x1;
	% f2 = T*((-1/tau_ry)*x2 + w_ry) + x2;
	% f3 = T*((-1/tau_rz)*x3 + w_rz) + x3;
	% f4 = T*(1/2)*( x1*x7 - x2*x6 + x3*x5) + x4;
	% f5 = T*(1/2)*( x1*x6 + x2*x7 - x3*x4) + x5;
	% f6 = T*(1/2)*(-x1*x5 + x2*x4 + x3*x7) + x6;
	% f7 = T*(1/2)*(-x1*x4 - x2*x5 - x3*x6) + x7;

	x_hat_minus_k = zeros(7,1);
	x_hat_minus_k(1) = T*((-1/tau_rx)*x1) + x1;
	x_hat_minus_k(2) = T*((-1/tau_ry)*x2) + x2;
	x_hat_minus_k(3) = T*((-1/tau_rz)*x3) + x3;
	x_hat_minus_k(4) = T*(1/2)*( x1*x7 - x2*x6 + x3*x5) + x4;
	x_hat_minus_k(5) = T*(1/2)*( x1*x6 + x2*x7 - x3*x4) + x5;
	x_hat_minus_k(6) = T*(1/2)*(-x1*x5 + x2*x4 + x3*x7) + x6;
	x_hat_minus_k(7) = T*(1/2)*(-x1*x4 - x2*x5 - x3*x6) + x7;

	% (c) Compute the following partial derivative matrices:
	x1 = x_hat_minus_k(1);
	x2 = x_hat_minus_k(2);
	x3 = x_hat_minus_k(3);
	x4 = x_hat_minus_k(4);
	x5 = x_hat_minus_k(5);
	x6 = x_hat_minus_k(6);
	x7 = x_hat_minus_k(7);
	u  = u_k_1;

	H = [1, 0, 0,                                                      0,                                                      0,                                                      0,                                                      0;
		 0, 1, 0,                                                      0,                                                      0,                                                      0,                                                      0;
		 0, 0, 1,                                                      0,                                                      0,                                                      0,                                                      0;
		 0, 0, 0, 4*ax_inertial*x4 + 2*ay_inertial*x5 + 2*az_inertial*x6,                    2*ay_inertial*x4 - 2*az_inertial*x7,                    2*ay_inertial*x7 + 2*az_inertial*x4, 4*ax_inertial*x7 + 2*ay_inertial*x6 - 2*az_inertial*x5;
		 0, 0, 0,                    2*ax_inertial*x5 + 2*az_inertial*x7, 2*ax_inertial*x4 + 4*ay_inertial*x5 + 2*az_inertial*x6,                    2*az_inertial*x5 - 2*ax_inertial*x7, 4*ay_inertial*x7 - 2*ax_inertial*x6 + 2*az_inertial*x4;
		 0, 0, 0,                    2*ax_inertial*x6 - 2*ay_inertial*x7,                    2*ax_inertial*x7 + 2*ay_inertial*x6, 2*ax_inertial*x4 + 2*ay_inertial*x5 + 4*az_inertial*x6, 2*ax_inertial*x5 - 2*ay_inertial*x4 + 4*az_inertial*x7;
		 0, 0, 0, 4*mx_inertial*x4 + 2*my_inertial*x5 + 2*mz_inertial*x6,                    2*my_inertial*x4 - 2*mz_inertial*x7,                    2*my_inertial*x7 + 2*mz_inertial*x4, 4*mx_inertial*x7 + 2*my_inertial*x6 - 2*mz_inertial*x5;
		 0, 0, 0,                    2*mx_inertial*x5 + 2*mz_inertial*x7, 2*mx_inertial*x4 + 4*my_inertial*x5 + 2*mz_inertial*x6,                    2*mz_inertial*x5 - 2*mx_inertial*x7, 4*my_inertial*x7 - 2*mx_inertial*x6 + 2*mz_inertial*x4;
		 0, 0, 0,                    2*mx_inertial*x6 - 2*my_inertial*x7,                    2*mx_inertial*x7 + 2*my_inertial*x6, 2*mx_inertial*x4 + 2*my_inertial*x5 + 4*mz_inertial*x6, 2*mx_inertial*x5 - 2*my_inertial*x4 + 4*mz_inertial*x7];
	 
	% M = [ 1, 0, 0, 0, 0, 0, 0, 0, 0;
	% 	    0, 1, 0, 0, 0, 0, 0, 0, 0;
	% 	    0, 0, 1, 0, 0, 0, 0, 0, 0;
	% 	    0, 0, 0, 1, 0, 0, 0, 0, 0;
	% 	    0, 0, 0, 0, 1, 0, 0, 0, 0;
	% 	    0, 0, 0, 0, 0, 1, 0, 0, 0;
	% 	    0, 0, 0, 0, 0, 0, 1, 0, 0;
	% 	    0, 0, 0, 0, 0, 0, 0, 1, 0;
	% 	    0, 0, 0, 0, 0, 0, 0, 0, 1];

	% (d) Perform the measurement update of the state estimate and estimation error covariance as follows:   
	% K = P_minus_k * H.' * inv(H*P_minus_k*H.' + M*R_k*M.');
	% note: H and M are unit matrices
	K = P_minus_k * H.' * inv(H*P_minus_k*H.' + R_k);

    % v1=0; v2=0; v3=0; v4=0; v5=0; v6=0; v7=0; v8=0; v9=0;
    
	h_k = zeros(9,1);
	h_k(1) = x1;
	h_k(2) = x2;
	h_k(3) = x3;
	h_k(4) =  ax_inertial*(x4^2 - x5^2 - x6^2 + x7^2) + ay_inertial*(2*x4*x5 + 2*x6*x7) + az_inertial*(2*x4*x6 - 2*x5*x7);
	h_k(5) = -ay_inertial*(x4^2 - x5^2 + x6^2 - x7^2) + ax_inertial*(2*x4*x5 - 2*x6*x7) + az_inertial*(2*x4*x7 + 2*x5*x6);
	h_k(6) = -az_inertial*(x4^2 + x5^2 - x6^2 - x7^2) + ax_inertial*(2*x4*x6 + 2*x5*x7) - ay_inertial*(2*x4*x7 - 2*x5*x6);
	h_k(7) =  mx_inertial*(x4^2 - x5^2 - x6^2 + x7^2) + my_inertial*(2*x4*x5 + 2*x6*x7) + mz_inertial*(2*x4*x6 - 2*x5*x7);
	h_k(8) = -my_inertial*(x4^2 - x5^2 + x6^2 - x7^2) + mx_inertial*(2*x4*x5 - 2*x6*x7) + mz_inertial*(2*x4*x7 + 2*x5*x6);
	h_k(9) = -mz_inertial*(x4^2 + x5^2 - x6^2 - x7^2) + mx_inertial*(2*x4*x6 + 2*x5*x7) - my_inertial*(2*x4*x7 - 2*x5*x6);

	% P_plus_k = (I - K*H)*(P_minus_k)*(I - K*H)' + K*R*K';
	% note: H and M are unit matrices
	P_plus_k = (I - K*H)*(P_minus_k)*(I - K*H)' + K*R_k*K';
	x_hat_plus_k = x_hat_minus_k + K*(y_meas - h_k);
    x_hat_plus_k = double(x_hat_plus_k);
    norm = sqrt(x_hat_plus_k(4)^2 + x_hat_plus_k(5)^2 + x_hat_plus_k(6)^2 + x_hat_plus_k(7)^2);
    x_hat_plus_k(4) = x_hat_plus_k(4)/norm;
    x_hat_plus_k(5) = x_hat_plus_k(5)/norm;
    x_hat_plus_k(6) = x_hat_plus_k(6)/norm;
    x_hat_plus_k(7) = x_hat_plus_k(7)/norm;
    
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

