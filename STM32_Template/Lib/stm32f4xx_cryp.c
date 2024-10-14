/**
  ******************************************************************************
  * 文件:    stm32f4xx_cryp.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能来管理加密处理器 (CRYP) 外设的以下功能:
  *           + 初始化和配置函数
  *           + 数据处理函数
  *           + 上下文交换函数
  *           + DMA 接口函数
  *           + 中断和标志管理
  *
@verbatim
 ===================================================================
                 ##### 如何使用此驱动程序 #####
 ===================================================================
 [..]
   (#) 使用启用 CRYP 控制器时钟
       RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_CRYP, ENABLE) 函数.

   (#) 使用 CRYP_Init()、CRYP_KeyInit() 和如果需要 CRYP_IVInit() 初始化 CRYP。

   (#) 使用 CRYP_FIFOFlush() 函数刷新 IN 和 OUT FIFO。

   (#) 使用 CRYP_Cmd() 函数启用 CRYP 控制器。

   (#) 如果使用 DMA 进行数据输入和输出传输，请使用 CRYP_DMACmd() 函数激活所需的 DMA 请求

   (#) 如果 DMA 不用于数据传输，则使用 CRYP_DataIn() 和 CRYP_DataOut() 函数将数据输入到 IN FIFO 并从 OUT FIFO 中获取结果。

   (#) 要控制 CRYP 事件，您可以使用以下两种方法之一:
       (++) 使用 CRYP_GetFlagStatus() 函数检查 CRYP 标志。
       (++) 在初始化阶段通过函数 CRYP_ITConfig() 使用 CRYP 中断，
			在处理阶段将 CRYP_GetITStatus() 函数用于中断例程。

   (#) 使用 CRYP_SaveContext() 和 CRYP_RestoreContext() 函数保存和恢复加密处理器上下文。


 *** 执行加密或解密的过程 ***
 ==========================================================

 *** 初始化 ***
 ======================
 [..]
(#) 使用 CRYP_Init()、CRYP_KeyInit() 和 CRYP_IVInit 函数初始化外设:
        (++) 配置密钥大小(128、192 或 256 位，仅在 AES 中)
        (++) 输入对称密钥
        (++) 配置数据类型
        (++) AES-ECB或AES-CBC解密时，必须准备密钥:  配置密钥准备模式。 
             然后使用 CRYP_Cmd() 函数启用 CRYP 外设: 设置 BUSY 标志。
             等到 BUSY 标志被重置: 密钥已准备好解密
        (++) 配置算法和链接(ECB/CBC 中的 DES/TDES，ECB/CBC/CTR 中的 AES)
        (++) 配置方向(加密/解密)。
        (++) 编写初始化向量(仅在 CBC 或 CTR 模式下)

    (#) 使用 CRYP_FIFOFlush() 函数刷新 IN 和 OUT FIFO


  *** 基本处理模式(轮询模式) ***
  ============================================
  [..]
(#) 使用 CRYP_Cmd() 函数启用加密处理器。

     (#) 使用 CRYP_DataIn() 函数将第一个块写入输入 FIFO(2 到 8 个字)。

     (#) 重复以下顺序，直到处理完完整的消息:

         (++) 等待标志 CRYP_FLAG_OFNE 出现(使用 CRYP_GetFlagStatus() 函数)，
			  然后使用 CRYP_DataOut() 函数读取 OUT-FIFO(1 块或直到 FIFO 为空)

         (++) 等待标志 CRYP_FLAG_IFNF 出现，(使用 CRYP_GetFlagStatus()
			  函数然后使用 CRYP_DataIn() 函数写入 IN FIFO(1 块或直到 FIFO 已满)

     (#) 在处理结束时，CRYP_FLAG_BUSY 标志将被重置并且两个 FIFO 都是空的
		(CRYP_FLAG_IFEM 被设置并且 CRYP_FLAG_OFNE 被重置)。 您可以使用 CRYP_Cmd() 函数禁用外设。

 *** 中断处理模式 ***
 ==================================
 [..] 在这种模式下，CPU 在中断期间传输数据时完成处理。

    (#) 使用 CRYP_ITConfig() 函数启用中断 CRYP_IT_INI 和 CRYP_IT_OUTI。

    (#) 使用 CRYP_Cmd() 函数启用加密处理器。

    (#) 在 CRYP_IT_INI 中断处理程序中:使用 CRYP_DataIn() 函数将输入消息加载到 IN FIFO 中。
		您可以一次加载 2 或 4 个字，或者加载数据直到 IN FIFO 已满。
		当消息的最后一个字已输入 IN FIFO 时，禁用 CRYP_IT_INI 中断(使用 CRYP_ITConfig() 函数)。

    (#) 在 CRYP_IT_OUTI 中断处理程序中:使用 CRYP_DataOut() 函数从 OUT FIFO 读取输出消息。
		 您可以一次读取 1 个块(2 或 4 个字)或读取数据，直到 FIFO 为空。
         读取最后一个字时，INIM=0，BUSY=0，两个 FIFO 都为空(CRYP_FLAG_IFEM 置位，CRYP_FLAG_OFNE 复位)。
         您可以禁用 CRYP_IT_OUTI 中断(使用 CRYP_ITConfig() 函数)，也可以使用 CRYP_Cmd() 函数禁用外设。

 *** DMA处理模式 ***
 ===========================
 [..] 在此模式下，当使用 DMA 将数据从/向内存传输时，处理完成。

    (#) 使用 DMA_Init() 函数配置 DMA 控制器以从内存传输输入数据。
         传输长度是消息的长度。
         由于外设不管理消息填充，因此消息长度必须是块的整数。
		 数据以突发模式传输。 突发长度在 AES 中为 4 个字，在 DES/TDES 中为 2 或 4 个字。
		 DMA 应配置为在输出数据传输完成时设置中断，以指示处理已完成。
         有关详细信息，请参阅 DMA 外设驱动程序。

     (#) 使用 CRYP_Cmd() 函数启用加密处理器。
          使用 CRYP_DMACmd() 函数启用 DMA 请求 CRYP_DMAReq_DataIN 和 CRYP_DMAReq_DataOUT。

     (#) 所有传输和处理都由 DMA 和加密处理器管理。
		 DMA 传输完成中断表示处理完成。 两个 FIFO 通常都是空的，并且 CRYP_FLAG_BUSY 标志被复位。

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
#include "stm32f4xx_cryp.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup CRYP
  * 简介: CRYP 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define FLAG_MASK     ((uint8_t)0x20)
#define MAX_TIMEOUT   ((uint16_t)0xFFFF)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup CRYP_Private_Functions
  */

/** @defgroup CRYP_Group1 初始化和配置函数
 *  简介    初始化和配置函数
 *
@verbatim
 ===============================================================================
             ##### 初始化和配置函数 #####
 ===============================================================================
 [..] 本节提供的功能允许
   (+) 使用 CRYP_Init() 函数初始化加密处理器
       (++)  加密或解密
       (++)  模式 : TDES-ECB, TDES-CBC,
                    DES-ECB, DES-CBC,
                    AES-ECB, AES-CBC, AES-CTR, AES-Key, AES-GCM, AES-CCM
       (++) 数据类型 :  32-bit data, 16-bit data, bit data or bit-string
       (++) 密钥大小 (仅在 AES 模式下)
   (+) 使用 CRYP_KeyInit() 函数配置加密或解密密钥
   (+) 配置初始化使用 CRYP_IVInit() 函数的 CBC 和 CTR 模式的矢量(IV)。
   (+) 使用 CRYP_FIFOFlush() 函数刷新输入和输出 FIFO。
   (+) 使用 CRYP_Cmd() 函数启用或禁用 CRYP 处理器

@endverbatim
  */
/**
  * 简介:  用于将 CRYP 配置设置为默认复位状态的函数
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void CRYP_DeInit(void) {
    /* 启用 CRYP重置状态 */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_CRYP, ENABLE);

    /* 从重置状态释放 CRYP */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_CRYP, DISABLE);
}

/**
  * 简介:  根据 CRYP_InitStruct 中指定的参数初始化 CRYP 外设。
  * 
  * 参数:  CRYP_InitStruct: 指向包含 CRYP 外设设备配置信息的 CRYP_InitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void CRYP_Init(CRYP_InitTypeDef* CRYP_InitStruct) {
    /* 检查参数 */
    assert_param(IS_CRYP_ALGOMODE(CRYP_InitStruct->CRYP_AlgoMode));
    assert_param(IS_CRYP_DATATYPE(CRYP_InitStruct->CRYP_DataType));
    assert_param(IS_CRYP_ALGODIR(CRYP_InitStruct->CRYP_AlgoDir));

    /* 选择算法模式*/
    CRYP->CR &= ~CRYP_CR_ALGOMODE;
    CRYP->CR |= CRYP_InitStruct->CRYP_AlgoMode;

    /* 选择数据类型 */
    CRYP->CR &= ~CRYP_CR_DATATYPE;
    CRYP->CR |= CRYP_InitStruct->CRYP_DataType;

    /* 选择密钥大小(仅用于AES算法) */
    if ((CRYP_InitStruct->CRYP_AlgoMode != CRYP_AlgoMode_TDES_ECB) &&
            (CRYP_InitStruct->CRYP_AlgoMode != CRYP_AlgoMode_TDES_CBC) &&
            (CRYP_InitStruct->CRYP_AlgoMode != CRYP_AlgoMode_DES_ECB) &&
            (CRYP_InitStruct->CRYP_AlgoMode != CRYP_AlgoMode_DES_CBC)) {
        assert_param(IS_CRYP_KEYSIZE(CRYP_InitStruct->CRYP_KeySize));
        CRYP->CR &= ~CRYP_CR_KEYSIZE;
        CRYP->CR |= CRYP_InitStruct->CRYP_KeySize; /* 一旦准备好密钥，就必须配置密钥大小和值 */
    }

    /* Select data Direction */
    CRYP->CR &= ~CRYP_CR_ALGODIR;
    CRYP->CR |= CRYP_InitStruct->CRYP_AlgoDir;
}

/**
  * 简介:  用默认值填充每个 CRYP_InitStruct 成员。
  * 
  * 参数:  CRYP_InitStruct: 指向将被初始化的 CRYP_InitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void CRYP_StructInit(CRYP_InitTypeDef* CRYP_InitStruct) {
    /* 初始化 CRYP_AlgoDir成员 */
    CRYP_InitStruct->CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;

    /* 初始化 CRYP_AlgoMode 成员 */
    CRYP_InitStruct->CRYP_AlgoMode = CRYP_AlgoMode_TDES_ECB;

    /* 初始化 CRYP_DataType 成员 */
    CRYP_InitStruct->CRYP_DataType = CRYP_DataType_32b;

    /* 初始化 CRYP_KeySize 成员 */
    CRYP_InitStruct->CRYP_KeySize = CRYP_KeySize_128b;
}

/**
  * 简介:  根据 CRYP_KeyInitStruct 中指定的参数初始化 CRYP 密钥。
  * 
  * 参数:  CRYP_KeyInitStruct: 指向包含 CRYP密钥配置信息的 CRYP_KeyInitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void CRYP_KeyInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct) {
    /* 密钥初始化 */
    CRYP->K0LR = CRYP_KeyInitStruct->CRYP_Key0Left;
    CRYP->K0RR = CRYP_KeyInitStruct->CRYP_Key0Right;
    CRYP->K1LR = CRYP_KeyInitStruct->CRYP_Key1Left;
    CRYP->K1RR = CRYP_KeyInitStruct->CRYP_Key1Right;
    CRYP->K2LR = CRYP_KeyInitStruct->CRYP_Key2Left;
    CRYP->K2RR = CRYP_KeyInitStruct->CRYP_Key2Right;
    CRYP->K3LR = CRYP_KeyInitStruct->CRYP_Key3Left;
    CRYP->K3RR = CRYP_KeyInitStruct->CRYP_Key3Right;
}

/**
  * 简介:  用默认值填充每个 CRYP_KeyInitStruct 成员。
  * 
  * 参数:  CRYP_KeyInitStruct: 指向将被初始化的 CRYP_KeyInitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void CRYP_KeyStructInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct) {
    CRYP_KeyInitStruct->CRYP_Key0Left  = 0;
    CRYP_KeyInitStruct->CRYP_Key0Right = 0;
    CRYP_KeyInitStruct->CRYP_Key1Left  = 0;
    CRYP_KeyInitStruct->CRYP_Key1Right = 0;
    CRYP_KeyInitStruct->CRYP_Key2Left  = 0;
    CRYP_KeyInitStruct->CRYP_Key2Right = 0;
    CRYP_KeyInitStruct->CRYP_Key3Left  = 0;
    CRYP_KeyInitStruct->CRYP_Key3Right = 0;
}
/**
  * 简介:  根据 CRYP_IVInitStruct 中指定的参数初始化 CRYP 初始化向量 (IV)。
  * 
  * 参数:  CRYP_IVInitStruct: 指向包含 CRYP配置信息的 CRYP_IVInitTypeDef 结构的指针初始化矢量(IV)。
  * 
  * 返回值: 无
  */
void CRYP_IVInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct) {
    CRYP->IV0LR = CRYP_IVInitStruct->CRYP_IV0Left;
    CRYP->IV0RR = CRYP_IVInitStruct->CRYP_IV0Right;
    CRYP->IV1LR = CRYP_IVInitStruct->CRYP_IV1Left;
    CRYP->IV1RR = CRYP_IVInitStruct->CRYP_IV1Right;
}

/**
  * 简介:  用默认值填充每个 CRYP_IVInitStruct 成员。
  * 
  * 参数:  CRYP_IVInitStruct: 指向将被初始化的 CRYP_IVInitTypeDef 初始化向量(IV)结构的指针。
  * 
  * 返回值: 无
  */
void CRYP_IVStructInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct) {
    CRYP_IVInitStruct->CRYP_IV0Left  = 0;
    CRYP_IVInitStruct->CRYP_IV0Right = 0;
    CRYP_IVInitStruct->CRYP_IV1Left  = 0;
    CRYP_IVInitStruct->CRYP_IV1Right = 0;
}

/**
  * 简介:  配置 AES-CCM 和 AES-GCM 阶段。
  * 
  * 注意:   此函数仅用于 AES-CCM 或 AES-GCM 算法
  * 
  * 参数:  CRYP_Phase: 指定要配置的 CRYP AES-CCM 和 AES-GCM 阶段。
  *           此参数可以是以下值之一:
  *            @arg CRYP_Phase_Init:    初始化阶段
  *            @arg CRYP_Phase_Header:  头部阶段
  *            @arg CRYP_Phase_Payload: 有效载荷阶段
  *            @arg CRYP_Phase_Final:   最后阶段
  * 
  * 返回值: 无
  */
void CRYP_PhaseConfig(uint32_t CRYP_Phase) {
    uint32_t tempcr = 0;

    /* 检查参数 */
    assert_param(IS_CRYP_PHASE(CRYP_Phase));

    /* 获取CR 寄存器 */
    tempcr = CRYP->CR;

    /* 重设相位配置位: GCMP_CCMPH */
    tempcr &= (uint32_t)(~CRYP_CR_GCM_CCMPH);
    /* 设置选定的阶段 */
    tempcr |= (uint32_t)CRYP_Phase;

    /* 设置 CR 寄存器 */
    CRYP->CR = tempcr;
}

/**
  * 简介:  刷新 IN 和 OUT FIFO(即 FIFO 的读写指针被复位)
  * 
  * 注意:   只有当BUSY标志被重置时，FIFO 必须被刷新。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void CRYP_FIFOFlush(void) {
    /* 重设 read and write pointers of the FIFOs */
    CRYP->CR |= CRYP_CR_FFLUSH;
}

/**
  * 简介:  启用或禁用 CRYP外设设备。
  * 
  * 参数:  NewState: CRYP 外围的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void CRYP_Cmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 Cryptographic 处理器 */
        CRYP->CR |= CRYP_CR_CRYPEN;
    } else {
        /* 禁用 Cryptographic 处理器 */
        CRYP->CR &= ~CRYP_CR_CRYPEN;
    }
}

/** @defgroup CRYP_Group2 CRYP 数据处理功能
 *  简介    CRYP 数据处理功能
 *
@verbatim
 ===============================================================================
                    ##### CRYP 数据处理功能 #####
 ===============================================================================
 [..] 本节提供了允许进行加密和解密操作的函数。
   (+) 在 IN FIFO 中输入要处理的数据:使用 CRYP_DataIn() 函数。
   (+) 从OUT FIFO获取数据结果:使用 CRYP_DataOut() 函数。

@endverbatim
  */

/**
  * 简介:  将数据写入数据输入寄存器(DIN)。
  * 
  * 注意:   在DIN寄存器被读过一次或几次之后,FIFO必须被刷新(使用 CRYP_FIFOFlush() 函数)。
  * 
  * 参数:  Data: 要写入数据输入寄存器的数据
  * 
  * 返回值: 无
  */
void CRYP_DataIn(uint32_t Data) {
    CRYP->DR = Data;
}

/**
  * 简介:  返回输入输出FIFO 的最后一个数据。
  * 
  * 参数:  无
  * 
  * 返回值: 最后输入输出FIFO 的数据。
  */
uint32_t CRYP_DataOut(void) {
    return CRYP->DOUT;
}

/** @defgroup CRYP_Group3 上下文交换函数
 *  简介   上下文交换函数
 *
@verbatim
 ===============================================================================
                      ##### 上下文交换函数 #####
 ===============================================================================
 [..] 本节提供允许保存和存储CRYP上下文的功能

 [..] 有可能中断一个加密/解密/密钥生成过程，以执行另一个具有更高优先级的处理，
        并在稍后完成被中断的过程，当更高优先级的任务完成后。要做到这一点，
        必须将被中断的任务的上下文从CRYP 寄存器中保存到内存中，然后再从内存中恢复到 CRYP 寄存器中。

   (#) 要保存当前上下文，请使用 CRYP_SaveContext() 函数
   (#) 要恢复保存的上下文，请使用 CRYP_RestoreContext() 函数

@endverbatim
  */

/**
  * 简介:  保存CRYP外设上下文。
  * 
  * 注意:   该函数在保存上下文之前停止DMA 传输。在 恢复上下文后，
  *         你必须再次启用 DMA(如果以前使用过DMA)。
  * 
  * 参数:  CRYP_ContextSave: 指向CRYP_Context结构的指针，该结构含有 当前上下文的存储库。
  * 
  * 参数:  CRYP_KeyInitStruct: 指向CRYP_KeyInitTypeDef 结构的指针，该结构包含 CRYP密钥的配置信息。
  * 
  * 返回值: 无
  */
ErrorStatus CRYP_SaveContext(CRYP_Context* CRYP_ContextSave,
                             CRYP_KeyInitTypeDef* CRYP_KeyInitStruct) {
    __IO uint32_t timeout = 0;
    uint32_t ckeckmask = 0, bitstatus;
    ErrorStatus status = ERROR;

    /* 通过清除 CRYP_DMACR中的 DIEN 位停止IN FIFO上的 DMA 传输。 */
    CRYP->DMACR &= ~(uint32_t)CRYP_DMACR_DIEN;

    /* 等到 IN 和OUT FIFO 都是空的(CRYP_SR 寄存器中IFEM=1和OfNE=0)，BUSY位被清除。 */

    if ((CRYP->CR & (uint32_t)(CRYP_CR_ALGOMODE_TDES_ECB | CRYP_CR_ALGOMODE_TDES_CBC)) != (uint32_t)0 ) { /* TDES */
        ckeckmask =  CRYP_SR_IFEM | CRYP_SR_BUSY ;
    } else { /* AES or DES */
        ckeckmask =  CRYP_SR_IFEM | CRYP_SR_BUSY | CRYP_SR_OFNE;
    }

    do {
        bitstatus = CRYP->SR & ckeckmask;
        timeout++;
    } while ((timeout != MAX_TIMEOUT) && (bitstatus != CRYP_SR_IFEM));

    if ((CRYP->SR & ckeckmask) != CRYP_SR_IFEM) {
        status = ERROR;
    } else {
        /* 通过以下方式停止OUT FIFO上的 DMA 传输
           - 将CRYP_DMACR 寄存器中的 DOEN 位写为0
           - 并清除 CRYPEN 位。 */

        CRYP->DMACR &= ~(uint32_t)CRYP_DMACR_DOEN;
        CRYP->CR &= ~(uint32_t)CRYP_CR_CRYPEN;

        /* 保存当前配置(CRYP_CR 寄存器中的第19位、第[17:16]位和第[9:2]位)。*/
        CRYP_ContextSave->CR_CurrentConfig  = CRYP->CR & (CRYP_CR_GCM_CCMPH |
                                              CRYP_CR_KEYSIZE  |
                                              CRYP_CR_DATATYPE |
                                              CRYP_CR_ALGOMODE |
                                              CRYP_CR_ALGODIR);

        /* and, if not in ECB mode, the 初始化Vectors. */
        CRYP_ContextSave->CRYP_IV0LR = CRYP->IV0LR;
        CRYP_ContextSave->CRYP_IV0RR = CRYP->IV0RR;
        CRYP_ContextSave->CRYP_IV1LR = CRYP->IV1LR;
        CRYP_ContextSave->CRYP_IV1RR = CRYP->IV1RR;

        /* 保存密钥值 */
        CRYP_ContextSave->CRYP_K0LR = CRYP_KeyInitStruct->CRYP_Key0Left;
        CRYP_ContextSave->CRYP_K0RR = CRYP_KeyInitStruct->CRYP_Key0Right;
        CRYP_ContextSave->CRYP_K1LR = CRYP_KeyInitStruct->CRYP_Key1Left;
        CRYP_ContextSave->CRYP_K1RR = CRYP_KeyInitStruct->CRYP_Key1Right;
        CRYP_ContextSave->CRYP_K2LR = CRYP_KeyInitStruct->CRYP_Key2Left;
        CRYP_ContextSave->CRYP_K2RR = CRYP_KeyInitStruct->CRYP_Key2Right;
        CRYP_ContextSave->CRYP_K3LR = CRYP_KeyInitStruct->CRYP_Key3Left;
        CRYP_ContextSave->CRYP_K3RR = CRYP_KeyInitStruct->CRYP_Key3Right;

        /* 保存上下文交换寄存器的内容 */
        CRYP_ContextSave->CRYP_CSGCMCCMR[0] = CRYP->CSGCMCCM0R;
        CRYP_ContextSave->CRYP_CSGCMCCMR[1] = CRYP->CSGCMCCM1R;
        CRYP_ContextSave->CRYP_CSGCMCCMR[2] = CRYP->CSGCMCCM2R;
        CRYP_ContextSave->CRYP_CSGCMCCMR[3] = CRYP->CSGCMCCM3R;
        CRYP_ContextSave->CRYP_CSGCMCCMR[4] = CRYP->CSGCMCCM4R;
        CRYP_ContextSave->CRYP_CSGCMCCMR[5] = CRYP->CSGCMCCM5R;
        CRYP_ContextSave->CRYP_CSGCMCCMR[6] = CRYP->CSGCMCCM6R;
        CRYP_ContextSave->CRYP_CSGCMCCMR[7] = CRYP->CSGCMCCM7R;

        CRYP_ContextSave->CRYP_CSGCMR[0] = CRYP->CSGCM0R;
        CRYP_ContextSave->CRYP_CSGCMR[1] = CRYP->CSGCM1R;
        CRYP_ContextSave->CRYP_CSGCMR[2] = CRYP->CSGCM2R;
        CRYP_ContextSave->CRYP_CSGCMR[3] = CRYP->CSGCM3R;
        CRYP_ContextSave->CRYP_CSGCMR[4] = CRYP->CSGCM4R;
        CRYP_ContextSave->CRYP_CSGCMR[5] = CRYP->CSGCM5R;
        CRYP_ContextSave->CRYP_CSGCMR[6] = CRYP->CSGCM6R;
        CRYP_ContextSave->CRYP_CSGCMR[7] = CRYP->CSGCM7R;

        /* 需要时，保存DMA状态(IN 和OUT信息的指针，剩余字节数等)。 */

        status = SUCCESS;
    }

    return status;
}

/**
  * 简介:  恢复 CRYP 外设设备上下文。
  * 
  * 注意:   由于 DMA 传输在 CRYP_SaveContext() 函数中被停止，
  *         在恢复上下文后，你必须再次启用 DMA(如果以前使用过DMA)。
  * 
  * 参数:  CRYP_ContextRestore: 指向包含已保存上下文的存储库的 CRYP_Context 结构的指针。
  * 
  * 注意:   上下文保存期间保存的数据必须重写到 IN FIFO 中。
  * 
  * 返回值: 无
  */
void CRYP_RestoreContext(CRYP_Context* CRYP_ContextRestore) {

    /* 配置 processor with the saved 配置*/
    CRYP->CR = CRYP_ContextRestore->CR_CurrentConfig;

    /* 恢复密钥值 */
    CRYP->K0LR = CRYP_ContextRestore->CRYP_K0LR;
    CRYP->K0RR = CRYP_ContextRestore->CRYP_K0RR;
    CRYP->K1LR = CRYP_ContextRestore->CRYP_K1LR;
    CRYP->K1RR = CRYP_ContextRestore->CRYP_K1RR;
    CRYP->K2LR = CRYP_ContextRestore->CRYP_K2LR;
    CRYP->K2RR = CRYP_ContextRestore->CRYP_K2RR;
    CRYP->K3LR = CRYP_ContextRestore->CRYP_K3LR;
    CRYP->K3RR = CRYP_ContextRestore->CRYP_K3RR;

    /* and the 初始化Vectors. */
    CRYP->IV0LR = CRYP_ContextRestore->CRYP_IV0LR;
    CRYP->IV0RR = CRYP_ContextRestore->CRYP_IV0RR;
    CRYP->IV1LR = CRYP_ContextRestore->CRYP_IV1LR;
    CRYP->IV1RR = CRYP_ContextRestore->CRYP_IV1RR;

    /* 恢复上下文交换寄存器的内容 */
    CRYP->CSGCMCCM0R = CRYP_ContextRestore->CRYP_CSGCMCCMR[0];
    CRYP->CSGCMCCM1R = CRYP_ContextRestore->CRYP_CSGCMCCMR[1];
    CRYP->CSGCMCCM2R = CRYP_ContextRestore->CRYP_CSGCMCCMR[2];
    CRYP->CSGCMCCM3R = CRYP_ContextRestore->CRYP_CSGCMCCMR[3];
    CRYP->CSGCMCCM4R = CRYP_ContextRestore->CRYP_CSGCMCCMR[4];
    CRYP->CSGCMCCM5R = CRYP_ContextRestore->CRYP_CSGCMCCMR[5];
    CRYP->CSGCMCCM6R = CRYP_ContextRestore->CRYP_CSGCMCCMR[6];
    CRYP->CSGCMCCM7R = CRYP_ContextRestore->CRYP_CSGCMCCMR[7];

    CRYP->CSGCM0R = CRYP_ContextRestore->CRYP_CSGCMR[0];
    CRYP->CSGCM1R = CRYP_ContextRestore->CRYP_CSGCMR[1];
    CRYP->CSGCM2R = CRYP_ContextRestore->CRYP_CSGCMR[2];
    CRYP->CSGCM3R = CRYP_ContextRestore->CRYP_CSGCMR[3];
    CRYP->CSGCM4R = CRYP_ContextRestore->CRYP_CSGCMR[4];
    CRYP->CSGCM5R = CRYP_ContextRestore->CRYP_CSGCMR[5];
    CRYP->CSGCM6R = CRYP_ContextRestore->CRYP_CSGCMR[6];
    CRYP->CSGCM7R = CRYP_ContextRestore->CRYP_CSGCMR[7];

    /* 启用 cryptographic 处理器 */
    CRYP->CR |= CRYP_CR_CRYPEN;
}

/** @defgroup CRYP_Group4 CRYP的 DMA 接口配置功能
 *  简介   CRYP的 DMA 接口配置功能
 *
@verbatim
 ===============================================================================
             ##### CRYP的 DMA 接口配置功能 #####
 ===============================================================================
 [..] 本节提供的功能允许 为 CRYP 数据输入和输出传输配置 DMA 接口。

 [..] 当 DMA 模式被启用时(使用 CRYP_DMACmd() 函数)，数据可以被传输。
   (+) 通过启用 CRYP_DMAReq_DataIN 请求，使用 DMA 外设从内存到 CRYP IN FIFO。
   (+) 通过启用 CRYP_DMAReq_DataOUT 请求，从 CRYP OUT FIFO 到使用 DMA 外设的存储器。

@endverbatim
  */

/**
  * 简介:  启用或禁用 CRYP DMA 接口。
  * 
  * 参数:  CRYP_DMAReq: 指定要启用或禁用的 CRYP DMA 传输请求。
  *           此参数可以是以下值的任意组合:
  *            @arg CRYP_DMAReq_DataOUT: 用于传出(Tx)数据传输的 DMA
  *            @arg CRYP_DMAReq_DataIN:  用于传入(Rx)数据传输的 DMA
  * 
  * 参数:  NewState: 所选 CRYP DMA 传输请求的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void CRYP_DMACmd(uint8_t CRYP_DMAReq, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_CRYP_DMAREQ(CRYP_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的 CRYP DMA 请求 */
        CRYP->DMACR |= CRYP_DMAReq;
    } else {
        /* 禁用选定的 CRYP DMA 请求 */
        CRYP->DMACR &= (uint8_t)~CRYP_DMAReq;
    }
}

/** @defgroup CRYP_Group5 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
              ##### 中断和标记管理函数 #####
 ===============================================================================

 [..] 本节提供的功能允许配置 CRYP Interrupts 和 以获得状态和中断等待位。

 [..] CRYP提供2个中断源和7个标志。

 *** Flags : ***
 ===============
 [..]
   (#) CRYP_FLAG_IFEM : 当输入FIFO为空时设置。这个标志只能由硬件清除。

   (#) CRYP_FLAG_IFNF : 当输入FIFO未满时设置。该标志仅由硬件清除。


   (#) CRYP_FLAG_INRIS : 当输入FIFO原始中断等待时设置，它给出输入FIFO服务中断屏蔽前的原始中断状态。
                         这个标志只能由硬件来清除。

   (#) CRYP_FLAG_OFNE : 当输出FIFO不空时设置。该标志仅由硬件清除。

   (#) CRYP_FLAG_OFFU : 当输出FIFO 满时设置。该标志仅由硬件清除。

   (#) CRYP_FLAG_OUTRIS : 当输出FIFO原始中断等待时设置，它给出了输出FIFO服务中断屏蔽之前的原始中断状态。
       这个标志只能由硬件来清除。

   (#) CRYP_FLAG_BUSY : 当CRYP核心目前正在处理一个数据块或一个密钥准备(用于AES解密)时设置。
                        这个标志只能由硬件来清除。要清除它，CRYP内核必须被禁用，并且最后的处理已经完成。

 *** 中断 : ***
 ====================
 [..]
   (#) CRYP_IT_INI   : 当输入FIFO 中的字数少于4个时，输入FIFO服务中断被断言。
                       这个中断与CRYP_FLAG_INRIS标志相关。

      -@- 该中断通过对输入FIFO进行写操作而被清除，直到它容纳4个或更多的字。
          输入FIFO服务中断INMIS是通过 CRYP使能位启用的。因此，当CRYP被禁用时，
          即使输入FIFO为空，INMIS信号也是低电平。



   (#) CRYP_IT_OUTI  : 当输出FIFO 中有一个或多个(32位字)数据项时，输出FIFO服务中断被断言。
                       该中断与CRYP_FLAG_OUTRIS标志相关。


       -@- 该中断通过从输出FIFO 中读取数据来清除，直到没有有效的(32位)字为止(也就是说，
           该中断跟随OFNE(输出FIFO不空)标志的状态)。

 *** 管理CRYP控制器事件 : ***
 =============================================
 [..] 用户应该确定在他的应用程序中使用哪种模式来管理CRYP控制器的事件:轮询模式或中断模式。

   (#) 在轮询模式下，建议使用以下函数。
       (++) CRYP_GetFlagStatus() : 检查是否发生标志事件。

       -@@- CRYPT标志不需要被清除，因为一旦相关事件被重置，它们就会被清除。


   (#) 在中断模式下，建议使用以下函数。
       (++) CRYP_ITConfig() : 启用或禁用中断源。
       (++) CRYP_GetITStatus() : 检查是否发生中断。

       -@@- CRYPT中断没有等待位，一旦相关事件被重置，中断就会被清除。

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 CRYP 中断。
  * 
  * 参数:  CRYP_IT: 指定要启用或禁用的 CRYP 中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg CRYP_IT_INI:  输入 FIFO 中断
  *            @arg CRYP_IT_OUTI: 输出 FIFO 中断
  * 
  * 参数:  NewState: 指定 CRYP 中断的新状态。
  *           此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void CRYP_ITConfig(uint8_t CRYP_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_CRYP_CONFIG_IT(CRYP_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的 CRYP 中断 */
        CRYP->IMSCR |= CRYP_IT;
    } else {
        /* 禁用选定的 CRYP 中断 */
        CRYP->IMSCR &= (uint8_t)~CRYP_IT;
    }
}

/**
  * 简介:  检查是否发生了指定的 CRYP 中断。
  * 
  * 注意:   该函数检查被屏蔽的中断的状态(即该中断应该是先前启用的)。
  * 
  * 参数:  CRYP_IT: 指定要检查的 CRYP(屏蔽的)中断源。
  *           此参数可以是以下值之一:
  *            @arg CRYP_IT_INI:  输入 FIFO 中断
  *            @arg CRYP_IT_OUTI: 输出 FIFO 中断
  * 
  * 返回值: CRYP_IT 的新状态(SET 或 RESET)。
  */
ITStatus CRYP_GetITStatus(uint8_t CRYP_IT) {
    ITStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_CRYP_GET_IT(CRYP_IT));

    /* 检查指定的 CRYP中断的状态 */
    if ((CRYP->MISR &  CRYP_IT) != (uint8_t)RESET) {
        /* CRYP_IT 被设置 */
        bitstatus = SET;
    } else {
        /* CRYP_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回CRYP_IT状态 */
    return bitstatus;
}

/**
  * 简介:  返回 CRYP 外设是启用还是禁用。
  * 
  * 参数:  无.
  * 
  * 返回值: CRYP外设的当前状态(ENABLE 或 DISABLE)。
  */
FunctionalState CRYP_GetCmdStatus(void) {
    FunctionalState state = DISABLE;

    if ((CRYP->CR & CRYP_CR_CRYPEN) != 0) {
        /* CRYPEN bit 被设置 */
        state = ENABLE;
    } else {
        /* CRYPEN bit  被重置 */
        state = DISABLE;
    }

    return state;
}

/**
  * 简介:  检查是否设置了指定的 CRYP 标志。
  * 
  * 参数:  CRYP_FLAG: 指定要检查的 CRYP标志。
  *          此参数可以是以下值之一:
  *            @arg CRYP_FLAG_IFEM:   输入 FIFO 空标志。
  *            @arg CRYP_FLAG_IFNF:   输入 FIFO 未满标志。
  *            @arg CRYP_FLAG_OFNE:   输出 FIFO 非空标志。
  *            @arg CRYP_FLAG_OFFU:   输出 FIFO 满标志。
  *            @arg CRYP_FLAG_BUSY:   忙碌标志.
  *            @arg CRYP_FLAG_OUTRIS: 输出 FIFO 原始中断标志.
  *            @arg CRYP_FLAG_INRIS:  输入 FIFO 原始中断标志.
  * 
  * 返回值。CRYP_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus CRYP_GetFlagStatus(uint8_t CRYP_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tempreg = 0;

    /* 检查参数 */
    assert_param(IS_CRYP_GET_FLAG(CRYP_FLAG));

    /* 检查 if the FLAG is in RISR 寄存器 */
    if ((CRYP_FLAG & FLAG_MASK) != 0x00) {
        tempreg = CRYP->RISR;
    } else { /* The FLAG is in SR 寄存器 */
        tempreg = CRYP->SR;
    }


    /* 检查 the status of the specified CRYP flag */
    if ((tempreg & CRYP_FLAG ) != (uint8_t)RESET) {
        /* CRYP_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* CRYP_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回CRYP_FLAG 状态 */
    return  bitstatus;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
