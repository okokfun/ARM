/**
  ******************************************************************************
  * 文件:    stm32f4xx_hash.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 HASH 固件库的所有函数原型.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_HASH_H
#define __STM32F4xx_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup HASH
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:    HASH初始化结构定义
  */
typedef struct {
    uint32_t HASH_AlgoSelection; /*!< SHA-1、SHA-224、SHA-256 或 MD5。
									               该参数可以是 @ref HASH_Algo_Selection 的值 */

    uint32_t HASH_AlgoMode;      /*!< 哈希或 HMAC。
									               该参数可以是 @ref HASH_processor_Algorithm_Mode 的值 */

    uint32_t HASH_DataType;      /*!< 32 位数据、16 位数据、8 位数据或位串。
									               该参数可以是 @ref HASH_Data_Type 的值 */
                                 
    uint32_t HASH_HMACKeyType;   /*!< HMAC 短密钥或 HMAC 长密钥。
									               该参数可以是 @ref HASH_HMAC_Long_key_only_for_HMAC_mode 的值 */
} HASH_InitTypeDef;

/**
  * 简介:  HASH消息摘要结果结构定义
  */
typedef struct {
    uint32_t Data[8];      /*!< 消息摘要结果:SHA-256 8x 32bit wors，
                                                       SHA-224 7x 32bit wors，
                                                       SHA-1 的 5 个 32 位字或
                                                       MD5 的 4 个 32 位字  */
} HASH_MsgDigest;

/**
  * 简介:  HASH上下文交换结构定义
  */
typedef struct {
    uint32_t HASH_IMR;
    uint32_t HASH_STR;
    uint32_t HASH_CR;
    uint32_t HASH_CSR[54];
} HASH_Context;

/* Exported constants --------------------------------------------------------*/

/** @defgroup HASH_Exported_Constants
  */

/** @defgroup HASH_Algo_Selection
  */
#define HASH_AlgoSelection_SHA1      ((uint32_t)0x0000) /*!< HASH 函数是 SHA1   */
#define HASH_AlgoSelection_SHA224    HASH_CR_ALGO_1     /*!< HASH 函数是 SHA224 */
#define HASH_AlgoSelection_SHA256    HASH_CR_ALGO       /*!< HASH 函数是 SHA256 */
#define HASH_AlgoSelection_MD5       HASH_CR_ALGO_0     /*!< HASH 函数是 is MD5    */
#define IS_HASH_ALGOSELECTION(ALGOSELECTION) (((ALGOSELECTION) == HASH_AlgoSelection_SHA1) || \
        ((ALGOSELECTION) == HASH_AlgoSelection_SHA224) || \
        ((ALGOSELECTION) == HASH_AlgoSelection_SHA256) || \
        ((ALGOSELECTION) == HASH_AlgoSelection_MD5))

/** @defgroup HASH_processor_Algorithm_Mode
  */
#define HASH_AlgoMode_HASH         ((uint32_t)0x00000000) /*!< 算法是HASH */
#define HASH_AlgoMode_HMAC         HASH_CR_MODE           /*!< 算法是HMAC */

#define IS_HASH_ALGOMODE(ALGOMODE) (((ALGOMODE) == HASH_AlgoMode_HASH) || \
                                    ((ALGOMODE) == HASH_AlgoMode_HMAC))

/** @defgroup HASH_Data_Type
  */
#define HASH_DataType_32b          ((uint32_t)0x0000) /*!< 32 位数据。 无交换                     */
#define HASH_DataType_16b          HASH_CR_DATATYPE_0 /*!< 16 位数据。 每个半字被交换       */
#define HASH_DataType_8b           HASH_CR_DATATYPE_1 /*!< 8 位数据。 所有字节都被交换           */
#define HASH_DataType_1b           HASH_CR_DATATYPE   /*!< 1 位数据。 在单词中所有位都被交换 */

#define IS_HASH_DATATYPE(DATATYPE) (((DATATYPE) == HASH_DataType_32b)|| \
                                    ((DATATYPE) == HASH_DataType_16b)|| \
                                    ((DATATYPE) == HASH_DataType_8b) || \
                                    ((DATATYPE) == HASH_DataType_1b))

/** @defgroup HASH_HMAC_Long_key_only_for_HMAC_mode
  */
#define HASH_HMACKeyType_ShortKey      ((uint32_t)0x00000000) /*!< HMAC 密钥 <= 64 字节 */
#define HASH_HMACKeyType_LongKey       HASH_CR_LKEY           /*!< HMAC 密钥 > 64 字节  */
#define IS_HASH_HMAC_KEYTYPE(KEYTYPE) (((KEYTYPE) == HASH_HMACKeyType_ShortKey) || \
                                       ((KEYTYPE) == HASH_HMACKeyType_LongKey))

/** @defgroup Number_of_valid_bits_in_last_word_of_the_message
  */
#define IS_HASH_VALIDBITSNUMBER(VALIDBITS) ((VALIDBITS) <= 0x1F)


/** @defgroup HASH_interrupts_definition
  */
#define HASH_IT_DINI               HASH_IMR_DINIM  /*!< 可以将新块输入到输入缓冲区 (DIN) */
#define HASH_IT_DCI                HASH_IMR_DCIM   /*!< 摘要计算完成                            */
#define IS_HASH_IT(IT) ((((IT) & (uint32_t)0xFFFFFFFC) == 0x00000000) && ((IT) != 0x00000000))
#define IS_HASH_GET_IT(IT) (((IT) == HASH_IT_DINI) || ((IT) == HASH_IT_DCI))


/** @defgroup HASH_flags_definition
  */
#define HASH_FLAG_DINIS            HASH_SR_DINIS  /*!< 16 个位置在 DIN 中是空闲的:可以将一个新块输入到输入缓冲区中 */
#define HASH_FLAG_DCIS             HASH_SR_DCIS   /*!< 摘要计算完成                                            */
#define HASH_FLAG_DMAS             HASH_SR_DMAS   /*!< 启用 DMA 接口 (DMAE=1) 或正在进行传输                    */
#define HASH_FLAG_BUSY             HASH_SR_BUSY   /*!< 哈希核心忙: 处理数据块                                   */
#define HASH_FLAG_DINNE            HASH_CR_DINNE  /*!< DIN 非空:输入缓冲区至少包含一个字的数据                   */
#define IS_HASH_GET_FLAG(FLAG) (((FLAG) == HASH_FLAG_DINIS) || \
                                ((FLAG) == HASH_FLAG_DCIS)  || \
                                ((FLAG) == HASH_FLAG_DMAS)  || \
                                ((FLAG) == HASH_FLAG_BUSY)  || \
                                ((FLAG) == HASH_FLAG_DINNE))

#define IS_HASH_CLEAR_FLAG(FLAG)(((FLAG) == HASH_FLAG_DINIS) || \
                                 ((FLAG) == HASH_FLAG_DCIS))



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 HASH 配置设置为默认重置状态的函数 ****/
void HASH_DeInit(void); // 将 HASH 外设寄存器取消初始化为其默认复位值。

/* HASH 配置功能 ************************************************/
void HASH_Init(HASH_InitTypeDef* HASH_InitStruct); // 根据HASH_InitStruct结构中的指定参数初始化 HASH 外设。
void HASH_StructInit(HASH_InitTypeDef* HASH_InitStruct); // 用每个HASH_InitStruct成员的默认值填充该成员。
void HASH_Reset(void); // 重置 HASH 处理器内核，以便 HASH 准备好计算新消息的消息摘要。

/* HASH 消息摘要生成功能 ***********************************/
void HASH_DataIn(uint32_t Data); // 在数据输入 FIFO 中写入数据。
uint8_t HASH_GetInFIFOWordsNbr(void); // 返回已推送到 IN FIFO 中的字数。
void HASH_SetLastWordValidBitsNbr(uint16_t ValidNumber); // 配置消息最后一个字中的有效位数。
void HASH_StartDigest(void); // 启动消息填充和最终消息的计算。
void HASH_AutoStartDigest(FunctionalState NewState); // 启用或禁用自动启动消息填充和在 DMA 传输结束时计算最终消息摘要。
void HASH_GetDigest(HASH_MsgDigest* HASH_MessageDigest); // 提供消息摘要结果。

/* HASH 上下文交换功能 ********************************************/
void HASH_SaveContext(HASH_Context* HASH_ContextSave); // 保存哈希外围上下文。
void HASH_RestoreContext(HASH_Context* HASH_ContextRestore); // 还原哈希外围上下文。

/* HASH DMA 接口功能 ************************************************/
void HASH_DMACmd(FunctionalState NewState); // 启用或禁用哈希 DMA 接口。

/* HASH 中断和标志管理功能 *****************************/
void HASH_ITConfig(uint32_t HASH_IT, FunctionalState NewState); // 启用或禁用指定的 HASH 中断
FlagStatus HASH_GetFlagStatus(uint32_t HASH_FLAG); // 检查是否设置了指定的 HASH 标志。
void HASH_ClearFlag(uint32_t HASH_FLAG); // 清除哈希标志。
ITStatus HASH_GetITStatus(uint32_t HASH_IT); // 检查指定的 HASH 中断是否发生。
void HASH_ClearITPendingBit(uint32_t HASH_IT); // 清除哈希中断挂起位。

/* 高级 SHA1 功能 **************************************************/
ErrorStatus HASH_SHA1(uint8_t *Input, uint32_t Ilen, uint8_t Output[20]); // 计算哈希 SHA1 摘要。
ErrorStatus HMAC_SHA1(uint8_t *Key, uint32_t Keylen,
                      uint8_t *Input, uint32_t Ilen,
                      uint8_t Output[20]); // 计算 HMAC SHA1 摘要。

/* 高级 MD5 功能 ***************************************************/
ErrorStatus HASH_MD5(uint8_t *Input, uint32_t Ilen, uint8_t Output[16]); // 计算HASH MD5 摘要。
ErrorStatus HMAC_MD5(uint8_t *Key, uint32_t Keylen,
                     uint8_t *Input, uint32_t Ilen,
                     uint8_t Output[16]); // 计算 HMAC MD5 摘要。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_HASH_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
