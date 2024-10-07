/**
  ******************************************************************************
  * 文件:    stm32f4xx_gpio.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 GPIO 固件库的所有功能原型.
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

/* 定义以防止递归包含 -------------------------------------*/
#ifndef __STM32F4xx_GPIO_H
#define __STM32F4xx_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup GPIO
  */

/* 导出的类型 ------------------------------------------------------------*/

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE) || \
                                    ((PERIPH) == GPIOF) || \
                                    ((PERIPH) == GPIOG) || \
                                    ((PERIPH) == GPIOH) || \
                                    ((PERIPH) == GPIOI) || \
                                    ((PERIPH) == GPIOJ) || \
                                    ((PERIPH) == GPIOK))

/**
  * 简介:  GPIO 配置模式枚举
  */
typedef enum {
    GPIO_Mode_IN   = 0x00, /*!< GPIO 输入模式 */
    GPIO_Mode_OUT  = 0x01, /*!< GPIO 输出模式 */
    GPIO_Mode_AF   = 0x02, /*!< GPIO 复用功能模式 */
    GPIO_Mode_AN   = 0x03  /*!< GPIO 模拟模式 */
} GPIOMode_TypeDef;
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_IN)  || ((MODE) == GPIO_Mode_OUT) || \
                            ((MODE) == GPIO_Mode_AF)|| ((MODE) == GPIO_Mode_AN))

/**
  * 简介:  GPIO 输出类型枚举
  */
typedef enum {
    GPIO_OType_PP = 0x00, // 开漏输出
    GPIO_OType_OD = 0x01  // 推挽输出
} GPIOOType_TypeDef;
#define IS_GPIO_OTYPE(OTYPE) (((OTYPE) == GPIO_OType_PP) || ((OTYPE) == GPIO_OType_OD))


/**
  * 简介:  GPIO 输出最大频率枚举
  */
typedef enum {
    GPIO_Low_Speed     = 0x00, /*!< 低速 */
    GPIO_Medium_Speed  = 0x01, /*!< 中速 */
    GPIO_Fast_Speed    = 0x02, /*!< 快速 */
    GPIO_High_Speed    = 0x03  /*!< 高速 */
} GPIOSpeed_TypeDef;

/* 添加旧版定义 */
#define  GPIO_Speed_2MHz    GPIO_Low_Speed
#define  GPIO_Speed_25MHz   GPIO_Medium_Speed
#define  GPIO_Speed_50MHz   GPIO_Fast_Speed
#define  GPIO_Speed_100MHz  GPIO_High_Speed

#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Low_Speed) || ((SPEED) == GPIO_Medium_Speed) || \
                              ((SPEED) == GPIO_Fast_Speed)||  ((SPEED) == GPIO_High_Speed))

/**
  * 简介:  GPIO 配置 PullUp PullDown 枚举
  */
typedef enum {
    GPIO_PuPd_NOPULL = 0x00,
    GPIO_PuPd_UP     = 0x01,
    GPIO_PuPd_DOWN   = 0x02
} GPIOPuPd_TypeDef;
#define IS_GPIO_PUPD(PUPD) (((PUPD) == GPIO_PuPd_NOPULL) || ((PUPD) == GPIO_PuPd_UP) || \
                            ((PUPD) == GPIO_PuPd_DOWN))

/**
  * 简介:  GPIO Bit SET 和 Bit RESET 枚举
  */
typedef enum {
    Bit_RESET = 0,
    Bit_SET
} BitAction;
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))


/**
  * 简介:    GPIO初始化结构定义
  */
typedef struct {
    uint32_t GPIO_Pin;              /*!< 指定要配置的 GPIO 引脚。
                                    该参数可以是 @ref GPIO_pins_define 的任意值 */

    GPIOMode_TypeDef GPIO_Mode;     /*!< 指定所选引脚的操作模式。
                                    该参数可以是 @ref GPIOMode_TypeDef 的值 */

    GPIOSpeed_TypeDef GPIO_Speed;   /*!< 指定选定引脚的速度。
                                    该参数可以是 @ref GPIOSpeed_TypeDef 的值 */

    GPIOOType_TypeDef GPIO_OType;   /*!< 指定所选引脚的操作输出类型。
                                    该参数可以是 @ref GPIOOType_TypeDef 的值 */

    GPIOPuPd_TypeDef GPIO_PuPd;     /*!< 指定所选引脚的操作上拉/下拉。
                                    该参数可以是 @ref GPIOPuPd_TypeDef 的值 */
} GPIO_InitTypeDef;

/* 导出的常量 --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
  */

/** @defgroup GPIO_pins_define
  */
#define GPIO_Pin_0                 ((uint16_t)0x0001)  /* 选择引脚 0 */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /* 选择引脚 1 */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /* 选择引脚 2 */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /* 选择引脚 3 */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /* 选择引脚 4 */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /* 选择引脚 5 */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /* 选择引脚 6 */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /* 选择引脚 7 */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /* 选择引脚 8 */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /* 选择引脚 9 */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /* 选择引脚 10 */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /* 选择引脚 11 */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /* 选择引脚 12 */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /* 选择引脚 13 */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /* 选择引脚 14 */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /* 选择引脚 15 */
#define GPIO_Pin_All               ((uint16_t)0xFFFF)  /* 已选择所有引脚 */

#define GPIO_PIN_MASK              ((uint32_t)0x0000FFFF) /* 断言测试的 PIN 掩码 */
#define IS_GPIO_PIN(PIN)           (((PIN) & GPIO_PIN_MASK ) != (uint32_t)0x00)
#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))


/** @defgroup GPIO_Pin_sources
  */
#define GPIO_PinSource0            ((uint8_t)0x00)
#define GPIO_PinSource1            ((uint8_t)0x01)
#define GPIO_PinSource2            ((uint8_t)0x02)
#define GPIO_PinSource3            ((uint8_t)0x03)
#define GPIO_PinSource4            ((uint8_t)0x04)
#define GPIO_PinSource5            ((uint8_t)0x05)
#define GPIO_PinSource6            ((uint8_t)0x06)
#define GPIO_PinSource7            ((uint8_t)0x07)
#define GPIO_PinSource8            ((uint8_t)0x08)
#define GPIO_PinSource9            ((uint8_t)0x09)
#define GPIO_PinSource10           ((uint8_t)0x0A)
#define GPIO_PinSource11           ((uint8_t)0x0B)
#define GPIO_PinSource12           ((uint8_t)0x0C)
#define GPIO_PinSource13           ((uint8_t)0x0D)
#define GPIO_PinSource14           ((uint8_t)0x0E)
#define GPIO_PinSource15           ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))

/** @defgroup GPIO_Alternat_function_selection_define
  */
/**
  * 简介: AF 0 选择
  */
#define GPIO_AF_RTC_50Hz      ((uint8_t)0x00)  /* RTC_50Hz 备用函数映射 */
#define GPIO_AF_MCO           ((uint8_t)0x00)  /* MCO(MCO1 和 MCO2)复用功能映射 */
#define GPIO_AF_TAMPER        ((uint8_t)0x00)  /* TAMPER(TAMPER_1 和 TAMPER_2)备用函数映射 */
#define GPIO_AF_SWJ           ((uint8_t)0x00)  /* SWJ(SWD 和 JTAG)复用功能映射 */
#define GPIO_AF_TRACE         ((uint8_t)0x00)  /* TRACE 备用函数映射 */
#if defined(STM32F446xx)
#define GPIO_AF0_TIM2         ((uint8_t)0x00)  /* TIM2 替代函数映射 */
#endif /* STM32F446xx */

/**
  * 简介: AF 1 选择
  */
#define GPIO_AF_TIM1          ((uint8_t)0x01)  /* TIM1 替代函数映射 */
#define GPIO_AF_TIM2          ((uint8_t)0x01)  /* TIM2 替代函数映射 */
#if defined(STM32F410xx) || defined(STM32F413_423xx)
#define GPIO_AF_LPTIM         ((uint8_t)0x01)  /* LPTIM 替代函数映射 */
#endif /* STM32F410xx || STM32F413_423xx */
/**
  * 简介: AF 2选择
  */
#define GPIO_AF_TIM3          ((uint8_t)0x02)  /* TIM3 替代函数映射 */
#define GPIO_AF_TIM4          ((uint8_t)0x02)  /* TIM4 替代函数映射 */
#define GPIO_AF_TIM5          ((uint8_t)0x02)  /* TIM5 替代函数映射 */

/**
  * 简介: AF 3选择
  */
#define GPIO_AF_TIM8          ((uint8_t)0x03)  /* TIM8 替代函数映射 */
#define GPIO_AF_TIM9          ((uint8_t)0x03)  /* TIM9 替代函数映射 */
#define GPIO_AF_TIM10         ((uint8_t)0x03)  /* TIM10 替代函数映射 */
#define GPIO_AF_TIM11         ((uint8_t)0x03)  /* TIM11 替代函数映射 */
#if defined(STM32F446xx)
#define GPIO_AF3_CEC          ((uint8_t)0x03)  /* CEC 替代函数映射 */
#endif /* STM32F446xx */
#if defined(STM32F413_423xx)
#define GPIO_AF3_DFSDM2       ((uint8_t)0x03)  /* DFSDM2 替代函数映射 */
#endif /* STM32F413_423xx */
/**
  * 简介: AF 4选择
  */
#define GPIO_AF_I2C1          ((uint8_t)0x04)  /* I2C1 备用函数映射 */
#define GPIO_AF_I2C2          ((uint8_t)0x04)  /* I2C2 备用函数映射 */
#define GPIO_AF_I2C3          ((uint8_t)0x04)  /* I2C3 备用函数映射 */
#if defined(STM32F446xx)
#define GPIO_AF4_CEC          ((uint8_t)0x04)  /* CEC 备用函数映射 */
#endif /* STM32F446xx */
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
#define GPIO_AF_FMPI2C        ((uint8_t)0x04)  /* FMPI2C 备用函数映射 */
#endif /* STM32F410xx || STM32F446xx */

/**
  * 简介: AF 5选择
  */
#define GPIO_AF_SPI1          ((uint8_t)0x05)  /* SPI1/I2S1 备用函数映射 */
#define GPIO_AF_SPI2          ((uint8_t)0x05)  /* SPI2/I2S2 备用函数映射 */
#define GPIO_AF5_SPI3         ((uint8_t)0x05)  /* SPI3/I2S3 备用函数映射 (Only for STM32F411xE and STM32F413_423xx Devices) */
#define GPIO_AF_SPI4          ((uint8_t)0x05)  /* SPI4/I2S4 备用函数映射 */
#define GPIO_AF_SPI5          ((uint8_t)0x05)  /* SPI5 备用函数映射      */
#define GPIO_AF_SPI6          ((uint8_t)0x05)  /* SPI6 备用函数映射      */

/**
  * 简介: AF 6选择
  */
#define GPIO_AF_SPI3          ((uint8_t)0x06)  /* SPI3/I2S3 备用函数映射 */
#define GPIO_AF6_SPI1         ((uint8_t)0x06)  /* SPI1 备用函数映射 (Only for STM32F410xx Devices) */
#define GPIO_AF6_SPI2         ((uint8_t)0x06)  /* SPI2 备用函数映射 (Only for STM32F410xx/STM32F411xE Devices) */
#define GPIO_AF6_SPI4         ((uint8_t)0x06)  /* SPI4 备用函数映射 (Only for STM32F411xE Devices) */
#define GPIO_AF6_SPI5         ((uint8_t)0x06)  /* SPI5 备用函数映射 (Only for STM32F410xx/STM32F411xE Devices) */
#define GPIO_AF_SAI1          ((uint8_t)0x06)  /* SAI1 备用函数映射      */
#define GPIO_AF_I2S2ext       ((uint8_t)0x06)  /* I2S2ext_SD 备用函数映射 (only for STM32F412xG and STM32F413_423xx Devices) */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF6_DFSDM1       ((uint8_t)0x06)  /* DFSDM1 备用函数映射 */
#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F413_423xx)
#define GPIO_AF6_DFSDM2       ((uint8_t)0x06)  /* DFSDM2 备用函数映射 */
#endif /* STM32F413_423xx */

/**
  * 简介: AF 7选择
  */
#define GPIO_AF_USART1         ((uint8_t)0x07)  /* USART1 备用函数映射  */
#define GPIO_AF_USART2         ((uint8_t)0x07)  /* USART2 备用函数映射  */
#define GPIO_AF_USART3         ((uint8_t)0x07)  /* USART3 备用函数映射  */
#define GPIO_AF7_SPI3          ((uint8_t)0x07)  /* SPI3/I2S3ext 备用函数映射 */
#if defined(STM32F413_423xx)
#define GPIO_AF7_DFSDM2        ((uint8_t)0x07)  /* DFSDM2 备用函数映射     */
#define GPIO_AF7_SAI1          ((uint8_t)0x07)  /* SAI1 备用函数映射       */
#endif /* STM32F413_423xx */

/**
  * 简介: AF 7选择传统
  */
#define GPIO_AF_I2S3ext   GPIO_AF7_SPI3

/**
  * 简介: AF 8选择
  */
#define GPIO_AF_UART4         ((uint8_t)0x08)  /* UART4 备用函数映射  */
#define GPIO_AF_UART5         ((uint8_t)0x08)  /* UART5 备用函数映射  */
#define GPIO_AF_USART6        ((uint8_t)0x08)  /* USART6 备用函数映射 */
#define GPIO_AF_UART7         ((uint8_t)0x08)  /* UART7 备用函数映射  */
#define GPIO_AF_UART8         ((uint8_t)0x08)  /* UART8 备用函数映射  */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF8_USART3        ((uint8_t)0x08)  /* USART3 备用函数映射 */
#define GPIO_AF8_DFSDM1        ((uint8_t)0x08)  /* DFSDM 备用函数映射  */
#define GPIO_AF8_CAN1          ((uint8_t)0x08)  /* CAN1 备用函数映射   */
#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F446xx)
#define GPIO_AF8_SAI2          ((uint8_t)0x08)  /* SAI2 备用函数映射 */
#define GPIO_AF_SPDIF         ((uint8_t)0x08)   /* SPDIF 备用函数映射 */
#endif /* STM32F446xx */

/**
  * 简介: AF 9选择
  */
#define GPIO_AF_CAN1          ((uint8_t)0x09)  /* CAN1 备用函数映射  */
#define GPIO_AF_CAN2          ((uint8_t)0x09)  /* CAN2 备用函数映射  */
#define GPIO_AF_TIM12         ((uint8_t)0x09)  /* TIM12 备用函数映射 */
#define GPIO_AF_TIM13         ((uint8_t)0x09)  /* TIM13 备用函数映射 */
#define GPIO_AF_TIM14         ((uint8_t)0x09)  /* TIM14 备用函数映射 */
#define GPIO_AF9_I2C2         ((uint8_t)0x09)  /* I2C2 备用函数映射 (Only for STM32F401xx/STM32F410xx/STM32F411xE/STM32F412xG/STM32F413_423xx Devices) */
#define GPIO_AF9_I2C3         ((uint8_t)0x09)  /* I2C3 备用函数映射 (Only for STM32F401xx/STM32F411xE/STM32F412xG and STM32F413_423xx Devices) */
#if defined(STM32F446xx)
#define GPIO_AF9_SAI2         ((uint8_t)0x09)  /* SAI2 备用函数映射 */
#endif /* STM32F446xx */
#define GPIO_AF9_LTDC         ((uint8_t)0x09)  /* LTDC 备用函数映射 */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
#define GPIO_AF9_QUADSPI      ((uint8_t)0x09)  /* QuadSPI 备用函数映射 */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF9_FMPI2C       ((uint8_t)0x09)  /* FMPI2C 备用函数映射 (Only for STM32F410xx Devices) */
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx */

/**
  * 简介: AF 10选择
  */
#define GPIO_AF_OTG_FS         ((uint8_t)0xA)  /* OTG_FS 备用函数映射 */
#define GPIO_AF_OTG_HS         ((uint8_t)0xA)  /* OTG_HS 备用函数映射 */
#if defined(STM32F446xx)
#define GPIO_AF10_SAI2         ((uint8_t)0x0A)  /* SAI2 备用函数映射 */
#endif /* STM32F446xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
#define GPIO_AF10_QUADSPI      ((uint8_t)0x0A)  /* QuadSPI 备用函数映射 */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF10_FMC           ((uint8_t)0xA)  /* FMC 备用函数映射    */
#define GPIO_AF10_DFSDM1         ((uint8_t)0xA) /* DFSDM 备用函数映射  */
#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F413_423xx)
#define GPIO_AF10_DFSDM2        ((uint8_t)0x0A)  /* DFSDM2 备用函数映射 */
#define GPIO_AF10_SAI1          ((uint8_t)0x0A)  /* SAI1 备用函数映射   */
#endif /* STM32F413_423xx */
/**
  * 简介: AF 11 selection
  */
#define GPIO_AF_ETH             ((uint8_t)0x0B)  /* ETHERNET 备用函数映射 */
#if defined(STM32F413_423xx)
#define GPIO_AF11_UART4         ((uint8_t)0x0B)  /* UART4 备用函数映射  */
#define GPIO_AF11_UART5         ((uint8_t)0x0B)  /* UART5 备用函数映射  */
#define GPIO_AF11_UART9         ((uint8_t)0x0B)  /* UART9 备用函数映射  */
#define GPIO_AF11_UART10        ((uint8_t)0x0B)  /* UART10 备用函数映射 */
#define GPIO_AF11_CAN3          ((uint8_t)0x0B)  /* CAN3 备用函数映射   */
#endif /* STM32F413_423xx */

/**
  * 简介: AF 12选择
  */
#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define GPIO_AF_FSMC             ((uint8_t)0xC)  /* FSMC 备用函数映射                     */
#endif /* STM32F40_41xxx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
#define GPIO_AF_FMC              ((uint8_t)0xC)  /* FMC 备用函数映射                      */
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F446xx || STM32F469_479xx */

#define GPIO_AF_OTG_HS_FS        ((uint8_t)0xC)  /* OTG HS configured in FS, 备用函数映射 */
#define GPIO_AF_SDIO             ((uint8_t)0xC)  /* SDIO 备用函数映射                     */

/**
  * 简介: AF 13选择
  */
#define GPIO_AF_DCMI          ((uint8_t)0x0D)  /* DCMI 备用函数映射 */
#if defined(STM32F469_479xx)
#define GPIO_AF_DSI           ((uint8_t)0x0D)  /* DSI 备用函数映射 */
#endif /* STM32F469_479xx */
/**
  * 简介: AF 14选择
  */
#define GPIO_AF_LTDC          ((uint8_t)0x0E)  /* LCD-TFT 备用函数映射 */
#if defined(STM32F413_423xx)
#define GPIO_AF14_RNG         ((uint8_t)0x0E)  /* RNG 备用函数映射  */
#endif /* STM32F413_423xx */

/**
  * 简介: AF 15选择
  */
#define GPIO_AF_EVENTOUT      ((uint8_t)0x0F)  /* EVENTOUT 备用函数映射 */

#if defined(STM32F40_41xxx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_RTC_50Hz)  || ((AF) == GPIO_AF_TIM14)     || \
                          ((AF) == GPIO_AF_MCO)       || ((AF) == GPIO_AF_TAMPER)    || \
                          ((AF) == GPIO_AF_SWJ)       || ((AF) == GPIO_AF_TRACE)     || \
                          ((AF) == GPIO_AF_TIM1)      || ((AF) == GPIO_AF_TIM2)      || \
                          ((AF) == GPIO_AF_TIM3)      || ((AF) == GPIO_AF_TIM4)      || \
                          ((AF) == GPIO_AF_TIM5)      || ((AF) == GPIO_AF_TIM8)      || \
                          ((AF) == GPIO_AF_I2C1)      || ((AF) == GPIO_AF_I2C2)      || \
                          ((AF) == GPIO_AF_I2C3)      || ((AF) == GPIO_AF_SPI1)      || \
                          ((AF) == GPIO_AF_SPI2)      || ((AF) == GPIO_AF_TIM13)     || \
                          ((AF) == GPIO_AF_SPI3)      || ((AF) == GPIO_AF_TIM14)     || \
                          ((AF) == GPIO_AF_USART1)    || ((AF) == GPIO_AF_USART2)    || \
                          ((AF) == GPIO_AF_USART3)    || ((AF) == GPIO_AF_UART4)     || \
                          ((AF) == GPIO_AF_UART5)     || ((AF) == GPIO_AF_USART6)    || \
                          ((AF) == GPIO_AF_CAN1)      || ((AF) == GPIO_AF_CAN2)      || \
                          ((AF) == GPIO_AF_OTG_FS)    || ((AF) == GPIO_AF_OTG_HS)    || \
                          ((AF) == GPIO_AF_ETH)       || ((AF) == GPIO_AF_OTG_HS_FS) || \
                          ((AF) == GPIO_AF_SDIO)      || ((AF) == GPIO_AF_DCMI)      || \
                          ((AF) == GPIO_AF_EVENTOUT)  || ((AF) == GPIO_AF_FSMC))
#endif /* STM32F40_41xxx */

#if defined(STM32F401xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_RTC_50Hz)  || ((AF) == GPIO_AF_TIM14)     || \
                          ((AF) == GPIO_AF_MCO)       || ((AF) == GPIO_AF_TAMPER)    || \
                          ((AF) == GPIO_AF_SWJ)       || ((AF) == GPIO_AF_TRACE)     || \
                          ((AF) == GPIO_AF_TIM1)      || ((AF) == GPIO_AF_TIM2)      || \
                          ((AF) == GPIO_AF_TIM3)      || ((AF) == GPIO_AF_TIM4)      || \
                          ((AF) == GPIO_AF_TIM5)      || ((AF) == GPIO_AF_TIM8)      || \
                          ((AF) == GPIO_AF_I2C1)      || ((AF) == GPIO_AF_I2C2)      || \
                          ((AF) == GPIO_AF_I2C3)      || ((AF) == GPIO_AF_SPI1)      || \
                          ((AF) == GPIO_AF_SPI2)      || ((AF) == GPIO_AF_TIM13)     || \
                          ((AF) == GPIO_AF_SPI3)      || ((AF) == GPIO_AF_TIM14)     || \
                          ((AF) == GPIO_AF_USART1)    || ((AF) == GPIO_AF_USART2)    || \
                          ((AF) == GPIO_AF_SDIO)      || ((AF) == GPIO_AF_USART6)    || \
                          ((AF) == GPIO_AF_OTG_FS)    || ((AF) == GPIO_AF_OTG_HS)    || \
                          ((AF) == GPIO_AF_EVENTOUT)  || ((AF) == GPIO_AF_SPI4))
#endif /* STM32F401xx */

#if defined(STM32F411xE)
#define IS_GPIO_AF(AF)   (((AF) < 16) && ((AF) != 11) && ((AF) != 13) && ((AF) != 14))
#endif /* STM32F411xE */

#if defined(STM32F410xx)
#define IS_GPIO_AF(AF)   (((AF) < 10) || ((AF) == 15))
#endif /* STM32F410xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_RTC_50Hz)  || ((AF) == GPIO_AF_TIM14)     || \
                          ((AF) == GPIO_AF_MCO)       || ((AF) == GPIO_AF_TAMPER)    || \
                          ((AF) == GPIO_AF_SWJ)       || ((AF) == GPIO_AF_TRACE)     || \
                          ((AF) == GPIO_AF_TIM1)      || ((AF) == GPIO_AF_TIM2)      || \
                          ((AF) == GPIO_AF_TIM3)      || ((AF) == GPIO_AF_TIM4)      || \
                          ((AF) == GPIO_AF_TIM5)      || ((AF) == GPIO_AF_TIM8)      || \
                          ((AF) == GPIO_AF_I2C1)      || ((AF) == GPIO_AF_I2C2)      || \
                          ((AF) == GPIO_AF_I2C3)      || ((AF) == GPIO_AF_SPI1)      || \
                          ((AF) == GPIO_AF_SPI2)      || ((AF) == GPIO_AF_TIM13)     || \
                          ((AF) == GPIO_AF_SPI3)      || ((AF) == GPIO_AF_TIM14)     || \
                          ((AF) == GPIO_AF_USART1)    || ((AF) == GPIO_AF_USART2)    || \
                          ((AF) == GPIO_AF_USART3)    || ((AF) == GPIO_AF_UART4)     || \
                          ((AF) == GPIO_AF_UART5)     || ((AF) == GPIO_AF_USART6)    || \
                          ((AF) == GPIO_AF_CAN1)      || ((AF) == GPIO_AF_CAN2)      || \
                          ((AF) == GPIO_AF_OTG_FS)    || ((AF) == GPIO_AF_OTG_HS)    || \
                          ((AF) == GPIO_AF_ETH)       || ((AF) == GPIO_AF_OTG_HS_FS) || \
                          ((AF) == GPIO_AF_SDIO)      || ((AF) == GPIO_AF_DCMI)      || \
                          ((AF) == GPIO_AF_EVENTOUT)  || ((AF) == GPIO_AF_SPI4)      || \
                          ((AF) == GPIO_AF_SPI5)      || ((AF) == GPIO_AF_SPI6)      || \
                          ((AF) == GPIO_AF_UART7)     || ((AF) == GPIO_AF_UART8)     || \
                          ((AF) == GPIO_AF_FMC)       ||  ((AF) == GPIO_AF_SAI1)     || \
                          ((AF) == GPIO_AF_LTDC))
#endif /* STM32F427_437xx ||  STM32F429_439xx */

#if defined(STM32F412xG)
#define IS_GPIO_AF(AF)   (((AF) < 16) && ((AF) != 11) && ((AF) != 14))
#endif /* STM32F412xG */

#if defined(STM32F413_423xx)
#define IS_GPIO_AF(AF)   (((AF) < 16) && ((AF) != 13))
#endif /* STM32F413_423xx */

#if defined(STM32F446xx)
#define IS_GPIO_AF(AF)   (((AF) < 16) && ((AF) != 11) && ((AF) != 14))
#endif /* STM32F446xx */

#if defined(STM32F469_479xx)
#define IS_GPIO_AF(AF)   ((AF) < 16)
#endif /* STM32F469_479xx */


/** @defgroup GPIO_Legacy
  */
#define GPIO_Mode_AIN           GPIO_Mode_AN

#define GPIO_AF_OTG1_FS         GPIO_AF_OTG_FS
#define GPIO_AF_OTG2_HS         GPIO_AF_OTG_HS
#define GPIO_AF_OTG2_FS         GPIO_AF_OTG_HS_FS



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 GPIO 配置设置为默认复位状态的函数 ****/
void GPIO_DeInit(GPIO_TypeDef* GPIOx); // 将 GPIOx 外设寄存器取消初始化为其缺省复位值。

/* 初始化和配置功能 *********************************/
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct); // 根据GPIO_InitStruct中指定的参数初始化 GPIOx 外设。
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct); // 用每个GPIO_InitStruct成员的默认值填充该成员。
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin); // 锁定 GPIO 引脚配置寄存器。

/* GPIO 读写功能 **********************************************/
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin); // 读取指定的输入端口引脚。
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx); // 读取指定的 GPIO 输入数据端口。
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin); // 读取指定的输出数据端口位。
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx); // 读取指定的 GPIO 输出数据端口。
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin); // 设置选定的数据端口位。
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin); // 清除选定的数据端口位。
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal); // 设置或清除选定的数据端口位。
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal); // 将数据写入指定的 GPIO 数据端口。
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin); // 切换指定的 GPIO 引脚。

/* GPIO 复用功能配置功能 ****************************/
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF); // 更改指定引脚的映射。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_GPIO_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
