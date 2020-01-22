/*
 * File: _coder_EKF1_api.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 22-Oct-2019 00:03:12
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_EKF1_api.h"
#include "_coder_EKF1_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131467U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "EKF1",                              /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4]);
static const mxArray *b_emlrt_marshallOut(const real32_T u[16]);
static real32_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *t, const
  char_T *identifier);
static real32_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *P, const
  char_T *identifier, real32_T y[16]);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char_T *identifier, real32_T y[4]);
static const mxArray *emlrt_marshallOut(const real32_T u[4]);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[16]);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *R, const
  char_T *identifier, real32_T y[36]);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[36]);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4]);
static real32_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[16]);
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[36]);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[4]
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4])
{
  i_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const real32_T u[16]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real32_T u[16])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv1[2] = { 4, 4 };

  real32_T *pData;
  int32_T i0;
  int32_T i;
  int32_T i1;
  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv1, (int16_T)mxSINGLE_CLASS, (int16_T)mxREAL);
  pData = (real32_T *)emlrtMxGetData(m1);
  i0 = 0;
  for (i = 0; i < 4; i++) {
    i1 = i << 2;
    pData[i0] = u[i1];
    i0++;
    pData[i0] = u[1 + i1];
    i0++;
    pData[i0] = u[2 + i1];
    i0++;
    pData[i0] = u[3 + i1];
    i0++;
  }

  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *t
 *                const char_T *identifier
 * Return Type  : real32_T
 */
static real32_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *t, const
  char_T *identifier)
{
  real32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(t), &thisId);
  emlrtDestroyArray(&t);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real32_T
 */
static real32_T d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = j_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *P
 *                const char_T *identifier
 *                real32_T y[16]
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *P, const
  char_T *identifier, real32_T y[16])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  f_emlrt_marshallIn(sp, emlrtAlias(P), &thisId, y);
  emlrtDestroyArray(&P);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *x
 *                const char_T *identifier
 *                real32_T y[4]
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *x, const
  char_T *identifier, real32_T y[4])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(x), &thisId, y);
  emlrtDestroyArray(&x);
}

/*
 * Arguments    : const real32_T u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real32_T u[4])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 1, 4 };

  real32_T *pData;
  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, (int16_T)mxSINGLE_CLASS, (int16_T)mxREAL);
  pData = (real32_T *)emlrtMxGetData(m0);
  pData[0] = u[0];
  pData[1] = u[1];
  pData[2] = u[2];
  pData[3] = u[3];
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[16]
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[16])
{
  k_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *R
 *                const char_T *identifier
 *                real32_T y[36]
 * Return Type  : void
 */
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *R, const
  char_T *identifier, real32_T y[36])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  h_emlrt_marshallIn(sp, emlrtAlias(R), &thisId, y);
  emlrtDestroyArray(&R);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[36]
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[36])
{
  l_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[4]
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4])
{
  static const int32_T dims[1] = { 4 };

  emlrtCheckBuiltInR2012b(sp, (const emlrtMsgIdentifier *)msgId, src,
    "single|double", false, 1U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real32_T
 */
static real32_T j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real32_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, (const emlrtMsgIdentifier *)msgId, src,
    "single|double", false, 0U, &dims);
  emlrtImportArrayR2015b(sp, src, &ret, 4, false);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[16]
 * Return Type  : void
 */
static void k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[16])
{
  static const int32_T dims[2] = { 4, 4 };

  emlrtCheckBuiltInR2012b(sp, (const emlrtMsgIdentifier *)msgId, src,
    "single|double", false, 2U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[36]
 * Return Type  : void
 */
static void l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[36])
{
  static const int32_T dims[2] = { 6, 6 };

  emlrtCheckBuiltInR2012b(sp, (const emlrtMsgIdentifier *)msgId, src,
    "single|double", false, 2U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray * const prhs[14]
 *                int32_T nlhs
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void EKF1_api(const mxArray * const prhs[14], int32_T nlhs, const mxArray *plhs
              [2])
{
  real32_T x[4];
  real32_T t;
  real32_T P[16];
  real32_T Q[16];
  real32_T R[36];
  real32_T Ax;
  real32_T Ay;
  real32_T Az;
  real32_T Mx;
  real32_T My;
  real32_T Mz;
  real32_T Gx;
  real32_T Gy;
  real32_T Gz;
  real32_T x_k[4];
  real32_T P_plus_k[16];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "x", x);
  t = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "t");
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "P", P);
  e_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "Q", Q);
  g_emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "R", R);
  Ax = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "Ax");
  Ay = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "Ay");
  Az = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "Az");
  Mx = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "Mx");
  My = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "My");
  Mz = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "Mz");
  Gx = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "Gx");
  Gy = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "Gy");
  Gz = c_emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "Gz");

  /* Invoke the target function */
  EKF1(x, t, P, Q, R, Ax, Ay, Az, Mx, My, Mz, Gx, Gy, Gz, x_k, P_plus_k);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(x_k);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(P_plus_k);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void EKF1_atexit(void)
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
  EKF1_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void EKF1_initialize(void)
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
void EKF1_terminate(void)
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
 * File trailer for _coder_EKF1_api.c
 *
 * [EOF]
 */
