/*!
    文件:    gd32f4xx_rcu.c
    简介:   RCU driver

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

#include "gd32f4xx_rcu.h"

/* define clock source */
#define SEL_IRC16M                  ((uint16_t)0U)                            /* IRC16M is selected as CK_SYS */
#define SEL_HXTAL                   ((uint16_t)1U)                            /* HXTAL is selected as CK_SYS */
#define SEL_PLLP                    ((uint16_t)2U)                            /* PLLP is selected as CK_SYS */
/* define startup timeout count */
#define OSC_STARTUP_TIMEOUT         ((uint32_t)0x000fffffU)
#define LXTAL_STARTUP_TIMEOUT       ((uint32_t)0x0fffffffU)

/* RCU IRC16M adjust value mask and offset*/
#define RCU_IRC16M_ADJUST_MASK      ((uint8_t)0x1FU)
#define RCU_IRC16M_ADJUST_OFFSET    ((uint32_t)3U)

/*!
    简介:    deinitialize the RCU
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void RCU_DeInit(void) {
    /* enable IRC16M */
    RCU_CTL |= RCU_CTL_IRC16MEN;
    RCU_osci_stab_Wait(RCU_IRC16M);
    RCU_CFG0 &= ~RCU_CFG0_SCS;

    /* reset CTL register */
    RCU_CTL &= ~(RCU_CTL_HXTALEN | RCU_CTL_CKMEN | RCU_CTL_PLLEN | RCU_CTL_PLLI2SEN
                 | RCU_CTL_PLLSAIEN);
    RCU_CTL &= ~(RCU_CTL_HXTALBPS);
    /* reset CFG0 register */
    RCU_CFG0 &= ~(RCU_CFG0_SCS | RCU_CFG0_AHBPSC | RCU_CFG0_APB1PSC | RCU_CFG0_APB2PSC |
                  RCU_CFG0_RTCDIV | RCU_CFG0_CKOUT0SEL | RCU_CFG0_I2SSEL | RCU_CFG0_CKOUT0DIV |
                  RCU_CFG0_CKOUT1DIV | RCU_CFG0_CKOUT1SEL);
    /* reset PLL register */
    RCU_PLL = 0x24003010U;
    /* reset PLLI2S register */
    RCU_PLLI2S = 0x24003000U;
    /* reset PLLSAI register */
    RCU_PLLSAI = 0x24003010U;
    /* reset INT register */
    RCU_INT = 0x00000000U;
    /* reset CFG1 register */
    RCU_CFG1 &= ~(RCU_CFG1_PLLSAIRDIV | RCU_CFG1_TIMERSEL);
}

/*!
    简介:    enable the peripherals clock
    参数[输入]:  periph: RCU peripherals, refer to RCU_Periph_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_GPIOx (x = A, B, C, D, E, F, G, H, I): GPIO ports clock
      参数:        RCU_CRC: CRC clock
      参数:        RCU_BKPSRAM: BKPSRAM clock
      参数:        RCU_TCMSRAM: TCMSRAM clock
      参数:        RCU_DMAx (x=0,1): DMA clock
      参数:        RCU_IPA: IPA clock
      参数:        RCU_ENET: ENET clock
      参数:        RCU_ENETTX: ENETTX clock
      参数:        RCU_ENETRX: ENETRX clock
      参数:        RCU_ENETPTP: ENETPTP clock
      参数:        RCU_USBHS: USBHS clock
      参数:        RCU_USBHSULPI: USBHSULPI clock
      参数:        RCU_DCI: DCI clock
      参数:        RCU_TRNG: TRNG clock
      参数:        RCU_USBFS: USBFS clock
      参数:        RCU_EXMC: EXMC clock
      参数:        RCU_TIMERx (x = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13): TIMER clock
      参数:        RCU_WWDGT: WWDGT clock
      参数:        RCU_SPIx (x = 0, 1, 2, 3, 4, 5): SPI clock
      参数:        RCU_USARTx (x = 0, 1, 2, 5): USART clock
      参数:        RCU_UARTx (x = 3, 4, 6, 7): UART clock
      参数:        RCU_I2Cx (x = 0, 1, 2): I2C clock
      参数:        RCU_CANx (x = 0, 1): CAN clock
      参数:        RCU_PMU: PMU clock
      参数:        RCU_DAC: DAC clock
      参数:        RCU_RTC: RTC clock
      参数:        RCU_ADCx (x = 0, 1, 2): ADC clock
      参数:        RCU_SDIO: SDIO clock
      参数:        RCU_SYSCFG: SYSCFG clock
      参数:        RCU_TLI: TLI clock
      参数:        RCU_CTC: CTC clock
      参数:        RCU_IREF: IREF clock
    参数[输出]:  无
    返回值:      无
*/
void RCU_Periph_Clock_Enable(RCU_Periph_enum periph) {
    RCU_REG_VAL(periph) |= BIT(RCU_Bit_POS(periph));
}

/*!
    简介:    disable the peripherals clock
    参数[输入]:  periph: RCU peripherals, refer to RCU_Periph_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_GPIOx (x = A, B, C, D, E, F, G, H, I): GPIO ports clock
      参数:        RCU_CRC: CRC clock
      参数:        RCU_BKPSRAM: BKPSRAM clock
      参数:        RCU_TCMSRAM: TCMSRAM clock
      参数:        RCU_DMAx (x=0,1): DMA clock
      参数:        RCU_IPA: IPA clock
      参数:        RCU_ENET: ENET clock
      参数:        RCU_ENETTX: ENETTX clock
      参数:        RCU_ENETRX: ENETRX clock
      参数:        RCU_ENETPTP: ENETPTP clock
      参数:        RCU_USBHS: USBHS clock
      参数:        RCU_USBHSULPI: USBHSULPI clock
      参数:        RCU_DCI: DCI clock
      参数:        RCU_TRNG: TRNG clock
      参数:        RCU_USBFS: USBFS clock
      参数:        RCU_EXMC: EXMC clock
      参数:        RCU_TIMERx (x = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13): TIMER clock
      参数:        RCU_WWDGT: WWDGT clock
      参数:        RCU_SPIx (x = 0, 1, 2, 3, 4, 5): SPI clock
      参数:        RCU_USARTx (x = 0, 1, 2, 5): USART clock
      参数:        RCU_UARTx (x = 3, 4, 6, 7): UART clock
      参数:        RCU_I2Cx (x = 0, 1, 2): I2C clock
      参数:        RCU_CANx (x = 0, 1): CAN clock
      参数:        RCU_PMU: PMU clock
      参数:        RCU_DAC: DAC clock
      参数:        RCU_RTC: RTC clock
      参数:        RCU_ADCx (x = 0, 1, 2): ADC clock
      参数:        RCU_SDIO: SDIO clock
      参数:        RCU_SYSCFG: SYSCFG clock
      参数:        RCU_TLI: TLI clock
      参数:        RCU_CTC: CTC clock
      参数:        RCU_IREF: IREF clock
    参数[输出]:  无
    返回值:      无
*/
void RCU_Periph_Clock_Disable(RCU_Periph_enum periph) {
    RCU_REG_VAL(periph) &= ~BIT(RCU_Bit_POS(periph));
}

/*!
    简介:    enable the peripherals clock when sleep mode
    参数[输入]:  periph: RCU peripherals, refer to RCU_Periph_sleep_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_GPIOx_SLP (x = A, B, C, D, E, F, G, H, I): GPIO ports clock
      参数:        RCU_CRC_SLP: CRC clock
      参数:        RCU_FMC_SLP: FMC clock
      参数:        RCU_SRAM0_SLP: SRAM0 clock
      参数:        RCU_SRAM1_SLP: SRAM1 clock
      参数:        RCU_BKPSRAM: BKPSRAM clock
      参数:        RCU_SRAM2_SLP: SRAM2 clock
      参数:        RCU_DMAx_SLP (x=0,1): DMA clock
      参数:        RCU_IPA_SLP: IPA clock
      参数:        RCU_ENET_SLP: ENET clock
      参数:        RCU_ENETTX_SLP: ENETTX clock
      参数:        RCU_ENETRX_SLP: ENETRX clock
      参数:        RCU_ENETPTP_SLP: ENETPTP clock
      参数:        RCU_USBHS_SLP: USBHS clock
      参数:        RCU_USBHSULPI_SLP: USBHSULPI clock
      参数:        RCU_DCI_SLP: DCI clock
      参数:        RCU_TRNG_SLP: TRNG clock
      参数:        RCU_USBFS_SLP: USBFS clock
      参数:        RCU_EXMC_SLP: EXMC clock
      参数:        RCU_TIMERx_SLP (x = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13): TIMER clock
      参数:        RCU_WWDGT_SLP: WWDGT clock
      参数:        RCU_SPIx_SLP (x = 0, 1, 2, 3, 4, 5): SPI clock
      参数:        RCU_USARTx_SLP (x = 0, 1, 2, 5): USART clock
      参数:        RCU_UARTx_SLP (x = 3, 4, 6, 7): UART clock
      参数:        RCU_I2Cx_SLP (x = 0, 1, 2): I2C clock
      参数:        RCU_CANx_SLP (x = 0, 1): CAN clock
      参数:        RCU_PMU_SLP: PMU clock
      参数:        RCU_DAC_SLP: DAC clock
      参数:        RCU_RTC_SLP: RTC clock
      参数:        RCU_ADCx_SLP (x = 0, 1, 2): ADC clock
      参数:        RCU_SDIO_SLP: SDIO clock
      参数:        RCU_SYSCFG_SLP: SYSCFG clock
      参数:        RCU_TLI_SLP: TLI clock
      参数:        RCU_CTC_SLP: CTC clock
      参数:        RCU_IREF_SLP: IREF clock
    参数[输出]:  无
    返回值:      无
*/
void RCU_Periph_Clock_sleep_Enable(RCU_Periph_sleep_enum periph) {
    RCU_REG_VAL(periph) |= BIT(RCU_Bit_POS(periph));
}

/*!
    简介:    disable the peripherals clock when sleep mode
    参数[输入]:  periph: RCU peripherals, refer to RCU_Periph_sleep_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_GPIOx_SLP (x = A, B, C, D, E, F, G, H, I): GPIO ports clock
      参数:        RCU_CRC_SLP: CRC clock
      参数:        RCU_FMC_SLP: FMC clock
      参数:        RCU_SRAM0_SLP: SRAM0 clock
      参数:        RCU_SRAM1_SLP: SRAM1 clock
      参数:        RCU_BKPSRAM: BKPSRAM clock
      参数:        RCU_SRAM2_SLP: SRAM2 clock
      参数:        RCU_DMAx_SLP (x=0,1): DMA clock
      参数:        RCU_IPA_SLP: IPA clock
      参数:        RCU_ENET_SLP: ENET clock
      参数:        RCU_ENETTX_SLP: ENETTX clock
      参数:        RCU_ENETRX_SLP: ENETRX clock
      参数:        RCU_ENETPTP_SLP: ENETPTP clock
      参数:        RCU_USBHS_SLP: USBHS clock
      参数:        RCU_USBHSULPI_SLP: USBHSULPI clock
      参数:        RCU_DCI_SLP: DCI clock
      参数:        RCU_TRNG_SLP: TRNG clock
      参数:        RCU_USBFS_SLP: USBFS clock
      参数:        RCU_EXMC_SLP: EXMC clock
      参数:        RCU_TIMERx_SLP (x = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13): TIMER clock
      参数:        RCU_WWDGT_SLP: WWDGT clock
      参数:        RCU_SPIx_SLP (x = 0, 1, 2, 3, 4, 5): SPI clock
      参数:        RCU_USARTx_SLP (x = 0, 1, 2, 5): USART clock
      参数:        RCU_UARTx_SLP (x = 3, 4, 6, 7): UART clock
      参数:        RCU_I2Cx_SLP (x = 0, 1, 2): I2C clock
      参数:        RCU_CANx_SLP (x = 0, 1): CAN clock
      参数:        RCU_PMU_SLP: PMU clock
      参数:        RCU_DAC_SLP: DAC clock
      参数:        RCU_RTC_SLP: RTC clock
      参数:        RCU_ADCx_SLP (x = 0, 1, 2): ADC clock
      参数:        RCU_SDIO_SLP: SDIO clock
      参数:        RCU_SYSCFG_SLP: SYSCFG clock
      参数:        RCU_TLI_SLP: TLI clock
      参数:        RCU_CTC_SLP: CTC clock
      参数:        RCU_IREF_SLP: IREF clock
    参数[输出]:  无
    返回值:      无
*/
void RCU_Periph_Clock_sleep_Disable(RCU_Periph_sleep_enum periph) {
    RCU_REG_VAL(periph) &= ~BIT(RCU_Bit_POS(periph));
}

/*!
    简介:    reset the peripherals
    参数[输入]:  periph_reset: RCU peripherals reset, refer to RCU_Periph_reset_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_GPIOxRST (x = A, B, C, D, E, F, G, H, I): reset GPIO ports
      参数:        RCU_CRCRST: reset CRC
      参数:        RCU_DMAxRST (x=0,1): reset DMA
      参数:        RCU_IPARST: reset IPA
      参数:        RCU_ENETRST: reset ENET
      参数:        RCU_USBHSRST: reset USBHS
      参数:        RCU_DCIRST: reset DCI
      参数:        RCU_TRNGRST: reset TRNG
      参数:        RCU_USBFSRST: reset USBFS
      参数:        RCU_EXMCRST: reset EXMC
      参数:        RCU_TIMERxRST (x = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13): reset TIMER
      参数:        RCU_WWDGTRST: reset WWDGT
      参数:        RCU_SPIxRST (x = 0, 1, 2, 3, 4, 5): reset SPI
      参数:        RCU_USARTxRST (x = 0, 1, 2, 5): reset USART
      参数:        RCU_UARTxRST (x = 3, 4, 6, 7): reset UART
      参数:        RCU_I2CxRST (x = 0, 1, 2): reset I2C
      参数:        RCU_CANxRST (x = 0, 1): reset CAN
      参数:        RCU_PMURST: reset PMU
      参数:        RCU_DACRST: reset DAC
      参数:        RCU_ADCRST (x = 0, 1, 2): reset ADC
      参数:        RCU_SDIORST: reset SDIO
      参数:        RCU_SYSCFGRST: reset SYSCFG
      参数:        RCU_TLIRST: reset TLI
      参数:        RCU_CTCRST: reset CTC
      参数:        RCU_IREFRST: reset IREF
    参数[输出]:  无
    返回值:      无
*/
void RCU_Periph_Reset_Enable(RCU_Periph_reset_enum periph_reset) {
    RCU_REG_VAL(periph_reset) |= BIT(RCU_Bit_POS(periph_reset));
}

/*!
    简介:    disable reset the peripheral
    参数[输入]:  periph_reset: RCU peripherals reset, refer to RCU_Periph_reset_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_GPIOxRST (x = A, B, C, D, E, F, G, H, I): reset GPIO ports
      参数:        RCU_CRCRST: reset CRC
      参数:        RCU_DMAxRST (x=0,1): reset DMA
      参数:        RCU_IPARST: reset IPA
      参数:        RCU_ENETRST: reset ENET
      参数:        RCU_USBHSRST: reset USBHS
      参数:        RCU_DCIRST: reset DCI
      参数:        RCU_TRNGRST: reset TRNG
      参数:        RCU_USBFSRST: reset USBFS
      参数:        RCU_EXMCRST: reset EXMC
      参数:        RCU_TIMERxRST (x = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13): reset TIMER
      参数:        RCU_WWDGTRST: reset WWDGT
      参数:        RCU_SPIxRST (x = 0, 1, 2, 3, 4, 5): reset SPI
      参数:        RCU_USARTxRST (x = 0, 1, 2, 5): reset USART
      参数:        RCU_UARTxRST (x = 3, 4, 6, 7): reset UART
      参数:        RCU_I2CxRST (x = 0, 1, 2): reset I2C
      参数:        RCU_CANxRST (x = 0, 1): reset CAN
      参数:        RCU_PMURST: reset PMU
      参数:        RCU_DACRST: reset DAC
      参数:        RCU_ADCRST (x = 0, 1, 2): reset ADC
      参数:        RCU_SDIORST: reset SDIO
      参数:        RCU_SYSCFGRST: reset SYSCFG
      参数:        RCU_TLIRST: reset TLI
      参数:        RCU_CTCRST: reset CTC
      参数:        RCU_IREFRST: reset IREF
    参数[输出]:  无
    返回值:      无
*/
void RCU_Periph_Reset_Disable(RCU_Periph_reset_enum periph_reset) {
    RCU_REG_VAL(periph_reset) &= ~BIT(RCU_Bit_POS(periph_reset));
}

/*!
    简介:    reset the BKP
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void RCU_bkp_reset_Enable(void) {
    RCU_BDCTL |= RCU_BDCTL_BKPRST;
}

/*!
    简介:    disable the BKP reset
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void RCU_bkp_reset_Disable(void) {
    RCU_BDCTL &= ~RCU_BDCTL_BKPRST;
}

/*!
    简介:    configure the system clock source
    参数[输入]:  ck_sys: system clock source select
                only one parameter can be selected which is shown as below:
      参数:        RCU_CKSYSSRC_IRC16M: select CK_IRC16M as the CK_SYS source
      参数:        RCU_CKSYSSRC_HXTAL: select CK_HXTAL as the CK_SYS source
      参数:        RCU_CKSYSSRC_PLLP: select CK_PLLP as the CK_SYS source
    参数[输出]:  无
    返回值:      无
*/
void RCU_System_Clock_Source_Config(uint32_t ck_sys) {
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the SCS bits and set 根据 ck_sys */
    reg &= ~RCU_CFG0_SCS;
    RCU_CFG0 = (reg | ck_sys);
}

/*!
    简介:    get the system clock source
    参数[输入]:  无
    参数[输出]:  无
    返回值:     which clock is selected as CK_SYS source
      参数:        RCU_SCSS_IRC16M: CK_IRC16M is selected as the CK_SYS source
      参数:        RCU_SCSS_HXTAL: CK_HXTAL is selected as the CK_SYS source
      参数:        RCU_SCSS_PLLP: CK_PLLP is selected as the CK_SYS source
*/
uint32_t RCU_System_Clock_Source_Get(void) {
    return (RCU_CFG0 & RCU_CFG0_SCSS);
}

/*!
    简介:    configure the AHB clock prescaler selection
    参数[输入]:  ck_ahb: AHB clock prescaler selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_AHB_CKSYS_DIVx (x = 1, 2, 4, 8, 16, 64, 128, 256, 512): select CK_SYS / x as CK_AHB
    参数[输出]:  无
    返回值:      无
*/
void RCU_ahb_Clock_Config(uint32_t ck_ahb) {
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the AHBPSC bits and set 根据 ck_ahb */
    reg &= ~RCU_CFG0_AHBPSC;
    RCU_CFG0 = (reg | ck_ahb);
}

/*!
    简介:    configure the APB1 clock prescaler selection
    参数[输入]:  ck_apb1: APB1 clock prescaler selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_APB1_CKAHB_DIV1: select CK_AHB as CK_APB1
      参数:        RCU_APB1_CKAHB_DIV2: select CK_AHB / 2 as CK_APB1
      参数:        RCU_APB1_CKAHB_DIV4: select CK_AHB / 4 as CK_APB1
      参数:        RCU_APB1_CKAHB_DIV8: select CK_AHB / 8 as CK_APB1
      参数:        RCU_APB1_CKAHB_DIV16: select CK_AHB / 16 as CK_APB1
    参数[输出]:  无
    返回值:      无
*/
void RCU_apb1_Clock_Config(uint32_t ck_apb1) {
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the APB1PSC and set 根据 ck_apb1 */
    reg &= ~RCU_CFG0_APB1PSC;
    RCU_CFG0 = (reg | ck_apb1);
}

/*!
    简介:    configure the APB2 clock prescaler selection
    参数[输入]:  ck_apb2: APB2 clock prescaler selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_APB2_CKAHB_DIV1: select CK_AHB as CK_APB2
      参数:        RCU_APB2_CKAHB_DIV2: select CK_AHB / 2 as CK_APB2
      参数:        RCU_APB2_CKAHB_DIV4: select CK_AHB / 4 as CK_APB2
      参数:        RCU_APB2_CKAHB_DIV8: select CK_AHB / 8 as CK_APB2
      参数:        RCU_APB2_CKAHB_DIV16: select CK_AHB / 16 as CK_APB2
    参数[输出]:  无
    返回值:      无
*/
void RCU_apb2_Clock_Config(uint32_t ck_apb2) {
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the APB2PSC and set 根据 ck_apb2 */
    reg &= ~RCU_CFG0_APB2PSC;
    RCU_CFG0 = (reg | ck_apb2);
}

/*!
    简介:    configure the CK_OUT0 clock source and divider
    参数[输入]:  ckout0_src: CK_OUT0 clock source selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_CKOUT0SRC_IRC16M: IRC16M selected
      参数:        RCU_CKOUT0SRC_LXTAL: LXTAL selected
      参数:        RCU_CKOUT0SRC_HXTAL: HXTAL selected
      参数:        RCU_CKOUT0SRC_PLLP: PLLP selected
    参数[输入]:  ckout0_div: CK_OUT0 divider
      参数:        RCU_CKOUT0_DIVx(x = 1, 2, 3, 4, 5): CK_OUT0 is divided by x
    参数[输出]:  无
    返回值:      无
*/
void RCU_ckout0_Config(uint32_t ckout0_src, uint32_t ckout0_div) {
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the CKOUT0SRC, CKOUT0DIV and set 根据 ckout0_src and ckout0_div */
    reg &= ~(RCU_CFG0_CKOUT0SEL | RCU_CFG0_CKOUT0DIV);
    RCU_CFG0 = (reg | ckout0_src | ckout0_div);
}

/*!
    简介:    configure the CK_OUT1 clock source and divider
    参数[输入]:  ckout1_src: CK_OUT1 clock source selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_CKOUT1SRC_SYSTEMCLOCK: system clock selected
      参数:        RCU_CKOUT1SRC_PLLI2SR: PLLI2SR selected
      参数:        RCU_CKOUT1SRC_HXTAL: HXTAL selected
      参数:        RCU_CKOUT1SRC_PLLP: PLLP selected
    参数[输入]:  ckout1_div: CK_OUT1 divider
      参数:        RCU_CKOUT1_DIVx(x = 1, 2, 3, 4, 5): CK_OUT1 is divided by x
    参数[输出]:  无
    返回值:      无
*/
void RCU_ckout1_Config(uint32_t ckout1_src, uint32_t ckout1_div) {
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the CKOUT1SRC, CKOUT1DIV and set 根据 ckout1_src and ckout1_div */
    reg &= ~(RCU_CFG0_CKOUT1SEL | RCU_CFG0_CKOUT1DIV);
    RCU_CFG0 = (reg | ckout1_src | ckout1_div);
}

/*!
    简介:    configure the main PLL clock
    参数[输入]:  pll_src: PLL clock source selection
      参数:        RCU_PLLSRC_IRC16M: select IRC16M as PLL source clock
      参数:        RCU_PLLSRC_HXTAL: select HXTAL as PLL source clock
    参数[输入]:  pll_psc: the PLL VCO source clock prescaler
      参数:         this parameter should be selected between 2 and 63
    参数[输入]:  pll_n: the PLL VCO clock multi factor
      参数:        this parameter should be selected between 64 and 500
    参数[输入]:  pll_p: the PLLP output frequency division factor from PLL VCO clock
      参数:        this parameter should be selected 2,4,6,8
    参数[输入]:  pll_q: the PLL Q output frequency division factor from PLL VCO clock
      参数:        this parameter should be selected between 2 and 15
    参数[输出]:  无
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus RCU_pll_Config(uint32_t pll_src, uint32_t pll_psc, uint32_t pll_n, uint32_t pll_p, uint32_t pll_q) {
    uint32_t ss_modulation_inc;
    uint32_t ss_modulation_reg;

    ss_modulation_inc = 0U;
    ss_modulation_reg = RCU_PLLSSCTL;

    /* calculate the minimum factor of PLLN */
    if((ss_modulation_reg & RCU_PLLSSCTL_SSCGON) == RCU_PLLSSCTL_SSCGON) {
        if((ss_modulation_reg & RCU_SS_TYPE_DOWN) == RCU_SS_TYPE_DOWN) {
            ss_modulation_inc += RCU_SS_MODULATION_Down_INC;
        } else {
            ss_modulation_inc += RCU_SS_MODULATION_CENTER_INC;
        }
    }

    /* check the function parameter */
    if(CHECK_PLL_PSC_VALID(pll_psc) && CHECK_PLL_N_VALID(pll_n, ss_modulation_inc) &&
            CHECK_PLL_P_VALID(pll_p) && CHECK_PLL_Q_VALID(pll_q)) {
        RCU_PLL = pll_psc | (pll_n << 6) | (((pll_p >> 1) - 1U) << 16) |
                  (pll_src) | (pll_q << 24);
    } else {
        /* return status */
        return ERROR;
    }

    /* return status */
    return SUCCESS;
}

/*!
    简介:    configure the PLLI2S clock
    参数[输入]:  pllI2S_n: the PLLI2S VCO clock multi factor
      参数:        this parameter should be selected between 50 and 500
    参数[输入]:  pllI2S_r: the PLLI2S R output frequency division factor from PLLI2S VCO clock
      参数:        this parameter should be selected between 2 and 7
    参数[输出]:  无
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus RCU_pllI2S_Config(uint32_t pllI2S_n, uint32_t pllI2S_r) {
    /* check the function parameter */
    if(CHECK_PLLI2S_N_VALID(pllI2S_n) && CHECK_PLLI2S_R_VALID(pllI2S_r)) {
        RCU_PLLI2S = (pllI2S_n << 6) | (pllI2S_r << 28);
    } else {
        /* return status */
        return ERROR;
    }

    /* return status */
    return SUCCESS;
}

/*!
    简介:    configure the PLLSAI clock
    参数[输入]:  pllsai_n: the PLLSAI VCO clock multi factor
      参数:        this parameter should be selected between 50 and 500
    参数[输入]:  pllsai_p: the PLLSAI P output frequency division factor from PLL VCO clock
      参数:        this parameter should be selected 2,4,6,8
    参数[输入]:  pllsai_r: the PLLSAI R output frequency division factor from PLL VCO clock
      参数:        this parameter should be selected between 2 and 7
    参数[输出]:  无
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus RCU_pllsai_Config(uint32_t pllsai_n, uint32_t pllsai_p, uint32_t pllsai_r) {
    /* check the function parameter */
    if(CHECK_PLLSAI_N_VALID(pllsai_n) && CHECK_PLLSAI_P_VALID(pllsai_p) && CHECK_PLLSAI_R_VALID(pllsai_r)) {
        RCU_PLLSAI = (pllsai_n << 6U) | (((pllsai_p >> 1U) - 1U) << 16U) | (pllsai_r << 28U);
    } else {
        /* return status */
        return ERROR;
    }

    /* return status */
    return SUCCESS;
}

/*!
    简介:    configure the RTC clock source selection
    参数[输入]:  RTC_Clock_source: RTC clock source selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_RTCSRC_NONE: no clock selected
      参数:        RCU_RTCSRC_LXTAL: CK_LXTAL selected as RTC source clock
      参数:        RCU_RTCSRC_IRC32K: CK_IRC32K selected as RTC source clock
      参数:        RCU_RTCSRC_HXTAL_DIV_RTCDIV: CK_HXTAL / RTCDIV selected as RTC source clock
    参数[输出]:  无
    返回值:      无
*/
void RCU_RTC_Clock_Config(uint32_t RTC_Clock_source) {
    uint32_t reg;

    reg = RCU_BDCTL;
    /* reset the RTCSRC bits and set 根据 RTC_Clock_source */
    reg &= ~RCU_BDCTL_RTCSRC;
    RCU_BDCTL = (reg | RTC_Clock_source);
}

/*!
    简介:    configure the frequency division of RTC clock when HXTAL was selected as its clock source
    参数[输入]:  RTC_div: RTC clock frequency division
                only one parameter can be selected which is shown as below:
      参数:        RCU_RTC_HXTAL_NONE: no clock for RTC
      参数:        RCU_RTC_HXTAL_DIVx: RTCDIV clock select CK_HXTAL / x, x = 2....31
    参数[输出]:  无
    返回值:      无
*/
void RCU_RTC_div_Config(uint32_t RTC_div) {
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the RTCDIV bits and set 根据 RTC_div value */
    reg &= ~RCU_CFG0_RTCDIV;
    RCU_CFG0 = (reg | RTC_div);
}


/*!
    简介:    configure the I2S clock source selection
    参数[输入]:  I2S_Clock_source: I2S clock source selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_I2SSRC_PLLI2S: CK_PLLI2S selected as I2S source clock
      参数:        RCU_I2SSRC_I2S_CKIN: external I2S_ckin pin selected as I2S source clock
    参数[输出]:  无
    返回值:      无
*/
void RCU_I2S_Clock_Config(uint32_t I2S_Clock_source) {
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the I2SSEL bit and set 根据 I2S_Clock_source */
    reg &= ~RCU_CFG0_I2SSEL;
    RCU_CFG0 = (reg | I2S_Clock_source);
}

/*!
    简介:    configure the CK48M clock source selection
    参数[输入]:  ck48m_Clock_source: CK48M clock source selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_CK48MSRC_PLL48M: CK_PLL48M selected as CK48M source clock
      参数:        RCU_CK48MSRC_IRC48M: CK_IRC48M selected as CK48M source clock
    参数[输出]:  无
    返回值:      无
*/
void RCU_ck48m_Clock_Config(uint32_t ck48m_Clock_source) {
    uint32_t reg;

    reg = RCU_ADDCTL;
    /* reset the CK48MSEL bit and set 根据 I2S_Clock_source */
    reg &= ~RCU_ADDCTL_CK48MSEL;
    RCU_ADDCTL = (reg | ck48m_Clock_source);
}

/*!
    简介:    configure the PLL48M clock source selection
    参数[输入]:  pll48m_Clock_source: PLL48M clock source selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_PLL48MSRC_PLLQ: CK_PLLQ selected as PLL48M source clock
      参数:        RCU_PLL48MSRC_PLLSAIP: CK_PLLSAIP selected as PLL48M source clock
    参数[输出]:  无
    返回值:      无
*/
void RCU_pll48m_Clock_Config(uint32_t pll48m_Clock_source) {
    uint32_t reg;

    reg = RCU_ADDCTL;
    /* reset the PLL48MSEL bit and set 根据 pll48m_Clock_source */
    reg &= ~RCU_ADDCTL_PLL48MSEL;
    RCU_ADDCTL = (reg | pll48m_Clock_source);
}

/*!
    简介:    configure the TIMER clock prescaler selection
    参数[输入]:  TIMER_Clock_prescaler: TIMER clock selection
                only one parameter can be selected which is shown as below:
      参数:        RCU_TIMER_PSC_MUL2: if APB1PSC/APB2PSC in RCU_CFG0 register is 0b0xx(CK_APBx = CK_AHB)
                                      or 0b100(CK_APBx = CK_AHB/2), the TIMER clock is equal to CK_AHB(CK_TIMERx = CK_AHB).
                                      or else, the TIMER clock is twice the corresponding APB clock (TIMER in APB1 domain: CK_TIMERx = 2 x CK_APB1;
                                      TIMER in APB2 domain: CK_TIMERx = 2 x CK_APB2)
      参数:        RCU_TIMER_PSC_MUL4: if APB1PSC/APB2PSC in RCU_CFG0 register is 0b0xx(CK_APBx = CK_AHB),
                                      0b100(CK_APBx = CK_AHB/2), or 0b101(CK_APBx = CK_AHB/4), the TIMER clock is equal to CK_AHB(CK_TIMERx = CK_AHB).
                                      or else, the TIMER clock is four timers the corresponding APB clock (TIMER in APB1 domain: CK_TIMERx = 4 x CK_APB1;
                                      TIMER in APB2 domain: CK_TIMERx = 4 x CK_APB2)
    参数[输出]:  无
    返回值:      无
*/
void RCU_TIMER_Clock_Prescaler_Config(uint32_t TIMER_Clock_prescaler) {
    /* configure the TIMERSEL bit and select the TIMER clock prescaler */
    if(TIMER_Clock_prescaler == RCU_TIMER_PSC_MUL2) {
        RCU_CFG1 &= TIMER_Clock_prescaler;
    } else {
        RCU_CFG1 |= TIMER_Clock_prescaler;
    }
}

/*!
    简介:    configure the PLLSAIR divider used as input of TLI
    参数[输入]:  pllsai_r_div: PLLSAIR divider used as input of TLI
                only one parameter can be selected which is shown as below:
      参数:        RCU_PLLSAIR_DIVx(x=2,4,8,16): PLLSAIR divided x used as input of TLI
    参数[输出]:  无
    返回值:      无
*/
void RCU_tli_Clock_div_Config(uint32_t pllsai_r_div) {
    uint32_t reg;

    reg = RCU_CFG1;
    /* reset the PLLSAIRDIV bit and set 根据 pllsai_r_div */
    reg &= ~RCU_CFG1_PLLSAIRDIV;
    RCU_CFG1 = (reg | pllsai_r_div);
}

/*!
    简介:    configure the LXTAL drive capability
    参数[输入]:  lxtal_dricap: drive capability of LXTAL
                only one parameter can be selected which is shown as below:
      参数:        RCU_LXTALDRI_LOWER_DRIVE: lower driving capability
      参数:        RCU_LXTALDRI_HIGHER_DRIVE: higher driving capability
    参数[输出]:  无
    返回值:      无
*/
void RCU_lxtal_drive_capability_Config(uint32_t lxtal_dricap) {
    uint32_t reg;

    reg = RCU_BDCTL;

    /* reset the LXTALDRI bits and set 根据 lxtal_dricap */
    reg &= ~RCU_BDCTL_LXTALDRI;
    RCU_BDCTL = (reg | lxtal_dricap);
}

/*!
    简介:    wait for oscillator stabilization flags is SET or oscillator startup is timeout
    参数[输入]:  osci: oscillator types, refer to RCU_osci_type_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_HXTAL: HXTAL
      参数:        RCU_LXTAL: LXTAL
      参数:        RCU_IRC16M: IRC16M
      参数:        RCU_IRC48M: IRC48M
      参数:        RCU_IRC32K: IRC32K
      参数:        RCU_PLL_CK: PLL
      参数:        RCU_PLLI2S_CK: PLLI2S
      参数:        RCU_PLLSAI_CK: PLLSAI
    参数[输出]:  无
    返回值:     ErrStatus: SUCCESS or ERROR
*/
ErrStatus RCU_osci_stab_Wait(RCU_osci_type_enum osci) {
    uint32_t stb_cnt = 0U;
    ErrStatus reval = ERROR;
    FlagStatus osci_stat = RESET;

    switch(osci) {
    /* wait HXTAL stable */
    case RCU_HXTAL:
        while((RESET == osci_stat) && (HXTAL_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = RCU_Flag_Get(RCU_Flag_HXTALSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != RCU_Flag_Get(RCU_Flag_HXTALSTB)) {
            reval = SUCCESS;
        }

        break;

    /* wait LXTAL stable */
    case RCU_LXTAL:
        while((RESET == osci_stat) && (LXTAL_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = RCU_Flag_Get(RCU_Flag_LXTALSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != RCU_Flag_Get(RCU_Flag_LXTALSTB)) {
            reval = SUCCESS;
        }

        break;

    /* wait IRC16M stable */
    case RCU_IRC16M:
        while((RESET == osci_stat) && (IRC16M_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = RCU_Flag_Get(RCU_Flag_IRC16MSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != RCU_Flag_Get(RCU_Flag_IRC16MSTB)) {
            reval = SUCCESS;
        }

        break;

    /* wait IRC48M stable */
    case RCU_IRC48M:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = RCU_Flag_Get(RCU_Flag_IRC48MSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != RCU_Flag_Get(RCU_Flag_IRC48MSTB)) {
            reval = SUCCESS;
        }

        break;

    /* wait IRC32K stable */
    case RCU_IRC32K:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = RCU_Flag_Get(RCU_Flag_IRC32KSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != RCU_Flag_Get(RCU_Flag_IRC32KSTB)) {
            reval = SUCCESS;
        }

        break;

    /* wait PLL stable */
    case RCU_PLL_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = RCU_Flag_Get(RCU_Flag_PLLSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != RCU_Flag_Get(RCU_Flag_PLLSTB)) {
            reval = SUCCESS;
        }

        break;

    /* wait PLLI2S stable */
    case RCU_PLLI2S_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = RCU_Flag_Get(RCU_Flag_PLLI2SSTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != RCU_Flag_Get(RCU_Flag_PLLI2SSTB)) {
            reval = SUCCESS;
        }

        break;

    /* wait PLLSAI stable */
    case RCU_PLLSAI_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = RCU_Flag_Get(RCU_Flag_PLLSAISTB);
            stb_cnt++;
        }

        /* check whether flag is set */
        if(RESET != RCU_Flag_Get(RCU_Flag_PLLSAISTB)) {
            reval = SUCCESS;
        }

        break;

    default:
        break;
    }

    /* return value */
    return reval;
}

/*!
    简介:    turn on the oscillator
    参数[输入]:  osci: oscillator types, refer to RCU_osci_type_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_HXTAL: HXTAL
      参数:        RCU_LXTAL: LXTAL
      参数:        RCU_IRC16M: IRC16M
      参数:        RCU_IRC48M: IRC48M
      参数:        RCU_IRC32K: IRC32K
      参数:        RCU_PLL_CK: PLL
      参数:        RCU_PLLI2S_CK: PLLI2S
      参数:        RCU_PLLSAI_CK: PLLSAI
    参数[输出]:  无
    返回值:      无
*/
void RCU_osci_on(RCU_osci_type_enum osci) {
    RCU_REG_VAL(osci) |= BIT(RCU_Bit_POS(osci));
}

/*!
    简介:    turn off the oscillator
    参数[输入]:  osci: oscillator types, refer to RCU_osci_type_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_HXTAL: HXTAL
      参数:        RCU_LXTAL: LXTAL
      参数:        RCU_IRC16M: IRC16M
      参数:        RCU_IRC48M: IRC48M
      参数:        RCU_IRC32K: IRC32K
      参数:        RCU_PLL_CK: PLL
      参数:        RCU_PLLI2S_CK: PLLI2S
      参数:        RCU_PLLSAI_CK: PLLSAI
    参数[输出]:  无
    返回值:      无
*/
void RCU_osci_off(RCU_osci_type_enum osci) {
    RCU_REG_VAL(osci) &= ~BIT(RCU_Bit_POS(osci));
}

/*!
    简介:    enable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it
    参数[输入]:  osci: oscillator types, refer to RCU_osci_type_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      参数:        RCU_LXTAL: low speed crystal oscillator(LXTAL)
    参数[输出]:  无
    返回值:      无
*/
void RCU_osci_bypass_Mode_Enable(RCU_osci_type_enum osci) {
    uint32_t reg;

    switch(osci) {
    /* enable HXTAL to bypass mode */
    case RCU_HXTAL:
        reg = RCU_CTL;
        RCU_CTL &= ~RCU_CTL_HXTALEN;
        RCU_CTL = (reg | RCU_CTL_HXTALBPS);
        break;

    /* enable LXTAL to bypass mode */
    case RCU_LXTAL:
        reg = RCU_BDCTL;
        RCU_BDCTL &= ~RCU_BDCTL_LXTALEN;
        RCU_BDCTL = (reg | RCU_BDCTL_LXTALBPS);
        break;

    case RCU_IRC16M:
    case RCU_IRC48M:
    case RCU_IRC32K:
    case RCU_PLL_CK:
    case RCU_PLLI2S_CK:
    case RCU_PLLSAI_CK:
        break;

    default:
        break;
    }
}

/*!
    简介:    disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it
    参数[输入]:  osci: oscillator types, refer to RCU_osci_type_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      参数:        RCU_LXTAL: low speed crystal oscillator(LXTAL)
    参数[输出]:  无
    返回值:      无
*/
void RCU_osci_bypass_Mode_Disable(RCU_osci_type_enum osci) {
    uint32_t reg;

    switch(osci) {
    /* disable HXTAL to bypass mode */
    case RCU_HXTAL:
        reg = RCU_CTL;
        RCU_CTL &= ~RCU_CTL_HXTALEN;
        RCU_CTL = (reg & ~RCU_CTL_HXTALBPS);
        break;

    /* disable LXTAL to bypass mode */
    case RCU_LXTAL:
        reg = RCU_BDCTL;
        RCU_BDCTL &= ~RCU_BDCTL_LXTALEN;
        RCU_BDCTL = (reg & ~RCU_BDCTL_LXTALBPS);
        break;

    case RCU_IRC16M:
    case RCU_IRC48M:
    case RCU_IRC32K:
    case RCU_PLL_CK:
    case RCU_PLLI2S_CK:
    case RCU_PLLSAI_CK:
        break;

    default:
        break;
    }
}

/*!
    简介:    set the IRC16M adjust value
    参数[输入]:  irc16m_adjval: IRC16M adjust value, must be between 0 and 0x1F
      参数:        0x00 - 0x1F
    参数[输出]:  无
    返回值:      无
*/
void RCU_irc16m_adjust_Value_Set(uint32_t irc16m_adjval) {
    uint32_t reg;

    reg = RCU_CTL;
    /* reset the IRC16MADJ bits and set 根据 irc16m_adjval */
    reg &= ~RCU_CTL_IRC16MADJ;
    RCU_CTL = (reg | ((irc16m_adjval & RCU_IRC16M_ADJUST_MASK) << RCU_IRC16M_ADJUST_OFFSET));
}

/*!
    简介:    configure the spread spectrum modulation for the main PLL clock
    参数[输入]:  spread_spectrum_type: PLL spread spectrum modulation type select
      参数:        RCU_SS_TYPE_CENTER: center spread type is selected
      参数:        RCU_SS_TYPE_DOWN: down spread type is selected
    参数[输入]:  modstep: configure PLL spread spectrum modulation profile amplitude and frequency
      参数:        This parameter should be selected between 0 and 7FFF.The following criteria must be met: MODSTEP*MODCNT <=2^15-1
    参数[输入]:  modcnt: configure PLL spread spectrum modulation profile amplitude and frequency
      参数:        This parameter should be selected between 0 and 1FFF.The following criteria must be met: MODSTEP*MODCNT <=2^15-1
    参数[输出]:  无
    返回值:      无
*/
void RCU_spread_spectrum_Config(uint32_t spread_spectrum_type, uint32_t modstep, uint32_t modcnt) {
    uint32_t reg;

    reg = RCU_PLLSSCTL;
    /* reset the RCU_PLLSSCTL register bits */
    reg &= ~(RCU_PLLSSCTL_MODCNT | RCU_PLLSSCTL_MODSTEP | RCU_PLLSSCTL_SS_TYPE);
    RCU_PLLSSCTL = (reg | spread_spectrum_type | modstep << 13 | modcnt);
}

/*!
    简介:    enable the PLL spread spectrum modulation
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void RCU_spread_spectrum_Enable(void) {
    RCU_PLLSSCTL |= RCU_PLLSSCTL_SSCGON;
}

/*!
    简介:    disable the PLL spread spectrum modulation
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void RCU_spread_spectrum_Disable(void) {
    RCU_PLLSSCTL &= ~RCU_PLLSSCTL_SSCGON;
}

/*!
    简介:    enable the HXTAL clock monitor
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/

void RCU_hxtal_Clock_monitor_Enable(void) {
    RCU_CTL |= RCU_CTL_CKMEN;
}

/*!
    简介:    disable the HXTAL clock monitor
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void RCU_hxtal_Clock_monitor_Disable(void) {
    RCU_CTL &= ~RCU_CTL_CKMEN;
}

/*!
    简介:    unlock the voltage key
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void RCU_voltage_Key_unlock(void) {
    RCU_VKEY = RCU_VKEY_UNLOCK;
}

/*!
    简介:    deep-sleep mode voltage select
    参数[输入]:  dsvol: deep sleep mode voltage
                only one parameter can be selected which is shown as below:
      参数:        RCU_DEEPSLEEP_V_0: the core voltage is default value
      参数:        RCU_DEEPSLEEP_V_1: the core voltage is (default value-0.1)V(customers are not recommended to use it)
      参数:        RCU_DEEPSLEEP_V_2: the core voltage is (default value-0.2)V(customers are not recommended to use it)
      参数:        RCU_DEEPSLEEP_V_3: the core voltage is (default value-0.3)V(customers are not recommended to use it)
    参数[输出]:  无
    返回值:      无
*/
void RCU_deepsleep_voltage_Set(uint32_t dsvol) {
    dsvol &= RCU_DSV_DSLPVS;
    RCU_DSV = dsvol;
}

/*!
    简介:    get the system clock, bus and peripheral clock frequency
    参数[输入]:  clock: the clock frequency which to get
                only one parameter can be selected which is shown as below:
      参数:        CK_SYS: system clock frequency
      参数:        CK_AHB: AHB clock frequency
      参数:        CK_APB1: APB1 clock frequency
      参数:        CK_APB2: APB2 clock frequency
    参数[输出]:  无
    返回值:     clock frequency of system, AHB, APB1, APB2
*/
uint32_t RCU_Clock_Freq_Get(RCU_Clock_freq_enum clock) {
    uint32_t sws, ck_freq = 0U;
    uint32_t cksys_freq, ahb_freq, apb1_freq, apb2_freq;
    uint32_t pllpsc, plln, pllsel, pllp, ck_src, idx, clk_exp;

    /* exponent of AHB, APB1 and APB2 clock divider */
    const uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
    const uint8_t apb1_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    const uint8_t apb2_exp[8] = {0, 0, 0, 0, 1, 2, 3, 4};

    sws = GET_BITS(RCU_CFG0, 2, 3);

    switch(sws) {
    /* IRC16M is selected as CK_SYS */
    case SEL_IRC16M:
        cksys_freq = IRC16M_VALUE;
        break;

    /* HXTAL is selected as CK_SYS */
    case SEL_HXTAL:
        cksys_freq = HXTAL_VALUE;
        break;

    /* PLLP is selected as CK_SYS */
    case SEL_PLLP:
        /* get the value of PLLPSC[5:0] */
        pllpsc = GET_BITS(RCU_PLL, 0U, 5U);
        plln = GET_BITS(RCU_PLL, 6U, 14U);
        pllp = (GET_BITS(RCU_PLL, 16U, 17U) + 1U) * 2U;
        /* PLL clock source selection, HXTAL or IRC16M/2 */
        pllsel = (RCU_PLL & RCU_PLL_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel) {
            ck_src = HXTAL_VALUE;
        } else {
            ck_src = IRC16M_VALUE;
        }

        cksys_freq = ((ck_src / pllpsc) * plln) / pllp;
        break;

    /* IRC16M is selected as CK_SYS */
    default:
        cksys_freq = IRC16M_VALUE;
        break;
    }

    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    ahb_freq = cksys_freq >> clk_exp;

    /* calculate APB1 clock frequency */
    idx = GET_BITS(RCU_CFG0, 10, 12);
    clk_exp = apb1_exp[idx];
    apb1_freq = ahb_freq >> clk_exp;

    /* calculate APB2 clock frequency */
    idx = GET_BITS(RCU_CFG0, 13, 15);
    clk_exp = apb2_exp[idx];
    apb2_freq = ahb_freq >> clk_exp;

    /* return the clocks frequency */
    switch(clock) {
    case CK_SYS:
        ck_freq = cksys_freq;
        break;

    case CK_AHB:
        ck_freq = ahb_freq;
        break;

    case CK_APB1:
        ck_freq = apb1_freq;
        break;

    case CK_APB2:
        ck_freq = apb2_freq;
        break;

    default:
        break;
    }

    return ck_freq;
}

/*!
    简介:    get the clock stabilization and periphral reset flags
    参数[输入]:  flag: the clock stabilization and periphral reset flags, refer to RCU_Flag_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_Flag_IRC16MSTB: IRC16M stabilization flag
      参数:        RCU_Flag_HXTALSTB: HXTAL stabilization flag
      参数:        RCU_Flag_PLLSTB: PLL stabilization flag
      参数:        RCU_Flag_PLLI2SSTB: PLLI2S stabilization flag
      参数:        RCU_Flag_PLLSAISTB: PLLSAI stabilization flag
      参数:        RCU_Flag_LXTALSTB: LXTAL stabilization flag
      参数:        RCU_Flag_IRC32KSTB: IRC32K stabilization flag
      参数:        RCU_Flag_IRC48MSTB: IRC48M stabilization flag
      参数:        RCU_Flag_BORRST: BOR reset flags
      参数:        RCU_Flag_EPRST: external PIN reset flag
      参数:        RCU_Flag_PORRST: Power reset flag
      参数:        RCU_Flag_SWRST: software reset flag
      参数:        RCU_Flag_FWDGTRST: free watchdog timer reset flag
      参数:        RCU_Flag_WWDGTRST: window watchdog timer reset flag
      参数:        RCU_Flag_LPRST: low-power reset flag
    参数[输出]:  无
    返回值:      无
*/
FlagStatus RCU_Flag_Get(RCU_Flag_enum flag) {
    /* get the rcu flag */
    if(RESET != (RCU_REG_VAL(flag) & BIT(RCU_Bit_POS(flag)))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    简介:    clear all the reset flag
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void RCU_all_reset_Flag_Clear(void) {
    RCU_RSTSCK |= RCU_RSTSCK_RSTFC;
}

/*!
    简介:    get the clock stabilization interrupt and ckm flags
    参数[输入]:  int_flag: interrupt and ckm flags, refer to RCU_int_Flag_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_INT_Flag_IRC32KSTB: IRC32K stabilization interrupt flag
      参数:        RCU_INT_Flag_LXTALSTB: LXTAL stabilization interrupt flag
      参数:        RCU_INT_Flag_IRC16MSTB: IRC16M stabilization interrupt flag
      参数:        RCU_INT_Flag_HXTALSTB: HXTAL stabilization interrupt flag
      参数:        RCU_INT_Flag_PLLSTB: PLL stabilization interrupt flag
      参数:        RCU_INT_Flag_PLLI2SSTB: PLLI2S stabilization interrupt flag
      参数:        RCU_INT_Flag_PLLSAISTB: PLLSAI stabilization interrupt flag
      参数:        RCU_INT_Flag_CKM: HXTAL clock stuck interrupt flag
      参数:        RCU_INT_Flag_IRC48MSTB: IRC48M stabilization interrupt flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus RCU_Interrupt_Flag_Get(RCU_int_Flag_enum int_flag) {
    /* get the rcu interrupt flag */
    if(RESET != (RCU_REG_VAL(int_flag) & BIT(RCU_Bit_POS(int_flag)))) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    简介:    clear the interrupt flags
    参数[输入]:  int_flag: clock stabilization and stuck interrupt flags clear, refer to RCU_int_Flag_Clear_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_INT_Flag_IRC32KSTB_CLR: IRC32K stabilization interrupt flag clear
      参数:        RCU_INT_Flag_LXTALSTB_CLR: LXTAL stabilization interrupt flag clear
      参数:        RCU_INT_Flag_IRC16MSTB_CLR: IRC16M stabilization interrupt flag clear
      参数:        RCU_INT_Flag_HXTALSTB_CLR: HXTAL stabilization interrupt flag clear
      参数:        RCU_INT_Flag_PLLSTB_CLR: PLL stabilization interrupt flag clear
      参数:        RCU_INT_Flag_PLLI2SSTB_CLR: PLLI2S stabilization interrupt flag clear
      参数:        RCU_INT_Flag_PLLSAISTB_CLR: PLLSAI stabilization interrupt flag clear
      参数:        RCU_INT_Flag_CKM_CLR: clock stuck interrupt flag clear
      参数:        RCU_INT_Flag_IRC48MSTB_CLR: IRC48M stabilization interrupt flag clear
    参数[输出]:  无
    返回值:      无
*/
void RCU_Interrupt_Flag_Clear(RCU_int_Flag_Clear_enum int_flag) {
    RCU_REG_VAL(int_flag) |= BIT(RCU_Bit_POS(int_flag));
}

/*!
    简介:    enable the stabilization interrupt
    参数[输入]:  interrupt: clock stabilization interrupt, refer to RCU_int_enum
                Only one parameter can be selected which is shown as below:
      参数:        RCU_INT_IRC32KSTB: IRC32K stabilization interrupt enable
      参数:        RCU_INT_LXTALSTB: LXTAL stabilization interrupt enable
      参数:        RCU_INT_IRC16MSTB: IRC16M stabilization interrupt enable
      参数:        RCU_INT_HXTALSTB: HXTAL stabilization interrupt enable
      参数:        RCU_INT_PLLSTB: PLL stabilization interrupt enable
      参数:        RCU_INT_PLLI2SSTB: PLLI2S stabilization interrupt enable
      参数:        RCU_INT_PLLSAISTB: PLLSAI stabilization interrupt enable
      参数:        RCU_INT_IRC48MSTB: IRC48M stabilization interrupt enable
    参数[输出]:  无
    返回值:      无
*/
void RCU_Interrupt_Enable(RCU_int_enum interrupt) {
    RCU_REG_VAL(interrupt) |= BIT(RCU_Bit_POS(interrupt));
}


/*!
    简介:    disable the stabilization interrupt
    参数[输入]:  interrupt: clock stabilization interrupt, refer to RCU_int_enum
                only one parameter can be selected which is shown as below:
      参数:        RCU_INT_IRC32KSTB: IRC32K stabilization interrupt disable
      参数:        RCU_INT_LXTALSTB: LXTAL stabilization interrupt disable
      参数:        RCU_INT_IRC16MSTB: IRC16M stabilization interrupt disable
      参数:        RCU_INT_HXTALSTB: HXTAL stabilization interrupt disable
      参数:        RCU_INT_PLLSTB: PLL stabilization interrupt disable
      参数:        RCU_INT_PLLI2SSTB: PLLI2S stabilization interrupt disable
      参数:        RCU_INT_PLLSAISTB: PLLSAI stabilization interrupt disable
      参数:        RCU_INT_IRC48MSTB: IRC48M stabilization interrupt disable
    参数[输出]:  无
    返回值:      无
*/
void RCU_Interrupt_Disable(RCU_int_enum interrupt) {
    RCU_REG_VAL(interrupt) &= ~BIT(RCU_Bit_POS(interrupt));
}
