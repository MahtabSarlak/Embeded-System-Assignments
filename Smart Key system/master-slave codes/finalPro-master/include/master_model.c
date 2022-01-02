/*
 * File: master_model.c
 *
 * Code generated for Simulink model 'master_model'.
 *
 * Model version                  : 1.9
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Thu Jan 21 23:59:07 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "master_model.h"
#include "master_model_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define master_model_IN_addressSend    ((uint8_T)1U)
#define master_model_IN_getReport      ((uint8_T)2U)
#define master_model_IN_init           ((uint8_T)3U)
#define master_model_IN_initSend       ((uint8_T)4U)
#define master_model_IN_sendMsg        ((uint8_T)5U)

/* Block states (default storage) */
DW_master_model_T master_model_DW;

/* External inputs (root inport signals with default storage) */
ExtU_master_model_T master_model_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_master_model_T master_model_Y;

/* Real-time model */
RT_MODEL_master_model_T master_model_M_;
RT_MODEL_master_model_T *const master_model_M = &master_model_M_;

/* Model step function */
void master_model_step(void)
{
  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/deviceSelect'
   */
  if (master_model_DW.is_active_c3_master_model == 0U) {
    master_model_DW.is_active_c3_master_model = 1U;
    master_model_DW.is_c3_master_model = master_model_IN_init;
  } else {
    switch (master_model_DW.is_c3_master_model) {
     case master_model_IN_addressSend:
      /* Outport: '<Root>/modeBus' */
      master_model_Y.modeBus = 1U;
      master_model_DW.is_c3_master_model = master_model_IN_getReport;
      break;

     case master_model_IN_getReport:
      /* Outport: '<Root>/modeBus' */
      master_model_Y.modeBus = 0U;

      /* Outport: '<Root>/dataBus' incorporates:
       *  Inport: '<Root>/in'
       */
      master_model_Y.dataBus = master_model_U.in;
      master_model_DW.is_c3_master_model = master_model_IN_sendMsg;
      break;

     case master_model_IN_init:
      if ((master_model_U.deviceSelect == 1) || (master_model_U.deviceSelect ==
           2)) {
        /* Outport: '<Root>/dataBus' */
        master_model_Y.dataBus = 1U;
        master_model_DW.is_c3_master_model = master_model_IN_initSend;
      }
      break;

     case master_model_IN_initSend:
      /* Outport: '<Root>/dataBus' incorporates:
       *  Inport: '<Root>/address'
       */
      master_model_Y.dataBus = master_model_U.address;
      master_model_DW.is_c3_master_model = master_model_IN_addressSend;
      break;

     default:
      /* case IN_sendMsg: */
      if ((master_model_U.deviceSelect != 1) && (master_model_U.deviceSelect !=
           2)) {
        /* Outport: '<Root>/modeBus' */
        master_model_Y.modeBus = 1U;
        master_model_DW.is_c3_master_model = master_model_IN_getReport;
      } else {
        if ((master_model_U.deviceSelect == 1) || (master_model_U.deviceSelect ==
             2)) {
          /* Outport: '<Root>/dataBus' */
          master_model_Y.dataBus = 0U;
          master_model_DW.is_c3_master_model = master_model_IN_init;
        }
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */
}

/* Model initialize function */
void master_model_initialize(void)
{
  // master_model_Y.modeBus=0;
  /* (no initialization code required) */
}

/* Model terminate function */
void master_model_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
