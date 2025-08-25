/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Mon Aug 25 16:01:00 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "vehicle_control.h"
#include "simulink_import.h"

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
void vehicle_control_step(vehicle_control_RT_MODEL *const rtM,
  vehicle_control_ExtU *rtU, vehicle_control_ExtY *rtY)
{
  float rtb_Gain;

  /* Gain: '<Root>/Gain' */
  rtb_Gain = 0.01F * rtU->cockpit.accel;

  /* Gain: '<Root>/Gain2' */
  rtY->torq.torque.rl = torq_limit_rl * rtb_Gain;

  /* Gain: '<Root>/Gain3' */
  rtY->torq.torque.rr = torq_limit_rr * rtb_Gain;

  /* BusCreator generated from: '<Root>/torq_BusCreator' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   */
  rtY->torq.torque.fl = 0.0F;
  rtY->torq.torque.fr = 0.0F;

  /* BusCreator generated from: '<Root>/torq_BusCreator' incorporates:
   *  Constant: '<Root>/Constant'
   */
  rtY->torq.header.timestamp_ns = 0ULL;
  UNUSED_PARAMETER(rtM);
}

/* Model initialize function */
void vehicle_control_initialize(vehicle_control_RT_MODEL *const rtM)
{
  /* (no initialization code required) */
  UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
