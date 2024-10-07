/**
  ******************************************************************************
  * 文件:    stm32f4xx_syscfg.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供管理SYSCFG外设设备的固件功能。
  *
 @verbatim

 ===============================================================================
                     ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..] 该驱动程序提供以下功能:

       (#) 使用 SYSCFG_MemoryRemapConfig() 重新映射代码区中可访问的内存

       (#) 交换内部闪存 Bank1 和 Bank2 此功能仅对 STM32F42xxx/43xxx 设备设备可见。

       (#) 使用 SYSCFG_EXTILineConfig() 管理到GPIO的EXTI线路连接
       
       (#) 使用 SYSCFG_ETH_MediaInterfaceConfig() 选择以太网媒体接口(RMII/RII)

       -@- 必须启用SYSCFG APB时钟，才能使用RCC_APB2PeriphClockCmd(RCC_APP2PeripH_SYSCFG，ENABLE)
		  获得对SYSCFG寄存器的写入访问权限;

 @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup SYSCFG
  * 简介: SYSCFG驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* ------------ RCC registers bit address in the alias region ----------- */
#define SYSCFG_OFFSET             (SYSCFG_BASE - PERIPH_BASE)
/* ---  MEMRMP 寄存器 ---*/
/* Alias word address of UFB_MODE 位 */
#define MEMRMP_OFFSET             SYSCFG_OFFSET
#define UFB_MODE_BitNumber        ((uint8_t)0x8)
#define UFB_MODE_BB               (PERIPH_BB_BASE + (MEMRMP_OFFSET * 32) + (UFB_MODE_BitNumber * 4))

/* ---  PMC 寄存器 ---*/
/* Alias word address of MII_RMII_SEL 位 */
#define PMC_OFFSET                (SYSCFG_OFFSET + 0x04)
#define MII_RMII_SEL_BitNumber    ((uint8_t)0x17)
#define PMC_MII_RMII_SEL_BB       (PERIPH_BB_BASE + (PMC_OFFSET * 32) + (MII_RMII_SEL_BitNumber * 4))

/* ---  CMPCR 寄存器 ---*/
/* Alias word address of CMP_PD 位 */
#define CMPCR_OFFSET              (SYSCFG_OFFSET + 0x20)
#define CMP_PD_BitNumber          ((uint8_t)0x00)
#define CMPCR_CMP_PD_BB           (PERIPH_BB_BASE + (CMPCR_OFFSET * 32) + (CMP_PD_BitNumber * 4))

/* ---  MCHDLYCR 寄存器 ---*/
/* Alias word address of BSCKSEL 位 */
#define MCHDLYCR_OFFSET            (SYSCFG_OFFSET + 0x30)
#define BSCKSEL_BIT_NUMBER         POSITION_VAL(SYSCFG_MCHDLYCR_BSCKSEL)
#define MCHDLYCR_BSCKSEL_BB        (uint32_t)(PERIPH_BB_BASE + (MCHDLYCR_OFFSET * 32) + (BSCKSEL_BIT_NUMBER * 4))

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup SYSCFG_Private_Functions
  */

/**
  * 简介:  将备用函数(重映射和 EXTI 配置)寄存器取消初始化为其默认重置值。
  * 参数:  无
  * 返回值: 无
  */
void SYSCFG_DeInit(void) {
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, DISABLE);
}

/**
  * 简介:  更改指定引脚的映射。
  * 参数:  SYSCFG_Memory: 选择内存重新映射。
  *         此参数可以是以下值之一:
  *            @arg SYSCFG_MemoryRemap_Flash:       主闪存映射为0x00000000
  *            @arg SYSCFG_MemoryRemap_SystemFlash: 系统闪存映射为0x00000000
  *            @arg SYSCFG_MemoryRemap_FSMC:        FSMC (Bank1 (NOR/PSRAM 1 and 2) mapped at 0x00000000 for STM32F405xx/407xx, STM32F415xx/417xx and STM32F413_423xx devices.
  *            @arg SYSCFG_MemoryRemap_FMC:         FMC (Bank1 (NOR/PSRAM 1 and 2) mapped at 0x00000000 for STM32F42xxx/43xxx devices.
  *            @arg SYSCFG_MemoryRemap_ExtMEM:      External Memory mapped at 0x00000000 for STM32F446xx/STM32F469_479xx devices.
  *            @arg SYSCFG_MemoryRemap_SRAM:        Embedded SRAM (112kB) mapped at 0x00000000
  *            @arg SYSCFG_MemoryRemap_SDRAM:       FMC (External SDRAM)  mapped at 0x00000000 for STM32F42xxx/43xxx devices.
  * 返回值: 无
  */
void SYSCFG_MemoryRemapConfig(uint8_t SYSCFG_MemoryRemap) {
    /* 检查参数 */
    assert_param(IS_SYSCFG_MEMORY_REMAP_CONFING(SYSCFG_MemoryRemap));

    SYSCFG->MEMRMP = SYSCFG_MemoryRemap;
}

/**
  * 简介:  启用或禁用内部闪存组交换。
  *
  * 注意:   此函数只能用于STM32F42xxx/43xxx设备。
  *
  * 参数:  NewState: 内部闪存库交换的新状态。
  *          此参数可以是以下值之一:
  *            @arg ENABLE: Flash Bank2映射于0x080000000(别名为@0x00000000)，
  *                         Flash Bank1映射于0x00810000(别名为0x001000000)
  *            @arg DISABLE:(默认状态)Flash Bank1映射到0x0800000(别名为@0x0000 0000)，
  *                         Flash Bank2映射到0x8810000(别名为0x00100000)
  * 返回值: 无
  */
void SYSCFG_MemorySwappingBank(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    *(__IO uint32_t *) UFB_MODE_BB = (uint32_t)NewState;
}

/**
  * 简介:  选择用作 EXTI 线路的 GPIO 引脚。
  * 参数:  EXTI_PortSourceGPIOx : 选择要用作EXTI线路源的GPIO端口，其中x可以是
  *                               STM32F42xxx/43xxx设备的(A..K)，(A..I)
  *                               用于STM32P405xx/407xx和STM32C415xx/417xx设备，
  *                               或(A、B、C、D和H)用于STM2401xx设备。
  *
  * 参数:  EXTI_PinSourcex: 指定要配置的EXTI行。
  *           此参数可以是EXTI_PinSourcex，其中x可以是(0..15，除了EXTI_PortSourceGPIOI x
  *           对于STM32F405xx/407xx和STM32P405xx/407xxx设备可以为(0..11)，
  *           对于EXTI_Port SourceGPIOK x对于STM2F42xxx/43xxx设备可为(0..7)。
  *
  * 返回值: 无
  */
void SYSCFG_EXTILineConfig(uint8_t EXTI_PortSourceGPIOx, uint8_t EXTI_PinSourcex) {
    uint32_t tmp = 0x00;

    /* 检查参数 */
    assert_param(IS_EXTI_PORT_SOURCE(EXTI_PortSourceGPIOx));
    assert_param(IS_EXTI_PIN_SOURCE(EXTI_PinSourcex));

    tmp = ((uint32_t)0x0F) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03));
    SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] &= ~tmp;
    SYSCFG->EXTICR[EXTI_PinSourcex >> 0x02] |= (((uint32_t)EXTI_PortSourceGPIOx) << (0x04 * (EXTI_PinSourcex & (uint8_t)0x03)));
}

/**
  * 简介:  选择以太网媒体接口。
  * 参数:  SYSCFG_ETH_MediaInterface: 指定媒体接口模式。
  *          此参数可以是以下值之一:
  *            @arg SYSCFG_ETH_MediaInterface_MII: 已选择MII模式
  *            @arg SYSCFG_ETH_MediaInterface_RMII: 已选择RMII模式
  * 返回值: 无
  */
void SYSCFG_ETH_MediaInterfaceConfig(uint32_t SYSCFG_ETH_MediaInterface) {
    assert_param(IS_SYSCFG_ETH_MEDIA_INTERFACE(SYSCFG_ETH_MediaInterface));
    /* 配置MII_RMII选择位*/
    *(__IO uint32_t *) PMC_MII_RMII_SEL_BB = SYSCFG_ETH_MediaInterface;
}

/**
  * 简介:  启用或禁用 I/O 补偿单元。
  * 注意:   仅当设备电源电压范围为2.4至3.6 V时，才能使用I/O补偿单元。
  * 参数:  NewState: I/O补偿单元的新状态。
  *          此参数可以是以下值之一:
  *            @arg ENABLE: I/O补偿单元已启用
  *            @arg DISABLE: I/O补偿单元断电模式
  * 返回值: 无
  */
void SYSCFG_CompensationCellCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    *(__IO uint32_t *) CMPCR_CMP_PD_BB = (uint32_t)NewState;
}

/**
  * 简介:  检查是否设置了 I/O 补偿单元就绪标志。
  * 参数:  无
  * 返回值: I/O补偿单元就绪标志的新状态(SET或RESET)
  */
FlagStatus SYSCFG_GetCompensationCellStatus(void) {
    FlagStatus bitstatus = RESET;

    if ((SYSCFG->CMPCR & SYSCFG_CMPCR_READY ) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx)
/**
  * 简介:  将所选参数连接到 TIM1 的中断输入。
  * 注意:   所选配置已锁定，可以通过系统重置解除锁定
  * 参数:  SYSCFG_Break: 选择要连接到中断TIM1输入的配置
  *   此参数可以是以下值的任意组合:
  *     @arg SYSCFG_Break_PVD: PVD中断连接至TIM1/8的中断输入。
  *     @arg SYSCFG_Break_HardFault: CortexM4的锁定输出连接到TIM1/8的中断输入。
  * 返回值: 无
  */
void SYSCFG_BreakConfig(uint32_t SYSCFG_Break) {
    /* 检查参数 */
    assert_param(IS_SYSCFG_LOCK_CONFIG(SYSCFG_Break));

    SYSCFG->CFGR2 |= (uint32_t) SYSCFG_Break;
}
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx */

#if defined(STM32F413_423xx)
/**
  * 简介:  选择 DFSDM2 或 TIM2_OC1 作为比特流时钟的时钟源。
  * 参数:  source: BITSTREAM_CLOCK_DFSDM2.
  *                BITSTREAM_CLOCK_TIM2OC1.
  * 返回值: 无
  */
void DFSDM_BitstreamClock_SourceSelection(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;
    tmp = (tmp & (~SYSCFG_MCHDLYCR_BSCKSEL));

    SYSCFG->MCHDLYCR  = (tmp | source);
}

/**
  * 简介:  禁用 DFSDM1/2 的延迟时钟。
  * 参数:  MCHDLY: MCHDLY_CLOCK_DFSDM2.
  *                MCHDLY_CLOCK_DFSDM1.
  * 返回值: 无
  */
void DFSDM_DisableDelayClock(uint32_t MCHDLY) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;

    if(MCHDLY == MCHDLY_CLOCK_DFSDM2) {
        tmp = tmp & (~SYSCFG_MCHDLYCR_MCHDLY2EN);
    } else {
        tmp = tmp & (~SYSCFG_MCHDLYCR_MCHDLY1EN);
    }

    SYSCFG->MCHDLYCR  = tmp;
}

/**
  * 简介:  启用 DFSDM1/2 的延迟时钟。
  * 参数:  MCHDLY: MCHDLY_CLOCK_DFSDM2.
  *                MCHDLY_CLOCK_DFSDM1.
  * 返回值: 无
  */
void DFSDM_EnableDelayClock(uint32_t MCHDLY) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;
    tmp = tmp & ~MCHDLY;

    SYSCFG->MCHDLYCR  = (tmp | MCHDLY);
}

/**
  * 简介:  选择 DFSDM1/2 的 CKin 信号源。
  * 参数:  source: DFSDM2_CKIN_PAD.
  *                DFSDM2_CKIN_DM.
  *                DFSDM1_CKIN_PAD.
  *                DFSDM1_CKIN_DM.
  * 返回值: 无
  */
void DFSDM_ClockIn_SourceSelection(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;

    if((source == DFSDM2_CKIN_PAD) || (source == DFSDM2_CKIN_DM)) {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2CFG);
    } else {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM1CFG);
    }

    SYSCFG->MCHDLYCR |= (source | tmp);
}

/**
  * 简介:  为 DFSDM1/2 选择 CKOut 信号源。
  * 参数:  source: DFSDM2_CKOUT_DFSDM2.
  *                DFSDM2_CKOUT_M27.
  *                DFSDM1_CKOUT_DFSDM1.
  *                DFSDM1_CKOUT_M27.
  * 返回值: 无
  */
void DFSDM_ClockOut_SourceSelection(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;

    if((source == DFSDM2_CKOUT_DFSDM2) || (source == DFSDM2_CKOUT_M27)) {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2CKOSEL);
    } else {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM1CKOSEL);
    }

    SYSCFG->MCHDLYCR |= (source | tmp);
}

/**
  * 简介:  选择 DFSDM1/2 的 DataIn0 信号源。
  * 参数:  source: DATAIN0_DFSDM2_PAD.
  *                DATAIN0_DFSDM2_DATAIN1.
  *                DATAIN0_DFSDM1_PAD.
  *                DATAIN0_DFSDM1_DATAIN1.
  * 返回值: 无
  */
void DFSDM_DataIn0_SourceSelection(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;

    if((source == DATAIN0_DFSDM2_PAD) || (source == DATAIN0_DFSDM2_DATAIN1)) {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2D0SEL);
    } else {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM1D0SEL);
    }

    SYSCFG->MCHDLYCR |= (source | tmp);
}

/**
  * 简介:  为 DFSDM1/2 选择 DataIn2 信号源。
  * 参数:  source: DATAIN2_DFSDM2_PAD.
  *                DATAIN2_DFSDM2_DATAIN3.
  *                DATAIN2_DFSDM1_PAD.
  *                DATAIN2_DFSDM1_DATAIN3.
  * 返回值: 无
  */
void DFSDM_DataIn2_SourceSelection(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;

    if((source == DATAIN2_DFSDM2_PAD) || (source == DATAIN2_DFSDM2_DATAIN3)) {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2D2SEL);
    } else {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM1D2SEL);
    }

    SYSCFG->MCHDLYCR |= (source | tmp);
}

/**
  * 简介:  为 DFSDM2 选择 DataIn4 信号源。
  * 参数:  source: DATAIN4_DFSDM2_PAD.
  *                DATAIN4_DFSDM2_DATAIN5
  * 返回值: 无
  */
void DFSDM_DataIn4_SourceSelection(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;
    tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2D4SEL);

    SYSCFG->MCHDLYCR |= (source | tmp);
}

/**
  * 简介:  为 DFSDM2 选择 DataIn6 信号源。
  * 参数:  source: DATAIN6_DFSDM2_PAD.
  *                DATAIN6_DFSDM2_DATAIN7.
  * 返回值: 无
  */
void DFSDM_DataIn6_SourceSelection(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;

    tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2D6SEL);

    SYSCFG->MCHDLYCR |= (source | tmp);
}

/**
  * 简介:  配置从 TIM4 门控的比特流时钟的分布。
  * 参数:  source: DFSDM1_CLKIN0_TIM4OC2
  *                DFSDM1_CLKIN2_TIM4OC2
  *                DFSDM1_CLKIN1_TIM4OC1
  *                DFSDM1_CLKIN3_TIM4OC1
  * 返回值: 无
  */
void DFSDM1_BitStreamClk_Config(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;

    if ((source == DFSDM1_CLKIN0_TIM4OC2) || (source == DFSDM1_CLKIN2_TIM4OC2)) {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM1CK02SEL);
    } else {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM1CK13SEL);
    }

    SYSCFG->MCHDLYCR |= (source | tmp);
}

/**
  * 简介:  配置从 TIM3 门控的比特流时钟的分布。
  * 参数:  source: DFSDM2_CLKIN0_TIM3OC4
  *                DFSDM2_CLKIN4_TIM3OC4
  *                DFSDM2_CLKIN1_TIM3OC3
  *                DFSDM2_CLKIN5_TIM3OC3
  *                DFSDM2_CLKIN2_TIM3OC2
  *                DFSDM2_CLKIN6_TIM3OC2
  *                DFSDM2_CLKIN3_TIM3OC1
  *                DFSDM2_CLKIN7_TIM3OC1
  * 返回值: 无
  */
void DFSDM2_BitStreamClk_Config(uint32_t source) {
    uint32_t tmp = 0;

    tmp = SYSCFG->MCHDLYCR;

    if ((source == DFSDM2_CLKIN0_TIM3OC4) || (source == DFSDM2_CLKIN4_TIM3OC4)) {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2CK04SEL);
    } else if ((source == DFSDM2_CLKIN1_TIM3OC3) || (source == DFSDM2_CLKIN5_TIM3OC3)) {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2CK15SEL);

    } else  if ((source == DFSDM2_CLKIN2_TIM3OC2) || (source == DFSDM2_CLKIN6_TIM3OC2)) {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2CK26SEL);
    } else {
        tmp =  (tmp & ~SYSCFG_MCHDLYCR_DFSDM2CK37SEL);
    }

    SYSCFG->MCHDLYCR |= (source | tmp);
}

#endif /* STM32F413_423xx */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
