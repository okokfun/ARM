/**
  **************************************************************************
  * @file     at32f435_437_dvp.h
  * @brief    at32f435_437 dvp header file
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
#ifndef __AT32F435_437_DVP_H
#define __AT32F435_437_DVP_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @addtogroup DVP
  */

/** @defgroup DVP_Event_flags_definition
  * @brief dvp event flag
  */
#define DVP_CFD_EVT_FLAG                 ((uint32_t)0x00000001) /*!< capture frame done event status flag */
#define DVP_OVR_EVT_FLAG                 ((uint32_t)0x00000002) /*!< data fifo overrun event status flag */
#define DVP_ESE_EVT_FLAG                 ((uint32_t)0x00000004) /*!< embedded synchronization error event status flag */
#define DVP_VS_EVT_FLAG                  ((uint32_t)0x00000008) /*!< vertical synchonization event status flag */
#define DVP_HS_EVT_FLAG                  ((uint32_t)0x00000010) /*!< horizontal synchonization event status flag */

/** @defgroup DVP_Interrupt_flags_definition
  * @brief dvp interrupt flag
  */
#define DVP_CFD_INT_FLAG                 ((uint32_t)0x80000001) /*!< capture frame done interrupt status flag */
#define DVP_OVR_INT_FLAG                 ((uint32_t)0x80000002) /*!< data fifo overrun interrupt status flag */
#define DVP_ESE_INT_FLAG                 ((uint32_t)0x80000004) /*!< embedded synchronization error interrupt status flag */
#define DVP_VS_INT_FLAG                  ((uint32_t)0x80000008) /*!< vertical synchonization interrupt status flag */
#define DVP_HS_INT_FLAG                  ((uint32_t)0x80000010) /*!< horizontal synchonization interrupt status flag */

/** @defgroup DVP_Interrupts_definition
  * @brief dvp interrupt
  */
#define DVP_CFD_INT                      ((uint32_t)0x00000001) /*!< capture frame done 中断 */
#define DVP_OVR_INT                      ((uint32_t)0x00000002) /*!< data fifo overrun 中断 */
#define DVP_ESE_INT                      ((uint32_t)0x00000004) /*!< embedded synchronization error 中断 */
#define DVP_VS_INT                       ((uint32_t)0x00000008) /*!< vertical synchonization 中断 */
#define DVP_HS_INT                       ((uint32_t)0x00000010) /*!< horizontal synchonization 中断 */

/** @defgroup DVP_exported_Types
  */

/**
  * @brief dvp cfm type
  */
typedef enum {
    DVP_CAP_FUNC_Mode_CONTINUOUS           = 0x00,
    DVP_CAP_FUNC_Mode_SINGLE               = 0x01
} DVP_cfm_Type;

/**
  * @brief dvp sm type
  */
typedef enum {
    DVP_Sync_Mode_HARDWARE                 = 0x00,
    DVP_Sync_Mode_EMBEDDED                 = 0x01
} DVP_sm_Type;

/**
  * @brief dvp ckp type
  */
typedef enum {
    DVP_CLK_Polarity_RISING                = 0x00,
    DVP_CLK_Polarity_FALLING               = 0x01
} DVP_ckp_Type;

/**
  * @brief dvp hsp type
  */
typedef enum {
    DVP_HSync_Polarity_HIGH                = 0x00,
    DVP_HSync_Polarity_LOW                 = 0x01
} DVP_hsp_Type;

/**
  * @brief dvp vsp type
  */
typedef enum {
    DVP_VSync_Polarity_LOW                 = 0x00,
    DVP_VSync_Polarity_HIGH                = 0x01
} DVP_vsp_Type;

/**
  * @brief dvp bfrc type
  */
typedef enum {
    DVP_BFRC_ALL                           = 0x00,
    DVP_BFRC_HALF                          = 0x01,
    DVP_BFRC_QUARTER                       = 0x02
} DVP_bfrc_Type;

/**
  * @brief dvp pdl type
  */
typedef enum {
    DVP_Pixel_Data_Length_8                = 0x00,
    DVP_Pixel_Data_Length_10               = 0x01,
    DVP_Pixel_Data_Length_12               = 0x02,
    DVP_Pixel_Data_Length_14               = 0x03
} DVP_pdl_Type;

/**
  * @brief dvp pcdc type
  */
typedef enum {
    DVP_PCDC_ALL                           = 0x00,
    DVP_PCDC_ONE_In_TWO                    = 0x01,
    DVP_PCDC_ONE_In_FOUR                   = 0x02,
    DVP_PCDC_TWO_In_FOUR                   = 0x03
} DVP_pcdc_Type;

/**
  * @brief dvp pcds type
  */
typedef enum {
    DVP_PCDS_CAP_FIRST                     = 0x00,
    DVP_PCDS_DROP_FIRST                    = 0x01
} DVP_pcds_Type;

/**
  * @brief dvp lcdc type
  */
typedef enum {
    DVP_LCDC_ALL                           = 0x00,
    DVP_LCDC_ONE_In_TWO                    = 0x01
} DVP_lcdc_Type;

/**
  * @brief dvp lcds type
  */
typedef enum {
    DVP_LCDS_CAP_FIRST                     = 0x00,
    DVP_LCDS_DROP_FIRST                    = 0x01
} DVP_lcds_Type;

/**
  * @brief dvp status basic type
  */
typedef enum {
    DVP_Status_HSYN                        = 0x00,
    DVP_Status_VSYN                        = 0x01,
    DVP_Status_OFNE                        = 0x02
} DVP_Status_Basic_Type;

/**
  * @brief dvp pcdes type
  */
typedef enum {
    DVP_PCDES_CAP_FIRST                    = 0x00,
    DVP_PCDES_DROP_FIRST                   = 0x01
} DVP_pcdes_Type;

/**
  * @brief dvp efdf type
  */
typedef enum {
    DVP_EFDF_ByPass                        = 0x00,
    DVP_EFDF_YUV422_UYVY                   = 0x04,
    DVP_EFDF_YUV422_YUYV                   = 0x05,
    DVP_EFDF_RGB565_555                    = 0x06,
    DVP_EFDF_Y8                            = 0x07
} DVP_efdf_Type;

/**
  * @brief dvp idus type
  */
typedef enum {
    DVP_IDUS_MSB                           = 0x00,
    DVP_IDUS_LSB                           = 0x01
} DVP_idus_Type;

/**
  * @brief dvp dmabt type
  */
typedef enum {
    DVP_DMABT_SINGLE                       = 0x00,
    DVP_DMABT_BURST                        = 0x01
} DVP_dmabt_Type;

/**
  * @brief dvp hseid type
  */
typedef enum {
    DVP_HSEID_Line_END                     = 0x00,
    DVP_HSEID_Line_Start                   = 0x01
} DVP_hseid_Type;

/**
  * @brief dvp vseid type
  */
typedef enum {
    DVP_VSEID_Frame_END                    = 0x00,
    DVP_VSEID_FRMAE_Start                  = 0x01
} DVP_vseid_Type;
/**
  * @brief dvp idun type
  */
typedef enum {
    DVP_IDUN_0                             = 0x00,
    DVP_IDUN_2                             = 0x01,
    DVP_IDUN_4                             = 0x02,
    DVP_IDUN_6                             = 0x03
} DVP_idun_Type;

typedef struct {
    /**
      * @brief dvp ctrl register, offset:0x00
      */
    union {
        __IO uint32_t ctrl;
        struct {
            __IO uint32_t cap                  : 1; /* [0] */
            __IO uint32_t cfm                  : 1; /* [1] */
            __IO uint32_t crp                  : 1; /* [2] */
            __IO uint32_t jpeg                 : 1; /* [3] */
            __IO uint32_t sm                   : 1; /* [4] */
            __IO uint32_t ckp                  : 1; /* [5] */
            __IO uint32_t hsp                  : 1; /* [6] */
            __IO uint32_t vsp                  : 1; /* [7] */
            __IO uint32_t bfrc                 : 2; /* [9:8] */
            __IO uint32_t pdl                  : 2; /* [11:10] */
            __IO uint32_t reserved1            : 2; /* [13:12] */
            __IO uint32_t ena                  : 1; /* [14] */
            __IO uint32_t reserved2            : 1; /* [15] */
            __IO uint32_t pcdc                 : 2; /* [17:16] */
            __IO uint32_t pcds                 : 1; /* [18] */
            __IO uint32_t lcdc                 : 1; /* [19] */
            __IO uint32_t lcds                 : 1; /* [20] */
            __IO uint32_t reserved3            : 11;/* [31:21] */
        } ctrl_bit;
    };

    /**
      * @brief dvp sts register, offset:0x04
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t hsyn                 : 1; /* [0] */
            __IO uint32_t vsyn                 : 1; /* [1] */
            __IO uint32_t ofne                 : 1; /* [2] */
            __IO uint32_t reserved1            : 29;/* [31:3] */
        } sts_bit;
    };

    /**
      * @brief dvp ests register, offset:0x08
      */
    union {
        __IO uint32_t ests;
        struct {
            __IO uint32_t cfdes                : 1; /* [0] */
            __IO uint32_t ovres                : 1; /* [1] */
            __IO uint32_t esees                : 1; /* [2] */
            __IO uint32_t vses                 : 1; /* [3] */
            __IO uint32_t hses                 : 1; /* [4] */
            __IO uint32_t reserved1            : 27;/* [31:5] */
        } ests_bit;
    };

    /**
      * @brief dvp ier register, offset:0x0C
      */
    union {
        __IO uint32_t ier;
        struct {
            __IO uint32_t cfdie                : 1; /* [0] */
            __IO uint32_t ovrie                : 1; /* [1] */
            __IO uint32_t eseie                : 1; /* [2] */
            __IO uint32_t vsie                 : 1; /* [3] */
            __IO uint32_t hsie                 : 1; /* [4] */
            __IO uint32_t reserved1            : 27;/* [31:5] */
        } ier_bit;
    };

    /**
      * @brief dvp ists register, offset:0x10
      */
    union {
        __IO uint32_t ists;
        struct {
            __IO uint32_t cfdis                : 1; /* [0] */
            __IO uint32_t ovris                : 1; /* [1] */
            __IO uint32_t eseis                : 1; /* [2] */
            __IO uint32_t vsis                 : 1; /* [3] */
            __IO uint32_t hsis                 : 1; /* [4] */
            __IO uint32_t reserved1            : 27;/* [31:5] */
        } ists_bit;
    };

    /**
      * @brief dvp iclr register, offset:0x14
      */
    union {
        __IO uint32_t iclr;
        struct {
            __IO uint32_t cfdic                : 1; /* [0] */
            __IO uint32_t ovric                : 1; /* [1] */
            __IO uint32_t eseic                : 1; /* [2] */
            __IO uint32_t vsic                 : 1; /* [3] */
            __IO uint32_t hsic                 : 1; /* [4] */
            __IO uint32_t reserved1            : 27;/* [31:5] */
        } iclr_bit;
    };

    /**
      * @brief dvp scr register, offset:0x18
      */
    union {
        __IO uint32_t scr;
        struct {
            __IO uint32_t fmsc                 : 8; /* [7:0] */
            __IO uint32_t lnsc                 : 8; /* [15:8] */
            __IO uint32_t lnec                 : 8; /* [23:16] */
            __IO uint32_t fmec                 : 8; /* [31:24] */
        } scr_bit;
    };

    /**
      * @brief dvp sur register, offset:0x1C
      */
    union {
        __IO uint32_t sur;
        struct {
            __IO uint32_t fmsu                 : 8; /* [7:0] */
            __IO uint32_t lnsu                 : 8; /* [15:8] */
            __IO uint32_t lneu                 : 8; /* [23:16] */
            __IO uint32_t fmeu                 : 8; /* [31:24] */
        } sur_bit;
    };

    /**
      * @brief dvp cwst register, offset:0x20
      */
    union {
        __IO uint32_t cwst;
        struct {
            __IO uint32_t chstr                : 14;/* [13:0] */
            __IO uint32_t reserved1            : 2; /* [15:14] */
            __IO uint32_t cvstr                : 13;/* [28:16] */
            __IO uint32_t reserved2            : 3; /* [31:29] */
        } cwst_bit;
    };

    /**
      * @brief dvp cwsz register, offset:0x24
      */
    union {
        __IO uint32_t cwsz;
        struct {
            __IO uint32_t chnum                : 14;/* [13:0] */
            __IO uint32_t reserved1            : 2; /* [15:14] */
            __IO uint32_t cvnum                : 14;/* [29:16] */
            __IO uint32_t reserved2            : 2; /* [31:30] */
        } cwsz_bit;
    };

    /**
      * @brief dvp dt register, offset:0x28
      */
    union {
        __IO uint32_t dt;
        struct {
            __IO uint32_t dr0                  : 8; /* [7:0] */
            __IO uint32_t dr1                  : 8; /* [15:8] */
            __IO uint32_t dr2                  : 8; /* [23:16] */
            __IO uint32_t dr3                  : 8; /* [31:24] */
        } dt_bit;
    };

    /**
      * @brief dvp reserved1 register, offset:0x2C-0x3C
      */
    __IO uint32_t reserved1[5];

    /**
      * @brief dvp actrl register, offset:0x40
      */
    union {
        __IO uint32_t actrl;
        struct {
            __IO uint32_t eisre                : 1; /* [0] */
            __IO uint32_t efrce                : 1; /* [1] */
            __IO uint32_t mibe                 : 1; /* [2] */
            __IO uint32_t pcdes                : 1; /* [3] */
            __IO uint32_t efdf                 : 3; /* [6:4] */
            __IO uint32_t reserved1            : 1; /* [7] */
            __IO uint32_t idun                 : 2; /* [9:8] */
            __IO uint32_t idus                 : 1; /* [10] */
            __IO uint32_t reserved2            : 1; /* [11] */
            __IO uint32_t dmabt                : 1; /* [12] */
            __IO uint32_t reserved3            : 1; /* [13] */
            __IO uint32_t reserved4            : 1; /* [14] */
            __IO uint32_t reserved5            : 1; /* [15] */
            __IO uint32_t hseid                : 1; /* [16] */
            __IO uint32_t vseid                : 1; /* [17] */
            __IO uint32_t reserved6            : 1; /* [18] */
            __IO uint32_t reserved7            : 2; /* [20:19] */
            __IO uint32_t reserved8            : 11;/* [31:21] */
        } actrl_bit;
    };

    /**
      * @brief dvp reserved2 register, offset:0x44
      */
    __IO uint32_t reserved2;

    /**
      * @brief dvp hscf register, offset:0x48
      */
    union {
        __IO uint32_t hscf;
        struct {
            __IO uint32_t hsrss                : 13;/* [12:0] */
            __IO uint32_t reserved1            : 3; /* [15:13] */
            __IO uint32_t hsrts                : 13;/* [28:16] */
            __IO uint32_t reserved2            : 3; /* [31:29] */
        } hscf_bit;
    };

    /**
      * @brief dvp vscf register, offset:0x4C
      */
    union {
        __IO uint32_t vscf;
        struct {
            __IO uint32_t vsrss                : 13;/* [12:0] */
            __IO uint32_t reserved1            : 3; /* [15:13] */
            __IO uint32_t vsrts                : 13;/* [28:16] */
            __IO uint32_t reserved2            : 3; /* [31:29] */
        } vscf_bit;
    };

    /**
      * @brief dvp frf register, offset:0x50
      */
    union {
        __IO uint32_t frf;
        struct {
            __IO uint32_t efrcsf               : 5; /* [4:0] */
            __IO uint32_t reserved1            : 3; /* [7:5] */
            __IO uint32_t efrctf               : 5; /* [12:8] */
            __IO uint32_t reserved2            : 19;/* [31:13] */
        } frf_bit;
    };

    /**
      * @brief dvp bth register, offset:0x54
      */
    union {
        __IO uint32_t bth;
        struct {
            __IO uint32_t mibthd               : 8; /* [7:0] */
            __IO uint32_t reserved1            : 24;/* [31:8] */
        } bth_bit;
    };

} DVP_Type;
#define DVP                              ((DVP_Type *) DVP_BASE)

/** @defgroup DVP_exported_functions
  */
void DVP_Reset(void);
void DVP_Capture_Enable(confirm_state new_state);
void DVP_Capture_Mode_Set(DVP_cfm_Type cap_Mode);
void DVP_Window_Crop_Enable(confirm_state new_state);
void DVP_Window_Crop_Set(uint16_t crop_x, uint16_t crop_y, uint16_t crop_w, uint16_t crop_h, uint8_t bytes);
void DVP_Jpeg_Enable(confirm_state new_state);
void DVP_Sync_Mode_Set(DVP_sm_Type sync_Mode);
void DVP_Sync_code_Set(uint8_t fmsc, uint8_t fmec, uint8_t lnsc, uint8_t lnec);
void DVP_Sync_unmask_Set(uint8_t fmsu, uint8_t fmeu, uint8_t lnsu, uint8_t lneu);
void DVP_PCLK_Polarity_Set(DVP_ckp_Type eage);
void DVP_HSync_Polarity_Set(DVP_hsp_Type hsync_pol);
void DVP_VSync_Polarity_Set(DVP_vsp_Type vsync_pol);
void DVP_Basic_Frame_rate_Control_Set(DVP_bfrc_Type DVP_bfrc);
void DVP_Pixel_Data_Length_Set(DVP_pdl_Type DVP_pdl);
void DVP_Enable(confirm_state new_state);
void DVP_ZoomOut_Select(DVP_pcdes_Type DVP_pcdes);
void DVP_ZoomOut_Set(DVP_pcdc_Type DVP_pcdc, DVP_pcds_Type DVP_pcds, DVP_lcdc_Type DVP_lcdc, DVP_lcds_Type DVP_lcds);
flag_status DVP_Basic_Status_Get(DVP_Status_Basic_Type DVP_Status_basic);
void DVP_Interrupt_Enable(uint32_t DVP_int, confirm_state new_state);
flag_status DVP_Flag_Get(uint32_t flag);
void DVP_Flag_Clear(uint32_t flag);
void DVP_Enhanced_Scaling_Resize_Enable(confirm_state new_state);
void DVP_Enhanced_Scaling_Resize_Set(uint16_t src_w, uint16_t des_w, uint16_t src_h, uint16_t des_h);
void DVP_Enhanced_Framerate_Set(uint16_t efrcsf, uint16_t efrctf, confirm_state new_state);
void DVP_Monochrome_Image_Binarization_Set(uint8_t mibthd, confirm_state new_state);
void DVP_Enhanced_Data_Format_Set(DVP_efdf_Type DVP_efdf);
void DVP_Input_Data_Unused_Set(DVP_idus_Type DVP_idus, DVP_idun_Type DVP_idun);
void DVP_DMA_Burst_Set(DVP_dmabt_Type DVP_dmabt);
void DVP_Sync_Event_Interrupt_Set(DVP_hseid_Type DVP_hseid, DVP_vseid_Type DVP_vseid);

#ifdef __cplusplus
}
#endif

#endif
