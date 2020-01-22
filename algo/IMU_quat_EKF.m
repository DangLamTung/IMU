%#codegen
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Applied extended Kalman filter in inertial measurement
% unit (IMU) 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [x_hat_plus_k, P_plus_k] = IMU_quat_EKF(Ax, Ay, Az, Mx, My, Mz, Gx, Gy, Gz, x_hat_plus_k_1, P_plus_k_1,...
                                                 Q_k, R_k, T, tau_rx, tau_ry, tau_rz,...
                                                 ax_inertial, ay_inertial, az_inertial,...
                                                 mx_inertial, my_inertial, mz_inertial)
    assert(isa(Ax,'double') && isa(Ay,'double') && isa(Az,'double') );
    assert(isa(Mx,'double') && isa(My,'double') && isa(Mz,'double') );
    assert(isa(Gx,'double') && isa(Gy,'double') && isa(Gz,'double') );
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

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Algorithms' parameters
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % Initial values
%     x_hat_plus_k_1 = [0                       % gyrox
%                       0                       % gyroy
%                       0                       % gyroz
%                       0                       % qa
%                       0                       % qb
%                       0                       % qc
%                       1];                     % qd
%     P_plus_k_1 = [100  0   0   0   0   0   0 ;
%                    0  100  0   0   0   0   0 ;
%                    0   0  100  0   0   0   0 ;
%                    0   0   0  100  0   0   0 ; 
%                    0   0   0   0  100  0   0 ;
%                    0   0   0   0   0  100  0 ;
%                    0   0   0   0   0   0  100];

    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    % 
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    % Kalman
    y_meas = [Gx; Gy; Gz; Ax; Ay; Az; Mx; My; Mz];
    [x_hat_plus_k, P_plus_k] = IMU_EKF(0, y_meas, x_hat_plus_k_1, P_plus_k_1,...
                                       Q_k, R_k, T, tau_rx, tau_ry, tau_rz,...
                                       ax_inertial, ay_inertial, az_inertial,...
                                       mx_inertial, my_inertial, mz_inertial);
   
end

 