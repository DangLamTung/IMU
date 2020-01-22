/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 06-Sep-2019 10:24:15
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "IMU_EKF.h"
#include "main.h"
#include "IMU_EKF_terminate.h"
#include "IMU_EKF_initialize.h"

/* Function Declarations */
static void argInit_7x1_real_T(double result[7]);
static void argInit_7x7_real_T(double result[49]);
static void argInit_9x1_real_T(double result[9]);
static void argInit_9x9_real_T(double result[81]);
static double argInit_real_T(void);
static void main_IMU_EKF(void);

/* Function Definitions */

/*
 * Arguments    : double result[7]
 * Return Type  : void
 */
static void argInit_7x1_real_T(double result[7])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 7; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[49]
 * Return Type  : void
 */
static void argInit_7x7_real_T(double result[49])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 7; idx0++) {
    for (idx1 = 0; idx1 < 7; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 7 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : double result[9]
 * Return Type  : void
 */
static void argInit_9x1_real_T(double result[9])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 9; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[81]
 * Return Type  : void
 */
static void argInit_9x9_real_T(double result[81])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 9; idx0++) {
    for (idx1 = 0; idx1 < 9; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 9 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_IMU_EKF(void)
{
  double u_k_1;
  double y_meas[9];
  double x_hat_plus_k_1[7];
  double P_plus_k_1_tmp[49];
  double dv1[81];
  double x_hat_plus_k[7];
  double P_plus_k[49];

  /* Initialize function 'IMU_EKF' input arguments. */
  u_k_1 = argInit_real_T();

  /* Initialize function input argument 'y_meas'. */
  argInit_9x1_real_T(y_meas);

  /* Initialize function input argument 'x_hat_plus_k_1'. */
  argInit_7x1_real_T(x_hat_plus_k_1);

  /* Initialize function input argument 'P_plus_k_1'. */
  argInit_7x7_real_T(P_plus_k_1_tmp);

  /* Initialize function input argument 'Q_k'. */
  /* Initialize function input argument 'R_k'. */
  /* Call the entry-point 'IMU_EKF'. */
  argInit_9x9_real_T(dv1);
  IMU_EKF(u_k_1, y_meas, x_hat_plus_k_1, P_plus_k_1_tmp, P_plus_k_1_tmp, dv1,
          argInit_real_T(), argInit_real_T(), argInit_real_T(), argInit_real_T(),
          argInit_real_T(), argInit_real_T(), argInit_real_T(), argInit_real_T(),
          argInit_real_T(), argInit_real_T(), x_hat_plus_k, P_plus_k);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  IMU_EKF_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_IMU_EKF();

  /* Terminate the application.
     You do not need to do this more than one time. */
  IMU_EKF_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
