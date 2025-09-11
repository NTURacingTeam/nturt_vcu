/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: vehicle_control.c
 *
 * Code generated for Simulink model 'vehicle_control'.
 *
 * Model version                  : 5.8
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Thu Sep 11 12:31:01 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "vehicle_control.h"
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

/*
 * Output and update for atomic system:
 *    '<S1>/MATLAB Function1'
 *    '<S1>/MATLAB Function2'
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
    double deltaT;
    double deltaT_tmp;
    double riseValLimit;
    double rtb_Gain3;
    double rtb_torqueCmd;
    bool limitedCache;

    /* Gain: '<Root>/Gain3' */
    rtb_Gain3 = 0.01 * rtU->cockpit.accel;

    /* MATLAB Function: '<S1>/MATLAB Function2' incorporates:
     *  Constant: '<S1>/Constant4'
     *  Constant: '<S1>/Constant5'
     *  Gain: '<Root>/Gain1'
     */
    MATLABFunction1(rtb_Gain3, 0.076335877862595422 * rtU->wheel.speed.rr,
                    torq_derate_begin, torq_derate_end, &rtb_torqueCmd);

    /* Gain: '<S1>/Gain1' */
    rtb_torqueCmd *= torq_limit_rr;

    /* RateLimiter: '<S1>/Rate Limiter' */
    if (rtDW->LastMajorTime == (rtInf)) {
      /* RateLimiter: '<S1>/Rate Limiter' */
      rtDW->RateLimiter = rtb_torqueCmd;
    } else {
      deltaT_tmp = rtM->Timing.t[0];
      deltaT = deltaT_tmp - rtDW->LastMajorTime;
      if (rtDW->LastMajorTime == deltaT_tmp) {
        if (rtDW->PrevLimited) {
          /* RateLimiter: '<S1>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY;
        } else {
          /* RateLimiter: '<S1>/Rate Limiter' */
          rtDW->RateLimiter = rtb_torqueCmd;
        }
      } else {
        riseValLimit = deltaT * torq_slew;
        deltaT_tmp = rtb_torqueCmd - rtDW->PrevY;
        if (deltaT_tmp > riseValLimit) {
          /* RateLimiter: '<S1>/Rate Limiter' */
          rtDW->RateLimiter = rtDW->PrevY + riseValLimit;
          limitedCache = true;
        } else {
          deltaT *= -2.0 * torq_slew;
          if (deltaT_tmp < deltaT) {
            /* RateLimiter: '<S1>/Rate Limiter' */
            rtDW->RateLimiter = rtDW->PrevY + deltaT;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S1>/Rate Limiter' */
            rtDW->RateLimiter = rtb_torqueCmd;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S1>/Rate Limiter' */

    /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
     *  Constant: '<S1>/Constant4'
     *  Constant: '<S1>/Constant5'
     *  Gain: '<Root>/Gain2'
     */
    MATLABFunction1(rtb_Gain3, 0.076335877862595422 * rtU->wheel.speed.rl,
                    torq_derate_begin, torq_derate_end, &rtb_torqueCmd);

    /* Gain: '<S1>/Gain' */
    rtb_Gain3 = torq_limit_rl * rtb_torqueCmd;

    /* RateLimiter: '<S1>/Rate Limiter1' */
    if (rtDW->LastMajorTime_i == (rtInf)) {
      /* RateLimiter: '<S1>/Rate Limiter1' */
      rtDW->RateLimiter1 = rtb_Gain3;
    } else {
      deltaT_tmp = rtM->Timing.t[0];
      deltaT = deltaT_tmp - rtDW->LastMajorTime_i;
      if (rtDW->LastMajorTime_i == deltaT_tmp) {
        if (rtDW->PrevLimited_k) {
          /* RateLimiter: '<S1>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY_b;
        } else {
          /* RateLimiter: '<S1>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtb_Gain3;
        }
      } else {
        riseValLimit = deltaT * torq_slew;
        deltaT_tmp = rtb_Gain3 - rtDW->PrevY_b;
        if (deltaT_tmp > riseValLimit) {
          /* RateLimiter: '<S1>/Rate Limiter1' */
          rtDW->RateLimiter1 = rtDW->PrevY_b + riseValLimit;
          limitedCache = true;
        } else {
          deltaT *= -2.0 * torq_slew;
          if (deltaT_tmp < deltaT) {
            /* RateLimiter: '<S1>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtDW->PrevY_b + deltaT;
            limitedCache = true;
          } else {
            /* RateLimiter: '<S1>/Rate Limiter1' */
            rtDW->RateLimiter1 = rtb_Gain3;
            limitedCache = false;
          }
        }

        if (rtsiIsModeUpdateTimeStep(&rtM->solverInfo)) {
          rtDW->PrevLimited_k = limitedCache;
        }
      }
    }

    /* End of RateLimiter: '<S1>/Rate Limiter1' */

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

    /* Update for RateLimiter: '<S1>/Rate Limiter' incorporates:
     *  RateLimiter: '<S1>/Rate Limiter1'
     */
    rtDW->PrevY = rtDW->RateLimiter;
    LastMajorTime_tmp = rtM->Timing.t[0];
    rtDW->LastMajorTime = LastMajorTime_tmp;

    /* Update for RateLimiter: '<S1>/Rate Limiter1' */
    rtDW->PrevY_b = rtDW->RateLimiter1;
    rtDW->LastMajorTime_i = LastMajorTime_tmp;
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

  /* InitializeConditions for RateLimiter: '<S1>/Rate Limiter' */
  rtDW->LastMajorTime = (rtInf);

  /* InitializeConditions for RateLimiter: '<S1>/Rate Limiter1' */
  rtDW->LastMajorTime_i = (rtInf);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
