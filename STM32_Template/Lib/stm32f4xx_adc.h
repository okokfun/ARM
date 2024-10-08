/**
  ******************************************************************************
  * 文件:    stm32f4xx_adc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 ADC 固件库的所有功能原型。
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
#ifndef __STM32F4xx_ADC_H
#define __STM32F4xx_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup ADC
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:    ADC初始化结构定义
  */
typedef struct {
    uint32_t ADC_Resolution;                /*!< 配置 ADC 分辨率双模式。
                                            该参数可以是 @ref ADC_resolution 的值 */

    FunctionalState ADC_ScanConvMode;       /*!< 指定是在扫描(多通道)还是单(单通道)模式下执行转换。
											                      此参数可设置为 ENABLE 或 DISABLE */

    FunctionalState ADC_ContinuousConvMode; /*!< 指定是在连续模式还是单次模式下执行转换。
                                            此参数可以设置为 ENABLE 或 DISABLE。 */

    uint32_t ADC_ExternalTrigConvEdge;      /*!< 选择外部触发沿并启用常规组的触发。
											                      该参数可以是 @ref ADC_external_trigger_edge_for_regular_channels_conversion 的值 */

    uint32_t ADC_ExternalTrigConv;          /*!< 选择用于触发常规组转换开始的外部事件。
                                            此参数可以是 @ref ADC_extrenal_trigger_sources_for_regular_channels_conversion 的值 */

    uint32_t ADC_DataAlign;                 /*!< 指定 ADC 数据对齐是左对齐还是右对齐。
                                            该参数可以是 @ref ADC_data_align 的值 */

    uint8_t  ADC_NbrOfConversion;           /*!< 指定将使用常规通道组的定序器完成的 ADC 转换次数。
                                            此参数的范围必须为 1 到 16。 */
} ADC_InitTypeDef;

/**
  * 简介:    ADC Common Init 结构定义
  */
typedef struct {
    uint32_t ADC_Mode;                      /*!< 将 ADC 配置为在独立模式或多模式下运行。
											                      该参数可以是 @ref ADC_Common_mode 的值 */

    uint32_t ADC_Prescaler;                 /*!< 选择 ADC 的时钟频率。 时钟对所有 ADC 都是通用的。
											                      该参数可以是 @ref ADC_Prescaler 的值 */

    uint32_t ADC_DMAAccessMode;             /*!< 为多 ADC 模式配置直接内存访问模式。
											                      该参数可以是 @ref ADC_Direct_memory_access_mode_for_multi_mode 的值 */

    uint32_t ADC_TwoSamplingDelay;          /*!< 配置 2 个采样阶段之间的延迟。
											                      该参数可以是 @ref ADC_delay_between_2_sampling_phases 的值 */
} ADC_CommonInitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  */
#define IS_ADC_ALL_PERIPH(PERIPH) (((PERIPH) == ADC1) || \
                                   ((PERIPH) == ADC2) || \
                                   ((PERIPH) == ADC3))

/** @defgroup ADC_Common_mode
  */
#define ADC_Mode_Independent                       ((uint32_t)0x00000000)
#define ADC_DualMode_RegSimult_InjecSimult         ((uint32_t)0x00000001)
#define ADC_DualMode_RegSimult_AlterTrig           ((uint32_t)0x00000002)
#define ADC_DualMode_InjecSimult                   ((uint32_t)0x00000005)
#define ADC_DualMode_RegSimult                     ((uint32_t)0x00000006)
#define ADC_DualMode_Interl                        ((uint32_t)0x00000007)
#define ADC_DualMode_AlterTrig                     ((uint32_t)0x00000009)
#define ADC_TripleMode_RegSimult_InjecSimult       ((uint32_t)0x00000011)
#define ADC_TripleMode_RegSimult_AlterTrig         ((uint32_t)0x00000012)
#define ADC_TripleMode_InjecSimult                 ((uint32_t)0x00000015)
#define ADC_TripleMode_RegSimult                   ((uint32_t)0x00000016)
#define ADC_TripleMode_Interl                      ((uint32_t)0x00000017)
#define ADC_TripleMode_AlterTrig                   ((uint32_t)0x00000019)
#define IS_ADC_MODE(MODE) (((MODE) == ADC_Mode_Independent) || \
                           ((MODE) == ADC_DualMode_RegSimult_InjecSimult) || \
                           ((MODE) == ADC_DualMode_RegSimult_AlterTrig) || \
                           ((MODE) == ADC_DualMode_InjecSimult) || \
                           ((MODE) == ADC_DualMode_RegSimult) || \
                           ((MODE) == ADC_DualMode_Interl) || \
                           ((MODE) == ADC_DualMode_AlterTrig) || \
                           ((MODE) == ADC_TripleMode_RegSimult_InjecSimult) || \
                           ((MODE) == ADC_TripleMode_RegSimult_AlterTrig) || \
                           ((MODE) == ADC_TripleMode_InjecSimult) || \
                           ((MODE) == ADC_TripleMode_RegSimult) || \
                           ((MODE) == ADC_TripleMode_Interl) || \
                           ((MODE) == ADC_TripleMode_AlterTrig))


/** @defgroup ADC_Prescaler
  */
#define ADC_Prescaler_Div2                         ((uint32_t)0x00000000)
#define ADC_Prescaler_Div4                         ((uint32_t)0x00010000)
#define ADC_Prescaler_Div6                         ((uint32_t)0x00020000)
#define ADC_Prescaler_Div8                         ((uint32_t)0x00030000)
#define IS_ADC_PRESCALER(PRESCALER) (((PRESCALER) == ADC_Prescaler_Div2) || \
                                     ((PRESCALER) == ADC_Prescaler_Div4) || \
                                     ((PRESCALER) == ADC_Prescaler_Div6) || \
                                     ((PRESCALER) == ADC_Prescaler_Div8))


/** @defgroup ADC_Direct_memory_access_mode_for_multi_mode
  */
#define ADC_DMAAccessMode_Disabled      ((uint32_t)0x00000000)     /* 禁用 DMA 模式 */
#define ADC_DMAAccessMode_1             ((uint32_t)0x00004000)     /* 启用 DMA 模式 1(2 / 3 个半字一个接一个 - 1 然后 2 然后 3)*/
#define ADC_DMAAccessMode_2             ((uint32_t)0x00008000)     /* 启用 DMA 模式 2(成对的 2 / 3 个半字 - 2&1 然后 1&3 然后 3&2)*/
#define ADC_DMAAccessMode_3             ((uint32_t)0x0000C000)     /* 启用 DMA 模式 3(成对 2 / 3 个字节 - 2&1 然后 1&3 然后 3&2) */
#define IS_ADC_DMA_ACCESS_MODE(MODE) (((MODE) == ADC_DMAAccessMode_Disabled) || \
                                      ((MODE) == ADC_DMAAccessMode_1) || \
                                      ((MODE) == ADC_DMAAccessMode_2) || \
                                      ((MODE) == ADC_DMAAccessMode_3))



/** @defgroup ADC_delay_between_2_sampling_phases
  */
#define ADC_TwoSamplingDelay_5Cycles               ((uint32_t)0x00000000)
#define ADC_TwoSamplingDelay_6Cycles               ((uint32_t)0x00000100)
#define ADC_TwoSamplingDelay_7Cycles               ((uint32_t)0x00000200)
#define ADC_TwoSamplingDelay_8Cycles               ((uint32_t)0x00000300)
#define ADC_TwoSamplingDelay_9Cycles               ((uint32_t)0x00000400)
#define ADC_TwoSamplingDelay_10Cycles              ((uint32_t)0x00000500)
#define ADC_TwoSamplingDelay_11Cycles              ((uint32_t)0x00000600)
#define ADC_TwoSamplingDelay_12Cycles              ((uint32_t)0x00000700)
#define ADC_TwoSamplingDelay_13Cycles              ((uint32_t)0x00000800)
#define ADC_TwoSamplingDelay_14Cycles              ((uint32_t)0x00000900)
#define ADC_TwoSamplingDelay_15Cycles              ((uint32_t)0x00000A00)
#define ADC_TwoSamplingDelay_16Cycles              ((uint32_t)0x00000B00)
#define ADC_TwoSamplingDelay_17Cycles              ((uint32_t)0x00000C00)
#define ADC_TwoSamplingDelay_18Cycles              ((uint32_t)0x00000D00)
#define ADC_TwoSamplingDelay_19Cycles              ((uint32_t)0x00000E00)
#define ADC_TwoSamplingDelay_20Cycles              ((uint32_t)0x00000F00)
#define IS_ADC_SAMPLING_DELAY(DELAY) (((DELAY) == ADC_TwoSamplingDelay_5Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_6Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_7Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_8Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_9Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_10Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_11Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_12Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_13Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_14Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_15Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_16Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_17Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_18Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_19Cycles) || \
                                      ((DELAY) == ADC_TwoSamplingDelay_20Cycles))



/** @defgroup ADC_resolution
  */
#define ADC_Resolution_12b                         ((uint32_t)0x00000000)
#define ADC_Resolution_10b                         ((uint32_t)0x01000000)
#define ADC_Resolution_8b                          ((uint32_t)0x02000000)
#define ADC_Resolution_6b                          ((uint32_t)0x03000000)
#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_Resolution_12b) || \
                                       ((RESOLUTION) == ADC_Resolution_10b) || \
                                       ((RESOLUTION) == ADC_Resolution_8b) || \
                                       ((RESOLUTION) == ADC_Resolution_6b))



/** @defgroup ADC_external_trigger_edge_for_regular_channels_conversion
  */
#define ADC_ExternalTrigConvEdge_None          ((uint32_t)0x00000000)
#define ADC_ExternalTrigConvEdge_Rising        ((uint32_t)0x10000000)
#define ADC_ExternalTrigConvEdge_Falling       ((uint32_t)0x20000000)
#define ADC_ExternalTrigConvEdge_RisingFalling ((uint32_t)0x30000000)
#define IS_ADC_EXT_TRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigConvEdge_None) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Rising) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_Falling) || \
                                    ((EDGE) == ADC_ExternalTrigConvEdge_RisingFalling))


/** @defgroup ADC_extrenal_trigger_sources_for_regular_channels_conversion
  */
#define ADC_ExternalTrigConv_T1_CC1                ((uint32_t)0x00000000)
#define ADC_ExternalTrigConv_T1_CC2                ((uint32_t)0x01000000)
#define ADC_ExternalTrigConv_T1_CC3                ((uint32_t)0x02000000)
#define ADC_ExternalTrigConv_T2_CC2                ((uint32_t)0x03000000)
#define ADC_ExternalTrigConv_T2_CC3                ((uint32_t)0x04000000)
#define ADC_ExternalTrigConv_T2_CC4                ((uint32_t)0x05000000)
#define ADC_ExternalTrigConv_T2_TRGO               ((uint32_t)0x06000000)
#define ADC_ExternalTrigConv_T3_CC1                ((uint32_t)0x07000000)
#define ADC_ExternalTrigConv_T3_TRGO               ((uint32_t)0x08000000)
#define ADC_ExternalTrigConv_T4_CC4                ((uint32_t)0x09000000)
#define ADC_ExternalTrigConv_T5_CC1                ((uint32_t)0x0A000000)
#define ADC_ExternalTrigConv_T5_CC2                ((uint32_t)0x0B000000)
#define ADC_ExternalTrigConv_T5_CC3                ((uint32_t)0x0C000000)
#define ADC_ExternalTrigConv_T8_CC1                ((uint32_t)0x0D000000)
#define ADC_ExternalTrigConv_T8_TRGO               ((uint32_t)0x0E000000)
#define ADC_ExternalTrigConv_Ext_IT11              ((uint32_t)0x0F000000)
#define IS_ADC_EXT_TRIG(REGTRIG) (((REGTRIG) == ADC_ExternalTrigConv_T1_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T1_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_CC4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T2_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T3_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T4_CC4) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T5_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T5_CC2) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T5_CC3) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T8_CC1) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_T8_TRGO) || \
                                  ((REGTRIG) == ADC_ExternalTrigConv_Ext_IT11))


/** @defgroup ADC_data_align
  */
#define ADC_DataAlign_Right                        ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                         ((uint32_t)0x00000800)
#define IS_ADC_DATA_ALIGN(ALIGN) (((ALIGN) == ADC_DataAlign_Right) || \
                                  ((ALIGN) == ADC_DataAlign_Left))


/** @defgroup ADC_channels
  */
#define ADC_Channel_0                               ((uint8_t)0x00)
#define ADC_Channel_1                               ((uint8_t)0x01)
#define ADC_Channel_2                               ((uint8_t)0x02)
#define ADC_Channel_3                               ((uint8_t)0x03)
#define ADC_Channel_4                               ((uint8_t)0x04)
#define ADC_Channel_5                               ((uint8_t)0x05)
#define ADC_Channel_6                               ((uint8_t)0x06)
#define ADC_Channel_7                               ((uint8_t)0x07)
#define ADC_Channel_8                               ((uint8_t)0x08)
#define ADC_Channel_9                               ((uint8_t)0x09)
#define ADC_Channel_10                              ((uint8_t)0x0A)
#define ADC_Channel_11                              ((uint8_t)0x0B)
#define ADC_Channel_12                              ((uint8_t)0x0C)
#define ADC_Channel_13                              ((uint8_t)0x0D)
#define ADC_Channel_14                              ((uint8_t)0x0E)
#define ADC_Channel_15                              ((uint8_t)0x0F)
#define ADC_Channel_16                              ((uint8_t)0x10)
#define ADC_Channel_17                              ((uint8_t)0x11)
#define ADC_Channel_18                              ((uint8_t)0x12)

#if defined (STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define ADC_Channel_TempSensor                      ((uint8_t)ADC_Channel_16)
#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F410xx) || defined (STM32F411xE)
#define ADC_Channel_TempSensor                      ((uint8_t)ADC_Channel_18)
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F410xx || STM32F411xE */

#define ADC_Channel_Vrefint                         ((uint8_t)ADC_Channel_17)
#define ADC_Channel_Vbat                            ((uint8_t)ADC_Channel_18)

#define IS_ADC_CHANNEL(CHANNEL) (((CHANNEL) == ADC_Channel_0) || \
                                 ((CHANNEL) == ADC_Channel_1) || \
                                 ((CHANNEL) == ADC_Channel_2) || \
                                 ((CHANNEL) == ADC_Channel_3) || \
                                 ((CHANNEL) == ADC_Channel_4) || \
                                 ((CHANNEL) == ADC_Channel_5) || \
                                 ((CHANNEL) == ADC_Channel_6) || \
                                 ((CHANNEL) == ADC_Channel_7) || \
                                 ((CHANNEL) == ADC_Channel_8) || \
                                 ((CHANNEL) == ADC_Channel_9) || \
                                 ((CHANNEL) == ADC_Channel_10) || \
                                 ((CHANNEL) == ADC_Channel_11) || \
                                 ((CHANNEL) == ADC_Channel_12) || \
                                 ((CHANNEL) == ADC_Channel_13) || \
                                 ((CHANNEL) == ADC_Channel_14) || \
                                 ((CHANNEL) == ADC_Channel_15) || \
                                 ((CHANNEL) == ADC_Channel_16) || \
                                 ((CHANNEL) == ADC_Channel_17) || \
                                 ((CHANNEL) == ADC_Channel_18))


/** @defgroup ADC_sampling_times
  */
#define ADC_SampleTime_3Cycles                    ((uint8_t)0x00)
#define ADC_SampleTime_15Cycles                   ((uint8_t)0x01)
#define ADC_SampleTime_28Cycles                   ((uint8_t)0x02)
#define ADC_SampleTime_56Cycles                   ((uint8_t)0x03)
#define ADC_SampleTime_84Cycles                   ((uint8_t)0x04)
#define ADC_SampleTime_112Cycles                  ((uint8_t)0x05)
#define ADC_SampleTime_144Cycles                  ((uint8_t)0x06)
#define ADC_SampleTime_480Cycles                  ((uint8_t)0x07)
#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SampleTime_3Cycles) || \
                                  ((TIME) == ADC_SampleTime_15Cycles) || \
                                  ((TIME) == ADC_SampleTime_28Cycles) || \
                                  ((TIME) == ADC_SampleTime_56Cycles) || \
                                  ((TIME) == ADC_SampleTime_84Cycles) || \
                                  ((TIME) == ADC_SampleTime_112Cycles) || \
                                  ((TIME) == ADC_SampleTime_144Cycles) || \
                                  ((TIME) == ADC_SampleTime_480Cycles))


/** @defgroup ADC_external_trigger_edge_for_injected_channels_conversion
  */
#define ADC_ExternalTrigInjecConvEdge_None          ((uint32_t)0x00000000)
#define ADC_ExternalTrigInjecConvEdge_Rising        ((uint32_t)0x00100000)
#define ADC_ExternalTrigInjecConvEdge_Falling       ((uint32_t)0x00200000)
#define ADC_ExternalTrigInjecConvEdge_RisingFalling ((uint32_t)0x00300000)
#define IS_ADC_EXT_INJEC_TRIG_EDGE(EDGE) (((EDGE) == ADC_ExternalTrigInjecConvEdge_None) || \
        ((EDGE) == ADC_ExternalTrigInjecConvEdge_Rising) || \
        ((EDGE) == ADC_ExternalTrigInjecConvEdge_Falling) || \
        ((EDGE) == ADC_ExternalTrigInjecConvEdge_RisingFalling))



/** @defgroup ADC_extrenal_trigger_sources_for_injected_channels_conversion
  */
#define ADC_ExternalTrigInjecConv_T1_CC4            ((uint32_t)0x00000000)
#define ADC_ExternalTrigInjecConv_T1_TRGO           ((uint32_t)0x00010000)
#define ADC_ExternalTrigInjecConv_T2_CC1            ((uint32_t)0x00020000)
#define ADC_ExternalTrigInjecConv_T2_TRGO           ((uint32_t)0x00030000)
#define ADC_ExternalTrigInjecConv_T3_CC2            ((uint32_t)0x00040000)
#define ADC_ExternalTrigInjecConv_T3_CC4            ((uint32_t)0x00050000)
#define ADC_ExternalTrigInjecConv_T4_CC1            ((uint32_t)0x00060000)
#define ADC_ExternalTrigInjecConv_T4_CC2            ((uint32_t)0x00070000)
#define ADC_ExternalTrigInjecConv_T4_CC3            ((uint32_t)0x00080000)
#define ADC_ExternalTrigInjecConv_T4_TRGO           ((uint32_t)0x00090000)
#define ADC_ExternalTrigInjecConv_T5_CC4            ((uint32_t)0x000A0000)
#define ADC_ExternalTrigInjecConv_T5_TRGO           ((uint32_t)0x000B0000)
#define ADC_ExternalTrigInjecConv_T8_CC2            ((uint32_t)0x000C0000)
#define ADC_ExternalTrigInjecConv_T8_CC3            ((uint32_t)0x000D0000)
#define ADC_ExternalTrigInjecConv_T8_CC4            ((uint32_t)0x000E0000)
#define ADC_ExternalTrigInjecConv_Ext_IT15          ((uint32_t)0x000F0000)
#define IS_ADC_EXT_INJEC_TRIG(INJTRIG) (((INJTRIG) == ADC_ExternalTrigInjecConv_T1_CC4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T1_TRGO) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T2_CC1) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T2_TRGO) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T3_CC2) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T3_CC4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T4_CC1) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T4_CC2) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T4_CC3) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T4_TRGO) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T5_CC4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T5_TRGO) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T8_CC2) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T8_CC3) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_T8_CC4) || \
                                        ((INJTRIG) == ADC_ExternalTrigInjecConv_Ext_IT15))


/** @defgroup ADC_injected_channel_selection
  */
#define ADC_InjectedChannel_1                       ((uint8_t)0x14)
#define ADC_InjectedChannel_2                       ((uint8_t)0x18)
#define ADC_InjectedChannel_3                       ((uint8_t)0x1C)
#define ADC_InjectedChannel_4                       ((uint8_t)0x20)
#define IS_ADC_INJECTED_CHANNEL(CHANNEL) (((CHANNEL) == ADC_InjectedChannel_1) || \
        ((CHANNEL) == ADC_InjectedChannel_2) || \
        ((CHANNEL) == ADC_InjectedChannel_3) || \
        ((CHANNEL) == ADC_InjectedChannel_4))


/** @defgroup ADC_analog_watchdog_selection
  */
#define ADC_AnalogWatchdog_SingleRegEnable         ((uint32_t)0x00800200)
#define ADC_AnalogWatchdog_SingleInjecEnable       ((uint32_t)0x00400200)
#define ADC_AnalogWatchdog_SingleRegOrInjecEnable  ((uint32_t)0x00C00200)
#define ADC_AnalogWatchdog_AllRegEnable            ((uint32_t)0x00800000)
#define ADC_AnalogWatchdog_AllInjecEnable          ((uint32_t)0x00400000)
#define ADC_AnalogWatchdog_AllRegAllInjecEnable    ((uint32_t)0x00C00000)
#define ADC_AnalogWatchdog_None                    ((uint32_t)0x00000000)
#define IS_ADC_ANALOG_WATCHDOG(WATCHDOG) (((WATCHDOG) == ADC_AnalogWatchdog_SingleRegEnable) || \
        ((WATCHDOG) == ADC_AnalogWatchdog_SingleInjecEnable) || \
        ((WATCHDOG) == ADC_AnalogWatchdog_SingleRegOrInjecEnable) || \
        ((WATCHDOG) == ADC_AnalogWatchdog_AllRegEnable) || \
        ((WATCHDOG) == ADC_AnalogWatchdog_AllInjecEnable) || \
        ((WATCHDOG) == ADC_AnalogWatchdog_AllRegAllInjecEnable) || \
        ((WATCHDOG) == ADC_AnalogWatchdog_None))


/** @defgroup ADC_interrupts_definition
  */
#define ADC_IT_EOC                                 ((uint16_t)0x0205)
#define ADC_IT_AWD                                 ((uint16_t)0x0106)
#define ADC_IT_JEOC                                ((uint16_t)0x0407)
#define ADC_IT_OVR                                 ((uint16_t)0x201A)
#define IS_ADC_IT(IT) (((IT) == ADC_IT_EOC) || ((IT) == ADC_IT_AWD) || \
                       ((IT) == ADC_IT_JEOC)|| ((IT) == ADC_IT_OVR))


/** @defgroup ADC_flags_definition
  */
#define ADC_FLAG_AWD                               ((uint8_t)0x01)
#define ADC_FLAG_EOC                               ((uint8_t)0x02)
#define ADC_FLAG_JEOC                              ((uint8_t)0x04)
#define ADC_FLAG_JSTRT                             ((uint8_t)0x08)
#define ADC_FLAG_STRT                              ((uint8_t)0x10)
#define ADC_FLAG_OVR                               ((uint8_t)0x20)

#define IS_ADC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint8_t)0xC0) == 0x00) && ((FLAG) != 0x00))
#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_AWD) || \
                               ((FLAG) == ADC_FLAG_EOC) || \
                               ((FLAG) == ADC_FLAG_JEOC) || \
                               ((FLAG)== ADC_FLAG_JSTRT) || \
                               ((FLAG) == ADC_FLAG_STRT) || \
                               ((FLAG)== ADC_FLAG_OVR))


/** @defgroup ADC_thresholds
  */
#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)


/** @defgroup ADC_injected_offset
  */
#define IS_ADC_OFFSET(OFFSET) ((OFFSET) <= 0xFFF)


/** @defgroup ADC_injected_length
  */
#define IS_ADC_INJECTED_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x4))


/** @defgroup ADC_injected_rank
  */
#define IS_ADC_INJECTED_RANK(RANK) (((RANK) >= 0x1) && ((RANK) <= 0x4))


/** @defgroup ADC_regular_length
  */
#define IS_ADC_REGULAR_LENGTH(LENGTH) (((LENGTH) >= 0x1) && ((LENGTH) <= 0x10))


/** @defgroup ADC_regular_rank
  */
#define IS_ADC_REGULAR_RANK(RANK) (((RANK) >= 0x1) && ((RANK) <= 0x10))


/** @defgroup ADC_regular_discontinuous_mode_number
  */
#define IS_ADC_REGULAR_DISC_NUMBER(NUMBER) (((NUMBER) >= 0x1) && ((NUMBER) <= 0x8))



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 ADC 配置设置为默认复位状态的函数 *****/
void ADC_DeInit(void);

/* 初始化和配置功能 *********************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct); // 根据 ADC_InitStruct 中指定的参数初始化 ADCx 外设。
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct); //  ADC_InitStruct 中的每一个参数按缺省值填入
void ADC_CommonInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct);
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 使能或者失能指定的 ADC

/* 模拟看门狗配置功能 ************************************/
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog); // 使能或者失能指定单个/全体，规则/注入组通道上的模拟看门狗
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold, uint16_t LowThreshold); // 设置模拟看门狗的高/低阈值
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel); // 对单个 ADC 通道设置模拟看门狗

/* 温度传感器、Vrefint 和 VBAT 管理功能 ******************/
void ADC_TempSensorVrefintCmd(FunctionalState NewState); // 使能或者失能温度传感器和内部参考电压通道
void ADC_VBATCmd(FunctionalState NewState); // 启用或禁用 VBAT(电压电池)通道。

/* 常规频道配置功能 ***********************************/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime); // 设置指定 ADC 的规则组通道，设置它们的转化顺序和采样时间
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx); // 启用常规通道的选定 ADC 软件启动转换。
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx); // 获取 ADC 软件转换启动状态
void ADC_EOCOnEachRegularChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 在每个常规通道转换上启用或禁用 EOC。
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 启用或禁用 ADC 连续转换模式。
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number); // 对 ADC 规则组通道配置间断模式
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 使能或者失能指定的 ADC 规则组通道的间断模式
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx); // 返回最近一次 ADCx 规则组的转换结果
uint32_t ADC_GetMultiModeConversionValue(void); // 返回所选多模式下最后一次 ADC1、ADC2 和 ADC3 常规转换结果数据。

/* 常规通道 DMA 配置功能 *******************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 使能或者失能指定的 ADC 的 DMA 请求
void ADC_DMARequestAfterLastTransferCmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 在最后一次传输后启用或禁用 ADC DMA 请求(单 ADC 模式)
void ADC_MultiModeDMARequestAfterLastTransferCmd(FunctionalState NewState); // 在多 ADC 模式下最后一次传输后启用或禁用 ADC DMA 请求。

/* 注入通道配置功能 **********************************/
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime); // 设置指定 ADC 的注入组通道，设置它们的转化顺序和采样时间
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length); // 设置注入组通道的转换序列长度
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset); // 设置注入组通道的转换偏移值
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv); // 配置 ADCx 的外部触发启动注入组转换功能
void ADC_ExternalTrigInjectedConvEdgeConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConvEdge); // 为注入通道转换配置 ADCx 外部触发沿。
void ADC_SoftwareStartInjectedConv(ADC_TypeDef* ADCx); // 使能或者失能 ADCx 软件启动注入组转换功能
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx); // 获取选定的 ADC 软件启动注入转换状态。
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 使能或者失能指定 ADC 在规则组转化后自动开始注入组转换
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState); // 使能或者失能指定 ADC 的注入组间断模式
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel); // 返回 ADC 指定注入通道的转换结果

/* 中断和标志管理功能 **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState); // 使能或者失能指定的 ADC 的中断
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG); // 检查制定 ADC 标志位置 1 与否
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG); // 清除 ADCx 的待处理标志位
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT); // 检查指定的 ADC 中断是否发生
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT); // 清除 ADCx 的中断待处理位

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_ADC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
