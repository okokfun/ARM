/**
  **************************************************************************
  * @file     at32f435_437_mcudbg.c
  * @brief    contains all the functions for the mcudbg firmware library
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

/** @defgroup DEBUG
  * @brief DEBUG driver modules
  */

#ifdef DEBUG_MODULE_EnableD

/** @defgroup DEBUG_private_functions
  */

/**
  * @brief  get debug device id
  * @param  无
  * @retval the debug device id
  */
uint32_t DEBUG_Device_ID_Get(void) {
    return DEBUGMCU->pid;
}
/**
  * @brief  set periph debug mode
  * @param  periph_DEBUG_Mode
  *         该参数可以是以下值之一:
  *         - DEBUG_SLEEP
  *         - DEBUG_DEEPSLEEP
  *         - DEBUG_STANDBY
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DEBUG_Low_Power_Mode_Set(uint32_t low_Power_Mode, confirm_state new_state) {
    if(new_state != FALSE) {
        DEBUGMCU->ctrl |= low_Power_Mode;
    } else {
        DEBUGMCU->ctrl &= ~low_Power_Mode;
    }
}
/**
  * @brief  set apb1 periph debug mode
  * @param  periph_DEBUG_Mode
  *         该参数可以是以下值的任意组合:
  *         - DEBUG_TMR2_PAUSE                      - DEBUG_TMR3_PAUSE
  *         - DEBUG_TMR4_PAUSE                      - DEBUG_TMR5_PAUSE
  *         - DEBUG_TMR6_PAUSE                      - DEBUG_TMR7_PAUSE
  *         - DEBUG_TMR12_PAUSE                     - DEBUG_TMR13_PAUSE
  *         - DEBUG_TMR14_PAUSE                     - DEBUG_ERTC_PAUSE
  *         - DEBUG_WWDT_PAUSE                      - DEBUG_WDT_PAUSE
  *         - DEBUG_ERTC_512_PAUSE                  - DEBUG_I2C1_SmBus_TIMEOUT
  *         - DEBUG_I2C2_SmBus_TIMEOUT              - DEBUG_I2C3_SmBus_TIMEOUT
  *         - DEBUG_CAN1_PAUSE                      - DEBUG_CAN2_PAUSE
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DEBUG_APB1_Periph_Mode_Set(uint32_t apb1_periph, confirm_state new_state) {
    if(new_state != FALSE) {
        DEBUGMCU->apb1_frz |= apb1_periph;
    } else {
        DEBUGMCU->apb1_frz &= ~apb1_periph;
    }
}
/**
  * @brief  set apb2 periph debug mode
  * @param  periph_DEBUG_Mode
  *         该参数可以是以下值的任意组合:
  *         - DEBUG_TMR1_PAUSE                      - DEBUG_TMR8_PAUSE
  *         - DEBUG_TMR20_PAUSE                     - DEBUG_TMR9_PAUSE
  *         - DEBUG_TMR10_PAUSE                     - DEBUG_TMR11_PAUSE
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DEBUG_APB2_Periph_Mode_Set(uint32_t apb2_periph, confirm_state new_state) {
    if(new_state != FALSE) {
        DEBUGMCU->apb2_frz |= apb2_periph;
    } else {
        DEBUGMCU->apb2_frz &= ~apb2_periph;
    }
}

#endif
