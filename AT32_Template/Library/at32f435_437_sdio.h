/**
  **************************************************************************
  * @file     at32f435_437_sdio.h
  * @brief    at32f435_437 sdio header file
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

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_SDIO_H
#define __AT32F435_437_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup SDIO
  * @{
  */

/** @defgroup SDIO_Interrupts_definition
  * @brief sdio interrupt
  * @{
  */
#define SDIO_CMDFAIL_INT                 ((uint32_t)0x00000001) /*!< command response received check failed 中断 */
#define SDIO_DTFAIL_INT                  ((uint32_t)0x00000002) /*!< data block sent/received check failed 中断 */
#define SDIO_CMDTIMEOUT_INT              ((uint32_t)0x00000004) /*!< command response timerout 中断 */
#define SDIO_DTTIMEOUT_INT               ((uint32_t)0x00000008) /*!< data timeout 中断 */
#define SDIO_TXERRU_INT                  ((uint32_t)0x00000010) /*!< transmit underrun error 中断 */
#define SDIO_RXERRO_INT                  ((uint32_t)0x00000020) /*!< received overrun error 中断 */
#define SDIO_CMDRSPCMPL_INT              ((uint32_t)0x00000040) /*!< command response received 中断 */
#define SDIO_CMDCMPL_INT                 ((uint32_t)0x00000080) /*!< command sent 中断 */
#define SDIO_DTCMP_INT                   ((uint32_t)0x00000100) /*!< data sent 中断 */
#define SDIO_SBITERR_INT                 ((uint32_t)0x00000200) /*!< start bit not detected on data bus 中断 */
#define SDIO_DTBLKCMPL_INT               ((uint32_t)0x00000400) /*!< data block sent/received 中断 */
#define SDIO_DOCMD_INT                   ((uint32_t)0x00000800) /*!< command transfer in progress 中断 */
#define SDIO_DOTX_INT                    ((uint32_t)0x00001000) /*!< data transmit in progress 中断 */
#define SDIO_DORX_INT                    ((uint32_t)0x00002000) /*!< data receive in progress 中断 */
#define SDIO_TXBUFH_INT                  ((uint32_t)0x00004000) /*!< transmit buf half empty 中断 */
#define SDIO_RXBUFH_INT                  ((uint32_t)0x00008000) /*!< receive buf half full 中断 */
#define SDIO_TXBUFF_INT                  ((uint32_t)0x00010000) /*!< transmit buf full 中断 */
#define SDIO_RXBUFF_INT                  ((uint32_t)0x00020000) /*!< receive buf full 中断 */
#define SDIO_TXBUFE_INT                  ((uint32_t)0x00040000) /*!< transmit buf empty 中断 */
#define SDIO_RXBUFE_INT                  ((uint32_t)0x00080000) /*!< receive buf empty 中断 */
#define SDIO_TXBUF_INT                   ((uint32_t)0x00100000) /*!< data available in transmit 中断 */
#define SDIO_RXBUF_INT                   ((uint32_t)0x00200000) /*!< data available in receive 中断 */
#define SDIO_SDIOIF_INT                  ((uint32_t)0x00400000) /*!< sdio interface received 中断 */

/**
  * @}
  */

/** @defgroup SDIO_flags_definition
  * @brief sdio flag
  * @{
  */
#define SDIO_CMDFAIL_FLAG                ((uint32_t)0x00000001) /*!< command response received check failed flag */
#define SDIO_DTFAIL_FLAG                 ((uint32_t)0x00000002) /*!< data block sent/received check failed flag */
#define SDIO_CMDTIMEOUT_FLAG             ((uint32_t)0x00000004) /*!< command response timerout flag */
#define SDIO_DTTIMEOUT_FLAG              ((uint32_t)0x00000008) /*!< data timeout flag */
#define SDIO_TXERRU_FLAG                 ((uint32_t)0x00000010) /*!< transmit underrun error flag */
#define SDIO_RXERRO_FLAG                 ((uint32_t)0x00000020) /*!< received overrun error flag */
#define SDIO_CMDRSPCMPL_FLAG             ((uint32_t)0x00000040) /*!< command response received flag */
#define SDIO_CMDCMPL_FLAG                ((uint32_t)0x00000080) /*!< command sent flag */
#define SDIO_DTCMPL_FLAG                 ((uint32_t)0x00000100) /*!< data sent flag */
#define SDIO_SBITERR_FLAG                ((uint32_t)0x00000200) /*!< start bit not detected on data bus flag */
#define SDIO_DTBLKCMPL_FLAG              ((uint32_t)0x00000400) /*!< data block sent/received flag */
#define SDIO_DOCMD_FLAG                  ((uint32_t)0x00000800) /*!< command transfer in progress flag */
#define SDIO_DOTX_FLAG                   ((uint32_t)0x00001000) /*!< data transmit in progress flag */
#define SDIO_DORX_FLAG                   ((uint32_t)0x00002000) /*!< data receive in progress flag */
#define SDIO_TXBUFH_FLAG                 ((uint32_t)0x00004000) /*!< transmit buf half empty flag */
#define SDIO_RXBUFH_FLAG                 ((uint32_t)0x00008000) /*!< receive buf half full flag */
#define SDIO_TXBUFF_FLAG                 ((uint32_t)0x00010000) /*!< transmit buf full flag */
#define SDIO_RXBUFF_FLAG                 ((uint32_t)0x00020000) /*!< receive buf full flag */
#define SDIO_TXBUFE_FLAG                 ((uint32_t)0x00040000) /*!< transmit buf empty flag */
#define SDIO_RXBUFE_FLAG                 ((uint32_t)0x00080000) /*!< receive buf empty flag */
#define SDIO_TXBUF_FLAG                  ((uint32_t)0x00100000) /*!< data available in transmit flag */
#define SDIO_RXBUF_FLAG                  ((uint32_t)0x00200000) /*!< data available in receive flag */
#define SDIO_SDIOIF_FLAG                 ((uint32_t)0x00400000) /*!< sdio interface received flag */

/**
  * @}
  */

/** @defgroup SDIO_exported_Types
  * @{
  */

/**
  * @brief sdio power state
  */
typedef enum {
    SDIO_Power_OFF                         = 0x00, /*!< power-off, clock to card is stopped */
    SDIO_Power_ON                          = 0x03  /*!< power-on, the card is clocked */
} SDIO_Power_State_Type;

/**
  * @brief sdio edge phase
  */
typedef enum {
    SDIO_Clock_Edge_RISING                 = 0x00, /*!< sdio bus clock generated on the rising edge of the master clock */
    SDIO_Clock_Edge_FALLING                = 0x01  /*!< sdio bus clock generated on the falling edge of the master clock */
} SDIO_Edge_phase_Type;

/**
  * @brief sdio bus width
  */
typedef enum {
    SDIO_Bus_Width_D1                      = 0x00, /*!< sdio wide bus select 1-bit */
    SDIO_Bus_Width_D4                      = 0x01, /*!< sdio wide bus select 4-bit */
    SDIO_Bus_Width_D8                      = 0x02  /*!< sdio wide bus select 8-bit */
} SDIO_Bus_Width_Type;

/**
  * @brief sdio response type
  */
typedef enum {
    SDIO_Response_NO                       = 0x00, /*!< no response */
    SDIO_Response_SHORT                    = 0x01, /*!< short response */
    SDIO_Response_LONG                     = 0x03  /*!< long response */
} SDIO_reponse_Type;

/**
  * @brief sdio wait type
  */
typedef enum {
    SDIO_Wait_FOR_NO                       = 0x00, /*!< no wait */
    SDIO_Wait_FOR_INT                      = 0x01, /*!< wait interrupt request */
    SDIO_Wait_FOR_PEND                     = 0x02  /*!< wait end of transfer */
} SDIO_Wait_Type;

/**
  * @brief sdio response register index
  */
typedef enum {
    SDIO_RSP1_INDEX                        = 0x00, /*!< response index 1, corresponding to SDIO_rsp register 1 */
    SDIO_RSP2_INDEX                        = 0x01, /*!< response index 2, corresponding to SDIO_rsp register 2 */
    SDIO_RSP3_INDEX                        = 0x02, /*!< response index 3, corresponding to SDIO_rsp register 3 */
    SDIO_RSP4_INDEX                        = 0x03  /*!< response index 4, corresponding to SDIO_rsp register 4 */
} SDIO_rsp_index_Type;

/**
  * @brief sdio data block size
  */
typedef enum {
    SDIO_Data_Block_SIZE_1B                = 0x00, /*!< data block size 1 byte */
    SDIO_Data_Block_SIZE_2B                = 0x01, /*!< data block size 2 bytes */
    SDIO_Data_Block_SIZE_4B                = 0x02, /*!< data block size 4 bytes */
    SDIO_Data_Block_SIZE_8B                = 0x03, /*!< data block size 8 bytes */
    SDIO_Data_Block_SIZE_16B               = 0x04, /*!< data block size 16 bytes */
    SDIO_Data_Block_SIZE_32B               = 0x05, /*!< data block size 32 bytes */
    SDIO_Data_Block_SIZE_64B               = 0x06, /*!< data block size 64 bytes */
    SDIO_Data_Block_SIZE_128B              = 0x07, /*!< data block size 128 bytes */
    SDIO_Data_Block_SIZE_256B              = 0x08, /*!< data block size 256 bytes */
    SDIO_Data_Block_SIZE_512B              = 0x09, /*!< data block size 512 bytes */
    SDIO_Data_Block_SIZE_1024B             = 0x0A, /*!< data block size 1024 bytes */
    SDIO_Data_Block_SIZE_2048B             = 0x0B, /*!< data block size 2048 bytes */
    SDIO_Data_Block_SIZE_4096B             = 0x0C, /*!< data block size 4096 bytes */
    SDIO_Data_Block_SIZE_8192B             = 0x0D, /*!< data block size 8192 bytes */
    SDIO_Data_Block_SIZE_16384B            = 0x0E  /*!< data block size 16384 bytes */
} SDIO_Block_size_Type;

/**
  * @brief sdio data transfer mode
  */
typedef enum {
    SDIO_Data_Block_TRANSFER               = 0x00, /*!< the sdio block transfer mode */
    SDIO_Data_Stream_TRANSFER              = 0x01  /*!< the sdio stream transfer mode */
} SDIO_Transfer_Mode_Type;

/**
  * @brief sdio data transfer direction
  */
typedef enum {
    SDIO_Data_Transfer_To_CARD             = 0x00, /*!< the sdio controller write */
    SDIO_Data_Transfer_To_CONTROLLER       = 0x01  /*!< the sdio controller read */
} SDIO_Transfer_Direction_Type;

/**
  * @brief sdio read wait mode
  */
typedef enum {
    SDIO_Read_Wait_CONTROLLED_BY_D2        = 0x00, /*!< the sdio read wait on data2 line */
    SDIO_Read_Wait_CONTROLLED_BY_CK        = 0x01  /*!< the sdio read wait on clock line */
} SDIO_Read_Wait_Mode_Type;

/**
  * @brief sdio command structure
  */
typedef struct {
    uint32_t                               argument;  /*!< the sdio command argument is sent to a card as part of command message */
    uint8_t                                cmd_index; /*!< the sdio command index */
    SDIO_reponse_Type                      rsp_Type;  /*!< the sdio response type */
    SDIO_Wait_Type                         wait_Type; /*!< the sdio wait for interrupt request is enabled or disable */
} SDIO_Command_struct_Type;

/**
  * @brief sdio data structure
  */
typedef struct {
    uint32_t                               timeout;            /*!< the sdio data timeout period in car bus clock periods */
    uint32_t                               data_length;        /*!< the sdio data length */
    SDIO_Block_size_Type                   block_size;         /*!< the sdio data block size of block transfer mode */
    SDIO_Transfer_Mode_Type                transfer_Mode;      /*!< the sdio transfer mode, block or stream */
    SDIO_Transfer_Direction_Type           transfer_direction; /*!< the sdio data transfer direction */
} SDIO_Data_struct_Type;

/**
  * @brief type define sdio register all
  */
typedef struct {
    /**
      * @brief sdio pwrctrl register, offset:0x00
      */
    union {
        __IO uint32_t pwrctrl;
        struct {
            __IO uint32_t ps                   : 2; /* [1:0] */
            __IO uint32_t reserved1            : 30;/* [31:2] */
        } pwrctrl_bit;
    };

    /**
      * @brief sdio clkctrl register, offset:0x04
      */
    union {
        __IO uint32_t clkctrl;
        struct {
            __IO uint32_t clkdiv_l             : 8; /* [7:0] */
            __IO uint32_t clkoen               : 1; /* [8] */
            __IO uint32_t pwrsven              : 1; /* [9] */
            __IO uint32_t bypsen               : 1; /* [10] */
            __IO uint32_t busws                : 2; /* [12:11] */
            __IO uint32_t clkegs               : 1; /* [13] */
            __IO uint32_t hfcen                : 1; /* [14] */
            __IO uint32_t clkdiv_h             : 2; /* [16:15] */
            __IO uint32_t reserved1            : 15;/* [31:17] */
        } clkctrl_bit;
    };

    /**
      * @brief sdio argu register, offset:0x08
      */
    union {
        __IO uint32_t argu;
        struct {
            __IO uint32_t argu                 : 32;/* [31:0] */
        } argu_bit;
    };

    /**
      * @brief sdio cmdctrl register, offset:0x0C
      */
    union {
        __IO uint32_t cmdctrl;
        struct {
            __IO uint32_t cmdidx               : 6; /* [5:0] */
            __IO uint32_t rspwt                : 2; /* [7:6] */
            __IO uint32_t intwt                : 1; /* [8] */
            __IO uint32_t pndwt                : 1; /* [9] */
            __IO uint32_t ccsmen               : 1; /* [10] */
            __IO uint32_t iosusp               : 1; /* [11] */
            __IO uint32_t reserved1            : 20;/* [31:12] */
        } cmdctrl_bit;
    };

    /**
      * @brief sdio rspcmd register, offset:0x10
      */
    union {
        __IO uint32_t rspcmd;
        struct {
            __IO uint32_t rspcmd               : 6; /* [5:0] */
            __IO uint32_t reserved1            : 26;/* [31:6] */
        } rspcmd_bit;
    };

    /**
      * @brief sdio rsp1 register, offset:0x14
      */
    union {
        __IO uint32_t rsp1;
        struct {
            __IO uint32_t cardsts1             : 32;/* [31:0] */
        } rsp1_bit;
    };

    /**
      * @brief sdio rsp2 register, offset:0x18
      */
    union {
        __IO uint32_t rsp2;
        struct {
            __IO uint32_t cardsts2             : 32;/* [31:0] */
        } rsp2_bit;
    };

    /**
      * @brief sdio rsp3 register, offset:0x1C
      */
    union {
        __IO uint32_t rsp3;
        struct {
            __IO uint32_t cardsts3             : 32;/* [31:0] */
        } rsp3_bit;
    };

    /**
      * @brief sdio rsp4 register, offset:0x20
      */
    union {
        __IO uint32_t rsp4;
        struct {
            __IO uint32_t cardsts4             : 32;/* [31:0] */
        } rsp4_bit;
    };

    /**
      * @brief sdio dttmr register, offset:0x24
      */
    union {
        __IO uint32_t dttmr;
        struct {
            __IO uint32_t timeout              : 32;/* [31:0] */
        } dtTMR_bit;
    };

    /**
      * @brief sdio dtlen register, offset:0x28
      */
    union {
        __IO uint32_t dtlen;
        struct {
            __IO uint32_t dtlen                : 25;/* [24:0] */
            __IO uint32_t reserved1            : 7; /* [31:25] */
        } dtlen_bit;
    };

    /**
      * @brief sdio dtctrl register, offset:0x2C
      */
    union {
        __IO uint32_t dtctrl;
        struct {
            __IO uint32_t tfren                : 1; /* [0] */
            __IO uint32_t tfrdir               : 1; /* [1] */
            __IO uint32_t tfrmode              : 1; /* [2] */
            __IO uint32_t dmaen                : 1; /* [3] */
            __IO uint32_t blksize              : 4; /* [7:4] */
            __IO uint32_t rdwtstart            : 1; /* [8] */
            __IO uint32_t rdwtstop             : 1; /* [9] */
            __IO uint32_t rdwtmode             : 1; /* [10] */
            __IO uint32_t ioen                 : 1; /* [11] */
            __IO uint32_t reserved1            : 20;/* [31:12] */
        } dtctrl_bit;
    };

    /**
      * @brief sdio dtcnt register, offset:0x30
      */
    union {
        __IO uint32_t dtcnt;
        struct {
            __IO uint32_t cnt                  : 25;/* [24:0] */
            __IO uint32_t reserved1            : 7; /* [31:25] */
        } dtcnt_bit;
    };

    /**
      * @brief sdio sts register, offset:0x34
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t cmdfail              : 1; /* [0] */
            __IO uint32_t dtfail               : 1; /* [1] */
            __IO uint32_t cmdtimeout           : 1; /* [2] */
            __IO uint32_t dttimeout            : 1; /* [3] */
            __IO uint32_t txerru               : 1; /* [4] */
            __IO uint32_t rxerro               : 1; /* [5] */
            __IO uint32_t cmdrspcmpl           : 1; /* [6] */
            __IO uint32_t cmdcmpl              : 1; /* [7] */
            __IO uint32_t dtcmpl               : 1; /* [8] */
            __IO uint32_t sbiterr              : 1; /* [9] */
            __IO uint32_t dtblkcmpl            : 1; /* [10] */
            __IO uint32_t docmd                : 1; /* [11] */
            __IO uint32_t dotx                 : 1; /* [12] */
            __IO uint32_t dorx                 : 1; /* [13] */
            __IO uint32_t txbufh               : 1; /* [14] */
            __IO uint32_t rxbufh               : 1; /* [15] */
            __IO uint32_t txbuff               : 1; /* [16] */
            __IO uint32_t rxbuff               : 1; /* [17] */
            __IO uint32_t txbufe               : 1; /* [18] */
            __IO uint32_t rxbufe               : 1; /* [19] */
            __IO uint32_t txbuf                : 1; /* [20] */
            __IO uint32_t rxbuf                : 1; /* [21] */
            __IO uint32_t ioif                 : 1; /* [22] */
            __IO uint32_t reserved1            : 9; /* [31:23] */
        } sts_bit;
    };

    /**
      * @brief sdio intclr register, offset:0x38
      */
    union {
        __IO uint32_t intclr;
        struct {
            __IO uint32_t cmdfail              : 1; /* [0] */
            __IO uint32_t dtfail               : 1; /* [1] */
            __IO uint32_t cmdtimeout           : 1; /* [2] */
            __IO uint32_t dttimeout            : 1; /* [3] */
            __IO uint32_t txerru               : 1; /* [4] */
            __IO uint32_t rxerro               : 1; /* [5] */
            __IO uint32_t cmdrspcmpl           : 1; /* [6] */
            __IO uint32_t cmdcmpl              : 1; /* [7] */
            __IO uint32_t dtcmpl               : 1; /* [8] */
            __IO uint32_t sbiterr              : 1; /* [9] */
            __IO uint32_t dtblkcmpl            : 1; /* [10] */
            __IO uint32_t reserved1            : 11;/* [21:11] */
            __IO uint32_t ioif                 : 1; /* [22] */
            __IO uint32_t reserved2            : 9; /* [31:23] */
        } intclr_bit;
    };

    /**
      * @brief sdio inten register, offset:0x3C
      */
    union {
        __IO uint32_t inten;
        struct {
            __IO uint32_t cmdfailien           : 1; /* [0] */
            __IO uint32_t dtfailien            : 1; /* [1] */
            __IO uint32_t cmdtimeoutien        : 1; /* [2] */
            __IO uint32_t dttimeoutien         : 1; /* [3] */
            __IO uint32_t txerruien            : 1; /* [4] */
            __IO uint32_t rxerroien            : 1; /* [5] */
            __IO uint32_t cmdrspcmplien        : 1; /* [6] */
            __IO uint32_t cmdcmplien           : 1; /* [7] */
            __IO uint32_t dtcmplien            : 1; /* [8] */
            __IO uint32_t sbiterrien           : 1; /* [9] */
            __IO uint32_t dtblkcmplien         : 1; /* [10] */
            __IO uint32_t docmdien             : 1; /* [11] */
            __IO uint32_t dotxien              : 1; /* [12] */
            __IO uint32_t dorxien              : 1; /* [13] */
            __IO uint32_t txbufhien            : 1; /* [14] */
            __IO uint32_t rxbufhien            : 1; /* [15] */
            __IO uint32_t txbuffien            : 1; /* [16] */
            __IO uint32_t rxbuffien            : 1; /* [17] */
            __IO uint32_t txbufeien            : 1; /* [18] */
            __IO uint32_t rxbufeien            : 1; /* [19] */
            __IO uint32_t txbufien             : 1; /* [20] */
            __IO uint32_t rxbufien             : 1; /* [21] */
            __IO uint32_t ioifien              : 1; /* [22] */
            __IO uint32_t reserved1            : 9; /* [31:23] */
        } inten_bit;
    };

    /**
      * @brief sdio reserved1 register, offset:0x40~0x44
      */
    __IO uint32_t reserved1[2];

    /**
      * @brief sdio bufcnt register, offset:0x48
      */
    union {
        __IO uint32_t bufcnt;
        struct {
            __IO uint32_t cnt                  : 24;/* [23:0] */
            __IO uint32_t reserved1            : 8; /* [31:24] */
        } bufcnt_bit;
    };

    /**
      * @brief sdio reserved2 register, offset:0x4C~0x7C
      */
    __IO uint32_t reserved2[13];

    /**
      * @brief sdio buf register, offset:0x80
      */
    union {
        __IO uint32_t buf;
        struct {
            __IO uint32_t dt                   : 32;/* [31:0] */
        } buf_bit;
    };

} SDIO_Type;

/**
  * @}
  */
#define SDIO1                            ((SDIO_Type *) SDIO1_BASE)
#define SDIO2                            ((SDIO_Type *) SDIO2_BASE)

/** @defgroup SDIO_exported_functions
  * @{
  */

void SDIO_Reset(SDIO_Type *SDIO_x);
void SDIO_Power_Set(SDIO_Type *SDIO_x, SDIO_Power_State_Type power_state);
SDIO_Power_State_Type SDIO_Power_Status_Get(SDIO_Type *SDIO_x);
void SDIO_Clock_Config(SDIO_Type *SDIO_x, uint16_t clk_div, SDIO_Edge_phase_Type clk_edg);
void SDIO_Bus_Width_Config(SDIO_Type *SDIO_x, SDIO_Bus_Width_Type width);
void SDIO_Clock_ByPass(SDIO_Type *SDIO_x, confirm_state new_state);
void SDIO_Power_Saving_Mode_Enable(SDIO_Type *SDIO_x, confirm_state new_state);
void SDIO_Flow_Control_Enable(SDIO_Type *SDIO_x, confirm_state new_state);
void SDIO_Clock_Enable(SDIO_Type *SDIO_x, confirm_state new_state);
void SDIO_DMA_Enable(SDIO_Type *SDIO_x, confirm_state new_state);
void SDIO_Interrupt_Enable(SDIO_Type *SDIO_x, uint32_t int_opt,  confirm_state new_state);
flag_status SDIO_Flag_Get(SDIO_Type *SDIO_x, uint32_t flag);
void SDIO_Flag_Clear(SDIO_Type *SDIO_x, uint32_t flag);
void SDIO_Command_Config(SDIO_Type *SDIO_x, SDIO_Command_struct_Type *command_struct);
void SDIO_Command_State_Machine_Enable(SDIO_Type *SDIO_x, confirm_state new_state);
uint8_t SDIO_Command_Response_Get(SDIO_Type *SDIO_x);
uint32_t SDIO_Response_Get(SDIO_Type *SDIO_x, SDIO_rsp_index_Type reg_index);
void SDIO_Data_Config(SDIO_Type *SDIO_x, SDIO_Data_struct_Type *data_struct);
void SDIO_Data_State_Machine_Enable(SDIO_Type *SDIO_x, confirm_state new_state);
uint32_t SDIO_Data_Counter_Get(SDIO_Type *SDIO_x);
uint32_t SDIO_Data_Read(SDIO_Type *SDIO_x);
uint32_t SDIO_Buffer_Counter_Get(SDIO_Type *SDIO_x);
void SDIO_Data_Write(SDIO_Type *SDIO_x, uint32_t data);
void SDIO_Read_Wait_Mode_Set(SDIO_Type *SDIO_x, SDIO_Read_Wait_Mode_Type mode);
void SDIO_Read_Wait_Start(SDIO_Type *SDIO_x, confirm_state new_state);
void SDIO_Read_Wait_stop(SDIO_Type *SDIO_x, confirm_state new_state);
void SDIO_IO_Function_Enable(SDIO_Type *SDIO_x, confirm_state new_state);
void SDIO_IO_Suspend_Command_Set(SDIO_Type *SDIO_x, confirm_state new_state);

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
