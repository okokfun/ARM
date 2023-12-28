/**
  **************************************************************************
  * @file     at32f435_437_exint.h
  * @brief    at32f435_437 exint header file
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
#ifndef __AT32F435_437_EXINT_H
#define __AT32F435_437_EXINT_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup EXINT
  * @{
  */

/** @defgroup EXINT_lines
  * @{
  */
#define EXINT_Line_NONE                  ((uint32_t)0x000000)
#define EXINT_Line_0                     ((uint32_t)0x000001) /*!< external interrupt line 0 */
#define EXINT_Line_1                     ((uint32_t)0x000002) /*!< external interrupt line 1 */
#define EXINT_Line_2                     ((uint32_t)0x000004) /*!< external interrupt line 2 */
#define EXINT_Line_3                     ((uint32_t)0x000008) /*!< external interrupt line 3 */
#define EXINT_Line_4                     ((uint32_t)0x000010) /*!< external interrupt line 4 */
#define EXINT_Line_5                     ((uint32_t)0x000020) /*!< external interrupt line 5 */
#define EXINT_Line_6                     ((uint32_t)0x000040) /*!< external interrupt line 6 */
#define EXINT_Line_7                     ((uint32_t)0x000080) /*!< external interrupt line 7 */
#define EXINT_Line_8                     ((uint32_t)0x000100) /*!< external interrupt line 8 */
#define EXINT_Line_9                     ((uint32_t)0x000200) /*!< external interrupt line 9 */
#define EXINT_Line_10                    ((uint32_t)0x000400) /*!< external interrupt line 10 */
#define EXINT_Line_11                    ((uint32_t)0x000800) /*!< external interrupt line 11 */
#define EXINT_Line_12                    ((uint32_t)0x001000) /*!< external interrupt line 12 */
#define EXINT_Line_13                    ((uint32_t)0x002000) /*!< external interrupt line 13 */
#define EXINT_Line_14                    ((uint32_t)0x004000) /*!< external interrupt line 14 */
#define EXINT_Line_15                    ((uint32_t)0x008000) /*!< external interrupt line 15 */
#define EXINT_Line_16                    ((uint32_t)0x010000) /*!< external interrupt line 16 */
#define EXINT_Line_17                    ((uint32_t)0x020000) /*!< external interrupt line 17 */
#define EXINT_Line_18                    ((uint32_t)0x040000) /*!< external interrupt line 18 */
#define EXINT_Line_19                    ((uint32_t)0x080000) /*!< external interrupt line 19 */
#define EXINT_Line_20                    ((uint32_t)0x100000) /*!< external interrupt line 20 */
#define EXINT_Line_21                    ((uint32_t)0x200000) /*!< external interrupt line 21 */
#define EXINT_Line_22                    ((uint32_t)0x400000) /*!< external interrupt line 22 */

/**
  * @}
  */

/** @defgroup EXINT_exported_Types
  * @{
  */

/**
  * @brief exint line mode type
  */
typedef enum {
    EXINT_Line_INTERRUPUT                  = 0x00, /*!< external interrupt line interrupt mode */
    EXINT_Line_EVENT                       = 0x01  /*!< external interrupt line event mode */
} EXINT_Line_Mode_Type;

/**
  * @brief exint polarity configuration type
  */
typedef enum {
    EXINT_Trigger_RISING_EDGE              = 0x00, /*!< external interrupt line rising trigger mode */
    EXINT_Trigger_FALLING_EDGE             = 0x01, /*!< external interrupt line falling trigger mode */
    EXINT_Trigger_BOTH_EDGE                = 0x02  /*!< external interrupt line both rising and falling trigger mode */
} EXINT_Polarity_Config_Type;

/**
  * @brief exint init type
  */
typedef struct {
    EXINT_Line_Mode_Type                   line_Mode;     /*!< choose mode event or interrupt mode */
    uint32_t                               line_Select;   /*!< select the exint line, availiable for single line or multiple lines */
    EXINT_Polarity_Config_Type             line_polarity; /*!< select the tregger polarity, with rising edge, falling edge or both edge */
    confirm_state                          line_Enable;   /*!< enable or disable exint */
} EXINT_Init_Type;

/**
  * @brief type define exint register all
  */
typedef struct {

    /**
      * @brief exint inten register, offset:0x00
      */
    union {
        __IO uint32_t inten;
        struct {
            __IO uint32_t intenx               : 23;/* [22:0] */
            __IO uint32_t reserved1            : 9; /* [31:23] */
        } inten_bit;
    };

    /**
      * @brief exint evten register, offset:0x04
      */
    union {
        __IO uint32_t evten;
        struct {
            __IO uint32_t evtenx               : 23;/* [22:0] */
            __IO uint32_t reserved1            : 9; /* [31:23] */
        } evten_bit;
    };

    /**
      * @brief exint polcfg1 register, offset:0x08
      */
    union {
        __IO uint32_t polcfg1;
        struct {
            __IO uint32_t rpx                  : 23;/* [22:0] */
            __IO uint32_t reserved1            : 9; /* [31:23] */
        } polcfg1_bit;
    };

    /**
      * @brief exint polcfg2 register, offset:0x0C
      */
    union {
        __IO uint32_t polcfg2;
        struct {
            __IO uint32_t fpx                  : 23;/* [22:0] */
            __IO uint32_t reserved1            : 9; /* [31:23] */
        } polcfg2_bit;
    };

    /**
      * @brief exint swtrg register, offset:0x10
      */
    union {
        __IO uint32_t swtrg;
        struct {
            __IO uint32_t swtx                 : 23;/* [22:0] */
            __IO uint32_t reserved1            : 9; /* [31:23] */
        } swtrg_bit;
    };

    /**
      * @brief exint intsts register, offset:0x14
      */
    union {
        __IO uint32_t intsts;
        struct {
            __IO uint32_t linex                : 23;/* [22:0] */
            __IO uint32_t reserved1            : 9; /* [31:23] */
        } intsts_bit;
    };
} EXINT_Type;

/**
  * @}
  */
#define EXINT                             ((EXINT_Type *) EXINT_BASE)

/** @defgroup EXINT_exported_functions
  * @{
  */

void EXINT_Reset(void);
void EXINT_Default_Para_Init(EXINT_Init_Type *EXINT_struct);
void EXINT_Init(EXINT_Init_Type *EXINT_struct);
void EXINT_Flag_Clear(uint32_t EXINT_line);
flag_status EXINT_Flag_Get(uint32_t EXINT_line);
void EXINT_Software_Interrupt_Event_Generate(uint32_t EXINT_line);
void EXINT_Interrupt_Enable(uint32_t EXINT_line, confirm_state new_state);
void EXINT_Event_Enable(uint32_t EXINT_line, confirm_state new_state);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
