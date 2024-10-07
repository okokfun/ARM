/**
  **************************************************************************
  * @file     at32f435_437_dvp.c
  * @brief    contains all the functions for the dvp firmware library
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

/** @defgroup DVP
  * @brief DVP driver modules
  */

#ifdef DVP_MODULE_EnableD

/** @defgroup DVP_private_functions
  */

/**
  * @brief  reset the dvp register
  * @param  无
  * @retval 无
  */
void DVP_Reset(void) {
    CRM_Periph_Reset(CRM_DVP_Periph_Reset, TRUE);
    CRM_Periph_Reset(CRM_DVP_Periph_Reset, FALSE);
}

/**
  * @brief  enable or disable dvp capture
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DVP_Capture_Enable(confirm_state new_state) {
    DVP->ctrl_bit.cap = new_state;
}

/**
  * @brief  set dvp capture mode
  * @param  cap_Mode
  *         该参数可以是以下值之一:
  *         - DVP_CAP_FUNC_Mode_CONTINUOUS
  *         - DVP_CAP_FUNC_Mode_SINGLE
  * @retval 无
  */
void DVP_Capture_Mode_Set(DVP_cfm_Type cap_Mode) {
    DVP->ctrl_bit.cfm = cap_Mode;
}

/**
  * @brief  set dvp cropping window enable
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DVP_Window_Crop_Enable(confirm_state new_state) {
    DVP->ctrl_bit.crp = new_state;
}

/**
  * @brief  set dvp cropping window configuration
  * @param  crop_x: cropping window horizontal start pixel
  * @param  crop_y: cropping window vertical start line
  * @param  crop_w: cropping window horizontal pixel number
  * @param  crop_h: cropping window vertical line number
  * @param  bytes: the number of bytes corresponding to one pixel
  *         eg. y8:bytes = 1, rgb565:bytes = 2
  * @retval 无
  */
void DVP_Window_Crop_Set(uint16_t crop_x, uint16_t crop_y, uint16_t crop_w, uint16_t crop_h, uint8_t bytes) {
    DVP->cwst = ((crop_x * bytes) | (crop_y << 16));
    DVP->cwsz = ((crop_w * bytes - 1) | ((crop_h - 1) << 16));
}

/**
  * @brief  enable or disable dvp jpeg
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DVP_Jpeg_Enable(confirm_state new_state) {
    DVP->ctrl_bit.jpeg = new_state;
}

/**
  * @brief  set dvp synchronization mode
  * @param  sync_Mode
  *         该参数可以是以下值之一:
  *         - DVP_Sync_Mode_HARDWARE
  *         - DVP_Sync_Mode_EMBEDDED
  * @retval 无
  */
void DVP_Sync_Mode_Set(DVP_sm_Type sync_Mode) {
    DVP->ctrl_bit.sm = sync_Mode;
}

/**
  * @brief  set dvp synchronization code configuration
  * @param  fmsc(0x00~0xFF): frame start code
  * @param  fmec(0x00~0xFF): frame end code
  * @param  lnsc(0x00~0xFF): line start code
  * @param  lnec(0x00~0xFF): line end code
  * @retval 无
  */
void DVP_Sync_code_Set(uint8_t fmsc, uint8_t fmec, uint8_t lnsc, uint8_t lnec) {
    DVP->scr = (fmsc | (lnsc << 8) | (lnec << 16) | (fmec << 24));
}

/**
  * @brief  set dvp synchronization unmask configuration
  * @param  fmsu(0x00~0xFF): frame start unmask
  * @param  fmeu(0x00~0xFF): frame end unmask
  * @param  lnsu(0x00~0xFF): line start unmask
  * @param  lneu(0x00~0xFF): line end unmask
  * @retval 无
  */
void DVP_Sync_unmask_Set(uint8_t fmsu, uint8_t fmeu, uint8_t lnsu, uint8_t lneu) {
    DVP->sur = (fmsu | (lnsu << 8) | (lneu << 16) | (fmeu << 24));
}

/**
  * @brief  set dvp pixel clock polarity
  * @param  edge
  *         该参数可以是以下值之一:
  *         - DVP_CLK_Polarity_RISING
  *         - DVP_CLK_Polarity_FALLING
  * @retval 无
  */
void DVP_PCLK_Polarity_Set(DVP_ckp_Type edge) {
    DVP->ctrl_bit.ckp = edge;
}

/**
  * @brief  set dvp horizontal synchronization polarity
  * @param  hsync_pol
  *         该参数可以是以下值之一:
  *         - DVP_HSync_Polarity_HIGH
  *         - DVP_HSync_Polarity_LOW
  * @retval 无
  */
void DVP_HSync_Polarity_Set(DVP_hsp_Type hsync_pol) {
    DVP->ctrl_bit.hsp = hsync_pol;
}

/**
  * @brief  set dvp vertical synchronization polarity
  * @param  vsync_pol
  *         该参数可以是以下值之一:
  *         - DVP_VSync_Polarity_LOW
  *         - DVP_VSync_Polarity_HIGH
  * @retval 无
  */
void DVP_VSync_Polarity_Set(DVP_vsp_Type vsync_pol) {
    DVP->ctrl_bit.vsp = vsync_pol;
}

/**
  * @brief  config dvp basic frame rate control
  * @note   this function only work in continuous fire mode(ctrl_bit.cfm = 0)
  * @param  DVP_bfrc
  *         该参数可以是以下值之一:
  *         - DVP_BFRC_ALL
  *         - DVP_BFRC_HALF
  *         - DVP_BFRC_QUARTER
  * @retval 无
  */
void DVP_Basic_Frame_rate_Control_Set(DVP_bfrc_Type DVP_bfrc) {
    DVP->ctrl_bit.bfrc = DVP_bfrc;
}

/**
  * @brief  config dvp pixel data length
  * @param  DVP_pdl
  *         该参数可以是以下值之一:
  *         - DVP_Pixel_Data_Length_8
  *         - DVP_Pixel_Data_Length_10
  *         - DVP_Pixel_Data_Length_12
  *         - DVP_Pixel_Data_Length_14
  * @retval 无
  */
void DVP_Pixel_Data_Length_Set(DVP_pdl_Type DVP_pdl) {
    DVP->ctrl_bit.pdl = DVP_pdl;
}

/**
  * @brief  enable or disable dvp function
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DVP_Enable(confirm_state new_state) {
    DVP->ctrl_bit.ena = new_state;
}

/**
  * @brief  set dvp zoomout select
  * @param  DVP_pcdes: pixel capture/drop selection extension (Only work when pcdc = 2)
  *         该参数可以是以下值之一:
  *         - DVP_PCDES_CAP_FIRST
  *         - DVP_PCDES_DROP_FIRST
  * @retval 无
  */
void DVP_ZoomOut_Select(DVP_pcdes_Type DVP_pcdes) {
    DVP->actrl_bit.pcdes = DVP_pcdes;
}

/**
  * @brief  set dvp zoomout configuration
  * @param  DVP_pcdc: basic pixel capture/drop control
  *         该参数可以是以下值之一:
  *         - DVP_PCDC_ALL
  *         - DVP_PCDC_ONE_In_TWO
  *         - DVP_PCDC_ONE_In_FOUR
  *         - DVP_PCDC_TWO_In_FOUR
  * @param  DVP_pcds: pixel capture/drop selection
  *         该参数可以是以下值之一:
  *         - DVP_PCDS_CAP_FIRST
  *         - DVP_PCDS_DROP_FIRST
  * @param  DVP_lcdc: line capture/drop control
  *         该参数可以是以下值之一:
  *         - DVP_LCDC_ALL
  *         - DVP_LCDC_ONE_In_TWO
  * @param  DVP_lcds: line capture/drop selection
  *         该参数可以是以下值之一:
  *         - DVP_LCDS_CAP_FIRST
  *         - DVP_LCDS_DROP_FIRST
  * @retval 无
  */
void DVP_ZoomOut_Set(DVP_pcdc_Type DVP_pcdc, DVP_pcds_Type DVP_pcds, DVP_lcdc_Type DVP_lcdc, DVP_lcds_Type DVP_lcds) {
    DVP->ctrl_bit.pcdc = DVP_pcdc;
    DVP->ctrl_bit.pcds = DVP_pcds;
    DVP->ctrl_bit.lcdc = DVP_lcdc;
    DVP->ctrl_bit.lcds = DVP_lcds;
}

/**
  * @brief  get dvp basic status
  * @param  DVP_Status_Basic_Type:
  *         该参数可以是以下值之一:
  *         - DVP_Status_HSYN
  *         - DVP_Status_VSYN
  *         - DVP_Status_OFNE
  * @retval flag_status (SET or RESET)
  */
flag_status DVP_Basic_Status_Get(DVP_Status_Basic_Type DVP_Status_basic) {
    flag_status status = RESET;

    if ((DVP->sts & (0x1 << DVP_Status_basic)) != (uint16_t)RESET) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/**
  * @brief  enable or disable dvp interrupt
  * @param  DVP_int:
  *         该参数可以是以下值的任意组合:
  *         - DVP_CFD_INT
  *         - DVP_OVR_INT
  *         - DVP_ESE_INT
  *         - DVP_VS_INT
  *         - DVP_HS_INT
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DVP_Interrupt_Enable(uint32_t DVP_int, confirm_state new_state) {
    if(new_state == TRUE) {
        DVP->ier |= DVP_int;
    } else {
        DVP->ier &= ~DVP_int;
    }
}

/**
  * @brief  get dvp event/interrupt flag status
  * @param  flag
  *         该参数可以是以下值之一:
  *         event flag:
  *         - DVP_CFD_EVT_FLAG
  *         - DVP_OVR_EVT_FLAG
  *         - DVP_ESE_EVT_FLAG
  *         - DVP_VS_EVT_FLAG
  *         - DVP_HS_EVT_FLAG
  *         interrupt flag:
  *         - DVP_CFD_INT_FLAG
  *         - DVP_OVR_INT_FLAG
  *         - DVP_ESE_INT_FLAG
  *         - DVP_VS_INT_FLAG
  *         - DVP_HS_INT_FLAG
  * @retval flag_status (SET or RESET)
  */
flag_status DVP_Flag_Get(uint32_t flag) {
    flag_status status = RESET;

    if(flag & 0x80000000) {
        if((DVP->ists & flag) != RESET) {
            status = SET;
        } else {
            status = RESET;
        }
    } else {
        if((DVP->ests & flag) != RESET) {
            status = SET;
        } else {
            status = RESET;
        }
    }

    return status;
}

/**
  * @brief  clear dvp's pending flags
  * @param  flag
  *         该参数可以是以下值之一:
  *         event flag:
  *         - DVP_CFD_EVT_FLAG
  *         - DVP_OVR_EVT_FLAG
  *         - DVP_ESE_EVT_FLAG
  *         - DVP_VS_EVT_FLAG
  *         - DVP_HS_EVT_FLAG
  *         interrupt flag:
  *         - DVP_CFD_INT_FLAG
  *         - DVP_OVR_INT_FLAG
  *         - DVP_ESE_INT_FLAG
  *         - DVP_VS_INT_FLAG
  *         - DVP_HS_INT_FLAG
  * @retval 无
  */
void DVP_Flag_Clear(uint32_t flag) {
    flag &= ~0x80000000;
    DVP->iclr = flag;
}

/**
  * @brief  set dvp enhanced image scaling resize enable
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DVP_Enhanced_Scaling_Resize_Enable(confirm_state new_state) {
    DVP->actrl_bit.eisre = new_state;
}
/**
  * @brief  set dvp enhanced image scaling resize configuration
  * @param  src_w(0x0001~0x1FFF): horizontal scaling resize source size (source image width)
  * @param  des_w(0x0001~0x1FFF): horizontal scaling resize target size (target image width)
  * @param  src_h(0x0001~0x1FFF): vertical scaling resize source size (source image height)
  * @param  des_h(0x0001~0x1FFF): vertical scaling resize target size (target image height)
  * @retval 无
  */
void DVP_Enhanced_Scaling_Resize_Set(uint16_t src_w, uint16_t des_w, uint16_t src_h, uint16_t des_h) {
    if((!DVP->ctrl_bit.pcdc) && (!DVP->ctrl_bit.lcdc) && DVP->actrl_bit.efdf) {
        DVP->hscf = (src_w | (des_w << 16));
        DVP->vscf = (src_h | (des_h << 16));
    }
}

/**
  * @brief  set enhanced frame rate control configuration
  * @param  efrcsf(0x00~0x1F): original frame rate contorl factor
  * @param  efrctf(0x00~0x1F): enhanced frame rate contorl factor
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DVP_Enhanced_Framerate_Set(uint16_t efrcsf, uint16_t efrctf, confirm_state new_state) {
    if((!DVP->ctrl_bit.cfm) && (!DVP->ctrl_bit.bfrc) && (efrctf <= efrcsf)) {
        DVP->frf = (efrcsf | (efrctf << 8));
    }

    DVP->actrl_bit.efrce = new_state;
}

/**
  * @brief  set dvp monochrome image binarization configuration
  * @param  mibthd(0x00~0xFF): monochrome image binarization threshold
  * @param  new_state: (TRUE or FALSE)
  * @retval 无
  */
void DVP_Monochrome_Image_Binarization_Set(uint8_t mibthd, confirm_state new_state) {
    DVP->bth_bit.mibthd = mibthd;
    DVP->actrl_bit.mibe = new_state;
}

/**
  * @brief  set dvp enhanced function data format configuration
  * @param  DVP_efdf: enhanced function data format
  *         该参数可以是以下值之一:
  *         - DVP_EFDF_ByPass
  *         - DVP_EFDF_YUV422_UYVY
  *         - DVP_EFDF_YUV422_YUYV
  *         - DVP_EFDF_RGB565_555
  *         - DVP_EFDF_Y8
  * @retval 无
  */
void DVP_Enhanced_Data_Format_Set(DVP_efdf_Type DVP_efdf) {
    DVP->actrl_bit.efdf = DVP_efdf;
}

/**
  * @brief  set dvp input data un-used condition/number configuration
  * @param  DVP_idus: input data un-used condition
  *         该参数可以是以下值之一:
  *         - DVP_IDUS_MSB
  *         - DVP_IDUS_LSB
  * @param  DVP_idun: input data un-used number
  *         该参数可以是以下值之一:
  *         - DVP_IDUN_0
  *         - DVP_IDUN_2
  *         - DVP_IDUN_4
  *         - DVP_IDUN_6
  * @retval 无
  */
void DVP_Input_Data_Unused_Set(DVP_idus_Type DVP_idus, DVP_idun_Type DVP_idun) {
    DVP->actrl_bit.idus = DVP_idus;
    DVP->actrl_bit.idun = DVP_idun;
}

/**
  * @brief  set dvp dma burst transfer configuration
  * @param  DVP_dmabt: dma burst transfer configuration
  *         该参数可以是以下值之一:
  *         - DVP_DMABT_SINGLE
  *         - DVP_DMABT_BURST
  * @retval 无
  */
void DVP_DMA_Burst_Set(DVP_dmabt_Type DVP_dmabt) {
    DVP->actrl_bit.dmabt = DVP_dmabt;
}

/**
  * @brief  set dvp hsync/vsync event interrupt strategy configuration
  * @param  DVP_hseid: hsync event interrupt strategy
  *         该参数可以是以下值之一:
  *         - DVP_HSEID_Line_END
  *         - DVP_HSEID_Line_Start
  * @param  DVP_vseid: vsync event interrupt strategy
  *         该参数可以是以下值之一:
  *         - DVP_VSEID_Frame_END
  *         - DVP_VSEID_FRMAE_Start
  * @retval 无
  */
void DVP_Sync_Event_Interrupt_Set(DVP_hseid_Type DVP_hseid, DVP_vseid_Type DVP_vseid) {
    DVP->actrl_bit.hseid = DVP_hseid;
    DVP->actrl_bit.vseid = DVP_vseid;
}

#endif
