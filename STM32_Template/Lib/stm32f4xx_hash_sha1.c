/**
  ******************************************************************************
  * 文件:    stm32f4xx_hash_sha1.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * @简介   该文件提供了计算输入消息的 HASH SHA1和HMAC SHA1摘要的高级函数。
  *          它使用 Stm32f4xx_hash.c/h驱动程序访问STM32F4xx HASH 外设设备。
  *
@verbatim
 ===================================================================
                 ##### 如何使用此驱动程序 #####
 ===================================================================
 [..]
   (#) 使用启用 HASH控制器时钟函数
       RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_HASH, ENABLE).

   (#) 使用 HASH_SHA1() 函数计算HASH SHA1摘要。

   (#) 使用 HMAC_SHA1() 函数计算HMAC SHA1摘要。

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

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup HASH
  * @简介 HASH驱动程序模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define SHA1BUSY_TIMEOUT    ((uint32_t) 0x00010000)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup HASH_Private_Functions
  */

/** @defgroup HASH_Group6高级SHA1功能
 *  @简介   高级SHA1哈希和HMAC函数
 *
@verbatim
 ===============================================================================
               ##### 高级SHA1哈希和HMAC函数 #####
 ===============================================================================


@endverbatim
  */

/**
  * @简介  计算HASH SHA1摘要。
  * 
  * @参数  Input: 指向要处理的输入缓冲区的指针。
  * @参数  Ilen: 输入缓冲区的长度。
  * @参数  Output: 返回的摘要
  * 
  * @返回值 ErrorStatus枚举值:
  *          - SUCCESS: 摘要计算已完成
  *          - ERROR: 摘要计算失败
  */
ErrorStatus HASH_SHA1(uint8_t *Input, uint32_t Ilen, uint8_t Output[20]) {
    HASH_InitTypeDef SHA1_HASH_InitStructure;
    HASH_MsgDigest SHA1_MessageDigest;
    __IO uint16_t nbvalidbitsdata = 0;
    uint32_t i = 0;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;

    /* 输入数据最后一个字的有效位数 */
    nbvalidbitsdata = 8 * (Ilen % 4);

    /* HASH 外设设备初始化 */
    HASH_DeInit();

    /* HASH配置 */
    SHA1_HASH_InitStructure.HASH_AlgoSelection = HASH_AlgoSelection_SHA1;
    SHA1_HASH_InitStructure.HASH_AlgoMode = HASH_AlgoMode_HASH;
    SHA1_HASH_InitStructure.HASH_DataType = HASH_DataType_8b;
    HASH_Init(&SHA1_HASH_InitStructure);

    /* 配置数据最后一个字中的有效位数 */
    HASH_SetLastWordValidBitsNbr(nbvalidbitsdata);

    /* 将输入块写入IN FIFO */
    for(i = 0; i < Ilen; i += 4) {
        HASH_DataIn(*(uint32_t*)inputaddr);
        inputaddr += 4;
    }

    /* 启动HASH处理器 */
    HASH_StartDigest();

    /* 等到Busy标志被重置 */
    do {
        busystatus = HASH_GetFlagStatus(HASH_FLAG_BUSY);
        counter++;
    } while ((counter != SHA1BUSY_TIMEOUT) && (busystatus != RESET));

    if (busystatus != RESET) {
        status = ERROR;
    } else {
        /* 读取信息摘要 */
        HASH_GetDigest(&SHA1_MessageDigest);
        *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[0]);
        outputaddr += 4;
        *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[1]);
        outputaddr += 4;
        *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[2]);
        outputaddr += 4;
        *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[3]);
        outputaddr += 4;
        *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[4]);
    }

    return status;
}

/**
  * @简介  计算HMAC SHA1摘要。
  * 
  * @参数  Key:     指向HMAC所用密钥的指针。
  * @参数  Keylen:  用于HMAC 的密钥的长度。
  * @参数  Input:   指向要处理的输入缓冲区的指针。
  * @参数  Ilen:    输入缓冲区的长度。
  * @参数  Output:  返回的摘要
  * 
  * @返回值 ErrorStatus枚举值:
  *          - SUCCESS: 摘要计算已完成
  *          - ERROR: 摘要计算失败
  */
ErrorStatus HMAC_SHA1(uint8_t *Key, uint32_t Keylen, uint8_t *Input,
                      uint32_t Ilen, uint8_t Output[20]) {
    HASH_InitTypeDef SHA1_HASH_InitStructure;
    HASH_MsgDigest SHA1_MessageDigest;
    __IO uint16_t nbvalidbitsdata = 0;
    __IO uint16_t nbvalidbitskey = 0;
    uint32_t i = 0;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;

    /* 输入数据最后一个字中的有效位数 */
    nbvalidbitsdata = 8 * (Ilen % 4);

    /* 密钥最后一个字中的有效位数 */
    nbvalidbitskey = 8 * (Keylen % 4);

    /* HASH 外设初始化 */
    HASH_DeInit();

    /* HASH配置 */
    SHA1_HASH_InitStructure.HASH_AlgoSelection = HASH_AlgoSelection_SHA1;
    SHA1_HASH_InitStructure.HASH_AlgoMode = HASH_AlgoMode_HMAC;
    SHA1_HASH_InitStructure.HASH_DataType = HASH_DataType_8b;

    if(Keylen > 64) {
        /* HMAC长密钥 */
        SHA1_HASH_InitStructure.HASH_HMACKeyType = HASH_HMACKeyType_LongKey;
    } else {
        /* HMAC短密钥 */
        SHA1_HASH_InitStructure.HASH_HMACKeyType = HASH_HMACKeyType_ShortKey;
    }

    HASH_Init(&SHA1_HASH_InitStructure);

    /* 配置 密钥最后一个字中的有效位数 */
    HASH_SetLastWordValidBitsNbr(nbvalidbitskey);

    /* 写入密钥 */
    for(i = 0; i < Keylen; i += 4) {
        HASH_DataIn(*(uint32_t*)keyaddr);
        keyaddr += 4;
    }

    /* 启动HASH处理器 */
    HASH_StartDigest();

    /* 等到Busy标志被重置 */
    do {
        busystatus = HASH_GetFlagStatus(HASH_FLAG_BUSY);
        counter++;
    } while ((counter != SHA1BUSY_TIMEOUT) && (busystatus != RESET));

    if (busystatus != RESET) {
        status = ERROR;
    } else {
        /* 配置 输入数据最后一个字中的有效位数 */
        HASH_SetLastWordValidBitsNbr(nbvalidbitsdata);

        /* 将输入块写入IN FIFO */
        for(i = 0; i < Ilen; i += 4) {
            HASH_DataIn(*(uint32_t*)inputaddr);
            inputaddr += 4;
        }

        /* 启动HASH处理器 */
        HASH_StartDigest();


        /* 等到Busy标志被重置 */
        counter = 0;

        do {
            busystatus = HASH_GetFlagStatus(HASH_FLAG_BUSY);
            counter++;
        } while ((counter != SHA1BUSY_TIMEOUT) && (busystatus != RESET));

        if (busystatus != RESET) {
            status = ERROR;
        } else {
            /* 配置 密钥最后一个字中的有效位数 */
            HASH_SetLastWordValidBitsNbr(nbvalidbitskey);

            /* 写入密钥 */
            keyaddr = (uint32_t)Key;

            for(i = 0; i < Keylen; i += 4) {
                HASH_DataIn(*(uint32_t*)keyaddr);
                keyaddr += 4;
            }

            /* 启动HASH处理器 */
            HASH_StartDigest();

            /* 等到Busy标志被重置 */
            counter = 0;

            do {
                busystatus = HASH_GetFlagStatus(HASH_FLAG_BUSY);
                counter++;
            } while ((counter != SHA1BUSY_TIMEOUT) && (busystatus != RESET));

            if (busystatus != RESET) {
                status = ERROR;
            } else {
                /* 读取信息摘要 */
                HASH_GetDigest(&SHA1_MessageDigest);
                *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[0]);
                outputaddr += 4;
                *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[1]);
                outputaddr += 4;
                *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[2]);
                outputaddr += 4;
                *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[3]);
                outputaddr += 4;
                *(uint32_t*)(outputaddr)  = __REV(SHA1_MessageDigest.Data[4]);
            }
        }
    }

    return status;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
