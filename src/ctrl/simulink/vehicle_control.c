/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 5.19
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Sun Jul 12 17:40:04 2026
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
#include "rt_nonfinite.h"
#include <stdbool.h>
#include <stdint.h>
#include "look1_binlc.h"
#include "look1_binlx.h"
#include "look1_binlca.h"
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
extern const double rtCP_pooled_RXVSwQvYbp64[3];
extern const double rtCP_pooled_H9ZWZ4ADDsDZ[3];
extern const double rtCP_pooled_uwHIxEvoWXdL[24];
extern const double rtCP_pooled_8QUqjQztIgEy[24];
extern const double rtCP_pooled_H9OEu2SpkouB[23];
extern const double rtCP_pooled_PTMBB9DE4cTK[23];
extern const double rtCP_pooled_YP6SBkVgEhvQ[6];
extern const double rtCP_pooled_F2Efh38yzWKs[6];

#define rtCP_uDLookupTable_tableData   rtCP_pooled_RXVSwQvYbp64  /* Expression: [-826.04999999999995;0;826.04999999999995]
                                                                  * Referenced by: '<S30>/1-D Lookup Table'
                                                                  */
#define rtCP_uDLookupTable_bp01Data    rtCP_pooled_H9ZWZ4ADDsDZ  /* Expression: [-1424.3699999999999;0;1424.3699999999999]
                                                                  * Referenced by: '<S30>/1-D Lookup Table'
                                                                  */
#define rtCP_Steer_FL_tableData        rtCP_pooled_uwHIxEvoWXdL  /* Expression: [-21;-18;-16;-14;-12;-10;-8;-7;-5;-4;-3;-1;0;0;2;4;6;8;10;12;14;16;20;21]
                                                                  * Referenced by: '<S41>/Steer_FL'
                                                                  */
#define rtCP_Steer_FL_bp01Data         rtCP_pooled_8QUqjQztIgEy  /* Expression: [-121;-111;-100;-89;-79;-69;-59;-51;-40;-31;-21;-10;0;9;19;29;39;51;59;70;79;90;111;118]
                                                                  * Referenced by: '<S41>/Steer_FL'
                                                                  */
#define rtCP_Steer_FR_tableData        rtCP_pooled_H9OEu2SpkouB  /* Expression: [-20;-17;-16;-14;-12;-11;-9;-7;-5;-4;-2;0;1;3;5;7;9;11;13;15;17;20;24]
                                                                  * Referenced by: '<S41>/Steer_FR'
                                                                  */
#define rtCP_Steer_FR_bp01Data         rtCP_pooled_PTMBB9DE4cTK  /* Expression: [-110;-100;-90;-80;-70;-60;-50;-40;-30;-20;-10;0;10;20;30;40;50;60;70;80;90;100;110]
                                                                  * Referenced by: '<S41>/Steer_FR'
                                                                  */
#define rtCP_uDLookupTable5_tableData  rtCP_pooled_YP6SBkVgEhvQ  /* Expression: [20;20;17.08;13.33;8.75;1.67]
                                                                  * Referenced by: '<S3>/1-D Lookup Table5'
                                                                  */
#define rtCP_uDLookupTable5_bp01Data   rtCP_pooled_F2Efh38yzWKs  /* Expression: [0;12000;14000;16000;18000;20000]
                                                                  * Referenced by: '<S3>/1-D Lookup Table5'
                                                                  */
#define rtCP_uDLookupTable6_tableData  rtCP_pooled_YP6SBkVgEhvQ  /* Expression: [20;20;17.08;13.33;8.75;1.67]
                                                                  * Referenced by: '<S3>/1-D Lookup Table6'
                                                                  */
#define rtCP_uDLookupTable6_bp01Data   rtCP_pooled_F2Efh38yzWKs  /* Expression: [0;12000;14000;16000;18000;20000]
                                                                  * Referenced by: '<S3>/1-D Lookup Table6'
                                                                  */
#define rtCP_uDLookupTable7_tableData  rtCP_pooled_YP6SBkVgEhvQ  /* Expression: [20;20;17.08;13.33;8.75;1.67]
                                                                  * Referenced by: '<S3>/1-D Lookup Table7'
                                                                  */
#define rtCP_uDLookupTable7_bp01Data   rtCP_pooled_F2Efh38yzWKs  /* Expression: [0;12000;14000;16000;18000;20000]
                                                                  * Referenced by: '<S3>/1-D Lookup Table7'
                                                                  */
#define rtCP_uDLookupTable8_tableData  rtCP_pooled_YP6SBkVgEhvQ  /* Expression: [20;20;17.08;13.33;8.75;1.67]
                                                                  * Referenced by: '<S3>/1-D Lookup Table8'
                                                                  */
#define rtCP_uDLookupTable8_bp01Data   rtCP_pooled_F2Efh38yzWKs  /* Expression: [0;12000;14000;16000;18000;20000]
                                                                  * Referenced by: '<S3>/1-D Lookup Table8'
                                                                  */

static void MATLABFunction14(double rtu_v, double rtu_delta_trq, double *rty_y);
static void MATLABFunction(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_u, double
  *rty_y);
static void MATLABFunction1(double rtu_TC, double rtu_TC_last, double
  rtu_count_last, double *rty_rate_limit, double *rty_count);
static void MATLABFunction2(double rtu_trq, double rtu_rate_limit, double
  *rty_rate_up, double *rty_rate_lo);
static void MATLABFunction_d(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_last_y_6,
  double rtu_last_y_7, double rtu_u, double *rty_y);

/*
 * Output and update for atomic system:
 *    '<S3>/MATLAB Function14'
 *    '<S3>/MATLAB Function18'
 */
static void MATLABFunction14(double rtu_v, double rtu_delta_trq, double *rty_y)
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
 *    '<S29>/MATLAB Function'
 *    '<S33>/MATLAB Function'
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
 *    '<S35>/MATLAB Function1'
 *    '<S36>/MATLAB Function1'
 *    '<S37>/MATLAB Function1'
 *    '<S38>/MATLAB Function1'
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
 *    '<S35>/MATLAB Function2'
 *    '<S36>/MATLAB Function2'
 *    '<S37>/MATLAB Function2'
 *    '<S38>/MATLAB Function2'
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
 *    '<S39>/MATLAB Function'
 *    '<S40>/MATLAB Function'
 *    '<S42>/MATLAB Function'
 *    '<S43>/MATLAB Function'
 *    '<S44>/MATLAB Function'
 *    '<S45>/MATLAB Function'
 */
static void MATLABFunction_d(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_last_y_6,
  double rtu_last_y_7, double rtu_u, double *rty_y)
{
  *rty_y = (((((((rtu_last_y_1 + rtu_last_y_2) + rtu_last_y_3) + rtu_last_y_4) +
               rtu_last_y_5) + rtu_last_y_6) + rtu_last_y_7) + rtu_u) / 8.0;
}

/* Model step function */
void vehicle_control_step(void)
{
  double x[4];
  double Ffs;
  double Fz;
  double Fz_f;
  double Fz_r;
  double e;
  double e_tmp;
  double p_idx_1;
  double p_idx_2;
  double p_idx_3;
  double rtb_Abs6;
  double rtb_Abs7;
  double rtb_Add2;
  double rtb_Add3;
  double rtb_F_aero;
  double rtb_F_dy;
  double rtb_FzFL;
  double rtb_FzFR;
  double rtb_FzRL;
  double rtb_FzRR;
  double rtb_Gain;
  double rtb_Gain2;
  double rtb_Subtract;
  double rtb_Switch2_n0;
  double rtb_TSamp;
  double rtb_TSamp_l;
  double rtb_UnitConversion;
  double rtb_UnitDelay;
  double rtb_UnitDelay1;
  double rtb_UnitDelay1_f;
  double rtb_UnitDelay1_gt;
  double rtb_UnitDelay1_j;
  double rtb_UnitDelay1_n;
  double rtb_UnitDelay1_p;
  double rtb_UnitDelay1_pk;
  double rtb_UnitDelay2;
  double rtb_UnitDelay2_b;
  double rtb_UnitDelay2_e;
  double rtb_UnitDelay2_g;
  double rtb_UnitDelay2_h;
  double rtb_UnitDelay2_m;
  double rtb_UnitDelay2_p1;
  double rtb_UnitDelay3;
  double rtb_UnitDelay3_a;
  double rtb_UnitDelay3_a1;
  double rtb_UnitDelay3_d;
  double rtb_UnitDelay3_g;
  double rtb_UnitDelay3_j;
  double rtb_UnitDelay3_p;
  double rtb_UnitDelay4;
  double rtb_UnitDelay4_i;
  double rtb_UnitDelay4_j;
  double rtb_UnitDelay4_o;
  double rtb_UnitDelay4_p;
  double rtb_UnitDelay5;
  double rtb_UnitDelay5_f;
  double rtb_UnitDelay5_h;
  double rtb_UnitDelay5_ke;
  double rtb_UnitDelay5_p;
  double rtb_UnitDelay_ee;
  double rtb_UnitDelay_em;
  double rtb_UnitDelay_o;
  double rtb_count_m;
  double rtb_moment;
  double rtb_rate_lo_j;
  double rtb_rate_lo_m;
  double rtb_rate_lo_p;
  double rtb_ratio;
  double rtb_tmax_fl;
  double rtb_tmax_fr;
  double rtb_tmax_rl;
  double rtb_tmax_rr;
  double rtb_uDLookupTable;
  double rtb_y;
  double rtb_y_c;
  double rtb_y_cb;
  double rtb_y_d;
  double rtb_y_g;
  double rtb_y_h;
  double rtb_y_j0;
  double rtb_y_kb;
  double rtb_y_o;
  double t_f_mtr;
  double t_r_mtr;
  int32_t idx;
  int32_t k;
  bool b_free_idx_0;
  bool b_free_idx_1;
  bool b_free_idx_2;
  bool b_free_idx_3;
  bool exitg1;

  /* MATLAB Function: '<S30>/MATLAB Function3' incorporates:
   *  Inport generated from: '<Root>/states'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   */
  rtb_F_aero = vehicle_control_U.states.velocity.x *
    vehicle_control_U.states.velocity.x * 0.6125 * 2.0;

  /* UnitDelay: '<S39>/Unit Delay' */
  rtb_UnitDelay = vehicle_control_DW_l.UnitDelay_DSTATE;

  /* UnitDelay: '<S39>/Unit Delay1' */
  rtb_UnitDelay1 = vehicle_control_DW_l.UnitDelay1_DSTATE;

  /* UnitDelay: '<S39>/Unit Delay2' */
  rtb_UnitDelay2 = vehicle_control_DW_l.UnitDelay2_DSTATE;

  /* UnitDelay: '<S39>/Unit Delay3' */
  rtb_UnitDelay3 = vehicle_control_DW_l.UnitDelay3_DSTATE;

  /* UnitDelay: '<S39>/Unit Delay4' */
  rtb_UnitDelay4 = vehicle_control_DW_l.UnitDelay4_DSTATE;

  /* UnitDelay: '<S39>/Unit Delay5' */
  rtb_UnitDelay5 = vehicle_control_DW_l.UnitDelay5_DSTATE;

  /* MATLAB Function: '<S39>/MATLAB Function' incorporates:
   *  Inport generated from: '<Root>/imu'
   *  UnitDelay: '<S39>/Unit Delay'
   *  UnitDelay: '<S39>/Unit Delay1'
   *  UnitDelay: '<S39>/Unit Delay2'
   *  UnitDelay: '<S39>/Unit Delay3'
   *  UnitDelay: '<S39>/Unit Delay4'
   *  UnitDelay: '<S39>/Unit Delay5'
   *  UnitDelay: '<S39>/Unit Delay6'
   */
  MATLABFunction_d(vehicle_control_DW_l.UnitDelay_DSTATE,
                   vehicle_control_DW_l.UnitDelay1_DSTATE,
                   vehicle_control_DW_l.UnitDelay2_DSTATE,
                   vehicle_control_DW_l.UnitDelay3_DSTATE,
                   vehicle_control_DW_l.UnitDelay4_DSTATE,
                   vehicle_control_DW_l.UnitDelay5_DSTATE,
                   vehicle_control_DW_l.UnitDelay6_DSTATE,
                   vehicle_control_U.imu.accel.x, &rtb_y_kb);

  /* Gain: '<S30>/Gain' incorporates:
   *  Constant: '<S3>/CG_h'
   *  Constant: '<S3>/a'
   *  Constant: '<S3>/b'
   *  Constant: '<S3>/m'
   *  MATLAB Function: '<S30>/MATLAB Function2'
   */
  rtb_Gain = 0.201875 * rtb_y_kb * 350.25 * 0.5;

  /* UnitDelay: '<S40>/Unit Delay' */
  rtb_UnitDelay_em = vehicle_control_DW_l.UnitDelay_DSTATE_c;

  /* UnitDelay: '<S40>/Unit Delay1' */
  rtb_UnitDelay1_gt = vehicle_control_DW_l.UnitDelay1_DSTATE_h;

  /* UnitDelay: '<S40>/Unit Delay2' */
  rtb_UnitDelay2_p1 = vehicle_control_DW_l.UnitDelay2_DSTATE_p;

  /* UnitDelay: '<S40>/Unit Delay3' */
  rtb_UnitDelay3_d = vehicle_control_DW_l.UnitDelay3_DSTATE_e;

  /* UnitDelay: '<S40>/Unit Delay4' */
  rtb_UnitDelay4_o = vehicle_control_DW_l.UnitDelay4_DSTATE_p;

  /* UnitDelay: '<S40>/Unit Delay5' */
  rtb_UnitDelay5_ke = vehicle_control_DW_l.UnitDelay5_DSTATE_f;

  /* MATLAB Function: '<S40>/MATLAB Function' incorporates:
   *  Inport generated from: '<Root>/imu'
   *  UnitDelay: '<S40>/Unit Delay'
   *  UnitDelay: '<S40>/Unit Delay1'
   *  UnitDelay: '<S40>/Unit Delay2'
   *  UnitDelay: '<S40>/Unit Delay3'
   *  UnitDelay: '<S40>/Unit Delay4'
   *  UnitDelay: '<S40>/Unit Delay5'
   *  UnitDelay: '<S40>/Unit Delay6'
   */
  MATLABFunction_d(vehicle_control_DW_l.UnitDelay_DSTATE_c,
                   vehicle_control_DW_l.UnitDelay1_DSTATE_h,
                   vehicle_control_DW_l.UnitDelay2_DSTATE_p,
                   vehicle_control_DW_l.UnitDelay3_DSTATE_e,
                   vehicle_control_DW_l.UnitDelay4_DSTATE_p,
                   vehicle_control_DW_l.UnitDelay5_DSTATE_f,
                   vehicle_control_DW_l.UnitDelay6_DSTATE_a,
                   vehicle_control_U.imu.accel.y, &rtb_y_h);

  /* MATLAB Function: '<S30>/MATLAB Function1' incorporates:
   *  Constant: '<S3>/CG_h'
   *  Constant: '<S3>/m'
   */
  rtb_F_dy = 0.26048387096774195 * rtb_y_h * 350.25;

  /* Lookup_n-D: '<S30>/1-D Lookup Table' */
  rtb_uDLookupTable = look1_binlc(rtb_F_dy, rtCP_uDLookupTable_bp01Data,
    rtCP_uDLookupTable_tableData, 2U);

  /* Sum: '<S30>/Subtract' */
  rtb_Subtract = rtb_F_dy - rtb_uDLookupTable;

  /* MATLAB Function: '<S30>/MATLAB Function4' incorporates:
   *  Constant: '<S3>/COP_f'
   */
  rtb_FzFR = rtb_F_aero * 0.48 / 2.0;
  rtb_FzFL = ((754.8172078125 - rtb_Gain) - rtb_Subtract) + rtb_FzFR;
  rtb_FzFR += (754.8172078125 - rtb_Gain) + rtb_Subtract;
  rtb_F_aero = rtb_F_aero * 0.52 / 2.0;
  rtb_FzRL = ((rtb_Gain + 961.4077921875) - rtb_uDLookupTable) + rtb_F_aero;
  rtb_FzRR = ((rtb_Gain + 961.4077921875) + rtb_uDLookupTable) + rtb_F_aero;

  /* Sum: '<S3>/Add2' incorporates:
   *  MATLAB Function: '<S3>/System ID'
   */
  rtb_Add2 = (rtb_FzFL * rtb_FzFL * 0.02 + 0.0 * rtb_FzFL) + (rtb_FzFR *
    rtb_FzFR * 0.02 + 0.0 * rtb_FzFR);

  /* UnitConversion: '<S85>/Unit Conversion' incorporates:
   *  Gain: '<Root>/Gain9'
   *  Inport generated from: '<Root>/cockpit'
   *  UnitConversion: '<S1>/Unit Conversion'
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  /* Unit Conversion - from: rad to: deg
     Expression: output = (57.2958*input) + (0) */
  rtb_Switch2_n0 = -(0.017453292519943295 * vehicle_control_U.cockpit.steer) *
    57.295779513082323;

  /* UnitConversion: '<S82>/Unit Conversion' incorporates:
   *  Gain: '<S41>/Gain4'
   *  Lookup_n-D: '<S41>/Steer_FL'
   *  Lookup_n-D: '<S41>/Steer_FR'
   *  Sum: '<S41>/Add'
   *  Switch: '<S79>/Switch2'
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_UnitConversion = (look1_binlx(rtb_Switch2_n0, rtCP_Steer_FL_bp01Data,
    rtCP_Steer_FL_tableData, 23U) + look1_binlx(rtb_Switch2_n0,
    rtCP_Steer_FR_bp01Data, rtCP_Steer_FR_tableData, 22U)) * 0.5 *
    0.017453292519943295;

  /* Sum: '<S3>/Add3' incorporates:
   *  MATLAB Function: '<S3>/System ID'
   */
  rtb_Add3 = (rtb_FzRL * rtb_FzRL * 0.02 + 0.0 * rtb_FzRL) + (rtb_FzRR *
    rtb_FzRR * 0.02 + 0.0 * rtb_FzRR);

  /* UnitDelay: '<S33>/Unit Delay' */
  rtb_F_aero = vehicle_control_DW_l.UnitDelay_DSTATE_h;

  /* UnitDelay: '<S33>/Unit Delay1' */
  rtb_Gain = vehicle_control_DW_l.UnitDelay1_DSTATE_a;

  /* UnitDelay: '<S33>/Unit Delay2' */
  rtb_uDLookupTable = vehicle_control_DW_l.UnitDelay2_DSTATE_n;

  /* UnitDelay: '<S33>/Unit Delay3' */
  rtb_F_dy = vehicle_control_DW_l.UnitDelay3_DSTATE_o;

  /* UnitDelay: '<S32>/Unit Delay' */
  rtb_Subtract = vehicle_control_DW_l.UnitDelay_DSTATE_m;

  /* UnitDelay: '<S32>/Unit Delay1' */
  Ffs = vehicle_control_DW_l.UnitDelay1_DSTATE_f;

  /* MATLAB Function: '<S32>/MATLAB Function' incorporates:
   *  Constant: '<S3>/Ku_target'
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S47>/reference yaw rate'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   *  UnitDelay: '<S32>/Unit Delay'
   *  UnitDelay: '<S32>/Unit Delay1'
   *  UnitDelay: '<S32>/Unit Delay2'
   */
  rtb_y_d = (vehicle_control_U.states.velocity.x * rtb_UnitConversion /
             (vehicle_control_U.states.velocity.x *
              vehicle_control_U.states.velocity.x * 0.003 + 1.6) +
             ((vehicle_control_DW_l.UnitDelay_DSTATE_m +
               vehicle_control_DW_l.UnitDelay1_DSTATE_f) +
              vehicle_control_DW_l.UnitDelay2_DSTATE_pk)) / 4.0;

  /* SampleTimeMath: '<S8>/TSamp'
   *
   * About '<S8>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp = rtb_y_d * 100.0;

  /* MATLAB Function: '<S33>/MATLAB Function' incorporates:
   *  Sum: '<S8>/Diff'
   *  UnitDelay: '<S33>/Unit Delay'
   *  UnitDelay: '<S33>/Unit Delay1'
   *  UnitDelay: '<S33>/Unit Delay2'
   *  UnitDelay: '<S33>/Unit Delay3'
   *  UnitDelay: '<S33>/Unit Delay4'
   *  UnitDelay: '<S8>/UD'
   *
   * Block description for '<S8>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S8>/UD':
   *
   *  Store in Global RAM
   */
  MATLABFunction(vehicle_control_DW_l.UnitDelay_DSTATE_h,
                 vehicle_control_DW_l.UnitDelay1_DSTATE_a,
                 vehicle_control_DW_l.UnitDelay2_DSTATE_n,
                 vehicle_control_DW_l.UnitDelay3_DSTATE_o,
                 vehicle_control_DW_l.UnitDelay4_DSTATE_h, rtb_TSamp -
                 vehicle_control_DW_l.UD_DSTATE, &rtb_y_cb);

  /* UnitDelay: '<S29>/Unit Delay' */
  rtb_UnitDelay_o = vehicle_control_DW_l.UnitDelay_DSTATE_n;

  /* UnitDelay: '<S29>/Unit Delay1' */
  rtb_UnitDelay1_n = vehicle_control_DW_l.UnitDelay1_DSTATE_i;

  /* UnitDelay: '<S29>/Unit Delay2' */
  rtb_UnitDelay2_h = vehicle_control_DW_l.UnitDelay2_DSTATE_b;

  /* UnitDelay: '<S29>/Unit Delay3' */
  rtb_UnitDelay3_p = vehicle_control_DW_l.UnitDelay3_DSTATE_f;

  /* UnitDelay: '<S31>/Unit Delay' */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_UnitDelay_ee = vehicle_control_DW_l.UnitDelay_DSTATE_b;

  /* UnitDelay: '<S31>/Unit Delay1' */
  rtb_UnitDelay1_f = vehicle_control_DW_l.UnitDelay1_DSTATE_m;

  /* UnitDelay: '<S31>/Unit Delay2' */
  rtb_UnitDelay2_e = vehicle_control_DW_l.UnitDelay2_DSTATE_d;

  /* MATLAB Function: '<S31>/MATLAB Function' incorporates:
   *  Inport generated from: '<Root>/imu'
   *  UnitConversion: '<S2>/Unit Conversion'
   *  UnitDelay: '<S31>/Unit Delay'
   *  UnitDelay: '<S31>/Unit Delay1'
   *  UnitDelay: '<S31>/Unit Delay2'
   *  UnitDelay: '<S31>/Unit Delay3'
   */
  rtb_y_g = ((((vehicle_control_DW_l.UnitDelay_DSTATE_b +
                vehicle_control_DW_l.UnitDelay1_DSTATE_m) +
               vehicle_control_DW_l.UnitDelay2_DSTATE_d) +
              vehicle_control_DW_l.UnitDelay3_DSTATE_fs) + 0.017453292519943295 *
             vehicle_control_U.imu.gyro.z) / 5.0;

  /* SampleTimeMath: '<S9>/TSamp'
   *
   * About '<S9>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   *   */
  rtb_TSamp_l = rtb_y_g * 100.0;

  /* MATLAB Function: '<S29>/MATLAB Function' incorporates:
   *  Sum: '<S9>/Diff'
   *  UnitDelay: '<S29>/Unit Delay'
   *  UnitDelay: '<S29>/Unit Delay1'
   *  UnitDelay: '<S29>/Unit Delay2'
   *  UnitDelay: '<S29>/Unit Delay3'
   *  UnitDelay: '<S29>/Unit Delay4'
   *  UnitDelay: '<S9>/UD'
   *
   * Block description for '<S9>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S9>/UD':
   *
   *  Store in Global RAM
   */
  MATLABFunction(vehicle_control_DW_l.UnitDelay_DSTATE_n,
                 vehicle_control_DW_l.UnitDelay1_DSTATE_i,
                 vehicle_control_DW_l.UnitDelay2_DSTATE_b,
                 vehicle_control_DW_l.UnitDelay3_DSTATE_f,
                 vehicle_control_DW_l.UnitDelay4_DSTATE_o, rtb_TSamp_l -
                 vehicle_control_DW_l.UD_DSTATE_i, &rtb_y_o);

  /* MATLAB Function: '<S3>/FB_Kp' incorporates:
   *  Constant: '<S3>/Ku_target'
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S3>/FF'
   *  MATLAB Function: '<S3>/MATLAB Function19'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   */
  rtb_ratio = rtb_UnitConversion;
  rtb_moment = vehicle_control_U.states.velocity.x;
  e = rtb_y_g;
  if (rtb_y_g < 0.3) {
    e = 0.3;
  }

  if (vehicle_control_U.states.velocity.x < 2.0) {
    rtb_moment = 2.0;
  }

  rtb_UnitDelay3_j = fabs(rtb_UnitConversion);
  if (rtb_UnitDelay3_j < 0.087266462599716474) {
    if (rtIsNaN(rtb_UnitConversion)) {
      Fz_r = (rtNaN);
    } else if (rtb_UnitConversion < 0.0) {
      Fz_r = -1.0;
    } else {
      Fz_r = (rtb_UnitConversion > 0.0);
    }

    rtb_ratio = Fz_r * 5.0 * 3.1415926535897931 / 180.0;
  }

  rtb_Gain2 = rtb_moment * rtb_moment * 0.003 + 1.6;
  rtb_UnitDelay1_j = 1.0 / rtb_Add2 + 1.0 / rtb_Add3;
  rtb_ratio = fabs(rtb_ratio * rtb_moment / (rtb_Gain2 * rtb_Gain2) * rtb_moment
                   / e / 1.6 * rtb_UnitDelay1_j);

  /* End of MATLAB Function: '<S3>/FB_Kp' */

  /* MATLAB Function: '<S3>/FB_P' incorporates:
   *  Inport generated from: '<Root>/states'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   *  Sum: '<S3>/Subtract1'
   *  Switch: '<S3>/Switch10'
   */
  rtb_moment = rtb_ratio;
  e_tmp = rtb_y_d - rtb_y_g;
  e = e_tmp;
  if (fabs(e_tmp) < 0.005) {
    e = 0.0;
  }

  if (rtb_ratio < 0.001) {
    rtb_moment = 0.001;
  }

  rtb_moment = e / rtb_moment;
  if (vehicle_control_U.states.velocity.x < 2.0) {
    rtb_moment = 0.0;
  }

  if (rtb_moment > 300.0) {
    rtb_moment = 300.0;
  } else if (rtb_moment < -300.0) {
    rtb_moment = -300.0;
  }

  /* End of MATLAB Function: '<S3>/FB_P' */

  /* MATLAB Function: '<S3>/MATLAB Function14' incorporates:
   *  Inport generated from: '<Root>/states'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   */
  MATLABFunction14(vehicle_control_U.states.velocity.x, rtb_moment,
                   &rtb_rate_lo_j);

  /* DiscreteIntegrator: '<S3>/Discrete-Time Integrator2' incorporates:
   *  MATLAB Function: '<S3>/MATLAB Function19'
   */
  if (rtb_UnitDelay3_j < 0.087266462599716474) {
    vehicle_control_DW_l.DiscreteTimeIntegrator2_DSTATE = 0.0;
  }

  /* MATLAB Function: '<S3>/MATLAB Function18' incorporates:
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator2'
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S3>/FB_Ki1'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   */
  MATLABFunction14(vehicle_control_U.states.velocity.x,
                   vehicle_control_DW_l.DiscreteTimeIntegrator2_DSTATE /
                   rtb_ratio / 0.1, &rtb_count_m);

  /* Gain: '<S3>/yaw_inertia1' incorporates:
   *  Sum: '<S3>/Subtract2'
   */
  rtb_ratio = (rtb_y_cb - rtb_y_o) * 105.0;

  /* Saturate: '<S3>/Saturation6' */
  if (rtb_ratio > 300.0) {
    rtb_ratio = 300.0;
  } else if (rtb_ratio < -300.0) {
    rtb_ratio = -300.0;
  }

  /* Gain: '<S3>/TV_Gain' incorporates:
   *  Constant: '<S3>/Ku_target'
   *  Constant: '<S3>/a'
   *  Constant: '<S3>/b'
   *  Constant: '<S3>/m'
   *  Gain: '<S3>/FF_Gain'
   *  Gain: '<S3>/Kd'
   *  Gain: '<S3>/Ki'
   *  Gain: '<S3>/Kp'
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S3>/FF'
   *  Saturate: '<S3>/Saturation6'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Add2 = (((((0.7037 / rtb_Add2 - 0.8963 / rtb_Add3) * 350.25 *
                 (vehicle_control_U.states.velocity.x *
                  vehicle_control_U.states.velocity.x) / rtb_UnitDelay1_j *
                 rtb_UnitConversion / (vehicle_control_U.states.velocity.x *
    vehicle_control_U.states.velocity.x * 0.003 + 1.6) -
                 vehicle_control_U.states.velocity.x *
                 vehicle_control_U.states.velocity.x * 0.0048000000000000004 /
                 rtb_UnitDelay1_j * rtb_UnitConversion /
                 (vehicle_control_U.states.velocity.x *
                  vehicle_control_U.states.velocity.x * 0.003 + 1.6)) * ff_gain
                + Kd * rtb_ratio) + Kp * rtb_rate_lo_j) + Ki * rtb_count_m) *
    TV_gain;

  /* Switch: '<S3>/Switch8' incorporates:
   *  Constant: '<S3>/Constant11'
   *  Inport generated from: '<Root>/cockpit'
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S3>/MATLAB Function12'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   */
  if (vehicle_control_U.cockpit.brake > 0.1) {
    rtb_rate_lo_j = 0.0;
  } else if (vehicle_control_U.states.velocity.x > 4.0) {
    /* MATLAB Function: '<S3>/MATLAB Function12' */
    rtb_rate_lo_j = rtb_Add2;
  } else if ((vehicle_control_U.states.velocity.x <= 4.0) &&
             (vehicle_control_U.states.velocity.x > 2.0)) {
    /* MATLAB Function: '<S3>/MATLAB Function12' incorporates:
     *  Inport generated from: '<Root>/states'
     *  SignalConversion generated from: '<Root>/Bus Selector1'
     */
    rtb_rate_lo_j = (vehicle_control_U.states.velocity.x - 2.0) * rtb_Add2 / 2.0;
  } else {
    rtb_rate_lo_j = 0.0;
  }

  /* End of Switch: '<S3>/Switch8' */

  /* Abs: '<S3>/Abs3' incorporates:
   *  Gain: '<Root>/Gain5'
   *  Inport generated from: '<Root>/wheel'
   */
  rtb_count_m = fabs(-13.1 * vehicle_control_U.wheel.speed.fr);

  /* Gain: '<S3>/tmax_fl' incorporates:
   *  Abs: '<S3>/Abs3'
   *  Lookup_n-D: '<S3>/1-D Lookup Table5'
   */
  rtb_tmax_fl = tmax_fl * look1_binlca(rtb_count_m, rtCP_uDLookupTable5_bp01Data,
    rtCP_uDLookupTable5_tableData, 5U);

  /* Gain: '<Root>/Gain2' incorporates:
   *  Inport generated from: '<Root>/cockpit'
   */
  rtb_Gain2 = 0.01 * vehicle_control_U.cockpit.accel;

  /* UnitDelay: '<S42>/Unit Delay' */
  rtb_Add2 = vehicle_control_DW_l.UnitDelay_DSTATE_j;

  /* UnitDelay: '<S42>/Unit Delay1' */
  rtb_UnitConversion = vehicle_control_DW_l.UnitDelay1_DSTATE_c;

  /* UnitDelay: '<S42>/Unit Delay2' */
  rtb_Add3 = vehicle_control_DW_l.UnitDelay2_DSTATE_f;

  /* UnitDelay: '<S42>/Unit Delay3' */
  rtb_UnitDelay3_j = vehicle_control_DW_l.UnitDelay3_DSTATE_m;

  /* UnitDelay: '<S42>/Unit Delay4' */
  rtb_ratio = vehicle_control_DW_l.UnitDelay4_DSTATE_f;

  /* UnitDelay: '<S42>/Unit Delay5' */
  rtb_moment = vehicle_control_DW_l.UnitDelay5_DSTATE_e;

  /* MATLAB Function: '<S42>/MATLAB Function' incorporates:
   *  UnitDelay: '<S42>/Unit Delay'
   *  UnitDelay: '<S42>/Unit Delay1'
   *  UnitDelay: '<S42>/Unit Delay2'
   *  UnitDelay: '<S42>/Unit Delay3'
   *  UnitDelay: '<S42>/Unit Delay4'
   *  UnitDelay: '<S42>/Unit Delay5'
   *  UnitDelay: '<S42>/Unit Delay6'
   */
  MATLABFunction_d(vehicle_control_DW_l.UnitDelay_DSTATE_j,
                   vehicle_control_DW_l.UnitDelay1_DSTATE_c,
                   vehicle_control_DW_l.UnitDelay2_DSTATE_f,
                   vehicle_control_DW_l.UnitDelay3_DSTATE_m,
                   vehicle_control_DW_l.UnitDelay4_DSTATE_f,
                   vehicle_control_DW_l.UnitDelay5_DSTATE_e,
                   vehicle_control_DW_l.UnitDelay6_DSTATE_j, rtb_FzFL, &e);

  /* UnitDelay: '<S43>/Unit Delay' */
  rtb_FzFL = vehicle_control_DW_l.UnitDelay_DSTATE_g;

  /* UnitDelay: '<S43>/Unit Delay1' */
  rtb_UnitDelay1_j = vehicle_control_DW_l.UnitDelay1_DSTATE_n;

  /* UnitDelay: '<S43>/Unit Delay2' */
  rtb_UnitDelay2_m = vehicle_control_DW_l.UnitDelay2_DSTATE_d5;

  /* UnitDelay: '<S43>/Unit Delay3' */
  rtb_UnitDelay3_a1 = vehicle_control_DW_l.UnitDelay3_DSTATE_l;

  /* UnitDelay: '<S43>/Unit Delay4' */
  rtb_UnitDelay4_p = vehicle_control_DW_l.UnitDelay4_DSTATE_i;

  /* UnitDelay: '<S43>/Unit Delay5' */
  rtb_UnitDelay5_f = vehicle_control_DW_l.UnitDelay5_DSTATE_c;

  /* MATLAB Function: '<S43>/MATLAB Function' incorporates:
   *  UnitDelay: '<S43>/Unit Delay'
   *  UnitDelay: '<S43>/Unit Delay1'
   *  UnitDelay: '<S43>/Unit Delay2'
   *  UnitDelay: '<S43>/Unit Delay3'
   *  UnitDelay: '<S43>/Unit Delay4'
   *  UnitDelay: '<S43>/Unit Delay5'
   *  UnitDelay: '<S43>/Unit Delay6'
   */
  MATLABFunction_d(vehicle_control_DW_l.UnitDelay_DSTATE_g,
                   vehicle_control_DW_l.UnitDelay1_DSTATE_n,
                   vehicle_control_DW_l.UnitDelay2_DSTATE_d5,
                   vehicle_control_DW_l.UnitDelay3_DSTATE_l,
                   vehicle_control_DW_l.UnitDelay4_DSTATE_i,
                   vehicle_control_DW_l.UnitDelay5_DSTATE_c,
                   vehicle_control_DW_l.UnitDelay6_DSTATE_f, rtb_FzFR, &rtb_y_c);

  /* UnitDelay: '<S44>/Unit Delay' */
  rtb_FzFR = vehicle_control_DW_l.UnitDelay_DSTATE_jf;

  /* UnitDelay: '<S44>/Unit Delay1' */
  rtb_UnitDelay1_p = vehicle_control_DW_l.UnitDelay1_DSTATE_b;

  /* UnitDelay: '<S44>/Unit Delay2' */
  rtb_UnitDelay2_b = vehicle_control_DW_l.UnitDelay2_DSTATE_l;

  /* UnitDelay: '<S44>/Unit Delay3' */
  rtb_UnitDelay3_g = vehicle_control_DW_l.UnitDelay3_DSTATE_mt;

  /* UnitDelay: '<S44>/Unit Delay4' */
  rtb_UnitDelay4_i = vehicle_control_DW_l.UnitDelay4_DSTATE_j;

  /* UnitDelay: '<S44>/Unit Delay5' */
  rtb_UnitDelay5_h = vehicle_control_DW_l.UnitDelay5_DSTATE_h;

  /* MATLAB Function: '<S44>/MATLAB Function' incorporates:
   *  UnitDelay: '<S44>/Unit Delay'
   *  UnitDelay: '<S44>/Unit Delay1'
   *  UnitDelay: '<S44>/Unit Delay2'
   *  UnitDelay: '<S44>/Unit Delay3'
   *  UnitDelay: '<S44>/Unit Delay4'
   *  UnitDelay: '<S44>/Unit Delay5'
   *  UnitDelay: '<S44>/Unit Delay6'
   */
  MATLABFunction_d(vehicle_control_DW_l.UnitDelay_DSTATE_jf,
                   vehicle_control_DW_l.UnitDelay1_DSTATE_b,
                   vehicle_control_DW_l.UnitDelay2_DSTATE_l,
                   vehicle_control_DW_l.UnitDelay3_DSTATE_mt,
                   vehicle_control_DW_l.UnitDelay4_DSTATE_j,
                   vehicle_control_DW_l.UnitDelay5_DSTATE_h,
                   vehicle_control_DW_l.UnitDelay6_DSTATE_ab, rtb_FzRL,
                   &rtb_y_j0);

  /* UnitDelay: '<S45>/Unit Delay' */
  rtb_FzRL = vehicle_control_DW_l.UnitDelay_DSTATE_bu;

  /* UnitDelay: '<S45>/Unit Delay1' */
  rtb_UnitDelay1_pk = vehicle_control_DW_l.UnitDelay1_DSTATE_p;

  /* UnitDelay: '<S45>/Unit Delay2' */
  rtb_UnitDelay2_g = vehicle_control_DW_l.UnitDelay2_DSTATE_k;

  /* UnitDelay: '<S45>/Unit Delay3' */
  rtb_UnitDelay3_a = vehicle_control_DW_l.UnitDelay3_DSTATE_lk;

  /* UnitDelay: '<S45>/Unit Delay4' */
  rtb_UnitDelay4_j = vehicle_control_DW_l.UnitDelay4_DSTATE_n;

  /* UnitDelay: '<S45>/Unit Delay5' */
  rtb_UnitDelay5_p = vehicle_control_DW_l.UnitDelay5_DSTATE_a;

  /* MATLAB Function: '<S45>/MATLAB Function' incorporates:
   *  UnitDelay: '<S45>/Unit Delay'
   *  UnitDelay: '<S45>/Unit Delay1'
   *  UnitDelay: '<S45>/Unit Delay2'
   *  UnitDelay: '<S45>/Unit Delay3'
   *  UnitDelay: '<S45>/Unit Delay4'
   *  UnitDelay: '<S45>/Unit Delay5'
   *  UnitDelay: '<S45>/Unit Delay6'
   */
  MATLABFunction_d(vehicle_control_DW_l.UnitDelay_DSTATE_bu,
                   vehicle_control_DW_l.UnitDelay1_DSTATE_p,
                   vehicle_control_DW_l.UnitDelay2_DSTATE_k,
                   vehicle_control_DW_l.UnitDelay3_DSTATE_lk,
                   vehicle_control_DW_l.UnitDelay4_DSTATE_n,
                   vehicle_control_DW_l.UnitDelay5_DSTATE_a,
                   vehicle_control_DW_l.UnitDelay6_DSTATE_j0, rtb_FzRR, &rtb_y);

  /* Abs: '<S3>/Abs6' incorporates:
   *  Gain: '<Root>/Gain6'
   *  Inport generated from: '<Root>/wheel'
   */
  rtb_Abs6 = fabs(13.1 * vehicle_control_U.wheel.speed.fl);

  /* Gain: '<S3>/tmax_fr' incorporates:
   *  Abs: '<S3>/Abs6'
   *  Lookup_n-D: '<S3>/1-D Lookup Table6'
   */
  rtb_tmax_fr = tmax_fr * look1_binlca(rtb_Abs6, rtCP_uDLookupTable6_bp01Data,
    rtCP_uDLookupTable6_tableData, 5U);

  /* Abs: '<S3>/Abs7' incorporates:
   *  Gain: '<Root>/Gain'
   *  Inport generated from: '<Root>/wheel'
   */
  rtb_Abs7 = fabs(-13.1 * vehicle_control_U.wheel.speed.rl);

  /* Gain: '<S3>/tmax_rl' incorporates:
   *  Abs: '<S3>/Abs7'
   *  Lookup_n-D: '<S3>/1-D Lookup Table7'
   */
  rtb_tmax_rl = tmax_rl * look1_binlca(rtb_Abs7, rtCP_uDLookupTable7_bp01Data,
    rtCP_uDLookupTable7_tableData, 5U);

  /* Abs: '<S3>/Abs9' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Inport generated from: '<Root>/wheel'
   */
  rtb_FzRR = fabs(13.1 * vehicle_control_U.wheel.speed.rr);

  /* Gain: '<S3>/tmax_rr' incorporates:
   *  Abs: '<S3>/Abs9'
   *  Lookup_n-D: '<S3>/1-D Lookup Table8'
   */
  rtb_tmax_rr = tmax_rr * look1_binlca(rtb_FzRR, rtCP_uDLookupTable8_bp01Data,
    rtCP_uDLookupTable8_tableData, 5U);

  /* Saturate: '<S3>/Saturation7' */
  if (e <= 0.0) {
    Fz_r = 0.0;
  } else {
    Fz_r = e;
  }

  /* Saturate: '<S3>/Saturation8' */
  if (rtb_y_c <= 0.0) {
    p_idx_3 = 0.0;
  } else {
    p_idx_3 = rtb_y_c;
  }

  /* MATLAB Function: '<S3>/torque_distribution' incorporates:
   *  Saturate: '<S3>/Saturation7'
   *  Saturate: '<S3>/Saturation8'
   */
  Fz_f = Fz_r + p_idx_3;

  /* Saturate: '<S3>/Saturation9' */
  if (rtb_y_j0 <= 0.0) {
    Fz_r = 0.0;
  } else {
    Fz_r = rtb_y_j0;
  }

  /* Saturate: '<S3>/Saturation10' */
  if (rtb_y <= 0.0) {
    p_idx_3 = 0.0;
  } else {
    p_idx_3 = rtb_y;
  }

  /* MATLAB Function: '<S3>/torque_distribution' incorporates:
   *  Gain: '<S3>/Gas_scale'
   *  Gain: '<S3>/TV_cut'
   *  Saturate: '<S3>/Saturation10'
   *  Saturate: '<S3>/Saturation9'
   */
  Fz_r += p_idx_3;
  Fz = Fz_f + Fz_r;
  p_idx_3 = rtb_tmax_fl + rtb_tmax_fr;
  rtb_Switch2_n0 = ((p_idx_3 + rtb_tmax_rl) + rtb_tmax_rr) * rtb_Gain2;
  t_f_mtr = rtb_Switch2_n0 * Fz_f / Fz;
  t_r_mtr = rtb_Switch2_n0 * Fz_r / Fz;
  if (t_f_mtr > p_idx_3) {
    t_f_mtr = p_idx_3;
    t_r_mtr = rtb_Switch2_n0 - p_idx_3;
  } else if (t_r_mtr > rtb_tmax_rl + rtb_tmax_rr) {
    t_r_mtr = rtb_tmax_rl + rtb_tmax_rr;
    t_f_mtr = rtb_Switch2_n0 - t_r_mtr;
  }

  if (gas_scale == 1.0) {
    rtb_Switch2_n0 = rtb_Gain2 / 0.15;
    if (rtb_Switch2_n0 > 1.0) {
      rtb_Switch2_n0 = 1.0;
    }

    rtb_rate_lo_j *= rtb_Switch2_n0;
  }

  Fz_f = rtb_rate_lo_j * Fz_f / Fz;
  rtb_rate_lo_j = rtb_rate_lo_j * Fz_r / Fz;
  Fz_r = t_r_mtr * 13.1 / 0.254;
  p_idx_3 = t_f_mtr * 13.1 / 0.254 * 0.62;
  t_r_mtr = (p_idx_3 - Fz_f) / 1.24 * 0.254 / 13.1;
  Fz_f = (p_idx_3 + Fz_f) / 1.24 * 0.254 / 13.1;
  Fz_r /= 2.0;
  rtb_rate_lo_j /= 1.24;
  t_f_mtr = (Fz_r - rtb_rate_lo_j) * 0.254 / 13.1;
  rtb_rate_lo_j = (Fz_r + rtb_rate_lo_j) * 0.254 / 13.1;
  if ((TV_cut == 1.0) && (rtb_Gain2 <= 0.0)) {
    t_r_mtr = 0.0;
    Fz_f = 0.0;
    t_f_mtr = 0.0;
    rtb_rate_lo_j = 0.0;
  }

  /* Switch: '<S27>/Switch2' incorporates:
   *  RelationalOperator: '<S27>/LowerRelop1'
   */
  if (!(t_r_mtr > rtb_tmax_fl)) {
    /* Gain: '<S3>/Gain33' */
    rtb_tmax_fl = -rtb_tmax_fl;

    /* Switch: '<S27>/Switch' incorporates:
     *  RelationalOperator: '<S27>/UpperRelop'
     */
    if (!(t_r_mtr < rtb_tmax_fl)) {
      rtb_tmax_fl = t_r_mtr;
    }

    /* End of Switch: '<S27>/Switch' */
  }

  /* End of Switch: '<S27>/Switch2' */

  /* Switch: '<S28>/Switch2' incorporates:
   *  RelationalOperator: '<S28>/LowerRelop1'
   */
  if (!(Fz_f > rtb_tmax_fr)) {
    /* Gain: '<S3>/Gain34' */
    rtb_tmax_fr = -rtb_tmax_fr;

    /* Switch: '<S28>/Switch' incorporates:
     *  RelationalOperator: '<S28>/UpperRelop'
     */
    if (!(Fz_f < rtb_tmax_fr)) {
      rtb_tmax_fr = Fz_f;
    }

    /* End of Switch: '<S28>/Switch' */
  }

  /* End of Switch: '<S28>/Switch2' */

  /* Switch: '<S21>/Switch2' incorporates:
   *  RelationalOperator: '<S21>/LowerRelop1'
   */
  if (!(t_f_mtr > rtb_tmax_rl)) {
    /* Gain: '<S3>/Gain35' */
    rtb_tmax_rl = -rtb_tmax_rl;

    /* Switch: '<S21>/Switch' incorporates:
     *  RelationalOperator: '<S21>/UpperRelop'
     */
    if (!(t_f_mtr < rtb_tmax_rl)) {
      rtb_tmax_rl = t_f_mtr;
    }

    /* End of Switch: '<S21>/Switch' */
  }

  /* End of Switch: '<S21>/Switch2' */

  /* Switch: '<S22>/Switch2' incorporates:
   *  RelationalOperator: '<S22>/LowerRelop1'
   */
  if (!(rtb_rate_lo_j > rtb_tmax_rr)) {
    /* Gain: '<S3>/Gain36' */
    rtb_tmax_rr = -rtb_tmax_rr;

    /* Switch: '<S22>/Switch' incorporates:
     *  RelationalOperator: '<S22>/UpperRelop'
     */
    if (!(rtb_rate_lo_j < rtb_tmax_rr)) {
      rtb_tmax_rr = rtb_rate_lo_j;
    }

    /* End of Switch: '<S22>/Switch' */
  }

  /* End of Switch: '<S22>/Switch2' */

  /* MATLAB Function: '<S3>/P_limit' incorporates:
   *  Gain: '<S3>/TARGET'
   *  Inport generated from: '<Root>/states'
   *  MATLAB Function: '<S3>/MATLAB Function20'
   *  SignalConversion generated from: '<Root>/Bus Selector1'
   */
  Fz_f = rtb_y_g * 0.62;
  rtb_Gain2 = (vehicle_control_U.states.velocity.x - Fz_f) / 0.254;
  t_r_mtr = (Fz_f + vehicle_control_U.states.velocity.x) / 0.254;
  rtb_rate_lo_j = rtb_Gain2 * rtb_tmax_fl * 13.1;
  p_idx_1 = t_r_mtr * rtb_tmax_fr * 13.1;
  p_idx_2 = rtb_Gain2 * rtb_tmax_rl * 13.1;
  p_idx_3 = t_r_mtr * rtb_tmax_rr * 13.1;
  rtb_Gain2 = (TARGET - (((rtb_rate_lo_j + p_idx_1) + p_idx_2) + p_idx_3)) / 4.0;
  Fz_r = rtb_rate_lo_j + rtb_Gain2;
  rtb_rate_lo_j = Fz_r;
  if (Fz_r < 0.0) {
    rtb_rate_lo_j = 0.0;
  } else if (Fz_r > 20000.0) {
    rtb_rate_lo_j = 20000.0;
  }

  b_free_idx_0 = false;
  Fz_r = p_idx_1 + rtb_Gain2;
  p_idx_1 = Fz_r;
  if (Fz_r < 0.0) {
    p_idx_1 = 0.0;
  } else if (Fz_r > 20000.0) {
    p_idx_1 = 20000.0;
  }

  b_free_idx_1 = false;
  Fz_r = p_idx_2 + rtb_Gain2;
  p_idx_2 = Fz_r;
  if (Fz_r < 0.0) {
    p_idx_2 = 0.0;
  } else if (Fz_r > 20000.0) {
    p_idx_2 = 20000.0;
  }

  b_free_idx_2 = false;
  Fz_r = p_idx_3 + rtb_Gain2;
  p_idx_3 = Fz_r;
  if (Fz_r < 0.0) {
    p_idx_3 = 0.0;
  } else if (Fz_r > 20000.0) {
    p_idx_3 = 20000.0;
  }

  b_free_idx_3 = false;
  rtb_Gain2 = 0.0;
  if ((rtb_rate_lo_j > 0.0) && (rtb_rate_lo_j < 20000.0)) {
    b_free_idx_0 = true;
    rtb_Gain2 = 1.0;
  }

  if ((p_idx_1 > 0.0) && (p_idx_1 < 20000.0)) {
    b_free_idx_1 = true;
    rtb_Gain2++;
  }

  if ((p_idx_2 > 0.0) && (p_idx_2 < 20000.0)) {
    b_free_idx_2 = true;
    rtb_Gain2++;
  }

  if ((p_idx_3 > 0.0) && (p_idx_3 < 20000.0)) {
    b_free_idx_3 = true;
    rtb_Gain2++;
  }

  if (rtb_Gain2 > 0.0) {
    rtb_Gain2 = (TARGET - (((rtb_rate_lo_j + p_idx_1) + p_idx_2) + p_idx_3)) /
      rtb_Gain2;
    if (b_free_idx_0) {
      Fz_r = rtb_rate_lo_j + rtb_Gain2;
      rtb_rate_lo_j = Fz_r;
      if (Fz_r < 0.0) {
        rtb_rate_lo_j = 0.0;
      } else if (Fz_r > 20000.0) {
        rtb_rate_lo_j = 20000.0;
      }
    }

    if (b_free_idx_1) {
      Fz_r = p_idx_1 + rtb_Gain2;
      p_idx_1 = Fz_r;
      if (Fz_r < 0.0) {
        p_idx_1 = 0.0;
      } else if (Fz_r > 20000.0) {
        p_idx_1 = 20000.0;
      }
    }

    if (b_free_idx_2) {
      Fz_r = p_idx_2 + rtb_Gain2;
      p_idx_2 = Fz_r;
      if (Fz_r < 0.0) {
        p_idx_2 = 0.0;
      } else if (Fz_r > 20000.0) {
        p_idx_2 = 20000.0;
      }
    }

    if (b_free_idx_3) {
      Fz_r = p_idx_3 + rtb_Gain2;
      p_idx_3 = Fz_r;
      if (Fz_r < 0.0) {
        p_idx_3 = 0.0;
      } else if (Fz_r > 20000.0) {
        p_idx_3 = 20000.0;
      }
    }
  }

  /* Product: '<S3>/Divide4' incorporates:
   *  Gain: '<S3>/Gain37'
   *  MATLAB Function: '<S3>/P_limit'
   *  UnitConversion: '<S7>/Unit Conversion'
   */
  /* Unit Conversion - from: rpm to: rad/s
     Expression: output = (0.10472*input) + (0) */
  rtb_Switch2_n0 = 1.0 / (0.10471975511965977 * rtb_count_m) *
    (0.86956521739130443 * rtb_rate_lo_j);

  /* Switch: '<S23>/Switch2' incorporates:
   *  RelationalOperator: '<S23>/LowerRelop1'
   */
  if (!(rtb_tmax_fl > rtb_Switch2_n0)) {
    /* Switch: '<S23>/Switch' incorporates:
     *  Gain: '<S3>/Gain23'
     *  RelationalOperator: '<S23>/UpperRelop'
     */
    if (rtb_tmax_fl < -rtb_Switch2_n0) {
      rtb_Switch2_n0 = -rtb_Switch2_n0;
    } else {
      rtb_Switch2_n0 = rtb_tmax_fl;
    }

    /* End of Switch: '<S23>/Switch' */
  }

  /* End of Switch: '<S23>/Switch2' */

  /* Gain: '<S3>/Gain27' */
  Fz_r = 13.1 * rtb_Switch2_n0;

  /* Abs: '<S35>/Abs1' incorporates:
   *  Memory: '<S35>/Memory'
   */
  rtb_Gain2 = fabs(vehicle_control_DW_l.Memory_PreviousInput);

  /* MATLAB Function: '<S3>/MATLAB Function20' */
  rtb_count_m = rtb_count_m / 13.1 * 0.254;
  x[0] = rtb_count_m + Fz_f;
  rtb_Switch2_n0 = rtb_Abs6 / 13.1 * 0.254;
  x[1] = rtb_Switch2_n0 - Fz_f;
  t_f_mtr = rtb_Abs7 / 13.1 * 0.254;
  x[2] = t_f_mtr + Fz_f;
  t_r_mtr = rtb_FzRR / 13.1 * 0.254;
  x[3] = t_r_mtr - Fz_f;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 5)) {
      if (!rtIsNaN(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    rtb_rate_lo_j = x[0];
  } else {
    rtb_rate_lo_j = x[idx - 1];
    for (k = idx + 1; k < 5; k++) {
      rtb_tmax_fl = x[k - 1];
      if (rtb_rate_lo_j > rtb_tmax_fl) {
        rtb_rate_lo_j = rtb_tmax_fl;
      }
    }
  }

  rtb_tmax_fl = Fz_f + rtb_rate_lo_j;
  rtb_rate_lo_j -= Fz_f;
  rtb_count_m = (rtb_count_m - rtb_rate_lo_j) / rtb_rate_lo_j;
  Fz_f = (rtb_Switch2_n0 - rtb_tmax_fl) / rtb_tmax_fl;
  Fz = (t_f_mtr - rtb_rate_lo_j) / rtb_rate_lo_j;
  t_f_mtr = (t_r_mtr - rtb_tmax_fl) / rtb_tmax_fl;

  /* MATLAB Function: '<S35>/MATLAB Function' incorporates:
   *  Abs: '<S35>/Abs'
   *  Constant: '<S3>/Constant16'
   *  Constant: '<S3>/Constant18'
   */
  if ((rtb_count_m > 0.12) && (rtb_count_m <= 0.15)) {
    rtb_tmax_fl = 1.0;
  } else if ((rtb_count_m > 0.15) && (rtb_count_m <= 0.18)) {
    rtb_Gain2 -= 0.2;
    rtb_tmax_fl = 1.0;
  } else if (rtb_count_m > 0.18) {
    rtb_Gain2 -= 0.5;
    rtb_tmax_fl = 1.0;
  } else {
    rtb_Gain2 = fabs(Fz_r);
    rtb_tmax_fl = 0.0;
  }

  /* End of MATLAB Function: '<S35>/MATLAB Function' */

  /* MATLAB Function: '<S35>/MATLAB Function1' incorporates:
   *  Memory: '<S35>/Memory2'
   *  Memory: '<S35>/Memory3'
   */
  MATLABFunction1(rtb_tmax_fl, vehicle_control_DW_l.Memory2_PreviousInput,
                  vehicle_control_DW_l.Memory3_PreviousInput, &rtb_rate_lo_p,
                  &rtb_count_m);

  /* MATLAB Function: '<S35>/MATLAB Function2' */
  MATLABFunction2(Fz_r, rtb_rate_lo_p, &t_r_mtr, &rtb_rate_lo_j);

  /* Product: '<S59>/delta rise limit' incorporates:
   *  SampleTimeMath: '<S59>/sample time'
   *
   * About '<S59>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Switch2_n0 = t_r_mtr * 0.01;

  /* Saturate: '<S35>/Saturation' */
  if (rtb_Gain2 <= 0.0) {
    rtb_Gain2 = 0.0;
  }

  /* End of Saturate: '<S35>/Saturation' */

  /* Switch: '<S60>/Switch2' incorporates:
   *  RelationalOperator: '<S60>/LowerRelop1'
   */
  if (!(Fz_r > rtb_Gain2)) {
    /* Gain: '<S35>/Gain' */
    rtb_Gain2 = -rtb_Gain2;

    /* Switch: '<S60>/Switch' incorporates:
     *  RelationalOperator: '<S60>/UpperRelop'
     */
    if (!(Fz_r < rtb_Gain2)) {
      rtb_Gain2 = Fz_r;
    }

    /* End of Switch: '<S60>/Switch' */
  }

  /* End of Switch: '<S60>/Switch2' */

  /* Delay: '<S59>/Delay' */
  if (vehicle_control_DW_l.icLoad) {
    vehicle_control_DW_l.Delay_DSTATE = rtb_Gain2;
  }

  /* Sum: '<S59>/Difference Inputs1' incorporates:
   *  Delay: '<S59>/Delay'
   *
   * Block description for '<S59>/Difference Inputs1':
   *
   *  Add in CPU
   */
  t_r_mtr = rtb_Gain2 - vehicle_control_DW_l.Delay_DSTATE;

  /* Switch: '<S61>/Switch2' incorporates:
   *  RelationalOperator: '<S61>/LowerRelop1'
   */
  if (!(t_r_mtr > rtb_Switch2_n0)) {
    /* Product: '<S59>/delta fall limit' incorporates:
     *  SampleTimeMath: '<S59>/sample time'
     *
     * About '<S59>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_rate_lo_j *= 0.01;

    /* Switch: '<S61>/Switch' incorporates:
     *  RelationalOperator: '<S61>/UpperRelop'
     */
    if (t_r_mtr < rtb_rate_lo_j) {
      rtb_Switch2_n0 = rtb_rate_lo_j;
    } else {
      rtb_Switch2_n0 = t_r_mtr;
    }

    /* End of Switch: '<S61>/Switch' */
  }

  /* End of Switch: '<S61>/Switch2' */

  /* Sum: '<S59>/Difference Inputs2' incorporates:
   *  Delay: '<S59>/Delay'
   *
   * Block description for '<S59>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_rate_lo_j = rtb_Switch2_n0 + vehicle_control_DW_l.Delay_DSTATE;

  /* Switch: '<S3>/Switch6' incorporates:
   *  Constant: '<S3>/TC_switch'
   */
  if (tc_switch > 0.0) {
    Fz_r = rtb_rate_lo_j;
  }

  /* Gain: '<Root>/Gain7' incorporates:
   *  Switch: '<S3>/Switch6'
   */
  vehicle_control_Y.torq.torque.fl = 0.076335877862595422 * Fz_r;

  /* Product: '<S3>/Divide5' incorporates:
   *  Gain: '<S3>/Gain38'
   *  MATLAB Function: '<S3>/P_limit'
   *  UnitConversion: '<S4>/Unit Conversion'
   */
  /* Unit Conversion - from: rpm to: rad/s
     Expression: output = (0.10472*input) + (0) */
  rtb_Switch2_n0 = 1.0 / (0.10471975511965977 * rtb_Abs6) * (0.86956521739130443
    * p_idx_1);

  /* Switch: '<S24>/Switch2' incorporates:
   *  RelationalOperator: '<S24>/LowerRelop1'
   */
  if (!(rtb_tmax_fr > rtb_Switch2_n0)) {
    /* Switch: '<S24>/Switch' incorporates:
     *  Gain: '<S3>/Gain24'
     *  RelationalOperator: '<S24>/UpperRelop'
     */
    if (rtb_tmax_fr < -rtb_Switch2_n0) {
      rtb_Switch2_n0 = -rtb_Switch2_n0;
    } else {
      rtb_Switch2_n0 = rtb_tmax_fr;
    }

    /* End of Switch: '<S24>/Switch' */
  }

  /* End of Switch: '<S24>/Switch2' */

  /* Gain: '<S3>/Gain28' */
  p_idx_1 = 13.1 * rtb_Switch2_n0;

  /* Abs: '<S36>/Abs1' incorporates:
   *  Memory: '<S36>/Memory'
   */
  rtb_tmax_fr = fabs(vehicle_control_DW_l.Memory_PreviousInput_e);

  /* MATLAB Function: '<S36>/MATLAB Function' incorporates:
   *  Abs: '<S36>/Abs'
   *  Constant: '<S3>/Constant16'
   *  Constant: '<S3>/Constant18'
   */
  if ((Fz_f > 0.12) && (Fz_f <= 0.15)) {
    rtb_Abs6 = 1.0;
  } else if ((Fz_f > 0.15) && (Fz_f <= 0.18)) {
    rtb_tmax_fr -= 0.2;
    rtb_Abs6 = 1.0;
  } else if (Fz_f > 0.18) {
    rtb_tmax_fr -= 0.5;
    rtb_Abs6 = 1.0;
  } else {
    rtb_tmax_fr = fabs(p_idx_1);
    rtb_Abs6 = 0.0;
  }

  /* End of MATLAB Function: '<S36>/MATLAB Function' */

  /* Saturate: '<S36>/Saturation' */
  if (rtb_tmax_fr <= 0.0) {
    rtb_tmax_fr = 0.0;
  }

  /* End of Saturate: '<S36>/Saturation' */

  /* Switch: '<S66>/Switch2' incorporates:
   *  RelationalOperator: '<S66>/LowerRelop1'
   */
  if (!(p_idx_1 > rtb_tmax_fr)) {
    /* Gain: '<S36>/Gain' */
    rtb_tmax_fr = -rtb_tmax_fr;

    /* Switch: '<S66>/Switch' incorporates:
     *  RelationalOperator: '<S66>/UpperRelop'
     */
    if (!(p_idx_1 < rtb_tmax_fr)) {
      rtb_tmax_fr = p_idx_1;
    }

    /* End of Switch: '<S66>/Switch' */
  }

  /* End of Switch: '<S66>/Switch2' */

  /* Delay: '<S65>/Delay' */
  if (vehicle_control_DW_l.icLoad_f) {
    vehicle_control_DW_l.Delay_DSTATE_o = rtb_tmax_fr;
  }

  /* MATLAB Function: '<S36>/MATLAB Function1' incorporates:
   *  Memory: '<S36>/Memory2'
   *  Memory: '<S36>/Memory3'
   */
  MATLABFunction1(rtb_Abs6, vehicle_control_DW_l.Memory2_PreviousInput_e,
                  vehicle_control_DW_l.Memory3_PreviousInput_b, &rtb_rate_lo_m,
                  &t_r_mtr);

  /* MATLAB Function: '<S36>/MATLAB Function2' */
  MATLABFunction2(p_idx_1, rtb_rate_lo_m, &Fz_r, &rtb_rate_lo_p);

  /* Product: '<S65>/delta rise limit' incorporates:
   *  SampleTimeMath: '<S65>/sample time'
   *
   * About '<S65>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Switch2_n0 = Fz_r * 0.01;

  /* Sum: '<S65>/Difference Inputs1' incorporates:
   *  Delay: '<S65>/Delay'
   *
   * Block description for '<S65>/Difference Inputs1':
   *
   *  Add in CPU
   */
  Fz_f = rtb_tmax_fr - vehicle_control_DW_l.Delay_DSTATE_o;

  /* Switch: '<S67>/Switch2' incorporates:
   *  RelationalOperator: '<S67>/LowerRelop1'
   */
  if (!(Fz_f > rtb_Switch2_n0)) {
    /* Product: '<S65>/delta fall limit' incorporates:
     *  SampleTimeMath: '<S65>/sample time'
     *
     * About '<S65>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    Fz_r = 0.01 * rtb_rate_lo_p;

    /* Switch: '<S67>/Switch' incorporates:
     *  RelationalOperator: '<S67>/UpperRelop'
     */
    if (Fz_f < Fz_r) {
      rtb_Switch2_n0 = Fz_r;
    } else {
      rtb_Switch2_n0 = Fz_f;
    }

    /* End of Switch: '<S67>/Switch' */
  }

  /* End of Switch: '<S67>/Switch2' */

  /* Sum: '<S65>/Difference Inputs2' incorporates:
   *  Delay: '<S65>/Delay'
   *
   * Block description for '<S65>/Difference Inputs2':
   *
   *  Add in CPU
   */
  Fz_f = rtb_Switch2_n0 + vehicle_control_DW_l.Delay_DSTATE_o;

  /* Switch: '<S3>/Switch7' incorporates:
   *  Constant: '<S3>/TC_switch'
   */
  if (tc_switch > 0.0) {
    p_idx_1 = Fz_f;
  }

  /* Gain: '<Root>/Gain8' incorporates:
   *  Switch: '<S3>/Switch7'
   */
  vehicle_control_Y.torq.torque.fr = 0.076335877862595422 * p_idx_1;

  /* Product: '<S3>/Divide6' incorporates:
   *  Gain: '<S3>/Gain39'
   *  MATLAB Function: '<S3>/P_limit'
   *  UnitConversion: '<S5>/Unit Conversion'
   */
  /* Unit Conversion - from: rpm to: rad/s
     Expression: output = (0.10472*input) + (0) */
  rtb_Switch2_n0 = 1.0 / (0.10471975511965977 * rtb_Abs7) * (0.86956521739130443
    * p_idx_2);

  /* Switch: '<S25>/Switch2' incorporates:
   *  RelationalOperator: '<S25>/LowerRelop1'
   */
  if (!(rtb_tmax_rl > rtb_Switch2_n0)) {
    /* Switch: '<S25>/Switch' incorporates:
     *  Gain: '<S3>/Gain25'
     *  RelationalOperator: '<S25>/UpperRelop'
     */
    if (rtb_tmax_rl < -rtb_Switch2_n0) {
      rtb_Switch2_n0 = -rtb_Switch2_n0;
    } else {
      rtb_Switch2_n0 = rtb_tmax_rl;
    }

    /* End of Switch: '<S25>/Switch' */
  }

  /* End of Switch: '<S25>/Switch2' */

  /* Gain: '<S3>/Gain29' */
  p_idx_1 = 13.1 * rtb_Switch2_n0;

  /* Abs: '<S37>/Abs1' incorporates:
   *  Memory: '<S37>/Memory'
   */
  rtb_tmax_rl = fabs(vehicle_control_DW_l.Memory_PreviousInput_m);

  /* MATLAB Function: '<S37>/MATLAB Function' incorporates:
   *  Abs: '<S37>/Abs'
   *  Constant: '<S3>/Constant16'
   *  Constant: '<S3>/Constant18'
   */
  if ((Fz > 0.12) && (Fz <= 0.15)) {
    rtb_Abs7 = 1.0;
  } else if ((Fz > 0.15) && (Fz <= 0.18)) {
    rtb_tmax_rl -= 0.2;
    rtb_Abs7 = 1.0;
  } else if (Fz > 0.18) {
    rtb_tmax_rl -= 0.5;
    rtb_Abs7 = 1.0;
  } else {
    rtb_tmax_rl = fabs(p_idx_1);
    rtb_Abs7 = 0.0;
  }

  /* End of MATLAB Function: '<S37>/MATLAB Function' */

  /* Saturate: '<S37>/Saturation' */
  if (rtb_tmax_rl <= 0.0) {
    rtb_tmax_rl = 0.0;
  }

  /* End of Saturate: '<S37>/Saturation' */

  /* Switch: '<S72>/Switch2' incorporates:
   *  RelationalOperator: '<S72>/LowerRelop1'
   */
  if (!(p_idx_1 > rtb_tmax_rl)) {
    /* Gain: '<S37>/Gain' */
    rtb_tmax_rl = -rtb_tmax_rl;

    /* Switch: '<S72>/Switch' incorporates:
     *  RelationalOperator: '<S72>/UpperRelop'
     */
    if (!(p_idx_1 < rtb_tmax_rl)) {
      rtb_tmax_rl = p_idx_1;
    }

    /* End of Switch: '<S72>/Switch' */
  }

  /* End of Switch: '<S72>/Switch2' */

  /* Delay: '<S71>/Delay' */
  if (vehicle_control_DW_l.icLoad_fb) {
    vehicle_control_DW_l.Delay_DSTATE_e = rtb_tmax_rl;
  }

  /* MATLAB Function: '<S37>/MATLAB Function1' incorporates:
   *  Memory: '<S37>/Memory2'
   *  Memory: '<S37>/Memory3'
   */
  MATLABFunction1(rtb_Abs7, vehicle_control_DW_l.Memory2_PreviousInput_b,
                  vehicle_control_DW_l.Memory3_PreviousInput_a, &p_idx_2, &Fz_r);

  /* MATLAB Function: '<S37>/MATLAB Function2' */
  MATLABFunction2(p_idx_1, p_idx_2, &rtb_rate_lo_p, &rtb_rate_lo_m);

  /* Product: '<S71>/delta rise limit' incorporates:
   *  SampleTimeMath: '<S71>/sample time'
   *
   * About '<S71>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Switch2_n0 = rtb_rate_lo_p * 0.01;

  /* Sum: '<S71>/Difference Inputs1' incorporates:
   *  Delay: '<S71>/Delay'
   *
   * Block description for '<S71>/Difference Inputs1':
   *
   *  Add in CPU
   */
  Fz = rtb_tmax_rl - vehicle_control_DW_l.Delay_DSTATE_e;

  /* Switch: '<S73>/Switch2' incorporates:
   *  RelationalOperator: '<S73>/LowerRelop1'
   */
  if (!(Fz > rtb_Switch2_n0)) {
    /* Product: '<S71>/delta fall limit' incorporates:
     *  SampleTimeMath: '<S71>/sample time'
     *
     * About '<S71>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Switch2_n0 = 0.01 * rtb_rate_lo_m;

    /* Switch: '<S73>/Switch' incorporates:
     *  RelationalOperator: '<S73>/UpperRelop'
     */
    if (!(Fz < rtb_Switch2_n0)) {
      rtb_Switch2_n0 = Fz;
    }

    /* End of Switch: '<S73>/Switch' */
  }

  /* End of Switch: '<S73>/Switch2' */

  /* Sum: '<S71>/Difference Inputs2' incorporates:
   *  Delay: '<S71>/Delay'
   *
   * Block description for '<S71>/Difference Inputs2':
   *
   *  Add in CPU
   */
  Fz = rtb_Switch2_n0 + vehicle_control_DW_l.Delay_DSTATE_e;

  /* Switch: '<S3>/Switch9' incorporates:
   *  Constant: '<S3>/TC_switch'
   */
  if (tc_switch > 0.0) {
    p_idx_1 = Fz;
  }

  /* Gain: '<Root>/Gain3' incorporates:
   *  Switch: '<S3>/Switch9'
   */
  vehicle_control_Y.torq.torque.rl = 0.076335877862595422 * p_idx_1;

  /* Product: '<S3>/Divide7' incorporates:
   *  Gain: '<S3>/Gain22'
   *  MATLAB Function: '<S3>/P_limit'
   *  UnitConversion: '<S6>/Unit Conversion'
   */
  /* Unit Conversion - from: rpm to: rad/s
     Expression: output = (0.10472*input) + (0) */
  rtb_Switch2_n0 = 1.0 / (0.10471975511965977 * rtb_FzRR) * (0.86956521739130443
    * p_idx_3);

  /* Switch: '<S26>/Switch2' incorporates:
   *  RelationalOperator: '<S26>/LowerRelop1'
   */
  if (!(rtb_tmax_rr > rtb_Switch2_n0)) {
    /* Switch: '<S26>/Switch' incorporates:
     *  Gain: '<S3>/Gain26'
     *  RelationalOperator: '<S26>/UpperRelop'
     */
    if (rtb_tmax_rr < -rtb_Switch2_n0) {
      rtb_Switch2_n0 = -rtb_Switch2_n0;
    } else {
      rtb_Switch2_n0 = rtb_tmax_rr;
    }

    /* End of Switch: '<S26>/Switch' */
  }

  /* End of Switch: '<S26>/Switch2' */

  /* Gain: '<S3>/Gain30' */
  rtb_tmax_rr = 13.1 * rtb_Switch2_n0;

  /* Abs: '<S38>/Abs1' incorporates:
   *  Memory: '<S38>/Memory'
   */
  rtb_Switch2_n0 = fabs(vehicle_control_DW_l.Memory_PreviousInput_l);

  /* MATLAB Function: '<S38>/MATLAB Function' incorporates:
   *  Abs: '<S38>/Abs'
   *  Constant: '<S3>/Constant16'
   *  Constant: '<S3>/Constant18'
   */
  if ((t_f_mtr > 0.12) && (t_f_mtr <= 0.15)) {
    rtb_FzRR = 1.0;
  } else if ((t_f_mtr > 0.15) && (t_f_mtr <= 0.18)) {
    rtb_Switch2_n0 -= 0.2;
    rtb_FzRR = 1.0;
  } else if (t_f_mtr > 0.18) {
    rtb_Switch2_n0 -= 0.5;
    rtb_FzRR = 1.0;
  } else {
    rtb_Switch2_n0 = fabs(rtb_tmax_rr);
    rtb_FzRR = 0.0;
  }

  /* End of MATLAB Function: '<S38>/MATLAB Function' */

  /* Saturate: '<S38>/Saturation' */
  if (rtb_Switch2_n0 <= 0.0) {
    t_f_mtr = 0.0;
  } else {
    t_f_mtr = rtb_Switch2_n0;
  }

  /* End of Saturate: '<S38>/Saturation' */

  /* Switch: '<S78>/Switch2' incorporates:
   *  RelationalOperator: '<S78>/LowerRelop1'
   */
  if (!(rtb_tmax_rr > t_f_mtr)) {
    /* Gain: '<S38>/Gain' */
    t_f_mtr = -t_f_mtr;

    /* Switch: '<S78>/Switch' incorporates:
     *  RelationalOperator: '<S78>/UpperRelop'
     */
    if (!(rtb_tmax_rr < t_f_mtr)) {
      t_f_mtr = rtb_tmax_rr;
    }

    /* End of Switch: '<S78>/Switch' */
  }

  /* End of Switch: '<S78>/Switch2' */

  /* Delay: '<S77>/Delay' */
  if (vehicle_control_DW_l.icLoad_o) {
    vehicle_control_DW_l.Delay_DSTATE_l = t_f_mtr;
  }

  /* MATLAB Function: '<S38>/MATLAB Function1' incorporates:
   *  Memory: '<S38>/Memory2'
   *  Memory: '<S38>/Memory3'
   */
  MATLABFunction1(rtb_FzRR, vehicle_control_DW_l.Memory2_PreviousInput_a,
                  vehicle_control_DW_l.Memory3_PreviousInput_c, &p_idx_2,
                  &rtb_rate_lo_p);

  /* MATLAB Function: '<S38>/MATLAB Function2' */
  MATLABFunction2(rtb_tmax_rr, p_idx_2, &rtb_Switch2_n0, &rtb_rate_lo_m);

  /* Product: '<S77>/delta rise limit' incorporates:
   *  SampleTimeMath: '<S77>/sample time'
   *
   * About '<S77>/sample time':
   *  y = K where K = ( w * Ts )
   *   */
  rtb_Switch2_n0 *= 0.01;

  /* Sum: '<S77>/Difference Inputs1' incorporates:
   *  Delay: '<S77>/Delay'
   *
   * Block description for '<S77>/Difference Inputs1':
   *
   *  Add in CPU
   */
  p_idx_1 = t_f_mtr - vehicle_control_DW_l.Delay_DSTATE_l;

  /* Switch: '<S79>/Switch2' incorporates:
   *  RelationalOperator: '<S79>/LowerRelop1'
   */
  if (!(p_idx_1 > rtb_Switch2_n0)) {
    /* Product: '<S77>/delta fall limit' incorporates:
     *  SampleTimeMath: '<S77>/sample time'
     *
     * About '<S77>/sample time':
     *  y = K where K = ( w * Ts )
     *   */
    rtb_Switch2_n0 = 0.01 * rtb_rate_lo_m;

    /* Switch: '<S79>/Switch' incorporates:
     *  RelationalOperator: '<S79>/UpperRelop'
     */
    if (!(p_idx_1 < rtb_Switch2_n0)) {
      rtb_Switch2_n0 = p_idx_1;
    }

    /* End of Switch: '<S79>/Switch' */
  }

  /* End of Switch: '<S79>/Switch2' */

  /* Sum: '<S77>/Difference Inputs2' incorporates:
   *  Delay: '<S77>/Delay'
   *
   * Block description for '<S77>/Difference Inputs2':
   *
   *  Add in CPU
   */
  rtb_Switch2_n0 += vehicle_control_DW_l.Delay_DSTATE_l;

  /* Switch: '<S3>/Switch11' incorporates:
   *  Constant: '<S3>/TC_switch'
   */
  if (tc_switch > 0.0) {
    rtb_tmax_rr = rtb_Switch2_n0;
  }

  /* Gain: '<Root>/Gain4' incorporates:
   *  Switch: '<S3>/Switch11'
   */
  vehicle_control_Y.torq.torque.rr = 0.076335877862595422 * rtb_tmax_rr;

  /* BusCreator generated from: '<Root>/torq_BusCreator' incorporates:
   *  Constant: '<Root>/Constant'
   */
  vehicle_control_Y.torq.header.timestamp_ns = 0ULL;

  /* Abs: '<S3>/Abs8' incorporates:
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator2'
   */
  rtb_tmax_rr = fabs(vehicle_control_DW_l.DiscreteTimeIntegrator2_DSTATE);

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

  /* Update for UnitDelay: '<S39>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE = rtb_y_kb;

  /* Update for UnitDelay: '<S39>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE = rtb_UnitDelay;

  /* Update for UnitDelay: '<S39>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE = rtb_UnitDelay1;

  /* Update for UnitDelay: '<S39>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE = rtb_UnitDelay2;

  /* Update for UnitDelay: '<S39>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE = rtb_UnitDelay3;

  /* Update for UnitDelay: '<S39>/Unit Delay5' */
  vehicle_control_DW_l.UnitDelay5_DSTATE = rtb_UnitDelay4;

  /* Update for UnitDelay: '<S39>/Unit Delay6' */
  vehicle_control_DW_l.UnitDelay6_DSTATE = rtb_UnitDelay5;

  /* Update for UnitDelay: '<S40>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_c = rtb_y_h;

  /* Update for UnitDelay: '<S40>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_h = rtb_UnitDelay_em;

  /* Update for UnitDelay: '<S40>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_p = rtb_UnitDelay1_gt;

  /* Update for UnitDelay: '<S40>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_e = rtb_UnitDelay2_p1;

  /* Update for UnitDelay: '<S40>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_p = rtb_UnitDelay3_d;

  /* Update for UnitDelay: '<S40>/Unit Delay5' */
  vehicle_control_DW_l.UnitDelay5_DSTATE_f = rtb_UnitDelay4_o;

  /* Update for UnitDelay: '<S40>/Unit Delay6' */
  vehicle_control_DW_l.UnitDelay6_DSTATE_a = rtb_UnitDelay5_ke;

  /* Update for UnitDelay: '<S33>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_h = rtb_y_cb;

  /* Update for UnitDelay: '<S33>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_a = rtb_F_aero;

  /* Update for UnitDelay: '<S33>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_n = rtb_Gain;

  /* Update for UnitDelay: '<S33>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_o = rtb_uDLookupTable;

  /* Update for UnitDelay: '<S33>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_h = rtb_F_dy;

  /* Update for UnitDelay: '<S32>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_m = rtb_y_d;

  /* Update for UnitDelay: '<S32>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_f = rtb_Subtract;

  /* Update for UnitDelay: '<S32>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_pk = Ffs;

  /* Update for UnitDelay: '<S8>/UD'
   *
   * Block description for '<S8>/UD':
   *
   *  Store in Global RAM
   */
  vehicle_control_DW_l.UD_DSTATE = rtb_TSamp;

  /* Update for UnitDelay: '<S29>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_n = rtb_y_o;

  /* Update for UnitDelay: '<S29>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_i = rtb_UnitDelay_o;

  /* Update for UnitDelay: '<S29>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_b = rtb_UnitDelay1_n;

  /* Update for UnitDelay: '<S29>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_f = rtb_UnitDelay2_h;

  /* Update for UnitDelay: '<S29>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_o = rtb_UnitDelay3_p;

  /* Update for UnitDelay: '<S31>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_b = rtb_y_g;

  /* Update for UnitDelay: '<S31>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_m = rtb_UnitDelay_ee;

  /* Update for UnitDelay: '<S31>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_d = rtb_UnitDelay1_f;

  /* Update for UnitDelay: '<S31>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_fs = rtb_UnitDelay2_e;

  /* Update for UnitDelay: '<S9>/UD'
   *
   * Block description for '<S9>/UD':
   *
   *  Store in Global RAM
   */
  vehicle_control_DW_l.UD_DSTATE_i = rtb_TSamp_l;

  /* Switch: '<S3>/Switch10' incorporates:
   *  Constant: '<S3>/Constant19'
   *  Memory: '<S3>/Memory7'
   */
  if (vehicle_control_DW_l.Memory7_PreviousInput >= 0.04) {
    e_tmp = 0.0;
  }

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator2' incorporates:
   *  Switch: '<S3>/Switch10'
   */
  vehicle_control_DW_l.DiscreteTimeIntegrator2_DSTATE += 0.01 * e_tmp;

  /* Update for UnitDelay: '<S42>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_j = e;

  /* Update for UnitDelay: '<S42>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_c = rtb_Add2;

  /* Update for UnitDelay: '<S42>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_f = rtb_UnitConversion;

  /* Update for UnitDelay: '<S42>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_m = rtb_Add3;

  /* Update for UnitDelay: '<S42>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_f = rtb_UnitDelay3_j;

  /* Update for UnitDelay: '<S42>/Unit Delay5' */
  vehicle_control_DW_l.UnitDelay5_DSTATE_e = rtb_ratio;

  /* Update for UnitDelay: '<S42>/Unit Delay6' */
  vehicle_control_DW_l.UnitDelay6_DSTATE_j = rtb_moment;

  /* Update for UnitDelay: '<S43>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_g = rtb_y_c;

  /* Update for UnitDelay: '<S43>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_n = rtb_FzFL;

  /* Update for UnitDelay: '<S43>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_d5 = rtb_UnitDelay1_j;

  /* Update for UnitDelay: '<S43>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_l = rtb_UnitDelay2_m;

  /* Update for UnitDelay: '<S43>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_i = rtb_UnitDelay3_a1;

  /* Update for UnitDelay: '<S43>/Unit Delay5' */
  vehicle_control_DW_l.UnitDelay5_DSTATE_c = rtb_UnitDelay4_p;

  /* Update for UnitDelay: '<S43>/Unit Delay6' */
  vehicle_control_DW_l.UnitDelay6_DSTATE_f = rtb_UnitDelay5_f;

  /* Update for UnitDelay: '<S44>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_jf = rtb_y_j0;

  /* Update for UnitDelay: '<S44>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_b = rtb_FzFR;

  /* Update for UnitDelay: '<S44>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_l = rtb_UnitDelay1_p;

  /* Update for UnitDelay: '<S44>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_mt = rtb_UnitDelay2_b;

  /* Update for UnitDelay: '<S44>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_j = rtb_UnitDelay3_g;

  /* Update for UnitDelay: '<S44>/Unit Delay5' */
  vehicle_control_DW_l.UnitDelay5_DSTATE_h = rtb_UnitDelay4_i;

  /* Update for UnitDelay: '<S44>/Unit Delay6' */
  vehicle_control_DW_l.UnitDelay6_DSTATE_ab = rtb_UnitDelay5_h;

  /* Update for UnitDelay: '<S45>/Unit Delay' */
  vehicle_control_DW_l.UnitDelay_DSTATE_bu = rtb_y;

  /* Update for UnitDelay: '<S45>/Unit Delay1' */
  vehicle_control_DW_l.UnitDelay1_DSTATE_p = rtb_FzRL;

  /* Update for UnitDelay: '<S45>/Unit Delay2' */
  vehicle_control_DW_l.UnitDelay2_DSTATE_k = rtb_UnitDelay1_pk;

  /* Update for UnitDelay: '<S45>/Unit Delay3' */
  vehicle_control_DW_l.UnitDelay3_DSTATE_lk = rtb_UnitDelay2_g;

  /* Update for UnitDelay: '<S45>/Unit Delay4' */
  vehicle_control_DW_l.UnitDelay4_DSTATE_n = rtb_UnitDelay3_a;

  /* Update for UnitDelay: '<S45>/Unit Delay5' */
  vehicle_control_DW_l.UnitDelay5_DSTATE_a = rtb_UnitDelay4_j;

  /* Update for UnitDelay: '<S45>/Unit Delay6' */
  vehicle_control_DW_l.UnitDelay6_DSTATE_j0 = rtb_UnitDelay5_p;

  /* Update for Memory: '<S35>/Memory' */
  vehicle_control_DW_l.Memory_PreviousInput = rtb_Gain2;

  /* Update for Memory: '<S35>/Memory2' */
  vehicle_control_DW_l.Memory2_PreviousInput = rtb_tmax_fl;

  /* Update for Memory: '<S35>/Memory3' */
  vehicle_control_DW_l.Memory3_PreviousInput = rtb_count_m;

  /* Update for Delay: '<S59>/Delay' */
  vehicle_control_DW_l.icLoad = false;
  vehicle_control_DW_l.Delay_DSTATE = rtb_rate_lo_j;

  /* Update for Memory: '<S36>/Memory' */
  vehicle_control_DW_l.Memory_PreviousInput_e = rtb_tmax_fr;

  /* Update for Delay: '<S65>/Delay' */
  vehicle_control_DW_l.icLoad_f = false;
  vehicle_control_DW_l.Delay_DSTATE_o = Fz_f;

  /* Update for Memory: '<S36>/Memory2' */
  vehicle_control_DW_l.Memory2_PreviousInput_e = rtb_Abs6;

  /* Update for Memory: '<S36>/Memory3' */
  vehicle_control_DW_l.Memory3_PreviousInput_b = t_r_mtr;

  /* Update for Memory: '<S37>/Memory' */
  vehicle_control_DW_l.Memory_PreviousInput_m = rtb_tmax_rl;

  /* Update for Delay: '<S71>/Delay' */
  vehicle_control_DW_l.icLoad_fb = false;
  vehicle_control_DW_l.Delay_DSTATE_e = Fz;

  /* Update for Memory: '<S37>/Memory2' */
  vehicle_control_DW_l.Memory2_PreviousInput_b = rtb_Abs7;

  /* Update for Memory: '<S37>/Memory3' */
  vehicle_control_DW_l.Memory3_PreviousInput_a = Fz_r;

  /* Update for Memory: '<S38>/Memory' */
  vehicle_control_DW_l.Memory_PreviousInput_l = t_f_mtr;

  /* Update for Delay: '<S77>/Delay' */
  vehicle_control_DW_l.icLoad_o = false;
  vehicle_control_DW_l.Delay_DSTATE_l = rtb_Switch2_n0;

  /* Update for Memory: '<S38>/Memory2' */
  vehicle_control_DW_l.Memory2_PreviousInput_a = rtb_FzRR;

  /* Update for Memory: '<S38>/Memory3' */
  vehicle_control_DW_l.Memory3_PreviousInput_c = rtb_rate_lo_p;

  /* Update for Memory: '<S3>/Memory7' */
  vehicle_control_DW_l.Memory7_PreviousInput = rtb_tmax_rr;
}

/* Model initialize function */
void vehicle_control_initialize(void)
{
  /* InitializeConditions for Delay: '<S59>/Delay' */
  vehicle_control_DW_l.icLoad = true;

  /* InitializeConditions for Delay: '<S65>/Delay' */
  vehicle_control_DW_l.icLoad_f = true;

  /* InitializeConditions for Delay: '<S71>/Delay' */
  vehicle_control_DW_l.icLoad_fb = true;

  /* InitializeConditions for Delay: '<S77>/Delay' */
  vehicle_control_DW_l.icLoad_o = true;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
