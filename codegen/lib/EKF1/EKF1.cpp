//
// File: EKF1.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 22-Oct-2019 00:03:12
//

// Include Files
#include <cmath>
#include "EKF1.h"

// Function Definitions

//
// Arguments    : float x[4]
//                float t
//                float P[16]
//                const float Q[16]
//                const float R[36]
//                float Ax
//                float Ay
//                float Az
//                float Mx
//                float My
//                float Mz
//                float Gx
//                float Gy
//                float Gz
//                float x_k[4]
//                float P_plus_k[16]
// Return Type  : void
//
void EKF1(float x[4], float t, float P[16], const float Q[16], const float R[36],
          float Ax, float Ay, float Az, float Mx, float My, float Mz, float Gx,
          float Gy, float Gz, float x_k[4], float P_plus_k[16])
{
  float mag_norm;
  float smax;
  float H_full[24];
  float fv0[12];
  float s;
  float f0;
  float f1;
  int i0;
  float a[4];
  static const signed char b_a[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 1 };

  int k;
  int jy;
  int iy;
  float c_a[16];
  float fcnOutput_tmp[24];
  int j;
  int K_full_tmp;
  int jp1j;
  float K_full[24];
  int jj;
  float b_H_full[24];
  signed char ipiv[6];
  float c[36];
  int ix;
  int jA;
  float b_Ax[6];

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //  Extended Kalman filter function
  //  Input u_k_1: prior control signal
  //  Input y_meas: measurement data (gyroscope,
  //                accelerometer, magnetometer)
  //  Input x_hat_plus_k_1: prior estimation
  //  Input P_plus_k_1: prior covariance of estimation
  //                    error
  //  Output x_hat_plus_k: posteriori estimation
  //  Output P_plus_k: posteriori covariance of estimation
  //                   error
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  mag_norm = std::sqrt((Mx * Mx + My * My) + Mz * Mz);
  smax = -2.0F * -x[2];
  H_full[0] = smax;
  H_full[6] = -2.0F * x[3];
  H_full[12] = -2.0F * -x[0];
  H_full[18] = -2.0F * x[1];
  H_full[1] = -2.0F * x[1];
  H_full[7] = -2.0F * x[0];
  H_full[13] = -2.0F * x[3];
  H_full[19] = -2.0F * x[2];
  H_full[2] = -2.0F * x[0];
  H_full[8] = -2.0F * -x[1];
  H_full[14] = smax;
  H_full[20] = -2.0F * x[3];
  H_full[3] = 2.0F * x[3];
  H_full[9] = 2.0F * x[2];
  H_full[15] = 2.0F * x[1];
  H_full[21] = 2.0F * x[0];
  H_full[4] = 2.0F * x[0];
  smax = 2.0F * -x[1];
  H_full[10] = smax;
  H_full[16] = 2.0F * x[2];
  H_full[22] = 2.0F * -x[3];
  H_full[5] = smax;
  H_full[11] = 2.0F * -x[0];
  H_full[17] = 2.0F * x[3];
  H_full[23] = 2.0F * x[2];

  // predict route
  smax = -x[1] * 0.5F * t;
  fv0[0] = smax;
  s = -x[2] * 0.5F * t;
  fv0[4] = s;
  f0 = -x[3] * 0.5F * t;
  fv0[8] = f0;
  f1 = x[0] * 0.5F * t;
  fv0[1] = f1;
  fv0[5] = f0;
  fv0[9] = x[2] * 0.5F * t;
  fv0[2] = x[3] * 0.5F * t;
  fv0[6] = f1;
  fv0[10] = smax;
  fv0[3] = s;
  fv0[7] = x[1] * 0.5F * t;
  fv0[11] = f1;
  for (i0 = 0; i0 < 4; i0++) {
    a[i0] = 0.0F;
    a[i0] = (((float)b_a[i0] * x[0] + (float)b_a[i0 + 4] * x[1]) + (float)b_a[i0
             + 8] * x[2]) + (float)b_a[i0 + 12] * x[3];
  }

  for (i0 = 0; i0 < 4; i0++) {
    x[i0] = 0.0F;
    smax = (fv0[i0] * Gx + fv0[i0 + 4] * Gy) + fv0[i0 + 8] * Gz;
    x[i0] = smax;
    x[i0] = a[i0] + smax;
    for (k = 0; k < 4; k++) {
      iy = k << 2;
      jy = i0 + iy;
      c_a[jy] = 0.0F;
      c_a[jy] = (((float)b_a[i0] * P[iy] + (float)b_a[i0 + 4] * P[1 + iy]) +
                 (float)b_a[i0 + 8] * P[2 + iy]) + (float)b_a[i0 + 12] * P[3 +
        iy];
    }
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (k = 0; k < 4; k++) {
      jy = k << 2;
      iy = i0 + jy;
      P[iy] = (((c_a[i0] * (float)b_a[jy] + c_a[i0 + 4] * (float)b_a[1 + jy]) +
                c_a[i0 + 8] * (float)b_a[2 + jy]) + c_a[i0 + 12] * (float)b_a[3
               + jy]) + Q[iy];
    }
  }

  //  % %quaternion rotation matrix
  //  %
  //      K = P*transpose(H)/(H*P*transpose(H) + R);
  for (i0 = 0; i0 < 6; i0++) {
    iy = i0 << 2;
    fcnOutput_tmp[iy] = H_full[i0];
    fcnOutput_tmp[1 + iy] = H_full[i0 + 6];
    fcnOutput_tmp[2 + iy] = H_full[i0 + 12];
    fcnOutput_tmp[3 + iy] = H_full[i0 + 18];
  }

  for (i0 = 0; i0 < 4; i0++) {
    for (k = 0; k < 6; k++) {
      K_full_tmp = k << 2;
      jp1j = i0 + K_full_tmp;
      K_full[jp1j] = 0.0F;
      K_full[jp1j] = ((P[i0] * fcnOutput_tmp[K_full_tmp] + P[i0 + 4] *
                       fcnOutput_tmp[1 + K_full_tmp]) + P[i0 + 8] *
                      fcnOutput_tmp[2 + K_full_tmp]) + P[i0 + 12] *
        fcnOutput_tmp[3 + K_full_tmp];
    }
  }

  for (i0 = 0; i0 < 6; i0++) {
    for (k = 0; k < 4; k++) {
      iy = i0 + 6 * k;
      b_H_full[iy] = 0.0F;
      jy = k << 2;
      b_H_full[iy] = ((H_full[i0] * P[jy] + H_full[i0 + 6] * P[1 + jy]) +
                      H_full[i0 + 12] * P[2 + jy]) + H_full[i0 + 18] * P[3 + jy];
    }

    for (k = 0; k < 6; k++) {
      jy = k << 2;
      iy = i0 + 6 * k;
      c[iy] = (((b_H_full[i0] * fcnOutput_tmp[jy] + b_H_full[i0 + 6] *
                 fcnOutput_tmp[1 + jy]) + b_H_full[i0 + 12] * fcnOutput_tmp[2 +
                jy]) + b_H_full[i0 + 18] * fcnOutput_tmp[3 + jy]) + R[iy];
    }

    ipiv[i0] = (signed char)(1 + i0);
  }

  for (j = 0; j < 5; j++) {
    K_full_tmp = j * 7;
    jj = j * 7;
    jp1j = K_full_tmp + 2;
    iy = 6 - j;
    jy = 0;
    ix = K_full_tmp;
    smax = std::abs(c[K_full_tmp]);
    for (k = 2; k <= iy; k++) {
      ix++;
      s = std::abs(c[ix]);
      if (s > smax) {
        jy = k - 1;
        smax = s;
      }
    }

    if (c[jj + jy] != 0.0F) {
      if (jy != 0) {
        iy = j + jy;
        ipiv[j] = (signed char)(iy + 1);
        ix = j;
        for (k = 0; k < 6; k++) {
          smax = c[ix];
          c[ix] = c[iy];
          c[iy] = smax;
          ix += 6;
          iy += 6;
        }
      }

      i0 = (jj - j) + 6;
      for (iy = jp1j; iy <= i0; iy++) {
        c[iy - 1] /= c[jj];
      }
    }

    iy = 4 - j;
    jy = K_full_tmp + 6;
    jA = jj;
    for (K_full_tmp = 0; K_full_tmp <= iy; K_full_tmp++) {
      smax = c[jy];
      if (c[jy] != 0.0F) {
        ix = jj + 1;
        i0 = jA + 8;
        k = (jA - j) + 12;
        for (jp1j = i0; jp1j <= k; jp1j++) {
          c[jp1j - 1] += c[ix] * -smax;
          ix++;
        }
      }

      jy += 6;
      jA += 6;
    }
  }

  for (j = 0; j < 6; j++) {
    iy = (j << 2) - 1;
    jy = 6 * j;
    for (k = 0; k < j; k++) {
      jA = k << 2;
      smax = c[k + jy];
      if (smax != 0.0F) {
        K_full[1 + iy] -= smax * K_full[jA];
        K_full[2 + iy] -= smax * K_full[jA + 1];
        K_full[3 + iy] -= smax * K_full[jA + 2];
        K_full[4 + iy] -= smax * K_full[jA + 3];
      }
    }

    smax = 1.0F / c[j + jy];
    K_full[1 + iy] *= smax;
    K_full[2 + iy] *= smax;
    K_full[3 + iy] *= smax;
    K_full[4 + iy] *= smax;
  }

  for (j = 5; j >= 0; j--) {
    iy = (j << 2) - 1;
    jy = 6 * j - 1;
    i0 = j + 2;
    for (k = i0; k < 7; k++) {
      jA = (k - 1) << 2;
      smax = c[k + jy];
      if (smax != 0.0F) {
        K_full[1 + iy] -= smax * K_full[jA];
        K_full[2 + iy] -= smax * K_full[jA + 1];
        K_full[3 + iy] -= smax * K_full[jA + 2];
        K_full[4 + iy] -= smax * K_full[jA + 3];
      }
    }
  }

  for (iy = 4; iy >= 0; iy--) {
    if (ipiv[iy] != iy + 1) {
      jy = iy << 2;
      smax = K_full[jy];
      K_full_tmp = (ipiv[iy] - 1) << 2;
      K_full[jy] = K_full[K_full_tmp];
      K_full[K_full_tmp] = smax;
      jA = 1 + jy;
      smax = K_full[jA];
      jp1j = 1 + K_full_tmp;
      K_full[jA] = K_full[jp1j];
      K_full[jp1j] = smax;
      jA = 2 + jy;
      smax = K_full[jA];
      jp1j = 2 + K_full_tmp;
      K_full[jA] = K_full[jp1j];
      K_full[jp1j] = smax;
      jy += 3;
      smax = K_full[jy];
      K_full_tmp += 3;
      K_full[jy] = K_full[K_full_tmp];
      K_full[K_full_tmp] = smax;
    }
  }

  //        y;
  //      s = (transpose(y) - H*x);
  b_Ax[0] = Ax;
  b_Ax[1] = Ay;
  b_Ax[2] = Az;
  b_Ax[3] = Mx / mag_norm;
  b_Ax[4] = My / mag_norm;
  b_Ax[5] = Mz / mag_norm;
  for (i0 = 0; i0 < 6; i0++) {
    b_Ax[i0] -= ((H_full[i0] * x[0] + H_full[i0 + 6] * x[1]) + H_full[i0 + 12] *
                 x[2]) + H_full[i0 + 18] * x[3];
  }

  for (i0 = 0; i0 < 4; i0++) {
    smax = 0.0F;
    for (k = 0; k < 6; k++) {
      smax += K_full[i0 + (k << 2)] * b_Ax[k];
    }

    for (k = 0; k < 4; k++) {
      s = 0.0F;
      for (jy = 0; jy < 6; jy++) {
        s += K_full[i0 + (jy << 2)] * H_full[jy + 6 * k];
      }

      iy = i0 + (k << 2);
      c_a[iy] = (float)b_a[iy] - s;
    }

    for (k = 0; k < 4; k++) {
      iy = k << 2;
      jy = i0 + iy;
      P_plus_k[jy] = 0.0F;
      P_plus_k[jy] = ((c_a[i0] * P[iy] + c_a[i0 + 4] * P[1 + iy]) + c_a[i0 + 8] *
                      P[2 + iy]) + c_a[i0 + 12] * P[3 + iy];
    }

    x[i0] += smax;
  }

  smax = std::sqrt(((x[0] * x[0] + x[1] * x[1]) + x[2] * x[2]) + x[3] * x[3]);
  x_k[0] = x[0] / smax;
  x_k[1] = x[1] / smax;
  x_k[2] = x[2] / smax;
  x_k[3] = x[3] / smax;
}

//
// File trailer for EKF1.cpp
//
// [EOF]
//
