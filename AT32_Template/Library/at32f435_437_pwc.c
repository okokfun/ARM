/**
  **************************************************************************
  * @file     at32f435_437_pwc.c
  * @brief    contains all the functions for the pwc firmware library
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

/** @defgroup PWC
  * @brief PWC driver modules
  */

#ifdef PWC_MODULE_EnableD

/** @defgroup PWC_private_functions
  */

/**
  * @brief  deinitialize the pwc peripheral registers to their default reset values.
  * @param  无
  * @retval 无
  */
void PWC_Reset(void) {
    CRM_Periph_Reset(CRM_PWC_Periph_Reset, TRUE);
    CRM_Periph_Reset(CRM_PWC_Periph_Reset, FALSE);
}

/**
  * @brief  enable or disable access to the battery powered domain.
  * @param  new_state: new state of battery powered domain access.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void PWC_Battery_Powered_Domain_Access(confirm_state new_state) {
    PWC->ctrl_bit.bpwen = new_state;
}

/**
  * @brief  select the voltage threshold detected by the power voltage detector.
  * @param  pvm_voltage: select pwc pvm voltage
  *         该参数可以是以下值之一:
  *         - PWC_PVM_Voltage_2V3
  *         - PWC_PVM_Voltage_2V4
  *         - PWC_PVM_Voltage_2V5
  *         - PWC_PVM_Voltage_2V6
  *         - PWC_PVM_Voltage_2V7
  *         - PWC_PVM_Voltage_2V8
  *         - PWC_PVM_Voltage_2V9
  * @retval 无
  */
void PWC_PVM_level_Select(PWC_PVM_Voltage_Type pvm_voltage) {
    PWC->ctrl_bit.pvmsel = pvm_voltage;
}

/**
  * @brief  enable or disable pwc power voltage monitor (pvm)
  * @param  new_state: new state of pvm.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void PWC_Power_Voltage_Monitor_Enable(confirm_state new_state) {
    PWC->ctrl_bit.pvmen = new_state;
}

/**
  * @brief  enable or disable pwc standby wakeup pin
  * @param  pin_Num: choose the wakeup pin.
  *         该参数可以是 be any combination of the following values:
  *         - PWC_WakeUp_Pin_1
  *         - PWC_WakeUp_Pin_2
  * @param  new_state: new state of the standby wakeup pin.
  *         该参数可以是以下值之一:
  *         - TRUE <wakeup pin is used for wake up cpu from standby mode>
  *         - FALSE <wakeup pin is used for general purpose I/O>
  * @retval 无
  */
void PWC_WakeUp_Pin_Enable(uint32_t pin_Num, confirm_state new_state) {
    if(new_state == TRUE) {
        PWC->ctrlsts |= pin_Num;
    } else {
        PWC->ctrlsts &= ~pin_Num;
    }
}

/**
  * @brief  clear flag of pwc
  * @param  PWC_flag: select the pwc flag.
  *         该参数可以是以下值的任意组合:
  *         - PWC_WakeUp_FLAG
  *         - PWC_Standby_FLAG
  *         - note:"PWC_PVM_OutPut_FLAG" cannot be choose!this bit is readonly bit,it means the voltage monitoring output state
  * @retval 无
  */
void PWC_Flag_Clear(uint32_t PWC_flag) {
    if(PWC_flag & PWC_Standby_FLAG)
        PWC->ctrl_bit.clsef = TRUE;

    if(PWC_flag & PWC_WakeUp_FLAG)
        PWC->ctrl_bit.clswef = TRUE;
}

/**
  * @brief  get flag of pwc
  * @param  PWC_flag: select the pwc flag.
  *         该参数可以是以下值之一:
  *         - PWC_WakeUp_FLAG
  *         - PWC_Standby_FLAG
  *         - PWC_PVM_OutPut_FLAG
  * @retval state of select flag(SET or RESET).
  */
flag_status PWC_Flag_Get(uint32_t PWC_flag) {
    flag_status status = RESET;

    if ((PWC->ctrlsts & PWC_flag) == RESET) {
        status = RESET;
    } else {
        status = SET;
    }

    return status;
}

/**
  * @brief  enter pwc sleep mode
  * @param  sleep_Mode_Enter: choose the instruction to enter sleep mode.
  *         该参数可以是以下值之一:
  *         - PWC_Sleep_Enter_WFI
  *         - PWC_Sleep_Enter_WFE
  * @retval 无
  */
void PWC_Sleep_Mode_Enter(PWC_Sleep_Enter_Type PWC_Sleep_Enter) {
    SCB->SCR &= (uint32_t)~0x4;

    if(PWC_Sleep_Enter == PWC_Sleep_Enter_WFE) {
        __SEV();
        __WFE();
        __WFE();
    } else if(PWC_Sleep_Enter == PWC_Sleep_Enter_WFI) {
        __WFI();
    }
}

/**
  * @brief  enter pwc deep-sleep mode
  * @param  PWC_Deep_Sleep_Enter: choose the instruction to enter deep sleep mode.
  *         该参数可以是以下值之一:
  *         - PWC_Deep_Sleep_Enter_WFI
  *         - PWC_Deep_Sleep_Enter_WFE
  * @retval 无
  */
void PWC_Deep_Sleep_Mode_Enter(PWC_Deep_Sleep_Enter_Type PWC_Deep_Sleep_Enter) {
    SCB->SCR |= 0x04;

    if(PWC_Deep_Sleep_Enter == PWC_Deep_Sleep_Enter_WFE) {
        __SEV();
        __WFE();
        __WFE();
    } else if(PWC_Deep_Sleep_Enter == PWC_Deep_Sleep_Enter_WFI) {
        __WFI();
    }

    SCB->SCR &= (uint32_t)~0x4;
}

/**
  * @brief  regulate low power consumption in the deep sleep mode
  * @param  PWC_regulator: set the regulator state.
  *         该参数可以是以下值之一:
  *         - PWC_REGULATOR_ON
  *         - PWC_REGULATOR_Low_POWER
  * @retval 无
  */
void PWC_Voltage_Regulate_Set(PWC_regulator_Type PWC_regulator) {
    PWC->ctrl_bit.vrsel = PWC_regulator;
}

/**
  * @brief  enter pwc standby mode
  * @param  无
  * @retval 无
  */
void PWC_Standby_Mode_Enter(void) {
    PWC->ctrl_bit.clswef = TRUE;
    PWC->ctrl_bit.lpsel = TRUE;
    SCB->SCR |= 0x04;
    #if defined (__CC_ARM)
    __Force_stores();
    #endif

    while(1) {
        __WFI();
    }
}

#endif
