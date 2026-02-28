/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 3.16
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Tue Feb 10 22:00:07 2026
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
static void MATLABFunction1(double rtu_torqueReq, double rtu_speed, double
  rtu_begin, double rtu_max, double *rty_torqueCmd);
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
  double rtb_TSamp_n;

  {
    double C_alhpa_r;
    double Diff;
    double rtb_F_aero;
    double rtb_F_dy;
    double rtb_F_dy_tmp;
    double rtb_FzRL;
    double rtb_Gain;
    double rtb_Subtract;
    double rtb_Switch2_ea;
    double rtb_uDLookupTable;
    double rtb_uDLookupTable_tmp;
    double rtb_uDLookupTable_tmp_0;
    double rtb_uDLookupTable_tmp_tmp;
    bool limitedCache;

    /* UnitConversion: '<S3>/Unit Conversion' */
    /* Unit Conversion - from: deg/s to: rad/s
       Expression: output = (0.0174533*input) + (0) */
    rtb_Switch2_ea = 0.017453292519943295 * rtU->cockpit.steer;

    /* Gain: '<S22>/Gain4' incorporates:
     *  Lookup_n-D: '<S22>/SteerWheel to SteerAngle(L)'
     *  Lookup_n-D: '<S22>/SteerWheel to SteerAngle(R)'
     *  Sum: '<S22>/Add'
     *  Switch: '<S5>/Switch2'
     */
    rtb_Switch2_ea = (look1_binlx(rtb_Switch2_ea, rtConstP.pooled4,
      rtConstP.SteerWheeltoSteerAngleL_tableDa, 100U) + look1_binlx
                      (rtb_Switch2_ea, rtConstP.pooled4,
                       rtConstP.SteerWheeltoSteerAngleR_tableDa, 100U)) * 0.5;

    /* SampleTimeMath: '<S11>/TSamp'
     *
     * About '<S11>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    rtb_TSamp = rtU->imu.gyro.z * 100.0;

    /* Sum: '<S11>/Diff' incorporates:
     *  UnitDelay: '<S11>/UD'
     *
     * Block description for '<S11>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S11>/UD':
     *
     *  Store in Global RAM
     */
    Diff = rtb_TSamp - rtDW->UD_DSTATE;

    /* MATLAB Function: '<S20>/MATLAB Function3' */
    rtb_F_aero = rtU->vehicle_state.velocity.x * rtU->vehicle_state.velocity.x *
      0.6125 * 2.2;

    /* Gain: '<S20>/Gain' incorporates:
     *  MATLAB Function: '<S20>/MATLAB Function2'
     */
    rtb_Gain = 0.18749999999999997 * rtU->imu.accel.x * 307.0 * 0.5;

    /* MATLAB Function: '<S20>/MATLAB Function1' */
    rtb_F_dy = 0.24193548387096772 * rtU->imu.accel.y * 307.0;

    /* Lookup_n-D: '<S20>/1-D Lookup Table' */
    rtb_uDLookupTable = look1_binlx(rtb_F_dy, rtConstP.uDLookupTable_bp01Data,
      rtConstP.uDLookupTable_tableData, 2U);

    /* Sum: '<S20>/Subtract' */
    rtb_Subtract = rtb_F_dy - rtb_uDLookupTable;

    /* MATLAB Function: '<S20>/MATLAB Function4' */
    rtb_F_dy_tmp = rtb_F_aero * 0.48 / 2.0;
    rtb_F_dy = ((658.56000000000006 - rtb_Gain) - rtb_Subtract) + rtb_F_dy_tmp;
    rtb_Subtract = ((658.56000000000006 - rtb_Gain) + rtb_Subtract) +
      rtb_F_dy_tmp;
    rtb_F_dy_tmp = rtb_F_aero * 0.52 / 2.0;
    rtb_FzRL = ((rtb_Gain + 909.43999999999994) - rtb_uDLookupTable) +
      rtb_F_dy_tmp;
    rtb_F_aero = ((rtb_Gain + 909.43999999999994) + rtb_uDLookupTable) +
      rtb_F_dy_tmp;

    /* MATLAB Function: '<S5>/Torque_Max' incorporates:
     *  Constant: '<S5>/TC_limit'
     *  Constant: '<S5>/scaling'
     *  MATLAB Function: '<S5>/MATLAB Function'
     *  MATLAB Function: '<S5>/MATLAB Function3'
     */
    rtb_F_dy_tmp = cos(rtb_Switch2_ea);
    rtb_Gain = 0.92799999999999994 * rtb_F_dy_tmp;
    rtb_Gain = fabs((rtb_Gain * 320.0 * rtU->imu.accel.y - 51.0 * Diff) /
                    (rtb_Gain + 0.672));
    rtb_uDLookupTable_tmp_tmp = rtb_F_aero * rtb_F_aero;
    rtb_uDLookupTable_tmp = (rtb_uDLookupTable_tmp_tmp * -0.00059 + 1.46113 *
      rtb_F_aero) + 17.01657;
    C_alhpa_r = rtb_FzRL * rtb_FzRL;
    rtb_uDLookupTable_tmp_0 = (C_alhpa_r * -0.00059 + 1.46113 * rtb_FzRL) +
      17.01657;
    rtb_uDLookupTable = rtb_uDLookupTable_tmp * scaling * rtb_Gain /
      (rtb_uDLookupTable_tmp_0 * scaling + rtb_uDLookupTable_tmp * scaling);
    rtb_F_aero = (1.0 - rtb_uDLookupTable / (((rtb_uDLookupTable_tmp_tmp *
      -0.0005 + 3.2826 * rtb_F_aero) - 37.404) * scaling)) * ((2.4825 *
      rtb_F_aero + 0.4821) * scaling) / 0.254 * tc_lim;
    rtb_uDLookupTable = (1.0 - (rtb_Gain - rtb_uDLookupTable) / (((C_alhpa_r *
      -0.0005 + 3.2826 * rtb_FzRL) - 37.404) * scaling)) * ((2.4825 * rtb_FzRL +
      0.4821) * scaling) / 0.254 * tc_lim;

    /* Gain: '<Root>/Gain2' */
    rtb_Gain = 0.01 * rtU->cockpit.accel;

    /* MATLAB Function: '<S23>/reference yaw rate 1' */
    rtb_FzRL = rtU->vehicle_state.velocity.x * rtb_Switch2_ea / 1.6;

    /* SampleTimeMath: '<S10>/TSamp'
     *
     * About '<S10>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *   */
    rtb_TSamp_n = rtb_FzRL * 100.0;

    /* MATLAB Function: '<S5>/MATLAB Function' incorporates:
     *  Constant: '<S5>/FR_ratio'
     *  Constant: '<S5>/scaling'
     *  MATLAB Function: '<S5>/MATLAB Function3'
     */
    rtb_F_dy = (rtb_F_dy * rtb_F_dy * -0.00059 + 1.46113 * rtb_F_dy) + 17.01657;
    rtb_uDLookupTable_tmp_tmp = (rtb_Subtract * rtb_Subtract * -0.00059 +
      1.46113 * rtb_Subtract) + 17.01657;
    rtb_Subtract = (rtb_F_dy * scaling + rtb_uDLookupTable_tmp_tmp * scaling) *
      fr_ratio;
    C_alhpa_r = rtb_uDLookupTable_tmp_0 * scaling + rtb_uDLookupTable_tmp *
      scaling;

    /* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
     *  Constant: '<S5>/FR_ratio'
     *  Constant: '<S5>/scaling'
     *  MATLAB Function: '<S5>/MATLAB Function3'
     */
    rtb_F_dy = (rtb_FzRL - rtU->imu.gyro.z) / fabs((1.0 / ((rtb_F_dy * scaling +
      rtb_uDLookupTable_tmp_tmp * scaling) * fr_ratio) + 1.0 /
      (rtb_uDLookupTable_tmp_0 * scaling + rtb_uDLookupTable_tmp * scaling)) *
      (rtb_Switch2_ea * rt_powd_snf(rtU->vehicle_state.velocity.x, 3.0) *
       rtU->imu.accel.y) / 4.096000000000001);

    /* Gain: '<S5>/Gain2' incorporates:
     *  Sum: '<S10>/Diff'
     *  Sum: '<S5>/Subtract3'
     *  UnitDelay: '<S10>/UD'
     *
     * Block description for '<S10>/Diff':
     *
     *  Add in CPU
     *
     * Block description for '<S10>/UD':
     *
     *  Store in Global RAM
     */
    Diff = ((rtb_TSamp_n - rtDW->UD_DSTATE_l) - Diff) * 51.0;

    /* Saturate: '<S5>/Saturation1' */
    if (Diff > 300.0) {
      Diff = 300.0;
    } else if (Diff < -300.0) {
      Diff = -300.0;
    }

    /* MATLAB Function: '<S5>/MATLAB Function4' */
    if (!(rtU->vehicle_state.velocity.x > 5.0)) {
      if ((rtU->vehicle_state.velocity.x <= 5.0) &&
          (rtU->vehicle_state.velocity.x > 2.0)) {
        rtb_F_dy = (rtU->vehicle_state.velocity.x - 2.0) * rtb_F_dy / 3.0;
      } else {
        rtb_F_dy = 0.0;
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
    rtb_Switch2_ea = (((0.672 * C_alhpa_r - 0.92799999999999994 * rtb_Subtract *
                        rtb_F_dy_tmp) / (rtb_Subtract + C_alhpa_r) * 320.0 *
                       (rtU->vehicle_state.velocity.x *
                        rtU->vehicle_state.velocity.x) / 1.6 * rtb_Switch2_ea *
                       ff_gain + ff_dyna_gain * Diff) + fb_gain * rtb_F_dy) /
      1.24 * 0.254;

    /* Saturate: '<S5>/Saturation' */
    if (rtb_Switch2_ea > 210.0) {
      rtb_Switch2_ea = 210.0;
    } else if (rtb_Switch2_ea < -210.0) {
      rtb_Switch2_ea = -210.0;
    }

    /* End of Saturate: '<S5>/Saturation' */

    /* Switch: '<S5>/Switch2' incorporates:
     *  Constant: '<S5>/Constant1'
     *  MATLAB Function: '<S5>/MATLAB Function2'
     */
    if (rtU->cockpit.brake > 0.1) {
      rtb_Switch2_ea = 0.0;
    } else if (!(rtU->vehicle_state.velocity.x > 4.0)) {
      /* MATLAB Function: '<S5>/MATLAB Function2' */
      if ((rtU->vehicle_state.velocity.x <= 4.0) &&
          (rtU->vehicle_state.velocity.x > 2.0)) {
        rtb_Switch2_ea = (rtU->vehicle_state.velocity.x - 2.0) * rtb_Switch2_ea /
          2.0;
      } else {
        rtb_Switch2_ea = 0.0;
      }
    }

    /* End of Switch: '<S5>/Switch2' */

    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S5>/Constant'
     *  Gain: '<S5>/Gain'
     *  Product: '<S5>/Product'
     */
    Diff = trq_lim * rtb_Gain * 13.1 - rtb_Switch2_ea;

    /* Switch: '<S5>/Switch' incorporates:
     *  Constant: '<S5>/TC_Switch'
     */
    if (tc_switch > 0.0) {
      /* Saturate: '<S5>/Saturation3' */
      if (rtb_uDLookupTable <= 0.0) {
        rtb_F_dy = 0.0;
      } else {
        rtb_F_dy = rtb_uDLookupTable;
      }

      /* End of Saturate: '<S5>/Saturation3' */

      /* Switch: '<S17>/Switch2' incorporates:
       *  RelationalOperator: '<S17>/LowerRelop1'
       */
      if (Diff > rtb_F_dy) {
        Diff = rtb_F_dy;
      } else {
        /* Gain: '<S5>/Gain3' */
        rtb_F_dy = -rtb_F_dy;

        /* Switch: '<S17>/Switch' incorporates:
         *  RelationalOperator: '<S17>/UpperRelop'
         */
        if (Diff < rtb_F_dy) {
          Diff = rtb_F_dy;
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
    MATLABFunction1(0.076335877862595422 * Diff, 0.0, torq_derate_begin,
                    torq_derate_end, &rtb_F_dy);

    /* Switch: '<S8>/Switch2' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     *  RelationalOperator: '<S8>/LowerRelop1'
     *  RelationalOperator: '<S8>/UpperRelop'
     *  Switch: '<S8>/Switch'
     */
    if (rtb_F_dy > torq_limit_rl) {
      Diff = torq_limit_rl;
    } else if (rtb_F_dy < -torq_limit_rl) {
      /* Switch: '<S8>/Switch' incorporates:
       *  Constant: '<S4>/Constant'
       */
      Diff = -torq_limit_rl;
    } else {
      Diff = rtb_F_dy;
    }

    /* End of Switch: '<S8>/Switch2' */

    /* RateLimiter: '<S4>/Rate Limiter1' */
    if (rtDW->LastMajorTime == (rtInf)) {
      /* RateLimiter: '<S4>/Rate Limiter1' */
      rtDW->RateLimiter1 = Diff;
    } else {
      rtb_Subtract = rtM->Timing.t[0];
      rtb_F_dy = rtb_Subtract - rtDW->LastMajorTime;
      if (rtDW->LastMajorTime == rtb_Subtract) {
        if (rtDW->PrevLimited) {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY;
        } else {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = Diff;
        }
      } else {
        rtb_FzRL = rtb_F_dy * torq_slew;
        rtb_Subtract = Diff - rtDW->PrevY;
        if (rtb_Subtract > rtb_FzRL) {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY + rtb_FzRL;
          limitedCache = true;
        } else {
          rtb_F_dy *= -torq_slew;
          if (rtb_Subtract < rtb_F_dy) {
            /* RateLimiter: '<S4>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtDW->PrevY + rtb_F_dy;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S4>/Rate Limiter1' */
            rtDW->RateLimiter1 = Diff;
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
    Diff = rtb_Gain * trq_lim * 13.1 + rtb_Switch2_ea;

    /* Switch: '<S5>/Switch1' incorporates:
     *  Constant: '<S5>/TC_Switch'
     */
    if (tc_switch > 0.0) {
      /* Saturate: '<S5>/Saturation2' */
      if (rtb_F_aero <= 0.0) {
        rtb_F_aero = 0.0;
      }

      /* End of Saturate: '<S5>/Saturation2' */

      /* Switch: '<S18>/Switch2' incorporates:
       *  RelationalOperator: '<S18>/LowerRelop1'
       */
      if (Diff > rtb_F_aero) {
        Diff = rtb_F_aero;
      } else {
        /* Gain: '<S5>/Gain4' */
        rtb_F_aero = -rtb_F_aero;

        /* Switch: '<S18>/Switch' incorporates:
         *  RelationalOperator: '<S18>/UpperRelop'
         */
        if (Diff < rtb_F_aero) {
          Diff = rtb_F_aero;
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
    MATLABFunction1(0.076335877862595422 * Diff, 0.0, torq_derate_begin,
                    torq_derate_end, &Diff);

    /* Switch: '<S9>/Switch2' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Constant: '<S4>/Constant3'
     *  RelationalOperator: '<S9>/LowerRelop1'
     *  RelationalOperator: '<S9>/UpperRelop'
     *  Switch: '<S9>/Switch'
     */
    if (Diff > torq_limit_rr) {
      rtb_F_aero = torq_limit_rr;
    } else if (Diff < -torq_limit_rr) {
      /* Switch: '<S9>/Switch' incorporates:
       *  Constant: '<S4>/Constant3'
       */
      rtb_F_aero = -torq_limit_rr;
    } else {
      rtb_F_aero = Diff;
    }

    /* End of Switch: '<S9>/Switch2' */

    /* RateLimiter: '<S4>/Rate Limiter' */
    if (rtDW->LastMajorTime_b == (rtInf)) {
      /* RateLimiter: '<S4>/Rate Limiter' */
      rtDW->RateLimiter = rtb_F_aero;
    } else {
      rtb_Subtract = rtM->Timing.t[0];
      rtb_F_dy = rtb_Subtract - rtDW->LastMajorTime_b;
      if (rtDW->LastMajorTime_b == rtb_Subtract) {
        if (rtDW->PrevLimited_p) {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_a;
        } else {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtb_F_aero;
        }
      } else {
        rtb_FzRL = rtb_F_dy * torq_slew;
        rtb_Subtract = rtb_F_aero - rtDW->PrevY_a;
        if (rtb_Subtract > rtb_FzRL) {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_a + rtb_FzRL;
          limitedCache = true;
        } else {
          rtb_F_dy *= -torq_slew;
          if (rtb_Subtract < rtb_F_dy) {
            /* RateLimiter: '<S4>/Rate Limiter' */
            rtDW->RateLimiter = rtDW->PrevY_a + rtb_F_dy;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S4>/Rate Limiter' */
            rtDW->RateLimiter = rtb_F_aero;
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

    /* Update for UnitDelay: '<S11>/UD'
     *
     * Block description for '<S11>/UD':
     *
     *  Store in Global RAM
     */
    rtDW->UD_DSTATE = rtb_TSamp;

    /* Update for UnitDelay: '<S10>/UD'
     *
     * Block description for '<S10>/UD':
     *
     *  Store in Global RAM
     */
    rtDW->UD_DSTATE_l = rtb_TSamp_n;

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
