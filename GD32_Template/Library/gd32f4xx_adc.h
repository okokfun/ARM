/*!
    文件:    gd32f4xx_adc.h
    简介:   definitions for the ADC

    版本: 2016-08-15, V1.0.0, firmware for GD32F4xx
    版本: 2018-12-12, V2.0.0, firmware for GD32F4xx
    版本: 2020-09-30, V2.1.0, firmware for GD32F4xx
    版本: 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32F4XX_ADC_H
#define GD32F4XX_ADC_H

#include "gd32f4xx.h"

/* ADC definitions */
#define ADC0                            ADC_BASE
#define ADC1                            (ADC_BASE + 0x100U)
#define ADC2                            (ADC_BASE + 0x200U)

/* registers definitions */
#define ADC_STAT(adcx)                  REG32((adcx) + 0x00U)             /*!< ADC status register */
#define ADC_CTL0(adcx)                  REG32((adcx) + 0x04U)             /*!< ADC control register 0 */
#define ADC_CTL1(adcx)                  REG32((adcx) + 0x08U)             /*!< ADC control register 1 */
#define ADC_SAMPT0(adcx)                REG32((adcx) + 0x0CU)             /*!< ADC sampling time register 0 */
#define ADC_SAMPT1(adcx)                REG32((adcx) + 0x10U)             /*!< ADC sampling time register 1 */
#define ADC_IOFF0(adcx)                 REG32((adcx) + 0x14U)             /*!< ADC inserted channel data offset register 0 */
#define ADC_IOFF1(adcx)                 REG32((adcx) + 0x18U)             /*!< ADC inserted channel data offset register 1 */
#define ADC_IOFF2(adcx)                 REG32((adcx) + 0x1CU)             /*!< ADC inserted channel data offset register 2 */
#define ADC_IOFF3(adcx)                 REG32((adcx) + 0x20U)             /*!< ADC inserted channel data offset register 3 */
#define ADC_WDHT(adcx)                  REG32((adcx) + 0x24U)             /*!< ADC watchdog high threshold register */
#define ADC_WDLT(adcx)                  REG32((adcx) + 0x28U)             /*!< ADC watchdog low threshold register */
#define ADC_RSQ0(adcx)                  REG32((adcx) + 0x2CU)             /*!< ADC regular sequence register 0 */
#define ADC_RSQ1(adcx)                  REG32((adcx) + 0x30U)             /*!< ADC regular sequence register 1 */
#define ADC_RSQ2(adcx)                  REG32((adcx) + 0x34U)             /*!< ADC regular sequence register 2 */
#define ADC_ISQ(adcx)                   REG32((adcx) + 0x38U)             /*!< ADC inserted sequence register */
#define ADC_IDATA0(adcx)                REG32((adcx) + 0x3CU)             /*!< ADC inserted data register 0 */
#define ADC_IDATA1(adcx)                REG32((adcx) + 0x40U)             /*!< ADC inserted data register 1 */
#define ADC_IDATA2(adcx)                REG32((adcx) + 0x44U)             /*!< ADC inserted data register 2 */
#define ADC_IDATA3(adcx)                REG32((adcx) + 0x48U)             /*!< ADC inserted data register 3 */
#define ADC_RDATA(adcx)                 REG32((adcx) + 0x4CU)             /*!< ADC regular data register */
#define ADC_OVSAMPCTL(adcx)             REG32((adcx) + 0x80U)             /*!< ADC oversampling control register */
#define ADC_SSTAT                       REG32((ADC_BASE) + 0x300U)        /*!< ADC summary status register */
#define ADC_SYNCCTL                     REG32((ADC_BASE) + 0x304U)        /*!< ADC synchronization control register */
#define ADC_SYNCDATA                    REG32((ADC_BASE) + 0x308U)        /*!< ADC synchronization regular data register */

/* bits definitions */
/* ADC_STAT */
#define ADC_STAT_WDE                    BIT(0)                           /*!< analog watchdog event flag */
#define ADC_STAT_EOC                    BIT(1)                           /*!< end of conversion */
#define ADC_STAT_EOIC                   BIT(2)                           /*!< inserted channel end of conversion */
#define ADC_STAT_STIC                   BIT(3)                           /*!< inserted channel start flag */
#define ADC_STAT_STRC                   BIT(4)                           /*!< regular channel start flag */
#define ADC_STAT_ROVF                   BIT(5)                           /*!< regular data register overflow */

/* ADC_CTL0 */
#define ADC_CTL0_WDCHSEL                BITS(0,4)                        /*!< analog watchdog channel select bits */
#define ADC_CTL0_EOCIE                  BIT(5)                           /*!< interrupt enable for EOC */
#define ADC_CTL0_WDEIE                  BIT(6)                           /*!< analog watchdog interrupt enable */
#define ADC_CTL0_EOICIE                 BIT(7)                           /*!< interrupt enable for inserted channels */
#define ADC_CTL0_SM                     BIT(8)                           /*!< scan mode */
#define ADC_CTL0_WDSC                   BIT(9)                           /*!< when in scan mode, analog watchdog is effective on a single channel */
#define ADC_CTL0_ICA                    BIT(10)                          /*!< automatic inserted group conversion */
#define ADC_CTL0_DISRC                  BIT(11)                          /*!< discontinuous mode on regular channels */
#define ADC_CTL0_DISIC                  BIT(12)                          /*!< discontinuous mode on inserted channels */
#define ADC_CTL0_DISNUM                 BITS(13,15)                      /*!< discontinuous mode channel count */
#define ADC_CTL0_IWDEN                  BIT(22)                          /*!< analog watchdog enable on inserted channels */
#define ADC_CTL0_RWDEN                  BIT(23)                          /*!< analog watchdog enable on regular channels */
#define ADC_CTL0_DRES                   BITS(24,25)                      /*!< ADC data resolution */
#define ADC_CTL0_ROVFIE                 BIT(26)                          /*!< interrupt enable for ROVF */

/* ADC_CTL1 */
#define ADC_CTL1_ADCON                  BIT(0)                           /*!< ADC converter on */
#define ADC_CTL1_CTN                    BIT(1)                           /*!< continuous conversion */
#define ADC_CTL1_CLB                    BIT(2)                           /*!< ADC calibration */
#define ADC_CTL1_RSTCLB                 BIT(3)                           /*!< reset calibration */
#define ADC_CTL1_DMA                    BIT(8)                           /*!< direct memory access mode */
#define ADC_CTL1_DDM                    BIT(9)                           /*!< DMA disable mode */
#define ADC_CTL1_EOCM                   BIT(10)                          /*!< end of conversion mode */
#define ADC_CTL1_DAL                    BIT(11)                          /*!< data alignment */
#define ADC_CTL1_ETSIC                  BITS(16,19)                      /*!< external event select for inserted group */
#define ADC_CTL1_ETMIC                  BITS(20,21)                      /*!< external trigger conversion mode for inserted channels */
#define ADC_CTL1_SWICST                 BIT(22)                          /*!< start conversion of inserted channels */
#define ADC_CTL1_ETSRC                  BITS(24,27)                      /*!< external event select for regular group */
#define ADC_CTL1_ETMRC                  BITS(28,29)                      /*!< external trigger conversion mode for regular channels */
#define ADC_CTL1_SWRCST                 BIT(30)                          /*!< start conversion of regular channels */

/* ADC_SAMPTx x=0..1 */
#define ADC_SAMPTX_SPTN                 BITS(0,2)                        /*!< channel x sample time selection */

/* ADC_IOFFx x=0..3 */
#define ADC_IOFFX_IOFF                  BITS(0,11)                       /*!< data offset for inserted channel x */

/* ADC_WDHT */
#define ADC_WDHT_WDHT                   BITS(0,11)                       /*!< analog watchdog high threshold */

/* ADC_WDLT */
#define ADC_WDLT_WDLT                   BITS(0,11)                       /*!< analog watchdog low threshold */

/* ADC_RSQx */
#define ADC_RSQX_RSQN                   BITS(0,4)                        /*!< x conversion in regular sequence */
#define ADC_RSQ0_RL                     BITS(20,23)                      /*!< regular channel sequence length */

/* ADC_ISQ */
#define ADC_ISQ_ISQN                    BITS(0,4)                        /*!< x conversion in regular sequence */
#define ADC_ISQ_IL                      BITS(20,21)                      /*!< inserted sequence length */

/* ADC_IDATAx x=0..3*/
#define ADC_IDATAX_IDATAN               BITS(0,15)                       /*!< inserted data x */

/* ADC_RDATA */
#define ADC_RDATA_RDATA                 BITS(0,15)                       /*!< regular data */

/* ADC_OVSAMPCTL */
#define ADC_OVSAMPCTL_OVSEN             BIT(0)                           /*!< oversampling enable */
#define ADC_OVSAMPCTL_OVSR              BITS(2,4)                        /*!< oversampling ratio */
#define ADC_OVSAMPCTL_OVSS              BITS(5,8)                        /*!< oversampling shift */
#define ADC_OVSAMPCTL_TOVS              BIT(9)                           /*!< triggered oversampling */

/* ADC_SSTAT */
#define ADC_SSTAT_WDE0                  BIT(0)                           /*!< the mirror image of the WDE bit of ADC0 */
#define ADC_SSTAT_EOC0                  BIT(1)                           /*!< the mirror image of the EOC bit of ADC0 */
#define ADC_SSTAT_EOIC0                 BIT(2)                           /*!< the mirror image of the EOIC bit of ADC0 */
#define ADC_SSTAT_STIC0                 BIT(3)                           /*!< the mirror image of the STIC bit of ADC0 */
#define ADC_SSTAT_STRC0                 BIT(4)                           /*!< the mirror image of the STRC bit of ADC0 */
#define ADC_SSTAT_ROVF0                 BIT(5)                           /*!< the mirror image of the ROVF bit of ADC0 */
#define ADC_SSTAT_WDE1                  BIT(8)                           /*!< the mirror image of the WDE bit of ADC1 */
#define ADC_SSTAT_EOC1                  BIT(9)                           /*!< the mirror image of the EOC bit of ADC1 */
#define ADC_SSTAT_EOIC1                 BIT(10)                          /*!< the mirror image of the EOIC bit of ADC1 */
#define ADC_SSTAT_STIC1                 BIT(11)                          /*!< the mirror image of the STIC bit of ADC1 */
#define ADC_SSTAT_STRC1                 BIT(12)                          /*!< the mirror image of the STRC bit of ADC1 */
#define ADC_SSTAT_ROVF1                 BIT(13)                          /*!< the mirror image of the ROVF bit of ADC1 */
#define ADC_SSTAT_WDE2                  BIT(16)                          /*!< the mirror image of the WDE bit of ADC2 */
#define ADC_SSTAT_EOC2                  BIT(17)                          /*!< the mirror image of the EOC bit of ADC2 */
#define ADC_SSTAT_EOIC2                 BIT(18)                          /*!< the mirror image of the EOIC bit of ADC2 */
#define ADC_SSTAT_STIC2                 BIT(19)                          /*!< the mirror image of the STIC bit of ADC2 */
#define ADC_SSTAT_STRC2                 BIT(20)                          /*!< the mirror image of the STRC bit of ADC2 */
#define ADC_SSTAT_ROVF2                 BIT(21)                          /*!< the mirror image of the ROVF bit of ADC2 */

/* ADC_SYNCCTL */
#define ADC_SYNCCTL_SYNCM               BITS(0,4)                        /*!< ADC synchronization mode */
#define ADC_SYNCCTL_SYNCDLY             BITS(8,11)                       /*!< ADC synchronization delay */
#define ADC_SYNCCTL_SYNCDDM             BIT(13)                          /*!< ADC synchronization DMA disable mode */
#define ADC_SYNCCTL_SYNCDMA             BITS(14,15)                      /*!< ADC synchronization DMA mode selection */
#define ADC_SYNCCTL_ADCCK               BITS(16,18)                      /*!< ADC clock */
#define ADC_SYNCCTL_VBATEN              BIT(22)                          /*!< channel 18 (1/4 voltate of external battery) enable of ADC0 */
#define ADC_SYNCCTL_TSVREN              BIT(23)                          /*!< channel 16 (temperature sensor) and 17 (internal reference voltage) enable of ADC0 */

/* ADC_SYNCDATA */
#define ADC_SYNCDATA_SYNCDATA0          BITS(0,15)                       /*!< regular data1 in ADC synchronization mode */
#define ADC_SYNCDATA_SYNCDATA1          BITS(16,31)                      /*!< regular data2 in ADC synchronization mode */

/* constants definitions */
/* ADC status flag */
#define ADC_Flag_WDE                    ADC_STAT_WDE                     /*!< analog watchdog event flag */
#define ADC_Flag_EOC                    ADC_STAT_EOC                     /*!< end of conversion */
#define ADC_Flag_EOIC                   ADC_STAT_EOIC                    /*!< inserted channel end of conversion */
#define ADC_Flag_STIC                   ADC_STAT_STIC                    /*!< inserted channel start flag */
#define ADC_Flag_STRC                   ADC_STAT_STRC                    /*!< regular channel start flag */
#define ADC_Flag_ROVF                   ADC_STAT_ROVF                    /*!< regular data register overflow */

/* ADC_ctl0 register value */
#define CTL0_DISNUM(regval)             (BITS(13,15) & ((uint32_t)(regval) << 13))   /*!< write value to ADC_CTL0_DISNUM bit field */

/* ADC special function definitions */
#define ADC_SCAN_MODE                   ADC_CTL0_SM                   /*!< scan mode */
#define ADC_Inserted_Channel_AUTO       ADC_CTL0_ICA                  /*!< inserted channel group convert automatically */
#define ADC_CONTINUOUS_MODE             ADC_CTL1_CTN                  /*!< continuous mode */

/* temperature sensor channel, internal reference voltage channel, VBAT channel */
#define ADC_VBAT_Channel_SWITCH         ADC_SYNCCTL_VBATEN                  /*!< VBAT channel */
#define ADC_TEMP_VREF_Channel_SWITCH    ADC_SYNCCTL_TSVREN                  /*!< Vref and Vtemp channel */

/* ADC synchronization mode */
#define SYNCCTL_SYNCM(regval)              (BITS(0,4) & ((uint32_t)(regval)))    /*!< write value to ADC_CTL0_SYNCM bit field */
#define ADC_Sync_Mode_INDEPENDENT                           SYNCCTL_SYNCM(0)     /*!< ADC synchronization mode disabled.All the ADCs work independently */
#define ADC_DAUL_REGULAL_PARALLEL_Inserted_PARALLEL         SYNCCTL_SYNCM(1)     /*!< ADC0 and ADC1 work in combined regular parallel & inserted parallel mode. ADC2 works independently */
#define ADC_DAUL_REGULAL_PARALLEL_Inserted_ROTATION         SYNCCTL_SYNCM(2)     /*!< ADC0 and ADC1 work in combined regular parallel & trigger rotation mode. ADC2 works independently */
#define ADC_DAUL_Inserted_PARALLEL                          SYNCCTL_SYNCM(5)     /*!< ADC0 and ADC1 work in inserted parallel mode. ADC2 works independently */
#define ADC_DAUL_REGULAL_PARALLEL                           SYNCCTL_SYNCM(6)     /*!< ADC0 and ADC1 work in regular parallel mode. ADC2 works independently */
#define ADC_DAUL_REGULAL_FOLLOW_UP                          SYNCCTL_SYNCM(7)     /*!< ADC0 and ADC1 work in follow-up mode. ADC2 works independently */
#define ADC_DAUL_Inserted_TRRIGGER_ROTATION                 SYNCCTL_SYNCM(9)     /*!< ADC0 and ADC1 work in trigger rotation mode. ADC2 works independently */
#define ADC_ALL_REGULAL_PARALLEL_Inserted_PARALLEL          SYNCCTL_SYNCM(17)    /*!< all ADCs work in combined regular parallel & inserted parallel mode */
#define ADC_ALL_REGULAL_PARALLEL_Inserted_ROTATION          SYNCCTL_SYNCM(18)    /*!< all ADCs work in combined regular parallel & trigger rotation mode */
#define ADC_ALL_Inserted_PARALLEL                           SYNCCTL_SYNCM(21)    /*!< all ADCs work in inserted parallel mode */
#define ADC_ALL_REGULAL_PARALLEL                            SYNCCTL_SYNCM(22)    /*!< all ADCs work in regular parallel mode */
#define ADC_ALL_REGULAL_FOLLOW_UP                           SYNCCTL_SYNCM(23)    /*!< all ADCs work in follow-up mode */
#define ADC_ALL_Inserted_TRRIGGER_ROTATION                  SYNCCTL_SYNCM(25)    /*!< all ADCs work in trigger rotation mode */

/* ADC data alignment */
#define ADC_DATAALIGN_RIGHT             ((uint32_t)0x00000000U)                  /*!< LSB alignment */
#define ADC_DATAALIGN_LEFT              ADC_CTL1_DAL                             /*!< MSB alignment */

/* external trigger mode for regular and inserted  channel */
#define EXTERNAL_Trigger_DISABLE        ((uint32_t)0x00000000U)           /*!< external trigger disable */
#define EXTERNAL_Trigger_RISING         ((uint32_t)0x00000001U)           /*!< rising edge of external trigger */
#define EXTERNAL_Trigger_FALLING        ((uint32_t)0x00000002U)           /*!< falling edge of external trigger */
#define EXTERNAL_Trigger_RISING_FALLING ((uint32_t)0x00000003U)           /*!< rising and falling edge of external trigger */

/* ADC external trigger select for regular channel */
#define CTL1_ETSRC(regval)              (BITS(24,27) & ((uint32_t)(regval) << 24))
#define ADC_EXTTRIG_Regular_T0_CH0      CTL1_ETSRC(0)                    /*!< timer 0 CC0 event select */
#define ADC_EXTTRIG_Regular_T0_CH1      CTL1_ETSRC(1)                    /*!< timer 0 CC1 event select */
#define ADC_EXTTRIG_Regular_T0_CH2      CTL1_ETSRC(2)                    /*!< timer 0 CC2 event select */
#define ADC_EXTTRIG_Regular_T1_CH1      CTL1_ETSRC(3)                    /*!< timer 1 CC1 event select */
#define ADC_EXTTRIG_Regular_T1_CH2      CTL1_ETSRC(4)                    /*!< timer 1 CC2 event select */
#define ADC_EXTTRIG_Regular_T1_CH3      CTL1_ETSRC(5)                    /*!< timer 1 CC3 event select */
#define ADC_EXTTRIG_Regular_T1_TRGO     CTL1_ETSRC(6)                    /*!< timer 1 TRGO event select */
#define ADC_EXTTRIG_Regular_T2_CH0      CTL1_ETSRC(7)                    /*!< timer 2 CC0 event select */
#define ADC_EXTTRIG_Regular_T2_TRGO     CTL1_ETSRC(8)                    /*!< timer 2 TRGO event select */
#define ADC_EXTTRIG_Regular_T3_CH3      CTL1_ETSRC(9)                    /*!< timer 3 CC3 event select */
#define ADC_EXTTRIG_Regular_T4_CH0      CTL1_ETSRC(10)                   /*!< timer 4 CC0 event select */
#define ADC_EXTTRIG_Regular_T4_CH1      CTL1_ETSRC(11)                   /*!< timer 4 CC1 event select */
#define ADC_EXTTRIG_Regular_T4_CH2      CTL1_ETSRC(12)                   /*!< timer 4 CC2 event select */
#define ADC_EXTTRIG_Regular_T7_CH0      CTL1_ETSRC(13)                   /*!< timer 7 CC0 event select */
#define ADC_EXTTRIG_Regular_T7_TRGO     CTL1_ETSRC(14)                   /*!< timer 7 TRGO event select */
#define ADC_EXTTRIG_Regular_EXTI_11     CTL1_ETSRC(15)                   /*!< extiline 11 select  */

/* ADC external trigger select for inserted channel */
#define CTL1_ETSIC(regval)              (BITS(16,19) & ((uint32_t)(regval) << 16))
#define ADC_EXTTRIG_Inserted_T0_CH3     CTL1_ETSIC(0)                    /*!< timer0 capture compare 3 */
#define ADC_EXTTRIG_Inserted_T0_TRGO    CTL1_ETSIC(1)                    /*!< timer0 TRGO event */
#define ADC_EXTTRIG_Inserted_T1_CH0     CTL1_ETSIC(2)                    /*!< timer1 capture compare 0 */
#define ADC_EXTTRIG_Inserted_T1_TRGO    CTL1_ETSIC(3)                    /*!< timer1 TRGO event */
#define ADC_EXTTRIG_Inserted_T2_CH1     CTL1_ETSIC(4)                    /*!< timer2 capture compare 1 */
#define ADC_EXTTRIG_Inserted_T2_CH3     CTL1_ETSIC(5)                    /*!< timer2 capture compare 3 */
#define ADC_EXTTRIG_Inserted_T3_CH0     CTL1_ETSIC(6)                    /*!< timer3 capture compare 0 */
#define ADC_EXTTRIG_Inserted_T3_CH1     CTL1_ETSIC(7)                    /*!< timer3 capture compare 1 */
#define ADC_EXTTRIG_Inserted_T3_CH2     CTL1_ETSIC(8)                    /*!< timer3 capture compare 2 */
#define ADC_EXTTRIG_Inserted_T3_TRGO    CTL1_ETSIC(9)                    /*!< timer3 capture compare TRGO */
#define ADC_EXTTRIG_Inserted_T4_CH3     CTL1_ETSIC(10)                   /*!< timer4 capture compare 3 */
#define ADC_EXTTRIG_Inserted_T4_TRGO    CTL1_ETSIC(11)                   /*!< timer4 capture compare TRGO */
#define ADC_EXTTRIG_Inserted_T7_CH1     CTL1_ETSIC(12)                   /*!< timer7 capture compare 1 */
#define ADC_EXTTRIG_Inserted_T7_CH2     CTL1_ETSIC(13)                   /*!< timer7 capture compare 2 */
#define ADC_EXTTRIG_Inserted_T7_CH3     CTL1_ETSIC(14)                   /*!< timer7 capture compare 3 */
#define ADC_EXTTRIG_Inserted_EXTI_15    CTL1_ETSIC(15)                   /*!< external interrupt line 15 */

/* ADC channel sample time */
#define SAMPTX_SPT(regval)               (BITS(0,2) & ((uint32_t)(regval) << 0))     /*!< write value to ADC_SAMPTX_SPT bit field */
#define ADC_SAMPLETIME_3                 SAMPTX_SPT(0)                  /*!< 3 sampling cycles */
#define ADC_SAMPLETIME_15                SAMPTX_SPT(1)                  /*!< 15 sampling cycles */
#define ADC_SAMPLETIME_28                SAMPTX_SPT(2)                  /*!< 28 sampling cycles */
#define ADC_SAMPLETIME_56                SAMPTX_SPT(3)                  /*!< 56 sampling cycles */
#define ADC_SAMPLETIME_84                SAMPTX_SPT(4)                  /*!< 84 sampling cycles */
#define ADC_SAMPLETIME_112               SAMPTX_SPT(5)                  /*!< 112 sampling cycles */
#define ADC_SAMPLETIME_144               SAMPTX_SPT(6)                  /*!< 144 sampling cycles */
#define ADC_SAMPLETIME_480               SAMPTX_SPT(7)                  /*!< 480 sampling cycles */

/* ADC_ioffx register value */
#define IOFFX_IOFF(regval)               (BITS(0,11) & ((uint32_t)(regval) << 0))    /*!< write value to ADC_IOFFX_IOFF bit field */

/* ADC_wdht register value */
#define WDHT_WDHT(regval)                (BITS(0,11) & ((uint32_t)(regval) << 0))    /*!< write value to ADC_WDHT_WDHT bit field */

/* ADC_wdlt register value */
#define WDLT_WDLT(regval)                (BITS(0,11) & ((uint32_t)(regval) << 0))    /*!< write value to ADC_WDLT_WDLT bit field */

/* ADC_rsqx register value */
#define RSQ0_RL(regval)                  (BITS(20,23) & ((uint32_t)(regval) << 20))  /*!< write value to ADC_RSQ0_RL bit field */

/* ADC_isq register value */
#define ISQ_IL(regval)                   (BITS(20,21) & ((uint32_t)(regval) << 20))  /*!< write value to ADC_ISQ_IL bit field */

/* ADC_ovsampctl register value */
/* ADC resolution */
#define CTL0_DRES(regval)                (BITS(24,25) & ((uint32_t)(regval) << 24))  /*!< write value to ADC_CTL0_DRES bit field */
#define ADC_Resolution_12B               CTL0_DRES(0)                                /*!< 12-bit ADC resolution */
#define ADC_Resolution_10B               CTL0_DRES(1)                                /*!< 10-bit ADC resolution */
#define ADC_Resolution_8B                CTL0_DRES(2)                                /*!< 8-bit ADC resolution */
#define ADC_Resolution_6B                CTL0_DRES(3)                                /*!< 6-bit ADC resolution */

/* oversampling shift */
#define OVSAMPCTL_OVSS(regval)           (BITS(5,8) & ((uint32_t)(regval) << 5))     /*!< write value to ADC_OVSAMPCTL_OVSS bit field */
#define ADC_OVERSAMPLING_SHIFT_NONE      OVSAMPCTL_OVSS(0)                           /*!< no oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_1B        OVSAMPCTL_OVSS(1)                           /*!< 1-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_2B        OVSAMPCTL_OVSS(2)                           /*!< 2-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_3B        OVSAMPCTL_OVSS(3)                           /*!< 3-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_4B        OVSAMPCTL_OVSS(4)                           /*!< 4-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_5B        OVSAMPCTL_OVSS(5)                           /*!< 5-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_6B        OVSAMPCTL_OVSS(6)                           /*!< 6-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_7B        OVSAMPCTL_OVSS(7)                           /*!< 7-bit oversampling shift */
#define ADC_OVERSAMPLING_SHIFT_8B        OVSAMPCTL_OVSS(8)                           /*!< 8-bit oversampling shift */

/* oversampling ratio */
#define OVSAMPCTL_OVSR(regval)           (BITS(2,4) & ((uint32_t)(regval) << 2))     /*!< write value to ADC_OVSAMPCTL_OVSR bit field */
#define ADC_OVERSAMPLING_RATIO_MUL2      OVSAMPCTL_OVSR(0)                           /*!< oversampling ratio multiple 2 */
#define ADC_OVERSAMPLING_RATIO_MUL4      OVSAMPCTL_OVSR(1)                           /*!< oversampling ratio multiple 4 */
#define ADC_OVERSAMPLING_RATIO_MUL8      OVSAMPCTL_OVSR(2)                           /*!< oversampling ratio multiple 8 */
#define ADC_OVERSAMPLING_RATIO_MUL16     OVSAMPCTL_OVSR(3)                           /*!< oversampling ratio multiple 16 */
#define ADC_OVERSAMPLING_RATIO_MUL32     OVSAMPCTL_OVSR(4)                           /*!< oversampling ratio multiple 32 */
#define ADC_OVERSAMPLING_RATIO_MUL64     OVSAMPCTL_OVSR(5)                           /*!< oversampling ratio multiple 64 */
#define ADC_OVERSAMPLING_RATIO_MUL128    OVSAMPCTL_OVSR(6)                           /*!< oversampling ratio multiple 128 */
#define ADC_OVERSAMPLING_RATIO_MUL256    OVSAMPCTL_OVSR(7)                           /*!< oversampling ratio multiple 256 */

/* triggered Oversampling */
#define ADC_OVERSAMPLING_ALL_CONVERT     ((uint32_t)0x00000000U)                     /*!< all oversampled conversions for a channel are done consecutively after a trigger */
#define ADC_OVERSAMPLING_ONE_CONVERT     ADC_OVSAMPCTL_TOVS                          /*!< each oversampled conversion for a channel needs a trigger */

/* ADC channel group definitions */
#define ADC_Regular_CHANNEL              ((uint8_t)0x01U)                            /*!< adc regular channel group */
#define ADC_Inserted_CHANNEL             ((uint8_t)0x02U)                            /*!< adc inserted channel group */
#define ADC_Regular_Inserted_CHANNEL     ((uint8_t)0x03U)                            /*!< both regular and inserted channel group */
#define ADC_Channel_DISCON_DISABLE       ((uint8_t)0x04U)                            /*!< disable discontinuous mode of regular & inserted channel */

/* ADC inserted channel definitions */
#define ADC_Inserted_Channel_0          ((uint8_t)0x00U)                  /*!< adc inserted channel 0 */
#define ADC_Inserted_Channel_1          ((uint8_t)0x01U)                  /*!< adc inserted channel 1 */
#define ADC_Inserted_Channel_2          ((uint8_t)0x02U)                  /*!< adc inserted channel 2 */
#define ADC_Inserted_Channel_3          ((uint8_t)0x03U)                  /*!< adc inserted channel 3 */

/* ADC channel definitions */
#define ADC_Channel_0                   ((uint8_t)0x00U)                  /*!< ADC channel 0 */
#define ADC_Channel_1                   ((uint8_t)0x01U)                  /*!< ADC channel 1 */
#define ADC_Channel_2                   ((uint8_t)0x02U)                  /*!< ADC channel 2 */
#define ADC_Channel_3                   ((uint8_t)0x03U)                  /*!< ADC channel 3 */
#define ADC_Channel_4                   ((uint8_t)0x04U)                  /*!< ADC channel 4 */
#define ADC_Channel_5                   ((uint8_t)0x05U)                  /*!< ADC channel 5 */
#define ADC_Channel_6                   ((uint8_t)0x06U)                  /*!< ADC channel 6 */
#define ADC_Channel_7                   ((uint8_t)0x07U)                  /*!< ADC channel 7 */
#define ADC_Channel_8                   ((uint8_t)0x08U)                  /*!< ADC channel 8 */
#define ADC_Channel_9                   ((uint8_t)0x09U)                  /*!< ADC channel 9 */
#define ADC_Channel_10                  ((uint8_t)0x0AU)                  /*!< ADC channel 10 */
#define ADC_Channel_11                  ((uint8_t)0x0BU)                  /*!< ADC channel 11 */
#define ADC_Channel_12                  ((uint8_t)0x0CU)                  /*!< ADC channel 12 */
#define ADC_Channel_13                  ((uint8_t)0x0DU)                  /*!< ADC channel 13 */
#define ADC_Channel_14                  ((uint8_t)0x0EU)                  /*!< ADC channel 14 */
#define ADC_Channel_15                  ((uint8_t)0x0FU)                  /*!< ADC channel 15 */
#define ADC_Channel_16                  ((uint8_t)0x10U)                  /*!< ADC channel 16 */
#define ADC_Channel_17                  ((uint8_t)0x11U)                  /*!< ADC channel 17 */
#define ADC_Channel_18                  ((uint8_t)0x12U)                  /*!< ADC channel 18 */

/* ADC interrupt flag */
#define ADC_INT_WDE                     ADC_CTL0_WDEIE                    /*!< analog watchdog event 中断 */
#define ADC_INT_EOC                     ADC_CTL0_EOCIE                    /*!< end of group conversion 中断 */
#define ADC_INT_EOIC                    ADC_CTL0_EOICIE                   /*!< end of inserted group conversion 中断 */
#define ADC_INT_ROVF                    ADC_CTL0_ROVFIE                   /*!< regular data register overflow */

/* ADC interrupt flag */
#define ADC_INT_Flag_WDE                ADC_STAT_WDE                      /*!< analog watchdog event 中断 */
#define ADC_INT_Flag_EOC                ADC_STAT_EOC                      /*!< end of group conversion 中断 */
#define ADC_INT_Flag_EOIC               ADC_STAT_EOIC                     /*!< end of inserted group conversion 中断 */
#define ADC_INT_Flag_ROVF               ADC_STAT_ROVF                     /*!< regular data register overflow */

/* 为所有 ADCs 配置 ADC 时钟 */
#define SYNCCTL_ADCCK(regval)           (BITS(16,18) & ((uint32_t)(regval) << 16))
#define ADC_ADCCK_PCLK2_DIV2            SYNCCTL_ADCCK(0)                 /*!< PCLK2 div2 */
#define ADC_ADCCK_PCLK2_DIV4            SYNCCTL_ADCCK(1)                 /*!< PCLK2 div4 */
#define ADC_ADCCK_PCLK2_DIV6            SYNCCTL_ADCCK(2)                 /*!< PCLK2 div6 */
#define ADC_ADCCK_PCLK2_DIV8            SYNCCTL_ADCCK(3)                 /*!< PCLK2 div8 */
#define ADC_ADCCK_HCLK_DIV5             SYNCCTL_ADCCK(4)                 /*!< HCLK div5 */
#define ADC_ADCCK_HCLK_DIV6             SYNCCTL_ADCCK(5)                 /*!< HCLK div6 */
#define ADC_ADCCK_HCLK_DIV10            SYNCCTL_ADCCK(6)                 /*!< HCLK div10 */
#define ADC_ADCCK_HCLK_DIV20            SYNCCTL_ADCCK(7)                 /*!< HCLK div20 */

/* ADC synchronization delay */
#define ADC_Sync_Delay_5CYCLE                               ((uint32_t)0x00000000U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 5 ADC clock cycles. */
#define ADC_Sync_Delay_6CYCLE                               ((uint32_t)0x00000100U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 6 ADC clock cycles. */
#define ADC_Sync_Delay_7CYCLE                               ((uint32_t)0x00000200U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 7 ADC clock cycles. */
#define ADC_Sync_Delay_8CYCLE                               ((uint32_t)0x00000300U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 8 ADC clock cycles. */
#define ADC_Sync_Delay_9CYCLE                               ((uint32_t)0x00000400U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 9 ADC clock cycles. */
#define ADC_Sync_Delay_10CYCLE                              ((uint32_t)0x00000500U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 10 ADC clock cycles. */
#define ADC_Sync_Delay_11CYCLE                              ((uint32_t)0x00000600U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 11 ADC clock cycles. */
#define ADC_Sync_Delay_12CYCLE                              ((uint32_t)0x00000700U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 12 ADC clock cycles. */
#define ADC_Sync_Delay_13CYCLE                              ((uint32_t)0x00000800U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 13 ADC clock cycles. */
#define ADC_Sync_Delay_14CYCLE                              ((uint32_t)0x00000900U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 14 ADC clock cycles. */
#define ADC_Sync_Delay_15CYCLE                              ((uint32_t)0x00000A00U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 15 ADC clock cycles. */
#define ADC_Sync_Delay_16CYCLE                              ((uint32_t)0x00000B00U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 16 ADC clock cycles. */
#define ADC_Sync_Delay_17CYCLE                              ((uint32_t)0x00000C00U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 17 ADC clock cycles. */
#define ADC_Sync_Delay_18CYCLE                              ((uint32_t)0x00000D00U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 18 ADC clock cycles. */
#define ADC_Sync_Delay_19CYCLE                              ((uint32_t)0x00000E00U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 19 ADC clock cycles. */
#define ADC_Sync_Delay_20CYCLE                              ((uint32_t)0x00000F00U)    /*!< the delay between 2 sampling phases in ADC synchronization modes to 20 ADC clock cycles. */

/* ADC synchronization DMA mode selection */
#define ADC_Sync_DMA_DISABLE                                ((uint32_t)0x00000000U)    /*!< ADC synchronization DMA disabled */
#define ADC_Sync_DMA_MODE0                                  ((uint32_t)0x00004000U)    /*!< ADC synchronization DMA mode 0 */
#define ADC_Sync_DMA_MODE1                                  ((uint32_t)0x00008000U)    /*!< ADC synchronization DMA mode 1 */

/* end of conversion mode */
#define ADC_EOC_SET_SEQUENCE                                ((uint8_t)0x00U)           /*!< only at the end of a sequence of regular conversions, the EOC bit is set */
#define ADC_EOC_SET_CONVERSION                              ((uint8_t)0x01U)           /*!< at the end of each regular conversion, the EOC bit is set */

/* function declarations */
/* initialization config */
/* reset ADC */
void ADC_DeInit(void);
/* 为所有 ADCs 配置 ADC 时钟 */
void ADC_Clock_Config(uint32_t prescaler);
/* 启用或禁用 ADC 特殊函数 */
void ADC_Special_Function_Config(uint32_t ADC_periph, uint32_t function, ControlStatus newvalue);
/* configure ADC data alignment */
void ADC_Data_Alignment_Config(uint32_t ADC_periph, uint32_t data_alignment);
/* enable ADC interface */
void ADC_Enable(uint32_t ADC_periph);
/* disable ADC interface */
void ADC_Disable(uint32_t ADC_periph);
/* ADC calibration and reset calibration */
void ADC_Calibration_Enable(uint32_t ADC_periph);
/* configure temperature sensor and internal reference voltage channel or VBAT channel function */
void ADC_Channel_16_to_18(uint32_t function, ControlStatus newvalue);
/* configure ADC resolution */
void ADC_Resolution_Config(uint32_t ADC_periph, uint32_t resolution);
/* configure ADC oversample mode */
void ADC_OverSample_Mode_Config(uint32_t ADC_periph, uint32_t mode, uint16_t shift, uint8_t ratio);
/* enable ADC oversample mode */
void ADC_OverSample_Mode_Enable(uint32_t ADC_periph);
/* disable ADC oversample mode */
void ADC_OverSample_Mode_Disable(uint32_t ADC_periph);

/* DMA config */
/* enable DMA request */
void ADC_DMA_Mode_Enable(uint32_t ADC_periph);
/* disable DMA request */
void ADC_DMA_Mode_Disable(uint32_t ADC_periph);
/* when DMA=1, the DMA engine issues a request at end of each regular conversion */
void ADC_DMA_Request_After_Last_Enable(uint32_t ADC_periph);
/* the DMA engine is disabled after the end of transfer signal from DMA controller is detected */
void ADC_DMA_Request_After_Last_Disable(uint32_t ADC_periph);

/* regular group and inserted group config */
/* configure ADC discontinuous mode */
void ADC_Discontinuous_Mode_Config(uint32_t ADC_periph, uint8_t ADC_Channel_group, uint8_t length);
/* configure the length of regular channel group or inserted channel group */
void ADC_Channel_Length_Config(uint32_t ADC_periph, uint8_t ADC_Channel_group, uint32_t length);
/* configure ADC regular channel */
void ADC_Regular_Channel_Config(uint32_t ADC_periph, uint8_t rank, uint8_t ADC_channel, uint32_t sample_time);
/* configure ADC inserted channel */
void ADC_Inserted_Channel_Config(uint32_t ADC_periph, uint8_t rank, uint8_t ADC_channel, uint32_t sample_time);
/* configure ADC inserted channel offset */
void ADC_Inserted_Channel_Offset_Config(uint32_t ADC_periph, uint8_t inserted_channel, uint16_t offset);
/* configure ADC external trigger source */
void ADC_External_Trigger_Source_Config(uint32_t ADC_periph, uint8_t ADC_Channel_group, uint32_t external_Trigger_source);
/* enable ADC external trigger */
void ADC_External_Trigger_Config(uint32_t ADC_periph, uint8_t ADC_Channel_group, uint32_t trigger_mode);
/* enable ADC software trigger */
void ADC_Software_Trigger_Enable(uint32_t ADC_periph, uint8_t ADC_Channel_group);
/* configure end of conversion mode */
void ADC_End_Of_Conversion_Config(uint32_t ADC_periph, uint8_t end_selection);

/* get channel data */
/* read ADC regular group data register */
uint16_t ADC_Regular_Data_Read(uint32_t ADC_periph);
/* read ADC inserted group data register */
uint16_t ADC_Inserted_Data_Read(uint32_t ADC_periph, uint8_t inserted_channel);

/* watchdog config */
/* disable ADC analog watchdog single channel */
void ADC_WatchDog_Single_Channel_Disable(uint32_t ADC_periph );
/* enable ADC analog watchdog single channel */
void ADC_WatchDog_Single_Channel_Enable(uint32_t ADC_periph, uint8_t ADC_channel);
/* configure ADC analog watchdog group channel */
void ADC_WatchDog_Group_Channel_Enable(uint32_t ADC_periph, uint8_t ADC_Channel_group);
/* disable ADC analog watchdog */
void ADC_WatchDog_Disable(uint32_t ADC_periph, uint8_t ADC_Channel_group);
/* configure ADC analog watchdog threshold */
void ADC_WatchDog_Threshold_Config(uint32_t ADC_periph, uint16_t low_threshold, uint16_t high_threshold);

/* interrupt & flag functions */
/* get the ADC flag bits */
FlagStatus ADC_Flag_Get(uint32_t ADC_periph, uint32_t ADC_flag);
/* clear the ADC flag bits */
void ADC_Flag_Clear(uint32_t ADC_periph, uint32_t ADC_flag);
/* get the bit state of ADCx software start conversion */
FlagStatus ADC_Regular_Software_Startconv_Flag_Get(uint32_t ADC_periph);
/* get the bit state of ADCx software inserted channel start conversion */
FlagStatus ADC_Inserted_Software_Startconv_Flag_Get(uint32_t ADC_periph);
/* get the ADC interrupt bits */
FlagStatus ADC_Interrupt_Flag_Get(uint32_t ADC_periph, uint32_t ADC_interrupt);
/* clear the ADC flag */
void ADC_Interrupt_Flag_Clear(uint32_t ADC_periph, uint32_t ADC_interrupt);
/* enable ADC 中断 */
void ADC_Interrupt_Enable(uint32_t ADC_periph, uint32_t ADC_interrupt);
/* disable ADC 中断 */
void ADC_Interrupt_Disable(uint32_t ADC_periph, uint32_t ADC_interrupt);

/* ADC synchronization */
/* configure the ADC sync mode */
void ADC_Sync_Mode_Config(uint32_t sync_mode);
/* configure the delay between 2 sampling phases in ADC sync modes */
void ADC_Sync_Delay_Config(uint32_t sample_delay);
/* configure ADC sync DMA mode selection */
void ADC_Sync_DMA_Config(uint32_t DMA_mode );
/* configure ADC sync DMA engine is disabled after the end of transfer signal from DMA controller is detected */
void ADC_Sync_DMA_Request_After_Last_Enable(void);
/* configure ADC sync DMA engine issues requests 根据 the SYNCDMA bits */
void ADC_Sync_DMA_Request_After_Last_Disable(void);
/* read ADC sync regular data register */
uint32_t ADC_Sync_Regular_Data_Read(void);

#endif /* GD32F4XX_ADC_H */
