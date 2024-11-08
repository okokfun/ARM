/**
  ******************************************************************************
  * 文件:    stm32f4xx_wwdg.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，用于管理Window watchdog(WWDG)外设设备的以下函数:
  *           + 预分频器、刷新窗口和计数器配置
  *           + WWDG激活
  *           + 中断和标志管理
  *
 @verbatim
 ===============================================================================
                           ##### WWDG功能 #####
 ===============================================================================
    [..]
        启用后，WWDG 在编程时间段到期时生成系统重置，
          除非程序在达到 0x3F 值之前刷新计数器(下行计数器)(即当计数器值从 0x40 滚动到 0x3F 时生成重置)。
        如果在计数器达到刷新窗口值之前刷新计数器值，
          也会生成 MCU 重置。这意味着必须在有限的窗口中刷新计数器。

        启用后，除通过系统重置外，无法禁用 WWDG。

        RCC_CSR 寄存器中的 WWDGRST 标志可用于通知何时发生 WWDG 重置。

        WWDG 计数器输入时钟由 APB 时钟除以可编程预分频器得到。

        WWDG 计数器时钟 = PCLK1 / Prescaler
        WWDG 超时 = (WWDG counter clock) * (counter value)

        Min-max timeout value @42 MHz(PCLK1): ~97.5 us / ~49.9 ms

                      ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..]
      (#) 使用 RCC_APB1PeriphClockCmd(RCC_APP1Periph-WWDG，Enable) 函数启用 WWDG 时钟

      (#) 使用 WWDG_SetPrescaler() 函数配置 WWDG 预分频器

      (#) 使用 WWDG_SetWindowValue() 函数配置 WWDG 刷新窗口

      (#) 设置 WWDG 计数器值，并使用 WWDG_Enable() 函数启动它。
          启用 WWDG 时，计数器值应配置为大于 0x40 的值，以防止生成立即重置。

      (#) 您可以选择启用计数器达到 0x40 时生成的早期唤醒中断。
          一旦启用，除非系统复位，否则不能禁用此中断。

      (#) 然后，应用程序必须在正常操作期间定期刷新 WWDG 计数器，以防止 MCU 重置，
          方法是使用 WWDG_SetCounter() 函数。仅当计数器值低于使用 WWDG_SetWindowValue()
          编程的刷新窗口值时，才能执行此操作。

    @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_wwdg.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup WWDG
  * 简介: WWDG 驱动程序模块
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* ----------- WWDG 在别名区域中注册位地址 ----------- */
#define WWDG_OFFSET       (WWDG_BASE - PERIPH_BASE)
/* EWI位的别名字地址 */
#define CFR_OFFSET        (WWDG_OFFSET + 0x04)
#define EWI_BitNumber     0x09
#define CFR_EWI_BB        (PERIPH_BB_BASE + (CFR_OFFSET * 32) + (EWI_BitNumber * 4))

/* --------------------- WWDG 寄存器位掩码 ------------------------ */
/* CFR 寄存器位掩码 */
#define CFR_WDGTB_MASK    ((uint32_t)0xFFFFFE7F)
#define CFR_W_MASK        ((uint32_t)0xFFFFFF80)
#define BIT_MASK          ((uint8_t)0x7F)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup WWDG_Private_Functions
  */

/** @defgroup WWDG_Group1 预分频器、刷新窗口和计数器配置功能
 *  简介   预分频器、刷新窗口和计数器配置功能
 *
@verbatim
 ===============================================================================
    ##### 预分频器、刷新窗口和计数器配置功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  将WWDG 外围寄存器取消初始化为其默认重置值。
  * 参数:  无
  * 返回值: 无
  */
void WWDG_DeInit(void) {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/**
  * 简介:  设置 WWDG 预分频器。
  * 参数:  WWDG_Prescaler: 指定 WWDG 预分频器。
  *   此参数可以是以下值之一:
  *     @arg WWDG_Prescaler_1: WWDG 计数器时钟 = (PCLK1/4096)/1
  *     @arg WWDG_Prescaler_2: WWDG 计数器时钟 = (PCLK1/4096)/2
  *     @arg WWDG_Prescaler_4: WWDG 计数器时钟 = (PCLK1/4096)/4
  *     @arg WWDG_Prescaler_8: WWDG 计数器时钟 = (PCLK1/4096)/8
  * 返回值: 无
  */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler) {
    uint32_t tmpreg = 0;
    /* 检查参数 */
    assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
    /* 清除 WDGTB[1:0]位 */
    tmpreg = WWDG->CFR & CFR_WDGTB_MASK;
    /* 根据 WWDG_Prescaller值设置 WDGTB[1:0]位 */
    tmpreg |= WWDG_Prescaler;
    /* 存储新值 */
    WWDG->CFR = tmpreg;
}

/**
  * 简介:  设置 WWDG 窗口值。
  * 参数:  WindowValue: 指定要与递减计数器进行比较的窗口值。
  *       此参数值必须低于 0x80。
  * 返回值: 无
  */
void WWDG_SetWindowValue(uint8_t WindowValue) {
    __IO uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
    /* 清除 W[6:0] 位 */

    tmpreg = WWDG->CFR & CFR_W_MASK;

    /* 根据WindowValue值设置 W[6:0]位 */
    tmpreg |= WindowValue & (uint32_t) BIT_MASK;

    /* 存储新值 */
    WWDG->CFR = tmpreg;
}

/**
  * 简介:  启用 WWDG 早期唤醒中断(EWI)。
  * 注意:   一旦启用，除非系统复位，否则不能禁用此中断。
  * 参数:  无
  * 返回值: 无
  */
void WWDG_EnableIT(void) {
    *(__IO uint32_t *) CFR_EWI_BB = (uint32_t)ENABLE;
}

/**
  * 简介:  设置 WWDG 计数器值。
  * 参数:  Counter: 指定看门狗计数器值。
  *        此参数必须是 0x40 和 0x7F 之间的数字(以防止生成立即重置)
  * 返回值: 无
  */
void WWDG_SetCounter(uint8_t Counter) {
    /* 检查参数 */
    assert_param(IS_WWDG_COUNTER(Counter));
    /* 写入 T[6:0]位以配置计数器值，无需进行读修改写入;将0写入WDGA位不起任何作用 */
    WWDG->CR = Counter & BIT_MASK;
}

/** @defgroup WWDG_Group2 WWDG激活函数s
 *  简介   WWDG激活函数s
 *
@verbatim
 ===============================================================================
                    ##### WWDG激活函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用 WWDG并加载计数器值。
  * 参数:  Counter: 指定看门狗计数器值。
  *        此参数必须是 0x40 和 0x7F 之间的数字(以防止生成立即重置)
  * 返回值: 无
  */
void WWDG_Enable(uint8_t Counter) {
    /* 检查参数 */
    assert_param(IS_WWDG_COUNTER(Counter));
    WWDG->CR = WWDG_CR_WDGA | Counter;
}

/** @defgroup WWDG_Group3 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
            ##### 中断和标记管理函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  检查是否设置了早期唤醒中断标志。
  * 参数:  无
  * 返回值: 早期唤醒中断标志(SET 或 RESET)的新状态
  */
FlagStatus WWDG_GetFlagStatus(void) {
    FlagStatus bitstatus = RESET;

    if ((WWDG->SR) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除早期唤醒中断标志。
  * 参数:  无
  * 返回值: 无
  */
void WWDG_ClearFlag(void) {
    WWDG->SR = (uint32_t)RESET;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
