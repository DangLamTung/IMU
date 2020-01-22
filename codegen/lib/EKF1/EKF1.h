//
// File: EKF1.h
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 22-Oct-2019 00:03:12
//
#ifndef EKF1_H
#define EKF1_H

// Include Files
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "EKF1_types.h"

// Function Declarations
extern void EKF1(float x[4], float t, float P[16], const float Q[16], const
                 float R[36], float Ax, float Ay, float Az, float Mx, float My,
                 float Mz, float Gx, float Gy, float Gz, float x_k[4], float
                 P_plus_k[16]);

#endif

//
// File trailer for EKF1.h
//
// [EOF]
//
