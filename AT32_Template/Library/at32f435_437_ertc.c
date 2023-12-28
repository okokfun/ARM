/**
  **************************************************************************
  * @file     at32f435_437_ertc.c
  * @brief    contains all the functions for the ertc firmware library
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
  * @{
  */

/** @defgroup ERTC
  * @brief ERTC driver modules
  * @{
  */

#ifdef ERTC_MODULE_EnableD

/** @defgroup ERTC_private_functions
  * @{
  */
#define ERTC_TIMEOUT         ((uint32_t) 0x00360000)

/**
  * @brief  number conversion to bcd code.
  * @param  num: number(0~99)
  * @retval bcd code.
  */
uint8_t ERTC_Num_To_BCD(uint8_t num) {
    uint8_t bcd_h = 0, bcd_l = 0;

    bcd_h = num / 10;
    bcd_l = num % 10;

    return  ((uint8_t)(bcd_h << 4) | bcd_l);
}

/**
  * @brief  bcd code conversion to number.
  * @param  bcd: bcd code(0~99).
  * @retval number.
  */
uint8_t ERTC_BCD_To_Num(uint8_t bcd) {
    return ((((uint8_t)(bcd & (uint8_t)0xF0) >> 4) * 10) + (bcd & (uint8_t)0x0F));
}

/**
  * @brief  enable write protection.
  * @param  无.
  * @retval 无
  */
void ERTC_Write_Protect_Enable(void) {
    ERTC->wp = 0xFF;
}

/**
  * @brief  禁用写保护.
  * @param  无.
  * @retval 无
  */
void ERTC_Write_Protect_Disable(void) {
    ERTC->wp = 0xCA;
    ERTC->wp = 0x53;
}

/**
  * @brief  ertc wait register update finish.
  * @param  无.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Wait_Update(void) {
    uint32_t timeout = ERTC_TIMEOUT * 2;

    /* clear updf flag */
    ERTC->sts = ~(ERTC_UPDF_FLAG | 0x00000080) | (ERTC->sts_bit.imen << 7);

    while(ERTC->sts_bit.updf == 0) {
        if(timeout == 0) {
            return ERROR;
        }

        timeout--;
    }

    return SUCCESS;
}

/**
  * @brief  ertc wait flag status.
  * @param  flag: flag to wait.
  *         该参数可以是以下值之一:
  *         - ERTC_ALAWF_FLAG: alarm a register allows write flag.
  *         - ERTC_ALBWF_FLAG: alarm b register allows write flag.
  *         - ERTC_WATWF_FLAG: wakeup timer register allows write flag.
  *         - ERTC_TADJF_FLAG: time adjustment flag.
  *         - ERTC_CALUPDF_FLAG: calibration value update completed flag.
  * @param  status: status to wait.
  *         该参数可以是以下值之一:
  *         - SET.
  *         - RESET.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Wait_flag(uint32_t flag, flag_status status) {
    uint32_t timeout = ERTC_TIMEOUT;

    while(ERTC_Flag_Get(flag) == status) {
        if(timeout == 0) {
            /* enable write protection */
            ERTC_Write_Protect_Enable();

            return ERROR;
        }

        timeout--;
    }

    return SUCCESS;
}

/**
  * @brief  ertc enter init mode.
  * @param  无.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Init_Mode_Enter(void) {
    uint32_t timeout = ERTC_TIMEOUT * 2;

    if(ERTC->sts_bit.imf == 0) {
        /* enter init mode */
        ERTC->sts = 0xFFFFFFFF;

        while(ERTC->sts_bit.imf == 0) {
            if(timeout == 0) {
                /* enable write protection */
                ERTC_Write_Protect_Enable();

                return ERROR;
            }

            timeout--;
        }
    }

    return SUCCESS;
}

/**
  * @brief  ertc exit init mode.
  * @param  无.
  * @retval 无.
  */
void ERTC_Init_Mode_Exit(void) {
    ERTC->sts = 0xFFFFFF7F;
}

/**
  * @brief  ertc reset all register.
  * @param  无.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Reset(void) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl = (uint32_t)0x00000000;

    /* enter init mode */
    if(ERTC_Init_Mode_Enter() != SUCCESS) {
        return ERROR;
    }

    /* reset register */
    ERTC->time   = (uint32_t)0x00000000;
    ERTC->date   = (uint32_t)0x00002101;
    ERTC->ctrl   = (uint32_t)0x00000000;
    ERTC->div    = (uint32_t)0x007F00FF;
    ERTC->wat    = (uint32_t)0x0000FFFF;
    ERTC->ccal   = (uint32_t)0x00000000;
    ERTC->ala    = (uint32_t)0x00000000;
    ERTC->alb    = (uint32_t)0x00000000;
    ERTC->tadj   = (uint32_t)0x00000000;
    ERTC->scal   = (uint32_t)0x00000000;
    ERTC->tamp   = (uint32_t)0x00000000;
    ERTC->alasbs = (uint32_t)0x00000000;
    ERTC->albsbs = (uint32_t)0x00000000;
    ERTC->sts    = (uint32_t)0x00000000;

    /* wait calendar update */
    ERTC_Wait_Update();

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  ertc division set.
  * @param  div_a: division a (0~0x7F).
  * @param  div_b: division b (0~0x7FFF).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Divider_Set(uint16_t div_a, uint16_t div_b) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    /* enter init mode */
    if(ERTC_Init_Mode_Enter() != SUCCESS) {
        return ERROR;
    }

    /* config the ertc divider */
    ERTC->div_bit.diva = div_a;
    ERTC->div_bit.divb = div_b;

    /* exit init mode */
    ERTC_Init_Mode_Exit();

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  ertc hour mode set.
  * @param  mode: hour mode.
  *         该参数可以是以下值之一:
  *         - ERTC_HOUR_Mode_24: 24-hour format.
  *         - ERTC_HOUR_Mode_12: 12-hour format.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_hour_Mode_Set(ERTC_hour_Mode_Set_Type mode) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    /* enter init mode */
    if(ERTC_Init_Mode_Enter() != SUCCESS) {
        return ERROR;
    }

    /* write register */
    ERTC->ctrl_bit.hm = mode;

    /* exit init mode */
    ERTC_Init_Mode_Exit();

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  set date.
  * @param  year: year (0~99).
  * @param  month: month (1~12).
  * @param  date: date (1~31).
  * @param  week: week (1~7).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Date_Set(uint8_t year, uint8_t month, uint8_t date, uint8_t week) {
    ERTC_reg_Date_Type reg;

    reg.date = 0;

    reg.date_bit.y  = ERTC_Num_To_BCD(year);
    reg.date_bit.m  = ERTC_Num_To_BCD(month);
    reg.date_bit.d  = ERTC_Num_To_BCD(date);
    reg.date_bit.wk = week;

    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    /* enter init mode */
    if(ERTC_Init_Mode_Enter() != SUCCESS) {
        return ERROR;
    }

    /* set the ERTC_date register */
    ERTC->date = reg.date;

    /* exit init mode */
    ERTC_Init_Mode_Exit();

    if(ERTC->ctrl_bit.dren == 0) {
        ERTC_Wait_Update();
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  set time.
  * @param  hour: hour (0~23).
  * @param  min: minute (0~59).
  * @param  sec: second (0~59).
  * @param  ampm: hour mode.
  *         该参数可以是以下值之一:
  *         - ERTC_24H: 24-hour format.
  *         - ERTC_AM: 12-hour format, ante meridiem.
  *         - ERTC_PM: 12-hour format, post meridiem.
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Time_Set(uint8_t hour, uint8_t min, uint8_t sec, ERTC_am_pm_Type ampm) {
    ERTC_reg_Time_Type reg;

    reg.time = 0;

    reg.time_bit.h = ERTC_Num_To_BCD(hour);
    reg.time_bit.m = ERTC_Num_To_BCD(min);
    reg.time_bit.s = ERTC_Num_To_BCD(sec);
    reg.time_bit.ampm = ampm;

    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    /* enter init mode */
    if(ERTC_Init_Mode_Enter() != SUCCESS) {
        return ERROR;
    }

    ERTC->time = reg.time;

    /* exit init mode */
    ERTC_Init_Mode_Exit();

    if(ERTC->ctrl_bit.dren == 0) {
        ERTC_Wait_Update();
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  get calendar
  * @param  time: ertc time.
  * @retval 无.
  */
void ERTC_Calendar_Get(ERTC_Time_Type* time) {
    ERTC_reg_Time_Type reg_tm;
    ERTC_reg_Date_Type reg_dt;

    reg_tm.time = ERTC->time;
    reg_dt.date = ERTC->date;

    time->hour  = ERTC_BCD_To_Num(reg_tm.time_bit.h);
    time->min   = ERTC_BCD_To_Num(reg_tm.time_bit.m);
    time->sec   = ERTC_BCD_To_Num(reg_tm.time_bit.s);
    time->ampm  = (ERTC_am_pm_Type)reg_tm.time_bit.ampm;

    time->year  = ERTC_BCD_To_Num(reg_dt.date_bit.y);
    time->month = ERTC_BCD_To_Num(reg_dt.date_bit.m);
    time->day   = ERTC_BCD_To_Num(reg_dt.date_bit.d);
    time->week  = reg_dt.date_bit.wk;
}

/**
  * @brief  get current sub second.
  * @param  无.
  * @retval sub second.
  */
uint32_t ERTC_Sub_Second_Get(void) {
    uint32_t reg = 0;

    reg = ERTC->sbs;

    (void) (ERTC->date);

    return (reg);
}

/**
  * @brief  set which bits are irrelevant to the alarm match.
  * @param  alarm_x: select the alarm.
  *         该参数可以是以下值之一:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  mask: select which bits are irrelevant to the alarm match.
  *         该参数可以是以下值之一:
  *         - ERTC_Alarm_Mask_NONE: match all.
  *         - ERTC_Alarm_Mask_SEC: don't match seconds.
  *         - ERTC_Alarm_Mask_MIN: don't match minute.
  *         - ERTC_Alarm_Mask_HOUR: don't match hour.
  *         - ERTC_Alarm_Mask_Date_WEEK: don't match date or week.
  *         - ERTC_Alarm_Mask_ALL: don't match all.
  * @param  alarm: alarm para.
  * @retval 无.
  */
void ERTC_Alarm_Mask_Set(ERTC_Alarm_Type alarm_x, uint32_t mask) {
    uint32_t reg;

    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(alarm_x == ERTC_ALA) {
        reg = ERTC->ala;

        reg &= ~ERTC_Alarm_Mask_ALL;
        reg |= mask;

        ERTC->ala = reg;
    } else {
        reg = ERTC->alb;

        reg &= ~ERTC_Alarm_Mask_ALL;
        reg |= mask;

        ERTC->alb = reg;
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  alarm week or date mode select.
  * @param  alarm_x: select the alarm.
  *         该参数可以是以下值之一:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  wk: week or date mode select.
  *         该参数可以是以下值之一:
  *         - ERTC_SLECT_DATE: slect date mode.
  *         - ERTC_SLECT_WEEK: slect week mode.
  * @retval 无.
  */
void ERTC_Alarm_week_Date_Select(ERTC_Alarm_Type alarm_x, ERTC_week_Date_Select_Type wk) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(alarm_x == ERTC_ALA) {
        ERTC->ala_bit.wksel = wk;
    } else {
        ERTC->alb_bit.wksel = wk;
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set alarm.
  * @param  alarm_x: select the alarm.
  *         该参数可以是以下值之一:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  week_day: week or date.
  *         - week: 1~7.
  *         - date: 1~31.
  * @param  hour: hour (0~23).
  * @param  min: minute (0~59).
  * @param  sec: second (0~59).
  * @param  ampm: hour mode.
  *         该参数可以是以下值之一:
  *         - ERTC_24H: 24-hour format.
  *         - ERTC_AM: 12-hour format, ante meridiem.
  *         - ERTC_PM: 12-hour format, post meridiem.
  * @param  alarm: alarm para.
  * @retval 无.
  */
void ERTC_Alarm_Set(ERTC_Alarm_Type alarm_x, uint8_t week_date, uint8_t hour, uint8_t min, uint8_t sec, ERTC_am_pm_Type ampm) {
    ERTC_reg_Alarm_Type reg;

    if(alarm_x == ERTC_ALA) {
        reg.ala = ERTC->ala;
    } else {
        reg.ala = ERTC->alb;
    }

    reg.ala_bit.d = ERTC_Num_To_BCD(week_date);
    reg.ala_bit.h = ERTC_Num_To_BCD(hour);
    reg.ala_bit.m = ERTC_Num_To_BCD(min);
    reg.ala_bit.s = ERTC_Num_To_BCD(sec);
    reg.ala_bit.ampm = ampm;

    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(alarm_x == ERTC_ALA) {
        ERTC->ala = reg.ala;
    } else {
        ERTC->alb = reg.ala;
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set alarm sub second.
  * @param  alarm_x: select the alarm.
  *         该参数可以是以下值之一:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  value: sub second value.
  * @param  mask: sub second mask.
  *         该参数可以是以下值之一:
  *         - ERTC_Alarm_SBS_Mask_ALL: do not match the sub-second.
  *         - ERTC_Alarm_SBS_Mask_14_1: only compare bit [0].
  *         - ERTC_Alarm_SBS_Mask_14_2: only compare bit [1:0].
  *         - ERTC_Alarm_SBS_Mask_14_3: only compare bit [2:0].
  *         - ERTC_Alarm_SBS_Mask_14_4: only compare bit [3:0].
  *         - ERTC_Alarm_SBS_Mask_14_5: only compare bit [4:0].
  *         - ERTC_Alarm_SBS_Mask_14_6: only compare bit [5:0].
  *         - ERTC_Alarm_SBS_Mask_14_7: only compare bit [6:0].
  *         - ERTC_Alarm_SBS_Mask_14_8: only compare bit [7:0].
  *         - ERTC_Alarm_SBS_Mask_14_9: only compare bit [8:0].
  *         - ERTC_Alarm_SBS_Mask_14_10: only compare bit [9:0].
  *         - ERTC_Alarm_SBS_Mask_14_11: only compare bit [10:0].
  *         - ERTC_Alarm_SBS_Mask_14_12: only compare bit [11:0].
  *         - ERTC_Alarm_SBS_Mask_14_13: only compare bit [12:0].
  *         - ERTC_Alarm_SBS_Mask_14: only compare bit [13:0].
  *         - ERTC_Alarm_SBS_Mask_NONE:  compare bit [14:0].
  * @retval 无.
  */
void ERTC_Alarm_Sub_Second_Set(ERTC_Alarm_Type alarm_x, uint32_t value, ERTC_Alarm_sbs_Mask_Type mask) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(alarm_x == ERTC_ALA) {
        ERTC->alasbs_bit.sbsmsk = mask;
        ERTC->alasbs_bit.sbs = value;
    } else {
        ERTC->albsbs_bit.sbsmsk = mask;
        ERTC->albsbs_bit.sbs = value;
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  enable or disable alarm clock.
  * @param  alarm_x: select the alarm.
  *         该参数可以是以下值之一:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  new_state (TRUE or FALSE).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Alarm_Enable(ERTC_Alarm_Type alarm_x, confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(alarm_x == ERTC_ALA) {
        ERTC->ctrl_bit.alaen = new_state;

        if(new_state == FALSE) {
            if(ERTC_Wait_flag(ERTC_ALAWF_FLAG, RESET) != SUCCESS) {
                return ERROR;
            }
        }
    } else {
        ERTC->ctrl_bit.alben = new_state;

        if(new_state == FALSE) {
            if(ERTC_Wait_flag(ERTC_ALBWF_FLAG, RESET) != SUCCESS) {
                return ERROR;
            }
        }
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  get alarm value.
  * @param  alarm_x: select the alarm.
  *         该参数可以是以下值之一:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @param  alarm: alarm para.
  * @retval 无.
  */
void ERTC_Alarm_Get(ERTC_Alarm_Type alarm_x, ERTC_Alarm_Value_Type* alarm) {
    ERTC_reg_Alarm_Type reg;

    reg.ala = 0;

    if(alarm_x == ERTC_ALA) {
        reg.ala = ERTC->ala;
    } else {
        reg.ala = ERTC->alb;
    }

    alarm->day           = ERTC_BCD_To_Num(reg.ala_bit.d);
    alarm->week          = ERTC_BCD_To_Num(reg.ala_bit.d);
    alarm->hour          = ERTC_BCD_To_Num(reg.ala_bit.h);
    alarm->min           = ERTC_BCD_To_Num(reg.ala_bit.m);
    alarm->sec           = ERTC_BCD_To_Num(reg.ala_bit.s);
    alarm->ampm          = (ERTC_am_pm_Type)reg.ala_bit.ampm;
    alarm->week_Date_sel = reg.ala_bit.wksel;
    alarm->mask          = reg.ala & ERTC_Alarm_Mask_ALL;
}

/**
  * @brief  get alarm sub second.
  * @param  alarm_x: select the alarm.
  *         该参数可以是以下值之一:
  *         - ERTC_ALA: alarm a.
  *         - ERTC_ALB: alarm b.
  * @retval sub second.
  */
uint32_t ERTC_Alarm_Sub_Second_Get(ERTC_Alarm_Type alarm_x) {
    if(alarm_x == ERTC_ALA) {
        return (ERTC->alasbs_bit.sbs);
    } else {
        return (ERTC->albsbs_bit.sbs);
    }
}

/**
  * @brief  set wakeup timer clock.
  * @param  clock: wakeup timer 时钟源.
  *         该参数可以是以下值之一:
  *         - ERTC_WAT_CLK_ERTCCLK_DIV16: ERTC_CLK / 16.
  *         - ERTC_WAT_CLK_ERTCCLK_DIV8: ERTC_CLK / 8.
  *         - ERTC_WAT_CLK_ERTCCLK_DIV4: ERTC_CLK / 4.
  *         - ERTC_WAT_CLK_ERTCCLK_DIV2: ERTC_CLK / 2.
  *         - ERTC_WAT_CLK_CK_B_16BITS: CK_B, wakeup counter = ERTC_WAT
  *         - ERTC_WAT_CLK_CK_B_17BITS: CK_B, wakeup counter = ERTC_WAT + 65535.
  * @retval 无.
  */
void ERTC_WakeUp_Clock_Set(ERTC_WakeUp_Clock_Type clock) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl_bit.watclk = clock;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set wakeup counter.
  * @param  counter: wakeup counter(0~65535).
  * @retval 无.
  */
void ERTC_WakeUp_Counter_Set(uint32_t counter) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->wat_bit.val = counter;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  get wakeup counter.
  * @param  无.
  * @retval wakeup counter.
  */
uint16_t ERTC_WakeUp_Counter_Get(void) {
    return ERTC->wat_bit.val;
}

/**
  * @brief  enable or disable wakeup timer.
  * @param  new_state (TRUE or FALSE).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_WakeUp_Enable(confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl_bit.waten = new_state;

    if(new_state == FALSE) {
        if(ERTC_Wait_flag(ERTC_WATWF_FLAG, RESET) != SUCCESS) {
            return ERROR;
        }
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  config the smooth calibration.
  * @param  period: calibration period.
  *         该参数可以是以下值之一:
  *         - ERTC_Smooth_CAL_Period_32: 32 second calibration period.
  *         - ERTC_Smooth_CAL_Period_16: 16 second calibration period.
  *         - ERTC_Smooth_CAL_Period_8: 8 second calibration period.
  * @param  clk_add: add clock.
  *         该参数可以是以下值之一:
  *         - ERTC_Smooth_CAL_CLK_ADD_0: do not increase clock.
  *         - ERTC_Smooth_CAL_CLK_ADD_512: add 512 clocks.
  * @param  clk_dec: decrease clock(0~511).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Smooth_Calibration_Config(ERTC_Smooth_CAL_Period_Type period, ERTC_Smooth_CAL_CLK_add_Type clk_add, uint32_t clk_dec) {
    ERTC_reg_scal_Type reg;

    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(ERTC_Wait_flag(ERTC_CALUPDF_FLAG, SET) != SUCCESS) {
        return ERROR;
    }

    reg.scal = 0;

    switch (period) {
        case ERTC_Smooth_CAL_Period_32:
            break;

        case ERTC_Smooth_CAL_Period_16:
            reg.scal_bit.cal16 = 1;
            break;

        case ERTC_Smooth_CAL_Period_8:
            reg.scal_bit.cal8 = 1;
            break;

        default:
            break;
    }

    reg.scal_bit.add = clk_add;
    reg.scal_bit.dec = clk_dec;

    ERTC->scal = reg.scal;

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  set the coarse digital calibration.
  * @param  dir: calibration direction.
  *         该参数可以是以下值之一:
  *         - ERTC_CAL_Dir_POSITIVE: positive calibration.
  *         - ERTC_CAL_Dir_NEGATIVE: negative calibration.
  * @param  value: calibration value(0~31).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Coarse_Calibration_Set(ERTC_CAL_Direction_Type dir, uint32_t value) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    /* enter init mode */
    if(ERTC_Init_Mode_Enter() == ERROR) {
        return ERROR;
    }

    ERTC->ccal_bit.caldir = dir;

    ERTC->ccal_bit.calval = value;

    /* exit init mode */
    ERTC_Init_Mode_Exit();

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  enable or disable coarse calibration.
  * @param  new_state (TRUE or FALSE).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Coarse_Calibration_Enable(confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    /* enter init mode */
    if(ERTC_Init_Mode_Enter() == ERROR) {
        return ERROR;
    }

    ERTC->ctrl_bit.ccalen = new_state;

    /* exit init mode */
    ERTC_Init_Mode_Exit();

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  calibration output source select.
  * @param  output: output source.
  *         该参数可以是以下值之一:
  *         - ERTC_CAL_OutPut_512HZ: output 512 hz.
  *         - ERTC_CAL_OutPut_1HZ: output 1 hz.
  * @retval 无.
  */
void ERTC_CAL_OutPut_Select(ERTC_CAL_OutPut_Select_Type output) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl_bit.calosel = output;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  enable or disable calibration output.
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void ERTC_CAL_OutPut_Enable(confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl_bit.caloen = new_state;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  adjust the time.
  * @param  add1s: second operation.
  *         该参数可以是以下值之一:
  *         - ERTC_Time_ADD_NONE: none operation.
  *         - ERTC_Time_ADD_1S: add 1 second.
  * @param  decsbs: decrease sub second(0~0x7FFF).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_Time_Adjust(ERTC_Time_Adjust_Type add1s, uint32_t decsbs) {
    ERTC_reg_tadj_Type reg;

    reg.tadj = 0;

    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(ERTC_Wait_flag(ERTC_TADJF_FLAG, SET) != SUCCESS) {
        return ERROR;
    }

    /* check if the reference clock detection is disabled */
    if(ERTC->ctrl_bit.rcden == 0) {
        reg.tadj_bit.add1s = add1s;
        reg.tadj_bit.decsbs = decsbs;

        ERTC->tadj = reg.tadj;

        if(ERTC_Wait_Update() == ERROR) {
            return ERROR;
        }
    } else {
        return ERROR;
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  config the daylight saving time.
  * @param  operation: time adjust.
  *         该参数可以是以下值之一:
  *         - ERTC_DST_ADD_1H: add 1 hour.
  *         - ERTC_DST_DEC_1H: dec 1 hour.
  * @param  save: operation save.
  *         该参数可以是以下值之一:
  *         - ERTC_DST_SAVE_0: set the bpr register value to 0.
  *         - ERTC_DST_SAVE_1: set the bpr register value to 1.
  * @retval 无.
  */
void ERTC_DayLight_Set(ERTC_dst_Operation_Type operation, ERTC_dst_save_Type save) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(operation == ERTC_DST_ADD_1H) {
        ERTC->ctrl_bit.add1h = 1;
    } else {
        ERTC->ctrl_bit.dec1h = 1;
    }

    ERTC->ctrl_bit.bpr = save;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  get the bpr value.
  * @param  无.
  * @retval bpr value.
  */
uint8_t ERTC_DayLight_BPR_Get(void) {
    return ERTC->ctrl_bit.bpr;
}

/**
  * @brief  enable or disable refer clock detect.
  * @param  new_state (TRUE or FALSE).
  * @retval error_status (ERROR or SUCCESS).
  */
error_status ERTC_refer_Clock_Detect_Enable(confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    /* enter init mode */
    if(ERTC_Init_Mode_Enter() != SUCCESS) {
        return ERROR;
    }

    /* write register */
    ERTC->ctrl_bit.rcden = new_state;

    /* exit init mode */
    ERTC_Init_Mode_Exit();

    /* enable write protection */
    ERTC_Write_Protect_Enable();

    return SUCCESS;
}

/**
  * @brief  enable or disable direct read mode.
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void ERTC_Direct_Read_Enable(confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl_bit.dren = new_state;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set the output mode.
  * @param  source: output source.
  *         该参数可以是以下值之一:
  *         - ERTC_OutPut_Disable: diable output.
  *         - ERTC_OutPut_Alarm_A: output alarm a event.
  *         - ERTC_OutPut_Alarm_B: output alarm b event.
  *         - ERTC_OutPut_WAKEUP: output wakeup event.
  * @param  polarity: output polarity.
  *         该参数可以是以下值之一:
  *         - ERTC_OutPut_Polarity_HIGH: when the event occurs, the output is high.
  *         - ERTC_OutPut_Polarity_LOW: when the event occurs, the output is low.
  * @param  type: output type.
  *         该参数可以是以下值之一:
  *         - ERTC_OutPut_Type_Open_DRAIN: open drain output.
  *         - ERTC_OutPut_Type_PUSH_PULL: push pull output.
  * @retval 无.
  */
void ERTC_OutPut_Set(ERTC_OutPut_Source_Type source, ERTC_OutPut_Polarity_Type polarity, ERTC_OutPut_Type type) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl_bit.outp = polarity;

    ERTC->tamp_bit.outtype = type;

    ERTC->ctrl_bit.outsel = source;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  timestamp detection pin selection.
  * @param  pin: data register
  *         该参数可以是以下值之一:
  *         - ERTC_Pin_PC13: pc13 is used as timestamp detection pin.
  *         - ERTC_Pin_PA0: pa0 is used as timestamp detection pin.
  * @retval data value.
  */
void ERTC_TimeStamp_Pin_Select(ERTC_Pin_Select_Type pin) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->tamp_bit.tspin = pin;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set the timestamp valid edge.
  * @param  edge: calibration period.
  *         该参数可以是以下值之一:
  *         - ERTC_TimeStamp_Edge_RISING : rising edge trigger.
  *         - ERTC_TimeStamp_Edge_FALLING: falling edge trigger.
  * @retval 无.
  */
void ERTC_TimeStamp_Valid_Edge_Set(ERTC_TimeStamp_Valid_Edge_Type edge) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl_bit.tsedg = edge;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  enable or disable timestamp.
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void ERTC_TimeStamp_Enable(confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->ctrl_bit.tsen = new_state;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  get the timestamp.
  * @param  time: time.
  * @param  date: date.
  * @retval 无.
  */
void ERTC_TimeStamp_Get(ERTC_Time_Type* time) {
    ERTC_reg_tstm_Type tmtime;
    ERTC_reg_tsdt_Type tmdate;

    tmtime.tstm = ERTC->tstm;
    tmdate.tsdt = ERTC->tsdt;

    time->year  = 0;
    time->month = ERTC_BCD_To_Num(tmdate.tsdt_bit.m);
    time->day   = ERTC_BCD_To_Num(tmdate.tsdt_bit.d);
    time->week  = ERTC_BCD_To_Num(tmdate.tsdt_bit.wk);
    time->hour  = ERTC_BCD_To_Num(tmtime.tstm_bit.h);
    time->min   = ERTC_BCD_To_Num(tmtime.tstm_bit.m);
    time->sec   = ERTC_BCD_To_Num(tmtime.tstm_bit.s);
    time->ampm  = (ERTC_am_pm_Type)tmtime.tstm_bit.ampm;
}

/**
  * @brief  get the timestamp sub second.
  * @param  无.
  * @retval timestamp sub second.
  */
uint32_t ERTC_TimeStamp_Sub_Second_Get(void) {
    return ERTC->tssbs_bit.sbs;
}

/**
  * @brief  tamper 1 detection pin selection.
  * @param  pin: data register
  *         该参数可以是以下值之一:
  *         - ERTC_Pin_PC13: pc13 is used as tamper 1 detection pin.
  *         - ERTC_Pin_PA0: pa0 is used as tamper 1 detection pin.
  * @retval data value.
  */
void ERTC_Tamper_1_Pin_Select(ERTC_Pin_Select_Type pin) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->tamp_bit.tp1pin = pin;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  enable or disable tamper pin pull up.
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void ERTC_Tamper_Pull_Up_Enable(confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->tamp_bit.tppu = !new_state;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set the tamper pin pre-charge time.
  * @param  precharge: tamper detection pre-charge time
  *         该参数可以是以下值之一:
  *         - ERTC_Tamper_PR_1_ERTCCLK: pre-charge time is 1 ERTC_CLK.
  *         - ERTC_Tamper_PR_2_ERTCCLK: pre-charge time is 2 ERTC_CLK.
  *         - ERTC_Tamper_PR_4_ERTCCLK: pre-charge time is 4 ERTC_CLK.
  *         - ERTC_Tamper_PR_8_ERTCCLK: pre-charge time is 8 ERTC_CLK.
  * @retval 无.
  */
void ERTC_Tamper_Precharge_Set(ERTC_Tamper_Precharge_Type precharge) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->tamp_bit.tppr = precharge;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set the tamper filter time.
  * @param  filter: tamper filter.
  *         该参数可以是以下值之一:
  *         - ERTC_Tamper_Filter_Disable: disable filter function.
  *         - ERTC_Tamper_Filter_2: 2 consecutive samples arw valid, effective tamper event.
  *         - ERTC_Tamper_Filter_4: 4 consecutive samples arw valid, effective tamper event.
  *         - ERTC_Tamper_Filter_8: 8 consecutive samples arw valid, effective tamper event.
  * @retval 无.
  */
void ERTC_Tamper_Filter_Set(ERTC_Tamper_Filter_Type filter) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->tamp_bit.tpflt = filter;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set the tamper detection frequency.
  * @param  freq: tamper detection frequency.
  *         该参数可以是以下值之一:
  *         - ERTC_Tamper_Freq_Div_32768: ERTC_CLK / 32768.
  *         - ERTC_Tamper_Freq_Div_16384: ERTC_CLK / 16384.
  *         - ERTC_Tamper_Freq_Div_8192: ERTC_CLK / 8192.
  *         - ERTC_Tamper_Freq_Div_4096: ERTC_CLK / 4096.
  *         - ERTC_Tamper_Freq_Div_2048: ERTC_CLK / 2048.
  *         - ERTC_Tamper_Freq_Div_1024: ERTC_CLK / 1024.
  *         - ERTC_Tamper_Freq_Div_512: ERTC_CLK / 512.
  *         - ERTC_Tamper_Freq_Div_256: ERTC_CLK / 256.
  * @retval 无.
  */
void ERTC_Tamper_Detect_Freq_Set(ERTC_Tamper_Detect_Freq_Type freq) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->tamp_bit.tpfreq = freq;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  set the tamper trigger.
  * @param  tamper_x: select the tamper.
  *         该参数可以是以下值之一:
  *         - ERTC_Tamper_1: tamper 1.
  *         - ERTC_Tamper_2: tamper 2.
  * @param  trigger: tamper valid edge.
  *         该参数可以是以下值之一:
  *         - ERTC_Tamper_Edge_RISING: rising gedge.
  *         - ERTC_Tamper_Edge_FALLING: falling gedge.
  *         - ERTC_Tamper_Edge_LOW: low level.
  *         - ERTC_Tamper_Edge_HIGH: high level.
  * @param  alarm: alarm para.
  * @retval 无.
  */
void ERTC_Tamper_Valid_Edge_Set(ERTC_Tamper_Select_Type tamper_x, ERTC_Tamper_Valid_Edge_Type trigger) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(tamper_x == ERTC_Tamper_1) {
        ERTC->tamp_bit.tp1edg = trigger;
    } else {
        ERTC->tamp_bit.tp2edg = trigger;
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  enable or disable trigger timestamp when tamper event occurs.
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void ERTC_Tamper_TimeStamp_Enable(confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    ERTC->tamp_bit.tptsen = new_state;

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  enable or disable tamper.
  * @param  tamper_x: select the tamper.
  *         该参数可以是以下值之一:
  *         - ERTC_Tamper_1: tamper 1.
  *         - ERTC_Tamper_2: tamper 2.
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void ERTC_Tamper_Enable(ERTC_Tamper_Select_Type tamper_x, confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(tamper_x == ERTC_Tamper_1) {
        ERTC->tamp_bit.tp1en = new_state;
    } else {
        ERTC->tamp_bit.tp2en = new_state;
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  enable or disable interrupt.
  * @param  source: interrupts sources
  *         该参数可以是以下值的任意组合:
  *         - ERTC_TP_INT: tamper interrupt.
  *         - ERTC_ALA_INT: alarm a interrupt.
  *         - ERTC_ALB_INT: alarm b interrupt.
  *         - ERTC_WAT_INT: wakeup timer interrupt.
  *         - ERTC_TS_INT: timestamp interrupt.
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void ERTC_Interrupt_Enable(uint32_t source, confirm_state new_state) {
    /* 禁用写保护 */
    ERTC_Write_Protect_Disable();

    if(source & ERTC_TP_INT) {
        if(new_state != FALSE) {
            ERTC->tamp |= ERTC_TP_INT;
        } else {
            ERTC->tamp &= ~ERTC_TP_INT;
        }

        source &= ~ERTC_TP_INT;
    }

    if(new_state != FALSE) {
        ERTC->ctrl |= source;
    } else {
        ERTC->ctrl &= ~source;
    }

    /* enable write protection */
    ERTC_Write_Protect_Enable();
}

/**
  * @brief  get interrupt status
  * @param  source
  *         该参数可以是以下值之一:
  *         - ERTC_TP_INT: tamper interrupt.
  *         - ERTC_ALA_INT: alarm a interrupt.
  *         - ERTC_ALB_INT: alarm b interrupt.
  *         - ERTC_WAT_INT: wakeup timer interrupt.
  *         - ERTC_TS_INT: timestamp interrupt.
  * @retval flag_status (SET or RESET)
  */
flag_status ERTC_Interrupt_Get(uint32_t source) {
    if(source & ERTC_TP_INT) {
        if((ERTC->tamp & ERTC_TP_INT) != RESET) {
            return SET;
        } else {
            return RESET;
        }
    }

    if((ERTC->ctrl & source) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  get flag status.
  * @param  flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - ERTC_ALAWF_FLAG: alarm a register allows write flag.
  *         - ERTC_ALBWF_FLAG: alarm b register allows write flag.
  *         - ERTC_WATWF_FLAG: wakeup timer register allows write flag.
  *         - ERTC_TADJF_FLAG: time adjustment flag.
  *         - ERTC_InitF_FLAG: calendar initialization flag.
  *         - ERTC_UPDF_FLAG: calendar update flag.
  *         - ERTC_IMF_FLAG: enter initialization mode flag.
  *         - ERTC_ALAF_FLAG: alarm clock a flag.
  *         - ERTC_ALBF_FLAG: alarm clock b flag.
  *         - ERTC_WATF_FLAG: wakeup timer flag.
  *         - ERTC_TSF_FLAG: timestamp flag.
  *         - ERTC_TSOF_FLAG: timestamp overflow flag.
  *         - ERTC_TP1F_FLAG: tamper detection 1 flag.
  *         - ERTC_TP2F_FLAG: tamper detection 2 flag.
  *         - ERTC_CALUPDF_FLAG: calibration value update completed flag.
  * @retval the new state of flag (SET or RESET).
  */
flag_status ERTC_Flag_Get(uint32_t flag) {
    if((ERTC->sts & flag) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  clear flag status
  * @param  flag: 指定flag to clear.
  *         该参数可以是以下值的任意组合:
  *         - ERTC_ALAWF_FLAG: alarm a register allows write flag.
  *         - ERTC_ALBWF_FLAG: alarm b register allows write flag.
  *         - ERTC_WATWF_FLAG: wakeup timer register allows write flag.
  *         - ERTC_TADJF_FLAG: time adjustment flag.
  *         - ERTC_InitF_FLAG: calendar initialization flag.
  *         - ERTC_UPDF_FLAG: calendar update flag.
  *         - ERTC_IMF_FLAG: enter initialization mode flag.
  *         - ERTC_ALAF_FLAG: alarm clock a flag.
  *         - ERTC_ALBF_FLAG: alarm clock b flag.
  *         - ERTC_WATF_FLAG: wakeup timer flag.
  *         - ERTC_TSF_FLAG: timestamp flag.
  *         - ERTC_TSOF_FLAG: timestamp overflow flag.
  *         - ERTC_TP1F_FLAG: tamper detection 1 flag.
  *         - ERTC_TP2F_FLAG: tamper detection 2 flag.
  *         - ERTC_CALUPDF_FLAG: calibration value update completed flag.
  * @retval 无
  */
void ERTC_Flag_Clear(uint32_t flag) {
    ERTC->sts = ~(flag | 0x00000080) | (ERTC->sts_bit.imen << 7);
}

/**
  * @brief  write data to the bpr register.
  * @param  dt: data register
  *         该参数可以是以下值之一:
  *         - ERTC_DT1
  *         - ERTC_DT2
  *         - ...
  *         - ERTC_DT19
  *         - ERTC_DT20
  * @param  data: data to be write.
  * @retval 无.
  */
void ERTC_BPR_Data_Write(ERTC_dt_Type dt, uint32_t data) {
    __IO uint32_t reg = 0;

    reg = ERTC_BASE + 0x50 + (dt * 4);

    *(__IO uint32_t *)reg = data;
}

/**
  * @brief  read data from bpr register.
  * @param  dt: data register
  *         该参数可以是以下值之一:
  *         - ERTC_DT1
  *         - ERTC_DT2
  *         - ...
  *         - ERTC_DT19
  *         - ERTC_DT20
  * @retval data value.
  */
uint32_t ERTC_BPR_Data_Read(ERTC_dt_Type dt) {
    __IO uint32_t reg = 0;

    reg = ERTC_BASE + 0x50 + (dt * 4);

    return (*(__IO uint32_t *)reg);
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
