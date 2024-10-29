/**
  ******************************************************************************
  * 文件:    stm32f4xx_hash.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件函数，用于管理HASH/HMAC处理器(HASH)外设设备的以下函数:
  *           - 初始化和配置函数
  *           - 消息摘要生成函数
  *           - 上下文交换函数
  *           - DMA 接口函数
  *           - 中断和标志管理
  *
@verbatim
 ===================================================================
                 ##### 如何使用此驱动程序 #####
 ===================================================================

 *** HASH 操作 : ***
 ========================
 [..]
   (#) 使用 RCC_AHB2PeriphClockCmd(RCC_AHB2Periph-HASH，Enable) 函数启用 HASH控制器时钟。

   (#) 使用 HASH_Init() 函数初始化HASH。

   (#) 重置 HASH 处理器内核，以便 HASH 可以使用 HASH_Reset() 函数计算新消息的消息摘要。

   (#) 使用 HASH_Cmd() 函数启用 HASH 控制器。
 
   (#) 如果使用 DMA 进行数据输入传输，请使用 HASH_DMACmd() 函数激活 DMA 请求

   (#) 如果 DMA 不用于数据传输，请使用 HASH_DataIn() 函数将数据输入到 IN FIFO。

   (#) 配置消息最后一个字的有效位数
       使用 HASH_SetLastWordValidBitsNbr() 函数。

   (#) 如果消息长度不是512位的精确倍数，则必须调用函数 HASH_StartDigest() 来启动最终摘要的计算。

   (#) 计算完成后，可以使用 HASH_GetDigest() 函数读取摘要。

   (#) 要控制 HASH 事件，可以使用以下两种方法之一:
       (++) 使用 HASH_GetFlagStatus() 函数检查HASH标志。

       (++) 在初始化阶段通过函数 HASH_ITConfig() 和 HASH_GetITStatus() 将 HASH 中断用于哈希阶段的中断例程。
            检查标志后，应使用 HASH_ClearFlag() 函数将其清除。在检查中断事件后，
            
		应该使用 HASH_ClearITPendingBit() 函数清除它。

   (#) 使用 hash_SaveContext() 和 hash_RestoreContext() 函数保存和还原哈希处理器上下文。



 *** HMAC操作 : ***
 ========================
 [..] HMAC算法用于消息身份验证，通过不可逆地将正在处理的消息绑定到用户选择的密钥。
      有关HMAC规范，请参阅"HMAC:keyed hashing For message authentication，H.Krawczyk，M.Bellare，R.Canetti，1997年2月"

 [..] 基本上，HMAC算法由两个嵌套哈希操作组成:
      HMAC(message) = Hash[((key | pad) XOR 0x5C) | Hash(((key | pad) XOR 0x36) | message)]
      where:
      (+) "pad"是将密钥扩展到基础哈希函数数据块长度所需的一系列零(即SHA-1和MD5哈希算法都是512位)
      (+) "|"   表示串联运算符


 [..]为了计算HMAC，需要四个不同的阶段:
   (#) 使用 HASH_Init() 函数初始化 HASH 以执行 HMAC 操作。

   (#) 然后将密钥(用于内部哈希函数)提供给核心。
       此操作遵循与哈希操作中用于发送消息的机制相同的机制(即，通过 hash_DataIn() 函数，最后通过 hash_StartDigest() 函数)。

   (#) 一旦输入了最后一个字并开始计算，哈希处理器就会详细说明密钥。
	然后，它就可以使用与在哈希操作中发送消息相同的机制来接受消息文本。

   (#) 第一轮散列后，散列处理器返回"ready"，表示它准备好接收用于外部散列函数的密钥(通常，该密钥与用于内部散列函数中的密钥相同)。
       当输入键的最后一个字并开始计算时，可以使用 HASH_GetDigest() 函数获得HMAC结果。

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
#include "stm32f4xx_hash.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup HASH
  * 简介: HASH驱动程序模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup HASH_Private_Functions
  */

/** @defgroup HASH_Group1初始化和配置函数
 *  简介    初始化和配置函数
 *
@verbatim
 ===============================================================================
              ##### 初始化和配置函数 #####
 ===============================================================================
 [..] 本节提供的函数允许
   (+) 初始化HASH 外设设备
   (+) 配置HASH处理器
   (+) MD5/SHA1,
   (+) HASH/HMAC,
   (+) datatype
   (+) HMAC Key (if mode = HMAC)
   (+) 重置HASH处理器

@endverbatim
  */

/**
  * 简介:  将HASH 外设寄存器反初始化为其默认重置值
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void HASH_DeInit(void) {
    /* 启用 HASH复位状态 */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_HASH, ENABLE);
    /* 从复位状态释放HASH */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_HASH, DISABLE);
}

/**
  * 简介:  根据HASH_InitStruct 结构中的指定参数初始化HASH 外设设备。
  * 
  * 注意:  调用此函数时，哈希处理器会重置，以便hash可以计算新消息的消息摘要。
  *        不需要调用 HASH_Reset() 函数。
  * 
  * 参数:  HASH_InitStruct: 指向包含 HASH 外设设备配置信息的 HASH_InitTypeDef 结构的指针。
  * 
  * 注意:   仅当算法模式为 HMAC 时，必须填充 HASH_InitTypeDef 中的字段 HASH_HMACKeyType。
  * 
  * 返回值: 无
  */
void HASH_Init(HASH_InitTypeDef* HASH_InitStruct) {
    /* 检查参数 */
    assert_param(IS_HASH_ALGOSELECTION(HASH_InitStruct->HASH_AlgoSelection));
    assert_param(IS_HASH_DATATYPE(HASH_InitStruct->HASH_DataType));
    assert_param(IS_HASH_ALGOMODE(HASH_InitStruct->HASH_AlgoMode));

    /* 配置使用的算法、算法模式和数据类型 */
    HASH->CR &= ~ (HASH_CR_ALGO | HASH_CR_DATATYPE | HASH_CR_MODE);
    HASH->CR |= (HASH_InitStruct->HASH_AlgoSelection | \
                 HASH_InitStruct->HASH_DataType | \
                 HASH_InitStruct->HASH_AlgoMode);

    /* 如果算法模式为 HMAC，则设置密钥 */
    if(HASH_InitStruct->HASH_AlgoMode == HASH_AlgoMode_HMAC) {
        assert_param(IS_HASH_HMAC_KEYTYPE(HASH_InitStruct->HASH_HMACKeyType));
        HASH->CR &= ~HASH_CR_LKEY;
        HASH->CR |= HASH_InitStruct->HASH_HMACKeyType;
    }

    /* 重置HASH处理器内核，以便HASH可以计算新消息的消息摘要 */
    HASH->CR |= HASH_CR_INIT;
}

/**
  * 简介:  用默认值填充每个HASH_InitStruct 成员。
  * 
  * 参数:  HASH_InitStruct : 指向将被初始化的 HASH_InitTypeDef 结构的指针。
  * 
  * @note  默认值设置为:处理器模式为 HASH，选择的算法为SHA1，选择的数据类型为32b，HMAC密钥类型为短键。
  * 
  * 返回值: 无
  */
void HASH_StructInit(HASH_InitTypeDef* HASH_InitStruct) {
    /* 初始化HASH_AlgoSelection成员 */
    HASH_InitStruct->HASH_AlgoSelection = HASH_AlgoSelection_SHA1;

    /* 初始化HASH_AlgoMode成员 */
    HASH_InitStruct->HASH_AlgoMode = HASH_AlgoMode_HASH;

    /* 初始化HASH_DataType成员 */
    HASH_InitStruct->HASH_DataType = HASH_DataType_32b;

    /* 初始化HASH_HMACKeyType成员 */
    HASH_InitStruct->HASH_HMACKeyType = HASH_HMACKeyType_ShortKey;
}

/**
  * 简介:  重置HASH处理器内核，以便HASH可以计算新消息的消息摘要。
  * 
  * 注意:   调用此函数将清除与HASH_IT_DCI中断和HASH_FLAG_DCIS标志相对应的 HASH_SR_DCIS(摘要计算完成中断状态)位。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void HASH_Reset(void) {
    /* 重置HASH处理器内核 */
    HASH->CR |= HASH_CR_INIT;
}

/** @defgroup HASH_Group2消息摘要生成函数
 *  简介    消息摘要生成函数
 *
@verbatim
 ===============================================================================
                  ##### 函数息摘要生成功能 #####
 ===============================================================================
 [..] 本节提供了允许生成消息摘要的函数:
   (+) 在 IN FIFO 中推送数据:使用 HASH_DataIn()
   (+) 获取 IN FIFO 中设置的字数，使用 HASH_GetInFIFOWordsNbr()
   (+) 使用 HASH_SetLastWordValidBitsNbr()设置最后一个字的有效位数
   (+) 开始摘要计算:使用 HASH_StartDigest()
   (+) 获取摘要消息:使用 HASH_GetDigest()

@endverbatim
  */


/**
  * 简介:  配置消息最后一个字的有效位数
  * 
  * 参数:  ValidNumber:消息最后一个字的有效位数。
  *           此参数必须是介于 0 和 0x1F 之间的数字。
  *             - 0x00: 最后写入的所有32位数据均有效
  *             - 0x01: 只有最后写入数据的位[0]有效
  *             - 0x02: 只有最后写入的数据的位[1:0]有效
  *             - 0x03: 只有最后写入的数据的位[2:0]有效
  *             - ...
  *             - 0x1F: 只有最后写入的数据的位[30:0]有效
  * 
  * 注意:   在开始消息摘要竞争(在哈希和HMAC 中)和密钥处理(在HMAC)之前，必须设置有效位数。
  * 
  * 返回值: 无
  */
void HASH_SetLastWordValidBitsNbr(uint16_t ValidNumber) {
    /* 检查参数 */
    assert_param(IS_HASH_VALIDBITSNUMBER(ValidNumber));

    /* 配置消息最后一个字的有效位数 */
    HASH->STR &= ~(HASH_STR_NBW);
    HASH->STR |= ValidNumber;
}

/**
  * 简介:  将数据写入数据输入FIFO
  * 
  * 参数:  Data:待处理消息的新数据。
  * 
  * 返回值: 无
  */
void HASH_DataIn(uint32_t Data) {
    /* 在 DIN寄存器中写入新数据 */
    HASH->DIN = Data;
}

/**
  * 简介:  返回已推入IN FIFO 的字数。
  * 
  * 参数:  无
  * 
  * 返回值: 已推入IN FIFO 的字的值。
  */
uint8_t HASH_GetInFIFOWordsNbr(void) {
    /* 返回NBW位的值 */
    return ((HASH->CR & HASH_CR_NBW) >> 8);
}

/**
  * 简介:  提供消息摘要结果。
  * 
  * 注意:   在MD5模式下，不使用 HASH_MsgDigest 结构的 Data[7]到Data[4]字段，并将其读取为零。
  *         在 SHA-1模式下，HASH_MsgDigest 结构的 Data[7]到Data[5]字段不使用，读取为零。
  *         在 SHA-224模式下，不使用 HASH_MsgDigest 结构的 Data[7]字段，读取为零。
  * 
  * 参数:  HASH_MessageDigest:指向将保存消息摘要结果的 HASH_MsgDigest 结构的指针
  * 
  * 返回值: 无
  */
void HASH_GetDigest(HASH_MsgDigest* HASH_MessageDigest) {
    /* 获取数据字段 */
    HASH_MessageDigest->Data[0] = HASH->HR[0];
    HASH_MessageDigest->Data[1] = HASH->HR[1];
    HASH_MessageDigest->Data[2] = HASH->HR[2];
    HASH_MessageDigest->Data[3] = HASH->HR[3];
    HASH_MessageDigest->Data[4] = HASH->HR[4];
    HASH_MessageDigest->Data[5] = HASH_DIGEST->HR[5];
    HASH_MessageDigest->Data[6] = HASH_DIGEST->HR[6];
    HASH_MessageDigest->Data[7] = HASH_DIGEST->HR[7];
}

/**
  * 简介:  开始填充消息并计算最终消息
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void HASH_StartDigest(void) {
    /* 启动摘要计算 */
    HASH->STR |= HASH_STR_DCAL;
}

/** @defgroup HASH_Group3上下文交换函数
 *  简介   上下文交换功能
 *
@verbatim
 ===============================================================================
                      ##### 上下文交换功能 #####
 ===============================================================================

 [..] 本节提供了允许保存和存储HASH上下文的函数

 [..] 可以中断HASH/HMAC 进程以执行具有较高优先级的另一个处理，
	并在较高优先级任务完成后完成中断的进程。
	为此，中断任务的上下文必须从HASH寄存器保存到内存，然后从内存恢复到HASH注册表。

   (#) 要保存当前上下文，请使用 HASH_SaveContext() 函数
   (#) 要还原保存的上下文，请使用 HASH_RestoreContext() 函数


@endverbatim
  */

/**
  * 简介:  保存哈希外设上下文。
  * 
  * 注意:   仅当当前未处理任何块时，才能保存上下文。
    *                  因此用户必须等待DINIS=1(最后一个块已处理，输入FIFO 为空)或NBW！=0(FIFO未满，未进行任何处理)。
    * 
  * 参数:  HASH_ContextSave: 指向包含当前上下文存储库的 HASH_Context 结构的指针。
  * 
  * 返回值: 无
  */
void HASH_SaveContext(HASH_Context* HASH_ContextSave) {
    uint8_t i = 0;

    /* 保存上下文寄存器 */
    HASH_ContextSave->HASH_IMR = HASH->IMR;
    HASH_ContextSave->HASH_STR = HASH->STR;
    HASH_ContextSave->HASH_CR  = HASH->CR;

    for(i = 0; i <= 53; i++) {
        HASH_ContextSave->HASH_CSR[i] = HASH->CSR[i];
    }
}

/**
  * 简介:  还原哈希外围上下文。
  * 
  * 注意:   调用此函数后，用户可以从中断点重新启动处理。
  * 
  * 参数:  HASH_ContextRestore: 指向包含已保存上下文的存储库的 HASH_Context 结构的指针。
  * 
  * 返回值: 无
  */
void HASH_RestoreContext(HASH_Context* HASH_ContextRestore) {
    uint8_t i = 0;

    /* 恢复上下文寄存器 */
    HASH->IMR = HASH_ContextRestore->HASH_IMR;
    HASH->STR = HASH_ContextRestore->HASH_STR;
    HASH->CR = HASH_ContextRestore->HASH_CR;

    /* 初始化哈希处理器 */
    HASH->CR |= HASH_CR_INIT;

    /* 继续恢复上下文寄存器 */
    for(i = 0; i <= 53; i++) {
        HASH->CSR[i] = HASH_ContextRestore->HASH_CSR[i];
    }
}

/** @defgroup HASH_Group4 HASH的 DMA 接口配置函数
 *  简介   HASH的 DMA 接口配置函数
 *
@verbatim
 ===============================================================================
               ##### HASH的 DMA 接口配置函数 #####
 ===============================================================================

 [..] 本节提供了允许为 HASH/HMAC 数据输入传输配置 DMA 接口的函数。

 [..] 启用 DMA 模式时(使用 HASH_DMACmd() 函数)，可以使用 DMA外设设备将数据发送到 IN FIFO。

@endverbatim
  */

/**
  * 简介:  启用或禁用 DMA 传输结束时自动启动消息填充和最终消息摘要的计算。
  * 
  * 参数:  NewState: 所选HASH DMA 传输请求的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void HASH_AutoStartDigest(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 在 DMA 传输结束时启用最终消息摘要的自动启动 */
        HASH->CR &= ~HASH_CR_MDMAT;
    } else {
        /* 在 DMA 传输结束时禁用最终消息摘要的自动启动 */
        HASH->CR |= HASH_CR_MDMAT;
    }
}

/**
  * 简介:  启用或禁用 HASH DMA 接口。
  * 
  * 注意:   DMA在传输结束后被硬件禁用。
  * 
  * 参数:  NewState: 所选HASH DMA 传输请求的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void HASH_DMACmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 HASH DMA 请求 */
        HASH->CR |= HASH_CR_DMAE;
    } else {
        /* 禁用 HASH DMA 请求 */
        HASH->CR &= ~HASH_CR_DMAE;
    }
}

/** @defgroup HASH_Group5中断和标志管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
               ##### 中断和标记管理函数 #####
 ===============================================================================

 [..] 本节提供了允许配置HASH中断、获取状态、清除标志和中断挂起位的函数。

 [..] HASH提供2个中断源和5个标志:

 *** 标志 : ***
 ===============
 [..]
   (#) HASH_FLAG_DINIS : 当 Data IN FIFO 中有16个位置空闲时设置，
	这意味着一个新的块(512位)可以进入输入缓冲区。。

   (#) HASH_FLAG_DCIS :  摘要计算完成时设置

   (#) HASH_FLAG_DMAS :  当HASH的 DMA 接口被启用(DMAE=1)或传输正在进行时设置。此标志仅由硬件清除。

   (#) HASH_FLAG_BUSY :  当散列核心正在处理数据块时设置此标志仅由硬件清除。

   (#) HASH_FLAG_DINNE : 当数据 IN FIFO不为空时设置，这意味着数据 IN FIVO至少包含一个数据字。此标志仅由硬件清除。

 *** 中断 : ***
 ====================
 [..]
   (#) HASH_IT_DINI  : 如果启用，当数据输入FIFO 中有16个位置空闲时，该中断源处于待定状态，
	这意味着可以将新块(512位)输入到输入缓冲器中。
	使用 HASH_ClearITPendingBit(HASH_IT_DINI) 函数清除此中断源。

   (#) HASH_IT_DCI   : 如果启用，则当摘要计算完成时，此中断源处于挂起状态。
	使用 HASH_ClearITPendingBit(HASH_IT_DCI) 函数清除此中断源。

 *** 管理HASH控制器事件 : ***
 =============================================
 [..] 用户应确定在其应用程序中将使用哪种模式来管理HASH控制器事件:轮询模式或中断模式。

   (#) 在轮询模式下，建议使用以下功能:
       (++) HASH_GetFlagStatus() : 以检查是否发生标志事件。
       (++) HASH_ClearFlag()     : 以清除标志事件。

   (#)  在中断模式下，建议使用以下功能:
       (++) HASH_ITConfig()       : 以启用或禁用中断源。
       (++) HASH_GetITStatus()    : 检查是否发生中断。
       (++) HASH_ClearITPendingBit() : 清除中断挂起位(相应标志)。

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 HASH中断。
  * 
  * 参数:  HASH_IT: 指定要启用或禁用的 HASH中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg HASH_IT_DINI: 数据输入中断
  *            @arg HASH_IT_DCI: 摘要计算完成中断
  * 
  * 参数:  NewState: 指定HASH中断的新状态。
  *           此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void HASH_ITConfig(uint32_t HASH_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_HASH_IT(HASH_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用所选HASH中断 */
        HASH->IMR |= HASH_IT;
    } else {
        /* 禁用所选HASH中断 */
        HASH->IMR &= (uint32_t)(~HASH_IT);
    }
}

/**
  * 简介:  检查是否设置了指定的 HASH标志。
  * 
  * 参数:  HASH_FLAG: 指定要检查的 HASH标志。
  *          此参数可以是以下值之一:
  *            @arg HASH_FLAG_DINIS: 数据输入中断状态标志
  *            @arg HASH_FLAG_DCIS: 摘要计算完成中断状态标志
  *            @arg HASH_FLAG_BUSY: Busy标志
  *            @arg HASH_FLAG_DMAS: DMAS状态标志
  *            @arg HASH_FLAG_DINNE: 数据输入寄存器(DIN)非空状态标志
  * 
  * 返回值: HASH_FLAG 的新状态(SET 或 RESET)
  */
FlagStatus HASH_GetFlagStatus(uint32_t HASH_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tempreg = 0;

    /* 检查参数 */
    assert_param(IS_HASH_GET_FLAG(HASH_FLAG));

    /* 检查FLAG是否在 CR 寄存器中 */
    if ((HASH_FLAG & HASH_FLAG_DINNE) != (uint32_t)RESET ) {
        tempreg = HASH->CR;
    } else { /* FLAG 在 SR 寄存器中 */
        tempreg = HASH->SR;
    }

    /* 检查指定HASH标志的状态 */
    if ((tempreg & HASH_FLAG) != (uint32_t)RESET) {
        /* HASH 被设置 */
        bitstatus = SET;
    } else {
        /* HASH_FLAG 复位 */
        bitstatus = RESET;
    }

    /* 返回HASH_FLAG状态 */
    return  bitstatus;
}
/**
  * 简介:  清除HASH标志。
  * 
  * 参数:  HASH_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *            @arg HASH_FLAG_DINIS: 数据输入标志
  *            @arg HASH_FLAG_DCIS: 摘要计算完成标志
  * 
  * 返回值: 无
  */
void HASH_ClearFlag(uint32_t HASH_FLAG) {
    /* 检查参数 */
    assert_param(IS_HASH_CLEAR_FLAG(HASH_FLAG));

    /* 清除选定的 HASH标志 */
    HASH->SR = ~(uint32_t)HASH_FLAG;
}
/**
  * 简介:  检查指定的 HASH中断是否发生。
  * 
  * 参数:  HASH_IT: 指定要检查的 HASH中断源。
  *          此参数可以是以下值之一:
  *            @arg HASH_IT_DINI: 数据输入中断
  *            @arg HASH_IT_DCI: 摘要计算完成中断
  * 
  * 返回值: HASH_IT 的新状态(SET 或 RESET)。
  */
ITStatus HASH_GetITStatus(uint32_t HASH_IT) {
    ITStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_HASH_GET_IT(HASH_IT));


    /* 检查指定HASH中断的状态 */
    tmpreg =  HASH->SR;

    if (((HASH->IMR & tmpreg) & HASH_IT) != RESET) {
        /* HASH_IT已设置 */
        bitstatus = SET;
    } else {
        /* HASH_IT重置 */
        bitstatus = RESET;
    }

    /* 返回HASH_IT状态 */
    return bitstatus;
}

/**
  * 简介:  清除HASH中断挂起位。
  * 
  * 参数:  HASH_IT: 指定要清除的 HASH中断挂起位。
  *          此参数可以是以下值的任意组合:
  *            @arg HASH_IT_DINI: 数据输入中断
  *            @arg HASH_IT_DCI: 摘要计算完成中断
  * 
  * 返回值: 无
  */
void HASH_ClearITPendingBit(uint32_t HASH_IT) {
    /* 检查参数 */
    assert_param(IS_HASH_IT(HASH_IT));

    /* 清除所选HASH中断挂起位 */
    HASH->SR = (uint32_t)(~HASH_IT);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
