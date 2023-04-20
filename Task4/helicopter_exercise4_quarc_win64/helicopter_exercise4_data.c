/*
 * helicopter_exercise4_data.c
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

/* Block parameters (default storage) */
P_helicopter_exercise4_T helicopter_exercise4_P = {
  /* Variable: K
   * Referenced by: '<Root>/Multiply'
   */
  { -7.2920421431248466, -1.0936428085242412E-13, -13.325076396260869,
    -1.3590666810341294E-13, 4.9271232069402124, 3.6898654452170163E-14,
    1.1785215152140602, 5.6981254483540285E-15, -1.1213243701897788E-14,
    13.376882848904573, -2.5059675942833262E-15, 10.540306908780428 },

  /* Variable: K_ed
   * Referenced by: '<S4>/K_ed'
   */
  13.658171933401293,

  /* Variable: K_ei
   * Referenced by: '<S4>/K_ei'
   */
  0.34145429833503238,

  /* Variable: K_ep
   * Referenced by: '<S4>/K_ep'
   */
  3.4145429833503234,

  /* Variable: K_pd
   * Referenced by: '<S6>/K_pd'
   */
  6.4298470948012243,

  /* Variable: K_pp
   * Referenced by: '<S6>/K_pp'
   */
  5.7868623853211014,

  /* Variable: Vd_ff
   * Referenced by: '<Root>/Vd_bias'
   */
  0.1,

  /* Variable: Vs_ff
   * Referenced by: '<Root>/Vs_bias'
   */
  7.73,

  /* Variable: elevation_gain
   * Referenced by: '<S5>/Elevation_gain'
   */
  1.0,

  /* Variable: travel_gain
   * Referenced by: '<S5>/Travel_gain'
   */
  1.0,

  /* Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S5>/HIL Write Analog'
   */
  { 0U, 1U },

  /* Expression: set_other_outputs_at_terminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_out
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_start
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_in
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: final_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: final_pwm_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: analog_input_maximums
   * Referenced by: '<Root>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_input_minimums
   * Referenced by: '<Root>/HIL Initialize'
   */
  -10.0,

  /* Expression: analog_output_maximums
   * Referenced by: '<Root>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_output_minimums
   * Referenced by: '<Root>/HIL Initialize'
   */
  -10.0,

  /* Expression: initial_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: pwm_frequency
   * Referenced by: '<Root>/HIL Initialize'
   */
  24305.934065934067,

  /* Expression: pwm_leading_deadband
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: pwm_trailing_deadband
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: initial_pwm_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_pwm_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Constant'
   */
  0.0,

  /* Expression: pi/180
   * Referenced by: '<S3>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 180
   * Referenced by: '<Root>/travel_offset [deg]'
   */
  180.0,

  /* Expression: 2*pi/8192
   * Referenced by: '<S5>/Travel: Count to rad'
   */
  0.00076699039394282058,

  /* Expression: 180/pi
   * Referenced by: '<S13>/Gain'
   */
  57.295779513082323,

  /* Computed Parameter: TravelTransferFcn_A
   * Referenced by: '<S5>/Travel: Transfer Fcn'
   */
  -10.0,

  /* Computed Parameter: TravelTransferFcn_C
   * Referenced by: '<S5>/Travel: Transfer Fcn'
   */
  -100.0,

  /* Computed Parameter: TravelTransferFcn_D
   * Referenced by: '<S5>/Travel: Transfer Fcn'
   */
  10.0,

  /* Expression: 180/pi
   * Referenced by: '<S14>/Gain'
   */
  57.295779513082323,

  /* Expression: 2*pi /4096
   * Referenced by: '<S5>/Pitch: Count to rad'
   */
  0.0015339807878856412,

  /* Expression: 180/pi
   * Referenced by: '<S10>/Gain'
   */
  57.295779513082323,

  /* Computed Parameter: PitchTransferFcn_A
   * Referenced by: '<S5>/Pitch: Transfer Fcn'
   */
  -30.0,

  /* Computed Parameter: PitchTransferFcn_C
   * Referenced by: '<S5>/Pitch: Transfer Fcn'
   */
  -900.0,

  /* Computed Parameter: PitchTransferFcn_D
   * Referenced by: '<S5>/Pitch: Transfer Fcn'
   */
  30.0,

  /* Expression: 180/pi
   * Referenced by: '<S11>/Gain'
   */
  57.295779513082323,

  /* Expression: -2 * pi /4096
   * Referenced by: '<S5>/Elevation: Count to rad'
   */
  -0.0015339807878856412,

  /* Expression: 180/pi
   * Referenced by: '<S8>/Gain'
   */
  57.295779513082323,

  /* Expression: -30
   * Referenced by: '<Root>/elavation_offset [deg]'
   */
  -30.0,

  /* Computed Parameter: ElevationTransferFcn_A
   * Referenced by: '<S5>/Elevation: Transfer Fcn'
   */
  -10.0,

  /* Computed Parameter: ElevationTransferFcn_C
   * Referenced by: '<S5>/Elevation: Transfer Fcn'
   */
  -100.0,

  /* Computed Parameter: ElevationTransferFcn_D
   * Referenced by: '<S5>/Elevation: Transfer Fcn'
   */
  10.0,

  /* Expression: 180/pi
   * Referenced by: '<S9>/Gain'
   */
  57.295779513082323,

  /* Expression: pi/180
   * Referenced by: '<S2>/Gain1'
   */
  0.017453292519943295,

  /* Expression: 0
   * Referenced by: '<Root>/elevation_ref'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S4>/Integrator'
   */
  0.0,

  /* Expression: inf
   * Referenced by: '<S4>/Integrator'
   */
  0.0,

  /* Expression: -inf
   * Referenced by: '<S4>/Integrator'
   */
  0.0,

  /* Expression: 0.5
   * Referenced by: '<S1>/Back gain'
   */
  0.5,

  /* Expression: 0.5
   * Referenced by: '<S1>/Front gain'
   */
  0.5,

  /* Expression: 180/pi
   * Referenced by: '<S12>/Gain'
   */
  57.295779513082323,

  /* Expression: 5
   * Referenced by: '<S5>/Back motor: Saturation'
   */
  5.0,

  /* Expression: -5
   * Referenced by: '<S5>/Back motor: Saturation'
   */
  -5.0,

  /* Expression: 5
   * Referenced by: '<S5>/Front motor: Saturation'
   */
  5.0,

  /* Expression: -5
   * Referenced by: '<S5>/Front motor: Saturation'
   */
  -5.0,

  /* Computed Parameter: HILInitialize_CKChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0, 1, 2 },

  /* Computed Parameter: HILInitialize_DOWatchdog
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIInitial
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POModes
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POConfiguration
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POAlignment
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POPolarity
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILReadEncoderTimebase_Clock
   * Referenced by: '<S5>/HIL Read Encoder Timebase'
   */
  0,

  /* Computed Parameter: HILInitialize_AIChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_AOChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_EIChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_EIQuadrature
   * Referenced by: '<Root>/HIL Initialize'
   */
  4U,

  /* Computed Parameter: HILInitialize_POChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILReadEncoderTimebase_Channels
   * Referenced by: '<S5>/HIL Read Encoder Timebase'
   */
  { 0U, 1U, 2U },

  /* Computed Parameter: HILReadEncoderTimebase_SamplesI
   * Referenced by: '<S5>/HIL Read Encoder Timebase'
   */
  500U,

  /* Computed Parameter: HILInitialize_Active
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_CKEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AIPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AIPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_AOEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_AOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_EIPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_EIStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_POEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_OOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_DOFinal
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_DOInitial
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILReadEncoderTimebase_Active
   * Referenced by: '<S5>/HIL Read Encoder Timebase'
   */
  1,

  /* Computed Parameter: HILWriteAnalog_Active
   * Referenced by: '<S5>/HIL Write Analog'
   */
  0,

  /* Computed Parameter: HILReadEncoderTimebase_Overflow
   * Referenced by: '<S5>/HIL Read Encoder Timebase'
   */
  1U
};
