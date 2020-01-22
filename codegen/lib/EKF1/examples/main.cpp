//
// File: main.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 22-Oct-2019 00:03:12
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include <string.h>
#include "EKF1.h"
#include "main.h"
#include "EKF1_terminate.h"
#include "EKF1_initialize.h"

// Function Declarations
static void argInit_4x1_real32_T(float result[4]);
static void argInit_4x4_real32_T(float result[16]);
static void argInit_6x6_real32_T(float result[36]);
static float argInit_real32_T();
static void main_EKF1();

// Function Definitions

//
// Arguments    : float result[4]
// Return Type  : void
//
static void argInit_4x1_real32_T(float result[4])
{
  float result_tmp;

  // Loop over the array to initialize each element.
  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result_tmp = argInit_real32_T();
  result[0] = result_tmp;

  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result[1] = result_tmp;

  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result[2] = argInit_real32_T();

  // Set the value of the array element.
  // Change this value to the value that the application requires.
  result[3] = argInit_real32_T();
}

//
// Arguments    : float result[16]
// Return Type  : void
//
static void argInit_4x4_real32_T(float result[16])
{
  int idx0;
  float result_tmp;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 4; idx0++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result_tmp = argInit_real32_T();
    result[idx0] = result_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 4] = result_tmp;

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 8] = argInit_real32_T();

    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx0 + 12] = argInit_real32_T();
  }
}

//
// Arguments    : float result[36]
// Return Type  : void
//
static void argInit_6x6_real32_T(float result[36])
{
  int idx0;
  int idx1;

  // Loop over the array to initialize each element.
  for (idx0 = 0; idx0 < 6; idx0++) {
    for (idx1 = 0; idx1 < 6; idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + 6 * idx1] = argInit_real32_T();
    }
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_EKF1()
{
  float x[4];
  float t;
  float P_tmp[16];
  float Q[16];
  float fv1[36];
  float x_k[4];
  float P_plus_k[16];

  // Initialize function 'EKF1' input arguments.
  // Initialize function input argument 'x'.
  argInit_4x1_real32_T(x);
  t = argInit_real32_T();

  // Initialize function input argument 'P'.
  argInit_4x4_real32_T(P_tmp);

  // Initialize function input argument 'Q'.
  memcpy(&Q[0], &P_tmp[0], sizeof(float) << 4);

  // Initialize function input argument 'R'.
  // Call the entry-point 'EKF1'.
  argInit_6x6_real32_T(fv1);
  EKF1(x, t, P_tmp, Q, fv1, argInit_real32_T(), argInit_real32_T(),
       argInit_real32_T(), argInit_real32_T(), argInit_real32_T(),
       argInit_real32_T(), argInit_real32_T(), argInit_real32_T(),
       argInit_real32_T(), x_k, P_plus_k);
}

//
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
  // Initialize the application.
  // You do not need to do this more than one time.
  EKF1_initialize();

  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_EKF1();

  // Terminate the application.
  // You do not need to do this more than one time.
  EKF1_terminate();
  return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
