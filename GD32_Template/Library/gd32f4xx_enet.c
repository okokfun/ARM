/*!
    文件:    gd32f4xx_enet.c
    简介:   ENET driver

    版本: 2016-08-15, V1.0.0, firmware for GD32F4xx
    版本: 2018-12-12, V2.0.0, firmware for GD32F4xx
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

#include "gd32f4xx_enet.h"

#if defined   (__CC_ARM)                                    /*!< ARM compiler */
__align(4)
ENET_Descriptors_Struct  rxdesc_tab[ENET_RXBUF_NUM];        /*!< ENET RxDMA descriptor */
__align(4)
ENET_Descriptors_Struct  txdesc_tab[ENET_TXBUF_NUM];        /*!< ENET TxDMA descriptor */
__align(4)
uint8_t rx_buff[ENET_RXBUF_NUM][ENET_RXBUF_SIZE];           /*!< ENET receive buffer */
__align(4)
uint8_t tx_buff[ENET_TXBUF_NUM][ENET_TXBUF_SIZE];           /*!< ENET transmit buffer */

#elif defined ( __ICCARM__ )                                /*!< IAR compiler */
#pragma data_alignment=4
ENET_Descriptors_Struct  rxdesc_tab[ENET_RXBUF_NUM];        /*!< ENET RxDMA descriptor */
#pragma data_alignment=4
ENET_Descriptors_Struct  txdesc_tab[ENET_TXBUF_NUM];        /*!< ENET TxDMA descriptor */
#pragma data_alignment=4
uint8_t rx_buff[ENET_RXBUF_NUM][ENET_RXBUF_SIZE];           /*!< ENET receive buffer */
#pragma data_alignment=4
uint8_t tx_buff[ENET_TXBUF_NUM][ENET_TXBUF_SIZE];           /*!< ENET transmit buffer */

#elif defined (__GNUC__)        /* GNU Compiler */
ENET_Descriptors_Struct  rxdesc_tab[ENET_RXBUF_NUM] __attribute__((aligned(4)));          /*!< ENET RxDMA descriptor */
ENET_Descriptors_Struct  txdesc_tab[ENET_TXBUF_NUM] __attribute__((aligned(4)));          /*!< ENET TxDMA descriptor */
uint8_t rx_buff[ENET_RXBUF_NUM][ENET_RXBUF_SIZE] __attribute__((aligned(4)));             /*!< ENET receive buffer */
uint8_t tx_buff[ENET_TXBUF_NUM][ENET_TXBUF_SIZE] __attribute__((aligned(4)));             /*!< ENET transmit buffer */

#endif /* __CC_ARM */

/* global transmit and receive descriptors pointers */
ENET_Descriptors_Struct  *DMA_Current_txdesc;
ENET_Descriptors_Struct  *DMA_Current_rxdesc;

/* structure pointer of ptp descriptor for normal mode */
ENET_Descriptors_Struct  *DMA_Current_PTP_txdesc = NULL;
ENET_Descriptors_Struct  *DMA_Current_PTP_rxdesc = NULL;

/* init structure parameters for ENET initialization */
static ENET_initpara_Struct ENET_initpara = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint32_t ENET_unknow_err = 0U;
/* array of register offset for debug information get */
static const uint16_t ENET_reg_tab[] = {
    0x0000, 0x0004, 0x0008, 0x000C, 0x0010, 0x0014, 0x0018, 0x001C, 0x0028, 0x002C, 0x0034,
    0x0038, 0x003C, 0x0040, 0x0044, 0x0048, 0x004C, 0x0050, 0x0054, 0x0058, 0x005C, 0x1080,

    0x0100, 0x0104, 0x0108, 0x010C, 0x0110, 0x014C, 0x0150, 0x0168, 0x0194, 0x0198, 0x01C4,

    0x0700, 0x0704, 0x0708, 0x070C, 0x0710, 0x0714, 0x0718, 0x071C, 0x0720, 0x0728, 0x072C,

    0x1000, 0x1004, 0x1008, 0x100C, 0x1010, 0x1014, 0x1018, 0x101C, 0x1020, 0x1024, 0x1048,
    0x104C, 0x1050, 0x1054
};

/* initialize ENET peripheral with generally concerned parameters, call it by ENET_Init() */
static void ENET_default_Init(void);
#ifdef USE_DELAY
/* user can provide more timing precise _ENET_Delay_ function */
#define _ENET_Delay_                              delay_ms
#else
/* insert a delay time */
static void ENET_delay(uint32_t ncount);
/* default _ENET_Delay_ function with less precise timing */
#define _ENET_Delay_                              ENET_delay
#endif


/*!
    简介:    deinitialize the ENET, and reset structure parameters for ENET initialization
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_DeInit(void) {
    RCU_Periph_Reset_Enable(RCU_ENETRST);
    RCU_Periph_Reset_Disable(RCU_ENETRST);
    ENET_initpara_Reset();
}

/*!
    简介:    configure the parameters which are usually less cared for initialization
                note -- this function must be called before ENET_Init(), otherwise
                configuration will be no effect
    参数[输入]:  option: different function option, which is related to several parameters, refer to ENET_option_enum
                only one parameter can be selected which is shown as below
      参数:        FORWARD_OPTION: choose to configure the frame forward related parameters
      参数:        DMABUS_OPTION: choose to configure the DMA bus mode related parameters
      参数:        DMA_MAXBURST_OPTION: choose to configure the DMA max burst related parameters
      参数:        DMA_ARBITRATION_OPTION: choose to configure the DMA arbitration related parameters
      参数:        STORE_OPTION: choose to configure the store forward mode related parameters
      参数:        DMA_OPTION: choose to configure the DMA descriptor related parameters
      参数:        VLAN_OPTION: choose to configure vlan related parameters
      参数:        FLOWCTL_OPTION: choose to configure flow control related parameters
      参数:        HASHH_OPTION: choose to configure hash high
      参数:        HASHL_OPTION: choose to configure hash low
      参数:        FILTER_OPTION: choose to configure frame filter related parameters
      参数:        HALFDUPLEX_OPTION: choose to configure halfduplex mode related parameters
      参数:        TIMER_OPTION: choose to configure time counter related parameters
      参数:        INTERFRAMEGAP_OPTION: choose to configure the inter frame gap related parameters
    参数[输入]:  para: the related parameters 根据 the option
                all the related parameters should be configured which are shown as below
                      FORWARD_OPTION related parameters:
                      -  ENET_Auto_PADCRC_DROP_ENABLE/ ENET_Auto_PADCRC_DROP_DISABLE ;
                      -  ENET_TYPEFRAME_CRC_DROP_ENABLE/ ENET_TYPEFRAME_CRC_DROP_DISABLE ;
                      -  ENET_FORWARD_ERRFRAMES_ENABLE/ ENET_FORWARD_ERRFRAMES_DISABLE ;
                      -  ENET_FORWARD_UNDERSZ_GOODFRAMES_ENABLE/ ENET_FORWARD_UNDERSZ_GOODFRAMES_DISABLE .
                      DMABUS_OPTION related parameters:
                      -  ENET_Address_ALIGN_ENABLE/ ENET_Address_ALIGN_DISABLE ;
                      -  ENET_FIXED_Burst_ENABLE/ ENET_FIXED_Burst_DISABLE ;
                      -  ENET_MIXED_Burst_ENABLE/ ENET_MIXED_Burst_DISABLE ;
                      DMA_MAXBURST_OPTION related parameters:
                      -  ENET_RXDP_1BEAT/ ENET_RXDP_2BEAT/ ENET_RXDP_4BEAT/
                         ENET_RXDP_8BEAT/ ENET_RXDP_16BEAT/ ENET_RXDP_32BEAT/
                         ENET_RXDP_4xPGBL_4BEAT/ ENET_RXDP_4xPGBL_8BEAT/
                         ENET_RXDP_4xPGBL_16BEAT/ ENET_RXDP_4xPGBL_32BEAT/
                         ENET_RXDP_4xPGBL_64BEAT/ ENET_RXDP_4xPGBL_128BEAT ;
                      -  ENET_PGBL_1BEAT/ ENET_PGBL_2BEAT/ ENET_PGBL_4BEAT/
                         ENET_PGBL_8BEAT/ ENET_PGBL_16BEAT/ ENET_PGBL_32BEAT/
                         ENET_PGBL_4xPGBL_4BEAT/ ENET_PGBL_4xPGBL_8BEAT/
                         ENET_PGBL_4xPGBL_16BEAT/ ENET_PGBL_4xPGBL_32BEAT/
                         ENET_PGBL_4xPGBL_64BEAT/ ENET_PGBL_4xPGBL_128BEAT ;
                      -  ENET_RXTX_DIFFERENT_PGBL/ ENET_RXTX_SAME_PGBL ;
                      DMA_ARBITRATION_OPTION related parameters:
                      -  ENET_ARBITRATION_RXPRIORTX
                      -  ENET_ARBITRATION_RXTX_1_1/ ENET_ARBITRATION_RXTX_2_1/
                         ENET_ARBITRATION_RXTX_3_1/ ENET_ARBITRATION_RXTX_4_1/.
                      STORE_OPTION related parameters:
                      -  ENET_RX_Mode_STOREFORWARD/ ENET_RX_Mode_CUTTHROUGH ;
                      -  ENET_TX_Mode_STOREFORWARD/ ENET_TX_Mode_CUTTHROUGH ;
                      -  ENET_RX_Threshold_64BYTES/ ENET_RX_Threshold_32BYTES/
                         ENET_RX_Threshold_96BYTES/ ENET_RX_Threshold_128BYTES ;
                      -  ENET_TX_Threshold_64BYTES/ ENET_TX_Threshold_128BYTES/
                         ENET_TX_Threshold_192BYTES/ ENET_TX_Threshold_256BYTES/
                         ENET_TX_Threshold_40BYTES/ ENET_TX_Threshold_32BYTES/
                         ENET_TX_Threshold_24BYTES/ ENET_TX_Threshold_16BYTES .
                      DMA_OPTION related parameters:
                      -  ENET_FLUSH_RXframe_ENABLE/ ENET_FLUSH_RXframe_DISABLE ;
                      -  ENET_SECONDFRAME_OPT_ENABLE/ ENET_SECONDFRAME_OPT_DISABLE ;
                      -  ENET_Enhanced_DESCRIPTOR/ ENET_Normal_DESCRIPTOR .
                      VLAN_OPTION related parameters:
                      -  ENET_VLANTAGCOMPARISON_12BIT/ ENET_VLANTAGCOMPARISON_16BIT ;
                      -  MAC_VLT_VLTI(regval) .
                      FLOWCTL_OPTION related parameters:
                      -  MAC_FCTL_PTM(regval) ;
                      -  ENET_ZERO_QUANTA_PAUSE_ENABLE/ ENET_ZERO_QUANTA_PAUSE_DISABLE ;
                      -  ENET_PAUSETIME_MINUS4/ ENET_PAUSETIME_MINUS28/
                         ENET_PAUSETIME_MINUS144/ENET_PAUSETIME_MINUS256 ;
                      -  ENET_MAC0_AND_UNIQUE_Address_PAUSEDETECT/ ENET_UNIQUE_PAUSEDETECT ;
                      -  ENET_RX_FLOWCONTROL_ENABLE/ ENET_RX_FLOWCONTROL_DISABLE ;
                      -  ENET_TX_FLOWCONTROL_ENABLE/ ENET_TX_FLOWCONTROL_DISABLE ;
                      -  ENET_ACTIVE_Threshold_256BYTES/ ENET_ACTIVE_Threshold_512BYTES ;
                      -  ENET_ACTIVE_Threshold_768BYTES/ ENET_ACTIVE_Threshold_1024BYTES ;
                      -  ENET_ACTIVE_Threshold_1280BYTES/ ENET_ACTIVE_Threshold_1536BYTES ;
                      -  ENET_ACTIVE_Threshold_1792BYTES ;
                      -  ENET_DEACTIVE_Threshold_256BYTES/ ENET_DEACTIVE_Threshold_512BYTES ;
                      -  ENET_DEACTIVE_Threshold_768BYTES/ ENET_DEACTIVE_Threshold_1024BYTES ;
                      -  ENET_DEACTIVE_Threshold_1280BYTES/ ENET_DEACTIVE_Threshold_1536BYTES ;
                      -  ENET_DEACTIVE_Threshold_1792BYTES .
                      HASHH_OPTION related parameters:
                      -  0x0~0xFFFF FFFFU
                      HASHL_OPTION related parameters:
                      -  0x0~0xFFFF FFFFU
                      FILTER_OPTION related parameters:
                      -  ENET_SRC_Filter_Normal_ENABLE/ ENET_SRC_Filter_INVERSE_ENABLE/
                         ENET_SRC_Filter_DISABLE ;
                      -  ENET_DEST_Filter_INVERSE_ENABLE/ ENET_DEST_Filter_INVERSE_DISABLE ;
                      -  ENET_MULTICAST_Filter_HASH_OR_PERFECT/ ENET_MULTICAST_Filter_HASH/
                         ENET_MULTICAST_Filter_PERFECT/ ENET_MULTICAST_Filter_NONE ;
                      -  ENET_UNICAST_Filter_EITHER/ ENET_UNICAST_Filter_HASH/
                         ENET_UNICAST_Filter_PERFECT ;
                      -  ENET_PCFRM_PREVENT_ALL/ ENET_PCFRM_PREVENT_PAUSEFRAME/
                         ENET_PCFRM_FORWARD_ALL/ ENET_PCFRM_FORWARD_FILTERED .
                      HALFDUPLEX_OPTION related parameters:
                      -  ENET_CARRIERSENSE_ENABLE/ ENET_CARRIERSENSE_DISABLE ;
                      -  ENET_RECEIVEOWN_ENABLE/ ENET_RECEIVEOWN_DISABLE ;
                      -  ENET_RETRYTRANSMISSION_ENABLE/ ENET_RETRYTRANSMISSION_DISABLE ;
                      -  ENET_BACKOFFLIMIT_10/ ENET_BACKOFFLIMIT_8/
                         ENET_BACKOFFLIMIT_4/ ENET_BACKOFFLIMIT_1 ;
                      -  ENET_DEFERRALCHECK_ENABLE/ ENET_DEFERRALCHECK_DISABLE .
                      TIMER_OPTION related parameters:
                      -  ENET_WatchDog_ENABLE/ ENET_WatchDog_DISABLE ;
                      -  ENET_JABBER_ENABLE/ ENET_JABBER_DISABLE ;
                      INTERFRAMEGAP_OPTION related parameters:
                      -  ENET_INTERFRAMEGAP_96BIT/ ENET_INTERFRAMEGAP_88BIT/
                         ENET_INTERFRAMEGAP_80BIT/ ENET_INTERFRAMEGAP_72BIT/
                         ENET_INTERFRAMEGAP_64BIT/ ENET_INTERFRAMEGAP_56BIT/
                         ENET_INTERFRAMEGAP_48BIT/ ENET_INTERFRAMEGAP_40BIT .
    参数[输出]:  无
    返回值:      无
*/
void ENET_initpara_Config(ENET_option_enum option, uint32_t para) {
    switch(option) {
    case FORWARD_OPTION:
        /* choose to configure forward_frame, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)FORWARD_OPTION;
        ENET_initpara.forward_frame = para;
        break;

    case DMABUS_OPTION:
        /* choose to configure dmabus_mode, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)DMABUS_OPTION;
        ENET_initpara.dmabus_mode = para;
        break;

    case DMA_MAXBURST_OPTION:
        /* choose to configure DMA_maxburst, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)DMA_MAXBURST_OPTION;
        ENET_initpara.DMA_maxburst = para;
        break;

    case DMA_ARBITRATION_OPTION:
        /* choose to configure DMA_arbitration, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)DMA_ARBITRATION_OPTION;
        ENET_initpara.DMA_arbitration = para;
        break;

    case STORE_OPTION:
        /* choose to configure store_forward_mode, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)STORE_OPTION;
        ENET_initpara.store_forward_mode = para;
        break;

    case DMA_OPTION:
        /* choose to configure DMA_function, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)DMA_OPTION;

#ifndef SELECT_Descriptors_Enhanced_MODE
        para &= ~ENET_Enhanced_DESCRIPTOR;
#endif /* SELECT_Descriptors_Enhanced_MODE */

        ENET_initpara.DMA_function = para;
        break;

    case VLAN_OPTION:
        /* choose to configure vlan_Config, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)VLAN_OPTION;
        ENET_initpara.vlan_Config = para;
        break;

    case FLOWCTL_OPTION:
        /* choose to configure flow_control, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)FLOWCTL_OPTION;
        ENET_initpara.flow_control = para;
        break;

    case HASHH_OPTION:
        /* choose to configure hashtable_high, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)HASHH_OPTION;
        ENET_initpara.hashtable_high = para;
        break;

    case HASHL_OPTION:
        /* choose to configure hashtable_low, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)HASHL_OPTION;
        ENET_initpara.hashtable_low = para;
        break;

    case FILTER_OPTION:
        /* choose to configure framesfilter_mode, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)FILTER_OPTION;
        ENET_initpara.framesfilter_mode = para;
        break;

    case HALFDUPLEX_OPTION:
        /* choose to configure halfduplex_param, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)HALFDUPLEX_OPTION;
        ENET_initpara.halfduplex_param = para;
        break;

    case TIMER_OPTION:
        /* choose to configure TIMER_Config, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)TIMER_OPTION;
        ENET_initpara.TIMER_Config = para;
        break;

    case INTERFRAMEGAP_OPTION:
        /* choose to configure interframegap, and save the configuration parameters */
        ENET_initpara.option_enable |= (uint32_t)INTERFRAMEGAP_OPTION;
        ENET_initpara.interframegap = para;
        break;

    default:
        break;
    }
}

/*!
    简介:    initialize ENET peripheral with generally concerned parameters and the less cared
                parameters
    参数[输入]:  mediamode: PHY mode and mac loopback configurations, refer to ENET_mediamode_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_Auto_NEGOTIATION: PHY auto negotiation
      参数:        ENET_100M_FULLDUPLEX: 100Mbit/s, full-duplex
      参数:        ENET_100M_HALFDUPLEX: 100Mbit/s, half-duplex
      参数:        ENET_10M_FULLDUPLEX: 10Mbit/s, full-duplex
      参数:        ENET_10M_HALFDUPLEX: 10Mbit/s, half-duplex
      参数:        ENET_LOOPBACKMODE: MAC in loopback mode at the MII
    参数[输入]:  checksum: IP frame checksum offload function, refer to ENET_mediamode_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_NO_AUTOCHECKSUM: disable IP frame checksum function
      参数:        ENET_AUTOCHECKSUM_DROP_FAILFRAMES: enable IP frame checksum function
      参数:        ENET_AUTOCHECKSUM_ACCEPT_FAILFRAMES: enable IP frame checksum function, and the received frame
                                                       with only payload error but no other errors will not be dropped
    参数[输入]:  recept: frame filter function, refer to ENET_frmrecept_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_PROMISCUOUS_MODE: promiscuous mode enabled
      参数:        ENET_RECEIVEALL: all received frame are forwarded to application
      参数:        ENET_BROADCAST_FRAMES_PASS: the address filters pass all received broadcast frames
      参数:        ENET_BROADCAST_FRAMES_DROP: the address filters filter all incoming broadcast frames
    参数[输出]:  无
    返回值:     ErrStatus: ERROR or SUCCESS
*/
ErrStatus ENET_Init(ENET_mediamode_enum mediamode, ENET_chksumconf_enum checksum, ENET_frmrecept_enum recept) {
    uint32_t reg_value = 0U, reg_temp = 0U, temp = 0U;
    uint32_t media_temp = 0U;
    uint32_t timeout = 0U;
    uint16_t phy_value = 0U;
    ErrStatus phy_state = ERROR, ENET_state = ERROR;

    /* PHY interface configuration, configure SMI clock and reset PHY chip */
    if(ERROR == ENET_PHY_Config()) {
        _ENET_Delay_(PHY_RESETDELAY);

        if(ERROR == ENET_PHY_Config()) {
            return ENET_state;
        }
    }

    /* initialize ENET peripheral with generally concerned parameters */
    ENET_default_Init();

    /* 1st, configure mediamode */
    media_temp = (uint32_t)mediamode;

    /* if is PHY auto negotiation */
    if((uint32_t)ENET_Auto_NEGOTIATION == media_temp) {
        /* wait for PHY_LINKED_STATUS bit be set */
        do {
            ENET_PHY_Write_Read(ENET_PHY_READ, PHY_ADDRESS, PHY_REG_BSR, &phy_value);
            phy_value &= PHY_LINKED_STATUS;
            timeout++;
        } while((RESET == phy_value) && (timeout < PHY_READ_TO));

        /* return ERROR due to timeout */
        if(PHY_READ_TO == timeout) {
            return ENET_state;
        }

        /* reset timeout counter */
        timeout = 0U;

        /* enable auto-negotiation */
        phy_value = PHY_AUTONEGOTIATION;
        phy_state = ENET_PHY_Write_Read(ENET_PHY_WRITE, PHY_ADDRESS, PHY_REG_BCR, &phy_value);

        if(!phy_state) {
            /* return ERROR due to 写入超时 */
            return ENET_state;
        }

        /* wait for the PHY_AUTONEGO_COMPLETE bit be set */
        do {
            ENET_PHY_Write_Read(ENET_PHY_READ, PHY_ADDRESS, PHY_REG_BSR, &phy_value);
            phy_value &= PHY_AUTONEGO_COMPLETE;
            timeout++;
        } while((RESET == phy_value) && (timeout < (uint32_t)PHY_READ_TO));

        /* return ERROR due to timeout */
        if(PHY_READ_TO == timeout) {
            return ENET_state;
        }

        /* reset timeout counter */
        timeout = 0U;

        /* read the result of the auto-negotiation */
        ENET_PHY_Write_Read(ENET_PHY_READ, PHY_ADDRESS, PHY_SR, &phy_value);

        /* configure the duplex mode of MAC following the auto-negotiation result */
        if((uint16_t)RESET != (phy_value & PHY_DUPLEX_STATUS)) {
            media_temp = ENET_Mode_FULLDUPLEX;
        } else {
            media_temp = ENET_Mode_HALFDUPLEX;
        }

        /* configure the communication speed of MAC following the auto-negotiation result */
        if((uint16_t)RESET != (phy_value & PHY_SPEED_STATUS)) {
            media_temp |= ENET_SPEEDMODE_10M;
        } else {
            media_temp |= ENET_SPEEDMODE_100M;
        }
    } else {
        phy_value = (uint16_t)((media_temp & ENET_MAC_CFG_DPM) >> 3);
        phy_value |= (uint16_t)((media_temp & ENET_MAC_CFG_SPD) >> 1);
        phy_state = ENET_PHY_Write_Read(ENET_PHY_WRITE, PHY_ADDRESS, PHY_REG_BCR, &phy_value);

        if(!phy_state) {
            /* return ERROR due to 写入超时 */
            return ENET_state;
        }

        /* PHY configuration need some time */
        _ENET_Delay_(PHY_ConfigDELAY);
    }

    /* after configuring the PHY, use mediamode to configure registers */
    reg_value = ENET_MAC_CFG;
    /* configure ENET_MAC_CFG register */
    reg_value &= (~(ENET_MAC_CFG_SPD | ENET_MAC_CFG_DPM | ENET_MAC_CFG_LBM));
    reg_value |= media_temp;
    ENET_MAC_CFG = reg_value;


    /* 2st, configure checksum */
    if(RESET != ((uint32_t)checksum & ENET_CHECKSUMOFFLOAD_ENABLE)) {
        ENET_MAC_CFG |= ENET_CHECKSUMOFFLOAD_ENABLE;

        reg_value = ENET_DMA_CTL;
        /* configure ENET_DMA_CTL register */
        reg_value &= ~ENET_DMA_CTL_DTCERFD;
        reg_value |= ((uint32_t)checksum & ENET_DMA_CTL_DTCERFD);
        ENET_DMA_CTL = reg_value;
    }

    /* 3rd, configure recept */
    ENET_MAC_FRMF |= (uint32_t)recept;

    /* 4th, configure different function options */
    /* configure forward_frame related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)FORWARD_OPTION)) {
        reg_temp = ENET_initpara.forward_frame;

        reg_value = ENET_MAC_CFG;
        temp = reg_temp;
        /* configure ENET_MAC_CFG register */
        reg_value &= (~(ENET_MAC_CFG_TFCD | ENET_MAC_CFG_APCD));
        temp &= (ENET_MAC_CFG_TFCD | ENET_MAC_CFG_APCD);
        reg_value |= temp;
        ENET_MAC_CFG = reg_value;

        reg_value = ENET_DMA_CTL;
        temp = reg_temp;
        /* configure ENET_DMA_CTL register */
        reg_value &= (~(ENET_DMA_CTL_FERF | ENET_DMA_CTL_FUF));
        temp &= ((ENET_DMA_CTL_FERF | ENET_DMA_CTL_FUF) << 2);
        reg_value |= (temp >> 2);
        ENET_DMA_CTL = reg_value;
    }

    /* configure dmabus_mode related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)DMABUS_OPTION)) {
        temp = ENET_initpara.dmabus_mode;

        reg_value = ENET_DMA_BCTL;
        /* configure ENET_DMA_BCTL register */
        reg_value &= ~(ENET_DMA_BCTL_AA | ENET_DMA_BCTL_FB \
                       | ENET_DMA_BCTL_FPBL | ENET_DMA_BCTL_MB);
        reg_value |= temp;
        ENET_DMA_BCTL = reg_value;
    }

    /* configure DMA_maxburst related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)DMA_MAXBURST_OPTION)) {
        temp = ENET_initpara.DMA_maxburst;

        reg_value = ENET_DMA_BCTL;
        /* configure ENET_DMA_BCTL register */
        reg_value &= ~(ENET_DMA_BCTL_RXDP | ENET_DMA_BCTL_PGBL | ENET_DMA_BCTL_UIP);
        reg_value |= temp;
        ENET_DMA_BCTL = reg_value;
    }

    /* configure DMA_arbitration related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)DMA_ARBITRATION_OPTION)) {
        temp = ENET_initpara.DMA_arbitration;

        reg_value = ENET_DMA_BCTL;
        /* configure ENET_DMA_BCTL register */
        reg_value &= ~(ENET_DMA_BCTL_RTPR | ENET_DMA_BCTL_DAB);
        reg_value |= temp;
        ENET_DMA_BCTL = reg_value;
    }

    /* configure store_forward_mode related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)STORE_OPTION)) {
        temp = ENET_initpara.store_forward_mode;

        reg_value = ENET_DMA_CTL;
        /* configure ENET_DMA_CTL register */
        reg_value &= ~(ENET_DMA_CTL_RSFD | ENET_DMA_CTL_TSFD | ENET_DMA_CTL_RTHC | ENET_DMA_CTL_TTHC);
        reg_value |= temp;
        ENET_DMA_CTL = reg_value;
    }

    /* configure DMA_function related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)DMA_OPTION)) {
        reg_temp = ENET_initpara.DMA_function;

        reg_value = ENET_DMA_CTL;
        temp = reg_temp;
        /* configure ENET_DMA_CTL register */
        reg_value &= (~(ENET_DMA_CTL_DAFRF | ENET_DMA_CTL_OSF));
        temp &= (ENET_DMA_CTL_DAFRF | ENET_DMA_CTL_OSF);
        reg_value |= temp;
        ENET_DMA_CTL = reg_value;

        reg_value = ENET_DMA_BCTL;
        temp = reg_temp;
        /* configure ENET_DMA_BCTL register */
        reg_value &= (~ENET_DMA_BCTL_DFM);
        temp &= ENET_DMA_BCTL_DFM;
        reg_value |= temp;
        ENET_DMA_BCTL = reg_value;
    }

    /* configure vlan_Config related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)VLAN_OPTION)) {
        reg_temp = ENET_initpara.vlan_Config;

        reg_value = ENET_MAC_VLT;
        /* configure ENET_MAC_VLT register */
        reg_value &= ~(ENET_MAC_VLT_VLTI | ENET_MAC_VLT_VLTC);
        reg_value |= reg_temp;
        ENET_MAC_VLT = reg_value;
    }

    /* configure flow_control related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)FLOWCTL_OPTION)) {
        reg_temp = ENET_initpara.flow_control;

        reg_value = ENET_MAC_FCTL;
        temp = reg_temp;
        /* configure ENET_MAC_FCTL register */
        reg_value &= ~(ENET_MAC_FCTL_PTM | ENET_MAC_FCTL_DZQP | ENET_MAC_FCTL_PLTS \
                       | ENET_MAC_FCTL_UPFDT | ENET_MAC_FCTL_RFCEN | ENET_MAC_FCTL_TFCEN);
        temp &= (ENET_MAC_FCTL_PTM | ENET_MAC_FCTL_DZQP | ENET_MAC_FCTL_PLTS \
                 | ENET_MAC_FCTL_UPFDT | ENET_MAC_FCTL_RFCEN | ENET_MAC_FCTL_TFCEN);
        reg_value |= temp;
        ENET_MAC_FCTL = reg_value;

        reg_value = ENET_MAC_FCTH;
        temp = reg_temp;
        /* configure ENET_MAC_FCTH register */
        reg_value &= ~(ENET_MAC_FCTH_RFA | ENET_MAC_FCTH_RFD);
        temp &= ((ENET_MAC_FCTH_RFA | ENET_MAC_FCTH_RFD) << 8);
        reg_value |= (temp >> 8);
        ENET_MAC_FCTH = reg_value;
    }

    /* configure hashtable_high related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)HASHH_OPTION)) {
        ENET_MAC_HLH = ENET_initpara.hashtable_high;
    }

    /* configure hashtable_low related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)HASHL_OPTION)) {
        ENET_MAC_HLL = ENET_initpara.hashtable_low;
    }

    /* configure framesfilter_mode related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)FILTER_OPTION)) {
        reg_temp = ENET_initpara.framesfilter_mode;

        reg_value = ENET_MAC_FRMF;
        /* configure ENET_MAC_FRMF register */
        reg_value &= ~(ENET_MAC_FRMF_SAFLT | ENET_MAC_FRMF_SAIFLT | ENET_MAC_FRMF_DAIFLT \
                       | ENET_MAC_FRMF_HMF | ENET_MAC_FRMF_HPFLT | ENET_MAC_FRMF_MFD \
                       | ENET_MAC_FRMF_HUF | ENET_MAC_FRMF_PCFRM);
        reg_value |= reg_temp;
        ENET_MAC_FRMF = reg_value;
    }

    /* configure halfduplex_param related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)HALFDUPLEX_OPTION)) {
        reg_temp = ENET_initpara.halfduplex_param;

        reg_value = ENET_MAC_CFG;
        /* configure ENET_MAC_CFG register */
        reg_value &= ~(ENET_MAC_CFG_CSD | ENET_MAC_CFG_ROD | ENET_MAC_CFG_RTD \
                       | ENET_MAC_CFG_BOL | ENET_MAC_CFG_DFC);
        reg_value |= reg_temp;
        ENET_MAC_CFG = reg_value;
    }

    /* configure TIMER_Config related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)TIMER_OPTION)) {
        reg_temp = ENET_initpara.TIMER_Config;

        reg_value = ENET_MAC_CFG;
        /* configure ENET_MAC_CFG register */
        reg_value &= ~(ENET_MAC_CFG_WDD | ENET_MAC_CFG_JBD);
        reg_value |= reg_temp;
        ENET_MAC_CFG = reg_value;
    }

    /* configure interframegap related registers */
    if(RESET != (ENET_initpara.option_enable & (uint32_t)INTERFRAMEGAP_OPTION)) {
        reg_temp = ENET_initpara.interframegap;

        reg_value = ENET_MAC_CFG;
        /* configure ENET_MAC_CFG register */
        reg_value &= ~ENET_MAC_CFG_IGBS;
        reg_value |= reg_temp;
        ENET_MAC_CFG = reg_value;
    }

    ENET_state = SUCCESS;
    return ENET_state;
}

/*!
    简介:    reset all core internal registers located in CLK_TX and CLK_RX
    参数[输入]:  无
    参数[输出]:  无
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_Software_Reset(void) {
    uint32_t timeout = 0U;
    ErrStatus ENET_state = ERROR;
    uint32_t DMA_flag;

    /* reset all core internal registers located in CLK_TX and CLK_RX */
    ENET_DMA_BCTL |= ENET_DMA_BCTL_SWR;

    /* wait for reset operation complete */
    do {
        DMA_flag = (ENET_DMA_BCTL & ENET_DMA_BCTL_SWR);
        timeout++;
    } while((RESET != DMA_flag) && (ENET_Delay_TO != timeout));

    /* reset operation complete */
    if(RESET == (ENET_DMA_BCTL & ENET_DMA_BCTL_SWR)) {
        ENET_state = SUCCESS;
    }

    return ENET_state;
}

/*!
    简介:    check receive frame valid and return frame size
    参数[输入]:  无
    参数[输出]:  无
    返回值:     size of received frame: 0x0 - 0x3FFF
*/
uint32_t ENET_RXframe_size_Get(void) {
    uint32_t size = 0U;
    uint32_t status;

    /* get rdes0 information of current RxDMA descriptor */
    status = DMA_Current_rxdesc->status;

    /* if the desciptor is owned by DMA */
    if((uint32_t)RESET != (status & ENET_RDES0_DAV)) {
        return 0U;
    }

    /* if has any error, or the frame uses two or more descriptors */
    if((((uint32_t)RESET) != (status & ENET_RDES0_ERRS)) ||
            (((uint32_t)RESET) == (status & ENET_RDES0_LDES)) ||
            (((uint32_t)RESET) == (status & ENET_RDES0_FDES))) {
        /* drop current receive frame */
        ENET_RXframe_Drop();

        return 1U;
    }

#ifdef SELECT_Descriptors_Enhanced_MODE

    /* if is an ethernet-type frame, and IP frame payload error occurred */
    if(((uint32_t)RESET) != (DMA_Current_rxdesc->status & ENET_RDES0_FRMT) &&
            ((uint32_t)RESET) != (DMA_Current_rxdesc->extended_status & ENET_RDES4_IPPLDERR)) {
        /* drop current receive frame */
        ENET_RXframe_Drop();

        return 1U;
    }

#else

    /* if is an ethernet-type frame, and IP frame payload error occurred */
    if((((uint32_t)RESET) != (status & ENET_RDES0_FRMT)) &&
            (((uint32_t)RESET) != (status & ENET_RDES0_PCERR))) {
        /* drop current receive frame */
        ENET_RXframe_Drop();

        return 1U;
    }

#endif

    /* if CPU owns current descriptor, no error occured, the frame uses only one descriptor */
    if((((uint32_t)RESET) == (status & ENET_RDES0_DAV)) &&
            (((uint32_t)RESET) == (status & ENET_RDES0_ERRS)) &&
            (((uint32_t)RESET) != (status & ENET_RDES0_LDES)) &&
            (((uint32_t)RESET) != (status & ENET_RDES0_FDES))) {
        /* get the size of the received data including CRC */
        size = GET_RDES0_FRML(status);
        /* substract the CRC size */
        size = size - 4U;

        /* if is a type frame, and CRC is not included in forwarding frame */
        if((RESET != (ENET_MAC_CFG & ENET_MAC_CFG_TFCD)) && (RESET != (status & ENET_RDES0_FRMT))) {
            size = size + 4U;
        }
    } else {
        ENET_unknow_err++;
        ENET_RXframe_Drop();

        return 1U;
    }

    /* return packet size */
    return size;
}

/*!
    简介:    initialize the DMA Tx/Rx descriptors's parameters in chain mode
    参数[输入]:  direction: the descriptors which users want to init, refer to ENET_dmadirection_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_TX: DMA Tx descriptors
      参数:        ENET_DMA_RX: DMA Rx descriptors
    参数[输出]:  无
    返回值:      无
*/
void ENET_Descriptors_Chain_Init(ENET_dmadirection_enum direction) {
    uint32_t num = 0U, count = 0U, maxsize = 0U;
    uint32_t desc_status = 0U, desc_bufsize = 0U;
    ENET_Descriptors_Struct *desc, *desc_tab;
    uint8_t *buf;

    /* if want to initialize DMA Tx descriptors */
    if(ENET_DMA_TX == direction) {
        /* save a copy of the DMA Tx descriptors */
        desc_tab = txdesc_tab;
        buf = &tx_buff[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        /* select chain mode */
        desc_status = ENET_TDES0_TCHM;

        /* configure DMA Tx descriptor table address register */
        ENET_DMA_TDTADDR = (uint32_t)desc_tab;
        DMA_Current_txdesc = desc_tab;
    } else {
        /* if want to initialize DMA Rx descriptors */
        /* save a copy of the DMA Rx descriptors */
        desc_tab = rxdesc_tab;
        buf = &rx_buff[0][0];
        count = ENET_RXBUF_NUM;
        maxsize = ENET_RXBUF_SIZE;

        /* enable receiving */
        desc_status = ENET_RDES0_DAV;
        /* select receive chained mode and set buffer1 size */
        desc_bufsize = ENET_RDES1_RCHM | (uint32_t)ENET_RXBUF_SIZE;

        /* configure DMA Rx descriptor table address register */
        ENET_DMA_RDTADDR = (uint32_t)desc_tab;
        DMA_Current_rxdesc = desc_tab;
    }

    DMA_Current_PTP_rxdesc = NULL;
    DMA_Current_PTP_txdesc = NULL;

    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->status = desc_status;
        desc->control_Buffer_size = desc_bufsize;
        desc->buffer1_addr = (uint32_t)(&buf[num * maxsize]);

        /* if is not the last descriptor */
        if(num < (count - 1U)) {
            /* configure the next descriptor address */
            desc->buffer2_next_Desc_addr = (uint32_t)(desc_tab + num + 1U);
        } else {
            /* when it is the last descriptor, the next descriptor address
            equals to first descriptor address in descriptor table */
            desc->buffer2_next_Desc_addr = (uint32_t) desc_tab;
        }
    }
}

/*!
    简介:    initialize the DMA Tx/Rx descriptors's parameters in ring mode
    参数[输入]:  direction: the descriptors which users want to init, refer to ENET_dmadirection_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_TX: DMA Tx descriptors
      参数:        ENET_DMA_RX: DMA Rx descriptors
    参数[输出]:  无
    返回值:      无
*/
void ENET_Descriptors_Ring_Init(ENET_dmadirection_enum direction) {
    uint32_t num = 0U, count = 0U, maxsize = 0U;
    uint32_t desc_status = 0U, desc_bufsize = 0U;
    ENET_Descriptors_Struct *desc;
    ENET_Descriptors_Struct *desc_tab;
    uint8_t *buf;

    /* configure descriptor skip length */
    ENET_DMA_BCTL &= ~ENET_DMA_BCTL_DPSL;
    ENET_DMA_BCTL |= DMA_BCTL_DPSL(0);

    /* if want to initialize DMA Tx descriptors */
    if(ENET_DMA_TX == direction) {
        /* save a copy of the DMA Tx descriptors */
        desc_tab = txdesc_tab;
        buf = &tx_buff[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        /* configure DMA Tx descriptor table address register */
        ENET_DMA_TDTADDR = (uint32_t)desc_tab;
        DMA_Current_txdesc = desc_tab;
    } else {
        /* if want to initialize DMA Rx descriptors */
        /* save a copy of the DMA Rx descriptors */
        desc_tab = rxdesc_tab;
        buf = &rx_buff[0][0];
        count = ENET_RXBUF_NUM;
        maxsize = ENET_RXBUF_SIZE;

        /* enable receiving */
        desc_status = ENET_RDES0_DAV;
        /* set buffer1 size */
        desc_bufsize = ENET_RXBUF_SIZE;

        /* configure DMA Rx descriptor table address register */
        ENET_DMA_RDTADDR = (uint32_t)desc_tab;
        DMA_Current_rxdesc = desc_tab;
    }

    DMA_Current_PTP_rxdesc = NULL;
    DMA_Current_PTP_txdesc = NULL;

    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->status = desc_status;
        desc->control_Buffer_size = desc_bufsize;
        desc->buffer1_addr = (uint32_t)(&buf[num * maxsize]);

        /* when it is the last descriptor */
        if(num == (count - 1U)) {
            if(ENET_DMA_TX == direction) {
                /* configure transmit end of ring mode */
                desc->status |= ENET_TDES0_TERM;
            } else {
                /* configure receive end of ring mode */
                desc->control_Buffer_size |= ENET_RDES1_RERM;
            }
        }
    }
}

/*!
    简介:    handle current received frame data to application buffer
    参数[输入]:  bufsize: the size of buffer which is the parameter in function
    参数[输出]: buffer: pointer to the received frame data
                note -- if the input is NULL, user should copy data in application by himself
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_Frame_Receive(uint8_t *buffer, uint32_t bufsize) {
    uint32_t offset = 0U, size = 0U;

    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (DMA_Current_rxdesc->status & ENET_RDES0_DAV)) {
        return ERROR;
    }


    /* if buffer pointer is null, indicates that users has copied data in application */
    if(NULL != buffer) {
        /* if no error occurs, and the frame uses only one descriptor */
        if((((uint32_t)RESET) == (DMA_Current_rxdesc->status & ENET_RDES0_ERRS)) &&
                (((uint32_t)RESET) != (DMA_Current_rxdesc->status & ENET_RDES0_LDES)) &&
                (((uint32_t)RESET) != (DMA_Current_rxdesc->status & ENET_RDES0_FDES))) {
            /* get the frame length except CRC */
            size = GET_RDES0_FRML(DMA_Current_rxdesc->status);
            size = size - 4U;

            /* if is a type frame, and CRC is not included in forwarding frame */
            if((RESET != (ENET_MAC_CFG & ENET_MAC_CFG_TFCD)) && (RESET != (DMA_Current_rxdesc->status & ENET_RDES0_FRMT))) {
                size = size + 4U;
            }

            /* to avoid situation that the frame size exceeds the buffer length */
            if(size > bufsize) {
                return ERROR;
            }

            /* copy data from Rx buffer to application buffer */
            for(offset = 0U; offset < size; offset++) {
                (*(buffer + offset)) = (*(__IO uint8_t *)(uint32_t)((DMA_Current_rxdesc->buffer1_addr) + offset));
            }

        } else {
            /* return ERROR */
            return ERROR;
        }
    }

    /* enable reception, descriptor is owned by DMA */
    DMA_Current_rxdesc->status = ENET_RDES0_DAV;

    /* check Rx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_STAT & ENET_DMA_STAT_RBU)) {
        /* clear RBU flag */
        ENET_DMA_STAT = ENET_DMA_STAT_RBU;
        /* resume DMA reception by writing to the RPEN register*/
        ENET_DMA_RPEN = 0U;
    }

    /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
    /* chained mode */
    if((uint32_t)RESET != (DMA_Current_rxdesc->control_Buffer_size & ENET_RDES1_RCHM)) {
        DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_rxdesc->buffer2_next_Desc_addr);
    } else {
        /* ring mode */
        if((uint32_t)RESET != (DMA_Current_rxdesc->control_Buffer_size & ENET_RDES1_RERM)) {
            /* if is the last descriptor in table, the next descriptor is the table header */
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(ENET_DMA_RDTADDR);
        } else {
            /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(uint32_t)((uint32_t)DMA_Current_rxdesc + ETH_DMARXDESC_SIZE + (GET_DMA_BCTL_DPSL(ENET_DMA_BCTL)));
        }
    }

    return SUCCESS;
}

/*!
    简介:    handle application buffer data to transmit it
    参数[输入]:  buffer: pointer to the frame data to be transmitted,
                note -- if the input is NULL, user should handle the data in application by himself
    参数[输入]:  length: the length of frame data to be transmitted
    参数[输出]:  无
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_Frame_Transmit(uint8_t *buffer, uint32_t length) {
    uint32_t offset = 0U;
    uint32_t DMA_tbu_flag, DMA_tu_flag;

    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_DAV)) {
        return ERROR;
    }

    /* only frame length no more than ENET_MAX_Frame_SIZE is allowed */
    if(length > ENET_MAX_Frame_SIZE) {
        return ERROR;
    }

    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0U; offset < length; offset++) {
            (*(__IO uint8_t *)(uint32_t)((DMA_Current_txdesc->buffer1_addr) + offset)) = (*(buffer + offset));
        }
    }

    /* set the frame length */
    DMA_Current_txdesc->control_Buffer_size = length;
    /* set the segment of frame, frame is transmitted in one descriptor */
    DMA_Current_txdesc->status |= ENET_TDES0_LSG | ENET_TDES0_FSG;
    /* enable the DMA transmission */
    DMA_Current_txdesc->status |= ENET_TDES0_DAV;

    /* check Tx buffer unavailable flag status */
    DMA_tbu_flag = (ENET_DMA_STAT & ENET_DMA_STAT_TBU);
    DMA_tu_flag = (ENET_DMA_STAT & ENET_DMA_STAT_TU);

    if((RESET != DMA_tbu_flag) || (RESET != DMA_tu_flag)) {
        /* clear TBU and TU flag */
        ENET_DMA_STAT = (DMA_tbu_flag | DMA_tu_flag);
        /* resume DMA transmission by writing to the TPEN register*/
        ENET_DMA_TPEN = 0U;
    }

    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table*/
    /* chained mode */
    if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_TCHM)) {
        DMA_Current_txdesc = (ENET_Descriptors_Struct *)(DMA_Current_txdesc->buffer2_next_Desc_addr);
    } else {
        /* ring mode */
        if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_TERM)) {
            /* if is the last descriptor in table, the next descriptor is the table header */
            DMA_Current_txdesc = (ENET_Descriptors_Struct *)(ENET_DMA_TDTADDR);
        } else {
            /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
            DMA_Current_txdesc = (ENET_Descriptors_Struct *)(uint32_t)((uint32_t)DMA_Current_txdesc + ETH_DMATXDESC_SIZE + (GET_DMA_BCTL_DPSL(ENET_DMA_BCTL)));
        }
    }

    return SUCCESS;
}

/*!
    简介:    configure the transmit IP frame checksum offload calculation and insertion
    参数[输入]:  desc: the descriptor pointer which users want to configure, refer to ENET_Descriptors_Struct
    参数[输入]:  checksum: IP frame checksum configuration
                only one parameter can be selected which is shown as below
      参数:        ENET_CHECKSUM_DISABLE: checksum insertion disabled
      参数:        ENET_CHECKSUM_IPV4HEADER: only IP header checksum calculation and insertion are enabled
      参数:        ENET_CHECKSUM_TCPUDPICMP_SEGMENT: TCP/UDP/ICMP checksum insertion calculated but pseudo-header
      参数:        ENET_CHECKSUM_TCPUDPICMP_FULL: TCP/UDP/ICMP checksum insertion fully calculated
    参数[输出]:  无
    返回值:      无
*/
void ENET_Transmit_checksum_Config(ENET_Descriptors_Struct *desc, uint32_t checksum) {
    desc->status &= ~ENET_TDES0_CM;
    desc->status |= checksum;
}

/*!
    简介:    ENET Tx and Rx function enable (include MAC and DMA module)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_Enable(void) {
    ENET_TX_Enable();
    ENET_RX_Enable();
}

/*!
    简介:    ENET Tx and Rx function disable (include MAC and DMA module)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_Disable(void) {
    ENET_TX_Disable();
    ENET_RX_Disable();
}

/*!
    简介:    configure MAC address
    参数[输入]:  mac_addr: select which MAC address will be set, refer to ENET_macaddress_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_ADDRESS0: set MAC address 0 filter
      参数:        ENET_MAC_ADDRESS1: set MAC address 1 filter
      参数:        ENET_MAC_ADDRESS2: set MAC address 2 filter
      参数:        ENET_MAC_ADDRESS3: set MAC address 3 filter
    参数[输入]:  paddr: the buffer pointer which stores the MAC address
                  (little-ending store, such as MAC address is aa:bb:cc:dd:ee:22, the buffer is {22, ee, dd, cc, bb, aa})
    参数[输出]:  无
    返回值:      无
*/
void ENET_mac_Address_Set(ENET_macaddress_enum mac_addr, uint8_t paddr[]) {
    REG32(ENET_ADDRH_BASE + (uint32_t)mac_addr) = ENET_SET_MACADDRH(paddr);
    REG32(ENET_ADDRL_BASE + (uint32_t)mac_addr) = ENET_SET_MACADDRL(paddr);
}

/*!
    简介:    get MAC address
    参数[输入]:  mac_addr: select which MAC address will be get, refer to ENET_macaddress_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_ADDRESS0: get MAC address 0 filter
      参数:        ENET_MAC_ADDRESS1: get MAC address 1 filter
      参数:        ENET_MAC_ADDRESS2: get MAC address 2 filter
      参数:        ENET_MAC_ADDRESS3: get MAC address 3 filter
    参数[输出]: paddr: the buffer pointer which is stored the MAC address
                  (little-ending store, such as mac address is aa:bb:cc:dd:ee:22, the buffer is {22, ee, dd, cc, bb, aa})
    返回值:      无
*/
void ENET_mac_Address_Get(ENET_macaddress_enum mac_addr, uint8_t paddr[]) {
    paddr[0] = ENET_GET_MACADDR(mac_addr, 0U);
    paddr[1] = ENET_GET_MACADDR(mac_addr, 1U);
    paddr[2] = ENET_GET_MACADDR(mac_addr, 2U);
    paddr[3] = ENET_GET_MACADDR(mac_addr, 3U);
    paddr[4] = ENET_GET_MACADDR(mac_addr, 4U);
    paddr[5] = ENET_GET_MACADDR(mac_addr, 5U);
}

/*!
    简介:    get the ENET MAC/MSC/PTP/DMA status flag
    参数[输入]:  ENET_flag: ENET status flag, refer to ENET_Flag_enum,
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_Flag_MPKR: magic packet received flag
      参数:        ENET_MAC_Flag_WUFR: wakeup frame received flag
      参数:        ENET_MAC_Flag_FLOWCONTROL: flow control status flag
      参数:        ENET_MAC_Flag_WUM: WUM status flag
      参数:        ENET_MAC_Flag_MSC: MSC status flag
      参数:        ENET_MAC_Flag_MSCR: MSC receive status flag
      参数:        ENET_MAC_Flag_MSCT: MSC transmit status flag
      参数:        ENET_MAC_Flag_TMST: time stamp trigger status flag
      参数:        ENET_PTP_Flag_TSSCO: timestamp second counter overflow flag
      参数:        ENET_PTP_Flag_TTM: target time match flag
      参数:        ENET_MSC_Flag_RFCE: received frames CRC error flag
      参数:        ENET_MSC_Flag_RFAE: received frames alignment error flag
      参数:        ENET_MSC_Flag_RGUF: received good unicast frames flag
      参数:        ENET_MSC_Flag_TGFSC: transmitted good frames single collision flag
      参数:        ENET_MSC_Flag_TGFMSC: transmitted good frames more single collision flag
      参数:        ENET_MSC_Flag_TGF: transmitted good frames flag
      参数:        ENET_DMA_Flag_TS: transmit status flag
      参数:        ENET_DMA_Flag_TPS: transmit process stopped status flag
      参数:        ENET_DMA_Flag_TBU: transmit buffer unavailable status flag
      参数:        ENET_DMA_Flag_TJT: transmit jabber timeout status flag
      参数:        ENET_DMA_Flag_RO: receive overflow status flag
      参数:        ENET_DMA_Flag_TU: transmit underflow status flag
      参数:        ENET_DMA_Flag_RS: receive status flag
      参数:        ENET_DMA_Flag_RBU: receive buffer unavailable status flag
      参数:        ENET_DMA_Flag_RPS: receive process stopped status flag
      参数:        ENET_DMA_Flag_RWT: receive watchdog timeout status flag
      参数:        ENET_DMA_Flag_ET: early transmit status flag
      参数:        ENET_DMA_Flag_FBE: fatal bus error status flag
      参数:        ENET_DMA_Flag_ER: early receive status flag
      参数:        ENET_DMA_Flag_AI: abnormal interrupt summary flag
      参数:        ENET_DMA_Flag_NI: normal interrupt summary flag
      参数:        ENET_DMA_Flag_EB_DMA_ERROR: DMA error flag
      参数:        ENET_DMA_Flag_EB_Transfer_ERROR: transfer error flag
      参数:        ENET_DMA_Flag_EB_ACCESS_ERROR: access error flag
      参数:        ENET_DMA_Flag_MSC: MSC status flag
      参数:        ENET_DMA_Flag_WUM: WUM status flag
      参数:        ENET_DMA_Flag_TST: timestamp trigger status flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus ENET_Flag_Get(ENET_Flag_enum ENET_flag) {
    if(RESET != (ENET_REG_VAL(ENET_flag) & BIT(ENET_Bit_POS(ENET_flag)))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    简介:    clear the ENET DMA status flag
    参数[输入]:  ENET_flag: ENET DMA flag clear, refer to ENET_Flag_Clear_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_Flag_TS_CLR: transmit status flag clear
      参数:        ENET_DMA_Flag_TPS_CLR: transmit process stopped status flag clear
      参数:        ENET_DMA_Flag_TBU_CLR: transmit buffer unavailable status flag clear
      参数:        ENET_DMA_Flag_TJT_CLR: transmit jabber timeout status flag clear
      参数:        ENET_DMA_Flag_RO_CLR: receive overflow status flag clear
      参数:        ENET_DMA_Flag_TU_CLR: transmit underflow status flag clear
      参数:        ENET_DMA_Flag_RS_CLR: receive status flag clear
      参数:        ENET_DMA_Flag_RBU_CLR: receive buffer unavailable status flag clear
      参数:        ENET_DMA_Flag_RPS_CLR: receive process stopped status flag clear
      参数:        ENET_DMA_Flag_RWT_CLR: receive watchdog timeout status flag clear
      参数:        ENET_DMA_Flag_ET_CLR: early transmit status flag clear
      参数:        ENET_DMA_Flag_FBE_CLR: fatal bus error status flag clear
      参数:        ENET_DMA_Flag_ER_CLR: early receive status flag clear
      参数:        ENET_DMA_Flag_AI_CLR: abnormal interrupt summary flag clear
      参数:        ENET_DMA_Flag_NI_CLR: normal interrupt summary flag clear
    参数[输出]:  无
    返回值:      无
*/
void ENET_Flag_Clear(ENET_Flag_Clear_enum ENET_flag) {
    /* write 1 to the corresponding bit in ENET_DMA_STAT, to clear it */
    ENET_REG_VAL(ENET_flag) = BIT(ENET_Bit_POS(ENET_flag));
}

/*!
    简介:    enable ENET MAC/MSC/DMA interrupt
    参数[输入]:  ENET_int: ENET interrupt,, refer to ENET_int_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_INT_WUMIM: WUM interrupt mask
      参数:        ENET_MAC_INT_TMSTIM: timestamp trigger interrupt mask
      参数:        ENET_MSC_INT_RFCEIM: received frame CRC error interrupt mask
      参数:        ENET_MSC_INT_RFAEIM: received frames alignment error interrupt mask
      参数:        ENET_MSC_INT_RGUFIM: received good unicast frames interrupt mask
      参数:        ENET_MSC_INT_TGFSCIM: transmitted good frames single collision interrupt mask
      参数:        ENET_MSC_INT_TGFMSCIM: transmitted good frames more single collision interrupt mask
      参数:        ENET_MSC_INT_TGFIM: transmitted good frames interrupt mask
      参数:        ENET_DMA_INT_TIE: transmit interrupt enable
      参数:        ENET_DMA_INT_TPSIE: transmit process stopped interrupt enable
      参数:        ENET_DMA_INT_TBUIE: transmit buffer unavailable interrupt enable
      参数:        ENET_DMA_INT_TJTIE: transmit jabber timeout interrupt enable
      参数:        ENET_DMA_INT_ROIE: receive overflow interrupt enable
      参数:        ENET_DMA_INT_TUIE: transmit underflow interrupt enable
      参数:        ENET_DMA_INT_RIE: receive interrupt enable
      参数:        ENET_DMA_INT_RBUIE: receive buffer unavailable interrupt enable
      参数:        ENET_DMA_INT_RPSIE: receive process stopped interrupt enable
      参数:        ENET_DMA_INT_RWTIE: receive watchdog timeout interrupt enable
      参数:        ENET_DMA_INT_ETIE: early transmit interrupt enable
      参数:        ENET_DMA_INT_FBEIE: fatal bus error interrupt enable
      参数:        ENET_DMA_INT_ERIE: early receive interrupt enable
      参数:        ENET_DMA_INT_AIE: abnormal interrupt summary enable
      参数:        ENET_DMA_INT_NIE: normal interrupt summary enable
    参数[输出]:  无
    返回值:      无
*/
void ENET_Interrupt_Enable(ENET_int_enum ENET_int) {
    if(DMA_INTEN_REG_OFFSET == ((uint32_t)ENET_int >> 6)) {
        /* ENET_DMA_INTEN register 中断 */
        ENET_REG_VAL(ENET_int) |= BIT(ENET_Bit_POS(ENET_int));
    } else {
        /* other INTMSK register 中断 */
        ENET_REG_VAL(ENET_int) &= ~BIT(ENET_Bit_POS(ENET_int));
    }
}

/*!
    简介:    disable ENET MAC/MSC/DMA interrupt
    参数[输入]:  ENET_int: ENET interrupt, refer to ENET_int_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_INT_WUMIM: WUM interrupt mask
      参数:        ENET_MAC_INT_TMSTIM: timestamp trigger interrupt mask
      参数:        ENET_MSC_INT_RFCEIM: received frame CRC error interrupt mask
      参数:        ENET_MSC_INT_RFAEIM: received frames alignment error interrupt mask
      参数:        ENET_MSC_INT_RGUFIM: received good unicast frames interrupt mask
      参数:        ENET_MSC_INT_TGFSCIM: transmitted good frames single collision interrupt mask
      参数:        ENET_MSC_INT_TGFMSCIM: transmitted good frames more single collision interrupt mask
      参数:        ENET_MSC_INT_TGFIM: transmitted good frames interrupt mask
      参数:        ENET_DMA_INT_TIE: transmit interrupt enable
      参数:        ENET_DMA_INT_TPSIE: transmit process stopped interrupt enable
      参数:        ENET_DMA_INT_TBUIE: transmit buffer unavailable interrupt enable
      参数:        ENET_DMA_INT_TJTIE: transmit jabber timeout interrupt enable
      参数:        ENET_DMA_INT_ROIE: receive overflow interrupt enable
      参数:        ENET_DMA_INT_TUIE: transmit underflow interrupt enable
      参数:        ENET_DMA_INT_RIE: receive interrupt enable
      参数:        ENET_DMA_INT_RBUIE: receive buffer unavailable interrupt enable
      参数:        ENET_DMA_INT_RPSIE: receive process stopped interrupt enable
      参数:        ENET_DMA_INT_RWTIE: receive watchdog timeout interrupt enable
      参数:        ENET_DMA_INT_ETIE: early transmit interrupt enable
      参数:        ENET_DMA_INT_FBEIE: fatal bus error interrupt enable
      参数:        ENET_DMA_INT_ERIE: early receive interrupt enable
      参数:        ENET_DMA_INT_AIE: abnormal interrupt summary enable
      参数:        ENET_DMA_INT_NIE: normal interrupt summary enable
    参数[输出]:  无
    返回值:      无
*/
void ENET_Interrupt_Disable(ENET_int_enum ENET_int) {
    if(DMA_INTEN_REG_OFFSET == ((uint32_t)ENET_int >> 6)) {
        /* ENET_DMA_INTEN register 中断 */
        ENET_REG_VAL(ENET_int) &= ~BIT(ENET_Bit_POS(ENET_int));
    } else {
        /* other INTMSK register 中断 */
        ENET_REG_VAL(ENET_int) |= BIT(ENET_Bit_POS(ENET_int));
    }
}

/*!
    简介:    get ENET MAC/MSC/DMA interrupt flag
    参数[输入]:  int_flag: ENET interrupt flag, refer to ENET_int_Flag_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_INT_Flag_WUM: WUM status flag
      参数:        ENET_MAC_INT_Flag_MSC: MSC status flag
      参数:        ENET_MAC_INT_Flag_MSCR: MSC receive status flag
      参数:        ENET_MAC_INT_Flag_MSCT: MSC transmit status flag
      参数:        ENET_MAC_INT_Flag_TMST: time stamp trigger status flag
      参数:        ENET_MSC_INT_Flag_RFCE: received frames CRC error flag
      参数:        ENET_MSC_INT_Flag_RFAE: received frames alignment error flag
      参数:        ENET_MSC_INT_Flag_RGUF: received good unicast frames flag
      参数:        ENET_MSC_INT_Flag_TGFSC: transmitted good frames single collision flag
      参数:        ENET_MSC_INT_Flag_TGFMSC: transmitted good frames more single collision flag
      参数:        ENET_MSC_INT_Flag_TGF: transmitted good frames flag
      参数:        ENET_DMA_INT_Flag_TS: transmit status flag
      参数:        ENET_DMA_INT_Flag_TPS: transmit process stopped status flag
      参数:        ENET_DMA_INT_Flag_TBU: transmit buffer unavailable status flag
      参数:        ENET_DMA_INT_Flag_TJT: transmit jabber timeout status flag
      参数:        ENET_DMA_INT_Flag_RO: receive overflow status flag
      参数:        ENET_DMA_INT_Flag_TU: transmit underflow status flag
      参数:        ENET_DMA_INT_Flag_RS: receive status flag
      参数:        ENET_DMA_INT_Flag_RBU: receive buffer unavailable status flag
      参数:        ENET_DMA_INT_Flag_RPS: receive process stopped status flag
      参数:        ENET_DMA_INT_Flag_RWT: receive watchdog timeout status flag
      参数:        ENET_DMA_INT_Flag_ET: early transmit status flag
      参数:        ENET_DMA_INT_Flag_FBE: fatal bus error status flag
      参数:        ENET_DMA_INT_Flag_ER: early receive status flag
      参数:        ENET_DMA_INT_Flag_AI: abnormal interrupt summary flag
      参数:        ENET_DMA_INT_Flag_NI: normal interrupt summary flag
      参数:        ENET_DMA_INT_Flag_MSC: MSC status flag
      参数:        ENET_DMA_INT_Flag_WUM: WUM status flag
      参数:        ENET_DMA_INT_Flag_TST: timestamp trigger status flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus ENET_Interrupt_Flag_Get(ENET_int_Flag_enum int_flag) {
    if(RESET != (ENET_REG_VAL(int_flag) & BIT(ENET_Bit_POS(int_flag)))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    简介:    clear ENET DMA interrupt flag
    参数[输入]:  int_Flag_clear: clear ENET interrupt flag, refer to ENET_int_Flag_Clear_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_INT_Flag_TS_CLR: transmit status flag
      参数:        ENET_DMA_INT_Flag_TPS_CLR: transmit process stopped status flag
      参数:        ENET_DMA_INT_Flag_TBU_CLR: transmit buffer unavailable status flag
      参数:        ENET_DMA_INT_Flag_TJT_CLR: transmit jabber timeout status flag
      参数:        ENET_DMA_INT_Flag_RO_CLR: receive overflow status flag
      参数:        ENET_DMA_INT_Flag_TU_CLR: transmit underflow status flag
      参数:        ENET_DMA_INT_Flag_RS_CLR: receive status flag
      参数:        ENET_DMA_INT_Flag_RBU_CLR: receive buffer unavailable status flag
      参数:        ENET_DMA_INT_Flag_RPS_CLR: receive process stopped status flag
      参数:        ENET_DMA_INT_Flag_RWT_CLR: receive watchdog timeout status flag
      参数:        ENET_DMA_INT_Flag_ET_CLR: early transmit status flag
      参数:        ENET_DMA_INT_Flag_FBE_CLR: fatal bus error status flag
      参数:        ENET_DMA_INT_Flag_ER_CLR: early receive status flag
      参数:        ENET_DMA_INT_Flag_AI_CLR: abnormal interrupt summary flag
      参数:        ENET_DMA_INT_Flag_NI_CLR: normal interrupt summary flag
    参数[输出]:  无
    返回值:      无
*/
void ENET_Interrupt_Flag_Clear(ENET_int_Flag_Clear_enum int_Flag_clear) {
    /* write 1 to the corresponding bit in ENET_DMA_STAT, to clear it */
    ENET_REG_VAL(int_Flag_clear) = BIT(ENET_Bit_POS(int_Flag_clear));
}

/*!
    简介:    ENET Tx function enable (include MAC and DMA module)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_TX_Enable(void) {
    ENET_MAC_CFG |= ENET_MAC_CFG_TEN;
    ENET_TXFIFO_Flush();
    ENET_DMA_CTL |= ENET_DMA_CTL_STE;
}

/*!
    简介:    ENET Tx function disable (include MAC and DMA module)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_TX_Disable(void) {
    ENET_DMA_CTL &= ~ENET_DMA_CTL_STE;
    ENET_TXFIFO_Flush();
    ENET_MAC_CFG &= ~ENET_MAC_CFG_TEN;
}

/*!
    简介:    ENET Rx function enable (include MAC and DMA module)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_RX_Enable(void) {
    ENET_MAC_CFG |= ENET_MAC_CFG_REN;
    ENET_DMA_CTL |= ENET_DMA_CTL_SRE;
}

/*!
    简介:    ENET Rx function disable (include MAC and DMA module)
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_RX_Disable(void) {
    ENET_DMA_CTL &= ~ENET_DMA_CTL_SRE;
    ENET_MAC_CFG &= ~ENET_MAC_CFG_REN;
}

/*!
    简介:    put registers value into the application buffer
    参数[输入]:  type: register type which will be get, refer to ENET_registers_type_enum,
                only one parameter can be selected which is shown as below
      参数:        ALL_MAC_REG: get the registers within the offset scope between ENET_MAC_CFG and ENET_MAC_FCTH
      参数:        ALL_MSC_REG: get the registers within the offset scope between ENET_MSC_CTL and ENET_MSC_RGUFCNT
      参数:        ALL_PTP_REG: get the registers within the offset scope between ENET_PTP_TSCTL and ENET_PTP_PPSCTL
      参数:        ALL_DMA_REG: get the registers within the offset scope between ENET_DMA_BCTL and ENET_DMA_CRBADDR
    参数[输入]:  num: the number of registers that the user want to get
    参数[输出]: preg: the application buffer pointer for storing the register value
    返回值:      无
*/
void ENET_registers_Get(ENET_registers_type_enum type, uint32_t *preg, uint32_t num) {
    uint32_t offset = 0U, max = 0U, limit = 0U;

    offset = (uint32_t)type;
    max = (uint32_t)type + num;
    limit = sizeof(ENET_reg_tab) / sizeof(uint16_t);

    /* prevent element in this array is out of range */
    if(max > limit) {
        max = limit;
    }

    for(; offset < max; offset++) {
        /* get value of the corresponding register */
        *preg = REG32((ENET) + ENET_reg_tab[offset]);
        preg++;
    }
}

/*!
    简介:    get the enet debug status from the debug register
    参数[输入]:  mac_debug: enet debug status
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_Receiver_NOT_IDLE: MAC receiver is not in idle state
      参数:        ENET_RX_ASYNCHRONOUS_FIFO_STATE: Rx asynchronous FIFO status
      参数:        ENET_RXFIFO_WRITING: RxFIFO is doing write operation
      参数:        ENET_RXFIFO_READ_STATUS: RxFIFO read operation status
      参数:        ENET_RXFIFO_STATE: RxFIFO state
      参数:        ENET_MAC_TRANSMITTER_NOT_IDLE: MAC transmitter is not in idle state
      参数:        ENET_MAC_TRANSMITTER_STATUS: status of MAC transmitter
      参数:        ENET_PAUSE_CONDITION_STATUS: pause condition status
      参数:        ENET_TXFIFO_READ_STATUS: TxFIFO read operation status
      参数:        ENET_TXFIFO_WRITING: TxFIFO is doing write operation
      参数:        ENET_TXFIFO_NOT_EMPTY: TxFIFO is not empty
      参数:        ENET_TXFIFO_FULL: TxFIFO is full
    参数[输出]:  无
    返回值:     value of the status users want to get
*/
uint32_t ENET_Debug_Status_Get(uint32_t mac_debug) {
    uint32_t temp_state = 0U;

    switch(mac_debug) {
    case ENET_RX_ASYNCHRONOUS_FIFO_STATE:
        temp_state = GET_MAC_DBG_RXAFS(ENET_MAC_DBG);
        break;

    case ENET_RXFIFO_READ_STATUS:
        temp_state = GET_MAC_DBG_RXFRS(ENET_MAC_DBG);
        break;

    case ENET_RXFIFO_STATE:
        temp_state = GET_MAC_DBG_RXFS(ENET_MAC_DBG);
        break;

    case ENET_MAC_TRANSMITTER_STATUS:
        temp_state = GET_MAC_DBG_SOMT(ENET_MAC_DBG);
        break;

    case ENET_TXFIFO_READ_STATUS:
        temp_state = GET_MAC_DBG_TXFRS(ENET_MAC_DBG);
        break;

    default:
        if(RESET != (ENET_MAC_DBG & mac_debug)) {
            temp_state = 0x1U;
        }

        break;
    }

    return temp_state;
}

/*!
    简介:    enable the MAC address filter
    参数[输入]:  mac_addr: select which MAC address will be enable, refer to ENET_macaddress_enum
      参数:        ENET_MAC_ADDRESS1: enable MAC address 1 filter
      参数:        ENET_MAC_ADDRESS2: enable MAC address 2 filter
      参数:        ENET_MAC_ADDRESS3: enable MAC address 3 filter
    参数[输出]:  无
    返回值:      无
*/
void ENET_Address_Filter_Enable(ENET_macaddress_enum mac_addr) {
    REG32(ENET_ADDRH_BASE + mac_addr) |= ENET_MAC_ADDR1H_AFE;
}

/*!
    简介:    disable the MAC address filter
    参数[输入]:  mac_addr: select which MAC address will be disable, refer to ENET_macaddress_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_ADDRESS1: disable MAC address 1 filter
      参数:        ENET_MAC_ADDRESS2: disable MAC address 2 filter
      参数:        ENET_MAC_ADDRESS3: disable MAC address 3 filter
    参数[输出]:  无
    返回值:      无
*/
void ENET_Address_Filter_Disable(ENET_macaddress_enum mac_addr) {
    REG32(ENET_ADDRH_BASE + mac_addr) &= ~ENET_MAC_ADDR1H_AFE;
}

/*!
    简介:    configure the MAC address filter
    参数[输入]:  mac_addr: select which MAC address will be configured, refer to ENET_macaddress_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC_ADDRESS1: configure MAC address 1 filter
      参数:        ENET_MAC_ADDRESS2: configure MAC address 2 filter
      参数:        ENET_MAC_ADDRESS3: configure MAC address 3 filter
    参数[输入]:  addr_mask: select which MAC address bytes will be mask
                one or more parameters can be selected which are shown as below
      参数:        ENET_Address_MASK_BYTE0: mask ENET_MAC_ADDR1L[7:0] bits
      参数:        ENET_Address_MASK_BYTE1: mask ENET_MAC_ADDR1L[15:8] bits
      参数:        ENET_Address_MASK_BYTE2: mask ENET_MAC_ADDR1L[23:16] bits
      参数:        ENET_Address_MASK_BYTE3: mask ENET_MAC_ADDR1L [31:24] bits
      参数:        ENET_Address_MASK_BYTE4: mask ENET_MAC_ADDR1H [7:0] bits
      参数:        ENET_Address_MASK_BYTE5: mask ENET_MAC_ADDR1H [15:8] bits
    参数[输入]:  filter_type: select which MAC address filter type will be selected
                only one parameter can be selected which is shown as below
      参数:        ENET_Address_Filter_SA: The MAC address is used to compared with the SA field of the received frame
      参数:        ENET_Address_Filter_DA: The MAC address is used to compared with the DA field of the received frame
    参数[输出]:  无
    返回值:      无
*/
void ENET_Address_Filter_Config(ENET_macaddress_enum mac_addr, uint32_t addr_mask, uint32_t filter_type) {
    uint32_t reg;

    /* get the address filter register value which is to be configured */
    reg = REG32(ENET_ADDRH_BASE + mac_addr);

    /* clear and configure the address filter register */
    reg &= ~(ENET_MAC_ADDR1H_MB | ENET_MAC_ADDR1H_SAF);
    reg |= (addr_mask | filter_type);
    REG32(ENET_ADDRH_BASE + mac_addr) = reg;
}

/*!
    简介:    PHY interface configuration (configure SMI clock and reset PHY chip)
    参数[输入]:  无
    参数[输出]:  无
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_PHY_Config(void) {
    uint32_t ahbclk;
    uint32_t reg;
    uint16_t phy_value;
    ErrStatus ENET_state = ERROR;

    /* clear the previous MDC clock */
    reg = ENET_MAC_PHY_CTL;
    reg &= ~ENET_MAC_PHY_CTL_CLR;

    /* get the HCLK frequency */
    ahbclk = RCU_Clock_Freq_Get(CK_AHB);

    /* configure MDC clock 根据 HCLK frequency range */
    if(ENET_RANGE(ahbclk, 20000000U, 35000000U)) {
        reg |= ENET_MDC_HCLK_DIV16;
    } else if(ENET_RANGE(ahbclk, 35000000U, 60000000U)) {
        reg |= ENET_MDC_HCLK_DIV26;
    } else if(ENET_RANGE(ahbclk, 60000000U, 100000000U)) {
        reg |= ENET_MDC_HCLK_DIV42;
    } else if(ENET_RANGE(ahbclk, 100000000U, 150000000U)) {
        reg |= ENET_MDC_HCLK_DIV62;
    } else if((ENET_RANGE(ahbclk, 150000000U, 240000000U)) || (240000000U == ahbclk)) {
        reg |= ENET_MDC_HCLK_DIV102;
    } else {
        return ENET_state;
    }

    ENET_MAC_PHY_CTL = reg;

    /* reset PHY */
    phy_value = PHY_RESET;

    if(ERROR == (ENET_PHY_Write_Read(ENET_PHY_WRITE, PHY_ADDRESS, PHY_REG_BCR, &phy_value))) {
        return ENET_state;
    }

    /* PHY reset need some time */
    _ENET_Delay_(ENET_Delay_TO);

    /* check whether PHY reset is complete */
    if(ERROR == (ENET_PHY_Write_Read(ENET_PHY_READ, PHY_ADDRESS, PHY_REG_BCR, &phy_value))) {
        return ENET_state;
    }

    /* PHY reset complete */
    if(RESET == (phy_value & PHY_RESET)) {
        ENET_state = SUCCESS;
    }

    return ENET_state;
}

/*!
    简介:    write to / read from a PHY register
    参数[输入]:  direction: only one parameter can be selected which is shown as below, refer to ENET_phydirection_enum
      参数:        ENET_PHY_WRITE: write data to phy register
      参数:        ENET_PHY_READ:  read data from phy register
    参数[输入]:  phy_address: 0x0000 - 0x001F
    参数[输入]:  phy_reg: 0x0000 - 0x001F
    参数[输入]:  pvalue: the value will be written to the PHY register in ENET_PHY_WRITE direction
    参数[输出]: pvalue: the value will be read from the PHY register in ENET_PHY_READ direction
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_PHY_Write_Read(ENET_phydirection_enum direction, uint16_t phy_address, uint16_t phy_reg, uint16_t *pvalue) {
    uint32_t reg, phy_flag;
    uint32_t timeout = 0U;
    ErrStatus ENET_state = ERROR;

    /* configure ENET_MAC_PHY_CTL with write/read operation */
    reg = ENET_MAC_PHY_CTL;
    reg &= ~(ENET_MAC_PHY_CTL_PB | ENET_MAC_PHY_CTL_PW | ENET_MAC_PHY_CTL_PR | ENET_MAC_PHY_CTL_PA);
    reg |= (direction | MAC_PHY_CTL_PR(phy_reg) | MAC_PHY_CTL_PA(phy_address) | ENET_MAC_PHY_CTL_PB);

    /* if do the write operation, write value to the register */
    if(ENET_PHY_WRITE == direction) {
        ENET_MAC_PHY_DATA = *pvalue;
    }

    /* do PHY write/read operation, and wait the operation complete  */
    ENET_MAC_PHY_CTL = reg;

    do {
        phy_flag = (ENET_MAC_PHY_CTL & ENET_MAC_PHY_CTL_PB);
        timeout++;
    } while((RESET != phy_flag) && (ENET_Delay_TO != timeout));

    /* write/read operation complete */
    if(RESET == (ENET_MAC_PHY_CTL & ENET_MAC_PHY_CTL_PB)) {
        ENET_state = SUCCESS;
    }

    /* if do the read operation, get value from the register */
    if(ENET_PHY_READ == direction) {
        *pvalue = (uint16_t)ENET_MAC_PHY_DATA;
    }

    return ENET_state;
}

/*!
    简介:    enable the loopback function of PHY chip
    参数[输入]:  无
    参数[输出]:  无
    返回值:     ErrStatus: ERROR or SUCCESS
*/
ErrStatus ENET_phyloopback_Enable(void) {
    uint16_t temp_phy = 0U;
    ErrStatus phy_state = ERROR;

    /* get the PHY configuration to update it */
    ENET_PHY_Write_Read(ENET_PHY_READ, PHY_ADDRESS, PHY_REG_BCR, &temp_phy);

    /* enable the PHY loopback mode */
    temp_phy |= PHY_LOOPBACK;

    /* update the PHY control register with the new configuration */
    phy_state = ENET_PHY_Write_Read(ENET_PHY_WRITE, PHY_ADDRESS, PHY_REG_BCR, &temp_phy);

    return phy_state;
}

/*!
    简介:    disable the loopback function of PHY chip
    参数[输入]:  无
    参数[输出]:  无
    返回值:     ErrStatus: ERROR or SUCCESS
*/
ErrStatus ENET_phyloopback_Disable(void) {
    uint16_t temp_phy = 0U;
    ErrStatus phy_state = ERROR;

    /* get the PHY configuration to update it */
    ENET_PHY_Write_Read(ENET_PHY_READ, PHY_ADDRESS, PHY_REG_BCR, &temp_phy);

    /* disable the PHY loopback mode */
    temp_phy &= (uint16_t)~PHY_LOOPBACK;

    /* update the PHY control register with the new configuration */
    phy_state = ENET_PHY_Write_Read(ENET_PHY_WRITE, PHY_ADDRESS, PHY_REG_BCR, &temp_phy);

    return phy_state;
}

/*!
    简介:    enable ENET forward feature
    参数[输入]:  feature: the feature of ENET forward mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_Auto_PADCRC_DROP: the function of the MAC strips the Pad/FCS field on received frames
      参数:        ENET_TYPEFRAME_CRC_DROP: the function that FCS field(last 4 bytes) of frame will be dropped before forwarding
      参数:        ENET_FORWARD_ERRFRAMES: the function that all frame received with error except runt error are forwarded to memory
      参数:        ENET_FORWARD_UNDERSZ_GOODFRAMES: the function that forwarding undersized good frames
    参数[输出]:  无
    返回值:      无
*/
void ENET_forward_Feature_Enable(uint32_t feature) {
    uint32_t mask;

    mask = (feature & (~(ENET_FORWARD_ERRFRAMES | ENET_FORWARD_UNDERSZ_GOODFRAMES)));
    ENET_MAC_CFG |= mask;

    mask = (feature & (~(ENET_Auto_PADCRC_DROP | ENET_TYPEFRAME_CRC_DROP)));
    ENET_DMA_CTL |= (mask >> 2);
}

/*!
    简介:    disable ENET forward feature
    参数[输入]:  feature: the feature of ENET forward mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_Auto_PADCRC_DROP: the function of the MAC strips the Pad/FCS field on received frames
      参数:        ENET_TYPEFRAME_CRC_DROP: the function that FCS field(last 4 bytes) of frame will be dropped before forwarding
      参数:        ENET_FORWARD_ERRFRAMES: the function that all frame received with error except runt error are forwarded to memory
      参数:        ENET_FORWARD_UNDERSZ_GOODFRAMES: the function that forwarding undersized good frames
    参数[输出]:  无
    返回值:      无
*/
void ENET_forward_Feature_Disable(uint32_t feature) {
    uint32_t mask;

    mask = (feature & (~(ENET_FORWARD_ERRFRAMES | ENET_FORWARD_UNDERSZ_GOODFRAMES)));
    ENET_MAC_CFG &= ~mask;

    mask = (feature & (~(ENET_Auto_PADCRC_DROP | ENET_TYPEFRAME_CRC_DROP)));
    ENET_DMA_CTL &= ~(mask >> 2);
}

/*!
    简介:      enable ENET fliter feature
    参数[输入]:  feature: the feature of ENET fliter mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_SRC_FILTER: filter source address function
      参数:        ENET_SRC_Filter_INVERSE: inverse source address filtering result function
      参数:        ENET_DEST_Filter_INVERSE: inverse DA filtering result function
      参数:        ENET_MULTICAST_Filter_PASS: pass all multicast frames function
      参数:        ENET_MULTICAST_Filter_HASH_MODE: HASH multicast filter function
      参数:        ENET_UNICAST_Filter_HASH_MODE: HASH unicast filter function
      参数:        ENET_Filter_Mode_EITHER: HASH or perfect filter function
    参数[输出]:  无
    返回值:      无
*/
void ENET_fliter_Feature_Enable(uint32_t feature) {
    ENET_MAC_FRMF |= feature;
}

/*!
    简介:    disable ENET fliter feature
    参数[输入]:  feature: the feature of ENET fliter mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_SRC_FILTER: filter source address function
      参数:        ENET_SRC_Filter_INVERSE: inverse source address filtering result function
      参数:        ENET_DEST_Filter_INVERSE: inverse DA filtering result function
      参数:        ENET_MULTICAST_Filter_PASS: pass all multicast frames function
      参数:        ENET_MULTICAST_Filter_HASH_MODE: HASH multicast filter function
      参数:        ENET_UNICAST_Filter_HASH_MODE: HASH unicast filter function
      参数:        ENET_Filter_Mode_EITHER: HASH or perfect filter function
    参数[输出]:  无
    返回值:      无
*/
void ENET_fliter_Feature_Disable(uint32_t feature) {
    ENET_MAC_FRMF &= ~feature;
}

/*!
    简介:    generate the pause frame, ENET will send pause frame after enable transmit flow control
                this function only use in full-dulex mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:     ErrStatus: ERROR or SUCCESS
*/
ErrStatus ENET_pauseframe_Generate(void) {
    ErrStatus ENET_state = ERROR;
    uint32_t temp = 0U;

    /* in full-duplex mode, must make sure this bit is 0 before writing register */
    temp = ENET_MAC_FCTL & ENET_MAC_FCTL_FLCBBKPA;

    if(RESET == temp) {
        ENET_MAC_FCTL |= ENET_MAC_FCTL_FLCBBKPA;
        ENET_state = SUCCESS;
    }

    return ENET_state;
}

/*!
    简介:    configure the pause frame detect type
    参数[输入]:  detect: pause frame detect type
                only one parameter can be selected which is shown as below
      参数:        ENET_MAC0_AND_UNIQUE_Address_PAUSEDETECT: besides the unique multicast address, MAC can also
                                                            use the MAC0 address to detecting pause frame
      参数:        ENET_UNIQUE_PAUSEDETECT: only the unique multicast address for pause frame which is specified
                                           in IEEE802.3 can be detected
    参数[输出]:  无
    返回值:      无
*/
void ENET_pauseframe_detect_Config(uint32_t detect) {
    ENET_MAC_FCTL &= ~ENET_MAC_FCTL_UPFDT;
    ENET_MAC_FCTL |= detect;
}

/*!
    简介:    configure the pause frame parameters
    参数[输入]:  pausetime: pause time in transmit pause control frame
    参数[输入]:  pause_threshold: the threshold of the pause timer for retransmitting frames automatically
                this value must make sure to be less than configured pause time
                only one parameter can be selected which is shown as below
      参数:        ENET_PAUSETIME_MINUS4: pause time minus 4 slot times
      参数:        ENET_PAUSETIME_MINUS28: pause time minus 28 slot times
      参数:        ENET_PAUSETIME_MINUS144: pause time minus 144 slot times
      参数:        ENET_PAUSETIME_MINUS256: pause time minus 256 slot times
    参数[输出]:  无
    返回值:      无
*/
void ENET_pauseframe_Config(uint32_t pausetime, uint32_t pause_threshold) {
    ENET_MAC_FCTL &= ~(ENET_MAC_FCTL_PTM | ENET_MAC_FCTL_PLTS);
    ENET_MAC_FCTL |= (MAC_FCTL_PTM(pausetime) | pause_threshold);
}

/*!
    简介:    configure the threshold of the flow control(deactive and active threshold)
    参数[输入]:  deactive: the threshold of the deactive flow control
                this value should always be less than active flow control value
                only one parameter can be selected which is shown as below
      参数:        ENET_DEACTIVE_Threshold_256BYTES: threshold level is 256 bytes
      参数:        ENET_DEACTIVE_Threshold_512BYTES: threshold level is 512 bytes
      参数:        ENET_DEACTIVE_Threshold_768BYTES: threshold level is 768 bytes
      参数:        ENET_DEACTIVE_Threshold_1024BYTES: threshold level is 1024 bytes
      参数:        ENET_DEACTIVE_Threshold_1280BYTES: threshold level is 1280 bytes
      参数:        ENET_DEACTIVE_Threshold_1536BYTES: threshold level is 1536 bytes
      参数:        ENET_DEACTIVE_Threshold_1792BYTES: threshold level is 1792 bytes
    参数[输入]:  active: the threshold of the active flow control
                only one parameter can be selected which is shown as below
      参数:        ENET_ACTIVE_Threshold_256BYTES: threshold level is 256 bytes
      参数:        ENET_ACTIVE_Threshold_512BYTES: threshold level is 512 bytes
      参数:        ENET_ACTIVE_Threshold_768BYTES: threshold level is 768 bytes
      参数:        ENET_ACTIVE_Threshold_1024BYTES: threshold level is 1024 bytes
      参数:        ENET_ACTIVE_Threshold_1280BYTES: threshold level is 1280 bytes
      参数:        ENET_ACTIVE_Threshold_1536BYTES: threshold level is 1536 bytes
      参数:        ENET_ACTIVE_Threshold_1792BYTES: threshold level is 1792 bytes
    参数[输出]:  无
    返回值:      无
*/
void ENET_flowcontrol_Threshold_Config(uint32_t deactive, uint32_t active) {
    ENET_MAC_FCTH = ((deactive | active) >> 8);
}

/*!
    简介:    enable ENET flow control feature
    参数[输入]:  feature: the feature of ENET flow control mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_ZERO_QUANTA_PAUSE: the automatic zero-quanta generation function
      参数:        ENET_TX_FLOWCONTROL: the flow control operation in the MAC
      参数:        ENET_RX_FLOWCONTROL: decoding function for the received pause frame and process it
      参数:        ENET_BACK_PRESSURE: back pressure operation in the MAC(only use in half-dulex mode)
    参数[输出]:  无
    返回值:      无
*/
void ENET_flowcontrol_Feature_Enable(uint32_t feature) {
    if(RESET != (feature & ENET_ZERO_QUANTA_PAUSE)) {
        ENET_MAC_FCTL &= ~ENET_ZERO_QUANTA_PAUSE;
    }

    feature &= ~ENET_ZERO_QUANTA_PAUSE;
    ENET_MAC_FCTL |= feature;
}

/*!
    简介:    disable ENET flow control feature
    参数[输入]:  feature: the feature of ENET flow control mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_ZERO_QUANTA_PAUSE: the automatic zero-quanta generation function
      参数:        ENET_TX_FLOWCONTROL: the flow control operation in the MAC
      参数:        ENET_RX_FLOWCONTROL: decoding function for the received pause frame and process it
      参数:        ENET_BACK_PRESSURE: back pressure operation in the MAC(only use in half-dulex mode)
    参数[输出]:  无
    返回值:      无
*/
void ENET_flowcontrol_Feature_Disable(uint32_t feature) {
    if(RESET != (feature & ENET_ZERO_QUANTA_PAUSE)) {
        ENET_MAC_FCTL |= ENET_ZERO_QUANTA_PAUSE;
    }

    feature &= ~ENET_ZERO_QUANTA_PAUSE;
    ENET_MAC_FCTL &= ~feature;
}

/*!
    简介:    get the dma transmit/receive process state
    参数[输入]:  direction: choose the direction of dma process which users want to check, refer to ENET_dmadirection_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_TX: dma transmit process
      参数:        ENET_DMA_RX: dma receive process
    参数[输出]:  无
    返回值:     state of dma process, the value range shows below:
                  ENET_RX_State_STOPPED, ENET_RX_State_FETCHING, ENET_RX_State_WaitING,
                  ENET_RX_State_SUSPENDED, ENET_RX_State_CLOSING, ENET_RX_State_QUEUING,
                  ENET_TX_State_STOPPED, ENET_TX_State_FETCHING, ENET_TX_State_WaitING,
                  ENET_TX_State_READING, ENET_TX_State_SUSPENDED, ENET_TX_State_CLOSING
*/
uint32_t ENET_Dmaprocess_State_Get(ENET_dmadirection_enum direction) {
    uint32_t reval;
    reval = (uint32_t)(ENET_DMA_STAT & (uint32_t)direction);
    return reval;
}

/*!
    简介:    poll the DMA transmission/reception enable by writing any value to the
                ENET_DMA_TPEN/ENET_DMA_RPEN register, this will make the DMA to resume transmission/reception
    参数[输入]:  direction: choose the direction of DMA process which users want to resume, refer to ENET_dmadirection_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_TX: DMA transmit process
      参数:        ENET_DMA_RX: DMA receive process
    参数[输出]:  无
    返回值:      无
*/
void ENET_Dmaprocess_Resume(ENET_dmadirection_enum direction) {
    if(ENET_DMA_TX == direction) {
        ENET_DMA_TPEN = 0U;
    } else {
        ENET_DMA_RPEN = 0U;
    }
}

/*!
    简介:    check and recover the Rx process
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_RXprocess_Check_Recovery(void) {
    uint32_t status;

    /* get DAV information of current RxDMA descriptor */
    status = DMA_Current_rxdesc->status;
    status &= ENET_RDES0_DAV;

    /* if current descriptor is owned by DMA, but the descriptor address mismatches with
    receive descriptor address pointer updated by RxDMA controller */
    if((ENET_DMA_CRDADDR != ((uint32_t)DMA_Current_rxdesc)) &&
            (ENET_RDES0_DAV == status)) {
        DMA_Current_rxdesc = (ENET_Descriptors_Struct *)ENET_DMA_CRDADDR;
    }
}

/*!
    简介:    flush the ENET transmit FIFO, and wait until the flush operation completes
    参数[输入]:  无
    参数[输出]:  无
    返回值:     ErrStatus: ERROR or SUCCESS
*/
ErrStatus ENET_TXFIFO_Flush(void) {
    uint32_t flush_state;
    uint32_t timeout = 0U;
    ErrStatus ENET_state = ERROR;

    /* set the FTF bit for flushing transmit FIFO */
    ENET_DMA_CTL |= ENET_DMA_CTL_FTF;

    /* wait until the flush operation completes */
    do {
        flush_state = ENET_DMA_CTL & ENET_DMA_CTL_FTF;
        timeout++;
    } while((RESET != flush_state) && (timeout < ENET_Delay_TO));

    /* return ERROR due to timeout */
    if(RESET == flush_state) {
        ENET_state = SUCCESS;
    }

    return  ENET_state;
}

/*!
    简介:    get the transmit/receive address of current descriptor, or current buffer, or descriptor table
    参数[输入]:  addr_get: choose the address which users want to get, refer to ENET_Desc_reg_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_RX_Desc_TABLE: the start address of the receive descriptor table
      参数:        ENET_RX_Current_DESC: the start descriptor address of the current receive descriptor read by
                                        the RxDMA controller
      参数:        ENET_RX_Current_BUFFER: the current receive buffer address being read by the RxDMA controller
      参数:        ENET_TX_Desc_TABLE: the start address of the transmit descriptor table
      参数:        ENET_TX_Current_DESC: the start descriptor address of the current transmit descriptor read by
                                        the TxDMA controller
      参数:        ENET_TX_Current_BUFFER: the current transmit buffer address being read by the TxDMA controller
    参数[输出]:  无
    返回值:     address value
*/
uint32_t ENET_Current_Desc_Address_Get(ENET_Desc_reg_enum addr_get) {
    uint32_t reval = 0U;

    reval = REG32((ENET) + (uint32_t)addr_get);
    return reval;
}

/*!
    简介:    get the Tx or Rx descriptor information
    参数[输入]:  desc: the descriptor pointer which users want to get information
    参数[输入]:  info_get: the descriptor information type which is selected, refer to ENET_descstate_enum
                only one parameter can be selected which is shown as below
      参数:        RXDESC_Buffer_1_SIZE: receive buffer 1 size
      参数:        RXDESC_Buffer_2_SIZE: receive buffer 2 size
      参数:        RXDESC_Frame_LENGTH: the byte length of the received frame that was transferred to the buffer
      参数:        TXDESC_COLLISION_COUNT: the number of collisions occurred before the frame was transmitted
      参数:        RXDESC_Buffer_1_ADDR: the buffer1 address of the Rx frame
      参数:        TXDESC_Buffer_1_ADDR: the buffer1 address of the Tx frame
    参数[输出]:  无
    返回值:     descriptor information, if value is 0xFFFFFFFFU, means the false input parameter
*/
uint32_t ENET_Desc_Information_Get(ENET_Descriptors_Struct *desc, ENET_descstate_enum info_get) {
    uint32_t reval = 0xFFFFFFFFU;

    switch(info_get) {
    case RXDESC_Buffer_1_SIZE:
        reval = GET_RDES1_RB1S(desc->control_Buffer_size);
        break;

    case RXDESC_Buffer_2_SIZE:
        reval = GET_RDES1_RB2S(desc->control_Buffer_size);
        break;

    case RXDESC_Frame_LENGTH:
        reval = GET_RDES0_FRML(desc->status);

        if(reval > 4U) {
            reval = reval - 4U;

            /* if is a type frame, and CRC is not included in forwarding frame */
            if((RESET != (ENET_MAC_CFG & ENET_MAC_CFG_TFCD)) && (RESET != (desc->status & ENET_RDES0_FRMT))) {
                reval = reval + 4U;
            }
        } else {
            reval = 0U;
        }

        break;

    case RXDESC_Buffer_1_ADDR:
        reval = desc->buffer1_addr;
        break;

    case TXDESC_Buffer_1_ADDR:
        reval = desc->buffer1_addr;
        break;

    case TXDESC_COLLISION_COUNT:
        reval = GET_TDES0_COCNT(desc->status);
        break;

    default:
        break;
    }

    return reval;
}

/*!
    简介:    get the number of missed frames during receiving
    参数[输入]:  无
    参数[输出]: rxfifo_drop: pointer to the number of frames dropped by RxFIFO
    参数[输出]: rxDMA_drop: pointer to the number of frames missed by the RxDMA controller
    返回值:      无
*/
void ENET_Missed_Frame_Counter_Get(uint32_t *rxfifo_drop, uint32_t *rxDMA_drop) {
    uint32_t temp_counter = 0U;

    temp_counter = ENET_DMA_MFBOCNT;
    *rxfifo_drop = GET_DMA_MFBOCNT_MSFA(temp_counter);
    *rxDMA_drop = GET_DMA_MFBOCNT_MSFC(temp_counter);
}

/*!
    简介:    get the bit flag of ENET DMA descriptor
    参数[输入]:  desc: the descriptor pointer which users want to get flag
    参数[输入]:  desc_flag: the bit flag of ENET DMA descriptor
                only one parameter can be selected which is shown as below
      参数:        ENET_TDES0_DB: deferred
      参数:        ENET_TDES0_UFE: underflow error
      参数:        ENET_TDES0_EXD: excessive deferral
      参数:        ENET_TDES0_VFRM: VLAN frame
      参数:        ENET_TDES0_ECO: excessive collision
      参数:        ENET_TDES0_LCO: late collision
      参数:        ENET_TDES0_NCA: no carrier
      参数:        ENET_TDES0_LCA: loss of carrier
      参数:        ENET_TDES0_IPPE: IP payload error
      参数:        ENET_TDES0_FRMF: frame flushed
      参数:        ENET_TDES0_JT: jabber timeout
      参数:        ENET_TDES0_ES: error summary
      参数:        ENET_TDES0_IPHE: IP header error
      参数:        ENET_TDES0_TTMSS: transmit timestamp status
      参数:        ENET_TDES0_TCHM: the second address chained mode
      参数:        ENET_TDES0_TERM: transmit end of ring mode
      参数:        ENET_TDES0_TTSEN: transmit timestamp function enable
      参数:        ENET_TDES0_DPAD: disable adding pad
      参数:        ENET_TDES0_DCRC: disable CRC
      参数:        ENET_TDES0_FSG: first segment
      参数:        ENET_TDES0_LSG: last segment
      参数:        ENET_TDES0_INTC: interrupt on completion
      参数:        ENET_TDES0_DAV: DAV bit

      参数:        ENET_RDES0_PCERR: payload checksum error
      参数:        ENET_RDES0_EXSV: extended status valid
      参数:        ENET_RDES0_CERR: CRC error
      参数:        ENET_RDES0_DBERR: dribble bit error
      参数:        ENET_RDES0_RERR: receive error
      参数:        ENET_RDES0_RWDT: receive watchdog timeout
      参数:        ENET_RDES0_FRMT: frame type
      参数:        ENET_RDES0_LCO: late collision
      参数:        ENET_RDES0_IPHERR: IP frame header error
      参数:        ENET_RDES0_TSV: timestamp valid
      参数:        ENET_RDES0_LDES: last descriptor
      参数:        ENET_RDES0_FDES: first descriptor
      参数:        ENET_RDES0_VTAG: VLAN tag
      参数:        ENET_RDES0_OERR: overflow error
      参数:        ENET_RDES0_LERR: length error
      参数:        ENET_RDES0_SAFF: SA filter fail
      参数:        ENET_RDES0_DERR: descriptor error
      参数:        ENET_RDES0_ERRS: error summary
      参数:        ENET_RDES0_DAFF: destination address filter fail
      参数:        ENET_RDES0_DAV: descriptor available
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus ENET_Desc_Flag_Get(ENET_Descriptors_Struct *desc, uint32_t desc_flag) {
    FlagStatus ENET_flag = RESET;

    if((uint32_t)RESET != (desc->status & desc_flag)) {
        ENET_flag = SET;
    }

    return ENET_flag;
}

/*!
    简介:    set the bit flag of ENET DMA descriptor
    参数[输入]:  desc: the descriptor pointer which users want to set flag
    参数[输入]:  desc_flag: the bit flag of ENET DMA descriptor
                only one parameter can be selected which is shown as below
      参数:        ENET_TDES0_VFRM: VLAN frame
      参数:        ENET_TDES0_FRMF: frame flushed
      参数:        ENET_TDES0_TCHM: the second address chained mode
      参数:        ENET_TDES0_TERM: transmit end of ring mode
      参数:        ENET_TDES0_TTSEN: transmit timestamp function enable
      参数:        ENET_TDES0_DPAD: disable adding pad
      参数:        ENET_TDES0_DCRC: disable CRC
      参数:        ENET_TDES0_FSG: first segment
      参数:        ENET_TDES0_LSG: last segment
      参数:        ENET_TDES0_INTC: interrupt on completion
      参数:        ENET_TDES0_DAV: DAV bit
      参数:        ENET_RDES0_DAV: descriptor available
    参数[输出]:  无
    返回值:      无
*/
void ENET_Desc_Flag_Set(ENET_Descriptors_Struct *desc, uint32_t desc_flag) {
    desc->status |= desc_flag;
}

/*!
    简介:    clear the bit flag of ENET DMA descriptor
    参数[输入]:  desc: the descriptor pointer which users want to clear flag
    参数[输入]:  desc_flag: the bit flag of ENET DMA descriptor
                only one parameter can be selected which is shown as below
      参数:        ENET_TDES0_VFRM: VLAN frame
      参数:        ENET_TDES0_FRMF: frame flushed
      参数:        ENET_TDES0_TCHM: the second address chained mode
      参数:        ENET_TDES0_TERM: transmit end of ring mode
      参数:        ENET_TDES0_TTSEN: transmit timestamp function enable
      参数:        ENET_TDES0_DPAD: disable adding pad
      参数:        ENET_TDES0_DCRC: disable CRC
      参数:        ENET_TDES0_FSG: first segment
      参数:        ENET_TDES0_LSG: last segment
      参数:        ENET_TDES0_INTC: interrupt on completion
      参数:        ENET_TDES0_DAV: DAV bit
      参数:        ENET_RDES0_DAV: descriptor available
    参数[输出]:  无
    返回值:      无
*/
void ENET_Desc_Flag_Clear(ENET_Descriptors_Struct *desc, uint32_t desc_flag) {
    desc->status &= ~desc_flag;
}

/*!
    简介:    when receiving completed, set RS bit in ENET_DMA_STAT register will immediately set
    参数[输入]:  desc: the descriptor pointer which users want to configure
    参数[输出]:  无
    返回值:      无
*/
void ENET_RX_Desc_Immediate_Receive_Complete_Interrupt(ENET_Descriptors_Struct *desc) {
    desc->control_Buffer_size &= ~ENET_RDES1_DINTC;
}

/*!
    简介:    when receiving completed, set RS bit in ENET_DMA_STAT register will is set after a configurable delay time
    参数[输入]:  desc: the descriptor pointer which users want to configure
    参数[输入]:  delay_time: delay a time of 256*delay_time HCLK(0x00000000 - 0x000000FF)
    参数[输出]:  无
    返回值:      无
*/
void ENET_RX_Desc_Delay_Receive_Complete_Interrupt(ENET_Descriptors_Struct *desc, uint32_t delay_time) {
    desc->control_Buffer_size |= ENET_RDES1_DINTC;
    ENET_DMA_RSWDC = DMA_RSWDC_WDCFRS(delay_time);
}

/*!
    简介:    drop current receive frame
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_RXframe_Drop(void) {
    /* enable reception, descriptor is owned by DMA */
    DMA_Current_rxdesc->status = ENET_RDES0_DAV;

    /* chained mode */
    if((uint32_t)RESET != (DMA_Current_rxdesc->control_Buffer_size & ENET_RDES1_RCHM)) {
        if(NULL != DMA_Current_PTP_rxdesc) {
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_rxdesc->buffer2_next_Desc_addr);

            /* if it is the last ptp descriptor */
            if(0U != DMA_Current_PTP_rxdesc->status) {
                /* pointer back to the first ptp descriptor address in the desc_ptptab list address */
                DMA_Current_PTP_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_rxdesc->status);
            } else {
                /* ponter to the next ptp descriptor */
                DMA_Current_PTP_rxdesc++;
            }
        } else {
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_rxdesc->buffer2_next_Desc_addr);
        }

    } else {
        /* ring mode */
        if((uint32_t)RESET != (DMA_Current_rxdesc->control_Buffer_size & ENET_RDES1_RERM)) {
            /* if is the last descriptor in table, the next descriptor is the table header */
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(ENET_DMA_RDTADDR);

            if(NULL != DMA_Current_PTP_rxdesc) {
                DMA_Current_PTP_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_rxdesc->status);
            }
        } else {
            /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(uint32_t)((uint32_t)DMA_Current_rxdesc + ETH_DMARXDESC_SIZE + GET_DMA_BCTL_DPSL(ENET_DMA_BCTL));

            if(NULL != DMA_Current_PTP_rxdesc) {
                DMA_Current_PTP_rxdesc++;
            }
        }
    }
}

/*!
    简介:    enable DMA feature
    参数[输入]:  feature: the feature of DMA mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_NO_FLUSH_RXFRAME: RxDMA does not flushes frames function
      参数:        ENET_SECONDFRAME_OPT: TxDMA controller operate on second frame function
    参数[输出]:  无
    返回值:      无
*/
void ENET_DMA_Feature_Enable(uint32_t feature) {
    ENET_DMA_CTL |= feature;
}

/*!
    简介:    disable DMA feature
    参数[输入]:  feature: the feature of DMA mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_NO_FLUSH_RXFRAME: RxDMA does not flushes frames function
      参数:        ENET_SECONDFRAME_OPT: TxDMA controller operate on second frame function
    参数[输出]:  无
    返回值:      无
*/
void ENET_DMA_Feature_Disable(uint32_t feature) {
    ENET_DMA_CTL &= ~feature;
}

#ifdef SELECT_Descriptors_Enhanced_MODE
/*!
    简介:    get the bit of extended status flag in ENET DMA descriptor
    参数[输入]:  desc: the descriptor pointer which users want to get the extended status flag
    参数[输入]:  desc_status: the extended status want to get
                only one parameter can be selected which is shown as below
      参数:        ENET_RDES4_IPPLDT: IP frame payload type
      参数:        ENET_RDES4_IPHERR: IP frame header error
      参数:        ENET_RDES4_IPPLDERR: IP frame payload error
      参数:        ENET_RDES4_IPCKSB: IP frame checksum bypassed
      参数:        ENET_RDES4_IPF4: IP frame in version 4
      参数:        ENET_RDES4_IPF6: IP frame in version 6
      参数:        ENET_RDES4_PTPMT: PTP message type
      参数:        ENET_RDES4_PTPOEF: PTP on ethernet frame
      参数:        ENET_RDES4_PTPVF: PTP version format
    参数[输出]:  无
    返回值:     value of extended status
*/
uint32_t ENET_RX_Desc_Enhanced_Status_Get(ENET_Descriptors_Struct *desc, uint32_t desc_status) {
    uint32_t reval = 0xFFFFFFFFU;

    switch(desc_status) {
    case ENET_RDES4_IPPLDT:
        reval = GET_RDES4_IPPLDT(desc->extended_status);
        break;

    case ENET_RDES4_PTPMT:
        reval = GET_RDES4_PTPMT(desc->extended_status);
        break;

    default:
        if((uint32_t)RESET != (desc->extended_status & desc_status)) {
            reval = 1U;
        } else {
            reval = 0U;
        }
    }

    return reval;
}

/*!
    简介:    configure descriptor to work in enhanced mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_Desc_Select_Enhanced_Mode(void) {
    ENET_DMA_BCTL |= ENET_DMA_BCTL_DFM;
}

/*!
    简介:    initialize the DMA Tx/Rx descriptors's parameters in enhanced chain mode with ptp function
    参数[输入]:  direction: the descriptors which users want to init, refer to ENET_dmadirection_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_TX: DMA Tx descriptors
      参数:        ENET_DMA_RX: DMA Rx descriptors
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Enhanced_Descriptors_Chain_Init(ENET_dmadirection_enum direction) {
    uint32_t num = 0U, count = 0U, maxsize = 0U;
    uint32_t desc_status = 0U, desc_bufsize = 0U;
    ENET_Descriptors_Struct *desc, *desc_tab;
    uint8_t *buf;

    /* if want to initialize DMA Tx descriptors */
    if(ENET_DMA_TX == direction) {
        /* save a copy of the DMA Tx descriptors */
        desc_tab = txdesc_tab;
        buf = &tx_buff[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        /* select chain mode, and enable transmit timestamp function */
        desc_status = ENET_TDES0_TCHM | ENET_TDES0_TTSEN;

        /* configure DMA Tx descriptor table address register */
        ENET_DMA_TDTADDR = (uint32_t)desc_tab;
        DMA_Current_txdesc = desc_tab;
    } else {
        /* if want to initialize DMA Rx descriptors */
        /* save a copy of the DMA Rx descriptors */
        desc_tab = rxdesc_tab;
        buf = &rx_buff[0][0];
        count = ENET_RXBUF_NUM;
        maxsize = ENET_RXBUF_SIZE;

        /* enable receiving */
        desc_status = ENET_RDES0_DAV;
        /* select receive chained mode and set buffer1 size */
        desc_bufsize = ENET_RDES1_RCHM | (uint32_t)ENET_RXBUF_SIZE;

        /* configure DMA Rx descriptor table address register */
        ENET_DMA_RDTADDR = (uint32_t)desc_tab;
        DMA_Current_rxdesc = desc_tab;
    }

    /* configuration each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->status = desc_status;
        desc->control_Buffer_size = desc_bufsize;
        desc->buffer1_addr = (uint32_t)(&buf[num * maxsize]);

        /* if is not the last descriptor */
        if(num < (count - 1U)) {
            /* configure the next descriptor address */
            desc->buffer2_next_Desc_addr = (uint32_t)(desc_tab + num + 1U);
        } else {
            /* when it is the last descriptor, the next descriptor address
            equals to first descriptor address in descriptor table */
            desc->buffer2_next_Desc_addr = (uint32_t)desc_tab;
        }
    }
}

/*!
    简介:    initialize the DMA Tx/Rx descriptors's parameters in enhanced ring mode with ptp function
    参数[输入]:  direction: the descriptors which users want to init, refer to ENET_dmadirection_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_TX: DMA Tx descriptors
      参数:        ENET_DMA_RX: DMA Rx descriptors
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Enhanced_Descriptors_Ring_Init(ENET_dmadirection_enum direction) {
    uint32_t num = 0U, count = 0U, maxsize = 0U;
    uint32_t desc_status = 0U, desc_bufsize = 0U;
    ENET_Descriptors_Struct *desc;
    ENET_Descriptors_Struct *desc_tab;
    uint8_t *buf;

    /* configure descriptor skip length */
    ENET_DMA_BCTL &= ~ENET_DMA_BCTL_DPSL;
    ENET_DMA_BCTL |= DMA_BCTL_DPSL(0);

    /* if want to initialize DMA Tx descriptors */
    if(ENET_DMA_TX == direction) {
        /* save a copy of the DMA Tx descriptors */
        desc_tab = txdesc_tab;
        buf = &tx_buff[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        /* select ring mode, and enable transmit timestamp function */
        desc_status = ENET_TDES0_TTSEN;

        /* configure DMA Tx descriptor table address register */
        ENET_DMA_TDTADDR = (uint32_t)desc_tab;
        DMA_Current_txdesc = desc_tab;
    } else {
        /* if want to initialize DMA Rx descriptors */
        /* save a copy of the DMA Rx descriptors */
        desc_tab = rxdesc_tab;
        buf = &rx_buff[0][0];
        count = ENET_RXBUF_NUM;
        maxsize = ENET_RXBUF_SIZE;

        /* enable receiving */
        desc_status = ENET_RDES0_DAV;
        /* set buffer1 size */
        desc_bufsize = ENET_RXBUF_SIZE;

        /* configure DMA Rx descriptor table address register */
        ENET_DMA_RDTADDR = (uint32_t)desc_tab;
        DMA_Current_rxdesc = desc_tab;
    }

    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->status = desc_status;
        desc->control_Buffer_size = desc_bufsize;
        desc->buffer1_addr = (uint32_t)(&buf[num * maxsize]);

        /* when it is the last descriptor */
        if(num == (count - 1U)) {
            if(ENET_DMA_TX == direction) {
                /* configure transmit end of ring mode */
                desc->status |= ENET_TDES0_TERM;
            } else {
                /* configure receive end of ring mode */
                desc->control_Buffer_size |= ENET_RDES1_RERM;
            }
        }
    }
}

/*!
    简介:    receive a packet data with timestamp values to application buffer, when the DMA is in enhanced mode
    参数[输入]:  bufsize: the size of buffer which is the parameter in function
    参数[输出]: buffer: pointer to the application buffer
                note -- if the input is NULL, user should copy data in application by himself
    参数[输出]: timestamp: pointer to the table which stores the timestamp high and low
                note -- if the input is NULL, timestamp is ignored
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_PTPFrame_Receive_Enhanced_Mode(uint8_t *buffer, uint32_t bufsize, uint32_t timestamp[]) {
    uint32_t offset = 0U, size = 0U;
    uint32_t timeout = 0U;
    uint32_t rdes0_tsv_flag;

    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (DMA_Current_rxdesc->status & ENET_RDES0_DAV)) {
        return ERROR;
    }

    /* if buffer pointer is null, indicates that users has copied data in application */
    if(NULL != buffer) {
        /* if no error occurs, and the frame uses only one descriptor */
        if(((uint32_t)RESET == (DMA_Current_rxdesc->status & ENET_RDES0_ERRS)) &&
                ((uint32_t)RESET != (DMA_Current_rxdesc->status & ENET_RDES0_LDES)) &&
                ((uint32_t)RESET != (DMA_Current_rxdesc->status & ENET_RDES0_FDES))) {
            /* get the frame length except CRC */
            size = GET_RDES0_FRML(DMA_Current_rxdesc->status) - 4U;

            /* if is a type frame, and CRC is not included in forwarding frame */
            if((RESET != (ENET_MAC_CFG & ENET_MAC_CFG_TFCD)) && (RESET != (DMA_Current_rxdesc->status & ENET_RDES0_FRMT))) {
                size = size + 4U;
            }

            /* to avoid situation that the frame size exceeds the buffer length */
            if(size > bufsize) {
                return ERROR;
            }

            /* copy data from Rx buffer to application buffer */
            for(offset = 0; offset < size; offset++) {
                (*(buffer + offset)) = (*(__IO uint8_t *)((DMA_Current_rxdesc->buffer1_addr) + offset));
            }
        } else {
            return ERROR;
        }
    }

    /* if timestamp pointer is null, indicates that users don't care timestamp in application */
    if(NULL != timestamp) {
        /* wait for ENET_RDES0_TSV flag to be set, the timestamp value is taken and
        write to the RDES6 and RDES7 */
        do {
            rdes0_tsv_flag = (DMA_Current_rxdesc->status & ENET_RDES0_TSV);
            timeout++;
        } while((RESET == rdes0_tsv_flag) && (timeout < ENET_Delay_TO));

        /* return ERROR due to timeout */
        if(ENET_Delay_TO == timeout) {
            return ERROR;
        }

        /* clear the ENET_RDES0_TSV flag */
        DMA_Current_rxdesc->status &= ~ENET_RDES0_TSV;
        /* get the timestamp value of the received frame */
        timestamp[0] = DMA_Current_rxdesc->timestamp_low;
        timestamp[1] = DMA_Current_rxdesc->timestamp_high;
    }

    /* enable reception, descriptor is owned by DMA */
    DMA_Current_rxdesc->status = ENET_RDES0_DAV;

    /* check Rx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_STAT & ENET_DMA_STAT_RBU)) {
        /* Clear RBU flag */
        ENET_DMA_STAT = ENET_DMA_STAT_RBU;
        /* resume DMA reception by writing to the RPEN register*/
        ENET_DMA_RPEN = 0;
    }

    /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
    /* chained mode */
    if((uint32_t)RESET != (DMA_Current_rxdesc->control_Buffer_size & ENET_RDES1_RCHM)) {
        DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_rxdesc->buffer2_next_Desc_addr);
    } else {
        /* ring mode */
        if((uint32_t)RESET != (DMA_Current_rxdesc->control_Buffer_size & ENET_RDES1_RERM)) {
            /* if is the last descriptor in table, the next descriptor is the table header */
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(ENET_DMA_RDTADDR);
        } else {
            /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)((uint32_t)DMA_Current_rxdesc + ETH_DMARXDESC_SIZE + GET_DMA_BCTL_DPSL(ENET_DMA_BCTL));
        }
    }

    return SUCCESS;
}

/*!
    简介:    send data with timestamp values in application buffer as a transmit packet, when the DMA is in enhanced mode
    参数[输入]:  buffer: pointer on the application buffer
                note -- if the input is NULL, user should copy data in application by himself
    参数[输入]:  length: the length of frame data to be transmitted
    参数[输出]: timestamp: pointer to the table which stores the timestamp high and low
                note -- if the input is NULL, timestamp is ignored
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_PTPFrame_Transmit_Enhanced_Mode(uint8_t *buffer, uint32_t length, uint32_t timestamp[]) {
    uint32_t offset = 0;
    uint32_t DMA_tbu_flag, DMA_tu_flag;
    uint32_t tdes0_ttmss_flag;
    uint32_t timeout = 0;

    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_DAV)) {
        return ERROR;
    }

    /* only frame length no more than ENET_MAX_Frame_SIZE is allowed */
    if(length > ENET_MAX_Frame_SIZE) {
        return ERROR;
    }

    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0; offset < length; offset++) {
            (*(__IO uint8_t *)((DMA_Current_txdesc->buffer1_addr) + offset)) = (*(buffer + offset));
        }
    }

    /* set the frame length */
    DMA_Current_txdesc->control_Buffer_size = length;
    /* set the segment of frame, frame is transmitted in one descriptor */
    DMA_Current_txdesc->status |= ENET_TDES0_LSG | ENET_TDES0_FSG;
    /* enable the DMA transmission */
    DMA_Current_txdesc->status |= ENET_TDES0_DAV;

    /* check Tx buffer unavailable flag status */
    DMA_tbu_flag = (ENET_DMA_STAT & ENET_DMA_STAT_TBU);
    DMA_tu_flag = (ENET_DMA_STAT & ENET_DMA_STAT_TU);

    if((RESET != DMA_tbu_flag) || (RESET != DMA_tu_flag)) {
        /* Clear TBU and TU flag */
        ENET_DMA_STAT = (DMA_tbu_flag | DMA_tu_flag);
        /* resume DMA transmission by writing to the TPEN register*/
        ENET_DMA_TPEN = 0;
    }

    /* if timestamp pointer is null, indicates that users don't care timestamp in application */
    if(NULL != timestamp) {
        /* wait for ENET_TDES0_TTMSS flag to be set, a timestamp was captured */
        do {
            tdes0_ttmss_flag = (DMA_Current_txdesc->status & ENET_TDES0_TTMSS);
            timeout++;
        } while((RESET == tdes0_ttmss_flag) && (timeout < ENET_Delay_TO));

        /* return ERROR due to timeout */
        if(ENET_Delay_TO == timeout) {
            return ERROR;
        }

        /* clear the ENET_TDES0_TTMSS flag */
        DMA_Current_txdesc->status &= ~ENET_TDES0_TTMSS;
        /* get the timestamp value of the transmit frame */
        timestamp[0] = DMA_Current_txdesc->timestamp_low;
        timestamp[1] = DMA_Current_txdesc->timestamp_high;
    }

    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table*/
    /* chained mode */
    if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_TCHM)) {
        DMA_Current_txdesc = (ENET_Descriptors_Struct *)(DMA_Current_txdesc->buffer2_next_Desc_addr);
    } else {
        /* ring mode */
        if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_TERM)) {
            /* if is the last descriptor in table, the next descriptor is the table header */
            DMA_Current_txdesc = (ENET_Descriptors_Struct *)(ENET_DMA_TDTADDR);
        } else {
            /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
            DMA_Current_txdesc = (ENET_Descriptors_Struct *)((uint32_t)DMA_Current_txdesc + ETH_DMATXDESC_SIZE + GET_DMA_BCTL_DPSL(ENET_DMA_BCTL));
        }
    }

    return SUCCESS;
}

#else

/*!
    简介:    configure descriptor to work in normal mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_Desc_Select_Normal_Mode(void) {
    ENET_DMA_BCTL &= ~ENET_DMA_BCTL_DFM;
}

/*!
    简介:    initialize the DMA Tx/Rx descriptors's parameters in normal chain mode with PTP function
    参数[输入]:  direction: the descriptors which users want to init, refer to ENET_dmadirection_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_TX: DMA Tx descriptors
      参数:        ENET_DMA_RX: DMA Rx descriptors
    参数[输入]:  desc_ptptab: pointer to the first descriptor address of PTP Rx descriptor table
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Normal_Descriptors_Chain_Init(ENET_dmadirection_enum direction, ENET_Descriptors_Struct *desc_ptptab) {
    uint32_t num = 0U, count = 0U, maxsize = 0U;
    uint32_t desc_status = 0U, desc_bufsize = 0U;
    ENET_Descriptors_Struct *desc, *desc_tab;
    uint8_t *buf;

    /* if want to initialize DMA Tx descriptors */
    if(ENET_DMA_TX == direction) {
        /* save a copy of the DMA Tx descriptors */
        desc_tab = txdesc_tab;
        buf = &tx_buff[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        /* select chain mode, and enable transmit timestamp function */
        desc_status = ENET_TDES0_TCHM | ENET_TDES0_TTSEN;

        /* configure DMA Tx descriptor table address register */
        ENET_DMA_TDTADDR = (uint32_t)desc_tab;
        DMA_Current_txdesc = desc_tab;
        DMA_Current_PTP_txdesc = desc_ptptab;
    } else {
        /* if want to initialize DMA Rx descriptors */
        /* save a copy of the DMA Rx descriptors */
        desc_tab = rxdesc_tab;
        buf = &rx_buff[0][0];
        count = ENET_RXBUF_NUM;
        maxsize = ENET_RXBUF_SIZE;

        /* enable receiving */
        desc_status = ENET_RDES0_DAV;
        /* select receive chained mode and set buffer1 size */
        desc_bufsize = ENET_RDES1_RCHM | (uint32_t)ENET_RXBUF_SIZE;

        /* configure DMA Rx descriptor table address register */
        ENET_DMA_RDTADDR = (uint32_t)desc_tab;
        DMA_Current_rxdesc = desc_tab;
        DMA_Current_PTP_rxdesc = desc_ptptab;
    }

    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->status = desc_status;
        desc->control_Buffer_size = desc_bufsize;
        desc->buffer1_addr = (uint32_t)(&buf[num * maxsize]);

        /* if is not the last descriptor */
        if(num < (count - 1U)) {
            /* configure the next descriptor address */
            desc->buffer2_next_Desc_addr = (uint32_t)(desc_tab + num + 1U);
        } else {
            /* when it is the last descriptor, the next descriptor address
            equals to first descriptor address in descriptor table */
            desc->buffer2_next_Desc_addr = (uint32_t)desc_tab;
        }

        /* set desc_ptptab equal to desc_tab */
        (&desc_ptptab[num])->buffer1_addr = desc->buffer1_addr;
        (&desc_ptptab[num])->buffer2_next_Desc_addr = desc->buffer2_next_Desc_addr;
    }

    /* when it is the last ptp descriptor, preserve the first descriptor
    address of desc_ptptab in ptp descriptor status */
    (&desc_ptptab[num - 1U])->status = (uint32_t)desc_ptptab;
}

/*!
    简介:    initialize the DMA Tx/Rx descriptors's parameters in normal ring mode with PTP function
    参数[输入]:  direction: the descriptors which users want to init, refer to ENET_dmadirection_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_DMA_TX: DMA Tx descriptors
      参数:        ENET_DMA_RX: DMA Rx descriptors
    参数[输入]:  desc_ptptab: pointer to the first descriptor address of PTP Rx descriptor table
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Normal_Descriptors_Ring_Init(ENET_dmadirection_enum direction, ENET_Descriptors_Struct *desc_ptptab) {
    uint32_t num = 0U, count = 0U, maxsize = 0U;
    uint32_t desc_status = 0U, desc_bufsize = 0U;
    ENET_Descriptors_Struct *desc, *desc_tab;
    uint8_t *buf;

    /* configure descriptor skip length */
    ENET_DMA_BCTL &= ~ENET_DMA_BCTL_DPSL;
    ENET_DMA_BCTL |= DMA_BCTL_DPSL(0);

    /* if want to initialize DMA Tx descriptors */
    if(ENET_DMA_TX == direction) {
        /* save a copy of the DMA Tx descriptors */
        desc_tab = txdesc_tab;
        buf = &tx_buff[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        /* select ring mode, and enable transmit timestamp function */
        desc_status = ENET_TDES0_TTSEN;

        /* configure DMA Tx descriptor table address register */
        ENET_DMA_TDTADDR = (uint32_t)desc_tab;
        DMA_Current_txdesc = desc_tab;
        DMA_Current_PTP_txdesc = desc_ptptab;
    } else {
        /* if want to initialize DMA Rx descriptors */
        /* save a copy of the DMA Rx descriptors */
        desc_tab = rxdesc_tab;
        buf = &rx_buff[0][0];
        count = ENET_RXBUF_NUM;
        maxsize = ENET_RXBUF_SIZE;

        /* enable receiving */
        desc_status = ENET_RDES0_DAV;
        /* select receive ring mode and set buffer1 size */
        desc_bufsize = (uint32_t)ENET_RXBUF_SIZE;

        /* configure DMA Rx descriptor table address register */
        ENET_DMA_RDTADDR = (uint32_t)desc_tab;
        DMA_Current_rxdesc = desc_tab;
        DMA_Current_PTP_rxdesc = desc_ptptab;
    }

    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->status = desc_status;
        desc->control_Buffer_size = desc_bufsize;
        desc->buffer1_addr = (uint32_t)(&buf[num * maxsize]);

        /* when it is the last descriptor */
        if(num == (count - 1U)) {
            if(ENET_DMA_TX == direction) {
                /* configure transmit end of ring mode */
                desc->status |= ENET_TDES0_TERM;
            } else {
                /* configure receive end of ring mode */
                desc->control_Buffer_size |= ENET_RDES1_RERM;
            }
        }

        /* set desc_ptptab equal to desc_tab */
        (&desc_ptptab[num])->buffer1_addr = desc->buffer1_addr;
        (&desc_ptptab[num])->buffer2_next_Desc_addr = desc->buffer2_next_Desc_addr;
    }

    /* when it is the last ptp descriptor, preserve the first descriptor
    address of desc_ptptab in ptp descriptor status */
    (&desc_ptptab[num - 1U])->status = (uint32_t)desc_ptptab;
}

/*!
    简介:    receive a packet data with timestamp values to application buffer, when the DMA is in normal mode
    参数[输入]:  bufsize: the size of buffer which is the parameter in function
    参数[输出]: buffer: pointer to the application buffer
                note -- if the input is NULL, user should copy data in application by himself
    参数[输出]: timestamp: pointer to the table which stores the timestamp high and low
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_PTPFrame_Receive_Normal_Mode(uint8_t *buffer, uint32_t bufsize, uint32_t timestamp[]) {
    uint32_t offset = 0U, size = 0U;

    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (DMA_Current_rxdesc->status & ENET_RDES0_DAV)) {
        return ERROR;
    }

    /* if buffer pointer is null, indicates that users has copied data in application */
    if(NULL != buffer) {
        /* if no error occurs, and the frame uses only one descriptor */
        if(((uint32_t)RESET == (DMA_Current_rxdesc->status & ENET_RDES0_ERRS)) &&
                ((uint32_t)RESET != (DMA_Current_rxdesc->status & ENET_RDES0_LDES)) &&
                ((uint32_t)RESET != (DMA_Current_rxdesc->status & ENET_RDES0_FDES))) {

            /* get the frame length except CRC */
            size = GET_RDES0_FRML(DMA_Current_rxdesc->status) - 4U;

            /* if is a type frame, and CRC is not included in forwarding frame */
            if((RESET != (ENET_MAC_CFG & ENET_MAC_CFG_TFCD)) && (RESET != (DMA_Current_rxdesc->status & ENET_RDES0_FRMT))) {
                size = size + 4U;
            }

            /* to avoid situation that the frame size exceeds the buffer length */
            if(size > bufsize) {
                return ERROR;
            }

            /* copy data from Rx buffer to application buffer */
            for(offset = 0U; offset < size; offset++) {
                (*(buffer + offset)) = (*(__IO uint8_t *)(uint32_t)((DMA_Current_PTP_rxdesc->buffer1_addr) + offset));
            }

        } else {
            return ERROR;
        }
    }

    /* copy timestamp value from Rx descriptor to application array */
    timestamp[0] = DMA_Current_rxdesc->buffer1_addr;
    timestamp[1] = DMA_Current_rxdesc->buffer2_next_Desc_addr;

    DMA_Current_rxdesc->buffer1_addr = DMA_Current_PTP_rxdesc ->buffer1_addr ;
    DMA_Current_rxdesc->buffer2_next_Desc_addr = DMA_Current_PTP_rxdesc ->buffer2_next_Desc_addr;

    /* enable reception, descriptor is owned by DMA */
    DMA_Current_rxdesc->status = ENET_RDES0_DAV;

    /* check Rx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_STAT & ENET_DMA_STAT_RBU)) {
        /* clear RBU flag */
        ENET_DMA_STAT = ENET_DMA_STAT_RBU;
        /* resume DMA reception by writing to the RPEN register*/
        ENET_DMA_RPEN = 0U;
    }


    /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
    /* chained mode */
    if((uint32_t)RESET != (DMA_Current_rxdesc->control_Buffer_size & ENET_RDES1_RCHM)) {
        DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_rxdesc->buffer2_next_Desc_addr);

        /* if it is the last ptp descriptor */
        if(0U != DMA_Current_PTP_rxdesc->status) {
            /* pointer back to the first ptp descriptor address in the desc_ptptab list address */
            DMA_Current_PTP_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_rxdesc->status);
        } else {
            /* ponter to the next ptp descriptor */
            DMA_Current_PTP_rxdesc++;
        }
    } else {
        /* ring mode */
        if((uint32_t)RESET != (DMA_Current_rxdesc->control_Buffer_size & ENET_RDES1_RERM)) {
            /* if is the last descriptor in table, the next descriptor is the table header */
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(ENET_DMA_RDTADDR);
            /* RDES2 and RDES3 will not be covered by buffer address, so do not need to preserve a new table,
            use the same table with RxDMA descriptor */
            DMA_Current_PTP_rxdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_rxdesc->status);
        } else {
            /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
            DMA_Current_rxdesc = (ENET_Descriptors_Struct *)(uint32_t)((uint32_t)DMA_Current_rxdesc + ETH_DMARXDESC_SIZE + GET_DMA_BCTL_DPSL(ENET_DMA_BCTL));
            DMA_Current_PTP_rxdesc ++;
        }
    }

    return SUCCESS;
}

/*!
    简介:    send data with timestamp values in application buffer as a transmit packet, when the DMA is in normal mode
    参数[输入]:  buffer: pointer on the application buffer
                note -- if the input is NULL, user should copy data in application by himself
    参数[输入]:  length: the length of frame data to be transmitted
    参数[输出]: timestamp: pointer to the table which stores the timestamp high and low
                note -- if the input is NULL, timestamp is ignored
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_PTPFrame_Transmit_Normal_Mode(uint8_t *buffer, uint32_t length, uint32_t timestamp[]) {
    uint32_t offset = 0U, timeout = 0U;
    uint32_t DMA_tbu_flag, DMA_tu_flag, tdes0_ttmss_flag;

    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_DAV)) {
        return ERROR;
    }

    /* only frame length no more than ENET_MAX_Frame_SIZE is allowed */
    if(length > ENET_MAX_Frame_SIZE) {
        return ERROR;
    }

    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0U; offset < length; offset++) {
            (*(__IO uint8_t *)(uint32_t)((DMA_Current_PTP_txdesc->buffer1_addr) + offset)) = (*(buffer + offset));
        }
    }

    /* set the frame length */
    DMA_Current_txdesc->control_Buffer_size = (length & (uint32_t)0x1FFF);
    /* set the segment of frame, frame is transmitted in one descriptor */
    DMA_Current_txdesc->status |= ENET_TDES0_LSG | ENET_TDES0_FSG;
    /* enable the DMA transmission */
    DMA_Current_txdesc->status |= ENET_TDES0_DAV;

    /* check Tx buffer unavailable flag status */
    DMA_tbu_flag = (ENET_DMA_STAT & ENET_DMA_STAT_TBU);
    DMA_tu_flag = (ENET_DMA_STAT & ENET_DMA_STAT_TU);

    if((RESET != DMA_tbu_flag) || (RESET != DMA_tu_flag)) {
        /* clear TBU and TU flag */
        ENET_DMA_STAT = (DMA_tbu_flag | DMA_tu_flag);
        /* resume DMA transmission by writing to the TPEN register*/
        ENET_DMA_TPEN = 0U;
    }

    /* if timestamp pointer is null, indicates that users don't care timestamp in application */
    if(NULL != timestamp) {
        /* wait for ENET_TDES0_TTMSS flag to be set, a timestamp was captured */
        do {
            tdes0_ttmss_flag = (DMA_Current_txdesc->status & ENET_TDES0_TTMSS);
            timeout++;
        } while((RESET == tdes0_ttmss_flag) && (timeout < ENET_Delay_TO));

        /* return ERROR due to timeout */
        if(ENET_Delay_TO == timeout) {
            return ERROR;
        }

        /* clear the ENET_TDES0_TTMSS flag */
        DMA_Current_txdesc->status &= ~ENET_TDES0_TTMSS;
        /* get the timestamp value of the transmit frame */
        timestamp[0] = DMA_Current_txdesc->buffer1_addr;
        timestamp[1] = DMA_Current_txdesc->buffer2_next_Desc_addr;
    }

    DMA_Current_txdesc->buffer1_addr = DMA_Current_PTP_txdesc ->buffer1_addr ;
    DMA_Current_txdesc->buffer2_next_Desc_addr = DMA_Current_PTP_txdesc ->buffer2_next_Desc_addr;

    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table */
    /* chained mode */
    if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_TCHM)) {
        DMA_Current_txdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_txdesc->buffer2_next_Desc_addr);

        /* if it is the last ptp descriptor */
        if(0U != DMA_Current_PTP_txdesc->status) {
            /* pointer back to the first ptp descriptor address in the desc_ptptab list address */
            DMA_Current_PTP_txdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_txdesc->status);
        } else {
            /* ponter to the next ptp descriptor */
            DMA_Current_PTP_txdesc++;
        }
    } else {
        /* ring mode */
        if((uint32_t)RESET != (DMA_Current_txdesc->status & ENET_TDES0_TERM)) {
            /* if is the last descriptor in table, the next descriptor is the table header */
            DMA_Current_txdesc = (ENET_Descriptors_Struct *)(ENET_DMA_TDTADDR);
            /* TDES2 and TDES3 will not be covered by buffer address, so do not need to preserve a new table,
            use the same table with TxDMA descriptor */
            DMA_Current_PTP_txdesc = (ENET_Descriptors_Struct *)(DMA_Current_PTP_txdesc->status);
        } else {
            /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
            DMA_Current_txdesc = (ENET_Descriptors_Struct *)(uint32_t)((uint32_t)DMA_Current_txdesc + ETH_DMATXDESC_SIZE + GET_DMA_BCTL_DPSL(ENET_DMA_BCTL));
            DMA_Current_PTP_txdesc ++;
        }
    }

    return SUCCESS;
}

#endif /* SELECT_Descriptors_Enhanced_MODE */

/*!
    简介:    wakeup frame filter register pointer reset
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_WUM_Filter_Register_Pointer_Reset(void) {
    ENET_MAC_WUM |= ENET_MAC_WUM_WUFFRPR;
}

/*!
    简介:    set the remote wakeup frame registers
    参数[输入]:  pdata: pointer to buffer data which is written to remote wakeup frame registers (8 words total)
    参数[输出]:  无
    返回值:      无
*/
void ENET_WUM_Filter_Config(uint32_t pdata[]) {
    uint32_t num = 0U;

    /* configure ENET_MAC_RWFF register */
    for(num = 0U; num < ETH_WakeUp_Register_LENGTH; num++) {
        ENET_MAC_RWFF = pdata[num];
    }
}

/*!
    简介:    enable wakeup management features
    参数[输入]:  feature: the wake up type which is selected
                one or more parameters can be selected which are shown as below
      参数:        ENET_WUM_Power_DOWN: power down mode
      参数:        ENET_WUM_MAGIC_PACKET_FRAME: enable a wakeup event due to magic packet reception
      参数:        ENET_WUM_WAKE_Up_FRAME: enable a wakeup event due to wakeup frame reception
      参数:        ENET_WUM_GLOBAL_UNICAST: any received unicast frame passed filter is considered to be a wakeup frame
    参数[输出]:  无
    返回值:      无
*/
void ENET_WUM_Feature_Enable(uint32_t feature) {
    ENET_MAC_WUM |= feature;
}

/*!
    简介:    disable wakeup management features
    参数[输入]:  feature: the wake up type which is selected
                one or more parameters can be selected which are shown as below
      参数:        ENET_WUM_MAGIC_PACKET_FRAME: enable a wakeup event due to magic packet reception
      参数:        ENET_WUM_WAKE_Up_FRAME: enable a wakeup event due to wakeup frame reception
      参数:        ENET_WUM_GLOBAL_UNICAST: any received unicast frame passed filter is considered to be a wakeup frame
    参数[输出]:  无
    返回值:      无
*/
void ENET_WUM_Feature_Disable(uint32_t feature) {
    ENET_MAC_WUM &= (~feature);
}

/*!
    简介:    reset the MAC statistics counters
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_MSC_Counters_Reset(void) {
    /* reset all counters */
    ENET_MSC_CTL |= ENET_MSC_CTL_CTR;
}

/*!
    简介:    enable the MAC statistics counter features
    参数[输入]:  feature: the feature of MAC statistics counter
                one or more parameters can be selected which are shown as below
      参数:        ENET_MSC_Counter_Stop_ROLLOVER: counter stop rollover
      参数:        ENET_MSC_RESET_ON_READ: reset on read
      参数:        ENET_MSC_Counters_FREEZE: MSC counter freeze
    参数[输出]:  无
    返回值:      无
*/
void ENET_MSC_Feature_Enable(uint32_t feature) {
    ENET_MSC_CTL |= feature;
}

/*!
    简介:    disable the MAC statistics counter features
    参数[输入]:  feature: the feature of MAC statistics counter
                one or more parameters can be selected which are shown as below
      参数:        ENET_MSC_Counter_Stop_ROLLOVER: counter stop rollover
      参数:        ENET_MSC_RESET_ON_READ: reset on read
      参数:        ENET_MSC_Counters_FREEZE: MSC counter freeze
    参数[输出]:  无
    返回值:      无
*/
void ENET_MSC_Feature_Disable(uint32_t feature) {
    ENET_MSC_CTL &= (~feature);
}

/*!
    简介:    configure MAC statistics counters preset mode
    参数[输入]:  mode: MSC counters preset mode, refer to ENET_MSC_Preset_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MSC_Preset_NONE: do not preset MSC counter
      参数:        ENET_MSC_Preset_HALF: preset all MSC counters to almost-half(0x7FFF FFF0) value
      参数:        ENET_MSC_Preset_FULL: preset all MSC counters to almost-full(0xFFFF FFF0) value
    参数[输出]:  无
    返回值:      无
*/
void ENET_MSC_Counters_Preset_Config(ENET_MSC_Preset_enum mode) {
    ENET_MSC_CTL &= ENET_MSC_Preset_MASK;
    ENET_MSC_CTL |= (uint32_t)mode;
}

/*!
    简介:    get MAC statistics counter
    参数[输入]:  counter: MSC counters which is selected, refer to ENET_MSC_Counter_enum
                only one parameter can be selected which is shown as below
      参数:        ENET_MSC_TX_SCCNT: MSC transmitted good frames after a single collision counter
      参数:        ENET_MSC_TX_MSCCNT: MSC transmitted good frames after more than a single collision counter
      参数:        ENET_MSC_TX_TGFCNT: MSC transmitted good frames counter
      参数:        ENET_MSC_RX_RFCECNT: MSC received frames with CRC error counter
      参数:        ENET_MSC_RX_RFAECNT: MSC received frames with alignment error counter
      参数:        ENET_MSC_RX_RGUFCNT: MSC received good unicast frames counter
    参数[输出]:  无
    返回值:     the MSC counter value
*/
uint32_t ENET_MSC_Counters_Get(ENET_MSC_Counter_enum counter) {
    uint32_t reval;

    reval = REG32((ENET + (uint32_t)counter));

    return reval;
}

/*!
    简介:    enable the PTP features
    参数[输入]:  feature: the feature of ENET PTP mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_RXTX_TIMESTAMP: timestamp function for transmit and receive frames
      参数:        ENET_PTP_Timestamp_INT: timestamp interrupt trigger
      参数:        ENET_ALL_RX_TIMESTAMP: all received frames are taken snapshot
      参数:        ENET_NONTYPE_Frame_SNAPSHOT: take snapshot when received non type frame
      参数:        ENET_IPV6_Frame_SNAPSHOT: take snapshot for IPv6 frame
      参数:        ENET_IPV4_Frame_SNAPSHOT: take snapshot for IPv4 frame
      参数:        ENET_PTP_Frame_USE_MACADDRESS_FILTER: use MAC address1-3 to filter the PTP frame
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Feature_Enable(uint32_t feature) {
    ENET_PTP_TSCTL |= feature;
}

/*!
    简介:    disable the PTP features
    参数[输入]:  feature: the feature of ENET PTP mode
                one or more parameters can be selected which are shown as below
      参数:        ENET_RXTX_TIMESTAMP: timestamp function for transmit and receive frames
      参数:        ENET_PTP_Timestamp_INT: timestamp interrupt trigger
      参数:        ENET_ALL_RX_TIMESTAMP: all received frames are taken snapshot
      参数:        ENET_NONTYPE_Frame_SNAPSHOT: take snapshot when received non type frame
      参数:        ENET_IPV6_Frame_SNAPSHOT: take snapshot for IPv6 frame
      参数:        ENET_IPV4_Frame_SNAPSHOT: take snapshot for IPv4 frame
      参数:        ENET_PTP_Frame_USE_MACADDRESS_FILTER: use MAC address1-3 to filter the PTP frame
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Feature_Disable(uint32_t feature) {
    ENET_PTP_TSCTL &= ~feature;
}

/*!
    简介:    configure the PTP timestamp function
    参数[输入]:  func: the function of PTP timestamp
                only one parameter can be selected which is shown as below
      参数:        ENET_CKNT_ORDINARY: type of ordinary clock node type for timestamp
      参数:        ENET_CKNT_BOUNDARY: type of boundary clock node type for timestamp
      参数:        ENET_CKNT_End_TO_END: type of end-to-end transparent clock node type for timestamp
      参数:        ENET_CKNT_PEER_TO_PEER: type of peer-to-peer transparent clock node type for timestamp
      参数:        ENET_PTP_Addend_UPDATE: addend register update
      参数:        ENET_PTP_SYSTIME_UPDATE: timestamp update
      参数:        ENET_PTP_SYSTIME_INIT: timestamp initialize
      参数:        ENET_PTP_FINEMODE: the system timestamp uses the fine method for updating
      参数:        ENET_PTP_COARSEMODE: the system timestamp uses the coarse method for updating
      参数:        ENET_SubSecond_DIGITAL_ROLLOVER: digital rollover mode
      参数:        ENET_SubSecond_BINARY_ROLLOVER: binary rollover mode
      参数:        ENET_SNOOPING_PTP_VERSION_2: version 2
      参数:        ENET_SNOOPING_PTP_VERSION_1: version 1
      参数:        ENET_Event_TYPE_MESSAGES_SNAPSHOT: only event type messages are taken snapshot
      参数:        ENET_ALL_TYPE_MESSAGES_SNAPSHOT: all type messages are taken snapshot except announce,
                                                   management and signaling message
      参数:        ENET_Master_NODE_Message_SNAPSHOT: snapshot is only take for master node message
      参数:        ENET_Slave_NODE_Message_SNAPSHOT: snapshot is only taken for slave node message
    参数[输出]:  无
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus ENET_PTP_Timestamp_Function_Config(ENET_PTP_Function_enum func) {
    uint32_t temp_Config = 0U, temp_state = 0U;
    uint32_t timeout = 0U;
    ErrStatus ENET_state = SUCCESS;

    switch(func) {
    case ENET_CKNT_ORDINARY:
    case ENET_CKNT_BOUNDARY:
    case ENET_CKNT_End_TO_END:
    case ENET_CKNT_PEER_TO_PEER:
        ENET_PTP_TSCTL &= ~ENET_PTP_TSCTL_CKNT;
        ENET_PTP_TSCTL |= (uint32_t)func;
        break;

    case ENET_PTP_Addend_UPDATE:

        /* this bit must be read as zero before application set it */
        do {
            temp_state = ENET_PTP_TSCTL & ENET_PTP_TSCTL_TMSARU;
            timeout++;
        } while((RESET != temp_state) && (timeout < ENET_Delay_TO));

        /* return ERROR due to timeout */
        if(ENET_Delay_TO == timeout) {
            ENET_state = ERROR;
        } else {
            ENET_PTP_TSCTL |= ENET_PTP_TSCTL_TMSARU;
        }

        break;

    case ENET_PTP_SYSTIME_UPDATE:

        /* both the TMSSTU and TMSSTI bits must be read as zero before application set this bit */
        do {
            temp_state = ENET_PTP_TSCTL & (ENET_PTP_TSCTL_TMSSTU | ENET_PTP_TSCTL_TMSSTI);
            timeout++;
        } while((RESET != temp_state) && (timeout < ENET_Delay_TO));

        /* return ERROR due to timeout */
        if(ENET_Delay_TO == timeout) {
            ENET_state = ERROR;
        } else {
            ENET_PTP_TSCTL |= ENET_PTP_TSCTL_TMSSTU;
        }

        break;

    case ENET_PTP_SYSTIME_INIT:

        /* this bit must be read as zero before application set it */
        do {
            temp_state = ENET_PTP_TSCTL & ENET_PTP_TSCTL_TMSSTI;
            timeout++;
        } while((RESET != temp_state) && (timeout < ENET_Delay_TO));

        /* return ERROR due to timeout */
        if(ENET_Delay_TO == timeout) {
            ENET_state = ERROR;
        } else {
            ENET_PTP_TSCTL |= ENET_PTP_TSCTL_TMSSTI;
        }

        break;

    default:
        temp_Config = (uint32_t)func & (~BIT(31));

        if(RESET != ((uint32_t)func & BIT(31))) {
            ENET_PTP_TSCTL |= temp_Config;
        } else {
            ENET_PTP_TSCTL &= ~temp_Config;
        }

        break;
    }

    return ENET_state;
}

/*!
    简介:    configure system time subsecond increment value
    参数[输入]:  subsecond: the value will be added to the subsecond value of system time(0x00000000 - 0x000000FF)
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_SubSecond_Increment_Config(uint32_t subsecond) {
    ENET_PTP_SSINC = PTP_SSINC_STMSSI(subsecond);
}

/*!
    简介:    adjusting the clock frequency only in fine update mode
    参数[输入]:  add: the value will be added to the accumulator register to achieve time synchronization
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Timestamp_Addend_Config(uint32_t add) {
    ENET_PTP_TSADDEND = add;
}

/*!
    简介:    initialize or add/subtract to second of the system time
    参数[输入]:  sign: timestamp update positive or negative sign
                only one parameter can be selected which is shown as below
      参数:        ENET_PTP_ADD_TO_TIME: timestamp update value is added to system time
      参数:        ENET_PTP_SUBSTRACT_FROM_TIME: timestamp update value is subtracted from system time
    参数[输入]:  second: initializing or adding/subtracting to second of the system time
    参数[输入]:  subsecond: the current subsecond of the system time
                with 0.46 ns accuracy if required accuracy is 20 ns
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Timestamp_Update_Config(uint32_t sign, uint32_t second, uint32_t subsecond) {
    ENET_PTP_TSUH = second;
    ENET_PTP_TSUL = sign | PTP_TSUL_TMSUSS(subsecond);
}

/*!
    简介:    configure the expected target time
    参数[输入]:  second: the expected target second time
    参数[输入]:  nanosecond: the expected target nanosecond time (signed)
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_Expected_Time_Config(uint32_t second, uint32_t nanosecond) {
    ENET_PTP_ETH = second;
    ENET_PTP_ETL = nanosecond;
}

/*!
    简介:    get the current system time
    参数[输入]:  无
    参数[输出]: systime_Struct: pointer to a ENET_PTP_systime_Struct structure which contains
                parameters of PTP system time
                members of the structure and the member values are shown as below:
                  second: 0x0 - 0xFFFF FFFF
                  subsecond: 0x0 - 0x7FFF FFFF
                  sign: ENET_PTP_Time_POSITIVE, ENET_PTP_Time_NEGATIVE
    返回值:      无
*/
void ENET_PTP_System_Time_Get(ENET_PTP_systime_Struct *systime_Struct) {
    uint32_t temp_sec = 0U, temp_subs = 0U;

    /* get the value of sysytem time registers */
    temp_sec = (uint32_t)ENET_PTP_TSH;
    temp_subs = (uint32_t)ENET_PTP_TSL;

    /* get sysytem time and construct the ENET_PTP_systime_Struct structure */
    systime_Struct->second = temp_sec;
    systime_Struct->subsecond = GET_PTP_TSL_STMSS(temp_subs);
    systime_Struct->sign = GET_PTP_TSL_STS(temp_subs);
}

/*!
    简介:    configure the PPS output frequency
    参数[输入]:  freq: PPS output frequency
                only one parameter can be selected which is shown as below
      参数:        ENET_PPSOFC_1HZ: PPS output 1Hz frequency
      参数:        ENET_PPSOFC_2HZ: PPS output 2Hz frequency
      参数:        ENET_PPSOFC_4HZ: PPS output 4Hz frequency
      参数:        ENET_PPSOFC_8HZ: PPS output 8Hz frequency
      参数:        ENET_PPSOFC_16HZ: PPS output 16Hz frequency
      参数:        ENET_PPSOFC_32HZ: PPS output 32Hz frequency
      参数:        ENET_PPSOFC_64HZ: PPS output 64Hz frequency
      参数:        ENET_PPSOFC_128HZ: PPS output 128Hz frequency
      参数:        ENET_PPSOFC_256HZ: PPS output 256Hz frequency
      参数:        ENET_PPSOFC_512HZ: PPS output 512Hz frequency
      参数:        ENET_PPSOFC_1024HZ: PPS output 1024Hz frequency
      参数:        ENET_PPSOFC_2048HZ: PPS output 2048Hz frequency
      参数:        ENET_PPSOFC_4096HZ: PPS output 4096Hz frequency
      参数:        ENET_PPSOFC_8192HZ: PPS output 8192Hz frequency
      参数:        ENET_PPSOFC_16384HZ: PPS output 16384Hz frequency
      参数:        ENET_PPSOFC_32768HZ: PPS output 32768Hz frequency
    参数[输出]:  无
    返回值:      无
*/
void ENET_PTP_PPS_OutPut_Frequency_Config(uint32_t freq) {
    ENET_PTP_PPSCTL = freq;
}

/*!
    简介:    reset the ENET initpara struct, call it before using ENET_initpara_Config()
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ENET_initpara_Reset(void) {
    ENET_initpara.option_enable = 0U;
    ENET_initpara.forward_frame = 0U;
    ENET_initpara.dmabus_mode = 0U;
    ENET_initpara.DMA_maxburst = 0U;
    ENET_initpara.DMA_arbitration = 0U;
    ENET_initpara.store_forward_mode = 0U;
    ENET_initpara.DMA_function = 0U;
    ENET_initpara.vlan_Config = 0U;
    ENET_initpara.flow_control = 0U;
    ENET_initpara.hashtable_high = 0U;
    ENET_initpara.hashtable_low = 0U;
    ENET_initpara.framesfilter_mode = 0U;
    ENET_initpara.halfduplex_param = 0U;
    ENET_initpara.TIMER_Config = 0U;
    ENET_initpara.interframegap = 0U;
}

/*!
    简介:    initialize ENET peripheral with generally concerned parameters, call it by ENET_Init()
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
static void ENET_default_Init(void) {
    uint32_t reg_value = 0U;

    /* MAC */
    /* configure ENET_MAC_CFG register */
    reg_value = ENET_MAC_CFG;
    reg_value &= MAC_CFG_MASK;
    reg_value |= ENET_WatchDog_ENABLE | ENET_JABBER_ENABLE | ENET_INTERFRAMEGAP_96BIT \
                 | ENET_SPEEDMODE_10M | ENET_Mode_HALFDUPLEX | ENET_LOOPBACKMODE_DISABLE \
                 | ENET_CARRIERSENSE_ENABLE | ENET_RECEIVEOWN_ENABLE \
                 | ENET_RETRYTRANSMISSION_ENABLE | ENET_BACKOFFLIMIT_10 \
                 | ENET_DEFERRALCHECK_DISABLE \
                 | ENET_TYPEFRAME_CRC_DROP_DISABLE \
                 | ENET_Auto_PADCRC_DROP_DISABLE \
                 | ENET_CHECKSUMOFFLOAD_DISABLE;
    ENET_MAC_CFG = reg_value;

    /* configure ENET_MAC_FRMF register */
    ENET_MAC_FRMF = ENET_SRC_Filter_DISABLE | ENET_DEST_Filter_INVERSE_DISABLE \
                    | ENET_MULTICAST_Filter_PERFECT | ENET_UNICAST_Filter_PERFECT \
                    | ENET_PCFRM_PREVENT_ALL | ENET_BROADCASTFRAMES_ENABLE \
                    | ENET_PROMISCUOUS_DISABLE | ENET_RX_Filter_ENABLE;

    /* configure ENET_MAC_HLH, ENET_MAC_HLL register */
    ENET_MAC_HLH = 0x0U;

    ENET_MAC_HLL = 0x0U;

    /* configure ENET_MAC_FCTL, ENET_MAC_FCTH register */
    reg_value = ENET_MAC_FCTL;
    reg_value &= MAC_FCTL_MASK;
    reg_value |= MAC_FCTL_PTM(0) | ENET_ZERO_QUANTA_PAUSE_DISABLE \
                 | ENET_PAUSETIME_MINUS4 | ENET_UNIQUE_PAUSEDETECT \
                 | ENET_RX_FLOWCONTROL_DISABLE | ENET_TX_FLOWCONTROL_DISABLE;
    ENET_MAC_FCTL = reg_value;

    /* configure ENET_MAC_VLT register */
    ENET_MAC_VLT = ENET_VLANTAGCOMPARISON_16BIT | MAC_VLT_VLTI(0);

    /* DMA */
    /* configure ENET_DMA_CTL register */
    reg_value = ENET_DMA_CTL;
    reg_value &= DMA_CTL_MASK;
    reg_value |= ENET_TCPIP_CKSUMERROR_DROP | ENET_RX_Mode_STOREFORWARD \
                 | ENET_FLUSH_RXframe_ENABLE | ENET_TX_Mode_STOREFORWARD \
                 | ENET_TX_Threshold_64BYTES | ENET_RX_Threshold_64BYTES \
                 | ENET_SECONDFRAME_OPT_DISABLE;
    ENET_DMA_CTL = reg_value;

    /* configure ENET_DMA_BCTL register */
    reg_value = ENET_DMA_BCTL;
    reg_value &= DMA_BCTL_MASK;
    reg_value = ENET_Address_ALIGN_ENABLE | ENET_ARBITRATION_RXTX_2_1 \
                | ENET_RXDP_32BEAT | ENET_PGBL_32BEAT | ENET_RXTX_DIFFERENT_PGBL \
                | ENET_FIXED_Burst_ENABLE | ENET_MIXED_Burst_DISABLE \
                | ENET_Normal_DESCRIPTOR;
    ENET_DMA_BCTL = reg_value;
}

#ifndef USE_DELAY
/*!
    简介:    insert a delay time
    参数[输入]:  ncount: 指定delay time length
    参数[输出]:  无
    参数[输出]:  无
*/
static void ENET_delay(uint32_t ncount) {
    __IO uint32_t delay_time = 0U;

    for(delay_time = ncount; delay_time != 0U; delay_time--) {
    }
}
#endif /* USE_DELAY */
