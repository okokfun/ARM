/**
  ******************************************************************************
  * 文件:    stm32f4xx_flash_ramfunc.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    FLASH RAMFUNC 模块驱动程序。
  *           此文件提供应从内部 SRAM执行的 FLASH固件功能
  *           + 系统运行时停止/启动闪存界面
  *           + 在系统运行时启用/禁用闪存睡眠
  *
 @verbatim
 ==============================================================================
                    ##### 从内部 RAM执行的 API #####
  ==============================================================================
  [..]
    *** ARM编译器 ***
    --------------------
        [..] RAM功能使用工具链选项定义。
        RAM 中执行的功能应位于单独的源模块中。使用" 文件选项"对话框，您可以
            简单地将模块的 "代码/常量"区域更改为物理 RAM 中的内存空间。
        可用内存区域在"目标选项"对话框的 "目标"选项卡中声明。

    *** ICCARM 编译器 ***
    -----------------------
        [..] RAM函数使用特定的工具链关键字"__ramfunc" 定义。

    *** GNU 编译器 ***
    --------------------
        [..] RAM功能使用特定的工具链属性"__attribute__((section(".RamFunc"))" 定义。

  @endverbatim
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
#include "stm32f4xx_flash_ramfunc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup FLASH RAMFUNC
  * 简介: FLASH RAMFUNC 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup FLASH_RAMFUNC_Private_Functions
  */

/** @defgroup FLASH_RAMFUNC_Group1 外设设备具有从内部 RAM执行的功能
  *  简介 外围扩展功能功能
  *
@verbatim

 ===============================================================================
                      ##### ramfunc 功能#####
 ===============================================================================
    [..]
    本小节提供了应从RAM传输执行的一组功能。

@endverbatim
  */

/**
  * 简介:  开始/停止flash接口当系统运行时
  * 
  * 注意:  这个模式只为 STM32F411xx 设备.
  * 
  * 注意:  使用闪存本身执行时无法设置此模式。
  *        它应该使用从RAM执行的特定例程来完成。
  * 
  * 参数:  NewState: 智能卡模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
__RAM_FUNC FLASH_FlashInterfaceCmd(FunctionalState NewState) {
    if (NewState != DISABLE) {
        /* 在系统运行时启动闪存接口 */
        CLEAR_BIT(PWR->CR, PWR_CR_FISSR);
    } else {
        /* 系统运行时停止闪存界面 */
        SET_BIT(PWR->CR, PWR_CR_FISSR);
    }
}

/**
  * 简介: 使能/失能 flash 睡眠模式当系统运行时
  * 
  * 注意:  这个模式只为 STM32F411xx devices.
  * 
  * 注意:  使用闪存本身执行时无法设置此模式。
  *        它应该使用从RAM执行的特定例程来完成。
  * 
  * 参数:  NewState: 智能卡模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
__RAM_FUNC FLASH_FlashSleepModeCmd(FunctionalState NewState) {
    if (NewState != DISABLE) {
        /* 启用 flash sleep 系统运行时 */
        SET_BIT(PWR->CR, PWR_CR_FMSSR);
    } else {
        /* 禁用 flash sleep 系统运行时 */
        CLEAR_BIT(PWR->CR, PWR_CR_FMSSR);
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
