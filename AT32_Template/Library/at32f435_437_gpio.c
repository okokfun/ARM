/**
  **************************************************************************
  * @file     at32f435_437_gpio.c
  * @brief    contains all the functions for the gpio firmware library
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

/** @addtogroup AT32F435_437_periph_driver
  * @{
  */

/** @defgroup GPIO
  * @brief GPIO driver modules
  * @{
  */

#ifdef GPIO_MODULE_EnableD

/** @defgroup GPIO_private_functions
  * @{
  */

/**
  * @brief  reset the gpio register
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @retval none
  */
void gpio_Reset(GPIO_Type *gpio_x) {
    if(gpio_x == GPIOA) {
        crm_periph_Reset(CRM_GPIOA_PERIPH_Reset, TRUE);
        crm_periph_Reset(CRM_GPIOA_PERIPH_Reset, FALSE);
    } else if(gpio_x == GPIOB) {
        crm_periph_Reset(CRM_GPIOB_PERIPH_Reset, TRUE);
        crm_periph_Reset(CRM_GPIOB_PERIPH_Reset, FALSE);
    } else if(gpio_x == GPIOC) {
        crm_periph_Reset(CRM_GPIOC_PERIPH_Reset, TRUE);
        crm_periph_Reset(CRM_GPIOC_PERIPH_Reset, FALSE);
    } else if(gpio_x == GPIOD) {
        crm_periph_Reset(CRM_GPIOD_PERIPH_Reset, TRUE);
        crm_periph_Reset(CRM_GPIOD_PERIPH_Reset, FALSE);
    } else if(gpio_x == GPIOE) {
        crm_periph_Reset(CRM_GPIOE_PERIPH_Reset, TRUE);
        crm_periph_Reset(CRM_GPIOE_PERIPH_Reset, FALSE);
    } else if(gpio_x == GPIOF) {
        crm_periph_Reset(CRM_GPIOF_PERIPH_Reset, TRUE);
        crm_periph_Reset(CRM_GPIOF_PERIPH_Reset, FALSE);
    } else if(gpio_x == GPIOG) {
        crm_periph_Reset(CRM_GPIOG_PERIPH_Reset, TRUE);
        crm_periph_Reset(CRM_GPIOG_PERIPH_Reset, FALSE);
    } else if(gpio_x == GPIOH) {
        crm_periph_Reset(CRM_GPIOH_PERIPH_Reset, TRUE);
        crm_periph_Reset(CRM_GPIOH_PERIPH_Reset, FALSE);
    }
}

/**
  * @brief  initialize the gpio peripheral.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  gpio_Init_struct: pointer to gpio init structure.
  * @retval none
  */
void GPIO_Init(GPIO_Type *gpio_x, GPIO_Init_Type *gpio_Init_struct) {
    uint16_t pinx_value, pin_index = 0;

    pinx_value = (uint16_t)gpio_Init_struct->GPIO_Pins;

    while(pinx_value > 0) {
        if(pinx_value & 0x01) {
            gpio_x->cfgr  &= (uint32_t)~(0x03 << (pin_index * 2));
            gpio_x->cfgr  |= (uint32_t)(gpio_Init_struct->GPIO_Mode << (pin_index * 2));

            gpio_x->omode &= (uint32_t)~(0x01 << (pin_index));
            gpio_x->omode |= (uint32_t)(gpio_Init_struct->GPIO_Out_Type << (pin_index));

            gpio_x->odrvr &= (uint32_t)~(0x03 << (pin_index * 2));
            gpio_x->odrvr |= (uint32_t)(gpio_Init_struct->GPIO_Drive_Strength << (pin_index * 2));

            gpio_x->pull  &= (uint32_t)~(0x03 << (pin_index * 2));
            gpio_x->pull  |= (uint32_t)(gpio_Init_struct->GPIO_Pull << (pin_index * 2));
        }

        pinx_value >>= 1;
        pin_index++;
    }
}

/**
  * @brief  fill each gpio_Init_Type member with its default value.
  * @param  gpio_Init_struct : pointer to a gpio_Init_Type structure which will be initialized.
  * @retval none
  */
void GPIO_Default_Para_Init(GPIO_Init_Type *gpio_Init_struct) {
    /* reset gpio init structure parameters values */
    gpio_Init_struct->GPIO_Pins  = GPIO_Pins_ALL;
    gpio_Init_struct->GPIO_Mode = GPIO_Mode_INPUT;
    gpio_Init_struct->GPIO_Out_Type = GPIO_OutPut_PUSH_PULL;
    gpio_Init_struct->GPIO_Pull = GPIO_Pull_NONE;
    gpio_Init_struct->GPIO_Drive_Strength = GPIO_Drive_Strength_STRONGER;
}

/**
  * @brief  read the specified input port pin.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  pins: gpio pin number
  *         this parameter can be one of the following values:
  *         - GPIO_Pins_0
  *         - GPIO_Pins_1
  *         - GPIO_Pins_2
  *         - GPIO_Pins_3
  *         - GPIO_Pins_4
  *         - GPIO_Pins_5
  *         - GPIO_Pins_6
  *         - GPIO_Pins_7
  *         - GPIO_Pins_8
  *         - GPIO_Pins_9
  *         - GPIO_Pins_10
  *         - GPIO_Pins_11
  *         - GPIO_Pins_12
  *         - GPIO_Pins_13
  *         - GPIO_Pins_14
  *         - GPIO_Pins_15
  * @retval flag_status (SET or RESET)
  */
flag_status GPIO_Input_Data_Bit_Read(GPIO_Type *gpio_x, uint16_t pins) {
    flag_status status = RESET;

    if(pins != (pins & gpio_x->idt)) {
        status = RESET;
    } else {
        status = SET;
    }

    return status;
}

/**
  * @brief  read the specified gpio input data port.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @retval gpio input data port value.
  */
uint16_t GPIO_Input_Data_Read(GPIO_Type *gpio_x) {
    return ((uint16_t)(gpio_x->idt));
}

/**
  * @brief  read the specified output port pin.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  pins: gpio pin number
  *         this parameter can be one of the following values:
  *         - GPIO_Pins_0
  *         - GPIO_Pins_1
  *         - GPIO_Pins_2
  *         - GPIO_Pins_3
  *         - GPIO_Pins_4
  *         - GPIO_Pins_5
  *         - GPIO_Pins_6
  *         - GPIO_Pins_7
  *         - GPIO_Pins_8
  *         - GPIO_Pins_9
  *         - GPIO_Pins_10
  *         - GPIO_Pins_11
  *         - GPIO_Pins_12
  *         - GPIO_Pins_13
  *         - GPIO_Pins_14
  *         - GPIO_Pins_15
  * @retval flag_status (SET or RESET)
  */
flag_status GPIO_OutPut_Data_Bit_Read(GPIO_Type *gpio_x, uint16_t pins) {
    flag_status status = RESET;

    if((gpio_x->odt & pins) != RESET) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/**
  * @brief  read the specified gpio ouput data port.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @retval gpio input data port value.
  */
uint16_t GPIO_OutPut_Data_Read(GPIO_Type *gpio_x) {
    return ((uint16_t)(gpio_x->odt));
}

/**
  * @brief  set the selected data port bits.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_Pin_x, gpio_Pin_x as following values:
  *         - GPIO_Pins_0
  *         - GPIO_Pins_1
  *         - GPIO_Pins_2
  *         - GPIO_Pins_3
  *         - GPIO_Pins_4
  *         - GPIO_Pins_5
  *         - GPIO_Pins_6
  *         - GPIO_Pins_7
  *         - GPIO_Pins_8
  *         - GPIO_Pins_9
  *         - GPIO_Pins_10
  *         - GPIO_Pins_11
  *         - GPIO_Pins_12
  *         - GPIO_Pins_13
  *         - GPIO_Pins_14
  *         - GPIO_Pins_15
  *         - GPIO_Pins_ALL
  * @retval none
  */
void GPIO_Bits_Set(GPIO_Type *gpio_x, uint16_t pins) {
    gpio_x->scr = pins;
}

/**
  * @brief  clear the selected data port bits.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_Pin_x, gpio_Pin_x as following values:
  *         - GPIO_Pins_0
  *         - GPIO_Pins_1
  *         - GPIO_Pins_2
  *         - GPIO_Pins_3
  *         - GPIO_Pins_4
  *         - GPIO_Pins_5
  *         - GPIO_Pins_6
  *         - GPIO_Pins_7
  *         - GPIO_Pins_8
  *         - GPIO_Pins_9
  *         - GPIO_Pins_10
  *         - GPIO_Pins_11
  *         - GPIO_Pins_12
  *         - GPIO_Pins_13
  *         - GPIO_Pins_14
  *         - GPIO_Pins_15
  *         - GPIO_Pins_ALL
  * @retval none
  */
void GPIO_Bits_Reset(GPIO_Type *gpio_x, uint16_t pins) {
    gpio_x->clr = pins;
}

/**
  * @brief  set or clear the selected data port bit.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_Pin_x, gpio_Pin_x as following values:
  *         - GPIO_Pins_0
  *         - GPIO_Pins_1
  *         - GPIO_Pins_2
  *         - GPIO_Pins_3
  *         - GPIO_Pins_4
  *         - GPIO_Pins_5
  *         - GPIO_Pins_6
  *         - GPIO_Pins_7
  *         - GPIO_Pins_8
  *         - GPIO_Pins_9
  *         - GPIO_Pins_10
  *         - GPIO_Pins_11
  *         - GPIO_Pins_12
  *         - GPIO_Pins_13
  *         - GPIO_Pins_14
  *         - GPIO_Pins_15
  *         - GPIO_Pins_ALL
  * @param  bit_state: specifies the value to be written to the selected bit (TRUE or FALSE).
  * @retval none
  */
void GPIO_Bits_Write(GPIO_Type *gpio_x, uint16_t pins, confirm_state bit_state) {
    if(bit_state != FALSE) {
        gpio_x->scr = pins;
    } else {
        gpio_x->clr = pins;
    }
}

/**
  * @brief  write data to the specified gpio data port.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  port_value: specifies the value to be written to the port output data register.
  * @retval none
  */
void GPIO_Port_Write(GPIO_Type *gpio_x, uint16_t port_value) {
    gpio_x->odt = port_value;
}

/**
  * @brief  write protect gpio pins configuration registers.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  pins: gpio pin number
  *         this parameter can be any combination of the following:
  *         - GPIO_Pins_0
  *         - GPIO_Pins_1
  *         - GPIO_Pins_2
  *         - GPIO_Pins_3
  *         - GPIO_Pins_4
  *         - GPIO_Pins_5
  *         - GPIO_Pins_6
  *         - GPIO_Pins_7
  *         - GPIO_Pins_8
  *         - GPIO_Pins_9
  *         - GPIO_Pins_10
  *         - GPIO_Pins_11
  *         - GPIO_Pins_12
  *         - GPIO_Pins_13
  *         - GPIO_Pins_14
  *         - GPIO_Pins_15
  *         - GPIO_Pins_ALL
  * @retval none
  */
void GPIO_Pin_WP_Config(GPIO_Type *gpio_x, uint16_t pins) {
    uint32_t temp = 0x00010000;

    temp |= pins;
    /* set wpen bit */
    gpio_x->wpr = temp;
    /* reset wpen bit */
    gpio_x->wpr =  pins;
    /* set wpen bit */
    gpio_x->wpr = temp;
    /* read wpen bit*/
    temp = gpio_x->wpr;
    /* read wpen bit*/
    temp = gpio_x->wpr;
}

/**
  * @brief  enable or disable gpio pins huge driven.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  pins: gpio pin number
  *         parameter can be any combination of gpio_Pin_x, gpio_Pin_x as following values:
  *         - GPIO_Pins_0
  *         - GPIO_Pins_1
  *         - GPIO_Pins_2
  *         - GPIO_Pins_3
  *         - GPIO_Pins_4
  *         - GPIO_Pins_5
  *         - GPIO_Pins_6
  *         - GPIO_Pins_7
  *         - GPIO_Pins_8
  *         - GPIO_Pins_9
  *         - GPIO_Pins_10
  *         - GPIO_Pins_11
  *         - GPIO_Pins_12
  *         - GPIO_Pins_13
  *         - GPIO_Pins_14
  *         - GPIO_Pins_15
  *         - GPIO_Pins_ALL
  * @param  new_state: new state of the slew rate.
  *         this parameter can be: true or false.
  * @retval none
  */
void GPIO_Pins_Huge_Driven_Config(GPIO_Type *gpio_x, uint16_t pins, confirm_state new_state) {
    if(new_state != FALSE) {
        gpio_x->hdrv |= pins;
    } else {
        gpio_x->hdrv &= ~pins;
    }
}

/**
  * @brief  configure the pin's muxing function.
  * @param  gpio_x: to select the gpio peripheral.
  *         this parameter can be one of the following values:
  *         GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH.
  * @param  gpio_Pin_source: specifies the pin for the muxing function.
  *         this parameter can be one of the following values:
  *         - GPIO_Pins_SOURCE0
  *         - GPIO_Pins_SOURCE1
  *         - GPIO_Pins_SOURCE2
  *         - GPIO_Pins_SOURCE3
  *         - GPIO_Pins_SOURCE4
  *         - GPIO_Pins_SOURCE5
  *         - GPIO_Pins_SOURCE6
  *         - GPIO_Pins_SOURCE7
  *         - GPIO_Pins_SOURCE8
  *         - GPIO_Pins_SOURCE9
  *         - GPIO_Pins_SOURCE10
  *         - GPIO_Pins_SOURCE11
  *         - GPIO_Pins_SOURCE12
  *         - GPIO_Pins_SOURCE13
  *         - GPIO_Pins_SOURCE14
  *         - GPIO_Pins_SOURCE15
  * @param  gpio_mux: select the pin to used as muxing function.
  *         this parameter can be one of the following values:
  *         - GPIO_MUX_0
  *         - GPIO_MUX_1
  *         - GPIO_MUX_2
  *         - GPIO_MUX_3
  *         - GPIO_MUX_4
  *         - GPIO_MUX_5
  *         - GPIO_MUX_6
  *         - GPIO_MUX_7
  *         - GPIO_MUX_8
  *         - GPIO_MUX_9
  *         - GPIO_MUX_10
  *         - GPIO_MUX_11
  *         - GPIO_MUX_12
  *         - GPIO_MUX_13
  *         - GPIO_MUX_14
  *         - GPIO_MUX_15
  * @retval none
  */
void GPIO_Pin_Mux_Config(GPIO_Type *gpio_x, GPIO_Pins_Source_Type gpio_Pin_source, GPIO_Mux_Sel_Type gpio_mux) {
    uint32_t temp = 0x00;
    uint32_t temp_2 = 0x00;

    temp = ((uint32_t)(gpio_mux) << ((uint32_t)((uint32_t)gpio_Pin_source & (uint32_t)0x07) * 4));

    if(gpio_Pin_source >> 0x03) {
        gpio_x->muxh &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)gpio_Pin_source & (uint32_t)0x07) * 4));
        temp_2 = gpio_x->muxh | temp;
        gpio_x->muxh = temp_2;
    } else {
        gpio_x->muxl &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)gpio_Pin_source & (uint32_t)0x07) * 4));
        temp_2 = gpio_x->muxl | temp;
        gpio_x->muxl = temp_2;
    }
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
