/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.h
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 4.15
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Sun Apr  5 15:41:15 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Traceability
 *    2. Debugging
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

#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include <stddef.h>
#include <string.h>

/* Includes for objects with custom storage classes */
#include "simulink_import.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct vehicle_control_tag_RTM vehicle_control_RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  double UnitDelay_DSTATE;             /* '<S20>/Unit Delay' */
  double UnitDelay1_DSTATE;            /* '<S20>/Unit Delay1' */
  double UnitDelay2_DSTATE;            /* '<S20>/Unit Delay2' */
  double UD_DSTATE;                    /* '<S5>/UD' */
  double UnitDelay_DSTATE_d;           /* '<S21>/Unit Delay' */
  double UnitDelay1_DSTATE_b;          /* '<S21>/Unit Delay1' */
  double UnitDelay2_DSTATE_h;          /* '<S21>/Unit Delay2' */
  double UnitDelay3_DSTATE;            /* '<S21>/Unit Delay3' */
  double UnitDelay4_DSTATE;            /* '<S21>/Unit Delay4' */
  double UnitDelay_DSTATE_c;           /* '<S22>/Unit Delay' */
  double UnitDelay1_DSTATE_a;          /* '<S22>/Unit Delay1' */
  double UnitDelay2_DSTATE_m;          /* '<S22>/Unit Delay2' */
  double UnitDelay3_DSTATE_a;          /* '<S22>/Unit Delay3' */
  double UnitDelay4_DSTATE_m;          /* '<S22>/Unit Delay4' */
  double UnitDelay_DSTATE_j;           /* '<S19>/Unit Delay' */
  double UnitDelay1_DSTATE_j;          /* '<S19>/Unit Delay1' */
  double UnitDelay2_DSTATE_n;          /* '<S19>/Unit Delay2' */
  double UnitDelay3_DSTATE_m;          /* '<S19>/Unit Delay3' */
  double UD_DSTATE_f;                  /* '<S6>/UD' */
  double UnitDelay_DSTATE_n;           /* '<S26>/Unit Delay' */
  double UnitDelay1_DSTATE_f;          /* '<S26>/Unit Delay1' */
  double UnitDelay2_DSTATE_he;         /* '<S26>/Unit Delay2' */
  double UnitDelay3_DSTATE_f;          /* '<S26>/Unit Delay3' */
  double UnitDelay4_DSTATE_j;          /* '<S26>/Unit Delay4' */
  double UnitDelay5_DSTATE;            /* '<S26>/Unit Delay5' */
  double UnitDelay6_DSTATE;            /* '<S26>/Unit Delay6' */
  double UnitDelay_DSTATE_cq;          /* '<S25>/Unit Delay' */
  double UnitDelay1_DSTATE_e;          /* '<S25>/Unit Delay1' */
  double UnitDelay2_DSTATE_c;          /* '<S25>/Unit Delay2' */
  double UnitDelay3_DSTATE_n;          /* '<S25>/Unit Delay3' */
  double UnitDelay4_DSTATE_jj;         /* '<S25>/Unit Delay4' */
  double UnitDelay5_DSTATE_f;          /* '<S25>/Unit Delay5' */
  double UnitDelay6_DSTATE_m;          /* '<S25>/Unit Delay6' */
  double DiscreteTimeIntegrator1_DSTATE;/* '<S2>/Discrete-Time Integrator1' */
  double Delay_DSTATE;                 /* '<S40>/Delay' */
  double Delay_DSTATE_f;               /* '<S46>/Delay' */
  double Memory_PreviousInput;         /* '<S23>/Memory' */
  double Memory2_PreviousInput;        /* '<S23>/Memory2' */
  double Memory3_PreviousInput;        /* '<S23>/Memory3' */
  double Memory_PreviousInput_d;       /* '<S24>/Memory' */
  double Memory2_PreviousInput_e;      /* '<S24>/Memory2' */
  double Memory3_PreviousInput_c;      /* '<S24>/Memory3' */
  double Memory_PreviousInput_o;       /* '<S2>/Memory' */
  bool icLoad;                         /* '<S40>/Delay' */
  bool icLoad_n;                       /* '<S46>/Delay' */
} vehicle_control_DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  msg_ctrl_tc_in tc_in;                /* '<Root>/tc_in' */
  msg_ctrl_states states;              /* '<Root>/states' */
  msg_sensor_cockpit cockpit;          /* '<Root>/cockpit' */
  msg_sensor_wheel wheel;              /* '<Root>/wheel' */
  msg_sensor_imu imu;                  /* '<Root>/imu' */
  msg_sensor_gps gps;                  /* '<Root>/gps' */
} vehicle_control_ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  msg_ctrl_torque torq;                /* '<Root>/torq' */
  msg_ctrl_tc tc;                      /* '<Root>/tc' */
} vehicle_control_ExtY;

/* Real-time Model Data Structure */
struct vehicle_control_tag_RTM {
  const char * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern vehicle_control_DW vehicle_control_DW_l;

/* External inputs (root inport signals with default storage) */
extern vehicle_control_ExtU vehicle_control_U;

/* External outputs (root outports fed by signals with default storage) */
extern vehicle_control_ExtY vehicle_control_Y;

/* Model entry point functions */
extern void vehicle_control_initialize(void);
extern void vehicle_control_step(void);

/* Real-time Model object */
extern vehicle_control_RT_MODEL *const vehicle_control_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S40>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S42>/Data Type Duplicate' : Unused code path elimination
 * Block '<S42>/Data Type Propagation' : Unused code path elimination
 * Block '<S41>/Data Type Duplicate' : Unused code path elimination
 * Block '<S41>/Data Type Propagation' : Unused code path elimination
 * Block '<S23>/Scope' : Unused code path elimination
 * Block '<S46>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S48>/Data Type Duplicate' : Unused code path elimination
 * Block '<S48>/Data Type Propagation' : Unused code path elimination
 * Block '<S47>/Data Type Duplicate' : Unused code path elimination
 * Block '<S47>/Data Type Propagation' : Unused code path elimination
 * Block '<S40>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S46>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S2>/TV_Gain' : Eliminated nontunable gain of 1
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
 * '<S1>'   : 'vehicle_control/Angle Conversion'
 * '<S2>'   : 'vehicle_control/Vehicle Control(TV&TC)'
 * '<S3>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion'
 * '<S4>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion1'
 * '<S5>'   : 'vehicle_control/Vehicle Control(TV&TC)/Discrete Derivative'
 * '<S6>'   : 'vehicle_control/Vehicle Control(TV&TC)/Discrete Derivative2'
 * '<S7>'   : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function'
 * '<S8>'   : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function1'
 * '<S9>'   : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function2'
 * '<S10>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function3'
 * '<S11>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function4'
 * '<S12>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function5'
 * '<S13>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function6'
 * '<S14>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function7'
 * '<S15>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function8'
 * '<S16>'  : 'vehicle_control/Vehicle Control(TV&TC)/SR'
 * '<S17>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem'
 * '<S18>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1'
 * '<S19>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem2'
 * '<S20>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem3'
 * '<S21>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem5'
 * '<S22>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem6'
 * '<S23>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL'
 * '<S24>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR'
 * '<S25>'  : 'vehicle_control/Vehicle Control(TV&TC)/ax_filter'
 * '<S26>'  : 'vehicle_control/Vehicle Control(TV&TC)/ay_filter'
 * '<S27>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1'
 * '<S28>'  : 'vehicle_control/Vehicle Control(TV&TC)/yaw rate reference'
 * '<S29>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1/MATLAB Function1'
 * '<S30>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1/MATLAB Function2'
 * '<S31>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1/MATLAB Function3'
 * '<S32>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1/MATLAB Function4'
 * '<S33>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem2/MATLAB Function'
 * '<S34>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem3/MATLAB Function'
 * '<S35>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem5/MATLAB Function'
 * '<S36>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem6/MATLAB Function'
 * '<S37>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL/MATLAB Function'
 * '<S38>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL/MATLAB Function1'
 * '<S39>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL/MATLAB Function2'
 * '<S40>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL/Rate Limiter Dynamic'
 * '<S41>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL/Saturation Dynamic2'
 * '<S42>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S43>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR/MATLAB Function'
 * '<S44>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR/MATLAB Function1'
 * '<S45>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR/MATLAB Function2'
 * '<S46>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR/Rate Limiter Dynamic'
 * '<S47>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR/Saturation Dynamic2'
 * '<S48>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S49>'  : 'vehicle_control/Vehicle Control(TV&TC)/ax_filter/MATLAB Function'
 * '<S50>'  : 'vehicle_control/Vehicle Control(TV&TC)/ay_filter/MATLAB Function'
 * '<S51>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion'
 * '<S52>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion1'
 * '<S53>'  : 'vehicle_control/Vehicle Control(TV&TC)/yaw rate reference/reference yaw rate'
 */
#endif                                 /* vehicle_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
