/**
  **************************************************************************
  * @file     at32f435_437_dma.h
  * @brief    at32f435_437 dma header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_DMA_H
#define __AT32F435_437_DMA_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup DMA
  */

/** @defgroup DMA_Interrupts_definition
  * @brief dma interrupt
  */
#define DMA_FDT_INT                      ((uint32_t)0x00000002) /*!< dma full data transfer 中断 */
#define DMA_HDT_INT                      ((uint32_t)0x00000004) /*!< dma half data transfer 中断 */
#define DMA_DTERR_INT                    ((uint32_t)0x00000008) /*!< dma errorr 中断 */

/** @defgroup DMA_flags_definition
  * @brief edma flag
  */
#define DMA1_GL1_FLAG                    ((uint32_t)0x00000001) /*!< dma1 channel1 global flag */
#define DMA1_FDT1_FLAG                   ((uint32_t)0x00000002) /*!< dma1 channel1 full data transfer flag */
#define DMA1_HDT1_FLAG                   ((uint32_t)0x00000004) /*!< dma1 channel1 half data transfer flag */
#define DMA1_DTERR1_FLAG                 ((uint32_t)0x00000008) /*!< dma1 channel1 error flag */
#define DMA1_GL2_FLAG                    ((uint32_t)0x00000010) /*!< dma1 channel2 global flag */
#define DMA1_FDT2_FLAG                   ((uint32_t)0x00000020) /*!< dma1 channel2 full data transfer flag */
#define DMA1_HDT2_FLAG                   ((uint32_t)0x00000040) /*!< dma1 channel2 half data transfer flag */
#define DMA1_DTERR2_FLAG                 ((uint32_t)0x00000080) /*!< dma1 channel2 error flag */
#define DMA1_GL3_FLAG                    ((uint32_t)0x00000100) /*!< dma1 channel3 global flag */
#define DMA1_FDT3_FLAG                   ((uint32_t)0x00000200) /*!< dma1 channel3 full data transfer flag */
#define DMA1_HDT3_FLAG                   ((uint32_t)0x00000400) /*!< dma1 channel3 half data transfer flag */
#define DMA1_DTERR3_FLAG                 ((uint32_t)0x00000800) /*!< dma1 channel3 error flag */
#define DMA1_GL4_FLAG                    ((uint32_t)0x00001000) /*!< dma1 channel4 global flag */
#define DMA1_FDT4_FLAG                   ((uint32_t)0x00002000) /*!< dma1 channel4 full data transfer flag */
#define DMA1_HDT4_FLAG                   ((uint32_t)0x00004000) /*!< dma1 channel4 half data transfer flag */
#define DMA1_DTERR4_FLAG                 ((uint32_t)0x00008000) /*!< dma1 channel4 error flag */
#define DMA1_GL5_FLAG                    ((uint32_t)0x00010000) /*!< dma1 channel5 global flag */
#define DMA1_FDT5_FLAG                   ((uint32_t)0x00020000) /*!< dma1 channel5 full data transfer flag */
#define DMA1_HDT5_FLAG                   ((uint32_t)0x00040000) /*!< dma1 channel5 half data transfer flag */
#define DMA1_DTERR5_FLAG                 ((uint32_t)0x00080000) /*!< dma1 channel5 error flag */
#define DMA1_GL6_FLAG                    ((uint32_t)0x00100000) /*!< dma1 channel6 global flag */
#define DMA1_FDT6_FLAG                   ((uint32_t)0x00200000) /*!< dma1 channel6 full data transfer flag */
#define DMA1_HDT6_FLAG                   ((uint32_t)0x00400000) /*!< dma1 channel6 half data transfer flag */
#define DMA1_DTERR6_FLAG                 ((uint32_t)0x00800000) /*!< dma1 channel6 error flag */
#define DMA1_GL7_FLAG                    ((uint32_t)0x01000000) /*!< dma1 channel7 global flag */
#define DMA1_FDT7_FLAG                   ((uint32_t)0x02000000) /*!< dma1 channel7 full data transfer flag */
#define DMA1_HDT7_FLAG                   ((uint32_t)0x04000000) /*!< dma1 channel7 half data transfer flag */
#define DMA1_DTERR7_FLAG                 ((uint32_t)0x08000000) /*!< dma1 channel7 error flag */

#define DMA2_GL1_FLAG                    ((uint32_t)0x10000001) /*!< dma2 channel1 global flag */
#define DMA2_FDT1_FLAG                   ((uint32_t)0x10000002) /*!< dma2 channel1 full data transfer flag */
#define DMA2_HDT1_FLAG                   ((uint32_t)0x10000004) /*!< dma2 channel1 half data transfer flag */
#define DMA2_DTERR1_FLAG                 ((uint32_t)0x10000008) /*!< dma2 channel1 error flag */
#define DMA2_GL2_FLAG                    ((uint32_t)0x10000010) /*!< dma2 channel2 global flag */
#define DMA2_FDT2_FLAG                   ((uint32_t)0x10000020) /*!< dma2 channel2 full data transfer flag */
#define DMA2_HDT2_FLAG                   ((uint32_t)0x10000040) /*!< dma2 channel2 half data transfer flag */
#define DMA2_DTERR2_FLAG                 ((uint32_t)0x10000080) /*!< dma2 channel2 error flag */
#define DMA2_GL3_FLAG                    ((uint32_t)0x10000100) /*!< dma2 channel3 global flag */
#define DMA2_FDT3_FLAG                   ((uint32_t)0x10000200) /*!< dma2 channel3 full data transfer flag */
#define DMA2_HDT3_FLAG                   ((uint32_t)0x10000400) /*!< dma2 channel3 half data transfer flag */
#define DMA2_DTERR3_FLAG                 ((uint32_t)0x10000800) /*!< dma2 channel3 error flag */
#define DMA2_GL4_FLAG                    ((uint32_t)0x10001000) /*!< dma2 channel4 global flag */
#define DMA2_FDT4_FLAG                   ((uint32_t)0x10002000) /*!< dma2 channel4 full data transfer flag */
#define DMA2_HDT4_FLAG                   ((uint32_t)0x10004000) /*!< dma2 channel4 half data transfer flag */
#define DMA2_DTERR4_FLAG                 ((uint32_t)0x10008000) /*!< dma2 channel4 error flag */
#define DMA2_GL5_FLAG                    ((uint32_t)0x10010000) /*!< dma2 channel5 global flag */
#define DMA2_FDT5_FLAG                   ((uint32_t)0x10020000) /*!< dma2 channel5 full data transfer flag */
#define DMA2_HDT5_FLAG                   ((uint32_t)0x10040000) /*!< dma2 channel5 half data transfer flag */
#define DMA2_DTERR5_FLAG                 ((uint32_t)0x10080000) /*!< dma2 channel5 error flag */
#define DMA2_GL6_FLAG                    ((uint32_t)0x10100000) /*!< dma2 channel6 global flag */
#define DMA2_FDT6_FLAG                   ((uint32_t)0x10200000) /*!< dma2 channel6 full data transfer flag */
#define DMA2_HDT6_FLAG                   ((uint32_t)0x10400000) /*!< dma2 channel6 half data transfer flag */
#define DMA2_DTERR6_FLAG                 ((uint32_t)0x10800000) /*!< dma2 channel6 error flag */
#define DMA2_GL7_FLAG                    ((uint32_t)0x11000000) /*!< dma2 channel7 global flag */
#define DMA2_FDT7_FLAG                   ((uint32_t)0x12000000) /*!< dma2 channel7 full data transfer flag */
#define DMA2_HDT7_FLAG                   ((uint32_t)0x14000000) /*!< dma2 channel7 half data transfer flag */
#define DMA2_DTERR7_FLAG                 ((uint32_t)0x18000000) /*!< dma2 channel7 error flag */

/**
  * @brief dmamux flag
  */
#define DMAMUX_Sync_OV1_FLAG             ((uint32_t)0x00000001) /*!< dmamux channel1 synchronization overrun event flag */
#define DMAMUX_Sync_OV2_FLAG             ((uint32_t)0x00000002) /*!< dmamux channel2 synchronization overrun event flag */
#define DMAMUX_Sync_OV3_FLAG             ((uint32_t)0x00000004) /*!< dmamux channel3 synchronization overrun event flag */
#define DMAMUX_Sync_OV4_FLAG             ((uint32_t)0x00000008) /*!< dmamux channel4 synchronization overrun event flag */
#define DMAMUX_Sync_OV5_FLAG             ((uint32_t)0x00000010) /*!< dmamux channel5 synchronization overrun event flag */
#define DMAMUX_Sync_OV6_FLAG             ((uint32_t)0x00000020) /*!< dmamux channel6 synchronization overrun event flag */
#define DMAMUX_Sync_OV7_FLAG             ((uint32_t)0x00000040) /*!< dmamux channel7 synchronization overrun event flag */

#define DMAMUX_Gen_Trig_OV1_FLAG         ((uint32_t)0x00000001) /*!< dmamux generator channel1 overrun event flag */
#define DMAMUX_Gen_Trig_OV2_FLAG         ((uint32_t)0x00000002) /*!< dmamux generator channel2 overrun event flag */
#define DMAMUX_Gen_Trig_OV3_FLAG         ((uint32_t)0x00000004) /*!< dmamux generator channel3 overrun event flag */
#define DMAMUX_Gen_Trig_OV4_FLAG         ((uint32_t)0x00000008) /*!< dmamux generator channel4 overrun event flag */

/** @defgroup DMA_exported_Types
  */

/**
  * @brief dma direction type
  */
typedef enum {
    DMA_Dir_PERIPHERAL_To_MEMORY           = 0x0000, /*!< dma data transfer direction: peripheral to memory */
    DMA_Dir_Memory_To_PERIPHERAL           = 0x0010, /*!< dma data transfer direction: memory to peripheral */
    DMA_Dir_Memory_To_MEMORY               = 0x4000  /*!< dma data transfer direction: memory to memory */
} DMA_Dir_Type;

/**
  * @brief dma peripheral data size type
  */
typedef enum {
    DMA_Peripheral_Data_Width_BYTE         = 0x00, /*!< dma peripheral databus width 8bit */
    DMA_Peripheral_Data_Width_HALFWORD     = 0x01, /*!< dma peripheral databus width 16bit */
    DMA_Peripheral_Data_Width_WORD         = 0x02  /*!< dma peripheral databus width 32bit */
} DMA_peripheral_Data_size_Type;

/**
  * @brief dma memory data size type
  */
typedef enum {
    DMA_Memory_Data_Width_BYTE             = 0x00, /*!< dma memory databus width 8bit */
    DMA_Memory_Data_Width_HALFWORD         = 0x01, /*!< dma memory databus width 16bit */
    DMA_Memory_Data_Width_WORD             = 0x02  /*!< dma memory databus width 32bit */
} DMA_Memory_Data_size_Type;

/**
  * @brief dma priority level type
  */
typedef enum {
    DMA_Priority_LOW                       = 0x00, /*!< dma channel priority: low */
    DMA_Priority_MEDIUM                    = 0x01, /*!< dma channel priority: medium */
    DMA_Priority_HIGH                      = 0x02, /*!< dma channel priority: high */
    DMA_Priority_VERY_HIGH                 = 0x03  /*!< dma channel priority: very high */
} DMA_Priority_level_Type;

/**
  * @brief dmamux request type
  */
typedef enum {
    DMAMUX_DMAREQ_ID_REQ_G1                = 0x01, /*!< dmamux channel dma request inputs resources: generator channel1 */
    DMAMUX_DMAREQ_ID_REQ_G2                = 0x02, /*!< dmamux channel dma request inputs resources: generator channel2 */
    DMAMUX_DMAREQ_ID_REQ_G3                = 0x03, /*!< dmamux channel dma request inputs resources: generator channel3 */
    DMAMUX_DMAREQ_ID_REQ_G4                = 0x04, /*!< dmamux channel dma request inputs resources: generator channel4 */
    DMAMUX_DMAREQ_ID_ADC1                  = 0x05, /*!< dmamux channel dma request inputs resources: adc1 */
    DMAMUX_DMAREQ_ID_ADC2                  = 0x24, /*!< dmamux channel dma request inputs resources: adc2 */
    DMAMUX_DMAREQ_ID_ADC3                  = 0x25, /*!< dmamux channel dma request inputs resources: adc3 */
    DMAMUX_DMAREQ_ID_DAC1                  = 0x06, /*!< dmamux channel dma request inputs resources: dac1 */
    DMAMUX_DMAREQ_ID_DAC2                  = 0x29, /*!< dmamux channel dma request inputs resources: dac2 */
    DMAMUX_DMAREQ_ID_TMR6_OVERFLOW         = 0x08, /*!< dmamux channel dma request inputs resources: timer6 overflow */
    DMAMUX_DMAREQ_ID_TMR7_OVERFLOW         = 0x09, /*!< dmamux channel dma request inputs resources: timer7 overflow */
    DMAMUX_DMAREQ_ID_SPI1_RX               = 0x0A, /*!< dmamux channel dma request inputs resources: spi1 rx */
    DMAMUX_DMAREQ_ID_SPI1_TX               = 0x0B, /*!< dmamux channel dma request inputs resources: spi1 tx */
    DMAMUX_DMAREQ_ID_SPI2_RX               = 0x0C, /*!< dmamux channel dma request inputs resources: spi2 rx */
    DMAMUX_DMAREQ_ID_SPI2_TX               = 0x0D, /*!< dmamux channel dma request inputs resources: spi2 tx */
    DMAMUX_DMAREQ_ID_SPI3_RX               = 0x0E, /*!< dmamux channel dma request inputs resources: spi3 rx */
    DMAMUX_DMAREQ_ID_SPI3_TX               = 0x0F, /*!< dmamux channel dma request inputs resources: spi3 tx */
    DMAMUX_DMAREQ_ID_SPI4_RX               = 0x6A, /*!< dmamux channel dma request inputs resources: spi4 rx */
    DMAMUX_DMAREQ_ID_SPI4_TX               = 0x6B, /*!< dmamux channel dma request inputs resources: spi4 tx */
    DMAMUX_DMAREQ_ID_I2S2_Ext_RX           = 0x6E, /*!< dmamux channel dma request inputs resources: i2s2_Ext_rx */
    DMAMUX_DMAREQ_ID_I2S2_Ext_TX           = 0x6F, /*!< dmamux channel dma request inputs resources: i2s2_Ext_tx */
    DMAMUX_DMAREQ_ID_I2S3_Ext_RX           = 0x70, /*!< dmamux channel dma request inputs resources: i2s3_Ext_rx */
    DMAMUX_DMAREQ_ID_I2S3_Ext_TX           = 0x71, /*!< dmamux channel dma request inputs resources: i2s3_Ext_tx */
    DMAMUX_DMAREQ_ID_I2C1_RX               = 0x10, /*!< dmamux channel dma request inputs resources: i2c1_rx */
    DMAMUX_DMAREQ_ID_I2C1_TX               = 0x11, /*!< dmamux channel dma request inputs resources: i2c1_tx */
    DMAMUX_DMAREQ_ID_I2C2_RX               = 0x12, /*!< dmamux channel dma request inputs resources: i2c2_rx */
    DMAMUX_DMAREQ_ID_I2C2_TX               = 0x13, /*!< dmamux channel dma request inputs resources: i2c2_tx */
    DMAMUX_DMAREQ_ID_I2C3_RX               = 0x14, /*!< dmamux channel dma request inputs resources: i2c3_rx */
    DMAMUX_DMAREQ_ID_I2C3_TX               = 0x15, /*!< dmamux channel dma request inputs resources: i2c3_tx */
    DMAMUX_DMAREQ_ID_USART1_RX             = 0x18, /*!< dmamux channel dma request inputs resources: usart1_rx */
    DMAMUX_DMAREQ_ID_USART1_TX             = 0x19, /*!< dmamux channel dma request inputs resources: usart1_tx */
    DMAMUX_DMAREQ_ID_USART2_RX             = 0x1A, /*!< dmamux channel dma request inputs resources: usart2_rx */
    DMAMUX_DMAREQ_ID_USART2_TX             = 0x1B, /*!< dmamux channel dma request inputs resources: usart2_tx */
    DMAMUX_DMAREQ_ID_USART3_RX             = 0x1C, /*!< dmamux channel dma request inputs resources: usart3_rx */
    DMAMUX_DMAREQ_ID_USART3_TX             = 0x1D, /*!< dmamux channel dma request inputs resources: usart3_tx */
    DMAMUX_DMAREQ_ID_UART4_RX              = 0x1E, /*!< dmamux channel dma request inputs resources: uart4_rx */
    DMAMUX_DMAREQ_ID_UART4_TX              = 0x1F, /*!< dmamux channel dma request inputs resources: uart4_tx */
    DMAMUX_DMAREQ_ID_UART5_RX              = 0x20, /*!< dmamux channel dma request inputs resources: uart5_rx */
    DMAMUX_DMAREQ_ID_UART5_TX              = 0x21, /*!< dmamux channel dma request inputs resources: uart5_tx */
    DMAMUX_DMAREQ_ID_USART6_RX             = 0x72, /*!< dmamux channel dma request inputs resources: usart6_rx */
    DMAMUX_DMAREQ_ID_USART6_TX             = 0x73, /*!< dmamux channel dma request inputs resources: usart6_tx */
    DMAMUX_DMAREQ_ID_UART7_RX              = 0x74, /*!< dmamux channel dma request inputs resources: uart7_rx */
    DMAMUX_DMAREQ_ID_UART7_TX              = 0x75, /*!< dmamux channel dma request inputs resources: uart7_tx */
    DMAMUX_DMAREQ_ID_UART8_RX              = 0x76, /*!< dmamux channel dma request inputs resources: uart8_rx */
    DMAMUX_DMAREQ_ID_UART8_TX              = 0x77, /*!< dmamux channel dma request inputs resources: uart8_tx */
    DMAMUX_DMAREQ_ID_SDIO1                 = 0x27, /*!< dmamux channel dma request inputs resources: sdio1 */
    DMAMUX_DMAREQ_ID_SDIO2                 = 0x67, /*!< dmamux channel dma request inputs resources: sdio2 */
    DMAMUX_DMAREQ_ID_QSPI1                 = 0x28, /*!< dmamux channel dma request inputs resources: qspi1 */
    DMAMUX_DMAREQ_ID_QSPI2                 = 0x68, /*!< dmamux channel dma request inputs resources: qspi2 */
    DMAMUX_DMAREQ_ID_TMR1_CH1              = 0x2A, /*!< dmamux channel dma request inputs resources: timer1 ch1 */
    DMAMUX_DMAREQ_ID_TMR1_CH2              = 0x2B, /*!< dmamux channel dma request inputs resources: timer1 ch2 */
    DMAMUX_DMAREQ_ID_TMR1_CH3              = 0x2C, /*!< dmamux channel dma request inputs resources: timer1 ch3 */
    DMAMUX_DMAREQ_ID_TMR1_CH4              = 0x2D, /*!< dmamux channel dma request inputs resources: timer1 ch4 */
    DMAMUX_DMAREQ_ID_TMR1_OVERFLOW         = 0x2E, /*!< dmamux channel dma request inputs resources: timer1 overflow */
    DMAMUX_DMAREQ_ID_TMR1_TRIG             = 0x2F, /*!< dmamux channel dma request inputs resources: timer1 trigger */
    DMAMUX_DMAREQ_ID_TMR1_HALL             = 0x30, /*!< dmamux channel dma request inputs resources: timer1 hall */
    DMAMUX_DMAREQ_ID_TMR8_CH1              = 0x31, /*!< dmamux channel dma request inputs resources: timer8 ch1 */
    DMAMUX_DMAREQ_ID_TMR8_CH2              = 0x32, /*!< dmamux channel dma request inputs resources: timer8 ch2 */
    DMAMUX_DMAREQ_ID_TMR8_CH3              = 0x33, /*!< dmamux channel dma request inputs resources: timer8 ch3 */
    DMAMUX_DMAREQ_ID_TMR8_CH4              = 0x34, /*!< dmamux channel dma request inputs resources: timer8 ch4 */
    DMAMUX_DMAREQ_ID_TMR8_OVERFLOW         = 0x35, /*!< dmamux channel dma request inputs resources: timer8 overflow */
    DMAMUX_DMAREQ_ID_TMR8_TRIG             = 0x36, /*!< dmamux channel dma request inputs resources: timer8 trigger */
    DMAMUX_DMAREQ_ID_TMR8_HALL             = 0x37, /*!< dmamux channel dma request inputs resources: timer8 hall */
    DMAMUX_DMAREQ_ID_TMR2_CH1              = 0x38, /*!< dmamux channel dma request inputs resources: timer2 ch1 */
    DMAMUX_DMAREQ_ID_TMR2_CH2              = 0x39, /*!< dmamux channel dma request inputs resources: timer2 ch2 */
    DMAMUX_DMAREQ_ID_TMR2_CH3              = 0x3A, /*!< dmamux channel dma request inputs resources: timer2 ch3 */
    DMAMUX_DMAREQ_ID_TMR2_CH4              = 0x3B, /*!< dmamux channel dma request inputs resources: timer2 ch4 */
    DMAMUX_DMAREQ_ID_TMR2_OVERFLOW         = 0x3C, /*!< dmamux channel dma request inputs resources: timer2 overflow */
    DMAMUX_DMAREQ_ID_TMR2_TRIG             = 0x7E, /*!< dmamux channel dma request inputs resources: timer2 trigger */
    DMAMUX_DMAREQ_ID_TMR3_CH1              = 0x3D, /*!< dmamux channel dma request inputs resources: timer3 ch1 */
    DMAMUX_DMAREQ_ID_TMR3_CH2              = 0x3E, /*!< dmamux channel dma request inputs resources: timer3 ch2 */
    DMAMUX_DMAREQ_ID_TMR3_CH3              = 0x3F, /*!< dmamux channel dma request inputs resources: timer3 ch3 */
    DMAMUX_DMAREQ_ID_TMR3_CH4              = 0x40, /*!< dmamux channel dma request inputs resources: timer3 ch4 */
    DMAMUX_DMAREQ_ID_TMR3_OVERFLOW         = 0x41, /*!< dmamux channel dma request inputs resources: timer3 overflow */
    DMAMUX_DMAREQ_ID_TMR3_TRIG             = 0x42, /*!< dmamux channel dma request inputs resources: timer3 trigger */
    DMAMUX_DMAREQ_ID_TMR4_CH1              = 0x43, /*!< dmamux channel dma request inputs resources: timer4 ch1 */
    DMAMUX_DMAREQ_ID_TMR4_CH2              = 0x44, /*!< dmamux channel dma request inputs resources: timer4 ch2 */
    DMAMUX_DMAREQ_ID_TMR4_CH3              = 0x45, /*!< dmamux channel dma request inputs resources: timer4 ch3 */
    DMAMUX_DMAREQ_ID_TMR4_CH4              = 0x46, /*!< dmamux channel dma request inputs resources: timer4 ch4 */
    DMAMUX_DMAREQ_ID_TMR4_OVERFLOW         = 0x47, /*!< dmamux channel dma request inputs resources: timer4 overflow */
    DMAMUX_DMAREQ_ID_TMR4_TRIG             = 0x7F, /*!< dmamux channel dma request inputs resources: timer4 trigger */
    DMAMUX_DMAREQ_ID_TMR5_CH1              = 0x48, /*!< dmamux channel dma request inputs resources: timer5 ch1 */
    DMAMUX_DMAREQ_ID_TMR5_CH2              = 0x49, /*!< dmamux channel dma request inputs resources: timer5 ch2 */
    DMAMUX_DMAREQ_ID_TMR5_CH3              = 0x4A, /*!< dmamux channel dma request inputs resources: timer5 ch3 */
    DMAMUX_DMAREQ_ID_TMR5_CH4              = 0x4B, /*!< dmamux channel dma request inputs resources: timer5 ch4 */
    DMAMUX_DMAREQ_ID_TMR5_OVERFLOW         = 0x4C, /*!< dmamux channel dma request inputs resources: timer5 overflow */
    DMAMUX_DMAREQ_ID_TMR5_TRIG             = 0x4D, /*!< dmamux channel dma request inputs resources: timer5 trigger */
    DMAMUX_DMAREQ_ID_TMR20_CH1             = 0x56, /*!< dmamux channel dma request inputs resources: timer20 ch1 */
    DMAMUX_DMAREQ_ID_TMR20_CH2             = 0x57, /*!< dmamux channel dma request inputs resources: timer20 ch2 */
    DMAMUX_DMAREQ_ID_TMR20_CH3             = 0x58, /*!< dmamux channel dma request inputs resources: timer20 ch3 */
    DMAMUX_DMAREQ_ID_TMR20_CH4             = 0x59, /*!< dmamux channel dma request inputs resources: timer20 ch4 */
    DMAMUX_DMAREQ_ID_TMR20_OVERFLOW        = 0x5A, /*!< dmamux channel dma request inputs resources: timer20 overflow */
    DMAMUX_DMAREQ_ID_TMR20_TRIG            = 0x5D, /*!< dmamux channel dma request inputs resources: timer20 trigger */
    DMAMUX_DMAREQ_ID_TMR20_HALL            = 0x5E, /*!< dmamux channel dma request inputs resources: timer20 hall */
    DMAMUX_DMAREQ_ID_DVP                   = 0x69  /*!< dmamux channel dma request inputs resources: dvp */
} DMAMUX_Requst_ID_sel_Type;

/**
  * @brief dmamux sync id type
  */
typedef enum {
    DMAMUX_Sync_ID_EXINT0                  = 0x00, /*!< dmamux channel synchronization inputs resources: exint line0 */
    DMAMUX_Sync_ID_EXINT1                  = 0x01, /*!< dmamux channel synchronization inputs resources: exint line1 */
    DMAMUX_Sync_ID_EXINT2                  = 0x02, /*!< dmamux channel synchronization inputs resources: exint line2 */
    DMAMUX_Sync_ID_EXINT3                  = 0x03, /*!< dmamux channel synchronization inputs resources: exint line3 */
    DMAMUX_Sync_ID_EXINT4                  = 0x04, /*!< dmamux channel synchronization inputs resources: exint line4 */
    DMAMUX_Sync_ID_EXINT5                  = 0x05, /*!< dmamux channel synchronization inputs resources: exint line5 */
    DMAMUX_Sync_ID_EXINT6                  = 0x06, /*!< dmamux channel synchronization inputs resources: exint line6 */
    DMAMUX_Sync_ID_EXINT7                  = 0x07, /*!< dmamux channel synchronization inputs resources: exint line7 */
    DMAMUX_Sync_ID_EXINT8                  = 0x08, /*!< dmamux channel synchronization inputs resources: exint line8 */
    DMAMUX_Sync_ID_EXINT9                  = 0x09, /*!< dmamux channel synchronization inputs resources: exint line9 */
    DMAMUX_Sync_ID_EXINT10                 = 0x0A, /*!< dmamux channel synchronization inputs resources: exint line10 */
    DMAMUX_Sync_ID_EXINT11                 = 0x0B, /*!< dmamux channel synchronization inputs resources: exint line11 */
    DMAMUX_Sync_ID_EXINT12                 = 0x0C, /*!< dmamux channel synchronization inputs resources: exint line12 */
    DMAMUX_Sync_ID_EXINT13                 = 0x0D, /*!< dmamux channel synchronization inputs resources: exint line13 */
    DMAMUX_Sync_ID_EXINT14                 = 0x0E, /*!< dmamux channel synchronization inputs resources: exint line14 */
    DMAMUX_Sync_ID_EXINT15                 = 0x0F, /*!< dmamux channel synchronization inputs resources: exint line15 */
    DMAMUX_Sync_ID_DMAMUX_CH1_EVT          = 0x10, /*!< dmamux channel synchronization inputs resources: dmamux channel1 event */
    DMAMUX_Sync_ID_DMAMUX_CH2_EVT          = 0x11, /*!< dmamux channel synchronization inputs resources: dmamux channel2 event */
    DMAMUX_Sync_ID_DMAMUX_CH3_EVT          = 0x12, /*!< dmamux channel synchronization inputs resources: dmamux channel3 event */
    DMAMUX_Sync_ID_DMAMUX_CH4_EVT          = 0x13, /*!< dmamux channel synchronization inputs resources: dmamux channel4 event */
    DMAMUX_Sync_ID_DMAMUX_CH5_EVT          = 0x14, /*!< dmamux channel synchronization inputs resources: dmamux channel5 event */
    DMAMUX_Sync_ID_DMAMUX_CH6_EVT          = 0x15, /*!< dmamux channel synchronization inputs resources: dmamux channel6 event */
    DMAMUX_Sync_ID_DMAMUX_CH7_EVT          = 0x16  /*!< dmamux channel synchronization inputs resources: dmamux channel7 event */
} DMAMUX_Sync_ID_sel_Type;

/**
  * @brief dmamux sync polarity type
  */
typedef enum {
    DMAMUX_Sync_Polarity_Disable           = 0x00, /*!< dmamux channel synchronization inputs resources polarity default value */
    DMAMUX_Sync_Polarity_RISING            = 0x01, /*!< dmamux channel synchronization inputs resources polarity: rising */
    DMAMUX_Sync_Polarity_FALLING           = 0x02, /*!< dmamux channel synchronization inputs resources polarity: falling */
    DMAMUX_Sync_Polarity_RISING_FALLING    = 0x03  /*!< dmamux channel synchronization inputs resources polarity: rising_falling */
} DMAMUX_Sync_pol_Type;

/**
  * @brief dmamux generator id type
  */
typedef enum {
    DMAMUX_Gen_ID_EXINT0                   = 0x00, /*!< dmamux generator channel inputs resources: exint line0 */
    DMAMUX_Gen_ID_EXINT1                   = 0x01, /*!< dmamux generator channel inputs resources: exint line1 */
    DMAMUX_Gen_ID_EXINT2                   = 0x02, /*!< dmamux generator channel inputs resources: exint line2 */
    DMAMUX_Gen_ID_EXINT3                   = 0x03, /*!< dmamux generator channel inputs resources: exint line3 */
    DMAMUX_Gen_ID_EXINT4                   = 0x04, /*!< dmamux generator channel inputs resources: exint line4 */
    DMAMUX_Gen_ID_EXINT5                   = 0x05, /*!< dmamux generator channel inputs resources: exint line5 */
    DMAMUX_Gen_ID_EXINT6                   = 0x06, /*!< dmamux generator channel inputs resources: exint line6 */
    DMAMUX_Gen_ID_EXINT7                   = 0x07, /*!< dmamux generator channel inputs resources: exint line7 */
    DMAMUX_Gen_ID_EXINT8                   = 0x08, /*!< dmamux generator channel inputs resources: exint line8 */
    DMAMUX_Gen_ID_EXINT9                   = 0x09, /*!< dmamux generator channel inputs resources: exint line9 */
    DMAMUX_Gen_ID_EXINT10                  = 0x0A, /*!< dmamux generator channel inputs resources: exint line10 */
    DMAMUX_Gen_ID_EXINT11                  = 0x0B, /*!< dmamux generator channel inputs resources: exint line11 */
    DMAMUX_Gen_ID_EXINT12                  = 0x0C, /*!< dmamux generator channel inputs resources: exint line12 */
    DMAMUX_Gen_ID_EXINT13                  = 0x0D, /*!< dmamux generator channel inputs resources: exint line13 */
    DMAMUX_Gen_ID_EXINT14                  = 0x0E, /*!< dmamux generator channel inputs resources: exint line14 */
    DMAMUX_Gen_ID_EXINT15                  = 0x0F, /*!< dmamux generator channel inputs resources: exint line15 */
    DMAMUX_Gen_ID_DMAMUX_CH1_EVT           = 0x10, /*!< dmamux generator channel inputs resources: dmamux channel1 event */
    DMAMUX_Gen_ID_DMAMUX_CH2_EVT           = 0x11, /*!< dmamux generator channel inputs resources: dmamux channel2 event */
    DMAMUX_Gen_ID_DMAMUX_CH3_EVT           = 0x12, /*!< dmamux generator channel inputs resources: dmamux channel3 event */
    DMAMUX_Gen_ID_DMAMUX_CH4_EVT           = 0x13, /*!< dmamux generator channel inputs resources: dmamux channel4 event */
    DMAMUX_Gen_ID_DMAMUX_CH5_EVT           = 0x14, /*!< dmamux generator channel inputs resources: dmamux channel5 event */
    DMAMUX_Gen_ID_DMAMUX_CH6_EVT           = 0x15, /*!< dmamux generator channel inputs resources: dmamux channel6 event */
    DMAMUX_Gen_ID_DMAMUX_CH7_EVT           = 0x16  /*!< dmamux generator channel inputs resources: dmamux channel7 event */
} DMAMUX_Gen_ID_sel_Type;

/**
  * @brief dmamux generator polarity type
  */
typedef enum {
    DMAMUX_Gen_Polarity_Disable            = 0x00, /*!< dmamux generator channel inputs resources polarity default value */
    DMAMUX_Gen_Polarity_RISING             = 0x01, /*!< dmamux generator channel inputs resources polarity: rising */
    DMAMUX_Gen_Polarity_FALLING            = 0x02, /*!< dmamux generator channel inputs resources polarity: falling */
    DMAMUX_Gen_Polarity_RISING_FALLING     = 0x03  /*!< dmamux generator channel inputs resources polarity: rising_falling */
} DMAMUX_Gen_pol_Type;

/**
  * @brief dma init type
  */
typedef struct {
    uint32_t                               Peripheral_Base_Addr;    /*!< base addrress for peripheral */
    uint32_t                               Memory_Base_Addr;        /*!< base addrress for memory */
    DMA_Dir_Type                           direction;               /*!< dma transmit direction, peripheral as source or as destnation  */
    uint16_t                               Buffer_Size;             /*!< counter to transfer (0~0xFFFF) */
    confirm_state                          Peripheral_Inc_Enable;   /*!< periphera address increment after one transmit */
    confirm_state                          Memory_Inc_Enable;       /*!< memory address increment after one transmit */
    DMA_peripheral_Data_size_Type          Peripheral_Data_Width;   /*!< peripheral data width for transmit */
    DMA_Memory_Data_size_Type              Memory_Data_Width;       /*!< memory data width for transmit */
    confirm_state                          Loop_Mode_Enable;        /*!< when loop mode enable, buffer size will reload if count to 0*/
    DMA_Priority_level_Type                priority;                /*!< dma priority can choose from very high,high,dedium or low */
} DMA_Init_Type;

/**
  * @brief dmamux sync init type
  */
typedef struct {
    DMAMUX_Sync_ID_sel_Type                Sync_Signal_Sel;     /*!< dma dmamux synchronization input select */
    uint32_t                               Sync_Polarity;       /*!< dma dmamux synchronization polarity */
    uint32_t                               Sync_Request_Number; /*!< dma dmamux number of dma requests before an output event is generated  */
    confirm_state                          Sync_Event_Enable;   /*!< dma dmamux event generation disabled */
    confirm_state                          Sync_Enable;         /*!< dma dmamux synchronization enable */
} DMAMUX_Sync_Init_Type;

/**
  * @brief dmamux generator init type
  */
typedef struct {
    DMAMUX_Gen_ID_sel_Type                 Gen_Signal_Sel;     /*!< dma dmamux generator dma request trigger input select */
    DMAMUX_Gen_pol_Type                    Gen_Polarity;       /*!< dma dmamux generator trigger polarity */
    uint32_t                               Gen_Request_Number; /*!< dma dmamux the number of dma requests to be generated after a trigger event  */
    confirm_state                          Gen_Enable;         /*!< dma dmamux generator enable */
} DMAMUX_Gen_Init_Type;

/**
  * @brief type define dma1 register
  */
typedef struct {
    /**
      * @brief dma sts register, offset:0x00
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t gf1                  : 1; /* [0] */
            __IO uint32_t fdtf1                : 1; /* [1] */
            __IO uint32_t hdtf1                : 1; /* [2] */
            __IO uint32_t dterrf1              : 1; /* [3] */
            __IO uint32_t gf2                  : 1; /* [4] */
            __IO uint32_t fdtf2                : 1; /* [5] */
            __IO uint32_t hdtf2                : 1; /* [6] */
            __IO uint32_t dterrf2              : 1; /* [7] */
            __IO uint32_t gf3                  : 1; /* [8] */
            __IO uint32_t fdtf3                : 1; /* [9] */
            __IO uint32_t hdtf3                : 1; /* [10] */
            __IO uint32_t dterrf3              : 1; /* [11] */
            __IO uint32_t gf4                  : 1; /* [12] */
            __IO uint32_t fdtf4                : 1; /* [13] */
            __IO uint32_t hdtf4                : 1; /* [14] */
            __IO uint32_t dterrf4              : 1; /* [15] */
            __IO uint32_t gf5                  : 1; /* [16] */
            __IO uint32_t fdtf5                : 1; /* [17] */
            __IO uint32_t hdtf5                : 1; /* [18] */
            __IO uint32_t dterrf5              : 1; /* [19] */
            __IO uint32_t gf6                  : 1; /* [20] */
            __IO uint32_t fdtf6                : 1; /* [21] */
            __IO uint32_t hdtf6                : 1; /* [22] */
            __IO uint32_t dterrf6              : 1; /* [23] */
            __IO uint32_t gf7                  : 1; /* [24] */
            __IO uint32_t fdtf7                : 1; /* [25] */
            __IO uint32_t hdtf7                : 1; /* [26] */
            __IO uint32_t dterrf7              : 1; /* [27] */
            __IO uint32_t reserved1            : 4; /* [31:28] */
        } sts_bit;
    };

    /**
      * @brief dma clr register, offset:0x04
      */
    union {
        __IO uint32_t clr;
        struct {
            __IO uint32_t gfc1                 : 1; /* [0] */
            __IO uint32_t fdtfc1               : 1; /* [1] */
            __IO uint32_t hdtfc1               : 1; /* [2] */
            __IO uint32_t dterrfc1             : 1; /* [3] */
            __IO uint32_t gfc2                 : 1; /* [4] */
            __IO uint32_t fdtfc2               : 1; /* [5] */
            __IO uint32_t hdtfc2               : 1; /* [6] */
            __IO uint32_t dterrfc2             : 1; /* [7] */
            __IO uint32_t gfc3                 : 1; /* [8] */
            __IO uint32_t fdtfc3               : 1; /* [9] */
            __IO uint32_t hdtfc3               : 1; /* [10] */
            __IO uint32_t dterrfc3             : 1; /* [11] */
            __IO uint32_t gfc4                 : 1; /* [12] */
            __IO uint32_t fdtfc4               : 1; /* [13] */
            __IO uint32_t hdtfc4               : 1; /* [14] */
            __IO uint32_t dterrfc4             : 1; /* [15] */
            __IO uint32_t gfc5                 : 1; /* [16] */
            __IO uint32_t fdtfc5               : 1; /* [17] */
            __IO uint32_t hdtfc5               : 1; /* [18] */
            __IO uint32_t dterrfc5             : 1; /* [19] */
            __IO uint32_t gfc6                 : 1; /* [20] */
            __IO uint32_t fdtfc6               : 1; /* [21] */
            __IO uint32_t hdtfc6               : 1; /* [22] */
            __IO uint32_t dterrfc6             : 1; /* [23] */
            __IO uint32_t gfc7                 : 1; /* [24] */
            __IO uint32_t fdtfc7               : 1; /* [25] */
            __IO uint32_t hdtfc7               : 1; /* [26] */
            __IO uint32_t dterrfc7             : 1; /* [27] */
            __IO uint32_t reserved1            : 4; /* [31:28] */
        } clr_bit;
    };

    /**
      * @brief reserved, offset:0x08~0xFC
      */
    __IO uint32_t reserved1[62];

    /**
      * @brief dmamux sel register, offset:0x100
      */
    union {
        __IO uint32_t muxsel;
        struct {
            __IO uint32_t tblsel               : 1; /* [0] */
            __IO uint32_t reserved1            : 31;/* [31:1] */
        } muxsel_bit;
    };

    /**
      * @brief reserved, offset:0x104~0x12C
      */
    __IO uint32_t reserved2[11];

    /**
      * @brief dmamux syncsts register, offset:0x130
      */
    union {
        __IO uint32_t muxsyncsts;
        struct {
            __IO uint32_t syncovf              : 7; /* [6:0] */
            __IO uint32_t reserved1            : 25;/* [31:7] */
        } muxsyncsts_bit;
    };

    /**
      * @brief dmamux syncclr register, offset:0x134
      */
    union {
        __IO uint32_t muxsyncclr;
        struct {
            __IO uint32_t syncovfc             : 7; /* [6:0] */
            __IO uint32_t reserved1            : 25;/* [31:7] */
        } muxsyncclr_bit;
    };

    /**
      * @brief dmamux request generator status register, offset:0x138
      */
    union {
        __IO uint32_t muxgsts;
        struct {
            __IO uint32_t trgovf               : 4; /* [3:0] */
            __IO uint32_t reserved1            : 28;/* [31:4] */
        } muxgsts_bit;
    };
    /**
      * @brief dmamux request generator status clear register, offset:0x13C
      */
    union {
        __IO uint32_t muxgclr;
        struct {
            __IO uint32_t trgovfc              : 4; /* [3:0] */
            __IO uint32_t reserved1            : 28;/* [31:4] */
        } muxgclr_bit;
    };
} DMA_Type;

/**
  * @brief type define dma channel register all
  */
typedef struct {
    /**
      * @brief dma ch ctrl0 register, offset:0x08+20*(x-1) x=1...7
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t chen                 : 1; /* [0] */
            __IO uint32_t fdtien               : 1; /* [1] */
            __IO uint32_t hdtien               : 1; /* [2] */
            __IO uint32_t dterrien             : 1; /* [3] */
            __IO uint32_t dtd                  : 1; /* [4] */
            __IO uint32_t lm                   : 1; /* [5] */
            __IO uint32_t pincm                : 1; /* [6] */
            __IO uint32_t mincm                : 1; /* [7] */
            __IO uint32_t pwidth               : 2; /* [9:8] */
            __IO uint32_t mwidth               : 2; /* [11:10] */
            __IO uint32_t chpl                 : 2; /* [13:12] */
            __IO uint32_t m2m                  : 1; /* [14] */
            __IO uint32_t reserved1            : 17;/* [31:15] */
        } ctrl_bit;
    };

    /**
      * @brief dma tcnt register, offset:0x0C+20*(x-1) x=1...7
      */
    union {
        __IO uint32_t dtcnt;
        struct {
            __IO uint32_t cnt                  : 16;/* [15:0] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } dtcnt_bit;
    };

    /**
      * @brief dma cpba register, offset:0x10+20*(x-1) x=1...7
      */
    union {
        __IO uint32_t paddr;
        struct {
            __IO uint32_t paddr                : 32;/* [31:0] */
        } paddr_bit;
    };

    /**
      * @brief dma cmba register, offset:0x14+20*(x-1) x=1...7
      */
    union {
        __IO uint32_t maddr;
        struct {
            __IO uint32_t maddr                : 32;/* [31:0] */
        } maddr_bit;
    };
} DMA_Channel_Type;

/**
  * @brief type define dmamux muxsctrl register
  */
typedef struct {
    /**
      * @brief dma muxsctrl register
      */
    union {
        __IO uint32_t muxctrl;
        struct {
            __IO uint32_t reqsel               : 7; /* [6:0] */
            __IO uint32_t reserved1            : 1; /* [7] */
            __IO uint32_t syncovien            : 1; /* [8] */
            __IO uint32_t evtgen               : 1; /* [9] */
            __IO uint32_t reserved2            : 6; /* [15:10] */
            __IO uint32_t syncen               : 1; /* [16] */
            __IO uint32_t syncpol              : 2; /* [18:17] */
            __IO uint32_t reqcnt               : 5; /* [23:19] */
            __IO uint32_t syncsel              : 5; /* [28:24] */
            __IO uint32_t reserved3            : 3; /* [31:29] */
        } muxctrl_bit;
    };
} DMAMUX_Channel_Type;

/**
  * @brief type define dmamux request generator register all
  */
typedef struct {
    /**
      * @brief dmamux request generator register, offset:0x120+4*(x-1) x=1...4
      */
    union {
        __IO uint32_t gctrl;
        struct {
            __IO uint32_t sigsel               : 5; /* [4:0] */
            __IO uint32_t reserved1            : 3; /* [7:5] */
            __IO uint32_t trgovien             : 1; /* [8] */
            __IO uint32_t reserved2            : 7; /* [15:9] */
            __IO uint32_t gen                  : 1; /* [16] */
            __IO uint32_t gpol                 : 2; /* [18:17] */
            __IO uint32_t greqcnt              : 5; /* [23:19] */
            __IO uint32_t reserved3            : 8; /* [31:24] */
        } gctrl_bit;
    };
} DMAMUX_Generator_Type;
#define DMA1                             ((DMA_Type *) DMA1_BASE)
#define DMA1_ChanneL1                    ((DMA_Channel_Type *) DMA1_ChanneL1_BASE)
#define DMA1_ChanneL2                    ((DMA_Channel_Type *) DMA1_ChanneL2_BASE)
#define DMA1_ChanneL3                    ((DMA_Channel_Type *) DMA1_ChanneL3_BASE)
#define DMA1_ChanneL4                    ((DMA_Channel_Type *) DMA1_ChanneL4_BASE)
#define DMA1_ChanneL5                    ((DMA_Channel_Type *) DMA1_ChanneL5_BASE)
#define DMA1_ChanneL6                    ((DMA_Channel_Type *) DMA1_ChanneL6_BASE)
#define DMA1_ChanneL7                    ((DMA_Channel_Type *) DMA1_ChanneL7_BASE)

#define DMA1MUX_ChanneL1                 ((DMAMUX_Channel_Type *) DMA1MUX_ChanneL1_BASE)
#define DMA1MUX_ChanneL2                 ((DMAMUX_Channel_Type *) DMA1MUX_ChanneL2_BASE)
#define DMA1MUX_ChanneL3                 ((DMAMUX_Channel_Type *) DMA1MUX_ChanneL3_BASE)
#define DMA1MUX_ChanneL4                 ((DMAMUX_Channel_Type *) DMA1MUX_ChanneL4_BASE)
#define DMA1MUX_ChanneL5                 ((DMAMUX_Channel_Type *) DMA1MUX_ChanneL5_BASE)
#define DMA1MUX_ChanneL6                 ((DMAMUX_Channel_Type *) DMA1MUX_ChanneL6_BASE)
#define DMA1MUX_ChanneL7                 ((DMAMUX_Channel_Type *) DMA1MUX_ChanneL7_BASE)

#define DMA1MUX_GENERATOR1               ((DMAMUX_Generator_Type *) DMA1MUX_GENERATOR1_BASE)
#define DMA1MUX_GENERATOR2               ((DMAMUX_Generator_Type *) DMA1MUX_GENERATOR2_BASE)
#define DMA1MUX_GENERATOR3               ((DMAMUX_Generator_Type *) DMA1MUX_GENERATOR3_BASE)
#define DMA1MUX_GENERATOR4               ((DMAMUX_Generator_Type *) DMA1MUX_GENERATOR4_BASE)

#define DMA2                             ((DMA_Type *) DMA2_BASE)
#define DMA2_ChanneL1                    ((DMA_Channel_Type *) DMA2_ChanneL1_BASE)
#define DMA2_ChanneL2                    ((DMA_Channel_Type *) DMA2_ChanneL2_BASE)
#define DMA2_ChanneL3                    ((DMA_Channel_Type *) DMA2_ChanneL3_BASE)
#define DMA2_ChanneL4                    ((DMA_Channel_Type *) DMA2_ChanneL4_BASE)
#define DMA2_ChanneL5                    ((DMA_Channel_Type *) DMA2_ChanneL5_BASE)
#define DMA2_ChanneL6                    ((DMA_Channel_Type *) DMA2_ChanneL6_BASE)
#define DMA2_ChanneL7                    ((DMA_Channel_Type *) DMA2_ChanneL7_BASE)

#define DMA2MUX_ChanneL1                 ((DMAMUX_Channel_Type *) DMA2MUX_ChanneL1_BASE)
#define DMA2MUX_ChanneL2                 ((DMAMUX_Channel_Type *) DMA2MUX_ChanneL2_BASE)
#define DMA2MUX_ChanneL3                 ((DMAMUX_Channel_Type *) DMA2MUX_ChanneL3_BASE)
#define DMA2MUX_ChanneL4                 ((DMAMUX_Channel_Type *) DMA2MUX_ChanneL4_BASE)
#define DMA2MUX_ChanneL5                 ((DMAMUX_Channel_Type *) DMA2MUX_ChanneL5_BASE)
#define DMA2MUX_ChanneL6                 ((DMAMUX_Channel_Type *) DMA2MUX_ChanneL6_BASE)
#define DMA2MUX_ChanneL7                 ((DMAMUX_Channel_Type *) DMA2MUX_ChanneL7_BASE)

#define DMA2MUX_GENERATOR1               ((DMAMUX_Generator_Type *) DMA2MUX_GENERATOR1_BASE)
#define DMA2MUX_GENERATOR2               ((DMAMUX_Generator_Type *) DMA2MUX_GENERATOR2_BASE)
#define DMA2MUX_GENERATOR3               ((DMAMUX_Generator_Type *) DMA2MUX_GENERATOR3_BASE)
#define DMA2MUX_GENERATOR4               ((DMAMUX_Generator_Type *) DMA2MUX_GENERATOR4_BASE)

/** @defgroup DMA_exported_functions
  */

/* dma controller function */
void DMA_Reset(DMA_Channel_Type *dmax_Channely);
void DMA_Data_Number_Set(DMA_Channel_Type *dmax_Channely, uint16_t data_Number);
uint16_t DMA_Data_Number_Get(DMA_Channel_Type *dmax_Channely);
void DMA_Interrupt_Enable(DMA_Channel_Type *dmax_Channely, uint32_t DMA_int, confirm_state new_state);
void DMA_Channel_Enable(DMA_Channel_Type *dmax_Channely, confirm_state new_state);
flag_status DMA_Flag_Get(uint32_t dmax_flag);
void DMA_Flag_Clear(uint32_t dmax_flag);
void DMA_Default_Para_Init(DMA_Init_Type *DMA_Init_struct);
void DMA_Init(DMA_Channel_Type *dmax_Channely, DMA_Init_Type *DMA_Init_struct);

/* dma requst multiplexer function */
void DMA_Flexible_Config(DMA_Type* DMA_x, DMAMUX_Channel_Type *DMAMUX_Channelx, DMAMUX_Requst_ID_sel_Type DMAMUX_req_sel);
void DMAMUX_Enable(DMA_Type *DMA_x, confirm_state new_state);
void DMAMUX_Init(DMAMUX_Channel_Type *DMAMUX_Channelx, DMAMUX_Requst_ID_sel_Type DMAMUX_req_sel);
void DMAMUX_Sync_Default_Para_Init(DMAMUX_Sync_Init_Type *DMAMUX_Sync_Init_struct);
void DMAMUX_Sync_Config(DMAMUX_Channel_Type *DMAMUX_Channelx, DMAMUX_Sync_Init_Type *DMAMUX_Sync_Init_struct);
void DMAMUX_Generator_Default_Para_Init(DMAMUX_Gen_Init_Type *DMAMUX_Gen_Init_struct);
void DMAMUX_Generator_Config(DMAMUX_Generator_Type *DMAMUX_Gen_x, DMAMUX_Gen_Init_Type *DMAMUX_Gen_Init_struct);
void DMAMUX_Sync_Interrupt_Enable(DMAMUX_Channel_Type *DMAMUX_Channelx, confirm_state new_state);
void DMAMUX_Generator_Interrupt_Enable(DMAMUX_Generator_Type *DMAMUX_Gen_x, confirm_state new_state);
flag_status DMAMUX_Sync_Flag_Get(DMA_Type *DMA_x, uint32_t flag);
void DMAMUX_Sync_Flag_Clear(DMA_Type *DMA_x, uint32_t flag);
flag_status DMAMUX_Generator_Flag_Get(DMA_Type *DMA_x, uint32_t flag);
void DMAMUX_Generator_Flag_Clear(DMA_Type *DMA_x, uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif
