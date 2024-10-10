/**
  ******************************************************************************
  * file    stm32f4xx_adc.c
  * author  MCD Application Team
  * version V1.8.0
  * date    04-November-2016
  * 简介:    此文件提供固件功能来管理以下内容
  *          模数转换器 (ADC) 外设的功能:
  *           + 初始化和配置(除了 ADC 多模式选择)
  *           + 模拟看门狗配置
  *           + 温度传感器和 Vrefint(内部电压参考)和 VBAT管理
  *           + 常规频道配置
  *           + 常规通道 DMA 配置
  *           + 注入通道配置
  *           + 中断和标志管理
  *
  @verbatim

 ===============================================================================
                     ##### 如何使用此驱动程序 #####
 ===============================================================================
    [..]
    (#) 使用启用 ADC 接口时钟
         RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADCx，ENABLE);

     (#) ADC 引脚配置
          (++) 使用以下函数启用 ADC GPIO 的时钟:
               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx，ENABLE);

          (++) 使用 GPIO_Init() 将这些 ADC 引脚配置为模拟模式;

      (#) 使用 ADC_Init() 函数配置 ADC 预分频器、转换分辨率和数据对齐。
      
      (#) 使用 ADC_Cmd() 函数激活 ADC 外设。

      ***常规频道组配置***
     ============================================
     [..]
        (+) 要配置 ADC 常规通道组功能，请使用
            ADC_Init() 和 ADC_RegularChannelConfig() 函数。

        (+) 要激活连续模式，请使用 ADC_continuousModeCmd() 函数。

        (+) 要配置和激活不连续模式，请使用 ADC_DiscModeChannelCountConfig() 和 ADC_DiscModeCmd() 函数。

        (+) 要读取 ADC 转换值，请使用 ADC_GetConversionValue() 函数。

      *** 多模式 ADC 常规通道配置 ***
     ======================================================
     [..]
        (+) 参考"常规通道组配置"说明配置ADC1、ADC2和ADC3常规通道。

        (+) 使用 ADC_CommonInit() 函数选择多模式 ADC 常规通道功能(双模式或三模式)，
            并使用 ADC_MultiModeDMARequestAfterLastTransferCmd() 函数配置 DMA 模式。

        (+) 使用 ADC_GetMultiModeConversionValue() 函数读取 ADC 转换值。

      *** 用于常规通道组功能配置的 DMA ***
     =============================================================
     [..]
        (+) 要启用常规通道组的 DMA 模式，请使用 ADC_DMACmd() 函数。
        (+) 要在最后一次 DMA 传输结束时连续生成 DMA 请求，请使用 ADC_DMARequestAfterLastTransferCmd() 函数。

      ***注入通道组配置***
     =============================================
     [..]
        (+) 要配置 ADC 注入通道组功能，请使用 ADC_InjectedChannelConfig() 
			      和 ADC_InjectedSequencerLengthConfig() 函数。

        (+) 要激活连续模式，请使用 ADC_continuousModeCmd() 函数。

        (+) 要激活注入不连续模式，请使用 ADC_InjectedDiscModeCmd() 函数。

        (+) 要激活 AutoInjected 模式，请使用 ADC_AutoInjectedConvCmd() 函数。

        (+) 要读取 ADC 转换值，请使用 ADC_GetInjectedConversionValue() 函数。

    @endverbatim
  ******************************************************************************
  * attention
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
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"

/** addtogroup STM32F4xx_StdPeriph_Driver
  * {
  */

/** defgroup ADC
  * brief ADC驱动模块
  * {
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* ADC DISCNUM掩码 */
#define CR1_DISCNUM_RESET         ((uint32_t)0xFFFF1FFF)

/* ADC AWDCH掩码 */
#define CR1_AWDCH_RESET           ((uint32_t)0xFFFFFFE0)

/* ADC 模拟看门狗使能模式掩码 */
#define CR1_AWDMode_RESET         ((uint32_t)0xFF3FFDFF)

/* CR1寄存器掩码 */
#define CR1_CLEAR_MASK            ((uint32_t)0xFCFFFEFF)

/* ADC EXTEN掩码 */
#define CR2_EXTEN_RESET           ((uint32_t)0xCFFFFFFF)

/* ADC JEXTEN掩码 */
#define CR2_JEXTEN_RESET          ((uint32_t)0xFFCFFFFF)

/* ADC JEXTSEL 掩码 */
#define CR2_JEXTSEL_RESET         ((uint32_t)0xFFF0FFFF)

/* CR2 寄存器掩码 */
#define CR2_CLEAR_MASK            ((uint32_t)0xC0FFF7FD)

/* ADC SQx掩码 */
#define SQR3_SQ_SET               ((uint32_t)0x0000001F)
#define SQR2_SQ_SET               ((uint32_t)0x0000001F)
#define SQR1_SQ_SET               ((uint32_t)0x0000001F)

/* ADC L掩码 */
#define SQR1_L_RESET              ((uint32_t)0xFF0FFFFF)

/* ADC JSQx掩码 */
#define JSQR_JSQ_SET              ((uint32_t)0x0000001F)

/* ADC JL掩码 */
#define JSQR_JL_SET               ((uint32_t)0x00300000)
#define JSQR_JL_RESET             ((uint32_t)0xFFCFFFFF)

/* ADC SMPx掩码 */
#define SMPR1_SMP_SET             ((uint32_t)0x00000007)
#define SMPR2_SMP_SET             ((uint32_t)0x00000007)

/* ADC JDRx寄存器偏移 */
#define JDR_OFFSET                ((uint8_t)0x28)

/* ADC CDR 寄存器基址 */
#define CDR_ADDRESS               ((uint32_t)0x40012308)

/* ADC CCR 寄存器掩码 */
#define CR_CLEAR_MASK             ((uint32_t)0xFFFC30E0)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** defgroup ADC_Private_Functions
  * {
  */

/** defgroup ADC_Group1 初始化和配置函数
 *  简介    初始化和配置函数
 *
@verbatim
 ===============================================================================
              ##### 初始化和配置函数 #####
 ===============================================================================
    [..]  本节提供的函数允许:
      (+) 初始化和配置 ADC 预分频器
      (+) ADC 转换分辨率(12 位..6 位)
      (+) 常规组扫描转换模式(多通道或单通道)
      (+) 常规组的 ADC 连续转换模式(连续或单次转换)
      (+) 外部触发 常规组的边沿和源，
      (+) 转换后的数据对齐方式(左或右)
      (+) 将使用常规通道组的定序器完成的 ADC 转换次数
      (+) 多 ADC 模式选择
      (+) 多 ADC 模式的直接存储器访问模式选择
      (+) 2 个采样阶段之间的延迟(用于双或三交错模式)
      (+) 启用或禁用 ADC 外设
@endverbatim
  * {
  */

/**
  * 简介:  将所有 ADC 外设寄存器取消初始化为其默认复位值。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void ADC_DeInit(void) {
    /* 启用所有 ADC 复位状态 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC, ENABLE);

    /* 从复位状态释放所有 ADC */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC, DISABLE);
}

/**
  * 简介:  根据 ADC_InitStruct 中指定的参数初始化 ADCx 外设。
  * 
  * 注意   此功能用于配置 ADC 的全局特性(分辨率和数据对齐)，
			     但其余配置参数特定于常规通道组(扫描模式激活、连续模式激活、
			     外部触发源和边沿、数量 常规通道组定序器中的转换)。

  * 参数:  ADCx:其中 x 可以是 1、2 或 3 以选择 ADC 外设。
  * 
  * 参数:  ADC_InitStruct: 指向 ADC_InitTypeDef 结构的指针，
  *                       该结构包含指定 ADC 外设的配置信息。
  * 返回值: 无
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct) {
    uint32_t tmpreg1 = 0;
    uint8_t tmpreg2 = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_RESOLUTION(ADC_InitStruct->ADC_Resolution));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ScanConvMode));
    assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
    assert_param(IS_ADC_EXT_TRIG_EDGE(ADC_InitStruct->ADC_ExternalTrigConvEdge));
    assert_param(IS_ADC_EXT_TRIG(ADC_InitStruct->ADC_ExternalTrigConv));
    assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));
    assert_param(IS_ADC_REGULAR_LENGTH(ADC_InitStruct->ADC_NbrOfConversion));

    /*---------------------------- ADCx CR1 配置 -----------------*/
    /* 获取 ADCx CR1 值 */
    tmpreg1 = ADCx->CR1;

    /* 清除 RES 和 SCAN 位 */
    tmpreg1 &= CR1_CLEAR_MASK;

    /* 配置 ADCx:扫描转换模式和分辨率 */
    /* 根据 ADC_ScanConvMode 值设置 SCAN 位 */
    /* 根据 ADC_Resolution 值设置 RES 位 */
    tmpreg1 |= (uint32_t)(((uint32_t)ADC_InitStruct->ADC_ScanConvMode << 8) | \
                          ADC_InitStruct->ADC_Resolution);
    /* 写入 ADCx CR1 */
    ADCx->CR1 = tmpreg1;
    /*---------------------------- ADCx CR2 配置 -----------------*/
    /* 获取 ADCx CR2 值 */
    tmpreg1 = ADCx->CR2;

    /* 清除 CONT、ALIGN、EXTEN 和 EXTSEL 位 */
    tmpreg1 &= CR2_CLEAR_MASK;

    /* 配置 ADCx:外部触发事件和边沿、数据对齐和连续转换模式 */
    /* 根据 ADC_DataAlign 值设置 ALIGN 位 */
    /* 根据 ADC_ExternalTrigConvEdge 值设置 EXTEN 位 */
    /* 根据 ADC_ExternalTrigConv 值设置 EXTSEL 位 */
    /* 根据 ADC_ContinuousConvMode 值设置 CONT 位 */
    tmpreg1 |= (uint32_t)(ADC_InitStruct->ADC_DataAlign | \
                          ADC_InitStruct->ADC_ExternalTrigConv |
                          ADC_InitStruct->ADC_ExternalTrigConvEdge | \
                          ((uint32_t)ADC_InitStruct->ADC_ContinuousConvMode << 1));

    /* 写入 ADCx CR2 */
    ADCx->CR2 = tmpreg1;
    /*---------------------------- ADCx SQR1 配置 -----------------*/
    /* 获取 ADCx SQR1 值 */
    tmpreg1 = ADCx->SQR1;

    /* 清除 L 位 */
    tmpreg1 &= SQR1_L_RESET;

    /* 配置 ADCx:常规通道序列长度 */
    /* 根据 ADC_NbrOfConversion 值设置 L 位 */
    tmpreg2 |= (uint8_t)(ADC_InitStruct->ADC_NbrOfConversion - (uint8_t)1);
    tmpreg1 |= ((uint32_t)tmpreg2 << 20);

    /* 写入 ADCx SQR1 */
    ADCx->SQR1 = tmpreg1;
}

/**
  * 简介:  用默认值填充每个 ADC_InitStruct 成员。
  * 
  * 注意  此函数用于初始化 ADC 的全局特性(分辨率和数据对齐)，
  *			  但其余配置参数特定于常规通道组(扫描模式激活、
  *			  连续模式激活、外部触发源和边沿、数量 常规通道组定序器中的转换)。
  * 
  * 参数:  ADC_InitStruct:指向将被初始化的 ADC_InitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct) {
    /* 初始化 ADC_Mode 成员 */
    ADC_InitStruct->ADC_Resolution = ADC_Resolution_12b;

    /* 初始化 ADC_ScanConvMode 成员 */
    ADC_InitStruct->ADC_ScanConvMode = DISABLE;

    /* 初始化 ADC_ContinuousConvMode 成员 */
    ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;

    /* 初始化 ADC_ExternalTrigConvEdge 成员 */
    ADC_InitStruct->ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;

    /* 初始化 ADC_ExternalTrigConv 成员 */
    ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;

    /* 初始化 ADC_DataAlign 成员 */
    ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;

    /* 初始化 ADC_NbrOfConversion 成员 */
    ADC_InitStruct->ADC_NbrOfConversion = 1;
}

/**
  * 简介:  根据 ADC_CommonInitStruct 中指定的参数初始化 ADC 外设。
  * 
  * 参数:  ADC_CommonInitStruct:指向 ADC_CommonInitTypeDef 结构的指针，
  *			   该结构包含所有 ADC 外设的配置信息。
  * 
  * 返回值: 无
  */
void ADC_CommonInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct) {
    uint32_t tmpreg1 = 0;
    /* 检查参数 */
    assert_param(IS_ADC_MODE(ADC_CommonInitStruct->ADC_Mode));
    assert_param(IS_ADC_PRESCALER(ADC_CommonInitStruct->ADC_Prescaler));
    assert_param(IS_ADC_DMA_ACCESS_MODE(ADC_CommonInitStruct->ADC_DMAAccessMode));
    assert_param(IS_ADC_SAMPLING_DELAY(ADC_CommonInitStruct->ADC_TwoSamplingDelay));
    /*---------------------------- ADC CCR 配置 -----------------*/
    /* 获得 ADC CCR 值 */
    tmpreg1 = ADC->CCR;

    /* 清除 MULTI、DELAY、DMA 和 ADCPRE 位 */
    tmpreg1 &= CR_CLEAR_MASK;

    /* 配置 ADCx:多模式、两个采样时间之间的延迟、ADC 预分频器和多模式的 DMA 访问模式 */
    /* 根据 ADC_Mode 值设置 MULTI 位 */
    /* 根据 ADC_Prescaler 值设置 ADCPRE 位 */
    /* 根据 ADC_DMAAccessMode 值设置 DMA 位 */
    /* 根据 ADC_TwoSamplingDelay 值设置 DELAY 位 */
    tmpreg1 |= (uint32_t)(ADC_CommonInitStruct->ADC_Mode |
                          ADC_CommonInitStruct->ADC_Prescaler |
                          ADC_CommonInitStruct->ADC_DMAAccessMode |
                          ADC_CommonInitStruct->ADC_TwoSamplingDelay);

    /* 写入 ADC CCR */
    ADC->CCR = tmpreg1;
}

/**
  * 简介:  用默认值填充每个 ADC_CommonInitStruct 成员。
  * 
  * 参数:  ADC_CommonInitStruct:指向将被初始化的 ADC_CommonInitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct) {
    /* 初始化 ADC_Mode 成员 */
    ADC_CommonInitStruct->ADC_Mode = ADC_Mode_Independent;

    /* 初始化 ADC_Prescaler 成员 */
    ADC_CommonInitStruct->ADC_Prescaler = ADC_Prescaler_Div2;

    /* 初始化 ADC_DMAAccessMode 成员 */
    ADC_CommonInitStruct->ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;

    /* 初始化 ADC_TwoSamplingDelay 成员 */
    ADC_CommonInitStruct->ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
}

/**
  * 简介:  启用或禁用指定的ADC外设设备。
  * 
  * 参数:  ADCx:其中x可以是1、2或3，以选择ADC外设设备。
  * 
  * 参数:  NewState: ADCx外设设备的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 ADON 位以将 ADC 从掉电模式中唤醒 */
        ADCx->CR2 |= (uint32_t)ADC_CR2_ADON;
    } else {
        /* 禁用选定的 ADC 外设 */
        ADCx->CR2 &= (uint32_t)(~ADC_CR2_ADON);
    }
}
/**
  * }
  */

/** defgroup ADC_Group2 模拟看门狗配置函数
 *  简介    模拟看门狗配置功能
 *
@verbatim
 ===============================================================================
             ##### 模拟看门狗配置函数 #####
 ===============================================================================
    [..] 本节提供允许在 ADC 中配置模拟看门狗 (AWD) 函数的功能。

    [..] 典型配置模拟看门狗按照以下步骤完成:
      (#) 使用 ADC_AnalogWatchdogSingleChannelConfig() 函数选择 ADC 保护通道。
      (#) 使用 ADC_AnalogWatchdogThresholdsConfig() 函数配置模拟看门狗下限和上限阈值。
      (#) 使用 ADC_AnalogWatchdogCmd() 函数启用并配置模拟看门狗以启用对一个或多个通道的检查。
@endverbatim
  * {
  */

/**
  * 简介:  启用或禁用单个/所有常规或注入通道上的模拟看门狗
  * 
  * 参数:  ADCx:其中x可以是1、2或3，以选择ADC外设设备。
  * 
  * 参数:  ADC_AnalogWatchdog:ADC模拟看门狗配置。
  *        此参数可以是以下值之一:
  * 		   @arg ADC_AnalogWatchdog_SingleRegEnable			    : 单个常规通道上的模拟看门狗
  * 		   @arg ADC_AnalogWatchdog_SingleInjecEnable		    : 单注入通道上的模拟看门狗
  * 		   @arg ADC_AnalogWatchdog_SingleRegOrInjectEnable	: 单个常规或注入通道上的模拟看门狗
  * 		   @arg ADC_AnalogWatchdog_AllRegEnable				      : 所有常规通道上的模拟看门狗
  * 		   @arg ADC_AnalogWatchdog_AllInjectEnable			    : 所有注入通道上的模拟看门狗
  * 		   @arg ADC_AnalogWatchdog_AllRegAllInjectEnable	  : 所有常规和注入通道上的模拟看门狗
  * 		   @arg ADC_AnalogWatchdog_None						          : 模拟看门狗没有保护通道
  * 
  * 返回值: 无
  */
void ADC_AnalogWatchdogCmd(ADC_TypeDef* ADCx, uint32_t ADC_AnalogWatchdog) {
    uint32_t tmpreg = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_ANALOG_WATCHDOG(ADC_AnalogWatchdog));

    /* 获取旧的寄存器值 */
    tmpreg = ADCx->CR1;

    /* 清除 AWDEN、JAWDEN 和 AWDSGL 位 */
    tmpreg &= CR1_AWDMode_RESET;

    /* 设置模拟看门狗使能模式 */
    tmpreg |= ADC_AnalogWatchdog;

    /* 存储新的寄存器值 */
    ADCx->CR1 = tmpreg;
}

/**
  * 简介:  配置模拟看门狗的高阈值和低阈值。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设设备。
  * 
  * 参数:  高阈值: ADC模拟看门狗高阈值。
  *          此参数必须是12位值。
  * 
  * 参数:  低阈值: ADC模拟看门狗低阈值。
  *          此参数必须是12位值。
  * 
  * 返回值: 无
  */
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef* ADCx, uint16_t HighThreshold,
                                        uint16_t LowThreshold) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_THRESHOLD(HighThreshold));
    assert_param(IS_ADC_THRESHOLD(LowThreshold));

    /* 设置 ADCx 高阈值 */
    ADCx->HTR = HighThreshold;

    /* 设置 ADCx 低阈值 */
    ADCx->LTR = LowThreshold;
}

/**
  * 简介:  配置模拟看门狗保护的单通道
  * 
  * 参数:  ADCx: 其中 x 可以是 1、2 或 3，以选择 ADC 外设。
  * 
  * 参数:  ADC_Channel: 为模拟看门狗配置的 ADC 通道。
  *          此参数可以是以下值之一:
  *            @arg ADC_Channel_0:  已选择 ADC 通道 0
  *            @arg ADC_Channel_1:  已选择 ADC 通道 1
  *            @arg ADC_Channel_2:  已选择 ADC 通道 2
  *            @arg ADC_Channel_3:  已选择 ADC 通道 3
  *            @arg ADC_Channel_4:  已选择 ADC 通道 4
  *            @arg ADC_Channel_5:  已选择 ADC 通道 5
  *            @arg ADC_Channel_6:  已选择 ADC 通道 6
  *            @arg ADC_Channel_7:  已选择 ADC 通道 7
  *            @arg ADC_Channel_8:  已选择 ADC 通道 8
  *            @arg ADC_Channel_9:  已选择 ADC 通道 9
  *            @arg ADC_Channel_10: 已选择 ADC 通道 10
  *            @arg ADC_Channel_11: 已选择 ADC 通道 11
  *            @arg ADC_Channel_12: 已选择 ADC 通道 12
  *            @arg ADC_Channel_13: 已选择 ADC 通道 13
  *            @arg ADC_Channel_14: 已选择 ADC 通道 14
  *            @arg ADC_Channel_15: 已选择 ADC 通道 15
  *            @arg ADC_Channel_16: 已选择 ADC 通道 16
  *            @arg ADC_Channel_17: 已选择 ADC 通道 17
  *            @arg ADC_Channel_18: 已选择 ADC 通道 18
  * 
  * 返回值: 无
  */
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel) {
    uint32_t tmpreg = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));

    /* 获取旧的寄存器值 */
    tmpreg = ADCx->CR1;

    /* 清除模拟看门狗通道选择位 */
    tmpreg &= CR1_AWDCH_RESET;

    /* 设置模拟看门狗通道 */
    tmpreg |= ADC_Channel;

    /* 存储新的寄存器值 */
    ADCx->CR1 = tmpreg;
}
/**
  * }
  */

/** defgroup ADC_Group3温度传感器、Vrefint(内部参考电压)和VBAT(蓄电池电压)管理功能
 *  简介   温度传感器、Vrefint和VBAT管理功能
 *
@verbatim
 ===============================================================================
      ##### 温度传感器、Vrefint和VBAT管理功能 #####
 ===============================================================================
    [..] 本节提供允许启用/禁用ADC与温度传感器、Vrefint和Vbat源之间的内部连接的功能。

    [..] 获取温度传感器和Vrefint通道电压的典型配置如下步骤:
      (#) 使用 ADC_TempSensorVrefintCmd()  函数启用温度传感器和Vrefint源与 ADC 通道的内部连接。
      (#) 使用 ADC_RegularChannelConfig()  或    ADC_InjectedChannelConfiguration() 函数
          选择 ADC_Channel_TempSensor      和/或 ADC_Cannel_Refint
      (#) 使用 ADC_GetConversionValue()    或    ADC_GetInjectedConversionValue() 获取电压值。

    [..] 按照以下步骤完成获取VBAT信道电压的典型配置:
      (#) 使用 ADC_VBATCmd() 函数启用VBAT源与ADC通道的内部连接。
      (#) 使用 ADC_RegularChannelConfig() 或 ADC_InjectedChannelConfiguration() 函数选择 ADC_Channel_Vbat
      (#) 使用 ADC_GetConversionValue() 或 ADC_GetInjectedConversionValue() 获取电压值。

@endverbatim
  * {
  */


/**
  * 简介:  启用或禁用温度传感器和Vrefint通道。
  * 
  * 参数:  NewState: 温度传感器和Vrefint通道的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_TempSensorVrefintCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用温度传感器和Vrefint通道 */
        ADC->CCR |= (uint32_t)ADC_CCR_TSVREFE;
    } else {
        /* 禁用温度传感器和Vrefint通道 */
        ADC->CCR &= (uint32_t)(~ADC_CCR_TSVREFE);
    }
}

/**
  * 简介:  启用或禁用VBAT(蓄电池电压)通道。
  *
  * 注意   在STM32F40xx和STM32V41xx 设备上测得的电池电压等于VBAT/2，
  *         在STM32 F42xx和ST M32F43xx 设备中等于VBAT/4
  *
  * 参数:  NewState: VBAT通道的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void ADC_VBATCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用VBAT通道 */
        ADC->CCR |= (uint32_t)ADC_CCR_VBATE;
    } else {
        /* 禁用VBAT通道 */
        ADC->CCR &= (uint32_t)(~ADC_CCR_VBATE);
    }
}

/**
  * }
  */

/** defgroup ADC_Group4常规通道配置功能
 *  简介   常规通道配置功能
 *
@verbatim
 ===============================================================================
             ##### 常规通道配置功能 #####
 ===============================================================================

    [..] 本节提供了允许管理ADC常规通道的功能，它由2个子节组成:

      (#) 常规通道的配置和管理功能:本小节提供允许配置ADC常规通道的功能:
         (++) 在常规组序列器中为每个通道配置列组
         (++) 配置每个通道的采样时间
         (++) 为常规频道选择转换触发器
         (++) 选择所需的EOC事件行为配置
         (++) 激活连续模式(*)
         (++) 激活不连续模式
         -@@- 请注意，常规频道的以下功能是使用ADC_Init() 函数配置的:
           (+@@) 扫描模式激活
           (+@@) 连续模式激活(**)
           (+@@) 外部触发源
           (+@@) 外部触发边缘
           (+@@) 常规通道组序列器中的转换数。

         -@@- (*)和(**)正在执行相同的配置

      (#) 获取转换数据:本小节在ADC外设设备中提供了一个重要的函数，
          因为它返回当前常规通道的转换数据。读取转换值时，EOC标志自动清除。

          -@- 对于多ADC模式，可以使用ADC_GetMultiModeConversionValue()
          函数同时返回最后一个ADC1、ADC2和ADC3常规转换结果数据(在选定的多模式中)。

@endverbatim
  * {
  */
/**
  * 简介:  为所选ADC常规通道配置其在序列器中的相应秩及其采样时间。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设设备。
  * 
  * 参数:  ADC_Channel: 要配置的ADC通道。
  *          此参数可以是以下值之一:
  *            @arg ADC_Channel_0:  已选择 ADC 通道 0
  *            @arg ADC_Channel_1:  已选择 ADC 通道 1
  *            @arg ADC_Channel_2:  已选择 ADC 通道 2
  *            @arg ADC_Channel_3:  已选择 ADC 通道 3
  *            @arg ADC_Channel_4:  已选择 ADC 通道 4
  *            @arg ADC_Channel_5:  已选择 ADC 通道 5
  *            @arg ADC_Channel_6:  已选择 ADC 通道 6
  *            @arg ADC_Channel_7:  已选择 ADC 通道 7
  *            @arg ADC_Channel_8:  已选择 ADC 通道 8
  *            @arg ADC_Channel_9:  已选择 ADC 通道 9
  *            @arg ADC_Channel_10: 已选择 ADC 通道 10
  *            @arg ADC_Channel_11: 已选择 ADC 通道 11
  *            @arg ADC_Channel_12: 已选择 ADC 通道 12
  *            @arg ADC_Channel_13: 已选择 ADC 通道 13
  *            @arg ADC_Channel_14: 已选择 ADC 通道 14
  *            @arg ADC_Channel_15: 已选择 ADC 通道 15
  *            @arg ADC_Channel_16: 已选择 ADC 通道 16
  *            @arg ADC_Channel_17: 已选择 ADC 通道 17
  *            @arg ADC_Channel_18: 已选择 ADC 通道 18
  * 
  * 参数:  Rank: 常规组序列器中的秩。
  *          此参数必须介于1到16之间。
  * 
  * 参数:  ADC_SampleTime: 要为选定通道设置的采样时间值。
  *          此参数可以是以下值之一:
  *            @arg ADC_SampleTime_3Cycles:   采样时间等于 3   个周期
  *            @arg ADC_SampleTime_15Cycles:  采样时间等于 15  个周期
  *            @arg ADC_SampleTime_28Cycles:  采样时间等于 28  个周期
  *            @arg ADC_SampleTime_56Cycles:  采样时间等于 56  个周期
  *            @arg ADC_SampleTime_84Cycles:  采样时间等于 84  个周期
  *            @arg ADC_SampleTime_112Cycles: 采样时间等于 112 个周期
  *            @arg ADC_SampleTime_144Cycles: 采样时间等于 144 个周期
  *            @arg ADC_SampleTime_480Cycles: 采样时间等于 480 个周期
  * 
  * 返回值: 无
  */
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime) {
    uint32_t tmpreg1 = 0, tmpreg2 = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));
    assert_param(IS_ADC_REGULAR_RANK(Rank));
    assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

    /* 如果选择了ADC_Channel_10…ADC_Cannel_18 */
    if (ADC_Channel > ADC_Channel_9) {
        /* 获取旧寄存器值 */
        tmpreg1 = ADCx->SMPR1;

        /* 计算要清除的掩码 */
        tmpreg2 = SMPR1_SMP_SET << (3 * (ADC_Channel - 10));

        /* 清除旧样本时间 */
        tmpreg1 &= ~tmpreg2;

        /* 计算要设置的掩码 */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));

        /* 设置新采样时间 */
        tmpreg1 |= tmpreg2;

        /* 存储新的寄存器值 */
        ADCx->SMPR1 = tmpreg1;
    } else { /* ADC_Channel包含在ADC_Cchannel_[0..9]中 */
        /* 获取旧寄存器值 */
        tmpreg1 = ADCx->SMPR2;

        /* 计算要清除的掩码 */
        tmpreg2 = SMPR2_SMP_SET << (3 * ADC_Channel);

        /* 清除旧样本时间 */
        tmpreg1 &= ~tmpreg2;

        /* 计算要设置的掩码 */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);

        /* 设置新采样时间 */
        tmpreg1 |= tmpreg2;

        /* 存储新的寄存器值 */
        ADCx->SMPR2 = tmpreg1;
    }

    /* 1至6级 */
    if (Rank < 7) {
        /* 获取旧寄存器值 */
        tmpreg1 = ADCx->SQR3;

        /* 计算要清除的掩码 */
        tmpreg2 = SQR3_SQ_SET << (5 * (Rank - 1));

        /* 清除所选列组的旧SQx位 */
        tmpreg1 &= ~tmpreg2;

        /* 计算要设置的掩码 */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));

        /* 设置所选列组的SQx位 */
        tmpreg1 |= tmpreg2;

        /* 存储新的寄存器值 */
        ADCx->SQR3 = tmpreg1;
    }
    /* 7至12级 */
    else if (Rank < 13) {
        /* 获取旧寄存器值 */
        tmpreg1 = ADCx->SQR2;

        /* 计算要清除的掩码 */
        tmpreg2 = SQR2_SQ_SET << (5 * (Rank - 7));

        /* 清除所选列组的旧SQx位 */
        tmpreg1 &= ~tmpreg2;

        /* 计算要设置的掩码 */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));

        /* 设置所选列组的SQx位 */
        tmpreg1 |= tmpreg2;

        /* 存储新的寄存器值 */
        ADCx->SQR2 = tmpreg1;
    }
    /* 13至16级 */
    else {
        /* 获取旧寄存器值 */
        tmpreg1 = ADCx->SQR1;

        /* 计算要清除的掩码 */
        tmpreg2 = SQR1_SQ_SET << (5 * (Rank - 13));

        /* 清除所选列组的旧SQx位 */
        tmpreg1 &= ~tmpreg2;

        /* 计算要设置的掩码 */
        tmpreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));

        /* 设置所选列组的SQx位 */
        tmpreg1 |= tmpreg2;

        /* 存储新的寄存器值 */
        ADCx->SQR1 = tmpreg1;
    }
}

/**
  * 简介:  启用常规通道的选定 ADC 软件启动转换。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 返回值: 无
  */
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* 为常规组启用选定的ADC转换 */
    ADCx->CR2 |= (uint32_t)ADC_CR2_SWSTART;
}

/**
  * 简介:  获取 ADC 软件转换启动状态
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 返回值:: ADC软件启动转换的新状态(SET或RESET)。
  */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* 检查SWSTART的状态位 */
    if ((ADCx->CR2 & ADC_CR2_SWSTART) != (uint32_t)RESET) {
        /* SWSTART位已设置 */
        bitstatus = SET;
    } else {
        /* SWSTART位复位 */
        bitstatus = RESET;
    }

    /* 返回SWSTART位状态 */
    return  bitstatus;
}


/**
  * 简介:  在每个常规通道转换中启用或禁用EOC。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  NewState: 所选ADC 的新状态 EOC标志上升
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_EOCOnEachRegularChannelCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 在每个常规通道转换中启用选定的ADC EOC上升 */
        ADCx->CR2 |= (uint32_t)ADC_CR2_EOCS;
    } else {
        /* 在每个常规通道转换中禁用选定的ADC EOC上升 */
        ADCx->CR2 &= (uint32_t)(~ADC_CR2_EOCS);
    }
}

/**
  * 简介:  启用或禁用 ADC 连续转换模式。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  NewState: 所选ADC连续转换模式的新状态
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的ADC连续转换模式 */
        ADCx->CR2 |= (uint32_t)ADC_CR2_CONT;
    } else {
        /* 禁用选定的ADC连续转换模式 */
        ADCx->CR2 &= (uint32_t)(~ADC_CR2_CONT);
    }
}

/**
  * 简介:  对 ADC 规则组通道配置间断模式
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  Number: 指定非连续模式下的常规信道计数值。
  *          这个数字必须在1到8之间。
  * 
  * 返回值: 无
  */
void ADC_DiscModeChannelCountConfig(ADC_TypeDef* ADCx, uint8_t Number) {
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;

    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_REGULAR_DISC_NUMBER(Number));

    /* 获取旧寄存器值 */
    tmpreg1 = ADCx->CR1;

    /* 清除旧的不连续模式通道计数 */
    tmpreg1 &= CR1_DISCNUM_RESET;

    /* 设置不连续模式通道计数 */
    tmpreg2 = Number - 1;
    tmpreg1 |= tmpreg2 << 13;

    /* 存储新的寄存器值 */
    ADCx->CR1 = tmpreg1;
}

/**
  * 简介:  使能或者失能指定的 ADC 规则组通道的间断模式
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  NewState: 选定的ADC非连续模式的新状态在常规组通道。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用用选定的ADC常规不连续模式 */
        ADCx->CR1 |= (uint32_t)ADC_CR1_DISCEN;
    } else {
        /* 禁用选定的ADC常规不连续模式 */
        ADCx->CR1 &= (uint32_t)(~ADC_CR1_DISCEN);
    }
}

/**
  * 简介:  返回最近一次 ADCx 规则组的转换结果
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 返回值:: 数据转换值。
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* 返回selected ADC conversion 值 */
    return (uint16_t) ADCx->DR;
}

/**
  * 简介:  返回所选多模式下最后一次 ADC1、ADC2 和 ADC3 常规转换结果数据。
  * 
  * 参数:  无
  * 
  * 返回值: 数据转换值。
  * 
  * 注意   在双模式下，此函数返回的值如下
  *           Data[15:0] : 这些比特位包含 ADC1 的常规数据。
  *           Data[31:16]: 这些比特位包含 ADC2 的常规数据。
  * 
  * 注意   在三重模式下，此函数返回的值如下
  *           Data[15:0] : 这些比特交替地包含ADC1、ADC3和ADC2的常规数据。
  *           Data[31:16]: 这些位交替包含ADC2、ADC1和ADC3的常规数据。
  */
uint32_t ADC_GetMultiModeConversionValue(void) {
    /* 返回multi mode conversion 值 */
    return (*(__IO uint32_t *) CDR_ADDRESS);
}
/**
  * }
  */

/** defgroup ADC_Group5 常规通道DMA配置功能
 *  简介   常规通道DMA配置功能
 *
@verbatim
 ===============================================================================
            ##### 常规通道DMA配置功能 #####
 ===============================================================================
    [..] 本节提供了允许为ADC常规通道配置 DMA的功能。
         由于转换后的常规信道值存储在唯一的数据寄存器中，
            因此使用 DMA转换多个常规信道是有用的。这避免了已存储在ADC 数据寄存器中的数据丢失。
         启用 DMA 模式时(使用ADC_DMACmd() 函数)，在每次转换常规频道后，都会生成DMA 请求。
    [..] 根据"独立ADC模式的DMA禁用选择"配置(使用ADC_DMARequestAfterLastTransferCmd() 函数)，
            在最后一次DMA传输结束时，允许两种可能性:
      (+) 没有向DMA控制器发出新的DMA 请求(功能已禁用)
      (+) 可以继续生成请求(功能已启用)。
    [..] 根据"针对多ADC模式的DMA禁用选择"配置(使用void ADC_MultiModeDMARequestAfterLastTransferCmd() 函数)，
            在最后一次DMA传输结束时，允许两种可能性:
        (+) 没有向DMA控制器发出新的DMA 请求(功能已禁用)
        (+) 可以继续生成请求(功能已启用)。

@endverbatim
  * {
  */

/**
 * 简介:  使能或者失能指定的 ADC 的 DMA 请求
 * 
 * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
 * 
 * 参数:  NewState: 新状态-> selected ADC DMA transfer.
 *          此参数可以是: ENABLE或DISABLE。
 * 
 * 返回值: 无
 */
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 ADC DMA request */
        ADCx->CR2 |= (uint32_t)ADC_CR2_DMA;
    } else {
        /* 禁用被选中的 ADC DMA request */
        ADCx->CR2 &= (uint32_t)(~ADC_CR2_DMA);
    }
}

/**
  * 简介:  在最后一次传输后启用或禁用 ADC DMA 请求(单 ADC 模式)
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  NewState: 最后一次传输后所选ADC DMA 请求的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_DMARequestAfterLastTransferCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 在最后一次传输后启用选定的ADC DMA 请求 */
        ADCx->CR2 |= (uint32_t)ADC_CR2_DDS;
    } else {
        /* 在最后一次传输后禁用选定的ADC DMA 请求 */
        ADCx->CR2 &= (uint32_t)(~ADC_CR2_DDS);
    }
}

/**
  * 简介:  在多 ADC 模式下最后一次传输后启用或禁用 ADC DMA 请求。
  * 
  * 参数:  NewState: 最后一次传输后所选ADC DMA 请求的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 注意   如果启用，则只要转换数据，就会发出DMA 请求，
		   并且多ADC模式的DMA 模式(由ADC_CommonInitStruct.ADC_DMAAccessMode
		   结构成员使用ADC_CommonInit() 函数选择)为ADC_DMAAccessMode_1、
		   ADC_DMAccessMode_2或ADC_DMAAccessMode_3。

  * 返回值: 无
  */
void ADC_MultiModeDMARequestAfterLastTransferCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 在最后一次传输后启用选定的ADC DMA 请求 */
        ADC->CCR |= (uint32_t)ADC_CCR_DDS;
    } else {
        /* 在最后一次传输后禁用选定的ADC DMA 请求 */
        ADC->CCR &= (uint32_t)(~ADC_CCR_DDS);
    }
}
/**
  * }
  */

/** defgroup ADC_Group6 注入的通道 配置功能
 *  简介   注入的通道 配置功能
 *
@verbatim
 ===============================================================================
              ##### 注入的通道 配置功能 #####
 ===============================================================================

    [..] 本节提供了允许配置ADC注入通道的功能。它由2个子部分组成。

      (#) 注入通道的配置功能。本节提供了 功能，允许配置ADC 的注入通道。
        (++) 配置每个通道的注入组序列器中的等级
        (++) 配置每个通道的采样时间
        (++) 激活自动注入模式
        (++) 激活不连续模式
        (++) 激活扫描模式
        (++) 外部/软件触发源
        (++) 外部触发边缘
        (++) 注入的通道排序器。

      (#) 获取指定的注入通道转换数据。这个小节
            在ADC外设中提供了一个重要的功能，因为它返回了 特定注入通道的转换数据。

@endverbatim
  * {
  */
/**
  * 简介:  设置指定 ADC 的注入组通道，设置它们的转化顺序和采样时间
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  ADC_Channel: 要配置的ADC通道。
  *          此参数可以是以下值之一:
  *            @arg ADC_Channel_0: 已选择ADC通道0
  *            @arg ADC_Channel_1: 已选择ADC通道1
  *            @arg ADC_Channel_2: 已选择ADC通道2
  *            @arg ADC_Channel_3: 已选择ADC通道3
  *            @arg ADC_Channel_4: 已选择ADC通道4
  *            @arg ADC_Channel_5: 已选择ADC通道5
  *            @arg ADC_Channel_6: 已选择ADC通道6
  *            @arg ADC_Channel_7: 已选择ADC通道7
  *            @arg ADC_Channel_8: 已选择ADC通道8
  *            @arg ADC_Channel_9: 已选择ADC通道9
  *            @arg ADC_Channel_10: 已选择ADC通道10
  *            @arg ADC_Channel_11: 已选择ADC通道11
  *            @arg ADC_Channel_12: 已选择ADC通道12
  *            @arg ADC_Channel_13: 已选择ADC通道13
  *            @arg ADC_Channel_14: 已选择ADC通道14
  *            @arg ADC_Channel_15: 已选择ADC通道15
  *            @arg ADC_Channel_16: 已选择ADC通道16
  *            @arg ADC_Channel_17: 已选择ADC通道17
  *            @arg ADC_Channel_18: 已选择ADC通道18
  * 
  * 参数:  Rank: 注入组排序器中的等级。
  *          这个参数必须在1到4之间。
  * 
  * 参数:  ADC_SampleTime: 要为所选通道设置的采样时间值。
  *          此参数可以是以下值之一:
  *            @arg ADC_SampleTime_3Cycles: 采样时间等于3 cycles
  *            @arg ADC_SampleTime_15Cycles: 采样时间等于15 cycles
  *            @arg ADC_SampleTime_28Cycles: 采样时间等于28 cycles
  *            @arg ADC_SampleTime_56Cycles: 采样时间等于56 cycles
  *            @arg ADC_SampleTime_84Cycles: 采样时间等于84 cycles
  *            @arg ADC_SampleTime_112Cycles: 采样时间等于112 cycles
  *            @arg ADC_SampleTime_144Cycles: 采样时间等于144 cycles
  *            @arg ADC_SampleTime_480Cycles: 采样时间等于480 cycles
  * 
  * 返回值: 无
  */
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime) {
    uint32_t tmpreg1 = 0, tmpreg2 = 0, tmpreg3 = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));
    assert_param(IS_ADC_INJECTED_RANK(Rank));
    assert_param(IS_ADC_SAMPLE_TIME(ADC_SampleTime));

    /* 如果选择了ADC_Channel_10…ADC_Cannel_18 */
    if (ADC_Channel > ADC_Channel_9) {
        /* 获取旧寄存器值 */
        tmpreg1 = ADCx->SMPR1;
        /* 计算要清除的掩码 */
        tmpreg2 = SMPR1_SMP_SET << (3 * (ADC_Channel - 10));
        /* 清除旧样本时间 */
        tmpreg1 &= ~tmpreg2;
        /* 计算要设置的掩码 */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * (ADC_Channel - 10));
        /* 设置新采样时间 */
        tmpreg1 |= tmpreg2;
        /* 存储新的寄存器值 */
        ADCx->SMPR1 = tmpreg1;
    } else { /* ADC_Channel包含在ADC_Cchannel_[0..9]中 */
        /* 获取旧寄存器值 */
        tmpreg1 = ADCx->SMPR2;
        /* 计算要清除的掩码 */
        tmpreg2 = SMPR2_SMP_SET << (3 * ADC_Channel);
        /* 清除旧样本时间 */
        tmpreg1 &= ~tmpreg2;
        /* 计算要设置的掩码 */
        tmpreg2 = (uint32_t)ADC_SampleTime << (3 * ADC_Channel);
        /* 设置新采样时间 */
        tmpreg1 |= tmpreg2;
        /* 存储新的寄存器值 */
        ADCx->SMPR2 = tmpreg1;
    }

    /* Rank 配置*/
    /* 获取旧寄存器值 */
    tmpreg1 = ADCx->JSQR;
    /* Get JL value: Number = JL+1 */
    tmpreg3 =  (tmpreg1 & JSQR_JL_SET) >> 20;
    /* 计算要清除的掩码: ((Rank-1)+(4-JL-1)) */
    tmpreg2 = JSQR_JSQ_SET << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
    /* 清除所选列组的旧JSQx位 */
    tmpreg1 &= ~tmpreg2;
    /* 计算要设置的掩码: ((Rank-1)+(4-JL-1)) */
    tmpreg2 = (uint32_t)ADC_Channel << (5 * (uint8_t)((Rank + 3) - (tmpreg3 + 1)));
    /* 为所选列组设置JSQx位 */
    tmpreg1 |= tmpreg2;
    /* 存储新的寄存器值 */
    ADCx->JSQR = tmpreg1;
}

/**
  * 简介:  配置注入通道的定序器长度
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  Length: 序列器长度。
  *          此参数必须是1到4之间的数字。
  * 
  * 返回值: 无
  */
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef* ADCx, uint8_t Length) {
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_INJECTED_LENGTH(Length));

    /* 获取旧寄存器值 */
    tmpreg1 = ADCx->JSQR;

    /* 清除旧注入序列长度JL位 */
    tmpreg1 &= JSQR_JL_RESET;

    /* 设置注入序列长度JL位 */
    tmpreg2 = Length - 1;
    tmpreg1 |= tmpreg2 << 20;

    /* 存储新的寄存器值 */
    ADCx->JSQR = tmpreg1;
}

/**
  * 简介:  设置注入通道转换值偏移
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  ADC_InjectedChannel: ADC注入通道以设置其偏移。
  *          此参数可以是以下值之一:
  *            @arg ADC_InjectedChannel_1: 已选择注入通道1
  *            @arg ADC_InjectedChannel_2: 已选择注入通道2
  *            @arg ADC_InjectedChannel_3: 已选择注入通道3
  *            @arg ADC_InjectedChannel_4: 已选择注入通道4
  * 
  * 参数:  Offset: 所选ADC注入通道的偏移值
  *          此参数必须是12位值。
  * 
  * 返回值: 无
  */
void ADC_SetInjectedOffset(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset) {
    __IO uint32_t tmp = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));
    assert_param(IS_ADC_OFFSET(Offset));

    tmp = (uint32_t)ADCx;
    tmp += ADC_InjectedChannel;

    /* 设置所选注入通道数据偏移 */
    *(__IO uint32_t *) tmp = (uint32_t)Offset;
}

/**
 * 简介:  为注入通道转换配置ADCx外部触发器。
 * 
 * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
 * 
 * 参数:  ADC_ExternalTrigInjecConv: 指定启动注入转换的ADC触发器。
 *          此参数可以是以下值之一:
 *            @arg ADC_ExternalTrigInjecConv_T1_CC4:   已选择计时器 1 捕获比较4
 *            @arg ADC_ExternalTrigInjecConv_T1_TRGO:  已选择定时器 1 TRGO事件
 *            @arg ADC_ExternalTrigInjecConv_T2_CC1:   已选择计时器 2 捕获比较1
 *            @arg ADC_ExternalTrigInjecConv_T2_TRGO:  已选择计时器 2 TRGO事件
 *            @arg ADC_ExternalTrigInjecConv_T3_CC2:   已选择定时器 3 捕获比较2
 *            @arg ADC_ExternalTrigInjecConv_T3_CC4:   已选择计时器 3 捕获比较4
 *            @arg ADC_ExternalTrigInjecConv_T4_CC1:   已选择计时器 4 捕获比较1
 *            @arg ADC_ExternalTrigInjecConv_T4_CC2:   已选择计时器 4 捕获比较2
 *            @arg ADC_ExternalTrigInjecConv_T4_CC3:   已选择计时器 4 捕获比较3
 *            @arg ADC_ExternalTrigInjecConv_T4_TRGO:  已选择定时器 4 TRGO事件
 *            @arg ADC_ExternalTrigInjecConv_T5_CC4:   已选择计时器 5 捕获比较4
 *            @arg ADC_ExternalTrigInjecConv_T5_TRGO:  已选择定时器 5 TRGO事件
 *            @arg ADC_ExternalTrigInjecConv_T8_CC2:   已选择定时器 8 捕获比较2
 *            @arg ADC_ExternalTrigInjecConv_T8_CC3:   已选择计时器 8 捕获比较3
 *            @arg ADC_ExternalTrigInjecConv_T8_CC4:   已选择计时器 8 捕获比较4
 *            @arg ADC_ExternalTrigInjecConv_Ext_IT15: 已选择外部中断行15事件
 * 
 * 返回值: 无
 */
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConv) {
    uint32_t tmpreg = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_EXT_INJEC_TRIG(ADC_ExternalTrigInjecConv));

    /* 获取旧寄存器值 */
    tmpreg = ADCx->CR2;

    /* 清除注入组的旧外部事件选择 */
    tmpreg &= CR2_JEXTSEL_RESET;

    /* 设置注入组的外部事件选择 */
    tmpreg |= ADC_ExternalTrigInjecConv;

    /* 存储新的寄存器值 */
    ADCx->CR2 = tmpreg;
}

/**
  * 简介:  为注入通道转换配置ADCx外部触发边缘。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  ADC_ExternalTrigInjecConvEdge: 指定启动注入转换的ADC外部触发器边缘。
  *          此参数可以是以下值之一:
  *            @arg ADC_ExternalTrigInjecConvEdge_None: 为注入转换禁用外部触发器
  *            @arg ADC_ExternalTrigInjecConvEdge_Rising: 上升沿检测
  *            @arg ADC_ExternalTrigInjecConvEdge_Falling: 下降沿检测
  *            @arg ADC_ExternalTrigInjecConvEdge_RisingFalling: 上升沿和下降沿检测
  * 
  * 返回值: 无
  */
void ADC_ExternalTrigInjectedConvEdgeConfig(ADC_TypeDef* ADCx, uint32_t ADC_ExternalTrigInjecConvEdge) {
    uint32_t tmpreg = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_EXT_INJEC_TRIG_EDGE(ADC_ExternalTrigInjecConvEdge));
    /* 获取旧寄存器值 */
    tmpreg = ADCx->CR2;
    /* 清除注入组的旧外部触发器边缘 */
    tmpreg &= CR2_JEXTEN_RESET;
    /* 为注射组设置新的外部触发边缘 */
    tmpreg |= ADC_ExternalTrigInjecConvEdge;
    /* 存储新的寄存器值 */
    ADCx->CR2 = tmpreg;
}

/**
  * 简介:  启用所选ADC软件启动注入通道的转换。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 返回值: 无
  */
void ADC_SoftwareStartInjectedConv(ADC_TypeDef* ADCx) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    /* 为注入组启用选定的ADC转换 */
    ADCx->CR2 |= (uint32_t)ADC_CR2_JSWSTART;
}

/**
  * 简介:  获取所选ADC软件开始注入的转换状态。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 返回值:: ADC软件的新状态开始注入转换(SET或RESET)。
  */
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef* ADCx) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* 检查JSWSTART位的状态 */
    if ((ADCx->CR2 & ADC_CR2_JSWSTART) != (uint32_t)RESET) {
        /* JSWSTART位已设置 */
        bitstatus = SET;
    } else {
        /* JSWSTART位重置 */
        bitstatus = RESET;
    }

    /* 返回JSWSTART位状态 */
    return  bitstatus;
}

/**
  * 简介:  在常规ADC自动注入组转换之后，启用或禁用所选ADC自动插入组转换。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  NewState: 所选ADC自动注入转换的新状态
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_AutoInjectedConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用所选ADC自动注入组转换 */
        ADCx->CR1 |= (uint32_t)ADC_CR1_JAUTO;
    } else {
        /* 禁用所选ADC自动注入组转换 */
        ADCx->CR1 &= (uint32_t)(~ADC_CR1_JAUTO);
    }
}

/**
  * 简介:  为指定ADC 的注入组通道启用或禁用不连续模式
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  NewState: 注入组通道上所选ADC不连续模式的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_InjectedDiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用所选ADC注入不连续模式 */
        ADCx->CR1 |= (uint32_t)ADC_CR1_JDISCEN;
    } else {
        /* 禁用所选ADC注入不连续模式 */
        ADCx->CR1 &= (uint32_t)(~ADC_CR1_JDISCEN);
    }
}

/**
  * 简介:  返回ADC注入通道转换结果
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  ADC_InjectedChannel: 转换后的ADC注入通道。
  *          此参数可以是以下值之一:
  *            @arg ADC_InjectedChannel_1: 已选择注入通道1
  *            @arg ADC_InjectedChannel_2: 已选择注入通道2
  *            @arg ADC_InjectedChannel_3: 已选择注入通道3
  *            @arg ADC_InjectedChannel_4: 已选择注入通道4
  * 
  * 返回值:: 数据转换值。
  */
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef* ADCx, uint8_t ADC_InjectedChannel) {
    __IO uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_INJECTED_CHANNEL(ADC_InjectedChannel));

    tmp = (uint32_t)ADCx;
    tmp += ADC_InjectedChannel + JDR_OFFSET;

    /* 返回所选注入通道转换数据值 */
    return (uint16_t) (*(__IO uint32_t*)  tmp);
}
/**
  * }
  */

/** defgroup ADC_Group7中断和标志管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
            ##### 中断和标记管理函数 #####
 ===============================================================================

    [..] 本节提供了允许配置ADC中断、获取状态、清除标志和中断挂起位的函数。

    [..] 每个ADC提供4个中断源和6个标志，可分为3组:

  *** ADC常规通道的标志和中断 ***
  =====================================================
    [..]
      (+) Flags :
        (##) ADC_FLAG_OVR : 常规转换数据丢失时的溢出检测

        (##) ADC_FLAG_EOC : 常规通道转换结束==>以指示(取决于EOCS位，
                            由ADC_EOCOnEachRegularChannelCmd()管理)以下内容的结束:
             (+++) 常规CHANNEL转换
             (+++) 常规GROUP转换的序列。

        (##) ADC_FLAG_STRT: 常规通道开始==>指示常规通道转换开始的时间。
    [..]
      (+) 中断 :
        (##) ADC_IT_OVR : 指定超限检测事件的中断源。
        (##) ADC_IT_EOC : 指定常规通道转换结束事件的中断源。


  *** ADC注入通道的标志和中断 ***
  ======================================================
    [..]
      (+) Flags :
        (##) ADC_FLAG_JEOC : 注入的通道转换结束==>表示注入的GROUP转换结束

        (##) ADC_FLAG_JSTRT: 注入通道启动==>以指示注入GROUP转换开始时的硬件。
    [..]
      (+) 中断 :
        (##) ADC_IT_JEOC : 指定注入通道转换结束事件的中断源。

  *** ADC 的一般标志和中断 ***
  ================================================
    [..]
      (+)标志 :
        (##) ADC_FLAG_AWD: 模拟看门狗==>指示转换后的电压是否超过编程设定的阈值。
    [..]
      (+) 中断 :
        (##) ADC_IT_AWD : 指定模拟看门狗事件的中断源。


    [..] 用户应确定在其应用程序中将使用哪种模式来管理ADC控制器事件:轮询模式或中断模式。

    [..] 在轮询模式下，建议使用以下功能:
      (+) ADC_GetFlagStatus() : 以检查是否发生标志事件。
      (+) ADC_ClearFlag()     : 以清除标志事件。

    [..] 在中断模式下，建议使用以下功能:
      (+) ADC_ITConfig()          : 以启用或禁用中断源。
      (+) ADC_GetITStatus()       : 检查是否发生中断。
      (+) ADC_ClearITPendingBit() : 清除中断挂起位(相应标志)。
@endverbatim
  * {
  */
/**
  * 简介:  启用或禁用指定的ADC中断。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  ADC_IT: 指定要启用或禁用的ADC中断源。
  *          此参数可以是以下值之一:
  *            @arg ADC_IT_EOC: 转换中断屏蔽结束
  *            @arg ADC_IT_AWD: 模拟看门狗中断屏蔽
  *            @arg ADC_IT_JEOC: 注入转换中断掩码结束
  *            @arg ADC_IT_OVR: 超限中断启用
  * 
  * 参数:  NewState: 指定ADC中断的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void ADC_ITConfig(ADC_TypeDef* ADCx, uint16_t ADC_IT, FunctionalState NewState) {
    uint32_t itmask = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_IT(ADC_IT));

    /* 获取ADC IT索引 */
    itmask = (uint8_t)ADC_IT;
    itmask = (uint32_t)0x01 << itmask;

    if (NewState != DISABLE) {
        /* 启用所选ADC中断 */
        ADCx->CR1 |= itmask;
    } else {
        /* 禁用所选ADC中断 */
        ADCx->CR1 &= (~(uint32_t)itmask);
    }
}

/**
  * 简介:  检查是否设置了指定的ADC标志。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  ADC_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg ADC_FLAG_AWD:   模拟看门狗标志
  *            @arg ADC_FLAG_EOC:   转换结束标志
  *            @arg ADC_FLAG_JEOC:  注入组转换标志结束
  *            @arg ADC_FLAG_JSTRT: 注入组转换标志的开始
  *            @arg ADC_FLAG_STRT:  常规组转换标志的开始
  *            @arg ADC_FLAG_OVR:   溢出标志
  * 
  * 返回值:: ADC_FLAG的新状态(SET或RESET)。
  */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint8_t ADC_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_GET_FLAG(ADC_FLAG));

    /* 检查指定ADC标志的状态 */
    if ((ADCx->SR & ADC_FLAG) != (uint8_t)RESET) {
        /* ADC_FLAG已设置 */
        bitstatus = SET;
    } else {
        /* ADC_FLAG复位 */
        bitstatus = RESET;
    }

    /* 返回ADC_FLAG状态 */
    return  bitstatus;
}

/**
  * 简介:  清除ADCx的挂起标志。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设。
  * 
  * 参数:  ADC_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *            @arg ADC_FLAG_AWD:   模拟看门狗标志
  *            @arg ADC_FLAG_EOC:   转换结束标志
  *            @arg ADC_FLAG_JEOC:  注入组转换标志结束
  *            @arg ADC_FLAG_JSTRT: 注入组转换标志的开始
  *            @arg ADC_FLAG_STRT:  常规组转换标志的开始
  *            @arg ADC_FLAG_OVR:   溢出标志
  * 
  * 返回值: 无
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint8_t ADC_FLAG) {
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

    /* 清除所选ADC标志 */
    ADCx->SR = ~(uint32_t)ADC_FLAG;
}

/**
  * 简介:  检查指定的ADC中断是否发生。
  * 
  * 参数:  ADCx:   其中x可以是1、2或3，以选择ADC外设设备。
  * 
  * 参数:  ADC_IT: 指定要检查的ADC中断源。
  *          此参数可以是以下值之一:
  *            @arg ADC_IT_EOC:  转换中断屏蔽结束
  *            @arg ADC_IT_AWD:  模拟看门狗中断屏蔽
  *            @arg ADC_IT_JEOC: 注入转换中断掩码结束
  *            @arg ADC_IT_OVR:  溢出中断掩码
  * 
  * 返回值:: ADC_IT的新状态(SET或RESET)。
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint16_t ADC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t itmask = 0, enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_IT(ADC_IT));

    /* 获取ADC IT索引 */
    itmask = ADC_IT >> 8;

    /* 获取ADC_IT启用位状态 */
    enablestatus = (ADCx->CR1 & ((uint32_t)0x01 << (uint8_t)ADC_IT)) ;

    /* 检查指定ADC中断的状态 */
    if (((ADCx->SR & itmask) != (uint32_t)RESET) && enablestatus) {
        /* ADC_IT已设置 */
        bitstatus = SET;
    } else {
        /* ADC_IT重置 */
        bitstatus = RESET;
    }

    /* 返回ADC_IT状态 */
    return  bitstatus;
}

/**
  * 简介:  清除ADCx的中断挂起位。
  * 
  * 参数:  ADCx: 其中x可以是1、2或3，以选择ADC外设设备。
  * 
  * 参数:  ADC_IT: 指定要清除的ADC中断挂起位。
  *          此参数可以是以下值之一:
  *            @arg ADC_IT_EOC:  转换中断屏蔽结束
  *            @arg ADC_IT_AWD:  模拟看门狗中断屏蔽
  *            @arg ADC_IT_JEOC: 注入转换中断掩码结束
  *            @arg ADC_IT_OVR:  溢出中断掩码
  * 
  * 返回值: 无
  */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint16_t ADC_IT) {
    uint8_t itmask = 0;
    /* 检查参数 */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_IT(ADC_IT));
    /* 获取ADC IT索引 */
    itmask = (uint8_t)(ADC_IT >> 8);
    /* 清除所选ADC中断挂起位 */
    ADCx->SR = ~(uint32_t)itmask;
}
/**
  * }
  */

/**
  * }
  */

/**
  * }
  */

/**
  * }
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
