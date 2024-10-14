/**
  **************************************************************************
  * @file     system_at32f435_437.c
  * @brief    contains all the functions for cmsis cortex-m4 system source file
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

/** @addtogroup CMSIS
  */

/** @addtogroup AT32F435_437_system
  */

#include "at32f435_437.h"

/** @addtogroup AT32F435_437_System_private_defines
  */
#define VECT_TAB_OFFSET                  0x0 /*!< 矢量表基偏移字段。 该值必须是0x400的倍数。 */
/** @addtogroup AT32F435_437_System_private_variables
  */
unsigned int system_Core_clock           = HICK_VALUE; /*!< 系统时钟频率(核心时钟) */
/** @addtogroup AT32F435_437_System_private_functions
  */

/**
  * @brief  设置微控制器系统
  *         初始化flash接口。
  * @note   此功能只能在复位后使用。
  * @param  无
  * @retval 无
  */
void SystemInit (void) {
    #if defined (__FPU_USED) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3U << 10U * 2U) |         /* set cp10 full access */
                   (3U << 11U * 2U)  );       /* set cp11 full access */
    #endif

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

    #ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE  | VECT_TAB_OFFSET;  /* 内部 SRAM 中的矢量表重定位. */
    #else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;  /* 内部FLASH中的矢量表重定位. */
    #endif
}

/**
  * @brief  update system_Core_clock variable 根据 clock register values.
  *         the system_Core_clock variable contains the core clock (hclk), it can
  *         be used by the user application to setup the systick timer or configure
  *         other parameters.
  * @param  无
  * @retval 无
  */
void system_Core_Clock_Update(void) {
    uint32_t pll_ns = 0, pll_ms = 0, pll_fr = 0, pll_Clock_source = 0, pllrcsfreq = 0;
    uint32_t temp = 0, div_value = 0;
    CRM_SCLK_Type sclk_source;

    static const uint8_t sys_AHB_Div_table[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    static const uint8_t pll_FR_table[6] = {1, 2, 4, 8, 16, 32};

    /* get sclk source */
    sclk_source = CRM_SysCLK_Switch_Status_Get();

    switch(sclk_source) {
        case CRM_SCLK_HICK:
            if(((CRM->misc1_bit.hick_To_sclk) != RESET) && ((CRM->misc1_bit.hickdiv) != RESET))
                system_Core_clock = HICK_VALUE * 6;
            else
                system_Core_clock = HICK_VALUE;

            break;

        case CRM_SCLK_HEXT:
            system_Core_clock = HEXT_VALUE;
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

            system_Core_clock = (uint32_t)(((uint64_t)pllrcsfreq * pll_ns) / (pll_ms * pll_fr));
            break;

        default:
            system_Core_clock = HICK_VALUE;
            break;
    }

    /* compute sclk, ahbclk frequency */
    /* get ahb division */
    temp = CRM->cfg_bit.ahbdiv;
    div_value = sys_AHB_Div_table[temp];
    /* ahbclk frequency */
    system_Core_clock = system_Core_clock >> div_value;
}
