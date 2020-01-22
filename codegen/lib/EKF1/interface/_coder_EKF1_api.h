/*
 * File: _coder_EKF1_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 22-Oct-2019 00:03:12
 */

#ifndef _CODER_EKF1_API_H
#define _CODER_EKF1_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_EKF1_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void EKF1(real32_T x[4], real32_T t, real32_T P[16], real32_T Q[16],
                 real32_T R[36], real32_T Ax, real32_T Ay, real32_T Az, real32_T
                 Mx, real32_T My, real32_T Mz, real32_T Gx, real32_T Gy,
                 real32_T Gz, real32_T x_k[4], real32_T P_plus_k[16]);
extern void EKF1_api(const mxArray * const prhs[14], int32_T nlhs, const mxArray
                     *plhs[2]);
extern void EKF1_atexit(void);
extern void EKF1_initialize(void);
extern void EKF1_terminate(void);
extern void EKF1_xil_terminate(void);

#endif

/*
 * File trailer for _coder_EKF1_api.h
 *
 * [EOF]
 */
