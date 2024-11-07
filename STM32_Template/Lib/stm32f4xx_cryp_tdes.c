/**
  ******************************************************************************
  * 文件:    stm32f4xx_cryp_tdes.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供高级函数，用于在 ECB/CBC 模式下使用 TDES 加密和解密输入消息。
  *          它使用 stm32f4xx_cryp.c/.h 驱动程序来访问 STM32F4xx CRYP 外设。
  *
@verbatim

 ===============================================================================
                           ##### 如何使用此驱动程序 #####
 ===============================================================================
 [..]
   (#) 启用 CRYP 控制器时钟使用函数
       RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_CRYP, ENABLE);

   (#) 使用 CRYP_TDES_ECB() 函数在 ECB 模式下使用 TDES 进行加密和解密。

   (#) 使用 CRYP_TDES_CBC() 函数在 CBC 模式下使用 TDES 进行加密和解密。

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
#define TDESBUSY_TIMEOUT    ((uint32_t) 0x00010000)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/


/** @defgroup CRYP_Private_Functions
  */

/** @defgroup CRYP_Group7 高水平的 TDES功能
 *  简介   高水平的 TDES功能
 *
@verbatim
 ===============================================================================
                      ##### 高水平的 TDES功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  在 ECB 模式下使用 TDES 进行加密和解密。
  * 
  * 参数:  Mode: 加密或解密模式。
  *           此参数可以是以下值之一:
  *            @arg MODE_ENCRYPT: 加密
  *            @arg MODE_DECRYPT: 解密
  * 
  * 参数:  Key: 用于 TDES 算法的密钥。
  * 
  * 参数:  Ilength: 输入缓冲区的长度，必须是 8 的倍数。
  * 
  * 参数:  Input: 指向输入缓冲区的指针。
  * 
  * 参数:  Output: 指向返回缓冲区的指针。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: 操作已完成
  *          - ERROR: 操作失败
  */
ErrorStatus CRYP_TDES_ECB(uint8_t Mode, uint8_t Key[24], uint8_t *Input,
                          uint32_t Ilength, uint8_t *Output) {
    CRYP_InitTypeDef TDES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef TDES_CRYP_KeyInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus = 0;
    ErrorStatus status = SUCCESS;
    uint32_t keyaddr    = (uint32_t)Key;
    uint32_t inputaddr  = (uint32_t)Input;
    uint32_t outputaddr = (uint32_t)Output;
    uint32_t i = 0;

    /* 加密结构初始化*/
    CRYP_KeyStructInit(&TDES_CRYP_KeyInitStructure);

    /* 加密过程的 Crypto Init */
    if(Mode == MODE_ENCRYPT) { /* TDES 加密 */
        TDES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
    } else { /*if(Mode == MODE_DECRYPT)*/
        /* TDES 解密 */
        TDES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
    }

    TDES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_TDES_ECB;
    TDES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;
    CRYP_Init(&TDES_CRYP_InitStructure);

    /* 密钥初始化 */
    TDES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
    CRYP_KeyInit(& TDES_CRYP_KeyInitStructure);

    /* Flush IN/OUT FIFO */
    CRYP_FIFOFlush();

    /* 启用加密处理器 */
    CRYP_Cmd(ENABLE);

    if(CRYP_GetCmdStatus() == DISABLE) {
        /* CRYP 外设时钟未启用或设备未嵌入 CRYP 外设(请检查设备销售类型。 */
        status = ERROR;
    } else {
        for(i = 0; ((i < Ilength) && (status != ERROR)); i += 8) {
            /* 在输入 FIFO 中写入输入块 */
            CRYP_DataIn(*(uint32_t*)(inputaddr));
            inputaddr += 4;
            CRYP_DataIn(*(uint32_t*)(inputaddr));
            inputaddr += 4;

            /* 等待，直到完整的信息被处理完毕 */
            counter = 0;

            do {
                busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                counter++;
            } while ((counter != TDESBUSY_TIMEOUT) && (busystatus != RESET));

            if (busystatus != RESET) {
                status = ERROR;
            } else {

                /* 从输出FIFO 中读取输出块 */
                *(uint32_t*)(outputaddr) = CRYP_DataOut();
                outputaddr += 4;
                *(uint32_t*)(outputaddr) = CRYP_DataOut();
                outputaddr += 4;
            }
        }

        /* 禁用加密 */
        CRYP_Cmd(DISABLE);
    }

    return status;
}

/**
  * 简介:  在 CBC 模式下使用 TDES 进行加密和解密。
  * 
  * 参数:  Mode: 加密或解密模式。
  *           此参数可以是以下值之一:
  *            @arg MODE_ENCRYPT: 加密
  *            @arg MODE_DECRYPT: 解密
  * 
  * 参数:  Key: 用于 TDES 算法的密钥。
  * 
  * 参数:  InitVectors: 用于 TDES 算法的初始化矢量。
  * 
  * 参数:  Input: 指向输入缓冲区的指针。
  * 
  * 参数:  Ilength: 输入缓冲区的长度，必须是 8 的倍数。
  * 
  * 参数:  Output: 指向返回缓冲区的指针。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: 操作已完成
  *          - ERROR: 操作失败
  */
ErrorStatus CRYP_TDES_CBC(uint8_t Mode, uint8_t Key[24], uint8_t InitVectors[8],
                          uint8_t *Input, uint32_t Ilength, uint8_t *Output) {
    CRYP_InitTypeDef TDES_CRYP_InitStructure;
    CRYP_KeyInitTypeDef TDES_CRYP_KeyInitStructure;
    CRYP_IVInitTypeDef TDES_CRYP_IVInitStructure;
    __IO uint32_t counter = 0;
    uint32_t busystatus   = 0;
    ErrorStatus status    = SUCCESS;
    uint32_t keyaddr      = (uint32_t)Key;
    uint32_t inputaddr    = (uint32_t)Input;
    uint32_t outputaddr   = (uint32_t)Output;
    uint32_t ivaddr       = (uint32_t)InitVectors;
    uint32_t i            = 0;

    /* 加密数据结构初始化 */
    CRYP_KeyStructInit(&TDES_CRYP_KeyInitStructure);

    /* Crypto加密进程的初始化 */
    if(Mode == MODE_ENCRYPT) { /* TDES 加密 */
        TDES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Encrypt;
    } else {
        TDES_CRYP_InitStructure.CRYP_AlgoDir = CRYP_AlgoDir_Decrypt;
    }

    TDES_CRYP_InitStructure.CRYP_AlgoMode = CRYP_AlgoMode_TDES_CBC;
    TDES_CRYP_InitStructure.CRYP_DataType = CRYP_DataType_8b;

    CRYP_Init(&TDES_CRYP_InitStructure);

    /* 密钥初始化 */
    TDES_CRYP_KeyInitStructure.CRYP_Key1Left = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key1Right = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key2Left = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key2Right = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key3Left = __REV(*(uint32_t*)(keyaddr));
    keyaddr += 4;
    TDES_CRYP_KeyInitStructure.CRYP_Key3Right = __REV(*(uint32_t*)(keyaddr));
    CRYP_KeyInit(& TDES_CRYP_KeyInitStructure);

    /* 初始化 Vectors */
    TDES_CRYP_IVInitStructure.CRYP_IV0Left = __REV(*(uint32_t*)(ivaddr));
    ivaddr += 4;
    TDES_CRYP_IVInitStructure.CRYP_IV0Right = __REV(*(uint32_t*)(ivaddr));
    CRYP_IVInit(&TDES_CRYP_IVInitStructure);

    /* Flush IN/OUT FIFO */
    CRYP_FIFOFlush();

    /* 启用加密处理器 */
    CRYP_Cmd(ENABLE);

    if(CRYP_GetCmdStatus() == DISABLE) {
        /* CRYP 外设时钟没有启用，或者设备没有嵌入 CRYP 外设(请检查设备销售类型。*/
        status = ERROR;
    } else {
        for(i = 0; ((i < Ilength) && (status != ERROR)); i += 8) {
            /* 在输入 FIFO 中写入输入块 */
            CRYP_DataIn(*(uint32_t*)(inputaddr));
            inputaddr += 4;
            CRYP_DataIn(*(uint32_t*)(inputaddr));
            inputaddr += 4;

            /* 等待，直到完整的信息被处理完毕 */
            counter = 0;

            do {
                busystatus = CRYP_GetFlagStatus(CRYP_FLAG_BUSY);
                counter++;
            } while ((counter != TDESBUSY_TIMEOUT) && (busystatus != RESET));

            if (busystatus != RESET) {
                status = ERROR;
            } else {

                /* 从输出FIFO 中读取输出块 */
                *(uint32_t*)(outputaddr) = CRYP_DataOut();
                outputaddr += 4;
                *(uint32_t*)(outputaddr) = CRYP_DataOut();
                outputaddr += 4;
            }
        }

        /* 禁用加密 */
        CRYP_Cmd(DISABLE);
    }

    return status;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
