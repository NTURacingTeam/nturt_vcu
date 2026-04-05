/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: rt_hypotd_snf.c
 *
 * Code generated for Simulink model 'sensor_fusion'.
 *
 * Model version                  : 5.10
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Sun Apr  5 11:25:12 2026
 */

#include "rt_hypotd_snf.h"
#include <math.h>
#include "rt_nonfinite.h"

double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double b;
  double y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = sqrt(b * b + 1.0) * a;
  } else if (rtIsNaN(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
