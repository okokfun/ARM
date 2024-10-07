/**
  ******************************************************************************
  * 文件:    stm32f4xx_iwdg.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供了固件功能来管理以下内容 独立看门狗(IWDG)外设的功能:
  *           + 预分频器和计数器配置
  *           + IWDG激活
  *           + 标志管理
  *
    @verbatim
 ===============================================================================
                          ##### IWDG的特点 #####
 ===============================================================================
    [..]
      IWDG可以由软件或硬件启动(可通过选项字节配置)。

      IWDG由它自己的专用低速时钟(LSI)提供时钟，因此即使主时钟失效，它也能保持活动。
      一旦IWDG被启动，LSI被强制打开，不能被禁用(LSI也不能被禁用)，
        计数器开始从重置值0xFFF开始倒数。当它到达计数结束值(0x000)时，就会产生系统复位。
      IWDG计数器应定期重新加载以防止MCU复位。

      IWDG在VDD电压域中实现，在STOP和STANDBY模式下仍然有效(IWDG复位可以从STANDBY唤醒)。

      RCC_CSR寄存器中的IWDGRST标志可用于通知何时发生IWDG复位。

      最小-最大超时值@32KHz(LSI): ~125us/~32.7s
      由于LSI频率分散，IWDG超时可能会有所不同。STM32F4xx器件提供了测量LSI频率的能力
      (LSI时钟内部连接到TIM5 CH4输入捕捉)。测量值可用于具有可接受精度的IWDG超时。
      欲了解更多信息，请参考STM32F4xx参考手册

                     ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..]
      (#) 使用 IWDG_PR 和 IWDG_RLR 寄存器启用写访问。
          IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable) 函数，
          启用对 IWDG_PR 和 IWDG_RLR 寄存器的写访问。

      (#) 使用 IWDG_SetPrescaler() 函数配置 IWDG 预分频器

      (#) 使用 IWDG_SetReload() 函数配置 IWDG 计数器的值。
          这个值将在每次重新加载 IWDG 计数器时被加载，然后 IWDG 将从这个值开始倒数。

      (#) 使用 IWDG_Enable() 函数启动 IWDG，当 IWDG 以软件模式使用时(不需要启用 LSI，它将由硬件启用)。

      (#) 然后应用程序必须在正常运行期间定期重新加载IWDG计数器，以防止出现故障。以防止 MCU 复位，使用
          IWDG_ReloadCounter() 函数。

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
#include "stm32f4xx_iwdg.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup IWDG
  * 简介: IWDG 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* KR寄存器位掩码 */
#define KR_KEY_RELOAD    ((uint16_t)0xAAAA)
#define KR_KEY_ENABLE    ((uint16_t)0xCCCC)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup IWDG_Private_Functions
  */

/** @defgroup IWDG_Group1 预分频器和计数器配置功能
 *  简介   预分频器和计数器配置功能
 *
@verbatim
 ===============================================================================
              ##### 预分频器和计数器配置功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用或禁用对 IWDG_PR 和 IWDG_RLR 寄存器的写入访问权限。
  * 
  * 参数:  IWDG_WriteAccess: 对 IWDG_PR 和 IWDG_RLR 寄存器进行写操作的新状态。
  *          此参数可以是以下值之一:
  *            @arg IWDG_WriteAccess_Enable:  启用对IWDG_PR和IWDG_RLR寄存器的写入权限
  *            @arg IWDG_WriteAccess_Disable: 禁止对IWDG_PR和IWDG_RLR寄存器的写访问
  * 
  * 返回值: 无
  */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess) {
    /* 检查参数 */
    assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
    IWDG->KR = IWDG_WriteAccess;
}

/**
  * 简介:  设置IWDG预分频器值。
  * 
  * 参数:  IWDG_Prescaler: 指定IWDG预分频器的值。
  *          此参数可以是以下值之一:
  *               @arg IWDG_Prescaler_4:   IWDG预分频器设置为 4
  *               @arg IWDG_Prescaler_8:   IWDG预分频器设置为 8
  *               @arg IWDG_Prescaler_16:  IWDG预分频器设置为 16
  *               @arg IWDG_Prescaler_32:  IWDG预分频器设置为 32
  *               @arg IWDG_Prescaler_64:  IWDG预分频器设置为 64
  *               @arg IWDG_Prescaler_128: IWDG预分频器设置为 128
  *               @arg IWDG_Prescaler_256: IWDG预分频器设置为 256
  * 
  * 返回值: 无
  */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler) {
    /* 检查参数 */
    assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));
    IWDG->PR = IWDG_Prescaler;
}

/**
  * 简介:  设置 IWDG 重新加载值。
  * 
  * 参数:  Reload: 指定 IWDG 重新加载值。
  *          这个参数必须是 0 到 0x0FFF 之间的数字。
  * 
  * 返回值: 无
  */
void IWDG_SetReload(uint16_t Reload) {
    /* 检查参数 */
    assert_param(IS_IWDG_RELOAD(Reload));
    IWDG->RLR = Reload;
}

/**
  * 简介:  使用重新加载寄存器中定义的值重新加载 IWDG 计数器
  *       (禁用对 IWDG_PR 和 IWDG_RLR 寄存器的写入访问)。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void IWDG_ReloadCounter(void) {
    IWDG->KR = KR_KEY_RELOAD;
}


/** @defgroup IWDG_Group2 IWDG激活函数
 *  简介   IWDG激活函数
 *
@verbatim
 ===============================================================================
                    ##### IWDG激活函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用 IWDG(禁用对IWDG_PR和IWDG_RLR寄存器的写访问)。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void IWDG_Enable(void) {
    IWDG->KR = KR_KEY_ENABLE;
}


/** @defgroup IWDG_Group3 标志管理功能
 *  简介  标志管理功能
 *
@verbatim
 ===============================================================================
                    ##### 标志管理功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  检查是否设置了指定的 IWDG 标志。
  * 
  * 参数:  IWDG_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *             @arg IWDG_FLAG_PVU: 预分频器值更新时的情况
  *             @arg IWDG_FLAG_RVU: 重新加载值的更新。
  * 
  * 返回值。IWDG_FLAG的新状态(SET或RESET)。
  */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_IWDG_FLAG(IWDG_FLAG));

    if ((IWDG->SR & IWDG_FLAG) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    /* 返回标志状态 */
    return bitstatus;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
