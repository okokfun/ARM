/**
  ******************************************************************************
  * 文件:    stm32f4xx_rtc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 RTC 固件库的所有功能原型.
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
#ifndef __STM32F4xx_RTC_H
#define __STM32F4xx_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  RTC Init 结构定义
  */
typedef struct {
    uint32_t RTC_HourFormat;   /*!< 指定 RTC 小时格式。
                              该参数可以是@ref RTC_Hour_Formats 的值 */

    uint32_t RTC_AsynchPrediv; /*!< 指定 RTC 异步预分频器值。
                              此参数必须设置为低于 0x7F 的值 */

    uint32_t RTC_SynchPrediv;  /*!< 指定 RTC 同步预分频器值。
                              此参数必须设置为小于 0x7FFF 的值 */
} RTC_InitTypeDef;

/**
  * 简介:  RTC 时间结构定义
  */
typedef struct {
    uint8_t RTC_Hours;    /*!< 指定 RTC 时间小时。
                         如果选择 RTC_HourFormat_12，则该参数必须设置为 0-12 范围内的值;
						 如果选择 RTC_HourFormat_24，则该参数必须设置为 0-23 范围内的值。 */

    uint8_t RTC_Minutes;  /*!< 指定 RTC 时间分钟。
                         此参数必须设置为 0-59 范围内的值。 */

    uint8_t RTC_Seconds;  /*!< 指定 RTC 时间秒数。
                         此参数必须设置为 0-59 范围内的值。 */

    uint8_t RTC_H12;      /*!< 指定 RTC AM/PM 时间.
                        此参数可以是@ref RTC_AM_PM_Definitions 的值 */
} RTC_TimeTypeDef;

/**
  * 简介:  RTC日期结构定义
  */
typedef struct {
    uint8_t RTC_WeekDay; /*!< 指定 RTC 日期 WeekDay。
                         此参数可以是 @ref RTC_WeekDay_Definitions 的值 */

    uint8_t RTC_Month;   /*!< 指定 RTC 日期月份(BCD 格式)。
                         此参数可以是 @ref RTC_Month_Date_Definitions 的值 */

    uint8_t RTC_Date;     /*!< 指定 RTC 日期。
                         此参数必须设置为 1-31 范围内的值。 */

    uint8_t RTC_Year;     /*!< 指定 RTC 日期年份。
                         此参数必须设置为 0-99 范围内的值。 */
} RTC_DateTypeDef;

/**
  * 简介:  RTC 告警结构定义
  */
typedef struct {
    RTC_TimeTypeDef RTC_AlarmTime;     /*!< 指定 RTC 警报时间成员。 */

    uint32_t RTC_AlarmMask;            /*!< 指定 RTC 警报掩码。
                                      该参数可以是@ref RTC_AlarmMask_Definitions 的值 */

    uint32_t RTC_AlarmDateWeekDaySel;  /*!< 指定 RTC 警报在日期或工作日。
                                      此参数可以是 @ref RTC_AlarmDateWeekDay_Definitions 的值 */

    uint8_t RTC_AlarmDateWeekDay;      /*!< 指定 RTC 警报日期/工作日。
                                      如果选择了报警日期，则该参数必须设置为 1-31 范围内的值。
                                      如果选择了 Alarm WeekDay，则此参数可以是 @ref RTC_WeekDay_Definitions 的值 */
} RTC_AlarmTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Exported_Constants
  * @{
  */


/** @defgroup RTC_Hour_Formats
  * @{
  */
#define RTC_HourFormat_24              ((uint32_t)0x00000000)
#define RTC_HourFormat_12              ((uint32_t)0x00000040)
#define IS_RTC_HOUR_FORMAT(FORMAT)     (((FORMAT) == RTC_HourFormat_12) || \
                                        ((FORMAT) == RTC_HourFormat_24))
/**
  * @}
  */

/** @defgroup RTC_Asynchronous_Predivider
  * @{
  */
#define IS_RTC_ASYNCH_PREDIV(PREDIV)   ((PREDIV) <= 0x7F)

/**
  * @}
  */


/** @defgroup RTC_Synchronous_Predivider
  * @{
  */
#define IS_RTC_SYNCH_PREDIV(PREDIV)    ((PREDIV) <= 0x7FFF)

/**
  * @}
  */

/** @defgroup RTC_Time_Definitions
  * @{
  */
#define IS_RTC_HOUR12(HOUR)            (((HOUR) > 0) && ((HOUR) <= 12))
#define IS_RTC_HOUR24(HOUR)            ((HOUR) <= 23)
#define IS_RTC_MINUTES(MINUTES)        ((MINUTES) <= 59)
#define IS_RTC_SECONDS(SECONDS)        ((SECONDS) <= 59)

/**
  * @}
  */

/** @defgroup RTC_AM_PM_Definitions
  * @{
  */
#define RTC_H12_AM                     ((uint8_t)0x00)
#define RTC_H12_PM                     ((uint8_t)0x40)
#define IS_RTC_H12(PM) (((PM) == RTC_H12_AM) || ((PM) == RTC_H12_PM))

/**
  * @}
  */

/** @defgroup RTC_Year_Date_Definitions
  * @{
  */
#define IS_RTC_YEAR(YEAR)              ((YEAR) <= 99)

/**
  * @}
  */

/** @defgroup RTC_Month_Date_Definitions
  * @{
  */

/* Coded in BCD format */
#define RTC_Month_January              ((uint8_t)0x01)
#define RTC_Month_February             ((uint8_t)0x02)
#define RTC_Month_March                ((uint8_t)0x03)
#define RTC_Month_April                ((uint8_t)0x04)
#define RTC_Month_May                  ((uint8_t)0x05)
#define RTC_Month_June                 ((uint8_t)0x06)
#define RTC_Month_July                 ((uint8_t)0x07)
#define RTC_Month_August               ((uint8_t)0x08)
#define RTC_Month_September            ((uint8_t)0x09)
#define RTC_Month_October              ((uint8_t)0x10)
#define RTC_Month_November             ((uint8_t)0x11)
#define RTC_Month_December             ((uint8_t)0x12)
#define IS_RTC_MONTH(MONTH)            (((MONTH) >= 1) && ((MONTH) <= 12))
#define IS_RTC_DATE(DATE)              (((DATE) >= 1) && ((DATE) <= 31))

/**
  * @}
  */

/** @defgroup RTC_WeekDay_Definitions
  * @{
  */
#define RTC_Weekday_Monday             ((uint8_t)0x01)
#define RTC_Weekday_Tuesday            ((uint8_t)0x02)
#define RTC_Weekday_Wednesday          ((uint8_t)0x03)
#define RTC_Weekday_Thursday           ((uint8_t)0x04)
#define RTC_Weekday_Friday             ((uint8_t)0x05)
#define RTC_Weekday_Saturday           ((uint8_t)0x06)
#define RTC_Weekday_Sunday             ((uint8_t)0x07)
#define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday) || \
                                 ((WEEKDAY) == RTC_Weekday_Tuesday) || \
                                 ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                 ((WEEKDAY) == RTC_Weekday_Thursday) || \
                                 ((WEEKDAY) == RTC_Weekday_Friday) || \
                                 ((WEEKDAY) == RTC_Weekday_Saturday) || \
                                 ((WEEKDAY) == RTC_Weekday_Sunday))
/**
  * @}
  */


/** @defgroup RTC_Alarm_Definitions
  * @{
  */
#define IS_RTC_ALARM_DATE_WEEKDAY_DATE(DATE) (((DATE) > 0) && ((DATE) <= 31))
#define IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_Weekday_Monday) || \
        ((WEEKDAY) == RTC_Weekday_Tuesday) || \
        ((WEEKDAY) == RTC_Weekday_Wednesday) || \
        ((WEEKDAY) == RTC_Weekday_Thursday) || \
        ((WEEKDAY) == RTC_Weekday_Friday) || \
        ((WEEKDAY) == RTC_Weekday_Saturday) || \
        ((WEEKDAY) == RTC_Weekday_Sunday))

/**
  * @}
  */


/** @defgroup RTC_AlarmDateWeekDay_Definitions
  * @{
  */
#define RTC_AlarmDateWeekDaySel_Date      ((uint32_t)0x00000000)
#define RTC_AlarmDateWeekDaySel_WeekDay   ((uint32_t)0x40000000)

#define IS_RTC_ALARM_DATE_WEEKDAY_SEL(SEL) (((SEL) == RTC_AlarmDateWeekDaySel_Date) || \
        ((SEL) == RTC_AlarmDateWeekDaySel_WeekDay))

/**
  * @}
  */


/** @defgroup RTC_AlarmMask_Definitions
  * @{
  */
#define RTC_AlarmMask_None                ((uint32_t)0x00000000)
#define RTC_AlarmMask_DateWeekDay         ((uint32_t)0x80000000)
#define RTC_AlarmMask_Hours               ((uint32_t)0x00800000)
#define RTC_AlarmMask_Minutes             ((uint32_t)0x00008000)
#define RTC_AlarmMask_Seconds             ((uint32_t)0x00000080)
#define RTC_AlarmMask_All                 ((uint32_t)0x80808080)
#define IS_ALARM_MASK(MASK)  (((MASK) & 0x7F7F7F7F) == (uint32_t)RESET)

/**
  * @}
  */

/** @defgroup RTC_Alarms_Definitions
  * @{
  */
#define RTC_Alarm_A                       ((uint32_t)0x00000100)
#define RTC_Alarm_B                       ((uint32_t)0x00000200)
#define IS_RTC_ALARM(ALARM)     (((ALARM) == RTC_Alarm_A) || ((ALARM) == RTC_Alarm_B))
#define IS_RTC_CMD_ALARM(ALARM) (((ALARM) & (RTC_Alarm_A | RTC_Alarm_B)) != (uint32_t)RESET)

/**
  * @}
  */

/** @defgroup RTC_Alarm_Sub_Seconds_Masks_Definitions
* @{
*/
#define RTC_AlarmSubSecondMask_All         ((uint32_t)0x00000000) /*!< 所有警报 SS 字段都被屏蔽。
                                                                        警报没有亚秒比较 */
#define RTC_AlarmSubSecondMask_SS14_1      ((uint32_t)0x01000000) /*!< SS[14:1] 在报警比较中是不关心的。 仅比较 SS[0]。 */
#define RTC_AlarmSubSecondMask_SS14_2      ((uint32_t)0x02000000) /*!< SS[14:2] 在报警比较中是不关心的。 仅比较 SS[1:0] */
#define RTC_AlarmSubSecondMask_SS14_3      ((uint32_t)0x03000000) /*!< SS[14:3] 在报警比较中是不关心的。 仅比较 SS[2:0] */
#define RTC_AlarmSubSecondMask_SS14_4      ((uint32_t)0x04000000) /*!< SS[14:4] 在报警比较中是不关心的。 仅比较 SS[3:0] */
#define RTC_AlarmSubSecondMask_SS14_5      ((uint32_t)0x05000000) /*!< SS[14:5] 在报警比较中是不关心的。 仅比较 SS[4:0] */
#define RTC_AlarmSubSecondMask_SS14_6      ((uint32_t)0x06000000) /*!< SS[14:6] 在报警比较中是不关心的。 仅比较 SS[5:0] */
#define RTC_AlarmSubSecondMask_SS14_7      ((uint32_t)0x07000000) /*!< SS[14:7] 在报警比较中是不关心的。 仅比较 SS[6:0] */
#define RTC_AlarmSubSecondMask_SS14_8      ((uint32_t)0x08000000) /*!< SS[14:8] 在报警比较中是不关心的。 仅比较 SS[7:0] */
#define RTC_AlarmSubSecondMask_SS14_9      ((uint32_t)0x09000000) /*!< SS[14:9] 在报警比较中是不关心的。 仅比较 SS[8:0] */
#define RTC_AlarmSubSecondMask_SS14_10     ((uint32_t)0x0A000000) /*!< SS[14:10] 在报警比较中是不关心的。 仅比较 SS[9:0] */
#define RTC_AlarmSubSecondMask_SS14_11     ((uint32_t)0x0B000000) /*!< SS[14:11] 在报警比较中是不关心的。 仅比较 SS[10:0] */
#define RTC_AlarmSubSecondMask_SS14_12     ((uint32_t)0x0C000000) /*!< SS[14:12] 在报警比较中是不关心的。仅比较 SS[11:0] */
#define RTC_AlarmSubSecondMask_SS14_13     ((uint32_t)0x0D000000) /*!< SS[14:13] 在报警比较中是不关心的。 仅比较 SS[12:0] */
#define RTC_AlarmSubSecondMask_SS14        ((uint32_t)0x0E000000) /*!< 报警比较中不关心 SS[14]。仅比较 SS[13:0] */
#define RTC_AlarmSubSecondMask_None        ((uint32_t)0x0F000000) /*!< SS[14:0] 被比较并且必须匹配以激活警报。 */
#define IS_RTC_ALARM_SUB_SECOND_MASK(MASK)   (((MASK) == RTC_AlarmSubSecondMask_All) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_1) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_2) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_3) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_4) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_5) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_6) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_7) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_8) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_9) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_10) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_11) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_12) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14_13) || \
        ((MASK) == RTC_AlarmSubSecondMask_SS14) || \
        ((MASK) == RTC_AlarmSubSecondMask_None))
/**
  * @}
  */

/** @defgroup RTC_Alarm_Sub_Seconds_Value
  * @{
  */
#define IS_RTC_ALARM_SUB_SECOND_VALUE(VALUE) ((VALUE) <= 0x00007FFF)

/**
  * @}
  */

/** @defgroup RTC_Wakeup_Timer_Definitions
  * @{
  */
#define RTC_WakeUpClock_RTCCLK_Div16        ((uint32_t)0x00000000)
#define RTC_WakeUpClock_RTCCLK_Div8         ((uint32_t)0x00000001)
#define RTC_WakeUpClock_RTCCLK_Div4         ((uint32_t)0x00000002)
#define RTC_WakeUpClock_RTCCLK_Div2         ((uint32_t)0x00000003)
#define RTC_WakeUpClock_CK_SPRE_16bits      ((uint32_t)0x00000004)
#define RTC_WakeUpClock_CK_SPRE_17bits      ((uint32_t)0x00000006)
#define IS_RTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == RTC_WakeUpClock_RTCCLK_Div16) || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div8) || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div4) || \
                                    ((CLOCK) == RTC_WakeUpClock_RTCCLK_Div2) || \
                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_16bits) || \
                                    ((CLOCK) == RTC_WakeUpClock_CK_SPRE_17bits))
#define IS_RTC_WAKEUP_COUNTER(COUNTER)  ((COUNTER) <= 0xFFFF)
/**
  * @}
  */

/** @defgroup RTC_Time_Stamp_Edges_definitions
  * @{
  */
#define RTC_TimeStampEdge_Rising          ((uint32_t)0x00000000)
#define RTC_TimeStampEdge_Falling         ((uint32_t)0x00000008)
#define IS_RTC_TIMESTAMP_EDGE(EDGE) (((EDGE) == RTC_TimeStampEdge_Rising) || \
                                     ((EDGE) == RTC_TimeStampEdge_Falling))
/**
  * @}
  */

/** @defgroup RTC_Output_selection_Definitions
  * @{
  */
#define RTC_Output_Disable             ((uint32_t)0x00000000)
#define RTC_Output_AlarmA              ((uint32_t)0x00200000)
#define RTC_Output_AlarmB              ((uint32_t)0x00400000)
#define RTC_Output_WakeUp              ((uint32_t)0x00600000)

#define IS_RTC_OUTPUT(OUTPUT) (((OUTPUT) == RTC_Output_Disable) || \
                               ((OUTPUT) == RTC_Output_AlarmA) || \
                               ((OUTPUT) == RTC_Output_AlarmB) || \
                               ((OUTPUT) == RTC_Output_WakeUp))

/**
  * @}
  */

/** @defgroup RTC_Output_Polarity_Definitions
  * @{
  */
#define RTC_OutputPolarity_High           ((uint32_t)0x00000000)
#define RTC_OutputPolarity_Low            ((uint32_t)0x00100000)
#define IS_RTC_OUTPUT_POL(POL) (((POL) == RTC_OutputPolarity_High) || \
                                ((POL) == RTC_OutputPolarity_Low))
/**
  * @}
  */


/** @defgroup RTC_Digital_Calibration_Definitions
  * @{
  */
#define RTC_CalibSign_Positive            ((uint32_t)0x00000000)
#define RTC_CalibSign_Negative            ((uint32_t)0x00000080)
#define IS_RTC_CALIB_SIGN(SIGN) (((SIGN) == RTC_CalibSign_Positive) || \
                                 ((SIGN) == RTC_CalibSign_Negative))
#define IS_RTC_CALIB_VALUE(VALUE) ((VALUE) < 0x20)

/**
  * @}
  */

/** @defgroup RTC_Calib_Output_selection_Definitions
 * @{
 */
#define RTC_CalibOutput_512Hz            ((uint32_t)0x00000000)
#define RTC_CalibOutput_1Hz              ((uint32_t)0x00080000)
#define IS_RTC_CALIB_OUTPUT(OUTPUT)  (((OUTPUT) == RTC_CalibOutput_512Hz) || \
                                      ((OUTPUT) == RTC_CalibOutput_1Hz))
/**
  * @}
  */

/** @defgroup RTC_Smooth_calib_period_Definitions
  * @{
  */
#define RTC_SmoothCalibPeriod_32sec   ((uint32_t)0x00000000) /*!<  如果 RTCCLK = 32768 Hz，平滑校准周期为 32s，否则为 2exp20 RTCCLK 秒 */
#define RTC_SmoothCalibPeriod_16sec   ((uint32_t)0x00002000) /*!<  如果 RTCCLK = 32768 Hz，平滑校准周期为 16 秒，否则为 2exp19 RTCCLK 秒 */
#define RTC_SmoothCalibPeriod_8sec    ((uint32_t)0x00004000) /*!<  如果 RTC CLK = 32768 Hz，平滑校准周期为 8s，否则为 2exp18 RTCCLK 秒 */
#define IS_RTC_SMOOTH_CALIB_PERIOD(PERIOD) (((PERIOD) == RTC_SmoothCalibPeriod_32sec) || \
        ((PERIOD) == RTC_SmoothCalibPeriod_16sec) || \
        ((PERIOD) == RTC_SmoothCalibPeriod_8sec))

/**
  * @}
  */

/** @defgroup RTC_Smooth_calib_Plus_pulses_Definitions
  * @{
  */
#define RTC_SmoothCalibPlusPulses_Set    ((uint32_t)0x00008000) /*!<  在 X 秒窗口期间添加的 RTCCLK 脉冲数 = Y - CALM[8:0]。 
																	  当 X = 32、16、8 时，Y = 512、256、128 */
#define RTC_SmoothCalibPlusPulses_Reset  ((uint32_t)0x00000000) /*!< 在 32 秒窗口内替换的 RTCCLK 脉冲数 = CALM[8:0]。*/
#define IS_RTC_SMOOTH_CALIB_PLUS(PLUS) (((PLUS) == RTC_SmoothCalibPlusPulses_Set) || \
                                        ((PLUS) == RTC_SmoothCalibPlusPulses_Reset))

/**
  * @}
  */

/** @defgroup RTC_Smooth_calib_Minus_pulses_Definitions
  * @{
  */
#define  IS_RTC_SMOOTH_CALIB_MINUS(VALUE) ((VALUE) <= 0x000001FF)

/**
  * @}
  */

/** @defgroup RTC_DayLightSaving_Definitions
  * @{
  */
#define RTC_DayLightSaving_SUB1H   ((uint32_t)0x00020000)
#define RTC_DayLightSaving_ADD1H   ((uint32_t)0x00010000)
#define IS_RTC_DAYLIGHT_SAVING(SAVE) (((SAVE) == RTC_DayLightSaving_SUB1H) || \
                                      ((SAVE) == RTC_DayLightSaving_ADD1H))

#define RTC_StoreOperation_Reset        ((uint32_t)0x00000000)
#define RTC_StoreOperation_Set          ((uint32_t)0x00040000)
#define IS_RTC_STORE_OPERATION(OPERATION) (((OPERATION) == RTC_StoreOperation_Reset) || \
        ((OPERATION) == RTC_StoreOperation_Set))
/**
  * @}
  */

/** @defgroup RTC_Tamper_Trigger_Definitions
  * @{
  */
#define RTC_TamperTrigger_RisingEdge            ((uint32_t)0x00000000)
#define RTC_TamperTrigger_FallingEdge           ((uint32_t)0x00000001)
#define RTC_TamperTrigger_LowLevel              ((uint32_t)0x00000000)
#define RTC_TamperTrigger_HighLevel             ((uint32_t)0x00000001)
#define IS_RTC_TAMPER_TRIGGER(TRIGGER) (((TRIGGER) == RTC_TamperTrigger_RisingEdge) || \
                                        ((TRIGGER) == RTC_TamperTrigger_FallingEdge) || \
                                        ((TRIGGER) == RTC_TamperTrigger_LowLevel) || \
                                        ((TRIGGER) == RTC_TamperTrigger_HighLevel))

/**
  * @}
  */

/** @defgroup RTC_Tamper_Filter_Definitions
  * @{
  */
#define RTC_TamperFilter_Disable   ((uint32_t)0x00000000) /*!< 篡改过滤器已禁用 */

#define RTC_TamperFilter_2Sample   ((uint32_t)0x00000800) /*!< 在活动级别连续 2 次采样后激活篡改 */
#define RTC_TamperFilter_4Sample   ((uint32_t)0x00001000) /*!< 在活动级别连续 4 次采样后激活篡改 */
#define RTC_TamperFilter_8Sample   ((uint32_t)0x00001800) /*!< 在活动级别连续 8 次采样后，篡改被激活。 */
#define IS_RTC_TAMPER_FILTER(FILTER) (((FILTER) == RTC_TamperFilter_Disable) || \
                                      ((FILTER) == RTC_TamperFilter_2Sample) || \
                                      ((FILTER) == RTC_TamperFilter_4Sample) || \
                                      ((FILTER) == RTC_TamperFilter_8Sample))
/**
  * @}
  */

/** @defgroup RTC_Tamper_Sampling_Frequencies_Definitions
  * @{
  */
#define RTC_TamperSamplingFreq_RTCCLK_Div32768  ((uint32_t)0x00000000) /*!< 每个篡改输入的采样频率 = RTCCLK / 32768 */
#define RTC_TamperSamplingFreq_RTCCLK_Div16384  ((uint32_t)0x000000100) /*!< 每个篡改输入的采样频率 = RTCCLK / 16384 */
#define RTC_TamperSamplingFreq_RTCCLK_Div8192   ((uint32_t)0x00000200) /*!< 每个篡改输入的采样频率 =  RTCCLK / 8192  */
#define RTC_TamperSamplingFreq_RTCCLK_Div4096   ((uint32_t)0x00000300) /*!< 每个篡改输入的采样频率 =  RTCCLK / 4096  */
#define RTC_TamperSamplingFreq_RTCCLK_Div2048   ((uint32_t)0x00000400) /*!< 每个篡改输入的采样频率 =  RTCCLK / 2048  */
#define RTC_TamperSamplingFreq_RTCCLK_Div1024   ((uint32_t)0x00000500) /*!< 每个篡改输入的采样频率 =  RTCCLK / 1024  */
#define RTC_TamperSamplingFreq_RTCCLK_Div512    ((uint32_t)0x00000600) /*!< 每个篡改输入的采样频率 =  RTCCLK / 512   */
#define RTC_TamperSamplingFreq_RTCCLK_Div256    ((uint32_t)0x00000700) /*!< 每个篡改输入的采样频率 =  RTCCLK / 256   */
#define IS_RTC_TAMPER_SAMPLING_FREQ(FREQ) (((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div32768) || \
        ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div16384) || \
        ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div8192) || \
        ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div4096) || \
        ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div2048) || \
        ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div1024) || \
        ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div512) || \
        ((FREQ) ==RTC_TamperSamplingFreq_RTCCLK_Div256))

/**
  * @}
  */

/** @defgroup RTC_Tamper_Pin_Precharge_Duration_Definitions
* @{
*/
#define RTC_TamperPrechargeDuration_1RTCCLK ((uint32_t)0x00000000)  /*!< 篡改引脚在 1 个 RTCCLK 周期内采样前预充电 */
#define RTC_TamperPrechargeDuration_2RTCCLK ((uint32_t)0x00002000)  /*!< 篡改引脚在 2 个 RTCCLK 周期内采样前预充电 */
#define RTC_TamperPrechargeDuration_4RTCCLK ((uint32_t)0x00004000)  /*!< 篡改引脚在 4 个 RTCCLK 周期内采样前预充电 */
#define RTC_TamperPrechargeDuration_8RTCCLK ((uint32_t)0x00006000)  /*!< 篡改引脚在 8 个 RTCCLK 周期内采样前预充电 */

#define IS_RTC_TAMPER_PRECHARGE_DURATION(DURATION) (((DURATION) == RTC_TamperPrechargeDuration_1RTCCLK) || \
        ((DURATION) == RTC_TamperPrechargeDuration_2RTCCLK) || \
        ((DURATION) == RTC_TamperPrechargeDuration_4RTCCLK) || \
        ((DURATION) == RTC_TamperPrechargeDuration_8RTCCLK))
/**
  * @}
  */

/** @defgroup RTC_Tamper_Pins_Definitions
  * @{
  */
#define RTC_Tamper_1 RTC_TAFCR_TAMP1E
#define RTC_Tamper_2 RTC_TAFCR_TAMP2E
#define IS_RTC_TAMPER(TAMPER) (((TAMPER) == RTC_Tamper_1) || ((TAMPER) == RTC_Tamper_2))

/**
  * @}
  */

/** @defgroup RTC_Tamper_Pin_Selection
  * @{
  */
#define RTC_TamperPin_Default       ((uint32_t)0x00000000)
#define RTC_TamperPin_Pos1          ((uint32_t)0x00010000)
#define IS_RTC_TAMPER_PIN(PIN)      (((PIN) == RTC_TamperPin_Default) || \
                                     ((PIN) == RTC_TamperPin_Pos1))
/* Legacy Defines */
#define RTC_TamperPin_PC13           RTC_TamperPin_Default
#define RTC_TamperPin_PI8            RTC_TamperPin_Pos1
/**
  * @}
  */

/** @defgroup RTC_TimeStamp_Pin_Selection
  * @{
  */
#define RTC_TimeStampPin_PC13              ((uint32_t)0x00000000)
#define RTC_TimeStampPin_PI8               ((uint32_t)0x00020000)
#define IS_RTC_TIMESTAMP_PIN(PIN) (((PIN) == RTC_TimeStampPin_PC13) || \
                                   ((PIN) == RTC_TimeStampPin_PI8))

/**
  * @}
  */

/** @defgroup RTC_Output_Type_ALARM_OUT
  * @{
  */
#define RTC_OutputType_OpenDrain           ((uint32_t)0x00000000)
#define RTC_OutputType_PushPull            ((uint32_t)0x00040000)
#define IS_RTC_OUTPUT_TYPE(TYPE) (((TYPE) == RTC_OutputType_OpenDrain) || \
                                  ((TYPE) == RTC_OutputType_PushPull))

/**
  * @}
  */

/** @defgroup RTC_Add_1_Second_Parameter_Definitions
  * @{
  */
#define RTC_ShiftAdd1S_Reset      ((uint32_t)0x00000000)
#define RTC_ShiftAdd1S_Set        ((uint32_t)0x80000000)
#define IS_RTC_SHIFT_ADD1S(SEL) (((SEL) == RTC_ShiftAdd1S_Reset) || \
                                 ((SEL) == RTC_ShiftAdd1S_Set))
/**
  * @}
  */

/** @defgroup RTC_Substract_Fraction_Of_Second_Value
  * @{
  */
#define IS_RTC_SHIFT_SUBFS(FS) ((FS) <= 0x00007FFF)

/**
  * @}
  */

/** @defgroup RTC_Backup_Registers_Definitions
  * @{
  */
#define RTC_BKP_DR0                       ((uint32_t)0x00000000)
#define RTC_BKP_DR1                       ((uint32_t)0x00000001)
#define RTC_BKP_DR2                       ((uint32_t)0x00000002)
#define RTC_BKP_DR3                       ((uint32_t)0x00000003)
#define RTC_BKP_DR4                       ((uint32_t)0x00000004)
#define RTC_BKP_DR5                       ((uint32_t)0x00000005)
#define RTC_BKP_DR6                       ((uint32_t)0x00000006)
#define RTC_BKP_DR7                       ((uint32_t)0x00000007)
#define RTC_BKP_DR8                       ((uint32_t)0x00000008)
#define RTC_BKP_DR9                       ((uint32_t)0x00000009)
#define RTC_BKP_DR10                      ((uint32_t)0x0000000A)
#define RTC_BKP_DR11                      ((uint32_t)0x0000000B)
#define RTC_BKP_DR12                      ((uint32_t)0x0000000C)
#define RTC_BKP_DR13                      ((uint32_t)0x0000000D)
#define RTC_BKP_DR14                      ((uint32_t)0x0000000E)
#define RTC_BKP_DR15                      ((uint32_t)0x0000000F)
#define RTC_BKP_DR16                      ((uint32_t)0x00000010)
#define RTC_BKP_DR17                      ((uint32_t)0x00000011)
#define RTC_BKP_DR18                      ((uint32_t)0x00000012)
#define RTC_BKP_DR19                      ((uint32_t)0x00000013)
#define IS_RTC_BKP(BKP)                   (((BKP) == RTC_BKP_DR0) || \
        ((BKP) == RTC_BKP_DR1) || \
        ((BKP) == RTC_BKP_DR2) || \
        ((BKP) == RTC_BKP_DR3) || \
        ((BKP) == RTC_BKP_DR4) || \
        ((BKP) == RTC_BKP_DR5) || \
        ((BKP) == RTC_BKP_DR6) || \
        ((BKP) == RTC_BKP_DR7) || \
        ((BKP) == RTC_BKP_DR8) || \
        ((BKP) == RTC_BKP_DR9) || \
        ((BKP) == RTC_BKP_DR10) || \
        ((BKP) == RTC_BKP_DR11) || \
        ((BKP) == RTC_BKP_DR12) || \
        ((BKP) == RTC_BKP_DR13) || \
        ((BKP) == RTC_BKP_DR14) || \
        ((BKP) == RTC_BKP_DR15) || \
        ((BKP) == RTC_BKP_DR16) || \
        ((BKP) == RTC_BKP_DR17) || \
        ((BKP) == RTC_BKP_DR18) || \
        ((BKP) == RTC_BKP_DR19))
/**
  * @}
  */

/** @defgroup RTC_Input_parameter_format_definitions
  * @{
  */
#define RTC_Format_BIN                    ((uint32_t)0x000000000)
#define RTC_Format_BCD                    ((uint32_t)0x000000001)
#define IS_RTC_FORMAT(FORMAT) (((FORMAT) == RTC_Format_BIN) || ((FORMAT) == RTC_Format_BCD))

/**
  * @}
  */

/** @defgroup RTC_Flags_Definitions
  * @{
  */
#define RTC_FLAG_RECALPF                  ((uint32_t)0x00010000)
#define RTC_FLAG_TAMP1F                   ((uint32_t)0x00002000)
#define RTC_FLAG_TAMP2F                   ((uint32_t)0x00004000)
#define RTC_FLAG_TSOVF                    ((uint32_t)0x00001000)
#define RTC_FLAG_TSF                      ((uint32_t)0x00000800)
#define RTC_FLAG_WUTF                     ((uint32_t)0x00000400)
#define RTC_FLAG_ALRBF                    ((uint32_t)0x00000200)
#define RTC_FLAG_ALRAF                    ((uint32_t)0x00000100)
#define RTC_FLAG_INITF                    ((uint32_t)0x00000040)
#define RTC_FLAG_RSF                      ((uint32_t)0x00000020)
#define RTC_FLAG_INITS                    ((uint32_t)0x00000010)
#define RTC_FLAG_SHPF                     ((uint32_t)0x00000008)
#define RTC_FLAG_WUTWF                    ((uint32_t)0x00000004)
#define RTC_FLAG_ALRBWF                   ((uint32_t)0x00000002)
#define RTC_FLAG_ALRAWF                   ((uint32_t)0x00000001)
#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_TSOVF) || ((FLAG) == RTC_FLAG_TSF) || \
                               ((FLAG) == RTC_FLAG_WUTF) || ((FLAG) == RTC_FLAG_ALRBF) || \
                               ((FLAG) == RTC_FLAG_ALRAF) || ((FLAG) == RTC_FLAG_INITF) || \
                               ((FLAG) == RTC_FLAG_RSF) || ((FLAG) == RTC_FLAG_WUTWF) || \
                               ((FLAG) == RTC_FLAG_ALRBWF) || ((FLAG) == RTC_FLAG_ALRAWF) || \
                               ((FLAG) == RTC_FLAG_TAMP1F) || ((FLAG) == RTC_FLAG_RECALPF) || \
                               ((FLAG) == RTC_FLAG_TAMP2F) ||((FLAG) == RTC_FLAG_SHPF))
#define IS_RTC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFF00DF) == (uint32_t)RESET))
/**
  * @}
  */

/** @defgroup RTC_Interrupts_Definitions
  * @{
  */
#define RTC_IT_TS                         ((uint32_t)0x00008000)
#define RTC_IT_WUT                        ((uint32_t)0x00004000)
#define RTC_IT_ALRB                       ((uint32_t)0x00002000)
#define RTC_IT_ALRA                       ((uint32_t)0x00001000)
#define RTC_IT_TAMP                       ((uint32_t)0x00000004) /* Used only to Enable the Tamper 中断 */
#define RTC_IT_TAMP1                      ((uint32_t)0x00020000)
#define RTC_IT_TAMP2                      ((uint32_t)0x00040000)

#define IS_RTC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFF0FFB) == (uint32_t)RESET))
#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_TS) || ((IT) == RTC_IT_WUT) || \
                           ((IT) == RTC_IT_ALRB) || ((IT) == RTC_IT_ALRA) || \
                           ((IT) == RTC_IT_TAMP1) || ((IT) == RTC_IT_TAMP2))
#define IS_RTC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFF90FFF) == (uint32_t)RESET))

/**
  * @}
  */

/** @defgroup RTC_Legacy
  * @{
  */
#define RTC_DigitalCalibConfig  RTC_CoarseCalibConfig
#define RTC_DigitalCalibCmd     RTC_CoarseCalibCmd

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将RTC配置设置为默认复位状态的函数 *****/
ErrorStatus RTC_DeInit(void); // 将 RTC 寄存器去初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct); // 根据RTC_InitStruct中指定的参数初始化 RTC 寄存器。
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct); // 用其默认值填充每个RTC_InitStruct成员。
void RTC_WriteProtectionCmd(FunctionalState NewState); // 启用或禁用 RTC 寄存器写保护。
ErrorStatus RTC_EnterInitMode(void); // 进入 RTC 初始化模式。
void RTC_ExitInitMode(void); // 退出 RTC 初始化模式。
ErrorStatus RTC_WaitForSynchro(void); // 等到 RTC 时间和日期寄存器(RTC_TR和RTC_DR)与 RTC APB 时钟同步。
ErrorStatus RTC_RefClockCmd(FunctionalState NewState); // 启用或禁用 RTC 参考时钟检测。
void RTC_BypassShadowCmd(FunctionalState NewState); // 启用或禁用"绕过阴影"功能。

/* 时间和日期配置功能 **************************************/
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct); // 设置 RTC 当前时间。
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct); // 用默认值填充每个RTC_TimeStruct成员(时间 = 00h:00min:00sec)。
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct); // 获取 RTC 当前时间。
uint32_t RTC_GetSubSecond(void); //获取 RTC 当前日历子秒值。
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct); //设置 RTC 当前日期。
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct); //用默认值填充每个RTC_DateStruct成员(星期一，一月 01 xx00)。
void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct); // 获取 RTC 当前日期。

/* 报警(报警A和报警B)配置功能  */
void RTC_SetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct); //设置指定的 RTC 警报。
void RTC_AlarmStructInit(RTC_AlarmTypeDef* RTC_AlarmStruct); // 用默认值填充每个RTC_AlarmStruct成员(时间 = 00h:00mn:00sec / 日期 = 该月的第一天/掩码 = 所有字段都被屏蔽)。
void RTC_GetAlarm(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmTypeDef* RTC_AlarmStruct); //获取 RTC 警报值和掩码。
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState); //启用或禁用指定的 RTC 警报。
void RTC_AlarmSubSecondConfig(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask); // 配置 RTC 警报A/B 子秒值和掩码。
uint32_t RTC_GetAlarmSubSecond(uint32_t RTC_Alarm); // 获取 RTC 警报子秒值。

/* 唤醒定时器配置功能 */
void RTC_WakeUpClockConfig(uint32_t RTC_WakeUpClock); // 配置 RTC 唤醒时钟源。
void RTC_SetWakeUpCounter(uint32_t RTC_WakeUpCounter); // 配置 RTC 唤醒计数器。
uint32_t RTC_GetWakeUpCounter(void); // 返回 RTC 唤醒计时器计数器值。
ErrorStatus RTC_WakeUpCmd(FunctionalState NewState); // 启用或禁用 RTC 唤醒计时器。

/* 夏令时配置功能 ************************************/
void RTC_DayLightSavingConfig(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation); // 从当前时间相加或减去一小时。
uint32_t RTC_GetStoreOperation(void); // 返回RTC日间节能存储操作。

/* 输出引脚配置功能 ******************************************/
void RTC_OutputConfig(uint32_t RTC_Output, uint32_t RTC_OutputPolarity); // 配置 RTC 输出源 (AFO_ALARM)。

/* 数字校准配置功能 *********************************/
ErrorStatus RTC_CoarseCalibConfig(uint32_t RTC_CalibSign, uint32_t Value); // 配置粗略校准参数。
ErrorStatus RTC_CoarseCalibCmd(FunctionalState NewState); // 启用或禁用粗校准过程。
void RTC_CalibOutputCmd(FunctionalState NewState); // 使能或禁用通过相对引脚输出的RTC时钟。
void RTC_CalibOutputConfig(uint32_t RTC_CalibOutput); // 配置校准引脚排列(RTC_CALIB)选择(1Hz 或 512Hz)。
ErrorStatus RTC_SmoothCalibConfig(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue); // 配置平滑校准设置。

/* TimeStamp 配置功能 */
void RTC_TimeStampCmd(uint32_t RTC_TimeStampEdge, FunctionalState NewState); // 启用或禁用具有指定时间戳引脚激励边沿的 RTC 时间戳功能。
void RTC_GetTimeStamp(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_StampTimeStruct,
                      RTC_DateTypeDef* RTC_StampDateStruct); // 获取 RTC 时间戳值和掩码。
uint32_t RTC_GetTimeStampSubSecond(void); //获取 RTC 时间戳子秒值。

/* 篡改配置功能 */
void RTC_TamperTriggerConfig(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger); // 配置选择篡改引脚边缘。
void RTC_TamperCmd(uint32_t RTC_Tamper, FunctionalState NewState); // 启用或禁用篡改检测。
void RTC_TamperFilterConfig(uint32_t RTC_TamperFilter); // 配置篡改筛选器。
void RTC_TamperSamplingFreqConfig(uint32_t RTC_TamperSamplingFreq); // 配置篡改采样频率。
void RTC_TamperPinsPrechargeDuration(uint32_t RTC_TamperPrechargeDuration); // 配置篡改引脚输入预充电持续时间。
void RTC_TimeStampOnTamperDetectionCmd(FunctionalState NewState); // 启用或禁用篡改检测事件的时间戳。
void RTC_TamperPullUpCmd(FunctionalState NewState); // 启用或禁用篡改引脚的预充电。

/* 备份数据寄存器配置功能 */
void RTC_WriteBackupRegister(uint32_t RTC_BKP_DR, uint32_t Data); // 在指定的 RTC 备份数据寄存器中写入数据。
uint32_t RTC_ReadBackupRegister(uint32_t RTC_BKP_DR); // 从指定的 RTC 备份数据寄存器读取数据。

/* RTC Tamper and TimeStamp Pins Selection and Output Type Config configuration
   functions */
void RTC_TamperPinSelection(uint32_t RTC_TamperPin); // 选择 RTC 篡改引脚。
void RTC_TimeStampPinSelection(uint32_t RTC_TimeStampPin); // 选择 RTC 时间戳引脚。
void RTC_OutputTypeConfig(uint32_t RTC_OutputType); // 配置 RTC 输出引脚模式。

/* RTC_Shift_control_synchonisation_functions *********************************/
ErrorStatus RTC_SynchroShiftConfig(uint32_t RTC_ShiftAdd1S, uint32_t RTC_ShiftSubFS); // 配置同步切换控制设置。

/* 中断和标记管理功能 **********************************/
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState); // 启用或禁用指定的 RTC 中断。
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG); // 检查是否设置了指定的 RTC 标志。
void RTC_ClearFlag(uint32_t RTC_FLAG); // 清除 RTC 的挂起标志。
ITStatus RTC_GetITStatus(uint32_t RTC_IT); // 检查指定的 RTC 中断是否发生。
void RTC_ClearITPendingBit(uint32_t RTC_IT); // 清除 RTC 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_RTC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
