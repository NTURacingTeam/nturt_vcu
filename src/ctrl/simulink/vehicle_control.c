/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 5.43
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Sat Feb  7 21:55:47 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Traceability
 *    2. Debugging
 * Validation result: Not run
 */

#include "vehicle_control.h"
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include "simulink_import.h"
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
static void MATLABFunction1(double rtu_torqueReq, double rtu_speed, double
  rtu_begin, double rtu_max, double *rty_torqueCmd);
static void MATLABFunction3(double rtu_y_last, double rtu_u, double *rty_y,
  vehicle_cont_DW_MATLABFunction3 *localDW);
static void MATLABFunction3_o(double rtu_y_last, double rtu_u, double *rty_y,
  vehicle_co_DW_MATLABFunction3_a *localDW);
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

/*
 * Output and update for atomic system:
 *    '<S4>/MATLAB Function1'
 *    '<S4>/MATLAB Function2'
 *    '<S5>/MATLAB Function1'
 *    '<S5>/MATLAB Function2'
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
 *    '<S26>/MATLAB Function3'
 *    '<S29>/MATLAB Function3'
 */
static void MATLABFunction3(double rtu_y_last, double rtu_u, double *rty_y,
  vehicle_cont_DW_MATLABFunction3 *localDW)
{
  if (!localDW->data_not_empty) {
    localDW->data[0] = 0.0;
    localDW->data[1] = 0.0;
    localDW->data[2] = 0.0;
    localDW->data[3] = 0.0;
    localDW->data_not_empty = true;
  } else {
    localDW->data[1] = localDW->data[0];
    localDW->data[2] = localDW->data[1];
    localDW->data[3] = localDW->data[2];
    localDW->data[0] = rtu_y_last;
  }

  *rty_y = ((((localDW->data[0] + localDW->data[1]) + localDW->data[2]) +
             localDW->data[3]) + rtu_u) / 5.0;
}

/*
 * Output and update for atomic system:
 *    '<S27>/MATLAB Function3'
 *    '<S28>/MATLAB Function3'
 *    '<S30>/MATLAB Function3'
 *    '<S31>/MATLAB Function3'
 *    '<S32>/MATLAB Function3'
 */
static void MATLABFunction3_o(double rtu_y_last, double rtu_u, double *rty_y,
  vehicle_co_DW_MATLABFunction3_a *localDW)
{
  double y;
  int32_t i;
  if (!localDW->data_not_empty) {
    memset(&localDW->data[0], 0, 9U * sizeof(double));
    localDW->data_not_empty = true;
  } else {
    for (i = 0; i < 8; i++) {
      localDW->data[i + 1] = localDW->data[i];
    }

    localDW->data[0] = rtu_y_last;
  }

  y = localDW->data[0];
  for (i = 0; i < 8; i++) {
    y += localDW->data[i + 1];
  }

  *rty_y = (y + rtu_u) / 10.0;
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
  double rtb_TSamp_d;

  {
    double C_alhpa_r_tmp;
    double C_alhpa_r_tmp_0;
    double C_alhpa_r_tmp_tmp;
    double rtb_F_aero;
    double rtb_F_dy;
    double rtb_F_dy_tmp;
    double rtb_FzFR;
    double rtb_Gain;
    double rtb_Gain4;
    double rtb_Subtract;
    double rtb_uDLookupTable;
    double u0;
    bool limitedCache;

    /* UnitConversion: '<S3>/Unit Conversion' */
    /* Unit Conversion - from: deg/s to: rad/s
       Expression: output = (0.0174533*input) + (0) */
    rtb_FzFR = 0.017453292519943295 * rtU->cockpit.steer;

    /* Gain: '<S34>/Gain4' incorporates:
     *  Lookup_n-D: '<S34>/SteerWheel to SteerAngle(L)'
     *  Lookup_n-D: '<S34>/SteerWheel to SteerAngle(R)'
     *  Sum: '<S34>/Add'
     *  Switch: '<S6>/Switch'
     */
    rtb_Gain4 = (look1_binlx(rtb_FzFR, rtConstP.pooled4,
      rtConstP.SteerWheeltoSteerAngleL_tableDa, 100U) + look1_binlx(rtb_FzFR,
      rtConstP.pooled4, rtConstP.SteerWheeltoSteerAngleR_tableDa, 100U)) * 0.5;

    /* MATLAB Function: '<S27>/MATLAB Function3' incorporates:
     *  MATLAB Function: '<S35>/reference yaw rate 1'
     *  Memory: '<S27>/Memory'
     */
    MATLABFunction3_o(rtDW->Memory_PreviousInput, rtU->vehicle_state.velocity.x *
                      rtb_Gain4 / 1.6, &rtDW->y_o, &rtDW->sf_MATLABFunction3_o);

    /* SampleTimeMath: '<S15>/TSamp'
     *
     * About '<S15>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    rtb_TSamp = rtDW->y_o * 100.0;

    /* MATLAB Function: '<S29>/MATLAB Function3' incorporates:
     *  Memory: '<S29>/Memory'
     *  Sum: '<S15>/Diff'
     *  UnitDelay: '<S15>/UD'
     *
     * Block description for '<S15>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S15>/UD':
     *
     *  Store in Global RAM
     */
    MATLABFunction3(rtDW->Memory_PreviousInput_l, rtb_TSamp - rtDW->UD_DSTATE,
                    &rtDW->y_p, &rtDW->sf_MATLABFunction3_g);

    /* MATLAB Function: '<S28>/MATLAB Function3' incorporates:
     *  Memory: '<S28>/Memory'
     */
    MATLABFunction3_o(rtDW->Memory_PreviousInput_i, rtU->imu.gyro.z, &rtDW->y_l,
                      &rtDW->sf_MATLABFunction3_pn);

    /* SampleTimeMath: '<S16>/TSamp'
     *
     * About '<S16>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    rtb_TSamp_d = rtDW->y_l * 100.0;

    /* MATLAB Function: '<S26>/MATLAB Function3' incorporates:
     *  Memory: '<S26>/Memory'
     *  Sum: '<S16>/Diff'
     *  UnitDelay: '<S16>/UD'
     *
     * Block description for '<S16>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S16>/UD':
     *
     *  Store in Global RAM
     */
    MATLABFunction3(rtDW->Memory_PreviousInput_k, rtb_TSamp_d -
                    rtDW->UD_DSTATE_h, &rtDW->y_k, &rtDW->sf_MATLABFunction3_m);

    /* MATLAB Function: '<S25>/MATLAB Function3' */
    rtb_F_aero = rtU->vehicle_state.velocity.x * rtU->vehicle_state.velocity.x *
      0.6125 * 2.2;

    /* MATLAB Function: '<S32>/MATLAB Function3' incorporates:
     *  Memory: '<S32>/Memory'
     */
    MATLABFunction3_o(rtDW->Memory_PreviousInput_h, rtU->imu.accel.x, &rtDW->y,
                      &rtDW->sf_MATLABFunction3_p4);

    /* Gain: '<S25>/Gain' incorporates:
     *  MATLAB Function: '<S25>/MATLAB Function2'
     */
    rtb_Gain = 0.18749999999999997 * rtDW->y * 307.0 * 0.5;

    /* MATLAB Function: '<S31>/MATLAB Function3' incorporates:
     *  Memory: '<S31>/Memory'
     */
    MATLABFunction3_o(rtDW->Memory_PreviousInput_o, rtU->imu.accel.y, &rtDW->y_e,
                      &rtDW->sf_MATLABFunction3_e);

    /* MATLAB Function: '<S25>/MATLAB Function1' */
    rtb_F_dy = 0.24193548387096772 * rtDW->y_e * 307.0;

    /* Lookup_n-D: '<S25>/1-D Lookup Table' */
    rtb_uDLookupTable = look1_binlx(rtb_F_dy, rtConstP.uDLookupTable_bp01Data,
      rtConstP.uDLookupTable_tableData, 2U);

    /* Sum: '<S25>/Subtract' */
    rtb_Subtract = rtb_F_dy - rtb_uDLookupTable;

    /* MATLAB Function: '<S25>/MATLAB Function4' */
    rtb_F_dy_tmp = rtb_F_aero * 0.48 / 2.0;
    rtb_F_dy = ((637.98 - rtb_Gain) - rtb_Subtract) + rtb_F_dy_tmp;
    rtb_FzFR = ((637.98 - rtb_Gain) + rtb_Subtract) + rtb_F_dy_tmp;
    rtb_F_aero = rtb_F_aero * 0.52 / 2.0;
    rtb_Subtract = ((rtb_Gain + 881.02) - rtb_uDLookupTable) + rtb_F_aero;
    rtb_F_aero += (rtb_Gain + 881.02) + rtb_uDLookupTable;

    /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
     *  Constant: '<S6>/FR_ratio'
     *  Constant: '<S6>/scaling'
     *  MATLAB Function: '<S6>/MATLAB Function3'
     *  MATLAB Function: '<S6>/Torque_Max'
     */
    rtb_Gain = (rtb_F_dy * rtb_F_dy * -0.00059 + 1.46113 * rtb_F_dy) + 17.01657;
    rtb_F_dy = (rtb_FzFR * rtb_FzFR * -0.00059 + 1.46113 * rtb_FzFR) + 17.01657;
    rtb_uDLookupTable = (rtb_Gain * scaling + rtb_F_dy * scaling) * fr_ratio;
    rtb_F_dy_tmp = rtb_Subtract * rtb_Subtract;
    C_alhpa_r_tmp = (rtb_F_dy_tmp * -0.00059 + 1.46113 * rtb_Subtract) +
      17.01657;
    C_alhpa_r_tmp_tmp = rtb_F_aero * rtb_F_aero;
    C_alhpa_r_tmp_0 = (C_alhpa_r_tmp_tmp * -0.00059 + 1.46113 * rtb_F_aero) +
      17.01657;
    rtb_FzFR = C_alhpa_r_tmp * scaling + C_alhpa_r_tmp_0 * scaling;

    /* MATLAB Function: '<S30>/MATLAB Function3' incorporates:
     *  Constant: '<S6>/FR_ratio'
     *  Constant: '<S6>/scaling'
     *  MATLAB Function: '<S6>/MATLAB Function3'
     *  Memory: '<S30>/Memory'
     */
    MATLABFunction3_o(rtDW->Memory_PreviousInput_p, rtb_Gain4 * rt_powd_snf
                      (rtU->vehicle_state.velocity.x, 3.0) * rtDW->y_e * (1.0 /
      ((rtb_Gain * scaling + rtb_F_dy * scaling) * fr_ratio) + 1.0 /
      (C_alhpa_r_tmp * scaling + C_alhpa_r_tmp_0 * scaling)) / 4.096000000000001,
                      &rtDW->y_g, &rtDW->sf_MATLABFunction3_m0);

    /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
     *  MATLAB Function: '<S6>/Torque_Max'
     */
    rtb_Gain = cos(rtb_Gain4);

    /* Switch: '<S6>/Switch2' incorporates:
     *  Constant: '<S6>/Constant1'
     *  MATLAB Function: '<S6>/MATLAB Function2'
     */
    if (rtU->cockpit.brake > 0.1) {
      rtb_F_dy = 0.0;
    } else if (rtU->vehicle_state.velocity.x > 2.0) {
      /* MATLAB Function: '<S6>/MATLAB Function4' incorporates:
       *  MATLAB Function: '<S6>/MATLAB Function1'
       */
      if (rtU->vehicle_state.velocity.x > 5.0) {
        rtb_F_dy = (rtDW->y_o - rtDW->y_l) / rtDW->y_g;
      } else {
        rtb_F_dy = 0.0;
      }

      /* Gain: '<S6>/Gain2' incorporates:
       *  Sum: '<S6>/Subtract3'
       */
      u0 = (rtDW->y_p - rtDW->y_k) * 51.0;

      /* Saturate: '<S6>/Saturation1' */
      if (u0 > 300.0) {
        u0 = 300.0;
      } else if (u0 < -300.0) {
        u0 = -300.0;
      }

      /* Product: '<S24>/Product' incorporates:
       *  Constant: '<S24>/track'
       *  Constant: '<S24>/wheel radius'
       *  Gain: '<S6>/FB_Gain'
       *  Gain: '<S6>/FF_Dyna_Gain'
       *  Gain: '<S6>/FF_Gain'
       *  MATLAB Function: '<S6>/MATLAB Function'
       *  MATLAB Function: '<S6>/MATLAB Function4'
       *  Product: '<S24>/Divide'
       *  Saturate: '<S6>/Saturation1'
       *  Sum: '<S6>/Sum2'
       */
      rtb_F_dy = (((0.672 * rtb_FzFR - 0.92799999999999994 * rtb_uDLookupTable *
                    rtb_Gain) / (rtb_uDLookupTable + rtb_FzFR) * 310.0 *
                   (rtU->vehicle_state.velocity.x *
                    rtU->vehicle_state.velocity.x) / 1.6 * rtb_Gain4 * ff_gain +
                   ff_dyna_gain * u0) + fb_gain * rtb_F_dy) / 1.24 * 0.259;

      /* Saturate: '<S6>/Saturation' */
      if (rtb_F_dy > 210.0) {
        /* MATLAB Function: '<S6>/MATLAB Function2' */
        rtb_F_dy = 210.0;
      } else if (rtb_F_dy < -210.0) {
        /* MATLAB Function: '<S6>/MATLAB Function2' */
        rtb_F_dy = -210.0;
      }

      /* End of Saturate: '<S6>/Saturation' */
    } else {
      rtb_F_dy = 0.0;
    }

    /* End of Switch: '<S6>/Switch2' */

    /* Gain: '<Root>/Gain2' */
    rtb_Gain4 = 0.01 * rtU->cockpit.accel;

    /* Sum: '<S6>/Sum' incorporates:
     *  Constant: '<S6>/Constant'
     *  Gain: '<S6>/Gain'
     *  Product: '<S6>/Product'
     */
    rtb_FzFR = trq_lim * rtb_Gain4 * 13.1 - rtb_F_dy;

    /* MATLAB Function: '<S6>/Torque_Max' incorporates:
     *  Constant: '<S6>/Constant4'
     *  Constant: '<S6>/scaling'
     */
    rtb_uDLookupTable = 0.92799999999999994 * rtb_Gain;
    rtb_Gain = fabs((rtb_uDLookupTable * 310.0 * rtDW->y_e - 51.0 * rtDW->y_k) /
                    (rtb_uDLookupTable + 0.672));
    rtb_uDLookupTable = C_alhpa_r_tmp_0 * scaling * rtb_Gain / (C_alhpa_r_tmp *
      scaling + C_alhpa_r_tmp_0 * scaling);
    rtb_F_aero = (1.0 - rtb_uDLookupTable / (((C_alhpa_r_tmp_tmp * -0.0005 +
      3.2826 * rtb_F_aero) - 37.404) * scaling)) * ((2.4825 * rtb_F_aero +
      0.4821) * scaling) / 0.259 * tc_lim;
    rtb_Subtract = (1.0 - (rtb_Gain - rtb_uDLookupTable) / (((rtb_F_dy_tmp *
      -0.0005 + 3.2826 * rtb_Subtract) - 37.404) * scaling)) * ((2.4825 *
      rtb_Subtract + 0.4821) * scaling) / 0.259 * tc_lim;

    /* Switch: '<S6>/Switch' incorporates:
     *  Constant: '<S6>/TC_Switch'
     */
    if (tc_switch > 0.0) {
      /* Saturate: '<S6>/Saturation3' */
      if (rtb_Subtract <= 0.0) {
        rtb_Subtract = 0.0;
      }

      /* End of Saturate: '<S6>/Saturation3' */

      /* Switch: '<S22>/Switch2' incorporates:
       *  RelationalOperator: '<S22>/LowerRelop1'
       */
      if (rtb_FzFR > rtb_Subtract) {
        rtb_FzFR = rtb_Subtract;
      } else {
        /* Gain: '<S6>/Gain3' */
        rtb_Subtract = -rtb_Subtract;

        /* Switch: '<S22>/Switch' incorporates:
         *  RelationalOperator: '<S22>/UpperRelop'
         */
        if (rtb_FzFR < rtb_Subtract) {
          rtb_FzFR = rtb_Subtract;
        }

        /* End of Switch: '<S22>/Switch' */
      }

      /* End of Switch: '<S22>/Switch2' */
    }

    /* End of Switch: '<S6>/Switch' */

    /* MATLAB Function: '<S4>/MATLAB Function1' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant5'
     *  Gain: '<Root>/Gain3'
     */
    MATLABFunction1(0.076335877862595422 * rtb_FzFR, 0.0, torq_derate_begin,
                    torq_derate_end, &rtb_Subtract);

    /* Switch: '<S9>/Switch2' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     *  RelationalOperator: '<S9>/LowerRelop1'
     *  RelationalOperator: '<S9>/UpperRelop'
     *  Switch: '<S9>/Switch'
     */
    if (rtb_Subtract > torq_limit_rl) {
      rtb_Subtract = torq_limit_rl;
    } else if (rtb_Subtract < -torq_limit_rl) {
      /* Switch: '<S9>/Switch' incorporates:
       *  Constant: '<S4>/Constant'
       */
      rtb_Subtract = -torq_limit_rl;
    }

    /* End of Switch: '<S9>/Switch2' */

    /* RateLimiter: '<S4>/Rate Limiter1' */
    if (rtDW->LastMajorTime == (rtInf)) {
      /* RateLimiter: '<S4>/Rate Limiter1' */
      rtDW->RateLimiter1 = rtb_Subtract;
    } else {
      rtb_Gain = rtM->Timing.t[0];
      rtb_FzFR = rtb_Gain - rtDW->LastMajorTime;
      if (rtDW->LastMajorTime == rtb_Gain) {
        if (rtDW->PrevLimited) {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY;
        } else {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtb_Subtract;
        }
      } else {
        rtb_uDLookupTable = rtb_FzFR * torq_slew;
        rtb_Gain = rtb_Subtract - rtDW->PrevY;
        if (rtb_Gain > rtb_uDLookupTable) {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY + rtb_uDLookupTable;
          limitedCache = true;
        } else {
          rtb_FzFR *= -torq_slew;
          if (rtb_Gain < rtb_FzFR) {
            /* RateLimiter: '<S4>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtDW->PrevY + rtb_FzFR;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S4>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtb_Subtract;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S4>/Rate Limiter1' */

    /* Sum: '<S6>/Sum1' incorporates:
     *  Constant: '<S6>/Constant'
     *  Gain: '<S6>/Gain1'
     *  Product: '<S6>/Product1'
     */
    rtb_F_dy += rtb_Gain4 * trq_lim * 13.1;

    /* Switch: '<S6>/Switch1' incorporates:
     *  Constant: '<S6>/TC_Switch'
     */
    if (tc_switch > 0.0) {
      /* Saturate: '<S6>/Saturation2' */
      if (rtb_F_aero <= 0.0) {
        rtb_Subtract = 0.0;
      } else {
        rtb_Subtract = rtb_F_aero;
      }

      /* End of Saturate: '<S6>/Saturation2' */

      /* Switch: '<S23>/Switch2' incorporates:
       *  RelationalOperator: '<S23>/LowerRelop1'
       */
      if (rtb_F_dy > rtb_Subtract) {
        rtb_F_dy = rtb_Subtract;
      } else {
        /* Gain: '<S6>/Gain4' */
        rtb_Subtract = -rtb_Subtract;

        /* Switch: '<S23>/Switch' incorporates:
         *  RelationalOperator: '<S23>/UpperRelop'
         */
        if (rtb_F_dy < rtb_Subtract) {
          rtb_F_dy = rtb_Subtract;
        }

        /* End of Switch: '<S23>/Switch' */
      }

      /* End of Switch: '<S23>/Switch2' */
    }

    /* End of Switch: '<S6>/Switch1' */

    /* MATLAB Function: '<S4>/MATLAB Function2' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant5'
     *  Gain: '<Root>/Gain4'
     */
    MATLABFunction1(0.076335877862595422 * rtb_F_dy, 0.0, torq_derate_begin,
                    torq_derate_end, &rtb_Subtract);

    /* Switch: '<S10>/Switch2' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Constant: '<S4>/Constant3'
     *  RelationalOperator: '<S10>/LowerRelop1'
     *  RelationalOperator: '<S10>/UpperRelop'
     *  Switch: '<S10>/Switch'
     */
    if (rtb_Subtract > torq_limit_rr) {
      rtb_F_dy = torq_limit_rr;
    } else if (rtb_Subtract < -torq_limit_rr) {
      /* Switch: '<S10>/Switch' incorporates:
       *  Constant: '<S4>/Constant3'
       */
      rtb_F_dy = -torq_limit_rr;
    } else {
      rtb_F_dy = rtb_Subtract;
    }

    /* End of Switch: '<S10>/Switch2' */

    /* RateLimiter: '<S4>/Rate Limiter' */
    if (rtDW->LastMajorTime_l == (rtInf)) {
      /* RateLimiter: '<S4>/Rate Limiter' */
      rtDW->RateLimiter = rtb_F_dy;
    } else {
      rtb_Gain = rtM->Timing.t[0];
      rtb_FzFR = rtb_Gain - rtDW->LastMajorTime_l;
      if (rtDW->LastMajorTime_l == rtb_Gain) {
        if (rtDW->PrevLimited_m) {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_o;
        } else {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtb_F_dy;
        }
      } else {
        rtb_uDLookupTable = rtb_FzFR * torq_slew;
        rtb_Gain = rtb_F_dy - rtDW->PrevY_o;
        if (rtb_Gain > rtb_uDLookupTable) {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_o + rtb_uDLookupTable;
          limitedCache = true;
        } else {
          rtb_FzFR *= -torq_slew;
          if (rtb_Gain < rtb_FzFR) {
            /* RateLimiter: '<S4>/Rate Limiter' */
            rtDW->RateLimiter = rtDW->PrevY_o + rtb_FzFR;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S4>/Rate Limiter' */
            rtDW->RateLimiter = rtb_F_dy;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited_m = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S4>/Rate Limiter' */

    /* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
     *  Constant: '<S5>/Constant4'
     *  Constant: '<S5>/Constant5'
     *  Gain: '<Root>/Gain'
     */
    MATLABFunction1(rtb_Gain4, 13.1 * rtU->wheel.speed.rl, torq_derate_begin,
                    torq_derate_end, &rtb_F_dy);

    /* MATLAB Function: '<S5>/MATLAB Function2' incorporates:
     *  Constant: '<S5>/Constant4'
     *  Constant: '<S5>/Constant5'
     *  Gain: '<Root>/Gain1'
     */
    MATLABFunction1(rtb_Gain4, 13.1 * rtU->wheel.speed.rr, torq_derate_begin,
                    torq_derate_end, &rtb_F_dy);

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

    /* Update for Memory: '<S27>/Memory' */
    rtDW->Memory_PreviousInput = rtDW->y_o;

    /* Update for UnitDelay: '<S15>/UD'
     *
     * Block description for '<S15>/UD':
     *
     *  Store in Global RAM
     */
    rtDW->UD_DSTATE = rtb_TSamp;

    /* Update for Memory: '<S29>/Memory' */
    rtDW->Memory_PreviousInput_l = rtDW->y_p;

    /* Update for Memory: '<S26>/Memory' */
    rtDW->Memory_PreviousInput_k = rtDW->y_k;

    /* Update for Memory: '<S28>/Memory' */
    rtDW->Memory_PreviousInput_i = rtDW->y_l;

    /* Update for UnitDelay: '<S16>/UD'
     *
     * Block description for '<S16>/UD':
     *
     *  Store in Global RAM
     */
    rtDW->UD_DSTATE_h = rtb_TSamp_d;

    /* Update for Memory: '<S32>/Memory' */
    rtDW->Memory_PreviousInput_h = rtDW->y;

    /* Update for Memory: '<S31>/Memory' */
    rtDW->Memory_PreviousInput_o = rtDW->y_e;

    /* Update for Memory: '<S30>/Memory' */
    rtDW->Memory_PreviousInput_p = rtDW->y_g;

    /* Update for RateLimiter: '<S4>/Rate Limiter1' incorporates:
     *  RateLimiter: '<S4>/Rate Limiter'
     */
    rtDW->PrevY = rtDW->RateLimiter1;
    LastMajorTime_tmp = rtM->Timing.t[0];
    rtDW->LastMajorTime = LastMajorTime_tmp;

    /* Update for RateLimiter: '<S4>/Rate Limiter' */
    rtDW->PrevY_o = rtDW->RateLimiter;
    rtDW->LastMajorTime_l = LastMajorTime_tmp;
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

  /* InitializeConditions for RateLimiter: '<S4>/Rate Limiter1' */
  rtDW->LastMajorTime = (rtInf);

  /* InitializeConditions for RateLimiter: '<S4>/Rate Limiter' */
  rtDW->LastMajorTime_l = (rtInf);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
