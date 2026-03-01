/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
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

#include "vehicle_control.h"
#include <math.h>
#include <stdbool.h>
#include "simulink_import.h"
#include <stdint.h>
#include "math.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern double rt_powd_snf(double u0, double u1);
static double look1_binlx(double u0, const double bp0[], const double table[],
  uint32_t maxIndex);
static double look1_binlc(double u0, const double bp0[], const double table[],
  uint32_t maxIndex);
static void MATLABFunction1(double rtu_torqueReq, double rtu_speed, double
  rtu_begin, double rtu_max, double *rty_torqueCmd);
static void MATLABFunction(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_last_y_6,
  double rtu_last_y_7, double rtu_u, double *rty_y);
static double rtGetInf(void);
static float rtGetInfF(void);
static double rtGetMinusInf(void);
static float rtGetMinusInfF(void);
static double rtGetNaN(void);
static float rtGetNaNF(void);
extern double rtInf;
extern double rtMinusInf;
extern double rtNaN;
extern float rtInfF;
extern float rtMinusInfF;
extern float rtNaNF;
static bool rtIsInf(double value);
static bool rtIsInfF(float value);
static bool rtIsNaN(double value);
static bool rtIsNaNF(float value);
double rtNaN = -(double)NAN;
double rtInf = (double)INFINITY;
double rtMinusInf = -(double)INFINITY;
float rtNaNF = -(float)NAN;
float rtInfF = (float)INFINITY;
float rtMinusInfF = -(float)INFINITY;

/* Return rtInf needed by the generated code. */
static double rtGetInf(void)
{
  return rtInf;
}

/* Get rtInfF needed by the generated code. */
static float rtGetInfF(void)
{
  return rtInfF;
}

/* Return rtMinusInf needed by the generated code. */
static double rtGetMinusInf(void)
{
  return rtMinusInf;
}

/* Return rtMinusInfF needed by the generated code. */
static float rtGetMinusInfF(void)
{
  return rtMinusInfF;
}

/* Return rtNaN needed by the generated code. */
static double rtGetNaN(void)
{
  return rtNaN;
}

/* Return rtNaNF needed by the generated code. */
static float rtGetNaNF(void)
{
  return rtNaNF;
}

/* Test if value is infinite */
static bool rtIsInf(double value)
{
  return (bool)isinf(value);
}

/* Test if single-precision value is infinite */
static bool rtIsInfF(float value)
{
  return (bool)isinf(value);
}

/* Test if value is not a number */
static bool rtIsNaN(double value)
{
  return (bool)(isnan(value) != 0);
}

/* Test if single-precision value is not a number */
static bool rtIsNaNF(float value)
{
  return (bool)(isnan(value) != 0);
}

static double look1_binlx(double u0, const double bp0[], const double table[],
  uint32_t maxIndex)
{
  double frac;
  double yL_0d0;
  uint32_t iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_t bpIdx;
    uint32_t iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

static double look1_binlc(double u0, const double bp0[], const double table[],
  uint32_t maxIndex)
{
  double frac;
  double yL_0d0;
  uint32_t iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_t bpIdx;
    uint32_t iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = 1.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/*
 * Output and update for atomic system:
 *    '<S4>/MATLAB Function1'
 *    '<S4>/MATLAB Function2'
 */
static void MATLABFunction1(double rtu_torqueReq, double rtu_speed, double
  rtu_begin, double rtu_max, double *rty_torqueCmd)
{
  if (rtu_speed > rtu_max) {
    *rty_torqueCmd = 0.0;
  } else if (rtu_speed < rtu_begin) {
    *rty_torqueCmd = rtu_torqueReq;
  } else {
    *rty_torqueCmd = (1.0 - (rtu_speed - rtu_begin) / rtu_max) * rtu_torqueReq;
  }
}

/*
 * Output and update for atomic system:
 *    '<S21>/MATLAB Function'
 *    '<S22>/MATLAB Function'
 *    '<S23>/MATLAB Function'
 *    '<S24>/MATLAB Function'
 *    '<S25>/MATLAB Function'
 *    '<S26>/MATLAB Function'
 */
static void MATLABFunction(double rtu_last_y_1, double rtu_last_y_2, double
  rtu_last_y_3, double rtu_last_y_4, double rtu_last_y_5, double rtu_last_y_6,
  double rtu_last_y_7, double rtu_u, double *rty_y)
{
  *rty_y = (((((((rtu_last_y_1 + rtu_last_y_2) + rtu_last_y_3) + rtu_last_y_4) +
               rtu_last_y_5) + rtu_last_y_6) + rtu_last_y_7) + rtu_u) / 8.0;
}

double rt_powd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    double tmp;
    double tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void vehicle_control_step(vehicle_control_RT_MODEL *const rtM,
  vehicle_control_ExtU *rtU, vehicle_control_ExtY *rtY)
{
  vehicle_control_DW *rtDW = rtM->dwork;

  /* local block i/o variables */
  double rtb_TSamp;
  double rtb_UnitDelay;
  double rtb_UnitDelay1;
  double rtb_UnitDelay2;
  double rtb_UnitDelay3;
  double rtb_UnitDelay4;
  double rtb_UnitDelay5;
  double rtb_UnitDelay_m;
  double rtb_UnitDelay1_h;
  double rtb_UnitDelay2_l;
  double rtb_UnitDelay3_i;
  double rtb_UnitDelay4_g;
  double rtb_UnitDelay5_i;
  double rtb_TSamp_d;

  {
    double C_alhpa_r_tmp;
    double C_alhpa_r_tmp_0;
    double C_alhpa_r_tmp_tmp;
    double rtb_F_aero;
    double rtb_F_dy;
    double rtb_FzFL;
    double rtb_FzFL_tmp;
    double rtb_FzFR;
    double rtb_Gain;
    double rtb_Gain2;
    double rtb_uDLookupTable1;
    double u0;
    bool limitedCache;

    /* UnitConversion: '<S3>/Unit Conversion' */
    /* Unit Conversion - from: deg/s to: rad/s
       Expression: output = (0.0174533*input) + (0) */
    rtb_Gain2 = 0.017453292519943295 * rtU->cockpit.steer;

    /* Gain: '<S28>/Gain4' incorporates:
     *  Gain: '<Root>/Gain2'
     *  Lookup_n-D: '<S28>/SteerWheel to SteerAngle(L)'
     *  Lookup_n-D: '<S28>/SteerWheel to SteerAngle(R)'
     *  Sum: '<S28>/Add'
     */
    rtb_Gain2 = (look1_binlx(rtb_Gain2, rtConstP.pooled4,
      rtConstP.SteerWheeltoSteerAngleL_tableDa, 100U) + look1_binlx(rtb_Gain2,
      rtConstP.pooled4, rtConstP.SteerWheeltoSteerAngleR_tableDa, 100U)) * 0.5;

    /* UnitDelay: '<S26>/Unit Delay' */
    rtDW->UnitDelay = rtDW->UnitDelay_DSTATE;

    /* UnitDelay: '<S26>/Unit Delay1' */
    rtDW->UnitDelay1 = rtDW->UnitDelay1_DSTATE;

    /* UnitDelay: '<S26>/Unit Delay2' */
    rtDW->UnitDelay2 = rtDW->UnitDelay2_DSTATE;

    /* UnitDelay: '<S26>/Unit Delay3' */
    rtDW->UnitDelay3 = rtDW->UnitDelay3_DSTATE;

    /* UnitDelay: '<S26>/Unit Delay4' */
    rtDW->UnitDelay4 = rtDW->UnitDelay4_DSTATE;

    /* UnitDelay: '<S26>/Unit Delay5' */
    rtDW->UnitDelay5 = rtDW->UnitDelay5_DSTATE;

    /* MATLAB Function: '<S26>/MATLAB Function' incorporates:
     *  MATLAB Function: '<S29>/reference yaw rate 1'
     *  UnitDelay: '<S26>/Unit Delay6'
     */
    MATLABFunction(rtDW->UnitDelay, rtDW->UnitDelay1, rtDW->UnitDelay2,
                   rtDW->UnitDelay3, rtDW->UnitDelay4, rtDW->UnitDelay5,
                   rtDW->UnitDelay6_DSTATE, rtU->vehicle_state.velocity.x *
                   rtb_Gain2 / 1.6, &rtDW->y);

    /* SampleTimeMath: '<S10>/TSamp'
     *
     * About '<S10>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    rtb_TSamp = rtDW->y * 100.0;

    /* UnitDelay: '<S24>/Unit Delay' */
    rtb_UnitDelay = rtDW->UnitDelay_DSTATE_h;

    /* UnitDelay: '<S24>/Unit Delay1' */
    rtb_UnitDelay1 = rtDW->UnitDelay1_DSTATE_b;

    /* UnitDelay: '<S24>/Unit Delay2' */
    rtb_UnitDelay2 = rtDW->UnitDelay2_DSTATE_g;

    /* UnitDelay: '<S24>/Unit Delay3' */
    rtb_UnitDelay3 = rtDW->UnitDelay3_DSTATE_n;

    /* UnitDelay: '<S24>/Unit Delay4' */
    rtb_UnitDelay4 = rtDW->UnitDelay4_DSTATE_p;

    /* UnitDelay: '<S24>/Unit Delay5' */
    rtb_UnitDelay5 = rtDW->UnitDelay5_DSTATE_d;

    /* MATLAB Function: '<S24>/MATLAB Function' incorporates:
     *  Sum: '<S10>/Diff'
     *  UnitDelay: '<S10>/UD'
     *  UnitDelay: '<S24>/Unit Delay6'
     *
     * Block description for '<S10>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S10>/UD':
     *
     *  Store in Global RAM
     */
    MATLABFunction(rtb_UnitDelay, rtb_UnitDelay1, rtb_UnitDelay2, rtb_UnitDelay3,
                   rtb_UnitDelay4, rtb_UnitDelay5, rtDW->UnitDelay6_DSTATE_e,
                   rtb_TSamp - rtDW->UD_DSTATE, &rtDW->y_f);

    /* UnitDelay: '<S25>/Unit Delay' */
    rtb_UnitDelay_m = rtDW->UnitDelay_DSTATE_d;

    /* UnitDelay: '<S25>/Unit Delay1' */
    rtb_UnitDelay1_h = rtDW->UnitDelay1_DSTATE_g;

    /* UnitDelay: '<S25>/Unit Delay2' */
    rtb_UnitDelay2_l = rtDW->UnitDelay2_DSTATE_a;

    /* UnitDelay: '<S25>/Unit Delay3' */
    rtb_UnitDelay3_i = rtDW->UnitDelay3_DSTATE_p;

    /* UnitDelay: '<S25>/Unit Delay4' */
    rtb_UnitDelay4_g = rtDW->UnitDelay4_DSTATE_e;

    /* UnitDelay: '<S25>/Unit Delay5' */
    rtb_UnitDelay5_i = rtDW->UnitDelay5_DSTATE_a;

    /* UnitDelay: '<S23>/Unit Delay' */
    rtDW->UnitDelay_e = rtDW->UnitDelay_DSTATE_b;

    /* UnitDelay: '<S23>/Unit Delay1' */
    rtDW->UnitDelay1_l = rtDW->UnitDelay1_DSTATE_j;

    /* UnitDelay: '<S23>/Unit Delay2' */
    rtDW->UnitDelay2_i = rtDW->UnitDelay2_DSTATE_an;

    /* UnitDelay: '<S23>/Unit Delay3' */
    rtDW->UnitDelay3_p = rtDW->UnitDelay3_DSTATE_c;

    /* UnitDelay: '<S23>/Unit Delay4' */
    rtDW->UnitDelay4_c = rtDW->UnitDelay4_DSTATE_en;

    /* UnitDelay: '<S23>/Unit Delay5' */
    rtDW->UnitDelay5_j = rtDW->UnitDelay5_DSTATE_b;

    /* MATLAB Function: '<S23>/MATLAB Function' incorporates:
     *  UnitDelay: '<S23>/Unit Delay6'
     */
    MATLABFunction(rtDW->UnitDelay_e, rtDW->UnitDelay1_l, rtDW->UnitDelay2_i,
                   rtDW->UnitDelay3_p, rtDW->UnitDelay4_c, rtDW->UnitDelay5_j,
                   rtDW->UnitDelay6_DSTATE_m, rtU->imu.gyro.z, &rtDW->y_m);

    /* SampleTimeMath: '<S11>/TSamp'
     *
     * About '<S11>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    rtb_TSamp_d = rtDW->y_m * 100.0;

    /* MATLAB Function: '<S25>/MATLAB Function' incorporates:
     *  Sum: '<S11>/Diff'
     *  UnitDelay: '<S11>/UD'
     *  UnitDelay: '<S25>/Unit Delay6'
     *
     * Block description for '<S11>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S11>/UD':
     *
     *  Store in Global RAM
     */
    MATLABFunction(rtb_UnitDelay_m, rtb_UnitDelay1_h, rtb_UnitDelay2_l,
                   rtb_UnitDelay3_i, rtb_UnitDelay4_g, rtb_UnitDelay5_i,
                   rtDW->UnitDelay6_DSTATE_l, rtb_TSamp_d - rtDW->UD_DSTATE_h,
                   &rtDW->y_a);

    /* MATLAB Function: '<S20>/MATLAB Function3' */
    rtb_F_aero = rtU->vehicle_state.velocity.x * rtU->vehicle_state.velocity.x *
      0.6125 * 2.2;

    /* UnitDelay: '<S21>/Unit Delay' */
    rtDW->UnitDelay_f = rtDW->UnitDelay_DSTATE_l;

    /* UnitDelay: '<S21>/Unit Delay1' */
    rtDW->UnitDelay1_h = rtDW->UnitDelay1_DSTATE_ju;

    /* UnitDelay: '<S21>/Unit Delay2' */
    rtDW->UnitDelay2_f = rtDW->UnitDelay2_DSTATE_p;

    /* UnitDelay: '<S21>/Unit Delay3' */
    rtDW->UnitDelay3_j = rtDW->UnitDelay3_DSTATE_e;

    /* UnitDelay: '<S21>/Unit Delay4' */
    rtDW->UnitDelay4_i = rtDW->UnitDelay4_DSTATE_b;

    /* UnitDelay: '<S21>/Unit Delay5' */
    rtDW->UnitDelay5_a = rtDW->UnitDelay5_DSTATE_n;

    /* MATLAB Function: '<S21>/MATLAB Function' incorporates:
     *  UnitDelay: '<S21>/Unit Delay6'
     */
    MATLABFunction(rtDW->UnitDelay_f, rtDW->UnitDelay1_h, rtDW->UnitDelay2_f,
                   rtDW->UnitDelay3_j, rtDW->UnitDelay4_i, rtDW->UnitDelay5_a,
                   rtDW->UnitDelay6_DSTATE_j, rtU->imu.accel.x, &rtDW->y_h);

    /* Gain: '<S20>/Gain' incorporates:
     *  MATLAB Function: '<S20>/MATLAB Function2'
     */
    rtb_Gain = 0.18749999999999997 * rtDW->y_h * 307.0 * 0.5;

    /* UnitDelay: '<S22>/Unit Delay' */
    rtDW->UnitDelay_g = rtDW->UnitDelay_DSTATE_a;

    /* UnitDelay: '<S22>/Unit Delay1' */
    rtDW->UnitDelay1_o = rtDW->UnitDelay1_DSTATE_p;

    /* UnitDelay: '<S22>/Unit Delay2' */
    rtDW->UnitDelay2_b = rtDW->UnitDelay2_DSTATE_as;

    /* UnitDelay: '<S22>/Unit Delay3' */
    rtDW->UnitDelay3_l = rtDW->UnitDelay3_DSTATE_d;

    /* UnitDelay: '<S22>/Unit Delay4' */
    rtDW->UnitDelay4_a = rtDW->UnitDelay4_DSTATE_a;

    /* UnitDelay: '<S22>/Unit Delay5' */
    rtDW->UnitDelay5_jx = rtDW->UnitDelay5_DSTATE_h;

    /* MATLAB Function: '<S22>/MATLAB Function' incorporates:
     *  UnitDelay: '<S22>/Unit Delay6'
     */
    MATLABFunction(rtDW->UnitDelay_g, rtDW->UnitDelay1_o, rtDW->UnitDelay2_b,
                   rtDW->UnitDelay3_l, rtDW->UnitDelay4_a, rtDW->UnitDelay5_jx,
                   rtDW->UnitDelay6_DSTATE_f, rtU->imu.accel.y, &rtDW->y_p);

    /* MATLAB Function: '<S20>/MATLAB Function1' */
    rtb_F_dy = 0.24193548387096772 * rtDW->y_p * 307.0;

    /* Lookup_n-D: '<S20>/1-D Lookup Table1' */
    rtb_uDLookupTable1 = look1_binlc(rtb_F_dy, rtConstP.uDLookupTable1_bp01Data,
      rtConstP.uDLookupTable1_tableData, 1U);

    /* Sum: '<S20>/Subtract' */
    rtb_F_dy -= rtb_uDLookupTable1;

    /* MATLAB Function: '<S20>/MATLAB Function4' */
    rtb_FzFL_tmp = rtb_F_aero * 0.48 / 2.0;
    rtb_FzFL = ((658.56000000000006 - rtb_Gain) - rtb_F_dy) + rtb_FzFL_tmp;
    rtb_FzFR = ((658.56000000000006 - rtb_Gain) + rtb_F_dy) + rtb_FzFL_tmp;
    rtb_F_aero = rtb_F_aero * 0.52 / 2.0;
    rtb_F_dy = ((rtb_Gain + 909.43999999999994) - rtb_uDLookupTable1) +
      rtb_F_aero;
    rtb_F_aero += (rtb_Gain + 909.43999999999994) + rtb_uDLookupTable1;

    /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
     *  Constant: '<S5>/FR_ratio'
     *  Constant: '<S5>/scaling'
     *  MATLAB Function: '<S5>/MATLAB Function3'
     *  MATLAB Function: '<S5>/Torque_Max'
     */
    rtb_FzFL = (rtb_FzFL * rtb_FzFL * -0.00059 + 1.46113 * rtb_FzFL) + 17.01657;
    rtb_Gain = (rtb_FzFR * rtb_FzFR * -0.00059 + 1.46113 * rtb_FzFR) + 17.01657;
    rtb_uDLookupTable1 = (rtb_FzFL * scaling + rtb_Gain * scaling) * fr_ratio;
    rtb_FzFL_tmp = rtb_F_dy * rtb_F_dy;
    C_alhpa_r_tmp = (rtb_FzFL_tmp * -0.00059 + 1.46113 * rtb_F_dy) + 17.01657;
    C_alhpa_r_tmp_tmp = rtb_F_aero * rtb_F_aero;
    C_alhpa_r_tmp_0 = (C_alhpa_r_tmp_tmp * -0.00059 + 1.46113 * rtb_F_aero) +
      17.01657;
    rtb_FzFR = C_alhpa_r_tmp * scaling + C_alhpa_r_tmp_0 * scaling;

    /* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
     *  Constant: '<S5>/FR_ratio'
     *  Constant: '<S5>/scaling'
     *  MATLAB Function: '<S5>/MATLAB Function3'
     */
    rtb_FzFL = (rtDW->y - rtDW->y_m) / fabs((1.0 / ((rtb_FzFL * scaling +
      rtb_Gain * scaling) * fr_ratio) + 1.0 / (C_alhpa_r_tmp * scaling +
      C_alhpa_r_tmp_0 * scaling)) * (rtb_Gain2 * rt_powd_snf
      (rtU->vehicle_state.velocity.x, 3.0) * rtDW->y_p) / 4.096000000000001);

    /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
     *  MATLAB Function: '<S5>/Torque_Max'
     */
    rtb_Gain = cos(rtb_Gain2);

    /* Gain: '<S5>/Gain2' incorporates:
     *  Sum: '<S5>/Subtract3'
     */
    u0 = (rtDW->y_f - rtDW->y_a) * 51.0;

    /* Saturate: '<S5>/Saturation1' */
    if (u0 > 300.0) {
      u0 = 300.0;
    } else if (u0 < -300.0) {
      u0 = -300.0;
    }

    /* MATLAB Function: '<S5>/MATLAB Function4' */
    if (!(rtU->vehicle_state.velocity.x > 5.0)) {
      if ((rtU->vehicle_state.velocity.x <= 5.0) &&
          (rtU->vehicle_state.velocity.x > 2.0)) {
        rtb_FzFL = (rtU->vehicle_state.velocity.x - 2.0) * rtb_FzFL / 3.0;
      } else {
        rtb_FzFL = 0.0;
      }
    }

    /* Product: '<S19>/Product' incorporates:
     *  Constant: '<S19>/track'
     *  Constant: '<S19>/wheel radius'
     *  Gain: '<S5>/FB_Gain'
     *  Gain: '<S5>/FF_Dyna_Gain'
     *  Gain: '<S5>/FF_Gain'
     *  MATLAB Function: '<S5>/MATLAB Function'
     *  MATLAB Function: '<S5>/MATLAB Function4'
     *  Product: '<S19>/Divide'
     *  Saturate: '<S5>/Saturation1'
     *  Sum: '<S5>/Sum2'
     */
    rtb_Gain2 = (((0.672 * rtb_FzFR - 0.92799999999999994 * rtb_uDLookupTable1 *
                   rtb_Gain) / (rtb_uDLookupTable1 + rtb_FzFR) * 320.0 *
                  (rtU->vehicle_state.velocity.x * rtU->vehicle_state.velocity.x)
                  / 1.6 * rtb_Gain2 * ff_gain + ff_dyna_gain * u0) + fb_gain *
                 rtb_FzFL) / 1.24 * 0.254;

    /* Saturate: '<S5>/Saturation' */
    if (rtb_Gain2 > 210.0) {
      rtb_Gain2 = 210.0;
    } else if (rtb_Gain2 < -210.0) {
      rtb_Gain2 = -210.0;
    }

    /* End of Saturate: '<S5>/Saturation' */

    /* Switch: '<S5>/Switch2' incorporates:
     *  Constant: '<S5>/Constant1'
     *  MATLAB Function: '<S5>/MATLAB Function2'
     */
    if (rtU->cockpit.brake > 0.1) {
      rtb_FzFL = 0.0;
    } else if (rtU->vehicle_state.velocity.x > 4.0) {
      /* MATLAB Function: '<S5>/MATLAB Function2' */
      rtb_FzFL = rtb_Gain2;
    } else if ((rtU->vehicle_state.velocity.x <= 4.0) &&
               (rtU->vehicle_state.velocity.x > 2.0)) {
      /* MATLAB Function: '<S5>/MATLAB Function2' */
      rtb_FzFL = (rtU->vehicle_state.velocity.x - 2.0) * rtb_Gain2 / 2.0;
    } else {
      rtb_FzFL = 0.0;
    }

    /* End of Switch: '<S5>/Switch2' */

    /* Gain: '<Root>/Gain2' */
    rtb_Gain2 = 0.01 * rtU->cockpit.accel;

    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S5>/Constant'
     *  Gain: '<S5>/Gain'
     *  Product: '<S5>/Product'
     */
    rtb_FzFR = trq_lim * rtb_Gain2 * 13.1 - rtb_FzFL;

    /* MATLAB Function: '<S5>/Torque_Max' incorporates:
     *  Constant: '<S5>/TC_limit'
     *  Constant: '<S5>/scaling'
     */
    rtb_uDLookupTable1 = 0.92799999999999994 * rtb_Gain;
    rtb_Gain = fabs((rtb_uDLookupTable1 * 320.0 * rtDW->y_p - 51.0 * rtDW->y_a) /
                    (rtb_uDLookupTable1 + 0.672));
    rtb_uDLookupTable1 = C_alhpa_r_tmp_0 * scaling * rtb_Gain / (C_alhpa_r_tmp *
      scaling + C_alhpa_r_tmp_0 * scaling);
    rtb_F_aero = (1.0 - rtb_uDLookupTable1 / (((C_alhpa_r_tmp_tmp * -0.0005 +
      3.2826 * rtb_F_aero) - 37.404) * scaling)) * ((2.4825 * rtb_F_aero +
      0.4821) * scaling) / 0.254 * tc_lim;
    rtb_F_dy = (1.0 - (rtb_Gain - rtb_uDLookupTable1) / (((rtb_FzFL_tmp *
      -0.0005 + 3.2826 * rtb_F_dy) - 37.404) * scaling)) * ((2.4825 * rtb_F_dy +
      0.4821) * scaling) / 0.254 * tc_lim;

    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S5>/TC_Switch'
     */
    if (tc_switch > 0.0) {
      /* Saturate: '<S5>/Saturation3' */
      if (rtb_F_dy <= 0.0) {
        rtb_F_dy = 0.0;
      }

      /* End of Saturate: '<S5>/Saturation3' */

      /* Switch: '<S17>/Switch2' incorporates:
       *  RelationalOperator: '<S17>/LowerRelop1'
       */
      if (rtb_FzFR > rtb_F_dy) {
        rtb_FzFR = rtb_F_dy;
      } else {
        /* Gain: '<S5>/Gain3' */
        rtb_F_dy = -rtb_F_dy;

        /* Switch: '<S17>/Switch' incorporates:
         *  RelationalOperator: '<S17>/UpperRelop'
         */
        if (rtb_FzFR < rtb_F_dy) {
          rtb_FzFR = rtb_F_dy;
        }

        /* End of Switch: '<S17>/Switch' */
      }

      /* End of Switch: '<S17>/Switch2' */
    }

    /* End of Switch: '<S5>/Switch' */

    /* MATLAB Function: '<S4>/MATLAB Function1' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant5'
     *  Gain: '<Root>/Gain3'
     */
    MATLABFunction1(0.076335877862595422 * rtb_FzFR, 0.0, torq_derate_begin,
                    torq_derate_end, &rtb_F_dy);

    /* Switch: '<S8>/Switch2' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     *  RelationalOperator: '<S8>/LowerRelop1'
     *  RelationalOperator: '<S8>/UpperRelop'
     *  Switch: '<S8>/Switch'
     */
    if (rtb_F_dy > torq_limit_rl) {
      rtb_F_dy = torq_limit_rl;
    } else if (rtb_F_dy < -torq_limit_rl) {
      /* Switch: '<S8>/Switch' incorporates:
       *  Constant: '<S4>/Constant'
       */
      rtb_F_dy = -torq_limit_rl;
    }

    /* End of Switch: '<S8>/Switch2' */

    /* RateLimiter: '<S4>/Rate Limiter1' */
    if (rtDW->LastMajorTime == (rtInf)) {
      /* RateLimiter: '<S4>/Rate Limiter1' */
      rtDW->RateLimiter1 = rtb_F_dy;
    } else {
      rtb_Gain = rtM->Timing.t[0];
      rtb_FzFR = rtb_Gain - rtDW->LastMajorTime;
      if (rtDW->LastMajorTime == rtb_Gain) {
        if (rtDW->PrevLimited) {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY;
        } else {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtb_F_dy;
        }
      } else {
        rtb_uDLookupTable1 = rtb_FzFR * torq_slew;
        rtb_Gain = rtb_F_dy - rtDW->PrevY;
        if (rtb_Gain > rtb_uDLookupTable1) {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY + rtb_uDLookupTable1;
          limitedCache = true;
        } else {
          rtb_FzFR *= -torq_slew;
          if (rtb_Gain < rtb_FzFR) {
            /* RateLimiter: '<S4>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtDW->PrevY + rtb_FzFR;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S4>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtb_F_dy;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S4>/Rate Limiter1' */

    /* Sum: '<S5>/Sum1' incorporates:
     *  Constant: '<S5>/Constant'
     *  Gain: '<S5>/Gain1'
     *  Product: '<S5>/Product1'
     */
    rtb_FzFR = rtb_Gain2 * trq_lim * 13.1 + rtb_FzFL;

    /* Switch: '<S5>/Switch1' incorporates:
     *  Constant: '<S5>/TC_Switch'
     */
    if (tc_switch > 0.0) {
      /* Saturate: '<S5>/Saturation2' */
      if (rtb_F_aero <= 0.0) {
        rtb_Gain2 = 0.0;
      } else {
        rtb_Gain2 = rtb_F_aero;
      }

      /* End of Saturate: '<S5>/Saturation2' */

      /* Switch: '<S18>/Switch2' incorporates:
       *  RelationalOperator: '<S18>/LowerRelop1'
       */
      if (rtb_FzFR > rtb_Gain2) {
        rtb_FzFR = rtb_Gain2;
      } else {
        /* Gain: '<S5>/Gain4' */
        rtb_Gain2 = -rtb_Gain2;

        /* Switch: '<S18>/Switch' incorporates:
         *  RelationalOperator: '<S18>/UpperRelop'
         */
        if (rtb_FzFR < rtb_Gain2) {
          rtb_FzFR = rtb_Gain2;
        }

        /* End of Switch: '<S18>/Switch' */
      }

      /* End of Switch: '<S18>/Switch2' */
    }

    /* End of Switch: '<S5>/Switch1' */

    /* MATLAB Function: '<S4>/MATLAB Function2' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant5'
     *  Gain: '<Root>/Gain4'
     */
    MATLABFunction1(0.076335877862595422 * rtb_FzFR, 0.0, torq_derate_begin,
                    torq_derate_end, &rtb_FzFR);

    /* Switch: '<S9>/Switch2' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Constant: '<S4>/Constant3'
     *  RelationalOperator: '<S9>/LowerRelop1'
     *  RelationalOperator: '<S9>/UpperRelop'
     *  Switch: '<S9>/Switch'
     */
    if (rtb_FzFR > torq_limit_rr) {
      rtb_Gain2 = torq_limit_rr;
    } else if (rtb_FzFR < -torq_limit_rr) {
      /* Switch: '<S9>/Switch' incorporates:
       *  Constant: '<S4>/Constant3'
       */
      rtb_Gain2 = -torq_limit_rr;
    } else {
      rtb_Gain2 = rtb_FzFR;
    }

    /* End of Switch: '<S9>/Switch2' */

    /* RateLimiter: '<S4>/Rate Limiter' */
    if (rtDW->LastMajorTime_b == (rtInf)) {
      /* RateLimiter: '<S4>/Rate Limiter' */
      rtDW->RateLimiter = rtb_Gain2;
    } else {
      rtb_Gain = rtM->Timing.t[0];
      rtb_FzFR = rtb_Gain - rtDW->LastMajorTime_b;
      if (rtDW->LastMajorTime_b == rtb_Gain) {
        if (rtDW->PrevLimited_p) {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_a;
        } else {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtb_Gain2;
        }
      } else {
        rtb_uDLookupTable1 = rtb_FzFR * torq_slew;
        rtb_Gain = rtb_Gain2 - rtDW->PrevY_a;
        if (rtb_Gain > rtb_uDLookupTable1) {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_a + rtb_uDLookupTable1;
          limitedCache = true;
        } else {
          rtb_FzFR *= -torq_slew;
          if (rtb_Gain < rtb_FzFR) {
            /* RateLimiter: '<S4>/Rate Limiter' */
            rtDW->RateLimiter = rtDW->PrevY_a + rtb_FzFR;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S4>/Rate Limiter' */
            rtDW->RateLimiter = rtb_Gain2;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited_p = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S4>/Rate Limiter' */

    /* BusCreator generated from: '<Root>/tc_BusCreator' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    rtY->tc.header.timestamp_ns = 0ULL;

    /* BusCreator generated from: '<Root>/tc_BusCreator' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Constant: '<Root>/Constant5'
     *  Constant: '<Root>/Constant6'
     *  Constant: '<Root>/Constant7'
     *  Constant: '<Root>/Constant8'
     *  Outport: '<Root>/tc'
     */
    rtY->tc.sr_l = 0.0;
    rtY->tc.sr_r = 0.0;
    rtY->tc.sa = 0.0;
    rtY->tc.yawrate_real = 0.0;
    rtY->tc.yawrate_ref = 0.0;

    /* Outport: '<Root>/torq' incorporates:
     *  BusCreator generated from: '<Root>/torq_BusCreator'
     *  Constant: '<Root>/Constant'
     *  Constant: '<Root>/Constant1'
     *  Constant: '<Root>/Constant2'
     */
    rtY->torq.header.timestamp_ns = 0ULL;
    rtY->torq.torque.fl = 0.0;
    rtY->torq.torque.fr = 0.0;
    rtY->torq.torque.rl = rtDW->RateLimiter1;
    rtY->torq.torque.rr = rtDW->RateLimiter;
  }

  {
    double LastMajorTime_tmp;

    /* Update for UnitDelay: '<S26>/Unit Delay' */
    rtDW->UnitDelay_DSTATE = rtDW->y;

    /* Update for UnitDelay: '<S26>/Unit Delay1' */
    rtDW->UnitDelay1_DSTATE = rtDW->UnitDelay;

    /* Update for UnitDelay: '<S26>/Unit Delay2' */
    rtDW->UnitDelay2_DSTATE = rtDW->UnitDelay1;

    /* Update for UnitDelay: '<S26>/Unit Delay3' */
    rtDW->UnitDelay3_DSTATE = rtDW->UnitDelay2;

    /* Update for UnitDelay: '<S26>/Unit Delay4' */
    rtDW->UnitDelay4_DSTATE = rtDW->UnitDelay3;

    /* Update for UnitDelay: '<S26>/Unit Delay5' */
    rtDW->UnitDelay5_DSTATE = rtDW->UnitDelay4;

    /* Update for UnitDelay: '<S26>/Unit Delay6' */
    rtDW->UnitDelay6_DSTATE = rtDW->UnitDelay5;

    /* Update for UnitDelay: '<S10>/UD'
     *
     * Block description for '<S10>/UD':
     *
     *  Store in Global RAM
     */
    rtDW->UD_DSTATE = rtb_TSamp;

    /* Update for UnitDelay: '<S24>/Unit Delay' */
    rtDW->UnitDelay_DSTATE_h = rtDW->y_f;

    /* Update for UnitDelay: '<S24>/Unit Delay1' */
    rtDW->UnitDelay1_DSTATE_b = rtb_UnitDelay;

    /* Update for UnitDelay: '<S24>/Unit Delay2' */
    rtDW->UnitDelay2_DSTATE_g = rtb_UnitDelay1;

    /* Update for UnitDelay: '<S24>/Unit Delay3' */
    rtDW->UnitDelay3_DSTATE_n = rtb_UnitDelay2;

    /* Update for UnitDelay: '<S24>/Unit Delay4' */
    rtDW->UnitDelay4_DSTATE_p = rtb_UnitDelay3;

    /* Update for UnitDelay: '<S24>/Unit Delay5' */
    rtDW->UnitDelay5_DSTATE_d = rtb_UnitDelay4;

    /* Update for UnitDelay: '<S24>/Unit Delay6' */
    rtDW->UnitDelay6_DSTATE_e = rtb_UnitDelay5;

    /* Update for UnitDelay: '<S25>/Unit Delay' */
    rtDW->UnitDelay_DSTATE_d = rtDW->y_a;

    /* Update for UnitDelay: '<S25>/Unit Delay1' */
    rtDW->UnitDelay1_DSTATE_g = rtb_UnitDelay_m;

    /* Update for UnitDelay: '<S25>/Unit Delay2' */
    rtDW->UnitDelay2_DSTATE_a = rtb_UnitDelay1_h;

    /* Update for UnitDelay: '<S25>/Unit Delay3' */
    rtDW->UnitDelay3_DSTATE_p = rtb_UnitDelay2_l;

    /* Update for UnitDelay: '<S25>/Unit Delay4' */
    rtDW->UnitDelay4_DSTATE_e = rtb_UnitDelay3_i;

    /* Update for UnitDelay: '<S25>/Unit Delay5' */
    rtDW->UnitDelay5_DSTATE_a = rtb_UnitDelay4_g;

    /* Update for UnitDelay: '<S25>/Unit Delay6' */
    rtDW->UnitDelay6_DSTATE_l = rtb_UnitDelay5_i;

    /* Update for UnitDelay: '<S23>/Unit Delay' */
    rtDW->UnitDelay_DSTATE_b = rtDW->y_m;

    /* Update for UnitDelay: '<S23>/Unit Delay1' */
    rtDW->UnitDelay1_DSTATE_j = rtDW->UnitDelay_e;

    /* Update for UnitDelay: '<S23>/Unit Delay2' */
    rtDW->UnitDelay2_DSTATE_an = rtDW->UnitDelay1_l;

    /* Update for UnitDelay: '<S23>/Unit Delay3' */
    rtDW->UnitDelay3_DSTATE_c = rtDW->UnitDelay2_i;

    /* Update for UnitDelay: '<S23>/Unit Delay4' */
    rtDW->UnitDelay4_DSTATE_en = rtDW->UnitDelay3_p;

    /* Update for UnitDelay: '<S23>/Unit Delay5' */
    rtDW->UnitDelay5_DSTATE_b = rtDW->UnitDelay4_c;

    /* Update for UnitDelay: '<S23>/Unit Delay6' */
    rtDW->UnitDelay6_DSTATE_m = rtDW->UnitDelay5_j;

    /* Update for UnitDelay: '<S11>/UD'
     *
     * Block description for '<S11>/UD':
     *
     *  Store in Global RAM
     */
    rtDW->UD_DSTATE_h = rtb_TSamp_d;

    /* Update for UnitDelay: '<S21>/Unit Delay' */
    rtDW->UnitDelay_DSTATE_l = rtDW->y_h;

    /* Update for UnitDelay: '<S21>/Unit Delay1' */
    rtDW->UnitDelay1_DSTATE_ju = rtDW->UnitDelay_f;

    /* Update for UnitDelay: '<S21>/Unit Delay2' */
    rtDW->UnitDelay2_DSTATE_p = rtDW->UnitDelay1_h;

    /* Update for UnitDelay: '<S21>/Unit Delay3' */
    rtDW->UnitDelay3_DSTATE_e = rtDW->UnitDelay2_f;

    /* Update for UnitDelay: '<S21>/Unit Delay4' */
    rtDW->UnitDelay4_DSTATE_b = rtDW->UnitDelay3_j;

    /* Update for UnitDelay: '<S21>/Unit Delay5' */
    rtDW->UnitDelay5_DSTATE_n = rtDW->UnitDelay4_i;

    /* Update for UnitDelay: '<S21>/Unit Delay6' */
    rtDW->UnitDelay6_DSTATE_j = rtDW->UnitDelay5_a;

    /* Update for UnitDelay: '<S22>/Unit Delay' */
    rtDW->UnitDelay_DSTATE_a = rtDW->y_p;

    /* Update for UnitDelay: '<S22>/Unit Delay1' */
    rtDW->UnitDelay1_DSTATE_p = rtDW->UnitDelay_g;

    /* Update for UnitDelay: '<S22>/Unit Delay2' */
    rtDW->UnitDelay2_DSTATE_as = rtDW->UnitDelay1_o;

    /* Update for UnitDelay: '<S22>/Unit Delay3' */
    rtDW->UnitDelay3_DSTATE_d = rtDW->UnitDelay2_b;

    /* Update for UnitDelay: '<S22>/Unit Delay4' */
    rtDW->UnitDelay4_DSTATE_a = rtDW->UnitDelay3_l;

    /* Update for UnitDelay: '<S22>/Unit Delay5' */
    rtDW->UnitDelay5_DSTATE_h = rtDW->UnitDelay4_a;

    /* Update for UnitDelay: '<S22>/Unit Delay6' */
    rtDW->UnitDelay6_DSTATE_f = rtDW->UnitDelay5_jx;

    /* Update for RateLimiter: '<S4>/Rate Limiter1' incorporates:
     *  RateLimiter: '<S4>/Rate Limiter'
     */
    rtDW->PrevY = rtDW->RateLimiter1;
    LastMajorTime_tmp = rtM->Timing.t[0];
    rtDW->LastMajorTime = LastMajorTime_tmp;

    /* Update for RateLimiter: '<S4>/Rate Limiter' */
    rtDW->PrevY_a = rtDW->RateLimiter;
    rtDW->LastMajorTime_b = LastMajorTime_tmp;
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  rtM->Timing.t[0] =
    ((double)(++rtM->Timing.clockTick0)) * rtM->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.01, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }
}

/* Model initialize function */
void vehicle_control_initialize(vehicle_control_RT_MODEL *const rtM)
{
  vehicle_control_DW *rtDW = rtM->dwork;

  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&rtM->solverInfo, false);
  rtsiSetIsContModeFrozen(&rtM->solverInfo, false);
  rtsiSetSolverName(&rtM->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.01;

  memset(rtDW, 0, sizeof(vehicle_control_DW));

  /* InitializeConditions for RateLimiter: '<S4>/Rate Limiter1' */
  rtDW->LastMajorTime = (rtInf);

  /* InitializeConditions for RateLimiter: '<S4>/Rate Limiter' */
  rtDW->LastMajorTime_b = (rtInf);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */