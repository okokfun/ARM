/**
  ******************************************************************************
  * @file    system_stm32f4xx.c
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    09-November-2016
  * 简介:   CMSIS Cortex-M4设备外围访问层系统源文件。
  *          此文件包含 STM32F4xx 设备的系统时钟配置。
  *
  * 1.  此文件提供两个函数和一个全局变量，可从用户应用程序调用：
  *      - SystemInit(): 根据时钟xls工具中的配置，设置系统时钟(系统时钟源、PLL乘法器和
  *                      分频器系数、AHB/APBx预分频器和闪存设置)。此函数在复位后和分支到主程序
  *                      之前的启动时调用。
  *                      此调用在 "startup_stm32f4xx.s" 文件中进行。
  *
  *      - SystemCoreClock variable: 包含核心时钟(HCLK)，
  *                                  用户应用程序可以使用它来设置 SysTick 计时器或配置其他参数。
  *
  *      - SystemCoreClockUpdate(): 更新变量 SystemCoreClock，
  *                                 并且必须在程序执行期间更改核心时钟时调用。
  *
  * 2. 每次设备复位后，HSI(16 MHz)用作系统时钟源。
  *    然后，在"startup_stm32f4xx.s"文件中调用 SystemInit() 函数，以在分支到主程序之前配置系统时钟。
  *
  * 3. 如果用户选择的系统时钟源无法启动，SystemInit() 函数将不执行任何操作，
  *    HSI仍用作系统时钟源。用户可以在 SetSysClock() 函数中添加一些代码来处理此问题。
  *
  * 4. HSE晶体的默认值设置为25MHz，请参阅"stm32f4xx.h"文件中的"HSE_value"定义。
  *    当HSE直接或通过PLL用作系统时钟源时，如果您使用不同的晶体，则必须根据您自己的配置调整HSE值。
  *
  * 5. 此文件按如下方式配置系统时钟：
  *=============================================================================
  *=============================================================================
  *                    支持的 STM32F40xxx/41xxx 设备
  *-----------------------------------------------------------------------------
  *        系统时钟源                             | PLL (HSE)
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 168000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 168000000
  *-----------------------------------------------------------------------------
  *        AHB预分频器                            | 1
  *-----------------------------------------------------------------------------
  *        APB1 预分频器                          | 4
  *-----------------------------------------------------------------------------
  *        APB2 预分频器                          | 2
  *-----------------------------------------------------------------------------
  *        HSE Frequency(Hz)                      | 25000000
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 25
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 336
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 7
  *-----------------------------------------------------------------------------
  *        PLLI2S_N                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_R                               | NA
  *-----------------------------------------------------------------------------
  *        I2S input clock                        | NA
  *-----------------------------------------------------------------------------
  *        VDD(V)                                 | 3.3
  *-----------------------------------------------------------------------------
  *        Main regulator output voltage          | Scale1 mode
  *-----------------------------------------------------------------------------
  *        Flash Latency(WS)                      | 5
  *-----------------------------------------------------------------------------
  *        Prefetch Buffer                        | ON
  *-----------------------------------------------------------------------------
  *        Instruction cache                      | ON
  *-----------------------------------------------------------------------------
  *        Data cache                             | ON
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *-----------------------------------------------------------------------------
  *=============================================================================
  *=============================================================================
  *                    支持的 STM32F42xxx/43xxx devices
  *-----------------------------------------------------------------------------
  *        系统时钟源                             | PLL (HSE)
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 180000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 180000000
  *-----------------------------------------------------------------------------
  *        AHB 预分频器                           | 1
  *-----------------------------------------------------------------------------
  *        APB1 预分频器                          | 4
  *-----------------------------------------------------------------------------
  *        APB2 预分频器                          | 2
  *-----------------------------------------------------------------------------
  *        HSE Frequency(Hz)                      | 25000000
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 25
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 360
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 7
  *-----------------------------------------------------------------------------
  *        PLLI2S_N                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_R                               | NA
  *-----------------------------------------------------------------------------
  *        I2S input clock                        | NA
  *-----------------------------------------------------------------------------
  *        VDD(V)                                 | 3.3
  *-----------------------------------------------------------------------------
  *        Main regulator output voltage          | Scale1 mode
  *-----------------------------------------------------------------------------
  *        Flash Latency(WS)                      | 5
  *-----------------------------------------------------------------------------
  *        Prefetch Buffer                        | ON
  *-----------------------------------------------------------------------------
  *        Instruction cache                      | ON
  *-----------------------------------------------------------------------------
  *        Data cache                             | ON
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *-----------------------------------------------------------------------------
  *=============================================================================
  *=============================================================================
  *                         Supported STM32F401xx devices
  *-----------------------------------------------------------------------------
  *        系统时钟源                             | PLL (HSE)
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 84000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 84000000
  *-----------------------------------------------------------------------------
  *        AHB 预分频器                           | 1
  *-----------------------------------------------------------------------------
  *        APB1 预分频器                          | 2
  *-----------------------------------------------------------------------------
  *        APB2 预分频器                          | 1
  *-----------------------------------------------------------------------------
  *        HSE Frequency(Hz)                      | 25000000
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 25
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 336
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 4
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 7
  *-----------------------------------------------------------------------------
  *        PLLI2S_N                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_R                               | NA
  *-----------------------------------------------------------------------------
  *        I2S input clock                        | NA
  *-----------------------------------------------------------------------------
  *        VDD(V)                                 | 3.3
  *-----------------------------------------------------------------------------
  *        Main regulator output voltage          | Scale1 mode
  *-----------------------------------------------------------------------------
  *        Flash Latency(WS)                      | 2
  *-----------------------------------------------------------------------------
  *        Prefetch Buffer                        | ON
  *-----------------------------------------------------------------------------
  *        Instruction cache                      | ON
  *-----------------------------------------------------------------------------
  *        Data cache                             | ON
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *-----------------------------------------------------------------------------
  *=============================================================================
  *=============================================================================
  *                Supported STM32F411xx/STM32F410xx devices
  *-----------------------------------------------------------------------------
  *        系统时钟源                             | PLL (HSI)
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 100000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 100000000
  *-----------------------------------------------------------------------------
  *        AHB 预分频器                           | 1
  *-----------------------------------------------------------------------------
  *        APB1 分频器                            | 2
  *-----------------------------------------------------------------------------
  *        APB2 分频器                            | 1
  *-----------------------------------------------------------------------------
  *        HSI Frequency(Hz)                      | 16000000
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 16
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 400
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 4
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 7
  *-----------------------------------------------------------------------------
  *        PLLI2S_N                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_R                               | NA
  *-----------------------------------------------------------------------------
  *        I2S input clock                        | NA
  *-----------------------------------------------------------------------------
  *        VDD(V)                                 | 3.3
  *-----------------------------------------------------------------------------
  *        Main regulator output voltage          | Scale1 mode
  *-----------------------------------------------------------------------------
  *        Flash Latency(WS)                      | 3
  *-----------------------------------------------------------------------------
  *        Prefetch Buffer                        | ON
  *-----------------------------------------------------------------------------
  *        Instruction cache                      | ON
  *-----------------------------------------------------------------------------
  *        Data cache                             | ON
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *-----------------------------------------------------------------------------
  *=============================================================================
  *=============================================================================
  *                         Supported STM32F446xx devices
  *-----------------------------------------------------------------------------
  *        系统时钟源                             | PLL (HSE)
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 180000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 180000000
  *-----------------------------------------------------------------------------
  *        AHB 预分频器                           | 1
  *-----------------------------------------------------------------------------
  *        APB1 分频器                            | 4
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler                         | 2
  *-----------------------------------------------------------------------------
  *        HSE Frequency(Hz)                      | 8000000
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 8
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 360
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 7
  *-----------------------------------------------------------------------------
  *        PLL_R                                  | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_M                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_N                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_P                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_Q                               | NA
  *-----------------------------------------------------------------------------
  *        PLLI2S_R                               | NA
  *-----------------------------------------------------------------------------
  *        I2S input clock                        | NA
  *-----------------------------------------------------------------------------
  *        VDD(V)                                 | 3.3
  *-----------------------------------------------------------------------------
  *        Main regulator output voltage          | Scale1 mode
  *-----------------------------------------------------------------------------
  *        Flash Latency(WS)                      | 5
  *-----------------------------------------------------------------------------
  *        Prefetch Buffer                        | ON
  *-----------------------------------------------------------------------------
  *        Instruction cache                      | ON
  *-----------------------------------------------------------------------------
  *        Data cache                             | ON
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *-----------------------------------------------------------------------------
  *=============================================================================
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

/** @addtogroup STM32F4xx_System_Private_Includes
  */

#include "stm32f4xx.h"


/** @addtogroup STM32F4xx_System_Private_TypesDefinitions
  */


/** @addtogroup STM32F4xx_System_Private_Defines
  */

/************************* Miscellaneous Configuration ************************/
/*!< 如果需要使用安装在 STM324xG_EVAL/STM324x7I_EVAL/STM324x9I_EVAL 板上的外部 SRAM或SDRAM作为数据存储器，请取消注释以下行  */
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx) || defined(STM32F413_423xx)
/* #define DATA_IN_ExtSRAM */
#endif /* STM32F40_41xxx || STM32F427_437x || STM32F429_439xx || STM32F469_479xx || STM32F413_423xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
/* #define DATA_IN_ExtSDRAM */
#endif /* STM32F427_437x || STM32F429_439xx || STM32F446xx || STM32F469_479xx */

#if defined(STM32F410xx) || defined(STM32F411xE)
/*!< 如果您需要通过 STM32F103 微控制器的 STLINK MCO 引脚通过 HSE 旁路对 STM32F410xx/STM32F411xE 进行时钟，请取消注释以下行。频率不能更改，并且固定在8MHz。
     Nucleo 板所需的硬件配置:
     – SB54, SB55 OFF
     – R35 removed
     – SB16, SB50 ON */
/* #define USE_HSE_BYPASS */

#if defined(USE_HSE_BYPASS)
#define HSE_BYPASS_INPUT_FREQUENCY   8000000
#endif /* USE_HSE_BYPASS */
#endif /* STM32F410xx || STM32F411xE */

/*!< 如果需要在内部 SRAM 中重新定位矢量表，请取消注释以下行。 */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00 /*!< 矢量表基偏移字段。 
                                   此值必须是 0x200 的倍数。 */
/******************************************************************************/

/************************* PLL参数 *************************************/
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F469_479xx)
/* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N */
#define PLL_M      25
#elif defined(STM32F412xG) || defined(STM32F413_423xx) || defined (STM32F446xx)
#define PLL_M      8
#elif defined (STM32F410xx) || defined (STM32F411xE)
#if defined(USE_HSE_BYPASS)
#define PLL_M      8
#else /* !USE_HSE_BYPASS */
#define PLL_M      16
#endif /* USE_HSE_BYPASS */
#else
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F469_479xx */

/* USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ */
#define PLL_Q      7

#if defined(STM32F446xx)
/* I2S、SAI、SYSTEM 和 SPDIF的PLL分频因子: Clock =  PLL_VCO / PLLR */
#define PLL_R      7
#elif defined(STM32F412xG) || defined(STM32F413_423xx)
#define PLL_R      2
#else
#endif /* STM32F446xx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
#define PLL_N      360
/* SYSCLK = PLL_VCO / PLL_P */
#define PLL_P      2
#endif /* STM32F427_437x || STM32F429_439xx || STM32F446xx || STM32F469_479xx */

#if defined (STM32F40_41xxx)
#define PLL_N      336
/* SYSCLK = PLL_VCO / PLL_P */
#define PLL_P      2
#endif /* STM32F40_41xxx */

#if defined(STM32F401xx)
#define PLL_N      336
/* SYSCLK = PLL_VCO / PLL_P */
#define PLL_P      4
#endif /* STM32F401xx */

#if defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F412xG) || defined(STM32F413_423xx)
#define PLL_N      400
/* SYSCLK = PLL_VCO / PLL_P */
#define PLL_P      4
#endif /* STM32F410xx || STM32F411xE || STM32F412xG || STM32F413_423xx */

/******************************************************************************/


/** @addtogroup STM32F4xx_System_Private_Macros
  */


/** @addtogroup STM32F4xx_System_Private_Variables
  */

#if defined(STM32F40_41xxx)
uint32_t SystemCoreClock = 168000000;
#endif /* STM32F40_41xxx */

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
uint32_t SystemCoreClock = 180000000;
#endif /* STM32F427_437x || STM32F429_439xx || STM32F446xx || STM32F469_479xx */

#if defined(STM32F401xx)
uint32_t SystemCoreClock = 84000000;
#endif /* STM32F401xx */

#if defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F412xG) || defined(STM32F413_423xx)
uint32_t SystemCoreClock = 100000000;
#endif /* STM32F410xx || STM32F401xE || STM32F412xG || STM32F413_423xx */

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};


/** @addtogroup STM32F4xx_System_Private_FunctionPrototypes
  */

static void SetSysClock(void);

#if defined(DATA_IN_ExtSRAM) || defined(DATA_IN_ExtSDRAM)
static void SystemInit_ExtMemCtl(void);
#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */


/** @addtogroup STM32F4xx_System_Private_Functions
  */

/**
  * 简介:  设置微控制器系统
  *         初始化嵌入式闪存接口、PLL并更新 SystemFrequency变量。
  * 参数:  无
  * 返回值: 无
  */
void SystemInit(void) {
    /* FPU 设置 ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* 设置 CP10 和 CP11 完全访问 */
#endif
    /* 将RCC 时钟配置重置为默认重置状态 ------------*/
    /* 重置 HSION bit */
    RCC->CR |= (uint32_t)0x00000001;

    /* 重置 CFGR 寄存器 */
    RCC->CFGR = 0x00000000;

    /* 重置 HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* 重置 PLLCFGR R 寄存器 */
    RCC->PLLCFGR = 0x24003010;

    /* 重置 HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* 禁用所有中断 */
    RCC->CIR = 0x00000000;

#if defined(DATA_IN_ExtSRAM) || defined(DATA_IN_ExtSDRAM)
    SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */

    /* 配置系统时钟源 , PLL 乘法器和除法器因子，
       AHB/APBx 预分频器和 Flash 设置 ----------------------------------*/
    SetSysClock();

    /* 配置矢量表位置添加偏移地址 ------------------*/
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* 内部 SRAM 中的矢量表重定位 */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* 内部FLASH中的矢量表重定位 */
#endif
}

/**
   * 简介:  根据时钟寄存器值更新 SystemCoreClock 变量。
  *         SystemCoreClock 变量包含核心时钟(HCLK)，用户应用程序可以使用它来设置 SysTick 计时器或配置其他参数。
  *
  * @note   每次核心时钟(HCLK)发生变化时，都必须调用此函数来更新 SystemCoreClock
  *         变量值。否则，基于此变量的任何配置都将是不正确的。
  *
  * @note   - 通过该函数计算的系统频率不是芯片中的实际频率。它是根据预定义的常数和选定的时钟源进行计算的：
  *
  *           - 如果 SYSCLK 源是 HSI，SystemCoreClock 将包含 HSI_VALUE(*)
  *
  *           - 如果 SYSCLK 源为 HSE，SystemCoreClock将包含 HSE_VALUE(**)
  *
  *           - 如果 SYSCLK 源是PLL，则SystemCoreClock将包含 HSE_VALUE(**)或HSI_VALE(*)乘以/除以PLL因子。
  *
  *         (*) HSI_VALUE 是 stm32f44xx.h 文件中定义的常数(默认值16 MHz)，但实际值可能会根据电压和温度的变化而变化。
  *
  *         (**) HSE_VALUE 是 stm32f44xx.h 文件中定义的常数(默认值25 MHz)，
  *              用户必须确保 HSE_VALUE 与所用晶体的实际频率相同。否则，此函数可能会产生错误的结果。
  *
  *         - 当使用 HSE 晶体的分数值时，该函数的结果可能不正确。
  *
  * 参数:  无
  * 返回值: 无
  */
void SystemCoreClockUpdate(void) {
    uint32_t tmp = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
    uint32_t pllr = 2;
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */
    /* Get SYSCLK source -------------------------------------------------------*/
    tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp) {
    case 0x00:  /* HSI 用作系统时钟源           */
        SystemCoreClock = HSI_VALUE;
        break;
    case 0x04:  /* HSE 用作系统时钟源           */
        SystemCoreClock = HSE_VALUE;
        break;
    case 0x08:  /* PLL P 用作系统时钟源           */
        /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
          SYSCLK = PLL_VCO / PLL_P
          */
        pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
        pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
        if (pllsource != 0) {
            /* HSE 用作PLL时钟源 */
            pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        } else {
            /* HSI 用作PLL时钟源 */
            pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        }
#elif defined(STM32F410xx) || defined(STM32F411xE)
#if defined(USE_HSE_BYPASS)
        if (pllsource != 0) {
            /* HSE 用作PLL时钟源 */
            pllvco = (HSE_BYPASS_INPUT_FREQUENCY / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        }
#else
        if (pllsource == 0) {
            /* HSI 用作PLL时钟源 */
            pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        }
#endif /* USE_HSE_BYPASS */
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F412xG || STM32F413_423xx ||  STM32F446xx || STM32F469_479xx */
        pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >>16) + 1 ) *2;
        SystemCoreClock = pllvco/pllp;
        break;
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
    case 0x0C:  /* PLL R 用作系统时钟源           */
        /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
          SYSCLK = PLL_VCO / PLL_R
          */
        pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
        pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;
        if (pllsource != 0) {
            /* HSE 用作PLL时钟源 */
            pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        } else {
            /* HSI 用作PLL时钟源 */
            pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
        }

        pllr = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >>28) + 1 ) *2;
        SystemCoreClock = pllvco/pllr;
        break;
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */
    default:
        SystemCoreClock = HSI_VALUE;
        break;
    }
    /* 计算 HCLK 频率 --------------------------------------------------*/
    /* 获取 HCLK 预分频器 */
    tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
    /* HCLK 频率 */
    SystemCoreClock >>= tmp;
}

/**
  * 简介:  配置系统时钟源, PLL 乘法器和除法器因子，
  *         AHB/APBx 预分频器和 Flash 设置
  * @Note   这个函数应该只在 RCC 时钟配置重置为默认重置状态(在 SystemInit() 函数中完成)时调用。
  * 参数:  无
  * 返回值: 无
  */
static void SetSysClock(void) {
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)|| defined(STM32F469_479xx)
    /******************************************************************************/
    /*            PLL (clocked by HSE) 用作系统时钟源                          */
    /******************************************************************************/
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    /* 等待HSE准备就绪，如果达到超时，则退出 */
    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* 选择调节器电压输出比例1模式 */
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
        PWR->CR |= PWR_CR_VOS;

        /* HCLK = SYSCLK / 1*/
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) ||  defined(STM32F412xG) || defined(STM32F446xx) || defined(STM32F469_479xx)
        /* PCLK2 = HCLK / 2*/
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

        /* PCLK1 = HCLK / 4*/
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
#endif /* STM32F40_41xxx || STM32F427_437x || STM32F429_439xx  || STM32F412xG || STM32F446xx || STM32F469_479xx */

#if defined(STM32F401xx) || defined(STM32F413_423xx)
        /* PCLK2 = HCLK / 1*/
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK / 2*/
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
#endif /* STM32F401xx || STM32F413_423xx */

#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F469_479xx)
        /* 配置main PLL */
        RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                       (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);
#endif /* STM32F40_41xxx || STM32F401xx || STM32F427_437x || STM32F429_439xx || STM32F469_479xx */

#if  defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
        /* 配置main PLL */
        RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                       (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24) | (PLL_R << 28);
#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx */

        /* 启用主 PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* 等待主 PLL 准备就绪 */
        while((RCC->CR & RCC_CR_PLLRDY) == 0) {
        }

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
        /* 启用 Over-drive 将时钟频率扩展到 180 Mhz */
        PWR->CR |= PWR_CR_ODEN;
        while((PWR->CSR & PWR_CSR_ODRDY) == 0) {
        }
        PWR->CR |= PWR_CR_ODSWEN;
        while((PWR->CSR & PWR_CSR_ODSWRDY) == 0) {
        }
        /* 配置闪存预取、指令缓存、数据缓存和等待状态 */
        FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
#endif /* STM32F427_437x || STM32F429_439xx || STM32F446xx || STM32F469_479xx */

#if defined(STM32F40_41xxx)  || defined(STM32F412xG)
        /* 配置闪存预取、指令缓存、数据缓存和等待状态 */
        FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
#endif /* STM32F40_41xxx  || STM32F412xG */

#if defined(STM32F413_423xx)
        /* 配置闪存预取、指令缓存、数据缓存和等待状态 */
        FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_3WS;
#endif /* STM32F413_423xx */

#if defined(STM32F401xx)
        /* 配置闪存预取、指令缓存、数据缓存和等待状态 */
        FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;
#endif /* STM32F401xx */

        /* 选择主 PLL 作为系统时钟源           */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= RCC_CFGR_SW_PLL;

        /* 等待主 PLL 用作系统时钟源           */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
        {
        }
    } else {
        /* 如果HSE未能启动，应用程序将具有错误的时钟配置。用户可以在此处添加一些代码来处理此错误 */
    }
#elif defined(STM32F410xx) || defined(STM32F411xE)
#if defined(USE_HSE_BYPASS)
    /******************************************************************************/
    /*            PLL (clocked by HSE) 用作系统时钟源                          */
    /******************************************************************************/
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* 启用 HSE 和HSE BYPASS */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON | RCC_CR_HSEBYP);

    /* 等待HSE准备就绪，如果达到超时，则退出 */
    do {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET) {
        HSEStatus = (uint32_t)0x01;
    } else {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01) {
        /* 选择调节器电压输出比例1模式 */
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
        PWR->CR |= PWR_CR_VOS;

        /* HCLK = SYSCLK / 1*/
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK / 2*/
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

        /* PCLK1 = HCLK / 4*/
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

        /* 配置main PLL */
        RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                       (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

        /* 启用主 PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* 等待主 PLL 准备就绪 */
        while((RCC->CR & RCC_CR_PLLRDY) == 0) {
        }

        /* 配置闪存预取、指令缓存、数据缓存和等待状态 */
        FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;

        /* 选择主 PLL 作为系统时钟源           */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= RCC_CFGR_SW_PLL;

        /* 等待主 PLL 用作系统时钟源           */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
        {
        }
    } else {
        /* 如果HSE未能启动，应用程序将具有错误的时钟配置。用户可以在此处添加一些代码来处理此错误 */
    }
#else /* HSI will be 用作PLL时钟源 */
    /* 选择调节器电压输出比例1模式 */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    /* HCLK = SYSCLK / 1*/
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    /* PCLK2 = HCLK / 2*/
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

    /* PCLK1 = HCLK / 4*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    /* 配置main PLL */
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (PLL_Q << 24);

    /* 启用主 PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* 等待主 PLL 准备就绪 */
    while((RCC->CR & RCC_CR_PLLRDY) == 0) {
    }

    /* 配置闪存预取、指令缓存、数据缓存和等待状态 */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_2WS;

    /* 选择主 PLL 作为系统时钟源           */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    /* 等待主 PLL 用作系统时钟源           */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
#endif /* USE_HSE_BYPASS */
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F469_479xx */
}
#if defined (DATA_IN_ExtSRAM) && defined (DATA_IN_ExtSDRAM)
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
/**
  * 简介:  设置外部内存控制器。
  *         在跳转到 main 之前，在 startup_stm32f4xx.s 中调用。
  *         此函数配置外部存储器(SRAM/SDRAM)
  *         该 SRAM/SDRAM 将用作程序数据存储器(包括堆和堆栈)。
  * 参数:  无
  * 返回值: 无
  */
void SystemInit_ExtMemCtl(void) {
    __IO uint32_t tmp = 0x00;

    register uint32_t tmpreg = 0, timeout = 0xFFFF;
    register uint32_t index;

    /* 启用 GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH and GPIOI 接口时钟 */
    RCC->AHB1ENR |= 0x000001F8;

    /* RCC 外围时钟启用后的延迟 */
    tmp = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);

    /* 将 PDx 引脚连接到 FMC 复用功能 */
    GPIOD->AFR[0]  = 0x00CCC0CC;
    GPIOD->AFR[1]  = 0xCCCCCCCC;
    /* 在复用功能模式下配置 PDx 引脚 */
    GPIOD->MODER   = 0xAAAA0A8A;
    /* 将 PDx 引脚速度配置为 100 MHz */
    GPIOD->OSPEEDR = 0xFFFF0FCF;
    /* 配置 PDx 引脚输出类型为推拉 */
    GPIOD->OTYPER  = 0x00000000;
    /* PDx引脚无上拉、下拉 */
    GPIOD->PUPDR   = 0x00000000;

    /* 将 PEx 引脚连接到 FMC 复用功能 */
    GPIOE->AFR[0]  = 0xC00CC0CC;
    GPIOE->AFR[1]  = 0xCCCCCCCC;
    /* 在复用功能模式下配置 PEx 引脚 */
    GPIOE->MODER   = 0xAAAA828A;
    /* 将 PEx 引脚速度配置为 100 MHz */
    GPIOE->OSPEEDR = 0xFFFFC3CF;
    /* 配置 PEx 引脚输出类型为推拉 */
    GPIOE->OTYPER  = 0x00000000;
    /* PEx 引脚无上拉、下拉 */
    GPIOE->PUPDR   = 0x00000000;

    /* 将 PFx 引脚连接到 FMC 复用功能 */
    GPIOF->AFR[0]  = 0xCCCCCCCC;
    GPIOF->AFR[1]  = 0xCCCCCCCC;
    /* 在复用功能模式下配置 PFx 引脚 */
    GPIOF->MODER   = 0xAA800AAA;
    /* 将 PEx 引脚速度配置为 50 MHz */
    GPIOF->OSPEEDR = 0xAA800AAA;
    /* 配置 PFx 引脚输出类型为推拉 */
    GPIOF->OTYPER  = 0x00000000;
    /* PFx 引脚无上拉、下拉 */
    GPIOF->PUPDR   = 0x00000000;

    /* 将 PGx 引脚连接到 FMC 复用功能 */
    GPIOG->AFR[0]  = 0xCCCCCCCC;
    GPIOG->AFR[1]  = 0xCCCCCCCC;
    /* 在复用功能模式下配置 PGx 引脚 */
    GPIOG->MODER   = 0xAAAAAAAA;
    /* 将 PGx 引脚速度配置为 50 MHz */
    GPIOG->OSPEEDR = 0xAAAAAAAA;
    /* 配置 PGx 引脚输出类型为推拉 */
    GPIOG->OTYPER  = 0x00000000;
    /* PGx 引脚无上拉、下拉 */
    GPIOG->PUPDR   = 0x00000000;

    /* 将 PHx 引脚连接到 FMC 复用功能 */
    GPIOH->AFR[0]  = 0x00C0CC00;
    GPIOH->AFR[1]  = 0xCCCCCCCC;
    /* 在复用功能模式下配置 PHx 引脚 */
    GPIOH->MODER   = 0xAAAA08A0;
    /* 将 PHx 引脚速度配置为 50 MHz */
    GPIOH->OSPEEDR = 0xAAAA08A0;
    /* 配置 PHx 引脚输出类型为推拉 */
    GPIOH->OTYPER  = 0x00000000;
    /* PHx 引脚无上拉、下拉 */
    GPIOH->PUPDR   = 0x00000000;

    /* 将 PIx 引脚连接到 FMC 复用功能 */
    GPIOI->AFR[0]  = 0xCCCCCCCC;
    GPIOI->AFR[1]  = 0x00000CC0;
    /* 在复用功能模式下配置 PIx 引脚 */
    GPIOI->MODER   = 0x0028AAAA;
    /* 将 PIx 引脚速度配置为 50 MHz */
    GPIOI->OSPEEDR = 0x0028AAAA;
    /* 配置 PIx 引脚输出类型为推拉 */
    GPIOI->OTYPER  = 0x00000000;
    /* PIx 引脚无上拉、下拉 */
    GPIOI->PUPDR   = 0x00000000;

    /*-- FMC 定义 -------------------------------------------------------*/
    /* 启用 FMC 接口时钟 */
    RCC->AHB3ENR |= 0x00000001;
    /* RCC 外围时钟启用后的延迟 */
    tmp = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);

    FMC_Bank5_6->SDCR[0] = 0x000019E4;
    FMC_Bank5_6->SDTR[0] = 0x01115351;

    /* SDRAM 初始化序列 */
    /* 时钟启用命令 */
    FMC_Bank5_6->SDCMR = 0x00000011;
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    while((tmpreg != 0) && (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    }

    /* Delay */
    for (index = 0; index<1000; index++);

    /* PALL command */
    FMC_Bank5_6->SDCMR = 0x00000012;
    timeout = 0xFFFF;
    while((tmpreg != 0) && (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    }

    /*自动刷新命令 */
    FMC_Bank5_6->SDCMR = 0x00000073;
    timeout = 0xFFFF;
    while((tmpreg != 0) && (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    }

    /* MRD 寄存器程序 */
    FMC_Bank5_6->SDCMR = 0x00046014;
    timeout = 0xFFFF;
    while((tmpreg != 0) && (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    }

    /* 设置刷新计数 */
    tmpreg = FMC_Bank5_6->SDRTR;
    FMC_Bank5_6->SDRTR = (tmpreg | (0x0000027C<<1));

    /* 禁用写保护 */
    tmpreg = FMC_Bank5_6->SDCR[0];
    FMC_Bank5_6->SDCR[0] = (tmpreg & 0xFFFFFDFF);

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)
    /* 配置并启用 Bank1_SRAM2 */
    FMC_Bank1->BTCR[2]  = 0x00001011;
    FMC_Bank1->BTCR[3]  = 0x00000201;
    FMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx */
#if defined(STM32F469xx) || defined(STM32F479xx)
    /* 配置并启用 Bank1_SRAM2 */
    FMC_Bank1->BTCR[2]  = 0x00001091;
    FMC_Bank1->BTCR[3]  = 0x00110212;
    FMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif /* STM32F469xx || STM32F479xx */

    (void)(tmp);
}
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469xx || STM32F479xx */
#elif defined (DATA_IN_ExtSRAM)
/**
  * 简介:  设置外部内存控制器。在跳转到__main 之前在 startup_stm32f4xx.s 中调用
  * 参数:  无
  * 返回值: 无
  */
/**
  * 简介:  设置外部内存控制器。
  *         在跳转到 main 之前，在 startup_stm32f4xx.s 中调用。
  *         此功能配置安装在 STM324xG_EVAL/STM324x7I板上的外部 SRAM
  *         该 SRAM 将用作程序数据存储器(包括堆和堆栈)。
  * 参数:  无
  * 返回值: 无
  */
void SystemInit_ExtMemCtl(void) {
    /*-- GPIOs 定义 -----------------------------------------------------*/
    /*
     +-------------------+--------------------+------------------+--------------+
     +                       SRAM pins assignment                               +
     +-------------------+--------------------+------------------+--------------+
     | PD0  <-> FMC_D2  | PE0  <-> FMC_NBL0 | PF0  <-> FMC_A0 | PG0 <-> FMC_A10 |
     | PD1  <-> FMC_D3  | PE1  <-> FMC_NBL1 | PF1  <-> FMC_A1 | PG1 <-> FMC_A11 |
     | PD4  <-> FMC_NOE | PE3  <-> FMC_A19  | PF2  <-> FMC_A2 | PG2 <-> FMC_A12 |
     | PD5  <-> FMC_NWE | PE4  <-> FMC_A20  | PF3  <-> FMC_A3 | PG3 <-> FMC_A13 |
     | PD8  <-> FMC_D13 | PE7  <-> FMC_D4   | PF4  <-> FMC_A4 | PG4 <-> FMC_A14 |
     | PD9  <-> FMC_D14 | PE8  <-> FMC_D5   | PF5  <-> FMC_A5 | PG5 <-> FMC_A15 |
     | PD10 <-> FMC_D15 | PE9  <-> FMC_D6   | PF12 <-> FMC_A6 | PG9 <-> FMC_NE2 |
     | PD11 <-> FMC_A16 | PE10 <-> FMC_D7   | PF13 <-> FMC_A7 |-----------------+
     | PD12 <-> FMC_A17 | PE11 <-> FMC_D8   | PF14 <-> FMC_A8 |
     | PD13 <-> FMC_A18 | PE12 <-> FMC_D9   | PF15 <-> FMC_A9 |
     | PD14 <-> FMC_D0  | PE13 <-> FMC_D10  |-----------------+
     | PD15 <-> FMC_D1  | PE14 <-> FMC_D11  |
     |                  | PE15 <-> FMC_D12  |
     +------------------+------------------+
    */
    /* 启用 GPIOD, GPIOE, GPIOF and GPIOG 接口时钟 */
    RCC->AHB1ENR   |= 0x00000078;

    /* 将 PDx 引脚连接到 FMC 复用功能 */
    GPIOD->AFR[0]  = 0x00cc00cc;
    GPIOD->AFR[1]  = 0xcccccccc;
    /* 在复用功能模式下配置 PDx 引脚 */
    GPIOD->MODER   = 0xaaaa0a0a;
    /* 将 PDx 引脚速度配置为 100 MHz */
    GPIOD->OSPEEDR = 0xffff0f0f;
    /* 配置 PDx 引脚输出类型为推拉 */
    GPIOD->OTYPER  = 0x00000000;
    /* PDx引脚无上拉、下拉 */
    GPIOD->PUPDR   = 0x00000000;

    /* 将 PEx 引脚连接到 FMC 复用功能 */
    GPIOE->AFR[0]  = 0xcccccccc;
    GPIOE->AFR[1]  = 0xcccccccc;
    /* 在复用功能模式下配置 PEx 引脚 */
    GPIOE->MODER   = 0xaaaaaaaa;
    /* 将 PEx 引脚速度配置为 100 MHz */
    GPIOE->OSPEEDR = 0xffffffff;
    /* 配置 PEx 引脚输出类型为推拉 */
    GPIOE->OTYPER  = 0x00000000;
    /* PEx 引脚无上拉、下拉 */
    GPIOE->PUPDR   = 0x00000000;

    /* 将 PFx 引脚连接到 FMC 复用功能 */
    GPIOF->AFR[0]  = 0x00cccccc;
    GPIOF->AFR[1]  = 0xcccc0000;
    /* 在复用功能模式下配置 PFx 引脚 */
    GPIOF->MODER   = 0xaa000aaa;
    /* 将 PFx 引脚速度配置为 100 MHz */
    GPIOF->OSPEEDR = 0xff000fff;
    /* 配置 PFx 引脚输出类型为推拉 */
    GPIOF->OTYPER  = 0x00000000;
    /* PFx 引脚无上拉、下拉 */
    GPIOF->PUPDR   = 0x00000000;

    /* 将 PGx 引脚连接到 FMC 复用功能 */
    GPIOG->AFR[0]  = 0x00cccccc;
    GPIOG->AFR[1]  = 0x000000c0;
    /* 在复用功能模式下配置 PGx 引脚 */
    GPIOG->MODER   = 0x00080aaa;
    /* 将 PGx 引脚速度配置为 100 MHz */
    GPIOG->OSPEEDR = 0x000c0fff;
    /* 配置 PGx 引脚输出类型为推拉 */
    GPIOG->OTYPER  = 0x00000000;
    /* PGx 引脚无上拉、下拉 */
    GPIOG->PUPDR   = 0x00000000;

    /*-- FMC 定义 ------------------------------------------------------*/
    /* 启用 FMC/FSMC 接口时钟 */
    RCC->AHB3ENR         |= 0x00000001;

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
    /* 配置并启用 Bank1_SRAM2 */
    FMC_Bank1->BTCR[2]  = 0x00001011;
    FMC_Bank1->BTCR[3]  = 0x00000201;
    FMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F446xx || STM32F469_479xx */

#if defined(STM32F40_41xxx)
    /* 配置并启用 Bank1_SRAM2 */
    FSMC_Bank1->BTCR[2]  = 0x00001011;
    FSMC_Bank1->BTCR[3]  = 0x00000201;
    FSMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif  /* STM32F40_41xxx */

    /*
      Bank1_SRAM2配置如下：
      如果是FSMC配置
      NORSRAMTimingStructure.FSMC_AddressSetupTime = 1;
      NORSRAMTimingStructure.FSMC_AddressHoldTime = 0;
      NORSRAMTimingStructure.FSMC_DataSetupTime = 2;
      NORSRAMTimingStructure.FSMC_BusTurnAroundDuration = 0;
      NORSRAMTimingStructure.FSMC_CLKDivision = 0;
      NORSRAMTimingStructure.FSMC_DataLatency = 0;
      NORSRAMTimingStructure.FSMC_AccessMode = FMC_AccessMode_A;

      FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM2;
      FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
      FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
      FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
      FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
      FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
      FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
      FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
      FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
      FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
      FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
      FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &NORSRAMTimingStructure;
      FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &NORSRAMTimingStructure;

      如果是FMC配置
      NORSRAMTimingStructure.FMC_AddressSetupTime = 1;
      NORSRAMTimingStructure.FMC_AddressHoldTime = 0;
      NORSRAMTimingStructure.FMC_DataSetupTime = 2;
      NORSRAMTimingStructure.FMC_BusTurnAroundDuration = 0;
      NORSRAMTimingStructure.FMC_CLKDivision = 0;
      NORSRAMTimingStructure.FMC_DataLatency = 0;
      NORSRAMTimingStructure.FMC_AccessMode = FMC_AccessMode_A;

      FMC_NORSRAMInitStructure.FMC_Bank = FMC_Bank1_NORSRAM2;
      FMC_NORSRAMInitStructure.FMC_DataAddressMux = FMC_DataAddressMux_Disable;
      FMC_NORSRAMInitStructure.FMC_MemoryType = FMC_MemoryType_SRAM;
      FMC_NORSRAMInitStructure.FMC_MemoryDataWidth = FMC_MemoryDataWidth_16b;
      FMC_NORSRAMInitStructure.FMC_BurstAccessMode = FMC_BurstAccessMode_Disable;
      FMC_NORSRAMInitStructure.FMC_AsynchronousWait = FMC_AsynchronousWait_Disable;
      FMC_NORSRAMInitStructure.FMC_WaitSignalPolarity = FMC_WaitSignalPolarity_Low;
      FMC_NORSRAMInitStructure.FMC_WrapMode = FMC_WrapMode_Disable;
      FMC_NORSRAMInitStructure.FMC_WaitSignalActive = FMC_WaitSignalActive_BeforeWaitState;
      FMC_NORSRAMInitStructure.FMC_WriteOperation = FMC_WriteOperation_Enable;
      FMC_NORSRAMInitStructure.FMC_WaitSignal = FMC_WaitSignal_Disable;
      FMC_NORSRAMInitStructure.FMC_ExtendedMode = FMC_ExtendedMode_Disable;
      FMC_NORSRAMInitStructure.FMC_WriteBurst = FMC_WriteBurst_Disable;
      FMC_NORSRAMInitStructure.FMC_ContinousClock = FMC_CClock_SyncOnly;
      FMC_NORSRAMInitStructure.FMC_ReadWriteTimingStruct = &NORSRAMTimingStructure;
      FMC_NORSRAMInitStructure.FMC_WriteTimingStruct = &NORSRAMTimingStructure;
    */

}
#elif defined (DATA_IN_ExtSDRAM)
/**
  * 简介:  设置外部内存控制器。
  *         在跳转到 main 之前，在 startup_stm32f4xx.s 中调用。
  *         This function configures the external SDRAM mounted on STM324x9I_EVAL board
  *         This SDRAM will be used as program data memory (including heap and stack).
  * 参数:  无
  * 返回值: 无
  */
void SystemInit_ExtMemCtl(void) {
    register uint32_t tmpreg = 0, timeout = 0xFFFF;
    register uint32_t index;

    /* Enable GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH and GPIOI interface
        clock */
    RCC->AHB1ENR |= 0x000001FC;

    /* 将PCx引脚连接至FMC 备用函数 */
    GPIOC->AFR[0]  = 0x0000000c;
    GPIOC->AFR[1]  = 0x00007700;
    /* Configure PCx pins in Alternate function mode */
    GPIOC->MODER   = 0x00a00002;
    /* 将 PCx 引脚速度配置为 50 MHz */
    GPIOC->OSPEEDR = 0x00a00002;
    /* 配置 PCx 引脚输出类型为推拉 */
    GPIOC->OTYPER  = 0x00000000;
    /* No pull-up, pull-down for PCx pins */
    GPIOC->PUPDR   = 0x00500000;

    /* 将 PDx 引脚连接到 FMC 复用功能 */
    GPIOD->AFR[0]  = 0x000000CC;
    GPIOD->AFR[1]  = 0xCC000CCC;
    /* 在复用功能模式下配置 PDx 引脚 */
    GPIOD->MODER   = 0xA02A000A;
    /* 将 PDx 引脚速度配置为 50 MHz */
    GPIOD->OSPEEDR = 0xA02A000A;
    /* 配置 PDx 引脚输出类型为推拉 */
    GPIOD->OTYPER  = 0x00000000;
    /* PDx引脚无上拉、下拉 */
    GPIOD->PUPDR   = 0x00000000;

    /* 将 PEx 引脚连接到 FMC 复用功能 */
    GPIOE->AFR[0]  = 0xC00000CC;
    GPIOE->AFR[1]  = 0xCCCCCCCC;
    /* 在复用功能模式下配置 PEx 引脚 */
    GPIOE->MODER   = 0xAAAA800A;
    /* 将 PEx 引脚速度配置为 50 MHz */
    GPIOE->OSPEEDR = 0xAAAA800A;
    /* 配置 PEx 引脚输出类型为推拉 */
    GPIOE->OTYPER  = 0x00000000;
    /* PEx 引脚无上拉、下拉 */
    GPIOE->PUPDR   = 0x00000000;

    /* 将 PFx 引脚连接到 FMC 复用功能 */
    GPIOF->AFR[0]  = 0xcccccccc;
    GPIOF->AFR[1]  = 0xcccccccc;
    /* 在复用功能模式下配置 PFx 引脚 */
    GPIOF->MODER   = 0xAA800AAA;
    /* 将 PEx 引脚速度配置为 50 MHz */
    GPIOF->OSPEEDR = 0xAA800AAA;
    /* 配置 PFx 引脚输出类型为推拉 */
    GPIOF->OTYPER  = 0x00000000;
    /* PFx 引脚无上拉、下拉 */
    GPIOF->PUPDR   = 0x00000000;

    /* 将 PGx 引脚连接到 FMC 复用功能 */
    GPIOG->AFR[0]  = 0xcccccccc;
    GPIOG->AFR[1]  = 0xcccccccc;
    /* 在复用功能模式下配置 PGx 引脚 */
    GPIOG->MODER   = 0xaaaaaaaa;
    /* 将 PGx 引脚速度配置为 50 MHz */
    GPIOG->OSPEEDR = 0xaaaaaaaa;
    /* 配置 PGx 引脚输出类型为推拉 */
    GPIOG->OTYPER  = 0x00000000;
    /* PGx 引脚无上拉、下拉 */
    GPIOG->PUPDR   = 0x00000000;

    /* 将 PHx 引脚连接到 FMC 复用功能 */
    GPIOH->AFR[0]  = 0x00C0CC00;
    GPIOH->AFR[1]  = 0xCCCCCCCC;
    /* 在复用功能模式下配置 PHx 引脚 */
    GPIOH->MODER   = 0xAAAA08A0;
    /* 将 PHx 引脚速度配置为 50 MHz */
    GPIOH->OSPEEDR = 0xAAAA08A0;
    /* 配置 PHx 引脚输出类型为推拉 */
    GPIOH->OTYPER  = 0x00000000;
    /* PHx 引脚无上拉、下拉 */
    GPIOH->PUPDR   = 0x00000000;

    /* 将 PIx 引脚连接到 FMC 复用功能 */
    GPIOI->AFR[0]  = 0xCCCCCCCC;
    GPIOI->AFR[1]  = 0x00000CC0;
    /* 在复用功能模式下配置 PIx 引脚 */
    GPIOI->MODER   = 0x0028AAAA;
    /* 将 PIx 引脚速度配置为 50 MHz */
    GPIOI->OSPEEDR = 0x0028AAAA;
    /* 配置 PIx 引脚输出类型为推拉 */
    GPIOI->OTYPER  = 0x00000000;
    /* PIx 引脚无上拉、下拉 */
    GPIOI->PUPDR   = 0x00000000;

    /*-- FMC 定义 ------------------------------------------------------*/
    /* 启用 FMC 接口时钟 */
    RCC->AHB3ENR |= 0x00000001;

    /* Configure and enable SDRAM bank1 */
    FMC_Bank5_6->SDCR[0] = 0x000039D0;
    FMC_Bank5_6->SDTR[0] = 0x01115351;

    /* SDRAM 初始化序列 */
    /* 时钟启用命令 */
    FMC_Bank5_6->SDCMR = 0x00000011;
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    while((tmpreg != 0) & (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    }

    /* Delay */
    for (index = 0; index<1000; index++);

    /* PALL command */
    FMC_Bank5_6->SDCMR = 0x00000012;
    timeout = 0xFFFF;
    while((tmpreg != 0) & (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    }

    /*自动刷新命令 */
    FMC_Bank5_6->SDCMR = 0x00000073;
    timeout = 0xFFFF;
    while((tmpreg != 0) & (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    }

    /* MRD 寄存器程序 */
    FMC_Bank5_6->SDCMR = 0x00046014;
    timeout = 0xFFFF;
    while((tmpreg != 0) & (timeout-- > 0)) {
        tmpreg = FMC_Bank5_6->SDSR & 0x00000020;
    }

    /* 设置刷新计数 */
    tmpreg = FMC_Bank5_6->SDRTR;
    FMC_Bank5_6->SDRTR = (tmpreg | (0x0000027C<<1));

    /* 禁用写保护 */
    tmpreg = FMC_Bank5_6->SDCR[0];
    FMC_Bank5_6->SDCR[0] = (tmpreg & 0xFFFFFDFF);

    /*
      Bank1_SDRAM is configured as follow:

      FMC_SDRAMTimingInitStructure.FMC_LoadToActiveDelay = 2;
      FMC_SDRAMTimingInitStructure.FMC_ExitSelfRefreshDelay = 6;
      FMC_SDRAMTimingInitStructure.FMC_SelfRefreshTime = 4;
      FMC_SDRAMTimingInitStructure.FMC_RowCycleDelay = 6;
      FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime = 2;
      FMC_SDRAMTimingInitStructure.FMC_RPDelay = 2;
      FMC_SDRAMTimingInitStructure.FMC_RCDDelay = 2;

      FMC_SDRAMInitStructure.FMC_Bank = SDRAM_BANK;
      FMC_SDRAMInitStructure.FMC_ColumnBitsNumber = FMC_ColumnBits_Number_8b;
      FMC_SDRAMInitStructure.FMC_RowBitsNumber = FMC_RowBits_Number_11b;
      FMC_SDRAMInitStructure.FMC_SDMemoryDataWidth = FMC_SDMemory_Width_16b;
      FMC_SDRAMInitStructure.FMC_InternalBankNumber = FMC_InternalBank_Number_4;
      FMC_SDRAMInitStructure.FMC_CASLatency = FMC_CAS_Latency_3;
      FMC_SDRAMInitStructure.FMC_WriteProtection = FMC_Write_Protection_Disable;
      FMC_SDRAMInitStructure.FMC_SDClockPeriod = FMC_SDClock_Period_2;
      FMC_SDRAMInitStructure.FMC_ReadBurst = FMC_Read_Burst_disable;
      FMC_SDRAMInitStructure.FMC_ReadPipeDelay = FMC_ReadPipe_Delay_1;
      FMC_SDRAMInitStructure.FMC_SDRAMTimingStruct = &FMC_SDRAMTimingInitStructure;
    */

}
#endif /* DATA_IN_ExtSDRAM && DATA_IN_ExtSRAM */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
