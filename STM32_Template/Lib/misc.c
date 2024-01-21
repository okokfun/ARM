/**
  ******************************************************************************
  * 文件:    misc.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供所有其他固件功能(CMSIS功能的附加功能)。
  *
  *  @verbatim
  *
  *          ===================================================================
  *                        如何使用驱动程序配置中断
  *          ===================================================================
  *
  *            本节提供允许配置 NVIC 中断 (IRQ) 的功能。
  *            Cortex-M4 异常由 CMSIS 函数管理。
  *
  *            1. 根据下表使用 NVIC_PriorityGroupConfig() 函数配置 NVIC 优先级分组。
  *
  *  根据 NVIC_PriorityGroupConfig 函数执行的 Priority Grouping 配置，下表给出了抢占优先级和子优先级的允许值
  *    ==========================================================================================================================
  *      NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  |       描述
  *    ==========================================================================================================================
  *     NVIC_PriorityGroup_0  |                0                  |            0-15             | 抢占优先级为0位
  *                           |                                   |                             | 4位用于次优先级
  *    --------------------------------------------------------------------------------------------------------------------------
  *     NVIC_PriorityGroup_1  |                0-1                |            0-7              | 先占优先级为1位
  *                           |                                   |                             | 子优先级为3位
  *    --------------------------------------------------------------------------------------------------------------------------
  *     NVIC_PriorityGroup_2  |                0-3                |            0-3              | 先占优先级为2位
  *                           |                                   |                             | 子优先级为2位
  *    --------------------------------------------------------------------------------------------------------------------------
  *     NVIC_PriorityGroup_3  |                0-7                |            0-1              | 先占优先级为3位
  *                           |                                   |                             | 子优先级为1位
  *    --------------------------------------------------------------------------------------------------------------------------
  *     NVIC_PriorityGroup_4  |                0-15               |            0                | 先占优先级为4位
  *                           |                                   |                             | 子优先级为0位
  *    ==========================================================================================================================
  *
  *            2. 使用 NVIC_Init() 启用和配置所选 IRQ 通道的优先级
  *
  * 注意:  当NVIC prioritygroup0被选中时，IRQ抢占将不再可能。
  *        挂起的 IRQ 优先级将仅由子优先级管理。
  *
  * 注意:  IRQ优先级顺序(按最高优先级到最低优先级排序)
  *         - Lowest 抢占式优先级
  *         - Lowest 优先权
  *         - Lowest 硬件优先级(IRQ号)
  *
  *  @endverbatim
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
#include "misc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup MISC
  * 简介: MISC驱动模块
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define AIRCR_VECTKEY_MASK    ((uint32_t)0x05FA0000)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup MISC_Private_Functions
  * @{
  */

/**
  * 简介: 配置优先级分组:抢占优先级和子优先级。
  * 
  * 参数: NVIC_PriorityGroup:指定优先级分组位长度。
  * 此参数可以是以下值之一:
                @arg NVIC_PriorityGroup_0: 0 位用于抢占优先级
   	                                       4 位用于子优先级

                @arg NVIC_PriorityGroup_1: 1 位用于抢占优先级
   	                                       3 位用于子优先级

                @arg NVIC_PriorityGroup_2: 2 位用于抢占优先级
   	                                       2 位用于子优先级

                @arg NVIC_PriorityGroup_3: 3 位用于抢占优先级
   	                                       1 位用于子优先级

                @arg NVIC_PriorityGroup_4: 4 位用于抢占优先级
   	                                       0 位表示子优先级

  * 注意: 选择 NVIC_PRIORITYGROUP_0 时，IRQ预先抢先是不可能的。
  *       挂起的 IRQ 优先级将仅由子优先级管理。
  * 
  * 返回值: 无
  */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup) {
    /* 检查参数 */
    assert_param(IS_NVIC_PRIORITY_GROUP(NVIC_PriorityGroup));

    /* 设置 根据 NVIC_PriorityGroup 的 PRIGROUP[10:8] 位值*/
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
   * 简介: 根据指定初始化 NVIC 外设 NVIC_InitStruct 中的参数。
   * 
   * 注意: 要正确配置中断优先级，NVIC_PriorityGroupConfig()
   *       函数应该在之前调用。
   * 
   * 参数: NVIC_InitStruct: 指向 NVIC_InitTypeDef 结构的指针，
   *       该结构包含指定 NVIC 外设的配置信息。
   * 
   * 返回值: 无
   */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct) {
    uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NVIC_InitStruct->NVIC_IRQChannelCmd));
    assert_param(IS_NVIC_PREEMPTION_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority));
    assert_param(IS_NVIC_SUB_PRIORITY(NVIC_InitStruct->NVIC_IRQChannelSubPriority));

    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE) {
        /* 计算相应的 IRQ 优先级 --------------------------------*/
        tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t)0x700)) >> 0x08;
        tmppre = (0x4 - tmppriority);
        tmpsub = tmpsub >> tmppriority;

        tmppriority = NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
        tmppriority |=  (uint8_t)(NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub);

        tmppriority = tmppriority << 0x04;

        NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = tmppriority;

        /* 启用选定的 IRQ 通道 --------------------------------------*/
        NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
            (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    } else {
        /* 禁用选定的 IRQ 通道 -------------------------------------*/
        NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] =
            (uint32_t)0x01 << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    }
}

/**
   * 简介: 设置向量表位置和偏移量。
   * 
   * 参数: NVIC_VectTab: 指定向量表是在 RAM 还是 FLASH 存储器中。
   * 此参数可以是以下值之一:
   * 	@arg NVIC_VectTab_RAM: 内部 SRAM 中的向量表。
   * 	@arg NVIC_VectTab_FLASH: 内部 FLASH 中的向量表。
   * 
   * 参数: Offset: 向量表基本偏移字段。 
   *       该值必须是 0x200 的倍数。
   * 
   * 返回值: 无
   */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset) {
    /* 检查参数 */
    assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
    assert_param(IS_NVIC_OFFSET(Offset));

    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80);
}

/**
   * 简介: 选择系统进入低功耗模式的条件。
   * 
   * 参数: LowPowerMode: 指定系统进入低功耗模式的新模式。
   * 此参数可以是以下值之一:
   * 	@arg NVIC_LP_SEVONPEND: 低功耗 SEV 挂起。
   * 	@arg NVIC_LP_SLEEPDEEP: 低功耗 DEEPSLEEP 请求。
   * 	@arg NVIC_LP_SLEEPONEXIT: 退出时低功耗睡眠。
   * 
   * 参数: NewState:LP 条件的新状态。 
   *      该参数可以是: ENABLE 或 DISABLE。
   * 
   * 返回值: 无
   */
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_NVIC_LP(LowPowerMode));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        SCB->SCR |= LowPowerMode;
    } else {
        SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
    }
}

/**
  * 简介: 配置 SysTick 时钟源。
  * 
  * 参数:  sysTick_CLKSource: 指定 SysTick 时钟源。
  *  此参数可以是以下值之一:
  * 	@arg SysTick_CLKSource_HCLK_Div8: AHB 时钟除以 8 被选为 SysTick 时钟源。
  * 	@arg SysTick_CLKSource_HCLK: 选择 AHB 时钟作为 SysTick 时钟源。
  * 
  * 返回值: 无
*/
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource) {
    /* 检查参数 */
    assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));

    if (SysTick_CLKSource == SysTick_CLKSource_HCLK) {
        SysTick->CTRL |= SysTick_CLKSource_HCLK;
    } else {
        SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
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
