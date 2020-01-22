/*
 * File: _coder_LPF_api.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Nov-2019 22:59:23
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_LPF_api.h"
#include "_coder_LPF_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131467U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "LPF",                               /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *ax, const
  char_T *identifier);
static const mxArray *emlrt_marshallOut(const real_T u);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *ax
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *ax, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(ax), &thisId);
  emlrtDestroyArray(&ax);
  return y;
}

/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const mxArray * const prhs[13]
 *                int32_T nlhs
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void LPF_api(const mxArray * const prhs[13], int32_T nlhs, const mxArray *plhs[3])
{
  real_T ax;
  real_T ay;
  real_T az;
  real_T gx;
  real_T gy;
  real_T gz;
  real_T mx;
  real_T my;
  real_T mz;
  real_T r;
  real_T p;
  real_T y;
  real_T dt;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  ax = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "ax");
  ay = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "ay");
  az = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "az");
  gx = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "gx");
  gy = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "gy");
  gz = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "gz");
  mx = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "mx");
  my = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "my");
  mz = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "mz");
  r = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "r");
  p = emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "p");
  y = emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "y");
  dt = emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "dt");

  /* Invoke the target function */
  LPF(ax, ay, az, gx, gy, gz, mx, my, mz, &r, &p, &y, dt);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(r);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(p);
  }

  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(y);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void LPF_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  LPF_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void LPF_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void LPF_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_LPF_api.c
 *
 * [EOF]
 */
