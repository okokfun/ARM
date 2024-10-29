/**
  ******************************************************************************
  * 文件:    stm32f4xx_dcmi.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能来管理 DCMI 外设的以下功能:
  *           + 初始化与配置
  *           + 图像捕捉功能
  *           + 中断和标志管理
  *
 @verbatim
 ===============================================================================
                        ##### 如何使用此驱动程序 #####
 ===============================================================================
    [..]
      以下序列描述了如何使用此驱动程序从连接到 DCMI 接口的相机模块捕获图像。
      此序列不考虑摄像头模块的配置，需要在配置和启用 DCMI 捕获图像之前进行配置。

      (#) 使用以下函数启用 DCMI 和相关 GPIO 的时钟:
          RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
          RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

      (#) DCMI 引脚配置
        (++) 使用以下函数将涉及的 DCMI 引脚连接到 AF13
            GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_DCMI);
        (++) 通过调用函数 GPIO_Init() 将这些 DCMI 引脚配置为复用功能模式;

      (#) 声明一个 DCMI_InitTypeDef 结构，例如:
          DCMI_InitTypeDef  DCMI_InitStructure;
          并用结构成员的允许值填充 DCMI_InitStructure 变量。

      (#) 通过调用函数初始化 DCMI接口
          DCMI_Init(&DCMI_InitStructure);

      (#) 配置 DMA2_Stream1 通道 1 以将数据从 DCMI DR 寄存器传输到目标内存缓冲区。

      (#) 使用函数启用 DCMI 接口
          DCMI_Cmd(ENABLE);

      (#) 使用函数开始图像捕获
          DCMI_CaptureCmd(ENABLE);

      (#) 在这个阶段，DCMI 接口等待第一个帧开始，
		  然后连续/一次生成 DMA 请求(取决于使用的模式，连续/快照)，
		  以将接收到的数据传输到目标存储器。

      -@-  如果您只需要从接收到的图像中捕获一个矩形窗口，
		   您必须使用 DCMI_CROPConfig() 函数来配置要捕获的窗口的坐标和大小，
		   然后使用 DCMI_CROPCmd(ENABLE) 启用 Crop 功能;
           在这种情况下，应先进行 Crop 配置，以启用和启动 DCMI 界面。

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
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup DCMI
  * 简介: DCMI 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup DCMI_Private_Functions
  */

/** @defgroup DCMI_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
              ##### 初始化和配置函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  将 DCMI 寄存器取消初始化为其默认复位值。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void DCMI_DeInit(void) {
    DCMI->CR = 0x0;
    DCMI->IER = 0x0;
    DCMI->ICR = 0x1F;
    DCMI->ESCR = 0x0;
    DCMI->ESUR = 0x0;
    DCMI->CWSTRTR = 0x0;
    DCMI->CWSIZER = 0x0;
}

/**
  * 简介:  根据 DCMI_InitStruct 中指定的参数初始化 DCMI。
  * 
  * 参数:  DCMI_InitStruct: 指向 DCMI_InitTypeDef 结构的指针，该结构包含DCMI 的配置信息。
  * 
  * 返回值: 无
  */
void DCMI_Init(DCMI_InitTypeDef* DCMI_InitStruct) {
    uint32_t temp = 0x0;

    /* 检查参数 */
    assert_param(IS_DCMI_CAPTURE_MODE(DCMI_InitStruct->DCMI_CaptureMode));
    assert_param(IS_DCMI_SYNCHRO(DCMI_InitStruct->DCMI_SynchroMode));
    assert_param(IS_DCMI_PCKPOLARITY(DCMI_InitStruct->DCMI_PCKPolarity));
    assert_param(IS_DCMI_VSPOLARITY(DCMI_InitStruct->DCMI_VSPolarity));
    assert_param(IS_DCMI_HSPOLARITY(DCMI_InitStruct->DCMI_HSPolarity));
    assert_param(IS_DCMI_CAPTURE_RATE(DCMI_InitStruct->DCMI_CaptureRate));
    assert_param(IS_DCMI_EXTENDED_DATA(DCMI_InitStruct->DCMI_ExtendedDataMode));

    /* 在启用 CR_ENABLE 位和 CR_CAPTURE 之前，应正确编程 DCMI 配置寄存器位 */
    DCMI->CR &= ~(DCMI_CR_ENABLE | DCMI_CR_CAPTURE);

    /* 重设 old DCMI 配置*/
    temp = DCMI->CR;

    temp &= ~((uint32_t)DCMI_CR_CM     | DCMI_CR_ESS   | DCMI_CR_PCKPOL |
              DCMI_CR_HSPOL  | DCMI_CR_VSPOL | DCMI_CR_FCRC_0 |
              DCMI_CR_FCRC_1 | DCMI_CR_EDM_0 | DCMI_CR_EDM_1);

    /* 设置 DCMI 的新配置外设 */
    temp |= ((uint32_t)DCMI_InitStruct->DCMI_CaptureMode |
             DCMI_InitStruct->DCMI_SynchroMode |
             DCMI_InitStruct->DCMI_PCKPolarity |
             DCMI_InitStruct->DCMI_VSPolarity |
             DCMI_InitStruct->DCMI_HSPolarity |
             DCMI_InitStruct->DCMI_CaptureRate |
             DCMI_InitStruct->DCMI_ExtendedDataMode);

    DCMI->CR = temp;
}

/**
  * 简介:  用默认值填充每个 DCMI_InitStruct 成员。
  * 
  * 参数:  DCMI_InitStruct : 指向 DCMI_InitTypeDef 结构的指针，该结构将被初始化。
  * 
  * 返回值: 无
  */
void DCMI_StructInit(DCMI_InitTypeDef* DCMI_InitStruct) {
    /* 设置默认配置 */
    DCMI_InitStruct->DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
    DCMI_InitStruct->DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
    DCMI_InitStruct->DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
    DCMI_InitStruct->DCMI_VSPolarity = DCMI_VSPolarity_Low;
    DCMI_InitStruct->DCMI_HSPolarity = DCMI_HSPolarity_Low;
    DCMI_InitStruct->DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
    DCMI_InitStruct->DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
}

/**
  * 简介:  根据 DCMI_CROPInitStruct 中指定的参数初始化 DCMI 外设 CROP 模式。
  * 
  * 注意:   这个函数应该在启用和启动 DCMI接口之前被调用
  * 。
  * 参数:  DCMI_CROPInitStruct:  指向 DCMI_CROPInitTypeDef 结构的指针，
  *                              该结构包含DCMI 外围CROP模式的配置信息。
  * 
  * 返回值: 无
  */
void DCMI_CROPConfig(DCMI_CROPInitTypeDef* DCMI_CROPInitStruct) {
    /* 设置 CROP窗口坐标 */
    DCMI->CWSTRTR = (uint32_t)((uint32_t)DCMI_CROPInitStruct->DCMI_HorizontalOffsetCount |
                               ((uint32_t)DCMI_CROPInitStruct->DCMI_VerticalStartLine << 16));

    /* 设置 CROP窗口大小 */
    DCMI->CWSIZER = (uint32_t)(DCMI_CROPInitStruct->DCMI_CaptureCount |
                               ((uint32_t)DCMI_CROPInitStruct->DCMI_VerticalLineCount << 16));
}

/**
  * 简介:  启用或禁用 DCMI 裁剪功能。
  * 
  * 注意:   这个函数应该在启用和启动 DCMI接口之前被调用。
  * 
  * 参数:  NewState: 新状态的 DCMI作物功能。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DCMI_CROPCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 DCMI 裁剪功能 */
        DCMI->CR |= (uint32_t)DCMI_CR_CROP;
    } else {
        /* 禁用 DCMI 裁剪功能 */
        DCMI->CR &= ~(uint32_t)DCMI_CR_CROP;
    }
}

/**
  * 简介:  设置嵌入式同步代码。
  * 
  * 参数:  DCMI_CodesInitTypeDef: 指向 DCMI_CodesInitTypeDef 结构的指针，
  *                               该结构包含DCMI 外设的嵌入式同步代码。
  * 
  * 返回值: 无
  */
void DCMI_SetEmbeddedSynchroCodes(DCMI_CodesInitTypeDef* DCMI_CodesInitStruct) {
    DCMI->ESCR = (uint32_t)(DCMI_CodesInitStruct->DCMI_FrameStartCode |
                            ((uint32_t)DCMI_CodesInitStruct->DCMI_LineStartCode << 8) |
                            ((uint32_t)DCMI_CodesInitStruct->DCMI_LineEndCode << 16) |
                            ((uint32_t)DCMI_CodesInitStruct->DCMI_FrameEndCode << 24));
}

/**
  * 简介:  启用或禁用 DCMI JPEG 格式。
  * 
  * 注意:   裁剪和嵌入式同步功能不能在此模式下使用。
  * 
  * 参数:  NewState: DCMI JPEG 格式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DCMI_JPEGCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 DDCMI JPEG 格式 */
        DCMI->CR |= (uint32_t)DCMI_CR_JPEG;
    } else {
        /* 禁用 DCMI JPEG 格式 */
        DCMI->CR &= ~(uint32_t)DCMI_CR_JPEG;
    }
}

/** @defgroup DCMI_Group2 图像采集功能
 *  简介   图像采集功能
 *
@verbatim
 ===============================================================================
                    ##### 图像采集功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用或禁用 DCMI 接口。
  * 
  * 参数:  NewState: DCMI 接口的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DCMI_Cmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 DDCMI 通过设置 ENABLE 位 */
        DCMI->CR |= (uint32_t)DCMI_CR_ENABLE;
    } else {
        /* 禁用 DDCMI 通过清除 ENABLE 位 */
        DCMI->CR &= ~(uint32_t)DCMI_CR_ENABLE;
    }
}

/**
  * 简介:  启用或禁用 DCMI 捕获。
  * 
  * 参数:  NewState: DCMI捕获的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DCMI_CaptureCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 DCMI 捕获 */
        DCMI->CR |= (uint32_t)DCMI_CR_CAPTURE;
    } else {
        /* 禁用 DCMI 捕获 */
        DCMI->CR &= ~(uint32_t)DCMI_CR_CAPTURE;
    }
}

/**
  * 简介:  读取存储在 DR 寄存器中的数据。
  * 
  * 参数:  无
  * 
  * 返回值: 数据寄存器值
  */
uint32_t DCMI_ReadData(void) {
    return DCMI->DR;
}

/** @defgroup DCMI_Group3 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
             ##### 中断和标记管理函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用或禁用 DCMI 接口中断。
  * 
  * 参数:  DCMI_IT: 指定要启用或禁用的 DCMI中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg DCMI_IT_FRAME: 帧捕获完成中断掩码
  *            @arg DCMI_IT_OVF: 溢出中断掩码
  *            @arg DCMI_IT_ERR: 同步错误中断掩码
  *            @arg DCMI_IT_VSYNC: VSYNC 中断掩码
  *            @arg DCMI_IT_LINE: 线路中断屏蔽
  * 
  * 参数:  NewState: 指定的 DCMI中断的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DCMI_CONFIG_IT(DCMI_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用中断源 */
        DCMI->IER |= DCMI_IT;
    } else {
        /* 禁用中断源 */
        DCMI->IER &= (uint16_t)(~DCMI_IT);
    }
}

/**
  * 简介:  检查是否设置了 DCMI 接口标志。
  * 
  * 参数:  DCMI_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *              @arg DCMI_FLAG_FRAMERI: 帧捕获完成的原始标志面具
  *              @arg DCMI_FLAG_OVFRI:   溢出原始标志掩码
  *              @arg DCMI_FLAG_ERRRI:   同步错误 原始标志掩码
  *              @arg DCMI_FLAG_VSYNCRI: VSYNC 原始标志掩码
  *              @arg DCMI_FLAG_LINERI:  线路原始标志掩码
  *              @arg DCMI_FLAG_FRAMEMI: 帧捕获完成 掩码标志掩码
  *              @arg DCMI_FLAG_OVFMI:   溢出掩码标志掩码
  *              @arg DCMI_FLAG_ERRMI:   同步错误 掩码标志掩码
  *              @arg DCMI_FLAG_VSYNCMI: VSYNC 掩码标志掩码
  *              @arg DCMI_FLAG_LINEMI:  线路掩码标志掩码
  *              @arg DCMI_FLAG_HSYNC:   HSYNC 标志掩码
  *              @arg DCMI_FLAG_VSYNC:   VSYNC 标志掩码
  *              @arg DCMI_FLAG_FNE: Fifo 非空标志掩码
  * 
  * 返回值。DCMI_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus DCMI_GetFlagStatus(uint16_t DCMI_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t dcmireg, tempreg = 0;

    /* 检查参数 */
    assert_param(IS_DCMI_GET_FLAG(DCMI_FLAG));

    /* 获取 DCMI register index */
    dcmireg = (((uint16_t)DCMI_FLAG) >> 12);

    if (dcmireg == 0x00) { /* The FLAG is in RISR 寄存器 */
        tempreg = DCMI->RISR;
    } else if (dcmireg == 0x02) { /* The FLAG is in SR 寄存器 */
        tempreg = DCMI->SR;
    } else { /* The FLAG is in MISR 寄存器 */
        tempreg = DCMI->MISR;
    }

    if ((tempreg & DCMI_FLAG) != (uint16_t)RESET ) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    /* 返回 DCMI_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 DCMI 的挂起标志。
  * 
  * 参数:  DCMI_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
    *           @arg DCMI_FLAG_FRAMERI: 帧捕获完成的原始标志面具
    *           @arg DCMI_FLAG_OVFRI:   溢出原始标志掩码
    *           @arg DCMI_FLAG_ERRRI:   同步错误 原始标志掩码
    *           @arg DCMI_FLAG_VSYNCRI: VSYNC 原始标志掩码
    *           @arg DCMI_FLAG_LINERI:  线路原始标志掩码
    * 
  * 返回值: 无
  */
void DCMI_ClearFlag(uint16_t DCMI_FLAG) {
    /* 检查参数 */
    assert_param(IS_DCMI_CLEAR_FLAG(DCMI_FLAG));

    /* 通过在 ICR 寄存器1 中写到相应的flag 位置*/

    DCMI->ICR = DCMI_FLAG;
}

/**
  * 简介:  检查是否发生了 DCMI 中断。
  * 
  * 参数:  DCMI_IT: 指定要检查的 DCMI中断源。
  *         此参数可以是以下值之一。
  *          @arg DCMI_IT_FRAME: 帧捕获完成的中断掩码
  *          @arg DCMI_IT_OVF: 溢出中断掩码
  *          @arg DCMI_IT_ERR: 同步错误中断掩码
  *          @arg DCMI_IT_VSYNC: VSYNC 中断掩码
  *          @arg DCMI_IT_LINE: 线路中断掩码
  * 
  * 返回值: DCMI_IT 的新状态(SET 或 RESET)。
  */
ITStatus DCMI_GetITStatus(uint16_t DCMI_IT) {
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0;

    /* 检查参数 */
    assert_param(IS_DCMI_GET_IT(DCMI_IT));

    itstatus = DCMI->MISR & DCMI_IT; /* 只检查被屏蔽的中断 */

    if ((itstatus != (uint16_t)RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 DCMI 的中断挂起位。
  * 
  * 参数:  DCMI_IT: 指定要清除的 DCMI中断等待位。
  *          此参数可以是以下值的任意组合:
    *           @arg DCMI_IT_FRAME: 帧捕获完成中断掩码
    *           @arg DCMI_IT_OVF: 溢出中断掩码
    *           @arg DCMI_IT_ERR: 同步错误中断掩码
    *           @arg DCMI_IT_VSYNC: VSYNC 中断掩码
    *           @arg DCMI_IT_LINE: 线路中断屏蔽
    * 
  * 返回值: 无
  */
void DCMI_ClearITPendingBit(uint16_t DCMI_IT) {
    /* 清除通过在相应的挂起位位置写入ICR 寄存器1来中断挂起位*/

    DCMI->ICR = DCMI_IT;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
