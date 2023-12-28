/*!
    文件:    gd32f4xx_pmu.c
    简介:   PMU driver

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

#include "gd32f4xx_pmu.h"
#include "core_cm4.h"

/*!
    简介:      reset PMU registers
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_DeInit(void) {
    /* reset PMU */
    RCU_Periph_Reset_Enable(RCU_PMURST);
    RCU_Periph_Reset_Disable(RCU_PMURST);
}

/*!
    简介:      select low voltage detector threshold
    参数[输入]:  lvdt_n:
      参数:        PMU_LVDT_0: voltage threshold is 2.1V
      参数:        PMU_LVDT_1: voltage threshold is 2.3V
      参数:        PMU_LVDT_2: voltage threshold is 2.4V
      参数:        PMU_LVDT_3: voltage threshold is 2.6V
      参数:        PMU_LVDT_4: voltage threshold is 2.7V
      参数:        PMU_LVDT_5: voltage threshold is 2.9V
      参数:        PMU_LVDT_6: voltage threshold is 3.0V
      参数:        PMU_LVDT_7: voltage threshold is 3.1V
    参数[输出]:  无
    返回值:      无
*/
void PMU_lvd_Select(uint32_t lvdt_n) {
    /* disable LVD */
    PMU_CTL &= ~PMU_CTL_LVDEN;
    /* clear LVDT bits */
    PMU_CTL &= ~PMU_CTL_LVDT;
    /* set LVDT bits 根据 PMU_lvdt_n */
    PMU_CTL |= lvdt_n;
    /* enable LVD */
    PMU_CTL |= PMU_CTL_LVDEN;
}

/*!
    简介:      disable PMU lvd
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_lvd_Disable(void) {
    /* disable LVD */
    PMU_CTL &= ~PMU_CTL_LVDEN;
}

/*!
    简介:      select LDO output voltage
                this bit set by software when the main PLL closed, before closing PLL, change the system clock to IRC16M or HXTAL
    参数[输入]:  ldo_output:
      参数:        PMU_LDOVS_LOW: low-driver mode enable in deep-sleep mode
      参数:        PMU_LDOVS_MID: mid-driver mode disable in deep-sleep mode
      参数:        PMU_LDOVS_HIGH: high-driver mode disable in deep-sleep mode
    参数[输出]:  无
    返回值:      无
*/
void PMU_ldo_OutPut_Select(uint32_t ldo_output) {
    PMU_CTL &= ~PMU_CTL_LDOVS;
    PMU_CTL |= ldo_output;
}

/*!
    简介:      enable high-driver mode
                this bit set by software only when IRC16M or HXTAL used as system clock
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_highdriver_Mode_Enable(void) {
    PMU_CTL |= PMU_CTL_HDEN;
}

/*!
    简介:      disable high-driver mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_highdriver_Mode_Disable(void) {
    PMU_CTL &= ~PMU_CTL_HDEN;
}

/*!
    简介:      switch high-driver mode
                this bit set by software only when IRC16M or HXTAL used as system clock
    参数[输入]:  highdr_switch:
      参数:        PMU_HIGHDR_Switch_NONE: disable high-driver mode switch
      参数:        PMU_HIGHDR_Switch_EN: enable high-driver mode switch
    参数[输出]:  无
    返回值:      无
*/
void PMU_highdriver_Switch_Select(uint32_t highdr_switch) {
    /* wait for HDRF flag set */
    while(SET != PMU_Flag_Get(PMU_Flag_HDRF)) {
    }

    PMU_CTL &= ~PMU_CTL_HDS;
    PMU_CTL |= highdr_switch;
}

/*!
    简介:      enable low-driver mode in deep-sleep
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_lowdriver_Mode_Enable(void) {
    PMU_CTL |= PMU_CTL_LDEN;
}

/*!
    简介:      disable low-driver mode in deep-sleep
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_lowdriver_Mode_Disable(void) {
    PMU_CTL &= ~PMU_CTL_LDEN;
}

/*!
    简介:      in deep-sleep mode, driver mode when use low power LDO
    参数[输入]:  mode:
      参数:        PMU_NORMALDR_LOWPWR:  normal driver when use low power LDO
      参数:        PMU_LOWDR_LOWPWR:  low-driver mode enabled when LDEN is 11 and use low power LDO
    参数[输出]:  无
    返回值:      无
*/
void PMU_Lowpower_driver_Config(uint32_t mode) {
    PMU_CTL &= ~PMU_CTL_LDLP;
    PMU_CTL |= mode;
}

/*!
    简介:      in deep-sleep mode, driver mode when use normal power LDO
    参数[输入]:  mode:
      参数:        PMU_NORMALDR_NORMALPWR: normal driver when use normal power LDO
      参数:        PMU_LOWDR_NORMALPWR: low-driver mode enabled when LDEN is 11 and use normal power LDO
    参数[输出]:  无
    返回值:      无
*/
void PMU_normalpower_driver_Config(uint32_t mode) {
    PMU_CTL &= ~PMU_CTL_LDNP;
    PMU_CTL |= mode;
}

/*!
    简介:      PMU work in sleep mode
    参数[输入]:  sleepmodecmd:
      参数:        WFI_CMD: use WFI command
      参数:        WFE_CMD: use WFE command
    参数[输出]:  无
    返回值:      无
*/
void PMU_to_sleepmode(uint8_t sleepmodecmd) {
    /* clear sleepdeep bit of Cortex-M4 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    /* select WFI or WFE command to enter sleep mode */
    if(WFI_CMD == sleepmodecmd) {
        __WFI();
    } else {
        __WFE();
    }
}

/*!
    简介:      PMU work in deep-sleep mode
    参数[输入]:  ldo
      参数:        PMU_LDO_NORMAL: LDO normal work when pmu enter deep-sleep mode
      参数:        PMU_LDO_LOWPOWER: LDO work at low power mode when pmu enter deep-sleep mode
    参数[输入]:  lowdrive:
                only one parameter can be selected which is shown as below:
      参数:        PMU_LOWDRIVER_DISABLE: Low-driver mode disable in deep-sleep mode
      参数:        PMU_LOWDRIVER_ENABLE: Low-driver mode enable in deep-sleep mode
    参数[输入]:  deepsleepmodecmd:
      参数:        WFI_CMD: use WFI command
      参数:        WFE_CMD: use WFE command
    参数[输出]:  无
    返回值:      无
*/
void PMU_to_deepsleepmode(uint32_t ldo, uint32_t lowdrive, uint8_t deepsleepmodecmd) {
    static uint32_t reg_snap[4];
    /* clear stbmod and ldolp bits */
    PMU_CTL &= ~((uint32_t)(PMU_CTL_STBMOD | PMU_CTL_LDOLP | PMU_CTL_LDEN | PMU_CTL_LDNP | PMU_CTL_LDLP));

    /* set ldolp bit 根据 PMU_ldo */
    PMU_CTL |= ldo;

    /* configure low drive mode in deep-sleep mode */
    if(PMU_LOWDRIVER_ENABLE == lowdrive) {
        if(PMU_LDO_NORMAL == ldo) {
            PMU_CTL |= (uint32_t)(PMU_CTL_LDEN | PMU_CTL_LDNP);
        } else {
            PMU_CTL |= (uint32_t)(PMU_CTL_LDEN | PMU_CTL_LDLP);
        }
    }

    /* set sleepdeep bit of Cortex-M4 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    reg_snap[0] = REG32(0xE000E010U);
    reg_snap[1] = REG32(0xE000E100U);
    reg_snap[2] = REG32(0xE000E104U);
    reg_snap[3] = REG32(0xE000E108U);

    REG32(0xE000E010U) &= 0x00010004U;
    REG32(0xE000E180U)  = 0XFF7FF831U;
    REG32(0xE000E184U)  = 0XBFFFF8FFU;
    REG32(0xE000E188U)  = 0xFFFFEFFFU;

    /* select WFI or WFE command to enter deep-sleep mode */
    if(WFI_CMD == deepsleepmodecmd) {
        __WFI();
    } else {
        __SEV();
        __WFE();
        __WFE();
    }

    REG32(0xE000E010U) = reg_snap[0];
    REG32(0xE000E100U) = reg_snap[1];
    REG32(0xE000E104U) = reg_snap[2];
    REG32(0xE000E108U) = reg_snap[3];

    /* reset sleepdeep bit of Cortex-M4 system control register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/*!
    简介:      pmu work in standby mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_to_standbymode(void) {
    /* set stbmod bit */
    PMU_CTL |= PMU_CTL_STBMOD;

    /* reset wakeup flag */
    PMU_CTL |= PMU_CTL_WURST;

    /* set sleepdeep bit of Cortex-M4 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    REG32(0xE000E010U) &= 0x00010004U;
    REG32(0xE000E180U)  = 0XFFFFFFF7U;
    REG32(0xE000E184U)  = 0XFFFFFDFFU;
    REG32(0xE000E188U)  = 0xFFFFFFFFU;

    /* select WFI command to enter standby mode */
    __WFI();
}

/*!
    简介:      enable PMU wakeup pin
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_WakeUp_Pin_Enable(void) {
    PMU_CS |= PMU_CS_WUPEN;
}

/*!
    简介:      disable PMU wakeup pin
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_WakeUp_Pin_Disable(void) {
    PMU_CS &= ~PMU_CS_WUPEN;
}

/*!
    简介:      backup SRAM LDO on
    参数[输入]:  bkp_ldo:
      参数:        PMU_BLDOON_OFF: backup SRAM LDO closed
      参数:        PMU_BLDOON_ON: open the backup SRAM LDO
    参数[输出]:  无
    返回值:      无
*/
void PMU_backup_ldo_Config(uint32_t bkp_ldo) {
    PMU_CS &= ~PMU_CS_BLDOON;
    PMU_CS |= bkp_ldo;
}

/*!
    简介:      enable write access to the registers in backup domain
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_backup_Write_Enable(void) {
    PMU_CTL |= PMU_CTL_BKPWEN;
}

/*!
    简介:      disable write access to the registers in backup domain
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void PMU_backup_Write_Disable(void) {
    PMU_CTL &= ~PMU_CTL_BKPWEN;
}

/*!
    简介:      get flag state
    参数[输入]:  flag:
      参数:        PMU_Flag_WAKEUP: wakeup flag
      参数:        PMU_Flag_STANDBY: standby flag
      参数:        PMU_Flag_LVD: lvd flag
      参数:        PMU_Flag_BLDORF: backup SRAM LDO ready flag
      参数:        PMU_Flag_LDOVSRF: LDO voltage select ready flag
      参数:        PMU_Flag_HDRF: high-driver ready flag
      参数:        PMU_Flag_HDSRF: high-driver switch ready flag
      参数:        PMU_Flag_LDRF: low-driver mode ready flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus PMU_Flag_Get(uint32_t flag) {
    if(PMU_CS & flag) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    简介:      clear flag bit
    参数[输入]:  flag:
      参数:        PMU_Flag_RESET_WAKEUP: reset wakeup flag
      参数:        PMU_Flag_RESET_STANDBY: reset standby flag
    参数[输出]:  无
    返回值:      无
*/
void PMU_Flag_Clear(uint32_t flag) {
    switch(flag) {
    case PMU_Flag_RESET_WAKEUP:
        /* reset wakeup flag */
        PMU_CTL |= PMU_CTL_WURST;
        break;

    case PMU_Flag_RESET_STANDBY:
        /* reset standby flag */
        PMU_CTL |= PMU_CTL_STBRST;
        break;

    default :
        break;
    }
}
