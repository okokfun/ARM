/*!
    文件:    gd32f4xx_syscfg.c
    简介:   SYSCFG driver

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

#include "gd32f4xx_syscfg.h"

/*!
    简介:    reset the SYSCFG registers
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void SYSCFG_DeInit(void) {
    RCU_Periph_Reset_Enable(RCU_SYSCFGRST);
    RCU_Periph_Reset_Disable(RCU_SYSCFGRST);
}

/*!
    简介:    configure the boot mode
    参数[输入]:  SYSCFG_bootmode: selects the memory remapping
                only one parameter can be selected which is shown as below:
      参数:        SYSCFG_BootMode_FLASH: main flash memory (0x08000000~0x083BFFFF) is mapped at address 0x00000000
      参数:        SYSCFG_BootMode_BOOTLOADER: boot loader (0x1FFF0000 - 0x1FFF77FF) is mapped at address 0x00000000
      参数:        SYSCFG_BootMode_EXMC_SRAM: SRAM/NOR 0 and 1 of EXMC (0x60000000~0x67FFFFFF) is mapped at address 0x00000000
      参数:        SYSCFG_BootMode_SRAM: SRAM0 of on-chip SRAM (0x20000000~0x2001BFFF) is mapped at address 0x00000000
      参数:        SYSCFG_BootMode_EXMC_SDRAM: SDRAM bank0 of EXMC (0xC0000000~0xC7FFFFFF) is mapped at address 0x00000000
    参数[输出]:  无
    返回值:      无
*/
void SYSCFG_BootMode_Config(uint8_t SYSCFG_bootmode) {
    /* reset the SYSCFG_CFG0_BOOT_MODE bit and set 根据 SYSCFG_bootmode */
    SYSCFG_CFG0 &= ~SYSCFG_CFG0_BOOT_MODE;
    SYSCFG_CFG0 |= (uint32_t)SYSCFG_bootmode;
}

/*!
    简介:    FMC memory mapping swap
    参数[输入]:  SYSCFG_FMC_swap: selects the interal flash bank swapping
                only one parameter can be selected which is shown as below:
      参数:        SYSCFG_FMC_SWP_BANK0: bank 0 is mapped at address 0x08000000 and bank 1 is mapped at address 0x08100000
      参数:        SYSCFG_FMC_SWP_BANK1: bank 1 is mapped at address 0x08000000 and bank 0 is mapped at address 0x08100000
    参数[输出]:  无
    返回值:      无
*/
void SYSCFG_FMC_Swap_Config(uint32_t SYSCFG_FMC_swap) {
    uint32_t reg;
    reg = SYSCFG_CFG0;
    /* reset the FMC_SWP bit and set 根据 SYSCFG_FMC_swap */
    reg &= ~SYSCFG_CFG0_FMC_SWP;
    SYSCFG_CFG0 = (reg | SYSCFG_FMC_swap);
}

/*!
    简介:    EXMC memory mapping swap
    参数[输入]:  SYSCFG_EXMC_swap: selects the memories in EXMC swapping
                only one parameter can be selected which is shown as below:
      参数:        SYSCFG_EXMC_SWP_ENABLE: SDRAM bank 0 and bank 1 are swapped with NAND bank 1 and PC card
      参数:        SYSCFG_EXMC_SWP_DISABLE: no memory mapping swap
    参数[输出]:  无
    返回值:      无
*/
void SYSCFG_EXMC_Swap_Config(uint32_t SYSCFG_EXMC_swap) {
    uint32_t reg;

    reg = SYSCFG_CFG0;
    /* reset the SYSCFG_CFG0_EXMC_SWP bits and set 根据 SYSCFG_EXMC_swap */
    reg &= ~SYSCFG_CFG0_EXMC_SWP;
    SYSCFG_CFG0 = (reg | SYSCFG_EXMC_swap);
}

/*!
    简介:    configure the GPIO pin as EXTI Line
    参数[输入]:  EXTI_port: specify the GPIO port used in EXTI
                only one parameter can be selected which is shown as below:
      参数:        EXTI_Source_GPIOx(x = A,B,C,D,E,F,G,H,I): EXTI GPIO port
    参数[输入]:  EXTI_pin: specify the EXTI line
                only one parameter can be selected which is shown as below:
      参数:        EXTI_Source_PINx(x = 0..15): EXTI GPIO pin
    参数[输出]:  无
    返回值:      无
*/
void SYSCFG_EXTI_Line_Config(uint8_t EXTI_port, uint8_t EXTI_pin) {
    uint32_t clear_EXTI_mask = ~((uint32_t)EXTI_SS_MASK << (EXTI_SS_MSTEP(EXTI_pin)));
    uint32_t config_EXTI_mask = ((uint32_t)EXTI_port) << (EXTI_SS_MSTEP(EXTI_pin));

    switch(EXTI_pin / EXTI_SS_JSTEP) {
    case EXTISS0:
        /* clear EXTI source line(0..3) */
        SYSCFG_EXTISS0 &= clear_EXTI_mask;
        /* configure EXTI soure line(0..3) */
        SYSCFG_EXTISS0 |= config_EXTI_mask;
        break;

    case EXTISS1:
        /* clear EXTI soure line(4..7) */
        SYSCFG_EXTISS1 &= clear_EXTI_mask;
        /* configure EXTI soure line(4..7) */
        SYSCFG_EXTISS1 |= config_EXTI_mask;
        break;

    case EXTISS2:
        /* clear EXTI soure line(8..11) */
        SYSCFG_EXTISS2 &= clear_EXTI_mask;
        /* configure EXTI soure line(8..11) */
        SYSCFG_EXTISS2 |= config_EXTI_mask;
        break;

    case EXTISS3:
        /* clear EXTI soure line(12..15) */
        SYSCFG_EXTISS3 &= clear_EXTI_mask;
        /* configure EXTI soure line(12..15) */
        SYSCFG_EXTISS3 |= config_EXTI_mask;
        break;

    default:
        break;
    }
}

/*!
    简介:    configure the PHY interface for the ethernet MAC
    参数[输入]:  SYSCFG_ENET_PHY_interface: 指定media interface mode.
                only one parameter can be selected which is shown as below:
      参数:        SYSCFG_ENET_PHY_MII: MII mode is selected
      参数:        SYSCFG_ENET_PHY_RMII: RMII mode is selected
    参数[输出]:  无
    返回值:      无
*/
void SYSCFG_ENET_PHY_Interface_Config(uint32_t SYSCFG_ENET_PHY_interface) {
    uint32_t reg;

    reg = SYSCFG_CFG1;
    /* reset the ENET_PHY_SEL bit and set 根据 SYSCFG_ENET_PHY_interface */
    reg &= ~SYSCFG_CFG1_ENET_PHY_SEL;
    SYSCFG_CFG1 = (reg | SYSCFG_ENET_PHY_interface);
}

/*!
    简介:    configure the I/O compensation cell
    参数[输入]:  SYSCFG_compensation: 指定I/O compensation cell mode
                only one parameter can be selected which is shown as below:
      参数:        SYSCFG_Compensation_ENABLE: I/O compensation cell is enabled
      参数:        SYSCFG_Compensation_DISABLE: I/O compensation cell is disabled
    参数[输出]:  无
    返回值:      无
*/
void SYSCFG_Compensation_Config(uint32_t SYSCFG_compensation) {
    uint32_t reg;

    reg = SYSCFG_CPSCTL;
    /* reset the SYSCFG_CPSCTL_CPS_EN bit and set 根据 SYSCFG_compensation */
    reg &= ~SYSCFG_CPSCTL_CPS_EN;
    SYSCFG_CPSCTL = (reg | SYSCFG_compensation);
}

/*!
    简介:    checks whether the I/O compensation cell ready flag is set or not
    参数[输入]:  无
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
  */
FlagStatus SYSCFG_Flag_Get(void) {
    if(((uint32_t)RESET) != (SYSCFG_CPSCTL & SYSCFG_CPSCTL_CPS_RDY)) {
        return SET;
    } else {
        return RESET;
    }
}
