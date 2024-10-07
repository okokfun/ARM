/**
 *******************************************************************************
 * @file  system_hc32f4a0sitb.h
 * @brief This file contains all the functions prototypes of the HC32 System.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __SYSTEM_HC32F4A0SITB_H__
#define __SYSTEM_HC32F4A0SITB_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <stdint.h>

/**
 * @addtogroup CMSIS
 */

/**
 * @addtogroup HC32F4A0_System
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('define')
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Global_Macros
 */

/**
 * @addtogroup HC32F4A0_System_Clock_Source
 */
#if !defined (MRC_VALUE)
#define MRC_VALUE                       (8000000UL)     /*!< Internal middle speed RC freq. */
#endif

#if !defined (LRC_VALUE)
#define LRC_VALUE                       (32768UL)       /*!< Internal low speed RC freq. */
#endif

#if !defined (RTCLRC_VALUE)
#define RTCLRC_VALUE                    (32768UL)       /*!< Internal RTC low speed RC freq. */
#endif

#if !defined (SWDTLRC_VALUE)
#define SWDTLRC_VALUE                   (10000UL)       /*!< Internal SWDT low speed RC freq. */
#endif

#if !defined (XTAL_VALUE)
#define XTAL_VALUE                      (8000000UL)     /*!< External high speed OSC freq. */
#endif

#if !defined (XTAL32_VALUE)
#define XTAL32_VALUE                    (32768UL)       /*!< External low speed OSC freq. */
#endif

#if !defined (HCLK_VALUE)
#define HCLK_VALUE                      (SystemCoreClock >> ((CM_CMU->SCFGR & CMU_SCFGR_HCLKS) >> CMU_SCFGR_HCLKS_POS))
#endif





/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Exported_Variable
 */

extern uint32_t SystemCoreClock;        /*!< 系统时钟频率(核心时钟) */
extern uint32_t HRC_VALUE;              /*!< HRC frequency */



/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup HC32F4A0_System_Global_Functions
 */

extern void SystemInit(void);             /*!< Initialize the system */
extern void SystemCoreClockUpdate(void);  /*!< Update SystemCoreClock variable */







#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_HC32F4A0SITB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
