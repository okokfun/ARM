/**
  **************************************************************************
  * @file     at32f435_437_qspi.h
  * @brief    at32f435_437 qspi header file
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
#ifndef __AT32F435_437_QSPI_H
#define __AT32F435_437_QSPI_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup QSPI
  * @{
  */

/** @defgroup QSPI_flags_definition
  * @brief qspi flag
  * @{
  */
#define QSPI_CMDSTS_FLAG                 ((uint32_t)0x00000001) /*!< qspi command complete status flag */
#define QSPI_RXFIFORDY_FLAG              ((uint32_t)0x00000002) /*!< qspi rxfifo ready status flag */
#define QSPI_TXFIFORDY_FLAG              ((uint32_t)0x00000004) /*!< qspi txfifo ready status flag */

/**
  * @}
  */

/** @defgroup QSPI_exported_Types
  * @{
  */

/**
  * @brief qspi xip read access mode type
  */
typedef enum {
    QSPI_XIPR_SEL_ModeD                    = 0x00, /*!< qspi xip read select mode d */
    QSPI_XIPR_SEL_ModeT                    = 0x01  /*!< qspi xip read select mode t */
} QSPI_Xip_Read_sel_Type;

/**
  * @brief qspi xip write access mode type
  */
typedef enum {
    QSPI_XIPW_SEL_ModeD                    = 0x00, /*!< qspi xip write select mode d */
    QSPI_XIPW_SEL_ModeT                    = 0x01  /*!< qspi xip write select mode t */
} QSPI_Xip_Write_sel_Type;

/**
  * @brief qspi busy bit offset position in status register type
  */
typedef enum {
    QSPI_Busy_Offset_0                     = 0x00, /*!< qspi busy bit offset position 0 */
    QSPI_Busy_Offset_1                     = 0x01, /*!< qspi busy bit offset position 1 */
    QSPI_Busy_Offset_2                     = 0x02, /*!< qspi busy bit offset position 2 */
    QSPI_Busy_Offset_3                     = 0x03, /*!< qspi busy bit offset position 3 */
    QSPI_Busy_Offset_4                     = 0x04, /*!< qspi busy bit offset position 4 */
    QSPI_Busy_Offset_5                     = 0x05, /*!< qspi busy bit offset position 5 */
    QSPI_Busy_Offset_6                     = 0x06, /*!< qspi busy bit offset position 6 */
    QSPI_Busy_Offset_7                     = 0x07  /*!< qspi busy bit offset position 7 */
} QSPI_Busy_pos_Type;

/**
  * @brief qspi read status configure type
  */
typedef enum {
    QSPI_RSTSC_HW_AUTO                     = 0x00, /*!< qspi read status by hardware */
    QSPI_RSTSC_SW_ONCE                     = 0x01  /*!< qspi read status by software */
} QSPI_Read_Status_conf_Type;

/**
  * @brief qspi operate mode type
  */
typedef enum {
    QSPI_OPERATE_Mode_111                  = 0x00, /*!< qspi serial mode */
    QSPI_OPERATE_Mode_112                  = 0x01, /*!< qspi dual mode */
    QSPI_OPERATE_Mode_114                  = 0x02, /*!< qspi quad mode */
    QSPI_OPERATE_Mode_122                  = 0x03, /*!< qspi dual i/o mode */
    QSPI_OPERATE_Mode_144                  = 0x04, /*!< qspi quad i/o mode */
    QSPI_OPERATE_Mode_222                  = 0x05, /*!< qspi instruction 2-bit mode */
    QSPI_OPERATE_Mode_444                  = 0x06  /*!< qspi instruction 4-bit mode(qpi) */
} QSPI_operate_Mode_Type;

/**
  * @brief qspi clock division type
  */
typedef enum {
    QSPI_CLK_Div_2                         = 0x00, /*!< qspi clk divide by 2 */
    QSPI_CLK_Div_4                         = 0x01, /*!< qspi clk divide by 4 */
    QSPI_CLK_Div_6                         = 0x02, /*!< qspi clk divide by 6 */
    QSPI_CLK_Div_8                         = 0x03, /*!< qspi clk divide by 8 */
    QSPI_CLK_Div_3                         = 0x04, /*!< qspi clk divide by 3 */
    QSPI_CLK_Div_5                         = 0x05, /*!< qspi clk divide by 5 */
    QSPI_CLK_Div_10                        = 0x06, /*!< qspi clk divide by 10 */
    QSPI_CLK_Div_12                        = 0x07  /*!< qspi clk divide by 12 */
} QSPI_CLK_Div_Type;

/**
  * @brief qspi command port address length type
  */
typedef enum {
    QSPI_CMD_ADRLEN_0_BYTE                 = 0x00, /*!< qspi  no address */
    QSPI_CMD_ADRLEN_1_BYTE                 = 0x01, /*!< qspi  address length 1 byte */
    QSPI_CMD_ADRLEN_2_BYTE                 = 0x02, /*!< qspi  address length 2 byte */
    QSPI_CMD_ADRLEN_3_BYTE                 = 0x03, /*!< qspi  address length 3 byte */
    QSPI_CMD_ADRLEN_4_BYTE                 = 0x04  /*!< qspi  address length 4 byte */
} QSPI_CMD_adrlen_Type;

/**
  * @brief qspi command port instruction length type
  */
typedef enum {
    QSPI_CMD_INSLEN_0_BYTE                 = 0x00, /*!< qspi no instruction code */
    QSPI_CMD_INSLEN_1_BYTE                 = 0x01, /*!< qspi instruction code 1 byte */
    QSPI_CMD_INSLEN_2_BYTE                 = 0x02  /*!< qspi instruction code 2 byte(repeat) */
} QSPI_CMD_inslen_Type;

/**
  * @brief qspi xip r/w address length type
  */
typedef enum {
    QSPI_Xip_AddrLEN_3_BYTE                = 0x00, /*!< qspi xip address length 3 byte */
    QSPI_Xip_AddrLEN_4_BYTE                = 0x01  /*!< qspi xip address length 4 byte */
} QSPI_Xip_Addrlen_Type;

/**
  * @brief qspi sckout mode type
  */
typedef enum {
    QSPI_SCK_Mode_0                        = 0x00, /*!< qspi sck mode 0 */
    QSPI_SCK_Mode_3                        = 0x01  /*!< qspi sck mode 3 */
} QSPI_CLK_Mode_Type;

/**
  * @brief qspi dma tx/rx fifo threshold type
  */
typedef enum {
    QSPI_DMA_FIFO_THOD_WORD08              = 0x00, /*!< qspi dma fifo threshold 8 words */
    QSPI_DMA_FIFO_THOD_WORD16              = 0x01, /*!< qspi dma fifo threshold 16 words */
    QSPI_DMA_FIFO_THOD_WORD32              = 0x02  /*!< qspi dma fifo threshold 32 words */
} QSPI_DMA_FIFO_thod_Type;

/**
  * @brief qspi cmd type
  */
typedef struct {
    confirm_state                          pe_Mode_Enable;          /*!< perfornance enhance mode enable */
    uint8_t                                pe_Mode_operate_code;    /*!< performance enhance mode operate code */
    uint8_t                                instruction_code;        /*!< instruction code */
    QSPI_CMD_inslen_Type                   instruction_length;      /*!< instruction code length */
    uint32_t                               address_code;            /*!< address code */
    QSPI_CMD_adrlen_Type                   address_length;          /*!< address legnth */
    uint32_t                               data_counter;            /*!< read/write data counter */
    uint8_t                                second_dummy_Cycle_Num;  /*!< number of second dummy state cycle 0~32 */
    QSPI_operate_Mode_Type                 operation_Mode;          /*!< operation mode */
    QSPI_Read_Status_conf_Type             read_Status_Config;      /*!< config to read status */
    confirm_state                          read_Status_Enable;      /*!< config to read status */
    confirm_state                          write_Data_Enable;       /*!< enable to write data */
} QSPI_CMD_Type;

/**
  * @brief qspi xip type
  */
typedef struct {
    uint8_t                                read_instruction_code;         /*!< read instruction code */
    QSPI_Xip_Addrlen_Type                  read_Address_length;           /*!< read address legnth */
    QSPI_operate_Mode_Type                 read_Operation_Mode;           /*!< read operation mode */
    uint8_t                                read_Second_dummy_Cycle_Num;   /*!< read number of second dummy state cycle 0~32 */
    uint8_t                                write_instruction_code;        /*!< write instruction code */
    QSPI_Xip_Addrlen_Type                  write_Address_length;          /*!< write address legnth */
    QSPI_operate_Mode_Type                 write_Operation_Mode;          /*!< write operation mode */
    uint8_t                                write_Second_dummy_Cycle_Num;  /*!< write number of second dummy state cycle 0~32 */
    QSPI_Xip_Write_sel_Type                write_Select_Mode;             /*!< write mode d or mode t selection */
    uint8_t                                write_Time_counter;            /*!< write count for mode t */
    uint8_t                                write_Data_counter;            /*!< write count for mode d */
    QSPI_Xip_Read_sel_Type                 read_Select_Mode;              /*!< read mode d or mode t selection */
    uint8_t                                read_Time_counter;             /*!< read count for mode t */
    uint8_t                                read_Data_counter;             /*!< read count for mode d */
} QSPI_Xip_Type;

/**
  * @brief type define qspi register all
  */
typedef struct {
    /**
      * @brief qspi cmd_w0 register, offset:0x00
      */
    union {
        __IO uint32_t cmd_w0;
        struct {

            __IO uint32_t spiadr               : 32;/* [31:0] */
        } cmd_w0_bit;
    };

    /**
      * @brief qspi cmd_w1 register, offset:0x04
      */
    union {
        __IO uint32_t cmd_w1;
        struct {
            __IO uint32_t adrlen               : 3; /* [2:0] */
            __IO uint32_t reserved1            : 13;/* [15:3] */
            __IO uint32_t dum2                 : 8; /* [23:16] */
            __IO uint32_t inslen               : 2; /* [25:24] */
            __IO uint32_t reserved2            : 2; /* [27:26] */
            __IO uint32_t pemen                : 1; /* [28] */
            __IO uint32_t reserved3            : 3; /* [31:29] */
        } cmd_w1_bit;
    };

    /**
      * @brief qspi cmd_w2 register, offset:0x08
      */
    union {
        __IO uint32_t cmd_w2;
        struct {
            __IO uint32_t dcnt                 : 32;/* [31:0] */
        } cmd_w2_bit;
    };

    /**
      * @brief qspi cmd_w3 register, offset:0x0C
      */
    union {
        __IO uint32_t cmd_w3;
        struct {
            __IO uint32_t reserved1            : 1; /* [0] */
            __IO uint32_t wen                  : 1; /* [1] */
            __IO uint32_t rstsen               : 1; /* [2] */
            __IO uint32_t rstsc                : 1; /* [3] */
            __IO uint32_t reserved2            : 1; /* [4] */
            __IO uint32_t opmode               : 3; /* [7:5] */
            __IO uint32_t reserved3            : 8; /* [15:8] */
            __IO uint32_t pemopc               : 8; /* [23:16] */
            __IO uint32_t insc                 : 8; /* [31:24] */
        } cmd_w3_bit;
    };

    /**
      * @brief qspi ctrl register, offset:0x10
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t clkdiv               : 3; /* [2:0] */
            __IO uint32_t reserved1            : 1; /* [3] */
            __IO uint32_t sckmode              : 1; /* [4] */
            __IO uint32_t reserved2            : 2; /* [6:5] */
            __IO uint32_t xipidle              : 1; /* [7] */
            __IO uint32_t abort                : 1; /* [8] */
            __IO uint32_t reserved3            : 7; /* [15:9] */
            __IO uint32_t busy                 : 3; /* [18:16] */
            __IO uint32_t xiprcmdf             : 1; /* [19] */
            __IO uint32_t xipsel               : 1; /* [20] */
            __IO uint32_t keyen                : 1; /* [21] */
            __IO uint32_t reserved4            : 10;/* [31:22] */
        } ctrl_bit;
    };

    /**
      * @brief qspi actr register, offset:0x14
      */
    union {
        __IO uint32_t actr;
        struct {
            __IO uint32_t csdly                : 4; /* [3:0] */
            __IO uint32_t reserved1            : 28;/* [31:4] */
        } actr_bit;
    };

    /**
      * @brief qspi fifosts register, offset:0x18
      */
    union {
        __IO uint32_t fifosts;
        struct {
            __IO uint32_t txfifordy            : 1; /* [0] */
            __IO uint32_t rxfifordy            : 1; /* [1] */
            __IO uint32_t reserved1            : 30;/* [31:2] */
        } fifosts_bit;
    };

    /**
      * @brief qspi reserved register, offset:0x1C
      */
    __IO uint32_t reserved1;

    /**
      * @brief qspi ctrl2 register, offset:0x20
      */
    union {
        __IO uint32_t ctrl2;
        struct {
            __IO uint32_t dmaen                : 1; /* [0] */
            __IO uint32_t cmdie                : 1; /* [1] */
            __IO uint32_t reserved1            : 6; /* [7:2] */
            __IO uint32_t txfifo_thod          : 2; /* [9:8] */
            __IO uint32_t reserved2            : 2; /* [11:10] */
            __IO uint32_t rxfifo_thod          : 2; /* [13:12] */
            __IO uint32_t reserved3            : 18;/* [31:14] */
        } ctrl2_bit;
    };

    /**
      * @brief qspi cmdsts register, offset:0x24
      */
    union {
        __IO uint32_t cmdsts;
        struct {
            __IO uint32_t cmdsts               : 1; /* [0] */
            __IO uint32_t reserved1            : 31;/* [31:1] */
        } cmdsts_bit;
    };

    /**
      * @brief qspi rsts register, offset:0x28
      */
    union {
        __IO uint32_t rsts;
        struct {
            __IO uint32_t spists               : 8; /* [7:0] */
            __IO uint32_t reserved1            : 24;/* [31:8] */
        } rsts_bit;
    };

    /**
      * @brief qspi fsize register, offset:0x2C
      */
    union {
        __IO uint32_t fsize;
        struct {
            __IO uint32_t spifsize             : 32;/* [31:0] */
        } fsize_bit;
    };

    /**
      * @brief qspi xip_CMD_w0 register, offset:0x30
      */
    union {
        __IO uint32_t xip_CMD_w0;
        struct {
            __IO uint32_t xipr_dum2            : 8; /* [7:0] */
            __IO uint32_t xipr_opmode          : 3; /* [10:8] */
            __IO uint32_t xipr_adrlen          : 1; /* [11] */
            __IO uint32_t xipr_insc            : 8; /* [19:12] */
            __IO uint32_t reserved1            : 12;/* [31:20] */
        } xip_CMD_w0_bit;
    };

    /**
      * @brief qspi xip_CMD_w1 register, offset:0x34
      */
    union {
        __IO uint32_t xip_CMD_w1;
        struct {
            __IO uint32_t xipr_dum2            : 8; /* [7:0] */
            __IO uint32_t xipr_opmode          : 3; /* [10:8] */
            __IO uint32_t xipr_adrlen          : 1; /* [11] */
            __IO uint32_t xipr_insc            : 8; /* [19:12] */
            __IO uint32_t reserved1            : 12;/* [31:20] */
        } xip_CMD_w1_bit;
    };

    /**
      * @brief qspi xip_CMD_w2 register, offset:0x38
      */
    union {
        __IO uint32_t xip_CMD_w2;
        struct {
            __IO uint32_t xipr_dcnt            : 6; /* [5:0] */
            __IO uint32_t reserved1            : 2; /* [7:6] */
            __IO uint32_t xipr_tcnt            : 7; /* [14:8] */
            __IO uint32_t xipr_sel             : 1; /* [15] */
            __IO uint32_t xipw_dcnt            : 6; /* [21:16] */
            __IO uint32_t reserved2            : 2; /* [23:22] */
            __IO uint32_t xipw_tcnt            : 7; /* [30:24] */
            __IO uint32_t xipw_sel             : 1; /* [31] */
        } xip_CMD_w2_bit;
    };

    /**
      * @brief qspi xip_CMD_w3 register, offset:0x3C
      */
    union {
        __IO uint32_t xip_CMD_w3;
        struct {
            __IO uint32_t bypassc             : 1; /* [0] */
            __IO uint32_t reserved1           : 2; /* [2:1] */
            __IO uint32_t csts                : 1; /* [3] */
            __IO uint32_t reserved2           : 28;/* [31:4] */
        } xip_CMD_w3_bit;
    };

    /**
      * @brief qspi reserved register, offset:0x40~4C
      */
    __IO uint32_t reserved2[4];

    /**
      * @brief qspi rev register, offset:0x50
      */
    union {
        __IO uint32_t rev;
        struct {
            __IO uint32_t rev                  : 32;/* [31:0] */
        } rev_bit;
    };

    /**
      * @brief qspi reserved register, offset:0x54~FC
      */
    __IO uint32_t reserved3[43];

    /**
      * @brief qspi dt register, offset:0x100
      */
    union {
        __IO uint8_t  dt_u8;
        __IO uint16_t dt_u16;
        __IO uint32_t dt;
        struct {
            __IO uint32_t dt                   : 32;/* [31:0] */
        } dt_bit;
    };

} QSPI_Type;

/**
  * @}
  */
#define QSPI1                            ((QSPI_Type*)QSPI1_REG_BASE)
#define QSPI2                            ((QSPI_Type*)QSPI2_REG_BASE)

/** @defgroup QSPI_exported_functions
  * @{
  */

void QSPI_Encryption_Enable(QSPI_Type* QSPI_x, confirm_state new_state);
void QSPI_SCK_Mode_Set(QSPI_Type* QSPI_x, QSPI_CLK_Mode_Type new_Mode);
void QSPI_CLK_Division_Set(QSPI_Type* QSPI_x, QSPI_CLK_Div_Type new_CLKdiv);
void QSPI_Xip_Cache_ByPass_Set(QSPI_Type* QSPI_x, confirm_state new_state);
void QSPI_Interrupt_Enable(QSPI_Type* QSPI_x, confirm_state new_state);
flag_status QSPI_Flag_Get(QSPI_Type* QSPI_x, uint32_t flag);
void QSPI_Flag_Clear(QSPI_Type* QSPI_x, uint32_t flag);
void QSPI_DMA_RX_Threshold_Set(QSPI_Type* QSPI_x, QSPI_DMA_FIFO_thod_Type new_threshold);
void QSPI_DMA_TX_Threshold_Set(QSPI_Type* QSPI_x, QSPI_DMA_FIFO_thod_Type new_threshold);
void QSPI_DMA_Enable(QSPI_Type* QSPI_x, confirm_state new_state);
void QSPI_Busy_Config(QSPI_Type* QSPI_x, QSPI_Busy_pos_Type busy_pos);
void QSPI_Xip_Enable(QSPI_Type* QSPI_x, confirm_state new_state);
void QSPI_CMD_Operation_kick(QSPI_Type* QSPI_x, QSPI_CMD_Type* QSPI_CMD_struct);
void QSPI_Xip_Init(QSPI_Type* QSPI_x, QSPI_Xip_Type* xip_Init_struct);
uint8_t QSPI_Byte_Read(QSPI_Type* QSPI_x);
uint16_t QSPI_Half_Word_Read(QSPI_Type* QSPI_x);
uint32_t QSPI_Word_Read(QSPI_Type* QSPI_x);
void QSPI_Word_Write(QSPI_Type* QSPI_x, uint32_t value);
void QSPI_Half_Word_Write(QSPI_Type* QSPI_x, uint16_t value);
void QSPI_Byte_Write(QSPI_Type* QSPI_x, uint8_t value);
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
