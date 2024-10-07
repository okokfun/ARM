/**
  **************************************************************************
  * @file     at32f435_437_usart.c
  * @brief    contains all the functions for the usart firmware library
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

/* includes ------------------------------------------------------------------*/
#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @defgroup USART
  * @brief USART driver modules
  */

#ifdef USART_MODULE_EnableD

/** @defgroup USART_private_functions
  */

/**
  * @brief  deinitialize the usart peripheral registers to their default reset values.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7,or UART8.
  * @retval 无
  */
void USART_Reset(USART_Type* USART_x) {
    if(USART_x == USART1) {
        CRM_Periph_Reset(CRM_USART1_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_USART1_Periph_Reset, FALSE);
    } else if(USART_x == USART2) {
        CRM_Periph_Reset(CRM_USART2_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_USART2_Periph_Reset, FALSE);
    } else if(USART_x == USART3) {
        CRM_Periph_Reset(CRM_USART3_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_USART3_Periph_Reset, FALSE);
    } else if(USART_x == UART4) {
        CRM_Periph_Reset(CRM_UART4_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_UART4_Periph_Reset, FALSE);
    } else if(USART_x == UART5) {
        CRM_Periph_Reset(CRM_UART5_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_UART5_Periph_Reset, FALSE);
    } else if(USART_x == USART6) {
        CRM_Periph_Reset(CRM_USART6_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_USART6_Periph_Reset, FALSE);
    } else if(USART_x == UART7) {
        CRM_Periph_Reset(CRM_UART7_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_UART7_Periph_Reset, FALSE);
    }

    #if defined (AT32F435Zx) || defined (AT32F435Vx) || defined (AT32F435Rx) || \
    defined (AT32F437Zx) || defined (AT32F437Vx) || defined (AT32F437Rx)
    else if(USART_x == UART8) {
        CRM_Periph_Reset(CRM_UART8_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_UART8_Periph_Reset, FALSE);
    }

    #endif
}

/**
  * @brief  根据指定的参数初始化usart外设。
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4 ,UART5, USART6, UART7 or UART8.
  * @param  baud_rate: configure the usart communication baud rate.
  * @param  data_bit: data bits transmitted or received in a frame
  *         该参数可以是以下值之一:
  *         - USART_Data_7BITS
  *         - USART_Data_8BITS
  *         - USART_Data_9BITS.
  * @param  stop_bit: stop bits transmitted
  *         该参数可以是以下值之一:
  *         - USART_Stop_1_BIT
  *         - USART_Stop_0_5_BIT.
  *         - USART_Stop_2_BIT
  *         - USART_Stop_1_5_BIT.
  * @retval 无
  */
void USART_Init(USART_Type* USART_x, uint32_t baud_rate, USART_Data_Bit_Num_Type data_bit, USART_Stop_Bit_Num_Type stop_bit) {
    CRM_Clocks_Freq_Type clocks_freq;
    uint32_t apb_clock, temp_val;
    CRM_Clocks_Freq_Get(&clocks_freq);

    if((USART_x == USART1) || (USART_x == USART6)) {
        apb_clock = clocks_freq.apb2_freq;
    } else {
        apb_clock = clocks_freq.apb1_freq;
    }

    temp_val = (apb_clock * 10 / baud_rate);

    if((temp_val % 10) < 5) {
        temp_val = (temp_val / 10);
    } else {
        temp_val = (temp_val / 10) + 1;
    }

    USART_x->baudr_bit.div = temp_val;

    if(data_bit == USART_Data_7BITS) {
        USART_x->ctrl1_bit.dbn_h = 1;
        USART_x->ctrl1_bit.dbn_l = 0;
    } else if(data_bit == USART_Data_8BITS) {
        USART_x->ctrl1_bit.dbn_h = 0;
        USART_x->ctrl1_bit.dbn_l = 0;
    } else {
        USART_x->ctrl1_bit.dbn_h = 0;
        USART_x->ctrl1_bit.dbn_l = 1;
    }

    USART_x->ctrl2_bit.stopbn = stop_bit;
}

/**
  * @brief  usart parity selection config.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4 ,UART5, USART6, UART7 or UART8.
  * @param  parity: select the none, odd or even parity.
  *         该参数可以是以下值之一:
  *         - USART_PARITY_NONE
  *         - USART_PARITY_EVEN.
  *         - USART_PARITY_ODD
  * @retval 无
  */
void USART_parity_Selection_Config(USART_Type* USART_x, USART_parity_Selection_Type parity) {
    if(parity == USART_PARITY_NONE) {
        USART_x->ctrl1_bit.psel = FALSE;
        USART_x->ctrl1_bit.pen = FALSE;
    } else if(parity == USART_PARITY_EVEN) {
        USART_x->ctrl1_bit.psel = FALSE;
        USART_x->ctrl1_bit.pen = TRUE;
    } else if(parity == USART_PARITY_ODD) {
        USART_x->ctrl1_bit.psel = TRUE;
        USART_x->ctrl1_bit.pen = TRUE;
    }
}

/**
  * @brief  enable or disable the specified usart peripheral.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  new_state: new state of the usart peripheral.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl1_bit.uen = new_state;
}

/**
  * @brief  usart transmitter enable.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4 ,UART5, USART6, UART7 or UART8.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void USARTTransmitter_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl1_bit.ten = new_state;
}

/**
  * @brief  usart receiver enable.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4 ,UART5, USART6, UART7 or UART8.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void USART_Receiver_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl1_bit.ren = new_state;
}

/**
  * @brief  usart clock config.
  * @note   clock config are not available for UART4, UART5, UART7 and UART8.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3 or USART6.
  * @param  clk_pol: polarity of the clock output on the ck pin.
  *         该参数可以是以下值之一:
  *         - USART_Clock_Polarity_LOW
  *         - USART_Clock_Polarity_HIGH
  * @param  clk_pha: phase of the clock output on the ck pin.
  *         该参数可以是以下值之一:
  *         - USART_Clock_PHASE_1EDGE
  *         - USART_Clock_PHASE_2EDGE
  * @param  clk_lb: whether the clock pulse of the last data bit transmitted (MSB) is outputted on the ck pin.
  *         该参数可以是以下值之一:
  *         - USART_Clock_LAST_Bit_NONE
  *         - USART_Clock_LAST_Bit_OutPUT
  * @retval 无
  */
void USART_Clock_Config(USART_Type* USART_x, USART_Clock_Polarity_Type clk_pol, USART_Clock_phase_Type clk_pha, USART_lbcp_Type clk_lb) {
    USART_x->ctrl2_bit.clkpol = clk_pol;
    USART_x->ctrl2_bit.clkpha = clk_pha;
    USART_x->ctrl2_bit.lbcp = clk_lb;
}

/**
  * @brief  usart enable the ck pin.
  * @note   clock enable are not available for UART4, UART5, UART7 and UART8.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3 or USART6.
  * @param  new_state: TRUE or FALSE
  * @retval 无
  */
void USART_Clock_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl2_bit.clken = new_state;
}

/**
  * @brief  enable or disable the specified usart interrupts.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  USART_int: 指定USART interrupt sources to be enabled or disabled.
  *         该参数可以是以下值之一:
  *         - USART_IDLE_INT:  idle interrupt
  *         - USART_RDBF_INT:  rdbf interrupt
  *         - USART_TDC_INT:   tdc interrupt
  *         - USART_TDBE_INT:  tdbe interrupt
  *         - USART_PERR_INT:  perr interrupt
  *         - USART_BF_INT:    break frame interrupt
  *         - USART_ERR_INT:   err interrupt
  *         - USART_CTSCF_INT: ctscf interrupt
  * @param  new_state: new state of the specified usart interrupts.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_Interrupt_Enable(USART_Type* USART_x, uint32_t USART_int, confirm_state new_state) {
    if(new_state == TRUE)
        PERIPH_REG((uint32_t)USART_x, USART_int) |= PERIPH_REG_BIT(USART_int);
    else
        PERIPH_REG((uint32_t)USART_x, USART_int) &= ~PERIPH_REG_BIT(USART_int);
}

/**
  * @brief  启用或禁用 Usart的dma发射机接口。
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  new_state: new state of the dma request sources.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_DMATransmitter_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl3_bit.dmaten = new_state;
}

/**
  * @brief  启用或禁用 Usart的dma接收机接口。
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  new_state: new state of the dma request sources.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_DMA_Receiver_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl3_bit.dmaren = new_state;
}

/**
  * @brief  set the wakeup id of the usart.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  USART_id: the matching id(0x0~0xFF).
  * @retval 无
  */
void USART_WakeUp_ID_Set(USART_Type* USART_x, uint8_t USART_id) {
    if(USART_x->ctrl2_bit.idbn == USART_ID_FIXED_4_BIT) {
        USART_x->ctrl2_bit.id_l = (USART_id & 0x0F);
        USART_x->ctrl2_bit.id_h = 0;
    } else {
        USART_x->ctrl2_bit.id_l = (USART_id & 0x0F);
        USART_x->ctrl2_bit.id_h = ((USART_id & 0xF0) >> 4);
    }
}

/**
  * @brief  select the usart wakeup method in multi-processor communication.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  wakeup_Mode: determines the way to wake up usart method.
  *         该参数可以是以下值之一:
  *         - USART_WakeUp_BY_IDLE_Frame
  *         - USART_WakeUp_BY_MATCHING_ID
  * @retval 无
  */
void USART_WakeUp_Mode_Set(USART_Type* USART_x, USART_WakeUp_Mode_Type wakeup_Mode) {
    USART_x->ctrl1_bit.wum = wakeup_Mode;
}

/**
  * @brief  config the usart in mute mode in multi-processor communication.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  new_state: new state of the usart mute mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_Receiver_mute_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl1_bit.rm = new_state;
}

/**
  * @brief  set the usart break frame bit num.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  break_bit: 指定break bit num.
  *         该参数可以是以下值之一:
  *         - USART_Break_10BITS
  *         - USART_Break_11BITS
  * @retval 无
  */
void USART_Break_Bit_Num_Set(USART_Type* USART_x, USART_Break_Bit_Num_Type break_bit) {
    USART_x->ctrl2_bit.bfbn = break_bit;
}

/**
  * @brief  enable or disable the usart lin mode.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  new_state: new state of the usart lin mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_lin_Mode_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl2_bit.linen = new_state;
}

/**
  * @brief  transmit single data through the usart peripheral.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  data: the data to transmit.
  * @retval 无
  */
void USART_Data_Transmit(USART_Type* USART_x, uint16_t data) {
    USART_x->dt = (data & 0x01FF);
}

/**
  * @brief  return the most recent received data by the usart peripheral.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @retval the received data.
  */
uint16_t USART_Data_Receive(USART_Type* USART_x) {
    return (uint16_t)(USART_x->dt);
}

/**
  * @brief  transmit break characters.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @retval 无
  */
void USART_Break_Send(USART_Type* USART_x) {
    USART_x->ctrl1_bit.sbf = TRUE;
}

/**
  * @brief  config the specified usart smartcard guard time.
  * @note   The guard time bits are not available for UART4, UART5, UART7 or UART8.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3 or USART6.
  * @param  guard_Time_val: 指定guard time (0x00~0xFF).
  * @retval 无
  */
void USART_SmartCard_Guard_Time_Set(USART_Type* USART_x, uint8_t guard_Time_val) {
    USART_x->gdiv_bit.scgt = guard_Time_val;
}

/**
  * @brief  config the irda/smartcard division.
  * @note   the division are not available for UART4, UART5, UART7 or UART8.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3 or USART6.
  * @param  div_val: 指定division.
  * @retval 无
  */
void USART_IRDA_SmartCard_Division_Set(USART_Type* USART_x, uint8_t div_val) {
    USART_x->gdiv_bit.isdiv = div_val;
}

/**
  * @brief  enable or disable the usart smart card mode.
  * @note   the smart card mode are not available for UART4, UART5, UART7 or UART8.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3 or USART6.
  * @param  new_state: new state of the smart card mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_SmartCard_Mode_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl3_bit.scmen = new_state;
}

/**
  * @brief  enable or disable nack transmission in smartcard mode.
  * @note   the smart card nack are not available for UART4, UART5, UART7 or UART8.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3 or USART6.
  * @param  new_state: new state of the nack transmission.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_SmartCard_Nack_Set(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl3_bit.scnacken = new_state;
}

/**
  * @brief  enable or disable the usart single line bidirectional half-duplex communication.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  new_state: new state of the single line half-duplex select.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_Single_Line_halfduplex_Select(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl3_bit.slben = new_state;
}

/**
  * @brief  enable or disable the usart's irda interface.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  new_state: new state of the irda mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_IRDA_Mode_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl3_bit.irdaen = new_state;
}

/**
  * @brief  configure the usart's irda low power.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  new_state: new state of the irda mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_IRDA_Low_Power_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl3_bit.irdalp = new_state;
}

/**
  * @brief  configure the usart's hardware flow control.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3
  * @param  flow_state: 指定hardware flow control.
  *         该参数可以是以下值之一:
  *         - USART_Hardware_Flow_NONE
  *         - USART_Hardware_Flow_RTS,
  *         - USART_Hardware_Flow_CTS,
  *         - USART_Hardware_Flow_RTS_CTS
  * @retval 无
  */
void USART_Hardware_Flow_Control_Set(USART_Type* USART_x, USART_Hardware_Flow_Control_Type flow_state) {
    if(flow_state == USART_Hardware_Flow_NONE) {
        USART_x->ctrl3_bit.rtsen = FALSE;
        USART_x->ctrl3_bit.ctsen = FALSE;
    } else if(flow_state == USART_Hardware_Flow_RTS) {
        USART_x->ctrl3_bit.rtsen = TRUE;
        USART_x->ctrl3_bit.ctsen = FALSE;
    } else if(flow_state == USART_Hardware_Flow_CTS) {
        USART_x->ctrl3_bit.rtsen = FALSE;
        USART_x->ctrl3_bit.ctsen = TRUE;
    } else if(flow_state == USART_Hardware_Flow_RTS_CTS) {
        USART_x->ctrl3_bit.rtsen = TRUE;
        USART_x->ctrl3_bit.ctsen = TRUE;
    }
}

/**
  * @brief  check whether the specified usart flag is set or not.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - USART_CTSCF_FLAG: cts change flag (not available for UART4,UART5,USART6,UART7 and UART8)
  *         - USART_BFF_FLAG:   break frame flag
  *         - USART_TDBE_FLAG:  transmit data buffer empty flag
  *         - USART_TDC_FLAG:   transmit data complete flag
  *         - USART_RDBF_FLAG:  receive data buffer full flag
  *         - USART_IDLEF_FLAG: idle flag
  *         - USART_ROERR_FLAG: receiver overflow error flag
  *         - USART_NERR_FLAG:  noise error flag
  *         - USART_FERR_FLAG:  framing error flag
  *         - USART_PERR_FLAG:  parity error flag
  * @retval the new state of USART_flag (SET or RESET).
  */
flag_status USART_Flag_Get(USART_Type* USART_x, uint32_t flag) {
    if(USART_x->sts & flag) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  clear the usart's pending flags.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7 or UART8.
  * @param  flag: 指定flag to clear.
  *         该参数可以是以下值的任意组合:
  *         - USART_CTSCF_FLAG: (not available for UART4,UART5,USART6,UART7 and UART8).
  *         - USART_BFF_FLAG:
  *         - USART_TDC_FLAG:
  *         - USART_RDBF_FLAG:
  *         - USART_PERR_FLAG:
  *         - USART_FERR_FLAG:
  *         - USART_NERR_FLAG:
  *         - USART_ROERR_FLAG:
  *         - USART_IDLEF_FLAG:
  * @note
  *         - USART_PERR_FLAG, USART_FERR_FLAG, USART_NERR_FLAG, USART_ROERR_FLAG and USART_IDLEF_FLAG are cleared by software
  *           sequence: a read operation to usart sts register (USART_Flag_Get())
  *           followed by a read operation to usart dt register (USART_Data_Receive()).
  *         - USART_RDBF_FLAG can be also cleared by a read to the usart dt register(USART_Data_Receive()).
  *         - USART_TDC_FLAG can be also cleared by software sequence: a read operation to usart sts register (USART_Flag_Get())
  *           followed by a write operation to usart dt register (USART_Data_Transmit()).
  *         - USART_TDBE_FLAG is cleared only by a write to the usart dt register(USART_Data_Transmit()).
  * @retval 无
  */
void USART_Flag_Clear(USART_Type* USART_x, uint32_t flag) {
    if(flag & (USART_PERR_FLAG | USART_FERR_FLAG | USART_NERR_FLAG | USART_ROERR_FLAG | USART_IDLEF_FLAG)) {
        UNUSED(USART_x->sts);
        UNUSED(USART_x->dt);
    } else {
        USART_x->sts = ~flag;
    }
}

/**
  * @brief  configure the usart's rs485 transmit delay time.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3
  * @param  start_Delay_time: transmit start delay time.
  * @param  complete_Delay_time: transmit complete delay time.
  * @retval 无
  */
void USART_RS485_Delay_Time_Config(USART_Type* USART_x, uint8_t start_Delay_time, uint8_t complete_Delay_time) {
    USART_x->ctrl1_bit.tsdt = start_Delay_time;
    USART_x->ctrl1_bit.tcdt = complete_Delay_time;
}

/**
  * @brief  swap the usart's transmit receive pin.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7,or UART8.
  * @param  new_state: new state of the usart peripheral.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_Transmit_Receive_Pin_Swap(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl2_bit.trpswap = new_state;
}

/**
  * @brief  set the usart's identification bit num.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3, UART4, UART5, USART6, UART7,or UART8.
  * @param  id_Bit_Num: the usart wakeup identification bit num.
  *         该参数可以是: USART_ID_FIXED_4_BIT or USART_ID_RELATED_Data_BIT.
  * @retval 无
  */
void USART_ID_Bit_Num_Set(USART_Type* USART_x, USART_identification_Bit_Num_Type id_Bit_Num) {
    USART_x->ctrl2_bit.idbn = (uint8_t)id_Bit_Num;
}

/**
  * @brief  set the usart's de polarity.
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3
  * @param  de_polarity: the usart de polarity selection.
  *         该参数可以是: USART_DE_Polarity_HIGH or USART_DE_Polarity_LOW.
  * @retval 无
  */
void USART_DE_Polarity_Set(USART_Type* USART_x, USART_DE_Polarity_Type de_polarity) {
    USART_x->ctrl3_bit.dep = (uint8_t)de_polarity;
}

/**
  * @brief  启用或禁用 Usart的rs485模式。
  * @param  USART_x: 选择usart或uart外设。
  *         该参数可以是以下值之一:
  *         USART1, USART2, USART3
  * @param  new_state: new state of the irda mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void USART_RS485_Mode_Enable(USART_Type* USART_x, confirm_state new_state) {
    USART_x->ctrl3_bit.rs485en = new_state;
}

#endif
