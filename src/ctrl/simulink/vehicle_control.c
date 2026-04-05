/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
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

#include "vehicle_control.h"
#include <math.h>
#include <string.h>
#include "look1_binlx.h"
#include "look1_binlc.h"
#include "simulink_import.h"

/* Block signals and states (default storage) */
vehicle_control_DW vehicle_control_DW_l;

/* External inputs (root inport signals with default storage) */
vehicle_control_ExtU vehicle_control_U;

/* External outputs (root outports fed by signals with default storage) */
vehicle_control_ExtY vehicle_control_Y;

/* Real-time model */
static vehicle_control_RT_MODEL vehicle_control_M_;
vehicle_control_RT_MODEL *const vehicle_control_M = &vehicle_control_M_;
extern const double rtCP_pooled_xEgtjtEWFzHM[23];
extern const double rtCP_pooled_uGCq6zXFsU2Z[23];
extern const double rtCP_pooled_UBMtqbU4Pmyk[23];
extern const double rtCP_pooled_RXVSwQvYbp64[3];
extern const double rtCP_pooled_H9ZWZ4ADDsDZ[3];

#define rtCP_SteerWheeltoSteerAngleL_ne rtCP_pooled_xEgtjtEWFzHM /* Expression: [-24;-23;-19;-16;-12;-9;-6;-4;-2;0;2;4;5;7;9;11;13;15;17;19;21;24;25]
                                                                  * Referenced by: '<S27>/SteerWheel to SteerAngle(L)_new'
                                                                  */
#define rtCP_SteerWheeltoSteerAngleL__j rtCP_pooled_uGCq6zXFsU2Z /* Expression: [-84;-80;-70;-60;-50;-40;-30;-20;-10;0;10;20;30;40;50;60;70;80;90;100;110;120;124]
                                                                  * Referenced by: '<S27>/SteerWheel to SteerAngle(L)_new'
                                                                  */
#define rtCP_SteerWheeltoSteerAngleR_ne rtCP_pooled_UBMtqbU4Pmyk /* Expression: [-24;-23;-19;-16;-13;-10;-7;-5;-2;0;2;4;7;9;11;13;15;18;20;23;25;27;28]
                                                                  * Referenced by: '<S27>/SteerWheel to SteerAngle(R)_new1'
                                                                  */
#define rtCP_SteerWheeltoSteerAngleR__d rtCP_pooled_uGCq6zXFsU2Z /* Expression: [-84;-80;-70;-60;-50;-40;-30;-20;-10;0;10;20;30;40;50;60;70;80;90;100;110;120;124]
                                                                  * Referenced by: '<S27>/SteerWheel to SteerAngle(R)_new1'
                                                                  */
#define rtCP_uDLookupTable_tableData   rtCP_pooled_RXVSwQvYbp64  /* Expression: [-826.04999999999995;0;826.04999999999995]
                                                                  * Referenced by: '<S18>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable_bp01Data    rtCP_pooled_H9ZWZ4ADDsDZ  /* Expression: [-1424.3699999999999;0;1424.3699999999999]
                                                                  * Referenced by: '<S18>/1-D Lookup Table'
                                                                  */

static void MATLABFunction4(double rtu_v, double rtu_delta_trq, double *rty_y);
static void MATLABFunction(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_u, double
  *rty_y);
static void MATLABFunction1(double rtu_TC, double rtu_TC_last, double
  rtu_count_last, double *rty_rate_limit, double *rty_count);
static void MATLABFunction2(double rtu_trq, double rtu_rate_limit, double
  *rty_rate_up, double *rty_rate_lo);
static void MATLABFunction_f(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_last_y_6,
  double rtu_last_y_7, double rtu_u, double *rty_y);

/*
 * Output and update for atomic system:
 *    '<S2>/MATLAB Function4'
 *    '<S2>/MATLAB Function6'
 */
static void MATLABFunction4(double rtu_v, double rtu_delta_trq, double *rty_y)
{
  if (rtu_v > 5.0) {
    *rty_y = rtu_delta_trq;
  } else if ((rtu_v <= 5.0) && (rtu_v > 2.0)) {
    *rty_y = (rtu_v - 2.0) * rtu_delta_trq / 3.0;
  } else {
    *rty_y = 0.0;
  }
}

/*
 * Output and update for atomic system:
 *    '<S21>/MATLAB Function'
 *    '<S22>/MATLAB Function'
 */
static void MATLABFunction(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_u, double
  *rty_y)
{
  *rty_y = (((((rtu_last_y_1 + rtu_last_y_2) + rtu_last_y_3) + rtu_last_y_4) +
             rtu_last_y_5) + rtu_u) / 6.0;
}

/*
 * Output and update for atomic system:
 *    '<S23>/MATLAB Function1'
 *    '<S24>/MATLAB Function1'
 */
static void MATLABFunction1(double rtu_TC, double rtu_TC_last, double
  rtu_count_last, double *rty_rate_limit, double *rty_count)
{
  if ((rtu_TC_last == 1.0) && (rtu_TC == 0.0)) {
    *rty_count = 1.0;
    *rty_rate_limit = 500.0;
  } else if ((rtu_count_last > 0.0) && (rtu_count_last < 20.0)) {
    *rty_count = rtu_count_last + 1.0;
    *rty_rate_limit = 500.0;
  } else {
    *rty_count = 0.0;
    *rty_rate_limit = (rtInf);
  }
}

/*
 * Output and update for atomic system:
 *    '<S23>/MATLAB Function2'
 *    '<S24>/MATLAB Function2'
 */
static void MATLABFunction2(double rtu_trq, double rtu_rate_limit, double
  *rty_rate_up, double *rty_rate_lo)
{
  if (rtu_trq > 0.0) {
    *rty_rate_up = rtu_rate_limit;
    *rty_rate_lo = (rtMinusInf);
  } else {
    *rty_rate_up = (rtInf);
    *rty_rate_lo = -rtu_rate_limit;
  }
}

/*
 * Output and update for atomic system:
 *    '<S25>/MATLAB Function'
 *    '<S26>/MATLAB Function'
 */
static void MATLABFunction_f(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_last_y_6,
  double rtu_last_y_7, double rtu_u, double *rty_y)
{
  *rty_y = (((((((rtu_last_y_1 + rtu_last_y_2) + rtu_last_y_3) + rtu_last_y_4) +
               rtu_last_y_5) + rtu_last_y_6) + rtu_last_y_7) + rtu_u) / 8.0;
}

/* Model step function */
void vehicle_control_step(void)
{
  double rtb_F_aero;
  double rtb_F_dy;
  double rtb_FzFR;
  double rtb_Gain;
  double rtb_Memory;
  double rtb_Sum;
  double rtb_Switch2_f;
  double rtb_Switch2_g_tmp;
  double rtb_TSamp;
  double rtb_TSamp_d;
  double rtb_UnitConversion;
  double rtb_UnitDelay;
  double rtb_UnitDelay1;
  double rtb_UnitDelay1_c;
  double rtb_UnitDelay1_e;
  double rtb_UnitDelay1_g;
  double rtb_UnitDelay1_k;
  double rtb_UnitDelay1_oo;
  double rtb_UnitDelay2_a;
  double rtb_UnitDelay2_c;
  double rtb_UnitDelay2_gi;
  double rtb_UnitDelay2_i;
  double rtb_UnitDelay2_po;
  double rtb_UnitDelay3;
  double rtb_UnitDelay3_f;
  double rtb_UnitDelay3_i;
  double rtb_UnitDelay3_l;
  double rtb_UnitDelay4_k;
  double rtb_UnitDelay4_l;
  double rtb_UnitDelay5;
  double rtb_UnitDelay5_i;
  double rtb_UnitDelay_c;
  double rtb_UnitDelay_ju;
  double rtb_UnitDelay_k;
  double rtb_UnitDelay_m;
  double rtb_UnitDelay_n;
  double rtb_rate_limit;
  double rtb_rate_lo_o;
  double rtb_ratio;
  double rtb_uDLookupTable;
  double rtb_y;
  double rtb_y_ft;
  double rtb_y_g;
  double rtb_y_j5;
  double rtb_y_k;
  double rtb_y_n;

  /* UnitConversion: '<S1>/Unit Conversion' incorporates:
   *  Inport generated from: '<Root>/cockpit'
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_rate_lo_o = 0.017453292519943295 * vehicle_control_U.cockpit.steer;

  /* UnitConversion: '<S51>/Unit Conversion' */
  /* Unit Conversion - from: rad to: deg
     Expression: output = (57.2958*input) + (0) */
  rtb_Switch2_f = 57.295779513082323 * rtb_rate_lo_o;

  /* UnitConversion: '<S52>/Unit Conversion' incorporates:
   *  Gain: '<S27>/Gain4'
   *  Lookup_n-D: '<S27>/SteerWheel to SteerAngle(L)_new'
   *  Lookup_n-D: '<S27>/SteerWheel to SteerAngle(R)_new1'
   *  Sum: '<S27>/Add'
   *  Switch: '<S48>/Switch2'
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_UnitConversion = (look1_binlx(rtb_Switch2_f,
    rtCP_SteerWheeltoSteerAngleL__j, rtCP_SteerWheeltoSteerAngleL_ne, 22U) +
                        look1_binlx(rtb_Switch2_f,
    rtCP_SteerWheeltoSteerAngleR__d, rtCP_SteerWheeltoSteerAngleR_ne, 22U)) *
    0.5 * 0.017453292519943295;

  /* UnitDelay: '<S20>/Unit Delay' */
  rtb_UnitDelay = vehicle_control_DW_l.UnitDelay_DSTATE;

  /* UnitDelay: '<S20>/Unit Delay1' */
  rtb_UnitDelay1 = vehicle_control_DW_l.UnitDelay1_DSTATE;

  /* MATLAB Function: '<S20>/MATLAB Function' incorporates:
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S28>/reference yaw rate'
   *  UnitDelay: '<S20>/Unit Delay'
   *  UnitDelay: '<S20>/Unit Delay1'
   *  UnitDelay: '<S20>/Unit Delay2'
   */
  rtb_y_ft = (((vehicle_control_DW_l.UnitDelay_DSTATE +
                vehicle_control_DW_l.UnitDelay1_DSTATE) +
               vehicle_control_DW_l.UnitDelay2_DSTATE) +
              vehicle_control_U.states.velocity.x * rtb_UnitConversion / 1.6) /
    4.0;

  /* SampleTimeMath: '<S5>/TSamp'
   *
   * About '<S5>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp = rtb_y_ft * 100.0;

  /* UnitDelay: '<S21>/Unit Delay' */
  rtb_UnitDelay_c = vehicle_control_DW_l.UnitDelay_DSTATE_d;

  /* UnitDelay: '<S21>/Unit Delay1' */
  rtb_UnitDelay1_c = vehicle_control_DW_l.UnitDelay1_DSTATE_b;

  /* UnitDelay: '<S21>/Unit Delay2' */
  rtb_UnitDelay2_i = vehicle_control_DW_l.UnitDelay2_DSTATE_h;

  /* UnitDelay: '<S21>/Unit Delay3' */
  rtb_UnitDelay3 = vehicle_control_DW_l.UnitDelay3_DSTATE;

  /* MATLAB Function: '<S21>/MATLAB Function' incorporates:
   *  Sum: '<S5>/Diff'
   *  UnitDelay: '<S21>/Unit Delay'
   *  UnitDelay: '<S21>/Unit Delay1'
   *  UnitDelay: '<S21>/Unit Delay2'
   *  UnitDelay: '<S21>/Unit Delay3'
   *  UnitDelay: '<S21>/Unit Delay4'
   *  UnitDelay: '<S5>/UD'
   *
   * Block description for '<S5>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S5>/UD':
   *
   *  Store in Global RAM
   */
  MATLABFunction(vehicle_control_DW_l.UnitDelay_DSTATE_d,
                 vehicle_control_DW_l.UnitDelay1_DSTATE_b,
                 vehicle_control_DW_l.UnitDelay2_DSTATE_h,
                 vehicle_control_DW_l.UnitDelay3_DSTATE,
                 vehicle_control_DW_l.UnitDelay4_DSTATE, rtb_TSamp -
                 vehicle_control_DW_l.UD_DSTATE, &rtb_y_j5);

  /* UnitDelay: '<S22>/Unit Delay' */
  rtb_UnitDelay_m = vehicle_control_DW_l.UnitDelay_DSTATE_c;

  /* UnitDelay: '<S22>/Unit Delay1' */
  rtb_UnitDelay1_oo = vehicle_control_DW_l.UnitDelay1_DSTATE_a;

  /* UnitDelay: '<S22>/Unit Delay2' */
  rtb_UnitDelay2_a = vehicle_control_DW_l.UnitDelay2_DSTATE_m;

  /* UnitDelay: '<S22>/Unit Delay3' */
  rtb_UnitDelay3_f = vehicle_control_DW_l.UnitDelay3_DSTATE_a;

  /* UnitDelay: '<S19>/Unit Delay' */
  rtb_UnitDelay_n = vehicle_control_DW_l.UnitDelay_DSTATE_j;

  /* UnitDelay: '<S19>/Unit Delay1' */
  rtb_UnitDelay1_k = vehicle_control_DW_l.UnitDelay1_DSTATE_j;

  /* UnitDelay: '<S19>/Unit Delay2' */
  rtb_UnitDelay2_gi = vehicle_control_DW_l.UnitDelay2_DSTATE_n;

  /* MATLAB Function: '<S19>/MATLAB Function' incorporates:
   *  Inport generated from: '<Root>/imu'
   *  UnitDelay: '<S19>/Unit Delay'
   *  UnitDelay: '<S19>/Unit Delay1'
   *  UnitDelay: '<S19>/Unit Delay2'
   *  UnitDelay: '<S19>/Unit Delay3'
   */
  rtb_y_n = ((((vehicle_control_DW_l.UnitDelay_DSTATE_j +
                vehicle_control_DW_l.UnitDelay1_DSTATE_j) +
               vehicle_control_DW_l.UnitDelay2_DSTATE_n) +
              vehicle_control_DW_l.UnitDelay3_DSTATE_m) +
             vehicle_control_U.imu.gyro.z) / 5.0;

  /* SampleTimeMath: '<S6>/TSamp'
   *
   * About '<S6>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp_d = rtb_y_n * 100.0;

  /* MATLAB Function: '<S22>/MATLAB Function' incorporates:
   *  Sum: '<S6>/Diff'
   *  UnitDelay: '<S22>/Unit Delay'
   *  UnitDelay: '<S22>/Unit Delay1'
   *  UnitDelay: '<S22>/Unit Delay2'
   *  UnitDelay: '<S22>/Unit Delay3'
   *  UnitDelay: '<S22>/Unit Delay4'
   *  UnitDelay: '<S6>/UD'
   *
   * Block description for '<S6>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S6>/UD':
   *
   *  Store in Global RAM
   */
  MATLABFunction(vehicle_control_DW_l.UnitDelay_DSTATE_c,
                 vehicle_control_DW_l.UnitDelay1_DSTATE_a,
                 vehicle_control_DW_l.UnitDelay2_DSTATE_m,
                 vehicle_control_DW_l.UnitDelay3_DSTATE_a,
                 vehicle_control_DW_l.UnitDelay4_DSTATE_m, rtb_TSamp_d -
                 vehicle_control_DW_l.UD_DSTATE_f, &rtb_y_k);

  /* UnitDelay: '<S26>/Unit Delay' */
  rtb_UnitDelay_k = vehicle_control_DW_l.UnitDelay_DSTATE_n;

  /* UnitDelay: '<S26>/Unit Delay1' */
  rtb_UnitDelay1_e = vehicle_control_DW_l.UnitDelay1_DSTATE_f;

  /* UnitDelay: '<S26>/Unit Delay2' */
  rtb_UnitDelay2_po = vehicle_control_DW_l.UnitDelay2_DSTATE_he;

  /* UnitDelay: '<S26>/Unit Delay3' */
  rtb_UnitDelay3_l = vehicle_control_DW_l.UnitDelay3_DSTATE_f;

  /* UnitDelay: '<S26>/Unit Delay4' */
  rtb_UnitDelay4_l = vehicle_control_DW_l.UnitDelay4_DSTATE_j;

  /* UnitDelay: '<S26>/Unit Delay5' */
  rtb_UnitDelay5 = vehicle_control_DW_l.UnitDelay5_DSTATE;

  /* MATLAB Function: '<S26>/MATLAB Function' incorporates:
   *  Inport generated from: '<Root>/imu'
   *  UnitDelay: '<S26>/Unit Delay'
   *  UnitDelay: '<S26>/Unit Delay1'
   *  UnitDelay: '<S26>/Unit Delay2'
   *  UnitDelay: '<S26>/Unit Delay3'
   *  UnitDelay: '<S26>/Unit Delay4'
   *  UnitDelay: '<S26>/Unit Delay5'
   *  UnitDelay: '<S26>/Unit Delay6'
   */
  MATLABFunction_f(vehicle_control_DW_l.UnitDelay_DSTATE_n,
                   vehicle_control_DW_l.UnitDelay1_DSTATE_f,
                   vehicle_control_DW_l.UnitDelay2_DSTATE_he,
                   vehicle_control_DW_l.UnitDelay3_DSTATE_f,
                   vehicle_control_DW_l.UnitDelay4_DSTATE_j,
                   vehicle_control_DW_l.UnitDelay5_DSTATE,
                   vehicle_control_DW_l.UnitDelay6_DSTATE,
                   vehicle_control_U.imu.accel.y, &rtb_y);

  /* MATLAB Function: '<S18>/MATLAB Function3' incorporates:
   *  Inport generated from: '<Root>/states'
   */
  rtb_F_aero = vehicle_control_U.states.velocity.x *
    vehicle_control_U.states.velocity.x * 0.6125 * 2.2;

  /* UnitDelay: '<S25>/Unit Delay' */
  rtb_UnitDelay_ju = vehicle_control_DW_l.UnitDelay_DSTATE_cq;

  /* UnitDelay: '<S25>/Unit Delay1' */
  rtb_UnitDelay1_g = vehicle_control_DW_l.UnitDelay1_DSTATE_e;

  /* UnitDelay: '<S25>/Unit Delay2' */
  rtb_UnitDelay2_c = vehicle_control_DW_l.UnitDelay2_DSTATE_c;

  /* UnitDelay: '<S25>/Unit Delay3' */
  rtb_UnitDelay3_i = vehicle_control_DW_l.UnitDelay3_DSTATE_n;

  /* UnitDelay: '<S25>/Unit Delay4' */
  rtb_UnitDelay4_k = vehicle_control_DW_l.UnitDelay4_DSTATE_jj;

  /* UnitDelay: '<S25>/Unit Delay5' */
  rtb_UnitDelay5_i = vehicle_control_DW_l.UnitDelay5_DSTATE_f;

  /* MATLAB Function: '<S25>/MATLAB Function' incorporates:
   *  Inport generated from: '<Root>/imu'
   *  UnitDelay: '<S25>/Unit Delay'
   *  UnitDelay: '<S25>/Unit Delay1'
   *  UnitDelay: '<S25>/Unit Delay2'
   *  UnitDelay: '<S25>/Unit Delay3'
   *  UnitDelay: '<S25>/Unit Delay4'
   *  UnitDelay: '<S25>/Unit Delay5'
   *  UnitDelay: '<S25>/Unit Delay6'
   */
  MATLABFunction_f(vehicle_control_DW_l.UnitDelay_DSTATE_cq,
                   vehicle_control_DW_l.UnitDelay1_DSTATE_e,
                   vehicle_control_DW_l.UnitDelay2_DSTATE_c,
                   vehicle_control_DW_l.UnitDelay3_DSTATE_n,
                   vehicle_control_DW_l.UnitDelay4_DSTATE_jj,
                   vehicle_control_DW_l.UnitDelay5_DSTATE_f,
                   vehicle_control_DW_l.UnitDelay6_DSTATE_m,
                   vehicle_control_U.imu.accel.x, &rtb_y_g);

  /* Gain: '<S18>/Gain' incorporates:
   *  MATLAB Function: '<S18>/MATLAB Function2'
   */
  rtb_Gain = 0.18749999999999997 * rtb_y_g * 307.0 * 0.5;

  /* MATLAB Function: '<S18>/MATLAB Function1' */
  rtb_F_dy = 0.24193548387096772 * rtb_y * 307.0;

  /* Lookup_n-D: '<S18>/1-D Lookup Table' */
  rtb_uDLookupTable = look1_binlc(rtb_F_dy, rtCP_uDLookupTable_bp01Data,
    rtCP_uDLookupTable_tableData, 2U);

  /* Sum: '<S18>/Subtract' */
  rtb_Switch2_f = rtb_F_dy - rtb_uDLookupTable;

  /* MATLAB Function: '<S18>/MATLAB Function4' */
  rtb_FzFR = rtb_F_aero * 0.48 / 2.0;
  rtb_F_dy = ((658.56000000000006 - rtb_Gain) - rtb_Switch2_f) + rtb_FzFR;
  rtb_FzFR += (658.56000000000006 - rtb_Gain) + rtb_Switch2_f;
  rtb_Switch2_g_tmp = rtb_F_aero * 0.52 / 2.0;
  rtb_Switch2_f = ((rtb_Gain + 909.43999999999994) - rtb_uDLookupTable) +
    rtb_Switch2_g_tmp;
  rtb_uDLookupTable = ((rtb_Gain + 909.43999999999994) + rtb_uDLookupTable) +
    rtb_Switch2_g_tmp;

  /* Abs: '<S2>/Abs3' */
  rtb_rate_lo_o = fabs(rtb_rate_lo_o);

  /* MATLAB Function: '<S2>/MATLAB Function8' */
  if (rtb_y >= 1.0) {
    rtb_ratio = ((((((((rtb_y_g * rtb_y_g * 9.7E-5 + rtb_y * rtb_y * -0.00035) +
                       rtb_rate_lo_o * rtb_rate_lo_o * -0.049471) + 0.000939 *
                      rtb_y_g * rtb_y) + -0.01124 * rtb_y_g * rtb_rate_lo_o) +
                    -0.002413 * rtb_y * rtb_rate_lo_o) + 0.033397 * rtb_y_g) +
                  0.001481 * rtb_y) + 0.108267 * rtb_rate_lo_o) + 0.793474;
  } else if (rtb_y <= -1.0) {
    rtb_ratio = ((((((((rtb_y_g * rtb_y_g * -0.000251 + rtb_y * rtb_y *
                        -0.000919) + rtb_rate_lo_o * rtb_rate_lo_o * 0.094683) +
                      0.001845 * rtb_y_g * rtb_y) + 0.036116 * rtb_y_g *
                     rtb_rate_lo_o) + 0.00389 * rtb_y * rtb_rate_lo_o) +
                   0.014372 * rtb_y_g) + -0.009646 * rtb_y) + -0.139092 *
                 rtb_rate_lo_o) + 0.882179;
  } else {
    rtb_Sum = rtb_y_g * rtb_y_g;
    rtb_F_aero = rtb_rate_lo_o * rtb_rate_lo_o;
    rtb_ratio = ((((((((((rtb_Sum * 9.7E-5 - 0.00035) + rtb_F_aero * -0.049471)
                        + 0.000939 * rtb_y_g) + -0.01124 * rtb_y_g *
                       rtb_rate_lo_o) + -0.002413 * rtb_rate_lo_o) + 0.033397 *
                     rtb_y_g) + 0.001481) + 0.108267 * rtb_rate_lo_o) + 0.793474)
                 * (rtb_y + 1.0) + (((((((((rtb_Sum * -0.000251 - 0.000919) +
      rtb_F_aero * 0.094683) - 0.001845 * rtb_y_g) + 0.036116 * rtb_y_g *
      rtb_rate_lo_o) + -0.00389 * rtb_rate_lo_o) + 0.014372 * rtb_y_g) +
      0.009646) + -0.139092 * rtb_rate_lo_o) + 0.882179) * (1.0 - rtb_y)) / 2.0;
  }

  /* End of MATLAB Function: '<S2>/MATLAB Function8' */

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  Constant: '<S2>/Constant2'
   */
  rtb_rate_lo_o = (((rtb_F_dy * rtb_F_dy * -0.00059 + 1.46113 * rtb_F_dy) +
                    17.01657) * 0.66 + ((rtb_FzFR * rtb_FzFR * -0.00059 +
    1.46113 * rtb_FzFR) + 17.01657) * 0.66) * rtb_ratio;
  rtb_F_aero = ((rtb_Switch2_f * rtb_Switch2_f * -0.00059 + 1.46113 *
                 rtb_Switch2_f) + 17.01657) * 0.66 + ((rtb_uDLookupTable *
    rtb_uDLookupTable * -0.00059 + 1.46113 * rtb_uDLookupTable) + 17.01657) *
    0.66;

  /* MATLAB Function: '<S2>/MATLAB Function3' incorporates:
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S2>/MATLAB Function'
   *  MATLAB Function: '<S2>/MATLAB Function7'
   */
  rtb_Gain = rtb_UnitConversion;
  rtb_F_dy = rtb_rate_lo_o;
  rtb_FzFR = rtb_F_aero;
  rtb_Switch2_f = fabs(rtb_UnitConversion);
  if (rtb_Switch2_f < 0.087266462599716474) {
    rtb_Gain = 0.087266462599716474;
  }

  rtb_uDLookupTable = cos(rtb_Gain);
  rtb_rate_limit = 0.672 / rtb_rate_lo_o;
  rtb_Memory = 0.92799999999999994 / rtb_F_aero;
  rtb_Gain = 1.0 / cos(rtb_Gain - (rtb_rate_limit / rtb_uDLookupTable -
    rtb_Memory) * (320.0 * rtb_y / 1.6));
  rtb_Sum = 1.0 / rtb_rate_lo_o;
  rtb_F_aero = 1.0 / rtb_F_aero;
  rtb_ratio = (rtb_Sum / rtb_uDLookupTable + rtb_F_aero) *
    (vehicle_control_U.states.velocity.x / 1.6 * (rtb_Gain * rtb_Gain)) / 1.6;

  /* End of MATLAB Function: '<S2>/MATLAB Function3' */

  /* MATLAB Function: '<S2>/MATLAB Function1' incorporates:
   *  Sum: '<S2>/Subtract'
   *  Switch: '<S2>/Switch4'
   */
  rtb_Switch2_g_tmp = rtb_y_ft - rtb_y_n;

  /* MATLAB Function: '<S2>/MATLAB Function4' incorporates:
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S2>/MATLAB Function1'
   */
  MATLABFunction4(vehicle_control_U.states.velocity.x, rtb_Switch2_g_tmp /
                  rtb_ratio, &rtb_FzFR);

  /* DiscreteIntegrator: '<S2>/Discrete-Time Integrator1' incorporates:
   *  MATLAB Function: '<S2>/MATLAB Function7'
   */
  if (rtb_Switch2_f < 0.087266462599716474) {
    vehicle_control_DW_l.DiscreteTimeIntegrator1_DSTATE = 0.0;
  }

  /* MATLAB Function: '<S2>/MATLAB Function6' incorporates:
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator1'
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S2>/MATLAB Function5'
   */
  MATLABFunction4(vehicle_control_U.states.velocity.x,
                  vehicle_control_DW_l.DiscreteTimeIntegrator1_DSTATE /
                  rtb_ratio / 0.1, &rtb_F_dy);

  /* MATLAB Function: '<S2>/MATLAB Function' */
  rtb_UnitConversion = cos(rtb_UnitConversion);

  /* Gain: '<S2>/Gain2' incorporates:
   *  Sum: '<S2>/Subtract3'
   */
  rtb_rate_lo_o = (rtb_y_j5 - rtb_y_k) * 51.0;

  /* Saturate: '<S2>/Saturation1' */
  if (rtb_rate_lo_o > 300.0) {
    rtb_rate_lo_o = 300.0;
  } else if (rtb_rate_lo_o < -300.0) {
    rtb_rate_lo_o = -300.0;
  }

  /* Product: '<S17>/Product' incorporates:
   *  Constant: '<S17>/track'
   *  Constant: '<S17>/wheel radius'
   *  Gain: '<S2>/FF_Gain'
   *  Gain: '<S2>/Kd'
   *  Gain: '<S2>/Ki'
   *  Gain: '<S2>/Kp'
   *  MATLAB Function: '<S2>/MATLAB Function'
   *  Product: '<S17>/Divide'
   *  Saturate: '<S2>/Saturation1'
   *  Sum: '<S2>/Sum2'
   */
  rtb_F_dy = ((((rtb_rate_limit / rtb_UnitConversion - rtb_Memory) * 200.0 *
                rtb_y / (rtb_Sum / rtb_UnitConversion + rtb_F_aero) * 1.6 *
                ff_gain + Kd * rtb_rate_lo_o) + Kp * rtb_FzFR) + Ki * rtb_F_dy) /
    1.24 * 0.254;

  /* Saturate: '<S2>/Saturation' */
  if (rtb_F_dy > 200.0) {
    rtb_F_dy = 200.0;
  } else if (rtb_F_dy < -200.0) {
    rtb_F_dy = -200.0;
  }

  /* End of Saturate: '<S2>/Saturation' */

  /* Switch: '<S2>/Switch2' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Inport generated from: '<Root>/cockpit'
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S2>/MATLAB Function2'
   */
  if (vehicle_control_U.cockpit.brake > 0.1) {
    rtb_ratio = 0.0;
  } else if (vehicle_control_U.states.velocity.x > 4.0) {
    /* MATLAB Function: '<S2>/MATLAB Function2' */
    rtb_ratio = rtb_F_dy;
  } else if ((vehicle_control_U.states.velocity.x <= 4.0) &&
             (vehicle_control_U.states.velocity.x > 2.0)) {
    /* MATLAB Function: '<S2>/MATLAB Function2' incorporates:
     *  Inport generated from: '<Root>/states'
     */
    rtb_ratio = (vehicle_control_U.states.velocity.x - 2.0) * rtb_F_dy / 2.0;
  } else {
    rtb_ratio = 0.0;
  }

  /* End of Switch: '<S2>/Switch2' */

  /* Gain: '<Root>/Gain2' incorporates:
   *  Inport generated from: '<Root>/cockpit'
   */
  rtb_Switch2_f = 0.01 * vehicle_control_U.cockpit.accel;

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<S2>/Constant'
   *  Gain: '<S2>/Gain'
   *  Product: '<S2>/Product'
   */
  rtb_Sum = torq_lim * rtb_Switch2_f * 13.1 - rtb_ratio;

  /* Abs: '<S23>/Abs1' incorporates:
   *  Memory: '<S23>/Memory'
   */
  rtb_F_aero = fabs(vehicle_control_DW_l.Memory_PreviousInput);

  /* MATLAB Function: '<S2>/SR' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  Gain: '<S2>/Gain5'
   *  Gain: '<S2>/Gain6'
   *  Inport generated from: '<Root>/states'
   *  Inport generated from: '<Root>/wheel'
   *  UnitConversion: '<S3>/Unit Conversion'
   *  UnitConversion: '<S4>/Unit Conversion'
   */
  /* Unit Conversion - from: rpm to: rad/s
     Expression: output = (0.10472*input) + (0) */
  rtb_UnitConversion = rtb_y_n * 0.62;
  rtb_rate_lo_o = rtb_UnitConversion + vehicle_control_U.states.velocity.x;
  rtb_F_dy = vehicle_control_U.states.velocity.x - rtb_UnitConversion;
  if (vehicle_control_U.states.velocity.x < 2.0) {
    rtb_Gain = 0.0;
    rtb_F_dy = 0.0;
  } else {
    rtb_Gain = (13.1 * vehicle_control_U.wheel.speed.rr * 0.10471975511965977 *
                0.076335877862595422 / 13.1 * 0.254 - rtb_rate_lo_o) /
      rtb_rate_lo_o;
    rtb_F_dy = (13.1 * vehicle_control_U.wheel.speed.rl * 0.10471975511965977 *
                0.076335877862595422 / 13.1 * 0.254 - rtb_F_dy) / rtb_F_dy;
  }

  /* End of MATLAB Function: '<S2>/SR' */

  /* Abs: '<S2>/Abs1' */
  rtb_F_dy = fabs(rtb_F_dy);

  /* MATLAB Function: '<S23>/MATLAB Function' incorporates:
   *  Abs: '<S23>/Abs'
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant4'
   */
  if ((rtb_F_dy > 0.1) && (rtb_F_dy <= 0.12)) {
    rtb_UnitConversion = 1.0;
  } else if ((rtb_F_dy > 0.12) && (rtb_F_dy <= 0.15)) {
    rtb_F_aero -= 0.5;
    rtb_UnitConversion = 1.0;
  } else if (rtb_F_dy > 0.15) {
    rtb_F_aero--;
    rtb_UnitConversion = 1.0;
  } else {
    rtb_F_aero = fabs(rtb_Sum);
    rtb_UnitConversion = 0.0;
  }

  /* End of MATLAB Function: '<S23>/MATLAB Function' */

  /* MATLAB Function: '<S23>/MATLAB Function1' incorporates:
   *  Memory: '<S23>/Memory2'
   *  Memory: '<S23>/Memory3'
   */
  MATLABFunction1(rtb_UnitConversion, vehicle_control_DW_l.Memory2_PreviousInput,
                  vehicle_control_DW_l.Memory3_PreviousInput, &rtb_rate_limit,
                  &rtb_F_dy);

  /* MATLAB Function: '<S23>/MATLAB Function2' */
  MATLABFunction2(rtb_Sum, rtb_rate_limit, &rtb_uDLookupTable, &rtb_FzFR);

  /* Product: '<S40>/delta rise limit' incorporates:
   *  SampleTimeMath: '<S40>/sample time'
   *
   * About '<S40>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_rate_lo_o = rtb_uDLookupTable * 0.01;

  /* Saturate: '<S23>/Saturation' */
  if (rtb_F_aero <= 0.0) {
    rtb_F_aero = 0.0;
  }

  /* End of Saturate: '<S23>/Saturation' */

  /* Switch: '<S41>/Switch2' incorporates:
   *  RelationalOperator: '<S41>/LowerRelop1'
   */
  if (!(rtb_Sum > rtb_F_aero)) {
    /* Gain: '<S23>/Gain' */
    rtb_F_aero = -rtb_F_aero;

    /* Switch: '<S41>/Switch' incorporates:
     *  RelationalOperator: '<S41>/UpperRelop'
     */
    if (!(rtb_Sum < rtb_F_aero)) {
      rtb_F_aero = rtb_Sum;
    }

    /* End of Switch: '<S41>/Switch' */
  }

  /* End of Switch: '<S41>/Switch2' */

  /* Delay: '<S40>/Delay' */
  if (vehicle_control_DW_l.icLoad) {
    vehicle_control_DW_l.Delay_DSTATE = rtb_F_aero;
  }

  /* Sum: '<S40>/Difference Inputs1' incorporates:
   *  Delay: '<S40>/Delay'
   *
   * Block description for '<S40>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_uDLookupTable = rtb_F_aero - vehicle_control_DW_l.Delay_DSTATE;

  /* Switch: '<S42>/Switch2' incorporates:
   *  RelationalOperator: '<S42>/LowerRelop1'
   */
  if (!(rtb_uDLookupTable > rtb_rate_lo_o)) {
    /* Product: '<S40>/delta fall limit' incorporates:
     *  SampleTimeMath: '<S40>/sample time'
     *
     * About '<S40>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_rate_lo_o = 0.01 * rtb_FzFR;

    /* Switch: '<S42>/Switch' incorporates:
     *  RelationalOperator: '<S42>/UpperRelop'
     */
    if (!(rtb_uDLookupTable < rtb_rate_lo_o)) {
      rtb_rate_lo_o = rtb_uDLookupTable;
    }

    /* End of Switch: '<S42>/Switch' */
  }

  /* End of Switch: '<S42>/Switch2' */

  /* Sum: '<S40>/Difference Inputs2' incorporates:
   *  Delay: '<S40>/Delay'
   *
   * Block description for '<S40>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_FzFR = rtb_rate_lo_o + vehicle_control_DW_l.Delay_DSTATE;

  /* Switch: '<S2>/Switch3' incorporates:
   *  Constant: '<S2>/Constant5'
   *  Constant: '<S2>/TC_Switch'
   *  Inport generated from: '<Root>/cockpit'
   */
  if (vehicle_control_U.cockpit.brake > 0.05) {
    rtb_Memory = 0.0;
  } else {
    rtb_Memory = tc_switch;
  }

  /* End of Switch: '<S2>/Switch3' */

  /* Switch: '<S2>/Switch' */
  if (rtb_Memory > 0.0) {
    rtb_Sum = rtb_FzFR;
  }

  /* Gain: '<Root>/Gain3' incorporates:
   *  Switch: '<S2>/Switch'
   */
  vehicle_control_Y.torq.torque.rl = 0.076335877862595422 * rtb_Sum;

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S2>/Constant'
   *  Gain: '<S2>/Gain1'
   *  Product: '<S2>/Product1'
   */
  rtb_ratio += rtb_Switch2_f * torq_lim * 13.1;

  /* Abs: '<S24>/Abs1' incorporates:
   *  Memory: '<S24>/Memory'
   */
  rtb_rate_lo_o = fabs(vehicle_control_DW_l.Memory_PreviousInput_d);

  /* Abs: '<S2>/Abs2' */
  rtb_Switch2_f = fabs(rtb_Gain);

  /* MATLAB Function: '<S24>/MATLAB Function' incorporates:
   *  Abs: '<S24>/Abs'
   *  Constant: '<S2>/Constant3'
   *  Constant: '<S2>/Constant4'
   */
  if ((rtb_Switch2_f > 0.1) && (rtb_Switch2_f <= 0.12)) {
    rtb_Gain = 1.0;
  } else if ((rtb_Switch2_f > 0.12) && (rtb_Switch2_f <= 0.15)) {
    rtb_rate_lo_o -= 0.5;
    rtb_Gain = 1.0;
  } else if (rtb_Switch2_f > 0.15) {
    rtb_rate_lo_o--;
    rtb_Gain = 1.0;
  } else {
    rtb_rate_lo_o = fabs(rtb_ratio);
    rtb_Gain = 0.0;
  }

  /* End of MATLAB Function: '<S24>/MATLAB Function' */

  /* Saturate: '<S24>/Saturation' */
  if (rtb_rate_lo_o <= 0.0) {
    rtb_Sum = 0.0;
  } else {
    rtb_Sum = rtb_rate_lo_o;
  }

  /* End of Saturate: '<S24>/Saturation' */

  /* Switch: '<S47>/Switch2' incorporates:
   *  RelationalOperator: '<S47>/LowerRelop1'
   */
  if (!(rtb_ratio > rtb_Sum)) {
    /* Gain: '<S24>/Gain' */
    rtb_rate_lo_o = -rtb_Sum;

    /* Switch: '<S47>/Switch' incorporates:
     *  Gain: '<S24>/Gain'
     *  RelationalOperator: '<S47>/UpperRelop'
     */
    if (rtb_ratio < -rtb_Sum) {
      rtb_Sum = -rtb_Sum;
    } else {
      rtb_Sum = rtb_ratio;
    }

    /* End of Switch: '<S47>/Switch' */
  }

  /* End of Switch: '<S47>/Switch2' */

  /* Delay: '<S46>/Delay' */
  if (vehicle_control_DW_l.icLoad_n) {
    vehicle_control_DW_l.Delay_DSTATE_f = rtb_Sum;
  }

  /* MATLAB Function: '<S24>/MATLAB Function1' incorporates:
   *  Memory: '<S24>/Memory2'
   *  Memory: '<S24>/Memory3'
   */
  MATLABFunction1(rtb_Gain, vehicle_control_DW_l.Memory2_PreviousInput_e,
                  vehicle_control_DW_l.Memory3_PreviousInput_c, &rtb_rate_limit,
                  &rtb_uDLookupTable);

  /* MATLAB Function: '<S24>/MATLAB Function2' */
  MATLABFunction2(rtb_ratio, rtb_rate_limit, &rtb_Switch2_f, &rtb_rate_lo_o);

  /* Product: '<S46>/delta rise limit' incorporates:
   *  SampleTimeMath: '<S46>/sample time'
   *
   * About '<S46>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Switch2_f *= 0.01;

  /* Sum: '<S46>/Difference Inputs1' incorporates:
   *  Delay: '<S46>/Delay'
   *
   * Block description for '<S46>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_rate_limit = rtb_Sum - vehicle_control_DW_l.Delay_DSTATE_f;

  /* Switch: '<S48>/Switch2' incorporates:
   *  RelationalOperator: '<S48>/LowerRelop1'
   */
  if (!(rtb_rate_limit > rtb_Switch2_f)) {
    /* Product: '<S46>/delta fall limit' incorporates:
     *  SampleTimeMath: '<S46>/sample time'
     *
     * About '<S46>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_rate_lo_o *= 0.01;

    /* Switch: '<S48>/Switch' incorporates:
     *  RelationalOperator: '<S48>/UpperRelop'
     */
    if (rtb_rate_limit < rtb_rate_lo_o) {
      rtb_Switch2_f = rtb_rate_lo_o;
    } else {
      rtb_Switch2_f = rtb_rate_limit;
    }

    /* End of Switch: '<S48>/Switch' */
  }

  /* End of Switch: '<S48>/Switch2' */

  /* Sum: '<S46>/Difference Inputs2' incorporates:
   *  Delay: '<S46>/Delay'
   *
   * Block description for '<S46>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_rate_lo_o = rtb_Switch2_f + vehicle_control_DW_l.Delay_DSTATE_f;

  /* Switch: '<S2>/Switch1' */
  if (rtb_Memory > 0.0) {
    rtb_ratio = rtb_rate_lo_o;
  }

  /* Gain: '<Root>/Gain4' incorporates:
   *  Switch: '<S2>/Switch1'
   */
  vehicle_control_Y.torq.torque.rr = 0.076335877862595422 * rtb_ratio;

  /* BusCreator generated from: '<Root>/torq_BusCreator' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   */
  vehicle_control_Y.torq.torque.fl = 0.0;
  vehicle_control_Y.torq.torque.fr = 0.0;

  /* BusCreator generated from: '<Root>/torq_BusCreator' incorporates:
   *  Constant: '<Root>/Constant'
   */
  vehicle_control_Y.torq.header.timestamp_ns = 0ULL;

  /* Abs: '<S2>/Abs4' incorporates:
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator1'
   */
  rtb_Switch2_f = fabs(vehicle_control_DW_l.DiscreteTimeIntegrator1_DSTATE);

  /* BusCreator generated from: '<Root>/tc_BusCreator' incorporates:
   *  Constant: '<Root>/Constant3'
   */
  vehicle_control_Y.tc.header.timestamp_ns = 0ULL;

  /* BusCreator generated from: '<Root>/tc_BusCreator' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Constant: '<Root>/Constant5'
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant7'
   *  Constant: '<Root>/Constant8'
   *  Outport: '<Root>/tc'
   */
  vehicle_control_Y.tc.sr_l = 0.0;
  vehicle_control_Y.tc.sr_r = 0.0;
  vehicle_control_Y.tc.sa = 0.0;
  vehicle_control_Y.tc.yawrate_real = 0.0;
  vehicle_control_Y.tc.yawrate_ref = 0.0;

  /* Update for UnitDelay: '<S20>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE = rtb_y_ft;

  /* Update for UnitDelay: '<S20>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE = rtb_UnitDelay;

  /* Update for UnitDelay: '<S20>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE = rtb_UnitDelay1;

  /* Update for UnitDelay: '<S5>/UD'
   *
   * Block description for '<S5>/UD':
   *
   *  Store in Global RAM
   */
  vehicle_control_DW_l.UD_DSTATE = rtb_TSamp;

  /* Update for UnitDelay: '<S21>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_d = rtb_y_j5;

  /* Update for UnitDelay: '<S21>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_b = rtb_UnitDelay_c;

  /* Update for UnitDelay: '<S21>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_h = rtb_UnitDelay1_c;

  /* Update for UnitDelay: '<S21>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE = rtb_UnitDelay2_i;

  /* Update for UnitDelay: '<S21>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE = rtb_UnitDelay3;

  /* Update for UnitDelay: '<S22>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_c = rtb_y_k;

  /* Update for UnitDelay: '<S22>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_a = rtb_UnitDelay_m;

  /* Update for UnitDelay: '<S22>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_m = rtb_UnitDelay1_oo;

  /* Update for UnitDelay: '<S22>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_a = rtb_UnitDelay2_a;

  /* Update for UnitDelay: '<S22>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_m = rtb_UnitDelay3_f;

  /* Update for UnitDelay: '<S19>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_j = rtb_y_n;

  /* Update for UnitDelay: '<S19>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_j = rtb_UnitDelay_n;

  /* Update for UnitDelay: '<S19>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_n = rtb_UnitDelay1_k;

  /* Update for UnitDelay: '<S19>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_m = rtb_UnitDelay2_gi;

  /* Update for UnitDelay: '<S6>/UD'
   *
   * Block description for '<S6>/UD':
   *
   *  Store in Global RAM
   */
  vehicle_control_DW_l.UD_DSTATE_f = rtb_TSamp_d;

  /* Update for UnitDelay: '<S26>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_n = rtb_y;

  /* Update for UnitDelay: '<S26>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_f = rtb_UnitDelay_k;

  /* Update for UnitDelay: '<S26>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_he = rtb_UnitDelay1_e;

  /* Update for UnitDelay: '<S26>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_f = rtb_UnitDelay2_po;

  /* Update for UnitDelay: '<S26>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_j = rtb_UnitDelay3_l;

  /* Update for UnitDelay: '<S26>/Unit Delay5' */
  vehicle_control_DW_l.UnitDelay5_DSTATE = rtb_UnitDelay4_l;

  /* Update for UnitDelay: '<S26>/Unit Delay6' */
  vehicle_control_DW_l.UnitDelay6_DSTATE = rtb_UnitDelay5;

  /* Update for UnitDelay: '<S25>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_cq = rtb_y_g;

  /* Update for UnitDelay: '<S25>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_e = rtb_UnitDelay_ju;

  /* Update for UnitDelay: '<S25>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_c = rtb_UnitDelay1_g;

  /* Update for UnitDelay: '<S25>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_n = rtb_UnitDelay2_c;

  /* Update for UnitDelay: '<S25>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_jj = rtb_UnitDelay3_i;

  /* Update for UnitDelay: '<S25>/Unit Delay5' */
  vehicle_control_DW_l.UnitDelay5_DSTATE_f = rtb_UnitDelay4_k;

  /* Update for UnitDelay: '<S25>/Unit Delay6' */
  vehicle_control_DW_l.UnitDelay6_DSTATE_m = rtb_UnitDelay5_i;

  /* Switch: '<S2>/Switch4' incorporates:
   *  Constant: '<S2>/Constant6'
   *  Memory: '<S2>/Memory'
   */
  if (vehicle_control_DW_l.Memory_PreviousInput_o >= 0.04) {
    rtb_Switch2_g_tmp = 0.0;
  }

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator1' incorporates:
   *  Switch: '<S2>/Switch4'
   */
  vehicle_control_DW_l.DiscreteTimeIntegrator1_DSTATE += 0.01 *
    rtb_Switch2_g_tmp;

  /* Update for Memory: '<S23>/Memory' */
  vehicle_control_DW_l.Memory_PreviousInput = rtb_F_aero;

  /* Update for Memory: '<S23>/Memory2' */
  vehicle_control_DW_l.Memory2_PreviousInput = rtb_UnitConversion;

  /* Update for Memory: '<S23>/Memory3' */
  vehicle_control_DW_l.Memory3_PreviousInput = rtb_F_dy;

  /* Update for Delay: '<S40>/Delay' */
  vehicle_control_DW_l.icLoad = false;
  vehicle_control_DW_l.Delay_DSTATE = rtb_FzFR;

  /* Update for Memory: '<S24>/Memory' */
  vehicle_control_DW_l.Memory_PreviousInput_d = rtb_Sum;

  /* Update for Delay: '<S46>/Delay' */
  vehicle_control_DW_l.icLoad_n = false;
  vehicle_control_DW_l.Delay_DSTATE_f = rtb_rate_lo_o;

  /* Update for Memory: '<S24>/Memory2' */
  vehicle_control_DW_l.Memory2_PreviousInput_e = rtb_Gain;

  /* Update for Memory: '<S24>/Memory3' */
  vehicle_control_DW_l.Memory3_PreviousInput_c = rtb_uDLookupTable;

  /* Update for Memory: '<S2>/Memory' */
  vehicle_control_DW_l.Memory_PreviousInput_o = rtb_Switch2_f;
}

/* Model initialize function */
void vehicle_control_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(vehicle_control_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&vehicle_control_DW_l, 0,
                sizeof(vehicle_control_DW));

  /* external inputs */
  (void)memset(&vehicle_control_U, 0, sizeof(vehicle_control_ExtU));

  /* external outputs */
  (void)memset(&vehicle_control_Y, 0, sizeof(vehicle_control_ExtY));

  /* InitializeConditions for Delay: '<S40>/Delay' */
  vehicle_control_DW_l.icLoad = true;

  /* InitializeConditions for Delay: '<S46>/Delay' */
  vehicle_control_DW_l.icLoad_n = true;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
