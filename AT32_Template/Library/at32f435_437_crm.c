/**
  **************************************************************************
  * @file     at32f435_437_crm.c
  * @brief    contains all the functions for the crm firmware library
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

/** @defgroup CRM
  * @brief CRM driver modules
  */

#ifdef CRM_MODULE_EnableD

/** @defgroup CRM_private_functions
  */

/**
  * @brief  reset the crm register
  * @param  无
  * @retval 无
  */
void CRM_Reset(void) {
    /* 将CRM 时钟配置重置为默认重置状态(用于调试目的) */
    /* set hicken bit */
    CRM->ctrl_bit.hicken = TRUE;

    /* wait hick stable */
    while(CRM->ctrl_bit.hickstbl != SET);

    /* hick used as system clock */
    CRM->cfg_bit.sclksel = CRM_SCLK_HICK;

    /* wait sclk switch status */
    while(CRM->cfg_bit.sclksts != CRM_SCLK_HICK);

    /* reset hexten, hextbyps, cfden and pllen bits */
    CRM->ctrl &= ~(0x010D0000U);

    /* reset cfg register, include sclk switch, ahbdiv, apb1div, apb2div, adcdiv, clkout bits */
    CRM->cfg = 0;

    /* reset pllms pllns pllfr pllrcs bits */
    CRM->pllcfg = 0x00033002U;

    /* reset clkout[3], usbbufs, hickdiv, clkoutdiv */
    CRM->misc1 = 0;

    /* 禁用所有中断 enable and clear pending bits  */
    CRM->clkint = 0x009F0000U;
}

/**
  * @brief  enable or disable crm low speed external crystal bypass
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Lext_ByPass(confirm_state new_state) {
    CRM->bpdc_bit.lextbyps = new_state;
}

/**
  * @brief  enable or disable crm high speed external crystal bypass
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Hext_ByPass(confirm_state new_state) {
    CRM->ctrl_bit.hextbyps = new_state;
}

/**
  * @brief  get crm flag status
  * @param  flag
  *         该参数可以是以下值之一:
  *         - CRM_HICK_Stable_FLAG
  *         - CRM_Hext_Stable_FLAG
  *         - CRM_PLL_Stable_FLAG
  *         - CRM_Lext_Stable_FLAG
  *         - CRM_LICK_Stable_FLAG
  *         - CRM_Pin_Reset_FLAG
  *         - CRM_POR_Reset_FLAG
  *         - CRM_SW_Reset_FLAG
  *         - CRM_WDT_Reset_FLAG
  *         - CRM_WWDT_Reset_FLAG
  *         - CRM_LowPower_Reset_FLAG
  *         interrupt flag:
  *         - CRM_LICK_ReadY_INT_FLAG
  *         - CRM_Lext_ReadY_INT_FLAG
  *         - CRM_HICK_ReadY_INT_FLAG
  *         - CRM_Hext_ReadY_INT_FLAG
  *         - CRM_PLL_ReadY_INT_FLAG
  *         - CRM_Clock_Failure_INT_FLAG
  * @retval flag_status (SET or RESET)
  */
flag_status CRM_Flag_Get(uint32_t flag) {
    flag_status status = RESET;

    if((CRM_REG(flag) & CRM_REG_BIT(flag)) != CRM_REG_BIT(flag)) {
        status = RESET;
    } else {
        status = SET;
    }

    return status;
}

/**
  * @brief  wait for hext stable
  * @param  无
  * @retval error_status (ERROR or SUCCESS)
  */
error_status CRM_Hext_Stable_Wait(void) {
    uint32_t stable_cnt = 0;
    error_status status = ERROR;

    while((CRM_Flag_Get(CRM_Hext_Stable_FLAG) != SET) && (stable_cnt < HEXT_StartUP_TIMEOUT)) {
        stable_cnt ++;
    }

    if(CRM_Flag_Get(CRM_Hext_Stable_FLAG) != SET) {
        status = ERROR;
    } else {
        status = SUCCESS;
    }

    return status;
}

/**
  * @brief  set the hick trimming value
  * @param  trim_value (0x00~0x3F)
  * @retval 无
  */
void CRM_HICK_Clock_Trimming_Set(uint8_t trim_value) {
    CRM->ctrl_bit.hicktrim = trim_value;
}

/**
  * @brief  set the crm calibration value
  * @param  cali_value (0x00~0xFF)
  * @retval 无
  */
void CRM_HICK_Clock_Calibration_Set(uint8_t cali_value) {
    /* enable write hick calibration */
    CRM->misc1_bit.hickcal_key = 0x5A;

    /* write hick calibration value */
    CRM->ctrl_bit.hickcal = cali_value;

    /* disable write hick calibration */
    CRM->misc1_bit.hickcal_key = 0x0;
}

/**
  * @brief  enable or disable the peripheral clock
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_GPIOA_Periph_CLOCK        - CRM_GPIOB_Periph_CLOCK        - CRM_GPIOC_Periph_CLOCK       - CRM_GPIOD_Periph_CLOCK
  *         - CRM_GPIOE_Periph_CLOCK        - CRM_GPIOF_Periph_CLOCK        - CRM_GPIOG_Periph_CLOCK       - CRM_GPIOH_Periph_CLOCK
  *         - CRM_CRC_Periph_CLOCK          - CRM_EDMA_Periph_CLOCK         - CRM_DMA1_Periph_CLOCK        - CRM_DMA2_Periph_CLOCK
  *         - CRM_EMAC_Periph_CLOCK         - CRM_EMACTX_Periph_CLOCK       - CRM_EMACRX_Periph_CLOCK      - CRM_EMACPTP_Periph_CLOCK
  *         - CRM_OTGFS2_Periph_CLOCK       - CRM_DVP_Periph_CLOCK          - CRM_OTGFS1_Periph_CLOCK      - CRM_SDIO1_Periph_CLOCK
  *         - CRM_XMC_Periph_CLOCK          - CRM_QSPI1_Periph_CLOCK        - CRM_QSPI2_Periph_CLOCK       - CRM_SDIO2_Periph_CLOCK
  *         - CRM_TMR2_Periph_CLOCK         - CRM_TMR3_Periph_CLOCK         - CRM_TMR4_Periph_CLOCK        - CRM_TMR5_Periph_CLOCK
  *         - CRM_TMR6_Periph_CLOCK         - CRM_TMR7_Periph_CLOCK         - CRM_TMR12_Periph_CLOCK       - CRM_TMR13_Periph_CLOCK
  *         - CRM_TMR14_Periph_CLOCK        - CRM_WWDT_Periph_CLOCK         - CRM_SPI2_Periph_CLOCK        - CRM_SPI3_Periph_CLOCK
  *         - CRM_USART2_Periph_CLOCK       - CRM_USART3_Periph_CLOCK       - CRM_UART4_Periph_CLOCK       - CRM_UART5_Periph_CLOCK
  *         - CRM_I2C1_Periph_CLOCK         - CRM_I2C2_Periph_CLOCK         - CRM_I2C3_Periph_CLOCK        - CRM_CAN1_Periph_CLOCK
  *         - CRM_CAN2_Periph_CLOCK         - CRM_PWC_Periph_CLOCK          - CRM_DAC_Periph_CLOCK         - CRM_UART7_Periph_CLOCK
  *         - CRM_UART8_Periph_CLOCK        - CRM_TMR1_Periph_CLOCK         - CRM_TMR8_Periph_CLOCK        - CRM_USART1_Periph_CLOCK
  *         - CRM_USART6_Periph_CLOCK       - CRM_ADC1_Periph_CLOCK         - CRM_ADC2_Periph_CLOCK        - CRM_ADC3_Periph_CLOCK
  *         - CRM_SPI1_Periph_CLOCK         - CRM_SPI4_Periph_CLOCK         - CRM_SCFG_Periph_CLOCK        - CRM_TMR9_Periph_CLOCK
  *         - CRM_TMR10_Periph_CLOCK        - CRM_TMR11_Periph_CLOCK        - CRM_TMR20_Periph_CLOCK       - CRM_ACC_Periph_CLOCK
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Periph_Clock_Enable(CRM_Periph_Clock_Type value, confirm_state new_state) {
    /* enable periph clock */
    if(TRUE == new_state) {
        CRM_REG(value) |= CRM_REG_BIT(value);
    }
    /* disable periph clock */
    else {
        CRM_REG(value) &= ~(CRM_REG_BIT(value));
    }
}

/**
  * @brief  enable or disable the peripheral reset
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_GPIOA_Periph_Reset        - CRM_GPIOB_Periph_Reset        - CRM_GPIOC_Periph_Reset       - CRM_GPIOD_Periph_Reset
  *         - CRM_GPIOE_Periph_Reset        - CRM_GPIOF_Periph_Reset        - CRM_GPIOG_Periph_Reset       - CRM_GPIOH_Periph_Reset
  *         - CRM_CRC_Periph_Reset          - CRM_EDMA_Periph_Reset         - CRM_DMA1_Periph_Reset        - CRM_DMA2_Periph_Reset
  *         - CRM_EMAC_Periph_Reset         - CRM_OTGFS2_Periph_Reset       - CRM_DVP_Periph_Reset         - CRM_OTGFS1_Periph_Reset
  *         - CRM_SDIO1_Periph_Reset        - CRM_XMC_Periph_Reset          - CRM_QSPI1_Periph_Reset       - CRM_QSPI2_Periph_Reset
  *         - CRM_SDIO2_Periph_Reset        - CRM_TMR2_Periph_Reset         - CRM_TMR3_Periph_Reset        - CRM_TMR4_Periph_Reset
  *         - CRM_TMR5_Periph_Reset         - CRM_TMR6_Periph_Reset         - CRM_TMR7_Periph_Reset        - CRM_TMR12_Periph_Reset
  *         - CRM_TMR13_Periph_Reset        - CRM_TMR14_Periph_Reset        - CRM_WWDT_Periph_Reset        - CRM_SPI2_Periph_Reset
  *         - CRM_SPI3_Periph_Reset         - CRM_USART2_Periph_Reset       - CRM_USART3_Periph_Reset      - CRM_UART4_Periph_Reset
  *         - CRM_UART5_Periph_Reset        - CRM_I2C1_Periph_Reset         - CRM_I2C2_Periph_Reset        - CRM_I2C3_Periph_Reset
  *         - CRM_CAN1_Periph_Reset         - CRM_CAN2_Periph_Reset         - CRM_PWC_Periph_Reset         - CRM_DAC_Periph_Reset
  *         - CRM_UART7_Periph_Reset        - CRM_UART8_Periph_Reset        - CRM_TMR1_Periph_Reset        - CRM_TMR8_Periph_Reset
  *         - CRM_USART1_Periph_Reset       - CRM_USART6_Periph_Reset       - CRM_ADC_Periph_Reset         - CRM_SPI1_Periph_Reset
  *         - CRM_SPI4_Periph_Reset         - CRM_SCFG_Periph_Reset         - CRM_TMR9_Periph_Reset        - CRM_TMR10_Periph_Reset
  *         - CRM_TMR11_Periph_Reset        - CRM_TMR20_Periph_Reset        - CRM_ACC_Periph_Reset
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Periph_Reset(CRM_Periph_Reset_Type value, confirm_state new_state) {
    /* enable periph reset */
    if(new_state == TRUE) {
        CRM_REG(value) |= (CRM_REG_BIT(value));
    }
    /* disable periph reset */
    else {
        CRM_REG(value) &= ~(CRM_REG_BIT(value));
    }
}

/**
  * @brief  enable or disable the peripheral clock in lowpower mode
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_GPIOA_Periph_LOWPOWER     - CRM_GPIOB_Periph_LOWPOWER     - CRM_GPIOC_Periph_LOWPOWER    - CRM_GPIOD_Periph_LOWPOWER
  *         - CRM_GPIOE_Periph_LOWPOWER     - CRM_GPIOF_Periph_LOWPOWER     - CRM_GPIOG_Periph_LOWPOWER    - CRM_GPIOH_Periph_LOWPOWER
  *         - CRM_CRC_Periph_LOWPOWER       - CRM_EDMA_Periph_LOWPOWER      - CRM_DMA1_Periph_LOWPOWER     - CRM_DMA2_Periph_LOWPOWER
  *         - CRM_EMAC_Periph_LOWPOWER      - CRM_EMACTX_Periph_LOWPOWER    - CRM_EMACRX_Periph_LOWPOWER   - CRM_EMACPTP_Periph_LOWPOWER
  *         - CRM_OTGFS2_Periph_LOWPOWER    - CRM_DVP_Periph_LOWPOWER       - CRM_OTGFS1_Periph_LOWPOWER   - CRM_SDIO1_Periph_LOWPOWER
  *         - CRM_XMC_Periph_LOWPOWER       - CRM_QSPI1_Periph_LOWPOWER     - CRM_QSPI2_Periph_LOWPOWER    - CRM_SDIO2_Periph_LOWPOWER
  *         - CRM_TMR2_Periph_LOWPOWER      - CRM_TMR3_Periph_LOWPOWER      - CRM_TMR4_Periph_LOWPOWER     - CRM_TMR5_Periph_LOWPOWER
  *         - CRM_TMR6_Periph_LOWPOWER      - CRM_TMR7_Periph_LOWPOWER      - CRM_TMR12_Periph_LOWPOWER    - CRM_TMR13_Periph_LOWPOWER
  *         - CRM_TMR14_Periph_LOWPOWER     - CRM_WWDT_Periph_LOWPOWER      - CRM_SPI2_Periph_LOWPOWER     - CRM_SPI3_Periph_LOWPOWER
  *         - CRM_USART2_Periph_LOWPOWER    - CRM_USART3_Periph_LOWPOWER    - CRM_UART4_Periph_LOWPOWER    - CRM_UART5_Periph_LOWPOWER
  *         - CRM_I2C1_Periph_LOWPOWER      - CRM_I2C2_Periph_LOWPOWER      - CRM_I2C3_Periph_LOWPOWER     - CRM_CAN1_Periph_LOWPOWER
  *         - CRM_CAN2_Periph_LOWPOWER      - CRM_PWC_Periph_LOWPOWER       - CRM_DAC_Periph_LOWPOWER      - CRM_UART7_Periph_LOWPOWER
  *         - CRM_UART8_Periph_LOWPOWER     - CRM_TMR1_Periph_LOWPOWER      - CRM_TMR8_Periph_LOWPOWER     - CRM_USART1_Periph_LOWPOWER
  *         - CRM_USART6_Periph_LOWPOWER    - CRM_ADC1_Periph_LOWPOWER      - CRM_ADC2_Periph_LOWPOWER     - CRM_ADC3_Periph_LOWPOWER
  *         - CRM_SPI1_Periph_LOWPOWER      - CRM_SPI4_Periph_LOWPOWER      - CRM_SCFG_Periph_LOWPOWER     - CRM_TMR9_Periph_LOWPOWER
  *         - CRM_TMR10_Periph_LOWPOWER     - CRM_TMR11_Periph_LOWPOWER     - CRM_TMR20_Periph_LOWPOWER    - CRM_ACC_Periph_LOWPOWER
  *         - CRM_FLASH_Periph_LOWPOWER     - CRM_SRAM1_Periph_LOWPOWER     - CRM_SRAM2_Periph_LOWPOWER
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Periph_LowPower_Mode_Enable(CRM_Periph_Clock_LowPower_Type value, confirm_state new_state) {
    /* enable periph clock in lowpower mode */
    if(new_state == TRUE) {
        CRM_REG(value) |= (CRM_REG_BIT(value));
    }
    /* disable periph clock in lowpower mode */
    else {
        CRM_REG(value) &= ~(CRM_REG_BIT(value));
    }
}

/**
  * @brief  enable or disable the crm clock source
  * @param  source
  *         该参数可以是以下值之一:
  *         - CRM_Clock_Source_HICK
  *         - CRM_Clock_Source_HEXT
  *         - CRM_Clock_Source_PLL
  *         - CRM_Clock_Source_LEXT
  *         - CRM_Clock_Source_LICK
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Clock_Source_Enable(CRM_Clock_Source_Type source, confirm_state new_state) {
    switch(source) {
        case CRM_Clock_Source_HICK:
            CRM->ctrl_bit.hicken = new_state;
            break;

        case CRM_Clock_Source_HEXT:
            CRM->ctrl_bit.hexten = new_state;
            break;

        case CRM_Clock_Source_PLL:
            CRM->ctrl_bit.pllen = new_state;
            break;

        case CRM_Clock_Source_LEXT:
            CRM->bpdc_bit.lexten = new_state;
            break;

        case CRM_Clock_Source_LICK:
            CRM->ctrlsts_bit.licken = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  clear the crm reset flags
  * @param  flag
  *         该参数可以是以下值之一:
  *         reset flag:
  *         - CRM_Pin_Reset_FLAG
  *         - CRM_POR_Reset_FLAG
  *         - CRM_SW_Reset_FLAG
  *         - CRM_WDT_Reset_FLAG
  *         - CRM_WWDT_Reset_FLAG
  *         - CRM_LowPower_Reset_FLAG
  *         - CRM_All_Reset_FLAG
  *         interrupt flag:
  *         - CRM_LICK_ReadY_INT_FLAG
  *         - CRM_Lext_ReadY_INT_FLAG
  *         - CRM_HICK_ReadY_INT_FLAG
  *         - CRM_Hext_ReadY_INT_FLAG
  *         - CRM_PLL_ReadY_INT_FLAG
  *         - CRM_Clock_Failure_INT_FLAG
  * @retval 无
  */
void CRM_Flag_Clear(uint32_t flag) {
    switch(flag) {
        case CRM_NRST_Reset_FLAG:
        case CRM_POR_Reset_FLAG:
        case CRM_SW_Reset_FLAG:
        case CRM_WDT_Reset_FLAG:
        case CRM_WWDT_Reset_FLAG:
        case CRM_LowPower_Reset_FLAG:
        case CRM_All_Reset_FLAG:
            CRM->ctrlsts_bit.rstfc = TRUE;

            while(CRM->ctrlsts_bit.rstfc == TRUE);

            break;

        case CRM_LICK_ReadY_INT_FLAG:
            CRM->clkint_bit.lickstblfc = TRUE;
            break;

        case CRM_Lext_ReadY_INT_FLAG:
            CRM->clkint_bit.lextstblfc = TRUE;
            break;

        case CRM_HICK_ReadY_INT_FLAG:
            CRM->clkint_bit.hickstblfc = TRUE;
            break;

        case CRM_Hext_ReadY_INT_FLAG:
            CRM->clkint_bit.hextstblfc = TRUE;
            break;

        case CRM_PLL_ReadY_INT_FLAG:
            CRM->clkint_bit.pllstblfc = TRUE;
            break;

        case CRM_Clock_Failure_INT_FLAG:
            CRM->clkint_bit.cfdfc = TRUE;
            break;

        default:
            break;
    }
}

/**
  * @brief  select ertc clock
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_ERTC_Clock_NOCLK
  *         - CRM_ERTC_Clock_LEXT
  *         - CRM_ERTC_Clock_LICK
  *         - CRM_ERTC_Clock_Hext_Div_2
  *         - CRM_ERTC_Clock_Hext_Div_3
  *         - CRM_ERTC_Clock_Hext_Div_4
  *         - CRM_ERTC_Clock_Hext_Div_5
  *         - CRM_ERTC_Clock_Hext_Div_6
  *         - CRM_ERTC_Clock_Hext_Div_7
  *         - CRM_ERTC_Clock_Hext_Div_8
  *         - CRM_ERTC_Clock_Hext_Div_9
  *         - CRM_ERTC_Clock_Hext_Div_10
  *         - CRM_ERTC_Clock_Hext_Div_11
  *         - CRM_ERTC_Clock_Hext_Div_12
  *         - CRM_ERTC_Clock_Hext_Div_13
  *         - CRM_ERTC_Clock_Hext_Div_14
  *         - CRM_ERTC_Clock_Hext_Div_15
  *         - CRM_ERTC_Clock_Hext_Div_16
  *         - CRM_ERTC_Clock_Hext_Div_17
  *         - CRM_ERTC_Clock_Hext_Div_18
  *         - CRM_ERTC_Clock_Hext_Div_19
  *         - CRM_ERTC_Clock_Hext_Div_20
  *         - CRM_ERTC_Clock_Hext_Div_21
  *         - CRM_ERTC_Clock_Hext_Div_22
  *         - CRM_ERTC_Clock_Hext_Div_23
  *         - CRM_ERTC_Clock_Hext_Div_24
  *         - CRM_ERTC_Clock_Hext_Div_25
  *         - CRM_ERTC_Clock_Hext_Div_26
  *         - CRM_ERTC_Clock_Hext_Div_27
  *         - CRM_ERTC_Clock_Hext_Div_28
  *         - CRM_ERTC_Clock_Hext_Div_29
  *         - CRM_ERTC_Clock_Hext_Div_30
  *         - CRM_ERTC_Clock_Hext_Div_31
  * @retval 无
  */
void CRM_ERTC_Clock_Select(CRM_ERTC_Clock_Type value) {
    CRM->cfg_bit.ertcdiv = ((value & 0x1F0) >> 4);
    CRM->bpdc_bit.ertcsel = (value & 0xF);
}

/**
  * @brief  enable or disable ertc
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_ERTC_Clock_Enable(confirm_state new_state) {
    CRM->bpdc_bit.ertcen = new_state;
}

/**
  * @brief  set crm ahb division
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_AHB_Div_1
  *         - CRM_AHB_Div_2
  *         - CRM_AHB_Div_4
  *         - CRM_AHB_Div_8
  *         - CRM_AHB_Div_16
  *         - CRM_AHB_Div_64
  *         - CRM_AHB_Div_128
  *         - CRM_AHB_Div_256
  *         - CRM_AHB_Div_512
  * @retval 无
  */
void CRM_AHB_Div_Set(CRM_AHB_Div_Type value) {
    CRM->cfg_bit.ahbdiv = value;
}

/**
  * @brief  set crm apb1 division
  * @note   the maximum frequency of APB1/APB2 clock is 144 MHz
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_APB1_Div_1
  *         - CRM_APB1_Div_2
  *         - CRM_APB1_Div_4
  *         - CRM_APB1_Div_8
  *         - CRM_APB1_Div_16
  * @retval 无
  */
void CRM_APB1_Div_Set(CRM_APB1_Div_Type value) {
    CRM->cfg_bit.apb1div = value;
}

/**
  * @brief  set crm apb2 division
  * @note   the maximum frequency of APB1/APB2 clock is 144 MHz
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_APB2_Div_1
  *         - CRM_APB2_Div_2
  *         - CRM_APB2_Div_4
  *         - CRM_APB2_Div_8
  *         - CRM_APB2_Div_16
  * @retval 无
  */
void CRM_APB2_Div_Set(CRM_APB2_Div_Type value) {
    CRM->cfg_bit.apb2div = value;
}

/**
  * @brief  set usb division
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_USB_Div_1_5
  *         - CRM_USB_Div_1
  *         - CRM_USB_Div_2_5
  *         - CRM_USB_Div_2
  *         - CRM_USB_Div_3_5
  *         - CRM_USB_Div_3
  *         - CRM_USB_Div_4_5
  *         - CRM_USB_Div_4
  *         - CRM_USB_Div_5_5
  *         - CRM_USB_Div_5
  *         - CRM_USB_Div_6_5
  *         - CRM_USB_Div_6
  *         - CRM_USB_Div_7
  * @retval 无
  */
void CRM_USB_Clock_Div_Set(CRM_USB_Div_Type value) {
    CRM->misc2_bit.usbdiv = value;
}

/**
  * @brief  enable or disable clock failure detection
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Clock_Failure_Detection_Enable(confirm_state new_state) {
    CRM->ctrl_bit.cfden = new_state;
}

/**
  * @brief  battery powered domain software reset
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Battery_Powered_Domain_Reset(confirm_state new_state) {
    CRM->bpdc_bit.bpdrst = new_state;
}

/**
  * @brief  auto step clock switch enable
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Auto_Step_Mode_Enable(confirm_state new_state) {
    if(new_state == TRUE)
        CRM->misc2_bit.auto_Step_en = CRM_Auto_Step_Mode_ENABLE;
    else
        CRM->misc2_bit.auto_Step_en = CRM_Auto_Step_Mode_DISABLE;
}

/**
  * @brief  config hick divider select
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_HICK48_DIV6
  *         - CRM_HICK48_NODIV
  * @retval 无
  */
void CRM_HICK_Divider_Select(CRM_HICK_Div_6_Type value) {
    CRM->misc1_bit.hickdiv = value;
}

/**
  * @brief  hick as system clock frequency select
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_HICK_SCLK_8MHZ
  *         - CRM_HICK_SCLK_48MHZ
  * @retval 无
  */
void CRM_HICK_SCLK_Frequency_Select(CRM_HICK_SCLK_Frequency_Type value) {
    CRM_HICK_Divider_Select(CRM_HICK48_NODIV);
    CRM->misc1_bit.hick_To_sclk = value;
}

/**
  * @brief  usb 48 mhz clock source select
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_USB_Clock_Source_PLL
  *         - CRM_USB_Clock_Source_HICK
  * @retval 无
  */
void CRM_USB_Clock_Source_Select(CRM_USB_Clock_Source_Type value) {
    if(value == CRM_USB_Clock_Source_HICK) {
        CRM_HICK_SCLK_Frequency_Select(CRM_HICK_SCLK_48MHZ);
    }

    CRM->misc1_bit.hick_To_usb = value;
}

/**
  * @brief  enable or disable clkout direct to tmr10 channel 1
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_CLKout_To_TMR10_Enable(confirm_state new_state) {
    CRM->misc2_bit.clk_To_tmr = new_state;
}

/**
  * @brief  config crm pll
  *                        pll_rcs_freq * pll_ns
  *         pll clock = --------------------------------
  *                           pll_ms * pll_FR_n
  *         attemtion:
  *                  31 <= pll_ns <= 500
  *                  1  <= pll_ms <= 15
  *
  *                       pll_rcs_freq
  *         2mhz <=  ---------------------- <= 16mhz
  *                          pll_ms
  *
  *                       pll_rcs_freq * pll_ns
  *         500mhz <=  -------------------------------- <= 1200mhz
  *                               pll_ms
  * @param  clock_source
  *         该参数可以是以下值之一:
  *         - CRM_PLL_Source_HICK
  *         - CRM_PLL_Source_HEXT
  * @param  pll_ns (31~500)
  * @param  pll_ms (1~15)
  * @param  pll_fr
  *         该参数可以是以下值之一:
  *         - CRM_PLL_FR_1
  *         - CRM_PLL_FR_2
  *         - CRM_PLL_FR_4
  *         - CRM_PLL_FR_8
  *         - CRM_PLL_FR_16
  *         - CRM_PLL_FR_32
  * @retval 无
  */
void CRM_PLL_Config(CRM_PLL_Clock_Source_Type clock_source, uint16_t pll_ns, \
                    uint16_t pll_ms, CRM_PLL_FR_Type pll_fr) {
    /* config pll clock source */
    if(clock_source == CRM_PLL_Source_HICK) {
        CRM->misc1_bit.hickdiv = CRM_HICK48_NODIV;
    }

    CRM->pllcfg_bit.pllrcs = clock_source;

    /* config pll multiplication factor */
    CRM->pllcfg_bit.pllns = pll_ns;
    CRM->pllcfg_bit.pllms = pll_ms;
    CRM->pllcfg_bit.pllfr = pll_fr;
}

/**
  * @brief  select system clock source
  * @param  value
  *         该参数可以是以下值之一:
  *         - CRM_SCLK_HICK
  *         - CRM_SCLK_HEXT
  *         - CRM_SCLK_PLL
  * @retval 无
  */
void CRM_SysCLK_Switch(CRM_SCLK_Type value) {
    CRM->cfg_bit.sclksel = value;
}

/**
  * @brief  indicate which clock source is used as system clock
  * @param  无
  * @retval CRM_sclk
  *         this return can be one of the following values:
  *         - CRM_SCLK_HICK
  *         - CRM_SCLK_HEXT
  *         - CRM_SCLK_PLL
  */
CRM_SCLK_Type CRM_SysCLK_Switch_Status_Get(void) {
    return (CRM_SCLK_Type)CRM->cfg_bit.sclksts;
}

/**
  * @brief  get crm clocks freqency
  * @param  clocks_struct
  *         - pointer to the CRM_Clocks_Freq_Type structure
  * @retval 无
  */
void CRM_Clocks_Freq_Get(CRM_Clocks_Freq_Type *clocks_struct) {
    uint32_t pll_ns = 0, pll_ms = 0, pll_fr = 0, pll_Clock_source = 0, pllrcsfreq = 0;
    uint32_t temp = 0, div_value = 0;
    CRM_SCLK_Type sclk_source;

    static const uint8_t sclk_AHB_Div_table[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    static const uint8_t ahb_APB1_Div_table[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    static const uint8_t ahb_APB2_Div_table[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    static const uint8_t pll_FR_table[6] = {1, 2, 4, 8, 16, 32};

    /* get sclk source */
    sclk_source = CRM_SysCLK_Switch_Status_Get();

    switch(sclk_source) {
        case CRM_SCLK_HICK:
            if(((CRM->misc1_bit.hick_To_sclk) != RESET) && ((CRM->misc1_bit.hickdiv) != RESET))
                clocks_struct->sclk_freq = HICK_VALUE * 6;
            else
                clocks_struct->sclk_freq = HICK_VALUE;

            break;

        case CRM_SCLK_HEXT:
            clocks_struct->sclk_freq = HEXT_VALUE;
            break;

        case CRM_SCLK_PLL:
            /* get pll clock source */
            pll_Clock_source = CRM->pllcfg_bit.pllrcs;

            /* get multiplication factor */
            pll_ns = CRM->pllcfg_bit.pllns;
            pll_ms = CRM->pllcfg_bit.pllms;
            pll_fr = pll_FR_table[CRM->pllcfg_bit.pllfr];

            if (pll_Clock_source == CRM_PLL_Source_HICK) {
                /* hick selected as pll clock entry */
                pllrcsfreq = HICK_VALUE;
            } else {
                /* hext selected as pll clock entry */
                pllrcsfreq = HEXT_VALUE;
            }

            clocks_struct->sclk_freq = (uint32_t)(((uint64_t)pllrcsfreq * pll_ns) / (pll_ms * pll_fr));
            break;

        default:
            clocks_struct->sclk_freq = HICK_VALUE;
            break;
    }

    /* compute sclk, ahbclk, abp1clk and apb2clk frequencies */
    /* get ahb division */
    temp = CRM->cfg_bit.ahbdiv;
    div_value = sclk_AHB_Div_table[temp];
    /* ahbclk frequency */
    clocks_struct->ahb_freq = clocks_struct->sclk_freq >> div_value;

    /* get apb1 division */
    temp = CRM->cfg_bit.apb1div;
    div_value = ahb_APB1_Div_table[temp];
    /* apb1clk frequency */
    clocks_struct->apb1_freq = clocks_struct->ahb_freq >> div_value;

    /* get apb2 division */
    temp = CRM->cfg_bit.apb2div;
    div_value = ahb_APB2_Div_table[temp];
    /* apb2clk frequency */
    clocks_struct->apb2_freq = clocks_struct->ahb_freq >> div_value;
}

/**
  * @brief  set crm clkout1
  * @param  clkout
  *         该参数可以是以下值之一:
  *         - CRM_CLKOUT1_HICK
  *         - CRM_CLKOUT1_LEXT
  *         - CRM_CLKOUT1_HEXT
  *         - CRM_CLKOUT1_PLL
  * @retval 无
  */
void CRM_Clock_Out1_Set(CRM_CLKout1_Select_Type clkout) {
    CRM->cfg_bit.clkout1_sel = clkout;
}

/**
  * @brief  set crm clkout2
  * @param  clkout
  *         该参数可以是以下值之一:
  *         - CRM_CLKOUT2_SCLK
  *         - CRM_CLKOUT2_HEXT
  *         - CRM_CLKOUT2_PLL
  *         - CRM_CLKOUT2_USB
  *         - CRM_CLKOUT2_ADC
  *         - CRM_CLKOUT2_HICK
  *         - CRM_CLKOUT2_LICK
  *         - CRM_CLKOUT2_LEXT
  * @retval 无
  */
void CRM_Clock_Out2_Set(CRM_CLKout2_Select_Type clkout) {
    if(clkout < 0x10) {
        CRM->cfg_bit.clkout2_sel1 = (clkout & 0x3);
    } else {
        CRM->cfg_bit.clkout2_sel1 = 0x1;
        CRM->misc1_bit.clkout2_sel2 = (clkout & 0xF);
    }
}

/**
  * @brief  set crm clkout1 division1
  * @param  div1
  *         该参数可以是以下值之一:
  *         - CRM_CLKOUT_INDEX_1
  *         - CRM_CLKOUT_INDEX_2
  * @param  div1
  *         该参数可以是以下值之一:
  *         - CRM_CLKOUT_DIV1_1
  *         - CRM_CLKOUT_DIV1_2
  *         - CRM_CLKOUT_DIV1_3
  *         - CRM_CLKOUT_DIV1_4
  *         - CRM_CLKOUT_DIV1_5
  * @param  div2
  *         该参数可以是以下值之一:
  *         - CRM_CLKOUT_Div2_1
  *         - CRM_CLKOUT_Div2_2
  *         - CRM_CLKOUT_Div2_4
  *         - CRM_CLKOUT_Div2_8
  *         - CRM_CLKOUT_Div2_16
  *         - CRM_CLKOUT_Div2_64
  *         - CRM_CLKOUT_Div2_128
  *         - CRM_CLKOUT_Div2_256
  *         - CRM_CLKOUT_Div2_512
  * @retval 无
  */
void CRM_CLKout_Div_Set(CRM_CLKout_index_Type index, CRM_CLKout_div1_Type div1, CRM_CLKout_Div2_Type div2) {
    if(index == CRM_CLKOUT_INDEX_1) {
        CRM->cfg_bit.clkout1div1 = div1;
        CRM->misc1_bit.clkout1div2 = div2;
    } else {
        CRM->cfg_bit.clkout2div1 = div1;
        CRM->misc1_bit.clkout2div2 = div2;
    }
}

/**
  * @brief  set emac output pulse width
  * @param  width
  *         该参数可以是以下值之一:
  *         - CRM_EMAC_Pulse_125MS
  *         - CRM_EMAC_Pulse_1SCLK
  * @retval 无
  */
void CRM_EMAC_OutPut_Pulse_Set(CRM_EMAC_OutPut_Pulse_Type width) {
    CRM->misc2_bit.EMAC_PPS_sel = width;
}

/**
  * @brief  config crm interrupt
  * @param  int
  *         该参数可以是以下值的任意组合:
  *         - CRM_LICK_Stable_INT
  *         - CRM_Lext_Stable_INT
  *         - CRM_HICK_Stable_INT
  *         - CRM_Hext_Stable_INT
  *         - CRM_PLL_Stable_INT
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void CRM_Interrupt_Enable(uint32_t CRM_int, confirm_state new_state) {
    if(TRUE == new_state)
        CRM->clkint |= CRM_int;
    else
        CRM->clkint &= ~CRM_int;
}

/**
  * @brief  calculate the pll parameters with pll reference clock and target pll output frequency.
  *                        pll_rcs_freq * pll_ns
  *         pll clock = --------------------------------
  *                           pll_ms * pll_FR_n
  *         attemtion:
  *                  31 <= pll_ns <= 500
  *                  1  <= pll_ms <= 15
  *
  *                       pll_rcs_freq
  *         2mhz <=  ---------------------- <= 16mhz
  *                          pll_ms
  *
  *                       pll_rcs_freq * pll_ns
  *         500mhz <=  -------------------------------- <= 1200mhz
  *                               pll_ms
  * @param  pll_rcs
  *         该参数可以是以下值之一:
  *         - CRM_PLL_Source_HICK
  *         - CRM_PLL_Source_HEXT
  * @param  target_SCLK_freq: target pll output frequency, such as 200 mhz (target_SCLK_freq: 200000000)
  * @param  ret_ms: pointer to ms value, return the pll_ms of pll parameters
  * @param  ret_ns: pointer to ns value, return the pll_ns of pll parameters
  * @param  ret_fr: pointer to fr value, return the pll_fr of pll parameters
  * @retval error_status (SUCCESS or ERROR)
  */
error_status CRM_PLL_Parameter_Calculate(CRM_PLL_Clock_Source_Type pll_rcs, uint32_t target_SCLK_freq, \
        uint16_t *ret_ms, uint16_t *ret_ns, uint16_t *ret_fr) {
    int32_t pll_rcs_freq = 0, ns = 0, ms = 0, fr = 0;
    uint32_t ms_min = 0, ms_max = 0, error_min = 0xFFFFFFFF;
    uint32_t result = 0, absolute_value = 0;

    /* reduce calculate accuracy, target_SCLK_freq accuracy with khz */
    target_SCLK_freq = target_SCLK_freq / 1000;

    /* get pll reference clock frequency, accuracy with khz */
    if(pll_rcs == CRM_PLL_Source_HICK)
        pll_rcs_freq = HICK_VALUE / 1000;
    else
        pll_rcs_freq = HEXT_VALUE / 1000;

    /* polling ms range, accuracy with khz */
    for(ms = 1; ms <= 15; ms ++) {
        result = pll_rcs_freq / ms;

        if((result >= 2000U) && (result <= 16000U)) {
            if(ms_min == 0)
                ms_min = ms;

            ms_max = ms;
        }
    }

    /* polling pll parameters */
    for(ms = ms_min; ms <= ms_max; ms ++) {
        for(fr = 5; fr >= 0; fr --) {
            for(ns = 31; ns <= 500; ns ++) {
                result = (pll_rcs_freq * ns) / (ms);

                /* check vco frequency range, accuracy with khz */
                if((result < 500000U) || (result > 1200000U)) {
                    continue;
                }

                /* calculate pll output frequency */
                result = result / (0x1 << fr);

                /* check frequency */
                if(target_SCLK_freq == result) {
                    *ret_ms = ms;
                    *ret_ns = ns;
                    *ret_fr = fr;
                    /* the pll parameters that is equal to target_SCLK_freq */
                    return SUCCESS;
                }

                /* calculate error range, accuracy with khz */
                absolute_value = (result > target_SCLK_freq) ? (result - target_SCLK_freq) : (target_SCLK_freq - result);

                if(absolute_value < error_min) {
                    error_min = absolute_value;
                    *ret_ms = ms;
                    *ret_ns = ns;
                    *ret_fr = fr;
                }
            }
        }
    }

    /* the pll parameters that is the closest approach to target_SCLK_freq */
    return ERROR;
}

#endif
