/**
  **************************************************************************
  * @file     at32f435_437_can.c
  * @brief    contains all the functions for the can firmware library
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
  * @{
  */

/** @defgroup CAN
  * @brief CAN driver modules
  * @{
  */

#ifdef CAN_MODULE_EnableD

/** @defgroup CAN_private_functions
  * @{
  */

/**
  * @brief  deinitialize the can peripheral registers to their default reset values.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @retval 无.
  */
void CAN_Reset(CAN_Type* CAN_x) {
    if(CAN_x == CAN1) {
        CRM_Periph_Reset(CRM_CAN1_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_CAN1_Periph_Reset, FALSE);
    } else if(CAN_x == CAN2) {
        CRM_Periph_Reset(CRM_CAN2_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_CAN2_Periph_Reset, FALSE);
    }
}

/**
  * @brief  fill each CAN_Baudrate_struct member with its default value.
  * @param  CAN_Baudrate_struct: pointer to a CAN_Baudrate_Type structure which will be initialized.
  * @retval 无.
  */
void CAN_Baudrate_Default_Para_Init(CAN_Baudrate_Type* CAN_Baudrate_struct) {
    /* reset can baudrate structure parameters values */

    /* baud rate division */
    CAN_Baudrate_struct->baudrate_div = 1;

    /* resynchronization adjust width */
    CAN_Baudrate_struct->rsaw_size = CAN_RSAW_2TQ;

    /* bit time segment 1 */
    CAN_Baudrate_struct->bts1_size = CAN_BTS1_4TQ;

    /* bit time segment 2 */
    CAN_Baudrate_struct->bts2_size = CAN_BTS2_3TQ;
}

/**
  * @brief  set the baudrate of the can peripheral
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  CAN_Baudrate_struct: pointer to a CAN_Baudrate_Type structure which will be set.
  * @note   baudrate calculate method is:
  *         baudrate = fpclk/(baudrate_div *(3 + bts1_size + bts2_size))
  * @retval the result of baudrate set
  *         该参数可以是以下值之一:
  *         SUCCESS or ERROR
  */
error_status CAN_Baudrate_Set(CAN_Type* CAN_x, CAN_Baudrate_Type* CAN_Baudrate_struct) {
    error_status status_index = ERROR;
    uint32_t wait_ACK_index = 0x00000000;
    /* exit from doze mode */
    CAN_x->mctrl_bit.dzen = FALSE;

    /* request freeze mode */
    CAN_x->mctrl_bit.fzen = TRUE;

    /* wait the acknowledge */
    while((!CAN_x->msts_bit.fzc) && (wait_ACK_index != FZC_TIMEOUT)) {
        wait_ACK_index++;
    }

    /* check acknowledge */
    if(CAN_x->msts_bit.fzc) {
        CAN_x->btmg_bit.brdiv = CAN_Baudrate_struct->baudrate_div - 1;
        CAN_x->btmg_bit.rsaw = CAN_Baudrate_struct->rsaw_size;
        CAN_x->btmg_bit.bts1 = CAN_Baudrate_struct->bts1_size;
        CAN_x->btmg_bit.bts2 = CAN_Baudrate_struct->bts2_size;

        /* request leave freeze mode */
        CAN_x->mctrl_bit.fzen = FALSE;

        /* wait the acknowledge */
        wait_ACK_index = 0;

        while((CAN_x->msts_bit.fzc) && (wait_ACK_index != FZC_TIMEOUT)) {
            wait_ACK_index++;
        }

        /* check acknowledged */
        if(CAN_x->msts_bit.fzc) {
            status_index = ERROR;
        } else {
            status_index = SUCCESS ;
        }
    } else {
        status_index = ERROR;
    }

    /* return the status of baudrate set */
    return status_index;
}

/**
  * @brief  fill each CAN_Init_struct member with its default value.
  * @param  CAN_Base_struct: pointer to a CAN_Base_Type structure which will be initialized.
  * @retval 无.
  */
void CAN_Default_Para_Init(CAN_Base_Type* CAN_Base_struct) {
    /* reset can init structure parameters values */

    /* initialize the time triggered communication mode */
    CAN_Base_struct->ttc_Enable = FALSE;

    /* initialize the automatic exit bus-off management */
    CAN_Base_struct->aebo_Enable = FALSE;

    /* initialize the automatic exit doze mode */
    CAN_Base_struct->aed_Enable = FALSE;

    /* initialize the prohibit retransmission when sending fails */
    CAN_Base_struct->prsf_Enable = FALSE;

    /* initialize the message discarding rule select when overflow */
    CAN_Base_struct->mdrsel_Selection = CAN_DISCARDING_FIRST_ReceiveD;

    /* initialize the multiple message sending sequence rule */
    CAN_Base_struct->mmssr_Selection = CAN_SendING_BY_ID;

    /* initialize the CAN_Mode */
    CAN_Base_struct->mode_Selection = CAN_Mode_COMMUNICATE;
}

/**
  * @brief  initialize the can peripheral 根据 the specified
  *         parameters in the CAN_Init_struct.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  CAN_Base_struct: pointer to a CAN_Base_struct structure that contains the configuration information for the can peripheral.
  * @retval the status of initialization
  *         该参数可以是以下值之一:
  *         SUCCESS or ERROR
  */
error_status CAN_Base_Init(CAN_Type* CAN_x, CAN_Base_Type* CAN_Base_struct) {
    error_status init_Status_index = ERROR;
    uint32_t wait_ACK_index = 0x00000000;
    /* exit from doze mode */
    CAN_x->mctrl_bit.dzen = FALSE;

    /* request freeze mode */
    CAN_x->mctrl_bit.fzen = TRUE;

    /* wait the acknowledge */
    while((!CAN_x->msts_bit.fzc) && (wait_ACK_index != FZC_TIMEOUT)) {
        wait_ACK_index++;
    }

    /* check acknowledge */
    if(CAN_x->msts_bit.fzc) {
        /* set the time triggered communication mode */
        CAN_x->mctrl_bit.ttcen = CAN_Base_struct->ttc_Enable;

        /* set the automatic exit bus-off management */
        CAN_x->mctrl_bit.aeboen = CAN_Base_struct->aebo_Enable;

        /* set the automatic automatic exit doze mode */
        CAN_x->mctrl_bit.aeden = CAN_Base_struct->aed_Enable;

        /* set the prohibit retransmission when sending fails */
        CAN_x->mctrl_bit.prsfen = CAN_Base_struct->prsf_Enable;

        /* set the message discarding rule select when overflow */
        CAN_x->mctrl_bit.mdrsel = CAN_Base_struct->mdrsel_Selection;

        /* set the multiple message sending sequence rule */
        CAN_x->mctrl_bit.mmssr = CAN_Base_struct->mmssr_Selection;

        /* set the test mode */
        CAN_x->btmg_bit.lben = CAN_Base_struct->mode_Selection & 0x01;
        CAN_x->btmg_bit.loen = (CAN_Base_struct->mode_Selection >> 1) & 0x01;

        /* request leave freeze mode */
        CAN_x->mctrl_bit.fzen = FALSE;

        /* wait the acknowledge */
        wait_ACK_index = 0;

        while((CAN_x->msts_bit.fzc) && (wait_ACK_index != FZC_TIMEOUT)) {
            wait_ACK_index++;
        }

        /* check acknowledged */
        if(CAN_x->msts_bit.fzc) {
            init_Status_index = ERROR;
        } else {
            init_Status_index = SUCCESS ;
        }
    } else {
        init_Status_index = ERROR;
    }

    /* return the status of initialization */
    return init_Status_index;
}

/**
  * @brief  fill each CAN_Filter_Init_struct member with its default value.
  * @param  CAN_Filter_Init_struct: pointer to a CAN_Filter_Init_Type structure which will be initialized.
  * @retval 无.
  */
void CAN_Filter_Default_Para_Init(CAN_Filter_Init_Type* CAN_Filter_Init_struct) {
    /* reset can filter init structure parameters values */

    /* initialize the filter activate state */
    CAN_Filter_Init_struct->filter_activate_Enable = FALSE;

    /* filter mode */
    CAN_Filter_Init_struct->filter_Mode = CAN_Filter_Mode_ID_MASK;

    /* filter relation fifo select */
    CAN_Filter_Init_struct->filter_FIFO = CAN_Filter_FIFO0;

    /* filter number select */
    CAN_Filter_Init_struct->filter_Number = 0;

    /* initialize the filter bit width */
    CAN_Filter_Init_struct->filter_bit = CAN_Filter_16BIT;

    /* initialize the filters filter data bit */
    CAN_Filter_Init_struct->filter_ID_high = 0;
    CAN_Filter_Init_struct->filter_ID_low = 0;
    CAN_Filter_Init_struct->filter_Mask_high = 0;
    CAN_Filter_Init_struct->filter_Mask_low = 0;
}

/**
  * @brief  initialize the can peripheral 根据 the specified
  *         parameters in the CAN_Filter_Init_struct.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  CAN_Filter_Init_struct: pointer to a CAN_Filter_Init_Type structure that contains the configuration information.
  * @retval 无.
  */
void CAN_Filter_Init(CAN_Type* CAN_x, CAN_Filter_Init_Type* CAN_Filter_Init_struct) {
    uint32_t filter_Number_Bit_pos = 0;
    filter_Number_Bit_pos = ((uint32_t)1) << CAN_Filter_Init_struct->filter_Number;
    /* set the filter turn into configuration condition */
    CAN_x->fctrl_bit.fcs = TRUE;

    /* filter activate disable */
    CAN_x->facfg &= ~(uint32_t)filter_Number_Bit_pos;

    /* filter bit width */
    switch(CAN_Filter_Init_struct->filter_bit) {
        case CAN_Filter_16BIT:
            CAN_x->fbwcfg &= ~(uint32_t)filter_Number_Bit_pos;
            /* first 16-bit identifier and first 16-bit mask or first 16-bit identifier and second 16-bit identifier */
            CAN_x->ffb[CAN_Filter_Init_struct->filter_Number].ffdb1 = ((0x0000FFFF & (uint32_t)CAN_Filter_Init_struct->filter_Mask_low) << 16);
            CAN_x->ffb[CAN_Filter_Init_struct->filter_Number].ffdb1 |= (0x0000FFFF & (uint32_t)CAN_Filter_Init_struct->filter_ID_low);

            /* second 16-bit identifier and second 16-bit mask or third 16-bit identifier and fourth 16-bit identifier */
            CAN_x->ffb[CAN_Filter_Init_struct->filter_Number].ffdb2 = ((0x0000FFFF & (uint32_t)CAN_Filter_Init_struct->filter_Mask_high) << 16);
            CAN_x->ffb[CAN_Filter_Init_struct->filter_Number].ffdb2 |= (0x0000FFFF & (uint32_t)CAN_Filter_Init_struct->filter_ID_high);

            break;

        case CAN_Filter_32BIT:
            CAN_x->fbwcfg |= filter_Number_Bit_pos;
            /* 32-bit identifier or first 32-bit identifier */
            CAN_x->ffb[CAN_Filter_Init_struct->filter_Number].ffdb1 = ((0x0000FFFF & (uint32_t)CAN_Filter_Init_struct->filter_ID_high) << 16);
            CAN_x->ffb[CAN_Filter_Init_struct->filter_Number].ffdb1 |= (0x0000FFFF & (uint32_t)CAN_Filter_Init_struct->filter_ID_low);

            /* 32-bit mask or second 32-bit identifier */
            CAN_x->ffb[CAN_Filter_Init_struct->filter_Number].ffdb2 = ((0x0000FFFF & (uint32_t)CAN_Filter_Init_struct->filter_Mask_high) << 16);
            CAN_x->ffb[CAN_Filter_Init_struct->filter_Number].ffdb2 |= (0x0000FFFF & (uint32_t)CAN_Filter_Init_struct->filter_Mask_low);

            break;

        default:
            break;
    }

    /* filter mode */
    switch(CAN_Filter_Init_struct->filter_Mode) {
        case CAN_Filter_Mode_ID_MASK:
            CAN_x->fmcfg &= ~(uint32_t)filter_Number_Bit_pos;
            break;

        case CAN_Filter_Mode_ID_LIST:
            CAN_x->fmcfg |= (uint32_t)filter_Number_Bit_pos;
            break;

        default:
            break;
    }

    /* filter relation fifo select */
    switch(CAN_Filter_Init_struct->filter_FIFO) {
        case CAN_Filter_FIFO0:
            CAN_x->frf &= ~(uint32_t)filter_Number_Bit_pos;
            break;

        case CAN_Filter_FIFO1:
            CAN_x->frf |= (uint32_t)filter_Number_Bit_pos;
            break;

        default:
            break;
    }

    /* filter activate enable */
    switch(CAN_Filter_Init_struct->filter_activate_Enable) {
        case TRUE:
            CAN_x->facfg |= (uint32_t)filter_Number_Bit_pos;
            break;

        case FALSE:
            CAN_x->facfg &= ~(uint32_t)filter_Number_Bit_pos;
            break;

        default:
            break;
    }

    /* set the filter turn into working condition */
    CAN_x->fctrl_bit.fcs = FALSE;
}

/**
  * @brief  enable or disable the debug transmission prohibit of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  new_state: new state of debug transmission prohibit.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无.
  */
void CAN_DEBUG_Transmission_Prohibit(CAN_Type* CAN_x, confirm_state new_state) {
    CAN_x->mctrl_bit.ptd = new_state;
}

/**
  * @brief  enable or disable time trigger operation communication mode of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1 or CAN2.
  * @param  new_state : new state of time trigger operation communication mode.
  *         该参数可以是: TRUE or FALSE.
  * @note
  *         note1:
  *         when enabled, transmit mailbox time stamp(tmts[15:0]) value is sent in the last two data bytes of
  *         the 8-byte message: tmts[7:0] in data byte 6 and tmts[15:8] in data byte 7
  * @note
  *         note2:
  *         tmdtbl must be programmed as 8 in order time stamp (2 bytes) to be sent over the can bus.
  * @retval 无
  */
void CAN_ttc_Mode_Enable(CAN_Type* CAN_x, confirm_state new_state) {
    /* config the ttc mode new_state */
    CAN_x->mctrl_bit.ttcen = new_state;

    /* config tmtsten bits new_state */
    CAN_x->tx_mailbox[0].tmc_bit.tmtsten = new_state;
    CAN_x->tx_mailbox[1].tmc_bit.tmtsten = new_state;
    CAN_x->tx_mailbox[2].tmc_bit.tmtsten = new_state;
}

/**
  * @brief  fill the transmission message and transmit of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  tx_Message_struct: pointer to a structure which contains the message to be trans.
  * @retval the number of the mailbox that is used for transmission:
  *         该参数可以是以下值之一:
  *         - CAN_TX_MAILBOX0
  *         - CAN_TX_MAILBOX1
  *         - CAN_TX_MAILBOX2
  *         - CAN_TX_Status_NO_EMPTY <meanings there is no empty mailbox, message cannot be filled>
  */
uint8_t CAN_Message_Transmit(CAN_Type* CAN_x, CAN_TX_Message_Type* tx_Message_struct) {
    uint8_t transmit_mailbox = CAN_TX_Status_NO_EMPTY;

    /* select one empty transmit mailbox */
    if(CAN_x->tsts_bit.tm0ef) {
        transmit_mailbox = CAN_TX_MAILBOX0;
    } else if(CAN_x->tsts_bit.tm1ef) {
        transmit_mailbox = CAN_TX_MAILBOX1;
    } else if(CAN_x->tsts_bit.tm2ef) {
        transmit_mailbox = CAN_TX_MAILBOX2;
    } else {
        transmit_mailbox = CAN_TX_Status_NO_EMPTY;
    }

    if(transmit_mailbox != CAN_TX_Status_NO_EMPTY) {
        /* set up the id */
        CAN_x->tx_mailbox[transmit_mailbox].tmi &= 0x00000001;
        CAN_x->tx_mailbox[transmit_mailbox].tmi_bit.tmidsel = tx_Message_struct->id_Type;

        switch(tx_Message_struct->id_Type) {
            case CAN_ID_STANDARD:
                CAN_x->tx_mailbox[transmit_mailbox].tmi_bit.tmsid = tx_Message_struct->standard_id;
                break;

            case CAN_ID_EXTENDED:
                CAN_x->tx_mailbox[transmit_mailbox].tmi |= (tx_Message_struct->extended_id << 3);
                break;

            default:
                break;
        }

        CAN_x->tx_mailbox[transmit_mailbox].tmi_bit.tmfrsel = tx_Message_struct->frame_Type;
        /* set up the dlc */
        CAN_x->tx_mailbox[transmit_mailbox].tmc_bit.tmdtbl = (tx_Message_struct->dlc & ((uint8_t)0x0F));

        /* set up the data field */
        CAN_x->tx_mailbox[transmit_mailbox].tmdtl = (((uint32_t)tx_Message_struct->data[3] << 24) |
                ((uint32_t)tx_Message_struct->data[2] << 16) |
                ((uint32_t)tx_Message_struct->data[1] << 8) |
                ((uint32_t)tx_Message_struct->data[0]));
        CAN_x->tx_mailbox[transmit_mailbox].tmdth = (((uint32_t)tx_Message_struct->data[7] << 24) |
                ((uint32_t)tx_Message_struct->data[6] << 16) |
                ((uint32_t)tx_Message_struct->data[5] << 8) |
                ((uint32_t)tx_Message_struct->data[4]));

        /* request transmission */
        CAN_x->tx_mailbox[transmit_mailbox].tmi_bit.tmsr = TRUE;
    }

    return transmit_mailbox;
}

/**
  * @brief  check the transmission state of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1 or CAN2.
  * @param  transmit_mailbox: the number of the mailbox that is used for transmission.
  *         该参数可以是以下值之一:
  *         - CAN_TX_MAILBOX0
  *         - CAN_TX_MAILBOX1
  *         - CAN_TX_MAILBOX2
  * @retval can transmit status
  *         该参数可以是以下值之一:
  *         - CAN_TX_Status_SUCCESSFUL
  *         - CAN_TX_Status_FAILED
  *         - CAN_TX_Status_PENDING
  */
CAN_Transmit_Status_Type CAN_Transmit_Status_Get(CAN_Type* CAN_x, CAN_TX_mailbox_Num_Type transmit_mailbox) {
    CAN_Transmit_Status_Type state_index = CAN_TX_Status_FAILED;

    switch(transmit_mailbox) {
        case CAN_TX_MAILBOX0:
            if(CAN_x->tsts_bit.tm0tcf != RESET) {
                if(CAN_x->tsts_bit.tm0tsf != RESET) {
                    state_index = CAN_TX_Status_SUCCESSFUL;
                } else {
                    state_index = CAN_TX_Status_FAILED;
                }
            } else {
                state_index = CAN_TX_Status_PENDING;
            }

            break;

        case CAN_TX_MAILBOX1:
            if(CAN_x->tsts_bit.tm1tcf != RESET) {
                if(CAN_x->tsts_bit.tm1tsf != RESET) {
                    state_index = CAN_TX_Status_SUCCESSFUL;
                } else {
                    state_index = CAN_TX_Status_FAILED;
                }
            } else {
                state_index = CAN_TX_Status_PENDING;
            }

            break;

        case CAN_TX_MAILBOX2:
            if(CAN_x->tsts_bit.tm2tcf != RESET) {
                if(CAN_x->tsts_bit.tm2tsf != RESET) {
                    state_index = CAN_TX_Status_SUCCESSFUL;
                } else {
                    state_index = CAN_TX_Status_FAILED;
                }
            } else {
                state_index = CAN_TX_Status_PENDING;
            }

            break;

        default:
            state_index = CAN_TX_Status_FAILED;
            break;
    }

    return state_index;
}

/**
  * @brief  cancel a transmit request of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1 or CAN2.
  * @param  mailbox:  mailbox number.
  *         该参数可以是以下值之一:
  *         - CAN_TX_MAILBOX0
  *         - CAN_TX_MAILBOX1
  *         - CAN_TX_MAILBOX2
  * @retval 无.
  */
void CAN_Transmit_Cancel(CAN_Type* CAN_x, CAN_TX_mailbox_Num_Type transmit_mailbox) {
    switch (transmit_mailbox) {
        case CAN_TX_MAILBOX0:
            CAN_x->tsts = CAN_TSTS_TM0CT_VAL;
            break;

        case CAN_TX_MAILBOX1:
            CAN_x->tsts = CAN_TSTS_TM1CT_VAL;
            break;

        case CAN_TX_MAILBOX2:
            CAN_x->tsts = CAN_TSTS_TM2CT_VAL;
            break;

        default:
            break;
    }
}

/**
  * @brief  receive message of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  fifo_Number: receive fifo number.
  *         该参数可以是以下值之一:
  *         - CAN_RX_FIFO0
  *         - CAN_RX_FIFO1
  * @param  rx_Message_struct: pointer to a structure which store the receive message.
  * @retval 无.
  */
void CAN_Message_Receive(CAN_Type* CAN_x, CAN_RX_FIFO_Num_Type fifo_Number, CAN_RX_Message_Type* rx_Message_struct) {
    /* get the id type */
    rx_Message_struct->id_Type = (CAN_Identifier_Type)CAN_x->fifo_mailbox[fifo_Number].rfi_bit.rfidi;

    switch (rx_Message_struct->id_Type) {
        case CAN_ID_STANDARD:
            rx_Message_struct->standard_id = CAN_x->fifo_mailbox[fifo_Number].rfi_bit.rfsid;
            break;

        case CAN_ID_EXTENDED:
            rx_Message_struct->extended_id = 0x1FFFFFFF & (CAN_x->fifo_mailbox[fifo_Number].rfi >> 3);
            break;

        default:
            break;
    }

    rx_Message_struct->frame_Type = (CAN_trans_Frame_Type)CAN_x->fifo_mailbox[fifo_Number].rfi_bit.rffri;
    /* get the dlc */
    rx_Message_struct->dlc = CAN_x->fifo_mailbox[fifo_Number].rfc_bit.rfdtl;

    /* get the filter match number */
    rx_Message_struct->filter_index = CAN_x->fifo_mailbox[fifo_Number].rfc_bit.rffmn;

    /* get the data field */
    rx_Message_struct->data[0] = CAN_x->fifo_mailbox[fifo_Number].rfdtl_bit.rfdt0;
    rx_Message_struct->data[1] = CAN_x->fifo_mailbox[fifo_Number].rfdtl_bit.rfdt1;
    rx_Message_struct->data[2] = CAN_x->fifo_mailbox[fifo_Number].rfdtl_bit.rfdt2;
    rx_Message_struct->data[3] = CAN_x->fifo_mailbox[fifo_Number].rfdtl_bit.rfdt3;
    rx_Message_struct->data[4] = CAN_x->fifo_mailbox[fifo_Number].rfdth_bit.rfdt4;
    rx_Message_struct->data[5] = CAN_x->fifo_mailbox[fifo_Number].rfdth_bit.rfdt5;
    rx_Message_struct->data[6] = CAN_x->fifo_mailbox[fifo_Number].rfdth_bit.rfdt6;
    rx_Message_struct->data[7] = CAN_x->fifo_mailbox[fifo_Number].rfdth_bit.rfdt7;

    /* release the fifo */
    CAN_Receive_FIFO_release(CAN_x, fifo_Number);
}

/**
  * @brief  release the specified fifo of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  fifo_Number: fifo to be release.
  *         该参数可以是以下值之一:
  *         - CAN_RX_FIFO0
  *         - CAN_RX_FIFO1
  * @retval 无.
  */
void CAN_Receive_FIFO_release(CAN_Type* CAN_x, CAN_RX_FIFO_Num_Type fifo_Number) {
    switch (fifo_Number) {
        case CAN_RX_FIFO0:
            CAN_x->rf0 = CAN_RF0_RF0R_VAL;
            break;

        case CAN_RX_FIFO1:
            CAN_x->rf1 = CAN_RF1_RF1R_VAL;
            break;

        default:
            break;
    }
}

/**
  * @brief  return the number of pending messages of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  fifo_Number: receive fifo number.
  *         该参数可以是以下值之一:
  *         - CAN_RX_FIFO0
  *         - CAN_RX_FIFO1
  * @retval the number of message pending in the receive fifo.
  */
uint8_t CAN_Receive_Message_pending_Get(CAN_Type* CAN_x, CAN_RX_FIFO_Num_Type fifo_Number) {
    uint8_t message_pending = 0;

    switch (fifo_Number) {
        case CAN_RX_FIFO0:
            message_pending = CAN_x->rf0_bit.rf0mn;
            break;

        case CAN_RX_FIFO1:
            message_pending = CAN_x->rf1_bit.rf1mn;
            break;

        default:
            break;
    }

    return message_pending;
}

/**
  * @brief  set the operation mode of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  CAN_operating_Mode: can operating mode.
  *         该参数可以是以下值之一:
  *         - CAN_OPERATINGMODE_Freeze
  *         - CAN_OPERATINGMODE_DOZE
  *         - CAN_OPERATINGMODE_COMMUNICATE
  * @retval status of operation mode set
  *         该参数可以是以下值之一:
  *         SUCCESS or ERROR
  */
error_status CAN_operating_Mode_Set(CAN_Type* CAN_x, CAN_operating_Mode_Type CAN_operating_Mode) {
    error_status status = ERROR;
    uint32_t time_Out_index = FZC_TIMEOUT;

    if (CAN_operating_Mode == CAN_OPERATINGMODE_Freeze) {
        /* request enter freeze mode */
        CAN_x->mctrl_bit.dzen = FALSE;
        CAN_x->mctrl_bit.fzen = TRUE;

        while(((CAN_x->msts_bit.dzc) || (!CAN_x->msts_bit.fzc)) && (time_Out_index != 0)) {
            time_Out_index--;
        }

        if((CAN_x->msts_bit.dzc) || (!CAN_x->msts_bit.fzc)) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    } else if(CAN_operating_Mode == CAN_OPERATINGMODE_DOZE) {
        /* request enter doze mode */
        CAN_x->mctrl_bit.dzen = TRUE;
        CAN_x->mctrl_bit.fzen = FALSE;

        while(((!CAN_x->msts_bit.dzc) || (CAN_x->msts_bit.fzc)) && (time_Out_index != 0)) {
            time_Out_index--;
        }

        if((!CAN_x->msts_bit.dzc) || (CAN_x->msts_bit.fzc)) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    } else if(CAN_operating_Mode == CAN_OPERATINGMODE_COMMUNICATE) {
        /* request enter normal mode */
        CAN_x->mctrl_bit.dzen = FALSE;
        CAN_x->mctrl_bit.fzen = FALSE;

        while(((CAN_x->msts_bit.dzc) || (CAN_x->msts_bit.fzc)) && (time_Out_index != 0)) {
            time_Out_index--;
        }

        if((CAN_x->msts_bit.dzc) || (CAN_x->msts_bit.fzc)) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    } else {
        status = ERROR;
    }

    return status;
}

/**
  * @brief  enter the low power mode of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @retval status of doze mode enter, the returned value can be:
  *         - CAN_Enter_Doze_SUCCESSFUL  <it meaning enter the doze mode succeed>
  *         - CAN_Enter_Doze_FAILED  <it meaning enter the doze mode failed>
  */
CAN_Enter_Doze_Status_Type CAN_Doze_Mode_Enter(CAN_Type* CAN_x) {
    CAN_Enter_Doze_Status_Type status = CAN_Enter_Doze_FAILED;
    uint32_t time_Out_index = FZC_TIMEOUT;
    CAN_x->mctrl_bit.fzen = FALSE;
    CAN_x->mctrl_bit.dzen = TRUE;

    while(((!CAN_x->msts_bit.dzc) || (CAN_x->msts_bit.fzc)) && (time_Out_index != 0)) {
        time_Out_index--;
    }

    if((!CAN_x->msts_bit.dzc) || (CAN_x->msts_bit.fzc)) {
        status =  CAN_Enter_Doze_FAILED;
    } else {
        status =  CAN_Enter_Doze_SUCCESSFUL;
    }

    return status;
}

/**
  * @brief  exit the doze mode of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @retval status of doze mode enter, the returned value can be:
  *         - CAN_QUIT_Doze_SUCCESSFUL  <it meaning exit the doze mode succeed>
  *         - CAN_QUIT_Doze_FAILED  <it meaning exit the doze mode failed>
  */
CAN_quit_Doze_Status_Type CAN_Doze_Mode_Exit(CAN_Type* CAN_x) {
    CAN_quit_Doze_Status_Type status = CAN_QUIT_Doze_FAILED;
    uint32_t time_Out_index = DZC_TIMEOUT;
    CAN_x->mctrl_bit.dzen = FALSE;

    while((CAN_x->msts_bit.dzc) && (time_Out_index != 0)) {
        time_Out_index--;
    }

    if(!CAN_x->msts_bit.dzc) {
        status = CAN_QUIT_Doze_SUCCESSFUL;
    }

    return status;
}

/**
  * @brief  return the error type record (etr) of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @retval the value of the error code
  *         the return can be one of the follow values:
  *         - CAN_ERRORRECORD_NOERR
  *         - CAN_ERRORRECORD_STUFFERR,
  *         - CAN_ERRORRECORD_FORMERR,
  *         - CAN_ERRORRECORD_ACKERR,
  *         - CAN_ERRORRECORD_BITRECESSIVEERR,
  *         - CAN_ERRORRECORD_BITDOMINANTERR,
  *         - CAN_ERRORRECORD_CRCERR,
  *         - CAN_ERRORRECORD_SOFTWARESETERR
  */
CAN_Error_Record_Type CAN_Error_Type_Record_Get(CAN_Type* CAN_x) {
    CAN_Error_Record_Type error_code = CAN_ERRORRECORD_NOERR;

    error_code = (CAN_Error_Record_Type)CAN_x->ests_bit.etr;
    return error_code;
}

/**
  * @brief  return the receive error counter (rec) of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @retval the value of receive error counter.
  */
uint8_t CAN_Receive_Error_Counter_Get(CAN_Type* CAN_x) {
    uint8_t counter = 0;
    counter = CAN_x->ests_bit.rec;
    return counter;
}

/**
  * @brief  return the transmit error counter of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @retval the value of transmit error counter.
  */
uint8_t CAN_Transmit_Error_Counter_Get(CAN_Type* CAN_x) {
    uint8_t counter = 0;
    counter = CAN_x->ests_bit.tec;
    return counter;
}

/**
  * @brief  enable or disable the interrupt of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  CAN_int: 指定can interrupt sources to be enabled or disabled.
  *         该参数可以是以下值之一:
  *         - CAN_TCIEN_INT
  *         - CAN_RF0MIEN_INT
  *         - CAN_RF0FIEN_INT
  *         - CAN_RF0OIEN_INT
  *         - CAN_RF1MIEN_INT
  *         - CAN_RF1FIEN_INT
  *         - CAN_RF1OIEN_INT
  *         - CAN_EAIEN_INT
  *         - CAN_EPIEN_INT
  *         - CAN_BOIEN_INT
  *         - CAN_ETRIEN_INT
  *         - CAN_EOIEN_INT
  *         - CAN_QDZIEN_INT
  *         - CAN_EDZIEN_INT
  * @param  new_state: new state of the can interrupts.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无.
  */
void CAN_Interrupt_Enable(CAN_Type* CAN_x, uint32_t CAN_int, confirm_state new_state) {
    if (new_state != FALSE) {
        CAN_x->inten |= CAN_int;
    } else {
        CAN_x->inten &= ~CAN_int;
    }
}

/**
  * @brief  get flag of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  CAN_flag: select the flag.
  *         该参数可以是 one of the following flags:
  *         - CAN_EAF_FLAG
  *         - CAN_EPF_FLAG
  *         - CAN_BOF_FLAG
  *         - CAN_ETR_FLAG
  *         - CAN_EOIF_FLAG
  *         - CAN_TM0TCF_FLAG
  *         - CAN_TM1TCF_FLAG
  *         - CAN_TM2TCF_FLAG
  *         - CAN_RF0MN_FLAG
  *         - CAN_RF0FF_FLAG
  *         - CAN_RF0OF_FLAG
  *         - CAN_RF1MN_FLAG
  *         - CAN_RF1FF_FLAG
  *         - CAN_RF1OF_FLAG
  *         - CAN_QDZIF_FLAG
  *         - CAN_EDZC_FLAG
  *         - CAN_TMEF_FLAG
  *         note:the state of CAN_EDZC_FLAG need to check dzc and edzif bit
  *         note:the state of CAN_TMEF_FLAG need to check rqc0,rqc1 and rqc2 bit
  * @retval status of CAN_flag, the returned value can be:SET or RESET.
  */
flag_status CAN_Flag_Get(CAN_Type* CAN_x, uint32_t CAN_flag) {
    flag_status bit_status = RESET;

    switch(CAN_flag) {
        case CAN_EAF_FLAG:
            bit_status = (flag_status)CAN_x->ests_bit.eaf;
            break;

        case CAN_EPF_FLAG:
            bit_status = (flag_status)CAN_x->ests_bit.epf;
            break;

        case CAN_BOF_FLAG:
            bit_status = (flag_status)CAN_x->ests_bit.bof;
            break;

        case CAN_ETR_FLAG:
            if(CAN_x->ests_bit.etr != 0) {
                bit_status = SET;
            } else {
                bit_status = RESET;
            }

            break;

        case CAN_EOIF_FLAG:
            bit_status = (flag_status)CAN_x->msts_bit.eoif;
            break;

        case CAN_TM0TCF_FLAG:
            bit_status = (flag_status)CAN_x->tsts_bit.tm0tcf;
            break;

        case CAN_TM1TCF_FLAG:
            bit_status = (flag_status)CAN_x->tsts_bit.tm1tcf;
            break;

        case CAN_TM2TCF_FLAG:
            bit_status = (flag_status)CAN_x->tsts_bit.tm2tcf;
            break;

        case CAN_RF0MN_FLAG:
            if(CAN_x->rf0_bit.rf0mn != 0) {
                bit_status = SET;
            } else {
                bit_status = RESET;
            }

            break;

        case CAN_RF0FF_FLAG:
            bit_status = (flag_status)CAN_x->rf0_bit.rf0ff;
            break;

        case CAN_RF0OF_FLAG:
            bit_status = (flag_status)CAN_x->rf0_bit.rf0of;
            break;

        case CAN_RF1MN_FLAG:
            if(CAN_x->rf1_bit.rf1mn != 0) {
                bit_status = SET;
            } else {
                bit_status = RESET;
            }

            break;

        case CAN_RF1FF_FLAG:
            bit_status = (flag_status)CAN_x->rf1_bit.rf1ff;
            break;

        case CAN_RF1OF_FLAG:
            bit_status = (flag_status)CAN_x->rf1_bit.rf1of;
            break;

        case CAN_QDZIF_FLAG:
            bit_status = (flag_status)CAN_x->msts_bit.qdzif;
            break;

        case CAN_EDZC_FLAG:
            if((CAN_x->msts_bit.dzc != RESET) || (CAN_x->msts_bit.edzif != RESET)) {
                bit_status = SET;
            } else {
                bit_status = RESET;
            }

            break;

        case CAN_TMEF_FLAG:
            if((CAN_x->tsts_bit.tm0ef != RESET) || (CAN_x->tsts_bit.tm1ef != RESET) || (CAN_x->tsts_bit.tm2ef != RESET)) {
                bit_status = SET;
            } else {
                bit_status = RESET;
            }

            break;

        default:
            bit_status = RESET;
            break;
    }

    return bit_status;
}

/**
  * @brief  clear flag of the specified can peripheral.
  * @param  CAN_x: select the can peripheral.
  *         该参数可以是以下值之一:
  *         CAN1,CAN2.
  * @param  CAN_flag: select the flag.
  *         该参数可以是 one of the following flags:
  *         - CAN_EAF_FLAG
  *         - CAN_EPF_FLAG
  *         - CAN_BOF_FLAG
  *         - CAN_ETR_FLAG
  *         - CAN_EOIF_FLAG
  *         - CAN_TM0TCF_FLAG
  *         - CAN_TM1TCF_FLAG
  *         - CAN_TM2TCF_FLAG
  *         - CAN_RF0FF_FLAG
  *         - CAN_RF0OF_FLAG
  *         - CAN_RF1FF_FLAG
  *         - CAN_RF1OF_FLAG
  *         - CAN_QDZIF_FLAG
  *         - CAN_EDZC_FLAG
  *         - CAN_TMEF_FLAG
  *         note:CAN_RF0MN_FLAG and CAN_RF1MN_FLAG can not clear by this function
  * @retval 无.
  */
void CAN_Flag_Clear(CAN_Type* CAN_x, uint32_t CAN_flag) {
    switch(CAN_flag) {
        case CAN_EAF_FLAG:
        case CAN_EPF_FLAG:
        case CAN_BOF_FLAG:
        case CAN_EOIF_FLAG:
            CAN_x->msts = CAN_MSTS_EOIF_VAL;
            break;

        case CAN_ETR_FLAG:
            CAN_x->msts = CAN_MSTS_EOIF_VAL;
            CAN_x->ests = 0;
            break;

        case CAN_TM0TCF_FLAG:
            CAN_x->tsts = CAN_TSTS_TM0TCF_VAL;
            break;

        case CAN_TM1TCF_FLAG:
            CAN_x->tsts = CAN_TSTS_TM1TCF_VAL;
            break;

        case CAN_TM2TCF_FLAG:
            CAN_x->tsts = CAN_TSTS_TM2TCF_VAL;
            break;

        case CAN_RF0FF_FLAG:
            CAN_x->rf0 = CAN_RF0_RF0FF_VAL;
            break;

        case CAN_RF0OF_FLAG:
            CAN_x->rf0 = CAN_RF0_RF0OF_VAL;
            break;

        case CAN_RF1FF_FLAG:
            CAN_x->rf1 = CAN_RF1_RF1FF_VAL;
            break;

        case CAN_RF1OF_FLAG:
            CAN_x->rf1 = CAN_RF1_RF1OF_VAL;
            break;

        case CAN_QDZIF_FLAG:
            CAN_x->msts = CAN_MSTS_QDZIF_VAL;
            break;

        case CAN_EDZC_FLAG:
            CAN_x->msts = CAN_MSTS_EDZIF_VAL;
            break;

        case CAN_TMEF_FLAG:
            CAN_x->tsts = CAN_TSTS_TM0TCF_VAL | CAN_TSTS_TM1TCF_VAL | CAN_TSTS_TM2TCF_VAL;
            break;

        default:
            break;
    }
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
