/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: div_nde_s32_floor.c
 *
 * Code generated for Simulink model 'sensor_fusion'.
 *
 * Model version                  : 5.10
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Sun Apr  5 11:25:12 2026
 */

#include "div_nde_s32_floor.h"
#include <stdint.h>

int32_t div_nde_s32_floor(int32_t numerator, int32_t denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
