/**
  **************************************************************************
  * @file     at32f435_437_wwdt.c
  * @brief    contains all the functions for the wwdt firmware library
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

/** @defgroup WWDT
  * @brief WWDT driver modules
  */

#ifdef WWDT_MODULE_EnableD

/** @defgroup WWDT_private_functions
  */

/**
  * @brief  wwdt reset by crm reset register
  * @retval 无
  */
void wWDT_Reset(void) {
    CRM_Periph_Reset(CRM_WWDT_Periph_Reset, TRUE);
    CRM_Periph_Reset(CRM_WWDT_Periph_Reset, FALSE);
}

/**
  * @brief  wwdt division set
  * @param  division
  *         该参数可以是以下值之一:
  *         - WWDT_PCLK1_Div_4096        (wwdt counter clock = (pclk1/4096)/1)
  *         - WWDT_PCLK1_Div_8192        (wwdt counter clock = (pclk1/4096)/2)
  *         - WWDT_PCLK1_Div_16384       (wwdt counter clock = (pclk1/4096)/4)
  *         - WWDT_PCLK1_Div_32768       (wwdt counter clock = (pclk1/4096)/8)
  * @retval 无
  */
void wWDT_Divider_Set(wWDT_Division_Type division) {
    WWDT->cfg_bit.div = division;
}

/**
  * @brief  wwdt reload counter interrupt flag clear
  * @param  无
  * @retval 无
  */
void wWDT_Flag_Clear(void) {
    WWDT->sts = 0;
}

/**
  * @brief  wwdt enable and the counter value load
  * @param  wWDT_cnt (0x40~0x7f)
  * @retval 无
  */
void wWDT_Enable(uint8_t wWDT_cnt) {
    WWDT->ctrl = wWDT_cnt | WWDT_EN_BIT;
}

/**
  * @brief  wwdt reload counter interrupt enable
  * @param  无
  * @retval 无
  */
void wWDT_Interrupt_Enable(void) {
    WWDT->cfg_bit.rldien = TRUE;
}

/**
  * @brief  wwdt reload counter interrupt flag get
  * @param  无
  * @retval state of reload counter interrupt flag
  */
flag_status wWDT_Flag_Get(void) {
    return (flag_status)WWDT->sts_bit.rldf;
}

/**
  * @brief  wwdt counter value set
  * @param  wWDT_cnt (0x40~0x7f)
  * @retval 无
  */
void wWDT_Counter_Set(uint8_t wWDT_cnt) {
    WWDT->ctrl_bit.cnt = wWDT_cnt;
}

/**
  * @brief  wwdt window counter value set
  * @param  window_cnt (0x40~0x7f)
  * @retval 无
  */
void wWDT_Window_Counter_Set(uint8_t window_cnt) {
    WWDT->cfg_bit.win = window_cnt;
}

#endif
