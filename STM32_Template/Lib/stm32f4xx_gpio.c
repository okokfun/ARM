/**
  ******************************************************************************
  * 文件:    stm32f4xx_gpio.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能以管理GPIO外设设备的以下功能:
  *           + 初始化及配置
  *           + GPIO读写
  *           + GPIO复用功能配置
  *
@verbatim
 ===============================================================================
                      ##### 如何使用此驱动程序 #####
 ===============================================================================
 [..]
   (#) 使用以下函数启用GPIO AHB时钟
       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

   (#) 使用GPIO_Init()配置GPIO引脚
       每个引脚有四种可能的配置:
       (++) 输入:浮空、上拉、下拉。

       (++) 输出:推拉(向上拉、向下拉或无拉)打开排水管(向上、向下拉或者无拉)。
				  在输出模式下，速度可配置:2 MHz、25 MHz、50 MHz或100 MHz。

       (++) Alternate Function: Push-Pull (Pull-up, Pull-down or no Pull) Open
            Drain (Pull-up, Pull-down or no Pull).

       (++) 模拟:引脚用作ADC通道或DAC输出时所需的模式。

   (#) 外设设备替代功能:
       (++) 对于ADC和DAC，使用GPIO_InitStruct->GPIO_mode=GPIO_mode_AN在模拟模式下配置所需引脚;
            (+++) 对于其他外设设备(TIM、USART…):
            
            (+++) 使用GPIO_PinAFConfig()函数将管脚连接到所需外设设备的复用功能(AF)

            (+++) 使用GPIO_InitStruct->GPIO_mode=GPIO_mode_AF在复用功能模式下配置所需引脚

            (+++) 通过GPIO_PuPd、GPIO_OType和GPIO_speed成员选择类型、上拉/下拉和输出速度

            (+++) 调用GPIO_Init()函数

   (#) 使用GPIO_ReadInputDataBit()获取输入模式中配置的管脚级别

   (#) 要设置/重置输出模式中配置的管脚级别，请使用GPIO_SetBits()/GPIO_ResetBits

   (#) 复位期间和复位后，复用功能不激活，GPIO引脚配置为输入浮动模式(JTAG引脚除外)。

   (#) LSE振荡器关闭时，可以将LSE振荡器引脚OSC32\uIN和OSC32\OUT用作通用(分别为PC14和PC15)。
		LSE优先于GPIO功能。

   (#) 当HSE振荡器关闭时，HSE振荡器引脚OSC_IN/OSC_OUT可分别用作通用PH0和PH1。
		HSE优先于GPIO职能。

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
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO
  * 简介: GPIO驱动程序模块
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions
  * @{
  */

/** @defgroup GPIO_Group1 初始化及配置
 *  简介   初始化及配置
 *
@verbatim
 ===============================================================================
                 ##### 初始化及配置 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  将GPIOx外围寄存器反初始化为其默认重置值。
  * 
  * 注意:   默认情况下，GPIO引脚配置为输入浮动模式(JTAG引脚除外)。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)，为STM32F42xxx/43xxx设备选择GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 返回值: 无
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    if (GPIOx == GPIOA) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA, DISABLE);
    } else if (GPIOx == GPIOB) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, DISABLE);
    } else if (GPIOx == GPIOC) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOC, DISABLE);
    } else if (GPIOx == GPIOD) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD, DISABLE);
    } else if (GPIOx == GPIOE) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOE, DISABLE);
    } else if (GPIOx == GPIOF) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOF, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOF, DISABLE);
    } else if (GPIOx == GPIOG) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOG, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOG, DISABLE);
    } else if (GPIOx == GPIOH) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOH, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOH, DISABLE);
    } else if (GPIOx == GPIOI) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOI, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOI, DISABLE);
    } else if (GPIOx == GPIOJ) {
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOJ, ENABLE);
        RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOJ, DISABLE);
    } else {
        if (GPIOx == GPIOK) {
            RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOK, ENABLE);
            RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOK, DISABLE);
        }
    }
}

/**
  * 简介:  根据GPIO_InitStruct中的指定参数初始化GPIOx外设设备。
  * 
  * 参数:  GPIOx: 其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32F145xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_InitStruct:指向包含指定GPIO外设设备配置信息的GPIO_InitTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct) {
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00;

    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

    /* ------------------------- 配置端口引脚 ---------------- */
    /*-- GPIO模式配置 --*/
    for (pinpos = 0x00; pinpos < 0x10; pinpos++) {
        pos = ((uint32_t)0x01) << pinpos;
        /* 获取端口引脚位置 */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

        if (currentpin == pos) {
            GPIOx->MODER  &= ~(GPIO_MODER_MODER0 << (pinpos * 2));
            GPIOx->MODER |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));

            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF)) {
                /* 检查速度模式参数 */
                assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

                /* 速度模式配置 */
                GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2));
                GPIOx->OSPEEDR |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

                /* 检查输出模式参数 */
                assert_param(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

                /* 输出模式配置 */
                GPIOx->OTYPER  &= ~((GPIO_OTYPER_OT_0) << ((uint16_t)pinpos)) ;
                GPIOx->OTYPER |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos));
            }

            /* 上拉下拉电阻器配置 */
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
            GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
        }
    }
}

/**
  * 简介:  用默认值填充每个GPIO_InitStruct成员。
  * 
  * 参数:  GPIO_InitStruct:指向将被初始化的GPIO_InitTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct) {
    /* 重置GPIO初始化结构参数值 */
    GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * 简介:  锁定GPIO引脚配置寄存器。
  * 
  * 注意:   锁定的寄存器包括GPIOx_MODER、GPIOx_OTYPER、GPIOx_OSPEEDR、GPIOx _PUPDR、GPIOx-AFRL和GPIOx_AFRH。
  * 
  * 注意:   锁定的GPIO引脚的配置在下次重置之前无法再修改。
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_Pin:指定要锁定的端口位。
  *          此参数可以是GPIO_Pin_x的任意组合，其中x可以是(0..15)。
  * 
  * 返回值: 无
  */
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    __IO uint32_t tmp = 0x00010000;

    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    tmp |= GPIO_Pin;
    /* 设置LCKK位 */
    GPIOx->LCKR = tmp;
    /* 重置LCKK位 */
    GPIOx->LCKR =  GPIO_Pin;
    /* 设置LCKK位 */
    GPIOx->LCKR = tmp;
    /* 读取LCKK位 */
    tmp = GPIOx->LCKR;
    /* 读取LCKK位 */
    tmp = GPIOx->LCKR;
}

/**
  * @}
  */

/** @defgroup GPIO_Group2 GPIO读写
 *  简介   GPIO读写
 *
@verbatim
 ===============================================================================
                         ##### GPIO读写 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  读取指定的输入端口引脚。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_Pin:指定要读取的端口位。
  *         此参数可以是GPIO_Pin_x，其中x可以是(0..15)。
  * 
  * 返回值: 输入端口引脚值。
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    uint8_t bitstatus = 0x00;

    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET) {
        bitstatus = (uint8_t)Bit_SET;
    } else {
        bitstatus = (uint8_t)Bit_RESET;
    }

    return bitstatus;
}

/**
  * 简介:  读取指定的GPIO输入数据端口。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 返回值: GPIO输入数据端口值。
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->IDR);
}

/**
  * 简介:  读取指定的输出数据端口位。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_Pin:指定要读取的端口位。
  *          此参数可以是GPIO_Pin_x，其中x可以是(0..15)。
  * 
  * 返回值: 输出端口引脚值。
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    uint8_t bitstatus = 0x00;

    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    if (((GPIOx->ODR) & GPIO_Pin) != (uint32_t)Bit_RESET) {
        bitstatus = (uint8_t)Bit_SET;
    } else {
        bitstatus = (uint8_t)Bit_RESET;
    }

    return bitstatus;
}

/**
  * 简介:  读取指定的GPIO输出数据端口。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 返回值: GPIO输出数据端口值。
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    return ((uint16_t)GPIOx->ODR);
}

/**
  * 简介:  设置所选数据端口位。
  * 
  * 注意:   此函数使用GPIOx_BSRR寄存器允许原子读取/修改访问。
		这样，在读取和修改访问之间就不会发生IRQ风险。

  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_Pin: 指定要写入的端口位。
  *          此参数可以是GPIO_Pin_x的任意组合，其中x可以是(0..15)。
  * 
  * 返回值: 无
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->BSRRL = GPIO_Pin;
}

/**
  * 简介:  清除选定的数据端口位。
  * 
  * 注意:   此函数使用GPIOx_BSRR寄存器允许原子读取/修改访问。
		这样，在读取和修改访问之间就不会发生IRQ风险。

  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_Pin: 指定要写入的端口位。
  *          此参数可以是GPIO_Pin_x的任意组合，其中x可以是(0..15)。
  * 
  * 返回值: 无
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    GPIOx->BSRRH = GPIO_Pin;
}

/**
  * 简介:  设置或清除所选数据端口位。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_Pin:指定要写入的端口位。
  *          此参数可以是GPIO_Pin_x之一，其中x可以是(0..15)。
  * 
  * 参数:  BitVal: 指定要写入选定位的值。
  *          此参数可以是BitAction枚举值之一:
  *            @arg Bit_RESET: 清除端口引脚
  *            @arg Bit_SET: 设置端口引脚
  * 
  * 返回值: 无
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_GPIO_BIT_ACTION(BitVal));

    if (BitVal != Bit_RESET) {
        GPIOx->BSRRL = GPIO_Pin;
    } else {
        GPIOx->BSRRH = GPIO_Pin ;
    }
}

/**
  * 简介:  将数据写入指定的GPIO数据端口。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  PortVal:指定要写入端口输出数据寄存器的值。
  * 
  * 返回值: 无
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->ODR = PortVal;
}

/**
  * 简介:  切换指定的GPIO引脚。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_Pin:指定要切换的管脚。
  * 
  * 返回值: 无
  */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->ODR ^= GPIO_Pin;
}

/**
  * @}
  */

/** @defgroup GPIO_Group3 GPIO复用功能配置功能
 *  简介   GPIO复用功能配置功能
 *
@verbatim
 ===============================================================================
           ##### GPIO复用功能配置功能 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  更改指定引脚的映射。
  * 
  * 参数:  GPIOx:其中x可以是(A..K)，用于为STM32F405xx/407xx和STM32P415xx/417xx设备选择GPIO外设设备
  *                      x可以是(A..I)以选择STM32F42xxx/43xxx设备的GPIO外设设备。
  *                      x可以是(A、B、C、D和H)，以选择STM32F401xx设备的GPIO外设设备。
  * 
  * 参数:  GPIO_PinSource:指定复用功能的管脚。
  *         此参数可以是GPIO_PinSourcex，其中x可以是(0..15)。
  * 
  * 参数:  GPIO_AFS选择:选择要用作复用功能的管脚。(重置后默认)
  *          此参数可以是以下值之一:
  *            @arg GPIO_AF_RTC_50Hz : 将RTC_50Hz pin to AF0 (重置后默认)
  *            @arg GPIO_AF_MCO : 将MCO pin (MCO1 and MCO2) to AF0 (重置后默认)
  *            @arg GPIO_AF_TAMPER : 将TAMPER pins (TAMPER_1 and TAMPER_2) to AF0 (重置后默认)
  *            @arg GPIO_AF_SWJ : 将SWJ引脚(SWD and JTAG)to AF0 (重置后默认)
  *            @arg GPIO_AF_TRACE : 将TRACE引脚连接到AF0 (重置后默认)
  *            @arg GPIO_AF_TIM1: 将TIM1引脚连接到AF1
  *            @arg GPIO_AF_TIM2: 将TIM2引脚连接到AF1
  *            @arg GPIO_AF_TIM3: 将TIM3引脚连接到AF2
  *            @arg GPIO_AF_TIM4: 将TIM4引脚连接到AF2
  *            @arg GPIO_AF_TIM5: 将TIM5引脚连接到AF2
  *            @arg GPIO_AF_TIM8: 将TIM8引脚连接到AF3
  *            @arg GPIO_AF_TIM9: 将TIM9引脚连接到AF3
  *            @arg GPIO_AF_TIM10: 将TIM10引脚连接到AF3
  *            @arg GPIO_AF_TIM11: 将TIM11引脚连接到AF3
  *            @arg GPIO_AF_I2C1: 将I2C1引脚连接到AF4
  *            @arg GPIO_AF_I2C2: 将I2C2引脚连接到AF4
  *            @arg GPIO_AF_I2C3: 将I2C3引脚连接到AF4
  *            @arg GPIO_AF_SPI1: 将SPI1引脚连接到AF5
  *            @arg GPIO_AF_SPI2: 将SPI2/I2S2引脚连接到AF5
  *            @arg GPIO_AF_SPI4: 将SPI4引脚连接到AF5
  *            @arg GPIO_AF_SPI5: 将SPI5引脚连接到AF5
  *            @arg GPIO_AF_SPI6: 将SPI6引脚连接到AF5
  *            @arg GPIO_AF_SAI1: 将SAI1引脚连接到STM32F42xxx/43xxx设备的AF6。
  *            @arg GPIO_AF_SPI3: 将SPI3/I2S3引脚连接到AF6
  *            @arg GPIO_AF_I2S3ext : 将I2S3ext引脚连接到AF7
  *            @arg GPIO_AF_USART1 : 将USART1引脚连接到AF7
  *            @arg GPIO_AF_USART2 : 将USART2引脚连接到AF7
  *            @arg GPIO_AF_USART3 : 将USART3引脚连接到AF7
  *            @arg GPIO_AF_UART4 : 将UART4引脚连接到AF8
  *            @arg GPIO_AF_UART5 : 将UART5引脚连接到AF8
  *            @arg GPIO_AF_USART6 : 将USART6引脚连接到AF8
  *            @arg GPIO_AF_UART7 : 将UART7引脚连接到AF8
  *            @arg GPIO_AF_UART8 : 将UART8引脚连接到AF8
  *            @arg GPIO_AF_CAN1 : 将CAN1引脚连接到AF9
  *            @arg GPIO_AF_CAN2 : 将CAN2引脚连接到AF9
  *            @arg GPIO_AF_TIM12 : 将TIM12引脚连接到AF9
  *            @arg GPIO_AF_TIM13 : 将TIM13引脚连接到AF9
  *            @arg GPIO_AF_TIM14 : 将TIM14引脚连接到AF9
  *            @arg GPIO_AF_OTG_FS : 将OTG_FS引脚连接到AF10
  *            @arg GPIO_AF_OTG_HS : 将OTG_HS引脚连接到AF10
  *            @arg GPIO_AF_ETH : 将ETHERNET引脚连接到AF11
  *            @arg GPIO_AF_FSMC : 将FSMC引脚连接到AF12
  *            @arg GPIO_AF_FMC : 将FMC引脚连接到AF12 for STM32F42xxx/43xxx devices.
  *            @arg GPIO_AF_OTG_HS_FS : 将OTG HS (configured in FS)引脚连接到AF12
  *            @arg GPIO_AF_SDIO : 将SDIO引脚连接到AF12
  *            @arg GPIO_AF_DCMI : 将DCMI引脚连接到AF13
  *            @arg GPIO_AF_LTDC : 将LTDC引脚连接到AF14 for STM32F429xx/439xx devices.
  *            @arg GPIO_AF_EVENTOUT : 将EVENTOUT引脚连接到AF15
  * 
  * 返回值: 无
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF) {
    uint32_t temp = 0x00;
    uint32_t temp_2 = 0x00;

    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    assert_param(IS_GPIO_AF(GPIO_AF));

    temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
    GPIOx->AFR[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4)) ;
    temp_2 = GPIOx->AFR[GPIO_PinSource >> 0x03] | temp;
    GPIOx->AFR[GPIO_PinSource >> 0x03] = temp_2;
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
