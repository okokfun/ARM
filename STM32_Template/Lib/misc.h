/**
  ******************************************************************************
  * 文件:    misc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含各种固件库函数(CMSIS 函数的附加组件)的所有函数原型。
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
#ifndef __MISC_H
#define __MISC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup MISC
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  NVIC 初始化结构定义
  */
typedef struct {
    uint8_t NVIC_IRQChannel;                    /*!< 指定要启用或禁用的 IRQ 通道。
                                                该参数可以是 @ref IRQn_Type枚举的枚举器(完整的
                                                STM32 Devices IRQ Channels列表请参考stm32f4xx.h 文件) */

    uint8_t NVIC_IRQChannelPreemptionPriority;  /*!< 指定 NVIC_IRQChannel 中指定的 IRQ 通道的抢占优先级。
                                                此参数可以是 0 到 15 之间的值，
                                                如表中所述 @ref MISC_NVIC_Priority_Table
                                                较低的优先级值表示较高的优先级 */

    uint8_t NVIC_IRQChannelSubPriority;         /*!< 指定 NVIC_IRQChannel 中指定的 IRQ 通道的子优先级。
                                                此参数可以是 0 到 15 之间的值，
                                                如表中所述 @ref MISC_NVIC_Priority_Table
                                                较低的优先级值表示较高的优先级 */

    FunctionalState NVIC_IRQChannelCmd;         /*!< 指定是启用还是禁用 NVIC_IRQChannel 中定义的 IRQ 通道。
                                                此参数可以设置为 ENABLE 或 DISABLE */
} NVIC_InitTypeDef;

/* 导出的常量 --------------------------------------------------------*/

/** @defgroup MISC_Exported_Constants
  */

/** @defgroup MISC_Vector_Table_Base
  */
#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
#define IS_NVIC_VECTTAB(VECTTAB) (((VECTTAB) == NVIC_VectTab_RAM) || \
                                  ((VECTTAB) == NVIC_VectTab_FLASH))

/** @defgroup MISC_System_Low_Power
  */
#define NVIC_LP_SEVONPEND            ((uint8_t)0x10)
#define NVIC_LP_SLEEPDEEP            ((uint8_t)0x04)
#define NVIC_LP_SLEEPONEXIT          ((uint8_t)0x02)
#define IS_NVIC_LP(LP) (((LP) == NVIC_LP_SEVONPEND) || \
                        ((LP) == NVIC_LP_SLEEPDEEP) || \
                        ((LP) == NVIC_LP_SLEEPONEXIT))

/** @defgroup MISC_Preemption_Priority_Group
  */
#define NVIC_PriorityGroup_0         ((uint32_t)0x700) /*!< 0 位用于抢占优先级 4 位用于子优先级 */
#define NVIC_PriorityGroup_1         ((uint32_t)0x600) /*!< 1 位用于抢占优先级 3 位用于子优先级 */
#define NVIC_PriorityGroup_2         ((uint32_t)0x500) /*!< 2 位用于抢占优先级 2 位用于子优先级 */
#define NVIC_PriorityGroup_3         ((uint32_t)0x400) /*!< 3 位用于抢占优先级 1 位用于子优先级 */
#define NVIC_PriorityGroup_4         ((uint32_t)0x300) /*!< 4 位用于抢占优先级 0 位用于子优先级 */

#define IS_NVIC_PRIORITY_GROUP(GROUP) (((GROUP) == NVIC_PriorityGroup_0) || \
                                       ((GROUP) == NVIC_PriorityGroup_1) || \
                                       ((GROUP) == NVIC_PriorityGroup_2) || \
                                       ((GROUP) == NVIC_PriorityGroup_3) || \
                                       ((GROUP) == NVIC_PriorityGroup_4))

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

#define IS_NVIC_SUB_PRIORITY(PRIORITY)  ((PRIORITY) < 0x10)

#define IS_NVIC_OFFSET(OFFSET)  ((OFFSET) < 0x000FFFFF)


/** @defgroup MISC_SysTick_clock_source
  */
#define SysTick_CLKSource_HCLK_Div8    ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK         ((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \
                                       ((SOURCE) == SysTick_CLKSource_HCLK_Div8))


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* 配置优先级分组:抢占优先级和子优先级。 */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);

/* 根据 NVIC_InitStruct 中指定的参数初始化 NVIC 外设。 */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);

/* 设置矢量表位置和偏移量。 */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);

/* 选择系统进入低功耗模式的条件。 */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState);

/* 配置 SysTick 时钟源。 */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

#ifdef __cplusplus
}
#endif

#endif /* __MISC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
