/*
 * File: _coder_LPF_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Nov-2019 22:59:23
 */

#ifndef _CODER_LPF_API_H
#define _CODER_LPF_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_LPF_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void LPF(real_T ax, real_T ay, real_T az, real_T gx, real_T gy, real_T gz,
                real_T mx, real_T my, real_T mz, real_T *r, real_T *p, real_T *y,
                real_T dt);
extern void LPF_api(const mxArray * const prhs[13], int32_T nlhs, const mxArray *
                    plhs[3]);
extern void LPF_atexit(void);
extern void LPF_initialize(void);
extern void LPF_terminate(void);
extern void LPF_xil_terminate(void);

#endif

/*
 * File trailer for _coder_LPF_api.h
 *
 * [EOF]
 */
