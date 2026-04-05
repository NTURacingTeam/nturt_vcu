/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensor_fusion.h
 *
 * Code generated for Simulink model 'sensor_fusion'.
 *
 * Model version                  : 5.14
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Sun Apr  5 15:38:40 2026
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
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include <stddef.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct sensor_fusion_tag_RTM sensor_fusion_RT_MODEL;

#ifndef struct_tag_TnSw2MAzLuDBp6VSQ4Cx9
#define struct_tag_TnSw2MAzLuDBp6VSQ4Cx9

struct tag_TnSw2MAzLuDBp6VSQ4Cx9
{
  int32_t isInitialized;
};

#endif                                 /* struct_tag_TnSw2MAzLuDBp6VSQ4Cx9 */

#ifndef typedef_matlabshared_tracking_internal_
#define typedef_matlabshared_tracking_internal_

typedef struct tag_TnSw2MAzLuDBp6VSQ4Cx9 matlabshared_tracking_internal_;

#endif                             /* typedef_matlabshared_tracking_internal_ */

#ifndef struct_tag_RZEbOWb6wzemkvwSIeSZmH
#define struct_tag_RZEbOWb6wzemkvwSIeSZmH

struct tag_RZEbOWb6wzemkvwSIeSZmH
{
  int32_t isInitialized;
};

#endif                                 /* struct_tag_RZEbOWb6wzemkvwSIeSZmH */

#ifndef typedef_matlabshared_tracking_interna_e
#define typedef_matlabshared_tracking_interna_e

typedef struct tag_RZEbOWb6wzemkvwSIeSZmH matlabshared_tracking_interna_e;

#endif                             /* typedef_matlabshared_tracking_interna_e */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  double P[9];                         /* '<S3>/DataStoreMemory - P' */
  double x[3];                         /* '<S3>/DataStoreMemory - x' */
  double steer_angle_L;                /* '<S2>/SteerWheel to SteerAngle(L)2' */
  double steer_angle_R;                /* '<S2>/SteerWheel to SteerAngle(R)2' */
} sensor_fusion_DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  msg_sensor_cockpit cockpit;          /* '<Root>/cockpit' */
  msg_sensor_wheel wheel;              /* '<Root>/wheel' */
  msg_sensor_imu imu;                  /* '<Root>/imu' */
  msg_sensor_gps gps;                  /* '<Root>/gps' */
} sensor_fusion_ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  msg_ctrl_states states;              /* '<Root>/states' */
} sensor_fusion_ExtY;

/* Real-time Model Data Structure */
struct sensor_fusion_tag_RTM {
  const char * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern sensor_fusion_DW sensor_fusion_DW_l;

/* External inputs (root inport signals with default storage) */
extern sensor_fusion_ExtU sensor_fusion_U;

/* External outputs (root outports fed by signals with default storage) */
extern sensor_fusion_ExtY sensor_fusion_Y;

/* External data declarations for dependent source files */
extern const msg_ctrl_states sensor_fusion_rtZmsg_ctrl_state;/* msg_ctrl_states ground */

/* Model entry point functions */
extern void sensor_fusion_initialize(void);
extern void sensor_fusion_step(void);

/* Real-time Model object */
extern sensor_fusion_RT_MODEL *const sensor_fusion_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/checkMeasurementFcn1Signals' : Unused code path elimination
 * Block '<S3>/checkStateTransitionFcnSignals' : Unused code path elimination
 * Block '<S3>/DataTypeConversion_Q' : Eliminate redundant data type conversion
 * Block '<S3>/DataTypeConversion_R1' : Eliminate redundant data type conversion
 * Block '<S3>/DataTypeConversion_uMeas1' : Eliminate redundant data type conversion
 * Block '<S3>/DataTypeConversion_uState' : Eliminate redundant data type conversion
 * Block '<S3>/DataTypeConversion_y1' : Eliminate redundant data type conversion
 * Block '<S2>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S2>/Zero-Order Hold1' : Eliminated since input and output rates are identical
 * Block '<S2>/Zero-Order Hold2' : Eliminated since input and output rates are identical
 * Block '<S2>/Zero-Order Hold3' : Eliminated since input and output rates are identical
 * Block '<S2>/Zero-Order Hold4' : Eliminated since input and output rates are identical
 * Block '<S2>/Zero-Order Hold5' : Eliminated since input and output rates are identical
 */

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
 * '<S1>'   : 'sensor_fusion/Angle Conversion'
 * '<S2>'   : 'sensor_fusion/EKF'
 * '<S3>'   : 'sensor_fusion/EKF/Extended Kalman Filter1'
 * '<S4>'   : 'sensor_fusion/EKF/MATLAB Function1'
 * '<S5>'   : 'sensor_fusion/EKF/Simulink Function3'
 * '<S6>'   : 'sensor_fusion/EKF/Simulink Function4'
 * '<S7>'   : 'sensor_fusion/EKF/Simulink Function5'
 * '<S8>'   : 'sensor_fusion/EKF/Wheel covarience1'
 * '<S9>'   : 'sensor_fusion/EKF/mean1'
 * '<S10>'  : 'sensor_fusion/EKF/process noise covarience1'
 * '<S11>'  : 'sensor_fusion/EKF/wheel speed signal1'
 * '<S12>'  : 'sensor_fusion/EKF/Extended Kalman Filter1/Correct1'
 * '<S13>'  : 'sensor_fusion/EKF/Extended Kalman Filter1/Output'
 * '<S14>'  : 'sensor_fusion/EKF/Extended Kalman Filter1/Predict'
 * '<S15>'  : 'sensor_fusion/EKF/Extended Kalman Filter1/Output/MATLAB Function'
 * '<S16>'  : 'sensor_fusion/EKF/Simulink Function3/MATLAB Function1'
 * '<S17>'  : 'sensor_fusion/EKF/Simulink Function3/MATLAB Function2'
 * '<S18>'  : 'sensor_fusion/EKF/Simulink Function3/MATLAB Function3'
 * '<S19>'  : 'sensor_fusion/EKF/Simulink Function4/MATLAB Function'
 * '<S20>'  : 'sensor_fusion/EKF/Simulink Function5/MATLAB Function3'
 * '<S21>'  : 'sensor_fusion/EKF/Wheel covarience1/MATLAB Function2'
 * '<S22>'  : 'sensor_fusion/EKF/process noise covarience1/MATLAB Function2'
 */
#endif                                 /* sensor_fusion_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
