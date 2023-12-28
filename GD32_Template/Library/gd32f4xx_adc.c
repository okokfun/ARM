/*!
    文件:    gd32f4xx_adc.c
    简介:   ADC driver

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

#include "gd32f4xx_adc.h"

#define REGULAR_Trigger_MODE                        ((uint32_t)28U)
#define INSERTED_Trigger_MODE                       ((uint32_t)20U)
/* discontinuous mode macro*/
#define  ADC_Channel_Length_SUBTRACT_ONE            ((uint8_t)1U)

/* ADC regular channel macro */
#define  ADC_Regular_Channel_RANK_SIX               ((uint8_t)6U)
#define  ADC_Regular_Channel_RANK_TWELVE            ((uint8_t)12U)
#define  ADC_Regular_Channel_RANK_SIXTEEN           ((uint8_t)16U)
#define  ADC_Regular_Channel_RANK_LENGTH            ((uint8_t)5U)

/* ADC sampling time macro */
#define  ADC_Channel_Sample_TEN                     ((uint8_t)10U)
#define  ADC_Channel_Sample_EIGHTEEN                ((uint8_t)18U)
#define  ADC_Channel_Sample_LENGTH                  ((uint8_t)3U)

/* ADC inserted channel macro */
#define  ADC_Inserted_Channel_RANK_LENGTH           ((uint8_t)5U)
#define  ADC_Inserted_Channel_SHIFT_LENGTH          ((uint8_t)15U)

/* ADC inserted channel offset macro */
#define  ADC_Offset_LENGTH                          ((uint8_t)3U)
#define  ADC_Offset_SHIFT_LENGTH                    ((uint8_t)4U)

/*!
    简介:    reset ADC
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ADC_DeInit(void) {
    RCU_Periph_Reset_Enable(RCU_ADCRST);
    RCU_Periph_Reset_Disable(RCU_ADCRST);
}

/*!
    简介:        为所有 ADCs 配置 ADC 时钟
    参数[输入]:    prescaler: configure ADCs prescaler ratio
                  only one parameter can be selected which is shown as below:
      参数:        ADC_ADCCK_PCLK2_DIV2: PCLK2 div2
      参数:        ADC_ADCCK_PCLK2_DIV4: PCLK2 div4
      参数:        ADC_ADCCK_PCLK2_DIV6: PCLK2 div6
      参数:        ADC_ADCCK_PCLK2_DIV8: PCLK2 div8
      参数:        ADC_ADCCK_HCLK_DIV5: HCLK div5
      参数:        ADC_ADCCK_HCLK_DIV6: HCLK div6
      参数:        ADC_ADCCK_HCLK_DIV10: HCLK div10
      参数:        ADC_ADCCK_HCLK_DIV20: HCLK div20
    参数[输出]:   无
    返回值:       无
*/
void ADC_Clock_Config(uint32_t prescaler) {
    ADC_SYNCCTL &= ~((uint32_t)ADC_SYNCCTL_ADCCK);
    ADC_SYNCCTL |= (uint32_t) prescaler;
}

/*!
    简介:        启用或禁用 ADC 特殊函数
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输入]:    function: the function to config
                  only one parameter can be selected which is shown as below:
    参数:          ADC_SCAN_MODE: scan mode select
    参数:          ADC_Inserted_Channel_AUTO: inserted channel group convert automatically
    参数:          ADC_CONTINUOUS_MODE: continuous mode select
    参数[输入]:    newvalue: ENABLE or DISABLE
    参数[输出]:   无
    返回值:       无
*/
void ADC_Special_Function_Config(uint32_t ADC_periph, uint32_t function, ControlStatus newvalue) {
    if(newvalue) {
        if(0U != (function & ADC_SCAN_MODE)) {
            /* enable scan mode */
            ADC_CTL0(ADC_periph) |= ADC_SCAN_MODE;
        }

        if(0U != (function & ADC_Inserted_Channel_AUTO)) {
            /* enable inserted channel group convert automatically */
            ADC_CTL0(ADC_periph) |= ADC_Inserted_Channel_AUTO;
        }

        if(0U != (function & ADC_CONTINUOUS_MODE)) {
            /* enable continuous mode */
            ADC_CTL1(ADC_periph) |= ADC_CONTINUOUS_MODE;
        }
    } else {
        if(0U != (function & ADC_SCAN_MODE)) {
            /* disable scan mode */
            ADC_CTL0(ADC_periph) &= ~ADC_SCAN_MODE;
        }

        if(0U != (function & ADC_Inserted_Channel_AUTO)) {
            /* disable inserted channel group convert automatically */
            ADC_CTL0(ADC_periph) &= ~ADC_Inserted_Channel_AUTO;
        }

        if(0U != (function & ADC_CONTINUOUS_MODE)) {
            /* disable continuous mode */
            ADC_CTL1(ADC_periph) &= ~ADC_CONTINUOUS_MODE;
        }
    }
}

/*!
    简介:        configure ADC data alignment
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输入]:    data_alignment: data alignment select
                  only one parameter can be selected which is shown as below:
    参数:          ADC_DATAALIGN_RIGHT: LSB alignment
    参数:          ADC_DATAALIGN_LEFT: MSB alignment
    参数[输出]:   无
    返回值:       无
*/
void ADC_Data_Alignment_Config(uint32_t ADC_periph, uint32_t data_alignment) {
    if(ADC_DATAALIGN_RIGHT != data_alignment) {
        /* MSB alignment */
        ADC_CTL1(ADC_periph) |= ADC_CTL1_DAL;
    } else {
        /* LSB alignment */
        ADC_CTL1(ADC_periph) &= ~((uint32_t)ADC_CTL1_DAL);
    }
}

/*!
    简介:        enable ADC interface
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输出]:   无
    返回值:       无
*/
void ADC_Enable(uint32_t ADC_periph) {
    if(RESET == (ADC_CTL1(ADC_periph) & ADC_CTL1_ADCON)) {
        /* enable ADC */
        ADC_CTL1(ADC_periph) |= (uint32_t)ADC_CTL1_ADCON;
    }
}

/*!
    简介:        disable ADC interface
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输出]:   无
    返回值:       无
*/
void ADC_Disable(uint32_t ADC_periph) {
    /* disable ADC */
    ADC_CTL1(ADC_periph) &= ~((uint32_t)ADC_CTL1_ADCON);
}

/*!
    简介:        ADC calibration and reset calibration
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输出]:   无
    返回值:       无
*/
void ADC_Calibration_Enable(uint32_t ADC_periph) {
    /* reset the selected ADC calibration registers */
    ADC_CTL1(ADC_periph) |= (uint32_t) ADC_CTL1_RSTCLB;

    /* check the RSTCLB bit state */
    while(RESET != (ADC_CTL1(ADC_periph) & ADC_CTL1_RSTCLB)) {
    }

    /* enable ADC calibration process */
    ADC_CTL1(ADC_periph) |= ADC_CTL1_CLB;

    /* check the CLB bit state */
    while(RESET != (ADC_CTL1(ADC_periph) & ADC_CTL1_CLB)) {
    }
}

/*!
    简介:        configure temperature sensor and internal reference voltage channel or VBAT channel function
    参数[输入]:    function: temperature sensor and internal reference voltage channel or VBAT channel
                  only one parameter can be selected which is shown as below:
    参数:          ADC_VBAT_Channel_SWITCH: channel 18 (1/4 voltate of external battery) switch of ADC0
    参数:          ADC_TEMP_VREF_Channel_SWITCH: channel 16 (temperature sensor) and 17 (internal reference voltage) switch of ADC0
    参数[输入]:    newvalue: ENABLE or DISABLE
    参数[输出]:   无
    返回值:       无
*/
void ADC_Channel_16_to_18(uint32_t function, ControlStatus newvalue) {
    if(newvalue) {
        if(RESET != (function & ADC_VBAT_Channel_SWITCH)) {
            /* enable ADC0 Vbat channel */
            ADC_SYNCCTL |= ADC_VBAT_Channel_SWITCH;
        }

        if(RESET != (function & ADC_TEMP_VREF_Channel_SWITCH)) {
            /* enable ADC0 Vref and Temperature channel */
            ADC_SYNCCTL |= ADC_TEMP_VREF_Channel_SWITCH;
        }
    } else {
        if(RESET != (function & ADC_VBAT_Channel_SWITCH)) {
            /* disable ADC0 Vbat channel  */
            ADC_SYNCCTL &= ~ADC_VBAT_Channel_SWITCH;
        }

        if(RESET != (function & ADC_TEMP_VREF_Channel_SWITCH)) {
            /* disable ADC0 Vref and Temperature channel */
            ADC_SYNCCTL &= ~ADC_TEMP_VREF_Channel_SWITCH;
        }
    }
}

/*!
    简介:        configure ADC resolution
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输入]:    resolution: ADC resolution
                  only one parameter can be selected which is shown as below:
    参数:          ADC_Resolution_12B: 12-bit ADC resolution
    参数:          ADC_Resolution_10B: 10-bit ADC resolution
    参数:          ADC_Resolution_8B: 8-bit ADC resolution
    参数:          ADC_Resolution_6B: 6-bit ADC resolution
    参数[输出]:   无
    返回值:       无
*/
void ADC_Resolution_Config(uint32_t ADC_periph, uint32_t resolution) {
    ADC_CTL0(ADC_periph) &= ~((uint32_t)ADC_CTL0_DRES);
    ADC_CTL0(ADC_periph) |= (uint32_t)resolution;
}

/*!
    简介:        configure ADC oversample mode
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输入]:    mode: ADC oversampling mode
                  only one parameter can be selected which is shown as below:
    参数:          ADC_OVERSAMPLING_ALL_CONVERT: all oversampled conversions for a channel are done consecutively after a trigger
    参数:          ADC_OVERSAMPLING_ONE_CONVERT: each oversampled conversion for a channel needs a trigger
    参数[输入]:    shift: ADC oversampling shift
                  only one parameter can be selected which is shown as below:
    参数:          ADC_OVERSAMPLING_SHIFT_NONE: no oversampling shift
    参数:          ADC_OVERSAMPLING_SHIFT_1B: 1-bit oversampling shift
    参数:          ADC_OVERSAMPLING_SHIFT_2B: 2-bit oversampling shift
    参数:          ADC_OVERSAMPLING_SHIFT_3B: 3-bit oversampling shift
    参数:          ADC_OVERSAMPLING_SHIFT_4B: 3-bit oversampling shift
    参数:          ADC_OVERSAMPLING_SHIFT_5B: 5-bit oversampling shift
    参数:          ADC_OVERSAMPLING_SHIFT_6B: 6-bit oversampling shift
    参数:          ADC_OVERSAMPLING_SHIFT_7B: 7-bit oversampling shift
    参数:          ADC_OVERSAMPLING_SHIFT_8B: 8-bit oversampling shift
    参数[输入]:    ratio: ADC oversampling ratio
                  only one parameter can be selected which is shown as below:
    参数:          ADC_OVERSAMPLING_RATIO_MUL2: oversampling ratio multiple 2
    参数:          ADC_OVERSAMPLING_RATIO_MUL4: oversampling ratio multiple 4
    参数:          ADC_OVERSAMPLING_RATIO_MUL8: oversampling ratio multiple 8
    参数:          ADC_OVERSAMPLING_RATIO_MUL16: oversampling ratio multiple 16
    参数:          ADC_OVERSAMPLING_RATIO_MUL32: oversampling ratio multiple 32
    参数:          ADC_OVERSAMPLING_RATIO_MUL64: oversampling ratio multiple 64
    参数:          ADC_OVERSAMPLING_RATIO_MUL128: oversampling ratio multiple 128
    参数:          ADC_OVERSAMPLING_RATIO_MUL256: oversampling ratio multiple 256
    参数[输出]:   无
    返回值:       无
*/
void ADC_OverSample_Mode_Config(uint32_t ADC_periph, uint32_t mode, uint16_t shift, uint8_t ratio) {
    if(ADC_OVERSAMPLING_ONE_CONVERT == mode) {
        ADC_OVSAMPCTL(ADC_periph) |= (uint32_t)ADC_OVSAMPCTL_TOVS;
    } else {
        ADC_OVSAMPCTL(ADC_periph) &= ~((uint32_t)ADC_OVSAMPCTL_TOVS);
    }

    /* config the shift and ratio */
    ADC_OVSAMPCTL(ADC_periph) &= ~((uint32_t)(ADC_OVSAMPCTL_OVSR | ADC_OVSAMPCTL_OVSS));
    ADC_OVSAMPCTL(ADC_periph) |= ((uint32_t)shift | (uint32_t)ratio);
}

/*!
    简介:        enable ADC oversample mode
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输出]:   无
    返回值:       无
*/
void ADC_OverSample_Mode_Enable(uint32_t ADC_periph) {
    ADC_OVSAMPCTL(ADC_periph) |= ADC_OVSAMPCTL_OVSEN;
}

/*!
    简介:        disable ADC oversample mode
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输出]:   无
    返回值:       无
*/
void ADC_OverSample_Mode_Disable(uint32_t ADC_periph) {
    ADC_OVSAMPCTL(ADC_periph) &= ~((uint32_t)ADC_OVSAMPCTL_OVSEN);
}

/*!
    简介:        enable DMA request
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输出]:   无
    返回值:       无
*/
void ADC_DMA_Mode_Enable(uint32_t ADC_periph) {
    /* enable DMA request */
    ADC_CTL1(ADC_periph) |= (uint32_t)(ADC_CTL1_DMA);
}

/*!
    简介:      disable DMA request
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输出]:  无
    返回值:      无
*/
void ADC_DMA_Mode_Disable(uint32_t ADC_periph) {
    /* disable DMA request */
    ADC_CTL1(ADC_periph) &= ~((uint32_t)ADC_CTL1_DMA);
}

/*!
    简介:    when DMA=1, the DMA engine issues a request at end of each regular conversion
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输出]:  无
    返回值:      无
*/
void ADC_DMA_Request_After_Last_Enable(uint32_t ADC_periph) {
    ADC_CTL1(ADC_periph) |= (uint32_t)(ADC_CTL1_DDM);
}

/*!
    简介:    the DMA engine is disabled after the end of transfer signal from DMA controller is detected
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输出]:  无
    返回值:      无
*/
void ADC_DMA_Request_After_Last_Disable(uint32_t ADC_periph) {
    ADC_CTL1(ADC_periph) &= ~((uint32_t)ADC_CTL1_DDM);
}

/*!
    简介:        configure ADC discontinuous mode
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输入]:    ADC_Channel_group: select the channel group
                  only one parameter can be selected which is shown as below:
    参数:          ADC_Regular_CHANNEL: regular channel group
    参数:          ADC_Inserted_CHANNEL: inserted channel group
    参数:          ADC_Channel_DISCON_DISABLE: disable discontinuous mode of regular & inserted channel
    参数[输入]:    length: number of conversions in discontinuous mode,the number can be 1..8
                  for regular channel ,the number has no effect for inserted channel
    参数[输出]:   无
    返回值:       无
*/
void ADC_Discontinuous_Mode_Config(uint32_t ADC_periph, uint8_t ADC_Channel_group, uint8_t length) {
    /* disable discontinuous mode of regular & inserted channel */
    ADC_CTL0(ADC_periph) &= ~((uint32_t)(ADC_CTL0_DISRC | ADC_CTL0_DISIC));

    switch(ADC_Channel_group) {
    case ADC_Regular_CHANNEL:
        /* config the number of conversions in discontinuous mode  */
        ADC_CTL0(ADC_periph) &= ~((uint32_t)ADC_CTL0_DISNUM);

        if((length <= 8U) && (length >= 1U)) {
            ADC_CTL0(ADC_periph) |= CTL0_DISNUM(((uint32_t)length - ADC_Channel_Length_SUBTRACT_ONE));
        }

        /* enable regular channel group discontinuous mode */
        ADC_CTL0(ADC_periph) |= (uint32_t)ADC_CTL0_DISRC;
        break;

    case ADC_Inserted_CHANNEL:
        /* enable inserted channel group discontinuous mode */
        ADC_CTL0(ADC_periph) |= (uint32_t)ADC_CTL0_DISIC;
        break;

    case ADC_Channel_DISCON_DISABLE:

    /* disable discontinuous mode of regular & inserted channel */
    default:
        break;
    }
}

/*!
    简介:        configure the length of regular channel group or inserted channel group
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输入]:    ADC_Channel_group: select the channel group
                  only one parameter can be selected which is shown as below:
    参数:          ADC_Regular_CHANNEL: regular channel group
    参数:          ADC_Inserted_CHANNEL: inserted channel group
    参数[输入]:    length: the length of the channel
                  regular channel 1-16
                  inserted channel 1-4
    参数[输出]:   无
    返回值:       无
*/
void ADC_Channel_Length_Config(uint32_t ADC_periph, uint8_t ADC_Channel_group, uint32_t length) {
    switch(ADC_Channel_group) {
    case ADC_Regular_CHANNEL:
        if((length >= 1U) && (length <= 16U)) {
            ADC_RSQ0(ADC_periph) &= ~((uint32_t)ADC_RSQ0_RL);
            ADC_RSQ0(ADC_periph) |= RSQ0_RL((uint32_t)(length - ADC_Channel_Length_SUBTRACT_ONE));
        }

        break;

    case ADC_Inserted_CHANNEL:
        if((length >= 1U) && (length <= 4U)) {
            ADC_ISQ(ADC_periph) &= ~((uint32_t)ADC_ISQ_IL);
            ADC_ISQ(ADC_periph) |= ISQ_IL((uint32_t)(length - ADC_Channel_Length_SUBTRACT_ONE));
        }

        break;

    default:
        break;
    }
}

/*!
    简介:        configure ADC regular channel
    参数[输入]:    ADC_periph: ADCx,x=0,1,2
    参数[输入]:    rank: the regular group sequencer rank,this parameter must be between 0 to 15
    参数[输入]:    ADC_channel: the selected ADC channel
                  only one parameter can be selected which is shown as below:
    参数:          ADC_Channel_x(x=0..18): ADC Channelx
    参数[输入]:    sample_time: the sample time value
                  only one parameter can be selected which is shown as below:
    参数:          ADC_SAMPLETIME_3: 3 cycles
    参数:          ADC_SAMPLETIME_15: 15 cycles
    参数:          ADC_SAMPLETIME_28: 28 cycles
    参数:          ADC_SAMPLETIME_56: 56 cycles
    参数:          ADC_SAMPLETIME_84: 84 cycles
    参数:          ADC_SAMPLETIME_112: 112 cycles
    参数:          ADC_SAMPLETIME_144: 144 cycles
    参数:          ADC_SAMPLETIME_480: 480 cycles
    参数[输出]:   无
    返回值:       无
*/
void ADC_Regular_Channel_Config(uint32_t ADC_periph, uint8_t rank, uint8_t ADC_channel, uint32_t sample_time) {
    uint32_t rsq, sampt;

    /* ADC regular sequence config */
    if(rank < ADC_Regular_Channel_RANK_SIX) {
        /* the regular group sequence rank is smaller than six */
        rsq = ADC_RSQ2(ADC_periph);
        rsq &=  ~((uint32_t)(ADC_RSQX_RSQN << (ADC_Regular_Channel_RANK_LENGTH * rank)));
        /* the channel number is written to these bits to select a channel as the nth conversion in the regular channel group */
        rsq |= ((uint32_t)ADC_channel << (ADC_Regular_Channel_RANK_LENGTH * rank));
        ADC_RSQ2(ADC_periph) = rsq;
    } else if(rank < ADC_Regular_Channel_RANK_TWELVE) {
        /* the regular group sequence rank is smaller than twelve */
        rsq = ADC_RSQ1(ADC_periph);
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (ADC_Regular_Channel_RANK_LENGTH * (rank - ADC_Regular_Channel_RANK_SIX))));
        /* the channel number is written to these bits to select a channel as the nth conversion in the regular channel group */
        rsq |= ((uint32_t)ADC_channel << (ADC_Regular_Channel_RANK_LENGTH * (rank - ADC_Regular_Channel_RANK_SIX)));
        ADC_RSQ1(ADC_periph) = rsq;
    } else if(rank < ADC_Regular_Channel_RANK_SIXTEEN) {
        /* the regular group sequence rank is smaller than sixteen */
        rsq = ADC_RSQ0(ADC_periph);
        rsq &= ~((uint32_t)(ADC_RSQX_RSQN << (ADC_Regular_Channel_RANK_LENGTH * (rank - ADC_Regular_Channel_RANK_TWELVE))));
        /* the channel number is written to these bits to select a channel as the nth conversion in the regular channel group */
        rsq |= ((uint32_t)ADC_channel << (ADC_Regular_Channel_RANK_LENGTH * (rank - ADC_Regular_Channel_RANK_TWELVE)));
        ADC_RSQ0(ADC_periph) = rsq;
    } else {
    }

    /* ADC sampling time config */
    if(ADC_channel < ADC_Channel_Sample_TEN) {
        /* the regular group sequence rank is smaller than ten */
        sampt = ADC_SAMPT1(ADC_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_Channel_Sample_LENGTH * ADC_channel)));
        /* channel sample time set*/
        sampt |= (uint32_t)(sample_time << (ADC_Channel_Sample_LENGTH * ADC_channel));
        ADC_SAMPT1(ADC_periph) = sampt;
    } else if(ADC_channel <= ADC_Channel_Sample_EIGHTEEN) {
        /* the regular group sequence rank is smaller than eighteen */
        sampt = ADC_SAMPT0(ADC_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_Channel_Sample_LENGTH * (ADC_channel - ADC_Channel_Sample_TEN))));
        /* channel sample time set*/
        sampt |= (uint32_t)(sample_time << (ADC_Channel_Sample_LENGTH * (ADC_channel - ADC_Channel_Sample_TEN)));
        ADC_SAMPT0(ADC_periph) = sampt;
    } else {
    }
}

/*!
    简介:    configure ADC inserted channel
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  rank: the inserted group sequencer rank,this parameter must be between 0 to 3
    参数[输入]:  ADC_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
    参数:        ADC_Channel_x(x=0..18): ADC Channelx
    参数[输入]:  sample_time: The sample time value
                only one parameter can be selected which is shown as below:
    参数:        ADC_SAMPLETIME_3: 3 cycles
    参数:        ADC_SAMPLETIME_15: 15 cycles
    参数:        ADC_SAMPLETIME_28: 28 cycles
    参数:        ADC_SAMPLETIME_56: 56 cycles
    参数:        ADC_SAMPLETIME_84: 84 cycles
    参数:        ADC_SAMPLETIME_112: 112 cycles
    参数:        ADC_SAMPLETIME_144: 144 cycles
    参数:        ADC_SAMPLETIME_480: 480 cycles
    参数[输出]:  无
    返回值:      无
*/
void ADC_Inserted_Channel_Config(uint32_t ADC_periph, uint8_t rank, uint8_t ADC_channel, uint32_t sample_time) {
    uint8_t inserted_length;
    uint32_t isq, sampt;

    /* get inserted channel group length */
    inserted_length = (uint8_t)GET_BITS(ADC_ISQ(ADC_periph), 20U, 21U);

    /* the channel number is written to these bits to select a channel as the nth conversion in the inserted channel group */
    if(rank < 4U) {
        isq = ADC_ISQ(ADC_periph);
        isq &= ~((uint32_t)(ADC_ISQ_ISQN << (ADC_Inserted_Channel_SHIFT_LENGTH - (inserted_length - rank) * ADC_Inserted_Channel_RANK_LENGTH)));
        isq |= ((uint32_t)ADC_channel << (ADC_Inserted_Channel_SHIFT_LENGTH - (inserted_length - rank) * ADC_Inserted_Channel_RANK_LENGTH));
        ADC_ISQ(ADC_periph) = isq;
    }

    /* ADC sampling time config */
    if(ADC_channel < ADC_Channel_Sample_TEN) {
        /* the inserted group sequence rank is smaller than ten */
        sampt = ADC_SAMPT1(ADC_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_Channel_Sample_LENGTH * ADC_channel)));
        /* channel sample time set*/
        sampt |= (uint32_t) sample_time << (ADC_Channel_Sample_LENGTH * ADC_channel);
        ADC_SAMPT1(ADC_periph) = sampt;
    } else if(ADC_channel <= ADC_Channel_Sample_EIGHTEEN) {
        /* the inserted group sequence rank is smaller than eighteen */
        sampt = ADC_SAMPT0(ADC_periph);
        sampt &= ~((uint32_t)(ADC_SAMPTX_SPTN << (ADC_Channel_Sample_LENGTH * (ADC_channel - ADC_Channel_Sample_TEN))));
        /* channel sample time set*/
        sampt |= ((uint32_t)sample_time << (ADC_Channel_Sample_LENGTH * (ADC_channel - ADC_Channel_Sample_TEN)));
        ADC_SAMPT0(ADC_periph) = sampt;
    } else {
    }
}

/*!
    简介:      configure ADC inserted channel offset
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  inserted_channel : insert channel select
                only one parameter can be selected which is shown as below:
    参数:        ADC_Inserted_Channel_0: inserted channel0
    参数:        ADC_Inserted_Channel_1: inserted channel1
    参数:        ADC_Inserted_Channel_2: inserted channel2
    参数:        ADC_Inserted_Channel_3: inserted channel3
    参数[输入]:  offset : the offset data
    参数[输出]:  无
    返回值:      无
*/
void ADC_Inserted_Channel_Offset_Config(uint32_t ADC_periph, uint8_t inserted_channel, uint16_t offset) {
    uint8_t inserted_length;
    uint32_t num = 0U;

    inserted_length = (uint8_t)GET_BITS(ADC_ISQ(ADC_periph), 20U, 21U);
    num = ((uint32_t)ADC_Offset_LENGTH - ((uint32_t)inserted_length - (uint32_t)inserted_channel));

    if(num <= ADC_Offset_LENGTH) {
        /* calculate the offset of the register */
        num = num * ADC_Offset_SHIFT_LENGTH;
        /* config the offset of the selected channels */
        REG32((ADC_periph) + 0x14U + num) = IOFFX_IOFF((uint32_t)offset);
    }
}

/*!
    简介:      configure ADC external trigger source
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_Channel_group: select the channel group
                only one parameter can be selected which is shown as below:
    参数:        ADC_Regular_CHANNEL: regular channel group
    参数:        ADC_Inserted_CHANNEL: inserted channel group
    参数[输入]:  external_Trigger_source: regular or inserted group trigger source
                for regular channel:
                only one parameter can be selected which is shown as below:
    参数:        ADC_EXTTRIG_Regular_T0_CH0: external trigger timer 0 CC0 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T0_CH1: external trigger timer 0 CC1 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T0_CH2: external trigger timer 0 CC2 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T1_CH1: external trigger timer 1 CC1 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T1_CH2: external trigger timer 1 CC2 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T1_CH3: external trigger timer 1 CC3 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T1_TRGO: external trigger timer 1 TRGO event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T2_CH0 : external trigger timer 2 CC0 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T2_TRGO : external trigger timer 2 TRGO event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T3_CH3: external trigger timer 3 CC3 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T4_CH0: external trigger timer 4 CC0 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T4_CH1: external trigger timer 4 CC1 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T4_CH2: external trigger timer 4 CC2 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T7_CH0: external trigger timer 7 CC0 event select for regular channel
    参数:        ADC_EXTTRIG_Regular_T7_TRGO: external trigger timer 7 TRGO event select for regular channel
    参数:        ADC_EXTTRIG_Regular_EXTI_11: external trigger extiline 11 select for regular channel
                for inserted channel:
                only one parameter can be selected which is shown as below:
    参数:        ADC_EXTTRIG_Inserted_T0_CH3: timer0 capture compare 3
    参数:        ADC_EXTTRIG_Inserted_T0_TRGO: timer0 TRGO event
    参数:        ADC_EXTTRIG_Inserted_T1_CH0: timer1 capture compare 0
    参数:        ADC_EXTTRIG_Inserted_T1_TRGO: timer1 TRGO event
    参数:        ADC_EXTTRIG_Inserted_T2_CH1: timer2 capture compare 1
    参数:        ADC_EXTTRIG_Inserted_T2_CH3: timer2 capture compare 3
    参数:        ADC_EXTTRIG_Inserted_T3_CH0: timer3 capture compare 0
    参数:        ADC_EXTTRIG_Inserted_T3_CH1: timer3 capture compare 1
    参数:        ADC_EXTTRIG_Inserted_T3_CH2: timer3 capture compare 2
    参数:        ADC_EXTTRIG_Inserted_T3_TRGO: timer3 capture compare TRGO
    参数:        ADC_EXTTRIG_Inserted_T4_CH3: timer4 capture compare 3
    参数:        ADC_EXTTRIG_Inserted_T4_TRGO: timer4 capture compare TRGO
    参数:        ADC_EXTTRIG_Inserted_T7_CH1: timer7 capture compare 1
    参数:        ADC_EXTTRIG_Inserted_T7_CH2: timer7 capture compare 2
    参数:        ADC_EXTTRIG_Inserted_T7_CH3: timer7 capture compare 3
    参数:        ADC_EXTTRIG_Inserted_EXTI_15: external interrupt line 15
    参数[输出]:  无
    返回值:      无
*/
void ADC_External_Trigger_Source_Config(uint32_t ADC_periph, uint8_t ADC_Channel_group, uint32_t external_Trigger_source) {
    switch(ADC_Channel_group) {
    case ADC_Regular_CHANNEL:
        /* configure ADC regular group external trigger source */
        ADC_CTL1(ADC_periph) &= ~((uint32_t)ADC_CTL1_ETSRC);
        ADC_CTL1(ADC_periph) |= (uint32_t)external_Trigger_source;
        break;

    case ADC_Inserted_CHANNEL:
        /* configure ADC inserted group external trigger source */
        ADC_CTL1(ADC_periph) &= ~((uint32_t)ADC_CTL1_ETSIC);
        ADC_CTL1(ADC_periph) |= (uint32_t)external_Trigger_source;
        break;

    default:
        break;
    }
}

/*!
    简介:      enable ADC external trigger
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_Channel_group: select the channel group
                only one parameter can be selected which is shown as below:
    参数:        ADC_Regular_CHANNEL: regular channel group
    参数:        ADC_Inserted_CHANNEL: inserted channel group
    参数[输入]:  trigger_mode: external trigger mode
                only one parameter can be selected which is shown as below:
    参数:        EXTERNAL_Trigger_DISABLE: external trigger disable
    参数:        EXTERNAL_Trigger_RISING: rising edge of external trigger
    参数:        EXTERNAL_Trigger_FALLING: falling edge of external trigger
    参数:        EXTERNAL_Trigger_RISING_FALLING: rising and falling edge of external trigger
    参数[输出]:  无
    返回值:      无
*/
void ADC_External_Trigger_Config(uint32_t ADC_periph, uint8_t ADC_Channel_group, uint32_t trigger_mode) {
    switch(ADC_Channel_group) {
    case ADC_Regular_CHANNEL:
        /* configure ADC regular channel group external trigger mode */
        ADC_CTL1(ADC_periph) &= ~((uint32_t)ADC_CTL1_ETMRC);
        ADC_CTL1(ADC_periph) |= (uint32_t)(trigger_mode << REGULAR_Trigger_MODE);
        break;

    case ADC_Inserted_CHANNEL:
        /* configure ADC inserted channel group external trigger mode */
        ADC_CTL1(ADC_periph) &=  ~((uint32_t)ADC_CTL1_ETMIC);
        ADC_CTL1(ADC_periph) |= (uint32_t)(trigger_mode << INSERTED_Trigger_MODE);
        break;

    default:
        break;
    }
}

/*!
    简介:      enable ADC software trigger
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_Channel_group: select the channel group
                only one parameter can be selected which is shown as below:
    参数:        ADC_Regular_CHANNEL: regular channel group
    参数:        ADC_Inserted_CHANNEL: inserted channel group
    参数[输出]:  无
    返回值:      无
*/
void ADC_Software_Trigger_Enable(uint32_t ADC_periph, uint8_t ADC_Channel_group) {
    switch(ADC_Channel_group) {
    case ADC_Regular_CHANNEL:
        /* enable ADC regular channel group software trigger */
        ADC_CTL1(ADC_periph) |= (uint32_t)ADC_CTL1_SWRCST;
        break;

    case ADC_Inserted_CHANNEL:
        /* enable ADC inserted channel group software trigger */
        ADC_CTL1(ADC_periph) |= (uint32_t)ADC_CTL1_SWICST;
        break;

    default:
        break;
    }
}

/*!
    简介:      configure end of conversion mode
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  end_selection: end of conversion mode
                only one parameter can be selected which is shown as below:
    参数:        ADC_EOC_SET_SEQUENCE: only at the end of a sequence of regular conversions, the EOC bit is set.Overflow detection is disabled unless DMA=1.
    参数:        ADC_EOC_SET_CONVERSION: at the end of each regular conversion, the EOC bit is set.Overflow is detected automatically.
    参数[输出]:  无
    返回值:      无
*/
void ADC_End_Of_Conversion_Config(uint32_t ADC_periph, uint8_t end_selection) {
    switch(end_selection) {
    case ADC_EOC_SET_SEQUENCE:
        /* only at the end of a sequence of regular conversions, the EOC bit is set */
        ADC_CTL1(ADC_periph) &= ~((uint32_t)ADC_CTL1_EOCM);
        break;

    case ADC_EOC_SET_CONVERSION:
        /* at the end of each regular conversion, the EOC bit is set.Overflow is detected automatically */
        ADC_CTL1(ADC_periph) |= (uint32_t)(ADC_CTL1_EOCM);
        break;

    default:
        break;
    }
}

/*!
    简介:      read ADC regular group data register
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  无
    参数[输出]:  无
    返回值:     the conversion value
*/
uint16_t ADC_Regular_Data_Read(uint32_t ADC_periph) {
    return (uint16_t)(ADC_RDATA(ADC_periph));
}

/*!
    简介:      read ADC inserted group data register
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  inserted_channel : insert channel select
                only one parameter can be selected which is shown as below:
    参数:        ADC_Inserted_Channel_0: inserted Channel0
    参数:        ADC_Inserted_Channel_1: inserted channel1
    参数:        ADC_Inserted_Channel_2: inserted Channel2
    参数:        ADC_Inserted_Channel_3: inserted Channel3
    参数[输出]:  无
    返回值:     the conversion value
*/
uint16_t ADC_Inserted_Data_Read(uint32_t ADC_periph, uint8_t inserted_channel) {
    uint32_t idata;

    /* read the data of the selected channel */
    switch(inserted_channel) {
    case ADC_Inserted_Channel_0:
        /* read the data of channel 0 */
        idata = ADC_IDATA0(ADC_periph);
        break;

    case ADC_Inserted_Channel_1:
        /* read the data of channel 1 */
        idata = ADC_IDATA1(ADC_periph);
        break;

    case ADC_Inserted_Channel_2:
        /* read the data of channel 2 */
        idata = ADC_IDATA2(ADC_periph);
        break;

    case ADC_Inserted_Channel_3:
        /* read the data of channel 3 */
        idata = ADC_IDATA3(ADC_periph);
        break;

    default:
        idata = 0U;
        break;
    }

    return (uint16_t)idata;
}

/*!
    简介:      disable ADC analog watchdog single channel
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输出]:  无
    返回值:      无
*/
void ADC_WatchDog_Single_Channel_Disable(uint32_t ADC_periph) {
    ADC_CTL0(ADC_periph) &= ~((uint32_t)ADC_CTL0_WDSC);
}

/*!
    简介:      enable ADC analog watchdog single channel
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_channel: the selected ADC channel
                only one parameter can be selected which is shown as below:
    参数:        ADC_Channel_x: ADC Channelx(x=0..18)
    参数[输出]:  无
    返回值:      无
*/
void ADC_WatchDog_Single_Channel_Enable(uint32_t ADC_periph, uint8_t ADC_channel) {
    ADC_CTL0(ADC_periph) &= ~((uint32_t)ADC_CTL0_WDCHSEL);

    /* analog watchdog channel select */
    ADC_CTL0(ADC_periph) |= (uint32_t)ADC_channel;
    ADC_CTL0(ADC_periph) |= (uint32_t) ADC_CTL0_WDSC;
}

/*!
    简介:      configure ADC analog watchdog group channel
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_Channel_group: the channel group use analog watchdog
                only one parameter can be selected which is shown as below:
    参数:        ADC_Regular_CHANNEL: regular channel group
    参数:        ADC_Inserted_CHANNEL: inserted channel group
    参数:        ADC_Regular_Inserted_CHANNEL: both regular and inserted group
    参数[输出]:  无
    返回值:      无
*/
void ADC_WatchDog_Group_Channel_Enable(uint32_t ADC_periph, uint8_t ADC_Channel_group) {
    ADC_CTL0(ADC_periph) &= ~((uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN | ADC_CTL0_WDSC));

    /* select the group */
    switch(ADC_Channel_group) {
    case ADC_Regular_CHANNEL:
        /* regular channel analog watchdog enable */
        ADC_CTL0(ADC_periph) |= (uint32_t) ADC_CTL0_RWDEN;
        break;

    case ADC_Inserted_CHANNEL:
        /* inserted channel analog watchdog enable */
        ADC_CTL0(ADC_periph) |= (uint32_t) ADC_CTL0_IWDEN;
        break;

    case ADC_Regular_Inserted_CHANNEL:
        /* regular and inserted channel analog watchdog enable */
        ADC_CTL0(ADC_periph) |= (uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN);
        break;

    default:
        break;
    }
}

/*!
    简介:      disable ADC analog watchdog
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_Channel_group: the channel group use analog watchdog
                only one parameter can be selected which is shown as below:
    参数:        ADC_Regular_CHANNEL: regular channel group
    参数:        ADC_Inserted_CHANNEL: inserted channel group
    参数:        ADC_Regular_Inserted_CHANNEL: both regular and inserted group
    参数[输出]:  无
    返回值:      无
*/
void ADC_WatchDog_Disable(uint32_t ADC_periph, uint8_t ADC_Channel_group) {
    /* select the group */
    switch(ADC_Channel_group) {
    case ADC_Regular_CHANNEL:
        /* disable ADC analog watchdog regular channel group */
        ADC_CTL0(ADC_periph) &=  ~((uint32_t)ADC_CTL0_RWDEN);
        break;

    case ADC_Inserted_CHANNEL:
        /* disable ADC analog watchdog inserted channel group */
        ADC_CTL0(ADC_periph) &=  ~((uint32_t)ADC_CTL0_IWDEN);
        break;

    case ADC_Regular_Inserted_CHANNEL:
        /* disable ADC analog watchdog regular and inserted channel group */
        ADC_CTL0(ADC_periph) &=  ~((uint32_t)(ADC_CTL0_RWDEN | ADC_CTL0_IWDEN));
        break;

    default:
        break;
    }
}

/*!
    简介:      configure ADC analog watchdog threshold
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  low_threshold: analog watchdog low threshold,0..4095
    参数[输入]:  high_threshold: analog watchdog high threshold,0..4095
    参数[输出]:  无
    返回值:      无
*/
void ADC_WatchDog_Threshold_Config(uint32_t ADC_periph, uint16_t low_threshold, uint16_t high_threshold) {
    /* configure ADC analog watchdog low threshold */
    ADC_WDLT(ADC_periph) = (uint32_t)WDLT_WDLT(low_threshold);
    /* configure ADC analog watchdog high threshold */
    ADC_WDHT(ADC_periph) = (uint32_t)WDHT_WDHT(high_threshold);
}

/*!
    简介:      get the ADC flag bits
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_flag: the adc flag bits
                only one parameter can be selected which is shown as below:
    参数:        ADC_Flag_WDE: analog watchdog event flag
    参数:        ADC_Flag_EOC: end of group conversion flag
    参数:        ADC_Flag_EOIC: end of inserted group conversion flag
    参数:        ADC_Flag_STIC: start flag of inserted channel group
    参数:        ADC_Flag_STRC: start flag of regular channel group
    参数:        ADC_Flag_ROVF: regular data register overflow flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus ADC_Flag_Get(uint32_t ADC_periph, uint32_t ADC_flag) {
    FlagStatus reval = RESET;

    if(ADC_STAT(ADC_periph) & ADC_flag) {
        reval = SET;
    }

    return reval;

}

/*!
    简介:      clear the ADC flag bits
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_flag: the adc flag bits
                only one parameter can be selected which is shown as below:
    参数:        ADC_Flag_WDE: analog watchdog event flag
    参数:        ADC_Flag_EOC: end of group conversion flag
    参数:        ADC_Flag_EOIC: end of inserted group conversion flag
    参数:        ADC_Flag_STIC: start flag of inserted channel group
    参数:        ADC_Flag_STRC: start flag of regular channel group
    参数:        ADC_Flag_ROVF: regular data register overflow flag
    参数[输出]:  无
    返回值:      无
*/
void ADC_Flag_Clear(uint32_t ADC_periph, uint32_t ADC_flag) {
    ADC_STAT(ADC_periph) &= ~((uint32_t)ADC_flag);
}

/*!
    简介:      get the bit state of ADCx software start conversion
    参数[输入]:  ADC_periph: ADCx, x=0,1,2 only one among these parameters can be selected
    参数[输入]:  无
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus ADC_Regular_Software_Startconv_Flag_Get(uint32_t ADC_periph) {
    FlagStatus reval = RESET;

    if((uint32_t)RESET != (ADC_STAT(ADC_periph) & ADC_STAT_STRC)) {
        reval = SET;
    }

    return reval;
}

/*!
    简介:      get the bit state of ADCx software inserted channel start conversion
    参数[输入]:  ADC_periph: ADCx, x=0,1,2 only one among these parameters can be selected
    参数[输入]:  无
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus ADC_Inserted_Software_Startconv_Flag_Get(uint32_t ADC_periph) {
    FlagStatus reval = RESET;

    if((uint32_t)RESET != (ADC_STAT(ADC_periph) & ADC_STAT_STIC)) {
        reval = SET;
    }

    return reval;
}

/*!
    简介:      get the ADC interrupt bits
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_interrupt: the adc interrupt bits
                only one parameter can be selected which is shown as below:
    参数:        ADC_INT_Flag_WDE: analog watchdog interrupt
    参数:        ADC_INT_Flag_EOC: end of group conversion interrupt
    参数:        ADC_INT_Flag_EOIC: end of inserted group conversion interrupt
    参数:        ADC_INT_Flag_ROVF: regular data register overflow interrupt
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus ADC_Interrupt_Flag_Get(uint32_t ADC_periph, uint32_t ADC_interrupt) {
    FlagStatus interrupt_flag = RESET;
    uint32_t state;

    /* check the interrupt bits */
    switch(ADC_interrupt) {
    case ADC_INT_Flag_WDE:
        /* get the ADC analog watchdog interrupt bits */
        state = ADC_STAT(ADC_periph) & ADC_STAT_WDE;

        if((ADC_CTL0(ADC_periph) & ADC_CTL0_WDEIE) && state) {
            interrupt_flag = SET;
        }

        break;

    case ADC_INT_Flag_EOC:
        /* get the ADC end of group conversion interrupt bits */
        state = ADC_STAT(ADC_periph) & ADC_STAT_EOC;

        if((ADC_CTL0(ADC_periph) & ADC_CTL0_EOCIE) && state) {
            interrupt_flag = SET;
        }

        break;

    case ADC_INT_Flag_EOIC:
        /* get the ADC end of inserted group conversion interrupt bits */
        state = ADC_STAT(ADC_periph) & ADC_STAT_EOIC;

        if((ADC_CTL0(ADC_periph) & ADC_CTL0_EOICIE) && state) {
            interrupt_flag = SET;
        }

        break;

    case ADC_INT_Flag_ROVF:
        /* get the ADC regular data register overflow interrupt bits */
        state = ADC_STAT(ADC_periph) & ADC_STAT_ROVF;

        if((ADC_CTL0(ADC_periph) & ADC_CTL0_ROVFIE) && state) {
            interrupt_flag = SET;
        }

        break;

    default:
        break;
    }

    return interrupt_flag;
}

/*!
    简介:      clear the ADC flag
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_interrupt: the adc status flag
                only one parameter can be selected which is shown as below:
    参数:        ADC_INT_Flag_WDE: analog watchdog interrupt
    参数:        ADC_INT_Flag_EOC: end of group conversion interrupt
    参数:        ADC_INT_Flag_EOIC: end of inserted group conversion interrupt
    参数:        ADC_INT_Flag_ROVF: regular data register overflow interrupt
    参数[输出]:  无
    返回值:      无
*/
void ADC_Interrupt_Flag_Clear(uint32_t ADC_periph, uint32_t ADC_interrupt) {
    ADC_STAT(ADC_periph) &= ~((uint32_t)ADC_interrupt);
}

/*!
    简介:      enable ADC interrupt
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_interrupt: the adc interrupt flag
                only one parameter can be selected which is shown as below:
    参数:        ADC_INT_WDE: analog watchdog interrupt flag
    参数:        ADC_INT_EOC: end of group conversion interrupt flag
    参数:        ADC_INT_EOIC: end of inserted group conversion interrupt flag
    参数:        ADC_INT_ROVF: regular data register overflow interrupt flag
    参数[输出]:  无
    返回值:      无
*/
void ADC_Interrupt_Enable(uint32_t ADC_periph, uint32_t ADC_interrupt) {
    switch(ADC_interrupt) {
    case ADC_INT_WDE:
        /* enable analog watchdog 中断 */
        ADC_CTL0(ADC_periph) |= (uint32_t) ADC_CTL0_WDEIE;
        break;

    case ADC_INT_EOC:
        /* enable end of group conversion 中断 */
        ADC_CTL0(ADC_periph) |= (uint32_t) ADC_CTL0_EOCIE;
        break;

    case ADC_INT_EOIC:
        /* enable end of inserted group conversion 中断 */
        ADC_CTL0(ADC_periph) |= (uint32_t) ADC_CTL0_EOICIE;
        break;

    case ADC_INT_ROVF:
        ADC_CTL0(ADC_periph) |= (uint32_t) ADC_CTL0_ROVFIE;
        break;

    default:
        break;
    }
}

/*!
    简介:      disable ADC interrupt
    参数[输入]:  ADC_periph: ADCx,x=0,1,2
    参数[输入]:  ADC_flag: the adc interrupt flag
                only one parameter can be selected which is shown as below:
      参数:      ADC_INT_WDE: analog watchdog interrupt flag
      参数:      ADC_INT_EOC: end of group conversion interrupt flag
      参数:      ADC_INT_EOIC: end of inserted group conversion interrupt flag
      参数:      ADC_INT_ROVF: regular data register overflow interrupt flag
    参数[输出]:  无
    返回值:      无
*/
void ADC_Interrupt_Disable(uint32_t ADC_periph, uint32_t ADC_interrupt) {
    switch(ADC_interrupt) {
    /* select the interrupt source */
    case ADC_INT_WDE:
        ADC_CTL0(ADC_periph) &= ~((uint32_t)ADC_CTL0_WDEIE);
        break;

    case ADC_INT_EOC:
        ADC_CTL0(ADC_periph) &= ~((uint32_t)ADC_CTL0_EOCIE);
        break;

    case ADC_INT_EOIC:
        ADC_CTL0(ADC_periph) &= ~((uint32_t)ADC_CTL0_EOICIE);
        break;

    case ADC_INT_ROVF:
        ADC_CTL0(ADC_periph) &= ~((uint32_t)ADC_CTL0_ROVFIE);
        break;

    default:
        break;
    }
}

/*!
    简介:      configure the ADC sync mode
    参数[输入]:  sync_mode: ADC sync mode
                only one parameter can be selected which is shown as below:
    参数:        ADC_Sync_Mode_INDEPENDENT: all the ADCs work independently
    参数:        ADC_DAUL_REGULAL_PARALLEL_Inserted_PARALLEL: ADC0 and ADC1 work in combined regular parallel & inserted parallel mode
    参数:        ADC_DAUL_REGULAL_PARALLEL_Inserted_ROTATION: ADC0 and ADC1 work in combined regular parallel & trigger rotation mode
    参数:        ADC_DAUL_Inserted_PARALLEL: ADC0 and ADC1 work in inserted parallel mode
    参数:        ADC_DAUL_REGULAL_PARALLEL: ADC0 and ADC1 work in regular parallel mode
    参数:        ADC_DAUL_REGULAL_FOLLOW_UP: ADC0 and ADC1 work in follow-up mode
    参数:        ADC_DAUL_Inserted_TRRIGGER_ROTATION: ADC0 and ADC1 work in trigger rotation mode
    参数:        ADC_ALL_REGULAL_PARALLEL_Inserted_PARALLEL: all ADCs work in combined regular parallel & inserted parallel mode
    参数:        ADC_ALL_REGULAL_PARALLEL_Inserted_ROTATION: all ADCs work in combined regular parallel & trigger rotation mode
    参数:        ADC_ALL_Inserted_PARALLEL: all ADCs work in inserted parallel mode
    参数:        ADC_ALL_REGULAL_PARALLEL: all ADCs work in regular parallel mode
    参数:        ADC_ALL_REGULAL_FOLLOW_UP: all ADCs work in follow-up mode
    参数:        ADC_ALL_Inserted_TRRIGGER_ROTATION: all ADCs work in trigger rotation mode
    参数[输出]:  无
    返回值:      无
*/
void ADC_Sync_Mode_Config(uint32_t sync_mode) {
    ADC_SYNCCTL &= ~(ADC_SYNCCTL_SYNCM);
    ADC_SYNCCTL |= sync_mode;
}

/*!
    简介:      configure the delay between 2 sampling phases in ADC sync modes
    参数[输入]:  sample_delay:  the delay between 2 sampling phases in ADC sync modes
                only one parameter can be selected which is shown as below:
      参数:      ADC_Sync_Delay_xCYCLE: x=5..20,the delay between 2 sampling phases in ADC sync modes is x ADC clock cycles
    参数[输出]:  无
    返回值:      无
*/
void ADC_Sync_Delay_Config(uint32_t sample_delay) {
    ADC_SYNCCTL &= ~(ADC_SYNCCTL_SYNCDLY);
    ADC_SYNCCTL |= sample_delay;
}

/*!
    简介:      configure ADC sync DMA mode selection
    参数[输入]:  DMA_mode:  ADC sync DMA mode
                only one parameter can be selected which is shown as below:
    参数:        ADC_Sync_DMA_DISABLE: ADC sync DMA disabled
    参数:        ADC_Sync_DMA_MODE0: ADC sync DMA mode 0
    参数:        ADC_Sync_DMA_MODE1: ADC sync DMA mode 1
    参数[输出]:  无
    返回值:      无
*/
void ADC_Sync_DMA_Config(uint32_t DMA_mode) {
    ADC_SYNCCTL &= ~(ADC_SYNCCTL_SYNCDMA);
    ADC_SYNCCTL |= DMA_mode;
}

/*!
    简介:      configure ADC sync DMA engine is disabled after the end of transfer signal from DMA controller is detected
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ADC_Sync_DMA_Request_After_Last_Enable(void) {
    ADC_SYNCCTL |= ADC_SYNCCTL_SYNCDDM;
}

/*!
    简介:      configure ADC sync DMA engine issues requests 根据 the SYNCDMA bits
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void ADC_Sync_DMA_Request_After_Last_Disable(void) {
    ADC_SYNCCTL &= ~(ADC_SYNCCTL_SYNCDDM);
}

/*!
    简介:      read ADC sync regular data register
    参数[输入]:  无
    参数[输出]:  无
    返回值:     sync regular data
*/
uint32_t ADC_Sync_Regular_Data_Read(void) {
    return (uint32_t)ADC_SYNCDATA;
}
