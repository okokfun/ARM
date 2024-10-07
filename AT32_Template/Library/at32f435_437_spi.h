/**
  **************************************************************************
  * @file     at32f435_437_spi.h
  * @brief    at32f435_437 spi header file
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
#ifndef __AT32F435_437_SPI_H
#define __AT32F435_437_SPI_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup SPI
  */

/**
  * @defgroup SPI_I2S_flags_definition
  * @brief spi i2s flag
  */
#define SPI_I2S_RDBF_FLAG                0x0001 /*!< spi or i2s receive data buffer full flag */
#define SPI_I2S_TDBE_FLAG                0x0002 /*!< spi or i2s transmit data buffer empty flag */
#define I2S_ACS_FLAG                     0x0004 /*!< i2s audio channel state flag */
#define I2S_TUERR_FLAG                   0x0008 /*!< i2s transmitter underload error flag */
#define SPI_CCERR_FLAG                   0x0010 /*!< spi crc calculation error flag */
#define SPI_MMERR_FLAG                   0x0020 /*!< spi master mode error flag */
#define SPI_I2S_ROERR_FLAG               0x0040 /*!< spi or i2s receiver overflow error flag */
#define SPI_I2S_BF_FLAG                  0x0080 /*!< spi or i2s busy flag */
#define SPI_CSPAS_FLAG                   0x0100 /*!< spi cs pulse abnormal setting fiag */

/**
  * @defgroup SPI_I2S_Interrupts_definition
  * @brief spi i2s interrupt
  */
#define SPI_I2S_Error_INT                0x0020 /*!< error 中断 */
#define SPI_I2S_RDBF_INT                 0x0040 /*!< receive data buffer full 中断 */
#define SPI_I2S_TDBE_INT                 0x0080 /*!< transmit data buffer empty 中断 */

/** @defgroup SPI_exported_Types
  */

/**
  * @brief spi frame bit num type
  */
typedef enum {
    SPI_Frame_8BIT                         = 0x00, /*!< 8-bit data frame format */
    SPI_Frame_16BIT                        = 0x01  /*!< 16-bit data frame format */
} SPI_Frame_Bit_Num_Type;

/**
  * @brief spi master/slave mode type
  */
typedef enum {
    SPI_Mode_SLAVE                         = 0x00, /*!< select as slave mode */
    SPI_Mode_MASTER                        = 0x01  /*!< select as master mode */
} SPI_Master_Slave_Mode_Type;

/**
  * @brief spi clock polarity (clkpol) type
  */
typedef enum {
    SPI_Clock_Polarity_LOW                 = 0x00, /*!< sck keeps low at idle state */
    SPI_Clock_Polarity_HIGH                = 0x01  /*!< sck keeps high at idle state */
} SPI_Clock_Polarity_Type;

/**
  * @brief spi clock phase (clkpha) type
  */
typedef enum {
    SPI_Clock_PHASE_1EDGE                  = 0x00, /*!< data capture start from the first clock edge */
    SPI_Clock_PHASE_2EDGE                  = 0x01  /*!< data capture start from the second clock edge */
} SPI_Clock_phase_Type;

/**
  * @brief spi cs mode type
  */
typedef enum {
    SPI_CS_Hardware_Mode                   = 0x00, /*!< cs is hardware mode */
    SPI_CS_Software_Mode                   = 0x01  /*!< cs is software mode */
} SPI_CS_Mode_Type;

/**
  * @brief spi master clock frequency division type
  */
typedef enum {
    SPI_MCLK_Div_2                         = 0x00, /*!< master clock frequency division 2 */
    SPI_MCLK_Div_3                         = 0x0A, /*!< master clock frequency division 3 */
    SPI_MCLK_Div_4                         = 0x01, /*!< master clock frequency division 4 */
    SPI_MCLK_Div_8                         = 0x02, /*!< master clock frequency division 8 */
    SPI_MCLK_Div_16                        = 0x03, /*!< master clock frequency division 16 */
    SPI_MCLK_Div_32                        = 0x04, /*!< master clock frequency division 32 */
    SPI_MCLK_Div_64                        = 0x05, /*!< master clock frequency division 64 */
    SPI_MCLK_Div_128                       = 0x06, /*!< master clock frequency division 128 */
    SPI_MCLK_Div_256                       = 0x07, /*!< master clock frequency division 256 */
    SPI_MCLK_Div_512                       = 0x08, /*!< master clock frequency division 512 */
    SPI_MCLK_Div_1024                      = 0x09  /*!< master clock frequency division 1024 */
} SPI_mclk_Freq_Div_Type;

/**
  * @brief spi transmit first bit (lsb/msb) type
  */
typedef enum {
    SPI_FIRST_Bit_MSB                      = 0x00, /*!< the frame format is msb first */
    SPI_FIRST_Bit_LSB                      = 0x01  /*!< the frame format is lsb first */
} SPI_first_Bit_Type;

/**
  * @brief spi transmission mode type
  */
typedef enum {
    SPI_Transmit_FULL_DUPLEX               = 0x00, /*!< dual line unidirectional full-duplex mode(slben = 0 and ora = 0) */
    SPI_Transmit_SIMPLEX_RX                = 0x01, /*!< dual line unidirectional simplex receive-only mode(slben = 0 and ora = 1) */
    SPI_Transmit_Half_Duplex_RX            = 0x02, /*!< single line bidirectional half duplex mode-receiving(slben = 1 and slbtd = 0) */
    SPI_Transmit_Half_Duplex_TX            = 0x03  /*!< single line bidirectional half duplex mode-transmitting(slben = 1 and slbtd = 1) */
} SPI_Transmission_Mode_Type;

/**
  * @brief spi crc direction type
  */
typedef enum {
    SPI_CRC_RX                             = 0x0014, /*!< crc direction is rx */
    SPI_CRC_TX                             = 0x0018  /*!< crc direction is tx */
} SPI_CRC_Direction_Type;

/**
  * @brief spi single line bidirectional direction type
  */
typedef enum {
    SPI_Half_Duplex_Direction_RX           = 0x00, /*!< single line bidirectional half duplex mode direction: receive(slbtd = 0) */
    SPI_Half_Duplex_Direction_TX           = 0x01  /*!< single line bidirectional half duplex mode direction: transmit(slbtd = 1) */
} SPI_Half_Duplex_Direction_Type;

/**
  * @brief spi software cs internal level type
  */
typedef enum {
    SPI_SWCS_Internal_LEVEL_LOW            = 0x00, /*!< internal level low */
    SPI_SWCS_Internal_LEVEL_HIGHT          = 0x01  /*!< internal level high */
} SPI_Software_CS_level_Type;

/**
  * @brief i2s audio protocol type
  */
typedef enum {
    I2S_AUDIO_PROTOCOL_PHILLIPS            = 0x00, /*!< i2s philip standard */
    I2S_AUDIO_PROTOCOL_MSB                 = 0x01, /*!< msb-justified standard */
    I2S_AUDIO_PROTOCOL_LSB                 = 0x02, /*!< lsb-justified standard */
    I2S_AUDIO_PROTOCOL_PCM_SHORT           = 0x03, /*!< pcm standard-short frame */
    I2S_AUDIO_PROTOCOL_PCM_LONG            = 0x04  /*!< pcm standard-long frame */
} I2S_audio_protocol_Type;

/**
  * @brief i2s audio frequency type
  */
typedef enum {
    I2S_AUDIO_Frequency_DEFAULT            = 2,     /*!< i2s audio sampling frequency default */
    I2S_AUDIO_Frequency_8K                 = 8000,  /*!< i2s audio sampling frequency 8k */
    I2S_AUDIO_Frequency_11_025K            = 11025, /*!< i2s audio sampling frequency 11.025k */
    I2S_AUDIO_Frequency_16K                = 16000, /*!< i2s audio sampling frequency 16k */
    I2S_AUDIO_Frequency_22_05K             = 22050, /*!< i2s audio sampling frequency 22.05k */
    I2S_AUDIO_Frequency_32K                = 32000, /*!< i2s audio sampling frequency 32k */
    I2S_AUDIO_Frequency_44_1K              = 44100, /*!< i2s audio sampling frequency 44.1k */
    I2S_AUDIO_Frequency_48K                = 48000, /*!< i2s audio sampling frequency 48k */
    I2S_AUDIO_Frequency_96K                = 96000, /*!< i2s audio sampling frequency 96k */
    I2S_AUDIO_Frequency_192K               = 192000 /*!< i2s audio sampling frequency 192k */
} I2S_audio_sampling_Freq_Type;

/**
  * @brief i2s data bit num and channel bit num type
  */
typedef enum {
    I2S_Data_16BIT_Channel_16BIT           = 0x01, /*!< 16-bit data packed in 16-bit channel frame */
    I2S_Data_16BIT_Channel_32BIT           = 0x02, /*!< 16-bit data packed in 32-bit channel frame */
    I2S_Data_24BIT_Channel_32BIT           = 0x03, /*!< 24-bit data packed in 32-bit channel frame */
    I2S_Data_32BIT_Channel_32BIT           = 0x04  /*!< 32-bit data packed in 32-bit channel frame */
} I2S_Data_Channel_Format_Type;

/**
  * @brief i2s operation mode type
  */
typedef enum {
    I2S_Mode_Slave_TX                      = 0x00, /*!< slave transmission mode */
    I2S_Mode_Slave_RX                      = 0x01, /*!< slave reception mode */
    I2S_Mode_Master_TX                     = 0x02, /*!< master transmission mode */
    I2S_Mode_Master_RX                     = 0x03  /*!< master reception mode */
} I2S_Operation_Mode_Type;

/**
  * @brief i2s clock polarity type
  */
typedef enum {
    I2S_Clock_Polarity_LOW                 = 0x00, /*!< i2s clock steady state is low level */
    I2S_Clock_Polarity_HIGH                = 0x01  /*!< i2s clock steady state is high level */
} I2S_Clock_Polarity_Type;

/**
  * @brief spi init type
  */
typedef struct {
    SPI_Transmission_Mode_Type             transmission_Mode;     /*!< transmission mode selection */
    SPI_Master_Slave_Mode_Type             master_Slave_Mode;     /*!< master or slave mode selection */
    SPI_mclk_Freq_Div_Type                 mclk_Freq_division;    /*!< master clock frequency division selection */
    SPI_first_Bit_Type                     first_Bit_transmission;/*!< transmit lsb or msb selection */
    SPI_Frame_Bit_Num_Type                 frame_Bit_Num;         /*!< frame bit num 8 or 16 bit selection */
    SPI_Clock_Polarity_Type                clock_polarity;        /*!< clock polarity selection */
    SPI_Clock_phase_Type                   clock_phase;           /*!< clock phase selection */
    SPI_CS_Mode_Type                       cs_Mode_Selection;     /*!< hardware or software cs mode selection */
} SPI_Init_Type;

/**
  * @brief i2s init type
  */
typedef struct {
    I2S_Operation_Mode_Type                operation_Mode;        /*!< operation mode selection */
    I2S_audio_protocol_Type                audio_protocol;        /*!< audio protocol selection */
    I2S_audio_sampling_Freq_Type           audio_sampling_freq;   /*!< audio frequency selection */
    I2S_Data_Channel_Format_Type           data_Channel_format;   /*!< data bit num and channel bit num selection */
    I2S_Clock_Polarity_Type                clock_polarity;        /*!< clock polarity selection */
    confirm_state                          mclk_OutPut_Enable;    /*!< mclk_Output selection */
} I2S_Init_Type;

/**
  * @brief type define spi register all
  */
typedef struct {

    /**
      * @brief spi ctrl1 register, offset:0x00
      */
    union {
        __IO uint32_t ctrl1;
        struct {
            __IO uint32_t clkpha               : 1; /* [0] */
            __IO uint32_t clkpol               : 1; /* [1] */
            __IO uint32_t msten                : 1; /* [2] */
            __IO uint32_t mdiv_l               : 3; /* [5:3] */
            __IO uint32_t spien                : 1; /* [6] */
            __IO uint32_t ltf                  : 1; /* [7] */
            __IO uint32_t swcsil               : 1; /* [8] */
            __IO uint32_t swcsen               : 1; /* [9] */
            __IO uint32_t ora                  : 1; /* [10] */
            __IO uint32_t fbn                  : 1; /* [11] */
            __IO uint32_t ntc                  : 1; /* [12] */
            __IO uint32_t ccen                 : 1; /* [13] */
            __IO uint32_t slbtd                : 1; /* [14] */
            __IO uint32_t slben                : 1; /* [15] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } ctrl1_bit;
    };

    /**
      * @brief spi ctrl2 register, offset:0x04
      */
    union {
        __IO uint32_t ctrl2;
        struct {
            __IO uint32_t dmaren               : 1; /* [0] */
            __IO uint32_t dmaten               : 1; /* [1] */
            __IO uint32_t hwcsoe               : 1; /* [2] */
            __IO uint32_t reserved1            : 1; /* [3] */
            __IO uint32_t tien                 : 1; /* [4] */
            __IO uint32_t errie                : 1; /* [5] */
            __IO uint32_t rdbfie               : 1; /* [6] */
            __IO uint32_t tdbeie               : 1; /* [7] */
            __IO uint32_t mdiv_h               : 1; /* [8] */
            __IO uint32_t mdiv3en              : 1; /* [9] */
            __IO uint32_t reserved2            : 22;/* [31:10] */
        } ctrl2_bit;
    };

    /**
      * @brief spi sts register, offset:0x08
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t rdbf                 : 1; /* [0] */
            __IO uint32_t tdbe                 : 1; /* [1] */
            __IO uint32_t acs                  : 1; /* [2] */
            __IO uint32_t tuerr                : 1; /* [3] */
            __IO uint32_t ccerr                : 1; /* [4] */
            __IO uint32_t mmerr                : 1; /* [5] */
            __IO uint32_t roerr                : 1; /* [6] */
            __IO uint32_t bf                   : 1; /* [7] */
            __IO uint32_t cspas                : 1; /* [8] */
            __IO uint32_t reserved1            : 23;/* [31:9] */
        } sts_bit;
    };

    /**
      * @brief spi dt register, offset:0x0C
      */
    union {
        __IO uint32_t dt;
        struct {
            __IO uint32_t dt                  : 16;/* [15:0] */
            __IO uint32_t reserved1           : 16;/* [31:16] */
        } dt_bit;
    };

    /**
      * @brief spi cpoly register, offset:0x10
      */
    union {
        __IO uint32_t cpoly;
        struct {
            __IO uint32_t cpoly               : 16;/* [15:0] */
            __IO uint32_t reserved1           : 16;/* [31:16] */
        } cpoly_bit;
    };

    /**
      * @brief spi rcrc register, offset:0x14
      */
    union {
        __IO uint32_t rcrc;
        struct {
            __IO uint32_t rcrc                : 16;/* [15:0] */
            __IO uint32_t reserved1           : 16;/* [31:16] */
        } rCRC_bit;
    };

    /**
      * @brief spi tcrc register, offset:0x18
      */
    union {
        __IO uint32_t tcrc;
        struct {
            __IO uint32_t tcrc                : 16;/* [15:0] */
            __IO uint32_t reserved1           : 16;/* [31:16] */
        } tCRC_bit;
    };

    /**
      * @brief spi i2sctrl register, offset:0x1C
      */
    union {
        __IO uint32_t i2sctrl;
        struct {
            __IO uint32_t i2scbn              : 1; /* [0] */
            __IO uint32_t i2sdbn              : 2; /* [2:1] */
            __IO uint32_t i2sclkpol           : 1; /* [3] */
            __IO uint32_t stdsel              : 2; /* [5:4] */
            __IO uint32_t reserved1           : 1; /* [6] */
            __IO uint32_t pcmfssel            : 1; /* [7] */
            __IO uint32_t opersel             : 2; /* [9:8] */
            __IO uint32_t i2sen               : 1; /* [10] */
            __IO uint32_t i2smsel             : 1; /* [11] */
            __IO uint32_t reserved2           : 20;/* [31:12] */
        } i2sctrl_bit;
    };

    /**
      * @brief spi i2sclk register, offset:0x20
      */
    union {
        __IO uint32_t i2sclk;
        struct {
            __IO uint32_t i2sdiv_l            : 8; /* [7:0] */
            __IO uint32_t i2sodd              : 1; /* [8] */
            __IO uint32_t i2smclkoe           : 1; /* [9] */
            __IO uint32_t i2sdiv_h            : 2; /* [11:10] */
            __IO uint32_t reserved1           : 20;/* [31:12] */
        } i2sclk_bit;
    };

} SPI_Type;
#define SPI1                            ((SPI_Type *) SPI1_BASE)
#define SPI2                            ((SPI_Type *) SPI2_BASE)
#define SPI3                            ((SPI_Type *) SPI3_BASE)
#define SPI4                            ((SPI_Type *) SPI4_BASE)
#define I2S2EXT                         ((SPI_Type *) I2S2EXT_BASE)
#define I2S3EXT                         ((SPI_Type *) I2S3EXT_BASE)

/** @defgroup SPI_exported_functions
  */
void SPI_I2S_Reset(SPI_Type *SPI_x);
void SPI_Default_Para_Init(SPI_Init_Type* SPI_Init_struct);
void SPI_Init(SPI_Type* SPI_x, SPI_Init_Type* SPI_Init_struct);
void SPI_Ti_Mode_Enable(SPI_Type* SPI_x, confirm_state new_state);
void SPI_CRC_Next_Transmit(SPI_Type* SPI_x);
void SPI_CRC_Polynomial_Set(SPI_Type* SPI_x, uint16_t CRC_poly);
uint16_t SPI_CRC_Polynomial_Get(SPI_Type* SPI_x);
void SPI_CRC_Enable(SPI_Type* SPI_x, confirm_state new_state);
uint16_t SPI_CRC_Value_Get(SPI_Type* SPI_x, SPI_CRC_Direction_Type CRC_direction);
void SPI_Hardware_CS_OutPut_Enable(SPI_Type* SPI_x, confirm_state new_state);
void SPI_Software_CS_Internal_level_Set(SPI_Type* SPI_x, SPI_Software_CS_level_Type level);
void SPI_Frame_Bit_Num_Set(SPI_Type* SPI_x, SPI_Frame_Bit_Num_Type bit_Num);
void SPI_Half_Duplex_Direction_Set(SPI_Type* SPI_x, SPI_Half_Duplex_Direction_Type direction);
void SPI_Enable(SPI_Type* SPI_x, confirm_state new_state);
void I2S_Default_Para_Init(I2S_Init_Type* I2S_Init_struct);
void I2S_Init(SPI_Type* SPI_x, I2S_Init_Type* I2S_Init_struct);
void I2S_Enable(SPI_Type* SPI_x, confirm_state new_state);
void SPI_I2S_Interrupt_Enable(SPI_Type* SPI_x, uint32_t SPI_I2S_int, confirm_state new_state);
void SPI_I2S_DMATransmitter_Enable(SPI_Type* SPI_x, confirm_state new_state);
void SPI_I2S_DMA_Receiver_Enable(SPI_Type* SPI_x, confirm_state new_state);
void SPI_I2S_Data_Transmit(SPI_Type* SPI_x, uint16_t tx_data);
uint16_t SPI_I2S_Data_Receive(SPI_Type* SPI_x);
flag_status SPI_I2S_Flag_Get(SPI_Type* SPI_x, uint32_t SPI_I2S_flag);
void SPI_I2S_Flag_Clear(SPI_Type* SPI_x, uint32_t SPI_I2S_flag);

#ifdef __cplusplus
}
#endif

#endif
