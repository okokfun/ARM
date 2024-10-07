/**
  ******************************************************************************
  * 文件:    stm32f4xx_rng.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含随机数生成器 (RNG) 固件库的所有函数原型.
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

/* 定义以防止递归包含 -------------------------------------*/
#ifndef __STM32F4xx_RNG_H
#define __STM32F4xx_RNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup RNG
  */
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx)
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup RNG_Exported_Constants
  */

/** @defgroup RNG_flags_definition
  */
#define RNG_FLAG_DRDY               ((uint8_t)0x0001) /*!< 数据准备就绪 */
#define RNG_FLAG_CECS               ((uint8_t)0x0002) /*!< 时钟错误当前状态 */
#define RNG_FLAG_SECS               ((uint8_t)0x0004) /*!< 种子错误当前状态 */

#define IS_RNG_GET_FLAG(RNG_FLAG) (((RNG_FLAG) == RNG_FLAG_DRDY) || \
                                   ((RNG_FLAG) == RNG_FLAG_CECS) || \
                                   ((RNG_FLAG) == RNG_FLAG_SECS))
#define IS_RNG_CLEAR_FLAG(RNG_FLAG) (((RNG_FLAG) == RNG_FLAG_CECS) || \
                                     ((RNG_FLAG) == RNG_FLAG_SECS))

/** @defgroup RNG_interrupts_definition
  */
#define RNG_IT_CEI                  ((uint8_t)0x20) /*!< 时钟错误中断 */
#define RNG_IT_SEI                  ((uint8_t)0x40) /*!< 种子错误中断 */

#define IS_RNG_IT(IT) ((((IT) & (uint8_t)0x9F) == 0x00) && ((IT) != 0x00))
#define IS_RNG_GET_IT(RNG_IT) (((RNG_IT) == RNG_IT_CEI) || ((RNG_IT) == RNG_IT_SEI))


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 RNG 配置设置为默认重置状态的函数 *****/
void RNG_DeInit(void); // 将 RNG 外设寄存器取消初始化为其默认复位值。

/* 配置功能 *****************************************************/
void RNG_Cmd(FunctionalState NewState); // 启用或禁用 RNG 外设设备。

/* 获取 32 位随机数功能 ******************************************/
uint32_t RNG_GetRandomNumber(void); // 返回一个 32 位随机数。

/* 中断和标志管理功能 **********************************/
void RNG_ITConfig(FunctionalState NewState); // 启用或禁用 RNG 中断。
FlagStatus RNG_GetFlagStatus(uint8_t RNG_FLAG); // 检查是否设置了指定的 RNG 标志。
void RNG_ClearFlag(uint8_t RNG_FLAG); // 清除 RNG 标志。
ITStatus RNG_GetITStatus(uint8_t RNG_IT); // 检查指定的 RNG 中断是否发生。
void RNG_ClearITPendingBit(uint8_t RNG_IT); // 清除 RNG 中断挂起位。
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F429_439xx || STM32F469_479xx */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_RNG_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
