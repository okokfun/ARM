/**
  **************************************************************************
  * @file     at32f435_437_wdt.h
  * @brief    at32f435_437 wdt header file
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
#ifndef __AT32F435_437_WDT_H
#define __AT32F435_437_WDT_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup WDT
  */


/** @defgroup WDT_flags_definition
  * @brief wdt flag
  */
#define WDT_DIVF_Update_FLAG             ((uint16_t)0x0001) /*!< wdt division value update complete flag */
#define WDT_RLDF_Update_FLAG             ((uint16_t)0x0002) /*!< wdt reload value update complete flag */
#define WDT_WINF_Update_FLAG             ((uint16_t)0x0004) /*!< wdt window value update complete flag */

/** @defgroup WDT_exported_Types
  */

/**
  * @brief wdt division value type
  */
typedef enum {
    WDT_CLK_Div_4                          = 0x00, /*!< wdt clock divider value is 4 */
    WDT_CLK_Div_8                          = 0x01, /*!< wdt clock divider value is 8 */
    WDT_CLK_Div_16                         = 0x02, /*!< wdt clock divider value is 16 */
    WDT_CLK_Div_32                         = 0x03, /*!< wdt clock divider value is 32 */
    WDT_CLK_Div_64                         = 0x04, /*!< wdt clock divider value is 64 */
    WDT_CLK_Div_128                        = 0x05, /*!< wdt clock divider value is 128 */
    WDT_CLK_Div_256                        = 0x06  /*!< wdt clock divider value is 256 */
} WDT_Division_Type;

/**
  * @brief wdt cmd value type
  */
typedef enum {
    WDT_CMD_LOCK                           = 0x0000, /*!< 禁用写保护 command */
    WDT_CMD_UNLOCK                         = 0x5555, /*!< enable write protection command */
    WDT_CMD_Enable                         = 0xCCCC, /*!< enable wdt command */
    WDT_CMD_RELOAD                         = 0xAAAA  /*!< reload command */
} WDT_CMD_Value_Type;

/**
  * @brief type define wdt register all
  */
typedef struct {

    /**
      * @brief wdt cmd register, offset:0x00
      */
    union {
        __IO uint32_t cmd;
        struct {
            __IO uint32_t cmd                  : 16;/* [15:0] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } cmd_bit;
    };

    /**
      * @brief wdt div register, offset:0x04
      */
    union {
        __IO uint32_t div;
        struct {
            __IO uint32_t div                  : 3; /* [2:0] */
            __IO uint32_t reserved1            : 29;/* [31:3] */
        } div_bit;
    };

    /**
     * @brief wdt rld register, offset:0x08
     */
    union {
        __IO uint32_t rld;
        struct {
            __IO uint32_t rld                  : 12;/* [11:0] */
            __IO uint32_t reserved1            : 20;/* [31:12] */
        } rld_bit;
    };

    /**
    * @brief wdt sts register, offset:0x0C
    */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t divf                 : 1; /* [0] */
            __IO uint32_t rldf                 : 1; /* [1] */
            __IO uint32_t reserved1            : 30;/* [31:2] */
        } sts_bit;
    };

    /**
    * @brief wdt win register, offset:0x10
    */
    union {
        __IO uint32_t win;
        struct {
            __IO uint32_t win                  : 12;/* [11:0] */
            __IO uint32_t reserved1            : 20;/* [31:12] */
        } win_bit;
    };
} WDT_Type;
#define WDT                             ((WDT_Type *) WDT_BASE)

/** @defgroup WDT_exported_functions
  */
void WDT_Enable(void);
void WDT_Counter_reload(void);
void WDT_Reload_Value_Set(uint16_t reload_value);
void WDT_Divider_Set(WDT_Division_Type division);
void WDT_Register_Write_Enable( confirm_state new_state);
flag_status WDT_Flag_Get(uint16_t WDT_flag);
void WDT_Window_Counter_Set(uint16_t window_cnt);

#ifdef __cplusplus
}
#endif

#endif
