/**
  ******************************************************************************
  * 文件:    stm32f4xx_spdifrx.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，用于管理串行音频接口(SPDIFRX)的以下函数:
  *           + 初始化和函数
  *           + 数据传输函数
  *           + DMA传输管理
  *           + 中断和标志管理
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
#include "stm32f4xx_spdifrx.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup SPDIFRX
  * 简介: SPDIFRX驱动模块
  * @{
  */
#if defined(STM32F446xx)
/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define CR_CLEAR_MASK 0x000000FE7
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup SPDIFRX_Private_Functions
  * @{
  */

/** @defgroup SPDIFRX_Group1 初始化和配置函数
  *  简介   初始化和配置函数
  *
@verbatim
 ===============================================================================
            ##### 初始化和配置函数 #####
 ===============================================================================
  [..]
  本节提供了一组允许初始化SPDIFRX音频的函数

  块模式、音频协议、数据大小、音频块之间的同步、主时钟分频器、
  FIFO阈值、帧配置、插槽配置、三态模式、压缩模式和静音模式。
  [..]
  SPDIFRX_Init()、SPDIFRX_FrameInit()和SPDIFRX块配置程序遵循主模式和从模式的SPDIFRX块配置程序(有关这些程序的详细信息，请参阅参考手册(RMxxxx))。

@endverbatim
  * @{
  */

/**
  * 简介:  将SPDIFRXx外围寄存器取消初始化为其默认重置值。
  * 参数:  void
  * 返回值: 无
  */
void SPDIFRX_DeInit(void) {
    /* 使能SPDIFRX 复位状态 */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPDIFRX, ENABLE);
    /* 释放SPDIFRX from 复位状态 */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPDIFRX, DISABLE);
}

/**
  * 简介:  根据 SPDIFRX_InitStruct 中指定的参数初始化 SPDIFRX 外设。
  *
  * 注意:   SPDIFRX时钟由PLLSPDIFRX的特定输出或PLLI2S的特定输出或绕过PLLI2S的替代函数生成。
  *
  * 参数:  SPDIFRX_InitStruct: 指向SPDIFRX_InitTypeDef结构的指针，该结构包含指定SPDIFRX块外设设备的配置信息。
  * 返回值: 无
  */
void SPDIFRX_Init(SPDIFRX_InitTypeDef* SPDIFRX_InitStruct) {
    uint32_t tmpreg = 0;

    /* 检查 the SPDIFRX 参数 */
    assert_param(IS_STEREO_MODE(SPDIFRX_InitStruct->SPDIFRX_StereoMode));
    assert_param(IS_SPDIFRX_INPUT_SELECT(SPDIFRX_InitStruct->SPDIFRX_InputSelection));
    assert_param(IS_SPDIFRX_MAX_RETRIES(SPDIFRX_InitStruct->SPDIFRX_Retries));
    assert_param(IS_SPDIFRX_WAIT_FOR_ACTIVITY(SPDIFRX_InitStruct->SPDIFRX_WaitForActivity));
    assert_param(IS_SPDIFRX_CHANNEL(SPDIFRX_InitStruct->SPDIFRX_ChannelSelection));
    assert_param(IS_SPDIFRX_DATA_FORMAT(SPDIFRX_InitStruct->SPDIFRX_DataFormat));

    /* SPDIFRX CR 配置*/
    /* 获取SPDIFRX CR 值 */
    tmpreg = SPDIFRX->CR;
    /* 清除 INSEL, WFA, NBTR, CHSEL, DRFMT and RXSTEO 位 */
    tmpreg &= CR_CLEAR_MASK;
    /* Configure SPDIFRX: Input selection, Maximum allowed re-tries during synchronization phase,
    wait for activity, Channel Selection, Data samples format and stereo/mono mode */
    /* 设置 INSEL bits 根据 SPDIFRX_InputSelection 值   */
    /* 设置 WFA   bit  根据 SPDIFRX_WaitForActivity 值  */
    /* 设置 NBTR  bit  根据 SPDIFRX_Retries 值          */
    /* 设置 CHSEL bit  根据 SPDIFRX_ChannelSelection 值 */
    /* 设置 DRFMT bits 根据 SPDIFRX_DataFormat 值       */
    /* 设置 RXSTEO bit 根据 SPDIFRX_StereoMode 值       */

    tmpreg |= (uint32_t)(SPDIFRX_InitStruct->SPDIFRX_InputSelection   | SPDIFRX_InitStruct->SPDIFRX_WaitForActivity   |
                         SPDIFRX_InitStruct->SPDIFRX_Retries          | SPDIFRX_InitStruct->SPDIFRX_ChannelSelection  |
                         SPDIFRX_InitStruct->SPDIFRX_DataFormat       | SPDIFRX_InitStruct->SPDIFRX_StereoMode
                        );

    /* 写入SPDIFRX CR */
    SPDIFRX->CR = tmpreg;
}

/**
  * 简介:  用默认值填充每个 SPDIFRX_InitStruct 成员。
  * 参数:  SPDIFRX_InitStruct: 指向将被初始化的 SPDIFRX_InitTypeDef 结构的指针。
  * 返回值: 无
  */
void SPDIFRX_StructInit(SPDIFRX_InitTypeDef* SPDIFRX_InitStruct) {
    /* Reset SPDIFRX init structure parameters values */
    /* 初始化 PDIF_InputSelection 成员 */
    SPDIFRX_InitStruct->SPDIFRX_InputSelection = SPDIFRX_Input_IN0;
    /* 初始化 SPDIFRX_WaitForActivity 成员 */
    SPDIFRX_InitStruct->SPDIFRX_WaitForActivity = SPDIFRX_WaitForActivity_On;
    /* 初始化 SPDIFRX_Retries 成员 */
    SPDIFRX_InitStruct->SPDIFRX_Retries = SPDIFRX_16MAX_RETRIES;
    /* 初始化 SPDIFRX_ChannelSelection 成员 */
    SPDIFRX_InitStruct->SPDIFRX_ChannelSelection = SPDIFRX_Select_Channel_A;
    /* 初始化 SPDIFRX_DataFormat 成员 */
    SPDIFRX_InitStruct->SPDIFRX_DataFormat = SPDIFRX_MSB_DataFormat;
    /* 初始化 SPDIFRX_StereoMode 成员 */
    SPDIFRX_InitStruct->SPDIFRX_StereoMode = SPDIFRX_StereoMode_Enabled;
}

/**
  * 简介:  启用或禁用SPDIFRX frame x bit.
  * 参数:  NewState: 选定SPDIFRX帧位的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPDIFRX_SetPreambleTypeBit(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 SPDIFRX frame 位 */
        SPDIFRX->CR |= SPDIFRX_CR_PTMSK;
    } else {
        /* 禁用被选中的 SPDIFRX frame 位 */
        SPDIFRX->CR &= ~(SPDIFRX_CR_PTMSK);
    }
}

/**
  * 简介:  启用或禁用SPDIFRX frame x bit.
  * 参数:  NewState: 选定SPDIFRX帧位的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPDIFRX_SetUserDataChannelStatusBits(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 SPDIFRX frame 位 */
        SPDIFRX->CR |= SPDIFRX_CR_CUMSK;
    } else {
        /* 禁用被选中的 SPDIFRX frame 位 */
        SPDIFRX->CR &= ~(SPDIFRX_CR_CUMSK);
    }
}

/**
  * 简介:  启用或禁用 SPDIFRX 帧 x 位。
  * 参数:  NewState: 选定SPDIFRX帧位的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPDIFRX_SetValidityBit(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 SPDIFRX frame 位 */
        SPDIFRX->CR |= SPDIFRX_CR_VMSK;
    } else {
        /* 禁用被选中的 SPDIFRX frame 位 */
        SPDIFRX->CR &= ~(SPDIFRX_CR_VMSK);
    }
}

/**
  * 简介:  启用或禁用 SPDIFRX 帧 x 位。
  * 参数:  NewState: 选定SPDIFRX帧位的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPDIFRX_SetParityBit(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的SPDIFRX帧位 */
        SPDIFRX->CR |= SPDIFRX_CR_PMSK;
    } else {
        /* 禁用选定的SPDIFRX帧位 */
        SPDIFRX->CR &= ~(SPDIFRX_CR_PMSK);
    }
}

/**
  * 简介:  启用或禁用 SPDIFRX DMA 接口 (RX)。
  * 参数:  NewState: 所选SPDIFRX DMA传输请求的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPDIFRX_RxDMACmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的SPDIFRX DMA请求 */
        SPDIFRX->CR |= SPDIFRX_CR_RXDMAEN;
    } else {
        /* 禁用选定的SPDIFRX DMA请求 */
        SPDIFRX->CR &= ~(SPDIFRX_CR_RXDMAEN);
    }
}

/**
  * 简介:  启用或禁用 SPDIFRX DMA 接口(控制缓冲区)。
  * 参数:  NewState: 所选SPDIFRX DMA传输请求的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPDIFRX_CbDMACmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的SPDIFRX DMA请求 */
        SPDIFRX->CR |= SPDIFRX_CR_CBDMAEN;
    } else {
        /* 禁用选定的SPDIFRX DMA请求 */
        SPDIFRX->CR &= ~(SPDIFRX_CR_CBDMAEN);
    }
}

/**
  * 简介:  启用或禁用 SPDIFRX 外设。
  * 参数:  SPDIFRX_State: 指定SPDIFRX外设设备状态。
  *          此参数可以是以下值之一:
  *            @arg SPDIFRX_STATE_IDLE : Disable SPDIFRX-RX (STATE_IDLE)
  *            @arg SPDIFRX_STATE_SYNC : Enable SPDIFRX-RX Synchronization only
  *            @arg SPDIFRX_STATE_RCV  : Enable SPDIFRX Receiver
  * 返回值: 无
  */
void SPDIFRX_Cmd(uint32_t SPDIFRX_State) {
    /* 检查参数 */
    assert_param(IS_SPDIFRX_STATE(SPDIFRX_State));

    /* 清除 SPDIFRXEN 位 */
    SPDIFRX->CR &= ~(SPDIFRX_CR_SPDIFEN);
    /* Set new SPDIFRXEN 值 */
    SPDIFRX->CR |= SPDIFRX_State;
}

/**
  * 简介:  启用或禁用指定的 SPDIFRX 块中断。
  * 
  * 参数:  SPDIFRX_IT: 指定要启用或禁用的SPDIFRX中断源。
  *          此参数可以是以下值之一:
  *            @arg SPDIFRX_IT_RXNE:  RXNE中断启用
  *            @arg SPDIFRX_IT_CSRNE: 控制缓冲就绪中断启用
  *            @arg SPDIFRX_IT_PERRIE: 奇偶校验错误中断 enable
  *            @arg SPDIFRX_IT_OVRIE:  溢出错误中断启用
  *            @arg SPDIFRX_IT_SBLKIE: 同步块检测到中断启用
  *            @arg SPDIFRX_IT_SYNCDIE: 同步完成
  *            @arg SPDIFRX_IT_IFEIE: 串行接口错误中断启用
  * 
  * 参数:  NewState: 新状态-> 指定的 SPDIFRX 中断。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void SPDIFRX_ITConfig(uint32_t SPDIFRX_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPDIFRX_CONFIG_IT(SPDIFRX_IT));

    if (NewState != DISABLE) {
        /* 启用选定的SPDIFRX中断 */
        SPDIFRX->IMR |= SPDIFRX_IT;
    } else {
        /* 禁用选定的SPDIFRX中断 */
        SPDIFRX->IMR &= ~(SPDIFRX_IT);
    }
}

/**
  * 简介:  检查是否设置了指定的SPDIFRX标志。
  * 参数:  SPDIFRX_FLAG: 指定要检查的SPDIFRX标志。
  *          此参数可以是以下值之一:
  *            @arg SPDIFRX_FLAG_RXNE: 读取数据寄存器非空标志。
  *            @arg SPDIFRX_FLAG_CSRNE: 控制缓冲寄存器非空标志。
  *            @arg SPDIFRX_FLAG_PERR: 奇偶校验错误标志。
  *            @arg SPDIFRX_FLAG_OVR: 溢出错误标志。
  *            @arg SPDIFRX_FLAG_SBD: 检测到同步块标志。
  *            @arg SPDIFRX_FLAG_SYNCD: 同步完成 flag.
  *            @arg SPDIFRX_FLAG_FERR: 帧错误标志。
  *            @arg SPDIFRX_FLAG_SERR: 同步错误标志。
  *            @arg SPDIFRX_FLAG_TERR: 超时错误标志。
  * 返回值: 新状态-> SPDIFRX_FLAG (SET or RESET).
  */
FlagStatus SPDIFRX_GetFlagStatus(uint32_t SPDIFRX_FLAG) {
    FlagStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_SPDIFRX_FLAG(SPDIFRX_FLAG));

    /* 检查 the status of the specified SPDIFRX flag */
    if ((SPDIFRX->SR & SPDIFRX_FLAG) != (uint32_t)RESET) {
        /* SPDIFRX_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* SPDIFRX_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回SPDIFRX_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除指定的 SPDIFRX 标志。
  * 参数:  SPDIFRX_FLAG: 指定要检查的SPDIFRX标志。
  *          此参数可以是以下值之一:
  *            @arg SPDIFRX_FLAG_PERR: 奇偶校验错误标志。
  *            @arg SPDIFRX_FLAG_OVR: 溢出错误标志。
  *            @arg SPDIFRX_FLAG_SBD: 检测到同步块标志。
  *            @arg SPDIFRX_FLAG_SYNCD: 同步完成 flag.
  *
  * 返回值: 无
  */
void SPDIFRX_ClearFlag(uint32_t SPDIFRX_FLAG) {
    /* 检查参数 */
    assert_param(IS_SPDIFRX_CLEAR_FLAG(SPDIFRX_FLAG));

    /* 清除 selected SPDIFRX Block flag */
    SPDIFRX->IFCR |= SPDIFRX_FLAG;
}

/**
  * 简介:  检查指定的 SPDIFRX 中断是否发生。
  * 
  * 参数:  SPDIFRX_IT: 指定要启用或禁用的SPDIFRX中断源。
  *          此参数可以是以下值之一:
  *            @arg SPDIFRX_IT_RXNE:  RXNE中断启用
  *            @arg SPDIFRX_IT_CSRNE: 控制缓冲就绪中断启用
  *            @arg SPDIFRX_IT_PERRIE: 奇偶校验错误中断 enable
  *            @arg SPDIFRX_IT_OVRIE:  溢出错误中断启用
  *            @arg SPDIFRX_IT_SBLKIE: 同步块检测到中断启用
  *            @arg SPDIFRX_IT_SYNCDIE: 同步完成
  *            @arg SPDIFRX_IT_IFEIE: 串行接口错误中断启用
  * 
  * 返回值: SPDIFRX_IT的新状态(SET或RESET)。
  */
ITStatus SPDIFRX_GetITStatus(uint32_t SPDIFRX_IT) {
    ITStatus bitstatus = RESET;
    uint32_t  enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_SPDIFRX_CONFIG_IT(SPDIFRX_IT));

    /* 获取SPDIFRX_IT enable bit 状态 */
    enablestatus = (SPDIFRX->IMR & SPDIFRX_IT) ;

    /* 检查 the status of the specified SPDIFRX 中断 */
    if (((SPDIFRX->SR & SPDIFRX_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET)) {
        /* SPDIFRX_IT 被设置 */
        bitstatus = SET;
    } else {
        /* SPDIFRX_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回SPDIFRX_IT 状态 */
    return bitstatus;
}

/**
  * 简介:  清除 SPDIFRX 中断挂起位。
  * 
  * 参数:  SAI_IT: 指定要清除的SPDIFRX中断挂起位。
  *          此参数可以是以下值之一:
  *            @arg SPDIFRX_IT_MUTEDET: 静音检测中断。
  *            @arg SPDIFRX_IT_OVRUDR: 超限/欠载运行中断。
  *            @arg SPDIFRX_IT_WCKCFG: 错误的时钟配置中断。
  *            @arg SPDIFRX_IT_CNRDY: codec not 就绪中断.
  *            @arg SPDIFRX_IT_AFSDET: 预期的帧同步检测中断。
  *            @arg SPDIFRX_IT_LFSDET: 后期帧同步检测中断。
  *
  * 注意:    FREQ (FIFO Request) flag is cleared :
  *          - 当音频块是发送器且 FIFO 已满或 FIFO 有一个数据（一个缓冲模式）时，
  *            取决于 SPDIFRX_xCR2 寄存器中的位FTH。
  *          - 当音频块为接收器且 FIFO 不为空时
  *
  * 返回值: 无
  */
void SPDIFRX_ClearITPendingBit(uint32_t SPDIFRX_IT) {
    /* 检查参数 */
    assert_param(IS_SPDIFRX_CLEAR_FLAG(SPDIFRX_IT));

    /* 清除 selected SPDIFRX interrupt pending 位 */
    SPDIFRX->IFCR |= SPDIFRX_IT;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* STM32F446xx */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
