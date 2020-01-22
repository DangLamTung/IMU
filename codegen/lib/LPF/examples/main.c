/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 23-Nov-2019 22:59:23
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
#include "rt_nonfinite.h"
#include "LPF.h"
#include "main.h"
#include "LPF_terminate.h"
#include "LPF_initialize.h"

/* Function Declarations */
static double argInit_real_T(void);
static void main_LPF(void);

/* Function Definitions */

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
static void main_LPF(void)
{
  double ax_tmp;
  double az;
  double gx;
  double gy;
  double gz;
  double mx;
  double my;
  double r;
  double p;
  double y;

  /* Initialize function 'LPF' input arguments. */
  ax_tmp = argInit_real_T();
  az = argInit_real_T();
  gx = argInit_real_T();
  gy = argInit_real_T();
  gz = argInit_real_T();
  mx = argInit_real_T();
  my = argInit_real_T();

  /* Call the entry-point 'LPF'. */
  r = argInit_real_T();
  p = argInit_real_T();
  y = argInit_real_T();
  LPF(ax_tmp, ax_tmp, az, gx, gy, gz, mx, my, argInit_real_T(), &r, &p, &y,
      argInit_real_T());
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
  LPF_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_LPF();

  /* Terminate the application.
     You do not need to do this more than one time. */
  LPF_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
