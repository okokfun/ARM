/**
  **************************************************************************
  * @file     at32f435_437_scfg.c
  * @brief    contains all the functions for the system config firmware library
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

/** @defgroup SCFG
  * @brief SCFG driver modules
  */

#ifdef SCFG_MODULE_EnableD

/** @defgroup SCFG_private_functions
  */

/**
  * @brief  scfg reset
  * @param  无
  * @retval 无
  */
void SCFG_Reset(void) {
    CRM_Periph_Reset(CRM_SCFG_Periph_Reset, TRUE);
    CRM_Periph_Reset(CRM_SCFG_Periph_Reset, FALSE);
}

/**
  * @brief  scfg xmc address mapping swap set
  * @param  XMC_Swap
  *         该参数可以是以下值之一:
  *         - SCFG_XMC_Swap_NONE
  *         - SCFG_XMC_Swap_Mode1
  *         - SCFG_XMC_Swap_Mode2
  *         - SCFG_XMC_Swap_Mode3
  * @retval 无
  */
void SCFG_XMC_Mapping_Swap_Set(SCFG_XMC_Swap_Type XMC_Swap) {
    SCFG->cfg1_bit.swap_xmc = XMC_Swap;
}

/**
  * @brief  scfg infrared config
  * @param  source
  *         该参数可以是以下值之一:
  *         - SCFG_IR_Source_TMR10
  *         - SCFG_IR_Source_USART1
  *         - SCFG_IR_Source_USART2
  * @param  polarity
  *         该参数可以是以下值之一:
  *         - SCFG_IR_Polarity_NO_AFFECTE
  *         - SCFG_IR_Polarity_REVERSE
  * @retval 无
  */
void SCFG_Infrared_Config(SCFG_IR_Source_Type source, SCFG_IR_Polarity_Type polarity) {
    SCFG->cfg1_bit.ir_src_sel = source;
    SCFG->cfg1_bit.ir_pol = polarity;
}

/**
  * @brief  scfg memory address mapping set
  * @param  mem_map
  *         该参数可以是以下值之一:
  *         - SCFG_Mem_Map_MAIN_MEMORY
  *         - SCFG_Mem_Map_BOOT_MEMORY
  *         - SCFG_Mem_Map_XMC_BANK1
  *         - SCFG_Mem_Map_Internal_SRAM
  *         - SCFG_Mem_Map_XMC_SDRAM_BANK1
  * @retval 无
  */
void SCFG_Mem_Map_Set(SCFG_Mem_Map_Type mem_map) {
    SCFG->cfg1_bit.mem_Map_sel = mem_map;
}

/**
  * @brief  scfg emac interface set
  * @param  mode
  *         该参数可以是以下值之一:
  *         - SCFG_EMAC_Select_MII
  *         - SCFG_EMAC_Select_RMII
  * @retval 无
  */
void SCFG_EMAC_Interface_Set(SCFG_EMAC_Interface_Type mode) {
    SCFG->cfg2_bit.mii_rmii_sel = mode;
}

/**
  * @brief  select the gpio pin used as exint line.
  * @param  port_source:
  *         select the gpio port to be used as source for exint lines.
  *         该参数可以是以下值之一:
  *         - SCFG_Port_Source_GPIOA
  *         - SCFG_Port_Source_GPIOB
  *         - SCFG_Port_Source_GPIOC
  *         - SCFG_Port_Source_GPIOD
  *         - SCFG_Port_Source_GPIOE
  *         - SCFG_Port_Source_GPIOF
  *         - SCFG_Port_Source_GPIOG
  *         - SCFG_Port_Source_GPIOH
  * @param  pin_source:
  *         specifies the exint line to be configured.
  *         该参数可以是以下值之一:
  *         - SCFG_Pins_SOURCE0
  *         - SCFG_Pins_SOURCE1
  *         - SCFG_Pins_SOURCE2
  *         - SCFG_Pins_SOURCE3
  *         - SCFG_Pins_SOURCE4
  *         - SCFG_Pins_SOURCE5
  *         - SCFG_Pins_SOURCE6
  *         - SCFG_Pins_SOURCE7
  *         - SCFG_Pins_SOURCE8
  *         - SCFG_Pins_SOURCE9
  *         - SCFG_Pins_SOURCE10
  *         - SCFG_Pins_SOURCE11
  *         - SCFG_Pins_SOURCE12
  *         - SCFG_Pins_SOURCE13
  *         - SCFG_Pins_SOURCE14
  *         - SCFG_Pins_SOURCE15
  * @retval 无
  */
void SCFG_EXINT_Line_Config(SCFG_Port_Source_Type port_source, SCFG_Pins_Source_Type pin_source) {
    uint32_t tmp = 0x00;
    tmp = ((uint32_t)0x0F) << (0x04 * (pin_source & (uint8_t)0x03));

    switch (pin_source >> 0x02) {
        case 0:
            SCFG->exintc1 &= ~tmp;
            SCFG->exintc1 |= (((uint32_t)port_source) << (0x04 * (pin_source & (uint8_t)0x03)));
            break;

        case 1:
            SCFG->exintc2 &= ~tmp;
            SCFG->exintc2 |= (((uint32_t)port_source) << (0x04 * (pin_source & (uint8_t)0x03)));
            break;

        case 2:
            SCFG->exintc3 &= ~tmp;
            SCFG->exintc3 |= (((uint32_t)port_source) << (0x04 * (pin_source & (uint8_t)0x03)));
            break;

        case 3:
            SCFG->exintc4 &= ~tmp;
            SCFG->exintc4 |= (((uint32_t)port_source) << (0x04 * (pin_source & (uint8_t)0x03)));
            break;

        default:
            break;
    }
}

/**
  * @brief  enable or disable gpio pins ultra driven.
  * @param  value:
  *         该参数可以是以下值之一:
  *         - SCFG_Ultra_Driven_PB3
  *         - SCFG_Ultra_Driven_PB9
  *         - SCFG_Ultra_Driven_PB10
  *         - SCFG_Ultra_Driven_PD12
  *         - SCFG_Ultra_Driven_PD13
  *         - SCFG_Ultra_Driven_PD14
  *         - SCFG_Ultra_Driven_PD15
  *         - SCFG_Ultra_Driven_PF14
  *         - SCFG_Ultra_Driven_PF15
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SCFG_Pins_Ultra_Driven_Enable(SCFG_Ultra_Driven_Pins_Type value, confirm_state new_state) {
    if(TRUE == new_state) {
        SCFG_REG(value) |= SCFG_REG_BIT(value);
    } else {
        SCFG_REG(value) &= ~(SCFG_REG_BIT(value));
    }
}

#endif
