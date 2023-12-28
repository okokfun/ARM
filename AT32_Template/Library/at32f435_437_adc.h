/**
  **************************************************************************
  * @file     at32f435_437_adc.h
  * @brief    at32f435_437 adc header file
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
#ifndef __AT32F435_437_ADC_H
#define __AT32F435_437_ADC_H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "at32f435_437.h"


/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_Interrupts_definition
  * @brief adc interrupt
  * @{
  */
#define ADC_Occe_INT                     ((uint32_t)0x00000020) /*!< ordinary channels conversion end 中断 */
#define ADC_VMOR_INT                     ((uint32_t)0x00000040) /*!< voltage monitoring out of range 中断 */
#define ADC_PCCE_INT                     ((uint32_t)0x00000080) /*!< preempt channels conversion end 中断 */
#define ADC_OCCO_INT                     ((uint32_t)0x04000000) /*!< ordinary channel conversion overflow 中断 */

/**
  * @}
  */

/** @defgroup ADC_flags_definition
  * @brief adc flag
  * @{
  */
#define ADC_VMOR_FLAG                    ((uint8_t)0x01) /*!< voltage monitoring out of range flag */
#define ADC_Occe_FLAG                    ((uint8_t)0x02) /*!< ordinary channels conversion end flag */
#define ADC_PCCE_FLAG                    ((uint8_t)0x04) /*!< preempt channels conversion end flag */
#define ADC_PCCS_FLAG                    ((uint8_t)0x08) /*!< preempt channel conversion start flag */
#define ADC_OCCS_FLAG                    ((uint8_t)0x10) /*!< ordinary channel conversion start flag */
#define ADC_OCCO_FLAG                    ((uint8_t)0x20) /*!< ordinary channel conversion overflow flag */
#define ADC_RDY_FLAG                     ((uint8_t)0x40) /*!< adc ready to conversion flag */

/**
  * @}
  */

/** @defgroup ADC_exported_Types
  * @{
  */

/**
  * @brief adc division type
  */
typedef enum {
    ADC_HCLK_Div_2                         = 0x00, /*!< adcclk is hclk/2 */
    ADC_HCLK_Div_3                         = 0x01, /*!< adcclk is hclk/3 */
    ADC_HCLK_Div_4                         = 0x02, /*!< adcclk is hclk/4 */
    ADC_HCLK_Div_5                         = 0x03, /*!< adcclk is hclk/5 */
    ADC_HCLK_Div_6                         = 0x04, /*!< adcclk is hclk/6 */
    ADC_HCLK_Div_7                         = 0x05, /*!< adcclk is hclk/7 */
    ADC_HCLK_Div_8                         = 0x06, /*!< adcclk is hclk/8 */
    ADC_HCLK_Div_9                         = 0x07, /*!< adcclk is hclk/9 */
    ADC_HCLK_Div_10                        = 0x08, /*!< adcclk is hclk/10 */
    ADC_HCLK_Div_11                        = 0x09, /*!< adcclk is hclk/11 */
    ADC_HCLK_Div_12                        = 0x0A, /*!< adcclk is hclk/12 */
    ADC_HCLK_Div_13                        = 0x0B, /*!< adcclk is hclk/13 */
    ADC_HCLK_Div_14                        = 0x0C, /*!< adcclk is hclk/14 */
    ADC_HCLK_Div_15                        = 0x0D, /*!< adcclk is hclk/15 */
    ADC_HCLK_Div_16                        = 0x0E, /*!< adcclk is hclk/16 */
    ADC_HCLK_Div_17                        = 0x0F  /*!< adcclk is hclk/17 */
} ADC_Div_Type;

/**
  * @brief adc combine mode type
  */
typedef enum {
    ADC_INDEPENDENT_Mode                               = 0x00, /*!< independent mode */
    ADC_Ordinary_SMLT_Preempt_SMLT_ONESLAVE_Mode       = 0x01, /*!< single slaver combined ordinary simultaneous + preempt simultaneous mode */
    ADC_Ordinary_SMLT_Preempt_INTERLTRIG_ONESLAVE_Mode = 0x02, /*!< single slaver combined ordinary simultaneous + preempt interleaved trigger mode */
    ADC_Preempt_SMLT_ONLY_ONESLAVE_Mode                = 0x05, /*!< single slaver preempt simultaneous mode only */
    ADC_Ordinary_SMLT_ONLY_ONESLAVE_Mode               = 0x06, /*!< single slaver ordinary simultaneous mode only */
    ADC_Ordinary_Shift_ONLY_ONESLAVE_Mode              = 0x07, /*!< single slaver ordinary shifting mode only */
    ADC_Preempt_INTERLTRIG_ONLY_ONESLAVE_Mode          = 0x09, /*!< single slaver preempt interleaved trigger mode only */
    ADC_Ordinary_SMLT_Preempt_SMLT_TWOSLAVE_Mode       = 0x11, /*!< double slaver combined ordinary simultaneous + preempt simultaneous mode */
    ADC_Ordinary_SMLT_Preempt_INTERLTRIG_TWOSLAVE_Mode = 0x12, /*!< double slaver combined ordinary simultaneous + preempt interleaved trigger mode */
    ADC_Preempt_SMLT_ONLY_TWOSLAVE_Mode                = 0x15, /*!< double slaver preempt simultaneous mode only */
    ADC_Ordinary_SMLT_ONLY_TWOSLAVE_Mode               = 0x16, /*!< double slaver ordinary simultaneous mode only */
    ADC_Ordinary_Shift_ONLY_TWOSLAVE_Mode              = 0x17, /*!< double slaver ordinary shifting mode only */
    ADC_Preempt_INTERLTRIG_ONLY_TWOSLAVE_Mode          = 0x19  /*!< double slaver preempt interleaved trigger mode only */
} ADC_Combine_Mode_Type;

/**
  * @brief adc common dma mode type
  */
typedef enum {
    ADC_Common_DMAMODE_Disable             = 0x00, /*!< dma mode disabled */
    ADC_Common_DMAMODE_1                   = 0x01, /*!< dma mode1: each dma request trans a half-word data(reference manual account the rule of data package) */
    ADC_Common_DMAMODE_2                   = 0x02, /*!< dma mode2: each dma request trans two half-word data(reference manual account the rule of data package) */
    ADC_Common_DMAMODE_3                   = 0x03, /*!< dma mode3: each dma request trans two bytes data(reference manual account the rule of data package) */
    ADC_Common_DMAMODE_4                   = 0x04, /*!< dma mode4: each dma request trans three bytes data(reference manual account the rule of data package) */
    ADC_Common_DMAMODE_5                   = 0x05  /*!< dma mode5: odd dma request trans two half-word data,even dma request trans a half-word data(reference manual account the rule of data package) */
} ADC_Common_DMA_Mode_Type;

/**
  * @brief adc common sampling interval type
  */
typedef enum {
    ADC_SAMPLING_INTERVAL_5CYCLES          = 0x00, /*!< ordinary shifting mode adjacent adc sampling interval 5 adcclk */
    ADC_SAMPLING_INTERVAL_6CYCLES          = 0x01, /*!< ordinary shifting mode adjacent adc sampling interval 6 adcclk */
    ADC_SAMPLING_INTERVAL_7CYCLES          = 0x02, /*!< ordinary shifting mode adjacent adc sampling interval 7 adcclk */
    ADC_SAMPLING_INTERVAL_8CYCLES          = 0x03, /*!< ordinary shifting mode adjacent adc sampling interval 8 adcclk */
    ADC_SAMPLING_INTERVAL_9CYCLES          = 0x04, /*!< ordinary shifting mode adjacent adc sampling interval 9 adcclk */
    ADC_SAMPLING_INTERVAL_10CYCLES         = 0x05, /*!< ordinary shifting mode adjacent adc sampling interval 10 adcclk */
    ADC_SAMPLING_INTERVAL_11CYCLES         = 0x06, /*!< ordinary shifting mode adjacent adc sampling interval 11 adcclk */
    ADC_SAMPLING_INTERVAL_12CYCLES         = 0x07, /*!< ordinary shifting mode adjacent adc sampling interval 12 adcclk */
    ADC_SAMPLING_INTERVAL_13CYCLES         = 0x08, /*!< ordinary shifting mode adjacent adc sampling interval 13 adcclk */
    ADC_SAMPLING_INTERVAL_14CYCLES         = 0x09, /*!< ordinary shifting mode adjacent adc sampling interval 14 adcclk */
    ADC_SAMPLING_INTERVAL_15CYCLES         = 0x0A, /*!< ordinary shifting mode adjacent adc sampling interval 15 adcclk */
    ADC_SAMPLING_INTERVAL_16CYCLES         = 0x0B, /*!< ordinary shifting mode adjacent adc sampling interval 16 adcclk */
    ADC_SAMPLING_INTERVAL_17CYCLES         = 0x0C, /*!< ordinary shifting mode adjacent adc sampling interval 17 adcclk */
    ADC_SAMPLING_INTERVAL_18CYCLES         = 0x0D, /*!< ordinary shifting mode adjacent adc sampling interval 18 adcclk */
    ADC_SAMPLING_INTERVAL_19CYCLES         = 0x0E, /*!< ordinary shifting mode adjacent adc sampling interval 19 adcclk */
    ADC_SAMPLING_INTERVAL_20CYCLES         = 0x0F  /*!< ordinary shifting mode adjacent adc sampling interval 20 adcclk */
} ADC_sampling_interval_Type;

/**
  * @brief adc conversion resolution type
  */
typedef enum {
    ADC_Resolution_12B                     = 0x00, /*!< conversion resolution 12 bit */
    ADC_Resolution_10B                     = 0x01, /*!< conversion resolution 10 bit */
    ADC_Resolution_8B                      = 0x02, /*!< conversion resolution 8 bit */
    ADC_Resolution_6B                      = 0x03  /*!< conversion resolution 6 bit */
} ADC_Resolution_Type;

/**
  * @brief adc data align type
  */
typedef enum {
    ADC_RIGHT_ALIGNMENT                    = 0x00, /*!< data right alignment */
    ADC_LEFT_ALIGNMENT                     = 0x01  /*!< data left alignment */
} ADC_Data_align_Type;

/**
  * @brief adc channel select type
  */
typedef enum {
    ADC_Channel_0                          = 0x00, /*!< adc channel 0 */
    ADC_Channel_1                          = 0x01, /*!< adc channel 1 */
    ADC_Channel_2                          = 0x02, /*!< adc channel 2 */
    ADC_Channel_3                          = 0x03, /*!< adc channel 3 */
    ADC_Channel_4                          = 0x04, /*!< adc channel 4 */
    ADC_Channel_5                          = 0x05, /*!< adc channel 5 */
    ADC_Channel_6                          = 0x06, /*!< adc channel 6 */
    ADC_Channel_7                          = 0x07, /*!< adc channel 7 */
    ADC_Channel_8                          = 0x08, /*!< adc channel 8 */
    ADC_Channel_9                          = 0x09, /*!< adc channel 9 */
    ADC_Channel_10                         = 0x0A, /*!< adc channel 10 */
    ADC_Channel_11                         = 0x0B, /*!< adc channel 11 */
    ADC_Channel_12                         = 0x0C, /*!< adc channel 12 */
    ADC_Channel_13                         = 0x0D, /*!< adc channel 13 */
    ADC_Channel_14                         = 0x0E, /*!< adc channel 14 */
    ADC_Channel_15                         = 0x0F, /*!< adc channel 15 */
    ADC_Channel_16                         = 0x10, /*!< adc channel 16 */
    ADC_Channel_17                         = 0x11, /*!< adc channel 17 */
    ADC_Channel_18                         = 0x12  /*!< adc channel 18 */
} ADC_Channel_Select_Type;

/**
  * @brief adc sampletime select type
  */
typedef enum {
    ADC_SAMPLETIME_2_5                     = 0x00, /*!< adc sample time 2.5 cycle */
    ADC_SAMPLETIME_6_5                     = 0x01, /*!< adc sample time 6.5 cycle */
    ADC_SAMPLETIME_12_5                    = 0x02, /*!< adc sample time 12.5 cycle */
    ADC_SAMPLETIME_24_5                    = 0x03, /*!< adc sample time 24.5 cycle */
    ADC_SAMPLETIME_47_5                    = 0x04, /*!< adc sample time 47.5 cycle */
    ADC_SAMPLETIME_92_5                    = 0x05, /*!< adc sample time 92.5 cycle */
    ADC_SAMPLETIME_247_5                   = 0x06, /*!< adc sample time 247.5 cycle */
    ADC_SAMPLETIME_640_5                   = 0x07  /*!< adc sample time 640.5 cycle */
} ADC_sampletime_Select_Type;

/**
  * @brief adc ordinary group trigger event select type
  */
typedef enum {
    ADC_Ordinary_Trig_TMR1CH1              = 0x00, /*!< timer1 ch1 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR1CH2              = 0x01, /*!< timer1 ch2 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR1CH3              = 0x02, /*!< timer1 ch3 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR2CH2              = 0x03, /*!< timer2 ch2 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR2CH3              = 0x04, /*!< timer2 ch3 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR2CH4              = 0x05, /*!< timer2 ch4 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR2TRGOUT           = 0x06, /*!< timer2 trgout event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR3CH1              = 0x07, /*!< timer3 ch1 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR3TRGOUT           = 0x08, /*!< timer3 trgout event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR4CH4              = 0x09, /*!< timer4 ch4 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR5CH1              = 0x0A, /*!< timer5 ch1 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR5CH2              = 0x0B, /*!< timer5 ch2 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR5CH3              = 0x0C, /*!< timer5 ch3 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR8CH1              = 0x0D, /*!< timer8 ch1 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR8TRGOUT           = 0x0E, /*!< timer8 trgout event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_EXINT11              = 0x0F, /*!< exint line11 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR20TRGOUT          = 0x10, /*!< timer20 trgout event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR20TRGOUT2         = 0x11, /*!< timer20 trgout2 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR20CH1             = 0x12, /*!< timer20 ch1 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR20CH2             = 0x13, /*!< timer20 ch2 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR20CH3             = 0x14, /*!< timer20 ch3 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR8TRGOUT2          = 0x15, /*!< timer8 trgout2 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR1TRGOUT2          = 0x16, /*!< timer1 trgout2 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR4TRGOUT           = 0x17, /*!< timer4 trgout event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR6TRGOUT           = 0x18, /*!< timer6 trgout event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR3CH4              = 0x19, /*!< timer3 ch4 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR4CH1              = 0x1A, /*!< timer4 ch1 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR1TRGOUT           = 0x1B, /*!< timer1 trgout event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR2CH1              = 0x1C, /*!< timer2 ch1 event as trigger source of ordinary sequence */
    ADC_Ordinary_Trig_TMR7TRGOUT           = 0x1E  /*!< timer7 trgout event as trigger source of ordinary sequence */
} ADC_Ordinary_Trig_Select_Type;

/**
  * @brief adc ordinary channel conversion's external_Trigger_edge type
  */
typedef enum {
    ADC_Ordinary_Trig_Edge_NONE            = 0x00, /*!< ordinary channels trigger detection disabled */
    ADC_Ordinary_Trig_Edge_RISING          = 0x01, /*!< ordinary channels trigger detection on the rising edge */
    ADC_Ordinary_Trig_Edge_FALLING         = 0x02, /*!< ordinary channels trigger detection on the falling edge */
    ADC_Ordinary_Trig_Edge_RISING_FALLING  = 0x03  /*!< ordinary channels trigger detection on both the rising and falling edges */
} ADC_Ordinary_Trig_Edge_Type;

/**
  * @brief adc preempt group external trigger event select type
  */
typedef enum {
    ADC_Preempt_Trig_TMR1CH4               = 0x00, /*!< timer1 ch4 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR1TRGOUT            = 0x01, /*!< timer1 trgout event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR2CH1               = 0x02, /*!< timer2 ch1 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR2TRGOUT            = 0x03, /*!< timer2 trgout event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR3CH2               = 0x04, /*!< timer3 ch2 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR3CH4               = 0x05, /*!< timer3 ch4 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR4CH1               = 0x06, /*!< timer4 ch1 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR4CH2               = 0x07, /*!< timer4 ch2 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR4CH3               = 0x08, /*!< timer4 ch3 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR4TRGOUT            = 0x09, /*!< timer4 trgout event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR5CH4               = 0x0A, /*!< timer5 ch4 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR5TRGOUT            = 0x0B, /*!< timer5 trgout event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR8CH2               = 0x0C, /*!< timer8 ch2 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR8CH3               = 0x0D, /*!< timer8 ch3 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR8CH4               = 0x0E, /*!< timer8 ch4 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_EXINT15               = 0x0F, /*!< exint line15 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR20TRGOUT           = 0x10, /*!< timer20 trgout event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR20TRGOUT2          = 0x11, /*!< timer20 trgout2 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR20CH4              = 0x12, /*!< timer20 ch4 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR1TRGOUT2           = 0x13, /*!< timer1 trgout2 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR8TRGOUT            = 0x14, /*!< timer8 trgout event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR8TRGOUT2           = 0x15, /*!< timer8 trgout2 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR3CH3               = 0x16, /*!< timer3 ch3 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR3TRGOUT            = 0x17, /*!< timer3 trgout event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR3CH1               = 0x18, /*!< timer3 ch1 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR6TRGOUT            = 0x19, /*!< timer6 trgout event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR4CH4               = 0x1A, /*!< timer4 ch4 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR1CH3               = 0x1B, /*!< timer1 ch3 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR20CH2              = 0x1C, /*!< timer20 ch2 event as trigger source of preempt sequence */
    ADC_Preempt_Trig_TMR7TRGOUT            = 0x1E  /*!< timer7 trgout event as trigger source of preempt sequence */
} ADC_Preempt_Trig_Select_Type;

/**
  * @brief adc preempt channel conversion's external_Trigger_edge type
  */
typedef enum {
    ADC_Preempt_Trig_Edge_NONE             = 0x00, /*!< preempt channels trigger detection disabled */
    ADC_Preempt_Trig_Edge_RISING           = 0x01, /*!< preempt channels trigger detection on the rising edge */
    ADC_Preempt_Trig_Edge_FALLING          = 0x02, /*!< preempt channels trigger detection on the falling edge */
    ADC_Preempt_Trig_Edge_RISING_FALLING   = 0x03  /*!< preempt channels trigger detection on both the rising and falling edges */
} ADC_Preempt_Trig_Edge_Type;

/**
  * @brief adc preempt channel type
  */
typedef enum {
    ADC_Preempt_Channel_1                  = 0x00, /*!< adc preempt channel 1 */
    ADC_Preempt_Channel_2                  = 0x01, /*!< adc preempt channel 2 */
    ADC_Preempt_Channel_3                  = 0x02, /*!< adc preempt channel 3 */
    ADC_Preempt_Channel_4                  = 0x03  /*!< adc preempt channel 4 */
} ADC_Preempt_Channel_Type;

/**
  * @brief adc voltage_monitoring type
  */
typedef enum {
    ADC_VMONITOR_Single_ORDINARY           = 0x00800200, /*!< voltage_monitoring on a single ordinary channel */
    ADC_VMONITOR_Single_PREEMPT            = 0x00400200, /*!< voltage_monitoring on a single preempt channel */
    ADC_VMONITOR_Single_Ordinary_PREEMPT   = 0x00C00200, /*!< voltage_monitoring on a single ordinary or preempt channel */
    ADC_VMONITOR_All_ORDINARY              = 0x00800000, /*!< voltage_monitoring on all ordinary channel */
    ADC_VMONITOR_All_PREEMPT               = 0x00400000, /*!< voltage_monitoring on all preempt channel */
    ADC_VMONITOR_All_Ordinary_PREEMPT      = 0x00C00000, /*!< voltage_monitoring on all ordinary and preempt channel */
    ADC_VMONITOR_NONE                      = 0x00000000  /*!< no channel guarded by the voltage_monitoring */
} ADC_Voltage_monitoring_Type;

/**
  * @brief adc oversample ratio type
  */
typedef enum {
    ADC_OverSample_Ratio_2                 = 0x00, /*!< adc oversample ratio 2 */
    ADC_OverSample_Ratio_4                 = 0x01, /*!< adc oversample ratio 4 */
    ADC_OverSample_Ratio_8                 = 0x02, /*!< adc oversample ratio 8 */
    ADC_OverSample_Ratio_16                = 0x03, /*!< adc oversample ratio 16 */
    ADC_OverSample_Ratio_32                = 0x04, /*!< adc oversample ratio 32 */
    ADC_OverSample_Ratio_64                = 0x05, /*!< adc oversample ratio 64 */
    ADC_OverSample_Ratio_128               = 0x06, /*!< adc oversample ratio 128 */
    ADC_OverSample_Ratio_256               = 0x07  /*!< adc oversample ratio 256 */
} ADC_OverSample_Ratio_Type;

/**
  * @brief adc oversample shift type
  */
typedef enum {
    ADC_OverSample_Shift_0                 = 0x00, /*!< adc oversample shift 0 */
    ADC_OverSample_Shift_1                 = 0x01, /*!< adc oversample shift 1 */
    ADC_OverSample_Shift_2                 = 0x02, /*!< adc oversample shift 2 */
    ADC_OverSample_Shift_3                 = 0x03, /*!< adc oversample shift 3 */
    ADC_OverSample_Shift_4                 = 0x04, /*!< adc oversample shift 4 */
    ADC_OverSample_Shift_5                 = 0x05, /*!< adc oversample shift 5 */
    ADC_OverSample_Shift_6                 = 0x06, /*!< adc oversample shift 6 */
    ADC_OverSample_Shift_7                 = 0x07, /*!< adc oversample shift 7 */
    ADC_OverSample_Shift_8                 = 0x08  /*!< adc oversample shift 8 */
} ADC_OverSample_Shift_Type;

/**
  * @brief adc ordinary oversample recover type
  */
typedef enum {
    ADC_OverSample_CONTINUE                = 0x00, /*!< continue mode:when preempt triggered,oversampling is temporary stopped and continued after preempt sequence */
    ADC_OverSample_RESTART                 = 0x01  /*!< restart mode:when preempt triggered,oversampling is aborted and resumed from start after preempt sequence */
} ADC_Ordinary_OverSample_Restart_Type;

/**
  * @brief adc common config type
  */
typedef struct {
    ADC_Combine_Mode_Type                  combine_Mode;                    /*!< adc combine mode select */
    ADC_Div_Type                           div;                             /*!< adc division select */
    ADC_Common_DMA_Mode_Type               common_DMA_Mode;                 /*!< adc common dma mode select */
    confirm_state                          common_DMA_Request_Repeat_state; /*!< adc common dma repeat state */
    ADC_sampling_interval_Type             sampling_interval;               /*!< ordinary shifting mode adjacent adc sampling interval select */
    confirm_state                          tempervintrv_state;              /*!< adc temperature sensor and vintrv state */
    confirm_state                          vbat_state;                      /*!< adc voltage battery state */
} ADC_Common_Config_Type;

/**
  * @brief adc base config type
  */
typedef struct {
    confirm_state                          sequence_Mode;           /*!< adc sequence mode */
    confirm_state                          repeat_Mode;             /*!< adc repeat mode */
    ADC_Data_align_Type                    data_align;              /*!< adc data alignment */
    uint8_t                                ordinary_Channel_length; /*!< adc ordinary channel sequence length*/
} ADC_Base_Config_Type;

/**
  * @brief type define adc register all
  */
typedef struct {

    /**
      * @brief adc sts register, offset:0x00
      */
    union {
        __IO uint32_t sts;
        struct {
            __IO uint32_t vmor                 : 1; /* [0] */
            __IO uint32_t occe                 : 1; /* [1] */
            __IO uint32_t pcce                 : 1; /* [2] */
            __IO uint32_t pccs                 : 1; /* [3] */
            __IO uint32_t occs                 : 1; /* [4] */
            __IO uint32_t occo                 : 1; /* [5] */
            __IO uint32_t rdy                  : 1; /* [6] */
            __IO uint32_t reserved1            : 25;/* [31:7] */
        } sts_bit;
    };

    /**
      * @brief adc ctrl1 register, offset:0x04
      */
    union {
        __IO uint32_t ctrl1;
        struct {
            __IO uint32_t vmcsel               : 5; /* [4:0] */
            __IO uint32_t occeien              : 1; /* [5] */
            __IO uint32_t vmorien              : 1; /* [6] */
            __IO uint32_t pcceien              : 1; /* [7] */
            __IO uint32_t sqen                 : 1; /* [8] */
            __IO uint32_t vmsgen               : 1; /* [9] */
            __IO uint32_t pcautoen             : 1; /* [10] */
            __IO uint32_t ocpen                : 1; /* [11] */
            __IO uint32_t pcpen                : 1; /* [12] */
            __IO uint32_t ocpcnt               : 3; /* [15:13] */
            __IO uint32_t reserved1            : 6; /* [21:16] */
            __IO uint32_t pcvmen               : 1; /* [22] */
            __IO uint32_t ocvmen               : 1; /* [23] */
            __IO uint32_t crsel                : 2; /* [25:24] */
            __IO uint32_t occoien              : 1; /* [26] */
            __IO uint32_t reserved2            : 5; /* [31:27] */
        } ctrl1_bit;
    };

    /**
     * @brief adc ctrl2 register, offset:0x08
     */
    union {
        __IO uint32_t ctrl2;
        struct {
            __IO uint32_t adcen                : 1; /* [0] */
            __IO uint32_t rpen                 : 1; /* [1] */
            __IO uint32_t adcal                : 1; /* [2] */
            __IO uint32_t adcalinit            : 1; /* [3] */
            __IO uint32_t adabrt               : 1; /* [4] */
            __IO uint32_t reserved1            : 3; /* [7:5] */
            __IO uint32_t ocdmaen              : 1; /* [8] */
            __IO uint32_t ocdrcen              : 1; /* [9] */
            __IO uint32_t eocsfen              : 1; /* [10] */
            __IO uint32_t dtalign              : 1; /* [11] */
            __IO uint32_t reserved2            : 4; /* [15:12] */
            __IO uint32_t pctesel_l            : 4; /* [19:16] */
            __IO uint32_t pcete                : 2; /* [21:20] */
            __IO uint32_t pcswtrg              : 1; /* [22] */
            __IO uint32_t pctesel_h            : 1; /* [23] */
            __IO uint32_t octesel_l            : 4; /* [27:24] */
            __IO uint32_t ocete                : 2; /* [29:28] */
            __IO uint32_t ocswtrg              : 1; /* [30] */
            __IO uint32_t octesel_h            : 1; /* [31] */
        } ctrl2_bit;
    };

    /**
    * @brief adc spt1 register, offset:0x0C
    */
    union {
        __IO uint32_t spt1;
        struct {
            __IO uint32_t cspt10               : 3; /* [2:0] */
            __IO uint32_t cspt11               : 3; /* [5:3] */
            __IO uint32_t cspt12               : 3; /* [8:6] */
            __IO uint32_t cspt13               : 3; /* [11:9] */
            __IO uint32_t cspt14               : 3; /* [14:12] */
            __IO uint32_t cspt15               : 3; /* [17:15] */
            __IO uint32_t cspt16               : 3; /* [20:18] */
            __IO uint32_t cspt17               : 3; /* [23:21] */
            __IO uint32_t cspt18               : 3; /* [26:24] */
            __IO uint32_t reserved1            : 5;/* [31:27] */
        } spt1_bit;
    };

    /**
    * @brief adc spt2 register, offset:0x10
    */
    union {
        __IO uint32_t spt2;
        struct {
            __IO uint32_t cspt0                : 3;/* [2:0] */
            __IO uint32_t cspt1                : 3;/* [5:3] */
            __IO uint32_t cspt2                : 3;/* [8:6] */
            __IO uint32_t cspt3                : 3;/* [11:9] */
            __IO uint32_t cspt4                : 3;/* [14:12] */
            __IO uint32_t cspt5                : 3;/* [17:15] */
            __IO uint32_t cspt6                : 3;/* [20:18] */
            __IO uint32_t cspt7                : 3;/* [23:21] */
            __IO uint32_t cspt8                : 3;/* [26:24] */
            __IO uint32_t cspt9                : 3;/* [29:27] */
            __IO uint32_t reserved1            : 2;/* [31:30] */
        } spt2_bit;
    };

    /**
    * @brief adc pcdto1 register, offset:0x14
    */
    union {
        __IO uint32_t pcdto1;
        struct {
            __IO uint32_t pcdto1               : 12; /* [11:0] */
            __IO uint32_t reserved1            : 20; /* [31:12] */
        } pcdto1_bit;
    };

    /**
    * @brief adc pcdto2 register, offset:0x18
    */
    union {
        __IO uint32_t pcdto2;
        struct {
            __IO uint32_t pcdto2               : 12; /* [11:0] */
            __IO uint32_t reserved1            : 20; /* [31:12] */
        } pcdto2_bit;
    };

    /**
    * @brief adc pcdto3 register, offset:0x1C
    */
    union {
        __IO uint32_t pcdto3;
        struct {
            __IO uint32_t pcdto3               : 12; /* [11:0] */
            __IO uint32_t reserved1            : 20; /* [31:12] */
        } pcdto3_bit;
    };

    /**
    * @brief adc pcdto4 register, offset:0x20
    */
    union {
        __IO uint32_t pcdto4;
        struct {
            __IO uint32_t pcdto4               : 12; /* [11:0] */
            __IO uint32_t reserved1            : 20; /* [31:12] */
        } pcdto4_bit;
    };

    /**
    * @brief adc vmhb register, offset:0x24
    */
    union {
        __IO uint32_t vmhb;
        struct {
            __IO uint32_t vmhb                 : 12; /* [11:0] */
            __IO uint32_t reserved1            : 20; /* [31:12] */
        } vmhb_bit;
    };

    /**
    * @brief adc vmlb register, offset:0x28
    */
    union {
        __IO uint32_t vmlb;
        struct {
            __IO uint32_t vmlb                 : 12; /* [11:0] */
            __IO uint32_t reserved1            : 20; /* [31:12] */
        } vmlb_bit;
    };

    /**
    * @brief adc osq1 register, offset:0x2C
    */
    union {
        __IO uint32_t osq1;
        struct {
            __IO uint32_t osn13                : 5; /* [4:0] */
            __IO uint32_t osn14                : 5; /* [9:5] */
            __IO uint32_t osn15                : 5; /* [14:10] */
            __IO uint32_t osn16                : 5; /* [19:15] */
            __IO uint32_t oclen                : 4; /* [23:20] */
            __IO uint32_t reserved1            : 8; /* [31:24] */
        } osq1_bit;
    };

    /**
    * @brief adc osq2 register, offset:0x30
    */
    union {
        __IO uint32_t osq2;
        struct {
            __IO uint32_t osn7                 : 5; /* [4:0] */
            __IO uint32_t osn8                 : 5; /* [9:5] */
            __IO uint32_t osn9                 : 5; /* [14:10] */
            __IO uint32_t osn10                : 5; /* [19:15] */
            __IO uint32_t osn11                : 5; /* [24:20] */
            __IO uint32_t osn12                : 5; /* [29:25] */
            __IO uint32_t reserved1            : 2; /* [31:30] */
        } osq2_bit;
    };

    /**
    * @brief adc osq3 register, offset:0x34
    */
    union {
        __IO uint32_t osq3;
        struct {
            __IO uint32_t osn1                 : 5; /* [4:0] */
            __IO uint32_t osn2                 : 5; /* [9:5] */
            __IO uint32_t osn3                 : 5; /* [14:10] */
            __IO uint32_t osn4                 : 5; /* [19:15] */
            __IO uint32_t osn5                 : 5; /* [24:20] */
            __IO uint32_t osn6                 : 5; /* [29:25] */
            __IO uint32_t reserved1            : 2; /* [31:30] */
        } osq3_bit;
    };

    /**
    * @brief adc psq register, offset:0x38
    */
    union {
        __IO uint32_t psq;
        struct {
            __IO uint32_t psn1                 : 5; /* [4:0] */
            __IO uint32_t psn2                 : 5; /* [9:5] */
            __IO uint32_t psn3                 : 5; /* [14:10] */
            __IO uint32_t psn4                 : 5; /* [19:15] */
            __IO uint32_t pclen                : 2; /* [21:20] */
            __IO uint32_t reserved1            : 10;/* [31:22] */
        } psq_bit;
    };

    /**
    * @brief adc pdt1 register, offset:0x3C
    */
    union {
        __IO uint32_t pdt1;
        struct {
            __IO uint32_t pdt1                 : 16; /* [15:0] */
            __IO uint32_t reserved1            : 16; /* [31:16] */
        } pdt1_bit;
    };

    /**
    * @brief adc pdt2 register, offset:0x40
    */
    union {
        __IO uint32_t pdt2;
        struct {
            __IO uint32_t pdt2                 : 16; /* [15:0] */
            __IO uint32_t reserved1            : 16; /* [31:16] */
        } pdt2_bit;
    };

    /**
    * @brief adc pdt3 register, offset:0x44
    */
    union {
        __IO uint32_t pdt3;
        struct {
            __IO uint32_t pdt3                 : 16; /* [15:0] */
            __IO uint32_t reserved1            : 16; /* [31:16] */
        } pdt3_bit;
    };

    /**
    * @brief adc pdt4 register, offset:0x48
    */
    union {
        __IO uint32_t pdt4;
        struct {
            __IO uint32_t pdt4                 : 16; /* [15:0] */
            __IO uint32_t reserved1            : 16; /* [31:16] */
        } pdt4_bit;
    };

    /**
    * @brief adc odt register, offset:0x4C
    */
    union {
        __IO uint32_t odt;
        struct {
            __IO uint32_t odt                  : 16; /* [15:0] */
            __IO uint32_t reserved1            : 16; /* [31:16] */
        } odt_bit;
    };

    __IO uint32_t reserved1[12];

    /**
    * @brief adc ovsp register, offset:0x80
    */
    union {
        __IO uint32_t ovsp;
        struct {
            __IO uint32_t oosen                : 1; /* [0] */
            __IO uint32_t posen                : 1; /* [1] */
            __IO uint32_t osrsel               : 3; /* [4:2] */
            __IO uint32_t osssel               : 4; /* [8:5] */
            __IO uint32_t oostren              : 1; /* [9] */
            __IO uint32_t oosrsel              : 1; /* [10] */
            __IO uint32_t reserved1            : 21; /* [31:11] */
        } ovsp_bit;
    };

    __IO uint32_t reserved2[12];

    /**
    * @brief adc calval register, offset:0xB4
    */
    union {
        __IO uint32_t calval;
        struct {
            __IO uint32_t calval               : 7; /* [6:0] */
            __IO uint32_t reserved1            : 25; /* [31:7] */
        } calval_bit;
    };
} ADC_Type;

/**
  * @brief type define adc register all
  */
typedef struct {

    /**
      * @brief adc csts register, offset:0x00
      */
    union {
        __IO uint32_t csts;
        struct {
            __IO uint32_t vmor1                : 1; /* [0] */
            __IO uint32_t occe1                : 1; /* [1] */
            __IO uint32_t pcce1                : 1; /* [2] */
            __IO uint32_t pccs1                : 1; /* [3] */
            __IO uint32_t occs1                : 1; /* [4] */
            __IO uint32_t occo1                : 1; /* [5] */
            __IO uint32_t rdy1                 : 1; /* [6] */
            __IO uint32_t reserved1            : 1; /* [7] */
            __IO uint32_t vmor2                : 1; /* [8] */
            __IO uint32_t occe2                : 1; /* [9] */
            __IO uint32_t pcce2                : 1; /* [10] */
            __IO uint32_t pccs2                : 1; /* [11] */
            __IO uint32_t occs2                : 1; /* [12] */
            __IO uint32_t occo2                : 1; /* [13] */
            __IO uint32_t rdy2                 : 1; /* [14] */
            __IO uint32_t reserved2            : 1; /* [15] */
            __IO uint32_t vmor3                : 1; /* [16] */
            __IO uint32_t occe3                : 1; /* [17] */
            __IO uint32_t pcce3                : 1; /* [18] */
            __IO uint32_t pccs3                : 1; /* [19] */
            __IO uint32_t occs3                : 1; /* [20] */
            __IO uint32_t occo3                : 1; /* [21] */
            __IO uint32_t rdy3                 : 1; /* [22] */
            __IO uint32_t reserved3            : 9; /* [31:23] */
        } csts_bit;
    };

    /**
      * @brief adc cctrl register, offset:0x04
      */
    union {
        __IO uint32_t cctrl;
        struct {
            __IO uint32_t mssel                : 5; /* [4_0] */
            __IO uint32_t reserved1            : 3; /* [7:5] */
            __IO uint32_t asisel               : 4; /* [11:8] */
            __IO uint32_t reserved2            : 1; /* [12] */
            __IO uint32_t msdrcen              : 1; /* [13] */
            __IO uint32_t msdmasel_l           : 2; /* [15:14] */
            __IO uint32_t adcdiv               : 4; /* [19:16] */
            __IO uint32_t reserved3            : 2; /* [21:20] */
            __IO uint32_t vbaten               : 1; /* [22] */
            __IO uint32_t itsrven              : 1; /* [23] */
            __IO uint32_t reserved4            : 4; /* [27:24] */
            __IO uint32_t msdmasel_h           : 1; /* [28] */
            __IO uint32_t reserved5            : 3; /* [31:29] */
        } cctrl_bit;
    };

    /**
    * @brief adc codt register, offset:0x08
    */
    union {
        __IO uint32_t codt;
        struct {
            __IO uint32_t codtl                : 16; /* [15:0] */
            __IO uint32_t codth                : 16; /* [31:16] */
        } codt_bit;
    };
} adccom_Type;

/**
  * @}
  */
#define ADC1                             ((ADC_Type *) ADC1_BASE)
#define ADC2                             ((ADC_Type *) ADC2_BASE)
#define ADC3                             ((ADC_Type *) ADC3_BASE)
#define ADCCOM                           ((adccom_Type *) ADCCOM_BASE)

/** @defgroup ADC_exported_functions
  * @{
  */

void ADC_Reset(void);
void ADC_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_Base_Default_Para_Init(ADC_Base_Config_Type *ADC_Base_struct);
void ADC_Base_Config(ADC_Type *ADC_x, ADC_Base_Config_Type *ADC_Base_struct);
void ADC_Common_Default_Para_Init(ADC_Common_Config_Type *ADC_Common_struct);
void ADC_Common_Config(ADC_Common_Config_Type *ADC_Common_struct);
void ADC_Resolution_Set(ADC_Type *ADC_x, ADC_Resolution_Type resolution);
void ADC_Voltage_Battery_Enable(confirm_state new_state);
void ADC_DMA_Mode_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_DMA_Request_Repeat_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_Interrupt_Enable(ADC_Type *ADC_x, uint32_t ADC_int, confirm_state new_state);
void ADC_Calibration_Value_Set(ADC_Type *ADC_x, uint8_t ADC_Calibration_value);
void ADC_Calibration_Init(ADC_Type *ADC_x);
flag_status ADC_Calibration_Init_Status_Get(ADC_Type *ADC_x);
void ADC_Calibration_Start(ADC_Type *ADC_x);
flag_status ADC_Calibration_Status_Get(ADC_Type *ADC_x);
void ADC_Voltage_Monitor_Enable(ADC_Type *ADC_x, ADC_Voltage_monitoring_Type ADC_Voltage_monitoring);
void ADC_Voltage_Monitor_Threshold_Value_Set(ADC_Type *ADC_x, uint16_t ADC_high_threshold, uint16_t ADC_Low_threshold);
void ADC_Voltage_Monitor_Single_Channel_Select(ADC_Type *ADC_x, ADC_Channel_Select_Type ADC_Channel);
void ADC_Ordinary_Channel_Set(ADC_Type *ADC_x, ADC_Channel_Select_Type ADC_Channel, uint8_t ADC_sequence, ADC_sampletime_Select_Type ADC_sampletime);
void ADC_Preempt_Channel_Length_Set(ADC_Type *ADC_x, uint8_t ADC_Channel_lenght);
void ADC_Preempt_Channel_Set(ADC_Type *ADC_x, ADC_Channel_Select_Type ADC_Channel, uint8_t ADC_sequence, ADC_sampletime_Select_Type ADC_sampletime);
void ADC_Ordinary_Conversion_Trigger_Set(ADC_Type *ADC_x, ADC_Ordinary_Trig_Select_Type ADC_Ordinary_trig, ADC_Ordinary_Trig_Edge_Type ADC_Ordinary_Trig_edge);
void ADC_Preempt_Conversion_Trigger_Set(ADC_Type *ADC_x, ADC_Preempt_Trig_Select_Type ADC_Preempt_trig, ADC_Preempt_Trig_Edge_Type ADC_Preempt_Trig_edge);
void ADC_Preempt_Offset_Value_Set(ADC_Type *ADC_x, ADC_Preempt_Channel_Type ADC_Preempt_Channel, uint16_t ADC_Offset_value);
void ADC_Ordinary_Part_Count_Set(ADC_Type *ADC_x, uint8_t ADC_Channel_count);
void ADC_Ordinary_Part_Mode_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_Preempt_Part_Mode_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_Preempt_Auto_Mode_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_Conversion_stop(ADC_Type *ADC_x);
flag_status ADC_Conversion_Stop_Status_Get(ADC_Type *ADC_x);
void ADC_Occe_Each_Conversion_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_Ordinary_Software_Trigger_Enable(ADC_Type *ADC_x, confirm_state new_state);
flag_status ADC_Ordinary_Software_Trigger_Status_Get(ADC_Type *ADC_x);
void ADC_Preempt_Software_Trigger_Enable(ADC_Type *ADC_x, confirm_state new_state);
flag_status ADC_Preempt_Software_Trigger_Status_Get(ADC_Type *ADC_x);
uint16_t ADC_Ordinary_Conversion_Data_Get(ADC_Type *ADC_x);
uint32_t ADC_Combine_Ordinary_Conversion_Data_Get(void);
uint16_t ADC_Preempt_Conversion_Data_Get(ADC_Type *ADC_x, ADC_Preempt_Channel_Type ADC_Preempt_Channel);
flag_status ADC_Flag_Get(ADC_Type *ADC_x, uint8_t ADC_flag);
void ADC_Flag_Clear(ADC_Type *ADC_x, uint32_t ADC_flag);
void ADC_Ordinary_OverSample_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_Preempt_OverSample_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_OverSample_Ratio_Shift_Set(ADC_Type *ADC_x, ADC_OverSample_Ratio_Type ADC_OverSample_ratio, ADC_OverSample_Shift_Type ADC_OverSample_shift);
void ADC_Ordinary_OverSample_Trig_Enable(ADC_Type *ADC_x, confirm_state new_state);
void ADC_Ordinary_OverSample_Restart_Set(ADC_Type *ADC_x, ADC_Ordinary_OverSample_Restart_Type ADC_Ordinary_OverSample_restart);

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
