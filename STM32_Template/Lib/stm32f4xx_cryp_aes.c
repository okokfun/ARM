/**
  ******************************************************************************
  * 文件:    stm32f4xx_cryp_aes.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供高级功能，用于在 ECB/CBC/CTR/GCM/CCM 模式下使用 AES 加密和解密输入消息。
  *          它使用 stm32f4xx_cryp.c/.h 驱动程序来访问 STM32F4xx CRYP 外设。
  *          AES-ECB/CBC/CTR/GCM/CCM 模式在 STM32F437x 器件上可用。
  *          对于 STM32F41xx 器件，只有 AES-ECB/CBC/CTR 模式可用。
  *
@verbatim
 ===================================================================
                  ##### 如何使用此驱动程序 #####
 ===================================================================
 [..]
   (#) 使用 RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_CRYP, ENABLE) 启用 CRYP 控制器时钟.

   (#) 使用 CRYP_AES_ECB() 函数在 ECB 模式下使用 AES 进行加密和解密。

   (#) 使用 CRYP_AES_CBC() 函数在 CBC 模式下使用 AES 进行加密和解密。

   (#) 使用 CRYP_AES_CTR() 函数在 CTR 模式下使用 AES 进行加密和解密。

   (#) 使用 CRYP_AES_GCM() 函数在 GCM 模式下使用 AES 进行加密和解密。

   (#) 使用 CRYP_AES_CCM() 函数在 CCM 模式下使用 AES 进行加密和解密。

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

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup CRYP
  * 简介: CRYP 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define AESBUSY_TIMEOUT    ((uint32_t) 0x00010000)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup CRYP_Private_Functions
  */

/** @defgroup CRYP_Group6 高水平的 AES功能
 *  简介   高水平的 AES功能
 *
@verbatim
 ===============================================================================
                       ##### 高水平的 AES功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  在 ECB 模式下使用 AES 进行加密和解密。
  * 
  * 参数:  Mode: 加密或解密模式。
  *          此参数可以是以下值之一:
  *            @arg MODE_ENCRYPT: 加密
  *            @arg MODE_DECRYPT: 解密
  * 
  * 参数:  Key: 用于AES 算法的密钥。
  * 
  * 参数:  Keysize: 密钥的长度必须为128、192 或256。
  * 
  * 参数:  Input: 指向输入缓冲区的指针。
  * 
  * 参数:  Ilength: 输入缓冲区的长度必须是16的倍数。
  * 
  * 参数:  Output: 指向返回缓冲区的指针。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: 操作已完成
  *          - ERROR: 操作失败
  */
ErrorStatus CRYP_AES_ECB(uint8_t Mode, uint8_t* Key, uint16_t Keysize,
                         uint8_t* Input, uint32_t Ilength, uint8_t* Output) {
    CRYP_InitTypeDef AES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef AES_CRYP_KeyInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    uint32_t i = 0;

    /* 加密数据结构初始化 */
    CRYP_KeyStructInit(&AES_CRYP_KeyInitStructure);

    switch(Keysize) {
        case 128:
            AES_CRYP_InitStructure.CRYP_KeySize = CRYP_KeySize_128b;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 192:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_192b;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 256:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_256b;
            AES_CRYP_KeyInitStructure.CRYP_Key0Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key0Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        default:
            break;
    }

    /*------------------ AES解密 ------------------*/
    if(Mode == MODE_DECRYPT) { /* AES解密 */
        /* Flush IN/OUT FIFOs */
        CRYP_FIFOFlush();

        /* 用于解密过程密钥准备的加密初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_Key;
        AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_32b;
        CRYP_Init(&AES_CRYP_InitStructure);

        /* 密钥初始化 */
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        /* 等到Busy标志被重置 */
        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

        if (busystatus != RESET) {
            status = ERROR;
        } else {
            /* 用于解密过程的加密初始化 */
            AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        }
    }
    /*------------------ AES加密 ------------------*/
    else { /* AES加密 */

        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

        /* Crypto加密进程的初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir  = CRYP_AlgoDir_Encrypt;
    }

    AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_ECB;
    AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&AES_CRYP_InitStructure);

    /* Flush IN/OUT FIFOs */
    CRYP_FIFOFlush();

    /* 启用加密处理器 */
    CRYP_Cmd(ENABLE);

    if(CRYP_GetCmdStatus() == DISABLE) {
        /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
        return(ERROR);
    }

    for(i = 0; ((i < Ilength) && (status != ERROR)); i += 16) {

        /* 在 IN FIFO 中写入输入块 */
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;

        /* 等待，直到完整的信息被处理完毕 */
        counter = 0;

        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

        if (busystatus != RESET) {
            status = ERROR;
        } else {

            /* 从输出FIFO 中读取输出块 */
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
        }
    }

    /* 禁用加密 */
    CRYP_Cmd(DISABLE);

    return status;
}

/**
  * 简介:  在 CBC 模式下使用 AES 进行加密和解密。
  * 
  * 参数:  Mode: 加密或解密模式。
  *          此参数可以是以下值之一:
  *            @arg MODE_ENCRYPT:加密
  *            @arg MODE_DECRYPT:解密
  * 
  * 参数:  InitVectors: 用于AES 算法的初始化矢量。
  * 
  * 参数:  Key: 用于AES 算法的密钥。
  * 
  * 参数:  Keysize: 密钥的长度必须为128、192 或256。
  * 
  * 参数:  Input: 指向输入缓冲区的指针。
  * 
  * 参数:  Ilength: 输入缓冲区的长度必须是 16 的倍数。
  * 
  * 参数:  Output: 指向返回缓冲区的指针。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: 操作已完成
  *          - ERROR: 操作失败
  */
ErrorStatus CRYP_AES_CBC(uint8_t Mode, uint8_t InitVectors[16], uint8_t *Key,
                         uint16_t Keysize, uint8_t *Input, uint32_t Ilength,
                         uint8_t *Output) {
    CRYP_InitTypeDef AES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef AES_CRYP_KeyInitStructure;
    CRYP_IVInitTypeDef AES_CRYP_IVInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    uint32_t ivaddr = (uint32_t)InitVectors;
    uint32_t i = 0;

    /* 加密数据结构初始化 */
    CRYP_KeyStructInit(&AES_CRYP_KeyInitStructure);

    switch(Keysize) {
        case 128:
            AES_CRYP_InitStructure.CRYP_KeySize = CRYP_KeySize_128b;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 192:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_192b;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 256:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_256b;
            AES_CRYP_KeyInitStructure.CRYP_Key0Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key0Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        default:
            break;
    }

    /* CRYP 初始化 Vectors */
    AES_CRYP_IVInitStructure.CRYP_IV0Left = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV0Right = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Left = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Right = __REV(*(uint32_t*)(ivaddr));


    /*------------------ AES解密 ------------------*/
    if(Mode == MODE_DECRYPT) { /* AES解密 */
        /* Flush IN/OUT FIFOs */
        CRYP_FIFOFlush();

        /* 用于解密过程密钥准备的加密初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_Key;
        AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_32b;

        CRYP_Init(&AES_CRYP_InitStructure);

        /* 密钥初始化 */
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        /* 等到Busy标志被重置 */
        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

        if (busystatus != RESET) {
            status = ERROR;
        } else {
            /* 用于解密过程的加密初始化 */
            AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        }
    }
    /*------------------ AES加密 ------------------*/
    else { /* AES加密 */
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

        /* Crypto加密进程的初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir  = CRYP_AlgoDir_Encrypt;
    }

    AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_CBC;
    AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&AES_CRYP_InitStructure);

    /* CRYP 初始化 Vectors */
    CRYP_IVInit(&AES_CRYP_IVInitStructure);

    /* Flush IN/OUT FIFOs */
    CRYP_FIFOFlush();

    /* 启用加密处理器 */
    CRYP_Cmd(ENABLE);

    if(CRYP_GetCmdStatus() == DISABLE) {
        /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
        return(ERROR);
    }

    for(i = 0; ((i < Ilength) && (status != ERROR)); i += 16) {

        /* 在 IN FIFO 中写入输入块 */
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        /* 等待，直到完整的信息被处理完毕 */
        counter = 0;

        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

        if (busystatus != RESET) {
            status = ERROR;
        } else {

            /* 从输出FIFO 中读取输出块 */
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
        }
    }

    /* 禁用加密 */
    CRYP_Cmd(DISABLE);

    return status;
}

/**
  * 简介:  在 CTR 模式下使用 AES 进行加密和解密。
  * 
  * 参数:  Mode: 加密或解密模式。
  *           此参数可以是以下值之一:
  *            @arg MODE_ENCRYPT: 加密
  *            @arg MODE_DECRYPT: 解密
  * 
  * 参数:  InitVectors: 用于AES 算法的初始化矢量。
  * 
  * 参数:  Key: 用于AES 算法的密钥。
  * 
  * 参数:  Keysize: 密钥的长度必须为128、192 或256。
  * 
  * 参数:  Input: 指向输入缓冲区的指针。
  * 
  * 参数:  Ilength: 输入缓冲区的长度必须是16的倍数。
  * 
  * 参数:  Output: 指向返回缓冲区的指针。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS	: 操作已完成
  *          - ERROR	: 操作失败
  */
ErrorStatus CRYP_AES_CTR(uint8_t Mode, uint8_t InitVectors[16], uint8_t *Key,
                         uint16_t Keysize, uint8_t *Input, uint32_t Ilength,
                         uint8_t *Output) {
    CRYP_InitTypeDef AES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef AES_CRYP_KeyInitStructure;
    CRYP_IVInitTypeDef AES_CRYP_IVInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    uint32_t ivaddr     = (uint32_t)InitVectors;
    uint32_t i = 0;

    /* 加密数据结构初始化 */
    CRYP_KeyStructInit(&AES_CRYP_KeyInitStructure);

    switch(Keysize) {
        case 128:
            AES_CRYP_InitStructure.CRYP_KeySize = CRYP_KeySize_128b;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 192:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_192b;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 256:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_256b;
            AES_CRYP_KeyInitStructure.CRYP_Key0Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key0Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        default:
            break;
    }

    /* CRYP 初始化 Vectors */
    AES_CRYP_IVInitStructure.CRYP_IV0Left = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV0Right = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Left = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Right = __REV(*(uint32_t*)(ivaddr));

    /* 密钥初始化 */
    CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

    /*------------------ AES解密 ------------------*/
    if(Mode == MODE_DECRYPT) { /* AES解密 */
        /* 用于解密过程的加密初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
    }
    /*------------------ AES加密 ------------------*/
    else { /* AES加密 */
        /* Crypto加密进程的初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
    }

    AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_CTR;
    AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&AES_CRYP_InitStructure);

    /* CRYP 初始化 Vectors */
    CRYP_IVInit(&AES_CRYP_IVInitStructure);

    /* Flush IN/OUT FIFOs */
    CRYP_FIFOFlush();

    /* 启用加密处理器 */
    CRYP_Cmd(ENABLE);

    if(CRYP_GetCmdStatus() == DISABLE) {
        /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
        return(ERROR);
    }

    for(i = 0; ((i < Ilength) && (status != ERROR)); i += 16) {

        /* 在 IN FIFO 中写入输入块 */
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        CRYP_DataIn(*(uint32_t*)(inputaddr));
        inputaddr += 4;
        /* 等待，直到完整的信息被处理完毕 */
        counter = 0;

        do {
            busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
            counter++;
        } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

        if (busystatus != RESET) {
            status = ERROR;
        } else {

            /* 从输出FIFO 中读取输出块 */
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
            *(uint32_t*)(outputaddr) = CRYP_DataOut();
            outputaddr += 4;
        }
    }

    /* 禁用加密 */
    CRYP_Cmd(DISABLE);

    return status;
}

/**
  * 简介:  在 GCM 模式下使用 AES 进行加密和解密。GCM 和 CCM 模式仅在 STM32F437x 设备上可用。
  * 
  * 参数:  Mode: 加密或解密模式。
  *          此参数可以是以下值之一:
  *            @arg MODE_ENCRYPT: 加密
  *            @arg MODE_DECRYPT: 解密
  * 
  * 参数:  InitVectors: 用于AES 算法的初始化矢量。
  * 
  * 参数:  Key: 用于AES 算法的密钥。
  * 
  * 参数:  Keysize: 密钥的长度必须为128、192 或256。
  * 
  * 参数:  Input: 指向输入缓冲区的指针。
  * 
  * 参数:  Ilength: 输入缓冲区的长度(以字节为单位)必须是 16 的倍数。
  * 
  * 参数:  Header: 指向头缓冲区的指针。
  * 
  * 参数:  Hlength: 头部缓冲区的长度，单位是字节，必须是 16 的倍数。
  * 参数:  Output: 指向返回缓冲区的指针。
  * 
  * 参数:  AuthTAG: 指向认证TAG缓冲区的指针。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: 操作已完成
  *          - ERROR: 操作失败
  */
ErrorStatus CRYP_AES_GCM(uint8_t Mode, uint8_t InitVectors[16],
                         uint8_t *Key, uint16_t Keysize,
                         uint8_t *Input, uint32_t ILength,
                         uint8_t *Header, uint32_t HLength,
                         uint8_t *Output, uint8_t *AuthTAG) {
    CRYP_InitTypeDef AES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef AES_CRYP_KeyInitStructure;
    CRYP_IVInitTypeDef AES_CRYP_IVInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    uint32_t ivaddr     = (uint32_t)InitVectors;
    uint32_t headeraddr = (uint32_t)Header;
    uint32_t tagaddr = (uint32_t)AuthTAG;
    uint64_t headerlength = HLength * 8;/* header length in 位 */
    uint64_t inputlength = ILength * 8;/* input length in 位 */
    uint32_t loopcounter = 0;

    /* 加密数据结构初始化 */
    CRYP_KeyStructInit(&AES_CRYP_KeyInitStructure);

    switch(Keysize) {
        case 128:
            AES_CRYP_InitStructure.CRYP_KeySize = CRYP_KeySize_128b;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 192:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_192b;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 256:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_256b;
            AES_CRYP_KeyInitStructure.CRYP_Key0Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key0Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        default:
            break;
    }

    /* CRYP 初始化 Vectors */
    AES_CRYP_IVInitStructure.CRYP_IV0Left = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV0Right = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Left = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Right = __REV(*(uint32_t*)(ivaddr));

    /*------------------ AES加密 ------------------*/
    if(Mode == MODE_ENCRYPT) { /* AES加密 */
        /* Flush IN/OUT FIFOs */
        CRYP_FIFOFlush();

        /* 密钥初始化 */
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

        /* CRYP 初始化 Vectors */
        CRYP_IVInit(&AES_CRYP_IVInitStructure);

        /* 用于解密过程密钥准备的加密初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
        AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_GCM;
        AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
        CRYP_Init(&AES_CRYP_InitStructure);

        /***************************** 初始阶段 *********************************/
        /* 选择初始化阶段 */
        CRYP_PhaseConfig(CRYP_Phase_Init);

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        /* 等待密码位为0 */
        while(CRYP_GetCmdStatus() == ENABLE) {
        }

        /***************************** 头部阶段 *******************************/
        if(HLength != 0) {
            /* 选择头部阶段 */
            CRYP_PhaseConfig(CRYP_Phase_Header);

            /* 启用加密处理器 */
            CRYP_Cmd(ENABLE);

            if(CRYP_GetCmdStatus() == DISABLE) {
                /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
                return(ERROR);
            }

            for(loopcounter = 0; (loopcounter < HLength); loopcounter += 16) {
                /* 等待IFEM标志被重置 */
                while(CRYP_GetFlagStatus(CRYP_FLAG_IFEM) == RESET) {
                }

                /* 在 IN FIFO 中写入输入块 */
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
            }

            /* 等待，直到完整的信息被处理完毕 */
            counter = 0;

            do {
                busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                counter++;
            } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

            if (busystatus != RESET) {
                status = ERROR;
            }
        }

        /**************************** 有效负载阶段 *******************************/
        if(ILength != 0) {
            /* 选择有效负载阶段 */
            CRYP_PhaseConfig(CRYP_Phase_Payload);

            /* 启用加密处理器 */
            CRYP_Cmd(ENABLE);

            if(CRYP_GetCmdStatus() == DISABLE) {
                /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
                return(ERROR);
            }

            for(loopcounter = 0; ((loopcounter < ILength) && (status != ERROR)); loopcounter += 16) {
                /* 等待IFEM标志被重置 */
                while(CRYP_GetFlagStatus(CRYP_FLAG_IFEM) == RESET) {
                }

                /* 在 IN FIFO 中写入输入块 */
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;

                /* 等待，直到完整的信息被处理完毕 */
                counter = 0;

                do {
                    busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                    counter++;
                } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

                if (busystatus != RESET) {
                    status = ERROR;
                } else {
                    /* 等待OFNE标志被重置 */
                    while(CRYP_GetFlagStatus(CRYP_FLAG_OFNE) == RESET) {
                    }

                    /* 从输出FIFO 中读取输出块 */
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                }
            }
        }

        /***************************** 最后阶段 ********************************/
        /* 选择最后阶段 */
        CRYP_PhaseConfig(CRYP_Phase_Final);

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        if(CRYP_GetCmdStatus() == DISABLE) {
            /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
            return(ERROR);
        }

        /* 写入 FIFO 中与头连接的位数 */
        CRYP_DataIn(__REV(headerlength >> 32));
        CRYP_DataIn(__REV(headerlength));
        CRYP_DataIn(__REV(inputlength >> 32));
        CRYP_DataIn(__REV(inputlength));

        /* 等待OFNE标志被重置 */
        while(CRYP_GetFlagStatus(CRYP_FLAG_OFNE) == RESET) {
        }

        tagaddr = (uint32_t)AuthTAG;
        /* 读取IN FIFO 中的 Auth TAG。 */
        *(uint32_t*)(tagaddr) = CRYP_DataOut();
        tagaddr += 4;
        *(uint32_t*)(tagaddr) = CRYP_DataOut();
        tagaddr += 4;
        *(uint32_t*)(tagaddr) = CRYP_DataOut();
        tagaddr += 4;
        *(uint32_t*)(tagaddr) = CRYP_DataOut();
        tagaddr += 4;
    }
    /*------------------ AES解密 ------------------*/
    else { /* AES解密 */
        /* Flush IN/OUT FIFOs */
        CRYP_FIFOFlush();

        /* 密钥初始化 */
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

        /* CRYP 初始化 Vectors */
        CRYP_IVInit(&AES_CRYP_IVInitStructure);

        /* 用于解密过程密钥准备的加密初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_GCM;
        AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
        CRYP_Init(&AES_CRYP_InitStructure);

        /***************************** 初始阶段 *********************************/
        /* 选择初始化阶段 */
        CRYP_PhaseConfig(CRYP_Phase_Init);

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        /* 等待密码位为0 */
        while(CRYP_GetCmdStatus() == ENABLE) {
        }

        /***************************** 头部阶段 *******************************/
        if(HLength != 0) {
            /* 选择头部阶段 */
            CRYP_PhaseConfig(CRYP_Phase_Header);

            /* 启用加密处理器 */
            CRYP_Cmd(ENABLE);

            if(CRYP_GetCmdStatus() == DISABLE) {
                /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
                return(ERROR);
            }

            for(loopcounter = 0; (loopcounter < HLength); loopcounter += 16) {
                /* 等待IFEM标志被重置 */
                while(CRYP_GetFlagStatus(CRYP_FLAG_IFEM) == RESET) {
                }

                /* 在 IN FIFO 中写入输入块 */
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
            }

            /* 等待，直到完整的信息被处理完毕 */
            counter = 0;

            do {
                busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                counter++;
            } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

            if (busystatus != RESET) {
                status = ERROR;
            }
        }

        /**************************** 有效负载阶段 *******************************/
        if(ILength != 0) {
            /* 选择有效负载阶段 */
            CRYP_PhaseConfig(CRYP_Phase_Payload);

            /* 启用加密处理器 */
            CRYP_Cmd(ENABLE);

            if(CRYP_GetCmdStatus() == DISABLE) {
                /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
                return(ERROR);
            }

            for(loopcounter = 0; ((loopcounter < ILength) && (status != ERROR)); loopcounter += 16) {
                /* 等待IFEM标志被重置 */
                while(CRYP_GetFlagStatus(CRYP_FLAG_IFEM) == RESET) {
                }

                /* 在 IN FIFO 中写入输入块 */
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;

                /* 等待，直到完整的信息被处理完毕 */
                counter = 0;

                do {
                    busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                    counter++;
                } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

                if (busystatus != RESET) {
                    status = ERROR;
                } else {
                    /* 等待OFNE标志被重置 */
                    while(CRYP_GetFlagStatus(CRYP_FLAG_OFNE) == RESET) {
                    }

                    /* 从输出FIFO 中读取输出块 */
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                }
            }
        }

        /***************************** 最后阶段 ********************************/
        /* 选择最后阶段 */
        CRYP_PhaseConfig(CRYP_Phase_Final);

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        if(CRYP_GetCmdStatus() == DISABLE) {
            /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
            return(ERROR);
        }

        /* 写入 FIFO 中与头连接的位数 */
        CRYP_DataIn(__REV(headerlength >> 32));
        CRYP_DataIn(__REV(headerlength));
        CRYP_DataIn(__REV(inputlength >> 32));
        CRYP_DataIn(__REV(inputlength));

        /* 等待OFNE标志被重置 */
        while(CRYP_GetFlagStatus(CRYP_FLAG_OFNE) == RESET) {
        }

        tagaddr = (uint32_t)AuthTAG;
        /* 读取IN FIFO 中的 Auth TAG。 */
        *(uint32_t*)(tagaddr) = CRYP_DataOut();
        tagaddr += 4;
        *(uint32_t*)(tagaddr) = CRYP_DataOut();
        tagaddr += 4;
        *(uint32_t*)(tagaddr) = CRYP_DataOut();
        tagaddr += 4;
        *(uint32_t*)(tagaddr) = CRYP_DataOut();
        tagaddr += 4;
    }

    /* 禁用加密 */
    CRYP_Cmd(DISABLE);

    return status;
}

/**
  * 简介:  在 CCM 模式下使用 AES 进行加密和解密。
  *        GCM 和 CCM 模式仅在 STM32F437x 器件上可用。
  * 
  * 参数:  Mode: 加密或解密模式。
  *          此参数可以是以下值之一:
  *            @arg MODE_ENCRYPT: 加密
  *            @arg MODE_DECRYPT: 解密
  * 
  * 参数:  Nonce: 用于 AES 算法的 nonce。它对每一次处理都应是唯一的。
  * 
  * 参数:  Key: 用于 AES 算法的密钥。
  * 
  * 参数:  Keysize: 密钥的长度必须为 128、192 或256。
  * 
  * 参数:  Input: 指向输入缓冲区的指针。
  * 
  * 参数:  Ilength: 输入缓冲区的长度(以字节为单位)必须是 16 的倍数。
  * 
  * 参数:  Header: 指向头缓冲区的指针。
  * 
  * 参数:  Hlength: 头部缓冲区的长度，以字节为单位。
  * 
  * 参数:  HBuffer: 指向用于附加头的临时缓冲区的指针 HBuffer 的大小必须等于 Hlength + 21
  * 
  * 参数:  Output: 指向返回缓冲区的指针。
  * 
  * 参数:  AuthTAG: 指向认证 TAG 缓冲区的指针。
  * 
  * 参数:  TAGSize: TAG 的大小(也叫MAC)。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: 操作已完成
  *          - ERROR: 操作失败
  */
ErrorStatus CRYP_AES_CCM(uint8_t Mode,
                         uint8_t* Nonce, uint32_t NonceSize,
                         uint8_t *Key, uint16_t Keysize,
                         uint8_t *Input, uint32_t ILength,
                         uint8_t *Header, uint32_t HLength, uint8_t *HBuffer,
                         uint8_t *Output,
                         uint8_t *AuthTAG, uint32_t TAGSize) {
    CRYP_InitTypeDef AES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef AES_CRYP_KeyInitStructure;
    CRYP_IVInitTypeDef AES_CRYP_IVInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    uint32_t headeraddr = (uint32_t)Header;
    uint32_t tagaddr = (uint32_t)AuthTAG;
    uint32_t headersize = HLength;
    uint32_t loopcounter = 0;
    uint32_t bufferidx = 0;
    uint8_t blockb0[16] = {0};/* Block B0 */
    uint8_t ctr[16] = {0}; /* Counter */
    uint32_t temptag[4] = {0}; /* temporary TAG (MAC) */
    uint32_t ctraddr = (uint32_t)ctr;
    uint32_t b0addr = (uint32_t)blockb0;

    /************************ 格式化头块 ***********************/
    if(headersize != 0) {
        /* 检查相关数据(或头)的长度是否低于 2^16 - 2^8 = 65536 - 256 = 65280 */
        if(headersize < 65280) {
            HBuffer[bufferidx++] = (uint8_t) ((headersize >> 8) & 0xFF);
            HBuffer[bufferidx++] = (uint8_t) ((headersize) & 0xFF);
            headersize += 2;
        } else {
            /* 头被编码为 0xff || 0xfe || [headersize]32, i.e., six octets */
            HBuffer[bufferidx++] = 0xFF;
            HBuffer[bufferidx++] = 0xFE;
            HBuffer[bufferidx++] = headersize & 0xff000000;
            HBuffer[bufferidx++] = headersize & 0x00ff0000;
            HBuffer[bufferidx++] = headersize & 0x0000ff00;
            HBuffer[bufferidx++] = headersize & 0x000000ff;
            headersize += 6;
        }

        /* 在内部缓冲区 "HBuffer "中复制头部缓冲区 */
        for(loopcounter = 0; loopcounter < headersize; loopcounter++) {
            HBuffer[bufferidx++] = Header[loopcounter];
        }

        /* 如果头的大小是模数 16，则检查 */
        if ((headersize % 16) != 0) {
            /* 用0填充头缓冲区，直到 HBuffer 长度为16的模数。 */
            for(loopcounter = headersize; loopcounter <= ((headersize / 16) + 1) * 16; loopcounter++) {
                HBuffer[loopcounter] = 0;
            }

            /* 设置 headersize 为16的模数 */
            headersize = ((headersize / 16) + 1) * 16;
        }

        /* 设置指向HBuffer 的指针 headeraddr */
        headeraddr = (uint32_t)HBuffer;
    }

    /************************* 格式化块B0 **************************/
    if(headersize != 0) {
        blockb0[0] = 0x40;
    }

    /* 字节标志 */
    blockb0[0] |= 0u | (((( (uint8_t) TAGSize - 2) / 2) & 0x07 ) << 3 ) | ( ( (uint8_t) (15 - NonceSize) - 1) & 0x07);

    for (loopcounter = 0; loopcounter < NonceSize; loopcounter++) {
        blockb0[loopcounter + 1] = Nonce[loopcounter];
    }

    for ( ; loopcounter < 13; loopcounter++) {
        blockb0[loopcounter + 1] = 0;
    }

    blockb0[14] = ((ILength >> 8) & 0xFF);
    blockb0[15] = (ILength & 0xFF);

    /************************* 格式化初始计数器 *******************/
    /* Byte 0:
       第 7 和第 6 位是保留位，应设置为0
       第 3、4 和 5 位也应设置为 0，以确保所有的计数器块都与 B0 不同。
       第 0、1 和 2 位包含与 B0 中相同的q的编码
    */
    ctr[0] = blockb0[0] & 0x07;

    /* 字节 1 到 NonceSize 是IV(Nonce)。 */
    for(loopcounter = 1; loopcounter < NonceSize + 1; loopcounter++) {
        ctr[loopcounter] = blockb0[loopcounter];
    }

    /* 设置 LSB to 1 */
    ctr[15] |= 0x01;

    /* 加密数据结构初始化 */
    CRYP_KeyStructInit(&AES_CRYP_KeyInitStructure);

    switch(Keysize) {
        case 128:
            AES_CRYP_InitStructure.CRYP_KeySize = CRYP_KeySize_128b;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 192:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_192b;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        case 256:
            AES_CRYP_InitStructure.CRYP_KeySize  = CRYP_KeySize_256b;
            AES_CRYP_KeyInitStructure.CRYP_Key0Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key0Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
            keyaddr += 4;
            AES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
            break;

        default:
            break;
    }

    /* CRYP 初始化 Vectors */
    AES_CRYP_IVInitStructure.CRYP_IV0Left = (__REV(*(uint32_t*)(ctraddr)));
    ctraddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV0Right = (__REV(*(uint32_t*)(ctraddr)));
    ctraddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Left = (__REV(*(uint32_t*)(ctraddr)));
    ctraddr += 4;
    AES_CRYP_IVInitStructure.CRYP_IV1Right = (__REV(*(uint32_t*)(ctraddr)));

    /*------------------ AES加密 ------------------*/
    if(Mode == MODE_ENCRYPT) { /* AES加密 */
        /* Flush IN/OUT FIFOs */
        CRYP_FIFOFlush();

        /* 密钥初始化 */
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

        /* CRYP 初始化 Vectors */
        CRYP_IVInit(&AES_CRYP_IVInitStructure);

        /* 用于解密过程密钥准备的加密初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
        AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_CCM;
        AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
        CRYP_Init(&AES_CRYP_InitStructure);

        /***************************** 初始阶段 *********************************/
        /* 选择初始化阶段 */
        CRYP_PhaseConfig(CRYP_Phase_Init);

        b0addr = (uint32_t)blockb0;
        /* 在 IN FIFO 中写入blockb0块。 */
        CRYP_DataIn((*(uint32_t*)(b0addr)));
        b0addr += 4;
        CRYP_DataIn((*(uint32_t*)(b0addr)));
        b0addr += 4;
        CRYP_DataIn((*(uint32_t*)(b0addr)));
        b0addr += 4;
        CRYP_DataIn((*(uint32_t*)(b0addr)));

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        /* 等待密码位为0 */
        while(CRYP_GetCmdStatus() == ENABLE) {
        }

        /***************************** 头部阶段 *******************************/
        if(headersize != 0) {
            /* 选择头部阶段 */
            CRYP_PhaseConfig(CRYP_Phase_Header);

            /* 启用加密处理器 */
            CRYP_Cmd(ENABLE);

            if(CRYP_GetCmdStatus() == DISABLE) {
                /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
                return(ERROR);
            }

            for(loopcounter = 0; (loopcounter < headersize); loopcounter += 16) {
                /* 等待IFEM标志被重置 */
                while(CRYP_GetFlagStatus(CRYP_FLAG_IFEM) == RESET) {
                }

                /* 在 IN FIFO 中写入输入块 */
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
            }

            /* 等待，直到完整的信息被处理完毕 */
            counter = 0;

            do {
                busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                counter++;
            } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

            if (busystatus != RESET) {
                status = ERROR;
            }
        }

        /**************************** 有效负载阶段 *******************************/
        if(ILength != 0) {
            /* 选择有效负载阶段 */
            CRYP_PhaseConfig(CRYP_Phase_Payload);

            /* 启用加密处理器 */
            CRYP_Cmd(ENABLE);

            if(CRYP_GetCmdStatus() == DISABLE) {
                /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
                return(ERROR);
            }

            for(loopcounter = 0; ((loopcounter < ILength) && (status != ERROR)); loopcounter += 16) {
                /* 等待IFEM标志被重置 */
                while(CRYP_GetFlagStatus(CRYP_FLAG_IFEM) == RESET) {
                }

                /* 在 IN FIFO 中写入输入块 */
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;

                /* 等待，直到完整的信息被处理完毕 */
                counter = 0;

                do {
                    busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                    counter++;
                } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

                if (busystatus != RESET) {
                    status = ERROR;
                } else {
                    /* 等待OFNE标志被重置 */
                    while(CRYP_GetFlagStatus(CRYP_FLAG_OFNE) == RESET) {
                    }

                    /* 从输出FIFO 中读取输出块 */
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                }
            }
        }

        /***************************** 最后阶段 ********************************/
        /* 选择最后阶段 */
        CRYP_PhaseConfig(CRYP_Phase_Final);

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        if(CRYP_GetCmdStatus() == DISABLE) {
            /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
            return(ERROR);
        }

        ctraddr = (uint32_t)ctr;
        /* 在 IN FIFO 中写入计数器块 */
        CRYP_DataIn(*(uint32_t*)(ctraddr));
        ctraddr += 4;
        CRYP_DataIn(*(uint32_t*)(ctraddr));
        ctraddr += 4;
        CRYP_DataIn(*(uint32_t*)(ctraddr));
        ctraddr += 4;
        /* 复位位0(8位互换后)相当于复位位24(8位互换前)。 */
        CRYP_DataIn(*(uint32_t*)(ctraddr) & 0xfeffffff);

        /* 等待OFNE标志被重置 */
        while(CRYP_GetFlagStatus(CRYP_FLAG_OFNE) == RESET) {
        }

        /* 读取IN FIFO 中的 Auth TAG。 */
        temptag[0] = CRYP_DataOut();
        temptag[1] = CRYP_DataOut();
        temptag[2] = CRYP_DataOut();
        temptag[3] = CRYP_DataOut();
    }
    /*------------------ AES解密 ------------------*/
    else { /* AES解密 */
        /* Flush IN/OUT FIFOs */
        CRYP_FIFOFlush();

        /* 密钥初始化 */
        CRYP_KeyInit(&AES_CRYP_KeyInitStructure);

        /* CRYP 初始化 Vectors */
        CRYP_IVInit(&AES_CRYP_IVInitStructure);

        /* 用于解密过程密钥准备的加密初始化 */
        AES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
        AES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_AES_CCM;
        AES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
        CRYP_Init(&AES_CRYP_InitStructure);

        /***************************** 初始阶段 *********************************/
        /* 选择初始化阶段 */
        CRYP_PhaseConfig(CRYP_Phase_Init);

        b0addr = (uint32_t)blockb0;
        /* 在 IN FIFO 中写入blockb0块。 */
        CRYP_DataIn((*(uint32_t*)(b0addr)));
        b0addr += 4;
        CRYP_DataIn((*(uint32_t*)(b0addr)));
        b0addr += 4;
        CRYP_DataIn((*(uint32_t*)(b0addr)));
        b0addr += 4;
        CRYP_DataIn((*(uint32_t*)(b0addr)));

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        /* 等待密码位为0 */
        while(CRYP_GetCmdStatus() == ENABLE) {
        }

        /***************************** 头部阶段 *******************************/
        if(headersize != 0) {
            /* 选择头部阶段 */
            CRYP_PhaseConfig(CRYP_Phase_Header);

            /* 启用加密处理器 */
            CRYP_Cmd(ENABLE);

            if(CRYP_GetCmdStatus() == DISABLE) {
                /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
                return(ERROR);
            }

            for(loopcounter = 0; (loopcounter < headersize); loopcounter += 16) {
                /* 等待IFEM标志被重置 */
                while(CRYP_GetFlagStatus(CRYP_FLAG_IFEM) == RESET) {
                }

                /* 在 IN FIFO 中写入输入块 */
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
                CRYP_DataIn(*(uint32_t*)(headeraddr));
                headeraddr += 4;
            }

            /* 等待，直到完整的信息被处理完毕 */
            counter = 0;

            do {
                busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                counter++;
            } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

            if (busystatus != RESET) {
                status = ERROR;
            }
        }

        /**************************** 有效负载阶段 *******************************/
        if(ILength != 0) {
            /* 选择有效负载阶段 */
            CRYP_PhaseConfig(CRYP_Phase_Payload);

            /* 启用加密处理器 */
            CRYP_Cmd(ENABLE);

            if(CRYP_GetCmdStatus() == DISABLE) {
                /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
                return(ERROR);
            }

            for(loopcounter = 0; ((loopcounter < ILength) && (status != ERROR)); loopcounter += 16) {
                /* 等待IFEM标志被重置 */
                while(CRYP_GetFlagStatus(CRYP_FLAG_IFEM) == RESET) {
                }

                /* 在 IN FIFO 中写入输入块 */
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;
                CRYP_DataIn(*(uint32_t*)(inputaddr));
                inputaddr += 4;

                /* 等待，直到完整的信息被处理完毕 */
                counter = 0;

                do {
                    busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                    counter++;
                } while ((counter != AESBUSY_TIMEOUT) && (busystatus != RESET));

                if (busystatus != RESET) {
                    status = ERROR;
                } else {
                    /* 等待OFNE标志被重置 */
                    while(CRYP_GetFlagStatus(CRYP_FLAG_OFNE) == RESET) {
                    }

                    /* 从输出FIFO 中读取输出块 */
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                    *(uint32_t*)(outputaddr) = CRYP_DataOut();
                    outputaddr += 4;
                }
            }
        }

        /***************************** 最后阶段 ********************************/
        /* 选择最后阶段 */
        CRYP_PhaseConfig(CRYP_Phase_Final);

        /* 启用加密处理器 */
        CRYP_Cmd(ENABLE);

        if(CRYP_GetCmdStatus() == DISABLE) {
            /* CRYP 外围时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型)。 */
            return(ERROR);
        }

        ctraddr = (uint32_t)ctr;
        /* 在 IN FIFO 中写入计数器块 */
        CRYP_DataIn(*(uint32_t*)(ctraddr));
        ctraddr += 4;
        CRYP_DataIn(*(uint32_t*)(ctraddr));
        ctraddr += 4;
        CRYP_DataIn(*(uint32_t*)(ctraddr));
        ctraddr += 4;
        /* 复位位0(8位互换后)相当于复位位24(8位互换前)。 */
        CRYP_DataIn(*(uint32_t*)(ctraddr) & 0xfeffffff);

        /* 等待OFNE标志被重置 */
        while(CRYP_GetFlagStatus(CRYP_FLAG_OFNE) == RESET) {
        }

        /* 读取IN FIFO 中的认证标签(MAC)。 */
        temptag[0] = CRYP_DataOut();
        temptag[1] = CRYP_DataOut();
        temptag[2] = CRYP_DataOut();
        temptag[3] = CRYP_DataOut();
    }

    /* 在用户TAG缓冲区中复制临时认证TAG */
    for(loopcounter = 0; (loopcounter < TAGSize); loopcounter++) {
        /* 设置认证TAG缓冲区 */
        *((uint8_t*)tagaddr + loopcounter) = *((uint8_t*)temptag + loopcounter);
    }

    /* 禁用加密 */
    CRYP_Cmd(DISABLE);

    return status;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

