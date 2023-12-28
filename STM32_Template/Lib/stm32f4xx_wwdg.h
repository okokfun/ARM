/**
  ******************************************************************************
  * 文件:    stm32f4xx_wwdg.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 WWDG 固件库的所有功能原型.
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
#ifndef __STM32F4xx_WWDG_H
#define __STM32F4xx_WWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup WWDG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup WWDG_Exported_Constants
  * @{
  */

/** @defgroup WWDG_Prescaler
  * @{
  */
#define WWDG_Prescaler_1    ((uint32_t)0x00000000)
#define WWDG_Prescaler_2    ((uint32_t)0x00000080)
#define WWDG_Prescaler_4    ((uint32_t)0x00000100)
#define WWDG_Prescaler_8    ((uint32_t)0x00000180)
#define IS_WWDG_PRESCALER(PRESCALER) (((PRESCALER) == WWDG_Prescaler_1) || \
                                      ((PRESCALER) == WWDG_Prescaler_2) || \
                                      ((PRESCALER) == WWDG_Prescaler_4) || \
                                      ((PRESCALER) == WWDG_Prescaler_8))
#define IS_WWDG_WINDOW_VALUE(VALUE) ((VALUE) <= 0x7F)
#define IS_WWDG_COUNTER(COUNTER) (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 WWDG 配置设置为默认复位状态的函数 ****/
void WWDG_DeInit(void); // 将 WWDG 外设寄存器去初始化为其默认复位值。

/* 预分频器、刷新窗口和计数器配置功能 **************/
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler); 	// 设置 WWDG 预缩放程序。
void WWDG_SetWindowValue(uint8_t WindowValue); 		// 设置 WWDG 窗口值。
void WWDG_EnableIT(void); 							      // 启用 WWDG 早期唤醒中断 (EWI)。
void WWDG_SetCounter(uint8_t Counter); 				// 设置 WWDG 计数器值。

/* WWDG 激活功能 ***************************************************/
void WWDG_Enable(uint8_t Counter); // 启用 WWDG 并加载计数器值。

/* 中断和标志管理功能 **********************************/
FlagStatus WWDG_GetFlagStatus(void); 	// 检查是否设置了"早期唤醒中断"标志。
void WWDG_ClearFlag(void); 				    // 清除早期唤醒中断标志。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_WWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
