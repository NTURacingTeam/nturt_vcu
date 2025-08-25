/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensor_fusion.h
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

#ifndef sensor_fusion_h_
#define sensor_fusion_h_
#ifndef sensor_fusion_COMMON_INCLUDES_
#define sensor_fusion_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* sensor_fusion_COMMON_INCLUDES_ */

#include "simulink_import.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct sensor_fusion_tag_RTM sensor_fusion_RT_MODEL;

/* External inputs (root inport signals with default storage) */
typedef struct {
  msg_sensor_cockpit cockpit;          /* '<Root>/cockpit' */
  msg_sensor_wheel wheel;              /* '<Root>/wheel' */
  msg_sensor_imu imu;                  /* '<Root>/imu' */
  msg_sensor_gps gps;                  /* '<Root>/gps' */
} sensor_fusion_ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  msg_ctrl_vehicle_state vehicle_state;/* '<Root>/vehicle_state' */
} sensor_fusion_ExtY;

/* Real-time Model Data Structure */
struct sensor_fusion_tag_RTM {
  const char * volatile errorStatus;
};

/* Model entry point functions */
extern void sensor_fusion_initialize(sensor_fusion_RT_MODEL *const rtM);
extern void sensor_fusion_step(sensor_fusion_RT_MODEL *const rtM,
  sensor_fusion_ExtU *rtU, sensor_fusion_ExtY *rtY);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'sensor_fusion'
 * '<S1>'   : 'sensor_fusion/Angular Velocity Conversion'
 */
#endif                                 /* sensor_fusion_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
