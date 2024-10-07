/**
  **************************************************************************
  * @file     at32f435_437_acc.h
  * @brief    at32f435_437 acc header file
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
#ifndef __AT32F435_437_ACC_H
#define __AT32F435_437_ACC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup ACC
  */

/** @defgroup ACC_exported_constants
  */
#define ACC_CAL_HICKCAL                  ((uint16_t)0x0000) /*!< acc hick calibration */
#define ACC_CAL_HICKTRIM                 ((uint16_t)0x0002) /*!< acc hick trim */

#define ACC_RSLOST_FLAG                  ((uint16_t)0x0002) /*!< acc reference signal lost error flag */
#define ACC_CALRDY_FLAG                  ((uint16_t)0x0001) /*!< acc internal high-speed clock calibration ready error flag */

#define ACC_CALRDYIEN_INT                ((uint16_t)0x0020) /*!< acc internal high-speed clock calibration 就绪中断 enable */
#define ACC_EIEN_INT                     ((uint16_t)0x0010) /*!< acc reference signal lost interrupt enable */

#define ACC_SOF_OTG1                     ((uint16_t)0x0000) /*!< acc sof signal select: otg1 */
#define ACC_SOF_OTG2                     ((uint16_t)0x0004) /*!< acc sof signal select: otg2 */

/** @defgroup ACC_exported_Types
  */

/**
  * @brief type define acc register all
  */
typedef struct {

    /**
      * @brief acc sts register, offset:0x00
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t calrdy               : 1; /* [0] */
            __IO uint32_t rslost               : 1; /* [1] */
            __IO uint32_t reserved1            : 30;/* [31:2] */
        } sts_bit;
    };

    /**
      * @brief acc ctrl1 register, offset:0x04
      */
    union {
        __IO uint32_t ctrl1;
        struct {
            __IO uint32_t calon                : 1; /* [0] */
            __IO uint32_t entrim               : 1; /* [1] */
            __IO uint32_t reserved1            : 2; /* [3:2] */
            __IO uint32_t eien                 : 1; /* [4] */
            __IO uint32_t calrdyien            : 1; /* [5] */
            __IO uint32_t reserved2            : 2; /* [7:6] */
            __IO uint32_t step                 : 4; /* [11:8] */
            __IO uint32_t reserved3            : 20;/* [31:12] */
        } ctrl1_bit;
    };

    /**
     * @brief acc ctrl2 register, offset:0x08
     */
    union {
        __IO uint32_t ctrl2;
        struct {
            __IO uint32_t hickcal              : 8; /* [7:0] */
            __IO uint32_t hicktrim             : 6; /* [13:8] */
            __IO uint32_t reserved1            : 18;/* [31:14] */
        } ctrl2_bit;
    };

    /**
    * @brief acc ACC_C1 register, offset:0x0C
    */
    union {
        __IO uint32_t c1;
        struct {
            __IO uint32_t c1                   : 16;/* [15:0] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } c1_bit;
    };

    /**
    * @brief acc ACC_C2 register, offset:0x10
    */
    union {
        __IO uint32_t c2;
        struct {
            __IO uint32_t c2                   : 16;/* [15:0] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } c2_bit;
    };

    /**
    * @brief acc ACC_C3 register, offset:0x14
    */
    union {
        __IO uint32_t c3;
        struct {
            __IO uint32_t c3                   : 16;/* [15:0] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } c3_bit;
    };
} ACC_Type;
#define ACC                             ((ACC_Type *) ACC_BASE)

/** @defgroup ACC_exported_functions
  */
void ACC_Calibration_Mode_Enable(uint16_t ACC_trim, confirm_state new_state);
void ACC_Step_Set(uint8_t step_value);
void ACC_SOF_Select(uint16_t sof_sel);
void ACC_Interrupt_Enable(uint16_t ACC_int, confirm_state new_state);
uint8_t ACC_Hicktrim_Get(void);
uint8_t ACC_Hickcal_Get(void);
void ACC_Write_C1(uint16_t ACC_C1_value);
void ACC_Write_C2(uint16_t ACC_C2_value);
void ACC_Write_C3(uint16_t ACC_C3_value);
uint16_t ACC_Read_C1(void);
uint16_t ACC_Read_C2(void);
uint16_t ACC_Read_C3(void);
flag_status ACC_Flag_Get(uint16_t ACC_flag);
void ACC_Flag_Clear(uint16_t ACC_flag);

#ifdef __cplusplus
}
#endif

#endif
