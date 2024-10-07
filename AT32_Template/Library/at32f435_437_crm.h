/**
  **************************************************************************
  * @file     at32f435_437_crm.h
  * @brief    at32f435_437 crm header file
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

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_CRM_H
#define __AT32F435_437_CRM_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup CRM
  */
#define CRM_REG(value)                   PERIPH_REG(CRM_BASE, value)
#define CRM_REG_BIT(value)               PERIPH_REG_BIT(value)

/** @defgroup CRM_flags_definition
  * @brief crm flag
  */
#define CRM_HICK_Stable_FLAG             MAKE_VALUE(0x00, 1)  /*!< high speed internal clock stable flag */
#define CRM_Hext_Stable_FLAG             MAKE_VALUE(0x00, 17) /*!< high speed external crystal stable flag */
#define CRM_PLL_Stable_FLAG              MAKE_VALUE(0x00, 25) /*!< phase locking loop stable flag */
#define CRM_Lext_Stable_FLAG             MAKE_VALUE(0x70, 1)  /*!< low speed external crystal stable flag */
#define CRM_LICK_Stable_FLAG             MAKE_VALUE(0x74, 1)  /*!< low speed internal clock stable flag */
#define CRM_All_Reset_FLAG               MAKE_VALUE(0x74, 24) /*!< all reset flag */
#define CRM_NRST_Reset_FLAG              MAKE_VALUE(0x74, 26) /*!< nrst pin reset flag */
#define CRM_POR_Reset_FLAG               MAKE_VALUE(0x74, 27) /*!< power on reset flag */
#define CRM_SW_Reset_FLAG                MAKE_VALUE(0x74, 28) /*!< software reset flag */
#define CRM_WDT_Reset_FLAG               MAKE_VALUE(0x74, 29) /*!< watchdog timer reset flag */
#define CRM_WWDT_Reset_FLAG              MAKE_VALUE(0x74, 30) /*!< window watchdog timer reset flag */
#define CRM_LowPower_Reset_FLAG          MAKE_VALUE(0x74, 31) /*!< low-power reset flag */
#define CRM_LICK_ReadY_INT_FLAG          MAKE_VALUE(0x0C, 0)  /*!< low speed internal clock stable interrupt ready flag */
#define CRM_Lext_ReadY_INT_FLAG          MAKE_VALUE(0x0C, 1)  /*!< low speed external crystal stable interrupt ready flag */
#define CRM_HICK_ReadY_INT_FLAG          MAKE_VALUE(0x0C, 2)  /*!< high speed internal clock stable interrupt ready flag */
#define CRM_Hext_ReadY_INT_FLAG          MAKE_VALUE(0x0C, 3)  /*!< high speed external crystal stable interrupt ready flag */
#define CRM_PLL_ReadY_INT_FLAG           MAKE_VALUE(0x0C, 4)  /*!< phase locking loop stable interrupt ready flag */
#define CRM_Clock_Failure_INT_FLAG       MAKE_VALUE(0x0C, 7)  /*!< clock failure interrupt ready flag */

/** @defgroup CRM_Interrupts_definition
  * @brief crm interrupt
  */
#define CRM_LICK_Stable_INT              ((uint32_t)0x00000100) /*!< low speed internal clock stable 中断 */
#define CRM_Lext_Stable_INT              ((uint32_t)0x00000200) /*!< low speed external crystal stable 中断 */
#define CRM_HICK_Stable_INT              ((uint32_t)0x00000400) /*!< high speed internal clock stable 中断 */
#define CRM_Hext_Stable_INT              ((uint32_t)0x00000800) /*!< high speed external crystal stable 中断 */
#define CRM_PLL_Stable_INT               ((uint32_t)0x00001000) /*!< phase locking loop stable 中断 */
#define CRM_Clock_Failure_INT            ((uint32_t)0x00800000) /*!< clock failure 中断 */

/** @defgroup CRM_exported_Types
  */

/**
  * @brief crm periph clock
  */
typedef enum {
    #if defined (AT32F435xx)
    /* ahb periph1 */
    CRM_GPIOA_Periph_CLOCK                 = MAKE_VALUE(0x30, 0),  /*!< gpioa periph clock */
    CRM_GPIOB_Periph_CLOCK                 = MAKE_VALUE(0x30, 1),  /*!< gpiob periph clock */
    CRM_GPIOC_Periph_CLOCK                 = MAKE_VALUE(0x30, 2),  /*!< gpioc periph clock */
    CRM_GPIOD_Periph_CLOCK                 = MAKE_VALUE(0x30, 3),  /*!< gpiod periph clock */
    CRM_GPIOE_Periph_CLOCK                 = MAKE_VALUE(0x30, 4),  /*!< gpioe periph clock */
    CRM_GPIOF_Periph_CLOCK                 = MAKE_VALUE(0x30, 5),  /*!< gpiof periph clock */
    CRM_GPIOG_Periph_CLOCK                 = MAKE_VALUE(0x30, 6),  /*!< gpiog periph clock */
    CRM_GPIOH_Periph_CLOCK                 = MAKE_VALUE(0x30, 7),  /*!< gpioh periph clock */
    CRM_CRC_Periph_CLOCK                   = MAKE_VALUE(0x30, 12), /*!< crc periph clock */
    CRM_EDMA_Periph_CLOCK                  = MAKE_VALUE(0x30, 21), /*!< edma periph clock */
    CRM_DMA1_Periph_CLOCK                  = MAKE_VALUE(0x30, 22), /*!< dma1 periph clock */
    CRM_DMA2_Periph_CLOCK                  = MAKE_VALUE(0x30, 24), /*!< dma2 periph clock */
    CRM_OTGFS2_Periph_CLOCK                = MAKE_VALUE(0x30, 29), /*!< otgfs2 periph clock */
    /* ahb periph2 */
    CRM_DVP_Periph_CLOCK                   = MAKE_VALUE(0x34, 0),  /*!< dvp periph clock */
    CRM_OTGFS1_Periph_CLOCK                = MAKE_VALUE(0x34, 7),  /*!< otgfs1 periph clock */
    CRM_SDIO1_Periph_CLOCK                 = MAKE_VALUE(0x34, 15), /*!< sdio1 periph clock */
    /* ahb periph3 */
    CRM_XMC_Periph_CLOCK                   = MAKE_VALUE(0x38, 0),  /*!< xmc periph clock */
    CRM_QSPI1_Periph_CLOCK                 = MAKE_VALUE(0x38, 1),  /*!< qspi1 periph clock */
    CRM_QSPI2_Periph_CLOCK                 = MAKE_VALUE(0x38, 14), /*!< qspi2 periph clock */
    CRM_SDIO2_Periph_CLOCK                 = MAKE_VALUE(0x38, 15), /*!< sdio2 periph clock */
    /* apb1 periph */
    CRM_TMR2_Periph_CLOCK                  = MAKE_VALUE(0x40, 0),  /*!< tmr2 periph clock */
    CRM_TMR3_Periph_CLOCK                  = MAKE_VALUE(0x40, 1),  /*!< tmr3 periph clock */
    CRM_TMR4_Periph_CLOCK                  = MAKE_VALUE(0x40, 2),  /*!< tmr4 periph clock */
    CRM_TMR5_Periph_CLOCK                  = MAKE_VALUE(0x40, 3),  /*!< tmr5 periph clock */
    CRM_TMR6_Periph_CLOCK                  = MAKE_VALUE(0x40, 4),  /*!< tmr6 periph clock */
    CRM_TMR7_Periph_CLOCK                  = MAKE_VALUE(0x40, 5),  /*!< tmr7 periph clock */
    CRM_TMR12_Periph_CLOCK                 = MAKE_VALUE(0x40, 6),  /*!< tmr12 periph clock */
    CRM_TMR13_Periph_CLOCK                 = MAKE_VALUE(0x40, 7),  /*!< tmr13 periph clock */
    CRM_TMR14_Periph_CLOCK                 = MAKE_VALUE(0x40, 8),  /*!< tmr14 periph clock */
    CRM_WWDT_Periph_CLOCK                  = MAKE_VALUE(0x40, 11), /*!< wwdt periph clock */
    CRM_SPI2_Periph_CLOCK                  = MAKE_VALUE(0x40, 14), /*!< spi2 periph clock */
    CRM_SPI3_Periph_CLOCK                  = MAKE_VALUE(0x40, 15), /*!< spi3 periph clock */
    CRM_USART2_Periph_CLOCK                = MAKE_VALUE(0x40, 17), /*!< usart2 periph clock */
    CRM_USART3_Periph_CLOCK                = MAKE_VALUE(0x40, 18), /*!< usart3 periph clock */
    CRM_UART4_Periph_CLOCK                 = MAKE_VALUE(0x40, 19), /*!< uart4 periph clock */
    CRM_UART5_Periph_CLOCK                 = MAKE_VALUE(0x40, 20), /*!< uart5 periph clock */
    CRM_I2C1_Periph_CLOCK                  = MAKE_VALUE(0x40, 21), /*!< i2c1 periph clock */
    CRM_I2C2_Periph_CLOCK                  = MAKE_VALUE(0x40, 22), /*!< i2c2 periph clock */
    CRM_I2C3_Periph_CLOCK                  = MAKE_VALUE(0x40, 23), /*!< i2c3 periph clock */
    CRM_CAN1_Periph_CLOCK                  = MAKE_VALUE(0x40, 25), /*!< can1 periph clock */
    CRM_CAN2_Periph_CLOCK                  = MAKE_VALUE(0x40, 26), /*!< can2 periph clock */
    CRM_PWC_Periph_CLOCK                   = MAKE_VALUE(0x40, 28), /*!< pwc periph clock */
    CRM_DAC_Periph_CLOCK                   = MAKE_VALUE(0x40, 29), /*!< dac periph clock */
    CRM_UART7_Periph_CLOCK                 = MAKE_VALUE(0x40, 30), /*!< uart7 periph clock */
    CRM_UART8_Periph_CLOCK                 = MAKE_VALUE(0x40, 31), /*!< uart8 periph clock */
    /* apb2 periph */
    CRM_TMR1_Periph_CLOCK                  = MAKE_VALUE(0x44, 0),  /*!< tmr1 periph clock */
    CRM_TMR8_Periph_CLOCK                  = MAKE_VALUE(0x44, 1),  /*!< tmr8 periph clock */
    CRM_USART1_Periph_CLOCK                = MAKE_VALUE(0x44, 4),  /*!< usart1 periph clock */
    CRM_USART6_Periph_CLOCK                = MAKE_VALUE(0x44, 5),  /*!< usart6 periph clock */
    CRM_ADC1_Periph_CLOCK                  = MAKE_VALUE(0x44, 8),  /*!< adc1 periph clock */
    CRM_ADC2_Periph_CLOCK                  = MAKE_VALUE(0x44, 9),  /*!< adc2 periph clock */
    CRM_ADC3_Periph_CLOCK                  = MAKE_VALUE(0x44, 10), /*!< adc3 periph clock */
    CRM_SPI1_Periph_CLOCK                  = MAKE_VALUE(0x44, 12), /*!< spi1 periph clock */
    CRM_SPI4_Periph_CLOCK                  = MAKE_VALUE(0x44, 13), /*!< spi4 periph clock */
    CRM_SCFG_Periph_CLOCK                  = MAKE_VALUE(0x44, 14), /*!< scfg periph clock */
    CRM_TMR9_Periph_CLOCK                  = MAKE_VALUE(0x44, 16), /*!< tmr9 periph clock */
    CRM_TMR10_Periph_CLOCK                 = MAKE_VALUE(0x44, 17), /*!< tmr10 periph clock */
    CRM_TMR11_Periph_CLOCK                 = MAKE_VALUE(0x44, 18), /*!< tmr11 periph clock */
    CRM_TMR20_Periph_CLOCK                 = MAKE_VALUE(0x44, 20), /*!< tmr20 periph clock */
    CRM_ACC_Periph_CLOCK                   = MAKE_VALUE(0x44, 29)  /*!< acc periph clock */
    #endif

            #if defined (AT32F437xx)
            /* ahb periph1 */
            CRM_GPIOA_Periph_CLOCK                 = MAKE_VALUE(0x30, 0),  /*!< gpioa periph clock */
            CRM_GPIOB_Periph_CLOCK                 = MAKE_VALUE(0x30, 1),  /*!< gpiob periph clock */
            CRM_GPIOC_Periph_CLOCK                 = MAKE_VALUE(0x30, 2),  /*!< gpioc periph clock */
            CRM_GPIOD_Periph_CLOCK                 = MAKE_VALUE(0x30, 3),  /*!< gpiod periph clock */
            CRM_GPIOE_Periph_CLOCK                 = MAKE_VALUE(0x30, 4),  /*!< gpioe periph clock */
            CRM_GPIOF_Periph_CLOCK                 = MAKE_VALUE(0x30, 5),  /*!< gpiof periph clock */
            CRM_GPIOG_Periph_CLOCK                 = MAKE_VALUE(0x30, 6),  /*!< gpiog periph clock */
            CRM_GPIOH_Periph_CLOCK                 = MAKE_VALUE(0x30, 7),  /*!< gpioh periph clock */
            CRM_CRC_Periph_CLOCK                   = MAKE_VALUE(0x30, 12), /*!< crc periph clock */
            CRM_EDMA_Periph_CLOCK                  = MAKE_VALUE(0x30, 21), /*!< edma periph clock */
            CRM_DMA1_Periph_CLOCK                  = MAKE_VALUE(0x30, 22), /*!< dma1 periph clock */
            CRM_DMA2_Periph_CLOCK                  = MAKE_VALUE(0x30, 24), /*!< dma2 periph clock */
            CRM_EMAC_Periph_CLOCK                  = MAKE_VALUE(0x30, 25), /*!< emac periph clock */
            CRM_EMACTX_Periph_CLOCK                = MAKE_VALUE(0x30, 26), /*!< emac tx periph clock */
            CRM_EMACRX_Periph_CLOCK                = MAKE_VALUE(0x30, 27), /*!< emac rx periph clock */
            CRM_EMACPTP_Periph_CLOCK               = MAKE_VALUE(0x30, 28), /*!< emac ptp periph clock */
            CRM_OTGFS2_Periph_CLOCK                = MAKE_VALUE(0x30, 29), /*!< otgfs2 periph clock */
            /* ahb periph2 */
            CRM_DVP_Periph_CLOCK                   = MAKE_VALUE(0x34, 0),  /*!< dvp periph clock */
            CRM_OTGFS1_Periph_CLOCK                = MAKE_VALUE(0x34, 7),  /*!< otgfs1 periph clock */
            CRM_SDIO1_Periph_CLOCK                 = MAKE_VALUE(0x34, 15), /*!< sdio1 periph clock */
            /* ahb periph3 */
            CRM_XMC_Periph_CLOCK                   = MAKE_VALUE(0x38, 0),  /*!< xmc periph clock */
            CRM_QSPI1_Periph_CLOCK                 = MAKE_VALUE(0x38, 1),  /*!< qspi1 periph clock */
            CRM_QSPI2_Periph_CLOCK                 = MAKE_VALUE(0x38, 14), /*!< qspi2 periph clock */
            CRM_SDIO2_Periph_CLOCK                 = MAKE_VALUE(0x38, 15), /*!< sdio2 periph clock */
            /* apb1 periph */
            CRM_TMR2_Periph_CLOCK                  = MAKE_VALUE(0x40, 0),  /*!< tmr2 periph clock */
            CRM_TMR3_Periph_CLOCK                  = MAKE_VALUE(0x40, 1),  /*!< tmr3 periph clock */
            CRM_TMR4_Periph_CLOCK                  = MAKE_VALUE(0x40, 2),  /*!< tmr4 periph clock */
            CRM_TMR5_Periph_CLOCK                  = MAKE_VALUE(0x40, 3),  /*!< tmr5 periph clock */
            CRM_TMR6_Periph_CLOCK                  = MAKE_VALUE(0x40, 4),  /*!< tmr6 periph clock */
            CRM_TMR7_Periph_CLOCK                  = MAKE_VALUE(0x40, 5),  /*!< tmr7 periph clock */
            CRM_TMR12_Periph_CLOCK                 = MAKE_VALUE(0x40, 6),  /*!< tmr12 periph clock */
            CRM_TMR13_Periph_CLOCK                 = MAKE_VALUE(0x40, 7),  /*!< tmr13 periph clock */
            CRM_TMR14_Periph_CLOCK                 = MAKE_VALUE(0x40, 8),  /*!< tmr14 periph clock */
            CRM_WWDT_Periph_CLOCK                  = MAKE_VALUE(0x40, 11), /*!< wwdt periph clock */
            CRM_SPI2_Periph_CLOCK                  = MAKE_VALUE(0x40, 14), /*!< spi2 periph clock */
            CRM_SPI3_Periph_CLOCK                  = MAKE_VALUE(0x40, 15), /*!< spi3 periph clock */
            CRM_USART2_Periph_CLOCK                = MAKE_VALUE(0x40, 17), /*!< usart2 periph clock */
            CRM_USART3_Periph_CLOCK                = MAKE_VALUE(0x40, 18), /*!< usart3 periph clock */
            CRM_UART4_Periph_CLOCK                 = MAKE_VALUE(0x40, 19), /*!< uart4 periph clock */
            CRM_UART5_Periph_CLOCK                 = MAKE_VALUE(0x40, 20), /*!< uart5 periph clock */
            CRM_I2C1_Periph_CLOCK                  = MAKE_VALUE(0x40, 21), /*!< i2c1 periph clock */
            CRM_I2C2_Periph_CLOCK                  = MAKE_VALUE(0x40, 22), /*!< i2c2 periph clock */
            CRM_I2C3_Periph_CLOCK                  = MAKE_VALUE(0x40, 23), /*!< i2c3 periph clock */
            CRM_CAN1_Periph_CLOCK                  = MAKE_VALUE(0x40, 25), /*!< can1 periph clock */
            CRM_CAN2_Periph_CLOCK                  = MAKE_VALUE(0x40, 26), /*!< can2 periph clock */
            CRM_PWC_Periph_CLOCK                   = MAKE_VALUE(0x40, 28), /*!< pwc periph clock */
            CRM_DAC_Periph_CLOCK                   = MAKE_VALUE(0x40, 29), /*!< dac periph clock */
            CRM_UART7_Periph_CLOCK                 = MAKE_VALUE(0x40, 30), /*!< uart7 periph clock */
            CRM_UART8_Periph_CLOCK                 = MAKE_VALUE(0x40, 31), /*!< uart8 periph clock */
            /* apb2 periph */
            CRM_TMR1_Periph_CLOCK                  = MAKE_VALUE(0x44, 0),  /*!< tmr1 periph clock */
            CRM_TMR8_Periph_CLOCK                  = MAKE_VALUE(0x44, 1),  /*!< tmr8 periph clock */
            CRM_USART1_Periph_CLOCK                = MAKE_VALUE(0x44, 4),  /*!< usart1 periph clock */
            CRM_USART6_Periph_CLOCK                = MAKE_VALUE(0x44, 5),  /*!< usart6 periph clock */
            CRM_ADC1_Periph_CLOCK                  = MAKE_VALUE(0x44, 8),  /*!< adc1 periph clock */
            CRM_ADC2_Periph_CLOCK                  = MAKE_VALUE(0x44, 9),  /*!< adc2 periph clock */
            CRM_ADC3_Periph_CLOCK                  = MAKE_VALUE(0x44, 10), /*!< adc3 periph clock */
            CRM_SPI1_Periph_CLOCK                  = MAKE_VALUE(0x44, 12), /*!< spi1 periph clock */
            CRM_SPI4_Periph_CLOCK                  = MAKE_VALUE(0x44, 13), /*!< spi4 periph clock */
            CRM_SCFG_Periph_CLOCK                  = MAKE_VALUE(0x44, 14), /*!< scfg periph clock */
            CRM_TMR9_Periph_CLOCK                  = MAKE_VALUE(0x44, 16), /*!< tmr9 periph clock */
            CRM_TMR10_Periph_CLOCK                 = MAKE_VALUE(0x44, 17), /*!< tmr10 periph clock */
            CRM_TMR11_Periph_CLOCK                 = MAKE_VALUE(0x44, 18), /*!< tmr11 periph clock */
            CRM_TMR20_Periph_CLOCK                 = MAKE_VALUE(0x44, 20), /*!< tmr20 periph clock */
            CRM_ACC_Periph_CLOCK                   = MAKE_VALUE(0x44, 29)  /*!< acc periph clock */
            #endif

} CRM_Periph_Clock_Type;

/**
  * @brief crm periph reset
  */
typedef enum {
    #if defined (AT32F435xx)
    /* ahb periph1 */
    CRM_GPIOA_Periph_Reset                 = MAKE_VALUE(0x10, 0),  /*!< gpioa periph reset */
    CRM_GPIOB_Periph_Reset                 = MAKE_VALUE(0x10, 1),  /*!< gpiob periph reset */
    CRM_GPIOC_Periph_Reset                 = MAKE_VALUE(0x10, 2),  /*!< gpioc periph reset */
    CRM_GPIOD_Periph_Reset                 = MAKE_VALUE(0x10, 3),  /*!< gpiod periph reset */
    CRM_GPIOE_Periph_Reset                 = MAKE_VALUE(0x10, 4),  /*!< gpioe periph reset */
    CRM_GPIOF_Periph_Reset                 = MAKE_VALUE(0x10, 5),  /*!< gpiof periph reset */
    CRM_GPIOG_Periph_Reset                 = MAKE_VALUE(0x10, 6),  /*!< gpiog periph reset */
    CRM_GPIOH_Periph_Reset                 = MAKE_VALUE(0x10, 7),  /*!< gpioh periph reset */
    CRM_CRC_Periph_Reset                   = MAKE_VALUE(0x10, 12), /*!< crc periph reset */
    CRM_EDMA_Periph_Reset                  = MAKE_VALUE(0x10, 21), /*!< edma periph reset */
    CRM_DMA1_Periph_Reset                  = MAKE_VALUE(0x10, 22), /*!< dma1 periph reset */
    CRM_DMA2_Periph_Reset                  = MAKE_VALUE(0x10, 24), /*!< dma2 periph reset */
    CRM_OTGFS2_Periph_Reset                = MAKE_VALUE(0x10, 29), /*!< otgfs2 periph reset */
    /* ahb periph2 */
    CRM_DVP_Periph_Reset                   = MAKE_VALUE(0x14, 0),  /*!< dvp periph reset */
    CRM_OTGFS1_Periph_Reset                = MAKE_VALUE(0x14, 7),  /*!< otgfs1 periph reset */
    CRM_SDIO1_Periph_Reset                 = MAKE_VALUE(0x14, 15), /*!< sdio1 periph reset */
    /* ahb periph3 */
    CRM_XMC_Periph_Reset                   = MAKE_VALUE(0x18, 0),  /*!< xmc periph reset */
    CRM_QSPI1_Periph_Reset                 = MAKE_VALUE(0x18, 1),  /*!< qspi1 periph reset */
    CRM_QSPI2_Periph_Reset                 = MAKE_VALUE(0x18, 14), /*!< qspi2 periph reset */
    CRM_SDIO2_Periph_Reset                 = MAKE_VALUE(0x18, 15), /*!< sdio2 periph reset */
    /* apb1 periph */
    CRM_TMR2_Periph_Reset                  = MAKE_VALUE(0x20, 0),  /*!< tmr2 periph reset */
    CRM_TMR3_Periph_Reset                  = MAKE_VALUE(0x20, 1),  /*!< tmr3 periph reset */
    CRM_TMR4_Periph_Reset                  = MAKE_VALUE(0x20, 2),  /*!< tmr4 periph reset */
    CRM_TMR5_Periph_Reset                  = MAKE_VALUE(0x20, 3),  /*!< tmr5 periph reset */
    CRM_TMR6_Periph_Reset                  = MAKE_VALUE(0x20, 4),  /*!< tmr6 periph reset */
    CRM_TMR7_Periph_Reset                  = MAKE_VALUE(0x20, 5),  /*!< tmr7 periph reset */
    CRM_TMR12_Periph_Reset                 = MAKE_VALUE(0x20, 6),  /*!< tmr12 periph reset */
    CRM_TMR13_Periph_Reset                 = MAKE_VALUE(0x20, 7),  /*!< tmr13 periph reset */
    CRM_TMR14_Periph_Reset                 = MAKE_VALUE(0x20, 8),  /*!< tmr14 periph reset */
    CRM_WWDT_Periph_Reset                  = MAKE_VALUE(0x20, 11), /*!< wwdt periph reset */
    CRM_SPI2_Periph_Reset                  = MAKE_VALUE(0x20, 14), /*!< spi2 periph reset */
    CRM_SPI3_Periph_Reset                  = MAKE_VALUE(0x20, 15), /*!< spi3 periph reset */
    CRM_USART2_Periph_Reset                = MAKE_VALUE(0x20, 17), /*!< usart2 periph reset */
    CRM_USART3_Periph_Reset                = MAKE_VALUE(0x20, 18), /*!< usart3 periph reset */
    CRM_UART4_Periph_Reset                 = MAKE_VALUE(0x20, 19), /*!< uart4 periph reset */
    CRM_UART5_Periph_Reset                 = MAKE_VALUE(0x20, 20), /*!< uart5 periph reset */
    CRM_I2C1_Periph_Reset                  = MAKE_VALUE(0x20, 21), /*!< i2c1 periph reset */
    CRM_I2C2_Periph_Reset                  = MAKE_VALUE(0x20, 22), /*!< i2c2 periph reset */
    CRM_I2C3_Periph_Reset                  = MAKE_VALUE(0x20, 23), /*!< i2c3 periph reset */
    CRM_CAN1_Periph_Reset                  = MAKE_VALUE(0x20, 25), /*!< can1 periph reset */
    CRM_CAN2_Periph_Reset                  = MAKE_VALUE(0x20, 26), /*!< can2 periph reset */
    CRM_PWC_Periph_Reset                   = MAKE_VALUE(0x20, 28), /*!< pwc periph reset */
    CRM_DAC_Periph_Reset                   = MAKE_VALUE(0x20, 29), /*!< dac periph reset */
    CRM_UART7_Periph_Reset                 = MAKE_VALUE(0x20, 30), /*!< uart7 periph reset */
    CRM_UART8_Periph_Reset                 = MAKE_VALUE(0x20, 31), /*!< uart8 periph reset */
    /* apb2 periph */
    CRM_TMR1_Periph_Reset                  = MAKE_VALUE(0x24, 0),  /*!< tmr1 periph reset */
    CRM_TMR8_Periph_Reset                  = MAKE_VALUE(0x24, 1),  /*!< tmr8 periph reset */
    CRM_USART1_Periph_Reset                = MAKE_VALUE(0x24, 4),  /*!< usart1 periph reset */
    CRM_USART6_Periph_Reset                = MAKE_VALUE(0x24, 5),  /*!< usart6 periph reset */
    CRM_ADC_Periph_Reset                   = MAKE_VALUE(0x24, 8),  /*!< adc periph reset */
    CRM_SPI1_Periph_Reset                  = MAKE_VALUE(0x24, 12), /*!< spi1 periph reset */
    CRM_SPI4_Periph_Reset                  = MAKE_VALUE(0x24, 13), /*!< spi4 periph reset */
    CRM_SCFG_Periph_Reset                  = MAKE_VALUE(0x24, 14), /*!< scfg periph reset */
    CRM_TMR9_Periph_Reset                  = MAKE_VALUE(0x24, 16), /*!< tmr9 periph reset */
    CRM_TMR10_Periph_Reset                 = MAKE_VALUE(0x24, 17), /*!< tmr10 periph reset */
    CRM_TMR11_Periph_Reset                 = MAKE_VALUE(0x24, 18), /*!< tmr11 periph reset */
    CRM_TMR20_Periph_Reset                 = MAKE_VALUE(0x24, 20), /*!< tmr20 periph reset */
    CRM_ACC_Periph_Reset                   = MAKE_VALUE(0x24, 29)  /*!< acc periph reset */
    #endif

            #if defined (AT32F437xx)
            /* ahb periph1 */
            CRM_GPIOA_Periph_Reset                 = MAKE_VALUE(0x10, 0),  /*!< gpioa periph reset */
            CRM_GPIOB_Periph_Reset                 = MAKE_VALUE(0x10, 1),  /*!< gpiob periph reset */
            CRM_GPIOC_Periph_Reset                 = MAKE_VALUE(0x10, 2),  /*!< gpioc periph reset */
            CRM_GPIOD_Periph_Reset                 = MAKE_VALUE(0x10, 3),  /*!< gpiod periph reset */
            CRM_GPIOE_Periph_Reset                 = MAKE_VALUE(0x10, 4),  /*!< gpioe periph reset */
            CRM_GPIOF_Periph_Reset                 = MAKE_VALUE(0x10, 5),  /*!< gpiof periph reset */
            CRM_GPIOG_Periph_Reset                 = MAKE_VALUE(0x10, 6),  /*!< gpiog periph reset */
            CRM_GPIOH_Periph_Reset                 = MAKE_VALUE(0x10, 7),  /*!< gpioh periph reset */
            CRM_CRC_Periph_Reset                   = MAKE_VALUE(0x10, 12), /*!< crc periph reset */
            CRM_EDMA_Periph_Reset                  = MAKE_VALUE(0x10, 21), /*!< edma periph reset */
            CRM_DMA1_Periph_Reset                  = MAKE_VALUE(0x10, 22), /*!< dma1 periph reset */
            CRM_DMA2_Periph_Reset                  = MAKE_VALUE(0x10, 24), /*!< dma2 periph reset */
            CRM_EMAC_Periph_Reset                  = MAKE_VALUE(0x10, 25), /*!< emac periph reset */
            CRM_OTGFS2_Periph_Reset                = MAKE_VALUE(0x10, 29), /*!< otgfs2 periph reset */
            /* ahb periph2 */
            CRM_DVP_Periph_Reset                   = MAKE_VALUE(0x14, 0),  /*!< dvp periph reset */
            CRM_OTGFS1_Periph_Reset                = MAKE_VALUE(0x14, 7),  /*!< otgfs1 periph reset */
            CRM_SDIO1_Periph_Reset                 = MAKE_VALUE(0x14, 15), /*!< sdio1 periph reset */
            /* ahb periph3 */
            CRM_XMC_Periph_Reset                   = MAKE_VALUE(0x18, 0),  /*!< xmc periph reset */
            CRM_QSPI1_Periph_Reset                 = MAKE_VALUE(0x18, 1),  /*!< qspi1 periph reset */
            CRM_QSPI2_Periph_Reset                 = MAKE_VALUE(0x18, 14), /*!< qspi2 periph reset */
            CRM_SDIO2_Periph_Reset                 = MAKE_VALUE(0x18, 15), /*!< sdio2 periph reset */
            /* apb1 periph */
            CRM_TMR2_Periph_Reset                  = MAKE_VALUE(0x20, 0),  /*!< tmr2 periph reset */
            CRM_TMR3_Periph_Reset                  = MAKE_VALUE(0x20, 1),  /*!< tmr3 periph reset */
            CRM_TMR4_Periph_Reset                  = MAKE_VALUE(0x20, 2),  /*!< tmr4 periph reset */
            CRM_TMR5_Periph_Reset                  = MAKE_VALUE(0x20, 3),  /*!< tmr5 periph reset */
            CRM_TMR6_Periph_Reset                  = MAKE_VALUE(0x20, 4),  /*!< tmr6 periph reset */
            CRM_TMR7_Periph_Reset                  = MAKE_VALUE(0x20, 5),  /*!< tmr7 periph reset */
            CRM_TMR12_Periph_Reset                 = MAKE_VALUE(0x20, 6),  /*!< tmr12 periph reset */
            CRM_TMR13_Periph_Reset                 = MAKE_VALUE(0x20, 7),  /*!< tmr13 periph reset */
            CRM_TMR14_Periph_Reset                 = MAKE_VALUE(0x20, 8),  /*!< tmr14 periph reset */
            CRM_WWDT_Periph_Reset                  = MAKE_VALUE(0x20, 11), /*!< wwdt periph reset */
            CRM_SPI2_Periph_Reset                  = MAKE_VALUE(0x20, 14), /*!< spi2 periph reset */
            CRM_SPI3_Periph_Reset                  = MAKE_VALUE(0x20, 15), /*!< spi3 periph reset */
            CRM_USART2_Periph_Reset                = MAKE_VALUE(0x20, 17), /*!< usart2 periph reset */
            CRM_USART3_Periph_Reset                = MAKE_VALUE(0x20, 18), /*!< usart3 periph reset */
            CRM_UART4_Periph_Reset                 = MAKE_VALUE(0x20, 19), /*!< uart4 periph reset */
            CRM_UART5_Periph_Reset                 = MAKE_VALUE(0x20, 20), /*!< uart5 periph reset */
            CRM_I2C1_Periph_Reset                  = MAKE_VALUE(0x20, 21), /*!< i2c1 periph reset */
            CRM_I2C2_Periph_Reset                  = MAKE_VALUE(0x20, 22), /*!< i2c2 periph reset */
            CRM_I2C3_Periph_Reset                  = MAKE_VALUE(0x20, 23), /*!< i2c3 periph reset */
            CRM_CAN1_Periph_Reset                  = MAKE_VALUE(0x20, 25), /*!< can1 periph reset */
            CRM_CAN2_Periph_Reset                  = MAKE_VALUE(0x20, 26), /*!< can2 periph reset */
            CRM_PWC_Periph_Reset                   = MAKE_VALUE(0x20, 28), /*!< pwc periph reset */
            CRM_DAC_Periph_Reset                   = MAKE_VALUE(0x20, 29), /*!< dac periph reset */
            CRM_UART7_Periph_Reset                 = MAKE_VALUE(0x20, 30), /*!< uart7 periph reset */
            CRM_UART8_Periph_Reset                 = MAKE_VALUE(0x20, 31), /*!< uart8 periph reset */
            /* apb2 periph */
            CRM_TMR1_Periph_Reset                  = MAKE_VALUE(0x24, 0),  /*!< tmr1 periph reset */
            CRM_TMR8_Periph_Reset                  = MAKE_VALUE(0x24, 1),  /*!< tmr8 periph reset */
            CRM_USART1_Periph_Reset                = MAKE_VALUE(0x24, 4),  /*!< usart1 periph reset */
            CRM_USART6_Periph_Reset                = MAKE_VALUE(0x24, 5),  /*!< usart6 periph reset */
            CRM_ADC_Periph_Reset                   = MAKE_VALUE(0x24, 8),  /*!< adc periph reset */
            CRM_SPI1_Periph_Reset                  = MAKE_VALUE(0x24, 12), /*!< spi1 periph reset */
            CRM_SPI4_Periph_Reset                  = MAKE_VALUE(0x24, 13), /*!< spi4 periph reset */
            CRM_SCFG_Periph_Reset                  = MAKE_VALUE(0x24, 14), /*!< scfg periph reset */
            CRM_TMR9_Periph_Reset                  = MAKE_VALUE(0x24, 16), /*!< tmr9 periph reset */
            CRM_TMR10_Periph_Reset                 = MAKE_VALUE(0x24, 17), /*!< tmr10 periph reset */
            CRM_TMR11_Periph_Reset                 = MAKE_VALUE(0x24, 18), /*!< tmr11 periph reset */
            CRM_TMR20_Periph_Reset                 = MAKE_VALUE(0x24, 20), /*!< tmr20 periph reset */
            CRM_ACC_Periph_Reset                   = MAKE_VALUE(0x24, 29)  /*!< acc periph reset */
            #endif

} CRM_Periph_Reset_Type;

/**
  * @brief crm periph clock in low power mode
  */
typedef enum {
    #if defined (AT32F435xx)
    /* ahb periph1 */
    CRM_GPIOA_Periph_LOWPOWER              = MAKE_VALUE(0x50, 0),  /*!< gpioa sleep mode periph clock */
    CRM_GPIOB_Periph_LOWPOWER              = MAKE_VALUE(0x50, 1),  /*!< gpiob sleep mode periph clock */
    CRM_GPIOC_Periph_LOWPOWER              = MAKE_VALUE(0x50, 2),  /*!< gpioc sleep mode periph clock */
    CRM_GPIOD_Periph_LOWPOWER              = MAKE_VALUE(0x50, 3),  /*!< gpiod sleep mode periph clock */
    CRM_GPIOE_Periph_LOWPOWER              = MAKE_VALUE(0x50, 4),  /*!< gpioe sleep mode periph clock */
    CRM_GPIOF_Periph_LOWPOWER              = MAKE_VALUE(0x50, 5),  /*!< gpiof sleep mode periph clock */
    CRM_GPIOG_Periph_LOWPOWER              = MAKE_VALUE(0x50, 6),  /*!< gpiog sleep mode periph clock */
    CRM_GPIOH_Periph_LOWPOWER              = MAKE_VALUE(0x50, 7),  /*!< gpioh sleep mode periph clock */
    CRM_CRC_Periph_LOWPOWER                = MAKE_VALUE(0x50, 12), /*!< crc sleep mode periph clock */
    CRM_FLASH_Periph_LOWPOWER              = MAKE_VALUE(0x50, 15), /*!< flash sleep mode periph clock */
    CRM_SRAM1_Periph_LOWPOWER              = MAKE_VALUE(0x50, 16), /*!< sram1 sleep mode periph clock */
    CRM_SRAM2_Periph_LOWPOWER              = MAKE_VALUE(0x50, 17), /*!< sram2 sleep mode periph clock */
    CRM_EDMA_Periph_LOWPOWER               = MAKE_VALUE(0x50, 21), /*!< edma sleep mode periph clock */
    CRM_DMA1_Periph_LOWPOWER               = MAKE_VALUE(0x50, 22), /*!< dma1 sleep mode periph clock */
    CRM_DMA2_Periph_LOWPOWER               = MAKE_VALUE(0x50, 24), /*!< dma2 sleep mode periph clock */
    CRM_OTGFS2_Periph_LOWPOWER             = MAKE_VALUE(0x50, 29), /*!< otgfs2 sleep mode periph clock */
    /* ahb periph2 */
    CRM_DVP_Periph_LOWPOWER                = MAKE_VALUE(0x54, 0),  /*!< dvp sleep mode periph clock */
    CRM_OTGFS1_Periph_LOWPOWER             = MAKE_VALUE(0x54, 7),  /*!< otgfs1 sleep mode periph clock */
    CRM_SDIO1_Periph_LOWPOWER              = MAKE_VALUE(0x54, 15), /*!< sdio1 sleep mode periph clock */
    /* ahb periph3 */
    CRM_XMC_Periph_LOWPOWER                = MAKE_VALUE(0x58, 0),  /*!< xmc sleep mode periph clock */
    CRM_QSPI1_Periph_LOWPOWER              = MAKE_VALUE(0x58, 1),  /*!< qspi1 sleep mode periph clock */
    CRM_QSPI2_Periph_LOWPOWER              = MAKE_VALUE(0x58, 14), /*!< qspi2 sleep mode periph clock */
    CRM_SDIO2_Periph_LOWPOWER              = MAKE_VALUE(0x58, 15), /*!< sdio2 sleep mode periph clock */
    /* apb1 periph */
    CRM_TMR2_Periph_LOWPOWER               = MAKE_VALUE(0x60, 0),  /*!< tmr2 sleep mode periph clock */
    CRM_TMR3_Periph_LOWPOWER               = MAKE_VALUE(0x60, 1),  /*!< tmr3 sleep mode periph clock */
    CRM_TMR4_Periph_LOWPOWER               = MAKE_VALUE(0x60, 2),  /*!< tmr4 sleep mode periph clock */
    CRM_TMR5_Periph_LOWPOWER               = MAKE_VALUE(0x60, 3),  /*!< tmr5 sleep mode periph clock */
    CRM_TMR6_Periph_LOWPOWER               = MAKE_VALUE(0x60, 4),  /*!< tmr6 sleep mode periph clock */
    CRM_TMR7_Periph_LOWPOWER               = MAKE_VALUE(0x60, 5),  /*!< tmr7 sleep mode periph clock */
    CRM_TMR12_Periph_LOWPOWER              = MAKE_VALUE(0x60, 6),  /*!< tmr12 sleep mode periph clock */
    CRM_TMR13_Periph_LOWPOWER              = MAKE_VALUE(0x60, 7),  /*!< tmr13 sleep mode periph clock */
    CRM_TMR14_Periph_LOWPOWER              = MAKE_VALUE(0x60, 8),  /*!< tmr14 sleep mode periph clock */
    CRM_WWDT_Periph_LOWPOWER               = MAKE_VALUE(0x60, 11), /*!< wwdt sleep mode periph clock */
    CRM_SPI2_Periph_LOWPOWER               = MAKE_VALUE(0x60, 14), /*!< spi2 sleep mode periph clock */
    CRM_SPI3_Periph_LOWPOWER               = MAKE_VALUE(0x60, 15), /*!< spi3 sleep mode periph clock */
    CRM_USART2_Periph_LOWPOWER             = MAKE_VALUE(0x60, 17), /*!< usart2 sleep mode periph clock */
    CRM_USART3_Periph_LOWPOWER             = MAKE_VALUE(0x60, 18), /*!< usart3 sleep mode periph clock */
    CRM_UART4_Periph_LOWPOWER              = MAKE_VALUE(0x60, 19), /*!< uart4 sleep mode periph clock */
    CRM_UART5_Periph_LOWPOWER              = MAKE_VALUE(0x60, 20), /*!< uart5 sleep mode periph clock */
    CRM_I2C1_Periph_LOWPOWER               = MAKE_VALUE(0x60, 21), /*!< i2c1 sleep mode periph clock */
    CRM_I2C2_Periph_LOWPOWER               = MAKE_VALUE(0x60, 22), /*!< i2c2 sleep mode periph clock */
    CRM_I2C3_Periph_LOWPOWER               = MAKE_VALUE(0x60, 23), /*!< i2c3 sleep mode periph clock */
    CRM_CAN1_Periph_LOWPOWER               = MAKE_VALUE(0x60, 25), /*!< can1 sleep mode periph clock */
    CRM_CAN2_Periph_LOWPOWER               = MAKE_VALUE(0x60, 26), /*!< can2 sleep mode periph clock */
    CRM_PWC_Periph_LOWPOWER                = MAKE_VALUE(0x60, 28), /*!< pwc sleep mode periph clock */
    CRM_DAC_Periph_LOWPOWER                = MAKE_VALUE(0x60, 29), /*!< dac sleep mode periph clock */
    CRM_UART7_Periph_LOWPOWER              = MAKE_VALUE(0x60, 30), /*!< uart7 sleep mode periph clock */
    CRM_UART8_Periph_LOWPOWER              = MAKE_VALUE(0x60, 31), /*!< uart8 sleep mode periph clock */
    /* apb2 periph */
    CRM_TMR1_Periph_LOWPOWER               = MAKE_VALUE(0x64, 0),  /*!< tmr1 sleep mode periph clock */
    CRM_TMR8_Periph_LOWPOWER               = MAKE_VALUE(0x64, 1),  /*!< tmr8 sleep mode periph clock */
    CRM_USART1_Periph_LOWPOWER             = MAKE_VALUE(0x64, 4),  /*!< usart1 sleep mode periph clock */
    CRM_USART6_Periph_LOWPOWER             = MAKE_VALUE(0x64, 5),  /*!< usart6 sleep mode periph clock */
    CRM_ADC1_Periph_LOWPOWER               = MAKE_VALUE(0x64, 8),  /*!< adc1 sleep mode periph clock */
    CRM_ADC2_Periph_LOWPOWER               = MAKE_VALUE(0x64, 9),  /*!< adc2 sleep mode periph clock */
    CRM_ADC3_Periph_LOWPOWER               = MAKE_VALUE(0x64, 10), /*!< adc3 sleep mode periph clock */
    CRM_SPI1_Periph_LOWPOWER               = MAKE_VALUE(0x64, 12), /*!< spi1 sleep mode periph clock */
    CRM_SPI4_Periph_LOWPOWER               = MAKE_VALUE(0x64, 13), /*!< spi4 sleep mode periph clock */
    CRM_SCFG_Periph_LOWPOWER               = MAKE_VALUE(0x64, 14), /*!< scfg sleep mode periph clock */
    CRM_TMR9_Periph_LOWPOWER               = MAKE_VALUE(0x64, 16), /*!< tmr9 sleep mode periph clock */
    CRM_TMR10_Periph_LOWPOWER              = MAKE_VALUE(0x64, 17), /*!< tmr10 sleep mode periph clock */
    CRM_TMR11_Periph_LOWPOWER              = MAKE_VALUE(0x64, 18), /*!< tmr11 sleep mode periph clock */
    CRM_TMR20_Periph_LOWPOWER              = MAKE_VALUE(0x64, 20), /*!< tmr20 sleep mode periph clock */
    CRM_ACC_Periph_LOWPOWER                = MAKE_VALUE(0x64, 29)  /*!< acc sleep mode periph clock */
    #endif

            #if defined (AT32F437xx)
            /* ahb periph1 */
            CRM_GPIOA_Periph_LOWPOWER              = MAKE_VALUE(0x50, 0),  /*!< gpioa sleep mode periph clock */
            CRM_GPIOB_Periph_LOWPOWER              = MAKE_VALUE(0x50, 1),  /*!< gpiob sleep mode periph clock */
            CRM_GPIOC_Periph_LOWPOWER              = MAKE_VALUE(0x50, 2),  /*!< gpioc sleep mode periph clock */
            CRM_GPIOD_Periph_LOWPOWER              = MAKE_VALUE(0x50, 3),  /*!< gpiod sleep mode periph clock */
            CRM_GPIOE_Periph_LOWPOWER              = MAKE_VALUE(0x50, 4),  /*!< gpioe sleep mode periph clock */
            CRM_GPIOF_Periph_LOWPOWER              = MAKE_VALUE(0x50, 5),  /*!< gpiof sleep mode periph clock */
            CRM_GPIOG_Periph_LOWPOWER              = MAKE_VALUE(0x50, 6),  /*!< gpiog sleep mode periph clock */
            CRM_GPIOH_Periph_LOWPOWER              = MAKE_VALUE(0x50, 7),  /*!< gpioh sleep mode periph clock */
            CRM_CRC_Periph_LOWPOWER                = MAKE_VALUE(0x50, 12), /*!< crc sleep mode periph clock */
            CRM_FLASH_Periph_LOWPOWER              = MAKE_VALUE(0x50, 15), /*!< flash sleep mode periph clock */
            CRM_SRAM1_Periph_LOWPOWER              = MAKE_VALUE(0x50, 16), /*!< sram1 sleep mode periph clock */
            CRM_SRAM2_Periph_LOWPOWER              = MAKE_VALUE(0x50, 17), /*!< sram2 sleep mode periph clock */
            CRM_EDMA_Periph_LOWPOWER               = MAKE_VALUE(0x50, 21), /*!< edma sleep mode periph clock */
            CRM_DMA1_Periph_LOWPOWER               = MAKE_VALUE(0x50, 22), /*!< dma1 sleep mode periph clock */
            CRM_DMA2_Periph_LOWPOWER               = MAKE_VALUE(0x50, 24), /*!< dma2 sleep mode periph clock */
            CRM_EMAC_Periph_LOWPOWER               = MAKE_VALUE(0x50, 25), /*!< emac sleep mode periph clock */
            CRM_EMACTX_Periph_LOWPOWER             = MAKE_VALUE(0x50, 26), /*!< emac tx sleep mode periph clock */
            CRM_EMACRX_Periph_LOWPOWER             = MAKE_VALUE(0x50, 27), /*!< emac rx sleep mode periph clock */
            CRM_EMACPTP_Periph_LOWPOWER            = MAKE_VALUE(0x50, 28), /*!< emac ptp sleep mode periph clock */
            CRM_OTGFS2_Periph_LOWPOWER             = MAKE_VALUE(0x50, 29), /*!< otgfs2 sleep mode periph clock */
            /* ahb periph2 */
            CRM_DVP_Periph_LOWPOWER                = MAKE_VALUE(0x54, 0),  /*!< dvp sleep mode periph clock */
            CRM_OTGFS1_Periph_LOWPOWER             = MAKE_VALUE(0x54, 7),  /*!< otgfs1 sleep mode periph clock */
            CRM_SDIO1_Periph_LOWPOWER              = MAKE_VALUE(0x54, 15), /*!< sdio1 sleep mode periph clock */
            /* ahb periph3 */
            CRM_XMC_Periph_LOWPOWER                = MAKE_VALUE(0x58, 0),  /*!< xmc sleep mode periph clock */
            CRM_QSPI1_Periph_LOWPOWER              = MAKE_VALUE(0x58, 1),  /*!< qspi1 sleep mode periph clock */
            CRM_QSPI2_Periph_LOWPOWER              = MAKE_VALUE(0x58, 14), /*!< qspi2 sleep mode periph clock */
            CRM_SDIO2_Periph_LOWPOWER              = MAKE_VALUE(0x58, 15), /*!< sdio2 sleep mode periph clock */
            /* apb1 periph */
            CRM_TMR2_Periph_LOWPOWER               = MAKE_VALUE(0x60, 0),  /*!< tmr2 sleep mode periph clock */
            CRM_TMR3_Periph_LOWPOWER               = MAKE_VALUE(0x60, 1),  /*!< tmr3 sleep mode periph clock */
            CRM_TMR4_Periph_LOWPOWER               = MAKE_VALUE(0x60, 2),  /*!< tmr4 sleep mode periph clock */
            CRM_TMR5_Periph_LOWPOWER               = MAKE_VALUE(0x60, 3),  /*!< tmr5 sleep mode periph clock */
            CRM_TMR6_Periph_LOWPOWER               = MAKE_VALUE(0x60, 4),  /*!< tmr6 sleep mode periph clock */
            CRM_TMR7_Periph_LOWPOWER               = MAKE_VALUE(0x60, 5),  /*!< tmr7 sleep mode periph clock */
            CRM_TMR12_Periph_LOWPOWER              = MAKE_VALUE(0x60, 6),  /*!< tmr12 sleep mode periph clock */
            CRM_TMR13_Periph_LOWPOWER              = MAKE_VALUE(0x60, 7),  /*!< tmr13 sleep mode periph clock */
            CRM_TMR14_Periph_LOWPOWER              = MAKE_VALUE(0x60, 8),  /*!< tmr14 sleep mode periph clock */
            CRM_WWDT_Periph_LOWPOWER               = MAKE_VALUE(0x60, 11), /*!< wwdt sleep mode periph clock */
            CRM_SPI2_Periph_LOWPOWER               = MAKE_VALUE(0x60, 14), /*!< spi2 sleep mode periph clock */
            CRM_SPI3_Periph_LOWPOWER               = MAKE_VALUE(0x60, 15), /*!< spi3 sleep mode periph clock */
            CRM_USART2_Periph_LOWPOWER             = MAKE_VALUE(0x60, 17), /*!< usart2 sleep mode periph clock */
            CRM_USART3_Periph_LOWPOWER             = MAKE_VALUE(0x60, 18), /*!< usart3 sleep mode periph clock */
            CRM_UART4_Periph_LOWPOWER              = MAKE_VALUE(0x60, 19), /*!< uart4 sleep mode periph clock */
            CRM_UART5_Periph_LOWPOWER              = MAKE_VALUE(0x60, 20), /*!< uart5 sleep mode periph clock */
            CRM_I2C1_Periph_LOWPOWER               = MAKE_VALUE(0x60, 21), /*!< i2c1 sleep mode periph clock */
            CRM_I2C2_Periph_LOWPOWER               = MAKE_VALUE(0x60, 22), /*!< i2c2 sleep mode periph clock */
            CRM_I2C3_Periph_LOWPOWER               = MAKE_VALUE(0x60, 23), /*!< i2c3 sleep mode periph clock */
            CRM_CAN1_Periph_LOWPOWER               = MAKE_VALUE(0x60, 25), /*!< can1 sleep mode periph clock */
            CRM_CAN2_Periph_LOWPOWER               = MAKE_VALUE(0x60, 26), /*!< can2 sleep mode periph clock */
            CRM_PWC_Periph_LOWPOWER                = MAKE_VALUE(0x60, 28), /*!< pwc sleep mode periph clock */
            CRM_DAC_Periph_LOWPOWER                = MAKE_VALUE(0x60, 29), /*!< dac sleep mode periph clock */
            CRM_UART7_Periph_LOWPOWER              = MAKE_VALUE(0x60, 30), /*!< uart7 sleep mode periph clock */
            CRM_UART8_Periph_LOWPOWER              = MAKE_VALUE(0x60, 31), /*!< uart8 sleep mode periph clock */
            /* apb2 periph */
            CRM_TMR1_Periph_LOWPOWER               = MAKE_VALUE(0x64, 0),  /*!< tmr1 sleep mode periph clock */
            CRM_TMR8_Periph_LOWPOWER               = MAKE_VALUE(0x64, 1),  /*!< tmr8 sleep mode periph clock */
            CRM_USART1_Periph_LOWPOWER             = MAKE_VALUE(0x64, 4),  /*!< usart1 sleep mode periph clock */
            CRM_USART6_Periph_LOWPOWER             = MAKE_VALUE(0x64, 5),  /*!< usart6 sleep mode periph clock */
            CRM_ADC1_Periph_LOWPOWER               = MAKE_VALUE(0x64, 8),  /*!< adc1 sleep mode periph clock */
            CRM_ADC2_Periph_LOWPOWER               = MAKE_VALUE(0x64, 9),  /*!< adc2 sleep mode periph clock */
            CRM_ADC3_Periph_LOWPOWER               = MAKE_VALUE(0x64, 10), /*!< adc3 sleep mode periph clock */
            CRM_SPI1_Periph_LOWPOWER               = MAKE_VALUE(0x64, 12), /*!< spi1 sleep mode periph clock */
            CRM_SPI4_Periph_LOWPOWER               = MAKE_VALUE(0x64, 13), /*!< spi4 sleep mode periph clock */
            CRM_SCFG_Periph_LOWPOWER               = MAKE_VALUE(0x64, 14), /*!< scfg sleep mode periph clock */
            CRM_TMR9_Periph_LOWPOWER               = MAKE_VALUE(0x64, 16), /*!< tmr9 sleep mode periph clock */
            CRM_TMR10_Periph_LOWPOWER              = MAKE_VALUE(0x64, 17), /*!< tmr10 sleep mode periph clock */
            CRM_TMR11_Periph_LOWPOWER              = MAKE_VALUE(0x64, 18), /*!< tmr11 sleep mode periph clock */
            CRM_TMR20_Periph_LOWPOWER              = MAKE_VALUE(0x64, 20), /*!< tmr20 sleep mode periph clock */
            CRM_ACC_Periph_LOWPOWER                = MAKE_VALUE(0x64, 29)  /*!< acc sleep mode periph clock */
            #endif

} CRM_Periph_Clock_LowPower_Type;

/**
  * @brief crm pll clock source
  */
typedef enum {
    CRM_PLL_Source_HICK                    = 0x00, /*!< high speed internal clock as pll reference clock source */
    CRM_PLL_Source_HEXT                    = 0x01  /*!< high speed external crystal as pll reference clock source */
} CRM_PLL_Clock_Source_Type;

/**
  * @brief crm pll fr
  */
typedef enum {
    CRM_PLL_FR_1                           = 0x00, /*!< pll post-division div1 */
    CRM_PLL_FR_2                           = 0x01, /*!< pll post-division div2 */
    CRM_PLL_FR_4                           = 0x02, /*!< pll post-division div4 */
    CRM_PLL_FR_8                           = 0x03, /*!< pll post-division div8 */
    CRM_PLL_FR_16                          = 0x04, /*!< pll post-division div16 */
    CRM_PLL_FR_32                          = 0x05  /*!< pll post-division div32 */
} CRM_PLL_FR_Type;

/**
  * @brief crm clock source
  */
typedef enum {
    CRM_Clock_Source_HICK                  = 0x00, /*!< high speed internal clock */
    CRM_Clock_Source_HEXT                  = 0x01, /*!< high speed external crystal */
    CRM_Clock_Source_PLL                   = 0x02, /*!< phase locking loop */
    CRM_Clock_Source_LEXT                  = 0x03, /*!< low speed external crystal */
    CRM_Clock_Source_LICK                  = 0x04  /*!< low speed internal clock */
} CRM_Clock_Source_Type;

/**
  * @brief crm ahb division
  */
typedef enum {
    CRM_AHB_Div_1                          = 0x00, /*!< sclk div1 to ahbclk */
    CRM_AHB_Div_2                          = 0x08, /*!< sclk div2 to ahbclk */
    CRM_AHB_Div_4                          = 0x09, /*!< sclk div4 to ahbclk */
    CRM_AHB_Div_8                          = 0x0A, /*!< sclk div8 to ahbclk */
    CRM_AHB_Div_16                         = 0x0B, /*!< sclk div16 to ahbclk */
    CRM_AHB_Div_64                         = 0x0C, /*!< sclk div64 to ahbclk */
    CRM_AHB_Div_128                        = 0x0D, /*!< sclk div128 to ahbclk */
    CRM_AHB_Div_256                        = 0x0E, /*!< sclk div256 to ahbclk */
    CRM_AHB_Div_512                        = 0x0F  /*!< sclk div512 to ahbclk */
} CRM_AHB_Div_Type;

/**
  * @brief crm apb1 division
  */
typedef enum {
    CRM_APB1_Div_1                         = 0x00, /*!< ahbclk div1 to apb1clk */
    CRM_APB1_Div_2                         = 0x04, /*!< ahbclk div2 to apb1clk */
    CRM_APB1_Div_4                         = 0x05, /*!< ahbclk div4 to apb1clk */
    CRM_APB1_Div_8                         = 0x06, /*!< ahbclk div8 to apb1clk */
    CRM_APB1_Div_16                        = 0x07  /*!< ahbclk div16 to apb1clk */
} CRM_APB1_Div_Type;

/**
  * @brief crm apb2 division
  */
typedef enum {
    CRM_APB2_Div_1                         = 0x00, /*!< ahbclk div1 to apb2clk */
    CRM_APB2_Div_2                         = 0x04, /*!< ahbclk div2 to apb2clk */
    CRM_APB2_Div_4                         = 0x05, /*!< ahbclk div4 to apb2clk */
    CRM_APB2_Div_8                         = 0x06, /*!< ahbclk div8 to apb2clk */
    CRM_APB2_Div_16                        = 0x07  /*!< ahbclk div16 to apb2clk */
} CRM_APB2_Div_Type;

/**
  * @brief crm usb division
  */
typedef enum {
    CRM_USB_Div_1_5                        = 0x00, /*!< pllclk div1.5 to usbclk */
    CRM_USB_Div_1                          = 0x01, /*!< pllclk div1 to usbclk */
    CRM_USB_Div_2_5                        = 0x02, /*!< pllclk div2.5 to usbclk */
    CRM_USB_Div_2                          = 0x03, /*!< pllclk div2 to usbclk */
    CRM_USB_Div_3_5                        = 0x04, /*!< pllclk div3.5 to usbclk */
    CRM_USB_Div_3                          = 0x05, /*!< pllclk div3 to usbclk */
    CRM_USB_Div_4_5                        = 0x06, /*!< pllclk div4.5 to usbclk */
    CRM_USB_Div_4                          = 0x07, /*!< pllclk div4 to usbclk */
    CRM_USB_Div_5_5                        = 0x08, /*!< pllclk div5.5 to usbclk */
    CRM_USB_Div_5                          = 0x09, /*!< pllclk div5 to usbclk */
    CRM_USB_Div_6_5                        = 0x0A, /*!< pllclk div6.5 to usbclk */
    CRM_USB_Div_6                          = 0x0B, /*!< pllclk div6 to usbclk */
    CRM_USB_Div_7                          = 0x0C  /*!< pllclk div7 to usbclk */
} CRM_USB_Div_Type;

/**
  * @brief crm ertc clock
  */
typedef enum {
    CRM_ERTC_Clock_NOCLK                   = 0x000, /*!< no clock as ertc clock source */
    CRM_ERTC_Clock_LEXT                    = 0x001, /*!< low speed external crystal as ertc clock source */
    CRM_ERTC_Clock_LICK                    = 0x002, /*!< low speed internal clock as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_2              = 0x023, /*!< high speed external crystal div2 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_3              = 0x033, /*!< high speed external crystal div3 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_4              = 0x043, /*!< high speed external crystal div4 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_5              = 0x053, /*!< high speed external crystal div5 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_6              = 0x063, /*!< high speed external crystal div6 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_7              = 0x073, /*!< high speed external crystal div7 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_8              = 0x083, /*!< high speed external crystal div8 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_9              = 0x093, /*!< high speed external crystal div9 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_10             = 0x0A3, /*!< high speed external crystal div10 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_11             = 0x0B3, /*!< high speed external crystal div11 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_12             = 0x0C3, /*!< high speed external crystal div12 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_13             = 0x0D3, /*!< high speed external crystal div13 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_14             = 0x0E3, /*!< high speed external crystal div14 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_15             = 0x0F3, /*!< high speed external crystal div15 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_16             = 0x103, /*!< high speed external crystal div16 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_17             = 0x113, /*!< high speed external crystal div17 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_18             = 0x123, /*!< high speed external crystal div18 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_19             = 0x133, /*!< high speed external crystal div19 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_20             = 0x143, /*!< high speed external crystal div20 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_21             = 0x153, /*!< high speed external crystal div21 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_22             = 0x163, /*!< high speed external crystal div22 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_23             = 0x173, /*!< high speed external crystal div23 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_24             = 0x183, /*!< high speed external crystal div24 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_25             = 0x193, /*!< high speed external crystal div25 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_26             = 0x1A3, /*!< high speed external crystal div26 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_27             = 0x1B3, /*!< high speed external crystal div27 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_28             = 0x1C3, /*!< high speed external crystal div28 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_29             = 0x1D3, /*!< high speed external crystal div29 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_30             = 0x1E3, /*!< high speed external crystal div30 as ertc clock source */
    CRM_ERTC_Clock_Hext_Div_31             = 0x1F3  /*!< high speed external crystal div31 as ertc clock source */
} CRM_ERTC_Clock_Type;

/**
  * @brief crm hick 48mhz division
  */
typedef enum {
    CRM_HICK48_DIV6                        = 0x00, /*!< fixed 8 mhz when hick is selected as sclk */
    CRM_HICK48_NODIV                       = 0x01  /*!< 8 mhz or 48 mhz depend on hickdiv when hick is selected as sclk */
} CRM_HICK_Div_6_Type;

/**
  * @brief crm sclk select
  */
typedef enum {
    CRM_SCLK_HICK                          = 0x00, /*!< select high speed internal clock as sclk */
    CRM_SCLK_HEXT                          = 0x01, /*!< select high speed external crystal as sclk */
    CRM_SCLK_PLL                           = 0x02  /*!< select phase locking loop clock as sclk */
} CRM_SCLK_Type;

/**
  * @brief crm clkout index
  */
typedef enum {
    CRM_CLKOUT_INDEX_1                     = 0x00, /*!< clkout1 */
    CRM_CLKOUT_INDEX_2                     = 0x01  /*!< clkout2 */
} CRM_CLKout_index_Type;

/**
  * @brief crm clkout1 select
  */
typedef enum {
    CRM_CLKOUT1_HICK                       = 0x00, /*!< output high speed internal clock to clkout1 pin */
    CRM_CLKOUT1_LEXT                       = 0x01, /*!< output low speed external crystal to clkout1 pin */
    CRM_CLKOUT1_HEXT                       = 0x02, /*!< output high speed external crystal to clkout1 pin */
    CRM_CLKOUT1_PLL                        = 0x03  /*!< output phase locking loop clock to clkout1 pin */
} CRM_CLKout1_Select_Type;

/**
  * @brief crm clkout2 select
  */
typedef enum {
    CRM_CLKOUT2_SCLK                       = 0x00,  /*!< output system clock to clkout2 pin */
    CRM_CLKOUT2_HEXT                       = 0x02,  /*!< output high speed external crystal to clkout2 pin */
    CRM_CLKOUT2_PLL                        = 0x03,  /*!< output phase locking loop clock to clkout2 pin */
    CRM_CLKOUT2_USB                        = 0x10, /*!< output usbclk to clkout2 pin */
    CRM_CLKOUT2_ADC                        = 0x11, /*!< output adcclk to clkout2 pin */
    CRM_CLKOUT2_HICK                       = 0x12, /*!< output high speed internal clock to clkout2 pin */
    CRM_CLKOUT2_LICK                       = 0x13, /*!< output low speed internal clock to clkout2 pin */
    CRM_CLKOUT2_LEXT                       = 0x14  /*!< output low speed external crystal to clkout2 pin */
} CRM_CLKout2_Select_Type;

/**
  * @brief crm clkout division1
  */
typedef enum {
    CRM_CLKOUT_DIV1_1                      = 0x00, /*!< clkout division1 div1 */
    CRM_CLKOUT_DIV1_2                      = 0x04, /*!< clkout division1 div2 */
    CRM_CLKOUT_DIV1_3                      = 0x05, /*!< clkout division1 div3 */
    CRM_CLKOUT_DIV1_4                      = 0x06, /*!< clkout division1 div4 */
    CRM_CLKOUT_DIV1_5                      = 0x07  /*!< clkout division1 div5 */
} CRM_CLKout_div1_Type;

/**
  * @brief crm clkout division2
  */
typedef enum {
    CRM_CLKOUT_Div2_1                      = 0x00, /*!< clkout division2 div1 */
    CRM_CLKOUT_Div2_2                      = 0x08, /*!< clkout division2 div2 */
    CRM_CLKOUT_Div2_4                      = 0x09, /*!< clkout division2 div4 */
    CRM_CLKOUT_Div2_8                      = 0x0A, /*!< clkout division2 div8 */
    CRM_CLKOUT_Div2_16                     = 0x0B, /*!< clkout division2 div16 */
    CRM_CLKOUT_Div2_64                     = 0x0C, /*!< clkout division2 div64 */
    CRM_CLKOUT_Div2_128                    = 0x0D, /*!< clkout division2 div128 */
    CRM_CLKOUT_Div2_256                    = 0x0E, /*!< clkout division2 div256 */
    CRM_CLKOUT_Div2_512                    = 0x0F  /*!< clkout division2 div512 */
} CRM_CLKout_Div2_Type;

/**
  * @brief crm auto step mode
  */
typedef enum {
    CRM_Auto_Step_Mode_DISABLE             = 0x00, /*!< disable auto step mode */
    CRM_Auto_Step_Mode_ENABLE              = 0x03  /*!< enable auto step mode */
} CRM_Auto_Step_Mode_Type;

/**
  * @brief crm usb 48 mhz clock source select
  */
typedef enum {
    CRM_USB_Clock_Source_PLL               = 0x00, /*!< select phase locking loop clock as usb clock source */
    CRM_USB_Clock_Source_HICK              = 0x01  /*!< select high speed internal clock as usb clock source */
} CRM_USB_Clock_Source_Type;

/**
  * @brief crm hick as system clock frequency select
  */
typedef enum {
    CRM_HICK_SCLK_8MHZ                     = 0x00, /*!< fixed 8 mhz when hick is selected as sclk */
    CRM_HICK_SCLK_48MHZ                    = 0x01  /*!< 8 mhz or 48 mhz depend on hickdiv when hick is selected as sclk */
} CRM_HICK_SCLK_Frequency_Type;

/**
  * @brief crm emac output pulse width
  */
typedef enum {
    CRM_EMAC_Pulse_125MS                   = 0x00, /*!< emac output pulse width 125ms */
    CRM_EMAC_Pulse_1SCLK                   = 0x01  /*!< emac output pulse width 1 system clock */
} CRM_EMAC_OutPut_Pulse_Type;

/**
  * @brief crm clocks freqency structure
  */
typedef struct {
    uint32_t sclk_freq; /*!< system clock frequency */
    uint32_t ahb_freq;  /*!< ahb bus clock frequency */
    uint32_t apb2_freq; /*!< apb2 bus clock frequency */
    uint32_t apb1_freq; /*!< apb1 bus clock frequency */
} CRM_Clocks_Freq_Type;

/**
  * @brief type define crm register all
  */
typedef struct {
    /**
      * @brief crm ctrl register, offset:0x00
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t hicken               : 1; /* [0] */
            __IO uint32_t hickstbl             : 1; /* [1] */
            __IO uint32_t hicktrim             : 6; /* [7:2] */
            __IO uint32_t hickcal              : 8; /* [15:8] */
            __IO uint32_t hexten               : 1; /* [16] */
            __IO uint32_t hextstbl             : 1; /* [17] */
            __IO uint32_t hextbyps             : 1; /* [18] */
            __IO uint32_t cfden                : 1; /* [19] */
            __IO uint32_t reserved1            : 4; /* [23:20] */
            __IO uint32_t pllen                : 1; /* [24] */
            __IO uint32_t pllstbl              : 1; /* [25] */
            __IO uint32_t reserved2            : 6; /* [31:26] */
        } ctrl_bit;
    };

    /**
      * @brief crm pllcfg register, offset:0x04
      */
    union {
        __IO uint32_t pllcfg;
        struct {
            __IO uint32_t pllms                : 4; /* [3:0] */
            __IO uint32_t reserved1            : 2; /* [5:4] */
            __IO uint32_t pllns                : 9; /* [14:6] */
            __IO uint32_t reserved2            : 1; /* [15] */
            __IO uint32_t pllfr                : 3; /* [18:16] */
            __IO uint32_t reserved3            : 3; /* [21:19] */
            __IO uint32_t pllrcs               : 1; /* [22] */
            __IO uint32_t reserved4            : 9; /* [31:23] */
        } pllcfg_bit;
    };

    /**
      * @brief crm cfg register, offset:0x08
      */
    union {
        __IO uint32_t cfg;
        struct {
            __IO uint32_t sclksel              : 2; /* [1:0] */
            __IO uint32_t sclksts              : 2; /* [3:2] */
            __IO uint32_t ahbdiv               : 4; /* [7:4] */
            __IO uint32_t reserved1            : 2; /* [9:8] */
            __IO uint32_t apb1div              : 3; /* [12:10] */
            __IO uint32_t apb2div              : 3; /* [15:13] */
            __IO uint32_t ertcdiv              : 5; /* [20:16] */
            __IO uint32_t clkout1_sel          : 2; /* [22:21] */
            __IO uint32_t reserved2            : 1; /* [23] */
            __IO uint32_t clkout1div1          : 3; /* [26:24] */
            __IO uint32_t clkout2div1          : 3; /* [29:27] */
            __IO uint32_t clkout2_sel1         : 2; /* [31:30] */
        } cfg_bit;
    };

    /**
      * @brief crm clkint register, offset:0x0C
      */
    union {
        __IO uint32_t clkint;
        struct {
            __IO uint32_t lickstblf            : 1; /* [0] */
            __IO uint32_t lextstblf            : 1; /* [1] */
            __IO uint32_t hickstblf            : 1; /* [2] */
            __IO uint32_t hextstblf            : 1; /* [3] */
            __IO uint32_t pllstblf             : 1; /* [4] */
            __IO uint32_t reserved1            : 2; /* [6:5] */
            __IO uint32_t cfdf                 : 1; /* [7] */
            __IO uint32_t lickstblien          : 1; /* [8] */
            __IO uint32_t lextstblien          : 1; /* [9] */
            __IO uint32_t hickstblien          : 1; /* [10] */
            __IO uint32_t hextstblien          : 1; /* [11] */
            __IO uint32_t pllstblien           : 1; /* [12] */
            __IO uint32_t reserved2            : 3; /* [15:13] */
            __IO uint32_t lickstblfc           : 1; /* [16] */
            __IO uint32_t lextstblfc           : 1; /* [17] */
            __IO uint32_t hickstblfc           : 1; /* [18] */
            __IO uint32_t hextstblfc           : 1; /* [19] */
            __IO uint32_t pllstblfc            : 1; /* [20] */
            __IO uint32_t reserved3            : 2; /* [22:21] */
            __IO uint32_t cfdfc                : 1; /* [23] */
            __IO uint32_t reserved4            : 8; /* [31:24] */
        } clkint_bit;
    };

    /**
      * @brief crm ahbrst1 register, offset:0x10
      */
    union {
        __IO uint32_t ahbrst1;
        #if defined (AT32F435xx)
        struct {
            __IO uint32_t gpioarst             : 1; /* [0] */
            __IO uint32_t gpiobrst             : 1; /* [1] */
            __IO uint32_t gpiocrst             : 1; /* [2] */
            __IO uint32_t gpiodrst             : 1; /* [3] */
            __IO uint32_t gpioerst             : 1; /* [4] */
            __IO uint32_t gpiofrst             : 1; /* [5] */
            __IO uint32_t gpiogrst             : 1; /* [6] */
            __IO uint32_t gpiohrst             : 1; /* [7] */
            __IO uint32_t reserved1            : 4; /* [11:8] */
            __IO uint32_t crcrst               : 1; /* [12] */
            __IO uint32_t reserved2            : 8; /* [20:13] */
            __IO uint32_t edmarst              : 1; /* [21] */
            __IO uint32_t dma1rst              : 1; /* [22] */
            __IO uint32_t reserved3            : 1; /* [23] */
            __IO uint32_t dma2rst              : 1; /* [24] */
            __IO uint32_t reserved4            : 4; /* [28:25] */
            __IO uint32_t otgfs2rst            : 1; /* [29] */
            __IO uint32_t reserved5            : 2; /* [31:30] */
        } ahbrst1_bit;
        #endif

        #if defined (AT32F437xx)
        struct {
            __IO uint32_t gpioarst             : 1; /* [0] */
            __IO uint32_t gpiobrst             : 1; /* [1] */
            __IO uint32_t gpiocrst             : 1; /* [2] */
            __IO uint32_t gpiodrst             : 1; /* [3] */
            __IO uint32_t gpioerst             : 1; /* [4] */
            __IO uint32_t gpiofrst             : 1; /* [5] */
            __IO uint32_t gpiogrst             : 1; /* [6] */
            __IO uint32_t gpiohrst             : 1; /* [7] */
            __IO uint32_t reserved1            : 4; /* [11:8] */
            __IO uint32_t crcrst               : 1; /* [12] */
            __IO uint32_t reserved2            : 8; /* [20:13] */
            __IO uint32_t edmarst              : 1; /* [21] */
            __IO uint32_t dma1rst              : 1; /* [22] */
            __IO uint32_t reserved3            : 1; /* [23] */
            __IO uint32_t dma2rst              : 1; /* [24] */
            __IO uint32_t emacrst              : 1; /* [25] */
            __IO uint32_t reserved4            : 3; /* [28:26] */
            __IO uint32_t otgfs2rst            : 1; /* [29] */
            __IO uint32_t reserved5            : 2; /* [31:30] */
        } ahbrst1_bit;
        #endif
    };

    /**
      * @brief crm ahbrst2 register, offset:0x14
      */
    union {
        __IO uint32_t ahbrst2;
        struct {
            __IO uint32_t dvprst               : 1; /* [0] */
            __IO uint32_t reserved1            : 6; /* [6:1] */
            __IO uint32_t otgfs1rst            : 1; /* [7] */
            __IO uint32_t reserved2            : 7; /* [14:8] */
            __IO uint32_t sdio1rst             : 1; /* [15] */
            __IO uint32_t reserved3            : 16;/* [31:16] */
        } ahbrst2_bit;
    };

    /**
      * @brief crm ahbrst3 register, offset:0x18
      */
    union {
        __IO uint32_t ahbrst3;
        struct {
            __IO uint32_t xmcrst               : 1; /* [0] */
            __IO uint32_t qspi1rst             : 1; /* [1] */
            __IO uint32_t reserved1            : 12;/* [13:2] */
            __IO uint32_t qspi2rst             : 1; /* [14] */
            __IO uint32_t sdio2rst             : 1; /* [15] */
            __IO uint32_t reserved3            : 16;/* [31:16] */
        } ahbrst3_bit;
    };

    /**
      * @brief crm reserved1 register, offset:0x1C
      */
    __IO uint32_t reserved1;

    /**
      * @brief crm apb1rst register, offset:0x20
      */
    union {
        __IO uint32_t apb1rst;
        struct {
            __IO uint32_t tmr2rst              : 1; /* [0] */
            __IO uint32_t tmr3rst              : 1; /* [1] */
            __IO uint32_t tmr4rst              : 1; /* [2] */
            __IO uint32_t tmr5rst              : 1; /* [3] */
            __IO uint32_t tmr6rst              : 1; /* [4] */
            __IO uint32_t tmr7rst              : 1; /* [5] */
            __IO uint32_t tmr12rst             : 1; /* [6] */
            __IO uint32_t tmr13rst             : 1; /* [7] */
            __IO uint32_t adc14rst             : 1; /* [8] */
            __IO uint32_t reserved1            : 2; /* [10:9] */
            __IO uint32_t wwdtrst              : 1; /* [11] */
            __IO uint32_t reserved2            : 2; /* [13:12] */
            __IO uint32_t spi2rst              : 1; /* [14] */
            __IO uint32_t spi3rst              : 1; /* [15] */
            __IO uint32_t reserved3            : 1; /* [16] */
            __IO uint32_t usart2rst            : 1; /* [17] */
            __IO uint32_t usart3rst            : 1; /* [18] */
            __IO uint32_t uart4rst             : 1; /* [19] */
            __IO uint32_t uart5rst             : 1; /* [20] */
            __IO uint32_t i2c1rst              : 1; /* [21] */
            __IO uint32_t i2c2rst              : 1; /* [22] */
            __IO uint32_t i2c3rst              : 1; /* [23] */
            __IO uint32_t reserved4            : 1; /* [24] */
            __IO uint32_t can1rst              : 1; /* [25] */
            __IO uint32_t can2rst              : 1; /* [26] */
            __IO uint32_t reserved5            : 1; /* [27] */
            __IO uint32_t pwcrst               : 1; /* [28] */
            __IO uint32_t dacrst               : 1; /* [29] */
            __IO uint32_t uart7rst             : 1; /* [30] */
            __IO uint32_t uart8rst             : 1; /* [31] */
        } apb1rst_bit;
    };

    /**
      * @brief crm apb2rst register, offset:0x24
      */
    union {
        __IO uint32_t apb2rst;
        struct {
            __IO uint32_t tmr1rst              : 1; /* [0] */
            __IO uint32_t tmr8rst              : 1; /* [1] */
            __IO uint32_t reserved1            : 2; /* [3:2] */
            __IO uint32_t usart1rst            : 1; /* [4] */
            __IO uint32_t usart6rst            : 1; /* [5] */
            __IO uint32_t reserved2            : 2; /* [7:6] */
            __IO uint32_t adcrst               : 1; /* [8] */
            __IO uint32_t reserved3            : 3; /* [11:9] */
            __IO uint32_t spi1rst              : 1; /* [12] */
            __IO uint32_t spi4rst              : 1; /* [13] */
            __IO uint32_t scfgrst              : 1; /* [14] */
            __IO uint32_t reserved4            : 1; /* [15] */
            __IO uint32_t tmr9rst              : 1; /* [16] */
            __IO uint32_t tmr10rst             : 1; /* [17] */
            __IO uint32_t tmr11rst             : 1; /* [18] */
            __IO uint32_t reserved5            : 1; /* [19] */
            __IO uint32_t tmr20rst             : 1; /* [20] */
            __IO uint32_t reserved6            : 8; /* [28:21] */
            __IO uint32_t accrst               : 1; /* [29] */
            __IO uint32_t reserved7            : 2; /* [31:30] */
        } apb2rst_bit;
    };

    /**
      * @brief crm reserved2 register, offset:0x28~0x2C
      */
    __IO uint32_t reserved2[2];

    /**
      * @brief crm ahben1 register, offset:0x30
      */
    union {
        __IO uint32_t ahben1;
        #if defined (AT32F435xx)
        struct {
            __IO uint32_t gpioaen              : 1; /* [0] */
            __IO uint32_t gpioben              : 1; /* [1] */
            __IO uint32_t gpiocen              : 1; /* [2] */
            __IO uint32_t gpioden              : 1; /* [3] */
            __IO uint32_t gpioeen              : 1; /* [4] */
            __IO uint32_t gpiofen              : 1; /* [5] */
            __IO uint32_t gpiogen              : 1; /* [6] */
            __IO uint32_t gpiohen              : 1; /* [7] */
            __IO uint32_t reserved1            : 4; /* [11:8] */
            __IO uint32_t crcen                : 1; /* [12] */
            __IO uint32_t reserved2            : 8; /* [20:13] */
            __IO uint32_t edmaen               : 1; /* [21] */
            __IO uint32_t dma1en               : 1; /* [22] */
            __IO uint32_t reserved3            : 1; /* [23] */
            __IO uint32_t dma2en               : 1; /* [24] */
            __IO uint32_t reserved4            : 4; /* [28:25] */
            __IO uint32_t otgfs2en             : 1; /* [29] */
            __IO uint32_t reserved5            : 2; /* [31:30] */
        } ahben1_bit;
        #endif

        #if defined (AT32F437xx)
        struct {
            __IO uint32_t gpioaen              : 1; /* [0] */
            __IO uint32_t gpioben              : 1; /* [1] */
            __IO uint32_t gpiocen              : 1; /* [2] */
            __IO uint32_t gpioden              : 1; /* [3] */
            __IO uint32_t gpioeen              : 1; /* [4] */
            __IO uint32_t gpiofen              : 1; /* [5] */
            __IO uint32_t gpiogen              : 1; /* [6] */
            __IO uint32_t gpiohen              : 1; /* [7] */
            __IO uint32_t reserved1            : 4; /* [11:8] */
            __IO uint32_t crcen                : 1; /* [12] */
            __IO uint32_t reserved2            : 8; /* [20:13] */
            __IO uint32_t edmaen               : 1; /* [21] */
            __IO uint32_t dma1en               : 1; /* [22] */
            __IO uint32_t reserved3            : 1; /* [23] */
            __IO uint32_t dma2en               : 1; /* [24] */
            __IO uint32_t emacen               : 1; /* [25] */
            __IO uint32_t reserved4            : 3; /* [28:26] */
            __IO uint32_t otgfs2en             : 1; /* [29] */
            __IO uint32_t reserved5            : 2; /* [31:30] */
        } ahben1_bit;
        #endif
    };

    /**
      * @brief crm ahben2 register, offset:0x34
      */
    union {
        __IO uint32_t ahben2;
        struct {
            __IO uint32_t dvpen                : 1; /* [0] */
            __IO uint32_t reserved1            : 6; /* [6:1] */
            __IO uint32_t otgfs1en             : 1; /* [7] */
            __IO uint32_t reserved2            : 7; /* [14:8] */
            __IO uint32_t sdio1en              : 1; /* [15] */
            __IO uint32_t reserved3            : 16;/* [31:16] */
        } ahben2_bit;
    };

    /**
      * @brief crm ahben3 register, offset:0x38
      */
    union {
        __IO uint32_t ahben3;
        struct {
            __IO uint32_t xmcen                : 1; /* [0] */
            __IO uint32_t qspi1en              : 1; /* [1] */
            __IO uint32_t reserved1            : 12;/* [13:2] */
            __IO uint32_t qspi2en              : 1; /* [14] */
            __IO uint32_t sdio2en              : 1; /* [15] */
            __IO uint32_t reserved3            : 16;/* [31:16] */
        } ahben3_bit;
    };

    /**
      * @brief crm reserved3 register, offset:0x3C
      */
    __IO uint32_t reserved3;

    /**
      * @brief crm apb1en register, offset:0x40
      */
    union {
        __IO uint32_t apb1en;
        struct {
            __IO uint32_t tmr2en               : 1; /* [0] */
            __IO uint32_t tmr3en               : 1; /* [1] */
            __IO uint32_t tmr4en               : 1; /* [2] */
            __IO uint32_t tmr5en               : 1; /* [3] */
            __IO uint32_t tmr6en               : 1; /* [4] */
            __IO uint32_t tmr7en               : 1; /* [5] */
            __IO uint32_t tmr12en              : 1; /* [6] */
            __IO uint32_t tmr13en              : 1; /* [7] */
            __IO uint32_t adc14en              : 1; /* [8] */
            __IO uint32_t reserved1            : 2; /* [10:9] */
            __IO uint32_t wwdten               : 1; /* [11] */
            __IO uint32_t reserved2            : 2; /* [13:12] */
            __IO uint32_t spi2en               : 1; /* [14] */
            __IO uint32_t spi3en               : 1; /* [15] */
            __IO uint32_t reserved3            : 1; /* [16] */
            __IO uint32_t usart2en             : 1; /* [17] */
            __IO uint32_t usart3en             : 1; /* [18] */
            __IO uint32_t uart4en              : 1; /* [19] */
            __IO uint32_t uart5en              : 1; /* [20] */
            __IO uint32_t i2c1en               : 1; /* [21] */
            __IO uint32_t i2c2en               : 1; /* [22] */
            __IO uint32_t i2c3en               : 1; /* [23] */
            __IO uint32_t reserved4            : 1; /* [24] */
            __IO uint32_t can1en               : 1; /* [25] */
            __IO uint32_t can2en               : 1; /* [26] */
            __IO uint32_t reserved5            : 1; /* [27] */
            __IO uint32_t pwcen                : 1; /* [28] */
            __IO uint32_t dacen                : 1; /* [29] */
            __IO uint32_t uart7en              : 1; /* [30] */
            __IO uint32_t uart8en              : 1; /* [31] */
        } apb1en_bit;
    };

    /**
      * @brief crm apb2en register, offset:0x44
      */
    union {
        __IO uint32_t apb2en;
        struct {
            __IO uint32_t tmr1en               : 1; /* [0] */
            __IO uint32_t tmr8en               : 1; /* [1] */
            __IO uint32_t reserved1            : 2; /* [3:2] */
            __IO uint32_t usart1en             : 1; /* [4] */
            __IO uint32_t usart6en             : 1; /* [5] */
            __IO uint32_t reserved2            : 2; /* [7:6] */
            __IO uint32_t adcen                : 1; /* [8] */
            __IO uint32_t reserved3            : 3; /* [11:9] */
            __IO uint32_t spi1en               : 1; /* [12] */
            __IO uint32_t spi4en               : 1; /* [13] */
            __IO uint32_t scfgen               : 1; /* [14] */
            __IO uint32_t reserved4            : 1; /* [15] */
            __IO uint32_t tmr9en               : 1; /* [16] */
            __IO uint32_t tmr10en              : 1; /* [17] */
            __IO uint32_t tmr11en              : 1; /* [18] */
            __IO uint32_t reserved5            : 1; /* [19] */
            __IO uint32_t tmr20en              : 1; /* [20] */
            __IO uint32_t reserved6            : 8; /* [28:21] */
            __IO uint32_t accen                : 1; /* [29] */
            __IO uint32_t reserved7            : 2; /* [31:30] */
        } apb2en_bit;
    };

    /**
      * @brief crm reserved4 register, offset:0x48~0x4C
      */
    __IO uint32_t reserved4[2];

    /**
      * @brief crm ahblpen1 register, offset:0x50
      */
    union {
        __IO uint32_t ahblpen1;
        #if defined (AT32F435xx)
        struct {
            __IO uint32_t gpioalpen            : 1; /* [0] */
            __IO uint32_t gpioblpen            : 1; /* [1] */
            __IO uint32_t gpioclpen            : 1; /* [2] */
            __IO uint32_t gpiodlpen            : 1; /* [3] */
            __IO uint32_t gpioelpen            : 1; /* [4] */
            __IO uint32_t gpioflpen            : 1; /* [5] */
            __IO uint32_t gpioglpen            : 1; /* [6] */
            __IO uint32_t gpiohlpen            : 1; /* [7] */
            __IO uint32_t reserved1            : 4; /* [11:8] */
            __IO uint32_t crclpen              : 1; /* [12] */
            __IO uint32_t reserved2            : 8; /* [20:13] */
            __IO uint32_t edmalpen             : 1; /* [21] */
            __IO uint32_t dma1lpen             : 1; /* [22] */
            __IO uint32_t reserved3            : 1; /* [23] */
            __IO uint32_t dma2lpen             : 1; /* [24] */
            __IO uint32_t reserved4            : 4; /* [28:25] */
            __IO uint32_t otgfs2lpen           : 1; /* [29] */
            __IO uint32_t reserved5            : 2; /* [31:30] */
        } ahblpen1_bit;
        #endif

        #if defined (AT32F437xx)
        struct {
            __IO uint32_t gpioalpen            : 1; /* [0] */
            __IO uint32_t gpioblpen            : 1; /* [1] */
            __IO uint32_t gpioclpen            : 1; /* [2] */
            __IO uint32_t gpiodlpen            : 1; /* [3] */
            __IO uint32_t gpioelpen            : 1; /* [4] */
            __IO uint32_t gpioflpen            : 1; /* [5] */
            __IO uint32_t gpioglpen            : 1; /* [6] */
            __IO uint32_t gpiohlpen            : 1; /* [7] */
            __IO uint32_t reserved1            : 4; /* [11:8] */
            __IO uint32_t crclpen              : 1; /* [12] */
            __IO uint32_t reserved2            : 8; /* [20:13] */
            __IO uint32_t edmalpen             : 1; /* [21] */
            __IO uint32_t dma1lpen             : 1; /* [22] */
            __IO uint32_t reserved3            : 1; /* [23] */
            __IO uint32_t dma2lpen             : 1; /* [24] */
            __IO uint32_t emaclpen             : 1; /* [25] */
            __IO uint32_t reserved4            : 3; /* [28:26] */
            __IO uint32_t otgfs2lpen           : 1; /* [29] */
            __IO uint32_t reserved5            : 2; /* [31:30] */
        } ahblpen1_bit;
        #endif
    };

    /**
      * @brief crm ahblpen2 register, offset:0x54
      */
    union {
        __IO uint32_t ahblpen2;
        struct {
            __IO uint32_t dvplpen              : 1; /* [0] */
            __IO uint32_t reserved1            : 6; /* [6:1] */
            __IO uint32_t otgfs1lpen           : 1; /* [7] */
            __IO uint32_t reserved2            : 7; /* [14:8] */
            __IO uint32_t sdio1lpen            : 1; /* [15] */
            __IO uint32_t reserved3            : 16;/* [31:16] */
        } ahblpen2_bit;
    };

    /**
      * @brief crm ahblpen3 register, offset:0x58
      */
    union {
        __IO uint32_t ahblpen3;
        struct {
            __IO uint32_t xmclpen              : 1; /* [0] */
            __IO uint32_t qspi1lpen            : 1; /* [1] */
            __IO uint32_t reserved1            : 12;/* [13:2] */
            __IO uint32_t qspi2lpen            : 1; /* [14] */
            __IO uint32_t sdio2lpen            : 1; /* [15] */
            __IO uint32_t reserved3            : 16;/* [31:16] */
        } ahblpen3_bit;
    };

    /**
      * @brief crm reserved5 register, offset:0x5C
      */
    __IO uint32_t reserved5;

    /**
      * @brief crm apb1lpen register, offset:0x60
      */
    union {
        __IO uint32_t apb1lpen;
        struct {
            __IO uint32_t tmr2lpen             : 1; /* [0] */
            __IO uint32_t tmr3lpen             : 1; /* [1] */
            __IO uint32_t tmr4lpen             : 1; /* [2] */
            __IO uint32_t tmr5lpen             : 1; /* [3] */
            __IO uint32_t tmr6lpen             : 1; /* [4] */
            __IO uint32_t tmr7lpen             : 1; /* [5] */
            __IO uint32_t tmr12lpen            : 1; /* [6] */
            __IO uint32_t tmr13lpen            : 1; /* [7] */
            __IO uint32_t adc14lpen            : 1; /* [8] */
            __IO uint32_t reserved1            : 2; /* [10:9] */
            __IO uint32_t wwdtlpen             : 1; /* [11] */
            __IO uint32_t reserved2            : 2; /* [13:12] */
            __IO uint32_t spi2lpen             : 1; /* [14] */
            __IO uint32_t spi3lpen             : 1; /* [15] */
            __IO uint32_t reserved3            : 1; /* [16] */
            __IO uint32_t usart2lpen           : 1; /* [17] */
            __IO uint32_t usart3lpen           : 1; /* [18] */
            __IO uint32_t uart4lpen            : 1; /* [19] */
            __IO uint32_t uart5lpen            : 1; /* [20] */
            __IO uint32_t i2c1lpen             : 1; /* [21] */
            __IO uint32_t i2c2lpen             : 1; /* [22] */
            __IO uint32_t i2c3lpen             : 1; /* [23] */
            __IO uint32_t reserved4            : 1; /* [24] */
            __IO uint32_t can1lpen             : 1; /* [25] */
            __IO uint32_t can2lpen             : 1; /* [26] */
            __IO uint32_t reserved5            : 1; /* [27] */
            __IO uint32_t pwclpen              : 1; /* [28] */
            __IO uint32_t daclpen              : 1; /* [29] */
            __IO uint32_t uart7lpen            : 1; /* [30] */
            __IO uint32_t uart8lpen            : 1; /* [31] */
        } apb1lpen_bit;
    };

    /**
      * @brief crm apb2lpen register, offset:0x64
      */
    union {
        __IO uint32_t apb2lpen;
        struct {
            __IO uint32_t tmr1lpen             : 1; /* [0] */
            __IO uint32_t tmr8lpen             : 1; /* [1] */
            __IO uint32_t reserved1            : 2; /* [3:2] */
            __IO uint32_t usart1lpen           : 1; /* [4] */
            __IO uint32_t usart6lpen           : 1; /* [5] */
            __IO uint32_t reserved2            : 2; /* [7:6] */
            __IO uint32_t adclpen              : 1; /* [8] */
            __IO uint32_t reserved3            : 3; /* [11:9] */
            __IO uint32_t spi1lpen             : 1; /* [12] */
            __IO uint32_t spi4lpen             : 1; /* [13] */
            __IO uint32_t scfglpen             : 1; /* [14] */
            __IO uint32_t reserved4            : 1; /* [15] */
            __IO uint32_t tmr9lpen             : 1; /* [16] */
            __IO uint32_t tmr10lpen            : 1; /* [17] */
            __IO uint32_t tmr11lpen            : 1; /* [18] */
            __IO uint32_t reserved5            : 1; /* [19] */
            __IO uint32_t tmr20lpen            : 1; /* [20] */
            __IO uint32_t reserved6            : 8; /* [28:21] */
            __IO uint32_t acclpen              : 1; /* [29] */
            __IO uint32_t reserved7            : 2; /* [31:30] */
        } apb2lpen_bit;
    };

    /**
      * @brief crm reserved6 register, offset:0x68~0x6C
      */
    __IO uint32_t reserved6[2];

    /**
      * @brief crm bpdc register, offset:0x70
      */
    union {
        __IO uint32_t bpdc;
        struct {
            __IO uint32_t lexten               : 1; /* [0] */
            __IO uint32_t lextstbl             : 1; /* [1] */
            __IO uint32_t lextbyps             : 1; /* [2] */
            __IO uint32_t reserved1            : 5; /* [7:3] */
            __IO uint32_t ertcsel              : 2; /* [9:8] */
            __IO uint32_t reserved2            : 5; /* [14:10] */
            __IO uint32_t ertcen               : 1; /* [15] */
            __IO uint32_t bpdrst               : 1; /* [16] */
            __IO uint32_t reserved3            : 15;/* [31:17] */
        } bpdc_bit;
    };

    /**
      * @brief crm ctrlsts register, offset:0x74
      */
    union {
        __IO uint32_t ctrlsts;
        struct {
            __IO uint32_t licken               : 1; /* [0] */
            __IO uint32_t lickstbl             : 1; /* [1] */
            __IO uint32_t reserved1            : 22;/* [23:2] */
            __IO uint32_t rstfc                : 1; /* [24] */
            __IO uint32_t reserved2            : 1; /* [25] */
            __IO uint32_t nrstf                : 1; /* [26] */
            __IO uint32_t porrstf              : 1; /* [27] */
            __IO uint32_t swrstf               : 1; /* [28] */
            __IO uint32_t wdtrstf              : 1; /* [29] */
            __IO uint32_t wwdtrstf             : 1; /* [30] */
            __IO uint32_t lprstf               : 1; /* [31] */
        } ctrlsts_bit;
    };

    /**
      * @brief crm reserved7 register, offset:0x78~0x9C
      */
    __IO uint32_t reserved7[10];

    /**
      * @brief crm misc1 register, offset:0xA0
      */
    union {
        __IO uint32_t misc1;
        struct {
            __IO uint32_t hickcal_key          : 8; /* [7:0] */
            __IO uint32_t reserved1            : 4; /* [11:8] */
            __IO uint32_t hickdiv              : 1; /* [12] */
            __IO uint32_t hick_To_usb          : 1; /* [13] */
            __IO uint32_t hick_To_sclk         : 1; /* [14] */
            __IO uint32_t reserved2            : 1; /* [15] */
            __IO uint32_t clkout2_sel2         : 4; /* [19:16] */
            __IO uint32_t reserved3            : 4; /* [23:20] */
            __IO uint32_t clkout1div2          : 4; /* [27:24] */
            __IO uint32_t clkout2div2          : 4; /* [31:28] */
        } misc1_bit;
    };

    /**
      * @brief crm misc2 register, offset:0xA4
      */
    union {
        __IO uint32_t misc2;
        struct {
            __IO uint32_t reserved1            : 4; /* [3:0] */
            __IO uint32_t auto_Step_en         : 2; /* [5:4] */
            __IO uint32_t reserved2            : 2; /* [7:6] */
            __IO uint32_t clk_To_tmr           : 1; /* [8] */
            __IO uint32_t EMAC_PPS_sel         : 1; /* [9] */
            __IO uint32_t reserved3            : 2; /* [11:10] */
            __IO uint32_t usbdiv               : 4; /* [15:12] */
            __IO uint32_t reserved4            : 16;/* [31:16] */
        } misc2_bit;
    };

} CRM_Type;
#define CRM                              ((CRM_Type *) CRM_BASE)

/** @defgroup CRM_exported_functions
  */
void CRM_Reset(void);
void CRM_Lext_ByPass(confirm_state new_state);
void CRM_Hext_ByPass(confirm_state new_state);
flag_status CRM_Flag_Get(uint32_t flag);
error_status CRM_Hext_Stable_Wait(void);
void CRM_HICK_Clock_Trimming_Set(uint8_t trim_value);
void CRM_HICK_Clock_Calibration_Set(uint8_t cali_value);
void CRM_Periph_Clock_Enable(CRM_Periph_Clock_Type value, confirm_state new_state);
void CRM_Periph_Reset(CRM_Periph_Reset_Type value, confirm_state new_state);
void CRM_Periph_LowPower_Mode_Enable(CRM_Periph_Clock_LowPower_Type value, confirm_state new_state);
void CRM_Clock_Source_Enable(CRM_Clock_Source_Type source, confirm_state new_state);
void CRM_Flag_Clear(uint32_t flag);
void CRM_ERTC_Clock_Select(CRM_ERTC_Clock_Type value);
void CRM_ERTC_Clock_Enable(confirm_state new_state);
void CRM_AHB_Div_Set(CRM_AHB_Div_Type value);
void CRM_APB1_Div_Set(CRM_APB1_Div_Type value);
void CRM_APB2_Div_Set(CRM_APB2_Div_Type value);
void CRM_USB_Clock_Div_Set(CRM_USB_Div_Type value);
void CRM_Clock_Failure_Detection_Enable(confirm_state new_state);
void CRM_Battery_Powered_Domain_Reset(confirm_state new_state);
void CRM_Auto_Step_Mode_Enable(confirm_state new_state);
void CRM_HICK_Divider_Select(CRM_HICK_Div_6_Type value);
void CRM_HICK_SCLK_Frequency_Select(CRM_HICK_SCLK_Frequency_Type value);
void CRM_USB_Clock_Source_Select(CRM_USB_Clock_Source_Type value);
void CRM_CLKout_To_TMR10_Enable(confirm_state new_state);
void CRM_PLL_Config(CRM_PLL_Clock_Source_Type clock_source, uint16_t pll_ns, \
                    uint16_t pll_ms, CRM_PLL_FR_Type pll_fr);
void CRM_SysCLK_Switch(CRM_SCLK_Type value);
CRM_SCLK_Type CRM_SysCLK_Switch_Status_Get(void);
void CRM_Clocks_Freq_Get(CRM_Clocks_Freq_Type *clocks_struct);
void CRM_Clock_Out1_Set(CRM_CLKout1_Select_Type clkout);
void CRM_Clock_Out2_Set(CRM_CLKout2_Select_Type clkout);
void CRM_CLKout_Div_Set(CRM_CLKout_index_Type index, CRM_CLKout_div1_Type div1, CRM_CLKout_Div2_Type div2);
void CRM_EMAC_OutPut_Pulse_Set(CRM_EMAC_OutPut_Pulse_Type width);
void CRM_Interrupt_Enable(uint32_t CRM_int, confirm_state new_state);
error_status CRM_PLL_Parameter_Calculate(CRM_PLL_Clock_Source_Type pll_rcs, uint32_t target_SCLK_freq, \
        uint16_t *ret_ms, uint16_t *ret_ns, uint16_t *ret_fr);

#ifdef __cplusplus
}
#endif

#endif
