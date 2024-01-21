/**
  ******************************************************************************
  * 文件:    stm32f4xx_usart.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含USART固件库的所有功能原型。
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_USART_H
#define __STM32F4xx_USART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  USART 初始化结构定义
  */
typedef struct {
    uint32_t USART_BaudRate;            /*!< 该成员配置 USART 通信波特率。
                                            波特率使用以下公式计算:
                                             - IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (USART_InitStruct->USART_BaudRate)))
                                             - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 8 * (OVR8+1)) + 0.5
                                            其中 OVR8 是 CR1 寄存器中的"8 模式过采样"配置位。*/

    uint16_t USART_WordLength;          /*!< 指定帧中传输或接收的数据位数。
                                            该参数可以是@ref USART_Word_Length 的值 */

    uint16_t USART_StopBits;            /*!< 指定传输的停止位数。
                                            此参数可以是 @ref USART_Stop_Bits 的值 */

    uint16_t USART_Parity;              /*!< 指定奇偶校验模式。
                                            此参数可以是 @ref USART_Parity 的值
                                            @note 启用奇偶校验时，计算出的奇偶校验插入到传输数据的 MSB 位置(字长设置为 9 个数据位时为第 9 位;
											                      字长设置为 8 个数据位时为第 8 位)。 */

    uint16_t USART_Mode;                /*!< 指定是启用还是禁用接收或传输模式。
                                            该参数可以是@ref USART_Mode 的值 */

    uint16_t USART_HardwareFlowControl; /*!< 指定是启用还是禁用硬件流控制模式。
											                      该参数可以是@ref USART 硬件流控制的值 */
} USART_InitTypeDef;

/**
  * 简介:  USART 时钟初始化结构定义
  */
typedef struct {

    uint16_t USART_Clock;   /*!< 指定是启用还是禁用 USART 时钟。
                                该参数可以是@ref USART_Clock 的值 */

    uint16_t USART_CPOL;    /*!< 指定串行时钟的稳定状态。
                                此参数可以是 @ref USART_Clock_Polarity 的值 */

    uint16_t USART_CPHA;    /*!< 指定进行位捕获的时钟转换。
                                该参数可以是@ref USART_Clock_Phase 的值 */

    uint16_t USART_LastBit; /*!< 指定是否与最后发送的时钟脉冲相对应
                                在同步模式下，数据位 (MSB) 必须在 SCLK 引脚上输出。
                                此参数可以是 @ref USART_Last_Bit 的值 */
} USART_ClockInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup USART_Exported_Constants
  * @{
  */
#define IS_USART_ALL_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                     ((PERIPH) == USART2) || \
                                     ((PERIPH) == USART3) || \
                                     ((PERIPH) == UART4)  || \
                                     ((PERIPH) == UART5)  || \
                                     ((PERIPH) == USART6) || \
                                     ((PERIPH) == UART7)  || \
                                     ((PERIPH) == UART8)  || \
                                     ((PERIPH) == UART9)  || \
                                     ((PERIPH) == UART10))

#define IS_USART_1236_PERIPH(PERIPH) (((PERIPH) == USART1) || \
                                      ((PERIPH) == USART2) || \
                                      ((PERIPH) == USART3) || \
                                      ((PERIPH) == USART6))

/** @defgroup USART_Word_Length
  * @{
  */
#define USART_WordLength_8b                  ((uint16_t)0x0000)
#define USART_WordLength_9b                  ((uint16_t)0x1000)

#define IS_USART_WORD_LENGTH(LENGTH) (((LENGTH) == USART_WordLength_8b) || \
                                      ((LENGTH) == USART_WordLength_9b))
/**
  * @}
  */

/** @defgroup USART_Stop_Bits
  * @{
  */
#define USART_StopBits_1                     ((uint16_t)0x0000)
#define USART_StopBits_0_5                   ((uint16_t)0x1000)
#define USART_StopBits_2                     ((uint16_t)0x2000)
#define USART_StopBits_1_5                   ((uint16_t)0x3000)
#define IS_USART_STOPBITS(STOPBITS) (((STOPBITS) == USART_StopBits_1) || \
                                     ((STOPBITS) == USART_StopBits_0_5) || \
                                     ((STOPBITS) == USART_StopBits_2) || \
                                     ((STOPBITS) == USART_StopBits_1_5))
/**
  * @}
  */

/** @defgroup USART_Parity
  * @{
  */
#define USART_Parity_No                      ((uint16_t)0x0000)
#define USART_Parity_Even                    ((uint16_t)0x0400)
#define USART_Parity_Odd                     ((uint16_t)0x0600)
#define IS_USART_PARITY(PARITY) (((PARITY) == USART_Parity_No) || \
                                 ((PARITY) == USART_Parity_Even) || \
                                 ((PARITY) == USART_Parity_Odd))
/**
  * @}
  */

/** @defgroup USART_Mode
  * @{
  */
#define USART_Mode_Rx                        ((uint16_t)0x0004)
#define USART_Mode_Tx                        ((uint16_t)0x0008)
#define IS_USART_MODE(MODE) ((((MODE) & (uint16_t)0xFFF3) == 0x00) && ((MODE) != (uint16_t)0x00))
/**
  * @}
  */

/** @defgroup USART_Hardware_Flow_Control
  * @{
  */
#define USART_HardwareFlowControl_None       ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS        ((uint16_t)0x0100)
#define USART_HardwareFlowControl_CTS        ((uint16_t)0x0200)
#define USART_HardwareFlowControl_RTS_CTS    ((uint16_t)0x0300)
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)\
    (((CONTROL) == USART_HardwareFlowControl_None) || \
     ((CONTROL) == USART_HardwareFlowControl_RTS) || \
     ((CONTROL) == USART_HardwareFlowControl_CTS) || \
     ((CONTROL) == USART_HardwareFlowControl_RTS_CTS))
/**
  * @}
  */

/** @defgroup USART_Clock
  * @{
  */
#define USART_Clock_Disable                  ((uint16_t)0x0000)
#define USART_Clock_Enable                   ((uint16_t)0x0800)
#define IS_USART_CLOCK(CLOCK) (((CLOCK) == USART_Clock_Disable) || \
                               ((CLOCK) == USART_Clock_Enable))
/**
  * @}
  */

/** @defgroup USART_Clock_Polarity
  * @{
  */
#define USART_CPOL_Low                       ((uint16_t)0x0000)
#define USART_CPOL_High                      ((uint16_t)0x0400)
#define IS_USART_CPOL(CPOL) (((CPOL) == USART_CPOL_Low) || ((CPOL) == USART_CPOL_High))

/**
  * @}
  */

/** @defgroup USART_Clock_Phase
  * @{
  */
#define USART_CPHA_1Edge                     ((uint16_t)0x0000)
#define USART_CPHA_2Edge                     ((uint16_t)0x0200)
#define IS_USART_CPHA(CPHA) (((CPHA) == USART_CPHA_1Edge) || ((CPHA) == USART_CPHA_2Edge))

/**
  * @}
  */

/** @defgroup USART_Last_Bit
  * @{
  */
#define USART_LastBit_Disable                ((uint16_t)0x0000)
#define USART_LastBit_Enable                 ((uint16_t)0x0100)
#define IS_USART_LASTBIT(LASTBIT) (((LASTBIT) == USART_LastBit_Disable) || \
                                   ((LASTBIT) == USART_LastBit_Enable))
/**
  * @}
  */

/** @defgroup USART_Interrupt_definition
  * @{
  */
#define USART_IT_PE                          ((uint16_t)0x0028)
#define USART_IT_TXE                         ((uint16_t)0x0727)
#define USART_IT_TC                          ((uint16_t)0x0626)
#define USART_IT_RXNE                        ((uint16_t)0x0525)
#define USART_IT_ORE_RX                      ((uint16_t)0x0325) /* 如果 RXNEIE 位置位，则产生中断 */
#define USART_IT_IDLE                        ((uint16_t)0x0424)
#define USART_IT_LBD                         ((uint16_t)0x0846)
#define USART_IT_CTS                         ((uint16_t)0x096A)
#define USART_IT_ERR                         ((uint16_t)0x0060)
#define USART_IT_ORE_ER                      ((uint16_t)0x0360) /* 如果 EIE 位置位，则产生中断 */
#define USART_IT_NE                          ((uint16_t)0x0260)
#define USART_IT_FE                          ((uint16_t)0x0160)

/** @defgroup USART_Legacy
  * @{
  */
#define USART_IT_ORE                          USART_IT_ORE_ER
/**
  * @}
  */
#define IS_USART_CONFIG_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                                ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                                ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                                ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ERR))
#define IS_USART_GET_IT(IT) (((IT) == USART_IT_PE) || ((IT) == USART_IT_TXE) || \
                             ((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                             ((IT) == USART_IT_IDLE) || ((IT) == USART_IT_LBD) || \
                             ((IT) == USART_IT_CTS) || ((IT) == USART_IT_ORE) || \
                             ((IT) == USART_IT_ORE_RX) || ((IT) == USART_IT_ORE_ER) || \
                             ((IT) == USART_IT_NE) || ((IT) == USART_IT_FE))
#define IS_USART_CLEAR_IT(IT) (((IT) == USART_IT_TC) || ((IT) == USART_IT_RXNE) || \
                               ((IT) == USART_IT_LBD) || ((IT) == USART_IT_CTS))
/**
  * @}
  */

/** @defgroup USART_DMA_Requests
  * @{
  */
#define USART_DMAReq_Tx                      ((uint16_t)0x0080)
#define USART_DMAReq_Rx                      ((uint16_t)0x0040)
#define IS_USART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFF3F) == 0x00) && ((DMAREQ) != (uint16_t)0x00))

/**
  * @}
  */

/** @defgroup USART_WakeUp_methods
  * @{
  */
#define USART_WakeUp_IdleLine                ((uint16_t)0x0000)
#define USART_WakeUp_AddressMark             ((uint16_t)0x0800)
#define IS_USART_WAKEUP(WAKEUP) (((WAKEUP) == USART_WakeUp_IdleLine) || \
                                 ((WAKEUP) == USART_WakeUp_AddressMark))
/**
  * @}
  */

/** @defgroup USART_LIN_Break_Detection_Length
  * @{
  */
#define USART_LINBreakDetectLength_10b      ((uint16_t)0x0000)
#define USART_LINBreakDetectLength_11b      ((uint16_t)0x0020)
#define IS_USART_LIN_BREAK_DETECT_LENGTH(LENGTH) \
    (((LENGTH) == USART_LINBreakDetectLength_10b) || \
     ((LENGTH) == USART_LINBreakDetectLength_11b))
/**
  * @}
  */

/** @defgroup USART_IrDA_Low_Power
  * @{
  */
#define USART_IrDAMode_LowPower              ((uint16_t)0x0004)
#define USART_IrDAMode_Normal                ((uint16_t)0x0000)
#define IS_USART_IRDA_MODE(MODE) (((MODE) == USART_IrDAMode_LowPower) || \
                                  ((MODE) == USART_IrDAMode_Normal))
/**
  * @}
  */

/** @defgroup USART_Flags
  * @{
  */
#define USART_FLAG_CTS                       ((uint16_t)0x0200)
#define USART_FLAG_LBD                       ((uint16_t)0x0100)
#define USART_FLAG_TXE                       ((uint16_t)0x0080)
#define USART_FLAG_TC                        ((uint16_t)0x0040)
#define USART_FLAG_RXNE                      ((uint16_t)0x0020)
#define USART_FLAG_IDLE                      ((uint16_t)0x0010)
#define USART_FLAG_ORE                       ((uint16_t)0x0008)
#define USART_FLAG_NE                        ((uint16_t)0x0004)
#define USART_FLAG_FE                        ((uint16_t)0x0002)
#define USART_FLAG_PE                        ((uint16_t)0x0001)
#define IS_USART_FLAG(FLAG) (((FLAG) == USART_FLAG_PE) || ((FLAG) == USART_FLAG_TXE) || \
                             ((FLAG) == USART_FLAG_TC) || ((FLAG) == USART_FLAG_RXNE) || \
                             ((FLAG) == USART_FLAG_IDLE) || ((FLAG) == USART_FLAG_LBD) || \
                             ((FLAG) == USART_FLAG_CTS) || ((FLAG) == USART_FLAG_ORE) || \
                             ((FLAG) == USART_FLAG_NE) || ((FLAG) == USART_FLAG_FE))

#define IS_USART_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFC9F) == 0x00) && ((FLAG) != (uint16_t)0x00))

#define IS_USART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 7500001))
#define IS_USART_ADDRESS(ADDRESS) ((ADDRESS) <= 0xF)
#define IS_USART_DATA(DATA) ((DATA) <= 0x1FF)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 USART 配置设置为默认复位状态的函数 ***/
void USART_DeInit(USART_TypeDef* USARTx); // 将 USARTx 外设寄存器去初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void USART_Init(USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct);  // 根据 USART_InitStruct 中的指定参数初始化 USARTx 外设。
void USART_StructInit(USART_InitTypeDef* USART_InitStruct);                   // 用每个USART_InitStruct成员的默认值填充该成员。
void USART_ClockInit(USART_TypeDef* USARTx, USART_ClockInitTypeDef* USART_ClockInitStruct); // 根据 USART_ClockInitStruct 中的指定参数初始化 USARTx 外设时钟。
void USART_ClockStructInit(USART_ClockInitTypeDef* USART_ClockInitStruct);    // 用其默认值填充每个USART_ClockInitStruct成员。
void USART_Cmd(USART_TypeDef* USARTx, FunctionalState NewState);              // 启用或禁用指定的 USART 外设。
void USART_SetPrescaler(USART_TypeDef* USARTx, uint8_t USART_Prescaler);      // 设置系统时钟预分频器。
void USART_OverSampling8Cmd(USART_TypeDef* USARTx, FunctionalState NewState); // 启用或禁用 USART 的 8x 过采样模式。
void USART_OneBitMethodCmd(USART_TypeDef* USARTx, FunctionalState NewState);  // 启用或禁用 USART 的一位采样方法。

/* 数据传输功能 ***************************************************/
void USART_SendData(USART_TypeDef* USARTx, uint16_t Data); // 通过 USARTx 外设传输单个数据。
uint16_t USART_ReceiveData(USART_TypeDef* USARTx);         // 返回 USARTx 外设最近接收到的数据。

/* 多处理器通讯功能 ************************************/
void USART_SetAddress(USART_TypeDef* USARTx, uint8_t USART_Address);    // 设置 USART 节点的地址。
void USART_WakeUpConfig(USART_TypeDef* USARTx, uint16_t USART_WakeUp);  // 选择 USART 唤醒方法。
void USART_ReceiverWakeUpCmd(USART_TypeDef* USARTx, FunctionalState NewState); // 确定 USART 是否处于静音模式。

/* LIN 模式功能 *********************************************************/
void USART_LINBreakDetectLengthConfig(USART_TypeDef* USARTx, uint16_t USART_LINBreakDetectLength); // 设置 USART LIN 中断检测长度。
void USART_LINCmd(USART_TypeDef* USARTx, FunctionalState NewState); // 启用或禁用 USART 的 LIN 模式。
void USART_SendBreak(USART_TypeDef* USARTx);                        // 传输中断字符。

/* 半双工模式功能 **************************************************/
void USART_HalfDuplexCmd(USART_TypeDef* USARTx, FunctionalState NewState); // 启用或禁用 USART 的半双工通信。

/* 智能卡模式功能 ***************************************************/
void USART_SmartCardCmd(USART_TypeDef* USARTx, FunctionalState NewState);     // 启用或禁用 USART 的智能卡模式。
void USART_SmartCardNACKCmd(USART_TypeDef* USARTx, FunctionalState NewState); // 启用或禁用 NACK 传输。
void USART_SetGuardTime(USART_TypeDef* USARTx, uint8_t USART_GuardTime);      // 设置指定的 USART 保护时间。

/* IrDA 模式功能 ********************************************************/
void USART_IrDAConfig(USART_TypeDef* USARTx, uint16_t USART_IrDAMode);  // 配置 USART 的 IrDA 接口。
void USART_IrDACmd(USART_TypeDef* USARTx, FunctionalState NewState);    // 启用或禁用 USART 的 IrDA 接口。

/* DMA 传输管理功能 *****************************************/
void USART_DMACmd(USART_TypeDef* USARTx, uint16_t USART_DMAReq, FunctionalState NewState); // 启用或禁用 USART 的 DMA 接口。

/* 中断和标志管理功能 **********************************/
void USART_ITConfig(USART_TypeDef* USARTx, uint16_t USART_IT, FunctionalState NewState); // 启用或禁用指定的 USART 中断。
FlagStatus USART_GetFlagStatus(USART_TypeDef* USARTx, uint16_t USART_FLAG);              // 检查是否设置了指定的 USART 标志。
void USART_ClearFlag(USART_TypeDef* USARTx, uint16_t USART_FLAG);                        // 清除 USARTx 的挂起标志。
ITStatus USART_GetITStatus(USART_TypeDef* USARTx, uint16_t USART_IT);                    // 检查指定的 USART 中断是否发生。
void USART_ClearITPendingBit(USART_TypeDef* USARTx, uint16_t USART_IT);                  // 清除 USARTx 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_USART_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
