/*
 * File: LPF.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Nov-2019 22:59:23
 */

/* Include Files */
#include <math.h>
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "LPF.h"
#include "sosfilt.h"

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * Arguments    : double ax
 *                double ay
 *                double az
 *                double gx
 *                double gy
 *                double gz
 *                double mx
 *                double my
 *                double mz
 *                double *r
 *                double *p
 *                double *y
 *                double dt
 * Return Type  : void
 */
void LPF(double ax, double ay, double az, double gx, double gy, double gz,
         double mx, double my, double mz, double *r, double *p, double *y,
         double dt)
{
  int i0;
  double y2;
  double dv0[6];
  static const double dv1[6] = { 1.0, 1.3085, 1.0, 1.0, -1.9382, 0.94 };

  double y3;
  (void)mz;
  for (i0 = 0; i0 < 6; i0++) {
    dv0[i0] = dv1[i0];
  }

  y2 = sosfilt(dv0, ay) / 10.0;
  for (i0 = 0; i0 < 6; i0++) {
    dv0[i0] = dv1[i0];
  }

  y3 = sosfilt(dv0, az) / 10.0;
  for (i0 = 0; i0 < 6; i0++) {
    dv0[i0] = dv1[i0];
  }

  *r = 0.9 * (*r + dt * gx) + 0.099999999999999978 * (atan(-(sosfilt(dv0, ax) /
    10.0) / sqrt(y2 * y2 + y3 * y3)) * 180.0 / 3.1415926535897931);
  *p = 0.9 * (*p + dt * gy) + 0.099999999999999978 * (atan(y2 / y3) * 180.0 /
    3.1415926535897931);
  *y = 0.9 * (*y + dt * gz) + 0.099999999999999978 * (rt_atan2d_snf(my, mx) *
    180.0 / 3.1415926535897931);
}

/*
 * File trailer for LPF.c
 *
 * [EOF]
 */
