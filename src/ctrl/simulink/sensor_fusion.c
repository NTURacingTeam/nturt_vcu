/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensor_fusion.c
 *
 * Code generated for Simulink model 'sensor_fusion'.
 *
 * Model version                  : 5.0
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Mon Aug 25 15:26:30 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "sensor_fusion.h"

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

/* Model step function */
void sensor_fusion_step(sensor_fusion_RT_MODEL *const rtM, sensor_fusion_ExtU
  *rtU, sensor_fusion_ExtY *rtY)
{
  /* Gain: '<Root>/Gain1' incorporates:
   *  Gain: '<Root>/Gain'
   *  Sum: '<Root>/Sum'
   *  UnitConversion: '<S1>/Unit Conversion'
   */
  /* Unit Conversion - from: rpm to: rad/s
     Expression: output = (0.10472*input) + (0) */
  rtY->vehicle_state.velocity.x = (((rtU->wheel.speed.fl + rtU->wheel.speed.fr)
    + rtU->wheel.speed.rl) + rtU->wheel.speed.rr) * 0.25F * 0.104719758F *
    0.254F;

  /* BusCreator generated from: '<Root>/vehicle_state_BusCreator' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  rtY->vehicle_state.velocity.y = 0.0F;

  /* BusCreator generated from: '<Root>/vehicle_state_BusCreator' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  rtY->vehicle_state.header.timestamp_ns = 0ULL;
  UNUSED_PARAMETER(rtM);
}

/* Model initialize function */
void sensor_fusion_initialize(sensor_fusion_RT_MODEL *const rtM)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
