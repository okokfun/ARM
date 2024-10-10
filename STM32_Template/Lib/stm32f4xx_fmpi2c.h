/**
  ******************************************************************************
  * 文件:    stm32f4xx_fmpi2c.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 I2C Fast Mode Plus 固件库的所有功能原型.
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
#ifndef __STM32F4xx_FMPI2C_H
#define __STM32F4xx_FMPI2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup FMPI2C
  */
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  FMPI2C 初始化结构定义
  */
typedef struct {
    uint32_t FMPI2C_Timing;              /*!< 指定 FMPI2C_TIMINGR_register 值。
                                          此参数参考参考手册中的 FMPI2C 初始化部分计算得出*/

    uint32_t FMPI2C_AnalogFilter;        /*!< 启用或禁用模拟噪声滤波器。
                                          该参数可以是 @ref FMPI2C_Analog_Filter 的值 */

    uint32_t FMPI2C_DigitalFilter;       /*!< 配置数字噪声滤波器。
                                          此参数可以是 0x00 和 0x0F 之间的数字 */

    uint32_t FMPI2C_Mode;                /*!< 指定 FMPI2C 模式。
                                          该参数可以是 @ref FMPI2C_mode 的值 */

    uint32_t FMPI2C_OwnAddress1;         /*!< 指定设备自己的地址 1。
                                          该参数可以是 7 位或 10 位地址 */

    uint32_t FMPI2C_Ack;                 /*!< 启用或禁用确认。
                                          该参数可以是 @ref FMPI2C_acknowledgement 的值 */

    uint32_t FMPI2C_AcknowledgedAddress; /*!< 指定是否确认 7 位或 10 位地址。
                                          该参数可以是 @ref FMPI2C_acknowledged_address 的值 */
} FMPI2C_InitTypeDef;

/* Exported constants --------------------------------------------------------*/


/** @defgroup FMPI2C_Exported_Constants
  */
#define IS_FMPI2C_ALL_PERIPH(PERIPH)       ((PERIPH) == FMPI2C1)

/** @defgroup FMPI2C_Analog_Filter
  */
#define FMPI2C_AnalogFilter_Enable         ((uint32_t)0x00000000)
#define FMPI2C_AnalogFilter_Disable        FMPI2C_CR1_ANFOFF

#define IS_FMPI2C_ANALOG_FILTER(FILTER)    (((FILTER) == FMPI2C_AnalogFilter_Enable) || \
        ((FILTER) == FMPI2C_AnalogFilter_Disable))

/** @defgroup FMPI2C_Digital_Filter
  */
#define IS_FMPI2C_DIGITAL_FILTER(FILTER)   ((FILTER) <= 0x0000000F)

/** @defgroup FMPI2C_mode
  */
#define FMPI2C_Mode_FMPI2C                ((uint32_t)0x00000000)
#define FMPI2C_Mode_SMBusDevice            FMPI2C_CR1_SMBDEN
#define FMPI2C_Mode_SMBusHost              FMPI2C_CR1_SMBHEN

#define IS_FMPI2C_MODE(MODE)               (((MODE) == FMPI2C_Mode_FMPI2C) || \
        ((MODE) == FMPI2C_Mode_SMBusDevice) || \
        ((MODE) == FMPI2C_Mode_SMBusHost))

/** @defgroup FMPI2C_acknowledgement
  */
#define FMPI2C_Ack_Enable                  ((uint32_t)0x00000000)
#define FMPI2C_Ack_Disable                 FMPI2C_CR2_NACK

#define IS_FMPI2C_ACK(ACK)                 (((ACK) == FMPI2C_Ack_Enable) || \
        ((ACK) == FMPI2C_Ack_Disable))

/** @defgroup FMPI2C_acknowledged_address
  */
#define FMPI2C_AcknowledgedAddress_7bit    ((uint32_t)0x00000000)
#define FMPI2C_AcknowledgedAddress_10bit   FMPI2C_OAR1_OA1MODE

#define IS_FMPI2C_ACKNOWLEDGE_ADDRESS(ADDRESS) (((ADDRESS) == FMPI2C_AcknowledgedAddress_7bit) || \
        ((ADDRESS) == FMPI2C_AcknowledgedAddress_10bit))

/** @defgroup FMPI2C_own_address1
  */
#define IS_FMPI2C_OWN_ADDRESS1(ADDRESS1)   ((ADDRESS1) <= (uint32_t)0x000003FF)

/** @defgroup FMPI2C_transfer_direction
  */
#define FMPI2C_Direction_Transmitter       ((uint16_t)0x0000)
#define FMPI2C_Direction_Receiver          ((uint16_t)0x0400)

#define IS_FMPI2C_DIRECTION(DIRECTION)     (((DIRECTION) == FMPI2C_Direction_Transmitter) || \
        ((DIRECTION) == FMPI2C_Direction_Receiver))

/** @defgroup FMPI2C_DMA_transfer_requests
  */
#define FMPI2C_DMAReq_Tx                   FMPI2C_CR1_TXDMAEN
#define FMPI2C_DMAReq_Rx                   FMPI2C_CR1_RXDMAEN

#define IS_FMPI2C_DMA_REQ(REQ)             ((((REQ) & (uint32_t)0xFFFF3FFF) == 0x00) && ((REQ) != 0x00))

/** @defgroup FMPI2C_slave_address
  */
#define IS_FMPI2C_SLAVE_ADDRESS(ADDRESS)   ((ADDRESS) <= (uint16_t)0x03FF)


/** @defgroup FMPI2C_own_address2
  */
#define IS_FMPI2C_OWN_ADDRESS2(ADDRESS2)   ((ADDRESS2) <= (uint16_t)0x00FF)


/** @defgroup FMPI2C_own_address2_mask
  */
#define FMPI2C_OA2_NoMask                  ((uint8_t)0x00)
#define FMPI2C_OA2_Mask01                  ((uint8_t)0x01)
#define FMPI2C_OA2_Mask02                  ((uint8_t)0x02)
#define FMPI2C_OA2_Mask03                  ((uint8_t)0x03)
#define FMPI2C_OA2_Mask04                  ((uint8_t)0x04)
#define FMPI2C_OA2_Mask05                  ((uint8_t)0x05)
#define FMPI2C_OA2_Mask06                  ((uint8_t)0x06)
#define FMPI2C_OA2_Mask07                  ((uint8_t)0x07)

#define IS_FMPI2C_OWN_ADDRESS2_MASK(MASK)  (((MASK) == FMPI2C_OA2_NoMask) || \
        ((MASK) == FMPI2C_OA2_Mask01) || \
        ((MASK) == FMPI2C_OA2_Mask02) || \
        ((MASK) == FMPI2C_OA2_Mask03) || \
        ((MASK) == FMPI2C_OA2_Mask04) || \
        ((MASK) == FMPI2C_OA2_Mask05) || \
        ((MASK) == FMPI2C_OA2_Mask06) || \
        ((MASK) == FMPI2C_OA2_Mask07))


/** @defgroup FMPI2C_timeout
  */
#define IS_FMPI2C_TIMEOUT(TIMEOUT)   ((TIMEOUT) <= (uint16_t)0x0FFF)


/** @defgroup FMPI2C_registers
  */
#define FMPI2C_Register_CR1                ((uint8_t)0x00)
#define FMPI2C_Register_CR2                ((uint8_t)0x04)
#define FMPI2C_Register_OAR1               ((uint8_t)0x08)
#define FMPI2C_Register_OAR2               ((uint8_t)0x0C)
#define FMPI2C_Register_TIMINGR            ((uint8_t)0x10)
#define FMPI2C_Register_TIMEOUTR           ((uint8_t)0x14)
#define FMPI2C_Register_ISR                ((uint8_t)0x18)
#define FMPI2C_Register_ICR                ((uint8_t)0x1C)
#define FMPI2C_Register_PECR               ((uint8_t)0x20)
#define FMPI2C_Register_RXDR               ((uint8_t)0x24)
#define FMPI2C_Register_TXDR               ((uint8_t)0x28)

#define IS_FMPI2C_REGISTER(REGISTER)       (((REGISTER) == FMPI2C_Register_CR1) || \
        ((REGISTER) == FMPI2C_Register_CR2) || \
        ((REGISTER) == FMPI2C_Register_OAR1) || \
        ((REGISTER) == FMPI2C_Register_OAR2) || \
        ((REGISTER) == FMPI2C_Register_TIMINGR) || \
        ((REGISTER) == FMPI2C_Register_TIMEOUTR) || \
        ((REGISTER) == FMPI2C_Register_ISR) || \
        ((REGISTER) == FMPI2C_Register_ICR) || \
        ((REGISTER) == FMPI2C_Register_PECR) || \
        ((REGISTER) == FMPI2C_Register_RXDR) || \
        ((REGISTER) == FMPI2C_Register_TXDR))

/** @defgroup FMPI2C_interrupts_definition
  */
#define FMPI2C_IT_ERRI                     FMPI2C_CR1_ERRIE
#define FMPI2C_IT_TCI                      FMPI2C_CR1_TCIE
#define FMPI2C_IT_STOPI                    FMPI2C_CR1_STOPIE
#define FMPI2C_IT_NACKI                    FMPI2C_CR1_NACKIE
#define FMPI2C_IT_ADDRI                    FMPI2C_CR1_ADDRIE
#define FMPI2C_IT_RXI                      FMPI2C_CR1_RXIE
#define FMPI2C_IT_TXI                      FMPI2C_CR1_TXIE

#define IS_FMPI2C_CONFIG_IT(IT)            ((((IT) & (uint32_t)0xFFFFFF01) == 0x00) && ((IT) != 0x00))


/** @defgroup FMPI2C_flags_definition
  */
#define  FMPI2C_FLAG_TXE                   FMPI2C_ISR_TXE
#define  FMPI2C_FLAG_TXIS                  FMPI2C_ISR_TXIS
#define  FMPI2C_FLAG_RXNE                  FMPI2C_ISR_RXNE
#define  FMPI2C_FLAG_ADDR                  FMPI2C_ISR_ADDR
#define  FMPI2C_FLAG_NACKF                 FMPI2C_ISR_NACKF
#define  FMPI2C_FLAG_STOPF                 FMPI2C_ISR_STOPF
#define  FMPI2C_FLAG_TC                    FMPI2C_ISR_TC
#define  FMPI2C_FLAG_TCR                   FMPI2C_ISR_TCR
#define  FMPI2C_FLAG_BERR                  FMPI2C_ISR_BERR
#define  FMPI2C_FLAG_ARLO                  FMPI2C_ISR_ARLO
#define  FMPI2C_FLAG_OVR                   FMPI2C_ISR_OVR
#define  FMPI2C_FLAG_PECERR                FMPI2C_ISR_PECERR
#define  FMPI2C_FLAG_TIMEOUT               FMPI2C_ISR_TIMEOUT
#define  FMPI2C_FLAG_ALERT                 FMPI2C_ISR_ALERT
#define  FMPI2C_FLAG_BUSY                  FMPI2C_ISR_BUSY

#define IS_FMPI2C_CLEAR_FLAG(FLAG)         ((((FLAG) & (uint32_t)0xFFFF4000) == 0x00) && ((FLAG) != 0x00))

#define IS_FMPI2C_GET_FLAG(FLAG)           (((FLAG) == FMPI2C_FLAG_TXE) || ((FLAG) == FMPI2C_FLAG_TXIS) || \
        ((FLAG) == FMPI2C_FLAG_RXNE) || ((FLAG) == FMPI2C_FLAG_ADDR) || \
        ((FLAG) == FMPI2C_FLAG_NACKF) || ((FLAG) == FMPI2C_FLAG_STOPF) || \
        ((FLAG) == FMPI2C_FLAG_TC) || ((FLAG) == FMPI2C_FLAG_TCR) || \
        ((FLAG) == FMPI2C_FLAG_BERR) || ((FLAG) == FMPI2C_FLAG_ARLO) || \
        ((FLAG) == FMPI2C_FLAG_OVR) || ((FLAG) == FMPI2C_FLAG_PECERR) || \
        ((FLAG) == FMPI2C_FLAG_TIMEOUT) || ((FLAG) == FMPI2C_FLAG_ALERT) || \
        ((FLAG) == FMPI2C_FLAG_BUSY))



/** @defgroup FMPI2C_interrupts_definition
  */
#define  FMPI2C_IT_TXIS                    FMPI2C_ISR_TXIS
#define  FMPI2C_IT_RXNE                    FMPI2C_ISR_RXNE
#define  FMPI2C_IT_ADDR                    FMPI2C_ISR_ADDR
#define  FMPI2C_IT_NACKF                   FMPI2C_ISR_NACKF
#define  FMPI2C_IT_STOPF                   FMPI2C_ISR_STOPF
#define  FMPI2C_IT_TC                      FMPI2C_ISR_TC
#define  FMPI2C_IT_TCR                     FMPI2C_ISR_TCR
#define  FMPI2C_IT_BERR                    FMPI2C_ISR_BERR
#define  FMPI2C_IT_ARLO                    FMPI2C_ISR_ARLO
#define  FMPI2C_IT_OVR                     FMPI2C_ISR_OVR
#define  FMPI2C_IT_PECERR                  FMPI2C_ISR_PECERR
#define  FMPI2C_IT_TIMEOUT                 FMPI2C_ISR_TIMEOUT
#define  FMPI2C_IT_ALERT                   FMPI2C_ISR_ALERT

#define IS_FMPI2C_CLEAR_IT(IT)             ((((IT) & (uint32_t)0xFFFFC001) == 0x00) && ((IT) != 0x00))

#define IS_FMPI2C_GET_IT(IT)               (((IT) == FMPI2C_IT_TXIS) || ((IT) == FMPI2C_IT_RXNE) || \
        ((IT) == FMPI2C_IT_ADDR) || ((IT) == FMPI2C_IT_NACKF) || \
        ((IT) == FMPI2C_IT_STOPF) || ((IT) == FMPI2C_IT_TC) || \
        ((IT) == FMPI2C_IT_TCR) || ((IT) == FMPI2C_IT_BERR) || \
        ((IT) == FMPI2C_IT_ARLO) || ((IT) == FMPI2C_IT_OVR) || \
        ((IT) == FMPI2C_IT_PECERR) || ((IT) == FMPI2C_IT_TIMEOUT) || \
        ((IT) == FMPI2C_IT_ALERT))


/** @defgroup FMPI2C_ReloadEndMode_definition
  */
#define  FMPI2C_Reload_Mode                FMPI2C_CR2_RELOAD
#define  FMPI2C_AutoEnd_Mode               FMPI2C_CR2_AUTOEND
#define  FMPI2C_SoftEnd_Mode               ((uint32_t)0x00000000)


#define IS_RELOAD_END_MODE(MODE)        (((MODE) == FMPI2C_Reload_Mode) || \
        ((MODE) == FMPI2C_AutoEnd_Mode) || \
        ((MODE) == FMPI2C_SoftEnd_Mode))



/** @defgroup FMPI2C_StartStopMode_definition
  */
#define  FMPI2C_No_StartStop                 ((uint32_t)0x00000000)
#define  FMPI2C_Generate_Stop                FMPI2C_CR2_STOP
#define  FMPI2C_Generate_Start_Read          (uint32_t)(FMPI2C_CR2_START | FMPI2C_CR2_RD_WRN)
#define  FMPI2C_Generate_Start_Write         FMPI2C_CR2_START


#define IS_START_STOP_MODE(MODE)        (((MODE) == FMPI2C_Generate_Stop) || \
        ((MODE) == FMPI2C_Generate_Start_Read) || \
        ((MODE) == FMPI2C_Generate_Start_Write) || \
        ((MODE) == FMPI2C_No_StartStop))




/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


/* 初始化和配置功能 *********************************/
void FMPI2C_DeInit(FMPI2C_TypeDef* FMPI2Cx); // 将 FMPI2Cx 外设寄存器取消初始化为其默认复位值。
void FMPI2C_Init(FMPI2C_TypeDef* FMPI2Cx, FMPI2C_InitTypeDef* FMPI2C_InitStruct); // 根据 FMPI2C_InitStruct 中指定的参数初始化 FMPI2Cx 外设。
void FMPI2C_StructInit(FMPI2C_InitTypeDef* FMPI2C_InitStruct); // 用默认值填充每个 FMPI2C_InitStruct 成员。
void FMPI2C_Cmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用指定的 FMPI2C 外设。
void FMPI2C_SoftwareResetCmd(FMPI2C_TypeDef* FMPI2Cx); // 启用或禁用指定的 FMPI2C 软件复位。
void FMPI2C_ITConfig(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_IT, FunctionalState NewState); // 启用或禁用指定的 FMPI2C 中断。
void FMPI2C_StretchClockCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C 时钟延长。
void FMPI2C_DualAddressCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C 自己的地址 2。
void FMPI2C_OwnAddress2Config(FMPI2C_TypeDef* FMPI2Cx, uint16_t Address, uint8_t Mask); // 配置 FMPI2C 从机自己的地址 2 和掩码。
void FMPI2C_GeneralCallCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C 广播呼叫模式。
void FMPI2C_SlaveByteControlCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C 从字节控制。
void FMPI2C_SlaveAddressConfig(FMPI2C_TypeDef* FMPI2Cx, uint16_t Address); // 配置启动生成后要发送的从地址。
void FMPI2C_10BitAddressingModeCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用主设备的 FMPI2C 10 位寻址模式。

/* 通讯处理功能 ******************************************/
void FMPI2C_AutoEndCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C 自动结束模式(传输 nbytes 数据时自动发送停止条件)。
void FMPI2C_ReloadCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C nbytes 重载模式。
void FMPI2C_NumberOfBytesConfig(FMPI2C_TypeDef* FMPI2Cx, uint8_t Number_Bytes); // 配置要发送/接收的字节数。
void FMPI2C_MasterRequestConfig(FMPI2C_TypeDef* FMPI2Cx, uint16_t FMPI2C_Direction); // 配置主站的传输请求类型。
void FMPI2C_GenerateSTART(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 生成 FMPI2Cx 通信启动条件。
void FMPI2C_GenerateSTOP(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 生成 FMPI2Cx 通信停止条件。
void FMPI2C_10BitAddressHeaderCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用具有读取方向的 FMPI2C 10 位仅标头模式。
void FMPI2C_AcknowledgeConfig(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 生成 FMPI2C 通信确认。
uint8_t FMPI2C_GetAddressMatched(FMPI2C_TypeDef* FMPI2Cx); // 返回 FMPI2C 从机匹配地址。
uint16_t FMPI2C_GetTransferDirection(FMPI2C_TypeDef* FMPI2Cx); // 返回 FMPI2C 从机接收到的请求。
void FMPI2C_TransferHandling(FMPI2C_TypeDef* FMPI2Cx, uint16_t Address, uint8_t Number_Bytes, uint32_t ReloadEndMode, uint32_t StartStopMode); // 在开始传输或传输期间(TC 或 TCR 标志置位)处理 FMPI2Cx 通信。

/*  SMBUS管理功能 ************************************************/
void FMPI2C_SMBusAlertCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C SMBus 警报。
void FMPI2C_ClockTimeoutCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C 时钟超时(SCL 超时检测)。
void FMPI2C_ExtendedClockTimeoutCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C 扩展时钟超时(SCL 累积超时检测)。
void FMPI2C_IdleClockTimeoutCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C 空闲时钟超时(总线空闲 SCL 和 SDA 高电平检测)。
void FMPI2C_TimeoutAConfig(FMPI2C_TypeDef* FMPI2Cx, uint16_t Timeout); // 配置 FMPI2C 总线超时 A(TIDLE = 0 时 SCL 超时或 TIDLE = 1 时总线空闲 SCL 和 SDA 高)。
void FMPI2C_TimeoutBConfig(FMPI2C_TypeDef* FMPI2Cx, uint16_t Timeout); // 配置 FMPI2C 总线超时 B(SCL 累积超时)。
void FMPI2C_CalculatePEC(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C PEC 计算。
void FMPI2C_PECRequestCmd(FMPI2C_TypeDef* FMPI2Cx, FunctionalState NewState); // 启用或禁用 FMPI2C PEC 发送/接收请求。
uint8_t FMPI2C_GetPEC(FMPI2C_TypeDef* FMPI2Cx); // 返回 FMPI2C PEC。

/* FMPI2C 寄存器管理功能 *****************************************/
uint32_t FMPI2C_ReadRegister(FMPI2C_TypeDef* FMPI2Cx, uint8_t FMPI2C_Register); // 读取指定的 FMPI2C 寄存器并返回其值。

/* 数据传输管理功能 ****************************************/
void FMPI2C_SendData(FMPI2C_TypeDef* FMPI2Cx, uint8_t Data); // 通过 FMPI2Cx 外设发送一个数据字节。
uint8_t FMPI2C_ReceiveData(FMPI2C_TypeDef* FMPI2Cx); // 返回 FMPI2Cx 外设最近接收的数据。

/* DMA 传输管理功能 *****************************************/
void FMPI2C_DMACmd(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_DMAReq, FunctionalState NewState); // 启用或禁用 FMPI2C DMA 接口。

/* 中断和标志管理功能 **********************************/
FlagStatus FMPI2C_GetFlagStatus(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_FLAG); // 检查是否设置了指定的 FMPI2C 标志。
void FMPI2C_ClearFlag(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_FLAG); // 清除 FMPI2Cx 的挂起标志。
ITStatus FMPI2C_GetITStatus(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_IT); // 检查是否发生了指定的 FMPI2C 中断。
void FMPI2C_ClearITPendingBit(FMPI2C_TypeDef* FMPI2Cx, uint32_t FMPI2C_IT); // 清除 FMPI2Cx 的中断挂起位。

#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx */


#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_FMPI2C_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
