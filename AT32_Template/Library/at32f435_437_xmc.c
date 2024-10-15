/**
  **************************************************************************
  * @file     at32f435_437_xmc.c
  * @brief    contains all the functions for the xmc firmware library
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

/** @defgroup XMC
  * @brief XMC driver modules
  */

#ifdef XMC_MODULE_EnableD

/** @defgroup XMC_private_functions
  */

/**
  * @brief  xmc nor or sram registers reset
  * @param  XMC_subbank
  *         该参数可以是以下值之一:
  *         - XMC_Bank1_NOR_SRAM1
  *         - XMC_Bank1_NOR_SRAM2
  *         - XMC_Bank1_NOR_SRAM3
  *         - XMC_Bank1_NOR_SRAM4
  * @retval 无
  */
void XMC_NOR_SRAM_Reset(XMC_NOR_SRAM_SubBank_Type XMC_subbank) {
    /* XMC_Bank1_NORSRAM1 */
    if(XMC_subbank == XMC_Bank1_NOR_SRAM1) {
        XMC_BANK1->ctrl_tmg_group[XMC_subbank].bk1ctrl = 0x000030DB;
    }
    /* XMC_Bank1_NORSRAM2,  XMC_Bank1_NORSRAM3 or XMC_Bank1_NORSRAM4 */
    else {
        XMC_BANK1->ctrl_tmg_group[XMC_subbank].bk1ctrl = 0x000030D2;
    }

    XMC_BANK1->ctrl_tmg_group[XMC_subbank].bk1tmg = 0x0FFFFFFF;
    XMC_BANK1->tmgwr_group[XMC_subbank].bk1tmgwr = 0x0FFFFFFF;
}

/**
  * @brief  initialize the xmc nor/sram banks 根据 the specified
  *         parameters in the XMC_norsraminitstruct.
  * @param  XMC_NORSRAM_Init_struct : pointer to a XMC_NORSRAM_Init_Type
  *         structure that contains the configuration information for
  *         the xmc nor/sram specified banks.
  * @retval 无
  */
void XMC_NOR_SRAM_Init(XMC_NORSRAM_Init_Type* XMC_NORSRAM_Init_struct) {
    /* bank1 nor/sram control register configuration */
    XMC_BANK1->ctrl_tmg_group[XMC_NORSRAM_Init_struct->subbank].bk1ctrl =
        (uint32_t)XMC_NORSRAM_Init_struct->data_Addr_multiplex |
        XMC_NORSRAM_Init_struct->device |
        XMC_NORSRAM_Init_struct->bus_Type |
        XMC_NORSRAM_Init_struct->burst_Mode_Enable |
        XMC_NORSRAM_Init_struct->asynwait_Enable |
        XMC_NORSRAM_Init_struct->wait_signal_lv |
        XMC_NORSRAM_Init_struct->wrapped_Mode_Enable |
        XMC_NORSRAM_Init_struct->wait_signal_Config |
        XMC_NORSRAM_Init_struct->write_Enable |
        XMC_NORSRAM_Init_struct->wait_signal_Enable |
        XMC_NORSRAM_Init_struct->write_Timing_Enable |
        XMC_NORSRAM_Init_struct->write_Burst_syn;

    /* if nor flash device */
    if(XMC_NORSRAM_Init_struct->device == XMC_Device_NOR) {
        XMC_BANK1->ctrl_tmg_group[XMC_NORSRAM_Init_struct->subbank].bk1ctrl_bit.noren = 0x1;
    }
}

/**
  * @brief  initialize the xmc nor/sram banks 根据 the specified
  *         parameters in the XMC_rw_Timing_struct and XMC_w_Timing_struct.
  * @param  XMC_rw_Timing_struct : pointer to a XMC_NORSRAM_Timing_Init_Type
  *         structure that contains the configuration information for
  *         the xmc nor/sram specified banks.
  * @param  XMC_w_Timing_struct : pointer to a XMC_NORSRAM_Timing_Init_Type
  *         structure that contains the configuration information for
  *         the xmc nor/sram specified banks.
  * @retval 无
  */
void XMC_NOR_SRAM_Timing_Config(XMC_NORSRAM_Timing_Init_Type* XMC_rw_Timing_struct,
                                XMC_NORSRAM_Timing_Init_Type* XMC_w_Timing_struct) {
    /* bank1 nor/sram timing register configuration */
    XMC_BANK1->ctrl_tmg_group[XMC_rw_Timing_struct->subbank].bk1tmg =
        (uint32_t)XMC_rw_Timing_struct->addr_Setup_time |
        (XMC_rw_Timing_struct->addr_hold_time << 4) |
        (XMC_rw_Timing_struct->data_Setup_time << 8) |
        (XMC_rw_Timing_struct->bus_latency_time << 16) |
        (XMC_rw_Timing_struct->clk_psc << 20) |
        (XMC_rw_Timing_struct->data_latency_time << 24) |
        XMC_rw_Timing_struct->mode;

    /* bank1 nor/sram timing register for write configuration, if extended mode is used */
    if(XMC_rw_Timing_struct->write_Timing_Enable == XMC_Write_Timing_Enable) {
        XMC_BANK1->tmgwr_group[XMC_w_Timing_struct->subbank].bk1tmgwr =
            (uint32_t)XMC_w_Timing_struct->addr_Setup_time |
            (XMC_w_Timing_struct->addr_hold_time << 4) |
            (XMC_w_Timing_struct->data_Setup_time << 8) |
            (XMC_w_Timing_struct->bus_latency_time << 16) |
            (XMC_w_Timing_struct->clk_psc << 20) |
            (XMC_w_Timing_struct->data_latency_time << 24) |
            XMC_w_Timing_struct->mode;
    } else {
        XMC_BANK1->tmgwr_group[XMC_w_Timing_struct->subbank].bk1tmgwr = 0x0FFFFFFF;
    }
}

/**
  * @brief  fill each XMC_NOR_SRAM_Init_struct member with its default value.
  * @param  XMC_NOR_SRAM_Init_struct: pointer to a XMC_NORSRAM_Init_Type
  *         structure which will be initialized.
  * @retval 无
  */
void XMC_NORSRAM_Default_Para_Init(XMC_NORSRAM_Init_Type* XMC_NOR_SRAM_Init_struct) {
    /* reset nor/sram init structure parameters values */
    XMC_NOR_SRAM_Init_struct->subbank = XMC_Bank1_NOR_SRAM1;
    XMC_NOR_SRAM_Init_struct->data_Addr_multiplex = XMC_Data_Addr_MUX_Enable;
    XMC_NOR_SRAM_Init_struct->device = XMC_Device_SRAM;
    XMC_NOR_SRAM_Init_struct->bus_Type = XMC_BUSTYPE_8_BITS;
    XMC_NOR_SRAM_Init_struct->burst_Mode_Enable = XMC_Burst_Mode_Disable;
    XMC_NOR_SRAM_Init_struct->asynwait_Enable = XMC_ASYN_Wait_Disable;
    XMC_NOR_SRAM_Init_struct->wait_signal_lv = XMC_Wait_SIGNAL_LEVEL_LOW;
    XMC_NOR_SRAM_Init_struct->wrapped_Mode_Enable = XMC_WRAPPED_Mode_Disable;
    XMC_NOR_SRAM_Init_struct->wait_signal_Config = XMC_Wait_SIGNAL_SYN_BEFORE;
    XMC_NOR_SRAM_Init_struct->write_Enable = XMC_Write_Operation_Enable;
    XMC_NOR_SRAM_Init_struct->wait_signal_Enable = XMC_Wait_SIGNAL_Enable;
    XMC_NOR_SRAM_Init_struct->write_Timing_Enable = XMC_Write_Timing_Disable;
    XMC_NOR_SRAM_Init_struct->write_Burst_syn = XMC_Write_Burst_SYN_Disable;
}

/**
  * @brief  fill each XMC_rw_Timing_struct and XMC_w_Timing_struct member with its default value.
  * @param  XMC_rw_Timing_struct: pointer to a XMC_NORSRAM_Timing_Init_Type
  *         structure which will be initialized.
  * @param  XMC_w_Timing_struct: pointer to a XMC_NORSRAM_Timing_Init_Type
  *         structure which will be initialized.
  * @retval 无
  */
void XMC_NORSRAM_Timing_Default_Para_Init(XMC_NORSRAM_Timing_Init_Type* XMC_rw_Timing_struct,
        XMC_NORSRAM_Timing_Init_Type* XMC_w_Timing_struct) {
    XMC_rw_Timing_struct->subbank = XMC_Bank1_NOR_SRAM1;
    XMC_rw_Timing_struct->write_Timing_Enable = XMC_Write_Timing_Disable;
    XMC_rw_Timing_struct->addr_Setup_time = 0xF;
    XMC_rw_Timing_struct->addr_hold_time = 0xF;
    XMC_rw_Timing_struct->data_Setup_time = 0xFF;
    XMC_rw_Timing_struct->bus_latency_time = 0xF;
    XMC_rw_Timing_struct->clk_psc = 0xF;
    XMC_rw_Timing_struct->data_latency_time = 0xF;
    XMC_rw_Timing_struct->mode = XMC_Access_Mode_A;
    XMC_w_Timing_struct->subbank = XMC_Bank1_NOR_SRAM1;
    XMC_w_Timing_struct->write_Timing_Enable = XMC_Write_Timing_Disable;
    XMC_w_Timing_struct->addr_Setup_time = 0xF;
    XMC_w_Timing_struct->addr_hold_time = 0xF;
    XMC_w_Timing_struct->data_Setup_time = 0xFF;
    XMC_w_Timing_struct->bus_latency_time = 0xF;
    XMC_w_Timing_struct->clk_psc = 0xF;
    XMC_w_Timing_struct->data_latency_time = 0xF;
    XMC_w_Timing_struct->mode = XMC_Access_Mode_A;
}

/**
  * @brief  enable or disable the specified nor/sram memory bank.
  * @param  XMC_subbank
  *         该参数可以是以下值之一:
  *         - XMC_Bank1_NOR_SRAM1
  *         - XMC_Bank1_NOR_SRAM2
  *         - XMC_Bank1_NOR_SRAM3
  *         - XMC_Bank1_NOR_SRAM4
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void XMC_NOR_SRAM_Enable(XMC_NOR_SRAM_SubBank_Type XMC_subbank, confirm_state new_state) {
    XMC_BANK1->ctrl_tmg_group[XMC_subbank].bk1ctrl_bit.en = new_state;
}

/**
  * @brief  config the bus turnaround phase.
  * @param  XMC_Sub_bank
  *         该参数可以是以下值之一:
  *         - XMC_Bank1_NOR_SRAM1
  *         - XMC_Bank1_NOR_SRAM2
  *         - XMC_Bank1_NOR_SRAM3
  *         - XMC_Bank1_NOR_SRAM4
  * @param  w2w_timing :write timing
  * @param  r2r_timing :read timing
  * @retval 无
  */
void XMC_Ext_Timing_Config(XMC_NOR_SRAM_SubBank_Type XMC_Sub_bank, uint16_t w2w_timing, uint16_t r2r_timing) {
    XMC_BANK1->ext_bit[XMC_Sub_bank].buslatr2r = r2r_timing;
    XMC_BANK1->ext_bit[XMC_Sub_bank].buslatw2w = w2w_timing;
}

/**
  * @brief  xmc nand flash registers reset
  * @param  XMC_bank
  *         该参数可以是以下值之一:
  *         - XMC_Bank2_NAND
  *         - XMC_BANK3_NAND
  * @retval 无
  */
void XMC_NAND_Reset(XMC_class_bank_Type XMC_bank) {
    /* set the XMC_Bank2_nand registers to their reset values */
    if(XMC_bank == XMC_Bank2_NAND) {
        XMC_BANK2->bk2ctrl = 0x00000018;
        XMC_BANK2->bk2is = 0x00000040;
        XMC_BANK2->bk2tmgatt = 0xFCFCFCFC;
        XMC_BANK2->bk2tmgmem = 0xFCFCFCFC;
    }
    /* set the XMC_bank3_nand registers to their reset values */
    else {
        XMC_BANK3->bk3ctrl = 0x00000018;
        XMC_BANK3->bk3is = 0x00000040;
        XMC_BANK3->bk3tmgatt = 0xFCFCFCFC;
        XMC_BANK3->bk3tmgmem = 0xFCFCFCFC;
    }
}

/**
  * @brief  initialize the xmc nand banks 根据 the specified
  *         parameters in the XMC_nandinitstruct.
  * @param  XMC_NAND_Init_struct : pointer to a XMC_NAND_Init_Type
  *         structure that contains the configuration information for the xmc
  *         nand specified banks.
  * @retval 无
  */
void XMC_NAND_Init(XMC_NAND_Init_Type* XMC_NAND_Init_struct) {
    uint32_t tempctrl = 0x0;

    /* Set the tempctrl value 根据 XMC_NAND_Init_struct parameters */
    tempctrl = (uint32_t)XMC_NAND_Init_struct->wait_Enable |
               XMC_NAND_Init_struct->bus_Type |
               XMC_NAND_Init_struct->ecc_Enable |
               XMC_NAND_Init_struct->ecc_pagesize |
               (XMC_NAND_Init_struct->delay_Time_cycle << 9) |
               (XMC_NAND_Init_struct->delay_Time_ar << 13) |
               0x00000008;

    /* XMC_Bank2_nand registers configuration */
    if(XMC_NAND_Init_struct->nand_bank == XMC_Bank2_NAND) {
        XMC_BANK2->bk2ctrl = tempctrl;
    }
    /* XMC_bank3_nand registers configuration */
    else {
        XMC_BANK3->bk3ctrl = tempctrl;
    }
}

/**
  * @brief  initialize the xmc nand banks 根据 the specified
  *         parameters in the XMC_nandinitstruct.
  * @param  XMC_regular_spacetiming_struct : pointer to a XMC_NAND_PcCard_TimingInit_Type
  *         structure that contains the configuration information for the xmc
  *         nand specified banks.
  * @param  XMC_special_spacetiming_struct : pointer to a XMC_NAND_PcCard_TimingInit_Type
  *         structure that contains the configuration information for the xmc
  *         nand specified banks.
  * @retval 无
  */
void XMC_NAND_Timing_Config(XMC_NAND_PcCard_TimingInit_Type* XMC_regular_spacetiming_struct,
                            XMC_NAND_PcCard_TimingInit_Type* XMC_special_spacetiming_struct) {
    uint32_t tempmem = 0x0, tempatt = 0x0;

    /* set the tempmem value 根据 XMC_NAND_Init_struct parameters */
    tempmem = (uint32_t)XMC_regular_spacetiming_struct->mem_Setup_time |
              (XMC_regular_spacetiming_struct->mem_Waite_time << 8) |
              (XMC_regular_spacetiming_struct->mem_hold_time << 16) |
              (XMC_regular_spacetiming_struct->mem_hiz_time << 24);

    /* set the tempatt value 根据 XMC_NAND_Init_struct parameters */
    tempatt = (uint32_t)XMC_special_spacetiming_struct->mem_Setup_time |
              (XMC_special_spacetiming_struct->mem_Waite_time << 8) |
              (XMC_special_spacetiming_struct->mem_hold_time << 16) |
              (XMC_special_spacetiming_struct->mem_hiz_time << 24);

    /* XMC_Bank2_nand registers configuration */
    if(XMC_regular_spacetiming_struct->class_bank == XMC_Bank2_NAND) {
        XMC_BANK2->bk2tmgatt = tempatt;
        XMC_BANK2->bk2tmgmem = tempmem;
    } else {
        XMC_BANK3->bk3tmgatt = tempatt;
        XMC_BANK3->bk3tmgmem = tempmem;
    }
}

/**
  * @brief  fill each XMC_NAND_Init_struct member with its default value.
  * @param  XMC_NAND_Init_struct: pointer to a XMC_NAND_Init_Type
  *         structure which will be initialized.
  * @retval 无
  */
void XMC_NAND_Default_Para_Init(XMC_NAND_Init_Type* XMC_NAND_Init_struct) {
    /* reset nand init structure parameters values */
    XMC_NAND_Init_struct->nand_bank = XMC_Bank2_NAND;
    XMC_NAND_Init_struct->wait_Enable = XMC_Wait_Operation_Disable;
    XMC_NAND_Init_struct->bus_Type = XMC_BUSTYPE_8_BITS;
    XMC_NAND_Init_struct->ecc_Enable = XMC_ECC_Operation_Disable;
    XMC_NAND_Init_struct->ecc_pagesize = XMC_ECC_PAGESIZE_256_BYTES;
    XMC_NAND_Init_struct->delay_Time_cycle = 0x0;
    XMC_NAND_Init_struct->delay_Time_ar = 0x0;
}

/**
  * @brief  fill each XMC_Common_spacetiming_struct and XMC_attribute_spacetiming_struct member with its default value.
  * @param  XMC_Common_spacetiming_struct: pointer to a XMC_NAND_PcCard_TimingInit_Type
  *         structure which will be initialized.
  * @param  XMC_special_spacetiming_struct: pointer to a XMC_NAND_PcCard_TimingInit_Type
  *         structure which will be initialized.
  * @retval 无
  */
void XMC_NAND_Timing_Default_Para_Init(XMC_NAND_PcCard_TimingInit_Type* XMC_regular_spacetiming_struct,
                                       XMC_NAND_PcCard_TimingInit_Type* XMC_special_spacetiming_struct) {
    XMC_regular_spacetiming_struct->class_bank = XMC_Bank2_NAND;
    XMC_regular_spacetiming_struct->mem_hold_time  = 0xFC;
    XMC_regular_spacetiming_struct->mem_Waite_time = 0xFC;
    XMC_regular_spacetiming_struct->mem_Setup_time = 0xFC;
    XMC_regular_spacetiming_struct->mem_hiz_time = 0xFC;
    XMC_special_spacetiming_struct->class_bank = XMC_Bank2_NAND;
    XMC_special_spacetiming_struct->mem_hold_time = 0xFC;
    XMC_special_spacetiming_struct->mem_Waite_time = 0xFC;
    XMC_special_spacetiming_struct->mem_Setup_time = 0xFC;
    XMC_special_spacetiming_struct->mem_hiz_time = 0xFC;
}

/**
  * @brief  enable or disable the specified nand memory bank.
  * @param  XMC_bank: 指定xmc bank to be used
  *   该参数可以是以下值之一:
  *   - XMC_Bank2_NAND
  *   - XMC_BANK3_NAND
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void XMC_NAND_Enable(XMC_class_bank_Type XMC_bank, confirm_state new_state) {
    /* enable or disable the nand bank2 by setting the en bit in the bk2ctrl register */
    if(XMC_bank == XMC_Bank2_NAND) {
        XMC_BANK2->bk2ctrl_bit.en = new_state;
    }
    /* enable or disable the nand bank3 by setting the en bit in the bk3ctrl register */
    else {
        XMC_BANK3->bk3ctrl_bit.en = new_state;
    }
}

/**
  * @brief  enable or disable the xmc nand ecc feature.
  * @param  XMC_bank: 指定xmc bank to be used
  *   该参数可以是以下值之一:
  *   - XMC_Bank2_NAND
  *   - XMC_BANK3_NAND
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void XMC_NAND_ecc_Enable(XMC_class_bank_Type XMC_bank, confirm_state new_state) {
    /* enable the selected nand bank2 ecc function by setting the eccen bit in the bk2ctrl register */
    if(XMC_bank == XMC_Bank2_NAND) {
        XMC_BANK2->bk2ctrl_bit.eccen = new_state;
    }
    /* enable the selected nand bank3 ecc function by setting the eccen bit in the bk3ctrl register */
    else {
        XMC_BANK3->bk3ctrl_bit.eccen = new_state;
    }
}

/**
  * @brief  return the error correction code register value.
  * @param  XMC_bank: 指定xmc bank to be used
  *   该参数可以是以下值之一:
  *   - XMC_Bank2_NAND
  *   - XMC_BANK3_NAND
  * @retval the error correction code (ecc) value.
  */
uint32_t XMC_ecc_Get(XMC_class_bank_Type XMC_bank) {
    uint32_t eccvaule = 0x0;

    /* get the bk2ecc register value */
    if(XMC_bank == XMC_Bank2_NAND) {
        eccvaule = XMC_BANK2->bk2ecc;
    }
    /* get the bk3ecc register value */
    else {
        eccvaule = XMC_BANK3->bk3ecc;
    }

    /* return the error correction code value */
    return eccvaule;
}

/**
  * @brief  xmc sdram registers reset
  * @param  XMC_bank
  *         该参数可以是以下值之一:
  *         - XMC_SDRAM_BANK1
  *         - XMC_SDRAM_BANK2
  * @retval 无
  */
void XMC_SDRAM_Reset(XMC_SDRAM_bank_Type XMC_bank) {
    XMC_SDRAM->ctrl[XMC_bank] = 0x000002D0;
    XMC_SDRAM->tm[XMC_bank]   = 0x0FFFFFFF;
    XMC_SDRAM->cmd            = 0x00000000;
    XMC_SDRAM->rcnt           = 0x00000000;
    XMC_SDRAM->sts            = 0x00000000;
}

/**
  * @brief  initialize the xmc sdram banks 根据 the specified
  *         parameters in the XMC_SDRAM_Init_struct and XMC_SDRAM_Timing_struct.
  * @param  XMC_SDRAM_Init_struct : pointer to a XMC_SDRAM_Init_Type
  *         structure that contains the configuration information for the xmc
  *         sdram specified banks.
  * @param  XMC_SDRAM_Timing_struct : pointer to a XMC_SDRAM_Timing_Type
  *         structure that contains the configuration information for the xmc
  *         sdram specified banks.
  * @retval 无
  */
void XMC_SDRAM_Init(XMC_SDRAM_Init_Type *XMC_SDRAM_Init_struct, XMC_SDRAM_Timing_Type *XMC_SDRAM_Timing_struct) {
    if(XMC_SDRAM_Init_struct->sdram_bank == XMC_SDRAM_BANK1) {
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].ca = XMC_SDRAM_Init_struct->column_Address;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].ra = XMC_SDRAM_Init_struct->row_Address;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].db = XMC_SDRAM_Init_struct->width;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].inbk = XMC_SDRAM_Init_struct->internel_banks;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].cas = XMC_SDRAM_Init_struct->cas;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].wrp = XMC_SDRAM_Init_struct->write_protection;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].bstr = XMC_SDRAM_Init_struct->burst_Read;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].rd = XMC_SDRAM_Init_struct->read_delay;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].clkdiv = XMC_SDRAM_Init_struct->clkdiv;

        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].tmrd = XMC_SDRAM_Timing_struct->tmrd;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].txsr = XMC_SDRAM_Timing_struct->txsr;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].tras = XMC_SDRAM_Timing_struct->tras;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trc = XMC_SDRAM_Timing_struct->trc;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].twr = XMC_SDRAM_Timing_struct->twr;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trp = XMC_SDRAM_Timing_struct->trp;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trcd = XMC_SDRAM_Timing_struct->trcd;
    }

    if(XMC_SDRAM_Init_struct->sdram_bank == XMC_SDRAM_BANK2) {
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].ca = XMC_SDRAM_Init_struct->column_Address;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].ra = XMC_SDRAM_Init_struct->row_Address;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].db = XMC_SDRAM_Init_struct->width;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].inbk = XMC_SDRAM_Init_struct->internel_banks;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].cas = XMC_SDRAM_Init_struct->cas;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK2].wrp = XMC_SDRAM_Init_struct->write_protection;
        /* sdctrl2 bstr is not care */
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].bstr = XMC_SDRAM_Init_struct->burst_Read;
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].rd = XMC_SDRAM_Init_struct->read_delay;
        /* sdctrl2 clkdiv is not care */
        XMC_SDRAM->ctrl_bit[XMC_SDRAM_BANK1].clkdiv = XMC_SDRAM_Init_struct->clkdiv;

        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].tmrd = XMC_SDRAM_Timing_struct->tmrd;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].txsr = XMC_SDRAM_Timing_struct->txsr;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].tras = XMC_SDRAM_Timing_struct->tras;
        /* sdtm2 trc is not care */
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trc = XMC_SDRAM_Timing_struct->trc;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].twr = XMC_SDRAM_Timing_struct->twr;
        /* sdtm2 trp is not care */
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK1].trp = XMC_SDRAM_Timing_struct->trp;
        XMC_SDRAM->tm_bit[XMC_SDRAM_BANK2].trcd = XMC_SDRAM_Timing_struct->trcd;
    }
}

/**
  * @brief  fill each XMC_SDRAM_Init_struct member with its default value.
  * @param  XMC_SDRAM_Init_struct: pointer to a XMC_SDRAM_Init_Type
  *         structure which will be initialized.
  * @param  XMC_SDRAM_Timing_struct: pointer to a XMC_SDRAM_Timing_Type
  *         structure which will be initialized.
  * @retval 无
  */
void XMC_SDRAM_Default_Para_Init(XMC_SDRAM_Init_Type *XMC_SDRAM_Init_struct, XMC_SDRAM_Timing_Type *XMC_SDRAM_Timing_struct) {
    /* reset sdram init structure parameters values */
    XMC_SDRAM_Init_struct->sdram_bank       = XMC_SDRAM_BANK1;
    XMC_SDRAM_Init_struct->internel_banks   = XMC_INBK_4;
    XMC_SDRAM_Init_struct->clkdiv           = XMC_NO_CLK;
    XMC_SDRAM_Init_struct->write_protection = FALSE;
    XMC_SDRAM_Init_struct->burst_Read       = FALSE;
    XMC_SDRAM_Init_struct->column_Address   = XMC_COLUMN_8;
    XMC_SDRAM_Init_struct->row_Address      = XMC_ROW_11;
    XMC_SDRAM_Init_struct->cas              = XMC_CAS_1;
    XMC_SDRAM_Init_struct->width            = XMC_Mem_Width_8;
    XMC_SDRAM_Init_struct->read_delay       = XMC_Read_Delay_1;

    XMC_SDRAM_Timing_struct->tmrd           = XMC_Delay_Cycle_16;
    XMC_SDRAM_Timing_struct->txsr           = XMC_Delay_Cycle_16;
    XMC_SDRAM_Timing_struct->tras           = XMC_Delay_Cycle_16;
    XMC_SDRAM_Timing_struct->trc            = XMC_Delay_Cycle_16;
    XMC_SDRAM_Timing_struct->twr            = XMC_Delay_Cycle_16;
    XMC_SDRAM_Timing_struct->trp            = XMC_Delay_Cycle_16;
    XMC_SDRAM_Timing_struct->trcd           = XMC_Delay_Cycle_16;
}

/**
  * @brief  sdram command confg
  * @param  XMC_SDRAM_CMD_struct: pointer to a XMC_SDRAM_CMD_Type
  *         structure which will be initialized.
  * @retval 无
  */
void XMC_SDRAM_CMD(XMC_SDRAM_CMD_Type *XMC_SDRAM_CMD_struct) {
    XMC_SDRAM->cmd = (XMC_SDRAM_CMD_struct->auto_refresh << 5) |
                     (XMC_SDRAM_CMD_struct->data << 9) |
                     XMC_SDRAM_CMD_struct->cmd |
                     XMC_SDRAM_CMD_struct->cmd_banks;
}


/**
  * @brief  get sdram bank status
  * @param  XMC_bank: 指定xmc bank to be used
  *   该参数可以是以下值之一:
  *   - XMC_SDRAM_BANK1
  *   - XMC_SDRAM_BANK1
  * @retval the bank status
  */
uint32_t XMC_SDRAM_Status_Get(XMC_SDRAM_bank_Type XMC_bank) {
    if(XMC_bank == XMC_SDRAM_BANK1) {
        return ((XMC_SDRAM->sts >> 1) & XMC_Status_MASK);
    } else {
        return ((XMC_SDRAM->sts >> 3) & XMC_Status_MASK);
    }
}

/**
  * @brief  set sdram refresh counter
  * @param  counter: xmc sdram refresh counter
  * @retval 无
  */
void XMC_SDRAM_Refresh_Counter_Set(uint32_t counter) {
    XMC_SDRAM->rcnt_bit.rc = counter;
}

/**
  * @brief  set sdram auto refresh number
  * @param  number: xmc sdram auto refresh number
  * @retval 无
  */
void XMC_SDRAM_Auto_Refresh_Set(uint32_t number) {
    XMC_SDRAM->cmd_bit.art = number;
}

/**
  * @brief  enable or disable the specified xmc interrupts.
  * @param  XMC_bank: 指定xmc bank to be used
  *         该参数可以是以下值之一:
  *         - XMC_Bank2_NAND
  *         - XMC_BANK3_NAND
  *         - XMC_BANK4_PCCARD
  *         - XMC_BANK5_6_SDRAM
  * @param  XMC_int: 指定xmc interrupt sources to be enabled or disabled.
  *         该参数可以是以下值的任意组合:
  *         - XMC_INT_RISING_EDGE
  *         - XMC_INT_LEVEL
  *         - XMC_INT_FALLING_EDGE
  *         - XMC_INT_ERR
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void XMC_Interrupt_Enable(XMC_class_bank_Type XMC_bank, XMC_Interrupt_sources_Type XMC_int, confirm_state new_state) {
    if(new_state != FALSE) {
        /* enable the selected XMC_bank2 中断 */
        if(XMC_bank == XMC_Bank2_NAND) {
            XMC_BANK2->bk2is |= XMC_int;
        }
        /* enable the selected XMC_bank3 中断 */
        else if(XMC_bank == XMC_BANK3_NAND) {
            XMC_BANK3->bk3is |= XMC_int;
        }
        /* enable the selected XMC_bank4 中断 */
        else if(XMC_bank == XMC_BANK4_PCCARD) {
            XMC_BANK4->bk4is |= XMC_int;
        }
        /* enable the selected XMC_sdram 中断 */
        else {
            XMC_SDRAM->rcnt |= XMC_int;
        }
    } else {
        /* disable the selected XMC_bank2 中断 */
        if(XMC_bank == XMC_Bank2_NAND) {
            XMC_BANK2->bk2is &= ~XMC_int;
        }
        /* disable the selected XMC_bank3 中断 */
        else if(XMC_bank == XMC_BANK3_NAND) {
            XMC_BANK3->bk3is &= ~XMC_int;
        }
        /* disable the selected XMC_bank4 中断 */
        else if(XMC_bank == XMC_BANK4_PCCARD) {
            XMC_BANK4->bk4is &= ~XMC_int;
        }
        /* disable the selected XMC_sdram 中断 */
        else {
            XMC_SDRAM->rcnt &= ~XMC_int;
        }
    }
}

/**
  * @brief  check whether the specified xmc flag is set or not.
  * @param  XMC_bank: 指定xmc bank to be used
  *         该参数可以是以下值之一:
  *         - XMC_Bank2_NAND
  *         - XMC_BANK3_NAND
  *         - XMC_BANK4_PCCARD
  *         - XMC_BANK5_6_SDRAM
  * @param  XMC_flag: 指定flag to check.
  *         该参数可以是以下值的任意组合:
  *         - XMC_RISINGEDGE_FLAG
  *         - XMC_LEVEL_FLAG
  *         - XMC_FALLINGEDGE_FLAG
  *         - XMC_FEMPT_FLAG
  *         - XMC_Busy_FLAG
  *         - XMC_ERR_FLAG
  * @retval 无
  */
flag_status XMC_Flag_Status_Get(XMC_class_bank_Type XMC_bank, XMC_Interrupt_Flag_Type XMC_flag) {
    flag_status status = RESET;
    uint32_t temp = 0;

    if(XMC_bank == XMC_Bank2_NAND) {
        temp = XMC_BANK2->bk2is;
    } else if(XMC_bank == XMC_BANK3_NAND) {
        temp = XMC_BANK3->bk3is;
    } else if(XMC_bank == XMC_BANK4_PCCARD) {
        temp = XMC_BANK4->bk4is;
    } else {
        temp = XMC_SDRAM->sts;
    }

    /* get the flag status */
    if((temp & XMC_flag) == RESET) {
        status = RESET;
    } else {
        status = SET;
    }

    /* return the flag status */
    return status;
}

/**
  * @brief  clear the xmc's pending flags.
  * @param  XMC_bank: 指定xmc bank to be used
  *         该参数可以是以下值之一:
  *         - XMC_Bank2_NAND
  *         - XMC_BANK3_NAND
  *         - XMC_BANK4_PCCARD
  *         - XMC_BANK5_6_SDRAM
  * @param  XMC_flag: 指定flag to check.
  *         该参数可以是以下值的任意组合:
  *         - XMC_RISINGEDGE_FLAG
  *         - XMC_LEVEL_FLAG
  *         - XMC_FALLINGEDGE_FLAG
  *         - XMC_ERR_FLAG
  * @retval 无
  */
void XMC_Flag_Clear(XMC_class_bank_Type XMC_bank, XMC_Interrupt_Flag_Type XMC_flag) {
    __IO uint32_t int_state;

    if(XMC_bank == XMC_Bank2_NAND) {
        int_state = XMC_BANK2->bk2is & 0x38; /* keep interrupt state */
        XMC_BANK2->bk2is = (~(XMC_flag | 0x38) | int_state);
    } else if(XMC_bank == XMC_BANK3_NAND) {
        int_state = XMC_BANK3->bk3is & 0x38; /* keep interrupt state */
        XMC_BANK3->bk3is = (~(XMC_flag | 0x38) | int_state);
    } else if(XMC_bank == XMC_BANK4_PCCARD) {
        int_state = XMC_BANK4->bk4is & 0x38; /* keep interrupt state */
        XMC_BANK4->bk4is = (~(XMC_flag | 0x38) | int_state);
    } else {
        XMC_SDRAM->rcnt |= XMC_flag;
    }
}

/**
  * @brief  xmc pc card registers reset
  * @param  无
  * @retval 无
  */
void XMC_PcCard_Reset(void) {
    /* Set the XMC_Bank4 registers to their reset values */
    XMC_BANK4->bk4ctrl = 0x00000018;
    XMC_BANK4->bk4is = 0x00000000;
    XMC_BANK4->bk4tmgatt = 0xFCFCFCFC;
    XMC_BANK4->bk4tmgio = 0xFCFCFCFC;
    XMC_BANK4->bk4tmgmem = 0xFCFCFCFC;
}

/**
  * @brief  initialize the xmc pccard bank 根据 the specified
  *         parameters in the XMC_PcCard_Init_struct.
  * @param  XMC_PcCard_Init_struct : pointer to a XMC_PcCard_Init_Type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @retval 无
  */
void XMC_PcCard_Init(XMC_PcCard_Init_Type* XMC_PcCard_Init_struct) {
    /* set the bk4ctrl register value 根据 XMC_PcCard_Init_struct parameters */
    XMC_BANK4->bk4ctrl = (uint32_t)XMC_PcCard_Init_struct->enable_Wait |
                         XMC_BUSTYPE_16_BITS |
                         (XMC_PcCard_Init_struct->delay_Time_cr << 9) |
                         (XMC_PcCard_Init_struct->delay_Time_ar << 13);
}

/**
  * @brief  initialize the xmc pccard bank 根据 the specified
  *         parameters in the XMC_Common_spacetiming_struct/XMC_attribute_spacetiming_struct
  *         and XMC_iospace_Timing_struct.
  * @param  XMC_regular_spacetiming_struct : pointer to a XMC_PcCard_Init_Type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @param  XMC_special_spacetiming_struct : pointer to a XMC_PcCard_Init_Type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @param  XMC_iospace_Timing_struct : pointer to a XMC_PcCard_Init_Type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @retval 无
  */
void XMC_PcCard_Timing_Config(XMC_NAND_PcCard_TimingInit_Type* XMC_regular_spacetiming_struct,
                              XMC_NAND_PcCard_TimingInit_Type* XMC_special_spacetiming_struct,
                              XMC_NAND_PcCard_TimingInit_Type* XMC_iospace_Timing_struct) {
    /* set bk4tmgmem register value 根据 XMC_regular_spacetiming_struct parameters */
    XMC_BANK4->bk4tmgmem = (uint32_t)XMC_regular_spacetiming_struct->mem_Setup_time |
                           (XMC_regular_spacetiming_struct->mem_Waite_time << 8) |
                           (XMC_regular_spacetiming_struct->mem_hold_time << 16) |
                           (XMC_regular_spacetiming_struct->mem_hiz_time << 24);

    /* Set bk4tmgatt register value 根据 XMC_special_spacetiming_struct parameters */
    XMC_BANK4->bk4tmgatt = (uint32_t)XMC_special_spacetiming_struct->mem_Setup_time |
                           (XMC_special_spacetiming_struct->mem_Waite_time << 8) |
                           (XMC_special_spacetiming_struct->mem_hold_time << 16) |
                           (XMC_special_spacetiming_struct->mem_hiz_time << 24);

    /* Set bk4tmgio register value 根据 XMC_iospace_Timing_struct parameters */
    XMC_BANK4->bk4tmgio = (uint32_t)XMC_iospace_Timing_struct->mem_Setup_time |
                          (XMC_iospace_Timing_struct->mem_Waite_time << 8) |
                          (XMC_iospace_Timing_struct->mem_hold_time << 16) |
                          (XMC_iospace_Timing_struct->mem_hiz_time << 24);
}
/**
  * @brief  fill each XMC_PcCard_Init_struct member with its default value.
  * @param  XMC_PcCard_Init_struct: pointer to a XMC_pccardinittype
  *         structure which will be initialized.
  * @retval 无
  */
void XMC_PcCard_Default_Para_Init(XMC_PcCard_Init_Type* XMC_PcCard_Init_struct) {
    /* 重置PCCARD Init 结构参数值 */
    XMC_PcCard_Init_struct->enable_Wait = XMC_Wait_Operation_Disable;
    XMC_PcCard_Init_struct->delay_Time_ar = 0x0;
    XMC_PcCard_Init_struct->delay_Time_cr = 0x0;

}
/**
  * @brief  fill each XMC_Common_spacetiming_struct/XMC_attribute_spacetiming_struct
  *         and XMC_iospace_Timing_struct member with its default value.
  * @param  XMC_regular_spacetiming_struct : pointer to a XMC_PcCard_Init_Type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @param  XMC_special_spacetiming_struct : pointer to a XMC_PcCard_Init_Type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @param  XMC_iospace_Timing_struct : pointer to a XMC_PcCard_Init_Type
  *         structure that contains the configuration information for the xmc
  *         pccard bank.
  * @retval 无
  */
void XMC_PcCard_Timing_Default_Para_Init(XMC_NAND_PcCard_TimingInit_Type* XMC_regular_spacetiming_struct,
        XMC_NAND_PcCard_TimingInit_Type* XMC_special_spacetiming_struct,
        XMC_NAND_PcCard_TimingInit_Type* XMC_iospace_Timing_struct) {
    XMC_regular_spacetiming_struct->class_bank = XMC_BANK4_PCCARD;
    XMC_regular_spacetiming_struct->mem_hold_time  = 0xFC;
    XMC_regular_spacetiming_struct->mem_Waite_time = 0xFC;
    XMC_regular_spacetiming_struct->mem_Setup_time = 0xFC;
    XMC_regular_spacetiming_struct->mem_hiz_time = 0xFC;
    XMC_special_spacetiming_struct->class_bank = XMC_BANK4_PCCARD;
    XMC_special_spacetiming_struct->mem_hold_time  = 0xFC;
    XMC_special_spacetiming_struct->mem_Waite_time = 0xFC;
    XMC_special_spacetiming_struct->mem_Setup_time = 0xFC;
    XMC_special_spacetiming_struct->mem_hiz_time = 0xFC;
    XMC_iospace_Timing_struct->class_bank = XMC_BANK4_PCCARD;
    XMC_iospace_Timing_struct->mem_hold_time = 0xFC;
    XMC_iospace_Timing_struct->mem_Waite_time = 0xFC;
    XMC_iospace_Timing_struct->mem_Setup_time = 0xFC;
    XMC_iospace_Timing_struct->mem_hiz_time = 0xFC;
}
/**
  * @brief  enable or disable the pccard memory bank.
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void XMC_PcCard_Enable(confirm_state new_state) {
    /* enable the pccard bank4 by setting the en bit in the bk4ctrl register */
    XMC_BANK4->bk4ctrl_bit.en = new_state;
}

#endif
