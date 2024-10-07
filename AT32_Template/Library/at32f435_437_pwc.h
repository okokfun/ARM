/**
  **************************************************************************
  * @file     at32f435_437_pwc.h
  * @brief    at32f435_437 pwr header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_PWC_H
#define __AT32F435_437_PWC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup PWC
  */

/** @defgroup PWC_flags_definition
  * @brief pwc flag
  */
#define PWC_WakeUp_FLAG                  ((uint32_t)0x00000001) /*!< wakeup flag */
#define PWC_Standby_FLAG                 ((uint32_t)0x00000002) /*!< standby flag */
#define PWC_PVM_OutPut_FLAG              ((uint32_t)0x00000004) /*!< pvm output flag */

/**
  * @brief pwc wakeup pin num definition
  */
#define PWC_WakeUp_Pin_1                 ((uint32_t)0x00000100) /*!< standby wake-up pin1 */
#define PWC_WakeUp_Pin_2                 ((uint32_t)0x00000200) /*!< standby wake-up pin2 */

/**
  * @brief  select ldo output voltage.
  * @param  val: set the ldo output voltage.
  *         该参数可以是以下值之一:
  *         - PWC_LDO_OutPut_1V3: system clock up to 288MHz.
  *         - PWC_LDO_OutPut_1V2: system clock up to 240MHz.
  *         - PWC_LDO_OutPut_1V1: system clock up to 192MHz.
  *         - PWC_LDO_OutPut_1V0: system clock up to 144MHz.
  * @note   useage limited.
  *         PWC_LDO_OutPut_1V3: operation temperature range -40~85 degree, VDD must over 3.0V.
  */
#define PWC_Ldo_OutPut_Voltage_Set(val)  (PWC->ldoov_bit.ldoovsel = val)

/** @defgroup PWC_exported_Types
  */

/**
  * @brief pwc pvm voltage type
  */
typedef enum {
    PWC_PVM_Voltage_2V3                    = 0x01, /*!< power voltage monitoring boundary 2.3v */
    PWC_PVM_Voltage_2V4                    = 0x02, /*!< power voltage monitoring boundary 2.4v */
    PWC_PVM_Voltage_2V5                    = 0x03, /*!< power voltage monitoring boundary 2.5v */
    PWC_PVM_Voltage_2V6                    = 0x04, /*!< power voltage monitoring boundary 2.6v */
    PWC_PVM_Voltage_2V7                    = 0x05, /*!< power voltage monitoring boundary 2.7v */
    PWC_PVM_Voltage_2V8                    = 0x06, /*!< power voltage monitoring boundary 2.8v */
    PWC_PVM_Voltage_2V9                    = 0x07  /*!< power voltage monitoring boundary 2.9v */
} PWC_PVM_Voltage_Type;

/**
  * @brief pwc ldo output voltage type
  */
typedef enum {
    PWC_LDO_OutPut_1V3                     = 0x01, /*!< ldo output voltage is 1.3v */
    PWC_LDO_OutPut_1V2                     = 0x00, /*!< ldo output voltage is 1.2v */
    PWC_LDO_OutPut_1V1                     = 0x04, /*!< ldo output voltage is 1.1v */
    PWC_LDO_OutPut_1V0                     = 0x05, /*!< ldo output voltage is 1.0v */
} PWC_ldo_OutPut_Voltage_Type;

/**
  * @brief pwc sleep enter type
  */
typedef enum {
    PWC_Sleep_Enter_WFI                    = 0x00, /*!< use wfi enter sleep mode */
    PWC_Sleep_Enter_WFE                    = 0x01  /*!< use wfe enter sleep mode */
} PWC_Sleep_Enter_Type ;

/**
  * @brief pwc deep sleep enter type
  */
typedef enum {
    PWC_Deep_Sleep_Enter_WFI               = 0x00, /*!< use wfi enter deepsleep mode */
    PWC_Deep_Sleep_Enter_WFE               = 0x01  /*!< use wfe enter deepsleep mode */
} PWC_Deep_Sleep_Enter_Type ;

/**
  * @brief pwc regulator type
  */
typedef enum {
    PWC_REGULATOR_ON                       = 0x00, /*!< voltage regulator state on when deepsleep mode */
    PWC_REGULATOR_Low_POWER                = 0x01  /*!< voltage regulator state low power when deepsleep mode */
} PWC_regulator_Type ;

/**
  * @brief type define pwc register all
  */
typedef struct {
    /**
      * @brief pwc ctrl register, offset:0x00
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t vrsel                : 1; /* [0] */
            __IO uint32_t lpsel                : 1; /* [1] */
            __IO uint32_t clswef               : 1; /* [2] */
            __IO uint32_t clsef                : 1; /* [3] */
            __IO uint32_t pvmen                : 1; /* [4] */
            __IO uint32_t pvmsel               : 3; /* [7:5] */
            __IO uint32_t bpwen                : 1; /* [8] */
            __IO uint32_t reserved1            : 23;/* [31:9] */
        } ctrl_bit;
    };

    /**
      * @brief pwc ctrlsts register, offset:0x04
      */
    union {
        __IO uint32_t ctrlsts;
        struct {
            __IO uint32_t swef                 : 1; /* [0] */
            __IO uint32_t sef                  : 1; /* [1] */
            __IO uint32_t pvmof                : 1; /* [2] */
            __IO uint32_t reserved1            : 5; /* [7:3] */
            __IO uint32_t swpen1               : 1; /* [8] */
            __IO uint32_t swpen2               : 1; /* [9] */
            __IO uint32_t reserved2            : 22;/* [31:10] */
        } ctrlsts_bit;
    };

    __IO uint32_t reserved1[2];

    /**
      * @brief pwc ldoov register, offset:0x10
      */
    union {
        __IO uint32_t ldoov;
        struct {
            __IO uint32_t ldoovsel             : 3; /* [2:0] */
            __IO uint32_t reserved1            : 29;/* [31:3] */
        } ldoov_bit;
    };

} PWC_Type;
#define PWC                              ((PWC_Type *) PWC_BASE)

/** @defgroup PWC_exported_functions
  */
void PWC_Reset(void);
void PWC_Battery_Powered_Domain_Access(confirm_state new_state);
void PWC_PVM_level_Select(PWC_PVM_Voltage_Type pvm_voltage);
void PWC_Power_Voltage_Monitor_Enable(confirm_state new_state);
void PWC_WakeUp_Pin_Enable(uint32_t pin_Num, confirm_state new_state);
void PWC_Flag_Clear(uint32_t PWC_flag);
flag_status PWC_Flag_Get(uint32_t PWC_flag);
void PWC_Sleep_Mode_Enter(PWC_Sleep_Enter_Type PWC_Sleep_Enter);
void PWC_Deep_Sleep_Mode_Enter(PWC_Deep_Sleep_Enter_Type PWC_Deep_Sleep_Enter);
void PWC_Voltage_Regulate_Set(PWC_regulator_Type PWC_regulator);
void PWC_Standby_Mode_Enter(void);

#ifdef __cplusplus
}
#endif

#endif
