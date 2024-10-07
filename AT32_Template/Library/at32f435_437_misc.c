/**
  **************************************************************************
  * @file     at32f435_437_misc.c
  * @brief    contains all the functions for the misc firmware library
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

/* includes ------------------------------------------------------------------*/
#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @defgroup MISC
  * @brief MISC driver modules
  */

#ifdef MISC_MODULE_EnableD

/** @defgroup MISC_private_functions
  */
#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/**
  * @brief  system reset
  * @param  无
  * @retval 无
  */
void NVIC_System_Reset(void) {
    NVIC_SystemReset();
}

/**
  * @brief  enable nvic irq
  * @param  irqn (IRQn_Type number)
  * @param  preempt_priority: preemptive priority value (starting from 0)
  * @param  sub_priority: subpriority value (starting from 0)
  * @retval 无
  */
void NVIC_IRQ_Enable(IRQn_Type irqn, uint32_t preempt_priority, uint32_t sub_priority) {
    uint32_t temp_priority = 0;

    /* encode priority */
    temp_priority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), preempt_priority, sub_priority);
    /* set priority */
    NVIC_SetPriority(irqn, temp_priority);
    /* enable irqn */
    NVIC_EnableIRQ(irqn);
}

/**
  * @brief  disable nvic irq number
  * @param  irqn (IRQn_Type number)
  * @retval 无
  */
void NVIC_IRQ_Disable(IRQn_Type irqn) {
    NVIC_DisableIRQ(irqn);
}

/**
  * @brief  config nvic priority group
  * @param  priority_group
  *         该参数可以是以下值之一:
  *         - NVIC_Priority_Group_0
  *         - NVIC_Priority_Group_1
  *         - NVIC_Priority_Group_2
  *         - NVIC_Priority_Group_3
  *         - NVIC_Priority_Group_4
  * @retval 无
  */
void NVIC_Priority_Group_Config(NVIC_Priority_Group_Type priority_group) {
    /* set the prigroup[10:8] bits 根据 NVIC_prioritygroup value */
    NVIC_SetPriorityGrouping(priority_group);
}

/**
  * @brief  set the vector table location and offset.
  * @param  base
  *         该参数可以是以下值之一:
  *         - NVIC_VECTTAB_RAM
  *         - NVIC_VECTTAB_FLASH
  * @param  offset (矢量表基偏移字段。 this value must be a multiple of 0x200)
  * @retval 无
  */
void NVIC_Vector_Table_Set(uint32_t base, uint32_t offset) {
    SCB->VTOR = base | (offset & (uint32_t)0x1FFFFF80);
}

/**
  * @brief  config nvic lowpower mode
  * @param  lp_Mode
  *         该参数可以是以下值之一:
  *         - NVIC_LP_SEVONPEND
  *         - NVIC_LP_SLEEPDEEP
  *         - NVIC_LP_SLEEPONEXIT
  * @param  new_state (new state of lp condition. ENABLE or DISABLE)
  * @retval 无
  */
void NVIC_LowPower_Mode_Config(NVIC_LowPower_Mode_Type lp_Mode, confirm_state new_state) {
    if(new_state != FALSE) {
        SCB->SCR |= lp_Mode;
    } else {
        SCB->SCR &= (uint32_t)(~(uint32_t)lp_Mode);
    }
}

/**
  * @brief  config systick clock source
  * @param  source
  *         该参数可以是以下值之一:
  *         - Systick_Clock_Source_AHBCLK_DIV8
  *         - Systick_Clock_Source_AHBCLK_NODIV
  * @retval 无
  */
void Systick_Clock_Source_Config(Systick_Clock_Source_Type source) {
    if(source == Systick_Clock_Source_AHBCLK_NODIV) {
        SysTick->CTRL |= Systick_Clock_Source_AHBCLK_NODIV;
    } else {
        SysTick->CTRL &= ~(uint32_t)Systick_Clock_Source_AHBCLK_NODIV;
    }
}

#endif


