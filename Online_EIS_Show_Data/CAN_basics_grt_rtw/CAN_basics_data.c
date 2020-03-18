/*
 * CAN_basics_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "CAN_basics".
 *
 * Model version              : 1.138
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Wed Jan 15 09:40:53 2020
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "CAN_basics.h"
#include "CAN_basics_private.h"

/* Block parameters (default storage) */
P_CAN_basics_T CAN_basics_P = {
  /* Expression: 32767
   * Referenced by: '<S5>/Constant9'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S5>/Multiply9'
   */
  5.0,

  /* Expression: 32767
   * Referenced by: '<S5>/Constant8'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S5>/Multiply8'
   */
  5.0,

  /* Expression: 32767
   * Referenced by: '<S5>/Constant7'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S5>/Multiply7'
   */
  5.0,

  /* Expression: 32767
   * Referenced by: '<S5>/Constant6'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S5>/Multiply6'
   */
  5.0,

  /* Expression: 32767
   * Referenced by: '<S5>/Constant5'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S5>/Multiply5'
   */
  5.0,

  /* Expression: 32767
   * Referenced by: '<S5>/Constant4'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S5>/Multiply4'
   */
  5.0,

  /* Expression: 32767
   * Referenced by: '<S5>/Constant3'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S5>/Multiply3'
   */
  5.0,

  /* Expression: 32767
   * Referenced by: '<S5>/Constant2'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S5>/Multiply2'
   */
  5.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch4'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch5'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch6'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch7'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch8'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S5>/Switch9'
   */
  0.0,

  /* Expression: 32767
   * Referenced by: '<S6>/Constant9'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S6>/Multiply9'
   */
  5.0,

  /* Expression: 32767
   * Referenced by: '<S6>/Constant2'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S6>/Multiply2'
   */
  5.0,

  /* Expression: 0
   * Referenced by: '<S6>/Switch9'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S6>/Switch2'
   */
  0.0,

  /* Computed Parameter: Merge_InitialOutput
   * Referenced by: '<S3>/Merge'
   */
  0.0,

  /* Computed Parameter: Merge1_InitialOutput
   * Referenced by: '<S3>/Merge1'
   */
  0.0,

  /* Computed Parameter: Merge2_InitialOutput
   * Referenced by: '<S3>/Merge2'
   */
  0.0,

  /* Computed Parameter: Merge3_InitialOutput
   * Referenced by: '<S3>/Merge3'
   */
  0.0,

  /* Computed Parameter: Merge4_InitialOutput
   * Referenced by: '<S3>/Merge4'
   */
  0.0,

  /* Computed Parameter: Merge5_InitialOutput
   * Referenced by: '<S3>/Merge5'
   */
  0.0,

  /* Computed Parameter: Merge6_InitialOutput
   * Referenced by: '<S3>/Merge6'
   */
  0.0,

  /* Computed Parameter: Merge7_InitialOutput
   * Referenced by: '<S3>/Merge7'
   */
  0.0,

  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S4>/Out1'
   */
  0.0,

  /* Computed Parameter: Out2_Y0
   * Referenced by: '<S4>/Out2'
   */
  0.0,

  /* Expression: 32767
   * Referenced by: '<S4>/Constant1'
   */
  32767.0,

  /* Expression: 32767
   * Referenced by: '<S4>/Constant2'
   */
  32767.0,

  /* Expression: 5
   * Referenced by: '<S4>/Multiply1'
   */
  5.0,

  /* Expression: 5
   * Referenced by: '<S4>/Multiply2'
   */
  5.0,

  /* Expression: 5
   * Referenced by: '<S7>/Constant'
   */
  5.0,

  /* Expression: 65534
   * Referenced by: '<S7>/Multiply'
   */
  65534.0,

  /* Expression: 5
   * Referenced by: '<S7>/Constant1'
   */
  5.0,

  /* Expression: 65534
   * Referenced by: '<S7>/Multiply1'
   */
  65534.0,

  /* Expression: 5
   * Referenced by: '<S8>/Constant'
   */
  5.0,

  /* Expression: 65534
   * Referenced by: '<S8>/Multiply'
   */
  65534.0,

  /* Expression: 5
   * Referenced by: '<S8>/Constant1'
   */
  5.0,

  /* Expression: 65534
   * Referenced by: '<S8>/Multiply1'
   */
  65534.0,

  /* Expression: 1
   * Referenced by: '<S1>/Constant'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S1>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S2>/Amp min'
   */
  0.0,

  /* Expression: 2.399014778325123
   * Referenced by: '<S2>/Amp max'
   */
  2.3990147783251232,

  /* Expression: 1
   * Referenced by: '<S2>/Next F'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/Constant4'
   */
  1.0,

  /* Computed Parameter: Output_Y0
   * Referenced by: '<S4>/Output'
   */
  0U,

  /* Computed Parameter: Output1_Y0
   * Referenced by: '<S4>/Output1'
   */
  0U,

  /* Computed Parameter: Frequency_Value
   * Referenced by: '<S2>/Frequency'
   */
  1000U,

  /* Computed Parameter: Period_Value
   * Referenced by: '<S2>/Period'
   */
  20U
};
