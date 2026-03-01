/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.h
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 3.18
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Sun Mar  1 01:46:13 2026
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
  double UnitDelay;                    /* '<S26>/Unit Delay' */
  double UnitDelay1;                   /* '<S26>/Unit Delay1' */
  double UnitDelay2;                   /* '<S26>/Unit Delay2' */
  double UnitDelay3;                   /* '<S26>/Unit Delay3' */
  double UnitDelay4;                   /* '<S26>/Unit Delay4' */
  double UnitDelay5;                   /* '<S26>/Unit Delay5' */
  double UnitDelay_e;                  /* '<S23>/Unit Delay' */
  double UnitDelay1_l;                 /* '<S23>/Unit Delay1' */
  double UnitDelay2_i;                 /* '<S23>/Unit Delay2' */
  double UnitDelay3_p;                 /* '<S23>/Unit Delay3' */
  double UnitDelay4_c;                 /* '<S23>/Unit Delay4' */
  double UnitDelay5_j;                 /* '<S23>/Unit Delay5' */
  double UnitDelay_f;                  /* '<S21>/Unit Delay' */
  double UnitDelay1_h;                 /* '<S21>/Unit Delay1' */
  double UnitDelay2_f;                 /* '<S21>/Unit Delay2' */
  double UnitDelay3_j;                 /* '<S21>/Unit Delay3' */
  double UnitDelay4_i;                 /* '<S21>/Unit Delay4' */
  double UnitDelay5_a;                 /* '<S21>/Unit Delay5' */
  double UnitDelay_g;                  /* '<S22>/Unit Delay' */
  double UnitDelay1_o;                 /* '<S22>/Unit Delay1' */
  double UnitDelay2_b;                 /* '<S22>/Unit Delay2' */
  double UnitDelay3_l;                 /* '<S22>/Unit Delay3' */
  double UnitDelay4_a;                 /* '<S22>/Unit Delay4' */
  double UnitDelay5_jx;                /* '<S22>/Unit Delay5' */
  double RateLimiter1;                 /* '<S4>/Rate Limiter1' */
  double RateLimiter;                  /* '<S4>/Rate Limiter' */
  double y;                            /* '<S26>/MATLAB Function' */
  double y_a;                          /* '<S25>/MATLAB Function' */
  double y_f;                          /* '<S24>/MATLAB Function' */
  double y_m;                          /* '<S23>/MATLAB Function' */
  double y_p;                          /* '<S22>/MATLAB Function' */
  double y_h;                          /* '<S21>/MATLAB Function' */
  double UnitDelay_DSTATE;             /* '<S26>/Unit Delay' */
  double UnitDelay1_DSTATE;            /* '<S26>/Unit Delay1' */
  double UnitDelay2_DSTATE;            /* '<S26>/Unit Delay2' */
  double UnitDelay3_DSTATE;            /* '<S26>/Unit Delay3' */
  double UnitDelay4_DSTATE;            /* '<S26>/Unit Delay4' */
  double UnitDelay5_DSTATE;            /* '<S26>/Unit Delay5' */
  double UnitDelay6_DSTATE;            /* '<S26>/Unit Delay6' */
  double UD_DSTATE;                    /* '<S10>/UD' */
  double UnitDelay_DSTATE_h;           /* '<S24>/Unit Delay' */
  double UnitDelay1_DSTATE_b;          /* '<S24>/Unit Delay1' */
  double UnitDelay2_DSTATE_g;          /* '<S24>/Unit Delay2' */
  double UnitDelay3_DSTATE_n;          /* '<S24>/Unit Delay3' */
  double UnitDelay4_DSTATE_p;          /* '<S24>/Unit Delay4' */
  double UnitDelay5_DSTATE_d;          /* '<S24>/Unit Delay5' */
  double UnitDelay6_DSTATE_e;          /* '<S24>/Unit Delay6' */
  double UnitDelay_DSTATE_d;           /* '<S25>/Unit Delay' */
  double UnitDelay1_DSTATE_g;          /* '<S25>/Unit Delay1' */
  double UnitDelay2_DSTATE_a;          /* '<S25>/Unit Delay2' */
  double UnitDelay3_DSTATE_p;          /* '<S25>/Unit Delay3' */
  double UnitDelay4_DSTATE_e;          /* '<S25>/Unit Delay4' */
  double UnitDelay5_DSTATE_a;          /* '<S25>/Unit Delay5' */
  double UnitDelay6_DSTATE_l;          /* '<S25>/Unit Delay6' */
  double UnitDelay_DSTATE_b;           /* '<S23>/Unit Delay' */
  double UnitDelay1_DSTATE_j;          /* '<S23>/Unit Delay1' */
  double UnitDelay2_DSTATE_an;         /* '<S23>/Unit Delay2' */
  double UnitDelay3_DSTATE_c;          /* '<S23>/Unit Delay3' */
  double UnitDelay4_DSTATE_en;         /* '<S23>/Unit Delay4' */
  double UnitDelay5_DSTATE_b;          /* '<S23>/Unit Delay5' */
  double UnitDelay6_DSTATE_m;          /* '<S23>/Unit Delay6' */
  double UD_DSTATE_h;                  /* '<S11>/UD' */
  double UnitDelay_DSTATE_l;           /* '<S21>/Unit Delay' */
  double UnitDelay1_DSTATE_ju;         /* '<S21>/Unit Delay1' */
  double UnitDelay2_DSTATE_p;          /* '<S21>/Unit Delay2' */
  double UnitDelay3_DSTATE_e;          /* '<S21>/Unit Delay3' */
  double UnitDelay4_DSTATE_b;          /* '<S21>/Unit Delay4' */
  double UnitDelay5_DSTATE_n;          /* '<S21>/Unit Delay5' */
  double UnitDelay6_DSTATE_j;          /* '<S21>/Unit Delay6' */
  double UnitDelay_DSTATE_a;           /* '<S22>/Unit Delay' */
  double UnitDelay1_DSTATE_p;          /* '<S22>/Unit Delay1' */
  double UnitDelay2_DSTATE_as;         /* '<S22>/Unit Delay2' */
  double UnitDelay3_DSTATE_d;          /* '<S22>/Unit Delay3' */
  double UnitDelay4_DSTATE_a;          /* '<S22>/Unit Delay4' */
  double UnitDelay5_DSTATE_h;          /* '<S22>/Unit Delay5' */
  double UnitDelay6_DSTATE_f;          /* '<S22>/Unit Delay6' */
  double PrevY;                        /* '<S4>/Rate Limiter1' */
  double LastMajorTime;                /* '<S4>/Rate Limiter1' */
  double PrevY_a;                      /* '<S4>/Rate Limiter' */
  double LastMajorTime_b;              /* '<S4>/Rate Limiter' */
  bool PrevLimited;                    /* '<S4>/Rate Limiter1' */
  bool PrevLimited_p;                  /* '<S4>/Rate Limiter' */
} vehicle_control_DW;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [-0.6680937;-0.653558249;-0.639118443;-0.624770091;-0.61050953;-0.596332569;-0.58223572;-0.568215316;-0.554268041;-0.540390405;-0.52657944;-0.512832005;-0.499144959;-0.485515509;-0.471940687;-0.458418051;-0.444944458;-0.43151764;-0.418134805;-0.404793683;-0.391491656;-0.378226281;-0.36499529;-0.351796412;-0.33862703;-0.325485225;-0.312368727;-0.299275092;-0.286202227;-0.273148212;-0.260110428;-0.247087131;-0.23407605;-0.221074918;-0.208081641;-0.195094297;-0.182110618;-0.169128301;-0.156145373;-0.143159635;-0.13016887;-0.11717088;-0.10416343;-0.091144268;-0.078111092;-0.06506158;-0.051993375;-0.038904052;-0.025791166;-0.012652193;0.000515427;0.013714331;0.02694722;0.040216871;0.053526141;0.066877961;0.080275405;0.093721614;0.107219815;0.120773431;0.134385934;0.148061025;0.161802473;0.175614328;0.189500691;0.203465943;0.217514621;0.231651614;0.245881981;0.260210959;0.274644483;0.289188311;0.303848728;0.318632888;0.333547773;0.348601063;0.36380131;0.379157066;0.394678104;0.410374722;0.426258091;0.442340427;0.458634995;0.475156281;0.491920169;0.508944284;0.526247827;0.543852789;0.561782905;0.580065403;0.598731001;0.617814431;0.637355486;0.657400592;0.678003156;0.699226359;0.7211456;0.74385181;0.767455991;0.792097247;0.81795238]
   * Referenced by: '<S28>/SteerWheel to SteerAngle(L)'
   */
  double SteerWheeltoSteerAngleL_tableDa[101];

  /* Pooled Parameter (Expression: [-3.1415926;-3.078760748;-3.015928896;-2.953097044;-2.890265192;-2.82743334;-2.764601488;-2.701769636;-2.638937784;-2.576105932;-2.51327408;-2.450442228;-2.387610376;-2.324778524;-2.261946672;-2.19911482;-2.136282968;-2.073451116;-2.010619264;-1.947787412;-1.88495556;-1.822123708;-1.759291856;-1.696460004;-1.633628152;-1.5707963;-1.507964448;-1.445132596;-1.382300744;-1.319468892;-1.25663704;-1.193805188;-1.130973336;-1.068141484;-1.005309632;-0.94247778;-0.879645928;-0.816814076;-0.753982224;-0.691150372;-0.62831852;-0.565486668;-0.502654816;-0.439822964;-0.376991112;-0.31415926;-0.251327408;-0.188495556;-0.125663704;-0.062831852;-2.8678e-15;0.062831852;0.125663704;0.188495556;0.251327408;0.31415926;0.376991112;0.439822964;0.502654816;0.565486668;0.62831852;0.691150372;0.753982224;0.816814076;0.879645928;0.94247778;1.005309632;1.068141484;1.130973336;1.193805188;1.25663704;1.319468892;1.382300744;1.445132596;1.507964448;1.5707963;1.633628152;1.696460004;1.759291856;1.822123708;1.88495556;1.947787412;2.010619264;2.073451116;2.136282968;2.19911482;2.261946672;2.324778524;2.387610376;2.450442228;2.51327408;2.576105932;2.638937784;2.701769636;2.764601488;2.82743334;2.890265192;2.953097044;3.015928896;3.078760748;3.1415926])
   * Referenced by:
   *   '<S28>/SteerWheel to SteerAngle(L)'
   *   '<S28>/SteerWheel to SteerAngle(R)'
   */
  double pooled4[101];

  /* Expression: [-0.817958663;-0.792103181;-0.767461751;-0.743857395;-0.721151011;-0.699231595;-0.678008217;-0.657405479;-0.637360373;-0.617818968;-0.598735364;-0.580069766;-0.561787094;-0.543856803;-0.526251842;-0.50894795;-0.491923834;-0.475159772;-0.458638486;-0.442343743;-0.426261232;-0.410377689;-0.394681071;-0.379159858;-0.363804103;-0.348603856;-0.333550391;-0.318635331;-0.303851171;-0.289190406;-0.274646577;-0.260213054;-0.245883901;-0.231653359;-0.217516367;-0.203467514;-0.189502087;-0.175615724;-0.1618038;-0.148062247;-0.134387051;-0.120774443;-0.10722074;-0.093722416;-0.080276121;-0.06687859;-0.053526647;-0.04021729;-0.026947534;-0.013714544;-0.000515538;0.012652185;0.025791254;0.038904244;0.051993672;0.065061981;0.078111598;0.091144879;0.104164145;0.1171717;0.130169795;0.143160664;0.156146525;0.16912954;0.18211184;0.195095693;0.208083211;0.221076664;0.234077796;0.247089051;0.260112523;0.273150306;0.286204496;0.299277536;0.31237117;0.325487843;0.338629823;0.351799205;0.364998257;0.378229423;0.391494972;0.404796999;0.418138296;0.431521306;0.444948298;0.45842189;0.471944876;0.485519697;0.499149322;0.512836369;0.526584152;0.540395117;0.554272928;0.568220377;0.582240956;0.59633798;0.61051494;0.624775851;0.639124377;0.653564358;0.668099983]
   * Referenced by: '<S28>/SteerWheel to SteerAngle(R)'
   */
  double SteerWheeltoSteerAngleR_tableDa[101];

  /* Expression: [0;826.04999999999995]
   * Referenced by: '<S20>/1-D Lookup Table1'
   */
  double uDLookupTable1_tableData[2];

  /* Expression: [0;1424.3699999999999]
   * Referenced by: '<S20>/1-D Lookup Table1'
   */
  double uDLookupTable1_bp01Data[2];
} vehicle_control_ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  msg_ctrl_tc_in tc_in;                /* '<Root>/tc_in' */
  msg_ctrl_vehicle_state vehicle_state;/* '<Root>/vehicle_state' */
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

/* Constant parameters (default storage) */
extern const vehicle_control_ConstP rtConstP;

/* Model entry point functions */
extern void vehicle_control_initialize(vehicle_control_RT_MODEL *const rtM);
extern void vehicle_control_step(vehicle_control_RT_MODEL *const rtM,
  vehicle_control_ExtU *rtU, vehicle_control_ExtY *rtY);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Unit Conversion' : Unused code path elimination
 * Block '<S2>/Unit Conversion' : Unused code path elimination
 * Block '<Root>/Gain' : Unused code path elimination
 * Block '<Root>/Gain1' : Unused code path elimination
 * Block '<S8>/Data Type Duplicate' : Unused code path elimination
 * Block '<S8>/Data Type Propagation' : Unused code path elimination
 * Block '<S9>/Data Type Duplicate' : Unused code path elimination
 * Block '<S9>/Data Type Propagation' : Unused code path elimination
 * Block '<S10>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S17>/Data Type Duplicate' : Unused code path elimination
 * Block '<S17>/Data Type Propagation' : Unused code path elimination
 * Block '<S18>/Data Type Duplicate' : Unused code path elimination
 * Block '<S18>/Data Type Propagation' : Unused code path elimination
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
 * '<S1>'   : 'vehicle_control/Angular Velocity Conversion'
 * '<S2>'   : 'vehicle_control/Angular Velocity Conversion1'
 * '<S3>'   : 'vehicle_control/Angular Velocity Conversion2'
 * '<S4>'   : 'vehicle_control/Subsystem1'
 * '<S5>'   : 'vehicle_control/Vehicle Control(TV&TC)'
 * '<S6>'   : 'vehicle_control/Subsystem1/MATLAB Function1'
 * '<S7>'   : 'vehicle_control/Subsystem1/MATLAB Function2'
 * '<S8>'   : 'vehicle_control/Subsystem1/Saturation Dynamic'
 * '<S9>'   : 'vehicle_control/Subsystem1/Saturation Dynamic1'
 * '<S10>'  : 'vehicle_control/Vehicle Control(TV&TC)/Discrete Derivative'
 * '<S11>'  : 'vehicle_control/Vehicle Control(TV&TC)/Discrete Derivative2'
 * '<S12>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function'
 * '<S13>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function1'
 * '<S14>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function2'
 * '<S15>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function3'
 * '<S16>'  : 'vehicle_control/Vehicle Control(TV&TC)/MATLAB Function4'
 * '<S17>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic'
 * '<S18>'  : 'vehicle_control/Vehicle Control(TV&TC)/Saturation Dynamic1'
 * '<S19>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem'
 * '<S20>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1'
 * '<S21>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem2'
 * '<S22>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem3'
 * '<S23>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4'
 * '<S24>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem5'
 * '<S25>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem6'
 * '<S26>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem8'
 * '<S27>'  : 'vehicle_control/Vehicle Control(TV&TC)/Torque_Max'
 * '<S28>'  : 'vehicle_control/Vehicle Control(TV&TC)/bicycle model steering angle'
 * '<S29>'  : 'vehicle_control/Vehicle Control(TV&TC)/yaw rate reference'
 * '<S30>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1/MATLAB Function1'
 * '<S31>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1/MATLAB Function2'
 * '<S32>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1/MATLAB Function3'
 * '<S33>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem1/MATLAB Function4'
 * '<S34>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem2/MATLAB Function'
 * '<S35>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem3/MATLAB Function'
 * '<S36>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem4/MATLAB Function'
 * '<S37>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem5/MATLAB Function'
 * '<S38>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem6/MATLAB Function'
 * '<S39>'  : 'vehicle_control/Vehicle Control(TV&TC)/Subsystem8/MATLAB Function'
 * '<S40>'  : 'vehicle_control/Vehicle Control(TV&TC)/yaw rate reference/reference yaw rate 1'
 */
#endif                                 /* vehicle_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
