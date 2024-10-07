/**
  **************************************************************************
  * @file     at32f435_437_emac.c
  * @brief    contains all the functions for the emac firmware library
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

/** @defgroup EMAC
  * @brief EMAC driver modules
  */

#ifdef EMAC_MODULE_EnableD

/** @defgroup EMAC_private_functions
  */

#if defined (EMAC_BASE)
/**
  * @brief global pointers on tx and rx descriptor used to track transmit and receive descriptors
  */
EMAC_DMA_Desc_Type  *DMA_TX_Desc_To_Set;
EMAC_DMA_Desc_Type  *DMA_RX_Desc_To_Get;

/* emac private function */
static void EMAC_delay(uint32_t delay);

/**
  * @brief  deinitialize the emac peripheral registers to their default reset values.
  * @param  无
  * @retval 无
  */
void EMAC_Reset(void) {
    CRM_Periph_Reset(CRM_EMAC_Periph_Reset, TRUE);
    CRM_Periph_Reset(CRM_EMAC_Periph_Reset, FALSE);
}

/**
  * @brief  initialize emac control structure
  * @param  EMAC_Control_Config_Type
  * @retval 无
  */
void EMAC_Control_Para_Init(EMAC_Control_Config_Type *control_para) {
    control_para->auto_nego = EMAC_Auto_NEGOTIATION_OFF;
    control_para->auto_pad_CRC_strip = FALSE;
    control_para->back_off_limit = EMAC_BackOff_Limit_0;
    control_para->carrier_Sense_Disable = FALSE;
    control_para->deferral_check = FALSE;
    control_para->duplex_Mode = EMAC_Half_DUPLEX;
    control_para->fast_ethernet_speed = EMAC_SPEED_10MBPS;
    control_para->interframe_gap = EMAC_INTERFRAME_Gap_96BIT;
    control_para->ipv4_checksum_offload = FALSE;
    control_para->jabber_Disable = FALSE;
    control_para->loopback_Mode = FALSE;
    control_para->receive_Own_Disable = FALSE;
    control_para->retry_Disable = FALSE;
    control_para->watchdog_Disable = FALSE;
}

/**
  * @brief  根据 hclk to set mdc clock frequency.
  * @param  无
  * @retval 无
  */
void EMAC_Clock_Range_Set(void) {
    uint8_t bits_value = 0;
    CRM_Clocks_Freq_Type clocks_freq = {0};

    /* clear clock range bits */
    EMAC->miiaddr_bit.cr = bits_value;

    CRM_Clocks_Freq_Get(&clocks_freq);

    if((clocks_freq.ahb_freq >= EMAC_HCLK_BORDER_20MHZ) && (clocks_freq.ahb_freq < EMAC_HCLK_BORDER_35MHZ)) {
        bits_value = EMAC_Clock_Range_20_To_35;
    } else if((clocks_freq.ahb_freq >= EMAC_HCLK_BORDER_35MHZ) && (clocks_freq.ahb_freq < EMAC_HCLK_BORDER_60MHZ)) {
        bits_value = EMAC_Clock_Range_35_To_60;
    } else if((clocks_freq.ahb_freq >= EMAC_HCLK_BORDER_60MHZ) && (clocks_freq.ahb_freq < EMAC_HCLK_BORDER_100MHZ)) {
        bits_value = EMAC_Clock_Range_60_To_100;
    } else if((clocks_freq.ahb_freq >= EMAC_HCLK_BORDER_100MHZ) && (clocks_freq.ahb_freq < EMAC_HCLK_BORDER_150MHZ)) {
        bits_value = EMAC_Clock_Range_100_To_150;
    } else if((clocks_freq.ahb_freq >= EMAC_HCLK_BORDER_150MHZ) && (clocks_freq.ahb_freq < EMAC_HCLK_BORDER_250MHZ)) {
        bits_value = EMAC_Clock_Range_150_To_250;
    } else if((clocks_freq.ahb_freq >= EMAC_HCLK_BORDER_250MHZ) && (clocks_freq.ahb_freq <= EMAC_HCLK_BORDER_288MHZ)) {
        bits_value = EMAC_Clock_Range_250_To_288;
    }

    EMAC->miiaddr_bit.cr = bits_value;
}

/**
  * @brief  configure emac control setting.
  * @param  control_struct: control setting of mac control register.
  * @retval 无
  */
void EMAC_Control_Config(EMAC_Control_Config_Type *control_struct) {
    EMAC_Deferral_Check_Set(control_struct->deferral_check);
    EMAC_BackOff_Limit_Set(control_struct->back_off_limit);
    EMAC_Auto_pad_CRC_Stripping_Set(control_struct->auto_pad_CRC_strip);
    EMAC_Retry_Disable(control_struct->retry_Disable);
    EMAC_Ipv4_checksum_offload_Set(control_struct->ipv4_checksum_offload);
    EMAC_Loopback_Mode_Enable(control_struct->loopback_Mode);
    EMAC_Receive_Own_Disable(control_struct->receive_Own_Disable);
    EMAC_Carrier_Sense_Disable(control_struct->carrier_Sense_Disable);
    EMAC_Interframe_Gap_Set(control_struct->interframe_gap);
    EMAC_Jabber_Disable(control_struct->jabber_Disable);
    EMAC_WatchDog_Disable(control_struct->watchdog_Disable);
}

/**
  * @brief  reset emac dma
  * @param  无
  * @retval 无
  */
void EMAC_DMA_Software_Reset_Set(void) {
    EMAC_DMA->bm_bit.swr = 1;
}

/**
  * @brief  get emac dma reset status
  * @param  无
  * @retval TRUE of FALSE
  */
flag_status EMAC_DMA_Software_Reset_Get(void) {
    if(EMAC_DMA->bm_bit.swr) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  enable emac and dma reception/transmission
  * @param  无
  * @retval 无
  */
void EMAC_Start(void) {
    /* enable transmit state machine of the mac for transmission on the mii */
    EMAC_Trasmitter_Enable(TRUE);

    /* flush transmit fifo */
    EMAC_DMA_Operations_Set(EMAC_DMA_OPS_Flush_Transmit_FIFO, TRUE);

    /* enable receive state machine of the mac for reception from the mii */
    EMAC_Receiver_Enable(TRUE);

    /* start dma transmission */
    EMAC_DMA_Operations_Set(EMAC_DMA_OPS_Start_Stop_Transmit, TRUE);

    /* start dma reception */
    EMAC_DMA_Operations_Set(EMAC_DMA_OPS_Start_Stop_Receive, TRUE);
}

/**
  * @brief  stop emac and dma reception/transmission
  * @param  无
  * @retval 无
  */
void EMAC_Stop(void) {
    /* stop dma transmission */
    EMAC_DMA_Operations_Set(EMAC_DMA_OPS_Start_Stop_Transmit, FALSE);

    /* stop dma reception */
    EMAC_DMA_Operations_Set(EMAC_DMA_OPS_Start_Stop_Receive, FALSE);

    /* stop receive state machine of the mac for reception from the mii */
    EMAC_Receiver_Enable(FALSE);

    /* flush transmit fifo */
    EMAC_DMA_Operations_Set(EMAC_DMA_OPS_Flush_Transmit_FIFO, TRUE);

    /* stop transmit state machine of the mac for transmission on the mii */
    EMAC_Trasmitter_Enable(FALSE);
}


/**
  * @brief  write phy data.
  * @param  address: phy address.
  * @param  reg: register of phy.
  * @param  data: value that wants to write to phy.
  * @retval SUCCESS or ERROR
  */
error_status EMAC_PHY_Register_Write(uint8_t address, uint8_t reg, uint16_t data) {
    uint32_t timeout = 0;

    EMAC->miidt_bit.md = data;

    EMAC->miiaddr_bit.pa = address;
    EMAC->miiaddr_bit.mii = reg;
    EMAC->miiaddr_bit.mw = 1;
    EMAC->miiaddr_bit.mb = 1;

    do {
        timeout++;
    } while((EMAC->miiaddr_bit.mb) && (timeout < PHY_TIMEOUT));

    if(timeout == PHY_TIMEOUT) {
        return ERROR;
    }

    return SUCCESS;
}

/**
  * @brief  read phy data
  * @param  address: phy address.
  * @param  reg: register of phy.
  * @param  data: value that is read from phy.
  * @retval SUCCESS or ERROR
  */
error_status EMAC_PHY_Register_Read(uint8_t address, uint8_t reg, uint16_t *data) {
    uint32_t timeout = 0;

    EMAC->miiaddr_bit.pa = address;
    EMAC->miiaddr_bit.mii = reg;
    EMAC->miiaddr_bit.mw = 0;
    EMAC->miiaddr_bit.mb = 1;

    do {
        timeout++;
        *data = EMAC->miidt_bit.md;
    } while((EMAC->miiaddr_bit.mb) && (timeout < PHY_TIMEOUT));

    if(timeout == PHY_TIMEOUT) {
        return ERROR;
    }

    *data = EMAC->miidt_bit.md;
    return SUCCESS;
}

/**
  * @brief  emac receiver enable.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Receiver_Enable(confirm_state new_state) {
    __IO uint32_t temp = 0;

    EMAC->ctrl_bit.re = new_state;

    temp = EMAC->ctrl;
    EMAC_delay(1);
    EMAC->ctrl = temp;
}

/**
  * @brief  emac transmitter enable.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Trasmitter_Enable(confirm_state new_state) {
    __IO uint32_t temp = 0;

    EMAC->ctrl_bit.te = new_state;

    temp = EMAC->ctrl;
    EMAC_delay(1);
    EMAC->ctrl = temp;
}

/**
  * @brief  emac defferal check enable, only avalible in half-duplex mode.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Deferral_Check_Set(confirm_state new_state) {
    EMAC->ctrl_bit.dc = new_state;
}

/**
  * @brief  emac back-off limit, only avalible in half-duplex mode.
  * @param  slot_time: waiting time of retransmission after collision
  *         该参数可以是以下值之一:
  *         - EMAC_BackOff_Limit_0
  *         - EMAC_BackOff_Limit_1
  *         - EMAC_BackOff_Limit_2
  *         - EMAC_BackOff_Limit_3
  * @retval 无
  */
void EMAC_BackOff_Limit_Set(EMAC_bol_Type slot_time) {
    EMAC->ctrl_bit.bl = slot_time;
}

/**
  * @brief  set mac automatic pad/CRC stripping.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Auto_pad_CRC_Stripping_Set(confirm_state new_state) {
    EMAC->ctrl_bit.acs = new_state;
}

/**
  * @brief  transmittion retry disable.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Retry_Disable(confirm_state new_state) {
    EMAC->ctrl_bit.dr = new_state;
}

/**
  * @brief  set ipv4 checksum offload.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Ipv4_checksum_offload_Set(confirm_state new_state) {
    EMAC->ctrl_bit.ipc = new_state;
}

/**
  * @brief  enable loopback mode.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Loopback_Mode_Enable(confirm_state new_state) {
    EMAC->ctrl_bit.lm = new_state;
}

/**
  * @brief  receive own disable.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Receive_Own_Disable(confirm_state new_state) {
    EMAC->ctrl_bit.dro = new_state;
}

/**
  * @brief  carrier sense disbale.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Carrier_Sense_Disable(confirm_state new_state) {
    EMAC->ctrl_bit.dcs = new_state;
}

/**
  * @brief  set minimum interframe gap between frames during transmission.
  * @param  number: interframe gap number.
  *         该参数可以是以下值之一:
  *         - EMAC_Frame_Gap_96BIT
  *         - EMAC_Frame_Gap_88BIT
  *         - EMAC_Frame_Gap_80BIT
  *         - EMAC_Frame_Gap_72BIT
  *         - EMAC_Frame_Gap_64BIT
  *         - EMAC_Frame_Gap_56BIT
  *         - EMAC_Frame_Gap_48BIT
  *         - EMAC_Frame_Gap_40BIT
  * @retval 无
  */
void EMAC_Interframe_Gap_Set(EMAC_intergrame_Gap_Type number) {
    EMAC->ctrl_bit.ifg = number;
}

/**
  * @brief  jabber disable.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Jabber_Disable(confirm_state new_state) {
    EMAC->ctrl_bit.jd = new_state;
}

/**
  * @brief  watchdog disable.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_WatchDog_Disable(confirm_state new_state) {
    EMAC->ctrl_bit.wd = new_state;
}

/**
  * @brief  set mac fast emac speed.
  * @param  speed: mac bandwidth
  *         该参数可以是以下值之一:
  *         - EMAC_SPEED_10MBPS
  *         - EMAC_SPEED_100MBPS
  * @retval 无
  */
void EMAC_Fast_Speed_Set(EMAC_Speed_Type speed) {
    EMAC->ctrl_bit.fes = speed;
}

/**
  * @brief  set duplex mode.
  * @param  duplex_Mode: communication mode
  *         该参数可以是以下值之一:
  *         - EMAC_Half_DUPLEX
  *         - EMAC_FULL_DUPLEX
  * @retval 无
  */
void EMAC_Duplex_Mode_Set(EMAC_Duplex_Type duplex_Mode) {
    EMAC->ctrl_bit.dm = duplex_Mode;
}

/**
  * @brief  set mac promiscuous mode.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Promiscuous_Mode_Set(confirm_state new_state) {
    EMAC->frmf_bit.pr = new_state;
}

/**
  * @brief  hash unicast.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Hash_Unicast_Set(confirm_state new_state) {
    EMAC->frmf_bit.huc = new_state;
}

/**
  * @brief  hash multicast.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Hash_MultiCast_Set(confirm_state new_state) {
    EMAC->frmf_bit.hmc = new_state;
}

/**
  * @brief  destination address inverse filtering.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Dstaddr_Inverse_Filter_Set(confirm_state new_state) {
    EMAC->frmf_bit.daif = new_state;
}

/**
  * @brief  pass all multicasting frames.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Pass_All_MultiCasting_Set(confirm_state new_state) {
    EMAC->frmf_bit.pmc = new_state;
}

/**
  * @brief  broadcast frames disable.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_broadcast_Frames_Disable(confirm_state new_state) {
    EMAC->frmf_bit.dbf = new_state;
}

/**
  * @brief  set mac how to pass control frames.
  * @param  condition: set what control frame can pass filter.
  *         该参数可以是以下值之一:
  *         - EMAC_Control_Frame_PASSING_NO
  *         - EMAC_Control_Frame_PASSING_ALL
  *         - EMAC_Control_Frame_PASSING_MATCH
  * @retval 无
  */
void EMAC_Pass_Control_Frames_Set(EMAC_Control_Frames_Filter_Type condition) {
    EMAC->frmf_bit.pcf = condition;
}

/**
  * @brief  source address inverse filtering.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Srcaddr_Inverse_Filter_Set(confirm_state new_state) {
    EMAC->frmf_bit.saif = new_state;
}

/**
  * @brief  source address filtering.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Srcaddr_Filter_Set(confirm_state new_state) {
    EMAC->frmf_bit.saf = new_state;
}

/**
  * @brief  mac uses hash or perfect filter.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Hash_Perfect_Filter_Set(confirm_state new_state) {
    EMAC->frmf_bit.hpf = new_state;
}

/**
  * @brief  mac receives all frames.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Receive_All_Set(confirm_state new_state) {
    EMAC->frmf_bit.ra = new_state;
}

/**
  * @brief  hash table high 32-bit.
  * @param  high32bits: the highest 32-bit of hash table.
  * @retval 无
  */
void EMAC_Hash_Table_High32bits_Set(uint32_t high32bits) {
    EMAC->hth_bit.hth = high32bits;
}

/**
  * @brief  hash table low 32-bit.
  * @param  low32bits: the lowest 32-bit of hash table.
  * @retval 无
  */
void EMAC_Hash_Table_Low32bits_Set(uint32_t low32bits) {
    EMAC->htl_bit.htl = low32bits;
}

/**
  * @brief  mii busy status.
  * @param  无
  * @retval SET or RESET
  */
flag_status EMAC_MII_Busy_Get(void) {
    if(EMAC->miiaddr_bit.mb) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  tell phy that will be written.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_MII_Write(confirm_state new_state) {
    EMAC->miiaddr_bit.mw = new_state;
}

/**
  * @brief  set flow control busy in full-duplex mode, back pressure activate in half-duplex mode.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_FCB_BPA_Set(confirm_state new_state) {
    EMAC->fctrl_bit.fcbbpa = new_state;
}

/**
  * @brief  set transmit flow control.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Transmit_Flow_Control_Enable(confirm_state new_state) {
    EMAC->fctrl_bit.etf = new_state;
}

/**
  * @brief  set receive flow control.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Receive_Flow_Control_Enable(confirm_state new_state) {
    EMAC->fctrl_bit.erf = new_state;
}

/**
  * @brief  set unicast pause frame detect.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Unicast_Pause_Frame_Detect(confirm_state new_state) {
    EMAC->fctrl_bit.dup = new_state;
}

/**
  * @brief  set pause low threshold.
  * @param  pasue_threshold: pause slot time.
  *         该参数可以是以下值之一:
  *         - EMAC_Pause_4_SLOT_TIME
  *         - EMAC_Pause_28_SLOT_TIME
  *         - EMAC_Pause_144_SLOT_TIME
  *         - EMAC_Pause_256_SLOT_TIME
  * @retval 无
  */
void EMAC_Pause_Low_Threshold_Set(EMAC_Pause_slot_Threshold_Type pasue_threshold) {
    EMAC->fctrl_bit.plt = pasue_threshold;
}

/**
  * @brief  set zero-quanta pause disable.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Zero_Quanta_Pause_Disable(confirm_state new_state) {
    EMAC->fctrl_bit.dzqp = new_state;
}

/**
  * @brief  set pause time.
  * @param  pause_time: time slots to pause transmit frame.
  * @retval 无
  */
void EMAC_Pause_Time_Set(uint16_t pause_time) {
    EMAC->fctrl_bit.pt = pause_time;
}

/**
  * @brief  identify coming vlan frame field with setting value.
  * @param  identifier: it will be compared with coming frame.
  * @retval 无
  */
void EMAC_Vlan_Tag_Identifier_Set(uint16_t identifier) {
    EMAC->vlt_bit.vti = identifier;
}

/**
  * @brief  set 12-bit vlan identifier.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Vlan_Tag_Comparison_Set(confirm_state new_state) {
    EMAC->vlt_bit.etv = new_state;
}

/**
  * @brief  set wakeup frame.
  * @param  value: it will be written to eight non transparent registers.
  * @retval 无
  */
void EMAC_WakeUp_Frame_Set(uint32_t value) {
    EMAC->rwff = value;
}

/**
  * @brief  get wakeup frame.
  * @param  无
  * @retval get value from eight non transparent registers.
  */
uint32_t EMAC_WakeUp_Frame_Get(void) {
    return (EMAC->rwff);
}

/**
  * @brief  all frame will be droppped except wakeup frame or magic packet.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Power_Down_Set(confirm_state new_state) {
    EMAC->pmtctrlsts_bit.pd = new_state;
}

/**
  * @brief  magic packet enable
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Magic_Packet_Enable(confirm_state new_state) {
    EMAC->pmtctrlsts_bit.emp = new_state;
}

/**
  * @brief  wakeup frame enable
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_WakeUp_Frame_Enable(confirm_state new_state) {
    EMAC->pmtctrlsts_bit.erwf = new_state;
}

/**
  * @brief  received magic packet
  * @param  无
  * @retval the new state of USART_flag (SET or RESET).
  */
flag_status EMAC_Received_Magic_Packet_Get(void) {
    if(EMAC->pmtctrlsts_bit.rmp) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  received wakeup frame.
  * @param  无
  * @retval the new state of USART_flag (SET or RESET).
  */
flag_status EMAC_Received_WakeUp_Frame_Get(void) {
    if(EMAC->pmtctrlsts_bit.rrwf) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  set unicast frame that passes DAF as wakeup frame.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Global_Unicast_Set(confirm_state new_state) {
    EMAC->pmtctrlsts_bit.guc = new_state;
}

/**
  * @brief  reset wakeup frame filter resgister
  * @param new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_WakeUp_Frame_Filter_Reset(confirm_state new_state) {
    EMAC->pmtctrlsts_bit.rwffpr = new_state;
}

/**
  * @brief  read interrupt status
  * @param  flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - EMAC_PMT_FLAG
  *         - EMAC_MMC_FLAG
  *         - EMAC_MMCR_FLAG
  *         - EMAC_MMCT_FLAG
  *         - EMAC_TST_FLAG
  * @retval the new state of USART_flag (SET or RESET).
  */
flag_status EMAC_Interrupt_Status_Read(uint32_t flag) {
    if(EMAC->ists & flag) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  set interrupt mask
  * @param  mask_Type: mask the interrupt signal
  *         该参数可以是以下值之一:
  *         - EMAC_Interrupt_PMT_MASK
  *         - EMAC_Interrupt_TST_MASK
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_Interrupt_Mask_Set(EMAC_Interrupt_Mask_Type mask_Type, confirm_state new_state) {
    switch(mask_Type) {
        case EMAC_Interrupt_PMT_MASK: {
            EMAC->imr_bit.pim = new_state;
            break;
        }

        case EMAC_Interrupt_TST_MASK: {
            EMAC->imr_bit.tim = new_state;
            break;
        }
    }
}

/**
  * @brief  set local mac address
  * @param  address: local address for mac0
  * @retval 无
  */
void EMAC_Local_Address_Set(uint8_t *address) {
    EMAC->a0h_bit.ma0h = (uint32_t)(address[5] << 8 | address[4]);
    EMAC->a0l_bit.ma0l = (uint32_t)(address[3] << 24 | address[2] << 16 | address[1] << 8 | address[0]);
}

/**
  * @brief  set mac filter address
  * @param  mac: select which mac you want to set
  *         该参数可以是以下值之一:
  *         - EMAC_Address_Filter_1
  *         - EMAC_Address_Filter_2
  *         - EMAC_Address_Filter_3
  * @retval 无
  */
void EMAC_Address_Filter_Set(EMAC_Address_Type mac, EMAC_Address_Filter_Type filter, EMAC_Address_Mask_Type mask_bit, confirm_state new_state) {
    switch(mac) {
        case EMAC_Address_Filter_1: {
            EMAC->a1h_bit.sa = filter;
            EMAC->a1h_bit.mbc = mask_bit;
            EMAC->a1h_bit.ae = new_state;
            break;
        }

        case EMAC_Address_Filter_2: {
            EMAC->a2h_bit.sa = filter;
            EMAC->a2h_bit.mbc = mask_bit;
            EMAC->a2h_bit.ae = new_state;
            break;
        }

        case EMAC_Address_Filter_3: {
            EMAC->a3h_bit.sa = filter;
            EMAC->a3h_bit.mbc = mask_bit;
            EMAC->a3h_bit.ae = new_state;
            break;
        }
    }
}

/**
  * @brief  set transmit/receive descriptor list address
  * @param  transfer_Type: it will be transmit or receive
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_Transmit
  *         - EMAC_DMA_Receive
  * @param  DMA_Desc_tab: pointer on the first tx desc list
  * @param  buff: pointer on the first tx/rx buffer list
  * @param  buffer_count: number of the used Tx desc in the list
  * @retval 无
  */
void EMAC_DMA_Descriptor_List_Address_Set(EMAC_DMA_TX_RX_Type transfer_Type, EMAC_DMA_Desc_Type *DMA_Desc_tab, uint8_t *buff, uint32_t buffer_count) {
    uint32_t i = 0;
    EMAC_DMA_Desc_Type *DMA_descriptor;

    switch(transfer_Type) {
        case EMAC_DMA_Transmit: {
            DMA_TX_Desc_To_Set = DMA_Desc_tab;

            for(i = 0; i < buffer_count; i++) {
                DMA_descriptor = DMA_Desc_tab + i;

                DMA_descriptor->status = EMAC_DMATXDESC_TCH;

                DMA_descriptor->buf1addr = (uint32_t)(&buff[i * EMAC_MAX_Packet_LENGTH]);

                if(i < (buffer_count - 1)) {
                    DMA_descriptor->buf2nextdescaddr = (uint32_t)(DMA_Desc_tab + i + 1);
                } else {
                    DMA_descriptor->buf2nextdescaddr = (uint32_t) DMA_Desc_tab;
                }
            }

            EMAC_DMA->tdladdr_bit.stl = (uint32_t) DMA_Desc_tab;
            break;
        }

        case EMAC_DMA_Receive: {
            DMA_RX_Desc_To_Get = DMA_Desc_tab;

            for(i = 0; i < buffer_count; i++) {
                DMA_descriptor = DMA_Desc_tab + i;

                DMA_descriptor->status = EMAC_DMARXDESC_OWN;

                DMA_descriptor->controlsize = EMAC_DMARXDESC_RCH | (uint32_t)EMAC_MAX_Packet_LENGTH;

                DMA_descriptor->buf1addr = (uint32_t)(&buff[i * EMAC_MAX_Packet_LENGTH]);

                if(i < (buffer_count - 1)) {
                    DMA_descriptor->buf2nextdescaddr = (uint32_t)(DMA_Desc_tab + i + 1);
                } else {
                    DMA_descriptor->buf2nextdescaddr = (uint32_t) DMA_Desc_tab;
                }
            }

            EMAC_DMA->rdladdr_bit.srl = (uint32_t) DMA_Desc_tab;
            break;
        }
    }
}

/**
  * @brief  enable or disable the specified dma rx descriptor receive interrupt
  * @param  DMA_RX_desc: pointer on a rx desc.
  * @param  new_state: new state of the specified dma rx descriptor interrupt.
  *         该参数可以是以下值之一:
  *         - TRUE
  *         - FALSE.
  * @retval 无
  */
void EMAC_DMA_RX_Desc_Interrupt_Config(EMAC_DMA_Desc_Type *DMA_RX_desc, confirm_state new_state) {
    if (new_state != FALSE) {
        /* enable the dma rx desc receive 中断 */
        DMA_RX_desc->controlsize &= (~(uint32_t)EMAC_DMARXDESC_DIC);
    } else {
        /* disable the dma rx desc receive 中断 */
        DMA_RX_desc->controlsize |= EMAC_DMARXDESC_DIC;
    }
}

/**
  * @brief  get transmit/receive descriptor list address
  * @param  transfer_Type: it will be transmit or receive
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_Transmit
  *         - EMAC_DMA_Receive
  * @retval transmit/receive descriptor list address
  */
uint32_t EMAC_DMA_Descriptor_List_Address_Get(EMAC_DMA_TX_RX_Type transfer_Type) {
    switch(transfer_Type) {
        case EMAC_DMA_Transmit: {
            return (EMAC_DMA->tdladdr_bit.stl);
        }

        case EMAC_DMA_Receive: {
            return (EMAC_DMA->rdladdr_bit.srl);
        }
    }

    return 0;
}

/**
  * @brief  get the size of received the received packet.
  * @param  无
  * @retval received packet size
  */
uint32_t EMAC_Received_Packet_size_Get(void) {
    uint32_t frame_length = 0;

    if(((DMA_RX_Desc_To_Get->status & EMAC_DMARXDESC_OWN) == (uint32_t)RESET) &&
            ((DMA_RX_Desc_To_Get->status & EMAC_DMATXDESC_ES) == (uint32_t)RESET) &&
            ((DMA_RX_Desc_To_Get->status & EMAC_DMARXDESC_LS) != (uint32_t)RESET) &&
            ((DMA_RX_Desc_To_Get->status & EMAC_DMARXDESC_FS) != (uint32_t)RESET)) {
        frame_length = EMAC_Dmarxdesc_Frame_Length_Get(DMA_RX_Desc_To_Get);
    }

    return frame_length;
}

/**
  * @brief  get the specified dma rx descsriptor frame length.
  * @param  DMA_RX_desc: pointer on a dma rx descriptor
  * @retval the rx descriptor received frame length.
  */
uint32_t EMAC_Dmarxdesc_Frame_Length_Get(EMAC_DMA_Desc_Type *DMA_RX_desc) {
    return ((DMA_RX_desc->status & EMAC_DMARXDESC_FL) >> EMAC_DMARXDESC_Frame_LENGTHSHIFT);
}

/**
  * @brief  init emac dma parameters
  * @param  EMAC_DMA_Config_Type
  * @retval 无
  */
void EMAC_DMA_Para_Init(EMAC_DMA_Config_Type *control_para) {
    control_para->aab_Enable = FALSE;
    control_para->da_Enable = FALSE;
    control_para->desc_Skip_length = 0;
    control_para->dt_Disable = FALSE;
    control_para->fb_Enable = FALSE;
    control_para->fef_Enable = FALSE;
    control_para->flush_RX_Disable = FALSE;
    control_para->fugf_Enable = FALSE;
    control_para->osf_Enable = FALSE;
    control_para->priority_ratio = EMAC_DMA_1_RX_1_TX;
    control_para->rsf_Enable = FALSE;
    control_para->rx_DMA_pal = EMAC_DMA_PBL_1;
    control_para->rx_threshold = EMAC_DMA_RX_Threshold_64_BYTES;
    control_para->tsf_Enable = FALSE;
    control_para->tx_DMA_pal = EMAC_DMA_PBL_1;
    control_para->tx_threshold = EMAC_DMA_TX_Threshold_64_BYTES;
    control_para->usp_Enable = FALSE;
}

/**
  * @brief  configure emac dma
  * @param  EMAC_DMA_Config_Type
  * @retval 无
  */
void EMAC_DMA_Config(EMAC_DMA_Config_Type *control_para) {
    EMAC_DMA->bm_bit.aab = control_para->aab_Enable;
    EMAC_DMA->bm_bit.dsl = control_para->desc_Skip_length;
    EMAC_DMA->bm_bit.rdp = control_para->rx_DMA_pal;
    EMAC_DMA->bm_bit.pbl = control_para->tx_DMA_pal;
    EMAC_DMA->bm_bit.fb = control_para->fb_Enable;
    EMAC_DMA->bm_bit.usp = control_para->usp_Enable;
    EMAC_DMA->bm_bit.da = control_para->da_Enable;
    EMAC_DMA->bm_bit.pr = control_para->priority_ratio;

    EMAC_DMA->opm_bit.dt = control_para->dt_Disable;
    EMAC_DMA->opm_bit.rsf = control_para->rsf_Enable;
    EMAC_DMA->opm_bit.dfrf = control_para->flush_RX_Disable;
    EMAC_DMA->opm_bit.tsf = control_para->tsf_Enable;
    EMAC_DMA->opm_bit.ttc = control_para->tx_threshold;
    EMAC_DMA->opm_bit.fef = control_para->fef_Enable;
    EMAC_DMA->opm_bit.fugf = control_para->fugf_Enable;
    EMAC_DMA->opm_bit.rtc = control_para->rx_threshold;
    EMAC_DMA->opm_bit.osf = control_para->osf_Enable;
}

/**
  * @brief  set rx tx priority
  * @param  ratio: rx tx priority ratio
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_1_RX_1_TX
  *         - EMAC_DMA_2_RX_1_TX
  *         - EMAC_DMA_3_RX_1_TX
  *         - EMAC_DMA_4_RX_1_TX
  * @param  new_state: TRUE or FALSE
  * @retval 无
  */
void EMAC_DMA_Arbitation_Set(EMAC_DMA_RX_TX_Ratio_Type ratio, confirm_state new_state) {
    EMAC_DMA->bm_bit.da = new_state;

    if(new_state) {
        EMAC_DMA->bm_bit.pr = ratio;
    }
}

/**
  * @brief  set descriptor skip mength
  * @param  length: descriptor skip length
  * @retval 无
  */
void EMAC_DMA_Descriptor_Skip_Length_Set(uint8_t length) {
    EMAC_DMA->bm_bit.dsl = length;
}

/**
  * @brief  set programmable burst length
  * @param  tx_length: tx programmable burst length
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_PBL_1
  *         - EMAC_DMA_PBL_2
  *         - EMAC_DMA_PBL_4
  *         - EMAC_DMA_PBL_8
  *         - EMAC_DMA_PBL_16
  *         - EMAC_DMA_PBL_32
  * @param  rx_length: rx programmable burst length
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_PBL_1
  *         - EMAC_DMA_PBL_2
  *         - EMAC_DMA_PBL_4
  *         - EMAC_DMA_PBL_8
  *         - EMAC_DMA_PBL_16
  *         - EMAC_DMA_PBL_32
  * @param  new_state: TRUE or FALSE
  * @retval 无
  */
void EMAC_DMA_Separate_pbl_Set(EMAC_DMA_pbl_Type tx_length, EMAC_DMA_pbl_Type rx_length, confirm_state new_state) {
    EMAC_DMA->bm_bit.usp = new_state;
    EMAC_DMA->bm_bit.pbl = tx_length;

    if(new_state) {
        EMAC_DMA->bm_bit.pbl = rx_length;
    }
}

/**
  * @brief  set 8 times programmable burst length
  * @param  new_state: TRUE or FALSE
  * @retval 无
  */
void EMAC_DMA_Eight_pbl_Mode_Set(confirm_state new_state) {
    EMAC_DMA->bm_bit.pblx8 = new_state;
}

/**
  * @brief  set address-aligned beats
  * @param  new_state: TRUE or FALSE
  * @retval 无
  */
void EMAC_DMA_Address_Aligned_Beats_Set(confirm_state new_state) {
    EMAC_DMA->bm_bit.aab = new_state;
}

/**
  * @brief  set transmit/receive poll demand
  * @param  transfer_Type: it will be transmit or receive
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_Transmit
  *         - EMAC_DMA_Receive
  * @param  value: it can be any number
  * @retval 无
  */
void EMAC_DMA_Poll_Demand_Set(EMAC_DMA_TX_RX_Type transfer_Type, uint32_t value) {
    switch(transfer_Type) {
        case EMAC_DMA_Transmit: {
            EMAC_DMA->tpd_bit.tpd = value;
            break;
        }

        case EMAC_DMA_Receive: {
            EMAC_DMA->rpd_bit.rpd = value;
            break;
        }
    }
}

/**
  * @brief  get transmit poll demand
  * @param  transfer_Type: it will be transmit or receive
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_Transmit
  *         - EMAC_DMA_Receive
  * @retval current transmit descriptor
  */
uint32_t EMAC_DMA_Poll_Demand_Get(EMAC_DMA_TX_RX_Type transfer_Type) {
    switch(transfer_Type) {
        case EMAC_DMA_Transmit: {
            return (EMAC_DMA->tpd_bit.tpd);
        }

        case EMAC_DMA_Receive: {
            return (EMAC_DMA->rpd_bit.rpd);
        }
    }

    return 0;
}

/**
  * @brief  get receive dma process status
  * @param  无
  * @retval every situation it describe in RM
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_RX_Reset_Stop_COMMAND
  *         - EMAC_DMA_RX_FETCH_DESCRIPTOR
  *         - EMAC_DMA_RX_WaitING_Packet
  *         - EMAC_DMA_RX_DESCRIPTOR_UNAVAILABLE
  *         - EMAC_DMA_RX_Close_DESCRIPTOR
  *         - EMAC_DMA_RX_FIFO_To_HOST
  */
EMAC_DMA_Receive_Process_Status_Type EMAC_DMA_Receive_Status_Get(void) {
    switch(EMAC_DMA->sts_bit.rs) {
        case EMAC_DMA_RX_Reset_Stop_COMMAND: {
            return EMAC_DMA_RX_Reset_Stop_COMMAND;
        }

        case EMAC_DMA_RX_FETCH_DESCRIPTOR: {
            return EMAC_DMA_RX_FETCH_DESCRIPTOR;
        }

        case EMAC_DMA_RX_WaitING_Packet: {
            return EMAC_DMA_RX_WaitING_Packet;
        }

        case EMAC_DMA_RX_DESCRIPTOR_UNAVAILABLE: {
            return EMAC_DMA_RX_DESCRIPTOR_UNAVAILABLE;
        }

        case EMAC_DMA_RX_Close_DESCRIPTOR: {
            return EMAC_DMA_RX_Close_DESCRIPTOR;
        }

        case EMAC_DMA_RX_FIFO_To_HOST: {
            return EMAC_DMA_RX_FIFO_To_HOST;
        }
    }

    return EMAC_DMA_RX_Reset_Stop_COMMAND;
}

/**
  * @brief  get transmit dma process status
  * @param  无
  * @retval every situation it describe in RM
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_TX_Reset_Stop_COMMAND
  *         - EMAC_DMA_TX_FETCH_DESCRIPTOR
  *         - EMAC_DMA_TX_WaitING_FOR_STATUS
  *         - EMAC_DMA_TX_HOST_To_FIFO
  *         - EMAC_DMA_TX_DESCRIPTOR_UNAVAILABLE
  *         - EMAC_DMA_TX_Close_DESCRIPTOR
  */
EMAC_DMA_Transmit_Process_Status_Type EMAC_DMA_Transmit_Status_Get(void) {
    switch(EMAC_DMA->sts_bit.ts) {
        case EMAC_DMA_TX_Reset_Stop_COMMAND: {
            return EMAC_DMA_TX_Reset_Stop_COMMAND;
        }

        case EMAC_DMA_TX_FETCH_DESCRIPTOR: {
            return EMAC_DMA_TX_FETCH_DESCRIPTOR;
        }

        case EMAC_DMA_TX_WaitING_FOR_STATUS: {
            return EMAC_DMA_TX_WaitING_FOR_STATUS;
        }

        case EMAC_DMA_TX_HOST_To_FIFO: {
            return EMAC_DMA_TX_HOST_To_FIFO;
        }

        case EMAC_DMA_TX_DESCRIPTOR_UNAVAILABLE: {
            return EMAC_DMA_TX_DESCRIPTOR_UNAVAILABLE;
        }

        case EMAC_DMA_TX_Close_DESCRIPTOR: {
            return EMAC_DMA_TX_Close_DESCRIPTOR;
        }
    }

    return EMAC_DMA_TX_Reset_Stop_COMMAND;
}

/**
  * @brief  set dma operations
  * @param  ops: operations of dma
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_OPS_Start_Stop_Receive
  *         - EMAC_DMA_OPS_Second_Frame
  *         - EMAC_DMA_OPS_FORWARD_UNDERSIZED
  *         - EMAC_DMA_OPS_FORWARD_ERROR
  *         - EMAC_DMA_OPS_Start_Stop_Transmit
  *         - EMAC_DMA_OPS_Flush_Transmit_FIFO
  *         - EMAC_DMA_OPS_Transmit_STORE_FORWARD
  *         - EMAC_DMA_OPS_Receive_Flush_Disable
  *         - EMAC_DMA_OPS_Receive_STORE_FORWARD
  *         - EMAC_DMA_OPS_DROP_Error_Disable
  * @param  new_state: TRUE or FALSE
  * @retval 无
  */
void EMAC_DMA_Operations_Set(EMAC_DMA_Operations_Type ops, confirm_state new_state) {
    __IO uint32_t temp = 0;

    switch(ops) {
        case EMAC_DMA_OPS_Start_Stop_Receive: {
            EMAC_DMA->opm_bit.ssr = new_state;
            break;
        }

        case EMAC_DMA_OPS_Second_Frame: {
            EMAC_DMA->opm_bit.osf = new_state;
            break;
        }

        case EMAC_DMA_OPS_FORWARD_UNDERSIZED: {
            EMAC_DMA->opm_bit.fugf = new_state;
            break;
        }

        case EMAC_DMA_OPS_FORWARD_ERROR: {
            EMAC_DMA->opm_bit.fef = new_state;
            break;
        }

        case EMAC_DMA_OPS_Start_Stop_Transmit: {
            EMAC_DMA->opm_bit.sstc = new_state;
            break;
        }

        case EMAC_DMA_OPS_Flush_Transmit_FIFO: {
            EMAC_DMA->opm_bit.ftf = new_state;
            temp = EMAC_DMA->opm;
            EMAC_delay(1);
            EMAC_DMA->opm = temp;
            break;
        }

        case EMAC_DMA_OPS_Transmit_STORE_FORWARD: {
            EMAC_DMA->opm_bit.tsf = new_state;
            break;
        }

        case EMAC_DMA_OPS_Receive_Flush_Disable: {
            EMAC_DMA->opm_bit.dfrf = new_state;
            break;
        }

        case EMAC_DMA_OPS_Receive_STORE_FORWARD: {
            EMAC_DMA->opm_bit.rsf = new_state;
            break;
        }

        case EMAC_DMA_OPS_DROP_Error_Disable: {
            EMAC_DMA->opm_bit.dt = new_state;
            break;
        }
    }
}

/**
  * @brief  set receive dma threshold
  * @param  value: receive threshold
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_RX_Threshold_64_BYTES
  *         - EMAC_DMA_RX_Threshold_32_BYTES
  *         - EMAC_DMA_RX_Threshold_96_BYTES
  *         - EMAC_DMA_RX_Threshold_128_BYTES
  * @retval 无
  */
void EMAC_DMA_Receive_Threshold_Set(EMAC_DMA_Receive_Threshold_Type value) {
    EMAC_DMA->opm_bit.rtc = value;
}

/**
  * @brief  set transmit dma threshold
  * @param  value: transmit threshold
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_TX_Threshold_64_BYTES
  *         - EMAC_DMA_TX_Threshold_128_BYTES
  *         - EMAC_DMA_TX_Threshold_192_BYTES
  *         - EMAC_DMA_TX_Threshold_256_BYTES
  *         - EMAC_DMA_TX_Threshold_40_BYTES
  *         - EMAC_DMA_TX_Threshold_32_BYTES
  *         - EMAC_DMA_TX_Threshold_24_BYTES
  *         - EMAC_DMA_TX_Threshold_16_BYTES
  * @retval 无
  */
void EMAC_DMA_Transmit_Threshold_Set(EMAC_DMA_Transmit_Threshold_Type value) {
    EMAC_DMA->opm_bit.ttc = value;
}

/**
  * @brief  enable dma interrupt
  * @param  it: interrupt type
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_Interrupt_TX
  *         - EMAC_DMA_Interrupt_TX_STOP
  *         - EMAC_DMA_Interrupt_TX_UNAVAILABLE
  *         - EMAC_DMA_Interrupt_TX_JABBER
  *         - EMAC_DMA_Interrupt_RX_OVERFLOW
  *         - EMAC_DMA_Interrupt_TX_UNDERFLOW
  *         - EMAC_DMA_Interrupt_RX
  *         - EMAC_DMA_Interrupt_RX_UNAVAILABLE
  *         - EMAC_DMA_Interrupt_RX_STOP
  *         - EMAC_DMA_Interrupt_RX_TIMEOUT
  *         - EMAC_DMA_Interrupt_TX_EARLY
  *         - EMAC_DMA_Interrupt_FATAL_Bus_ERROR
  *         - EMAC_DMA_Interrupt_RX_EARLY
  *         - EMAC_DMA_Interrupt_ABNORMAL_SUMMARY
  *         - EMAC_DMA_Interrupt_NORMAL_SUMMARY
  * @param  new_state: TRUE or FALSE
  * @retval 无
  */
void EMAC_DMA_Interrupt_Enable(EMAC_DMA_Interrupt_Type it, confirm_state new_state) {
    switch(it) {
        case EMAC_DMA_Interrupt_TX: {
            EMAC_DMA->ie_bit.tie = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_TX_STOP: {
            EMAC_DMA->ie_bit.tse = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_TX_UNAVAILABLE: {
            EMAC_DMA->ie_bit.tue = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_TX_JABBER: {
            EMAC_DMA->ie_bit.tje = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_RX_OVERFLOW: {
            EMAC_DMA->ie_bit.ove = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_TX_UNDERFLOW: {
            EMAC_DMA->ie_bit.une = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_RX: {
            EMAC_DMA->ie_bit.rie = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_RX_UNAVAILABLE: {
            EMAC_DMA->ie_bit.rbue = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_RX_STOP: {
            EMAC_DMA->ie_bit.rse = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_RX_TIMEOUT: {
            EMAC_DMA->ie_bit.rwte = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_TX_EARLY: {
            EMAC_DMA->ie_bit.eie = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_FATAL_Bus_ERROR: {
            EMAC_DMA->ie_bit.fbee = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_RX_EARLY: {
            EMAC_DMA->ie_bit.ere = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_ABNORMAL_SUMMARY: {
            EMAC_DMA->ie_bit.aie = new_state;
            break;
        }

        case EMAC_DMA_Interrupt_NORMAL_SUMMARY: {
            EMAC_DMA->ie_bit.nie = new_state;
            break;
        }
    }
}

/**
  * @brief  get missed frames by the controller
  * @param  无
  * @retval missed frames by the controller
  */
uint16_t EMAC_DMA_Controller_Missing_Frame_Get(void) {
    uint16_t number = EMAC_DMA->mfbocnt_bit.mfc;
    return number;
}

/**
  * @brief  get overflow bit for missed frame counter
  * @param  无
  * @retval overflow bit for missed frame counter
  */
uint8_t EMAC_DMA_Missing_OverFlow_Bit_Get(void) {
    uint8_t number = EMAC_DMA->mfbocnt_bit.obmfc;
    return number;
}

/**
  * @brief  get missed frames by the application
  * @param  无
  * @retval missed frames by the application
  */
uint16_t EMAC_DMA_Application_Missing_Frame_Get(void) {
    uint16_t number = EMAC_DMA->mfbocnt_bit.ofc;
    return number;
}

/**
  * @brief  get overflow bit for FIFO overflow counter
  * @param  无
  * @retval overflow bit for FIFO overflow counter
  */
uint8_t EMAC_DMA_FIFO_OverFlow_Bit_Get(void) {
    uint8_t number = EMAC_DMA->mfbocnt_bit.obfoc;
    return number;
}

/**
  * @brief  get overflow bit for FIFO overflow counter
  * @param  transfer type: receive/transmit type
  *         该参数可以是以下值之一:
  *         - EMAC_DMA_TX_DESCRIPTOR
  *         - EMAC_DMA_RX_DESCRIPTOR
  *         - EMAC_DMA_TX_BUFFER
  *         - EMAC_DMA_RX_BUFFER
  * @retval memory address
  */
uint32_t EMAC_DMA_tansfer_Address_Get(EMAC_DMA_Transfer_Address_Type transfer_Type) {
    uint32_t address = 0;

    switch(transfer_Type) {
        case EMAC_DMA_TX_DESCRIPTOR: {
            address = EMAC_DMA->ctd_bit.htdap;
            break;
        }

        case EMAC_DMA_RX_DESCRIPTOR: {
            address = EMAC_DMA->crd_bit.hrdap;
            break;
        }

        case EMAC_DMA_TX_BUFFER: {
            address = EMAC_DMA->ctbaddr_bit.htbap;
            break;
        }

        case EMAC_DMA_RX_BUFFER: {
            address = EMAC_DMA->crbaddr_bit.hrbap;
            break;
        }
    }

    return address;
}

/**
  * @brief  reset all counter
  * @param  无
  * @retval 无
  */
void EMAC_MMC_Counter_Reset(void) {
    EMAC_MMC->ctrl_bit.rc = TRUE;
}

/**
  * @brief  counter stop counting from zero when it reaches maximum
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_MMC_Rollover_Stop(confirm_state new_state) {
    EMAC_MMC->ctrl_bit.scr = new_state;
}

/**
  * @brief  enable reset on read
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_MMC_Reset_ON_Read_Enable(confirm_state new_state) {
    EMAC_MMC->ctrl_bit.rr = new_state;
}

/**
  * @brief  freeze mmc counter
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_MMC_Counter_Freeze(confirm_state new_state) {
    EMAC_MMC->ctrl_bit.fmc = new_state;
}

/**
  * @brief  interupt status of received frames
  * @param  flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - MMC_RX_CRC_ERROR
  *         - MMC_RX_ALIGN_ERROR
  *         - MMC_RX_Good_UNICAST
  * @retval the new state of USART_flag (SET or RESET).
  */
flag_status EMAC_MMC_Received_Status_Get(uint32_t flag) {
    if(EMAC_MMC->ri & flag) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  interupt status of transmit frames
  * @param  transmit_Type: transmit type.
  *         该参数可以是以下值之一:
  *         - MMC_TX_Single_COL
  *         - MMC_TX_MULTIPLE_COL
  *         - MMC_TX_Good_FrameS
  * @retval the new state of USART_flag (SET or RESET).
  */
flag_status EMAC_MMC_Transmit_Status_Get(uint32_t flag) {
    if(EMAC_MMC->ti & flag) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  mask received mmc interrupt
  * @param  flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - MMC_RX_CRC_ERROR
  *         - MMC_RX_ALIGN_ERROR
  *         - MMC_RX_Good_UNICAST
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_MMC_Received_Interrupt_Mask_Set(uint32_t flag, confirm_state new_state) {
    switch(flag) {
        case MMC_RX_CRC_ERROR: {
            EMAC_MMC->rim_bit.rcefcim = new_state;
            break;
        }

        case MMC_RX_ALIGN_ERROR: {
            EMAC_MMC->rim_bit.raefacim = new_state;
            break;
        }

        case MMC_RX_Good_UNICAST: {
            EMAC_MMC->rim_bit.rugfcim = new_state;
            break;
        }
    }
}

/**
  * @brief  mask transmit mmc interrupt
  * @param  transmit_Type: transmit type.
  *         该参数可以是以下值之一:
  *         - MMC_TX_Single_COL
  *         - MMC_TX_MULTIPLE_COL
  *         - MMC_TX_Good_FrameS
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_MMC_Transmit_Interrupt_Mask_Set(uint32_t flag, confirm_state new_state) {
    switch(flag) {
        case MMC_TX_Single_COL: {
            EMAC_MMC->tim_bit.tscgfcim = new_state;
            break;
        }

        case MMC_TX_MULTIPLE_COL: {
            EMAC_MMC->tim_bit.tmcgfcim = new_state;
            break;
        }

        case MMC_TX_Good_FrameS: {
            EMAC_MMC->tim_bit.tgfcim = new_state;
            break;
        }
    }
}

/**
  * @brief  get good frame numbers as single collision occurs.
  * @param  flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - MMC_TX_Single_COL
  *         - MMC_TX_MULTIPLE_COL
  *         - MMC_TX_Good_FrameS
  * @retval good frames
  */
uint32_t EMAC_MMC_Transmit_Good_Frames_Get(uint32_t flag) {
    uint32_t good_Frames = MMC_TX_Good_FrameS;

    switch(flag) {
        case MMC_TX_Single_COL: {
            good_Frames = EMAC_MMC->tfscc_bit.tgfscc;
            break;
        }

        case MMC_TX_MULTIPLE_COL: {
            good_Frames = EMAC_MMC->tfmscc_bit.tgfmscc;
            break;
        }

        case MMC_TX_Good_FrameS: {
            good_Frames = EMAC_MMC->tfcnt_bit.tgfc;
            break;
        }
    }

    return good_Frames;
}

/**
  * @brief  get good frame numbers as single collision occurs.
  * @param  flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - MMC_RX_CRC_ERROR
  *         - MMC_RX_ALIGN_ERROR
  *         - MMC_RX_Good_UNICAST
  * @retval good frames
  */
uint32_t EMAC_MMC_Received_Error_Frames_Get(uint32_t flag) {
    uint32_t error_Frames = MMC_RX_Good_UNICAST;

    switch(flag) {
        case MMC_RX_CRC_ERROR: {
            error_Frames = EMAC_MMC->rfcecnt_bit.rfcec;
            break;
        }

        case MMC_RX_ALIGN_ERROR: {
            error_Frames = EMAC_MMC->rfaecnt_bit.rfaec;
            break;
        }

        case MMC_RX_Good_UNICAST: {
            error_Frames = EMAC_MMC->rgufcnt_bit.rgufc;
            break;
        }
    }

    return error_Frames;
}

/**
  * @brief  enable timestamp.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_TimeStamp_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.te = new_state;
}

/**
  * @brief  enable timestamp fine update.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_TimeStamp_Fine_Update_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.tfcu = new_state;
}

/**
  * @brief  initialize timestamp time system.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_TimeStamp_System_Time_Init(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.ti = new_state;
}

/**
  * @brief  update timestamp time system.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_TimeStamp_System_Time_Update(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.tu = new_state;
}

/**
  * @brief  enable timestamp interrupt trigger.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_Interrupt_Trigger_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.tite = new_state;
}

/**
  * @brief  update timestamp addend register.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_Addend_Register_Update(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.aru = new_state;
}

/**
  * @brief  enable timestamp snapshot for all received frames.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_SnapShot_Received_Frames_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.etaf = new_state;
}

/**
  * @brief  enable digital rollover.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_SubSecond_Rollover_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.tdbrc = new_state;
}

/**
  * @brief  enable packet snooping for version 2.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_PSV2_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.eppv2f = new_state;
}

/**
  * @brief  enable snapshot over emac.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_SnapShot_EMAC_Frames_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.eppef = new_state;
}

/**
  * @brief  enable snapshot for ipv6 frames.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_SnapShot_Ipv6_Frames_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.eppfsip6u = new_state;
}

/**
  * @brief  enable snapshot for ipv4 frames.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_SnapShot_Ipv4_Frames_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.eppfsip4u = new_state;
}

/**
  * @brief  enable snapshot for event message.
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_SnapShot_Event_Message_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.etsfem = new_state;
}

/**
  * @brief  enable snapshot for message relevant to master
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_SnapShot_Master_Event_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.esfmrtm = new_state;
}

/**
  * @brief  set clock node type
  * @param  node: select ptp packets for taking snapshot
  *         该参数可以是以下值之一:
  *         - EMAC_PTP_NORMAL_CLOCK
  *         - EMAC_PTP_BOUNDARY_CLOCK
  *         - EMAC_PTP_End_To_End_CLOCK
  *         - EMAC_PTP_PEER_To_PEER_CLOCK
  * @retval 无
  */
void EMAC_PTP_Clock_Node_Set(EMAC_PTP_Clock_Node_Type node) {
    EMAC_PTP->tsctrl_bit.sppfts = node;
}

/**
  * @brief  enable ptp frame filtering mac address
  * @param  new_state: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_MAC_Address_Filter_Enable(confirm_state new_state) {
    EMAC_PTP->tsctrl_bit.emafpff = new_state;
}

/**
  * @brief  set subsecond increment value
  * @param  value: add to subsecond value for every update
  * @retval 无
  */
void EMAC_PTP_SubSecond_Increment_Set(uint8_t value) {
    EMAC_PTP->ssinc_bit.ssiv = value;
}

/**
  * @brief  get system time second
  * @param  无
  * @retval system time second
  */
uint32_t EMAC_PTP_System_Second_Get(void) {
    uint32_t second = EMAC_PTP->tsh_bit.ts;
    return second;
}

/**
  * @brief  get system time subsecond
  * @param  无
  * @retval system time subsecond
  */
uint32_t EMAC_PTP_System_SubSecond_Get(void) {
    uint32_t subsecond = EMAC_PTP->tsl_bit.tss;
    return subsecond;
}

/**
  * @brief  get system time sign
  * @param  无
  * @retval TRUE or FALSE
  */
confirm_state EMAC_PTP_System_Time_Sign_Get(void) {
    if(EMAC_PTP->tsl_bit.ast) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
  * @brief  set system time second
  * @param  second: system time second
  * @retval 无
  */
void EMAC_PTP_System_Second_Set(uint32_t second) {
    EMAC_PTP->tshud_bit.ts = second;
}

/**
  * @brief  set system time subsecond
  * @param  subsecond: system time subsecond
  * @retval 无
  */
void EMAC_PTP_System_SubSecond_Set(uint32_t subsecond) {
    EMAC_PTP->tslud_bit.tss = subsecond;
}

/**
  * @brief  set system time sign
  * @param  sign: TRUE or FALSE.
  * @retval 无
  */
void EMAC_PTP_System_Time_Sign_Set(confirm_state sign) {
    if(sign) {
        EMAC_PTP->tslud_bit.ast = 1;
    } else {
        EMAC_PTP->tslud_bit.ast = 0;
    }
}

/**
  * @brief  set time stamp addend
  * @param  value: to achieve time synchronization
  * @retval 无
  */
void EMAC_PTP_TimeStamp_Addend_Set(uint32_t value) {
    EMAC_PTP->tsad_bit.tar = value;
}

/**
  * @brief  set target time stamp high
  * @param  value: to set target time second
  * @retval 无
  */
void EMAC_PTP_Target_Second_Set(uint32_t value) {
    EMAC_PTP->tth_bit.ttsr = value;
}

/**
  * @brief  set target time stamp low
  * @param  value: to set target time nanosecond
  * @retval 无
  */
void EMAC_PTP_Target_NanoSecond_Set(uint32_t value) {
    EMAC_PTP->ttl_bit.ttlr = value;
}

/**
  * @brief  set target time stamp low
  * @param  status: type of status
  *         该参数可以是以下值之一:
  *         - EMAC_PTP_Second_OVERFLOW
  *         - EMAC_PTP_Target_Time_REACH
  * @retval TRUE or FALSE
  */
confirm_state EMAC_PTP_TimeStamp_Status_Get(EMAC_PTP_TimeStamp_Status_Type status) {
    switch(status) {
        case EMAC_PTP_Second_OVERFLOW: {
            if(EMAC_PTP->tssr_bit.tso) {
                return TRUE;
            } else {
                return FALSE;
            }
        }

        case EMAC_PTP_Target_Time_REACH: {
            if(EMAC_PTP->tssr_bit.tttr) {
                return TRUE;
            } else {
                return FALSE;
            }
        }
    }

    return FALSE;
}

/**
  * @brief  set pps frequency
  * @param  freq: pps frequency
  *         该参数可以是以下值之一:
  *         - EMAC_PTP_PPS_1HZ
  *         - EMAC_PTP_PPS_2HZ
  *         - EMAC_PTP_PPS_4HZ
  *         - EMAC_PTP_PPS_8HZ
  *         - EMAC_PTP_PPS_16HZ
  *         - EMAC_PTP_PPS_32HZ
  *         - EMAC_PTP_PPS_64HZ
  *         - EMAC_PTP_PPS_128HZ
  *         - EMAC_PTP_PPS_256HZ
  *         - EMAC_PTP_PPS_512HZ
  *         - EMAC_PTP_PPS_1024HZ
  *         - EMAC_PTP_PPS_2048HZ
  *         - EMAC_PTP_PPS_4096HZ
  *         - EMAC_PTP_PPS_8192HZ
  *         - EMAC_PTP_PPS_16384HZ
  *         - EMAC_PTP_PPS_32768HZ
  * @retval 无
  */
void EMAC_PTP_PPS_Frequency_Set(EMAC_PTP_PPS_Control_Type freq) {
    EMAC_PTP->ppscr_bit.pofc = freq;
}

/**
  * @brief  this is delay function base on system clock.
  * @param  delay: delay time
  * @retval 无
  */
static void EMAC_delay(uint32_t delay) {
    __IO uint32_t delay_time = delay * (system_Core_clock / 8 / 1000);

    do {
        __NOP();
    } while(delay_time --);
}

/**
  * @brief  check whether the specified emac dma flag is set or not.
  * @param  DMA_flag: 指定emac dma flag to check.
  *         该参数可以是 one of emac dma flag status:
  *         - EMAC_DMA_Ti_FLAG
  *         - EMAC_DMA_TPS_FLAG
  *         - EMAC_DMA_TBU_FLAG
  *         - EMAC_DMA_TJT_FLAG
  *         - EMAC_DMA_OVF_FLAG
  *         - EMAC_DMA_UNF_FLAG
  *         - EMAC_DMA_RI_FLAG
  *         - EMAC_DMA_RBU_FLAG
  *         - EMAC_DMA_RPS_FLAG
  *         - EMAC_DMA_RWT_FLAG
  *         - EMAC_DMA_ETI_FLAG
  *         - EMAC_DMA_FBEI_FLAG
  *         - EMAC_DMA_ERI_FLAG
  *         - EMAC_DMA_AIS_FLAG
  *         - EMAC_DMA_NIS_FLAG
  * @retval the new state of DMA_flag (SET or RESET).
  */
flag_status EMAC_DMA_Flag_Get(uint32_t DMA_flag) {
    flag_status status = RESET;

    if(EMAC_DMA->sts & DMA_flag)
        status = SET;

    /* return the new state (SET or RESET) */
    return status;
}

/**
  * @brief  clear the emac dma flag.
  * @param  DMA_flag: 指定emac dma flags to clear.
  *         该参数可以是以下值的任意组合:
  *         - EMAC_DMA_Ti_FLAG
  *         - EMAC_DMA_TPS_FLAG
  *         - EMAC_DMA_TBU_FLAG
  *         - EMAC_DMA_TJT_FLAG
  *         - EMAC_DMA_OVF_FLAG
  *         - EMAC_DMA_UNF_FLAG
  *         - EMAC_DMA_RI_FLAG
  *         - EMAC_DMA_RBU_FLAG
  *         - EMAC_DMA_RPS_FLAG
  *         - EMAC_DMA_RWT_FLAG
  *         - EMAC_DMA_ETI_FLAG
  *         - EMAC_DMA_FBEI_FLAG
  *         - EMAC_DMA_ERI_FLAG
  *         - EMAC_DMA_AIS_FLAG
  *         - EMAC_DMA_NIS_FLAG
  * @retval 无
  */
void EMAC_DMA_Flag_Clear(uint32_t DMA_flag) {
    EMAC_DMA->sts = DMA_flag;
}

#endif

#endif
