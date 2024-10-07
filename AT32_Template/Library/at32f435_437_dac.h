/**
  **************************************************************************
  * @file     at32f435_437_dac.h
  * @brief    at32f435_437 dac header file
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
#ifndef __AT32F435_437_DAC_H
#define __AT32F435_437_DAC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup DAC
  */
#define DAC1_D1DMAUDRF                   ((uint32_t)(0x00002000))
#define DAC2_D2DMAUDRF                   ((uint32_t)(0x20000000))

/** @defgroup DAC_exported_Types
  */

/**
  * @brief dac select type
  */
typedef enum {
    DAC1_Select                            = 0x01, /*!< dac1 select */
    DAC2_Select                            = 0x02  /*!< dac2 select */
} DAC_Select_Type;

/**
  * @brief dac trigger type
  */
typedef enum {
    DAC_TMR6_Trgout_EVENT                  = 0x00, /*!< dac trigger selection:timer6 trgout event */
    DAC_TMR8_Trgout_EVENT                  = 0x01, /*!< dac trigger selection:timer8 trgout event */
    DAC_TMR7_Trgout_EVENT                  = 0x02, /*!< dac trigger selection:timer7 trgout event */
    DAC_TMR5_Trgout_EVENT                  = 0x03, /*!< dac trigger selection:timer5 trgout event */
    DAC_TMR2_Trgout_EVENT                  = 0x04, /*!< dac trigger selection:timer2 trgout event */
    DAC_TMR4_Trgout_EVENT                  = 0x05, /*!< dac trigger selection:timer4 trgout event */
    DAC_External_Interrupt_Line_9          = 0x06, /*!< dac trigger selection:external line9 */
    DAC_Software_TRIGGER                   = 0x07  /*!< dac trigger selection:software trigger */
} DAC_Trigger_Type;

/**
  * @brief dac wave type
  */
typedef enum {
    DAC_Wave_Generate_NONE                 = 0x00, /*!< dac wave generation disabled */
    DAC_Wave_Generate_NOISE                = 0x01, /*!< dac noise wave generation enabled */
    DAC_Wave_Generate_TRIANGLE             = 0x02  /*!< dac triangle wave generation enabled */
} DAC_Wave_Type;

/**
  * @brief dac mask amplitude type
  */
typedef enum {
    DAC_LSFR_BIT0_Amplitude_1              = 0x00, /*!< unmask bit0/ triangle amplitude equal to 1 */
    DAC_LSFR_BIT10_Amplitude_3             = 0x01, /*!< unmask bit[1:0]/ triangle amplitude equal to 3 */
    DAC_LSFR_BIT20_Amplitude_7             = 0x02, /*!< unmask bit[2:0]/ triangle amplitude equal to 7 */
    DAC_LSFR_BIT30_Amplitude_15            = 0x03, /*!< unmask bit[3:0]/ triangle amplitude equal to 15 */
    DAC_LSFR_BIT40_Amplitude_31            = 0x04, /*!< unmask bit[4:0]/ triangle amplitude equal to 31 */
    DAC_LSFR_BIT50_Amplitude_63            = 0x05, /*!< unmask bit[5:0]/ triangle amplitude equal to 63 */
    DAC_LSFR_BIT60_Amplitude_127           = 0x06, /*!< unmask bit[6:0]/ triangle amplitude equal to 127 */
    DAC_LSFR_BIT70_Amplitude_255           = 0x07, /*!< unmask bit[7:0]/ triangle amplitude equal to 255 */
    DAC_LSFR_BIT80_Amplitude_511           = 0x08, /*!< unmask bit[8:0]/ triangle amplitude equal to 511 */
    DAC_LSFR_BIT90_Amplitude_1023          = 0x09, /*!< unmask bit[9:0]/ triangle amplitude equal to 1023 */
    DAC_LSFR_BITA0_Amplitude_2047          = 0x0A, /*!< unmask bit[10:0]/ triangle amplitude equal to 2047 */
    DAC_LSFR_BITB0_Amplitude_4095          = 0x0B  /*!< unmask bit[11:0]/ triangle amplitude equal to 4095 */
} DAC_Mask_Amplitude_Type;

/**
  * @brief  dac1 aligned data type
  */
typedef enum {
    DAC1_12BIT_RIGHT                       = 0x40007408, /*!< dac1 12-bit data right-aligned */
    DAC1_12BIT_LEFT                        = 0x4000740C, /*!< dac1 12-bit data left-aligned */
    DAC1_8BIT_RIGHT                        = 0x40007410  /*!< dac1 8-bit data right-aligned */
} dac1_Aligned_Data_Type;

/**
  * @brief  dac2 aligned data type
  */
typedef enum {
    DAC2_12BIT_RIGHT                       = 0x40007414, /*!< dac2 12-bit data right-aligned */
    DAC2_12BIT_LEFT                        = 0x40007418, /*!< dac2 12-bit data left-aligned */
    DAC2_8BIT_RIGHT                        = 0x4000741C  /*!< dac2 8-bit data right-aligned */
} dac2_Aligned_Data_Type;

/**
  * @brief  dac dual data type
  */
typedef enum {
    DAC_Dual_12BIT_RIGHT                   = 0x40007420, /*!<double dac 12-bit data right-aligned */
    DAC_Dual_12BIT_LEFT                    = 0x40007424, /*!<double dac 12-bit data left-aligned */
    DAC_Dual_8BIT_RIGHT                    = 0x40007428  /*!<double dac 8-bit data right-aligned */
} DAC_Dual_Data_Type;

/**
  * @brief type define dac register all
  */
typedef struct {
    /**
      * @brief dac ctrl register, offset:0x00
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t d1en                 : 1; /* [0] */
            __IO uint32_t d1obdis              : 1; /* [1] */
            __IO uint32_t d1trgen              : 1; /* [2] */
            __IO uint32_t d1trgsel             : 3; /* [5:3] */
            __IO uint32_t d1nm                 : 2; /* [7:6] */
            __IO uint32_t d1nbsel              : 4; /* [11:8] */
            __IO uint32_t d1dmaen              : 1; /* [12] */
            __IO uint32_t d1dmaudrien          : 1; /* [13] */
            __IO uint32_t reserved1            : 2; /* [15:14] */
            __IO uint32_t d2en                 : 1; /* [16] */
            __IO uint32_t d2obdis              : 1; /* [17] */
            __IO uint32_t d2trgen              : 1; /* [18] */
            __IO uint32_t d2trgsel             : 3; /* [21:19] */
            __IO uint32_t d2nm                 : 2; /* [23:22] */
            __IO uint32_t d2nbsel              : 4; /* [27:24] */
            __IO uint32_t d2dmaen              : 1; /* [28] */
            __IO uint32_t d2dmaudrien          : 1; /* [29] */
            __IO uint32_t reserved2            : 2; /* [31:30] */
        } ctrl_bit;
    };

    /**
       * @brief dac swtrg register, offset:0x04
       */
    union {
        __IO uint32_t swtrg;
        struct {
            __IO uint32_t d1swtrg              : 1; /* [0] */
            __IO uint32_t d2swtrg              : 1; /* [1] */
            __IO uint32_t reserved1            : 30;/* [31:2] */
        } swtrg_bit;
    };

    /**
       * @brief dac d1dth12r register, offset:0x08
       */
    union {
        __IO uint32_t d1dth12r;
        struct {
            __IO uint32_t d1dt12r              : 12;/* [11:0] */
            __IO uint32_t reserved1            : 20;/* [31:2] */
        } d1dth12r_bit;
    };

    /**
       * @brief dac d1dth12l register, offset:0x0C
       */
    union {
        __IO uint32_t d1dth12l;
        struct {
            __IO uint32_t d1dt12l              : 12;/* [11:0] */
            __IO uint32_t reserved1            : 20;/* [31:2] */
        } d1dth12l_bit;
    };

    /**
       * @brief dac d1dth8r register, offset:0x10
       */
    union {
        __IO uint32_t d1dth8r;
        struct {
            __IO uint32_t d1dt8r               : 8; /* [7:0] */
            __IO uint32_t reserved1            : 24;/* [31:8] */
        } d1dth8r_bit;
    };

    /**
       * @brief dac d2dth12r register, offset:0x14
       */
    union {
        __IO uint32_t d2dth12r;
        struct {
            __IO uint32_t d2dt12r              : 12;/* [11:0] */
            __IO uint32_t reserved1            : 20;/* [31:2] */
        } d2dth12r_bit;
    };

    /**
       * @brief dac d2dth12l register, offset:0x18
       */
    union {
        __IO uint32_t d2dth12l;
        struct {
            __IO uint32_t d2dt12l              : 12;/* [11:0] */
            __IO uint32_t reserved1            : 20;/* [31:2] */
        } d2dth12l_bit;
    };

    /**
       * @brief dac d2dth8r register, offset:0x1C
       */
    union {
        __IO uint32_t d2dth8r;
        struct {
            __IO uint32_t d2dt8r               : 8; /* [7:0] */
            __IO uint32_t reserved1            : 24;/* [31:8] */
        } d2dth8r_bit;
    };

    /**
       * @brief dac ddth12r register, offset:0x20
       */
    union {
        __IO uint32_t ddth12r;
        struct {
            __IO uint32_t dd1dt12r             : 12;/* [11:0] */
            __IO uint32_t reserved1            : 4; /* [15:12] */
            __IO uint32_t dd2dt12r             : 12;/* [27:16] */
            __IO uint32_t reserved2            : 4; /* [31:28] */
        } ddth12r_bit;
    };

    /**
       * @brief dac ddth12l register, offset:0x24
       */
    union {
        __IO uint32_t ddth12l;
        struct {
            __IO uint32_t reserved1            : 4; /* [3:0] */
            __IO uint32_t dd1dt12l             : 12;/* [15:4] */
            __IO uint32_t reserved2            : 4; /* [19:16] */
            __IO uint32_t dd2dt12l             : 12;/* [31:20] */
        } ddth12l_bit;
    };

    /**
       * @brief dac ddth8r register, offset:0x28
       */
    union {
        __IO uint32_t ddth8r;
        struct {
            __IO uint32_t dd1dt8r              : 8; /* [7:0] */
            __IO uint32_t dd2dt8r              : 8; /* [15:8] */
            __IO uint32_t reserved1            : 16;/* [31:16] */
        } ddth8r_bit;
    };

    /**
       * @brief dac d1odt register, offset:0x2c
       */
    union {
        __IO uint32_t d1odt;
        struct {
            __IO uint32_t d1odt                : 12;/* [11:0] */
            __IO uint32_t reserved1            : 20;/* [31:12] */
        } d1odt_bit;
    };

    /**
       * @brief dac d2odt register, offset:0x30
       */
    union {
        __IO uint32_t d2odt;
        struct {
            __IO uint32_t d2odt                : 12;/* [11:0] */
            __IO uint32_t reserved1            : 20;/* [31:12] */
        } d2odt_bit;
    };

    /**
       * @brief dac sr register, offset:0x34
       */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t reserved1            : 13;/* [12:0] */
            __IO uint32_t d1dmaudrf            : 1; /* [13] */
            __IO uint32_t reserved2            : 15;/* [28:14] */
            __IO uint32_t d2dmaudrf            : 1; /* [29] */
            __IO uint32_t reserved3            : 2;/* [31:30] */
        } sts_bit;
    };
} DAC_Type;
#define DAC                              ((DAC_Type *) DAC_BASE)

/** @defgroup DAC_exported_functions
  */
void DAC_Reset(void);
void DAC_Enable(DAC_Select_Type DAC_Select, confirm_state new_state);
void DAC_OutPut_Buffer_Enable(DAC_Select_Type DAC_Select, confirm_state new_state);
void DAC_Trigger_Enable(DAC_Select_Type DAC_Select, confirm_state new_state);
void DAC_Trigger_Select(DAC_Select_Type DAC_Select, DAC_Trigger_Type DAC_Trigger_source);
void DAC_Software_Trigger_Generate(DAC_Select_Type DAC_Select);
void DAC_Dual_Software_Trigger_Generate(void);
void DAC_Wave_Generate(DAC_Select_Type DAC_Select, DAC_Wave_Type DAC_wave);
void DAC_Mask_Amplitude_Select(DAC_Select_Type DAC_Select, DAC_Mask_Amplitude_Type DAC_Mask_amplitude);
void DAC_DMA_Enable(DAC_Select_Type DAC_Select, confirm_state new_state);
uint16_t DAC_Data_OutPut_Get(DAC_Select_Type DAC_Select);
void DAC_1_Data_Set(dac1_Aligned_Data_Type dac1_aligned, uint16_t dac1_data);
void DAC_2_Data_Set(dac2_Aligned_Data_Type dac2_aligned, uint16_t dac2_data);
void DAC_Dual_Data_Set(DAC_Dual_Data_Type DAC_dual, uint16_t data1, uint16_t data2);
void DAC_UDR_Enable(DAC_Select_Type DAC_Select, confirm_state new_state);
flag_status DAC_UDR_Flag_Get(DAC_Select_Type DAC_Select);
void DAC_UDR_Flag_Clear(DAC_Select_Type DAC_Select);

#ifdef __cplusplus
}
#endif

#endif
