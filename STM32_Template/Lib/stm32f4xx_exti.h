/**
  ******************************************************************************
  * 文件:    stm32f4xx_exti.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 EXTI 固件库的所有功能原型.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_EXTI_H
#define __STM32F4xx_EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup EXTI
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  EXTI 模式枚举
  */

typedef enum {
    EXTI_Mode_Interrupt = 0x00,
    EXTI_Mode_Event = 0x04
} EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))

/**
  * 简介:  EXTI 触发器枚举
  */

typedef enum {
    EXTI_Trigger_Rising = 0x08,
    EXTI_Trigger_Falling = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
} EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))
/**
  * 简介:  EXTI 初始化结构定义
  */
typedef struct {
    uint32_t EXTI_Line;               /*!< 指定要启用或禁用的 EXTI 行。
                                      该参数可以是 @ref EXTI_Lines 的任意组合值 */

    EXTIMode_TypeDef EXTI_Mode;       /*!< 指定 EXTI 行的模式。
                                      该参数可以是 @ref EXTIMode_TypeDef 的值 */

    EXTITrigger_TypeDef EXTI_Trigger; /*!< 指定 EXTI 线的触发信号有效边沿。
                                      该参数可以是 @ref EXTITrigger_TypeDef 的值 */

    FunctionalState EXTI_LineCmd;     /*!< 指定选定 EXTI 行的新状态。
									                    此参数可以设置为 ENABLE 或 DISABLE */
} EXTI_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup EXTI_Exported_Constants
  */

/** @defgroup EXTI_Lines
  */
#define EXTI_Line0       ((uint32_t)0x00001)     /*!< 外部中断线 0 */
#define EXTI_Line1       ((uint32_t)0x00002)     /*!< 外部中断线 1 */
#define EXTI_Line2       ((uint32_t)0x00004)     /*!< 外部中断线 2 */
#define EXTI_Line3       ((uint32_t)0x00008)     /*!< 外部中断线 3 */
#define EXTI_Line4       ((uint32_t)0x00010)     /*!< 外部中断线 4 */
#define EXTI_Line5       ((uint32_t)0x00020)     /*!< 外部中断线 5 */
#define EXTI_Line6       ((uint32_t)0x00040)     /*!< 外部中断线 6 */
#define EXTI_Line7       ((uint32_t)0x00080)     /*!< 外部中断线 7 */
#define EXTI_Line8       ((uint32_t)0x00100)     /*!< 外部中断线 8 */
#define EXTI_Line9       ((uint32_t)0x00200)     /*!< 外部中断线 9 */
#define EXTI_Line10      ((uint32_t)0x00400)     /*!< 外部中断线 10 */
#define EXTI_Line11      ((uint32_t)0x00800)     /*!< 外部中断线 11 */
#define EXTI_Line12      ((uint32_t)0x01000)     /*!< 外部中断线 12 */
#define EXTI_Line13      ((uint32_t)0x02000)     /*!< 外部中断线 13 */
#define EXTI_Line14      ((uint32_t)0x04000)     /*!< 外部中断线 14 */
#define EXTI_Line15      ((uint32_t)0x08000)     /*!< 外部中断线 15 */
#define EXTI_Line16      ((uint32_t)0x10000)     /*!< 外部中断线 16 连接到 PVD 输出 */
#define EXTI_Line17      ((uint32_t)0x20000)     /*!< 外部中断线 17 连接到 RTC 警报事件 */
#define EXTI_Line18      ((uint32_t)0x40000)     /*!< 外部中断线 18 连接到 USB OTG FS 从挂起事件唤醒 */
#define EXTI_Line19      ((uint32_t)0x80000)     /*!< 外部中断线 19 连接到以太网唤醒事件 */
#define EXTI_Line20      ((uint32_t)0x00100000)  /*!< 外部中断线 20 连接到 USB OTG HS(在 FS 中配置)唤醒事件  */
#define EXTI_Line21      ((uint32_t)0x00200000)  /*!< 外部中断线 21 连接到 RTC 篡改和时间戳事件 */
#define EXTI_Line22      ((uint32_t)0x00400000)  /*!< 外部中断线 22 连接到 RTC 唤醒事件 */
#define EXTI_Line23      ((uint32_t)0x00800000)  /*!< 外部中断线 23 连接到 LPTIM 唤醒事件 */


#define IS_EXTI_LINE(LINE) ((((LINE) & (uint32_t)0xFF800000) == 0x00) && ((LINE) != (uint16_t)0x00))

#define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) || \
                                ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) || \
                                ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) || \
                                ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) || \
                                ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) || \
                                ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                                ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                                ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                                ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                                ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19) || \
                                ((LINE) == EXTI_Line20) || ((LINE) == EXTI_Line21) ||\
                                ((LINE) == EXTI_Line22) || ((LINE) == EXTI_Line23))



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 EXTI 配置设置为默认复位状态的函数 *****/
void EXTI_DeInit(void); // 将 EXTI 外设寄存器取消初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct); // 根据 EXTI_InitStruct 中指定的参数初始化 EXTI 外设。
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct); // 用其重置值填充每个 EXTI_InitStruct 成员。
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line); // 在选定的 EXTI 线上产生一个软件中断。

/* 中断和标志管理功能 **********************************/
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line); // 检查是否设置了指定的 EXTI 行标志。
void EXTI_ClearFlag(uint32_t EXTI_Line); // 清除 EXTI 的行挂起标志。
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line); // 检查指定的 EXTI 行是否被断言。
void EXTI_ClearITPendingBit(uint32_t EXTI_Line); // 清除 EXTI 的行挂起位。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_EXTI_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
