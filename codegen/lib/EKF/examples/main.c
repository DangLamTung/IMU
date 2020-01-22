/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 24-Nov-2019 09:52:46
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
#include <string.h>
#include "EKF.h"
#include "main.h"
#include "EKF_terminate.h"
#include "EKF_initialize.h"

/* Function Declarations */
static void argInit_6x6_real_T(double result[36]);
static void argInit_7x1_real_T(double result[7]);
static void argInit_7x7_real_T(double result[49]);
static double argInit_real_T(void);
static void main_EKF(void);

/* Function Definitions */

/*
 * Arguments    : double result[36]
 * Return Type  : void
 */
static void argInit_6x6_real_T(double result[36])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 6; idx0++) {
    for (idx1 = 0; idx1 < 6; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 6 * idx1] = argInit_real_T();
    }
  }
}

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
static void main_EKF(void)
{
  double x[7];
  double t;
  double P_tmp[49];
  double P[49];
  double dv0[36];

  /* Initialize function 'EKF' input arguments. */
  /* Initialize function input argument 'x'. */
  argInit_7x1_real_T(x);
  t = argInit_real_T();

  /* Initialize function input argument 'P'. */
  argInit_7x7_real_T(P_tmp);

  /* Initialize function input argument 'Q'. */
  /* Initialize function input argument 'R'. */
  /* Call the entry-point 'EKF'. */
  memcpy(&P[0], &P_tmp[0], 49U * sizeof(double));
  argInit_6x6_real_T(dv0);
  EKF(x, t, P, P_tmp, dv0, argInit_real_T(), argInit_real_T(), argInit_real_T(),
      argInit_real_T(), argInit_real_T(), argInit_real_T(), argInit_real_T(),
      argInit_real_T(), argInit_real_T());
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
  EKF_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_EKF();

  /* Terminate the application.
     You do not need to do this more than one time. */
  EKF_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
