/**
  ******************************************************************************
  * 文件:    stm32f4xx_dma.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能来管理直接内存访问控制器 (DMA) 的以下功能:
  *           + 初始化和配置
  *           + 数据计数器
  *           + 双缓冲模式配置和命令
  *           + 中断和标志管理
  *
  @verbatim
 ===============================================================================
                       ##### 如何使用此驱动程序 #####
 ===============================================================================
    [..]
      (#) 使用 DMA1 的 RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_DMA1, ENABLE) 函数
		  或 DMA2 的 RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_DMA2, ENABLE)
		  函数启用 DMA 控制器时钟。

      (#) 启用和配置外设以连接到 DMA 流(内部 SRAM / FLASH 存储器除外:无需初始化)。

      (#) 对于给定的 Stream，通过以下参数编程所需的配置:
          源和目标地址、传输方向、传输大小、源和目标数据格式、
		  循环或正常模式、流优先级、源和目标递增模式、FIFO 模式及其阈值(如果需要)、
		  源和/或目标的突发模式 (如果需要)使用 DMA_Init() 函数。

          为避免填充不必要的字段，您可以调用 DMA_StructInit() 函数
		  以使用默认值(重置值)初始化给定结构，只修改必要的字段
           (即源地址和目标地址、传输大小和数据格式)。

      (#) 使用函数启用 NVIC 和相应的中断
           DMA_ITConfig() 如果您需要使用 DMA 中断。

      (#) 或者，如果启用了循环模式，您可以通过函数 DMA_DoubleBufferModeConfig()
		  配置要使用的第二个内存地址和第一个内存来使用双缓冲区模式。
		  然后通过函数 DMA_DoubleBufferModeCmd() 启用双缓冲模式。
		  这些操作必须在步骤 6 之前完成。

      (#) 使用 DMA_Cmd() 函数启用 DMA 流。

      (#) 使用 PPP_DMACmd() 函数为除内部 SRAM 和 FLASH 之外的任何 PPP 外设(即 SPI、USART ...)
		  激活所需的流请求。每个 PPP 外设驱动程序中都提供了允许此操作的函数(即 SPI 外设的 SPI_DMACmd)。

		  启用流后，除非流被停止和禁用，否则无法修改其配置。
          启用 Stream 后，建议使用函数 DMA_GetCmdStatus() 监控 EN 位状态。
		  在配置错误或总线错误的情况下，该位将保持复位并且该流上的所有传输将保持保持。

      (#) 或者，您可以使用函数 DMA_SetCurrDataCounter()
			配置在禁用流时(即在每个传输完成事件之后或发生传输错误时)要传输的数据数量。

		  您可以在运行时(启用并运行 DMA 流时)使用函数 DMA_GetCurrDataCounter() 获取要传输的剩余数据数。

      (#) 要控制 DMA 事件，您可以使用以下两种方法之一:
        (##) 使用函数 DMA_GetFlagStatus() 检查 DMA 流标志。
        (##) 在初始化阶段通过函数 DMA_ITConfig() 使用 DMA 中断，
			 在通信阶段通过 DMA_GetITStatus() 函数进入中断例程。
    [..]
          检查标志后，您应该使用 DMA_ClearFlag() 函数清除它。
		  在检查中断事件后，您应该使用 DMA_ClearITPendingBit() 函数将其清除。

      (#) 或者，如果启用循环模式和双缓冲区模式，您可以使用函数 DMA_MemoryTargetConfig() 修改内存地址。
			确保要修改的内存地址不是 DMA Stream 当前正在使用的内存地址。
          可以使用函数 DMA_GetCurrentMemoryTarget() 监控这种情况。

      (#) 可选地，可以执行暂停-恢复操作:
          DMA_Cmd() 函数可用于执行暂停-恢复操作。
          当传输正在进行时，调用此函数禁用 Stream 将导致传输暂停。
		  所有配置寄存器和剩余数据的数量将被保留。
		  当再次调用此函数重新启用 Stream 时，传输将从暂停点恢复。

      -@- 通过将内存地址设置到外设寄存器中，可以实现内存到内存的传输。
		  在此模式下，不允许使用循环模式和双缓冲模式。

      -@- FIFO 主要用于减少总线使用并允许数据打包/解包:
		  可以为外设和内存设置不同的数据大小(即，您可以为外设设置半字数据大小以访问其数据寄存器
		  并设置内存的字数据大小以获得访问时间。'
		  每两个半字将被打包并写入一次访问内存中的一个字)。

      -@- FIFO 禁用时，不允许配置不同的
           源和目标的数据大小。 在这种情况下，外围数据大小将应用于源和目标。

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
#include "stm32f4xx_dma.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup DMA
  * 简介: DMA 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* 掩码定义 */
#define TRANSFER_IT_ENABLE_MASK (uint32_t)(DMA_SxCR_TCIE | DMA_SxCR_HTIE | \
        DMA_SxCR_TEIE | DMA_SxCR_DMEIE)

#define DMA_Stream0_IT_MASK     (uint32_t)(DMA_LISR_FEIF0 | DMA_LISR_DMEIF0 | \
        DMA_LISR_TEIF0 | DMA_LISR_HTIF0 | \
        DMA_LISR_TCIF0)

#define DMA_Stream1_IT_MASK     (uint32_t)(DMA_Stream0_IT_MASK << 6)
#define DMA_Stream2_IT_MASK     (uint32_t)(DMA_Stream0_IT_MASK << 16)
#define DMA_Stream3_IT_MASK     (uint32_t)(DMA_Stream0_IT_MASK << 22)
#define DMA_Stream4_IT_MASK     (uint32_t)(DMA_Stream0_IT_MASK | (uint32_t)0x20000000)
#define DMA_Stream5_IT_MASK     (uint32_t)(DMA_Stream1_IT_MASK | (uint32_t)0x20000000)
#define DMA_Stream6_IT_MASK     (uint32_t)(DMA_Stream2_IT_MASK | (uint32_t)0x20000000)
#define DMA_Stream7_IT_MASK     (uint32_t)(DMA_Stream3_IT_MASK | (uint32_t)0x20000000)
#define TRANSFER_IT_MASK        (uint32_t)0x0F3C0F3C
#define HIGH_ISR_MASK           (uint32_t)0x20000000
#define RESERVED_MASK           (uint32_t)0x0F7D0F7D

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/


/** @defgroup DMA_Private_Functions
  */

/** @defgroup DMA_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
                ##### 初始化和配置函数 #####
 ===============================================================================
    [..]
    本小节提供了允许初始化 DMA 流源地址和目标地址、增量和数据大小、传输方向、缓冲区大小、
    循环/正常模式选择、内存到内存模式选择和流优先级值的函数。
    [..]
    DMA_Init() 函数遵循参考手册(RM0090)中描述的 DMA 配置程序，但第一点除外:等待 EN 位复位。
    在调用 DMA_Init() 函数之前，用户应用程序应使用函数 DMA_GetCmdStatus() 检查此条件。

@endverbatim
  */

/**
  * 简介:  将 DMAy Streamx 寄存器取消初始化为其默认复位值。
  * 
  * 参数:  DMAy_Streamx: 其中 y 可以是1或2，以选择 DMA, x 可以是 0 到 7，以选择 DMA 流。
  *  
  * 返回值: 无
  */
void DMA_DeInit(DMA_Stream_TypeDef* DMAy_Streamx) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));

    /* 禁用被选中的 DMAy Streamx */
    DMAy_Streamx->CR &= ~((uint32_t)DMA_SxCR_EN);

    /* 重置 DMAy Streamx control 寄存器 */
    DMAy_Streamx->CR  = 0;

    /* 重置 DMAy Streamx Number of Data to Transfer 寄存器 */
    DMAy_Streamx->NDTR = 0;

    /* 重置 DMAy Streamx peripheral address 寄存器 */
    DMAy_Streamx->PAR  = 0;

    /* 重置 DMAy Streamx memory 0 address 寄存器 */
    DMAy_Streamx->M0AR = 0;

    /* 重置 DMAy Streamx memory 1 address 寄存器 */
    DMAy_Streamx->M1AR = 0;

    /* 重置 DMAy Streamx FIFO control 寄存器 */
    DMAy_Streamx->FCR = (uint32_t)0x00000021;

    /* 重置 interrupt pending bits for the selected stream */
    if (DMAy_Streamx == DMA1_Stream0) {
        /* 重置 DMA1 Stream0 的中断挂起位 */
        DMA1->LIFCR = DMA_Stream0_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream1) {
        /* 重置 DMA1 Stream1 的中断挂起位 */
        DMA1->LIFCR = DMA_Stream1_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream2) {
        /* 重置 DMA1 Stream2 的中断挂起位 */
        DMA1->LIFCR = DMA_Stream2_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream3) {
        /* 重置 DMA1 Stream3 的中断挂起位 */
        DMA1->LIFCR = DMA_Stream3_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream4) {
        /* 重置 DMA1 Stream4 的中断挂起位 */
        DMA1->HIFCR = DMA_Stream4_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream5) {
        /* 重置 DMA1 Stream5 的中断挂起位 */
        DMA1->HIFCR = DMA_Stream5_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream6) {
        /* 重置 DMA1 Stream6 的中断挂起位 */
        DMA1->HIFCR = (uint32_t)DMA_Stream6_IT_MASK;
    } else if (DMAy_Streamx == DMA1_Stream7) {
        /* 重置 DMA1 Stream7 的中断挂起位 */
        DMA1->HIFCR = DMA_Stream7_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream0) {
        /* 重置 DMA2 Stream0 的中断挂起位 */
        DMA2->LIFCR = DMA_Stream0_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream1) {
        /* 重置 DMA2 Stream1 的中断挂起位 */
        DMA2->LIFCR = DMA_Stream1_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream2) {
        /* 重置 DMA2 Stream2 的中断挂起位 */
        DMA2->LIFCR = DMA_Stream2_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream3) {
        /* 重置 DMA2 Stream3 的中断挂起位 */
        DMA2->LIFCR = DMA_Stream3_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream4) {
        /* 重置 DMA2 Stream4 的中断挂起位 */
        DMA2->HIFCR = DMA_Stream4_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream5) {
        /* 重置 DMA2 Stream5 的中断挂起位 */
        DMA2->HIFCR = DMA_Stream5_IT_MASK;
    } else if (DMAy_Streamx == DMA2_Stream6) {
        /* 重置 DMA2 Stream6 的中断挂起位 */
        DMA2->HIFCR = DMA_Stream6_IT_MASK;
    } else {
        if (DMAy_Streamx == DMA2_Stream7) {
            /* 重置 DMA2 Stream7 的中断挂起位 */
            DMA2->HIFCR = DMA_Stream7_IT_MASK;
        }
    }
}

/**
  * 简介:  根据 DMA_InitStruct 结构中的指定参数初始化 DMAy Streamx。
  * 
  * 注意:   在调用此函数之前，建议使用函数 DMA_GetCmdStatus() 检查 Stream 是否实际被禁用。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  DMA_InitStruct: 指向 DMA_InitTypeDef 结构的指针，该结构包含指定 DMA 流的配置信息。
  * 
  * 返回值: 无
  */
void DMA_Init(DMA_Stream_TypeDef* DMAy_Streamx, DMA_InitTypeDef* DMA_InitStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CHANNEL(DMA_InitStruct->DMA_Channel));
    assert_param(IS_DMA_DIRECTION(DMA_InitStruct->DMA_DIR));
    assert_param(IS_DMA_BUFFER_SIZE(DMA_InitStruct->DMA_BufferSize));
    assert_param(IS_DMA_PERIPHERAL_INC_STATE(DMA_InitStruct->DMA_PeripheralInc));
    assert_param(IS_DMA_MEMORY_INC_STATE(DMA_InitStruct->DMA_MemoryInc));
    assert_param(IS_DMA_PERIPHERAL_DATA_SIZE(DMA_InitStruct->DMA_PeripheralDataSize));
    assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitStruct->DMA_MemoryDataSize));
    assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
    assert_param(IS_DMA_PRIORITY(DMA_InitStruct->DMA_Priority));
    assert_param(IS_DMA_FIFO_MODE_STATE(DMA_InitStruct->DMA_FIFOMode));
    assert_param(IS_DMA_FIFO_THRESHOLD(DMA_InitStruct->DMA_FIFOThreshold));
    assert_param(IS_DMA_MEMORY_BURST(DMA_InitStruct->DMA_MemoryBurst));
    assert_param(IS_DMA_PERIPHERAL_BURST(DMA_InitStruct->DMA_PeripheralBurst));

    /*------------------------- DMAy Streamx CR 配置 ------------------*/
    /* 获取 DMAy_Streamx CR 值 */
    tmpreg = DMAy_Streamx->CR;

    /* 清除 CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR 位 */
    tmpreg &= ((uint32_t)~(DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST | \
                           DMA_SxCR_PL | DMA_SxCR_MSIZE | DMA_SxCR_PSIZE | \
                           DMA_SxCR_MINC | DMA_SxCR_PINC | DMA_SxCR_CIRC | \
                           DMA_SxCR_DIR));

    /* 配置 DMAy Streamx: */
    /* 设置 CHSEL bits 根据 DMA_CHSEL 值 */
    /* 设置 DIR bits 根据 DMA_DIR 值 */
    /* 设置 PINC bit 根据 DMA_PeripheralInc 值 */
    /* 设置 MINC bit 根据 DMA_MemoryInc 值 */
    /* 设置 PSIZE bits 根据 DMA_PeripheralDataSize 值 */
    /* 设置 MSIZE bits 根据 DMA_MemoryDataSize 值 */
    /* 设置 CIRC bit 根据 DMA_Mode 值 */
    /* 设置 PL bits 根据 DMA_Priority 值 */
    /* 设置 MBURST bits 根据 DMA_MemoryBurst 值 */
    /* 设置 PBURST bits 根据 DMA_PeripheralBurst 值 */
    tmpreg |= DMA_InitStruct->DMA_Channel | DMA_InitStruct->DMA_DIR |
              DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
              DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
              DMA_InitStruct->DMA_Mode | DMA_InitStruct->DMA_Priority |
              DMA_InitStruct->DMA_MemoryBurst | DMA_InitStruct->DMA_PeripheralBurst;

    /* 写入 DMAy Streamx CR 寄存器 */
    DMAy_Streamx->CR = tmpreg;

    /*------------------------- DMAy Streamx FCR 配置 -----------------*/
    /* 获取 DMAy_Streamx FCR 值 */
    tmpreg = DMAy_Streamx->FCR;

    /* 清除 DMDIS and FTH 位 */
    tmpreg &= (uint32_t)~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);

    /* 配置 DMAy Streamx FIFO:
      设置 DMDIS bits 根据 DMA_FIFOMode value
      设置 FTH bits 根据 DMA_FIFOThreshold 值 */
    tmpreg |= DMA_InitStruct->DMA_FIFOMode | DMA_InitStruct->DMA_FIFOThreshold;

    /* 写入 DMAy Streamx CR */
    DMAy_Streamx->FCR = tmpreg;

    /*------------------------- DMAy Streamx NDTR 配置 ----------------*/
    /* 写入 DMAy Streamx NDTR 寄存器 */
    DMAy_Streamx->NDTR = DMA_InitStruct->DMA_BufferSize;

    /*------------------------- DMAy Streamx PAR 配置 -----------------*/
    /* 写入 DMAy Streamx PAR */
    DMAy_Streamx->PAR = DMA_InitStruct->DMA_PeripheralBaseAddr;

    /*------------------------- DMAy Streamx M0AR 配置 ----------------*/
    /* 写入 DMAy Streamx M0AR */
    DMAy_Streamx->M0AR = DMA_InitStruct->DMA_Memory0BaseAddr;
}

/**
  * 简介:  用默认值填充每个 DMA_InitStruct 成员。
  * 
  * 参数:  DMA_InitStruct : 指向将被初始化的 DMA_InitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct) {
    /*-------------- 重置 DMA初始化结构参数值 ----------------*/
    /* 初始化 DMA_Channel 成员 */
    DMA_InitStruct->DMA_Channel = 0;

    /* 初始化 DMA_PeripheralBaseAddr 成员 */
    DMA_InitStruct->DMA_PeripheralBaseAddr = 0;

    /* 初始化 DMA_Memory0BaseAddr 成员 */
    DMA_InitStruct->DMA_Memory0BaseAddr = 0;

    /* 初始化 DMA_DIR 成员 */
    DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralToMemory;

    /* 初始化 DMA_BufferSize 成员 */
    DMA_InitStruct->DMA_BufferSize = 0;

    /* 初始化 DMA_PeripheralInc 成员 */
    DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;

    /* 初始化 DMA_MemoryInc 成员 */
    DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;

    /* 初始化 DMA_PeripheralDataSize 成员 */
    DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    /* 初始化 DMA_MemoryDataSize 成员 */
    DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

    /* 初始化 DMA_Mode 成员 */
    DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;

    /* 初始化 DMA_Priority 成员 */
    DMA_InitStruct->DMA_Priority = DMA_Priority_Low;

    /* 初始化 DMA_FIFOMode 成员 */
    DMA_InitStruct->DMA_FIFOMode = DMA_FIFOMode_Disable;

    /* 初始化 DMA_FIFOThreshold 成员 */
    DMA_InitStruct->DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;

    /* 初始化 DMA_MemoryBurst 成员 */
    DMA_InitStruct->DMA_MemoryBurst = DMA_MemoryBurst_Single;

    /* 初始化 DMA_PeripheralBurst 成员 */
    DMA_InitStruct->DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
}

/**
  * 简介:  启用或禁用指定的 DMAy Streamx。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  NewState: DMAy Streamx 的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  *
  * 注意:  此功能可用于执行暂停恢复操作。当传输正在进行时，
  *        调用此函数以禁用流将导致传输暂停。将保留所有配置寄存器和剩余数据的数量。
  *        再次调用此函数以重新启用流时，传输将从暂停的点恢复。
  *
  * 注意:  配置 DMA 流(DMA_Init() 函数)并启用该流后，建议检查(或等待)
  *        DMA 流是否有效启用。如果配置参数错误，流可能会保持禁用状态。
  *        禁用 DMA 流后，还建议检查(或等待)DMA 流被有效禁用。如果流在数据传输过程中被禁用，
  *        则当前数据将被传输，只有在完成单个数据的传输后，流才会被有效禁用。
  *
  * 返回值: 无
  */
void DMA_Cmd(DMA_Stream_TypeDef* DMAy_Streamx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 DMAy Streamx by setting EN 位 */
        DMAy_Streamx->CR |= (uint32_t)DMA_SxCR_EN;
    } else {
        /* 禁用被选中的 DMAy Streamx by clearing EN 位 */
        DMAy_Streamx->CR &= ~(uint32_t)DMA_SxCR_EN;
    }
}

/**
  * 简介:  设置 PINC(外设增量地址模式)位时，配置外设地址是否应随数据大小(使用 PSIZE 位配置)
  *        或等于 4 的固定偏移量(32 位对齐地址)递增。
  *
  * 注意:   如果禁用"外围增量"模式，则此功能无效。
  *
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  DMA_Pincos: 指定圆周增量偏移大小。
  *          此参数可以是以下值之一:
  *            @arg DMA_PINCOS_Psize: 外设地址增量根据 PSIZE 参数进行。
  *            @arg DMA_PINCOS_WordAligned: 外围地址增量偏移量固定为4(32位对齐地址)。
  * 
  * 返回值: 无
  */
void DMA_PeriphIncOffsetSizeConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_Pincos) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_PINCOS_SIZE(DMA_Pincos));

    /* 检查 the needed Peripheral increment offset */
    if(DMA_Pincos != DMA_PINCOS_Psize) {
        /* 用输入参数配置 DMA_SxCR_PINCOS 位 */
        DMAy_Streamx->CR |= (uint32_t)DMA_SxCR_PINCOS;
    } else {
        /* 清除 PINCOS bit: 外设地址根据 PSIZE 递增 */
        DMAy_Streamx->CR &= ~(uint32_t)DMA_SxCR_PINCOS;
    }
}

/**
  * 简介:  当禁用 DMAy Streamx 时，配置下一个事务(外设或内存)的流控制器。
  *
  * 注意:   在启用此功能之前，请检查使用的外设设备是否支持流量控制器模式。
  *
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  DMA_FlowCtrl: 指定 DMA 流控制器。
  *          此参数可以是以下值之一:
  *            @arg DMA_FlowCtrl_Memory: DMAy_Streamx事务流控制器是 DMA 控制器.
  *            @arg DMA_FlowCtrl_Peripheral: DMAy_Streamx事务流控制器是外设设备。
  * 返回值: 无
  */
void DMA_FlowControllerConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FlowCtrl) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_FLOW_CTRL(DMA_FlowCtrl));

    /* 检查 the needed flow controller  */
    if(DMA_FlowCtrl != DMA_FlowCtrl_Memory) {
        /* 使用输入参数配置 DMA_SxCR_PFCTRL 位 */
        DMAy_Streamx->CR |= (uint32_t)DMA_SxCR_PFCTRL;
    } else {
        /* 清除 PFCTRL bit: 内存是流量控制器 */
        DMAy_Streamx->CR &= ~(uint32_t)DMA_SxCR_PFCTRL;
    }
}

/** @defgroup DMA_Group2 数据计数器功能
 *  简介   数据计数器功能
 *
@verbatim
 ===============================================================================
                      ##### 数据计数器功能 #####
 ===============================================================================
    [..]
    本小节提供了允许配置和读取缓冲区大小(要传输的数据数量)的功能。
    [..]
    仅当 DMA 流被禁用时(即传输完成事件后)，才能写入 DMA 数据计数器。
    [..]
    以下函数可用于写入流数据计数器值:
      (+) void DMA_SetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx, uint16_t Counter);
      -@- 在只需要重新加载数据缓冲区的情况下，建议使用此函数而不是 DMA_Init()。
      -@- 如果"源数据大小"和"目标数据大小"不同，
          则写入数据计数器的值(表示传输数)与"外设设备"的传输数相关。
          例如，如果内存数据大小为 Word，外设设备数据大小为 Half Words，
          则数据计数器中要配置的值是要从/传输到外设设备的 Half Word数。
    [..]
    可以读取 DMA 数据计数器，以指示相对 DMA 流的剩余传输数。
    此计数器在每次数据传输结束时以及传输完成时递减:
      (+) 如果选择正常模式: 计数器被设置为0。
      (+) 如果选择了循环模式: 计数器被重新加载初始值(在启用 DMA 流之前配置的)。
     [..]
     下面的函数可以用来读取 Stream 数据计数器的值:
       (+) uint16_t DMA_GetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx);

@endverbatim
  */

/**
  * 简介:  写入要在 DMAy Streamx 上传输的数据单元的数量。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  Counter: 要传输的数据单元数(从 0 到65535)数据项数仅取决于外设设备数据格式。
  *
  * 注意:   如果外设设备数据格式为字节:数据单元数等于要传输的总字节数。
  *
  * 注意:   如果外设设备数据格式为半字:数据单元数等于要传输的总字节数/2。
  *
  * 注意:   如果外设设备数据格式为 Word:数据单元数等于要传输的总字节数/4。
  *
  * 注意:   在内存到内存传输模式中，DMAy_SxPAR 寄存器指向的内存缓冲区被视为外设。
  *
  * 返回值: 当前 DMAy Streamx 传输中剩余的数据单元数。
  */
void DMA_SetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx, uint16_t Counter) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));

    /* 要传输的数据单元数 */
    DMAy_Streamx->NDTR = (uint16_t)Counter;
}

/**
  * 简介:  Returns 当前 DMAy Streamx 传输中剩余的数据单元数。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 返回值: 当前 DMAy Streamx 传输中剩余的数据单元数。
  */
uint16_t DMA_GetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));

    /* DMAy Streamx 的剩余数据单元数 */
    return ((uint16_t)(DMAy_Streamx->NDTR));
}

/** @defgroup DMA_Group3 双缓冲模式功能
 *  简介   双缓冲模式功能
 *
@verbatim
 ===============================================================================
                    ##### 双缓冲模式功能 #####
 ===============================================================================
    [..]
    本小节提供了允许配置和控制双缓冲模式参数的功能。
    [..]
    只有启用"循环"模式时，才能使用"双缓冲区"模式。
    在将数据从内存传输到内存时，不能使用双缓冲区模式。

    [..]
    双缓冲区模式允许设置 DMA 控制器交替访问的两个不同内存地址
        (完成与目标内存0 的传输后，将开始与目标内存1 的传输)。
    这可以减少双缓冲的软件开销，并减少CPU访问时间。

    [..]
    在调用 DMA_Init() 函数之前，必须调用两个函数:
      (+) void DMA_DoubleBufferModeConfig(DMA_Stream_TypeDef* DMAy_Streamx,
          uint32_t Memory1BaseAddr, uint32_t DMA_CurrentMemory);
      (+) void DMA_DoubleBufferModeCmd(DMA_Stream_TypeDef* DMAy_Streamx, FunctionalState NewState);

    [..]
    调用 DMA_DoubleBufferModeConfig() 配置内存1基址和启用 DMA 流后开始传输的第一个内存目标。
    然后必须调用 DMA_DoubleBufferModeCmd() 以启用双缓冲区模式(或在不应使用时禁用它)。

    [..]
    当传输正在进行时(或 DMA 流停止时)，可以动态调用两个函数来修改目标内存地址或检查当前使用的内存目标:
      (+) void DMA_MemoryTargetConfig(DMA_Stream_TypeDef* DMAy_Streamx,
                                      uint32_t MemoryBaseAddr, uint32_t DMA_MemoryTarget);
      (+) uint32_t DMA_GetCurrentMemoryTarget(DMA_Stream_TypeDef* DMAy_Streamx);

    [..]
    可以调用 DMA_MemoryTargetConfig() 来修改两个目标内存之一的基址。
    DMA 流当前不得使用将修改基址的内存(即，如果 DMA 流目前正在从内存1传输，
        则只能修改目标内存0 的基址，反之亦然)。
    要检查此条件，建议使用函数 DMA_GetCurrentMemoryTarget()，
        该函数返回 DMA 流当前使用的内存目标的索引。

@endverbatim
  */

/**
  * 简介:  当禁用 DMAy Streamx 时，配置双缓冲模式和当前内存目标。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  Memory1BaseAddr: 第二个缓冲区(存储器1)的基址
  * 
  * 参数:  DMA_CurrentMemory: 指定启用流时，哪个内存将是事务的第一个缓冲区。
  *          此参数可以是以下值之一:
  *            @arg DMA_Memory_0: Memory 0 是当前缓冲区。
  *            @arg DMA_Memory_1: Memory 1 是当前缓冲区。
  *
  * 注意:   Memory0BaseAddr 由 DMA_Init() 中的 DMA 结构配置设置。
  *
  * 返回值: 无
  */
void DMA_DoubleBufferModeConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t Memory1BaseAddr,
                                uint32_t DMA_CurrentMemory) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CURRENT_MEM(DMA_CurrentMemory));

    if (DMA_CurrentMemory != DMA_Memory_0) {
        /* 设置"内存1"为当前内存地址 */
        DMAy_Streamx->CR |= (uint32_t)(DMA_SxCR_CT);
    } else {
        /* 设置"内存0"为当前内存地址 */
        DMAy_Streamx->CR &= ~(uint32_t)(DMA_SxCR_CT);
    }

    /* 写入 DMAy Streamx M1AR */
    DMAy_Streamx->M1AR = Memory1BaseAddr;
}

/**
  * 简介:  启用或禁用选定 DMA 流的双缓冲模式。
  * 
  * 注意:   只有在禁用 DMA 流时才能调用此函数。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  NewState: DMAy Streamx 双缓冲模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DMA_DoubleBufferModeCmd(DMA_Stream_TypeDef* DMAy_Streamx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 配置双缓冲模式 */
    if (NewState != DISABLE) {
        /* 启用双缓冲模式 */
        DMAy_Streamx->CR |= (uint32_t)DMA_SxCR_DBM;
    } else {
        /* 禁用双缓冲模式 */
        DMAy_Streamx->CR &= ~(uint32_t)DMA_SxCR_DBM;
    }
}

/**
  * 简介:  为双缓冲区模式下的下一个缓冲区传输配置内存地址(用于动态使用)。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  MemoryBaseAddr: 目标内存缓冲区的基地址
  * 
  * 参数:  DMA_MemoryTarget: 下一个要使用的内存目标。
  *         此参数可以是以下值之一:
  *            @arg DMA_Memory_0: 使用内存地址0
  *            @arg DMA_Memory_1: 使用内存地址1
  *
  * 注意:    当目标内存参与当前传输时，不允许修改该目标内存的基本地址。
			 即，如果 DMA 流当前正在向存储器1传输/从存储器1传输，
			 则不可能修改存储器1 的基本地址，但可以修改存储器0 的基本地址。
  *          要知道当前使用的内存，可以使用函数 DMA_GetCurrentMemoryTarget()。
  *
  * 返回值: 无
  */
void DMA_MemoryTargetConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t MemoryBaseAddr,
                            uint32_t DMA_MemoryTarget) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CURRENT_MEM(DMA_MemoryTarget));

    /* 待配置的内存目标器 */
    if (DMA_MemoryTarget != DMA_Memory_0) {
        /* 写入 DMAy Streamx M1AR */
        DMAy_Streamx->M1AR = MemoryBaseAddr;
    } else {
        /* 写入 DMAy Streamx M0AR */
        DMAy_Streamx->M0AR = MemoryBaseAddr;
    }
}

/**
  * 简介:  返回双缓冲区传输使用的当前内存目标。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 返回值: 内存目标数: Memory0 为 0,Memory1 为 1。
  */
uint32_t DMA_GetCurrentMemoryTarget(DMA_Stream_TypeDef* DMAy_Streamx) {
    uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));

    /* 获取当前内存目标 */
    if ((DMAy_Streamx->CR & DMA_SxCR_CT) != 0) {
        /* 当前使用的内存缓冲区是内存1 */
        tmp = 1;
    } else {
        /* 当前使用的内存缓冲区是内存0 */
        tmp = 0;
    }

    return tmp;
}

/** @defgroup DMA_Group4 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
              ##### 中断和标记管理函数 #####
 ===============================================================================
    [..]
本小节提供了以下功能:
(+) 检查DMA启用状态
(+) 检查FIFO状态
(+)配置 DMA中断源并检查或清除标志或挂起位状态。

    [..]
      (#) DMA启用状态:
          配置 DMA 流(DMA_Init() 函数)并启用该流后，建议检查(或等待)DMA 流是否有效启用。
          如果配置参数错误，流可能会保持禁用状态。禁用 DMA 流后，还建议检查(或等待)DMA 流被有效禁用。
          如果流在数据传输过程中被禁用，则当前数据将被传输，只有在数据传输完成后，流才会被有效禁用。
          要监视此状态，可以使用以下功能:
        (++) FunctionalState DMA_GetCmdStatus(DMA_Stream_TypeDef* DMAy_Streamx);

      (#) FIFO 状态:
          当传输正在进行时，可以使用以下功能监控FIFO状态:
        (++) uint32_t DMA_GetFIFOStatus(DMA_Stream_TypeDef* DMAy_Streamx);

      (#) DMA中断和标志:
          用户应确定在其应用程序中将使用哪种模式来管理 DMA 控制器事件:轮询模式或中断模式。

    *** 轮询模式 ***
    ====================
    [..]
    每个 DMA 流可以通过4个事件标志进行管理:
    (x:DMA 流编号)
    (#) DMA_FLAG_FEIFx: 表示发生 FIFO 模式传输错误事件。
    (#) DMA_FLAG_DMEIFx: 表示发生了直接模式传输错误事件。
    (#) DMA_FLAG_TEIFx: 表示发生了传输错误事件。
    (#) DMA_FLAG_HTIFx: 表示发生了"半传输完成"事件。
    (#) DMA_FLAG_TCIFx: 表示发生传输完成事件。
    [..]
    在此模式下，建议使用以下功能:
      (+) FlagStatus DMA_GetFlagStatus(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FLAG);
      (+) void DMA_ClearFlag(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FLAG);

    *** 中断模式 ***
    ======================
    [..]
    每个 DMA 流可以通过4个中断进行管理:

    *** 中断源 ***
    ========================
    [..]
     (#) DMA_IT_FEIFx: 指定 FIFO 模式传输错误事件的中断源。
     (#) DMA_IT_DMEIFx: 指定直接模式传输错误事件的中断源。
     (#) DMA_IT_TEIFx: 指定传输错误事件的中断源。
     (#) DMA_IT_HTIFx: 指定"半传输完成"事件的中断源。
     (#) DMA_IT_TCIFx: 指定传输完成事件的中断源。
    [..]
    在此模式下，建议使用以下功能:
      (+) void DMA_ITConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT, FunctionalState NewState);
      (+) ITStatus DMA_GetITStatus(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT);
      (+) void DMA_ClearITPendingBit(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT);

@endverbatim
  */

/**
  * 简介:  返回指定 DMAy Streamx 的 EN 位的状态。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  *
  * 注意:    配置 DMA 流(DMA_Init() 函数)并启用该流后，建议检查(或等待)
  *              DMA 流是否有效启用。如果配置参数错误，流可能会保持禁用状态。
  *          禁用 DMA 流后，还建议检查(或等待)DMA 流被有效禁用。如果流在数据
  *              传输过程中被禁用，则当前数据将被传输，只有在完成单个数据的传输后，
  *              流才会被有效禁用。
  *
  * 返回值: DMAy Streamx 的当前状态(ENABLE 或 DISABLE)。
  */
FunctionalState DMA_GetCmdStatus(DMA_Stream_TypeDef* DMAy_Streamx) {
    FunctionalState state = DISABLE;

    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));

    if ((DMAy_Streamx->CR & (uint32_t)DMA_SxCR_EN) != 0) {
        /* 设置了所选的 DMAy Streamx EN 位(DMA仍在传输) */
        state = ENABLE;
    } else {
        /* 选中的 DMAy Streamx EN 位被清除(DMA被禁用，所有传输都完成)
    }

    return state;
}

/**
  * 简介:  返回当前的 DMAy Streamx FIFO 填充级别。

  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。

  * 返回值: FIFO填充状态。
  *           -DMA_FIFOStatus_Less1QuarterFull: 当 FIFO 小于1/4满且不为空时。
  *           -DMA_FIFOStatus_1QuarterFull: 如果超过四分之一满。
  *           -DMA_FIFOStatus_HalfFull: 如果超过一半满。
  *           -DMA_FIFOStatus_3QuartersFull: 如果已满四分之三以上。
  *           -DMA_FIFOStatus_Empty: 当 FIFO 为空时
  *           -DMA_FIFOStatus_Full: 当 FIFO 已满时
  */
uint32_t DMA_GetFIFOStatus(DMA_Stream_TypeDef* DMAy_Streamx) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));

    /* 获取 FIFO level 位 */
    tmpreg = (uint32_t)((DMAy_Streamx->FCR & DMA_SxFCR_FS));

    return tmpreg;
}

/**
  * 简介:  检查是否设置了指定的 DMAy Streamx 标志。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  DMA_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg DMA_FLAG_TCIFx: Streamx 传输完成标志
  *            @arg DMA_FLAG_HTIFx: Streamx 半传输完成标志
  *            @arg DMA_FLAG_TEIFx: Streamx 传输错误标志
  *            @arg DMA_FLAG_DMEIFx: Streamx 直接模式错误标志
  *            @arg DMA_FLAG_FEIFx: Streamx FIFO 错误标志
  *            其中 x 可以是 0 到 7，以选择 DMA 流。
  * 
  * 返回值: DMA_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus DMA_GetFlagStatus(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FLAG) {
    FlagStatus bitstatus = RESET;
    DMA_TypeDef* DMAy;
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_GET_FLAG(DMA_FLAG));

    /* 确定该流所属的 DMA */
    if (DMAy_Streamx < DMA2_Stream0) {
        /* DMAy_Streamx 属于 DMA1 */
        DMAy = DMA1;
    } else {
        /* DMAy_Streamx 属于 DMA2 */
        DMAy = DMA2;
    }

    /* 如果标志在 HISR 或 LISR 中 */
    if ((DMA_FLAG & HIGH_ISR_MASK) != (uint32_t)RESET) {
        /* 得到 DMAy HISr 寄存器值 */
        tmpreg = DMAy->HISR;
    } else {
        /* 得到 DMAy LISr 寄存器值 */
        tmpreg = DMAy->LISR;
    }

    /* Mask the reserved 位 */
    tmpreg &= (uint32_t)RESERVED_MASK;

    /* 检查指定 DMA 标志的状态 */
    if ((tmpreg & DMA_FLAG) != (uint32_t)RESET) {
        /* DMA_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* DMA_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回 DMA_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 DMAy Streamx 的挂起标志。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  DMA_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *          @arg DMA_FLAG_TCIFx: Streamx 传输完成标志
  *          @arg DMA_FLAG_HTIFx: Streamx 半传输完成标志
  *          @arg DMA_FLAG_TEIFx: Streamx 传输错误标志
  *          @arg DMA_FLAG_DMEIFx: Streamx 直接模式错误标志
  *          @arg DMA_FLAG_FEIFx: Streamx FIFO 错误标志
  *          其中 x 可以是 0 到 7，以选择 DMA 流。
  * 
  * 返回值: 无
  */
void DMA_ClearFlag(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FLAG) {
    DMA_TypeDef* DMAy;

    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CLEAR_FLAG(DMA_FLAG));

    /* 确定该流所属的 DMA */
    if (DMAy_Streamx < DMA2_Stream0) {
        /* DMAy_Streamx 属于 DMA1 */
        DMAy = DMA1;
    } else {
        /* DMAy_Streamx 属于 DMA2 */
        DMAy = DMA2;
    }

    /* 是否以 LIFCR 或 HIFCR 寄存器为目标 */
    if ((DMA_FLAG & HIGH_ISR_MASK) != (uint32_t)RESET) {
        /* 设置 DMAy HIFCR 寄存器清除标志位 */
        DMAy->HIFCR = (uint32_t)(DMA_FLAG & RESERVED_MASK);
    } else {
        /* 设置 DMAy LIFCR 寄存器清除标志位 */
        DMAy->LIFCR = (uint32_t)(DMA_FLAG & RESERVED_MASK);
    }
}

/**
  * 简介:  启用或禁用指定的 DMAy Streamx 中断。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数: DMA_IT: 指定要启用或禁用的 DMA中断源。
  *          此参数可以是以下值的任意组合:
  *          @arg DMA_IT_TC: 传输完成中断掩码
  *          @arg DMA_IT_HT: 半传输完成中断掩码
  *          @arg DMA_IT_TE: 传输错误中断掩码
  *          @arg DMA_IT_FE: FIFO错误中断掩码
  * 
  * 参数:  NewState: 指定 DMA中断的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DMA_ITConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CONFIG_IT(DMA_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 检查如果 DMA_IT参数包含 FIFO 中断 */
    if ((DMA_IT & DMA_IT_FE) != 0) {
        if (NewState != DISABLE) {
            /* 启用选定的 DMA FIFO 中断 */
            DMAy_Streamx->FCR |= (uint32_t)DMA_IT_FE;
        } else {
            /* 禁用选定的 DMA FIFO 中断 */
            DMAy_Streamx->FCR &= ~(uint32_t)DMA_IT_FE;
        }
    }

    /* 检查如果 DMA_IT参数包含传输中断 */
    if (DMA_IT != DMA_IT_FE) {
        if (NewState != DISABLE) {
            /* 启用选定的 DMA 传输中断 */
            DMAy_Streamx->CR |= (uint32_t)(DMA_IT  & TRANSFER_IT_ENABLE_MASK);
        } else {
            /* 禁用选定的 DMA 传输中断 */
            DMAy_Streamx->CR &= ~(uint32_t)(DMA_IT & TRANSFER_IT_ENABLE_MASK);
        }
    }
}

/**
  * 简介:  检查是否发生了指定的 DMAy Streamx 中断。
  * 
  * 参数:  DMAy_Streamx: 其中y可以是1或2以选择 DMA，x 可以是 0 到 7以选择 DMAStream。
  * 
  * 参数:  DMA_IT: 指定要检查的 DMA中断源。
  *          此参数可以是以下值之一:
  *          @arg DMA_IT_TCIFx: Streamx 传输完成中断
  *          @arg DMA_IT_HTIFx: Streamx 半传输完成中断
  *          @arg DMA_IT_TEIFx: Streamx 传输错误中断
  *          @arg DMA_IT_DMEIFx: Streamx 直接模式错误中断
  *          @arg DMA_IT_FEIFx: Streamx FIFO 错误中断
  *          其中 x 可以是 0 到 7，以选择 DMA 流。
  * 
  * 返回值: DMA_IT 的新状态(SET 或 RESET)。
  */
ITStatus DMA_GetITStatus(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT) {
    ITStatus bitstatus = RESET;
    DMA_TypeDef* DMAy;
    uint32_t tmpreg = 0, enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_GET_IT(DMA_IT));

    /* 确定该流所属的 DMA */
    if (DMAy_Streamx < DMA2_Stream0) {
        /* DMAy_Streamx 属于 DMA1 */
        DMAy = DMA1;
    } else {
        /* DMAy_Streamx 属于 DMA2 */
        DMAy = DMA2;
    }

    /* 检查如果中断使能位在 CR 或 FCR 中寄存器 */
    if ((DMA_IT & TRANSFER_IT_MASK) != (uint32_t)RESET) {
        /* 在 CR 寄存器中获取中断使能位置掩码 */
        tmpreg = (uint32_t)((DMA_IT >> 11) & TRANSFER_IT_ENABLE_MASK);

        /* 检查 CR 寄存器中的启用位  */
        enablestatus = (uint32_t)(DMAy_Streamx->CR & tmpreg);
    } else {
        /* 检查 FCR 寄存器中的启用位 */
        enablestatus = (uint32_t)(DMAy_Streamx->FCR & DMA_IT_FE);
    }

    /* 检查中断挂起标志是否在 LISR 或 HISR 中 */
    if ((DMA_IT & HIGH_ISR_MASK) != (uint32_t)RESET) {
        /* 得到 DMAy HISr 寄存器值 */
        tmpreg = DMAy->HISR ;
    } else {
        /* 得到 DMAy LISr 寄存器值 */
        tmpreg = DMAy->LISR ;
    }

    /* 掩码全部保留位 */
    tmpreg &= (uint32_t)RESERVED_MASK;

    /* 检查指定 DMA 中断的状态 */
    if (((tmpreg & DMA_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET)) {
        /* DMA_IT 被设置 */
        bitstatus = SET;
    } else {
        /* DMA_IT 被重置 */
        bitstatus = RESET;
    }

    /* 返回 DMA_IT 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 DMAy Streamx 的中断挂起位。
  * 
  * 参数:  DMAy_Streamx: 其中 y 可以是 1 或 2 以选择 DMA，x 可以是 0 到 7 以选择 DMAStream。
  * 
  * 参数:  DMA_IT: 指定要清除的 DMA中断挂起位。
  *          此参数可以是以下值的任意组合:
  *          @arg DMA_IT_TCIFx: Streamx 传输完成中断
  *          @arg DMA_IT_HTIFx: Streamx 半传输完成中断
  *          @arg DMA_IT_TEIFx: Streamx 传输错误中断
  *          @arg DMA_IT_DMEIFx: Streamx 直接模式错误中断
  *          @arg DMA_IT_FEIFx: Streamx FIFO 错误中断
  *          其中 x 可以是 0 到 7，以选择 DMA 流。
  * 
  * 返回值: 无
  */
void DMA_ClearITPendingBit(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT) {
    DMA_TypeDef* DMAy;

    /* 检查参数 */
    assert_param(IS_DMA_ALL_PERIPH(DMAy_Streamx));
    assert_param(IS_DMA_CLEAR_IT(DMA_IT));

    /* 确定该流所属的 DMA */
    if (DMAy_Streamx < DMA2_Stream0) {
        /* DMAy_Streamx 属于 DMA1 */
        DMAy = DMA1;
    } else {
        /* DMAy_Streamx 属于 DMA2 */
        DMAy = DMA2;
    }

    /* 是否以 LIFCR 或 HIFCR 寄存器为目标 */
    if ((DMA_IT & HIGH_ISR_MASK) != (uint32_t)RESET) {
        /* 设置 DMAy HIFCR 寄存器清除中断位 */
        DMAy->HIFCR = (uint32_t)(DMA_IT & RESERVED_MASK);
    } else {
        /* 设置 DMAy LIFCR 寄存器清除中断位 */
        DMAy->LIFCR = (uint32_t)(DMA_IT & RESERVED_MASK);
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
