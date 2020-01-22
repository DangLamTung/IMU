/*
 * File: sosfilt.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Nov-2019 22:59:23
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "LPF.h"
#include "sosfilt.h"

/* Function Definitions */

/*
 * Arguments    : double SOS[6]
 *                double x
 * Return Type  : double
 */
double sosfilt(double SOS[6], double x)
{
  if (SOS[3] != 1.0) {
    SOS[0] /= SOS[3];
  }

  return x * SOS[0];
}

/*
 * File trailer for sosfilt.c
 *
 * [EOF]
 */
