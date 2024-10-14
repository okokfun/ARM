/**
  ******************************************************************************
  * 文件:    stm32f4xx_pwr.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，以管理电源控制器(PWR)外设设备的以下功能:
  *           + 备份域访问
  *           + PVD配置
  *           + 唤醒引脚配置
  *           + 主调节器和备用调节器配置
  *           + FLASH 掉电配置
  *           + 低功率模式配置
  *           + Flags management
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
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup PWR
  * 简介: PWR驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* --------- PWR在别名区域中注册位地址 ---------- */
#define PWR_OFFSET               (PWR_BASE - PERIPH_BASE)

/* --- CR Register ---*/

/* Alias word address of DBP 位 */
#define CR_OFFSET                (PWR_OFFSET + 0x00)
#define DBP_BitNumber            0x08
#define CR_DBP_BB                (PERIPH_BB_BASE + (CR_OFFSET * 32) + (DBP_BitNumber * 4))

/* Alias word address of PVDE 位 */
#define PVDE_BitNumber           0x04
#define CR_PVDE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PVDE_BitNumber * 4))

/* Alias word address of FPDS 位 */
#define FPDS_BitNumber           0x09
#define CR_FPDS_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (FPDS_BitNumber * 4))

/* Alias word address of PMODE 位 */
#define PMODE_BitNumber           0x0E
#define CR_PMODE_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (PMODE_BitNumber * 4))

/* ODEN 的别名字地址位 */
#define ODEN_BitNumber           0x10
#define CR_ODEN_BB               (PERIPH_BB_BASE + (CR_OFFSET * 32) + (ODEN_BitNumber * 4))

/* Alias word address of ODSWEN 位 */
#define ODSWEN_BitNumber         0x11
#define CR_ODSWEN_BB             (PERIPH_BB_BASE + (CR_OFFSET * 32) + (ODSWEN_BitNumber * 4))

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx)
    /* Alias word address of MRUDS 位 */
    #define MRUDS_BitNumber         0x0B
    #define CR_MRUDS_BB             (PERIPH_BB_BASE + (CR_OFFSET * 32) + (MRUDS_BitNumber * 4))

    /* Alias word address of LPUDS 位 */
    #define LPUDS_BitNumber         0x0A
    #define CR_LPUDS_BB             (PERIPH_BB_BASE + (CR_OFFSET * 32) + (LPUDS_BitNumber * 4))
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F446xx */

#if defined(STM32F401xx) || defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F412xG) || defined(STM32F413_423xx)
    /* Alias word address of MRLVDS 位 */
    #define MRLVDS_BitNumber         0x0B
    #define CR_MRLVDS_BB             (PERIPH_BB_BASE + (CR_OFFSET * 32) + (MRLVDS_BitNumber * 4))

    /* Alias word address of LPLVDS 位 */
    #define LPLVDS_BitNumber         0x0A
    #define CR_LPLVDS_BB             (PERIPH_BB_BASE + (CR_OFFSET * 32) + (LPLVDS_BitNumber * 4))
#endif /* STM32F401xx || STM32F410xx || STM32F411xE || STM32F412xG || STM32F413_423xx */

/* --- CSR Register ---*/
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F469_479xx)
    /* Alias word address of EWUP 位 */
    #define CSR_OFFSET               (PWR_OFFSET + 0x04)
    #define EWUP_BitNumber           0x08
    #define CSR_EWUP_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP_BitNumber * 4))
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F469_479xx */

#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
    /* Alias word address of EWUP2 位 */
    #define CSR_OFFSET               (PWR_OFFSET + 0x04)
    #define EWUP1_BitNumber           0x08
    #define CSR_EWUP1_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP1_BitNumber * 4))
    #define EWUP2_BitNumber           0x07
    #define CSR_EWUP2_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP2_BitNumber * 4))
    #if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx)
        #define EWUP3_BitNumber           0x06
        #define CSR_EWUP3_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (EWUP2_BitNumber * 4))
    #endif /* STM32F410xx || STM32F412xG || STM32F413_423xx */
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx */

/* Alias word address of BRE 位 */
#define BRE_BitNumber            0x09
#define CSR_BRE_BB              (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (BRE_BitNumber * 4))

/* ------------------ PWR 寄存器位掩码 ------------------------ */

/* CR 寄存器位掩码 */
#define CR_DS_MASK               ((uint32_t)0xFFFFF3FC)
#define CR_PLS_MASK              ((uint32_t)0xFFFFFF1F)
#define CR_VOS_MASK              ((uint32_t)0xFFFF3FFF)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions
  */

/** @defgroup PWR_Group1 备份域访问函数
  *  简介   备份域访问函数
  *
@verbatim
 ===============================================================================
                  ##### 备份域访问函数 #####
 ===============================================================================
    [..]
      复位后，备份域(RTC 寄存器、RTC 备份数据寄存器和备份 SRAM)被保护起来，
        以免发生意外。寄存器和备份 SRAM)被保护起来，防止可能的不需要的 写访问。
      启用对 RTC 域和 RTC 寄存器的访问，步骤如下:
        (+) 使用 RCC_APB1PeriphClockCmd() 函数启用电源控制器(PWR)APB1接口时钟。
        (+) 使用 PWR_BackupAccessCmd() 函数启用对 RTC 域的访问。

@endverbatim
  */

/**
  * 简介:  将压水堆外设寄存器去初始化为其默认复位值。
  * 参数:  无
  * 返回值: 无
  */
void PWR_DeInit(void) {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

/**
  * 简介:  启用或禁用对备份域(RTC 寄存器、RTC 备份数据寄存器和备份 SRAM)的访问。
  * 注意:   如果HSE除以2、3、...31被用作 RTC时钟，那么 备份域访问应保持启用。
  * 参数:  NewState: 访问备份域的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_BackupAccessCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    *(__IO uint32_t *) CR_DBP_BB = (uint32_t)NewState;
}


/** @defgroup PWR_Group2 PVD配置功能
  *  简介   PVD配置功能
  *
@verbatim
 ===============================================================================
                    ##### PVD配置功能 #####
 ===============================================================================
    [..]
      (+) PVD用于监测VDD 电源，将其与PVD 电平(PWR_CR中的PLS[2:0]位)选择的阈值进行比较。
      (+) 一个PVDO 标志可用于指示VDD/VDDA是高于还是低于 高于或低于PVD阈值。
          该事件内部连接到EXTI 线16，如果通过EXTI寄存器启用，可以产生一个中断。
      (+) PVD停止在待机模式。

@endverbatim
  */

/**
  * 简介:  配置电源电压检测器(PVD) 检测到的电压阈值。
  * 参数:  PWR_PVDLevel: 指定PVD检测水平
  *          此参数可以是以下值之一:
  *            @arg PWR_PVDLevel_0
  *            @arg PWR_PVDLevel_1
  *            @arg PWR_PVDLevel_2
  *            @arg PWR_PVDLevel_3
  *            @arg PWR_PVDLevel_4
  *            @arg PWR_PVDLevel_5
  *            @arg PWR_PVDLevel_6
  *            @arg PWR_PVDLevel_7
  * 注意:   关于每个检测级别对应的电压阈值的更多细节，
  *         请参考您的器件数据手册的电气特性。检测水平对应的电压阈值。
  * 返回值: 无
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));

    tmpreg = PWR->CR;

    /* 清除 PLS[7:5] 位 */
    tmpreg &= CR_PLS_MASK;

    /* 根据PWR_PVDLevel值，设置PLS[7:5]位。 */
    tmpreg |= PWR_PVDLevel;

    /* 存储新值 */
    PWR->CR = tmpreg;
}

/**
  * 简介:  启用或禁用电源电压检测器 (PVD)。
  * 参数:  NewState: PVD 的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_PVDCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    *(__IO uint32_t *) CR_PVDE_BB = (uint32_t)NewState;
}


/** @defgroup PWR_Group3 唤醒引脚配置功能
  *  简介   唤醒引脚配置功能
  *
@verbatim
 ===============================================================================
                 ##### 唤醒引脚配置功能 #####
 ===============================================================================
    [..]
      (+) WakeUp引脚用于将系统从待机模式唤醒。该引脚被强制配置为输入下拉，
          并在上升沿时处于激活状态。强制输入下拉配置，并且在上升沿上是有效的。
      (+) 有一个唤醒引脚。PA.00上的唤醒针脚1。
	   (++) 对于 STM32F446xx，有两个唤醒引脚。PA.00的引脚1和PC.13的引脚2
           (++) 对于 STM32F410xx/STM32F412xG/STM32F413_423xx，有三个唤醒引脚。PA.00上的Pin1、PC.00上的Pin2 和PC.01上的Pin3
@endverbatim
  */
#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE)
/**
  * 简介:  启用或禁用唤醒引脚功能。
  * 参数:  NewState: 唤醒引脚功能的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_WakeUpPinCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    *(__IO uint32_t *) CSR_EWUP_BB = (uint32_t)NewState;
}
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE */

#if defined(STM32F410xx) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
/**
  * 简介:  启用或禁用唤醒引脚功能。
  * 参数:  PWR_WakeUpPinx: 指定唤醒引脚。
  *          此参数可以是以下值之一:
  *            @arg PWR_WakeUp_Pin1: WKUP1 引脚用于从待机模式唤醒。
  *            @arg PWR_WakeUp_Pin2: WKUP2 引脚用于从待机模式唤醒。
  *            @arg PWR_WakeUp_Pin3: WKUP3引脚用于从待机模式唤醒。(仅适用于 STM32F410xx、STM32P412xG 和 STM32V413_423xx 设备)
  * 参数:  NewState: 唤醒引脚功能的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_WakeUpPinCmd(uint32_t PWR_WakeUpPinx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_PWR_WAKEUP_PIN(NewState));

    if(PWR_WakeUpPinx == PWR_WakeUp_Pin1) { /* PWR_WakeUp_Pin1 */
        *(__IO uint32_t *) CSR_EWUP1_BB = (uint32_t)NewState;
    }

    #if defined(STM32F410xx)|| defined(STM32F412xG) || defined(STM32F413_423xx)
    else if(PWR_WakeUpPinx == PWR_WakeUp_Pin3) { /* PWR_WakeUp_Pin3 */
        *(__IO uint32_t *) CSR_EWUP3_BB = (uint32_t)NewState;
    }

    #endif /* STM32F410xx */
    else { /* PWR_WakeUp_Pin2 */
        *(__IO uint32_t *) CSR_EWUP2_BB = (uint32_t)NewState;
    }
}
#endif /* STM32F410xx || STM32F412xG || STM32F413_423xx || STM32F446xx */


/** @defgroup PWR_Group4 主用和备用调节器配置功能
  *  简介   主用和备用调节器配置功能
  *
@verbatim
 ===============================================================================
          ##### 主用和备用调节器配置功能 #####
 ===============================================================================
    [..]
      (+) 备份域包括仅可从CPU访问的4K字节备份 SRAM，以及32位、16位或8位模式的地址。
          当启用低功率备用调节器时，即使在待机或VBAT模式下，其内容也会保留。当VBAT始终存在时，
          可将其视为内部EEPROM。您可以使用 PWR_BackupRegulatorCmd() 函数启用低功率备用稳压器，
          并使用 PWR_GetFlagStatus(PWR_FLAG_BRR) 检查其是否就绪。

      (+) 当备份域由 VDD(连接到VDD 的模拟开关)供电时，备份 SRAM由 VDD供电，
          VDD取代了VBAT 电源以节省电池寿命。

      (+) 备份 SRAM 不会被篡改事件大规模擦除。它受到读取保护，以防止机密数据(如加密私钥)
          被访问。当请求保护级别从1级更改为0级时，只能通过闪存接口擦除备份 SRAM。
      -@- 请参阅参考手册中的读取保护(RDP)说明。

      (+) 主内部调节器可以被配置为在设备不以最大频率操作时在性能和功耗之间进行权衡。
      (+) 对于 STM32F405xx/407xx 和 STM32F415xx/417xx 设备，
          可以通过PWR_MainRegulatorModelConfig() 函数动态配置调节器，
          该函数配置PWR_CR 寄存器中的VOS位:
        (++) 当设置此位时(选择调节器电压输出比例1模式)，系统频率可上升至168 MHz。
        (++) 当重置此位(选择调节器电压输出比例2模式)时，系统频率可达到144 MHz。

       (+) 对于 STM32F42xxx/43xxx 设备，可以通过PWR_MainRegulatorModeConfig()
           函数配置调节器，该函数配置PWR_CR 寄存器中的VOS[1:0]位:
           在 PWR_CR 寄存器中配置VOS[1:0]位:
        (++)当VOS[1:0]=11(选择调节器电压输出比例1模式)时，系统频率可上升至168 MHz。
        (++)当VOS[1:0]=10(选择调节器电压输出比例2模式)时，系统频率可上升至144 MHz。
        (++)当VOS[1:0]=01(选择调节器电压输出比例3模式)时，系统频率可升至120 MHz。

       (+) 对于 STM32F42xxx/43xxx 设备，只有当PLL关闭且HSI 或HSE时钟源被选为系统时钟时，
            才能修改刻度。
           编程的新值仅在 PLL接通时激活。
           当锁相环关闭时，电压标度3被自动选择。
        有关更多详细信息，请参阅数据表。

       (+) 对于 STM32F42xxx/43xxx 设备，在运行模式下:主调节器有两种可用的操作模式:
        (++) 正常模式:CPU和核心逻辑在给定电压标度下以最大频率运行(标度1、标度2 或标度3)
        (++) Over-drive mode: 该模式允许CPU和核心逻辑在给定电压缩放(缩放1、缩放2 或缩放3)
            下以高于正常模式的频率操作。此模式通过PWR_OverDriveCmd() 函数和PWR_OverDriveSWCmd() 函数启用，
            要进入或退出Overdrive模式，请遵循参考手册中描述的顺序。

       (+) For STM32F42xxx/43xxx Devices, in Stop mode: 主调节器或低功率调节器向1.2V
              域提供低功率电压，从而保留寄存器和内部 SRAM 的内容。有两种操作模式可供选择:
         (++) Normal mode: 1.2V域保持在标称泄漏模式下。
                           此模式仅在主调节器或低功率调节器用于比例3或低电压模式时可用。
         (++) Under-drive mode: 在减少泄漏模式下保留1.2V域。该模式仅在主稳压器或低功率稳压器处于低压模式时可用。
                                该模式通过PWR_UnderDriveCmd() 函数启用。

@endverbatim
  */

/**
  * 简介:  启用或禁用备份调节器。
  * 参数:  NewState: 备用调节器的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_BackupRegulatorCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    *(__IO uint32_t *) CSR_BRE_BB = (uint32_t)NewState;
}

/**
  * 简介:  配置主内部稳压器输出电压。
  * 参数:  PWR_Regulator_Voltage: 指定稳压器的输出电压，以便在器件不以最大频率
  *                               工作时实现性能和功耗之间的权衡(更多细节请参考数据手册)。
  *          此参数可以是以下值之一:
  *            @arg PWR_Regulator_Voltage_Scale1: 稳压器电压输出刻度1模式，系统频率高达168MHz。
  *            @arg PWR_Regulator_Voltage_Scale2: 稳压器电压输出刻度2模式，系统频率高达144MHz。
  *            @arg PWR_Regulator_Voltage_Scale3: 稳压器电压输出 Scale 3模式，
  *                                               系统频率高达120 MHz(仅适用于 STM32F42xxx/43xxx器件)。
  * 返回值: 无
  */
void PWR_MainRegulatorModeConfig(uint32_t PWR_Regulator_Voltage) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_PWR_REGULATOR_VOLTAGE(PWR_Regulator_Voltage));

    tmpreg = PWR->CR;

    /* 清除 VOS[15:14] 位 */
    tmpreg &= CR_VOS_MASK;

    /* 设置 VOS[15:14] bits 根据 PWR_Regulator_Voltage 值 */
    tmpreg |= PWR_Regulator_Voltage;

    /* 存储新值 */
    PWR->CR = tmpreg;
}

/**
  * 简介:  启用或禁用过载。
  *
  * 注意:   此函数只能用于 STM32F42xxx/STM3243xxx 设备。
  *
  * 这种模式允许CPU和核心逻辑在给定的电压比例(比例1、比例2 或比例3)下以高于正常模式的频率运行。
  *
  * 注意: 建议在应用程序不运行关键任务，并且系统时钟源为 HSI 或HSE时，进入或退出超速驱动模式。
  *       在超速驱动开关激活期间，不应启用任何外围时钟。
  *       一旦超速模式被激活，外围时钟必须被启用。
  *
  * 参数:  NewState: 超速模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_OverDriveCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Set/Reset the ODEN bit to enable/disable the Over Drive mode */
    *(__IO uint32_t *) CR_ODEN_BB = (uint32_t)NewState;
}

/**
  * 简介:  启用或禁用过驱切换。
  *
  * 注意:   此函数只能用于 STM32F42xxx/STM3243xxx 设备。
  *
  * 参数:  NewState: 超速档切换模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_OverDriveSWCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 设置/重置ODSWEN 位以启用/禁用超速档切换模式 */
    *(__IO uint32_t *) CR_ODSWEN_BB = (uint32_t)NewState;
}

/**
  * 简介:    启用或禁用欠驱动模式。
  *
  * 注意:   此函数只能用于 STM32F42xxx/STM3243xxx 设备。
  * 注意:    此模式仅在 STOP低功率模式下启用。
  *          在这种模式下，1.2V域保持在减少泄漏模式下。
  *           此模式仅在主调节器或低功率调节器处于低压模式时可用
  *
  * 注意:   如果启用了欠驱动模式，则在退出停止模式后会自动禁用。
  *         当电压调节器在欠驱动模式下运行时，从停止模式唤醒时会产生额外的启动延迟。
  *
  * 参数:  NewState: 欠驱动模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_UnderDriveCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 UDEN[1:0] 位用于启用欠驱动模式 */
        PWR->CR |= (uint32_t)PWR_CR_UDEN;
    } else {
        /* 重设 UDEN[1:0]位用于禁用欠驱动模式 */
        PWR->CR &= (uint32_t)(~PWR_CR_UDEN);
    }
}

#if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx)
/**
  * 简介: 在驱动模式下启用或禁用主调节器。
  *
  * 注意:  此模式仅适用于 STM32F427_437xx/STM32F429_439xx/STM22F446xx 设备。
  *
  * 参数:  NewState: 主调节器欠驱动模式的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_MainRegulatorUnderDriveCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        *(__IO uint32_t *) CR_MRUDS_BB = (uint32_t)ENABLE;
    } else {
        *(__IO uint32_t *) CR_MRUDS_BB = (uint32_t)DISABLE;
    }
}

/**
  * 简介: 在驱动模式下启用或禁用低功率调节器。
  *
  * 注意:  此模式仅适用于 STM32F427_437xx/STM32F429_439xx/STM22F446xx 设备。
  *
  * 参数:  NewState: 低功率调节器在驱动模式下的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_LowRegulatorUnderDriveCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        *(__IO uint32_t *) CR_LPUDS_BB = (uint32_t)ENABLE;
    } else {
        *(__IO uint32_t *) CR_LPUDS_BB = (uint32_t)DISABLE;
    }
}
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F446xx */

#if defined(STM32F401xx) || defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F412xG) || defined(STM32F413_423xx)
/**
  * 简介: 启用或禁用主调节器低压模式。
  *
  * 注意:  此模式仅适用于 STM32F401xx/STM32F410xx/STM32.F411xx/STM3.2F412xG/STM32F2F413_423xx 设备。
  *
  * 参数:  NewState: 主调节器低压模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_MainRegulatorLowVoltageCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        *(__IO uint32_t *) CR_MRLVDS_BB = (uint32_t)ENABLE;
    } else {
        *(__IO uint32_t *) CR_MRLVDS_BB = (uint32_t)DISABLE;
    }
}

/**
  * 简介: 启用或禁用低功率稳压器的低电压模式。
  *
  * 注意:  该模式仅适用于 STM32F401xx/STM32F410xx/STM32F411xx/STM32F412xG/STM32F413_423xx器件。
  *
  * 参数:  NewState: 低功率调节器低电压模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_LowRegulatorLowVoltageCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        *(__IO uint32_t *) CR_LPLVDS_BB = (uint32_t)ENABLE;
    } else {
        *(__IO uint32_t *) CR_LPLVDS_BB = (uint32_t)DISABLE;
    }
}
#endif /* STM32F401xx || STM32F410xx || STM32F411xE || STM32F412xG || STM32F413_423xx */


/** @defgroup PWR_Group5 FLASH掉电配置功能
  *  简介   FLASH掉电配置功能
  *
@verbatim
 ===============================================================================
             ##### FLASH掉电配置功能 #####
 ===============================================================================
    [..]
      (+) 通过使用 PWR_FlashPowerDownCmd() 函数设置PWR_CR 寄存器中的 FPDS位，
          当器件进入Stop模式时，闪存也进入了掉电模式。当闪存处于掉电模式时，
          当从停止模式唤醒时，会产生额外的启动延迟。
@endverbatim
  */

/**
  * 简介:  启用或禁用 STOP模式下的 Flash断电函数。
  * 参数:  NewState: 闪存功率模式的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void PWR_FlashPowerDownCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    *(__IO uint32_t *) CR_FPDS_BB = (uint32_t)NewState;
}


/** @defgroup PWR_Group6 低功率模式配置功能
  *  简介   低功率模式配置功能
  *
@verbatim
 ===============================================================================
              ##### 低功率模式配置功能 #####
 ===============================================================================
    [..]
      这些设备具有3种低功耗模式:
      (+)睡眠模式:Cortex-M4核心停止，外设设备继续运行。
      (+)停止模式:所有时钟停止，调节器运行，调节器处于低功率模式
      (+)待机模式:1.2V域断电。

   *** 睡眠模式 ***
   ==================
    [..]
      (+) 进入:
        (++) 使用__WFI()或__WFE() 函数进入睡眠模式。
      (+) 退出:
        (++) 嵌套向量中断控制器(NVIC)确认的任何外围中断都可以将设备从睡眠模式唤醒。

   *** 停止模式 ***
   =================
    [..]
      在停止模式下，1.2V域中的所有时钟停止，PLL、HSI和HSE RC振荡器被禁用。保留内部 SRAM 和寄存器内容。
        电压调节器可以配置为正常模式或低功率模式。
      为了最小化停止模式下的消耗，可以在进入停止模式之前关闭闪存。
        在使用 PWR_FlashPowerDownCmd() 函数退出停止模式后，可以通过软件再次打开。

      (+) 进入:
        (++) 使用 PWR_EnterSTOPMode(PWR_MainRegulator_ON) 功能进入停止模式:
          (+++) 主调节器打开。
          (+++) 低功率调节器打开。
      (+) 退出:
        (++) 在中断/事件模式下配置的任何EXTI线路(内部或外部)。

   *** 待机模式 ***
   ====================
    [..]
      待机模式允许实现最低功耗。它基于Cortex-M4深度睡眠模式，电压调节器被禁用。
      因此，1.2V域断电。PLL、HSI振荡器和HSE振荡器也关闭。
        SRAM 和寄存器内容丢失，RTC 寄存器、RTC 备份寄存器、备份 SRAM 和备用电路除外。

      电压调节器关闭。

      (+) 进入:
        (++) 使用 PWR_EnterSTANDBYMode() 函数进入待机模式。
      (+) 退出:
        (++) WKUP引脚上升沿、RTC警报(警报A 和警报B)、
          RTC唤醒、篡改事件、时间戳事件、NRST 引脚外部复位、IWDG复位。

   *** 从低功耗模式自动唤醒(AWU) ***
   =============================================
    [..]
      MCU可以通过RTC报警事件、RTC唤醒事件、篡改事件、时间戳事件或比较器事件从
        低功耗模式中被唤醒。唤醒事件、篡改事件、时间戳事件或比较器事件。
        而不依赖外部中断(自动唤醒模式)。

      (#) RTC从停止模式自动唤醒(AWU)

        (++) 要想在RTC报警事件中从停止模式中唤醒，就必须:
          (++) 使用EXTI_Init() 函数将EXTI 17号线配置为对上升沿敏感(中断或事件模式)。
          (++) 使用 RTC_ITConfig() 函数启用 RTC报警中断。
          (++) 使用 RTC_SetAlarm()和 RTC_AlarmCmd() 函数配置 RTC以产生RTC报警。
        (++) 要想在RTC 篡改或时间戳事件中从停止模式中唤醒，就必须:
          (++) 使用EXTI_Init() 函数将EXTI 21号线配置为对上升沿敏感(中断或事件模式)。
          (++) 使用 RTC_ITConfig() 函数启用 RTC 篡改或时间戳中断。
          (++) 使用 RTC_TimeStampConfig(), RTC_TamperTriggerConfig()
              和 RTC_TamperCmd() 函数配置 RTC以检测篡改或时间戳事件。
        (++) 为了用 RTC唤醒事件从停止模式中唤醒，有必要:
           (++) 使用EXTI_Init() 函数将EXTI 22号线配置为对上升沿敏感(中断或事件模式)。
           (++) 使用 RTC_ITConfig() 函数启用 RTC唤醒中断。
           (++) 使用 RTC_WakeUpClockConfig()、RTC_SetWakeUpCounter()
              和 RTC_WakeUpCmd() 函数配置 RTC以产生RTC WakeUp事件。

      (#) RTC从待机模式自动唤醒(AWU)

        (++) 要从待机模式下用 RTC报警事件唤醒，必须:
          (+++) 使用 RTC_ITConfig() 函数启用 RTC报警中断
          (+++) 使用 RTC_SetAlarm()和 RTC_AlarmCmd() 函数配置 RTC以产生RTC报警。
        (++) 要从待机模式中唤醒RTC 篡改或时间戳事件，就必须:
          (+++) 使用 RTC_ITConfig() 函数启用 RTC 篡改或时间戳中断
          (+++) 使用 RTC_TimeStampConfig(), RTC_TamperTriggerConfig()
                和 RTC_TamperCmd() 函数配置 RTC以检测篡改或时间戳事件。
        (++) 要想用 RTC唤醒事件从待机模式中唤醒，就必须:
          (+++) 使用 RTC_ITConfig() 函数启用 RTC WakeUp中断。
          (+++) 使用 RTC_WakeUpClockConfig(), RTC_SetWakeUpCounter()
             和 RTC_WakeUpCmd() 函数配置 RTC以产生RTC WakeUp事件。

@endverbatim
  */

/**
  * 简介:  进入停止模式。
  *
  * 注意:   在停止模式下，所有的 I/O 引脚保持与运行模式下相同的状态。
  * 注意:   当通过发出中断或唤醒事件退出停止模式时，HSI RC振荡器被选为系统时钟。
  * 注意:   当电压调节器在低功率模式下工作时，从停止模式唤醒时会产生额外的启动延迟。
  *         在 "停止 "模式下保持内部调节器开启，虽然启动时间缩短，但消耗量会更大。
  *
  * 参数:  PWR_Regulator: 指定调节器在 STOP模式下的状态。
  *          此参数可以是以下值之一:
  *            @arg PWR_MainRegulator_ON: 调节器开启时的停止模式
  *            @arg PWR_LowPowerRegulator_ON: STOP模式，低功率调节器开启
  * 参数:  PWR_STOPEntry: 指定是否通过WFI 或WFE指令进入STOP模式。
  *          此参数可以是以下值之一:
  *            @arg PWR_STOPEntry_WFI: 用 WFI指令进入STOP模式
  *            @arg PWR_STOPEntry_WFE: 用 WFE指令进入STOP模式
  * 返回值: 无
  */
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_PWR_REGULATOR(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    /* 在停止模式下选择调节器状态 ---------------------------------*/
    tmpreg = PWR->CR;
    /* 清除PDDS和 LPDS位 */
    tmpreg &= CR_DS_MASK;

    /* Set LPDS, MRLVDS and LPLVDS bits 根据 PWR_Regulator 值 */
    tmpreg |= PWR_Regulator;

    /* 存储新值 */
    PWR->CR = tmpreg;

    /* Set SLEEPDEEP bit of Cortex System Control 寄存器 */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* 选择停止模式输入 --------------------------------------------------*/
    if(PWR_STOPEntry == PWR_STOPEntry_WFI) {
        /* 请求等待中断 */
        __WFI();
    } else {
        /* 请求等待事件 */
        __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control 寄存器 */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/**
  * 简介:  进入驱动器不足停止模式。
  *
  * 注意:   此模式仅适用于 STM32F42xxx/STM3243xxx 设备。
  *
  * 注意:    只有当Under Drive(欠驱动)已激活时，才能选择此模式
  *
  * 注意:   在停止模式下，所有I/O 引脚保持与运行模式下相同的状态。
  * 注意:   当通过发出中断或唤醒事件退出停止模式时，HSI RC振荡器被选作系统时钟。
  * 注意:   当电压调节器在低功率模式下运行时，从停止模式唤醒时会产生额外的启动延迟。
  *         通过在停止模式下保持内部调节器打开，虽然启动时间缩短，但消耗量较高。
  *
  * 参数:  PWR_Regulator: 指定 STOP模式下的调节器状态。
  *          此参数可以是以下值之一:
  *            @arg PWR_MainRegulator_UnderDrive_ON:  当设备处于驱动模式下的停止时，
  *                                                    主调节器处于驱动模式，闪存处于断电状态
  *            @arg PWR_LowPowerRegulator_UnderDrive_ON:  低功率调节器处于驱动模式下，
  *                                                     当设备处于驱动模式停止时，闪存处于断电状态
  * 参数:  PWR_STOPEntry: 指定是否使用 WFI 或WFE指令进入STOP模式。
  *          此参数可以是以下值之一:
  *            @arg PWR_STOPEntry_WFI: 使用 WFI指令进入STOP模式
  *            @arg PWR_STOPEntry_WFE: 使用 WFE指令进入STOP模式
  * 返回值: 无
  */
void PWR_EnterUnderDriveSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_PWR_REGULATOR_UNDERDRIVE(PWR_Regulator));
    assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));

    /* 在停止模式下选择调节器状态 ---------------------------------*/
    tmpreg = PWR->CR;
    /* 清除PDDS和 LPDS位 */
    tmpreg &= CR_DS_MASK;

    /* 根据PWR_Regulator设置LPDS、MRLUDS和 LPLUDS位值 */
    tmpreg |= PWR_Regulator;

    /* 存储新值 */
    PWR->CR = tmpreg;

    /* Set SLEEPDEEP bit of Cortex System Control 寄存器 */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* 选择停止模式输入 --------------------------------------------------*/
    if(PWR_STOPEntry == PWR_STOPEntry_WFI) {
        /* 请求等待中断 */
        __WFI();
    } else {
        /* 请求等待事件 */
        __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control 寄存器 */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
}

/**
  * 简介:  进入待机模式。
  * 注意:   在待机模式下，所有的 I/O 引脚都是高阻抗的，除了:
  *          - 复位垫(仍然可用)
  *          - RTC_AF1 引脚(PC13)如果被配置为防拆、时间戳、RTC 警报输出，或 RTC时钟校准输出。
  *          - RTC_AF2 引脚(PI8)，如果配置为防拆或时间戳。
  *          - 如果启用，WKUP引脚1(PA0)。
  * 注意:   唤醒标志(WUF)在调用函数能之前，需要在应用层面被清除。
  * 参数:  无
  * 返回值: 无
  */
void PWR_EnterSTANDBYMode(void) {
    /* Select STANDBY mode */
    PWR->CR |= PWR_CR_PDDS;

    /* Set SLEEPDEEP bit of Cortex System Control 寄存器 */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* This option is used to ensure that store operations are completed */
    #if defined ( __CC_ARM   )
    __force_stores();
    #endif
    /* 请求等待中断 */
    __WFI();
}


/** @defgroup PWR_Group7  标志管理功能
  *  简介    标志管理功能
  *
@verbatim
 ===============================================================================
                    #####标志管理功能#####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  检查是否设置了指定的 PWR 标志。
  * 参数:  PWR_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg PWR_FLAG_WU: 唤醒标志. 该标志表示从WKUP引脚或 RTC告警(告警a或告警B)、
  *                              RTC Tamper事件、RTC TimeStamp事件或 RTC唤醒接收到唤醒事件。
  *                              当WKUP引脚级别已经很高时，如果启用了WKUP引脚(通过设置EWUP位)，
  *                              则检测到额外的唤醒事件。
  *            @arg PWR_FLAG_SB: 备用Flage。此标志表示系统已从待机模式恢复。
  *            @arg PWR_FLAG_PVDO: PVD Output. 仅当PWR_PVDCmd() 函数启用 PVD时，此标志才有效。PVD在待机模式下停止
                                   因此，该位在待机或重置后等于0，直到PVDE位被设置。
  *            @arg PWR_FLAG_BRR: 后备调节器就绪标志。
  *                               当设备从待机模式唤醒或被系统复位或电源复位时，该位不会被重置。
  *            @arg PWR_FLAG_VOSRDY: 该标志表示稳压器电压比例输出选择已准备就绪。
  *            @arg PWR_FLAG_ODRDY: 该标志表示超速模式已经准备就绪(STM32F42xxx/43xxx器件)。
  *            @arg PWR_FLAG_ODSWRDY: 该标志表示超速模式切换已准备就绪(STM32F42xxx/43xxx器件)。
  *            @arg PWR_FLAG_UDRDY: 该标志表示在停止模式下启用欠驱动模式(STM32F42xxx/43xxx器件)。
  * 返回值: PWR_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG) {
    FlagStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_PWR_GET_FLAG(PWR_FLAG));

    if ((PWR->CSR & PWR_FLAG) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    /* 返回标志状态 */
    return bitstatus;
}

/**
  * 简介:  清除 PWR 的挂起标志。
  * 参数:  PWR_FLAG: 指定要清除的标志。
  *          此参数可以是以下值之一:
  *            @arg PWR_FLAG_WU: 唤醒标志
  *            @arg PWR_FLAG_SB:  待机旗
  *            @arg PWR_FLAG_UDRDY: 驱动器就绪标志下(STM32F42xxx/43xxx 设备)
  * 返回值: 无
  */
void PWR_ClearFlag(uint32_t PWR_FLAG) {
    /* 检查参数 */
    assert_param(IS_PWR_CLEAR_FLAG(PWR_FLAG));

    #if defined (STM32F427_437xx) || defined (STM32F429_439xx)

    if (PWR_FLAG != PWR_FLAG_UDRDY) {
        PWR->CR |=  PWR_FLAG << 2;
    } else {
        PWR->CSR |= PWR_FLAG_UDRDY;
    }

    #endif /* STM32F427_437xx ||  STM32F429_439xx */

    #if defined (STM32F40_41xxx) || defined (STM32F401xx) || defined (STM32F410xx) || defined (STM32F411xE) || defined(STM32F412xG) || defined(STM32F413_423xx)
    PWR->CR |=  PWR_FLAG << 2;
    #endif /* STM32F40_41xxx  || STM32F401xx || STM32F410xx || STM32F411xE || STM32F412xG || STM32F413_423xx */
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
