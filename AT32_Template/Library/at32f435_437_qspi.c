/**
  **************************************************************************
  * @file     at32f435_437_qspi.c
  * @brief    contain all the functions for qspi firmware library
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

/** @addtogroup AT32F435_437_periph_driver
  * @{
  */

/** @defgroup QSPI
  * @brief QSPI driver modules
  * @{
  */

#ifdef QSPI_MODULE_EnableD

/** @defgroup QSPI_private_functions
  * @{
  */

/**
  * @brief  enable/disable encryption for qspi.
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void QSPI_encryption_Enable(QSPI_Type* QSPI_x, confirm_state new_state) {
    QSPI_x->ctrl_bit.keyen = new_state;
}

/**
  * @brief  set qspi sck mode.
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_mode: new state to be set
  *         this parameter can be one of the following values:
  *         - QSPI_SCK_Mode_0
  *         - QSPI_SCK_Mode_3
  * @retval none
  */
void QSPI_sck_Mode_Set(QSPI_Type* QSPI_x, QSPI_clk_Mode_Type new_mode) {
    QSPI_x->ctrl_bit.sckmode = new_mode;
}

/**
  * @brief  set qspi clock division
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_clkdiv: new division value
  *         this parameter can be one of the following values:
  *         - QSPI_CLK_DIV_2
  *         - QSPI_CLK_DIV_4
  *         - QSPI_CLK_DIV_6
  *         - QSPI_CLK_DIV_8
  *         - QSPI_CLK_DIV_3
  *         - QSPI_CLK_DIV_5
  *         - QSPI_CLK_DIV_10
  *         - QSPI_CLK_DIV_12
  * @retval none
  */
void QSPI_clk_division_Set(QSPI_Type* QSPI_x, QSPI_clk_div_Type new_clkdiv) {
    QSPI_x->ctrl_bit.clkdiv = new_clkdiv;
}

/**
  * @brief  enable/disable cache in xip mode
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void QSPI_xip_cache_bypass_Set(QSPI_Type* QSPI_x, confirm_state new_state) {
    QSPI_x->xip_cmd_w3_bit.bypassc = new_state;
}

/**
  * @brief  enable/disable interrupt when command is completed
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void QSPI_Interrupt_Enable(QSPI_Type* QSPI_x, confirm_state new_state) {
    QSPI_x->ctrl2_bit.cmdie = new_state;
}

/**
  * @brief  get status flags.
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  flag: specifies the flag to check.
  *         this parameter can be one of the following values:
  *         - QSPI_RXFIFORDY_FLAG
  *         - QSPI_TXFIFORDY_FLAG
  *         - QSPI_CMDSTS_FLAG
  * @retval the new state of usart_flag (SET or RESET).
  */
flag_status QSPI_Flag_Get(QSPI_Type* QSPI_x, uint32_t flag) {
    flag_status bit_status = RESET;

    switch(flag) {
        case QSPI_RXFIFORDY_FLAG:
            bit_status = (flag_status)QSPI_x->fifosts_bit.rxfifordy;
            break;

        case QSPI_TXFIFORDY_FLAG:
            bit_status = (flag_status)QSPI_x->fifosts_bit.txfifordy;
            break;

        case QSPI_CMDSTS_FLAG:
            bit_status = (flag_status)QSPI_x->cmdsts_bit.cmdsts;
            break;

        default:
            break;
    }

    return bit_status;
}

/**
  * @brief  clear flags
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  flag: flags to be clear
  *         this parameter can be one of the following values:
  *         - QSPI_CMDSTS_FLAG
  * @retval none
  */
void QSPI_Flag_Clear(QSPI_Type* QSPI_x, uint32_t flag) {
    QSPI_x->cmdsts = QSPI_CMDSTS_FLAG;
}

/**
  * @brief  set dma threshold for dma rx
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_threshold: value to set
  *         this parameter can be one of the following values:
  *         - QSPI_DMA_FIFO_THOD_WORD08
  *         - QSPI_DMA_FIFO_THOD_WORD16
  *         - QSPI_DMA_FIFO_THOD_WORD32
  * @retval none
  */
void QSPI_DMA_rx_threshold_Set(QSPI_Type* QSPI_x, QSPI_DMA_FIFO_thod_Type new_threshold) {
    QSPI_x->ctrl2_bit.rxfifo_thod = new_threshold;
}

/**
  * @brief  set dma threshold for dma tx
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_threshold: value to set
  *         this parameter can be one of the following values:
  *         - QSPI_DMA_FIFO_THOD_WORD08
  *         - QSPI_DMA_FIFO_THOD_WORD16
  *         - QSPI_DMA_FIFO_THOD_WORD32
  * @retval none
  */
void QSPI_DMA_tx_threshold_Set(QSPI_Type* QSPI_x, QSPI_DMA_FIFO_thod_Type new_threshold) {
    QSPI_x->ctrl2_bit.txfifo_thod = new_threshold;
}

/**
  * @brief  enable/disable dma transfer
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void QSPI_DMA_Enable(QSPI_Type* QSPI_x, confirm_state new_state) {
    QSPI_x->ctrl2_bit.dmaen = new_state;
}

/**
  * @brief  set wip position in status register of flash
  * @note   the function must be configured only when qspi in command-port mode!!!
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  busy_pos: value to set
  *         this parameter can be one of the following values:
  *         - QSPI_BUSY_OFFSET_0
  *         - QSPI_BUSY_OFFSET_1
  *         - QSPI_BUSY_OFFSET_2
  *         - QSPI_BUSY_OFFSET_3
  *         - QSPI_BUSY_OFFSET_4
  *         - QSPI_BUSY_OFFSET_5
  *         - QSPI_BUSY_OFFSET_6
  *         - QSPI_BUSY_OFFSET_7
  * @retval none
  */
void QSPI_busy_Config(QSPI_Type* QSPI_x, QSPI_busy_pos_Type busy_pos) {
    QSPI_x->ctrl_bit.busy = busy_pos;
}

/**
  * @brief  enable xip mode or command-port mode.
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void QSPI_xip_Enable(QSPI_Type* QSPI_x, confirm_state new_state) {
    /* skip if state is no change */
    if(new_state == (confirm_state)(QSPI_x->ctrl_bit.xipsel)) {
        return;
    }

    /* wait until tx fifo emoty*/
    while(QSPI_x->fifosts_bit.txfifordy == 0);

    /* flush and reset qspi state */
    QSPI_x->ctrl_bit.xiprcmdf = 1;

    /* wait until action is finished */
    while(QSPI_x->ctrl_bit.abort);

    /* set xip mode to new state */
    QSPI_x->ctrl_bit.xipsel = new_state;

    /* wait until abort is not set */
    while(QSPI_x->ctrl_bit.abort);

    /* wait until cache status valid*/
    if(new_state == TRUE) {
        while( QSPI_x->xip_cmd_w3_bit.csts );
    }
}

/**
  * @brief  set command-port and QSPI_x will start to work
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  QSPI_cmd_struct: pointer to qspi cmd structure
  * @retval none
  */
void QSPI_cmd_Operation_kick(QSPI_Type* QSPI_x, QSPI_cmd_Type* QSPI_cmd_struct) {
    uint32_t w1_val = 0, w3_val = 0;

    /* config analyse cmd_w0 register */
    QSPI_x->cmd_w0 = (uint32_t)QSPI_cmd_struct->address_code;

    /* config analyse cmd_w1 register */
    w1_val = (uint32_t)QSPI_cmd_struct->address_length;
    w1_val |= (uint32_t)(QSPI_cmd_struct->second_dummy_cycle_Num << 16);
    w1_val |= (uint32_t)(QSPI_cmd_struct->instruction_length << 24);
    w1_val |= (uint32_t)(QSPI_cmd_struct->pe_Mode_Enable << 28);
    QSPI_x->cmd_w1 = w1_val;

    /* config analyse cmd_w2 register */
    QSPI_x->cmd_w2 = (uint32_t)QSPI_cmd_struct->data_counter;

    /* config analyse cmd_w3 register */
    w3_val = (uint32_t)(QSPI_cmd_struct->write_Data_Enable << 1);
    w3_val |= (uint32_t)(QSPI_cmd_struct->read_Status_Enable << 2);
    w3_val |= (uint32_t)(QSPI_cmd_struct->read_Status_Config << 3);
    w3_val |= (uint32_t)(QSPI_cmd_struct->operation_mode << 5);
    w3_val |= (uint32_t)(QSPI_cmd_struct->pe_Mode_operate_code << 16);
    w3_val |= (uint32_t)(QSPI_cmd_struct->instruction_code << 24);
    QSPI_x->cmd_w3 = w3_val;
}

/**
  * @brief  initial xip mode for QSPI_x
  * @param  QSPI_x: select the qspi peripheral.
  *         this parameter can be one of the following values:
  *         QSPI1,QSPI2.
  * @param  xip_Init_struct: pointer to xip init structure.
  * @retval none.
  */
void QSPI_xip_Init(QSPI_Type* QSPI_x, QSPI_xip_Type* xip_Init_struct) {
    uint32_t xc0_val = 0, xc1_val = 0, xc2_val = 0;
    /* config analyse xip_cmd_w0 register */
    xc0_val = (uint32_t)xip_Init_struct->read_Second_dummy_cycle_Num;
    xc0_val |= (uint32_t)(xip_Init_struct->read_Operation_mode << 8);
    xc0_val |= (uint32_t)(xip_Init_struct->read_Address_length << 11);
    xc0_val |= (uint32_t)(xip_Init_struct->read_instruction_code << 12);
    QSPI_x->xip_cmd_w0 = xc0_val;

    /* config analyse xip_cmd_w1 register */
    xc1_val = (uint32_t)xip_Init_struct->write_Second_dummy_cycle_Num;
    xc1_val |= (uint32_t)(xip_Init_struct->write_Operation_mode << 8);
    xc1_val |= (uint32_t)(xip_Init_struct->write_Address_length << 11);
    xc1_val |= (uint32_t)(xip_Init_struct->write_instruction_code << 12);
    QSPI_x->xip_cmd_w1 = xc1_val;

    /* config analyse xip_cmd_w2 register */
    xc2_val = (uint32_t)xip_Init_struct->read_Data_counter;
    xc2_val |= (uint32_t)(xip_Init_struct->read_Time_counter << 8);
    xc2_val |= (uint32_t)(xip_Init_struct->read_Select_mode << 15);
    xc2_val |= (uint32_t)(xip_Init_struct->write_Data_counter << 16);
    xc2_val |= (uint32_t)(xip_Init_struct->write_Time_counter << 24);
    xc2_val |= (uint32_t)(xip_Init_struct->write_Select_mode << 31);
    QSPI_x->xip_cmd_w2 = xc2_val;
}

/**
  * @brief  read one byte from qspi device in command mode
  * @param  QSPI_x: select the qspi peripheral.
  * @retval 8-bit data.
  */
uint8_t QSPI_Byte_Read(QSPI_Type* QSPI_x) {
    return QSPI_x->dt_u8;
}

/**
  * @brief  read one half-word from qspi device in command mode
  * @param  QSPI_x: select the qspi peripheral.
  * @retval 16-bit data.
  */
uint16_t QSPI_half_Word_Read(QSPI_Type* QSPI_x) {
    return QSPI_x->dt_u16;
}

/**
  * @brief  read one word from qspi device in command mode
  * @param  QSPI_x: select the qspi peripheral.
  * @retval 32-bit data.
  */
uint32_t QSPI_Word_Read(QSPI_Type* QSPI_x) {
    return QSPI_x->dt;
}

/**
  * @brief  write one byte to qspi device in command mode
  * @param  QSPI_x: select the qspi peripheral.
  * @param  value:  8-bit data.
  * @retval none.
  */
void QSPI_Byte_Write(QSPI_Type* QSPI_x, uint8_t value) {
    QSPI_x->dt_u8 = value;
}

/**
  * @brief  write one half-word to qspi device in command mode
  * @param  QSPI_x: select the qspi peripheral.
  * @param  value:  16-bit data.
  * @retval none.
  */
void QSPI_half_Word_Write(QSPI_Type* QSPI_x, uint16_t value) {
    QSPI_x->dt_u16 = value;
}

/**
  * @brief  write one word to qspi device in command mode
  * @param  QSPI_x: select the qspi peripheral.
  * @param  value:  32-bit data.
  * @retval none.
  */
void QSPI_Word_Write(QSPI_Type* QSPI_x, uint32_t value) {
    QSPI_x->dt = value;
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
