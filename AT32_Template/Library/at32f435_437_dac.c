/**
  **************************************************************************
  * @file     at32f435_437_dac.c
  * @brief    contains all the functions for the dac firmware library
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

/** @defgroup DAC
  * @brief DAC driver modules
  */

#ifdef DAC_MODULE_EnableD

/** @defgroup DAC_private_functions
  */

/**
  * @brief  dac reset
  * @param  无
  * @retval 无
  */
void DAC_Reset(void) {
    CRM_Periph_Reset(CRM_DAC_Periph_Reset, TRUE);
    CRM_Periph_Reset(CRM_DAC_Periph_Reset, FALSE);
}

/**
  * @brief  enable or disable dac
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DAC_Enable(DAC_Select_Type DAC_Select, confirm_state new_state) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->ctrl_bit.d1en = new_state;
            break;

        case DAC2_Select:
            DAC->ctrl_bit.d2en = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  enable or disable dac output buffer
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DAC_OutPut_Buffer_Enable(DAC_Select_Type DAC_Select, confirm_state new_state) {
    new_state = (confirm_state)!new_state;

    switch(DAC_Select) {
        case DAC1_Select:
            DAC->ctrl_bit.d1obdis = new_state;
            break;

        case DAC2_Select:
            DAC->ctrl_bit.d2obdis = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  enable or disable dac trigger
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DAC_Trigger_Enable(DAC_Select_Type DAC_Select, confirm_state new_state) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->ctrl_bit.d1trgen = new_state;
            break;

        case DAC2_Select:
            DAC->ctrl_bit.d2trgen = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  select dac trigger
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @param  DAC_Trigger_source
  *         该参数可以是以下值之一:
  *         - DAC_TMR6_Trgout_EVENT
  *         - DAC_TMR8_Trgout_EVENT
  *         - DAC_TMR7_Trgout_EVENT
  *         - DAC_TMR5_Trgout_EVENT
  *         - DAC_TMR2_Trgout_EVENT
  *         - DAC_TMR4_Trgout_EVENT
  *         - DAC_External_Interrupt_Line_9
  *         - DAC_Software_TRIGGER
  * @retval 无
  */
void DAC_Trigger_Select(DAC_Select_Type DAC_Select, DAC_Trigger_Type DAC_Trigger_source) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->ctrl_bit.d1trgsel = DAC_Trigger_source;
            break;

        case DAC2_Select:
            DAC->ctrl_bit.d2trgsel = DAC_Trigger_source;
            break;

        default:
            break;
    }
}

/**
  * @brief  generate dac software trigger
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @retval 无
  */
void DAC_Software_Trigger_Generate(DAC_Select_Type DAC_Select) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->swtrg_bit.d1swtrg = TRUE;
            break;

        case DAC2_Select:
            DAC->swtrg_bit.d2swtrg = TRUE;
            break;

        default:
            break;
    }
}

/**
  * @brief  generate dac dual software trigger synchronously
  * @param  无
  * @retval 无
  */
void DAC_Dual_Software_Trigger_Generate(void) {
    DAC->swtrg |= 0x03;
}

/**
  * @brief  generate dac wave
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @param  DAC_wave
  *         该参数可以是以下值之一:
  *         - DAC_Wave_Generate_NONE
  *         - DAC_Wave_Generate_NOISE
  *         - DAC_Wave_Generate_TRIANGLE
  * @retval 无
  */
void DAC_Wave_Generate(DAC_Select_Type DAC_Select, DAC_Wave_Type DAC_wave) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->ctrl_bit.d1nm = DAC_wave;
            break;

        case DAC2_Select:
            DAC->ctrl_bit.d2nm = DAC_wave;
            break;

        default:
            break;
    }
}

/**
  * @brief  select dac mask amplitude
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @param  DAC_Mask_amplitude
  *         该参数可以是以下值之一:
  *         - DAC_LSFR_BIT0_Amplitude_1
  *         - DAC_LSFR_BIT10_Amplitude_3
  *         - DAC_LSFR_BIT20_Amplitude_7
  *         - DAC_LSFR_BIT30_Amplitude_15
  *         - DAC_LSFR_BIT40_Amplitude_31
  *         - DAC_LSFR_BIT50_Amplitude_63
  *         - DAC_LSFR_BIT60_Amplitude_127
  *         - DAC_LSFR_BIT70_Amplitude_255
  *         - DAC_LSFR_BIT80_Amplitude_511
  *         - DAC_LSFR_BIT90_Amplitude_1023
  *         - DAC_LSFR_BITA0_Amplitude_2047
  *         - DAC_LSFR_BITB0_Amplitude_4095
  * @retval 无
  */
void DAC_Mask_Amplitude_Select(DAC_Select_Type DAC_Select, DAC_Mask_Amplitude_Type DAC_Mask_amplitude) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->ctrl_bit.d1nbsel = DAC_Mask_amplitude;
            break;

        case DAC2_Select:
            DAC->ctrl_bit.d2nbsel = DAC_Mask_amplitude;
            break;

        default:
            break;
    }
}

/**
  * @brief  enable or disable dac dma
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DAC_DMA_Enable(DAC_Select_Type DAC_Select, confirm_state new_state) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->ctrl_bit.d1dmaen = new_state;
            break;

        case DAC2_Select:
            DAC->ctrl_bit.d2dmaen = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  get dac data output
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @retval dac channel data output
  */
uint16_t DAC_Data_OutPut_Get(DAC_Select_Type DAC_Select) {
    uint16_t data_Output = 0;

    switch(DAC_Select) {
        case DAC1_Select:
            data_Output = DAC->d1odt_bit.d1odt;
            break;

        case DAC2_Select:
            data_Output = DAC->d2odt_bit.d2odt;
            break;

        default:
            break;
    }

    return data_Output;
}

/**
  * @brief  set dac1 data
  * @param  dac1_aligned
  *         该参数可以是以下值之一:
  *         DAC1_12BIT_RIGHT
  *         DAC1_12BIT_LEFT
  *         DAC1_8BIT_RIGHT
  * @param  dac1_data :indecate from selected data holding register
  * @retval 无
  */
void DAC_1_Data_Set(dac1_Aligned_Data_Type dac1_aligned, uint16_t dac1_data) {
    *(__IO uint32_t *) dac1_aligned = dac1_data;
}

/**
  * @brief  set dac2 data
  * @param  dac2_aligned
  *         该参数可以是以下值之一:
  *         DAC2_12BIT_RIGHT
  *         DAC2_12BIT_LEFT
  *         DAC2_8BIT_RIGHT
  * @param  dac2_data :indecate from selected data holding register
  * @retval 无
  */
void DAC_2_Data_Set(dac2_Aligned_Data_Type dac2_aligned, uint16_t dac2_data) {
    *(__IO uint32_t *) dac2_aligned = dac2_data;
}

/**
  * @brief  set dac dual data
  * @param  DAC_dual
  *         该参数可以是以下值之一:
  *         DAC_Dual_12BIT_RIGHT
  *         DAC_Dual_12BIT_LEFT
  *         DAC_Dual_8BIT_RIGHT
  * @param  data1 :dac1 channel indecate from selected data holding register
  * @param  data2 :dac1 channel indecate from selected data holding register
  * @retval 无
  */
void DAC_Dual_Data_Set(DAC_Dual_Data_Type DAC_dual, uint16_t data1, uint16_t data2) {
    switch(DAC_dual) {
        case DAC_Dual_12BIT_RIGHT:
            *(__IO uint32_t *) DAC_dual = (uint32_t)(data1 | (data2 << 16));
            break;

        case DAC_Dual_12BIT_LEFT:
            *(__IO uint32_t *) DAC_dual = (uint32_t)(data1 | (data2 << 16));
            break;

        case DAC_Dual_8BIT_RIGHT:
            *(__IO uint32_t *) DAC_dual = (uint32_t)(data1 | (data2 << 8));
            break;

        default:
            break;
    }
}

/**
  * @brief  enable/disable dac dma udr interrupt
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void DAC_UDR_Enable(DAC_Select_Type DAC_Select, confirm_state new_state) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->ctrl_bit.d1dmaudrien = new_state;
            break;

        case DAC2_Select:
            DAC->ctrl_bit.d2dmaudrien = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  get flag of the dac udr flag.
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @retval the new state of dac udr flag status(SET or RESET).
  */
flag_status DAC_UDR_Flag_Get(DAC_Select_Type DAC_Select) {
    flag_status status = RESET;

    switch(DAC_Select) {
        case DAC1_Select:
            if(DAC->sts_bit.d1dmaudrf != 0)
                status = SET;

            break;

        case DAC2_Select:
            if(DAC->sts_bit.d2dmaudrf != 0)
                status = SET;

            break;

        default:
            break;
    }

    return status;
}

/**
  * @brief  clear the dac udr flag.
  * @param  DAC_Select
  *         该参数可以是以下值之一:
  *         - DAC1_Select
  *         - DAC2_Select
  * @retval 无
  */
void DAC_UDR_Flag_Clear(DAC_Select_Type DAC_Select) {
    switch(DAC_Select) {
        case DAC1_Select:
            DAC->sts = DAC1_D1DMAUDRF;
            break;

        case DAC2_Select:
            DAC->sts = DAC2_D2DMAUDRF;
            break;

        default:
            break;
    }
}

#endif
