/**
  ******************************************************************************
  * 文件:    stm32f4xx_dfsdm.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 DFSDM 固件库的所有功能原型
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
#ifndef __STM32F4XX_DFSDM_H
#define __STM32F4XX_DFSDM_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(STM32F412xG) || defined(STM32F413_423xx)
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup DFSDM
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  DFSDM收发器初始化结构定义
  */
typedef struct {
    uint32_t DFSDM_Interface;            /*!< 选择串行接口类型和输入时钟相位。
				                        		     该参数可以是 @ref DFSDM_Interface_Selection 的值 */

    uint32_t DFSDM_Clock;                /*!< 指定串行接口收发器的时钟源。
                                         该参数可以是 @ref DFSDM_Clock_Selection 的值 */

    uint32_t DFSDM_Input;                /*!< 指定串行接口收发器的输入模式。
                                         该参数可以是 @ref DFSDM_Input_Selection 的值 */

    uint32_t DFSDM_Redirection;          /*!< 指定通道输入是否从通道通道 (y+1) 重定向。
                                         该参数可以是 @ref DFSDM_Redirection_Selection 的值 */

    uint32_t DFSDM_PackingMode;          /*!< 指定串行接口收发器的打包模式。
                                         此参数可以是 @ref DFSDM_Pack_Selection 的值 */

    uint32_t DFSDM_DataRightShift;       /*!< 定义最终数据右位移。
                                         此参数可以是 0 到 31 之间的值 */

    uint32_t DFSDM_Offset;               /*!< 设置校准偏移。
                                         此参数可以是 0 到 0xFFFFFF 之间的值 */

    uint32_t DFSDM_CLKAbsenceDetector;   /*!< 启用或禁用时钟缺失检测器。
                                         该参数可以是 @ref DFSDM_Clock_Absence_Detector_state 的值 */

    uint32_t DFSDM_ShortCircuitDetector; /*!< 启用或禁用短路检测器。
                                         该参数可以是 @ref DFSDM_Short_Circuit_Detector_state 的值 */
} DFSDM_TransceiverInitTypeDef;

/**
  * 简介:  DFSDM滤波器模拟参数结构定义
  */
typedef struct {
    uint32_t DFSDM_SincOrder;                  /*!< 设置 Sinc 滤波器顺序。
                                               该参数可以是 @ref DFSDM_Sinc_Order 的值*/

    uint32_t DFSDM_FilterOversamplingRatio;    /*!< 设置 Sinc 滤波器过采样率。
                                               此参数可以是 1 到 1024 之间的值 */

    uint32_t DFSDM_IntegratorOversamplingRatio;/*!< 设置积分器过采样率。
                                               此参数可以是 1 到 256 之间的值 */
} DFSDM_FilterInitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup DFSDM_Interface_Selection
  */
#define DFSDM_Interface_SPI_RisingEdge   ((uint32_t)0x00000000)  /*!<  带有上升沿的 DFSDM SPI 接口以选通数据 */
#define DFSDM_Interface_SPI_FallingEdge  ((uint32_t)0x00000001)  /*!<  DFSDM SPI 接口，带有用于选通数据的下降沿 */
#define DFSDM_Interface_Manchester1      ((uint32_t)0x00000002)  /*!<  DFSDM 曼彻斯特编码输入，上升沿 = 逻辑 0，下降沿 = 逻辑 1 */
#define DFSDM_Interface_Manchester2      ((uint32_t)0x00000003)  /*!<  DFSDM 曼彻斯特编码输入，上升沿 = 逻辑 1，下降沿 = 逻辑 0 */

#define IS_DFSDM_INTERFACE(INTERFACE)    (((INTERFACE) == DFSDM_Interface_SPI_RisingEdge) || \
        ((INTERFACE) == DFSDM_Interface_SPI_FallingEdge) || \
        ((INTERFACE) == DFSDM_Interface_Manchester1)     || \
        ((INTERFACE) == DFSDM_Interface_Manchester2))

/** @defgroup DFSDM_Clock_Selection
  */
#define DFSDM_Clock_External             ((uint32_t)0x00000000)  /*!<  来自外部 DFSDM_CKINy 输入的 DFSDM 时钟 */
#define DFSDM_Clock_Internal             ((uint32_t)0x00000004)  /*!<  DFSDM 时钟来自内部 DFSDM_CKOUT 输出 */
#define DFSDM_Clock_InternalDiv2_Mode1   ((uint32_t)0x00000008)  /*!<  DFSDM 时钟来自内部 DFSDM_CKOUT 输出除以 2，
																	   时钟变化在 DFSDM_CKOUT 输出信号的每个上升沿 */
#define DFSDM_Clock_InternalDiv2_Mode2   ((uint32_t)0x0000000C)  /*!<  DFSDM 时钟来自内部 DFSDM_CKOUT 输出除以 2，
																	   时钟变化发生在 DFSDM_CKOUT 输出信号的每个下降沿 */

#define IS_DFSDM_CLOCK(CLOCK)            (((CLOCK) == DFSDM_Clock_External)          || \
        ((CLOCK) == DFSDM_Clock_Internal)           || \
        ((CLOCK) == DFSDM_Clock_InternalDiv2_Mode1) || \
        ((CLOCK) == DFSDM_Clock_InternalDiv2_Mode2))

/** @defgroup DFSDM_Input_Selection
  */
#define DFSDM_Input_External     ((uint32_t)0x00000000)  /*!<  来自外部 DFSDM_CKINy 输入的 DFSDM 时钟 */
#define DFSDM_Input_ADC          ((uint32_t)0x00001000)  /*!<  DFSDM 时钟来自内部 DFSDM_CKOUT 输出 */
#define DFSDM_Input_Internal     ((uint32_t)0x00002000)  /*!<  DFSDM 时钟来自内部 DFSDM_CKOUT 输出除以 2，
															   时钟变化在 DFSDM_CKOUT 输出信号的每个上升沿 */

#define IS_DFSDM_Input_MODE(INPUT)      (((INPUT) == DFSDM_Input_External) || \
        ((INPUT) == DFSDM_Input_ADC)      || \
        ((INPUT) == DFSDM_Input_Internal))

/** @defgroup DFSDM_Redirection_Selection
  */
#define DFSDM_Redirection_Disabled       ((uint32_t)0x00000000)  /*!< DFSDM 通道串行输入取自同一通道 y 的引脚 */
#define DFSDM_Redirection_Enabled         DFSDM_CHCFGR1_CHINSEL  /*!< DFSDM 通道串行输入取自通道 (y+1) 模 8 的引脚 */

#define IS_DFSDM_Redirection_STATE(STATE)      (((STATE) == DFSDM_Redirection_Disabled) || \
        ((STATE) == DFSDM_Redirection_Enabled))

/** @defgroup DFSDM_Pack_Selection
  */
#define DFSDM_PackingMode_Standard     ((uint32_t)0x00000000)  /*!<  DFSDM_CHDATINyR 寄存器中的 DFSDM 输入数据仅存储在 INDAT0[15:0] */
#define DFSDM_PackingMode_Interleaved  ((uint32_t)0x00004000)  /*!<  DFSDM_CHDATINyR 寄存器中的 DFSDM 输入数据存储为两个样本:
																		- INDAT0[15:0] 中的第一个样本 - 分配给通道 y
																		- 第二个样本 INDAT1[15:0] - 分配给通道 y */
#define DFSDM_PackingMode_Dual         ((uint32_t)0x00008000)  /*!<  DFSDM_CHDATINyR 寄存器中的 DFSDM 输入数据存储为两个样本:
																		- 第一个样本 INDAT0[15:0] - 分配给通道 y
																		- 第二个样本 INDAT1[15:0] - 分配给通道 (y+1) */

#define IS_DFSDM_PACK_MODE(MODE)        (((MODE) == DFSDM_PackingMode_Standard)    || \
        ((MODE) == DFSDM_PackingMode_Interleaved) || \
        ((MODE) == DFSDM_PackingMode_Dual))

/** @defgroup DFSDM_Clock_Absence_Detector_state
  */
#define DFSDM_CLKAbsenceDetector_Enable     DFSDM_CHCFGR1_CKABEN    /*!<  DFSDM 时钟缺失检测器已启用 */
#define DFSDM_CLKAbsenceDetector_Disable    ((uint32_t)0x00000000)  /*!<  DFSDM 时钟缺失检测器已禁用 */

#define IS_DFSDM_CLK_DETECTOR_STATE(STATE)  (((STATE) == DFSDM_CLKAbsenceDetector_Enable) || \
        ((STATE) == DFSDM_CLKAbsenceDetector_Disable))

/** @defgroup DFSDM_Short_Circuit_Detector_state
  */
#define DFSDM_ShortCircuitDetector_Enable   DFSDM_CHCFGR1_SCDEN     /*!<  DFSDM 短路检测器已启用 */
#define DFSDM_ShortCircuitDetector_Disable  ((uint32_t)0x00000000)  /*!<  DFSDM 短路检测器已禁用 */

#define IS_DFSDM_SC_DETECTOR_STATE(STATE)  (((STATE) == DFSDM_ShortCircuitDetector_Enable) || \
        ((STATE) == DFSDM_ShortCircuitDetector_Disable))

/** @defgroup DFSDM_Sinc_Order
  */
#define DFSDM_SincOrder_FastSinc        ((uint32_t)0x00000000)  /*!<  DFSDM Sinc filter order = Fast sinc */
#define DFSDM_SincOrder_Sinc1           ((uint32_t)0x20000000)  /*!<  DFSDM Sinc filter order = 1 */
#define DFSDM_SincOrder_Sinc2           ((uint32_t)0x40000000)  /*!<  DFSDM Sinc filter order = 2 */
#define DFSDM_SincOrder_Sinc3           ((uint32_t)0x60000000)  /*!<  DFSDM Sinc filter order = 3 */
#define DFSDM_SincOrder_Sinc4           ((uint32_t)0x80000000)  /*!<  DFSDM Sinc filter order = 4 */
#define DFSDM_SincOrder_Sinc5           ((uint32_t)0xA0000000)  /*!<  DFSDM Sinc filter order = 5 */

#define IS_DFSDM_SINC_ORDER(ORDER)        (((ORDER) == DFSDM_SincOrder_FastSinc) || \
        ((ORDER) == DFSDM_SincOrder_Sinc1)     || \
        ((ORDER) == DFSDM_SincOrder_Sinc2)     || \
        ((ORDER) == DFSDM_SincOrder_Sinc3)     || \
        ((ORDER) == DFSDM_SincOrder_Sinc4)     || \
        ((ORDER) == DFSDM_SincOrder_Sinc5))

/** @defgroup DFSDM_Break_Signal_Assignment
  */
#define DFSDM_SCDBreak_0                 ((uint32_t)0x00001000)  /*!<  DFSDM Break 0 信号分配给短路检测器 */
#define DFSDM_SCDBreak_1                 ((uint32_t)0x00002000)  /*!<  DFSDM Break 1 信号分配给短路检测器 */
#define DFSDM_SCDBreak_2                 ((uint32_t)0x00004000)  /*!<  DFSDM Break 2 信号分配给短路检测器 */
#define DFSDM_SCDBreak_3                 ((uint32_t)0x00008000)  /*!<  DFSDM Break 3 信号分配给短路检测器 */

#define IS_DFSDM_SCD_BREAK_SIGNAL(RANK)    (((RANK) == DFSDM_SCDBreak_0) || \
        ((RANK) == DFSDM_SCDBreak_1)  || \
        ((RANK) == DFSDM_SCDBreak_2)  || \
        ((RANK) == DFSDM_SCDBreak_3))

/** @defgroup DFSDM_AWD_Sinc_Order
  */
#define DFSDM_AWDSincOrder_Fast            ((uint32_t)0x00000000)  /*!<  DFSDM Fast sinc filter */
#define DFSDM_AWDSincOrder_Sinc1           ((uint32_t)0x00400000)  /*!<  DFSDM sinc1 filter */
#define DFSDM_AWDSincOrder_Sinc2           ((uint32_t)0x00800000)  /*!<  DFSDM sinc2 filter */
#define DFSDM_AWDSincOrder_Sinc3           ((uint32_t)0x00C00000)  /*!<  DFSDM sinc3 filter */

#define IS_DFSDM_AWD_SINC_ORDER(ORDER)    (((ORDER) == DFSDM_AWDSincOrder_Fast)  || \
        ((ORDER) == DFSDM_AWDSincOrder_Sinc1) || \
        ((ORDER) == DFSDM_AWDSincOrder_Sinc2) || \
        ((ORDER) == DFSDM_AWDSincOrder_Sinc3))

/** @defgroup DFSDM_AWD_CHANNEL
  */
#define DFSDM_AWDChannel0               ((uint32_t)0x00010000)  /*!<  DFSDM AWDx 保护通道 0 */
#define DFSDM_AWDChannel1               ((uint32_t)0x00020000)  /*!<  DFSDM AWDx 保护通道 1 */
#define DFSDM_AWDChannel2               ((uint32_t)0x00040000)  /*!<  DFSDM AWDx 保护通道 2 */
#define DFSDM_AWDChannel3               ((uint32_t)0x00080000)  /*!<  DFSDM AWDx 保护通道 3 */
#define DFSDM_AWDChannel4               ((uint32_t)0x00100000)  /*!<  DFSDM AWDx 保护通道 4 */
#define DFSDM_AWDChannel5               ((uint32_t)0x00200000)  /*!<  DFSDM AWDx 保护通道 5 */
#define DFSDM_AWDChannel6               ((uint32_t)0x00400000)  /*!<  DFSDM AWDx 保护通道 6 */
#define DFSDM_AWDChannel7               ((uint32_t)0x00800000)  /*!<  DFSDM AWDx 保护通道 7 */

#define IS_DFSDM_AWD_CHANNEL(CHANNEL)    (((CHANNEL) == DFSDM_AWDChannel0) || \
        ((CHANNEL) == DFSDM_AWDChannel1) || \
        ((CHANNEL) == DFSDM_AWDChannel2) || \
        ((CHANNEL) == DFSDM_AWDChannel3) || \
        ((CHANNEL) == DFSDM_AWDChannel4) || \
        ((CHANNEL) == DFSDM_AWDChannel5) || \
        ((CHANNEL) == DFSDM_AWDChannel6) || \
        ((CHANNEL) == DFSDM_AWDChannel7))

/** @defgroup DFSDM_Threshold_Selection
  */
#define DFSDM_Threshold_Low               ((uint8_t)0x00)  /*!<  DFSDM 低阈值 */
#define DFSDM_Threshold_High              ((uint8_t)0x08)  /*!<  DFSDM 高阈值 */

#define IS_DFSDM_Threshold(THR)          (((THR) == DFSDM_Threshold_Low) || \
        ((THR) == DFSDM_Threshold_High))

/** @defgroup DFSDM_AWD_Fast_Mode_Selection
  */
#define DFSDM_AWDFastMode_Disable         ((uint32_t)0x00000000)  /*!<  AWD 的 DFSDM 快速模式已禁用 */
#define DFSDM_AWDFastMode_Enable          ((uint32_t)0x40000000)  /*!<  AWD 的 DFSDM 快速模式已启用 */

#define IS_DFSDM_AWD_MODE(MODE)          (((MODE) == DFSDM_AWDFastMode_Disable) || \
        ((MODE) == DFSDM_AWDFastMode_Enable))

/** @defgroup DFSDM_Clock_Output_Source_Selection
  */
#define DFSDM_ClkOutSource_SysClock        ((uint32_t)0x00000000)  /*!<  DFSDM 输出时钟源来自系统时钟 */
#define DFSDM_ClkOutSource_AudioClock      DFSDM_CHCFGR1_CKOUTSRC  /*!<  DFSDM 输出时钟源来自音频时钟 */

#define IS_DFSDM_CLOCK_OUT_SOURCE(SRC)    (((SRC) == DFSDM_ClkOutSource_SysClock) || \
        ((SRC) == DFSDM_ClkOutSource_AudioClock))

/** @defgroup DFSDM_Conversion_Mode
  */
#define DFSDM_DMAConversionMode_Regular     ((uint32_t)0x00000010)  /*!<  DFSDM 常规模式 */
#define DFSDM_DMAConversionMode_Injected    ((uint32_t)0x00000000)  /*!<  DFSDM 注入模式 */

#define IS_DFSDM_CONVERSION_MODE(MODE)    (((MODE) == DFSDM_DMAConversionMode_Regular) || \
        ((MODE) == DFSDM_DMAConversionMode_Injected))

/** @defgroup DFSDM_Extremes_Channel_Selection
  */
#define DFSDM_ExtremChannel0              ((uint32_t)0x00000100)  /*!<  DFSDM Extreme 探测器保护通道 0 */
#define DFSDM_ExtremChannel1              ((uint32_t)0x00000200)  /*!<  DFSDM Extreme 探测器保护通道 1 */
#define DFSDM_ExtremChannel2              ((uint32_t)0x00000400)  /*!<  DFSDM Extreme 探测器保护通道 2 */
#define DFSDM_ExtremChannel3              ((uint32_t)0x00000800)  /*!<  DFSDM Extreme 探测器保护通道 3 */
#define DFSDM_ExtremChannel4              ((uint32_t)0x00001000)  /*!<  DFSDM Extreme 探测器保护通道 4 */
#define DFSDM_ExtremChannel5              ((uint32_t)0x00002000)  /*!<  DFSDM Extreme 探测器保护通道 5 */
#define DFSDM_ExtremChannel6              ((uint32_t)0x00004000)  /*!<  DFSDM Extreme 探测器保护通道 6 */
#define DFSDM_ExtremChannel7              ((uint32_t)0x00008000)  /*!<  DFSDM Extreme 探测器保护通道 7 */

#define IS_DFSDM_EXTREM_CHANNEL(CHANNEL) (((CHANNEL) == DFSDM_ExtremChannel0) || \
        ((CHANNEL) == DFSDM_ExtremChannel1) || \
        ((CHANNEL) == DFSDM_ExtremChannel2) || \
        ((CHANNEL) == DFSDM_ExtremChannel3) || \
        ((CHANNEL) == DFSDM_ExtremChannel4) || \
        ((CHANNEL) == DFSDM_ExtremChannel5) || \
        ((CHANNEL) == DFSDM_ExtremChannel6) || \
        ((CHANNEL) == DFSDM_ExtremChannel7))

/** @defgroup DFSDM_Injected_Channel_Selection
  */
#define DFSDM_InjectedChannel0            ((uint32_t)0x00000001)  /*!<  DFSDM 通道 0 被选为注入通道 */
#define DFSDM_InjectedChannel1            ((uint32_t)0x00000002)  /*!<  DFSDM 通道 1 被选为注入通道 */
#define DFSDM_InjectedChannel2            ((uint32_t)0x00000004)  /*!<  DFSDM 通道 2 被选为注入通道 */
#define DFSDM_InjectedChannel3            ((uint32_t)0x00000008)  /*!<  DFSDM 通道 3 被选为注入通道 */
#define DFSDM_InjectedChannel4            ((uint32_t)0x00000010)  /*!<  DFSDM 通道 4 被选为注入通道 */
#define DFSDM_InjectedChannel5            ((uint32_t)0x00000020)  /*!<  DFSDM 通道 5 被选为注入通道 */
#define DFSDM_InjectedChannel6            ((uint32_t)0x00000040)  /*!<  DFSDM 通道 6 被选为注入通道 */
#define DFSDM_InjectedChannel7            ((uint32_t)0x00000080)  /*!<  DFSDM 通道 7 被选为注入通道 */

#define IS_DFSDM_INJECT_CHANNEL(CHANNEL) (((CHANNEL) == DFSDM_InjectedChannel0) || \
        ((CHANNEL) == DFSDM_InjectedChannel1) || \
        ((CHANNEL) == DFSDM_InjectedChannel2) || \
        ((CHANNEL) == DFSDM_InjectedChannel3) || \
        ((CHANNEL) == DFSDM_InjectedChannel4) || \
        ((CHANNEL) == DFSDM_InjectedChannel5) || \
        ((CHANNEL) == DFSDM_InjectedChannel6) || \
        ((CHANNEL) == DFSDM_InjectedChannel7))

/** @defgroup DFSDM_Regular_Channel_Selection
  */
#define DFSDM_RegularChannel0             ((uint32_t)0x00000000)  /*!<  DFSDM 通道 0 被选为常规通道 */
#define DFSDM_RegularChannel1             ((uint32_t)0x01000000)  /*!<  DFSDM 通道 1 被选为常规通道 */
#define DFSDM_RegularChannel2             ((uint32_t)0x02000000)  /*!<  DFSDM 通道 2 被选为常规通道 */
#define DFSDM_RegularChannel3             ((uint32_t)0x03000000)  /*!<  DFSDM 通道 3 被选为常规通道 */
#define DFSDM_RegularChannel4             ((uint32_t)0x04000000)  /*!<  DFSDM 通道 4 被选为常规通道 */
#define DFSDM_RegularChannel5             ((uint32_t)0x05000000)  /*!<  DFSDM 通道 5 被选为常规通道 */
#define DFSDM_RegularChannel6             ((uint32_t)0x06000000)  /*!<  DFSDM 通道 6 被选为常规通道 */
#define DFSDM_RegularChannel7             ((uint32_t)0x07000000)  /*!<  DFSDM 通道 7 被选为常规通道 */

#define IS_DFSDM_REGULAR_CHANNEL(CHANNEL) (((CHANNEL) == DFSDM_RegularChannel0) || \
        ((CHANNEL) == DFSDM_RegularChannel1) || \
        ((CHANNEL) == DFSDM_RegularChannel2) || \
        ((CHANNEL) == DFSDM_RegularChannel3) || \
        ((CHANNEL) == DFSDM_RegularChannel4) || \
        ((CHANNEL) == DFSDM_RegularChannel5) || \
        ((CHANNEL) == DFSDM_RegularChannel6) || \
        ((CHANNEL) == DFSDM_RegularChannel7))

/** @defgroup DFSDM_Injected_Trigger_signal
  */
#define DFSDM_Trigger_TIM1_TRGO          ((uint32_t)0x00000000)  /*!<  DFSDM 内部触发 0 */
#define DFSDM_Trigger_TIM1_TRGO2         ((uint32_t)0x00000100)  /*!<  DFSDM 内部触发 1 */
#define DFSDM_Trigger_TIM8_TRGO          ((uint32_t)0x00000200)  /*!<  DFSDM 内部触发 2 */
#define DFSDM_Trigger_TIM8_TRGO2         ((uint32_t)0x00000300)  /*!<  DFSDM 内部触发 3 */
#define DFSDM_Trigger_TIM3_TRGO          ((uint32_t)0x00000300)  /*!<  DFSDM 内部触发 4 */
#define DFSDM_Trigger_TIM4_TRGO          ((uint32_t)0x00000400)  /*!<  DFSDM 内部触发 5 */
#define DFSDM_Trigger_TIM16_OC1          ((uint32_t)0x00000400)  /*!<  DFSDM 内部触发 6 */
#define DFSDM_Trigger_TIM6_TRGO          ((uint32_t)0x00000500)  /*!<  DFSDM 内部触发 7 */
#define DFSDM_Trigger_TIM7_TRGO          ((uint32_t)0x00000500)  /*!<  DFSDM 内部触发 8 */
#define DFSDM_Trigger_EXTI11             ((uint32_t)0x00000600)  /*!<  DFSDM 外部触发 0 */
#define DFSDM_Trigger_EXTI15             ((uint32_t)0x00000700)  /*!<  DFSDM 外部触发 1 */

#define IS_DFSDM0_INJ_TRIGGER(TRIG)      (((TRIG) == DFSDM_Trigger_TIM1_TRGO)  || \
        ((TRIG) == DFSDM_Trigger_TIM1_TRGO2) || \
        ((TRIG) == DFSDM_Trigger_TIM8_TRGO)  || \
        ((TRIG) == DFSDM_Trigger_TIM8_TRGO2) || \
        ((TRIG) == DFSDM_Trigger_TIM4_TRGO)  || \
        ((TRIG) == DFSDM_Trigger_TIM6_TRGO)  || \
        ((TRIG) == DFSDM_Trigger_TIM7_TRGO)  || \
        ((TRIG) == DFSDM_Trigger_EXTI15)     || \
        ((TRIG) == DFSDM_Trigger_TIM3_TRGO)  || \
        ((TRIG) == DFSDM_Trigger_TIM16_OC1)  || \
        ((TRIG) == DFSDM_Trigger_EXTI11))

#define IS_DFSDM1_INJ_TRIGGER(TRIG)      IS_DFSDM0_INJ_TRIGGER(TRIG)

/** @defgroup DFSDM_Trigger_Edge_selection
  */
#define DFSDM_TriggerEdge_Disabled        ((uint32_t)0x00000000)  /*!<  DFSDM 触发检测已禁用 */
#define DFSDM_TriggerEdge_Rising          ((uint32_t)0x00002000)  /*!<  DFSDM 每个上升沿都请求启动注入转换 */
#define DFSDM_TriggerEdge_Falling         ((uint32_t)0x00004000)  /*!<  DFSDM 每个下降沿都请求启动注入转换 */
#define DFSDM_TriggerEdge_BothEdges       ((uint32_t)0x00006000)  /*!<  DFSDM 两个边缘都请求启动注入转换 */

#define IS_DFSDM_TRIGGER_EDGE(EDGE)      (((EDGE) == DFSDM_TriggerEdge_Disabled) || \
        ((EDGE) == DFSDM_TriggerEdge_Rising) || \
        ((EDGE) == DFSDM_TriggerEdge_Falling) || \
        ((EDGE) == DFSDM_TriggerEdge_BothEdges))

/** @defgroup DFSDM_Injected_Conversion_Mode_Selection
  */
#define DFSDM_InjectConvMode_Single        ((uint32_t)0x00000000)  /*!<  DFSDM 触发检测已禁用 */
#define DFSDM_InjectConvMode_Scan          ((uint32_t)0x00000010)  /*!<  DFSDM 每个上升沿都请求启动注入转换 */

#define IS_DFSDM_INJ_CONV_MODE(MODE)      (((MODE) == DFSDM_InjectConvMode_Single) || \
        ((MODE) == DFSDM_InjectConvMode_Scan))

/** @defgroup DFSDM_Interrupts_Definition
  */
#define DFSDM_IT_JEOC                            DFSDM_FLTCR2_JEOCIE
#define DFSDM_IT_REOC                            DFSDM_FLTCR2_REOCIE
#define DFSDM_IT_JOVR                            DFSDM_FLTCR2_JOVRIE
#define DFSDM_IT_ROVR                            DFSDM_FLTCR2_ROVRIE
#define DFSDM_IT_AWD                             DFSDM_FLTCR2_AWDIE
#define DFSDM_IT_SCD                             DFSDM_FLTCR2_SCDIE
#define DFSDM_IT_CKAB                            DFSDM_FLTCR2_CKABIE

#define IS_DFSDM_IT(IT)                         (((IT) == DFSDM_IT_JEOC) || \
        ((IT) == DFSDM_IT_REOC) || \
        ((IT) == DFSDM_IT_JOVR) || \
        ((IT) == DFSDM_IT_ROVR) || \
        ((IT) == DFSDM_IT_AWD)  || \
        ((IT) == DFSDM_IT_SCD)  || \
        ((IT) == DFSDM_IT_CKAB))

/** @defgroup DFSDM_Flag_Definition
  */
#define DFSDM_FLAG_JEOC                          DFSDM_FLTISR_JEOCF
#define DFSDM_FLAG_REOC                          DFSDM_FLTISR_REOCF
#define DFSDM_FLAG_JOVR                          DFSDM_FLTISR_JOVRF
#define DFSDM_FLAG_ROVR                          DFSDM_FLTISR_ROVRF
#define DFSDM_FLAG_AWD                           DFSDM_FLTISR_AWDF
#define DFSDM_FLAG_JCIP                          DFSDM_FLTISR_JCIP
#define DFSDM_FLAG_RCIP                          DFSDM_FLTISR_RCIP

#define IS_DFSDM_FLAG(FLAG)                     (((FLAG) == DFSDM_FLAG_JEOC) || \
        ((FLAG) == DFSDM_FLAG_REOC) || \
        ((FLAG) == DFSDM_FLAG_JOVR) || \
        ((FLAG) == DFSDM_FLAG_ROVR) || \
        ((FLAG) == DFSDM_FLAG_AWD)  || \
        ((FLAG) == DFSDM_FLAG_JCIP) || \
        ((FLAG) == DFSDM_FLAG_RCIP))

/** @defgroup DFSDM_Clock_Absence_Flag_Definition
  */
#define DFSDM_FLAG_CLKAbsence_Channel0           ((uint32_t)0x00010000)
#define DFSDM_FLAG_CLKAbsence_Channel1           ((uint32_t)0x00020000)
#define DFSDM_FLAG_CLKAbsence_Channel2           ((uint32_t)0x00040000)
#define DFSDM_FLAG_CLKAbsence_Channel3           ((uint32_t)0x00080000)
#define DFSDM_FLAG_CLKAbsence_Channel4           ((uint32_t)0x00100000)
#define DFSDM_FLAG_CLKAbsence_Channel5           ((uint32_t)0x00200000)
#define DFSDM_FLAG_CLKAbsence_Channel6           ((uint32_t)0x00400000)
#define DFSDM_FLAG_CLKAbsence_Channel7           ((uint32_t)0x00800000)

#define IS_DFSDM_CLK_ABS_FLAG(FLAG)             (((FLAG) == DFSDM_FLAG_CLKAbsence_Channel0) || \
        ((FLAG) == DFSDM_FLAG_CLKAbsence_Channel1) || \
        ((FLAG) == DFSDM_FLAG_CLKAbsence_Channel2) || \
        ((FLAG) == DFSDM_FLAG_CLKAbsence_Channel3) || \
        ((FLAG) == DFSDM_FLAG_CLKAbsence_Channel4) || \
        ((FLAG) == DFSDM_FLAG_CLKAbsence_Channel5) || \
        ((FLAG) == DFSDM_FLAG_CLKAbsence_Channel6) || \
        ((FLAG) == DFSDM_FLAG_CLKAbsence_Channel7))

/** @defgroup DFSDM_SCD_Flag_Definition
  */
#define DFSDM_FLAG_SCD_Channel0                  ((uint32_t)0x01000000)
#define DFSDM_FLAG_SCD_Channel1                  ((uint32_t)0x02000000)
#define DFSDM_FLAG_SCD_Channel2                  ((uint32_t)0x04000000)
#define DFSDM_FLAG_SCD_Channel3                  ((uint32_t)0x08000000)
#define DFSDM_FLAG_SCD_Channel4                  ((uint32_t)0x10000000)
#define DFSDM_FLAG_SCD_Channel5                  ((uint32_t)0x20000000)
#define DFSDM_FLAG_SCD_Channel6                  ((uint32_t)0x40000000)
#define DFSDM_FLAG_SCD_Channel7                  ((uint32_t)0x80000000)

#define IS_DFSDM_SCD_FLAG(FLAG)                 (((FLAG) == DFSDM_FLAG_SCD_Channel0) || \
        ((FLAG) == DFSDM_FLAG_SCD_Channel1) || \
        ((FLAG) == DFSDM_FLAG_SCD_Channel2) || \
        ((FLAG) == DFSDM_FLAG_SCD_Channel3) || \
        ((FLAG) == DFSDM_FLAG_SCD_Channel4) || \
        ((FLAG) == DFSDM_FLAG_SCD_Channel5) || \
        ((FLAG) == DFSDM_FLAG_SCD_Channel6) || \
        ((FLAG) == DFSDM_FLAG_SCD_Channel7))

/** @defgroup DFSDM_Clear_Flag_Definition
  */
#define DFSDM_CLEARF_JOVR                          DFSDM_FLTICR_CLRJOVRF
#define DFSDM_CLEARF_ROVR                          DFSDM_FLTICR_CLRROVRF

#define IS_DFSDM_CLEAR_FLAG(FLAG)                (((FLAG) == DFSDM_CLEARF_JOVR) || \
        ((FLAG) == DFSDM_CLEARF_ROVR))

/** @defgroup DFSDM_Clear_ClockAbs_Flag_Definition
  */
#define DFSDM_CLEARF_CLKAbsence_Channel0           ((uint32_t)0x00010000)
#define DFSDM_CLEARF_CLKAbsence_Channel1           ((uint32_t)0x00020000)
#define DFSDM_CLEARF_CLKAbsence_Channel2           ((uint32_t)0x00040000)
#define DFSDM_CLEARF_CLKAbsence_Channel3           ((uint32_t)0x00080000)
#define DFSDM_CLEARF_CLKAbsence_Channel4           ((uint32_t)0x00100000)
#define DFSDM_CLEARF_CLKAbsence_Channel5           ((uint32_t)0x00200000)
#define DFSDM_CLEARF_CLKAbsence_Channel6           ((uint32_t)0x00400000)
#define DFSDM_CLEARF_CLKAbsence_Channel7           ((uint32_t)0x00800000)

#define IS_DFSDM_CLK_ABS_CLEARF(FLAG)           (((FLAG) == DFSDM_CLEARF_CLKAbsence_Channel0) || \
        ((FLAG) == DFSDM_CLEARF_CLKAbsence_Channel1) || \
        ((FLAG) == DFSDM_CLEARF_CLKAbsence_Channel2) || \
        ((FLAG) == DFSDM_CLEARF_CLKAbsence_Channel3) || \
        ((FLAG) == DFSDM_CLEARF_CLKAbsence_Channel4) || \
        ((FLAG) == DFSDM_CLEARF_CLKAbsence_Channel5) || \
        ((FLAG) == DFSDM_CLEARF_CLKAbsence_Channel6) || \
        ((FLAG) == DFSDM_CLEARF_CLKAbsence_Channel7))

/** @defgroup DFSDM_Clear_Short_Circuit_Flag_Definition
  */
#define DFSDM_CLEARF_SCD_Channel0           ((uint32_t)0x01000000)
#define DFSDM_CLEARF_SCD_Channel1           ((uint32_t)0x02000000)
#define DFSDM_CLEARF_SCD_Channel2           ((uint32_t)0x04000000)
#define DFSDM_CLEARF_SCD_Channel3           ((uint32_t)0x08000000)
#define DFSDM_CLEARF_SCD_Channel4           ((uint32_t)0x10000000)
#define DFSDM_CLEARF_SCD_Channel5           ((uint32_t)0x20000000)
#define DFSDM_CLEARF_SCD_Channel6           ((uint32_t)0x40000000)
#define DFSDM_CLEARF_SCD_Channel7           ((uint32_t)0x80000000)

#define IS_DFSDM_SCD_CHANNEL_FLAG(FLAG)         (((FLAG) == DFSDM_CLEARF_SCD_Channel0) || \
        ((FLAG) == DFSDM_CLEARF_SCD_Channel1) || \
        ((FLAG) == DFSDM_CLEARF_SCD_Channel2) || \
        ((FLAG) == DFSDM_CLEARF_SCD_Channel3) || \
        ((FLAG) == DFSDM_CLEARF_SCD_Channel4) || \
        ((FLAG) == DFSDM_CLEARF_SCD_Channel5) || \
        ((FLAG) == DFSDM_CLEARF_SCD_Channel6) || \
        ((FLAG) == DFSDM_CLEARF_SCD_Channel7))

/** @defgroup DFSDM_Clock_Absence_Interrupt_Definition
  */
#define DFSDM_IT_CLKAbsence_Channel0           ((uint32_t)0x00010000)
#define DFSDM_IT_CLKAbsence_Channel1           ((uint32_t)0x00020000)
#define DFSDM_IT_CLKAbsence_Channel2           ((uint32_t)0x00040000)
#define DFSDM_IT_CLKAbsence_Channel3           ((uint32_t)0x00080000)
#define DFSDM_IT_CLKAbsence_Channel4           ((uint32_t)0x00100000)
#define DFSDM_IT_CLKAbsence_Channel5           ((uint32_t)0x00200000)
#define DFSDM_IT_CLKAbsence_Channel6           ((uint32_t)0x00400000)
#define DFSDM_IT_CLKAbsence_Channel7           ((uint32_t)0x00800000)

#define IS_DFSDM_CLK_ABS_IT(IT)               (((IT) == DFSDM_IT_CLKAbsence_Channel0) || \
        ((IT) == DFSDM_IT_CLKAbsence_Channel1) || \
        ((IT) == DFSDM_IT_CLKAbsence_Channel2) || \
        ((IT) == DFSDM_IT_CLKAbsence_Channel3) || \
        ((IT) == DFSDM_IT_CLKAbsence_Channel4) || \
        ((IT) == DFSDM_IT_CLKAbsence_Channel5) || \
        ((IT) == DFSDM_IT_CLKAbsence_Channel6) || \
        ((IT) == DFSDM_IT_CLKAbsence_Channel7))

/** @defgroup DFSDM_SCD_Interrupt_Definition
  */
#define DFSDM_IT_SCD_Channel0                  ((uint32_t)0x01000000)
#define DFSDM_IT_SCD_Channel1                  ((uint32_t)0x02000000)
#define DFSDM_IT_SCD_Channel2                  ((uint32_t)0x04000000)
#define DFSDM_IT_SCD_Channel3                  ((uint32_t)0x08000000)
#define DFSDM_IT_SCD_Channel4                  ((uint32_t)0x10000000)
#define DFSDM_IT_SCD_Channel5                  ((uint32_t)0x20000000)
#define DFSDM_IT_SCD_Channel6                  ((uint32_t)0x40000000)
#define DFSDM_IT_SCD_Channel7                  ((uint32_t)0x80000000)

#define IS_DFSDM_SCD_IT(IT)                   (((IT) == DFSDM_IT_SCD_Channel0) || \
        ((IT) == DFSDM_IT_SCD_Channel1) || \
        ((IT) == DFSDM_IT_SCD_Channel2) || \
        ((IT) == DFSDM_IT_SCD_Channel3) || \
        ((IT) == DFSDM_IT_SCD_Channel4) || \
        ((IT) == DFSDM_IT_SCD_Channel5) || \
        ((IT) == DFSDM_IT_SCD_Channel6) || \
        ((IT) == DFSDM_IT_SCD_Channel7))
#define IS_DFSDM_DATA_RIGHT_BIT_SHIFT(SHIFT)  ((SHIFT) < 0x20 )

#define IS_DFSDM_OFFSET(OFFSET)               ((OFFSET) < 0x01000000 )

#if defined(STM32F413_423xx)
#define IS_DFSDM_ALL_CHANNEL(CHANNEL)   (((CHANNEL) == DFSDM1_Channel0) || \
        ((CHANNEL) == DFSDM1_Channel1) || \
        ((CHANNEL) == DFSDM1_Channel2) || \
        ((CHANNEL) == DFSDM1_Channel3) || \
        ((CHANNEL) == DFSDM2_Channel0) || \
        ((CHANNEL) == DFSDM2_Channel1) || \
        ((CHANNEL) == DFSDM2_Channel2) || \
        ((CHANNEL) == DFSDM2_Channel3) || \
        ((CHANNEL) == DFSDM2_Channel4) || \
        ((CHANNEL) == DFSDM2_Channel5) || \
        ((CHANNEL) == DFSDM2_Channel6) || \
        ((CHANNEL) == DFSDM2_Channel7))

#define IS_DFSDM_ALL_FILTER(FILTER)     (((FILTER) == DFSDM1_0) || \
        ((FILTER) == DFSDM1_1) || \
        ((FILTER) == DFSDM2_0) || \
        ((FILTER) == DFSDM2_1) || \
        ((FILTER) == DFSDM2_2) || \
        ((FILTER) == DFSDM2_3))

#define IS_DFSDM_SYNC_FILTER(FILTER)    (((FILTER) == DFSDM1_0) || \
        ((FILTER) == DFSDM1_1) || \
        ((FILTER) == DFSDM2_0) || \
        ((FILTER) == DFSDM2_1) || \
        ((FILTER) == DFSDM2_2) || \
        ((FILTER) == DFSDM2_3))
#else
#define IS_DFSDM_ALL_CHANNEL(CHANNEL)   (((CHANNEL) == DFSDM1_Channel0) || \
        ((CHANNEL) == DFSDM1_Channel1) || \
        ((CHANNEL) == DFSDM1_Channel2) || \
        ((CHANNEL) == DFSDM1_Channel3))

#define IS_DFSDM_ALL_FILTER(FILTER)     (((FILTER) == DFSDM1_0) || \
        ((FILTER) == DFSDM1_1))

#define IS_DFSDM_SYNC_FILTER(FILTER)    (((FILTER) == DFSDM1_0) || \
        ((FILTER) == DFSDM1_1))
#endif /* STM32F413_423xx */




#define IS_DFSDM_SINC_OVRSMPL_RATIO(RATIO)  (((RATIO) < 0x401) && ((RATIO) >= 0x001))

#define IS_DFSDM_INTG_OVRSMPL_RATIO(RATIO)  (((RATIO) < 0x101 ) && ((RATIO) >= 0x001))

#define IS_DFSDM_CLOCK_OUT_DIVIDER(DIVIDER) ((DIVIDER) < 0x101 )

#define IS_DFSDM_CSD_THRESHOLD_VALUE(VALUE) ((VALUE) < 256)

#define IS_DFSDM_AWD_OVRSMPL_RATIO(RATIO)   ((RATIO) < 33) && ((RATIO) >= 0x001)

#define IS_DFSDM_HIGH_THRESHOLD(VALUE)      ((VALUE) < 0x1000000)
#define IS_DFSDM_LOW_THRESHOLD(VALUE)       ((VALUE) < 0x1000000)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* 初始化功能 ***************************************************/
void DFSDM_DeInit(void); // 将DFSDM外围寄存器取消初始化为其默认重置值。
void DFSDM_TransceiverInit(DFSDM_Channel_TypeDef* DFSDM_Channelx, DFSDM_TransceiverInitTypeDef* DFSDM_TransceiverInitStruct); // 根据DFSDM_TranceiverInit中的指定参数初始化DFSDM串行通道收发器。
void DFSDM_TransceiverStructInit(DFSDM_TransceiverInitTypeDef* DFSDM_TransceiverInitStruct); // 使用默认值填充每个DFSDM_TranceiverInitStruct成员。
void DFSDM_FilterInit(DFSDM_Filter_TypeDef* DFSDMx, DFSDM_FilterInitTypeDef* DFSDM_FilterInitStruct); // 根据DFSDM_FilterInitStruct中的指定参数初始化DFSDMx筛选器。
void DFSDM_FilterStructInit(DFSDM_FilterInitTypeDef* DFSDM_FilterInitStruct); // 用默认值填充每个DFSDM_FilterInitStruct成员。

/* 配置功能 ****************************************************/
#if defined(STM32F412xG)
void DFSDM_Command(FunctionalState NewState); // 启用或停用 DFSDM外设。
#else /* STM32F413_423xx */
void DFSDM_Cmd(uint32_t Instance, FunctionalState NewState); // 启用或禁用 DFSDM 外设.
#endif /* STM32F412xG */
void DFSDM_ChannelCmd(DFSDM_Channel_TypeDef* DFSDM_Channelx, FunctionalState NewState); // 启用或禁用指定的DFSDM串行通道x。
void DFSDM_FilterCmd(DFSDM_Filter_TypeDef* DFSDMx, FunctionalState NewState); // 启用或禁用指定的 DFSDMx 过滤器。
#if defined(STM32F412xG)
void DFSDM_ConfigClkOutputDivider(uint32_t DFSDM_ClkOutDivision); // 配置输出串行时钟分频器。
void DFSDM_ConfigClkOutputSource(uint32_t DFSDM_ClkOutSource); // 配置输出串行时钟源.
#else
void DFSDM_ConfigClkOutputDivider(uint32_t Instance, uint32_t DFSDM_ClkOutDivision); // 配置输出串行时钟分频器。
void DFSDM_ConfigClkOutputSource(uint32_t Instance, uint32_t DFSDM_ClkOutSource); // 配置输出串行时钟源.
#endif /* STM32F412xG */
void DFSDM_SelectInjectedConversionMode(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_InjectConvMode); // 为选定的DFSDMx选择注入转换模式。
void DFSDM_SelectInjectedChannel(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_InjectedChannelx);
void DFSDM_SelectRegularChannel(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_RegularChannelx); // 为选定的DFSDMx选择常规频道。
void DFSDM_StartSoftwareInjectedConversion(DFSDM_Filter_TypeDef* DFSDMx); // 为选定DFSDMx的注入通道组启动软件启动。
void DFSDM_StartSoftwareRegularConversion(DFSDM_Filter_TypeDef* DFSDMx); // 启动选定DFSDMx的常规频道的软件启动。
void DFSDM_SynchronousFilter0InjectedStart(DFSDM_Filter_TypeDef* DFSDMx); // 当在DFSDM0中由软件启动的注入转换时，同步启动注入转换。
void DFSDM_SynchronousFilter0RegularStart(DFSDM_Filter_TypeDef* DFSDMx); // 当在DFSDM0中由软件启动的常规转换时，同步启动常规转换。
void DFSDM_RegularContinuousModeCmd(DFSDM_Filter_TypeDef* DFSDMx, FunctionalState NewState); // 启用或禁用选定过滤器DFSDMx的常规转换的继续模式。
void DFSDM_InjectedContinuousModeCmd(DFSDM_Filter_TypeDef* DFSDMx, FunctionalState NewState);
void DFSDM_FastModeCmd(DFSDM_Filter_TypeDef* DFSDMx, FunctionalState NewState); // 启用或禁用所选过滤器DFSDMx的快速模式。
void DFSDM_ConfigInjectedTrigger(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_Trigger, uint32_t DFSDM_TriggerEdge); // 选择触发信号以启动所选DFSDMx的注入转换。
void DFSDM_ConfigBRKShortCircuitDetector(DFSDM_Channel_TypeDef* DFSDM_Channelx, uint32_t DFSDM_SCDBreak_i, FunctionalState NewState); // 对指定的DFSDM_Channelx启用或禁用指定的Break_i siganl。
void DFSDM_ConfigBRKAnalogWatchDog(DFSDM_Channel_TypeDef* DFSDM_Channelx, uint32_t DFSDM_SCDBreak_i, FunctionalState NewState);
void DFSDM_ConfigShortCircuitThreshold(DFSDM_Channel_TypeDef* DFSDM_Channelx, uint32_t DFSDM_SCDThreshold); // 为选定的DFSDM_Channelx定义短路检测器的阈值计数器。
void DFSDM_ConfigAnalogWatchdog(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_AWDChannelx, uint32_t DFSDM_AWDFastMode); // 选择所选DFSDMx的模拟看门狗要保护的通道，并选择是否启用快速模拟看门犬。
void DFSDM_ConfigAWDFilter(DFSDM_Channel_TypeDef* DFSDM_Channelx, uint32_t DFSDM_AWDSincOrder, uint32_t DFSDM_AWDSincOverSampleRatio);
uint32_t DFSDM_GetAWDConversionValue(DFSDM_Channel_TypeDef* DFSDM_Channelx); // 返回channelx的最后一个模拟看门狗过滤器转换结果数据。
void DFSDM_SetAWDThreshold(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_HighThreshold, uint32_t DFSDM_LowThreshold); // 为所选DFSDMx的模拟看门狗配置高阈值和低阈值。
void DFSDM_SelectExtremesDetectorChannel(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_ExtremChannelx); // 选择要由所选DFSDMx的模拟看门狗保护的通道要使用的模式.
int32_t DFSDM_GetRegularConversionData(DFSDM_Filter_TypeDef* DFSDMx); // 通过DFSDMx返回常规转换数据。
int32_t DFSDM_GetInjectedConversionData(DFSDM_Filter_TypeDef* DFSDMx); // 通过DFSDMx返回注入的转换数据。
int32_t DFSDM_GetMaxValue(DFSDM_Filter_TypeDef* DFSDMx); // 返回由DFSDMx转换的最大值。
int32_t DFSDM_GetMinValue(DFSDM_Filter_TypeDef* DFSDMx); // 返回由DFSDMx转换的最小值。
int32_t DFSDM_GetMaxValueChannel(DFSDM_Filter_TypeDef* DFSDMx); // 返回DFSDMx在其上捕获最高转换数据的通道数。
int32_t DFSDM_GetMinValueChannel(DFSDM_Filter_TypeDef* DFSDMx); // 返回DFSDMx在其上捕获最低转换数据的通道数。
uint32_t DFSDM_GetConversionTime(DFSDM_Filter_TypeDef* DFSDMx); // 返回DFSDMx的转换时间(以28位计时器为单位)。
void DFSDM_DMATransferConfig(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_DMAConversionMode, FunctionalState NewState); // 启用或禁用 DMA以读取所选滤波器DFSDMx的注入信道组的数据。
/* 中断和标志管理功能 **********************************/
void DFSDM_ITConfig(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_IT, FunctionalState NewState); // 启用或禁用指定的DFSDMx中断。
#if defined(STM32F412xG)
void DFSDM_ITClockAbsenceCmd(FunctionalState NewState); // 启用或禁用时钟缺失中断。
void DFSDM_ITShortCircuitDetectorCmd(FunctionalState NewState); // 启用或禁用短路检测器中断。
#else /* STM32F413_423xx */
void DFSDM_ITClockAbsenceCmd(uint32_t Instance, FunctionalState NewState); // 启用或禁用时钟缺失中断。
void DFSDM_ITShortCircuitDetectorCmd(uint32_t Instance, FunctionalState NewState); // 启用或禁用短路检测器中断。
#endif /* STM32F412xG */

FlagStatus DFSDM_GetFlagStatus(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_FLAG); // 检查是否设置了指定的DFSDM标志。
#if defined(STM32F412xG)
FlagStatus DFSDM_GetClockAbsenceFlagStatus(uint32_t DFSDM_FLAG_CLKAbsence); // 检查是否设置了指定的时钟缺失通道标志。
FlagStatus DFSDM_GetShortCircuitFlagStatus(uint32_t DFSDM_FLAG_SCD); // 检查是否设置了指定的短路通道检测器标志。
#else /* STM32F413_423xx */
FlagStatus DFSDM_GetClockAbsenceFlagStatus(uint32_t Instance, uint32_t DFSDM_FLAG_CLKAbsence); // 检查是否设置了指定的时钟缺失通道标志。
FlagStatus DFSDM_GetShortCircuitFlagStatus(uint32_t Instance, uint32_t DFSDM_FLAG_SCD); // 检查是否设置了指定的短路通道检测器标志。
#endif /* STM32F412xG */
FlagStatus DFSDM_GetWatchdogFlagStatus(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_AWDChannelx, uint8_t DFSDM_Threshold); // 检查是否设置了指定的看门狗阈值标志。

void DFSDM_ClearFlag(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_CLEARF); // 清除DFSDMx的挂起标志。
#if defined(STM32F412xG)
void DFSDM_ClearClockAbsenceFlag(uint32_t DFSDM_CLEARF_CLKAbsence); // 清除DFSDMx的挂起时钟缺失通道标志。
void DFSDM_ClearShortCircuitFlag(uint32_t DFSDM_CLEARF_SCD); // 清除DFSDMx的挂起短路通道标志。
#else /* STM32F413_423xx */
void DFSDM_ClearClockAbsenceFlag(uint32_t Instance, uint32_t DFSDM_CLEARF_CLKAbsence); // 清除DFSDMx的挂起时钟缺失通道标志。
void DFSDM_ClearShortCircuitFlag(uint32_t Instance, uint32_t DFSDM_CLEARF_SCD); // 清除DFSDMx的挂起短路通道标志。
#endif /* STM32F412xG */
void DFSDM_ClearAnalogWatchdogFlag(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_AWDChannelx, uint8_t DFSDM_Threshold); // 清除DFSDMx的挂起模拟监视器通道标志。

ITStatus DFSDM_GetITStatus(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_IT); // 检查指定的DFSDM中断是否已发生。
#if defined(STM32F412xG)
ITStatus DFSDM_GetClockAbsenceITStatus(uint32_t DFSDM_IT_CLKAbsence); // 检查指定的"时钟缺失"通道中断是否已发生。
ITStatus DFSDM_GetShortCircuitITStatus(uint32_t DFSDM_IT_SCR); // 检查指定的短路通道中断是否已经发生。
#else /* STM32F413_423xx */
ITStatus DFSDM_GetClockAbsenceITStatus(uint32_t Instance, uint32_t DFSDM_IT_CLKAbsence); // 检查指定的"时钟缺失"通道中断是否已发生。
ITStatus DFSDM_GetShortCircuitITStatus(uint32_t Instance, uint32_t DFSDM_IT_SCR); // 检查指定的短路通道中断是否已经发生。
#endif /* STM32F412xG */

#endif /* STM32F412xG || STM32F413_423xx */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4XX_DFSDM_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
