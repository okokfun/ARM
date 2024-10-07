/**
  **************************************************************************
  * @file     at32f435_437_i2c.h
  * @brief    at32f435_437 i2c header file
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
#ifndef __AT32F435_437_I2C_H
#define __AT32F435_437_I2C_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup I2C
  */

/**
  * @brief maximum number of single transfers
  */
#define MAX_Transfer_CNT                 255 /*!< maximum number of single transfers */

/** @defgroup I2C_Interrupts_definition
  * @brief i2c interrupt
  */
#define I2C_TD_INT                       ((uint32_t)0x00000002) /*!< i2c transmit data 中断 */
#define I2C_RD_INT                       ((uint32_t)0x00000004) /*!< i2c receive data 中断 */
#define I2C_Addr_INT                     ((uint32_t)0x00000008) /*!< i2c address match 中断 */
#define I2C_ACKFIAL_INT                  ((uint32_t)0x00000010) /*!< i2c ack fail 中断 */
#define I2C_Stop_INT                     ((uint32_t)0x00000020) /*!< i2c stop detect 中断 */
#define I2C_TDC_INT                      ((uint32_t)0x00000040) /*!< i2c transmit data complete 中断 */
#define I2C_ERR_INT                      ((uint32_t)0x00000080) /*!< i2c bus error 中断 */

/** @defgroup I2C_flags_definition
  * @brief i2c flag
  */
#define  I2C_TDBE_FLAG                   ((uint32_t)0x00000001) /*!< i2c transmit data buffer empty flag */
#define  I2C_TDIS_FLAG                   ((uint32_t)0x00000002) /*!< i2c send interrupt status */
#define  I2C_RDBF_FLAG                   ((uint32_t)0x00000004) /*!< i2c receive data buffer full flag */
#define  I2C_AddrF_FLAG                  ((uint32_t)0x00000008) /*!< i2c 0~7 bit address match flag */
#define  I2C_ACKFAIL_FLAG                ((uint32_t)0x00000010) /*!< i2c acknowledge failure flag */
#define  I2C_STOPF_FLAG                  ((uint32_t)0x00000020) /*!< i2c stop condition generation complete flag */
#define  I2C_TDC_FLAG                    ((uint32_t)0x00000040) /*!< i2c transmit data complete flag */
#define  I2C_TCRLD_FLAG                  ((uint32_t)0x00000080) /*!< i2c transmission is complete, waiting to load data */
#define  I2C_BUSERR_FLAG                 ((uint32_t)0x00000100) /*!< i2c bus error flag */
#define  I2C_ARLOST_FLAG                 ((uint32_t)0x00000200) /*!< i2c arbitration lost flag */
#define  I2C_OUF_FLAG                    ((uint32_t)0x00000400) /*!< i2c overflow or underflow flag */
#define  I2C_PECERR_FLAG                 ((uint32_t)0x00000800) /*!< i2c pec receive error flag */
#define  I2C_TMOUT_FLAG                  ((uint32_t)0x00001000) /*!< i2c smbus timeout flag */
#define  I2C_ALERTF_FLAG                 ((uint32_t)0x00002000) /*!< i2c smbus alert flag */
#define  I2C_BUSYF_FLAG                  ((uint32_t)0x00008000) /*!< i2c bus busy flag transmission mode */
#define  I2C_SDIR_FLAG                   ((uint32_t)0x00010000) /*!< i2c slave data transmit direction */

/** @defgroup I2C_exported_Types
  */

/**
  * @brief i2c smbus mode set
  */
typedef enum {
    I2C_SmBus_Mode_DEVICE                  = 0x00, /*!< smbus device mode */
    I2C_SmBus_Mode_HOST                    = 0x01  /*!< smbus host mode */
} I2C_SmBus_Mode_Type;

/**
  * @brief i2c address mode
  */
typedef enum {
    I2C_Address_Mode_7BIT                  = 0x00, /*!< 7bit address mode */
    I2C_Address_Mode_10BIT                 = 0x01  /*!< 10bit address mode */
} I2C_Address_Mode_Type;

/**
  * @brief i2c transfer direction
  */
typedef enum {
    I2C_Dir_Transmit                       = 0x00, /*!< master 请求写入传输 */
    I2C_Dir_Receive                        = 0x01  /*!< master 请求读取传输 */
} I2C_Transfer_Dir_Type;

/**
  * @brief i2c dma requests direction
  */
typedef enum {
    I2C_DMA_Request_TX                     = 0x00, /*!< dma transmit request */
    I2C_DMA_Request_RX                     = 0x01  /*!< dma receive request */
} I2C_DMA_Request_Type;

/**
  * @brief i2c smbus alert pin set
  */
typedef enum {
    I2C_SmBus_Alert_HIGH                   = 0x00, /*!< smbus alert pin set high */
    I2C_SmBus_Alert_LOW                    = 0x01  /*!< smbus alert pin set low */
} I2C_SmBus_Alert_Set_Type;

/**
  * @brief i2c clock timeout detection mode
  */
typedef enum {
    I2C_TimeOut_Detcet_LOW                 = 0x00, /*!< detect low level timeout */
    I2C_TimeOut_Detcet_HIGH                = 0x01  /*!< detect high level timeout */
} I2C_TimeOut_Detcet_Type;

/**
  * @brief i2c own address2 mask
  */
typedef enum {
    I2C_Addr2_NOMASK                       = 0x00, /*!< compare bit      [7:1] */
    I2C_Addr2_MASK01                       = 0x01, /*!< only compare bit [7:2] */
    I2C_Addr2_MASK02                       = 0x02, /*!< only compare bit [7:2] */
    I2C_Addr2_MASK03                       = 0x03, /*!< only compare bit [7:3] */
    I2C_Addr2_MASK04                       = 0x04, /*!< only compare bit [7:4] */
    I2C_Addr2_MASK05                       = 0x05, /*!< only compare bit [7:5] */
    I2C_Addr2_MASK06                       = 0x06, /*!< only compare bit [7:6] */
    I2C_Addr2_MASK07                       = 0x07  /*!< only compare bit [7] */
} I2C_Addr2_Mask_Type;

/**
  * @brief i2c reload end mode
  */
typedef enum {
    I2C_Auto_Stop_Mode                     = 0x02000000, /*!< auto generate stop mode */
    I2C_SOFT_Stop_Mode                     = 0x00000000, /*!< soft generate stop mode */
    I2C_Reload_Mode                        = 0x01000000  /*!< reload mode */
} I2C_Reload_Stop_Mode_Type;

/**
  * @brief i2c start mode
  */
typedef enum {
    I2C_WITHOUT_Start                      = 0x00000000, /*!< transfer data without start condition */
    I2C_Gen_Start_Read                     = 0x00002400, /*!< read data and generate start */
    I2C_Gen_Start_Write                    = 0x00002000  /*!< send data and generate start */
} I2C_Start_Mode_Type;

/**
  * @brief type define i2c register all
  */
typedef struct {
    /**
      * @brief i2c ctrl1 register, offset:0x00
      */
    union {
        __IO uint32_t ctrl1;
        struct {
            __IO uint32_t i2cen                : 1; /* [0] */
            __IO uint32_t tdien                : 1; /* [1] */
            __IO uint32_t rdien                : 1; /* [2] */
            __IO uint32_t addrien              : 1; /* [3] */
            __IO uint32_t ackfailien           : 1; /* [4] */
            __IO uint32_t stopien              : 1; /* [5] */
            __IO uint32_t tdcien               : 1; /* [6] */
            __IO uint32_t errien               : 1; /* [7] */
            __IO uint32_t dflt                 : 4; /* [11:8] */
            __IO uint32_t reserved1            : 2; /* [13:12] */
            __IO uint32_t dmaten               : 1; /* [14] */
            __IO uint32_t dmaren               : 1; /* [15] */
            __IO uint32_t sctrl                : 1; /* [16] */
            __IO uint32_t stretch              : 1; /* [17] */
            __IO uint32_t reserved2            : 1; /* [18] */
            __IO uint32_t gcaen                : 1; /* [19] */
            __IO uint32_t haddren              : 1; /* [20] */
            __IO uint32_t devaddren            : 1; /* [21] */
            __IO uint32_t smbalert             : 1; /* [22] */
            __IO uint32_t pecen                : 1; /* [23] */
            __IO uint32_t reserved3            : 8; /* [31:24] */
        } ctrl1_bit;
    };

    /**
      * @brief i2c ctrl2 register, offset:0x04
      */
    union {
        __IO uint32_t ctrl2;
        struct {
            __IO uint32_t saddr                : 10;/* [9:0] */
            __IO uint32_t dir                  : 1; /* [10] */
            __IO uint32_t addr10               : 1; /* [11] */
            __IO uint32_t readh10              : 1; /* [12] */
            __IO uint32_t genstart             : 1; /* [13] */
            __IO uint32_t genstop              : 1; /* [14] */
            __IO uint32_t nacken               : 1; /* [15] */
            __IO uint32_t cnt                  : 8; /* [23:16] */
            __IO uint32_t rlden                : 1; /* [24] */
            __IO uint32_t astopen              : 1; /* [25] */
            __IO uint32_t pecten               : 1; /* [26] */
            __IO uint32_t reserved1            : 5; /* [31:27] */
        } ctrl2_bit;
    };

    /**
      * @brief i2c oaddr1 register, offset:0x08
      */
    union {
        __IO uint32_t oaddr1;
        struct {
            __IO uint32_t addr1                : 10;/* [9:0] */
            __IO uint32_t addr1mode            : 1; /* [10] */
            __IO uint32_t reserved1            : 4; /* [14:11] */
            __IO uint32_t addr1en              : 1; /* [15] */
            __IO uint32_t reserved2            : 16;/* [31:16] */
        } oaddr1_bit;
    };

    /**
      * @brief i2c oaddr2 register, offset:0x0c
      */
    union {
        __IO uint32_t oaddr2;
        struct {
            __IO uint32_t reserved1            : 1; /* [0] */
            __IO uint32_t addr2                : 7; /* [7:1] */
            __IO uint32_t addr2mask            : 3; /* [10:8] */
            __IO uint32_t reserved2            : 4; /* [14:11] */
            __IO uint32_t addr2en              : 1; /* [15] */
            __IO uint32_t reserved3            : 16;/* [31:16] */
        } oaddr2_bit;
    };

    /**
      * @brief i2c clkctrl register, offset:0x10
      */
    union {
        __IO uint32_t clkctrl;
        struct {
            __IO uint32_t scll                 : 8; /* [7:0] */
            __IO uint32_t sclh                 : 8; /* [15:8] */
            __IO uint32_t sdad                 : 4; /* [19:16] */
            __IO uint32_t scld                 : 4; /* [23:20] */
            __IO uint32_t divh                 : 4; /* [27:24] */
            __IO uint32_t divl                 : 4; /* [31:28] */
        } clkctrl_bit;
    };

    /**
      * @brief i2c timeout register, offset:0x14
      */
    union {
        __IO uint32_t timeout;
        struct {
            __IO uint32_t totime               : 12;/* [11:0] */
            __IO uint32_t tomode               : 1; /* [12] */
            __IO uint32_t reserved1            : 2; /* [14:13] */
            __IO uint32_t toen                 : 1; /* [15] */
            __IO uint32_t exttime              : 12;/* [27:16] */
            __IO uint32_t reserved2            : 3; /* [30:28] */
            __IO uint32_t exten                : 1; /* [31] */
        } timeout_bit;
    };

    /**
      * @brief i2c sts register, offset:0x18
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t tdbe                 : 1; /* [0] */
            __IO uint32_t tdis                 : 1; /* [1] */
            __IO uint32_t rdbf                 : 1; /* [2] */
            __IO uint32_t addrf                : 1; /* [3] */
            __IO uint32_t ackfail              : 1; /* [4] */
            __IO uint32_t stopf                : 1; /* [5] */
            __IO uint32_t tdc                  : 1; /* [6] */
            __IO uint32_t tcrld                : 1; /* [7] */
            __IO uint32_t buserr               : 1; /* [8] */
            __IO uint32_t arlost               : 1; /* [9] */
            __IO uint32_t ouf                  : 1; /* [10] */
            __IO uint32_t pecerr               : 1; /* [11] */
            __IO uint32_t tmout                : 1; /* [12] */
            __IO uint32_t alertf               : 1; /* [13] */
            __IO uint32_t reserved1            : 1; /* [14] */
            __IO uint32_t busyf                : 1; /* [15] */
            __IO uint32_t sdir                 : 1; /* [16] */
            __IO uint32_t addr                 : 7; /* [23:17] */
            __IO uint32_t reserved2            : 8; /* [31:24] */
        } sts_bit;
    };

    /**
      * @brief i2c clr register, offset:0x1c
      */
    union {
        __IO uint32_t clr;
        struct {
            __IO uint32_t reserved1            : 3; /* [2:0] */
            __IO uint32_t addrc                : 1; /* [3] */
            __IO uint32_t ackfailc             : 1; /* [4] */
            __IO uint32_t stopc                : 1; /* [5] */
            __IO uint32_t reserved2            : 2; /* [6:7] */
            __IO uint32_t buserrc              : 1; /* [8] */
            __IO uint32_t arlostc              : 1; /* [9] */
            __IO uint32_t oufc                 : 1; /* [10] */
            __IO uint32_t pecerrc              : 1; /* [11] */
            __IO uint32_t tmoutc               : 1; /* [12] */
            __IO uint32_t alertc               : 1; /* [13] */
            __IO uint32_t reserved3            : 18;/* [31:14] */
        } clr_bit;
    };

    /**
      * @brief i2c pec register, offset:0x20
      */
    union {
        __IO uint32_t pec;
        struct {
            __IO uint32_t pecval               : 8; /* [7:0] */
            __IO uint32_t reserved1            : 24;/* [31:8] */
        } pec_bit;
    };

    /**
      * @brief i2c rxdt register, offset:0x20
      */
    union {
        __IO uint32_t rxdt;
        struct {
            __IO uint32_t dt                   : 8; /* [7:0] */
            __IO uint32_t reserved1            : 24;/* [31:8] */
        } rxdt_bit;
    };

    /**
      * @brief i2c txdt register, offset:0x20
      */
    union {
        __IO uint32_t txdt;
        struct {
            __IO uint32_t dt                   : 8; /* [7:0] */
            __IO uint32_t reserved1            : 24;/* [31:8] */
        } txdt_bit;
    };

} I2C_Type;
#define I2C1                             ((I2C_Type *) I2C1_BASE)
#define I2C2                             ((I2C_Type *) I2C2_BASE)
#define I2C3                             ((I2C_Type *) I2C3_BASE)

/** @defgroup I2C_exported_functions
  */
void I2C_Reset(I2C_Type *I2C_x);
void I2C_Init(I2C_Type *I2C_x, uint8_t dfilters, uint32_t clk);
void I2C_Own_Address1_Set(I2C_Type *I2C_x, I2C_Address_Mode_Type mode, uint16_t address);
void I2C_Own_Address2_Set(I2C_Type *I2C_x, uint8_t address, I2C_Addr2_Mask_Type mask);
void I2C_Own_Address2_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_SmBus_Enable(I2C_Type *I2C_x, I2C_SmBus_Mode_Type mode, confirm_state new_state);
void I2C_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_Clock_Stretch_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_ACK_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_Addr10_Mode_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_Transfer_Addr_Set(I2C_Type *I2C_x, uint16_t address);
uint16_t I2C_Transfer_Addr_Get(I2C_Type *I2C_x);
void I2C_Transfer_Dir_Set(I2C_Type *I2C_x, I2C_Transfer_Dir_Type I2C_direction);
I2C_Transfer_Dir_Type I2C_Transfer_Dir_Get(I2C_Type *I2C_x);
uint8_t I2C_Matched_Addr_Get(I2C_Type *I2C_x);
void I2C_Auto_Stop_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_Reload_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_CNT_Set(I2C_Type *I2C_x, uint8_t cnt);
void I2C_Addr10_header_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_General_Call_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_SmBus_Alert_Set(I2C_Type *I2C_x, I2C_SmBus_Alert_Set_Type level);
void I2C_Slave_Data_Ctrl_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_PEC_Calculate_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_PEC_Transmit_Enable(I2C_Type *I2C_x, confirm_state new_state);
uint8_t I2C_PEC_Value_Get(I2C_Type *I2C_x);
void I2C_TimeOut_Set(I2C_Type *I2C_x, uint16_t timeout);
void I2C_TimeOut_Detcet_Set(I2C_Type *I2C_x, I2C_TimeOut_Detcet_Type mode);
void I2C_TimeOut_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_Ext_TimeOut_Set(I2C_Type *I2C_x, uint16_t timeout);
void I2C_Ext_TimeOut_Enable(I2C_Type *I2C_x, confirm_state new_state);
void I2C_Interrupt_Enable(I2C_Type *I2C_x, uint32_t source, confirm_state new_state);
flag_status I2C_Interrupt_Get(I2C_Type *I2C_x, uint16_t source);
void I2C_DMA_Enable(I2C_Type *I2C_x, I2C_DMA_Request_Type DMA_req, confirm_state new_state);
void I2C_Transmit_Set(I2C_Type *I2C_x, uint16_t address, uint8_t cnt, I2C_Reload_Stop_Mode_Type rld_stop, I2C_Start_Mode_Type start);
void I2C_Start_Generate(I2C_Type *I2C_x);
void I2C_Stop_Generate(I2C_Type *I2C_x);
void I2C_Data_Send(I2C_Type *I2C_x, uint8_t data);
uint8_t I2C_Data_Receive(I2C_Type *I2C_x);
flag_status I2C_Flag_Get(I2C_Type *I2C_x, uint32_t flag);
void I2C_Flag_Clear(I2C_Type *I2C_x, uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif
