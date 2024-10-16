/**
  ******************************************************************************
  * 文件:    stm32f4xx_fmc.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，以管理FMC 外设设备的以下功能:
  *           + 与 SRAM、PSRAM、NOR 和OneNAND 存储器的接口
  *           + 与 NAND 存储器的接口
  *           + 与 16 位 PC卡 兼容的存储器接口
  *           + 与 SDRAM 存储器的接口
  *           + 中断和标志管理
  *
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
#include "stm32f4xx_fmc.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup FMC
  * 简介: FMC 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
const FMC_NORSRAMTimingInitTypeDef FMC_DefaultTimingStruct = {0x0F, /* FMC_AddressSetupTime */
                                                              0x0F, /* FMC_AddressHoldTime */
                                                              0xFF, /* FMC_DataSetupTime */
                                                              0x0F, /* FMC_BusTurnAroundDuration */
                                                              0x0F, /* FMC_CLKDivision */
                                                              0x0F, /* FMC_DataLatency */
                                                              FMC_AccessMode_A /* FMC_AccessMode */
                                                             };
/* --------------------- FMC 寄存器位掩码 ---------------------------- */
/* FMC BCRx Mask */
#define BCR_MBKEN_SET              ((uint32_t)0x00000001)
#define BCR_MBKEN_RESET            ((uint32_t)0x000FFFFE)
#define BCR_FACCEN_SET             ((uint32_t)0x00000040)

/* FMC PCRx Mask */
#define PCR_PBKEN_SET              ((uint32_t)0x00000004)
#define PCR_PBKEN_RESET            ((uint32_t)0x000FFFFB)
#define PCR_ECCEN_SET              ((uint32_t)0x00000040)
#define PCR_ECCEN_RESET            ((uint32_t)0x000FFFBF)
#define PCR_MEMORYTYPE_NAND        ((uint32_t)0x00000008)

/* FMC SDCRx write protection Mask*/
#define SDCR_WriteProtection_RESET ((uint32_t)0x00007DFF)

/* FMC SDCMR Mask*/
#define SDCMR_CTB1_RESET           ((uint32_t)0x003FFFEF)
#define SDCMR_CTB2_RESET           ((uint32_t)0x003FFFF7)
#define SDCMR_CTB1_2_RESET         ((uint32_t)0x003FFFE7)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup FMC_Private_Functions
  */

/** @defgroup FMC_Group1 NOR/SRAM 控制器功能
  * 简介:     NOR/SRAM 控制器功能
  *
@verbatim
 ===============================================================================
                    ##### NOR 和 SRAM 控制器功能 #####
 ===============================================================================

 [......]应该遵循以下顺序来配置 FMC，以便与连接到 NOR/SRAM 库的 SRAM、PSRAM、NOR或 OneNAND 存储器连接。
      与连接到 NOR/SRAM 库的 SRAM、PSRAM、NOR或 OneNAND 存储器的接口。

   (#) 使用以下函数为 FMC 和相关的 GPIO 启用时钟。
          RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE)。
          RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE)。

   (#) FMC 引脚配置
       (++)使用以下函数将所涉及的 FMC 引脚连接到AF12上
            GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_FMC)。
       (++)通过调用函数在复用功能模式下配置这些 FMC 引脚
            GPIO_Init()。

   (#) 声明一个 FMC_NORSRAMInitTypeDef 结构，例如。
          FMC_NORSRAMInitTypeDef FMC_NORSRAMInitStructure;
      并在FMC_NORSRAMInitStructure变量中填入结构成员的允许值。
      结构成员的允许值。

   (#) 通过调用函数来初始化 NOR/SRAM 控制器
          FMC_NORSRAMInit(&FMC_NORSRAMInitStructure)。

   (#) 然后启用 NOR/SRAM 库，比如说
          FMC_NORSRAMCmd(FMC_Bank1_NORSRAM2, ENABLE)。

   (#) 在这个阶段，你可以从/到连接到 NOR/SRAM 库的内存中读/写。

@endverbatim
  */

/**
  * 简介:  解除对FMC NOR/SRAM银行寄存器的初始化，使其达到默认的复位值。
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC银行。
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank1_NORSRAM1: FMC Bank1 NOR/SRAM1
  *            @arg FMC_Bank1_NORSRAM2: FMC Bank1 NOR/SRAM2
  *            @arg FMC_Bank1_NORSRAM3: FMC Bank1 NOR/SRAM3
  *            @arg FMC_Bank1_NORSRAM4: FMC Bank1 NOR/SRAM4
  * 
  * 返回值: 无
  */
void FMC_NORSRAMDeInit(uint32_t FMC_Bank) {
    /* 检查参数 */
    assert_param(IS_FMC_NORSRAM_BANK(FMC_Bank));

    /* FMC_Bank1_NORSRAM1 */
    if(FMC_Bank == FMC_Bank1_NORSRAM1) {
        FMC_Bank1->BTCR[FMC_Bank] = 0x000030DB;
    }
    /* FMC_Bank1_NORSRAM2,  FMC_Bank1_NORSRAM3 or FMC_Bank1_NORSRAM4 */
    else {
        FMC_Bank1->BTCR[FMC_Bank] = 0x000030D2;
    }

    FMC_Bank1->BTCR[FMC_Bank + 1] = 0x0FFFFFFF;
    FMC_Bank1E->BWTR[FMC_Bank] = 0x0FFFFFFF;
}

/**
  * 简介:  根据 FMC_NORSRAMInitStruct 中指定的参数初始化 FMC NOR/SRAM Bank。
  * 
  * 参数:  FMC_NORSRAMInitStruct : 指向 FMC_NORSRAMUnitTypeDef 结构的指针，
  *                                该结构包含 FMC NOR/SRAM 指定Backs的配置信息。
  * 
  * 返回值: 无
  */
void FMC_NORSRAMInit(FMC_NORSRAMInitTypeDef* FMC_NORSRAMInitStruct) {
    uint32_t tmpr = 0, tmpbcr = 0, tmpbwr = 0;

    /* 检查参数 */
    assert_param(IS_FMC_NORSRAM_BANK(FMC_NORSRAMInitStruct->FMC_Bank));
    assert_param(IS_FMC_MUX(FMC_NORSRAMInitStruct->FMC_DataAddressMux));
    assert_param(IS_FMC_MEMORY(FMC_NORSRAMInitStruct->FMC_MemoryType));
    assert_param(IS_FMC_NORSRAM_MEMORY_WIDTH(FMC_NORSRAMInitStruct->FMC_MemoryDataWidth));
    assert_param(IS_FMC_BURSTMODE(FMC_NORSRAMInitStruct->FMC_BurstAccessMode));
    assert_param(IS_FMC_WAIT_POLARITY(FMC_NORSRAMInitStruct->FMC_WaitSignalPolarity));
    assert_param(IS_FMC_WRAP_MODE(FMC_NORSRAMInitStruct->FMC_WrapMode));
    assert_param(IS_FMC_WAIT_SIGNAL_ACTIVE(FMC_NORSRAMInitStruct->FMC_WaitSignalActive));
    assert_param(IS_FMC_WRITE_OPERATION(FMC_NORSRAMInitStruct->FMC_WriteOperation));
    assert_param(IS_FMC_WAITE_SIGNAL(FMC_NORSRAMInitStruct->FMC_WaitSignal));
    assert_param(IS_FMC_EXTENDED_MODE(FMC_NORSRAMInitStruct->FMC_ExtendedMode));
    assert_param(IS_FMC_ASYNWAIT(FMC_NORSRAMInitStruct->FMC_AsynchronousWait));
    assert_param(IS_FMC_WRITE_BURST(FMC_NORSRAMInitStruct->FMC_WriteBurst));
    assert_param(IS_FMC_CONTINOUS_CLOCK(FMC_NORSRAMInitStruct->FMC_ContinousClock));
    assert_param(IS_FMC_ADDRESS_SETUP_TIME(FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_AddressSetupTime));
    assert_param(IS_FMC_ADDRESS_HOLD_TIME(FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_AddressHoldTime));
    assert_param(IS_FMC_DATASETUP_TIME(FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_DataSetupTime));
    assert_param(IS_FMC_TURNAROUND_TIME(FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_BusTurnAroundDuration));
    assert_param(IS_FMC_CLK_DIV(FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_CLKDivision));
    assert_param(IS_FMC_DATA_LATENCY(FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_DataLatency));
    assert_param(IS_FMC_ACCESS_MODE(FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_AccessMode));

    /* 获取 BTCR 寄存器值 */
    tmpbcr = FMC_Bank1->BTCR[FMC_NORSRAMInitStruct->FMC_Bank];

    /* 清除 MBKEN, MUXEN, MTYP, MWID, FACCEN, BURSTEN, WAITPOL, WRAPMOD, WAITCFG, WREN,
             WAITEN, EXTMOD, ASYNCWAIT, CBURSTRW and CCLKEN 位 */
    tmpbcr &= ((uint32_t)~(FMC_BCR1_MBKEN   | FMC_BCR1_MUXEN    | FMC_BCR1_MTYP     | \
                           FMC_BCR1_MWID     | FMC_BCR1_FACCEN   | FMC_BCR1_BURSTEN  | \
                           FMC_BCR1_WAITPOL  | FMC_BCR1_WRAPMOD  | FMC_BCR1_WAITCFG  | \
                           FMC_BCR1_WREN     | FMC_BCR1_WAITEN   | FMC_BCR1_EXTMOD   | \
                           FMC_BCR1_ASYNCWAIT | FMC_BCR1_CBURSTRW | FMC_BCR1_CCLKEN));

    /* NOR/SRAM 存储体控制寄存器配置*/
    tmpbcr |=  (uint32_t)FMC_NORSRAMInitStruct->FMC_DataAddressMux |
               FMC_NORSRAMInitStruct->FMC_MemoryType |
               FMC_NORSRAMInitStruct->FMC_MemoryDataWidth |
               FMC_NORSRAMInitStruct->FMC_BurstAccessMode |
               FMC_NORSRAMInitStruct->FMC_WaitSignalPolarity |
               FMC_NORSRAMInitStruct->FMC_WrapMode |
               FMC_NORSRAMInitStruct->FMC_WaitSignalActive |
               FMC_NORSRAMInitStruct->FMC_WriteOperation |
               FMC_NORSRAMInitStruct->FMC_WaitSignal |
               FMC_NORSRAMInitStruct->FMC_ExtendedMode |
               FMC_NORSRAMInitStruct->FMC_AsynchronousWait |
               FMC_NORSRAMInitStruct->FMC_WriteBurst |
               FMC_NORSRAMInitStruct->FMC_ContinousClock;

    FMC_Bank1->BTCR[FMC_NORSRAMInitStruct->FMC_Bank] = tmpbcr;

    if(FMC_NORSRAMInitStruct->FMC_MemoryType == FMC_MemoryType_NOR) {
        FMC_Bank1->BTCR[FMC_NORSRAMInitStruct->FMC_Bank] |= (uint32_t)BCR_FACCEN_SET;
    }

    /* 使用 bank2..4 时配置连续时钟功能 */
    if((FMC_NORSRAMInitStruct->FMC_ContinousClock == FMC_CClock_SyncAsync) && (FMC_NORSRAMInitStruct->FMC_Bank != FMC_Bank1_NORSRAM1)) {
        tmpr = (uint32_t)((FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1 + 1]) & ~(((uint32_t)0x0F) << 20));

        FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1]  |= FMC_NORSRAMInitStruct->FMC_ContinousClock;
        FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1]  |= FMC_BurstAccessMode_Enable;
        FMC_Bank1->BTCR[FMC_Bank1_NORSRAM1 + 1] = (uint32_t)(tmpr | (((FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_CLKDivision) - 1) << 20));
    }

    /* NOR/SRAM 组定时寄存器配置*/
    FMC_Bank1->BTCR[FMC_NORSRAMInitStruct->FMC_Bank + 1] =
        (uint32_t)FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_AddressSetupTime |
        (FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_AddressHoldTime << 4) |
        (FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_DataSetupTime << 8) |
        (FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_BusTurnAroundDuration << 16) |
        (FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_CLKDivision << 20) |
        (FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_DataLatency << 24) |
        FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct->FMC_AccessMode;

    /* NOR/SRAM 组定时寄存器，用于写入配置，如果使用扩展模式 */
    if(FMC_NORSRAMInitStruct->FMC_ExtendedMode == FMC_ExtendedMode_Enable) {
        assert_param(IS_FMC_ADDRESS_SETUP_TIME(FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_AddressSetupTime));
        assert_param(IS_FMC_ADDRESS_HOLD_TIME(FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_AddressHoldTime));
        assert_param(IS_FMC_DATASETUP_TIME(FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_DataSetupTime));
        assert_param(IS_FMC_TURNAROUND_TIME(FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_BusTurnAroundDuration));
        assert_param(IS_FMC_ACCESS_MODE(FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_AccessMode));

        /* 获取 BWTR 寄存器值 */
        tmpbwr = FMC_Bank1E->BWTR[FMC_NORSRAMInitStruct->FMC_Bank];

        /* 清除 ADDSET, ADDHLD, DATAST, BUSTURN and ACCMOD 位 */
        tmpbwr &= ((uint32_t)~(FMC_BWTR1_ADDSET  | FMC_BWTR1_ADDHLD | FMC_BWTR1_DATAST | \
                               FMC_BWTR1_BUSTURN | FMC_BWTR1_ACCMOD));

        tmpbwr |= (uint32_t)(FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_AddressSetupTime |
                             (FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_AddressHoldTime << 4) |
                             (FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_DataSetupTime << 8) |
                             (FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_BusTurnAroundDuration << 16) |
                             FMC_NORSRAMInitStruct->FMC_WriteTimingStruct->FMC_AccessMode);

        FMC_Bank1E->BWTR[FMC_NORSRAMInitStruct->FMC_Bank] = tmpbwr;
    } else {
        FMC_Bank1E->BWTR[FMC_NORSRAMInitStruct->FMC_Bank] = 0x0FFFFFFF;
    }

}

/**
  * 简介:  用默认值填充每个 FMC_NORSRAMInitStruct 成员。
  * 
  * 参数:  FMC_NORSRAMInitStruct: 指向将被初始化的 FMC_NORSRAMUnitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void FMC_NORSRAMStructInit(FMC_NORSRAMInitTypeDef* FMC_NORSRAMInitStruct) {
    /* Reset NOR/SRAM Init structure parameters values */
    FMC_NORSRAMInitStruct->FMC_Bank = FMC_Bank1_NORSRAM1;
    FMC_NORSRAMInitStruct->FMC_DataAddressMux = FMC_DataAddressMux_Enable;
    FMC_NORSRAMInitStruct->FMC_MemoryType = FMC_MemoryType_SRAM;
    FMC_NORSRAMInitStruct->FMC_MemoryDataWidth = FMC_NORSRAM_MemoryDataWidth_16b;
    FMC_NORSRAMInitStruct->FMC_BurstAccessMode = FMC_BurstAccessMode_Disable;
    FMC_NORSRAMInitStruct->FMC_AsynchronousWait = FMC_AsynchronousWait_Disable;
    FMC_NORSRAMInitStruct->FMC_WaitSignalPolarity = FMC_WaitSignalPolarity_Low;
    FMC_NORSRAMInitStruct->FMC_WrapMode = FMC_WrapMode_Disable;
    FMC_NORSRAMInitStruct->FMC_WaitSignalActive = FMC_WaitSignalActive_BeforeWaitState;
    FMC_NORSRAMInitStruct->FMC_WriteOperation = FMC_WriteOperation_Enable;
    FMC_NORSRAMInitStruct->FMC_WaitSignal = FMC_WaitSignal_Enable;
    FMC_NORSRAMInitStruct->FMC_ExtendedMode = FMC_ExtendedMode_Disable;
    FMC_NORSRAMInitStruct->FMC_WriteBurst = FMC_WriteBurst_Disable;
    FMC_NORSRAMInitStruct->FMC_ContinousClock = FMC_CClock_SyncOnly;

    FMC_NORSRAMInitStruct->FMC_ReadWriteTimingStruct = (FMC_NORSRAMTimingInitTypeDef*)((uint32_t)&FMC_DefaultTimingStruct);
    FMC_NORSRAMInitStruct->FMC_WriteTimingStruct = (FMC_NORSRAMTimingInitTypeDef*)((uint32_t)&FMC_DefaultTimingStruct);
}

/**
  * 简介:  启用或禁用指定的 NOR/SRAM Memory Bank.
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank1_NORSRAM1: FMC Bank1 NOR/SRAM1
  *            @arg FMC_Bank1_NORSRAM2: FMC Bank1 NOR/SRAM2
  *            @arg FMC_Bank1_NORSRAM3: FMC Bank1 NOR/SRAM3
  *            @arg FMC_Bank1_NORSRAM4: FMC Bank1 NOR/SRAM4
  * 
  * 参数:  NewState: 新状态-> FMC_Bank. 此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMC_NORSRAMCmd(uint32_t FMC_Bank, FunctionalState NewState) {
    assert_param(IS_FMC_NORSRAM_BANK(FMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用通过设置BCRx中的PBKEN 位来选择NOR/SRAM组寄存器 */
        FMC_Bank1->BTCR[FMC_Bank] |= BCR_MBKEN_SET;
    } else {
        /* 禁用通过清除 BCRx 中的 PBKEN 位来选择 NOR/SRAM 组寄存器 */
        FMC_Bank1->BTCR[FMC_Bank] &= BCR_MBKEN_RESET;
    }
}

/** @defgroup FMC_Group2 NAND 控制器功能
  * 简介:     NAND 控制器功能
  *
@verbatim
 ===============================================================================
                    ##### NAND 控制器功能 #####
 ===============================================================================

 [..]应遵循以下顺序来配置 FMC 与连接到 NAND Bank的8位或16位NAND 存储器的接口。

  (#) 使用下列函数为 FMC 和相关的 GPIO 启用时钟。
      (++) RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE)。
      (++) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE)。

  (#) FMC 引脚配置
      (++)使用以下函数将所涉及的 FMC 引脚连接到AF12上
           GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_FMC)。
      (++)通过调用函数在复用功能模式下配置这些 FMC 引脚
           GPIO_Init()。

  (#) 声明一个 FMC_NANDInitTypeDef 结构，例如。
      FMC_NANDInitTypeDef FMC_NANDInitStructure;
      并在FMC_NANDInitStructure变量中填入该结构成员的允许值。

  (#) 通过调用函数来初始化 NAND 控制器
      FMC_NANDInit(&FMC_NANDInitStructure)。

  (#) 然后启用 NAND Bank，比如说。
      FMC_NANDCmd(FMC_Bank3_NAND, ENABLE)。

  (#) 在这个阶段，你可以从/向连接到 NAND Bank的存储器读/写。

 [..]
  (@) 为了启用纠错码(ECC)，你必须使用函数
      FMC_NANDECCCmd(FMC_Bank3_NAND, ENABLE)。
 [..]
  (@)，为了获得当前的 ECC值，你必须使用函数
      ECCval = FMC_GetECC(FMC_Bank3_NAND)。

@endverbatim
  */

/**
  * 简介:  将 FMC NAND Banks 寄存器取消初始化为其默认复位值。
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  * 
  * 返回值: 无
  */
void FMC_NANDDeInit(uint32_t FMC_Bank) {
    /* 检查参数 */
    assert_param(IS_FMC_NAND_BANK(FMC_Bank));

    if(FMC_Bank == FMC_Bank2_NAND) {
        /* 设置 FFMC_Bank2寄存器的重置值 */
        FMC_Bank2->PCR2 = 0x00000018;
        FMC_Bank2->SR2 = 0x00000040;
        FMC_Bank2->PMEM2 = 0xFCFCFCFC;
        FMC_Bank2->PATT2 = 0xFCFCFCFC;
    }
    /* FMC_Bank3_NAND */
    else {
        /* 设置 FFMC_Bank3 寄存器的重置值 */
        FMC_Bank3->PCR3 = 0x00000018;
        FMC_Bank3->SR3 = 0x00000040;
        FMC_Bank3->PMEM3 = 0xFCFCFCFC;
        FMC_Bank3->PATT3 = 0xFCFCFCFC;
    }
}

/**
  * 简介:  根据 FMC_NANDInitStruct 中指定的参数初始化 FMC NAND Bank。
  * 
  * 参数:  FMC_NANDInitStruct : 指向 FMC_NANDInitTypeDef 结构的指针。包含 FMC NAND指定银行的配置信息。
  * 
  * 返回值: 无
  */
void FMC_NANDInit(FMC_NANDInitTypeDef* FMC_NANDInitStruct) {
    uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

    /* 检查参数 */
    assert_param(IS_FMC_NAND_BANK(FMC_NANDInitStruct->FMC_Bank));
    assert_param(IS_FMC_WAIT_FEATURE(FMC_NANDInitStruct->FMC_Waitfeature));
    assert_param(IS_FMC_NAND_MEMORY_WIDTH(FMC_NANDInitStruct->FMC_MemoryDataWidth));
    assert_param(IS_FMC_ECC_STATE(FMC_NANDInitStruct->FMC_ECC));
    assert_param(IS_FMC_ECCPAGE_SIZE(FMC_NANDInitStruct->FMC_ECCPageSize));
    assert_param(IS_FMC_TCLR_TIME(FMC_NANDInitStruct->FMC_TCLRSetupTime));
    assert_param(IS_FMC_TAR_TIME(FMC_NANDInitStruct->FMC_TARSetupTime));
    assert_param(IS_FMC_SETUP_TIME(FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_SetupTime));
    assert_param(IS_FMC_WAIT_TIME(FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_WaitSetupTime));
    assert_param(IS_FMC_HOLD_TIME(FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HoldSetupTime));
    assert_param(IS_FMC_HIZ_TIME(FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HiZSetupTime));
    assert_param(IS_FMC_SETUP_TIME(FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_SetupTime));
    assert_param(IS_FMC_WAIT_TIME(FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_WaitSetupTime));
    assert_param(IS_FMC_HOLD_TIME(FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HoldSetupTime));
    assert_param(IS_FMC_HIZ_TIME(FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HiZSetupTime));

    if(FMC_NANDInitStruct->FMC_Bank == FMC_Bank2_NAND) {
        /* 获取NAND bank 2寄存器值 */
        tmppcr = FMC_Bank2->PCR2;
    } else {
        /* 获取NAND bank 3 寄存器值 */
        tmppcr = FMC_Bank3->PCR3;
    }

    /* 清除 PWAITEN, PBKEN, PTYP, PWID, ECCEN, TCLR, TAR and ECCPS 位 */
    tmppcr &= ((uint32_t)~(FMC_PCR2_PWAITEN  | FMC_PCR2_PBKEN | FMC_PCR2_PTYP | \
                           FMC_PCR2_PWID | FMC_PCR2_ECCEN | FMC_PCR2_TCLR | \
                           FMC_PCR2_TAR | FMC_PCR2_ECCPS));

    /* 设置 tmppcr value 根据 FMC_NANDInitStruct parameters */
    tmppcr |= (uint32_t)FMC_NANDInitStruct->FMC_Waitfeature |
              PCR_MEMORYTYPE_NAND |
              FMC_NANDInitStruct->FMC_MemoryDataWidth |
              FMC_NANDInitStruct->FMC_ECC |
              FMC_NANDInitStruct->FMC_ECCPageSize |
              (FMC_NANDInitStruct->FMC_TCLRSetupTime << 9 ) |
              (FMC_NANDInitStruct->FMC_TARSetupTime << 13);

    if(FMC_NANDInitStruct->FMC_Bank == FMC_Bank2_NAND) {
        /* 获取NAND bank 2寄存器值 */
        tmppmem = FMC_Bank2->PMEM2;
    } else {
        /* 获取NAND bank 3 寄存器值 */
        tmppmem = FMC_Bank3->PMEM3;
    }

    /* 清除 MEMSETx, MEMWAITx, MEMHOLDx and MEMHIZx 位 */
    tmppmem &= ((uint32_t)~(FMC_PMEM2_MEMSET2  | FMC_PMEM2_MEMWAIT2 | FMC_PMEM2_MEMHOLD2 | \
                            FMC_PMEM2_MEMHIZ2));

    /* 根据FMC_CommonSpaceTimingStructure参数设置tmpmem值 */
    tmppmem |= (uint32_t)FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_SetupTime |
               (FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_WaitSetupTime << 8) |
               (FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HoldSetupTime << 16) |
               (FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HiZSetupTime << 24);

    if(FMC_NANDInitStruct->FMC_Bank == FMC_Bank2_NAND) {
        /* 获取NAND bank 2寄存器值 */
        tmppatt = FMC_Bank2->PATT2;
    } else {
        /* 获取NAND bank 3 寄存器值 */
        tmppatt = FMC_Bank3->PATT3;
    }

    /* 清除 ATTSETx, ATTWAITx, ATTHOLDx and ATTHIZx 位 */
    tmppatt &= ((uint32_t)~(FMC_PATT2_ATTSET2  | FMC_PATT2_ATTWAIT2 | FMC_PATT2_ATTHOLD2 | \
                            FMC_PATT2_ATTHIZ2));

    /* 根据FMC_AttributeSpaceTimingStructure参数设置tmppatt值 */
    tmppatt |= (uint32_t)FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_SetupTime |
               (FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_WaitSetupTime << 8) |
               (FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HoldSetupTime << 16) |
               (FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HiZSetupTime << 24);

    if(FMC_NANDInitStruct->FMC_Bank == FMC_Bank2_NAND) {
        /* FMC_Bank2_NAND 寄存器配置*/
        FMC_Bank2->PCR2 = tmppcr;
        FMC_Bank2->PMEM2 = tmppmem;
        FMC_Bank2->PATT2 = tmppatt;
    } else {
        /* FMC_Bank3_NAND 寄存器配置*/
        FMC_Bank3->PCR3 = tmppcr;
        FMC_Bank3->PMEM3 = tmppmem;
        FMC_Bank3->PATT3 = tmppatt;
    }
}


/**
  * 简介:  用默认值填充每个 FMC_NANDInitStruct 成员
  * 
  * 参数:  FMC_NANDInitStruct: 指向 FMC_NANDInitTypeDef 结构的指针，将被初始化。
  * 
  * 返回值: 无
  */
void FMC_NANDStructInit(FMC_NANDInitTypeDef* FMC_NANDInitStruct) {
    /* 重置NAND Init 结构参数值 */
    FMC_NANDInitStruct->FMC_Bank = FMC_Bank2_NAND;
    FMC_NANDInitStruct->FMC_Waitfeature = FMC_Waitfeature_Disable;
    FMC_NANDInitStruct->FMC_MemoryDataWidth = FMC_NAND_MemoryDataWidth_16b;
    FMC_NANDInitStruct->FMC_ECC = FMC_ECC_Disable;
    FMC_NANDInitStruct->FMC_ECCPageSize = FMC_ECCPageSize_256Bytes;
    FMC_NANDInitStruct->FMC_TCLRSetupTime = 0x0;
    FMC_NANDInitStruct->FMC_TARSetupTime = 0x0;
    FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_SetupTime = 252;
    FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_WaitSetupTime = 252;
    FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HoldSetupTime = 252;
    FMC_NANDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HiZSetupTime = 252;
    FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_SetupTime = 252;
    FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_WaitSetupTime = 252;
    FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HoldSetupTime = 252;
    FMC_NANDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HiZSetupTime = 252;
}

/**
  * 简介:  启用或禁用指定的 NAND Memory Bank.
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  * 
  * 参数:  NewState: 新状态-> FMC_Bank. 此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMC_NANDCmd(uint32_t FMC_Bank, FunctionalState NewState) {
    assert_param(IS_FMC_NAND_BANK(FMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用通过在 PCRx中设置PBKEN 位来选择NAND组寄存器 */
        if(FMC_Bank == FMC_Bank2_NAND) {
            FMC_Bank2->PCR2 |= PCR_PBKEN_SET;
        } else {
            FMC_Bank3->PCR3 |= PCR_PBKEN_SET;
        }
    } else {
        /* 禁用通过清除PCRx中的PBKEN 位来选择NAND组寄存器 */
        if(FMC_Bank == FMC_Bank2_NAND) {
            FMC_Bank2->PCR2 &= PCR_PBKEN_RESET;
        } else {
            FMC_Bank3->PCR3 &= PCR_PBKEN_RESET;
        }
    }
}
/**
  * 简介:  启用或禁用 FMC NAND ECC feature.
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  * 
  * 参数:  NewState: FMC NAND ECC功能的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMC_NANDECCCmd(uint32_t FMC_Bank, FunctionalState NewState) {
    assert_param(IS_FMC_NAND_BANK(FMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用通过在 PCRx中设置ECCEN 位来选择NAND组ECC功能寄存器 */
        if(FMC_Bank == FMC_Bank2_NAND) {
            FMC_Bank2->PCR2 |= PCR_ECCEN_SET;
        } else {
            FMC_Bank3->PCR3 |= PCR_ECCEN_SET;
        }
    } else {
        /* 禁用通过清除PCRx中的 ECCEN 位来选择NAND组ECC功能寄存器 */
        if(FMC_Bank == FMC_Bank2_NAND) {
            FMC_Bank2->PCR2 &= PCR_ECCEN_RESET;
        } else {
            FMC_Bank3->PCR3 &= PCR_ECCEN_RESET;
        }
    }
}

/**
  * 简介:  返回纠错码寄存器值。
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  * 
  * 返回值: 纠错代码(ECC)值。
  */
uint32_t FMC_GetECC(uint32_t FMC_Bank) {
    uint32_t eccval = 0x00000000;

    if(FMC_Bank == FMC_Bank2_NAND) {
        /* 获取ECCR2寄存器值 */
        eccval = FMC_Bank2->ECCR2;
    } else {
        /* 获取ECCR3 寄存器值 */
        eccval = FMC_Bank3->ECCR3;
    }

    /* 返回纠错码值 */
    return(eccval);
}

/** @defgroup FMC_Group3 PCCARD 控制器功能
  * 简介:     PCCARD 控制器功能
  *
@verbatim
 ===============================================================================
                    ##### PCCARD 控制器功能 #####
 ===============================================================================

 [..]  应遵循以下顺序来配置 FMC，使其与连接到PCCARD Bank的16位PC卡兼容存储器连接。

  (#) 使用下列函数为 FMC 和相关的 GPIO 启用时钟。
       (++) RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE)。
       (++) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE)。

  (#) FMC 引脚配置
       (++)使用以下函数将所涉及的 FMC 引脚连接到AF12上
            GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_FMC)。
       (++)通过调用函数在复用功能模式下配置这些 FMC 引脚
            GPIO_Init()。

  (#) 声明一个 FMC_PCCARDInitTypeDef 结构，例如。
      FMC_PCCARDInitTypeDef FMC_PCCARDInitStructure;
      并在FMC_PCCARDInitStructure变量中填入该结构成员的允许值。

  (#) 通过调用函数来初始化PCCARD 控制器
      FMC_PCCARDInit(&FMC_PCCARDInitStructure)。

  (#) 然后启用 PCCARD银行。
      FMC_PCCARDCmd(ENABLE)。

  (#) 在这个阶段，你可以从/到连接到PCCARD Bank的存储器中读/写。

@endverbatim
  */

/**
  * 简介:  将 FMC PCCARD 组寄存器取消初始化为其默认复位值。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void FMC_PCCARDDeInit(void) {
    /* 设置 FFMC_Bank4 寄存器的重置值 */
    FMC_Bank4->PCR4 = 0x00000018;
    FMC_Bank4->SR4 = 0x00000000;
    FMC_Bank4->PMEM4 = 0xFCFCFCFC;
    FMC_Bank4->PATT4 = 0xFCFCFCFC;
    FMC_Bank4->PIO4 = 0xFCFCFCFC;
}

/**
  * 简介:  根据 FMC_PCCARDInitStruct 中指定的参数初始化 FMC PCCARD Bank。
  * 
  * 参数:  FMC_PCCARDInitStruct : 指向 FMC_PCCARDInitTypeDef 结构的指针，该结构包含
  *                               FMC PCCARD银行的配置信息。
  * 
  * 返回值: 无
  */
void FMC_PCCARDInit(FMC_PCCARDInitTypeDef* FMC_PCCARDInitStruct) {
    /* 临时寄存器 */
    uint32_t tmppcr = 0, tmpmem = 0, tmppatt = 0, tmppio = 0;

    /* 检查参数 */
    assert_param(IS_FMC_WAIT_FEATURE(FMC_PCCARDInitStruct->FMC_Waitfeature));
    assert_param(IS_FMC_TCLR_TIME(FMC_PCCARDInitStruct->FMC_TCLRSetupTime));
    assert_param(IS_FMC_TAR_TIME(FMC_PCCARDInitStruct->FMC_TARSetupTime));

    assert_param(IS_FMC_SETUP_TIME(FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_SetupTime));
    assert_param(IS_FMC_WAIT_TIME(FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_WaitSetupTime));
    assert_param(IS_FMC_HOLD_TIME(FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HoldSetupTime));
    assert_param(IS_FMC_HIZ_TIME(FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HiZSetupTime));

    assert_param(IS_FMC_SETUP_TIME(FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_SetupTime));
    assert_param(IS_FMC_WAIT_TIME(FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_WaitSetupTime));
    assert_param(IS_FMC_HOLD_TIME(FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HoldSetupTime));
    assert_param(IS_FMC_HIZ_TIME(FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HiZSetupTime));
    assert_param(IS_FMC_SETUP_TIME(FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_SetupTime));
    assert_param(IS_FMC_WAIT_TIME(FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_WaitSetupTime));
    assert_param(IS_FMC_HOLD_TIME(FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_HoldSetupTime));
    assert_param(IS_FMC_HIZ_TIME(FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_HiZSetupTime));

    /* Get PCCARD control寄存器值 */
    tmppcr = FMC_Bank4->PCR4;

    /* 清除 TAR, TCLR, PWAITEN and PWID 位 */
    tmppcr &= ((uint32_t)~(FMC_PCR4_TAR  | FMC_PCR4_TCLR | FMC_PCR4_PWAITEN | \
                           FMC_PCR4_PWID));

    /* 设置根据FMC_CCARDInitStruct参数的PCR4 寄存器值 */
    tmppcr |= (uint32_t)FMC_PCCARDInitStruct->FMC_Waitfeature |
              FMC_NAND_MemoryDataWidth_16b |
              (FMC_PCCARDInitStruct->FMC_TCLRSetupTime << 9) |
              (FMC_PCCARDInitStruct->FMC_TARSetupTime << 13);

    FMC_Bank4->PCR4 = tmppcr;

    /* 获取PCCARD公共空间正时寄存器值 */
    tmpmem = FMC_Bank4->PMEM4;

    /* 清除 MEMSETx, MEMWAITx, MEMHOLDx and MEMHIZx 位 */
    tmpmem &= ((uint32_t)~(FMC_PMEM4_MEMSET4  | FMC_PMEM4_MEMWAIT4 | FMC_PMEM4_MEMHOLD4 | \
                           FMC_PMEM4_MEMHIZ4));

    /* 根据FMC_CommonSpaceTimingStructure参数设置PMEM4 寄存器值 */
    tmpmem |= (uint32_t)FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_SetupTime |
              (FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_WaitSetupTime << 8) |
              (FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HoldSetupTime << 16) |
              (FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HiZSetupTime << 24);

    FMC_Bank4->PMEM4 = tmpmem;

    /* 获取PCCARD正时参数 */
    tmppatt = FMC_Bank4->PATT4;

    /* 清除 ATTSETx, ATTWAITx, ATTHOLDx and ATTHIZx 位 */
    tmppatt &= ((uint32_t)~(FMC_PATT4_ATTSET4  | FMC_PATT4_ATTWAIT4 | FMC_PATT4_ATTHOLD4 | \
                            FMC_PATT4_ATTHIZ4));

    /* 根据FMC_AttributeSpaceTimingStructure参数设置PATT4 寄存器值 */
    tmppatt |= (uint32_t)FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_SetupTime |
               (FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_WaitSetupTime << 8) |
               (FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HoldSetupTime << 16) |
               (FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HiZSetupTime << 24);

    FMC_Bank4->PATT4 = tmppatt;

    /* 获取 FMC_PCARD设备定时参数 */
    tmppio = FMC_Bank4->PIO4;

    /* 清除 IOSET4, IOWAIT4, IOHOLD4 and IOHIZ4 位 */
    tmppio &= ((uint32_t)~(FMC_PIO4_IOSET4  | FMC_PIO4_IOWAIT4 | FMC_PIO4_IOHOLD4 | \
                           FMC_PIO4_IOHIZ4));

    /* 根据FMC_IOSpaceTimingStructure参数设置PIO4 寄存器值 */
    tmppio |= (uint32_t)FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_SetupTime |
              (FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_WaitSetupTime << 8) |
              (FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_HoldSetupTime << 16) |
              (FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_HiZSetupTime << 24);

    FMC_Bank4->PIO4 = tmppio;
}

/**
  * 简介:  用默认值填充每个 FMC_PCCARDInitStruct 成员。
  * 
  * 参数:  FMC_PCCARDInitStruct: 指向 FMC_PCCARDInitTypeDef 结构的指针，将被初始化。
  * 
  * 返回值: 无
  */
void FMC_PCCARDStructInit(FMC_PCCARDInitTypeDef* FMC_PCCARDInitStruct) {
    /* 重置PCCARD Init 结构参数值 */
    FMC_PCCARDInitStruct->FMC_Waitfeature = FMC_Waitfeature_Disable;
    FMC_PCCARDInitStruct->FMC_TCLRSetupTime = 0;
    FMC_PCCARDInitStruct->FMC_TARSetupTime = 0;
    FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_SetupTime = 252;
    FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_WaitSetupTime = 252;
    FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HoldSetupTime = 252;
    FMC_PCCARDInitStruct->FMC_CommonSpaceTimingStruct->FMC_HiZSetupTime = 252;
    FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_SetupTime = 252;
    FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_WaitSetupTime = 252;
    FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HoldSetupTime = 252;
    FMC_PCCARDInitStruct->FMC_AttributeSpaceTimingStruct->FMC_HiZSetupTime = 252;
    FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_SetupTime = 252;
    FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_WaitSetupTime = 252;
    FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_HoldSetupTime = 252;
    FMC_PCCARDInitStruct->FMC_IOSpaceTimingStruct->FMC_HiZSetupTime = 252;
}

/**
  * 简介:  启用或禁用 PCCARD Memory Bank.
  * 
  * 参数:  NewState: PCCARD内存库的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMC_PCCARDCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用通过在 PCR4中设置PBKEN 位，PCCARD Bank寄存器 */
        FMC_Bank4->PCR4 |= PCR_PBKEN_SET;
    } else {
        /* 禁用通过清除PCR4中的PBKEN 位，PCCARD Bank寄存器 */
        FMC_Bank4->PCR4 &= PCR_PBKEN_RESET;
    }
}


/** @defgroup FMC_Group4  SDRAM 控制器功能
  * 简介:     SDRAM 控制器功能
  *
@verbatim
 ===============================================================================
                     ##### SDRAM 控制器功能 #####
 ===============================================================================

 [..]  应遵循以下顺序来配置 FMC 与连接到 SDRAM 库1或SDRAM 库2 的 SDRAM存储器连接。

  (#) 使用下列函数为 FMC 和相关的 GPIO 启用时钟。
      (++) RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE)。
      (++) RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE)。

  (#) FMC 引脚配置
      (++)使用以下函数将所涉及的 FMC 引脚连接到AF12上
           GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_FMC)。
      (++)通过调用函数在复用功能模式下配置这些 FMC 引脚
           GPIO_Init()。

  (#) 声明一个 FMC_SDRAMInitTypeDef 结构，例如。
       FMC_SDRAMInitTypeDef FMC_SDRAMInitStructure;
      并用结构成员的允许值填充FMC_SDRAMInitStructure变量。

  (#) 通过调用函数来初始化 SDRAM 控制器
          FMC_SDRAMInit(&FMC_SDRAMInitStructure)。

  (#) 声明一个 FMC_SDRAMCommandTypeDef 结构，例如。
        FMC_SDRAMCommandTypeDef FMC_SDRAMCommandStructure;
      并用该结构成员的允许值填充FMC_SDRAMCommandStructure变量。

  (#) 通过调用函数FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStructure)，用所需的命令参数配置SDCM寄存器。

  (#) 在这个阶段，SDRAM内存已经准备好接受任何有效的命令。

@endverbatim
  */

/**
  * 简介:  将 FMC SDRAM 组寄存器取消初始化为其默认复位值。
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank1_SDRAM: FMC Bank1 SDRAM
  *            @arg FMC_Bank2_SDRAM: FMC Bank2 SDRAM
  * 
  * 返回值: 无
  */
void FMC_SDRAMDeInit(uint32_t FMC_Bank) {
    /* 检查参数 */
    assert_param(IS_FMC_SDRAM_BANK(FMC_Bank));

    FMC_Bank5_6->SDCR[FMC_Bank] = 0x000002D0;
    FMC_Bank5_6->SDTR[FMC_Bank] = 0x0FFFFFFF;
    FMC_Bank5_6->SDCMR = 0x00000000;
    FMC_Bank5_6->SDRTR = 0x00000000;
    FMC_Bank5_6->SDSR = 0x00000000;
}

/**
  * 简介:  根据 FMC_SDRAMInitStruct 中指定的参数初始化 FMC SDRAM Bank
  * 
  * 参数:  FMC_SDRAMInitStruct : 指向 FMC_SDRAMInitTypeDef 结构的指针，
  *                              该结构包含 FMC SDRAM 指定银行的配置信息。
  * 
  * 返回值: 无
  */
void FMC_SDRAMInit(FMC_SDRAMInitTypeDef* FMC_SDRAMInitStruct) {
    /* 临时寄存器 */
    uint32_t tmpr1 = 0, tmpr2 = 0, tmpr3 = 0, tmpr4 = 0;

    /* 检查参数 */

    /* 控制参数 */
    assert_param(IS_FMC_SDRAM_BANK(FMC_SDRAMInitStruct->FMC_Bank));
    assert_param(IS_FMC_COLUMNBITS_NUMBER(FMC_SDRAMInitStruct->FMC_ColumnBitsNumber));
    assert_param(IS_FMC_ROWBITS_NUMBER(FMC_SDRAMInitStruct->FMC_RowBitsNumber));
    assert_param(IS_FMC_SDMEMORY_WIDTH(FMC_SDRAMInitStruct->FMC_SDMemoryDataWidth));
    assert_param(IS_FMC_INTERNALBANK_NUMBER(FMC_SDRAMInitStruct->FMC_InternalBankNumber));
    assert_param(IS_FMC_CAS_LATENCY(FMC_SDRAMInitStruct->FMC_CASLatency));
    assert_param(IS_FMC_WRITE_PROTECTION(FMC_SDRAMInitStruct->FMC_WriteProtection));
    assert_param(IS_FMC_SDCLOCK_PERIOD(FMC_SDRAMInitStruct->FMC_SDClockPeriod));
    assert_param(IS_FMC_READ_BURST(FMC_SDRAMInitStruct->FMC_ReadBurst));
    assert_param(IS_FMC_READPIPE_DELAY(FMC_SDRAMInitStruct->FMC_ReadPipeDelay));

    /* 定时参数 */
    assert_param(IS_FMC_LOADTOACTIVE_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_LoadToActiveDelay));
    assert_param(IS_FMC_EXITSELFREFRESH_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_ExitSelfRefreshDelay));
    assert_param(IS_FMC_SELFREFRESH_TIME(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_SelfRefreshTime));
    assert_param(IS_FMC_ROWCYCLE_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RowCycleDelay));
    assert_param(IS_FMC_WRITE_RECOVERY_TIME(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_WriteRecoveryTime));
    assert_param(IS_FMC_RP_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RPDelay));
    assert_param(IS_FMC_RCD_DELAY(FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RCDDelay));

    /* Get SDRAM寄存器值 */
    tmpr1 = FMC_Bank5_6->SDCR[FMC_SDRAMInitStruct->FMC_Bank];

    /* 清除 NC, NR, MWID, NB, CAS, WP, SDCLK, RBURST, and RPIPE 位 */
    tmpr1 &= ((uint32_t)~(FMC_SDCR1_NC | FMC_SDCR1_NR | FMC_SDCR1_MWID | \
                          FMC_SDCR1_NB | FMC_SDCR1_CAS | FMC_SDCR1_WP | \
                          FMC_SDCR1_SDCLK | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE));

    /* SDRAM存储体控制寄存器配置*/
    tmpr1 |=   (uint32_t)FMC_SDRAMInitStruct->FMC_ColumnBitsNumber |
               FMC_SDRAMInitStruct->FMC_RowBitsNumber |
               FMC_SDRAMInitStruct->FMC_SDMemoryDataWidth |
               FMC_SDRAMInitStruct->FMC_InternalBankNumber |
               FMC_SDRAMInitStruct->FMC_CASLatency |
               FMC_SDRAMInitStruct->FMC_WriteProtection |
               FMC_SDRAMInitStruct->FMC_SDClockPeriod |
               FMC_SDRAMInitStruct->FMC_ReadBurst |
               FMC_SDRAMInitStruct->FMC_ReadPipeDelay;

    if(FMC_SDRAMInitStruct->FMC_Bank == FMC_Bank1_SDRAM ) {
        FMC_Bank5_6->SDCR[FMC_SDRAMInitStruct->FMC_Bank] = tmpr1;
    } else { /* SDCR2 "don't care" bits 配置*/
        /* Get SDCr 寄存器值 */
        tmpr3 = FMC_Bank5_6->SDCR[FMC_Bank1_SDRAM];

        /* 清除 NC, NR, MWID, NB, CAS, WP, SDCLK, RBURST, and RPIPE 位 */
        tmpr3 &= ((uint32_t)~(FMC_SDCR1_NC  | FMC_SDCR1_NR | FMC_SDCR1_MWID | \
                              FMC_SDCR1_NB  | FMC_SDCR1_CAS | FMC_SDCR1_WP | \
                              FMC_SDCR1_SDCLK | FMC_SDCR1_RBURST | FMC_SDCR1_RPIPE));

        tmpr3 |= (uint32_t)FMC_SDRAMInitStruct->FMC_SDClockPeriod |
                 FMC_SDRAMInitStruct->FMC_ReadBurst |
                 FMC_SDRAMInitStruct->FMC_ReadPipeDelay;

        FMC_Bank5_6->SDCR[FMC_Bank1_SDRAM] = tmpr3;
        FMC_Bank5_6->SDCR[FMC_SDRAMInitStruct->FMC_Bank] = tmpr1;
    }

    /* SDRAM组定时寄存器配置*/
    if(FMC_SDRAMInitStruct->FMC_Bank == FMC_Bank1_SDRAM ) {
        /* Get SDTr 寄存器值 */
        tmpr2 = FMC_Bank5_6->SDTR[FMC_SDRAMInitStruct->FMC_Bank];

        /* 清除 TMRD, TXSR, TRAS, TRC, TWR, TRP and TRCD 位 */
        tmpr2 &= ((uint32_t)~(FMC_SDTR1_TMRD  | FMC_SDTR1_TXSR | FMC_SDTR1_TRAS | \
                              FMC_SDTR1_TRC  | FMC_SDTR1_TWR | FMC_SDTR1_TRP | \
                              FMC_SDTR1_TRCD));

        tmpr2 |=   (uint32_t)((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_LoadToActiveDelay) - 1) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_ExitSelfRefreshDelay) - 1) << 4) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_SelfRefreshTime) - 1) << 8) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RowCycleDelay) - 1) << 12) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_WriteRecoveryTime) - 1) << 16) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RPDelay) - 1) << 20) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RCDDelay) - 1) << 24);

        FMC_Bank5_6->SDTR[FMC_SDRAMInitStruct->FMC_Bank] = tmpr2;
    } else { /* SDTR "don't care bits 配置*/
        /* Get SDTr 寄存器值 */
        tmpr2 = FMC_Bank5_6->SDTR[FMC_SDRAMInitStruct->FMC_Bank];

        /* 清除 TMRD, TXSR, TRAS, TRC, TWR, TRP and TRCD 位 */
        tmpr2 &= ((uint32_t)~(FMC_SDTR1_TMRD  | FMC_SDTR1_TXSR | FMC_SDTR1_TRAS | \
                              FMC_SDTR1_TRC  | FMC_SDTR1_TWR | FMC_SDTR1_TRP | \
                              FMC_SDTR1_TRCD));

        tmpr2 |=   (uint32_t)((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_LoadToActiveDelay) - 1) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_ExitSelfRefreshDelay) - 1) << 4) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_SelfRefreshTime) - 1) << 8) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_WriteRecoveryTime) - 1) << 16);

        /* Get SDTr 寄存器值 */
        tmpr4 = FMC_Bank5_6->SDTR[FMC_Bank1_SDRAM];

        /* 清除 TMRD, TXSR, TRAS, TRC, TWR, TRP and TRCD 位 */
        tmpr4 &= ((uint32_t)~(FMC_SDTR1_TMRD  | FMC_SDTR1_TXSR | FMC_SDTR1_TRAS | \
                              FMC_SDTR1_TRC  | FMC_SDTR1_TWR | FMC_SDTR1_TRP | \
                              FMC_SDTR1_TRCD));

        tmpr4 |=   (uint32_t)(((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RowCycleDelay) - 1) << 12) |
                   (((FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RPDelay) - 1) << 20);

        FMC_Bank5_6->SDTR[FMC_Bank1_SDRAM] = tmpr4;
        FMC_Bank5_6->SDTR[FMC_SDRAMInitStruct->FMC_Bank] = tmpr2;
    }

}

/**
  * 简介:  用默认值填充每个 FMC_SDRAMInitStruct 成员。
  * 
  * 参数:  FMC_SDRAMInitStruct: 指向 FMC_SDRAMInitTypeDef 结构的指针，该结构将被初始化。
  * 
  * 返回值: 无
  */
void FMC_SDRAMStructInit(FMC_SDRAMInitTypeDef* FMC_SDRAMInitStruct) {
    /* 重置SDRAM初始结构参数值 */
    FMC_SDRAMInitStruct->FMC_Bank = FMC_Bank1_SDRAM;
    FMC_SDRAMInitStruct->FMC_ColumnBitsNumber = FMC_ColumnBits_Number_8b;
    FMC_SDRAMInitStruct->FMC_RowBitsNumber = FMC_RowBits_Number_11b;
    FMC_SDRAMInitStruct->FMC_SDMemoryDataWidth = FMC_SDMemory_Width_16b;
    FMC_SDRAMInitStruct->FMC_InternalBankNumber = FMC_InternalBank_Number_4;
    FMC_SDRAMInitStruct->FMC_CASLatency = FMC_CAS_Latency_1;
    FMC_SDRAMInitStruct->FMC_WriteProtection = FMC_Write_Protection_Enable;
    FMC_SDRAMInitStruct->FMC_SDClockPeriod = FMC_SDClock_Disable;
    FMC_SDRAMInitStruct->FMC_ReadBurst = FMC_Read_Burst_Disable;
    FMC_SDRAMInitStruct->FMC_ReadPipeDelay = FMC_ReadPipe_Delay_0;

    FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_LoadToActiveDelay = 16;
    FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_ExitSelfRefreshDelay = 16;
    FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_SelfRefreshTime = 16;
    FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RowCycleDelay = 16;
    FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_WriteRecoveryTime = 16;
    FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RPDelay = 16;
    FMC_SDRAMInitStruct->FMC_SDRAMTimingStruct->FMC_RCDDelay = 16;

}

/**
  * 简介:  配置访问设备时发出的 SDRAM 内存命令。
  * 
  * 参数:  FMC_SDRAMCommandStruct: 指向将被配置的 FMC_SDRAMCommandTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void FMC_SDRAMCmdConfig(FMC_SDRAMCommandTypeDef* FMC_SDRAMCommandStruct) {
    uint32_t tmpr = 0x0;

    /* 检查 parameters */
    assert_param(IS_FMC_COMMAND_MODE(FMC_SDRAMCommandStruct->FMC_CommandMode));
    assert_param(IS_FMC_COMMAND_TARGET(FMC_SDRAMCommandStruct->FMC_CommandTarget));
    assert_param(IS_FMC_AUTOREFRESH_NUMBER(FMC_SDRAMCommandStruct->FMC_AutoRefreshNumber));
    assert_param(IS_FMC_MODE_REGISTER(FMC_SDRAMCommandStruct->FMC_ModeRegisterDefinition));

    tmpr =   (uint32_t)(FMC_SDRAMCommandStruct->FMC_CommandMode |
                        FMC_SDRAMCommandStruct->FMC_CommandTarget |
                        (((FMC_SDRAMCommandStruct->FMC_AutoRefreshNumber) - 1) << 5) |
                        ((FMC_SDRAMCommandStruct->FMC_ModeRegisterDefinition) << 9));

    FMC_Bank5_6->SDCMR = tmpr;

}


/**
  * 简介:  返回指示的 FMC SDRAM 组模式状态。
  * 
  * 参数:  SDRAM_Bank: 定义FMC SDRAM 库。
  *                    这个参数可以是FMC_Bank1_SDRAM或FMC_Bank2_SDRAM。
  * 
  * 返回值: FMC 的 SDRAM 库模式状态
  */
uint32_t FMC_GetModeStatus(uint32_t SDRAM_Bank) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FMC_SDRAM_BANK(SDRAM_Bank));

    /* 获取busy flag 状态 */
    if(SDRAM_Bank == FMC_Bank1_SDRAM) {
        tmpreg = (uint32_t)(FMC_Bank5_6->SDSR & FMC_SDSR_MODES1);
    } else {
        tmpreg = ((uint32_t)(FMC_Bank5_6->SDSR & FMC_SDSR_MODES2) >> 2);
    }

    /* 返回mode 状态 */
    return tmpreg;
}

/**
  * 简介:  定义 SDRAM 内存刷新率
  * 
  * 参数:  FMC_Count: 指定刷新定时器的计数。
  * 
  * 返回值: 无
  */
void FMC_SetRefreshCount(uint32_t FMC_Count) {
    /* 检查参数 */
    assert_param(IS_FMC_REFRESH_COUNT(FMC_Count));

    FMC_Bank5_6->SDRTR |= (FMC_Count << 1);

}

/**
  * 简介:  设置连续 SDRAM 内存自动刷新命令的数量。
  * 
  * 参数:  FMC_Number: 指定自动刷新号码。
  * 
  * 返回值: 无
  */
void FMC_SetAutoRefresh_Number(uint32_t FMC_Number) {
    /* 检查参数 */
    assert_param(IS_FMC_AUTOREFRESH_NUMBER(FMC_Number));

    FMC_Bank5_6->SDCMR |= (FMC_Number << 5);
}

/**
  * 简介:  启用或禁用对指定 FMC SDRAM Bank 的写保护。
  * 
  * 参数:  SDRAM_Bank: 定义FMC SDRAM 库。
  *                    这个参数可以是FMC_Bank1_SDRAM或FMC_Bank2_SDRAM。
  * 
  * 参数:  NewState: 写保护标志的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMC_SDRAMWriteProtectionConfig(uint32_t SDRAM_Bank, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_FMC_SDRAM_BANK(SDRAM_Bank));

    if (NewState != DISABLE) {
        FMC_Bank5_6->SDCR[SDRAM_Bank] |= FMC_Write_Protection_Enable;
    } else {
        FMC_Bank5_6->SDCR[SDRAM_Bank] &= SDCR_WriteProtection_RESET;
    }

}


/** @defgroup FMC_Group5  中断和标记管理函数
  * 简介:     中断和标记管理函数
  *
@verbatim
 ===============================================================================
             ##### 中断和标记管理函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 FMC 中断.
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  *            @arg FMC_Bank4_PCCARD: FMC Bank4 PCCARD
  *            @arg FMC_Bank1_SDRAM: FMC Bank1 SDRAM
  *            @arg FMC_Bank2_SDRAM: FMC Bank2 SDRAM
  * 
  * 参数:  FMC_IT: 指定要启用或禁用的 FMC 中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg FMC_IT_RisingEdge: 上升沿检测中断。
  *            @arg FMC_IT_Level: 水平边缘检测中断。
  *            @arg FMC_IT_FallingEdge: 下降沿检测中断。
  *            @arg FMC_IT_Refresh: 刷新错误检测中断。
  * 
  * 参数:  NewState: 指定FMC 中断的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FMC_ITConfig(uint32_t FMC_Bank, uint32_t FMC_IT, FunctionalState NewState) {
    assert_param(IS_FMC_IT_BANK(FMC_Bank));
    assert_param(IS_FMC_IT(FMC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 FMC_Bank2 中断 */
        if(FMC_Bank == FMC_Bank2_NAND) {
            FMC_Bank2->SR2 |= FMC_IT;
        }
        /* 启用被选定的 FMC_Bank3 中断 */
        else if (FMC_Bank == FMC_Bank3_NAND) {
            FMC_Bank3->SR3 |= FMC_IT;
        }
        /* 启用被选定的 FMC_Bank4 中断 */
        else if (FMC_Bank == FMC_Bank4_PCCARD) {
            FMC_Bank4->SR4 |= FMC_IT;
        }
        /* 启用被选定的 FMC_Bank5_6 中断 */
        else {
            /* 如果刷新错误标志为，则启用中断被设置 */
            FMC_Bank5_6->SDRTR |= FMC_IT;
        }
    } else {
        /* 禁用被选中的 FMC_Bank2 中断 */
        if(FMC_Bank == FMC_Bank2_NAND) {

            FMC_Bank2->SR2 &= (uint32_t)~FMC_IT;
        }
        /* 禁用被选中的 FMC_Bank3 中断 */
        else if (FMC_Bank == FMC_Bank3_NAND) {
            FMC_Bank3->SR3 &= (uint32_t)~FMC_IT;
        }
        /* 禁用被选中的 FMC_Bank4 中断 */
        else if(FMC_Bank == FMC_Bank4_PCCARD) {
            FMC_Bank4->SR4 &= (uint32_t)~FMC_IT;
        }
        /* 禁用被选中的 FMC_Bank5_6 中断 */
        else {
            /* 如果未设置刷新错误标志，则禁用中断 */
            FMC_Bank5_6->SDRTR &= (uint32_t)~FMC_IT;
        }
    }
}

/**
  * 简介:  检查是否设置了指定的 FMC 标志。
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  *            @arg FMC_Bank4_PCCARD: FMC Bank4 PCCARD
  *            @arg FMC_Bank1_SDRAM: FMC Bank1 SDRAM
  *            @arg FMC_Bank2_SDRAM: FMC Bank2 SDRAM
  *            @arg FMC_Bank1_SDRAM | FMC_Bank2_SDRAM: FMC Bank1 or Bank2 SDRAM
  * 
  * 参数:  FMC_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg FMC_FLAG_RisingEdge: 上升沿检测标志。
  *            @arg FMC_FLAG_Level: 水平检测标志。
  *            @arg FMC_FLAG_FallingEdge: 下降边缘检测标志.
  *            @arg FMC_FLAG_FEMPT: Fifo 空标志
  *            @arg FMC_FLAG_Refresh: 刷新错误标志。
  *            @arg FMC_FLAG_Busy: 忙碌状态标志。
  * 
  * 返回值: FMC_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus FMC_GetFlagStatus(uint32_t FMC_Bank, uint32_t FMC_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tmpsr = 0x00000000;

    /* 检查参数 */
    assert_param(IS_FMC_GETFLAG_BANK(FMC_Bank));
    assert_param(IS_FMC_GET_FLAG(FMC_FLAG));

    if(FMC_Bank == FMC_Bank2_NAND) {
        tmpsr = FMC_Bank2->SR2;
    } else if(FMC_Bank == FMC_Bank3_NAND) {
        tmpsr = FMC_Bank3->SR3;
    } else if(FMC_Bank == FMC_Bank4_PCCARD) {
        tmpsr = FMC_Bank4->SR4;
    } else {
        tmpsr = FMC_Bank5_6->SDSR;
    }

    /* 获取flag 状态 */
    if ((tmpsr & FMC_FLAG) != FMC_FLAG ) {
        bitstatus = RESET;
    } else {
        bitstatus = SET;
    }

    /* 返回标志状态 */
    return bitstatus;
}

/**
  * 简介:  清除 FMC 的挂起标志。
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  *            @arg FMC_Bank4_PCCARD: FMC Bank4 PCCARD
  *            @arg FMC_Bank1_SDRAM: FMC Bank1 SDRAM
  *            @arg FMC_Bank2_SDRAM: FMC Bank2 SDRAM
  * 
  * 参数:  FMC_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *            @arg FMC_FLAG_RisingEdge: 上升沿检测标志。
  *            @arg FMC_FLAG_Level: 水平检测标志。
  *            @arg FMC_FLAG_FallingEdge: 下降边缘检测标志.
  *            @arg FMC_FLAG_Refresh: 刷新错误标志。
  * 
  * 返回值: 无
  */
void FMC_ClearFlag(uint32_t FMC_Bank, uint32_t FMC_FLAG) {
    /* 检查参数 */
    assert_param(IS_FMC_GETFLAG_BANK(FMC_Bank));
    assert_param(IS_FMC_CLEAR_FLAG(FMC_FLAG)) ;

    if(FMC_Bank == FMC_Bank2_NAND) {
        FMC_Bank2->SR2 &= (~FMC_FLAG);
    } else if(FMC_Bank == FMC_Bank3_NAND) {
        FMC_Bank3->SR3 &= (~FMC_FLAG);
    } else if(FMC_Bank == FMC_Bank4_PCCARD) {
        FMC_Bank4->SR4 &= (~FMC_FLAG);
    }
    /* FMC_Bank5_6 SDRAM*/
    else {
        FMC_Bank5_6->SDRTR &= (~FMC_FLAG);
    }

}

/**
  * 简介:  检查是否发生了指定的 FMC 中断。
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  *            @arg FMC_Bank4_PCCARD: FMC Bank4 PCCARD
  *            @arg FMC_Bank1_SDRAM: FMC Bank1 SDRAM
  *            @arg FMC_Bank2_SDRAM: FMC Bank2 SDRAM
  * 
  * 参数:  FMC_IT: 指定要检查的 FMC 中断源。
  *          此参数可以是以下值之一:
  *            @arg FMC_IT_RisingEdge: 上升沿检测中断。
  *            @arg FMC_IT_Level: 水平边缘检测中断。
  *            @arg FMC_IT_FallingEdge: 下降沿检测中断。
  *            @arg FMC_IT_Refresh: 刷新错误检测中断。
  * 
  * 返回值: FMC_IT 的新状态(SET 或 RESET)。
  */
ITStatus FMC_GetITStatus(uint32_t FMC_Bank, uint32_t FMC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t tmpsr = 0x0;
    uint32_t tmpsr2 = 0x0;
    uint32_t itstatus = 0x0;
    uint32_t itenable = 0x0;

    /* 检查参数 */
    assert_param(IS_FMC_IT_BANK(FMC_Bank));
    assert_param(IS_FMC_GET_IT(FMC_IT));

    if(FMC_Bank == FMC_Bank2_NAND) {
        tmpsr = FMC_Bank2->SR2;
    } else if(FMC_Bank == FMC_Bank3_NAND) {
        tmpsr = FMC_Bank3->SR3;
    } else if(FMC_Bank == FMC_Bank4_PCCARD) {
        tmpsr = FMC_Bank4->SR4;
    }
    /* FMC_Bank5_6 SDRAM*/
    else {
        tmpsr = FMC_Bank5_6->SDRTR;
        tmpsr2 = FMC_Bank5_6->SDSR;
    }

    /* 获取IT启用位状态*/
    itenable = tmpsr & FMC_IT;

    /* 获取相应的 IT 标志状态*/
    if((FMC_Bank == FMC_Bank1_SDRAM) || (FMC_Bank == FMC_Bank2_SDRAM)) {
        itstatus = tmpsr2 & FMC_SDSR_RE;
    } else {
        itstatus = tmpsr & (FMC_IT >> 3);
    }

    if ((itstatus != (uint32_t)RESET)  && (itenable != (uint32_t)RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 FMC 的中断挂起位
  * 
  * 参数:  FMC_Bank: 指定要使用的 FMC Bank
  *          此参数可以是以下值之一:
  *            @arg FMC_Bank2_NAND: FMC Bank2 NAND
  *            @arg FMC_Bank3_NAND: FMC Bank3 NAND
  *            @arg FMC_Bank4_PCCARD: FMC Bank4 PCCARD
  *            @arg FMC_Bank1_SDRAM: FMC Bank1 SDRAM
  *            @arg FMC_Bank2_SDRAM: FMC Bank2 SDRAM
  * 
  * 参数:  FMC_IT: 指定要清除的中断等待位。
  *          此参数可以是以下值的任意组合:
  *            @arg FMC_IT_RisingEdge: 上升沿检测中断。
  *            @arg FMC_IT_Level: 水平边缘检测中断。
  *            @arg FMC_IT_FallingEdge: 下降沿检测中断。
  *            @arg FMC_IT_Refresh: 刷新错误检测中断。
  * 
  * 返回值: 无
  */
void FMC_ClearITPendingBit(uint32_t FMC_Bank, uint32_t FMC_IT) {
    /* 检查参数 */
    assert_param(IS_FMC_IT_BANK(FMC_Bank));
    assert_param(IS_FMC_IT(FMC_IT));

    if(FMC_Bank == FMC_Bank2_NAND) {
        FMC_Bank2->SR2 &= ~(FMC_IT >> 3);
    } else if(FMC_Bank == FMC_Bank3_NAND) {
        FMC_Bank3->SR3 &= ~(FMC_IT >> 3);
    } else if(FMC_Bank == FMC_Bank4_PCCARD) {
        FMC_Bank4->SR4 &= ~(FMC_IT >> 3);
    }
    /* FMC_Bank5_6 SDRAM*/
    else {
        FMC_Bank5_6->SDRTR |= FMC_SDRTR_CRE;
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
