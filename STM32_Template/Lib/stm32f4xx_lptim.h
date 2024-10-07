/**
  ******************************************************************************
  * 文件:    stm32f4xx_lptim.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 LPTIM 固件库的所有功能原型
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
#ifndef __STM32F4XX_LPTIM_H
#define __STM32F4XX_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup LPTIM
  */
#if defined(STM32F410xx) || defined(STM32F413_423xx)
/* Exported types ------------------------------------------------------------*/
/**
  * 简介:    LPTIM 初始化结构定义
  * 注意:
  */
typedef struct {
    uint32_t LPTIM_ClockSource;          /*!< 选择时钟源。
                                        该参数可以是 @ref LPTIM_Clock_Source 的值 */

    uint32_t LPTIM_Prescaler;            /*!< 指定定时器时钟预分频器。
                                        该参数可以是 @ref LPTIM_Clock_Prescaler 的值 */

    uint32_t LPTIM_Waveform;             /*!< 选择输出形状。
                                        此参数可以是 @ref LPTIM_Waveform_Shape 的值 */

    uint32_t LPTIM_OutputPolarity;       /*!< 指定 LPTIM 输出引脚极性。
                                        此参数可以是 @ref LPTIM_Output_Polarity 的值 */
} LPTIM_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Constants
  */
#define IS_LPTIM_ALL_PERIPH(PERIPH)                  ((PERIPH) == LPTIM1)

/** @defgroup LPTIM_Clock_Source LPTIM Clock Source
  */
#define LPTIM_ClockSource_APBClock_LPosc     ((uint32_t)0x00000000)
#define LPTIM_ClockSource_ULPTIM             ((uint32_t)0x00000001)
#define IS_LPTIM_CLOCK_SOURCE(SOURCE)        (((SOURCE) == LPTIM_ClockSource_ULPTIM) || \
        ((SOURCE) == LPTIM_ClockSource_APBClock_LPosc))

/** @defgroup LPTIM_Clock_Prescaler LPTIM Clock Prescaler
  */
#define LPTIM_Prescaler_DIV1                 ((uint32_t)0x00000000)
#define LPTIM_Prescaler_DIV2                 ((uint32_t)0x00000200)
#define LPTIM_Prescaler_DIV4                 ((uint32_t)0x00000400)
#define LPTIM_Prescaler_DIV8                 ((uint32_t)0x00000600)
#define LPTIM_Prescaler_DIV16                ((uint32_t)0x00000800)
#define LPTIM_Prescaler_DIV32                ((uint32_t)0x00000A00)
#define LPTIM_Prescaler_DIV64                ((uint32_t)0x00000C00)
#define LPTIM_Prescaler_DIV128               ((uint32_t)0x00000E00)
#define IS_LPTIM_CLOCK_PRESCALER(PRESCALER) (((PRESCALER) == LPTIM_Prescaler_DIV1) || \
        ((PRESCALER) == LPTIM_Prescaler_DIV2) || \
        ((PRESCALER) == LPTIM_Prescaler_DIV4) || \
        ((PRESCALER) == LPTIM_Prescaler_DIV8) || \
        ((PRESCALER) == LPTIM_Prescaler_DIV16) || \
        ((PRESCALER) == LPTIM_Prescaler_DIV32) || \
        ((PRESCALER) == LPTIM_Prescaler_DIV64) || \
        ((PRESCALER) == LPTIM_Prescaler_DIV128))

/** @defgroup LPTIM_Waveform_Shape LPTIM Waveform Shape
  */
#define LPTIM_Waveform_PWM_OnePulse          ((uint32_t)0x00000000)
#define LPTIM_Waveform_SetOnce               ((uint32_t)0x00100000)
#define IS_LPTIM_WAVEFORM(WAVE)             (((WAVE) == LPTIM_Waveform_SetOnce) || \
        ((WAVE) == LPTIM_Waveform_PWM_OnePulse))

/** @defgroup LPTIM_Output_Polarity LPTIM Output Polarity
  */
#define LPTIM_OutputPolarity_High            ((uint32_t)0x00000000)
#define LPTIM_OutputPolarity_Low             ((uint32_t)0x00200000)
#define IS_LPTIM_OUTPUT_POLARITY(POLARITY)   (((POLARITY) == LPTIM_OutputPolarity_Low ) || \
        ((POLARITY) == LPTIM_OutputPolarity_High))

/** @defgroup LPTIM_Clock_Polarity LPTIM Clock Polarity
  */
#define LPTIM_ClockPolarity_RisingEdge        ((uint32_t)0x00000000)
#define LPTIM_ClockPolarity_FallingEdge       ((uint32_t)0x00000002)
#define LPTIM_ClockPolarity_BothEdges         ((uint32_t)0x00000004)
#define IS_LPTIM_CLOCK_POLARITY(POLARITY)     (((POLARITY) == LPTIM_ClockPolarity_RisingEdge ) || \
        ((POLARITY) == LPTIM_ClockPolarity_FallingEdge ) || \
        ((POLARITY) == LPTIM_ClockPolarity_BothEdges))

/** @defgroup LPTIM_External_Trigger_Source LPTIM External Trigger Source
  */
#define LPTIM_ExtTRGSource_0          ((uint32_t)0x00000000)
#define LPTIM_ExtTRGSource_1          ((uint32_t)0x00002000)
#define LPTIM_ExtTRGSource_2          ((uint32_t)0x00004000)
#define LPTIM_ExtTRGSource_3          ((uint32_t)0x00006000)
#define LPTIM_ExtTRGSource_4          ((uint32_t)0x00008000)
#define LPTIM_ExtTRGSource_5          ((uint32_t)0x0000A000)
#define LPTIM_ExtTRGSource_6          ((uint32_t)0x0000C000)
#define LPTIM_ExtTRGSource_7          ((uint32_t)0x0000E000)
#define IS_LPTIM_EXT_TRG_SOURCE(TRIG)         (((TRIG) == LPTIM_ExtTRGSource_0) || \
        ((TRIG) == LPTIM_ExtTRGSource_1) || \
        ((TRIG) == LPTIM_ExtTRGSource_2) || \
        ((TRIG) == LPTIM_ExtTRGSource_3) || \
        ((TRIG) == LPTIM_ExtTRGSource_4) || \
        ((TRIG) == LPTIM_ExtTRGSource_5) || \
        ((TRIG) == LPTIM_ExtTRGSource_6) || \
        ((TRIG) == LPTIM_ExtTRGSource_7))

/** @defgroup LPTIM_External_Trigger_Polarity LPTIM External Trigger Polarity
  */
#define LPTIM_ExtTRGPolarity_RisingEdge       ((uint32_t)0x00020000)
#define LPTIM_ExtTRGPolarity_FallingEdge      ((uint32_t)0x00040000)
#define LPTIM_ExtTRGPolarity_BothEdges        ((uint32_t)0x00060000)
#define IS_LPTIM_EXT_TRG_POLARITY(POLAR)      (((POLAR) == LPTIM_ExtTRGPolarity_RisingEdge) || \
        ((POLAR) == LPTIM_ExtTRGPolarity_FallingEdge) || \
        ((POLAR) == LPTIM_ExtTRGPolarity_BothEdges))

/** @defgroup LPTIM_Clock_Sample_Time LPTIM Clock Sample Time
  */
#define LPTIM_ClockSampleTime_DirectTransistion  ((uint32_t)0x00000000)
#define LPTIM_ClockSampleTime_2Transistions      ((uint32_t)0x00000008)
#define LPTIM_ClockSampleTime_4Transistions      ((uint32_t)0x00000010)
#define LPTIM_ClockSampleTime_8Transistions      ((uint32_t)0x00000018)
#define IS_LPTIM_CLOCK_SAMPLE_TIME(SAMPLETIME)   (((SAMPLETIME) == LPTIM_ClockSampleTime_DirectTransistion) || \
        ((SAMPLETIME) == LPTIM_ClockSampleTime_2Transistions) || \
        ((SAMPLETIME) == LPTIM_ClockSampleTime_4Transistions) || \
        ((SAMPLETIME) == LPTIM_ClockSampleTime_8Transistions))

/** @defgroup LPTIM_Trigger_Sample_Time LPTIM Trigger Sample Time
  */
#define LPTIM_TrigSampleTime_DirectTransistion   ((uint32_t)0x00000000)
#define LPTIM_TrigSampleTime_2Transistions       ((uint32_t)0x00000040)
#define LPTIM_TrigSampleTime_4Transistions       ((uint32_t)0x00000080)
#define LPTIM_TrigSampleTime_8Transistions       ((uint32_t)0x000000C0)
#define IS_LPTIM_TRIG_SAMPLE_TIME(SAMPLETIME)    (((SAMPLETIME) == LPTIM_TrigSampleTime_DirectTransistion) || \
        ((SAMPLETIME) == LPTIM_TrigSampleTime_2Transistions) || \
        ((SAMPLETIME) == LPTIM_TrigSampleTime_4Transistions) || \
        ((SAMPLETIME) == LPTIM_TrigSampleTime_8Transistions))

/** @defgroup LPTIM_Operating_Mode LPTIM Operating Mode
  */
#define LPTIM_Mode_Continuous                    ((uint32_t)0x00000004)
#define LPTIM_Mode_Single                        ((uint32_t)0x00000002)
#define IS_LPTIM_MODE(MODE)                      (((MODE) == LPTIM_Mode_Continuous) || \
        ((MODE) == LPTIM_Mode_Single))

/** @defgroup LPTIM_Updating_Register LPTIM 更新寄存器
  */
#define LPTIM_Update_Immediate                  ((uint32_t)0x00000000)
#define LPTIM_Update_EndOfPeriod                ((uint32_t)0x00400000)
#define IS_LPTIM_UPDATE(UPDATE)                 (((UPDATE) == LPTIM_Update_Immediate) || \
        ((UPDATE) == LPTIM_Update_EndOfPeriod))

/** @defgroup LPTIM_Interrupts_Definition LPTIM Interrupts Definition
  */
#define LPTIM_IT_DOWN                            LPTIM_IER_DOWNIE
#define LPTIM_IT_UP                              LPTIM_IER_UPIE
#define LPTIM_IT_ARROK                           LPTIM_IER_ARROKIE
#define LPTIM_IT_CMPOK                           LPTIM_IER_CMPOKIE
#define LPTIM_IT_EXTTRIG                         LPTIM_IER_EXTTRIGIE
#define LPTIM_IT_ARRM                            LPTIM_IER_ARRMIE
#define LPTIM_IT_CMPM                            LPTIM_IER_CMPMIE
#define IS_LPTIM_IT(IT)                          (((IT) == LPTIM_IT_DOWN) || \
        ((IT) == LPTIM_IT_UP) || \
        ((IT) == LPTIM_IT_ARROK) || \
        ((IT) == LPTIM_IT_CMPOK) || \
        ((IT) == LPTIM_IT_EXTTRIG) || \
        ((IT) == LPTIM_IT_ARRM) || \
        ((IT) == LPTIM_IT_CMPM))

#define IS_LPTIM_GET_IT(IT)                      (((IT) == LPTIM_IT_DOWN) || \
        ((IT) == LPTIM_IT_UP) || \
        ((IT) == LPTIM_IT_ARROK) || \
        ((IT) == LPTIM_IT_CMPOK) || \
        ((IT) == LPTIM_IT_EXTTRIG) || \
        ((IT) == LPTIM_IT_ARRM) || \
        ((IT) == LPTIM_IT_CMPM))

/** @defgroup LPTIM_Flag_Definition LPTIM Flag Definition
  */
#define LPTIM_FLAG_DOWN                          LPTIM_ISR_DOWN
#define LPTIM_FLAG_UP                            LPTIM_ISR_UP
#define LPTIM_FLAG_ARROK                         LPTIM_ISR_ARROK
#define LPTIM_FLAG_CMPOK                         LPTIM_ISR_CMPOK
#define LPTIM_FLAG_EXTTRIG                       LPTIM_ISR_EXTTRIG
#define LPTIM_FLAG_ARRM                          LPTIM_ISR_ARRM
#define LPTIM_FLAG_CMPM                          LPTIM_ISR_CMPM
#define IS_LPTIM_GET_FLAG(FLAG)                 (((FLAG) == LPTIM_FLAG_DOWN) || \
        ((FLAG) == LPTIM_FLAG_UP) || \
        ((FLAG) == LPTIM_FLAG_ARROK) || \
        ((FLAG) == LPTIM_FLAG_CMPOK) || \
        ((FLAG) == LPTIM_FLAG_EXTTRIG) || \
        ((FLAG) == LPTIM_FLAG_ARRM) || \
        ((FLAG) == LPTIM_FLAG_CMPM))

/** @defgroup LPTIM_Clear_Flag_Definition LPTIM Clear Flag Definition
  */
#define LPTIM_CLEAR_DOWN                        LPTIM_ICR_DOWNCF
#define LPTIM_CLEAR_UP                          LPTIM_ICR_UPCF
#define LPTIM_CLEAR_ARROK                       LPTIM_ICR_ARROKCF
#define LPTIM_CLEAR_CMPOK                       LPTIM_ICR_CMPOKCF
#define LPTIM_CLEAR_EXTTRIG                     LPTIM_ICR_EXTTRIGCF
#define LPTIM_CLEAR_ARRM                        LPTIM_ICR_ARRMCF
#define LPTIM_CLEAR_CMPM                        LPTIM_ICR_CMPMCF
#define IS_LPTIM_CLEAR_FLAG(CLEARF)              (((CLEARF) == LPTIM_CLEAR_DOWN) || \
        ((CLEARF) == LPTIM_CLEAR_UP) || \
        ((CLEARF) == LPTIM_CLEAR_ARROK) || \
        ((CLEARF) == LPTIM_CLEAR_CMPOK) || \
        ((CLEARF) == LPTIM_CLEAR_EXTTRIG) || \
        ((CLEARF) == LPTIM_CLEAR_ARRM ) || \
        ((CLEARF) == LPTIM_CLEAR_CMPM))

/** @defgroup LPTIM_Autorelaod_Value LPTIM Autorelaod Value
  */
#define IS_LPTIM_AUTORELOAD(AUTORELOAD)         ((AUTORELOAD) <= 0x0000FFFF)

/** @defgroup LPTIM_Compare_Value LPTIM Compare Value
  */
#define IS_LPTIM_COMPARE(COMPARE)               ((COMPARE) <= 0x0000FFFF)

/** @defgroup LPTIM_Option_Register_Definition LPTIM Option Register Definition
  */
#define LPTIM_OP_PAD_AF                          ((uint32_t)0x00000000)
#define LPTIM_OP_PAD_PA4                         LPTIM_OR_OR_0
#define LPTIM_OP_PAD_PB9                         LPTIM_OR_OR_1
#define LPTIM_OP_TIM_DAC                         LPTIM_OR_OR


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* 初始化功能 ***************************************************/
void LPTIM_DeInit(LPTIM_TypeDef* LPTIMx); // 将 LPTIMx 外设寄存器取消初始化为其默认复位值。
void LPTIM_Init(LPTIM_TypeDef* LPTIMx, LPTIM_InitTypeDef* LPTIM_InitStruct); // 根据 LPTIM_InitStruct 中指定的参数初始化 LPTIMx 外设。
void LPTIM_StructInit(LPTIM_InitTypeDef* LPTIM_InitStruct); // 用默认值填充每个 LPTIM_InitStruct 成员。

/* 配置功能 ****************************************************/
void LPTIM_Cmd(LPTIM_TypeDef* LPTIMx, FunctionalState NewState); // 启用或禁用指定的 LPTIM 外设设备。
void LPTIM_SelectClockSource(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_ClockSource); // 选择 LPTIM 计数器的时钟源。
void LPTIM_SelectULPTIMClockPolarity(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_ClockPolarity); // 如果选择了 ULPTIM 输入，则配置用于计数的边沿极性。
void LPTIM_ConfigPrescaler(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Prescaler); // 配置时钟预分频器。
void LPTIM_ConfigExternalTrigger(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_ExtTRGSource, uint32_t LPTIM_ExtTRGPolarity); // 选择计数器的触发源及其极性。
void LPTIM_SelectSoftwareStart(LPTIM_TypeDef* LPTIMx); // 选择计数器的软件启动。
void LPTIM_ConfigTriggerGlitchFilter(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_TrigSampleTime); // 通过确定指定电平的连续样本数来配置触发的数字滤波器，以检测正确的转换。
void LPTIM_ConfigClockGlitchFilter(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_ClockSampleTime); // 通过确定指定级别的连续样本数来配置外部时钟的数字滤波器，以检测正确的转换。
void LPTIM_SelectOperatingMode(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Mode); // 选择操作模式。
void LPTIM_TimoutCmd(LPTIM_TypeDef* LPTIMx, FunctionalState NewState); // 启用或禁用超时功能。
void LPTIM_ConfigWaveform(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Waveform); // 配置波形形状。
void LPTIM_ConfigUpdate(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Update); // 配置自动重载和比较寄存器更新模式。
void LPTIM_SetAutoreloadValue(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Autoreload); // 将传递的参数写入 Autoreload 寄存器。
void LPTIM_SetCompareValue(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Compare); // 将传递的参数写入比较寄存器。
void LPTIM_SelectCounterMode(LPTIM_TypeDef* LPTIMx, FunctionalState NewState); // 启用或禁用计数器模式。 启用计数器模式后，计数器会在 ULPTIM 上的每个有效事件中递增
void LPTIM_SelectEncoderMode(LPTIM_TypeDef* LPTIMx, FunctionalState NewState); // 启用或禁用编码器模式。
void LPTIM_RemapConfig(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_OPTR); // LPTIM 输入 1 重映射。
uint32_t LPTIM_GetCounterValue(LPTIM_TypeDef* LPTIMx); // 获取 LPTIMx 计数器值。
uint32_t LPTIM_GetAutoreloadValue(LPTIM_TypeDef* LPTIMx); // 获取 LPTIMx 自动重载值。
uint32_t LPTIM_GetCompareValue(LPTIM_TypeDef* LPTIMx); // 获取 LPTIMx 比较值。

/* 中断和标志管理功能 **********************************/
void LPTIM_ITConfig(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_IT, FunctionalState NewState); // 启用或禁用指定的 LPTIM 中断。
FlagStatus LPTIM_GetFlagStatus(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_FLAG); // 检查是否设置了指定的 LPTIM 标志。
void LPTIM_ClearFlag(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_CLEARF); // 清除 LPTIMx 的挂起标志。
ITStatus LPTIM_GetITStatus(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_IT); // 检查指定的 LPTIM 中断是否发生。

#endif /* STM32F410xx || STM32F413_423xx */


#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_LPTIM_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
