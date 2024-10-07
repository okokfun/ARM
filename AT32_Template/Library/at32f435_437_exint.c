/**
  **************************************************************************
  * @file     at32f435_437_exint.c
  * @brief    contains all the functions for the exint firmware library
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

/** @defgroup EXINT
  * @brief EXINT driver modules
  */

#ifdef EXINT_MODULE_EnableD

/** @defgroup EXINT_private_functions
  */

/**
  * @brief  exint reset
  * @param  无
  * @retval 无
  */
void EXINT_Reset(void) {
    EXINT->inten = 0x00000000;
    EXINT->polcfg1 = 0x00000000;
    EXINT->polcfg2 = 0x00000000;
    EXINT->evten = 0x00000000;
    EXINT->intsts = 0x007FFFFF;
}

/**
  * @brief  exint default para init
  * @param  EXINT_struct
  *         - to the structure of EXINT_Init_Type
  * @retval 无
  */
void EXINT_Default_Para_Init(EXINT_Init_Type *EXINT_struct) {
    EXINT_struct->line_Enable = FALSE;
    EXINT_struct->line_Select = EXINT_Line_NONE;
    EXINT_struct->line_polarity = EXINT_Trigger_FALLING_EDGE;
    EXINT_struct->line_Mode = EXINT_Line_EVENT;
}

/**
  * @brief  exint init
  * @param  EXINT_struct
  *         - to the structure of EXINT_Init_Type
  * @retval 无
  */
void EXINT_Init(EXINT_Init_Type *EXINT_struct) {
    uint32_t line_index = 0;
    line_index = EXINT_struct->line_Select;

    EXINT->inten &= ~line_index;
    EXINT->evten &= ~line_index;

    if(EXINT_struct->line_Enable != FALSE) {
        if(EXINT_struct->line_Mode == EXINT_Line_INTERRUPUT) {
            EXINT->inten |= line_index;
        } else {
            EXINT->evten |= line_index;
        }

        EXINT->polcfg1 &= ~line_index;
        EXINT->polcfg2 &= ~line_index;

        if(EXINT_struct->line_polarity == EXINT_Trigger_RISING_EDGE) {
            EXINT->polcfg1 |= line_index;
        } else if(EXINT_struct->line_polarity == EXINT_Trigger_FALLING_EDGE) {
            EXINT->polcfg2 |= line_index;
        } else {
            EXINT->polcfg1 |= line_index;
            EXINT->polcfg2 |= line_index;
        }
    }
}

/**
  * @brief  clear exint flag
  * @param  EXINT_line
  *         该参数可以是以下值的任意组合:
  *         - EXINT_Line_0
  *         - EXINT_Line_1
  *         ...
  *         - EXINT_Line_21
  *         - EXINT_Line_22
  * @retval 无
  */
void EXINT_Flag_Clear(uint32_t EXINT_line) {
    EXINT->intsts = EXINT_line;
}

/**
  * @brief  get exint flag
  * @param  EXINT_line
  *         该参数可以是以下值之一:
  *         - EXINT_Line_0
  *         - EXINT_Line_1
  *         ...
  *         - EXINT_Line_21
  *         - EXINT_Line_22
  * @retval the new state of exint flag(SET or RESET).
  */
flag_status EXINT_Flag_Get(uint32_t EXINT_line) {
    flag_status status = RESET;
    uint32_t EXINT_flag = 0;
    EXINT_flag = EXINT->intsts & EXINT_line;

    if((EXINT_flag != (uint16_t)RESET)) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/**
  * @brief  generate exint software interrupt event
  * @param  EXINT_line
  *         该参数可以是以下值之一:
  *         - EXINT_Line_0
  *         - EXINT_Line_1
  *         ...
  *         - EXINT_Line_21
  *         - EXINT_Line_22
  * @retval 无
  */
void EXINT_Software_Interrupt_Event_Generate(uint32_t EXINT_line) {
    EXINT->swtrg |= EXINT_line;
}

/**
  * @brief  enable or disable exint interrupt
  * @param  EXINT_line
  *         该参数可以是以下值的任意组合:
  *         - EXINT_Line_0
  *         - EXINT_Line_1
  *         ...
  *         - EXINT_Line_21
  *         - EXINT_Line_22
  * @param  new_state: new state of exint interrupt.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void EXINT_Interrupt_Enable(uint32_t EXINT_line, confirm_state new_state) {
    if(new_state == TRUE) {
        EXINT->inten |= EXINT_line;
    } else {
        EXINT->inten &= ~EXINT_line;
    }
}

/**
  * @brief  enable or disable exint event
  * @param  EXINT_line
  *         该参数可以是以下值的任意组合:
  *         - EXINT_Line_0
  *         - EXINT_Line_1
  *         ...
  *         - EXINT_Line_21
  *         - EXINT_Line_22
  * @param  new_state: new state of exint event.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void EXINT_Event_Enable(uint32_t EXINT_line, confirm_state new_state) {
    if(new_state == TRUE) {
        EXINT->evten |= EXINT_line;
    } else {
        EXINT->evten &= ~EXINT_line;
    }
}

#endif
