/**
  **************************************************************************
  * @file     at32f435_437_scfg.h
  * @brief    at32f435_437 system config header file
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
#ifndef __AT32F435_437_SCFG_H
#define __AT32F435_437_SCFG_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup SCFG
  */
#define SCFG_REG(value)                  PERIPH_REG(SCFG_BASE, value)
#define SCFG_REG_BIT(value)              PERIPH_REG_BIT(value)

/** @defgroup SCFG_exported_Types
  */

/**
  * @brief scfg xmc addres mapping swap type
  */
typedef enum {
    SCFG_XMC_Swap_NONE                     = 0x00, /* no swap */
    SCFG_XMC_Swap_Mode1                    = 0x01, /* sdram 0x60000000 and 0x70000000, nor psram sram nand2 0xC00000000 and 0xD0000000 */
    SCFG_XMC_Swap_Mode2                    = 0x02, /* qspi2 0x80000000, nand3 0xB0000000 */
    SCFG_XMC_Swap_Mode3                    = 0x03  /* sdram 0x60000000 and 0x70000000, nor psram sram nand2 0xC00000000 and 0xD0000000, qspi2 0x80000000, nand3 0xB0000000 */
} SCFG_XMC_Swap_Type;

/**
  * @brief scfg infrared modulation signal source selecting type
  */
typedef enum {
    SCFG_IR_Source_TMR10                   = 0x00, /* infrared signal source select tmr10 */
    SCFG_IR_Source_USART1                  = 0x01, /* infrared signal source select usart1 */
    SCFG_IR_Source_USART2                  = 0x02  /* infrared signal source select usart2 */
} SCFG_IR_Source_Type;

/**
  * @brief scfg infrared output polarity selecting type
  */
typedef enum {
    SCFG_IR_Polarity_NO_AFFECTE            = 0x00, /* infrared output polarity no affecte */
    SCFG_IR_Polarity_REVERSE               = 0x01  /* infrared output polarity reverse */
} SCFG_IR_Polarity_Type;

/**
  * @brief scfg memory address mapping selecting type
  */
typedef enum {
    SCFG_Mem_Map_MAIN_MEMORY               = 0x00, /* 0x00000000 address mapping from main memory */
    SCFG_Mem_Map_BOOT_MEMORY               = 0x01, /* 0x00000000 address mapping from boot memory */
    SCFG_Mem_Map_XMC_BANK1                 = 0x02, /* 0x00000000 address mapping from xmc bank1 */
    SCFG_Mem_Map_Internal_SRAM             = 0x03, /* 0x00000000 address mapping from internal sram */
    SCFG_Mem_Map_XMC_SDRAM_BANK1           = 0x04  /* 0x00000000 address mapping from xmc sdram bank1 */
} SCFG_Mem_Map_Type;

/**
  * @brief scfg pin source type
  */
typedef enum {
    SCFG_Pins_SOURCE0                      = 0x00,
    SCFG_Pins_SOURCE1                      = 0x01,
    SCFG_Pins_SOURCE2                      = 0x02,
    SCFG_Pins_SOURCE3                      = 0x03,
    SCFG_Pins_SOURCE4                      = 0x04,
    SCFG_Pins_SOURCE5                      = 0x05,
    SCFG_Pins_SOURCE6                      = 0x06,
    SCFG_Pins_SOURCE7                      = 0x07,
    SCFG_Pins_SOURCE8                      = 0x08,
    SCFG_Pins_SOURCE9                      = 0x09,
    SCFG_Pins_SOURCE10                     = 0x0A,
    SCFG_Pins_SOURCE11                     = 0x0B,
    SCFG_Pins_SOURCE12                     = 0x0C,
    SCFG_Pins_SOURCE13                     = 0x0D,
    SCFG_Pins_SOURCE14                     = 0x0E,
    SCFG_Pins_SOURCE15                     = 0x0F
} SCFG_Pins_Source_Type;

/**
  * @brief gpio port source type
  */
typedef enum {
    SCFG_Port_Source_GPIOA                 = 0x00,
    SCFG_Port_Source_GPIOB                 = 0x01,
    SCFG_Port_Source_GPIOC                 = 0x02,
    SCFG_Port_Source_GPIOD                 = 0x03,
    SCFG_Port_Source_GPIOE                 = 0x04,
    SCFG_Port_Source_GPIOF                 = 0x05,
    SCFG_Port_Source_GPIOG                 = 0x06,
    SCFG_Port_Source_GPIOH                 = 0x07
} SCFG_Port_Source_Type;

/**
  * @brief scfg emac interface selecting type
  */
typedef enum {
    SCFG_EMAC_Select_MII                   = 0x00, /* emac interface select mii mode */
    SCFG_EMAC_Select_RMII                  = 0x01  /* emac interface select rmii mode */
} SCFG_EMAC_Interface_Type;

/**
  * @brief scfg ultra high sourcing/sinking strength pins type
  */
typedef enum {
    SCFG_Ultra_Driven_PB3                  = MAKE_VALUE(0x2C, 0),
    SCFG_Ultra_Driven_PB9                  = MAKE_VALUE(0x2C, 1),
    SCFG_Ultra_Driven_PB10                 = MAKE_VALUE(0x2C, 2),
    SCFG_Ultra_Driven_PD12                 = MAKE_VALUE(0x2C, 5),
    SCFG_Ultra_Driven_PD13                 = MAKE_VALUE(0x2C, 6),
    SCFG_Ultra_Driven_PD14                 = MAKE_VALUE(0x2C, 7),
    SCFG_Ultra_Driven_PD15                 = MAKE_VALUE(0x2C, 8),
    SCFG_Ultra_Driven_PF14                 = MAKE_VALUE(0x2C, 9),
    SCFG_Ultra_Driven_PF15                 = MAKE_VALUE(0x2C, 10)
} SCFG_Ultra_Driven_Pins_Type;

/**
  * @brief type define system config register all
  */
typedef struct {
    /**
      * @brief scfg cfg1 register, offset:0x00
      */
    union {
        __IO uint32_t cfg1;
        struct {
            __IO uint32_t mem_Map_sel          : 3; /* [2:0] */
            __IO uint32_t reserved1            : 2; /* [4:3] */
            __IO uint32_t ir_pol               : 1; /* [5] */
            __IO uint32_t ir_src_sel           : 2; /* [7:6] */
            __IO uint32_t reserved2            : 2; /* [9:8] */
            __IO uint32_t swap_xmc             : 2; /* [11:10] */
            __IO uint32_t reserved3            : 20;/* [31:12] */
        } cfg1_bit;
    };

    /**
      * @brief scfg cfg2 register, offset:0x04
      */
    union {
        __IO uint32_t cfg2;
        struct {
            __IO uint32_t reserved1            : 23;/* [22:0] */
            __IO uint32_t mii_rmii_sel         : 1; /* [23] */
            __IO uint32_t reserved2            : 8; /* [31:24] */
        } cfg2_bit;
    };

    /**
      * @brief scfg exintc1 register, offset:0x08
      */
    union {
        __IO uint32_t exintc1;
        struct {
            __IO uint32_t exint0               : 4; /* [3:0] */
            __IO uint32_t exint1               : 4; /* [7:4] */
            __IO uint32_t exint2               : 4; /* [11:8] */
            __IO uint32_t exint3               : 4; /* [15:12] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } exintc1_bit;
    };

    /**
      * @brief scfg exintc2 register, offset:0x0C
      */
    union {
        __IO uint32_t exintc2;
        struct {
            __IO uint32_t exint4               : 4; /* [3:0] */
            __IO uint32_t exint5               : 4; /* [7:4] */
            __IO uint32_t exint6               : 4; /* [11:8] */
            __IO uint32_t exint7               : 4; /* [15:12] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } exintc2_bit;
    };

    /**
      * @brief scfg exintc3 register, offset:0x10
      */
    union {
        __IO uint32_t exintc3;
        struct {
            __IO uint32_t exint8               : 4; /* [3:0] */
            __IO uint32_t exint9               : 4; /* [7:4] */
            __IO uint32_t exint10              : 4; /* [11:8] */
            __IO uint32_t exint11              : 4; /* [15:12] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } exintc3_bit;
    };

    /**
      * @brief scfg exintc4 register, offset:0x14
      */
    union {
        __IO uint32_t exintc4;
        struct {
            __IO uint32_t exint12              : 4; /* [3:0] */
            __IO uint32_t exint13              : 4; /* [7:4] */
            __IO uint32_t exint14              : 4; /* [11:8] */
            __IO uint32_t exint15              : 4; /* [15:12] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } exintc4_bit;
    };

    /**
      * @brief crm reserved1 register, offset:0x18~0x28
      */
    __IO uint32_t reserved1[5];

    /**
      * @brief scfg uhdrv register, offset:0x2C
      */
    union {
        __IO uint32_t uhdrv;
        struct {
            __IO uint32_t pb3_uh               : 1; /* [0] */
            __IO uint32_t pb9_uh               : 1; /* [1] */
            __IO uint32_t pb10_uh              : 1; /* [2] */
            __IO uint32_t reserved1            : 2; /* [4:3] */
            __IO uint32_t pd12_uh              : 1; /* [5] */
            __IO uint32_t pd13_uh              : 1; /* [6] */
            __IO uint32_t pd14_uh              : 1; /* [7] */
            __IO uint32_t pd15_uh              : 1; /* [8] */
            __IO uint32_t pf14_uh              : 1; /* [9] */
            __IO uint32_t pf15_uh              : 1; /* [10] */
            __IO uint32_t reserved2            : 21;/* [31:11] */
        } uhdrv_bit;
    };

} SCFG_Type;
#define SCFG                             ((SCFG_Type *) SCFG_BASE)

/** @defgroup SCFG_exported_functions
  */
void SCFG_Reset(void);
void SCFG_XMC_Mapping_Swap_Set(SCFG_XMC_Swap_Type XMC_Swap);
void SCFG_Infrared_Config(SCFG_IR_Source_Type source, SCFG_IR_Polarity_Type polarity);
void SCFG_Mem_Map_Set(SCFG_Mem_Map_Type mem_map);
void SCFG_EMAC_Interface_Set(SCFG_EMAC_Interface_Type mode);
void SCFG_EXINT_Line_Config(SCFG_Port_Source_Type port_source, SCFG_Pins_Source_Type pin_source);
void SCFG_Pins_Ultra_Driven_Enable(SCFG_Ultra_Driven_Pins_Type value, confirm_state new_state);

#ifdef __cplusplus
}
#endif

#endif
