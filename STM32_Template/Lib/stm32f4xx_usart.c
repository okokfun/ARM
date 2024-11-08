/**
  ******************************************************************************
  * 文件:    stm32f4xx_usart.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供了固件函数，用于管理通用同步异步接收机发射机(USART)的以下功能:
  *           + 初始化和配置
  *           + 数据传输
  *           + 多处理器通信
  *           + LIN 模式
  *           + Half-duplex 模式
  *           + 智能卡模式
  *           + IrDA 模式
  *           + DMA 传输管理
  *           + 中断和标志管理
  *
  @verbatim
 ===============================================================================
                        ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..]
      (#) 使用以下函数启用外围时钟
          RCC_APB2PeriphClockCmd(RCC_APB2Periph_USARTx, ENABLE) for USART1 and USART6
          RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE) for USART2, USART3,
          UART4 or UART5.

      (#) 根据 USART模式，使用
          RCC_AHB1PeriphClockCmd() 函数. (The I/O can be TX, RX, CTS,
          or/and SCLK).

      (#) 外设的替代函数:
        (++) 使用 GPIO_PinAFConfig() 函数将管脚连接到所需外设设备的复用功能(AF)

        (++) 通过以下方式在复用功能中配置所需引脚:
            GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF

        (++) 通过 GPIO_PuPd、GPIO_OType 和 GPIO_speed 成员选择类型、上拉/下拉和输出速度
        
        (++) 调用 GPIO_Init() 函数

      (#) 使用 USART_Init() 函数编程波特率、字长、停止位、奇偶校验、
            硬件流控制和模式(接收器/发送器)。

      (#) 对于同步模式，启用时钟并使用 USART_ClockInit() 函数编程极性、相位和最后一位。

      (#) 如果需要使用中断模式，请使用函数 USART_ITConfig() 启用 NVIC 和相应的中断。

      (#) 使用 DMA 模式时
        (++) 使用 DMA_Init() 函数配置 DMA
        (++) 使用 USART_DMACmd() 函数激活所需的信道请求

      (#) 使用 USART_Cmd() 函数启用 USART。

      (#) 使用 DMA 模式时，使用 DMA_Cmd() 功能启用 DMA。

      -@- 有关更多详细信息，请参阅多处理器、LIN、半双工、智能卡、IrDA 子部分

    [..]
    为了达到更高的通信波特率，可以使用 USART_OverSampling8Cmd() 功能通过8模式启用过采样。
    此函数应在启用 USART 时钟 (RCC_APBxPeriphClockCmd()) 之后调用，并在调用函数 USART_Init() 之前调用。

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
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup USART
  * 简介: USART驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/*!< USART CR1 寄存器清除掩码 ((~(uint16_t)0xE9F3)) */
#define CR1_CLEAR_MASK            ((uint16_t)(USART_CR1_M | USART_CR1_PCE | \
                                   USART_CR1_PS | USART_CR1_TE | \
                                   USART_CR1_RE))

/*!< USART CR2寄存器时钟位清除掩码 ((~(uint16_t)0xF0FF)) */
#define CR2_CLOCK_CLEAR_MASK      ((uint16_t)(USART_CR2_CLKEN | USART_CR2_CPOL | \
                                   USART_CR2_CPHA | USART_CR2_LBCL))

/*!< USART CR3 寄存器清除掩码 ((~(uint16_t)0xFCFF)) */
#define CR3_CLEAR_MASK            ((uint16_t)(USART_CR3_RTSE | USART_CR3_CTSE))

/*!< USART 中断掩码 */
#define IT_MASK                   ((uint16_t)0x001F)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup USART_Private_Functions
  */

/** @defgroup USART_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
            ##### 初始化和配置函数 #####
 ===============================================================================
    [..]
    本小节提供了一组函数，允许在异步和同步模式下初始化 USART。
      (+) 对于异步模式，只能配置以下参数:
        (++) 波特率
        (++) 字长
        (++) 停止位
        (++) 奇偶校验:如果奇偶校验启用，则写入数据寄存器的数据的 MSB 位将被传输，但由奇偶校验位更改。
             根据 M 位(8 位或 9 位)定义的帧长度，可能的 USART 帧格式如下表所示:
   +-------------------------------------------------------------+
   |   M bit |  PCE bit  |            USART frame                |
   |---------------------|---------------------------------------|
   |    0    |    0      |    | SB | 8 bit data | STB |          |
   |---------|-----------|---------------------------------------|
   |    0    |    1      |    | SB | 7 bit data | PB | STB |     |
   |---------|-----------|---------------------------------------|
   |    1    |    0      |    | SB | 9 bit data | STB |          |
   |---------|-----------|---------------------------------------|
   |    1    |    1      |    | SB | 8 bit data | PB | STB |     |
   +-------------------------------------------------------------+
        (++) 硬件流量控制
        (++) 接收器/发射器模式

    [..]
    USART_Init() 函数遵循 USART
        异步配置过程(有关该过程的详细信息，请参见参考手册 (RM0090))。

     (+) 对于同步模式，除了异步模式参数外，还应配置这些参数:
        (++) USART 时钟已启用
        (++) USAT 极性
        (++) USART 阶段
        (++) USART 最后一位

    [..]
    可以使用 USART_ClockInit() 函数配置这些参数。

@endverbatim
  */

/**
  * 简介:  将 USARTx 外围寄存器取消初始化为其默认重置值。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 返回值: 无
  */
void USART_DeInit(USART_TypeDef* USARTx) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    if (USARTx == USART1) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
    } else if (USARTx == USART2) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2, DISABLE);
    } else if (USARTx == USART3) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART3, DISABLE);
    } else if (USARTx == UART4) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART4, DISABLE);
    } else if (USARTx == UART5) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART5, DISABLE);
    } else if (USARTx == USART6) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART6, DISABLE);
    } else if (USARTx == UART7) {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART7, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART7, DISABLE);
    } else if (USARTx == UART8) 
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART8, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_UART8, DISABLE);
}

/**
  * 简介:  根据 USART_InitStruct 中的指定参数初始化 USARTx 外设设备。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_InitStruct: 指向 USART_InitTypeDef 结构的指针，
  *             该结构包含指定 USART 外设设备的配置信息。
  * 返回值: 无
  */
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct) {
    uint32_t tmpreg = 0x00, apbclock = 0x00;
    uint32_t integerdivider = 0x00;
    uint32_t fractionaldivider = 0x00;
    RCC_ClocksTypeDef RCC_ClocksStatus;

    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
    assert_param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
    assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
    assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
    assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
    assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));

    /* 硬件流控制仅适用于 USART1、USART2、USERT3 和 USART6 */
    if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }

    /*---------------------------- USART CR2 配置 -----------------------*/
    tmpreg = USARTx->CR2;

    /* 清除 STOP[13:12]位 */
    tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);

    /* 配置 USART停止位、时钟、CPOL、CPHA 和 LastBit:根据 USART_StopBits值设置 Stop[13:12]位 */
    tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;

    /* 写入 USART CR2 */
    USARTx->CR2 = (uint16_t)tmpreg;

    /*---------------------------- USART CR1 配置 -----------------------*/
    tmpreg = USARTx->CR1;

    /* 清除M、PCE、PS、TE 和 RE 位 */
    tmpreg &= (uint32_t)~((uint32_t)CR1_CLEAR_MASK);

    /* 配置 USART字长、奇偶校验和模式:
       根据 USART_WordLength值设置M位
       根据 USART_Parity 值设置PCE 和 PS 位
       根据 USART_Mode值设置 TE 和 RE 位 */
    tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
              USART_InitStruct->USART_Mode;

    /* 写入 USART CR1 */
    USARTx->CR1 = (uint16_t)tmpreg;

    /*---------------------------- USART CR3 配置 -----------------------*/
    tmpreg = USARTx->CR3;

    /* 清除 CTSE 和 RTSE 位 */
    tmpreg &= (uint32_t)~((uint32_t)CR3_CLEAR_MASK);

    /* 配置 USART HFC:
        根据 USART_HardwareFlowControl值设置 CTSE 和 RTSE 位 */
    tmpreg |= USART_InitStruct->USART_HardwareFlowControl;

    /* 写入 USART CR3 */
    USARTx->CR3 = (uint16_t)tmpreg;

    /*---------------------------- USART BRR 配置 -----------------------*/
    /* 配置 USART波特率 */
    RCC_GetClocksFreq(&RCC_ClocksStatus);

    if ((USARTx == USART1) || (USARTx == USART6)) {
        apbclock = RCC_ClocksStatus.PCLK2_Frequency;
    } else {
        apbclock = RCC_ClocksStatus.PCLK1_Frequency;
    }

    /* 确定整数部分 */
    if ((USARTx->CR1 & USART_CR1_OVER8) != 0) {
        /* 过采样模式为8采样时的整数部分计算 */
        integerdivider = ((25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate)));
    } else { /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
        /* 过采样模式为16采样时的整数部分计算 */
        integerdivider = ((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));
    }

    tmpreg = (integerdivider / 100) << 4;

    /* 确定分数部分 */
    fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

    /* 在寄存器中实现小数部分 */
    if ((USARTx->CR1 & USART_CR1_OVER8) != 0) {
        tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
    } else { /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
        tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
    }

    /* 写入 USART BRR 寄存器 */
    USARTx->BRR = (uint16_t)tmpreg;
}

/**
  * 简介:  用默认值填充每个 USART_InitStruct 成员。
  * 参数:  USART_InitStruct: 指向将被初始化的 USART_InitTypeDef 结构的指针。
  * 返回值: 无
  */
void USART_StructInit(USART_InitTypeDef* USART_InitStruct) {
    /* USART_InitStruct 成员默认值 */
    USART_InitStruct->USART_BaudRate = 9600;
    USART_InitStruct->USART_WordLength = USART_WordLength_8b;
    USART_InitStruct->USART_StopBits = USART_StopBits_1;
    USART_InitStruct->USART_Parity = USART_Parity_No ;
    USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
}

/**
  * 简介:  根据 USART_ClockInitStruct 中的指定参数初始化 USARTx 外围时钟。
  * 参数:  USARTx: 其中 x 可以是1、2、3或6，以选择 USART 外设设备。
  * 参数:  USART_ClockInitStruct: 指向 USART_ClockInitTypeDef 结构的指针，
  *         该结构包含指定 USART 外设设备的配置信息。
  * 注意:   智能卡和同步模式不适用于 UART4 和 UART5。
  * 返回值: 无
  */
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct) {
    uint32_t tmpreg = 0x00;
    /* 检查参数 */
    assert_param(IS_USART_1236_PERIPH(USARTx));
    assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
    assert_param(IS_USART_CPOL(USART_ClockInitStruct->USART_CPOL));
    assert_param(IS_USART_CPHA(USART_ClockInitStruct->USART_CPHA));
    assert_param(IS_USART_LASTBIT(USART_ClockInitStruct->USART_LastBit));

    /*---------------------------- USART CR2 配置 -----------------------*/
    tmpreg = USARTx->CR2;
    /* 清除 CLKEN、CPOL、CPHA 和 LBCL位 */
    tmpreg &= (uint32_t)~((uint32_t)CR2_CLOCK_CLEAR_MASK);
    /* 配置 USART 时钟、CPOL、CPHA 和 LastBit ------------*/
    /* 根据 USART_Clock值设置 CLKEN 位 */
    /* 根据 USART_CPOL值设置 CPOL位 */
    /* 根据 USART_CPHA值设置 CPHA位 */
    /* 根据 USART_LastBit值设置 LBCL位 */
    tmpreg |= (uint32_t)USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL |
              USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit;
    /* 写USART CR2 */
    USARTx->CR2 = (uint16_t)tmpreg;
}

/**
  * 简介:  用默认值填充每个 USART_ClockInitStruct 成员。
  * 参数:  USART_ClockInitStruct: 指向将被初始化的 USART_ClockInitTypeDef 结构的指针。
  * 返回值: 无
  */
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct) {
    /* USART_ClockInitStruct 成员默认值 */
    USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
    USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
    USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

/**
  * 简介:  启用或禁用指定的 USART 外设设备。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: USARTx 外设设备的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过设置 CR1 寄存器中的 UE 位来启用所选USART */
        USARTx->CR1 |= USART_CR1_UE;
    } else {
        /* 通过清除 CR1 寄存器中的 UE 位禁用所选USART */
        USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_UE);
    }
}

/**
  * 简介:  设置系统时钟预分频器。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_Prescaler: 指定预分频器时钟。
  * 注意:   该功能用于 UART4 和 UART5 的 IrDA 模式。
  * 返回值: 无
  */
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* 清除 USART预分频器 */
    USARTx->GTPR &= USART_GTPR_GT;
    /* 设置 USART预分频器 */
    USARTx->GTPR |= USART_Prescaler;
}

/**
  * 简介:  启用或禁用 USART 的8x过采样模式。
  * 注意:   为了获得正确的波特率分频器值，必须在调用 USART_Init() 函数之前调用此函数。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: USART 8x过采样模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过设置 CR1 寄存器中的 OVER8位，启用8x过采样模式*/
        USARTx->CR1 |= USART_CR1_OVER8;
    } else {
        /* 通过清除 CR1 寄存器中的 OVER8位，禁用8x过采样模式*/
        USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_OVER8);
    }
}

/**
  * 简介:  启用或禁用 USART 的一位采样方法。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: USART一位采样方法的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过在 CR3 寄存器中设置 ONEBITE 位来启用一位方法 */
        USARTx->CR3 |= USART_CR3_ONEBIT;
    } else {
        /* 通过清除 CR3 寄存器中的 ONEBITE 位禁用一位方法*/
        USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_ONEBIT);
    }
}


/** @defgroup USART_Group2 数据传输函数
 *  简介   数据传输函数
 *
@verbatim
 ===============================================================================
                      ##### 数据传输函数 #####
 ===============================================================================
    [..]
    本小节提供了一组允许管理 USART 数据传输的函数。
    [..]
    在 USART 接收期间，数据首先通过 RX 引脚以最低有效位移位。
    在此模式下，USART_DR 寄存器由内部总线和接收的移位寄存器之间的缓冲区(RDR)组成。
    [..]
    传输发生时，USART_DR 寄存器的写入指令将数据存储在 TDR 寄存器中，
    并在当前传输结束时复制到移位寄存器中。
    [..]
    USART_DR 寄存器的读取访问可以使用 USART_ReceiveData() 函数完成，
    并返回 RDR 缓冲值。而对 USART_DR 的写入访问可以使用 USART_SendData() 函数完成，
    并将写入的数据存储到 TDR 缓冲区中。

@endverbatim
  */

/**
  * 简介:  通过 USARTx 外设传输单个数据。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  Data:要传输的数据。
  * 返回值: 无
  */
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DATA(Data));

    /* 传输数据 */
    USARTx->DR = (Data & (uint16_t)0x01FF);
}

/**
  * 简介:  返回 USARTx 外设最近接收到的数据。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 返回值: 接收的数据。
  */
uint16_t USART_ReceiveData(USART_TypeDef* USARTx) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* 接收数据 */
    return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}


/** @defgroup USART_Group3 多处理器通讯函数
 *  简介   多处理器通讯函数
 *
@verbatim
 ===============================================================================
              ##### 多处理器通讯函数 #####
 ===============================================================================
    [..]
    本小节提供了一组允许管理 USART 多处理器通信的函数。
    [..]
    例如，其中一个 USART 可以是主机，其 TX 输出连接到另一个 USAR 的 RX 输入。
        其他是从机，它们各自的 TX 输出在逻辑上与在一起，并连接到主机的 RX 输入。
    [..]
    USART 多处理器通信可以通过以下过程实现:
      (#) 使用 USART_Init() 函数编程波特率、字长=9位、停止位、奇偶校验、
            模式发送器或模式接收器以及硬件流控制值。
      (#) 使用 USART_SetAddress() 函数配置 USART 地址。
      (#) 仅使用 USART_WakeUpConfig() 函数为从属设备配置唤醒方法
         (USART_WakeUp_IdleLine 或 USART_WhakeUp_AddressMark)。
      (#) 使用 USART_Cmd() 函数启用 USART。
      (#) 使用 USART_ReceiverWakeUpCmd() 函数以静音模式输入 USART 从机。
    [..]
    收到唤醒条件时，USART Slave 退出静音模式。

@endverbatim
  */

/**
  * 简介:  设置 USART 节点的地址。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_Address: 指示USART 节点的地址。
  * 返回值: 无
  */
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_ADDRESS(USART_Address));

    /* 清除 USART 地址 */
    USARTx->CR2 &= (uint16_t)~((uint16_t)USART_CR2_ADD);
    /* 设置 USART 地址节点 */
    USARTx->CR2 |= USART_Address;
}

/**
  * 简介:  确定 USART 是否处于静音模式。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: USART 静音模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过设置 CR1 寄存器中的 RWU位，启用 USART 静音模式 */
        USARTx->CR1 |= USART_CR1_RWU;
    } else {
        /* 通过清除 CR1 寄存器中的 RWU位禁用 USART 静音模式*/
        USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_RWU);
    }
}
/**
  * 简介:  选择 USART 唤醒方法。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_WakeUp: 指定 USART唤醒方法。
  *          此参数可以是以下值之一:
  *            @arg USART_WakeUp_IdleLine: 通过空闲线路检测唤醒
  *            @arg USART_WakeUp_AddressMark: 通过地址标记唤醒
  * 返回值: 无
  */
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_WAKEUP(USART_WakeUp));

    USARTx->CR1 &= (uint16_t)~((uint16_t)USART_CR1_WAKE);
    USARTx->CR1 |= USART_WakeUp;
}


/** @defgroup USART_Group4 LIN 模式功能
 *  简介   LIN 模式功能
 *
@verbatim
 ===============================================================================
                        ##### LIN 模式功能 #####
 ===============================================================================
    [..]
    本小节提供了一组允许管理 USART LIN 模式通信的函数。
    [..]
    在LIN 模式下，根据 LIN 标准，需要具有 1个停止位的8位数据格式。
    [..]
    USART IP 仅支持此 LIN 功能:
      (+) LIN主同步中断发送功能和 LIN 从中断检测功能: 13位中断生成和10/11位中断检测

    [..]
    USART LIN主发送器通信可以通过以下程序进行:
      (#) 使用 USART_Init() 函数编程波特率、字长=8位、停止位=1位、
            奇偶校验、模式发送器或模式接收器以及硬件流控制值。
      (#) 使用 USART_Cmd() 函数启用 USART。
      (#) 使用 USART_LINCmd() 函数启用 LIN 模式。
      (#) 使用 USART_SendBreak() 函数发送中断字符。
    [..]
    USART LIN主接收机可以通过以下程序进行通信:
      (#) 使用 USART_Init() 函数编程波特率、字长=8位、停止位=1位、奇偶校验、
            模式发送器或模式接收器以及硬件流控制值。
      (#) 使用 USART_Cmd() 函数启用 USART。
      (#) 使用 USART_LINBreakDetectLengthConfig() 函数配置中断检测长度。
      (#) 使用 USART_LINCmd() 函数启用 LIN 模式。

      -@- 在LIN 模式下，必须清除以下位:
       (+@) USART_CR2寄存器中的 CLKEN，
       (+@) USART_CR3 寄存器中的 STOP[1:0]、SCEN、HDSEL和 IREN。

@endverbatim
  */

/**
  * 简介:  设置 USART LI断检测长度。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_LINBreakDetectLength: 指定 LIN 中断检测长度。
  *          此参数可以是以下值之一:
  *            @arg USART_LINBreakDetectLength_10b: 10位中断检测
  *            @arg USART_LINBreakDetectLength_11b: 11位中断检测
  * 返回值: 无
  */
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_LIN_BREAK_DETECT_LENGTH(USART_LINBreakDetectLength));

    USARTx->CR2 &= (uint16_t)~((uint16_t)USART_CR2_LBDL);
    USARTx->CR2 |= USART_LINBreakDetectLength;
}
N 中
/**
  * 简介:  启用或禁用 USART 的 LIN 模式。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: 新状态-> USART LIN mode.
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过设置 CR2寄存器中的 LINEN 位来启用 LIN 模式 */
        USARTx->CR2 |= USART_CR2_LINEN;
    } else {
        /* 通过清除 CR2寄存器中的 LINEN 位禁用 LIN 模式 */
        USARTx->CR2 &= (uint16_t)~((uint16_t)USART_CR2_LINEN);
    }
}

/**
  * 简介:  传输中断字符。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 返回值: 无
  */
void USART_SendBreak(USART_TypeDef* USARTx) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));

    /* 发送中断字符*/
    USARTx->CR1 |= USART_CR1_SBK;
}


/** @defgroup USART_Group5 半双工模式功能
 *  简介   半双工模式功能
 *
@verbatim
 ===============================================================================
                    ##### 半双工模式功能 #####
 ===============================================================================
    [..]
    本小节提供了一组允许管理 USART 半双工通信的功能。
    [..]
    USART 可以配置为遵循单线半双工协议，其中 TX 和 RX 线在内部连接。
    [..]
    USART 半双工通信可通过以下程序实现:
      (#) 使用 USART_Init() 函数编程波特率、字长、停止位、奇偶校验、
            模式发送器或模式接收器以及硬件流控制值。
      (#) 使用 USART_SetAddress() 函数配置 USART 地址。
      (#) 使用 USART_Cmd() 函数启用 USART。
      (#) 使用 USART_HalfDuplexCmd() 函数启用半双工模式。


    -@- RX 引脚不再使用
    -@- 在半双工模式下，必须清除以下位:
      (+@) USART_CR2寄存器中的 LINEN 和 CLKEN 位。
      (+@) USART_CR3 寄存器中的 SCEN 和 IREN 位。

@endverbatim
  */

/**
  * 简介:  启用或禁用 USART 的半双工通信。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: USART 通信的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过设置 CR3 寄存器中的 HDSEL位，启用半双工模式 */
        USARTx->CR3 |= USART_CR3_HDSEL;
    } else {
        /* 通过清除 CR3 寄存器中的 HDSEL位禁用半双工模式 */
        USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_HDSEL);
    }
}



/** @defgroup USART_Group6 智能卡模式函数
 *  简介   智能卡模式函数
 *
@verbatim
 ===============================================================================
                              ##### 智能卡模式函数 #####
 ===============================================================================
    [..]
    本小节提供了一组允许管理 USART 智能卡通信的功能。
    [..]
    智能卡接口旨在支持ISO 7816-3标准中定义的异步协议智能卡。
    [..]
    USART 可以通过 SCLK 输出为智能卡提供时钟。
    在智能卡模式下，SCLK 与通信无关，只是通过5位预分频器从内部外围输入时钟派生而来。
    [..]
    智能卡通信可以通过以下步骤进行:
      (#) 使用 USART_SetPrescaler() 函数配置智能卡预分频器。
      (#) 使用 USART_SetGuardTime() 函数配置智能卡守卫时间。
      (#) 使用 USART_ClockInit() 函数对 USART 时钟进行编程，如下所示:
        (++) USART 时钟已启用
        (++) USART CPOL低
        (++) USART CPHA位于第一边缘
        (++) USART 最后一位时钟已启用
      (#) 使用 USART_Init() 函数对智能卡接口进行编程，如下所示:
        (++) 字长 = 9位
        (++) 1.5停止位
        (++) 偶数奇偶校验
        (++) 波特率 = 12096 波特率
        (++) 硬件流控制已禁用(RTS 和 CTS信号)
        (++) Tx 和 Rx已启用
      (#) P您可以选择启用奇偶校验错误中断 使用 USART_ITConfig() 函数
      (#) P使用 USART_Cmd() 函数启用 USART。
      (#) P使用 USART_SmartCardNACKCmd() 函数启用智能卡NACK。
      (#) P使用 USART_SmartCardCmd() 函数启用智能卡接口。

    有关更多详细信息，请参阅ISO 7816-3规范。

      -@- 也可以选择0.5个停止位用于接收，
            但建议在发送和接收时使用1.5个停止位，以避免在两种配置之间切换。
      -@- 在智能卡模式下，必须清除以下位:
        (+@) USART_CR2寄存器中的 LINEN 位。
        (+@) USART_CR3 寄存器中的 HDSEL和 IREN 位。
      -@- 智能卡模式仅在 USART 外设设备上可用(在 UART4 和 UART5 外设设备上不可用)。

@endverbatim
  */

/**
  * 简介:  设置指定的 USART 保护时间。
  * 参数:  USARTx: 其中 x 可以是1、2、3或6，以选择 USART 或 UART 外设设备。
  * 参数:  USART_GuardTime: 指定保护时间。
  * 返回值: 无
  */
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime) {
    /* 检查参数 */
    assert_param(IS_USART_1236_PERIPH(USARTx));

    /* 清除 USART警戒时间 */
    USARTx->GTPR &= USART_GTPR_PSC;
    /* 设置 USART警戒时间 */
    USARTx->GTPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

/**
  * 简介:  启用或禁用 USART 的智能卡模式。
  * 参数:  USARTx: 其中 x 可以是1、2、3或6，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: 智能卡模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_1236_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过设置 CR3 寄存器中的 SCEN 位来启用 SC 模式 */
        USARTx->CR3 |= USART_CR3_SCEN;
    } else {
        /* 通过清除 CR3 寄存器中的 SCEN 位禁用 SC 模式 */
        USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_SCEN);
    }
}

/**
  * 简介:  启用或禁用 NACK 传输。
  * 参数:  USARTx: 其中 x 可以是1、2、3或6，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: NACK传输的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_1236_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过设置 CR3 寄存器中的 NACK位来启用 NACK传输 */
        USARTx->CR3 |= USART_CR3_NACK;
    } else {
        /* 通过清除 CR3 寄存器中的 NACK位禁用 NACK传输 */
        USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_NACK);
    }
}


/** @defgroup USART_Group7 IrDA 模式函数
 *  简介   IrDA 模式函数
 *
@verbatim
 ===============================================================================
                        ##### IrDA 模式函数 #####
 ===============================================================================
    [..]
    本小节提供了一组允许管理 USART IrDA 通信的功能。
    [..]
    IrDA是一种半双工通信协议。如果发射机繁忙，IrDA解码器将忽略IrDA 接收线上的任何数据，
        如果接收机繁忙，则IrDA不会对 USART到 IrDA 的 TX数据进行编码。
    在接收数据时，应避免传输，因为要传输的数据可能会损坏。
    [..]
    可以通过以下程序进行IrDA 通信:
      (#) 使用 USART_Init() 函数编程波特率、字长=8位、
            停止位、奇偶校验、发送器/接收器模式和硬件流控制值。
      (#) 使用 USART_Cmd() 函数启用 USART。
      (#) 通过使用 USART_SetPrescaler() 函数配置预分频器来配置IrDA脉冲宽度。
      (#) 使用 USART_IrDAConfig()
            函数配置IrDA USART_IrDAMode_LowPower或 USART_ErDAMode_ Normal模式。
      (#) 使用 USART_IrDACmd() 函数启用 IrDA。

      -@- 宽度小于两个且大于一个PSC周期的脉冲可能会被拒绝，也可能不会被拒绝。
      -@- 接收器设置时间应由软件管理。
            IrDA物理层规范规定传输和接收之间的最小延迟为10毫秒(IrDA是半双工协议)。
      -@- 在 IrDA 模式下，必须清除以下位:
        (+@) USART_CR2寄存器中的 LINEN、STOP 和 CLKEN 位。
        (+@) USART_CR3 寄存器中的 SCEN 和HDSEL位。

@endverbatim
  */

/**
  * 简介:  配置 USART 的 IrDA 接口。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_IrDAMode: 指定 IrDA 模式。
  *          此参数可以是以下值之一:
  *            @arg USART_IrDAMode_LowPower
  *            @arg USART_IrDAMode_Normal
  * 返回值: 无
  */
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_IRDA_MODE(USART_IrDAMode));

    USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_IRLP);
    USARTx->CR3 |= USART_IrDAMode;
}

/**
  * 简介:  启用或禁用 USART 的 IrDA 接口。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  NewState: IrDA 模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过设置 CR3 寄存器中的 IREN 位来启用 IrDA 模式 */
        USARTx->CR3 |= USART_CR3_IREN;
    } else {
        /* 通过清除 CR3 寄存器中的 IREN 位来禁用 IrDA 模式 */
        USARTx->CR3 &= (uint16_t)~((uint16_t)USART_CR3_IREN);
    }
}


/** @defgroup USART_Group8 DMA 传输管理函数
 *  简介   DMA 传输管理 functions
 *
@verbatim
 ===============================================================================
              ##### DMA 传输管理函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用或禁用 USART 的 DMA 接口。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_DMAReq: 指定 DMA 请求。
  *          此参数可以是以下值的任意组合:
  *            @arg USART_DMAReq_Tx: USART DMA 传输请求
  *            @arg USART_DMAReq_Rx: USART DMA 接收请求
  * 参数:  NewState: DMA 请求源的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DMAREQ(USART_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 通过在 USART CR3 寄存器中设置 DMAT和/或 DMAR位，为所选请求启用 DMA 传输 */
        USARTx->CR3 |= USART_DMAReq;
    } else {
        /* 通过清除 USART CR3 寄存器中的 DMAT和/或 DMAR位，禁用所选请求的 DMA 传输 */
        USARTx->CR3 &= (uint16_t)~USART_DMAReq;
    }
}


/** @defgroup USART_Group9 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
            ##### 中断和标记管理函数 #####
 ===============================================================================
    [..]
    本小节提供了一组功能，允许配置 USART 中断源、DMA 信道请求以及检查或清除标志或挂起位状态。
    用户应确定在其应用程序中将使用哪种模式来管理通信:轮询模式、中断模式或 DMA 模式。

    *** 轮询模式 ***
    ====================
    [..]
    在轮询模式下，SPI 通信可以由10个标志管理:
      (#) USART_FLAG_TXE : 指示发送缓冲寄存器的状态
      (#) USART_FLAG_RXNE: 指示接收缓冲寄存器的状态
      (#) USART_FLAG_TC  : 指示传输操作的状态
      (#) USART_FLAG_IDLE: 指示空闲线路的状态
      (#) USART_FLAG_CTS : 指示 nCTS 输入的状态
      (#) USART_FLAG_LBD : 指示 LIN 中断检测的状态
      (#) USART_FLAG_NE  : 指示是否发生噪音错误
      (#) USART_FLAG_FE  : 指示是否发生帧错误
      (#) USART_FLAG_PE  : 指示是否发生奇偶校验错误
      (#) USART_FLAG_ORE : 指示是否发生超限错误
    [..]
    在此模式下，建议使用以下函数:
      (+) FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);
      (+) void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);

    *** 中断模式 ***
    ======================
    [..]
    在中断模式下，USART 通信可由8个中断源和10个待处理位进行管理:

      (#) 挂起的位:

        (##) USART_IT_TXE : 指示发送缓冲寄存器的状态
        (##) USART_IT_RXNE: 指示接收缓冲寄存器的状态
        (##) USART_IT_TC  : 指示传输操作的状态
        (##) USART_IT_IDLE: 指示空闲线路的状态
        (##) USART_IT_CTS : 指示 nCTS 输入的状态
        (##) USART_IT_LBD : 指示 LIN 中断检测的状态
        (##) USART_IT_NE  : 指示是否发生噪音错误
        (##) USART_IT_FE  : 指示是否发生帧错误
        (##) USART_IT_PE  : 指示是否发生奇偶校验错误
        (##) USART_IT_ORE : 指示是否发生超限错误

      (#) 中断源:

        (##) USART_IT_TXE : 指定 Tx 缓冲区空中断的中断源。
        (##) USART_IT_RXNE: 指定 Rx 缓冲区非空中断的中断源。
        (##) USART_IT_TC  : 指定传输完成中断的中断源。
        (##) USART_IT_IDLE: 指定空闲线路中断的中断源。
        (##) USART_IT_CTS : 指定 CTS 中断的中断源。
        (##) USART_IT_LBD : 指定 LIN 中断检测中断的中断源。
        (##) USART_IT_PE  : 指定中断源奇偶校验错误中断.
        (##) USART_IT_ERR : 指定错误中断的中断源。

      -@@- 对一些参数进行编码，以便将其用作中断源或挂起位。
    [..]
    在此模式下，建议使用以下函数:
      (+) void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState);
      (+) ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);
      (+) void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);

    *** DMA Mode ***
    ================
    [..]
    在 DMA 模式下，USART 通信可通过2个 DMA 信道请求进行管理:
      (#) USART_DMAReq_Tx: 指定 Tx 缓冲器 DMA 传输请求
      (#) USART_DMAReq_Rx: 指定 Rx 缓冲器 DMA 传输请求
    [..]
    在此模式下，建议使用以下函数:
      (+) void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState);

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 USART 中断。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_IT: 指定要启用或禁用的 USART 中断源。
  *          此参数可以是以下值之一:
  *            @arg USART_IT_CTS:  CTS 更改中断
  *            @arg USART_IT_LBD:  LIN 中断检测中断
  *            @arg USART_IT_TXE:  传输数据寄存器空中断
  *            @arg USART_IT_TC:   传输完成中断
  *            @arg USART_IT_RXNE: 接收数据寄存器非空中断
  *            @arg USART_IT_IDLE: 空闲线路检测中断
  *            @arg USART_IT_PE:   奇偶校验错误中断
  *            @arg USART_IT_ERR:  错误中断(帧错误、噪声错误、溢出错误)
  * 参数:  NewState: 指定 USARTx 中断的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState) {
    uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
    uint32_t usartxbase = 0x00;
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CONFIG_IT(USART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* CTS 中断不适用于 UART4 和 UART5 */
    if (USART_IT == USART_IT_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }

    usartxbase = (uint32_t)USARTx;

    /* 获取 USART寄存器索引 */
    usartreg = (((uint8_t)USART_IT) >> 0x05);

    /* 获取interrupt position */
    itpos = USART_IT & IT_MASK;
    itmask = (((uint32_t)0x01) << itpos);

    if (usartreg == 0x01) { /* IT在 CR1注册中 */
        usartxbase += 0x0C;
    } else if (usartreg == 0x02) { /* IT在 CR2注册中 */
        usartxbase += 0x10;
    } else { /* IT在 CR3注册中 */
        usartxbase += 0x14;
    }

    if (NewState != DISABLE) {
        *(__IO uint32_t*)usartxbase  |= itmask;
    } else {
        *(__IO uint32_t*)usartxbase &= ~itmask;
    }
}

/**
  * 简介:  检查是否设置了指定的 USART 标志。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg USART_FLAG_CTS:  CTS 更改标志(不适用于 UART4 和 UART5)
  *            @arg USART_FLAG_LBD:  LIN 中断检测标志
  *            @arg USART_FLAG_TXE:  传输数据寄存器为空标志
  *            @arg USART_FLAG_TC:   传输完成标志
  *            @arg USART_FLAG_RXNE: 接收数据寄存器非空标志
  *            @arg USART_FLAG_IDLE: 空闲线路检测标志
  *            @arg USART_FLAG_ORE:  OverRun 错误标志
  *            @arg USART_FLAG_NE:   噪声错误标志
  *            @arg USART_FLAG_FE:   帧错误标志
  *            @arg USART_FLAG_PE:  奇偶校验错误标志
  * 返回值: USART_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_FLAG(USART_FLAG));

    /* CTS标志不适用于 UART4 和 UART5 */
    if (USART_FLAG == USART_FLAG_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }

    if ((USARTx->SR & USART_FLAG) != (uint16_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 USARTx 的挂起标志。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *            @arg USART_FLAG_CTS:  CTS 更改标志(不适用于 UART4 和 UART5)。
  *            @arg USART_FLAG_LBD:  LIN 断开检测标志。
  *            @arg USART_FLAG_TC:   传输完成标志。
  *            @arg USART_FLAG_RXNE: 接收数据寄存器非空标志。
  *
  * 注意:   PE(奇偶校验错误)、FE(帧错误)、NE(噪声错误)、ORE(OverRun 错误)和
  *         IDLE(检测到空闲行)标志按软件顺序清除:先读取 USART_SR 寄存器
  *         (USART_GetFlagStatus())，然后读取 USART_DR 寄存器(USERT_ReceiveData())。
  * 注意:   RXNE 标志也可以通过读取 USART_DR 寄存器(USART_ReceiveData())来清除。
  * 注意:   TC 标志也可以通过软件序列清除:先读取 USART_SR 寄存器(USART_GetFlagStatus())，
  *             然后写入 USART_DR 寄存器(USATT_SendData())。
  * 注意:   TXE 标志只能通过写入 USART_DR 寄存器(USART_SendData())来清除。
  *
  * 返回值: 无
  */
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG) {
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));

    /* CTS标志不适用于 UART4 和 UART5 */
    if ((USART_FLAG & USART_FLAG_CTS) == USART_FLAG_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }

    USARTx->SR = (uint16_t)~USART_FLAG;
}

/**
  * 简介:  检查指定的 USART 中断是否发生。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_IT: 指定要检查的 USART 中断源。
  *          此参数可以是以下值之一:
  *            @arg USART_IT_CTS:  CTS 更改中断(不适用于 UART4 和 UART5)
  *            @arg USART_IT_LBD:  LIN 中断检测中断
  *            @arg USART_IT_TXE:  传输数据寄存器空中断
  *            @arg USART_IT_TC:   传输完成中断
  *            @arg USART_IT_RXNE: 接收数据寄存器非空中断
  *            @arg USART_IT_IDLE: 空闲线路检测中断
  *            @arg USART_IT_ORE_RX : 如果设置了 RXNEIE 位，则 OverRun Error 中断
  *            @arg USART_IT_ORE_ER : 如果设置了 EIE 位，则 OverRun Error 中断
  *            @arg USART_IT_NE:   噪声错误中断
  *            @arg USART_IT_FE:   帧错误中断
  *            @arg USART_IT_PE:   奇偶校验错误中断
  * 返回值: USART_IT 的新状态(SET 或 RESET)。
  */
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT) {
    uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
    ITStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_GET_IT(USART_IT));

    /* CTS 中断不适用于 UART4 和 UART5 */
    if (USART_IT == USART_IT_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }

    /* 获取 USART寄存器索引 */
    usartreg = (((uint8_t)USART_IT) >> 0x05);
    /* 获取中断位置 */
    itmask = USART_IT & IT_MASK;
    itmask = (uint32_t)0x01 << itmask;

    if (usartreg == 0x01) { /* IT在 CR1注册中 */
        itmask &= USARTx->CR1;
    } else if (usartreg == 0x02) { /* IT在 CR2注册中 */
        itmask &= USARTx->CR2;
    } else { /* IT在 CR3注册中 */
        itmask &= USARTx->CR3;
    }

    bitpos = USART_IT >> 0x08;
    bitpos = (uint32_t)0x01 << bitpos;
    bitpos &= USARTx->SR;

    if ((itmask != (uint16_t)RESET) && (bitpos != (uint16_t)RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 USARTx 的中断挂起位。
  * 参数:  USARTx: 其中 x 可以是1、2、3、4、5、6、7 或8，以选择 USART 或 UART 外设设备。
  * 参数:  USART_IT: 指定要清除的中断挂起位。
  *          此参数可以是以下值之一:
  *            @arg USART_IT_CTS:  CTS 更改中断(不适用于 UART4 和 UART5)
  *            @arg USART_IT_LBD:  LIN 中断检测中断
  *            @arg USART_IT_TC:   传输完成中断。
  *            @arg USART_IT_RXNE: 接收数据寄存器非空中断。
  *
  * 注意:   PE(奇偶校验错误)、FE(帧错误)、NE(噪声错误)、ORE(OverRun 错误)和
  *             IDLE(检测到空闲线)挂起的位按软件顺序清除:
  *             先读取 USART_SR 寄存器(USART_GetITStatus())，
  *             然后读取 USART_DR 寄存器(USERT_ReceiveData())
  * 注意:   RXNE 挂起位也可以通过读取 USART_DR 寄存器(USART_ReceiveData())来清除。
  * 注意:   TC 挂起位也可以通过软件序列清除:先读取 USART_SR 寄存器(USART_GetITStatus())，
  *             然后写入 USART_DR 寄存器(USATT_SendData())。
  * 注意:   TXE 挂起位仅通过写入 USART_DR 寄存器(USART_SendData())来清除。
  *
  * 返回值: 无
  */
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT) {
    uint16_t bitpos = 0x00, itmask = 0x00;
    /* 检查参数 */
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_IT(USART_IT));

    /* CTS 中断不适用于 UART4 和 UART5 */
    if (USART_IT == USART_IT_CTS) {
        assert_param(IS_USART_1236_PERIPH(USARTx));
    }

    bitpos = USART_IT >> 0x08;
    itmask = ((uint16_t)0x01 << (uint16_t)bitpos);
    USARTx->SR = (uint16_t)~itmask;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
