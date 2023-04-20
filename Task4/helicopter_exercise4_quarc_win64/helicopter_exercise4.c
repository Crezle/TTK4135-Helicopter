/*
 * helicopter_exercise4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopter_exercise4".
 *
 * Model version              : 10.0
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Apr 20 10:56:30 2023
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopter_exercise4.h"
#include "helicopter_exercise4_private.h"
#include "helicopter_exercise4_dt.h"

/* Block signals (default storage) */
B_helicopter_exercise4_T helicopter_exercise4_B;

/* Continuous states */
X_helicopter_exercise4_T helicopter_exercise4_X;

/* Block states (default storage) */
DW_helicopter_exercise4_T helicopter_exercise4_DW;

/* Real-time model */
static RT_MODEL_helicopter_exercise4_T helicopter_exercise4_M_;
RT_MODEL_helicopter_exercise4_T *const helicopter_exercise4_M =
  &helicopter_exercise4_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopter_exercise4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopter_exercise4_output(void)
{
  /* local block i/o variables */
  real_T rtb_u_k[2];
  real_T rtb_deltaX[6];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T tmp[12];
  real_T lastTime;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
  int32_T i;
  int32_T i_0;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
    /* set solver stop time */
    if (!(helicopter_exercise4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopter_exercise4_M->solverInfo,
                            ((helicopter_exercise4_M->Timing.clockTickH0 + 1) *
        helicopter_exercise4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopter_exercise4_M->solverInfo,
                            ((helicopter_exercise4_M->Timing.clockTick0 + 1) *
        helicopter_exercise4_M->Timing.stepSize0 +
        helicopter_exercise4_M->Timing.clockTickH0 *
        helicopter_exercise4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopter_exercise4_M)) {
    helicopter_exercise4_M->Timing.t[0] = rtsiGetT
      (&helicopter_exercise4_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopter_exercise4_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopter_exercise4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopter_exercise4_DW.HILReadEncoderTimebase_Task, 1,
         &helicopter_exercise4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopter_exercise4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopter_exercise4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopter_exercise4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S3>/Gain1' incorporates:
     *  Constant: '<Root>/Constant'
     */
    helicopter_exercise4_B.Gain1 = helicopter_exercise4_P.Gain1_Gain *
      helicopter_exercise4_P.Constant_Value;
  }

  /* FromWorkspace: '<Root>/u_k+' */
  {
    real_T *pDataValues = (real_T *) helicopter_exercise4_DW.u_k_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopter_exercise4_DW.u_k_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_exercise4_DW.u_k_IWORK.PrevIndex;
    real_T t = helicopter_exercise4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_exercise4_DW.u_k_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_u_k[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_u_k[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_u_k[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopter_exercise4_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopter_exercise4_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopter_exercise4_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopter_exercise4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopter_exercise4_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_deltaX[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_deltaX[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_deltaX[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
    /* Gain: '<S5>/Travel: Count to rad' incorporates:
     *  Gain: '<S5>/Travel_gain'
     */
    helicopter_exercise4_B.TravelCounttorad = helicopter_exercise4_P.travel_gain
      * rtb_HILReadEncoderTimebase_o1 *
      helicopter_exercise4_P.TravelCounttorad_Gain;

    /* Gain: '<S13>/Gain' */
    helicopter_exercise4_B.Gain = helicopter_exercise4_P.Gain_Gain *
      helicopter_exercise4_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/travel_offset [deg]'
     */
    helicopter_exercise4_B.Sum3 = helicopter_exercise4_P.travel_offsetdeg_Value
      + helicopter_exercise4_B.Gain;

    /* Gain: '<S5>/Pitch: Count to rad' */
    helicopter_exercise4_B.PitchCounttorad =
      helicopter_exercise4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopter_exercise4_B.Gain_i = helicopter_exercise4_P.Gain_Gain_a *
      helicopter_exercise4_B.PitchCounttorad;
  }

  /* Gain: '<S14>/Gain' incorporates:
   *  TransferFcn: '<S5>/Travel: Transfer Fcn'
   */
  helicopter_exercise4_B.Gain_d = (helicopter_exercise4_P.TravelTransferFcn_C *
    helicopter_exercise4_X.TravelTransferFcn_CSTATE +
    helicopter_exercise4_P.TravelTransferFcn_D *
    helicopter_exercise4_B.TravelCounttorad) *
    helicopter_exercise4_P.Gain_Gain_l;

  /* Gain: '<S11>/Gain' incorporates:
   *  TransferFcn: '<S5>/Pitch: Transfer Fcn'
   */
  helicopter_exercise4_B.Gain_b = (helicopter_exercise4_P.PitchTransferFcn_C *
    helicopter_exercise4_X.PitchTransferFcn_CSTATE +
    helicopter_exercise4_P.PitchTransferFcn_D *
    helicopter_exercise4_B.PitchCounttorad) *
    helicopter_exercise4_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
    /* Gain: '<S5>/Elevation: Count to rad' incorporates:
     *  Gain: '<S5>/Elevation_gain'
     */
    helicopter_exercise4_B.ElevationCounttorad =
      helicopter_exercise4_P.elevation_gain * rtb_HILReadEncoderTimebase_o3 *
      helicopter_exercise4_P.ElevationCounttorad_Gain;

    /* Gain: '<S8>/Gain' */
    helicopter_exercise4_B.Gain_e = helicopter_exercise4_P.Gain_Gain_lv *
      helicopter_exercise4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopter_exercise4_B.Sum = helicopter_exercise4_B.Gain_e +
      helicopter_exercise4_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S5>/Elevation: Transfer Fcn'
   */
  helicopter_exercise4_B.Gain_dg =
    (helicopter_exercise4_P.ElevationTransferFcn_C *
     helicopter_exercise4_X.ElevationTransferFcn_CSTATE +
     helicopter_exercise4_P.ElevationTransferFcn_D *
     helicopter_exercise4_B.ElevationCounttorad) *
    helicopter_exercise4_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  helicopter_exercise4_B.Gain1_e[0] = helicopter_exercise4_P.Gain1_Gain_f *
    helicopter_exercise4_B.Sum3;
  helicopter_exercise4_B.Gain1_e[1] = helicopter_exercise4_P.Gain1_Gain_f *
    helicopter_exercise4_B.Gain_d;
  helicopter_exercise4_B.Gain1_e[2] = helicopter_exercise4_P.Gain1_Gain_f *
    helicopter_exercise4_B.Gain_i;
  helicopter_exercise4_B.Gain1_e[3] = helicopter_exercise4_P.Gain1_Gain_f *
    helicopter_exercise4_B.Gain_b;
  helicopter_exercise4_B.Gain1_e[4] = helicopter_exercise4_P.Gain1_Gain_f *
    helicopter_exercise4_B.Sum;
  helicopter_exercise4_B.Gain1_e[5] = helicopter_exercise4_P.Gain1_Gain_f *
    helicopter_exercise4_B.Gain_dg;
  for (i = 0; i < 6; i++) {
    /* Sum: '<Root>/Sum7' */
    rtb_deltaX[i] = helicopter_exercise4_B.Gain1_e[i] - rtb_deltaX[i];
  }

  /* Gain: '<Root>/Multiply' */
  for (i = 0; i < 12; i++) {
    tmp[i] = -helicopter_exercise4_P.K[i];
  }

  for (i = 0; i < 2; i++) {
    /* Sum: '<Root>/Sum9' incorporates:
     *  Gain: '<Root>/Multiply'
     */
    rtb_Clock = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Clock += tmp[(i_0 << 1) + i] * rtb_deltaX[i_0];
    }

    rtb_u_k[i] += rtb_Clock;

    /* End of Sum: '<Root>/Sum9' */
  }

  /* Sum: '<Root>/Sum4' */
  helicopter_exercise4_B.Sum4 = helicopter_exercise4_B.Gain1 + rtb_u_k[0];

  /* Sum: '<Root>/Sum8' incorporates:
   *  Constant: '<Root>/elevation_ref'
   */
  helicopter_exercise4_B.Sum8 = rtb_u_k[1] +
    helicopter_exercise4_P.elevation_ref_Value;
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
    /* SignalConversion generated from: '<Root>/To File' */
    helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[0] =
      helicopter_exercise4_B.Sum4;
    helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[1] =
      helicopter_exercise4_B.Sum8;
    for (i = 0; i < 6; i++) {
      helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[i + 2] =
        helicopter_exercise4_B.Gain1_e[i];
    }

    /* End of SignalConversion generated from: '<Root>/To File' */
    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopter_exercise4_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopter_exercise4_DW.ToFile_IWORK.Count * (8 + 1)) + 1 < 100000000
          ) {
        FILE *fp = (FILE *) helicopter_exercise4_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[8 + 1];
          helicopter_exercise4_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopter_exercise4_M->Timing.t[1];
          u[1] = helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[0];
          u[2] = helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[1];
          u[3] = helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[2];
          u[4] = helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[3];
          u[5] = helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[4];
          u[6] = helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[5];
          u[7] = helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[6];
          u[8] = helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[7];
          if (fwrite(u, sizeof(real_T), 8 + 1, fp) != 8 + 1) {
            rtmSetErrorStatus(helicopter_exercise4_M,
                              "Error writing to MAT-file task4_X.mat");
            return;
          }

          if (((++helicopter_exercise4_DW.ToFile_IWORK.Count) * (8 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file task4_X.mat.\n");
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   */
  rtb_Clock = ((helicopter_exercise4_B.Sum4 - helicopter_exercise4_B.Gain1_e[2])
               * helicopter_exercise4_P.K_pp - helicopter_exercise4_P.K_pd *
               helicopter_exercise4_B.Gain1_e[3]) + helicopter_exercise4_P.Vd_ff;

  /* Integrator: '<S4>/Integrator' */
  /* Limited  Integrator  */
  if (helicopter_exercise4_X.Integrator_CSTATE >=
      helicopter_exercise4_P.Integrator_UpperSat) {
    helicopter_exercise4_X.Integrator_CSTATE =
      helicopter_exercise4_P.Integrator_UpperSat;
  } else {
    if (helicopter_exercise4_X.Integrator_CSTATE <=
        helicopter_exercise4_P.Integrator_LowerSat) {
      helicopter_exercise4_X.Integrator_CSTATE =
        helicopter_exercise4_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S4>/Sum' */
  rtb_Derivative = helicopter_exercise4_B.Sum8 - helicopter_exercise4_B.Gain1_e
    [4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S4>/K_ed'
   *  Gain: '<S4>/K_ep'
   *  Integrator: '<S4>/Integrator'
   *  Sum: '<S4>/Sum1'
   */
  rtb_Backgain = ((helicopter_exercise4_P.K_ep * rtb_Derivative +
                   helicopter_exercise4_X.Integrator_CSTATE) -
                  helicopter_exercise4_P.K_ed * helicopter_exercise4_B.Gain1_e[5])
    + helicopter_exercise4_P.Vs_ff;

  /* If: '<S4>/If' incorporates:
   *  Clock: '<S4>/Clock'
   *  Gain: '<S4>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
    rtAction = (int8_T)!(helicopter_exercise4_M->Timing.t[0] >= 2.0);
    helicopter_exercise4_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopter_exercise4_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopter_exercise4_B.In1 = helicopter_exercise4_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
      srUpdateBC(helicopter_exercise4_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S4>/If Action Subsystem' */
  }

  /* End of If: '<S4>/If' */
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
  }

  /* Derivative: '<S5>/Derivative' */
  rtb_Derivative = helicopter_exercise4_M->Timing.t[0];
  if ((helicopter_exercise4_DW.TimeStampA >= rtb_Derivative) &&
      (helicopter_exercise4_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    lastTime = helicopter_exercise4_DW.TimeStampA;
    lastU = &helicopter_exercise4_DW.LastUAtTimeA;
    if (helicopter_exercise4_DW.TimeStampA < helicopter_exercise4_DW.TimeStampB)
    {
      if (helicopter_exercise4_DW.TimeStampB < rtb_Derivative) {
        lastTime = helicopter_exercise4_DW.TimeStampB;
        lastU = &helicopter_exercise4_DW.LastUAtTimeB;
      }
    } else {
      if (helicopter_exercise4_DW.TimeStampA >= rtb_Derivative) {
        lastTime = helicopter_exercise4_DW.TimeStampB;
        lastU = &helicopter_exercise4_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopter_exercise4_B.PitchCounttorad - *lastU) /
      (rtb_Derivative - lastTime);
  }

  /* End of Derivative: '<S5>/Derivative' */

  /* Gain: '<S12>/Gain' */
  helicopter_exercise4_B.Gain_l = helicopter_exercise4_P.Gain_Gain_a1 *
    rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Backgain - rtb_Clock) *
    helicopter_exercise4_P.Backgain_Gain;

  /* Saturate: '<S5>/Back motor: Saturation' */
  if (rtb_Derivative > helicopter_exercise4_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopter_exercise4_B.BackmotorSaturation =
      helicopter_exercise4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative <
             helicopter_exercise4_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopter_exercise4_B.BackmotorSaturation =
      helicopter_exercise4_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopter_exercise4_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S5>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Clock + rtb_Backgain) *
    helicopter_exercise4_P.Frontgain_Gain;

  /* Saturate: '<S5>/Front motor: Saturation' */
  if (rtb_Derivative > helicopter_exercise4_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopter_exercise4_B.FrontmotorSaturation =
      helicopter_exercise4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative <
             helicopter_exercise4_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopter_exercise4_B.FrontmotorSaturation =
      helicopter_exercise4_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopter_exercise4_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S5>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
    /* S-Function (hil_write_analog_block): '<S5>/HIL Write Analog' */

    /* S-Function Block: helicopter_exercise4/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopter_exercise4_DW.HILWriteAnalog_Buffer[0] =
        helicopter_exercise4_B.FrontmotorSaturation;
      helicopter_exercise4_DW.HILWriteAnalog_Buffer[1] =
        helicopter_exercise4_B.BackmotorSaturation;
      result = hil_write_analog(helicopter_exercise4_DW.HILInitialize_Card,
        helicopter_exercise4_P.HILWriteAnalog_channels, 2,
        &helicopter_exercise4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopter_exercise4_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S5>/Derivative' */
  if (helicopter_exercise4_DW.TimeStampA == (rtInf)) {
    helicopter_exercise4_DW.TimeStampA = helicopter_exercise4_M->Timing.t[0];
    lastU = &helicopter_exercise4_DW.LastUAtTimeA;
  } else if (helicopter_exercise4_DW.TimeStampB == (rtInf)) {
    helicopter_exercise4_DW.TimeStampB = helicopter_exercise4_M->Timing.t[0];
    lastU = &helicopter_exercise4_DW.LastUAtTimeB;
  } else if (helicopter_exercise4_DW.TimeStampA <
             helicopter_exercise4_DW.TimeStampB) {
    helicopter_exercise4_DW.TimeStampA = helicopter_exercise4_M->Timing.t[0];
    lastU = &helicopter_exercise4_DW.LastUAtTimeA;
  } else {
    helicopter_exercise4_DW.TimeStampB = helicopter_exercise4_M->Timing.t[0];
    lastU = &helicopter_exercise4_DW.LastUAtTimeB;
  }

  *lastU = helicopter_exercise4_B.PitchCounttorad;

  /* End of Update for Derivative: '<S5>/Derivative' */
  if (rtmIsMajorTimeStep(helicopter_exercise4_M)) {
    rt_ertODEUpdateContinuousStates(&helicopter_exercise4_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopter_exercise4_M->Timing.clockTick0)) {
    ++helicopter_exercise4_M->Timing.clockTickH0;
  }

  helicopter_exercise4_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopter_exercise4_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopter_exercise4_M->Timing.clockTick1)) {
      ++helicopter_exercise4_M->Timing.clockTickH1;
    }

    helicopter_exercise4_M->Timing.t[1] =
      helicopter_exercise4_M->Timing.clockTick1 *
      helicopter_exercise4_M->Timing.stepSize1 +
      helicopter_exercise4_M->Timing.clockTickH1 *
      helicopter_exercise4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopter_exercise4_derivatives(void)
{
  XDot_helicopter_exercise4_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopter_exercise4_T *) helicopter_exercise4_M->derivs);

  /* Derivatives for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE +=
    helicopter_exercise4_P.TravelTransferFcn_A *
    helicopter_exercise4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopter_exercise4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_exercise4_P.PitchTransferFcn_A *
    helicopter_exercise4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopter_exercise4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_exercise4_P.ElevationTransferFcn_A *
    helicopter_exercise4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopter_exercise4_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  lsat = (helicopter_exercise4_X.Integrator_CSTATE <=
          helicopter_exercise4_P.Integrator_LowerSat);
  usat = (helicopter_exercise4_X.Integrator_CSTATE >=
          helicopter_exercise4_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopter_exercise4_B.In1 > 0.0)) ||
      (usat && (helicopter_exercise4_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopter_exercise4_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S4>/Integrator' */
}

/* Model initialize function */
void helicopter_exercise4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_exercise4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopter_exercise4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (helicopter_exercise4_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopter_exercise4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
      return;
    }

    if ((helicopter_exercise4_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &helicopter_exercise4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopter_exercise4_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &helicopter_exercise4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopter_exercise4_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (helicopter_exercise4_DW.HILInitialize_Card,
         helicopter_exercise4_P.HILInitialize_AIChannels, 8U,
         &helicopter_exercise4_DW.HILInitialize_AIMinimums[0],
         &helicopter_exercise4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_exercise4_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &helicopter_exercise4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopter_exercise4_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &helicopter_exercise4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopter_exercise4_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopter_exercise4_DW.HILInitialize_Card,
         helicopter_exercise4_P.HILInitialize_AOChannels, 8U,
         &helicopter_exercise4_DW.HILInitialize_AOMinimums[0],
         &helicopter_exercise4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_exercise4_P.HILInitialize_AOStart && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &helicopter_exercise4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_exercise4_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopter_exercise4_DW.HILInitialize_Card,
        helicopter_exercise4_P.HILInitialize_AOChannels, 8U,
        &helicopter_exercise4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_exercise4_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &helicopter_exercise4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_exercise4_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopter_exercise4_DW.HILInitialize_Card,
         helicopter_exercise4_P.HILInitialize_AOChannels, 8U,
         &helicopter_exercise4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_exercise4_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopter_exercise4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            helicopter_exercise4_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopter_exercise4_DW.HILInitialize_Card,
         helicopter_exercise4_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopter_exercise4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_exercise4_P.HILInitialize_EIStart && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopter_exercise4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            helicopter_exercise4_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopter_exercise4_DW.HILInitialize_Card,
        helicopter_exercise4_P.HILInitialize_EIChannels, 8U,
        &helicopter_exercise4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_exercise4_P.HILInitialize_POPStart && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_exercise4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopter_exercise4_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopter_exercise4_DW.HILInitialize_Card,
        helicopter_exercise4_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopter_exercise4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopter_exercise4_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopter_exercise4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopter_exercise4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopter_exercise4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopter_exercise4_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopter_exercise4_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopter_exercise4_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              helicopter_exercise4_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (helicopter_exercise4_DW.HILInitialize_Card,
           &helicopter_exercise4_DW.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &helicopter_exercise4_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (helicopter_exercise4_DW.HILInitialize_Card,
           &helicopter_exercise4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &helicopter_exercise4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopter_exercise4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            helicopter_exercise4_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopter_exercise4_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] =
            helicopter_exercise4_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopter_exercise4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] =
            helicopter_exercise4_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration
        (helicopter_exercise4_DW.HILInitialize_Card,
         helicopter_exercise4_P.HILInitialize_POChannels, 8U,
         (t_pwm_configuration *)
         &helicopter_exercise4_DW.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &helicopter_exercise4_DW.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &helicopter_exercise4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopter_exercise4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopter_exercise4_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopter_exercise4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_exercise4_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopter_exercise4_DW.HILInitialize_Card,
        helicopter_exercise4_P.HILInitialize_POChannels, 8U,
        &helicopter_exercise4_DW.HILInitialize_POSortedFreqs[0],
        &helicopter_exercise4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopter_exercise4_P.HILInitialize_POStart && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_exercise4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_exercise4_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopter_exercise4_DW.HILInitialize_Card,
        helicopter_exercise4_P.HILInitialize_POChannels, 8U,
        &helicopter_exercise4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }

    if (helicopter_exercise4_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_exercise4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_exercise4_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopter_exercise4_DW.HILInitialize_Card,
         helicopter_exercise4_P.HILInitialize_POChannels, 8U,
         &helicopter_exercise4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopter_exercise4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopter_exercise4_DW.HILInitialize_Card,
       helicopter_exercise4_P.HILReadEncoderTimebase_SamplesI,
       helicopter_exercise4_P.HILReadEncoderTimebase_Channels, 3,
       &helicopter_exercise4_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopter_exercise4_DW.HILReadEncoderTimebase_Task,
         (t_buffer_overflow_mode)
         (helicopter_exercise4_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<Root>/u_k+' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.36412976503346084, 0.11143279331977031,
      -0.10676627243482814, -0.27223209658678332, -0.39175370976611834,
      -0.47193503066417014, -0.51906141924998372, -0.52359877559829882,
      -0.52359877559829882, -0.5183413476399602, -0.48689198121975619,
      -0.44654756831447284, -0.40051828801833889, -0.35150981578960372,
      -0.30175453483849979, -0.25305673337879953, -0.20684705908898973,
      -0.16421847130379766, -0.12597856765359067, -0.092686130392734115,
      -0.064674395799709281, -0.042083494463209241, -0.024849127160471437,
      -0.012693707770544287, -0.0050967256902152737, -0.0012410042735564641,
      -5.8424268307548306E-9, 3.4868495977551289E-7, 4.8750784301974875E-7,
      4.8750784301974875E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.28552313888797942, 0.30300466282661448, 0.31965368930155152,
      0.33487434142470157, 0.34792227816544696, 0.35786324946591436,
      0.36354302662967158, 0.363543814342251, 0.35612294530834632,
      0.339163924673139, 0.3100931156899196, 0.26579454376986511,
      0.20250943877399427, 0.11572021546459588, -1.3828164296014162E-6,
      -7.2131993683487557E-7, -3.55987616830339E-7, -1.5480460317803414E-6,
      -1.3171575275160218E-6, -9.3526925072406083E-7, -1.3486620912628893E-6,
      -1.1133928585028815E-6, -1.1968696282011033E-6, -3.1350734945069355E-7,
      -7.846569695363122E-7, 2.0931027029552306E-7, -4.273714946773198E-7,
      -6.909949155326949E-7, -9.9929419705743214E-7, 3.4434214412142537E-7,
      3.4741462898852E-7, 2.8248715001692882E-7, 7.96558236096631E-7,
      -1.7560810343105321E-6, -1.1433602323063715E-7, 6.2004453720921458E-7,
      5.4939334278444354E-7, -4.9772559010756068E-7, 1.9855472762959498E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_exercise4_DW.u_k_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_exercise4_DW.u_k_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_exercise4_DW.u_k_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413625261, 3.1262155534579983,
      3.1033093000299643, 3.0666274151911783, 3.0144539223941584,
      2.9456562771175667, 2.8595077632935446, 2.7555515879651526,
      2.633505110490284, 2.4931956060320961, 2.334518576064299,
      2.1585535901353459, 1.9683298415085078, 1.7684158221403778,
      1.5641057657655049, 1.3606974881003391, 1.1629914155786245,
      0.97500299202236, 0.79972957749946338, 0.63925359632849, 0.49492135514192,
      0.36735858761723877, 0.25655735800184104, 0.16198994706393002,
      0.08272721894219888, 0.01755036463125877, -0.034949062128857109,
      -0.076282660119760592, -0.10799247948120243, -0.131591427280899,
      -0.14851570321355037, -0.1600881192298462, -0.16749113558091819,
      -0.17174875685162738, -0.17371676252943857, -0.17408116547191349,
      -0.17336532486991385, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, -0.015002048909068423, -0.046506351618112111,
      -0.091625013712135384, -0.14672753935514368, -0.2086939711880792,
      -0.27519058110636668, -0.34459405529608833, -0.41582470131356863,
      -0.48818590989947463, -0.56123801783275173, -0.63470811987118858,
      -0.70385994371581273, -0.76089499450735221, -0.7996560774725191,
      -0.81724022549949193, -0.81363311066066324, -0.79082429008685784,
      -0.75195369422505831, -0.70109365809158652, -0.64190392468389346,
      -0.57732896474628026, -0.51025107009872472, -0.44320491846159082,
      -0.37826964375164418, -0.31705091248692457, -0.26070741724376045,
      -0.2099977070404635, -0.16533439196361391, -0.1268392774457674,
      -0.094395791198786369, -0.067697103730605432, -0.046289664065183304,
      -0.029612065404288016, -0.017030485082836822, -0.0078720227112447916,
      -0.0014576117698995382, 0.0028633624079985563, 0.0056760748613255826, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.10602875205865551,
      0.22266037932317656, 0.31888147181640641, 0.38944360631144165,
      0.43795507377677839, 0.46997264230390062, 0.49051724877547082,
      0.5034310014147434, 0.5114213858602934, 0.51630439857701838,
      0.519258621270637, 0.4887386802474285, 0.4031019559850571,
      0.27394853064066294, 0.12427804246042584, -0.025493710039971102,
      -0.16120403259774146, -0.27472252596854607, -0.35945931076323939,
      -0.4183304297927336, -0.456391154163219, -0.47408094076423962,
      -0.47385659328997054, -0.4589377213614988, -0.43267061172482729,
      -0.39821430549025288, -0.35839686450172481, -0.31566325300661624,
      -0.27206876723452511, -0.22929816987332832, -0.18869612617674594,
      -0.15129960755717983, -0.11787089777323205, -0.088921804514503835,
      -0.06472851421308673, -0.045334606721026592, -0.030538995209065698,
      -0.019879177379953157, -0.012628978458501744, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823462206, 0.46652650905808424,
      0.38488436997291947, 0.28224853798014093, 0.19404586986134695,
      0.12807027410848904, 0.082178425886280465, 0.051655010557090583,
      0.031961537782199775, 0.019532050866899832, 0.011816890774474332,
      -0.12207976409283422, -0.34254689704948543, -0.51661370137757645,
      -0.59868195272094848, -0.59908701000158782, -0.54284129023108152,
      -0.45407397348321843, -0.33894713917877328, -0.23548447611797707,
      -0.15224289748194156, -0.070759146404082374, 0.00089738989707617816,
      0.059675487713887206, 0.10506843854668582, 0.13782522493829774,
      0.15926976395411227, 0.17093444598043442, 0.17437794308836446,
      0.17108238944478715, 0.16240817478632943, 0.14958607447826439,
      0.13371483913579116, 0.11579637303491291, 0.096773161205668382,
      0.077575629968240564, 0.059182446047843576, 0.042639271316450164,
      0.029000795685805651, 0.019002608127695466, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0044612990451246785, 0.012541721185634038,
      0.02352691888877273, 0.036802264357362176, 0.051827450947502296,
      0.068112918782428519, 0.085197575528657088, 0.10262717583145073,
      0.11993258496135362, 0.13660752850943214, 0.1520849944631249,
      0.16571164104183872, 0.17671950791823141, 0.18419429205088153,
      0.18703911623264002, 0.18629468728503987, 0.18281387382089823,
      0.17729238504574402, 0.17029478110534046, 0.162276370020116,
      0.15360168467858154, 0.14456008499410294, 0.13537884020655322,
      0.12623415038930574, 0.11726032638787759, 0.10855755305744655,
      0.10019827378213308, 0.092232591762329813, 0.084692716605659718,
      0.07759668137221673, 0.070951336678524643, 0.064754884425676409,
      0.058998943046660729, 0.053670164504481609, 0.04875172032624283,
      0.044224300560377121, 0.040066998690151269, 0.036258009814263643,
      0.0327752523269905, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.017845196180498714, 0.032321688562037439, 0.04394079081255476,
      0.053101381874357791, 0.060100746360560488, 0.065141871339704879,
      0.068338626984914233, 0.069718401211174591, 0.06922163651961151,
      0.066699774192314154, 0.061909863814770989, 0.0545065863148553,
      0.044031467505570812, 0.029899136530600431, 0.011379296727034008,
      -0.0029777157904006413, -0.013923253856566535, -0.02208595510061688,
      -0.027990415761614269, -0.032073644340897871, -0.034698741366137889,
      -0.036166398737914322, -0.036724979150198851, -0.036578759268989916,
      -0.035895296005712611, -0.034811093321724169, -0.033437117101253896,
      -0.031862728079213053, -0.030159500626680418, -0.028384140933771923,
      -0.026581378774768363, -0.024785809011392941, -0.023023765516062739,
      -0.021315114168716474, -0.0196737767129551, -0.018109679063462853,
      -0.016629207480903394, -0.015235955503550497, -0.013931029949092559,
      -0.012714398075210898, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopter_exercise4_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopter_exercise4_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopter_exercise4_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "task4_X.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopter_exercise4_M,
                        "Error creating .mat file task4_X.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 8 + 1, 0, "pc_ec_lambda_r_p_pdot_e_edot")) {
      rtmSetErrorStatus(helicopter_exercise4_M,
                        "Error writing mat file header to file task4_X.mat");
      return;
    }

    helicopter_exercise4_DW.ToFile_IWORK.Count = 0;
    helicopter_exercise4_DW.ToFile_IWORK.Decimation = -1;
    helicopter_exercise4_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for If: '<S4>/If' */
  helicopter_exercise4_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  helicopter_exercise4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  helicopter_exercise4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  helicopter_exercise4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  helicopter_exercise4_X.Integrator_CSTATE =
    helicopter_exercise4_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S5>/Derivative' */
  helicopter_exercise4_DW.TimeStampA = (rtInf);
  helicopter_exercise4_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopter_exercise4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopter_exercise4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopter_exercise4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopter_exercise4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopter_exercise4_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &helicopter_exercise4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopter_exercise4_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopter_exercise4_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopter_exercise4_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopter_exercise4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopter_exercise4_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopter_exercise4_DW.HILInitialize_Card
                         , helicopter_exercise4_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopter_exercise4_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopter_exercise4_DW.HILInitialize_AOVoltages[0]
                         , &helicopter_exercise4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (helicopter_exercise4_DW.HILInitialize_Card,
             helicopter_exercise4_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &helicopter_exercise4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (helicopter_exercise4_DW.HILInitialize_Card,
             helicopter_exercise4_P.HILInitialize_POChannels,
             num_final_pwm_outputs,
             &helicopter_exercise4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopter_exercise4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopter_exercise4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopter_exercise4_DW.HILInitialize_Card);
    hil_close(helicopter_exercise4_DW.HILInitialize_Card);
    helicopter_exercise4_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopter_exercise4_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "task4_X.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_exercise4_M,
                          "Error closing MAT-file task4_X.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopter_exercise4_M,
                          "Error reopening MAT-file task4_X.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 8 + 1,
           helicopter_exercise4_DW.ToFile_IWORK.Count,
           "pc_ec_lambda_r_p_pdot_e_edot")) {
        rtmSetErrorStatus(helicopter_exercise4_M,
                          "Error writing header for pc_ec_lambda_r_p_pdot_e_edot to MAT-file task4_X.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopter_exercise4_M,
                          "Error closing MAT-file task4_X.mat");
        return;
      }

      helicopter_exercise4_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopter_exercise4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopter_exercise4_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopter_exercise4_initialize();
}

void MdlTerminate(void)
{
  helicopter_exercise4_terminate();
}

/* Registration function */
RT_MODEL_helicopter_exercise4_T *helicopter_exercise4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopter_exercise4_P.Integrator_UpperSat = rtInf;
  helicopter_exercise4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopter_exercise4_M, 0,
                sizeof(RT_MODEL_helicopter_exercise4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopter_exercise4_M->solverInfo,
                          &helicopter_exercise4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopter_exercise4_M->solverInfo, &rtmGetTPtr
                (helicopter_exercise4_M));
    rtsiSetStepSizePtr(&helicopter_exercise4_M->solverInfo,
                       &helicopter_exercise4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopter_exercise4_M->solverInfo,
                 &helicopter_exercise4_M->derivs);
    rtsiSetContStatesPtr(&helicopter_exercise4_M->solverInfo, (real_T **)
                         &helicopter_exercise4_M->contStates);
    rtsiSetNumContStatesPtr(&helicopter_exercise4_M->solverInfo,
      &helicopter_exercise4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopter_exercise4_M->solverInfo,
      &helicopter_exercise4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopter_exercise4_M->solverInfo,
      &helicopter_exercise4_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopter_exercise4_M->solverInfo,
      &helicopter_exercise4_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopter_exercise4_M->solverInfo,
                          (&rtmGetErrorStatus(helicopter_exercise4_M)));
    rtsiSetRTModelPtr(&helicopter_exercise4_M->solverInfo,
                      helicopter_exercise4_M);
  }

  rtsiSetSimTimeStep(&helicopter_exercise4_M->solverInfo, MAJOR_TIME_STEP);
  helicopter_exercise4_M->intgData.f[0] = helicopter_exercise4_M->odeF[0];
  helicopter_exercise4_M->contStates = ((real_T *) &helicopter_exercise4_X);
  rtsiSetSolverData(&helicopter_exercise4_M->solverInfo, (void *)
                    &helicopter_exercise4_M->intgData);
  rtsiSetSolverName(&helicopter_exercise4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopter_exercise4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopter_exercise4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopter_exercise4_M->Timing.sampleTimes =
      (&helicopter_exercise4_M->Timing.sampleTimesArray[0]);
    helicopter_exercise4_M->Timing.offsetTimes =
      (&helicopter_exercise4_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopter_exercise4_M->Timing.sampleTimes[0] = (0.0);
    helicopter_exercise4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopter_exercise4_M->Timing.offsetTimes[0] = (0.0);
    helicopter_exercise4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopter_exercise4_M, &helicopter_exercise4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopter_exercise4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopter_exercise4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopter_exercise4_M, 35.0);
  helicopter_exercise4_M->Timing.stepSize0 = 0.002;
  helicopter_exercise4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopter_exercise4_M->Sizes.checksums[0] = (1317430043U);
  helicopter_exercise4_M->Sizes.checksums[1] = (2379873441U);
  helicopter_exercise4_M->Sizes.checksums[2] = (2375125675U);
  helicopter_exercise4_M->Sizes.checksums[3] = (2049113307U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopter_exercise4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopter_exercise4_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopter_exercise4_M->extModeInfo,
      &helicopter_exercise4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopter_exercise4_M->extModeInfo,
                        helicopter_exercise4_M->Sizes.checksums);
    rteiSetTPtr(helicopter_exercise4_M->extModeInfo, rtmGetTPtr
                (helicopter_exercise4_M));
  }

  helicopter_exercise4_M->solverInfoPtr = (&helicopter_exercise4_M->solverInfo);
  helicopter_exercise4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopter_exercise4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopter_exercise4_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopter_exercise4_M->blockIO = ((void *) &helicopter_exercise4_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopter_exercise4_B.Gain1_e[i] = 0.0;
    }

    for (i = 0; i < 8; i++) {
      helicopter_exercise4_B.TmpSignalConversionAtToFileInpo[i] = 0.0;
    }

    helicopter_exercise4_B.Gain1 = 0.0;
    helicopter_exercise4_B.TravelCounttorad = 0.0;
    helicopter_exercise4_B.Gain = 0.0;
    helicopter_exercise4_B.Sum3 = 0.0;
    helicopter_exercise4_B.Gain_d = 0.0;
    helicopter_exercise4_B.PitchCounttorad = 0.0;
    helicopter_exercise4_B.Gain_i = 0.0;
    helicopter_exercise4_B.Gain_b = 0.0;
    helicopter_exercise4_B.ElevationCounttorad = 0.0;
    helicopter_exercise4_B.Gain_e = 0.0;
    helicopter_exercise4_B.Sum = 0.0;
    helicopter_exercise4_B.Gain_dg = 0.0;
    helicopter_exercise4_B.Sum4 = 0.0;
    helicopter_exercise4_B.Sum8 = 0.0;
    helicopter_exercise4_B.Gain_l = 0.0;
    helicopter_exercise4_B.BackmotorSaturation = 0.0;
    helicopter_exercise4_B.FrontmotorSaturation = 0.0;
    helicopter_exercise4_B.In1 = 0.0;
  }

  /* parameters */
  helicopter_exercise4_M->defaultParam = ((real_T *)&helicopter_exercise4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopter_exercise4_X;
    helicopter_exercise4_M->contStates = (x);
    (void) memset((void *)&helicopter_exercise4_X, 0,
                  sizeof(X_helicopter_exercise4_T));
  }

  /* states (dwork) */
  helicopter_exercise4_M->dwork = ((void *) &helicopter_exercise4_DW);
  (void) memset((void *)&helicopter_exercise4_DW, 0,
                sizeof(DW_helicopter_exercise4_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_exercise4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_exercise4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_exercise4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_exercise4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_exercise4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_exercise4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_exercise4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopter_exercise4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopter_exercise4_DW.TimeStampA = 0.0;
  helicopter_exercise4_DW.LastUAtTimeA = 0.0;
  helicopter_exercise4_DW.TimeStampB = 0.0;
  helicopter_exercise4_DW.LastUAtTimeB = 0.0;
  helicopter_exercise4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopter_exercise4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopter_exercise4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopter_exercise4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopter_exercise4_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopter_exercise4_M->Sizes.numY = (0);/* Number of model outputs */
  helicopter_exercise4_M->Sizes.numU = (0);/* Number of model inputs */
  helicopter_exercise4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopter_exercise4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopter_exercise4_M->Sizes.numBlocks = (71);/* Number of blocks */
  helicopter_exercise4_M->Sizes.numBlockIO = (20);/* Number of block outputs */
  helicopter_exercise4_M->Sizes.numBlockPrms = (159);/* Sum of parameter "widths" */
  return helicopter_exercise4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
