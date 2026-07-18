/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.h
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 5.29
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Sun Jul 19 01:27:59 2026
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
  double UnitDelay_DSTATE;             /* '<S42>/Unit Delay' */
  double UnitDelay1_DSTATE;            /* '<S42>/Unit Delay1' */
  double UnitDelay2_DSTATE;            /* '<S42>/Unit Delay2' */
  double UnitDelay3_DSTATE;            /* '<S42>/Unit Delay3' */
  double UnitDelay4_DSTATE;            /* '<S42>/Unit Delay4' */
  double UnitDelay5_DSTATE;            /* '<S42>/Unit Delay5' */
  double UnitDelay6_DSTATE;            /* '<S42>/Unit Delay6' */
  double UnitDelay_DSTATE_c;           /* '<S43>/Unit Delay' */
  double UnitDelay1_DSTATE_h;          /* '<S43>/Unit Delay1' */
  double UnitDelay2_DSTATE_p;          /* '<S43>/Unit Delay2' */
  double UnitDelay3_DSTATE_e;          /* '<S43>/Unit Delay3' */
  double UnitDelay4_DSTATE_p;          /* '<S43>/Unit Delay4' */
  double UnitDelay5_DSTATE_f;          /* '<S43>/Unit Delay5' */
  double UnitDelay6_DSTATE_a;          /* '<S43>/Unit Delay6' */
  double UnitDelay_DSTATE_h;           /* '<S36>/Unit Delay' */
  double UnitDelay1_DSTATE_a;          /* '<S36>/Unit Delay1' */
  double UnitDelay2_DSTATE_n;          /* '<S36>/Unit Delay2' */
  double UnitDelay3_DSTATE_o;          /* '<S36>/Unit Delay3' */
  double UnitDelay4_DSTATE_h;          /* '<S36>/Unit Delay4' */
  double UnitDelay_DSTATE_m;           /* '<S35>/Unit Delay' */
  double UnitDelay1_DSTATE_f;          /* '<S35>/Unit Delay1' */
  double UnitDelay2_DSTATE_pk;         /* '<S35>/Unit Delay2' */
  double UD_DSTATE;                    /* '<S10>/UD' */
  double UnitDelay_DSTATE_n;           /* '<S32>/Unit Delay' */
  double UnitDelay1_DSTATE_i;          /* '<S32>/Unit Delay1' */
  double UnitDelay2_DSTATE_b;          /* '<S32>/Unit Delay2' */
  double UnitDelay3_DSTATE_f;          /* '<S32>/Unit Delay3' */
  double UnitDelay4_DSTATE_o;          /* '<S32>/Unit Delay4' */
  double UnitDelay_DSTATE_b;           /* '<S34>/Unit Delay' */
  double UnitDelay1_DSTATE_m;          /* '<S34>/Unit Delay1' */
  double UnitDelay2_DSTATE_d;          /* '<S34>/Unit Delay2' */
  double UnitDelay3_DSTATE_fs;         /* '<S34>/Unit Delay3' */
  double UD_DSTATE_i;                  /* '<S11>/UD' */
  double DiscreteTimeIntegrator2_DSTATE;/* '<S5>/Discrete-Time Integrator2' */
  double UnitDelay_DSTATE_j;           /* '<S45>/Unit Delay' */
  double UnitDelay1_DSTATE_c;          /* '<S45>/Unit Delay1' */
  double UnitDelay2_DSTATE_f;          /* '<S45>/Unit Delay2' */
  double UnitDelay3_DSTATE_m;          /* '<S45>/Unit Delay3' */
  double UnitDelay4_DSTATE_f;          /* '<S45>/Unit Delay4' */
  double UnitDelay5_DSTATE_e;          /* '<S45>/Unit Delay5' */
  double UnitDelay6_DSTATE_j;          /* '<S45>/Unit Delay6' */
  double UnitDelay_DSTATE_g;           /* '<S46>/Unit Delay' */
  double UnitDelay1_DSTATE_n;          /* '<S46>/Unit Delay1' */
  double UnitDelay2_DSTATE_d5;         /* '<S46>/Unit Delay2' */
  double UnitDelay3_DSTATE_l;          /* '<S46>/Unit Delay3' */
  double UnitDelay4_DSTATE_i;          /* '<S46>/Unit Delay4' */
  double UnitDelay5_DSTATE_c;          /* '<S46>/Unit Delay5' */
  double UnitDelay6_DSTATE_f;          /* '<S46>/Unit Delay6' */
  double UnitDelay_DSTATE_jf;          /* '<S47>/Unit Delay' */
  double UnitDelay1_DSTATE_b;          /* '<S47>/Unit Delay1' */
  double UnitDelay2_DSTATE_l;          /* '<S47>/Unit Delay2' */
  double UnitDelay3_DSTATE_mt;         /* '<S47>/Unit Delay3' */
  double UnitDelay4_DSTATE_j;          /* '<S47>/Unit Delay4' */
  double UnitDelay5_DSTATE_h;          /* '<S47>/Unit Delay5' */
  double UnitDelay6_DSTATE_ab;         /* '<S47>/Unit Delay6' */
  double UnitDelay_DSTATE_bu;          /* '<S48>/Unit Delay' */
  double UnitDelay1_DSTATE_p;          /* '<S48>/Unit Delay1' */
  double UnitDelay2_DSTATE_k;          /* '<S48>/Unit Delay2' */
  double UnitDelay3_DSTATE_lk;         /* '<S48>/Unit Delay3' */
  double UnitDelay4_DSTATE_n;          /* '<S48>/Unit Delay4' */
  double UnitDelay5_DSTATE_a;          /* '<S48>/Unit Delay5' */
  double UnitDelay6_DSTATE_j0;         /* '<S48>/Unit Delay6' */
  double Delay_DSTATE;                 /* '<S62>/Delay' */
  double Delay_DSTATE_o;               /* '<S68>/Delay' */
  double Delay_DSTATE_e;               /* '<S74>/Delay' */
  double Delay_DSTATE_l;               /* '<S80>/Delay' */
  double Memory_PreviousInput;         /* '<S38>/Memory' */
  double Memory2_PreviousInput;        /* '<S38>/Memory2' */
  double Memory3_PreviousInput;        /* '<S38>/Memory3' */
  double Memory_PreviousInput_e;       /* '<S39>/Memory' */
  double Memory2_PreviousInput_e;      /* '<S39>/Memory2' */
  double Memory3_PreviousInput_b;      /* '<S39>/Memory3' */
  double Memory_PreviousInput_m;       /* '<S40>/Memory' */
  double Memory2_PreviousInput_b;      /* '<S40>/Memory2' */
  double Memory3_PreviousInput_a;      /* '<S40>/Memory3' */
  double Memory_PreviousInput_l;       /* '<S41>/Memory' */
  double Memory2_PreviousInput_a;      /* '<S41>/Memory2' */
  double Memory3_PreviousInput_c;      /* '<S41>/Memory3' */
  double Memory7_PreviousInput;        /* '<S5>/Memory7' */
  bool icLoad;                         /* '<S62>/Delay' */
  bool icLoad_f;                       /* '<S68>/Delay' */
  bool icLoad_fb;                      /* '<S74>/Delay' */
  bool icLoad_o;                       /* '<S80>/Delay' */
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
 * Block '<S5>/Add4' : Unused code path elimination
 * Block '<S5>/Add5' : Unused code path elimination
 * Block '<S10>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/Display' : Unused code path elimination
 * Block '<S5>/Gain2' : Unused code path elimination
 * Block '<S5>/Gain21' : Unused code path elimination
 * Block '<S5>/Gain31' : Unused code path elimination
 * Block '<S5>/Gain32' : Unused code path elimination
 * Block '<S5>/Memory10' : Unused code path elimination
 * Block '<S5>/Memory11' : Unused code path elimination
 * Block '<S5>/Memory8' : Unused code path elimination
 * Block '<S5>/Memory9' : Unused code path elimination
 * Block '<S24>/Data Type Duplicate' : Unused code path elimination
 * Block '<S24>/Data Type Propagation' : Unused code path elimination
 * Block '<S25>/Data Type Duplicate' : Unused code path elimination
 * Block '<S25>/Data Type Propagation' : Unused code path elimination
 * Block '<S26>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Data Type Propagation' : Unused code path elimination
 * Block '<S27>/Data Type Duplicate' : Unused code path elimination
 * Block '<S27>/Data Type Propagation' : Unused code path elimination
 * Block '<S28>/Data Type Duplicate' : Unused code path elimination
 * Block '<S28>/Data Type Propagation' : Unused code path elimination
 * Block '<S29>/Data Type Duplicate' : Unused code path elimination
 * Block '<S29>/Data Type Propagation' : Unused code path elimination
 * Block '<S30>/Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Data Type Propagation' : Unused code path elimination
 * Block '<S31>/Data Type Duplicate' : Unused code path elimination
 * Block '<S31>/Data Type Propagation' : Unused code path elimination
 * Block '<S5>/Scope1' : Unused code path elimination
 * Block '<S5>/Scope10' : Unused code path elimination
 * Block '<S5>/Scope11' : Unused code path elimination
 * Block '<S5>/Scope12' : Unused code path elimination
 * Block '<S5>/Scope13' : Unused code path elimination
 * Block '<S5>/Scope14' : Unused code path elimination
 * Block '<S5>/Scope15' : Unused code path elimination
 * Block '<S5>/Scope16' : Unused code path elimination
 * Block '<S5>/Scope17' : Unused code path elimination
 * Block '<S5>/Scope18' : Unused code path elimination
 * Block '<S5>/Scope2' : Unused code path elimination
 * Block '<S5>/Scope3' : Unused code path elimination
 * Block '<S5>/Scope5' : Unused code path elimination
 * Block '<S5>/Scope9' : Unused code path elimination
 * Block '<S62>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S64>/Data Type Duplicate' : Unused code path elimination
 * Block '<S64>/Data Type Propagation' : Unused code path elimination
 * Block '<S63>/Data Type Duplicate' : Unused code path elimination
 * Block '<S63>/Data Type Propagation' : Unused code path elimination
 * Block '<S38>/Scope' : Unused code path elimination
 * Block '<S68>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S70>/Data Type Duplicate' : Unused code path elimination
 * Block '<S70>/Data Type Propagation' : Unused code path elimination
 * Block '<S69>/Data Type Duplicate' : Unused code path elimination
 * Block '<S69>/Data Type Propagation' : Unused code path elimination
 * Block '<S74>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S76>/Data Type Duplicate' : Unused code path elimination
 * Block '<S76>/Data Type Propagation' : Unused code path elimination
 * Block '<S75>/Data Type Duplicate' : Unused code path elimination
 * Block '<S75>/Data Type Propagation' : Unused code path elimination
 * Block '<S40>/Scope' : Unused code path elimination
 * Block '<S80>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S82>/Data Type Duplicate' : Unused code path elimination
 * Block '<S82>/Data Type Propagation' : Unused code path elimination
 * Block '<S81>/Data Type Duplicate' : Unused code path elimination
 * Block '<S81>/Data Type Propagation' : Unused code path elimination
 * Block '<S86>/Unit Conversion' : Unused code path elimination
 * Block '<S87>/Unit Conversion' : Unused code path elimination
 * Block '<S5>/k_brake' : Unused code path elimination
 * Block '<S62>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S68>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S74>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S80>/Zero-Order Hold' : Eliminated since input and output rates are identical
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
 * '<S2>'   : 'vehicle_control/Angle Conversion1'
 * '<S3>'   : 'vehicle_control/MATLAB Function'
 * '<S4>'   : 'vehicle_control/MATLAB Function1'
 * '<S5>'   : 'vehicle_control/Vehicle Control(TV&TC)'
 * '<S6>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion4'
 * '<S7>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion5'
 * '<S8>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion6'
 * '<S9>'   : 'vehicle_control/Vehicle Control(TV&TC)/Angular Velocity Conversion7'
 * '<S10>'  : 'vehicle_control/Vehicle Control(TV&TC)/Discrete Derivative1'
 * '<S11>'  : 'vehicle_control/Vehicle Control(TV&TC)/Discrete Derivative3'
 * '<S12>'  : 'vehicle_control/Vehicle Control(TV&TC)/FB_Ki1'
 * '<S13>'  : 'vehicle_control/Vehicle Control(TV&TC)/FB_Kp'
 * '<S14>'  : 'vehicle_control/Vehicle Control(TV&TC)/FB_P'
 * '<S15>'  : 'vehicle_control/Vehicle Control(TV&TC)/FF'
 * '<S16>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function1'
 * '<S17>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function12'
 * '<S18>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function14'
 * '<S19>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function18'
 * '<S20>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function19'
 * '<S21>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function2'
 * '<S22>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function20'
 * '<S23>'  : 'vehicle_control/Vehicle Control(TV&TC)/P_limit'
 * '<S24>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic10'
 * '<S25>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic11'
 * '<S26>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic12'
 * '<S27>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic13'
 * '<S28>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic14'
 * '<S29>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic15'
 * '<S30>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic8'
 * '<S31>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic9'
 * '<S32>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem10'
 * '<S33>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4'
 * '<S34>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem7'
 * '<S35>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem8'
 * '<S36>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem9'
 * '<S37>'  : 'vehicle_control/Vehicle Control(TV&TC)/System ID'
 * '<S38>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1'
 * '<S39>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1'
 * '<S40>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1'
 * '<S41>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1'
 * '<S42>'  : 'vehicle_control/Vehicle Control(TV&TC)/ax_filter'
 * '<S43>'  : 'vehicle_control/Vehicle Control(TV&TC)/ay_filter'
 * '<S44>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1'
 * '<S45>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter4'
 * '<S46>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter5'
 * '<S47>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter6'
 * '<S48>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter7'
 * '<S49>'  : 'vehicle_control/Vehicle Control(TV&TC)/torque_distribution'
 * '<S50>'  : 'vehicle_control/Vehicle Control(TV&TC)/yaw rate reference'
 * '<S51>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem10/MATLAB Function'
 * '<S52>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function1'
 * '<S53>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function2'
 * '<S54>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function3'
 * '<S55>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function4'
 * '<S56>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem7/MATLAB Function'
 * '<S57>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem8/MATLAB Function'
 * '<S58>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem9/MATLAB Function'
 * '<S59>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/MATLAB Function'
 * '<S60>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/MATLAB Function1'
 * '<S61>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/MATLAB Function2'
 * '<S62>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/Rate Limiter Dynamic'
 * '<S63>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/Saturation Dynamic2'
 * '<S64>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FL1/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S65>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/MATLAB Function'
 * '<S66>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/MATLAB Function1'
 * '<S67>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/MATLAB Function2'
 * '<S68>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/Rate Limiter Dynamic'
 * '<S69>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/Saturation Dynamic2'
 * '<S70>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_FR1/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S71>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/MATLAB Function'
 * '<S72>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/MATLAB Function1'
 * '<S73>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/MATLAB Function2'
 * '<S74>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/Rate Limiter Dynamic'
 * '<S75>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/Saturation Dynamic2'
 * '<S76>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RL1/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S77>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/MATLAB Function'
 * '<S78>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/MATLAB Function1'
 * '<S79>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/MATLAB Function2'
 * '<S80>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/Rate Limiter Dynamic'
 * '<S81>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/Saturation Dynamic2'
 * '<S82>'  : 'vehicle_control/Vehicle Control(TV&TC)/TC_RR1/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S83>'  : 'vehicle_control/Vehicle Control(TV&TC)/ax_filter/MATLAB Function'
 * '<S84>'  : 'vehicle_control/Vehicle Control(TV&TC)/ay_filter/MATLAB Function'
 * '<S85>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion1'
 * '<S86>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion2'
 * '<S87>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion3'
 * '<S88>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle1/Angle Conversion4'
 * '<S89>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter4/MATLAB Function'
 * '<S90>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter5/MATLAB Function'
 * '<S91>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter6/MATLAB Function'
 * '<S92>'  : 'vehicle_control/Vehicle Control(TV&TC)/filter7/MATLAB Function'
 * '<S93>'  : 'vehicle_control/Vehicle Control(TV&TC)/yaw rate reference/reference yaw rate'
 */
#endif                                 /* vehicle_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
