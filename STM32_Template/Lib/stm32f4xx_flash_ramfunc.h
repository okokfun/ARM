/**
  ******************************************************************************
  * 文件:    stm32f4xx_flash_ramfunc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    FLASH RAMFUNC驱动头文件.
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
#ifndef __STM32F4xx_FLASH_RAMFUNC_H
#define __STM32F4xx_FLASH_RAMFUNC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup FLASH RAMFUNC
  */

/* Exported types ------------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/**
  * 简介:  __RAM_FUNC definition
  */
#if defined ( __CC_ARM   )
/* ARM 编译器
   ------------
   RAM functions are defined using the toolchain options.
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const'
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog.
*/
#define __RAM_FUNC void

#elif defined ( __ICCARM__ )
/* ICCARM 编译器
   ---------------
   RAM 函数是使用特定的工具链关键字 "__ramfunc" 定义的。
*/
#define __RAM_FUNC __ramfunc void

#elif defined   (  __GNUC__  )
/* GNU 编译器
   ------------
  RAM函数是使用特定的工具链属性 "__attribute__((section(".RamFunc"))" 定义的。
*/
#define __RAM_FUNC void  __attribute__((section(".RamFunc")))

#endif
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
__RAM_FUNC FLASH_FlashInterfaceCmd(FunctionalState NewState); // __RAM_FUNC 定义
__RAM_FUNC FLASH_FlashSleepModeCmd(FunctionalState NewState); // 在系统运行时启用/禁用闪存睡眠。


#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_FLASH_RAMFUNC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

