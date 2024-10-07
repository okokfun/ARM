/**
  ******************************************************************************
  * 文件:    stm32f4xx_crc.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供所有 CRC 固件功能。
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
#include "stm32f4xx_crc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup CRC
  * 简介: CRC驱动模块
  */

/* 私有类型定义 -----------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------*/
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup CRC_Private_Functions
  */

/**
  * 简介:  重置 CRC 数据寄存器 (DR)。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void CRC_ResetDR(void) {
    /* 重置 CRC 生成器 */
    CRC->CR = CRC_CR_RESET;
}

/**
  * 简介:  计算给定数据字(32 位)的 32 位 CRC。
  * 
  * 参数:  数据: 用于计算其 CRC 的数据字(32 位)
  * 
  * 返回值: 32-bit CRC
  */
uint32_t CRC_CalcCRC(uint32_t Data) {
    CRC->DR = Data;

    return (CRC->DR);
}

/**
  * 简介:  计算给定数据字(32 位)缓冲区的 32 位 CRC。
  * 
  * 参数:  pBuffer: 指向包含要计算的数据的缓冲区的指针
  * 
  * 参数:  BufferLength: 要计算的缓冲区的长度
  * 
  * 返回值: 32-bit CRC
  */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength) {
    uint32_t index = 0;

    for(index = 0; index < BufferLength; index++) {
        CRC->DR = pBuffer[index];
    }

    return (CRC->DR);
}

/**
  * 简介:  返回当前的 CRC 值。
  * 
  * 参数:  无
  * 
  * 返回值: 32-bit CRC
  */
uint32_t CRC_GetCRC(void) {
    return (CRC->DR);
}

/**
  * 简介:  在独立数据 (ID) 寄存器中存储 8 位数据。
  * 
  * 参数:  IDValue:要存储在 ID 寄存器中的 8 位值
  * 
  * 返回值: 无
  */
void CRC_SetIDRegister(uint8_t IDValue) {
    CRC->IDR = IDValue;
}

/**
  * 简介:  返回存储在独立数据(ID)寄存器中的 8 位数据
  * 
  * 参数:  无
  * 
  * 返回值: ID 寄存器的 8 位值
  */
uint8_t CRC_GetIDRegister(void) {
    return (CRC->IDR);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
