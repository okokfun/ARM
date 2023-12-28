/**
  **************************************************************************
  * @file     at32f435_437_wwdt.h
  * @brief    at32f435_437 wwdt header file
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
#ifndef __AT32F435_437_WWDT_H
#define __AT32F435_437_WWDT_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup WWDT
  * @{
  */

/** @defgroup WWDT_Enable_Bit_definition
  * @brief wwdt enable bit
  * @{
  */
#define WWDT_EN_BIT                      ((uint32_t)0x00000080) /*!< wwdt enable bit */

/**
  * @}
  */

/** @defgroup WWDT_exported_Types
  * @{
  */

/**
  * @brief wwdt division type
  */
typedef enum {
    WWDT_PCLK1_Div_4096                    = 0x00, /*!< wwdt counter clock = (pclk1/4096)/1) */
    WWDT_PCLK1_Div_8192                    = 0x01, /*!< wwdt counter clock = (pclk1/4096)/2) */
    WWDT_PCLK1_Div_16384                   = 0x02, /*!< wwdt counter clock = (pclk1/4096)/4) */
    WWDT_PCLK1_Div_32768                   = 0x03  /*!< wwdt counter clock = (pclk1/4096)/8) */
} wWDT_Division_Type;

/**
  * @brief type define wwdt register all
  */
typedef struct {

    /**
      * @brief wwdt ctrl register, offset:0x00
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t cnt                  : 7; /* [6:0] */
            __IO uint32_t wwdten               : 1; /* [7] */
            __IO uint32_t reserved1            : 24;/* [31:8] */
        } ctrl_bit;
    };

    /**
      * @brief wwdt cfg register, offset:0x04
      */
    union {
        __IO uint32_t cfg;
        struct {
            __IO uint32_t win                  : 7; /* [6:0] */
            __IO uint32_t div                  : 2; /* [8:7] */
            __IO uint32_t rldien               : 1; /* [9] */
            __IO uint32_t reserved1            : 22;/* [31:10] */
        } cfg_bit;
    };

    /**
      * @brief wwdt cfg register, offset:0x08
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t rldf                 : 1; /* [0] */
            __IO uint32_t reserved1            : 31;/* [31:1] */
        } sts_bit;
    };

} wWDT_Type;

/**
  * @}
  */
#define WWDT                             ((wWDT_Type *) WWDT_BASE)

/** @defgroup WWDT_exported_functions
  * @{
  */

void wWDT_Reset(void);
void wWDT_Divider_Set(wWDT_Division_Type division);
void wWDT_Flag_Clear(void);
void wWDT_Enable(uint8_t wWDT_cnt);
void wWDT_Interrupt_Enable(void);
flag_status wWDT_Flag_Get(void);
void wWDT_Counter_Set(uint8_t wWDT_cnt);
void wWDT_Window_Counter_Set(uint8_t window_cnt);

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
