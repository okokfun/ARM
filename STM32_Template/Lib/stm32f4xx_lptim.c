/**
  ******************************************************************************
  * 文件:    stm32f4xx_lptim.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供了管理低功耗定时器(LPT)外设的以下功能的固件功能:
  *           + 初始化功能.
  *           + 配置功能.
  *           + 中断和标记管理函数.
  *
  *  @verbatim
  *
================================================================================
                   ##### 如何使用这个驱动程序 #####
================================================================================

           基础配置:
           --------------------
           - 通过填充 "LPTIM_InitTypeDef "结构并调用 LPTIM_Init 来配置时
             钟源、预分频器、波形形状和输出极性。

           - 如果选择了ULPTIM源作为时钟源，则通过 LPTIM_ConfigClockGlitch
             过滤器设置要检测的连续样本数来配置数字Glitch 过滤器。

           - 使用 LPTIM_SelectSoftwareStart 来选择一个软件启动。

           - 要为计数器的启动选择一个外部触发器，通过调用 LPTIM_ConfigExternalTrigger
             来配置源和它的有效边沿极性。通过使用 LPTIM_ConfigTriggerGlitch 过滤器
             设置要检测的连续样本数来配置外部触发器的数字突波滤波器。

           - 通过 LPTIM_SelectOperatingMode 来选择外设的工作模式，有两种模式可以选择。
               + 连续模式:定时器是自由运行的，定时器从一个触发事件开始，永不停止，直到定时器被禁用。
               + 一次性模式: 计时器从一个触发事件开始，当达到自动重载值时停止。

           - 使用 LPTIM_SetAutoreloadValue 来设置自动重载值，LPTIM_SetCompareValue 来设置比较值。

           - 通过使用 LPTIM_ConfigUpdate 函数配置预加载模式。有2种模式可供选择。
               + 自动加载和比较寄存器在 APB写入后立即更新。
               + 自动加载和比较寄存器在计数器周期结束时被更新。
               
            - 通过调用 LPTIM_Cmd 启用外设。

           编码器模式。
           -------------
           - 要选择编码器功能，请使用函数。LPTIM_SelectEncoderMode。
           - 要选择计数器在哪个边沿(上升沿、下降沿或两个边沿)递增，使用 LPTIM_SelectClockPolarity。

           计数器模式。
           -------------
           - 使用 LPTIM_SelectCounterMode 来选择计数模式。在这种模式下，
             计数器在 ULPTIM 上的每个有效事件上都会递增。

           超时功能。
           -----------------
           在这种情况下，触发器将重置定时器。第一个触发事件将启动定时器，
          任何连续的触发事件将重置计数器，定时器重新启动。
           - 要激活这个功能，请使用 LPTIM_TimoutCmd。

           中断配置。
           ------------------------
           - 使用 LPTIM_ITConfig 来配置一个中断。
           - 调用 LPTIM_GetFlagStatus 来获得一个标志状态。
           - 调用 LPTIM_GetITStatus 来获得中断状态。
           - 使用 LPTIM_ClearFlag 来清除一个标志。
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
#include "stm32f4xx_lptim.h"


/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup LPTIM
  * 简介: LPTIM 驱动模块
  */
#if defined(STM32F410xx) || defined(STM32F413_423xx)
/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* 私有宏s -----------------------------------------------------------*/

#define CFGR_INIT_CLEAR_MASK                 ((uint32_t) 0xFFCFF1FE)
#define CFGR_TRIG_AND_POL_CLEAR_MASK         ((uint32_t) 0xFFF91FFF)
/* 私有宏s ------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup LPTIM_Private_Functions
  */

/** @defgroup LPTIM_Group1 初始化功能
  *  简介   初始化功能
  *
@verbatim
 ===============================================================================
                             初始化功能
 ===============================================================================
  本节提供的功能允许:
   - 取消对 LPTimer 的初始化
   - 初始化时钟源、预分频器、输出波形形状和极性
   - 用默认值初始化 LPTIM_InitStruct 结构器的成员

@endverbatim
  */

/**
  * 简介:  将 LPTIMx 外设寄存器取消初始化为其默认复位值。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 返回值: 无
  *
  */
void LPTIM_DeInit(LPTIM_TypeDef* LPTIMx) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));

    /* Deinitializes the LPTIM1 外设 */
    if(LPTIMx == LPTIM1) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_LPTIM1, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_LPTIM1, DISABLE);
    }
}

/**
  * 简介:  根据 LPTIM_InitStruct 中指定的参数初始化 LPTIMx 外设。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_InitStruct: 指向 LPTIM_InitTypeDef 结构的指针，该结构包含指定 LPTIM 外设的配置信息。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_Init(LPTIM_TypeDef* LPTIMx, LPTIM_InitTypeDef* LPTIM_InitStruct) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_CLOCK_SOURCE(LPTIM_InitStruct->LPTIM_ClockSource));
    assert_param(IS_LPTIM_CLOCK_PRESCALER(LPTIM_InitStruct->LPTIM_Prescaler));
    assert_param(IS_LPTIM_WAVEFORM(LPTIM_InitStruct->LPTIM_Waveform));
    assert_param(IS_LPTIM_OUTPUT_POLARITY(LPTIM_InitStruct->LPTIM_OutputPolarity));

    /* 获取LPTIMx CFGR 值 */
    tmpreg1 = LPTIMx->CFGR;

    /* 清除 CKSEL, PRESC, WAVE and WAVEPOL 位 */
    tmpreg1 &= CFGR_INIT_CLEAR_MASK;

    /* 设置或重置 CKSEL bit 根据 LPTIM_ClockSource 值 */
    /* 设置或重置 PRESC bits 根据 LPTIM_Prescaler 值 */
    /* 设置或重置 WAVE bit 根据 LPTIM_Waveform 值 */
    /* 设置或重置 WAVEPOL bit 根据 LPTIM_OutputPolarity 值 */
    tmpreg1 |= (LPTIM_InitStruct->LPTIM_ClockSource | LPTIM_InitStruct->LPTIM_Prescaler
                | LPTIM_InitStruct->LPTIM_Waveform | LPTIM_InitStruct->LPTIM_OutputPolarity);

    /* 写入LPTIMx CFGR */
    LPTIMx->CFGR = tmpreg1;
}

/**
  * 简介:  用默认值填充每个 LPTIM_InitStruct 成员。
  * 
  * 参数:  LPTIM_InitStruct : 指向 LPTIM_InitTypeDef 结构的指针，该结构将被初始化。
  * 
  * 返回值: 无
  */
void LPTIM_StructInit(LPTIM_InitTypeDef* LPTIM_InitStruct) {
    /* APB 时钟/低功率振荡器被选为默认时钟源*/
    LPTIM_InitStruct->LPTIM_ClockSource = LPTIM_ClockSource_APBClock_LPosc;

    /* High Polarity被选为默认极性 */
    LPTIM_InitStruct->LPTIM_OutputPolarity = LPTIM_OutputPolarity_High;

    /* DIV=1被选为默认的预分频器 */
    LPTIM_InitStruct->LPTIM_Prescaler = LPTIM_Prescaler_DIV1;

    /* PWM/单脉冲模式被选为默认波形形状 */
    LPTIM_InitStruct->LPTIM_Waveform = LPTIM_Waveform_PWM_OnePulse;
}


/** @defgroup LPTIM_Group2 配置功能
  *  简介   配置功能
  *
@verbatim
 ===============================================================================
                       配置功能
 ===============================================================================
    本节提供的功能允许配置低功率定时器。
    - 选择时钟源。
    - 配置外部时钟的突波滤波器和外部时钟。
    - 配置计数器的预分频器。
    - 选择计数器的触发源。
    - 配置工作模式(单一或连续模式)。
    - 选择波形形状(PWM/单脉冲或设置一次)和极性。
    - 启用或禁用编码器模式和超时功能。
    - 写入自动加载和比较寄存器，配置预加载模式。
    - 获取计数器的值。
    - 启用或禁用外设。

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 LPTIM 外设.
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  NewState: 新状态-> LPTIMx 外设.
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void LPTIM_Cmd(LPTIM_TypeDef* LPTIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE) {
        /* 设置 ENABLE 位 */
        LPTIMx->CR |= LPTIM_CR_ENABLE;
    } else {
        /* 重设 ENABLE 位 */
        LPTIMx->CR &= ~(LPTIM_CR_ENABLE);
    }
}

/**
  * 简介:  选择 LPTIM 计数器的时钟源。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_ClockSource: 选定的时钟源。
  *         这个参数可以是:
  *         @arg LPTIM_ClockSource_APBClock_LPosc : 选择 APB 时钟/LP振荡器
  *         @arg LPTIM_ClockSource_ULPTIM: 选择 ULPTIM(外部输入)。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_SelectClockSource(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_ClockSource) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_CLOCK_SOURCE(LPTIM_ClockSource));

    /* 清除 CKSEL 位 */
    LPTIMx->CFGR &= ~(LPTIM_CFGR_CKSEL);

    /* 设置或重置 CKSEL 位 */
    LPTIMx->CFGR |= LPTIM_ClockSource;
}

/**
  * 简介:  如果选择了 ULPTIM 输入，则配置用于计数的边沿极性。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_ClockPolarity: 选择的时钟极性。
  * 这个参数可以是:
  *     @arg LPTIM_ClockPolarity_RisingEdge : Counter Clock = LPTIM Clock / 1
  *     @arg LPTIM_ClockPolarity_FallingEdge : Counter Clock = LPTIM Clock / 2
  *     @arg LPTIM_ClockPolarity_BothEdges : Counter Clock = LPTIM Clock / 4
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_SelectULPTIMClockPolarity(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_ClockPolarity) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_CLOCK_POLARITY(LPTIM_ClockPolarity));

    /* 获取LPTIMx CFGR 值 */
    tmpreg1 = LPTIMx->CFGR;

    /* 清除 CKPOL 位 */
    tmpreg1 &= ~(LPTIM_CFGR_CKPOL);

    /* 设置或重置 PRESC 位 */
    tmpreg1 |= LPTIM_ClockPolarity;

    /* 写入LPTIMx CFGR */
    LPTIMx->CFGR = tmpreg1;
}

/**
  * 简介:  配置时钟预分频器。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_Prescaler: 选择的时钟预分频器。
  * 这个参数可以是:
  *     @arg LPTIM_Prescaler_DIV1 : Counter Clock = LPTIM Clock / 1
  *     @arg LPTIM_Prescaler_DIV2 : Counter Clock = LPTIM Clock / 2
  *     @arg LPTIM_Prescaler_DIV4 : Counter Clock = LPTIM Clock / 4
  *     @arg LPTIM_Prescaler_DIV8 : Counter Clock = LPTIM Clock / 8
  *     @arg LPTIM_Prescaler_DIV16 : Counter Clock = LPTIM Clock / 16
  *     @arg LPTIM_Prescaler_DIV32 : Counter Clock = LPTIM Clock / 32
  *     @arg LPTIM_Prescaler_DIV64 : Counter Clock = LPTIM Clock / 64
  *     @arg LPTIM_Prescaler_DIV128 : Counter Clock = LPTIM Clock / 128
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_ConfigPrescaler(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Prescaler) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_CLOCK_PRESCALER(LPTIM_Prescaler));

    /* 获取LPTIMx CFGR 值 */
    tmpreg1 = LPTIMx->CFGR;

    /* 清除 PRESC 位 */
    tmpreg1 &= ~(LPTIM_CFGR_PRESC);

    /* 设置或重置 PRESC 位 */
    tmpreg1 |= LPTIM_Prescaler;

    /* 写入LPTIMx CFGR */
    LPTIMx->CFGR = tmpreg1;
}

/**
  * 简介:  选择计数器的触发源及其极性。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_ExtTRGSource: 选定的外部触发器。
  * 这个参数可以是:
  *     @arg LPTIM_ExtTRGSource_Trig0 : ext_trig0
  *     @arg LPTIM_ExtTRGSource_Trig1 : ext_trig1
  *     @arg LPTIM_ExtTRGSource_Trig2 : ext_trig2
  *     @arg LPTIM_ExtTRGSource_Trig3 : ext_trig3
  *     @arg LPTIM_ExtTRGSource_Trig4 : ext_trig4
  *     @arg LPTIM_ExtTRGSource_Trig5 : ext_trig5
  *     @arg LPTIM_ExtTRGSource_Trig6 : ext_trig6
  *     @arg LPTIM_ExtTRGSource_Trig7 : ext_trig7
  * 
  * 参数:  LPTIM_ExtTRGPolarity: 选定的外部触发器。
  * 这个参数可以是:
  *     @arg LPTIM_ExtTRGPolarity_RisingEdge : 选择的上升沿极性
  *     @arg LPTIM_ExtTRGPolarity_FallingEdge : 选择的下降沿极性
  *     @arg LPTIM_ExtTRGPolarity_BothEdges : 选择了两个边的极性
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_ConfigExternalTrigger(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_ExtTRGSource, uint32_t LPTIM_ExtTRGPolarity) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_EXT_TRG_SOURCE(LPTIM_ExtTRGSource));
    assert_param(IS_LPTIM_EXT_TRG_POLARITY(LPTIM_ExtTRGPolarity));

    /* 获取LPTIMx CFGR 值 */
    tmpreg1 = LPTIMx->CFGR;

    /* 清除 TRIGEN and TRIGSEL 位 */
    tmpreg1 &= CFGR_TRIG_AND_POL_CLEAR_MASK;

    /* 设置或重置 TRIGEN and TRIGSEL 位 */
    tmpreg1 |= (LPTIM_ExtTRGSource | LPTIM_ExtTRGPolarity);

    /* 写入LPTIMx CFGR */
    LPTIMx->CFGR = tmpreg1;
}

/**
  * 简介:  选择计数器的软件启动。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_SelectSoftwareStart(LPTIM_TypeDef* LPTIMx) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));

    /* 重设 TRIGEN bits to allow a software start */
    LPTIMx->CFGR &= ~(LPTIM_CFGR_TRIGEN);
}

/**
  * 简介:  通过确定指定电平的连续样本数来配置触发的数字滤波器，以检测正确的转换。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_TrigSampleTime: 检测一个有效过渡的样本数。
  * 这个参数可以是:
  *     @arg LPTIM_TrigSampleTime_DirectTransistion : 事件在输入转换时被检测到
  *     @arg LPTIM_TrigSampleTime_2Transistions : 在活动电平上连续2次采样后检测到事件
  *     @arg LPTIM_TrigSampleTime_4Transistions : 事件是在活动水平的连续2次采样后检测到的。
  *                                               在活动水平上连续4次采样后检测到事件。
  *     @arg LPTIM_TrigSampleTime_8Transistions : 事件在活动水平的连续8个样本后被检测到。
  *                                               在活动水平上连续8次采样后检测到事件。
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  * 注意:   必须有一个辅助时钟才能使用这一功能。
  */
void LPTIM_ConfigTriggerGlitchFilter(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_TrigSampleTime) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_TRIG_SAMPLE_TIME(LPTIM_TrigSampleTime));

    /* 获取LPTIMx CFGR 值 */
    tmpreg1 = LPTIMx->CFGR;

    /* 清除 TRGFLT 位 */
    tmpreg1 &= ~(LPTIM_CFGR_TRGFLT);

    /* 设置或重置 TRGFLT bits 根据 LPTIM_TrigSampleTime */
    tmpreg1 |= (LPTIM_TrigSampleTime);

    /* 写入LPTIMx CFGR */
    LPTIMx->CFGR = tmpreg1;
}

/**
  * 简介:  通过确定指定级别的连续样本数来配置外部时钟的数字滤波器，以检测正确的转换。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_ClockSampleTime: 检测一个有效过渡的样本数。
  * 这个参数可以是:
  *     @arg LPTIM_ClockSampleTime_DirectTransistion : 事件在输入转换时被检测到
  *     @arg LPTIM_ClockSampleTime_2Transistions : 在活动水平上连续2次采样后检测到事件
  *     @arg LPTIM_ClockSampleTime_4Transistions : 在活动水平上连续4次采样后检测到事件。
  *     @arg LPTIM_ClockSampleTime_8Transistions : 事件在活动水平的连续8个样本后被检测到。
  *                                                在活动水平上连续8次采样后检测到事件。
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  * 注意:   必须有一个辅助时钟才能使用这一功能。
  */
void LPTIM_ConfigClockGlitchFilter(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_ClockSampleTime) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_CLOCK_SAMPLE_TIME(LPTIM_ClockSampleTime));

    /* 获取LPTIMx CFGR 值 */
    tmpreg1 = LPTIMx->CFGR;

    /* 清除 CKFLT 位 */
    tmpreg1 &= ~(LPTIM_CFGR_CKFLT);

    /* 设置或重置 CKFLT bits 根据 LPTIM_ClockSampleTime */
    tmpreg1 |= LPTIM_ClockSampleTime;

    /* 写入LPTIMx CFGR */
    LPTIMx->CFGR = tmpreg1;
}

/**
  * 简介:  选择操作模式。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_Mode: 选择的模式。
  * 这个参数可以是:
  *       @arg LPTIM_Mode_Continuous : 计时器以连续模式启动
  *       @arg LPTIM_Mode_Single : 计时器以单一模式启动
  * 
  * 返回值: 无
  */
void LPTIM_SelectOperatingMode(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Mode) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_MODE(LPTIM_Mode));


    if(LPTIM_Mode == LPTIM_Mode_Continuous) {
        /* 设置 CNTSTRT to select the continuous start*/
        LPTIMx->CR |= LPTIM_Mode_Continuous;
    } else { /*LPTIM_Mode_Single */
        /* 设置 SNGSTRT to select the continuous start*/
        LPTIMx->CR |= LPTIM_Mode_Single;
    }
}

/**
  * 简介:  启用或禁用超时功能。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  NewState: 超时功能的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_TimoutCmd(LPTIM_TypeDef* LPTIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE) {
        /* 设置 TIMOUT 位 */
        LPTIMx->CFGR |= LPTIM_CFGR_TIMOUT;
    } else {
        /* 重设 TIMOUT 位 */
        LPTIMx->CFGR &= ~(LPTIM_CFGR_TIMOUT);
    }
}

/**
  * 简介:  配置波形形状。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_Waveform: 选定的波形形状。
  * 这个参数可以是。
  *     @arg LPTIM_Waveform_PWM_OnePulse : 选择PWM/One Pulse。
  *     @arg LPTIM_Waveform_SetOnce : 选择设置一次。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_ConfigWaveform(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Waveform) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_WAVEFORM(LPTIM_Waveform));

    /* 清除 WAVE 位 */
    LPTIMx->CFGR &= ~(LPTIM_CFGR_CKFLT);

    /* 设置或重置 符合LPTIM_Waveform的 WAVE位 */
    LPTIMx->CFGR |= (LPTIM_Waveform);
}

/**
  * 简介:  配置自动重载和比较寄存器更新模式。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_Update: 选定的更新模式。
  * 这个参数可以是:
  *     @arg LPTIM_Update_Immediate : APB写入后更新的寄存器
  *     @arg LPTIM_Update_EndOfPeriod : 当前计时器预加载结束时更新的寄存器
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_ConfigUpdate(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Update) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_UPDATE(LPTIM_Update));

    /* 清除预加载位 */
    LPTIMx->CFGR &= ~(LPTIM_CFGR_PRELOAD);

    /* 设置或重置 根据 LPTIM_Update 预加载位 */
    LPTIMx->CFGR |= (LPTIM_Update);
}

/**
  * 简介:  将传递的参数写入 Autoreload 寄存器。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_Autoreload: Autoreload值。
  *         此参数的值必须介于 0x0000 和 0xFFFF 之间
  * 
  * 返回值: 无
  */
void LPTIM_SetAutoreloadValue(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Autoreload) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_AUTORELOAD(LPTIM_Autoreload));

    /* 在 Autoreload中写入LPTIM_Autoreload寄存器 */
    LPTIMx->ARR = LPTIM_Autoreload;
}

/**
  * 简介:  将传递的参数写入比较寄存器。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_Compare: 比较值。
  *         此参数的值必须介于 0x0000 和 0xFFFF 之间
  * 
  * 返回值: 无
  */
void LPTIM_SetCompareValue(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_Compare) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_COMPARE(LPTIM_Compare));

    /* 在比较中写入LPTIM_Compare寄存器 */
    LPTIMx->CMP = LPTIM_Compare;
}

/**
  * 简介:  启用或禁用计数器模式。
  *         启用计数器模式后，计数器会在 ULPTIM 上的每个有效事件中递增
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  NewState: 计数器模式的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_SelectCounterMode(LPTIM_TypeDef* LPTIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE) {
        /* 设置 COUNTMODE 位 */
        LPTIMx->CFGR |= LPTIM_CFGR_COUNTMODE;
    } else {
        /* 重设 COUNTMODE 位 */
        LPTIMx->CFGR &= ~(LPTIM_CFGR_COUNTMODE);
    }
}

/**
  * 简介:  启用或禁用编码器模式。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  NewState: 编码器模式的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_SelectEncoderMode(LPTIM_TypeDef* LPTIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE) {
        /* 设置 ENC 位 */
        LPTIMx->CFGR |= LPTIM_CFGR_ENC;
    } else {
        /* 重设 ENC 位 */
        LPTIMx->CFGR &= ~(LPTIM_CFGR_ENC);
    }
}

/**
  * 简介:  获取 LPTIMx 计数器值。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 返回值: 计数器寄存器值
  */
uint32_t LPTIM_GetCounterValue(LPTIM_TypeDef* LPTIMx) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));

    /* 获取Counter 寄存器值 */
    return LPTIMx->CNT;
}

/**
  * 简介:  获取LPTIMx Autoreload值。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 返回值: 计数器寄存器值
  */
uint32_t LPTIM_GetAutoreloadValue(LPTIM_TypeDef* LPTIMx) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));

    /* 获取Counter 寄存器值 */
    return LPTIMx->ARR;
}

/**
  * 简介:  获取 LPTIMx 比较值。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 返回值: 计数器寄存器值
  */
uint32_t LPTIM_GetCompareValue(LPTIM_TypeDef* LPTIMx) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));

    /* 获取Counter 寄存器值 */
    return LPTIMx->CMP;
}

/**
  * 简介:  LPTIM 输入 1 重映射。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_OPTR :
  * 此参数可以是:
  *    @arg LPTIM_OP_PAD_AF  : AF1上的端口B5或AF1上用于输入定时器的端口C0
  *    @arg LPTIM_OP_PAD_PA4 : 输入重新映射到端口A4
  *    @arg RCC_LPTIM1CLKSOURCE_LSI : 输入重新映射到端口B9
  *    @arg LPTIM_OP_TIM_DAC : 来自定时器6输出的输入(用于编码器模式)
  * 
  * 返回值: 计数器寄存器值
  */
void LPTIM_RemapConfig(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_OPTR) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));

    /* 获取Counter 寄存器值 */
    LPTIMx->OR = LPTIM_OPTR;
}


/** @defgroup LPTIM_Group3 中断和标记管理函数
  *  简介    中断和标记管理函数
  *
@verbatim
 ===============================================================================
                  中断和标记管理函数
 ===============================================================================
  本节提供了允许配置LPTIM 中断、获取状态和清除标志位的函数。

  LPTIM提供7个标志和中断源(只有配备编码器模式接口的 LPTIM 外设设备上才有2个标志和干扰源)

  标志和中断源:
  =============================
  1. 比较匹配。
  2. 自动重新加载匹配。
  3. 外部触发事件。
  4. 自动重新加载寄存器写入完成。
  5. 比较寄存器写入完成。
  6. 方向改变:从上到下[仅适用于带编码器模式模块的 LPTIM 外设设备]
  7. 方向改变:从下到上[仅适用于带编码器模式模块的 LPTIM 外设设备]

  - 要启用特定的中断源，请使用"LPTIM_ITConfig"功能。
  - 要检查是否发生了中断，请调用"LPTIM_GetITStatus"函数并读取返回值。
  - 要获取标志状态，请调用"LPTIM_GetFlagStatus"函数并读取返回值。
  - 要清除标志或中断，请使用带有相应标志(中断)的 LPTIM_ClearFlag函数。

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 LPTIM 中断。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_IT: 指定要启用或禁用的 TIM 中断源。
  *         此参数可以是以下值的任意组合:
  *         @arg LPTIM_IT_DOWN: 计数器方向从上到下改变中断源
  *         @arg LPTIM_IT_UP: 计数器方向向下更改为向上中断源
  *         @arg LPTIM_IT_ARROK: 自动重新加载寄存器更新OK中断源
  *         @arg LPTIM_IT_CMPOK: 比较寄存器更新OK中断源
  *         @arg LPTIM_IT_EXTTRIG: 外部触发器边缘事件中断源
  *         @arg LPTIM_IT_ARRM: 自动重新加载匹配中断源
  *         @arg LPTIM_IT_CMPM: 比较匹配中断源
  * 
  * 注意:   LPTIM_IT_DOWN 仅适用于 LPTIM1。
  * 
  * 注意:   LPTIM_IT_UP 仅适用于 LPTIM1。
  * 
  * 参数:  NewState: TIM 中断的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用外设设备才能使用此功能。
  */
void LPTIM_ITConfig(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_IT(LPTIM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE) {
        /* 启用中断源 */
        LPTIMx->IER |= LPTIM_IT;
    } else {
        /* 禁用中断源 */
        LPTIMx->IER &= ~(LPTIM_IT);
    }
}

/**
  * 简介:  检查是否设置了指定的 LPTIM 标志。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_FLAG: 指定要检查的标志。
  *         此参数可以是以下值的任意组合:
  *         @arg LPTIM_FLAG_DOWN: 计数器方向更改向上标志
  *         @arg LPTIM_FLAG_UP: 计数器方向由下变为上标志
  *         @arg LPTIM_FLAG_ARROK: 自动重新加载寄存器更新OK标志
  *         @arg LPTIM_FLAG_CMPOK: 比较寄存器更新OK标志
  *         @arg LPTIM_FLAG_EXTTRIG: 外部触发器边缘事件标志
  *         @arg LPTIM_FLAG_ARRM: 自动重新加载匹配标志
  *         @arg LPTIM_FLAG_CMPM: 比较匹配标志
  * 
  * 注意:   LPTIM_Flag_DOWN 仅为 LPTIM1 生成。
  * 
  * 注意:   LPTIM_Flag_UP 仅为 LPTIM1 生成。
  * 
  * 参数:  NewState: TIM 中断的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
FlagStatus LPTIM_GetFlagStatus(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_FLAG) {
    ITStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_GET_FLAG(LPTIM_FLAG));

    if((LPTIMx->ISR & LPTIM_FLAG) != (RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 LPTIMx 的挂起标志。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_CLEARF: 指定要清除的挂起位。
  *         此参数可以是以下值的任意组合:
  *            @arg LPTIM_CLEARF_DOWN: 计数器方向向上更改清除标志
  *            @arg LPTIM_CLEARF_UP: 计数器方向由下向上变化清除标志
  *            @arg LPTIM_CLEARF_ARROK: 自动重新加载寄存器更新正常清除标志
  *            @arg LPTIM_CLEARF_CMPOK: 比较寄存器更新OK清除标志
  *            @arg LPTIM_CLEARF_EXTTRIG: 外部触发器边缘事件清除标志
  *            @arg LPTIM_CLEARF_ARRM: 自动重新加载匹配清除标志
  *            @arg LPTIM_CLEARF_CMPM: 比较匹配清除标志
  * 
  * 注意:   LPTIM_Flag_DOWN 仅为 LPTIM1 生成。
  * 注意:   LPTIM_Flag_UP 仅为 LPTIM1 生成。
  * 
  * 返回值: 无
  */
void LPTIM_ClearFlag(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_CLEARF) {
    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_CLEAR_FLAG(LPTIM_CLEARF));

    /* 清除 IT pending 位 */
    LPTIMx->ICR |= LPTIM_CLEARF;
}

/**
  * 简介:  检查指定的 LPTIM 中断是否发生。
  * 
  * 参数:  LPTIMx: 其中 x 可以是1。
  * 
  * 参数:  LPTIM_IT: 指定要检查的 LPTIM 中断源。
  *            @arg LPTIM_IT_DOWN: 计数器方向从上到下改变中断源
  *            @arg LPTIM_IT_UP: 计数器方向向下更改为向上中断源
  *            @arg LPTIM_IT_ARROK: 自动重新加载寄存器更新OK中断源
  *            @arg LPTIM_IT_CMPOK: 比较寄存器更新OK中断源
  *            @arg LPTIM_IT_EXTTRIG: 外部触发器边缘事件中断源
  *            @arg LPTIM_IT_ARRM: 自动重新加载匹配中断源
  *            @arg LPTIM_IT_CMPM: 比较匹配中断源
  * 
  * 返回值: LPTIM_IT 的新状态(SET 或 RESET)。
  */
ITStatus LPTIM_GetITStatus(LPTIM_TypeDef* LPTIMx, uint32_t LPTIM_IT) {
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    /* 检查参数 */
    assert_param(IS_LPTIM_ALL_PERIPH(LPTIMx));
    assert_param(IS_LPTIM_IT(LPTIM_IT));

    /* 获取中断状态位值 */
    itstatus = LPTIMx->ISR & LPTIM_IT;

    /* 检查中断是否已启用 */
    itenable = LPTIMx->IER & LPTIM_IT;

    if((itstatus != RESET) && (itenable != RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}


#endif /* STM32F410xx || STM32F413_423xx */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

