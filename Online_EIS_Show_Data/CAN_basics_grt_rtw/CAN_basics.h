/*
 * CAN_basics.h
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

#ifndef RTW_HEADER_CAN_basics_h_
#define RTW_HEADER_CAN_basics_h_
#include <string.h>
#include <math.h>
#include <float.h>
#include <stddef.h>
#ifndef CAN_basics_COMMON_INCLUDES_
# define CAN_basics_COMMON_INCLUDES_
#include <string.h>
#include <math.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "can_message.h"
#include "hostlib_vntcan.h"
#endif                                 /* CAN_basics_COMMON_INCLUDES_ */

#include "CAN_basics_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_zcfcn.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               (&(rtm)->Timing.taskTime0)
#endif

/* user code (top of export header file) */
#include "can_message.h"

/* Block signals (default storage) */
typedef struct {
  CAN_DATATYPE CANdatain;              /* '<S1>/CAN Receive' */
  CAN_DATATYPE CANdatain_f;            /* '<S1>/CAN Receive1' */
  CAN_DATATYPE CANPack;                /* '<S8>/CAN Pack' */
  CAN_DATATYPE CANPack_a;              /* '<S7>/CAN Pack' */
  real_T Timedata_double[4];           /* '<S4>/Multiply1' */
  real_T Frequencydata_double[4];      /* '<S4>/Multiply2' */
  real_T A0;                           /* '<S3>/Merge' */
  real_T A1;                           /* '<S3>/Merge1' */
  uint16_T Multiply;                   /* '<S8>/Multiply' */
  uint16_T Multiply1;                  /* '<S8>/Multiply1' */
  uint16_T Multiply_i;                 /* '<S7>/Multiply' */
  uint16_T Multiply1_b;                /* '<S7>/Multiply1' */
  uint16_T Frequencydata_int16[4];     /* '<S4>/Byte Unpack1' */
  uint16_T Timedata_int16[4];          /* '<S4>/Byte Unpack2' */
  uint16_T ByteUnpack1[4];             /* '<S6>/Byte Unpack1' */
  uint16_T ByteUnpack2[4];             /* '<S6>/Byte Unpack2' */
  uint16_T ByteUnpack;                 /* '<S5>/Byte Unpack' */
  uint16_T ByteUnpack1_e;              /* '<S5>/Byte Unpack1' */
  uint16_T ByteUnpack2_e;              /* '<S5>/Byte Unpack2' */
  uint16_T ByteUnpack3;                /* '<S5>/Byte Unpack3' */
  uint16_T ByteUnpack4;                /* '<S5>/Byte Unpack4' */
  uint16_T ByteUnpack5;                /* '<S5>/Byte Unpack5' */
  uint16_T ByteUnpack6;                /* '<S5>/Byte Unpack6' */
  uint16_T ByteUnpack7;                /* '<S5>/Byte Unpack7' */
  uint8_T BytePack5[2];                /* '<S8>/Byte Pack5' */
  uint8_T BytePack1[2];                /* '<S8>/Byte Pack1' */
  uint8_T BytePack3[2];                /* '<S8>/Byte Pack3' */
  uint8_T BytePack4[2];                /* '<S8>/Byte Pack4' */
  uint8_T BytePack6[8];                /* '<S8>/Byte Pack6' */
  uint8_T BytePack5_b[2];              /* '<S7>/Byte Pack5' */
  uint8_T BytePack1_p[2];              /* '<S7>/Byte Pack1' */
  uint8_T BytePack3_o[2];              /* '<S7>/Byte Pack3' */
  uint8_T BytePack4_o[2];              /* '<S7>/Byte Pack4' */
  uint8_T BytePack6_b[8];              /* '<S7>/Byte Pack6' */
  uint8_T CANUnpack2[8];               /* '<S4>/CAN Unpack2' */
  uint8_T CANUnpack1[8];               /* '<S4>/CAN Unpack1' */
  uint8_T CANUnpack1_e[8];             /* '<S6>/CAN Unpack1' */
  uint8_T CANUnpack[8];                /* '<S6>/CAN Unpack' */
  uint8_T CANUnpack_l[2];              /* '<S5>/CAN Unpack' */
  uint8_T CANUnpack1_g[2];             /* '<S5>/CAN Unpack1' */
  uint8_T CANUnpack2_f[2];             /* '<S5>/CAN Unpack2' */
  uint8_T CANUnpack3[2];               /* '<S5>/CAN Unpack3' */
  uint8_T CANUnpack4[2];               /* '<S5>/CAN Unpack4' */
  uint8_T CANUnpack5[2];               /* '<S5>/CAN Unpack5' */
  uint8_T CANUnpack6[2];               /* '<S5>/CAN Unpack6' */
  uint8_T CANUnpack7[2];               /* '<S5>/CAN Unpack7' */
} B_CAN_basics_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T CANReceive_CANReceive[137];   /* '<S1>/CAN Receive' */
  real_T CANReceive1_CANReceive[137];  /* '<S1>/CAN Receive1' */
  real_T CANTransmit_CANTransmit[137]; /* '<S8>/CAN Transmit' */
  real_T CANTransmit_CANTransmit_f[137];/* '<S7>/CAN Transmit' */
  struct {
    void *LoggedData[2];
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<Root>/Scope2' */

  struct {
    void *LoggedData[2];
  } Scope_PWORK_h;                     /* '<S1>/Scope' */

  struct {
    void *LoggedData[2];
  } Scope1_PWORK_m;                    /* '<S1>/Scope1' */

  int_T CANTransmit_PortWidth;         /* '<S8>/CAN Transmit' */
  int_T CANTransmit_PortWidth_p;       /* '<S7>/CAN Transmit' */
  int_T CANUnpack2_ModeSignalID;       /* '<S4>/CAN Unpack2' */
  int_T CANUnpack2_StatusPortID;       /* '<S4>/CAN Unpack2' */
  int_T CANUnpack1_ModeSignalID;       /* '<S4>/CAN Unpack1' */
  int_T CANUnpack1_StatusPortID;       /* '<S4>/CAN Unpack1' */
  int_T CANUnpack1_ModeSignalID_o;     /* '<S6>/CAN Unpack1' */
  int_T CANUnpack1_StatusPortID_h;     /* '<S6>/CAN Unpack1' */
  int_T CANUnpack_ModeSignalID;        /* '<S6>/CAN Unpack' */
  int_T CANUnpack_StatusPortID;        /* '<S6>/CAN Unpack' */
  int_T CANUnpack_ModeSignalID_c;      /* '<S5>/CAN Unpack' */
  int_T CANUnpack_StatusPortID_h;      /* '<S5>/CAN Unpack' */
  int_T CANUnpack1_ModeSignalID_e;     /* '<S5>/CAN Unpack1' */
  int_T CANUnpack1_StatusPortID_a;     /* '<S5>/CAN Unpack1' */
  int_T CANUnpack2_ModeSignalID_e;     /* '<S5>/CAN Unpack2' */
  int_T CANUnpack2_StatusPortID_d;     /* '<S5>/CAN Unpack2' */
  int_T CANUnpack3_ModeSignalID;       /* '<S5>/CAN Unpack3' */
  int_T CANUnpack3_StatusPortID;       /* '<S5>/CAN Unpack3' */
  int_T CANUnpack4_ModeSignalID;       /* '<S5>/CAN Unpack4' */
  int_T CANUnpack4_StatusPortID;       /* '<S5>/CAN Unpack4' */
  int_T CANUnpack5_ModeSignalID;       /* '<S5>/CAN Unpack5' */
  int_T CANUnpack5_StatusPortID;       /* '<S5>/CAN Unpack5' */
  int_T CANUnpack6_ModeSignalID;       /* '<S5>/CAN Unpack6' */
  int_T CANUnpack6_StatusPortID;       /* '<S5>/CAN Unpack6' */
  int_T CANUnpack7_ModeSignalID;       /* '<S5>/CAN Unpack7' */
  int_T CANUnpack7_StatusPortID;       /* '<S5>/CAN Unpack7' */
  boolean_T CANTransmit_BlockDisabled; /* '<S8>/CAN Transmit' */
  boolean_T CANTransmit_BlockDisabled_n;/* '<S7>/CAN Transmit' */
} DW_CAN_basics_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState FunctionCallSubsystem3_Trig_ZCE;/* '<S2>/Function-Call Subsystem3' */
  ZCSigState FunctionCallSubsystem1_Trig_ZCE;/* '<S2>/Function-Call Subsystem1' */
} PrevZCX_CAN_basics_T;

/* Parameters (default storage) */
struct P_CAN_basics_T_ {
  real_T Constant9_Value;              /* Expression: 32767
                                        * Referenced by: '<S5>/Constant9'
                                        */
  real_T Multiply9_Gain;               /* Expression: 5
                                        * Referenced by: '<S5>/Multiply9'
                                        */
  real_T Constant8_Value;              /* Expression: 32767
                                        * Referenced by: '<S5>/Constant8'
                                        */
  real_T Multiply8_Gain;               /* Expression: 5
                                        * Referenced by: '<S5>/Multiply8'
                                        */
  real_T Constant7_Value;              /* Expression: 32767
                                        * Referenced by: '<S5>/Constant7'
                                        */
  real_T Multiply7_Gain;               /* Expression: 5
                                        * Referenced by: '<S5>/Multiply7'
                                        */
  real_T Constant6_Value;              /* Expression: 32767
                                        * Referenced by: '<S5>/Constant6'
                                        */
  real_T Multiply6_Gain;               /* Expression: 5
                                        * Referenced by: '<S5>/Multiply6'
                                        */
  real_T Constant5_Value;              /* Expression: 32767
                                        * Referenced by: '<S5>/Constant5'
                                        */
  real_T Multiply5_Gain;               /* Expression: 5
                                        * Referenced by: '<S5>/Multiply5'
                                        */
  real_T Constant4_Value;              /* Expression: 32767
                                        * Referenced by: '<S5>/Constant4'
                                        */
  real_T Multiply4_Gain;               /* Expression: 5
                                        * Referenced by: '<S5>/Multiply4'
                                        */
  real_T Constant3_Value;              /* Expression: 32767
                                        * Referenced by: '<S5>/Constant3'
                                        */
  real_T Multiply3_Gain;               /* Expression: 5
                                        * Referenced by: '<S5>/Multiply3'
                                        */
  real_T Constant2_Value;              /* Expression: 32767
                                        * Referenced by: '<S5>/Constant2'
                                        */
  real_T Multiply2_Gain;               /* Expression: 5
                                        * Referenced by: '<S5>/Multiply2'
                                        */
  real_T Switch2_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch2'
                                        */
  real_T Switch3_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch3'
                                        */
  real_T Switch4_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch4'
                                        */
  real_T Switch5_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch5'
                                        */
  real_T Switch6_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch6'
                                        */
  real_T Switch7_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch7'
                                        */
  real_T Switch8_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch8'
                                        */
  real_T Switch9_Threshold;            /* Expression: 0
                                        * Referenced by: '<S5>/Switch9'
                                        */
  real_T Constant9_Value_b;            /* Expression: 32767
                                        * Referenced by: '<S6>/Constant9'
                                        */
  real_T Multiply9_Gain_a;             /* Expression: 5
                                        * Referenced by: '<S6>/Multiply9'
                                        */
  real_T Constant2_Value_h;            /* Expression: 32767
                                        * Referenced by: '<S6>/Constant2'
                                        */
  real_T Multiply2_Gain_o;             /* Expression: 5
                                        * Referenced by: '<S6>/Multiply2'
                                        */
  real_T Switch9_Threshold_k;          /* Expression: 0
                                        * Referenced by: '<S6>/Switch9'
                                        */
  real_T Switch2_Threshold_k;          /* Expression: 0
                                        * Referenced by: '<S6>/Switch2'
                                        */
  real_T Merge_InitialOutput;         /* Computed Parameter: Merge_InitialOutput
                                       * Referenced by: '<S3>/Merge'
                                       */
  real_T Merge1_InitialOutput;       /* Computed Parameter: Merge1_InitialOutput
                                      * Referenced by: '<S3>/Merge1'
                                      */
  real_T Merge2_InitialOutput;       /* Computed Parameter: Merge2_InitialOutput
                                      * Referenced by: '<S3>/Merge2'
                                      */
  real_T Merge3_InitialOutput;       /* Computed Parameter: Merge3_InitialOutput
                                      * Referenced by: '<S3>/Merge3'
                                      */
  real_T Merge4_InitialOutput;       /* Computed Parameter: Merge4_InitialOutput
                                      * Referenced by: '<S3>/Merge4'
                                      */
  real_T Merge5_InitialOutput;       /* Computed Parameter: Merge5_InitialOutput
                                      * Referenced by: '<S3>/Merge5'
                                      */
  real_T Merge6_InitialOutput;       /* Computed Parameter: Merge6_InitialOutput
                                      * Referenced by: '<S3>/Merge6'
                                      */
  real_T Merge7_InitialOutput;       /* Computed Parameter: Merge7_InitialOutput
                                      * Referenced by: '<S3>/Merge7'
                                      */
  real_T Out1_Y0;                      /* Computed Parameter: Out1_Y0
                                        * Referenced by: '<S4>/Out1'
                                        */
  real_T Out2_Y0;                      /* Computed Parameter: Out2_Y0
                                        * Referenced by: '<S4>/Out2'
                                        */
  real_T Constant1_Value;              /* Expression: 32767
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real_T Constant2_Value_h1;           /* Expression: 32767
                                        * Referenced by: '<S4>/Constant2'
                                        */
  real_T Multiply1_Gain;               /* Expression: 5
                                        * Referenced by: '<S4>/Multiply1'
                                        */
  real_T Multiply2_Gain_h;             /* Expression: 5
                                        * Referenced by: '<S4>/Multiply2'
                                        */
  real_T Constant_Value;               /* Expression: 5
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Multiply_Gain;                /* Expression: 65534
                                        * Referenced by: '<S7>/Multiply'
                                        */
  real_T Constant1_Value_d;            /* Expression: 5
                                        * Referenced by: '<S7>/Constant1'
                                        */
  real_T Multiply1_Gain_l;             /* Expression: 65534
                                        * Referenced by: '<S7>/Multiply1'
                                        */
  real_T Constant_Value_m;             /* Expression: 5
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Multiply_Gain_p;              /* Expression: 65534
                                        * Referenced by: '<S8>/Multiply'
                                        */
  real_T Constant1_Value_e;            /* Expression: 5
                                        * Referenced by: '<S8>/Constant1'
                                        */
  real_T Multiply1_Gain_i;             /* Expression: 65534
                                        * Referenced by: '<S8>/Multiply1'
                                        */
  real_T Constant_Value_j;             /* Expression: 1
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Constant1_Value_k;            /* Expression: 0
                                        * Referenced by: '<S1>/Constant1'
                                        */
  real_T Ampmin_Value;                 /* Expression: 0
                                        * Referenced by: '<S2>/Amp min'
                                        */
  real_T Ampmax_Value;                 /* Expression: 2.399014778325123
                                        * Referenced by: '<S2>/Amp max'
                                        */
  real_T NextF_Value;                  /* Expression: 1
                                        * Referenced by: '<S2>/Next F'
                                        */
  real_T Constant4_Value_a;            /* Expression: 1
                                        * Referenced by: '<S2>/Constant4'
                                        */
  uint16_T Output_Y0;                  /* Computed Parameter: Output_Y0
                                        * Referenced by: '<S4>/Output'
                                        */
  uint16_T Output1_Y0;                 /* Computed Parameter: Output1_Y0
                                        * Referenced by: '<S4>/Output1'
                                        */
  uint16_T Frequency_Value;            /* Computed Parameter: Frequency_Value
                                        * Referenced by: '<S2>/Frequency'
                                        */
  uint16_T Period_Value;               /* Computed Parameter: Period_Value
                                        * Referenced by: '<S2>/Period'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_CAN_basics_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_CAN_basics_T CAN_basics_P;

/* Block signals (default storage) */
extern B_CAN_basics_T CAN_basics_B;

/* Block states (default storage) */
extern DW_CAN_basics_T CAN_basics_DW;

/* Model entry point functions */
extern void CAN_basics_initialize(void);
extern void CAN_basics_step(void);
extern void CAN_basics_terminate(void);

/* Real-time Model object */
extern RT_MODEL_CAN_basics_T *const CAN_basics_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'CAN_basics'
 * '<S1>'   : 'CAN_basics/Receive'
 * '<S2>'   : 'CAN_basics/Transmit'
 * '<S3>'   : 'CAN_basics/Receive/Function-Call Subsystem'
 * '<S4>'   : 'CAN_basics/Receive/Function-Call Subsystem1'
 * '<S5>'   : 'CAN_basics/Receive/Function-Call Subsystem/If Action Subsystem'
 * '<S6>'   : 'CAN_basics/Receive/Function-Call Subsystem/If Action Subsystem1'
 * '<S7>'   : 'CAN_basics/Transmit/Function-Call Subsystem1'
 * '<S8>'   : 'CAN_basics/Transmit/Function-Call Subsystem3'
 */
#endif                                 /* RTW_HEADER_CAN_basics_h_ */
