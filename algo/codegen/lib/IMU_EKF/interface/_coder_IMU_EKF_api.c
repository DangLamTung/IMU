/*
 * File: _coder_IMU_EKF_api.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 06-Sep-2019 10:24:15
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_IMU_EKF_api.h"
#include "_coder_IMU_EKF_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131467U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "IMU_EKF",                           /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *b_emlrt_marshallOut(const real_T u[49]);
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *y_meas,
  const char_T *identifier))[9];
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[9];
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *x_hat_plus_k_1, const char_T *identifier))[7];
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *u_k_1, const
  char_T *identifier);
static const mxArray *emlrt_marshallOut(const real_T u[7]);
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[7];
static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *P_plus_k_1, const char_T *identifier))[49];
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[49];
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *R_k,
  const char_T *identifier))[81];
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[81];
static real_T k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[9];
static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[7];
static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[49];
static real_T (*o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[81];

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
  y = k_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const real_T u[49]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u[49])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv2[2] = { 0, 0 };

  static const int32_T iv3[2] = { 7, 7 };

  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv2, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m1, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m1, iv3, 2);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *y_meas
 *                const char_T *identifier
 * Return Type  : real_T (*)[9]
 */
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *y_meas,
  const char_T *identifier))[9]
{
  real_T (*y)[9];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(y_meas), &thisId);
  emlrtDestroyArray(&y_meas);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[9]
 */
  static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
  const emlrtMsgIdentifier *parentId))[9]
{
  real_T (*y)[9];
  y = l_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *x_hat_plus_k_1
 *                const char_T *identifier
 * Return Type  : real_T (*)[7]
 */
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *x_hat_plus_k_1, const char_T *identifier))[7]
{
  real_T (*y)[7];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(x_hat_plus_k_1), &thisId);
  emlrtDestroyArray(&x_hat_plus_k_1);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u_k_1
 *                const char_T *identifier
 * Return Type  : real_T
 */
  static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *u_k_1,
  const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(u_k_1), &thisId);
  emlrtDestroyArray(&u_k_1);
  return y;
}

/*
 * Arguments    : const real_T u[7]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u[7])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[1] = { 0 };

  static const int32_T iv1[1] = { 7 };

  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m0, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m0, iv1, 1);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[7]
 */
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[7]
{
  real_T (*y)[7];
  y = m_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *P_plus_k_1
 *                const char_T *identifier
 * Return Type  : real_T (*)[49]
 */
  static real_T (*g_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *P_plus_k_1, const char_T *identifier))[49]
{
  real_T (*y)[49];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = h_emlrt_marshallIn(sp, emlrtAlias(P_plus_k_1), &thisId);
  emlrtDestroyArray(&P_plus_k_1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[49]
 */
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[49]
{
  real_T (*y)[49];
  y = n_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *R_k
 *                const char_T *identifier
 * Return Type  : real_T (*)[81]
 */
  static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *R_k,
  const char_T *identifier))[81]
{
  real_T (*y)[81];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = j_emlrt_marshallIn(sp, emlrtAlias(R_k), &thisId);
  emlrtDestroyArray(&R_k);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[81]
 */
static real_T (*j_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[81]
{
  real_T (*y)[81];
  y = o_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
  static real_T k_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
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
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[9]
 */
static real_T (*l_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[9]
{
  real_T (*ret)[9];
  static const int32_T dims[1] = { 9 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[9])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[7]
 */
  static real_T (*m_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[7]
{
  real_T (*ret)[7];
  static const int32_T dims[1] = { 7 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[7])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[49]
 */
static real_T (*n_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[49]
{
  real_T (*ret)[49];
  static const int32_T dims[2] = { 7, 7 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[49])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[81]
 */
  static real_T (*o_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[81]
{
  real_T (*ret)[81];
  static const int32_T dims[2] = { 9, 9 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[81])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray * const prhs[16]
 *                int32_T nlhs
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void IMU_EKF_api(const mxArray * const prhs[16], int32_T nlhs, const mxArray
                 *plhs[2])
{
  real_T (*x_hat_plus_k)[7];
  real_T (*P_plus_k)[49];
  real_T u_k_1;
  real_T (*y_meas)[9];
  real_T (*x_hat_plus_k_1)[7];
  real_T (*P_plus_k_1)[49];
  real_T (*Q_k)[49];
  real_T (*R_k)[81];
  real_T T;
  real_T tau_rx;
  real_T tau_ry;
  real_T tau_rz;
  real_T ax_inertial;
  real_T ay_inertial;
  real_T az_inertial;
  real_T mx_inertial;
  real_T my_inertial;
  real_T mz_inertial;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  x_hat_plus_k = (real_T (*)[7])mxMalloc(sizeof(real_T [7]));
  P_plus_k = (real_T (*)[49])mxMalloc(sizeof(real_T [49]));

  /* Marshall function inputs */
  u_k_1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "u_k_1");
  y_meas = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "y_meas");
  x_hat_plus_k_1 = e_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "x_hat_plus_k_1");
  P_plus_k_1 = g_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "P_plus_k_1");
  Q_k = g_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "Q_k");
  R_k = i_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "R_k");
  T = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "T");
  tau_rx = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "tau_rx");
  tau_ry = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "tau_ry");
  tau_rz = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "tau_rz");
  ax_inertial = emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "ax_inertial");
  ay_inertial = emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "ay_inertial");
  az_inertial = emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "az_inertial");
  mx_inertial = emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "mx_inertial");
  my_inertial = emlrt_marshallIn(&st, emlrtAliasP(prhs[14]), "my_inertial");
  mz_inertial = emlrt_marshallIn(&st, emlrtAliasP(prhs[15]), "mz_inertial");

  /* Invoke the target function */
  IMU_EKF(u_k_1, *y_meas, *x_hat_plus_k_1, *P_plus_k_1, *Q_k, *R_k, T, tau_rx,
          tau_ry, tau_rz, ax_inertial, ay_inertial, az_inertial, mx_inertial,
          my_inertial, mz_inertial, *x_hat_plus_k, *P_plus_k);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*x_hat_plus_k);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*P_plus_k);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void IMU_EKF_atexit(void)
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
  IMU_EKF_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void IMU_EKF_initialize(void)
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
void IMU_EKF_terminate(void)
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
 * File trailer for _coder_IMU_EKF_api.c
 *
 * [EOF]
 */
