/**
  **************************************************************************
  * @file     at32f435_437_crc.c
  * @brief    contains all the functions for the crc firmware library
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

#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @defgroup CRC
  * @brief CRC driver modules
  */

#ifdef CRC_MODULE_EnableD

/** @defgroup CRC_private_functions
  */

/**
  * @brief  reset the crc data register.
  * @param  无
  * @retval 无
  */
void CRC_Data_Reset(void) {
    /* reset crc generator */
    CRC->ctrl_bit.rst = 0x1;
}

/**
  * @brief  compute the 32-bit crc of a given data word(32-bit).
  * @param  data: data word(32-bit) to compute its crc
  * @retval 32-bit crc
  */
uint32_t CRC_ONE_Word_Calculate(uint32_t data) {
    CRC->dt = data;
    return (CRC->dt);
}

/**
  * @brief  compute the 32-bit crc of a given buffer of data word(32-bit).
  * @param  pbuffer: pointer to the buffer containing the data to be computed
  * @param  length: length of the buffer to be computed
  * @retval 32-bit crc
  */
uint32_t CRC_Block_Calculate(uint32_t *pbuffer, uint32_t length) {
    uint32_t index = 0;

    for(index = 0; index < length; index++) {
        CRC->dt = pbuffer[index];
    }

    return (CRC->dt);
}

/**
  * @brief  return the current crc value.
  * @param  无
  * @retval 32-bit crc
  */
uint32_t CRC_Data_Get(void) {
    return (CRC->dt);
}

/**
  * @brief  store a 8-bit data in the common data register.
  * @param  cdt_value: 8-bit value to be stored in the common data register
  * @retval 无
  */
void CRC_Common_Data_Set(uint8_t cdt_value) {
    CRC->cdt_bit.cdt = cdt_value;
}

/**
  * @brief  return the 8-bit data stored in the common data register
  * @param  无
  * @retval 8-bit value of the common data register
  */
uint8_t CRC_Common_Data_Get(void) {
    return (CRC->cdt_bit.cdt);
}

/**
  * @brief  set the 32-bit initial data of crc
  * @param  value: initial data
  * @retval 无
  */
void CRC_Init_Data_Set(uint32_t value) {
    CRC->idt = value;
}

/**
  * @brief  control the reversal of the bit order in the input data
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRC_Reverse_Input_NO_AFFECTE
  *         - CRC_Reverse_Input_BY_BYTE
  *         - CRC_Reverse_Input_BY_HALFWORD
  *         - CRC_Reverse_Input_BY_WORD
  * @retval 无.
  */
void CRC_Reverse_Input_Data_Set(CRC_Reverse_Input_Type value) {
    CRC->ctrl_bit.revid = value;
}

/**
  * @brief  control the reversal of the bit order in the output data
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRC_Reverse_OutPut_NO_AFFECTE
  *         - CRC_Reverse_OutPut_DATA
  * @retval 无.
  */
void CRC_Reverse_OutPut_Data_Set(CRC_Reverse_OutPut_Type value) {
    CRC->ctrl_bit.revod = value;
}

#endif
