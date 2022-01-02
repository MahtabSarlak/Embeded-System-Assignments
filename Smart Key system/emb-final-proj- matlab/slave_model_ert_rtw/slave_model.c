/*
 * File: slave_model.c
 *
 * Code generated for Simulink model 'slave_model'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Fri Jan 22 00:04:44 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "slave_model.h"
#include "slave_model_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define slave_model_IN_addrValidation  ((uint8_T)1U)
#define slave_model_IN_getMsg          ((uint8_T)2U)
#define slave_model_IN_init            ((uint8_T)3U)
#define slave_model_IN_sendReport      ((uint8_T)4U)

/* Block states (default storage) */
DW_slave_model_T slave_model_DW;

/* External inputs (root inport signals with default storage) */
ExtU_slave_model_T slave_model_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_slave_model_T slave_model_Y;

/* Real-time model */
RT_MODEL_slave_model_T slave_model_M_;
RT_MODEL_slave_model_T *const slave_model_M = &slave_model_M_;

/* Model step function */
void slave_model_step(void)
{
  /* Chart: '<Root>/Chart' incorporates:
   *  Inport: '<Root>/msg'
   *  Inport: '<Root>/thisAddr'
   */
  if (slave_model_DW.is_active_c3_slave_model == 0U) {
    slave_model_DW.is_active_c3_slave_model = 1U;
    slave_model_DW.is_c3_slave_model = slave_model_IN_init;
  } else {
    switch (slave_model_DW.is_c3_slave_model) {
     case slave_model_IN_addrValidation:
      if (slave_model_U.msg != slave_model_U.thisAddr) {
        slave_model_DW.is_c3_slave_model = slave_model_IN_init;
      } else {
        if (slave_model_U.msg == slave_model_U.thisAddr) {
          /* Outport: '<Root>/modeBus' */
          slave_model_Y.modeBus = 0U;

          /* Outport: '<Root>/dataBus' incorporates:
           *  Inport: '<Root>/report'
           */
          slave_model_Y.dataBus = slave_model_U.report;
          slave_model_DW.is_c3_slave_model = slave_model_IN_sendReport;
        }
      }
      break;

     case slave_model_IN_getMsg:
      if (slave_model_U.msg != 0) {
        /* Outport: '<Root>/modeBus' */
        slave_model_Y.modeBus = 0U;

        /* Outport: '<Root>/dataBus' incorporates:
         *  Inport: '<Root>/report'
         */
        slave_model_Y.dataBus = slave_model_U.report;
        slave_model_DW.is_c3_slave_model = slave_model_IN_sendReport;
      } else {
        if (slave_model_U.msg == 0) {
          slave_model_DW.is_c3_slave_model = slave_model_IN_init;
        }
      }
      break;

     case slave_model_IN_init:
      if (slave_model_U.msg == 1) {
        slave_model_DW.is_c3_slave_model = slave_model_IN_addrValidation;
      }
      break;

     default:
      /* Outport: '<Root>/modeBus' */
      /* case IN_sendReport: */
      slave_model_Y.modeBus = 1U;
      slave_model_DW.is_c3_slave_model = slave_model_IN_getMsg;
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */
}

/* Model initialize function */
void slave_model_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void slave_model_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
