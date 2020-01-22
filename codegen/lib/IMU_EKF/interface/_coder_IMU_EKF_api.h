/*
 * File: _coder_IMU_EKF_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 24-Nov-2019 16:29:44
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
extern void IMU_EKF(real_T x[7], real_T t, real_T P[49], real_T Q[49], real_T R
                    [9], real_T Ax, real_T Ay, real_T Az, real_T Gx, real_T Gy,
                    real_T Gz);
extern void IMU_EKF_api(const mxArray * const prhs[11], int32_T nlhs, const
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
