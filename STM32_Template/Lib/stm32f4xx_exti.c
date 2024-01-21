/**
  ******************************************************************************
  * 文件:    stm32f4xx_exti.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，用于管理EXTI外设设备的以下功能:
  *           + 初始化和配置
  *           + 中断和标志管理
  *
@verbatim

 ===============================================================================
                              ##### EXTI功能 #####
 ===============================================================================

 [..] 外部中断/事件行映射如下:
   (#) 所有可用的 GPIO 引脚都连接到 EXTI0 到 EXTI15 的 16 条外部中断/事件线。
   (#) EXTI线路 1 6连接到 PVD 输出
   (#) EXTI线路 17 连接至 RTC 报警事件
   (#) EXTI线路 18 连接到 USB OTG FS 唤醒暂停事件
   (#) EXTI线路 19 连接到以太网唤醒事件
   (#) EXTI线路 20 连接到 USB OTG HS(在FS中配置)唤醒事件
   (#) EXTI线路 21 连接到 RTC篡改和时间戳事件
   (#) EXTI线路 22 连接至 RTC唤醒事件
   (#) EXTI线路 23 连接到LPTIM 唤醒事件

                       ##### 如何使用这个驱动程序 #####
 ===============================================================================

 [..] 为了将I/O引脚用作外部中断源，请执行以下步骤:
   (#) 使用 GPIO_Init() 在输入模式下配置I/O
   (#) 使用 SYSCFG_EXTILineConfig() 为EXTI线选择输入源引脚
   (#) 使用 EXTI_Init() 选择模式(中断、事件)并配置触发器选择(上升、下降或两者)
   (#) 使用 NVIC_Init() 配置映射到 EXTI 行的 NVIC IRQ 通道

 [..]
   (@) 必须启用SYSCFG APB时钟，才能使用RCC_APB2PeriphClockCmd(RCC_APP2PeripH_SYSCFG，ENABLE)
       对SYSCFG_EXTICRx寄存器进行写入访问;

@endverbatim
  *
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
#include "stm32f4xx_exti.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI
  * 简介: EXTI 驱动模块
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

#define EXTI_LINENONE    ((uint32_t)0x00000)  /* No interrupt selected */

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup EXTI_Private_Functions
  * @{
  */

/** @defgroup EXTI_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
             ##### 初始化和配置函数 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  将 EXTI 外设寄存器取消初始化为其默认复位值。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void EXTI_DeInit(void) {
    EXTI->IMR = 0x00000000;
    EXTI->EMR = 0x00000000;
    EXTI->RTSR = 0x00000000;
    EXTI->FTSR = 0x00000000;
    EXTI->PR = 0x007FFFFF;
}

/**
  * 简介:  根据 EXTI_InitStruct 中指定的参数初始化 EXTI 外设。
  * 
  * 参数:  EXTI_InitStruct: 指向包含EXTI外设设备配置信息的EXTI_InitTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct) {
    uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
    assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
    assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));
    assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineCmd));

    tmp = (uint32_t)EXTI_BASE;

    if (EXTI_InitStruct->EXTI_LineCmd != DISABLE) {
        /* 清除 EXTI 行的配置*/
        EXTI->IMR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->EMR &= ~EXTI_InitStruct->EXTI_Line;

        tmp += EXTI_InitStruct->EXTI_Mode;

        *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;

        /* 清除上升下降边缘配置*/
        EXTI->RTSR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->FTSR &= ~EXTI_InitStruct->EXTI_Line;

        /* 选择这个所选外部中断的触发器 */
        if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling) {
            /* 上升下降沿 */
            EXTI->RTSR |= EXTI_InitStruct->EXTI_Line;
            EXTI->FTSR |= EXTI_InitStruct->EXTI_Line;
        } else {
            tmp = (uint32_t)EXTI_BASE;
            tmp += EXTI_InitStruct->EXTI_Trigger;

            *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
        }
    } else {
        tmp += EXTI_InitStruct->EXTI_Mode;

        /* 禁用被选中的 external lines */
        *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
    }
}

/**
  * 简介:  用其重置值填充每个 EXTI_InitStruct 成员。
  * 
  * 参数:  EXTI_InitStruct: 指向将被初始化的EXTI_InitTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct) {
    EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
    EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

/**
  * 简介:  在选定的 EXTI 线上产生一个软件中断。
  * 
  * 参数:  EXTI_Line: 指定将在其上生成软件中断的EXTI行。
  *         此参数可以是EXTI_Linex的任意组合，其中x可以是(0..22)
  * 
  * 返回值: 无
  */
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line) {
    /* 检查参数 */
    assert_param(IS_EXTI_LINE(EXTI_Line));

    EXTI->SWIER |= EXTI_Line;
}

/**
  * @}
  */

/** @defgroup EXTI_Group2 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
             ##### 中断和标记管理函数 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  检查是否设置了指定的 EXTI 行标志。
  * 
  * 参数:  EXTI_Line: 指定要检查的EXTI行标志。
  *          此参数可以是EXTI_Linex，其中x可以是(0..22)
  * 
  * 返回值: EXTI_Line的新状态(SET或RESET)。
  */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));

    if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 EXTI 的行挂起标志。
  * 
  * 参数:  EXTI_Line: 指定要清除的EXTI行标志。
  *          此参数可以是EXTI_Linex的任意组合，其中x可以是(0..22)
  * 
  * 返回值: 无
  */
void EXTI_ClearFlag(uint32_t EXTI_Line) {
    /* 检查参数 */
    assert_param(IS_EXTI_LINE(EXTI_Line));

    EXTI->PR = EXTI_Line;
}

/**
  * 简介:  检查指定的 EXTI 行是否被断言。
  * 
  * 参数:  EXTI_Line: 指定要检查的EXTI行。
  *          此参数可以是EXTI_Linex，其中x可以是(0..22)
  * 
  * 返回值: EXTI_Line的新状态(SET或RESET)。
  */
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_GET_EXTI_LINE(EXTI_Line));

    if ((EXTI->PR & EXTI_Line) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;

}

/**
  * 简介:  清除 EXTI 的行挂起位。
  * 
  * 参数:  EXTI_Line: 指定要清除的EXTI行。
  *          此参数可以是EXTI_Linex的任意组合，其中x可以是(0..22)
  * 
  * 返回值: 无
  */
void EXTI_ClearITPendingBit(uint32_t EXTI_Line) {
    /* 检查参数 */
    assert_param(IS_EXTI_LINE(EXTI_Line));

    EXTI->PR = EXTI_Line;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
