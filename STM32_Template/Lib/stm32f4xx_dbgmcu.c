/**
  ******************************************************************************
  * 文件:    stm32f4xx_dbgmcu.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供所有 DBGMCU 固件功能。
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
#include "stm32f4xx_dbgmcu.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DBGMCU
  * 简介: DBGMCU 驱动模块
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup DBGMCU_Private_Functions
  * @{
  */

/**
  * 简介:  返回设备修订标识符。
  * 
  * 参数:  无
  * 
  * 返回值: 设备修订标识符
  */
uint32_t DBGMCU_GetREVID(void) {
    return(DBGMCU->IDCODE >> 16);
}

/**
  * 简介:  返回设备标识符。
  * 
  * 参数:  无
  * 
  * 返回值: 设备标识符
  */
uint32_t DBGMCU_GetDEVID(void) {
    return(DBGMCU->IDCODE & IDCODE_DEVID_MASK);
}

/**
  * 简介:  配置 MCU 处于调试模式时的低功耗模式行为。
  * 
  * 参数:  DBGMCU_Periph: 指定低功率模式。
  *   此参数可以是以下值的任意组合:
  *     @arg DBGMCU_SLEEP: 在SLEEP模式下保持调试器连接。
  *     @arg DBGMCU_STOP: 在STOP模式下保持调试器的连接
  *     @arg DBGMCU_STANDBY: 在STANDBY模式下保持调试器的连接。
  * 
  * 参数:  NewState: 在调试模式下指定的低功耗模式的新状态。
  *   此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        DBGMCU->CR |= DBGMCU_Periph;
    } else {
        DBGMCU->CR &= ~DBGMCU_Periph;
    }
}

/**
  * 简介:  当 MCU 处于调试模式时配置 APB1 外设行为。
  * 
  * 参数:  DBGMCU_Periph: 指定APB1外设。
  *   此参数可以是以下值的任意组合:
  *         @arg DBGMCU_TIM2_STOP。当 Core 停止时，TIM2 计数器停止
  *         @arg DBGMCU_TIM3_STOP: 当 Core 停止时，TIM3 计数器停止
  *         @arg DBGMCU_TIM4_STOP: 当 Core 停止时，TIM4 计数器停止
  *         @arg DBGMCU_TIM5_STOP: 当 Core 停止时，TIM5 计数器停止
  *         @arg DBGMCU_TIM6_STOP: 当 Core 停止时，TIM6 计数器停止
  *         @arg DBGMCU_TIM7_STOP: 当 Core 停止时，TIM7 计数器停止
  *         @arg DBGMCU_TIM12_STOP: 当 Core 停止时，TIM12 计数器停止
  *         @arg DBGMCU_TIM13_STOP: 当 Core 停止时，TIM13 计数器停止
  *         @arg DBGMCU_TIM14_STOP: 当 Core 停止时，TIM14 计数器停止
  *         @arg DBGMCU_RTC_STOP: 当 Core 停止时，RTC 日历和唤醒计数器停止。
  *         @arg DBGMCU_WWDG_STOP: 当 Core 停止时，Debug WWDG 被停止。
  *         @arg DBGMCU_IWDG_STOP: 当 Core 停止时，停止调试 IWDG。
  *         @arg DBGMCU_I2C1_SMBUS_TIMEOUT: 当 Core 停止时，I2C1 SMBUS 超时模式停止。
  *         @arg DBGMCU_I2C2_SMBUS_TIMEOUT: I2C2 SMBUS 超时模式在 Core 停止时停止。
  *         @arg DBGMCU_I2C3_SMBUS_TIMEOUT: I2C3 SMBUS 超时模式在Core 停止时停止。
  *         @arg DBGMCU_CAN2_STOP: 当 Core 停止时，停止调试CAN1。
  *         @arg DBGMCU_CAN1_STOP: 当 Core 停止时，停止调试CAN2。
  * 
  * 参数:  NewState: 此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DBGMCU_APB1PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DBGMCU_APB1PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        DBGMCU->APB1FZ |= DBGMCU_Periph;
    } else {
        DBGMCU->APB1FZ &= ~DBGMCU_Periph;
    }
}

/**
  * 简介:  当 MCU 处于调试模式时配置 APB2 外设行为。
  * 
  * 参数:  DBGMCU_Periph: 指定APB2外设。
  *   此参数可以是以下值的任意组合:
  *     @arg DBGMCU_TIM1_STOP。当 Core 停止时，TIM1 计数器停止
  *     @arg DBGMCU_TIM8_STOP: 当 Core 停止时，TIM8 计数器停止
  *     @arg DBGMCU_TIM9_STOP: 当 Core 停止时，TIM9 计数器停止
  *     @arg DBGMCU_TIM10_STOP: 当 Core 停止时，TIM10 计数器停止
  *     @arg DBGMCU_TIM11_STOP: 当 Core 停止工作时，TIM11 计数器停止工作
  * 
  * 参数:  NewState:在Debug模式下指定外设的新状态。
  *   此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void DBGMCU_APB2PeriphConfig(uint32_t DBGMCU_Periph, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DBGMCU_APB2PERIPH(DBGMCU_Periph));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        DBGMCU->APB2FZ |= DBGMCU_Periph;
    } else {
        DBGMCU->APB2FZ &= ~DBGMCU_Periph;
    }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
