
/**
  ******************************************************************************
  * 文件:    stm32f4xx_cec.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能来管理仅适用于
				STM32F446xx 器件的消费电子控制 (CEC) 外设的以下函数:
  *            + 初始化和配置
  *            + 数据传送函数
  *            + 中断和标志管理
  *
  *  @verbatim
  ==============================================================================
                            ##### CEC 特点 #####
  ==============================================================================
      [..] 该设备提供了一些功能:
           (#) 支持 HDMI-CEC 规范 1.4。

           (#) 支持两个源时钟(HSI/244 或 LSE)。
           (#) 在停止模式下工作(没有 APB 时钟，但有 CEC 时钟 32KHz)。
               它可以在 CPU 从低功耗模式唤醒的 CEC 时钟域中产生中断。

           (#) 传输开始前可配置的信号空闲时间。
			   传输前等待的标称数据位周期数可以由硬件或软件决定。

           (#) 可配置外设地址(多地址配置)。

           (#) 支持监听模式。启用监听模式选项后，
		       可以在不干扰 CEC 总线的情况下接收发往不同目的地的 CEC 消息。

           (#) 可配置的 Rx-Tolerance(标准和扩展容差余量)。

           (#) 带有可配置错误位生成的错误检测。

           (#) 两个CEC设备同时启动的情况下仲裁丢失错误。

                            ##### 如何使用此驱动程序 #####
  ==============================================================================
      [..] 此驱动程序提供配置和编程 CEC 设备的功能，请按照以下步骤操作:
           (#) 可以使用以下方式配置源时钟:
               (++) RCC_CECCLKConfig(RCC_CECCLK_HSI_Div244) for HSI(Default)
               (++) RCC_CECCLKConfig(RCC_CECCLK_LSE) for LSE.

           (#) 使用 RCC_APBPeriphClockCmd(RCC_APBPeriph_CEC, ENABLE) 启用 CEC 外设时钟。

           (#) 外设交替函数。
               (++) 使用 GPIO_PinAFConfig() 函数将引脚连接到所需外设的备用函数 (AF)。
               (++) 通过在备用函数中配置所需的引脚:
					          GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
               (++) 通过 GPIO_OType 和 GPIO_Speed 成员选择开漏类型和输出速度。
               (++) 调用 GPIO_Init() 函数。

           (#) 使用 CEC_Init() 函数配置信号空闲时间、Rx 容限、停止接收生成和误码生成。
                当 CEC 外设被禁用时，必须调用函数 CEC_Init()。

           (#) 通过调用函数 CEC_OwnAddressConfig() 配置 CEC 自己的地址。

           (#) 或者，您可以使用函数 CEC_ListenModeCmd() 配置监听模式。

           (#) 如果需要使用中断模式，请使用函数 CEC_ITConfig() 启用 NVIC 和相应的中断。
               在启用 CEC 外设之前必须调用 CEC_ITConfig()。

           (#) 使用 CEC_Cmd() 函数启用 CEC。

           (#) 使用 CEC_SendDataByte() 对 TXDR 寄存器中的第一个数据字节进行充电。

           (#) 使用 CEC_StartOfMessage() 启用 CEC 消息字节的传输

           (#) 使用 CEC_SendDataByte() 通过 CEC 外设传输单个数据，并使用 CEC_ReceiveDataByte() 接收最后传输的字节。

           (#) 启用 CEC_EndOfMessage() 以指示消息的最后一个字节。
      [..]
           (@) 如果启用监听模式，停止接收生成和误码生成必须处于复位状态。
           (@) 如果 CEC 消息仅包含 1 个字节，则必须在 CEC_StartOfMessage() 之前调用函数 CEC_EndOfMessage()。

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
#include "stm32f4xx_cec.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup CEC
  * 简介: CEC 驱动模块
  */
#if defined(STM32F446xx)
/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define BROADCAST_ADDRESS      ((uint32_t)0x0000F)
#define CFGR_CLEAR_MASK        ((uint32_t)0x7000FE00)   /* CFGR 寄存器掩码 */

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup CEC_Private_Functions
  */

/** @defgroup CEC_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
                            ##### 初始化和配置函数 #####
 ===============================================================================
      [..] 本节提供允许初始化的函数:
            (+) CEC 自己的地址
            (+) CEC 信号自由时间
            (+) CEC Rx Tolerance
            (+) CEC 停止接收
            (+) CEC 比特上升误差
            (+) CEC 长比特周期误差

      [..] 本节还提供了在侦听模式下配置 CEC 外设的功能。
            启用侦听模式后，可以接收发往不同目的地的消息，而不会干扰 CEC 总线。
@endverbatim
  */

/**
  * 简介:  用于将 CEC 配置设置为默认复位状态的函数

  * 参数:  无
  
  * 返回值: 无
  */
void CEC_DeInit(void) {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, DISABLE);
}

/**
  * 简介:  根据 CEC_InitStruct 中指定的参数，初始化 CEC 外设设备。
  * 
  * 注意:   在启用 CEC 外设之前，必须先配置 CEC参数。
  * 
  * 参数:  CEC_InitStruct: 指向一个CEC_InitTypeDef 结构的指针，
  *                        该结构包含了 该结构包含指定CEC 外设的配置信息。
  * 
  * 返回值: 无
  */
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_CEC_SIGNAL_FREE_TIME(CEC_InitStruct->CEC_SignalFreeTime));
    assert_param(IS_CEC_RX_TOLERANCE(CEC_InitStruct->CEC_RxTolerance));
    assert_param(IS_CEC_STOP_RECEPTION(CEC_InitStruct->CEC_StopReception));
    assert_param(IS_CEC_BIT_RISING_ERROR(CEC_InitStruct->CEC_BitRisingError));
    assert_param(IS_CEC_LONG_BIT_PERIOD_ERROR(CEC_InitStruct->CEC_LongBitPeriodError));
    assert_param(IS_CEC_BDR_NO_GEN_ERROR(CEC_InitStruct->CEC_BRDNoGen));
    assert_param(IS_CEC_SFT_OPTION(CEC_InitStruct->CEC_SFTOption));

    /* 获取CEC CFGR 值 */
    tmpreg = CEC->CFGR;

    /* 清除 CFGR 位 */
    tmpreg &= CFGR_CLEAR_MASK;

    /* 配置 CEC 外设 */
    tmpreg |= (CEC_InitStruct->CEC_SignalFreeTime | CEC_InitStruct->CEC_RxTolerance |
               CEC_InitStruct->CEC_StopReception  | CEC_InitStruct->CEC_BitRisingError |
               CEC_InitStruct->CEC_LongBitPeriodError | CEC_InitStruct->CEC_BRDNoGen |
               CEC_InitStruct->CEC_SFTOption);

    /* 写入CEC CFGR  寄存器 */
    CEC->CFGR = tmpreg;
}

/**
  * 简介:  用默认值填充每个CEC_InitStruct 成员。
  * 
  * 参数:  CEC_InitStruct: 指向CEC_InitTypeDef 结构的指针，将被初始化。
  * 
  * 返回值: 无
  */
void CEC_StructInit(CEC_InitTypeDef* CEC_InitStruct) {
    CEC_InitStruct->CEC_SignalFreeTime = CEC_SignalFreeTime_Standard;
    CEC_InitStruct->CEC_RxTolerance = CEC_RxTolerance_Standard;
    CEC_InitStruct->CEC_StopReception = CEC_StopReception_Off;
    CEC_InitStruct->CEC_BitRisingError = CEC_BitRisingError_Off;
    CEC_InitStruct->CEC_LongBitPeriodError = CEC_LongBitPeriodError_Off;
    CEC_InitStruct->CEC_BRDNoGen = CEC_BRDNoGen_Off;
    CEC_InitStruct->CEC_SFTOption = CEC_SFTOption_Off;
}

/**
  * 简介:  启用或禁用 CEC 外设设备。
  * 
  * 参数:  NewState: CEC 外设的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void CEC_Cmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 CEC 外设 */
        CEC->CR |= CEC_CR_CECEN;
    } else {
        /* 禁用 CEC 外设 */
        CEC->CR &= ~CEC_CR_CECEN;
    }
}

/**
  * 简介:  启用或禁用 CEC侦听模式。
  * 
  * 参数:  NewState: 侦听模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void CEC_ListenModeCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用监听模式 */
        CEC->CFGR |= CEC_CFGR_LSTN;
    } else {
        /* 禁用监听模式 */
        CEC->CFGR &= ~CEC_CFGR_LSTN;
    }
}

/**
  * 简介:  定义CEC设备的自有地址。
  * 
  * 参数:  CEC_OwnAddress: CEC自己的地址。
  * 
  * 返回值: 无
  */
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress) {
    uint32_t tmp = 0x00;
    /* 检查参数 */
    assert_param(IS_CEC_ADDRESS(CEC_OwnAddress));
    tmp = 1 << (CEC_OwnAddress + 16);
    /* 设置 CEC 自己的地址 */
    CEC->CFGR |= tmp;
}

/**
  * 简介:  清除 CEC设备的自有地址。
  * 
  * 参数:  CEC_OwnAddress:CEC自己的地址。
  * 
  * 返回值: 无
  */
void CEC_OwnAddressClear(void) {
    /* 设置 CEC 自己的地址 */
    CEC->CFGR = 0x0;
}


/** @defgroup CEC_Group2 数据传输函数
 *  简介    数据传输函数
 *
@verbatim
 ===============================================================================
                            ##### 数据传输函数 #####
 ===============================================================================
    [..] 本节提供了允许CEC 数据传输的功能。CEC_RXDR 寄存器的读取访问可以使用
         CEC_ReceiveData() 函数完成，并返回 Rx缓冲值。
         而对CEC_TXDR 的写访问可以使用 CEC_SendData() 函数完成。
@endverbatim
  */

/**
  * 简介:  Transmits single data through the CEC 外设.
  * 
  * 参数:  Data: 要传输的数据。
  * 返回值: 无
  */
void CEC_SendData(uint8_t Data) {
    /* 传输数据 */
    CEC->TXDR = Data;
}

/**
  * 简介:  返回CEC 外设设备最近接收的数据。
  * 
  * 参数:  无
  * 
  * 返回值: 接收的数据。
  */
uint8_t CEC_ReceiveData(void) {
    /* 接收数据 */
    return (uint8_t)(CEC->RXDR);
}

/**
  * 简介:  启动新消息
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void CEC_StartOfMessage(void) {
    /* 新消息的开头 */
    CEC->CR |= CEC_CR_TXSOM;
}

/**
  * 简介:  用EOM位传输消息。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void CEC_EndOfMessage(void) {
    /* 数据字节将与EOM一起传输位*/
    CEC->CR |= CEC_CR_TXEOM;
}


/** @defgroup CEC_Group3 中断和标记管理函数
 *  简介    中断和标记管理函数
*
@verbatim
 ===============================================================================
                            ##### 中断和标记管理函数 #####
 ===============================================================================
    [..] 本节提供的功能允许 配置 CEC中断源，并检查或清除标志或挂起位状态。
    [..] 用户应确定在其应用程序中将使用哪种模式来管理通信:轮询模式或中断模式。

    [..] 在轮询模式下，CEC可以通过以下标志进行管理:
            (+) CEC_FLAG_TXACKE : 表示在传输模式下有一个丢失的确认。
            (+) CEC_FLAG_TXERR :  表示在传输模式中发生错误。
                                  启动器检测到 CEC线路的低阻抗。
            (+) CEC_FLAG_TXUDR :  指示在传输模式下是否发生了欠运行错误。
                                  当软件还没有将任何数值加载到 TXDR 寄存器时，传输被启用。启用时，软件尚未将任何数值加载到 TXDR 寄存器中。
            (+) CEC_FLAG_TXEND :  指示成功传输的结束。
            (+) CEC_FLAG_TXBR :   指示下一个传输数据必须写入TXDR。
            (+) CEC_FLAG_ARBLST : 在两个CEC设备同时启动的情况下表示仲裁失败。同时启动的情况下，表示仲裁失败。
            (+) CEC_FLAG_RXACKE : 表示在接收模式下缺少确认。
            (+) CEC_FLAG_LBPE :   指示在接收模式下产生的长比特周期错误。
            (+) CEC_FLAG_SBPE :   指示在接收模式下产生的短比特周期错误。
            (+) CEC_FLAG_BRE :    表示在接收模式下产生的一个位上升错误。
            (+) CEC_FLAG_RXOVR :  指示是否在接收CEC信息时发生超限错误。
                                  在RXDR 寄存器中存储一个新的字节时，尚未收到一个字节。
            (+) CEC_FLAG_RXEND :  指示是否发生超限错误。
            (+) CEC_FLAG_RXBR :   表示已经从CEC线路上收到一个新的字节，并存储到RXDR 缓冲器中。
    [..]
           (@)在这种模式下，建议使用以下函数:
              FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG);
              void CEC_ClearFlag(uint16_t CEC_FLAG);

    [..] 在中断模式下，CEC可通过以下中断源进行管理:
           (+)CEC_IT_TXACKE :   表示一个 TX缺失确认。
           (+) CEC_IT_TXACKE :  表示在传输模式下的确认丢失。
           (+) CEC_IT_TXERR :   表示在传输模式中发生错误。
                                启动器检测到 CEC线路的低阻抗。
           (+) CEC_IT_TXUDR :   表示在传输模式下发生了欠载错误。
                                当软件还没有将任何数值加载到 TXDR 寄存器时，传输被启用。
                                启用时，软件尚未将任何数值加载到 TXDR 寄存器中。
           (+) CEC_IT_TXEND :   表示传输成功结束。
           (+) CEC_IT_TXBR :    指示下一个传输数据必须写入TXDR 寄存器。
           (+) CEC_IT_ARBLST :  在两个CEC设备同时启动的情况下表示仲裁失败。
           (+) CEC_IT_ARBLST :  在两个CEC设备同时启动的情况下，表示仲裁失败。
           (+) CEC_IT_RXACKE :  表示在接收模式下的确认丢失。
           (+) CEC_IT_LBPE :    指示在接收模式下产生的长比特周期错误。
           (+) CEC_IT_SBPE :    指示在接收模式下产生的短比特周期错误。
           (+) CEC_IT_BRE :     表示在接收模式下产生的一个位上升错误。
           (+) CEC_IT_RXOVR :   指示在接收CEC信息时是否发生超限错误。
                                在RXDR 寄存器中存储一个新的字节时，尚未收到一个字节。
           (+) CEC_IT_RXEND :   表示接收结束。
           (+) CEC_IT_RXBR :    表示已经从CEC线路接收到一个新的字节，并存储到RXDR 缓冲器。
    [..]
           (@)在这种模式下，建议使用以下函数:
              void CEC_ITConfig( uint16_t CEC_IT, FunctionalState NewState);
              ITStatus CEC_GetITStatus(uint16_t CEC_IT);
              void CEC_ClearITPendingBit(uint16_t CEC_IT);


@endverbatim
  */

/**
  * 简介:  启用或禁用选定的 CEC中断。
  * 
  * 参数:  CEC_IT: 指定要启用的 CEC中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg CEC_IT_TXACKE:  Tx缺失确认错误。
  *            @arg CEC_IT_TXERR:   Tx错误。
  *            @arg CEC_IT_TXUDR:   Tx缓冲区不足。
  *            @arg CEC_IT_TXEND:   传输结束(成功传输最后一个字节)。
  *            @arg CEC_IT_TXBR:    Tx字节请求。
  *            @arg CEC_IT_ARBLST:  仲裁丢失.
  *            @arg CEC_IT_RXACKE:  Rx缺少确认.
  *            @arg CEC_IT_LBPE:    Rx长周期错误.
  *            @arg CEC_IT_SBPE:    Rx短周期错误
  *            @arg CEC_IT_BRE:     Rx 位上升错误
  *            @arg CEC_IT_RXOVR:   Rx超限。
  *            @arg CEC_IT_RXEND:   接收结束
  *            @arg CEC_IT_RXBR:    接收的 Rx字节
  * 
  * 参数:  NewState: 选定的 CEC中断的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void CEC_ITConfig(uint16_t CEC_IT, FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_CEC_IT(CEC_IT));

    if (NewState != DISABLE) {
        /* 启用所选CEC中断 */
        CEC->IER |= CEC_IT;
    } else {
        CEC_IT = ~CEC_IT;
        /* 禁用用所选CEC中断 */
        CEC->IER &= CEC_IT;
    }
}

/**
  * 简介:  获取CEC 标志状态。
  * 
  * 参数:  CEC_FLAG: 指定要检查的 CEC 标志。
  *     此参数可以是以下值之一:
  *            @arg CEC_FLAG_TXACKE: Tx缺失确认错误。
  *            @arg CEC_FLAG_TXERR:  Tx错误。
  *            @arg CEC_FLAG_TXUDR:  Tx缓冲区不足。
  *            @arg CEC_FLAG_TXEND:  传输结束(成功传输最后一个字节)。
  *            @arg CEC_FLAG_TXBR:   Tx字节请求。
  *            @arg CEC_FLAG_ARBLST: 仲裁丢失.
  *            @arg CEC_FLAG_RXACKE: Rx缺少确认.
  *            @arg CEC_FLAG_LBPE:   Rx长周期错误.
  *            @arg CEC_FLAG_SBPE:   Rx短周期错误
  *            @arg CEC_FLAG_BRE:    Rx 位上升错误
  *            @arg CEC_FLAG_RXOVR:  Rx超限。
  *            @arg CEC_FLAG_RXEND:  接收结束.
  *            @arg CEC_FLAG_RXBR:   接收的 Rx字节.
  * 
  * 返回值: CEC_FLAG 的新状态(SET 或 RESET)
  */
FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG) {
    FlagStatus bitstatus = RESET;

    assert_param(IS_CEC_GET_FLAG(CEC_FLAG));

    /* 检查 指定CEC 标志的状态 */
    if ((CEC->ISR & CEC_FLAG) != (uint16_t)RESET) {
        /* 设置了CEC 标志 */
        bitstatus = SET;
    } else {
        /* CEC 标志复位 */
        bitstatus = RESET;
    }

    /* 返回CEC 标志状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 CEC 的挂起标志。
  * 
  * 参数:  CEC_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *            @arg CEC_FLAG_TXACKE: Tx缺失确认错误。
  *            @arg CEC_FLAG_TXERR:  Tx 错误
  *            @arg CEC_FLAG_TXUDR:  Tx缓冲区不足。
  *            @arg CEC_FLAG_TXEND:  传输结束(成功传输最后一个字节)。
  *            @arg CEC_FLAG_TXBR:   Tx字节请求
  *            @arg CEC_FLAG_ARBLST: 仲裁丢失.
  *            @arg CEC_FLAG_RXACKE: Rx缺少确认
  *            @arg CEC_FLAG_LBPE:   Rx长周期错误.
  *            @arg CEC_FLAG_SBPE:   Rx短周期错误
  *            @arg CEC_FLAG_BRE:    Rx 位上升错误
  *            @arg CEC_FLAG_RXOVR:  Rx超限
  *            @arg CEC_FLAG_RXEND:  接收结束
  *            @arg CEC_FLAG_RXBR:   接收的 Rx字节
  * 
  * 返回值: 无
  */
void CEC_ClearFlag(uint32_t CEC_FLAG) {
    assert_param(IS_CEC_CLEAR_FLAG(CEC_FLAG));

    /* 清除 所选CEC 标志 */
    CEC->ISR = CEC_FLAG;
}

/**
  * 简介:  检查指定的 CEC中断是否已发生。
  * 
  * 参数:  CEC_IT: 指定要检查的 CEC中断源。
  *          此参数可以是以下值之一:
  *            @arg CEC_IT_TXACKE: Tx缺失确认错误。
  *            @arg CEC_IT_TXERR:  Tx错误。
  *            @arg CEC_IT_TXUDR:  Tx缓冲区不足。
  *            @arg CEC_IT_TXEND:  传输结束(成功传输最后一个字节)。
  *            @arg CEC_IT_TXBR:   Tx字节请求。
  *            @arg CEC_IT_ARBLST: 仲裁丢失..
  *            @arg CEC_IT_RXACKE: Rx缺少确认..
  *            @arg CEC_IT_LBPE:   Rx长周期错误..
  *            @arg CEC_IT_SBPE:   Rx短周期错误.
  *            @arg CEC_IT_BRE:    Rx 位上升错误.
  *            @arg CEC_IT_RXOVR:  Rx超限。
  *            @arg CEC_IT_RXEND:  接收结束.
  *            @arg CEC_IT_RXBR:   接收的 Rx字节
  * 
  * 返回值: CEC_IT 的新状态(SET 或 RESET)。
  */
ITStatus CEC_GetITStatus(uint16_t CEC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_CEC_GET_IT(CEC_IT));

    /* 获取CEC IT enable bit 状态 */
    enablestatus = (CEC->IER & CEC_IT);

    /* 检查 the status of the specified CEC 中断 */
    if (((CEC->ISR & CEC_IT) != (uint32_t)RESET) && enablestatus) {
        /* CEC interrupt 被设置 */
        bitstatus = SET;
    } else {
        /* CEC interrupt  被重置 */
        bitstatus = RESET;
    }

    /* 返回CEC中断状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 CEC 的中断挂起位。
  * 
  * 参数:  CEC_IT: 指定要清除的 CEC中断挂起位。
  *          此参数可以是以下值的任意组合:
  *            @arg CEC_IT_TXACKE: Tx缺失确认错误。
  *            @arg CEC_IT_TXERR:  Tx 错误
  *            @arg CEC_IT_TXUDR:  Tx缓冲区不足。
  *            @arg CEC_IT_TXEND:  传输结束
  *            @arg CEC_IT_TXBR:   Tx字节请求
  *            @arg CEC_IT_ARBLST: 仲裁丢失.
  *            @arg CEC_IT_RXACKE: Rx缺少确认.
  *            @arg CEC_IT_LBPE:   Rx长周期错误.
  *            @arg CEC_IT_SBPE:   Rx短周期错误
  *            @arg CEC_IT_BRE:    Rx 位上升错误
  *            @arg CEC_IT_RXOVR:  Rx超限
  *            @arg CEC_IT_RXEND:  接收结束
  *            @arg CEC_IT_RXBR:   接收的 Rx字节
  * 
  * 返回值: 无
  */
void CEC_ClearITPendingBit(uint16_t CEC_IT) {
    assert_param(IS_CEC_IT(CEC_IT));

    /* 清除所选CEC中断挂起位 */
    CEC->ISR = CEC_IT;
}


#endif /* STM32F446xx */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
