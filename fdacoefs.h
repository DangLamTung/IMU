/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.5 and Signal Processing Toolbox 8.1.
 * Generated on: 23-Nov-2019 22:49:27
 */

/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II, Second-Order Sections
 * Number of Sections  : 2
 * Stable              : Yes
 * Linear Phase        : No
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * /usr/local/MATLAB/R2018b/extern/include/tmwtypes.h 
 */
#define MWSPT_NSEC 5
const int NL[MWSPT_NSEC] = { 1,3,1,3,1 };
const real64_T NUM[MWSPT_NSEC][3] = {
  {
   0.001874153394435,                 0,                 0 
  },
  {
                   1,                 2,                 1 
  },
  {
   0.001791657286246,                 0,                 0 
  },
  {
                   1,                 2,                 1 
  },
  {
                   1,                 0,                 0 
  }
};
const int DL[MWSPT_NSEC] = { 1,3,1,3,1 };
const real64_T DEN[MWSPT_NSEC][3] = {
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.927386516171,   0.9348831297486 
  },
  {
                   1,                 0,                 0 
  },
  {
                   1,   -1.842547203107,   0.8497138322524 
  },
  {
                   1,                 0,                 0 
  }
};
