/**
  **************************************************************************
  * @file     at32f435_437_xmc.h
  * @brief    at32f435_437 xmc header file
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
#ifndef __AT32F435_437_XMC_H
#define __AT32F435_437_XMC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup XMC
  */

/** @defgroup XMC_exported_Types
  */

/**
  * @brief xmc data address bus multiplexing type
  */
typedef enum {
    XMC_Data_Addr_MUX_Disable              = 0x00000000, /*!< xmc address/data multiplexing disable */
    XMC_Data_Addr_MUX_Enable               = 0x00000002  /*!< xmc address/data multiplexing enable */
} XMC_Data_Addr_mux_Type;

/**
  * @brief xmc burst access mode type
  */
typedef enum {
    XMC_Burst_Mode_Disable                 = 0x00000000, /*!< xmc burst mode disable */
    XMC_Burst_Mode_Enable                  = 0x00000100  /*!< xmc burst mode enable */
} XMC_Burst_Access_Mode_Type;

/**
  * @brief xmc asynchronous wait type
  */
typedef enum {
    XMC_ASYN_Wait_Disable                  = 0x00000000, /*!< xmc wait signal during asynchronous transfers disbale */
    XMC_ASYN_Wait_Enable                   = 0x00008000  /*!< xmc wait signal during asynchronous transfers enable */
} XMC_asyn_Wait_Type;

/**
  * @brief xmc wrapped mode type
  */
typedef enum {
    XMC_WRAPPED_Mode_Disable               = 0x00000000, /*!< xmc direct wrapped burst is disbale */
    XMC_WRAPPED_Mode_Enable                = 0x00000400  /*!< xmc direct wrapped burst is enable */
} XMC_wrap_Mode_Type;

/**
  * @brief xmc write operation type
  */
typedef enum {
    XMC_Write_Operation_Disable            = 0x00000000, /*!< xmc写入操作已禁用 */
    XMC_Write_Operation_Enable             = 0x00001000  /*!< xmc写入操作已启用 */
} XMC_Write_Operation_Type;

/**
  * @brief xmc wait signal type
  */
typedef enum {
    XMC_Wait_SIGNAL_Disable                = 0x00000000, /*!< xmc nwait signal is disable */
    XMC_Wait_SIGNAL_Enable                 = 0x00002000  /*!< xmc nwait signal is enable */
} XMC_Wait_signal_Type;

/**
  * @brief xmc write burst type
  */
typedef enum {
    XMC_Write_Burst_SYN_Disable            = 0x00000000, /*!< xmc write operations are always performed in asynchronous mode */
    XMC_Write_Burst_SYN_Enable             = 0x00080000  /*!< xmc write operations are performed in synchronous mode */
} XMC_Write_Burst_Type;

/**
  * @brief xmc extended mode type
  */
typedef enum {
    XMC_Write_Timing_Disable               = 0x00000000, /*!< xmc write timing disable */
    XMC_Write_Timing_Enable                = 0x00004000  /*!< xmc write timing enable */
} XMC_extended_Mode_Type;

/**
  * @brief xmc pccard wait type
  */
typedef enum {
    XMC_Wait_Operation_Disable             = 0x00000000, /*!< xmc wait operation for the pc card/nand flash memory bank disable */
    XMC_Wait_Operation_Enable              = 0x00000002  /*!< xmc wait operation for the pc card/nand flash memory bank enable */
} XMC_NAND_PcCard_Wait_Type;

/**
  * @brief xmc ecc enable type
  */
typedef enum {
    XMC_ECC_Operation_Disable              = 0x00000000, /*!< xmc ecc module disable */
    XMC_ECC_Operation_Enable               = 0x00000040  /*!< xmc ecc module enable */
} XMC_ecc_Enable_Type;

/**
  * @brief xmc nor/sram subbank type
  */
typedef enum {
    XMC_Bank1_NOR_SRAM1                    = 0x00000000, /*!< xmc nor/sram subbank1 */
    XMC_Bank1_NOR_SRAM2                    = 0x00000001, /*!< xmc nor/sram subbank2 */
    XMC_Bank1_NOR_SRAM3                    = 0x00000002, /*!< xmc nor/sram subbank3 */
    XMC_Bank1_NOR_SRAM4                    = 0x00000003  /*!< xmc nor/sram subbank4 */
} XMC_NOR_SRAM_SubBank_Type;

/**
  * @brief xmc class bank type
  */
typedef enum {
    XMC_Bank2_NAND                         = 0x00000000, /*!< xmc nand flash bank2 */
    XMC_BANK3_NAND                         = 0x00000001, /*!< xmc nand flash bank3 */
    XMC_BANK4_PCCARD                       = 0x00000002, /*!< xmc pc card bank4 */
    XMC_BANK5_6_SDRAM                      = 0x00000003  /*!< xmc sdram bank5/6 */
} XMC_class_bank_Type;

/**
  * @brief xmc memory type
  */
typedef enum {
    XMC_Device_SRAM                        = 0x00000000, /*!< xmc device choice sram */
    XMC_Device_PSRAM                       = 0x00000004, /*!< xmc device choice psram */
    XMC_Device_NOR                         = 0x00000008  /*!< xmc device choice nor flash */
} XMC_Memory_Type;

/**
  * @brief xmc data width type
  */
typedef enum {
    XMC_BUSTYPE_8_BITS                     = 0x00000000, /*!< xmc databuss width 8bits */
    XMC_BUSTYPE_16_BITS                    = 0x00000010  /*!< xmc databuss width 16bits */
} XMC_Data_Width_Type;

/**
  * @brief xmc wait signal polarity type
  */
typedef enum {
    XMC_Wait_SIGNAL_LEVEL_LOW              = 0x00000000, /*!< xmc nwait active low */
    XMC_Wait_SIGNAL_LEVEL_HIGH             = 0x00000200  /*!< xmc nwait active high */
} XMC_Wait_signal_Polarity_Type;

/**
  * @brief xmc wait timing type
  */
typedef enum {
    XMC_Wait_SIGNAL_SYN_BEFORE             = 0x00000000, /*!< xmc nwait signal is active one data cycle before wait state */
    XMC_Wait_SIGNAL_SYN_DURING             = 0x00000800  /*!< xmc nwait signal is active during wait state */
} XMC_Wait_Timing_Type;

/**
  * @brief xmc access mode type
  */
typedef enum {
    XMC_Access_Mode_A                      = 0x00000000, /*!< xmc access mode A */
    XMC_Access_Mode_B                      = 0x10000000, /*!< xmc access mode B */
    XMC_Access_Mode_C                      = 0x20000000, /*!< xmc access mode C */
    XMC_Access_Mode_D                      = 0x30000000  /*!< xmc access mode D */
} XMC_Access_Mode_Type;

/**
  * @brief xmc ecc page size type
  */
typedef enum {
    XMC_ECC_PAGESIZE_256_BYTES             = 0x00000000, /*!< xmc ecc page size 256 bytes */
    XMC_ECC_PAGESIZE_512_BYTES             = 0x00020000, /*!< xmc ecc page size 512 bytes */
    XMC_ECC_PAGESIZE_1024_BYTES            = 0x00040000, /*!< xmc ecc page size 1024 bytes */
    XMC_ECC_PAGESIZE_2048_BYTES            = 0x00060000, /*!< xmc ecc page size 2048 bytes */
    XMC_ECC_PAGESIZE_4096_BYTES            = 0x00080000, /*!< xmc ecc page size 4096 bytes */
    XMC_ECC_PAGESIZE_8192_BYTES            = 0x000A0000  /*!< xmc ecc page size 8192 bytes */
} XMC_ecc_pagesize_Type;

/**
  * @brief xmc interrupt sources type
  */
typedef enum {
    XMC_INT_RISING_EDGE                    = 0x00000008, /*!< xmc rising edge detection interrupt enable */
    XMC_INT_LEVEL                          = 0x00000010, /*!< xmc high-level edge detection interrupt enable */
    XMC_INT_FALLING_EDGE                   = 0x00000020, /*!< xmc falling edge detection interrupt enable */
    XMC_INT_ERR                            = 0x00004000  /*!< xmc sdram error interrupt enable */
} XMC_Interrupt_sources_Type;

/**
  * @brief xmc interrupt flag type
  */
typedef enum {
    XMC_RISINGEDGE_FLAG                    = 0x00000001, /*!< xmc中断上升沿检测标志 */
    XMC_LEVEL_FLAG                         = 0x00000002, /*!< xmc中断高级边缘检测标志 */
    XMC_FALLINGEDGE_FLAG                   = 0x00000004, /*!< xmc中断下降沿检测标志 */
    XMC_FEMPT_FLAG                         = 0x00000040, /*!< xmc fifo空标志 */
    XMC_ERR_FLAG                           = 0x00000001, /*!< xmc sdram错误标志 */
    XMC_Busy_FLAG                          = 0x00000020  /*!< xmc sdram忙标志 */
} XMC_Interrupt_Flag_Type;

/**
  * @brief xmc sdram number of column address type
  */
typedef enum {
    XMC_COLUMN_8                           = 0x00000000, /*!< xmc sdram column address 8bit */
    XMC_COLUMN_9                           = 0x00000001, /*!< xmc sdram column address 9bit */
    XMC_COLUMN_10                          = 0x00000002, /*!< xmc sdram column address 10bit */
    XMC_COLUMN_11                          = 0x00000003  /*!< xmc sdram column address 11bit */
} XMC_SDRAM_column_Type;

/**
  * @brief xmc sdram number of row address type
  */
typedef enum {
    XMC_ROW_11                             = 0x00000000, /*!< xmc sdram row address 11bit */
    XMC_ROW_12                             = 0x00000001, /*!< xmc sdram row address 12bit */
    XMC_ROW_13                             = 0x00000002  /*!< xmc sdram row address 13bit */
} XMC_SDRAM_row_Type;

/**
  * @brief xmc sdram memory data bus width type
  */
typedef enum {
    XMC_Mem_Width_8                        = 0x00000000, /*!< xmc sdram data bus width 8 */
    XMC_Mem_Width_16                       = 0x00000001  /*!< xmc sdram data bus width 16 */
} XMC_SDRAM_Width_Type;

/**
  * @brief xmc sdram number of internal banks type
  */
typedef enum {
    XMC_INBK_2                             = 0x00000000, /*!< xmc sdram 2 internal banks */
    XMC_INBK_4                             = 0x00000001  /*!< xmc sdram 4 internal banks */
} XMC_SDRAM_inbk_Type;

/**
  * @brief xmc sdram cas latency type
  */
typedef enum {
    XMC_CAS_1                              = 0x00000001, /*!< xmc sdram cas 1 */
    XMC_CAS_2                              = 0x00000002, /*!< xmc sdram cas 2 */
    XMC_CAS_3                              = 0x00000003  /*!< xmc sdram cas 3 */
} XMC_SDRAM_cas_Type;

/**
  * @brief xmc sdram clock div type
  */
typedef enum {
    XMC_NO_CLK                             = 0x00000000, /*!< xmc sdram disable clock */
    XMC_CLKDIV_2                           = 0x00000002, /*!< xmc sdram clock div 2 */
    XMC_CLKDIV_3                           = 0x00000003, /*!< xmc sdram clock div 3 */
    XMC_CLKDIV_4                           = 0x00000001  /*!< xmc sdram clock div 4 */
} XMC_SDRAM_CLKdiv_Type;

/**
  * @brief xmc sdram read delay
  */
typedef enum {
    XMC_Read_Delay_0                       = 0x00000000, /*!< xmc sdram no delay */
    XMC_Read_Delay_1                       = 0x00000001, /*!< xmc sdram delay 1 clock*/
    XMC_Read_Delay_2                       = 0x00000002, /*!< xmc sdram delay 2 clock */
} XMC_SDRAM_rd_Delay_Type;

/**
  * @brief xmc sdram bank type
  */
typedef enum {
    XMC_SDRAM_BANK1                        = 0x00000000, /*!< xmc sdram bank 1 */
    XMC_SDRAM_BANK2                        = 0x00000001  /*!< xmc sdram bank 2 */
} XMC_SDRAM_bank_Type;


/**
  * @brief xmc sdram timing delay cycle type
  */
typedef enum {
    XMC_Delay_Cycle_1                      = 0x00000000, /*!< xmc sdram timming delay 1 cycle */
    XMC_Delay_Cycle_2                      = 0x00000001, /*!< xmc sdram timming delay 2 cycle */
    XMC_Delay_Cycle_3                      = 0x00000002, /*!< xmc sdram timming delay 3 cycle */
    XMC_Delay_Cycle_4                      = 0x00000003, /*!< xmc sdram timming delay 4 cycle */
    XMC_Delay_Cycle_5                      = 0x00000004, /*!< xmc sdram timming delay 5 cycle */
    XMC_Delay_Cycle_6                      = 0x00000005, /*!< xmc sdram timming delay 6 cycle */
    XMC_Delay_Cycle_7                      = 0x00000006, /*!< xmc sdram timming delay 7 cycle */
    XMC_Delay_Cycle_8                      = 0x00000007, /*!< xmc sdram timming delay 8 cycle */
    XMC_Delay_Cycle_9                      = 0x00000008, /*!< xmc sdram timming delay 9 cycle */
    XMC_Delay_Cycle_10                     = 0x00000009, /*!< xmc sdram timming delay 10 cycle */
    XMC_Delay_Cycle_11                     = 0x0000000A, /*!< xmc sdram timming delay 11 cycle */
    XMC_Delay_Cycle_12                     = 0x0000000B, /*!< xmc sdram timming delay 12 cycle */
    XMC_Delay_Cycle_13                     = 0x0000000C, /*!< xmc sdram timming delay 13 cycle */
    XMC_Delay_Cycle_14                     = 0x0000000D, /*!< xmc sdram timming delay 14 cycle */
    XMC_Delay_Cycle_15                     = 0x0000000E, /*!< xmc sdram timming delay 15 cycle */
    XMC_Delay_Cycle_16                     = 0x0000000F  /*!< xmc sdram timming delay 16 cycle */
} XMC_SDRAM_Delay_Type;


/**
  * @brief xmc sdram command type
  */
typedef enum {
    XMC_CMD_NORMAL                         = 0x00000000, /*!< xmc sdram command normal */
    XMC_CMD_CLK                            = 0x00000001, /*!< xmc sdram command clock enable */
    XMC_CMD_PRECHARG_ALL                   = 0x00000002, /*!< xmc sdram command precharg all bank */
    XMC_CMD_Auto_REFRESH                   = 0x00000003, /*!< xmc sdram command auto refresh */
    XMC_CMD_LOAD_Mode                      = 0x00000004, /*!< xmc sdram command load mode register */
    XMC_CMD_SELF_REFRESH                   = 0x00000005, /*!< xmc sdram command self refresh */
    XMC_CMD_Power_DOWN                     = 0x00000006  /*!< xmc sdram command power down */
} XMC_Command_Type;

/**
  * @brief xmc sdram command bank select type
  */
typedef enum {
    XMC_CMD_BANK1                          = 0x00000010, /*!< send xmc sdram command to bank1 */
    XMC_CMD_BANK2                          = 0x00000008, /*!< send xmc sdram command to bank2 */
    XMC_CMD_Bank1_2                        = 0x00000018  /*!< send xmc sdram command to bank1 and bank2 */
} XMC_CMD_Bank1_2_Type;


/**
  * @brief xmc sdram bank status type
  */
typedef enum {
    XMC_Status_NORMAL                      = 0x00000000, /*!< xmc sdram status normal */
    XMC_Status_SELF_REFRESH                = 0x00000001, /*!< xmc sdram status self refresh */
    XMC_Status_Power_DOWN                  = 0x00000002, /*!< xmc sdram power down */
    XMC_Status_MASK                        = 0x00000003  /*!< xmc sdram mask */
} XMC_bank_Status_Type;


/**
  * @brief   nor/sram banks 定时参数
  */
typedef struct {
    XMC_NOR_SRAM_SubBank_Type              subbank;             /*!< xmc nor/sram subbank */
    XMC_extended_Mode_Type                 write_Timing_Enable; /*!< xmc nor/sram write timing enable */
    uint32_t                               addr_Setup_time;     /*!< xmc nor/sram address setup time */
    uint32_t                               addr_hold_time;      /*!< xmc nor/sram address hold time */
    uint32_t                               data_Setup_time;     /*!< xmc nor/sram data setup time */
    uint32_t                               bus_latency_time;    /*!< xmc nor/sram bus latency time */
    uint32_t                               clk_psc;             /*!< xmc nor/sram clock prescale */
    uint32_t                               data_latency_time;   /*!< xmc nor/sram data latency time */
    XMC_Access_Mode_Type                   mode;                /*!< xmc nor/sram access mode */
} XMC_NORSRAM_Timing_Init_Type;

/**
  * @brief  xmc nor/sram init structure definition
  */
typedef struct {
    XMC_NOR_SRAM_SubBank_Type              subbank;             /*!< xmc nor/sram subbank */
    XMC_Data_Addr_mux_Type                 data_Addr_multiplex; /*!< xmc nor/sram address/data multiplexing enable */
    XMC_Memory_Type                        device;              /*!< xmc nor/sram memory device */
    XMC_Data_Width_Type                    bus_Type;            /*!< xmc nor/sram data bus width */
    XMC_Burst_Access_Mode_Type             burst_Mode_Enable;   /*!< xmc nor/sram burst mode enable */
    XMC_asyn_Wait_Type                     asynwait_Enable;     /*!< xmc nor/sram nwait in asynchronous transfer enable */
    XMC_Wait_signal_Polarity_Type          wait_signal_lv;      /*!< xmc nor/sram nwait polarity */
    XMC_wrap_Mode_Type                     wrapped_Mode_Enable; /*!< xmc nor/sram wrapped enable */
    XMC_Wait_Timing_Type                   wait_signal_Config;  /*!< xmc nor/sram nwait timing configuration */
    XMC_Write_Operation_Type               write_Enable;        /*!< xmc nor/sram write enable */
    XMC_Wait_signal_Type                   wait_signal_Enable;  /*!< xmc nor/sram nwait in synchronous transfer enable */
    XMC_extended_Mode_Type                 write_Timing_Enable; /*!< xmc nor/sram read-write timing different */
    XMC_Write_Burst_Type                   write_Burst_syn;     /*!< xmc nor/sram memory write mode control */
} XMC_NORSRAM_Init_Type;

/**
  * @brief  nand and pccard 定时参数 xmc
  */
typedef struct {
    XMC_class_bank_Type                    class_bank;     /*!< xmc nand/pccard bank */
    uint32_t                               mem_Setup_time; /*!< xmc nand/pccard memory setup time */
    uint32_t                               mem_Waite_time; /*!< xmc nand/pccard memory wait time */
    uint32_t                               mem_hold_time;  /*!< xmc nand/pccard memory hold time */
    uint32_t                               mem_hiz_time;   /*!< xmc nand/pccard memory databus high resistance time */
} XMC_NAND_PcCard_TimingInit_Type;

/**
  * @brief  xmc nand init structure definition
  */
typedef struct {
    XMC_class_bank_Type                    nand_bank;        /*!< xmc nand bank */
    XMC_NAND_PcCard_Wait_Type              wait_Enable;      /*!< xmc wait feature enable */
    XMC_Data_Width_Type                    bus_Type;         /*!< xmc nand bus width */
    XMC_ecc_Enable_Type                    ecc_Enable;       /*!< xmc nand ecc enable */
    XMC_ecc_pagesize_Type                  ecc_pagesize;     /*!< xmc nand ecc page size */
    uint32_t                               delay_Time_cycle; /*!< xmc nand cle to re delay */
    uint32_t                               delay_Time_ar;    /*!< xmc nand ale to re delay */
} XMC_NAND_Init_Type;

/**
  * @brief  xmc pccard init structure definition
  */
typedef struct {
    XMC_NAND_PcCard_Wait_Type              enable_Wait;   /*!< xmc pccard wait feature enable */
    uint32_t                               delay_Time_cr; /*!< xmc pccard cle to re delay */
    uint32_t                               delay_Time_ar; /*!< xmc pccard ale to re delay */
} XMC_PcCard_Init_Type;

/**
  * @brief  xmc sdram init structure definition
  */
typedef struct {
    XMC_SDRAM_bank_Type                    sdram_bank;       /*!< xmc sdram bank bype */
    XMC_SDRAM_inbk_Type                    internel_banks;   /*!< xmc sdram internal banks */
    XMC_SDRAM_CLKdiv_Type                  clkdiv;           /*!< xmc sdram clock div */
    uint8_t                                write_protection; /*!< xmc sdram write protection */
    uint8_t                                burst_Read;       /*!< xmc sdram burst read */
    uint8_t                                read_delay;       /*!< xmc sdram read delay */
    XMC_SDRAM_column_Type                  column_Address;   /*!< xmc sdram column address */
    XMC_SDRAM_row_Type                     row_Address;      /*!< xmc sdram row address */
    XMC_SDRAM_cas_Type                     cas;              /*!< xmc sdram cas */
    XMC_SDRAM_Width_Type                   width;            /*!< xmc sdram data width */
} XMC_SDRAM_Init_Type;

/**
  * @brief  xmc sdram timing structure definition
  */
typedef struct {
    XMC_SDRAM_Delay_Type                   tmrd; /*!< mode register program to active delay  */
    XMC_SDRAM_Delay_Type                   txsr; /*!< exit self-refresh to active delay */
    XMC_SDRAM_Delay_Type                   tras; /*!< self refresh  */
    XMC_SDRAM_Delay_Type                   trc;  /*!< refresh to active delay */
    XMC_SDRAM_Delay_Type                   twr;  /*!< write recovery delay */
    XMC_SDRAM_Delay_Type                   trp;  /*!< precharge to active delay */
    XMC_SDRAM_Delay_Type                   trcd; /*!< row active to read/write delay */
} XMC_SDRAM_Timing_Type;

/**
  * @brief  xmc sdram command structure definition
  */
typedef struct {
    XMC_Command_Type                       cmd;          /*!< sdram command */
    XMC_CMD_Bank1_2_Type                   cmd_banks;    /*!< which bank send command */
    uint32_t                               auto_refresh; /*!< auto refresh times */
    uint32_t                               data;         /*!< mode register data */
} XMC_SDRAM_CMD_Type;

typedef struct {
    /**
      * @brief xmc bank1 bk1ctrl register, offset:0x00+0x08*(x-1) x= 1...4
      */
    union {
        __IO uint32_t bk1ctrl;
        struct {
            __IO uint32_t en                   : 1; /* [0] */
            __IO uint32_t admuxen              : 1; /* [1] */
            __IO uint32_t dev                  : 2; /* [3:2] */
            __IO uint32_t extmdbw              : 2; /* [5:4] */
            __IO uint32_t noren                : 1; /* [6] */
            __IO uint32_t reserved1            : 1; /* [7] */
            __IO uint32_t syncben              : 1; /* [8] */
            __IO uint32_t nwpol                : 1; /* [9] */
            __IO uint32_t wrapen               : 1; /* [10] */
            __IO uint32_t nwtcfg               : 1; /* [11] */
            __IO uint32_t wen                  : 1; /* [12] */
            __IO uint32_t nwsen                : 1; /* [13] */
            __IO uint32_t rwtd                 : 1; /* [14] */
            __IO uint32_t nwasen               : 1; /* [15] */
            __IO uint32_t crpgs                : 3; /* [18:16] */
            __IO uint32_t mwmc                 : 1; /* [19] */
            __IO uint32_t reserved2            : 12;/* [31:20] */
        } bk1ctrl_bit;
    };

    /**
      * @brief xmc bank1 bk1tmg register, offset:0x04+0x08*(x-1) x= 1...4
      */
    union {
        __IO uint32_t bk1tmg;
        struct {
            __IO uint32_t addrst               : 4; /* [3:0] */
            __IO uint32_t addrht               : 4; /* [7:4] */
            __IO uint32_t dtst                 : 8; /* [15:8] */
            __IO uint32_t buslat               : 4; /* [19:16] */
            __IO uint32_t clkpsc               : 4; /* [23:20] */
            __IO uint32_t dtlat                : 4; /* [27:24] */
            __IO uint32_t asyncm               : 2; /* [29:28] */
            __IO uint32_t reserved1            : 2; /* [31:30] */
        } bk1tmg_bit;
    };

} XMC_Bank1_Ctrl_tmg_reg_Type;

typedef struct {
    /**
      * @brief xmc bank1 bk1tmgwr register, offset:0x104+0x08*(x-1) x= 1...4
      */
    union {
        __IO uint32_t bk1tmgwr;
        struct {
            __IO uint32_t addrst               : 4; /* [3:0] */
            __IO uint32_t addrht               : 4; /* [7:4] */
            __IO uint32_t dtst                 : 8; /* [15:8] */
            __IO uint32_t buslat               : 4; /* [19:16] */
            __IO uint32_t reserved1            : 8; /* [27:20] */
            __IO uint32_t asyncm               : 2; /* [29:28] */
            __IO uint32_t reserved2            : 2; /* [31:30] */
        } bk1tmgwr_bit;
    };

    /**
      * @brief xmc bank1 reserved register
      */
    __IO uint32_t reserved1;

} XMC_Bank1_tmgwr_reg_Type;

/**
  * @brief xmc bank1 registers
  */
typedef struct {
    /**
      * @brief xmc bank1 ctrl and tmg register, offset:0x00~0x1C
      */
    XMC_Bank1_Ctrl_tmg_reg_Type ctrl_tmg_group[4];

    /**
      * @brief xmc bank1 reserved register, offset:0x20~0x100
      */
    __IO uint32_t reserved1[57];

    /**
       * @brief xmc bank1 tmgwr register, offset:0x104~0x11C
       */
    XMC_Bank1_tmgwr_reg_Type tmgwr_group[4];

    /**
      * @brief xmc bank1 reserved register, offset:0x120~0x21C
      */
    __IO uint32_t reserved2[63];

    /**
      * @brief xmc bank1 ext register, offset:0x220~0x22C
      */
    union {
        __IO uint32_t ext[4];
        struct {
            __IO uint32_t buslatw2w            : 8; /* [7:0] */
            __IO uint32_t buslatr2r            : 8; /* [15:8] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } ext_bit[4];
    };

} XMC_Bank1_Type;

/**
  * @brief xmc bank2 registers
  */
typedef struct {
    /**
      * @brief xmc bk2ctrl register, offset:0x60
      */
    union {
        __IO uint32_t bk2ctrl;
        struct {
            __IO uint32_t reserved1            : 1; /* [0] */
            __IO uint32_t nwen                 : 1; /* [1] */
            __IO uint32_t en                   : 1; /* [2] */
            __IO uint32_t dev                  : 1; /* [3] */
            __IO uint32_t extmdbw              : 2; /* [5:4] */
            __IO uint32_t eccen                : 1; /* [6] */
            __IO uint32_t reserved2            : 2; /* [8:7] */
            __IO uint32_t tcr                  : 4; /* [12:9] */
            __IO uint32_t tar                  : 4; /* [16:13] */
            __IO uint32_t eccpgs               : 3; /* [19:17] */
            __IO uint32_t reserved3            : 12;/* [31:20] */
        } bk2ctrl_bit;
    };

    /**
      * @brief xmc bk2is register, offset:0x64
      */
    union {
        __IO uint32_t bk2is;
        struct {
            __IO uint32_t res                  : 1; /* [0] */
            __IO uint32_t hls                  : 1; /* [1] */
            __IO uint32_t fes                  : 1; /* [2] */
            __IO uint32_t reien                : 1; /* [3] */
            __IO uint32_t hlien                : 1; /* [4] */
            __IO uint32_t feien                : 1; /* [5] */
            __IO uint32_t fifoe                : 1; /* [6] */
            __IO uint32_t reserved1            : 25;/* [31:7] */
        } bk2is_bit;
    };

    /**
    * @brief xmc bk2tmgmem register, offset:0x68
    */
    union {
        __IO uint32_t bk2tmgmem;
        struct {
            __IO uint32_t cmst                 : 8; /* [7:0] */
            __IO uint32_t cmwt                 : 8; /* [15:8] */
            __IO uint32_t cmht                 : 8; /* [23:16] */
            __IO uint32_t cmdhizt              : 8; /* [31:24] */
        } bk2tmgmem_bit;
    };

    /**
    * @brief xmc bk2tmgatt register, offset:0x6C
    */
    union {
        __IO uint32_t bk2tmgatt;
        struct {
            __IO uint32_t amst                 : 8; /* [7:0] */
            __IO uint32_t amwt                 : 8; /* [15:8] */
            __IO uint32_t amht                 : 8; /* [23:16] */
            __IO uint32_t amdhizt              : 8; /* [31:24] */
        } bk2tmgatt_bit;
    };

    /**
    * @brief xmc reserved register, offset:0x70
    */
    __IO uint32_t reserved1;

    /**
    * @brief xmc bk2ecc register, offset:0x74
    */
    union {
        __IO uint32_t bk2ecc;
        struct {
            __IO uint32_t ecc                  : 32; /* [31:0] */
        } bk2ecc_bit;
    };

} XMC_Bank2_Type;

/**
  * @brief xmc bank3 registers
  */
typedef struct {
    /**
      * @brief xmc bk3ctrl register, offset:0x80
      */
    union {
        __IO uint32_t bk3ctrl;
        struct {
            __IO uint32_t reserved1            : 1; /* [0] */
            __IO uint32_t nwen                 : 1; /* [1] */
            __IO uint32_t en                   : 1; /* [2] */
            __IO uint32_t dev                  : 1; /* [3] */
            __IO uint32_t extmdbw              : 2; /* [5:4] */
            __IO uint32_t eccen                : 1; /* [6] */
            __IO uint32_t reserved2            : 2; /* [8:7] */
            __IO uint32_t tcr                  : 4; /* [12:9] */
            __IO uint32_t tar                  : 4; /* [16:13] */
            __IO uint32_t eccpgs               : 3; /* [19:17] */
            __IO uint32_t reserved3            : 12;/* [31:20] */
        } bk3ctrl_bit;
    };

    /**
      * @brief xmc bk3is register, offset:0x84
      */
    union {
        __IO uint32_t bk3is;
        struct {
            __IO uint32_t res                  : 1; /* [0] */
            __IO uint32_t hls                  : 1; /* [1] */
            __IO uint32_t fes                  : 1; /* [2] */
            __IO uint32_t reien                : 1; /* [3] */
            __IO uint32_t hlien                : 1; /* [4] */
            __IO uint32_t feien                : 1; /* [5] */
            __IO uint32_t fifoe                : 1; /* [6] */
            __IO uint32_t reserved1            : 25;/* [31:7] */
        } bk3is_bit;
    };

    /**
    * @brief xmc bk3tmgmem register, offset:0x88
    */
    union {
        __IO uint32_t bk3tmgmem;
        struct {
            __IO uint32_t cmst                 : 8; /* [7:0] */
            __IO uint32_t cmwt                 : 8; /* [15:8] */
            __IO uint32_t cmht                 : 8; /* [23:16] */
            __IO uint32_t cmdhizt              : 8; /* [31:24] */
        } bk3tmgmem_bit;
    };

    /**
    * @brief xmc bk3tmgatt register, offset:0x8C
    */
    union {
        __IO uint32_t bk3tmgatt;
        struct {
            __IO uint32_t amst                 : 8; /* [7:0] */
            __IO uint32_t amwt                 : 8; /* [15:8] */
            __IO uint32_t amht                 : 8; /* [23:16] */
            __IO uint32_t amdhizt              : 8; /* [31:24] */
        } bk3tmgatt_bit;
    };

    /**
    * @brief xmc reserved register, offset:0x90
    */
    __IO uint32_t reserved1;

    /**
    * @brief xmc bk3ecc register, offset:0x94
    */
    union {
        __IO uint32_t bk3ecc;
        struct {
            __IO uint32_t ecc                  : 32; /* [31:0] */
        } bk3ecc_bit;
    };
} XMC_bank3_Type;

/**
  * @brief xmc bank4 registers
  */
typedef struct {

    /**
      * @brief xmc bk4ctrl register, offset:0xA0
      */
    union {
        __IO uint32_t bk4ctrl;
        struct {
            __IO uint32_t reserved1            : 1; /* [0] */
            __IO uint32_t nwen                 : 1; /* [1] */
            __IO uint32_t en                   : 1; /* [2] */
            __IO uint32_t dev                  : 1; /* [3] */
            __IO uint32_t extmdbw              : 2; /* [5:4] */
            __IO uint32_t eccen                : 1; /* [6] */
            __IO uint32_t reserved2            : 2; /* [8:7] */
            __IO uint32_t tcr                  : 4; /* [12:9] */
            __IO uint32_t tar                  : 4; /* [16:13] */
            __IO uint32_t eccpgs               : 3; /* [19:17] */
            __IO uint32_t reserved3            : 12;/* [31:20] */
        } bk4ctrl_bit;
    };

    /**
      * @brief xmc bk4is register, offset:0xA4
      */
    union {
        __IO uint32_t bk4is;
        struct {
            __IO uint32_t res                  : 1; /* [0] */
            __IO uint32_t hls                  : 1; /* [1] */
            __IO uint32_t fes                  : 1; /* [2] */
            __IO uint32_t reien                : 1; /* [3] */
            __IO uint32_t hlien                : 1; /* [4] */
            __IO uint32_t feien                : 1; /* [5] */
            __IO uint32_t fifoe                : 1; /* [6] */
            __IO uint32_t reserved1            : 25;/* [31:7] */
        } bk4is_bit;
    };

    /**
    * @brief xmc bk4tmgmem register, offset:0xA8
    */
    union {
        __IO uint32_t bk4tmgmem;
        struct {
            __IO uint32_t cmst                 : 8; /* [7:0] */
            __IO uint32_t cmwt                 : 8; /* [15:8] */
            __IO uint32_t cmht                 : 8; /* [23:16] */
            __IO uint32_t cmdhizt              : 8; /* [31:24] */
        } bk4tmgmem_bit;
    };

    /**
    * @brief xmc bk4tmgatt register, offset:0xAC
    */
    union {
        __IO uint32_t bk4tmgatt;
        struct {
            __IO uint32_t amst                 : 8; /* [7:0] */
            __IO uint32_t amwt                 : 8; /* [15:8] */
            __IO uint32_t amht                 : 8; /* [23:16] */
            __IO uint32_t amdhizt              : 8; /* [31:24] */
        } bk4tmgatt_bit;
    };

    /**
    * @brief xmc bk4tmgio register, offset:0xB0
    */
    union {
        __IO uint32_t bk4tmgio;
        struct {
            __IO uint32_t iost                 : 8; /* [7:0] */
            __IO uint32_t iowt                 : 8; /* [15:8] */
            __IO uint32_t ioht                 : 8; /* [23:16] */
            __IO uint32_t iohizt               : 8; /* [31:24] */
        } bk4tmgio_bit;
    };
} XMC_bank4_Type;

/**
  * @brief xmc sdram type
  */
typedef struct {
    /**
      * @brief xmc sdram ctrl register, offset:0x140~0x144
      */
    union {
        __IO uint32_t ctrl[2];
        struct {
            __IO uint32_t ca                   : 2; /* [1:0] */
            __IO uint32_t ra                   : 2; /* [3:2] */
            __IO uint32_t db                   : 2; /* [5:4] */
            __IO uint32_t inbk                 : 1; /* [6] */
            __IO uint32_t cas                  : 2; /* [8:7] */
            __IO uint32_t wrp                  : 1; /* [9] */
            __IO uint32_t clkdiv               : 2; /* [11:10] */
            __IO uint32_t bstr                 : 1; /* [12] */
            __IO uint32_t rd                   : 2; /* [14:13] */
            __IO uint32_t reserved1            : 17;/* [31:15] */
        } ctrl_bit[2];
    };

    /**
      * @brief xmc sdram tm register, offset:0x148~0x14C
      */
    union {
        __IO uint32_t tm[2];
        struct {
            __IO uint32_t tmrd                 : 4; /* [3:0] */
            __IO uint32_t txsr                 : 4; /* [7:4] */
            __IO uint32_t tras                 : 4; /* [11:8] */
            __IO uint32_t trc                  : 4; /* [15:12] */
            __IO uint32_t twr                  : 4; /* [19:16] */
            __IO uint32_t trp                  : 4; /* [23:20] */
            __IO uint32_t trcd                 : 4; /* [27:24] */
            __IO uint32_t reserved1            : 4; /* [31:28] */
        } tm_bit[2];

    };

    /**
        * @brief xmc sdram cmd register, offset:0x150
        */
    union {
        __IO uint32_t cmd;
        struct {
            __IO uint32_t cmd                  : 3; /* [2:0] */
            __IO uint32_t bk2                  : 1; /* [3] */
            __IO uint32_t bk1                  : 1; /* [4] */
            __IO uint32_t art                  : 4; /* [8:5] */
            __IO uint32_t mrd                  : 13;/* [21:9] */
            __IO uint32_t reserved1            : 10;/* [31:22] */
        } cmd_bit;
    };

    /**
      * @brief xmc sdram rcnt register, offset:0x154
      */
    union {
        __IO uint32_t rcnt;
        struct {
            __IO uint32_t errc                 : 1; /* [0] */
            __IO uint32_t rc                   : 13;/* [13:1] */
            __IO uint32_t erien                : 1; /* [14] */
            __IO uint32_t reserved1            : 17;/* [31:15] */
        } rcnt_bit;
    };

    /**
      * @brief xmc sdram sts register, offset:0x158
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t err                  : 1; /* [0] */
            __IO uint32_t bk1sts               : 2; /* [2:1] */
            __IO uint32_t bk2sts               : 2; /* [4:3] */
            __IO uint32_t busy                 : 1; /* [5] */
            __IO uint32_t reserved1            : 26;/* [31:6] */
        } sts_bit;
    };
} XMC_SDRAM_Type;
#define XMC_BANK1                        ((XMC_Bank1_Type *) XMC_Bank1_REG_BASE)
#define XMC_BANK2                        ((XMC_Bank2_Type *) XMC_Bank2_REG_BASE)
#define XMC_BANK3                        ((XMC_bank3_Type *) XMC_BANK3_REG_BASE)
#define XMC_BANK4                        ((XMC_bank4_Type *) XMC_BANK4_REG_BASE)
#define XMC_SDRAM                        ((XMC_SDRAM_Type *) XMC_SDRAM_REG_BASE)

/** @defgroup XMC_exported_functions
  */
void XMC_NOR_SRAM_Reset(XMC_NOR_SRAM_SubBank_Type XMC_subbank);
void XMC_NOR_SRAM_Init(XMC_NORSRAM_Init_Type* XMC_NORSRAM_Init_struct);
void XMC_NOR_SRAM_Timing_Config(XMC_NORSRAM_Timing_Init_Type* XMC_rw_Timing_struct,
                                XMC_NORSRAM_Timing_Init_Type* XMC_w_Timing_struct);
void XMC_NORSRAM_Default_Para_Init(XMC_NORSRAM_Init_Type* XMC_NOR_SRAM_Init_struct);
void XMC_NORSRAM_Timing_Default_Para_Init(XMC_NORSRAM_Timing_Init_Type* XMC_rw_Timing_struct,
        XMC_NORSRAM_Timing_Init_Type* XMC_w_Timing_struct);
void XMC_NOR_SRAM_Enable(XMC_NOR_SRAM_SubBank_Type XMC_subbank, confirm_state new_state);
void XMC_Ext_Timing_Config(XMC_NOR_SRAM_SubBank_Type XMC_Sub_bank, uint16_t w2w_timing, uint16_t r2r_timing);
void XMC_NAND_Reset(XMC_class_bank_Type XMC_bank);
void XMC_NAND_Init(XMC_NAND_Init_Type* XMC_NAND_Init_struct);
void XMC_NAND_Timing_Config(XMC_NAND_PcCard_TimingInit_Type* XMC_Common_spacetiming_struct,
                            XMC_NAND_PcCard_TimingInit_Type* XMC_attribute_spacetiming_struct);
void XMC_NAND_Default_Para_Init(XMC_NAND_Init_Type* XMC_NAND_Init_struct);
void XMC_NAND_Timing_Default_Para_Init(XMC_NAND_PcCard_TimingInit_Type* XMC_Common_spacetiming_struct,
                                       XMC_NAND_PcCard_TimingInit_Type* XMC_attribute_spacetiming_struct);
void XMC_NAND_Enable(XMC_class_bank_Type XMC_bank, confirm_state new_state);
void XMC_NAND_ecc_Enable(XMC_class_bank_Type XMC_bank, confirm_state new_state);
uint32_t XMC_ecc_Get(XMC_class_bank_Type XMC_bank);
void XMC_Interrupt_Enable(XMC_class_bank_Type XMC_bank, XMC_Interrupt_sources_Type XMC_int, confirm_state new_state);
flag_status XMC_Flag_Status_Get(XMC_class_bank_Type XMC_bank, XMC_Interrupt_Flag_Type XMC_flag);
void XMC_Flag_Clear(XMC_class_bank_Type XMC_bank, XMC_Interrupt_Flag_Type XMC_flag);
void XMC_PcCard_Reset(void);
void XMC_PcCard_Init(XMC_PcCard_Init_Type* XMC_PcCard_Init_struct);
void XMC_PcCard_Timing_Config(XMC_NAND_PcCard_TimingInit_Type* XMC_Common_spacetiming_struct,
                              XMC_NAND_PcCard_TimingInit_Type* XMC_attribute_spacetiming_struct,
                              XMC_NAND_PcCard_TimingInit_Type* XMC_iospace_Timing_struct);
void XMC_PcCard_Default_Para_Init(XMC_PcCard_Init_Type* XMC_PcCard_Init_struct);
void XMC_PcCard_Timing_Default_Para_Init(XMC_NAND_PcCard_TimingInit_Type* XMC_Common_spacetiming_struct,
        XMC_NAND_PcCard_TimingInit_Type* XMC_attribute_spacetiming_struct,
        XMC_NAND_PcCard_TimingInit_Type* XMC_iospace_Timing_struct);
void XMC_PcCard_Enable(confirm_state new_state);
void XMC_SDRAM_Reset(XMC_SDRAM_bank_Type XMC_bank);
void XMC_SDRAM_Init(XMC_SDRAM_Init_Type *XMC_SDRAM_Init_struct, XMC_SDRAM_Timing_Type *XMC_SDRAM_Timing_struct);
void XMC_SDRAM_Default_Para_Init(XMC_SDRAM_Init_Type *XMC_SDRAM_Init_struct, XMC_SDRAM_Timing_Type *XMC_SDRAM_Timing_struct);
void XMC_SDRAM_CMD(XMC_SDRAM_CMD_Type *XMC_SDRAM_CMD_struct);
uint32_t XMC_SDRAM_Status_Get(XMC_SDRAM_bank_Type XMC_bank);
void XMC_SDRAM_Refresh_Counter_Set(uint32_t counter);
void XMC_SDRAM_Auto_Refresh_Set(uint32_t number);

#ifdef __cplusplus
}
#endif

#endif
