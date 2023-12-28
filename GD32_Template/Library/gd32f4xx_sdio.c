/*!
    文件:    gd32f4xx_sdio.c
    简介:   SDIO driver

    版本: 2016-08-15, V1.0.0, firmware for GD32F4xx
    版本: 2018-12-12, V2.0.1, firmware for GD32F4xx
    版本: 2020-09-30, V2.1.0, firmware for GD32F4xx
    版本: 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx_sdio.h"

/*!
    简介:    deinitialize the SDIO
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_DeInit(void) {
    RCU_Periph_Reset_Enable(RCU_SDIORST);
    RCU_Periph_Reset_Disable(RCU_SDIORST);
}

/*!
    简介:    configure the SDIO clock
    参数[输入]:  clock_edge: SDIO_CLK clock edge
                only one parameter can be selected which is shown as below:
      参数:        SDIO_SDIOCLKEDGE_RISING: select the rising edge of the SDIOCLK to generate SDIO_CLK
      参数:        SDIO_SDIOCLKEDGE_FALLING: select the falling edge of the SDIOCLK to generate SDIO_CLK
    参数[输入]:  clock_bypass: clock bypass
                only one parameter can be selected which is shown as below:
      参数:        SDIO_CLOCKBYPASS_ENABLE: clock bypass
      参数:        SDIO_CLOCKBYPASS_DISABLE: no bypass
    参数[输入]:  clock_powersave: SDIO_CLK clock dynamic switch on/off for power saving
                only one parameter can be selected which is shown as below:
      参数:        SDIO_CLOCKPWRSAVE_ENABLE: SDIO_CLK closed when bus is idle
      参数:        SDIO_CLOCKPWRSAVE_DISABLE: SDIO_CLK clock is always on
    参数[输入]:  clock_division: clock division, less than 512
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Clock_Config(uint32_t clock_edge, uint32_t clock_bypass, uint32_t clock_powersave, uint16_t clock_division) {
    uint32_t clock_Config = 0U;
    clock_Config = SDIO_CLKCTL;
    /* reset the CLKEDGE, CLKBYP, CLKPWRSAV, DIV */
    clock_Config &= ~(SDIO_CLKCTL_CLKEDGE | SDIO_CLKCTL_CLKBYP | SDIO_CLKCTL_CLKPWRSAV | SDIO_CLKCTL_DIV8 | SDIO_CLKCTL_DIV);

    /* if the clock division is greater or equal to 256, set the DIV[8] */
    if(clock_division >= 256U) {
        clock_Config |= SDIO_CLKCTL_DIV8;
        clock_division -= 256U;
    }

    /* configure the SDIO_CLKCTL 根据 the parameters */
    clock_Config |= (clock_edge | clock_bypass | clock_powersave | clock_division);
    SDIO_CLKCTL = clock_Config;
}

/*!
    简介:    enable hardware clock control
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Hardware_Clock_Enable(void) {
    SDIO_CLKCTL |= SDIO_CLKCTL_HWCLKEN;
}

/*!
    简介:    disable hardware clock control
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Hardware_Clock_Disable(void) {
    SDIO_CLKCTL &= ~SDIO_CLKCTL_HWCLKEN;
}

/*!
    简介:    set different SDIO card bus mode
    参数[输入]:  bus_mode: SDIO card bus mode
                only one parameter can be selected which is shown as below:
      参数:        SDIO_BUSMODE_1BIT: 1-bit SDIO card bus mode
      参数:        SDIO_BUSMODE_4BIT: 4-bit SDIO card bus mode
      参数:        SDIO_BUSMODE_8BIT: 8-bit SDIO card bus mode
    参数[输出]:  无
    返回值:      无
*/
void SDIO_bus_Mode_Set(uint32_t bus_mode) {
    /* reset the SDIO card bus mode bits and set 根据 bus_mode */
    SDIO_CLKCTL &= ~SDIO_CLKCTL_BUSMODE;
    SDIO_CLKCTL |= bus_mode;
}

/*!
    简介:    set the SDIO power state
    参数[输入]:  power_state: SDIO power state
                only one parameter can be selected which is shown as below:
      参数:        SDIO_Power_ON: SDIO power on
      参数:        SDIO_Power_OFF: SDIO power off
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Power_State_Set(uint32_t power_state) {
    SDIO_PWRCTL = power_state;
}

/*!
    简介:    get the SDIO power state
    参数[输入]:  无
    参数[输出]:  无
    返回值:     SDIO power state
      参数:        SDIO_Power_ON: SDIO power on
      参数:        SDIO_Power_OFF: SDIO power off
*/
uint32_t SDIO_Power_State_Get(void) {
    return SDIO_PWRCTL;
}

/*!
    简介:    enable SDIO_CLK clock output
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Clock_Enable(void) {
    SDIO_CLKCTL |= SDIO_CLKCTL_CLKEN;
}

/*!
    简介:    disable SDIO_CLK clock output
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Clock_Disable(void) {
    SDIO_CLKCTL &= ~SDIO_CLKCTL_CLKEN;
}

/*!
    简介:    configure the command and response
    参数[输入]:  cmd_index: command index, refer to the related specifications
    参数[输入]:  cmd_argument: command argument, refer to the related specifications
    参数[输入]:  response_type: response type
                only one parameter can be selected which is shown as below:
      参数:        SDIO_RESPONSETYPE_NO: no response
      参数:        SDIO_RESPONSETYPE_SHORT: short response
      参数:        SDIO_RESPONSETYPE_LONG: long response
    参数[输出]:  无
    返回值:      无
*/
void SDIO_command_response_Config(uint32_t cmd_index, uint32_t cmd_argument, uint32_t response_type) {
    uint32_t cmd_Config = 0U;
    /* disable the CSM */
    SDIO_CMDCTL &= ~SDIO_CMDCTL_CSMEN;
    /* reset the command index, command argument and response type */
    SDIO_CMDAGMT &= ~SDIO_CMDAGMT_CMDAGMT;
    SDIO_CMDAGMT = cmd_argument;
    cmd_Config = SDIO_CMDCTL;
    cmd_Config &= ~(SDIO_CMDCTL_CMDIDX | SDIO_CMDCTL_CMDRESP);
    /* configure SDIO_CMDCTL and SDIO_CMDAGMT 根据 the parameters */
    cmd_Config |= (cmd_index | response_type);
    SDIO_CMDCTL = cmd_Config;
}

/*!
    简介:    set the command state machine wait type
    参数[输入]:  wait_type: wait type
                only one parameter can be selected which is shown as below:
      参数:        SDIO_WaitTYPE_NO: not wait interrupt
      参数:        SDIO_WaitTYPE_INTERRUPT: wait interrupt
      参数:        SDIO_WaitTYPE_DATAEND: wait the end of data transfer
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Wait_type_Set(uint32_t wait_type) {
    /* reset INTWAIT and WAITDEND */
    SDIO_CMDCTL &= ~(SDIO_CMDCTL_INTWAIT | SDIO_CMDCTL_WaitDEND);
    /* set the wait type 根据 wait_type */
    SDIO_CMDCTL |= wait_type;
}

/*!
    简介:    enable the CSM(command state machine)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_csm_Enable(void) {
    SDIO_CMDCTL |= SDIO_CMDCTL_CSMEN;
}

/*!
    简介:    disable the CSM(command state machine)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_csm_Disable(void) {
    SDIO_CMDCTL &= ~SDIO_CMDCTL_CSMEN;
}

/*!
    简介:    get the last response command index
    参数[输入]:  无
    参数[输出]:  无
    返回值:     last response command index
*/
uint8_t SDIO_command_index_Get(void) {
    return (uint8_t)SDIO_RSPCMDIDX;
}

/*!
    简介:    get the response for the last received command
    参数[输入]:  SDIO_responsex: SDIO response
                only one parameter can be selected which is shown as below:
      参数:       SDIO_RESPONSE0: card response[31:0]/card response[127:96]
      参数:       SDIO_RESPONSE1: card response[95:64]
      参数:       SDIO_RESPONSE2: card response[63:32]
      参数:       SDIO_RESPONSE3: card response[31:1], plus bit 0
    参数[输出]:  无
    返回值:     response for the last received command
*/
uint32_t SDIO_response_Get(uint32_t SDIO_responsex) {
    uint32_t resp_content = 0U;

    switch(SDIO_responsex) {
    case SDIO_RESPONSE0:
        resp_content = SDIO_RESP0;
        break;

    case SDIO_RESPONSE1:
        resp_content = SDIO_RESP1;
        break;

    case SDIO_RESPONSE2:
        resp_content = SDIO_RESP2;
        break;

    case SDIO_RESPONSE3:
        resp_content = SDIO_RESP3;
        break;

    default:
        break;
    }

    return resp_content;
}

/*!
    简介:    configure the data timeout, data length and data block size
    参数[输入]:  data_timeout: data timeout period in card bus clock periods
    参数[输入]:  data_length: number of data bytes to be transferred
    参数[输入]:  data_blocksize: size of data block for block transfer
                only one parameter can be selected which is shown as below:
      参数:        SDIO_DATABLOCKSIZE_1BYTE: block size = 1 byte
      参数:        SDIO_DATABLOCKSIZE_2BYTES: block size = 2 bytes
      参数:        SDIO_DATABLOCKSIZE_4BYTES: block size = 4 bytes
      参数:        SDIO_DATABLOCKSIZE_8BYTES: block size = 8 bytes
      参数:        SDIO_DATABLOCKSIZE_16BYTES: block size = 16 bytes
      参数:        SDIO_DATABLOCKSIZE_32BYTES: block size = 32 bytes
      参数:        SDIO_DATABLOCKSIZE_64BYTES: block size = 64 bytes
      参数:        SDIO_DATABLOCKSIZE_128BYTES: block size = 128 bytes
      参数:        SDIO_DATABLOCKSIZE_256BYTES: block size = 256 bytes
      参数:        SDIO_DATABLOCKSIZE_512BYTES: block size = 512 bytes
      参数:        SDIO_DATABLOCKSIZE_1024BYTES: block size = 1024 bytes
      参数:        SDIO_DATABLOCKSIZE_2048BYTES: block size = 2048 bytes
      参数:        SDIO_DATABLOCKSIZE_4096BYTES: block size = 4096 bytes
      参数:        SDIO_DATABLOCKSIZE_8192BYTES: block size = 8192 bytes
      参数:        SDIO_DATABLOCKSIZE_16384BYTES: block size = 16384 bytes
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Data_Config(uint32_t data_timeout, uint32_t data_length, uint32_t data_blocksize) {
    /* reset data timeout, data length and data block size */
    SDIO_DATATO &= ~SDIO_DATATO_DATATO;
    SDIO_DATALEN &= ~SDIO_DATALEN_DATALEN;
    SDIO_DATACTL &= ~SDIO_DATACTL_BLKSZ;
    /* configure the related parameters of data */
    SDIO_DATATO = data_timeout;
    SDIO_DATALEN = data_length;
    SDIO_DATACTL |= data_blocksize;
}

/*!
    简介:    configure the data transfer mode and direction
    参数[输入]:  transfer_mode: mode of data transfer
                only one parameter can be selected which is shown as below:
      参数:       SDIO_TRANSMODE_BLOCK: block transfer
      参数:       SDIO_TRANSMODE_STREAM: stream transfer or SDIO multibyte transfer
    参数[输入]:  transfer_direction: data transfer direction, read or write
                only one parameter can be selected which is shown as below:
      参数:       SDIO_TRANSDIRECTION_TOCARD: write data to card
      参数:       SDIO_TRANSDIRECTION_TOSDIO: read data from card
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Data_Transfer_Config(uint32_t transfer_mode, uint32_t transfer_direction) {
    uint32_t data_trans = 0U;
    /* reset the data transfer mode, transfer direction and set 根据 the parameters */
    data_trans = SDIO_DATACTL;
    data_trans &= ~(SDIO_DATACTL_TRANSMOD | SDIO_DATACTL_DATADIR);
    data_trans |= (transfer_mode | transfer_direction);
    SDIO_DATACTL = data_trans;
}

/*!
    简介:    enable the DSM(data state machine) for data transfer
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_dsm_Enable(void) {
    SDIO_DATACTL |= SDIO_DATACTL_DATAEN;
}

/*!
    简介:    disable the DSM(data state machine)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_dsm_Disable(void) {
    SDIO_DATACTL &= ~SDIO_DATACTL_DATAEN;
}

/*!
    简介:    write data(one word) to the transmit FIFO
    参数[输入]:  data: 32-bit data write to card
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Data_Write(uint32_t data) {
    SDIO_FIFO = data;
}

/*!
    简介:    read data(one word) from the receive FIFO
    参数[输入]:  无
    参数[输出]:  无
    返回值:     received data
*/
uint32_t SDIO_Data_Read(void) {
    return SDIO_FIFO;
}

/*!
    简介:    get the number of remaining data bytes to be transferred to card
    参数[输入]:  无
    参数[输出]:  无
    返回值:     number of remaining data bytes to be transferred
*/
uint32_t SDIO_Data_Counter_Get(void) {
    return SDIO_DATACNT;
}

/*!
    简介:    get the number of words remaining to be written or read from FIFO
    参数[输入]:  无
    参数[输出]:  无
    返回值:     remaining number of words
*/
uint32_t SDIO_FIFO_Counter_Get(void) {
    return SDIO_FIFOCNT;
}

/*!
    简介:    enable the DMA request for SDIO
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_DMA_Enable(void) {
    SDIO_DATACTL |= SDIO_DATACTL_DMAEN;
}

/*!
    简介:    disable the DMA request for SDIO
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_DMA_Disable(void) {
    SDIO_DATACTL &= ~SDIO_DATACTL_DMAEN;
}

/*!
    简介:    get the flags state of SDIO
    参数[输入]:  flag: flags state of SDIO
                one or more parameters can be selected which are shown as below:
      参数:        SDIO_Flag_CCRCERR: command response received (CRC check failed) flag
      参数:        SDIO_Flag_DTCRCERR: data block sent/received (CRC check failed) flag
      参数:        SDIO_Flag_CMDTMOUT: command response timeout flag
      参数:        SDIO_Flag_DTTMOUT: data timeout flag
      参数:        SDIO_Flag_TXURE: transmit FIFO underrun error occurs flag
      参数:        SDIO_Flag_RXORE: received FIFO overrun error occurs flag
      参数:        SDIO_Flag_CMDRECV: command response received (CRC check passed) flag
      参数:        SDIO_Flag_CMDSEND: command sent (no response required) flag
      参数:        SDIO_Flag_DTEND: data end (data counter, SDIO_DATACNT, is zero) flag
      参数:        SDIO_Flag_STBITE: start bit error in the bus flag
      参数:        SDIO_Flag_DTBLKEND: data block sent/received (CRC check passed) flag
      参数:        SDIO_Flag_CMDRUN: command transmission in progress flag
      参数:        SDIO_Flag_TXRUN: data transmission in progress flag
      参数:        SDIO_Flag_RXRUN: data reception in progress flag
      参数:        SDIO_Flag_TFH: transmit FIFO is half empty flag: at least 8 words can be written into the FIFO
      参数:        SDIO_Flag_RFH: receive FIFO is half full flag: at least 8 words can be read in the FIFO
      参数:        SDIO_Flag_TFF: transmit FIFO is full flag
      参数:        SDIO_Flag_RFF: receive FIFO is full flag
      参数:        SDIO_Flag_TFE: transmit FIFO is empty flag
      参数:        SDIO_Flag_RFE: receive FIFO is empty flag
      参数:        SDIO_Flag_TXDTVAL: data is valid in transmit FIFO flag
      参数:        SDIO_Flag_RXDTVAL: data is valid in receive FIFO flag
      参数:        SDIO_Flag_SDIOINT: SD I/O interrupt received flag
      参数:        SDIO_Flag_ATAEND: CE-ATA command completion signal received (only for CMD61) flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus SDIO_Flag_Get(uint32_t flag) {
    FlagStatus temp_flag = RESET;

    if(RESET != (SDIO_STAT & flag)) {
        temp_flag = SET;
    }

    return temp_flag;
}

/*!
    简介:    clear the pending flags of SDIO
    参数[输入]:  flag: flags state of SDIO
                one or more parameters can be selected which are shown as below:
      参数:        SDIO_Flag_CCRCERR: command response received (CRC check failed) flag
      参数:        SDIO_Flag_DTCRCERR: data block sent/received (CRC check failed) flag
      参数:        SDIO_Flag_CMDTMOUT: command response timeout flag
      参数:        SDIO_Flag_DTTMOUT: data timeout flag
      参数:        SDIO_Flag_TXURE: transmit FIFO underrun error occurs flag
      参数:        SDIO_Flag_RXORE: received FIFO overrun error occurs flag
      参数:        SDIO_Flag_CMDRECV: command response received (CRC check passed) flag
      参数:        SDIO_Flag_CMDSEND: command sent (no response required) flag
      参数:        SDIO_Flag_DTEND: data end (data counter, SDIO_DATACNT, is zero) flag
      参数:        SDIO_Flag_STBITE: start bit error in the bus flag
      参数:        SDIO_Flag_DTBLKEND: data block sent/received (CRC check passed) flag
      参数:        SDIO_Flag_SDIOINT: SD I/O interrupt received flag
      参数:        SDIO_Flag_ATAEND: CE-ATA command completion signal received (only for CMD61) flag
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Flag_Clear(uint32_t flag) {
    SDIO_INTC = flag;
}

/*!
    简介:    enable the SDIO interrupt
    参数[输入]:  int_flag: interrupt flags state of SDIO
                one or more parameters can be selected which are shown as below:
      参数:        SDIO_INT_CCRCERR: SDIO CCRCERR interrupt
      参数:        SDIO_INT_DTCRCERR: SDIO DTCRCERR interrupt
      参数:        SDIO_INT_CMDTMOUT: SDIO CMDTMOUT interrupt
      参数:        SDIO_INT_DTTMOUT: SDIO DTTMOUT interrupt
      参数:        SDIO_INT_TXURE: SDIO TXURE interrupt
      参数:        SDIO_INT_RXORE: SDIO RXORE interrupt
      参数:        SDIO_INT_CMDRECV: SDIO CMDRECV interrupt
      参数:        SDIO_INT_CMDSEND: SDIO CMDSEND interrupt
      参数:        SDIO_INT_DTEND: SDIO DTEND interrupt
      参数:        SDIO_INT_STBITE: SDIO STBITE interrupt
      参数:        SDIO_INT_DTBLKEND: SDIO DTBLKEND interrupt
      参数:        SDIO_INT_CMDRUN: SDIO CMDRUN interrupt
      参数:        SDIO_INT_TXRUN: SDIO TXRUN interrupt
      参数:        SDIO_INT_RXRUN: SDIO RXRUN interrupt
      参数:        SDIO_INT_TFH: SDIO TFH interrupt
      参数:        SDIO_INT_RFH: SDIO RFH interrupt
      参数:        SDIO_INT_TFF: SDIO TFF interrupt
      参数:        SDIO_INT_RFF: SDIO RFF interrupt
      参数:        SDIO_INT_TFE: SDIO TFE interrupt
      参数:        SDIO_INT_RFE: SDIO RFE interrupt
      参数:        SDIO_INT_TXDTVAL: SDIO TXDTVAL interrupt
      参数:        SDIO_INT_RXDTVAL: SDIO RXDTVAL interrupt
      参数:        SDIO_INT_SDIOINT: SDIO SDIOINT interrupt
      参数:        SDIO_INT_ATAEND: SDIO ATAEND interrupt
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Interrupt_Enable(uint32_t int_flag) {
    SDIO_INTEN |= int_flag;
}

/*!
    简介:    disable the SDIO interrupt
    参数[输入]:  int_flag: interrupt flags state of SDIO
                one or more parameters can be selected which are shown as below:
      参数:        SDIO_INT_CCRCERR: SDIO CCRCERR interrupt
      参数:        SDIO_INT_DTCRCERR: SDIO DTCRCERR interrupt
      参数:        SDIO_INT_CMDTMOUT: SDIO CMDTMOUT interrupt
      参数:        SDIO_INT_DTTMOUT: SDIO DTTMOUT interrupt
      参数:        SDIO_INT_TXURE: SDIO TXURE interrupt
      参数:        SDIO_INT_RXORE: SDIO RXORE interrupt
      参数:        SDIO_INT_CMDRECV: SDIO CMDRECV interrupt
      参数:        SDIO_INT_CMDSEND: SDIO CMDSEND interrupt
      参数:        SDIO_INT_DTEND: SDIO DTEND interrupt
      参数:        SDIO_INT_STBITE: SDIO STBITE interrupt
      参数:        SDIO_INT_DTBLKEND: SDIO DTBLKEND interrupt
      参数:        SDIO_INT_CMDRUN: SDIO CMDRUN interrupt
      参数:        SDIO_INT_TXRUN: SDIO TXRUN interrupt
      参数:        SDIO_INT_RXRUN: SDIO RXRUN interrupt
      参数:        SDIO_INT_TFH: SDIO TFH interrupt
      参数:        SDIO_INT_RFH: SDIO RFH interrupt
      参数:        SDIO_INT_TFF: SDIO TFF interrupt
      参数:        SDIO_INT_RFF: SDIO RFF interrupt
      参数:        SDIO_INT_TFE: SDIO TFE interrupt
      参数:        SDIO_INT_RFE: SDIO RFE interrupt
      参数:        SDIO_INT_TXDTVAL: SDIO TXDTVAL interrupt
      参数:        SDIO_INT_RXDTVAL: SDIO RXDTVAL interrupt
      参数:        SDIO_INT_SDIOINT: SDIO SDIOINT interrupt
      参数:        SDIO_INT_ATAEND: SDIO ATAEND interrupt
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Interrupt_Disable(uint32_t int_flag) {
    SDIO_INTEN &= ~int_flag;
}

/*!
    简介:    get the interrupt flags state of SDIO
    参数[输入]:  int_flag: interrupt flags state of SDIO
                one or more parameters can be selected which are shown as below:
      参数:        SDIO_INT_Flag_CCRCERR: SDIO CCRCERR interrupt flag
      参数:        SDIO_INT_Flag_DTCRCERR: SDIO DTCRCERR interrupt flag
      参数:        SDIO_INT_Flag_CMDTMOUT: SDIO CMDTMOUT interrupt flag
      参数:        SDIO_INT_Flag_DTTMOUT: SDIO DTTMOUT interrupt flag
      参数:        SDIO_INT_Flag_TXURE: SDIO TXURE interrupt flag
      参数:        SDIO_INT_Flag_RXORE: SDIO RXORE interrupt flag
      参数:        SDIO_INT_Flag_CMDRECV: SDIO CMDRECV interrupt flag
      参数:        SDIO_INT_Flag_CMDSEND: SDIO CMDSEND interrupt flag
      参数:        SDIO_INT_Flag_DTEND: SDIO DTEND interrupt flag
      参数:        SDIO_INT_Flag_STBITE: SDIO STBITE interrupt flag
      参数:        SDIO_INT_Flag_DTBLKEND: SDIO DTBLKEND interrupt flag
      参数:        SDIO_INT_Flag_CMDRUN: SDIO CMDRUN interrupt flag
      参数:        SDIO_INT_Flag_TXRUN: SDIO TXRUN interrupt flag
      参数:        SDIO_INT_Flag_RXRUN: SDIO RXRUN interrupt flag
      参数:        SDIO_INT_Flag_TFH: SDIO TFH interrupt flag
      参数:        SDIO_INT_Flag_RFH: SDIO RFH interrupt flag
      参数:        SDIO_INT_Flag_TFF: SDIO TFF interrupt flag
      参数:        SDIO_INT_Flag_RFF: SDIO RFF interrupt flag
      参数:        SDIO_INT_Flag_TFE: SDIO TFE interrupt flag
      参数:        SDIO_INT_Flag_RFE: SDIO RFE interrupt flag
      参数:        SDIO_INT_Flag_TXDTVAL: SDIO TXDTVAL interrupt flag
      参数:        SDIO_INT_Flag_RXDTVAL: SDIO RXDTVAL interrupt flag
      参数:        SDIO_INT_Flag_SDIOINT: SDIO SDIOINT interrupt flag
      参数:        SDIO_INT_Flag_ATAEND: SDIO ATAEND interrupt flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus SDIO_Interrupt_Flag_Get(uint32_t int_flag) {
    FlagStatus temp_flag = RESET;

    if(RESET != (SDIO_STAT & int_flag)) {
        temp_flag = SET;
    }

    return temp_flag;
}

/*!
    简介:    clear the interrupt pending flags of SDIO
    参数[输入]:  int_flag: interrupt flags state of SDIO
                one or more parameters can be selected which are shown as below:
      参数:        SDIO_INT_Flag_CCRCERR: command response received (CRC check failed) flag
      参数:        SDIO_INT_Flag_DTCRCERR: data block sent/received (CRC check failed) flag
      参数:        SDIO_INT_Flag_CMDTMOUT: command response timeout flag
      参数:        SDIO_INT_Flag_DTTMOUT: data timeout flag
      参数:        SDIO_INT_Flag_TXURE: transmit FIFO underrun error occurs flag
      参数:        SDIO_INT_Flag_RXORE: received FIFO overrun error occurs flag
      参数:        SDIO_INT_Flag_CMDRECV: command response received (CRC check passed) flag
      参数:        SDIO_INT_Flag_CMDSEND: command sent (no response required) flag
      参数:        SDIO_INT_Flag_DTEND: data end (data counter, SDIO_DATACNT, is zero) flag
      参数:        SDIO_INT_Flag_STBITE: start bit error in the bus flag
      参数:        SDIO_INT_Flag_DTBLKEND: data block sent/received (CRC check passed) flag
      参数:        SDIO_INT_Flag_SDIOINT: SD I/O interrupt received flag
      参数:        SDIO_INT_Flag_ATAEND: CE-ATA command completion signal received (only for CMD61) flag
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Interrupt_Flag_Clear(uint32_t int_flag) {
    SDIO_INTC = int_flag;
}

/*!
    简介:    enable the read wait mode(SD I/O only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_readwait_Enable(void) {
    SDIO_DATACTL |= SDIO_DATACTL_RWEN;
}

/*!
    简介:    disable the read wait mode(SD I/O only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_readwait_Disable(void) {
    SDIO_DATACTL &= ~SDIO_DATACTL_RWEN;
}

/*!
    简介:    enable the function that stop the read wait process(SD I/O only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Stop_readwait_Enable(void) {
    SDIO_DATACTL |= SDIO_DATACTL_RWSTOP;
}

/*!
    简介:    disable the function that stop the read wait process(SD I/O only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Stop_readwait_Disable(void) {
    SDIO_DATACTL &= ~SDIO_DATACTL_RWSTOP;
}

/*!
    简介:    set the read wait type(SD I/O only)
    参数[输入]:  readwait_type: SD I/O read wait type
                only one parameter can be selected which is shown as below:
      参数:        SDIO_READWAITTYPE_CLK: read wait control by stopping SDIO_CLK
      参数:        SDIO_READWAITTYPE_DAT2: read wait control using SDIO_DAT[2]
    参数[输出]:  无
    返回值:      无
*/
void SDIO_readwait_type_Set(uint32_t readwait_type) {
    if(SDIO_READWAITTYPE_CLK == readwait_type) {
        SDIO_DATACTL |= SDIO_DATACTL_RWTYPE;
    } else {
        SDIO_DATACTL &= ~SDIO_DATACTL_RWTYPE;
    }
}

/*!
    简介:    enable the SD I/O mode specific operation(SD I/O only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_operation_Enable(void) {
    SDIO_DATACTL |= SDIO_DATACTL_IOEN;
}

/*!
    简介:    disable the SD I/O mode specific operation(SD I/O only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_operation_Disable(void) {
    SDIO_DATACTL &= ~SDIO_DATACTL_IOEN;
}

/*!
    简介:    enable the SD I/O suspend operation(SD I/O only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_suspend_Enable(void) {
    SDIO_CMDCTL |= SDIO_CMDCTL_SUSPEND;
}

/*!
    简介:    disable the SD I/O suspend operation(SD I/O only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_suspend_Disable(void) {
    SDIO_CMDCTL &= ~SDIO_CMDCTL_SUSPEND;
}

/*!
    简介:    enable the CE-ATA command(CE-ATA only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Ceata_command_Enable(void) {
    SDIO_CMDCTL |= SDIO_CMDCTL_ATAEN;
}

/*!
    简介:    disable the CE-ATA command(CE-ATA only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Ceata_command_Disable(void) {
    SDIO_CMDCTL &= ~SDIO_CMDCTL_ATAEN;
}

/*!
    简介:    enable the CE-ATA interrupt(CE-ATA only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Ceata_Interrupt_Enable(void) {
    SDIO_CMDCTL &= ~SDIO_CMDCTL_NINTEN;
}

/*!
    简介:    disable the CE-ATA interrupt(CE-ATA only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Ceata_Interrupt_Disable(void) {
    SDIO_CMDCTL |= SDIO_CMDCTL_NINTEN;
}

/*!
    简介:    enable the CE-ATA command completion signal(CE-ATA only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Ceata_command_completion_Enable(void) {
    SDIO_CMDCTL |= SDIO_CMDCTL_ENCMDC;
}

/*!
    简介:    disable the CE-ATA command completion signal(CE-ATA only)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SDIO_Ceata_command_completion_Disable(void) {
    SDIO_CMDCTL &= ~SDIO_CMDCTL_ENCMDC;
}
