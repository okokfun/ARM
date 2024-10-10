/**
  ******************************************************************************
  * 文件:    stm32f4xx_fsmc.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
 * 简介:    该文件提供了固件功能来管理FSMC外设的以下功能:
  *           + 与SRAM、PSRAM、NOR和OneNAND存储器的接口
  *           + 与NAND存储器的接口
  *           + 与16位PC卡兼容存储器的接口
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
#include "stm32f4xx_fsmc.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup FSMC
  * 简介: FSMC 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
const FSMC_NORSRAMTimingInitTypeDef FSMC_DefaultTimingStruct = {0x0F, /* FSMC_AddressSetupTime */
                                                                0x0F, /* FSMC_AddressHoldTime */
                                                                0xFF, /* FSMC_DataSetupTime */
                                                                0x0F, /* FSMC_BusTurnAroundDuration */
                                                                0x0F, /* FSMC_CLKDivision */
                                                                0x0F, /* FSMC_DataLatency */
                                                                FSMC_AccessMode_A /* FSMC_AccessMode */
                                                               };
/* 私有宏 ------------------------------------------------------------*/

/* --------------------- FSMC寄存器位掩码 ---------------------------- */
/* FSMC BCRx Mask */
#define BCR_MBKEN_SET          ((uint32_t)0x00000001)
#define BCR_MBKEN_RESET        ((uint32_t)0x000FFFFE)
#define BCR_FACCEN_SET         ((uint32_t)0x00000040)

/* FSMC PCRx Mask */
#define PCR_PBKEN_SET          ((uint32_t)0x00000004)
#define PCR_PBKEN_RESET        ((uint32_t)0x000FFFFB)
#define PCR_ECCEN_SET          ((uint32_t)0x00000040)
#define PCR_ECCEN_RESET        ((uint32_t)0x000FFFBF)
#define PCR_MEMORYTYPE_NAND    ((uint32_t)0x00000008)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup FSMC_Private_Functions
  */

/** @defgroup FSMC_Group1 NOR和SRAM控制器功能
 *  简介   NOR和SRAM控制器功能
 *
@verbatim
 ===============================================================================
                    ##### NOR和SRAM控制器功能 #####
 ===============================================================================

 [...] 应遵循以下顺序来配置FSMC与连接到NOR/SRAM库的SRAM、PSRAM、NOR或OneNAND存储器的接口。

   (#) 使用以下函数为FSMC 和相关的GPIO启用时钟。
          RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE)。
          RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE)。

   (#) FSMC引脚配置
       (++) 使用以下函数将所涉及的FSMC引脚连接到AF12上
             GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_FSMC)。
       (++) 通过调用函数GPIO_Init()在复用功能模式下配置这些FSMC引脚。

   (#) 声明一个FSMC_NORSRAMInitTypeDef结构，例如。
          FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
      并在FSMC_NORSRAMInitStructure变量中填入该结构成员的允许值。

   (#) 通过调用函数来初始化NOR/SRAM控制器
          FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure)。

   (#)然后启用 NOR/SRAM库，例如。
          FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE)。

   (#) 在这个阶段，你可以从/到连接到NOR/SRAM库的内存中读/写。

@endverbatim
  */

/**
  * 简介:  将 FSMC NAND 存储体寄存器取消初始化为其默认重置值。
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank1_NORSRAM1: FSMC Bank1 NOR/SRAM1
  *            @arg FSMC_Bank1_NORSRAM2: FSMC Bank1 NOR/SRAM2
  *            @arg FSMC_Bank1_NORSRAM3: FSMC Bank1 NOR/SRAM3
  *            @arg FSMC_Bank1_NORSRAM4: FSMC Bank1 NOR/SRAM4
  * 
  * 返回值: 无
  */
void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank) {
    /* 检查参数 */
    assert_param(IS_FSMC_NORSRAM_BANK(FSMC_Bank));

    /* FSMC_Bank1_NORSRAM1 */
    if(FSMC_Bank == FSMC_Bank1_NORSRAM1) {
        FSMC_Bank1->BTCR[FSMC_Bank] = 0x000030DB;
    }
    /* FSMC_Bank1_NORSRAM2,  FSMC_Bank1_NORSRAM3 or FSMC_Bank1_NORSRAM4 */
    else {
        FSMC_Bank1->BTCR[FSMC_Bank] = 0x000030D2;
    }

    FSMC_Bank1->BTCR[FSMC_Bank + 1] = 0x0FFFFFFF;
    FSMC_Bank1E->BWTR[FSMC_Bank] = 0x0FFFFFFF;
}

/**
  * 简介:  根据FSMC_NANDInitStruct中指定的参数初始化 FSMC NAND 库。
  * 
  * 参数:  FSMC_NORSRAMInitStruct : 指向FSMC_NORSRAMInitTypeDef结构的指针，
  *                                 该结构包含FSMC NOR/SRAM指定银行的配置信息。
  * 
  * 返回值: 无
  */
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct) {
    uint32_t tmpbcr = 0, tmpbtr = 0, tmpbwr = 0;

    /* 检查参数 */
    assert_param(IS_FSMC_NORSRAM_BANK(FSMC_NORSRAMInitStruct->FSMC_Bank));
    assert_param(IS_FSMC_MUX(FSMC_NORSRAMInitStruct->FSMC_DataAddressMux));
    assert_param(IS_FSMC_MEMORY(FSMC_NORSRAMInitStruct->FSMC_MemoryType));
    assert_param(IS_FSMC_MEMORY_WIDTH(FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth));
    assert_param(IS_FSMC_BURSTMODE(FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode));
    assert_param(IS_FSMC_ASYNWAIT(FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait));
    assert_param(IS_FSMC_WAIT_POLARITY(FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity));
    assert_param(IS_FSMC_WRAP_MODE(FSMC_NORSRAMInitStruct->FSMC_WrapMode));
    assert_param(IS_FSMC_WAIT_SIGNAL_ACTIVE(FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive));
    assert_param(IS_FSMC_WRITE_OPERATION(FSMC_NORSRAMInitStruct->FSMC_WriteOperation));
    assert_param(IS_FSMC_WAITE_SIGNAL(FSMC_NORSRAMInitStruct->FSMC_WaitSignal));
    assert_param(IS_FSMC_EXTENDED_MODE(FSMC_NORSRAMInitStruct->FSMC_ExtendedMode));
    assert_param(IS_FSMC_WRITE_BURST(FSMC_NORSRAMInitStruct->FSMC_WriteBurst));
    assert_param(IS_FSMC_ADDRESS_SETUP_TIME(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime));
    assert_param(IS_FSMC_ADDRESS_HOLD_TIME(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime));
    assert_param(IS_FSMC_DATASETUP_TIME(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime));
    assert_param(IS_FSMC_TURNAROUND_TIME(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration));
    assert_param(IS_FSMC_CLK_DIV(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision));
    assert_param(IS_FSMC_DATA_LATENCY(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency));
    assert_param(IS_FSMC_ACCESS_MODE(FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode));

    /* 获取BTCR寄存器值 */
    tmpbcr = FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank];

    /* 清除 MBKEN, MUXEN, MTYP, MWID, FACCEN, BURSTEN, WAITPOL, WRAPMOD, WAITCFG, WREN,
             WAITEN, EXTMOD, ASYNCWAIT, CBURSTRW and CCLKEN 位 */
    tmpbcr &= ((uint32_t)~(FSMC_BCR1_MBKEN    | FSMC_BCR1_MUXEN    | FSMC_BCR1_MTYP     | \
                           FSMC_BCR1_MWID      | FSMC_BCR1_FACCEN   | FSMC_BCR1_BURSTEN  | \
                           FSMC_BCR1_WAITPOL   | FSMC_BCR1_WRAPMOD  | FSMC_BCR1_WAITCFG  | \
                           FSMC_BCR1_WREN      | FSMC_BCR1_WAITEN   | FSMC_BCR1_EXTMOD   | \
                           FSMC_BCR1_ASYNCWAIT | FSMC_BCR1_CBURSTRW));

    /* Bank1 NOR/SRAM control register 配置*/
    tmpbcr |= (uint32_t)FSMC_NORSRAMInitStruct->FSMC_DataAddressMux |
              FSMC_NORSRAMInitStruct->FSMC_MemoryType |
              FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth |
              FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode |
              FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait |
              FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity |
              FSMC_NORSRAMInitStruct->FSMC_WrapMode |
              FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive |
              FSMC_NORSRAMInitStruct->FSMC_WriteOperation |
              FSMC_NORSRAMInitStruct->FSMC_WaitSignal |
              FSMC_NORSRAMInitStruct->FSMC_ExtendedMode |
              FSMC_NORSRAMInitStruct->FSMC_WriteBurst;

    FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] = tmpbcr;

    if(FSMC_NORSRAMInitStruct->FSMC_MemoryType == FSMC_MemoryType_NOR) {
        FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] |= (uint32_t)BCR_FACCEN_SET;
    }

    /* 获取BTCR寄存器值 */
    tmpbtr = FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank + 1];

    /* 清除 ADDSET, ADDHLD, DATAST, BUSTURN, CLKDIV, DATLAT and ACCMOD 位 */
    tmpbtr &= ((uint32_t)~(FSMC_BTR1_ADDSET | FSMC_BTR1_ADDHLD | FSMC_BTR1_DATAST | \
                           FSMC_BTR1_BUSTURN | FSMC_BTR1_CLKDIV | FSMC_BTR1_DATLAT | \
                           FSMC_BTR1_ACCMOD));

    /* Bank1 NOR/SRAM timing register 配置*/
    tmpbtr |= (uint32_t)FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime |
              (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime << 4) |
              (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime << 8) |
              (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
              (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision << 20) |
              (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency << 24) |
              FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode;

    FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank + 1] = tmpbtr;

    /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
    if(FSMC_NORSRAMInitStruct->FSMC_ExtendedMode == FSMC_ExtendedMode_Enable) {
        assert_param(IS_FSMC_ADDRESS_SETUP_TIME(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime));
        assert_param(IS_FSMC_ADDRESS_HOLD_TIME(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime));
        assert_param(IS_FSMC_DATASETUP_TIME(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime));
        assert_param(IS_FSMC_TURNAROUND_TIME(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration));
        assert_param(IS_FSMC_ACCESS_MODE(FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode));

        /* 获取BWTR寄存器值 */
        tmpbwr = FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank];

        /* 清除 ADDSET, ADDHLD, DATAST, BUSTURN, and ACCMOD 位 */
        tmpbwr &= ((uint32_t)~(FSMC_BWTR1_ADDSET | FSMC_BWTR1_ADDHLD | FSMC_BWTR1_DATAST | \
                               FSMC_BWTR1_BUSTURN | FSMC_BWTR1_ACCMOD));

        tmpbwr |= (uint32_t)FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime |
                  (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime << 4 ) |
                  (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime << 8) |
                  (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
                  FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode;

        FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = tmpbwr;
    } else {
        FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 0x0FFFFFFF;
    }
}

/**
  * 简介:  用其默认值填充每个FSMC_NANDInitStruct成员。
  * 
  * 参数:  FSMC_NORSRAMInitStruct: 指向FSMC_NORSRAMInitTypeDef结构的指针，将被初始化。
  * 
  * 返回值: 无
  */
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct) {
    /* Reset NOR/SRAM Init structure parameters values */
    FSMC_NORSRAMInitStruct->FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStruct->FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
    FSMC_NORSRAMInitStruct->FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
    FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStruct->FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStruct->FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStruct->FSMC_WaitSignal = FSMC_WaitSignal_Enable;
    FSMC_NORSRAMInitStruct->FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStruct->FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct = (FSMC_NORSRAMTimingInitTypeDef*)((uint32_t)&FSMC_DefaultTimingStruct);
    FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct = (FSMC_NORSRAMTimingInitTypeDef*)((uint32_t)&FSMC_DefaultTimingStruct);
}

/**
  * 简介:  启用或禁用指定的 NOR/SRAM Memory Bank.
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank1_NORSRAM1: FSMC Bank1 NOR/SRAM1
  *            @arg FSMC_Bank1_NORSRAM2: FSMC Bank1 NOR/SRAM2
  *            @arg FSMC_Bank1_NORSRAM3: FSMC Bank1 NOR/SRAM3
  *            @arg FSMC_Bank1_NORSRAM4: FSMC Bank1 NOR/SRAM4
  * 
  * 参数:  NewState: 新状态-> FSMC_Bank. 此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState) {
    assert_param(IS_FSMC_NORSRAM_BANK(FSMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用通过设置BCRx中的PBKEN位来选择NOR/SRAM组寄存器 */
        FSMC_Bank1->BTCR[FSMC_Bank] |= BCR_MBKEN_SET;
    } else {
        /* 禁用通过清除 BCRx 中的 PBKEN 位来选择 NOR/SRAM 组寄存器 */
        FSMC_Bank1->BTCR[FSMC_Bank] &= BCR_MBKEN_RESET;
    }
}

/** @defgroup FSMC_Group2 NAND控制器功能
 *  简介   NAND控制器功能
 *
@verbatim
 ===============================================================================
                    ##### NAND控制器功能 #####
 ===============================================================================

 [..]  按照以下顺序配置FSMC与连接到NAND Bank的8位或16位NAND内存接口:

  (#) 使用以下函数启用FSMC 和相关GPIO的时钟。
      (++)  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
      (++)  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

  (#) FSMC引脚配置
      (++) 使用以下函数将涉及的FSMC引脚连接到AF12上:
           GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_FSMC);
      (++) 通过调用函数GPIO_Init()在交替功能模式下配置这些FSMC引脚。

  (#) 声明一个FSMC_NANDInitTypeDef结构，比如说。
      FSMC_NANDInitTypeDef  FSMC_NANDInitStructure;
      并用结构成员的允许值填充FSMC_NANDInitStructure变量。

  (#) 通过调用函数初始化NAND控制器
      FSMC_NANDInit(&FSMC_NANDInitStructure);

  (#) 然后启用 NAND Bank，比如说:
      FSMC_NANDCmd(FSMC_Bank3_NAND, ENABLE);

  (#) 在这个阶段，你可以从/向连接到NAND Bank的存储器读/写。

 [..]
  (@) 要启用纠错代码(ECC)，你必须使用函数
      FSMC_NANDECCCmd(FSMC_Bank3_NAND, ENABLE);
 [..]
  (@) 而要获得当前的ECC值，你必须使用函数
      ECCval = FSMC_GetECC(FSMC_Bank3_NAND);

@endverbatim
  */

/**
  * 简介:  取消初始化 FSMC NOR/SRAM 组寄存器到其默认复位值。
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND: FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND: FSMC Bank3 NAND
  * 
  * 返回值: 无
  */
void FSMC_NANDDeInit(uint32_t FSMC_Bank) {
    /* 检查参数 */
    assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));

    if(FSMC_Bank == FSMC_Bank2_NAND) {
        /* 设置 FSMC_Bank2 registers to their reset values */
        FSMC_Bank2->PCR2 = 0x00000018;
        FSMC_Bank2->SR2 = 0x00000040;
        FSMC_Bank2->PMEM2 = 0xFCFCFCFC;
        FSMC_Bank2->PATT2 = 0xFCFCFCFC;
    }
    /* FSMC_Bank3_NAND */
    else {
        /* 设置 FSMC_Bank3 将寄存器设置为其重置值 */
        FSMC_Bank3->PCR3 = 0x00000018;
        FSMC_Bank3->SR3 = 0x00000040;
        FSMC_Bank3->PMEM3 = 0xFCFCFCFC;
        FSMC_Bank3->PATT3 = 0xFCFCFCFC;
    }
}

/**
  * 简介:  根据FSMC_NANDInitStruct中指定的参数初始化 FSMC NAND 库。
  * 
  * 参数:  FSMC_NANDInitStruct : 指向FSMC_NANDInitTypeDef结构的指针，
  *                              该结构包含FSMC NAND指定银行的配置信息。
  * 
  * 返回值: 无
  */
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct) {
    uint32_t tmppcr = 0x00000000, tmppmem = 0x00000000, tmppatt = 0x00000000;

    /* 检查参数 */
    assert_param( IS_FSMC_NAND_BANK(FSMC_NANDInitStruct->FSMC_Bank));
    assert_param( IS_FSMC_WAIT_FEATURE(FSMC_NANDInitStruct->FSMC_Waitfeature));
    assert_param( IS_FSMC_MEMORY_WIDTH(FSMC_NANDInitStruct->FSMC_MemoryDataWidth));
    assert_param( IS_FSMC_ECC_STATE(FSMC_NANDInitStruct->FSMC_ECC));
    assert_param( IS_FSMC_ECCPAGE_SIZE(FSMC_NANDInitStruct->FSMC_ECCPageSize));
    assert_param( IS_FSMC_TCLR_TIME(FSMC_NANDInitStruct->FSMC_TCLRSetupTime));
    assert_param( IS_FSMC_TAR_TIME(FSMC_NANDInitStruct->FSMC_TARSetupTime));
    assert_param(IS_FSMC_SETUP_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime));
    assert_param(IS_FSMC_WAIT_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime));
    assert_param(IS_FSMC_HOLD_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime));
    assert_param(IS_FSMC_HIZ_TIME(FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime));
    assert_param(IS_FSMC_SETUP_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime));
    assert_param(IS_FSMC_WAIT_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime));
    assert_param(IS_FSMC_HOLD_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime));
    assert_param(IS_FSMC_HIZ_TIME(FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime));

    if(FSMC_NANDInitStruct->FSMC_Bank == FSMC_Bank2_NAND) {
        /* 获取NAND bank 2寄存器值 */
        tmppcr = FSMC_Bank2->PCR2;
    } else {
        /* 获取NAND bank 3寄存器值 */
        tmppcr = FSMC_Bank3->PCR3;
    }

    /* 清除 PWAITEN, PBKEN, PTYP, PWID, ECCEN, TCLR, TAR and ECCPS 位 */
    tmppcr &= ((uint32_t)~(FSMC_PCR2_PWAITEN  | FSMC_PCR2_PBKEN | FSMC_PCR2_PTYP | \
                           FSMC_PCR2_PWID | FSMC_PCR2_ECCEN | FSMC_PCR2_TCLR | \
                           FSMC_PCR2_TAR | FSMC_PCR2_ECCPS));

    /* 设置 tmppcr 值根据 FSMC_NANDInitStruct 参数 */
    tmppcr |= (uint32_t)FSMC_NANDInitStruct->FSMC_Waitfeature |
              PCR_MEMORYTYPE_NAND |
              FSMC_NANDInitStruct->FSMC_MemoryDataWidth |
              FSMC_NANDInitStruct->FSMC_ECC |
              FSMC_NANDInitStruct->FSMC_ECCPageSize |
              (FSMC_NANDInitStruct->FSMC_TCLRSetupTime << 9 ) |
              (FSMC_NANDInitStruct->FSMC_TARSetupTime << 13);

    if(FSMC_NANDInitStruct->FSMC_Bank == FSMC_Bank2_NAND) {
        /* 获取NAND bank 2寄存器值 */
        tmppmem = FSMC_Bank2->PMEM2;
    } else {
        /* 获取NAND bank 3寄存器值 */
        tmppmem = FSMC_Bank3->PMEM3;
    }

    /* 清除 MEMSETx, MEMWAITx, MEMHOLDx and MEMHIZx 位 */
    tmppmem &= ((uint32_t)~(FSMC_PMEM2_MEMSET2  | FSMC_PMEM2_MEMWAIT2 | FSMC_PMEM2_MEMHOLD2 | \
                            FSMC_PMEM2_MEMHIZ2));

    /* 根据FSMC_CommonSpaceTimingStructure参数设置tmpmem值 */
    tmppmem |= (uint32_t)FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
               (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
               (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
               (FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24);

    if(FSMC_NANDInitStruct->FSMC_Bank == FSMC_Bank2_NAND) {
        /* 获取NAND bank 2寄存器值 */
        tmppatt = FSMC_Bank2->PATT2;
    } else {
        /* 获取NAND bank 3寄存器值 */
        tmppatt = FSMC_Bank2->PATT2;
    }

    /* 清除 ATTSETx, ATTWAITx, ATTHOLDx and ATTHIZx 位 */
    tmppatt &= ((uint32_t)~(FSMC_PATT2_ATTSET2  | FSMC_PATT2_ATTWAIT2 | FSMC_PATT2_ATTHOLD2 | \
                            FSMC_PATT2_ATTHIZ2));

    /* 根据FSMC_AttributeSpaceTimingStructure参数设置tmppatt值 */
    tmppatt |= (uint32_t)FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
               (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
               (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
               (FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24);

    if(FSMC_NANDInitStruct->FSMC_Bank == FSMC_Bank2_NAND) {
        /* FSMC_Bank2_NAND 寄存器配置*/
        FSMC_Bank2->PCR2 = tmppcr;
        FSMC_Bank2->PMEM2 = tmppmem;
        FSMC_Bank2->PATT2 = tmppatt;
    } else {
        /* FSMC_Bank3_NAND 寄存器配置*/
        FSMC_Bank3->PCR3 = tmppcr;
        FSMC_Bank3->PMEM3 = tmppmem;
        FSMC_Bank3->PATT3 = tmppatt;
    }
}


/**
  * 简介:  用其默认值填充每个FSMC_NANDInitStruct成员。
  * 
  * 参数:  FSMC_NANDInitStruct: 指向FSMC_NANDInitTypeDef结构的指针，将被初始化。
  * 
  * 返回值: 无
  */
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct) {
    /* 重置NAND Init结构参数值 */
    FSMC_NANDInitStruct->FSMC_Bank = FSMC_Bank2_NAND;
    FSMC_NANDInitStruct->FSMC_Waitfeature = FSMC_Waitfeature_Disable;
    FSMC_NANDInitStruct->FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
    FSMC_NANDInitStruct->FSMC_ECC = FSMC_ECC_Disable;
    FSMC_NANDInitStruct->FSMC_ECCPageSize = FSMC_ECCPageSize_256Bytes;
    FSMC_NANDInitStruct->FSMC_TCLRSetupTime = 0x0;
    FSMC_NANDInitStruct->FSMC_TARSetupTime = 0x0;
    FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_NANDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
}

/**
  * 简介:  启用或禁用指定的 NAND Memory Bank.
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND: FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND: FSMC Bank3 NAND
  * 
  * 参数:  NewState: 新状态-> FSMC_Bank. 
  *                  此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState) {
    assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用通过在PCRx中设置PBKEN位来选择NAND组寄存器 */
        if(FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->PCR2 |= PCR_PBKEN_SET;
        } else {
            FSMC_Bank3->PCR3 |= PCR_PBKEN_SET;
        }
    } else {
        /* 禁用通过清除PCRx中的PBKEN位来选择NAND组寄存器 */
        if(FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->PCR2 &= PCR_PBKEN_RESET;
        } else {
            FSMC_Bank3->PCR3 &= PCR_PBKEN_RESET;
        }
    }
}
/**
  * 简介:  启用或禁用FSMC NAND ECC feature.
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND: FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND: FSMC Bank3 NAND
  * 
  * 参数:  NewState: 新状态-> FSMC NAND ECC feature.
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState) {
    assert_param(IS_FSMC_NAND_BANK(FSMC_Bank));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用通过在PCRx中设置ECCEN位来选择NAND组ECC功能寄存器 */
        if(FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->PCR2 |= PCR_ECCEN_SET;
        } else {
            FSMC_Bank3->PCR3 |= PCR_ECCEN_SET;
        }
    } else {
        /* 禁用通过清除PCRx中的ECCEN位来选择NAND组ECC功能寄存器 */
        if(FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->PCR2 &= PCR_ECCEN_RESET;
        } else {
            FSMC_Bank3->PCR3 &= PCR_ECCEN_RESET;
        }
    }
}

/**
  * 简介:  返回纠错码寄存器值。
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND: FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND: FSMC Bank3 NAND
  * 
  * 返回值: 纠错代码(ECC)值。
  */
uint32_t FSMC_GetECC(uint32_t FSMC_Bank) {
    uint32_t eccval = 0x00000000;

    if(FSMC_Bank == FSMC_Bank2_NAND) {
        /* 获取ECCR2寄存器值 */
        eccval = FSMC_Bank2->ECCR2;
    } else {
        /* 获取ECCR3寄存器值 */
        eccval = FSMC_Bank3->ECCR3;
    }

    /* 返回纠错码值 */
    return(eccval);
}

/** @defgroup FSMC_Group3 PCCARD控制器功能
 *  简介   PCCARD控制器功能
 *
@verbatim
 ===============================================================================
                    ##### PCCARD控制器功能 #####
 ===============================================================================

 [..]  应遵循以下顺序来配置FSMC，使其与连接到PCCARD Bank的16位PC卡兼容存储器连接。

  (#) 使用以下功能启用FSMC的时钟和相关的GPIO。
       (++)  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
       (++)  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

  (#) FSMC引脚配置
       (++)使用以下函数将涉及的FSMC引脚连接到AF12上
            GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_FSMC) 。
       (++)通过调用函数GPIO_Init()在复用功能模式下配置这些FSMC引脚。

  (#) 声明一个FSMC_PCCARDInitTypeDef结构，例如:
      FSMC_PCCARDInitTypeDef FSMC_PCCARDInitStructure;
      并在FSMC_PCCARDInitStructure变量中填入该结构成员的允许值。

  (#) 通过调用函数来初始化PCCARD控制器
      FSMC_PCCARDInit(&FSMC_PCCARDInitStructure)。

  (#) 然后启用 PCCARD Back:
      FSMC_PCCARDCmd(ENABLE)。

  (#) 在这个阶段，你可以对连接到PCCARD Bank的内存进行读/写。

@endverbatim
  */

/**
  * 简介:  取消初始化 FSMC PCCARD 银行寄存器到其默认重置值。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void FSMC_PCCARDDeInit(void) {
    /* 设置FSMC_Bank4将寄存器设置为其重置值 */
    FSMC_Bank4->PCR4 = 0x00000018;
    FSMC_Bank4->SR4 = 0x00000000;
    FSMC_Bank4->PMEM4 = 0xFCFCFCFC;
    FSMC_Bank4->PATT4 = 0xFCFCFCFC;
    FSMC_Bank4->PIO4 = 0xFCFCFCFC;
}

/**
  * 简介:  根据FSMC_PCCARDInitStruct中指定的参数初始化 FSMC PCCARD 库。
  * 
  * 参数:  FSMC_PCCARDInitStruct : 指向FSMC_PCCARDInitTypeDef结构的指针，
  *                                该结构包含FSMC PCCARD Back的配置信息。
  * 
  * 返回值: 无
  */
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct) {
    uint32_t tmppcr4 = 0, tmppmem4 = 0, tmppatt4 = 0, tmppio4 = 0;

    /* 检查参数 */
    assert_param(IS_FSMC_WAIT_FEATURE(FSMC_PCCARDInitStruct->FSMC_Waitfeature));
    assert_param(IS_FSMC_TCLR_TIME(FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime));
    assert_param(IS_FSMC_TAR_TIME(FSMC_PCCARDInitStruct->FSMC_TARSetupTime));

    assert_param(IS_FSMC_SETUP_TIME(FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime));
    assert_param(IS_FSMC_WAIT_TIME(FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime));
    assert_param(IS_FSMC_HOLD_TIME(FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime));
    assert_param(IS_FSMC_HIZ_TIME(FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime));

    assert_param(IS_FSMC_SETUP_TIME(FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime));
    assert_param(IS_FSMC_WAIT_TIME(FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime));
    assert_param(IS_FSMC_HOLD_TIME(FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime));
    assert_param(IS_FSMC_HIZ_TIME(FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime));
    assert_param(IS_FSMC_SETUP_TIME(FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime));
    assert_param(IS_FSMC_WAIT_TIME(FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime));
    assert_param(IS_FSMC_HOLD_TIME(FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime));
    assert_param(IS_FSMC_HIZ_TIME(FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime));

    /* Get PCCARD control寄存器值 */
    tmppcr4 = FSMC_Bank4->PCR4;

    /* 清除 TAR, TCLR, PWAITEN and PWID 位 */
    tmppcr4 &= ((uint32_t)~(FSMC_PCR4_TAR  | FSMC_PCR4_TCLR | FSMC_PCR4_PWAITEN | \
                            FSMC_PCR4_PWID));

    /* 设置根据FSMC_PCCARInitStruct参数的PCR4寄存器值 */
    tmppcr4 |= (uint32_t)FSMC_PCCARDInitStruct->FSMC_Waitfeature |
               FSMC_MemoryDataWidth_16b |
               (FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime << 9) |
               (FSMC_PCCARDInitStruct->FSMC_TARSetupTime << 13);

    FSMC_Bank4->PCR4 = tmppcr4;

    /* 获取PCCARD公共空间正时寄存器值 */
    tmppmem4 = FSMC_Bank4->PMEM4;

    /* 清除 MEMSETx, MEMWAITx, MEMHOLDx and MEMHIZx 位 */
    tmppmem4 &= ((uint32_t)~(FSMC_PMEM4_MEMSET4  | FSMC_PMEM4_MEMWAIT4 | FSMC_PMEM4_MEMHOLD4 | \
                             FSMC_PMEM4_MEMHIZ4));

    /* 根据FSMC_CommonSpaceTimingStructure参数设置PMEM4寄存器值 */
    tmppmem4 |= (uint32_t)FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime |
                (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
                (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
                (FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime << 24);

    FSMC_Bank4->PMEM4 = tmppmem4;

    /* 获取PCCARD正时参数 */
    tmppatt4 = FSMC_Bank4->PATT4;

    /* 清除 ATTSETx, ATTWAITx, ATTHOLDx and ATTHIZx 位 */
    tmppatt4 &= ((uint32_t)~(FSMC_PATT4_ATTSET4  | FSMC_PATT4_ATTWAIT4 | FSMC_PATT4_ATTHOLD4 | \
                             FSMC_PATT4_ATTHIZ4));

    /* 根据FSMC_AttributeSpaceTimingStructure参数设置PATT4寄存器值 */
    tmppatt4 |= (uint32_t)FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime |
                (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
                (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
                (FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime << 24);

    FSMC_Bank4->PATT4 = tmppatt4;

    /* Get FSMC_PCCARD device 定时参数 */
    tmppio4 = FSMC_Bank4->PIO4;

    /* 清除 IOSET4, IOWAIT4, IOHOLD4 and IOHIZ4 位 */
    tmppio4 &= ((uint32_t)~(FSMC_PIO4_IOSET4  | FSMC_PIO4_IOWAIT4 | FSMC_PIO4_IOHOLD4 | \
                            FSMC_PIO4_IOHIZ4));

    /* 根据FSMC_IOSpaceTimingStructure参数设置PIO4寄存器值 */
    tmppio4 |= (uint32_t)FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime |
               (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime << 8) |
               (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime << 16) |
               (FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime << 24);

    FSMC_Bank4->PIO4 = tmppio4;
}

/**
  * 简介:  用每个FSMC_PCCARDInitStruct成员的默认值填充该成员。
  * 
  * 参数:  FSMC_PCCARDInitStruct: 指向FSMC_PCCARDInitTypeDef结构的指针，将被初始化。
  * 
  * 返回值: 无
  */
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct) {
    /* 重置PCCARD Init结构参数值 */
    FSMC_PCCARDInitStruct->FSMC_Waitfeature = FSMC_Waitfeature_Disable;
    FSMC_PCCARDInitStruct->FSMC_TCLRSetupTime = 0x0;
    FSMC_PCCARDInitStruct->FSMC_TARSetupTime = 0x0;
    FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_CommonSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_AttributeSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_SetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_WaitSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HoldSetupTime = 0xFC;
    FSMC_PCCARDInitStruct->FSMC_IOSpaceTimingStruct->FSMC_HiZSetupTime = 0xFC;
}

/**
  * 简介:  启用或禁用 PCCARD Memory Bank.
  * 
  * 参数:  NewState: PCCARD内存库的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void FSMC_PCCARDCmd(FunctionalState NewState) {
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用通过在PCR4中设置PBKEN位，PCCARD Bank寄存器 */
        FSMC_Bank4->PCR4 |= PCR_PBKEN_SET;
    } else {
        /* 禁用通过清除PCR4中的PBKEN位，PCCARD Bank寄存器 */
        FSMC_Bank4->PCR4 &= PCR_PBKEN_RESET;
    }
}

/** @defgroup FSMC_Group4  中断和标记管理函数
 *  简介    中断和标记管理函数
 *
@verbatim
 ===============================================================================
             ##### 中断和标记管理函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 FSMC 中断.
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND:   FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND:   FSMC Bank3 NAND
  *            @arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
  * 
  * 参数:  FSMC_IT: 指定要启用或禁用的FSMC中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg FSMC_IT_RisingEdge:  上升沿检测中断。
  *            @arg FSMC_IT_Level:       水平边缘检测中断。
  *            @arg FSMC_IT_FallingEdge: 下降沿检测中断。
  * 
  * 参数:  NewState: 指定的FSMC中断的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void FSMC_ITConfig(uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState) {
    assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
    assert_param(IS_FSMC_IT(FSMC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 FSMC_Bank2 中断 */
        if(FSMC_Bank == FSMC_Bank2_NAND) {
            FSMC_Bank2->SR2 |= FSMC_IT;
        }
        /* 启用被选定的 FSMC_Bank3 中断 */
        else if (FSMC_Bank == FSMC_Bank3_NAND) {
            FSMC_Bank3->SR3 |= FSMC_IT;
        }
        /* 启用被选定的 FSMC_Bank4 中断 */
        else {
            FSMC_Bank4->SR4 |= FSMC_IT;
        }
    } else {
        /* 禁用被选中的 FSMC_Bank2 中断 */
        if(FSMC_Bank == FSMC_Bank2_NAND) {

            FSMC_Bank2->SR2 &= (uint32_t)~FSMC_IT;
        }
        /* 禁用被选中的 FSMC_Bank3 中断 */
        else if (FSMC_Bank == FSMC_Bank3_NAND) {
            FSMC_Bank3->SR3 &= (uint32_t)~FSMC_IT;
        }
        /* 禁用被选中的 FSMC_Bank4 中断 */
        else {
            FSMC_Bank4->SR4 &= (uint32_t)~FSMC_IT;
        }
    }
}

/**
  * 简介:  检查是否设置了指定的 FSMC 标志。
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND:    FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND:    FSMC Bank3 NAND
  *            @arg FSMC_Bank4_PCCARD:  FSMC Bank4 PCCARD
  * 
  * 参数:  FSMC_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg FSMC_FLAG_RisingEdge:  上升沿检测标志。
  *            @arg FSMC_FLAG_Level:       水平检测标志。
  *            @arg FSMC_FLAG_FallingEdge: 下降边缘检测标志.
  *            @arg FSMC_FLAG_FEMPT:       Fifo 空标志
  * 
  * 返回值: 新状态-> FSMC_FLAG (SET or RESET).
  */
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tmpsr = 0x00000000;

    /* 检查参数 */
    assert_param(IS_FSMC_GETFLAG_BANK(FSMC_Bank));
    assert_param(IS_FSMC_GET_FLAG(FSMC_FLAG));

    if(FSMC_Bank == FSMC_Bank2_NAND) {
        tmpsr = FSMC_Bank2->SR2;
    } else if(FSMC_Bank == FSMC_Bank3_NAND) {
        tmpsr = FSMC_Bank3->SR3;
    }
    /* FSMC_Bank4_PCCARD*/
    else {
        tmpsr = FSMC_Bank4->SR4;
    }

    /* 获取flag 状态 */
    if ((tmpsr & FSMC_FLAG) != (uint16_t)RESET ) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    /* 返回标志状态 */
    return bitstatus;
}

/**
  * 简介:  清除 FSMC 的挂起标志。
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND: FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND: FSMC Bank3 NAND
  *            @arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
  * 
  * 参数:  FSMC_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *            @arg FSMC_FLAG_RisingEdge: 上升沿检测标志。
  *            @arg FSMC_FLAG_Level: 水平检测标志。
  *            @arg FSMC_FLAG_FallingEdge: 下降边缘检测标志.
  * 
  * 返回值: 无
  */
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG) {
    /* 检查参数 */
    assert_param(IS_FSMC_GETFLAG_BANK(FSMC_Bank));
    assert_param(IS_FSMC_CLEAR_FLAG(FSMC_FLAG)) ;

    if(FSMC_Bank == FSMC_Bank2_NAND) {
        FSMC_Bank2->SR2 &= ~FSMC_FLAG;
    } else if(FSMC_Bank == FSMC_Bank3_NAND) {
        FSMC_Bank3->SR3 &= ~FSMC_FLAG;
    }
    /* FSMC_Bank4_PCCARD*/
    else {
        FSMC_Bank4->SR4 &= ~FSMC_FLAG;
    }
}

/**
  * 简介:  检查指定的 FSMC 中断是否发生。
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND: FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND: FSMC Bank3 NAND
  *            @arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
  * 
  * 参数:  FSMC_IT: 指定要检查的FSMC中断源。
  *          此参数可以是以下值之一:
  *            @arg FSMC_IT_RisingEdge: 上升沿检测中断。
  *            @arg FSMC_IT_Level: 水平边缘检测中断。
  *            @arg FSMC_IT_FallingEdge: 下降沿检测中断。
  * 
  * 返回值: FSMC_IT的新状态(SET或RESET)。
  */
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t tmpsr = 0x0, itstatus = 0x0, itenable = 0x0;

    /* 检查参数 */
    assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
    assert_param(IS_FSMC_GET_IT(FSMC_IT));

    if(FSMC_Bank == FSMC_Bank2_NAND) {
        tmpsr = FSMC_Bank2->SR2;
    } else if(FSMC_Bank == FSMC_Bank3_NAND) {
        tmpsr = FSMC_Bank3->SR3;
    }
    /* FSMC_Bank4_PCCARD*/
    else {
        tmpsr = FSMC_Bank4->SR4;
    }

    itstatus = tmpsr & FSMC_IT;

    itenable = tmpsr & (FSMC_IT >> 3);

    if ((itstatus != (uint32_t)RESET)  && (itenable != (uint32_t)RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 FSMC 的中断挂起位。
  * 
  * 参数:  FSMC_Bank: 指定要使用的FSMC Back
  *          此参数可以是以下值之一:
  *            @arg FSMC_Bank2_NAND: FSMC Bank2 NAND
  *            @arg FSMC_Bank3_NAND: FSMC Bank3 NAND
  *            @arg FSMC_Bank4_PCCARD: FSMC Bank4 PCCARD
  * 
  * 参数:  FSMC_IT: 指定要清除的中断等待位。
  *          此参数可以是以下值的任意组合:
  *            @arg FSMC_IT_RisingEdge: 上升沿检测中断。
  *            @arg FSMC_IT_Level: 水平边缘检测中断。
  *            @arg FSMC_IT_FallingEdge: 下降沿检测中断。
  * 
  * 返回值: 无
  */
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT) {
    /* 检查参数 */
    assert_param(IS_FSMC_IT_BANK(FSMC_Bank));
    assert_param(IS_FSMC_IT(FSMC_IT));

    if(FSMC_Bank == FSMC_Bank2_NAND) {
        FSMC_Bank2->SR2 &= ~(FSMC_IT >> 3);
    } else if(FSMC_Bank == FSMC_Bank3_NAND) {
        FSMC_Bank3->SR3 &= ~(FSMC_IT >> 3);
    }
    /* FSMC_Bank4_PCCARD*/
    else {
        FSMC_Bank4->SR4 &= ~(FSMC_IT >> 3);
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
