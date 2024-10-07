/**
  **************************************************************************
  * @file     at32f435_437_clock.c
  * @brief    system clock config program
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
#include "at32f435_437_clock.h"

/** @addtogroup AT32F437_Periph_template
  */

/** @addtogroup 437_System_Clock_Configuration System_Clock_Configuration
  */

/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         - system clock        = (hext * pll_ns)/(pll_ms * pll_fr)
  *         - system clock source = pll (hext)
  *         - hext                = 8000000
  *         - sclk                = 288000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 288000000
  *         - apb2div             = 2
  *         - apb2clk             = 144000000
  *         - apb1div             = 2
  *         - apb1clk             = 144000000
  *         - pll_ns              = 144
  *         - pll_ms              = 1
  *         - pll_fr              = 4
  * @param  无
  * @retval 无
  */
void system_Clock_Config(void) {
    /* reset crm */
    CRM_Reset();

    /* enable pwc periph clock */
    CRM_Periph_Clock_Enable(CRM_PWC_Periph_CLOCK, TRUE);

    /* config ldo voltage */
    PWC_Ldo_OutPut_Voltage_Set(PWC_LDO_OutPut_1V3);

    /* set the flash clock divider */
    FLASH_Clock_Divider_Set(FLASH_Clock_Div_3);

    CRM_Clock_Source_Enable(CRM_Clock_Source_HEXT, TRUE);

    /* wait till hext is ready */
    while(CRM_Hext_Stable_Wait() == ERROR) {
    }

    /* config pll clock resource
    common frequency config list: pll source selected  hick or hext(8mhz)
    _________________________________________________________________________________________________
    |        |         |         |         |         |         |         |         |        |        |
    |pll(mhz)|   288   |   252   |   216   |   192   |   180   |   144   |   108   |   72   |   36   |
    |________|_________|_________|_________|_________|_________|_________|_________|_________________|
    |        |         |         |         |         |         |         |         |        |        |
    |pll_ns  |   144   |   126   |   108   |   96    |   90    |   72    |   108   |   72   |   72   |
    |        |         |         |         |         |         |         |         |        |        |
    |pll_ms  |   1     |   1     |   1     |   1     |   1     |   1     |   1     |   1    |   1    |
    |        |         |         |         |         |         |         |         |        |        |
    |pll_fr  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_8  |   FR_8 |   FR_16|
    |________|_________|_________|_________|_________|_________|_________|_________|________|________|

    if pll clock source selects hext with other frequency values, or configure pll to other
    frequency values, please use the at32 new clock  configuration tool for configuration.  */
    CRM_PLL_Config(CRM_PLL_Source_HEXT, 144, 1, CRM_PLL_FR_4);

    /* enable pll */
    CRM_Clock_Source_Enable(CRM_Clock_Source_PLL, TRUE);

    /* wait till pll is ready */
    while(CRM_Flag_Get(CRM_PLL_Stable_FLAG) != SET) {
    }

    /* config ahbclk */
    CRM_AHB_Div_Set(CRM_AHB_Div_1);

    /* config apb2clk, the maximum frequency of APB1/APB2 clock is 144 MHz  */
    CRM_APB2_Div_Set(CRM_APB2_Div_2);

    /* config apb1clk, the maximum frequency of APB1/APB2 clock is 144 MHz  */
    CRM_APB1_Div_Set(CRM_APB1_Div_2);

    /* enable auto step mode */
    CRM_Auto_Step_Mode_Enable(TRUE);

    /* select pll as system clock source */
    CRM_SysCLK_Switch(CRM_SCLK_PLL);

    /* wait till pll is used as system clock source */
    while(CRM_SysCLK_Switch_Status_Get() != CRM_SCLK_PLL) {
    }

    /* disable auto step mode */
    CRM_Auto_Step_Mode_Enable(FALSE);

    /* update system_Core_clock global variable */
    system_Core_Clock_Update();
}

