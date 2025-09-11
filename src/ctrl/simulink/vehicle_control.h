/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.h
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 5.7
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Thu Sep 11 08:57:15 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef vehicle_control_h_
#define vehicle_control_h_
#ifndef vehicle_control_COMMON_INCLUDES_
#define vehicle_control_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* vehicle_control_COMMON_INCLUDES_ */

/* Includes for objects with custom storage classes */
#include "simulink_import.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Forward declaration for rtModel */
typedef struct vehicle_control_tag_RTM vehicle_control_RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  double RateLimiter1;                 /* '<S1>/Rate Limiter1' */
  double RateLimiter;                  /* '<S1>/Rate Limiter' */
  double PrevY;                        /* '<S1>/Rate Limiter1' */
  double LastMajorTime;                /* '<S1>/Rate Limiter1' */
  double PrevY_l;                      /* '<S1>/Rate Limiter' */
  double LastMajorTime_n;              /* '<S1>/Rate Limiter' */
  bool PrevLimited;                    /* '<S1>/Rate Limiter1' */
  bool PrevLimited_m;                  /* '<S1>/Rate Limiter' */
} vehicle_control_DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  msg_ctrl_vehicle_state vehicle_state;/* '<Root>/vehicle_state' */
  msg_sensor_cockpit cockpit;          /* '<Root>/cockpit' */
  msg_sensor_wheel wheel;              /* '<Root>/wheel' */
  msg_sensor_imu imu;                  /* '<Root>/imu' */
  msg_sensor_gps gps;                  /* '<Root>/gps' */
} vehicle_control_ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  msg_ctrl_torque torq;                /* '<Root>/torq' */
} vehicle_control_ExtY;

/* Real-time Model Data Structure */
struct vehicle_control_tag_RTM {
  const char *errorStatus;
  RTWSolverInfo solverInfo;
  vehicle_control_DW *dwork;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_t clockTick0;
    double stepSize0;
    uint32_t clockTick1;
    SimTimeStep simTimeStep;
    double *t;
    double tArray[2];
  } Timing;
};

/* Model entry point functions */
extern void vehicle_control_initialize(vehicle_control_RT_MODEL *const rtM);
extern void vehicle_control_step(vehicle_control_RT_MODEL *const rtM,
  vehicle_control_ExtU *rtU, vehicle_control_ExtY *rtY);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Constant' : Unused code path elimination
 * Block '<S1>/Constant1' : Unused code path elimination
 * Block '<S1>/Constant2' : Unused code path elimination
 * Block '<S1>/Constant3' : Unused code path elimination
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/LowerRelop1' : Unused code path elimination
 * Block '<S4>/Switch' : Unused code path elimination
 * Block '<S4>/Switch2' : Unused code path elimination
 * Block '<S4>/UpperRelop' : Unused code path elimination
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/LowerRelop1' : Unused code path elimination
 * Block '<S5>/Switch' : Unused code path elimination
 * Block '<S5>/Switch2' : Unused code path elimination
 * Block '<S5>/UpperRelop' : Unused code path elimination
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
 * '<Root>' : 'vehicle_control'
 * '<S1>'   : 'vehicle_control/Subsystem1'
 * '<S2>'   : 'vehicle_control/Subsystem1/MATLAB Function1'
 * '<S3>'   : 'vehicle_control/Subsystem1/MATLAB Function2'
 * '<S4>'   : 'vehicle_control/Subsystem1/Saturation Dynamic'
 * '<S5>'   : 'vehicle_control/Subsystem1/Saturation Dynamic1'
 */
#endif                                 /* vehicle_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
