/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.h
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 5.15
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Thu Jul  9 12:21:12 2026
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
#include "rtGetNaN.h"

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
  double UnitDelay_DSTATE;             /* '<S38>/Unit Delay' */
  double UnitDelay1_DSTATE;            /* '<S38>/Unit Delay1' */
  double UnitDelay2_DSTATE;            /* '<S38>/Unit Delay2' */
  double UnitDelay3_DSTATE;            /* '<S38>/Unit Delay3' */
  double UnitDelay4_DSTATE;            /* '<S38>/Unit Delay4' */
  double UnitDelay5_DSTATE;            /* '<S38>/Unit Delay5' */
  double UnitDelay6_DSTATE;            /* '<S38>/Unit Delay6' */
  double UnitDelay_DSTATE_c;           /* '<S39>/Unit Delay' */
  double UnitDelay1_DSTATE_h;          /* '<S39>/Unit Delay1' */
  double UnitDelay2_DSTATE_p;          /* '<S39>/Unit Delay2' */
  double UnitDelay3_DSTATE_e;          /* '<S39>/Unit Delay3' */
  double UnitDelay4_DSTATE_p;          /* '<S39>/Unit Delay4' */
  double UnitDelay5_DSTATE_f;          /* '<S39>/Unit Delay5' */
  double UnitDelay6_DSTATE_a;          /* '<S39>/Unit Delay6' */
  double UnitDelay_DSTATE_h;           /* '<S32>/Unit Delay' */
  double UnitDelay1_DSTATE_a;          /* '<S32>/Unit Delay1' */
  double UnitDelay2_DSTATE_n;          /* '<S32>/Unit Delay2' */
  double UnitDelay3_DSTATE_o;          /* '<S32>/Unit Delay3' */
  double UnitDelay4_DSTATE_h;          /* '<S32>/Unit Delay4' */
  double UnitDelay_DSTATE_m;           /* '<S31>/Unit Delay' */
  double UnitDelay1_DSTATE_f;          /* '<S31>/Unit Delay1' */
  double UnitDelay2_DSTATE_pk;         /* '<S31>/Unit Delay2' */
  double UD_DSTATE;                    /* '<S7>/UD' */
  double UnitDelay_DSTATE_n;           /* '<S28>/Unit Delay' */
  double UnitDelay1_DSTATE_i;          /* '<S28>/Unit Delay1' */
  double UnitDelay2_DSTATE_b;          /* '<S28>/Unit Delay2' */
  double UnitDelay3_DSTATE_f;          /* '<S28>/Unit Delay3' */
  double UnitDelay4_DSTATE_o;          /* '<S28>/Unit Delay4' */
  double UnitDelay_DSTATE_b;           /* '<S30>/Unit Delay' */
  double UnitDelay1_DSTATE_m;          /* '<S30>/Unit Delay1' */
  double UnitDelay2_DSTATE_d;          /* '<S30>/Unit Delay2' */
  double UnitDelay3_DSTATE_fs;         /* '<S30>/Unit Delay3' */
  double UD_DSTATE_i;                  /* '<S8>/UD' */
  double DiscreteTimeIntegrator2_DSTATE;/* '<S2>/Discrete-Time Integrator2' */
  double UnitDelay_DSTATE_j;           /* '<S41>/Unit Delay' */
  double UnitDelay1_DSTATE_c;          /* '<S41>/Unit Delay1' */
  double UnitDelay2_DSTATE_f;          /* '<S41>/Unit Delay2' */
  double UnitDelay3_DSTATE_m;          /* '<S41>/Unit Delay3' */
  double UnitDelay4_DSTATE_f;          /* '<S41>/Unit Delay4' */
  double UnitDelay5_DSTATE_e;          /* '<S41>/Unit Delay5' */
  double UnitDelay6_DSTATE_j;          /* '<S41>/Unit Delay6' */
  double UnitDelay_DSTATE_g;           /* '<S42>/Unit Delay' */
  double UnitDelay1_DSTATE_n;          /* '<S42>/Unit Delay1' */
  double UnitDelay2_DSTATE_d5;         /* '<S42>/Unit Delay2' */
  double UnitDelay3_DSTATE_l;          /* '<S42>/Unit Delay3' */
  double UnitDelay4_DSTATE_i;          /* '<S42>/Unit Delay4' */
  double UnitDelay5_DSTATE_c;          /* '<S42>/Unit Delay5' */
  double UnitDelay6_DSTATE_f;          /* '<S42>/Unit Delay6' */
  double UnitDelay_DSTATE_jf;          /* '<S43>/Unit Delay' */
  double UnitDelay1_DSTATE_b;          /* '<S43>/Unit Delay1' */
  double UnitDelay2_DSTATE_l;          /* '<S43>/Unit Delay2' */
  double UnitDelay3_DSTATE_mt;         /* '<S43>/Unit Delay3' */
  double UnitDelay4_DSTATE_j;          /* '<S43>/Unit Delay4' */
  double UnitDelay5_DSTATE_h;          /* '<S43>/Unit Delay5' */
  double UnitDelay6_DSTATE_ab;         /* '<S43>/Unit Delay6' */
  double UnitDelay_DSTATE_bu;          /* '<S44>/Unit Delay' */
  double UnitDelay1_DSTATE_p;          /* '<S44>/Unit Delay1' */
  double UnitDelay2_DSTATE_k;          /* '<S44>/Unit Delay2' */
  double UnitDelay3_DSTATE_lk;         /* '<S44>/Unit Delay3' */
  double UnitDelay4_DSTATE_n;          /* '<S44>/Unit Delay4' */
  double UnitDelay5_DSTATE_a;          /* '<S44>/Unit Delay5' */
  double UnitDelay6_DSTATE_j0;         /* '<S44>/Unit Delay6' */
  double Delay_DSTATE;                 /* '<S58>/Delay' */
  double Delay_DSTATE_o;               /* '<S64>/Delay' */
  double Delay_DSTATE_e;               /* '<S70>/Delay' */
  double Delay_DSTATE_l;               /* '<S76>/Delay' */
  double Memory_PreviousInput;         /* '<S34>/Memory' */
  double Memory2_PreviousInput;        /* '<S34>/Memory2' */
  double Memory3_PreviousInput;        /* '<S34>/Memory3' */
  double Memory_PreviousInput_e;       /* '<S35>/Memory' */
  double Memory2_PreviousInput_e;      /* '<S35>/Memory2' */
  double Memory3_PreviousInput_b;      /* '<S35>/Memory3' */
  double Memory_PreviousInput_m;       /* '<S36>/Memory' */
  double Memory2_PreviousInput_b;      /* '<S36>/Memory2' */
  double Memory3_PreviousInput_a;      /* '<S36>/Memory3' */
  double Memory_PreviousInput_l;       /* '<S37>/Memory' */
  double Memory2_PreviousInput_a;      /* '<S37>/Memory2' */
  double Memory3_PreviousInput_c;      /* '<S37>/Memory3' */
  double Memory7_PreviousInput;        /* '<S2>/Memory7' */
  bool icLoad;                         /* '<S58>/Delay' */
  bool icLoad_f;                       /* '<S64>/Delay' */
  bool icLoad_fb;                      /* '<S70>/Delay' */
  bool icLoad_o;                       /* '<S76>/Delay' */
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
 * Block '<S2>/Add4' : Unused code path elimination
 * Block '<S2>/Add5' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S8>/Data Type Duplicate' : Unused code path elimination
 * Block '<S2>/Display' : Unused code path elimination
 * Block '<S2>/Gain2' : Unused code path elimination
 * Block '<S2>/Gain21' : Unused code path elimination
 * Block '<S2>/Gain31' : Unused code path elimination
 * Block '<S2>/Gain32' : Unused code path elimination
 * Block '<S2>/Memory10' : Unused code path elimination
 * Block '<S2>/Memory11' : Unused code path elimination
 * Block '<S2>/Memory8' : Unused code path elimination
 * Block '<S2>/Memory9' : Unused code path elimination
 * Block '<S20>/Data Type Duplicate' : Unused code path elimination
 * Block '<S20>/Data Type Propagation' : Unused code path elimination
 * Block '<S21>/Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Propagation' : Unused code path elimination
 * Block '<S22>/Data Type Duplicate' : Unused code path elimination
 * Block '<S22>/Data Type Propagation' : Unused code path elimination
 * Block '<S23>/Data Type Duplicate' : Unused code path elimination
 * Block '<S23>/Data Type Propagation' : Unused code path elimination
 * Block '<S24>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Propagation' : Unused code path elimination
 * Block '<S25>/Data Type Duplicate' : Unused code path elimination
 * Block '<S25>/Data Type Propagation' : Unused code path elimination
 * Block '<S26>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Data Type Propagation' : Unused code path elimination
 * Block '<S27>/Data Type Duplicate' : Unused code path elimination
 * Block '<S27>/Data Type Propagation' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S2>/Scope10' : Unused code path elimination
 * Block '<S2>/Scope11' : Unused code path elimination
 * Block '<S2>/Scope12' : Unused code path elimination
 * Block '<S2>/Scope13' : Unused code path elimination
 * Block '<S2>/Scope14' : Unused code path elimination
 * Block '<S2>/Scope15' : Unused code path elimination
 * Block '<S2>/Scope16' : Unused code path elimination
 * Block '<S2>/Scope17' : Unused code path elimination
 * Block '<S2>/Scope18' : Unused code path elimination
 * Block '<S2>/Scope2' : Unused code path elimination
 * Block '<S2>/Scope3' : Unused code path elimination
 * Block '<S2>/Scope5' : Unused code path elimination
 * Block '<S2>/Scope9' : Unused code path elimination
 * Block '<S58>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Duplicate' : Unused code path elimination
 * Block '<S60>/Data Type Propagation' : Unused code path elimination
 * Block '<S59>/Data Type Duplicate' : Unused code path elimination
 * Block '<S59>/Data Type Propagation' : Unused code path elimination
 * Block '<S34>/Scope' : Unused code path elimination
 * Block '<S64>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S66>/Data Type Duplicate' : Unused code path elimination
 * Block '<S66>/Data Type Propagation' : Unused code path elimination
 * Block '<S65>/Data Type Duplicate' : Unused code path elimination
 * Block '<S65>/Data Type Propagation' : Unused code path elimination
 * Block '<S70>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S72>/Data Type Duplicate' : Unused code path elimination
 * Block '<S72>/Data Type Propagation' : Unused code path elimination
 * Block '<S71>/Data Type Duplicate' : Unused code path elimination
 * Block '<S71>/Data Type Propagation' : Unused code path elimination
 * Block '<S36>/Scope' : Unused code path elimination
 * Block '<S76>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S78>/Data Type Duplicate' : Unused code path elimination
 * Block '<S78>/Data Type Propagation' : Unused code path elimination
 * Block '<S77>/Data Type Duplicate' : Unused code path elimination
 * Block '<S77>/Data Type Propagation' : Unused code path elimination
 * Block '<S82>/Unit Conversion' : Unused code path elimination
 * Block '<S83>/Unit Conversion' : Unused code path elimination
 * Block '<S2>/k_brake' : Unused code path elimination
 * Block '<S58>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S64>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S70>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S76>/Zero-Order Hold' : Eliminated since input and output rates are identical
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
 * '<S3>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion4'
 * '<S4>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion5'
 * '<S5>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion6'
 * '<S6>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion7'
 * '<S7>'   : 'vehicle_control/Vehicle Control(TV&TC)/Discrete Derivative1'
 * '<S8>'   : 'vehicle_control/Vehicle Control(TV&TC)/Discrete Derivative3'
 * '<S9>'   : 'vehicle_control/Vehicle Control(TV&TC)/FB_Ki1'
 * '<S10>'  : 'vehicle_control/Vehicle Control(TV&TC)/FB_Kp'
 * '<S11>'  : 'vehicle_control/Vehicle Control(TV&TC)/FB_P'
 * '<S12>'  : 'vehicle_control/Vehicle Control(TV&TC)/FF'
 * '<S13>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function1'
 * '<S14>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function12'
 * '<S15>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function14'
 * '<S16>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function18'
 * '<S17>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function19'
 * '<S18>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function20'
 * '<S19>'  : 'vehicle_control/Vehicle Control(TV&TC)/P_limit'
 * '<S20>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic10'
 * '<S21>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic11'
 * '<S22>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic12'
 * '<S23>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic13'
 * '<S24>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic14'
 * '<S25>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic15'
 * '<S26>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic8'
 * '<S27>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic9'
 * '<S28>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem10'
 * '<S29>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4'
 * '<S30>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem7'
 * '<S31>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem8'
 * '<S32>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem9'
 * '<S33>'  : 'vehicle_control/Vehicle Control(TV&TC)/System ID'
 * '<S34>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1'
 * '<S35>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1'
 * '<S36>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1'
 * '<S37>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1'
 * '<S38>'  : 'vehicle_control/Vehicle Control(TV&TC)/ax_filter'
 * '<S39>'  : 'vehicle_control/Vehicle Control(TV&TC)/ay_filter'
 * '<S40>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1'
 * '<S41>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter4'
 * '<S42>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter5'
 * '<S43>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter6'
 * '<S44>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter7'
 * '<S45>'  : 'vehicle_control/Vehicle Control(TV&TC)/torque_distribution'
 * '<S46>'  : 'vehicle_control/Vehicle Control(TV&TC)/yaw rate reference'
 * '<S47>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem10/MATLAB Function'
 * '<S48>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function1'
 * '<S49>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function2'
 * '<S50>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function3'
 * '<S51>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function4'
 * '<S52>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem7/MATLAB Function'
 * '<S53>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem8/MATLAB Function'
 * '<S54>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem9/MATLAB Function'
 * '<S55>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/MATLAB Function'
 * '<S56>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/MATLAB Function1'
 * '<S57>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/MATLAB Function2'
 * '<S58>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/Rate Limiter Dynamic'
 * '<S59>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/Saturation Dynamic2'
 * '<S60>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S61>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/MATLAB Function'
 * '<S62>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/MATLAB Function1'
 * '<S63>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/MATLAB Function2'
 * '<S64>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/Rate Limiter Dynamic'
 * '<S65>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/Saturation Dynamic2'
 * '<S66>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S67>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/MATLAB Function'
 * '<S68>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/MATLAB Function1'
 * '<S69>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/MATLAB Function2'
 * '<S70>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/Rate Limiter Dynamic'
 * '<S71>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/Saturation Dynamic2'
 * '<S72>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S73>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/MATLAB Function'
 * '<S74>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/MATLAB Function1'
 * '<S75>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/MATLAB Function2'
 * '<S76>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/Rate Limiter Dynamic'
 * '<S77>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/Saturation Dynamic2'
 * '<S78>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S79>'  : 'vehicle_control/Vehicle Control(TV&TC)/ax_filter/MATLAB Function'
 * '<S80>'  : 'vehicle_control/Vehicle Control(TV&TC)/ay_filter/MATLAB Function'
 * '<S81>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion1'
 * '<S82>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion2'
 * '<S83>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion3'
 * '<S84>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion4'
 * '<S85>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter4/MATLAB Function'
 * '<S86>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter5/MATLAB Function'
 * '<S87>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter6/MATLAB Function'
 * '<S88>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter7/MATLAB Function'
 * '<S89>'  : 'vehicle_control/Vehicle Control(TV&TC)/yaw rate reference/reference yaw rate'
 */
#endif                                 /* vehicle_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
