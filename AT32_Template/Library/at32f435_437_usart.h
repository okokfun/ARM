/**
  **************************************************************************
  * @file     at32f435_437_usart.h
  * @brief    at32f435_437 usart header file
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
#ifndef __AT32F435_437_USART_H
#define __AT32F435_437_USART_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup USART
  * @{
  */

/** @defgroup USART_flags_definition
  * @brief usart flag
  * @{
  */
#define USART_PERR_FLAG                  ((uint32_t)0x00000001) /*!< usart parity error flag */
#define USART_FERR_FLAG                  ((uint32_t)0x00000002) /*!< usart framing error flag */
#define USART_NERR_FLAG                  ((uint32_t)0x00000004) /*!< usart noise error flag */
#define USART_ROERR_FLAG                 ((uint32_t)0x00000008) /*!< usart receiver overflow error flag */
#define USART_IDLEF_FLAG                 ((uint32_t)0x00000010) /*!< usart idle flag */
#define USART_RDBF_FLAG                  ((uint32_t)0x00000020) /*!< usart receive data buffer full flag */
#define USART_TDC_FLAG                   ((uint32_t)0x00000040) /*!< usart transmit data complete flag */
#define USART_TDBE_FLAG                  ((uint32_t)0x00000080) /*!< usart transmit data buffer empty flag */
#define USART_BFF_FLAG                   ((uint32_t)0x00000100) /*!< usart break frame flag */
#define USART_CTSCF_FLAG                 ((uint32_t)0x00000200) /*!< usart cts change flag */

/**
  * @}
  */

/** @defgroup USART_Interrupts_definition
  * @brief usart interrupt
  * @{
  */
#define USART_IDLE_INT                   MAKE_VALUE(0x0C,0x04) /*!< usart idle 中断 */
#define USART_RDBF_INT                   MAKE_VALUE(0x0C,0x05) /*!< usart receive data buffer full 中断 */
#define USART_TDC_INT                    MAKE_VALUE(0x0C,0x06) /*!< usart transmit data complete 中断 */
#define USART_TDBE_INT                   MAKE_VALUE(0x0C,0x07) /*!< usart transmit data buffer empty 中断 */
#define USART_PERR_INT                   MAKE_VALUE(0x0C,0x08) /*!< usart parity error 中断 */
#define USART_BF_INT                     MAKE_VALUE(0x10,0x06) /*!< usart break frame 中断 */
#define USART_ERR_INT                    MAKE_VALUE(0x14,0x00) /*!< usart error 中断 */
#define USART_CTSCF_INT                  MAKE_VALUE(0x14,0x0A) /*!< usart cts change 中断 */

/**
  * @}
  */

/** @defgroup USART_exported_Types
  * @{
  */

/**
  * @brief  usart parity selection type
  */
typedef enum {
    USART_PARITY_NONE                      = 0x00, /*!< usart no parity */
    USART_PARITY_EVEN                      = 0x01, /*!< usart even parity */
    USART_PARITY_ODD                       = 0x02  /*!< usart odd parity */
} USART_parity_Selection_Type;

/**
  * @brief  usart wakeup mode type
  */
typedef enum {
    USART_WakeUp_BY_IDLE_Frame             = 0x00, /*!< usart wakeup by idle frame */
    USART_WakeUp_BY_MATCHING_ID            = 0x01  /*!< usart wakeup by matching id */
} USART_WakeUp_Mode_Type;

/**
  * @brief  usart data bit num type
  */
typedef enum {
    USART_Data_7BITS                       = 0x00, /*!< usart data size is 7 bits */
    USART_Data_8BITS                       = 0x01, /*!< usart data size is 8 bits */
    USART_Data_9BITS                       = 0x02  /*!< usart data size is 9 bits */
} USART_Data_Bit_Num_Type;

/**
  * @brief  usart break frame bit num type
  */
typedef enum {
    USART_Break_10BITS                     = 0x00, /*!< usart lin mode berak frame detection 10 bits */
    USART_Break_11BITS                     = 0x01  /*!< usart lin mode berak frame detection 11 bits */
} USART_Break_Bit_Num_Type;

/**
  * @brief  usart phase of the clock type
  */
typedef enum {
    USART_Clock_PHASE_1EDGE                = 0x00, /*!< usart data capture is done on the clock leading edge */
    USART_Clock_PHASE_2EDGE                = 0x01  /*!< usart data capture is done on the clock trailing edge */
} USART_Clock_phase_Type;

/**
  * @brief  usart polarity of the clock type
  */
typedef enum {
    USART_Clock_Polarity_LOW               = 0x00, /*!< usart clock stay low level outside transmission window */
    USART_Clock_Polarity_HIGH              = 0x01  /*!< usart clock stay high level outside transmission window */
} USART_Clock_Polarity_Type;

/**
  * @brief  usart last bit clock pulse type
  */
typedef enum {
    USART_Clock_LAST_Bit_NONE              = 0x00, /*!< usart clock pulse of the last data bit is not outputted */
    USART_Clock_LAST_Bit_OutPUT            = 0x01  /*!< usart clock pulse of the last data bit is outputted */
} USART_lbcp_Type;

/**
  * @brief  usart stop bit num type
  */
typedef enum {
    USART_Stop_1_BIT                       = 0x00, /*!< usart stop bits num is 1 */
    USART_Stop_0_5_BIT                     = 0x01, /*!< usart stop bits num is 0.5 */
    USART_Stop_2_BIT                       = 0x02, /*!< usart stop bits num is 2 */
    USART_Stop_1_5_BIT                     = 0x03  /*!< usart stop bits num is 1.5 */
} USART_Stop_Bit_Num_Type;

/**
  * @brief  usart hardware flow control type
  */
typedef enum {
    USART_Hardware_Flow_NONE               = 0x00, /*!< usart without hardware flow */
    USART_Hardware_Flow_RTS                = 0x01, /*!< usart hardware flow only rts */
    USART_Hardware_Flow_CTS                = 0x02, /*!< usart hardware flow only cts */
    USART_Hardware_Flow_RTS_CTS            = 0x03  /*!< usart hardware flow both rts and cts */
} USART_Hardware_Flow_Control_Type;

/**
  * @brief  usart identification bit num type
  */
typedef enum {
    USART_ID_FIXED_4_BIT                   = 0x00, /*!< usart id bit num fixed 4 bits */
    USART_ID_RELATED_Data_BIT              = 0x01  /*!< usart id bit num related data bits */
} USART_identification_Bit_Num_Type;

/**
  * @brief  usart de polarity type
  */
typedef enum {
    USART_DE_Polarity_HIGH                 = 0x00, /*!< usart de polarity high */
    USART_DE_Polarity_LOW                  = 0x01  /*!< usart de polarity low */
} USART_DE_Polarity_Type;

/**
  * @brief type define usart register all
  */
typedef struct {
    /**
      * @brief usart sts register, offset:0x00
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t perr                 : 1; /* [0] */
            __IO uint32_t ferr                 : 1; /* [1] */
            __IO uint32_t nerr                 : 1; /* [2] */
            __IO uint32_t roerr                : 1; /* [3] */
            __IO uint32_t idlef                : 1; /* [4] */
            __IO uint32_t rdbf                 : 1; /* [5] */
            __IO uint32_t tdc                  : 1; /* [6] */
            __IO uint32_t tdbe                 : 1; /* [7] */
            __IO uint32_t bff                  : 1; /* [8] */
            __IO uint32_t ctscf                : 1; /* [9] */
            __IO uint32_t reserved1            : 22;/* [31:10] */
        } sts_bit;
    };

    /**
      * @brief usart dt register, offset:0x04
      */
    union {
        __IO uint32_t dt;
        struct {
            __IO uint32_t dt                   : 9; /* [8:0] */
            __IO uint32_t reserved1            : 23;/* [31:9] */
        } dt_bit;
    };

    /**
      * @brief usart baudr register, offset:0x08
      */
    union {
        __IO uint32_t baudr;
        struct {
            __IO uint32_t div                  : 16;/* [15:0] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } baudr_bit;
    };

    /**
      * @brief usart ctrl1 register, offset:0x0C
      */
    union {
        __IO uint32_t ctrl1;
        struct {
            __IO uint32_t sbf                  : 1; /* [0] */
            __IO uint32_t rm                   : 1; /* [1] */
            __IO uint32_t ren                  : 1; /* [2] */
            __IO uint32_t ten                  : 1; /* [3] */
            __IO uint32_t idleien              : 1; /* [4] */
            __IO uint32_t rdbfien              : 1; /* [5] */
            __IO uint32_t tdcien               : 1; /* [6] */
            __IO uint32_t tdbeien              : 1; /* [7] */
            __IO uint32_t perrien              : 1; /* [8] */
            __IO uint32_t psel                 : 1; /* [9] */
            __IO uint32_t pen                  : 1; /* [10] */
            __IO uint32_t wum                  : 1; /* [11] */
            __IO uint32_t dbn_l                : 1; /* [12] */
            __IO uint32_t uen                  : 1; /* [13] */
            __IO uint32_t reserved1            : 2; /* [15:14] */
            __IO uint32_t tcdt                 : 5; /* [20:16] */
            __IO uint32_t tsdt                 : 5; /* [25:21] */
            __IO uint32_t reserved2            : 2; /* [27:26] */
            __IO uint32_t dbn_h                : 1; /* [28] */
            __IO uint32_t reserved3            : 3; /* [31:29] */
        } ctrl1_bit;
    };

    /**
      * @brief usart ctrl2 register, offset:0x10
      */
    union {
        __IO uint32_t ctrl2;
        struct {
            __IO uint32_t id_l                 : 4; /* [3:0] */
            __IO uint32_t idbn                 : 1; /* [4] */
            __IO uint32_t bfbn                 : 1; /* [5] */
            __IO uint32_t bfien                : 1; /* [6] */
            __IO uint32_t reserved1            : 1; /* [7] */
            __IO uint32_t lbcp                 : 1; /* [8] */
            __IO uint32_t clkpha               : 1; /* [9] */
            __IO uint32_t clkpol               : 1; /* [10] */
            __IO uint32_t clken                : 1; /* [11] */
            __IO uint32_t stopbn               : 2; /* [13:12] */
            __IO uint32_t linen                : 1; /* [14] */
            __IO uint32_t trpswap              : 1; /* [15] */
            __IO uint32_t reserved2            : 12;/* [27:16] */
            __IO uint32_t id_h                 : 4; /* [31:28] */
        } ctrl2_bit;
    };

    /**
      * @brief usart ctrl3 register, offset:0x14
      */
    union {
        __IO uint32_t ctrl3;
        struct {
            __IO uint32_t errien               : 1; /* [0] */
            __IO uint32_t irdaen               : 1; /* [1] */
            __IO uint32_t irdalp               : 1; /* [2] */
            __IO uint32_t slben                : 1; /* [3] */
            __IO uint32_t scnacken             : 1; /* [4] */
            __IO uint32_t scmen                : 1; /* [5] */
            __IO uint32_t dmaren               : 1; /* [6] */
            __IO uint32_t dmaten               : 1; /* [7] */
            __IO uint32_t rtsen                : 1; /* [8] */
            __IO uint32_t ctsen                : 1; /* [9] */
            __IO uint32_t ctscfien             : 1; /* [10] */
            __IO uint32_t reserved1            : 3; /* [13:11] */
            __IO uint32_t rs485en              : 1; /* [14] */
            __IO uint32_t dep                  : 1; /* [15] */
            __IO uint32_t reserved2            : 16;/* [31:16] */
        } ctrl3_bit;
    };

    /**
      * @brief usart gdiv register, offset:0x18
      */
    union {
        __IO uint32_t gdiv;
        struct {
            __IO uint32_t isdiv                : 8; /* [7:0] */
            __IO uint32_t scgt                 : 8; /* [15:8] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } gdiv_bit;
    };
} USART_Type;

/**
  * @}
  */
#define USART1                           ((USART_Type *) USART1_BASE)
#define USART2                           ((USART_Type *) USART2_BASE)
#define USART3                           ((USART_Type *) USART3_BASE)
#define UART4                            ((USART_Type *) UART4_BASE)
#define UART5                            ((USART_Type *) UART5_BASE)
#define USART6                           ((USART_Type *) USART6_BASE)
#define UART7                            ((USART_Type *) UART7_BASE)
#if defined (AT32F435Zx) || defined (AT32F435Vx) || defined (AT32F435Rx) || \
defined (AT32F437Zx) || defined (AT32F437Vx) || defined (AT32F437Rx)
#define UART8                            ((USART_Type *) UART8_BASE)
#endif

/** @defgroup USART_exported_functions
  * @{
  */

void USART_Reset(USART_Type* USART_x);
void USART_Init(USART_Type* USART_x, uint32_t baud_rate, USART_Data_Bit_Num_Type data_bit, USART_Stop_Bit_Num_Type stop_bit);
void USART_parity_Selection_Config(USART_Type* USART_x, USART_parity_Selection_Type parity);
void USART_Enable(USART_Type* USART_x, confirm_state new_state);
void USARTTransmitter_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_Receiver_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_Clock_Config(USART_Type* USART_x, USART_Clock_Polarity_Type clk_pol, USART_Clock_phase_Type clk_pha, USART_lbcp_Type clk_lb);
void USART_Clock_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_Interrupt_Enable(USART_Type* USART_x, uint32_t USART_int, confirm_state new_state);
void USART_DMATransmitter_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_DMA_Receiver_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_WakeUp_ID_Set(USART_Type* USART_x, uint8_t USART_id);
void USART_WakeUp_Mode_Set(USART_Type* USART_x, USART_WakeUp_Mode_Type wakeup_Mode);
void USART_Receiver_mute_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_Break_Bit_Num_Set(USART_Type* USART_x, USART_Break_Bit_Num_Type break_bit);
void USART_lin_Mode_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_Data_Transmit(USART_Type* USART_x, uint16_t data);
uint16_t USART_Data_Receive(USART_Type* USART_x);
void USART_Break_Send(USART_Type* USART_x);
void USART_SmartCard_Guard_Time_Set(USART_Type* USART_x, uint8_t guard_Time_val);
void USART_IRDA_SmartCard_Division_Set(USART_Type* USART_x, uint8_t div_val);
void USART_SmartCard_Mode_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_SmartCard_Nack_Set(USART_Type* USART_x, confirm_state new_state);
void USART_Single_Line_halfduplex_Select(USART_Type* USART_x, confirm_state new_state);
void USART_IRDA_Mode_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_IRDA_Low_Power_Enable(USART_Type* USART_x, confirm_state new_state);
void USART_Hardware_Flow_Control_Set(USART_Type* USART_x, USART_Hardware_Flow_Control_Type flow_state);
flag_status USART_Flag_Get(USART_Type* USART_x, uint32_t flag);
void USART_Flag_Clear(USART_Type* USART_x, uint32_t flag);
void USART_RS485_Delay_Time_Config(USART_Type* USART_x, uint8_t start_Delay_time, uint8_t complete_Delay_time);
void USART_Transmit_Receive_Pin_Swap(USART_Type* USART_x, confirm_state new_state);
void USART_ID_Bit_Num_Set(USART_Type* USART_x, USART_identification_Bit_Num_Type id_Bit_Num);
void USART_DE_Polarity_Set(USART_Type* USART_x, USART_DE_Polarity_Type de_polarity);
void USART_RS485_Mode_Enable(USART_Type* USART_x, confirm_state new_state);

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
