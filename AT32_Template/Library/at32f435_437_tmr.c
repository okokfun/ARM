/**
  **************************************************************************
  * @file     at32f435_437_tmr.c
  * @brief    contains all the functions for the tmr firmware library
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

/** @defgroup TMR
  * @brief TMR driver modules
  */

#ifdef TMR_MODULE_EnableD

/** @defgroup TMR_private_functions
  */

/**
  * @brief  tmr reset by crm reset register
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @retval 无
  */
void TMR_Reset(TMR_Type *TMR_x) {
    if(TMR_x == TMR1) {
        CRM_Periph_Reset(CRM_TMR1_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR1_Periph_Reset, FALSE);
    } else if(TMR_x == TMR2) {
        CRM_Periph_Reset(CRM_TMR2_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR2_Periph_Reset, FALSE);
    } else if(TMR_x == TMR3) {
        CRM_Periph_Reset(CRM_TMR3_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR3_Periph_Reset, FALSE);
    } else if(TMR_x == TMR4) {
        CRM_Periph_Reset(CRM_TMR4_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR4_Periph_Reset, FALSE);
    } else if(TMR_x == TMR5) {
        CRM_Periph_Reset(CRM_TMR5_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR5_Periph_Reset, FALSE);
    } else if(TMR_x == TMR6) {
        CRM_Periph_Reset(CRM_TMR6_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR6_Periph_Reset, FALSE);
    } else if(TMR_x == TMR7) {
        CRM_Periph_Reset(CRM_TMR7_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR7_Periph_Reset, FALSE);
    } else if(TMR_x == TMR8) {
        CRM_Periph_Reset(CRM_TMR8_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR8_Periph_Reset, FALSE);
    } else if(TMR_x == TMR9) {
        CRM_Periph_Reset(CRM_TMR9_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR9_Periph_Reset, FALSE);
    } else if(TMR_x == TMR10) {
        CRM_Periph_Reset(CRM_TMR10_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR10_Periph_Reset, FALSE);
    } else if(TMR_x == TMR11) {
        CRM_Periph_Reset(CRM_TMR11_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR11_Periph_Reset, FALSE);
    } else if(TMR_x == TMR12) {
        CRM_Periph_Reset(CRM_TMR12_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR12_Periph_Reset, FALSE);
    } else if(TMR_x == TMR13) {
        CRM_Periph_Reset(CRM_TMR13_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR13_Periph_Reset, FALSE);
    } else if(TMR_x == TMR14) {
        CRM_Periph_Reset(CRM_TMR14_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR14_Periph_Reset, FALSE);
    } else if(TMR_x == TMR20) {
        CRM_Periph_Reset(CRM_TMR20_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_TMR20_Periph_Reset, FALSE);
    }
}

/**
  * @brief  enable or disable tmr counter
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_Counter_Enable(TMR_Type *TMR_x, confirm_state new_state) {
    /* tmr counter enable  */
    TMR_x->ctrl1_bit.tmren = new_state;
}

/**
  * @brief  init tmr output default para
  * @param  TMR_OutPut_struct
  *         - to the structure of TMR_OutPut_Config_Type
  * @retval 无
  */
void TMR_OutPut_Default_Para_Init(TMR_OutPut_Config_Type *TMR_OutPut_struct) {
    TMR_OutPut_struct->oc_Mode = TMR_OutPut_Control_OFF;
    TMR_OutPut_struct->oc_idle_state = FALSE;
    TMR_OutPut_struct->occ_idle_state = FALSE;
    TMR_OutPut_struct->oc_polarity = TMR_OutPut_ACTIVE_HIGH;
    TMR_OutPut_struct->occ_polarity = TMR_OutPut_ACTIVE_HIGH;
    TMR_OutPut_struct->oc_OutPut_state = FALSE;
    TMR_OutPut_struct->occ_OutPut_state = FALSE;
}

/**
  * @brief  init tmr input default para
  * @param  TMR_Input_struct
  *         - to the structure of TMR_Input_Config_Type
  * @retval 无
  */
void TMR_Input_Default_Para_Init(TMR_Input_Config_Type *TMR_Input_struct) {
    TMR_Input_struct->input_Channel_Select = TMR_Select_Channel_1;
    TMR_Input_struct->input_Polarity_Select = TMR_Input_RISING_EDGE;
    TMR_Input_struct->input_mapped_Select = TMR_CC_Channel_MAPPED_DIRECT;
    TMR_Input_struct->input_Filter_value = 0x0;
}

/**
  * @brief  init tmr brkdt default para
  * @param  TMR_Brkdt_struct
  *         - to the structure of TMR_Brkdt_Config_Type
  * @retval 无
  */
void TMR_Brkdt_Default_Para_Init(TMR_Brkdt_Config_Type *TMR_Brkdt_struct) {
    TMR_Brkdt_struct->deadtime = 0x0;
    TMR_Brkdt_struct->brk_polarity = TMR_BRK_Input_ACTIVE_LOW;
    TMR_Brkdt_struct->wp_level = TMR_WP_OFF;
    TMR_Brkdt_struct->auto_OutPut_Enable = FALSE ;
    TMR_Brkdt_struct->fcsoen_state = FALSE ;
    TMR_Brkdt_struct->fcsodis_state = FALSE ;
    TMR_Brkdt_struct->brk_Enable = FALSE ;
}

/**
  * @brief  init tmr base
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_pr (for 16 bit tmr 0x0000~0xFFFF,
  *                  for 32 bit tmr 0x0000_0000~0xFFFF_FFFF)
  * @param  TMR_div (timer div value:0x0000~0xFFFF)
  * @retval 无
  */
void TMR_Base_Init(TMR_Type* TMR_x, uint32_t TMR_pr, uint32_t TMR_div) {
    /* set the pr value */
    TMR_x->pr = TMR_pr;

    /* set the div value */
    TMR_x->div = TMR_div;

    /* trigger the overflow event to immediately reload pr value and div value */
    TMR_x->swevt_bit.ovfswtr = TRUE;
}

/**
  * @brief  set tmr clock source division
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Clock_div
  *         该参数可以是以下值之一:
  *         - TMR_Clock_DIV1
  *         - TMR_Clock_DIV2
  *         - TMR_Clock_DIV4
  * @retval 无
  */
void TMR_Clock_Source_Div_Set(TMR_Type *TMR_x, TMR_Clock_Division_Type TMR_Clock_div) {
    /* set tmr clock source division */
    TMR_x->ctrl1_bit.clkdiv = TMR_Clock_div;
}

/**
  * @brief  set tmr counter count direction
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_CNT_dir
  *         该参数可以是以下值之一:
  *         - TMR_Count_UP
  *         - TMR_Count_DOWN
  *         - TMR_Count_TWO_WAY_1
  *         - TMR_Count_TWO_WAY_2
  *         - TMR_Count_TWO_WAY_3
  * @retval 无
  */
void TMR_CNT_Dir_Set(TMR_Type *TMR_x, TMR_Count_Mode_Type TMR_CNT_dir) {
    /* set the cnt direct */
    TMR_x->ctrl1_bit.cnt_dir = TMR_CNT_dir;
}

/**
  * @brief  set the repetition counter register(rpr) value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR8, TMR20
  * @param  TMR_rpr_value (0x0000~0xFFFF)
  * @retval 无
  */
void TMR_Repetition_Counter_Set(TMR_Type *TMR_x, uint8_t TMR_rpr_value) {
    /* set the repetition counter value */
    TMR_x->rpr_bit.rpr = TMR_rpr_value;
}

/**
  * @brief  set tmr counter value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_CNT_value (for 16 bit tmr 0x0000~0xFFFF,
  *                        for 32 bit tmr 0x0000_0000~0xFFFF_FFFF)
  * @retval 无
  */
void TMR_Counter_Value_Set(TMR_Type *TMR_x, uint32_t TMR_CNT_value) {
    /* set the tmr counter value */
    TMR_x->cval = TMR_CNT_value;
}

/**
  * @brief  get tmr counter value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @retval tmr counter value
  */
uint32_t TMR_Counter_Value_Get(TMR_Type *TMR_x) {
    return TMR_x->cval;
}

/**
  * @brief  set tmr div value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Div_value (for 16 bit tmr 0x0000~0xFFFF,
  *                        for 32 bit tmr 0x0000_0000~0xFFFF_FFFF)
  * @retval 无
  */
void TMR_Div_Value_Set(TMR_Type *TMR_x, uint32_t TMR_Div_value) {
    /* set the tmr div value */
    TMR_x->div = TMR_Div_value;
}

/**
  * @brief  get tmr div value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @retval tmr div value
  */
uint32_t TMR_Div_Value_Get(TMR_Type *TMR_x) {
    return TMR_x->div;
}

/**
  * @brief  config tmr output channel
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_5
  * @param  TMR_OutPut_struct
  *         - to the structure of TMR_OutPut_Config_Type
  * @retval 无
  */
void TMR_OutPut_Channel_Config(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                               TMR_OutPut_Config_Type *TMR_OutPut_struct) {
    uint16_t channel_index = 0, channel_c_index = 0, channel = 0, chx_offset, chcx_offset;

    chx_offset = (8 + TMR_Channel);
    chcx_offset = (9 + TMR_Channel);

    /* get channel idle state bit position in ctrl2 register */
    channel_index = (uint16_t)(TMR_OutPut_struct->oc_idle_state << chx_offset);

    /* get channel complementary idle state bit position in ctrl2 register */
    channel_c_index = (uint16_t)(TMR_OutPut_struct->occ_idle_state << chcx_offset);

    /* set output channel complementary idle state */
    TMR_x->ctrl2 &= ~(1 << chcx_offset);
    TMR_x->ctrl2 |= channel_c_index;

    /* set output channel idle state */
    TMR_x->ctrl2 &= ~(1 << chx_offset);
    TMR_x->ctrl2 |= channel_index;

    /* set channel output mode */
    channel = TMR_Channel;

    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cm1_OutPut_bit.c1octrl = TMR_OutPut_struct->oc_Mode;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cm1_OutPut_bit.c2octrl = TMR_OutPut_struct->oc_Mode;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cm2_OutPut_bit.c3octrl = TMR_OutPut_struct->oc_Mode;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cm2_OutPut_bit.c4octrl = TMR_OutPut_struct->oc_Mode;
            break;

        case TMR_Select_Channel_5:
            TMR_x->cm3_OutPut_bit.c5octrl = TMR_OutPut_struct->oc_Mode;
            break;

        default:
            break;
    }

    chx_offset = ((TMR_Channel * 2) + 1);
    chcx_offset = ((TMR_Channel * 2) + 3);

    /* get channel polarity bit position in cctrl register */
    channel_index = (uint16_t)(TMR_OutPut_struct->oc_polarity << chx_offset);

    /* get channel complementary polarity bit position in cctrl register */
    channel_c_index = (uint16_t)(TMR_OutPut_struct->occ_polarity << chcx_offset);

    /* set output channel complementary polarity */
    TMR_x->cctrl &= ~(1 << chcx_offset);
    TMR_x->cctrl |= channel_c_index;

    /* set output channel polarity */
    TMR_x->cctrl &= ~(1 << chx_offset);
    TMR_x->cctrl |= channel_index;

    chx_offset = (TMR_Channel * 2);
    chcx_offset = ((TMR_Channel * 2) + 2);

    /* get channel enable bit position in cctrl register */
    channel_index = (uint16_t)(TMR_OutPut_struct->oc_OutPut_state << (TMR_Channel * 2));

    /* get channel complementary enable bit position in cctrl register */
    channel_c_index = (uint16_t)(TMR_OutPut_struct->occ_OutPut_state << ((TMR_Channel * 2) + 2));

    /* set output channel complementary enable bit */
    TMR_x->cctrl &= ~(1 << chcx_offset);
    TMR_x->cctrl |= channel_c_index;

    /* set output channel enable bit */
    TMR_x->cctrl &= ~(1 << chx_offset);
    TMR_x->cctrl |= channel_index;
}

/**
  * @brief  select tmr output channel mode
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_5
  * @param  oc_Mode
  *         该参数可以是以下值之一:
  *         - TMR_OutPut_Control_OFF
  *         - TMR_OutPut_Control_HIGH
  *         - TMR_OutPut_Control_LOW
  *         - TMR_OutPut_Control_Switch
  *         - TMR_OutPut_Control_Force_HIGH
  *         - TMR_OutPut_Control_Force_LOW
  *         - TMR_OutPut_Control_PWM_Mode_A
  *         - TMR_OutPut_Control_PWM_Mode_B
  * @retval 无
  */
void TMR_OutPut_Channel_Mode_Select(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                                    TMR_OutPut_Control_Mode_Type oc_Mode) {
    uint16_t channel;

    channel = TMR_Channel;

    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cm1_OutPut_bit.c1octrl = oc_Mode;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cm1_OutPut_bit.c2octrl = oc_Mode;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cm2_OutPut_bit.c3octrl = oc_Mode;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cm2_OutPut_bit.c4octrl = oc_Mode;
            break;

        case TMR_Select_Channel_5:
            TMR_x->cm3_OutPut_bit.c5octrl = oc_Mode;
            break;

        default:
            break;
    }
}
/**
  * @brief  set tmr period value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_pr_value: timer period register value of counter
  *                       (for 16 bit tmr 0x0000~0xFFFF,
  *                       for 32 bit tmr 0x0000_0000~0xFFFF_FFFF)
  * @retval 无
  */
void TMR_Period_Value_Set(TMR_Type *TMR_x, uint32_t TMR_pr_value) {
    /* set tmr period value */
    TMR_x->pr = TMR_pr_value;
}

/**
  * @brief  get tmr period value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @retval timer period register value of counter
  *         (for 16 bit tmr 0x0000~0xFFFF, for 32 bit tmr
  *         0x0000_0000~0xFFFF_FFFF)
  */
uint32_t TMR_Period_Value_Get(TMR_Type *TMR_x) {
    return TMR_x->pr;
}

/**
  * @brief  set tmr channel value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_5
  * @param  TMR_Channel_value (for 16 bit tmr 0x0000~0xFFFF,
  *                       for 32 bit tmr 0x0000_0000~0xFFFF_FFFF)
  * @retval 无
  */
void TMR_Channel_Value_Set(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                           uint32_t TMR_Channel_value) {
    uint16_t channel;

    channel = TMR_Channel;

    /* set tmr channel value */
    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->c1dt = TMR_Channel_value;
            break;

        case TMR_Select_Channel_2:
            TMR_x->c2dt = TMR_Channel_value;
            break;

        case TMR_Select_Channel_3:
            TMR_x->c3dt = TMR_Channel_value;
            break;

        case TMR_Select_Channel_4:
            TMR_x->c4dt = TMR_Channel_value;
            break;

        case TMR_Select_Channel_5:
            TMR_x->c5dt = TMR_Channel_value;
            break;

        default:
            break;
    }
}

/**
  * @brief  get tmr channel value
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_5
  * @retval tmr channel value
  */
uint32_t TMR_Channel_Value_Get(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel) {
    uint32_t cc_Value_Get = 0;
    uint16_t channel;

    channel = TMR_Channel;

    /* get tmr channel value */
    switch(channel) {
        case TMR_Select_Channel_1:
            cc_Value_Get = TMR_x->c1dt;
            break;

        case TMR_Select_Channel_2:
            cc_Value_Get = TMR_x->c2dt;
            break;

        case TMR_Select_Channel_3:
            cc_Value_Get = TMR_x->c3dt;
            break;

        case TMR_Select_Channel_4:
            cc_Value_Get = TMR_x->c4dt;
            break;

        case TMR_Select_Channel_5:
            cc_Value_Get = TMR_x->c5dt;
            break;

        default:
            break;
    }

    return cc_Value_Get;
}
/**
  * @brief  set tmr period buffer
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_Period_Buffer_Enable(TMR_Type *TMR_x, confirm_state new_state) {
    /* tmr period buffer set */
    TMR_x->ctrl1_bit.prben = new_state;
}

/**
  * @brief  set tmr output channel buffer
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_5
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_OutPut_Channel_Buffer_Enable(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                                      confirm_state new_state) {
    uint16_t channel;

    channel = TMR_Channel;

    /* get tmr channel value */
    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cm1_OutPut_bit.c1oben = new_state;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cm1_OutPut_bit.c2oben = new_state;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cm2_OutPut_bit.c3oben = new_state;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cm2_OutPut_bit.c4oben = new_state;
            break;

        case TMR_Select_Channel_5:
            TMR_x->cm3_OutPut_bit.c5oben = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  set tmr output channel immediately
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_5
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_OutPut_Channel_Immediately_Set(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                                        confirm_state new_state) {
    uint16_t channel;

    channel = TMR_Channel;

    /* get tmr channel value */
    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cm1_OutPut_bit.c1oien = new_state;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cm1_OutPut_bit.c2oien = new_state;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cm2_OutPut_bit.c3oien = new_state;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cm2_OutPut_bit.c4oien = new_state;
            break;

        case TMR_Select_Channel_5:
            TMR_x->cm3_OutPut_bit.c5oien = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  set tmr output channel switch
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_5
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_OutPut_Channel_Switch_Set(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                                   confirm_state new_state) {
    uint16_t channel;

    channel = TMR_Channel;

    /* get tmr channel value */
    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cm1_OutPut_bit.c1osen = new_state;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cm1_OutPut_bit.c2osen = new_state;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cm2_OutPut_bit.c3osen = new_state;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cm2_OutPut_bit.c4osen = new_state;
            break;

        case TMR_Select_Channel_5:
            TMR_x->cm3_OutPut_bit.c5osen = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  enable or disable tmr one cycle mode
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8, TMR9, TMR12, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_ONE_Cycle_Mode_Enable(TMR_Type *TMR_x, confirm_state new_state) {
    /* tmr one cycle mode enable */
    TMR_x->ctrl1_bit.ocmen = new_state;
}

/**
  * @brief  enable or disable  tmr 32 bit function(plus mode)
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR2, TMR5
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_32_Bit_Function_Enable (TMR_Type *TMR_x, confirm_state new_state) {
    /* tmr 32 bit function(plus mode) enable,only for TMR2/TMR5 */
    if((TMR_x == TMR2) || (TMR_x == TMR5)) {
        TMR_x->ctrl1_bit.pmen = new_state;
    }
}

/**
  * @brief  select tmr the overflow event sources
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_OverFlow_Request_Source_Set(TMR_Type *TMR_x, confirm_state new_state) {
    TMR_x->ctrl1_bit.ovfs = new_state;
}

/**
  * @brief  enable or disable tmr overflow event generation
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_OverFlow_Event_Disable(TMR_Type *TMR_x, confirm_state new_state) {
    TMR_x->ctrl1_bit.ovfen = new_state;
}

/**
  * @brief  init tmr input channel
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  input_struct
  *         - to the structure of TMR_Input_Config_Type
  * @param  divider_factor
  *         该参数可以是以下值之一:
  *         - TMR_Channel_Input_Div_1
  *         - TMR_Channel_Input_Div_2
  *         - TMR_Channel_Input_Div_4
  *         - TMR_Channel_Input_Div_8
  * @retval 无
  */
void TMR_Input_Channel_Init(TMR_Type *TMR_x, TMR_Input_Config_Type *input_struct, \
                            TMR_Channel_Input_Divider_Type divider_factor) {
    uint16_t channel = 0;

    /* get channel selected */
    channel = input_struct->input_Channel_Select;

    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cctrl_bit.c1en       = FALSE;
            TMR_x->cctrl_bit.c1p        = (uint32_t)input_struct->input_Polarity_Select;
            TMR_x->cctrl_bit.c1cp       = (input_struct->input_Polarity_Select & 0x2) >> 1;
            TMR_x->cm1_Input_bit.c1c    = input_struct->input_mapped_Select;
            TMR_x->cm1_Input_bit.c1df   = input_struct->input_Filter_value;
            TMR_x->cm1_Input_bit.c1idiv = divider_factor;
            TMR_x->cctrl_bit.c1en       = TRUE;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cctrl_bit.c2en       = FALSE;
            TMR_x->cctrl_bit.c2p        = (uint32_t)input_struct->input_Polarity_Select;
            TMR_x->cctrl_bit.c2cp       = (input_struct->input_Polarity_Select & 0x2) >> 1;
            TMR_x->cm1_Input_bit.c2c    = input_struct->input_mapped_Select;
            TMR_x->cm1_Input_bit.c2df   = input_struct->input_Filter_value;
            TMR_x->cm1_Input_bit.c2idiv = divider_factor;
            TMR_x->cctrl_bit.c2en       = TRUE;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cctrl_bit.c3en       = FALSE;
            TMR_x->cctrl_bit.c3p        = (uint32_t)input_struct->input_Polarity_Select;
            TMR_x->cctrl_bit.c3cp       = (input_struct->input_Polarity_Select & 0x2) >> 1;
            TMR_x->cm2_Input_bit.c3c    = input_struct->input_mapped_Select;
            TMR_x->cm2_Input_bit.c3df   = input_struct->input_Filter_value;
            TMR_x->cm2_Input_bit.c3idiv = divider_factor;
            TMR_x->cctrl_bit.c3en       = TRUE;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cctrl_bit.c4en       = FALSE;
            TMR_x->cctrl_bit.c4p        = (uint32_t)input_struct->input_Polarity_Select;
            TMR_x->cm2_Input_bit.c4c    = input_struct->input_mapped_Select;
            TMR_x->cm2_Input_bit.c4df   = input_struct->input_Filter_value;
            TMR_x->cm2_Input_bit.c4idiv = divider_factor;
            TMR_x->cctrl_bit.c4en       = TRUE;
            break;

        default:
            break;
    }
}

/**
  * @brief  tmr channel enable
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_1C
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_2C
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_3C
  *         - TMR_Select_Channel_4
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_Channel_Enable(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, confirm_state new_state) {
    uint16_t channel;

    channel = TMR_Channel;

    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cctrl_bit.c1en         = new_state;
            break;

        case TMR_Select_Channel_1C:
            TMR_x->cctrl_bit.c1cen        = new_state;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cctrl_bit.c2en         = new_state;
            break;

        case TMR_Select_Channel_2C:
            TMR_x->cctrl_bit.c2cen        = new_state;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cctrl_bit.c3en         = new_state;
            break;

        case TMR_Select_Channel_3C:
            TMR_x->cctrl_bit.c3cen        = new_state;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cctrl_bit.c4en         = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  set tmr input channel filter
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  * @param  filter_value (0x0~0xf)
  * @retval 无
  */
void TMR_Input_Channel_Filter_Set(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                                  uint16_t filter_value) {
    uint16_t channel;

    channel = TMR_Channel;

    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cm1_Input_bit.c1df = filter_value;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cm1_Input_bit.c2df = filter_value;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cm2_Input_bit.c3df = filter_value;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cm2_Input_bit.c4df = filter_value;
            break;

        default:
            break;
    }
}

/**
  * @brief  config tmr pwm input
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  input_struct
  *         - to the structure of TMR_Input_Config_Type
  * @param  divider_factor
  *         该参数可以是以下值之一:
  *         - TMR_Channel_Input_Div_1
  *         - TMR_Channel_Input_Div_2
  *         - TMR_Channel_Input_Div_4
  *         - TMR_Channel_Input_Div_8
  * @retval 无
  */
void TMR_PWM_Input_Config(TMR_Type *TMR_x, TMR_Input_Config_Type *input_struct, \
                          TMR_Channel_Input_Divider_Type divider_factor) {
    uint16_t channel = 0;

    /* get channel selected */
    channel = input_struct->input_Channel_Select;

    switch(channel) {
        case TMR_Select_Channel_1:
            if(input_struct->input_Polarity_Select == TMR_Input_RISING_EDGE) {
                /* set channel polarity */
                TMR_x->cctrl_bit.c1p          = TMR_Input_RISING_EDGE;
                TMR_x->cctrl_bit.c2p          = TMR_Input_FALLING_EDGE;
            } else if(input_struct->input_Polarity_Select == TMR_Input_FALLING_EDGE) {
                /* set channel polarity */
                TMR_x->cctrl_bit.c1p          = TMR_Input_FALLING_EDGE;
                TMR_x->cctrl_bit.c2p          = TMR_Input_RISING_EDGE;
            }

            if(input_struct->input_mapped_Select == TMR_CC_Channel_MAPPED_DIRECT) {
                /* ic1 is mapped on ti1 */
                TMR_x->cm1_Input_bit.c1c = TMR_CC_Channel_MAPPED_DIRECT;

                /* ic1 is mapped on ti2 */
                TMR_x->cm1_Input_bit.c2c = TMR_CC_Channel_MAPPED_INDIRECT;
            } else if(input_struct->input_mapped_Select == TMR_CC_Channel_MAPPED_INDIRECT) {
                /* ic1 is mapped on ti1 */
                TMR_x->cm1_Input_bit.c1c = TMR_CC_Channel_MAPPED_INDIRECT;

                /* ic1 is mapped on ti2 */
                TMR_x->cm1_Input_bit.c2c = TMR_CC_Channel_MAPPED_DIRECT;
            }

            /* set input ch1 and ch2 filter value*/
            TMR_x->cm1_Input_bit.c1df = input_struct->input_Filter_value;
            TMR_x->cm1_Input_bit.c2df = input_struct->input_Filter_value;

            /*set input ch1 and ch2 divider value*/
            TMR_x->cm1_Input_bit.c1idiv = divider_factor;
            TMR_x->cm1_Input_bit.c2idiv = divider_factor;

            TMR_x->cctrl_bit.c1en = TRUE;
            TMR_x->cctrl_bit.c2en = TRUE;
            break;

        case TMR_Select_Channel_2:
            if(input_struct->input_Polarity_Select == TMR_Input_RISING_EDGE) {
                /* set channel polarity */
                TMR_x->cctrl_bit.c2p          = TMR_Input_RISING_EDGE;
                TMR_x->cctrl_bit.c1p          = TMR_Input_FALLING_EDGE;
            } else if(input_struct->input_Polarity_Select == TMR_Input_FALLING_EDGE) {
                /* set channel polarity */
                TMR_x->cctrl_bit.c2p          = TMR_Input_FALLING_EDGE;
                TMR_x->cctrl_bit.c1p          = TMR_Input_RISING_EDGE;
            }

            if(input_struct->input_mapped_Select == TMR_CC_Channel_MAPPED_DIRECT) {
                /* set mapped direct */
                TMR_x->cm1_Input_bit.c2c = TMR_CC_Channel_MAPPED_DIRECT;
                TMR_x->cm1_Input_bit.c1c = TMR_CC_Channel_MAPPED_INDIRECT;
            } else if(input_struct->input_mapped_Select == TMR_CC_Channel_MAPPED_INDIRECT) {
                /* set mapped direct */
                TMR_x->cm1_Input_bit.c2c = TMR_CC_Channel_MAPPED_INDIRECT;
                TMR_x->cm1_Input_bit.c1c = TMR_CC_Channel_MAPPED_DIRECT;
            }

            /* set input ch1 and ch2 filter value*/
            TMR_x->cm1_Input_bit.c1df = input_struct->input_Filter_value;
            TMR_x->cm1_Input_bit.c2df = input_struct->input_Filter_value;

            /*set input ch1 and ch2 divider value*/
            TMR_x->cm1_Input_bit.c1idiv = divider_factor;
            TMR_x->cm1_Input_bit.c2idiv = divider_factor;

            TMR_x->cctrl_bit.c1en = TRUE;
            TMR_x->cctrl_bit.c2en = TRUE;
            break;

        default:
            break;
    }
}

/**
  * @brief  select tmr channel1 input
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR20
  * @param  ch1_Connect
  *         该参数可以是以下值之一:
  *         - TMR_CHANEL1_ConnectED_C1IRAW
  *         - TMR_CHANEL1_2_3_ConnectED_C1IRAW_XOR
  * @retval 无
  */
void TMR_Channel1_Input_Select(TMR_Type *TMR_x, TMR_Channel1_Input_Connected_Type ch1_Connect) {
    TMR_x->ctrl2_bit.c1insel = ch1_Connect;
}

/**
  * @brief  set tmr input channel divider
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  * @param  divider_factor
  *         该参数可以是以下值之一:
  *         - TMR_Channel_Input_Div_1
  *         - TMR_Channel_Input_Div_2
  *         - TMR_Channel_Input_Div_4
  *         - TMR_Channel_Input_Div_8
  * @retval 无
  */
void TMR_Input_Channel_Divider_Set(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                                   TMR_Channel_Input_Divider_Type divider_factor) {
    uint16_t channel;

    channel = TMR_Channel;

    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cm1_Input_bit.c1idiv = divider_factor;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cm1_Input_bit.c2idiv = divider_factor;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cm2_Input_bit.c3idiv = divider_factor;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cm2_Input_bit.c4idiv = divider_factor;
            break;

        default:
            break;
    }
}

/**
  * @brief  select tmr primary mode
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8, TMR20
  * @param  primary_Mode
  *         该参数可以是以下值之一:
  *         - TMR_Primary_SEL_Reset
  *         - TMR_Primary_SEL_Enable
  *         - TMR_Primary_SEL_OVERFLOW
  *         - TMR_Primary_SEL_COMPARE
  *         - TMR_Primary_SEL_C1ORAW
  *         - TMR_Primary_SEL_C2ORAW
  *         - TMR_Primary_SEL_C3ORAW
  *         - TMR_Primary_SEL_C4ORAW
  * @retval 无
  */
void TMR_Primary_Mode_Select(TMR_Type *TMR_x, TMR_Primary_Select_Type primary_Mode) {
    TMR_x->ctrl2_bit.ptos = primary_Mode;
}

/**
  * @brief  select tmr subordinate mode
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR12, TMR20
  * @param  sub_Mode
  *         该参数可以是以下值之一:
  *         - TMR_Sub_Mode_DIABLE
  *         - TMR_Sub_Encoder_Mode_A
  *         - TMR_Sub_Encoder_Mode_B
  *         - TMR_Sub_Encoder_Mode_C
  *         - TMR_Sub_Reset_Mode
  *         - TMR_Sub_HANG_Mode
  *         - TMR_Sub_Trigger_Mode
  *         - TMR_Sub_External_Clock_Mode_A

  * @retval 无
  */
void TMR_Sub_Mode_Select(TMR_Type *TMR_x, TMR_Sub_Mode_Select_Type sub_Mode) {
    TMR_x->stctrl_bit.smsel = sub_Mode;
}

/**
  * @brief  select tmr channel dma
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR12, TMR20
  * @param  cc_DMA_Select
  *         该参数可以是以下值之一:
  *         - TMR_DMA_Request_BY_ChanneL
  *         - TMR_DMA_Request_BY_OVERFLOW
  * @retval 无
  */
void TMR_Channel_DMA_Select(TMR_Type *TMR_x, TMR_DMA_Request_Source_Type cc_DMA_Select) {
    TMR_x->ctrl2_bit.drs = cc_DMA_Select;
}

/**
  * @brief  select tmr hall
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR8, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_Hall_Select(TMR_Type *TMR_x,  confirm_state new_state) {
    TMR_x->ctrl2_bit.ccfs = new_state;
}

/**
  * @brief  select tmr channel buffer
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR8, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_Channel_Buffer_Enable(TMR_Type *TMR_x, confirm_state new_state) {
    TMR_x->ctrl2_bit.cbctrl = new_state;
}

/**
  * @brief  select tmr trgout2
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR8, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_Trgout2_Enable(TMR_Type *TMR_x, confirm_state new_state) {
    TMR_x->ctrl2_bit.trgout2en = new_state;
}

/**
  * @brief  select tmr sub-trigger
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR12, TMR20
  * @param  trigger_Select
  *         该参数可以是以下值之一:
  *         - TMR_Sub_Input_SEL_IS0
  *         - TMR_Sub_Input_SEL_IS1
  *         - TMR_Sub_Input_SEL_IS2
  *         - TMR_Sub_Input_SEL_IS3
  *         - TMR_Sub_Input_SEL_C1INC
  *         - TMR_Sub_Input_SEL_C1DF1
  *         - TMR_Sub_Input_SEL_C2DF2
  *         - TMR_Sub_Input_SEL_EXTIN
  * @retval 无
  */
void TMR_Trigger_Input_Select(TMR_Type *TMR_x, sub_TMR_Input_sel_Type trigger_Select) {
    TMR_x->stctrl_bit.stis = trigger_Select;
}

/**
  * @brief  set tmr subordinate synchronization mode
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR12, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_Sub_Sync_Mode_Set(TMR_Type *TMR_x, confirm_state new_state) {
    TMR_x->stctrl_bit.sts = new_state;
}

/**
  * @brief  enable or disable tmr dma request
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  DMA_request
  *         该参数可以是以下值之一:
  *         - TMR_OverFlow_DMA_REQUEST
  *         - TMR_C1_DMA_REQUEST
  *         - TMR_C2_DMA_REQUEST
  *         - TMR_C3_DMA_REQUEST
  *         - TMR_C4_DMA_REQUEST
  *         - TMR_Hall_DMA_REQUEST
  *         - TMR_Trigger_DMA_REQUEST
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_DMA_Request_Enable(TMR_Type *TMR_x, TMR_DMA_Request_Type DMA_request, confirm_state new_state) {
    if(new_state == TRUE) {
        TMR_x->iden |= DMA_request;
    } else if(new_state == FALSE) {
        TMR_x->iden &= ~DMA_request;
    }
}

/**
  * @brief  enable or disable tmr interrupt
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Interrupt
  *         该参数可以是以下值之一:
  *         - TMR_OVF_INT
  *         - TMR_C1_INT
  *         - TMR_C2_INT
  *         - TMR_C3_INT
  *         - TMR_C4_INT
  *         - TMR_Hall_INT
  *         - TMR_Trigger_INT
  *         - TMR_BRK_INT
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_Interrupt_Enable(TMR_Type *TMR_x, uint32_t TMR_Interrupt, confirm_state new_state) {
    if(new_state == TRUE) {
        TMR_x->iden |= TMR_Interrupt;
    } else if(new_state == FALSE) {
        TMR_x->iden &= ~TMR_Interrupt;
    }
}

/**
  * @brief  get tmr flag
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_flag
  *         该参数可以是以下值之一:
  *         - TMR_OVF_FLAG
  *         - TMR_C1_FLAG
  *         - TMR_C2_FLAG
  *         - TMR_C3_FLAG
  *         - TMR_C4_FLAG
  *         - TMR_C5_FLAG
  *         - TMR_Hall_FLAG
  *         - TMR_Trigger_FLAG
  *         - TMR_BRK_FLAG
  *         - TMR_C1_RECAPTURE_FLAG
  *         - TMR_C2_RECAPTURE_FLAG
  *         - TMR_C3_RECAPTURE_FLAG
  *         - TMR_C4_RECAPTURE_FLAG
  * @retval state of tmr flag
  */
flag_status TMR_Flag_Get(TMR_Type *TMR_x, uint32_t TMR_flag) {
    flag_status status = RESET;

    if((TMR_x->ists & TMR_flag) != RESET) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/**
  * @brief  clear tmr flag
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_flag
  *         该参数可以是以下值的任意组合:
  *         - TMR_OVF_FLAG
  *         - TMR_C1_FLAG
  *         - TMR_C2_FLAG
  *         - TMR_C3_FLAG
  *         - TMR_C4_FLAG
  *         - TMR_C5_FLAG
  *         - TMR_Hall_FLAG
  *         - TMR_Trigger_FLAG
  *         - TMR_BRK_FLAG
  *         - TMR_C1_RECAPTURE_FLAG
  *         - TMR_C2_RECAPTURE_FLAG
  *         - TMR_C3_RECAPTURE_FLAG
  *         - TMR_C4_RECAPTURE_FLAG
  * @retval 无
  */
void TMR_Flag_Clear(TMR_Type *TMR_x, uint32_t TMR_flag) {
    TMR_x->ists = ~TMR_flag;
}

/**
  * @brief  generate tmr event
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR6, TMR7, TMR8,
  *         TMR9, TMR10, TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_event
  *         该参数可以是以下值之一:
  *         - TMR_OverFlow_SWTRIG
  *         - TMR_C1_SWTRIG
  *         - TMR_C2_SWTRIG
  *         - TMR_C3_SWTRIG
  *         - TMR_C4_SWTRIG
  *         - TMR_Hall_SWTRIG
  *         - TMR_Trigger_SWTRIG
  *         - TMR_BRK_SWTRIG
  * @retval 无
  */
void TMR_Event_SW_trigger(TMR_Type *TMR_x, TMR_Event_Trigger_Type TMR_event) {
    TMR_x->swevt |= TMR_event;
}

/**
  * @brief  tmr output enable(oen),this function is important for advtm output enable
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR8, TMR20
  * @param  new_state (TRUE or FALSE)
  * @retval 无
  */
void TMR_OutPut_Enable(TMR_Type *TMR_x, confirm_state new_state) {
    TMR_x->brk_bit.oen = new_state;
}

/**
  * @brief  set tmr select internal clock
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR12, TMR20
  * @retval 无
  */
void TMR_Internal_Clock_Set(TMR_Type *TMR_x) {
    TMR_x->stctrl_bit.smsel = TMR_Sub_Mode_DIABLE;
}

/**
  * @brief  set tmr output channel polarity
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_1C
  *         - TMR_Select_Channel_2C
  *         - TMR_Select_Channel_3C
  * @param  oc_polarity
  *         该参数可以是以下值之一:
  *         - TMR_Polarity_ACTIVE_HIGH
  *         - TMR_Polarity_ACTIVE_LOW
  * @retval 无
  */
void TMR_OutPut_Channel_Polarity_Set(TMR_Type *TMR_x, TMR_Channel_Select_Type TMR_Channel, \
                                     TMR_Polarity_active_Type oc_polarity) {
    uint16_t channel;

    channel = TMR_Channel;

    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cctrl_bit.c1p = (uint32_t)oc_polarity;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cctrl_bit.c2p = (uint32_t)oc_polarity;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cctrl_bit.c3p = (uint32_t)oc_polarity;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cctrl_bit.c4p = (uint32_t)oc_polarity;
            break;

        case TMR_Select_Channel_1C:
            TMR_x->cctrl_bit.c1cp = (uint32_t)oc_polarity;
            break;

        case TMR_Select_Channel_2C:
            TMR_x->cctrl_bit.c2cp = (uint32_t)oc_polarity;
            break;

        case TMR_Select_Channel_3C:
            TMR_x->cctrl_bit.c3cp = (uint32_t)oc_polarity;
            break;

        default:
            break;
    }
}

/**
  * @brief  config tmr external clock
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR20
  * @param  es_divide
  *         该参数可以是以下值之一:
  *         - TMR_ES_Frequency_Div_1
  *         - TMR_ES_Frequency_Div_2
  *         - TMR_ES_Frequency_Div_4
  *         - TMR_ES_Frequency_Div_8
  * @param  es_polarity
  *         该参数可以是以下值之一:
  *         - TMR_ES_Polarity_NON_INVERTED
  *         - TMR_ES_Polarity_INVERTED
  * @param  es_filter (0x0~0xf)
  * @retval 无
  */
void TMR_External_Clock_Config(TMR_Type *TMR_x, TMR_External_signal_Divider_Type es_divide, \
                               TMR_External_signal_Polarity_Type  es_polarity, uint16_t es_filter) {
    TMR_x->stctrl_bit.esdiv = es_divide;
    TMR_x->stctrl_bit.esp = es_polarity;
    TMR_x->stctrl_bit.esf = es_filter;
}

/**
  * @brief  config tmr external clock mode1
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR12, TMR20
  * @param  es_divide
  *         该参数可以是以下值之一:
  *         - TMR_ES_Frequency_Div_1
  *         - TMR_ES_Frequency_Div_2
  *         - TMR_ES_Frequency_Div_4
  *         - TMR_ES_Frequency_Div_8
  * @param  es_polarity
  *         该参数可以是以下值之一:
  *         - TMR_ES_Polarity_NON_INVERTED
  *         - TMR_ES_Polarity_INVERTED
  * @param  es_filter (0x0~0xf)
  * @retval 无
  */
void TMR_External_Clock_Mode1_Config(TMR_Type *TMR_x, TMR_External_signal_Divider_Type es_divide, \
                                     TMR_External_signal_Polarity_Type  es_polarity, uint16_t es_filter) {
    TMR_External_Clock_Config(TMR_x, es_divide, es_polarity, es_filter);
    TMR_x->stctrl_bit.smsel = TMR_Sub_External_Clock_Mode_A;
    TMR_x->stctrl_bit.stis = TMR_Sub_Input_SEL_EXTIN;
}

/**
  * @brief  config tmr external clock mode2
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR20
  * @param  es_divide
  *         该参数可以是以下值之一:
  *         - TMR_ES_Frequency_Div_1
  *         - TMR_ES_Frequency_Div_2
  *         - TMR_ES_Frequency_Div_4
  *         - TMR_ES_Frequency_Div_8
  * @param  es_polarity
  *         该参数可以是以下值之一:
  *         - TMR_ES_Polarity_NON_INVERTED
  *         - TMR_ES_Polarity_INVERTED
  * @param  es_filter (0x0~0xf)
  * @retval 无
  */
void TMR_External_Clock_Mode2_Config(TMR_Type *TMR_x, TMR_External_signal_Divider_Type es_divide, \
                                     TMR_External_signal_Polarity_Type  es_polarity, uint16_t es_filter) {
    TMR_External_Clock_Config(TMR_x, es_divide, es_polarity, es_filter);
    TMR_x->stctrl_bit.ecmben = TRUE;
}

/**
  * @brief  config tmr encoder mode
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR20
  * @param  encoder_Mode
  *         该参数可以是以下值之一:
  *         - TMR_Encoder_Mode_A
  *         - TMR_Encoder_Mode_B
  *         - TMR_Encoder_Mode_C
  * @param  ic1_polarity
  *         该参数可以是以下值之一:
  *         - TMR_Input_RISING_EDGE
  *         - TMR_Input_FALLING_EDGE
  *         - TMR_Input_BOTH_EDGE
  * @param  ic2_polarity
  *         该参数可以是以下值之一:
  *         - TMR_Input_RISING_EDGE
  *         - TMR_Input_FALLING_EDGE
  *         - TMR_Input_BOTH_EDGE
  * @retval 无
  */
void TMR_Encoder_Mode_Config(TMR_Type *TMR_x, TMR_Encoder_Mode_Type encoder_Mode, TMR_Input_Polarity_Type \
                             ic1_polarity, TMR_Input_Polarity_Type ic2_polarity) {
    TMR_x->stctrl_bit.smsel = encoder_Mode;

    /* set ic1 polarity */
    TMR_x->cctrl_bit.c1p =  (ic1_polarity & 0x1);
    TMR_x->cctrl_bit.c1cp = (ic1_polarity >> 1);
    /* set ic1 as input channel */
    TMR_x->cm1_Input_bit.c1c = TMR_CC_Channel_MAPPED_DIRECT;

    /* set ic2 polarity */
    TMR_x->cctrl_bit.c2p =  (ic2_polarity & 0x1);
    TMR_x->cctrl_bit.c2cp = (ic2_polarity >> 1);
    /* set ic2 as input channel */
    TMR_x->cm1_Input_bit.c2c = TMR_CC_Channel_MAPPED_DIRECT;
}

/**
  * @brief  set tmr force output
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR9, TMR10,
  *         TMR11, TMR12, TMR13, TMR14, TMR20
  * @param  TMR_Channel
  *         该参数可以是以下值之一:
  *         - TMR_Select_Channel_1
  *         - TMR_Select_Channel_2
  *         - TMR_Select_Channel_3
  *         - TMR_Select_Channel_4
  *         - TMR_Select_Channel_5
  * @param  force_Output
  *         该参数可以是以下值之一:
  *         - TMR_Force_OutPut_HIGH
  *         - TMR_Force_OutPut_LOW
  * @retval 无
  */
void TMR_Force_OutPut_Set(TMR_Type *TMR_x,  TMR_Channel_Select_Type TMR_Channel, \
                          TMR_Force_OutPut_Type force_Output) {
    uint16_t channel;

    channel = TMR_Channel;

    switch(channel) {
        case TMR_Select_Channel_1:
            TMR_x->cm1_OutPut_bit.c1octrl = force_Output;
            break;

        case TMR_Select_Channel_2:
            TMR_x->cm1_OutPut_bit.c2octrl = force_Output;
            break;

        case TMR_Select_Channel_3:
            TMR_x->cm2_OutPut_bit.c3octrl = force_Output;
            break;

        case TMR_Select_Channel_4:
            TMR_x->cm2_OutPut_bit.c4octrl = force_Output;
            break;

        case TMR_Select_Channel_5:
            TMR_x->cm3_OutPut_bit.c5octrl = force_Output;
            break;

        default:
            break;
    }
}

/**
  * @brief  config tmr dma control
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR2, TMR3, TMR4, TMR5, TMR8, TMR20
  * @param  DMA_length
  *         该参数可以是以下值之一:
  *         - TMR_DMA_Transfer_1BYTE
  *         - TMR_DMA_Transfer_2BYTES
  *         - TMR_DMA_Transfer_3BYTES
  *         ...
  *         - TMR_DMA_Transfer_17BYTES
  *         - TMR_DMA_Transfer_18BYTES
  * @param  DMA_Base_Address
  *         该参数可以是以下值之一:
  *         - TMR_CTRL1_Address
  *         - TMR_CTRL2_Address
  *         - TMR_STCTRL_Address
  *         - TMR_IDEN_Address
  *         - TMR_ISTS_Address
  *         - TMR_SWEVT_Address
  *         - TMR_CM1_Address
  *         - TMR_CM2_Address
  *         - TMR_CCTRL_Address
  *         - TMR_CVAL_Address
  *         - TMR_Div_Address
  *         - TMR_PR_Address
  *         - TMR_RPR_Address
  *         - TMR_C1DT_Address
  *         - TMR_C2DT_Address
  *         - TMR_C3DT_Address
  *         - TMR_C4DT_Address
  *         - TMR_BRK_Address
  *         - TMR_DMACTRL_Address
  * @retval 无
  */
void TMR_DMA_Control_Config(TMR_Type *TMR_x, TMR_DMA_Transfer_Length_Type DMA_length, \
                            TMR_DMA_Address_Type DMA_Base_Address) {
    TMR_x->dmactrl_bit.dtb = DMA_length;
    TMR_x->dmactrl_bit.addr = DMA_Base_Address;
}

/**
  * @brief  config tmr break mode and dead-time
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR1, TMR8, TMR20
  * @param  brkdt_struct
  *         - to the structure of TMR_Brkdt_Config_Type
  * @retval 无
  */
void TMR_Brkdt_Config(TMR_Type *TMR_x, TMR_Brkdt_Config_Type *brkdt_struct) {
    TMR_x->brk_bit.brken = brkdt_struct->brk_Enable;
    TMR_x->brk_bit.dtc = brkdt_struct->deadtime;
    TMR_x->brk_bit.fcsodis = brkdt_struct->fcsodis_state;
    TMR_x->brk_bit.fcsoen = brkdt_struct->fcsoen_state;
    TMR_x->brk_bit.brkv = brkdt_struct->brk_polarity;
    TMR_x->brk_bit.aoen = brkdt_struct->auto_OutPut_Enable;
    TMR_x->brk_bit.wpc = brkdt_struct->wp_level;
}

/**
  * @brief  set tmr2/tmr5 input channel remap
  * @param  TMR_x: select the tmr peripheral.
  *         该参数可以是以下值之一:
  *         TMR2, TMR5
  * @param  input_remap
  *         - TMR2_TMR8TRGOUT_TMR5_GPIO
  *         - TMR2_PTP_TMR5_LICK
  *         - TMR2_OTG1FS_TMR5_LEXT
  *         - TMR2_OTG2FS_TMR5_ERTC
  * @retval 无
  */
void TMR_Iremap_Config(TMR_Type *TMR_x, TMR_Input_remap_Type input_remap) {
    if(TMR_x == TMR2) {
        TMR_x->rmp_bit.tmr2_ch1_irmp = input_remap;
    } else if(TMR_x == TMR5) {
        TMR_x->rmp_bit.tmr5_ch4_irmp = input_remap;
    }
}

#endif
