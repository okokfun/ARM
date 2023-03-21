/*!
    文件:    gd32f4xx_timer.c
    简介:   TIMER driver

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


#include "gd32f4xx_timer.h"

/*!
    简介:      deinit a TIMER
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:      无
*/
void timer_deinit(uint32_t timer_periph) {
    switch(timer_periph) {
    case TIMER0:
        /* reset TIMER0 */
        rcu_periph_reset_enable(RCU_TIMER0RST);
        rcu_periph_reset_disable(RCU_TIMER0RST);
        break;

    case TIMER1:
        /* reset TIMER1 */
        rcu_periph_reset_enable(RCU_TIMER1RST);
        rcu_periph_reset_disable(RCU_TIMER1RST);
        break;

    case TIMER2:
        /* reset TIMER2 */
        rcu_periph_reset_enable(RCU_TIMER2RST);
        rcu_periph_reset_disable(RCU_TIMER2RST);
        break;

    case TIMER3:
        /* reset TIMER3 */
        rcu_periph_reset_enable(RCU_TIMER3RST);
        rcu_periph_reset_disable(RCU_TIMER3RST);
        break;

    case TIMER4:
        /* reset TIMER4 */
        rcu_periph_reset_enable(RCU_TIMER4RST);
        rcu_periph_reset_disable(RCU_TIMER4RST);
        break;

    case TIMER5:
        /* reset TIMER5 */
        rcu_periph_reset_enable(RCU_TIMER5RST);
        rcu_periph_reset_disable(RCU_TIMER5RST);
        break;

    case TIMER6:
        /* reset TIMER6 */
        rcu_periph_reset_enable(RCU_TIMER6RST);
        rcu_periph_reset_disable(RCU_TIMER6RST);
        break;

    case TIMER7:
        /* reset TIMER7 */
        rcu_periph_reset_enable(RCU_TIMER7RST);
        rcu_periph_reset_disable(RCU_TIMER7RST);
        break;

    case TIMER8:
        /* reset TIMER8 */
        rcu_periph_reset_enable(RCU_TIMER8RST);
        rcu_periph_reset_disable(RCU_TIMER8RST);
        break;

    case TIMER9:
        /* reset TIMER9 */
        rcu_periph_reset_enable(RCU_TIMER9RST);
        rcu_periph_reset_disable(RCU_TIMER9RST);
        break;

    case TIMER10:
        /* reset TIMER10 */
        rcu_periph_reset_enable(RCU_TIMER10RST);
        rcu_periph_reset_disable(RCU_TIMER10RST);
        break;

    case TIMER11:
        /* reset TIMER11 */
        rcu_periph_reset_enable(RCU_TIMER11RST);
        rcu_periph_reset_disable(RCU_TIMER11RST);
        break;

    case TIMER12:
        /* reset TIMER12 */
        rcu_periph_reset_enable(RCU_TIMER12RST);
        rcu_periph_reset_disable(RCU_TIMER12RST);
        break;

    case TIMER13:
        /* reset TIMER13 */
        rcu_periph_reset_enable(RCU_TIMER13RST);
        rcu_periph_reset_disable(RCU_TIMER13RST);
        break;

    default:
        break;
    }
}

/*!
    简介:      initialize TIMER init parameter struct with a default value
    参数[输入]:  initpara: init parameter struct
    参数[输出]:  无
    返回值:      无
*/
void timer_struct_para_init(timer_parameter_struct *initpara) {
    /* initialize the init parameter struct member with the default value */
    initpara->prescaler         = 0U;
    initpara->alignedmode       = TIMER_COUNTER_EDGE;
    initpara->counterdirection  = TIMER_COUNTER_UP;
    initpara->period            = 65535U;
    initpara->clockdivision     = TIMER_CKDIV_DIV1;
    initpara->repetitioncounter = 0U;
}

/*!
    简介:      initialize TIMER counter
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输入]:  initpara: init parameter struct
                prescaler: prescaler value of the counter clock,0~65535
                alignedmode: TIMER_COUNTER_EDGE,TIMER_COUNTER_CENTER_DOWN,TIMER_COUNTER_CENTER_UP,TIMER_COUNTER_CENTER_BOTH
                counterdirection: TIMER_COUNTER_UP,TIMER_COUNTER_DOWN
                period: counter auto reload value,(TIMER1,TIMER4,32 bit)
                clockdivision: TIMER_CKDIV_DIV1,TIMER_CKDIV_DIV2,TIMER_CKDIV_DIV4
                repetitioncounter: counter repetition value,0~255
    参数[输出]:  无
    返回值:      无
*/
void timer_init(uint32_t timer_periph, timer_parameter_struct *initpara) {
    /* configure the counter prescaler value */
    TIMER_PSC(timer_periph) = (uint16_t)initpara->prescaler;

    /* configure the counter direction and aligned mode */
    if((TIMER0 == timer_periph) || (TIMER1 == timer_periph) || (TIMER2 == timer_periph)
            || (TIMER3 == timer_periph) || (TIMER4 == timer_periph) || (TIMER7 == timer_periph)) {
        TIMER_CTL0(timer_periph) &= ~(uint32_t)(TIMER_CTL0_DIR | TIMER_CTL0_CAM);
        TIMER_CTL0(timer_periph) |= (uint32_t)initpara->alignedmode;
        TIMER_CTL0(timer_periph) |= (uint32_t)initpara->counterdirection;
    }

    /* configure the autoreload value */
    TIMER_CAR(timer_periph) = (uint32_t)initpara->period;

    if((TIMER5 != timer_periph) && (TIMER6 != timer_periph)) {
        /* reset the CKDIV bit */
        TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_CKDIV;
        TIMER_CTL0(timer_periph) |= (uint32_t)initpara->clockdivision;
    }

    if((TIMER0 == timer_periph) || (TIMER7 == timer_periph)) {
        /* configure the repetition counter value */
        TIMER_CREP(timer_periph) = (uint32_t)initpara->repetitioncounter;
    }

    /* generate an update event */
    TIMER_SWEVG(timer_periph) |= (uint32_t)TIMER_SWEVG_UPG;
}

/*!
    简介:      enable a TIMER
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:      无
*/
void timer_enable(uint32_t timer_periph) {
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_CEN;
}

/*!
    简介:      disable a TIMER
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:      无
*/
void timer_disable(uint32_t timer_periph) {
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_CEN;
}

/*!
    简介:      enable the auto reload shadow function
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:      无
*/
void timer_auto_reload_shadow_enable(uint32_t timer_periph) {
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_ARSE;
}

/*!
    简介:      disable the auto reload shadow function
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:      无
*/
void timer_auto_reload_shadow_disable(uint32_t timer_periph) {
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_ARSE;
}

/*!
    简介:      enable the update event
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:      无
*/
void timer_update_event_enable(uint32_t timer_periph) {
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_UPDIS;
}

/*!
    简介:      disable the update event
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:      无
*/
void timer_update_event_disable(uint32_t timer_periph) {
    TIMER_CTL0(timer_periph) |= (uint32_t) TIMER_CTL0_UPDIS;
}

/*!
    简介:      set TIMER counter alignment mode
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输入]:  aligned:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_COUNTER_EDGE: edge-aligned mode
      参数:        TIMER_COUNTER_CENTER_DOWN: center-aligned and counting down assert mode
      参数:        TIMER_COUNTER_CENTER_UP: center-aligned and counting up assert mode
      参数:        TIMER_COUNTER_CENTER_BOTH: center-aligned and counting up/down assert mode
    参数[输出]:  无
    返回值:      无
*/
void timer_counter_alignment(uint32_t timer_periph, uint16_t aligned) {
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_CAM;
    TIMER_CTL0(timer_periph) |= (uint32_t)aligned;
}

/*!
    简介:      set TIMER counter up direction
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_counter_up_direction(uint32_t timer_periph) {
    TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_DIR;
}

/*!
    简介:      set TIMER counter down direction
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_counter_down_direction(uint32_t timer_periph) {
    TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_DIR;
}

/*!
    简介:      configure TIMER prescaler
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输入]:  prescaler: prescaler value,0~65535
    参数[输入]:  pscreload: prescaler reload mode
                only one parameter can be selected which is shown as below:
      参数:        TIMER_PSC_RELOAD_NOW: the prescaler is loaded right now
      参数:        TIMER_PSC_RELOAD_UPDATE: the prescaler is loaded at the next update event
    参数[输出]:  无
    返回值:      无
*/
void timer_prescaler_config(uint32_t timer_periph, uint16_t prescaler, uint8_t pscreload) {
    TIMER_PSC(timer_periph) = (uint32_t)prescaler;

    if(TIMER_PSC_RELOAD_NOW == pscreload) {
        TIMER_SWEVG(timer_periph) |= (uint32_t)TIMER_SWEVG_UPG;
    }
}

/*!
    简介:      configure TIMER repetition register value
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输入]:  repetition: the counter repetition value,0~255
    参数[输出]:  无
    返回值:      无
*/
void timer_repetition_value_config(uint32_t timer_periph, uint16_t repetition) {
    TIMER_CREP(timer_periph) = (uint32_t)repetition;
}

/*!
    简介:      configure TIMER autoreload register value
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输入]:  autoreload: the counter auto-reload value
    参数[输出]:  无
    返回值:      无
*/
void timer_autoreload_value_config(uint32_t timer_periph, uint32_t autoreload) {
    TIMER_CAR(timer_periph) = (uint32_t)autoreload;
}

/*!
    简介:      configure TIMER counter register value
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输入]:  counter: the counter value,0~65535
    参数[输出]:  无
    返回值:      无
*/
void timer_counter_value_config(uint32_t timer_periph, uint32_t counter) {
    TIMER_CNT(timer_periph) = (uint32_t)counter;
}

/*!
    简介:      read TIMER counter value
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:     counter value
*/
uint32_t timer_counter_read(uint32_t timer_periph) {
    uint32_t count_value = 0U;
    count_value = TIMER_CNT(timer_periph);
    return (count_value);
}

/*!
    简介:      read TIMER prescaler value
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输出]:  无
    返回值:     prescaler register value
*/
uint16_t timer_prescaler_read(uint32_t timer_periph) {
    uint16_t prescaler_value = 0U;
    prescaler_value = (uint16_t)(TIMER_PSC(timer_periph));
    return (prescaler_value);
}

/*!
    简介:      configure TIMER single pulse mode
    参数[输入]:  timer_periph: TIMERx(x=0..8,11)
    参数[输入]:  spmode:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_SP_MODE_SINGLE: single pulse mode
      参数:        TIMER_SP_MODE_REPETITIVE: repetitive pulse mode
    参数[输出]:  无
    返回值:      无
*/
void timer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode) {
    if(TIMER_SP_MODE_SINGLE == spmode) {
        TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_SPM;
    } else if(TIMER_SP_MODE_REPETITIVE == spmode) {
        TIMER_CTL0(timer_periph) &= ~((uint32_t)TIMER_CTL0_SPM);
    } else {
        /* illegal parameters */
    }
}

/*!
    简介:      configure TIMER update source
    参数[输入]:  timer_periph: TIMERx(x=0..13)
    参数[输入]:  update:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_UPDATE_SRC_GLOBAL: update generate by setting of UPG bit or the counter overflow/underflow,or the slave mode controller trigger
      参数:        TIMER_UPDATE_SRC_REGULAR: update generate only by counter overflow/underflow
    参数[输出]:  无
    返回值:      无
*/
void timer_update_source_config(uint32_t timer_periph, uint32_t update) {
    if(TIMER_UPDATE_SRC_REGULAR == update) {
        TIMER_CTL0(timer_periph) |= (uint32_t)TIMER_CTL0_UPS;
    } else if(TIMER_UPDATE_SRC_GLOBAL == update) {
        TIMER_CTL0(timer_periph) &= ~(uint32_t)TIMER_CTL0_UPS;
    } else {
        /* illegal parameters */
    }
}

/*!
    简介:      enable the TIMER DMA
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  dma: specify which DMA to enable
                one or more parameters can be selected which is shown as below:
      参数:        TIMER_DMA_UPD:  update DMA,TIMERx(x=0..7)
      参数:        TIMER_DMA_CH0D: channel 0 DMA request,TIMERx(x=0..4,7)
      参数:        TIMER_DMA_CH1D: channel 1 DMA request,TIMERx(x=0..4,7)
      参数:        TIMER_DMA_CH2D: channel 2 DMA request,TIMERx(x=0..4,7)
      参数:        TIMER_DMA_CH3D: channel 3 DMA request,TIMERx(x=0..4,7)
      参数:        TIMER_DMA_CMTD: commutation DMA request,TIMERx(x=0,7)
      参数:        TIMER_DMA_TRGD: trigger DMA request,TIMERx(x=0..4,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_dma_enable(uint32_t timer_periph, uint16_t dma) {
    TIMER_DMAINTEN(timer_periph) |= (uint32_t) dma;
}

/*!
    简介:      disable the TIMER DMA
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  dma: specify which DMA to disable
                one or more parameters can be selected which are shown as below:
      参数:        TIMER_DMA_UPD:  update DMA,TIMERx(x=0..7)
      参数:        TIMER_DMA_CH0D: channel 0 DMA request,TIMERx(x=0..4,7)
      参数:        TIMER_DMA_CH1D: channel 1 DMA request,TIMERx(x=0..4,7)
      参数:        TIMER_DMA_CH2D: channel 2 DMA request,TIMERx(x=0..4,7)
      参数:        TIMER_DMA_CH3D: channel 3 DMA request,TIMERx(x=0..4,7)
      参数:        TIMER_DMA_CMTD: commutation DMA request ,TIMERx(x=0,7)
      参数:        TIMER_DMA_TRGD: trigger DMA request,TIMERx(x=0..4,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_dma_disable(uint32_t timer_periph, uint16_t dma) {
    TIMER_DMAINTEN(timer_periph) &= (~(uint32_t)(dma));
}

/*!
    简介:      channel DMA request source selection
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输入]:  dma_request: channel DMA request source selection
                only one parameter can be selected which is shown as below:
       参数:        TIMER_DMAREQUEST_CHANNELEVENT: DMA request of channel y is sent when channel y event occurs
       参数:        TIMER_DMAREQUEST_UPDATEEVENT: DMA request of channel y is sent when update event occurs
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_dma_request_source_select(uint32_t timer_periph, uint8_t dma_request) {
    if(TIMER_DMAREQUEST_UPDATEEVENT == dma_request) {
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_DMAS;
    } else if(TIMER_DMAREQUEST_CHANNELEVENT == dma_request) {
        TIMER_CTL1(timer_periph) &= ~(uint32_t)TIMER_CTL1_DMAS;
    } else {
        /* illegal parameters */
    }
}

/*!
    简介:      configure the TIMER DMA transfer
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  dma_baseaddr:
                only one parameter can be selected which is shown as below:
       参数:        TIMER_DMACFG_DMATA_CTL0: DMA transfer address is TIMER_CTL0,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CTL1: DMA transfer address is TIMER_CTL1,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_SMCFG: DMA transfer address is TIMER_SMCFG,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_DMAINTEN: DMA transfer address is TIMER_DMAINTEN,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_INTF: DMA transfer address is TIMER_INTF,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_SWEVG: DMA transfer address is TIMER_SWEVG,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CHCTL0: DMA transfer address is TIMER_CHCTL0,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CHCTL1: DMA transfer address is TIMER_CHCTL1,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CHCTL2: DMA transfer address is TIMER_CHCTL2,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CNT: DMA transfer address is TIMER_CNT,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_PSC: DMA transfer address is TIMER_PSC,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CAR: DMA transfer address is TIMER_CAR,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CREP: DMA transfer address is TIMER_CREP,TIMERx(x=0,7)
       参数:        TIMER_DMACFG_DMATA_CH0CV: DMA transfer address is TIMER_CH0CV,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CH1CV: DMA transfer address is TIMER_CH1CV,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CH2CV: DMA transfer address is TIMER_CH2CV,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CH3CV: DMA transfer address is TIMER_CH3CV,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_CCHP: DMA transfer address is TIMER_CCHP,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_DMACFG: DMA transfer address is TIMER_DMACFG,TIMERx(x=0..4,7)
       参数:        TIMER_DMACFG_DMATA_DMATB: DMA transfer address is TIMER_DMATB,TIMERx(x=0..4,7)
    参数[输入]:  dma_lenth:
                only one parameter can be selected which is shown as below:
       参数:        TIMER_DMACFG_DMATC_xTRANSFER(x=1..18): DMA transfer x time
    参数[输出]:  无
    返回值:      无
*/
void timer_dma_transfer_config(uint32_t timer_periph, uint32_t dma_baseaddr, uint32_t dma_lenth) {
    TIMER_DMACFG(timer_periph) &= (~(uint32_t)(TIMER_DMACFG_DMATA | TIMER_DMACFG_DMATC));
    TIMER_DMACFG(timer_periph) |= (uint32_t)(dma_baseaddr | dma_lenth);
}

/*!
    简介:      software generate events
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  event: the timer software event generation sources
                one or more parameters can be selected which are shown as below:
      参数:        TIMER_EVENT_SRC_UPG: update event,TIMERx(x=0..13)
      参数:        TIMER_EVENT_SRC_CH0G: channel 0 capture or compare event generation,TIMERx(x=0..4,7..13)
      参数:        TIMER_EVENT_SRC_CH1G: channel 1 capture or compare event generation,TIMERx(x=0..4,7,8,11)
      参数:        TIMER_EVENT_SRC_CH2G: channel 2 capture or compare event generation,TIMERx(x=0..4,7)
      参数:        TIMER_EVENT_SRC_CH3G: channel 3 capture or compare event generation,TIMERx(x=0..4,7)
      参数:        TIMER_EVENT_SRC_CMTG: channel commutation event generation,TIMERx(x=0,7)
      参数:        TIMER_EVENT_SRC_TRGG: trigger event generation,TIMERx(x=0..4,7,8,11)
      参数:        TIMER_EVENT_SRC_BRKG:  break event generation,TIMERx(x=0,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_event_software_generate(uint32_t timer_periph, uint16_t event) {
    TIMER_SWEVG(timer_periph) |= (uint32_t)event;
}

/*!
    简介:      initialize TIMER break parameter struct
    参数[输入]:  breakpara: TIMER break parameter struct
    参数[输出]:  无
    返回值:      无
*/
void timer_break_struct_para_init(timer_break_parameter_struct *breakpara) {
    /* initialize the break parameter struct member with the default value */
    breakpara->runoffstate     = TIMER_ROS_STATE_DISABLE;
    breakpara->ideloffstate    = TIMER_IOS_STATE_DISABLE;
    breakpara->deadtime        = 0U;
    breakpara->breakpolarity   = TIMER_BREAK_POLARITY_LOW;
    breakpara->outputautostate = TIMER_OUTAUTO_DISABLE;
    breakpara->protectmode     = TIMER_CCHP_PROT_OFF;
    breakpara->breakstate      = TIMER_BREAK_DISABLE;
}

/*!
    简介:      configure TIMER break function
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输入]:  breakpara: TIMER break parameter struct
                runoffstate: TIMER_ROS_STATE_ENABLE,TIMER_ROS_STATE_DISABLE
                ideloffstate: TIMER_IOS_STATE_ENABLE,TIMER_IOS_STATE_DISABLE
                deadtime: 0~255
                breakpolarity: TIMER_BREAK_POLARITY_LOW,TIMER_BREAK_POLARITY_HIGH
                outputautostate: TIMER_OUTAUTO_ENABLE,TIMER_OUTAUTO_DISABLE
                protectmode: TIMER_CCHP_PROT_OFF,TIMER_CCHP_PROT_0,TIMER_CCHP_PROT_1,TIMER_CCHP_PROT_2
                breakstate: TIMER_BREAK_ENABLE,TIMER_BREAK_DISABLE
    参数[输出]:  无
    返回值:      无
*/
void timer_break_config(uint32_t timer_periph, timer_break_parameter_struct *breakpara) {
    TIMER_CCHP(timer_periph) = (uint32_t)(((uint32_t)(breakpara->runoffstate)) |
                                          ((uint32_t)(breakpara->ideloffstate)) |
                                          ((uint32_t)(breakpara->deadtime)) |
                                          ((uint32_t)(breakpara->breakpolarity)) |
                                          ((uint32_t)(breakpara->outputautostate)) |
                                          ((uint32_t)(breakpara->protectmode)) |
                                          ((uint32_t)(breakpara->breakstate))) ;
}

/*!
    简介:      enable TIMER break function
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_break_enable(uint32_t timer_periph) {
    TIMER_CCHP(timer_periph) |= (uint32_t)TIMER_CCHP_BRKEN;
}

/*!
    简介:      disable TIMER break function
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_break_disable(uint32_t timer_periph) {
    TIMER_CCHP(timer_periph) &= ~(uint32_t)TIMER_CCHP_BRKEN;
}

/*!
    简介:      enable TIMER output automatic function
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_automatic_output_enable(uint32_t timer_periph) {
    TIMER_CCHP(timer_periph) |= (uint32_t)TIMER_CCHP_OAEN;
}

/*!
    简介:      disable TIMER output automatic function
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_automatic_output_disable(uint32_t timer_periph) {
    TIMER_CCHP(timer_periph) &= ~(uint32_t)TIMER_CCHP_OAEN;
}

/*!
    简介:      configure TIMER primary output function
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输入]:  newvalue: ENABLE or DISABLE
    参数[输出]:  无
    返回值:      无
*/
void timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue) {
    if(ENABLE == newvalue) {
        TIMER_CCHP(timer_periph) |= (uint32_t)TIMER_CCHP_POEN;
    } else {
        TIMER_CCHP(timer_periph) &= (~(uint32_t)TIMER_CCHP_POEN);
    }
}

/*!
    简介:      enable or disable channel capture/compare control shadow register
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输入]:  newvalue: ENABLE or DISABLE
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_control_shadow_config(uint32_t timer_periph, ControlStatus newvalue) {
    if(ENABLE == newvalue) {
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_CCSE;
    } else {
        TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_CCSE);
    }
}

/*!
    简介:      configure TIMER channel control shadow register update control
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输入]:  ccuctl: channel control shadow register update control
                only one parameter can be selected which is shown as below:
      参数:        TIMER_UPDATECTL_CCU: the shadow registers update by when CMTG bit is set
      参数:        TIMER_UPDATECTL_CCUTRI: the shadow registers update by when CMTG bit is set or an rising edge of TRGI occurs
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_control_shadow_update_config(uint32_t timer_periph, uint8_t ccuctl) {
    if(TIMER_UPDATECTL_CCU == ccuctl) {
        TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_CCUC);
    } else if(TIMER_UPDATECTL_CCUTRI == ccuctl) {
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_CCUC;
    } else {
        /* illegal parameters */
    }
}

/*!
    简介:      initialize TIMER channel output parameter struct with a default value
    参数[输入]:  ocpara: TIMER channel n output parameter struct
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_struct_para_init(timer_oc_parameter_struct *ocpara) {
    /* initialize the channel output parameter struct member with the default value */
    ocpara->outputstate  = (uint16_t)TIMER_CCX_DISABLE;
    ocpara->outputnstate = TIMER_CCXN_DISABLE;
    ocpara->ocpolarity   = TIMER_OC_POLARITY_HIGH;
    ocpara->ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    ocpara->ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    ocpara->ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;
}

/*!
    简介:      configure TIMER channel output function
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel 0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel 1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel 2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel 3(TIMERx(x=0..4,7))
    参数[输入]:  ocpara: TIMER channeln output parameter struct
                outputstate: TIMER_CCX_ENABLE,TIMER_CCX_DISABLE
                outputnstate: TIMER_CCXN_ENABLE,TIMER_CCXN_DISABLE
                ocpolarity: TIMER_OC_POLARITY_HIGH,TIMER_OC_POLARITY_LOW
                ocnpolarity: TIMER_OCN_POLARITY_HIGH,TIMER_OCN_POLARITY_LOW
                ocidlestate: TIMER_OC_IDLE_STATE_LOW,TIMER_OC_IDLE_STATE_HIGH
                ocnidlestate: TIMER_OCN_IDLE_STATE_LOW,TIMER_OCN_IDLE_STATE_HIGH
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_config(uint32_t timer_periph, uint16_t channel, timer_oc_parameter_struct *ocpara) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        TIMER_CHCTL0(timer_periph) &= ~(uint32_t)TIMER_CHCTL0_CH0MS;
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->outputstate;
        /* reset the CH0P bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0P);
        /* set the CH0P bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->ocpolarity;

        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph)) {
            /* reset the CH0NEN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NEN);
            /* set the CH0NEN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->outputnstate;
            /* reset the CH0NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NP);
            /* set the CH0NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpara->ocnpolarity;
            /* reset the ISO0 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO0);
            /* set the ISO0 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)ocpara->ocidlestate;
            /* reset the ISO0N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO0N);
            /* set the ISO0N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)ocpara->ocnidlestate;
        }

        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        TIMER_CHCTL0(timer_periph) &= ~(uint32_t)TIMER_CHCTL0_CH1MS;
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocpara->outputstate << 4U);
        /* reset the CH1P bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1P);
        /* set the CH1P bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocpolarity) << 4U);

        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph)) {
            /* reset the CH1NEN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NEN);
            /* set the CH1NEN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->outputnstate) << 4U);
            /* reset the CH1NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NP);
            /* set the CH1NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocnpolarity) << 4U);
            /* reset the ISO1 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1);
            /* set the ISO1 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocidlestate) << 2U);
            /* reset the ISO1N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO1N);
            /* set the ISO1N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocnidlestate) << 2U);
        }

        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        /* reset the CH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
        TIMER_CHCTL1(timer_periph) &= ~(uint32_t)TIMER_CHCTL1_CH2MS;
        /* set the CH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocpara->outputstate << 8U);
        /* reset the CH2P bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2P);
        /* set the CH2P bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocpolarity) << 8U);

        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph)) {
            /* reset the CH2NEN bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NEN);
            /* set the CH2NEN bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->outputnstate) << 8U);
            /* reset the CH2NP bit */
            TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NP);
            /* set the CH2NP bit */
            TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocnpolarity) << 8U);
            /* reset the ISO2 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO2);
            /* set the ISO2 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocidlestate) << 4U);
            /* reset the ISO2N bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO2N);
            /* set the ISO2N bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocnidlestate) << 4U);
        }

        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        /* reset the CH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
        TIMER_CHCTL1(timer_periph) &= ~(uint32_t)TIMER_CHCTL1_CH3MS;
        /* set the CH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocpara->outputstate << 12U);
        /* reset the CH3P bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3P);
        /* set the CH3P bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocpolarity) << 12U);

        if((TIMER0 == timer_periph) || (TIMER7 == timer_periph)) {
            /* reset the ISO3 bit */
            TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_ISO3);
            /* set the ISO3 bit */
            TIMER_CTL1(timer_periph) |= (uint32_t)((uint32_t)(ocpara->ocidlestate) << 6U);
        }

        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel output compare mode
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输入]:  ocmode: channel output compare mode
                only one parameter can be selected which is shown as below:
      参数:        TIMER_OC_MODE_TIMING: timing mode
      参数:        TIMER_OC_MODE_ACTIVE: active mode
      参数:        TIMER_OC_MODE_INACTIVE: inactive mode
      参数:        TIMER_OC_MODE_TOGGLE: toggle mode
      参数:        TIMER_OC_MODE_LOW: force low mode
      参数:        TIMER_OC_MODE_HIGH: force high mode
      参数:        TIMER_OC_MODE_PWM0: PWM0 mode
      参数:        TIMER_OC_MODE_PWM1: PWM1 mode
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_mode_config(uint32_t timer_periph, uint16_t channel, uint16_t ocmode) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMCTL);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)ocmode;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMCTL);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)(ocmode) << 8U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMCTL);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)ocmode;
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMCTL);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)(ocmode) << 8U);
        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel output pulse value
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输入]:  pulse: channel output pulse value,0~65535
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_pulse_value_config(uint32_t timer_periph, uint16_t channel, uint32_t pulse) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CH0CV(timer_periph) = (uint32_t)pulse;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CH1CV(timer_periph) = (uint32_t)pulse;
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CH2CV(timer_periph) = (uint32_t)pulse;
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CH3CV(timer_periph) = (uint32_t)pulse;
        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel output shadow function
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输入]:  ocshadow: channel output shadow state
                only one parameter can be selected which is shown as below:
      参数:        TIMER_OC_SHADOW_ENABLE: channel output shadow state enable
      参数:        TIMER_OC_SHADOW_DISABLE: channel output shadow state disable
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMSEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)ocshadow;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMSEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)(ocshadow) << 8U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMSEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)ocshadow;
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMSEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)(ocshadow) << 8U);
        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel output fast function
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输入]:  ocfast: channel output fast function
                only one parameter can be selected which is shown as below:
      参数:        TIMER_OC_FAST_ENABLE: channel output fast function enable
      参数:        TIMER_OC_FAST_DISABLE: channel output fast function disable
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_fast_config(uint32_t timer_periph, uint16_t channel, uint16_t ocfast) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMFEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)ocfast;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMFEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)ocfast << 8U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMFEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)ocfast;
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMFEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)ocfast << 8U);
        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel output clear function
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输入]:  occlear: channel output clear function
                only one parameter can be selected which is shown as below:
      参数:        TIMER_OC_CLEAR_ENABLE: channel output clear function enable
      参数:        TIMER_OC_CLEAR_DISABLE: channel output clear function disable
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_clear_config(uint32_t timer_periph, uint16_t channel, uint16_t occlear) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0COMCEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)occlear;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1COMCEN);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)occlear << 8U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2COMCEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)occlear;
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3COMCEN);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)occlear << 8U);
        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel output polarity
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输入]:  ocpolarity: channel output polarity
                only one parameter can be selected which is shown as below:
      参数:        TIMER_OC_POLARITY_HIGH: channel output polarity is high
      参数:        TIMER_OC_POLARITY_LOW: channel output polarity is low
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocpolarity) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocpolarity;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocpolarity << 4U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocpolarity << 8U);
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3P);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocpolarity << 12U);
        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel complementary output polarity
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
    参数[输入]:  ocnpolarity: channel complementary output polarity
                only one parameter can be selected which is shown as below:
      参数:        TIMER_OCN_POLARITY_HIGH: channel complementary output polarity is high
      参数:        TIMER_OCN_POLARITY_LOW: channel complementary output polarity is low
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_complementary_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnpolarity) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocnpolarity;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocnpolarity << 4U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NP);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocnpolarity << 8U);
        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel enable state
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输入]:  state: TIMER channel enable state
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CCX_ENABLE: channel enable
      参数:        TIMER_CCX_DISABLE: channel disable
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_output_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)state;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)state << 4U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)state << 8U);
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)state << 12U);
        break;

    default:
        break;
    }
}

/*!
    简介:      configure TIMER channel complementary output enable state
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0
      参数:        TIMER_CH_1: TIMER channel1
      参数:        TIMER_CH_2: TIMER channel2
    参数[输入]:  ocnstate: TIMER channel complementary output enable state
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CCXN_ENABLE: channel complementary enable
      参数:        TIMER_CCXN_DISABLE: channel complementary disable
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_complementary_output_state_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnstate) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)ocnstate;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocnstate << 4U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2NEN);
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)ocnstate << 8U);
        break;

    default:
        break;
    }
}

/*!
    简介:      initialize TIMER channel input parameter struct
    参数[输入]:  icpara: TIMER channel intput parameter struct
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_input_struct_para_init(timer_ic_parameter_struct *icpara) {
    /* initialize the channel input parameter struct member with the default value */
    icpara->icpolarity  = TIMER_IC_POLARITY_RISING;
    icpara->icselection = TIMER_IC_SELECTION_DIRECTTI;
    icpara->icprescaler = TIMER_IC_PSC_DIV1;
    icpara->icfilter    = 0U;
}

/*!
    简介:      configure TIMER input capture parameter
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
     参数[输入]:  icpara: TIMER channel intput parameter struct
                 icpolarity: TIMER_IC_POLARITY_RISING,TIMER_IC_POLARITY_FALLING,TIMER_IC_POLARITY_BOTH_EDGE
                 icselection: TIMER_IC_SELECTION_DIRECTTI,TIMER_IC_SELECTION_INDIRECTTI,TIMER_IC_SELECTION_ITS
                 icprescaler: TIMER_IC_PSC_DIV1,TIMER_IC_PSC_DIV2,TIMER_IC_PSC_DIV4,TIMER_IC_PSC_DIV8
                 icfilter: 0~15
    参数[输出]:  无
    返回值:      无
*/
void timer_input_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpara) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);

        /* reset the CH0P and CH0NP bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(icpara->icpolarity);
        /* reset the CH0MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(icpara->icselection);
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)(icpara->icfilter) << 4U);

        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);

        /* reset the CH1P and CH1NP bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(icpara->icpolarity) << 4U);
        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)(icpara->icselection) << 8U);
        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)(icpara->icfilter) << 12U);

        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        /* reset the CH2EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH2EN);

        /* reset the CH2P and CH2NP bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH2P | TIMER_CHCTL2_CH2NP));
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(icpara->icpolarity) << 8U);

        /* reset the CH2MS bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2MS);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)(icpara->icselection));

        /* reset the CH2CAPFLT bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2CAPFLT);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)(icpara->icfilter) << 4U);

        /* set the CH2EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH2EN;
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        /* reset the CH3EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH3EN);

        /* reset the CH3P bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH3P));
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(icpara->icpolarity) << 12U);

        /* reset the CH3MS bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3MS);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)(icpara->icselection) << 8U);

        /* reset the CH3CAPFLT bit */
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3CAPFLT);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)((uint32_t)(icpara->icfilter) << 12U);

        /* set the CH3EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH3EN;
        break;

    default:
        break;
    }

    /* configure TIMER channel input capture prescaler value */
    timer_channel_input_capture_prescaler_config(timer_periph, channel, (uint16_t)(icpara->icprescaler));
}

/*!
    简介:      configure TIMER channel input capture prescaler value
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输入]:  prescaler: channel input capture prescaler value
                only one parameter can be selected which is shown as below:
      参数:        TIMER_IC_PSC_DIV1: no prescaler
      参数:        TIMER_IC_PSC_DIV2: divided by 2
      参数:        TIMER_IC_PSC_DIV4: divided by 4
      参数:        TIMER_IC_PSC_DIV8: divided by 8
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_input_capture_prescaler_config(uint32_t timer_periph, uint16_t channel, uint16_t prescaler) {
    switch(channel) {
    /* configure TIMER_CH_0 */
    case TIMER_CH_0:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPPSC);
        TIMER_CHCTL0(timer_periph) |= (uint32_t)prescaler;
        break;

    /* configure TIMER_CH_1 */
    case TIMER_CH_1:
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPPSC);
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)prescaler << 8U);
        break;

    /* configure TIMER_CH_2 */
    case TIMER_CH_2:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH2CAPPSC);
        TIMER_CHCTL1(timer_periph) |= (uint32_t)prescaler;
        break;

    /* configure TIMER_CH_3 */
    case TIMER_CH_3:
        TIMER_CHCTL1(timer_periph) &= (~(uint32_t)TIMER_CHCTL1_CH3CAPPSC);
        TIMER_CHCTL1(timer_periph) |= ((uint32_t)prescaler << 8U);
        break;

    default:
        break;
    }
}

/*!
    简介:      read TIMER channel capture compare register value
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0(TIMERx(x=0..4,7..13))
      参数:        TIMER_CH_1: TIMER channel1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_CH_2: TIMER channel2(TIMERx(x=0..4,7))
      参数:        TIMER_CH_3: TIMER channel3(TIMERx(x=0..4,7))
    参数[输出]:  无
    返回值:     channel capture compare register value
*/
uint32_t timer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel) {
    uint32_t count_value = 0U;

    switch(channel) {
    /* read TIMER channel 0 capture compare register value */
    case TIMER_CH_0:
        count_value = TIMER_CH0CV(timer_periph);
        break;

    /* read TIMER channel 1 capture compare register value */
    case TIMER_CH_1:
        count_value = TIMER_CH1CV(timer_periph);
        break;

    /* read TIMER channel 2 capture compare register value */
    case TIMER_CH_2:
        count_value = TIMER_CH2CV(timer_periph);
        break;

    /* read TIMER channel 3 capture compare register value */
    case TIMER_CH_3:
        count_value = TIMER_CH3CV(timer_periph);
        break;

    default:
        break;
    }

    return (count_value);
}

/*!
    简介:      configure TIMER input pwm capture function
    参数[输入]:  timer_periph: TIMERx(x=0..4,7,8,11)
    参数[输入]:  channel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CH_0: TIMER channel0
      参数:        TIMER_CH_1: TIMER channel1
     参数[输入]:  icpwm:TIMER channel intput pwm parameter struct
                 icpolarity: TIMER_IC_POLARITY_RISING,TIMER_IC_POLARITY_FALLING
                 icselection: TIMER_IC_SELECTION_DIRECTTI,TIMER_IC_SELECTION_INDIRECTTI
                 icprescaler: TIMER_IC_PSC_DIV1,TIMER_IC_PSC_DIV2,TIMER_IC_PSC_DIV4,TIMER_IC_PSC_DIV8
                 icfilter: 0~15
    参数[输出]:  无
    返回值:      无
*/
void timer_input_pwm_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct *icpwm) {
    uint16_t icpolarity  = 0x0U;
    uint16_t icselection = 0x0U;

    /* Set channel input polarity */
    if(TIMER_IC_POLARITY_RISING == icpwm->icpolarity) {
        icpolarity = TIMER_IC_POLARITY_FALLING;
    } else {
        icpolarity = TIMER_IC_POLARITY_RISING;
    }

    /* Set channel input mode selection */
    if(TIMER_IC_SELECTION_DIRECTTI == icpwm->icselection) {
        icselection = TIMER_IC_SELECTION_INDIRECTTI;
    } else {
        icselection = TIMER_IC_SELECTION_DIRECTTI;
    }

    if(TIMER_CH_0 == channel) {
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* reset the CH0P and CH0NP bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        /* set the CH0P and CH0NP bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)(icpwm->icpolarity);
        /* reset the CH0MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        /* set the CH0MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(icpwm->icselection);
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        /* set the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpwm->icfilter) << 4U);
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_0, (uint16_t)(icpwm->icprescaler));

        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* reset the CH1P and CH1NP bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        /* set the CH1P and CH1NP bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)icpolarity << 4U);
        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        /* set the CH1MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)icselection << 8U);
        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        /* set the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)(icpwm->icfilter) << 12U);
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_1, (uint16_t)(icpwm->icprescaler));
    } else {
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* reset the CH1P and CH1NP bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        /* set the CH1P and CH1NP bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)(icpwm->icpolarity) << 4U);
        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        /* set the CH1MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)(icpwm->icselection) << 8U);
        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        /* set the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)(icpwm->icfilter) << 12U);
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_1, (uint16_t)(icpwm->icprescaler));

        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* reset the CH0P and CH0NP bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        /* set the CH0P and CH0NP bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)icpolarity;
        /* reset the CH0MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        /* set the CH0MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)icselection;
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        /* set the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= ((uint32_t)(icpwm->icfilter) << 4U);
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
        /* configure TIMER channel input capture prescaler value */
        timer_channel_input_capture_prescaler_config(timer_periph, TIMER_CH_0, (uint16_t)(icpwm->icprescaler));
    }
}

/*!
    简介:      configure TIMER hall sensor mode
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输入]:  hallmode:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_HALLINTERFACE_ENABLE: TIMER hall sensor mode enable
      参数:        TIMER_HALLINTERFACE_DISABLE: TIMER hall sensor mode disable
    参数[输出]:  无
    返回值:      无
*/
void timer_hall_mode_config(uint32_t timer_periph, uint32_t hallmode) {
    if(TIMER_HALLINTERFACE_ENABLE == hallmode) {
        TIMER_CTL1(timer_periph) |= (uint32_t)TIMER_CTL1_TI0S;
    } else if(TIMER_HALLINTERFACE_DISABLE == hallmode) {
        TIMER_CTL1(timer_periph) &= ~(uint32_t)TIMER_CTL1_TI0S;
    } else {
        /* illegal parameters */
    }
}

/*!
    简介:      select TIMER input trigger source
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  intrigger:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_SMCFG_TRGSEL_ITI0: internal trigger 0(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SMCFG_TRGSEL_ITI1: internal trigger 1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SMCFG_TRGSEL_ITI2: internal trigger 2(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SMCFG_TRGSEL_ITI3: internal trigger 3(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SMCFG_TRGSEL_CI0F_ED: TI0 edge detector(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SMCFG_TRGSEL_CI0FE0: filtered TIMER input 0(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SMCFG_TRGSEL_CI1FE1: filtered TIMER input 1(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SMCFG_TRGSEL_ETIFP: external trigger(TIMERx(x=0..4,7,8,11))
    参数[输出]:  无
    返回值:      无
*/
void timer_input_trigger_source_select(uint32_t timer_periph, uint32_t intrigger) {
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_TRGS);
    TIMER_SMCFG(timer_periph) |= (uint32_t)intrigger;
}

/*!
    简介:      select TIMER master mode output trigger source
    参数[输入]:  timer_periph: TIMERx(x=0..7)
    参数[输入]:  outrigger:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_TRI_OUT_SRC_RESET: the UPG bit as trigger output(TIMERx(x=0..7,9,10,12,13))
      参数:        TIMER_TRI_OUT_SRC_ENABLE: the counter enable signal TIMER_CTL0_CEN as trigger output(TIMERx(x=0..7,9,10,12,13))
      参数:        TIMER_TRI_OUT_SRC_UPDATE: update event as trigger output(TIMERx(x=0..7,9,10,12,13))
      参数:        TIMER_TRI_OUT_SRC_CH0: a capture or a compare match occurred in channal0 as trigger output TRGO(TIMERx(x=0..4,7,9,10,12,13))
      参数:        TIMER_TRI_OUT_SRC_O0CPRE: O0CPRE as trigger output(TIMERx(x=0..4,7,9,10,12,13))
      参数:        TIMER_TRI_OUT_SRC_O1CPRE: O1CPRE as trigger output(TIMERx(x=0..4,7))
      参数:        TIMER_TRI_OUT_SRC_O2CPRE: O2CPRE as trigger output(TIMERx(x=0..4,7))
      参数:        TIMER_TRI_OUT_SRC_O3CPRE: O3CPRE as trigger output(TIMERx(x=0..4,7))
    参数[输出]:  无
    返回值:      无
*/
void timer_master_output_trigger_source_select(uint32_t timer_periph, uint32_t outrigger) {
    TIMER_CTL1(timer_periph) &= (~(uint32_t)TIMER_CTL1_MMC);
    TIMER_CTL1(timer_periph) |= (uint32_t)outrigger;
}

/*!
    简介:      select TIMER slave mode
    参数[输入]:  timer_periph: TIMERx(x=0..4,7,8,11)
    参数[输入]:  slavemode:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_SLAVE_MODE_DISABLE: slave mode disable(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_ENCODER_MODE0: encoder mode 0(TIMERx(x=0..4,7))
      参数:        TIMER_ENCODER_MODE1: encoder mode 1(TIMERx(x=0..4,7))
      参数:        TIMER_ENCODER_MODE2: encoder mode 2(TIMERx(x=0..4,7))
      参数:        TIMER_SLAVE_MODE_RESTART: restart mode(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SLAVE_MODE_PAUSE: pause mode(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SLAVE_MODE_EVENT: event mode(TIMERx(x=0..4,7,8,11))
      参数:        TIMER_SLAVE_MODE_EXTERNAL0: external clock mode 0.(TIMERx(x=0..4,7,8,11))
    参数[输出]:  无
    返回值:      无
*/

void timer_slave_mode_select(uint32_t timer_periph, uint32_t slavemode) {
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_SMC);

    TIMER_SMCFG(timer_periph) |= (uint32_t)slavemode;
}

/*!
    简介:      configure TIMER master slave mode
    参数[输入]:  timer_periph: TIMERx(x=0..4,7,8,11)
    参数[输入]:  masterslave:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_MASTER_SLAVE_MODE_ENABLE: master slave mode enable
      参数:        TIMER_MASTER_SLAVE_MODE_DISABLE: master slave mode disable
    参数[输出]:  无
    返回值:      无
*/
void timer_master_slave_mode_config(uint32_t timer_periph, uint32_t masterslave) {
    if(TIMER_MASTER_SLAVE_MODE_ENABLE == masterslave) {
        TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SMCFG_MSM;
    } else if(TIMER_MASTER_SLAVE_MODE_DISABLE == masterslave) {
        TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_MSM;
    } else {
        /* illegal parameters */
    }
}

/*!
    简介:      configure TIMER external trigger input
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输入]:  extprescaler:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_EXT_TRI_PSC_OFF: no divided
      参数:        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      参数:        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      参数:        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    参数[输入]:  extpolarity:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_ETP_FALLING: active low or falling edge active
      参数:        TIMER_ETP_RISING: active high or rising edge active
    参数[输入]:  extfilter: a value between 0 and 15
    参数[输出]:  无
    返回值:      无
*/
void timer_external_trigger_config(uint32_t timer_periph, uint32_t extprescaler,
                                   uint32_t extpolarity, uint32_t extfilter) {
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)(TIMER_SMCFG_ETP | TIMER_SMCFG_ETPSC | TIMER_SMCFG_ETFC));
    TIMER_SMCFG(timer_periph) |= (uint32_t)(extprescaler | extpolarity);
    TIMER_SMCFG(timer_periph) |= (uint32_t)(extfilter << 8U);
}

/*!
    简介:      configure TIMER quadrature decoder mode
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输入]:  decomode:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_ENCODER_MODE0: counter counts on CI0FE0 edge depending on CI1FE1 level
      参数:        TIMER_ENCODER_MODE1: counter counts on CI1FE1 edge depending on CI0FE0 level
      参数:        TIMER_ENCODER_MODE2: counter counts on both CI0FE0 and CI1FE1 edges depending on the level of the other input
    参数[输入]:  ic0polarity:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_IC_POLARITY_RISING: capture rising edge
      参数:        TIMER_IC_POLARITY_FALLING: capture falling edge
    参数[输入]:  ic1polarity:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_IC_POLARITY_RISING: capture rising edge
      参数:        TIMER_IC_POLARITY_FALLING: capture falling edge
    参数[输出]:  无
    返回值:      无
*/
void timer_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode,
        uint16_t ic0polarity, uint16_t ic1polarity) {
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_SMC);
    TIMER_SMCFG(timer_periph) |= (uint32_t)decomode;

    TIMER_CHCTL0(timer_periph) &= (uint32_t)(((~(uint32_t)TIMER_CHCTL0_CH0MS)) & ((~(uint32_t)TIMER_CHCTL0_CH1MS)));
    TIMER_CHCTL0(timer_periph) |= (uint32_t)(TIMER_IC_SELECTION_DIRECTTI | ((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U));

    TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
    TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
    TIMER_CHCTL2(timer_periph) |= ((uint32_t)ic0polarity | ((uint32_t)ic1polarity << 4U));
}

/*!
    简介:      configure TIMER internal clock mode
    参数[输入]:  timer_periph: TIMERx(x=0..4,7,8,11)
    参数[输出]:  无
    返回值:      无
*/
void timer_internal_clock_config(uint32_t timer_periph) {
    TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_SMC;
}

/*!
    简介:      configure TIMER the internal trigger as external clock input
    参数[输入]:  timer_periph: TIMERx(x=0..4,7,8,11)
    参数[输入]:  intrigger:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_SMCFG_TRGSEL_ITI0: internal trigger 0
      参数:        TIMER_SMCFG_TRGSEL_ITI1: internal trigger 1
      参数:        TIMER_SMCFG_TRGSEL_ITI2: internal trigger 2
      参数:        TIMER_SMCFG_TRGSEL_ITI3: internal trigger 3
    参数[输出]:  无
    返回值:      无
*/
void timer_internal_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t intrigger) {
    timer_input_trigger_source_select(timer_periph, intrigger);
    TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_SMC;
    TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SLAVE_MODE_EXTERNAL0;
}

/*!
    简介:      configure TIMER the external trigger as external clock input
    参数[输入]:  timer_periph: TIMERx(x=0..4,7,8,11)
    参数[输入]:  extrigger:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_SMCFG_TRGSEL_CI0F_ED: TI0 edge detector
      参数:        TIMER_SMCFG_TRGSEL_CI0FE0: filtered TIMER input 0
      参数:        TIMER_SMCFG_TRGSEL_CI1FE1: filtered TIMER input 1
    参数[输入]:  extpolarity:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_IC_POLARITY_RISING: active high or rising edge active
      参数:        TIMER_IC_POLARITY_FALLING: active low or falling edge active
    参数[输入]:  extfilter: a value between 0 and 15
    参数[输出]:  无
    返回值:      无
*/
void timer_external_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t extrigger,
        uint16_t extpolarity, uint32_t extfilter) {
    if(TIMER_SMCFG_TRGSEL_CI1FE1 == extrigger) {
        /* reset the CH1EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH1EN);
        /* reset the CH1NP bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH1P | TIMER_CHCTL2_CH1NP));
        /* set the CH1NP bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)((uint32_t)extpolarity << 4U);
        /* reset the CH1MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1MS);
        /* set the CH1MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)((uint32_t)TIMER_IC_SELECTION_DIRECTTI << 8U);
        /* reset the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH1CAPFLT);
        /* set the CH1CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(extfilter << 12U);
        /* set the CH1EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH1EN;
    } else {
        /* reset the CH0EN bit */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)TIMER_CHCTL2_CH0EN);
        /* reset the CH0P and CH0NP bits */
        TIMER_CHCTL2(timer_periph) &= (~(uint32_t)(TIMER_CHCTL2_CH0P | TIMER_CHCTL2_CH0NP));
        /* set the CH0P and CH0NP bits */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)extpolarity;
        /* reset the CH0MS bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0MS);
        /* set the CH0MS bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)TIMER_IC_SELECTION_DIRECTTI;
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) &= (~(uint32_t)TIMER_CHCTL0_CH0CAPFLT);
        /* reset the CH0CAPFLT bit */
        TIMER_CHCTL0(timer_periph) |= (uint32_t)(extfilter << 4U);
        /* set the CH0EN bit */
        TIMER_CHCTL2(timer_periph) |= (uint32_t)TIMER_CHCTL2_CH0EN;
    }

    /* select TIMER input trigger source */
    timer_input_trigger_source_select(timer_periph, extrigger);
    /* reset the SMC bit */
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)TIMER_SMCFG_SMC);
    /* set the SMC bit */
    TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SLAVE_MODE_EXTERNAL0;
}

/*!
    简介:      configure TIMER the external clock mode0
    参数[输入]:  timer_periph: TIMERx(x=0..4,7,8,11)
    参数[输入]:  extprescaler:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_EXT_TRI_PSC_OFF: no divided
      参数:        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      参数:        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      参数:        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    参数[输入]:  extpolarity:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_ETP_FALLING: active low or falling edge active
      参数:        TIMER_ETP_RISING: active high or rising edge active
    参数[输入]:  extfilter: a value between 0 and 15
    参数[输出]:  无
    返回值:      无
*/
void timer_external_clock_mode0_config(uint32_t timer_periph, uint32_t extprescaler,
                                       uint32_t extpolarity, uint32_t extfilter) {
    /* configure TIMER external trigger input */
    timer_external_trigger_config(timer_periph, extprescaler, extpolarity, extfilter);

    /* reset the SMC bit,TRGS bit */
    TIMER_SMCFG(timer_periph) &= (~(uint32_t)(TIMER_SMCFG_SMC | TIMER_SMCFG_TRGS));
    /* set the SMC bit,TRGS bit */
    TIMER_SMCFG(timer_periph) |= (uint32_t)(TIMER_SLAVE_MODE_EXTERNAL0 | TIMER_SMCFG_TRGSEL_ETIFP);
}

/*!
    简介:      configure TIMER the external clock mode1
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输入]:  extprescaler:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_EXT_TRI_PSC_OFF: no divided
      参数:        TIMER_EXT_TRI_PSC_DIV2: divided by 2
      参数:        TIMER_EXT_TRI_PSC_DIV4: divided by 4
      参数:        TIMER_EXT_TRI_PSC_DIV8: divided by 8
    参数[输入]:  extpolarity:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_ETP_FALLING: active low or falling edge active
      参数:        TIMER_ETP_RISING: active high or rising edge active
    参数[输入]:  extfilter: a value between 0 and 15
    参数[输出]:  无
    返回值:      无
*/
void timer_external_clock_mode1_config(uint32_t timer_periph, uint32_t extprescaler,
                                       uint32_t extpolarity, uint32_t extfilter) {
    /* configure TIMER external trigger input */
    timer_external_trigger_config(timer_periph, extprescaler, extpolarity, extfilter);

    TIMER_SMCFG(timer_periph) |= (uint32_t)TIMER_SMCFG_SMC1;
}

/*!
    简介:      disable TIMER the external clock mode1
    参数[输入]:  timer_periph: TIMERx(x=0..4,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_external_clock_mode1_disable(uint32_t timer_periph) {
    TIMER_SMCFG(timer_periph) &= ~(uint32_t)TIMER_SMCFG_SMC1;
}

/*!
    简介:      configure TIMER channel remap function
    参数[输入]:  timer_periph: TIMERx(x=1,4,10)
    参数[输入]:  remap:
                only one parameter can be selected which is shown as below:
      参数:        TIMER1_ITI1_RMP_TIMER7_TRGO: timer1 internal trigger input1 remap to TIMER7_TRGO
      参数:        TIMER1_ITI1_RMP_ETHERNET_PTP: timer1 internal trigger input1 remap to ethernet PTP
      参数:        TIMER1_ITI1_RMP_USB_FS_SOF: timer1 internal trigger input1 remap to USB FS SOF
      参数:        TIMER1_ITI1_RMP_USB_HS_SOF: timer1 internal trigger input1 remap to USB HS SOF
      参数:        TIMER4_CI3_RMP_GPIO: timer4 channel 3 input remap to GPIO pin
      参数:        TIMER4_CI3_RMP_IRC32K: timer4 channel 3 input remap to IRC32K
      参数:        TIMER4_CI3_RMP_LXTAL: timer4 channel 3 input remap to  LXTAL
      参数:        TIMER4_CI3_RMP_RTC_WAKEUP_INT: timer4 channel 3 input remap to RTC wakeup interrupt
      参数:        TIMER10_ITI1_RMP_GPIO: timer10 internal trigger input1 remap based on GPIO setting
      参数:        TIMER10_ITI1_RMP_RTC_HXTAL_DIV: timer10 internal trigger input1 remap  HXTAL _DIV(clock used for RTC which is HXTAL clock divided by RTCDIV bits in RCU_CFG0 register)
    参数[输出]:  无
    返回值:      无
*/
void timer_channel_remap_config(uint32_t timer_periph, uint32_t remap) {
    TIMER_IRMP(timer_periph) = (uint32_t)remap;
}

/*!
    简介:      configure TIMER write CHxVAL register selection
    参数[输入]:  timer_periph: TIMERx(x=0,1,2,13,14,15,16)
    参数[输入]:  ccsel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_CHVSEL_DISABLE: no effect
      参数:        TIMER_CHVSEL_ENABLE:  when write the CHxVAL register, if the write value is same as the CHxVAL value, the write access is ignored
    参数[输出]:  无
    返回值:      无
*/
void timer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel) {
    if(TIMER_CHVSEL_ENABLE == ccsel) {
        TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_CHVSEL;
    } else if(TIMER_CHVSEL_DISABLE == ccsel) {
        TIMER_CFG(timer_periph) &= ~(uint32_t)TIMER_CFG_CHVSEL;
    } else {
        /* illegal parameters */
    }
}

/*!
    简介:      configure TIMER output value selection
    参数[输入]:  timer_periph: TIMERx(x=0,7)
    参数[输入]:  outsel:
                only one parameter can be selected which is shown as below:
      参数:        TIMER_OUTSEL_DISABLE: no effect
      参数:        TIMER_OUTSEL_ENABLE: if POEN and IOS is 0, the output disabled
    参数[输出]:  无
    返回值:      无
*/
void timer_output_value_selection_config(uint32_t timer_periph, uint16_t outsel) {
    if(TIMER_OUTSEL_ENABLE == outsel) {
        TIMER_CFG(timer_periph) |= (uint32_t)TIMER_CFG_OUTSEL;
    } else if(TIMER_OUTSEL_DISABLE == outsel) {
        TIMER_CFG(timer_periph) &= ~(uint32_t)TIMER_CFG_OUTSEL;
    } else {
        /* illegal parameters */
    }
}

/*!
    简介:      get TIMER flags
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  flag: the timer interrupt flags
                only one parameter can be selected which is shown as below:
      参数:        TIMER_FLAG_UP: update flag,TIMERx(x=0..13)
      参数:        TIMER_FLAG_CH0: channel 0 flag,TIMERx(x=0..4,7..13)
      参数:        TIMER_FLAG_CH1: channel 1 flag,TIMERx(x=0..4,7,8,11)
      参数:        TIMER_FLAG_CH2: channel 2 flag,TIMERx(x=0..4,7)
      参数:        TIMER_FLAG_CH3: channel 3 flag,TIMERx(x=0..4,7)
      参数:        TIMER_FLAG_CMT: channel control update flag,TIMERx(x=0,7)
      参数:        TIMER_FLAG_TRG: trigger flag,TIMERx(x=0,7,8,11)
      参数:        TIMER_FLAG_BRK: break flag,TIMERx(x=0,7)
      参数:        TIMER_FLAG_CH0O: channel 0 overcapture flag,TIMERx(x=0..4,7..11)
      参数:        TIMER_FLAG_CH1O: channel 1 overcapture flag,TIMERx(x=0..4,7,8,11)
      参数:        TIMER_FLAG_CH2O: channel 2 overcapture flag,TIMERx(x=0..4,7)
      参数:        TIMER_FLAG_CH3O: channel 3 overcapture flag,TIMERx(x=0..4,7)
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus timer_flag_get(uint32_t timer_periph, uint32_t flag) {
    if(RESET != (TIMER_INTF(timer_periph) & flag)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    简介:      clear TIMER flags
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  flag: the timer interrupt flags
                only one parameter can be selected which is shown as below:
      参数:        TIMER_FLAG_UP: update flag,TIMERx(x=0..13)
      参数:        TIMER_FLAG_CH0: channel 0 flag,TIMERx(x=0..4,7..13)
      参数:        TIMER_FLAG_CH1: channel 1 flag,TIMERx(x=0..4,7,8,11)
      参数:        TIMER_FLAG_CH2: channel 2 flag,TIMERx(x=0..4,7)
      参数:        TIMER_FLAG_CH3: channel 3 flag,TIMERx(x=0..4,7)
      参数:        TIMER_FLAG_CMT: channel control update flag,TIMERx(x=0,7)
      参数:        TIMER_FLAG_TRG: trigger flag,TIMERx(x=0,7,8,11)
      参数:        TIMER_FLAG_BRK: break flag,TIMERx(x=0,7)
      参数:        TIMER_FLAG_CH0O: channel 0 overcapture flag,TIMERx(x=0..4,7..11)
      参数:        TIMER_FLAG_CH1O: channel 1 overcapture flag,TIMERx(x=0..4,7,8,11)
      参数:        TIMER_FLAG_CH2O: channel 2 overcapture flag,TIMERx(x=0..4,7)
      参数:        TIMER_FLAG_CH3O: channel 3 overcapture flag,TIMERx(x=0..4,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_flag_clear(uint32_t timer_periph, uint32_t flag) {
    TIMER_INTF(timer_periph) = (~(uint32_t)flag);
}

/*!
    简介:      enable the TIMER interrupt
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  interrupt: timer interrupt enable source
                only one parameter can be selected which is shown as below:
      参数:        TIMER_INT_UP: update interrupt enable, TIMERx(x=0..13)
      参数:        TIMER_INT_CH0: channel 0 interrupt enable, TIMERx(x=0..4,7..13)
      参数:        TIMER_INT_CH1: channel 1 interrupt enable, TIMERx(x=0..4,7,8,11)
      参数:        TIMER_INT_CH2: channel 2 interrupt enable, TIMERx(x=0..4,7)
      参数:        TIMER_INT_CH3: channel 3 interrupt enable , TIMERx(x=0..4,7)
      参数:        TIMER_INT_CMT: commutation interrupt enable, TIMERx(x=0,7)
      参数:        TIMER_INT_TRG: trigger interrupt enable, TIMERx(x=0..4,7,8,11)
      参数:        TIMER_INT_BRK: break interrupt enable, TIMERx(x=0,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt) {
    TIMER_DMAINTEN(timer_periph) |= (uint32_t) interrupt;
}

/*!
    简介:      disable the TIMER interrupt
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  interrupt: timer interrupt source enable
                only one parameter can be selected which is shown as below:
      参数:        TIMER_INT_UP: update interrupt enable, TIMERx(x=0..13)
      参数:        TIMER_INT_CH0: channel 0 interrupt enable, TIMERx(x=0..4,7..13)
      参数:        TIMER_INT_CH1: channel 1 interrupt enable, TIMERx(x=0..4,7,8,11)
      参数:        TIMER_INT_CH2: channel 2 interrupt enable, TIMERx(x=0..4,7)
      参数:        TIMER_INT_CH3: channel 3 interrupt enable , TIMERx(x=0..4,7)
      参数:        TIMER_INT_CMT: commutation interrupt enable, TIMERx(x=0,7)
      参数:        TIMER_INT_TRG: trigger interrupt enable, TIMERx(x=0..4,7,8,11)
      参数:        TIMER_INT_BRK: break interrupt enable, TIMERx(x=0,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt) {
    TIMER_DMAINTEN(timer_periph) &= (~(uint32_t)interrupt);
}

/*!
    简介:      get timer interrupt flag
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  interrupt: the timer interrupt bits
                only one parameter can be selected which is shown as below:
      参数:        TIMER_INT_FLAG_UP: update interrupt flag,TIMERx(x=0..13)
      参数:        TIMER_INT_FLAG_CH0: channel 0 interrupt flag,TIMERx(x=0..4,7..13)
      参数:        TIMER_INT_FLAG_CH1: channel 1 interrupt flag,TIMERx(x=0..4,7,8,11)
      参数:        TIMER_INT_FLAG_CH2: channel 2 interrupt flag,TIMERx(x=0..4,7)
      参数:        TIMER_INT_FLAG_CH3: channel 3 interrupt flag,TIMERx(x=0..4,7)
      参数:        TIMER_INT_FLAG_CMT: channel commutation interrupt flag,TIMERx(x=0,7)
      参数:        TIMER_INT_FLAG_TRG: trigger interrupt flag,TIMERx(x=0,7,8,11)
      参数:        TIMER_INT_FLAG_BRK:  break interrupt flag,TIMERx(x=0,7)
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus timer_interrupt_flag_get(uint32_t timer_periph, uint32_t interrupt) {
    uint32_t val;
    val = (TIMER_DMAINTEN(timer_periph) & interrupt);

    if((RESET != (TIMER_INTF(timer_periph) & interrupt)) && (RESET != val)) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    简介:      clear TIMER interrupt flag
    参数[输入]:  timer_periph: please refer to the following parameters
    参数[输入]:  interrupt: the timer interrupt bits
                only one parameter can be selected which is shown as below:
      参数:        TIMER_INT_FLAG_UP: update interrupt flag,TIMERx(x=0..13)
      参数:        TIMER_INT_FLAG_CH0: channel 0 interrupt flag,TIMERx(x=0..4,7..13)
      参数:        TIMER_INT_FLAG_CH1: channel 1 interrupt flag,TIMERx(x=0..4,7,8,11)
      参数:        TIMER_INT_FLAG_CH2: channel 2 interrupt flag,TIMERx(x=0..4,7)
      参数:        TIMER_INT_FLAG_CH3: channel 3 interrupt flag,TIMERx(x=0..4,7)
      参数:        TIMER_INT_FLAG_CMT: channel commutation interrupt flag,TIMERx(x=0,7)
      参数:        TIMER_INT_FLAG_TRG: trigger interrupt flag,TIMERx(x=0,7,8,11)
      参数:        TIMER_INT_FLAG_BRK:  break interrupt flag,TIMERx(x=0,7)
    参数[输出]:  无
    返回值:      无
*/
void timer_interrupt_flag_clear(uint32_t timer_periph, uint32_t interrupt) {
    TIMER_INTF(timer_periph) = (~(uint32_t)interrupt);
}
