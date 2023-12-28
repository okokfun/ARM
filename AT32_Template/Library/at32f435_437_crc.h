/**
  **************************************************************************
  * @file     at32f435_437_crc.h
  * @brief    at32f435_437 crc header file
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

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_CRC_H
#define __AT32F435_437_CRC_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup  CRC
  * @{
  */

/** @defgroup CRC_exported_Types
  * @{
  */

/**
  * @brief crc reverse input data
  */
typedef enum {
    CRC_Reverse_Input_NO_AFFECTE           = 0x00, /*!< input data no reverse */
    CRC_Reverse_Input_BY_BYTE              = 0x01, /*!< input data reverse by byte */
    CRC_Reverse_Input_BY_HALFWORD          = 0x02, /*!< input data reverse by half word */
    CRC_Reverse_Input_BY_WORD              = 0x03  /*!< input data reverse by word */
} CRC_Reverse_Input_Type;

/**
  * @brief crc reverse output data
  */
typedef enum {
    CRC_Reverse_OutPut_NO_AFFECTE          = 0x00, /*!< output data no reverse */
    CRC_Reverse_OutPut_DATA                = 0x01  /*!< output data reverse by word */
} CRC_Reverse_OutPut_Type;

/**
 * @brief type define crc register all
 */
typedef struct {
    /**
      * @brief crc dt register, offset:0x00
      */
    union {
        __IO uint32_t dt;
        struct {
            __IO uint32_t dt                   : 32; /* [31:0] */
        } dt_bit;
    };

    /**
      * @brief crc cdt register, offset:0x04
      */
    union {
        __IO uint32_t cdt;
        struct {
            __IO uint32_t cdt                  : 8 ; /* [7:0] */
            __IO uint32_t reserved1            : 24 ;/* [31:8] */
        } cdt_bit;
    };

    /**
      * @brief crc ctrl register, offset:0x08
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t rst                  : 1 ; /* [0] */
            __IO uint32_t reserved1            : 4 ; /* [4:1] */
            __IO uint32_t revid                : 2 ; /* [6:5] */
            __IO uint32_t revod                : 1 ; /* [7] */
            __IO uint32_t reserved2            : 24 ;/* [31:8] */
        } ctrl_bit;
    };

    /**
      * @brief crm reserved1 register, offset:0x0C
      */
    __IO uint32_t reserved1;

    /**
      * @brief crc idt register, offset:0x10
      */
    union {
        __IO uint32_t idt;
        struct {
            __IO uint32_t idt                  : 32; /* [31:0] */
        } idt_bit;
    };

} CRC_Type;

/**
  * @}
  */
#define CRC                              ((CRC_Type *) CRC_BASE)

/** @defgroup CRC_exported_functions
  * @{
  */

void CRC_Data_Reset(void);
uint32_t CRC_ONE_Word_Calculate(uint32_t data);
uint32_t CRC_Block_Calculate(uint32_t *pbuffer, uint32_t length);
uint32_t CRC_Data_Get(void);
void CRC_Common_Data_Set(uint8_t cdt_value);
uint8_t CRC_Common_Data_Get(void);
void CRC_Init_Data_Set(uint32_t value);
void CRC_Reverse_Input_Data_Set(CRC_Reverse_Input_Type value);
void CRC_Reverse_OutPut_Data_Set(CRC_Reverse_OutPut_Type value);

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
