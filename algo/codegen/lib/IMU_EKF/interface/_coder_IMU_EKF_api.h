/*
 * File: _coder_IMU_EKF_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 06-Sep-2019 10:24:15
 */

#ifndef _CODER_IMU_EKF_API_H
#define _CODER_IMU_EKF_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_IMU_EKF_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void IMU_EKF(real_T u_k_1, real_T y_meas[9], real_T x_hat_plus_k_1[7],
                    real_T P_plus_k_1[49], real_T Q_k[49], real_T R_k[81],
                    real_T T, real_T tau_rx, real_T tau_ry, real_T tau_rz,
                    real_T ax_inertial, real_T ay_inertial, real_T az_inertial,
                    real_T mx_inertial, real_T my_inertial, real_T mz_inertial,
                    real_T x_hat_plus_k[7], real_T P_plus_k[49]);
extern void IMU_EKF_api(const mxArray * const prhs[16], int32_T nlhs, const
  mxArray *plhs[2]);
extern void IMU_EKF_atexit(void);
extern void IMU_EKF_initialize(void);
extern void IMU_EKF_terminate(void);
extern void IMU_EKF_xil_terminate(void);

#endif

/*
 * File trailer for _coder_IMU_EKF_api.h
 *
 * [EOF]
 */
