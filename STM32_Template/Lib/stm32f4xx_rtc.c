/**
  ******************************************************************************
  * 文件:    stm32f4xx_rtc.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，以管理实时时钟(RTC)外设设备的以下功能:
  *           + 初始化
  *           + 日历(时间和日期)配置
  *           + 警报(警报A和警报B)配置
  *           + 唤醒定时器配置
  *           + 夏令时配置
  *           + 输出引脚配置
  *           + 粗数字校准配置
  *           + 平滑数字校准配置
  *           + 时间戳配置
  *           + 篡改配置
  *           + 备份数据寄存器配置
  *           + 换档控制同步
  *           + RTC篡改和时间戳引脚选择和输出类型配置
  *           + 中断和标志管理
  *
@verbatim

 ===================================================================
              ##### 备份域操作条件 #####
 ===================================================================
 [..] 当主VDD电源关闭时，实时时钟(RTC)、RTC备份寄存器和备份SRAM(BKP SRAM)
        可以通过VBAT电压供电。
      为了保留RTC备份寄存器的内容，备份SRAM，并在VDD关闭时为RTC供电，
        VBAT引脚可以连接到电池或其他电源提供的可选备用电压。

 [..] 为了使RTC即使在主数字电源(VDD)关闭时也能运行，VBAT引脚为以下模块供电:
        (#) RTC
        (#) LSE振荡器
        (#) 启用低功率备用调节器时的备用SRAM
        (#) PC13到PC15 I/O，加上PI8 I/O(如果可用)

 [..] 当备份域由VDD(连接到VDD的模拟交换机)提供时，以下功能可用:
        (#) PC14和PC15可用作GPIO或LSE引脚
        (#) PC13可用作GPIO或RTC_AF1引脚
        (#) PI8可用作GPIO或RTC_AF2引脚

 [..] 当备份域由VBAT(由于VDD不存在而连接到VBAT的模拟交换机)提供时，以下功能可用:
        (#) PC14和PC15只能用作LSE引脚
        (#) PC13可用作RTC_AF1引脚
        (#) PI8可用作RTC_AF2引脚


                   ##### 备份域重置 #####
 ===================================================================
 [..] 备份域重置将所有RTC寄存器和寄存器设置为其重置值。BKPSRAM不受此复位的影响。
        重置BKPSRAM的唯一方法是通过Flash接口请求保护级别从1更改为0。
 [..] 发生以下事件之一时，将生成备份域重置:
   (#) 软件重置，通过设置RCC备份域控制寄存器(RCC_BDCR)中的BDRST位触发。
        您可以使用RCC_BackupResetCmd()。
   (#) VDD或VBAT电源打开(如果两个电源之前都已关闭)。


                   ##### 备份域访问 #####
 ===================================================================
 [..] 重置后，备份域(RTC寄存器、RTC备份数据寄存器和备份SRAM)
        将受到保护，以防可能出现不需要的写入访问。
 [..] 要启用对 RTC 域和 RTC 寄存器的访问，请执行以下操作:
    (+) 启用电源控制器 (PWR)APB1 接口使用 RCC_APB1PeriphClockCmd() 函数。
    (+) 使用 PWR_BackupAccessCmd()  函数启用对RTC域的访问。
    (+) 使用 RCC_RTCCLKConfig() 函数选择RTC时钟源。
    (+) 使用 RCC_RTCCLKCmd()  函数启用RTC时钟。


                  ##### 如何使用RTC驱动程序 #####
 ===================================================================
 [..]
   (+) 启用 RTC域访问(请参阅上一节中的描述)
   (+) 使用 RTC_Init() 函数配置 RTC 预分频器(异步和同步)和RTC小时格式。

 *** 时间和日期配置 ***
 ===================================
 [..]
   (+) 要配置 RTC 日历(时间和日期)，请使用 RTC_SetTime()
   (+) 要读取 RTC 日历，请使用 RTC_GetTime() 和 RTC_GetDate() 函数。
   (+) 使用 RTC_DayLightSavingConfig() 函数向 RTC 日历添加或减少一小时。

 *** 报警配置 ***
 ===========================
 [..]
    (+) 要配置 RTC 报警，请使用 RTC_SetAlarm() 函数。
    (+) 使用 RTC_AlarmCmd() 函数启用选定的 RTC 报警
    (+) 要读取 RTC 警报，请使用 RTC_GetAlarm() 函数。
    (+) 要读取 RTC 报警 SubSecond，请使用 RTC_GetAlarmSubSecnd() 函数。

 *** RTC唤醒配置 ***
 ================================
 [..]
    (+) 使用 RTC_WakeUpClockConfig() 函数配置 RTC 唤醒时钟源。
    (+) 使用 RTC_SetWakeUpCounter() 函数配置 RTC 唤醒计数器
    (+) 使用 RTC_WakeUpCmd()函数启用 RTC 唤醒
    (+) 要读取 RTC 唤醒计数器寄存器，请使用 RTC_GetWakeUpCounter() 函数。

 *** 输出配置 ***
 =============================
 [..] RTC有两种不同的输出:
   (+) AFO_ALARM: 该输出用于管理RTC警报A、警报B和WaKeUp信号。
                  要在RTC_AF1引脚上输出选定的RTC信号，请使用RTC_OutputConfig()函数。
   (+) AFO_CALIB: 该输出为512Hz信号或1Hz。
                  要在RTC_AF1引脚上输出RTC时钟，请使用RTC_CalibOutputCmd()函数。

 *** 平滑数字校准配置 ***
 ================================================
 [..]
   (+) 使用RTC_SmoothCalibConfig()函数
        配置RTC原始数字校准值和相应的校准周期周期(32秒、16秒和8秒)。

 *** 粗略数字校准配置 ***
 ================================================
 [..]
    (+) 使用RTC_CoarseCalibConfig()函数配置RTC粗略校准值和相应符号。
    (+) 使用RTC_CoarseCalibCmd()函数启用RTC粗校准

 *** 时间戳配置 ***
 ===============================
 [..]
   (+) 配置RTC_AF1触发器，并使用RTC_TimeStampCmd()函数启用RTC时间戳。
   (+) 要读取RTC时间戳时间和日期寄存器，请使用RTC_GetTimeStamp()函数。
   (+) 要读取RTC TimeStamp SubSecond寄存器，请使用RTC_GetTimeStampSubSecond()函数。
   (+) 根据RTC_TAFCR寄存器中TAMP1INSEL位的值，TAMPER1替代函数可以映射到RTC_AF1(PC13)
       或RTC_AF2(PI8)。您可以使用RTC_TamperPinSelection()函数选择相应的管脚。

 *** 篡改配置 ***
 ============================
 [..]
    (+) 使用 RTC_TamperCmd() 函数启用RTC篡改。
    (+) 使用 RTC_TamperFilterConfig() 函数配置篡改过滤器计数。
    (+) 使用 RTC_TamperConfig() 函数，根据 Tamper 过滤器(如果等于0 Edge else Level)
		    值配置 RTC Tamper 触发器Edge或Level。
    (+) 使用 RTC_TamperSamplingFreqConfig() 函数配置篡改采样频率。
    (+) 使用 RTC_TamperPinsPrechargeDuration() 函数配置篡改预充电或放电持续时间。
    (+) 使用 RTC_TamperPullUpDisableCmd() 函数启用 Tamper Pull-UP。
    (+) 使用 TC_TSOnTamperDetecCmd() 函数启用篡改检测事件的时间戳。
    (+) 根据 RTC_TAFCR 寄存器中 TSINSEL位 的值，TIMESTAMP 替代函数可以映射到
       RTC_AF1 或 RTC_AF2。您可以使用 RTC_TimeStampPinSelection() 函数选择相应的管脚。

 *** 备份数据寄存器配置 ***
 ===========================================
 [..]
    (+) 要写入 RTC 备份数据寄存器，请使用 RTC_WriteBackupRegister() 函数。
    (+) 要读取 RTC 备份数据寄存器，请使用 RTC_ReadBackupRegister() 函数。


                  ##### RTC和低功耗模式 #####
 ===================================================================
 [..] MCU 可以通过RTC 替代功能从低功耗模式唤醒。
 [..] RTC 替代功能包括 RTC 警报(警报A和警报B)、RTC 唤醒、RTC 篡改事件检测和 RTC 时间戳事件检测。
      这些 RTC 复用功能可将系统从停止和备用低功率模式唤醒。
 [..] 通过使用 RTC 警报或 RTC 唤醒事件，系统也可以从低功耗模式中唤醒，
      而不依赖于外部中断(自动唤醒模式)。
 [..] RTC 提供了一个可编程的时基，用于定期从停止或待机模式中唤醒。
      只有当 RTC 时钟源为 LSE 或 LSI 时，才能从 STOP 和 Standby 模式唤醒。


          ##### RTC_AF1复用功能的选择 #####
 ===================================================================
 [..] RTC_AF1引脚(PC13)可用于以下目的:
   (+) AFO_ALARM output
   (+) AFO_CALIB output
   (+) AFI_TAMPER
   (+) AFI_TIMESTAMP

 [..]
   +-------------------------------------------------------------------------------------------------------------+
   |     Pin         |AFO_ALARM |AFO_CALIB |AFI_TAMPER |AFI_TIMESTAMP | TAMP1INSEL |   TSINSEL    |ALARMOUTTYPE  |
   |  configuration  | ENABLED  | ENABLED  |  ENABLED  |   ENABLED    |TAMPER1 pin |TIMESTAMP pin |  AFO_ALARM   |
   |  and function   |          |          |           |              | selection  |  selection   |Configuration |
   |-----------------|----------|----------|-----------|--------------|------------|--------------|--------------|
   |   Alarm out     |          |          |           |              |    Don't   |     Don't    |              |
   |   output OD     |     1    |Don't care|Don't care | Don't care   |    care    |     care     |      0       |
   |-----------------|----------|----------|-----------|--------------|------------|--------------|--------------|
   |   Alarm out     |          |          |           |              |    Don't   |     Don't    |              |
   |   output PP     |     1    |Don't care|Don't care | Don't care   |    care    |     care     |      1       |
   |-----------------|----------|----------|-----------|--------------|------------|--------------|--------------|
   | Calibration out |          |          |           |              |    Don't   |     Don't    |              |
   |   output PP     |     0    |    1     |Don't care | Don't care   |    care    |     care     |  Don't care  |
   |-----------------|----------|----------|-----------|--------------|------------|--------------|--------------|
   |  TAMPER input   |          |          |           |              |            |     Don't    |              |
   |   floating      |     0    |    0     |     1     |      0       |      0     |     care     |  Don't care  |
   |-----------------|----------|----------|-----------|--------------|------------|--------------|--------------|
   |  TIMESTAMP and  |          |          |           |              |            |              |              |
   |  TAMPER input   |     0    |    0     |     1     |      1       |      0     |      0       |  Don't care  |
   |   floating      |          |          |           |              |            |              |              |
   |-----------------|----------|----------|-----------|--------------|------------|--------------|--------------|
   | TIMESTAMP input |          |          |           |              |    Don't   |              |              |
   |    floating     |     0    |    0     |     0     |      1       |    care    |      0       |  Don't care  |
   |-----------------|----------|----------|-----------|--------------|------------|--------------|--------------|
   |  Standard GPIO  |     0    |    0     |     0     |      0       | Don't care |  Don't care  |  Don't care  |
   +-------------------------------------------------------------------------------------------------------------+


        #####  RTC_AF2复用功能的选择 #####
 ===================================================================
 [..] RTC_AF2引脚(PI8)可用于以下目的:
   (+) AFI_TAMPER
   (+) AFI_TIMESTAMP
 [..]
   +---------------------------------------------------------------------------------------+
   |     Pin         |AFI_TAMPER |AFI_TIMESTAMP | TAMP1INSEL |   TSINSEL    |ALARMOUTTYPE  |
   |  configuration  |  ENABLED  |   ENABLED    |TAMPER1 pin |TIMESTAMP pin |  AFO_ALARM   |
   |  and function   |           |              | selection  |  selection   |Configuration |
   |-----------------|-----------|--------------|------------|--------------|--------------|
   |  TAMPER input   |           |              |            |     Don't    |              |
   |   floating      |     1     |      0       |      1     |     care     |  Don't care  |
   |-----------------|-----------|--------------|------------|--------------|--------------|
   |  TIMESTAMP and  |           |              |            |              |              |
   |  TAMPER input   |     1     |      1       |      1     |      1       |  Don't care  |
   |   floating      |           |              |            |              |              |
   |-----------------|-----------|--------------|------------|--------------|--------------|
   | TIMESTAMP input |           |              |    Don't   |              |              |
   |    floating     |     0     |      1       |    care    |      1       |  Don't care  |
   |-----------------|-----------|--------------|------------|--------------|--------------|
   |  Standard GPIO  |     0     |      0       | Don't care |  Don't care  |  Don't care  |
   +---------------------------------------------------------------------------------------+


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
#include "stm32f4xx_rtc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC
  * 简介: RTC驱动模块
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* 掩码定义 */
#define RTC_TR_RESERVED_MASK    ((uint32_t)0x007F7F7F)
#define RTC_DR_RESERVED_MASK    ((uint32_t)0x00FFFF3F)
#define RTC_INIT_MASK           ((uint32_t)0xFFFFFFFF)
#define RTC_RSF_MASK            ((uint32_t)0xFFFFFF5F)
#define RTC_FLAGS_MASK          ((uint32_t)(RTC_FLAG_TSOVF | RTC_FLAG_TSF | RTC_FLAG_WUTF | \
                                 RTC_FLAG_ALRBF | RTC_FLAG_ALRAF | RTC_FLAG_INITF | \
                                 RTC_FLAG_RSF | RTC_FLAG_INITS | RTC_FLAG_WUTWF | \
                                 RTC_FLAG_ALRBWF | RTC_FLAG_ALRAWF | RTC_FLAG_TAMP1F | \
                                 RTC_FLAG_TAMP2F | RTC_FLAG_RECALPF | RTC_FLAG_SHPF))

#define INITMODE_TIMEOUT         ((uint32_t) 0x00010000)
#define SYNCHRO_TIMEOUT          ((uint32_t) 0x00020000)
#define RECALPF_TIMEOUT          ((uint32_t) 0x00020000)
#define SHPF_TIMEOUT             ((uint32_t) 0x00001000)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/* 私有函数 ---------------------------------------------------------*/

/** @defgroup RTC_Private_Functions
  * @{
  */

/** @defgroup RTC_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
             ##### 初始化和配置函数 #####
 ===============================================================================

 [..] 本节提供的功能允许初始化和配置RTC预分频器(同步和异步)、RTC小时格式、
      禁用RTC寄存器写保护、进入和退出RTC初始化模式、RTC寄存器同步检查和基准时钟检测启用。

   (#) RTC 预分频器被编程为生成RTC 1Hz时基。它分为2个可编程预分频器，以最小化功耗。
       (++) 一个7位异步预分频器和一个13位同步预分频器。
       (++) 当两个预分频器都使用时，建议将异步预分频器配置为高值，以减少消耗。

   (#) 所有的RTC寄存器都有写保护。对RTC寄存器的写入是通过向写保护寄存器RTC_WPR写一个键来实现的。

   (#) 要配置RTC日历，用户应用程序应进入初始化模式。在这个模式下，日历计数器被停止，
       其值可以被更新。当初始化序列完成后，日历在4个RTCCLK周期后重新开始计数。

   (#) 在日历初始化、日历更新或从低功耗模式唤醒后，要通过影子寄存器读取日历，软件必须首先清除
       RSF标志。然后，软件必须等待它再次被设置，然后再读取日历，这意味着日历寄存器已经被正确地复制到
       RTC_TR和RTC_DR影子寄存器中。
       RTC_WaitForSynchro()函数实现了上述软件序列(RSF清零和RSF检查)。

@endverbatim
  * @{
  */

/**
  * 简介:  将 RTC 寄存器去初始化为其默认复位值。
  * 注意:   这个功能并不重置RTC时钟源和RTC备份数据寄存器。
  * 
  * 参数:  无
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC寄存器被取消初始化
  *          - ERROR: RTC寄存器没有被反初始化
  */
ErrorStatus RTC_DeInit(void) {
    __IO uint32_t wutcounter = 0x00;
    uint32_t wutwfstatus = 0x00;
    ErrorStatus status = ERROR;

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 设置初始化模式 */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        /* 复位TR、DR和CR寄存器 */
        RTC->TR = (uint32_t)0x00000000;
        RTC->DR = (uint32_t)0x00002101;
        /* Reset All CR bits except CR[2:0] */
        RTC->CR &= (uint32_t)0x00000007;

        /* 等到RTC的WUTWF标志被设置，如果达到超时则退出 */
        do {
            wutwfstatus = RTC->ISR & RTC_ISR_WUTWF;
            wutcounter++;
        } while((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));

        if ((RTC->ISR & RTC_ISR_WUTWF) == RESET) {
            status = ERROR;
        } else {
            /* 复位所有RTC CR寄存器位 */
            RTC->CR &= (uint32_t)0x00000000;
            RTC->WUTR = (uint32_t)0x0000FFFF;
            RTC->PRER = (uint32_t)0x007F00FF;
            RTC->CALIBR = (uint32_t)0x00000000;
            RTC->ALRMAR = (uint32_t)0x00000000;
            RTC->ALRMBR = (uint32_t)0x00000000;
            RTC->SHIFTR = (uint32_t)0x00000000;
            RTC->CALR = (uint32_t)0x00000000;
            RTC->ALRMASSR = (uint32_t)0x00000000;
            RTC->ALRMBSSR = (uint32_t)0x00000000;

            /* 复位ISR寄存器并退出初始化模式 */
            RTC->ISR = (uint32_t)0x00000000;

            /* Reset Tamper and alternate functions configuration 寄存器 */
            RTC->TAFCR = 0x00000000;

            if(RTC_WaitForSynchro() == ERROR) {
                status = ERROR;
            } else {
                status = SUCCESS;
            }
        }
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * 简介:  根据RTC_InitStruct中指定的参数初始化 RTC 寄存器。
  * 
  * 参数:  RTC_InitStruct: 指向包含RTC外设设备配置信息的RTC_InitTypeDef结构的指针。
  * 注意:   RTC预分频器寄存器有写保护，只能在初始化模式下写入。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC寄存器已初始化
  *          - ERROR: RTC寄存器未初始化
  */
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct) {
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
    assert_param(IS_RTC_ASYNCH_PREDIV(RTC_InitStruct->RTC_AsynchPrediv));
    assert_param(IS_RTC_SYNCH_PREDIV(RTC_InitStruct->RTC_SynchPrediv));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 设置初始化模式 */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        /* 清除 RTC CR FMT 位 */
        RTC->CR &= ((uint32_t)~(RTC_CR_FMT));
        /* Set RTC_CR 寄存器 */
        RTC->CR |=  ((uint32_t)(RTC_InitStruct->RTC_HourFormat));

        /* 配置 RTC PRER */
        RTC->PRER = (uint32_t)(RTC_InitStruct->RTC_SynchPrediv);
        RTC->PRER |= (uint32_t)(RTC_InitStruct->RTC_AsynchPrediv << 16);

        /* 退出初始化模式 */
        RTC_ExitInitMode();

        status = SUCCESS;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * 简介:  用其默认值填充每个RTC_InitStruct成员。
  * 
  * 参数:  RTC_InitStruct: 指向将被初始化的RTC_InitTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct) {
    /* 初始化 RTC_HourFormat 成员 */
    RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24;

    /* 初始化 RTC_AsynchPrediv 成员 */
    RTC_InitStruct->RTC_AsynchPrediv = (uint32_t)0x7F;

    /* 初始化 RTC_SynchPrediv 成员 */
    RTC_InitStruct->RTC_SynchPrediv = (uint32_t)0xFF;
}

/**
  * 简介:  启用或禁用 RTC 寄存器写保护。
  * 注意:   除了RTC_ISR[13:8]、RTC_TAFCR和RTC_BKPxR之外，所有的RTC寄存器都有写保护。
  * 注意:   写错的键会重新激活写保护。
  * 注意:   保护机制不受系统重置的影响。
  * 
  * 参数:  NewState: 写保护的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void RTC_WriteProtectionCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用对RTC寄存器的写保护 */
        RTC->WPR = 0xFF;
    } else {
        /* 禁用RTC寄存器的写保护 */
        RTC->WPR = 0xCA;
        RTC->WPR = 0x53;
    }
}

/**
  * 简介:  进入 RTC 初始化模式。
  * 
  * 注意:   RTC初始化模式是受写保护的，在调用此函数前请使用RTC_WriteProtectionCmd(DISABLE)。
  * 
  * 参数:  无
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC处于初始模式
  *          - ERROR: RTC不在初始模式下
  */
ErrorStatus RTC_EnterInitMode(void) {
    __IO uint32_t initcounter = 0x00;
    ErrorStatus status = ERROR;
    uint32_t initstatus = 0x00;

    /* 检查是否设置了初始化模式 */
    if ((RTC->ISR & RTC_ISR_INITF) == (uint32_t)RESET) {
        /* 设置初始化模式 */
        RTC->ISR = (uint32_t)RTC_INIT_MASK;

        /* 等待，直到RTC处于INIT状态，如果达到超时，则退出 */
        do {
            initstatus = RTC->ISR & RTC_ISR_INITF;
            initcounter++;
        } while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));

        if ((RTC->ISR & RTC_ISR_INITF) != RESET) {
            status = SUCCESS;
        } else {
            status = ERROR;
        }
    } else {
        status = SUCCESS;
    }

    return (status);
}

/**
  * 简介:  退出 RTC 初始化模式。
  * 
  * 注意:   当初始化序列完成后，日历在4个RTCCLK周期后重新开始计数。
  * 注意:   RTC初始化模式是受写保护的，在调用此函数前请使用RTC_WriteProtectionCmd(DISABLE)。
  * 
  * 参数:  无
  * 返回值: 无
  */
void RTC_ExitInitMode(void) {
    /* 退出初始化模式 */
    RTC->ISR &= (uint32_t)~RTC_ISR_INIT;
}

/**
  * 简介:  等到 RTC 时间和日期寄存器(RTC_TR和RTC_DR)与 RTC APB 时钟同步。
  * 
  * 注意:   RTC重新同步模式是受写保护的，在调用此函数前请使用RTC_WriteProtectionCmd(DISABLE)。
  * 
  * 注意:   在日历初始化、日历更新或从低功耗模式唤醒后，要通过影子寄存器读取日历，软件必须首先清除RSF标志。
  *         然后，软件必须等到它再次被设置后才能读取日历，这意味着日历寄存器已经被正确地
  *         复制到RTC_TR和RTC_DR影子寄存器中。
  * 
  * 参数:  无
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC寄存器同步
  *          - ERROR: RTC寄存器不同步
  */
ErrorStatus RTC_WaitForSynchro(void) {
    __IO uint32_t synchrocounter = 0;
    ErrorStatus status = ERROR;
    uint32_t synchrostatus = 0x00;

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 清除 RSF flag */
    RTC->ISR &= (uint32_t)RTC_RSF_MASK;

    /* 等待寄存器的同步 */
    do {
        synchrostatus = RTC->ISR & RTC_ISR_RSF;
        synchrocounter++;
    } while((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));

    if ((RTC->ISR & RTC_ISR_RSF) != RESET) {
        status = SUCCESS;
    } else {
        status = ERROR;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return (status);
}

/**
  * 简介:  启用或禁用RTC参考时钟检测。
  * 
  * 参数:  NewState: RTC基准时钟的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC参考时钟检测已启用
  *          - ERROR: RTC参考时钟检测被禁用
  */
ErrorStatus RTC_RefClockCmd(FunctionalState NewState) {
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 设置初始化模式 */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        if (NewState != DISABLE) {
            /* 启用RTC参考时钟检测 */
            RTC->CR |= RTC_CR_REFCKON;
        } else {
            /* 禁用RTC参考时钟检测 */
            RTC->CR &= ~RTC_CR_REFCKON;
        }

        /* 退出初始化模式 */
        RTC_ExitInitMode();

        status = SUCCESS;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * 简介:  启用或禁用旁路阴影功能。
  * 
  * 注意:   启用旁路阴影时，日历值直接从日历计数器中获取。
  * 
  * 参数:  NewState: 旁路阴影功能的新状态。
  *         此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
*/
void RTC_BypassShadowCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    if (NewState != DISABLE) {
        /* 设置 BYPSHAD 位 */
        RTC->CR |= (uint8_t)RTC_CR_BYPSHAD;
    } else {
        /* 重设 BYPSHAD 位 */
        RTC->CR &= (uint8_t)~RTC_CR_BYPSHAD;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * @}
  */

/** @defgroup RTC_Group2 时间和日期配置功能
 *  简介   时间和日期配置功能
 *
@verbatim
 ===============================================================================
                 ##### 时间和日期配置功能 #####
 ===============================================================================

 [..] 本节提供的功能允许对RTC日历(时间和日期)进行编程和读取。

@endverbatim
  * @{
  */

/**
  * 简介:  设置 RTC 当前时间。
  * 
  * 参数:  RTC_Format: 指定输入参数的格式。
  *          该参数可以是以下值之一:
  *            @arg RTC_Format_BIN:  二进制数据格式
  *            @arg RTC_Format_BCD:  BCD数据格式
  * 
  * 参数:  RTC_TimeStruct: 指向RTC_TimeTypeDef结构的指针，该结构包含RTC的时间配置信息。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC时间寄存器已被配置
  *          - ERROR: RTC时间寄存器没有配置
  */
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct) {
    uint32_t tmpreg = 0;
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    if (RTC_Format == RTC_Format_BIN) {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET) {
            assert_param(IS_RTC_HOUR12(RTC_TimeStruct->RTC_Hours));
            assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
        } else {
            RTC_TimeStruct->RTC_H12 = 0x00;
            assert_param(IS_RTC_HOUR24(RTC_TimeStruct->RTC_Hours));
        }

        assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
        assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
    } else {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET) {
            tmpreg = RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
            assert_param(IS_RTC_HOUR12(tmpreg));
            assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
        } else {
            RTC_TimeStruct->RTC_H12 = 0x00;
            assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
        }

        assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes)));
        assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds)));
    }

    /* 检查输入参数格式 */
    if (RTC_Format != RTC_Format_BIN) {
        tmpreg = (((uint32_t)(RTC_TimeStruct->RTC_Hours) << 16) | \
                  ((uint32_t)(RTC_TimeStruct->RTC_Minutes) << 8) | \
                  ((uint32_t)RTC_TimeStruct->RTC_Seconds) | \
                  ((uint32_t)(RTC_TimeStruct->RTC_H12) << 16));
    } else {
        tmpreg = (uint32_t)(((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Hours) << 16) | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Minutes) << 8) | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Seconds)) | \
                            (((uint32_t)RTC_TimeStruct->RTC_H12) << 16));
    }

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 设置初始化模式 */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        /* 设置 RTC_TR 寄存器 */
        RTC->TR = (uint32_t)(tmpreg & RTC_TR_RESERVED_MASK);

        /* 退出初始化模式 */
        RTC_ExitInitMode();

        /* 如果RTC_CR_BYPSHAD位=0，则等待同步，否则不需要此检查。 */
        if ((RTC->CR & RTC_CR_BYPSHAD) == RESET) {
            if(RTC_WaitForSynchro() == ERROR) {
                status = ERROR;
            } else {
                status = SUCCESS;
            }
        } else {
            status = SUCCESS;
        }
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * 简介:  用默认值填充每个RTC_TimeStruct成员(时间 = 00h:00min:00sec)。
  * 
  * 参数:  RTC_TimeStruct: 指向将被初始化的RTC_TimeTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct) {
    /* Time = 00h:00min:00sec */
    RTC_TimeStruct->RTC_H12 = RTC_H12_AM;
    RTC_TimeStruct->RTC_Hours = 0;
    RTC_TimeStruct->RTC_Minutes = 0;
    RTC_TimeStruct->RTC_Seconds = 0;
}

/**
  * 简介:  获取 RTC 当前时间。
  * 
  * 参数:  RTC_Format: 指定返回参数的格式。
  *          该参数可以是以下值之一:
  *            @arg RTC_Format_BIN:  二进制数据格式
  *            @arg RTC_Format_BCD:  BCD数据格式
  * 
  * 参数:  RTC_TimeStruct: 指向RTC_TimeTypeDef结构的指针，
  *                        该结构将包含返回的当前时间配置。
  * 
  * 返回值: 无
  */
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* 获取RTC_TR 寄存器 */
    tmpreg = (uint32_t)(RTC->TR & RTC_TR_RESERVED_MASK);

    /* 用读取的参数填充结构字段 */
    RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & (RTC_TR_HT | RTC_TR_HU)) >> 16);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)((tmpreg & (RTC_TR_MNT | RTC_TR_MNU)) >> 8);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)(tmpreg & (RTC_TR_ST | RTC_TR_SU));
    RTC_TimeStruct->RTC_H12 = (uint8_t)((tmpreg & (RTC_TR_PM)) >> 16);

    /* 检查输入参数格式 */
    if (RTC_Format == RTC_Format_BIN) {
        /* 将结构参数转换为二进制格式 */
        RTC_TimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
        RTC_TimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes);
        RTC_TimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds);
    }
}

/**
  * 简介:  获取 RTC 当前日历子秒值。
  * 
  * 注意:   此函数在读取SSR寄存器后冻结时间和日期寄存器。
  * 
  * 参数:  无
  * 
  * 返回值: RTC当前日历子秒值。
  */
uint32_t RTC_GetSubSecond(void) {
    uint32_t tmpreg = 0;

    /* 从相应寄存器获取次秒值*/
    tmpreg = (uint32_t)(RTC->SSR);

    /* 读取DR寄存器以解冻日历寄存器 */
    (void) (RTC->DR);

    return (tmpreg);
}

/**
  * 简介:  设置 RTC 当前日期。
  * 
  * 参数:  RTC_Format: 指定输入参数的格式。
  *          该参数可以是以下值之一:
  *            @arg RTC_Format_BIN:  二进制数据格式
  *            @arg RTC_Format_BCD:  BCD数据格式
  * 
  * 参数:  RTC_DateStruct: 指向包含RTC日期配置信息的RTC_DateTypeDef结构的指针。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC日期寄存器已配置
  *          - ERROR: RTC日期寄存器未配置
  */
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct) {
    uint32_t tmpreg = 0;
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    if ((RTC_Format == RTC_Format_BIN) && ((RTC_DateStruct->RTC_Month & 0x10) == 0x10)) {
        RTC_DateStruct->RTC_Month = (RTC_DateStruct->RTC_Month & (uint32_t)~(0x10)) + 0x0A;
    }

    if (RTC_Format == RTC_Format_BIN) {
        assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
        assert_param(IS_RTC_MONTH(RTC_DateStruct->RTC_Month));
        assert_param(IS_RTC_DATE(RTC_DateStruct->RTC_Date));
    } else {
        assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year)));
        tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
        assert_param(IS_RTC_MONTH(tmpreg));
        tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
        assert_param(IS_RTC_DATE(tmpreg));
    }

    assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->RTC_WeekDay));

    /* 检查输入参数格式 */
    if (RTC_Format != RTC_Format_BIN) {
        tmpreg = ((((uint32_t)RTC_DateStruct->RTC_Year) << 16) | \
                  (((uint32_t)RTC_DateStruct->RTC_Month) << 8) | \
                  ((uint32_t)RTC_DateStruct->RTC_Date) | \
                  (((uint32_t)RTC_DateStruct->RTC_WeekDay) << 13));
    } else {
        tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Year) << 16) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Month) << 8) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Date)) | \
                  ((uint32_t)RTC_DateStruct->RTC_WeekDay << 13));
    }

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 设置初始化模式 */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        /* 设置 RTC_DR 寄存器 */
        RTC->DR = (uint32_t)(tmpreg & RTC_DR_RESERVED_MASK);

        /* 退出初始化模式 */
        RTC_ExitInitMode();

        /* 如果RTC_CR_BYPSHAD位=0，则等待同步，否则不需要进行此检查 */
        if ((RTC->CR & RTC_CR_BYPSHAD) == RESET) {
            if(RTC_WaitForSynchro() == ERROR) {
                status = ERROR;
            } else {
                status = SUCCESS;
            }
        } else {
            status = SUCCESS;
        }
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * 简介:  用默认值填充每个RTC_DateStruct成员(星期一，一月 01 xx00)。
  * 
  * 参数:  RTC_DateStruct: 指向将被初始化的RTC_DateTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct) {
    /* Monday, January 01 xx00 */
    RTC_DateStruct->RTC_WeekDay = RTC_Weekday_Monday;
    RTC_DateStruct->RTC_Date = 1;
    RTC_DateStruct->RTC_Month = RTC_Month_January;
    RTC_DateStruct->RTC_Year = 0;
}

/** 
  * 简介:  获取RTC当前日期.
  * 
  * 参数:  RTC_Format: 指定返回参数的格式。
  *          此参数可以是以下值之一:
  *            @arg RTC_Format_BIN:二进制数据格式
  *            @arg RTC_Format_BCD:BCD数据格式
  * 
  * 参数: RTC_DateStruct: 指向RTC_DateTypeDef结构的指针，该结构将包含返回的当前日期配置。
  * 
  * 返回值: 无
  */
void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* 获取RTC_TR 寄存器 */
    tmpreg = (uint32_t)(RTC->DR & RTC_DR_RESERVED_MASK);

    /* 用读取的参数填充结构字段 */
    RTC_DateStruct->RTC_Year = (uint8_t)((tmpreg & (RTC_DR_YT | RTC_DR_YU)) >> 16);
    RTC_DateStruct->RTC_Month = (uint8_t)((tmpreg & (RTC_DR_MT | RTC_DR_MU)) >> 8);
    RTC_DateStruct->RTC_Date = (uint8_t)(tmpreg & (RTC_DR_DT | RTC_DR_DU));
    RTC_DateStruct->RTC_WeekDay = (uint8_t)((tmpreg & (RTC_DR_WDU)) >> 13);

    /* 检查输入参数格式 */
    if (RTC_Format == RTC_Format_BIN) {
        /* 将结构参数转换为二进制格式 */
        RTC_DateStruct->RTC_Year = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year);
        RTC_DateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
        RTC_DateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
    }
}

/**
  * @}
  */

/** @defgroup RTC_Group3 报警配置功能
 *  简介   报警(报警A和报警B)配置功能
 *
@verbatim
 ===============================================================================
         ##### 警报A和B配置功能 #####
 ===============================================================================

 [..] 本节提供允许编程和读取RTC警报的功能。

@endverbatim
  * @{
  */

/**
  * 简介:  设置指定的 RTC 警报。
  * 
  * 注意:   只有在禁用相应的报警时才能写入报警寄存器(使用RTC_AlarmCmd(DISABLE))。
  * 
  * 参数:  RTC_Format: 指定返回参数的格式。
  *          此参数可以是以下值之一:
  *            @arg RTC_Format_BIN:二进制数据格式
  *            @arg RTC_Format_BCD:BCD数据格式
  * 
  * 参数:  RTC_Alarm: 指定要配置的报警。
  *          此参数可以是以下值之一:
  *            @arg RTC_Alarm_A: 选择报警A
  *            @arg RTC_Alarm_B: 选择报警B
  * 
  * 参数:  RTC_AlarmStruct: 指向包含报警配置参数的 RTC_AlarmTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    assert_param(IS_RTC_ALARM(RTC_Alarm));
    assert_param(IS_ALARM_MASK(RTC_AlarmStruct->RTC_AlarmMask));
    assert_param(IS_RTC_ALARM_DATE_WEEKDAY_SEL(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel));

    if (RTC_Format == RTC_Format_BIN) {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET) {
            assert_param(IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
            assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
        } else {
            RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
            assert_param(IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
        }

        assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));
        assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));

        if(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel == RTC_AlarmDateWeekDaySel_Date) {
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
        } else {
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(RTC_AlarmStruct->RTC_AlarmDateWeekDay));
        }
    } else {
        if ((RTC->CR & RTC_CR_FMT) != (uint32_t)RESET) {
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
            assert_param(IS_RTC_HOUR12(tmpreg));
            assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
        } else {
            RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
            assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)));
        }

        assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)));
        assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)));

        if(RTC_AlarmStruct->RTC_AlarmDateWeekDaySel == RTC_AlarmDateWeekDaySel_Date) {
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(tmpreg));
        } else {
            tmpreg = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
            assert_param(IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(tmpreg));
        }
    }

    /* 检查输入参数格式 */
    if (RTC_Format != RTC_Format_BIN) {
        tmpreg = (((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) | \
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds) | \
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 16) | \
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmMask));
    } else {
        tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)) | \
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 16) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDateWeekDay) << 24) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmDateWeekDaySel) | \
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmMask));
    }

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 配置 Alarm 寄存器 */
    if (RTC_Alarm == RTC_Alarm_A) {
        RTC->ALRMAR = (uint32_t)tmpreg;
    } else {
        RTC->ALRMBR = (uint32_t)tmpreg;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * 简介:  用默认值填充每个RTC_AlarmStruct成员(时间 = 00h:00mn:00sec /
  *        日期 = 该月的第一天/掩码 = 所有字段都被屏蔽)。
  * 
  * 参数:  RTC_AlarmStruct: 指向将被初始化的@ref RTC_AlarmTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct) {
    /* 报警时间设置： Time = 00h:00mn:00sec */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;

    /* 报警日期设置： Date = 每月的第一天 */
    RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
    RTC_AlarmStruct->RTC_AlarmDateWeekDay = 1;

    /* 报警掩码设置s : Mask =  未屏蔽所有字段 */
    RTC_AlarmStruct->RTC_AlarmMask = RTC_AlarmMask_None;
}

/**
  * 简介:  获取 RTC 警报值和掩码。
  * 
  * 参数:  RTC_Format: 指定输出参数的格式。
  *          此参数可以是以下值之一:
  *            @arg RTC_Format_BIN:二进制数据格式
  *            @arg RTC_Format_BCD:BCD数据格式
  * 
  * 参数:  RTC_Alarm: 指定要读取的报警。
  *          此参数可以是以下值之一:
  *            @arg RTC_Alarm_A: 选择报警A
  *            @arg RTC_Alarm_B: 选择报警B
  * 
  * 参数:  RTC_AlarmStruct: 指向包含输出报警配置值的RTC_AlarmTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    assert_param(IS_RTC_ALARM(RTC_Alarm));

    /* 获取RTC_ALRMxR 寄存器 */
    if (RTC_Alarm == RTC_Alarm_A) {
        tmpreg = (uint32_t)(RTC->ALRMAR);
    } else {
        tmpreg = (uint32_t)(RTC->ALRMBR);
    }

    /* 用读取的参数填充结构 */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint32_t)((tmpreg & (RTC_ALRMAR_HT | \
            RTC_ALRMAR_HU)) >> 16);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint32_t)((tmpreg & (RTC_ALRMAR_MNT | \
            RTC_ALRMAR_MNU)) >> 8);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint32_t)(tmpreg & (RTC_ALRMAR_ST | \
            RTC_ALRMAR_SU));
    RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = (uint32_t)((tmpreg & RTC_ALRMAR_PM) >> 16);
    RTC_AlarmStruct->RTC_AlarmDateWeekDay = (uint32_t)((tmpreg & (RTC_ALRMAR_DT | RTC_ALRMAR_DU)) >> 24);
    RTC_AlarmStruct->RTC_AlarmDateWeekDaySel = (uint32_t)(tmpreg & RTC_ALRMAR_WDSEL);
    RTC_AlarmStruct->RTC_AlarmMask = (uint32_t)(tmpreg & RTC_AlarmMask_All);

    if (RTC_Format == RTC_Format_BIN) {
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = RTC_Bcd2ToByte(RTC_AlarmStruct-> \
                RTC_AlarmTime.RTC_Hours);
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = RTC_Bcd2ToByte(RTC_AlarmStruct-> \
                RTC_AlarmTime.RTC_Minutes);
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = RTC_Bcd2ToByte(RTC_AlarmStruct-> \
                RTC_AlarmTime.RTC_Seconds);
        RTC_AlarmStruct->RTC_AlarmDateWeekDay = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDateWeekDay);
    }
}

/**
  * 简介:  启用或禁用指定的 RTC 警报。
  * 
  * 参数:  RTC_Alarm: 指定要配置的报警。
  *          此参数可以是以下值的任意组合:
  *            @arg RTC_Alarm_A: 选择报警A
  *            @arg RTC_Alarm_B: 选择报警B
  * 
  * 参数:  NewState: 指定报警的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC警报已启用/禁用
  *          - ERROR: RTC警报未启用/禁用
  */
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState) {
    __IO uint32_t alarmcounter = 0x00;
    uint32_t alarmstatus = 0x00;
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_RTC_CMD_ALARM(RTC_Alarm));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 配置报警状态 */
    if (NewState != DISABLE) {
        RTC->CR |= (uint32_t)RTC_Alarm;

        status = SUCCESS;
    } else {
        /* 禁用 Alarm in RTC_CR 寄存器 */
        RTC->CR &= (uint32_t)~RTC_Alarm;

        /* 等待RTC ALRxWF标志设置，如果达到超时，则退出 */
        do {
            alarmstatus = RTC->ISR & (RTC_Alarm >> 8);
            alarmcounter++;
        } while((alarmcounter != INITMODE_TIMEOUT) && (alarmstatus == 0x00));

        if ((RTC->ISR & (RTC_Alarm >> 8)) == RESET) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * 简介:  配置 RTC 警报A/B 子秒值和掩码。
  * 
  * 注意:   这个功能只有在报警器被禁用时才会执行。
  * 
  * 参数:  RTC_Alarm: 指定要配置的报警。
  *   此参数可以是以下值之一:
  *     @arg RTC_Alarm_A: 选择报警A
  *     @arg RTC_Alarm_B: 选择报警B
  * 
  * 参数:  RTC_AlarmSubSecondValue: 指定子秒值。
  *   此参数可以是0到0x00007FFF之间的值。
  * 
  * 参数:  RTC_AlarmSubSecondMask:  指定子秒屏蔽。
  *   此参数可以是以下值的任意组合:
  *     @arg RTC_AlarmSubSecondMask_All    : 所有的报警SS字段都被屏蔽了。
  *                                          报警的子秒数没有比较。
  *     @arg RTC_AlarmSubSecondMask_SS14_1 : SS[14:1]在Alarm比较中是不被关心的。
  *                                          只有SS[0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_2 : SS[14:2]在Alarm比较中是不被关心的。
  *                                          只有SS[1:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_3 : SS[14:3]在Alarm比较中是不被关心的。
  *                                          只有SS[2:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_4 : SS[14:4]在Alarm比较中是不被关心的。
  *                                          只有SS[3:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_5 : SS[14:5]在Alarm比较中是不被关心的。
  *                                          只有SS[4:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_6 : SS[14:6]在Alarm比较中是不被关心的。
  *                                          只有SS[5:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_7 : SS[14:7]在Alarm比较中是不被关心的。
  *                                          只有SS[6:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_8 : SS[14:8]在Alarm比较中是不被关心的。
  *                                          只有SS[7:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_9 : SS[14:9]在Alarm比较中是不被关心的。
  *                                          只有SS[8:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_10: SS[14:10]在Alarm比较中是不被关心的。
  *                                          只有SS[9:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_11: SS[14:11]在Alarm比较中是不被关心的。
  *                                          只有SS[10:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_12: SS[14:12]在Alarm比较中是不被关心的。
  *                                          只有SS[11:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14_13: SS[14:13]在Alarm比较中是不被关心的。
  *                                          只有SS[12:0]被比较
  *     @arg RTC_AlarmSubSecondMask_SS14   : SS[14]在报警器比较中是不关心的。
  *                                          只有SS[13:0]被比较
  *     @arg RTC_AlarmSubSecondMask_None   : SS[14:0]被比较，必须匹配才能激活报警。
  * 
  * 返回值: 无
  */
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_RTC_ALARM(RTC_Alarm));
    assert_param(IS_RTC_ALARM_SUB_SECOND_VALUE(RTC_AlarmSubSecondValue));
    assert_param(IS_RTC_ALARM_SUB_SECOND_MASK(RTC_AlarmSubSecondMask));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 配置报警A或报警B次秒寄存器 */
    tmpreg = (uint32_t) (uint32_t)(RTC_AlarmSubSecondValue) | (uint32_t)(RTC_AlarmSubSecondMask);

    if (RTC_Alarm == RTC_Alarm_A) {
        /* 配置报警A 子秒寄存器 */
        RTC->ALRMASSR = tmpreg;
    } else {
        /* 配置报警B 子秒寄存器 */
        RTC->ALRMBSSR = tmpreg;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

}

/**
  * 简介:  获取 RTC 警报子秒值。
  * 
  * 参数:  RTC_Alarm: 指定要读取的报警。
  *   此参数可以是以下值之一:
  *     @arg RTC_Alarm_A: 选择报警A
  *     @arg RTC_Alarm_B: 选择报警B
  * 
  * 参数:  无
  * 
  * 返回值: RTC报警子秒值。
  */
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm) {
    uint32_t tmpreg = 0;

    /* 获取RTC_ALRMxR 寄存器 */
    if (RTC_Alarm == RTC_Alarm_A) {
        tmpreg = (uint32_t)((RTC->ALRMASSR) & RTC_ALRMASSR_SS);
    } else {
        tmpreg = (uint32_t)((RTC->ALRMBSSR) & RTC_ALRMBSSR_SS);
    }

    return (tmpreg);
}

/**
  * @}
  */

/** @defgroup RTC_Group4 唤醒定时器配置功能
 *  简介   唤醒定时器配置功能
 *
@verbatim
 ===============================================================================
                 ##### 唤醒定时器配置功能 #####
 ===============================================================================

 [..] 本节提供允许编程和读取RTC唤醒的功能。

@endverbatim
  * @{
  */

/**
  * 简介:  配置 RTC 唤醒时钟源。
  * 
  * 注意:   只有在禁用RTC唤醒时才能更改唤醒时钟源(使用RTC_WakeUpCmd(DISABLE))。
  * 
  * 参数:  RTC_WakeUpClock: 唤醒时钟源。
  *          此参数可以是以下值之一:
  *            @arg RTC_WakeUpClock_RTCCLK_Div16: RTC唤醒计数器时钟 = RTCCLK/16
  *            @arg RTC_WakeUpClock_RTCCLK_Div8: RTC唤醒计数器时钟 = RTCCLK/8
  *            @arg RTC_WakeUpClock_RTCCLK_Div4: RTC唤醒计数器时钟 = RTCCLK/4
  *            @arg RTC_WakeUpClock_RTCCLK_Div2: RTC唤醒计数器时钟 = RTCCLK/2
  *            @arg RTC_WakeUpClock_CK_SPRE_16bits: RTC唤醒计数器时钟 = CK_SPRE
  *            @arg RTC_WakeUpClock_CK_SPRE_17bits: RTC唤醒计数器时钟 = CK_SPRE
  * 
  * 返回值: 无
  */
void RTC_WakeUpClockConfig(uint32_t RTC_WakeUpClock) {
    /* 检查参数 */
    assert_param(IS_RTC_WAKEUP_CLOCK(RTC_WakeUpClock));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 清除CR中的唤醒定时器时钟源位寄存器 */
    RTC->CR &= (uint32_t)~RTC_CR_WUCKSEL;

    /* 配置时钟源 */
    RTC->CR |= (uint32_t)RTC_WakeUpClock;

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * 简介:  配置RTC唤醒计数器。
  * 
  * 注意:   RTC WakeUp计数器只能在禁用RTC WakeUp时写入(使用RTC_WakeUpCmd(DISABLE))。
  * 
  * 参数:  RTC_WakeUpCounter: 指定唤醒计数器.
  *          此参数可以是0x0000到0xFFFF之间的值。
  * 
  * 返回值: 无
  */
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter) {
    /* 检查参数 */
    assert_param(IS_RTC_WAKEUP_COUNTER(RTC_WakeUpCounter));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 配置唤醒计数器。 */
    RTC->WUTR = (uint32_t)RTC_WakeUpCounter;

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * 简介:  返回RTC唤醒计时器计数器值。
  * 
  * 参数:  无
  * 
  * 返回值: RTC唤醒计数器值。
  */
uint32_t RTC_GetWakeUpCounter(void) {
    /* 获取counter 值 */
    return ((uint32_t)(RTC->WUTR & RTC_WUTR_WUT));
}

/**
  * 简介:  启用或禁用RTC 唤醒计数器.
  * 
  * 参数:  NewState: 新状态-> WakeUp timer.
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
ErrorStatus RTC_WakeUpCmd(FunctionalState NewState) {
    __IO uint32_t wutcounter = 0x00;
    uint32_t wutwfstatus = 0x00;
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    if (NewState != DISABLE) {
        /* 启用 唤醒计数器 */
        RTC->CR |= (uint32_t)RTC_CR_WUTE;
        status = SUCCESS;
    } else {
        /* 禁用 唤醒计数器 */
        RTC->CR &= (uint32_t)~RTC_CR_WUTE;

        /* 等到RTC的WUTWF标志被设置，如果达到超时则退出 */
        do {
            wutwfstatus = RTC->ISR & RTC_ISR_WUTWF;
            wutcounter++;
        } while((wutcounter != INITMODE_TIMEOUT) && (wutwfstatus == 0x00));

        if ((RTC->ISR & RTC_ISR_WUTWF) == RESET) {
            status = ERROR;
        } else {
            status = SUCCESS;
        }
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * @}
  */

/** @defgroup RTC_Group5 夏令时配置功能
 *  简介   夏令时配置功能
 *
@verbatim
 ===============================================================================
              ##### 夏令时配置功能 #####
 ===============================================================================

 [..] 本节提供了允许配置RTC夏令时的功能。

@endverbatim
  * @{
  */

/**
  * 简介:  从当前时间相加或减去一小时。
  * 
  * 参数:  RTC_DayLightSaveOperation: 小时调整值。
  *          此参数可以是以下值之一:
  *            @arg RTC_DayLightSaving_SUB1H: Substract one hour (winter time)
  *            @arg RTC_DayLightSaving_ADD1H: Add one hour (summer time)
  * 
  * 参数:  RTC_StoreOperation: 指定要写入CR寄存器BCK位以存储操作的值。
  *          此参数可以是以下值之一:
  *            @arg RTC_StoreOperation_Reset: BCK位重置
  *            @arg RTC_StoreOperation_Set: BCK Bit Set
  * 
  * 返回值: 无
  */
void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation) {
    /* 检查参数 */
    assert_param(IS_RTC_DAYLIGHT_SAVING(RTC_DayLightSaving));
    assert_param(IS_RTC_STORE_OPERATION(RTC_StoreOperation));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 清除要配置的位 */
    RTC->CR &= (uint32_t)~(RTC_CR_BCK);

    /* 配置 RTC_CR 寄存器 */
    RTC->CR |= (uint32_t)(RTC_DayLightSaving | RTC_StoreOperation);

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * 简介:  返回RTC日间节能存储操作。
  * 
  * 参数:  无
  * 
  * 返回值: RTC日间节能存储操作。
  *          - RTC_StoreOperation_Reset
  *          - RTC_StoreOperation_Set
  */
uint32_t RTC_GetStoreOperation(void) {
    return (RTC->CR & RTC_CR_BCK);
}

/**
  * @}
  */

/** @defgroup RTC_Group6 输出引脚配置功能
 *  简介   输出引脚配置功能
 *
@verbatim
 ===============================================================================
                 ##### 输出引脚配置功能 #####
 ===============================================================================

 [..] 本节提供了允许配置RTC输出源的功能。

@endverbatim
  * @{
  */

/**
  * 简介:  配置 RTC 输出源 (AFO_ALARM)。
  * 
  * 参数:  RTC_Output: 指定将路由到RTC输出的信号。
  *          此参数可以是以下值之一:
  *            @arg RTC_Output_Disable: 未选择输出
  *            @arg RTC_Output_AlarmA: 映射到输出的AlarmA信号
  *            @arg RTC_Output_AlarmB: 映射到输出的AlarmB信号
  *            @arg RTC_Output_WakeUp: 映射到输出的唤醒信号
  * 
  * 参数:  RTC_OutputPolarity: 指定输出信号的极性。
  *          此参数可以是以下参数之一:
  *            @arg RTC_OutputPolarity_High: 当ALRAF/ALRBF/WUTF高时，输出引脚高(取决于OSEL)
  *            @arg RTC_OutputPolarity_Low: 当ALRAF/ALRBF/WUTF高时，输出引脚低(取决于OSEL)
  * 
  * 返回值: 无
  */
void RTC_OutputConfig(uint32_t RTC_Output, uint32_t RTC_OutputPolarity) {
    /* 检查参数 */
    assert_param(IS_RTC_OUTPUT(RTC_Output));
    assert_param(IS_RTC_OUTPUT_POL(RTC_OutputPolarity));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 清除要配置的位 */
    RTC->CR &= (uint32_t)~(RTC_CR_OSEL | RTC_CR_POL);

    /* 配置输出选择和极性 */
    RTC->CR |= (uint32_t)(RTC_Output | RTC_OutputPolarity);

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * @}
  */

/** @defgroup RTC_Group7 数字校准配置功能
 *  简介   粗校准配置功能
 *
@verbatim
 ===============================================================================
              ##### 数字校准配置功能 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  配置粗略校准参数。
  * 
  * 参数:  RTC_CalibSign: 指定粗校准值的符号。
  *          该参数可以是以下值之一:
  *            @arg RTC_CalibSign_Positive: 值符号为正
  *            @arg RTC_CalibSign_Negative: 值符号为负
  * 
  * 参数:  Value: 以ppm表示的粗校准值(编码为5位)。
  *
  * 注意:   当使用负符号和2-ppm步长时，该校准值应介于0和63之间。
  *
  * 注意:   当使用正号和4-ppm步长时，此校准值应介于0和126之间。
  *
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC粗校准已初始化
  *          - ERROR: RTC粗校准未初始化
  */
ErrorStatus RTC_CoarseCalibConfig(uint32_t RTC_CalibSign, uint32_t Value) {
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_RTC_CALIB_SIGN(RTC_CalibSign));
    assert_param(IS_RTC_CALIB_VALUE(Value));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 设置初始化模式 */
    if (RTC_EnterInitMode() == ERROR) {
        status = ERROR;
    } else {
        /* 设置 coarse calibration 值 */
        RTC->CALIBR = (uint32_t)(RTC_CalibSign | Value);
        /* 退出初始化模式 */
        RTC_ExitInitMode();

        status = SUCCESS;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * 简介:  启用或禁用粗校准过程。
  * 
  * 参数:  NewState: 粗校准的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC粗校准已启用/禁用
  *          - ERROR: RTC粗校准未启用/禁用
  */
ErrorStatus RTC_CoarseCalibCmd(FunctionalState NewState) {
    ErrorStatus status = ERROR;

    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 设置初始化模式 */
    if (RTC_EnterInitMode() == ERROR) {
        status =  ERROR;
    } else {
        if (NewState != DISABLE) {
            /* 启用粗校准 */
            RTC->CR |= (uint32_t)RTC_CR_DCE;
        } else {
            /* 禁用粗校准 */
            RTC->CR &= (uint32_t)~RTC_CR_DCE;
        }

        /* 退出初始化模式 */
        RTC_ExitInitMode();

        status = SUCCESS;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return status;
}

/**
  * 简介:  启用或禁用通过相关引脚输出的RTC时钟。
  * 
  * 参数:  NewState: 数字校准输出的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void RTC_CalibOutputCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    if (NewState != DISABLE) {
        /* 启用RTC时钟输出 */
        RTC->CR |= (uint32_t)RTC_CR_COE;
    } else {
        /* 禁用RTC时钟输出 */
        RTC->CR &= (uint32_t)~RTC_CR_COE;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * 简介:  配置校准引脚排列(RTC_CALIB)选择(1Hz 或 512Hz)。
  * 
  * 参数:  RTC_CalibOutput : 选择校准输出选择。
  *   此参数可以是以下值之一:
  *     @arg RTC_CalibOutput_512Hz: 信号具有512Hz的规则波形。
  *     @arg RTC_CalibOutput_1Hz  : 信号具有1Hz的规则波形。
  * 
  * 返回值: 无
*/
void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput) {
    /* 检查参数 */
    assert_param(IS_RTC_CALIB_OUTPUT(RTC_CalibOutput));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 清除之前的标志配置 */
    RTC->CR &= (uint32_t)~(RTC_CR_COSEL);

    /* 配置RTC_CR寄存器 */
    RTC->CR |= (uint32_t)RTC_CalibOutput;

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * 简介:  配置平滑校准设置。
  * 
  * 参数:  RTC_SmoothCalibPeriod : 选择平滑校准周期。
  *   此参数可以是以下值之一:
  *     @arg RTC_SmoothCalibPeriod_32sec : 平滑校准周期为32秒。
  *     @arg RTC_SmoothCalibPeriod_16sec : 平滑校准周期为16秒。
  *     @arg RTC_SmoothCalibPeriod_8sec  : 平滑校准周期为8秒。
  * 
  * 参数:  RTC_SmoothCalibPlusPulses : 选择以设置或重置CALP位。
  *   此参数可以是以下值之一:
  *     @arg RTC_SmoothCalibPlusPulses_Set  : 每2**11个脉冲添加一个RTCCLK脉冲。
  *     @arg RTC_SmoothCalibPlusPulses_Reset: 未添加RTCCLK脉冲。
  * 
  * 参数:  RTC_SmouthCalibMinusPulsesValue: 选择CALM[8:0]位的值。
  *        此参数可以是0到0x000001FF之间的任意值。
  * 
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC校准寄存器已配置
  *          - ERROR: RTC校准寄存器未配置
*/
ErrorStatus RTC_SmoothCalibConfig(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue) {
    ErrorStatus status = ERROR;
    uint32_t recalpfcount = 0;

    /* 检查参数 */
    assert_param(IS_RTC_SMOOTH_CALIB_PERIOD(RTC_SmoothCalibPeriod));
    assert_param(IS_RTC_SMOOTH_CALIB_PLUS(RTC_SmoothCalibPlusPulses));
    assert_param(IS_RTC_SMOOTH_CALIB_MINUS(RTC_SmouthCalibMinusPulsesValue));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 检查是否正在等待校准*/
    if ((RTC->ISR & RTC_ISR_RECALPF) != RESET) {
        /* 等待校准完成 */
        while (((RTC->ISR & RTC_ISR_RECALPF) != RESET) && (recalpfcount != RECALPF_TIMEOUT)) {
            recalpfcount++;
        }
    }

    /* 检查如果校准挂起已完成或根本没有校准操作*/
    if ((RTC->ISR & RTC_ISR_RECALPF) == RESET) {
        /* 配置平滑校准设置 */
        RTC->CALR = (uint32_t)((uint32_t)RTC_SmoothCalibPeriod | (uint32_t)RTC_SmoothCalibPlusPulses | (uint32_t)RTC_SmouthCalibMinusPulsesValue);

        status = SUCCESS;
    } else {
        status = ERROR;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return (ErrorStatus)(status);
}

/**
  * @}
  */


/** @defgroup RTC_Group8 TimeStamp 配置功能
 *  简介   TimeStamp 配置功能
 *
@verbatim
 ===============================================================================
                 ##### TimeStamp 配置功能 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  启用或禁用具有指定时间戳引脚刺激边缘的RTC TimeStamp功能。
  * 
  * 参数:  RTC_TimeStampEdge: 指定激活TimeStamp的管脚边缘。
  *          此参数可以是以下参数之一:
  *            @arg RTC_TimeStampEdge_Rising: 时间戳事件发生在相关引脚的上升沿上。
  *            @arg RTC_TimeStampEdge_Falling: 时间戳事件发生在相关引脚的下降沿上。
  * 
  * 参数:  NewState: 新状态-> TimeStamp.
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_RTC_TIMESTAMP_EDGE(RTC_TimeStampEdge));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 获取RTC_CR 寄存器 and 清除要配置的位 */
    tmpreg = (uint32_t)(RTC->CR & (uint32_t)~(RTC_CR_TSEDGE | RTC_CR_TSE));

    /* 获取new 配置*/
    if (NewState != DISABLE) {
        tmpreg |= (uint32_t)(RTC_TimeStampEdge | RTC_CR_TSE);
    } else {
        tmpreg |= (uint32_t)(RTC_TimeStampEdge);
    }

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 配置时间戳 TSEDGE 和 Enable 位 */
    RTC->CR = (uint32_t)tmpreg;

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * 简介:  获取 RTC 时间戳值和掩码。
  * 
  * 参数:  RTC_Format: 指定输出参数的格式。
  *          此参数可以是以下值之一:
  *            @arg RTC_Format_BIN:二进制数据格式
  *            @arg RTC_Format_BCD:BCD数据格式
  * 
  * 参数: RTC_StampTimeStruct: 指向RTC_TimeTypeDef结构的指针，该结构将包含TimeStamp时间值。
  * 
  * 参数: RTC_StampDateStruct: 指向将包含TimeStamp日期值的RTC_DateTypeDef结构的指针。
  * 
  * 返回值: 无
  */
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct,
                      RTC_DateTypeDef* RTC_StampDateStruct) {
    uint32_t tmptime = 0, tmpdate = 0;

    /* 检查参数 */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* 获取时间戳时间和日期寄存器值 */
    tmptime = (uint32_t)(RTC->TSTR & RTC_TR_RESERVED_MASK);
    tmpdate = (uint32_t)(RTC->TSDR & RTC_DR_RESERVED_MASK);

    /* 用读取的参数填充时间结构字段 */
    RTC_StampTimeStruct->RTC_Hours = (uint8_t)((tmptime & (RTC_TR_HT | RTC_TR_HU)) >> 16);
    RTC_StampTimeStruct->RTC_Minutes = (uint8_t)((tmptime & (RTC_TR_MNT | RTC_TR_MNU)) >> 8);
    RTC_StampTimeStruct->RTC_Seconds = (uint8_t)(tmptime & (RTC_TR_ST | RTC_TR_SU));
    RTC_StampTimeStruct->RTC_H12 = (uint8_t)((tmptime & (RTC_TR_PM)) >> 16);

    /* 用读取的参数填充Date结构字段 */
    RTC_StampDateStruct->RTC_Year = 0;
    RTC_StampDateStruct->RTC_Month = (uint8_t)((tmpdate & (RTC_DR_MT | RTC_DR_MU)) >> 8);
    RTC_StampDateStruct->RTC_Date = (uint8_t)(tmpdate & (RTC_DR_DT | RTC_DR_DU));
    RTC_StampDateStruct->RTC_WeekDay = (uint8_t)((tmpdate & (RTC_DR_WDU)) >> 13);

    /* 检查输入参数格式 */
    if (RTC_Format == RTC_Format_BIN) {
        /* 将时间结构参数转换为二进制格式 */
        RTC_StampTimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Hours);
        RTC_StampTimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Minutes);
        RTC_StampTimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_StampTimeStruct->RTC_Seconds);

        /* 将Date结构参数转换为二进制格式 */
        RTC_StampDateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Month);
        RTC_StampDateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_Date);
        RTC_StampDateStruct->RTC_WeekDay = (uint8_t)RTC_Bcd2ToByte(RTC_StampDateStruct->RTC_WeekDay);
    }
}

/**
  * 简介:  获取 RTC 时间戳子秒值。
  * 
  * 参数:  无
  * 
  * 返回值: RTC当前时间戳子秒值。
  */
uint32_t RTC_GetTimeStampSubSecond(void) {
    /* 从对应寄存器获取时间戳子秒值 */
    return (uint32_t)(RTC->TSSSR);
}

/**
  * @}
  */

/** @defgroup RTC_Group9 篡改配置功能
 *  简介   篡改配置功能
 *
@verbatim
 ===============================================================================
                 ##### 篡改配置功能 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  配置选择篡改引脚边缘。
  * 
  * 参数:  RTC_Tamper: 选定的防盗销。
  *          取值为RTC_Tamper_1或RTC_Tamper 2
  * 
  * 参数:  RTC_TamperTrigger: 指定触发篡改事件的篡改pin上的触发器。
  *   此参数可以是以下值之一:
  *     @arg RTC_TamperTrigger_RisingEdge: 防篡改销的上升边缘会导致篡改事件。
  *     @arg RTC_TamperTrigger_FallingEdge: 防篡改销的下降边缘导致篡改事件。
  *     @arg RTC_TamperTrigger_LowLevel: 防篡改销液位低会导致篡改事件。
  *     @arg RTC_TamperTrigger_HighLevel: 防篡改销的高电平导致篡改事件。
  * 
  * 返回值: 无
  */
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger) {
    /* 检查参数 */
    assert_param(IS_RTC_TAMPER(RTC_Tamper));
    assert_param(IS_RTC_TAMPER_TRIGGER(RTC_TamperTrigger));

    if (RTC_TamperTrigger == RTC_TamperTrigger_RisingEdge) {
        /* 配置 RTC_TAFCR 寄存器 */
        RTC->TAFCR &= (uint32_t)((uint32_t)~(RTC_Tamper << 1));
    } else {
        /* 配置 RTC_TAFCR 寄存器 */
        RTC->TAFCR |= (uint32_t)(RTC_Tamper << 1);
    }
}

/**
  * 简介:  启用或禁用篡改检测。
  * 
  * 参数:  RTC_Tamper: 选定的防盗销。
  *          取值为RTC_Tamper_1或RTC_Tamper_2
  * 
  * 参数:  NewState: 新状态-> tamper pin.
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_RTC_TAMPER(RTC_Tamper));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 Tamper pin */
        RTC->TAFCR |= (uint32_t)RTC_Tamper;
    } else {
        /* 禁用被选中的 Tamper pin */
        RTC->TAFCR &= (uint32_t)~RTC_Tamper;
    }
}

/**
  * 简介:  配置篡改过滤器。
  * 
  * 参数:  RTC_TamperFilter: 指定tampers 过滤器。
  *   此参数可以是以下值之一:
  *     @arg RTC_TamperFilter_Disable: 篡改过滤器已禁用。
  *     @arg RTC_TamperFilter_2Sample: 在激活水平下连续2个样本后激活篡改
  *     @arg RTC_TamperFilter_4Sample: 在激活水平下连续4个样本后激活篡改
  *     @arg RTC_TamperFilter_8Sample: 在激活水平下连续8个样本后激活篡改
  * 
  * 返回值: 无
  */
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter) {
    /* 检查参数 */
    assert_param(IS_RTC_TAMPER_FILTER(RTC_TamperFilter));

    /* 清除 TAMPFLT[1:0] bits in the RTC_TAFCR 寄存器 */
    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPFLT);

    /* 配置 RTC_TAFCR 寄存器 */
    RTC->TAFCR |= (uint32_t)RTC_TamperFilter;
}

/**
  * 简介:  配置篡改采样频率。
  * 
  * 参数:  RTC_TamperSamplingFreq: 指定篡改器采样频率。
  *   此参数可以是以下值之一:
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div32768: 每个篡改输入以频率 = RTCCLK / 32768 进行采样
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div16384: 每个篡改输入以频率 = RTCCLK / 16384 进行采样
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div8192: 每个篡改输入以频率 = RTCCLK / 8192 进行采样
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div4096: 每个篡改输入以频率 = RTCCLK / 4096 进行采样
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div2048: 每个篡改输入以频率 = RTCCLK / 2048 进行采样
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div1024: 每个篡改输入以频率 = RTCCLK / 1024 进行采样
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div512: 每个篡改输入以频率 = RTCCLK / 512 进行采样
  *     @arg RTC_TamperSamplingFreq_RTCCLK_Div256: 每个篡改输入以频率 = RTCCLK / 256 进行采样
  * 
  * 返回值: 无
  */
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq) {
    /* 检查参数 */
    assert_param(IS_RTC_TAMPER_SAMPLING_FREQ(RTC_TamperSamplingFreq));

    /* 清除 TAMPFREQ[2:0] bits in the RTC_TAFCR 寄存器 */
    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPFREQ);

    /* 配置 RTC_TAFCR 寄存器 */
    RTC->TAFCR |= (uint32_t)RTC_TamperSamplingFreq;
}

/**
  * 简介:  配置篡改引脚输入预充电持续时间。
  * 
  * 参数:  RTC_TamperPrechargeDuration: 指定Tampers Pins输入预充电时间。
  *   此参数可以是以下值之一:
  *     @arg RTC_TamperPrechargeDuration_1RTCCLK: 在 1 个RTCCLK循环中采样之前，对防篡改引脚进行预充电
  *     @arg RTC_TamperPrechargeDuration_2RTCCLK: 在 2 个RTCCLK循环中采样之前，对防篡改引脚进行预充电
  *     @arg RTC_TamperPrechargeDuration_4RTCCLK: 在 4 个RTCCLK循环中采样之前，对防篡改引脚进行预充电
  *     @arg RTC_TamperPrechargeDuration_8RTCCLK: 在 8 个RTCCLK循环中采样之前，对防篡改引脚进行预充电
  * 
  * 返回值: 无
  */
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration) {
    /* 检查参数 */
    assert_param(IS_RTC_TAMPER_PRECHARGE_DURATION(RTC_TamperPrechargeDuration));

    /* 清除 TAMPPRCH[1:0] bits in the RTC_TAFCR 寄存器 */
    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPPRCH);

    /* 配置 RTC_TAFCR 寄存器 */
    RTC->TAFCR |= (uint32_t)RTC_TamperPrechargeDuration;
}

/**
  * 简介:  启用或禁用篡改检测事件的时间戳。
  * 
  * 注意:   即使篡改控制寄存器中的TSE位被重置，时间戳仍然有效。
  * 
  * 参数:  NewState: 新状态-> timestamp on tamper event.
  *         此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 保存篡改检测事件的时间戳 */
        RTC->TAFCR |= (uint32_t)RTC_TAFCR_TAMPTS;
    } else {
        /* 篡改检测不会导致保存时间戳 */
        RTC->TAFCR &= (uint32_t)~RTC_TAFCR_TAMPTS;
    }
}

/**
  * 简介:  启用或禁用篡改引脚的预充电。
  * 
  * 参数:  NewState: 新状态->  tamper pull up.
  *   此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void RTC_TamperPullUpCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能所选Tamper引脚的预充电 */
        RTC->TAFCR &= (uint32_t)~RTC_TAFCR_TAMPPUDIS;
    } else {
        /* 禁用所选Tamper引脚的预充电 */
        RTC->TAFCR |= (uint32_t)RTC_TAFCR_TAMPPUDIS;
    }
}

/**
  * @}
  */

/** @defgroup RTC_Group10 备份数据寄存器配置功能
 *  简介   备份数据寄存器配置功能
 *
@verbatim
 ===============================================================================
             ##### 备份数据寄存器配置功能 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  在指定的 RTC 备份数据寄存器中写入数据。
  * 
  * 参数:  RTC_BKP_DR: RTC备份数据寄存器号。
  *          此参数可以是: RTC_BKP_DRx，其中x可以从0到19指定寄存器。
  * 
  * 参数:  Data: 写入指定RTC备份数据寄存器的数据。
  * 
  * 返回值: 无
  */
void RTC_WriteBackupRegister(uint32_t RTC_BKP_DR, uint32_t Data) {
    __IO uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_RTC_BKP(RTC_BKP_DR));

    tmp = RTC_BASE + 0x50;
    tmp += (RTC_BKP_DR * 4);

    /* 写 specified 寄存器 */
    *(__IO uint32_t *)tmp = (uint32_t)Data;
}

/**
  * 简介:  从指定的 RTC 备份数据寄存器读取数据。
  * 
  * 参数:  RTC_BKP_DR: RTC备份数据寄存器号。
  *          此参数可以是: RTC_BKP_DRx，其中x可以从0到19指定寄存器。
  * 
  * 返回值: 无
  */
uint32_t RTC_ReadBackupRegister(uint32_t RTC_BKP_DR) {
    __IO uint32_t tmp = 0;

    /* 检查参数 */
    assert_param(IS_RTC_BKP(RTC_BKP_DR));

    tmp = RTC_BASE + 0x50;
    tmp += (RTC_BKP_DR * 4);

    /* 读 specified 寄存器 */
    return (*(__IO uint32_t *)tmp);
}

/**
  * @}
  */

/** @defgroup RTC_Group11 RTC防篡改和时间戳引脚选择和输出类型配置功能
 *  简介   RTC防篡改和时间戳引脚选择和输出类型配置功能
 *
@verbatim
 ==================================================================================================
 ##### RTC防篡改和时间戳引脚选择和输出类型配置功能 #####
 ==================================================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  选择 RTC 篡改引脚。
  * 
  * 参数:  RTC_TamperPin: 指定RTC Tamper Pin。
  *          此参数可以是以下值之一:
  *            @arg RTC_TamperPin_Default: RTC_AF1 用作RTC篡改引脚。
  *            @arg RTC_TamperPin_Pos1: RTC_AF2 用作RTC篡改引脚。
  * 
  * 返回值: 无
  */
void RTC_TamperPinSelection(uint32_t RTC_TamperPin) {
    /* 检查参数 */
    assert_param(IS_RTC_TAMPER_PIN(RTC_TamperPin));

    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TAMPINSEL);
    RTC->TAFCR |= (uint32_t)(RTC_TamperPin);
}

/**
  * 简介:  选择 RTC 时间戳引脚。
  * 
  * 参数:  RTC_TimeStampPin: RTC时间戳引脚。
  *          此参数可以是以下值之一:
  *            @arg RTC_TimeStampPin_PC13: PC13 被选为 RTC 时间戳引脚。
  *            @arg RTC_TimeStampPin_PI8: PI8 被选为 RTC 时间戳引脚。
  * 
  * 返回值: 无
  */
void RTC_TimeStampPinSelection(uint32_t RTC_TimeStampPin) {
    /* 检查参数 */
    assert_param(IS_RTC_TIMESTAMP_PIN(RTC_TimeStampPin));

    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_TSINSEL);
    RTC->TAFCR |= (uint32_t)(RTC_TimeStampPin);
}

/**
  * 简介:  配置 RTC 输出引脚模式。
  * 
  * 参数:  RTC_OutputType: 指定RTC Output (PC13) pin mode.
  *          此参数可以是以下值之一:
  *            @arg RTC_OutputType_OpenDrain: RTC输出(PC13)配置为开漏模式。
  *            @arg RTC_OutputType_PushPull:  RTC输出(PC13)配置为推拉模式。
  * 
  * 返回值: 无
  */
void RTC_OutputTypeConfig(uint32_t RTC_OutputType) {
    /* 检查参数 */
    assert_param(IS_RTC_OUTPUT_TYPE(RTC_OutputType));

    RTC->TAFCR &= (uint32_t)~(RTC_TAFCR_ALARMOUTTYPE);
    RTC->TAFCR |= (uint32_t)(RTC_OutputType);
}

/**
  * @}
  */

/** @defgroup RTC_Group12 移位控制同步功能
 *  简介   移位控制同步功能
 *
@verbatim
 ===============================================================================
              ##### 移位控制同步功能 #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * 简介:  配置同步切换控制设置。
  * 
  * 注意:   设置REFCKON时，固件不得写入移位控制寄存器
  * 
  * 参数:  RTC_ShiftAdd1S : 选择可在时间日历中添加或不添加1秒。
  *   此参数可以是以下值之一:
  *     @arg RTC_ShiftAdd1S_Set  : 将一秒钟添加到时钟日历中。
  *     @arg RTC_ShiftAdd1S_Reset: No effect.
  * 参数:  RTC_ShiftSubFS: 选择要替换的第二个分数的数量。
  *         此参数可以是 0 到 0x7FFF 之间的任意值。
  * 返回值: ErrorStatus枚举值:
  *          - SUCCESS: RTC Shift registers are configured
  *          - ERROR: RTC Shift registers are not configured
*/
ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS) {
    ErrorStatus status = ERROR;
    uint32_t shpfcount = 0;

    /* 检查参数 */
    assert_param(IS_RTC_SHIFT_ADD1S(RTC_ShiftAdd1S));
    assert_param(IS_RTC_SHIFT_SUBFS(RTC_ShiftSubFS));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    /* 检查 if a Shift is pending*/
    if ((RTC->ISR & RTC_ISR_SHPF) != RESET) {
        /* Wait until the shift is completed*/
        while (((RTC->ISR & RTC_ISR_SHPF) != RESET) && (shpfcount != SHPF_TIMEOUT)) {
            shpfcount++;
        }
    }

    /* 检查是否完成了移位挂起，或者根本没有移位操作*/
    if ((RTC->ISR & RTC_ISR_SHPF) == RESET) {
        /* 检查如果参考时钟检测被禁用 */
        if((RTC->CR & RTC_CR_REFCKON) == RESET) {
            /* 配置 Shift settings */
            RTC->SHIFTR = (uint32_t)(uint32_t)(RTC_ShiftSubFS) | (uint32_t)(RTC_ShiftAdd1S);

            if(RTC_WaitForSynchro() == ERROR) {
                status = ERROR;
            } else {
                status = SUCCESS;
            }
        } else {
            status = ERROR;
        }
    } else {
        status = ERROR;
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;

    return (ErrorStatus)(status);
}

/**
  * @}
  */

/** @defgroup RTC_Group13 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
              ##### 中断和标记管理函数 #####
 ===============================================================================
 [..] 所有的RTC中断都连接到EXTI控制器。

   (+) 要启用RTC报警中断，需要按以下顺序进行。
       (++) 使用EXTI_Init()函数配置并启用中断模式下的EXTI 17号线，并选择上升沿灵敏度。
       (++) 使用NVIC_Init()函数配置并启用NVIC中的RTC_Alarm IRQ通道。
       (++) 使用RTC_SetAlarm()和RTC_AlarmCmd()函数配置RTC以产生RTC报警(报警A和/或报警B)。

   (+) 要启用RTC唤醒中断，需要按以下顺序进行。
       (++) 在中断模式下配置和启用EXTI 22号线，并使用EXTI_Init()函数
            选择上升沿灵敏度。使用EXTI_Init()函数选择上升沿灵敏度。
       (++) 使用NVIC_Init()函数配置并启用NVIC中的RTC_WKUP IRQ通道。
            NVIC_Init()函数配置并启用RTC_WKUP IRQ通道。
       (++) 配置RTC，使其产生RTC唤醒定时器事件，使用 RTC_WakeUpClockConfig(),
            RTC_SetWakeUpCounter()和RTC_WakeUpCmd() 函数。

   (+) 要启用RTC Tamper中断，需要按以下顺序进行。
       (++) 配置并启用中断模式下的EXTI 21号线，并使用EXTI_Init()函数
            选择上升沿灵敏度。使用EXTI_Init()函数选择上升沿灵敏度。
       (++) 使用NVIC_Init()函数配置并启用NVIC中的TAMP_STAMP IRQ通道。
            NVIC_Init()函数配置并启用NVIC的TAMP_STAMP IRQ通道。
       (++) 配置RTC，以检测RTC篡改事件，使用 RTC_TamperTriggerConfig()和
            RTC_TamperCmd()函数配置RTC以检测RTC篡改事件。

   (+) 要启用RTC时间戳中断，需要按以下顺序进行。
       (++) 配置并启用中断模式下的EXTI 21号线，并使用EXTI_Init()函数
            选择上升沿灵敏度。使用EXTI_Init()函数选择上升沿灵敏度。
       (++) 使用NVIC_Init()函数配置并启用NVIC中的TAMP_STAMP IRQ通道。NVIC_Init()函数
            配置并启用NVIC的TAMP_STAMP IRQ通道。
       (++) 配置RTC，以检测RTC时间戳事件，使用 RTC_TimeStampCmd()函数检测RTC时间戳事件。

@endverbatim
  * @{
  */

/**
  * 简介:  启用或禁用指定的 RTC 中断。
  * 
  * 参数:  RTC_IT: 指定要启用或禁用的RTC中断源。
  *          此参数可以是以下值的任意组合:
  *          @arg RTC_IT_TS:  时间戳中断掩码
  *          @arg RTC_IT_WUT:  唤醒定时器中断掩码
  *          @arg RTC_IT_ALRB: 警报B中断掩码
  *          @arg RTC_IT_ALRA: 警报A中断掩码
  *          @arg RTC_IT_TAMP: 篡改事件中断掩码
  * 
  * 参数:  NewState: 指定的RTC中断的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 
  * 返回值: 无
  */
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_RTC_CONFIG_IT(RTC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 禁用RTC寄存器的写保护 */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    if (NewState != DISABLE) {
        /* 配置RTC_CR寄存器中的中断。 */
        RTC->CR |= (uint32_t)(RTC_IT & ~RTC_TAFCR_TAMPIE);
        /* 在RTC_TAFCR中配置防篡改中断 */
        RTC->TAFCR |= (uint32_t)(RTC_IT & RTC_TAFCR_TAMPIE);
    } else {
        /* 配置RTC_CR寄存器中的中断。 */
        RTC->CR &= (uint32_t)~(RTC_IT & (uint32_t)~RTC_TAFCR_TAMPIE);
        /* 在RTC_TAFCR中配置防篡改中断 */
        RTC->TAFCR &= (uint32_t)~(RTC_IT & RTC_TAFCR_TAMPIE);
    }

    /* 启用对RTC寄存器的写保护 */
    RTC->WPR = 0xFF;
}

/**
  * 简介:  检查是否设置了指定的 RTC 标志。
  * 
  * 参数:  RTC_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg RTC_FLAG_RECALPF: RECALPF事件标志。
  *            @arg RTC_FLAG_TAMP1F:  篡改1事件标志
  *            @arg RTC_FLAG_TAMP2F:  篡改2事件标志
  *            @arg RTC_FLAG_TSOVF:   时间戳溢出标志
  *            @arg RTC_FLAG_TSF:     时间戳事件标志
  *            @arg RTC_FLAG_WUTF:    唤醒定时器标志
  *            @arg RTC_FLAG_ALRBF:   报警B标志
  *            @arg RTC_FLAG_ALRAF:   警报A标志
  *            @arg RTC_FLAG_INITF:   初始化模式标志
  *            @arg RTC_FLAG_RSF:     寄存器同步标志
  *            @arg RTC_FLAG_INITS:   寄存器已配置标志
  *            @arg RTC_FLAG_SHPF:    移位操作等待标志。
  *            @arg RTC_FLAG_WUTWF:   唤醒定时器写入标志
  *            @arg RTC_FLAG_ALRBWF:  警报B写入标志
  *            @arg RTC_FLAG_ALRAWF:  警报A写入标志
  * 
  * 返回值: RTC_FLAG的新状态(SET或RESET)。
  */
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG) {
    FlagStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_RTC_GET_FLAG(RTC_FLAG));

    /* 获得所有的标志 */
    tmpreg = (uint32_t)(RTC->ISR & RTC_FLAGS_MASK);

    /* 返回该标志的状态 */
    if ((tmpreg & RTC_FLAG) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 RTC 的挂起标志。
  * 
  * 参数:  RTC_FLAG: 指定要清除的RTC标志。
  *          此参数可以是以下值的任意组合:
  *            @arg RTC_FLAG_TAMP1F: 篡改1事件标志
  *            @arg RTC_FLAG_TAMP2F: 篡改2事件标志
  *            @arg RTC_FLAG_TSOVF:  时间戳溢出标志
  *            @arg RTC_FLAG_TSF:    时间戳事件标志
  *            @arg RTC_FLAG_WUTF:   唤醒定时器标志
  *            @arg RTC_FLAG_ALRBF:  报警B标志
  *            @arg RTC_FLAG_ALRAF:  警报A标志
  *            @arg RTC_FLAG_RSF:    寄存器同步标志
  * 
  * 返回值: 无
  */
void RTC_ClearFlag(uint32_t RTC_FLAG) {
    /* 检查参数 */
    assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));

    /* 清除 Flags in the RTC_ISR 寄存器 */
    RTC->ISR = (uint32_t)((uint32_t)(~((RTC_FLAG | RTC_ISR_INIT) & 0x0000FFFF) | (uint32_t)(RTC->ISR & RTC_ISR_INIT)));
}

/**
  * 简介:  检查指定的 RTC 中断是否发生。
  * 
  * 参数:  RTC_IT: 指定要检查的RTC中断源。
  *          此参数可以是以下值之一:
  *            @arg RTC_IT_TS:    时间戳中断
  *            @arg RTC_IT_WUT:   唤醒定时器中断
  *            @arg RTC_IT_ALRB:  警报B中断
  *            @arg RTC_IT_ALRA:  警报A中断
  *            @arg RTC_IT_TAMP1: Tamper 1事件中断
  *            @arg RTC_IT_TAMP2: 破坏者2事件中断
  * 
  * 返回值: RTC_IT的新状态(SET或RESET)。
  */
ITStatus RTC_GetITStatus(uint32_t RTC_IT) {
    ITStatus bitstatus = RESET;
    uint32_t tmpreg = 0, enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_RTC_GET_IT(RTC_IT));

    /* 获取TAMPER Interrupt enable bit and pending 位 */
    tmpreg = (uint32_t)(RTC->TAFCR & (RTC_TAFCR_TAMPIE));

    /* 获取Interrupt enable 状态 */
    enablestatus = (uint32_t)((RTC->CR & RTC_IT) | (tmpreg & (RTC_IT >> 15)) | (tmpreg & (RTC_IT >> 16)));

    /* 获取Interrupt pending 位 */
    tmpreg = (uint32_t)((RTC->ISR & (uint32_t)(RTC_IT >> 4)));

    /* 获取status of the 中断 */
    if ((enablestatus != (uint32_t)RESET) && ((tmpreg & 0x0000FFFF) != (uint32_t)RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 RTC 的中断挂起位。
  * 
  * 参数:  RTC_IT: 指定要清除的RTC中断等待位。
  *          此参数可以是以下值的任意组合:
  *            @arg RTC_IT_TS: 时间戳中断
  *            @arg RTC_IT_WUT: 唤醒定时器中断
  *            @arg RTC_IT_ALRB: 警报B中断
  *            @arg RTC_IT_ALRA: 警报A中断
  *            @arg RTC_IT_TAMP1: Tamper 1事件中断
  *            @arg RTC_IT_TAMP2: 破坏者2事件中断
  * 
  * 返回值: 无
  */
void RTC_ClearITPendingBit(uint32_t RTC_IT) {
    uint32_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_RTC_CLEAR_IT(RTC_IT));

    /* 获取RTC_ISR Interrupt pending bits mask */
    tmpreg = (uint32_t)(RTC_IT >> 4);

    /* 清除 interrupt pending bits in the RTC_ISR 寄存器 */
    RTC->ISR = (uint32_t)((uint32_t)(~((tmpreg | RTC_ISR_INIT) & 0x0000FFFF) | (uint32_t)(RTC->ISR & RTC_ISR_INIT)));
}

/**
  * @}
  */

/**
  * 简介:  将一个2位数的小数转换为BCD格式。
  * 
  * 参数:  Value: 要转换的字节。
  * 
  * 返回值: 转换后的字节
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value) {
    uint8_t bcdhigh = 0;

    while (Value >= 10) {
        bcdhigh++;
        Value -= 10;
    }

    return  ((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * 简介:  从2位BCD转换为二进制。
  * 
  * 参数:  Value: 要转换的BCD值。
  * 
  * 返回值: 转换的字
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value) {
    uint8_t tmp = 0;
    tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (Value & (uint8_t)0x0F));
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
