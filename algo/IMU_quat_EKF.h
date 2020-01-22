/*
 * File: IMU_quat_EKF.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 05-Sep-2019 11:32:23
 */

#ifndef IMU_QUAT_EKF_H
#define IMU_QUAT_EKF_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "IMU_quat_EKF_types.h"

/* Function Declarations */
extern void IMU_quat_EKF(double Ax, double Ay, double Az,
						 double Mx, double My, double Mz,
						 double Gx, double Gy, double Gz,
						 const double x_hat_plus_k_1[7], const double P_plus_k_1[49],
						 double x_hat_plus_k[7], double P_plus_k[49]);

#endif

/*
 * File trailer for IMU_quat_EKF.h
 *
 * [EOF]
 */
