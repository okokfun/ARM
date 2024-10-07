/**
  **************************************************************************
  * @file     at32f435_437_usb.c
  * @brief    contains all the functions for the usb firmware library
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

/** @defgroup USB
  * @brief USB driver modules
  */

#ifdef USB_MODULE_EnableD

/** @defgroup USB_private_functions
  */

#ifdef OTGFS_USB_GLOBAL
/**
  * @brief  usb global core soft reset
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval error status
  */
error_status USB_Global_Reset(OTG_Global_Type *usbx) {
    uint32_t timeout = 0;

    while(usbx->grstctl_bit.ahbidle == RESET) {
        if(timeout ++ > 200000) {
            break;
        }
    }

    timeout = 0;
    usbx->grstctl_bit.csftrst = TRUE;

    while(usbx->grstctl_bit.csftrst == SET) {
        if(timeout ++ > 200000) {
            break;
        }
    }

    return SUCCESS;
}

/**
  * @brief  usb global initialization
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Global_Init(OTG_Global_Type *usbx) {
    /* reset otg moudle */
    USB_Global_Reset(usbx);

    /* exit power down mode */
    usbx->gccfg_bit.pwrdown = TRUE;
}

/**
  * @brief  usb global select usb core (otg1 or otg2).
  * @param  USB_id: select otg1 or otg2
  *         该参数可以是以下值之一:
  *         - USB_OTG1_ID
  *         - USB_OTG2_ID
  * @retval usb global register type pointer
  */
OTG_Global_Type *USB_Global_Select_Core(uint8_t USB_id) {
    if(USB_id == USB_OTG1_ID) {
        /* use otg1 */
        return OTG1_GLOBAL;
    } else {
        /* use otg2 */
        return OTG2_GLOBAL;
    }
}

/**
  * @brief  flush tx fifo
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  fifo_Num: tx fifo num,when fifo_Num=16,flush all tx fifo
  *         parameter as following values: 0-16
  * @retval 无
  */
void USB_Flush_TX_FIFO(OTG_Global_Type *usbx, uint32_t fifo_Num) {
    uint32_t timeout = 0;
    /* set flush fifo number */
    usbx->grstctl_bit.txfnum = fifo_Num;

    /* start flush fifo */
    usbx->grstctl_bit.txfflsh = TRUE;

    while(usbx->grstctl_bit.txfflsh == TRUE) {
        if(timeout ++ > 200000) {
            break;
        }
    }
}

/**
  * @brief  flush rx fifo
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Flush_RX_FIFO(OTG_Global_Type *usbx) {
    uint32_t timeout = 0;
    usbx->grstctl_bit.rxfflsh = TRUE;

    while(usbx->grstctl_bit.rxfflsh == TRUE) {
        if(timeout ++ > 200000) {
            break;
        }
    }
}

/**
  * @brief  usb interrupt mask enable
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  interrupt:
  *         该参数可以是以下值的任意组合:
  *         - USB_OTG_ModeMIS_INT
  *         - USB_OTG_OTGINT_INT
  *         - USB_OTG_SOF_INT
  *         - USB_OTG_RXFLVL_INT
  *         - USB_OTG_NPTXFEMP_INT
  *         - USB_OTG_GINNAKEFF_INT
  *         - USB_OTG_GOUTNAKEFF_INT
  *         - USB_OTG_ERLYSUSP_INT
  *         - USB_OTG_USBSUSP_INT
  *         - USB_OTG_USBRST_INT
  *         - USB_OTG_ENUMDONE_INT
  *         - USB_OTG_ISOOUTDROP_INT
  *         - USB_OTG_IEPT_INT
  *         - USB_OTG_OEPT_INT
  *         - USB_OTG_INCOMISOIN_INT
  *         - USB_OTG_INCOMPIP_INCOMPISOOUT_INT
  *         - USB_OTG_PRT_INT
  *         - USB_OTG_HCH_INT
  *         - USB_OTG_PTXFEMP_INT
  *         - USB_OTG_CONIDSCHG_INT
  *         - USB_OTG_DISCON_INT
  *         - USB_OTG_WKUP_INT
  * @param  new_state: TRUE or FALSE
  * @retval 无
  */
void USB_Global_Interrupt_Enable(OTG_Global_Type *usbx, uint16_t interrupt, confirm_state new_state) {
    if(new_state == TRUE) {
        usbx->gintmsk |= interrupt;
    } else {
        usbx->gintmsk &= ~interrupt;
    }
}

/**
  * @brief  get all global core interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval intterupt flag
  */
uint32_t USB_Global_Get_All_Interrupt(OTG_Global_Type *usbx) {
    uint32_t intsts = usbx->gintsts;
    return intsts & usbx->gintmsk;
}

/**
  * @brief  clear the global interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  flag: interrupt flag
  *         该参数可以是以下值的任意组合:
  *         - USB_OTG_ModeMIS_FLAG
  *         - USB_OTG_OTGINT_FLAG
  *         - USB_OTG_SOF_FLAG
  *         - USB_OTG_RXFLVL_FLAG
  *         - USB_OTG_NPTXFEMP_FLAG
  *         - USB_OTG_GINNAKEFF_FLAG
  *         - USB_OTG_GOUTNAKEFF_FLAG
  *         - USB_OTG_ERLYSUSP_FLAG
  *         - USB_OTG_USBSUSP_FLAG
  *         - USB_OTG_USBRST_FLAG
  *         - USB_OTG_ENUMDONE_FLAG
  *         - USB_OTG_ISOOUTDROP_FLAG
  *         - USB_OTG_EOPF_FLAG
  *         - USB_OTG_IEPT_FLAG
  *         - USB_OTG_OEPT_FLAG
  *         - USB_OTG_INCOMISOIN_FLAG
  *         - USB_OTG_INCOMPIP_INCOMPISOOUT_FLAG
  *         - USB_OTG_PRT_FLAG
  *         - USB_OTG_HCH_FLAG
  *         - USB_OTG_PTXFEMP_FLAG
  *         - USB_OTG_CONIDSCHG_FLAG
  *         - USB_OTG_DISCON_FLAG
  *         - USB_OTG_WKUP_FLAG
  * @retval 无
  */
void USB_Global_Clear_Interrupt(OTG_Global_Type *usbx, uint32_t flag) {
    usbx->gintsts = flag;
}

/**
  * @brief  usb global interrupt enable
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         OTG1_GLOBAL , OTG2_GLOBAL
  * @retval 无
  */
void USB_Interrupt_Enable(OTG_Global_Type *usbx) {
    usbx->gahbcfg_bit.glbintmsk = TRUE;
}

/**
  * @brief  usb global interrupt disable
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Interrupt_Disable(OTG_Global_Type *usbx) {
    usbx->gahbcfg_bit.glbintmsk = FALSE;
}

/**
  * @brief  usb set rx fifo size
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  size: rx fifo size
  * @retval 无
  */
void USB_Set_RX_FIFO(OTG_Global_Type *usbx, uint16_t size) {
    usbx->grxfsiz = size;
}

/**
  * @brief  usb set tx fifo size
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  txfifo: the fifo number
  * @param  size: tx fifo size
  * @retval 无
  */
void USB_Set_TX_FIFO(OTG_Global_Type *usbx, uint8_t txfifo, uint16_t size) {
    uint8_t i_index = 0;
    uint32_t offset = 0;

    offset = usbx->grxfsiz;

    if(txfifo == 0) {
        usbx->gnptxfsiz_ept0tx = offset | (size << 16);
    } else {
        offset += usbx->gnptxfsiz_ept0tx_bit.nptxfdep;

        for(i_index = 0; i_index < (txfifo - 1); i_index ++) {
            offset += usbx->dieptxfn_bit[i_index].ineptxfdep;
        }

        usbx->dieptxfn[txfifo - 1] = offset | (size << 16);
    }
}


/**
  * @brief  set otg mode(device or host mode)
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  mode:
            该参数可以是以下值之一:
  *         - OTG_Device_Mode
  *         - OTG_HOST_Mode
  *         - OTG_DRD_Mode
  * @retval 无
  */
void USB_Global_Set_Mode(OTG_Global_Type *usbx, uint32_t mode) {
    /* set otg to device mode */
    if(mode == OTG_Device_Mode) {
        usbx->gusbcfg_bit.fhstmode = FALSE;
        usbx->gusbcfg_bit.fdevmode = TRUE;
    }

    /* set otg to host mode */
    if(mode == OTG_HOST_Mode) {
        usbx->gusbcfg_bit.fdevmode = FALSE;
        usbx->gusbcfg_bit.fhstmode = TRUE;
    }

    /* set otg to default mode */
    if(mode == OTG_DRD_Mode) {
        usbx->gusbcfg_bit.fdevmode = FALSE;
        usbx->gusbcfg_bit.fhstmode = FALSE;
    }
}


/**
  * @brief  disable the transceiver power down mode
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Global_Power_ON(OTG_Global_Type *usbx) {
    /* core soft reset */
    usbx->grstctl_bit.csftrst = TRUE;

    while(usbx->grstctl_bit.csftrst);

    /* disable power down mode */
    usbx->gccfg_bit.pwrdown = TRUE;

}

/**
  * @brief  usb stop phy clock
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Stop_PHY_CLK(OTG_Global_Type *usbx) {
    OTG_PCGCCTL(usbx)->pcgcctl_bit.stoppclk = TRUE;
}

/**
  * @brief  usb open phy clock
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Open_PHY_CLK(OTG_Global_Type *usbx) {
    OTG_PCGCCTL(usbx)->pcgcctl_bit.stoppclk = FALSE;
}


/**
  * @brief  write data from user memory to usb buffer
  * @param  pusr_buf: point to user buffer
  * @param  offset_Addr: endpoint tx offset address
  * @param  nbytes: number of bytes data write to usb buffer
  * @retval 无
  */
void USB_Write_Packet(OTG_Global_Type *usbx, uint8_t *pusr_buf, uint16_t num, uint16_t nbytes) {
    uint32_t n_index;
    uint32_t nhbytes = (nbytes + 3) / 4;
    uint32_t *pbuf = (uint32_t *)pusr_buf;

    for(n_index = 0; n_index < nhbytes; n_index ++) {
        #if defined (__ICCARM__) && (__VER__ < 7000000)
        USB_FIFO(usbx, num) = *(__packed uint32_t *)pbuf;
        #else
        USB_FIFO(usbx, num) = __UNALIGNED_UINT32_Read(pbuf);
        #endif
        pbuf ++;
    }
}

/**
  * @brief  read data from usb buffer to user buffer
  * @param  pusr_buf: point to user buffer
  * @param  offset_Addr: endpoint rx offset address
  * @param  nbytes: number of bytes data write to usb buffer
  * @retval 无
  */
void USB_Read_Packet(OTG_Global_Type *usbx, uint8_t *pusr_buf, uint16_t num, uint16_t nbytes) {
    uint32_t n_index;
    uint32_t nhbytes = (nbytes + 3) / 4;
    uint32_t *pbuf = (uint32_t *)pusr_buf;

    for(n_index = 0; n_index < nhbytes; n_index ++) {
        #if defined (__ICCARM__) && (__VER__ < 7000000)
        *(__packed uint32_t *)pbuf = USB_FIFO(usbx, 0);
        #else
        __UNALIGNED_UINT32_Write(pbuf, (USB_FIFO(usbx, 0)));
        #endif
        pbuf ++;
    }
}
#endif


#ifdef OTGFS_USB_DEVICE
/**
  * @brief  open usb endpoint
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  ept_info: endpoint information structure
  * @retval 无
  */
void USB_EPT_Open(OTG_Global_Type *usbx, USB_EPT_info *ept_info) {
    uint8_t mps = USB_EPT0_MPS_64;

    if(ept_info->eptn == USB_EPT0) {
        if(ept_info->maxpacket == 0x40) {
            mps = USB_EPT0_MPS_64;
        } else if(ept_info->maxpacket == 0x20) {
            mps = USB_EPT0_MPS_32;
        } else if(ept_info->maxpacket == 0x10) {
            mps = USB_EPT0_MPS_16;
        } else if(ept_info->maxpacket == 0x08) {
            mps = USB_EPT0_MPS_8;
        }
    }

    /* endpoint direction is in */
    if(ept_info->inout == EPT_Dir_IN) {
        OTG_DEVICE(usbx)->daintmsk |= 1 << ept_info->eptn;

        if(ept_info->eptn == USB_EPT0) {
            USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.mps = mps;
        } else {
            USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.mps = ept_info->maxpacket;
        }

        USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.eptype = ept_info->trans_Type;
        USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.txfnum = ept_info->eptn;
        USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.setd0pid = TRUE;
        USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.usbacept = TRUE;
    }
    /* endpoint direction is out */
    else {
        OTG_DEVICE(usbx)->daintmsk |= (1 << ept_info->eptn) << 16;

        if(ept_info->eptn == USB_EPT0) {
            USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.mps = mps;
        } else {
            USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.mps = ept_info->maxpacket;
        }

        USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.eptype = ept_info->trans_Type;
        USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.setd0pid = TRUE;
        USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.usbacept = TRUE;
    }
}

/**
  * @brief  close usb endpoint
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  ept_info: endpoint information structure
  * @retval 无
  */
void USB_EPT_Close(OTG_Global_Type *usbx, USB_EPT_info *ept_info) {
    if(ept_info->inout == EPT_Dir_IN) {
        OTG_DEVICE(usbx)->daintmsk &= ~(1 << ept_info->eptn);
        USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.usbacept = FALSE;
    } else {
        OTG_DEVICE(usbx)->daintmsk &= ~((1 << ept_info->eptn) << 16);
        USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.usbacept = FALSE;
    }
}


/**
  * @brief  set endpoint tx or rx status to stall
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  ept_info: endpoint information structure
  * @retval 无
  */
void USB_EPT_Stall(OTG_Global_Type *usbx, USB_EPT_info *ept_info) {
    if(ept_info->inout == EPT_Dir_IN) {
        if(USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.eptena == RESET) {
            USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.eptdis = FALSE;
        }

        USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.stall = SET;
    } else {
        if(USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.eptena == RESET) {
            USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.eptdis = FALSE;
        }

        USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.stall = TRUE;
    }
}

/**
  * @brief  clear endpoint tx or rx status to stall
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  ept_info: endpoint information structure
  * @retval 无
  */
void USB_EPT_Clear_Stall(OTG_Global_Type *usbx, USB_EPT_info *ept_info) {
    if(ept_info->inout == EPT_Dir_IN) {
        USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.stall = FALSE;

        if(ept_info->trans_Type == EPT_INT_Type || ept_info->trans_Type == EPT_BULK_Type) {
            USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.setd0pid = TRUE;
        }
    } else {
        USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.stall = FALSE;

        if(ept_info->trans_Type == EPT_INT_Type || ept_info->trans_Type == EPT_BULK_Type) {
            USB_OutEPT(usbx, ept_info->eptn)->doepctl_bit.setd0pid = TRUE;
        }
    }
}

/**
  * @brief  get all out endpoint interrupt bits
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval out endpoint interrupt bits
  */
uint32_t USB_Get_All_Out_Interrupt(OTG_Global_Type *usbx) {
    uint32_t intsts = OTG_DEVICE(usbx)->daint;
    return ((intsts & (OTG_DEVICE(usbx)->daintmsk)) >> 16);
}

/**
  * @brief  get all in endpoint interrupt bits
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval in endpoint interrupt bits
  */
uint32_t USB_Get_All_In_Interrupt(OTG_Global_Type *usbx) {
    uint32_t intsts = OTG_DEVICE(usbx)->daint;
    return ((intsts & (OTG_DEVICE(usbx)->daintmsk)) & 0xFFFF);
}


/**
  * @brief  get out endpoint interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  eptn: endpoint number
  * @retval out endpoint interrupt flags
  */
uint32_t USB_EPT_Out_Interrupt(OTG_Global_Type *usbx, uint32_t eptn) {
    uint32_t intsts = USB_OutEPT(usbx, eptn)->doepint;
    return (intsts & (OTG_DEVICE(usbx)->doepmsk));
}

/**
  * @brief  get in endpoint interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  eptn: endpoint number
  * @retval in endpoint intterupt flags
  */
uint32_t USB_EPT_In_Interrupt(OTG_Global_Type *usbx, uint32_t eptn) {
    uint32_t intsts, mask1, mask2;
    mask1 = OTG_DEVICE(usbx)->diepmsk;
    mask2 = OTG_DEVICE(usbx)->diepempmsk;
    mask1 |= ((mask2 >> eptn) & 0x1) << 7;
    intsts = USB_INEPT(usbx, eptn)->diepint & mask1;
    return intsts;
}

/**
  * @brief  clear out endpoint interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  eptn: endpoint number
  * @retval flag: interrupt flag
  *         该参数可以是以下值的任意组合:
  *         - USB_OTG_DOEPINT_XFERC_FLAG
  *         - USB_OTG_DOEPINT_EPTDISD_FLAG
  *         - USB_OTG_DOEPINT_SetUP_FLAG
  *         - USB_OTG_DOEPINT_OTEPDIS_FLAG
  *         - USB_OTG_DOEPINT_B2BSTUP_FLAG
  */
void USB_EPT_Out_Clear(OTG_Global_Type *usbx, uint32_t eptn, uint32_t flag) {
    USB_OutEPT(usbx, eptn)->doepint = flag;
}

/**
  * @brief  clear in endpoint interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  eptn: endpoint number
  * @retval flag: interrupt flag
  *         该参数可以是以下值的任意组合:
  *         - USB_OTG_DIEPINT_XFERC_FLAG
  *         - USB_OTG_DIEPINT_EPTDISD_FLAG
  *         - USB_OTG_DIEPINT_TMROC_FLAG
  *         - USB_OTG_DIEPINT_INTTXFE_FLAG
  *         - USB_OTG_DIEPINT_INEPNE_FLAG
  *         - USB_OTG_DIEPINT_TXFE_FLAG
  */
void USB_EPT_In_Clear(OTG_Global_Type *usbx, uint32_t eptn, uint32_t flag) {
    USB_INEPT(usbx, eptn)->diepint = flag;
}


/**
  * @brief  set the host assignment address
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  address: host assignment address
  * @retval 无
  */
void USB_Set_Address(OTG_Global_Type *usbx, uint8_t address) {
    OTG_DEVICE(usbx)->dcfg_bit.devaddr = address;
}

/**
  * @brief  enable endpoint 0 out
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_EPT0_Start(OTG_Global_Type *usbx) {
    OTG_eptout_Type *USB_Outept = USB_OutEPT(usbx, 0);
    USB_Outept->doeptsiz = 0;
    USB_Outept->doeptsiz_bit.pktcnt = 1;
    USB_Outept->doeptsiz_bit.xfersize = 24;
    USB_Outept->doeptsiz_bit.rxdpid_Setupcnt = 3;
}


/**
  * @brief  endpoint 0 start setup
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_EPT0_Setup(OTG_Global_Type *usbx) {
    USB_INEPT(usbx, 0)->diepctl_bit.mps = 0;
    OTG_DEVICE(usbx)->dctl_bit.cgnpinak = FALSE;
}

/**
  * @brief  connect usb device by enable pull-up
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Connect(OTG_Global_Type *usbx) {
    /* D+ 1.5k pull-up enable */
    OTG_DEVICE(usbx)->dctl_bit.sftdiscon = FALSE;
}

/**
  * @brief  disconnect usb device by disable pull-up
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Disconnect(OTG_Global_Type *usbx) {
    /* D+ 1.5k pull-up disable */
    OTG_DEVICE(usbx)->dctl_bit.sftdiscon = TRUE;
}


/**
  * @brief  usb remote wakeup set
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Remote_wkup_Set(OTG_Global_Type *usbx) {
    OTG_DEVICE(usbx)->dctl_bit.rwkupsig = TRUE;
}

/**
  * @brief  usb remote wakeup clear
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_Remote_wkup_Clear(OTG_Global_Type *usbx) {
    OTG_DEVICE(usbx)->dctl_bit.rwkupsig = FALSE;
}

/**
  * @brief  usb suspend status get
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval usb suspend status
  */
uint8_t USB_Suspend_Status_Get(OTG_Global_Type *usbx) {
    return OTG_DEVICE(usbx)->dsts_bit.suspsts;
}
#endif

#ifdef OTGFS_USB_HOST
/**
  * @brief  usb port power on
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  state: state (TRUE or FALSE)
  * @retval 无
  */
void USB_Port_Power_ON(OTG_Global_Type *usbx, confirm_state state) {
    OTG_HOST_Type *USB_host = OTG_HOST(usbx);
    uint32_t hprt_val = USB_host->hprt;

    hprt_val &= ~(USB_OTG_HPRT_PRTENA | USB_OTG_HPRT_PRTENCHNG |
                  USB_OTG_HPRT_PRTOVRCACT | USB_OTG_HPRT_PRTCONDET);

    if(state == TRUE) {
        USB_host->hprt = hprt_val | USB_OTG_HPRT_PRTPWR;
    } else {
        USB_host->hprt = hprt_val & (~USB_OTG_HPRT_PRTPWR);
    }
}

/**
  * @brief  get current frame number
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
uint32_t USBH_Get_Frame(OTG_Global_Type *usbx) {
    OTG_HOST_Type *USB_host = OTG_HOST(usbx);
    return USB_host->hfnum & 0xFFFF;
}

/**
  * @brief  enable one host channel
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  chn: host channel number
  * @param  ept_Num: devvice endpoint number
  * @param  dev_Address: device address
  * @param  type: channel transfer type
  *         该参数可以是以下值之一:
  *         - EPT_Control_Type
  *         - EPT_BULK_Type
  *         - EPT_INT_Type
  *         - EPT_ISO_Type
  * @param  maxpacket: support max packe size for this channel
  * @param  speed: device speed
  *         该参数可以是以下值之一:
  *         - USB_PRTSPD_FULL_SPEED
  *         - USB_PRTSPD_Low_SPEED
  * @retval 无
  */
void USB_HC_Enable(OTG_Global_Type *usbx,
                   uint8_t chn,
                   uint8_t ept_Num,
                   uint8_t dev_Address,
                   uint8_t type,
                   uint16_t maxpacket,
                   uint8_t speed) {
    OTG_hchannel_Type *hch = USB_CHL(usbx, chn);
    OTG_HOST_Type *USB_host = OTG_HOST(usbx);

    switch(type) {
        case EPT_Control_Type:
        case EPT_BULK_Type:
            hch->hcintmsk |= USB_OTG_HC_XFERCM_INT | USB_OTG_HC_StallM_INT |
                             USB_OTG_HC_XACTERRM_INT | USB_OTG_HC_NAKM_INT |
                             USB_OTG_HC_DTGLERRM_INT;

            if(ept_Num & 0x80) {
                hch->hcintmsk_bit.bblerrmsk = TRUE;
            }

            break;

        case EPT_INT_Type:
            hch->hcintmsk |= USB_OTG_HC_XFERCM_INT | USB_OTG_HC_StallM_INT |
                             USB_OTG_HC_XACTERRM_INT | USB_OTG_HC_NAKM_INT |
                             USB_OTG_HC_DTGLERRM_INT | USB_OTG_HC_FRMOVRRUN_INT;
            break;

        case EPT_ISO_Type:

            hch->hcintmsk |= USB_OTG_HC_XFERCM_INT | USB_OTG_HC_ACKM_INT |
                             USB_OTG_HC_FRMOVRRUN_INT;
            break;
    }

    USB_host->haintmsk |= 1 << chn;
    usbx->gintmsk_bit.hchintmsk = TRUE;

    hch->hcchar_bit.devaddr = dev_Address;
    hch->hcchar_bit.eptnum = ept_Num & 0x7F;
    hch->hcchar_bit.eptdir = (ept_Num & 0x80) ? 1 : 0;
    hch->hcchar_bit.lspddev = (speed == USB_PRTSPD_Low_SPEED) ? 1 : 0;
    hch->hcchar_bit.eptype = type;
    hch->hcchar_bit.mps = maxpacket;

    if(type == EPT_INT_Type) {
        hch->hcchar_bit.oddfrm = TRUE;
    }
}

/**
  * @brief  host read channel interrupt
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval interrupt flag
  */
uint32_t USB_HCH_Read_Interrupt(OTG_Global_Type *usbx) {
    OTG_HOST_Type *USB_host = OTG_HOST(usbx);
    return USB_host->haint & 0xFFFF;
}

/**
  * @brief  disable host
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @retval 无
  */
void USB_HOST_Disable(OTG_Global_Type *usbx) {
    uint32_t i_index = 0, count = 0;
    OTG_hchannel_Type *hch;
    OTG_HOST_Type *USB_host = OTG_HOST(usbx);

    usbx->gahbcfg_bit.glbintmsk = FALSE;
    USB_Flush_RX_FIFO(usbx);
    USB_Flush_TX_FIFO(usbx, 0x10);

    for(i_index = 0; i_index < 16; i_index ++) {
        hch = USB_CHL(usbx, i_index);
        hch->hcchar_bit.chdis = TRUE;
        hch->hcchar_bit.chena = FALSE;
        hch->hcchar_bit.eptdir = 0;
    }

    for(i_index = 0; i_index < 16; i_index ++) {
        hch = USB_CHL(usbx, i_index);
        hch->hcchar_bit.chdis = TRUE;
        hch->hcchar_bit.chena = TRUE;
        hch->hcchar_bit.eptdir = 0;

        do {
            if(count ++ > 1000)
                break;
        } while(hch->hcchar_bit.chena);
    }

    USB_host->haint = 0xFFFFFFFF;
    usbx->gintsts = 0xFFFFFFFF;
    usbx->gahbcfg_bit.glbintmsk = TRUE;
}

/**
  * @brief  halt channel
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  chn: channel number
  * @retval 无
  */
void USB_HCH_Halt(OTG_Global_Type *usbx, uint8_t chn) {
    uint32_t count = 0;
    OTG_hchannel_Type *USB_chh = USB_CHL(usbx, chn);
    OTG_HOST_Type *USB_host = OTG_HOST(usbx);

    /* endpoint type is control or bulk */
    if(USB_chh->hcchar_bit.eptype == EPT_Control_Type ||
            USB_chh->hcchar_bit.eptype == EPT_BULK_Type) {
        USB_chh->hcchar_bit.chdis = TRUE;

        if((usbx->gnptxsts_bit.nptxqspcavail) == 0) {
            USB_chh->hcchar_bit.chena = FALSE;
            USB_chh->hcchar_bit.chena = TRUE;

            do {
                if(count ++ > 1000)
                    break;
            } while(USB_chh->hcchar_bit.chena == SET);
        } else {
            USB_chh->hcchar_bit.chena = TRUE;
        }
    } else {
        USB_chh->hcchar_bit.chdis = TRUE;

        if((USB_host->hptxsts_bit.ptxqspcavil) == 0) {
            USB_chh->hcchar_bit.chena = FALSE;
            USB_chh->hcchar_bit.chena = TRUE;

            do {
                if(count ++ > 1000)
                    break;
            } while(USB_chh->hcchar_bit.chena == SET);
        } else {
            USB_chh->hcchar_bit.chena = TRUE;
        }
    }
}
/**
  * @brief  select full or low speed clock
  * @param  usbx: to select the otgfs peripheral.
  *         该参数可以是以下值之一:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  clk: clock frequency
  * @retval 无
  */
void USBH_Fsls_CLKsel(OTG_Global_Type *usbx, uint8_t clk) {
    OTG_HOST_Type *USB_host = OTG_HOST(usbx);

    USB_host->hcfg_bit.fslspclksel = clk;

    if(clk == USB_HCFG_CLK_6M) {
        USB_host->hfir = 6000;
    } else {
        USB_host->hfir = 48000;
    }
}
#endif


#endif
