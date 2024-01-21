/**
  ******************************************************************************
  * 文件:    stm32f4xx_i2c.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能，以管理集成电路(I2C)的下列功能
  *           + 初始化和配置
  *           + 数据传输
  *           + PEC 管理
  *           + DMA传输管理
  *           + 中断、事件和标志管理
  *
    @verbatim
 ===============================================================================
                    ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..]
      (#) 使用RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2Cx, ENABLE)函数为I2C1、I2C2或I2C3启用外围时钟。

      (#) 使用以下方法启用SDA、SCL和SMBA(当使用时)的GPIO时钟
          RCC_AHBPeriphClockCmd()函数。

      (#) 外设设备替代函数。
        (++) 使用GPIO_PinAFConfig()函数将引脚连接到所需的外设设备的替代功能(AF)。

        (++) 通过配置所需引脚的复用功能。
             GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF

        (++) 通过GPIO_PuPd、GPIO_OType和GPIO_Speed成员选择类型、上拉/下拉和输出速度
        
        (++) 调用GPIO_Init()函数
             建议配置为推挽、拉升、开漏。
             如果有必要的话，可以添加一个外部拉高(通常是4.7KOhm)。

      (#) 对模式、占空比、自己的地址、Ack、速度和Acknowledged地址进行编程。
          使用I2C_Init()函数对模式、占空比、自身地址、Ack、速度和确认地址进行编程。

      (#) 你可以选择启用/配置以下参数而不需要重新初始化(即不需要再次调用 I2C_Init() 函数)。
        (++) 使用 I2C_AcknowledgeConfig() 函数启用确认功能。
        (++) 使用 I2C_DualAddressCmd() 函数启用双寻址模式。
        (++) 使用 I2C_GeneralCallCmd() 函数启用一般调用功能
        (++) 使用 I2C_StretchClockCmd() 函数启用时钟拉伸功能
        (++) 使用 I2C_FastModeDutyCycleConfig() 函数启用快速模式占空比。
        (++) 使用 I2C_NACKPositionConfig() 函数配置主接收模式下的 NACK 位置，即 2 个字节的接收情况。
        (++) 使用 I2C_CalculatePEC() 函数启用 PEC 计算。
        (++) 对于 SMBus 模式。
        (++) 使用 I2C_ARPCmd() 函数启用地址解析协议(ARP)。
        (++) 使用 I2C_SMBusAlertConfig() 函数配置 SMBusAlert 引脚

      (#) 如果需要使用中断模式，使用函数 I2C_ITConfig() 启用 NVIC 和相应的中断。

      (#) 当使用 DMA 模式时
        (++) 使用 DMA_Init() 函数配置DMA
        (++) 使用 I2C_DMACmd() 函数激活所需的通道请求，或使用
             I2C_DMALastTransferCmd() 函数激活需要的通道请求。
        -@@- 当使用DMA模式时，可以同时使用 I2C 中断来控制通信流(开始/停止/确认...事件和错误)。

      (#) 使用 I2C_Cmd() 函数启用 I2C。

      (#) 在传输中使用DMA模式时，使用 DMA_Cmd() 函数启用 DMA。

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
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C
  * 简介: I2C 驱动模块
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

#define CR1_CLEAR_MASK    ((uint16_t)0xFBF5)      /*<! I2C registers Masks */
#define FLAG_MASK         ((uint32_t)0x00FFFFFF)  /*<! I2C FLAG mask */
#define ITEN_MASK         ((uint32_t)0x07000000)  /*<! I2C Interrupt Enable mask */

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup I2C_Private_Functions
  * @{
  */

/** @defgroup I2C_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
            ##### 初始化和配置函数 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  将I2Cx外设寄存器取消初始化为其默认复位值。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 返回值: 无
  */
void I2C_DeInit(I2C_TypeDef* I2Cx) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    if (I2Cx == I2C1) {
        /* 使能I2C1复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
        /* 释放I2C1 from 复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
    } else if (I2Cx == I2C2) {
        /* 使能I2C2复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
        /* 释放I2C2 from 复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
    } else {
        if (I2Cx == I2C3) {
            /* 使能I2C3复位状态 */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C3, ENABLE);
            /* 释放I2C3 from 复位状态 */
            RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C3, DISABLE);
        }
    }
}

/**
  * 简介:  根据I2C_InitStruct中的指定参数初始化I2Cx外设。
  *
  * 注意:  要在400KHz(快速模式)下使用I2C，PCLK1的频率(I2C外围输入时钟)必须是10MHz的倍数。
  *
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 参数:  I2C_InitStruct: 指向I2C_InitTypeDef结构的指针，该结构包含指定I2C外设的配置信息。
  * 
  * 返回值: 无
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct) {
    uint16_t tmpreg = 0, freqrange = 0;
    uint16_t result = 0x04;
    uint32_t pclk1 = 8000000;
    RCC_ClocksTypeDef  rcc_clocks;
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));
    assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
    assert_param(IS_I2C_DUTY_CYCLE(I2C_InitStruct->I2C_DutyCycle));
    assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddress1));
    assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->I2C_Ack));
    assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AcknowledgedAddress));

    /*---------------------------- I2Cx CR2 配置 ------------------------*/
    /* 获取I2Cx CR2 值 */
    tmpreg = I2Cx->CR2;
    /* 清除频率 FREQ[5:0] 位 */
    tmpreg &= (uint16_t)~((uint16_t)I2C_CR2_FREQ);
    /* 获得 pclk1 频率值 */
    RCC_GetClocksFreq(&rcc_clocks);
    pclk1 = rcc_clocks.PCLK1_Frequency;
    /* 根据pclk1设置频率位值 */
    freqrange = (uint16_t)(pclk1 / 1000000);
    tmpreg |= freqrange;
    /* 写入I2Cx CR2 */
    I2Cx->CR2 = tmpreg;

    /*---------------------------- I2Cx CCR 配置 ------------------------*/
    /* 禁用选择I2C外设配置TRISE */
    I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_PE);
    /* Reset tmpreg 值 */
    /* 清除 F/S, DUTY and CCR[11:0] 位 */
    tmpreg = 0;

    /* 在标准模式下配置速度 */
    if (I2C_InitStruct->I2C_ClockSpeed <= 100000) {
        /* 标准模式速度计算 */
        result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));

        /* 测试CCR值是否低于0x4*/
        if (result < 0x04) {
            /* 设置允许的最小值 */
            result = 0x04;
        }

        /* 设置标准模式的速度值 */
        tmpreg |= result;
        /* 设置标准模式的最大上升时间 */
        I2Cx->TRISE = freqrange + 1;
    }
    /* 在快速模式下配置速度 */
    /* 要使用400 KHz的I2C(在快速模式下)，PCLK1频率(I2C外围设备输入时钟)必须是10 MHz的倍数 */
    else { /*(I2C_InitStruct->I2C_ClockSpeed <= 400000)*/
        if (I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_2) {
            /* 快速模式速度计算: Tlow/Thigh = 2 */
            result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 3));
        } else { /*I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_16_9*/
            /* 快速模式速度计算: Tlow/Thigh = 16/9 */
            result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 25));
            /* Set DUTY 位 */
            result |= I2C_DutyCycle_16_9;
        }

        /* 测试CCR值是否低于0x1*/
        if ((result & I2C_CCR_CCR) == 0) {
            /* 设置允许的最小值 */
            result |= (uint16_t)0x0001;
        }

        /* 为快速模式设置速度值和F/S位 */
        tmpreg |= (uint16_t)(result | I2C_CCR_FS);
        /* 设置快速模式的最大上升时间 */
        I2Cx->TRISE = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
    }

    /* 写入I2Cx CCR */
    I2Cx->CCR = tmpreg;
    /* 启用被选定的 I2C 外设 */
    I2Cx->CR1 |= I2C_CR1_PE;

    /*---------------------------- I2Cx CR1 配置 ------------------------*/
    /* 获取I2Cx CR1 值 */
    tmpreg = I2Cx->CR1;
    /* 清除 ACK, SMBTYPE and  SMBUS 位 */
    tmpreg &= CR1_CLEAR_MASK;
    /* 配置I2Cx：模式和确认 */
    /* 根据I2C_Mode设置SMBTYPE和SMBUS位值 */
    /* 根据I2C_ACK设置ACK位值 */
    tmpreg |= (uint16_t)((uint32_t)I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack);
    /* 写入I2Cx CR1 */
    I2Cx->CR1 = tmpreg;

    /*---------------------------- I2Cx OAR1 配置 -----------------------*/
    /* Set I2Cx 自有地址1和确认地址 */
    I2Cx->OAR1 = (I2C_InitStruct->I2C_AcknowledgedAddress | I2C_InitStruct->I2C_OwnAddress1);
}

/**
  * 简介:  用每个I2C_InitStruct成员的默认值填充其默认值。
  * 
  * 参数:  I2C_InitStruct: 指向I2C_InitTypeDef结构的指针，将被初始化。
  * 
  * 返回值: 无
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct) {
    /*---------------- Reset I2C init structure parameters values ----------------*/
    /* 初始化 I2C_ClockSpeed 成员 */
    I2C_InitStruct->I2C_ClockSpeed = 5000;
    /* 初始化 I2C_Mode 成员 */
    I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
    /* 初始化 I2C_DutyCycle 成员 */
    I2C_InitStruct->I2C_DutyCycle = I2C_DutyCycle_2;
    /* 初始化 I2C_OwnAddress1 成员 */
    I2C_InitStruct->I2C_OwnAddress1 = 0;
    /* 初始化 I2C_Ack 成员 */
    I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
    /* 初始化 I2C_AcknowledgedAddress 成员 */
    I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}

/**
  * 简介:  启用或禁用指定的 I2C 外设.
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: 新状态-> I2Cx 外设.
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 I2C 外设 */
        I2Cx->CR1 |= I2C_CR1_PE;
    } else {
        /* 禁用被选中的 I2C 外设 */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_PE);
    }
}

/**
  * 简介:  启用或禁用Analog filter of I2C 外设.
  *
  * 注意:   该功能只能用于STM32F42xxx/STM3243xxx、STM32F401xx、STM32F410xx和STM32F411xE器件。
  *
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: 新的模拟状态的过滤器。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 注意:   这个函数应该在初始化和启用 I2C外设。
  * 
  * 返回值: 无
  */
void I2C_AnalogFilterCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 模拟滤波器 */
        I2Cx->FLTR &= (uint16_t)~((uint16_t)I2C_FLTR_ANOFF);
    } else {
        /* 禁用 模拟滤波器 */
        I2Cx->FLTR |= I2C_FLTR_ANOFF;
    }
}

/**
  * 简介:  配置 I2C 外设的数字噪声滤波器。
  *
  * 注意:   该功能只能用于STM32F42xxx/STM3243xxx、STM32F401xx、STM32F410xx和STM32F411xE器件。
  *
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_DigitalFilter: 数字噪音过滤器的系数。
  *          这个参数可以是0x00到0x0F之间的数字。
  * 
  * 注意:   这个函数应该在初始化和启用 I2C外设。
  * 
  * 返回值: 无
  */
void I2C_DigitalFilterConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DigitalFilter) {
    uint16_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_DIGITAL_FILTER(I2C_DigitalFilter));

    /* 获取old寄存器值 */
    tmpreg = I2Cx->FLTR;

    /* 重置 I2Cx DNF bit [3:0] */
    tmpreg &= (uint16_t)~((uint16_t)I2C_FLTR_DNF);

    /* 设置 I2Cx DNF coefficient */
    tmpreg |= (uint16_t)((uint16_t)I2C_DigitalFilter & I2C_FLTR_DNF);

    /* 存储新的寄存器值 */
    I2Cx->FLTR = tmpreg;
}

/**
  * 简介:  生成 I2Cx 通信启动条件。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2C START条件生成的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无.
  */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 生成START条件 */
        I2Cx->CR1 |= I2C_CR1_START;
    } else {
        /* 禁用START条件生成 */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_START);
    }
}

/**
  * 简介:  生成 I2Cx 通信停止条件。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: 产生I2C STOP条件的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无.
  */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 生成STOP条件 */
        I2Cx->CR1 |= I2C_CR1_STOP;
    } else {
        /* 禁用STOP条件生成 */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_STOP);
    }
}

/**
  * 简介:  传输地址字节以选择从设备。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  Address: 指定将被传送的从属地址
  * 
  * 参数:  I2C_Direction: 指定I2C设备是发射器还是接收器。
  *          该参数可以是以下值之一:
  *            @arg I2C_Direction_Transmitter: 发射器模式
  *            @arg I2C_Direction_Receiver: 接收器模式
  * 
  * 返回值: 无.
  */
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_DIRECTION(I2C_Direction));

    /* 测试设置/重置读/写的方向位 */
    if (I2C_Direction != I2C_Direction_Transmitter) {
        /* 设置用于读取的地址位0 */
        Address |= I2C_OAR1_ADD0;
    } else {
        /* 重设写入地址位0 */
        Address &= (uint8_t)~((uint8_t)I2C_OAR1_ADD0);
    }

    /* 发送地址 */
    I2Cx->DR = Address;
}

/**
  * 简介:  启用或禁用指定的 I2C 认可的特点。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2C确认的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无.
  */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用确认 */
        I2Cx->CR1 |= I2C_CR1_ACK;
    } else {
        /* 禁用确认 */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_ACK);
    }
}

/**
  * 简介:  配置指定的 I2C 自己的地址2。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  Address: 指定7位I2C自己的地址2。
  * 
  * 返回值: 无.
  */
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address) {
    uint16_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    /* 获取old寄存器值 */
    tmpreg = I2Cx->OAR2;

    /* Reset I2Cx Own address2 bit [7:1] */
    tmpreg &= (uint16_t)~((uint16_t)I2C_OAR2_ADD2);

    /* Set I2Cx Own address2 */
    tmpreg |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);

    /* 存储新的寄存器值 */
    I2Cx->OAR2 = tmpreg;
}

/**
  * 简介:  启用或禁用指定的 I2C 双寻址模式。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2C双寻址模式的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能双寻址模式 */
        I2Cx->OAR2 |= I2C_OAR2_ENDUAL;
    } else {
        /*禁用双寻址模式*/
        I2Cx->OAR2 &= (uint16_t)~((uint16_t)I2C_OAR2_ENDUAL);
    }
}

/**
  * 简介:  启用或禁用指定的 I2C 常规调用功能。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2C一般调用的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能general call */
        I2Cx->CR1 |= I2C_CR1_ENGC;
    } else {
        /*禁用常规呼叫*/
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_ENGC);
    }
}

/**
  * 简介:  启用或禁用指定的 I2C 软件复位.
  * 
  * 注意:   当软件复位被启用时，I2C IO被释放(这对于从总线错误中恢复很有用)。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2C软件复位的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 外设处于重置状态 */
        I2Cx->CR1 |= I2C_CR1_SWRST;
    } else {
        /* 外设设备未重置 */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_SWRST);
    }
}

/**
  * 简介:  启用或禁用指定的 I2C 时钟拉伸。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2Cx时钟拉伸的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState == DISABLE) {
        /* 启用被选定的 I2C Clock stretching */
        I2Cx->CR1 |= I2C_CR1_NOSTRETCH;
    } else {
        /* 禁用被选中的 I2C Clock stretching */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_NOSTRETCH);
    }
}

/**
  * 简介:  选择指定的 I2C 快速模式占空比。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_DutyCycle: 指定快速模式的占空比。
  *          此参数可以是以下值之一:
  *            @arg I2C_DutyCycle_2: I2C fast mode Tlow/Thigh = 2
  *            @arg I2C_DutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9
  * 
  * 返回值: 无
  */
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));

    if (I2C_DutyCycle != I2C_DutyCycle_16_9) {
        /* I2C 快速模式 Tlow/Thigh=2 */
        I2Cx->CCR &= I2C_DutyCycle_2;
    } else {
        /* I2C 快速模式 Tlow/Thigh=16/9 */
        I2Cx->CCR |= I2C_DutyCycle_16_9;
    }
}

/**
  * 简介:  在主接收机模式下选择指定的 I2C NACK 位置。
  * 
  * 注意:   此功能在I2C主机中很有用接收器模式 当要接收的数据数量等于2时。
  *         在这种情况下，应在数据接收开始之前调用此函数(使用参数I2C_NACKPosition_Next)，
  *         如参考手册第节:主接收器中推荐的2字节接收程序所述。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_NACKPosition: 指定NACK位置。
  *          此参数可以是以下值之一:
  *            @arg I2C_NACKPosition_Next: 指示下一个字节将是最后接收的字节。
  *            @arg I2C_NACKPosition_Current: 指示当前字节是最后接收的字节。
  *
  * 注意:    此函数配置与I2C_PECPositionConfig()相同的位(POS)，
  *          但用于I2C模式，而I2C_pECPositionConfiguration()用于SMBUS模式。
  *
  * 返回值: 无
  */
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_NACK_POSITION(I2C_NACKPosition));

    /* 检查输入参数 */
    if (I2C_NACKPosition == I2C_NACKPosition_Next) {
        /* 移位寄存器中的下一个字节是最后接收的字节 */
        I2Cx->CR1 |= I2C_NACKPosition_Next;
    } else {
        /* 移位寄存器中的当前字节是最后接收到的字节 */
        I2Cx->CR1 &= I2C_NACKPosition_Current;
    }
}

/**
  * 简介:  针对指定的 I2C 将 SMBusAlert 引脚驱动至高电平或低电平。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_SMBusAlert: 指定SMBAlert引脚级别。
  *          此参数可以是以下值之一:
  *            @arg I2C_SMBusAlert_Low: SMBAlert引脚驱动低
  *            @arg I2C_SMBusAlert_High: SMBAlert引脚驱动高
  * 
  * 返回值: 无
  */
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_SMBUS_ALERT(I2C_SMBusAlert));

    if (I2C_SMBusAlert == I2C_SMBusAlert_Low) {
        /* 将SMBusAlert引脚驱动为低 */
        I2Cx->CR1 |= I2C_SMBusAlert_Low;
    } else {
        /* 将SMBusAlert引脚驱动为高  */
        I2Cx->CR1 &= I2C_SMBusAlert_High;
    }
}

/**
  * 简介:  启用或禁用指定的 I2C ARP.
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2Cx ARP的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 I2C ARP */
        I2Cx->CR1 |= I2C_CR1_ENARP;
    } else {
        /* 禁用被选中的 I2C ARP */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_ENARP);
    }
}
/**
  * @}
  */

/** @defgroup I2C_Group2 数据传输函数
 *  简介   数据传输函数
 *
@verbatim
 ===============================================================================
                  ##### 数据传输函数 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  通过 I2Cx 外设发送一个数据字节。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  Data: 要传输的字节。
  * 
  * 返回值: 无
  */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* 在DR寄存器中写入要发送的数据 */
    I2Cx->DR = Data;
}

/**
  * 简介:  返回 I2Cx 外设最近接收到的数据。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 返回值: The value of 接收的数据。
  */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* 返回data in the DR 寄存器 */
    return (uint8_t)I2Cx->DR;
}

/**
  * @}
  */

/** @defgroup I2C_Group3 PEC 管理函数
 *  简介   PEC 管理函数
 *
@verbatim
 ===============================================================================
                  ##### PEC 管理函数 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  启用或禁用指定的 I2C PEC 传输.
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2C PEC传输的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的I2C PEC 传输 */
        I2Cx->CR1 |= I2C_CR1_PEC;
    } else {
        /* 禁用被选中的 I2C PEC 传输 */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_PEC);
    }
}

/**
  * 简介:  选择指定的 I2C PEC 位置。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_PECPosition: 指定PEC位置。
  *          此参数可以是以下值之一:
  *            @arg I2C_PECPosition_Next: 表示下一个字节是PEC
  *            @arg I2C_PECPosition_Current: 表示当前字节为PEC
  *
  * 注意:    此函数配置与I2C_NACKPositionConfig()相同的位(POS)，
  *          但用于SMBUS模式，而I2C_nACKPositConfig(()用于I2C模式。
  *
  * 返回值: 无
  */
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_PEC_POSITION(I2C_PECPosition));

    if (I2C_PECPosition == I2C_PECPosition_Next) {
        /* 移位寄存器中的下一个字节是PEC */
        I2Cx->CR1 |= I2C_PECPosition_Next;
    } else {
        /* 移位寄存器中的当前字节为PEC */
        I2Cx->CR1 &= I2C_PECPosition_Current;
    }
}

/**
  * 简介:  启用或禁用传输字节的 PEC 值计算。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2Cx PEC值计算的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 I2C PEC 计算 */
        I2Cx->CR1 |= I2C_CR1_ENPEC;
    } else {
        /* 禁用被选中的 I2C PEC 计算 */
        I2Cx->CR1 &= (uint16_t)~((uint16_t)I2C_CR1_ENPEC);
    }
}

/**
  * 简介:  返回指定 I2C 的 PEC 值。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 返回值: The PEC value.
  */
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* 返回被选择的 I2C PEC 值 */
    return ((I2Cx->SR2) >> 8);
}

/**
  * @}
  */

/** @defgroup I2C_Group4 DMA传输管理函数
 *  简介   DMA传输管理函数
 *
@verbatim
 ===============================================================================
                ##### DMA传输管理函数 #####
 ===============================================================================
  本节提供的功能允许配置I2C DMA信道请求。

@endverbatim
  * @{
  */

/**
  * 简介:  启用或禁用指定的 I2C DMA 请求.
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2C DMA传输的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 I2C DMA 请求 */
        I2Cx->CR2 |= I2C_CR2_DMAEN;
    } else {
        /* 禁用被选中的 I2C DMA 请求 */
        I2Cx->CR2 &= (uint16_t)~((uint16_t)I2C_CR2_DMAEN);
    }
}

/**
  * 简介:  指定下一次 DMA 传输是最后一次传输。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  NewState: I2C DMA最后一次传输的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 下一次DMA传输是最后一次传输 */
        I2Cx->CR2 |= I2C_CR2_LAST;
    } else {
        /* 下一次DMA传输不是最后一次传输 */
        I2Cx->CR2 &= (uint16_t)~((uint16_t)I2C_CR2_LAST);
    }
}

/**
  * @}
  */

/** @defgroup I2C_Group5 中断、事件和标志管理功能
 *  简介   中断、事件和标志管理功能
 *
@verbatim
 ===============================================================================
          ##### 中断、事件和标志管理功能#####
 ===============================================================================
    [..]
    本节提供的功能允许 配置I2C中断源，并检查或清除标志位或待定位状态。
    用户应该确定在他的应用程序中使用哪种模式来管理通信。轮询模式、中断模式或DMA模式。


                ##### I2C状态监测功能 #####
 ===============================================================================
    [..]
该I2C驱动提供了三种不同的I2C状态监测方式，这取决于应用的要求和限制。


     (#) 基本状态监测(使用I2C_CheckEvent()函数)

        它将状态寄存器(SR1和SR2)的内容与一个给定的事件(可以是一个或多个标志的组合)进行比较。
        如果当前状态包括给定的标志，它将返回SUCCESS，如果当前状态中缺少一个或多个标志，则返回ERROR。

          (++)何时使用
             (++) 这个函数适用于大多数应用以及启动活动，因为事件在产品参考手册(RM0090)中有完整的描述。
             (++) 它也适用于需要定义自己的事件的用户。

          (++)局限性
               如果发生错误(即除了被监控的标志外还设置了错误标志)，I2C_CheckEvent()函数可能会返回SUCCESS，尽管通信保持或现实状态被破坏。
               在这种情况下，建议使用错误中断来监测错误事件，并在中断IRQ处理程序中处理它们。

     -@@- 对于错误管理，建议使用以下函数。
        (+@@) I2C_ITConfig() 配置并启用错误中断(I2C_IT_ERR)。
        (+@@) I2Cx_ER_IRQHandler()，当错误中断发生时被调用。
              其中x是外设实例(I2C1, I2C2 ...)。
        (+@@) I2C_GetFlagStatus()或I2C_GetITStatus()被调用到I2Cx_ER_IRQHandler()函数中，以确定哪个错误发生。
        (+@@) I2C_ClearFlag() 或 I2C_ClearITPendingBit() 和/或 I2C_SoftwareResetCmd() 和/或 I2C_GenerateStop() ，以便清除错误标志和来源，返回到正确的通信状态。


     (#) 高级状态监测(使用函数I2C_GetLastEvent()

        使用函数I2C_GetLastEvent()，它在一个字(uint32_t)中返回两个状态寄存器的图像(状态寄存器2的值被左移16位并与状态寄存器1连接)。

          (++)何时使用
             (++) 该函数适用于上述相同的应用，但它可以克服I2C_GetFlagStatus()函数的上述限制。
             (++) 返回的值可以与库中已经定义的事件(stm32f4xx_i2c.h)或用户定义的自定义值相比较。
               这个函数适用于同时监测多个标志的情况。
             (++) 与I2C_CheckEvent()函数相反，该函数允许用户选择何时接受一个事件(当所有的事件标志被设置且没有其他标志被设置时，或者像I2C_CheckEvent()函数那样只设置需要的标志。

          (++)局限性
             (++) 用户可能需要定义自己的事件。
             (++) 如果用户决定只检查常规的通信标志(而忽略错误标志)，那么关于错误管理的同样评论也适用于这个函数。


     (#) 基于标志的状态监测(使用函数I2C_GetFlagStatus()

      使用函数I2C_GetFlagStatus()可以简单地返回一个单一标志的状态(即I2C_FLAG_RXNE ...)。

          (++) 何时使用
             (++) 这个函数可以用于特定的应用或在调试阶段使用。
             (++) 当只需要检查一个标志时，它是合适的(大多数I2C事件是通过多个标志监测的)。
          (++)局限性。
             (++) 当调用这个函数时，状态寄存器被访问。
               当状态寄存器被访问时，一些标志被清除。
               所以检查一个标志的状态，可能会清除其他的标志。
             (++) 为了监测一个单一的事件，该函数可能需要调用两次或更多次。

   关于事件的详细描述，请参考I2C_Events章节。stm32f4xx_i2c.h文件中的I2C_Events部分。

@endverbatim
  * @{
  */

/**
  * 简介:  读取指定的 I2C 寄存器并返回其值。
  * 
  * 参数:  I2C_Register: 指定要读取的寄存器。
  *          此参数可以是以下值之一:
  *            @arg I2C_Register_CR1:   CR1 寄存器.
  *            @arg I2C_Register_CR2:   CR2 寄存器.
  *            @arg I2C_Register_OAR1:  OAR1 寄存器.
  *            @arg I2C_Register_OAR2:  OAR2 寄存器.
  *            @arg I2C_Register_DR:    DR 寄存器.
  *            @arg I2C_Register_SR1:   SR1 寄存器.
  *            @arg I2C_Register_SR2:   SR2 寄存器.
  *            @arg I2C_Register_CCR:   CCR 寄存器.
  *            @arg I2C_Register_TRISE: TRISE 寄存器.
  * 
  * 返回值: 读取寄存器的值。
  */
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register) {
    __IO uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_REGISTER(I2C_Register));

    tmp = (uint32_t) I2Cx;
    tmp += I2C_Register;

    /* 返回被选择的寄存器值 */
    return (*(__IO uint16_t *) tmp);
}

/**
  * 简介:  启用或禁用指定的 I2C 中断.
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_IT: 指定要启用或禁用的I2C中断源。
  *          此参数可以是以下值的任意组合:
  *             @arg I2C_IT_BUF: 缓冲器中断屏蔽
  *             @arg I2C_IT_EVT: 事件中断掩码
  *             @arg I2C_IT_ERR: 错误中断屏蔽
  * 
  * 参数:  NewState: 指定I2C中断的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_I2C_CONFIG_IT(I2C_IT));

    if (NewState != DISABLE) {
        /* 启用被选定的 I2C 中断 */
        I2Cx->CR2 |= I2C_IT;
    } else {
        /* 禁用被选中的 I2C 中断 */
        I2Cx->CR2 &= (uint16_t)~I2C_IT;
    }
}

/*
 ===============================================================================
                          1. 基本状态监测
 ===============================================================================
 */

/**
  * 简介:  检查最后一个 I2Cx 事件是否等于作为参数传递的事件。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_EVENT: 指定要检查的事件。
  *          此参数可以是以下值之一:
  *            @arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED: EV1
  *            @arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED: EV1
  *            @arg I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED: EV1
  *            @arg I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED: EV1
  *            @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED: EV1
  *            @arg I2C_EVENT_SLAVE_BYTE_RECEIVED: EV2
  *            @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF): EV2
  *            @arg (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL): EV2
  *            @arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED: EV3
  *            @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF): EV3
  *            @arg (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL): EV3
  *            @arg I2C_EVENT_SLAVE_ACK_FAILURE: EV3_2
  *            @arg I2C_EVENT_SLAVE_STOP_DETECTED: EV4
  *            @arg I2C_EVENT_MASTER_MODE_SELECT: EV5
  *            @arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED: EV6
  *            @arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED: EV6
  *            @arg I2C_EVENT_MASTER_BYTE_RECEIVED: EV7
  *            @arg I2C_EVENT_MASTER_BYTE_TRANSMITTING: EV8
  *            @arg I2C_EVENT_MASTER_BYTE_TRANSMITTED: EV8_2
  *            @arg I2C_EVENT_MASTER_MODE_ADDRESS10: EV9
  *
  * 注意:   关于事件的详细描述，请参考stm32f4xx_i2c.h文件中I2C_Events部分。
  *
  * 返回值: ErrorStatus枚举值:
  *           - SUCCESS: 最后一个事件等同于I2C_EVENT。
  *           - ERROR: 最后一个事件与I2C_EVENT不同
  */
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT) {
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_EVENT(I2C_EVENT));

    /* 读 I2Cx 状态寄存器 */
    flag1 = I2Cx->SR1;
    flag2 = I2Cx->SR2;
    flag2 = flag2 << 16;

    /* 获取I2C状态的最后一个事件值寄存器 */
    lastevent = (flag1 | flag2) & FLAG_MASK;

    /* 检查是否最后一个事件包含I2C_EVENT */
    if ((lastevent & I2C_EVENT) == I2C_EVENT) {
        /* SUCCESS: 最后一个事件等于I2C_EVENT */
        status = SUCCESS;
    } else {
        /* ERROR: 最后一个事件与I2C_EVENT不同 */
        status = ERROR;
    }

    /* Return 状态 */
    return status;
}

/*
 ===============================================================================
                          2. 高级状态监测
 ===============================================================================
 */

/**
  * 简介:  返回最后一个 I2Cx 事件。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  *
  * 注意:   关于事件的详细描述，请参考I2C_Events部分 中的I2C_Events部分。
  *
  * 返回值: 最后一个事件
  */
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx) {
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;

    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    /* 读 I2Cx 状态寄存器 */
    flag1 = I2Cx->SR1;
    flag2 = I2Cx->SR2;
    flag2 = flag2 << 16;

    /* 获取I2C状态的最后一个事件值寄存器 */
    lastevent = (flag1 | flag2) & FLAG_MASK;

    /* Return 状态 */
    return lastevent;
}

/*
 ===============================================================================
                          3. 基于标志的状态监测
 ===============================================================================
 */

/**
  * 简介:  检查是否设置了指定的 I2C 标志。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *             @arg I2C_FLAG_DUALF: 双重标志 (从机模式)
  *             @arg I2C_FLAG_SMBHOST: SMBus主机头(从机模式)
  *             @arg I2C_FLAG_SMBDEFAULT: SMBus默认头(从属模式)
  *             @arg I2C_FLAG_GENCALL: 通用调用头标志(从属模式)
  *             @arg I2C_FLAG_TRA: 发送器/接收器标志
  *             @arg I2C_FLAG_BUSY: 总线繁忙标志
  *             @arg I2C_FLAG_MSL: 主/从标志
  *             @arg I2C_FLAG_SMBALERT: SMBus警报标志
  *             @arg I2C_FLAG_TIMEOUT: 超时或Tlow错误标志
  *             @arg I2C_FLAG_PECERR: 接收中的PEC错误标志
  *             @arg I2C_FLAG_OVR: 超载/欠载标志(从机模式)。
  *             @arg I2C_FLAG_AF: 确认失败标志
  *             @arg I2C_FLAG_ARLO: 仲裁丢失标志(主模式)
  *             @arg I2C_FLAG_BERR: 总线错误标志
  *             @arg I2C_FLAG_TXE: 数据寄存器空标志(发射器)。
  *             @arg I2C_FLAG_RXNE: 数据寄存器不为空(接收方)标志
  *             @arg I2C_FLAG_STOPF: 停止检测标志 (从机模式)
  *             @arg I2C_FLAG_ADD10: 10-bit header sent flag (Master mode)
  *             @arg I2C_FLAG_BTF: 字节传输完成标志
  *             @arg I2C_FLAG_ADDR: 地址发送标志(主模式) "ADSL"
  *             地址匹配标志(从机模式)"ENDAD"
  *             @arg I2C_FLAG_SB: 启动位标志(主模式)
  * 
  * 返回值: I2C_FLAG的新状态(SET或RESET)。
  */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG) {
    FlagStatus bitstatus = RESET;
    __IO uint32_t i2creg = 0, i2cxbase = 0;

    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

    /* 获取I2Cx 外设基地址 */
    i2cxbase = (uint32_t)I2Cx;

    /* 读取标志寄存器索引 */
    i2creg = I2C_FLAG >> 28;

    /* Get bit[23:0] of the flag */
    I2C_FLAG &= FLAG_MASK;

    if(i2creg != 0) {
        /* 获取I2Cx SR1寄存器地址 */
        i2cxbase += 0x14;
    } else {
        /* Flag in I2Cx SR2 寄存器 */
        I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
        /* 获取I2Cx SR2寄存器地址 */
        i2cxbase += 0x18;
    }

    if(((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET) {
        /* I2C_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* I2C_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回I2C_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 I2Cx 的挂起标志。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *             @arg I2C_FLAG_SMBALERT: SMBus警报标志
  *             @arg I2C_FLAG_TIMEOUT: 超时或Tlow错误标志
  *             @arg I2C_FLAG_PECERR: 接收中的PEC错误标志
  *             @arg I2C_FLAG_OVR: 超载/欠载标志(从机模式)。
  *             @arg I2C_FLAG_AF: 确认失败标志
  *             @arg I2C_FLAG_ARLO: 仲裁丢失标志(主模式)
  *             @arg I2C_FLAG_BERR: 总线错误标志
  *
  * 注意: STOPF(STOP检测)通过软件顺序清除:对I2C_SR1寄存器进行
  *       读操作(I2C_GetFlagStatus())，然后对I2C_CR1寄存器进行写操作(I2C_Cmd()以重新启用I2C外设)。
  * 注意: ADD10(发送10位头)通过软件顺序清除:对I2C_SR1进行读操作
  *     (I2C_GetFlagStatus())，然后在DR寄存器中写入地址的第二个字节。
  * 注意: BTF (Byte Transfer Finished)通过软件顺序清除:对I2C_SR1
  *       寄存器进行读操作(I2C_GetFlagStatus())，然后对I2C_DR寄存器进行读/写(I2C_SendData())。
  * 注意: ADDR(发送的地址)通过软件顺序清除:对I2C_SR1寄存器进行读操作(
  *       I2C_GetFlagStatus())，然后对I2C_SR2寄存器进行读操作((void)(I2Cx->SR2))。
  * 注意: SB(Start Bit)被清除 软件顺序:对I2C_SR1寄存器进行读操作
  *     (I2C_GetFlagStatus())，然后对I2C_DR寄存器进行写操作(I2C_SendData())。
  *
  * 返回值: 无
  */
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG) {
    uint32_t flagpos = 0;
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));
    /* 获取I2C标志位置 */
    flagpos = I2C_FLAG & FLAG_MASK;
    /* 清除被选择的 I2C 标志 */
    I2Cx->SR1 = (uint16_t)~flagpos;
}

/**
  * 简介:  检查是否发生了指定的 I2C 中断。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_IT: 指定要检查的中断源。
  *          此参数可以是以下值之一:
  *             @arg I2C_IT_SMBALERT: SMBus警报标志
  *             @arg I2C_IT_TIMEOUT: 超时或Tlow错误标志
  *             @arg I2C_IT_PECERR: 接收中的PEC错误标志
  *             @arg I2C_IT_OVR: 超载/欠载标志(从机模式)。
  *             @arg I2C_IT_AF: 确认失败标志
  *             @arg I2C_IT_ARLO: 仲裁丢失标志(主模式)
  *             @arg I2C_IT_BERR: 总线错误标志
  *             @arg I2C_IT_TXE: 数据寄存器空标志(发射器)。
  *             @arg I2C_IT_RXNE: 数据寄存器不空(接收器)标志
  *             @arg I2C_IT_STOPF: 停止检测标志 (从机模式)
  *             @arg I2C_IT_ADD10: 10-bit header sent flag (Master mode)
  *             @arg I2C_IT_BTF: 字节传输结束标志
  *             @arg I2C_IT_ADDR: 地址发送标志(主模式) "ADSL"
  *             地址匹配标志(从机模式)"ENDAD"
  *             @arg I2C_IT_SB: 启动位标志(主模式)
  * 
  * 返回值:I2C_IT的新状态(SET或RESET)。
  */
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT) {
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_GET_IT(I2C_IT));

    /* 检查中断源是否启用 */
    enablestatus = (uint32_t)(((I2C_IT & ITEN_MASK) >> 16) & (I2Cx->CR2)) ;

    /* Get bit[23:0] of the flag */
    I2C_IT &= FLAG_MASK;

    /* 检查指定的I2C标志的状态 */
    if (((I2Cx->SR1 & I2C_IT) != (uint32_t)RESET) && enablestatus) {
        /* I2C_IT 被设置 */
        bitstatus = SET;
    } else {
        /* I2C_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回I2C_IT 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 I2Cx 的中断挂起位。
  * 
  * 参数:  I2Cx: 其中x可以是1、2或3，以选择I2C的外设。
  * 
  * 参数:  I2C_IT: 指定要清除的中断等待位。
  *          此参数可以是以下值的任意组合:
  *              @arg I2C_IT_SMBALERT: SMBus警报中断
  *              @arg I2C_IT_TIMEOUT: 超时或Tlow错误中断
  *              @arg I2C_IT_PECERR: 接收中的PEC错误中断
  *              @arg I2C_IT_OVR: 超载/欠载中断(从机模式)
  *              @arg I2C_IT_AF: 确认失败中断
  *              @arg I2C_IT_ARLO: 仲裁丢失.中断(主模式)
  *              @arg I2C_IT_BERR: 总线错误中断
  *
  * 注意: STOPF(STOP检测)通过软件顺序清除:对I2C_SR1寄存器进行读操作
  *       (I2C_GetITStatus())，然后对I2C_CR1寄存器进行
  *        写操作(I2C_Cmd()以重新启用I2C外设)。
  * 注意: ADD10(发送10位头)通过软件顺序清除:对I2C_SR1进行读操作
  *     (I2C_GetITStatus())，然后在I2C_DR寄存器中写入地址的第二个字节。
  * 注意: BTF (Byte Transfer Finished)通过软件顺序清除:
  *       对I2C_SR1寄存器进行读操作(I2C_GetITStatus())，
  *       然后对I2C_DR寄存器进行读/写(I2C_SendData())。
  * 注意: ADDR(发送的地址)通过软件顺序清除:对I2C_SR1寄存器进行读操作
  *     (I2C_GetITStatus())，然后对I2C_SR2寄存器进行读操作((void)(I2Cx->SR2))。
  * 注意: SB (Start Bit)通过软件顺序清除:对I2C_SR1寄存器进行读操作
  *     (I2C_GetITStatus())，然后对I2C_DR寄存器进行写操作(I2C_SendData())。
  * 
  * 返回值: 无
  */
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT) {
    uint32_t flagpos = 0;
    /* 检查参数 */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLEAR_IT(I2C_IT));

    /* 获取I2C标志位置 */
    flagpos = I2C_IT & FLAG_MASK;

    /* 清除被选择的 I2C 标志 */
    I2Cx->SR1 = (uint16_t)~flagpos;
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
