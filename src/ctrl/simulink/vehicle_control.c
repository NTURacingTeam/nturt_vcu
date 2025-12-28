/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 5.38
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Sun Dec 28 13:24:48 2025
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

static double look1_binlx(double u0, const double bp0[], const double table[],
  uint32_t maxIndex);
static double look2_binlc(double u0, double u1, const double bp0[], const double
  bp1[], const double table[], const uint32_t maxIndex[], uint32_t stride);
static void MATLABFunction1(double rtu_torqueReq, double rtu_speed, double
  rtu_begin, double rtu_max, double *rty_torqueCmd);
static double rtGetInf(void);
static float rtGetInfF(void);
static double rtGetMinusInf(void);
static float rtGetMinusInfF(void);
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

static double look2_binlc(double u0, double u1, const double bp0[], const double
  bp1[], const double table[], const uint32_t maxIndex[], uint32_t stride)
{
  double fractions[2];
  double frac;
  double yL_0d0;
  double yL_0d1;
  uint32_t bpIndices[2];
  uint32_t bpIdx;
  uint32_t iLeft;
  uint32_t iRght;

  /* Column-major Lookup 2-D
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
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
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
    iLeft = maxIndex[0U] - 1U;
    frac = 1.0;
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = 1.0;
  }

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_0d0 = table[bpIdx];
  yL_0d0 += (table[bpIdx + 1U] - yL_0d0) * fractions[0U];
  bpIdx += stride;
  yL_0d1 = table[bpIdx];
  return (((table[bpIdx + 1U] - yL_0d1) * fractions[0U] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
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

/* Model step function */
void vehicle_control_step(vehicle_control_RT_MODEL *const rtM,
  vehicle_control_ExtU *rtU, vehicle_control_ExtY *rtY)
{
  vehicle_control_DW *rtDW = rtM->dwork;

  {
    double rtb_F_aero;
    double rtb_F_dy;
    double rtb_FzFR;
    double rtb_Gain;
    double rtb_Gain4;
    double rtb_Subtract;
    double rtb_UnitConversion;
    double rtb_uDLookupTable;
    bool limitedCache;

    /* UnitConversion: '<S3>/Unit Conversion' */
    /* Unit Conversion - from: deg/s to: rad/s
       Expression: output = (0.0174533*input) + (0) */
    rtb_UnitConversion = 0.017453292519943295 * rtU->cockpit.steer;

    /* Gain: '<S20>/Gain4' incorporates:
     *  Lookup_n-D: '<S20>/SteerWheel to SteerAngle(L)'
     *  Lookup_n-D: '<S20>/SteerWheel to SteerAngle(R)'
     *  Sum: '<S20>/Add'
     *  UnitConversion: '<S3>/Unit Conversion'
     */
    rtb_Gain4 = (look1_binlx(rtb_UnitConversion, rtConstP.pooled5,
      rtConstP.SteerWheeltoSteerAngleL_tableDa, 100U) + look1_binlx
                 (rtb_UnitConversion, rtConstP.pooled5,
                  rtConstP.SteerWheeltoSteerAngleR_tableDa, 100U)) * 0.5;

    /* MATLAB Function: '<S19>/MATLAB Function3' */
    rtb_F_aero = rtU->vehicle_state.velocity.x * rtU->vehicle_state.velocity.x *
      0.6125 * 3.23;

    /* Gain: '<S19>/Gain' incorporates:
     *  MATLAB Function: '<S19>/MATLAB Function2'
     */
    rtb_Gain = 0.18749999999999997 * rtU->imu.accel.x * 307.0 * 0.5;

    /* MATLAB Function: '<S19>/MATLAB Function1' */
    rtb_F_dy = 0.24193548387096772 * rtU->imu.accel.y * 307.0;

    /* Lookup_n-D: '<S19>/1-D Lookup Table' */
    rtb_uDLookupTable = look1_binlx(rtb_F_dy, rtConstP.uDLookupTable_bp01Data,
      rtConstP.uDLookupTable_tableData, 2U);

    /* Sum: '<S19>/Subtract' */
    rtb_Subtract = rtb_F_dy - rtb_uDLookupTable;

    /* MATLAB Function: '<S19>/MATLAB Function4' */
    rtb_FzFR = rtb_F_aero * 0.48 / 2.0;
    rtb_F_dy = ((631.806 - rtb_Gain) - rtb_Subtract) + rtb_FzFR;
    rtb_FzFR += (631.806 - rtb_Gain) + rtb_Subtract;
    rtb_F_aero = rtb_F_aero * 0.52 / 2.0;
    rtb_Subtract = ((rtb_Gain + 872.494) - rtb_uDLookupTable) + rtb_F_aero;
    rtb_F_aero += (rtb_Gain + 872.494) + rtb_uDLookupTable;

    /* MATLAB Function: '<S6>/MATLAB Function' */
    rtb_Gain = (((rtb_F_dy * rtb_F_dy * -0.0215 + 68.166 * rtb_F_dy) - 216.33) *
                2.0 + ((rtb_FzFR * rtb_FzFR * -0.0215 + 68.166 * rtb_FzFR) -
                       216.33) * 2.0) / 2.0;
    rtb_F_aero = (((rtb_Subtract * rtb_Subtract * -0.0215 + 68.166 *
                    rtb_Subtract) - 216.33) * 2.0 + ((rtb_F_aero * rtb_F_aero *
      -0.0215 + 68.166 * rtb_F_aero) - 216.33) * 2.0) / 2.0;

    /* MATLAB Function: '<S6>/MATLAB Function2' */
    if (rtU->vehicle_state.velocity.x > 2.5) {
      /* Product: '<S18>/Product' incorporates:
       *  Abs: '<S6>/Abs2'
       *  Constant: '<S18>/track'
       *  Constant: '<S18>/wheel radius'
       *  Gain: '<S6>/FB_Gain'
       *  Gain: '<S6>/FF_Gain'
       *  Lookup_n-D: '<S6>/2-D Lookup Table'
       *  MATLAB Function: '<S21>/reference yaw rate 1'
       *  MATLAB Function: '<S6>/MATLAB Function'
       *  MATLAB Function: '<S6>/MATLAB Function1'
       *  Product: '<S18>/Divide'
       *  Sum: '<S6>/Sum2'
       *  Switch: '<S6>/Switch'
       */
      rtb_Gain4 = (-(0.672 * rtb_F_aero - 0.92799999999999994 * rtb_Gain) /
                   (rtb_Gain + rtb_F_aero) * 300.0 *
                   (rtU->vehicle_state.velocity.x *
                    rtU->vehicle_state.velocity.x) / 1.6 * rtb_Gain4 * ff_gain +
                   (rtU->vehicle_state.velocity.x * rtb_Gain4 /
                    (rtU->vehicle_state.velocity.x *
                     rtU->vehicle_state.velocity.x * -0.00029411764705882274 +
                     1.6) - rtU->imu.gyro.z) / look2_binlc(fabs
        (rtb_UnitConversion), rtU->vehicle_state.velocity.x, rtConstP.pooled2,
        rtConstP.pooled3, rtConstP.pooled1, rtConstP.pooled11, 4U) * fb_gain) /
        1.24 * 0.259;

      /* Saturate: '<S6>/Saturation' */
      if (rtb_Gain4 > 200.0) {
        rtb_Gain4 = 200.0;
      } else if (rtb_Gain4 < -200.0) {
        rtb_Gain4 = -200.0;
      }

      /* End of Saturate: '<S6>/Saturation' */
    } else {
      rtb_Gain4 = 0.0;
    }

    /* End of MATLAB Function: '<S6>/MATLAB Function2' */

    /* Gain: '<Root>/Gain2' */
    rtb_UnitConversion = 0.01 * rtU->cockpit.accel;

    /* Gain: '<S6>/Gain' incorporates:
     *  Constant: '<S6>/Constant'
     *  Gain: '<S6>/Gain1'
     *  Product: '<S6>/Product'
     */
    rtb_Subtract = 20.0 * rtb_UnitConversion * 13.1;

    /* MATLAB Function: '<S4>/MATLAB Function1' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant5'
     *  Gain: '<Root>/Gain3'
     *  Gain: '<S6>/Gain'
     *  Sum: '<S6>/Sum'
     */
    MATLABFunction1(0.076335877862595422 * (rtb_Subtract - rtb_Gain4), 0.0,
                    torq_derate_begin, torq_derate_end, &rtb_F_aero);

    /* Switch: '<S9>/Switch2' incorporates:
     *  Constant: '<S4>/Constant'
     *  Constant: '<S4>/Constant1'
     *  RelationalOperator: '<S9>/LowerRelop1'
     *  RelationalOperator: '<S9>/UpperRelop'
     *  Switch: '<S9>/Switch'
     */
    if (rtb_F_aero > torq_limit_rl) {
      rtb_F_aero = torq_limit_rl;
    } else if (rtb_F_aero < -torq_limit_rl) {
      /* Switch: '<S9>/Switch' incorporates:
       *  Constant: '<S4>/Constant'
       */
      rtb_F_aero = -torq_limit_rl;
    }

    /* End of Switch: '<S9>/Switch2' */

    /* RateLimiter: '<S4>/Rate Limiter1' */
    if (rtDW->LastMajorTime == (rtInf)) {
      /* RateLimiter: '<S4>/Rate Limiter1' */
      rtDW->RateLimiter1 = rtb_F_aero;
    } else {
      rtb_uDLookupTable = rtM->Timing.t[0];
      rtb_Gain = rtb_uDLookupTable - rtDW->LastMajorTime;
      if (rtDW->LastMajorTime == rtb_uDLookupTable) {
        if (rtDW->PrevLimited) {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY;
        } else {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtb_F_aero;
        }
      } else {
        rtb_F_dy = rtb_Gain * torq_slew;
        rtb_uDLookupTable = rtb_F_aero - rtDW->PrevY;
        if (rtb_uDLookupTable > rtb_F_dy) {
          /* RateLimiter: '<S4>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY + rtb_F_dy;
          limitedCache = true;
        } else {
          rtb_Gain *= -torq_slew;
          if (rtb_uDLookupTable < rtb_Gain) {
            /* RateLimiter: '<S4>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtDW->PrevY + rtb_Gain;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S4>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtb_F_aero;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S4>/Rate Limiter1' */

    /* MATLAB Function: '<S4>/MATLAB Function2' incorporates:
     *  Constant: '<S4>/Constant4'
     *  Constant: '<S4>/Constant5'
     *  Gain: '<Root>/Gain4'
     *  Sum: '<S6>/Sum1'
     */
    MATLABFunction1(0.076335877862595422 * (rtb_Gain4 + rtb_Subtract), 0.0,
                    torq_derate_begin, torq_derate_end, &rtb_F_aero);

    /* Switch: '<S10>/Switch2' incorporates:
     *  Constant: '<S4>/Constant2'
     *  Constant: '<S4>/Constant3'
     *  RelationalOperator: '<S10>/LowerRelop1'
     *  RelationalOperator: '<S10>/UpperRelop'
     *  Switch: '<S10>/Switch'
     */
    if (rtb_F_aero > torq_limit_rr) {
      rtb_Gain4 = torq_limit_rr;
    } else if (rtb_F_aero < -torq_limit_rr) {
      /* Switch: '<S10>/Switch' incorporates:
       *  Constant: '<S4>/Constant3'
       */
      rtb_Gain4 = -torq_limit_rr;
    } else {
      rtb_Gain4 = rtb_F_aero;
    }

    /* End of Switch: '<S10>/Switch2' */

    /* RateLimiter: '<S4>/Rate Limiter' */
    if (rtDW->LastMajorTime_l == (rtInf)) {
      /* RateLimiter: '<S4>/Rate Limiter' */
      rtDW->RateLimiter = rtb_Gain4;
    } else {
      rtb_uDLookupTable = rtM->Timing.t[0];
      rtb_Gain = rtb_uDLookupTable - rtDW->LastMajorTime_l;
      if (rtDW->LastMajorTime_l == rtb_uDLookupTable) {
        if (rtDW->PrevLimited_m) {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_o;
        } else {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtb_Gain4;
        }
      } else {
        rtb_F_dy = rtb_Gain * torq_slew;
        rtb_uDLookupTable = rtb_Gain4 - rtDW->PrevY_o;
        if (rtb_uDLookupTable > rtb_F_dy) {
          /* RateLimiter: '<S4>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_o + rtb_F_dy;
          limitedCache = true;
        } else {
          rtb_Gain *= -torq_slew;
          if (rtb_uDLookupTable < rtb_Gain) {
            /* RateLimiter: '<S4>/Rate Limiter' */
            rtDW->RateLimiter = rtDW->PrevY_o + rtb_Gain;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S4>/Rate Limiter' */
            rtDW->RateLimiter = rtb_Gain4;
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
    MATLABFunction1(rtb_UnitConversion, 13.1 * rtU->wheel.speed.rl,
                    torq_derate_begin, torq_derate_end, &rtb_Gain4);

    /* MATLAB Function: '<S5>/MATLAB Function2' incorporates:
     *  Constant: '<S5>/Constant4'
     *  Constant: '<S5>/Constant5'
     *  Gain: '<Root>/Gain1'
     */
    MATLABFunction1(rtb_UnitConversion, 13.1 * rtU->wheel.speed.rr,
                    torq_derate_begin, torq_derate_end, &rtb_Gain4);

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
