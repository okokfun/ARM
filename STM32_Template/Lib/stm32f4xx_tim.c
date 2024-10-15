/**
  ******************************************************************************
  * 文件:    stm32f4xx_tim.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能，以管理TIM 外设设备的以下功能:
  *            + TimeBase管理
  *            + 输出比较管理
  *            + 输入捕获管理
  *            + 高级控制定时器(TIM1 和 TIM8)特定功能
  *            + 中断、DMA 和标志管理
  *            + 时钟管理
  *            + 同步管理
  *            + 具体接口管理
  *            + 特定重新映射管理
  *
  @verbatim
 ===============================================================================
                   #####  如何使用这个驱动程序 #####
 ===============================================================================
    [..]
    此驱动程序提供配置和编程所有 STM32F4xx 设备的 TIM 的功能。
    这些功能分为9组:

      (#) TIM 时基管理: 该组包括配置 TIM 时基单元所需的所有功能:
        (++) 设置/获取预分频器
        (++) 设置/获取自动重新加载
        (++) 计数器模式配置
        (++) 设置时钟分区
        (++) 选择单脉冲模式
        (++) 更新请求配置
        (++) 更新禁用配置
        (++) 自动预加载配置
        (++) 启用/禁用计数器

      (#) TIM 输出比较管理: 该组包括配置输出比较模式中使用的捕获/比较单元所需的所有功能:
        (++) 在输出比较模式下独立配置每个通道
        (++) 选择输出比较模式
        (++) 选择每个通道的极性
        (++) 设置/获取捕获/比较寄存器值
        (++) 选择输出比较快速模式
        (++) 选择输出比较强制模式
        (++) 输出比较预加载配置
        (++) 清除输出比较参考
        (++) 选择OCREF Clear信号
        (++) 启用/禁用捕获/比较通道

      (#) TIM 输入捕获管理: 该组包括配置输入捕获模式中使用的捕获/比较单元所需的所有功能:
        (++) 在输入捕获模式下配置每个通道
        (++) 在 PWM 输入模式下配置通道1/2
        (++) 设置输入捕获预分频器
        (++) 获取捕获/比较值

      (#) 高级控制定时器(TIM1 和 TIM8)特定功能
        (++) 配置中断输入、停滞时间、锁定级别、OSSI、OSSR 状态和 AOE(自动输出启用)
        (++) 启用/禁用 TIM 外设设备主输出
        (++) 选择换向事件
        (++) 设置/重置捕获比较预加载控制位

      (#) TIM 中断、DMA 和标志管理
        (++) 启用/禁用中断源
        (++) 获取标志状态
        (++) 清除标志/挂起位
        (++) 启用/禁用 DMA 请求
        (++) 配置 DMA 突发模式
        (++) 选择 CaptureCompare DMA 请求

      (#) TIM 时钟管理: 该组包括配置时钟控制器单元所需的所有功能:
        (++)选择内部/外部时钟
        (++)选择外部时钟模式: ETR(模式1/模式2)、TIx 或 ITRx

      (#) TIM 同步管理: 该组包括配置同步单元所需的所有功能:
        (++) 选择输入触发器
        (++) 选择输出触发器
        (++) 选择主从模式
        (++) 用作外部触发器时的 ETR 配置

      (#) TIM 特定接口管理，该组包括使用特定 TIM 接口所需的所有功能:
        (++) 编码器接口配置
        (++) 选择霍尔传感器

      (#) TIM 特定的重新映射管理包括特定定时器的重新映射配置

  @endverbatim
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
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup TIM
  * 简介: TIM 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* ---------------------- TIM寄存器位掩码 ------------------------ */
#define SMCR_ETR_MASK      ((uint16_t)0x00FF)
#define CCMR_OFFSET        ((uint16_t)0x0018)
#define CCER_CCE_SET       ((uint16_t)0x0001)
#define	CCER_CCNE_SET      ((uint16_t)0x0004)
#define CCMR_OC13M_MASK    ((uint16_t)0xFF8F)
#define CCMR_OC24M_MASK    ((uint16_t)0x8FFF)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI3_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);
static void TI4_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter);

/* 私有函数 ---------------------------------------------------------*/

/** @defgroup TIM_Private_Functions
  */

/** @defgroup TIM_Group1 TimeBase 管理功能
 *  简介   TimeBase 管理功能
 *
@verbatim
 ===============================================================================
                     ##### TimeBase 管理功能 #####
 ===============================================================================


            ##### TIM 驱动程序: 如何在计时(时基)模式下使用 #####
 ===============================================================================
    [..]
    要在定时(时基)模式下使用计时器，必须执行以下步骤:
        (#) 使用 RCC_APBxPeriphClockCmd(RCC_ABPxPeriph-TIMx，Enable) 函数启用 TIM 时钟

        (#) 用所需参数填充 TIM_TimeBaseInitStruct。

        (#) 调用 TIM_TimeBaseInit(TIMx，&TIM_TimeBaseInitStruct) 配置时基单元具有相应的配置

        (#) 如果需要生成更新中断，则启用 NVIC。

        (#) 使用函数 TIM_ITConfig(TIMx，TIM_IT_Update) 启用相应的中断

        (#) 调用 TIM_Cmd(ENABLE) 函数以启用 TIM 计数器。

       -@- 如果需要，可以单独使用所有其他函数来修改计时器的特定功能。

@endverbatim
  */

/**
  * 简介:  将 TIMx 外设寄存器去初始化为其默认复位值。
  * 
  * 参数:  TIMx: 其中 x 可以是 1 到 14，以选择 TIM 外设设备。
  * 
  * 返回值: 无
  */
void TIM_DeInit(TIM_TypeDef* TIMx) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    if (TIMx == TIM1) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);
    } else if (TIMx == TIM2) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
    } else if (TIMx == TIM3) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
    } else if (TIMx == TIM4) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
    } else if (TIMx == TIM5) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, DISABLE);
    } else if (TIMx == TIM6) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
    } else if (TIMx == TIM7) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
    } else if (TIMx == TIM8) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, DISABLE);
    } else if (TIMx == TIM9) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM9, DISABLE);
    } else if (TIMx == TIM10) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM10, DISABLE);
    } else if (TIMx == TIM11) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM11, DISABLE);
    } else if (TIMx == TIM12) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM12, DISABLE);
    } else if (TIMx == TIM13) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM13, DISABLE);
    } else {
        if (TIMx == TIM14) {
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, ENABLE);
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM14, DISABLE);
        }
    }
}

/**
  * 简介:  根据 TIM_TimeBaseInitStruct 中指定的参数初始化 TIMx 时基单元外设。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，用于选择 TIM 外设设备。
  * 参数:  TIM_TimeBaseInitStruct: 指向 TIM_TimeBaseInitTypeDef 结构的指针。
  *            该结构包含指定 TIM 外设的配置信息。
  * 返回值: 无
  */
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct) {
    uint16_t tmpcr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
    assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));

    tmpcr1 = TIMx->CR1;

    if((TIMx == TIM1) || (TIMx == TIM8) ||
            (TIMx == TIM2) || (TIMx == TIM3) ||
            (TIMx == TIM4) || (TIMx == TIM5)) {
        /* 选择这个计数器模式 */
        tmpcr1 &= (uint16_t)(~(TIM_CR1_DIR | TIM_CR1_CMS));
        tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_CounterMode;
    }

    if((TIMx != TIM6) && (TIMx != TIM7)) {
        /* 设置时钟分频 */
        tmpcr1 &=  (uint16_t)(~TIM_CR1_CKD);
        tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision;
    }

    TIMx->CR1 = tmpcr1;

    /* 设置 Autoreload 值 */
    TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;

    /* 设置预分频器值 */
    TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;

    if ((TIMx == TIM1) || (TIMx == TIM8)) {
        /* 设置重复计数器值 */
        TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
    }

    /* 生成更新事件以立即重新加载预分频器和重复计数器（仅适用于 TIM1 和 TIM8）值 */
    TIMx->EGR = TIM_PSCReloadMode_Immediate;
}

/**
  * 简介:  用每个 TIM_TimeBaseInitStruct 成员的默认值填充其默认值。
  * 参数:  TIM_TimeBaseInitStruct : 指向将被初始化的 TIM_TimeBaseInitTypeDef 结构的指针。
  * 返回值: 无
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct) {
    /* 设置默认配置 */
    TIM_TimeBaseInitStruct->TIM_Period = 0xFFFFFFFF;
    TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
    TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

/**
  * 简介:  配置 TIMx 预分频器。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 参数:  Prescaler: 指定预分频器寄存器的值
  * 参数:  TIM_PSCReloadMode: 指定 TIM 预分频器重新加载模式。
  *          此参数可以是以下值之一:
  *            @arg TIM_PSCReloadMode_Update: 预分频器在更新事件中被加载。
  *            @arg TIM_PSCReloadMode_Immediate: 预分频器立即被加载。
  * 返回值: 无
  */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));
    /* 设置预分频器值 */
    TIMx->PSC = Prescaler;
    /* 设置或重置 UG 位 */
    TIMx->EGR = TIM_PSCReloadMode;
}

/**
  * 简介:  指定要使用的 TIMx 计数器模式。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_CounterMode: 指明计数器要使用的模式
  *          此参数可以是以下值之一:
  *            @arg TIM_CounterMode_Up: TIM 向上计数模式
  *            @arg TIM_CounterMode_Down: TIM 向下计数模式
  *            @arg TIM_CounterMode_CenterAligned1: TIM 中心对齐模式1
  *            @arg TIM_CounterMode_CenterAligned2: TIM 中心对齐模式2
  *            @arg TIM_CounterMode_CenterAligned3: TIM 中心对齐模式3
  * 返回值: 无
  */
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode) {
    uint16_t tmpcr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));

    tmpcr1 = TIMx->CR1;

    /* 重设 CMS and DIR 位 */
    tmpcr1 &= (uint16_t)~(TIM_CR1_DIR | TIM_CR1_CMS);

    /* 设置计数器模式 */
    tmpcr1 |= TIM_CounterMode;

    /* 写入 TIMx CR1 寄存器 */
    TIMx->CR1 = tmpcr1;
}

/**
  * 简介:  设置 TIMx 计数器寄存器值。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 参数:  Counter: 指明计数器寄存器的新值。
  * 返回值: 无
  */
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* 设置计数器寄存器值 */
    TIMx->CNT = Counter;
}

/**
  * 简介:  设置 TIMx 自动重新加载寄存器值。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 参数:  Autoreload: 指定自动加载寄存器的新值。
  * 返回值: 无
  */
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* 设置自动加载寄存器值 */
    TIMx->ARR = Autoreload;
}

/**
  * 简介:  获取 TIMx 计数器值。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 返回值: 计数器寄存器值
  */
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* 获取计数器寄存器的值 */
    return TIMx->CNT;
}

/**
  * 简介:  获取 TIMx 预分频器值。
  * 参数:  TIMx: 其中 x 可以是 1 到14，用于选择 TIM 外设设备。
  * 返回值: 预分频器寄存器的值。
  */
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* 获取预分频器寄存器的值 */
    return TIMx->PSC;
}

/**
  * 简介:  启用或禁用 TIMx 更新事件。
  * 参数:  TIMx: 其中 x 可以是 1 到14，用于选择 TIM 外设设备。
  * 参数:  NewState: TIMx UDIS 位的新状态
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置更新禁用位*/
        TIMx->CR1 |= TIM_CR1_UDIS;
    } else {
        /* 重设更新禁用 位 */
        TIMx->CR1 &= (uint16_t)~TIM_CR1_UDIS;
    }
}

/**
  * 简介:  配置 TIMx 更新请求中断源。
  * 参数:  TIMx: 其中 x 可以是 1 到14，用于选择 TIM 外设设备。
  * 参数:  TIM_UpdateSource: 指定更新源。
  *          此参数可以是以下值之一:
  *            @arg TIM_UpdateSource_Global: 更新源是计数器溢出/下溢或 UG 位的设置，
  *                                             或通过从模式控制器生成的更新。
  *            @arg TIM_UpdateSource_Regular: 更新源为计数器溢出/下溢。
  * 返回值: 无
  */
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint16_t TIM_UpdateSource) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));

    if (TIM_UpdateSource != TIM_UpdateSource_Global) {
        /* 设置 URS 位 */
        TIMx->CR1 |= TIM_CR1_URS;
    } else {
        /* 重设 URS 位 */
        TIMx->CR1 &= (uint16_t)~TIM_CR1_URS;
    }
}

/**
  * 简介:  启用或禁用 ARR 上的 TIMx 外设预加载寄存器。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，用于选择 TIM 外设设备。
  * 参数:  NewState: TIMx 外围预加载寄存器的新状态
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 ARR 预加载位 */
        TIMx->CR1 |= TIM_CR1_ARPE;
    } else {
        /* 重设 ARR 预加载位 */
        TIMx->CR1 &= (uint16_t)~TIM_CR1_ARPE;
    }
}

/**
  * 简介:  选择 TIMx 的单脉冲模式。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，用于选择 TIM 外设设备。
  * 参数:  TIM_OPMode: 指定要使用的 OPM 模式。
  *          此参数可以是以下值之一:
  *            @arg TIM_OPMode_Single
  *            @arg TIM_OPMode_Repetitive
  * 返回值: 无
  */
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint16_t TIM_OPMode) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_OPM_MODE(TIM_OPMode));

    /* 重设 OPM 位 */
    TIMx->CR1 &= (uint16_t)~TIM_CR1_OPM;

    /* 配置 OPM Mode */
    TIMx->CR1 |= TIM_OPMode;
}

/**
  * 简介:  设置 TIMx 时钟分频值。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，6 和 7 除外，以选择 TIM 外设设备。
  * 参数:  TIM_CKD: 指定时钟分割值。
  *          该参数可以是以下值之一:
  *            @arg TIM_CKD_DIV1: TDTS = Tck_tim
  *            @arg TIM_CKD_DIV2: TDTS = 2*Tck_tim
  *            @arg TIM_CKD_DIV4: TDTS = 4*Tck_tim
  * 返回值: 无
  */
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint16_t TIM_CKD) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_CKD_DIV(TIM_CKD));

    /* 重设 CKD 位 */
    TIMx->CR1 &= (uint16_t)(~TIM_CR1_CKD);

    /* 设置 CKD 值 */
    TIMx->CR1 |= TIM_CKD;
}

/**
  * 简介:  启用或禁用指定的 TIM 外设。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，以选择 TIMx 外设。
  * 参数:  NewState: TIMx 外设的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 TIM 计数器 */
        TIMx->CR1 |= TIM_CR1_CEN;
    } else {
        /* 禁用 TIM 计数器 */
        TIMx->CR1 &= (uint16_t)~TIM_CR1_CEN;
    }
}

/** @defgroup TIM_Group2 输出比较管理功能
 *  简介    输出比较管理功能
 *
@verbatiM 输出比较管理
 ===============================================================================
              ##### 输出比较管理功能 #####
 ===============================================================================


        ##### TIM 驱动程序:如何在输出比较模式中使用它 #####
 ===============================================================================
    [..]
    要在输出比较模式下使用计时器，必须执行以下步骤:

      (#) 使用 RCC_APBxPeriphClockCmd(RCC_ABPxPeriph-TIMx，Enable) 函数启用 TIM 时钟

      (#) 通过配置相应的 GPIO 引脚来配置 TIM 引脚

      (#) 如本驱动程序第一部分所述配置时基单位，
        (++) 如果需要，否则定时器将以默认配置运行:
            自动重新加载值=0xFFFF
        (++) 预分频器值=0x0000
        (++) 计数器模式=递增计数
        (++) 时钟分区=TIM_CKD_DIV1

      (#) 用所需参数填充 TIM_OCInitStruct，包括:
        (++) TIM 输出比较模式: TIM_OC 模式
        (++) TIM 输出状态: TIM_OutputState
        (++) TIM 脉冲值: TIM_Pulse
        (++) TIM 输出比较极性: TIM_OC 极性

      (#) 调用 TIM_OCxInit(TIMx，&TIM_OCInitStruct)，用相应的配置配置所需的通道

      (#) 调用 TIM_Cmd(ENABLE) 函数以启用 TIM 计数器。

      -@- 如果需要，可以单独使用所有其他功能来修改计时器的特定功能。

      -@- 在 PWM模式下，此功能是必需的: TIM_OCxPreloadConfig(TIMx，TIM_OCPreload_ENABLE);

      -@- 如果需要相应的中断或 DMA 请求，用户应:
        (+@) 启用 NVIC(或 DMA)以使用 TIM 中断(或 DMA 请求)。
        (+@) 使用功能 TIM_ITConfig(TIMx，TIM_IT_CCx)
        (或 TIM_DMA_Cmd(TIMx，TIM_DMA _CCx)) 启用相应的中断(或 DMA 请求)

@endverbatim
  */

/**
  * 简介:  根据 TIM_OCInitStruct 中指定的参数初始化 TIMx 通道 1。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，6 和 7 除外，以选择 TIM 外设设备。
  * 参数:  TIM_OCInitStruct: 指向 TIM_OCInitTypeDef 结构的指针，该结构包含指定 TIM 外设设备的配置信息。
  * 返回值: 无
  */
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct) {
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* 禁用通道 1: 重设 CC1E 位 */
    TIMx->CCER &= (uint16_t)~TIM_CCER_CC1E;

    /* 获取TIMx CCER 寄存器的值 */
    tmpccer = TIMx->CCER;
    /* 获取TIMx CR2寄存器的值 */
    tmpcr2 =  TIMx->CR2;

    /* 获取TIMx CCMR1 寄存器值 */
    tmpccmrx = TIMx->CCMR1;

    /* 重设 选择输出比较模式位 */
    tmpccmrx &= (uint16_t)~TIM_CCMR1_OC1M;
    tmpccmrx &= (uint16_t)~TIM_CCMR1_CC1S;
    /* 选择输出比较模式 */
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;

    /* 重设输出极性水平 */
    tmpccer &= (uint16_t)~TIM_CCER_CC1P;
    /* 设置输出比较极性 */
    tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;

    /* 设置输出状态 */
    tmpccer |= TIM_OCInitStruct->TIM_OutputState;

    if((TIMx == TIM1) || (TIMx == TIM8)) {
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

        /* 重设 Output N Polarity level */
        tmpccer &= (uint16_t)~TIM_CCER_CC1NP;
        /* 设置 Output N Polarity */
        tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;
        /* 重设 Output N State */
        tmpccer &= (uint16_t)~TIM_CCER_CC1NE;

        /* 设置 Output N State */
        tmpccer |= TIM_OCInitStruct->TIM_OutputNState;
        /* 重设输出比较和输出比较 N 空闲状态 */
        tmpcr2 &= (uint16_t)~TIM_CR2_OIS1;
        tmpcr2 &= (uint16_t)~TIM_CR2_OIS1N;
        /* 设置 Output Idle state */
        tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
        /* 设置输出N空闲状态 */
        tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
    }

    /* 写入 TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* 写入 TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmrx;

    /* 设置捕获比较寄存器的值 */
    TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;

    /* 写入 TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  根据 TIM_OCInitStruct 中的指定参数初始化 TIMx 通道2。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_OCInitStruct: 指向 TIM_OCInitTypeDef 结构的指针，该结构包含指定 TIM 外设设备的配置信息。
  * 返回值: 无
  */
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct) {
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* 禁用通道 2: 重设 CC2E 位 */
    TIMx->CCER &= (uint16_t)~TIM_CCER_CC2E;

    /* 获取TIMx CCER 寄存器的值 */
    tmpccer = TIMx->CCER;
    /* 获取TIMx CR2寄存器的值 */
    tmpcr2 =  TIMx->CR2;

    /* 获取TIMx CCMR1 寄存器值 */
    tmpccmrx = TIMx->CCMR1;

    /* 重设输出比较模式和捕获/比较选择位 */
    tmpccmrx &= (uint16_t)~TIM_CCMR1_OC2M;
    tmpccmrx &= (uint16_t)~TIM_CCMR1_CC2S;

    /* 选择输出比较模式 */
    tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);

    /* 重设输出极性水平 */
    tmpccer &= (uint16_t)~TIM_CCER_CC2P;
    /* 设置输出比较极性 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);

    /* 设置输出状态 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 4);

    if((TIMx == TIM1) || (TIMx == TIM8)) {
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

        /* 重设 Output N Polarity level */
        tmpccer &= (uint16_t)~TIM_CCER_CC2NP;
        /* 设置 Output N Polarity */
        tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 4);
        /* 重设 Output N State */
        tmpccer &= (uint16_t)~TIM_CCER_CC2NE;

        /* 设置 Output N State */
        tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 4);
        /* 重设输出比较和输出比较 N 空闲状态 */
        tmpcr2 &= (uint16_t)~TIM_CR2_OIS2;
        tmpcr2 &= (uint16_t)~TIM_CR2_OIS2N;
        /* 设置 Output Idle state */
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 2);
        /* 设置输出N空闲状态 */
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
    }

    /* 写入 TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* 写入 TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmrx;

    /* 设置捕获比较寄存器的值 */
    TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;

    /* 写入 TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  根据 TIM_OCInitStruct 中指定的参数初始化 TIMx 通道 3。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCInitStruct: 指向 TIM_OCInitTypeDef 结构的指针，该结构包含指定 TIM 外设设备的配置信息。
  * 返回值: 无
  */
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct) {
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* 禁用通道 3: 重设 CC2E 位 */
    TIMx->CCER &= (uint16_t)~TIM_CCER_CC3E;

    /* 获取TIMx CCER 寄存器的值 */
    tmpccer = TIMx->CCER;
    /* 获取TIMx CR2寄存器的值 */
    tmpcr2 =  TIMx->CR2;

    /* 获取TIMx CCMR2寄存器的值 */
    tmpccmrx = TIMx->CCMR2;

    /* 重设输出比较模式和捕获/比较选择位 */
    tmpccmrx &= (uint16_t)~TIM_CCMR2_OC3M;
    tmpccmrx &= (uint16_t)~TIM_CCMR2_CC3S;
    /* 选择输出比较模式 */
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;

    /* 重设输出极性水平 */
    tmpccer &= (uint16_t)~TIM_CCER_CC3P;
    /* 设置输出比较极性 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 8);

    /* 设置输出状态 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 8);

    if((TIMx == TIM1) || (TIMx == TIM8)) {
        assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
        assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
        assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

        /* 重设 Output N Polarity level */
        tmpccer &= (uint16_t)~TIM_CCER_CC3NP;
        /* 设置 Output N Polarity */
        tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 8);
        /* 重设 Output N State */
        tmpccer &= (uint16_t)~TIM_CCER_CC3NE;

        /* 设置 Output N State */
        tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 8);
        /* 重设输出比较和输出比较 N 空闲状态 */
        tmpcr2 &= (uint16_t)~TIM_CR2_OIS3;
        tmpcr2 &= (uint16_t)~TIM_CR2_OIS3N;
        /* 设置 Output Idle state */
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 4);
        /* 设置输出N空闲状态 */
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
    }

    /* 写入 TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* 写入 TIMx CCMR2 */
    TIMx->CCMR2 = tmpccmrx;

    /* 设置捕获比较寄存器的值 */
    TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;

    /* 写入 TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  根据 TIM_OCInitStruct 中指定的参数初始化 TIMx 通道 4。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCInitStruct: 指向 TIM_OCInitTypeDef 结构的指针，该结构包含指定 TIM 外设设备的配置信息。
  * 返回值: 无
  */
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct) {
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
    assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));

    /* 禁用通道 4: 重设 CC4E 位 */
    TIMx->CCER &= (uint16_t)~TIM_CCER_CC4E;

    /* 获取TIMx CCER 寄存器的值 */
    tmpccer = TIMx->CCER;
    /* 获取TIMx CR2寄存器的值 */
    tmpcr2 =  TIMx->CR2;

    /* 获取TIMx CCMR2寄存器的值 */
    tmpccmrx = TIMx->CCMR2;

    /* 重设输出比较模式和捕获/比较选择位 */
    tmpccmrx &= (uint16_t)~TIM_CCMR2_OC4M;
    tmpccmrx &= (uint16_t)~TIM_CCMR2_CC4S;

    /* 选择输出比较模式 */
    tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);

    /* 重设输出极性水平 */
    tmpccer &= (uint16_t)~TIM_CCER_CC4P;
    /* 设置输出比较极性 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);

    /* 设置输出状态 */
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 12);

    if((TIMx == TIM1) || (TIMx == TIM8)) {
        assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
        /* 重设 Output Compare IDLE State */
        tmpcr2 &= (uint16_t) ~TIM_CR2_OIS4;
        /* 设置 Output Idle state */
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
    }

    /* 写入 TIMx CR2 */
    TIMx->CR2 = tmpcr2;

    /* 写入 TIMx CCMR2 */
    TIMx->CCMR2 = tmpccmrx;

    /* 设置捕获比较寄存器的值 */
    TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;

    /* 写入 TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  用其默认值填充每个 TIM_OCInitStruct 成员。
  * 参数:  TIM_OCInitStruct: 指向将被初始化的 TIM_OCInitTypeDef 结构的指针。
  * 返回值: 无
  */
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct) {
    /* 设置默认配置 */
    TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStruct->TIM_Pulse = 0x00000000;
    TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/**
  * 简介:  选择 TIM 输出比较模式。
  * 注意:   该函数在改变输出比较模式前禁用所选通道。如果需要，
  *             用户必须使用 TIM_CCxCmd() 和 TIM_CCxNCmd() 函数启用该通道。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，6 和 7 除外，以选择 TIM 外设设备。
  * 参数:  TIM_Channel: 指定 TIM 通道
  *          此参数可以是以下值之一:
  *            @arg TIM_Channel_1: TIM 通道 1
  *            @arg TIM_Channel_2: TIM 通道 2
  *            @arg TIM_Channel_3: TIM 通道 3
  *            @arg TIM_Channel_4: TIM 通道 4
  * 参数:  TIM_OCMode: 指定 TIM 输出比较模式。
  *           此参数可以是以下值之一:
  *            @arg TIM_OCMode_Timing
  *            @arg TIM_OCMode_Active
  *            @arg TIM_OCMode_Toggle
  *            @arg TIM_OCMode_PWM1
  *            @arg TIM_OCMode_PWM2
  *            @arg TIM_ForcedAction_Active
  *            @arg TIM_ForcedAction_InActive
  * 返回值: 无
  */
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode) {
    uint32_t tmp = 0;
    uint16_t tmp1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_CHANNEL(TIM_Channel));
    assert_param(IS_TIM_OCM(TIM_OCMode));

    tmp = (uint32_t) TIMx;
    tmp += CCMR_OFFSET;

    tmp1 = CCER_CCE_SET << (uint16_t)TIM_Channel;

    /* 禁用 Channel: 重设 CCxE 位 */
    TIMx->CCER &= (uint16_t) ~tmp1;

    if((TIM_Channel == TIM_Channel_1) || (TIM_Channel == TIM_Channel_3)) {
        tmp += (TIM_Channel >> 1);

        /* 重设 OCxM bits in the CCMRx 寄存器 */
        *(__IO uint32_t *) tmp &= CCMR_OC13M_MASK;

        /* 配置 OCxM bits in the CCMRx 寄存器 */
        *(__IO uint32_t *) tmp |= TIM_OCMode;
    } else {
        tmp += (uint16_t)(TIM_Channel - (uint16_t)4) >> (uint16_t)1;

        /* 重设 OCxM bits in the CCMRx 寄存器 */
        *(__IO uint32_t *) tmp &= CCMR_OC24M_MASK;

        /* 配置 OCxM bits in the CCMRx 寄存器 */
        *(__IO uint32_t *) tmp |= (uint16_t)(TIM_OCMode << 8);
    }
}

/**
  * 简介:  设置 TIMx 捕获比较1 寄存器值。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，6 和 7 除外，以选择 TIM 外设设备。
  * 参数:  Compare1: 指定捕获比较 1 寄存器的新值。
  * 返回值: 无
  */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));

    /* 设置捕获比较1 寄存器的值 */
    TIMx->CCR1 = Compare1;
}

/**
  * 简介:  设置 TIMx 捕获比较 2 寄存器值。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  Compare2: 指定捕获比较2寄存器的新值。
  * 返回值: 无
  */
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* 设置捕获比较2寄存器的值 */
    TIMx->CCR2 = Compare2;
}

/**
  * 简介:  设置 TIMx 捕获比较3 寄存器值。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5 或 8，以选择 TIM 外设设备。
  * 参数:  Compare3: 指定捕获比较 3 寄存器的新值。
  * 返回值: 无
  */
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* 设置捕获比较3 寄存器的值 */
    TIMx->CCR3 = Compare3;
}

/**
  * 简介:  设置 TIMx 捕获比较 4 寄存器值。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5 或 8，以选择 TIM 外设设备。
  * 参数:  Compare4: 指定捕获比较4 寄存器的新值。
  * 返回值: 无
  */
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* 设置捕获比较4 寄存器的值 */
    TIMx->CCR4 = Compare4;
}

/**
  * 简介:  强制 TIMx 输出 1 波形达到活动或非活动电平。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，6 和 7 除外，以选择 TIM 外设设备。
  * 参数:  TIM_ForcedAction: 指定要设置为输出波形的强制动作。
  *          此参数可以是以下值之一:
  *            @arg TIM_ForcedAction_Active: OC1REF 上的强制激活级别
  *            @arg TIM_ForcedAction_InActive: 强制 OC1REF 处于非活动状态。
  * 返回值: 无
  */
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction) {
    uint16_t tmpccmr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr1 = TIMx->CCMR1;

    /* 重设 OC1M 位 */
    tmpccmr1 &= (uint16_t)~TIM_CCMR1_OC1M;

    /* 配置强制输出模式 */
    tmpccmr1 |= TIM_ForcedAction;

    /* 写入 TIMx CCMR1 寄存器 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * 简介:  强制 TIMx 输出 2 波形达到活动或非活动电平。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5、8、9 或 12，以选择 TIM 外设设备。
  * 参数:  TIM_ForcedAction: 指定要设置为输出波形的强制动作。
  *          此参数可以是以下值之一:
  *            @arg TIM_ForcedAction_Active: OC2REF上的强制激活级别
  *            @arg TIM_ForcedAction_InActive: 强制 OC2REF 处于非活动状态。
  * 返回值: 无
  */
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction) {
    uint16_t tmpccmr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr1 = TIMx->CCMR1;

    /* 重设 OC2M 位 */
    tmpccmr1 &= (uint16_t)~TIM_CCMR1_OC2M;

    /* 配置强制输出模式 */
    tmpccmr1 |= (uint16_t)(TIM_ForcedAction << 8);

    /* 写入 TIMx CCMR1 寄存器 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * 简介:  强制 TIMx 输出 3 波形达到活动或非活动电平。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5 或 8，以选择 TIM 外设设备。
  * 参数:  TIM_ForcedAction: 指定要设置为输出波形的强制动作。
  *          此参数可以是以下值之一:
  *            @arg TIM_ForcedAction_Active: OC3REF 上的强制激活级别
  *            @arg TIM_ForcedAction_InActive: 强制 OC3REF 处于非活动状态。
  * 返回值: 无
  */
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction) {
    uint16_t tmpccmr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));

    tmpccmr2 = TIMx->CCMR2;

    /* 重设 OC1M 位 */
    tmpccmr2 &= (uint16_t)~TIM_CCMR2_OC3M;

    /* 配置强制输出模式 */
    tmpccmr2 |= TIM_ForcedAction;

    /* 写入 TIMx CCMR2 寄存器 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * 简介:  强制 TIMx 输出 4 波形达到活动或非活动电平。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5 或 8，以选择 TIM 外设设备。
  * 参数:  TIM_ForcedAction: 指定要设置为输出波形的强制动作。
  *          此参数可以是以下值之一:
  *            @arg TIM_ForcedAction_Active: OC4REF 上的强制激活级别
  *            @arg TIM_ForcedAction_InActive: 强制 OC4REF 上的非活动级别。
  * 返回值: 无
  */
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint16_t TIM_ForcedAction) {
    uint16_t tmpccmr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
    tmpccmr2 = TIMx->CCMR2;

    /* 重设 OC2M 位 */
    tmpccmr2 &= (uint16_t)~TIM_CCMR2_OC4M;

    /* 配置强制输出模式 */
    tmpccmr2 |= (uint16_t)(TIM_ForcedAction << 8);

    /* 写入 TIMx CCMR2 寄存器 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * 简介:  启用或禁用 CCR1 上的 TIMx 外设预加载寄存器。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，6 和 7 除外，以选择 TIM 外设设备。
  * 参数:  TIM_OCPreload: TIMx 外围预加载寄存器的新状态
  *          此参数可以是以下值之一:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * 返回值: 无
  */
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) {
    uint16_t tmpccmr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr1 = TIMx->CCMR1;

    /* 重设 OC1PE 位 */
    tmpccmr1 &= (uint16_t)(~TIM_CCMR1_OC1PE);

    /* 启用或禁用输出比较预加载功能 */
    tmpccmr1 |= TIM_OCPreload;

    /* 写入 TIMx CCMR1 寄存器 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * 简介:  启用或禁用 CCR2 上的 TIMx 外设预加载寄存器。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_OCPreload: TIMx 外围预加载寄存器的新状态
  *          此参数可以是以下值之一:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * 返回值: 无
  */
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) {
    uint16_t tmpccmr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr1 = TIMx->CCMR1;

    /* 重设 OC2PE 位 */
    tmpccmr1 &= (uint16_t)(~TIM_CCMR1_OC2PE);

    /* 启用或禁用输出比较预加载功能 */
    tmpccmr1 |= (uint16_t)(TIM_OCPreload << 8);

    /* 写入 TIMx CCMR1 寄存器 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * 简介:  启用或禁用 CCR3 上的 TIMx 外设预加载寄存器。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCPreload: TIMx 外围预加载寄存器的新状态
  *          此参数可以是以下值之一:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * 返回值: 无
  */
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) {
    uint16_t tmpccmr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr2 = TIMx->CCMR2;

    /* 重设 OC3PE 位 */
    tmpccmr2 &= (uint16_t)(~TIM_CCMR2_OC3PE);

    /* 启用或禁用输出比较预加载功能 */
    tmpccmr2 |= TIM_OCPreload;

    /* 写入 TIMx CCMR2 寄存器 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * 简介:  启用或禁用 CCR4 上的 TIMx 外设预加载寄存器。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCPreload: TIMx 外围预加载寄存器的新状态
  *          此参数可以是以下值之一:
  *            @arg TIM_OCPreload_Enable
  *            @arg TIM_OCPreload_Disable
  * 返回值: 无
  */
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload) {
    uint16_t tmpccmr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

    tmpccmr2 = TIMx->CCMR2;

    /* 重设 OC4PE 位 */
    tmpccmr2 &= (uint16_t)(~TIM_CCMR2_OC4PE);

    /* 启用或禁用输出比较预加载功能 */
    tmpccmr2 |= (uint16_t)(TIM_OCPreload << 8);

    /* 写入 TIMx CCMR2 寄存器 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * 简介:  配置 TIMx 输出比较 1 快速功能。
  * 参数:  TIMx: 其中 x 可以是 1 到 14，6 和 7 除外，以选择 TIM 外设设备。
  * 参数:  TIM_OCFast: 输出比较快速启用位的新状态。
  *          此参数可以是以下值之一:
  *            @arg TIM_OCFast_Enable: TIM 输出比较快速启用
  *            @arg TIM_OCFast_Disable: TIM 输出比较快速禁用
  * 返回值: 无
  */
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast) {
    uint16_t tmpccmr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* 获取TIMx CCMR1 寄存器值 */
    tmpccmr1 = TIMx->CCMR1;

    /* 重设 OC1FE 位 */
    tmpccmr1 &= (uint16_t)~TIM_CCMR1_OC1FE;

    /* 启用或禁用输出比较快速位 */
    tmpccmr1 |= TIM_OCFast;

    /* 写入 TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * 简介:  配置 TIMx 输出比较2快速功能。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_OCFast: 输出比较快速启用位的新状态。
  *          此参数可以是以下值之一:
  *            @arg TIM_OCFast_Enable: TIM 输出比较快速启用
  *            @arg TIM_OCFast_Disable: TIM 输出比较快速禁用
  * 返回值: 无
  */
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast) {
    uint16_t tmpccmr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* 获取TIMx CCMR1 寄存器值 */
    tmpccmr1 = TIMx->CCMR1;

    /* 重设 OC2FE 位 */
    tmpccmr1 &= (uint16_t)(~TIM_CCMR1_OC2FE);

    /* 启用或禁用输出比较快速位 */
    tmpccmr1 |= (uint16_t)(TIM_OCFast << 8);

    /* 写入 TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * 简介:  配置 TIMx 输出比较 3 快速功能。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCFast: 输出比较快速启用位的新状态。
  *          此参数可以是以下值之一:
  *            @arg TIM_OCFast_Enable: TIM 输出比较快速启用
  *            @arg TIM_OCFast_Disable: TIM 输出比较快速禁用
  * 返回值: 无
  */
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast) {
    uint16_t tmpccmr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* 获取TIMx CCMR2寄存器的值 */
    tmpccmr2 = TIMx->CCMR2;

    /* 重设 OC3FE 位 */
    tmpccmr2 &= (uint16_t)~TIM_CCMR2_OC3FE;

    /* 启用或禁用输出比较快速位 */
    tmpccmr2 |= TIM_OCFast;

    /* 写入 TIMx CCMR2 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * 简介:  配置 TIMx 输出比较4快速功能。
  * 参数:  TIMx: 其中 x 可以是 1、2、3、4、5 或 8，以选择 TIM 外设设备。
  * 参数:  TIM_OCFast: 输出比较快速启用位的新状态。
  *          此参数可以是以下值之一:
  *            @arg TIM_OCFast_Enable: TIM 输出比较快速启用
  *            @arg TIM_OCFast_Disable: TIM 输出比较快速禁用
  * 返回值: 无
  */
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast) {
    uint16_t tmpccmr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

    /* 获取TIMx CCMR2寄存器值 */
    tmpccmr2 = TIMx->CCMR2;

    /* 重设 OC4FE 位 */
    tmpccmr2 &= (uint16_t)(~TIM_CCMR2_OC4FE);

    /* 启用或禁用快速输出比较位 */
    tmpccmr2 |= (uint16_t)(TIM_OCFast << 8);

    /* 写入 TIMx CCMR2 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * 简介:  清除或保护外部事件上的 OCREF1 信号。
  * 参数:  TIMx: 其中 x 可以是1 到14，6 和7除外，以选择 TIM 外设设备。
  * 参数:  TIM_OCClear: 输出比较清除启用位的新状态。
  *          此参数可以是以下值之一:
  *            @arg TIM_OCClear_Enable: TIM 输出清零启用
  *            @arg TIM_OCClear_Disable: TIM 输出清除禁用
  * 返回值: 无
  */
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear) {
    uint16_t tmpccmr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr1 = TIMx->CCMR1;

    /* 重设 OC1CE 位 */
    tmpccmr1 &= (uint16_t)~TIM_CCMR1_OC1CE;

    /* 启用或禁用输出比较清除位*/
    tmpccmr1 |= TIM_OCClear;

    /* 写入 TIMx CCMR1 寄存器 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * 简介:  清除或保护外部事件上的 OCREF2 信号。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_OCClear: 输出比较清除启用位的新状态。
  *          此参数可以是以下值之一:
  *            @arg TIM_OCClear_Enable: TIM 输出清零启用
  *            @arg TIM_OCClear_Disable: TIM 输出清除禁用
  * 返回值: 无
  */
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear) {
    uint16_t tmpccmr1 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr1 = TIMx->CCMR1;

    /* 重设 OC2CE 位 */
    tmpccmr1 &= (uint16_t)~TIM_CCMR1_OC2CE;

    /* 启用或禁用输出比较清除位*/
    tmpccmr1 |= (uint16_t)(TIM_OCClear << 8);

    /* 写入 TIMx CCMR1 寄存器 */
    TIMx->CCMR1 = tmpccmr1;
}

/**
  * 简介:  清除或保护外部事件上的 OCREF3 信号。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCClear: 输出比较清除启用位的新状态。
  *          此参数可以是以下值之一:
  *            @arg TIM_OCClear_Enable: TIM 输出清零启用
  *            @arg TIM_OCClear_Disable: TIM 输出清除禁用
  * 返回值: 无
  */
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear) {
    uint16_t tmpccmr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr2 = TIMx->CCMR2;

    /* 重设 OC3CE 位 */
    tmpccmr2 &= (uint16_t)~TIM_CCMR2_OC3CE;

    /* 启用或禁用输出比较清除位 */
    tmpccmr2 |= TIM_OCClear;

    /* 写入 TIMx CCMR2寄存器 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * 简介:  清除或保护外部事件上的 OCREF4 信号。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCClear: 输出比较清除启用位的新状态。
  *          此参数可以是以下值之一:
  *            @arg TIM_OCClear_Enable: TIM 输出清零启用
  *            @arg TIM_OCClear_Disable: TIM 输出清除禁用
  * 返回值: 无
  */
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear) {
    uint16_t tmpccmr2 = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

    tmpccmr2 = TIMx->CCMR2;

    /* 重设 OC4CE 位 */
    tmpccmr2 &= (uint16_t)~TIM_CCMR2_OC4CE;

    /* 启用或禁用输出比较清除位*/
    tmpccmr2 |= (uint16_t)(TIM_OCClear << 8);

    /* 写入 TIMx CCMR2 寄存器 */
    TIMx->CCMR2 = tmpccmr2;
}

/**
  * 简介:  配置 TIMx 通道 1 极性。
  * 参数:  TIMx: 其中 x 可以是1 到14，6 和7除外，以选择 TIM 外设设备。
  * 参数:  TIM_OCPolarity: 指定OC1极性
  *          此参数可以是以下值之一:
  *            @arg TIM_OCPolarity_High: 输出比较激活高
  *            @arg TIM_OCPolarity_Low: 输出比较激活低
  * 返回值: 无
  */
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity) {
    uint16_t tmpccer = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* 设置或重置 CC1P位 */
    tmpccer &= (uint16_t)(~TIM_CCER_CC1P);
    tmpccer |= TIM_OCPolarity;

    /* 写入 TIMx CCER 寄存器 */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  配置 TIMx 通道 1N 极性。
  * 参数:  TIMx: 其中 x 可以是1或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCNPolarity: 指定OC1N极性
  *          此参数可以是以下值之一:
  *            @arg TIM_OCNPolarity_High: 输出比较激活高
  *            @arg TIM_OCNPolarity_Low: 输出比较激活低
  * 返回值: 无
  */
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity) {
    uint16_t tmpccer = 0;
    /* 检查参数 */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

    tmpccer = TIMx->CCER;

    /* 设置或重置 CC1NP位 */
    tmpccer &= (uint16_t)~TIM_CCER_CC1NP;
    tmpccer |= TIM_OCNPolarity;

    /* 写入 TIMx CCER 寄存器 */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  配置 TIMx 通道 2 极性。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_OCPolarity: 指定OC2极性
  *          此参数可以是以下值之一:
  *            @arg TIM_OCPolarity_High: 输出比较激活高
  *            @arg TIM_OCPolarity_Low: 输出比较激活低
  * 返回值: 无
  */
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity) {
    uint16_t tmpccer = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* 设置或重置 CC2P位 */
    tmpccer &= (uint16_t)(~TIM_CCER_CC2P);
    tmpccer |= (uint16_t)(TIM_OCPolarity << 4);

    /* 写入 TIMx CCER 寄存器 */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  配置 TIMx 通道 2N 极性。
  * 参数:  TIMx: 其中 x 可以是1或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCNPolarity: 指定OC2N极性
  *          此参数可以是以下值之一:
  *            @arg TIM_OCNPolarity_High: 输出比较激活高
  *            @arg TIM_OCNPolarity_Low: 输出比较激活低
  * 返回值: 无
  */
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity) {
    uint16_t tmpccer = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

    tmpccer = TIMx->CCER;

    /* 设置或重置 CC2NP 位 */
    tmpccer &= (uint16_t)~TIM_CCER_CC2NP;
    tmpccer |= (uint16_t)(TIM_OCNPolarity << 4);

    /* 写入 TIMx CCER 寄存器 */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  配置 TIMx 通道 3 极性。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCPolarity: 指定OC3极性
  *          此参数可以是以下值之一:
  *            @arg TIM_OCPolarity_High: 输出比较激活高
  *            @arg TIM_OCPolarity_Low: 输出比较激活低
  * 返回值: 无
  */
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity) {
    uint16_t tmpccer = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* 设置或重置 CC3P 位 */
    tmpccer &= (uint16_t)~TIM_CCER_CC3P;
    tmpccer |= (uint16_t)(TIM_OCPolarity << 8);

    /* 写入 TIMx CCER 寄存器 */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  配置 TIMx 通道 3N 极性。
  * 参数:  TIMx: 其中 x 可以是1或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCNPolarity: 指定OC3N极性
  *          此参数可以是以下值之一:
  *            @arg TIM_OCNPolarity_High: 输出比较激活高
  *            @arg TIM_OCNPolarity_Low: 输出比较激活低
  * 返回值: 无
  */
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity) {
    uint16_t tmpccer = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));

    tmpccer = TIMx->CCER;

    /* 设置或重置 CC3NP 位 */
    tmpccer &= (uint16_t)~TIM_CCER_CC3NP;
    tmpccer |= (uint16_t)(TIM_OCNPolarity << 8);

    /* 写入 TIMx CCER 寄存器 */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  配置 TIMx 通道 4 极性。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_OCPolarity: 指定OC4极性
  *          此参数可以是以下值之一:
  *            @arg TIM_OCPolarity_High: 输出比较激活高
  *            @arg TIM_OCPolarity_Low: 输出比较激活低
  * 返回值: 无
  */
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity) {
    uint16_t tmpccer = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

    tmpccer = TIMx->CCER;

    /* 设置或重置 CC4P 位 */
    tmpccer &= (uint16_t)~TIM_CCER_CC4P;
    tmpccer |= (uint16_t)(TIM_OCPolarity << 12);

    /* 写入 TIMx CCER 寄存器 */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  启用或禁用 TIM 捕获比较通道 x。
  * 参数:  TIMx: 其中 x 可以是1 到14，6 和7除外，以选择 TIM 外设设备。
  * 参数:  TIM_Channel: 指定 TIM通道
  *          此参数可以是以下值之一:
  *            @arg TIM_Channel_1: TIM通道 1
  *            @arg TIM_Channel_2: TIM通道 2
  *            @arg TIM_Channel_3: TIM通道 3
  *            @arg TIM_Channel_4: TIM通道 4
  * 参数:  TIM_CCx: 指定 TIM通道 CCxE 位新状态。
  *          此参数可以是: TIM_CCx_Enable or TIM_CCx_Disable.
  * 返回值: 无
  */
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx) {
    uint16_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_CHANNEL(TIM_Channel));
    assert_param(IS_TIM_CCX(TIM_CCx));

    tmp = CCER_CCE_SET << TIM_Channel;

    /* 重设 CCxE 位 */
    TIMx->CCER &= (uint16_t)~ tmp;

    /* 设置或重置 CCxE 位 */
    TIMx->CCER |=  (uint16_t)(TIM_CCx << TIM_Channel);
}

/**
  * 简介:  启用或禁用 TIM 捕获比较通道 xN。
  * 参数:  TIMx: 其中 x 可以是1或8，以选择 TIM 外设设备。
  * 参数:  TIM_Channel: 指定 TIM通道
  *          此参数可以是以下值之一:
  *            @arg TIM_Channel_1: TIM通道 1
  *            @arg TIM_Channel_2: TIM通道 2
  *            @arg TIM_Channel_3: TIM通道 3
  * 参数:  TIM_CCxN: 指定 TIM通道 CCxNE 位 新状态.
  *          此参数可以是: TIM_CCxN_Enable 或 TIM_CCxN_Disable。
  * 返回值: 无
  */
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN) {
    uint16_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_COMPLEMENTARY_CHANNEL(TIM_Channel));
    assert_param(IS_TIM_CCXN(TIM_CCxN));

    tmp = CCER_CCNE_SET << TIM_Channel;

    /* 重置 CCxNE 位 */
    TIMx->CCER &= (uint16_t) ~tmp;

    /* 设置或重置 CCxNE 位 */
    TIMx->CCER |=  (uint16_t)(TIM_CCxN << TIM_Channel);
}

/** @defgroup TIM_Group3 输入捕获管理功能
 *  简介    输入捕获管理功能
 *
@verbatim
 ===============================================================================
                  ##### 输入捕获管理功能 #####
 ===============================================================================

            ##### TIM 驱动程序: 如何在输入捕捉模式下使用 #####
 ===============================================================================
    [..]
    要在输入捕获模式下使用计时器，必须执行以下步骤:

      (#) 使用 RCC_APBxPeriphClockCmd(RCC_ABPxPeriph-TIMx，Enable) 函数启用 TIM 时钟

      (#) 通过配置相应的 GPIO 引脚来配置 TIM 引脚

      (#) 如有必要，按照本驱动程序第一部分所述配置时基单位，否则定时器将以默认配置运行:
        (++)自动重新加载值=0xFFFF
        (++)预分频器值=0x0000
        (++)计数器模式=递增计数
        (++)时钟分区=TIM_CKD_DIV1

      (#) 用所需参数填充 TIM_ICInitStruct，包括:
        (++)TIM通道: TIM_Channel
        (++)TIM 输入捕捉极性: TIM_IC 极性
        (++)TIM 输入捕捉选择: TIM_ICS 选择
        (++)TIM 输入捕获预定标器: TIM_IC 预定标器
        (++)TIM 输入捕获过滤器值: TIM_IC 过滤器

      (#) 调用 TIM_ICInit(TIMx， &TIM_ICInitStruct)用相应的配置配置所需的信道，
		  只测量输入信号的频率或占空比，或者调用 TIM_PWMIConfig(TIMx， &TIM_ICInitStruct)
		  用相应的配置配置所需的信道，测量输入信号的频率和占空比

      (#) 使能NVIC或 DMA读取测量频率。

      (#) 使用函数 TIM_ITConfig(TIMx, TIM_IT_CCx)
		 (或 TIM_DMA_Cmd(TIMx, TIM_DMA_CCx)) 启用相应的中断(或 DMA 请求)来读取捕获值

      (#) 调用 TIM_Cmd(ENABLE) 函数启用 TIM 计数器.

      (#) 使用 TIM_GetCapturex(TIMx) 读取捕获的值.

      -@- 如果需要，所有其他函数都可以单独使用来修改定时器的特定特性。

@endverbatim
  */

/**
  * 简介:  根据 TIM_ICInitStruct 中指定的参数初始化 TIM 外设。
  * 参数:  TIMx: 其中 x 可以是1 到14，6 和7除外，以选择 TIM 外设设备。
  * 参数:  TIM_ICInitStruct: 指向 TIM_ICInitTypeDef 结构的指针，该结构包含指定 TIM 外设设备的配置信息。
  * 返回值: 无
  */
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));
    assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
    assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));

    if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1) {
        /* TI1 配置*/
        TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* 设置 Input Capture 预分频器值 */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    } else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2) {
        /* TI2 配置*/
        assert_param(IS_TIM_LIST2_PERIPH(TIMx));
        TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* 设置 Input Capture 预分频器值 */
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    } else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3) {
        /* TI3 配置*/
        assert_param(IS_TIM_LIST3_PERIPH(TIMx));
        TI3_Config(TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* 设置 Input Capture 预分频器值 */
        TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    } else {
        /* TI4 配置*/
        assert_param(IS_TIM_LIST3_PERIPH(TIMx));
        TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* 设置 Input Capture 预分频器值 */
        TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
}

/**
  * 简介:  用其默认值填充每个 TIM_ICInitStruct 成员。
  * 参数:  TIM_ICInitStruct: 指向将被初始化的 TIM_ICInitTypeDef 结构的指针。
  * 返回值: 无
  */
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct) {
    /* 设置默认配置 */
    TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

/**
  * 简介:  根据 TIM_ICInitStruct 中的指定参数配置 TIM 外设，以测量外部 PWM 信号。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_ICInitStruct: 指向包含指定 TIM 外设设备配置信息的 TIM_ICInitTypeDef 结构的指针。
  * 返回值: 无
  */
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct) {
    uint16_t icoppositepolarity = TIM_ICPolarity_Rising;
    uint16_t icoppositeselection = TIM_ICSelection_DirectTI;

    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* 选择相反的输入 Polarity */
    if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising) {
        icoppositepolarity = TIM_ICPolarity_Falling;
    } else {
        icoppositepolarity = TIM_ICPolarity_Rising;
    }

    /* 选择相反的输入 */
    if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI) {
        icoppositeselection = TIM_ICSelection_IndirectTI;
    } else {
        icoppositeselection = TIM_ICSelection_DirectTI;
    }

    if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1) {
        /* TI1 配置*/
        TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* 设置 Input Capture 预分频器值 */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
        /* TI2 配置*/
        TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
        /* 设置 Input Capture 预分频器值 */
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    } else {
        /* TI2 配置*/
        TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        /* 设置 Input Capture 预分频器值 */
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
        /* TI1 配置*/
        TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
        /* 设置 Input Capture 预分频器值 */
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
}

/**
  * 简介:  获取 TIMx 输入捕获 1 值。
  * 参数:  TIMx: 其中 x 可以是1 到14，6 和7除外，以选择 TIM 外设设备。
  * 返回值: 捕获比较1 寄存器的值。
  */
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));

    /* 获取Capture 1 寄存器值 */
    return TIMx->CCR1;
}

/**
  * 简介:  获取 TIMx 输入捕获 2 值。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 返回值: 捕获比较2寄存器的值。
  */
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* 获取Capture 2寄存器值 */
    return TIMx->CCR2;
}

/**
  * 简介:  获取 TIMx 输入捕获 3 值。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 返回值: 捕获比较3 寄存器的值。
  */
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* 获取Capture 3 寄存器值 */
    return TIMx->CCR3;
}

/**
  * 简介:  获取 TIMx 输入捕获 4 值。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 返回值: 捕获比较4 寄存器的值。
  */
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));

    /* 获取Capture 4 寄存器值 */
    return TIMx->CCR4;
}

/**
  * 简介:  设置 TIMx 输入捕获 1 预分频器。
  * 参数:  TIMx: 其中 x 可以是1 到14，6 和7除外，以选择 TIM 外设设备。
  * 参数:  TIM_ICPSC: 指定输入捕获1预分频器的新值。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPSC_DIV1: 没有预分频器
  *            @arg TIM_ICPSC_DIV2: 每2个事件进行一次捕获
  *            @arg TIM_ICPSC_DIV4: 每4个事件进行一次捕获
  *            @arg TIM_ICPSC_DIV8: 每8个事件进行一次捕获
  * 返回值: 无
  */
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

    /* 重设 IC1PSC 位 */
    TIMx->CCMR1 &= (uint16_t)~TIM_CCMR1_IC1PSC;

    /* 设置 IC1PSC 值 */
    TIMx->CCMR1 |= TIM_ICPSC;
}

/**
  * 简介:  设置 TIMx 输入捕获 2 预分频器。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_ICPSC: 指定输入捕获2预分频器的新值。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPSC_DIV1: 没有预分频器
  *            @arg TIM_ICPSC_DIV2: 每2个事件进行一次捕获
  *            @arg TIM_ICPSC_DIV4: 每4个事件进行一次捕获
  *            @arg TIM_ICPSC_DIV8: 每8个事件进行一次捕获
  * 返回值: 无
  */
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

    /* 重设 IC2PSC 位 */
    TIMx->CCMR1 &= (uint16_t)~TIM_CCMR1_IC2PSC;

    /* 设置 IC2PSC 值 */
    TIMx->CCMR1 |= (uint16_t)(TIM_ICPSC << 8);
}

/**
  * 简介:  设置 TIMx 输入捕获 3 预分频器。
  * 参数:  TIMx:其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_ICPSC: 指定Input Capture3预分频器的新值。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPSC_DIV1: 无预分频器
  *            @arg TIM_ICPSC_DIV2: 每2个事件进行一次捕获
  *            @arg TIM_ICPSC_DIV4: 每4个事件进行一次捕获
  *            @arg TIM_ICPSC_DIV8: 每8个事件进行一次捕获
  * 返回值: 无
  */
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

    /* 重设 IC3PSC 位 */
    TIMx->CCMR2 &= (uint16_t)~TIM_CCMR2_IC3PSC;

    /* 设置 IC3PSC 值 */
    TIMx->CCMR2 |= TIM_ICPSC;
}

/**
  * 简介:  设置 TIMx 输入捕获 4 预分频器。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_ICPSC: 指定Input Capture4 prescaler new value.
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPSC_DIV1: 没有预分频器
  *            @arg TIM_ICPSC_DIV2: 每2个事件进行一次捕获
  *            @arg TIM_ICPSC_DIV4: 每4个事件进行一次捕获
  *            @arg TIM_ICPSC_DIV8: 每8个事件进行一次捕获
  * 返回值: 无
  */
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint16_t TIM_ICPSC) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

    /* 重设 IC4PSC 位 */
    TIMx->CCMR2 &= (uint16_t)~TIM_CCMR2_IC4PSC;

    /* 设置 IC4PSC 值 */
    TIMx->CCMR2 |= (uint16_t)(TIM_ICPSC << 8);
}

/** @defgroup TIM_Group4 高级控制定时器(TIM1 和 TIM8)特定功能
 *  简介   高级控制定时器(TIM1 和 TIM8)特定功能
 *
@verbatim
 ===============================================================================
      ##### 高级控制定时器(TIM1 和 TIM8)特定功能 #####
 ===============================================================================

             ##### TIM 驱动程序:如何使用中断功能 #####
 ===============================================================================
    [..]
    在适当的输出比较模式下配置定时器通道后:

      (#) 在 TIM_BDTRInitStruct 中填入定时器中断极性、死区时间、锁定电平、OSSI/OSSR 状态和
        AOE(自动输出启用)的所需参数。

      (#)调用 TIM_BDTRConfig(TIMx，&TIM_BTTRInitStruct)配置计时器

      (#)使用 TIM_CtrlPWM 输出(TIM1，Enable) 启用主输出

      (#)一旦出现收支平衡，定时器的输出信号将被置于重置状态或已知状态(根据 TIM_BDTRConfig() 函数中的配置)。

@endverbatim
  */

/**
  * 简介:  配置中断功能、死区时间、锁定级别、OSSI/OSSR 状态和 AOE(自动输出启用)。
  * 参数:  TIMx: where x can be  1 or 8 to select the TIM
  * 参数:  TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure that
  *         contains the BDTR Register configuration  information for the TIM 外设.
  * 返回值: 无
  */
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
    assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
    assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
    assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
    assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
    assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));

    /* 设置 Lock level, the Break enable Bit and the Polarity, the OSSR State,
       the OSSI State, the dead time value and the Automatic Output Enable 位 */
    TIMx->BDTR = (uint32_t)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
                 TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
                 TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
                 TIM_BDTRInitStruct->TIM_AutomaticOutput;
}

/**
  * 简介:  用其默认值填充每个 TIM_BDTRInitStruct 成员。
  * 参数:  TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef structure which
  *         will be initialized.
  * 返回值: 无
  */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct) {
    /* 设置默认配置 */
    TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
    TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
    TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
    TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/**
  * 简介:  启用或禁用 TIM 外设主输出。
  * 参数:  TIMx: 其中 x 可以是1或8，以选择 TIMx 外设。
  * 参数:  NewState: TIM 外设主要输出的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 TIM主输出 */
        TIMx->BDTR |= TIM_BDTR_MOE;
    } else {
        /* 禁用 TIM主输出 */
        TIMx->BDTR &= (uint16_t)~TIM_BDTR_MOE;
    }
}

/**
  * 简介:  选择 TIM 外设换向事件。
  * 参数:  TIMx: 其中 x 可以是1或8，以选择 TIMx 外设
  * 参数:  NewState: 换向事件的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 COM 位 */
        TIMx->CR2 |= TIM_CR2_CCUS;
    } else {
        /* 重设 COM 位 */
        TIMx->CR2 &= (uint16_t)~TIM_CR2_CCUS;
    }
}

/**
  * 简介:  设置或复位 TIM 外设捕获比较预紧力控制位。
  * 参数:  TIMx: 其中 x 可以是1或8，以选择 TIMx 外设
  * 参数:  NewState: 捕获比较预载控制位的新状态
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST4_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 CCPC 位 */
        TIMx->CR2 |= TIM_CR2_CCPC;
    } else {
        /* 重设 CCPC 位 */
        TIMx->CR2 &= (uint16_t)~TIM_CR2_CCPC;
    }
}

/** @defgroup TIM_Group5 中断、DMA 和标志管理功能
 *  简介    中断、DMA 和标志管理功能
 *
@verbatim
 ===============================================================================
          ##### 中断、DMA 和标志管理功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 TIM 中断。
  * 参数:  TIMx: 其中 x 可以是1 到14，以选择 TIMx 外设。
  * 参数:  TIM_IT: 指定要启用或禁用的 TIM 中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg TIM_IT_Update: TIM 更新中断源
  *            @arg TIM_IT_CC1: TIM 捕获比较1 中断源
  *            @arg TIM_IT_CC2: TIM 捕获比较2中断源
  *            @arg TIM_IT_CC3: TIM 捕获比较3中断源
  *            @arg TIM_IT_CC4: TIM 捕获比较4中断源
  *            @arg TIM_IT_COM: TIM换向中断源
  *            @arg TIM_IT_Trigger: TIM触发中断源
  *            @arg TIM_IT_Break: TIM 中断中断源
  *
  * 注意:   对于 TIM6 和 TIM7，只能使用参数 TIM_IT_Update
  * 注意:   对于 TIM9 和 TIM12，只能使用以下参数之一:
		    TIM_IT_Update、TIM_IT_CC1、TIM_IT_CC2 或 TIM_IT_Trigger。
  * 注意:   对于 TIM10、TIM11、TIM13 和 TIM14，只能使用以下参数之一: TIM_IT_Update 或 TIM_IT_CC1
  * 注意:   TIM_IT_COM 和 TIM_IT_Break 只能与 TIM1 和 TIM8 一起使用
  *
  * 参数:  NewState: TIM 中断的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_IT(TIM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用中断源 */
        TIMx->DIER |= TIM_IT;
    } else {
        /* 禁用中断源 */
        TIMx->DIER &= (uint16_t)~TIM_IT;
    }
}

/**
  * 简介:  将 TIMx 事件配置为由 软件生成。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 参数:  TIM_EventSource: 指定事件源。
  *          此参数可以是以下一个或多个值:
  *            @arg TIM_EventSource_Update: 计时器更新事件源
  *            @arg TIM_EventSource_CC1: 定时器捕获比较1事件源
  *            @arg TIM_EventSource_CC2: 定时器捕获比较2事件源
  *            @arg TIM_EventSource_CC3: 定时器捕获比较3事件源
  *            @arg TIM_EventSource_CC4: 定时器捕获比较4事件源
  *            @arg TIM_EventSource_COM: 定时器COM事件源
  *            @arg TIM_EventSource_Trigger: 计时器触发器事件源
  *            @arg TIM_EventSource_Break: 计时器中断事件源
  *
  * 注意:   TIM6 和 TIM7 只能生成一个更新事件。
  * 注意:   TIM_EventSource_COM 和 TIM_EventSource _Break 仅与 TIM1 和 TIM8 一起使用。
  *
  * 返回值: 无
  */
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint16_t TIM_EventSource) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource));

    /* 设置 event sources */
    TIMx->EGR = TIM_EventSource;
}

/**
  * 简介:  检查是否设置了指定的 TIM 标志。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 参数:  TIM_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg TIM_FLAG_Update: TIM update Flag
  *            @arg TIM_FLAG_CC1: TIM 捕获比较1标志
  *            @arg TIM_FLAG_CC2: TIM 捕获比较2标志
  *            @arg TIM_FLAG_CC3: TIM 捕获比较3标志
  *            @arg TIM_FLAG_CC4: TIM 捕获比较4标志
  *            @arg TIM_FLAG_COM: TIM Commutation Flag
  *            @arg TIM_FLAG_Trigger: TIM Trigger Flag
  *            @arg TIM_FLAG_Break: TIM Break Flag
  *            @arg TIM_FLAG_CC1OF: TIM 捕获比较1超过捕获标志
  *            @arg TIM_FLAG_CC2OF: TIM 捕获比较2超过捕获标志
  *            @arg TIM_FLAG_CC3OF: TIM 捕获比较3超过捕获标志
  *            @arg TIM_FLAG_CC4OF: TIM 捕获比较4超过捕获标志
  *
  * 注意:   TIM6 和 TIM7 只能有一个更新标志。
  * 注意:   FLAG_ COM 和 TIM_FLAG_ Break 仅与 TIM1 和 TIM8 一起使用。
  *
  * 返回值: TIM_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint16_t TIM_FLAG) {
    ITStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_GET_FLAG(TIM_FLAG));


    if ((TIMx->SR & TIM_FLAG) != (uint16_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 TIMx 的挂起标志。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 参数:  TIM_FLAG: 指定要清除的标志位。
  *          此参数可以是以下值的任意组合:
  *            @arg TIM_FLAG_Update: TIM 更新标志
  *            @arg TIM_FLAG_CC1: TIM 捕获比较1标志
  *            @arg TIM_FLAG_CC2: TIM 捕获比较2标志
  *            @arg TIM_FLAG_CC3: TIM 捕获比较3标志
  *            @arg TIM_FLAG_CC4: TIM 捕获比较4标志
  *            @arg TIM_FLAG_COM: TIM换向标志
  *            @arg TIM_FLAG_Trigger: TIM触发标志
  *            @arg TIM_FLAG_Break: TIM 中断标志
  *            @arg TIM_FLAG_CC1OF: TIM 捕获比较1超过捕获标志
  *            @arg TIM_FLAG_CC2OF: TIM 捕获比较2超过捕获标志
  *            @arg TIM_FLAG_CC3OF: TIM 捕获比较3超过捕获标志
  *            @arg TIM_FLAG_CC4OF: TIM 捕获比较4超过捕获标志
  *
  * 注意:   TIM6 和 TIM7 只能具有一个更新标志。
  * 注意:   FLAG_ COM 和 TIM_FLAG_ Break 仅与 TIM1 和 TIM8 一起使用。
  *
  * 返回值: 无
  */
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint16_t TIM_FLAG) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* 清除 flags */
    TIMx->SR = (uint16_t)~TIM_FLAG;
}

/**
  * 简介:  检查是否发生了 TIM 中断。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 参数:  TIM_IT: 指定要检查的 TIM 中断源。
  *          此参数可以是以下值之一:
  *            @arg TIM_IT_Update: TIM 更新中断源
  *            @arg TIM_IT_CC1: TIM 捕获比较1 中断源
  *            @arg TIM_IT_CC2: TIM 捕获比较2中断源
  *            @arg TIM_IT_CC3: TIM 捕获比较3中断源
  *            @arg TIM_IT_CC4: TIM 捕获比较4中断源
  *            @arg TIM_IT_COM: TIM换向中断源
  *            @arg TIM_IT_Trigger: TIM触发中断源
  *            @arg TIM_IT_Break: TIM 中断中断源
  *
  * 注意:   TIM6 和 TIM7 只能产生一个更新中断。
  * 注意:   TIM_IT_COM 和 TIM_IT_ Break 仅与 TIM1 和 TIM8 一起使用。
  *
  * 返回值: TIM_IT 的新状态(SET 或 RESET)。
  */
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint16_t TIM_IT) {
    ITStatus bitstatus = RESET;
    uint16_t itstatus = 0x0, itenable = 0x0;
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));
    assert_param(IS_TIM_GET_IT(TIM_IT));

    itstatus = TIMx->SR & TIM_IT;

    itenable = TIMx->DIER & TIM_IT;

    if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 TIMx 的中断挂起位。
  * 参数:  TIMx: 其中 x 可以是1 到14，用于选择 TIM 外设设备。
  * 参数:  TIM_IT: 指定要清除的挂起位。
  *          此参数可以是以下值的任意组合:
  *            @arg TIM_IT_Update: TIM 更新中断源
  *            @arg TIM_IT_CC1: TIM 捕获比较1 中断源
  *            @arg TIM_IT_CC2: TIM 捕获比较2中断源
  *            @arg TIM_IT_CC3: TIM 捕获比较3中断源
  *            @arg TIM_IT_CC4: TIM 捕获比较4中断源
  *            @arg TIM_IT_COM: TIM换向中断源
  *            @arg TIM_IT_Trigger: TIM Trigger Interrupt source
  *            @arg TIM_IT_Break: TIM Break Interrupt source
  *
  * 注意:   TIM6 和 TIM7 只能产生一个更新中断。
  * 注意:   TIM_IT_COM 和 TIM_IT_ Break 仅与 TIM1 和 TIM8 一起使用。
  *
  * 返回值: 无
  */
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT) {
    /* 检查参数 */
    assert_param(IS_TIM_ALL_PERIPH(TIMx));

    /* 清除 IT pending 位 */
    TIMx->SR = (uint16_t)~TIM_IT;
}

/**
  * 简介:  配置 TIMx 的 DMA 接口。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_DMABase: DMA Base address.
  *          此参数可以是以下值之一:
  *            @arg TIM_DMABase_CR1
  *            @arg TIM_DMABase_CR2
  *            @arg TIM_DMABase_SMCR
  *            @arg TIM_DMABase_DIER
  *            @arg TIM1_DMABase_SR
  *            @arg TIM_DMABase_EGR
  *            @arg TIM_DMABase_CCMR1
  *            @arg TIM_DMABase_CCMR2
  *            @arg TIM_DMABase_CCER
  *            @arg TIM_DMABase_CNT
  *            @arg TIM_DMABase_PSC
  *            @arg TIM_DMABase_ARR
  *            @arg TIM_DMABase_RCR
  *            @arg TIM_DMABase_CCR1
  *            @arg TIM_DMABase_CCR2
  *            @arg TIM_DMABase_CCR3
  *            @arg TIM_DMABase_CCR4
  *            @arg TIM_DMABase_BDTR
  *            @arg TIM_DMABase_DCR
  * 参数:  TIM_DMABurstLength: DMA 突发长度。该参数可以是一个介于。
  *         TIM_DMABurstLength_1Transfer 和 TIM_DMABurstLength_18Transfers。
  * 返回值: 无
  */
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_DMA_BASE(TIM_DMABase));
    assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));

    /* 设置 DMA基址和 DMA 突发长度 */
    TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}

/**
  * 简介:  启用或禁用 TIMx 的 DMA 请求。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、6、7或8，以选择 TIM 外设设备。
  * 参数:  TIM_DMASource: 指定 DMA 请求源。
  *          此参数可以是以下值的任意组合:
  *            @arg TIM_DMA_Update: TIM 更新中断源
  *            @arg TIM_DMA_CC1: TIM 捕获比较1 DMA源
  *            @arg TIM_DMA_CC2: TIM 捕获比较2 DMA源
  *            @arg TIM_DMA_CC3: TIM 捕获比较3 DMA源
  *            @arg TIM_DMA_CC4: TIM 捕获比较4 DMA源
  *            @arg TIM_DMA_COM: TIM 交换DMA源
  *            @arg TIM_DMA_Trigger: TIM触发器 DMA源
  * 参数:  NewState: DMA 请求源的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_DMACmd(TIM_TypeDef* TIMx, uint16_t TIM_DMASource, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 DMA源 */
        TIMx->DIER |= TIM_DMASource;
    } else {
        /* 禁用 DMA源 */
        TIMx->DIER &= (uint16_t)~TIM_DMASource;
    }
}

/**
  * 简介:  选择 TIMx 外设捕获比较 DMA 源。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  NewState: 捕获比较DMA源的新状态
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 CCDS 位 */
        TIMx->CR2 |= TIM_CR2_CCDS;
    } else {
        /* 重设 CCDS 位 */
        TIMx->CR2 &= (uint16_t)~TIM_CR2_CCDS;
    }
}

/** @defgroup TIM_Group6 时钟管理功能
 *  简介    时钟管理功能
 *
@verbatim
 ===============================================================================
                  ##### 时钟管理功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  配置 TIMx内部时钟
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 返回值: 无
  */
void TIM_InternalClockConfig(TIM_TypeDef* TIMx) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));

    /* 禁用从模式，直接用内部时钟给预分频器计时 */
    TIMx->SMCR &=  (uint16_t)~TIM_SMCR_SMS;
}

/**
  * 简介:  将 TIMx 内部触发器配置为外部时钟。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_InputTriggerSource: Trigger source.
  *          此参数可以是以下值之一:
  *            @arg TIM_TS_ITR0: 内部触发器0
  *            @arg TIM_TS_ITR1: 内部触发器1
  *            @arg TIM_TS_ITR2: 内部触发器2
  *            @arg TIM_TS_ITR3: 内部触发器3
  * 返回值: 无
  */
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));

    /* 选择这个内部触发器*/
    TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);

    /* 选择这个外部时钟模式1 */
    TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * 简介:  将 TIMx 触发器配置为外部时钟。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9、10、11、12、13或14，以选择 TIM 外设设备。
  * 参数:  TIM_TIxExternalCLKSource: Trigger source.
  *          此参数可以是以下值之一:
  *            @arg TIM_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
  *            @arg TIM_TIxExternalCLK1Source_TI1: 过滤定时器输入1
  *            @arg TIM_TIxExternalCLK1Source_TI2: 过滤定时器输入2
  * 参数:  TIM_ICPolarity: 指定 TIx Polarity.
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  * 参数:  ICFilter: 指定筛选器值。
  *          此参数的值必须介于 0x0 和0xF之间。
  * 返回值: 无
  */
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
    assert_param(IS_TIM_IC_FILTER(ICFilter));

    /* 配置定时器输入时钟源 */
    if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2) {
        TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
    } else {
        TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
    }

    /* 选择这个触发器源 */
    TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
    /* 选择这个外部时钟模式1 */
    TIMx->SMCR |= TIM_SlaveMode_External1;
}

/**
  * 简介:  配置外部时钟模式1。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_ExtTRGPrescaler: 外部触发预分频器。
  *          此参数可以是以下值之一:
  *            @arg TIM_ExtTRGPSC_OFF: ETRP预分频器关闭。
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP频率除以2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP频率除以4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP频率除以8.
  * 参数:  TIM_ExtTRGPolarity: 外部触发极性。
  *          此参数可以是以下值之一:
  *            @arg TIM_ExtTRGPolarity_Inverted: 活动低边或下降沿活动。
  *            @arg TIM_ExtTRGPolarity_NonInverted: 激活的高或上升沿激活。
  * 参数:  ExtTRGFilter: 外部触发器筛选器。
  *          此参数的值必须介于 0x00 和0x0F之间
  * 返回值: 无
  */
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter) {
    uint16_t tmpsmcr = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));
    /* 配置ETR时钟源 */
    TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);

    /* 获取TIMx SMCr 寄存器值 */
    tmpsmcr = TIMx->SMCR;

    /* 重设 SMS 位 */
    tmpsmcr &= (uint16_t)~TIM_SMCR_SMS;

    /* 选择这个外部时钟模式1 */
    tmpsmcr |= TIM_SlaveMode_External1;

    /* 选择这个 Trigger selection : ETRF */
    tmpsmcr &= (uint16_t)~TIM_SMCR_TS;
    tmpsmcr |= TIM_TS_ETRF;

    /* 写入 TIMx SMCR */
    TIMx->SMCR = tmpsmcr;
}

/**
  * 简介:  配置外部时钟模式1。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_ExtTRGPrescaler: 外部触发预分频器。
  *          此参数可以是以下值之一:
  *            @arg TIM_ExtTRGPSC_OFF: ETRP预分频器关闭。
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP频率除以2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP频率除以4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP频率除以8.
  * 参数:  TIM_ExtTRGPolarity: 外部触发极性。
  *          此参数可以是以下值之一:
  *            @arg TIM_ExtTRGPolarity_Inverted: 活动低边或下降沿活动。
  *            @arg TIM_ExtTRGPolarity_NonInverted: 激活的高或上升沿激活。
  * 参数:  ExtTRGFilter: 外部触发器筛选器。
  *          此参数的值必须介于 0x00 和0x0F之间
  * 返回值: 无
  */
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

    /* 配置ETR时钟源 */
    TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);

    /* 启用外部时钟模式2 */
    TIMx->SMCR |= TIM_SMCR_ECE;
}

/** @defgroup TIM_Group7 同步管理功能
 *  简介    同步管理功能
 *
@verbatim
 ===============================================================================
                ##### 同步管理功能 #####
 ===============================================================================

          ##### TIM 驱动程序:如何在同步模式下使用 #####
 ===============================================================================
    [..]

    *** 两个/多个定时器的情况 ***
    ==================================
    [..]
      (#) 使用以下功能配置主定时器:
        (++) void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
        (++) void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
      (#) 使用以下功能配置从定时器:
        (++) void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
        (++) void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);

    *** 定时器和外部触发器的情况(ETR引脚) ***
    ====================================================
    [..]
      (#) 使用此功能配置外部触发器:
        (++) void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                               uint16_t ExtTRGFilter);
      (#) 使用以下功能配置从定时器:
        (++) void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
        (++) void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);

@endverbatim
  */

/**
  * 简介:  选择输入触发器源。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9、10、11、12、13或14，以选择 TIM 外设设备。
  * 参数:  TIM_InputTriggerSource: 输入触发器源。
  *          此参数可以是以下值之一:
  *            @arg TIM_TS_ITR0: 内部触发器0
  *            @arg TIM_TS_ITR1: 内部触发器1
  *            @arg TIM_TS_ITR2: 内部触发器2
  *            @arg TIM_TS_ITR3: 内部触发器3
  *            @arg TIM_TS_TI1F_ED: TI1边缘探测器
  *            @arg TIM_TS_TI1FP1: 过滤定时器输入1
  *            @arg TIM_TS_TI2FP2: 过滤定时器输入2
  *            @arg TIM_TS_ETRF: 外部触发器输入
  * 返回值: 无
  */
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource) {
    uint16_t tmpsmcr = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST1_PERIPH(TIMx));
    assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));

    /* 获取TIMx SMCr 寄存器值 */
    tmpsmcr = TIMx->SMCR;

    /* 重设 TS 位 */
    tmpsmcr &= (uint16_t)~TIM_SMCR_TS;

    /* 设置 Input 触发器源 */
    tmpsmcr |= TIM_InputTriggerSource;

    /* 写入 TIMx SMCR */
    TIMx->SMCR = tmpsmcr;
}

/**
  * 简介:  选择 TIMx 触发输出模式。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、6、7或8，以选择 TIM 外设设备。
  *
  * 参数:  TIM_TRGOSource: 指定触发器输出源。
  *   此参数可以是以下值之一:
  *
  *  - For all TIMx
  *            @arg TIM_TRGOSource_Reset:  TIM_EGR 寄存器中的 UG位用作触发输出(TRGO)
  *            @arg TIM_TRGOSource_Enable: 计数器使能CEN用作触发输出(TRGO)
  *            @arg TIM_TRGOSource_Update: 选择更新事件作为触发输出(TRGO)
  *
  *  - For all TIMx except TIM6 and TIM7
  *            @arg TIM_TRGOSource_OC1: 一旦发生捕获或比较匹配(TRGO)，当要设置 CC1IF标志时，
										触发输出会发送一个正脉冲
  *            @arg TIM_TRGOSource_OC1Ref: OC1REF信号用作触发输出(TRGO)
  *            @arg TIM_TRGOSource_OC2Ref: OC2REF信号用作触发输出(TRGO)
  *            @arg TIM_TRGOSource_OC3Ref: OC3REF信号用作触发输出(TRGO)
  *            @arg TIM_TRGOSource_OC4Ref: OC4REF信号用作触发输出(TRGO)
  *
  * 返回值: 无
  */
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint16_t TIM_TRGOSource) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST5_PERIPH(TIMx));
    assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));

    /* 重设 MMS 位 */
    TIMx->CR2 &= (uint16_t)~TIM_CR2_MMS;
    /* 选择这个 TRGO source */
    TIMx->CR2 |=  TIM_TRGOSource;
}

/**
  * 简介:  选择 TIMx 从模式。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_SlaveMode: 指定定时器从模式。
  *          此参数可以是以下值之一:
  *            @arg TIM_SlaveMode_Reset: 所选触发信号(TRGI)的上升沿重新初始化计数器并触发寄存器更新
  *            @arg TIM_SlaveMode_Gated:     当触发信号(TRGI)高时，计数器时钟启用
  *            @arg TIM_SlaveMode_Trigger:   计数器从触发器TRGI 的上升沿开始
  *            @arg TIM_SlaveMode_External1: 所选触发器(TRGI)的上升沿为计数器计时
  * 返回值: 无
  */
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_SlaveMode) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));

    /* 重设 SMS 位 */
    TIMx->SMCR &= (uint16_t)~TIM_SMCR_SMS;

    /* 选择这个 Slave Mode */
    TIMx->SMCR |= TIM_SlaveMode;
}

/**
  * 简介:  设置或重置 TIMx 主/从模式。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_MasterSlaveMode: 指定定时器主从模式。
  *          此参数可以是以下值之一:
  *            @arg TIM_MasterSlaveMode_Enable: 当前定时器及其从机之间的同步(通过TRGO)
  *            @arg TIM_MasterSlaveMode_Disable: 无操作
  * 返回值: 无
  */
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_MSM_STATE(TIM_MasterSlaveMode));

    /* 重设 MSM 位 */
    TIMx->SMCR &= (uint16_t)~TIM_SMCR_MSM;

    /* 设置或重置 MSM 位 */
    TIMx->SMCR |= TIM_MasterSlaveMode;
}

/**
  * 简介:  配置 TIMx 外部触发器 (ETR)。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_ExtTRGPrescaler: 外部触发预分频器。
  *          此参数可以是以下值之一:
  *            @arg TIM_ExtTRGPSC_OFF: ETRP预分频器关闭。
  *            @arg TIM_ExtTRGPSC_DIV2: ETRP频率除以2.
  *            @arg TIM_ExtTRGPSC_DIV4: ETRP频率除以4.
  *            @arg TIM_ExtTRGPSC_DIV8: ETRP频率除以8.
  * 参数:  TIM_ExtTRGPolarity: 外部触发极性。
  *          此参数可以是以下值之一:
  *            @arg TIM_ExtTRGPolarity_Inverted: 活动低边或下降沿活动。
  *            @arg TIM_ExtTRGPolarity_NonInverted: 激活的高或上升沿激活。
  * 参数:  ExtTRGFilter: 外部触发器筛选器。
  *          此参数的值必须介于 0x00 和0x0F之间
  * 返回值: 无
  */
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
                   uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter) {
    uint16_t tmpsmcr = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST3_PERIPH(TIMx));
    assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
    assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
    assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

    tmpsmcr = TIMx->SMCR;

    /* 重设 ETR 位 */
    tmpsmcr &= SMCR_ETR_MASK;

    /* 设置预分频器、滤波器值和极性 */
    tmpsmcr |= (uint16_t)(TIM_ExtTRGPrescaler | (uint16_t)(TIM_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));

    /* 写入 TIMx SMCR */
    TIMx->SMCR = tmpsmcr;
}

/** @defgroup TIM_Group8 具体接口管理功能
 *  简介    具体接口管理功能
 *
@verbatim
 ===============================================================================
            ##### 具体接口管理功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  配置 TIMx 编码器接口。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_EncoderMode: 指定 TIMx编码器模式。
  *          此参数可以是以下值之一:
  *            @arg TIM_EncoderMode_TI1: TI1FP1边缘上的计数器计数取决于 TI2FP2级别。
  *            @arg TIM_EncoderMode_TI2: TI2FP2边缘上的计数器计数取决于 TI1FP1级别。
  *            @arg TIM_EncoderMode_TI12: TI1FP1 和 TI2FP2边缘上的计数器计数取决于其他输入的电平。
  * 参数:  TIM_IC1Polarity: 指定IC1极性
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPolarity_Falling: IC下降沿。
  *            @arg TIM_ICPolarity_Rising: IC上升沿。
  * 参数:  TIM_IC2Polarity: 指定IC2极性
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPolarity_Falling: IC下降沿。
  *            @arg TIM_ICPolarity_Rising: IC上升沿。
  * 返回值: 无
  */
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity) {
    uint16_t tmpsmcr = 0;
    uint16_t tmpccmr1 = 0;
    uint16_t tmpccer = 0;

    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
    assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
    assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));

    /* 获取TIMx SMCr 寄存器值 */
    tmpsmcr = TIMx->SMCR;

    /* 获取TIMx CCMR1 寄存器值 */
    tmpccmr1 = TIMx->CCMR1;

    /* 获取TIMx CCER 寄存器的值 */
    tmpccer = TIMx->CCER;

    /* 设置 encoder Mode */
    tmpsmcr &= (uint16_t)~TIM_SMCR_SMS;
    tmpsmcr |= TIM_EncoderMode;

    /* 选择这个 Capture Compare 1 and the Capture Compare 2 as input */
    tmpccmr1 &= ((uint16_t)~TIM_CCMR1_CC1S) & ((uint16_t)~TIM_CCMR1_CC2S);
    tmpccmr1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;

    /* 设置 TI1 and the TI2 Polarities */
    tmpccer &= ((uint16_t)~TIM_CCER_CC1P) & ((uint16_t)~TIM_CCER_CC2P);
    tmpccer |= (uint16_t)(TIM_IC1Polarity | (uint16_t)(TIM_IC2Polarity << (uint16_t)4));

    /* 写入 TIMx SMCR */
    TIMx->SMCR = tmpsmcr;

    /* 写入 TIMx CCMR1 */
    TIMx->CCMR1 = tmpccmr1;

    /* 写入 TIMx CCER */
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  启用或禁用 TIMx 的霍尔传感器接口。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  NewState: TIMx霍尔传感器接口的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST2_PERIPH(TIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 TI1S 位 */
        TIMx->CR2 |= TIM_CR2_TI1S;
    } else {
        /* 重设 TI1S 位 */
        TIMx->CR2 &= (uint16_t)~TIM_CR2_TI1S;
    }
}

/** @defgroup TIM_Group9 具体重映射管理功能
 *  简介   具体重映射管理功能
 *
@verbatim
 ===============================================================================
              ##### 具体重映射管理功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  配置 TIM2、TIM5 和 TIM11 重新映射输入功能。
  * 参数:  TIMx: where x can be 2, 5 or 11 to select the TIM 外设.
  * 参数:  TIM_Remap: 指定 TIM 输入重映射源。
  *          此参数可以是以下值之一:
  *            @arg TIM2_TIM8_TRGO: TIM2 ITR1输入连接至 TIM8触发器输出(默认)
  *            @arg TIM2_ETH_PTP:   TIM2 ITR1输入连接到ETH PTP触发输出。
  *            @arg TIM2_USBFS_SOF: TIM2 ITR1输入连接到USB FS SOF。
  *            @arg TIM2_USBHS_SOF: TIM2 ITR1输入连接到USB HS SOF。
  *            @arg TIM5_GPIO:      TIM5 CH4输入连接到专用定时器引脚(默认)
  *            @arg TIM5_LSI:       TIM5 CH4输入连接到LSI时钟。
  *            @arg TIM5_LSE:       TIM5 CH4输入连接到LSE时钟。
  *            @arg TIM5_RTC:       TIM5 CH4输入连接到 RTC输出事件。
  *            @arg TIM11_GPIO:     TIM11 CH4输入连接到专用定时器引脚(默认)
  *            @arg TIM11_HSE:      TIM11 CH4输入连接到HSE_RTC时钟(HSE由可编程预分频器分频)
  * 返回值: 无
  */
void TIM_RemapConfig(TIM_TypeDef* TIMx, uint16_t TIM_Remap) {
    /* 检查参数 */
    assert_param(IS_TIM_LIST6_PERIPH(TIMx));
    assert_param(IS_TIM_REMAP(TIM_Remap));

    /* 设置 Timer remapping 配置*/
    TIMx->OR =  TIM_Remap;
}

/**
  * 简介:  将 TI1配置为输入。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9、10、11、12、13或14，以选择 TIM 外设设备。
  * 参数:  TIM_ICPolarity : 输入极性。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  *            @arg TIM_ICPolarity_BothEdge
  * 参数:  TIM_ICSelection: 指定要使用的输入。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICSelection_DirectTI: 选择 TIM 输入1连接至IC1。
  *            @arg TIM_ICSelection_IndirectTI: 选择 TIM 输入1连接至IC2。
  *            @arg TIM_ICSelection_TRC: 选择 TIM 输入1连接至 TRC。
  * 参数:  TIM_ICFilter: 指定输入捕获过滤器。
  *          此参数的值必须介于 0x00 和0x0F之间。
  * 返回值: 无
  */
static void TI1_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter) {
    uint16_t tmpccmr1 = 0, tmpccer = 0;

    /* 禁用通道 1: 重设 CC1E 位 */
    TIMx->CCER &= (uint16_t)~TIM_CCER_CC1E;
    tmpccmr1 = TIMx->CCMR1;
    tmpccer = TIMx->CCER;

    /* 选择这个输入并设置过滤器 */
    tmpccmr1 &= ((uint16_t)~TIM_CCMR1_CC1S) & ((uint16_t)~TIM_CCMR1_IC1F);
    tmpccmr1 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));

    /* 选择这个Polarity and set the CC1E 位 */
    tmpccer &= (uint16_t)~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
    tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CCER_CC1E);

    /* 写入 TIMx CCMR1 and CCER registers */
    TIMx->CCMR1 = tmpccmr1;
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  将 TI2配置为输入。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5、8、9或12，以选择 TIM 外设设备。
  * 参数:  TIM_ICPolarity : 输入极性。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  *            @arg TIM_ICPolarity_BothEdge
  * 参数:  TIM_ICSelection: 指定要使用的输入。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICSelection_DirectTI: TIM 输入2被选择为连接到 IC2。
  *            @arg TIM_ICSelection_IndirectTI: TIM 输入2被选择为连接到 IC1。
  *            @arg TIM_ICSelection_TRC: TIM 输入2被选择连接到 TRC。
  * 参数:  TIM_ICFilter: 指定输入捕获过滤器。
  *          此参数的值必须介于 0x00 和0x0F之间。
  * 返回值: 无
  */
static void TI2_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter) {
    uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;

    /* 禁用通道 2: 重设 CC2E 位 */
    TIMx->CCER &= (uint16_t)~TIM_CCER_CC2E;
    tmpccmr1 = TIMx->CCMR1;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t)(TIM_ICPolarity << 4);

    /* 选择这个输入并设置过滤器 */
    tmpccmr1 &= ((uint16_t)~TIM_CCMR1_CC2S) & ((uint16_t)~TIM_CCMR1_IC2F);
    tmpccmr1 |= (uint16_t)(TIM_ICFilter << 12);
    tmpccmr1 |= (uint16_t)(TIM_ICSelection << 8);

    /* 选择这个Polarity and set the CC2E 位 */
    tmpccer &= (uint16_t)~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
    tmpccer |=  (uint16_t)(tmp | (uint16_t)TIM_CCER_CC2E);

    /* 写入 TIMx CCMR1 and CCER registers */
    TIMx->CCMR1 = tmpccmr1 ;
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  将 TI3 配置为输入。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_ICPolarity : 输入极性。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  *            @arg TIM_ICPolarity_BothEdge
  * 参数:  TIM_ICSelection: 指定要使用的输入。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICSelection_DirectTI: TIM 输入3被选择为连接到 IC3。
  *            @arg TIM_ICSelection_IndirectTI: TIM 输入3被选择为连接到 IC4。
  *            @arg TIM_ICSelection_TRC: TIM 输入3被选择为连接到 TRC。
  * 参数:  TIM_ICFilter: 指定输入捕获过滤器。
  *          此参数的值必须介于 0x00 和0x0F之间。
  * 返回值: 无
  */
static void TI3_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter) {
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    /* 禁用通道 3: 重设 CC3E 位 */
    TIMx->CCER &= (uint16_t)~TIM_CCER_CC3E;
    tmpccmr2 = TIMx->CCMR2;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t)(TIM_ICPolarity << 8);

    /* 选择这个输入并设置过滤器 */
    tmpccmr2 &= ((uint16_t)~TIM_CCMR1_CC1S) & ((uint16_t)~TIM_CCMR2_IC3F);
    tmpccmr2 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));

    /* 选择这个Polarity and set the CC3E 位 */
    tmpccer &= (uint16_t)~(TIM_CCER_CC3P | TIM_CCER_CC3NP);
    tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CCER_CC3E);

    /* 写入 TIMx CCMR2 and CCER registers */
    TIMx->CCMR2 = tmpccmr2;
    TIMx->CCER = tmpccer;
}

/**
  * 简介:  将 TI4 配置为输入。
  * 参数:  TIMx: 其中 x 可以是1、2、3、4、5或8，以选择 TIM 外设设备。
  * 参数:  TIM_ICPolarity : 输入极性。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICPolarity_Rising
  *            @arg TIM_ICPolarity_Falling
  *            @arg TIM_ICPolarity_BothEdge
  * 参数:  TIM_ICSelection: 指定要使用的输入。
  *          此参数可以是以下值之一:
  *            @arg TIM_ICSelection_DirectTI: 选择 TIM 输入4连接至IC4。
  *            @arg TIM_ICSelection_IndirectTI: 选择 TIM 输入4连接至IC3。
  *            @arg TIM_ICSelection_TRC: 选择 TIM 输入4连接至 TRC。
  * 参数:  TIM_ICFilter: 指定输入捕获过滤器。
  *          此参数的值必须介于 0x00 和0x0F之间。
  * 返回值: 无
  */
static void TI4_Config(TIM_TypeDef* TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection,
                       uint16_t TIM_ICFilter) {
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    /* 禁用通道 4: 重设 CC4E 位 */
    TIMx->CCER &= (uint16_t)~TIM_CCER_CC4E;
    tmpccmr2 = TIMx->CCMR2;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t)(TIM_ICPolarity << 12);

    /* 选择这个输入并设置过滤器 */
    tmpccmr2 &= ((uint16_t)~TIM_CCMR1_CC2S) & ((uint16_t)~TIM_CCMR1_IC2F);
    tmpccmr2 |= (uint16_t)(TIM_ICSelection << 8);
    tmpccmr2 |= (uint16_t)(TIM_ICFilter << 12);

    /* 选择极性并设置 CC4E位 */
    tmpccer &= (uint16_t)~(TIM_CCER_CC4P | TIM_CCER_CC4NP);
    tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CCER_CC4E);

    /* 写入 TIMx CCMR2 和 CCER 寄存器 */
    TIMx->CCMR2 = tmpccmr2;
    TIMx->CCER = tmpccer ;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
