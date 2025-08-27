/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 5.27
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Wed Aug 27 15:21:52 2025
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
static void MATLABFunction5(double rtu_last_1, double rtu_last_2, double
  rtu_last_3, double rtu_last_4, double rtu_u, double *rty_y);
static void MATLABFunction5_o(double rtu_last_1, double rtu_last_2, double
  rtu_last_3, double rtu_u, double *rty_y);
static void MATLABFunction(double rtu_brake, double rtu_trq_last, double
  rtu_tc_on_last, double rtu_trq_real, double rtu_delta_SR, double rtu_d_SR,
  double rtu_alpha, double *rty_trq_tc, double *rty_tc_on);
static void MATLABFunction1_l(double rtu_trq_tc, double rtu_trq_max, double
  *rty_trq_wl_tc);

/* private model entry point functions */
extern void vehicle_control_derivatives(vehicle_control_RT_MODEL *const rtM);
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
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  vehicle_control_RT_MODEL *const rtM, vehicle_control_ExtU *rtU,
  vehicle_control_ExtY *rtY)
{
  /* Solver Matrices */
  static const double rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const double rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  double t = rtsiGetT(si);
  double tnew = rtsiGetSolverStopTime(si);
  double h = rtsiGetStepSize(si);
  double *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  double *y = id->y;
  double *f0 = id->f[0];
  double *f1 = id->f[1];
  double *f2 = id->f[2];
  double hB[3];
  int i;
  int nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (unsigned int)nXc*sizeof(double));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  vehicle_control_derivatives(rtM);

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  vehicle_control_step(rtM, rtU, rtY);
  vehicle_control_derivatives(rtM);

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  vehicle_control_step(rtM, rtU, rtY);
  vehicle_control_derivatives(rtM);

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * Output and update for atomic system:
 *    '<S3>/MATLAB Function1'
 *    '<S3>/MATLAB Function2'
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
 *    '<S15>/MATLAB Function5'
 *    '<S16>/MATLAB Function5'
 *    '<S17>/MATLAB Function5'
 *    '<S18>/MATLAB Function5'
 */
static void MATLABFunction5(double rtu_last_1, double rtu_last_2, double
  rtu_last_3, double rtu_last_4, double rtu_u, double *rty_y)
{
  *rty_y = ((((rtu_u + rtu_last_1) + rtu_last_2) + rtu_last_3) + rtu_last_4) /
    5.0;
}

/*
 * Output and update for atomic system:
 *    '<S19>/MATLAB Function5'
 *    '<S20>/MATLAB Function5'
 */
static void MATLABFunction5_o(double rtu_last_1, double rtu_last_2, double
  rtu_last_3, double rtu_u, double *rty_y)
{
  *rty_y = (((rtu_u + rtu_last_1) + rtu_last_2) + rtu_last_3) / 4.0;
}

/*
 * Output and update for atomic system:
 *    '<S21>/MATLAB Function'
 *    '<S22>/MATLAB Function'
 */
static void MATLABFunction(double rtu_brake, double rtu_trq_last, double
  rtu_tc_on_last, double rtu_trq_real, double rtu_delta_SR, double rtu_d_SR,
  double rtu_alpha, double *rty_trq_tc, double *rty_tc_on)
{
  if (rtu_brake == 0.0) {
    if (rtu_tc_on_last == 1.0) {
      if ((rtu_delta_SR < 0.0) || (rtu_d_SR > 0.5)) {
        if (rtu_trq_last < rtu_trq_real) {
          *rty_trq_tc = rtu_trq_last - 10.0;
        } else {
          *rty_trq_tc = rtu_trq_real;
        }

        *rty_tc_on = 1.0;
      } else if (rtu_alpha > 0.2) {
        if (rtu_trq_last < rtu_trq_real) {
          *rty_trq_tc = rtu_trq_last - 30.0;
        } else {
          *rty_trq_tc = rtu_trq_real;
        }

        *rty_tc_on = 1.0;
      } else {
        if (rtu_trq_real > rtu_trq_last + 20.0) {
          *rty_trq_tc = rtu_trq_last + 20.0;
        } else {
          *rty_trq_tc = rtu_trq_real;
        }

        *rty_tc_on = 0.0;
      }
    } else if ((rtu_delta_SR < 0.0) || (rtu_d_SR > 0.5) || (rtu_alpha > 0.2)) {
      *rty_trq_tc = rtu_trq_real;
      *rty_tc_on = 1.0;
    } else {
      if (rtu_trq_real > rtu_trq_last + 20.0) {
        *rty_trq_tc = rtu_trq_last + 20.0;
      } else {
        *rty_trq_tc = rtu_trq_real;
      }

      *rty_tc_on = 0.0;
    }
  } else {
    *rty_trq_tc = rtu_trq_real;
    *rty_tc_on = 0.0;
  }
}

/*
 * Output and update for atomic system:
 *    '<S21>/MATLAB Function1'
 *    '<S22>/MATLAB Function1'
 */
static void MATLABFunction1_l(double rtu_trq_tc, double rtu_trq_max, double
  *rty_trq_wl_tc)
{
  if (rtu_trq_tc > rtu_trq_max) {
    *rty_trq_wl_tc = rtu_trq_max;
  } else if (rtu_trq_tc < -rtu_trq_max) {
    *rty_trq_wl_tc = -rtu_trq_max;
  } else {
    *rty_trq_wl_tc = rtu_trq_tc;
  }
}

/* Model step function */
void vehicle_control_step(vehicle_control_RT_MODEL *const rtM,
  vehicle_control_ExtU *rtU, vehicle_control_ExtY *rtY)
{
  vehicle_control_DW *rtDW = rtM->dwork;
  vehicle_control_X *rtX = rtM->contStates;

  /* local block i/o variables */
  double rtb_Memory2;
  double rtb_Memory1;
  double rtb_Memory;
  double rtb_Memory2_l;
  double rtb_Memory1_a;
  double rtb_Memory_j;
  double rtb_Memory2_i;
  double rtb_Memory1_m;
  double rtb_Memory2_n;
  double rtb_Memory1_l;
  double rtb_Memory_o;
  double rtb_Memory2_m;
  double rtb_Memory1_n;
  double rtb_Memory_f;
  double rtb_Memory2_f;
  double rtb_Memory1_h;
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  {
    double rtb_F_aero;
    double rtb_F_dy;
    double rtb_FzFR;
    double rtb_Gain;
    double rtb_Gain4;
    double rtb_Gain_k;
    double rtb_Sign_p;
    double rtb_Subtract;
    double rtb_TransferFcn;
    double rtb_torqueCmd_d;
    double rtb_uDLookupTable;
    double *lastU;
    bool limitedCache;
    bool tmp;

    /* Gain: '<Root>/Gain' */
    rtb_Gain = 13.1 * rtU->wheel.speed.rl;

    /* TransferFcn: '<S4>/Transfer Fcn' */
    rtb_TransferFcn = 66.666666666666671 * rtX->TransferFcn_CSTATE;

    /* UnitConversion: '<S9>/Unit Conversion' incorporates:
     *  SignalConversion generated from: '<Root>/Bus Selector'
     */
    /* Unit Conversion - from: deg to: rad
       Expression: output = (0.0174533*input) + (0) */
    rtb_torqueCmd_d = 0.017453292519943295 * rtU->cockpit.steer;

    /* Gain: '<S23>/Gain4' incorporates:
     *  Lookup_n-D: '<S23>/SteerWheel to SteerAngle(L)'
     *  Lookup_n-D: '<S23>/SteerWheel to SteerAngle(R)'
     *  Sum: '<S23>/Add'
     */
    rtb_Gain4 = (look1_binlx(rtb_torqueCmd_d, rtConstP.pooled7,
      rtConstP.SteerWheeltoSteerAngleL_tableDa, 100U) + look1_binlx
                 (rtb_torqueCmd_d, rtConstP.pooled7,
                  rtConstP.SteerWheeltoSteerAngleR_tableDa, 100U)) * 0.5;

    /* MATLAB Function: '<S14>/MATLAB Function3' */
    rtb_F_aero = rtU->vehicle_state.velocity.x * rtU->vehicle_state.velocity.x *
      0.6125 * 3.23;

    /* Gain: '<S14>/Gain' incorporates:
     *  MATLAB Function: '<S14>/MATLAB Function2'
     */
    rtb_Gain_k = 0.18749999999999997 * rtU->imu.accel.x * 307.0 * 0.5;

    /* MATLAB Function: '<S14>/MATLAB Function1' */
    rtb_F_dy = 0.24193548387096772 * rtU->imu.accel.y * 307.0;

    /* Lookup_n-D: '<S14>/1-D Lookup Table' */
    rtb_uDLookupTable = look1_binlx(rtb_F_dy, rtConstP.uDLookupTable_bp01Data,
      rtConstP.uDLookupTable_tableData, 2U);

    /* Sum: '<S14>/Subtract' */
    rtb_Subtract = rtb_F_dy - rtb_uDLookupTable;

    /* MATLAB Function: '<S14>/MATLAB Function4' */
    rtb_FzFR = rtb_F_aero * 0.48 / 2.0;
    rtb_F_dy = ((631.806 - rtb_Gain_k) - rtb_Subtract) + rtb_FzFR;
    rtb_FzFR += (631.806 - rtb_Gain_k) + rtb_Subtract;
    rtb_F_aero = rtb_F_aero * 0.52 / 2.0;
    rtb_Subtract = ((rtb_Gain_k + 872.494) - rtb_uDLookupTable) + rtb_F_aero;
    rtb_F_aero += (rtb_Gain_k + 872.494) + rtb_uDLookupTable;

    /* MATLAB Function: '<S4>/MATLAB Function' */
    rtb_uDLookupTable = (((rtb_F_dy * rtb_F_dy * -0.0231 + 70.615 * rtb_F_dy) -
                          826.71) * 2.0 + ((rtb_FzFR * rtb_FzFR * -0.0231 +
      70.615 * rtb_FzFR) - 826.71) * 2.0) / 2.0;
    rtb_F_dy = (((rtb_Subtract * rtb_Subtract * -0.0231 + 70.615 * rtb_Subtract)
                 - 826.71) * 2.0 + ((rtb_F_aero * rtb_F_aero * -0.0231 + 70.615 *
      rtb_F_aero) - 826.71) * 2.0) / 2.0;

    /* MATLAB Function: '<S24>/reference yaw rate 1' */
    rtb_F_aero = rtU->vehicle_state.velocity.x * rtb_Gain4 /
      (rtU->vehicle_state.velocity.x * rtU->vehicle_state.velocity.x *
       -0.00029411764705882274 + 1.6);

    /* Signum: '<S4>/Sign' */
    if (rtIsNaN(rtb_torqueCmd_d)) {
      rtb_Gain_k = (rtNaN);
    } else if (rtb_torqueCmd_d < 0.0) {
      rtb_Gain_k = -1.0;
    } else {
      rtb_Gain_k = (rtb_torqueCmd_d > 0.0);
    }

    /* Switch: '<S4>/Switch' incorporates:
     *  Product: '<S4>/Product2'
     *  SignalConversion generated from: '<Root>/Bus Selector2'
     *  Signum: '<S4>/Sign'
     *  Sum: '<S4>/Subtract'
     */
    if ((rtU->imu.gyro.z - rtb_F_aero) * rtb_Gain_k > 0.0) {
      /* Gain: '<Root>/Gain2' incorporates:
       *  Abs: '<S4>/Abs2'
       *  Lookup_n-D: '<S4>/2-D Lookup Table'
       */
      rtb_Gain_k = look2_binlc(fabs(rtb_torqueCmd_d),
        rtU->vehicle_state.velocity.x, rtConstP.pooled2, rtConstP.pooled3,
        rtConstP.pooled1, rtConstP.pooled17, 4U);
    } else {
      /* Gain: '<Root>/Gain2' incorporates:
       *  Abs: '<S4>/Abs2'
       *  Gain: '<S4>/Gain6'
       *  Lookup_n-D: '<S4>/2-D Lookup Table1'
       */
      rtb_Gain_k = 2.0 * look2_binlc(fabs(rtb_torqueCmd_d),
        rtU->vehicle_state.velocity.x, rtConstP.pooled2, rtConstP.pooled3,
        rtConstP.pooled1, rtConstP.pooled17, 4U);
    }

    /* End of Switch: '<S4>/Switch' */

    /* Gain: '<S4>/Gain10' incorporates:
     *  Constant: '<S13>/track'
     *  Constant: '<S13>/wheel radius'
     *  Gain: '<S4>/Gain4'
     *  Gain: '<S4>/Gain5'
     *  Gain: '<S4>/Gain9'
     *  MATLAB Function: '<S4>/MATLAB Function'
     *  MATLAB Function: '<S4>/MATLAB Function1'
     *  Product: '<S13>/Divide'
     *  Product: '<S13>/Product'
     *  SignalConversion generated from: '<Root>/Bus Selector2'
     *  Sum: '<S4>/Sum2'
     */
    rtb_Gain_k = ((0.672 * rtb_F_dy - 0.92799999999999994 * rtb_uDLookupTable) /
                  (rtb_uDLookupTable + rtb_F_dy) * 300.0 *
                  (rtU->vehicle_state.velocity.x * rtU->vehicle_state.velocity.x)
                  / 1.6 * rtb_Gain4 * -(1.0 - fb_ratio) + (rtb_F_aero -
      rtU->imu.gyro.z) / (5.0 * rtb_Gain_k) * fb_ratio) / 1.24 * 0.259 * tv_gain;

    /* Saturate: '<S4>/Saturation' */
    if (rtb_Gain_k > 200.0) {
      /* Gain: '<Root>/Gain2' */
      rtb_Gain_k = 200.0;
    } else if (rtb_Gain_k < -200.0) {
      /* Gain: '<Root>/Gain2' */
      rtb_Gain_k = -200.0;
    }

    /* End of Saturate: '<S4>/Saturation' */

    /* TransferFcn: '<S4>/Transfer Fcn1' incorporates:
     *  Sum: '<S4>/Sum'
     */
    rtb_Gain4 = rtb_TransferFcn - rtb_Gain_k;

    /* Signum: '<S21>/Sign' */
    if (rtIsNaN(rtb_Gain4)) {
      rtb_FzFR = (rtNaN);
    } else if (rtb_Gain4 < 0.0) {
      rtb_FzFR = -1.0;
    } else {
      rtb_FzFR = (rtb_Gain4 > 0.0);
    }

    /* End of Signum: '<S21>/Sign' */
    tmp = rtmIsMajorTimeStep(rtM);
    if (tmp) {
      /* Memory: '<S21>/Memory' */
      rtDW->Memory = rtDW->Memory_PreviousInput;

      /* Memory: '<S21>/Memory1' */
      rtDW->Memory1 = rtDW->Memory1_PreviousInput;

      /* Constant: '<S21>/target_SR' */
      rtDW->target_SR = target_sr;
    }

    /* Abs: '<S21>/Abs1' */
    rtb_F_dy = fabs(rtb_Gain4);

    /* SignalConversion generated from: '<Root>/Bus Selector4' */
    rtDW->sr_l = rtU->tc_in.sr_l;

    /* TransferFcn: '<S4>/Transfer Fcn1' incorporates:
     *  Abs: '<S21>/Abs'
     */
    rtb_Gain4 = fabs(rtDW->sr_l);

    /* Derivative: '<S21>/Derivative' incorporates:
     *  Derivative: '<S22>/Derivative'
     */
    rtb_torqueCmd_d = rtM->Timing.t[0];
    if ((rtDW->TimeStampA >= rtb_torqueCmd_d) && (rtDW->TimeStampB >=
         rtb_torqueCmd_d)) {
      /* Derivative: '<S21>/Derivative' */
      rtb_Subtract = 0.0;
    } else {
      rtb_Subtract = rtDW->TimeStampA;
      lastU = &rtDW->LastUAtTimeA;
      if (rtDW->TimeStampA < rtDW->TimeStampB) {
        if (rtDW->TimeStampB < rtb_torqueCmd_d) {
          rtb_Subtract = rtDW->TimeStampB;
          lastU = &rtDW->LastUAtTimeB;
        }
      } else if (rtDW->TimeStampA >= rtb_torqueCmd_d) {
        rtb_Subtract = rtDW->TimeStampB;
        lastU = &rtDW->LastUAtTimeB;
      }

      /* Derivative: '<S21>/Derivative' */
      rtb_Subtract = (rtDW->sr_l - *lastU) / (rtb_torqueCmd_d - rtb_Subtract);
    }

    /* End of Derivative: '<S21>/Derivative' */

    /* MATLAB Function: '<S4>/MATLAB Function2' incorporates:
     *  SignalConversion generated from: '<Root>/Bus Selector2'
     */
    if (rtU->vehicle_state.velocity.x < 1.0) {
      rtb_uDLookupTable = 0.0;
    } else {
      rtb_uDLookupTable = atan((rtU->vehicle_state.velocity.y - rtU->imu.gyro.z *
        0.672) / rtU->vehicle_state.velocity.x);
    }

    /* End of MATLAB Function: '<S4>/MATLAB Function2' */

    /* MATLAB Function: '<S21>/MATLAB Function' incorporates:
     *  Sum: '<S21>/Subtract'
     */
    MATLABFunction(rtU->cockpit.brake, rtDW->Memory, rtDW->Memory1, rtb_F_dy,
                   rtDW->target_SR - rtb_Gain4, rtb_Subtract, rtb_uDLookupTable,
                   &rtb_Gain4, &rtDW->tc_on_l);

    /* Saturate: '<S21>/Saturation' */
    if (rtb_Gain4 > 1000.0) {
      /* Saturate: '<S21>/Saturation' */
      rtDW->Saturation = 1000.0;
    } else if (rtb_Gain4 < 0.0) {
      /* Saturate: '<S21>/Saturation' */
      rtDW->Saturation = 0.0;
    } else {
      /* Saturate: '<S21>/Saturation' */
      rtDW->Saturation = rtb_Gain4;
    }

    /* End of Saturate: '<S21>/Saturation' */

    /* TransferFcn: '<S4>/Transfer Fcn1' incorporates:
     *  Gain: '<S4>/Gain8'
     *  Lookup_n-D: '<S4>/1-D Lookup Table'
     *  UnitConversion: '<S1>/Unit Conversion'
     */
    /* Unit Conversion - from: rpm to: rad/s
       Expression: output = (0.10472*input) + (0) */
    rtb_Gain4 = look1_binlx(0.10471975511965977 * rtb_Gain * 9.5492965855137211,
      rtConstP.pooled13, rtConstP.pooled12, 14U);

    /* Gain: '<S4>/Gain' incorporates:
     *  Gain: '<S4>/Gain11'
     */
    rtb_F_dy = 0.39999999999999997 * rtb_Gain4 * 3.05;

    /* MATLAB Function: '<S21>/MATLAB Function1' incorporates:
     *  Product: '<S21>/Product'
     */
    MATLABFunction1_l(rtb_FzFR * rtDW->Saturation, rtb_F_dy, &rtb_Gain4);

    /* MATLAB Function: '<S3>/MATLAB Function1' incorporates:
     *  Constant: '<S3>/Constant4'
     *  Constant: '<S3>/Constant5'
     */
    MATLABFunction1(rtb_Gain4, rtb_Gain, torq_derate_begin, torq_derate_end,
                    &rtb_Subtract);

    /* Switch: '<S7>/Switch2' incorporates:
     *  Constant: '<S3>/Constant'
     *  Constant: '<S3>/Constant1'
     *  RelationalOperator: '<S7>/LowerRelop1'
     *  RelationalOperator: '<S7>/UpperRelop'
     *  Switch: '<S7>/Switch'
     */
    if (rtb_Subtract > torq_limit_rl) {
      rtb_Gain = torq_limit_rl;
    } else if (rtb_Subtract < -torq_limit_rl) {
      /* Switch: '<S7>/Switch' incorporates:
       *  Constant: '<S3>/Constant'
       */
      rtb_Gain = -torq_limit_rl;
    } else {
      rtb_Gain = rtb_Subtract;
    }

    /* End of Switch: '<S7>/Switch2' */

    /* RateLimiter: '<S3>/Rate Limiter1' */
    if (rtDW->LastMajorTime == (rtInf)) {
      /* RateLimiter: '<S3>/Rate Limiter1' */
      rtDW->RateLimiter1 = rtb_Gain;
    } else {
      rtb_FzFR = rtM->Timing.t[0];
      rtb_Subtract = rtb_FzFR - rtDW->LastMajorTime;
      if (rtDW->LastMajorTime == rtb_FzFR) {
        if (rtDW->PrevLimited) {
          /* RateLimiter: '<S3>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY;
        } else {
          /* RateLimiter: '<S3>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtb_Gain;
        }
      } else {
        rtb_Sign_p = rtb_Subtract * torq_slew;
        rtb_FzFR = rtb_Gain - rtDW->PrevY;
        if (rtb_FzFR > rtb_Sign_p) {
          /* RateLimiter: '<S3>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY + rtb_Sign_p;
          limitedCache = true;
        } else {
          rtb_Subtract *= -torq_slew;
          if (rtb_FzFR < rtb_Subtract) {
            /* RateLimiter: '<S3>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtDW->PrevY + rtb_Subtract;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S3>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtb_Gain;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S3>/Rate Limiter1' */

    /* Gain: '<Root>/Gain1' */
    rtb_FzFR = 13.1 * rtU->wheel.speed.rr;

    /* TransferFcn: '<S4>/Transfer Fcn1' */
    rtb_Gain4 = 66.666666666666671 * rtX->TransferFcn1_CSTATE;

    /* Gain: '<Root>/Gain2' incorporates:
     *  Sum: '<S4>/Sum1'
     */
    rtb_Gain_k += rtb_Gain4;

    /* Signum: '<S22>/Sign' */
    if (rtIsNaN(rtb_Gain_k)) {
      rtb_Sign_p = (rtNaN);
    } else if (rtb_Gain_k < 0.0) {
      rtb_Sign_p = -1.0;
    } else {
      rtb_Sign_p = (rtb_Gain_k > 0.0);
    }

    /* End of Signum: '<S22>/Sign' */
    if (tmp) {
      /* Memory: '<S22>/Memory' */
      rtDW->Memory_j = rtDW->Memory_PreviousInput_p;

      /* Memory: '<S22>/Memory1' */
      rtDW->Memory1_p = rtDW->Memory1_PreviousInput_c;

      /* Constant: '<S22>/target_SR' */
      rtDW->target_SR_n = target_sr;
    }

    /* Abs: '<S22>/Abs1' */
    rtb_Gain = fabs(rtb_Gain_k);

    /* Gain: '<Root>/Gain2' incorporates:
     *  Abs: '<S22>/Abs'
     */
    rtb_Gain_k = fabs(rtU->tc_in.sr_r);

    /* Derivative: '<S22>/Derivative' */
    if ((rtDW->TimeStampA_g >= rtb_torqueCmd_d) && (rtDW->TimeStampB_i >=
         rtb_torqueCmd_d)) {
      /* Derivative: '<S22>/Derivative' */
      rtb_torqueCmd_d = 0.0;
    } else {
      rtb_Subtract = rtDW->TimeStampA_g;
      lastU = &rtDW->LastUAtTimeA_k;
      if (rtDW->TimeStampA_g < rtDW->TimeStampB_i) {
        if (rtDW->TimeStampB_i < rtb_torqueCmd_d) {
          rtb_Subtract = rtDW->TimeStampB_i;
          lastU = &rtDW->LastUAtTimeB_e;
        }
      } else if (rtDW->TimeStampA_g >= rtb_torqueCmd_d) {
        rtb_Subtract = rtDW->TimeStampB_i;
        lastU = &rtDW->LastUAtTimeB_e;
      }

      /* Derivative: '<S22>/Derivative' */
      rtb_torqueCmd_d = (rtU->tc_in.sr_r - *lastU) / (rtb_torqueCmd_d -
        rtb_Subtract);
    }

    /* MATLAB Function: '<S22>/MATLAB Function' incorporates:
     *  Sum: '<S22>/Subtract'
     */
    MATLABFunction(rtU->cockpit.brake, rtDW->Memory_j, rtDW->Memory1_p, rtb_Gain,
                   rtDW->target_SR_n - rtb_Gain_k, rtb_torqueCmd_d,
                   rtb_uDLookupTable, &rtb_Gain_k, &rtDW->tc_on);

    /* Saturate: '<S22>/Saturation' */
    if (rtb_Gain_k > 1000.0) {
      /* Saturate: '<S22>/Saturation' */
      rtDW->Saturation_d = 1000.0;
    } else if (rtb_Gain_k < 0.0) {
      /* Saturate: '<S22>/Saturation' */
      rtDW->Saturation_d = 0.0;
    } else {
      /* Saturate: '<S22>/Saturation' */
      rtDW->Saturation_d = rtb_Gain_k;
    }

    /* End of Saturate: '<S22>/Saturation' */

    /* Gain: '<Root>/Gain2' incorporates:
     *  Gain: '<S4>/Gain7'
     *  Lookup_n-D: '<S4>/1-D Lookup Table1'
     *  UnitConversion: '<S2>/Unit Conversion'
     */
    /* Unit Conversion - from: rpm to: rad/s
       Expression: output = (0.10472*input) + (0) */
    rtb_Gain_k = look1_binlx(0.10471975511965977 * rtb_FzFR * 9.5492965855137211,
      rtConstP.pooled13, rtConstP.pooled12, 14U);

    /* Gain: '<S4>/Gain1' incorporates:
     *  Gain: '<S4>/Gain12'
     */
    rtb_Gain = 0.39999999999999997 * rtb_Gain_k * 3.05;

    /* MATLAB Function: '<S22>/MATLAB Function1' incorporates:
     *  Product: '<S22>/Product'
     */
    MATLABFunction1_l(rtb_Sign_p * rtDW->Saturation_d, rtb_Gain, &rtb_Gain_k);

    /* MATLAB Function: '<S3>/MATLAB Function2' incorporates:
     *  Constant: '<S3>/Constant4'
     *  Constant: '<S3>/Constant5'
     */
    MATLABFunction1(rtb_Gain_k, rtb_FzFR, torq_derate_begin, torq_derate_end,
                    &rtb_torqueCmd_d);

    /* Switch: '<S8>/Switch2' incorporates:
     *  Constant: '<S3>/Constant2'
     *  Constant: '<S3>/Constant3'
     *  RelationalOperator: '<S8>/LowerRelop1'
     *  RelationalOperator: '<S8>/UpperRelop'
     *  Switch: '<S8>/Switch'
     */
    if (rtb_torqueCmd_d > torq_limit_rr) {
      rtb_Gain_k = torq_limit_rr;
    } else if (rtb_torqueCmd_d < -torq_limit_rr) {
      /* Switch: '<S8>/Switch' incorporates:
       *  Constant: '<S3>/Constant3'
       */
      rtb_Gain_k = -torq_limit_rr;
    } else {
      rtb_Gain_k = rtb_torqueCmd_d;
    }

    /* End of Switch: '<S8>/Switch2' */

    /* RateLimiter: '<S3>/Rate Limiter' */
    if (rtDW->LastMajorTime_l == (rtInf)) {
      /* RateLimiter: '<S3>/Rate Limiter' */
      rtDW->RateLimiter = rtb_Gain_k;
    } else {
      rtb_FzFR = rtM->Timing.t[0];
      rtb_Subtract = rtb_FzFR - rtDW->LastMajorTime_l;
      if (rtDW->LastMajorTime_l == rtb_FzFR) {
        if (rtDW->PrevLimited_m) {
          /* RateLimiter: '<S3>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_o;
        } else {
          /* RateLimiter: '<S3>/Rate Limiter' */
          rtDW->RateLimiter = rtb_Gain_k;
        }
      } else {
        rtb_Sign_p = rtb_Subtract * torq_slew;
        rtb_FzFR = rtb_Gain_k - rtDW->PrevY_o;
        if (rtb_FzFR > rtb_Sign_p) {
          /* RateLimiter: '<S3>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY_o + rtb_Sign_p;
          limitedCache = true;
        } else {
          rtb_Subtract *= -torq_slew;
          if (rtb_FzFR < rtb_Subtract) {
            /* RateLimiter: '<S3>/Rate Limiter' */
            rtDW->RateLimiter = rtDW->PrevY_o + rtb_Subtract;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S3>/Rate Limiter' */
            rtDW->RateLimiter = rtb_Gain_k;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited_m = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S3>/Rate Limiter' */

    /* Gain: '<Root>/Gain2' */
    rtb_Gain_k = 0.01 * rtU->cockpit.accel;

    /* Product: '<S4>/Product1' */
    rtDW->Product1 = rtb_Gain_k * rtb_Gain;

    /* Product: '<S4>/Product' */
    rtDW->Product = rtb_F_dy * rtb_Gain_k;
    if (tmp) {
      /* BusCreator generated from: '<Root>/torq_BusCreator' incorporates:
       *  Constant: '<Root>/Constant'
       */
      rtDW->header.timestamp_ns = 0ULL;

      /* BusCreator generated from: '<Root>/tc_BusCreator' incorporates:
       *  Constant: '<Root>/Constant3'
       */
      rtDW->header_g.timestamp_ns = 0ULL;

      /* Memory: '<S15>/Memory2' */
      rtb_Memory2 = rtDW->Memory2_PreviousInput;

      /* Memory: '<S15>/Memory1' */
      rtb_Memory1 = rtDW->Memory1_PreviousInput_m;

      /* Memory: '<S15>/Memory' */
      rtb_Memory = rtDW->Memory_PreviousInput_k;

      /* MATLAB Function: '<S15>/MATLAB Function5' incorporates:
       *  Memory: '<S15>/Memory3'
       */
      MATLABFunction5(rtb_Memory2, rtb_Memory1, rtb_Memory,
                      rtDW->Memory3_PreviousInput, 0.0, &rtDW->y_e);

      /* Memory: '<S17>/Memory2' */
      rtb_Memory2_l = rtDW->Memory2_PreviousInput_c;

      /* Memory: '<S17>/Memory1' */
      rtb_Memory1_a = rtDW->Memory1_PreviousInput_a;

      /* Memory: '<S17>/Memory' */
      rtb_Memory_j = rtDW->Memory_PreviousInput_d;

      /* MATLAB Function: '<S17>/MATLAB Function5' incorporates:
       *  Memory: '<S17>/Memory3'
       */
      MATLABFunction5(rtb_Memory2_l, rtb_Memory1_a, rtb_Memory_j,
                      rtDW->Memory3_PreviousInput_e, rtDW->y_e, &rtDW->y_p);

      /* Memory: '<S19>/Memory2' */
      rtb_Memory2_i = rtDW->Memory2_PreviousInput_f;

      /* Memory: '<S19>/Memory1' */
      rtb_Memory1_m = rtDW->Memory1_PreviousInput_mi;

      /* MATLAB Function: '<S19>/MATLAB Function5' incorporates:
       *  Memory: '<S19>/Memory'
       */
      MATLABFunction5_o(rtb_Memory2_i, rtb_Memory1_m,
                        rtDW->Memory_PreviousInput_m, rtDW->y_p, &rtDW->y_f);

      /* Memory: '<S16>/Memory2' */
      rtb_Memory2_n = rtDW->Memory2_PreviousInput_e;

      /* Memory: '<S16>/Memory1' */
      rtb_Memory1_l = rtDW->Memory1_PreviousInput_n;

      /* Memory: '<S16>/Memory' */
      rtb_Memory_o = rtDW->Memory_PreviousInput_a;

      /* MATLAB Function: '<S16>/MATLAB Function5' incorporates:
       *  Memory: '<S16>/Memory3'
       */
      MATLABFunction5(rtb_Memory2_n, rtb_Memory1_l, rtb_Memory_o,
                      rtDW->Memory3_PreviousInput_o, 0.0, &rtDW->y_m);

      /* Memory: '<S18>/Memory2' */
      rtb_Memory2_m = rtDW->Memory2_PreviousInput_h;

      /* Memory: '<S18>/Memory1' */
      rtb_Memory1_n = rtDW->Memory1_PreviousInput_nw;

      /* Memory: '<S18>/Memory' */
      rtb_Memory_f = rtDW->Memory_PreviousInput_j;

      /* MATLAB Function: '<S18>/MATLAB Function5' incorporates:
       *  Memory: '<S18>/Memory3'
       */
      MATLABFunction5(rtb_Memory2_m, rtb_Memory1_n, rtb_Memory_f,
                      rtDW->Memory3_PreviousInput_c, rtDW->y_m, &rtDW->y_i);

      /* Memory: '<S20>/Memory2' */
      rtb_Memory2_f = rtDW->Memory2_PreviousInput_m;

      /* Memory: '<S20>/Memory1' */
      rtb_Memory1_h = rtDW->Memory1_PreviousInput_d;

      /* MATLAB Function: '<S20>/MATLAB Function5' incorporates:
       *  Memory: '<S20>/Memory'
       */
      MATLABFunction5_o(rtb_Memory2_f, rtb_Memory1_h,
                        rtDW->Memory_PreviousInput_o, rtDW->y_i, &rtDW->y);
    }

    /* Outport: '<Root>/torq' incorporates:
     *  BusCreator generated from: '<Root>/torq_BusCreator'
     *  Constant: '<Root>/Constant1'
     *  Constant: '<Root>/Constant2'
     */
    rtY->torq.header = rtDW->header;
    rtY->torq.torque.fl = 0.0;
    rtY->torq.torque.fr = 0.0;
    rtY->torq.torque.rl = rtDW->RateLimiter1;
    rtY->torq.torque.rr = rtDW->RateLimiter;

    /* Outport: '<Root>/tc' incorporates:
     *  BusCreator generated from: '<Root>/tc_BusCreator'
     *  SignalConversion generated from: '<Root>/Bus Selector2'
     */
    rtY->tc.header = rtDW->header_g;
    rtY->tc.sr_l = rtb_TransferFcn;
    rtY->tc.sr_r = rtb_Gain4;
    rtY->tc.sa = rtb_uDLookupTable;
    rtY->tc.yawrate_real = rtU->imu.gyro.z;
    rtY->tc.yawrate_ref = rtb_F_aero;
  }

  if (rtmIsMajorTimeStep(rtM)) {
    double LastMajorTime_tmp;
    double *lastU;
    bool tmp;
    tmp = rtmIsMajorTimeStep(rtM);
    if (tmp) {
      /* Update for Memory: '<S21>/Memory' */
      rtDW->Memory_PreviousInput = rtDW->Saturation;

      /* Update for Memory: '<S21>/Memory1' */
      rtDW->Memory1_PreviousInput = rtDW->tc_on_l;
    }

    /* Update for Derivative: '<S21>/Derivative' */
    if (rtDW->TimeStampA == (rtInf)) {
      rtDW->TimeStampA = rtM->Timing.t[0];
      lastU = &rtDW->LastUAtTimeA;
    } else if (rtDW->TimeStampB == (rtInf)) {
      rtDW->TimeStampB = rtM->Timing.t[0];
      lastU = &rtDW->LastUAtTimeB;
    } else if (rtDW->TimeStampA < rtDW->TimeStampB) {
      rtDW->TimeStampA = rtM->Timing.t[0];
      lastU = &rtDW->LastUAtTimeA;
    } else {
      rtDW->TimeStampB = rtM->Timing.t[0];
      lastU = &rtDW->LastUAtTimeB;
    }

    *lastU = rtDW->sr_l;

    /* End of Update for Derivative: '<S21>/Derivative' */

    /* Update for RateLimiter: '<S3>/Rate Limiter1' incorporates:
     *  RateLimiter: '<S3>/Rate Limiter'
     */
    rtDW->PrevY = rtDW->RateLimiter1;
    LastMajorTime_tmp = rtM->Timing.t[0];
    rtDW->LastMajorTime = LastMajorTime_tmp;
    if (tmp) {
      /* Update for Memory: '<S22>/Memory' */
      rtDW->Memory_PreviousInput_p = rtDW->Saturation_d;

      /* Update for Memory: '<S22>/Memory1' */
      rtDW->Memory1_PreviousInput_c = rtDW->tc_on;
    }

    /* Update for Derivative: '<S22>/Derivative' */
    if (rtDW->TimeStampA_g == (rtInf)) {
      rtDW->TimeStampA_g = rtM->Timing.t[0];
      lastU = &rtDW->LastUAtTimeA_k;
    } else if (rtDW->TimeStampB_i == (rtInf)) {
      rtDW->TimeStampB_i = rtM->Timing.t[0];
      lastU = &rtDW->LastUAtTimeB_e;
    } else if (rtDW->TimeStampA_g < rtDW->TimeStampB_i) {
      rtDW->TimeStampA_g = rtM->Timing.t[0];
      lastU = &rtDW->LastUAtTimeA_k;
    } else {
      rtDW->TimeStampB_i = rtM->Timing.t[0];
      lastU = &rtDW->LastUAtTimeB_e;
    }

    *lastU = rtU->tc_in.sr_r;

    /* End of Update for Derivative: '<S22>/Derivative' */

    /* Update for RateLimiter: '<S3>/Rate Limiter' */
    rtDW->PrevY_o = rtDW->RateLimiter;
    rtDW->LastMajorTime_l = LastMajorTime_tmp;
    if (tmp) {
      /* Update for Memory: '<S15>/Memory2' */
      rtDW->Memory2_PreviousInput = rtDW->y_e;

      /* Update for Memory: '<S15>/Memory1' */
      rtDW->Memory1_PreviousInput_m = rtb_Memory2;

      /* Update for Memory: '<S15>/Memory' */
      rtDW->Memory_PreviousInput_k = rtb_Memory1;

      /* Update for Memory: '<S15>/Memory3' */
      rtDW->Memory3_PreviousInput = rtb_Memory;

      /* Update for Memory: '<S17>/Memory2' */
      rtDW->Memory2_PreviousInput_c = rtDW->y_p;

      /* Update for Memory: '<S17>/Memory1' */
      rtDW->Memory1_PreviousInput_a = rtb_Memory2_l;

      /* Update for Memory: '<S17>/Memory' */
      rtDW->Memory_PreviousInput_d = rtb_Memory1_a;

      /* Update for Memory: '<S17>/Memory3' */
      rtDW->Memory3_PreviousInput_e = rtb_Memory_j;

      /* Update for Memory: '<S19>/Memory2' */
      rtDW->Memory2_PreviousInput_f = rtDW->y_f;

      /* Update for Memory: '<S19>/Memory1' */
      rtDW->Memory1_PreviousInput_mi = rtb_Memory2_i;

      /* Update for Memory: '<S19>/Memory' */
      rtDW->Memory_PreviousInput_m = rtb_Memory1_m;

      /* Update for Memory: '<S16>/Memory2' */
      rtDW->Memory2_PreviousInput_e = rtDW->y_m;

      /* Update for Memory: '<S16>/Memory1' */
      rtDW->Memory1_PreviousInput_n = rtb_Memory2_n;

      /* Update for Memory: '<S16>/Memory' */
      rtDW->Memory_PreviousInput_a = rtb_Memory1_l;

      /* Update for Memory: '<S16>/Memory3' */
      rtDW->Memory3_PreviousInput_o = rtb_Memory_o;

      /* Update for Memory: '<S18>/Memory2' */
      rtDW->Memory2_PreviousInput_h = rtDW->y_i;

      /* Update for Memory: '<S18>/Memory1' */
      rtDW->Memory1_PreviousInput_nw = rtb_Memory2_m;

      /* Update for Memory: '<S18>/Memory' */
      rtDW->Memory_PreviousInput_j = rtb_Memory1_n;

      /* Update for Memory: '<S18>/Memory3' */
      rtDW->Memory3_PreviousInput_c = rtb_Memory_f;

      /* Update for Memory: '<S20>/Memory2' */
      rtDW->Memory2_PreviousInput_m = rtDW->y;

      /* Update for Memory: '<S20>/Memory1' */
      rtDW->Memory1_PreviousInput_d = rtb_Memory2_f;

      /* Update for Memory: '<S20>/Memory' */
      rtDW->Memory_PreviousInput_o = rtb_Memory1_h;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo, rtM, rtU, rtY);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void vehicle_control_derivatives(vehicle_control_RT_MODEL *const rtM)
{
  vehicle_control_DW *rtDW = rtM->dwork;
  vehicle_control_X *rtX = rtM->contStates;
  vehicle_control_XDot *_rtXdot;
  _rtXdot = ((vehicle_control_XDot *) rtM->derivs);

  /* Derivatives for TransferFcn: '<S4>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = -66.666666666666671 * rtX->TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += rtDW->Product;

  /* Derivatives for TransferFcn: '<S4>/Transfer Fcn1' */
  _rtXdot->TransferFcn1_CSTATE = -66.666666666666671 * rtX->TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += rtDW->Product1;
}

/* Model initialize function */
void vehicle_control_initialize(vehicle_control_RT_MODEL *const rtM)
{
  vehicle_control_DW *rtDW = rtM->dwork;
  vehicle_control_X *rtX = rtM->contStates;
  vehicle_control_XDis *rtXDis = ((vehicle_control_XDis *)
    rtM->contStateDisabled);

  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (double **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&rtM->solverInfo, (bool**)
      &rtM->contStateDisabled);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&rtM->solverInfo, false);
  rtsiSetIsContModeFrozen(&rtM->solverInfo, false);
  rtM->intgData.y = rtM->odeY;
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->intgData.f[1] = rtM->odeF[1];
  rtM->intgData.f[2] = rtM->odeF[2];
  rtM->contStates = ((vehicle_control_X *) rtX);
  rtM->contStateDisabled = ((vehicle_control_XDis *) rtXDis);
  rtM->Timing.tStart = (0.0);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetSolverName(&rtM->solverInfo,"ode3");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.01;

  /* InitializeConditions for TransferFcn: '<S4>/Transfer Fcn' */
  rtX->TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S21>/Derivative' */
  rtDW->TimeStampA = (rtInf);
  rtDW->TimeStampB = (rtInf);

  /* InitializeConditions for RateLimiter: '<S3>/Rate Limiter1' */
  rtDW->LastMajorTime = (rtInf);

  /* InitializeConditions for TransferFcn: '<S4>/Transfer Fcn1' */
  rtX->TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S22>/Derivative' */
  rtDW->TimeStampA_g = (rtInf);
  rtDW->TimeStampB_i = (rtInf);

  /* InitializeConditions for RateLimiter: '<S3>/Rate Limiter' */
  rtDW->LastMajorTime_l = (rtInf);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
