/*
 * CAN_basics.c
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

/* Block signals (default storage) */
B_CAN_basics_T CAN_basics_B;

/* Block states (default storage) */
DW_CAN_basics_T CAN_basics_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_CAN_basics_T CAN_basics_PrevZCX;

/* Real-time model */
RT_MODEL_CAN_basics_T CAN_basics_M_;
RT_MODEL_CAN_basics_T *const CAN_basics_M = &CAN_basics_M_;

/* Model step function */
void CAN_basics_step(void)
{
  char_T *sErr;
  void *outputMsgRef;
  int32_T isMsgAvailable;
  int32_T isMsgReceived;
  int32_T isMsgAvailable_0;
  int32_T isMsgReceived_0;
  ZCEventType zcEvent;
  real_T tmp;

  /* S-Function (svntcanreceive): '<S1>/CAN Receive' */
  sErr = GetErrorBuffer(&CAN_basics_DW.CANReceive_CANReceive[0U]);
  isMsgAvailable = 1;
  isMsgReceived = 0;
  outputMsgRef = &CAN_basics_B.CANdatain;
  while (isMsgAvailable == 1) {
    LibOutputs_CANReceive(&CAN_basics_DW.CANReceive_CANReceive[0U], outputMsgRef,
                          2, &isMsgReceived, &isMsgAvailable);
    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    if (isMsgReceived == 1) {
      isMsgReceived = 0;

      /* Outputs for Function Call SubSystem: '<S1>/Function-Call Subsystem' */
      /* If: '<S3>/If' incorporates:
       *  Constant: '<S1>/Constant1'
       */
      if (CAN_basics_P.Constant1_Value_k > 0.0) {
        /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
         *  ActionPort: '<S5>/Action Port'
         */
        /* S-Function (scanunpack): '<S5>/CAN Unpack' */
        {
          /* S-Function (scanunpack): '<S5>/CAN Unpack' */
          if ((2 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((600 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack_l[0],
                            CAN_basics_B.CANdatain.Data,
                            2 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S5>/Byte Unpack' */

        /* Unpack: <S5>/Byte Unpack */
        (void) memcpy(&CAN_basics_B.ByteUnpack, &CAN_basics_B.CANUnpack_l[0],
                      2);

        /* S-Function (scanunpack): '<S5>/CAN Unpack1' */
        {
          /* S-Function (scanunpack): '<S5>/CAN Unpack1' */
          if ((2 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((601 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack1_g[0],
                            CAN_basics_B.CANdatain.Data,
                            2 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S5>/Byte Unpack1' */

        /* Unpack: <S5>/Byte Unpack1 */
        (void) memcpy(&CAN_basics_B.ByteUnpack1_e, &CAN_basics_B.CANUnpack1_g[0],
                      2);

        /* S-Function (scanunpack): '<S5>/CAN Unpack2' */
        {
          /* S-Function (scanunpack): '<S5>/CAN Unpack2' */
          if ((2 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((602 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack2_f[0],
                            CAN_basics_B.CANdatain.Data,
                            2 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S5>/Byte Unpack2' */

        /* Unpack: <S5>/Byte Unpack2 */
        (void) memcpy(&CAN_basics_B.ByteUnpack2_e, &CAN_basics_B.CANUnpack2_f[0],
                      2);

        /* S-Function (scanunpack): '<S5>/CAN Unpack3' */
        {
          /* S-Function (scanunpack): '<S5>/CAN Unpack3' */
          if ((2 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((603 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack3[0],
                            CAN_basics_B.CANdatain.Data,
                            2 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S5>/Byte Unpack3' */

        /* Unpack: <S5>/Byte Unpack3 */
        (void) memcpy(&CAN_basics_B.ByteUnpack3, &CAN_basics_B.CANUnpack3[0],
                      2);

        /* S-Function (scanunpack): '<S5>/CAN Unpack4' */
        {
          /* S-Function (scanunpack): '<S5>/CAN Unpack4' */
          if ((2 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((604 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack4[0],
                            CAN_basics_B.CANdatain.Data,
                            2 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S5>/Byte Unpack4' */

        /* Unpack: <S5>/Byte Unpack4 */
        (void) memcpy(&CAN_basics_B.ByteUnpack4, &CAN_basics_B.CANUnpack4[0],
                      2);

        /* S-Function (scanunpack): '<S5>/CAN Unpack5' */
        {
          /* S-Function (scanunpack): '<S5>/CAN Unpack5' */
          if ((2 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((605 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack5[0],
                            CAN_basics_B.CANdatain.Data,
                            2 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S5>/Byte Unpack5' */

        /* Unpack: <S5>/Byte Unpack5 */
        (void) memcpy(&CAN_basics_B.ByteUnpack5, &CAN_basics_B.CANUnpack5[0],
                      2);

        /* S-Function (scanunpack): '<S5>/CAN Unpack6' */
        {
          /* S-Function (scanunpack): '<S5>/CAN Unpack6' */
          if ((2 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((606 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack6[0],
                            CAN_basics_B.CANdatain.Data,
                            2 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S5>/Byte Unpack6' */

        /* Unpack: <S5>/Byte Unpack6 */
        (void) memcpy(&CAN_basics_B.ByteUnpack6, &CAN_basics_B.CANUnpack6[0],
                      2);

        /* S-Function (scanunpack): '<S5>/CAN Unpack7' */
        {
          /* S-Function (scanunpack): '<S5>/CAN Unpack7' */
          if ((2 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((607 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack7[0],
                            CAN_basics_B.CANdatain.Data,
                            2 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S5>/Byte Unpack7' */

        /* Unpack: <S5>/Byte Unpack7 */
        (void) memcpy(&CAN_basics_B.ByteUnpack7, &CAN_basics_B.CANUnpack7[0],
                      2);

        /* Switch: '<S5>/Switch2' incorporates:
         *  Constant: '<S1>/Constant'
         *  Constant: '<S5>/Constant2'
         *  Gain: '<S5>/Multiply2'
         *  Product: '<S5>/Divide2'
         */
        if (CAN_basics_P.Constant_Value_j > CAN_basics_P.Switch2_Threshold) {
          CAN_basics_B.A1 = (real_T)CAN_basics_B.ByteUnpack1_e /
            CAN_basics_P.Constant2_Value * CAN_basics_P.Multiply2_Gain;
        } else {
          CAN_basics_B.A1 = CAN_basics_B.ByteUnpack1_e;
        }

        /* End of Switch: '<S5>/Switch2' */

        /* Switch: '<S5>/Switch9' incorporates:
         *  Constant: '<S1>/Constant'
         *  Constant: '<S5>/Constant9'
         *  Gain: '<S5>/Multiply9'
         *  Product: '<S5>/Divide9'
         */
        if (CAN_basics_P.Constant_Value_j > CAN_basics_P.Switch9_Threshold) {
          CAN_basics_B.A0 = (real_T)CAN_basics_B.ByteUnpack /
            CAN_basics_P.Constant9_Value * CAN_basics_P.Multiply9_Gain;
        } else {
          CAN_basics_B.A0 = CAN_basics_B.ByteUnpack;
        }

        /* End of Switch: '<S5>/Switch9' */
        /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
      } else {
        /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem1' incorporates:
         *  ActionPort: '<S6>/Action Port'
         */
        /* S-Function (scanunpack): '<S6>/CAN Unpack1' */
        {
          /* S-Function (scanunpack): '<S6>/CAN Unpack1' */
          if ((8 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((601 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack1_e[0],
                            CAN_basics_B.CANdatain.Data,
                            8 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S6>/Byte Unpack1' */

        /* Unpack: <S6>/Byte Unpack1 */
        (void) memcpy(&CAN_basics_B.ByteUnpack1[0], &CAN_basics_B.CANUnpack1_e[0],
                      8);

        /* S-Function (scanunpack): '<S6>/CAN Unpack' */
        {
          /* S-Function (scanunpack): '<S6>/CAN Unpack' */
          if ((8 == CAN_basics_B.CANdatain.Length) && (CAN_basics_B.CANdatain.ID
               != INVALID_CAN_ID) ) {
            if ((600 == CAN_basics_B.CANdatain.ID) && (0U ==
                 CAN_basics_B.CANdatain.Extended) ) {
              (void) memcpy(&CAN_basics_B.CANUnpack[0],
                            CAN_basics_B.CANdatain.Data,
                            8 * sizeof(uint8_T));
            }
          }
        }

        /* S-Function (byte2any): '<S6>/Byte Unpack2' */

        /* Unpack: <S6>/Byte Unpack2 */
        (void) memcpy(&CAN_basics_B.ByteUnpack2[0], &CAN_basics_B.CANUnpack[0],
                      8);

        /* Switch: '<S6>/Switch9' incorporates:
         *  Constant: '<S1>/Constant'
         */
        if (CAN_basics_P.Constant_Value_j > CAN_basics_P.Switch9_Threshold_k) {
          /* SignalConversion: '<S6>/OutportBufferForOutput9' incorporates:
           *  Constant: '<S6>/Constant9'
           *  Gain: '<S6>/Multiply9'
           *  Product: '<S6>/Divide9'
           */
          CAN_basics_B.A0 = (real_T)CAN_basics_B.ByteUnpack2[0] /
            CAN_basics_P.Constant9_Value_b * CAN_basics_P.Multiply9_Gain_a;

          /* SignalConversion: '<S6>/OutportBufferForOutput2' incorporates:
           *  Constant: '<S6>/Constant9'
           *  Gain: '<S6>/Multiply9'
           *  Product: '<S6>/Divide9'
           */
          CAN_basics_B.A1 = (real_T)CAN_basics_B.ByteUnpack2[1] /
            CAN_basics_P.Constant9_Value_b * CAN_basics_P.Multiply9_Gain_a;
        } else {
          /* SignalConversion: '<S6>/OutportBufferForOutput9' */
          CAN_basics_B.A0 = CAN_basics_B.ByteUnpack2[0];

          /* SignalConversion: '<S6>/OutportBufferForOutput2' */
          CAN_basics_B.A1 = CAN_basics_B.ByteUnpack2[1];
        }

        /* End of Switch: '<S6>/Switch9' */
        /* End of Outputs for SubSystem: '<S3>/If Action Subsystem1' */
      }

      /* End of If: '<S3>/If' */
      /* End of Outputs for SubSystem: '<S1>/Function-Call Subsystem' */
    }
  }

  /* End of Outputs for S-Function (svntcanreceive): '<S1>/CAN Receive' */
  /* S-Function (svntcanreceive): '<S1>/CAN Receive1' */
  sErr = GetErrorBuffer(&CAN_basics_DW.CANReceive1_CANReceive[0U]);
  isMsgAvailable_0 = 1;
  isMsgReceived_0 = 0;
  outputMsgRef = &CAN_basics_B.CANdatain_f;
  while (isMsgAvailable_0 == 1) {
    LibOutputs_CANReceive(&CAN_basics_DW.CANReceive1_CANReceive[0U],
                          outputMsgRef, 2, &isMsgReceived_0, &isMsgAvailable_0);
    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    if (isMsgReceived_0 == 1) {
      isMsgReceived_0 = 0;

      /* Outputs for Function Call SubSystem: '<S1>/Function-Call Subsystem1' */
      /* S-Function (scanunpack): '<S4>/CAN Unpack2' */
      {
        /* S-Function (scanunpack): '<S4>/CAN Unpack2' */
        if ((8 == CAN_basics_B.CANdatain_f.Length) &&
            (CAN_basics_B.CANdatain_f.ID != INVALID_CAN_ID) ) {
          if ((257 == CAN_basics_B.CANdatain_f.ID) && (0U ==
               CAN_basics_B.CANdatain_f.Extended) ) {
            (void) memcpy(&CAN_basics_B.CANUnpack2[0],
                          CAN_basics_B.CANdatain_f.Data,
                          8 * sizeof(uint8_T));
          }
        }
      }

      /* S-Function (byte2any): '<S4>/Byte Unpack1' */

      /* Unpack: <S4>/Byte Unpack1 */
      (void) memcpy(&CAN_basics_B.Frequencydata_int16[0],
                    &CAN_basics_B.CANUnpack2[0],
                    8);

      /* S-Function (scanunpack): '<S4>/CAN Unpack1' */
      {
        /* S-Function (scanunpack): '<S4>/CAN Unpack1' */
        if ((8 == CAN_basics_B.CANdatain_f.Length) &&
            (CAN_basics_B.CANdatain_f.ID != INVALID_CAN_ID) ) {
          if ((256 == CAN_basics_B.CANdatain_f.ID) && (0U ==
               CAN_basics_B.CANdatain_f.Extended) ) {
            (void) memcpy(&CAN_basics_B.CANUnpack1[0],
                          CAN_basics_B.CANdatain_f.Data,
                          8 * sizeof(uint8_T));
          }
        }
      }

      /* S-Function (byte2any): '<S4>/Byte Unpack2' */

      /* Unpack: <S4>/Byte Unpack2 */
      (void) memcpy(&CAN_basics_B.Timedata_int16[0], &CAN_basics_B.CANUnpack1[0],
                    8);

      /* Gain: '<S4>/Multiply1' incorporates:
       *  Constant: '<S4>/Constant1'
       *  Product: '<S4>/Divide1'
       */
      CAN_basics_B.Timedata_double[0] = (real_T)CAN_basics_B.Timedata_int16[0] /
        CAN_basics_P.Constant1_Value * CAN_basics_P.Multiply1_Gain;

      /* Gain: '<S4>/Multiply2' incorporates:
       *  Constant: '<S4>/Constant2'
       *  Product: '<S4>/Divide2'
       */
      CAN_basics_B.Frequencydata_double[0] = (real_T)
        CAN_basics_B.Frequencydata_int16[0] / CAN_basics_P.Constant2_Value_h1 *
        CAN_basics_P.Multiply2_Gain_h;

      /* Gain: '<S4>/Multiply1' incorporates:
       *  Constant: '<S4>/Constant1'
       *  Product: '<S4>/Divide1'
       */
      CAN_basics_B.Timedata_double[1] = (real_T)CAN_basics_B.Timedata_int16[1] /
        CAN_basics_P.Constant1_Value * CAN_basics_P.Multiply1_Gain;

      /* Gain: '<S4>/Multiply2' incorporates:
       *  Constant: '<S4>/Constant2'
       *  Product: '<S4>/Divide2'
       */
      CAN_basics_B.Frequencydata_double[1] = (real_T)
        CAN_basics_B.Frequencydata_int16[1] / CAN_basics_P.Constant2_Value_h1 *
        CAN_basics_P.Multiply2_Gain_h;

      /* Gain: '<S4>/Multiply1' incorporates:
       *  Constant: '<S4>/Constant1'
       *  Product: '<S4>/Divide1'
       */
      CAN_basics_B.Timedata_double[2] = (real_T)CAN_basics_B.Timedata_int16[2] /
        CAN_basics_P.Constant1_Value * CAN_basics_P.Multiply1_Gain;

      /* Gain: '<S4>/Multiply2' incorporates:
       *  Constant: '<S4>/Constant2'
       *  Product: '<S4>/Divide2'
       */
      CAN_basics_B.Frequencydata_double[2] = (real_T)
        CAN_basics_B.Frequencydata_int16[2] / CAN_basics_P.Constant2_Value_h1 *
        CAN_basics_P.Multiply2_Gain_h;

      /* Gain: '<S4>/Multiply1' incorporates:
       *  Constant: '<S4>/Constant1'
       *  Product: '<S4>/Divide1'
       */
      CAN_basics_B.Timedata_double[3] = (real_T)CAN_basics_B.Timedata_int16[3] /
        CAN_basics_P.Constant1_Value * CAN_basics_P.Multiply1_Gain;

      /* Gain: '<S4>/Multiply2' incorporates:
       *  Constant: '<S4>/Constant2'
       *  Product: '<S4>/Divide2'
       */
      CAN_basics_B.Frequencydata_double[3] = (real_T)
        CAN_basics_B.Frequencydata_int16[3] / CAN_basics_P.Constant2_Value_h1 *
        CAN_basics_P.Multiply2_Gain_h;

      /* End of Outputs for SubSystem: '<S1>/Function-Call Subsystem1' */
    }
  }

  /* End of Outputs for S-Function (svntcanreceive): '<S1>/CAN Receive1' */
  /* Outputs for Triggered SubSystem: '<S2>/Function-Call Subsystem1' incorporates:
   *  TriggerPort: '<S7>/function'
   */
  /* Constant: '<S2>/Next F' */
  zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                     &CAN_basics_PrevZCX.FunctionCallSubsystem1_Trig_ZCE,
                     (CAN_basics_P.NextF_Value));
  if (zcEvent != NO_ZCEVENT) {
    /* S-Function (any2byte): '<S7>/Byte Pack5' incorporates:
     *  Constant: '<S2>/Frequency'
     */

    /* Pack: <S7>/Byte Pack5 */
    (void) memcpy(&CAN_basics_B.BytePack5_b[0], &CAN_basics_P.Frequency_Value,
                  2);

    /* Gain: '<S7>/Multiply' incorporates:
     *  Constant: '<S2>/Amp min'
     *  Constant: '<S7>/Constant'
     *  Product: '<S7>/Divide'
     */
    tmp = floor(CAN_basics_P.Ampmin_Value / CAN_basics_P.Constant_Value *
                CAN_basics_P.Multiply_Gain);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 65536.0);
    }

    CAN_basics_B.Multiply_i = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)
      -(int16_T)(uint16_T)-tmp : (int32_T)(uint16_T)tmp);

    /* End of Gain: '<S7>/Multiply' */

    /* S-Function (any2byte): '<S7>/Byte Pack1' */

    /* Pack: <S7>/Byte Pack1 */
    (void) memcpy(&CAN_basics_B.BytePack1_p[0], &CAN_basics_B.Multiply_i,
                  2);

    /* Gain: '<S7>/Multiply1' incorporates:
     *  Constant: '<S2>/Amp max'
     *  Constant: '<S7>/Constant1'
     *  Product: '<S7>/Divide1'
     */
    tmp = floor(CAN_basics_P.Ampmax_Value / CAN_basics_P.Constant1_Value_d *
                CAN_basics_P.Multiply1_Gain_l);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 65536.0);
    }

    CAN_basics_B.Multiply1_b = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)
      -(int16_T)(uint16_T)-tmp : (int32_T)(uint16_T)tmp);

    /* End of Gain: '<S7>/Multiply1' */

    /* S-Function (any2byte): '<S7>/Byte Pack3' */

    /* Pack: <S7>/Byte Pack3 */
    (void) memcpy(&CAN_basics_B.BytePack3_o[0], &CAN_basics_B.Multiply1_b,
                  2);

    /* S-Function (any2byte): '<S7>/Byte Pack4' incorporates:
     *  Constant: '<S2>/Period'
     */

    /* Pack: <S7>/Byte Pack4 */
    (void) memcpy(&CAN_basics_B.BytePack4_o[0], &CAN_basics_P.Period_Value,
                  2);

    /* S-Function (any2byte): '<S7>/Byte Pack6' */

    /* Pack: <S7>/Byte Pack6 */
    (void) memcpy(&CAN_basics_B.BytePack6_b[0], &CAN_basics_B.BytePack5_b[0],
                  2);
    (void) memcpy(&CAN_basics_B.BytePack6_b[2], &CAN_basics_B.BytePack1_p[0],
                  2);
    (void) memcpy(&CAN_basics_B.BytePack6_b[4], &CAN_basics_B.BytePack3_o[0],
                  2);
    (void) memcpy(&CAN_basics_B.BytePack6_b[6], &CAN_basics_B.BytePack4_o[0],
                  2);

    /* S-Function (scanpack): '<S7>/CAN Pack' */
    /* S-Function (scanpack): '<S7>/CAN Pack' */
    CAN_basics_B.CANPack_a.ID = 1U;
    CAN_basics_B.CANPack_a.Length = 8U;
    CAN_basics_B.CANPack_a.Extended = 0U;
    CAN_basics_B.CANPack_a.Remote = 0;
    CAN_basics_B.CANPack_a.Data[0] = 0;
    CAN_basics_B.CANPack_a.Data[1] = 0;
    CAN_basics_B.CANPack_a.Data[2] = 0;
    CAN_basics_B.CANPack_a.Data[3] = 0;
    CAN_basics_B.CANPack_a.Data[4] = 0;
    CAN_basics_B.CANPack_a.Data[5] = 0;
    CAN_basics_B.CANPack_a.Data[6] = 0;
    CAN_basics_B.CANPack_a.Data[7] = 0;

    {
      (void) memcpy((CAN_basics_B.CANPack_a.Data), &CAN_basics_B.BytePack6_b[0],
                    8 * sizeof(uint8_T));
    }

    /* S-Function (svntcantransmit): '<S7>/CAN Transmit' */
    sErr = GetErrorBuffer(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
    outputMsgRef = &CAN_basics_B.CANPack_a;
    LibOutputs_CANTransmit(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U],
      outputMsgRef, 1);
    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    /* End of S-Function (svntcantransmit): '<S7>/CAN Transmit' */
  }

  /* End of Outputs for SubSystem: '<S2>/Function-Call Subsystem1' */

  /* Outputs for Triggered SubSystem: '<S2>/Function-Call Subsystem3' incorporates:
   *  TriggerPort: '<S8>/function'
   */
  /* Constant: '<S2>/Constant4' */
  zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                     &CAN_basics_PrevZCX.FunctionCallSubsystem3_Trig_ZCE,
                     (CAN_basics_P.Constant4_Value_a));
  if (zcEvent != NO_ZCEVENT) {
    /* S-Function (any2byte): '<S8>/Byte Pack5' incorporates:
     *  Constant: '<S2>/Frequency'
     */

    /* Pack: <S8>/Byte Pack5 */
    (void) memcpy(&CAN_basics_B.BytePack5[0], &CAN_basics_P.Frequency_Value,
                  2);

    /* Gain: '<S8>/Multiply' incorporates:
     *  Constant: '<S2>/Amp min'
     *  Constant: '<S8>/Constant'
     *  Product: '<S8>/Divide'
     */
    tmp = floor(CAN_basics_P.Ampmin_Value / CAN_basics_P.Constant_Value_m *
                CAN_basics_P.Multiply_Gain_p);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 65536.0);
    }

    CAN_basics_B.Multiply = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)
      (uint16_T)-tmp : (int32_T)(uint16_T)tmp);

    /* End of Gain: '<S8>/Multiply' */

    /* S-Function (any2byte): '<S8>/Byte Pack1' */

    /* Pack: <S8>/Byte Pack1 */
    (void) memcpy(&CAN_basics_B.BytePack1[0], &CAN_basics_B.Multiply,
                  2);

    /* Gain: '<S8>/Multiply1' incorporates:
     *  Constant: '<S2>/Amp max'
     *  Constant: '<S8>/Constant1'
     *  Product: '<S8>/Divide1'
     */
    tmp = floor(CAN_basics_P.Ampmax_Value / CAN_basics_P.Constant1_Value_e *
                CAN_basics_P.Multiply1_Gain_i);
    if (rtIsNaN(tmp) || rtIsInf(tmp)) {
      tmp = 0.0;
    } else {
      tmp = fmod(tmp, 65536.0);
    }

    CAN_basics_B.Multiply1 = (uint16_T)(tmp < 0.0 ? (int32_T)(uint16_T)-(int16_T)
      (uint16_T)-tmp : (int32_T)(uint16_T)tmp);

    /* End of Gain: '<S8>/Multiply1' */

    /* S-Function (any2byte): '<S8>/Byte Pack3' */

    /* Pack: <S8>/Byte Pack3 */
    (void) memcpy(&CAN_basics_B.BytePack3[0], &CAN_basics_B.Multiply1,
                  2);

    /* S-Function (any2byte): '<S8>/Byte Pack4' incorporates:
     *  Constant: '<S2>/Period'
     */

    /* Pack: <S8>/Byte Pack4 */
    (void) memcpy(&CAN_basics_B.BytePack4[0], &CAN_basics_P.Period_Value,
                  2);

    /* S-Function (any2byte): '<S8>/Byte Pack6' */

    /* Pack: <S8>/Byte Pack6 */
    (void) memcpy(&CAN_basics_B.BytePack6[0], &CAN_basics_B.BytePack5[0],
                  2);
    (void) memcpy(&CAN_basics_B.BytePack6[2], &CAN_basics_B.BytePack1[0],
                  2);
    (void) memcpy(&CAN_basics_B.BytePack6[4], &CAN_basics_B.BytePack3[0],
                  2);
    (void) memcpy(&CAN_basics_B.BytePack6[6], &CAN_basics_B.BytePack4[0],
                  2);

    /* S-Function (scanpack): '<S8>/CAN Pack' */
    /* S-Function (scanpack): '<S8>/CAN Pack' */
    CAN_basics_B.CANPack.ID = 1U;
    CAN_basics_B.CANPack.Length = 8U;
    CAN_basics_B.CANPack.Extended = 0U;
    CAN_basics_B.CANPack.Remote = 0;
    CAN_basics_B.CANPack.Data[0] = 0;
    CAN_basics_B.CANPack.Data[1] = 0;
    CAN_basics_B.CANPack.Data[2] = 0;
    CAN_basics_B.CANPack.Data[3] = 0;
    CAN_basics_B.CANPack.Data[4] = 0;
    CAN_basics_B.CANPack.Data[5] = 0;
    CAN_basics_B.CANPack.Data[6] = 0;
    CAN_basics_B.CANPack.Data[7] = 0;

    {
      (void) memcpy((CAN_basics_B.CANPack.Data), &CAN_basics_B.BytePack6[0],
                    8 * sizeof(uint8_T));
    }

    /* S-Function (svntcantransmit): '<S8>/CAN Transmit' */
    sErr = GetErrorBuffer(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);
    outputMsgRef = &CAN_basics_B.CANPack;
    LibOutputs_CANTransmit(&CAN_basics_DW.CANTransmit_CANTransmit[0U],
      outputMsgRef, 1);
    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    /* End of S-Function (svntcantransmit): '<S8>/CAN Transmit' */
  }

  /* End of Outputs for SubSystem: '<S2>/Function-Call Subsystem3' */

  /* Matfile logging */
  rt_UpdateTXYLogVars(CAN_basics_M->rtwLogInfo, (&CAN_basics_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.2s, 0.0s] */
    if ((rtmGetTFinal(CAN_basics_M)!=-1) &&
        !((rtmGetTFinal(CAN_basics_M)-CAN_basics_M->Timing.taskTime0) >
          CAN_basics_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(CAN_basics_M, "Simulation finished");
    }
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
  if (!(++CAN_basics_M->Timing.clockTick0)) {
    ++CAN_basics_M->Timing.clockTickH0;
  }

  CAN_basics_M->Timing.taskTime0 = CAN_basics_M->Timing.clockTick0 *
    CAN_basics_M->Timing.stepSize0 + CAN_basics_M->Timing.clockTickH0 *
    CAN_basics_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void CAN_basics_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)CAN_basics_M, 0,
                sizeof(RT_MODEL_CAN_basics_T));
  rtmSetTFinal(CAN_basics_M, -1);
  CAN_basics_M->Timing.stepSize0 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    CAN_basics_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(CAN_basics_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(CAN_basics_M->rtwLogInfo, (NULL));
    rtliSetLogT(CAN_basics_M->rtwLogInfo, "tout");
    rtliSetLogX(CAN_basics_M->rtwLogInfo, "");
    rtliSetLogXFinal(CAN_basics_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(CAN_basics_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(CAN_basics_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(CAN_basics_M->rtwLogInfo, 0);
    rtliSetLogDecimation(CAN_basics_M->rtwLogInfo, 1);
    rtliSetLogY(CAN_basics_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(CAN_basics_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(CAN_basics_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &CAN_basics_B), 0,
                sizeof(B_CAN_basics_T));

  {
    CAN_basics_B.CANdatain = CAN_DATATYPE_GROUND;
    CAN_basics_B.CANdatain_f = CAN_DATATYPE_GROUND;
    CAN_basics_B.CANPack = CAN_DATATYPE_GROUND;
    CAN_basics_B.CANPack_a = CAN_DATATYPE_GROUND;
  }

  /* states (dwork) */
  (void) memset((void *)&CAN_basics_DW, 0,
                sizeof(DW_CAN_basics_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(CAN_basics_M->rtwLogInfo, 0.0, rtmGetTFinal
    (CAN_basics_M), CAN_basics_M->Timing.stepSize0, (&rtmGetErrorStatus
    (CAN_basics_M)));

  {
    char_T *sErr;
    int32_T bitParams[4];
    uint32_T stdIDs[8];
    uint32_T extIDs;
    real_T stdIDsStart;
    real_T stdIDsEnd;
    int32_T idMaskParams[4];
    int32_T bitParams_0[4];
    uint32_T stdIDs_0[2];
    uint32_T extIDs_0;
    real_T stdIDsStart_0;
    real_T stdIDsEnd_0;
    int32_T idMaskParams_0[4];
    int32_T bitParams_1[4];
    int32_T bitParams_2[4];

    /* Start for S-Function (svntcanreceive): '<S1>/CAN Receive' incorporates:
     *  SubSystem: '<S1>/Function-Call Subsystem'
     */
    /* Start for IfAction SubSystem: '<S3>/If Action Subsystem' */
    /* Start for S-Function (scanunpack): '<S5>/CAN Unpack' */

    /*-----------S-Function Block: <S5>/CAN Unpack -----------------*/

    /* Start for S-Function (scanunpack): '<S5>/CAN Unpack1' */

    /*-----------S-Function Block: <S5>/CAN Unpack1 -----------------*/

    /* Start for S-Function (scanunpack): '<S5>/CAN Unpack2' */

    /*-----------S-Function Block: <S5>/CAN Unpack2 -----------------*/

    /* Start for S-Function (scanunpack): '<S5>/CAN Unpack3' */

    /*-----------S-Function Block: <S5>/CAN Unpack3 -----------------*/

    /* Start for S-Function (scanunpack): '<S5>/CAN Unpack4' */

    /*-----------S-Function Block: <S5>/CAN Unpack4 -----------------*/

    /* Start for S-Function (scanunpack): '<S5>/CAN Unpack5' */

    /*-----------S-Function Block: <S5>/CAN Unpack5 -----------------*/

    /* Start for S-Function (scanunpack): '<S5>/CAN Unpack6' */

    /*-----------S-Function Block: <S5>/CAN Unpack6 -----------------*/

    /* Start for S-Function (scanunpack): '<S5>/CAN Unpack7' */

    /*-----------S-Function Block: <S5>/CAN Unpack7 -----------------*/

    /* End of Start for SubSystem: '<S3>/If Action Subsystem' */

    /* Start for IfAction SubSystem: '<S3>/If Action Subsystem1' */
    /* Start for S-Function (scanunpack): '<S6>/CAN Unpack1' */

    /*-----------S-Function Block: <S6>/CAN Unpack1 -----------------*/

    /* Start for S-Function (scanunpack): '<S6>/CAN Unpack' */

    /*-----------S-Function Block: <S6>/CAN Unpack -----------------*/

    /* End of Start for SubSystem: '<S3>/If Action Subsystem1' */
    sErr = GetErrorBuffer(&CAN_basics_DW.CANReceive_CANReceive[0U]);
    CreateHostLibrary("slhostlibcanreceive.dll",
                      &CAN_basics_DW.CANReceive_CANReceive[0U]);
    if (*sErr == 0) {
      bitParams[0U] = 1;
      bitParams[1U] = 4;
      bitParams[2U] = 3;
      bitParams[3U] = 1;
      stdIDs[0U] = 600U;
      stdIDs[1U] = 601U;
      stdIDs[2U] = 602U;
      stdIDs[3U] = 603U;
      stdIDs[4U] = 604U;
      stdIDs[5U] = 605U;
      stdIDs[6U] = 606U;
      stdIDs[7U] = 607U;
      extIDs = MAX_uint32_T;
      stdIDsStart = 600.0;
      stdIDsEnd = 607.0;
      idMaskParams[0U] = 600;
      idMaskParams[1U] = 2040;
      idMaskParams[2U] = 0;
      idMaskParams[3U] = 536870911;
      LibCreate_CANReceive(&CAN_basics_DW.CANReceive_CANReceive[0U], "vector",
                           "slvectorxlwrapper.dll", "VN1610", 3880, 55, 1, 1,
                           "canslconverter", "vectorxlplugin", 500000.0,
                           &bitParams[0U], 0, 1, &stdIDs[0U], 8, 2, &extIDs, 1,
                           &stdIDsStart, &stdIDsEnd, 1, &idMaskParams[0U], 0);
    }

    if (*sErr == 0) {
      LibStart(&CAN_basics_DW.CANReceive_CANReceive[0U]);
    }

    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    /* End of Start for S-Function (svntcanreceive): '<S1>/CAN Receive' */
    /* Start for S-Function (svntcanreceive): '<S1>/CAN Receive1' incorporates:
     *  SubSystem: '<S1>/Function-Call Subsystem1'
     */
    /* Start for S-Function (scanunpack): '<S4>/CAN Unpack2' */

    /*-----------S-Function Block: <S4>/CAN Unpack2 -----------------*/

    /* Start for S-Function (scanunpack): '<S4>/CAN Unpack1' */

    /*-----------S-Function Block: <S4>/CAN Unpack1 -----------------*/
    sErr = GetErrorBuffer(&CAN_basics_DW.CANReceive1_CANReceive[0U]);
    CreateHostLibrary("slhostlibcanreceive.dll",
                      &CAN_basics_DW.CANReceive1_CANReceive[0U]);
    if (*sErr == 0) {
      bitParams_0[0U] = 1;
      bitParams_0[1U] = 4;
      bitParams_0[2U] = 3;
      bitParams_0[3U] = 1;
      stdIDs_0[0U] = 256U;
      stdIDs_0[1U] = 257U;
      extIDs_0 = MAX_uint32_T;
      stdIDsStart_0 = 256.0;
      stdIDsEnd_0 = 257.0;
      idMaskParams_0[0U] = 256;
      idMaskParams_0[1U] = 2046;
      idMaskParams_0[2U] = 0;
      idMaskParams_0[3U] = 536870911;
      LibCreate_CANReceive(&CAN_basics_DW.CANReceive1_CANReceive[0U], "vector",
                           "slvectorxlwrapper.dll", "VN1610", 3880, 55, 1, 1,
                           "canslconverter", "vectorxlplugin", 500000.0,
                           &bitParams_0[0U], 0, 1, &stdIDs_0[0U], 2, 2,
                           &extIDs_0, 1, &stdIDsStart_0, &stdIDsEnd_0, 1,
                           &idMaskParams_0[0U], 0);
    }

    if (*sErr == 0) {
      LibStart(&CAN_basics_DW.CANReceive1_CANReceive[0U]);
    }

    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    /* End of Start for S-Function (svntcanreceive): '<S1>/CAN Receive1' */
    /* Start for S-Function (svntcantransmit): '<S7>/CAN Transmit' */
    sErr = GetErrorBuffer(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
    CreateHostLibrary("slhostlibcantransmit.dll",
                      &CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
    if (*sErr == 0) {
      bitParams_1[0U] = 1;
      bitParams_1[1U] = 4;
      bitParams_1[2U] = 3;
      bitParams_1[3U] = 1;
      LibCreate_CANTransmit(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U],
                            "vector", "slvectorxlwrapper.dll", "VN1610", 3880,
                            55, 1, 1, "canslconverter", "vectorxlplugin",
                            500000.0, &bitParams_1[0U], 0, 0, 1.0, 0);
    }

    if (*sErr == 0) {
      LibStart(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
    }

    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    /* End of Start for S-Function (svntcantransmit): '<S7>/CAN Transmit' */
    /* End of Start for SubSystem: '<S2>/Function-Call Subsystem1' */
    /* Start for S-Function (svntcantransmit): '<S8>/CAN Transmit' */
    sErr = GetErrorBuffer(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);
    CreateHostLibrary("slhostlibcantransmit.dll",
                      &CAN_basics_DW.CANTransmit_CANTransmit[0U]);
    if (*sErr == 0) {
      bitParams_2[0U] = 1;
      bitParams_2[1U] = 4;
      bitParams_2[2U] = 3;
      bitParams_2[3U] = 1;
      LibCreate_CANTransmit(&CAN_basics_DW.CANTransmit_CANTransmit[0U], "vector",
                            "slvectorxlwrapper.dll", "VN1610", 3880, 55, 1, 1,
                            "canslconverter", "vectorxlplugin", 500000.0,
                            &bitParams_2[0U], 0, 0, 1.0, 0);
    }

    if (*sErr == 0) {
      LibStart(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);
    }

    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    /* End of Start for S-Function (svntcantransmit): '<S8>/CAN Transmit' */
    /* End of Start for SubSystem: '<S2>/Function-Call Subsystem3' */
  }

  CAN_basics_PrevZCX.FunctionCallSubsystem1_Trig_ZCE = UNINITIALIZED_ZCSIG;
  CAN_basics_PrevZCX.FunctionCallSubsystem3_Trig_ZCE = UNINITIALIZED_ZCSIG;

  /* SystemInitialize for S-Function (svntcanreceive): '<S1>/CAN Receive' incorporates:
   *  SubSystem: '<S1>/Function-Call Subsystem'
   */
  /* SystemInitialize for Merge: '<S3>/Merge' */
  CAN_basics_B.A0 = CAN_basics_P.Merge_InitialOutput;

  /* SystemInitialize for Merge: '<S3>/Merge1' */
  CAN_basics_B.A1 = CAN_basics_P.Merge1_InitialOutput;

  /* End of SystemInitialize for S-Function (svntcanreceive): '<S1>/CAN Receive' */

  /* SystemInitialize for S-Function (svntcanreceive): '<S1>/CAN Receive1' incorporates:
   *  SubSystem: '<S1>/Function-Call Subsystem1'
   */
  /* SystemInitialize for Outport: '<S4>/Out1' */
  CAN_basics_B.Timedata_double[0] = CAN_basics_P.Out1_Y0;

  /* SystemInitialize for Outport: '<S4>/Output' */
  CAN_basics_B.Timedata_int16[0] = CAN_basics_P.Output_Y0;

  /* SystemInitialize for Outport: '<S4>/Out2' */
  CAN_basics_B.Frequencydata_double[0] = CAN_basics_P.Out2_Y0;

  /* SystemInitialize for Outport: '<S4>/Output1' */
  CAN_basics_B.Frequencydata_int16[0] = CAN_basics_P.Output1_Y0;

  /* SystemInitialize for Outport: '<S4>/Out1' */
  CAN_basics_B.Timedata_double[1] = CAN_basics_P.Out1_Y0;

  /* SystemInitialize for Outport: '<S4>/Output' */
  CAN_basics_B.Timedata_int16[1] = CAN_basics_P.Output_Y0;

  /* SystemInitialize for Outport: '<S4>/Out2' */
  CAN_basics_B.Frequencydata_double[1] = CAN_basics_P.Out2_Y0;

  /* SystemInitialize for Outport: '<S4>/Output1' */
  CAN_basics_B.Frequencydata_int16[1] = CAN_basics_P.Output1_Y0;

  /* SystemInitialize for Outport: '<S4>/Out1' */
  CAN_basics_B.Timedata_double[2] = CAN_basics_P.Out1_Y0;

  /* SystemInitialize for Outport: '<S4>/Output' */
  CAN_basics_B.Timedata_int16[2] = CAN_basics_P.Output_Y0;

  /* SystemInitialize for Outport: '<S4>/Out2' */
  CAN_basics_B.Frequencydata_double[2] = CAN_basics_P.Out2_Y0;

  /* SystemInitialize for Outport: '<S4>/Output1' */
  CAN_basics_B.Frequencydata_int16[2] = CAN_basics_P.Output1_Y0;

  /* SystemInitialize for Outport: '<S4>/Out1' */
  CAN_basics_B.Timedata_double[3] = CAN_basics_P.Out1_Y0;

  /* SystemInitialize for Outport: '<S4>/Output' */
  CAN_basics_B.Timedata_int16[3] = CAN_basics_P.Output_Y0;

  /* SystemInitialize for Outport: '<S4>/Out2' */
  CAN_basics_B.Frequencydata_double[3] = CAN_basics_P.Out2_Y0;

  /* SystemInitialize for Outport: '<S4>/Output1' */
  CAN_basics_B.Frequencydata_int16[3] = CAN_basics_P.Output1_Y0;

  /* End of SystemInitialize for S-Function (svntcanreceive): '<S1>/CAN Receive1' */
  {
    char_T *sErr;

    /* Enable for Triggered SubSystem: '<S2>/Function-Call Subsystem1' */
    /* Enable for S-Function (svntcantransmit): '<S7>/CAN Transmit' */
    sErr = GetErrorBuffer(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
    LibReset(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
    LibStart(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    CAN_basics_DW.CANTransmit_BlockDisabled_n = false;

    /* End of Enable for S-Function (svntcantransmit): '<S7>/CAN Transmit' */
    /* End of Enable for SubSystem: '<S2>/Function-Call Subsystem1' */

    /* Enable for Triggered SubSystem: '<S2>/Function-Call Subsystem3' */
    /* Enable for S-Function (svntcantransmit): '<S8>/CAN Transmit' */
    sErr = GetErrorBuffer(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);
    LibReset(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);
    LibStart(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);
    if (*sErr != 0) {
      rtmSetErrorStatus(CAN_basics_M, sErr);
      rtmSetStopRequested(CAN_basics_M, 1);
    }

    CAN_basics_DW.CANTransmit_BlockDisabled = false;

    /* End of Enable for S-Function (svntcantransmit): '<S8>/CAN Transmit' */
    /* End of Enable for SubSystem: '<S2>/Function-Call Subsystem3' */
  }
}

/* Model terminate function */
void CAN_basics_terminate(void)
{
  char_T *sErr;

  /* Terminate for S-Function (svntcanreceive): '<S1>/CAN Receive' */
  sErr = GetErrorBuffer(&CAN_basics_DW.CANReceive_CANReceive[0U]);
  LibTerminate(&CAN_basics_DW.CANReceive_CANReceive[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(CAN_basics_M, sErr);
    rtmSetStopRequested(CAN_basics_M, 1);
  }

  LibDestroy(&CAN_basics_DW.CANReceive_CANReceive[0U], 0);
  DestroyHostLibrary(&CAN_basics_DW.CANReceive_CANReceive[0U]);

  /* End of Terminate for S-Function (svntcanreceive): '<S1>/CAN Receive' */

  /* Terminate for S-Function (svntcanreceive): '<S1>/CAN Receive1' */
  sErr = GetErrorBuffer(&CAN_basics_DW.CANReceive1_CANReceive[0U]);
  LibTerminate(&CAN_basics_DW.CANReceive1_CANReceive[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(CAN_basics_M, sErr);
    rtmSetStopRequested(CAN_basics_M, 1);
  }

  LibDestroy(&CAN_basics_DW.CANReceive1_CANReceive[0U], 0);
  DestroyHostLibrary(&CAN_basics_DW.CANReceive1_CANReceive[0U]);

  /* End of Terminate for S-Function (svntcanreceive): '<S1>/CAN Receive1' */

  /* Terminate for Triggered SubSystem: '<S2>/Function-Call Subsystem1' */
  /* Terminate for S-Function (svntcantransmit): '<S7>/CAN Transmit' */
  sErr = GetErrorBuffer(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
  LibTerminate(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(CAN_basics_M, sErr);
    rtmSetStopRequested(CAN_basics_M, 1);
  }

  LibDestroy(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U], 0);
  DestroyHostLibrary(&CAN_basics_DW.CANTransmit_CANTransmit_f[0U]);

  /* End of Terminate for S-Function (svntcantransmit): '<S7>/CAN Transmit' */
  /* End of Terminate for SubSystem: '<S2>/Function-Call Subsystem1' */

  /* Terminate for Triggered SubSystem: '<S2>/Function-Call Subsystem3' */
  /* Terminate for S-Function (svntcantransmit): '<S8>/CAN Transmit' */
  sErr = GetErrorBuffer(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);
  LibTerminate(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(CAN_basics_M, sErr);
    rtmSetStopRequested(CAN_basics_M, 1);
  }

  LibDestroy(&CAN_basics_DW.CANTransmit_CANTransmit[0U], 0);
  DestroyHostLibrary(&CAN_basics_DW.CANTransmit_CANTransmit[0U]);

  /* End of Terminate for S-Function (svntcantransmit): '<S8>/CAN Transmit' */
  /* End of Terminate for SubSystem: '<S2>/Function-Call Subsystem3' */
}
