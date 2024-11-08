/**
  ******************************************************************************
  * 文件:    stm32f4xx_spi.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 SPI 固件库的所有函数原型.
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
#ifndef __STM32F4xx_SPI_H
#define __STM32F4xx_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup SPI
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  SPI初始化结构定义
  */
typedef struct {
    uint16_t SPI_Direction;           /*!< 指定 SPI 单向或双向数据模式。
                                          该参数可以是 @ref SPI_data_direction 的值 */

    uint16_t SPI_Mode;                /*!< 指定 SPI 操作模式。
                                          该参数可以是 @ref SPI_mode 的值 */

    uint16_t SPI_DataSize;            /*!< 指定 SPI 数据大小。
                                          该参数可以是 @ref SPI_data_size 的值 */

    uint16_t SPI_CPOL;                /*!< 指定串行时钟稳定状态。
                                          该参数可以是 @ref SPI_Clock_Polarity 的值 */

    uint16_t SPI_CPHA;                /*!< 指定位捕获的时钟有效边沿。
                                          该参数可以是 @ref SPI_Clock_Phase 的值 */

    uint16_t SPI_NSS;                 /*!< 指定 NSS 信号是由硬件(NSS 引脚)还是由软件使用 SSI 位管理。
                                          该参数可以是 @ref SPI_Slave_Select_management 的值 */

    uint16_t SPI_BaudRatePrescaler;   /*!< 指定将用于配置发送和接收 SCK 时钟的波特率预分频器值。
                                          该参数可以是 @ref SPI_BaudRate_Prescaler 的值
                                          @note 通信时钟源自主时钟。 从时钟不需要设置。 */

    uint16_t SPI_FirstBit;            /*!< 指定数据传输是从 MSB 位还是 LSB 位开始。
                                          该参数可以是 @ref SPI_MSB_LSB_transmission 的值 */

    uint16_t SPI_CRCPolynomial;       /*!< 指定用于 CRC 计算的多项式。 */
} SPI_InitTypeDef;

/**
  * 简介:  I2S Init 结构定义
  */
typedef struct {

    uint16_t I2S_Mode;         /*!< 指定 I2S 操作模式。
                                   该参数可以是 @ref I2S_Mode 的值 */

    uint16_t I2S_Standard;     /*!< 指定用于 I2S 通信的标准。
                                   该参数可以是 @ref I2S_Standard 的值 */

    uint16_t I2S_DataFormat;   /*!< 指定 I2S 通信的数据格式。
                                   该参数可以是 @ref I2S_Data_Format 的值 */

    uint16_t I2S_MCLKOutput;   /*!< 指定是否启用 I2S MCLK 输出。
                                   该参数可以是 @ref I2S_MCLK_Output 的值 */

    uint32_t I2S_AudioFreq;    /*!< 指定为 I2S 通信选择的频率。
                                   该参数可以是 @ref I2S_Audio_Frequency 的值 */

    uint16_t I2S_CPOL;         /*!< 指定 I2S 时钟的空闲状态。
                                   该参数可以是 @ref I2S_Clock_Polarity 的值 */
} I2S_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  */
#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3) || \
                                   ((PERIPH) == SPI4) || \
                                   ((PERIPH) == SPI5) || \
                                   ((PERIPH) == SPI6))

#define IS_SPI_ALL_PERIPH_EXT(PERIPH) (((PERIPH) == SPI1)    || \
                                       ((PERIPH) == SPI2)    || \
                                       ((PERIPH) == SPI3)    || \
                                       ((PERIPH) == SPI4)    || \
                                       ((PERIPH) == SPI5)    || \
                                       ((PERIPH) == SPI6)    || \
                                       ((PERIPH) == I2S2ext) || \
                                       ((PERIPH) == I2S3ext))

#define IS_SPI_23_PERIPH(PERIPH)  (((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3))

#define IS_SPI_23_PERIPH_EXT(PERIPH)  (((PERIPH) == SPI2)    || \
                                       ((PERIPH) == SPI3)    || \
                                       ((PERIPH) == I2S2ext) || \
                                       ((PERIPH) == I2S3ext))

#define IS_I2S_EXT_PERIPH(PERIPH)  (((PERIPH) == I2S2ext) || \
                                    ((PERIPH) == I2S3ext))


/** @defgroup SPI_data_direction
  */
#define SPI_Direction_2Lines_FullDuplex ((uint16_t)0x0000)
#define SPI_Direction_2Lines_RxOnly     ((uint16_t)0x0400)
#define SPI_Direction_1Line_Rx          ((uint16_t)0x8000)
#define SPI_Direction_1Line_Tx          ((uint16_t)0xC000)
#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                     ((MODE) == SPI_Direction_2Lines_RxOnly) || \
                                     ((MODE) == SPI_Direction_1Line_Rx) || \
                                     ((MODE) == SPI_Direction_1Line_Tx))

/** @defgroup SPI_mode
  */
#define SPI_Mode_Master                 ((uint16_t)0x0104)
#define SPI_Mode_Slave                  ((uint16_t)0x0000)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))

/** @defgroup SPI_data_size
  */
#define SPI_DataSize_16b                ((uint16_t)0x0800)
#define SPI_DataSize_8b                 ((uint16_t)0x0000)
#define IS_SPI_DATASIZE(DATASIZE) (((DATASIZE) == SPI_DataSize_16b) || \
                                   ((DATASIZE) == SPI_DataSize_8b))

/** @defgroup SPI_Clock_Polarity
  */
#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   ((uint16_t)0x0002)
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))

/** @defgroup SPI_Clock_Phase
  */
#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  ((uint16_t)0x0001)
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))

/** @defgroup SPI_Slave_Select_management
  */
#define SPI_NSS_Soft                    ((uint16_t)0x0200)
#define SPI_NSS_Hard                    ((uint16_t)0x0000)
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))

/** @defgroup SPI_BaudRate_Prescaler
  */
#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030)
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
        ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
        ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
        ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
        ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
        ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
        ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
        ((PRESCALER) == SPI_BaudRatePrescaler_256))

/** @defgroup SPI_MSB_LSB_transmission
  */
#define SPI_FirstBit_MSB                ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                ((uint16_t)0x0080)
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))

/** @defgroup SPI_I2S_Mode
  */
#define I2S_Mode_SlaveTx                ((uint16_t)0x0000)
#define I2S_Mode_SlaveRx                ((uint16_t)0x0100)
#define I2S_Mode_MasterTx               ((uint16_t)0x0200)
#define I2S_Mode_MasterRx               ((uint16_t)0x0300)
#define IS_I2S_MODE(MODE) (((MODE) == I2S_Mode_SlaveTx) || \
                           ((MODE) == I2S_Mode_SlaveRx) || \
                           ((MODE) == I2S_Mode_MasterTx)|| \
                           ((MODE) == I2S_Mode_MasterRx))


/** @defgroup SPI_I2S_Standard
  */
#define I2S_Standard_Phillips           ((uint16_t)0x0000)
#define I2S_Standard_MSB                ((uint16_t)0x0010)
#define I2S_Standard_LSB                ((uint16_t)0x0020)
#define I2S_Standard_PCMShort           ((uint16_t)0x0030)
#define I2S_Standard_PCMLong            ((uint16_t)0x00B0)
#define IS_I2S_STANDARD(STANDARD) (((STANDARD) == I2S_Standard_Phillips) || \
                                   ((STANDARD) == I2S_Standard_MSB) || \
                                   ((STANDARD) == I2S_Standard_LSB) || \
                                   ((STANDARD) == I2S_Standard_PCMShort) || \
                                   ((STANDARD) == I2S_Standard_PCMLong))

/** @defgroup SPI_I2S_Data_Format
  */
#define I2S_DataFormat_16b              ((uint16_t)0x0000)
#define I2S_DataFormat_16bextended      ((uint16_t)0x0001)
#define I2S_DataFormat_24b              ((uint16_t)0x0003)
#define I2S_DataFormat_32b              ((uint16_t)0x0005)
#define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == I2S_DataFormat_16b) || \
                                    ((FORMAT) == I2S_DataFormat_16bextended) || \
                                    ((FORMAT) == I2S_DataFormat_24b) || \
                                    ((FORMAT) == I2S_DataFormat_32b))

/** @defgroup SPI_I2S_MCLK_Output
  */
#define I2S_MCLKOutput_Enable           ((uint16_t)0x0200)
#define I2S_MCLKOutput_Disable          ((uint16_t)0x0000)
#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOutput_Enable) || \
                                    ((OUTPUT) == I2S_MCLKOutput_Disable))

/** @defgroup SPI_I2S_Audio_Frequency
  */
#define I2S_AudioFreq_192k               ((uint32_t)192000)
#define I2S_AudioFreq_96k                ((uint32_t)96000)
#define I2S_AudioFreq_48k                ((uint32_t)48000)
#define I2S_AudioFreq_44k                ((uint32_t)44100)
#define I2S_AudioFreq_32k                ((uint32_t)32000)
#define I2S_AudioFreq_22k                ((uint32_t)22050)
#define I2S_AudioFreq_16k                ((uint32_t)16000)
#define I2S_AudioFreq_11k                ((uint32_t)11025)
#define I2S_AudioFreq_8k                 ((uint32_t)8000)
#define I2S_AudioFreq_Default            ((uint32_t)2)

#define IS_I2S_AUDIO_FREQ(FREQ) ((((FREQ) >= I2S_AudioFreq_8k) && \
                                  ((FREQ) <= I2S_AudioFreq_192k)) || \
                                 ((FREQ) == I2S_AudioFreq_Default))

/** @defgroup SPI_I2S_Clock_Polarity
  */
#define I2S_CPOL_Low                    ((uint16_t)0x0000)
#define I2S_CPOL_High                   ((uint16_t)0x0008)
#define IS_I2S_CPOL(CPOL) (((CPOL) == I2S_CPOL_Low) || \
                           ((CPOL) == I2S_CPOL_High))

/** @defgroup SPI_I2S_DMA_transfer_requests
  */
#define SPI_I2S_DMAReq_Tx               ((uint16_t)0x0002)
#define SPI_I2S_DMAReq_Rx               ((uint16_t)0x0001)
#define IS_SPI_I2S_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFFFC) == 0x00) && ((DMAREQ) != 0x00))

/** @defgroup SPI_NSS_internal_software_management
  */
#define SPI_NSSInternalSoft_Set         ((uint16_t)0x0100)
#define SPI_NSSInternalSoft_Reset       ((uint16_t)0xFEFF)
#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))

/** @defgroup SPI_CRC_Transmit_Receive
  */
#define SPI_CRC_Tx                      ((uint8_t)0x00)
#define SPI_CRC_Rx                      ((uint8_t)0x01)
#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))

/** @defgroup SPI_direction_transmit_receive
  */
#define SPI_Direction_Rx                ((uint16_t)0xBFFF)
#define SPI_Direction_Tx                ((uint16_t)0x4000)
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
                                     ((DIRECTION) == SPI_Direction_Tx))

/** @defgroup SPI_I2S_interrupts_definition
  */
#define SPI_I2S_IT_TXE                  ((uint8_t)0x71)
#define SPI_I2S_IT_RXNE                 ((uint8_t)0x60)
#define SPI_I2S_IT_ERR                  ((uint8_t)0x50)
#define I2S_IT_UDR                      ((uint8_t)0x53)
#define SPI_I2S_IT_TIFRFE               ((uint8_t)0x58)

#define IS_SPI_I2S_CONFIG_IT(IT) (((IT) == SPI_I2S_IT_TXE) || \
                                  ((IT) == SPI_I2S_IT_RXNE) || \
                                  ((IT) == SPI_I2S_IT_ERR))

#define SPI_I2S_IT_OVR                  ((uint8_t)0x56)
#define SPI_IT_MODF                     ((uint8_t)0x55)
#define SPI_IT_CRCERR                   ((uint8_t)0x54)

#define IS_SPI_I2S_CLEAR_IT(IT) (((IT) == SPI_IT_CRCERR))

#define IS_SPI_I2S_GET_IT(IT) (((IT) == SPI_I2S_IT_RXNE)|| ((IT) == SPI_I2S_IT_TXE) || \
                               ((IT) == SPI_IT_CRCERR)  || ((IT) == SPI_IT_MODF) || \
                               ((IT) == SPI_I2S_IT_OVR) || ((IT) == I2S_IT_UDR) ||\
                               ((IT) == SPI_I2S_IT_TIFRFE))

/** @defgroup SPI_I2S_flags_definition
  */
#define SPI_I2S_FLAG_RXNE               ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TXE                ((uint16_t)0x0002)
#define I2S_FLAG_CHSIDE                 ((uint16_t)0x0004)
#define I2S_FLAG_UDR                    ((uint16_t)0x0008)
#define SPI_FLAG_CRCERR                 ((uint16_t)0x0010)
#define SPI_FLAG_MODF                   ((uint16_t)0x0020)
#define SPI_I2S_FLAG_OVR                ((uint16_t)0x0040)
#define SPI_I2S_FLAG_BSY                ((uint16_t)0x0080)
#define SPI_I2S_FLAG_TIFRFE             ((uint16_t)0x0100)

#define IS_SPI_I2S_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
#define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == I2S_FLAG_UDR) || ((FLAG) == I2S_FLAG_CHSIDE) || \
                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE)|| \
                                   ((FLAG) == SPI_I2S_FLAG_TIFRFE))

/** @defgroup SPI_CRC_polynomial
  */
#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)

/** @defgroup SPI_I2S_Legacy
  */
#define SPI_DMAReq_Tx                SPI_I2S_DMAReq_Tx
#define SPI_DMAReq_Rx                SPI_I2S_DMAReq_Rx
#define SPI_IT_TXE                   SPI_I2S_IT_TXE
#define SPI_IT_RXNE                  SPI_I2S_IT_RXNE
#define SPI_IT_ERR                   SPI_I2S_IT_ERR
#define SPI_IT_OVR                   SPI_I2S_IT_OVR
#define SPI_FLAG_RXNE                SPI_I2S_FLAG_RXNE
#define SPI_FLAG_TXE                 SPI_I2S_FLAG_TXE
#define SPI_FLAG_OVR                 SPI_I2S_FLAG_OVR
#define SPI_FLAG_BSY                 SPI_I2S_FLAG_BSY
#define SPI_DeInit                   SPI_I2S_DeInit
#define SPI_ITConfig                 SPI_I2S_ITConfig
#define SPI_DMACmd                   SPI_I2S_DMACmd
#define SPI_SendData                 SPI_I2S_SendData
#define SPI_ReceiveData              SPI_I2S_ReceiveData
#define SPI_GetFlagStatus            SPI_I2S_GetFlagStatus
#define SPI_ClearFlag                SPI_I2S_ClearFlag
#define SPI_GetITStatus              SPI_I2S_GetITStatus
#define SPI_ClearITPendingBit        SPI_I2S_ClearITPendingBit


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 SPI 配置设置为默认复位状态的函数 *****/
void SPI_I2S_DeInit(SPI_TypeDef* SPIx); // 将 SPIx 外设寄存器取消初始化为其缺省复位值。

/* 初始化和配置功能 *********************************/
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct); // 根据 SPI_InitStruct 中指定的参数初始化 SPIx 外设。
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct); // 根据 I2S_InitStruct 中指定的参数初始化 SPIx 外设。
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);              // 用其默认值填充每个 SPI_InitStruct 成员。
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);              // 用每个 I2S_InitStruct 成员的默认值填充每个成员。
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);         // 启用或禁用指定的 SPI 外设。
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);         // 启用或禁用指定的 SPI 外设(在 I2S 模式下)。
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize); // 配置所选 SPI 的数据大小。
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction); // 为指定的 SPI 选择双向模式下的数据传输方向。
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft); // 通过软件在内部配置所选 SPI 的 NSS 引脚。
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState); // 启用或禁用所选 SPI 的 SS 输出。
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState);   // 启用或禁用 SPIx/I2Sx DMA 接口。

void I2S_FullDuplexConfig(SPI_TypeDef* I2Sxext, I2S_InitTypeDef* I2S_InitStruct); // 根据 I2S_InitStruct 中的指定参数，使用扩展名 I2Sxext 为 I2Sx 外设配置全双工模式。

/* 数据传输功能 ***************************************************/
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data); // 通过 SPIx/I2Sx 外设传输数据。
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);         // 返回 SPIx/I2Sx 外设最近接收到的数据。

/* 硬件 CRC 计算功能 *****************************************/
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState); // 启用或禁用传输字节的 CRC 值计算。
void SPI_TransmitCRC(SPI_TypeDef* SPIx);                 // 传输 SPIx CRC 值。
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC); // 返回指定 SPI 的发送或接收 CRC 寄存器值。
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);        // 	返回指定 SPI 的 CRC 多项式寄存器值。

/* DMA 传输管理功能 *****************************************/
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState); // 启用或禁用 SPIx/I2Sx DMA 接口。

/* 中断和标志管理功能 **********************************/
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState); // 启用或禁用指定的 SPI/I2S 中断。
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);             // 检查是否设置了指定的 SPIx/I2Sx 标志。
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);    // 清除 SPIx CRC 错误 (CRCERR) 标志。
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT); // 检查指定的 SPIx/I2Sx 中断是否发生。
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT); // 清除 SPIx CRC 错误 (CRCERR) 中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_SPI_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
