/**
  ******************************************************************************
  * 文件:    stm32f4xx_rng.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，用于管理随机数生成器(RNG)外设设备的以下功能:
  *           + 初始化和配置
  *           + 获取32位随机数
  *           + 中断和标志管理
  *
@verbatim

 ===================================================================
                 ##### 如何使用这个驱动程序 #####
 ===================================================================
 [..]
   (#) 启用 RNG控制器时钟使用 RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE) 函数。

   (#) 使用 RNG_Cmd() 函数激活 RNG 外设设备。

   (#) 等待直到 32 位随机数生成器包含有效的随机数据(使用轮询/中断模式)。
       更多详细信息，请参考"中断和标志管理功能"模块描述。

   (#) 使用 RNG_GetRandomNumber() 函数获取 32 位随机数

   (#) 如果需要另一个32位随机数，请转到步骤3。


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
#include "stm32f4xx_rng.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup RNG
  * 简介: RNG 驱动模块
  */
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx)
/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup RNG_Private_Functions
  */

/** @defgroup RNG_Group1 初始化和配置函数
 *  简介    初始化和配置函数
 *
@verbatim
 ===============================================================================
             ##### 初始化和配置函数 #####
 ===============================================================================
 [..] 本节提供的功能允许
   (+) 初始化RNG外设
   (+) 使能或禁用 RNG外设

@endverbatim
  */

/**
  * 简介:  将 RNG 外设寄存器取消初始化为其默认复位值。
  * 参数:  无
  * 返回值: 无
  */
void RNG_DeInit(void) {
    #if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx)
    /* 使能RNG 复位状态 */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_RNG, ENABLE);

    /* 释放RNG from 复位状态 */
    RCC_AHB2PeriphResetCmd(RCC_AHB2Periph_RNG, DISABLE);
    #endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F469_479xx */
    #if defined(STM32F410xx)
    /* 使能RNG 复位状态 */
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_RNG, ENABLE);

    /* 释放RNG from 复位状态 */
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_RNG, DISABLE);
    #endif /* STM32F410xx*/
}

/**
  * 简介:  启用或禁用 RNG 外设设备。
  * 参数:  NewState: RNG外设设备的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void RNG_Cmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 RNG */
        RNG->CR |= RNG_CR_RNGEN;
    } else {
        /* 禁用 RNG */
        RNG->CR &= ~RNG_CR_RNGEN;
    }
}

/** @defgroup RNG_Group2 得到32位随机数函数
 *  简介    得到32位随机数函数
 *

@verbatim
 ===============================================================================
                 ##### 得到32位随机数函数 #####
 ===============================================================================
 [..] 本节提供了一个函数，允许获取32位随机数

   (@)  在调用这个函数之前，你必须等待DRDY标志被设置，
        使用 RNG_GetFlagStatus(RNG_FLAG_DRDY) 函数。

@endverbatim
  */


/**
  * 简介:  返回一个 32 位随机数。
  *
  * 注意:   在调用此函数之前，您必须使用 RNG_GetFlagStatus(RNG_flag_DRDY)
			函数等待设置 DRDY(数据就绪)标志。
  * 注意:   每次读取随机数数据(使用 RNG_GetRandomNumber() 函数)
			时，RNG_FLAG_DRDY标志会自动清除。
  * 注意:   在种子错误的情况下，只要SECS位为"1"，随机数的生成就
			会中断。如果一个数字在RNG_DR 寄存器中可用，则不能使用它，
			因为它可能没有足够的熵。在这种情况下，建议清除 SEIS位
			(使用 RNG_ClearFlag(RNG_FLAG_SECS) 功能)，
			然后禁用并启用 RNG外设设备(使用 RNG_Cmd() 功能)
			以重新初始化并重新启动RNG。
  * 注意:   在时钟错误的情况下，由于PLL48CLK时钟不正确，
			RNG不再能够生成随机数。用户必须检查时钟控制器
			是否正确配置为提供RNG时钟并清除 CEIS位(使用
			RNG_ClearFlag(RNG_FLAG_CECS) 功能)。
			时钟错误对先前生成的随机数没有影响，
			并且可以使用 RNG_DR 寄存器内容。
  *
  * 参数:  无
  * 返回值: 32-bit 随机数.
  */
uint32_t RNG_GetRandomNumber(void) {
    /* 返回32 bit random number from the DR 寄存器 */
    return RNG->DR;
}



/** @defgroup RNG_Group3 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
             ##### 中断和标记管理函数 #####
 ===============================================================================

 [..] 本节提供的功能允许配置 RNG中断，并获取状态和清除标志以及中断挂起位。

 [..] RNG提供3个中断源和3个标志:

 *** Flags : ***
 ===============
 [..]
    (#) RNG_FLAG_DRDY :  在RNG_DR 寄存器包含有效随机数据的情况下。
		通过读取有效数据(使用 RNG_GetRandomNumber() 函数)来清除它。

    (#) RNG_FLAG_CECS : 在种子错误检测的情况下。

    (#) RNG_FLAG_SECS : 在时钟错误检测的情况下。

 *** 中断 ***
 ==================
 [..] 如果启用，则RNG中断处于挂起状态 :

   (#) 在RNG_DR 寄存器包含有效随机数据的情况下。
		一旦读取了RNG_DR 寄存器(使用 RNG_GetRandomNumber() 函数)，
		该中断源将被清除，直到计算出新的有效值;
   (#) 在种子错误的情况下 : 检测到以下故障序列之一:
       (++) 具有相同值(0或1)的64个以上连续位
       (++) 0 和1 的连续交替次数超过32次(0101010101…01)
       使用 RNG_ClearITPendingBit(RNG_IT_SEI) 函数清除该中断源;
   (#) 在时钟错误的情况下 : PLL48CLK(RNG外围时钟源)没有
		被正确地检测到(fPLL48CLK <fHCLK/16)。
		使用 RNG_ClearITPendingBit(RNG_IT_CEI) 功能清除此中断源。
       -@- 注意:在这种情况下，用户必须检查时钟控制器是否正确配置以提供RNG时钟。

 *** 管理RNG控制器事件 : ***
 ============================================
 [..] 用户应确定在其应用程序中将使用哪种模式来管理RNG控制器事件:轮询模式或中断模式。

   (#) 在轮询模式下，建议使用以函数:
       (++) RNG_GetFlagStatus() : 以检查是否发生标志事件。
       (++) RNG_ClearFlag()     : 以清除flags事件。

       -@@- RNG_ClearFlag()无法清除RNG_FLAG_DRDY。
			它仅通过读取随机数数据而被清除。

   (#)  在中断模式下，建议使用以下功能:
        (++) RNG_ITConfig()       : 以启用或禁用中断源。
        (++) RNG_GetITStatus()    : 以检查是否发生中断。
        (++) RNG_ClearITPendingBit() : 以清除中断未决位(对应的标志)。

@endverbatim
  */

/**
  * 简介:  启用或禁用 RNG 中断。
  * 注意:   RNG提供3个中断源，
  *           - 计算数据就绪事件(DRDY)，以及
  *           - 种子错误中断(SEI)和
  *           - 时钟错误中断(CEI)，
  *         所有这些中断源都是通过在CR 寄存器中设置IE位来启用的。
			但是，每个中断都有其特定的状态位(请参阅RNG_GetITStatus()
			函数)和清除位(请参见RNG_ClearITPendingBit() 函数，DRDY事件除外)。
  * 参数:  NewState: 新状态-> RNG 中断.
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void RNG_ITConfig(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 RNG 中断 */
        RNG->CR |= RNG_CR_IE;
    } else {
        /* 禁用 RNG 中断 */
        RNG->CR &= ~RNG_CR_IE;
    }
}

/**
  * 简介:  检查是否设置了指定的 RNG 标志。
  * 参数:  RNG_FLAG: 指定RNG flag to check.
  *          此参数可以是以下值之一:
  *            @arg RNG_FLAG_DRDY: Data Ready flag.
  *            @arg RNG_FLAG_CECS: Clock Error Current flag.
  *            @arg RNG_FLAG_SECS: Seed Error Current flag.
  * 返回值: 新状态-> RNG_FLAG (SET or RESET).
  */
FlagStatus RNG_GetFlagStatus(uint8_t RNG_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_RNG_GET_FLAG(RNG_FLAG));

    /* 检查 the status of the specified RNG flag */
    if ((RNG->SR & RNG_FLAG) != (uint8_t)RESET) {
        /* RNG_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* RNG_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回 RNG_FLAG 状态 */
    return  bitstatus;
}


/**
  * 简介:  清除 RNG 标志。
  * 参数:  RNG_FLAG: 指定要清除的标志。
  *          此参数可以是以下值的任意组合:
  *            @arg RNG_FLAG_CECS: Clock Error Current flag.
  *            @arg RNG_FLAG_SECS: Seed Error Current flag.
  * 注意:   RNG_FLAG_DRDY can not be cleared by RNG_ClearFlag() function.
  *         This flag is cleared only by reading the Random number data (using
  *         RNG_GetRandomNumber() function).
  * 返回值: 无
  */
void RNG_ClearFlag(uint8_t RNG_FLAG) {
    /* 检查参数 */
    assert_param(IS_RNG_CLEAR_FLAG(RNG_FLAG));
    /* 清除 selected RNG flags */
    RNG->SR = ~(uint32_t)(((uint32_t)RNG_FLAG) << 4);
}

/**
  * 简介:  检查指定的 RNG 中断是否发生。
  * 参数:  RNG_IT: 指定RNG interrupt source to check.
  *          此参数可以是以下值之一:
  *            @arg RNG_IT_CEI: Clock Error Interrupt.
  *            @arg RNG_IT_SEI: Seed Error Interrupt.
  * 返回值: 新状态-> RNG_IT (SET or RESET).
  */
ITStatus RNG_GetITStatus(uint8_t RNG_IT) {
    ITStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_RNG_GET_IT(RNG_IT));

    /* 检查 the status of the specified RNG 中断 */
    if ((RNG->SR & RNG_IT) != (uint8_t)RESET) {
        /* RNG_IT 被设置 */
        bitstatus = SET;
    } else {
        /* RNG_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回 RNG_IT 状态 */
    return bitstatus;
}


/**
  * 简介:  清除 RNG 中断挂起位。
  * 参数:  RNG_IT: 指定RNG 中断挂起位 bit(s) to clear.
  *          此参数可以是以下值的任意组合:
  *            @arg RNG_IT_CEI: Clock 错误中断.
  *            @arg RNG_IT_SEI: Seed 错误中断.
  * 返回值: 无
  */
void RNG_ClearITPendingBit(uint8_t RNG_IT) {
    /* 检查参数 */
    assert_param(IS_RNG_IT(RNG_IT));

    /* 清除所选RNG中断挂起位 */
    RNG->SR = (uint8_t)~RNG_IT;
}

#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F429_439xx || STM32F469_479xx */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
