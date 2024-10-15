/**
  ******************************************************************************
  * 文件:    stm32f4xx_gpio.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能以管理GPIO 外设设备的以下功能:
  *           + 初始化及配置
  *           + GPIO读写
  *           + GPIO复用功能配置
  *
@verbatim
 ===============================================================================
                      ##### 如何使用此驱动程序 #####
 ===============================================================================
 [..]
   (#) 使用以下函数启用 GPIO AHB 时钟
       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

   (#) 使用 GPIO_Init()配置GPIO 引脚
       每个引脚有四种可能的配置:
       (++) 输入: 浮空、上拉、下拉。

       (++) 输出: 推拉(向上拉、向下拉或无拉)打开排水管(向上、向下拉或者无拉)。
				  在输出模式下，速度可配置:2 MHz、25 MHz、50 MHz或100 MHz。

       (++) 复用功能: Push-Pull (Pull-up, Pull-down or no Pull) Open
            Drain (Pull-up, Pull-down or no Pull).

       (++) 模拟: 引脚用作ADC 通道或 DAC输出时所需的模式。

   (#) 外设设备复用功能:
       (++) 对于ADC 和 DAC，使用 GPIO_InitStruct->GPIO_mode=GPIO_mode_AN 在模拟模式下配置所需引脚;
            (+++) 对于其他外设设备(TIM、USART…):
            
            (+++) 使用 GPIO_PinAFConfig() 函数将管脚连接到所需外设设备的复用功能(AF)

            (+++) 使用 GPIO_InitStruct->GPIO_mode=GPIO_mode_AF 在复用功能模式下配置所需引脚

            (+++) 通过 GPIO_PuPd、GPIO_OType 和 GPIO_speed 成员选择类型、上拉/下拉和输出速度

            (+++) 调用 GPIO_Init() 函数

   (#) 使用 GPIO_ReadInputDataBit() 获取输入模式中配置的管脚级别

   (#) 要设置/重置输出模式中配置的管脚级别，请使用 GPIO_SetBits()/GPIO_ResetBits

   (#) 复位期间和复位后，复用功能不激活，GPIO 引脚配置为输入浮动模式(JTAG引脚除外)。

   (#) LSE振荡器关闭时，可以将LSE振荡器引脚 OSC_IN 和OSC_OUT 用作通用(分别为PC14 和PC15)。
		LSE优先于 GPIO 功能。

   (#) 当HSE振荡器关闭时，HSE 振荡器引脚 OSC_IN/OSC_OUT 可分别用作通用 PH0 和PH1。
		HSE优先于 GPIO 职能。

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
  */

/** @defgroup GPIO
  * 简介: GPIO驱动程序模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions
  */

/** @defgroup GPIO_Group1 初始化及配置
 *  简介   初始化及配置
 *
@verbatim
 ===============================================================================
                 ##### 初始化及配置 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  将GPIOx 外围寄存器反初始化为其默认重置值。
  * 
  * 注意:   默认情况下，GPIO 引脚配置为输入浮动模式(JTAG引脚除外)。
  * 
  * 参数:  GPIOx: 其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)，为STM32F42xxx/43xxx 设备选择GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
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
  * 简介:  根据 GPIO_InitStruct 中的指定参数初始化 GPIOx 外设设备。
  * 
  * 参数:  GPIOx: 其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32F145xx/417xx 设备选择 GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。 
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_InitStruct: 指向包含指定 GPIO 外设设备配置信息的 GPIO_InitTypeDef 结构的指针。
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
  * 简介:  用默认值填充每个 GPIO_InitStruct 成员。
  * 
  * 参数:  GPIO_InitStruct: 指向将被初始化的 GPIO_InitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct) {
    /* 重置GPIO初始化结构参数值 */
    GPIO_InitStruct->GPIO_Pin   = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct->GPIO_PuPd  = GPIO_PuPd_NOPULL;
}

/**
  * 简介:  锁定 GPIO 引脚配置寄存器。
  * 
  * 注意:  锁定的寄存器包括 GPIOx_MODER、GPIOx_OTYPER、GPIOx_OSPEEDR、GPIOx _PUPDR、GPIOx-AFRL 和 GPIOx_AFRH。
  * 
  * 注意:  锁定的 GPIO 引脚的配置在下次重置之前无法再修改。
  * 参数:  GPIOx: 其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_Pin: 指定要锁定的端口位。
  *          此参数可以是 GPIO_Pin_x 的任意组合，其中 x 可以是(0..15)。
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


/** @defgroup GPIO_Group2 GPIO读写
 *  简介   GPIO读写
 *
@verbatim
 ===============================================================================
                         ##### GPIO读写 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  读取指定的输入端口引脚。
  * 
  * 参数:  GPIOx: 其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_Pin: 指定要读取的端口位。
  *         此参数可以是 GPIO_Pin_x，其中 x 可以是(0..15)。
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
  * 简介:  读取指定的 GPIO输入数据端口。
  * 
  * 参数:  GPIOx: 其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择 GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
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
  * 参数:  GPIOx: 其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择 GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_Pin: 指定要读取的端口位。
  *          此参数可以是 GPIO_Pin_x，其中 x 可以是(0..15)。
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
  * 简介:  读取指定的 GPIO输出数据端口。
  * 
  * 参数:  GPIOx: 其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择 GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
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
  * 注意:   此函数使用 GPIOx_BSRR 寄存器允许原子读取/修改访问。
		这样，在读取和修改访问之间就不会发生IRQ风险。

  * 参数:  GPIOx:其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_Pin: 指定要写入的端口位。
  *          此参数可以是 GPIO_Pin_x 的任意组合，其中 x 可以是(0..15)。
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
  * 注意:   此函数使用 GPIOx_BSRR 寄存器允许原子读取/修改访问。
		这样，在读取和修改访问之间就不会发生IRQ风险。

  * 参数:  GPIOx:其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_Pin: 指定要写入的端口位。
  *          此参数可以是 GPIO_Pin_x 的任意组合，其中 x 可以是(0..15)。
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
  * 参数:  GPIOx:其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_Pin:指定要写入的端口位。
  *          此参数可以是 GPIO_Pin_x之一，其中 x 可以是(0..15)。
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
  * 简介:  将数据写入指定的 GPIO数据端口。
  * 
  * 参数:  GPIOx:其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
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
  * 简介:  切换指定的 GPIO 引脚。
  * 
  * 参数:  GPIOx: 其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_Pin: 指定要切换的管脚。
  * 
  * 返回值: 无
  */
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    /* 检查参数 */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->ODR ^= GPIO_Pin;
}


/** @defgroup GPIO_Group3 GPIO复用功能配置功能
 *  简介   GPIO复用功能配置功能
 *
@verbatim
 ===============================================================================
           ##### GPIO复用功能配置功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  更改指定引脚的映射。
  * 
  * 参数:  GPIOx:其中 x 可以是(A..K)，用于为 STM32F405xx/407xx 和 STM32P415xx/417xx 设备选择GPIO 外设设备
  *                      x 可以是(A..I)以选择 STM32F42xxx/43xxx 设备的 GPIO 外设设备。
  *                      x 可以是(A、B、C、D和H)，以选择 STM32F401xx 设备的 GPIO 外设设备。
  * 
  * 参数:  GPIO_PinSource:指定复用功能的管脚。
  *         此参数可以是 GPIO_PinSourcex，其中 x 可以是(0..15)。
  * 
  * 参数:  GPIO_AFS 选择:选择要用作复用功能的管脚。(重置后默认)
  *          此参数可以是以下值之一:
  *            @arg GPIO_AF_RTC_50Hz : 将 RTC_50Hz 引脚连接到 AF0 (重置后默认)
  *            @arg GPIO_AF_MCO :      将 MCO 引脚 (MCO1 and MCO2) 连接到 AF0 (重置后默认)
  *            @arg GPIO_AF_TAMPER :   将 TAMPER 引脚 (TAMPER_1 and TAMPER_2) 连接到 AF0 (重置后默认)
  *            @arg GPIO_AF_SWJ:       将 SWJ 引脚(SWD and JTAG)连接到 AF0 (重置后默认)
  *            @arg GPIO_AF_TRACE:     将 TRACE 引脚连接到 AF0 (重置后默认)
  *            @arg GPIO_AF_TIM1:      将 TIM1 引脚连接到 AF1
  *            @arg GPIO_AF_TIM2:      将 TIM2 引脚连接到 AF1
  *            @arg GPIO_AF_TIM3:      将 TIM3 引脚连接到 AF2
  *            @arg GPIO_AF_TIM4:      将 TIM4 引脚连接到 AF2
  *            @arg GPIO_AF_TIM5:      将 TIM5 引脚连接到 AF2
  *            @arg GPIO_AF_TIM8:      将 TIM8 引脚连接到 AF3
  *            @arg GPIO_AF_TIM9:      将 TIM9 引脚连接到 AF3
  *            @arg GPIO_AF_TIM10:     将 TIM10 引脚连接到 AF3
  *            @arg GPIO_AF_TIM11:     将 TIM11 引脚连接到 AF3
  *            @arg GPIO_AF_I2C1:      将 I2C1 引脚连接到 AF4
  *            @arg GPIO_AF_I2C2:      将 I2C2 引脚连接到 AF4
  *            @arg GPIO_AF_I2C3:      将 I2C3 引脚连接到 AF4
  *            @arg GPIO_AF_SPI1:      将 SPI1 引脚连接到 AF5
  *            @arg GPIO_AF_SPI2:      将 SPI2/I2S2 引脚连接到 AF5
  *            @arg GPIO_AF_SPI4:      将 SPI4 引脚连接到 AF5
  *            @arg GPIO_AF_SPI5:      将 SPI5 引脚连接到 AF5
  *            @arg GPIO_AF_SPI6:      将 SPI6 引脚连接到 AF5
  *            @arg GPIO_AF_SAI1:      将 SAI1 引脚连接到 STM32F42xxx/43xxx 设备的 AF6。
  *            @arg GPIO_AF_SPI3:      将 SPI3/I2S3 引脚连接到 AF6
  *            @arg GPIO_AF_I2S3ext :  将 I2S3ext 引脚连接到 AF7
  *            @arg GPIO_AF_USART1 :   将 USART1 引脚连接到 AF7
  *            @arg GPIO_AF_USART2 :   将 USART2 引脚连接到 AF7
  *            @arg GPIO_AF_USART3 :   将 USART3 引脚连接到 AF7
  *            @arg GPIO_AF_UART4 :    将 UART4 引脚连接到 AF8
  *            @arg GPIO_AF_UART5 :    将 UART5 引脚连接到 AF8
  *            @arg GPIO_AF_USART6 :   将 USART6 引脚连接到 AF8
  *            @arg GPIO_AF_UART7 :    将 UART7 引脚连接到 AF8
  *            @arg GPIO_AF_UART8 :    将 UART8 引脚连接到 AF8
  *            @arg GPIO_AF_CAN1 :     将 CAN1 引脚连接到 AF9
  *            @arg GPIO_AF_CAN2 :     将 CAN2 引脚连接到 AF9
  *            @arg GPIO_AF_TIM12 :    将 TIM12 引脚连接到 AF9
  *            @arg GPIO_AF_TIM13 :    将 TIM13 引脚连接到 AF9
  *            @arg GPIO_AF_TIM14 :    将 TIM14 引脚连接到 AF9
  *            @arg GPIO_AF_OTG_FS :   将 OTG_FS 引脚连接到 AF10
  *            @arg GPIO_AF_OTG_HS :   将 OTG_HS 引脚连接到 AF10
  *            @arg GPIO_AF_ETH :      将 ETHERNET 引脚连接到 AF11
  *            @arg GPIO_AF_FSMC :     将 FSMC 引脚连接到 AF12
  *            @arg GPIO_AF_FMC :      将 FMC 引脚连接到 AF12 for STM32F42xxx/43xxx devices.
  *            @arg GPIO_AF_OTG_HS_FS :将 OTG HS (configured in FS)引脚连接到 AF12
  *            @arg GPIO_AF_SDIO :     将 SDIO 引脚连接到 AF12
  *            @arg GPIO_AF_DCMI :     将 DCMI 引脚连接到 AF13
  *            @arg GPIO_AF_LTDC :     将 LTDC 引脚连接到 AF14 for STM32F429xx/439xx devices.
  *            @arg GPIO_AF_EVENTOUT : 将 EVENTOUT 引脚连接到 AF15
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
