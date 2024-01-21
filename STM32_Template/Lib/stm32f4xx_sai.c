/**
  ******************************************************************************
  * 文件:    stm32f4xx_sai.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，用于管理串行音频接口(SAI)的以下功能:
  *           + 初始化和配置
  *           + 数据传输函数
  *           + DMA传输管理
  *           + 中断和标志管理
  *
  @verbatim
 ===============================================================================
                     ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..]

       (#) 使用以下函数启用外围时钟
           RCC_APB2PeriphClockCmd(RCC_APB2Periph_SAI1, ENABLE) for SAI1

       (#) For each SAI Block A/B enable SCK, SD, FS and MCLK GPIO clocks
           using RCC_AHB1PeriphClockCmd() function.

       (#) 外设设备替代函数:
           (++) 使用GPIO_PinAFConfig()函数将引脚连接到所需外设的备用函数(AF)。

           (++) 通过GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF配置复用功能中所需的引脚

           (++) 通过GPIO_PuPd、GPIO_OType和GPIO_Speed成员选择类型、上拉/下拉和输出速度

           (++) 调用 GPIO_Init() 函数
           -@@- 如果使用外部时钟源，则I2S CKIN引脚也应配置为Alternate function Push-pull - pull-up模式。

      (#) SAI时钟可以从不同的时钟源生成:
          PLL I2S、PLL SAI或外部时钟源。
          (++) PLLI2S使用以下函数配置RCC_PLLI2SConfig()，
                                    RCC_PLLI2SCmd(ENABLE)，
                                    RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY)和
                                    RCC_SAIPLLI2SClkDivConfig()或;

          (++) PLLSAI使用以下函数配置RCC_PLLSAIConfig()，
                                      RCC_PLLSAICmd(ENABLE)，
                                      RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY)和
                                      RCC_SAIPLLSAIClkDivConfig()或;

          (++) 通过该函数配置外部时钟源
               RCC_I2S2CLKSource_Ext)，在stm32f4xx_conf.h文件中正确设置定义常量I2S_EXTERNAL_CLOCK_VAL之后。

      (#) 每个SAI块A或B都有自己的时钟发生器，使这两个块完全独立。
          时钟生成器使用RCC_SAIBlockACLKConfig()和RCC_SAIBlockBCLKConfig()函数配置。

      (#) 每个SAI Block A或B可以单独配置:
          (++) 使用 SAI_Init() 函数编程主时钟分压器，音频模式，协议，数据长度，时钟匹配边缘，同步模式，输出驱动器和FIFO阈值。
               在主模式下，使用以下公式编程主时钟分压器(MCKDIV):
               (+++) MCLK_x = SAI_CK_x / (MCKDIV * 2) with MCLK_x = 256 * FS
               (+++) FS = SAI_CK_x / (MCKDIV * 2) * 256
               (+++) MCKDIV = SAI_CK_x / FS * 512

         (++) 使用 SAI_FrameInit() 函数编程帧长度，帧活动长度，FS定义，FS极性，FS偏移量。

         (++) 使用 SAI_SlotInit() 函数编程槽位第1位偏移量，槽大小，槽号，槽活动。

      (#) 如果需要使用中断模式，可以使用函数 SAI_ITConfig() 启用 NVIC 和相应的中断。

      (#) 当使用DMA模式时
          (++) 使用 DMA_Init() 函数配置DMA
          (++) 使用 SAI_DMACmd() 函数激活所需的通道请求

      (#) 使用 SAI_Cmd() 函数启用SAI。

      (#) 当使用 DMA 模式时，使用 DMA_Cmd() 函数启用DMA。

      (#) SAI 有一些特定的功能，这取决于所选的音频协议。
          (++) 当音频块是一个发射器时，使用 SAI_MuteModeCmd() 函数启用静音模式，
               并使用 SAI_MuteValueConfig() 配置静音期间传输的值。

          (++) 当音频块是接收端时，使用SAI_MuteFrameCounterConfig()检测静音模式。
          (++) 当插槽数等于2时，使用SAI_MonoModeConfig()函数启用MONO模式，不需要内存中的任何数据预处理。

          (++) 使用SAI_CompandingModeConfig()启用数据压缩算法(U律和A律)。
          
          (++) 使用SAI_TRIStateConfig()函数在数据线上发送非活动槽时，选择输出中的SD线的行为。
  [..]
   (@)    在主TX模式下: 即使在FIFO中没有数据，启用音频块也立即为外部从站生成位时钟，
                       然而，FS信号的产生受FIFO中数据的存在的制约。

   (@)    在主RX模式下:使能音频块立即为外部从机生成位时钟和FS信号。

   (@)    为了避免不良SAI行为，必须遵守以下条件:
            (+@)  First bit Offset <= (SLOT size - Data size)
            (+@)  Data size <= SLOT size
            (+@)  Number of SLOT x SLOT size = Frame length
            (+@)  The number of slots should be even when bit FSDEF in the SAI_xFRCR is set.

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
#include "stm32f4xx_sai.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup SAI
  * 简介: SAI 驱动模块
  * @{
  */
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || \
defined (STM32F401xx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469_479xx) || \
defined (STM32F413_423xx)

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* *SAI registers Masks */
#define CR1_CLEAR_MASK            ((uint32_t)0xFF07C010)
#define FRCR_CLEAR_MASK           ((uint32_t)0xFFF88000)
#define SLOTR_CLEAR_MASK          ((uint32_t)0x0000F020)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup SAI_Private_Functions
  * @{
  */

/** @defgroup SAI_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
            ##### 初始化和配置函数 #####
 ===============================================================================
  [..]
  本节提供了一组功能，允许初始化SAI音频块模式、音频协议、数据大小、
  音频块之间的同步、主时钟分频器、Fifo阈值、帧配置、
  插槽配置、三态模式、压缩模式和静音模式。
  [..]
  SAI_Init()、SAI_FrameInit()和SAI_SlotInit()。

@endverbatim
  * @{
  */

/**
  * 简介:  将 SAIx 外设寄存器取消初始化为其默认复位值。
  * 参数:  SAIx: 要选择SAIx外设，其中x可以是不同的实例
  *
  * 返回值: 无
  */
void SAI_DeInit(SAI_TypeDef* SAIx) {
    /* 检查参数 */
    assert_param(IS_SAI_PERIPH(SAIx));

    if(SAIx == SAI1) {
        /* 使能SAI1 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SAI1, ENABLE);
        /* 释放SAI1 from 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SAI1, DISABLE);
    } else {
        #if defined(STM32F446xx)

        if(SAIx == SAI2) {
            /* 使能SAI2 复位状态 */
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_SAI2, ENABLE);
            /* 释放SAI2 from 复位状态 */
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_SAI2, DISABLE);
        }

        #endif /* STM32F446xx */
    }
}

/**
  * 简介:  根据 SAI_InitStruct 中指定的参数初始化 SAI Block x 外设。
  *
  * 注意:   SAI时钟是从PLLSAI的特定输出或PLLI2S的特定输出产生的，
			或者是从绕过PLL I2S的替代功能产生的。
  *
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_InitStruct: 指向 SAI_InitTypeDef 结构的指针，该结构包含指定 SAI 块的配置信息外设.
  * 返回值: 无
  */
void SAI_Init(SAI_Block_TypeDef* SAI_Block_x, SAI_InitTypeDef* SAI_InitStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

    /* 检查这个 SAI Block 参数 */
    assert_param(IS_SAI_BLOCK_MODE(SAI_InitStruct->SAI_AudioMode));
    assert_param(IS_SAI_BLOCK_PROTOCOL(SAI_InitStruct->SAI_Protocol));
    assert_param(IS_SAI_BLOCK_DATASIZE(SAI_InitStruct->SAI_DataSize));
    assert_param(IS_SAI_BLOCK_FIRST_BIT(SAI_InitStruct->SAI_FirstBit));
    assert_param(IS_SAI_BLOCK_CLOCK_STROBING(SAI_InitStruct->SAI_ClockStrobing));
    assert_param(IS_SAI_BLOCK_SYNCHRO(SAI_InitStruct->SAI_Synchro));
    assert_param(IS_SAI_BLOCK_SYNCEXT(SAI_InitStruct->SAI_SynchroExt));
    assert_param(IS_SAI_BLOCK_OUTPUT_DRIVE(SAI_InitStruct->SAI_OUTDRIV));
    assert_param(IS_SAI_BLOCK_NODIVIDER(SAI_InitStruct->SAI_NoDivider));
    assert_param(IS_SAI_BLOCK_MASTER_DIVIDER(SAI_InitStruct->SAI_MasterDivider));
    assert_param(IS_SAI_BLOCK_FIFO_THRESHOLD(SAI_InitStruct->SAI_FIFOThreshold));

    /* SAI Block_x CR1 配置*/
    /* 获取SAI Block_x CR1 值 */
    tmpreg = SAI_Block_x->CR1;
    /* 清除 MODE, PRTCFG, DS, LSBFIRST, CKSTR, SYNCEN, OUTDRIV, NODIV, and MCKDIV 位 */
    tmpreg &= CR1_CLEAR_MASK;
    /* 配置 SAI_Block_x: Audio mode, Protocol, Data Size, first transmitted bit, Clock strobing
       edge, Synchronization mode, Output drive, Master Divider and FIFO level */
    /* 设置 MODE 比特位 根据 SAI_AudioMode 值       */
    /* 设置 PRTCFG 比特位 根据 SAI_Protocol 值      */
    /* 设置 DS 比特位 根据 SAI_DataSize 值          */
    /* 设置 LSBFIRST 比特位根据 SAI_FirstBit 值     */
    /* 设置 CKSTR 比特位根据 SAI_ClockStrobing 值   */
    /* 设置 SYNCEN 比特位根据 SAI_Synchro 值        */
    /* 设置 OUTDRIV 比特位根据 SAI_OUTDRIV 值       */
    /* 设置 NODIV 比特位根据 SAI_NoDivider 值       */
    /* 设置 MCKDIV 比特位 根据 SAI_MasterDivider 值 */
    tmpreg |= (uint32_t)(SAI_InitStruct->SAI_AudioMode     | SAI_InitStruct->SAI_Protocol  |
                         SAI_InitStruct->SAI_DataSize      | SAI_InitStruct->SAI_FirstBit  |
                         SAI_InitStruct->SAI_ClockStrobing | SAI_InitStruct->SAI_Synchro   |
                         SAI_InitStruct->SAI_OUTDRIV       | SAI_InitStruct->SAI_NoDivider |
                         SAI_InitStruct->SAI_SynchroExt    | (uint32_t)((SAI_InitStruct->SAI_MasterDivider) << 20));
    /* 写入SAI_Block_x CR1 */
    SAI_Block_x->CR1 = tmpreg;

    /* SAI Block_x CR2 配置*/
    /* 获取SAIBlock_x CR2 值 */
    tmpreg = SAI_Block_x->CR2;
    /* 清除 FTH 位 */
    tmpreg &= ~(SAI_xCR2_FTH);
    /* 配置 FIFO Level */
    /* Set FTH bits 根据 SAI_FIFOThreshold 值 */
    tmpreg |= (uint32_t)(SAI_InitStruct->SAI_FIFOThreshold);
    /* 写入SAI_Block_x CR2 */
    SAI_Block_x->CR2 = tmpreg;
}

/**
  * 简介:  根据 SAI_FrameInitStruct 中指定的参数初始化 SAI Block Audio 帧。
  *
  * 注意:   如果选择了AC’97或SPDIF音频协议，则此功能没有任何意义。
  *
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_FrameInitStruct: 指向SAI_FrameInitTypeDef结构的指针，
		   该结构包含指定SAI块的音频帧配置

  * 返回值: 无
  */
void SAI_FrameInit(SAI_Block_TypeDef* SAI_Block_x, SAI_FrameInitTypeDef* SAI_FrameInitStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

    /* 检查这个 SAI Block 参数 */
    assert_param(IS_SAI_BLOCK_FRAME_LENGTH(SAI_FrameInitStruct->SAI_FrameLength));
    assert_param(IS_SAI_BLOCK_ACTIVE_FRAME(SAI_FrameInitStruct->SAI_ActiveFrameLength));
    assert_param(IS_SAI_BLOCK_FS_DEFINITION(SAI_FrameInitStruct->SAI_FSDefinition));
    assert_param(IS_SAI_BLOCK_FS_POLARITY(SAI_FrameInitStruct->SAI_FSPolarity));
    assert_param(IS_SAI_BLOCK_FS_OFFSET(SAI_FrameInitStruct->SAI_FSOffset));

    /* SAI Block_x FRCR 配置*/
    /* 获取SAI Block_x FRCR 值 */
    tmpreg = SAI_Block_x->FRCR;
    /* 清除 FRL, FSALL, FSDEF, FSPOL, FSOFF 位 */
    tmpreg &= FRCR_CLEAR_MASK;
    /* 配置 SAI_Block_x帧：帧长度、活动帧长度、帧同步定义、帧同步极性和帧同步极度 */
    /* 设置 FRL 比特位 根据 SAI_FrameLength 值*/
    /* 设置 FSALL 比特位 根据 SAI_ActiveFrameLength 值 */
    /* 设置 FSDEF 比特位 根据 SAI_FSDefinition 值*/
    /* 设置 FSPOL 比特位 根据 SAI_FSPolarity 值*/
    /* 设置 FSOFF 比特位 根据 SAI_FSOffset 值 */
    tmpreg |= (uint32_t)((uint32_t)(SAI_FrameInitStruct->SAI_FrameLength - 1)  |
                         SAI_FrameInitStruct->SAI_FSOffset     |
                         SAI_FrameInitStruct->SAI_FSDefinition |
                         SAI_FrameInitStruct->SAI_FSPolarity   |
                         (uint32_t)((SAI_FrameInitStruct->SAI_ActiveFrameLength - 1) << 8));

    /* 写入SAI_Block_x FRCR */
    SAI_Block_x->FRCR = tmpreg;
}

/**
  * 简介:  根据 SAI_SlotInitStruct 中指定的参数初始化 SAI Block 音频 Slot。
  *
  * 注意:   如果选择了AC’97或SPDIF音频协议，则此函数没有任何意义。
  *
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_SlotInitStruct: 指向SAI_SlotInitTypeDef结构的指针，
		   该结构包含指定SAI块的音频插槽配置
  * 返回值: 无
  */
void SAI_SlotInit(SAI_Block_TypeDef* SAI_Block_x, SAI_SlotInitTypeDef* SAI_SlotInitStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

    /* 检查 the SAI Block Slot parameters */
    assert_param(IS_SAI_BLOCK_FIRSTBIT_OFFSET(SAI_SlotInitStruct->SAI_FirstBitOffset));
    assert_param(IS_SAI_BLOCK_SLOT_SIZE(SAI_SlotInitStruct->SAI_SlotSize));
    assert_param(IS_SAI_BLOCK_SLOT_NUMBER(SAI_SlotInitStruct->SAI_SlotNumber));
    assert_param(IS_SAI_SLOT_ACTIVE(SAI_SlotInitStruct->SAI_SlotActive));

    /* SAI Block_x SLOTR 配置*/
    /* 获取SAI Block_x SLOTR 值 */
    tmpreg = SAI_Block_x->SLOTR;
    /* 清除 FBOFF, SLOTSZ, NBSLOT, SLOTEN 位 */
    tmpreg &= SLOTR_CLEAR_MASK;
    /* Configure SAI_Block_x Slot: First bit offset, Slot size, Number of Slot in
       audio frame and slots activated in audio frame */
    /* 设置 FBOFF bits 根据 SAI_FirstBitOffset 值  */
    /* 设置 SLOTSZ bits 根据 SAI_SlotSize 值       */
    /* 设置 NBSLOT bits 根据 SAI_SlotNumber 值     */
    /* 设置 SLOTEN bits 根据 SAI_SlotActive 值     */
    tmpreg |= (uint32_t)(SAI_SlotInitStruct->SAI_FirstBitOffset |
                         SAI_SlotInitStruct->SAI_SlotSize       |
                         SAI_SlotInitStruct->SAI_SlotActive     |
                         (uint32_t)((SAI_SlotInitStruct->SAI_SlotNumber - 1) <<  8));

    /* 写入SAI_Block_x SLOTR */
    SAI_Block_x->SLOTR = tmpreg;
}

/**
  * 简介:  用默认值填充每个 SAI_InitStruct 成员。
  * 参数:  SAI_InitStruct: 指向将被初始化的SAI_InitTypeDef结构的指针。
  * 返回值: 无
  */
void SAI_StructInit(SAI_InitTypeDef* SAI_InitStruct) {
    /* 重置SAI初始化结构参数值 */
    /* 初始化 SAI_AudioMode 成员 */
    SAI_InitStruct->SAI_AudioMode = SAI_Mode_MasterTx;
    /* 初始化 SAI_Protocol 成员 */
    SAI_InitStruct->SAI_Protocol = SAI_Free_Protocol;
    /* 初始化 SAI_DataSize 成员 */
    SAI_InitStruct->SAI_DataSize = SAI_DataSize_8b;
    /* 初始化 SAI_FirstBit 成员 */
    SAI_InitStruct->SAI_FirstBit = SAI_FirstBit_MSB;
    /* 初始化 SAI_ClockStrobing 成员 */
    SAI_InitStruct->SAI_ClockStrobing = SAI_ClockStrobing_FallingEdge;
    /* 初始化 SAI_Synchro 成员 */
    SAI_InitStruct->SAI_Synchro = SAI_Asynchronous;
    /* 初始化 SAI_SynchroExt 成员 */
    SAI_InitStruct->SAI_SynchroExt = SAI_SyncExt_Disable;
    /* 初始化 SAI_OUTDRIV 成员 */
    SAI_InitStruct->SAI_OUTDRIV = SAI_OutputDrive_Disabled;
    /* 初始化 SAI_NoDivider 成员 */
    SAI_InitStruct->SAI_NoDivider = SAI_MasterDivider_Enabled;
    /* 初始化 SAI_MasterDivider 成员 */
    SAI_InitStruct->SAI_MasterDivider = 0;
    /* 初始化 SAI_FIFOThreshold 成员 */
    SAI_InitStruct->SAI_FIFOThreshold = SAI_Threshold_FIFOEmpty;
}

/**
  * 简介:  用默认值填充每个 SAI_FrameInitStruct 成员。
  * 参数:  SAI_FrameInitStruct: 指向将被初始化的SAI_FrameInitTypeDef结构的指针。
  * 返回值: 无
  */
void SAI_FrameStructInit(SAI_FrameInitTypeDef* SAI_FrameInitStruct) {
    /* 重置SAI帧初始化结构参数值 */
    /* 初始化 SAI_FrameLength 成员 */
    SAI_FrameInitStruct->SAI_FrameLength = 8;
    /* 初始化 SAI_ActiveFrameLength 成员 */
    SAI_FrameInitStruct->SAI_ActiveFrameLength = 1;
    /* 初始化 SAI_FSDefinition 成员 */
    SAI_FrameInitStruct->SAI_FSDefinition = SAI_FS_StartFrame;
    /* 初始化 SAI_FSPolarity 成员 */
    SAI_FrameInitStruct->SAI_FSPolarity = SAI_FS_ActiveLow;
    /* 初始化 SAI_FSOffset 成员 */
    SAI_FrameInitStruct->SAI_FSOffset = SAI_FS_FirstBit;
}

/**
  * 简介:  用默认值填充每个 SAI_SlotInitStruct 成员。
  * 参数:  SAI_SlotInitStruct: 指向将被初始化的SAI_SlotInitTypeDef结构的指针。
  * 返回值: 无
  */
void SAI_SlotStructInit(SAI_SlotInitTypeDef* SAI_SlotInitStruct) {
    /* 重置SAI插槽初始化结构参数值 */
    /* 初始化 SAI_FirstBitOffset 成员 */
    SAI_SlotInitStruct->SAI_FirstBitOffset = 0;
    /* 初始化 SAI_SlotSize 成员 */
    SAI_SlotInitStruct->SAI_SlotSize = SAI_SlotSize_DataSize;
    /* 初始化 SAI_SlotNumber 成员 */
    SAI_SlotInitStruct->SAI_SlotNumber = 1;
    /* 初始化 SAI_SlotActive 成员 */
    SAI_SlotInitStruct->SAI_SlotActive = SAI_Slot_NotActive;

}

/**
  * 简介:  启用或禁用指定的 SAI Block 外设。
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设设备。
  * 参数:  NewState: SAI_Block_x外设设备的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SAI_Cmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用所选SAI外设设备 */
        SAI_Block_x->CR1 |= SAI_xCR1_SAIEN;
    } else {
        /* 禁用所选SAI外设设备 */
        SAI_Block_x->CR1 &= ~(SAI_xCR1_SAIEN);
    }
}

/**
  * 简介:  为选定的 SAI 模块配置单声道模式。
  *
  * 注意:  只有当插槽数量等于2时，此函数才有意义。
  *
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_MonoMode: 指定SAI block mono mode.
  *          此参数可以是以下值之一:
  *            @arg SAI_MonoMode : Set mono audio mode
  *            @arg SAI_StreoMode : Set streo audio mode
  * 返回值: 无
  */
void SAI_MonoModeConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_Mono_StreoMode) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_MONO_STREO_MODE(SAI_MonoMode));
    /* 清除 MONO 位 */
    SAI_Block_x->CR1 &= ~(SAI_xCR1_MONO);
    /* Set new Mono Mode 值 */
    SAI_Block_x->CR1 |= SAI_MonoMode;
}

/**
  * 简介:  为选定的 SAI 块配置数据线上的 TRIState 管理。
  *
  * 注意:  只有在变送器中配置SAI块时，此功能才有意义
  *
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_TRIState: 指定SAI block TRIState management.
  *          此参数可以是以下值之一:
  *            @arg SAI_Output_NotReleased :SD 输出线仍然由 SAI 驱动。
  *            @arg SAI_Output_Released : SD 输出线释放（HI-Z）
  * 返回值: 无
  */
void SAI_TRIStateConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_TRIState) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_TRISTATE_MANAGEMENT(SAI_TRIState));
    /* 清除 MONO 位 */
    SAI_Block_x->CR1 &= ~(SAI_xCR1_MONO);
    /* Set new Mono Mode 值 */
    SAI_Block_x->CR1 |= SAI_MonoMode;

}

/**
  * 简介:  为选定的 SAI 模块配置压扩模式。
  *
  * 注意:  数据扩展或数据压缩由所选SAI块（发射机或接收机）的状态决定。

  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_CompandingMode: 指定SAI block companding mode.
  *          此参数可以是以下值之一:
  *            @arg SAI_NoCompanding : 无压扩算法集
  *            @arg SAI_ULaw_1CPL_Companding : Set U law (算法1 的补码表示)
  *            @arg SAI_ALaw_1CPL_Companding : Set A law (算法1 的补码表示)
  *            @arg SAI_ULaw_2CPL_Companding : Set U law (算法2 的补码表示)
  *            @arg SAI_ALaw_2CPL_Companding : Set A law (算法2 的补码表示)
  * 
  * 返回值: 无
  */
void SAI_CompandingModeConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_CompandingMode) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_COMPANDING_MODE(SAI_CompandingMode));
    /* 清除 Companding Mode 位 */
    SAI_Block_x->CR2 &= ~(SAI_xCR2_COMP);
    /* 设置新的压缩模式值 */
    SAI_Block_x->CR2 |= SAI_CompandingMode;
}

/**
  * 简介:  启用或禁用选定 SAI 模块的静音模式。
  *
  * 注意:   只有当音频块是发射器时，此功能才有意义
  * 注意:   静音模式适用于所有有效插槽的整个帧
			当设置在音频帧的某个位置时，它在音频帧结束时变为活动。
  *         静音模式退出发生在设置了位Mute的帧的末尾。
  *
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  NewState: 新状态-> SAIx block.
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SAI_MuteModeCmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 SAI block 静音模式 */
        SAI_Block_x->CR2 |= SAI_xCR2_MUTE;
    } else {
        /* 选择的SAI SS输出 */
        SAI_Block_x->CR2 &= ~(SAI_xCR2_MUTE);
    }
}

/**
  * 简介:  为选定的 SAI 模块配置静音值。
  *
  * 注意:   只有当音频块是发射器时，此功能才有意义
  * 注意:   在静音模式期间发送的配置最后值只有在时隙数量小于或等于2
			并且设置了mute比特时才有意义。
  *
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_MuteValue: 指定SAI块静音值。
  *          此参数可以是以下值之一:
  *            @arg SAI_ZeroValue : 在静音模式期间发送位值0
  *            @arg SAI_LastSentValue : 静音模式下发送最后一个值
  * 返回值: 无
  */
void SAI_MuteValueConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_MuteValue) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_MUTE_VALUE(SAI_MuteValue));

    /* 清除 Mute value 位 */
    SAI_Block_x->CR2 &= ~(SAI_xCR2_MUTEVAL);
    /* 设置 new Mute 值 */
    SAI_Block_x->CR2 |= SAI_MuteValue;
}

/**
  * 简介:  启用或禁用选定 SAI 模块的静音模式。
  *
  * 注意:  只有当音频块为Receiver时，此函数才有意义
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_MuteCounter: 指定SAI block mute value.
  *         此参数可以是 0 到 6 3之间的数字。

  * 返回值: 无
  */
void SAI_MuteFrameCounterConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_MuteCounter) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_MUTE_COUNTER(SAI_MuteCounter));

    /* 清除 Mute value 位 */
    SAI_Block_x->CR2 &= ~(SAI_xCR2_MUTECNT);
    /* Set new Mute 值 */
    SAI_Block_x->CR2 |= (SAI_MuteCounter << 7);
}
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
defined(STM32F469_479xx) || defined(STM32F413_423xx) || defined(STM32F446xx)
/**
  * 简介:  配置 SAI Block 同步模式
  * 参数:  SAI_InitStruct: 指向SAI_InitTypeDef结构的指针，该结构包含指定SAI块的配置信息外设.
  * 参数:  SAIx: 选择SAIx外设设备，其中x可以是不同的实例
  * 返回值: 无
  */
void SAI_BlockSynchroConfig(SAI_InitTypeDef* SAI_InitStruct, SAI_TypeDef* SAIx) {
    uint32_t tmpregisterGCR = 0U;

    #if defined(STM32F446xx)

    /* 必须在禁用音频块(A和B)的情况下进行此设置         */
    switch(SAI_InitStruct->SAI_SynchroExt) {
        case SAI_SyncExt_Disable :
            tmpregisterGCR = 0U;
            break;

        case SAI_SyncExt_OutBlockA_Enable :
            tmpregisterGCR = SAI_GCR_SYNCOUT_0;
            break;

        case SAI_SyncExt_OutBlockB_Enable :
            tmpregisterGCR = SAI_GCR_SYNCOUT_1;
            break;

        default:
            break;
    }

    if(((SAI_InitStruct->SAI_Synchro) == SAI_Synchronous_Ext) && (SAIx == SAI1)) {
        tmpregisterGCR |= SAI_GCR_SYNCIN_0;
    }

    if(SAIx == SAI1) {
        SAI1->GCR = tmpregisterGCR;
    } else {
        SAI2->GCR = tmpregisterGCR;
    }

    #endif /* STM32F446xx */
    #if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
    defined(STM32F469_479xx) || defined(STM32F413_423xx)

    /* 必须在禁用音频块（A和B）的情况下进行此设置         */
    switch(SAI_InitStruct->SAI_SynchroExt) {
        case SAI_SyncExt_Disable :
            tmpregisterGCR = 0U;
            break;

        case SAI_SyncExt_OutBlockA_Enable :
            tmpregisterGCR = SAI_GCR_SYNCOUT_0;
            break;

        case SAI_SyncExt_OutBlockB_Enable :
            tmpregisterGCR = SAI_GCR_SYNCOUT_1;
            break;

        default:
            break;
    }

    SAI1->GCR = tmpregisterGCR;
    #endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469_479xx || STM32F413_423xx */
}
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469_479xx || STM32F413_423xx || STM32F446xx */

/**
  * 简介:  重新初始化 FIFO 指针
  *
  * 注意:   FIFO 指针可以随时重新初始化。如果 FIFO 中的数据不是空的，则会丢失。
  *
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  NewState: 新状态-> 选择 SAI TI 通信模式。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void SAI_FlushFIFO(SAI_Block_TypeDef* SAI_Block_x) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

    /* FIFO flush */
    SAI_Block_x->CR2 |= SAI_xCR2_FFLUSH;
}

/**
  * @}
  */

/** @defgroup SAI_Group2 数据传输函数
 *  简介   数据传输函数
 *
@verbatim
 ===============================================================================
                       ##### 数据传输函数 #####
 ===============================================================================
  [..]
  本节提供了一组允许管理SAI数据传输的功能。
  [..]
  在接收过程中，数据被接收，然后被存储到内部FIFO中，同时
  在传输中，数据在传输之前首先存储在内部FIFO中。
  [..]
  SAI_xDR寄存器的读取访问可以使用SAI_ReceiveData()函数完成，
  并返回Rx缓冲值。而对SAI_DR的写入访问可以使用SAI_SendData()
  函数来完成，并将写入的数据存储到Tx缓冲器中。

@endverbatim
  * @{
  */

/**
  * 简介:  返回 SAI 模块 x 外设最近接收到的数据。
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  *
  * 返回值: The value of 接收的数据。
  */
uint32_t SAI_ReceiveData(SAI_Block_TypeDef* SAI_Block_x) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

    /* 返回data in the DR 寄存器 */
    return SAI_Block_x->DR;
}

/**
  * 简介:  通过 SAI 模块 x 外设传输数据。
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  *
  * 参数:  Data: 要传输的数据。
  * 返回值: 无
  */
void SAI_SendData(SAI_Block_TypeDef* SAI_Block_x, uint32_t Data) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

    /* 在DR寄存器中写入要发送的数据 */
    SAI_Block_x->DR = Data;
}

/**
  * @}
  */

/** @defgroup SAI_Group3 DMA传输管理功能 
 *  简介   DMA传输管理功能 
  *
@verbatim
 ===============================================================================
                  ##### DMA传输管理功能 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  启用或禁用 SAI Block x DMA 接口。
  * 
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 
  * 参数:  NewState: 新状态-> 选择SAI块DMA传输请求。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void SAI_DMACmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选择SAI块静音模式 */
        SAI_Block_x->CR1 |= SAI_xCR1_DMAEN;
    } else {
        /* 选择的SAI SS输出 */
        SAI_Block_x->CR1 &= ~(SAI_xCR1_DMAEN);
    }
}

/**
  * @}
  */

/** @defgroup SAI_Group4 中断和标记管理函数
 *  简介   中断和标记管理函数
  *
@verbatim
 ===============================================================================
            ##### 中断和标记管理函数 #####
 ===============================================================================
  [..]
  本节提供了一组功能，允许配置SAI中断源并检查或清除标志或挂起位状态。
  用户应确定在其应用程序中将使用哪种模式来管理通信:轮询模式、中断模式或DMA模式。

  *** 轮询模式 ***
  ====================
  [..]
  在轮询模式下，SAI通信可以由7个标志管理:
     (#) SAI_FLAG_FREQ :    以指示是否存在要写入或要读取的FIFO请求。
     (#) SAI_FLAG_MUTEDET : 以指示是否检测到MUTE帧
     (#) SAI_FLAG_OVRUDR :  指示是否发生溢出或不足错误
     (#) SAI_FLAG_AFSDET :  以指示是否存在比预期更早的音频帧同步(FS)的检测
     (#) SAI_FLAG_LFSDET :  以指示是否检测到晚于预期的音频帧同步(FS)
     (#) SAI_FLAG_CNRDY :   以指示编解码器在接收AC97音频帧的TAG 0(slot0)期间是否未准备好通信
     (#) SAI_FLAG_WCKCFG:   以指示主模式中的错误时钟配置是否发生错误。
  [..]
  在此模式下，建议使用以下函数:
     (+) FlagStatus SAI_GetFlagStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG);
     (+) void SAI_ClearFlag(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG);

  *** 中断模式 ***
  ======================
  [..]
  在中断模式, SAI通信可以由7个中断源和7个未决位管理:
  (+) 挂起的位:
     (##) SAI_IT_FREQ : 以指示是否存在要写入或要读取的FIFO请求。
     (##) SAI_IT_MUTEDET : 以指示是否检测到MUTE帧。
     (##) SAI_IT_OVRUDR : 以指示是否发生溢出或不足运行错误。
     (##) SAI_IT_AFSDET : 以指示是否存在比预期更早的音频帧同步(FS)的检测。
     (##) SAI_IT_LFSDET : 以指示是否存在晚于预期的音频帧同步(FS)的检测。
     (##) SAI_IT_CNRDY : 以指示编解码器在接收AC97音频帧的TAG 0(slot0)期间是否未准备好通信。
     (##) SAI_IT_WCKCFG: 以指示主模式中的错误时钟配置是否发生错误。

  (+) 中断源:
     (##) SAI_IT_FREQ : 指定FIFO请求的中断源。
     (##) SAI_IT_MUTEDET : 指定检测到的MUTE帧的中断源。
     (##) SAI_IT_OVRUDR : 指定溢出或欠载错误的中断源。
     (##) SAI_IT_AFSDET : 指定预期帧同步检测中断的中断源。
     (##) SAI_IT_LFSDET : 指定延迟帧同步检测中断的中断源。
     (##) SAI_IT_CNRDY : 指定编解码器未就绪中断的中断源
     (##) SAI_IT_WCKCFG: 指定错误时钟配置中断的中断源。
  [..]
  在此模式下，建议使用以下函数:
     (+) void SAI_ITConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT, FunctionalState NewState);
     (+) ITStatus SAI_GetITStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT);
     (+) void SAI_ClearITPendingBit(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT);

  *** DMA模式 ***
  ================
  [..]
  在DMA模式, 每个SAI音频块具有独立的DMA接口，以便读取或写入SAI_xDR寄存器(以命中内部FIFO)。
  按照基本DMA请求/确认协议，音频块有一个DMA通道。
  [..]
  在此模式下，建议使用以下函数:
    (+) void SAI_DMACmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState);
  [..]
  本节还提供了允许
   (+) 检查SAI块启用状态
   (+) 检查FIFO状态

  *** SAI Block 启用状态 ***
  ===============================
  [..]
  禁用SAI块后，建议检查(或等待)SAI块被有效禁用。如果在音频
  帧传输进行时禁用块，则当前帧将被传输，并且该块将仅在音频帧结束时被有效禁用。
  要监控此状态，可以使用以下函数:
    (+) FunctionalState SAI_GetCmdStatus(SAI_Block_TypeDef* SAI_Block_x);

  *** SAI块FIFO状态 ***
  =============================
  [..]
  当传输正在进行时，可以使用以下功能监控FIFO状态:
    (+) uint32_t SAI_GetFIFOStatus(SAI_Block_TypeDef* SAI_Block_x);

@endverbatim
  * @{
  */

/**
  * 简介:  启用或禁用指定的 SAI 块中断。
  * 
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 
  * 参数:  SAI_IT: 指定要启用或禁用的SAI中断源。
  *          此参数可以是以下值之一:
  *            @arg SAI_IT_FREQ: FIFO请求中断掩码
  *            @arg SAI_IT_MUTEDET: MUTE检测中断掩码
  *            @arg SAI_IT_OVRUDR: 超限/欠载中断掩码
  *            @arg SAI_IT_AFSDET: 预期帧同步检测中断掩码
  *            @arg SAI_IT_LFSDET: 后期帧同步检测中断掩码
  *            @arg SAI_IT_CNRDY: 编解码器未就绪中断掩码
  *            @arg SAI_IT_WCKCFG: 错误的时钟配置中断掩码
  * 
  * 参数:  NewState: 新状态-> specified SAI 中断.
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void SAI_ITConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SAI_BLOCK_CONFIG_IT(SAI_IT));

    if (NewState != DISABLE) {
        /* 启用被选定的 SAI Block 中断 */
        SAI_Block_x->IMR |= SAI_IT;
    } else {
        /* 禁用被选中的 SAI Block 中断 */
        SAI_Block_x->IMR &= ~(SAI_IT);
    }
}

/**
  * 简介:  检查是否设置了指定的 SAI 块 x 标志。
  * 
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 
  * 参数:  SAI_FLAG: 指定要检查的SAI块标志。
  *          此参数可以是以下值之一:
  *            @arg SAI_FLAG_FREQ: FIFO 请求标志.
  *            @arg SAI_FLAG_MUTEDET: MUTE detection flag.
  *            @arg SAI_FLAG_OVRUDR: overrun/underrun flag.
  *            @arg SAI_FLAG_WCKCFG: wrong clock configuration flag.
  *            @arg SAI_FLAG_CNRDY: codec not ready flag.
  *            @arg SAI_FLAG_AFSDET: anticipated frame synchronization detection flag.
  *            @arg SAI_FLAG_LFSDET: late frame synchronization detection flag.
  * 
  * 返回值: 新状态-> SAI_FLAG (SET or RESET).
  */
FlagStatus SAI_GetFlagStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG) {
    FlagStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_GET_FLAG(SAI_FLAG));

    /* 检查 the status of the specified SAI flag */
    if ((SAI_Block_x->SR & SAI_FLAG) != (uint32_t)RESET) {
        /* SAI_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* SAI_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回SAI_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除指定的 SAI Block x 标志。
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_FLAG: 指定要检查的SAI块标志。
  *          此参数可以是以下值之一:
  *            @arg SAI_FLAG_MUTEDET: MUTE detection flag.
  *            @arg SAI_FLAG_OVRUDR: overrun/underrun flag.
  *            @arg SAI_FLAG_WCKCFG: wrong clock configuration flag.
  *            @arg SAI_FLAG_CNRDY: codec not ready flag.
  *            @arg SAI_FLAG_AFSDET: anticipated frame synchronization detection flag.
  *            @arg SAI_FLAG_LFSDET: late frame synchronization detection flag.
  *
  * 注意:    FREQ (FIFO Request) flag is cleared :
  *          - When the audio block is transmitter and the FIFO is full or the FIFO
  *            has one data (one buffer mode) depending the bit FTH in the
  *            SAI_xCR2 register.
  *          - 当音频块为接收器且 FIFO 不为空时
  *
  * 返回值: 无
  */
void SAI_ClearFlag(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_CLEAR_FLAG(SAI_FLAG));

    /* 清除 selected SAI Block flag */
    SAI_Block_x->CLRFR |= SAI_FLAG;
}

/**
  * 简介:  检查指定的 SAI Block x 中断是否发生。
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_IT: 指定要启用或禁用的SAI中断源。
  *          此参数可以是以下值之一:
  *            @arg SAI_IT_FREQ: FIFO Request interrupt
  *            @arg SAI_IT_MUTEDET: MUTE detection interrupt
  *            @arg SAI_IT_OVRUDR: overrun/underrun interrupt
  *            @arg SAI_IT_AFSDET: anticipated frame synchronization detection interrupt
  *            @arg SAI_IT_LFSDET: late frame synchronization detection interrupt
  *            @arg SAI_IT_CNRDY: codec not 就绪中断
  *            @arg SAI_IT_WCKCFG: wrong clock configuration interrupt
  *
  * 返回值: 新状态-> SAI_IT (SET or RESET).
  */
ITStatus SAI_GetITStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT) {
    ITStatus bitstatus = RESET;
    uint32_t  enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_CONFIG_IT(SAI_IT));

    /* 获取SAI_IT enable bit 状态 */
    enablestatus = (SAI_Block_x->IMR & SAI_IT) ;

    /* 检查 the status of the specified SAI 中断 */
    if (((SAI_Block_x->SR & SAI_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET)) {
        /* SAI_IT 被设置 */
        bitstatus = SET;
    } else {
        /* SAI_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回SAI_IT 状态 */
    return bitstatus;
}

/**
  * 简介:  清除 SAI Block x 中断挂起位。
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  * 参数:  SAI_IT: 指定要清除的SAI块中断挂起位。
  *          此参数可以是以下值之一:
  *            @arg SAI_IT_MUTEDET: 静音检测中断。
  *            @arg SAI_IT_OVRUDR: 超限/欠载运行中断。
  *            @arg SAI_IT_WCKCFG: 错误的时钟配置中断。
  *            @arg SAI_IT_CNRDY: codec not 就绪中断.
  *            @arg SAI_IT_AFSDET: 预期的帧同步检测中断。
  *            @arg SAI_IT_LFSDET: 后期帧同步检测中断。
  *
  * 注意:    FREQ (FIFO Request) flag is cleared :
  *          - When the audio block is transmitter and the FIFO is full or the FIFO
  *            has one data (one buffer mode) depending the bit FTH in the
  *            SAI_xCR2 register.
  *          - 当音频块为接收器且 FIFO 不为空时
  *
  * 返回值: 无
  */
void SAI_ClearITPendingBit(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT) {
    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));
    assert_param(IS_SAI_BLOCK_CONFIG_IT(SAI_IT));

    /* 清除 所选SAI块x中断挂起位 */
    SAI_Block_x->CLRFR |= SAI_IT;
}

/**
  * 简介:  返回指定 SAI 块 x 的 EN 位的状态。
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  *
  * 注意:    禁用SAI块后，建议检查(或等待)SAI块被有效禁用。
			 如果在音频帧传输过程中禁用了块，则当前帧将被传输，
			 并且该块将仅在音频帧结束时被有效禁用。
  *
  * 返回值: DMAy Streamx的当前状态(ENABLE或DISABLE)。
  */
FunctionalState SAI_GetCmdStatus(SAI_Block_TypeDef* SAI_Block_x) {
    FunctionalState state = DISABLE;

    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

    if ((SAI_Block_x->CR1 & (uint32_t)SAI_xCR1_SAIEN) != 0) {
        /* 已设置所选SAI Block x EN位(正在进行音频帧传输) */
        state = ENABLE;
    } else {
        /* 所选SAI块x EN位被清除(SAI块被禁用，所有传输都完成) */
        state = DISABLE;
    }

    return state;
}

/**
  * 简介:  返回当前 SAI 块 x FIFO 填充级别。
  * 参数:  SAI_Block_x: 其中x可以是A或B，以选择SAI块外设。
  *
  * 返回值: FIFO填充状态。
  *           - SAI_FIFOStatus_Empty: 当FIFO为空时
  *           - SAI_FIFOStatus_Less1QuarterFull: when FIFO is less than 1 quarter-full
  *                                               and not empty.
  *           - SAI_FIFOStatus_1QuarterFull: if more than 1 quarter-full.
  *           - SAI_FIFOStatus_HalfFull: if more than 1 half-full.
  *           - SAI_FIFOStatus_3QuartersFull: if more than 3 quarters-full.
  *           - SAI_FIFOStatus_Full: when FIFO is full
  */
uint32_t SAI_GetFIFOStatus(SAI_Block_TypeDef* SAI_Block_x) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_SAI_BLOCK_PERIPH(SAI_Block_x));

    /* 获取FIFO level 位 */
    tmpreg = (uint32_t)((SAI_Block_x->SR & SAI_xSR_FLVL));

    return tmpreg;
}


/**
  * @}
  */

/**
  * @}
  */
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE || STM32F446xx || STM32F469_479xx */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
