/**
  ******************************************************************************
  * 文件:    stm32f4xx_cryp.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含加密处理器 (CRYP) 固件库的所有功能原型.
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

/* 定义以防止递归包含 -------------------------------------*/
#ifndef __STM32F4xx_CRYP_H
#define __STM32F4xx_CRYP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRYP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:    CRYP 初始化结构定义
  */
typedef struct {
    uint32_t CRYP_AlgoDir;   /*!< 加密或解密。 
                             该参数可以是@ref CRYP_Algorithm_Direction 的值 */

    uint32_t CRYP_AlgoMode;  /*!< TDES-ECB、TDES-CBC、DES-ECB、DES-CBC、AES-ECB、
                                AES-CBC、AES-CTR、AES-Key、AES-GCM 和 AES-CCM。
								             该参数可以是@ref CRYP_Algorithm_Mode 的值 */

    uint32_t CRYP_DataType;  /*!< 32 位数据、16 位数据、位数据或位串。
								             该参数可以是@ref CRYP_Data_Type 的值 */
                             
    uint32_t CRYP_KeySize;   /*!< 仅在 AES 模式下使用:128、192 或 256 位密钥长度。 
                             此参数可以是 @ref CRYP_Key_Size_for_AES_only 的值 */
} CRYP_InitTypeDef;

/**
  * 简介:    CRYP 密钥结构定义
  */
typedef struct {
    uint32_t CRYP_Key0Left;  /*!< Key 0 Left  */
    uint32_t CRYP_Key0Right; /*!< Key 0 Right */
    uint32_t CRYP_Key1Left;  /*!< Key 1 left  */
    uint32_t CRYP_Key1Right; /*!< Key 1 Right */
    uint32_t CRYP_Key2Left;  /*!< Key 2 left  */
    uint32_t CRYP_Key2Right; /*!< Key 2 Right */
    uint32_t CRYP_Key3Left;  /*!< Key 3 left  */
    uint32_t CRYP_Key3Right; /*!< Key 3 Right */
} CRYP_KeyInitTypeDef;
/**
  * 简介:    CRYP 初始化向量 (IV) 结构定义
  */
typedef struct {
    uint32_t CRYP_IV0Left;  /*!< Init Vector 0 Left  */
    uint32_t CRYP_IV0Right; /*!< Init Vector 0 Right */
    uint32_t CRYP_IV1Left;  /*!< Init Vector 1 left  */
    uint32_t CRYP_IV1Right; /*!< Init Vector 1 Right */
} CRYP_IVInitTypeDef;

/**
  * 简介:  CRYP 上下文交换结构定义
  */
typedef struct {
    /*!< 当前配置 */
    uint32_t CR_CurrentConfig;
    /*!< IV */
    uint32_t CRYP_IV0LR;
    uint32_t CRYP_IV0RR;
    uint32_t CRYP_IV1LR;
    uint32_t CRYP_IV1RR;
    /*!< KEY */
    uint32_t CRYP_K0LR;
    uint32_t CRYP_K0RR;
    uint32_t CRYP_K1LR;
    uint32_t CRYP_K1RR;
    uint32_t CRYP_K2LR;
    uint32_t CRYP_K2RR;
    uint32_t CRYP_K3LR;
    uint32_t CRYP_K3RR;
    uint32_t CRYP_CSGCMCCMR[8];
    uint32_t CRYP_CSGCMR[8];
} CRYP_Context;


/* Exported constants --------------------------------------------------------*/

/** @defgroup CRYP_Exported_Constants
  * @{
  */

/** @defgroup CRYP_Algorithm_Direction
  * @{
  */
#define CRYP_AlgoDir_Encrypt      ((uint16_t)0x0000)
#define CRYP_AlgoDir_Decrypt      ((uint16_t)0x0004)
#define IS_CRYP_ALGODIR(ALGODIR) (((ALGODIR) == CRYP_AlgoDir_Encrypt) || \
                                  ((ALGODIR) == CRYP_AlgoDir_Decrypt))

/**
  * @}
  */

/** @defgroup CRYP_Algorithm_Mode
  * @{
  */

/*!< TDES Modes */
#define CRYP_AlgoMode_TDES_ECB    ((uint32_t)0x00000000)
#define CRYP_AlgoMode_TDES_CBC    ((uint32_t)0x00000008)

/*!< DES Modes */
#define CRYP_AlgoMode_DES_ECB     ((uint32_t)0x00000010)
#define CRYP_AlgoMode_DES_CBC     ((uint32_t)0x00000018)

/*!< AES Modes */
#define CRYP_AlgoMode_AES_ECB     ((uint32_t)0x00000020)
#define CRYP_AlgoMode_AES_CBC     ((uint32_t)0x00000028)
#define CRYP_AlgoMode_AES_CTR     ((uint32_t)0x00000030)
#define CRYP_AlgoMode_AES_Key     ((uint32_t)0x00000038)
#define CRYP_AlgoMode_AES_GCM     ((uint32_t)0x00080000)
#define CRYP_AlgoMode_AES_CCM     ((uint32_t)0x00080008)

#define IS_CRYP_ALGOMODE(ALGOMODE) (((ALGOMODE) == CRYP_AlgoMode_TDES_ECB) || \
                                    ((ALGOMODE) == CRYP_AlgoMode_TDES_CBC)|| \
                                    ((ALGOMODE) == CRYP_AlgoMode_DES_ECB) || \
                                    ((ALGOMODE) == CRYP_AlgoMode_DES_CBC) || \
                                    ((ALGOMODE) == CRYP_AlgoMode_AES_ECB) || \
                                    ((ALGOMODE) == CRYP_AlgoMode_AES_CBC) || \
                                    ((ALGOMODE) == CRYP_AlgoMode_AES_CTR) || \
                                    ((ALGOMODE) == CRYP_AlgoMode_AES_Key) || \
                                    ((ALGOMODE) == CRYP_AlgoMode_AES_GCM) || \
                                    ((ALGOMODE) == CRYP_AlgoMode_AES_CCM))
/**
  * @}
  */

/** @defgroup CRYP_Phase
  * @{
  */

/*!< 相位仅对 AES-GCM 和 AES-CCM 模式有效 */
#define CRYP_Phase_Init           ((uint32_t)0x00000000)
#define CRYP_Phase_Header         CRYP_CR_GCM_CCMPH_0
#define CRYP_Phase_Payload        CRYP_CR_GCM_CCMPH_1
#define CRYP_Phase_Final          CRYP_CR_GCM_CCMPH

#define IS_CRYP_PHASE(PHASE) (((PHASE) == CRYP_Phase_Init)    || \
                              ((PHASE) == CRYP_Phase_Header)  || \
                              ((PHASE) == CRYP_Phase_Payload) || \
                              ((PHASE) == CRYP_Phase_Final))

/**
  * @}
  */

/** @defgroup CRYP_Data_Type
  * @{
  */
#define CRYP_DataType_32b         ((uint16_t)0x0000)
#define CRYP_DataType_16b         ((uint16_t)0x0040)
#define CRYP_DataType_8b          ((uint16_t)0x0080)
#define CRYP_DataType_1b          ((uint16_t)0x00C0)
#define IS_CRYP_DATATYPE(DATATYPE) (((DATATYPE) == CRYP_DataType_32b) || \
                                    ((DATATYPE) == CRYP_DataType_16b)|| \
                                    ((DATATYPE) == CRYP_DataType_8b)|| \
                                    ((DATATYPE) == CRYP_DataType_1b))
/**
  * @}
  */

/** @defgroup CRYP_Key_Size_for_AES_only
  * @{
  */
#define CRYP_KeySize_128b         ((uint16_t)0x0000)
#define CRYP_KeySize_192b         ((uint16_t)0x0100)
#define CRYP_KeySize_256b         ((uint16_t)0x0200)
#define IS_CRYP_KEYSIZE(KEYSIZE) (((KEYSIZE) == CRYP_KeySize_128b)|| \
                                  ((KEYSIZE) == CRYP_KeySize_192b)|| \
                                  ((KEYSIZE) == CRYP_KeySize_256b))
/**
  * @}
  */

/** @defgroup CRYP_flags_definition
  * @{
  */
#define CRYP_FLAG_BUSY            ((uint8_t)0x10)  /*!< CRYP 核心当前正在处理数据块或密钥准备(用于 AES 解密)。 */
#define CRYP_FLAG_IFEM            ((uint8_t)0x01)  /*!< 输入先进先出空 */
#define CRYP_FLAG_IFNF            ((uint8_t)0x02)  /*!< 输入 FIFO 未满 */
#define CRYP_FLAG_INRIS           ((uint8_t)0x22)  /*!< 原始中断挂起 */
#define CRYP_FLAG_OFNE            ((uint8_t)0x04)  /*!< 输入 FIFO 服务原始中断状态 */
#define CRYP_FLAG_OFFU            ((uint8_t)0x08)  /*!< 输出 FIFO 已满 */
#define CRYP_FLAG_OUTRIS          ((uint8_t)0x21)  /*!< 输出 FIFO 服务原始中断状态 */

#define IS_CRYP_GET_FLAG(FLAG) (((FLAG) == CRYP_FLAG_IFEM)  || \
                                ((FLAG) == CRYP_FLAG_IFNF)  || \
                                ((FLAG) == CRYP_FLAG_OFNE)  || \
                                ((FLAG) == CRYP_FLAG_OFFU)  || \
                                ((FLAG) == CRYP_FLAG_BUSY)  || \
                                ((FLAG) == CRYP_FLAG_OUTRIS)|| \
                                ((FLAG) == CRYP_FLAG_INRIS))
/**
  * @}
  */

/** @defgroup CRYP_interrupts_definition
  * @{
  */
#define CRYP_IT_INI               ((uint8_t)0x01) /*!< IN FIFO 中断 */
#define CRYP_IT_OUTI              ((uint8_t)0x02) /*!< OUT 先进先出中断 */
#define IS_CRYP_CONFIG_IT(IT) ((((IT) & (uint8_t)0xFC) == 0x00) && ((IT) != 0x00))
#define IS_CRYP_GET_IT(IT) (((IT) == CRYP_IT_INI) || ((IT) == CRYP_IT_OUTI))

/**
  * @}
  */

/** @defgroup CRYP_Encryption_Decryption_modes_definition
  * @{
  */
#define MODE_ENCRYPT             ((uint8_t)0x01)
#define MODE_DECRYPT             ((uint8_t)0x00)

/**
  * @}
  */

/** @defgroup CRYP_DMA_transfer_requests
  * @{
  */
#define CRYP_DMAReq_DataIN             ((uint8_t)0x01)
#define CRYP_DMAReq_DataOUT            ((uint8_t)0x02)
#define IS_CRYP_DMAREQ(DMAREQ) ((((DMAREQ) & (uint8_t)0xFC) == 0x00) && ((DMAREQ) != 0x00))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 CRYP 配置设置为默认复位状态的函数 ****/
void CRYP_DeInit(void);

/* CRYP 初始化和配置功能 ****************************/
void CRYP_Init(CRYP_InitTypeDef* CRYP_InitStruct); // 根据 CRYP_InitStruct 中指定的参数初始化 CRYP 外设。
void CRYP_StructInit(CRYP_InitTypeDef* CRYP_InitStruct); // 用默认值填充每个 CRYP_InitStruct 成员。
void CRYP_KeyInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct); // 根据 CRYP_KeyInitStruct 中指定的参数初始化 CRYP 密钥。
void CRYP_KeyStructInit(CRYP_KeyInitTypeDef* CRYP_KeyInitStruct); // 用默认值填充每个 CRYP_KeyInitStruct 成员。
void CRYP_IVInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct); // 根据 CRYP_IVInitStruct 中指定的参数初始化 CRYP 初始化向量 (IV)。
void CRYP_IVStructInit(CRYP_IVInitTypeDef* CRYP_IVInitStruct); // 用默认值填充每个 CRYP_IVInitStruct 成员。
void CRYP_Cmd(FunctionalState NewState); // 根据 CRYP_InitStruct 中指定的参数初始化 CRYP 外设。
void CRYP_PhaseConfig(uint32_t CRYP_Phase); // 配置 AES-CCM 和 AES-GCM 阶段。
void CRYP_FIFOFlush(void); // 刷新 IN 和 OUT FIFO(即 FIFO 的读写指针被复位)
/* CRYP 数据处理功能 *********************************************/
void CRYP_DataIn(uint32_t Data); // 将数据写入数据输入寄存器 (DIN)。
uint32_t CRYP_DataOut(void); // 返回最后输入到输出 FIFO 的数据。

/* CRYP 上下文交换功能 ********************************************/
ErrorStatus CRYP_SaveContext(CRYP_Context* CRYP_ContextSave,
                             CRYP_KeyInitTypeDef* CRYP_KeyInitStruct); // 保存 CRYP 外设设备上下文。
void CRYP_RestoreContext(CRYP_Context* CRYP_ContextRestore); // 恢复 CRYP 外设设备上下文。

/* CRYP DMA接口功能 ************************************************/
void CRYP_DMACmd(uint8_t CRYP_DMAReq, FunctionalState NewState); // 启用或禁用 CRYP DMA 接口。

/* 中断和标志管理功能 **********************************/
void CRYP_ITConfig(uint8_t CRYP_IT, FunctionalState NewState); // 启用或禁用指定的 CRYP 中断。
ITStatus CRYP_GetITStatus(uint8_t CRYP_IT); // 检查是否发生了指定的 CRYP 中断。
FunctionalState CRYP_GetCmdStatus(void); // 返回 CRYP 外设是启用还是禁用。
FlagStatus CRYP_GetFlagStatus(uint8_t CRYP_FLAG); // 检查是否设置了指定的 CRYP 标志。

/* 高级 AES 功能 **************************************************/
ErrorStatus CRYP_AES_ECB(uint8_t Mode,
                         uint8_t *Key, uint16_t Keysize,
                         uint8_t *Input, uint32_t Ilength,
                         uint8_t *Output); // 在 ECB 模式下使用 AES 进行加密和解密。

ErrorStatus CRYP_AES_CBC(uint8_t Mode,
                         uint8_t InitVectors[16],
                         uint8_t *Key, uint16_t Keysize,
                         uint8_t *Input, uint32_t Ilength,
                         uint8_t *Output); // 在 CBC 模式下使用 AES 进行加密和解密。

ErrorStatus CRYP_AES_CTR(uint8_t Mode,
                         uint8_t InitVectors[16],
                         uint8_t *Key, uint16_t Keysize,
                         uint8_t *Input, uint32_t Ilength,
                         uint8_t *Output); // 在 CTR 模式下使用 AES 进行加密和解密。

ErrorStatus CRYP_AES_GCM(uint8_t Mode, uint8_t InitVectors[16],
                         uint8_t *Key, uint16_t Keysize,
                         uint8_t *Input, uint32_t ILength,
                         uint8_t *Header, uint32_t HLength,
                         uint8_t *Output, uint8_t *AuthTAG); // 在 GCM 模式下使用 AES 进行加密和解密。

ErrorStatus CRYP_AES_CCM(uint8_t Mode,
                         uint8_t* Nonce, uint32_t NonceSize,
                         uint8_t* Key, uint16_t Keysize,
                         uint8_t* Input, uint32_t ILength,
                         uint8_t* Header, uint32_t HLength, uint8_t *HBuffer,
                         uint8_t* Output,
                         uint8_t* AuthTAG, uint32_t TAGSize); // 在 CCM 模式下使用 AES 进行加密和解密。

/* 高级 TDES 功能 **************************************************/
ErrorStatus CRYP_TDES_ECB(uint8_t Mode,
                          uint8_t Key[24],
                          uint8_t *Input, uint32_t Ilength,
                          uint8_t *Output); // 在 ECB 模式下使用 TDES 进行加密和解密。

ErrorStatus CRYP_TDES_CBC(uint8_t Mode,
                          uint8_t Key[24],
                          uint8_t InitVectors[8],
                          uint8_t *Input, uint32_t Ilength,
                          uint8_t *Output); // 在 CBC 模式下使用 TDES 进行加密和解密。

/* 高级 DES 功能 **************************************************/
ErrorStatus CRYP_DES_ECB(uint8_t Mode,
                         uint8_t Key[8],
                         uint8_t *Input, uint32_t Ilength,
                         uint8_t *Output); // 在 ECB 模式下使用 DES 进行加密和解密。

ErrorStatus CRYP_DES_CBC(uint8_t Mode,
                         uint8_t Key[8],
                         uint8_t InitVectors[8],
                         uint8_t *Input, uint32_t Ilength,
                         uint8_t *Output); // 在 CBC 模式下使用 DES 进行加密和解密。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_CRYP_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
