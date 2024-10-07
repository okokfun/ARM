/**
  **************************************************************************
  * @file     at32f435_437_sdio.c
  * @brief    contains all the functions for the sdio firmware library
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

/** @defgroup SDIO
  * @brief SDIO driver modules
  */

#ifdef SDIO_MODULE_EnableD

/** @defgroup SDIO_private_functions
  */

/**
  * @brief  reset the sdio register
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @retval 无
  */
void SDIO_Reset(SDIO_Type *SDIO_x) {
    SDIO_x->pwrctrl = 0x0;
    SDIO_x->clkctrl = 0x0;
    SDIO_x->argu = 0x0;
    SDIO_x->cmdctrl = 0x0;
    SDIO_x->dttmr = 0x0;
    SDIO_x->dtlen = 0x0;
    SDIO_x->dtctrl = 0x0;
    SDIO_x->inten = 0x0;
    SDIO_x->intclr = 0x004007FF;
}

/**
  * @brief  set the power status of the controller
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  power_state
  *         该参数可以是以下值之一:
  *         - SDIO_Power_OFF
  *         - SDIO_Power_ON
  * @retval 无
  */
void SDIO_Power_Set(SDIO_Type *SDIO_x, SDIO_Power_State_Type power_state) {
    SDIO_x->pwrctrl_bit.ps = power_state;
}

/**
  * @brief  get power status.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @retval SDIO_Power_State_Type (SDIO_Power_ON or SDIO_Power_OFF)
  */
SDIO_Power_State_Type SDIO_Power_Status_Get(SDIO_Type *SDIO_x) {
    return (SDIO_Power_State_Type)(SDIO_x->pwrctrl_bit.ps);
}

/**
  * @brief  config sdio clock
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  clk_div: sdio clock divide factor(frequency = SDIO_CLK / [clk_psc + 2]).
  * @param  clk_edg
  *         该参数可以是以下值之一:
  *         - SDIO_Clock_Edge_RISING
  *         - SDIO_Clock_Edge_FALLING
  * @retval 无
  */
void SDIO_Clock_Config(SDIO_Type *SDIO_x, uint16_t clk_div, SDIO_Edge_phase_Type clk_edg) {
    /* config clock edge */
    SDIO_x->clkctrl_bit.clkegs = clk_edg;

    /* config clock divide [7:0] */
    SDIO_x->clkctrl_bit.clkdiv_l = (clk_div & 0xFF);

    /* config clock divide [9:8] */
    SDIO_x->clkctrl_bit.clkdiv_h = ((clk_div & 0x300) >> 8);
}

/**
  * @brief  config sdio bus width
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  width
  *         该参数可以是以下值之一:
  *         - SDIO_Bus_Width_D1
  *         - SDIO_Bus_Width_D4
  *         - SDIO_Bus_Width_D8
  * @retval 无
  */
void SDIO_Bus_Width_Config(SDIO_Type *SDIO_x, SDIO_Bus_Width_Type width) {
    SDIO_x->clkctrl_bit.busws = width;
}

/**
  * @brief  enable or disable clock divider bypss
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Clock_ByPass(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->clkctrl_bit.bypsen = new_state;
}

/**
  * @brief  enable or disable power saving mode, config SDIO_ck clock output
  *         when the bus is idle.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Power_Saving_Mode_Enable(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->clkctrl_bit.pwrsven = new_state;
}

/**
  * @brief  enable or disable hardware flow control.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Flow_Control_Enable(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->clkctrl_bit.hfcen = new_state;
}

/**
  * @brief  enable or disable SDIO_ck output.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Clock_Enable(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->clkctrl_bit.clkoen = new_state;
}

/**
  * @brief  enable or disable dma.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_DMA_Enable(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->dtctrl_bit.dmaen = new_state;
}

/**
  * @brief  config corresponding interrupt.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  int_opt
  *         该参数可以是以下值之一:
  *         - SDIO_CMDFAIL_INT
  *         - SDIO_DTFAIL_INT
  *         - SDIO_CMDTIMEOUT_INT
  *         - SDIO_DTTIMEOUT_INT
  *         - SDIO_TXERRU_INT
  *         - SDIO_RXERRO_INT
  *         - SDIO_CMDRSPCMPL_INT
  *         - SDIO_CMDCMPL_INT
  *         - SDIO_DTCMP_INT
  *         - SDIO_SBITERR_INT
  *         - SDIO_DTBLKCMPL_INT
  *         - SDIO_DOCMD_INT
  *         - SDIO_DOTX_INT
  *         - SDIO_DORX_INT
  *         - SDIO_TXBUFH_INT
  *         - SDIO_RXBUFH_INT
  *         - SDIO_TXBUFF_INT
  *         - SDIO_RXBUFF_INT
  *         - SDIO_TXBUFE_INT
  *         - SDIO_RXBUFE_INT
  *         - SDIO_TXBUF_INT
  *         - SDIO_RXBUF_INT
  *         - SDIO_SDIOIF_INT
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Interrupt_Enable(SDIO_Type *SDIO_x, uint32_t int_opt,  confirm_state new_state) {
    /* enable 中断 */
    if(TRUE == new_state) {
        SDIO_x->inten |= int_opt;
    }
    /* disable 中断 */
    else {
        SDIO_x->inten &= ~(int_opt);
    }
}

/**
  * @brief  get sdio flag.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  flag
  *         该参数可以是以下值之一:
  *         - SDIO_CMDFAIL_FLAG
  *         - SDIO_DTFAIL_FLAG
  *         - SDIO_CMDTIMEOUT_FLAG
  *         - SDIO_DTTIMEOUT_FLAG
  *         - SDIO_TXERRU_FLAG
  *         - SDIO_RXERRO_FLAG
  *         - SDIO_CMDRSPCMPL_FLAG
  *         - SDIO_CMDCMPL_FLAG
  *         - SDIO_DTCMPL_FLAG
  *         - SDIO_SBITERR_FLAG
  *         - SDIO_DTBLKCMPL_FLAG
  *         - SDIO_DOCMD_FLAG
  *         - SDIO_DOTX_FLAG
  *         - SDIO_DORX_FLAG
  *         - SDIO_TXBUFH_FLAG
  *         - SDIO_RXBUFH_FLAG
  *         - SDIO_TXBUFF_FLAG
  *         - SDIO_RXBUFF_FLAG
  *         - SDIO_TXBUFE_FLAG
  *         - SDIO_RXBUFE_FLAG
  *         - SDIO_TXBUF_FLAG
  *         - SDIO_RXBUF_FLAG
  *         - SDIO_SDIOIF_FLAG
  * @retval flag_status (SET or RESET)
  */
flag_status SDIO_Flag_Get(SDIO_Type *SDIO_x, uint32_t flag) {
    flag_status status = RESET;

    if((SDIO_x->sts & flag) == flag) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/**
  * @brief  clear sdio flag.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  int_opt
  *         该参数可以是以下值的任意组合:
  *         - SDIO_CMDFAIL_FLAG
  *         - SDIO_DTFAIL_FLAG
  *         - SDIO_CMDTIMEOUT_FLAG
  *         - SDIO_DTTIMEOUT_FLAG
  *         - SDIO_TXERRU_FLAG
  *         - SDIO_RXERRO_FLAG
  *         - SDIO_CMDRSPCMPL_FLAG
  *         - SDIO_CMDCMPL_FLAG
  *         - SDIO_DTCMPL_FLAG
  *         - SDIO_SBITERR_FLAG
  *         - SDIO_DTBLKCMPL_FLAG
  *         - SDIO_SDIOIF_FLAG
  * @retval 无
  */
void SDIO_Flag_Clear(SDIO_Type *SDIO_x, uint32_t flag) {
    SDIO_x->intclr = flag;
}

/**
  * @brief  config sdio command.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  command_struct : pointer to a SDIO_Command_struct_Type structure
  *         that contains the configuration information for the sdio command.
  * @retval 无
  */
void SDIO_Command_Config(SDIO_Type *SDIO_x, SDIO_Command_struct_Type *command_struct) {
    /* disable command path state machine */
    SDIO_x->cmdctrl_bit.ccsmen = FALSE;

    /* config command argument */
    SDIO_x->argu = command_struct->argument;

    /* config command register */
    SDIO_x->cmdctrl_bit.cmdidx = command_struct->cmd_index;
    SDIO_x->cmdctrl_bit.rspwt = command_struct->rsp_Type;
    SDIO_x->cmdctrl_bit.intwt = (command_struct->wait_Type & 0x1); /* [1:0] -> [0] */
    SDIO_x->cmdctrl_bit.pndwt = (command_struct->wait_Type & 0x2) >> 1; /* [1:0] -> [1] */
}

/**
  * @brief  enable or disable command path state machine(CPSM).
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Command_State_Machine_Enable(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->cmdctrl_bit.ccsmen = new_state;
}

/**
  * @brief  get command index of last command for which response received.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval uint8_t: command index
  */
uint8_t SDIO_Command_Response_Get(SDIO_Type *SDIO_x) {
    return SDIO_x->rspcmd_bit.rspcmd;
}

/**
  * @brief  get response received from the card for the last command.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  reg_index
  *         该参数可以是以下值之一:
  *         - SDIO_RSP1_INDEX
  *         - SDIO_RSP2_INDEX
  *         - SDIO_RSP3_INDEX
  *         - SDIO_RSP4_INDEX
  * @retval uint32_t: response register value
  */
uint32_t SDIO_Response_Get(SDIO_Type *SDIO_x, SDIO_rsp_index_Type reg_index) {
    uint32_t response_value = 0;

    switch(reg_index) {
        case SDIO_RSP1_INDEX:
            response_value = SDIO_x->rsp1;
            break;

        case SDIO_RSP2_INDEX:
            response_value = SDIO_x->rsp2;
            break;

        case SDIO_RSP3_INDEX:
            response_value = SDIO_x->rsp3;
            break;

        case SDIO_RSP4_INDEX:
            response_value = SDIO_x->rsp4;
            break;

        default:
            break;
    }

    return response_value;
}

/**
  * @brief  config sdio data.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  data_struct : pointer to a SDIO_Data_struct_Type structure
  *         that contains the configuration information for the sdio data.
  * @retval 无
  */
void SDIO_Data_Config(SDIO_Type *SDIO_x, SDIO_Data_struct_Type *data_struct) {
    /* disable data path state machine */
    SDIO_x->dtctrl_bit.tfren = FALSE;

    /* config data block, transfer mode and transfer direction */
    SDIO_x->dtctrl_bit.blksize = data_struct->block_size;
    SDIO_x->dtctrl_bit.tfrdir = data_struct->transfer_direction;
    SDIO_x->dtctrl_bit.tfrmode = data_struct->transfer_Mode;

    /* config data length */
    SDIO_x->dtlen_bit.dtlen = data_struct->data_length;

    /* config data transfer timeout */
    SDIO_x->dtTMR_bit.timeout = data_struct->timeout;
}

/**
  * @brief  enable or disable data path state machine(DPSM).
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Data_State_Machine_Enable(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->dtctrl_bit.tfren = new_state;
}

/**
  * @brief  get the number of remaining data bytes to be transferred.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @retval uint32_t: number of bytes
  */
uint32_t SDIO_Data_Counter_Get(SDIO_Type *SDIO_x) {
    return SDIO_x->dtcnt;
}

/**
  * @brief  read a word data from sdio fifo.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @retval uint32_t: data received
  */
uint32_t SDIO_Data_Read(SDIO_Type *SDIO_x) {
    return SDIO_x->buf;
}

/**
  * @brief  get the number of words left to be written to or read from fifo..
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @retval uint32_t: number of words
  */
uint32_t SDIO_Buffer_Counter_Get(SDIO_Type *SDIO_x) {
    return SDIO_x->bufcnt;
}

/**
  * @brief  write one word data to fifo.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  data: data to be transferred.
  * @retval 无
  */
void SDIO_Data_Write(SDIO_Type *SDIO_x, uint32_t data) {
    SDIO_x->buf = data;
}

/**
  * @brief  set the read wait mode.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  mode
  *         该参数可以是以下值之一:
  *         - SDIO_Read_Wait_CONTROLLED_BY_D2
  *         - SDIO_Read_Wait_CONTROLLED_BY_CK
  * @retval 无
  */
void SDIO_Read_Wait_Mode_Set(SDIO_Type *SDIO_x, SDIO_Read_Wait_Mode_Type mode) {
    SDIO_x->dtctrl_bit.rdwtmode = mode;
}

/**
  * @brief  enable or disable to start sd i/o read wait operation.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Read_Wait_Start(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->dtctrl_bit.rdwtstart = new_state;
}

/**
  * @brief  enable or disable to stop sd i/o read wait operation.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_Read_Wait_stop(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->dtctrl_bit.rdwtstop = new_state;
}

/**
  * @brief  enable or disable the sd i/o function.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_IO_Function_Enable(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->dtctrl_bit.ioen = new_state;
}

/**
  * @brief  enable or disable sd i/o suspend command sending.
  * @param  SDIO_x: to select the sdio peripheral.
  *         该参数可以是以下值之一:
  *         SDIO1, SDIO2.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void SDIO_IO_Suspend_Command_Set(SDIO_Type *SDIO_x, confirm_state new_state) {
    SDIO_x->cmdctrl_bit.iosusp = new_state;
}

#endif
