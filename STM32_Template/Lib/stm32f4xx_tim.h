/**
  ******************************************************************************
  * 文件:    stm32f4xx_tim.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含TIM固件库的所有功能原型。
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
#ifndef __STM32F4xx_TIM_H
#define __STM32F4xx_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup TIM
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  TIM 时基初始化结构定义
  * 注意:   此结构用于除 TIM6 和 TIM7 之外的所有 TIMx。
  */
typedef struct {
    uint16_t TIM_Prescaler;         /*!< 指定用于分频 TIM 时钟的预分频器值。
                                        此参数可以是 0x0000 和 0xFFFF 之间的数字*/

    uint16_t TIM_CounterMode;       /*!< 指定计数器模式。
                                        该参数可以是 @ref TIM_Counter_Mode 的值*/

    uint32_t TIM_Period;            /*!< 指定要加载到活动中的周期值
                                        下次更新事件时自动重新加载注册。
                                        此参数必须是介于 0x0000 和 0xFFFF 之间的数字。  */

    uint16_t TIM_ClockDivision;     /*!< 指定时钟分频。
                                       该参数可以是 @ref TIM_Clock_Division_CKD 的值 */

    uint8_t TIM_RepetitionCounter;  /*!< 指定重复计数器值。 每次 RCR 递减计数器达到零时，都会生成一个更新事件，并从 RCR 值 (N) 重新开始计数。
                                        这意味着在 PWM 模式下，(N+1) 对应于:
                                           - 边沿对齐模式下的 PWM 周期数
                                           - 中心对齐模式下半个 PWM 周期的数量
                                        此参数必须是介于 0x00 和 0xFF 之间的数字。
                                        @note 此参数仅对 TIM1 和 TIM8 有效。 */
} TIM_TimeBaseInitTypeDef;

/**
  * 简介:  TIM 输出比较初始化结构定义
  */
typedef struct {
    uint16_t TIM_OCMode;        /*!< 指定 TIM 模式。
                                    该参数可以是 @ref TIM_Output_Compare_and_PWM_modes 的值 */

    uint16_t TIM_OutputState;   /*!< 指定 TIM 输出比较状态。
                                    该参数可以是 @ref TIM_Output_Compare_State 的值 */

    uint16_t TIM_OutputNState;  /*!< 指定 TIM 互补输出比较状态。
                                    该参数可以是 @ref TIM_Output_Compare_N_State 的值
                                    @note 此参数仅对 TIM1 和 TIM8 有效。 */

    uint32_t TIM_Pulse;         /*!< 指定要加载到捕捉比较寄存器的脉冲值。
                                    此参数可以是 0x0000 和 0xFFFF 之间的数字 */

    uint16_t TIM_OCPolarity;    /*!< 指定输出极性。
                                    此参数可以是 @ref TIM_Output_Compare_Polarity 的值 */

    uint16_t TIM_OCNPolarity;   /*!< 指定互补输出极性。
                                    该参数可以是 @ref TIM_Output_Compare_N_Polarity 的值
                                    @note 此参数仅对 TIM1 和 TIM8 有效。 */

    uint16_t TIM_OCIdleState;   /*!< 指定空闲状态期间的 TIM 输出比较引脚状态。
                                    该参数可以是 @ref TIM_Output_Compare_Idle_State 的值
                                    @note 此参数仅对 TIM1 和 TIM8 有效。*/

    uint16_t TIM_OCNIdleState;  /*!< 指定空闲状态期间的 TIM 输出比较引脚状态。
                                    该参数可以是 @ref TIM_Output_Compare_N_Idle_State 的值
                                    @note 此参数仅对 TIM1 和 TIM8 有效。 */
} TIM_OCInitTypeDef;

/**
  * 简介:  TIM 输入捕获初始化结构定义
  */
typedef struct {

    uint16_t TIM_Channel;      /*!< 指定 TIM 通道。
                                   该参数可以是 @ref TIM_Channel 的值 */

    uint16_t TIM_ICPolarity;   /*!< 指定输入信号的有效边沿。
                                   该参数可以是 @ref TIM_Input_Capture_Polarity 的值 */

    uint16_t TIM_ICSelection;  /*!< 指定输入。
                                   该参数可以是 @ref TIM_Input_Capture_Selection 的值 */

    uint16_t TIM_ICPrescaler;  /*!< 指定输入捕捉预分频器。
                                   该参数可以是 @ref TIM_Input_Capture_Prescaler 的值 */

    uint16_t TIM_ICFilter;     /*!< 指定输入捕获过滤器。
                                   此参数可以是 0x0 和 0xF 之间的数字 */
} TIM_ICInitTypeDef;

/**
  * 简介:  BDTR 结构定义
  * 注意:   此结构仅用于 TIM1 和 TIM8。
  */
typedef struct {

    uint16_t TIM_OSSRState;        /*!< 指定在运行模式中使用的关闭状态选择。
                                       该参数可以是 @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state 的值 */

    uint16_t TIM_OSSIState;        /*!< 指定在空闲状态下使用的关闭状态。
                                       该参数可以是 @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state 的值 */

    uint16_t TIM_LOCKLevel;        /*!< 指定 LOCK 级别参数。
                                       该参数可以是 @ref TIM_Lock_level 的值 */

    uint16_t TIM_DeadTime;         /*!< 指定输出关闭和打开之间的延迟时间。
                                       此参数可以是 0x00 到 0xFF 之间的数字  */

    uint16_t TIM_Break;            /*!< 指定是否启用 TIM Break 输入。
                                       该参数可以是 @ref TIM_Break_Input_enable_disable 的值 */

    uint16_t TIM_BreakPolarity;    /*!< 指定 TIM 中断输入引脚极性。
                                       该参数可以是 @ref TIM_Break_Polarity 的值 */

    uint16_t TIM_AutomaticOutput;  /*!< 指定是否启用 TIM 自动输出功能。
                                       该参数可以是 @ref TIM_AOE_Bit_Set_Reset 的值 */
} TIM_BDTRInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup TIM_Exported_constants
  */
#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                   ((PERIPH) == TIM2) || \
                                   ((PERIPH) == TIM3) || \
                                   ((PERIPH) == TIM4) || \
                                   ((PERIPH) == TIM5) || \
                                   ((PERIPH) == TIM6) || \
                                   ((PERIPH) == TIM7) || \
                                   ((PERIPH) == TIM8) || \
                                   ((PERIPH) == TIM9) || \
                                   ((PERIPH) == TIM10) || \
                                   ((PERIPH) == TIM11) || \
                                   ((PERIPH) == TIM12) || \
                                   (((PERIPH) == TIM13) || \
                                    ((PERIPH) == TIM14)))
/* LIST1: TIM1, TIM2, TIM3, TIM4, TIM5, TIM8, TIM9, TIM10, TIM11, TIM12, TIM13 and TIM14 */
#define IS_TIM_LIST1_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM9) || \
                                     ((PERIPH) == TIM10) || \
                                     ((PERIPH) == TIM11) || \
                                     ((PERIPH) == TIM12) || \
                                     ((PERIPH) == TIM13) || \
                                     ((PERIPH) == TIM14))

/* LIST2: TIM1, TIM2, TIM3, TIM4, TIM5, TIM8, TIM9 and TIM12 */
#define IS_TIM_LIST2_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8) || \
                                     ((PERIPH) == TIM9) || \
                                     ((PERIPH) == TIM12))
/* LIST3: TIM1, TIM2, TIM3, TIM4, TIM5 and TIM8 */
#define IS_TIM_LIST3_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8))
/* LIST4: TIM1 and TIM8 */
#define IS_TIM_LIST4_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM8))
/* LIST5: TIM1, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7 and TIM8 */
#define IS_TIM_LIST5_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM6) || \
                                     ((PERIPH) == TIM7) || \
                                     ((PERIPH) == TIM8))
/* LIST6: TIM2, TIM5 and TIM11 */
#define IS_TIM_LIST6_PERIPH(TIMx)(((TIMx) == TIM2) || \
                                  ((TIMx) == TIM5) || \
                                  ((TIMx) == TIM11))

/** @defgroup TIM_Output_Compare_and_PWM_modes
  */
#define TIM_OCMode_Timing                  ((uint16_t)0x0000)
#define TIM_OCMode_Active                  ((uint16_t)0x0010)
#define TIM_OCMode_Inactive                ((uint16_t)0x0020)
#define TIM_OCMode_Toggle                  ((uint16_t)0x0030)
#define TIM_OCMode_PWM1                    ((uint16_t)0x0060)
#define TIM_OCMode_PWM2                    ((uint16_t)0x0070)
#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
                              ((MODE) == TIM_OCMode_Active) || \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle)|| \
                              ((MODE) == TIM_OCMode_PWM1) || \
                              ((MODE) == TIM_OCMode_PWM2))
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
                          ((MODE) == TIM_OCMode_Active) || \
                          ((MODE) == TIM_OCMode_Inactive) || \
                          ((MODE) == TIM_OCMode_Toggle)|| \
                          ((MODE) == TIM_OCMode_PWM1) || \
                          ((MODE) == TIM_OCMode_PWM2) ||	\
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive))

/** @defgroup TIM_One_Pulse_Mode
  */
#define TIM_OPMode_Single                  ((uint16_t)0x0008)
#define TIM_OPMode_Repetitive              ((uint16_t)0x0000)
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))

/** @defgroup TIM_Channel
  */
#define TIM_Channel_1                      ((uint16_t)0x0000)
#define TIM_Channel_2                      ((uint16_t)0x0004)
#define TIM_Channel_3                      ((uint16_t)0x0008)
#define TIM_Channel_4                      ((uint16_t)0x000C)

#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))

#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))
#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
        ((CHANNEL) == TIM_Channel_2) || \
        ((CHANNEL) == TIM_Channel_3))

/** @defgroup TIM_Clock_Division_CKD
  */
#define TIM_CKD_DIV1                       ((uint16_t)0x0000)
#define TIM_CKD_DIV2                       ((uint16_t)0x0100)
#define TIM_CKD_DIV4                       ((uint16_t)0x0200)
#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))

/** @defgroup TIM_Counter_Mode
  */
#define TIM_CounterMode_Up                 ((uint16_t)0x0000)
#define TIM_CounterMode_Down               ((uint16_t)0x0010)
#define TIM_CounterMode_CenterAligned1     ((uint16_t)0x0020)
#define TIM_CounterMode_CenterAligned2     ((uint16_t)0x0040)
#define TIM_CounterMode_CenterAligned3     ((uint16_t)0x0060)
#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||  \
                                   ((MODE) == TIM_CounterMode_Down) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3))

/** @defgroup TIM_Output_Compare_Polarity
  */
#define TIM_OCPolarity_High                ((uint16_t)0x0000)
#define TIM_OCPolarity_Low                 ((uint16_t)0x0002)
#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))

/** @defgroup TIM_Output_Compare_N_Polarity
  */
#define TIM_OCNPolarity_High               ((uint16_t)0x0000)
#define TIM_OCNPolarity_Low                ((uint16_t)0x0008)
#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))

/** @defgroup TIM_Output_Compare_State
  */
#define TIM_OutputState_Disable            ((uint16_t)0x0000)
#define TIM_OutputState_Enable             ((uint16_t)0x0001)
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))

/** @defgroup TIM_Output_Compare_N_State
  */
#define TIM_OutputNState_Disable           ((uint16_t)0x0000)
#define TIM_OutputNState_Enable            ((uint16_t)0x0004)
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))

/** @defgroup TIM_Capture_Compare_State
  */
#define TIM_CCx_Enable                      ((uint16_t)0x0001)
#define TIM_CCx_Disable                     ((uint16_t)0x0000)
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))

/** @defgroup TIM_Capture_Compare_N_State
  */
#define TIM_CCxN_Enable                     ((uint16_t)0x0004)
#define TIM_CCxN_Disable                    ((uint16_t)0x0000)
#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
                           ((CCXN) == TIM_CCxN_Disable))

/** @defgroup TIM_Break_Input_enable_disable
  */
#define TIM_Break_Enable                   ((uint16_t)0x1000)
#define TIM_Break_Disable                  ((uint16_t)0x0000)
#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
                                   ((STATE) == TIM_Break_Disable))

/** @defgroup TIM_Break_Polarity
  */
#define TIM_BreakPolarity_Low              ((uint16_t)0x0000)
#define TIM_BreakPolarity_High             ((uint16_t)0x2000)
#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
        ((POLARITY) == TIM_BreakPolarity_High))

/** @defgroup TIM_AOE_Bit_Set_Reset
  */
#define TIM_AutomaticOutput_Enable         ((uint16_t)0x4000)
#define TIM_AutomaticOutput_Disable        ((uint16_t)0x0000)
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
        ((STATE) == TIM_AutomaticOutput_Disable))

/** @defgroup TIM_Lock_level
  */
#define TIM_LOCKLevel_OFF                  ((uint16_t)0x0000)
#define TIM_LOCKLevel_1                    ((uint16_t)0x0100)
#define TIM_LOCKLevel_2                    ((uint16_t)0x0200)
#define TIM_LOCKLevel_3                    ((uint16_t)0x0300)
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) || \
                                  ((LEVEL) == TIM_LOCKLevel_2) || \
                                  ((LEVEL) == TIM_LOCKLevel_3))

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state
  */
#define TIM_OSSIState_Enable               ((uint16_t)0x0400)
#define TIM_OSSIState_Disable              ((uint16_t)0x0000)
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state
  */
#define TIM_OSSRState_Enable               ((uint16_t)0x0800)
#define TIM_OSSRState_Disable              ((uint16_t)0x0000)
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))

/** @defgroup TIM_Output_Compare_Idle_State
  */
#define TIM_OCIdleState_Set                ((uint16_t)0x0100)
#define TIM_OCIdleState_Reset              ((uint16_t)0x0000)
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))

/** @defgroup TIM_Output_Compare_N_Idle_State
  */
#define TIM_OCNIdleState_Set               ((uint16_t)0x0200)
#define TIM_OCNIdleState_Reset             ((uint16_t)0x0000)
#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))

/** @defgroup TIM_Input_Capture_Polarity
  */
#define  TIM_ICPolarity_Rising             ((uint16_t)0x0000)
#define  TIM_ICPolarity_Falling            ((uint16_t)0x0002)
#define  TIM_ICPolarity_BothEdge           ((uint16_t)0x000A)
#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling)|| \
                                      ((POLARITY) == TIM_ICPolarity_BothEdge))

/** @defgroup TIM_Input_Capture_Selection
  */
#define TIM_ICSelection_DirectTI           ((uint16_t)0x0001) /*!< 选择 TIM 输入 1、2、3 或 4 分别连接到 IC1、IC2、IC3 或 IC4 */
#define TIM_ICSelection_IndirectTI         ((uint16_t)0x0002) /*!< 选择 TIM 输入 1、2、3 或 4 分别连接到 IC2、IC1、IC4 或 IC3。 */
#define TIM_ICSelection_TRC                ((uint16_t)0x0003) /*!< 选择 TIM 输入 1、2、3 或 4 连接到 TRC。 */
#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC))

/** @defgroup TIM_Input_Capture_Prescaler
  */
#define TIM_ICPSC_DIV1                     ((uint16_t)0x0000) /*!< 每次在捕获输入上检测到边沿时执行捕获。 */
#define TIM_ICPSC_DIV2                     ((uint16_t)0x0004) /*!< 每 2 个事件执行一次捕获。 */
#define TIM_ICPSC_DIV4                     ((uint16_t)0x0008) /*!< 每 4 个事件执行一次捕获。 */
#define TIM_ICPSC_DIV8                     ((uint16_t)0x000C) /*!< 每 8 个事件执行一次捕获。 */
#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))

/** @defgroup TIM_interrupt_sources
  */
#define TIM_IT_Update                      ((uint16_t)0x0001)
#define TIM_IT_CC1                         ((uint16_t)0x0002)
#define TIM_IT_CC2                         ((uint16_t)0x0004)
#define TIM_IT_CC3                         ((uint16_t)0x0008)
#define TIM_IT_CC4                         ((uint16_t)0x0010)
#define TIM_IT_COM                         ((uint16_t)0x0020)
#define TIM_IT_Trigger                     ((uint16_t)0x0040)
#define TIM_IT_Break                       ((uint16_t)0x0080)
#define IS_TIM_IT(IT) ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) || \
                           ((IT) == TIM_IT_CC1) || \
                           ((IT) == TIM_IT_CC2) || \
                           ((IT) == TIM_IT_CC3) || \
                           ((IT) == TIM_IT_CC4) || \
                           ((IT) == TIM_IT_COM) || \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break))

/** @defgroup TIM_DMA_Base_address
  */
#define TIM_DMABase_CR1                    ((uint16_t)0x0000)
#define TIM_DMABase_CR2                    ((uint16_t)0x0001)
#define TIM_DMABase_SMCR                   ((uint16_t)0x0002)
#define TIM_DMABase_DIER                   ((uint16_t)0x0003)
#define TIM_DMABase_SR                     ((uint16_t)0x0004)
#define TIM_DMABase_EGR                    ((uint16_t)0x0005)
#define TIM_DMABase_CCMR1                  ((uint16_t)0x0006)
#define TIM_DMABase_CCMR2                  ((uint16_t)0x0007)
#define TIM_DMABase_CCER                   ((uint16_t)0x0008)
#define TIM_DMABase_CNT                    ((uint16_t)0x0009)
#define TIM_DMABase_PSC                    ((uint16_t)0x000A)
#define TIM_DMABase_ARR                    ((uint16_t)0x000B)
#define TIM_DMABase_RCR                    ((uint16_t)0x000C)
#define TIM_DMABase_CCR1                   ((uint16_t)0x000D)
#define TIM_DMABase_CCR2                   ((uint16_t)0x000E)
#define TIM_DMABase_CCR3                   ((uint16_t)0x000F)
#define TIM_DMABase_CCR4                   ((uint16_t)0x0010)
#define TIM_DMABase_BDTR                   ((uint16_t)0x0011)
#define TIM_DMABase_DCR                    ((uint16_t)0x0012)
#define TIM_DMABase_OR                     ((uint16_t)0x0013)
#define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1) || \
                               ((BASE) == TIM_DMABase_CR2) || \
                               ((BASE) == TIM_DMABase_SMCR) || \
                               ((BASE) == TIM_DMABase_DIER) || \
                               ((BASE) == TIM_DMABase_SR) || \
                               ((BASE) == TIM_DMABase_EGR) || \
                               ((BASE) == TIM_DMABase_CCMR1) || \
                               ((BASE) == TIM_DMABase_CCMR2) || \
                               ((BASE) == TIM_DMABase_CCER) || \
                               ((BASE) == TIM_DMABase_CNT) || \
                               ((BASE) == TIM_DMABase_PSC) || \
                               ((BASE) == TIM_DMABase_ARR) || \
                               ((BASE) == TIM_DMABase_RCR) || \
                               ((BASE) == TIM_DMABase_CCR1) || \
                               ((BASE) == TIM_DMABase_CCR2) || \
                               ((BASE) == TIM_DMABase_CCR3) || \
                               ((BASE) == TIM_DMABase_CCR4) || \
                               ((BASE) == TIM_DMABase_BDTR) || \
                               ((BASE) == TIM_DMABase_DCR) || \
                               ((BASE) == TIM_DMABase_OR))

/** @defgroup TIM_DMA_Burst_Length
  */
#define TIM_DMABurstLength_1Transfer           ((uint16_t)0x0000)
#define TIM_DMABurstLength_2Transfers          ((uint16_t)0x0100)
#define TIM_DMABurstLength_3Transfers          ((uint16_t)0x0200)
#define TIM_DMABurstLength_4Transfers          ((uint16_t)0x0300)
#define TIM_DMABurstLength_5Transfers          ((uint16_t)0x0400)
#define TIM_DMABurstLength_6Transfers          ((uint16_t)0x0500)
#define TIM_DMABurstLength_7Transfers          ((uint16_t)0x0600)
#define TIM_DMABurstLength_8Transfers          ((uint16_t)0x0700)
#define TIM_DMABurstLength_9Transfers          ((uint16_t)0x0800)
#define TIM_DMABurstLength_10Transfers         ((uint16_t)0x0900)
#define TIM_DMABurstLength_11Transfers         ((uint16_t)0x0A00)
#define TIM_DMABurstLength_12Transfers         ((uint16_t)0x0B00)
#define TIM_DMABurstLength_13Transfers         ((uint16_t)0x0C00)
#define TIM_DMABurstLength_14Transfers         ((uint16_t)0x0D00)
#define TIM_DMABurstLength_15Transfers         ((uint16_t)0x0E00)
#define TIM_DMABurstLength_16Transfers         ((uint16_t)0x0F00)
#define TIM_DMABurstLength_17Transfers         ((uint16_t)0x1000)
#define TIM_DMABurstLength_18Transfers         ((uint16_t)0x1100)
#define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Transfer) || \
                                   ((LENGTH) == TIM_DMABurstLength_2Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_3Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_4Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_5Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_6Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_7Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_8Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_9Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_10Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Transfers))

/** @defgroup TIM_DMA_sources
  */
#define TIM_DMA_Update                     ((uint16_t)0x0100)
#define TIM_DMA_CC1                        ((uint16_t)0x0200)
#define TIM_DMA_CC2                        ((uint16_t)0x0400)
#define TIM_DMA_CC3                        ((uint16_t)0x0800)
#define TIM_DMA_CC4                        ((uint16_t)0x1000)
#define TIM_DMA_COM                        ((uint16_t)0x2000)
#define TIM_DMA_Trigger                    ((uint16_t)0x4000)
#define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))


/** @defgroup TIM_External_Trigger_Prescaler
  */
#define TIM_ExtTRGPSC_OFF                  ((uint16_t)0x0000)
#define TIM_ExtTRGPSC_DIV2                 ((uint16_t)0x1000)
#define TIM_ExtTRGPSC_DIV4                 ((uint16_t)0x2000)
#define TIM_ExtTRGPSC_DIV8                 ((uint16_t)0x3000)
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
        ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
        ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
        ((PRESCALER) == TIM_ExtTRGPSC_DIV8))

/** @defgroup TIM_Internal_Trigger_Selection
  */
#define TIM_TS_ITR0                        ((uint16_t)0x0000)
#define TIM_TS_ITR1                        ((uint16_t)0x0010)
#define TIM_TS_ITR2                        ((uint16_t)0x0020)
#define TIM_TS_ITR3                        ((uint16_t)0x0030)
#define TIM_TS_TI1F_ED                     ((uint16_t)0x0040)
#define TIM_TS_TI1FP1                      ((uint16_t)0x0050)
#define TIM_TS_TI2FP2                      ((uint16_t)0x0060)
#define TIM_TS_ETRF                        ((uint16_t)0x0070)
#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
        ((SELECTION) == TIM_TS_ITR1) || \
        ((SELECTION) == TIM_TS_ITR2) || \
        ((SELECTION) == TIM_TS_ITR3) || \
        ((SELECTION) == TIM_TS_TI1F_ED) || \
        ((SELECTION) == TIM_TS_TI1FP1) || \
        ((SELECTION) == TIM_TS_TI2FP2) || \
        ((SELECTION) == TIM_TS_ETRF))
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
        ((SELECTION) == TIM_TS_ITR1) || \
        ((SELECTION) == TIM_TS_ITR2) || \
        ((SELECTION) == TIM_TS_ITR3))

/** @defgroup TIM_TIx_External_Clock_Source
  */
#define TIM_TIxExternalCLK1Source_TI1      ((uint16_t)0x0050)
#define TIM_TIxExternalCLK1Source_TI2      ((uint16_t)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED    ((uint16_t)0x0040)


/** @defgroup TIM_External_Trigger_Polarity
  */
#define TIM_ExtTRGPolarity_Inverted        ((uint16_t)0x8000)
#define TIM_ExtTRGPolarity_NonInverted     ((uint16_t)0x0000)
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))

/** @defgroup TIM_Prescaler_Reload_Mode
  */
#define TIM_PSCReloadMode_Update           ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate        ((uint16_t)0x0001)
#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
        ((RELOAD) == TIM_PSCReloadMode_Immediate))

/** @defgroup TIM_Forced_Action
  */
#define TIM_ForcedAction_Active            ((uint16_t)0x0050)
#define TIM_ForcedAction_InActive          ((uint16_t)0x0040)
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))

/** @defgroup TIM_Encoder_Mode
  */
#define TIM_EncoderMode_TI1                ((uint16_t)0x0001)
#define TIM_EncoderMode_TI2                ((uint16_t)0x0002)
#define TIM_EncoderMode_TI12               ((uint16_t)0x0003)
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))


/** @defgroup TIM_Event_Source
  */
#define TIM_EventSource_Update             ((uint16_t)0x0001)
#define TIM_EventSource_CC1                ((uint16_t)0x0002)
#define TIM_EventSource_CC2                ((uint16_t)0x0004)
#define TIM_EventSource_CC3                ((uint16_t)0x0008)
#define TIM_EventSource_CC4                ((uint16_t)0x0010)
#define TIM_EventSource_COM                ((uint16_t)0x0020)
#define TIM_EventSource_Trigger            ((uint16_t)0x0040)
#define TIM_EventSource_Break              ((uint16_t)0x0080)
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))


/** @defgroup TIM_Update_Source
  */
#define TIM_UpdateSource_Global            ((uint16_t)0x0000) /*!< 更新源是计数器上溢/下溢或 UG 位的设置，或通过从模式控制器生成的更新。 */
#define TIM_UpdateSource_Regular           ((uint16_t)0x0001) /*!< 更新源是计数器上溢/下溢。 */
#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))

/** @defgroup TIM_Output_Compare_Preload_State
  */
#define TIM_OCPreload_Enable               ((uint16_t)0x0008)
#define TIM_OCPreload_Disable              ((uint16_t)0x0000)
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))

/** @defgroup TIM_Output_Compare_Fast_State
  */
#define TIM_OCFast_Enable                  ((uint16_t)0x0004)
#define TIM_OCFast_Disable                 ((uint16_t)0x0000)
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))


/** @defgroup TIM_Output_Compare_Clear_State
  */
#define TIM_OCClear_Enable                 ((uint16_t)0x0080)
#define TIM_OCClear_Disable                ((uint16_t)0x0000)
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))

/** @defgroup TIM_Trigger_Output_Source
  */
#define TIM_TRGOSource_Reset               ((uint16_t)0x0000)
#define TIM_TRGOSource_Enable              ((uint16_t)0x0010)
#define TIM_TRGOSource_Update              ((uint16_t)0x0020)
#define TIM_TRGOSource_OC1                 ((uint16_t)0x0030)
#define TIM_TRGOSource_OC1Ref              ((uint16_t)0x0040)
#define TIM_TRGOSource_OC2Ref              ((uint16_t)0x0050)
#define TIM_TRGOSource_OC3Ref              ((uint16_t)0x0060)
#define TIM_TRGOSource_OC4Ref              ((uint16_t)0x0070)
#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))

/** @defgroup TIM_Slave_Mode
  */
#define TIM_SlaveMode_Reset                ((uint16_t)0x0004)
#define TIM_SlaveMode_Gated                ((uint16_t)0x0005)
#define TIM_SlaveMode_Trigger              ((uint16_t)0x0006)
#define TIM_SlaveMode_External1            ((uint16_t)0x0007)
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
                                 ((MODE) == TIM_SlaveMode_Gated) || \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1))

/** @defgroup TIM_Master_Slave_Mode
  */
#define TIM_MasterSlaveMode_Enable         ((uint16_t)0x0080)
#define TIM_MasterSlaveMode_Disable        ((uint16_t)0x0000)
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))
/** @defgroup TIM_Remap
  */
#define TIM2_TIM8_TRGO                     ((uint16_t)0x0000)
#define TIM2_ETH_PTP                       ((uint16_t)0x0400)
#define TIM2_USBFS_SOF                     ((uint16_t)0x0800)
#define TIM2_USBHS_SOF                     ((uint16_t)0x0C00)

#define TIM5_GPIO                          ((uint16_t)0x0000)
#define TIM5_LSI                           ((uint16_t)0x0040)
#define TIM5_LSE                           ((uint16_t)0x0080)
#define TIM5_RTC                           ((uint16_t)0x00C0)

#define TIM11_GPIO                         ((uint16_t)0x0000)
#define TIM11_HSE                          ((uint16_t)0x0002)

#define IS_TIM_REMAP(TIM_REMAP)	 (((TIM_REMAP) == TIM2_TIM8_TRGO)||\
                                  ((TIM_REMAP) == TIM2_ETH_PTP)||\
                                  ((TIM_REMAP) == TIM2_USBFS_SOF)||\
                                  ((TIM_REMAP) == TIM2_USBHS_SOF)||\
                                  ((TIM_REMAP) == TIM5_GPIO)||\
                                  ((TIM_REMAP) == TIM5_LSI)||\
                                  ((TIM_REMAP) == TIM5_LSE)||\
                                  ((TIM_REMAP) == TIM5_RTC)||\
                                  ((TIM_REMAP) == TIM11_GPIO)||\
                                  ((TIM_REMAP) == TIM11_HSE))

/** @defgroup TIM_Flags
  */
#define TIM_FLAG_Update                    ((uint16_t)0x0001)
#define TIM_FLAG_CC1                       ((uint16_t)0x0002)
#define TIM_FLAG_CC2                       ((uint16_t)0x0004)
#define TIM_FLAG_CC3                       ((uint16_t)0x0008)
#define TIM_FLAG_CC4                       ((uint16_t)0x0010)
#define TIM_FLAG_COM                       ((uint16_t)0x0020)
#define TIM_FLAG_Trigger                   ((uint16_t)0x0040)
#define TIM_FLAG_Break                     ((uint16_t)0x0080)
#define TIM_FLAG_CC1OF                     ((uint16_t)0x0200)
#define TIM_FLAG_CC2OF                     ((uint16_t)0x0400)
#define TIM_FLAG_CC3OF                     ((uint16_t)0x0800)
#define TIM_FLAG_CC4OF                     ((uint16_t)0x1000)
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
                               ((FLAG) == TIM_FLAG_CC1) || \
                               ((FLAG) == TIM_FLAG_CC2) || \
                               ((FLAG) == TIM_FLAG_CC3) || \
                               ((FLAG) == TIM_FLAG_CC4) || \
                               ((FLAG) == TIM_FLAG_COM) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) || \
                               ((FLAG) == TIM_FLAG_CC1OF) || \
                               ((FLAG) == TIM_FLAG_CC2OF) || \
                               ((FLAG) == TIM_FLAG_CC3OF) || \
                               ((FLAG) == TIM_FLAG_CC4OF))


/** @defgroup TIM_Input_Capture_Filer_Value
  */
#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF)

/** @defgroup TIM_External_Trigger_Filter
  */
#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)

/** @defgroup TIM_Legacy
  */
#define TIM_DMABurstLength_1Byte           TIM_DMABurstLength_1Transfer
#define TIM_DMABurstLength_2Bytes          TIM_DMABurstLength_2Transfers
#define TIM_DMABurstLength_3Bytes          TIM_DMABurstLength_3Transfers
#define TIM_DMABurstLength_4Bytes          TIM_DMABurstLength_4Transfers
#define TIM_DMABurstLength_5Bytes          TIM_DMABurstLength_5Transfers
#define TIM_DMABurstLength_6Bytes          TIM_DMABurstLength_6Transfers
#define TIM_DMABurstLength_7Bytes          TIM_DMABurstLength_7Transfers
#define TIM_DMABurstLength_8Bytes          TIM_DMABurstLength_8Transfers
#define TIM_DMABurstLength_9Bytes          TIM_DMABurstLength_9Transfers
#define TIM_DMABurstLength_10Bytes         TIM_DMABurstLength_10Transfers
#define TIM_DMABurstLength_11Bytes         TIM_DMABurstLength_11Transfers
#define TIM_DMABurstLength_12Bytes         TIM_DMABurstLength_12Transfers
#define TIM_DMABurstLength_13Bytes         TIM_DMABurstLength_13Transfers
#define TIM_DMABurstLength_14Bytes         TIM_DMABurstLength_14Transfers
#define TIM_DMABurstLength_15Bytes         TIM_DMABurstLength_15Transfers
#define TIM_DMABurstLength_16Bytes         TIM_DMABurstLength_16Transfers
#define TIM_DMABurstLength_17Bytes         TIM_DMABurstLength_17Transfers
#define TIM_DMABurstLength_18Bytes         TIM_DMABurstLength_18Transfers


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* 时间基准管理 ********************************************************/
void TIM_DeInit(TIM_TypeDef* TIMx); // 将 TIMx 外设寄存器去初始化为其默认复位值。
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct); // 根据 TIM_TimeBaseInitStruct 中指定的参数初始化TIMx时基单元外设。
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct); // 用每个 TIM_TimeBaseInitStruct 成员的默认值填充其默认值。
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode); // 配置 TIMx 预分频器。
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode); // 指定要使用的 TIMx 计数器模式。
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter); // 设置 TIMx 计数器寄存器值。
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload); // 设置 TIMx 自动重新加载寄存器值。
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx); // 获取 TIMx 计数器值。
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx); // 获取TIMx预分频器值。
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState); // 启用或禁用 TIMx 更新事件。
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource); // 配置 TIMx 更新请求中断源。
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState); // 启用或禁用 ARR 上的 TIMx 外设预加载寄存器。
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode); // 选择 TIMx 的单脉冲模式。
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD); // 设置 TIMx 时钟分频值。
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState); // 启用或禁用指定的 TIM 外设。

/* 输出比较管理 **************************************************/
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct); // 根据 TIM_OCInitStruct 中指定的参数初始化 TIMx 通道 1。
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct); // 根据 TIM_OCInitStruct 中指定的参数初始化 TIMx 通道 2。
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct); // 根据 TIM_OCInitStruct 中指定的参数初始化 TIMx 通道 3。
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct); // 根据 TIM_OCInitStruct 中指定的参数初始化 TIMx 通道 4。
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct); // 用其默认值填充每个 TIM_OCInitStruct 成员。
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode); // 选择 TIM 输出比较模式。
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1); // 设置 TIMx 捕获比较1 寄存器值。
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2); // 设置 TIMx 捕获比较2 寄存器值。
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3); // 设置 TIMx 捕获比较3 寄存器值。
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4); // 设置 TIMx 捕获比较4 寄存器值。
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction); // 强制 TIMx 输出 1 波形达到活动或非活动电平。
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction); // 强制 TIMx 输出 2 波形达到活动或非活动电平。
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction); // 强制 TIMx 输出 3 波形达到活动或非活动电平。
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction); // 强制 TIMx 输出 4 波形达到活动或非活动电平。
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload); // 启用或禁用 CCR1 上的 TIMx 外设预加载寄存器。
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload); // 启用或禁用 CCR2 上的 TIMx 外设预加载寄存器。
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload); // 启用或禁用 CCR3 上的 TIMx 外设预加载寄存器。
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload); // 启用或禁用 CCR4 上的 TIMx 外设预加载寄存器。
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast); // 配置 TIMx 输出比较 1 快速功能。
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast); // 配置 TIMx 输出比较 2 快速功能。
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast); // 配置 TIMx 输出比较 3 快速功能。
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast); // 配置 TIMx 输出比较 4 快速功能。
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear); // 清除或保护外部事件上的 OCREF1 信号。
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear); // 清除或保护外部事件上的 OCREF2 信号。
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear); // 清除或保护外部事件上的 OCREF3 信号。
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear); // 清除或保护外部事件上的 OCREF4 信号。
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity); // 配置 TIMx 通道 1 极性。
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity); // 配置 TIMx 通道 1N 极性。
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity); // 配置 TIMx 通道 2 极性。
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity); // 配置 TIMx 通道 2N 极性。
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity); // 配置 TIMx 通道 3 极性。
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity); // 配置 TIMx 通道 3N 极性。
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity); // 配置 TIMx 通道 4 极性。
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx); // 启用或禁用 TIM 捕获比较通道 x。
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN); // 启用或禁用 TIM 捕获比较通道 xN。

/* 输入捕获管理 ***************************************************/
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct); // 根据 TIM_ICInitStruct 中指定的参数初始化 TIM 外设。
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct); // 用其默认值填充每个 TIM_ICInitStruct 成员。
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct); // 根据 TIM_ICInitStruct 中的指定参数配置 TIM 外设，以测量外部 PWM 信号。
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx); // 获取 TIMx 输入捕获 1 值。
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx); // 获取 TIMx 输入捕获 2 值。
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx); // 获取 TIMx 输入捕获 3 值。
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx); // 获取 TIMx 输入捕获 4 值。
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC); // 设置 TIMx 输入捕获 1 预分频器。
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC); // 设置 TIMx 输入捕获 2 预分频器。
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC); // 设置 TIMx 输入捕获 3 预分频器。
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC); // 设置 TIMx 输入捕获 4 预分频器。

/* 高级控制定时器(TIM1 和 TIM8)特定功能 ******************/
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct); // 配置中断功能、死区时间、锁定级别、OSSI/OSSR 状态和 AOE(自动输出启用)。
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct); // 用其默认值填充每个 TIM_BDTRInitStruct 成员。
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState); // 启用或禁用 TIM 外设主输出。
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState); // 选择 TIM 外设换向事件。
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState); // 设置或复位 TIM 外设捕获比较预紧力控制位。

/* 中断、DMA 和标志管理 ***************************************/
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState); // 启用或禁用指定的 TIM 中断。
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource); // 将 TIMx 事件配置为由 软件生成。
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG); // 检查是否设置了指定的 TIM 标志。
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG); // 清除 TIMx 的挂起标志。
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT); // 检查是否发生了 TIM 中断。
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT); // 清除 TIMx 的中断挂起位。
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength); // 配置 TIMx 的 DMA 接口。
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState); // 启用或禁用 TIMx 的 DMA 请求。
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState); // 选择 TIMx 外设捕获比较 DMA 源。

/* 时钟管理 **********************************************************/
void TIM_InternalClockConfig(TIM_TypeDef* TIMx); // 配置 TIMx 内部时钟。
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource); // 将 TIMx 内部触发器配置为外部时钟。
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter); // 将 TIMx 触发器配置为外部时钟。
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter); // 配置外部时钟模式1。
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter); // 配置外部时钟模式2。

/* 同步管理 *************************************************/
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource); // 选择输入触发器源。
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource); // 选择 TIMx 触发输出模式。
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode); // 选择 TIMx 从模式。
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode); // 设置或重置 TIMx 主/从模式。
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter); // 配置 TIMx 外部触发器 (ETR)。

/* 具体接口管理 **********************************************/
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity); // 	配置 TIMx 编码器接口。
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState); // 启用或禁用 TIMx 的霍尔传感器接口。

/* 具体重映射管理 **********************************************/
void TIM_RemapConfig(TIM_TypeDef* TIMx, uint16_t TIM_Remap); // 配置 TIM2、TIM5 和 TIM11 重新映射输入功能。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_TIM_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
