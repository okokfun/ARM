/**
  **************************************************************************
  * @file     at32f435_437_emac.h
  * @brief    at32f435_437 eth header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_EMAC_H
#define __AT32F435_437_EMAC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup EMAC
  * @{
  */
#define PHY_TIMEOUT                      (0x000FFFFF) /*!< timeout for phy response */

/** @defgroup EMAC_smi_Clock_border_definition
  * @brief emac smi clock border
  * @{
  */
#define EMAC_HCLK_BORDER_20MHZ           (20000000)   /*!< hclk boarder of 20 mhz */
#define EMAC_HCLK_BORDER_35MHZ           (35000000)   /*!< hclk boarder of 35 mhz */
#define EMAC_HCLK_BORDER_60MHZ           (60000000)   /*!< hclk boarder of 60 mhz */
#define EMAC_HCLK_BORDER_100MHZ          (100000000)  /*!< hclk boarder of 100 mhz */
#define EMAC_HCLK_BORDER_150MHZ          (150000000)  /*!< hclk boarder of 150 mhz */
#define EMAC_HCLK_BORDER_250MHZ          (250000000)  /*!< hclk boarder of 250 mhz */
#define EMAC_HCLK_BORDER_288MHZ          (288000000)  /*!< hclk boarder of 288 mhz */

/**
  * @}
  */

/** @defgroup EMAC_Interrupts_definition
  * @brief emac interrupts
  * @{
  */
#define EMAC_PMT_FLAG                    ((uint32_t)0x00000008) /*!< interrupt bit of pmt */
#define EMAC_MMC_FLAG                    ((uint32_t)0x00000010) /*!< interrupt bit of mmc */
#define EMAC_MMCR_FLAG                   ((uint32_t)0x00000020) /*!< interrupt bit of mmcr */
#define EMAC_MMCT_FLAG                   ((uint32_t)0x00000040) /*!< interrupt bit of mmct */
#define EMAC_TST_FLAG                    ((uint32_t)0x00000200) /*!< interrupt bit of tst */

/**
  * @}
  */

/** @defgroup EMAC_MMC_flags_definition
  * @brief emac mmc flags
  * @{
  */
#define MMC_RX_CRC_ERROR                 ((uint32_t)0x00000020) /*!< mmc error flag of rx crc */
#define MMC_RX_ALIGN_ERROR               ((uint32_t)0x00000040) /*!< mmc error flag of rx alignment */
#define MMC_RX_Good_UNICAST              ((uint32_t)0x00020000) /*!< mmc error flag of rx unicast good frames */
#define MMC_TX_Single_COL                ((uint32_t)0x00004000) /*!< mmc error flag of tx single collision */
#define MMC_TX_MULTIPLE_COL              ((uint32_t)0x00008000) /*!< mmc error flag of tx multiple collision */
#define MMC_TX_Good_FrameS               ((uint32_t)0x00200000) /*!< mmc error flag of tx good frames */

/**
  * @}
  */

/** @defgroup EMAC_Packet_definition
  * @brief emac packet
  * @{
  */
#define EMAC_MAX_Packet_LENGTH           1520 /*!< EMAC_header + EMAC_extra + EMAC_max_payload + EMAC_crc */
#define EMAC_HEADER                      14   /*!< 6 byte dest addr, 6 byte src addr, 2 byte length/ept_Type */
#define EMAC_CRC                         4    /*!< ethernet crc */
#define EMAC_EXTRA                       2    /*!< extra bytes in some cases */
#define VLAN_TAG                         4    /*!< optional 802.1q vlan tag */
#define EMAC_MIN_PAYLOAD                 46   /*!< minimum ethernet payload size */
#define EMAC_MAX_PAYLOAD                 1500 /*!< maximum ethernet payload size */
#define JUMBO_Frame_PAYLOAD              9000 /*!< jumbo frame payload size */
#define EMAC_DMARXDESC_Frame_LENGTHSHIFT 16

/**
  * @}
  */

/** @defgroup EMAC_DMA_Descriptor_tdes0_definition
  * @brief tdes0 definition
  * @{
  */
#define EMAC_DMATXDESC_OWN               ((uint32_t)0x80000000) /*!< own bit: descriptor is owned by dma engine */
#define EMAC_DMATXDESC_IC                ((uint32_t)0x40000000) /*!< interrupt on completion */
#define EMAC_DMATXDESC_LS                ((uint32_t)0x20000000) /*!< last segment */
#define EMAC_DMATXDESC_FS                ((uint32_t)0x10000000) /*!< first segment */
#define EMAC_DMATXDESC_DC                ((uint32_t)0x08000000) /*!< disable crc */
#define EMAC_DMATXDESC_DP                ((uint32_t)0x04000000) /*!< disable padding */
#define EMAC_DMATXDESC_TTSE              ((uint32_t)0x02000000) /*!< transmit time stamp enable */
#define EMAC_DMATXDESC_CIC               ((uint32_t)0x00C00000) /*!< checksum insertion control: 4 cases */
#define EMAC_DMATXDESC_CIC_ByPass        ((uint32_t)0x00000000) /*!< do nothing: checksum engine is bypassed */
#define EMAC_DMATXDESC_CIC_IPV4HEADER    ((uint32_t)0x00400000) /*!< ipv4 header checksum insertion */
#define EMAC_DMATXDESC_CIC_TUI_SEG       ((uint32_t)0x00800000) /*!< tcp/udp/icmp checksum insertion calculated over segment only */
#define EMAC_DMATXDESC_CIC_TUI_FULL      ((uint32_t)0x00C00000) /*!< tcp/udp/icmp checksum insertion fully calculated */
#define EMAC_DMATXDESC_TER               ((uint32_t)0x00200000) /*!< transmit end of ring */
#define EMAC_DMATXDESC_TCH               ((uint32_t)0x00100000) /*!< second address chained */
#define EMAC_DMATXDESC_TTSS              ((uint32_t)0x00020000) /*!< tx time stamp status */
#define EMAC_DMATXDESC_IHE               ((uint32_t)0x00010000) /*!< ip header error */
#define EMAC_DMATXDESC_ES                ((uint32_t)0x00008000) /*!< error summary: or of the following bits: ue || ED || EC || LCO || NC || LCA || FF || JT */
#define EMAC_DMATXDESC_JT                ((uint32_t)0x00004000) /*!< jabber timeout */
#define EMAC_DMATXDESC_FF                ((uint32_t)0x00002000) /*!< frame flushed: dma/mtl flushed the frame due to SW flush */
#define EMAC_DMATXDESC_PCE               ((uint32_t)0x00001000) /*!< payload checksum error */
#define EMAC_DMATXDESC_LCA               ((uint32_t)0x00000800) /*!< loss of carrier: carrier lost during tramsmission */
#define EMAC_DMATXDESC_NC                ((uint32_t)0x00000400) /*!< no carrier: no carrier signal from the tranceiver */
#define EMAC_DMATXDESC_LCO               ((uint32_t)0x00000200) /*!< late collision: transmission aborted due to collision */
#define EMAC_DMATXDESC_EC                ((uint32_t)0x00000100) /*!< excessive collision: transmission aborted after 16 collisions */
#define EMAC_DMATXDESC_VF                ((uint32_t)0x00000080) /*!< vlan frame */
#define EMAC_DMATXDESC_CC                ((uint32_t)0x00000078) /*!< collision count */
#define EMAC_DMATXDESC_ED                ((uint32_t)0x00000004) /*!< excessive deferral */
#define EMAC_DMATXDESC_UF                ((uint32_t)0x00000002) /*!< underflow error: late data arrival from the memory */
#define EMAC_DMATXDESC_DB                ((uint32_t)0x00000001) /*!< deferred bit */

/**
  * @}
  */

/** @defgroup EMAC_DMA_Descriptor_tdes1_definition
  * @brief  tdes1 descriptor
  * @{
  */
#define EMAC_DMATXDESC_TBS2              ((uint32_t)0x1FFF0000) /*!< transmit buffer2 size */
#define EMAC_DMATXDESC_TBS1              ((uint32_t)0x00001FFF) /*!< transmit buffer1 size */

/**
  * @}
  */

/** @defgroup EMAC_DMA_Descriptor_tdes2_definition
  * @brief  tdes2 descriptor
  * @{
  */
#define EMAC_DMATXDESC_B1AP              ((uint32_t)0xFFFFFFFF) /*!< buffer1 address pointer */

/**
  * @}
  */

/** @defgroup EMAC_DMA_Descriptor_tdes3_definition
  * @brief  tdes3 descriptor
  * @{
  */
#define EMAC_DMATxDesc_B2AP              ((uint32_t)0xFFFFFFFF) /*!< buffer2 address pointer */

/**
  * @}
  */

/** @defgroup EMAC_DMA_Descriptor_rdes0_definition
  * @brief  rdes0 descriptor
  * @{
  */
#define EMAC_DMARXDESC_OWN               ((uint32_t)0x80000000) /*!< own bit: descriptor is owned by dma engine  */
#define EMAC_DMARXDESC_AFM               ((uint32_t)0x40000000) /*!< da filter fail for the rx frame  */
#define EMAC_DMARXDESC_FL                ((uint32_t)0x3FFF0000) /*!< receive descriptor frame length  */
#define EMAC_DMARXDESC_ES                ((uint32_t)0x00008000) /*!< error summary: or of the following bits: de || OE || IPC || LC || RWT || RE || CE */
#define EMAC_DMARXDESC_DE                ((uint32_t)0x00004000) /*!< desciptor error: no more descriptors for receive frame  */
#define EMAC_DMARXDESC_SAF               ((uint32_t)0x00002000) /*!< sa filter fail for the received frame */
#define EMAC_DMARXDESC_LE                ((uint32_t)0x00001000) /*!< frame size not matching with length field */
#define EMAC_DMARXDESC_OE                ((uint32_t)0x00000800) /*!< overflow error: frame was damaged due to buffer overflow */
#define EMAC_DMARXDESC_VLAN              ((uint32_t)0x00000400) /*!< vlan tag: received frame is a vlan frame */
#define EMAC_DMARXDESC_FS                ((uint32_t)0x00000200) /*!< first descriptor of the frame  */
#define EMAC_DMARXDESC_LS                ((uint32_t)0x00000100) /*!< last descriptor of the frame  */
#define EMAC_DMARXDESC_IPV4HCE           ((uint32_t)0x00000080) /*!< ipc checksum error: rx ipv4 header checksum error   */
#define EMAC_DMARXDESC_LC                ((uint32_t)0x00000040) /*!< late collision occurred during reception   */
#define EMAC_DMARXDESC_FT                ((uint32_t)0x00000020) /*!< frame ept_Type - ethernet, otherwise 802.3    */
#define EMAC_DMARXDESC_RWT               ((uint32_t)0x00000010) /*!< receive watchdog timeout: watchdog timer expired during reception    */
#define EMAC_DMARXDESC_RE                ((uint32_t)0x00000008) /*!< receive error: error reported by mii interface  */
#define EMAC_DMARXDESC_DBE               ((uint32_t)0x00000004) /*!< dribble bit error: frame contains non int multiple of 8 bits  */
#define EMAC_DMARXDESC_CE                ((uint32_t)0x00000002) /*!< crc error */
#define EMAC_DMARXDESC_MAMPCE            ((uint32_t)0x00000001) /*!< rx mac address/payload checksum error: rx mac address matched/ Rx Payload Checksum Error */

/**
  * @}
  */

/** @defgroup EMAC_DMA_Descriptor_rdes1_definition
  * @brief  rdes1 descriptor
  * @{
  */
#define EMAC_DMARXDESC_DIC               ((uint32_t)0x80000000) /*!< disable interrupt on completion */
#define EMAC_DMARXDESC_RBS2              ((uint32_t)0x1FFF0000) /*!< receive buffer2 size */
#define EMAC_DMARXDESC_RER               ((uint32_t)0x00008000) /*!< receive end of ring */
#define EMAC_DMARXDESC_RCH               ((uint32_t)0x00004000) /*!< second address chained */
#define EMAC_DMARXDESC_RBS1              ((uint32_t)0x00001FFF) /*!< receive buffer1 size */

/**
  * @}
  */

/** @defgroup EMAC_DMA_Descriptor_rdes2_definition
  * @brief  rdes2 descriptor
  * @{
  */
#define EMAC_DMARXDESC_B1AP              ((uint32_t)0xFFFFFFFF) /*!< buffer1 address pointer */

/**
  * @}
  */

/** @defgroup EMAC_DMA_Descriptor_rdes3_definition
  * @brief  rdes3 descriptor
  * @{
  */
#define EMAC_DMARXDESC_B2AP              ((uint32_t)0xFFFFFFFF) /*!< buffer2 address pointer */

/**
  * @}
  */

/**
  * @brief  emac dma flag
  */
#define EMAC_DMA_Ti_FLAG                 ((uint32_t)0x00000001) /*!< emac dma transmit 中断 */
#define EMAC_DMA_TPS_FLAG                ((uint32_t)0x00000002) /*!< emac dma transmit process stopped */
#define EMAC_DMA_TBU_FLAG                ((uint32_t)0x00000004) /*!< emac dma transmit buffer unavailable */
#define EMAC_DMA_TJT_FLAG                ((uint32_t)0x00000008) /*!< emac dma transmit jabber timeout */
#define EMAC_DMA_OVF_FLAG                ((uint32_t)0x00000010) /*!< emac dma receive overflow */
#define EMAC_DMA_UNF_FLAG                ((uint32_t)0x00000020) /*!< emac dma transmit underflow */
#define EMAC_DMA_RI_FLAG                 ((uint32_t)0x00000040) /*!< emac dma receive 中断 */
#define EMAC_DMA_RBU_FLAG                ((uint32_t)0x00000080) /*!< emac dma receive buffer unavailable */
#define EMAC_DMA_RPS_FLAG                ((uint32_t)0x00000100) /*!< emac dma receive process stopped */
#define EMAC_DMA_RWT_FLAG                ((uint32_t)0x00000200) /*!< emac dma receive watchdog timeout */
#define EMAC_DMA_ETI_FLAG                ((uint32_t)0x00000400) /*!< emac dma early transmit 中断 */
#define EMAC_DMA_FBEI_FLAG               ((uint32_t)0x00002000) /*!< emac dma fatal bus error 中断 */
#define EMAC_DMA_ERI_FLAG                ((uint32_t)0x00004000) /*!< emac dma early receive 中断 */
#define EMAC_DMA_AIS_FLAG                ((uint32_t)0x00008000) /*!< emac dma abnormal interrupt summary */
#define EMAC_DMA_NIS_FLAG                ((uint32_t)0x00010000) /*!< emac dma normal interrupt summary */

/** @defgroup EMAC_exported_Types
  * @{
  */

/**
  * @brief  emac auto negotiation type
  */
typedef enum {
    EMAC_Auto_NEGOTIATION_OFF              = 0x00, /*!< disable auto negotiation */
    EMAC_Auto_NEGOTIATION_ON               = 0x01  /*!< enable auto negotiation */
} EMAC_Auto_negotiation_Type;

/**
  * @brief  emac back_off limit type
  */
typedef enum {
    EMAC_BackOff_Limit_0                   = 0x00, /*!< retransmission clock gap numbers betwenn n and 10 */
    EMAC_BackOff_Limit_1                   = 0x01, /*!< retransmission clock gap numbers betwenn n and 8 */
    EMAC_BackOff_Limit_2                   = 0x02, /*!< retransmission clock gap numbers betwenn n and 4 */
    EMAC_BackOff_Limit_3                   = 0x03  /*!< retransmission clock gap numbers betwenn n and 1 */
} EMAC_bol_Type;

/**
  * @brief  emac duplex type
  */
typedef enum {
    EMAC_Half_DUPLEX                       = 0x00, /*!< half duplex */
    EMAC_FULL_DUPLEX                       = 0x01  /*!< full duplex */
} EMAC_Duplex_Type;

/**
  * @brief  emac speed type
  */
typedef enum {
    EMAC_SPEED_10MBPS                      = 0x00, /*!< 10 mbps */
    EMAC_SPEED_100MBPS                     = 0x01  /*!< 100 mbps */
} EMAC_Speed_Type;

/**
  * @brief  emac interframe gap type
  */
typedef enum {
    EMAC_INTERFRAME_Gap_96BIT              = 0x00, /*!< 96-bit numbers between two frames */
    EMAC_INTERFRAME_Gap_88BIT              = 0x01, /*!< 88-bit numbers between two frames */
    EMAC_INTERFRAME_Gap_80BIT              = 0x02, /*!< 80-bit numbers between two frames */
    EMAC_INTERFRAME_Gap_72BIT              = 0x03, /*!< 72-bit numbers between two frames */
    EMAC_INTERFRAME_Gap_64BIT              = 0x04, /*!< 64-bit numbers between two frames */
    EMAC_INTERFRAME_Gap_56BIT              = 0x05, /*!< 56-bit numbers between two frames */
    EMAC_INTERFRAME_Gap_48BIT              = 0x06, /*!< 48-bit numbers between two frames */
    EMAC_INTERFRAME_Gap_40BIT              = 0x07  /*!< 40-bit numbers between two frames */
} EMAC_intergrame_Gap_Type;

/**
  * @brief  mdc clock range type
  */
typedef enum {
    EMAC_Clock_Range_60_To_100             = 0x00, /*!< mdc is hclk/42 */
    EMAC_Clock_Range_100_To_150            = 0x01, /*!< mdc is hclk/62 */
    EMAC_Clock_Range_20_To_35              = 0x02, /*!< mdc is hclk/16 */
    EMAC_Clock_Range_35_To_60              = 0x03, /*!< mdc is hclk/26 */
    EMAC_Clock_Range_150_To_250            = 0x04, /*!< mdc is hclk/102 */
    EMAC_Clock_Range_250_To_288            = 0x05  /*!< mdc is hclk/102 */
} EMAC_Clock_Range_Type;

/**
  * @brief  emac control frames filter type
  */
typedef enum {
    EMAC_Control_Frame_PASSING_NO          = 0x00, /*!< don't pass any control frame to application */
    EMAC_Control_Frame_PASSING_ALL         = 0x02, /*!< pass all control frames to application */
    EMAC_Control_Frame_PASSING_MATCH       = 0x03  /*!< only pass filtered control frames to application */
} EMAC_Control_Frames_Filter_Type;

/**
  * @brief  pause threshold type
  */
typedef enum {
    EMAC_Pause_4_SLOT_TIME                 = 0x00, /*!< pause time is 4 slot time */
    EMAC_Pause_28_SLOT_TIME                = 0x01, /*!< pause time is 28 slot time */
    EMAC_Pause_144_SLOT_TIME               = 0x02, /*!< pause time is 144 slot time */
    EMAC_Pause_256_SLOT_TIME               = 0x03  /*!< pause time is 256 slot time */
} EMAC_Pause_slot_Threshold_Type;

/**
  * @brief  interrupt mask type
  */
typedef enum {
    EMAC_Interrupt_PMT_MASK                = 0x00, /*!< mask pmt 中断 */
    EMAC_Interrupt_TST_MASK                = 0x01  /*!< mask tst 中断 */
} EMAC_Interrupt_Mask_Type;

/**
  * @brief  mac address type
  */
typedef enum {
    EMAC_Address_Filter_1                  = 0x01, /*!< mac address 1 filter */
    EMAC_Address_Filter_2                  = 0x02, /*!< mac address 2 filter */
    EMAC_Address_Filter_3                  = 0x03  /*!< mac address 3 filter */
} EMAC_Address_Type;

/**
  * @brief  address filter type
  */
typedef enum {
    EMAC_DESTINATION_FILTER                = 0x00, /*!< destination mac address filter */
    EMAC_Source_FILTER                     = 0x01  /*!< source mac address filter */
} EMAC_Address_Filter_Type;

/**
  * @brief  address mask type
  */
typedef enum {
    EMAC_Address_Mask_8L0                  = 0x01, /*!< byte 0 of mac address low register */
    EMAC_Address_Mask_15L8                 = 0x02, /*!< byte 1 of mac address low register */
    EMAC_Address_Mask_23L16                = 0x04, /*!< byte 2 of mac address low register */
    EMAC_Address_Mask_31L24                = 0x08, /*!< byte 3 of mac address low register */
    EMAC_Address_Mask_7H0                  = 0x10, /*!< byte 0 of mac address high register */
    EMAC_Address_Mask_15H8                 = 0x20  /*!< byte 1 of mac address high register */
} EMAC_Address_Mask_Type;

/**
  * @brief  rx tx priority ratio type
  */
typedef enum {
    EMAC_DMA_1_RX_1_TX                     = 0x00, /*!< rx/tx ratio is 1:1 */
    EMAC_DMA_2_RX_1_TX                     = 0x01, /*!< rx/tx ratio is 2:1 */
    EMAC_DMA_3_RX_1_TX                     = 0x02, /*!< rx/tx ratio is 3:1 */
    EMAC_DMA_4_RX_1_TX                     = 0x03  /*!< rx/tx ratio is 4:1 */
} EMAC_DMA_RX_TX_Ratio_Type;

/**
  * @brief  programmable burst length
  */
typedef enum {
    EMAC_DMA_PBL_1                         = 0x01, /*!< maximum 1 time of beats to be transferred in one dma transaction */
    EMAC_DMA_PBL_2                         = 0x02, /*!< maximum 2 times of beats to be transferred in one dma transaction */
    EMAC_DMA_PBL_4                         = 0x04, /*!< maximum 4 times of beats to be transferred in one dma transaction */
    EMAC_DMA_PBL_8                         = 0x08, /*!< maximum 8 times of beats to be transferred in one dma transaction */
    EMAC_DMA_PBL_16                        = 0x10, /*!< maximum 16 times of beats to be transferred in one dma transaction */
    EMAC_DMA_PBL_32                        = 0x20  /*!< maximum 32 times of beats to be transferred in one dma transaction */
} EMAC_DMA_pbl_Type;

/**
  * @brief  dma tx rx type
  */
typedef enum {
    EMAC_DMA_Transmit                      = 0x00, /*!< transmit dma */
    EMAC_DMA_Receive                       = 0x01  /*!< receive dma */
} EMAC_DMA_TX_RX_Type;

/**
  * @brief  dma receive process status type
  */
typedef enum {
    EMAC_DMA_RX_Reset_Stop_COMMAND         = 0x00, /*!< receive reset or stop command */
    EMAC_DMA_RX_FETCH_DESCRIPTOR           = 0x01, /*!< rx dma is fetching descriptor */
    EMAC_DMA_RX_WaitING_Packet             = 0x03, /*!< rx dma is waiting for packets */
    EMAC_DMA_RX_DESCRIPTOR_UNAVAILABLE     = 0x04, /*!< rx dma descriptor is unavailable */
    EMAC_DMA_RX_Close_DESCRIPTOR           = 0x05, /*!< rx dma is closing descriptor */
    EMAC_DMA_RX_FIFO_To_HOST               = 0x07  /*!< rx dma is transferring data from fifo to host */
} EMAC_DMA_Receive_Process_Status_Type;

/**
  * @brief  dma transmit process status type
  */
typedef enum {
    EMAC_DMA_TX_Reset_Stop_COMMAND         = 0x00, /*!< receive reset or stop command */
    EMAC_DMA_TX_FETCH_DESCRIPTOR           = 0x01, /*!< tx dma is fetching descriptor */
    EMAC_DMA_TX_WaitING_FOR_STATUS         = 0x02, /*!< tx dma is waiting for status message */
    EMAC_DMA_TX_HOST_To_FIFO               = 0x03, /*!< tx dma is reading data from host and forward data to fifo */
    EMAC_DMA_TX_DESCRIPTOR_UNAVAILABLE     = 0x06, /*!< tx dma is unavailable or fifo underflow */
    EMAC_DMA_TX_Close_DESCRIPTOR           = 0x07  /*!< tx dma is closing descriptor */
} EMAC_DMA_Transmit_Process_Status_Type;

/**
  * @brief  dma operations type
  */
typedef enum {
    EMAC_DMA_OPS_Start_Stop_Receive        = 0x00, /*!< start/stop receive */
    EMAC_DMA_OPS_Second_Frame              = 0x01, /*!< operate on second frame */
    EMAC_DMA_OPS_FORWARD_UNDERSIZED        = 0x02, /*!< forward undersized good frames*/
    EMAC_DMA_OPS_FORWARD_ERROR             = 0x03, /*!< forward error frames */
    EMAC_DMA_OPS_Start_Stop_Transmit       = 0x04, /*!< start/stop transmission */
    EMAC_DMA_OPS_Flush_Transmit_FIFO       = 0x05, /*!< flush transmit fifo */
    EMAC_DMA_OPS_Transmit_STORE_FORWARD    = 0x06, /*!< transmit store and forward */
    EMAC_DMA_OPS_Receive_Flush_Disable     = 0x07, /*!< disable flushing of received frames */
    EMAC_DMA_OPS_Receive_STORE_FORWARD     = 0x08, /*!< receive store and forward */
    EMAC_DMA_OPS_DROP_Error_Disable        = 0x09  /*!< disbale dropping of tcp/ip checksum error frames */
} EMAC_DMA_Operations_Type;

/**
  * @brief  receive threshold control type
  */
typedef enum {
    EMAC_DMA_RX_Threshold_64_BYTES         = 0x00, /*!< receive starts when the frame size within the receiv fifo is larger than 64 bytes */
    EMAC_DMA_RX_Threshold_32_BYTES         = 0x01, /*!< receive starts when the frame size within the receiv fifo is larger than 32 bytes */
    EMAC_DMA_RX_Threshold_96_BYTES         = 0x02, /*!< receive starts when the frame size within the receiv fifo is larger than 96 bytes */
    EMAC_DMA_RX_Threshold_128_BYTES        = 0x03  /*!< receive starts when the frame size within the receiv fifo is larger than 128 bytes */
} EMAC_DMA_Receive_Threshold_Type;

/**
  * @brief  transmit threshold control type
  */
typedef enum {
    EMAC_DMA_TX_Threshold_64_BYTES         = 0x00, /*!< transmission starts when the frame size within the transmit FIFO is larger than 64 bytes */
    EMAC_DMA_TX_Threshold_128_BYTES        = 0x01, /*!< transmission starts when the frame size within the transmit FIFO is larger than 128 bytes */
    EMAC_DMA_TX_Threshold_192_BYTES        = 0x02, /*!< transmission starts when the frame size within the transmit FIFO is larger than 192 bytes */
    EMAC_DMA_TX_Threshold_256_BYTES        = 0x03, /*!< transmission starts when the frame size within the transmit FIFO is larger than 256 bytes */
    EMAC_DMA_TX_Threshold_40_BYTES         = 0x04, /*!< transmission starts when the frame size within the transmit FIFO is larger than 40 bytes */
    EMAC_DMA_TX_Threshold_32_BYTES         = 0x05, /*!< transmission starts when the frame size within the transmit FIFO is larger than 32 bytes */
    EMAC_DMA_TX_Threshold_24_BYTES         = 0x06, /*!< transmission starts when the frame size within the transmit FIFO is larger than 24 bytes */
    EMAC_DMA_TX_Threshold_16_BYTES         = 0x07  /*!< transmission starts when the frame size within the transmit FIFO is larger than 16 bytes */
} EMAC_DMA_Transmit_Threshold_Type;

/**
  * @brief  dma interrupt type
  */
typedef enum {
    EMAC_DMA_Interrupt_TX                  = 0x00, /*!< transmit 中断 */
    EMAC_DMA_Interrupt_TX_STOP             = 0x01, /*!< transmit process stopped 中断 */
    EMAC_DMA_Interrupt_TX_UNAVAILABLE      = 0x02, /*!< transmit buffer unavailable 中断 */
    EMAC_DMA_Interrupt_TX_JABBER           = 0x03, /*!< transmit jabber timeout 中断 */
    EMAC_DMA_Interrupt_RX_OVERFLOW         = 0x04, /*!< receive overflow 中断 */
    EMAC_DMA_Interrupt_TX_UNDERFLOW        = 0x05, /*!< transmit underflow 中断 */
    EMAC_DMA_Interrupt_RX                  = 0x06, /*!< receive 中断 */
    EMAC_DMA_Interrupt_RX_UNAVAILABLE      = 0x07, /*!< receive buffer unavailable 中断 */
    EMAC_DMA_Interrupt_RX_STOP             = 0x08, /*!< receive process stopped 中断 */
    EMAC_DMA_Interrupt_RX_TIMEOUT          = 0x09, /*!< receive watchdog timeout 中断 */
    EMAC_DMA_Interrupt_TX_EARLY            = 0x0A, /*!< early transmit 中断 */
    EMAC_DMA_Interrupt_FATAL_Bus_ERROR     = 0x0B, /*!< fatal bus error 中断 */
    EMAC_DMA_Interrupt_RX_EARLY            = 0x0C, /*!< early receive 中断 */
    EMAC_DMA_Interrupt_ABNORMAL_SUMMARY    = 0x0D, /*!< abnormal interrupt summary */
    EMAC_DMA_Interrupt_NORMAL_SUMMARY      = 0x0E  /*!< normal interrupt summary */
} EMAC_DMA_Interrupt_Type;

/**
  * @brief  dma tansfer address type
  */
typedef enum {
    EMAC_DMA_TX_DESCRIPTOR                 = 0x00, /*!< transmit descriptor address */
    EMAC_DMA_RX_DESCRIPTOR                 = 0x01, /*!< receive descriptor address */
    EMAC_DMA_TX_BUFFER                     = 0x02, /*!< transmit buffer address */
    EMAC_DMA_RX_BUFFER                     = 0x03  /*!< receive buffer address */
} EMAC_DMA_Transfer_Address_Type;

/**
  * @brief  clock node type
  */
typedef enum {
    EMAC_PTP_NORMAL_CLOCK                  = 0x00, /*!< normal clock node */
    EMAC_PTP_BOUNDARY_CLOCK                = 0x01, /*!< boundary clock node */
    EMAC_PTP_End_To_End_CLOCK              = 0x02, /*!< end to end transparent clock node */
    EMAC_PTP_PEER_To_PEER_CLOCK            = 0x03  /*!< peer to peer transparent clock node */
} EMAC_PTP_Clock_Node_Type;

/**
  * @brief  time stamp status type
  */
typedef enum {
    EMAC_PTP_Second_OVERFLOW               = 0x00, /*!< time stamp second overflow */
    EMAC_PTP_Target_Time_REACH             = 0x01  /*!< time stamp target time reached */
} EMAC_PTP_TimeStamp_Status_Type;

/**
  * @brief  pps control type
  */
typedef enum {
    EMAC_PTP_PPS_1HZ                       = 0x00, /*!< pps frequency is 1 hz */
    EMAC_PTP_PPS_2HZ                       = 0x01, /*!< pps frequency is 2 hz */
    EMAC_PTP_PPS_4HZ                       = 0x02, /*!< pps frequency is 4 hz */
    EMAC_PTP_PPS_8HZ                       = 0x03, /*!< pps frequency is 8 hz */
    EMAC_PTP_PPS_16HZ                      = 0x04, /*!< pps frequency is 16 hz */
    EMAC_PTP_PPS_32HZ                      = 0x05, /*!< pps frequency is 32 hz */
    EMAC_PTP_PPS_64HZ                      = 0x06, /*!< pps frequency is 64 hz */
    EMAC_PTP_PPS_128HZ                     = 0x07, /*!< pps frequency is 128 hz */
    EMAC_PTP_PPS_256HZ                     = 0x08, /*!< pps frequency is 256 hz */
    EMAC_PTP_PPS_512HZ                     = 0x09, /*!< pps frequency is 512 hz */
    EMAC_PTP_PPS_1024HZ                    = 0x0A, /*!< pps frequency is 1024 hz */
    EMAC_PTP_PPS_2048HZ                    = 0x0B, /*!< pps frequency is 2048 hz */
    EMAC_PTP_PPS_4096HZ                    = 0x0C, /*!< pps frequency is 4096 hz */
    EMAC_PTP_PPS_8192HZ                    = 0x0D, /*!< pps frequency is 8192 hz */
    EMAC_PTP_PPS_16384HZ                   = 0x0E, /*!< pps frequency is 16384 hz */
    EMAC_PTP_PPS_32768HZ                   = 0x0F  /*!< pps frequency is 32768 hz */
} EMAC_PTP_PPS_Control_Type;

/**
  * @brief  ethernet mac control config type
  */
typedef struct {
    EMAC_Auto_negotiation_Type             auto_nego;             /*!< auto negotiatin enable */
    confirm_state                          deferral_check;        /*!< deferral check enable */
    EMAC_bol_Type                          back_off_limit;        /*!< back-off limit setting */
    confirm_state                          auto_pad_CRC_strip;    /*!< automtic pad/crc stripping enable */
    confirm_state                          retry_Disable;         /*!< retry disable*/
    confirm_state                          ipv4_checksum_offload; /*!< ipv4 checksum offload enable */
    EMAC_Duplex_Type                       duplex_Mode;           /*!< duplex mode enable */
    confirm_state                          loopback_Mode;         /*!< loopback mode enable */
    confirm_state                          receive_Own_Disable;   /*!< receive own disbale */
    EMAC_Speed_Type                        fast_ethernet_speed;   /*!< fast ethernet speed enable */
    confirm_state                          carrier_Sense_Disable; /*!< carrier sense disable*/
    EMAC_intergrame_Gap_Type               interframe_gap;        /*!< set interframe gap */
    confirm_state                          jabber_Disable;        /*!< jabber disbale */
    confirm_state                          watchdog_Disable;      /*!< watchdog disable */
} EMAC_Control_Config_Type;

/**
  * @brief  ethernet mac dma config type
  */
typedef struct {
    confirm_state                          aab_Enable;        /*!< address-aligned beats enable */
    confirm_state                          usp_Enable;        /*!< separate PBL enable */
    EMAC_DMA_pbl_Type                      rx_DMA_pal;        /*!< rx dma pbl */
    confirm_state                          fb_Enable;         /*!< separate PBL enable */
    EMAC_DMA_pbl_Type                      tx_DMA_pal;        /*!< tx dma pbl */
    uint8_t                                desc_Skip_length;  /*!< descriptor skip length */
    confirm_state                          da_Enable;         /*!< dma arbitration enable */
    EMAC_DMA_RX_TX_Ratio_Type              priority_ratio;    /*!< priority ratio */
    confirm_state                          dt_Disable;        /*!< disable dropping of tcp/ip checksum error frames */
    confirm_state                          rsf_Enable;        /*!< enable receiving store or forward */
    confirm_state                          flush_RX_Disable;  /*!< disable flushing of received frames */
    confirm_state                          tsf_Enable;        /*!< enable transmitting store or forward */
    EMAC_DMA_Transmit_Threshold_Type       tx_threshold;      /*!< transmit threshold control */
    confirm_state                          fef_Enable;        /*!< enable forward error frames */
    confirm_state                          fugf_Enable;       /*!< enable forward undersized good frames */
    EMAC_DMA_Receive_Threshold_Type        rx_threshold;      /*!< receive threshold control */
    confirm_state                          osf_Enable;        /*!< enable operating on second frames */
} EMAC_DMA_Config_Type;

/**
  * @brief  dma desciptors data structure definition
  */
typedef struct  {
    uint32_t   status;                /*!< status */
    uint32_t   controlsize;           /*!< control and buffer1, buffer2 lengths */
    uint32_t   buf1addr;              /*!< buffer1 address pointer */
    uint32_t   buf2nextdescaddr;      /*!< buffer2 or next descriptor address pointer */
} EMAC_DMA_Desc_Type;

/**
  * @brief type define emac mac register all
  */
typedef struct {
    /**
      * @brief emac mac ctrl register, offset:0x00
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t reserved1            : 2; /* [0:1] */
            __IO uint32_t re                   : 1; /* [2] */
            __IO uint32_t te                   : 1; /* [3] */
            __IO uint32_t dc                   : 1; /* [4] */
            __IO uint32_t bl                   : 2; /* [5:6] */
            __IO uint32_t acs                  : 1; /* [7] */
            __IO uint32_t reserved2            : 1; /* [8] */
            __IO uint32_t dr                   : 1; /* [9] */
            __IO uint32_t ipc                  : 1; /* [10] */
            __IO uint32_t dm                   : 1; /* [11] */
            __IO uint32_t lm                   : 1; /* [12] */
            __IO uint32_t dro                  : 1; /* [13] */
            __IO uint32_t fes                  : 1; /* [14] */
            __IO uint32_t reserved3            : 1; /* [15] */
            __IO uint32_t dcs                  : 1; /* [16] */
            __IO uint32_t ifg                  : 3; /* [17:19] */
            __IO uint32_t reserved4            : 2; /* [20:21] */
            __IO uint32_t jd                   : 1; /* [22] */
            __IO uint32_t wd                   : 1; /* [23] */
            __IO uint32_t reserved5            : 8; /* [24:31] */
        } ctrl_bit;
    };

    /**
      * @brief emac mac frmf register, offset:0x04
      */
    union {
        __IO uint32_t frmf;
        struct {
            __IO uint32_t pr                   : 1; /* [0] */
            __IO uint32_t huc                  : 1; /* [1] */
            __IO uint32_t hmc                  : 1; /* [2] */
            __IO uint32_t daif                 : 1; /* [3] */
            __IO uint32_t pmc                  : 1; /* [4] */
            __IO uint32_t dbf                  : 1; /* [5] */
            __IO uint32_t pcf                  : 2; /* [6:7] */
            __IO uint32_t saif                 : 1; /* [8] */
            __IO uint32_t saf                  : 1; /* [9] */
            __IO uint32_t hpf                  : 1; /* [10] */
            __IO uint32_t reserved1            : 20;/* [11:30] */
            __IO uint32_t ra                   : 1; /* [31] */
        } frmf_bit;
    };

    /**
      * @brief emac mac hth register, offset:0x08
      */
    union {
        __IO uint32_t hth;
        struct {
            __IO uint32_t hth                  : 32; /* [0:31] */
        } hth_bit;
    };

    /**
      * @brief emac mac htl register, offset:0x0c
      */
    union {
        __IO uint32_t htl;
        struct {
            __IO uint32_t htl                  : 32; /* [0:31] */
        } htl_bit;
    };

    /**
      * @brief emac mac miiaddr register, offset:0x10
      */
    union {
        __IO uint32_t miiaddr;
        struct {
            __IO uint32_t mb                   : 1; /* [0] */
            __IO uint32_t mw                   : 1; /* [1] */
            __IO uint32_t cr                   : 4; /* [2:5] */
            __IO uint32_t mii                  : 5; /* [6:10] */
            __IO uint32_t pa                   : 5; /* [11:15] */
            __IO uint32_t reserved1            : 16;/* [16:31] */
        } miiaddr_bit;
    };

    /**
      * @brief emac mac miidt register, offset:0x14
      */
    union {
        __IO uint32_t miidt;
        struct {
            __IO uint32_t md                   : 16;/* [0:15] */
            __IO uint32_t reserved1            : 16;/* [16:31] */
        } miidt_bit;
    };

    /**
      * @brief emac mac fctrl register, offset:0x18
      */
    union {
        __IO uint32_t fctrl;
        struct {
            __IO uint32_t fcbbpa               : 1; /* [0] */
            __IO uint32_t etf                  : 1; /* [1] */
            __IO uint32_t erf                  : 1; /* [2] */
            __IO uint32_t dup                  : 1; /* [3] */
            __IO uint32_t plt                  : 2; /* [4:5] */
            __IO uint32_t reserved1            : 1; /* [6] */
            __IO uint32_t dzqp                 : 1; /* [7] */
            __IO uint32_t reserved2            : 8; /* [8:15] */
            __IO uint32_t pt                   : 16;/* [16:31] */
        } fctrl_bit;
    };

    /**
      * @brief emac mac vlt register, offset:0x1C
      */
    union {
        __IO uint32_t vlt;
        struct {
            __IO uint32_t vti                  : 16;/* [0:15] */
            __IO uint32_t etv                  : 1; /* [16] */
            __IO uint32_t reserved1            : 15;/* [17:31] */
        } vlt_bit;
    };

    /**
      * @brief emac mac reserved1 register, offset:0x20~0x24
      */
    __IO uint32_t reserved1[2];

    /**
      * @brief emac mac rwff register, offset:0x28
      */
    __IO uint32_t rwff;

    /**
      * @brief emac mac pmtctrlsts register, offset:0x2C
      */
    union {
        __IO uint32_t pmtctrlsts;
        struct {
            __IO uint32_t pd                   : 1; /* [0] */
            __IO uint32_t emp                  : 1; /* [1] */
            __IO uint32_t erwf                 : 1; /* [2] */
            __IO uint32_t reserved1            : 2; /* [3:4] */
            __IO uint32_t rmp                  : 1; /* [5] */
            __IO uint32_t rrwf                 : 1; /* [6] */
            __IO uint32_t reserved2            : 2; /* [7:8] */
            __IO uint32_t guc                  : 1; /* [9] */
            __IO uint32_t reserved3            : 21;/* [10:30] */
            __IO uint32_t rwffpr               : 1; /* [31] */
        } pmtctrlsts_bit;
    };

    /**
      * @brief emac mac reserved2 register, offset:0x30~0x34
      */
    __IO uint32_t reserved2[2];

    /**
      * @brief emac mac ists register, offset:0x38
      */
    union {
        __IO uint32_t ists;
        struct {
            __IO uint32_t reserved1            : 3; /* [0:2] */
            __IO uint32_t pis                  : 1; /* [3] */
            __IO uint32_t mis                  : 1; /* [4] */
            __IO uint32_t mris                 : 1; /* [5] */
            __IO uint32_t mtis                 : 1; /* [6] */
            __IO uint32_t reserved2            : 2; /* [7:8] */
            __IO uint32_t tis                  : 1; /* [9] */
            __IO uint32_t reserved3            : 22;/* [10:31] */
        } ists_bit;
    };

    /**
      * @brief emac mac imr register, offset:0x3C
      */
    union {
        __IO uint32_t imr;
        struct {
            __IO uint32_t reserved1            : 3; /* [0:2] */
            __IO uint32_t pim                  : 1; /* [3] */
            __IO uint32_t reserved2            : 5; /* [4:8] */
            __IO uint32_t tim                  : 1; /* [9] */
            __IO uint32_t reserved3            : 22;/* [10:31] */
        } imr_bit;
    };

    /**
      * @brief emac mac a0h register, offset:0x40
      */
    union {
        __IO uint32_t a0h;
        struct {
            __IO uint32_t ma0h                 : 16;/* [0:15] */
            __IO uint32_t reserved1            : 15;/* [16:30] */
            __IO uint32_t ae                   : 1; /* [31] */
        } a0h_bit;
    };

    /**
     * @brief emac mac a0l register, offset:0x44
     */
    union {
        __IO uint32_t a0l;
        struct {
            __IO uint32_t ma0l                 : 32;/* [0:31] */
        } a0l_bit;
    };

    /**
      * @brief emac mac a1h register, offset:0x48
      */
    union {
        __IO uint32_t a1h;
        struct {
            __IO uint32_t ma1h                 : 16;/* [0:15] */
            __IO uint32_t reserved1            : 8; /* [16:23] */
            __IO uint32_t mbc                  : 6; /* [24:29] */
            __IO uint32_t sa                   : 1; /* [30] */
            __IO uint32_t ae                  : 1; /* [31] */
        } a1h_bit;
    };

    /**
      * @brief emac mac a1l register, offset:0x4C
      */
    union {
        __IO uint32_t a1l;
        struct {
            __IO uint32_t ma1l                 : 32;/* [0:31] */
        } a1l_bit;
    };

    /**
      * @brief emac mac a2h register, offset:0x50
      */
    union {
        __IO uint32_t a2h;
        struct {
            __IO uint32_t ma2h                 : 16;/* [0:15] */
            __IO uint32_t reserved1            : 8; /* [16:23] */
            __IO uint32_t mbc                  : 6; /* [24:29] */
            __IO uint32_t sa                   : 1; /* [30] */
            __IO uint32_t ae                   : 1; /* [31] */
        } a2h_bit;
    };

    /**
      * @brief emac mac a2l register, offset:0x54
      */
    union {
        __IO uint32_t a2l;
        struct {
            __IO uint32_t ma2l                 : 32;/* [0:31] */
        } a2l_bit;
    };

    /**
      * @brief emac mac a3h register, offset:0x58
      */
    union {
        __IO uint32_t a3h;
        struct {
            __IO uint32_t ma3h                 : 16;/* [0:15] */
            __IO uint32_t reserved1            : 8; /* [16:23] */
            __IO uint32_t mbc                  : 6; /* [24:29] */
            __IO uint32_t sa                   : 1; /* [30] */
            __IO uint32_t ae                   : 1; /* [31] */
        } a3h_bit;
    };

    /**
      * @brief emac mac a3l register, offset:0x5C
      */
    union {
        __IO uint32_t a3l;
        struct {
            __IO uint32_t ma3l                 : 32;/* [0:31] */
        } a3l_bit;
    };
} EMAC_Type;

/**
  * @brief type define emac mmc register all
  */
typedef struct {
    /**
      * @brief emac mmc ctrl register, offset:0x0100
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t rc                   : 1; /* [0] */
            __IO uint32_t scr                  : 1; /* [1] */
            __IO uint32_t rr                   : 1; /* [2] */
            __IO uint32_t fmc                  : 1; /* [3] */
            __IO uint32_t reserved1            : 28;/* [4:31] */
        } ctrl_bit;
    };

    /**
      * @brief emac mmc ri register, offset:0x0104
      */
    union {
        __IO uint32_t ri;
        struct {
            __IO uint32_t reserved1            : 5; /* [0:4] */
            __IO uint32_t rfce                 : 1; /* [5] */
            __IO uint32_t rfae                 : 1; /* [6] */
            __IO uint32_t reserved2            : 10;/* [7:16] */
            __IO uint32_t rguf                 : 1; /* [17] */
            __IO uint32_t reserved3            : 14;/* [18:31] */
        } ri_bit;
    };

    /**
      * @brief emac mmc ti register, offset:0x0108
      */
    union {
        __IO uint32_t ti;
        struct {
            __IO uint32_t reserved1            : 14;/* [0:13] */
            __IO uint32_t tscgfci              : 1; /* [14] */
            __IO uint32_t tgfmsc               : 1; /* [15] */
            __IO uint32_t reserved2            : 5; /* [16:20] */
            __IO uint32_t tgf                  : 1; /* [21] */
            __IO uint32_t reserved3            : 10;/* [22:31] */
        } ti_bit;
    };

    /**
      * @brief emac mmc rim register, offset:0x010C
      */
    union {
        __IO uint32_t rim;
        struct {
            __IO uint32_t reserved1            : 5; /* [0:4] */
            __IO uint32_t rcefcim              : 1; /* [5] */
            __IO uint32_t raefacim             : 1; /* [6] */
            __IO uint32_t reserved2            : 10;/* [7:16] */
            __IO uint32_t rugfcim              : 1; /* [17] */
            __IO uint32_t reserved3            : 14;/* [18:31] */
        } rim_bit;
    };

    /**
      * @brief emac mmc tim register, offset:0x0110
      */
    union {
        __IO uint32_t tim;
        struct {
            __IO uint32_t reserved1            : 14;/* [0:13] */
            __IO uint32_t tscgfcim             : 1; /* [14] */
            __IO uint32_t tmcgfcim             : 1; /* [15] */
            __IO uint32_t reserved2            : 5; /* [16:20] */
            __IO uint32_t tgfcim               : 1; /* [21] */
            __IO uint32_t reserved3            : 10;/* [22:31] */
        } tim_bit;
    };

    /**
      * @brief emac mmc reserved1 register, offset:0x0114~0x0148
      */
    __IO uint32_t reserved1[14];

    /**
      * @brief emac mmc tfscc register, offset:0x014C
      */
    union {
        __IO uint32_t tfscc;
        struct {
            __IO uint32_t tgfscc               : 32;/* [0:31] */
        } tfscc_bit;
    };

    /**
      * @brief emac mmc tfmscc register, offset:0x0150
      */
    union {
        __IO uint32_t tfmscc;
        struct {
            __IO uint32_t tgfmscc              : 32;/* [0:31] */
        } tfmscc_bit;
    };

    /**
      * @brief emac mmc reserved2 register, offset:0x0154~0x0164
      */
    __IO uint32_t reserved2[5];

    /**
      * @brief emac mmc tfcnt register, offset:0x0168
      */
    union {
        __IO uint32_t tfcnt;
        struct {
            __IO uint32_t tgfc                 : 32;/* [0:31] */
        } tfcnt_bit;
    };

    /**
      * @brief emac mmc reserved3 register, offset:0x016C~0x0190
      */
    __IO uint32_t reserved3[10];

    /**
      * @brief emac mmc rfcecnt register, offset:0x0194
      */
    union {
        __IO uint32_t rfcecnt;
        struct {
            __IO uint32_t rfcec                : 32;/* [0:31] */
        } rfcecnt_bit;
    };

    /**
      * @brief emac mmc rfaecnt register, offset:0x0198
      */
    union {
        __IO uint32_t rfaecnt;
        struct {
            __IO uint32_t rfaec                : 32;/* [0:31] */
        } rfaecnt_bit;
    };

    /**
      * @brief emac mmc reserved4 register, offset:0x019C~0x01C0
      */
    __IO uint32_t reserved4[10];

    /**
      * @brief emac mmc rgufcnt register, offset:0x01C4
      */
    union {
        __IO uint32_t rgufcnt;
        struct {
            __IO uint32_t rgufc                : 32;/* [0:31] */
        } rgufcnt_bit;
    };
} EMAC_MMC_Type;

/**
  * @brief type define emac ptp register all
  */
typedef struct {
    /**
      * @brief emac ptp tsctrl register, offset:0x0700
      */
    union {
        __IO uint32_t tsctrl;
        struct {
            __IO uint32_t te                   : 1; /* [0] */
            __IO uint32_t tfcu                 : 1; /* [1] */
            __IO uint32_t ti                   : 1; /* [2] */
            __IO uint32_t tu                   : 1; /* [3] */
            __IO uint32_t tite                 : 1; /* [4] */
            __IO uint32_t aru                  : 1; /* [5] */
            __IO uint32_t reserved1            : 2; /* [6:7] */
            __IO uint32_t etaf                 : 1; /* [8] */
            __IO uint32_t tdbrc                : 1; /* [9] */
            __IO uint32_t eppv2f               : 1; /* [10] */
            __IO uint32_t eppef                : 1; /* [11] */
            __IO uint32_t eppfsip6u            : 1; /* [12] */
            __IO uint32_t eppfsip4u            : 1; /* [13] */
            __IO uint32_t etsfem               : 1; /* [14] */
            __IO uint32_t esfmrtm              : 1; /* [15] */
            __IO uint32_t sppfts               : 2; /* [16:17] */
            __IO uint32_t emafpff              : 1; /* [18] */
            __IO uint32_t reserved2            : 13;/* [19:31] */
        } tsctrl_bit;
    };

    /**
      * @brief emac ptp ssinc register, offset:0x0704
      */
    union {
        __IO uint32_t ssinc;
        struct {
            __IO uint32_t ssiv                 : 8; /* [0] */
            __IO uint32_t reserved1            : 24;/* [8:31] */
        } ssinc_bit;
    };

    /**
      * @brief emac ptp tsh register, offset:0x0708
      */
    union {
        __IO uint32_t tsh;
        struct {
            __IO uint32_t ts                   : 32;/* [0:31] */
        } tsh_bit;
    };

    /**
      * @brief emac ptp tsl register, offset:0x070C
      */
    union {
        __IO uint32_t tsl;
        struct {
            __IO uint32_t tss                  : 31;/* [0:30] */
            __IO uint32_t ast                  : 1; /* [31] */
        } tsl_bit;
    };

    /**
      * @brief emac ptp tshud register, offset:0x0710
      */
    union {
        __IO uint32_t tshud;
        struct {
            __IO uint32_t ts                   : 32;/* [0:31] */
        } tshud_bit;
    };

    /**
      * @brief emac ptp tslud register, offset:0x0714
      */
    union {
        __IO uint32_t tslud;
        struct {
            __IO uint32_t tss                  : 31;/* [0:30] */
            __IO uint32_t ast                  : 1; /* [31] */
        } tslud_bit;
    };

    /**
      * @brief emac ptp tsad register, offset:0x0718
      */
    union {
        __IO uint32_t tsad;
        struct {
            __IO uint32_t tar                  : 32;/* [0:31] */
        } tsad_bit;
    };

    /**
      * @brief emac ptp tth register, offset:0x071C
      */
    union {
        __IO uint32_t tth;
        struct {
            __IO uint32_t ttsr                 : 32;/* [0:31] */
        } tth_bit;
    };

    /**
      * @brief emac ptp ttl register, offset:0x0720
      */
    union {
        __IO uint32_t ttl;
        struct {
            __IO uint32_t ttlr                 : 32;/* [0:31] */
        } ttl_bit;
    };

    /**
      * @brief emac ptp reserved register, offset:0x0724
      */
    __IO uint32_t reserved1;

    /**
     * @brief emac ptp tssr register, offset:0x0728
     */
    union {
        __IO uint32_t tssr;
        struct {
            __IO uint32_t tso                  : 1; /* [0] */
            __IO uint32_t tttr                 : 1; /* [1] */
            __IO uint32_t reserved1            : 30;/* [2:31] */
        } tssr_bit;
    };

    /**
      * @brief emac ptp ppscr register, offset:0x072C
      */
    union {
        __IO uint32_t ppscr;
        struct {
            __IO uint32_t pofc                 : 4; /* [0:3] */
            __IO uint32_t reserved1            : 28;/* [4:31] */
        } ppscr_bit;
    };
} EMAC_PTP_Type;

/**
  * @brief type define emac ptp register all
  */
typedef struct {
    /**
      * @brief emac dma bm register, offset:0x1000
      */
    union {
        __IO uint32_t bm;
        struct {
            __IO uint32_t swr                  : 1; /* [0] */
            __IO uint32_t da                   : 1; /* [1] */
            __IO uint32_t dsl                  : 5; /* [2:6] */
            __IO uint32_t reserved1            : 1; /* [7] */
            __IO uint32_t pbl                  : 6; /* [8:13] */
            __IO uint32_t pr                   : 2; /* [14:15] */
            __IO uint32_t fb                   : 1; /* [16] */
            __IO uint32_t rdp                  : 6; /* [17:22] */
            __IO uint32_t usp                  : 1; /* [23] */
            __IO uint32_t pblx8                : 1; /* [24] */
            __IO uint32_t aab                  : 1; /* [25] */
            __IO uint32_t reserved2            : 6; /* [26:31] */
        } bm_bit;
    };

    /**
      * @brief emac dma tpd register, offset:0x1004
      */
    union {
        __IO uint32_t tpd;
        struct {
            __IO uint32_t tpd                  : 32; /* [0:31] */
        } tpd_bit;
    };

    /**
      * @brief emac dma rpd register, offset:0x1008
      */
    union {
        __IO uint32_t rpd;
        struct {
            __IO uint32_t rpd                  : 32; /* [0:31] */
        } rpd_bit;
    };

    /**
      * @brief emac dma rdladdr register, offset:0x100c
      */
    union {
        __IO uint32_t rdladdr;
        struct {
            __IO uint32_t srl                  : 32; /* [0:31] */
        } rdladdr_bit;
    };

    /**
      * @brief emac dma tdladdr register, offset:0x1010
      */
    union {
        __IO uint32_t tdladdr;
        struct {
            __IO uint32_t stl                  : 32; /* [0:31] */
        } tdladdr_bit;
    };

    /**
      * @brief emac dma sts register, offset:0x1014
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t ti                   : 1; /* [0] */
            __IO uint32_t tps                  : 1; /* [1] */
            __IO uint32_t tbu                  : 1; /* [2] */
            __IO uint32_t tjt                  : 1; /* [3] */
            __IO uint32_t ovf                  : 1; /* [4] */
            __IO uint32_t unf                  : 1; /* [5] */
            __IO uint32_t ri                   : 1; /* [6] */
            __IO uint32_t rbu                  : 1; /* [7] */
            __IO uint32_t rps                  : 1; /* [8] */
            __IO uint32_t rwt                  : 1; /* [9] */
            __IO uint32_t eti                  : 1; /* [10] */
            __IO uint32_t reserved1            : 2; /* [11:12] */
            __IO uint32_t fbei                 : 1; /* [13] */
            __IO uint32_t eri                  : 1; /* [14] */
            __IO uint32_t ais                  : 1; /* [15] */
            __IO uint32_t nis                  : 1; /* [16] */
            __IO uint32_t rs                   : 3; /* [17:19] */
            __IO uint32_t ts                   : 3; /* [20:22] */
            __IO uint32_t eb                   : 3; /* [23:25] */
            __IO uint32_t reserved2            : 1; /* [26] */
            __IO uint32_t mmi                  : 1; /* [27] */
            __IO uint32_t mpi                  : 1; /* [28] */
            __IO uint32_t tti                  : 1; /* [29] */
            __IO uint32_t reserved3            : 2; /* [30:31] */
        } sts_bit;
    };

    /**
      * @brief emac dma opm register, offset:0x1018
      */
    union {
        __IO uint32_t opm;
        struct {
            __IO uint32_t reserved1            : 1; /* [0] */
            __IO uint32_t ssr                  : 1; /* [1] */
            __IO uint32_t osf                  : 1; /* [2] */
            __IO uint32_t rtc                  : 2; /* [3:4] */
            __IO uint32_t reserved2            : 1; /* [5] */
            __IO uint32_t fugf                 : 1; /* [6] */
            __IO uint32_t fef                  : 1; /* [7] */
            __IO uint32_t reserved3            : 5; /* [8:12] */
            __IO uint32_t sstc                 : 1; /* [13] */
            __IO uint32_t ttc                  : 3; /* [14:16] */
            __IO uint32_t reserved4            : 3; /* [17:19] */
            __IO uint32_t ftf                  : 1; /* [20] */
            __IO uint32_t tsf                  : 1; /* [21] */
            __IO uint32_t reserved5            : 2; /* [22:23] */
            __IO uint32_t dfrf                 : 1; /* [24] */
            __IO uint32_t rsf                  : 1; /* [25] */
            __IO uint32_t dt                   : 1; /* [26] */
            __IO uint32_t reserved6            : 5; /* [27:31] */
        } opm_bit;
    };

    /**
      * @brief emac dma ie register, offset:0x101C
      */
    union {
        __IO uint32_t ie;
        struct {
            __IO uint32_t tie                  : 1; /* [0] */
            __IO uint32_t tse                  : 1; /* [1] */
            __IO uint32_t tue                  : 1; /* [2] */
            __IO uint32_t tje                  : 1; /* [3] */
            __IO uint32_t ove                  : 1; /* [4] */
            __IO uint32_t une                  : 1; /* [5] */
            __IO uint32_t rie                  : 1; /* [6] */
            __IO uint32_t rbue                 : 1; /* [7] */
            __IO uint32_t rse                  : 1; /* [8] */
            __IO uint32_t rwte                 : 1; /* [9] */
            __IO uint32_t eie                  : 1; /* [10] */
            __IO uint32_t reserved1            : 2; /* [11:12] */
            __IO uint32_t fbee                 : 1; /* [13] */
            __IO uint32_t ere                  : 1; /* [14] */
            __IO uint32_t aie                  : 1; /* [15] */
            __IO uint32_t nie                  : 1; /* [16] */
            __IO uint32_t reserved2            : 15;/* [17:31] */
        } ie_bit;
    };

    /**
      * @brief emac dma mfbocnt register, offset:0x1020
      */
    union {
        __IO uint32_t mfbocnt;
        struct {
            __IO uint32_t mfc                  : 16;/* [0:15] */
            __IO uint32_t obmfc                : 1; /* [16] */
            __IO uint32_t ofc                  : 11;/* [17:27] */
            __IO uint32_t obfoc                : 1; /* [28] */
            __IO uint32_t reserved1            : 3; /* [29:31] */
        } mfbocnt_bit;
    };

    /**
      * @brief emac dma reserved1 register, offset:0x1024~0x1044
      */
    __IO uint32_t reserved1[9];

    /**
      * @brief emac ctd register, offset:0x1048
      */
    union {
        __IO uint32_t ctd;
        struct {
            __IO uint32_t htdap                : 32;/* [0:31] */
        } ctd_bit;
    };

    /**
      * @brief emac crd register, offset:0x104C
      */
    union {
        __IO uint32_t crd;
        struct {
            __IO uint32_t hrdap                : 32;/* [0:31] */
        } crd_bit;
    };

    /**
      * @brief emac ctbaddr register, offset:0x1050
      */
    union {
        __IO uint32_t ctbaddr;
        struct {
            __IO uint32_t htbap                : 32;/* [0:31] */
        } ctbaddr_bit;
    };

    /**
      * @brief emac crbaddr register, offset:0x1054
      */
    union {
        __IO uint32_t crbaddr;
        struct {
            __IO uint32_t hrbap                : 32;/* [0:31] */
        } crbaddr_bit;
    };
} EMAC_DMA_Type;

/**
  * @}
  */
#define EMAC                             ((EMAC_Type *) EMAC_BASE)
#define EMAC_MMC                         ((EMAC_MMC_Type *) EMAC_MMC_BASE)
#define EMAC_PTP                         ((EMAC_PTP_Type *) EMAC_PTP_BASE)
#define EMAC_DMA                         ((EMAC_DMA_Type *) EMAC_DMA_BASE)

/** @defgroup EMAC_exported_functions
  * @{
  */

void EMAC_Reset(void);
void EMAC_Clock_Range_Set(void);
void EMAC_DMA_Software_Reset_Set(void);
flag_status EMAC_DMA_Software_Reset_Get(void);
void EMAC_Start(void);
void EMAC_Stop(void);
error_status EMAC_PHY_Register_Write(uint8_t address, uint8_t reg, uint16_t data);
error_status EMAC_PHY_Register_Read(uint8_t address, uint8_t reg, uint16_t *data);
void EMAC_Control_Para_Init(EMAC_Control_Config_Type *control_para);
void EMAC_Control_Config(EMAC_Control_Config_Type *control_struct);
void EMAC_Receiver_Enable(confirm_state new_state);
void EMAC_Trasmitter_Enable(confirm_state new_state);
void EMAC_Deferral_Check_Set(confirm_state new_state);
void EMAC_BackOff_Limit_Set(EMAC_bol_Type slot_time);
void EMAC_Auto_pad_CRC_Stripping_Set(confirm_state new_state);
void EMAC_Retry_Disable(confirm_state new_state);
void EMAC_Ipv4_checksum_offload_Set(confirm_state new_state);
void EMAC_Loopback_Mode_Enable(confirm_state new_state);
void EMAC_Receive_Own_Disable(confirm_state new_state);
void EMAC_Carrier_Sense_Disable(confirm_state new_state);
void EMAC_Interframe_Gap_Set(EMAC_intergrame_Gap_Type number);
void EMAC_Jabber_Disable(confirm_state new_state);
void EMAC_WatchDog_Disable(confirm_state new_state);
void EMAC_Fast_Speed_Set(EMAC_Speed_Type speed);
void EMAC_Duplex_Mode_Set(EMAC_Duplex_Type duplex_Mode);
void EMAC_Promiscuous_Mode_Set(confirm_state new_state);
void EMAC_Hash_Unicast_Set(confirm_state new_state);
void EMAC_Hash_MultiCast_Set(confirm_state new_state);
void EMAC_Dstaddr_Inverse_Filter_Set(confirm_state new_state);
void EMAC_Pass_All_MultiCasting_Set(confirm_state new_state);
void EMAC_broadcast_Frames_Disable(confirm_state new_state);
void EMAC_Pass_Control_Frames_Set(EMAC_Control_Frames_Filter_Type condition);
void EMAC_Srcaddr_Inverse_Filter_Set(confirm_state new_state);
void EMAC_Srcaddr_Filter_Set(confirm_state new_state);
void EMAC_Hash_Perfect_Filter_Set(confirm_state new_state);
void EMAC_Receive_All_Set(confirm_state new_state);
void EMAC_Hash_Table_High32bits_Set(uint32_t high32bits);
void EMAC_Hash_Table_Low32bits_Set(uint32_t low32bits);
flag_status EMAC_MII_Busy_Get(void);
void EMAC_MII_Write(confirm_state new_state);
void EMAC_FCB_BPA_Set(confirm_state new_state);
void EMAC_Transmit_Flow_Control_Enable(confirm_state new_state);
void EMAC_Receive_Flow_Control_Enable(confirm_state new_state);
void EMAC_Unicast_Pause_Frame_Detect(confirm_state new_state);
void EMAC_Pause_Low_Threshold_Set(EMAC_Pause_slot_Threshold_Type pasue_threshold);
void EMAC_Zero_Quanta_Pause_Disable(confirm_state new_state);
void EMAC_Pause_Time_Set(uint16_t pause_time);
void EMAC_Vlan_Tag_Identifier_Set(uint16_t identifier);
void EMAC_Vlan_Tag_Comparison_Set(confirm_state new_state);
void EMAC_WakeUp_Frame_Set(uint32_t value);
uint32_t EMAC_WakeUp_Frame_Get(void);
void EMAC_Power_Down_Set(confirm_state new_state);
void EMAC_Magic_Packet_Enable(confirm_state new_state);
void EMAC_WakeUp_Frame_Enable(confirm_state new_state);
flag_status EMAC_Received_Magic_Packet_Get(void);
flag_status EMAC_Received_WakeUp_Frame_Get(void);
void EMAC_Global_Unicast_Set(confirm_state new_state);
void EMAC_WakeUp_Frame_Filter_Reset(confirm_state new_state);
flag_status EMAC_Interrupt_Status_Read(uint32_t flag);
void EMAC_Interrupt_Mask_Set(EMAC_Interrupt_Mask_Type mask_Type, confirm_state new_state);
void EMAC_Local_Address_Set(uint8_t *address);
void EMAC_Address_Filter_Set(EMAC_Address_Type mac, EMAC_Address_Filter_Type filter, EMAC_Address_Mask_Type mask_bit, confirm_state new_state);
uint32_t EMAC_Received_Packet_size_Get(void);
uint32_t EMAC_Dmarxdesc_Frame_Length_Get(EMAC_DMA_Desc_Type *DMA_RX_desc);
void EMAC_DMA_Descriptor_List_Address_Set(EMAC_DMA_TX_RX_Type transfer_Type, EMAC_DMA_Desc_Type *DMA_Desc_tab, uint8_t *buff, uint32_t buffer_count);
uint32_t EMAC_DMA_Descriptor_List_Address_Get(EMAC_DMA_TX_RX_Type transfer_Type);
void EMAC_DMA_RX_Desc_Interrupt_Config(EMAC_DMA_Desc_Type *DMA_RX_desc, confirm_state new_state);
void EMAC_DMA_Para_Init(EMAC_DMA_Config_Type *control_para);
void EMAC_DMA_Config(EMAC_DMA_Config_Type *control_para);
void EMAC_DMA_Arbitation_Set(EMAC_DMA_RX_TX_Ratio_Type ratio, confirm_state new_state);
void EMAC_DMA_Descriptor_Skip_Length_Set(uint8_t length);
void EMAC_DMA_Separate_pbl_Set(EMAC_DMA_pbl_Type tx_length, EMAC_DMA_pbl_Type rx_length, confirm_state new_state);
void EMAC_DMA_Eight_pbl_Mode_Set(confirm_state new_state);
void EMAC_DMA_Address_Aligned_Beats_Set(confirm_state new_state);
void EMAC_DMA_Poll_Demand_Set(EMAC_DMA_TX_RX_Type transfer_Type, uint32_t value);
uint32_t EMAC_DMA_Poll_Demand_Get(EMAC_DMA_TX_RX_Type transfer_Type);
EMAC_DMA_Receive_Process_Status_Type EMAC_DMA_Receive_Status_Get(void);
EMAC_DMA_Transmit_Process_Status_Type EMAC_DMA_Transmit_Status_Get(void);
void EMAC_DMA_Operations_Set(EMAC_DMA_Operations_Type ops, confirm_state new_state);
void EMAC_DMA_Receive_Threshold_Set(EMAC_DMA_Receive_Threshold_Type value);
void EMAC_DMA_Transmit_Threshold_Set(EMAC_DMA_Transmit_Threshold_Type value);
void EMAC_DMA_Interrupt_Enable(EMAC_DMA_Interrupt_Type it, confirm_state new_state);
uint16_t EMAC_DMA_Controller_Missing_Frame_Get(void);
uint8_t EMAC_DMA_Missing_OverFlow_Bit_Get(void);
uint16_t EMAC_DMA_Application_Missing_Frame_Get(void);
uint8_t EMAC_DMA_FIFO_OverFlow_Bit_Get(void);
uint32_t EMAC_DMA_tansfer_Address_Get(EMAC_DMA_Transfer_Address_Type transfer_Type);
void EMAC_MMC_Counter_Reset(void);
void EMAC_MMC_Rollover_Stop(confirm_state new_state);
void EMAC_MMC_Reset_ON_Read_Enable(confirm_state new_state);
void EMAC_MMC_Counter_Freeze(confirm_state new_state);
flag_status EMAC_MMC_Received_Status_Get(uint32_t flag);
flag_status EMAC_MMC_Transmit_Status_Get(uint32_t flag);
void EMAC_MMC_Received_Interrupt_Mask_Set(uint32_t flag, confirm_state new_state);
void EMAC_MMC_Transmit_Interrupt_Mask_Set(uint32_t flag, confirm_state new_state);
uint32_t EMAC_MMC_Transmit_Good_Frames_Get(uint32_t flag);
uint32_t EMAC_MMC_Received_Error_Frames_Get(uint32_t flag);
void EMAC_PTP_TimeStamp_Enable(confirm_state new_state);
void EMAC_PTP_TimeStamp_Fine_Update_Enable(confirm_state new_state);
void EMAC_PTP_TimeStamp_System_Time_Init(confirm_state new_state);
void EMAC_PTP_TimeStamp_System_Time_Update(confirm_state new_state);
void EMAC_PTP_Interrupt_Trigger_Enable(confirm_state new_state);
void EMAC_PTP_Addend_Register_Update(confirm_state new_state);
void EMAC_PTP_SnapShot_Received_Frames_Enable(confirm_state new_state);
void EMAC_PTP_SubSecond_Rollover_Enable(confirm_state new_state);
void EMAC_PTP_PSV2_Enable(confirm_state new_state);
void EMAC_PTP_SnapShot_EMAC_Frames_Enable(confirm_state new_state);
void EMAC_PTP_SnapShot_Ipv6_Frames_Enable(confirm_state new_state);
void EMAC_PTP_SnapShot_Ipv4_Frames_Enable(confirm_state new_state);
void EMAC_PTP_SnapShot_Event_Message_Enable(confirm_state new_state);
void EMAC_PTP_SnapShot_Master_Event_Enable(confirm_state new_state);
void EMAC_PTP_Clock_Node_Set(EMAC_PTP_Clock_Node_Type node);
void EMAC_PTP_MAC_Address_Filter_Enable(confirm_state new_state);
void EMAC_PTP_SubSecond_Increment_Set(uint8_t value);
uint32_t EMAC_PTP_System_Second_Get(void);
uint32_t EMAC_PTP_System_SubSecond_Get(void);
confirm_state EMAC_PTP_System_Time_Sign_Get(void);
void EMAC_PTP_System_Second_Set(uint32_t second);
void EMAC_PTP_System_SubSecond_Set(uint32_t subsecond);
void EMAC_PTP_System_Time_Sign_Set(confirm_state sign);
void EMAC_PTP_TimeStamp_Addend_Set(uint32_t value);
void EMAC_PTP_Target_Second_Set(uint32_t value);
void EMAC_PTP_Target_NanoSecond_Set(uint32_t value);
confirm_state EMAC_PTP_TimeStamp_Status_Get(EMAC_PTP_TimeStamp_Status_Type status);
void EMAC_PTP_PPS_Frequency_Set(EMAC_PTP_PPS_Control_Type freq);
flag_status EMAC_DMA_Flag_Get(uint32_t DMA_flag);
void EMAC_DMA_Flag_Clear(uint32_t DMA_flag);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
