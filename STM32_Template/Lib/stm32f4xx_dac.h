/**
  ******************************************************************************
  * 文件:    stm32f4xx_dac.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 DAC 固件库的所有功能原型.
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
#ifndef __STM32F4xx_DAC_H
#define __STM32F4xx_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup DAC
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  DAC Init structure definition
  */
typedef struct {
    uint32_t DAC_Trigger;                      /*!< 指定所选 DAC 通道的外部触发。
												                        该参数可以是 @ref DAC_trigger_selection 的值 */

    uint32_t DAC_WaveGeneration;               /*!< 指定是否生成 DAC 通道噪声波或三角波，或者是否不生成波。
												                        该参数可以是 @ref DAC_wave_generation 的值 */

    uint32_t DAC_LFSRUnmask_TriangleAmplitude; /*!< 为 DAC 通道指定噪声波生成或最大幅度三角形生成的 LFSR 掩码。
												                        此参数可以是 @ref DAC_lfsrunmask_triangleamplitude 的值 */

    uint32_t DAC_OutputBuffer;                 /*!< 指定是启用还是禁用 DAC 通道输出缓冲器。
												                        该参数可以是 @ref DAC_output_buffer 的值 */
} DAC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DAC_Exported_Constants
  */

/** @defgroup DAC_trigger_selection
  */
#define DAC_Trigger_None                   ((uint32_t)0x00000000) /*!< 一旦加载了 DAC1_DHRxxxx 寄存器，转换是自动的，而不是通过外部触发 */
#define DAC_Trigger_T2_TRGO                ((uint32_t)0x00000024) /*!< 选择 TIM2 TRGO 作为 DAC 通道的外部转换触发 */
#define DAC_Trigger_T4_TRGO                ((uint32_t)0x0000002C) /*!< 选择 TIM4 TRGO 作为 DAC 通道的外部转换触发 */
#define DAC_Trigger_T5_TRGO                ((uint32_t)0x0000001C) /*!< 选择 TIM5 TRGO 作为 DAC 通道的外部转换触发 */
#define DAC_Trigger_T6_TRGO                ((uint32_t)0x00000004) /*!< 选择 TIM6 TRGO 作为 DAC 通道的外部转换触发 */
#define DAC_Trigger_T7_TRGO                ((uint32_t)0x00000014) /*!< 选择 TIM7 TRGO 作为 DAC 通道的外部转换触发 */
#define DAC_Trigger_T8_TRGO                ((uint32_t)0x0000000C) /*!< 选择 TIM8 TRGO 作为 DAC 通道的外部转换触发 */

#define DAC_Trigger_Ext_IT9                ((uint32_t)0x00000034) /*!< 选择 EXTI Line9 事件作为 DAC 通道的外部转换触发 */
#define DAC_Trigger_Software               ((uint32_t)0x0000003C) /*!< 由 DAC 通道的软件触发启动转换 */

#define IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_None) || \
                                 ((TRIGGER) == DAC_Trigger_T6_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T8_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T7_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T5_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T2_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_T4_TRGO) || \
                                 ((TRIGGER) == DAC_Trigger_Ext_IT9) || \
                                 ((TRIGGER) == DAC_Trigger_Software))


/** @defgroup DAC_wave_generation
  */
#define DAC_WaveGeneration_None            ((uint32_t)0x00000000)
#define DAC_WaveGeneration_Noise           ((uint32_t)0x00000040)
#define DAC_WaveGeneration_Triangle        ((uint32_t)0x00000080)
#define IS_DAC_GENERATE_WAVE(WAVE) (((WAVE) == DAC_WaveGeneration_None) || \
                                    ((WAVE) == DAC_WaveGeneration_Noise) || \
                                    ((WAVE) == DAC_WaveGeneration_Triangle))

/** @defgroup DAC_lfsrunmask_triangleamplitude
  */
#define DAC_LFSRUnmask_Bit0                ((uint32_t)0x00000000) /*!< 取消屏蔽 DAC 通道 LFSR bit0 以生成噪声波 */
#define DAC_LFSRUnmask_Bits1_0             ((uint32_t)0x00000100) /*!< 取消屏蔽 DAC 通道 LFSR 位 [1:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits2_0             ((uint32_t)0x00000200) /*!< 取消屏蔽 DAC 通道 LFSR 位 [2:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits3_0             ((uint32_t)0x00000300) /*!< 取消屏蔽 DAC 通道 LFSR 位 [3:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits4_0             ((uint32_t)0x00000400) /*!< 取消屏蔽 DAC 通道 LFSR 位 [4:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits5_0             ((uint32_t)0x00000500) /*!< 取消屏蔽 DAC 通道 LFSR 位 [5:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits6_0             ((uint32_t)0x00000600) /*!< 取消屏蔽 DAC 通道 LFSR 位 [6:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits7_0             ((uint32_t)0x00000700) /*!< 取消屏蔽 DAC 通道 LFSR 位 [7:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits8_0             ((uint32_t)0x00000800) /*!< 取消屏蔽 DAC 通道 LFSR 位 [8:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits9_0             ((uint32_t)0x00000900) /*!< 取消屏蔽 DAC 通道 LFSR 位 [9:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits10_0            ((uint32_t)0x00000A00) /*!< 取消屏蔽 DAC 通道 LFSR 位 [10:0] 以生成噪声波 */
#define DAC_LFSRUnmask_Bits11_0            ((uint32_t)0x00000B00) /*!< 取消屏蔽 DAC 通道 LFSR 位 [11:0] 以生成噪声波 */
#define DAC_TriangleAmplitude_1            ((uint32_t)0x00000000) /*!< 选择最大三角形幅度为 1 */
#define DAC_TriangleAmplitude_3            ((uint32_t)0x00000100) /*!< 选择最大三角形幅度为 3 */
#define DAC_TriangleAmplitude_7            ((uint32_t)0x00000200) /*!< 选择最大三角形幅度为 7 */
#define DAC_TriangleAmplitude_15           ((uint32_t)0x00000300) /*!< 选择最大三角形幅度为 15 */
#define DAC_TriangleAmplitude_31           ((uint32_t)0x00000400) /*!< 选择最大三角形幅度为 31 */
#define DAC_TriangleAmplitude_63           ((uint32_t)0x00000500) /*!< 选择最大三角形幅度为 63 */
#define DAC_TriangleAmplitude_127          ((uint32_t)0x00000600) /*!< 选择最大三角形幅度为 127 */
#define DAC_TriangleAmplitude_255          ((uint32_t)0x00000700) /*!< 选择最大三角形幅度为 255 */
#define DAC_TriangleAmplitude_511          ((uint32_t)0x00000800) /*!< 选择最大三角形幅度为 511 */
#define DAC_TriangleAmplitude_1023         ((uint32_t)0x00000900) /*!< 选择最大三角形幅度为 1023 */
#define DAC_TriangleAmplitude_2047         ((uint32_t)0x00000A00) /*!< 选择最大三角形幅度为 2047 */
#define DAC_TriangleAmplitude_4095         ((uint32_t)0x00000B00) /*!< 选择最大三角形幅度为 4096 */

#define IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) (((VALUE) == DAC_LFSRUnmask_Bit0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits1_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits2_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits3_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits4_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits5_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits6_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits7_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits8_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits9_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits10_0) || \
        ((VALUE) == DAC_LFSRUnmask_Bits11_0) || \
        ((VALUE) == DAC_TriangleAmplitude_1) || \
        ((VALUE) == DAC_TriangleAmplitude_3) || \
        ((VALUE) == DAC_TriangleAmplitude_7) || \
        ((VALUE) == DAC_TriangleAmplitude_15) || \
        ((VALUE) == DAC_TriangleAmplitude_31) || \
        ((VALUE) == DAC_TriangleAmplitude_63) || \
        ((VALUE) == DAC_TriangleAmplitude_127) || \
        ((VALUE) == DAC_TriangleAmplitude_255) || \
        ((VALUE) == DAC_TriangleAmplitude_511) || \
        ((VALUE) == DAC_TriangleAmplitude_1023) || \
        ((VALUE) == DAC_TriangleAmplitude_2047) || \
        ((VALUE) == DAC_TriangleAmplitude_4095))

/** @defgroup DAC_output_buffer
  */
#define DAC_OutputBuffer_Enable            ((uint32_t)0x00000000)
#define DAC_OutputBuffer_Disable           ((uint32_t)0x00000002)
#define IS_DAC_OUTPUT_BUFFER_STATE(STATE) (((STATE) == DAC_OutputBuffer_Enable) || \
        ((STATE) == DAC_OutputBuffer_Disable))

/** @defgroup DAC_Channel_selection
  */
#define DAC_Channel_1                      ((uint32_t)0x00000000)
#define DAC_Channel_2                      ((uint32_t)0x00000010)
#define IS_DAC_CHANNEL(CHANNEL) (((CHANNEL) == DAC_Channel_1) || \
                                 ((CHANNEL) == DAC_Channel_2))

/** @defgroup DAC_data_alignement
  */
#define DAC_Align_12b_R                    ((uint32_t)0x00000000)
#define DAC_Align_12b_L                    ((uint32_t)0x00000004)
#define DAC_Align_8b_R                     ((uint32_t)0x00000008)
#define IS_DAC_ALIGN(ALIGN) (((ALIGN) == DAC_Align_12b_R) || \
                             ((ALIGN) == DAC_Align_12b_L) || \
                             ((ALIGN) == DAC_Align_8b_R))

/** @defgroup DAC_wave_generation
  */
#define DAC_Wave_Noise                     ((uint32_t)0x00000040)
#define DAC_Wave_Triangle                  ((uint32_t)0x00000080)
#define IS_DAC_WAVE(WAVE) (((WAVE) == DAC_Wave_Noise) || \
                           ((WAVE) == DAC_Wave_Triangle))

/** @defgroup DAC_data
  */
#define IS_DAC_DATA(DATA) ((DATA) <= 0xFFF0)

/** @defgroup DAC_interrupts_definition
  */
#define DAC_IT_DMAUDR                      ((uint32_t)0x00002000)
#define IS_DAC_IT(IT) (((IT) == DAC_IT_DMAUDR))


/** @defgroup DAC_flags_definition
  */
#define DAC_FLAG_DMAUDR                    ((uint32_t)0x00002000)
#define IS_DAC_FLAG(FLAG) (((FLAG) == DAC_FLAG_DMAUDR))



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 DAC 配置设置为默认复位状态的函数 *****/
void DAC_DeInit(void);

/*  DAC通道配置:触发、输出缓冲器、数据格式功能 */
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct); // 根据 DAC_InitStruct 中指定的参数初始化 DAC 外设。
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct); // 用默认值填充每个 DAC_InitStruct 成员。
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState); // 根据 DAC_InitStruct 中指定的参数初始化 DAC 外设。
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState); // 启用或禁用选定的 DAC 通道软件触发。
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState); // 同时启用或禁用两个 DAC 通道软件触发。
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState); // 启用或禁用选定的 DAC 通道波形生成。
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data); // 为 DAC 通道 1 设置指定的数据保持寄存器值。
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data); // 为 DAC 通道 2 设置指定的数据保持寄存器值。
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1); // 为双通道 DAC 设置指定的数据保持寄存器值。
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel); // 返回所选 DAC 通道的最后一个数据输出值。

/* DMA管理功能 ***************************************************/
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState); // 启用或禁用指定的 DAC 通道 DMA 请求。

/* 中断和标志管理功能 **********************************/
void DAC_ITConfig(uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState); // 启用或禁用指定的 DAC 中断。
FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG); // 检查是否设置了指定的 DAC 标志。
void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG); // 清除 DAC 通道的挂起标志。
ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT); // 检查是否发生了指定的 DAC 中断。
void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT); // 清除 DAC 通道的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_DAC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
