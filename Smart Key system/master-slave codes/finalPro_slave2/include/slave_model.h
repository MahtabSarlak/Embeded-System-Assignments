/*
 * File: slave_model.h
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

#ifndef RTW_HEADER_slave_model_h_
#define RTW_HEADER_slave_model_h_
#include <stddef.h>
#ifndef slave_model_COMMON_INCLUDES_
# define slave_model_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* slave_model_COMMON_INCLUDES_ */

#include "slave_model_types.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c3_slave_model;    /* '<Root>/Chart' */
  uint8_T is_c3_slave_model;           /* '<Root>/Chart' */
} DW_slave_model_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uint8_T msg;                         /* '<Root>/msg' */
  uint8_T report;                      /* '<Root>/report' */
  uint8_T thisAddr;                    /* '<Root>/thisAddr' */
} ExtU_slave_model_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T modeBus;                     /* '<Root>/modeBus' */
  uint8_T dataBus;                     /* '<Root>/dataBus' */
} ExtY_slave_model_T;

/* Real-time Model Data Structure */
struct tag_RTM_slave_model_T {
  const char_T *errorStatus;
};

/* Block states (default storage) */
extern DW_slave_model_T slave_model_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_slave_model_T slave_model_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_slave_model_T slave_model_Y;

/* Model entry point functions */
extern void slave_model_initialize(void);
extern void slave_model_step(void);
extern void slave_model_terminate(void);

/* Real-time Model object */
extern RT_MODEL_slave_model_T *const slave_model_M;

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
 * '<Root>' : 'slave_model'
 * '<S1>'   : 'slave_model/Chart'
 */
#endif                                 /* RTW_HEADER_slave_model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
