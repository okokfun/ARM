/**
  ******************************************************************************
  * 文件:    stm32f4xx_crc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 CRC 固件库的所有功能原型.
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
#ifndef __STM32F4xx_CRC_H
#define __STM32F4xx_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup CRC
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup CRC_Exported_Constants
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void CRC_ResetDR(void); // 重置 CRC 数据寄存器 (DR)。
uint32_t CRC_CalcCRC(uint32_t Data); // 计算给定数据字(32 位)的 32 位 CRC。
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength); // 计算给定数据字(32 位)缓冲区的 32 位 CRC。
uint32_t CRC_GetCRC(void); // 返回当前的 CRC 值。
void CRC_SetIDRegister(uint8_t IDValue); // 在独立数据 (ID) 寄存器中存储 8 位数据。
uint8_t CRC_GetIDRegister(void); // 返回存储在独立数据 (ID) 寄存器中的 8 位数据。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_CRC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
