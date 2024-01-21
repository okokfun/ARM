/**
  ******************************************************************************
  * 文件:    stm32f4xx_qspi.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供了固件功能来管理以下内容串行外围接口(QSPI)的功能:
  *           + 初始化和配置
  *           + 间接数据读/写功能
  *           + 内存映射模式的数据读取功能
  *           + 自动轮询功能
  *           + DMA传输管理
  *           + 中断和标志管理
  *
  *  @verbatim
  *
 ===============================================================================
                       ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..]
        (#) 使用RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_QSPI,ENABLE)函数启用外围时钟。

        (#) 启用CLK、BK1_IO0、BK1_IO1、BK1_IO2、BK1_IO3、BK1_NCS、BK2_IO0。BK2_IO1,
            BK2_IO2, BK2_IO3 和 BK2_NCS 的 GPIO 时钟，使用 RCC_AHB1PeriphClockCmd()函数。

        (#) 外设设备替代函数。
           (++) 将引脚连接到所需的外设设备的替代函数(AF)。使用GPIO_PinAFConfig()
                函数将引脚连接到所需外设的复用功能(AF)。

           (++) 通过配置所需引脚的复用功能。
                GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF。

           (++) 通过以下方法选择类型、上拉/下拉和输出速度 GPIO_PuPd、GPIO_OType 和 GPIO_Speed
                成员选择类型、上拉/下拉和输出速度。

           (++) 调用 GPIO_Init() 函数。

        (#) 使用 QSPI_Init() 函数对Flash大小、CS High Time、Sample Shift、Prescaler、Clock Mode进行编程。
            值，使用 QSPI_Init() 函数。

        (#) 使用 QSPI_Cmd() 函数启用QSPI。

        (#) 使用 QSPI_SetDataLength() 函数设置QSPI数据长度。

        (#) 使用 QSPI_SetFIFOThreshold() 函数配置 FIFO 阈值，选择在哪个阈值上产生FTF事件。

        (#) 如果需要使用中断模式，使用函数 QSPI_ITConfig() 启用 NVIC 和相应的中断。

        (#) 当使用DMA模式时
           (++) 使用 DMA_Init() 函数配置 DMA。
           
           (++) 使用 SPI_I2S_DMACmd() 函数激活需要的通道请求。

        (#) 使用 QSPI_DMACmd() 函数启用 SPI。

        (#) 当使用 DMA 模式时，使用 DMA_Cmd() 函数启用 DMA。

    @endverbatim
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
#include "stm32f4xx_qspi.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup QSPI
  * 简介: QSPI 驱动模块
  * @{
  */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define QSPI_CR_CLEAR_MASK                           0x00FFFFCF
#define QSPI_DCR_CLEAR_MASK                          0xFFE0F7FE
#define QSPI_CCR_CLEAR_MASK                          0x90800000
#define QSPI_PIR_CLEAR_MASK                          0xFFFF0000
#define QSPI_LPTR_CLEAR_MASK                         0xFFFF0000
#define QSPI_CCR_CLEAR_INSTRUCTION_MASK              0xFFFFFF00
#define QSPI_CCR_CLEAR_DCY_MASK                      0xFFC3FFFF
#define QSPI_CR_CLEAR_FIFOTHRESHOLD_MASK             0xFFFFF0FF
#define QSPI_CR_INTERRUPT_MASK                       0x001F0000
#define QSPI_SR_INTERRUPT_MASK                       0x0000001F
#define QSPI_FSR_INTERRUPT_MASK                      0x0000001B
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/


/* 初始化和配置功能 *********************************/

/** @defgroup <PPP>_Private_Functions
  * @{
  */

/** @defgroup <PPP>_Group1 Function Group1 Name
 *  简介   功能组1名称描述(从头文件复制)
 *
@verbatim
 ===============================================================================
     ##### < Function group1 name (copied from the header file)
 Note: do not use "Peripheral" or "PPP" word in the function group name >  #####
 ===============================================================================

       [..] < 可选的:
              在这里添加关于这组功能所涵盖的IP功能的最重要信息。

              对于系统IP，本节包含如何使用本组API。
            >

@endverbatim
  * @{
  */

/**
  * 简介:  将 QSPI 外设寄存器取消初始化为其默认复位值。
  * 参数:  无
  * 返回值: 无
  */
void QSPI_DeInit(void) {
    /* 使能QSPI 复位状态 */
    RCC_AHB3PeriphResetCmd(RCC_AHB3Periph_QSPI, ENABLE);
    /* 释放QSPI from 复位状态 */
    RCC_AHB3PeriphResetCmd(RCC_AHB3Periph_QSPI, DISABLE);
}

/**
  * 简介:  用其默认值填充每个 QSPI_InitStruct 成员。
  * 参数:  QSPI_InitStruct: 指向QSPI_InitTypeDef结构的指针，将被初始化。
  * 返回值: 无
  */
void QSPI_StructInit(QSPI_InitTypeDef* QSPI_InitStruct) {
    /*--------- 重置QSPI初始化结构参数默认值 ------------*/
    /* 初始化 QSPI_SShift 成员 */
    QSPI_InitStruct->QSPI_SShift = QSPI_SShift_NoShift ;
    /* 初始化 QSPI_Prescaler 成员 */
    QSPI_InitStruct->QSPI_Prescaler = 0 ;
    /* 初始化 QSPI_CKMode 成员 */
    QSPI_InitStruct->QSPI_CKMode = QSPI_CKMode_Mode0 ;
    /* 初始化 QSPI_CSHTime 成员 */
    QSPI_InitStruct->QSPI_CSHTime = QSPI_CSHTime_1Cycle ;
    /* 初始化 QSPI_FSize 成员 */
    QSPI_InitStruct->QSPI_FSize = 0 ;
    /* 初始化 QSPI_FSelect 成员 */
    QSPI_InitStruct->QSPI_FSelect = QSPI_FSelect_1 ;
    /* 初始化 QSPI_DFlash 成员 */
    QSPI_InitStruct->QSPI_DFlash = QSPI_DFlash_Disable ;
}

/**
  * 简介:  用其默认值填充每个 QSPI_ComConfig_InitStruct 成员。
  * 参数:  QSPI_ComConfig_InitStruct: 指向QSPI_Comfig_InitTypeDef结构的指针，将被初始化。
  * 返回值: 无
  */
void QSPI_ComConfig_StructInit(QSPI_ComConfig_InitTypeDef* QSPI_ComConfig_InitStruct) {
    /*--------- 重置QSPI ComConfig初始化结构参数的默认值 ------------*/

    /* 设置QSPI通信配置结构参数的默认值 */
    /* 初始化 QSPI_ComConfig_DDRMode 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_DDRMode = QSPI_ComConfig_DDRMode_Disable ;
    /* 初始化 QSPI_ComConfig_DHHC 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_DHHC = QSPI_ComConfig_DHHC_Disable ;
    /* 初始化 QSPI_ComConfig_SIOOMode 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_SIOOMode = QSPI_ComConfig_SIOOMode_Disable ;
    /* 初始化 QSPI_ComConfig_FMode 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_FMode = QSPI_ComConfig_FMode_Indirect_Write ;
    /* 初始化 QSPI_ComConfig_DMode 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_DMode = QSPI_ComConfig_DMode_NoData ;
    /* 初始化 QSPI_ComConfig_DummyCycles 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_DummyCycles = 0 ;
    /* 初始化 QSPI_ComConfig_ABSize 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_ABSize = QSPI_ComConfig_ABSize_8bit ;
    /* 初始化 QSPI_ComConfig_ABMode 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_ABMode = QSPI_ComConfig_ABMode_NoAlternateByte ;
    /* 初始化 QSPI_ComConfig_ADSize 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_ADSize = QSPI_ComConfig_ADSize_8bit ;
    /* 初始化 QSPI_ComConfig_ADMode 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_ADMode = QSPI_ComConfig_ADMode_NoAddress ;
    /* 初始化 QSPI_ComConfig_IMode 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_IMode = QSPI_ComConfig_IMode_NoInstruction ;
    /* 初始化 QSPI_ComConfig_Ins 成员 */
    QSPI_ComConfig_InitStruct->QSPI_ComConfig_Ins = 0 ;
}

/**
  * 简介:  根据 QSPI_InitStruct 中指定的参数初始化 QSPI 外设。
  * 参数:  QSPI_InitStruct: 指向QSPI_InitTypeDef结构的指针，该结构包含指定QSPI外设的配置信息。
  * 返回值: 无
  */
void QSPI_Init(QSPI_InitTypeDef* QSPI_InitStruct) {
    uint32_t tmpreg = 0;

    /* 检查 QSPI 参数 */
    assert_param(IS_QSPI_SSHIFT(QSPI_InitStruct->QSPI_SShift));
    assert_param(IS_QSPI_PRESCALER(QSPI_InitStruct->QSPI_Prescaler));
    assert_param(IS_QSPI_CKMODE(QSPI_InitStruct->QSPI_CKMode));
    assert_param(IS_QSPI_CSHTIME(QSPI_InitStruct->QSPI_CSHTime));
    assert_param(IS_QSPI_FSIZE(QSPI_InitStruct->QSPI_FSize));
    assert_param(IS_QSPI_FSEL(QSPI_InitStruct->QSPI_FSelect));
    assert_param(IS_QSPI_DFM(QSPI_InitStruct->QSPI_DFlash));

    /*------------------------ QSPI CR 配置 ------------------------*/
    /* 获取QUADSPI CR1 值 */
    tmpreg = QUADSPI->CR;
    /* 清除 PRESCALER and SSHIFT 位 */
    tmpreg &= QSPI_CR_CLEAR_MASK;
    /* Configure QUADSPI: Prescaler and Sample Shift */
    tmpreg |= (uint32_t)(((QSPI_InitStruct->QSPI_Prescaler) << 24)
                         | (QSPI_InitStruct->QSPI_SShift)
                         | (QSPI_InitStruct->QSPI_FSelect)
                         | (QSPI_InitStruct->QSPI_DFlash));
    /* 写入QUADSPI CR */
    QUADSPI->CR = tmpreg;

    /*------------------------ QUADSPI DCR 配置 ------------------------*/
    /* 获取QUADSPI DCR 值 */
    tmpreg = QUADSPI->DCR;
    /* 清除 FSIZE, CSHT and CKMODE 位 */
    tmpreg &= QSPI_DCR_CLEAR_MASK;
    /* Configure QSPI: Flash Size, Chip Select High Time and Clock Mode */
    tmpreg |= (uint32_t)(((QSPI_InitStruct->QSPI_FSize) << 16)
                         | (QSPI_InitStruct->QSPI_CSHTime)
                         | (QSPI_InitStruct->QSPI_CKMode));
    /* 写入QSPI DCR */
    QUADSPI->DCR = tmpreg;
}

/**
  * 简介:  根据 QSPI_ComConfig_InitStruct 中指定的参数初始化 QSPI CCR。
  * 参数:  QSPI_ComConfig_InitStruct: 指向QSPI_ComConfig_InitTypeDef结构的指针，该结构包含有关QSPI外设设备的通信配置信息。
  * 返回值: 无
  */
void QSPI_ComConfig_Init(QSPI_ComConfig_InitTypeDef* QSPI_ComConfig_InitStruct) {
    uint32_t tmpreg = 0;

    /* 检查 QSPI 通信控制参数 */
    assert_param(IS_QSPI_FMODE       (QSPI_ComConfig_InitStruct->QSPI_ComConfig_FMode));
    assert_param(IS_QSPI_SIOOMODE    (QSPI_ComConfig_InitStruct->QSPI_ComConfig_SIOOMode));
    assert_param(IS_QSPI_DMODE       (QSPI_ComConfig_InitStruct->QSPI_ComConfig_DMode));
    assert_param(IS_QSPI_DCY         (QSPI_ComConfig_InitStruct->QSPI_ComConfig_DummyCycles));
    assert_param(IS_QSPI_ABSIZE      (QSPI_ComConfig_InitStruct->QSPI_ComConfig_ABSize));
    assert_param(IS_QSPI_ABMODE      (QSPI_ComConfig_InitStruct->QSPI_ComConfig_ABMode));
    assert_param(IS_QSPI_ADSIZE      (QSPI_ComConfig_InitStruct->QSPI_ComConfig_ADSize));
    assert_param(IS_QSPI_ADMODE      (QSPI_ComConfig_InitStruct->QSPI_ComConfig_ADMode));
    assert_param(IS_QSPI_IMODE       (QSPI_ComConfig_InitStruct->QSPI_ComConfig_IMode));
    assert_param(IS_QSPI_INSTRUCTION (QSPI_ComConfig_InitStruct->QSPI_ComConfig_Ins));
    assert_param(IS_QSPI_DDRMODE     (QSPI_ComConfig_InitStruct->QSPI_ComConfig_DDRMode));
    assert_param(IS_QSPI_DHHC        (QSPI_ComConfig_InitStruct->QSPI_ComConfig_DHHC));

    /*------------------------ QUADSPI CCR 配置 ------------------------*/
    /* 获取 QUADSPI CCR 值 */
    tmpreg = QUADSPI->CCR;
    /* 清除 FMODE Mode 位 */
    tmpreg &= QSPI_CCR_CLEAR_MASK;
    /* 配置 QUADSPI: CCR 配置*/
    tmpreg |=  (uint32_t)( (QSPI_ComConfig_InitStruct->QSPI_ComConfig_FMode)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_DDRMode)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_DHHC)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_SIOOMode)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_DMode)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_ABSize)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_ABMode)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_ADSize)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_ADMode)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_IMode)
                           | (QSPI_ComConfig_InitStruct->QSPI_ComConfig_Ins)
                           | ((QSPI_ComConfig_InitStruct->QSPI_ComConfig_DummyCycles) << 18));
    /* 写入QUADSPI DCR */
    QUADSPI->CCR = tmpreg;
}

/**
  * 简介:  使能或失能 QSPI 外设.
  * 参数:  NewState: 新状态-> QSPI 外设.
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void QSPI_Cmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能QSPI 外设 */
        QUADSPI->CR |= QUADSPI_CR_EN;
    } else {
        /* 禁用 QSPI 外设 */
        QUADSPI->CR &= ~ QUADSPI_CR_EN;
    }
}

/**
  * 简介:  配置 QSPI 自动轮询模式。
  * 参数:  QSPI_Match: 要与被屏蔽的状态寄存器进行比较以获得匹配的值。
  *                    这个参数可以是0x00000000到0xFFFFFFFF之间的任何值。
  * 参数:  QSPI_Mask: 在轮询模式下，对收到的状态字节进行屏蔽。
  *                    这个参数可以是0x00000000到0xFFFFFFFF之间的任何值。
  * 参数:  QSPI_Match_Mode: 表示在自动轮询模式下应该使用哪种方法来确定 "匹配"。
  *        此参数可以是以下任意值。
  * 参数   QSPI_PMM_AND: AND 匹配模式--如果从闪存接收到的所有未屏蔽的位与匹配寄存
  *                     器中的相应位相匹配，则SMF被设置。匹配寄存器中的相应位，则SMF被设置。
  *         @arg QSPI_PMM_OR:OR 匹配模式--如果从闪存中收到的任何一个未被屏蔽的位与
  *                     匹配寄存器中的相应位相匹配，则SMF被设置。匹配寄存器中的相应位。
  * 注意: 这个功能只在自动轮询模式下使用。
  * 返回值: 无
  */
void QSPI_AutoPollingMode_Config(uint32_t QSPI_Match, uint32_t QSPI_Mask, uint32_t QSPI_Match_Mode) {
    /* 检查参数 */
    assert_param(IS_QSPI_PMM(QSPI_Match_Mode));

    if ((QUADSPI->SR & QUADSPI_SR_BUSY) == RESET)
        /* 设备不忙 */
    {
        /* 设置 Match 寄存器 */
        QUADSPI->PSMAR = QSPI_Match ;

        /* 设置 Mask 寄存器 */
        QUADSPI->PSMKR = QSPI_Mask ;

        /* 设置轮询匹配模式 */
        if(QSPI_Match_Mode)
            /* OR 匹配模式 */
        {
            /* 设置 PMM 位 */
            QUADSPI->CR |= QUADSPI_CR_PMM;
        } else
            /* AND 匹配模式 */
        {
            /* 重设 PMM 位 */
            QUADSPI->CR &= ~ QUADSPI_CR_PMM;
        }
    }
}

/**
  * 简介:  设置自动轮询阶段两次读取之间的 CLK 周期数。
  * 参数:  QSPI_Interval: 自动轮询阶段两次读取之间的时钟周期数。
  *          此参数可以是0x0000和0xFFFF之间的任何值
  * 注意:   此功能仅在自动轮询模式下使用
  * 返回值: 无
  */
void QSPI_AutoPollingMode_SetInterval(uint32_t QSPI_Interval) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_QSPI_PIR(QSPI_Interval));

    if ((QUADSPI->SR & QUADSPI_SR_BUSY) == RESET)
        /* 设备不忙 */
    {
        /* 读 PIR 寄存器 */
        tmpreg = QUADSPI->PIR ;
        /* 清除轮询间隔位 */
        tmpreg &= QSPI_PIR_CLEAR_MASK ;
        /* 设置 QSPI 轮询间隔位 */
        tmpreg |= QSPI_Interval;
        /* 写 PIR 寄存器 */
        QUADSPI->PIR = tmpreg;
    }
}

/**
  * 简介:  设置内存映射模式下的超时值
  * 参数:  QSPI_Timeout: 此字段指示FIFO满后QSPI等待多少CLK周期，
  *                      直到它引发nCS，使闪存处于低消耗状态。
  *         此参数可以是0x0000和0xFFFF之间的任何值
  * 注意:   此函数仅在内存映射模式中使用
  * 返回值: 无
  */
void QSPI_MemoryMappedMode_SetTimeout(uint32_t QSPI_Timeout) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_QSPI_TIMEOUT(QSPI_Timeout));

    if ((QUADSPI->SR & QUADSPI_SR_BUSY) == RESET)
        /* 设备不忙 */
    {
        /* 读 LPTR 寄存器 */
        tmpreg = QUADSPI->LPTR ;
        /* 清除 Timeout 位 */
        tmpreg &= QSPI_LPTR_CLEAR_MASK ;
        /* Set Timeout 位 */
        tmpreg |= QSPI_Timeout;
        /* 写 LPTR 寄存器 */
        QUADSPI->LPTR = tmpreg;
    }
}

/**
  * 简介:  设置地址的值
  * 参数:  QSPI_Address: 要发送到外部闪存的地址。
  *         此参数可以在0x00000000和0xFFFFFFFFFF之间具有任何值。
  * 注意:   此功能仅在间接模式下使用
  * 返回值: 无
  */
void QSPI_SetAddress(uint32_t QSPI_Address) {
    if((QUADSPI->SR & QUADSPI_SR_BUSY) == RESET)
        /* 设备不忙 */
    {
        /* 写 AR 寄存器 */
        QUADSPI->AR = QSPI_Address;
    }
}

/**
  * 简介:  设置备用字节的值
  * 参数:  QSPI_AlternateByte: 可选数据发送到地址后的外部QSPI设备。
  *         此参数可以在0x00000000和0xFFFFFFFFFF之间具有任何值。
  * 注意:   此功能仅在间接模式下使用
  * 返回值: 无
  */
void QSPI_SetAlternateByte(uint32_t QSPI_AlternateByte) {
    if((QUADSPI->SR & QUADSPI_SR_BUSY) == RESET)
        /* 设备不忙 */
    {
        /* 写 ABR 寄存器 */
        QUADSPI->ABR = QSPI_AlternateByte;
    }
}

/**
  * 简介:  设置 FIFO 阈值
  * 参数:  QSPI_FIFOThres: 在间接模式下，定义FIFO中的阈值字节数，
  *                        这将导致设置FIFO阈值标志FTF。
  *         此参数可以是0x00和0x0F之间的任何值
  * 返回值: 无
  */
void QSPI_SetFIFOThreshold(uint32_t QSPI_FIFOThreshold) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_QSPI_FIFOTHRESHOLD(QSPI_FIFOThreshold));

    /* 读 CR 寄存器 */
    tmpreg = QUADSPI->CR ;
    /* 清除 FIFO 阀位 */
    tmpreg &= QSPI_CR_CLEAR_FIFOTHRESHOLD_MASK ;
    /* 设置 FIFO 阀位 */
    tmpreg |= (QSPI_FIFOThreshold << 8);
    /* 写 CR 寄存器 */
    QUADSPI->CR = tmpreg;
}

/**
  * 简介:  设置要传输的字节数
  * 参数:  QSPI_DataLength: 在间接和状态轮询模式下要检索的数据数(值+1)。
  *                         状态轮询模式应使用不大于3(表示4字节)的值。
  *         间接模式中的所有1表示未定义的长度，其中QSPI将持续到内存结束，如FSIZE所定义
  *         此参数可以在0x00000000和0xFFFFFFFFFF之间具有任何值。
  *             0x0000_0000:要传输1个字节
  *             0x0000_0001:要传输2个字节
  *             0x0000_0002:要传输3个字节
  *             0x0000_0003:要传输4个字节
  *             ...
  *             0xFFFF_FFFD:4294967294(4G-2)字节将被传输
  *             0xFFFF_FFFE:4294967295(4G-1)字节将被传输
  *             0xFFFF_FFFF:未定义的长度——闪存结束前的所有字节(如定义
  *             由FSIZE)转让
  * 注意:   此函数不用于内存映射模式。
  * 返回值: 无
  */
void QSPI_SetDataLength(uint32_t QSPI_DataLength) {
    if ((QUADSPI->SR & QUADSPI_SR_BUSY) == RESET)
        /* 设备不忙 */
    {
        /* 写 DLR 寄存器 */
        QUADSPI->DLR = QSPI_DataLength;
    }
}

/**
  * 简介:  启用或禁用超时计数器。
  * 参数:  NewState: 新状态-> 超时计数器。
  *          此参数可以是: ENABLE或DISABLE。
  * 注意:   此函数仅在内存映射模式中使用.
  * 返回值: 无
  */
void QSPI_TimeoutCounterCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if ((QUADSPI->SR & QUADSPI_SR_BUSY) == RESET)
        /* 设备不忙 */
    {
        if (NewState != DISABLE) {
            /* 使能超时计数器 */
            QUADSPI->CR |= QUADSPI_CR_TCEN;
        } else {
            /* 禁用超时计数器 */
            QUADSPI->CR &= ~ QUADSPI_CR_TCEN;
        }
    }
}

/**
  * 简介:  发生匹配时启用或禁用自动轮询模式停止。
  * 参数:  NewState: 新状态-> 自动轮询模式停止。
  *          此参数可以是: ENABLE或DISABLE。
  * 注意:   此功能仅在自动轮询模式下使用.
  * 返回值: 无
  */
void QSPI_AutoPollingModeStopCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if ((QUADSPI->SR & QUADSPI_SR_BUSY) == RESET)
        /* 设备不忙 */
    {
        if (NewState != DISABLE) {
            /* 使能自动轮询模式停止 */
            QUADSPI->CR |= QUADSPI_CR_APMS;
        } else {
            /* 禁用自动轮询模式停止 */
            QUADSPI->CR &= ~ QUADSPI_CR_APMS;
        }
    }
}

/**
  * 简介:  中止正在进行的命令序列。
  * 参数:  无
  * 返回值: 无
  */
void QSPI_AbortRequest(void) {
    /* 启用 ABORT request bit in CR */
    QUADSPI->CR |= QUADSPI_CR_ABORT;
}

/* 数据传输功能 ***************************************************/

/**
  * 简介:  通过 QSPI 外设传输 8 位数据。
  * 参数:  Data: 要传输的数据。
  * 返回值: 无
  */
void QSPI_SendData8(uint8_t Data) {
    uint32_t quadspibase = 0;

    quadspibase = (uint32_t)QUADSPI;
    quadspibase += 0x20;

    *(__IO uint8_t *) quadspibase = Data;
}

/**
  * 简介:  通过 QSPI 外设传输 16 位数据。
  * 参数:  Data: 要传输的数据。
  * 返回值: 无
  */
void QSPI_SendData16(uint16_t Data) {
    uint32_t quadspibase = 0;

    quadspibase = (uint32_t)QUADSPI;
    quadspibase += 0x20;

    *(__IO uint16_t *) quadspibase = Data;
}

/**
  * 简介:  通过 QSPI 外设传输 32 位数据。
  * 参数:  Data: 要传输的数据。
  * 返回值: 无
  */
void QSPI_SendData32(uint32_t Data) {
    QUADSPI->DR = Data;
}

/**
  * 简介:  返回 QSPI 外设最近接收到的 8 位数据。
  * 返回值: The value of 接收的数据。
  */
uint8_t QSPI_ReceiveData8(void) {
    uint32_t quadspibase = 0;

    quadspibase = (uint32_t)QUADSPI;
    quadspibase += 0x20;

    return *(__IO uint8_t *) quadspibase;
}

/**
  * 简介:  返回 QSPI 外设最近接收到的 16 位数据。
  * 返回值: The value of 接收的数据。
  */
uint16_t QSPI_ReceiveData16(void) {
    uint32_t quadspibase = 0;

    quadspibase = (uint32_t)QUADSPI;
    quadspibase += 0x20;

    return *(__IO uint16_t *) quadspibase;
}

/**
  * 简介:  返回 QSPI 外设最近接收到的 32 位数据。
  * 返回值: The value of 接收的数据。
  */
uint32_t QSPI_ReceiveData32(void) {
    return QUADSPI->DR;
}

/* DMA传输管理 functions *****************************************/

/**
  * 简介:  启用或禁用间接模式的 DMA。
  * 参数:  NewState: 新状态-> Timeout Counter.
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void QSPI_DMACmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能DMA */
        QUADSPI->CR |= QUADSPI_CR_DMAEN;
    } else {
        /* Disable DMA */
        QUADSPI->CR &= ~ QUADSPI_CR_DMAEN;
    }
}

/* 中断和标记管理功能 **********************************/

/**
  * 简介:  启用或禁用指定的 QSPI 中断.
  * 参数:  QSPI_IT: 指定要启用或禁用的QSPI中断源。
  *          此参数可以是以下值之一:
  *                @arg QSPI_IT_TO:超时中断
  *                @arg QSPI_IT_SM:状态匹配中断
  *                @arg QSPI_IT_FT:FIFO阈值
  *                @arg QSPI_IT_TC:传输完成
  *                @arg QSPI_IT_TE:传输错误
  * 参数:  NewState: 新状态-> 指定的QSPI中断。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void QSPI_ITConfig(uint32_t QSPI_IT, FunctionalState NewState) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_QSPI_IT(QSPI_IT));

    /* 读 CR 寄存器 */
    tmpreg = QUADSPI->CR ;

    if(NewState != DISABLE) {
        /* 启用被选择的 QSPI 中断 */
        tmpreg |= (uint32_t)(QSPI_IT & QSPI_CR_INTERRUPT_MASK);
    } else {
        /* 禁用被选择的 QSPI 中断 */
        tmpreg &= ~(uint32_t)(QSPI_IT & QSPI_CR_INTERRUPT_MASK);
    }

    /* 写 CR 寄存器 */
    QUADSPI->CR = tmpreg ;
}

/**
  * 简介:  返回当前 QSPI FIFO 填充级别。
  * 返回值: FIFO中保存的有效字节数。
  *         0x00 : FIFO 是空的
  *         0x1F : FIFO 是满的
  */
uint32_t QSPI_GetFIFOLevel(void) {
    /* 获取QSPI FIFO level 位 */
    return ((QUADSPI->SR & QUADSPI_SR_FLEVEL) >> 8);
}

/**
  * 简介:  返回 QSPI 功能模式。
  * 参数:  无
  * 返回值: QSPI功能模式。返回值可以是以下值之一:
  *              - 0x00000000: QSPI_FMode_Indirect_Write
  *              - 0x04000000: QSPI_FMode_Indirect_Read
  *              - 0x08000000: QSPI_FMode_AutoPolling
  *              - 0x0C000000: QSPI_FMode_MemoryMapped
  */
uint32_t QSPI_GetFMode(void) {
    /* 返回QSPI_FMode */
    return  (QUADSPI->CCR & QUADSPI_CCR_FMODE);
}

/**
  * 简介:  检查是否设置了指定的 QSPI 标志。
  * 参数:  QSPI_FLAG: 指定要检查的 QSPI 标志。
  *          此参数可以是以下值之一:
  *          @arg QSPI_FLAG_TO: 超时中断标志
  *          @arg QSPI_FLAG_SM: 状态匹配中断标志
  *          @arg QSPI_FLAG_FT: FIFO阈值标志
  *          @arg QSPI_FLAG_TC: 传输完成标志
  *          @arg QSPI_FLAG_TE: 传输错误标志
  *          @arg QSPI_FLAG_BUSY: 忙标志
  * 返回值: 新状态-> QSPI_FLAG (SET or RESET).
  */
FlagStatus QSPI_GetFlagStatus(uint32_t QSPI_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_QSPI_GET_FLAG(QSPI_FLAG));

    /* 检查指定的 QSPI 标志的状态 */
    if((QUADSPI->SR & QSPI_FLAG) != RESET) {
        /* QSPI_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* QSPI_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回QSPI_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 QSPI 标志。
  * 参数:  QSPI_FLAG: 指定要清除的QSPI标志。
  *          此参数可以是以下值之一:
  *          @arg QSPI_FLAG_TO:超时中断标志
  *          @arg QSPI_FLAG_SM:状态匹配中断标志
  *          @arg QSPI_FLAG_TC:传输完成标志
  *          @arg QSPI_FLAG_TE:传输错误标志
  * 返回值: 无
  */
void QSPI_ClearFlag(uint32_t QSPI_FLAG) {
    /* 检查参数 */
    assert_param(IS_QSPI_CLEAR_FLAG(QSPI_FLAG));

    /* 清除选定的 QSPI 标志 */
    QUADSPI->FCR = QSPI_FLAG;
}

/**
  * 简介:  检查指定的 QSPI 中断是否发生。
  * 参数:  QSPI_IT: 指定要检查的QSPI中断源。
  *          此参数可以是以下值之一:
  *          @arg QSPI_IT_TO: 超时中断
  *          @arg QSPI_IT_SM: 状态匹配中断
  *          @arg QSPI_IT_FT: FIFO阈值
  *          @arg QSPI_IT_TC: 传输完成
  *          @arg QSPI_IT_TE: 传输错误
  * 返回值: 新状态-> QSPI_IT (SET or RESET).
  */
ITStatus QSPI_GetITStatus(uint32_t QSPI_IT) {
    ITStatus bitstatus = RESET;
    uint32_t tmpcreg = 0, tmpsreg = 0;

    /* 检查参数 */
    assert_param(IS_QSPI_IT(QSPI_IT));

    /* 读 QUADSPI CR */
    tmpcreg = QUADSPI->CR;
    tmpcreg &= (uint32_t)(QSPI_IT & QSPI_CR_INTERRUPT_MASK);

    /* 读 QUADSPI SR */
    tmpsreg = QUADSPI->SR;
    tmpsreg &= (uint32_t)(QSPI_IT & QSPI_SR_INTERRUPT_MASK);

    /* 检查指定的 QSPI 的状态中断 */
    if((tmpcreg != RESET) && (tmpsreg != RESET)) {
        /* QSPI_IT 被设置 */
        bitstatus = SET;
    } else {
        /* QSPI_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回 QSPI_IT 状态 */
    return bitstatus;
}

/**
  * 简介:  清除 QSPI 的中断挂起位。
  * 参数:  QSPI_IT: 指定要清除的QSPI挂起位。
  *          此参数可以是以下值之一:
  *          @arg QSPI_IT_TO:超时中断
  *          @arg QSPI_IT_SM:状态匹配中断
  *          @arg QSPI_IT_TC:传输完成
  *          @arg QSPI_IT_TE:传输错误
  * 返回值: 无
  */
void QSPI_ClearITPendingBit(uint32_t QSPI_IT) {
    /* 检查参数 */
    assert_param(IS_QSPI_CLEAR_IT(QSPI_IT));

    QUADSPI->FCR = (uint32_t)(QSPI_IT & QSPI_FSR_INTERRUPT_MASK);
}

/**
  * 简介:  启用或禁用 QSPI 双Flash模式。
  * 参数:  NewState: 新状态-> QSPI 双Flash模式。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void QSPI_DualFlashMode_Cmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用QSPI双Flash模式 */
        QUADSPI->CR |= QUADSPI_CR_DFM;
    } else {
        /* 禁用QSPI双Flash模式 */
        QUADSPI->CR &= ~ QUADSPI_CR_DFM;
    }
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
