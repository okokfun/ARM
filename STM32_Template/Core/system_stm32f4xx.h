/**
  ******************************************************************************
  * @file    system_stm32f4xx.h
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    09-November-2016
  * 简介:   用于 STM32F4xx 器件的 CMSIS Cortex-M4 器件系统源文件。
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

/** @addtogroup CMSIS
  */

/** @addtogroup stm32f4xx_system
  */

/**
  * 简介: Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_STM32F4XX_H
#define __SYSTEM_STM32F4XX_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup STM32F4xx_System_Includes
  */



/** @addtogroup STM32F4xx_System_Exported_types
  */

extern uint32_t SystemCoreClock;          /*!< 系统时钟频率(核心时钟) */



/** @addtogroup STM32F4xx_System_Exported_Constants
  */


/** @addtogroup STM32F4xx_System_Exported_Macros
  */


/** @addtogroup STM32F4xx_System_Exported_Functions
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32F4XX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
