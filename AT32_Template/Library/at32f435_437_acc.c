/**
  **************************************************************************
  * @file     at32f435_437_acc.c
  * @brief    contains all the functions for the acc firmware library
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

/** @defgroup ACC
  * @brief ACC driver modules
  */

#ifdef ACC_MODULE_EnableD

/** @defgroup ACC_private_functions
  */

/**
  * @brief  启用或禁用acc校准模式.
  * @param  ACC_trim: 指定acc校准类型.
  *         该参数可以是以下值之一:
  *         - ACC_CAL_HICKCAL
  *         - ACC_CAL_HICKTRIM
  * @param  new_state:指定要启用或禁用的acc校准。(TRUE or FALSE)
  * @retval 无
  */
void ACC_Calibration_Mode_Enable(uint16_t ACC_trim, confirm_state new_state) {
    if(ACC_trim == ACC_CAL_HICKCAL) {
        ACC->ctrl1_bit.entrim = FALSE;
    } else {
        ACC->ctrl1_bit.entrim = TRUE;
    }

    ACC->ctrl1_bit.calon = new_state;
}

/**
  * @brief  store calibration step data in acc's ctrl1 register.
  * @param  step_value:  value to be stored in the acc's ctrl1 register
  * @retval 无
  */
void ACC_Step_Set(uint8_t step_value) {
    ACC->ctrl1_bit.step = step_value;
}

/**
  * @brief  select sof sourse for acc in acc's ctrl1 register.
  * @param  sof_sel:  value to be stored in the acc's ctrl1 register
  *         该参数可以是以下值之一:
  *         @arg ACC_SOF_OTG1
  *         @arg ACC_SOF_OTG2
  * @retval 无
  */
void ACC_SOF_Select(uint16_t sof_sel) {
    ACC->ctrl1 |= sof_sel;
}

/**
  * @brief  enable or disable the specified acc interrupts.
  * @param  ACC_int: 指定acc interrupt sources to be enabled or disabled.
  *         该参数可以是以下值之一:
  *         - ACC_CALRDYIEN_INT
  *         - ACC_EIEN_INT
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void ACC_Interrupt_Enable(uint16_t ACC_int, confirm_state new_state) {
    if(ACC_int == ACC_CALRDYIEN_INT) {
        ACC->ctrl1_bit.calrdyien = new_state;
    } else {
        ACC->ctrl1_bit.eien = new_state;
    }
}

/**
  * @brief  返回当前 acc hicktrim value.
  * @param  无
  * @retval 8-bit hicktrim value.
  */
uint8_t ACC_Hicktrim_Get(void) {
    return ((uint8_t)(ACC->ctrl2_bit.hicktrim));
}

/**
  * @brief  返回当前 acc hickcal value.
  * @param  无
  * @retval 8-bit hicktrim value.
  */
uint8_t ACC_Hickcal_Get(void) {
    return ((uint8_t)(ACC->ctrl2_bit.hickcal));
}

/**
  * @brief  将值传送到wtire the value to  acc c1寄存器.
  * @param  ACC_C1_value
  * @retval 无.
  */
void ACC_Write_C1(uint16_t ACC_C1_value) {
    ACC->c1 = ACC_C1_value;
}

/**
  * @brief  将值传送到acc c2寄存器.
  * @param  ACC_C2_value
  * @retval 无.
  */
void ACC_Write_C2(uint16_t ACC_C2_value) {
    ACC->c2 = ACC_C2_value;
}

/**
  * @brief  将值传送到acc c3寄存器.
  * @param  ACC_C3_value
  * @retval 无.
  */
void ACC_Write_C3(uint16_t ACC_C3_value) {
    ACC->c3 = ACC_C3_value;
}

/**
  * @brief  返回当前 acc c1 值.
  * @param  无
  * @retval 16-bit c1 value.
  */
uint16_t ACC_Read_C1(void) {
    return ((uint16_t)(ACC->c1));
}

/**
  * @brief  返回当前 acc c2 值.
  * @param  无
  * @retval 16-bit c2 value.
  */
uint16_t ACC_Read_C2(void) {
    return ((uint16_t)(ACC->c2));
}

/**
  * @brief  返回当前 acc c3 值.
  * @param  无
  * @retval 16-bit c3 value.
  */
uint16_t ACC_Read_C3(void) {
    return ((uint16_t)(ACC->c3));
}

/**
  * @brief  check whether the specified acc flag is set or not.
  * @param  ACC_flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - ACC_RSLOST_FLAG
  *         - ACC_CALRDY_FLAG
  * @retval  flag_status (SET or RESET)
  */
flag_status ACC_Flag_Get(uint16_t ACC_flag) {
    if(ACC_flag == ACC_CALRDY_FLAG)
        return (flag_status)(ACC->sts_bit.calrdy);
    else
        return (flag_status)(ACC->sts_bit.rslost);
}

/**
  * @brief  clear the specified acc flag is set or not.
  * @param  ACC_flag: 指定flag to check.
  *         该参数可以是以下值的任意组合:
  *         - ACC_RSLOST_FLAG
  *         - ACC_CALRDY_FLAG
  * @retval  无
  */
void ACC_Flag_Clear(uint16_t ACC_flag) {
    ACC->sts = ~ACC_flag;
}

#endif
