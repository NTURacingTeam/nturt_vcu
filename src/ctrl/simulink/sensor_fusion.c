/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: sensor_fusion.c
 *
 * Code generated for Simulink model 'sensor_fusion'.
 *
 * Model version                  : 5.14
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Sun Apr  5 15:38:40 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "sensor_fusion.h"
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "rt_hypotd_snf.h"
#include "simulink_import.h"
#include <stdbool.h>
#include "rt_nonfinite.h"
#include "look1_binlx.h"
#include "div_nde_s32_floor.h"

/* Block signals and states (default storage) */
sensor_fusion_DW sensor_fusion_DW_l;

/* External inputs (root inport signals with default storage) */
sensor_fusion_ExtU sensor_fusion_U;

/* External outputs (root outports fed by signals with default storage) */
sensor_fusion_ExtY sensor_fusion_Y;

/* Real-time model */
static sensor_fusion_RT_MODEL sensor_fusion_M_;
sensor_fusion_RT_MODEL *const sensor_fusion_M = &sensor_fusion_M_;
extern const double rtCP_pooled_BrF7RapXGBLM[9];
extern const double rtCP_pooled_zKsMALM6gECc[101];
extern const double rtCP_pooled_0doAzsqEh8nf[101];
extern const double rtCP_pooled_jCKyeStS7uCu[101];
extern const double rtCP_pooled_a7eukLP6siL3[9];

#define rtCP_G_Value                   rtCP_pooled_BrF7RapXGBLM  /* Expression: [0.01 0 0;0 0.01 0;0 0 1]
                                                                  * Referenced by: '<S5>/G'
                                                                  */
#define rtCP_G_Value_p                 rtCP_pooled_BrF7RapXGBLM  /* Expression: [0.01 0 0;0 0.01 0;0 0 1]
                                                                  * Referenced by: '<S7>/G'
                                                                  */
#define rtCP_SteerWheeltoSteerAngleL2_t rtCP_pooled_zKsMALM6gECc /* Expression: [-0.6680937;-0.653558249;-0.639118443;-0.624770091;-0.61050953;-0.596332569;-0.58223572;-0.568215316;-0.554268041;-0.540390405;-0.52657944;-0.512832005;-0.499144959;-0.485515509;-0.471940687;-0.458418051;-0.444944458;-0.43151764;-0.418134805;-0.404793683;-0.391491656;-0.378226281;-0.36499529;-0.351796412;-0.33862703;-0.325485225;-0.312368727;-0.299275092;-0.286202227;-0.273148212;-0.260110428;-0.247087131;-0.23407605;-0.221074918;-0.208081641;-0.195094297;-0.182110618;-0.169128301;-0.156145373;-0.143159635;-0.13016887;-0.11717088;-0.10416343;-0.091144268;-0.078111092;-0.06506158;-0.051993375;-0.038904052;-0.025791166;-0.012652193;0.000515427;0.013714331;0.02694722;0.040216871;0.053526141;0.066877961;0.080275405;0.093721614;0.107219815;0.120773431;0.134385934;0.148061025;0.161802473;0.175614328;0.189500691;0.203465943;0.217514621;0.231651614;0.245881981;0.260210959;0.274644483;0.289188311;0.303848728;0.318632888;0.333547773;0.348601063;0.36380131;0.379157066;0.394678104;0.410374722;0.426258091;0.442340427;0.458634995;0.475156281;0.491920169;0.508944284;0.526247827;0.543852789;0.561782905;0.580065403;0.598731001;0.617814431;0.637355486;0.657400592;0.678003156;0.699226359;0.7211456;0.74385181;0.767455991;0.792097247;0.81795238]
                                                                  * Referenced by: '<S2>/SteerWheel to SteerAngle(L)2'
                                                                  */
#define rtCP_SteerWheeltoSteerAngleL2_b rtCP_pooled_0doAzsqEh8nf /* Expression: [-3.1415926;-3.078760748;-3.015928896;-2.953097044;-2.890265192;-2.82743334;-2.764601488;-2.701769636;-2.638937784;-2.576105932;-2.51327408;-2.450442228;-2.387610376;-2.324778524;-2.261946672;-2.19911482;-2.136282968;-2.073451116;-2.010619264;-1.947787412;-1.88495556;-1.822123708;-1.759291856;-1.696460004;-1.633628152;-1.5707963;-1.507964448;-1.445132596;-1.382300744;-1.319468892;-1.25663704;-1.193805188;-1.130973336;-1.068141484;-1.005309632;-0.94247778;-0.879645928;-0.816814076;-0.753982224;-0.691150372;-0.62831852;-0.565486668;-0.502654816;-0.439822964;-0.376991112;-0.31415926;-0.251327408;-0.188495556;-0.125663704;-0.062831852;-2.8678e-15;0.062831852;0.125663704;0.188495556;0.251327408;0.31415926;0.376991112;0.439822964;0.502654816;0.565486668;0.62831852;0.691150372;0.753982224;0.816814076;0.879645928;0.94247778;1.005309632;1.068141484;1.130973336;1.193805188;1.25663704;1.319468892;1.382300744;1.445132596;1.507964448;1.5707963;1.633628152;1.696460004;1.759291856;1.822123708;1.88495556;1.947787412;2.010619264;2.073451116;2.136282968;2.19911482;2.261946672;2.324778524;2.387610376;2.450442228;2.51327408;2.576105932;2.638937784;2.701769636;2.764601488;2.82743334;2.890265192;2.953097044;3.015928896;3.078760748;3.1415926]
                                                                  * Referenced by: '<S2>/SteerWheel to SteerAngle(L)2'
                                                                  */
#define rtCP_SteerWheeltoSteerAngleR2_t rtCP_pooled_jCKyeStS7uCu /* Expression: [-0.817958663;-0.792103181;-0.767461751;-0.743857395;-0.721151011;-0.699231595;-0.678008217;-0.657405479;-0.637360373;-0.617818968;-0.598735364;-0.580069766;-0.561787094;-0.543856803;-0.526251842;-0.50894795;-0.491923834;-0.475159772;-0.458638486;-0.442343743;-0.426261232;-0.410377689;-0.394681071;-0.379159858;-0.363804103;-0.348603856;-0.333550391;-0.318635331;-0.303851171;-0.289190406;-0.274646577;-0.260213054;-0.245883901;-0.231653359;-0.217516367;-0.203467514;-0.189502087;-0.175615724;-0.1618038;-0.148062247;-0.134387051;-0.120774443;-0.10722074;-0.093722416;-0.080276121;-0.06687859;-0.053526647;-0.04021729;-0.026947534;-0.013714544;-0.000515538;0.012652185;0.025791254;0.038904244;0.051993672;0.065061981;0.078111598;0.091144879;0.104164145;0.1171717;0.130169795;0.143160664;0.156146525;0.16912954;0.18211184;0.195095693;0.208083211;0.221076664;0.234077796;0.247089051;0.260112523;0.273150306;0.286204496;0.299277536;0.31237117;0.325487843;0.338629823;0.351799205;0.364998257;0.378229423;0.391494972;0.404796999;0.418138296;0.431521306;0.444948298;0.45842189;0.471944876;0.485519697;0.499149322;0.512836369;0.526584152;0.540395117;0.554272928;0.568220377;0.582240956;0.59633798;0.61051494;0.624775851;0.639124377;0.653564358;0.668099983]
                                                                  * Referenced by: '<S2>/SteerWheel to SteerAngle(R)2'
                                                                  */
#define rtCP_SteerWheeltoSteerAngleR2_b rtCP_pooled_0doAzsqEh8nf /* Expression: [-3.1415926;-3.078760748;-3.015928896;-2.953097044;-2.890265192;-2.82743334;-2.764601488;-2.701769636;-2.638937784;-2.576105932;-2.51327408;-2.450442228;-2.387610376;-2.324778524;-2.261946672;-2.19911482;-2.136282968;-2.073451116;-2.010619264;-1.947787412;-1.88495556;-1.822123708;-1.759291856;-1.696460004;-1.633628152;-1.5707963;-1.507964448;-1.445132596;-1.382300744;-1.319468892;-1.25663704;-1.193805188;-1.130973336;-1.068141484;-1.005309632;-0.94247778;-0.879645928;-0.816814076;-0.753982224;-0.691150372;-0.62831852;-0.565486668;-0.502654816;-0.439822964;-0.376991112;-0.31415926;-0.251327408;-0.188495556;-0.125663704;-0.062831852;-2.8678e-15;0.062831852;0.125663704;0.188495556;0.251327408;0.31415926;0.376991112;0.439822964;0.502654816;0.565486668;0.62831852;0.691150372;0.753982224;0.816814076;0.879645928;0.94247778;1.005309632;1.068141484;1.130973336;1.193805188;1.25663704;1.319468892;1.382300744;1.445132596;1.507964448;1.5707963;1.633628152;1.696460004;1.759291856;1.822123708;1.88495556;1.947787412;2.010619264;2.073451116;2.136282968;2.19911482;2.261946672;2.324778524;2.387610376;2.450442228;2.51327408;2.576105932;2.638937784;2.701769636;2.764601488;2.82743334;2.890265192;2.953097044;3.015928896;3.078760748;3.1415926]
                                                                  * Referenced by: '<S2>/SteerWheel to SteerAngle(R)2'
                                                                  */
#define rtCP_DataStoreMemoryP_InitialVa rtCP_pooled_a7eukLP6siL3 /* Expression: p.InitialCovariance
                                                                  * Referenced by: '<S3>/DataStoreMemory - P'
                                                                  */

static void stateTransitionFcn(const double rtu_x[3], const double rtu_w[3],
  double rty_xNext[3]);
static void MeasurmentFcn(const double rtu_x[3], const double rtu_v[4], double
  rty_y[4]);
static void stateTransitionJacobianFcn(const double rtu_x[3], const double
  rtu_w[3], double rty_A[9], double rty_G[9]);

/* Forward declaration for local functions */
static double xzlangeM(const double x[16]);
static void xzlascl(double cfrom, double cto, double A[16]);
static double xnrm2(int32_t n, const double x[16], int32_t ix0);
static double xdotc(int32_t n, const double x[16], int32_t ix0, const double y
                    [16], int32_t iy0);
static void xaxpy(int32_t n, double a, int32_t ix0, double y[16], int32_t iy0);
static double xnrm2_e(int32_t n, const double x[4], int32_t ix0);
static void xaxpy_e(int32_t n, double a, const double x[16], int32_t ix0, double
                    y[4], int32_t iy0);
static void xaxpy_ew(int32_t n, double a, const double x[4], int32_t ix0, double
                     y[16], int32_t iy0);
static void xzlascl_e(double cfrom, double cto, double A[4]);
static void xswap_ew(double x[16], int32_t ix0, int32_t iy0);
static void xrotg(double a, double b, double *b_a, double *b_b, double *c,
                  double *s);
static void xrot_ew(double x[16], int32_t ix0, int32_t iy0, double c, double s);
static void svd(const double A[16], double U[16], double s[4], double V[16]);
static double xnrm2_ew(int32_t n, const double x[28], int32_t ix0);
static void EKFCorrectorNonAdditive_getMeas(const double Rs[16], const double x
  [3], const double S[9], double zEstimated[4], double Pxy[12], double Sy[16],
  double dhdx[12], double Rsqrt[16]);
static void trisolve(const double A[16], double B[12]);
static void trisolve_e(const double A[16], double B[12]);
static double xnrm2_ewq(int32_t n, const double x[21], int32_t ix0);
static void qrFactor(const double A[9], const double S[9], const double Ns[12],
                     double b_S[9]);
static double xzlangeM_e(const double x[9]);
static void xzlascl_ew(double cfrom, double cto, double A[9]);
static double xnrm2_ewqs(int32_t n, const double x[9], int32_t ix0);
static double xdotc_e(int32_t n, const double x[9], int32_t ix0, const double y
                      [9], int32_t iy0);
static void xaxpy_ewq(int32_t n, double a, int32_t ix0, double y[9], int32_t iy0);
static double xnrm2_ewqsy(const double x[3], int32_t ix0);
static void xaxpy_ewqs(int32_t n, double a, const double x[9], int32_t ix0,
  double y[3], int32_t iy0);
static void xaxpy_ewqsy(int32_t n, double a, const double x[3], int32_t ix0,
  double y[9], int32_t iy0);
static void xzlascl_ewq(double cfrom, double cto, double A[3]);
static void xswap_ewq(double x[9], int32_t ix0, int32_t iy0);
static void xrot_ewq(double x[9], int32_t ix0, int32_t iy0, double c, double s);
static void svd_e(const double A[9], double U[9], double s[3], double V[9]);
static double xnrm2_ewqsyl(int32_t n, const double x[18], int32_t ix0);
const msg_ctrl_states sensor_fusion_rtZmsg_ctrl_state = { { 0ULL/* timestamp_ns */
  },                                   /* header */

  { 0.0,                               /* x */
    0.0                                /* y */
  }                                    /* velocity */
};

/* Output and update for Simulink Function: '<S2>/Simulink Function3' */
static void stateTransitionFcn(const double rtu_x[3], const double rtu_w[3],
  double rty_xNext[3])
{
  double tmp[3];
  double rtb_Add_idx_0;
  double rtb_Add_idx_1;
  double rtb_Add_idx_2;
  double tmp_0;
  int32_t i;

  /* SignalConversion generated from: '<S5>/u' incorporates:
   *  Inport generated from: '<Root>/imu'
   *  SignalConversion generated from: '<S5>/w'
   *  Sum: '<S5>/Add2'
   */
  tmp[0] = sensor_fusion_U.imu.accel.x + rtu_w[0];
  tmp[1] = sensor_fusion_U.imu.accel.y + rtu_w[1];
  tmp[2] = sensor_fusion_U.imu.gyro.z + rtu_w[2];

  /* Product: '<S5>/Matrix Multiply' incorporates:
   *  Constant: '<S5>/G'
   */
  rtb_Add_idx_0 = 0.0;
  rtb_Add_idx_1 = 0.0;
  rtb_Add_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    tmp_0 = tmp[i];
    rtb_Add_idx_0 += rtCP_G_Value[3 * i] * tmp_0;
    rtb_Add_idx_1 += rtCP_G_Value[3 * i + 1] * tmp_0;
    rtb_Add_idx_2 += rtCP_G_Value[3 * i + 2] * tmp_0;
  }

  /* End of Product: '<S5>/Matrix Multiply' */

  /* SignalConversion generated from: '<S5>/xNext' incorporates:
   *  MATLAB Function: '<S5>/MATLAB Function1'
   *  MATLAB Function: '<S5>/MATLAB Function3'
   *  SignalConversion generated from: '<S5>/x'
   *  Sum: '<S5>/Add'
   */
  rty_xNext[0] = (0.01 * rtu_x[1] * rtu_x[2] + rtu_x[0]) + rtb_Add_idx_0;
  rty_xNext[1] = (rtu_x[1] - 0.01 * rtu_x[0] * rtu_x[2]) + rtb_Add_idx_1;
  rty_xNext[2] = rtb_Add_idx_2;
}

/* Output and update for Simulink Function: '<S2>/Simulink Function4' */
static void MeasurmentFcn(const double rtu_x[3], const double rtu_v[4], double
  rty_y[4])
{
  double tmp_0[12];
  double rtu_x_0;
  double rtu_x_1;
  double rtu_x_2;
  double tmp;
  int32_t i;

  /* MATLAB Function: '<S6>/MATLAB Function' incorporates:
   *  Constant: '<S6>/Constant3'
   *  Constant: '<S6>/Constant4'
   *  Constant: '<S6>/Constant5'
   *  SignalConversion generated from: '<S6>/thetaL'
   *  SignalConversion generated from: '<S6>/thetaR'
   */
  rtu_x_0 = cos(sensor_fusion_DW_l.steer_angle_L);
  rtu_x_1 = sin(sensor_fusion_DW_l.steer_angle_L);
  rtu_x_2 = cos(sensor_fusion_DW_l.steer_angle_R);
  tmp = sin(sensor_fusion_DW_l.steer_angle_R);
  tmp_0[0] = rtu_x_0;
  tmp_0[4] = rtu_x_1;
  tmp_0[8] = -0.62 * rtu_x_0 + 0.928 * rtu_x_1;
  tmp_0[1] = rtu_x_2;
  tmp_0[5] = tmp;
  tmp_0[9] = 0.62 * rtu_x_2 + 0.928 * tmp;
  tmp_0[2] = 1.0;
  tmp_0[6] = 0.0;
  tmp_0[10] = -0.62;
  tmp_0[3] = 1.0;
  tmp_0[7] = 0.0;
  tmp_0[11] = 0.62;

  /* SignalConversion generated from: '<S6>/x' incorporates:
   *  Product: '<S6>/Matrix Multiply'
   */
  rtu_x_0 = rtu_x[1];
  rtu_x_1 = rtu_x[0];
  rtu_x_2 = rtu_x[2];

  /* SignalConversion generated from: '<S6>/y' incorporates:
   *  Product: '<S6>/Matrix Multiply'
   *  SignalConversion generated from: '<S6>/v'
   *  SignalConversion generated from: '<S6>/x'
   *  Sum: '<S6>/Add'
   */
  for (i = 0; i < 4; i++) {
    rty_y[i] = ((tmp_0[i + 4] * rtu_x_0 + tmp_0[i] * rtu_x_1) + tmp_0[i + 8] *
                rtu_x_2) + rtu_v[i];
  }

  /* End of SignalConversion generated from: '<S6>/y' */
}

/* Output and update for Simulink Function: '<S2>/Simulink Function5' */
static void stateTransitionJacobianFcn(const double rtu_x[3], const double
  rtu_w[3], double rty_A[9], double rty_G[9])
{
  UNUSED_PARAMETER(rtu_w);

  /* SignalConversion generated from: '<S7>/G~' incorporates:
   *  Constant: '<S7>/G'
   */
  memcpy(&rty_G[0], &rtCP_G_Value_p[0], 9U * sizeof(double));

  /* SignalConversion generated from: '<S7>/A' incorporates:
   *  MATLAB Function: '<S7>/MATLAB Function3'
   *  SignalConversion generated from: '<S7>/x'
   */
  rty_A[0] = 1.0;
  rty_A[3] = 0.01 * rtu_x[2] / 2.0;
  rty_A[6] = 0.01 * rtu_x[1] / 2.0;
  rty_A[1] = -0.01 * rtu_x[2] / 2.0;
  rty_A[4] = 1.0;
  rty_A[7] = -0.01 * rtu_x[0] / 2.0;
  rty_A[2] = 0.0;
  rty_A[5] = 0.0;
  rty_A[8] = 0.0;
}

static double xzlangeM(const double x[16])
{
  double y;
  int32_t b_k;
  bool exitg1;
  y = 0.0;
  b_k = 0;
  exitg1 = false;
  while ((!exitg1) && (b_k < 16)) {
    double absxk;
    absxk = fabs(x[b_k]);
    if (rtIsNaN(absxk)) {
      y = (rtNaN);
      exitg1 = true;
    } else {
      if (absxk > y) {
        y = absxk;
      }

      b_k++;
    }
  }

  return y;
}

static void xzlascl(double cfrom, double cto, double A[16])
{
  double cfromc;
  double ctoc;
  int32_t b_j;
  bool notdone;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    double cfrom1;
    double cto1;
    double mul;
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    for (b_j = 0; b_j < 4; b_j++) {
      int32_t offset;
      offset = (b_j << 2) - 1;
      A[offset + 1] *= mul;
      A[offset + 2] *= mul;
      A[offset + 3] *= mul;
      A[offset + 4] *= mul;
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
}

static double xnrm2(int32_t n, const double x[16], int32_t ix0)
{
  double scale;
  double y;
  int32_t k;
  int32_t kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
  return scale * sqrt(y);
}

static double xdotc(int32_t n, const double x[16], int32_t ix0, const double y
                    [16], int32_t iy0)
{
  double d;
  int32_t b;
  int32_t k;
  d = 0.0;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  b = (uint8_t)n;
  for (k = 0; k < b; k++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    d += x[(ix0 + k) - 1] * y[(iy0 + k) - 1];
  }

  return d;
}

static void xaxpy(int32_t n, double a, int32_t ix0, double y[16], int32_t iy0)
{
  int32_t k;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  if (!(a == 0.0)) {
    for (k = 0; k < n; k++) {
      int32_t tmp;
      tmp = (iy0 + k) - 1;
      y[tmp] += y[(ix0 + k) - 1] * a;
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
}

static double xnrm2_e(int32_t n, const double x[4], int32_t ix0)
{
  double scale;
  double y;
  int32_t k;
  int32_t kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
  return scale * sqrt(y);
}

static void xaxpy_e(int32_t n, double a, const double x[16], int32_t ix0, double
                    y[4], int32_t iy0)
{
  int32_t k;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  if (!(a == 0.0)) {
    for (k = 0; k < n; k++) {
      int32_t tmp;
      tmp = (iy0 + k) - 1;
      y[tmp] += x[(ix0 + k) - 1] * a;
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
}

static void xaxpy_ew(int32_t n, double a, const double x[4], int32_t ix0, double
                     y[16], int32_t iy0)
{
  int32_t k;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  if (!(a == 0.0)) {
    for (k = 0; k < n; k++) {
      int32_t tmp;
      tmp = (iy0 + k) - 1;
      y[tmp] += x[(ix0 + k) - 1] * a;
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
}

static void xzlascl_e(double cfrom, double cto, double A[4])
{
  double cfromc;
  double ctoc;
  bool notdone;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    double cfrom1;
    double cto1;
    double mul;
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    A[0] *= mul;
    A[1] *= mul;
    A[2] *= mul;
    A[3] *= mul;
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
}

static void xswap_ew(double x[16], int32_t ix0, int32_t iy0)
{
  double temp;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  temp = x[ix0 - 1];
  x[ix0 - 1] = x[iy0 - 1];
  x[iy0 - 1] = temp;
  temp = x[ix0];
  x[ix0] = x[iy0];
  x[iy0] = temp;
  temp = x[ix0 + 1];
  x[ix0 + 1] = x[iy0 + 1];
  x[iy0 + 1] = temp;
  temp = x[ix0 + 2];
  x[ix0 + 2] = x[iy0 + 2];
  x[iy0 + 2] = temp;
}

static void xrotg(double a, double b, double *b_a, double *b_b, double *c,
                  double *s)
{
  double absa;
  double absb;
  double roe;
  double scale;

  /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
   *  MATLABSystem: '<S14>/MATLAB System'
   */
  roe = b;
  absa = fabs(a);
  absb = fabs(b);
  if (absa > absb) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
     *  MATLABSystem: '<S14>/MATLAB System'
     */
    roe = a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    *b_a = 0.0;
    *b_b = 0.0;
  } else {
    double ads;
    double bds;
    ads = absa / scale;
    bds = absb / scale;

    /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
     *  MATLABSystem: '<S14>/MATLAB System'
     */
    *b_a = sqrt(ads * ads + bds * bds) * scale;
    if (roe < 0.0) {
      *b_a = -*b_a;
    }

    /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
     *  MATLABSystem: '<S14>/MATLAB System'
     */
    *c = a / *b_a;
    *s = b / *b_a;
    if (absa > absb) {
      *b_b = *s;
    } else if (*c != 0.0) {
      /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
       *  MATLABSystem: '<S14>/MATLAB System'
       */
      *b_b = 1.0 / *c;
    } else {
      *b_b = 1.0;
    }
  }
}

static void xrot_ew(double x[16], int32_t ix0, int32_t iy0, double c, double s)
{
  double temp;
  double temp_tmp;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  temp = x[iy0 - 1];
  temp_tmp = x[ix0 - 1];
  x[iy0 - 1] = temp * c - temp_tmp * s;
  x[ix0 - 1] = temp_tmp * c + temp * s;
  temp = x[ix0] * c + x[iy0] * s;
  x[iy0] = x[iy0] * c - x[ix0] * s;
  x[ix0] = temp;
  temp = x[iy0 + 1];
  temp_tmp = x[ix0 + 1];
  x[iy0 + 1] = temp * c - temp_tmp * s;
  x[ix0 + 1] = temp_tmp * c + temp * s;
  temp = x[iy0 + 2];
  temp_tmp = x[ix0 + 2];
  x[iy0 + 2] = temp * c - temp_tmp * s;
  x[ix0 + 2] = temp_tmp * c + temp * s;
}

static void svd(const double A[16], double U[16], double s[4], double V[16])
{
  double A_0[16];
  double e[4];
  double s_0[4];
  double work[4];
  double anrm;
  double cscale;
  double emm1;
  double nrm;
  double rt;
  double shift;
  double smm1;
  double sqds;
  double ztest;
  double ztest0;
  double ztest0_tmp;
  int32_t colqp1;
  int32_t m;
  int32_t qjj;
  int32_t qp1;
  int32_t qp1jj;
  int32_t qq;
  int32_t qq_tmp;
  bool apply_transform;
  bool doscale;
  bool exitg1;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  s_0[0] = 0.0;
  e[0] = 0.0;
  work[0] = 0.0;
  s_0[1] = 0.0;
  e[1] = 0.0;
  work[1] = 0.0;
  s_0[2] = 0.0;
  e[2] = 0.0;
  work[2] = 0.0;
  s_0[3] = 0.0;
  e[3] = 0.0;
  work[3] = 0.0;
  for (qq_tmp = 0; qq_tmp < 16; qq_tmp++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    A_0[qq_tmp] = A[qq_tmp];
    U[qq_tmp] = 0.0;
    V[qq_tmp] = 0.0;
  }

  doscale = false;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  anrm = xzlangeM(A);
  cscale = anrm;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
    doscale = true;
    cscale = 6.7178761075670888E-139;
    xzlascl(anrm, cscale, A_0);
  } else if (anrm > 1.4885657073574029E+138) {
    doscale = true;
    cscale = 1.4885657073574029E+138;
    xzlascl(anrm, cscale, A_0);
  }

  for (m = 0; m < 3; m++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    qp1 = m + 2;
    colqp1 = m << 2;

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    qq_tmp = colqp1 + m;
    qq = qq_tmp + 1;
    apply_transform = false;

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    nrm = xnrm2(4 - m, A_0, qq_tmp + 1);
    if (nrm > 0.0) {
      apply_transform = true;

      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      if (A_0[qq_tmp] < 0.0) {
        nrm = -nrm;
      }

      s_0[m] = nrm;

      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      if (fabs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qp1jj = (qq_tmp - m) + 1;
        for (qjj = qq; qjj <= qp1jj + 3; qjj++) {
          A_0[qjj - 1] *= nrm;
        }
      } else {
        qp1jj = (qq_tmp - m) + 1;
        for (qjj = qq; qjj <= qp1jj + 3; qjj++) {
          A_0[qjj - 1] /= s_0[m];
        }
      }

      A_0[qq_tmp]++;
      s_0[m] = -s_0[m];
    } else {
      s_0[m] = 0.0;
    }

    for (qp1jj = qp1; qp1jj < 5; qp1jj++) {
      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      qjj = (((qp1jj - 1) << 2) + m) + 1;
      if (apply_transform) {
        /* Start for MATLABSystem: '<S12>/MATLAB System' */
        xaxpy(4 - m, -(xdotc(4 - m, A_0, qq_tmp + 1, A_0, qjj) / A_0[qq_tmp]),
              qq_tmp + 1, A_0, qjj);
      }

      e[qp1jj - 1] = A_0[qjj - 1];
    }

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    for (qq = m + 1; qq < 5; qq++) {
      qp1jj = (colqp1 + qq) - 1;
      U[qp1jj] = A_0[qp1jj];
    }

    if (m + 1 <= 2) {
      nrm = xnrm2_e(3 - m, e, m + 2);
      if (nrm == 0.0) {
        e[m] = 0.0;
      } else {
        if (e[m + 1] < 0.0) {
          e[m] = -nrm;
        } else {
          e[m] = nrm;
        }

        nrm = e[m];
        if (fabs(e[m]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[m];
          for (qjj = qp1; qjj < 5; qjj++) {
            e[qjj - 1] *= nrm;
          }
        } else {
          for (qjj = qp1; qjj < 5; qjj++) {
            e[qjj - 1] /= nrm;
          }
        }

        e[m + 1]++;
        e[m] = -e[m];
        for (qq = qp1; qq < 5; qq++) {
          work[qq - 1] = 0.0;
        }

        for (qq = qp1; qq < 5; qq++) {
          xaxpy_e(3 - m, e[qq - 1], A_0, (m + ((qq - 1) << 2)) + 2, work, m + 2);
        }

        for (qq = qp1; qq < 5; qq++) {
          xaxpy_ew(3 - m, -e[qq - 1] / e[m + 1], work, m + 2, A_0, (m + ((qq - 1)
                     << 2)) + 2);
        }
      }

      for (qq = qp1; qq < 5; qq++) {
        V[(qq + colqp1) - 1] = e[qq - 1];
      }
    }
  }

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  m = 3;
  s_0[3] = A_0[15];
  e[2] = A_0[14];
  e[3] = 0.0;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  U[12] = 0.0;
  U[13] = 0.0;
  U[14] = 0.0;
  U[15] = 1.0;
  for (colqp1 = 2; colqp1 >= 0; colqp1--) {
    qq_tmp = colqp1 << 2;
    qq = qq_tmp + colqp1;
    if (s_0[colqp1] != 0.0) {
      for (qp1jj = colqp1 + 2; qp1jj < 5; qp1jj++) {
        qjj = (((qp1jj - 1) << 2) + colqp1) + 1;

        /* Start for MATLABSystem: '<S12>/MATLAB System' */
        xaxpy(4 - colqp1, -(xdotc(4 - colqp1, U, qq + 1, U, qjj) / U[qq]), qq +
              1, U, qjj);
      }

      for (qp1 = colqp1 + 1; qp1 < 5; qp1++) {
        qp1jj = (qq_tmp + qp1) - 1;
        U[qp1jj] = -U[qp1jj];
      }

      U[qq]++;

      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      for (qq = 0; qq < colqp1; qq++) {
        U[qq + qq_tmp] = 0.0;
      }
    } else {
      U[qq_tmp] = 0.0;

      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      U[qq_tmp + 1] = 0.0;
      U[qq_tmp + 2] = 0.0;
      U[qq_tmp + 3] = 0.0;
      U[qq] = 1.0;
    }
  }

  for (colqp1 = 3; colqp1 >= 0; colqp1--) {
    if ((colqp1 + 1 <= 2) && (e[colqp1] != 0.0)) {
      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      qq = ((colqp1 << 2) + colqp1) + 2;
      for (qjj = colqp1 + 2; qjj < 5; qjj++) {
        /* Start for MATLABSystem: '<S12>/MATLAB System' */
        qp1jj = (((qjj - 1) << 2) + colqp1) + 2;
        xaxpy(3 - colqp1, -(xdotc(3 - colqp1, V, qq, V, qp1jj) / V[qq - 1]), qq,
              V, qp1jj);
      }
    }

    qp1 = colqp1 << 2;
    V[qp1] = 0.0;

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    V[qp1 + 1] = 0.0;
    V[qp1 + 2] = 0.0;
    V[qp1 + 3] = 0.0;
    V[colqp1 + qp1] = 1.0;
  }

  for (qp1 = 0; qp1 < 4; qp1++) {
    nrm = s_0[qp1];
    if (nrm != 0.0) {
      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      rt = fabs(nrm);
      nrm /= rt;
      s_0[qp1] = rt;

      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      if (qp1 + 1 < 4) {
        e[qp1] /= nrm;
      }

      qq = qp1 << 2;

      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      for (qjj = qq + 1; qjj <= qq + 4; qjj++) {
        U[qjj - 1] *= nrm;
      }
    }

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    if (qp1 + 1 < 4) {
      emm1 = e[qp1];
      if (emm1 != 0.0) {
        rt = fabs(emm1);
        nrm = rt / emm1;
        e[qp1] = rt;
        s_0[qp1 + 1] *= nrm;
        colqp1 = (qp1 + 1) << 2;
        for (qjj = colqp1 + 1; qjj <= colqp1 + 4; qjj++) {
          V[qjj - 1] *= nrm;
        }
      }
    }
  }

  rt = 0.0;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  nrm = fmax(fmax(fmax(fmax(0.0, fmax(fabs(s_0[0]), fabs(e[0]))), fmax(fabs(s_0
    [1]), fabs(e[1]))), fmax(fabs(s_0[2]), fabs(e[2]))), fmax(fabs(s_0[3]), fabs
              (e[3])));
  while ((m + 1 > 0) && (!(rt >= 75.0))) {
    colqp1 = m;
    qp1 = m;
    exitg1 = false;
    while ((!exitg1) && (qp1 > -1)) {
      colqp1 = qp1;
      if (qp1 == 0) {
        exitg1 = true;
      } else {
        ztest0 = fabs(e[qp1 - 1]);
        if ((ztest0 <= (fabs(s_0[qp1 - 1]) + fabs(s_0[qp1])) *
             2.2204460492503131E-16) || ((ztest0 <= 1.0020841800044864E-292) ||
             ((rt > 20.0) && (ztest0 <= 2.2204460492503131E-16 * nrm)))) {
          e[qp1 - 1] = 0.0;
          exitg1 = true;
        } else {
          qp1--;
        }
      }
    }

    if (colqp1 == m) {
      ztest0 = 4.0;
    } else {
      qp1 = m + 1;
      qq = m + 1;
      exitg1 = false;
      while ((!exitg1) && (qq >= colqp1)) {
        qp1 = qq;
        if (qq == colqp1) {
          exitg1 = true;
        } else {
          ztest0 = 0.0;
          if (qq < m + 1) {
            ztest0 = fabs(e[qq - 1]);
          }

          if (qq > colqp1 + 1) {
            ztest0 += fabs(e[qq - 2]);
          }

          ztest = fabs(s_0[qq - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s_0[qq - 1] = 0.0;
            exitg1 = true;
          } else {
            qq--;
          }
        }
      }

      if (qp1 == colqp1) {
        ztest0 = 3.0;
      } else if (m + 1 == qp1) {
        ztest0 = 1.0;
      } else {
        ztest0 = 2.0;
        colqp1 = qp1;
      }
    }

    switch ((int32_t)ztest0) {
     case 1:
      ztest0 = e[m - 1];
      e[m - 1] = 0.0;
      for (qq = m; qq >= colqp1 + 1; qq--) {
        xrotg(s_0[qq - 1], ztest0, &s_0[qq - 1], &ztest0, &ztest, &sqds);
        if (qq > colqp1 + 1) {
          emm1 = e[qq - 2];
          ztest0 = -sqds * emm1;
          e[qq - 2] = emm1 * ztest;
        }

        xrot_ew(V, ((qq - 1) << 2) + 1, (m << 2) + 1, ztest, sqds);
      }
      break;

     case 2:
      ztest0 = e[colqp1 - 1];
      e[colqp1 - 1] = 0.0;
      for (qp1 = colqp1 + 1; qp1 <= m + 1; qp1++) {
        xrotg(s_0[qp1 - 1], ztest0, &s_0[qp1 - 1], &ztest, &sqds, &smm1);
        emm1 = e[qp1 - 1];
        ztest0 = -smm1 * emm1;
        e[qp1 - 1] = emm1 * sqds;
        xrot_ew(U, ((qp1 - 1) << 2) + 1, ((colqp1 - 1) << 2) + 1, sqds, smm1);
      }
      break;

     case 3:
      smm1 = s_0[m - 1];
      sqds = e[m - 1];
      ztest = fmax(fmax(fmax(fmax(fabs(s_0[m]), fabs(smm1)), fabs(sqds)), fabs
                        (s_0[colqp1])), fabs(e[colqp1]));
      ztest0 = s_0[m] / ztest;
      smm1 /= ztest;
      emm1 = sqds / ztest;
      sqds = s_0[colqp1] / ztest;
      smm1 = ((smm1 + ztest0) * (smm1 - ztest0) + emm1 * emm1) / 2.0;
      emm1 *= ztest0;
      emm1 *= emm1;
      if ((smm1 != 0.0) || (emm1 != 0.0)) {
        shift = sqrt(smm1 * smm1 + emm1);
        if (smm1 < 0.0) {
          shift = -shift;
        }

        shift = emm1 / (smm1 + shift);
      } else {
        shift = 0.0;
      }

      ztest0 = (sqds + ztest0) * (sqds - ztest0) + shift;
      ztest = e[colqp1] / ztest * sqds;
      for (qq = colqp1 + 1; qq <= m; qq++) {
        xrotg(ztest0, ztest, &sqds, &smm1, &emm1, &shift);
        if (qq > colqp1 + 1) {
          e[qq - 2] = sqds;
        }

        ztest0_tmp = e[qq - 1];
        ztest0 = s_0[qq - 1];
        e[qq - 1] = ztest0_tmp * emm1 - ztest0 * shift;
        ztest = shift * s_0[qq];
        s_0[qq] *= emm1;
        qq_tmp = ((qq - 1) << 2) + 1;
        qp1jj = (qq << 2) + 1;
        xrot_ew(V, qq_tmp, qp1jj, emm1, shift);
        xrotg(ztest0 * emm1 + ztest0_tmp * shift, ztest, &s_0[qq - 1], &sqds,
              &smm1, &emm1);
        ztest0_tmp = e[qq - 1];
        ztest0 = ztest0_tmp * smm1 + emm1 * s_0[qq];
        s_0[qq] = ztest0_tmp * -emm1 + smm1 * s_0[qq];
        ztest = emm1 * e[qq];
        e[qq] *= smm1;
        xrot_ew(U, qq_tmp, qp1jj, smm1, emm1);
      }

      e[m - 1] = ztest0;
      rt++;
      break;

     default:
      if (s_0[colqp1] < 0.0) {
        s_0[colqp1] = -s_0[colqp1];
        qq = colqp1 << 2;
        for (qjj = qq + 1; qjj <= qq + 4; qjj++) {
          V[qjj - 1] = -V[qjj - 1];
        }
      }

      qp1 = colqp1 + 1;
      while ((colqp1 + 1 < 4) && (s_0[colqp1] < s_0[qp1])) {
        rt = s_0[colqp1];
        s_0[colqp1] = s_0[qp1];
        s_0[qp1] = rt;
        qq_tmp = (colqp1 << 2) + 1;
        qp1jj = ((colqp1 + 1) << 2) + 1;
        xswap_ew(V, qq_tmp, qp1jj);
        xswap_ew(U, qq_tmp, qp1jj);
        colqp1 = qp1;
        qp1++;
      }

      rt = 0.0;
      m--;
      break;
    }
  }

  s[0] = s_0[0];
  s[1] = s_0[1];
  s[2] = s_0[2];
  s[3] = s_0[3];
  if (doscale) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    xzlascl_e(cscale, anrm, s);
  }
}

static double xnrm2_ew(int32_t n, const double x[28], int32_t ix0)
{
  double scale;
  double y;
  int32_t k;
  int32_t kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
  return scale * sqrt(y);
}

static void EKFCorrectorNonAdditive_getMeas(const double Rs[16], const double x
  [3], const double S[9], double zEstimated[4], double Pxy[12], double Sy[16],
  double dhdx[12], double Rsqrt[16])
{
  double c_A[28];
  double dhdv[16];
  double Pxy_tmp[12];
  double y_tmp_0[12];
  double S_0[9];
  double y_tmp[9];
  double imz[4];
  double v_tmp[4];
  double z[4];
  double imvec[3];
  double epsilon;
  double x_0;
  double xnorm;
  double z_0;
  double z_1;
  double z_2;
  int32_t Pxy_tmp_0;
  int32_t coltop;
  int32_t dhdx_tmp;
  int32_t e;
  int32_t exitg1;
  int32_t ii;
  int32_t jy;
  int32_t knt;
  int32_t lastc;
  int32_t lastv;
  bool exitg2;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  v_tmp[0] = 0.0;
  v_tmp[1] = 0.0;
  v_tmp[2] = 0.0;
  v_tmp[3] = 0.0;
  MeasurmentFcn(x, v_tmp, z);
  xnorm = z[0];
  z_0 = z[1];
  z_1 = z[2];
  z_2 = z[3];
  for (ii = 0; ii < 3; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    imvec[0] = x[0];
    imvec[1] = x[1];
    imvec[2] = x[2];
    x_0 = x[ii];
    epsilon = fmax(1.4901161193847656E-8, 1.4901161193847656E-8 * fabs(x_0));
    imvec[ii] = x_0 + epsilon;
    MeasurmentFcn(imvec, v_tmp, imz);
    dhdx_tmp = ii << 2;
    dhdx[dhdx_tmp] = (imz[0] - xnorm) / epsilon;
    dhdx[dhdx_tmp + 1] = (imz[1] - z_0) / epsilon;
    dhdx[dhdx_tmp + 2] = (imz[2] - z_1) / epsilon;
    dhdx[dhdx_tmp + 3] = (imz[3] - z_2) / epsilon;
  }

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  MeasurmentFcn(x, v_tmp, z);
  xnorm = z[0];
  z_0 = z[1];
  z_1 = z[2];
  z_2 = z[3];
  for (ii = 0; ii < 4; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    z[0] = 0.0;
    z[1] = 0.0;
    z[2] = 0.0;
    z[3] = 0.0;
    z[ii] = 1.4901161193847656E-8;
    MeasurmentFcn(x, z, imz);
    dhdx_tmp = ii << 2;
    dhdv[dhdx_tmp] = (imz[0] - xnorm) / 1.4901161193847656E-8;
    dhdv[dhdx_tmp + 1] = (imz[1] - z_0) / 1.4901161193847656E-8;
    dhdv[dhdx_tmp + 2] = (imz[2] - z_1) / 1.4901161193847656E-8;
    dhdv[dhdx_tmp + 3] = (imz[3] - z_2) / 1.4901161193847656E-8;
  }

  for (ii = 0; ii < 4; ii++) {
    xnorm = 0.0;
    z_0 = 0.0;
    z_1 = 0.0;
    z_2 = 0.0;
    for (Pxy_tmp_0 = 0; Pxy_tmp_0 < 4; Pxy_tmp_0++) {
      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      epsilon = Rs[(ii << 2) + Pxy_tmp_0];
      dhdx_tmp = Pxy_tmp_0 << 2;
      xnorm += dhdv[dhdx_tmp] * epsilon;
      z_0 += dhdv[dhdx_tmp + 1] * epsilon;
      z_1 += dhdv[dhdx_tmp + 2] * epsilon;
      z_2 += dhdv[dhdx_tmp + 3] * epsilon;
    }

    dhdx_tmp = ii << 2;
    Rsqrt[dhdx_tmp + 3] = z_2;
    Rsqrt[dhdx_tmp + 2] = z_1;
    Rsqrt[dhdx_tmp + 1] = z_0;
    Rsqrt[dhdx_tmp] = xnorm;
  }

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  MeasurmentFcn(x, v_tmp, zEstimated);
  for (ii = 0; ii < 3; ii++) {
    y_tmp[3 * ii] = S[ii];
    y_tmp[3 * ii + 1] = S[ii + 3];
    y_tmp[3 * ii + 2] = S[ii + 6];
  }

  for (ii = 0; ii < 4; ii++) {
    Pxy_tmp[3 * ii] = dhdx[ii];
    Pxy_tmp[3 * ii + 1] = dhdx[ii + 4];
    Pxy_tmp[3 * ii + 2] = dhdx[ii + 8];
  }

  for (ii = 0; ii < 3; ii++) {
    xnorm = 0.0;
    z_0 = 0.0;
    z_1 = 0.0;
    for (Pxy_tmp_0 = 0; Pxy_tmp_0 < 3; Pxy_tmp_0++) {
      epsilon = y_tmp[3 * ii + Pxy_tmp_0];
      xnorm += S[3 * Pxy_tmp_0] * epsilon;
      z_0 += S[3 * Pxy_tmp_0 + 1] * epsilon;
      z_1 += S[3 * Pxy_tmp_0 + 2] * epsilon;
    }

    S_0[3 * ii + 2] = z_1;
    S_0[3 * ii + 1] = z_0;
    S_0[3 * ii] = xnorm;
  }

  for (dhdx_tmp = 0; dhdx_tmp < 4; dhdx_tmp++) {
    z[dhdx_tmp] = 0.0;
    xnorm = 0.0;
    z_0 = 0.0;
    z_1 = 0.0;
    for (ii = 0; ii < 3; ii++) {
      Pxy_tmp_0 = 3 * dhdx_tmp + ii;
      epsilon = Pxy_tmp[Pxy_tmp_0];
      xnorm += S_0[3 * ii] * epsilon;
      z_0 += S_0[3 * ii + 1] * epsilon;
      z_1 += S_0[3 * ii + 2] * epsilon;
      y_tmp_0[Pxy_tmp_0] = 0.0;
    }

    Pxy_tmp_0 = 3 * dhdx_tmp + 2;
    Pxy[Pxy_tmp_0] = z_1;
    lastv = 3 * dhdx_tmp + 1;
    Pxy[lastv] = z_0;
    Pxy[3 * dhdx_tmp] = xnorm;
    xnorm = y_tmp_0[3 * dhdx_tmp];
    z_0 = y_tmp_0[lastv];
    z_1 = y_tmp_0[Pxy_tmp_0];
    for (ii = 0; ii < 3; ii++) {
      epsilon = Pxy_tmp[3 * dhdx_tmp + ii];
      xnorm += y_tmp[3 * ii] * epsilon;
      z_0 += y_tmp[3 * ii + 1] * epsilon;
      z_1 += y_tmp[3 * ii + 2] * epsilon;
    }

    y_tmp_0[Pxy_tmp_0] = z_1;
    y_tmp_0[lastv] = z_0;
    y_tmp_0[3 * dhdx_tmp] = xnorm;
    c_A[7 * dhdx_tmp] = xnorm;
    c_A[7 * dhdx_tmp + 1] = z_0;
    c_A[7 * dhdx_tmp + 2] = z_1;
    c_A[7 * dhdx_tmp + 3] = Rsqrt[dhdx_tmp];
    c_A[7 * dhdx_tmp + 4] = Rsqrt[dhdx_tmp + 4];
    c_A[7 * dhdx_tmp + 5] = Rsqrt[dhdx_tmp + 8];
    c_A[7 * dhdx_tmp + 6] = Rsqrt[dhdx_tmp + 12];
    imz[dhdx_tmp] = 0.0;
  }

  for (Pxy_tmp_0 = 0; Pxy_tmp_0 < 4; Pxy_tmp_0++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    ii = Pxy_tmp_0 * 7 + Pxy_tmp_0;
    lastv = ii + 2;
    epsilon = c_A[ii];
    z[Pxy_tmp_0] = 0.0;

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    xnorm = xnrm2_ew(6 - Pxy_tmp_0, c_A, ii + 2);
    if (xnorm != 0.0) {
      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      z_0 = c_A[ii];
      xnorm = rt_hypotd_snf(z_0, xnorm);
      if (z_0 >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = -1;
        do {
          knt++;
          dhdx_tmp = ii - Pxy_tmp_0;
          for (coltop = lastv; coltop <= dhdx_tmp + 7; coltop++) {
            c_A[coltop - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          epsilon *= 9.9792015476736E+291;
        } while ((fabs(xnorm) < 1.0020841800044864E-292) && (knt + 1 < 20));

        xnorm = rt_hypotd_snf(epsilon, xnrm2_ew(6 - Pxy_tmp_0, c_A, ii + 2));
        if (epsilon >= 0.0) {
          xnorm = -xnorm;
        }

        z[Pxy_tmp_0] = (xnorm - epsilon) / xnorm;
        epsilon = 1.0 / (epsilon - xnorm);
        for (coltop = lastv; coltop <= dhdx_tmp + 7; coltop++) {
          c_A[coltop - 1] *= epsilon;
        }

        for (coltop = 0; coltop <= knt; coltop++) {
          xnorm *= 1.0020841800044864E-292;
        }

        epsilon = xnorm;
      } else {
        z[Pxy_tmp_0] = (xnorm - z_0) / xnorm;
        epsilon = 1.0 / (z_0 - xnorm);
        dhdx_tmp = ii - Pxy_tmp_0;
        for (coltop = lastv; coltop <= dhdx_tmp + 7; coltop++) {
          c_A[coltop - 1] *= epsilon;
        }

        epsilon = xnorm;
      }
    }

    c_A[ii] = epsilon;

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    if (Pxy_tmp_0 + 1 < 4) {
      c_A[ii] = 1.0;
      knt = ii + 8;
      if (z[Pxy_tmp_0] != 0.0) {
        lastv = 7 - Pxy_tmp_0;
        dhdx_tmp = ii - Pxy_tmp_0;
        while ((lastv > 0) && (c_A[dhdx_tmp + 6] == 0.0)) {
          lastv--;
          dhdx_tmp--;
        }

        lastc = 3 - Pxy_tmp_0;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          coltop = (lastc - 1) * 7 + ii;
          dhdx_tmp = coltop + 8;
          do {
            exitg1 = 0;
            if (dhdx_tmp <= (coltop + lastv) + 7) {
              if (c_A[dhdx_tmp - 1] != 0.0) {
                exitg1 = 1;
              } else {
                dhdx_tmp++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }

      if (lastv > 0) {
        if (lastc != 0) {
          memset(&imz[0], 0, (uint32_t)lastc * sizeof(double));
          coltop = (lastc - 1) * 7 + ii;
          for (jy = knt; jy <= coltop + 8; jy += 7) {
            xnorm = 0.0;
            e = jy + lastv;
            for (dhdx_tmp = jy; dhdx_tmp < e; dhdx_tmp++) {
              xnorm += c_A[(ii + dhdx_tmp) - jy] * c_A[dhdx_tmp - 1];
            }

            dhdx_tmp = div_nde_s32_floor((jy - ii) - 8, 7);
            imz[dhdx_tmp] += xnorm;
          }
        }

        if (!(-z[Pxy_tmp_0] == 0.0)) {
          jy = ii;
          dhdx_tmp = lastc;
          for (lastc = 0; lastc < dhdx_tmp; lastc++) {
            xnorm = imz[lastc];
            if (xnorm != 0.0) {
              xnorm *= -z[Pxy_tmp_0];
              knt = jy + 8;
              coltop = (lastv + jy) + 7;
              for (e = knt; e <= coltop; e++) {
                c_A[e - 1] += c_A[((ii + e) - jy) - 8] * xnorm;
              }
            }

            jy += 7;
          }
        }
      }

      c_A[ii] = epsilon;
    }
  }

  for (ii = 0; ii < 4; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    memcpy(&dhdv[ii << 2], &c_A[ii * 7], (uint32_t)(ii + 1) * sizeof(double));
    for (Pxy_tmp_0 = ii + 2; Pxy_tmp_0 < 5; Pxy_tmp_0++) {
      dhdv[(Pxy_tmp_0 + (ii << 2)) - 1] = 0.0;
    }
  }

  for (ii = 0; ii < 4; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    dhdx_tmp = ii << 2;
    Sy[dhdx_tmp] = dhdv[ii];
    Sy[dhdx_tmp + 1] = dhdv[ii + 4];
    Sy[dhdx_tmp + 2] = dhdv[ii + 8];
    Sy[dhdx_tmp + 3] = dhdv[ii + 12];
  }
}

static void trisolve(const double A[16], double B[12])
{
  int32_t b_j;
  int32_t b_k;
  int32_t i;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  for (b_j = 0; b_j < 3; b_j++) {
    int32_t jBcol;
    jBcol = (b_j << 2) - 1;
    for (b_k = 0; b_k < 4; b_k++) {
      double B_0;
      int32_t B_tmp;
      int32_t k;
      int32_t kAcol;
      k = b_k + 1;
      kAcol = (b_k << 2) - 1;
      B_tmp = (b_k + jBcol) + 1;
      B_0 = B[B_tmp];
      if (B_0 != 0.0) {
        B[B_tmp] = B_0 / A[(b_k + kAcol) + 1];
        for (i = k + 1; i < 5; i++) {
          int32_t tmp;
          tmp = i + jBcol;
          B[tmp] -= A[i + kAcol] * B[B_tmp];
        }
      }
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
}

static void trisolve_e(const double A[16], double B[12])
{
  int32_t b_i;
  int32_t b_j;
  int32_t k;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  for (b_j = 0; b_j < 3; b_j++) {
    int32_t jBcol;
    jBcol = b_j << 2;
    for (k = 3; k >= 0; k--) {
      double tmp;
      int32_t kAcol;
      int32_t tmp_0;
      kAcol = k << 2;
      tmp_0 = k + jBcol;
      tmp = B[tmp_0];
      if (tmp != 0.0) {
        B[tmp_0] = tmp / A[k + kAcol];
        for (b_i = 0; b_i < k; b_i++) {
          int32_t tmp_1;
          tmp_1 = b_i + jBcol;
          B[tmp_1] -= A[b_i + kAcol] * B[tmp_0];
        }
      }
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
}

static double xnrm2_ewq(int32_t n, const double x[21], int32_t ix0)
{
  double scale;
  double y;
  int32_t k;
  int32_t kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  /* End of Start for MATLABSystem: '<S12>/MATLAB System' */
  return scale * sqrt(y);
}

static void qrFactor(const double A[9], const double S[9], const double Ns[12],
                     double b_S[9])
{
  double c_A[21];
  double b_R[9];
  double b_tau[3];
  double work[3];
  double A_0;
  double b_atmp;
  double xnorm;
  int32_t b_i;
  int32_t coltop;
  int32_t e;
  int32_t exitg1;
  int32_t i;
  int32_t ii;
  int32_t jy;
  int32_t knt;
  int32_t lastc;
  int32_t lastv;
  bool exitg2;

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  for (i = 0; i < 3; i++) {
    b_tau[i] = 0.0;
    b_atmp = A[i + 3];
    xnorm = A[i];
    A_0 = A[i + 6];
    for (b_i = 0; b_i < 3; b_i++) {
      c_A[b_i + 7 * i] = (S[3 * b_i + 1] * b_atmp + S[3 * b_i] * xnorm) + S[3 *
        b_i + 2] * A_0;
    }

    c_A[7 * i + 3] = Ns[i];
    c_A[7 * i + 4] = Ns[i + 3];
    c_A[7 * i + 5] = Ns[i + 6];
    c_A[7 * i + 6] = Ns[i + 9];
    work[i] = 0.0;
  }

  for (b_i = 0; b_i < 3; b_i++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    ii = b_i * 7 + b_i;
    lastv = ii + 2;
    b_atmp = c_A[ii];
    b_tau[b_i] = 0.0;

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    xnorm = xnrm2_ewq(6 - b_i, c_A, ii + 2);
    if (xnorm != 0.0) {
      /* Start for MATLABSystem: '<S12>/MATLAB System' */
      A_0 = c_A[ii];
      xnorm = rt_hypotd_snf(A_0, xnorm);
      if (A_0 >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = -1;
        do {
          knt++;
          i = ii - b_i;
          for (coltop = lastv; coltop <= i + 7; coltop++) {
            c_A[coltop - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          b_atmp *= 9.9792015476736E+291;
        } while ((fabs(xnorm) < 1.0020841800044864E-292) && (knt + 1 < 20));

        xnorm = rt_hypotd_snf(b_atmp, xnrm2_ewq(6 - b_i, c_A, ii + 2));
        if (b_atmp >= 0.0) {
          xnorm = -xnorm;
        }

        b_tau[b_i] = (xnorm - b_atmp) / xnorm;
        b_atmp = 1.0 / (b_atmp - xnorm);
        for (coltop = lastv; coltop <= i + 7; coltop++) {
          c_A[coltop - 1] *= b_atmp;
        }

        for (coltop = 0; coltop <= knt; coltop++) {
          xnorm *= 1.0020841800044864E-292;
        }

        b_atmp = xnorm;
      } else {
        b_tau[b_i] = (xnorm - A_0) / xnorm;
        b_atmp = 1.0 / (A_0 - xnorm);
        i = ii - b_i;
        for (coltop = lastv; coltop <= i + 7; coltop++) {
          c_A[coltop - 1] *= b_atmp;
        }

        b_atmp = xnorm;
      }
    }

    c_A[ii] = b_atmp;

    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    if (b_i + 1 < 3) {
      c_A[ii] = 1.0;
      knt = ii + 8;
      if (b_tau[b_i] != 0.0) {
        lastv = 7 - b_i;
        i = ii - b_i;
        while ((lastv > 0) && (c_A[i + 6] == 0.0)) {
          lastv--;
          i--;
        }

        lastc = 2 - b_i;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          coltop = (lastc - 1) * 7 + ii;
          i = coltop + 8;
          do {
            exitg1 = 0;
            if (i <= (coltop + lastv) + 7) {
              if (c_A[i - 1] != 0.0) {
                exitg1 = 1;
              } else {
                i++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }

      if (lastv > 0) {
        if (lastc != 0) {
          memset(&work[0], 0, (uint32_t)lastc * sizeof(double));
          coltop = (lastc - 1) * 7 + ii;
          for (jy = knt; jy <= coltop + 8; jy += 7) {
            xnorm = 0.0;
            e = jy + lastv;
            for (i = jy; i < e; i++) {
              xnorm += c_A[(ii + i) - jy] * c_A[i - 1];
            }

            i = div_nde_s32_floor((jy - ii) - 8, 7);
            work[i] += xnorm;
          }
        }

        if (!(-b_tau[b_i] == 0.0)) {
          jy = ii;
          i = lastc;
          for (lastc = 0; lastc < i; lastc++) {
            xnorm = work[lastc];
            if (xnorm != 0.0) {
              xnorm *= -b_tau[b_i];
              knt = jy + 8;
              coltop = (lastv + jy) + 7;
              for (e = knt; e <= coltop; e++) {
                c_A[e - 1] += c_A[((ii + e) - jy) - 8] * xnorm;
              }
            }

            jy += 7;
          }
        }
      }

      c_A[ii] = b_atmp;
    }
  }

  for (ii = 0; ii < 3; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    memcpy(&b_R[ii * 3], &c_A[ii * 7], (uint32_t)(ii + 1) * sizeof(double));
    for (b_i = ii + 2; b_i < 4; b_i++) {
      b_R[(b_i + 3 * ii) - 1] = 0.0;
    }
  }

  for (b_i = 0; b_i < 3; b_i++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    b_S[3 * b_i] = b_R[b_i];
    b_S[3 * b_i + 1] = b_R[b_i + 3];
    b_S[3 * b_i + 2] = b_R[b_i + 6];
  }
}

static double xzlangeM_e(const double x[9])
{
  double y;
  int32_t b_k;
  bool exitg1;
  y = 0.0;
  b_k = 0;
  exitg1 = false;
  while ((!exitg1) && (b_k < 9)) {
    double absxk;
    absxk = fabs(x[b_k]);
    if (rtIsNaN(absxk)) {
      y = (rtNaN);
      exitg1 = true;
    } else {
      if (absxk > y) {
        y = absxk;
      }

      b_k++;
    }
  }

  return y;
}

static void xzlascl_ew(double cfrom, double cto, double A[9])
{
  double cfromc;
  double ctoc;
  int32_t b_j;
  bool notdone;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    double cfrom1;
    double cto1;
    double mul;
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    for (b_j = 0; b_j < 3; b_j++) {
      int32_t offset;
      offset = b_j * 3 - 1;
      A[offset + 1] *= mul;
      A[offset + 2] *= mul;
      A[offset + 3] *= mul;
    }
  }

  /* End of Start for MATLABSystem: '<S14>/MATLAB System' */
}

static double xnrm2_ewqs(int32_t n, const double x[9], int32_t ix0)
{
  double scale;
  double y;
  int32_t k;
  int32_t kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  /* End of Start for MATLABSystem: '<S14>/MATLAB System' */
  return scale * sqrt(y);
}

static double xdotc_e(int32_t n, const double x[9], int32_t ix0, const double y
                      [9], int32_t iy0)
{
  double d;
  int32_t b;
  int32_t k;
  d = 0.0;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  b = (uint8_t)n;
  for (k = 0; k < b; k++) {
    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    d += x[(ix0 + k) - 1] * y[(iy0 + k) - 1];
  }

  return d;
}

static void xaxpy_ewq(int32_t n, double a, int32_t ix0, double y[9], int32_t iy0)
{
  int32_t k;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  if (!(a == 0.0)) {
    for (k = 0; k < n; k++) {
      int32_t tmp;
      tmp = (iy0 + k) - 1;
      y[tmp] += y[(ix0 + k) - 1] * a;
    }
  }

  /* End of Start for MATLABSystem: '<S14>/MATLAB System' */
}

static double xnrm2_ewqsy(const double x[3], int32_t ix0)
{
  double scale;
  double y;
  int32_t k;
  y = 0.0;
  scale = 3.3121686421112381E-170;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  for (k = ix0; k <= ix0 + 1; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  /* End of Start for MATLABSystem: '<S14>/MATLAB System' */
  return scale * sqrt(y);
}

static void xaxpy_ewqs(int32_t n, double a, const double x[9], int32_t ix0,
  double y[3], int32_t iy0)
{
  int32_t k;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  if (!(a == 0.0)) {
    for (k = 0; k < n; k++) {
      int32_t tmp;
      tmp = (iy0 + k) - 1;
      y[tmp] += x[(ix0 + k) - 1] * a;
    }
  }

  /* End of Start for MATLABSystem: '<S14>/MATLAB System' */
}

static void xaxpy_ewqsy(int32_t n, double a, const double x[3], int32_t ix0,
  double y[9], int32_t iy0)
{
  int32_t k;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  if (!(a == 0.0)) {
    for (k = 0; k < n; k++) {
      int32_t tmp;
      tmp = (iy0 + k) - 1;
      y[tmp] += x[(ix0 + k) - 1] * a;
    }
  }

  /* End of Start for MATLABSystem: '<S14>/MATLAB System' */
}

static void xzlascl_ewq(double cfrom, double cto, double A[3])
{
  double cfromc;
  double ctoc;
  bool notdone;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    double cfrom1;
    double cto1;
    double mul;
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    A[0] *= mul;
    A[1] *= mul;
    A[2] *= mul;
  }

  /* End of Start for MATLABSystem: '<S14>/MATLAB System' */
}

static void xswap_ewq(double x[9], int32_t ix0, int32_t iy0)
{
  double temp;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  temp = x[ix0 - 1];
  x[ix0 - 1] = x[iy0 - 1];
  x[iy0 - 1] = temp;
  temp = x[ix0];
  x[ix0] = x[iy0];
  x[iy0] = temp;
  temp = x[ix0 + 1];
  x[ix0 + 1] = x[iy0 + 1];
  x[iy0 + 1] = temp;
}

static void xrot_ewq(double x[9], int32_t ix0, int32_t iy0, double c, double s)
{
  double temp;
  double temp_tmp;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  temp = x[iy0 - 1];
  temp_tmp = x[ix0 - 1];
  x[iy0 - 1] = temp * c - temp_tmp * s;
  x[ix0 - 1] = temp_tmp * c + temp * s;
  temp = x[ix0] * c + x[iy0] * s;
  x[iy0] = x[iy0] * c - x[ix0] * s;
  x[ix0] = temp;
  temp = x[iy0 + 1];
  temp_tmp = x[ix0 + 1];
  x[iy0 + 1] = temp * c - temp_tmp * s;
  x[ix0 + 1] = temp_tmp * c + temp * s;
}

static void svd_e(const double A[9], double U[9], double s[3], double V[9])
{
  double A_0[9];
  double e[3];
  double s_0[3];
  double work[3];
  double anrm;
  double cscale;
  double emm1;
  double nrm;
  double rt;
  double shift;
  double smm1;
  double sqds;
  double ztest;
  double ztest0;
  double ztest0_tmp;
  int32_t b;
  int32_t colqp1;
  int32_t m;
  int32_t qjj;
  int32_t qp1;
  int32_t qq;
  bool apply_transform;
  bool doscale;
  bool exitg1;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  s_0[0] = 0.0;
  e[0] = 0.0;
  work[0] = 0.0;
  s_0[1] = 0.0;
  e[1] = 0.0;
  work[1] = 0.0;
  s_0[2] = 0.0;
  e[2] = 0.0;
  work[2] = 0.0;
  for (b = 0; b < 9; b++) {
    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    A_0[b] = A[b];
    U[b] = 0.0;
    V[b] = 0.0;
  }

  doscale = false;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  anrm = xzlangeM_e(A);
  cscale = anrm;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
    doscale = true;
    cscale = 6.7178761075670888E-139;
    xzlascl_ew(anrm, cscale, A_0);
  } else if (anrm > 1.4885657073574029E+138) {
    doscale = true;
    cscale = 1.4885657073574029E+138;
    xzlascl_ew(anrm, cscale, A_0);
  }

  for (m = 0; m < 2; m++) {
    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    qp1 = m + 2;
    colqp1 = 3 * m + m;
    qq = colqp1 + 1;
    apply_transform = false;

    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    nrm = xnrm2_ewqs(3 - m, A_0, colqp1 + 1);
    if (nrm > 0.0) {
      apply_transform = true;

      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      if (A_0[colqp1] < 0.0) {
        nrm = -nrm;
      }

      s_0[m] = nrm;

      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      if (fabs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        b = (colqp1 - m) + 1;
        for (qjj = qq; qjj <= b + 2; qjj++) {
          A_0[qjj - 1] *= nrm;
        }
      } else {
        b = (colqp1 - m) + 1;
        for (qjj = qq; qjj <= b + 2; qjj++) {
          A_0[qjj - 1] /= s_0[m];
        }
      }

      A_0[colqp1]++;
      s_0[m] = -s_0[m];
    } else {
      s_0[m] = 0.0;
    }

    for (b = qp1; b < 4; b++) {
      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      qjj = ((b - 1) * 3 + m) + 1;
      if (apply_transform) {
        /* Start for MATLABSystem: '<S14>/MATLAB System' */
        xaxpy_ewq(3 - m, -(xdotc_e(3 - m, A_0, colqp1 + 1, A_0, qjj) /
                           A_0[colqp1]), colqp1 + 1, A_0, qjj);
      }

      e[b - 1] = A_0[qjj - 1];
    }

    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    for (qq = m + 1; qq < 4; qq++) {
      b = (3 * m + qq) - 1;
      U[b] = A_0[b];
    }

    if (m <= 0) {
      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      nrm = xnrm2_ewqsy(e, 2);
      if (nrm == 0.0) {
        e[0] = 0.0;
      } else {
        if (e[1] < 0.0) {
          /* Start for MATLABSystem: '<S14>/MATLAB System' */
          nrm = -nrm;
        }

        e[0] = nrm;

        /* Start for MATLABSystem: '<S14>/MATLAB System' */
        if (fabs(nrm) >= 1.0020841800044864E-292) {
          nrm = 1.0 / nrm;
          for (qjj = qp1; qjj < 4; qjj++) {
            e[qjj - 1] *= nrm;
          }
        } else {
          for (qjj = qp1; qjj < 4; qjj++) {
            e[qjj - 1] /= nrm;
          }
        }

        e[1]++;
        e[0] = -e[0];
        for (qq = qp1; qq < 4; qq++) {
          work[qq - 1] = 0.0;
        }

        for (qq = qp1; qq < 4; qq++) {
          /* Start for MATLABSystem: '<S14>/MATLAB System' */
          xaxpy_ewqs(2, e[qq - 1], A_0, 3 * (qq - 1) + 2, work, 2);
        }

        for (qq = qp1; qq < 4; qq++) {
          /* Start for MATLABSystem: '<S14>/MATLAB System' */
          xaxpy_ewqsy(2, -e[qq - 1] / e[1], work, 2, A_0, 3 * (qq - 1) + 2);
        }
      }

      for (colqp1 = qp1; colqp1 < 4; colqp1++) {
        V[colqp1 - 1] = e[colqp1 - 1];
      }
    }
  }

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  m = 2;
  s_0[2] = A_0[8];
  e[1] = A_0[7];
  e[2] = 0.0;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  U[6] = 0.0;
  U[7] = 0.0;
  U[8] = 1.0;
  for (colqp1 = 1; colqp1 >= 0; colqp1--) {
    qq = 3 * colqp1 + colqp1;
    if (s_0[colqp1] != 0.0) {
      for (b = colqp1 + 2; b < 4; b++) {
        qjj = ((b - 1) * 3 + colqp1) + 1;

        /* Start for MATLABSystem: '<S14>/MATLAB System' */
        xaxpy_ewq(3 - colqp1, -(xdotc_e(3 - colqp1, U, qq + 1, U, qjj) / U[qq]),
                  qq + 1, U, qjj);
      }

      for (qp1 = colqp1 + 1; qp1 < 4; qp1++) {
        b = (3 * colqp1 + qp1) - 1;
        U[b] = -U[b];
      }

      U[qq]++;

      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      if (colqp1 - 1 >= 0) {
        U[3 * colqp1] = 0.0;
      }
    } else {
      U[3 * colqp1] = 0.0;

      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      U[3 * colqp1 + 1] = 0.0;
      U[3 * colqp1 + 2] = 0.0;
      U[qq] = 1.0;
    }
  }

  for (colqp1 = 2; colqp1 >= 0; colqp1--) {
    if ((colqp1 <= 0) && (e[0] != 0.0)) {
      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      xaxpy_ewq(2, -(xdotc_e(2, V, 2, V, 5) / V[1]), 2, V, 5);
      xaxpy_ewq(2, -(xdotc_e(2, V, 2, V, 8) / V[1]), 2, V, 8);
    }

    V[3 * colqp1] = 0.0;

    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    V[3 * colqp1 + 1] = 0.0;
    V[3 * colqp1 + 2] = 0.0;
    V[colqp1 + 3 * colqp1] = 1.0;
  }

  for (qp1 = 0; qp1 < 3; qp1++) {
    nrm = s_0[qp1];
    if (nrm != 0.0) {
      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      rt = fabs(nrm);
      nrm /= rt;
      s_0[qp1] = rt;

      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      if (qp1 + 1 < 3) {
        e[qp1] /= nrm;
      }

      qq = 3 * qp1;

      /* Start for MATLABSystem: '<S14>/MATLAB System' */
      for (qjj = qq + 1; qjj <= qq + 3; qjj++) {
        U[qjj - 1] *= nrm;
      }
    }

    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    if (qp1 + 1 < 3) {
      ztest = e[qp1];
      if (ztest != 0.0) {
        rt = fabs(ztest);
        nrm = rt / ztest;
        e[qp1] = rt;
        s_0[qp1 + 1] *= nrm;
        colqp1 = (qp1 + 1) * 3;
        for (qjj = colqp1 + 1; qjj <= colqp1 + 3; qjj++) {
          V[qjj - 1] *= nrm;
        }
      }
    }
  }

  rt = 0.0;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  nrm = fmax(fmax(fmax(0.0, fmax(fabs(s_0[0]), fabs(e[0]))), fmax(fabs(s_0[1]),
    fabs(e[1]))), fmax(fabs(s_0[2]), fabs(e[2])));
  while ((m + 1 > 0) && (!(rt >= 75.0))) {
    colqp1 = m;
    qp1 = m;
    exitg1 = false;
    while ((!exitg1) && (qp1 > -1)) {
      colqp1 = qp1;
      if (qp1 == 0) {
        exitg1 = true;
      } else {
        ztest0 = fabs(e[qp1 - 1]);
        if ((ztest0 <= (fabs(s_0[qp1 - 1]) + fabs(s_0[qp1])) *
             2.2204460492503131E-16) || ((ztest0 <= 1.0020841800044864E-292) ||
             ((rt > 20.0) && (ztest0 <= 2.2204460492503131E-16 * nrm)))) {
          e[qp1 - 1] = 0.0;
          exitg1 = true;
        } else {
          qp1--;
        }
      }
    }

    if (colqp1 == m) {
      ztest0 = 4.0;
    } else {
      qp1 = m + 1;
      qq = m + 1;
      exitg1 = false;
      while ((!exitg1) && (qq >= colqp1)) {
        qp1 = qq;
        if (qq == colqp1) {
          exitg1 = true;
        } else {
          ztest0 = 0.0;
          if (qq < m + 1) {
            ztest0 = fabs(e[qq - 1]);
          }

          if (qq > colqp1 + 1) {
            ztest0 += fabs(e[qq - 2]);
          }

          ztest = fabs(s_0[qq - 1]);
          if ((ztest <= 2.2204460492503131E-16 * ztest0) || (ztest <=
               1.0020841800044864E-292)) {
            s_0[qq - 1] = 0.0;
            exitg1 = true;
          } else {
            qq--;
          }
        }
      }

      if (qp1 == colqp1) {
        ztest0 = 3.0;
      } else if (m + 1 == qp1) {
        ztest0 = 1.0;
      } else {
        ztest0 = 2.0;
        colqp1 = qp1;
      }
    }

    switch ((int32_t)ztest0) {
     case 1:
      ztest0 = e[m - 1];
      e[m - 1] = 0.0;
      for (qq = m; qq >= colqp1 + 1; qq--) {
        xrotg(s_0[qq - 1], ztest0, &s_0[qq - 1], &ztest0, &ztest, &sqds);
        if (qq > colqp1 + 1) {
          ztest0 = -sqds * e[0];
          e[0] *= ztest;
        }

        xrot_ewq(V, 3 * (qq - 1) + 1, 3 * m + 1, ztest, sqds);
      }
      break;

     case 2:
      ztest0 = e[colqp1 - 1];
      e[colqp1 - 1] = 0.0;
      for (qp1 = colqp1 + 1; qp1 <= m + 1; qp1++) {
        xrotg(s_0[qp1 - 1], ztest0, &s_0[qp1 - 1], &ztest, &sqds, &smm1);
        ztest = e[qp1 - 1];
        ztest0 = -smm1 * ztest;
        e[qp1 - 1] = ztest * sqds;
        xrot_ewq(U, 3 * (qp1 - 1) + 1, 3 * (colqp1 - 1) + 1, sqds, smm1);
      }
      break;

     case 3:
      smm1 = s_0[m - 1];
      sqds = e[m - 1];
      ztest = fmax(fmax(fmax(fmax(fabs(s_0[m]), fabs(smm1)), fabs(sqds)), fabs
                        (s_0[colqp1])), fabs(e[colqp1]));
      ztest0 = s_0[m] / ztest;
      smm1 /= ztest;
      emm1 = sqds / ztest;
      sqds = s_0[colqp1] / ztest;
      smm1 = ((smm1 + ztest0) * (smm1 - ztest0) + emm1 * emm1) / 2.0;
      emm1 *= ztest0;
      emm1 *= emm1;
      if ((smm1 != 0.0) || (emm1 != 0.0)) {
        shift = sqrt(smm1 * smm1 + emm1);
        if (smm1 < 0.0) {
          shift = -shift;
        }

        shift = emm1 / (smm1 + shift);
      } else {
        shift = 0.0;
      }

      ztest0 = (sqds + ztest0) * (sqds - ztest0) + shift;
      ztest = e[colqp1] / ztest * sqds;
      for (qq = colqp1 + 1; qq <= m; qq++) {
        xrotg(ztest0, ztest, &sqds, &smm1, &emm1, &shift);
        if (qq > colqp1 + 1) {
          e[0] = sqds;
        }

        ztest0_tmp = e[qq - 1];
        ztest0 = s_0[qq - 1];
        e[qq - 1] = ztest0_tmp * emm1 - ztest0 * shift;
        ztest = shift * s_0[qq];
        s_0[qq] *= emm1;
        b = (qq - 1) * 3 + 1;
        qjj = 3 * qq + 1;
        xrot_ewq(V, b, qjj, emm1, shift);
        xrotg(ztest0 * emm1 + ztest0_tmp * shift, ztest, &s_0[qq - 1], &sqds,
              &smm1, &emm1);
        ztest0_tmp = e[qq - 1];
        ztest0 = ztest0_tmp * smm1 + emm1 * s_0[qq];
        s_0[qq] = ztest0_tmp * -emm1 + smm1 * s_0[qq];
        ztest = emm1 * e[qq];
        e[qq] *= smm1;
        xrot_ewq(U, b, qjj, smm1, emm1);
      }

      e[m - 1] = ztest0;
      rt++;
      break;

     default:
      if (s_0[colqp1] < 0.0) {
        s_0[colqp1] = -s_0[colqp1];
        qq = 3 * colqp1;
        for (qjj = qq + 1; qjj <= qq + 3; qjj++) {
          V[qjj - 1] = -V[qjj - 1];
        }
      }

      qp1 = colqp1 + 1;
      while ((colqp1 + 1 < 3) && (s_0[colqp1] < s_0[qp1])) {
        rt = s_0[colqp1];
        s_0[colqp1] = s_0[qp1];
        s_0[qp1] = rt;
        b = 3 * colqp1 + 1;
        qjj = (colqp1 + 1) * 3 + 1;
        xswap_ewq(V, b, qjj);
        xswap_ewq(U, b, qjj);
        colqp1 = qp1;
        qp1++;
      }

      rt = 0.0;
      m--;
      break;
    }
  }

  s[0] = s_0[0];
  s[1] = s_0[1];
  s[2] = s_0[2];
  if (doscale) {
    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    xzlascl_ewq(cscale, anrm, s);
  }
}

static double xnrm2_ewqsyl(int32_t n, const double x[18], int32_t ix0)
{
  double scale;
  double y;
  int32_t k;
  int32_t kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;

  /* Start for MATLABSystem: '<S14>/MATLAB System' */
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  /* End of Start for MATLABSystem: '<S14>/MATLAB System' */
  return scale * sqrt(y);
}

/* Model step function */
void sensor_fusion_step(void)
{
  double c_A[18];
  double Ss[16];
  double b_V[16];
  double rtb_y_j[16];
  double B[12];
  double K[12];
  double dHdx[12];
  double A[9];
  double Ss_0[9];
  double b_varargout_1[9];
  double b_varargout_2[9];
  double rtb_MATLABSystem_o2_k[9];
  double rtb_MATLABSystem_o2_k_0[9];
  double rtb_y_e[9];
  double tmp[9];
  double s[4];
  double rtb_DataStoreRead[3];
  double rtb_MATLABSystem_o1_0[3];
  double s_0[3];
  double work[3];
  double b_V_0;
  double b_V_1;
  double b_V_2;
  double b_V_3;
  double rtb_UnitConversion;
  double rtb_wheel_RL;
  double rtb_wheel_RR;
  int32_t b_k;
  int32_t coltop;
  int32_t e;
  int32_t exitg1;
  int32_t i;
  int32_t ii;
  int32_t jy;
  int32_t knt;
  int32_t lastc;
  int32_t lastv;
  bool exitg2;

  /* UnitConversion: '<S1>/Unit Conversion' incorporates:
   *  Inport generated from: '<Root>/cockpit'
   */
  /* Unit Conversion - from: deg to: rad
     Expression: output = (0.0174533*input) + (0) */
  rtb_UnitConversion = 0.017453292519943295 * sensor_fusion_U.cockpit.steer;

  /* Gain: '<Root>/Gain' incorporates:
   *  Inport generated from: '<Root>/wheel'
   */
  rtb_wheel_RL = 13.1 * sensor_fusion_U.wheel.speed.rl;

  /* Gain: '<Root>/Gain2' incorporates:
   *  Inport generated from: '<Root>/wheel'
   */
  rtb_wheel_RR = 13.1 * sensor_fusion_U.wheel.speed.rr;

  /* Outputs for Atomic SubSystem: '<Root>/EKF' */
  /* Lookup_n-D: '<S2>/SteerWheel to SteerAngle(L)2' incorporates:
   *  UnitConversion: '<S1>/Unit Conversion'
   */
  sensor_fusion_DW_l.steer_angle_L = look1_binlx(rtb_UnitConversion,
    rtCP_SteerWheeltoSteerAngleL2_b, rtCP_SteerWheeltoSteerAngleL2_t, 100U);

  /* Lookup_n-D: '<S2>/SteerWheel to SteerAngle(R)2' incorporates:
   *  UnitConversion: '<S1>/Unit Conversion'
   */
  sensor_fusion_DW_l.steer_angle_R = look1_binlx(rtb_UnitConversion,
    rtCP_SteerWheeltoSteerAngleR2_b, rtCP_SteerWheeltoSteerAngleR2_t, 100U);

  /* MATLAB Function: '<S10>/MATLAB Function2' incorporates:
   *  Constant: '<S2>/Q_Vx1'
   */
  rtb_y_e[0] = 0.0464159;
  rtb_y_e[3] = 0.0;
  rtb_y_e[6] = 0.0;
  rtb_y_e[1] = 0.0;

  /* MATLAB Function: '<S2>/MATLAB Function1' incorporates:
   *  Gain: '<S9>/Multiply'
   *  Inport generated from: '<Root>/imu'
   *  Sum: '<S9>/Add1'
   */
  if (fabs((sensor_fusion_DW_l.steer_angle_L + sensor_fusion_DW_l.steer_angle_R)
           * 0.5) <= 0.02) {
    if (fabs(sensor_fusion_U.imu.gyro.z) <= 0.02) {
      /* MATLAB Function: '<S10>/MATLAB Function2' */
      rtb_y_e[4] = 0.0;
    } else {
      /* MATLAB Function: '<S10>/MATLAB Function2' incorporates:
       *  Constant: '<S2>/Q_Vy1'
       */
      rtb_y_e[4] = 0.006;
    }
  } else {
    /* MATLAB Function: '<S10>/MATLAB Function2' incorporates:
     *  Constant: '<S2>/Q_Vy1'
     */
    rtb_y_e[4] = 0.006;
  }

  /* End of MATLAB Function: '<S2>/MATLAB Function1' */

  /* MATLAB Function: '<S10>/MATLAB Function2' incorporates:
   *  Constant: '<S2>/Q_Vx1'
   */
  rtb_y_e[7] = 0.0;
  rtb_y_e[2] = 0.0;
  rtb_y_e[5] = 0.0;
  rtb_y_e[8] = 0.000464159;

  /* MATLAB Function: '<S8>/MATLAB Function2' */
  rtb_y_j[0] = 0.0071986;
  rtb_y_j[4] = 0.0;
  rtb_y_j[8] = 0.0;
  rtb_y_j[12] = 0.0;
  rtb_y_j[1] = 0.0;
  rtb_y_j[5] = 0.0071986;
  rtb_y_j[9] = 0.0;
  rtb_y_j[13] = 0.0;
  rtb_y_j[2] = 0.0;
  rtb_y_j[6] = 0.0;
  rtb_y_j[10] = 0.0071986;
  rtb_y_j[14] = 0.0;
  rtb_y_j[3] = 0.0;
  rtb_y_j[7] = 0.0;
  rtb_y_j[11] = 0.0;
  rtb_y_j[15] = 0.0071986;

  /* Outputs for Enabled SubSystem: '<S3>/Correct1' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  /* DataStoreRead: '<S12>/Data Store ReadP' */
  memcpy(&rtb_MATLABSystem_o2_k[0], &sensor_fusion_DW_l.P[0], 9U * sizeof(double));

  /* MATLABSystem: '<S12>/MATLAB System' */
  svd(rtb_y_j, Ss, s, b_V);
  memset(&Ss[0], 0, sizeof(double) << 4U);
  Ss[0] = s[0];
  Ss[5] = s[1];
  Ss[10] = s[2];
  Ss[15] = s[3];
  for (b_k = 0; b_k < 16; b_k++) {
    Ss[b_k] = sqrt(Ss[b_k]);
  }

  for (ii = 0; ii < 4; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    b_V_0 = 0.0;
    b_V_1 = 0.0;
    b_V_2 = 0.0;
    b_V_3 = 0.0;
    for (b_k = 0; b_k < 4; b_k++) {
      rtb_UnitConversion = Ss[(ii << 2) + b_k];
      i = b_k << 2;
      b_V_0 += b_V[i] * rtb_UnitConversion;
      b_V_1 += b_V[i + 1] * rtb_UnitConversion;
      b_V_2 += b_V[i + 2] * rtb_UnitConversion;
      b_V_3 += b_V[i + 3] * rtb_UnitConversion;
    }

    i = ii << 2;
    rtb_y_j[i + 3] = b_V_3;
    rtb_y_j[i + 2] = b_V_2;
    rtb_y_j[i + 1] = b_V_1;
    rtb_y_j[i] = b_V_0;
  }

  for (b_k = 0; b_k < 3; b_k++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
     *  DataStoreRead: '<S12>/Data Store ReadX'
     */
    rtb_DataStoreRead[b_k] = sensor_fusion_DW_l.x[b_k];
  }

  /* DataStoreRead: '<S12>/Data Store ReadP' */
  memcpy(&tmp[0], &sensor_fusion_DW_l.P[0], 9U * sizeof(double));

  /* MATLABSystem: '<S12>/MATLAB System' */
  EKFCorrectorNonAdditive_getMeas(rtb_y_j, rtb_DataStoreRead, tmp, s, K, Ss,
    dHdx, b_V);
  for (ii = 0; ii < 3; ii++) {
    i = ii << 2;
    B[i] = K[ii];
    B[i + 1] = K[ii + 3];
    B[i + 2] = K[ii + 6];
    B[i + 3] = K[ii + 9];
  }

  for (ii = 0; ii < 3; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    i = ii << 2;
    K[i] = B[i];
    K[i + 1] = B[i + 1];
    K[i + 2] = B[i + 2];
    K[i + 3] = B[i + 3];
  }

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  trisolve(Ss, K);

  /* MATLABSystem: '<S12>/MATLAB System' */
  for (ii = 0; ii < 3; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    i = ii << 2;
    B[i] = K[i];
    B[i + 1] = K[i + 1];
    B[i + 2] = K[i + 2];
    B[i + 3] = K[i + 3];
  }

  for (ii = 0; ii < 4; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    i = ii << 2;
    rtb_y_j[i] = Ss[ii];
    rtb_y_j[i + 1] = Ss[ii + 4];
    rtb_y_j[i + 2] = Ss[ii + 8];
    rtb_y_j[i + 3] = Ss[ii + 12];
  }

  /* Start for MATLABSystem: '<S12>/MATLAB System' */
  trisolve_e(rtb_y_j, B);

  /* MATLABSystem: '<S12>/MATLAB System' */
  for (ii = 0; ii < 4; ii++) {
    K[3 * ii] = B[ii];
    K[3 * ii + 1] = B[ii + 4];
    K[3 * ii + 2] = B[ii + 8];
  }

  for (ii = 0; ii < 12; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    B[ii] = -K[ii];
  }

  /* MATLABSystem: '<S12>/MATLAB System' */
  for (ii = 0; ii < 3; ii++) {
    b_V_0 = 0.0;
    b_V_1 = 0.0;
    b_V_2 = 0.0;
    for (b_k = 0; b_k < 4; b_k++) {
      rtb_UnitConversion = dHdx[(ii << 2) + b_k];
      b_V_0 += B[3 * b_k] * rtb_UnitConversion;
      b_V_1 += B[3 * b_k + 1] * rtb_UnitConversion;
      b_V_2 += B[3 * b_k + 2] * rtb_UnitConversion;
    }

    A[3 * ii + 2] = b_V_2;
    A[3 * ii + 1] = b_V_1;
    A[3 * ii] = b_V_0;
  }

  A[0]++;
  A[4]++;
  A[8]++;
  for (ii = 0; ii < 4; ii++) {
    /* Start for MATLABSystem: '<S12>/MATLAB System' */
    b_V_0 = 0.0;
    b_V_1 = 0.0;
    b_V_2 = 0.0;
    for (b_k = 0; b_k < 4; b_k++) {
      rtb_UnitConversion = b_V[(ii << 2) + b_k];
      b_V_0 += K[3 * b_k] * rtb_UnitConversion;
      b_V_1 += K[3 * b_k + 1] * rtb_UnitConversion;
      b_V_2 += K[3 * b_k + 2] * rtb_UnitConversion;
    }

    B[3 * ii + 2] = b_V_2;
    B[3 * ii + 1] = b_V_1;
    B[3 * ii] = b_V_0;
  }

  /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
   *  DataStoreWrite: '<S12>/Data Store WriteP'
   */
  qrFactor(A, rtb_MATLABSystem_o2_k, B, sensor_fusion_DW_l.P);

  /* End of Outputs for SubSystem: '<S3>/Correct1' */

  /* Product: '<S11>/Product' incorporates:
   *  Constant: '<S11>/Constant1'
   */
  rtb_wheel_RL *= 0.00203044;

  /* Outputs for Enabled SubSystem: '<S3>/Correct1' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
   *  Product: '<S11>/Product'
   */
  rtb_UnitConversion = rtb_wheel_RL - s[0];

  /* End of Outputs for SubSystem: '<S3>/Correct1' */

  /* Product: '<S11>/Product' incorporates:
   *  Constant: '<S11>/Constant1'
   */
  b_V_0 = rtb_wheel_RR * 0.00203044;

  /* Outputs for Enabled SubSystem: '<S3>/Correct1' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  /* Start for MATLABSystem: '<S12>/MATLAB System' incorporates:
   *  Product: '<S11>/Product'
   */
  rtb_wheel_RR = b_V_0 - s[1];
  rtb_wheel_RL -= s[2];
  b_V_0 -= s[3];

  /* Outputs for Atomic SubSystem: '<S3>/Output' */
  for (i = 0; i < 3; i++) {
    /* DataStoreWrite: '<S12>/Data Store WriteX' incorporates:
     *  DataStoreRead: '<S12>/Data Store ReadX'
     *  MATLABSystem: '<S12>/MATLAB System'
     * */
    b_V_1 = (((K[i + 3] * rtb_wheel_RR + K[i] * rtb_UnitConversion) + K[i + 6] *
              rtb_wheel_RL) + K[i + 9] * b_V_0) + sensor_fusion_DW_l.x[i];
    sensor_fusion_DW_l.x[i] = b_V_1;

    /* DataStoreRead: '<S13>/Data Store Read' */
    rtb_DataStoreRead[i] = b_V_1;
  }

  /* End of Outputs for SubSystem: '<S3>/Output' */
  /* End of Outputs for SubSystem: '<S3>/Correct1' */

  /* Outputs for Atomic SubSystem: '<S3>/Predict' */
  /* MATLABSystem: '<S14>/MATLAB System' */
  svd_e(rtb_y_e, Ss_0, s_0, A);
  for (b_k = 0; b_k < 9; b_k++) {
    /* DataStoreRead: '<S14>/Data Store ReadP' */
    rtb_MATLABSystem_o2_k[b_k] = sensor_fusion_DW_l.P[b_k];

    /* MATLABSystem: '<S14>/MATLAB System' */
    Ss_0[b_k] = 0.0;
  }

  /* MATLABSystem: '<S14>/MATLAB System' */
  Ss_0[0] = s_0[0];
  Ss_0[4] = s_0[1];
  Ss_0[8] = s_0[2];
  for (b_k = 0; b_k < 9; b_k++) {
    Ss_0[b_k] = sqrt(Ss_0[b_k]);
  }

  /* Start for MATLABSystem: '<S14>/MATLAB System' incorporates:
   *  DataStoreRead: '<S14>/Data Store ReadX'
   */
  s_0[0] = 0.0;
  s_0[1] = 0.0;
  s_0[2] = 0.0;
  stateTransitionJacobianFcn(sensor_fusion_DW_l.x, s_0, b_varargout_1,
    b_varargout_2);
  stateTransitionFcn(sensor_fusion_DW_l.x, s_0, rtb_MATLABSystem_o1_0);
  for (i = 0; i < 3; i++) {
    /* MATLABSystem: '<S14>/MATLAB System' */
    s_0[i] = 0.0;

    /* Start for MATLABSystem: '<S14>/MATLAB System' */
    b_V_0 = 0.0;
    b_V_1 = 0.0;
    b_V_2 = 0.0;
    rtb_wheel_RR = b_varargout_1[i + 3];
    rtb_wheel_RL = b_varargout_1[i];
    b_V_3 = b_varargout_1[i + 6];
    for (ii = 0; ii < 3; ii++) {
      b_k = 3 * i + ii;
      rtb_UnitConversion = Ss_0[b_k];
      b_V_0 += A[3 * ii] * rtb_UnitConversion;
      coltop = 3 * ii + 1;
      b_V_1 += A[coltop] * rtb_UnitConversion;
      lastv = 3 * ii + 2;
      b_V_2 += A[lastv] * rtb_UnitConversion;
      rtb_MATLABSystem_o2_k_0[b_k] = (rtb_MATLABSystem_o2_k[3 * ii] *
        rtb_wheel_RL + rtb_MATLABSystem_o2_k[coltop] * rtb_wheel_RR) +
        rtb_MATLABSystem_o2_k[lastv] * b_V_3;
      tmp[b_k] = 0.0;
    }

    coltop = 3 * i + 2;
    rtb_y_e[coltop] = b_V_2;
    lastv = 3 * i + 1;
    rtb_y_e[lastv] = b_V_1;
    rtb_y_e[3 * i] = b_V_0;
    rtb_UnitConversion = tmp[3 * i];
    rtb_wheel_RR = tmp[lastv];
    rtb_wheel_RL = tmp[coltop];
    for (ii = 0; ii < 3; ii++) {
      b_V_0 = rtb_y_e[3 * i + ii];
      rtb_UnitConversion += b_varargout_2[3 * ii] * b_V_0;
      rtb_wheel_RR += b_varargout_2[3 * ii + 1] * b_V_0;
      rtb_wheel_RL += b_varargout_2[3 * ii + 2] * b_V_0;
    }

    tmp[coltop] = rtb_wheel_RL;
    tmp[lastv] = rtb_wheel_RR;
    tmp[3 * i] = rtb_UnitConversion;
  }

  for (i = 0; i < 3; i++) {
    /* MATLABSystem: '<S14>/MATLAB System' */
    c_A[6 * i] = rtb_MATLABSystem_o2_k_0[3 * i];
    c_A[6 * i + 3] = tmp[i];
    c_A[6 * i + 1] = rtb_MATLABSystem_o2_k_0[3 * i + 1];
    c_A[6 * i + 4] = tmp[i + 3];
    c_A[6 * i + 2] = rtb_MATLABSystem_o2_k_0[3 * i + 2];
    c_A[6 * i + 5] = tmp[i + 6];
    work[i] = 0.0;
  }

  /* MATLABSystem: '<S14>/MATLAB System' */
  for (b_k = 0; b_k < 3; b_k++) {
    ii = b_k * 6 + b_k;
    coltop = ii + 2;
    rtb_UnitConversion = c_A[ii];
    s_0[b_k] = 0.0;
    rtb_wheel_RL = xnrm2_ewqsyl(5 - b_k, c_A, ii + 2);
    if (rtb_wheel_RL != 0.0) {
      rtb_wheel_RR = c_A[ii];
      rtb_wheel_RL = rt_hypotd_snf(rtb_wheel_RR, rtb_wheel_RL);
      if (rtb_wheel_RR >= 0.0) {
        rtb_wheel_RL = -rtb_wheel_RL;
      }

      if (fabs(rtb_wheel_RL) < 1.0020841800044864E-292) {
        knt = -1;
        do {
          knt++;
          i = ii - b_k;
          for (lastv = coltop; lastv <= i + 6; lastv++) {
            c_A[lastv - 1] *= 9.9792015476736E+291;
          }

          rtb_wheel_RL *= 9.9792015476736E+291;
          rtb_UnitConversion *= 9.9792015476736E+291;
        } while ((fabs(rtb_wheel_RL) < 1.0020841800044864E-292) && (knt + 1 < 20));

        rtb_wheel_RL = rt_hypotd_snf(rtb_UnitConversion, xnrm2_ewqsyl(5 - b_k,
          c_A, ii + 2));
        if (rtb_UnitConversion >= 0.0) {
          rtb_wheel_RL = -rtb_wheel_RL;
        }

        s_0[b_k] = (rtb_wheel_RL - rtb_UnitConversion) / rtb_wheel_RL;
        rtb_UnitConversion = 1.0 / (rtb_UnitConversion - rtb_wheel_RL);
        for (lastv = coltop; lastv <= i + 6; lastv++) {
          c_A[lastv - 1] *= rtb_UnitConversion;
        }

        for (lastv = 0; lastv <= knt; lastv++) {
          rtb_wheel_RL *= 1.0020841800044864E-292;
        }

        rtb_UnitConversion = rtb_wheel_RL;
      } else {
        s_0[b_k] = (rtb_wheel_RL - rtb_wheel_RR) / rtb_wheel_RL;
        rtb_UnitConversion = 1.0 / (rtb_wheel_RR - rtb_wheel_RL);
        i = ii - b_k;
        for (lastv = coltop; lastv <= i + 6; lastv++) {
          c_A[lastv - 1] *= rtb_UnitConversion;
        }

        rtb_UnitConversion = rtb_wheel_RL;
      }
    }

    c_A[ii] = rtb_UnitConversion;
    if (b_k + 1 < 3) {
      c_A[ii] = 1.0;
      knt = ii + 7;
      if (s_0[b_k] != 0.0) {
        lastv = 6 - b_k;
        i = ii - b_k;
        while ((lastv > 0) && (c_A[i + 5] == 0.0)) {
          lastv--;
          i--;
        }

        lastc = 2 - b_k;
        exitg2 = false;
        while ((!exitg2) && (lastc > 0)) {
          coltop = (lastc - 1) * 6 + ii;
          i = coltop + 7;
          do {
            exitg1 = 0;
            if (i <= (coltop + lastv) + 6) {
              if (c_A[i - 1] != 0.0) {
                exitg1 = 1;
              } else {
                i++;
              }
            } else {
              lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        lastc = 0;
      }

      if (lastv > 0) {
        if (lastc != 0) {
          memset(&work[0], 0, (uint32_t)lastc * sizeof(double));
          coltop = (lastc - 1) * 6 + ii;
          for (jy = knt; jy <= coltop + 7; jy += 6) {
            rtb_wheel_RL = 0.0;
            e = jy + lastv;
            for (i = jy; i < e; i++) {
              rtb_wheel_RL += c_A[(ii + i) - jy] * c_A[i - 1];
            }

            i = div_nde_s32_floor((jy - ii) - 7, 6);
            work[i] += rtb_wheel_RL;
          }
        }

        if (!(-s_0[b_k] == 0.0)) {
          jy = ii;
          i = lastc;
          for (lastc = 0; lastc < i; lastc++) {
            rtb_wheel_RR = work[lastc];
            if (rtb_wheel_RR != 0.0) {
              rtb_wheel_RL = rtb_wheel_RR * -s_0[b_k];
              knt = jy + 7;
              coltop = (lastv + jy) + 6;
              for (e = knt; e <= coltop; e++) {
                c_A[e - 1] += c_A[((ii + e) - jy) - 7] * rtb_wheel_RL;
              }
            }

            jy += 6;
          }
        }
      }

      c_A[ii] = rtb_UnitConversion;
    }
  }

  for (ii = 0; ii < 3; ii++) {
    memcpy(&Ss_0[ii * 3], &c_A[ii * 6], (uint32_t)(ii + 1) * sizeof(double));
    for (b_k = ii + 2; b_k < 4; b_k++) {
      Ss_0[(b_k + 3 * ii) - 1] = 0.0;
    }
  }

  for (i = 0; i < 3; i++) {
    /* DataStoreWrite: '<S14>/Data Store WriteP' incorporates:
     *  MATLABSystem: '<S14>/MATLAB System'
     * */
    sensor_fusion_DW_l.P[3 * i] = Ss_0[i];
    sensor_fusion_DW_l.P[3 * i + 1] = Ss_0[i + 3];
    sensor_fusion_DW_l.P[3 * i + 2] = Ss_0[i + 6];

    /* DataStoreWrite: '<S14>/Data Store WriteX' incorporates:
     *  MATLABSystem: '<S14>/MATLAB System'
     */
    sensor_fusion_DW_l.x[i] = rtb_MATLABSystem_o1_0[i];
  }

  /* End of Outputs for SubSystem: '<S3>/Predict' */

  /* Saturate: '<S2>/Saturation' */
  if (rtb_DataStoreRead[0] <= 0.0) {
    sensor_fusion_Y.states.velocity.x = 0.0;
  } else {
    sensor_fusion_Y.states.velocity.x = rtb_DataStoreRead[0];
  }

  /* End of Saturate: '<S2>/Saturation' */
  /* End of Outputs for SubSystem: '<Root>/EKF' */

  /* BusCreator generated from: '<Root>/states_BusCreator' incorporates:
   *  Constant: '<Root>/Constant'
   */
  sensor_fusion_Y.states.header.timestamp_ns = 0ULL;

  /* BusCreator generated from: '<Root>/states_BusCreator' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  sensor_fusion_Y.states.velocity.y = 0.0;
}

/* Model initialize function */
void sensor_fusion_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(sensor_fusion_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&sensor_fusion_DW_l, 0,
                sizeof(sensor_fusion_DW));

  /* external inputs */
  (void)memset(&sensor_fusion_U, 0, sizeof(sensor_fusion_ExtU));

  /* external outputs */
  sensor_fusion_Y.states = sensor_fusion_rtZmsg_ctrl_state;

  /* SystemInitialize for Atomic SubSystem: '<Root>/EKF' */
  /* Start for DataStoreMemory: '<S3>/DataStoreMemory - P' */
  memcpy(&sensor_fusion_DW_l.P[0], &rtCP_DataStoreMemoryP_InitialVa[0], 9U *
         sizeof(double));

  /* End of SystemInitialize for SubSystem: '<Root>/EKF' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
