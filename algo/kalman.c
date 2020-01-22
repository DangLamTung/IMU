#define T               0.002
#define tau_rx          0.01
#define tau_ry          0.01
#define tau_rz          0.01

#define ax_inertial     0
#define ay_inertial     0
#define az_inertial     9.81
#define mx_inertial     -0.171683422108236
#define my_inertial     0.035035590090210
#define mz_inertial     0.030100000000000

const double Q_k[49] = {0.0000374,  0,         0,          0,  0,  0,  0,
                        0,          0.000354,  0,          0,  0,  0,  0,
                        0,          0,         0.0000153,  0,  0,  0,  0,
                        0,          0,         0,          0,  0,  0,  0,
                        0,          0,         0,          0,  0,  0,  0,
                        0,          0,         0,          0,  0,  0,  0,
                        0,          0,         0,          0,  0,  0,  0};
       
const double R_k[81] = {0.0000374,  0,         0,          0,          0,          0,          0,           0,           0,
                        0,          0.000354,  0,          0,          0,          0,          0,           0,           0,
                        0,          0,         0.0000153,  0,          0,          0,          0,           0,           0,
                        0,          0,         0,          0.0000178,  0,          0,          0,           0,           0,
                        0,          0,         0,          0,          0.0000134,  0,          0,           0,           0,
                        0,          0,         0,          0,          0,          0.0000192,  0,           0,           0,
                        0,          0,         0,          0,          0,          0,          0.00000372,  0,           0,
                        0,          0,         0,          0,          0,          0,          0,           0.00000231,  0,
                        0,          0,         0,          0,          0,          0,          0,           0,           0.00000155};


void IMU_quat_EKF(double Ax, double Ay, double Az,
                  double Mx, double My, double Mz,
                  double Gx, double Gy, double Gz,
                  const double x_hat_plus_k_1[7], const double P_plus_k_1[49],
                  double x_hat_plus_k[7], double P_plus_k[49])
{

double * F = (double *)malloc(49 * sizeof(double));
  double* x_hat_minus_k = (double *)malloc(7 * sizeof(double));
  double b_norm;
  double F_tmp;
  double b_F_tmp;
  double c_F_tmp;
  double d_F_tmp;
  double e_F_tmp;
  double f_F_tmp;
  double g_F_tmp;
  double F_tmp_tmp;
  double h_F_tmp;
  double i_F_tmp;
F[0] = 1.0 - T / tau_rx;
  F[7] = 0.0;
  F[14] = 0.0;
  F[21] = 0.0;
  F[28] = 0.0;
  F[35] = 0.0;
  F[42] = 0.0;
  F[1] = 0.0;
  F[8] = 1.0 - T / tau_ry;
  F[15] = 0.0;
  F[22] = 0.0;
  F[29] = 0.0;
  F[36] = 0.0;
  F[43] = 0.0;
  F[2] = 0.0;
  F[9] = 0.0;
  F[16] = 1.0 - T / tau_rz;
  F[23] = 0.0;
  F[30] = 0.0;
  F[37] = 0.0;
  F[44] = 0.0;
  b_norm = T * x_hat_plus_k_1[6] *0.5;
  F[3] = b_norm;
  F_tmp = T * x_hat_plus_k_1[5];
  b_F_tmp = -F_tmp *0.5;
  F[10] = b_F_tmp;
  c_F_tmp = T * x_hat_plus_k_1[4];
  F[17] = c_F_tmp *0.5;
  F[24] = 1.0;
  d_F_tmp = T * x_hat_plus_k_1[2];
  e_F_tmp = d_F_tmp *0.5;
  F[31] = e_F_tmp;
  f_F_tmp = T * x_hat_plus_k_1[1];
  g_F_tmp = -f_F_tmp *0.5;
  F[38] = g_F_tmp;
  F_tmp_tmp = T * x_hat_plus_k_1[0];
  h_F_tmp = F_tmp_tmp *0.5;
  F[45] = h_F_tmp;
  F[4] = F_tmp *0.5;
  F[11] = b_norm;
  F_tmp = T * x_hat_plus_k_1[3];
  i_F_tmp = -F_tmp *0.5;
  F[18] = i_F_tmp;
  d_F_tmp = -d_F_tmp *0.5;
  F[25] = d_F_tmp;
  F[32] = 1.0;
  F[39] = h_F_tmp;
  f_F_tmp /= 2.0;
  F[46] = f_F_tmp;
  c_F_tmp = -c_F_tmp *0.5;
  F[5] = c_F_tmp;
  F[12] = F_tmp *0.5;
  F[19] = b_norm;
  F[26] = f_F_tmp;
  b_norm = -F_tmp_tmp *0.5;
  F[33] = b_norm;
  F[40] = 1.0;
  F[47] = e_F_tmp;
  F[6] = i_F_tmp;
  F[13] = c_F_tmp;
  F[20] = b_F_tmp;
  F[27] = b_norm;
  F[34] = g_F_tmp;
  F[41] = d_F_tmp;
  F[48] = 1.0;
//////////////////////////////
  x_hat_minus_k[0] = T * (-1.0 / tau_rx * x_hat_plus_k_1[0]) + x_hat_plus_k_1[0];
  x_hat_minus_k[1] = T * (-1.0 / tau_ry * x_hat_plus_k_1[1]) + x_hat_plus_k_1[1];
  x_hat_minus_k[2] = T * (-1.0 / tau_rz * x_hat_plus_k_1[2]) + x_hat_plus_k_1[2];
  x_hat_minus_k[3] = T * 0.5 * ((x_hat_plus_k_1[0] * x_hat_plus_k_1[6] -
    x_hat_plus_k_1[1] * x_hat_plus_k_1[5]) + x_hat_plus_k_1[2] * x_hat_plus_k_1
    [4]) + x_hat_plus_k_1[3];
  x_hat_minus_k[4] = T * 0.5 * ((x_hat_plus_k_1[0] * x_hat_plus_k_1[5] +
    x_hat_plus_k_1[1] * x_hat_plus_k_1[6]) - x_hat_plus_k_1[2] * x_hat_plus_k_1
    [3]) + x_hat_plus_k_1[4];
  x_hat_minus_k[5] = T * 0.5 * ((-x_hat_plus_k_1[0] * x_hat_plus_k_1[4] +
    x_hat_plus_k_1[1] * x_hat_plus_k_1[3]) + x_hat_plus_k_1[2] * x_hat_plus_k_1
    [6]) + x_hat_plus_k_1[5];
  x_hat_minus_k[6] = T * 0.5 * ((-x_hat_plus_k_1[0] * x_hat_plus_k_1[3] -
    x_hat_plus_k_1[1] * x_hat_plus_k_1[4]) - x_hat_plus_k_1[2] * x_hat_plus_k_1
    [5]) + x_hat_plus_k_1[6];
  ////////////////////////////////////////
  


}