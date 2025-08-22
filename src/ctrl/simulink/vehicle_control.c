/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Fri Aug 22 19:15:03 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "vehicle_control.h"
#include <stdint.h>
#include "simulink_import.h"

/* Model step function */
void vehicle_control_step(vehicle_control_RT_MODEL *const rtM,
  vehicle_control_ExtU *rtU, vehicle_control_ExtY *rtY)
{
  float rtb_Gain1;

  /* Gain: '<Root>/Gain1' incorporates:
   *  Gain: '<Root>/Gain'
   */
  rtb_Gain1 = 0.01F * rtU->cockpit.accel * 100.0F;

  /* Gain: '<Root>/Gain2' */
  rtY->torq.torque.rl = (float)torq_rl / 100.0F * rtb_Gain1;

  /* Gain: '<Root>/Gain3' */
  rtY->torq.torque.rr = (float)torq_rr / 100.0F * rtb_Gain1;

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
