/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensor_fusion.c
 *
 * Code generated for Simulink model 'sensor_fusion'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Fri Aug 22 15:57:37 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "sensor_fusion.h"

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
