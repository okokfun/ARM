/**
  ******************************************************************************
  * 文件:    stm32f4xx_dac.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
   * 简介:    该文件提供固件功能来管理数模转换器 (DAC) 外设的以下功能:
  *           + DAC通道配置: 触发、输出缓冲器、数据格式
  *           + DMA管理
  *           + 中断和标志管理
  *
 @verbatim
 ===============================================================================
                      ##### DAC 外设功能 #####
 ===============================================================================
    [..]
      *** DAC 通道 ***
      ====================
    [..]
    该器件集成了两个 12 位数模转换器，可独立使用或同时使用(双模式):
      (#) DAC 通道 1，DAC_OUT1 (PA4) 作为输出
      (#) DAC 通道 2，DAC_OUT2 (PA5) 作为输出

      *** DAC 触发器 ***
      ====================
    [..]
    使用 DAC_Trigger_None 可以不触发数模转换，
	并且一旦使用 DAC_SetChannel1Data() / DAC_SetChannel2Data() 函数写入 DHRx 寄存器，DAC_OUT1/DAC_OUT2 就可用。
    [..]
    数模转换可以通过以下方式触发:
      (#) 外部事件:EXTI 线 9(任何 GPIOx_Pin9)使用 DAC_Trigger_Ext_IT9。
           使用的引脚 (GPIOx_Pin9) 必须配置为输入模式。

      (#) 定时器 TRGO:TIM2、TIM4、TIM5、TIM6、TIM7 和 TIM8
           (DAC_Trigger_T2_TRGO、DAC_Trigger_T4_TRGO...)
           应使用 TIM_SelectOutputTrigger() 选择计时器 TRGO 事件

      (#) 使用 DAC_Trigger_Software 的软件

      *** DAC 缓冲模式功能 ***
      ===============================
      [..]
      每个 DAC 通道都集成了一个输出缓冲器，可用于降低输出阻抗，并直接驱动外部负载，而无需添加外部运算放大器。
      要启用，输出缓冲区使用
       DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
      [..]
      (@) 有关带和不带输出缓冲器的输出阻抗值的更多详细信息，请参阅器件数据表。

       *** DAC 波形生成功能 ***
       ===================================
       [..]
       两个 DAC 通道均可用于生成
         (#) 使用 DAC_WaveGeneration_Noise 的噪声波
         (#) 使用 DAC_WaveGeneration_Triangle 的三角波

          -@-  可以使用 DAC_WaveGeneration_None 禁用波形生成

       *** DAC数据格式 ***
       =======================
       [..]
       DAC 数据格式可以是:
		 (#) 使用 DAC_Align_8b_R 进行 8 位右对齐
         (#) 使用 DAC_Align_12b_L 进行 12 位左对齐
         (#) 使用 DAC_Align_12b_R 的 12 位右对齐

       *** DAC 数据值与电压对应关系 ***
       ================================================
       [..]
       每个 DAC 通道引脚上的模拟输出电压由以下公式确定:
       DAC_OUTx = VREF+ * DOR / 4095
       其中DOR是数据输出寄存器
          VEF+是输入电压基准(参考器件数据手册)。
        e.g. To set DAC_OUT1 to 0.7V, use
          DAC_SetChannel1Data(DAC_Align_12b_R, 868);
          Assuming that VREF+ = 3.3V, DAC_OUT1 = (3.3 * 868) / 4095 = 0.7V

       *** DMA 请求  ***
       =====================
       [..]
       如果使用 DAC_DMACmd() 启用 DMA1 请求，则会在发生外部触发(但不是软件触发)时生成 DMA1 请求
       [..]
       DMA1 请求映射如下:
         (#) DAC 通道 1:映射到 DMA1 流 5 通道 7，必须已配置
         (#) DAC 通道 2:映射到 DMA1 流 6 通道 7，必须已配置


                      ##### 如何使用此驱动程序 #####
 ===============================================================================
    [..]
      (+) 必须启用 DAC APB 时钟才能使用以下方式对 DAC 寄存器进行写访问
          RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE)
      (+) 在模拟模式下配置 DAC_OUTx (DAC_OUT1: PA4, DAC_OUT2: PA5)。
      (+) 使用 DAC_Init() 函数配置 DAC 通道
      (+) 使用 DAC_Cmd() 函数启用 DAC 通道

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
#include "stm32f4xx_dac.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DAC
  * 简介: DAC 驱动模块
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* CR 寄存器掩码 */
#define CR_CLEAR_MASK              ((uint32_t)0x00000FFE)

/* DAC 双通道 SWTRIG 掩码 */
#define DUAL_SWTRIG_SET            ((uint32_t)0x00000003)
#define DUAL_SWTRIG_RESET          ((uint32_t)0xFFFFFFFC)

/* DHR 寄存器的偏移量 */
#define DHR12R1_OFFSET             ((uint32_t)0x00000008)
#define DHR12R2_OFFSET             ((uint32_t)0x00000014)
#define DHR12RD_OFFSET             ((uint32_t)0x00000020)

/* DOR 寄存器偏移量 */
#define DOR_OFFSET                 ((uint32_t)0x0000002C)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup DAC_Private_Functions
  * @{
  */

/** @defgroup DAC_Group1 DAC通道配置
 *  简介   DAC通道配置:触发器、输出缓冲器、数据格式
 *
@verbatim
 ===============================================================================
   ##### DAC通道配置:触发器、输出缓冲器、数据格式 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  用于将 DAC 配置设置为默认复位状态的函数
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void DAC_DeInit(void) {
    /* 启用DAC复位状态 */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, ENABLE);
    /* 释放DAC from 复位状态 */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_DAC, DISABLE);
}

/**
  * 简介:  根据 DAC_InitStruct 中指定的参数初始化 DAC 外设。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  DAC_InitStruct: 指向 DAC_InitTypeDef 结构的指针，该结构包含了 包含指定DAC通道的配置信息。
  * 
  * 返回值: 无
  */
void DAC_Init(uint32_t DAC_Channel, DAC_InitTypeDef* DAC_InitStruct) {
    uint32_t tmpreg1 = 0, tmpreg2 = 0;

    /* 检查 DAC的参数 */
    assert_param(IS_DAC_TRIGGER(DAC_InitStruct->DAC_Trigger));
    assert_param(IS_DAC_GENERATE_WAVE(DAC_InitStruct->DAC_WaveGeneration));
    assert_param(IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude));
    assert_param(IS_DAC_OUTPUT_BUFFER_STATE(DAC_InitStruct->DAC_OutputBuffer));

    /*---------------------------- DAC CR 配置 --------------------------*/
    /* 获取DAC CR 值 */
    tmpreg1 = DAC->CR;
    /* 清除 BOFFx, TENx, TSELx, WAVEx and MAMPx 位 */
    tmpreg1 &= ~(CR_CLEAR_MASK << DAC_Channel);
    /* 为选定的DAC通道进行配置:缓冲器输出、触发器、波形生成、波形生成的掩码/振幅 */
    /* 根据DAC_Trigger设置TSELx和TENx位值 */
    /* 根据DAC_WaveGeneration设置WAVEx位值 */
    /* 根据DAC_LFSRUnmask_TriangleAmplitude设置MAMPx位值 */
    /* 根据DAC_OutputBuffer设置BOFFx位值 */
    tmpreg2 = (DAC_InitStruct->DAC_Trigger | DAC_InitStruct->DAC_WaveGeneration |
               DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude | \
               DAC_InitStruct->DAC_OutputBuffer);
    /* 根据DAC_Channel计算CR寄存器的值 */
    tmpreg1 |= tmpreg2 << DAC_Channel;
    /* 写入DAC CR */
    DAC->CR = tmpreg1;
}

/**
  * 简介:  用默认值填充每个 DAC_InitStruct 成员。
  * 
  * 参数:  DAC_InitStruct: 指向DAC_InitTypeDef结构的指针，该结构将被初始化。
  * 
  * 返回值: 无
  */
void DAC_StructInit(DAC_InitTypeDef* DAC_InitStruct) {
    /*--------------- 重置DAC初始结构参数值-----------------*/
    /* 初始化 DAC_Trigger 成员 */
    DAC_InitStruct->DAC_Trigger = DAC_Trigger_None;
    /* 初始化 DAC_WaveGeneration 成员 */
    DAC_InitStruct->DAC_WaveGeneration = DAC_WaveGeneration_None;
    /* 初始化 DAC_LFSRUnmask_TriangleAmplitude 成员 */
    DAC_InitStruct->DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    /* 初始化 DAC_OutputBuffer 成员 */
    DAC_InitStruct->DAC_OutputBuffer = DAC_OutputBuffer_Enable;
}

/**
  * 简介:  启用或停用指定的DAC通道。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  NewState: DAC通道的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 注意:   当DAC通道被启用时，触发源就不能再被修改。
  * 
  * 返回值: 无
  */
void DAC_Cmd(uint32_t DAC_Channel, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的DAC通道 */
        DAC->CR |= (DAC_CR_EN1 << DAC_Channel);
    } else {
        /* 禁用选定的DAC通道 */
        DAC->CR &= (~(DAC_CR_EN1 << DAC_Channel));
    }
}

/**
  * 简介:  启用或禁用选定的DAC通道软件触发。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  NewState: 所选DAC通道软件触发的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void DAC_SoftwareTriggerCmd(uint32_t DAC_Channel, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 为选定的DAC通道启用软件触发 */
        DAC->SWTRIGR |= (uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4);
    } else {
        /* 禁用所选DAC通道的软件触发 */
        DAC->SWTRIGR &= ~((uint32_t)DAC_SWTRIGR_SWTRIG1 << (DAC_Channel >> 4));
    }
}

/**
  * 简介:  同时启用或禁用两个 DAC 通道软件触发。
  * 
  * 参数:  NewState: DAC通道的新状态的软件触发。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void DAC_DualSoftwareTriggerCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 为两个DAC通道启用软件触发 */
        DAC->SWTRIGR |= DUAL_SWTRIG_SET;
    } else {
        /* 禁用两个DAC通道的软件触发 */
        DAC->SWTRIGR &= DUAL_SWTRIG_RESET;
    }
}

/**
  * 简介:  启用或禁用选定的 DAC 通道波形生成。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  DAC_Wave: 指定要启用或禁用的波浪类型。
  *          此参数可以是以下值之一:
  *            @arg DAC_Wave_Noise: 噪声波的产生
  *            @arg DAC_Wave_Triangle: 三角波生成
  * 
  * 参数:  NewState: 选定的DAC通道波形生成的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void DAC_WaveGenerationCmd(uint32_t DAC_Channel, uint32_t DAC_Wave, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_WAVE(DAC_Wave));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用为选定的DAC通道生成选定的波形 */
        DAC->CR |= DAC_Wave << DAC_Channel;
    } else {
        /* 禁用为选定的DAC通道生成选定的波形 */
        DAC->CR &= ~(DAC_Wave << DAC_Channel);
    }
}

/**
  * 简介:  为 DAC 通道 1 设置指定的数据保持寄存器值。
  * 
  * 参数:  DAC_Align: 指定DAC通道1的数据排列。
  *          此参数可以是以下值之一:
  *            @arg DAC_Align_8b_R: 选择8位右侧数据对齐
  *            @arg DAC_Align_12b_L: 选择了12位的左边数据排列
  *            @arg DAC_Align_12b_R: 选择了12位的右边数据排列
  * 
  * 参数:  Data: 要加载到选定的数据保持寄存器中的数据。
  * 
  * 返回值: 无
  */
void DAC_SetChannel1Data(uint32_t DAC_Align, uint16_t Data) {
    __IO uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data));

    tmp = (uint32_t)DAC_BASE;
    tmp += DHR12R1_OFFSET + DAC_Align;

    /* 设置 选择DAC通道1 data holding 寄存器 */
    *(__IO uint32_t *) tmp = Data;
}

/**
  * 简介:  为 DAC 通道 2 设置指定的数据保持寄存器值。
  * 
  * 参数:  DAC_Align: 指定DAC通道2的数据排列。
  *          此参数可以是以下值之一:
  *            @arg DAC_Align_8b_R: 选择8位右侧数据对齐
  *            @arg DAC_Align_12b_L: 选择了12位的左边数据排列
  *            @arg DAC_Align_12b_R: 选择了12位的右边数据排列
  * 
  * 参数:  Data: 要加载到选定的数据保持寄存器中的数据。
  * 
  * 返回值: 无
  */
void DAC_SetChannel2Data(uint32_t DAC_Align, uint16_t Data) {
    __IO uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data));

    tmp = (uint32_t)DAC_BASE;
    tmp += DHR12R2_OFFSET + DAC_Align;

    /* 设置 选择DAC通道2 data holding 寄存器 */
    *(__IO uint32_t *)tmp = Data;
}

/**
  * 简介:  为双通道 DAC 设置指定的数据保持寄存器值。
  * 
  * 参数:  DAC_Align: 指定双通道DAC的数据排列。
  *          此参数可以是以下值之一:
  *            @arg DAC_Align_8b_R: 选择8位右侧数据对齐
  *            @arg DAC_Align_12b_L: 选择了12位的左边数据排列
  *            @arg DAC_Align_12b_R: 选择了12位的右边数据排列
  * 
  * 参数:  Data2: 将DAC通道2的数据加载到选定的数据保持寄存器中。
  * 
  * 参数:  Data1: 将DAC通道1的数据加载到选定的数据保持寄存器中。
  * 
  * 注意:   在双模式下，需要一个独特的寄存器访问，以同时写入两个DAC通道。
  * 
  * 返回值: 无
  */
void DAC_SetDualChannelData(uint32_t DAC_Align, uint16_t Data2, uint16_t Data1) {
    uint32_t data = 0, tmp = 0;

    /* 检查参数 */
    assert_param(IS_DAC_ALIGN(DAC_Align));
    assert_param(IS_DAC_DATA(Data1));
    assert_param(IS_DAC_DATA(Data2));

    /* Calculate and set dual DAC data holding寄存器值 */
    if (DAC_Align == DAC_Align_8b_R) {
        data = ((uint32_t)Data2 << 8) | Data1;
    } else {
        data = ((uint32_t)Data2 << 16) | Data1;
    }

    tmp = (uint32_t)DAC_BASE;
    tmp += DHR12RD_OFFSET + DAC_Align;

    /* 设置 dual DAC selected data holding 寄存器 */
    *(__IO uint32_t *)tmp = data;
}

/**
  * 简介:  返回所选 DAC 通道的最后一个数据输出值。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 返回值: 选定的DAC通道数据输出值。
  */
uint16_t DAC_GetDataOutputValue(uint32_t DAC_Channel) {
    __IO uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));

    tmp = (uint32_t) DAC_BASE ;
    tmp += DOR_OFFSET + ((uint32_t)DAC_Channel >> 2);

    /* Returns the DAC channel data output寄存器值 */
    return (uint16_t) (*(__IO uint32_t*) tmp);
}
/**
  * @}
  */

/** @defgroup DAC_Group2 DMA管理功能
 *  简介   DMA管理功能
 *
@verbatim
 ===============================================================================
                       ##### DMA管理功能 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  启用或禁用指定的 DAC 通道 DMA 请求。
  * 
  * 注意:   当启用时，当外部触发(EXTI Line9、TIM2、TIM4、TIM5、TIM6、TIM7或TIM8，
  *         但不是软件触发)发生时产生DMA1。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  NewState: 所选DAC通道DMA请求的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 注意:   DAC通道1被映射到DMA1流5通道7上，该通道必须已经被配置。
  * 
  * 注意:   DAC通道2被映射到DMA1流6通道7上，该通道必须已经被配置。
  * 
  * 返回值: 无
  */
void DAC_DMACmd(uint32_t DAC_Channel, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的DAC通道 DMA request */
        DAC->CR |= (DAC_CR_DMAEN1 << DAC_Channel);
    } else {
        /* 禁用选定的DAC通道 DMA request */
        DAC->CR &= (~(DAC_CR_DMAEN1 << DAC_Channel));
    }
}
/**
  * @}
  */

/** @defgroup DAC_Group3 中断和标记管理函数
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
  * 简介:  启用或禁用指定的 DAC 中断。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  DAC_IT: 指定要启用或禁用的DAC中断源。
  *          这个参数可以是以下值。
  *            @arg DAC_IT_DMAUDR: DMA欠运行中断掩码
  * 
  * 注意:   当第二个外部触发器在收到第一个外部触发器的确认(第一个请求)之前到达时，DMA欠载发生。
  * 
  * 参数:  NewState: 指定 DAC 中断的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void DAC_ITConfig(uint32_t DAC_Channel, uint32_t DAC_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_DAC_IT(DAC_IT));

    if (NewState != DISABLE) {
        /* 启用被选定的 DAC 中断 */
        DAC->CR |=  (DAC_IT << DAC_Channel);
    } else {
        /* 禁用被选中的 DAC 中断 */
        DAC->CR &= (~(uint32_t)(DAC_IT << DAC_Channel));
    }
}

/**
  * 简介:  检查是否设置了指定的 DAC 标志。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  DAC_FLAG: 指定要检查的标志。
  *          该参数只能是以下值:
  *            @arg DAC_FLAG_DMAUDR: DMA欠载标志
  * 
  * 注意:   当第二个外部触发器在收到第一个外部触发器的确认(第一个请求)之前到达时，DMA欠载发生。
  * 
  * 返回值: DAC_FLAG的新状态(SET或RESET)。
  */
FlagStatus DAC_GetFlagStatus(uint32_t DAC_Channel, uint32_t DAC_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_FLAG(DAC_FLAG));

    /* 检查 the status of the specified DAC flag */
    if ((DAC->SR & (DAC_FLAG << DAC_Channel)) != (uint8_t)RESET) {
        /* DAC_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* DAC_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回DAC_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 DAC 通道的挂起标志。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  DAC_FLAG: 指定要清除的标志。
  *          这个参数可以是以下值:
  *            @arg DAC_FLAG_DMAUDR: DMA欠载标志
  * 
  * 注意:   当第二个外部触发器在收到第一个外部触发器的确认(第一个请求)之前到达时，DMA欠载发生。
  * 
  * 返回值: 无
  */
void DAC_ClearFlag(uint32_t DAC_Channel, uint32_t DAC_FLAG) {
    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_FLAG(DAC_FLAG));

    /* 清除 selected DAC flags */
    DAC->SR = (DAC_FLAG << DAC_Channel);
}

/**
  * 简介:  检查是否发生了指定的 DAC 中断。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  DAC_IT: 指定要检查的DAC中断源。
  *          这个参数可以是以下值。
  *            @arg DAC_IT_DMAUDR: DMA欠运行中断掩码
  * 
  * 注意:   当第二个外部触发器在收到第一个外部触发器的确认(第一个请求)之前到达时，DMA欠载发生。
  * 
  * 返回值: DAC_IT的新状态(SET或RESET)。
  */
ITStatus DAC_GetITStatus(uint32_t DAC_Channel, uint32_t DAC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_IT(DAC_IT));

    /* 获取DAC_IT enable bit 状态 */
    enablestatus = (DAC->CR & (DAC_IT << DAC_Channel)) ;

    /* 检查 the status of the specified DAC 中断 */
    if (((DAC->SR & (DAC_IT << DAC_Channel)) != (uint32_t)RESET) && enablestatus) {
        /* DAC_IT 被设置 */
        bitstatus = SET;
    } else {
        /* DAC_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回DAC_IT 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 DAC 通道的中断挂起位。
  * 
  * 参数:  DAC_Channel: 选定的DAC通道。
  *          此参数可以是以下值之一:
  *            @arg DAC_Channel_1: 选择DAC通道1
  *            @arg DAC_Channel_2: 选择DAC通道2
  * 
  * 参数:  DAC_IT: 指定要清除的DAC中断等待位。
  *          这个参数可以是以下值。
  *            @arg DAC_IT_DMAUDR: DMA欠运行中断掩码
  * 
  * 注意:   当第二个外部触发器在收到第一个外部触发器的确认(第一个请求)之前到达时，DMA欠载发生。
  * 
  * 返回值: 无
  */
void DAC_ClearITPendingBit(uint32_t DAC_Channel, uint32_t DAC_IT) {
    /* 检查参数 */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));
    assert_param(IS_DAC_IT(DAC_IT));

    /* 清除 selected DAC interrupt pending 位 */
    DAC->SR = (DAC_IT << DAC_Channel);
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
