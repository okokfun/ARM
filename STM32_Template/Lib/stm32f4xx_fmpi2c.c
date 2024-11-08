 /**
  ******************************************************************************
  * 文件:    stm32f4xx_fmpi2c.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供了管理以下内容的固件功能
  *             该文件提供了固件功能，以管理互连电路快速模式+(FMPI2C)的以下功能。
  *           + 初始化和配置
  *           + 通信处理
  *           + SMBUS 管理
  *           + FMPI2C 寄存器管理
  *           + 数据传输管理
  *           + DMA 传输管理
  *           + 中断和标志管理
  *
  *  @verbatim
 ============================================================================
                     ##### 如何使用这个驱动程序 #####
 ============================================================================
   [..]
   (#) 使用 RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2Cx, ENABLE) 函数为 FMPI2C 外设启用外围时钟。
   (#) 使用 RCC_AHBPeriph 函数启用 SDA、SCL 和 SMBA(如果使用) GPIO 时钟。
       RCC_AHBPeriphClockCmd() 函数。

   (#) 外设设备替代函数。
       (++)将引脚连接到所需的外设设备的替代函数。使用 GPIO_PinAFConfig()
           函数将引脚连接到所需外设的复用功能(AF)。

       (++)通过配置所需引脚的复用功能。
            GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF

       (++) 通过以下方式选择类型，OpenDrain和速度
            GPIO_PuPd, GPIO_OType 和 GPIO_Speed 成员选择类型、OpenDrain 和速度。
            
       (++) 调用 GPIO_Init() 函数。

   (#) 使用 FMPI2C_Init() 函数对模式、时序、自身地址、Ack和 Acknowledged Address进行编程。

   (#) 你可以选择启用/配置以下参数，而不需要重新初始化(即不需要再次调用 FMPI2C_Init() 函数)。
       (++) 使用 FMPI2C_AcknowledgeConfig() 函数启用确认功能。
       (++) 使用 FMPI2C_DualAddressCmd() 函数启用双地址模式。
       (++) 使用 FMPI2C_GeneralCallCmd() 函数启用一般调用功能。
       (++) 使用 FMPI2C_StretchClockCmd() 函数启用时钟拉伸功能。
       (++) 使用 FMPI2C_CalculatePEC() 函数启用 PEC 计算。
       (++) 对于 SMBuS 模式。
       (++) 使用 FMPI2C_SMBusAlertCmd() 函数启用 SMBusAlert 引脚。

   (#) 如果需要使用中断模式，使用函数FMPI2C_ITConfig() 启用 NVIC 和相应的中断。

   (#) 当使用 DMA 模式时
      (++) 使用 DMA_Init() 函数配置 DMA。
      (++) 使用 FMPI2C_DMACmd() 函数激活需要的通道请求。
   (#) 使用 FMPI2C_Cmd() 函数启用 FMPI2C。

   (#) 在传输中使用 DMA 模式时，使用 DMA_Cmd() 函数启用 DMA。
   [..]
   (@) 当在快速模式下使用 FMPI2C 时，必须通过设置 SYSCFG 中的驱动能力
       控制位来启用 SCL 和 SDA 引脚 20mA 电流驱动能力。

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
#include "stm32f4xx_fmpi2c.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup FMPI2C  FMPI2C
  * 简介: FMPI2C 驱动模块
  */
#if defined(STM32F410xx) || defined(STM32F412xG)|| defined(STM32F413_423xx) || defined(STM32F446xx)
/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

#define CR1_CLEAR_MASK          ((uint32_t)0x00CFE0FF)  /*<! FMPI2C CR1 clear 寄存器掩码 */
#define CR2_CLEAR_MASK          ((uint32_t)0x07FF7FFF)  /*<! FMPI2C CR2 clear 寄存器掩码 */
#define TIMING_CLEAR_MASK       ((uint32_t)0xF0FFFFFF)  /*<! FMPI2C TIMING clear 寄存器掩码 */
#define ERROR_IT_MASK           ((uint32_t)0x00003F00)  /*<! FMPI2C Error interrupt 寄存器掩码 */
#define TC_IT_MASK              ((uint32_t)0x000000C0)  /*<! FMPI2C TC interrupt 寄存器掩码 */

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/
     
/** @defgroup FMPI2C_Private_Functions
  */


/** @defgroup FMPI2C_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
           ##### 初始化和配置函数 #####
 ===============================================================================
    [..] 本节提供了一组函数，允许初始化FMPI2C 模式、FMPI2C 计时、FMPI2C滤波器、
         FMPI2C寻址模式、FMPI2C OwnAddress1。

    [..] FMPI2C_Init() 函数遵循FMPI2C配置程序(这些程序可以在参考手册中找到)。

    [..] 当使用 FMPI2C_SoftwareResetCmd() 函数进行软件复位时，
          内部状态机被复位，通信控制位以及状态位回到其复位值。

    [..] 在使用 FMPI2C_StopModeCmd() 函数启用停止模式之前，
         必须将FMPI2C 时钟源设置为 HSI，并且必须禁用数字滤波器。

    [..] 在通过FMPI2C_DualAddressCmd() 函数启用自有地址2之前，
         应使用 FMPI2C_OwnAddress2Config() 函数配置 OA2 和掩码。

    [..] FMPI2C_SlaveByteControlCmd() 函数启用从属字节控制，
         当NBYTES被设置为0x01时，允许用户在从属模式下获得每个字节的控制权。

@endverbatim
  */

/**
  * 简介:  将 FMPI2Cx 外设寄存器取消初始化为其默认复位值。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 返回值: 无
  */
void FMPI2C_DeInit(FMPI2C_TypeDef* FMPI2Cx) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));

    if (FMPI2Cx == FMPI2C1) {
        /* 使能FMPI2C1 复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_FMPI2C1, ENABLE);
        /* 释放FMPI2C1 from 复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_FMPI2C1, DISABLE);
    }
}

/**
  * 简介:  根据 FMPI2C_InitStruct 中指定的参数初始化 FMPI2Cx 外设。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  FMPI2C_InitStruct: 指向 FMPI2C_InitTypeDef 结构的指针，
  *                           该结构包含指定 FMPI2C 外设的配置信息。
  * 
  * 返回值: 无
  */
void FMPI2C_Init(FMPI2C_TypeDef* FMPI2Cx, FMPI2C_InitTypeDef* FMPI2C_InitStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_ANALOG_FILTER(FMPI2C_InitStruct->FMPI2C_AnalogFilter));
    assert_param(IS_FMPI2C_DIGITAL_FILTER(FMPI2C_InitStruct->FMPI2C_DigitalFilter));
    assert_param(IS_FMPI2C_MODE(FMPI2C_InitStruct->FMPI2C_Mode));
    assert_param(IS_FMPI2C_OWN_ADDRESS1(FMPI2C_InitStruct->FMPI2C_OwnAddress1));
    assert_param(IS_FMPI2C_ACK(FMPI2C_InitStruct->FMPI2C_Ack));
    assert_param(IS_FMPI2C_ACKNOWLEDGE_ADDRESS(FMPI2C_InitStruct->FMPI2C_AcknowledgedAddress));

    /* Disable FMPI2Cx 外设 */
    FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR1_PE);

    /*---------------------------- FMPI2Cx FILTERS 配置 ------------------*/
    /* 获取 FMPI2Cx CR1 值 */
    tmpreg = FMPI2Cx->CR1;
    /* 清除 FMPI2Cx CR1 寄存器 */
    tmpreg &= CR1_CLEAR_MASK;
    /* 配置 FMPI2Cx: 模拟和数字滤波器 */
    /* 设置 ANFOFF bit 根据 FMPI2C_AnalogFilter 值 */
    /* 设置 DFN bits 根据 FMPI2C_DigitalFilter 值 */
    tmpreg |= (uint32_t)FMPI2C_InitStruct->FMPI2C_AnalogFilter | (FMPI2C_InitStruct->FMPI2C_DigitalFilter << 8);

    /* 写入 FMPI2Cx CR1 */
    FMPI2Cx->CR1 = tmpreg;

    /*---------------------------- FMPI2Cx TIMING 配置 -------------------*/
    /* 配置 FMPI2Cx: Timing */
    /* 设置 TIMINGR bits 根据 FMPI2C_Timing */
    /* 写入 FMPI2Cx TIMING */
    FMPI2Cx->TIMINGR = FMPI2C_InitStruct->FMPI2C_Timing & TIMING_CLEAR_MASK;

    /* 使能FMPI2Cx 外设 */
    FMPI2Cx->CR1 |= FMPI2C_CR1_PE;

    /*---------------------------- FMPI2Cx OAR1 配置 ---------------------*/
    /* 清除 tmpreg local variable */
    tmpreg = 0;
    /* 清除 OAR1 寄存器 */
    FMPI2Cx->OAR1 = (uint32_t)tmpreg;
    /* 清除 OAR2 寄存器 */
    FMPI2Cx->OAR2 = (uint32_t)tmpreg;
    /* 配置 FMPI2Cx: 自有地址1和确认地址 */
    /* 设置 OA1MODE bit 根据 FMPI2C_AcknowledgedAddress 值 */
    /* 设置 OA1 bits 根据 FMPI2C_OwnAddress1 值 */
    tmpreg = (uint32_t)((uint32_t)FMPI2C_InitStruct->FMPI2C_AcknowledgedAddress | \
                        (uint32_t)FMPI2C_InitStruct->FMPI2C_OwnAddress1);
    /* 写入 FMPI2Cx OAR1 */
    FMPI2Cx->OAR1 = tmpreg;
    /* 使能Own 地址1确认 */
    FMPI2Cx->OAR1 |= FMPI2C_OAR1_OA1EN;

    /*---------------------------- FMPI2Cx MODE 配置 ---------------------*/
    /* 配置 FMPI2Cx: mode */
    /* 设置 SMBDEN and SMBHEN bits 根据 FMPI2C_Mode 值 */
    tmpreg = FMPI2C_InitStruct->FMPI2C_Mode;
    /* 写入 FMPI2Cx CR1 */
    FMPI2Cx->CR1 |= tmpreg;

    /*---------------------------- FMPI2Cx ACK 配置 ----------------------*/
    /* 获取 FMPI2Cx CR2 值 */
    tmpreg = FMPI2Cx->CR2;
    /* 清除 FMPI2Cx CR2 寄存器 */
    tmpreg &= CR2_CLEAR_MASK;
    /* 配置 FMPI2Cx: 确认 */
    /* 设置 NACK bit 根据 FMPI2C_Ack 值 */
    tmpreg |= FMPI2C_InitStruct->FMPI2C_Ack;
    /* 写入 FMPI2Cx CR2 */
    FMPI2Cx->CR2 = tmpreg;
}

/**
  * 简介:  用默认值填充每个 FMPI2C_InitStruct 成员。
  * 
  * 参数:  FMPI2C_InitStruct: 指向 FMPI2C_InitTypeDef 结构的指针，将被初始化。
  * 
  * 返回值: 无
  */
void FMPI2C_StructInit(FMPI2C_InitTypeDef* FMPI2C_InitStruct) {
    /*---------------- 重置 FMPI2C 初始化结构参数值 --------------*/
    /* 初始化 FMPI2C_Timing 成员 */
    FMPI2C_InitStruct->FMPI2C_Timing = 0;
    /* 初始化 FMPI2C_AnalogFilter 成员 */
    FMPI2C_InitStruct->FMPI2C_AnalogFilter = FMPI2C_AnalogFilter_Enable;
    /* 初始化 FMPI2C_DigitalFilter 成员 */
    FMPI2C_InitStruct->FMPI2C_DigitalFilter = 0;
    /* 初始化 FMPI2C_Mode 成员 */
    FMPI2C_InitStruct->FMPI2C_Mode = FMPI2C_Mode_FMPI2C;
    /* 初始化 FMPI2C_OwnAddress1 成员 */
    FMPI2C_InitStruct->FMPI2C_OwnAddress1 = 0;
    /* 初始化 FMPI2C_Ack 成员 */
    FMPI2C_InitStruct->FMPI2C_Ack = FMPI2C_Ack_Disable;
    /* 初始化 FMPI2C_AcknowledgedAddress 成员 */
    FMPI2C_InitStruct->FMPI2C_AcknowledgedAddress = FMPI2C_AcknowledgedAddress_7bit;
}

/**
  * 简介:  启用或禁用指定的 FMPI2C 外设.
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2Cx 外设的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_Cmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 FMPI2C 外设 */
        FMPI2Cx->CR1 |= FMPI2C_CR1_PE;
    } else {
        /* 禁用被选中的 FMPI2C 外设 */
        FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR1_PE);
    }
}


/**
  * 简介:  启用或禁用指定的 FMPI2C 软件复位。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 返回值: 无
  */
void FMPI2C_SoftwareResetCmd(FMPI2C_TypeDef* FMPI2Cx) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));

    /* Disable 外设 */
    FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR1_PE);

    /* 执行伪读取以将外围设备的禁用延迟至少3个 APB 时钟周期，以执行软件重置功能 */
    *(__IO uint32_t *)(uint32_t)FMPI2Cx;

    /* 使能外设 */
    FMPI2Cx->CR1 |= FMPI2C_CR1_PE;
}

/**
  * 简介:  启用或禁用指定的 FMPI2C 中断.
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  FMPI2C_IT: 指定要启用或禁用的 FMPI2C 中断源。
  *   此参数可以是以下值的任意组合:
  *     @arg FMPI2C_IT_ERRI: 错误中断 mask
  *     @arg FMPI2C_IT_TCI: 传输完成中断屏蔽
  *     @arg FMPI2C_IT_STOPI: 停止检测中断掩码
  *     @arg FMPI2C_IT_NACKI: 未收到确认信号的中断屏蔽
  *     @arg FMPI2C_IT_ADDRI: 地址匹配中断掩码
  *     @arg FMPI2C_IT_RXI: RX 中断掩码
  *     @arg FMPI2C_IT_TXI: TX 中断掩码
  * 
  * 参数:  NewState: 指定的 FMPI2C 中断的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_ITConfig(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_FMPI2C_CONFIG_IT(FMPI2C_IT));

    if (NewState != DISABLE) {
        /* 启用被选定的 FMPI2C 中断 */
        FMPI2Cx->CR1 |= FMPI2C_IT;
    } else {
        /* 禁用被选中的 FMPI2C 中断 */
        FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_IT);
    }
}

/**
  * 简介:  启用或禁用 FMPI2C 时钟拉伸。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2Cx 时钟拉伸的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_StretchClockCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能时钟伸展 */
        FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR1_NOSTRETCH);
    } else {
        /* 禁用时钟拉伸  */
        FMPI2Cx->CR1 |= FMPI2C_CR1_NOSTRETCH;
    }
}

/**
  * 简介:  启用或禁用 FMPI2C 自身地址 2.
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2C 自身地址的新状态 2.
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_DualAddressCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能自己的地址2 */
        FMPI2Cx->OAR2 |= FMPI2C_OAR2_OA2EN;
    } else {
        /* 禁用自己的地址2 */
        FMPI2Cx->OAR2 &= (uint32_t)~((uint32_t)FMPI2C_OAR2_OA2EN);
    }
}

/**
  * 简介:  配置 FMPI2C 从机自己的地址 2 和掩码。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  Address: 指定要编程的从属地址。
  * 
  * 参数:  Mask: 指定要编程的自己的地址2掩码。
  *   此参数可以是以下值之一:
  *     @arg FMPI2C_OA2_NoMask: 没有屏蔽。
  *     @arg FMPI2C_OA2_Mask01: OA2[1]被屏蔽，不关心。
  *     @arg FMPI2C_OA2_Mask02: OA2[2:1]被屏蔽，且不关心。
  *     @arg FMPI2C_OA2_Mask03: OA2[3:1]被屏蔽, 且不关心。
  *     @arg FMPI2C_OA2_Mask04: OA2[4:1]被屏蔽了，不关心。
  *     @arg FMPI2C_OA2_Mask05: OA2[5:1]被屏蔽，不关心。
  *     @arg FMPI2C_OA2_Mask06: OA2[6:1]被屏蔽，不关心。
  *     @arg FMPI2C_OA2_Mask07: OA2[7:1]被屏蔽了，不关心。
  * 
  * 返回值: 无
  */
void FMPI2C_OwnAddress2Config(FMPI2C_TypeDef* FMPI2Cx, uint16_t Address, uint8_t Mask) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_OWN_ADDRESS2(Address));
    assert_param(IS_FMPI2C_OWN_ADDRESS2_MASK(Mask));

    /* 获取old寄存器值 */
    tmpreg = FMPI2Cx->OAR2;

    /* 重置 FMPI2Cx OA2 bit [7:1] and OA2MSK bit [1:0]  */
    tmpreg &= (uint32_t)~((uint32_t)(FMPI2C_OAR2_OA2 | FMPI2C_OAR2_OA2MSK));

    /* 设置 FMPI2Cx SADD */
    tmpreg |= (uint32_t)(((uint32_t)Address & FMPI2C_OAR2_OA2) | \
                         (((uint32_t)Mask << 8) & FMPI2C_OAR2_OA2MSK)) ;

    /* 存储新的寄存器值 */
    FMPI2Cx->OAR2 = tmpreg;
}

/**
  * 简介:  启用或禁用 FMPI2C一般调用模式。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2C一般调用模式的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_GeneralCallCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能通用呼叫模式 */
        FMPI2Cx->CR1 |= FMPI2C_CR1_GCEN;
    } else {
        /* 禁用常规呼叫模式 */
        FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR1_GCEN);
    }
}

/**
  * 简介:  启用或禁用 FMPI2C从属字节控制。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2C从属字节控制的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_SlaveByteControlCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能从字节控制 */
        FMPI2Cx->CR1 |= FMPI2C_CR1_SBC;
    } else {
        /* 禁用从属字节控制 */
        FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR1_SBC);
    }
}

/**
  * 简介:  配置启动生成后要传输的从属地址。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  Address: 指定要编程的从属地址。
  * 
  * 注意:   这个函数应在生成启动条件之前调用。
  * 
  * 返回值: 无
  */
void FMPI2C_SlaveAddressConfig(FMPI2C_TypeDef* FMPI2Cx, uint16_t Address) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_SLAVE_ADDRESS(Address));

    /* 获取old寄存器值 */
    tmpreg = FMPI2Cx->CR2;

    /* 重置 FMPI2Cx SADD bit [9:0] */
    tmpreg &= (uint32_t)~((uint32_t)FMPI2C_CR2_SADD);

    /* 设置 FMPI2Cx SADD */
    tmpreg |= (uint32_t)((uint32_t)Address & FMPI2C_CR2_SADD);

    /* 存储新的寄存器值 */
    FMPI2Cx->CR2 = tmpreg;
}

/**
  * 简介:  启用或禁用 FMPI2C 主站的10位寻址模式。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2C 10位寻址模式的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 注意:   这个函数应在生成启动条件之前调用。
  * 
  * 返回值: 无
  */
void FMPI2C_10BitAddressingModeCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能10位寻址模式 */
        FMPI2Cx->CR2 |= FMPI2C_CR2_ADD10;
    } else {
        /* 禁用10位寻址模式 */
        FMPI2Cx->CR2 &= (uint32_t)~((uint32_t)FMPI2C_CR2_ADD10);
    }
}



/** @defgroup FMPI2C_Group2 通信处理功能
 *  简介   通信处理功能
 *
@verbatim
 ===============================================================================
                  ##### 通信处理功能 #####
 ===============================================================================
    [..] 本节提供了一组处理FMPI2C 通信的函数。

    [..] 自动结束模式是通过FMPI2C_AutoEndCmd() 函数启用的。
         当通过FMPI2C_ReloadCmd() 启用 Reload模式时，自动结束位没有作用。

    [..] FMPI2C_NumberOfBytesConfig() 函数设置要传输的字节数，
         这个配置应该在主模式下产生启动条件之前完成。

    [..] 在10Bit寻址模式下，当从主站写操作切换到读操作时，
         主站只能发送10位地址的前7位，然后通过FMPI2C_10BitAddressHeader() 函数启用 HEADR位，向读方向发送。

    [..] 在主控模式下，当传输超过255字节时，应该使用 Reload模式来处理通信。
         在传输的第一阶段，Nbytes应该被设置为255。在传输完这些字节后，
         TCR 标志被设置，FMPI2C_TransferHandling() 函数应该被调用来处理剩余的通信。

    [..] 在主控模式下，当选择了软件结束模式时，当所有的数据被传输完毕后，
         TC 标志被设置，FMPI2C_TransferHandling() 函数应该被调用以产生STOP或者产生ReStart。

@endverbatim
  */

/**
  * 简介:  启用或禁用 FMPI2C 自动结束模式(传输 nbytes 数据时自动发送停止条件)。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2C 自动结束模式的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 注意:   如果禁止重新加载模式，该功能就会生效。
  * 
  * 返回值: 无
  */
void FMPI2C_AutoEndCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能自动结束模式 */
        FMPI2Cx->CR2 |= FMPI2C_CR2_AUTOEND;
    } else {
        /* 禁用自动结束模式 */
        FMPI2Cx->CR2 &= (uint32_t)~((uint32_t)FMPI2C_CR2_AUTOEND);
    }
}

/**
  * 简介:  启用或禁用 FMPI2C nbytes 重载模式。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: nbytes重载模式的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_ReloadCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能自动重新加载模式 */
        FMPI2Cx->CR2 |= FMPI2C_CR2_RELOAD;
    } else {
        /* 禁用自动重新加载模式 */
        FMPI2Cx->CR2 &= (uint32_t)~((uint32_t)FMPI2C_CR2_RELOAD);
    }
}

/**
  * 简介:  配置要发送/接收的字节数。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  Number_Bytes: 指定要编程的字节数。
  * 
  * 返回值: 无
  */
void FMPI2C_NumberOfBytesConfig(FMPI2C_TypeDef* FMPI2Cx, uint8_t Number_Bytes) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));

    /* 获取old寄存器值 */
    tmpreg = FMPI2Cx->CR2;

    /* 重置 FMPI2Cx Nbytes bit [7:0] */
    tmpreg &= (uint32_t)~((uint32_t)FMPI2C_CR2_NBYTES);

    /* 设置 FMPI2Cx Nbytes */
    tmpreg |= (uint32_t)(((uint32_t)Number_Bytes << 16 ) & FMPI2C_CR2_NBYTES);

    /* 存储新的寄存器值 */
    FMPI2Cx->CR2 = tmpreg;
}

/**
  * 简介:  配置主站的传输请求类型。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  FMPI2C_Direction: 指定要编程的转移请求方向。
  *    此参数可以是以下值之一:
  *     @arg FMPI2C_Direction_Transmitter: 主控方要求进行写传输
  *     @arg FMPI2C_Direction_Receiver: 主控方要求进行读传输
  * 
  * 返回值: 无
  */
void FMPI2C_MasterRequestConfig(FMPI2C_TypeDef* FMPI2Cx, uint16_t FMPI2C_Direction) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_DIRECTION(FMPI2C_Direction));

    /* 测试设置/重置读/写的方向位 */
    if (FMPI2C_Direction == FMPI2C_Direction_Transmitter) {
        /* 请求写入传输 */
        FMPI2Cx->CR2 &= (uint32_t)~((uint32_t)FMPI2C_CR2_RD_WRN);
    } else {
        /* 请求读取传输 */
        FMPI2Cx->CR2 |= FMPI2C_CR2_RD_WRN;
    }
}

/**
  * 简介:  生成 FMPI2Cx 通信启动条件。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2C START条件生成的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_GenerateSTART(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 生成START条件 */
        FMPI2Cx->CR2 |= FMPI2C_CR2_START;
    } else {
        /* 禁用 START条件生成 */
        FMPI2Cx->CR2 &= (uint32_t)~((uint32_t)FMPI2C_CR2_START);
    }
}

/**
  * 简介:  生成 FMPI2Cx 通信停止条件。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2C STOP 条件生成的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_GenerateSTOP(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 生成STOP 条件 */
        FMPI2Cx->CR2 |= FMPI2C_CR2_STOP;
    } else {
        /* 禁用 STOP 条件生成 */
        FMPI2Cx->CR2 &= (uint32_t)~((uint32_t)FMPI2C_CR2_STOP);
    }
}

/**
  * 简介:  启用或禁用具有读取方向的 FMPI2C 10 位仅标头模式。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2C 10-bit header only模式的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 注意:   该模式只能在从主发射器模式切换到主接收器模式时使用。
  * 
  * 返回值: 无
  */
void FMPI2C_10BitAddressHeaderCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能仅10位标头模式 */
        FMPI2Cx->CR2 |= FMPI2C_CR2_HEAD10R;
    } else {
        /* 禁用仅10位标头模式 */
        FMPI2Cx->CR2 &= (uint32_t)~((uint32_t)FMPI2C_CR2_HEAD10R);
    }
}

/**
  * 简介:  生成 FMPI2C 通信确认。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: 新状态-> Acknowledge.
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_AcknowledgeConfig(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能 ACK 生成 */
        FMPI2Cx->CR2 &= (uint32_t)~((uint32_t)FMPI2C_CR2_NACK);
    } else {
        /* 使能 NACK 生成 */
        FMPI2Cx->CR2 |= FMPI2C_CR2_NACK;
    }
}

/**
  * 简介:  返回 FMPI2C 从机匹配地址。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 返回值: 从机匹配地址的值。
  */
uint8_t FMPI2C_GetAddressMatched(FMPI2C_TypeDef* FMPI2Cx) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));

    /* 返回SR1 中的从属匹配地址寄存器 */
    return (uint8_t)(((uint32_t)FMPI2Cx->ISR & FMPI2C_ISR_ADDCODE) >> 16) ;
}

/**
  * 简介:  返回 FMPI2C 从机接收到的请求。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 返回值: 收到的请求的值。
  */
uint16_t FMPI2C_GetTransferDirection(FMPI2C_TypeDef* FMPI2Cx) {
    uint32_t tmpreg = 0;
    uint16_t direction = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));

    /* 返回SR1 中的从属匹配地址寄存器 */
    tmpreg = (uint32_t)(FMPI2Cx->ISR & FMPI2C_ISR_DIR);

    /* 如果请求写入传输 */
    if (tmpreg == 0) {
        /* 请求写入传输 */
        direction = FMPI2C_Direction_Transmitter;
    } else {
        /* 请求读取传输 */
        direction = FMPI2C_Direction_Receiver;
    }

    return direction;
}

/**
  * 简介:  在开始传输或传输期间(TC 或 TCR 标志置位)处理 FMPI2Cx 通信。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  Address: 指定要编程的从属地址。
  * 
  * 参数:  Number_Bytes: 指定要编程的字节数。
  *   这个参数必须是 0 到 255 之间的值。
  * 
  * 参数:  ReloadEndMode: FMPI2C START条件生成的新状态。
  *   此参数可以是以下值之一:
  *     @arg FMPI2C_Reload_Mode: 启用重新加载模式。
  *     @arg FMPI2C_AutoEnd_Mode: 启用自动结束模式。
  *     @arg FMPI2C_SoftEnd_Mode: 启用软件结束模式。
  * 
  * 参数:  StartStopMode: FMPI2C启动条件生成的新状态。
  *     此参数可以是以下值之一。
  *     @arg FMPI2C_No_StartStop: 不产生停止和启动条件。
  *     @arg FMPI2C_Generate_Stop: 产生停止条件(Number_Bytes应该被设置为0)。
  *     @arg FMPI2C_Generate_Start_Read: 为读取请求生成重启条件。
  *     @arg FMPI2C_Generate_Start_Write: 为写请求产生重启。
  * 
  * 返回值: 无
  */
void FMPI2C_TransferHandling(FMPI2C_TypeDef* FMPI2Cx, uint16_t Address, uint8_t Number_Bytes, uint32_t ReloadEndMode, uint32_t StartStopMode) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_SLAVE_ADDRESS(Address));
    assert_param(IS_RELOAD_END_MODE(ReloadEndMode));
    assert_param(IS_START_STOP_MODE(StartStopMode));

    /* 获取CR2寄存器值 */
    tmpreg = FMPI2Cx->CR2;

    /* 清除 tmpreg specific 位 */
    tmpreg &= (uint32_t)~((uint32_t)(FMPI2C_CR2_SADD | FMPI2C_CR2_NBYTES | FMPI2C_CR2_RELOAD | FMPI2C_CR2_AUTOEND | FMPI2C_CR2_RD_WRN | FMPI2C_CR2_START | FMPI2C_CR2_STOP));

    /* update tmpreg */
    tmpreg |= (uint32_t)(((uint32_t)Address & FMPI2C_CR2_SADD) | (((uint32_t)Number_Bytes << 16 ) & FMPI2C_CR2_NBYTES) | \
                         (uint32_t)ReloadEndMode | (uint32_t)StartStopMode);

    /* update CR2 寄存器 */
    FMPI2Cx->CR2 = tmpreg;
}



/** @defgroup FMPI2C_Group3 SMBUS 管理功能
 *  简介   SMBUS 管理功能
 *
@verbatim
 ===============================================================================
                      ##### SMBUS 管理功能 #####
 ===============================================================================
    [..] 本节提供了一组处理 SMBus通信和超时检测的函数。

    [..] 通过调用 FMPI2C_Init() 函数并将FMPI2C_InitTypeDef()结构的
         FMPI2C_Mode成员设置为 FMPI2C_Mode_SMBusDevice，启用 SMBus设备默认地址(0b1100 001)。

    [..] 通过调用 FMPI2C_Init() 函数并将FMPI2C_InitTypeDef()结构的 FMPI2C_Mode成员
         设置为 FMPI2C_Mode_SMBusHost，启用 SMBus Host地址(0b0001 000)。

    [..] 使用 FMPI2C_SMBusAlertCmd() 函数启用警报响应地址(0b0001 100)。

    [..] 为了检测主站和从站模式下的累积SCL拉伸，应该用 FMPI2C_TimeoutBConfig()
         函数配置 TIMEOUTB(符合SMBus规范)，然后调用 FMPI2C_ExtendedClockTimeoutCmd() 函数来启用检测。

    [..] 通过使用 FMPI2C_TimeoutBConfig() 函数配置 TIMEOUTB，
         然后调用 FMPI2C_ClockTimeoutCmd()来检测SCL低电平超时。
         当在此过程中加入 FMPI2C_IdleClockTimeoutCmd() 函数的调用时，
         总线空闲状态(SCL和 SDA均为高电平)也被检测到。

@endverbatim
  */

/**
  * 简介:  启用或禁用 FMPI2C SMBus 警报。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2Cx SMBus 警报的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_SMBusAlertCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能 SMBus 警报 */
        FMPI2Cx->CR1 |= FMPI2C_CR1_ALERTEN;
    } else {
        /* 禁用 SMBus 警报 */
        FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR1_ALERTEN);
    }
}

/**
  * 简介:  启用或禁用 FMPI2C 时钟超时(SCL 超时检测)。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2Cx 时钟的新状态 超时。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_ClockTimeoutCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能时钟超时 */
        FMPI2Cx->TIMEOUTR |= FMPI2C_TIMEOUTR_TIMOUTEN;
    } else {
        /* 禁用时钟超时 */
        FMPI2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)FMPI2C_TIMEOUTR_TIMOUTEN);
    }
}

/**
  * 简介:  启用或禁用 FMPI2C 扩展时钟超时(SCL 累积超时检测)。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2Cx扩展时钟超时的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_ExtendedClockTimeoutCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能时钟超时 */
        FMPI2Cx->TIMEOUTR |= FMPI2C_TIMEOUTR_TEXTEN;
    } else {
        /* 禁用时钟超时 */
        FMPI2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)FMPI2C_TIMEOUTR_TEXTEN);
    }
}

/**
  * 简介:  启用或禁用 FMPI2C 空闲时钟超时(总线空闲 SCL 和 SDA 高电平检测)。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2Cx空闲时钟超时的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_IdleClockTimeoutCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能时钟超时 */
        FMPI2Cx->TIMEOUTR |= FMPI2C_TIMEOUTR_TIDLE;
    } else {
        /* 禁用时钟超时 */
        FMPI2Cx->TIMEOUTR &= (uint32_t)~((uint32_t)FMPI2C_TIMEOUTR_TIDLE);
    }
}

/**
  * 简介:  配置 FMPI2C 总线超时 A(TIDLE = 0 时 SCL 超时或 TIDLE = 1 时总线空闲 SCL 和 SDA 高)。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  Timeout: 指定要编程的 TimeoutA。
  * 
  * 返回值: 无
  */
void FMPI2C_TimeoutAConfig(FMPI2C_TypeDef* FMPI2Cx, uint16_t Timeout) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_TIMEOUT(Timeout));

    /* 获取old寄存器值 */
    tmpreg = FMPI2Cx->TIMEOUTR;

    /* 重置 FMPI2Cx TIMEOUTA bit [11:0] */
    tmpreg &= (uint32_t)~((uint32_t)FMPI2C_TIMEOUTR_TIMEOUTA);

    /* 设置 FMPI2Cx TIMEOUTA */
    tmpreg |= (uint32_t)((uint32_t)Timeout & FMPI2C_TIMEOUTR_TIMEOUTA) ;

    /* 存储新的寄存器值 */
    FMPI2Cx->TIMEOUTR = tmpreg;
}

/**
  * 简介:  配置 FMPI2C 总线超时 B(SCL 累积超时)。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  Timeout: 指定要编程的 TimeoutB。
  * 
  * 返回值: 无
  */
void FMPI2C_TimeoutBConfig(FMPI2C_TypeDef* FMPI2Cx, uint16_t Timeout) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_TIMEOUT(Timeout));

    /* 获取old寄存器值 */
    tmpreg = FMPI2Cx->TIMEOUTR;

    /* 重置 FMPI2Cx TIMEOUTB bit [11:0] */
    tmpreg &= (uint32_t)~((uint32_t)FMPI2C_TIMEOUTR_TIMEOUTB);

    /* 设置 FMPI2Cx TIMEOUTB */
    tmpreg |= (uint32_t)(((uint32_t)Timeout << 16) & FMPI2C_TIMEOUTR_TIMEOUTB) ;

    /* 存储新的寄存器值 */
    FMPI2Cx->TIMEOUTR = tmpreg;
}

/**
  * 简介:  启用或禁用 FMPI2C PEC 计算。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2Cx PEC 计算的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_CalculatePEC(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能PEC 计算 */
        FMPI2Cx->CR1 |= FMPI2C_CR1_PECEN;
    } else {
        /* 禁用 PEC 计算 */
        FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR1_PECEN);
    }
}

/**
  * 简介:  启用或禁用 FMPI2C PEC 发送/接收请求。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  NewState: FMPI2Cx PEC请求的新状态。
  *   此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_PECRequestCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能PEC发送/接收请求 */
        FMPI2Cx->CR1 |= FMPI2C_CR2_PECBYTE;
    } else {
        /* 禁用 PEC发送/接收请求 */
        FMPI2Cx->CR1 &= (uint32_t)~((uint32_t)FMPI2C_CR2_PECBYTE);
    }
}

/**
  * 简介:  返回 FMPI2C PEC。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 返回值: PEC 的值。
  */
uint8_t FMPI2C_GetPEC(FMPI2C_TypeDef* FMPI2Cx) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));

    /* 返回SR1 中的从属匹配地址寄存器 */
    return (uint8_t)((uint32_t)FMPI2Cx->PECR & FMPI2C_PECR_PEC);
}



/** @defgroup FMPI2C_Group4 FMPI2C注册管理功能
 *  简介   FMPI2C注册管理功能
 *
@verbatim
 ===============================================================================
                ##### FMPI2C注册管理功能 #####
 ===============================================================================
    [..] 本节提供了允许用户管理FMPI2C 寄存器的功能。

@endverbatim
  */

/**
* 简介:  读取指定的 FMPI2C 寄存器并返回其值。
* 
* 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
* 
* 参数:  FMPI2C_Register: 指定要读取的寄存器。
*   此参数可以是以下值之一:
*     @arg FMPI2C_Register_CR1: CR1 寄存器.
*     @arg FMPI2C_Register_CR2: CR2 寄存器.
*     @arg FMPI2C_Register_OAR1: OAR1 寄存器.
*     @arg FMPI2C_Register_OAR2: OAR2 寄存器.
*     @arg FMPI2C_Register_TIMINGR: TIMING 寄存器.
*     @arg FMPI2C_Register_TIMEOUTR: TIMEOUTR 寄存器.
*     @arg FMPI2C_Register_ISR: ISR 寄存器.
*     @arg FMPI2C_Register_ICR: ICR 寄存器.
*     @arg FMPI2C_Register_PECR: PECR 寄存器.
*     @arg FMPI2C_Register_RXDR: RXDR 寄存器.
*     @arg FMPI2C_Register_TXDR: TXDR 寄存器.
* 
* 返回值: 读取寄存器的值。
*/
uint32_t FMPI2C_ReadRegister(FMPI2C_TypeDef* FMPI2Cx, uint8_t FMPI2C_Register) {
    __IO uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_REGISTER(FMPI2C_Register));

    tmp = (uint32_t)FMPI2Cx;
    tmp += FMPI2C_Register;

    /* 返回selected寄存器值 */
    return (*(__IO uint32_t *) tmp);
}


/** @defgroup FMPI2C_Group5 数据传输管理功能
 *  简介   数据传输管理功能
 *
@verbatim
 ===============================================================================
                ##### 数据传输管理功能 #####
 ===============================================================================
    [..] 本小节提供了一组允许管理FMPI2C 数据传输的功能。

    [..] FMPI2C_RXDR 寄存器的读取访问可以使用 FMPI2S_ReceiveData() 函数完成，并返回接收的值。
         然而，可以使用 FMPI2C_SendData() 函数对FMPI2T_TXDR进行写入访问，并将写入的数据存储到 TXDR 中。
@endverbatim
  */

/**
  * 简介:  通过 FMPI2Cx 外设发送一个数据字节。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  Data: 要传输的字节。
  * 
  * 返回值: 无
  */
void FMPI2C_SendData(FMPI2C_TypeDef* FMPI2Cx, uint8_t Data) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));

    /* 在 DR 寄存器中写入要发送的数据 */
    FMPI2Cx->TXDR = (uint8_t)Data;
}

/**
  * 简介:  返回 FMPI2Cx 外设最近接收的数据。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 返回值: The value of 接收的数据。
  */
uint8_t FMPI2C_ReceiveData(FMPI2C_TypeDef* FMPI2Cx) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));

    /* 返回data in the DR 寄存器 */
    return (uint8_t)FMPI2Cx->RXDR;
}



/** @defgroup FMPI2C_Group6 DMA 传输管理功能
 *  简介   DMA 传输管理功能
 *
@verbatim
 ===============================================================================
               ##### DMA 传输管理功能 #####
 ===============================================================================
    [..] 本节提供了两个只能在 DMA 模式下使用的函数。

    [..] 在 DMA 模式下，FMPI2C 通信可通过2个 DMA 信道请求进行管理:
         (#) FMPI2C_DMAReq_Tx: 指定 Tx 缓冲器 DMA 传输请求。
         (#) FMPI2C_DMAReq_Rx: 指定 Rx 缓冲器 DMA 传输请求。

    [..] 在此模式下，建议使用以下函数:
         (+) FMPI2C_DMACmd(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_DMAReq, FunctionalState NewState);
@endverbatim
  */

/**
  * 简介:  启用或禁用 FMPI2C DMA 接口.
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  FMPI2C_DMAReq: 指定要启用或禁用的 FMPI2C DMA 传输请求。
  *   此参数可以是以下值的任意组合:
  *     @arg FMPI2C_DMAReq_Tx: Tx DMA 传输请求
  *     @arg FMPI2C_DMAReq_Rx: Rx DMA 传输请求
  * 
  * 参数:  NewState: 所选FMPI2C DMA 传输请求的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMPI2C_DMACmd(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_DMAReq, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_FMPI2C_DMA_REQ(FMPI2C_DMAReq));

    if (NewState != DISABLE) {
        /* 启用被选定的 FMPI2C DMA 请求 */
        FMPI2Cx->CR1 |= FMPI2C_DMAReq;
    } else {
        /* 禁用被选中的 FMPI2C DMA 请求 */
        FMPI2Cx->CR1 &= (uint32_t)~FMPI2C_DMAReq;
    }
}


/** @defgroup FMPI2C_Group7 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
             ##### 中断和标记管理函数  #####
 ===============================================================================
    [..] 本节提供的功能允许配置 FMPI2C 中断源，检查或清除标志或挂起位状态。
         用户应确定其应用程序将使用哪种模式来管理通信:
            轮询模式、中断模式或 DMA 模式(参见FMPI2C_Group6)。

  *** 轮询模式 ***
  ====================
    [..] 在轮询模式下，FMPI2C 通信可以由15个标志来管理。
        (#) FMPI2C_FLAG_TXE:表示发送数据寄存器空的状态标志。
        (#) FMPI2C_FLAG_TXIS:表示传输中断状态标志的状态。
        (#) FMPI2C_FLAG_RXNE: 表示接收数据寄存器非空标志的状态。
        (#) FMPI2C_FLAG_ADDR: 表示地址匹配标志的状态(从机模式)。
        (#) FMPI2C_FLAG_NACKF: 指示接收到 NACK标志的状态。
        (#) FMPI2C_FLAG_STOPF: 指示 STOP检测标志的状态。
        (#) FMPI2C_FLAG_TC: 指示传输完成标志的状态(主模式)。
        (#) FMPI2C_FLAG_TCR: 用于指示传输完成重载标志的状态。
        (#) FMPI2C_FLAG_BERR: 指示总线错误标志的状态。
        (#) FMPI2C_FLAG_ARLO: 指示仲裁失败标志的状态。
        (#) FMPI2C_FLAG_OVR: 指示超速/欠速标志的状态。
        (#) FMPI2C_FLAG_PECERR: 指示接收中的PEC 错误标志的状态。
        (#) FMPI2C_FLAG_TIMEOUT:表示超时或低速检测标志的状态。
        (#) FMPI2C_FLAG_ALERT: 指示 SMBus 警报标志的状态。
        (#) FMPI2C_FLAG_BUSY: 指示总线繁忙标志的状态。

    [..] 在这种模式下，建议使用以下函数:
        (+) FlagStatus FMPI2C_GetFlagStatus(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_FLAG);
        (+) void FMPI2C_ClearFlag(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_FLAG);

    [..]
        (@)不要使用BUSY 标志来处理每个数据传输或接收。最好使用 TXIS 和 RXNE 标志来代替。

  *** Interrupt Mode ***
  ======================
    [..] 在中断模式下，FMPI2C 通信可以由7个中断源和15个待处理位来管理。
    [..] 中断源:
        (#) FMPI2C_IT_ERRI:指定错误中断的中断源。
        (#) FMPI2C_IT_TCI: 指定传输完成中断的中断源。
        (#) FMPI2C_IT_STOPI: 指定停止检测中断的中断源。
        (#) FMPI2C_IT_NACKI: 指定未收到确认中断的中断源。
        (#) FMPI2C_IT_ADDRI: 指定地址匹配中断的中断源。
        (#) FMPI2C_IT_RXI: 指定 RX 中断的中断源。
        (#) FMPI2C_IT_TXI: 指定 TX 中断的中断源。

    [..] Pending Bits:
        (#) FMPI2C_IT_TXIS:表示传输中断状态标志的状态。
        (#) FMPI2C_IT_RXNE:表示接收数据寄存器非空标志的状态。
        (#) FMPI2C_IT_ADDR: 指示地址匹配标志的状态(从属模式)。
        (#) FMPI2C_IT_NACKF: 指示接收到 NACK标志的状态。
        (#) FMPI2C_IT_STOPF: 指示 STOP检测标志的状态。
        (#) FMPI2C_IT_TC: 指示传输完成标志的状态(主模式)。
        (#) FMPI2C_IT_TCR:表示传输完成重载标志的状态。
        (#) FMPI2C_IT_BERR: 指示总线错误标志的状态。
        (#) FMPI2C_IT_ARLO: 指示仲裁失败标志的状态。
        (#) FMPI2C_IT_OVR: 指示超速/欠速标志的状态。
        (#) FMPI2C_IT_PECERR: 指示接收中的PEC 错误标志的状态。
        (#) FMPI2C_IT_TIMEOUT:表示超时或低速检测标志的状态。
        (#) FMPI2C_IT_ALERT: 指示 SMBus 警报标志的状态。

    [..] 在这种模式下，建议使用以下函数:
         (+) void FMPI2C_ClearITPendingBit(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_IT);
         (+) ITStatus FMPI2C_GetITStatus(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_IT);

@endverbatim
  */

/**
  * 简介:  检查是否设置了指定的 FMPI2C 标志。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  FMPI2C_FLAG: 指定要检查的标志。
  *   此参数可以是以下值之一:
  *       @arg FMPI2C_FLAG_TXE: 传输数据寄存器为空
  *       @arg FMPI2C_FLAG_TXIS: 传输中断状态
  *       @arg FMPI2C_FLAG_RXNE: 接收数据寄存器不为空
  *       @arg FMPI2C_FLAG_ADDR: 地址匹配(从机模式)
  *       @arg FMPI2C_FLAG_NACKF: 收到 NACK标志
  *       @arg FMPI2C_FLAG_STOPF: STOP检测标志
  *       @arg FMPI2C_FLAG_TC: 传输完成(主模式)
  *       @arg FMPI2C_FLAG_TCR: 传输完成重载
  *       @arg FMPI2C_FLAG_BERR: 总线错误
  *       @arg FMPI2C_FLAG_ARLO: 仲裁丢失。
  *       @arg FMPI2C_FLAG_OVR: 超限/不足
  *       @arg FMPI2C_FLAG_PECERR: 接收时出现PEC 错误。
  *       @arg FMPI2C_FLAG_TIMEOUT: 超时或 Tlow检测标志
  *       @arg FMPI2C_FLAG_ALERT: SMBus 警报
  *       @arg FMPI2C_FLAG_BUSY: 总线繁忙。
  * 
  * 返回值: FMPI2C_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus FMPI2C_GetFlagStatus(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_FLAG) {
    uint32_t tmpreg = 0;
    FlagStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_GET_FLAG(FMPI2C_FLAG));

    /* 获取 ISr 寄存器值 */
    tmpreg = FMPI2Cx->ISR;

    /* 获取 flag 状态 */
    tmpreg &= FMPI2C_FLAG;

    if(tmpreg != 0) {
        /* FMPI2C_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* FMPI2C_FLAG  被重置 */
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 FMPI2Cx 的挂起标志。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  FMPI2C_FLAG: 指定要清除的标志。
  *   此参数可以是以下值的任意组合:
  *      @arg FMPI2C_FLAG_ADDR:地址匹配(从属模式)
  *      @arg FMPI2C_FLAG_NACKF:NACK收到标志
  *      @arg FMPI2C_FLAG_STOPF:停止检测标志
  *      @arg FMPI2C_FLAG_BERR: 总线错误
  *      @参数FMPI2C_FLAG_ARLO:仲裁丢失.
  *      @arg FMPI2C_FLAG_OVR:超限/不足
  *      @arg FMPI2C_FLAG_PECERR:接收时出现PEC 错误
  *      @arg FMPI2C_FLAG_TIMEOUT:超时或 Tlow检测标志
  *      @arg FMPI2C_FLAG_ALERT: SMBus 警报
  * 
  * 返回值: FMPI2C_FLAG 的新状态(SET 或 RESET)。
  */
void FMPI2C_ClearFlag(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_FLAG) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_CLEAR_FLAG(FMPI2C_FLAG));

    /* 清除被选择的 flag */
    FMPI2Cx->ICR = FMPI2C_FLAG;
}

/**
  * 简介:  检查是否发生了指定的 FMPI2C 中断。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  FMPI2C_IT: 指定要检查的中断源。
  *   此参数可以是以下值之一:
  *     @arg FMPI2C_IT_TXIS: 传输中断status
  *     @arg FMPI2C_IT_RXNE: 接收数据寄存器不为空
  *     @arg FMPI2C_IT_NACKF: 收到 NACK标志
  *     @arg FMPI2C_IT_STOPF: STOP检测标志
  *     @arg FMPI2C_IT_TC: 传输完成(主模式)
  *     @arg FMPI2C_IT_TCR: 传输完成重新加载
  *     @arg FMPI2C_IT_BERR: 总线错误
  *     @arg FMPI2C_IT_ARLO: 仲裁丢失。
  *     @arg FMPI2C_IT_OVR: 超限/不足
  *     @arg FMPI2C_IT_PECERR: PEC在接收时出错。
  *     @arg FMPI2C_IT_TIMEOUT: 超时或 Tlow检测标志
  *     @arg FMPI2C_IT_ALERT: SMBus 警报
  * 
  * 返回值。FMPI2C_IT 的新状态(SET 或 RESET)。
  */
ITStatus FMPI2C_GetITStatus(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_IT) {
    uint32_t tmpreg = 0;
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_GET_IT(FMPI2C_IT));

    /* 检查中断源是否启用 */
    /* If Error 中断 */
    if((uint32_t)(FMPI2C_IT & ERROR_IT_MASK)) {
        enablestatus = (uint32_t)((FMPI2C_CR1_ERRIE) & (FMPI2Cx->CR1));
    }
    /* If TC 中断 */
    else if((uint32_t)(FMPI2C_IT & TC_IT_MASK)) {
        enablestatus = (uint32_t)((FMPI2C_CR1_TCIE) & (FMPI2Cx->CR1));
    } else {
        enablestatus = (uint32_t)((FMPI2C_IT) & (FMPI2Cx->CR1));
    }

    /* 获取 ISr 寄存器值 */
    tmpreg = FMPI2Cx->ISR;

    /* Get flag 状态 */
    tmpreg &= FMPI2C_IT;

    /* 检查指定的 FMPI2C 标志的状态 */
    if((tmpreg != RESET) && enablestatus) {
        /* FMPI2C_IT 被设置 */
        bitstatus = SET;
    } else {
        /* FMPI2C_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回FMPI2C_IT 状态 */
    return bitstatus;
}

/**
  * 简介:  清除 FMPI2Cx 的中断挂起位。
  * 
  * 参数:  FMPI2Cx: 其中 x 可以是1，选择 FMPI2C 的外设。
  * 
  * 参数:  FMPI2C_IT: 指定要清除的中断等待位。
  *   此参数可以是以下值的任意组合:
  *         @arg FMPI2C_IT_ADDR: 地址匹配(从属模式)。
  *         @arg FMPI2C_IT_NACKF: 收到 NACK标志
  *         @arg FMPI2C_IT_STOPF: STOP检测标志
  *         @arg FMPI2C_IT_BERR: 总线错误
  *         @arg FMPI2C_IT_ARLO: 仲裁丢失。
  *         @arg FMPI2C_IT_OVR: 超限/不足
  *         @arg FMPI2C_IT_PECERR: PEC在接收时出错。
  *         @arg FMPI2C_IT_TIMEOUT: 超时或 Tlow检测标志
  *         @arg FMPI2C_IT_ALERT: SMBus 警报
  * 
  * 返回值: FMPI2C_IT 的新状态(SET 或 RESET)。
  */
void FMPI2C_ClearITPendingBit(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_IT) {
    /* 检查参数 */
    assert_param(IS_FMPI2C_ALL_PERIPH(FMPI2Cx));
    assert_param(IS_FMPI2C_CLEAR_IT(FMPI2C_IT));

    /* 清除被选择的 flag */
    FMPI2Cx->ICR = FMPI2C_IT;
}


#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
