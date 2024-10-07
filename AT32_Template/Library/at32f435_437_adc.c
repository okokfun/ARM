/**
  **************************************************************************
  * @file     at32f435_437_adc.c
  * @brief    contains all the functions for the adc firmware library
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

#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @defgroup ADC
  * @brief ADC driver modules
  */

#ifdef ADC_MODULE_EnableD

/** @defgroup ADC_private_functions
  */

/**
  * @brief  复位 ADC 使其所有寄存器保持复位值.
  * @param  无
  * @retval 无
  */
void ADC_Reset(void) {
    CRM_Periph_Reset(CRM_ADC_Periph_Reset, TRUE);
    CRM_Periph_Reset(CRM_ADC_Periph_Reset, FALSE);
}

/**
  * @brief  设定 A/D 转换器使能状态为关闭或开启.
  * @param  ADC_x: 所选择的 ADC 外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: A/D 转换器的预设状态.
  *         该参数可以选取自其中之一: TRUE or FALSE.
  * @retval 无
  */
void ADC_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl2_bit.adcen = new_state;
}

/**
  * @brief  为 adc_base_struct 指定初始默认值.
  * @param  sequence_Mode: 设置adc序列模式的状态.
  *         该参数可以是:TRUE or FALSE
  * @param  repeat_Mode: 设置adc重复转换模式的状态.
  *         该参数可以是:TRUE or FALSE
  * @param  data_align: 设置adc数据对齐的状态.
  *         该参数可以是以下值之一:
  *         - ADC_RIGHT_ALIGNMENT
  *         - ADC_LEFT_ALIGNMENT
  * @param  ordinary_Channel_length: 配置adc普通通道序列长度.
  *         该参数可以是:
  *         - (0x1~0xf)
  * @retval 无
  */
void ADC_Base_Default_Para_Init(ADC_Base_Config_Type *ADC_Base_struct) {
    ADC_Base_struct->sequence_Mode = FALSE;
    ADC_Base_struct->repeat_Mode = FALSE;
    ADC_Base_struct->data_align = ADC_RIGHT_ALIGNMENT;
    ADC_Base_struct->ordinary_Channel_length = 1;
}

/**
  * @brief  将 adc_base_struct 中指定的参数初始化到外设 ADC 的寄存器.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  sequence_Mode: 设置adc序列模式的状态.
  *         该参数可以是:TRUE or FALSE
  * @param  repeat_Mode: 设置adc重复转换模式的状态.
  *         该参数可以是:TRUE or FALSE
  * @param  data_align: 设置adc数据对齐的状态.
  *         该参数可以是以下值之一:
  *         - ADC_RIGHT_ALIGNMENT
  *         - ADC_LEFT_ALIGNMENT
  * @param  ordinary_Channel_length: 配置adc普通通道序列长度.
  *         该参数可以是:
  *         - (0x1~0xf)
  * @retval 无
  */
void ADC_Base_Config(ADC_Type *ADC_x, ADC_Base_Config_Type *ADC_Base_struct) {
    ADC_x->ctrl1_bit.sqen = ADC_Base_struct->sequence_Mode;
    ADC_x->ctrl2_bit.rpen = ADC_Base_struct->repeat_Mode;
    ADC_x->ctrl2_bit.dtalign = ADC_Base_struct->data_align;
    ADC_x->osq1_bit.oclen = ADC_Base_struct->ordinary_Channel_length - 1;
}

/**
  * @brief  为 adc_common_struct 指定初始默认值.
  * @param  combine_Mode: configure the adc combine_Mode mode.
  *         该参数可以是以下值之一:
  *         - ADC_INDEPENDENT_Mode                       - ADC_Ordinary_SMLT_Preempt_SMLT_ONESLAVE_Mode   - ADC_Ordinary_SMLT_Preempt_INTERLTRIG_ONESLAVE_Mode
  *         - ADC_Preempt_SMLT_ONLY_ONESLAVE_Mode        - ADC_Ordinary_SMLT_ONLY_ONESLAVE_Mode           - ADC_Ordinary_Shift_ONLY_ONESLAVE_Mode
  *         - ADC_Preempt_INTERLTRIG_ONLY_ONESLAVE_Mode  - ADC_Ordinary_SMLT_Preempt_SMLT_TWOSLAVE_Mode   - ADC_Ordinary_SMLT_Preempt_INTERLTRIG_TWOSLAVE_Mode
  *         - ADC_Preempt_SMLT_ONLY_TWOSLAVE_Mode        - ADC_Ordinary_SMLT_ONLY_TWOSLAVE_Mode           - ADC_Ordinary_Shift_ONLY_TWOSLAVE_Mode
  *         - ADC_Preempt_INTERLTRIG_ONLY_TWOSLAVE_Mode
  * @param  div: 配置adc分频.
  *         该参数可以是以下值之一:
  *         - ADC_HCLK_Div_2             - ADC_HCLK_Div_3             - ADC_HCLK_Div_4             - ADC_HCLK_Div_5
  *         - ADC_HCLK_Div_6             - ADC_HCLK_Div_7             - ADC_HCLK_Div_8             - ADC_HCLK_Div_9
  *         - ADC_HCLK_Div_10            - ADC_HCLK_Div_11            - ADC_HCLK_Div_12            - ADC_HCLK_Div_13
  *         - ADC_HCLK_Div_14            - ADC_HCLK_Div_15            - ADC_HCLK_Div_16            - ADC_HCLK_Div_17
  * @param  common_DMA_Mode: configure the adc common dma mode.
  *         该参数可以是以下值之一:
  *         - ADC_Common_DMAMODE_Disable
  *         - ADC_Common_DMAMODE_1 <mode 1 can be used: all ordinary simultaneous mode,all ordinary shifting mode>
  *         - ADC_Common_DMAMODE_2 <mode 2 can be used: one slaver ordinary simultaneous mode,all ordinary shifting mode>
  *         - ADC_Common_DMAMODE_3 <mode 3 can be used: one slaver ordinary simultaneous mode in 6/8 bit resolution,ordinary shifting mode in 6/8 bit resolution>
  *         - ADC_Common_DMAMODE_4 <mode 4 can be used: two slaver ordinary simultaneous mode in 6/8 bit resolution,two slave ordinary shifting mode in 6/8 bit resolution>
  *         - ADC_Common_DMAMODE_5 <mode 5 can be used: all two slaver ordinary simultaneous mode,all two slave ordinary shifting mode>
  * @param  common_DMA_Request_Repeat_state: set the adc common dma request repeat state.
  *         该参数可以是:TRUE or FALSE
  * @param  sampling_interval: configure the ordinary shifting mode adjacent adc sampling interval.
  *         该参数可以是以下值之一:
  *         - ADC_SAMPLING_INTERVAL_5CYCLES     - ADC_SAMPLING_INTERVAL_6CYCLES     - ADC_SAMPLING_INTERVAL_7CYCLES     - ADC_SAMPLING_INTERVAL_8CYCLES
  *         - ADC_SAMPLING_INTERVAL_9CYCLES     - ADC_SAMPLING_INTERVAL_10CYCLES    - ADC_SAMPLING_INTERVAL_11CYCLES    - ADC_SAMPLING_INTERVAL_12CYCLES
  *         - ADC_SAMPLING_INTERVAL_13CYCLES    - ADC_SAMPLING_INTERVAL_14CYCLES    - ADC_SAMPLING_INTERVAL_15CYCLES    - ADC_SAMPLING_INTERVAL_16CYCLES
  *         - ADC_SAMPLING_INTERVAL_17CYCLES    - ADC_SAMPLING_INTERVAL_18CYCLES    - ADC_SAMPLING_INTERVAL_19CYCLES    - ADC_SAMPLING_INTERVAL_20CYCLES
  * @param  tempervintrv_state: set the adc temperature sensor and vintrv state.
  *         该参数可以是:TRUE or FALSE
  * @param  vbat_state: set the adc voltage battery state.
  *         该参数可以是:TRUE or FALSE
  * @retval 无
  */
void ADC_Common_Default_Para_Init(ADC_Common_Config_Type *ADC_Common_struct) {
    ADC_Common_struct->combine_Mode = ADC_INDEPENDENT_Mode;
    ADC_Common_struct->div = ADC_HCLK_Div_2;
    ADC_Common_struct->common_DMA_Mode = ADC_Common_DMAMODE_Disable;
    ADC_Common_struct->common_DMA_Request_Repeat_state = FALSE;
    ADC_Common_struct->sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;
    ADC_Common_struct->tempervintrv_state = FALSE;
    ADC_Common_struct->vbat_state = FALSE;
}

/**
  * @brief  将 adc_common_struct 中指定的参数初始化到 ADC 公共寄存器.
  * @param  combine_Mode: configure the adc combine_Mode mode.
  *         该参数可以是以下值之一:
  *         - ADC_INDEPENDENT_Mode                       - ADC_Ordinary_SMLT_Preempt_SMLT_ONESLAVE_Mode   - ADC_Ordinary_SMLT_Preempt_INTERLTRIG_ONESLAVE_Mode
  *         - ADC_Preempt_SMLT_ONLY_ONESLAVE_Mode        - ADC_Ordinary_SMLT_ONLY_ONESLAVE_Mode           - ADC_Ordinary_Shift_ONLY_ONESLAVE_Mode
  *         - ADC_Preempt_INTERLTRIG_ONLY_ONESLAVE_Mode  - ADC_Ordinary_SMLT_Preempt_SMLT_TWOSLAVE_Mode   - ADC_Ordinary_SMLT_Preempt_INTERLTRIG_TWOSLAVE_Mode
  *         - ADC_Preempt_SMLT_ONLY_TWOSLAVE_Mode        - ADC_Ordinary_SMLT_ONLY_TWOSLAVE_Mode           - ADC_Ordinary_Shift_ONLY_TWOSLAVE_Mode
  *         - ADC_Preempt_INTERLTRIG_ONLY_TWOSLAVE_Mode
  * @param  div: 配置adc分频.
  *         该参数可以是以下值之一:
  *         - ADC_HCLK_Div_2             - ADC_HCLK_Div_3             - ADC_HCLK_Div_4             - ADC_HCLK_Div_5
  *         - ADC_HCLK_Div_6             - ADC_HCLK_Div_7             - ADC_HCLK_Div_8             - ADC_HCLK_Div_9
  *         - ADC_HCLK_Div_10            - ADC_HCLK_Div_11            - ADC_HCLK_Div_12            - ADC_HCLK_Div_13
  *         - ADC_HCLK_Div_14            - ADC_HCLK_Div_15            - ADC_HCLK_Div_16            - ADC_HCLK_Div_17
  * @param  common_DMA_Mode: configure the adc common dma mode.
  *         该参数可以是以下值之一:
  *         - ADC_Common_DMAMODE_Disable
  *         - ADC_Common_DMAMODE_1 <mode 1 can be used: all ordinary simultaneous mode,all ordinary shifting mode>
  *         - ADC_Common_DMAMODE_2 <mode 2 can be used: one slaver ordinary simultaneous mode,all ordinary shifting mode>
  *         - ADC_Common_DMAMODE_3 <mode 3 can be used: one slaver ordinary simultaneous mode in 6/8 bit resolution,ordinary shifting mode in 6/8 bit resolution>
  *         - ADC_Common_DMAMODE_4 <mode 4 can be used: two slaver ordinary simultaneous mode in 6/8 bit resolution,two slave ordinary shifting mode in 6/8 bit resolution>
  *         - ADC_Common_DMAMODE_5 <mode 5 can be used: all two slaver ordinary simultaneous mode,all two slave ordinary shifting mode>
  * @param  common_DMA_Request_Repeat_state: set the adc common dma request repeat state.
  *         该参数可以是:TRUE or FALSE
  * @param  sampling_interval: configure the ordinary shifting mode adjacent adc sampling interval.
  *         该参数可以是以下值之一:
  *         - ADC_SAMPLING_INTERVAL_5CYCLES     - ADC_SAMPLING_INTERVAL_6CYCLES     - ADC_SAMPLING_INTERVAL_7CYCLES     - ADC_SAMPLING_INTERVAL_8CYCLES
  *         - ADC_SAMPLING_INTERVAL_9CYCLES     - ADC_SAMPLING_INTERVAL_10CYCLES    - ADC_SAMPLING_INTERVAL_11CYCLES    - ADC_SAMPLING_INTERVAL_12CYCLES
  *         - ADC_SAMPLING_INTERVAL_13CYCLES    - ADC_SAMPLING_INTERVAL_14CYCLES    - ADC_SAMPLING_INTERVAL_15CYCLES    - ADC_SAMPLING_INTERVAL_16CYCLES
  *         - ADC_SAMPLING_INTERVAL_17CYCLES    - ADC_SAMPLING_INTERVAL_18CYCLES    - ADC_SAMPLING_INTERVAL_19CYCLES    - ADC_SAMPLING_INTERVAL_20CYCLES
  * @param  tempervintrv_state: set the adc temperature sensor and vintrv state.
  *         该参数可以是:TRUE or FALSE
  * @param  vbat_state: set the adc voltage battery state.
  *         该参数可以是:TRUE or FALSE
  * @retval 无
  */
void ADC_Common_Config(ADC_Common_Config_Type *ADC_Common_struct) {
    ADCCOM->cctrl_bit.mssel = ADC_Common_struct->combine_Mode;
    ADCCOM->cctrl_bit.adcdiv = ADC_Common_struct->div;

    if(ADC_Common_struct->common_DMA_Mode & 0x04) {
        ADCCOM->cctrl_bit.msdmasel_h = TRUE;
    } else {
        ADCCOM->cctrl_bit.msdmasel_h = FALSE;
    }

    ADCCOM->cctrl_bit.msdmasel_l = ADC_Common_struct->common_DMA_Mode & 0x03;
    ADCCOM->cctrl_bit.msdrcen = ADC_Common_struct->common_DMA_Request_Repeat_state;
    ADCCOM->cctrl_bit.asisel = ADC_Common_struct->sampling_interval;
    ADCCOM->cctrl_bit.itsrven = ADC_Common_struct->tempervintrv_state;
    ADCCOM->cctrl_bit.vbaten = ADC_Common_struct->vbat_state;
}

/**
  * @brief  设定 ADC 的转换分辨率.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  resolution: 选择 ADC 的转换分辨率.
  *         该参数可以是以下值之一:
  *         - ADC_Resolution_12B
  *         - ADC_Resolution_10B
  *         - ADC_Resolution_8B
  *         - ADC_Resolution_6B
  * @retval 无
  */
void ADC_Resolution_Set(ADC_Type *ADC_x, ADC_Resolution_Type resolution) {
    ADC_x->ctrl1_bit.crsel = resolution;
}

/**
  * @brief  enable or disable the adc voltage battery.
  * @param  new_state: new state of the adc voltage battery.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Voltage_Battery_Enable(confirm_state new_state) {
    ADCCOM->cctrl_bit.vbaten = new_state;
}

/**
  * @brief  enable or disable the adc dma transfer.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of the adc dma transfer.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_DMA_Mode_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl2_bit.ocdmaen = new_state;
}

/**
  * @brief  enable or disable the adc dma request repeat.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: the adc dma request repeat state.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_DMA_Request_Repeat_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl2_bit.ocdrcen = new_state;
}

/**
  * @brief  enable or disable the specified adc interrupts.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_int: 指定adc interrupt sources to be enabled or disabled.
  *         该参数可以是以下值之一:
  *         - ADC_Occe_INT
  *         - ADC_VMOR_INT
  *         - ADC_PCCE_INT
  *         - ADC_OCCO_INT
  * @param  new_state: new state of the specified adc interrupts.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Interrupt_Enable(ADC_Type *ADC_x, uint32_t ADC_int, confirm_state new_state) {
    if(new_state == TRUE) {
        ADC_x->ctrl1 |= ADC_int;
    } else if(new_state == FALSE) {
        ADC_x->ctrl1 &= ~ADC_int;
    }
}

/**
  * @brief  set calibration value of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Calibration_value: calibration value of adc.
  *         该参数可以是:
  *         - (0x00~0x7F)
  * @retval 无
  */
void ADC_Calibration_Value_Set(ADC_Type *ADC_x, uint8_t ADC_Calibration_value) {
    ADC_x->calval = ADC_Calibration_value;
}

/**
  * @brief  initialize calibration register of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval 无
  */
void ADC_Calibration_Init(ADC_Type *ADC_x) {
    ADC_x->ctrl2_bit.adcalinit = TRUE;
}

/**
  * @brief  get calibration register's initialize status of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval the new state of reset calibration register status(SET or RESET).
  */
flag_status ADC_Calibration_Init_Status_Get(ADC_Type *ADC_x) {
    if(ADC_x->ctrl2_bit.adcalinit) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  start calibration process of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval 无
  */
void ADC_Calibration_Start(ADC_Type *ADC_x) {
    ADC_x->ctrl2_bit.adcal = TRUE;
}

/**
  * @brief  get calibration status of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval the new state of calibration status(SET or RESET).
  */
flag_status ADC_Calibration_Status_Get(ADC_Type *ADC_x) {
    if(ADC_x->ctrl2_bit.adcal) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  enable or disable the voltage monitoring on single/all ordinary or preempt channels of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Voltage_monitoring: choose the ADC_Voltage_monitoring config.
  *         该参数可以是以下值之一:
  *         - ADC_VMONITOR_Single_ORDINARY
  *         - ADC_VMONITOR_Single_PREEMPT
  *         - ADC_VMONITOR_Single_Ordinary_PREEMPT
  *         - ADC_VMONITOR_All_ORDINARY
  *         - ADC_VMONITOR_All_PREEMPT
  *         - ADC_VMONITOR_All_Ordinary_PREEMPT
  *         - ADC_VMONITOR_NONE
  * @retval 无
  */
void ADC_Voltage_Monitor_Enable(ADC_Type *ADC_x, ADC_Voltage_monitoring_Type ADC_Voltage_monitoring) {
    ADC_x->ctrl1_bit.ocvmen = FALSE;
    ADC_x->ctrl1_bit.pcvmen = FALSE;
    ADC_x->ctrl1_bit.vmsgen = FALSE;
    ADC_x->ctrl1 |= ADC_Voltage_monitoring;
}

/**
  * @brief  set voltage monitoring's high and low thresholds value of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_high_threshold: voltage monitoring's high thresholds value.
  *         该参数可以是:
  *         - (0x000~0xFFF)
  * @param  ADC_Low_threshold: voltage monitoring's low thresholds value.
  *         该参数可以是:
  *         - (0x000~0xFFF)
  * @retval 无
  */
void ADC_Voltage_Monitor_Threshold_Value_Set(ADC_Type *ADC_x, uint16_t ADC_high_threshold, uint16_t ADC_Low_threshold) {
    ADC_x->vmhb_bit.vmhb = ADC_high_threshold;
    ADC_x->vmlb_bit.vmlb = ADC_Low_threshold;
}

/**
  * @brief  select the voltage monitoring's channel of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Channel: select the channel.
  *         该参数可以是以下值之一:
  *         - ADC_Channel_0    - ADC_Channel_1    - ADC_Channel_2    - ADC_Channel_3
  *         - ADC_Channel_4    - ADC_Channel_5    - ADC_Channel_6    - ADC_Channel_7
  *         - ADC_Channel_8    - ADC_Channel_9    - ADC_Channel_10   - ADC_Channel_11
  *         - ADC_Channel_12   - ADC_Channel_13   - ADC_Channel_14   - ADC_Channel_15
  *         - ADC_Channel_16   - ADC_Channel_17   - ADC_Channel_18
  * @retval 无
  */
void ADC_Voltage_Monitor_Single_Channel_Select(ADC_Type *ADC_x, ADC_Channel_Select_Type ADC_Channel) {
    ADC_x->ctrl1_bit.vmcsel = ADC_Channel;
}

/**
  * @brief  set ordinary channel's corresponding rank in the sequencer and sample time of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Channel: select the channel.
  *         该参数可以是以下值之一:
  *         - ADC_Channel_0    - ADC_Channel_1    - ADC_Channel_2    - ADC_Channel_3
  *         - ADC_Channel_4    - ADC_Channel_5    - ADC_Channel_6    - ADC_Channel_7
  *         - ADC_Channel_8    - ADC_Channel_9    - ADC_Channel_10   - ADC_Channel_11
  *         - ADC_Channel_12   - ADC_Channel_13   - ADC_Channel_14   - ADC_Channel_15
  *         - ADC_Channel_16   - ADC_Channel_17   - ADC_Channel_18
  * @param  ADC_sequence: set rank in the ordinary group sequencer.
  *         this parameter must be:
  *         - between 1 to 16
  * @param  ADC_sampletime: set the sampletime of adc channel.
  *         该参数可以是以下值之一:
  *         - ADC_SAMPLETIME_2_5
  *         - ADC_SAMPLETIME_6_5
  *         - ADC_SAMPLETIME_12_5
  *         - ADC_SAMPLETIME_24_5
  *         - ADC_SAMPLETIME_47_5
  *         - ADC_SAMPLETIME_92_5
  *         - ADC_SAMPLETIME_247_5
  *         - ADC_SAMPLETIME_640_5
  * @retval 无
  */
void ADC_Ordinary_Channel_Set(ADC_Type *ADC_x, ADC_Channel_Select_Type ADC_Channel, uint8_t ADC_sequence, ADC_sampletime_Select_Type ADC_sampletime) {
    switch(ADC_Channel) {
        case ADC_Channel_0:
            ADC_x->spt2_bit.cspt0 = ADC_sampletime;
            break;

        case ADC_Channel_1:
            ADC_x->spt2_bit.cspt1 = ADC_sampletime;
            break;

        case ADC_Channel_2:
            ADC_x->spt2_bit.cspt2 = ADC_sampletime;
            break;

        case ADC_Channel_3:
            ADC_x->spt2_bit.cspt3 = ADC_sampletime;
            break;

        case ADC_Channel_4:
            ADC_x->spt2_bit.cspt4 = ADC_sampletime;
            break;

        case ADC_Channel_5:
            ADC_x->spt2_bit.cspt5 = ADC_sampletime;
            break;

        case ADC_Channel_6:
            ADC_x->spt2_bit.cspt6 = ADC_sampletime;
            break;

        case ADC_Channel_7:
            ADC_x->spt2_bit.cspt7 = ADC_sampletime;
            break;

        case ADC_Channel_8:
            ADC_x->spt2_bit.cspt8 = ADC_sampletime;
            break;

        case ADC_Channel_9:
            ADC_x->spt2_bit.cspt9 = ADC_sampletime;
            break;

        case ADC_Channel_10:
            ADC_x->spt1_bit.cspt10 = ADC_sampletime;
            break;

        case ADC_Channel_11:
            ADC_x->spt1_bit.cspt11 = ADC_sampletime;
            break;

        case ADC_Channel_12:
            ADC_x->spt1_bit.cspt12 = ADC_sampletime;
            break;

        case ADC_Channel_13:
            ADC_x->spt1_bit.cspt13 = ADC_sampletime;
            break;

        case ADC_Channel_14:
            ADC_x->spt1_bit.cspt14 = ADC_sampletime;
            break;

        case ADC_Channel_15:
            ADC_x->spt1_bit.cspt15 = ADC_sampletime;
            break;

        case ADC_Channel_16:
            ADC_x->spt1_bit.cspt16 = ADC_sampletime;
            break;

        case ADC_Channel_17:
            ADC_x->spt1_bit.cspt17 = ADC_sampletime;
            break;

        case ADC_Channel_18:
            ADC_x->spt1_bit.cspt18 = ADC_sampletime;
            break;

        default:
            break;
    }

    switch(ADC_sequence) {
        case 1:
            ADC_x->osq3_bit.osn1 = ADC_Channel;
            break;

        case 2:
            ADC_x->osq3_bit.osn2 = ADC_Channel;
            break;

        case 3:
            ADC_x->osq3_bit.osn3 = ADC_Channel;
            break;

        case 4:
            ADC_x->osq3_bit.osn4 = ADC_Channel;
            break;

        case 5:
            ADC_x->osq3_bit.osn5 = ADC_Channel;
            break;

        case 6:
            ADC_x->osq3_bit.osn6 = ADC_Channel;
            break;

        case 7:
            ADC_x->osq2_bit.osn7 = ADC_Channel;
            break;

        case 8:
            ADC_x->osq2_bit.osn8 = ADC_Channel;
            break;

        case 9:
            ADC_x->osq2_bit.osn9 = ADC_Channel;
            break;

        case 10:
            ADC_x->osq2_bit.osn10 = ADC_Channel;
            break;

        case 11:
            ADC_x->osq2_bit.osn11 = ADC_Channel;
            break;

        case 12:
            ADC_x->osq2_bit.osn12 = ADC_Channel;
            break;

        case 13:
            ADC_x->osq1_bit.osn13 = ADC_Channel;
            break;

        case 14:
            ADC_x->osq1_bit.osn14 = ADC_Channel;
            break;

        case 15:
            ADC_x->osq1_bit.osn15 = ADC_Channel;
            break;

        case 16:
            ADC_x->osq1_bit.osn16 = ADC_Channel;
            break;

        default:
            break;
    }
}

/**
  * @brief  set preempt channel lenghth of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Channel_lenght: set the adc preempt channel lenghth.
  *         该参数可以是:
  *         - (0x1~0x4)
  * @retval 无
  */
void ADC_Preempt_Channel_Length_Set(ADC_Type *ADC_x, uint8_t ADC_Channel_lenght) {
    ADC_x->psq_bit.pclen =  ADC_Channel_lenght - 1;
}

/**
  * @brief  configure preempt channel's corresponding rank in the sequencer and sample time of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Channel: select the channel.
  *         该参数可以是以下值之一:
  *         - ADC_Channel_0    - ADC_Channel_1    - ADC_Channel_2    - ADC_Channel_3
  *         - ADC_Channel_4    - ADC_Channel_5    - ADC_Channel_6    - ADC_Channel_7
  *         - ADC_Channel_8    - ADC_Channel_9    - ADC_Channel_10   - ADC_Channel_11
  *         - ADC_Channel_12   - ADC_Channel_13   - ADC_Channel_14   - ADC_Channel_15
  *         - ADC_Channel_16   - ADC_Channel_17   - ADC_Channel_18
  * @param  ADC_sequence: set rank in the preempt group sequencer.
  *         this parameter must be:
  *         - between 1 to 4
  * @param  ADC_sampletime: config the sampletime of adc channel.
  *         该参数可以是以下值之一:
  *         - ADC_SAMPLETIME_2_5
  *         - ADC_SAMPLETIME_6_5
  *         - ADC_SAMPLETIME_12_5
  *         - ADC_SAMPLETIME_24_5
  *         - ADC_SAMPLETIME_47_5
  *         - ADC_SAMPLETIME_92_5
  *         - ADC_SAMPLETIME_247_5
  *         - ADC_SAMPLETIME_640_5
  * @retval 无
  */
void ADC_Preempt_Channel_Set(ADC_Type *ADC_x, ADC_Channel_Select_Type ADC_Channel, uint8_t ADC_sequence, ADC_sampletime_Select_Type ADC_sampletime) {
    uint16_t sequence_index = 0;

    switch(ADC_Channel) {
        case ADC_Channel_0:
            ADC_x->spt2_bit.cspt0 = ADC_sampletime;
            break;

        case ADC_Channel_1:
            ADC_x->spt2_bit.cspt1 = ADC_sampletime;
            break;

        case ADC_Channel_2:
            ADC_x->spt2_bit.cspt2 = ADC_sampletime;
            break;

        case ADC_Channel_3:
            ADC_x->spt2_bit.cspt3 = ADC_sampletime;
            break;

        case ADC_Channel_4:
            ADC_x->spt2_bit.cspt4 = ADC_sampletime;
            break;

        case ADC_Channel_5:
            ADC_x->spt2_bit.cspt5 = ADC_sampletime;
            break;

        case ADC_Channel_6:
            ADC_x->spt2_bit.cspt6 = ADC_sampletime;
            break;

        case ADC_Channel_7:
            ADC_x->spt2_bit.cspt7 = ADC_sampletime;
            break;

        case ADC_Channel_8:
            ADC_x->spt2_bit.cspt8 = ADC_sampletime;
            break;

        case ADC_Channel_9:
            ADC_x->spt2_bit.cspt9 = ADC_sampletime;
            break;

        case ADC_Channel_10:
            ADC_x->spt1_bit.cspt10 = ADC_sampletime;
            break;

        case ADC_Channel_11:
            ADC_x->spt1_bit.cspt11 = ADC_sampletime;
            break;

        case ADC_Channel_12:
            ADC_x->spt1_bit.cspt12 = ADC_sampletime;
            break;

        case ADC_Channel_13:
            ADC_x->spt1_bit.cspt13 = ADC_sampletime;
            break;

        case ADC_Channel_14:
            ADC_x->spt1_bit.cspt14 = ADC_sampletime;
            break;

        case ADC_Channel_15:
            ADC_x->spt1_bit.cspt15 = ADC_sampletime;
            break;

        case ADC_Channel_16:
            ADC_x->spt1_bit.cspt16 = ADC_sampletime;
            break;

        case ADC_Channel_17:
            ADC_x->spt1_bit.cspt17 = ADC_sampletime;
            break;

        case ADC_Channel_18:
            ADC_x->spt1_bit.cspt18 = ADC_sampletime;
            break;

        default:
            break;
    }

    sequence_index = ADC_sequence + 3 - ADC_x->psq_bit.pclen;

    switch(sequence_index) {
        case 1:
            ADC_x->psq_bit.psn1 = ADC_Channel;
            break;

        case 2:
            ADC_x->psq_bit.psn2 = ADC_Channel;
            break;

        case 3:
            ADC_x->psq_bit.psn3 = ADC_Channel;
            break;

        case 4:
            ADC_x->psq_bit.psn4 = ADC_Channel;
            break;

        default:
            break;
    }
}

/**
  * @brief  set the ordinary channel's external trigger edge and
  *         set external trigger event of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Ordinary_trig: select the external trigger event.
  *         该参数可以是以下值之一:
  *         - ADC_Ordinary_Trig_TMR1CH1     - ADC_Ordinary_Trig_TMR1CH2      - ADC_Ordinary_Trig_TMR1CH3      - ADC_Ordinary_Trig_TMR2CH2
  *         - ADC_Ordinary_Trig_TMR2CH3     - ADC_Ordinary_Trig_TMR2CH4      - ADC_Ordinary_Trig_TMR2TRGOUT   - ADC_Ordinary_Trig_TMR3CH1
  *         - ADC_Ordinary_Trig_TMR3TRGOUT  - ADC_Ordinary_Trig_TMR4CH4      - ADC_Ordinary_Trig_TMR5CH1      - ADC_Ordinary_Trig_TMR5CH2
  *         - ADC_Ordinary_Trig_TMR5CH3     - ADC_Ordinary_Trig_TMR8CH1      - ADC_Ordinary_Trig_TMR8TRGOUT   - ADC_Ordinary_Trig_EXINT11
  *         - ADC_Ordinary_Trig_TMR20TRGOUT - ADC_Ordinary_Trig_TMR20TRGOUT2 - ADC_Ordinary_Trig_TMR20CH1     - ADC_Ordinary_Trig_TMR20CH2
  *         - ADC_Ordinary_Trig_TMR20CH3    - ADC_Ordinary_Trig_TMR8TRGOUT2  - ADC_Ordinary_Trig_TMR1TRGOUT2  - ADC_Ordinary_Trig_TMR4TRGOUT
  *         - ADC_Ordinary_Trig_TMR6TRGOUT  - ADC_Ordinary_Trig_TMR3CH4      - ADC_Ordinary_Trig_TMR4CH1      - ADC_Ordinary_Trig_TMR1TRGOUT
  *         - ADC_Ordinary_Trig_TMR2CH1     - ADC_Ordinary_Trig_TMR7TRGOUT
  * @param  ADC_Ordinary_Trig_edge: ordinary channel conversion's external_Trigger_edge.
  *         该参数可以是以下值之一:
  *         - ADC_Ordinary_Trig_Edge_NONE
  *         - ADC_Ordinary_Trig_Edge_RISING
  *         - ADC_Ordinary_Trig_Edge_FALLING
  *         - ADC_Ordinary_Trig_Edge_RISING_FALLING
  * @retval 无
  */
void ADC_Ordinary_Conversion_Trigger_Set(ADC_Type *ADC_x, ADC_Ordinary_Trig_Select_Type ADC_Ordinary_trig, ADC_Ordinary_Trig_Edge_Type ADC_Ordinary_Trig_edge) {
    if(ADC_Ordinary_trig > ADC_Ordinary_Trig_EXINT11) {
        ADC_x->ctrl2_bit.octesel_h = 1;
        ADC_x->ctrl2_bit.octesel_l = ADC_Ordinary_trig & 0x0F;
    } else {
        ADC_x->ctrl2_bit.octesel_h = 0;
        ADC_x->ctrl2_bit.octesel_l = ADC_Ordinary_trig & 0x0F;
    }

    ADC_x->ctrl2_bit.ocete = ADC_Ordinary_Trig_edge;
}

/**
  * @brief  enable or disable the preempt channel's external trigger and
  *         set external trigger event of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Preempt_trig: select the external trigger event.
  *         该参数可以是以下值之一:
  *         - ADC_Preempt_Trig_TMR1CH4      - ADC_Preempt_Trig_TMR1TRGOUT   - ADC_Preempt_Trig_TMR2CH1   - ADC_Preempt_Trig_TMR2TRGOUT
  *         - ADC_Preempt_Trig_TMR3CH2      - ADC_Preempt_Trig_TMR3CH4      - ADC_Preempt_Trig_TMR4CH1   - ADC_Preempt_Trig_TMR4CH2
  *         - ADC_Preempt_Trig_TMR4CH3      - ADC_Preempt_Trig_TMR4TRGOUT   - ADC_Preempt_Trig_TMR5CH4   - ADC_Preempt_Trig_TMR5TRGOUT
  *         - ADC_Preempt_Trig_TMR8CH2      - ADC_Preempt_Trig_TMR8CH3      - ADC_Preempt_Trig_TMR8CH4   - ADC_Preempt_Trig_EXINT15
  *         - ADC_Preempt_Trig_TMR20TRGOUT  - ADC_Preempt_Trig_TMR20TRGOUT2 - ADC_Preempt_Trig_TMR20CH4  - ADC_Preempt_Trig_TMR1TRGOUT2
  *         - ADC_Preempt_Trig_TMR8TRGOUT   - ADC_Preempt_Trig_TMR8TRGOUT2  - ADC_Preempt_Trig_TMR3CH3   - ADC_Preempt_Trig_TMR3TRGOUT
  *         - ADC_Preempt_Trig_TMR3CH1      - ADC_Preempt_Trig_TMR6TRGOUT   - ADC_Preempt_Trig_TMR4CH4   - ADC_Preempt_Trig_TMR1CH3
  *         - ADC_Preempt_Trig_TMR20CH2     - ADC_Preempt_Trig_TMR7TRGOUT
  * @param  ADC_Preempt_Trig_edge: preempt channel conversion's external_Trigger_edge.
  *         该参数可以是以下值之一:
  *         - ADC_Preempt_Trig_Edge_NONE
  *         - ADC_Preempt_Trig_Edge_RISING
  *         - ADC_Preempt_Trig_Edge_FALLING
  *         - ADC_Preempt_Trig_Edge_RISING_FALLING
  * @retval 无
  */
void ADC_Preempt_Conversion_Trigger_Set(ADC_Type *ADC_x, ADC_Preempt_Trig_Select_Type ADC_Preempt_trig, ADC_Preempt_Trig_Edge_Type ADC_Preempt_Trig_edge) {
    if(ADC_Preempt_trig > ADC_Preempt_Trig_EXINT15) {
        ADC_x->ctrl2_bit.pctesel_h = 1;
        ADC_x->ctrl2_bit.pctesel_l = ADC_Preempt_trig & 0x0F;
    } else {
        ADC_x->ctrl2_bit.pctesel_h = 0;
        ADC_x->ctrl2_bit.pctesel_l = ADC_Preempt_trig & 0x0F;
    }

    ADC_x->ctrl2_bit.pcete = ADC_Preempt_Trig_edge;
}

/**
  * @brief  set preempt channel's conversion value offset of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Preempt_Channel: select the preempt channel.
  *         该参数可以是以下值之一:
  *         - ADC_Preempt_Channel_1
  *         - ADC_Preempt_Channel_2
  *         - ADC_Preempt_Channel_3
  *         - ADC_Preempt_Channel_4
  * @param  ADC_Offset_value: set the adc preempt channel's conversion value offset.
  *         该参数可以是:
  *         - (0x000~0xFFF)
  * @retval 无
  */
void ADC_Preempt_Offset_Value_Set(ADC_Type *ADC_x, ADC_Preempt_Channel_Type ADC_Preempt_Channel, uint16_t ADC_Offset_value) {
    switch(ADC_Preempt_Channel) {
        case ADC_Preempt_Channel_1:
            ADC_x->pcdto1_bit.pcdto1 = ADC_Offset_value;
            break;

        case ADC_Preempt_Channel_2:
            ADC_x->pcdto2_bit.pcdto2 = ADC_Offset_value;
            break;

        case ADC_Preempt_Channel_3:
            ADC_x->pcdto3_bit.pcdto3 = ADC_Offset_value;
            break;

        case ADC_Preempt_Channel_4:
            ADC_x->pcdto4_bit.pcdto4 = ADC_Offset_value;
            break;

        default:
            break;
    }
}

/**
  * @brief  set partitioned mode channel count of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Channel_count: configure the adc partitioned mode channel count.
  *         该参数可以是:
  *         - (0x1~0x8)
  * @retval 无
  */
void ADC_Ordinary_Part_Count_Set(ADC_Type *ADC_x, uint8_t ADC_Channel_count) {

    ADC_x->ctrl1_bit.ocpcnt =  ADC_Channel_count - 1;
}

/**
  * @brief  enable or disable the partitioned mode on ordinary channel of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of ordinary channel's partitioned mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Ordinary_Part_Mode_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl1_bit.ocpen = new_state;
}

/**
  * @brief  enable or disable the partitioned mode on preempt channel of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of preempt channel's partitioned mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Preempt_Part_Mode_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl1_bit.pcpen = new_state;
}

/**
  * @brief  enable or disable automatic preempt group conversion of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of automatic preempt group conversion.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Preempt_Auto_Mode_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl1_bit.pcautoen = new_state;
}

/**
  * @brief  stop the ongoing conversion of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval 无
  */
void ADC_Conversion_stop(ADC_Type *ADC_x) {
    ADC_x->ctrl2_bit.adabrt = TRUE;
}

/**
  * @brief  get stop conversion's status of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval the new state of stop conversion's status(SET or RESET).
  */
flag_status ADC_Conversion_Stop_Status_Get(ADC_Type *ADC_x) {
    if(ADC_x->ctrl2_bit.adabrt) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  enable or disable each ordinary channel conversion set occe flag of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of each ordinary channel conversion set occe flag.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Occe_Each_Conversion_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl2_bit.eocsfen = new_state;
}

/**
  * @brief  enable or disable ordinary software start conversion of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of ordinary software start conversion.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Ordinary_Software_Trigger_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl2_bit.ocswtrg = new_state;
}

/**
  * @brief  get ordinary software start conversion status of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval the new state of ordinary software start conversion status(SET or RESET).
  */
flag_status ADC_Ordinary_Software_Trigger_Status_Get(ADC_Type *ADC_x) {
    if(ADC_x->ctrl2_bit.ocswtrg) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  enable or disable preempt software start conversion of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of preempt software start conversion.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Preempt_Software_Trigger_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ctrl2_bit.pcswtrg = new_state;
}

/**
  * @brief  get preempt software start conversion status of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval the new state of preempt software start conversion status(SET or RESET).
  */
flag_status ADC_Preempt_Software_Trigger_Status_Get(ADC_Type *ADC_x) {
    if(ADC_x->ctrl2_bit.pcswtrg) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  return the last conversion data for ordinary channel of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @retval the last conversion data for ordinary channel.
  */
uint16_t ADC_Ordinary_Conversion_Data_Get(ADC_Type *ADC_x) {
    return (uint16_t)(ADC_x->odt_bit.odt);
}

/**
  * @brief  return the last ordinary conversion data of combine adc.
  * @retval the last conversion data for ordinary channel.
  */
uint32_t ADC_Combine_Ordinary_Conversion_Data_Get(void) {
    return (uint32_t)(ADCCOM->codt);
}

/**
  * @brief  return the conversion data for selection preempt channel of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_Preempt_Channel: select the preempt channel.
  *         该参数可以是以下值之一:
  *         - ADC_Preempt_Channel_1
  *         - ADC_Preempt_Channel_2
  *         - ADC_Preempt_Channel_3
  *         - ADC_Preempt_Channel_4
  * @retval the conversion data for selection preempt channel.
  */
uint16_t ADC_Preempt_Conversion_Data_Get(ADC_Type *ADC_x, ADC_Preempt_Channel_Type ADC_Preempt_Channel) {
    uint16_t preempt_conv_Data_index = 0;

    switch(ADC_Preempt_Channel) {
        case ADC_Preempt_Channel_1:
            preempt_conv_Data_index = (uint16_t)(ADC_x->pdt1_bit.pdt1);
            break;

        case ADC_Preempt_Channel_2:
            preempt_conv_Data_index = (uint16_t)(ADC_x->pdt2_bit.pdt2);
            break;

        case ADC_Preempt_Channel_3:
            preempt_conv_Data_index = (uint16_t)(ADC_x->pdt3_bit.pdt3);
            break;

        case ADC_Preempt_Channel_4:
            preempt_conv_Data_index = (uint16_t)(ADC_x->pdt4_bit.pdt4);
            break;

        default:
            break;
    }

    return preempt_conv_Data_index;
}

/**
  * @brief  get flag of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_flag: select the adc flag.
  *         该参数可以是以下值之一:
  *         - ADC_VMOR_FLAG
  *         - ADC_Occe_FLAG
  *         - ADC_PCCE_FLAG
  *         - ADC_PCCS_FLAG(无中断关联)
  *         - ADC_OCCS_FLAG(无中断关联)
  *         - ADC_OCCO_FLAG
  *         - ADC_RDY_FLAG(无中断关联)
  * @retval the new state of adc flag status(SET or RESET).
  */
flag_status ADC_Flag_Get(ADC_Type *ADC_x, uint8_t ADC_flag) {
    flag_status status = RESET;

    if((ADC_x->sts & ADC_flag) == RESET) {
        status = RESET;
    } else {
        status = SET;
    }

    return status;
}

/**
  * @brief  clear flag of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         ADC1, ADC2, ADC3.
  * @param  ADC_flag: select the adc flag.
  *         该参数可以是以下值的任意组合:
  *         - ADC_VMOR_FLAG
  *         - ADC_Occe_FLAG(also can clear by reading the ADC_x->odt)
  *         - ADC_PCCE_FLAG
  *         - ADC_PCCS_FLAG
  *         - ADC_OCCS_FLAG
  *         - ADC_OCCO_FLAG
  *         - note:"ADC_RDY_FLAG" cannot be choose!rdy bit is readonly bit,it means the adc is ready to accept conversion request
  * @retval 无
  */
void ADC_Flag_Clear(ADC_Type *ADC_x, uint32_t ADC_flag) {
    ADC_x->sts = ~ADC_flag;
}

/**
  * @brief  enable or disable the ordinary oversampling of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of ordinary oversampling.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Ordinary_OverSample_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ovsp_bit.oosen = new_state;
}

/**
  * @brief  enable or disable the preempt oversampling of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of preempt oversampling.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Preempt_OverSample_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ovsp_bit.posen = new_state;
}

/**
  * @brief  config the oversampling ratio and shift of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_OverSample_ratio: set the oversample ratio.
  *         该参数可以是以下值之一:
  *         - ADC_OverSample_Ratio_2
  *         - ADC_OverSample_Ratio_4
  *         - ADC_OverSample_Ratio_8
  *         - ADC_OverSample_Ratio_16
  *         - ADC_OverSample_Ratio_32
  *         - ADC_OverSample_Ratio_64
  *         - ADC_OverSample_Ratio_128
  *         - ADC_OverSample_Ratio_256
  * @param  ADC_OverSample_shift: set the oversample shift.
  *         该参数可以是以下值之一:
  *         - ADC_OverSample_Shift_0
  *         - ADC_OverSample_Shift_1
  *         - ADC_OverSample_Shift_2
  *         - ADC_OverSample_Shift_3
  *         - ADC_OverSample_Shift_4
  *         - ADC_OverSample_Shift_5
  *         - ADC_OverSample_Shift_6
  *         - ADC_OverSample_Shift_7
  *         - ADC_OverSample_Shift_8
  * @retval 无
  */
void ADC_OverSample_Ratio_Shift_Set(ADC_Type *ADC_x, ADC_OverSample_Ratio_Type ADC_OverSample_ratio, ADC_OverSample_Shift_Type ADC_OverSample_shift) {
    ADC_x->ovsp_bit.osrsel = ADC_OverSample_ratio;
    ADC_x->ovsp_bit.osssel = ADC_OverSample_shift;
}

/**
  * @brief  enable or disable the ordinary oversampling trigger mode of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  new_state: new state of ordinary oversampling trigger mode.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void ADC_Ordinary_OverSample_Trig_Enable(ADC_Type *ADC_x, confirm_state new_state) {
    ADC_x->ovsp_bit.oostren = new_state;
}

/**
  * @brief  set ordinary oversample restart mode of the specified adc peripheral.
  * @param  ADC_x: 选择adc外设.
  *         该参数可以是以下值之一:
  *         - ADC1, ADC2, ADC3.
  * @param  ADC_or_OverSample_restart: ordinary oversample restart mode.
  *         该参数可以是以下值之一:
  *         - ADC_OverSample_CONTINUE
  *         - ADC_OverSample_RESTART
  * @retval 无
  */
void ADC_Ordinary_OverSample_Restart_Set(ADC_Type *ADC_x, ADC_Ordinary_OverSample_Restart_Type ADC_Ordinary_OverSample_restart) {
    ADC_x->ovsp_bit.oosrsel = ADC_Ordinary_OverSample_restart;
}

#endif
