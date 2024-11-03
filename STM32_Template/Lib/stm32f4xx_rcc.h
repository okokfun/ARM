/**
  ******************************************************************************
  * 文件:    stm32f4xx_rcc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 RCC 固件库的所有功能原型。
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* 定义以防止递归包含 -------------------------------------*/
#ifndef __STM32F4xx_RCC_H
#define __STM32F4xx_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup RCC
  */

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint32_t SYSCLK_Frequency; /*!<  以 Hz 表示的 SYSCLK 时钟频率 */
    uint32_t HCLK_Frequency;   /*!<  HCLK 时钟频率以 Hz 表示   */
    uint32_t PCLK1_Frequency;  /*!<  PCLK1 时钟频率，单位为 Hz  */
    uint32_t PCLK2_Frequency;  /*!<  PCLK2 时钟频率，单位为 Hz  */
} RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  */

/** @defgroup RCC_HSE_configuration
  */
#define RCC_HSE_OFF                      ((uint8_t)0x00)
#define RCC_HSE_ON                       ((uint8_t)0x01)
#define RCC_HSE_Bypass                   ((uint8_t)0x05)
#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/** @defgroup RCC_LSE_Dual_Mode_Selection
  */
#define RCC_LSE_LOWPOWER_MODE           ((uint8_t)0x00)
#define RCC_LSE_HIGHDRIVE_MODE          ((uint8_t)0x01)
#define IS_RCC_LSE_MODE(MODE)           (((MODE) == RCC_LSE_LOWPOWER_MODE) || \
        ((MODE) == RCC_LSE_HIGHDRIVE_MODE))

/** @defgroup RCC_PLLSAIDivR_Factor
  */
#define RCC_PLLSAIDivR_Div2                ((uint32_t)0x00000000)
#define RCC_PLLSAIDivR_Div4                ((uint32_t)0x00010000)
#define RCC_PLLSAIDivR_Div8                ((uint32_t)0x00020000)
#define RCC_PLLSAIDivR_Div16               ((uint32_t)0x00030000)
#define IS_RCC_PLLSAI_DIVR_VALUE(VALUE) (((VALUE) == RCC_PLLSAIDivR_Div2) ||\
        ((VALUE) == RCC_PLLSAIDivR_Div4)  ||\
        ((VALUE) == RCC_PLLSAIDivR_Div8)  ||\
        ((VALUE) == RCC_PLLSAIDivR_Div16))

/** @defgroup RCC_PLL_Clock_Source
  */
#define RCC_PLLSource_HSI                ((uint32_t)0x00000000)
#define RCC_PLLSource_HSE                ((uint32_t)0x00400000)
#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI) || \
                                   ((SOURCE) == RCC_PLLSource_HSE))
#define IS_RCC_PLLM_VALUE(VALUE) ((VALUE) <= 63)
#define IS_RCC_PLLN_VALUE(VALUE) ((50 <= (VALUE)) && ((VALUE) <= 432))
#define IS_RCC_PLLP_VALUE(VALUE) (((VALUE) == 2) || ((VALUE) == 4) || ((VALUE) == 6) || ((VALUE) == 8))
#define IS_RCC_PLLQ_VALUE(VALUE) ((4 <= (VALUE)) && ((VALUE) <= 15))
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
#define IS_RCC_PLLR_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 7))
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */

#define IS_RCC_PLLI2SN_VALUE(VALUE) ((50 <= (VALUE)) && ((VALUE) <= 432))
#define IS_RCC_PLLI2SR_VALUE(VALUE) ((2 <= (VALUE))  && ((VALUE) <= 7))
#define IS_RCC_PLLI2SM_VALUE(VALUE) ((2 <= (VALUE))  && ((VALUE) <= 63))
#define IS_RCC_PLLI2SQ_VALUE(VALUE) ((2 <= (VALUE))  && ((VALUE) <= 15))
#if defined(STM32F446xx)
#define IS_RCC_PLLI2SP_VALUE(VALUE) (((VALUE) == 2) || ((VALUE) == 4) || ((VALUE) == 6) || ((VALUE) == 8))
#define IS_RCC_PLLSAIM_VALUE(VALUE) ((VALUE) <= 63)
#elif  defined(STM32F412xG) || defined(STM32F413_423xx)
#define IS_RCC_PLLI2SP_VALUE(VALUE) (((VALUE) == 2) || ((VALUE) == 4) || ((VALUE) == 6) || ((VALUE) == 8))
#else
#endif /* STM32F446xx */
#define IS_RCC_PLLSAIN_VALUE(VALUE) ((50 <= (VALUE)) && ((VALUE) <= 432))
#if defined(STM32F446xx) || defined(STM32F469_479xx)
#define IS_RCC_PLLSAIP_VALUE(VALUE) (((VALUE) == 2) || ((VALUE) == 4) || ((VALUE) == 6) || ((VALUE) == 8))
#endif /* STM32F446xx || STM32F469_479xx */
#define IS_RCC_PLLSAIQ_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 15))
#define IS_RCC_PLLSAIR_VALUE(VALUE) ((2 <= (VALUE)) && ((VALUE) <= 7))

#define IS_RCC_PLLSAI_DIVQ_VALUE(VALUE) ((1 <= (VALUE)) && ((VALUE) <= 32))
#define IS_RCC_PLLI2S_DIVQ_VALUE(VALUE) ((1 <= (VALUE)) && ((VALUE) <= 32))

#if defined(STM32F413_423xx)
#define IS_RCC_PLLI2S_DIVR_VALUE(VALUE) ((1 <= (VALUE)) && ((VALUE) <= 32))
#define IS_RCC_PLL_DIVR_VALUE(VALUE)    ((1 <= (VALUE)) && ((VALUE) <= 32))
#endif /* STM32F413_423xx */

/** @defgroup RCC_System_Clock_Source
  */

#if  defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
#define RCC_SYSCLKSource_HSI             ((uint32_t)0x00000000)
#define RCC_SYSCLKSource_HSE             ((uint32_t)0x00000001)
#define RCC_SYSCLKSource_PLLPCLK         ((uint32_t)0x00000002)
#define RCC_SYSCLKSource_PLLRCLK         ((uint32_t)0x00000003)
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLPCLK) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLRCLK))
/* Add legacy definition */
#define  RCC_SYSCLKSource_PLLCLK    RCC_SYSCLKSource_PLLPCLK
#endif /* STM32F446xx */

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F469_479xx)
#define RCC_SYSCLKSource_HSI             ((uint32_t)0x00000000)
#define RCC_SYSCLKSource_HSE             ((uint32_t)0x00000001)
#define RCC_SYSCLKSource_PLLCLK          ((uint32_t)0x00000002)
#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK))
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F469_479xx */

/** @defgroup RCC_AHB_Clock_Source
  */
#define RCC_SYSCLK_Div1                  ((uint32_t)0x00000000)
#define RCC_SYSCLK_Div2                  ((uint32_t)0x00000080)
#define RCC_SYSCLK_Div4                  ((uint32_t)0x00000090)
#define RCC_SYSCLK_Div8                  ((uint32_t)0x000000A0)
#define RCC_SYSCLK_Div16                 ((uint32_t)0x000000B0)
#define RCC_SYSCLK_Div64                 ((uint32_t)0x000000C0)
#define RCC_SYSCLK_Div128                ((uint32_t)0x000000D0)
#define RCC_SYSCLK_Div256                ((uint32_t)0x000000E0)
#define RCC_SYSCLK_Div512                ((uint32_t)0x000000F0)
#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))

/** @defgroup RCC_APB1_APB2_Clock_Source
  */
#define RCC_HCLK_Div1                    ((uint32_t)0x00000000)
#define RCC_HCLK_Div2                    ((uint32_t)0x00001000)
#define RCC_HCLK_Div4                    ((uint32_t)0x00001400)
#define RCC_HCLK_Div8                    ((uint32_t)0x00001800)
#define RCC_HCLK_Div16                   ((uint32_t)0x00001C00)
#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))

/** @defgroup RCC_Interrupt_Source
  */
#define RCC_IT_LSIRDY                    ((uint8_t)0x01)
#define RCC_IT_LSERDY                    ((uint8_t)0x02)
#define RCC_IT_HSIRDY                    ((uint8_t)0x04)
#define RCC_IT_HSERDY                    ((uint8_t)0x08)
#define RCC_IT_PLLRDY                    ((uint8_t)0x10)
#define RCC_IT_PLLI2SRDY                 ((uint8_t)0x20)
#define RCC_IT_PLLSAIRDY                 ((uint8_t)0x40)
#define RCC_IT_CSS                       ((uint8_t)0x80)

#define IS_RCC_IT(IT) ((((IT) & (uint8_t)0x80) == 0x00) && ((IT) != 0x00))
#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS) || \
                           ((IT) == RCC_IT_PLLSAIRDY) || ((IT) == RCC_IT_PLLI2SRDY))
#define IS_RCC_CLEAR_IT(IT)((IT) != 0x00)


/** @defgroup RCC_LSE_Configuration
  */
#define RCC_LSE_OFF                      ((uint8_t)0x00)
#define RCC_LSE_ON                       ((uint8_t)0x01)
#define RCC_LSE_Bypass                   ((uint8_t)0x04)
#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))

/** @defgroup RCC_RTC_Clock_Source
  */
#define RCC_RTCCLKSource_LSE             ((uint32_t)0x00000100)
#define RCC_RTCCLKSource_LSI             ((uint32_t)0x00000200)
#define RCC_RTCCLKSource_HSE_Div2        ((uint32_t)0x00020300)
#define RCC_RTCCLKSource_HSE_Div3        ((uint32_t)0x00030300)
#define RCC_RTCCLKSource_HSE_Div4        ((uint32_t)0x00040300)
#define RCC_RTCCLKSource_HSE_Div5        ((uint32_t)0x00050300)
#define RCC_RTCCLKSource_HSE_Div6        ((uint32_t)0x00060300)
#define RCC_RTCCLKSource_HSE_Div7        ((uint32_t)0x00070300)
#define RCC_RTCCLKSource_HSE_Div8        ((uint32_t)0x00080300)
#define RCC_RTCCLKSource_HSE_Div9        ((uint32_t)0x00090300)
#define RCC_RTCCLKSource_HSE_Div10       ((uint32_t)0x000A0300)
#define RCC_RTCCLKSource_HSE_Div11       ((uint32_t)0x000B0300)
#define RCC_RTCCLKSource_HSE_Div12       ((uint32_t)0x000C0300)
#define RCC_RTCCLKSource_HSE_Div13       ((uint32_t)0x000D0300)
#define RCC_RTCCLKSource_HSE_Div14       ((uint32_t)0x000E0300)
#define RCC_RTCCLKSource_HSE_Div15       ((uint32_t)0x000F0300)
#define RCC_RTCCLKSource_HSE_Div16       ((uint32_t)0x00100300)
#define RCC_RTCCLKSource_HSE_Div17       ((uint32_t)0x00110300)
#define RCC_RTCCLKSource_HSE_Div18       ((uint32_t)0x00120300)
#define RCC_RTCCLKSource_HSE_Div19       ((uint32_t)0x00130300)
#define RCC_RTCCLKSource_HSE_Div20       ((uint32_t)0x00140300)
#define RCC_RTCCLKSource_HSE_Div21       ((uint32_t)0x00150300)
#define RCC_RTCCLKSource_HSE_Div22       ((uint32_t)0x00160300)
#define RCC_RTCCLKSource_HSE_Div23       ((uint32_t)0x00170300)
#define RCC_RTCCLKSource_HSE_Div24       ((uint32_t)0x00180300)
#define RCC_RTCCLKSource_HSE_Div25       ((uint32_t)0x00190300)
#define RCC_RTCCLKSource_HSE_Div26       ((uint32_t)0x001A0300)
#define RCC_RTCCLKSource_HSE_Div27       ((uint32_t)0x001B0300)
#define RCC_RTCCLKSource_HSE_Div28       ((uint32_t)0x001C0300)
#define RCC_RTCCLKSource_HSE_Div29       ((uint32_t)0x001D0300)
#define RCC_RTCCLKSource_HSE_Div30       ((uint32_t)0x001E0300)
#define RCC_RTCCLKSource_HSE_Div31       ((uint32_t)0x001F0300)
#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div2) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div3) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div4) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div5) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div6) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div7) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div8) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div9) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div10) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div11) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div12) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div13) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div14) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div15) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div16) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div17) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div18) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div19) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div20) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div21) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div22) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div23) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div24) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div25) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div26) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div27) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div28) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div29) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div30) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div31))

#if defined(STM32F410xx) || defined(STM32F413_423xx)
/** @defgroup RCCEx_LPTIM1_Clock_Source  RCC LPTIM1 Clock Source
  */
#define RCC_LPTIM1CLKSOURCE_PCLK            ((uint32_t)0x00000000)
#define RCC_LPTIM1CLKSOURCE_HSI            ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_0)
#define RCC_LPTIM1CLKSOURCE_LSI            ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_1)
#define RCC_LPTIM1CLKSOURCE_LSE            ((uint32_t)RCC_DCKCFGR2_LPTIM1SEL_0 | RCC_DCKCFGR2_LPTIM1SEL_1)

#define IS_RCC_LPTIM1_CLOCKSOURCE(SOURCE) (((SOURCE) == RCC_LPTIM1CLKSOURCE_PCLK) || ((SOURCE) == RCC_LPTIM1CLKSOURCE_HSI) || \
        ((SOURCE) == RCC_LPTIM1CLKSOURCE_LSI) || ((SOURCE) == RCC_LPTIM1CLKSOURCE_LSE))
/* Legacy Defines */
#define IS_RCC_LPTIM1_SOURCE           IS_RCC_LPTIM1_CLOCKSOURCE

#if defined(STM32F410xx)

/** @defgroup RCCEx_I2S_APB_Clock_Source  RCC I2S APB Clock Source
  */
#define RCC_I2SAPBCLKSOURCE_PLLR            ((uint32_t)0x00000000)
#define RCC_I2SAPBCLKSOURCE_EXT             ((uint32_t)RCC_DCKCFGR_I2SSRC_0)
#define RCC_I2SAPBCLKSOURCE_PLLSRC          ((uint32_t)RCC_DCKCFGR_I2SSRC_1)
#define IS_RCC_I2SCLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2SAPBCLKSOURCE_PLLR) || ((SOURCE) == RCC_I2SAPBCLKSOURCE_EXT) || \
                                      ((SOURCE) == RCC_I2SAPBCLKSOURCE_PLLSRC))
#endif /* STM32F413_423xx */
#endif /* STM32F410xx  || STM32F413_423xx */

#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
/** @defgroup RCC_I2S_Clock_Source
  */
#define RCC_I2SCLKSource_PLLI2S             ((uint32_t)0x00)
#define RCC_I2SCLKSource_Ext                ((uint32_t)RCC_DCKCFGR_I2S1SRC_0)
#define RCC_I2SCLKSource_PLL                ((uint32_t)RCC_DCKCFGR_I2S1SRC_1)
#define RCC_I2SCLKSource_HSI_HSE            ((uint32_t)RCC_DCKCFGR_I2S1SRC_0 | RCC_DCKCFGR_I2S1SRC_1)

#define IS_RCC_I2SCLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2SCLKSource_PLLI2S) || ((SOURCE) == RCC_I2SCLKSource_Ext) || \
                                      ((SOURCE) == RCC_I2SCLKSource_PLL) || ((SOURCE) == RCC_I2SCLKSource_HSI_HSE))

/** @defgroup RCC_I2S_APBBus
  */
#define RCC_I2SBus_APB1             ((uint8_t)0x00)
#define RCC_I2SBus_APB2             ((uint8_t)0x01)
#define IS_RCC_I2S_APBx(BUS) (((BUS) == RCC_I2SBus_APB1) || ((BUS) == RCC_I2SBus_APB2))
#if defined(STM32F446xx)
/** @defgroup RCC_SAI_Clock_Source
  */
#define RCC_SAICLKSource_PLLSAI             ((uint32_t)0x00)
#define RCC_SAICLKSource_PLLI2S             ((uint32_t)RCC_DCKCFGR_SAI1SRC_0)
#define RCC_SAICLKSource_PLL                ((uint32_t)RCC_DCKCFGR_SAI1SRC_1)
#define RCC_SAICLKSource_HSI_HSE            ((uint32_t)RCC_DCKCFGR_SAI1SRC_0 | RCC_DCKCFGR_SAI1SRC_1)

#define IS_RCC_SAICLK_SOURCE(SOURCE) (((SOURCE) == RCC_SAICLKSource_PLLSAI) || ((SOURCE) == RCC_SAICLKSource_PLLI2S) || \
                                      ((SOURCE) == RCC_SAICLKSource_PLL) || ((SOURCE) == RCC_SAICLKSource_HSI_HSE))

/** @defgroup RCC_SAI_Instance
  */
#define RCC_SAIInstance_SAI1             ((uint8_t)0x00)
#define RCC_SAIInstance_SAI2             ((uint8_t)0x01)
#define IS_RCC_SAI_INSTANCE(BUS) (((BUS) == RCC_SAIInstance_SAI1) || ((BUS) == RCC_SAIInstance_SAI2))
#endif /* STM32F446xx */
#if defined(STM32F413_423xx)

/** @defgroup RCC_SAI_BlockA_Clock_Source
  */
#define RCC_SAIACLKSource_PLLI2S_R             ((uint32_t)0x00000000)
#define RCC_SAIACLKSource_I2SCKIN              ((uint32_t)RCC_DCKCFGR_SAI1ASRC_0)
#define RCC_SAIACLKSource_PLLR                 ((uint32_t)RCC_DCKCFGR_SAI1ASRC_1)
#define RCC_SAIACLKSource_HSI_HSE              ((uint32_t)RCC_DCKCFGR_SAI1ASRC_0 | RCC_DCKCFGR_SAI1ASRC_1)

#define IS_RCC_SAIACLK_SOURCE(SOURCE) (((SOURCE) == RCC_SAIACLKSource_PLLI2S_R) || ((SOURCE) == RCC_SAIACLKSource_I2SCKIN) || \
                                       ((SOURCE) == RCC_SAIACLKSource_PLLR) || ((SOURCE) == RCC_SAIACLKSource_HSI_HSE))

/** @defgroup RCC_SAI_BlockB_Clock_Source
  */
#define RCC_SAIBCLKSource_PLLI2S_R             ((uint32_t)0x00000000)
#define RCC_SAIBCLKSource_I2SCKIN              ((uint32_t)RCC_DCKCFGR_SAI1BSRC_0)
#define RCC_SAIBCLKSource_PLLR                 ((uint32_t)RCC_DCKCFGR_SAI1BSRC_1)
#define RCC_SAIBCLKSource_HSI_HSE              ((uint32_t)RCC_DCKCFGR_SAI1BSRC_0 | RCC_DCKCFGR_SAI1BSRC_1)

#define IS_RCC_SAIBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SAIBCLKSource_PLLI2S_R) || ((SOURCE) == RCC_SAIBCLKSource_I2SCKIN) || \
                                       ((SOURCE) == RCC_SAIBCLKSource_PLLR) || ((SOURCE) == RCC_SAIBCLKSource_HSI_HSE))
#endif /* STM32F413_423xx */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F469_479xx)
/** @defgroup RCC_I2S_Clock_Source
  */
#define RCC_I2S2CLKSource_PLLI2S             ((uint8_t)0x00)
#define RCC_I2S2CLKSource_Ext                ((uint8_t)0x01)

#define IS_RCC_I2SCLK_SOURCE(SOURCE) (((SOURCE) == RCC_I2S2CLKSource_PLLI2S) || ((SOURCE) == RCC_I2S2CLKSource_Ext))

/** @defgroup RCC_SAI_BlockA_Clock_Source
  */
#define RCC_SAIACLKSource_PLLSAI             ((uint32_t)0x00000000)
#define RCC_SAIACLKSource_PLLI2S             ((uint32_t)0x00100000)
#define RCC_SAIACLKSource_Ext                ((uint32_t)0x00200000)

#define IS_RCC_SAIACLK_SOURCE(SOURCE) (((SOURCE) == RCC_SAIACLKSource_PLLI2S) ||\
                                       ((SOURCE) == RCC_SAIACLKSource_PLLSAI) ||\
                                       ((SOURCE) == RCC_SAIACLKSource_Ext))

/** @defgroup RCC_SAI_BlockB_Clock_Source
  */
#define RCC_SAIBCLKSource_PLLSAI             ((uint32_t)0x00000000)
#define RCC_SAIBCLKSource_PLLI2S             ((uint32_t)0x00400000)
#define RCC_SAIBCLKSource_Ext                ((uint32_t)0x00800000)

#define IS_RCC_SAIBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SAIBCLKSource_PLLI2S) ||\
                                       ((SOURCE) == RCC_SAIBCLKSource_PLLSAI) ||\
                                       ((SOURCE) == RCC_SAIBCLKSource_Ext))
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE || STM32F469_479xx */

/** @defgroup RCC_TIM_PRescaler_Selection
  */
#define RCC_TIMPrescDesactivated             ((uint8_t)0x00)
#define RCC_TIMPrescActivated                ((uint8_t)0x01)

#define IS_RCC_TIMCLK_PRESCALER(VALUE) (((VALUE) == RCC_TIMPrescDesactivated) || ((VALUE) == RCC_TIMPrescActivated))

#if defined(STM32F469_479xx)
/** @defgroup RCC_DSI_Clock_Source_Selection
  */
#define RCC_DSICLKSource_PHY                ((uint8_t)0x00)
#define RCC_DSICLKSource_PLLR               ((uint8_t)0x01)
#define IS_RCC_DSI_CLOCKSOURCE(CLKSOURCE)   (((CLKSOURCE) == RCC_DSICLKSource_PHY) || \
        ((CLKSOURCE) == RCC_DSICLKSource_PLLR))
#endif /* STM32F469_479xx */

#if  defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
/** @defgroup RCC_SDIO_Clock_Source_Selection
  */
#define RCC_SDIOCLKSource_48MHZ              ((uint8_t)0x00)
#define RCC_SDIOCLKSource_SYSCLK             ((uint8_t)0x01)
#define IS_RCC_SDIO_CLOCKSOURCE(CLKSOURCE)   (((CLKSOURCE) == RCC_SDIOCLKSource_48MHZ) || \
        ((CLKSOURCE) == RCC_SDIOCLKSource_SYSCLK))


/** @defgroup RCC_48MHZ_Clock_Source_Selection
  */
#if  defined(STM32F446xx) || defined(STM32F469_479xx)
#define RCC_48MHZCLKSource_PLL                ((uint8_t)0x00)
#define RCC_48MHZCLKSource_PLLSAI             ((uint8_t)0x01)
#define IS_RCC_48MHZ_CLOCKSOURCE(CLKSOURCE)   (((CLKSOURCE) == RCC_48MHZCLKSource_PLL) || \
        ((CLKSOURCE) == RCC_48MHZCLKSource_PLLSAI))
#endif /* STM32F446xx || STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define RCC_CK48CLKSOURCE_PLLQ                ((uint8_t)0x00)
#define RCC_CK48CLKSOURCE_PLLI2SQ             ((uint8_t)0x01) /* Only for STM32F412xG and STM32F413_423xx Devices */
#define IS_RCC_48MHZ_CLOCKSOURCE(CLKSOURCE)   (((CLKSOURCE) == RCC_CK48CLKSOURCE_PLLQ) || \
        ((CLKSOURCE) == RCC_CK48CLKSOURCE_PLLI2SQ))
#endif /* STM32F412xG || STM32F413_423xx */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */

#if defined(STM32F446xx)
/** @defgroup RCC_SPDIFRX_Clock_Source_Selection
  */
#define RCC_SPDIFRXCLKSource_PLLR                 ((uint8_t)0x00)
#define RCC_SPDIFRXCLKSource_PLLI2SP              ((uint8_t)0x01)
#define IS_RCC_SPDIFRX_CLOCKSOURCE(CLKSOURCE)     (((CLKSOURCE) == RCC_SPDIFRXCLKSource_PLLR) || \
        ((CLKSOURCE) == RCC_SPDIFRXCLKSource_PLLI2SP))

/** @defgroup RCC_CEC_Clock_Source_Selection
  */
#define RCC_CECCLKSource_HSIDiv488            ((uint8_t)0x00)
#define RCC_CECCLKSource_LSE                  ((uint8_t)0x01)
#define IS_RCC_CEC_CLOCKSOURCE(CLKSOURCE)     (((CLKSOURCE) == RCC_CECCLKSource_HSIDiv488) || \
        ((CLKSOURCE) == RCC_CECCLKSource_LSE))

/** @defgroup RCC_AHB1_ClockGating
  */
#define RCC_AHB1ClockGating_APB1Bridge         ((uint32_t)0x00000001)
#define RCC_AHB1ClockGating_APB2Bridge         ((uint32_t)0x00000002)
#define RCC_AHB1ClockGating_CM4DBG             ((uint32_t)0x00000004)
#define RCC_AHB1ClockGating_SPARE              ((uint32_t)0x00000008)
#define RCC_AHB1ClockGating_SRAM               ((uint32_t)0x00000010)
#define RCC_AHB1ClockGating_FLITF              ((uint32_t)0x00000020)
#define RCC_AHB1ClockGating_RCC                ((uint32_t)0x00000040)

#define IS_RCC_AHB1_CLOCKGATING(PERIPH) ((((PERIPH) & 0xFFFFFF80) == 0x00) && ((PERIPH) != 0x00))

#endif /* STM32F446xx */

#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
/** @defgroup RCC_FMPI2C1_Clock_Source
  */
#define RCC_FMPI2C1CLKSource_APB1            ((uint32_t)0x00)
#define RCC_FMPI2C1CLKSource_SYSCLK          ((uint32_t)RCC_DCKCFGR2_FMPI2C1SEL_0)
#define RCC_FMPI2C1CLKSource_HSI             ((uint32_t)RCC_DCKCFGR2_FMPI2C1SEL_1)

#define IS_RCC_FMPI2C1_CLOCKSOURCE(SOURCE) (((SOURCE) == RCC_FMPI2C1CLKSource_APB1) || ((SOURCE) == RCC_FMPI2C1CLKSource_SYSCLK) || \
        ((SOURCE) == RCC_FMPI2C1CLKSource_HSI))
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx */

#if defined(STM32F412xG) || defined(STM32F413_423xx)
/** @defgroup RCC_DFSDM_Clock_Source
 */
#define RCC_DFSDMCLKSource_APB             ((uint8_t)0x00)
#define RCC_DFSDMCLKSource_SYS             ((uint8_t)0x01)
#define IS_RCC_DFSDMCLK_SOURCE(SOURCE) (((SOURCE) == RCC_DFSDMCLKSource_APB) || ((SOURCE) == RCC_DFSDMCLKSource_SYS))

/* Legacy Defines */
#define RCC_DFSDM1CLKSource_APB   RCC_DFSDMCLKSource_APB
#define RCC_DFSDM1CLKSource_SYS   RCC_DFSDMCLKSource_SYS
#define IS_RCC_DFSDM1CLK_SOURCE   IS_RCC_DFSDMCLK_SOURCE

/** @defgroup RCC_DFSDM_Audio_Clock_Source  RCC DFSDM Audio Clock Source
  */
#define RCC_DFSDM1AUDIOCLKSOURCE_I2SAPB1          ((uint32_t)0x00000000)
#define RCC_DFSDM1AUDIOCLKSOURCE_I2SAPB2          ((uint32_t)RCC_DCKCFGR_CKDFSDM1ASEL)
#define IS_RCC_DFSDM1ACLK_SOURCE(SOURCE) (((SOURCE) == RCC_DFSDM1AUDIOCLKSOURCE_I2SAPB1) || ((SOURCE) == RCC_DFSDM1AUDIOCLKSOURCE_I2SAPB2))

/* Legacy Defines */
#define IS_RCC_DFSDMACLK_SOURCE      IS_RCC_DFSDM1ACLK_SOURCE

#if defined(STM32F413_423xx)
/** @defgroup RCC_DFSDM_Audio_Clock_Source  RCC DFSDM Audio Clock Source
  */
#define RCC_DFSDM2AUDIOCLKSOURCE_I2SAPB1          ((uint32_t)0x00000000)
#define RCC_DFSDM2AUDIOCLKSOURCE_I2SAPB2          ((uint32_t)RCC_DCKCFGR_CKDFSDM2ASEL)
#define IS_RCC_DFSDM2ACLK_SOURCE(SOURCE) (((SOURCE) == RCC_DFSDM2AUDIOCLKSOURCE_I2SAPB1) || ((SOURCE) == RCC_DFSDM2AUDIOCLKSOURCE_I2SAPB2))
#endif /* STM32F413_423xx */
#endif /* STM32F412xG || STM32F413_423xx */

/** @defgroup RCC_AHB1_Peripherals
  */
#define RCC_AHB1Periph_GPIOA             ((uint32_t)0x00000001)
#define RCC_AHB1Periph_GPIOB             ((uint32_t)0x00000002)
#define RCC_AHB1Periph_GPIOC             ((uint32_t)0x00000004)
#define RCC_AHB1Periph_GPIOD             ((uint32_t)0x00000008)
#define RCC_AHB1Periph_GPIOE             ((uint32_t)0x00000010)
#define RCC_AHB1Periph_GPIOF             ((uint32_t)0x00000020)
#define RCC_AHB1Periph_GPIOG             ((uint32_t)0x00000040)
#define RCC_AHB1Periph_GPIOH             ((uint32_t)0x00000080)
#define RCC_AHB1Periph_GPIOI             ((uint32_t)0x00000100)
#define RCC_AHB1Periph_GPIOJ             ((uint32_t)0x00000200)
#define RCC_AHB1Periph_GPIOK             ((uint32_t)0x00000400)
#define RCC_AHB1Periph_CRC               ((uint32_t)0x00001000)
#define RCC_AHB1Periph_FLITF             ((uint32_t)0x00008000)
#define RCC_AHB1Periph_SRAM1             ((uint32_t)0x00010000)
#define RCC_AHB1Periph_SRAM2             ((uint32_t)0x00020000)
#define RCC_AHB1Periph_BKPSRAM           ((uint32_t)0x00040000)
#define RCC_AHB1Periph_SRAM3             ((uint32_t)0x00080000)
#define RCC_AHB1Periph_CCMDATARAMEN      ((uint32_t)0x00100000)
#define RCC_AHB1Periph_DMA1              ((uint32_t)0x00200000)
#define RCC_AHB1Periph_DMA2              ((uint32_t)0x00400000)
#define RCC_AHB1Periph_DMA2D             ((uint32_t)0x00800000)
#define RCC_AHB1Periph_ETH_MAC           ((uint32_t)0x02000000)
#define RCC_AHB1Periph_ETH_MAC_Tx        ((uint32_t)0x04000000)
#define RCC_AHB1Periph_ETH_MAC_Rx        ((uint32_t)0x08000000)
#define RCC_AHB1Periph_ETH_MAC_PTP       ((uint32_t)0x10000000)
#define RCC_AHB1Periph_OTG_HS            ((uint32_t)0x20000000)
#define RCC_AHB1Periph_OTG_HS_ULPI       ((uint32_t)0x40000000)
#if defined(STM32F410xx)
#define RCC_AHB1Periph_RNG               ((uint32_t)0x80000000)
#endif /* STM32F410xx */
#define IS_RCC_AHB1_CLOCK_PERIPH(PERIPH) ((((PERIPH) & 0x010BE800) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB1_RESET_PERIPH(PERIPH) ((((PERIPH) & 0x51FE800) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_AHB1_LPMODE_PERIPH(PERIPH) ((((PERIPH) & 0x01106800) == 0x00) && ((PERIPH) != 0x00))


/** @defgroup RCC_AHB2_Peripherals
  */
#define RCC_AHB2Periph_DCMI              ((uint32_t)0x00000001)
#define RCC_AHB2Periph_CRYP              ((uint32_t)0x00000010)
#define RCC_AHB2Periph_HASH              ((uint32_t)0x00000020)
#if defined(STM32F40_41xxx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx)
#define RCC_AHB2Periph_RNG               ((uint32_t)0x00000040)
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F469_479xx */
#define RCC_AHB2Periph_OTG_FS            ((uint32_t)0x00000080)
#define IS_RCC_AHB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFF0E) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup RCC_AHB3_Peripherals
  */
#if defined(STM32F40_41xxx)
#define RCC_AHB3Periph_FSMC                ((uint32_t)0x00000001)
#define IS_RCC_AHB3_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFFE) == 0x00) && ((PERIPH) != 0x00))
#endif /* STM32F40_41xxx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx)
#define RCC_AHB3Periph_FMC                 ((uint32_t)0x00000001)
#define IS_RCC_AHB3_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFFE) == 0x00) && ((PERIPH) != 0x00))
#endif /* STM32F427_437xx ||  STM32F429_439xx */

#if defined(STM32F446xx) || defined(STM32F469_479xx)
#define RCC_AHB3Periph_FMC                 ((uint32_t)0x00000001)
#define RCC_AHB3Periph_QSPI                ((uint32_t)0x00000002)
#define IS_RCC_AHB3_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFFC) == 0x00) && ((PERIPH) != 0x00))
#endif /* STM32F446xx ||  STM32F469_479xx */

#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define RCC_AHB3Periph_FSMC                 ((uint32_t)0x00000001)
#define RCC_AHB3Periph_QSPI                 ((uint32_t)0x00000002)
#define IS_RCC_AHB3_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFFFC) == 0x00) && ((PERIPH) != 0x00))
#endif /* STM32F412xG || STM32F413_423xx */


/** @defgroup RCC_APB1_Peripherals
  */
#define RCC_APB1Periph_TIM2              ((uint32_t)0x00000001)
#define RCC_APB1Periph_TIM3              ((uint32_t)0x00000002)
#define RCC_APB1Periph_TIM4              ((uint32_t)0x00000004)
#define RCC_APB1Periph_TIM5              ((uint32_t)0x00000008)
#define RCC_APB1Periph_TIM6              ((uint32_t)0x00000010)
#define RCC_APB1Periph_TIM7              ((uint32_t)0x00000020)
#define RCC_APB1Periph_TIM12             ((uint32_t)0x00000040)
#define RCC_APB1Periph_TIM13             ((uint32_t)0x00000080)
#define RCC_APB1Periph_TIM14             ((uint32_t)0x00000100)
#if defined(STM32F410xx) || defined(STM32F413_423xx)
#define RCC_APB1Periph_LPTIM1            ((uint32_t)0x00000200)
#endif /* STM32F410xx || STM32F413_423xx */
#define RCC_APB1Periph_WWDG              ((uint32_t)0x00000800)
#define RCC_APB1Periph_SPI2              ((uint32_t)0x00004000)
#define RCC_APB1Periph_SPI3              ((uint32_t)0x00008000)
#if defined(STM32F446xx)
#define RCC_APB1Periph_SPDIFRX           ((uint32_t)0x00010000)
#endif /* STM32F446xx */
#define RCC_APB1Periph_USART2            ((uint32_t)0x00020000)
#define RCC_APB1Periph_USART3            ((uint32_t)0x00040000)
#define RCC_APB1Periph_UART4             ((uint32_t)0x00080000)
#define RCC_APB1Periph_UART5             ((uint32_t)0x00100000)
#define RCC_APB1Periph_I2C1              ((uint32_t)0x00200000)
#define RCC_APB1Periph_I2C2              ((uint32_t)0x00400000)
#define RCC_APB1Periph_I2C3              ((uint32_t)0x00800000)
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
#define RCC_APB1Periph_FMPI2C1           ((uint32_t)0x01000000)
#endif /* STM32F410xx || STM32F446xx || STM32F413_423xx*/
#define RCC_APB1Periph_CAN1              ((uint32_t)0x02000000)
#define RCC_APB1Periph_CAN2              ((uint32_t)0x04000000)
#if defined(STM32F413_423xx)
#define RCC_APB1Periph_CAN3              ((uint32_t)0x08000000)
#endif /* STM32F413_423xx */
#if defined(STM32F446xx)
#define RCC_APB1Periph_CEC               ((uint32_t)0x08000000)
#endif /* STM32F446xx */
#define RCC_APB1Periph_PWR               ((uint32_t)0x10000000)
#define RCC_APB1Periph_DAC               ((uint32_t)0x20000000)
#define RCC_APB1Periph_UART7             ((uint32_t)0x40000000)
#define RCC_APB1Periph_UART8             ((uint32_t)0x80000000)
#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0x00003600) == 0x00) && ((PERIPH) != 0x00))

/** @defgroup RCC_APB2_Peripherals
  */
#define RCC_APB2Periph_TIM1              ((uint32_t)0x00000001)
#define RCC_APB2Periph_TIM8              ((uint32_t)0x00000002)
#define RCC_APB2Periph_USART1            ((uint32_t)0x00000010)
#define RCC_APB2Periph_USART6            ((uint32_t)0x00000020)
#define RCC_APB2Periph_ADC               ((uint32_t)0x00000100)
#define RCC_APB2Periph_ADC1              ((uint32_t)0x00000100)
#define RCC_APB2Periph_ADC2              ((uint32_t)0x00000200)
#define RCC_APB2Periph_ADC3              ((uint32_t)0x00000400)
#define RCC_APB2Periph_SDIO              ((uint32_t)0x00000800)
#define RCC_APB2Periph_SPI1              ((uint32_t)0x00001000)
#define RCC_APB2Periph_SPI4              ((uint32_t)0x00002000)
#define RCC_APB2Periph_SYSCFG            ((uint32_t)0x00004000)
#define RCC_APB2Periph_EXTIT             ((uint32_t)0x00008000)
#define RCC_APB2Periph_TIM9              ((uint32_t)0x00010000)
#define RCC_APB2Periph_TIM10             ((uint32_t)0x00020000)
#define RCC_APB2Periph_TIM11             ((uint32_t)0x00040000)
#define RCC_APB2Periph_SPI5              ((uint32_t)0x00100000)
#define RCC_APB2Periph_SPI6              ((uint32_t)0x00200000)
#define RCC_APB2Periph_SAI1              ((uint32_t)0x00400000)
#if defined(STM32F446xx) || defined(STM32F469_479xx)
#define RCC_APB2Periph_SAI2              ((uint32_t)0x00800000)
#endif /* STM32F446xx || STM32F469_479xx */
#define RCC_APB2Periph_LTDC              ((uint32_t)0x04000000)
#if defined(STM32F469_479xx)
#define RCC_APB2Periph_DSI               ((uint32_t)0x08000000)
#endif /* STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx)
#define RCC_APB2Periph_DFSDM1            ((uint32_t)0x01000000)
#endif /* STM32F412xG || STM32F413_423xx */
#if defined(STM32F413_423xx)
#define RCC_APB2Periph_DFSDM2            ((uint32_t)0x02000000)
#define RCC_APB2Periph_UART9             ((uint32_t)0x02000040)
#define RCC_APB2Periph_UART10            ((uint32_t)0x00000080)
#endif /* STM32F413_423xx */

/* Legacy Defines */
#define RCC_APB2Periph_DFSDM              RCC_APB2Periph_DFSDM1

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xF008000C) == 0x00) && ((PERIPH) != 0x00))
#define IS_RCC_APB2_RESET_PERIPH(PERIPH) ((((PERIPH) & 0xF208860C) == 0x00) && ((PERIPH) != 0x00))


/** @defgroup RCC_MCO1_Clock_Source_Prescaler
  */
#define RCC_MCO1Source_HSI               ((uint32_t)0x00000000)
#define RCC_MCO1Source_LSE               ((uint32_t)0x00200000)
#define RCC_MCO1Source_HSE               ((uint32_t)0x00400000)
#define RCC_MCO1Source_PLLCLK            ((uint32_t)0x00600000)
#define RCC_MCO1Div_1                    ((uint32_t)0x00000000)
#define RCC_MCO1Div_2                    ((uint32_t)0x04000000)
#define RCC_MCO1Div_3                    ((uint32_t)0x05000000)
#define RCC_MCO1Div_4                    ((uint32_t)0x06000000)
#define RCC_MCO1Div_5                    ((uint32_t)0x07000000)
#define IS_RCC_MCO1SOURCE(SOURCE) (((SOURCE) == RCC_MCO1Source_HSI) || ((SOURCE) == RCC_MCO1Source_LSE) || \
                                   ((SOURCE) == RCC_MCO1Source_HSE) || ((SOURCE) == RCC_MCO1Source_PLLCLK))

#define IS_RCC_MCO1DIV(DIV) (((DIV) == RCC_MCO1Div_1) || ((DIV) == RCC_MCO1Div_2) || \
                             ((DIV) == RCC_MCO1Div_3) || ((DIV) == RCC_MCO1Div_4) || \
                             ((DIV) == RCC_MCO1Div_5))

/** @defgroup RCC_MCO2_Clock_Source_Prescaler
  */
#define RCC_MCO2Source_SYSCLK            ((uint32_t)0x00000000)
#define RCC_MCO2Source_PLLI2SCLK         ((uint32_t)0x40000000)
#define RCC_MCO2Source_HSE               ((uint32_t)0x80000000)
#define RCC_MCO2Source_PLLCLK            ((uint32_t)0xC0000000)
#define RCC_MCO2Div_1                    ((uint32_t)0x00000000)
#define RCC_MCO2Div_2                    ((uint32_t)0x20000000)
#define RCC_MCO2Div_3                    ((uint32_t)0x28000000)
#define RCC_MCO2Div_4                    ((uint32_t)0x30000000)
#define RCC_MCO2Div_5                    ((uint32_t)0x38000000)
#define IS_RCC_MCO2SOURCE(SOURCE) (((SOURCE) == RCC_MCO2Source_SYSCLK) || ((SOURCE) == RCC_MCO2Source_PLLI2SCLK)|| \
                                   ((SOURCE) == RCC_MCO2Source_HSE) || ((SOURCE) == RCC_MCO2Source_PLLCLK))

#define IS_RCC_MCO2DIV(DIV) (((DIV) == RCC_MCO2Div_1) || ((DIV) == RCC_MCO2Div_2) || \
                             ((DIV) == RCC_MCO2Div_3) || ((DIV) == RCC_MCO2Div_4) || \
                             ((DIV) == RCC_MCO2Div_5))

/** @defgroup RCC_Flag
  */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x21)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x39)
#define RCC_FLAG_PLLI2SRDY               ((uint8_t)0x3B)
#define RCC_FLAG_PLLSAIRDY               ((uint8_t)0x3D)
#define RCC_FLAG_LSERDY                  ((uint8_t)0x41)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x61)
#define RCC_FLAG_BORRST                  ((uint8_t)0x79)
#define RCC_FLAG_PINRST                  ((uint8_t)0x7A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x7F)

#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY)   || ((FLAG) == RCC_FLAG_HSERDY) || \
                           ((FLAG) == RCC_FLAG_PLLRDY)   || ((FLAG) == RCC_FLAG_LSERDY) || \
                           ((FLAG) == RCC_FLAG_LSIRDY)   || ((FLAG) == RCC_FLAG_BORRST) || \
                           ((FLAG) == RCC_FLAG_PINRST)   || ((FLAG) == RCC_FLAG_PORRST) || \
                           ((FLAG) == RCC_FLAG_SFTRST)   || ((FLAG) == RCC_FLAG_IWDGRST)|| \
                           ((FLAG) == RCC_FLAG_WWDGRST)  || ((FLAG) == RCC_FLAG_LPWRRST)|| \
                           ((FLAG) == RCC_FLAG_PLLI2SRDY)|| ((FLAG) == RCC_FLAG_PLLSAIRDY))

#define IS_RCC_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* 用于将 RCC 时钟配置设置为默认复位状态的函数 */
void        RCC_DeInit(void); // 将 RCC 时钟配置重置为默认重置状态。

/* 内部/外部时钟、PLL、CSS 和 MCO 配置功能 *********/
void        RCC_HSEConfig(uint8_t RCC_HSE); // 配置外部高速振荡器 (HSE)。
ErrorStatus RCC_WaitForHSEStartUp(void); // 等待 HSE 启动。
void        RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue); // 调整内部高速振荡器 (HSI) 校准值。
void        RCC_HSICmd(FunctionalState NewState); // 启用或禁用内部高速振荡器 (HSI)。
void        RCC_LSEConfig(uint8_t RCC_LSE); // 配置外部低速振荡器 (LSE)。
void        RCC_LSICmd(FunctionalState NewState); // 启用或禁用内部低速振荡器 (LSI)。

void        RCC_PLLCmd(FunctionalState NewState); // 启用或禁用主 PLL。

#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
void        RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ, uint32_t PLLR); // 配置主PLL时钟源、乘法和除法系数。
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE)
void        RCC_PLLConfig(uint32_t RCC_PLLSource, uint32_t PLLM, uint32_t PLLN, uint32_t PLLP, uint32_t PLLQ); // 配置主PLL时钟源、乘法和除法系数。
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE */

void        RCC_PLLI2SCmd(FunctionalState NewState); // 启用或禁用 PLLI2S。

#if defined(STM32F40_41xxx) || defined(STM32F401xx)
void        RCC_PLLI2SConfig(uint32_t PLLI2SN, uint32_t PLLI2SR); // 配置PLLI2S 时钟乘除因子。
#endif /* STM32F40_41xxx || STM32F401xx */
#if defined(STM32F411xE)
void        RCC_PLLI2SConfig(uint32_t PLLI2SN, uint32_t PLLI2SR, uint32_t PLLI2SM); // 配置PLLI2S 时钟乘除因子。
#endif /* STM32F411xE */
#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx)
void        RCC_PLLI2SConfig(uint32_t PLLI2SN, uint32_t PLLI2SQ, uint32_t PLLI2SR); // 配置PLLI2S 时钟乘除因子。
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F469_479xx */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
void        RCC_PLLI2SConfig(uint32_t PLLI2SM, uint32_t PLLI2SN, uint32_t PLLI2SP, uint32_t PLLI2SQ, uint32_t PLLI2SR); // 配置PLLI2S 时钟乘除因子。
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */

void        RCC_PLLSAICmd(FunctionalState NewState); // 启用或禁用 PLLSAI。
#if defined(STM32F469_479xx)
void        RCC_PLLSAIConfig(uint32_t PLLSAIN, uint32_t PLLSAIP, uint32_t PLLSAIQ, uint32_t PLLSAIR);
#endif /* STM32F469_479xx */
#if defined(STM32F446xx)
void        RCC_PLLSAIConfig(uint32_t PLLSAIM, uint32_t PLLSAIN, uint32_t PLLSAIP, uint32_t PLLSAIQ);
#endif /* STM32F446xx */
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE)
void        RCC_PLLSAIConfig(uint32_t PLLSAIN, uint32_t PLLSAIQ, uint32_t PLLSAIR);
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE */

void        RCC_ClockSecuritySystemCmd(FunctionalState NewState); // 启用或禁用时钟安全系统。
void        RCC_MCO1Config(uint32_t RCC_MCO1Source, uint32_t RCC_MCO1Div); // 选择要在 MCO1 引脚 (PA8) 上输出的时钟源。
void        RCC_MCO2Config(uint32_t RCC_MCO2Source, uint32_t RCC_MCO2Div); // 选择要在 MCO2 引脚(PC9) 上输出的时钟源。

/* 系统、AHB 和 APB 总线时钟配置功能 ******************/
void        RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource); // 配置系统时钟 (SYSCLK)。
uint8_t     RCC_GetSYSCLKSource(void); // 返回用作系统时钟的时钟源。
void        RCC_HCLKConfig(uint32_t RCC_SYSCLK); // 配置 AHB 时钟 (HCLK)。
void        RCC_PCLK1Config(uint32_t RCC_HCLK); // 配置低速 APB 时钟 (PCLK1)。
void        RCC_PCLK2Config(uint32_t RCC_HCLK); // 配置高速 APB 时钟 (PCLK2)。
void        RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks); // 返回不同片上时钟的频率;SYSCLK，HCLK，PCLK1和 PCLK2。

/* 外设时钟配置功能 **********************************/
void        RCC_RTCCLKConfig(uint32_t RCC_RTCCLKSource); // 配置 RTC 时钟 (RTCCLK)。
void        RCC_RTCCLKCmd(FunctionalState NewState); // 启用或禁用 RTC 时钟。
void        RCC_BackupResetCmd(FunctionalState NewState); // 强制或释放备份域重置。

#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
void        RCC_I2SCLKConfig(uint32_t RCC_I2SAPBx, uint32_t RCC_I2SCLKSource);
#if defined(STM32F446xx)
void        RCC_SAICLKConfig(uint32_t RCC_SAIInstance, uint32_t RCC_SAICLKSource);
#endif /* STM32F446xx */
#if defined(STM32F413_423xx)
void RCC_SAIBlockACLKConfig(uint32_t RCC_SAIBlockACLKSource);
void RCC_SAIBlockBCLKConfig(uint32_t RCC_SAIBlockBCLKSource);
#endif /* STM32F413_423xx */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F469_479xx)
void        RCC_I2SCLKConfig(uint32_t RCC_I2SCLKSource);
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F469_479xx */

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx)
void        RCC_SAIBlockACLKConfig(uint32_t RCC_SAIBlockACLKSource);
void        RCC_SAIBlockBCLKConfig(uint32_t RCC_SAIBlockBCLKSource);
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F469_479xx */

void        RCC_SAIPLLI2SClkDivConfig(uint32_t RCC_PLLI2SDivQ); // 配置来自 PLLI2S 的 SAI 时钟分频器。
void        RCC_SAIPLLSAIClkDivConfig(uint32_t RCC_PLLSAIDivQ); // 配置来自 PLLSAI 的 SAI 时钟分频器。

#if defined(STM32F413_423xx)
void        RCC_SAIPLLI2SRClkDivConfig(uint32_t RCC_PLLI2SDivR);
void        RCC_SAIPLLRClkDivConfig(uint32_t RCC_PLLDivR);
#endif /* STM32F413_423xx */

void        RCC_LTDCCLKDivConfig(uint32_t RCC_PLLSAIDivR); // 配置来自 PLLSAI 的 LTDC 时钟分频器。
void        RCC_TIMCLKPresConfig(uint32_t RCC_TIMCLKPrescaler); // 配置"计时器时钟"预分频器选择。

void        RCC_AHB1PeriphClockCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState); // 启用或禁用 AHB1 外设时钟。
void        RCC_AHB2PeriphClockCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState); // 启用或禁用 AHB2 外设时钟。
void        RCC_AHB3PeriphClockCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState); // 启用或禁用 AHB3 外设时钟。
void        RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState); // 启用或禁用 APB1 外设时钟。
void        RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState); // 启用或禁用 APB2 外设时钟。

void        RCC_AHB1PeriphResetCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState); // 强制或释放AHB1外设复位。
void        RCC_AHB2PeriphResetCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState); // 强制或释放AHB2外设复位。
void        RCC_AHB3PeriphResetCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState); // 强制或释放AHB3 外设复位。
void        RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState); // 强制或释放APB1外设复位。
void        RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState); // 强制或释放APB2外设复位。

void        RCC_AHB1PeriphClockLPModeCmd(uint32_t RCC_AHB1Periph, FunctionalState NewState); // 在低功耗(睡眠)模式下启用或禁用 AHB1外设时钟。
void        RCC_AHB2PeriphClockLPModeCmd(uint32_t RCC_AHB2Periph, FunctionalState NewState); // 在低功耗(睡眠)模式下启用或禁用 AHB2外设时钟。
void        RCC_AHB3PeriphClockLPModeCmd(uint32_t RCC_AHB3Periph, FunctionalState NewState); // 在低功耗(睡眠)模式下启用或禁用 AHB3 外设时钟。
void        RCC_APB1PeriphClockLPModeCmd(uint32_t RCC_APB1Periph, FunctionalState NewState); // 在低功耗(睡眠)模式下启用或禁用 APB1外设时钟。
void        RCC_APB2PeriphClockLPModeCmd(uint32_t RCC_APB2Periph, FunctionalState NewState); // 在低功耗(睡眠)模式下启用或禁用 APB2外设时钟。

/* 仅适用于 STM32F410xx/STM32F411xx/STM32F446xx/STM32F469_479xx 器件的功能 */
void        RCC_LSEModeConfig(uint8_t RCC_Mode); // 配置外部低速振荡器模式(LSE 模式)。

/* 仅适用于 STM32F469_479xx 器件的功能 */
#if defined(STM32F469_479xx)
void        RCC_DSIClockSourceConfig(uint8_t RCC_ClockSource);
#endif /*  STM32F469_479xx */

/* 仅适用于 STM32F412xG/STM32F413_423xx/STM32F446xx/STM32F469_479xx 器件的功能 */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
void        RCC_48MHzClockSourceConfig(uint8_t RCC_ClockSource); // 配置48MHz时钟源。
void        RCC_SDIOClockSourceConfig(uint8_t RCC_ClockSource); // 配置 SDIO 时钟源。
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */

/* 仅适用于 STM32F446xx 器件的功能 */
#if defined(STM32F446xx)
void        RCC_AHB1ClockGatingCmd(uint32_t RCC_AHB1ClockGating, FunctionalState NewState); // 启用或禁用指定 IP的 AHB1时钟门控。
void        RCC_SPDIFRXClockSourceConfig(uint8_t RCC_ClockSource);
void        RCC_CECClockSourceConfig(uint8_t RCC_ClockSource);
#endif /* STM32F446xx */

/* 仅适用于 STM32F410xx/STM32F412xG/STM32F446xx 器件的功能 */
#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
void        RCC_FMPI2C1ClockSourceConfig(uint32_t RCC_ClockSource);
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx */

/* Features available only for STM32F410xx devices */
#if defined(STM32F410xx) || defined(STM32F413_423xx)
void        RCC_LPTIM1ClockSourceConfig(uint32_t RCC_ClockSource); // 配置 LPTIM1时钟源。
#if defined(STM32F410xx)
void        RCC_MCO1Cmd(FunctionalState NewState);
void        RCC_MCO2Cmd(FunctionalState NewState);
#endif /* STM32F410xx */
#endif /* STM32F410xx || STM32F413_423xx */

#if defined(STM32F412xG) || defined(STM32F413_423xx)
void RCC_DFSDMCLKConfig(uint32_t RCC_DFSDMCLKSource);
void RCC_DFSDM1ACLKConfig(uint32_t RCC_DFSDM1ACLKSource);
#if defined(STM32F413_423xx)
void RCC_DFSDM2ACLKConfig(uint32_t RCC_DFSDMACLKSource);
#endif /* STM32F413_423xx */
/* 传统定义 */
#define RCC_DFSDM1CLKConfig      RCC_DFSDMCLKConfig
#endif /* STM32F412xG || STM32F413_423xx */
/* 中断和标志管理功能 **********************************/
void        RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState); // 启用或禁用指定的 RCC 中断。
FlagStatus  RCC_GetFlagStatus(uint8_t RCC_FLAG); // 检查是否设置了指定的 RCC 标志。
void        RCC_ClearFlag(void); // 清除 RCC 重置标志。
ITStatus    RCC_GetITStatus(uint8_t RCC_IT); // 检查是否发生了指定的 RCC 中断。
void        RCC_ClearITPendingBit(uint8_t RCC_IT); // 清除 RCC 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_RCC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
