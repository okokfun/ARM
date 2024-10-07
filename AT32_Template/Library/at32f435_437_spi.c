/**
  **************************************************************************
  * @file     at32f435_437_spi.c
  * @brief    contains all the functions for the spi firmware library
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

#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @defgroup SPI
  * @brief SPI driver modules
  */

#ifdef SPI_MODULE_EnableD

/** @defgroup SPI_private_functions
  */

/**
  * @brief  spi reset by crm reset register
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @retval 无
  */
void SPI_I2S_Reset(SPI_Type *SPI_x) {
    if(SPI_x == SPI1) {
        CRM_Periph_Reset(CRM_SPI1_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_SPI1_Periph_Reset, FALSE);
    } else if(SPI_x == SPI2) {
        CRM_Periph_Reset(CRM_SPI2_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_SPI2_Periph_Reset, FALSE);
    } else if(SPI_x == SPI3) {
        CRM_Periph_Reset(CRM_SPI3_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_SPI3_Periph_Reset, FALSE);
    } else if(SPI_x == SPI4) {
        CRM_Periph_Reset(CRM_SPI4_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_SPI4_Periph_Reset, FALSE);
    }
}

/**
  * @brief  spi init config with its default value.
  * @param  SPI_Init_struct : pointer to a SPI_Init_Type structure which will
  *         be initialized.
  * @retval 无
  */
void SPI_Default_Para_Init(SPI_Init_Type* SPI_Init_struct) {
    SPI_Init_struct->transmission_Mode = SPI_Transmit_FULL_DUPLEX;
    SPI_Init_struct->master_Slave_Mode = SPI_Mode_SLAVE;
    SPI_Init_struct->mclk_Freq_division = SPI_MCLK_Div_2;
    SPI_Init_struct->first_Bit_transmission = SPI_FIRST_Bit_MSB;
    SPI_Init_struct->frame_Bit_Num = SPI_Frame_8BIT;
    SPI_Init_struct->clock_polarity = SPI_Clock_Polarity_LOW;
    SPI_Init_struct->clock_phase = SPI_Clock_PHASE_1EDGE;
    SPI_Init_struct->cs_Mode_Selection = SPI_CS_Software_Mode;
}

/**
  * @brief  spi init config with its setting value.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  SPI_Init_struct : pointer to a SPI_Init_Type structure which will be initialized.
  * @retval 无
  */
void SPI_Init(SPI_Type* SPI_x, SPI_Init_Type* SPI_Init_struct) {
    SPI_x->i2sctrl_bit.i2smsel = FALSE;

    if(SPI_Init_struct->transmission_Mode == SPI_Transmit_FULL_DUPLEX) {
        SPI_x->ctrl1_bit.slben = FALSE;
        SPI_x->ctrl1_bit.slbtd = FALSE;
        SPI_x->ctrl1_bit.ora = FALSE;
    } else if(SPI_Init_struct->transmission_Mode == SPI_Transmit_SIMPLEX_RX) {
        SPI_x->ctrl1_bit.slben = FALSE;
        SPI_x->ctrl1_bit.slbtd = FALSE;
        SPI_x->ctrl1_bit.ora = TRUE;
    } else if(SPI_Init_struct->transmission_Mode == SPI_Transmit_Half_Duplex_RX) {
        SPI_x->ctrl1_bit.slben = TRUE;
        SPI_x->ctrl1_bit.slbtd = FALSE;
        SPI_x->ctrl1_bit.ora = FALSE;
    } else if(SPI_Init_struct->transmission_Mode == SPI_Transmit_Half_Duplex_TX) {
        SPI_x->ctrl1_bit.slben = TRUE;
        SPI_x->ctrl1_bit.slbtd = TRUE;
        SPI_x->ctrl1_bit.ora = FALSE;
    }

    SPI_x->ctrl1_bit.swcsen = SPI_Init_struct->cs_Mode_Selection;

    if((SPI_Init_struct->master_Slave_Mode == SPI_Mode_MASTER) && (SPI_Init_struct->cs_Mode_Selection == SPI_CS_Software_Mode)) {
        SPI_x->ctrl1_bit.swcsil = TRUE;
    } else {
        SPI_x->ctrl1_bit.swcsil = FALSE;
    }

    SPI_x->ctrl1_bit.msten = SPI_Init_struct->master_Slave_Mode;

    if(SPI_Init_struct->mclk_Freq_division <= SPI_MCLK_Div_256) {
        SPI_x->ctrl2_bit.mdiv3en = FALSE;
        SPI_x->ctrl2_bit.mdiv_h = FALSE;
        SPI_x->ctrl1_bit.mdiv_l = SPI_Init_struct->mclk_Freq_division;
    } else if(SPI_Init_struct->mclk_Freq_division == SPI_MCLK_Div_3) {
        SPI_x->ctrl2_bit.mdiv3en = TRUE;
        SPI_x->ctrl2_bit.mdiv_h = FALSE;
        SPI_x->ctrl1_bit.mdiv_l = 0;
    } else {
        SPI_x->ctrl2_bit.mdiv3en = FALSE;
        SPI_x->ctrl2_bit.mdiv_h = TRUE;
        SPI_x->ctrl1_bit.mdiv_l = SPI_Init_struct->mclk_Freq_division & 0x7;
    }

    SPI_x->ctrl1_bit.ltf = SPI_Init_struct->first_Bit_transmission;
    SPI_x->ctrl1_bit.fbn = SPI_Init_struct->frame_Bit_Num;
    SPI_x->ctrl1_bit.clkpol = SPI_Init_struct->clock_polarity;
    SPI_x->ctrl1_bit.clkpha = SPI_Init_struct->clock_phase;
}

/**
  * @brief  enable or disable the ti mode for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  new_state: new state of ti mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void SPI_Ti_Mode_Enable(SPI_Type* SPI_x, confirm_state new_state) {
    SPI_x->ctrl2_bit.tien = new_state;
}

/**
  * @brief  spi next transmit crc for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @retval 无
  */
void SPI_CRC_Next_Transmit(SPI_Type* SPI_x) {
    SPI_x->ctrl1_bit.ntc = TRUE;
}

/**
  * @brief  set the crc polynomial value for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  CRC_poly: crc polynomial value.
  * @retval 无
  */
void SPI_CRC_Polynomial_Set(SPI_Type* SPI_x, uint16_t CRC_poly) {
    SPI_x->cpoly_bit.cpoly = CRC_poly;
}

/**
  * @brief  return the crc polynomial register value for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @retval the select crc polynomial register value
  */
uint16_t SPI_CRC_Polynomial_Get(SPI_Type* SPI_x) {
    return SPI_x->cpoly_bit.cpoly;
}

/**
  * @brief  enable or disable the hardware crc calculation for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  new_state: new state of crc calculation.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void SPI_CRC_Enable(SPI_Type* SPI_x, confirm_state new_state) {
    SPI_x->ctrl1_bit.ccen = new_state;
}

/**
  * @brief  return the transmit or the receive crc value for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  CRC_direction: select transmit or receive crc value to be read
  *         - SPI_CRC_RX
  *         - SPI_CRC_TX
  * @retval the select crc register value
  */
uint16_t SPI_CRC_Value_Get(SPI_Type* SPI_x, SPI_CRC_Direction_Type CRC_direction) {
    if(CRC_direction == SPI_CRC_RX)
        return  SPI_x->rCRC_bit.rcrc;
    else
        return  SPI_x->tCRC_bit.tcrc;
}

/**
  * @brief  enable or disable the hardware cs output for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  new_state: new state of spi master cs output.
  *         该参数可以是: TRUE or FALSE.
  *         note:the bit only use in spi master mode
  * @retval 无
  */
void SPI_Hardware_CS_OutPut_Enable(SPI_Type* SPI_x, confirm_state new_state) {
    SPI_x->ctrl2_bit.hwcsoe = new_state;
}

/**
  * @brief  set the software cs internal level for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  level: set the state of spi cs level.
  *         该参数可以是以下值之一:
  *         - SPI_SWCS_Internal_LEVEL_LOW
  *         - SPI_SWCS_Internal_LEVEL_HIGHT
  *         note:the bit only use when swcsen bit is set.
  *         note:when use this bit,io operation on the cs pin are invalid.
  * @retval 无
  */
void SPI_Software_CS_Internal_level_Set(SPI_Type* SPI_x, SPI_Software_CS_level_Type level) {
    SPI_x->ctrl1_bit.swcsil = level;
}

/**
  * @brief  set the data frame bit num for the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  bit_Num: set the data frame size
  *         - SPI_Frame_8BIT
  *         - SPI_Frame_16BIT
  * @retval 无
  */
void SPI_Frame_Bit_Num_Set(SPI_Type* SPI_x, SPI_Frame_Bit_Num_Type bit_Num) {
    SPI_x->ctrl1_bit.fbn = bit_Num;
}

/**
  * @brief  set the data transmission direction in single line bidirectiona half duplex mode of the spi peripheral.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  direction: data transfer direction
  *         该参数可以是以下值之一:
  *         - SPI_Half_Duplex_Direction_RX
  *         - SPI_Half_Duplex_Direction_TX
  * @retval 无
  */
void SPI_Half_Duplex_Direction_Set(SPI_Type* SPI_x, SPI_Half_Duplex_Direction_Type direction) {
    SPI_x->ctrl1_bit.slbtd = direction;
}

/**
  * @brief  enable or disable spi.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4
  * @param  new_state: new state of spi.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void SPI_Enable(SPI_Type* SPI_x, confirm_state new_state) {
    SPI_x->ctrl1_bit.spien = new_state;
}

/**
  * @brief  i2s init config with its default value.
  * @param  I2S_Init_struct : pointer to a I2S_Init_Type structure which will
  *         be initialized.
  * @retval 无
  */
void I2S_Default_Para_Init(I2S_Init_Type* I2S_Init_struct) {
    I2S_Init_struct->operation_Mode = I2S_Mode_Slave_TX;
    I2S_Init_struct->audio_protocol = I2S_AUDIO_PROTOCOL_PHILLIPS;
    I2S_Init_struct->audio_sampling_freq = I2S_AUDIO_Frequency_DEFAULT;
    I2S_Init_struct->data_Channel_format = I2S_Data_16BIT_Channel_16BIT;
    I2S_Init_struct->clock_polarity = I2S_Clock_Polarity_LOW;
    I2S_Init_struct->mclk_OutPut_Enable = FALSE;
}

/**
  * @brief  i2s init config with its setting value.
  * @param  SPI_x: select the spi peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @param  I2S_Init_struct : pointer to a I2S_Init_Type structure which will be initialized.
  * @retval 无
  */
void I2S_Init(SPI_Type* SPI_x, I2S_Init_Type* I2S_Init_struct) {
    CRM_Clocks_Freq_Type clocks_freq;
    uint32_t I2S_SCLK_index = 0;
    uint32_t i2sdiv_index = 2, i2sodd_index = 0, frequency_index = 0;

    /* i2s audio frequency config */
    if(I2S_Init_struct->audio_sampling_freq == I2S_AUDIO_Frequency_DEFAULT) {
        i2sodd_index = 0;
        i2sdiv_index = 2;
    } else {
        CRM_Clocks_Freq_Get(&clocks_freq);
        I2S_SCLK_index = clocks_freq.sclk_freq;

        if((I2S_Init_struct->audio_protocol == I2S_AUDIO_PROTOCOL_PCM_SHORT) || (I2S_Init_struct->audio_protocol == I2S_AUDIO_PROTOCOL_PCM_LONG)) {
            if(I2S_Init_struct->mclk_OutPut_Enable == TRUE) {
                frequency_index = (((I2S_SCLK_index / 128) * 10) / I2S_Init_struct->audio_sampling_freq) + 5;
            } else {
                if(I2S_Init_struct->data_Channel_format == I2S_Data_16BIT_Channel_16BIT)
                    frequency_index = (((I2S_SCLK_index / 16) * 10) / I2S_Init_struct->audio_sampling_freq) + 5;
                else
                    frequency_index = (((I2S_SCLK_index / 32) * 10) / I2S_Init_struct->audio_sampling_freq) + 5;
            }
        } else {
            if(I2S_Init_struct->mclk_OutPut_Enable == TRUE) {
                frequency_index = (((I2S_SCLK_index / 256) * 10) / I2S_Init_struct->audio_sampling_freq) + 5;
            } else {
                if(I2S_Init_struct->data_Channel_format == I2S_Data_16BIT_Channel_16BIT)
                    frequency_index = (((I2S_SCLK_index / 32) * 10) / I2S_Init_struct->audio_sampling_freq) + 5;
                else
                    frequency_index = (((I2S_SCLK_index / 64) * 10) / I2S_Init_struct->audio_sampling_freq) + 5;
            }
        }
    }

    frequency_index = frequency_index / 10;
    i2sodd_index = frequency_index & (uint16_t)0x0001;
    i2sdiv_index = (frequency_index - i2sodd_index) / 2;

    if((i2sdiv_index < 2) || (i2sdiv_index > 0x03FF)) {
        i2sodd_index = 0;
        i2sdiv_index = 2;
    }

    SPI_x->i2sclk_bit.i2sodd = i2sodd_index;

    if(i2sdiv_index > 0x00FF) {
        SPI_x->i2sclk_bit.i2sdiv_h = (i2sdiv_index >> 8) & 0x0003;
        SPI_x->i2sclk_bit.i2sdiv_l = i2sdiv_index & 0x00FF;
    } else {
        SPI_x->i2sclk_bit.i2sdiv_h = 0;
        SPI_x->i2sclk_bit.i2sdiv_l = i2sdiv_index;
    }

    /* i2s audio_protocol set*/
    if(I2S_Init_struct->audio_protocol == I2S_AUDIO_PROTOCOL_PCM_LONG) {
        SPI_x->i2sctrl_bit.pcmfssel = 1;
        SPI_x->i2sctrl_bit.stdsel = 3;
    } else if(I2S_Init_struct->audio_protocol == I2S_AUDIO_PROTOCOL_PCM_SHORT) {
        SPI_x->i2sctrl_bit.pcmfssel = 0;
        SPI_x->i2sctrl_bit.stdsel = 3;
    } else if(I2S_Init_struct->audio_protocol == I2S_AUDIO_PROTOCOL_LSB) {
        SPI_x->i2sctrl_bit.pcmfssel = 0;
        SPI_x->i2sctrl_bit.stdsel = 2;
    } else if(I2S_Init_struct->audio_protocol == I2S_AUDIO_PROTOCOL_MSB) {
        SPI_x->i2sctrl_bit.pcmfssel = 0;
        SPI_x->i2sctrl_bit.stdsel = 1;
    } else if(I2S_Init_struct->audio_protocol == I2S_AUDIO_PROTOCOL_PHILLIPS) {
        SPI_x->i2sctrl_bit.pcmfssel = 0;
        SPI_x->i2sctrl_bit.stdsel = 0;
    }

    /* i2s data_Channel_format set*/
    if(I2S_Init_struct->data_Channel_format == I2S_Data_16BIT_Channel_16BIT) {
        SPI_x->i2sctrl_bit.i2scbn = 0;
        SPI_x->i2sctrl_bit.i2sdbn = 0;
    } else if(I2S_Init_struct->data_Channel_format == I2S_Data_16BIT_Channel_32BIT) {
        SPI_x->i2sctrl_bit.i2scbn = 1;
        SPI_x->i2sctrl_bit.i2sdbn = 0;
    } else if(I2S_Init_struct->data_Channel_format == I2S_Data_24BIT_Channel_32BIT) {
        SPI_x->i2sctrl_bit.i2scbn = 1;
        SPI_x->i2sctrl_bit.i2sdbn = 1;
    } else if(I2S_Init_struct->data_Channel_format == I2S_Data_32BIT_Channel_32BIT) {
        SPI_x->i2sctrl_bit.i2scbn = 1;
        SPI_x->i2sctrl_bit.i2sdbn = 2;
    }

    SPI_x->i2sctrl_bit.i2sclkpol = I2S_Init_struct->clock_polarity;
    SPI_x->i2sclk_bit.i2smclkoe = I2S_Init_struct->mclk_OutPut_Enable;
    SPI_x->i2sctrl_bit.opersel = I2S_Init_struct->operation_Mode;
    SPI_x->i2sctrl_bit.i2smsel = TRUE;
}

/**
  * @brief  enable or disable i2s.
  * @param  SPI_x: select the i2s peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @param  new_state: new state of i2s.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void I2S_Enable(SPI_Type* SPI_x, confirm_state new_state) {
    SPI_x->i2sctrl_bit.i2sen = new_state;
}

/**
  * @brief  enable or disable the specified spi/i2s interrupts.
  * @param  SPI_x: select the spi/i2s peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @param  SPI_I2S_int: 指定spi/i2s interrupt sources to be enabled or disabled.
  *         该参数可以是以下值之一:
  *         - SPI_I2S_Error_INT
  *         - SPI_I2S_RDBF_INT
  *         - SPI_I2S_TDBE_INT
  * @param  new_state: new state of the specified spi/i2s interrupts.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void SPI_I2S_Interrupt_Enable(SPI_Type* SPI_x, uint32_t SPI_I2S_int, confirm_state new_state) {
    if(new_state != FALSE) {
        SPI_x->ctrl2 |= SPI_I2S_int;
    } else {
        SPI_x->ctrl2 &= ~SPI_I2S_int;
    }
}

/**
  * @brief  enable or disable the spi/i2s dma transmitter mode.
  * @param  SPI_x: select the spi/i2s peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @param  new_state: new state of the dma request.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void SPI_I2S_DMATransmitter_Enable(SPI_Type* SPI_x, confirm_state new_state) {
    SPI_x->ctrl2_bit.dmaten = new_state;
}

/**
  * @brief  enable or disable the spi/i2s dma receiver mode.
  * @param  SPI_x: select the spi/i2s peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @param  new_state: new state of the dma request.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void SPI_I2S_DMA_Receiver_Enable(SPI_Type* SPI_x, confirm_state new_state) {
    SPI_x->ctrl2_bit.dmaren = new_state;
}

/**
  * @brief  spi/i2s data transmit
  * @param  SPI_x: select the spi/i2s peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @param  tx_data: the data to be transmit.
  *         该参数可以是:
  *         - (0x0000~0xFFFF)
  * @retval 无
  */
void SPI_I2S_Data_Transmit(SPI_Type* SPI_x, uint16_t tx_data) {
    SPI_x->dt = tx_data;
}

/**
  * @brief  spi/i2s data receive
  * @param  SPI_x: select the spi/i2s peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @retval the received data value
  */
uint16_t SPI_I2S_Data_Receive(SPI_Type* SPI_x) {
    return (uint16_t)SPI_x->dt;
}

/**
  * @brief  get flag of the specified spi/i2s peripheral.
  * @param  SPI_x: select the spi/i2s peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @param  SPI_I2S_flag: select the spi/i2s flag
  *         该参数可以是以下值之一:
  *         - SPI_I2S_RDBF_FLAG
  *         - SPI_I2S_TDBE_FLAG
  *         - I2S_ACS_FLAG    (this flag only use in i2s mode)
  *         - I2S_TUERR_FLAG  (this flag only use in i2s mode)
  *         - SPI_CCERR_FLAG  (this flag only use in spi mode)
  *         - SPI_MMERR_FLAG  (this flag only use in spi mode)
  *         - SPI_I2S_ROERR_FLAG
  *         - SPI_I2S_BF_FLAG
  *         - SPI_CSPAS_FLAG
  * @retval the new state of spi/i2s flag
  */
flag_status SPI_I2S_Flag_Get(SPI_Type* SPI_x, uint32_t SPI_I2S_flag) {
    flag_status status = RESET;

    if ((SPI_x->sts & SPI_I2S_flag) == RESET) {
        status = RESET;
    } else {
        status = SET;
    }

    return status;
}

/**
  * @brief  clear flag of the specified spi/i2s peripheral.
  * @param  SPI_x: select the spi/i2s peripheral.
  *         该参数可以是以下值之一:
  *         SPI1, SPI2, SPI3 ,SPI4 , I2S2EXT, I2S3EXT
  * @param  SPI_I2S_flag: select the spi/i2s flag
  *         该参数可以是以下值之一:
  *         - SPI_CCERR_FLAG
  *         - SPI_I2S_RDBF_FLAG
  *         - I2S_TUERR_FLAG
  *         - SPI_MMERR_FLAG
  *         - SPI_I2S_ROERR_FLAG
  *         - SPI_CSPAS_FLAG
  * @note
  *         SPI_I2S_TDBE_FLAG  this flag is cleared when the tx buffer already contain data to be transmit.
  *         I2S_ACS_FLAG       this flag cann't cleared by software,the flag indicate the channel side(not use in pcm standard mode).
  *         SPI_I2S_BF_FLAG    this flag cann't cleared by software, it's set and cleared by hardware.
  * @retval 无
  */
void SPI_I2S_Flag_Clear(SPI_Type* SPI_x, uint32_t SPI_I2S_flag) {
    if(SPI_I2S_flag == SPI_CCERR_FLAG)
        SPI_x->sts = ~SPI_CCERR_FLAG;
    else if(SPI_I2S_flag == SPI_I2S_RDBF_FLAG)
        UNUSED(SPI_x->dt);
    else if(SPI_I2S_flag == I2S_TUERR_FLAG)
        UNUSED(SPI_x->sts);
    else if(SPI_I2S_flag == SPI_CSPAS_FLAG)
        UNUSED(SPI_x->sts);
    else if(SPI_I2S_flag == SPI_MMERR_FLAG) {
        UNUSED(SPI_x->sts);
        SPI_x->ctrl1 = SPI_x->ctrl1;
    } else if(SPI_I2S_flag == SPI_I2S_ROERR_FLAG) {
        UNUSED(SPI_x->dt);
        UNUSED(SPI_x->sts);
    }
}

#endif
