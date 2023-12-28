/**
  ******************************************************************************
  * 文件:    stm32f4xx_cec.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 CEC 固件库的所有功能原型，仅适用于 STM32F466xx 器件.
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
#ifndef __STM32F4XX_CEC_H
#define __STM32F4XX_CEC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup CEC
  * @{
  */
#if defined(STM32F446xx)
/* Exported types ------------------------------------------------------------*/

/**
  * 简介: CEC Init structure definition
  */
typedef struct {
    uint32_t CEC_SignalFreeTime;     /*!< 指定 CEC 信号空闲时间配置。
								   该参数可以是@ref CEC_Signal_Free_Time 的值 */
    uint32_t CEC_RxTolerance;        /*!< 指定 CEC 接收容差。
								   此参数可以是 @ref CEC_RxTolerance 的值 */
    uint32_t CEC_StopReception;      /*!< 指定 CEC 停止接收。
								   该参数可以是@ref CEC_Stop_Reception 的值 */
    uint32_t CEC_BitRisingError;     /*!< 指定 CEC 位上升错误生成。
								   该参数可以是@ref CEC_Bit_Rising_Error_Generation 的值 */
    uint32_t CEC_LongBitPeriodError; /*!< 指定 CEC 长位错误生成。
								   该参数可以是@ref CEC_Long_Bit_Error_Generation 的值 */
    uint32_t CEC_BRDNoGen;           /*!< 指定 CEC 广播错误生成。
								   该参数可以是@ref CEC_BDR_No_Gen 的值 */
    uint32_t CEC_SFTOption;          /*!< 指定 CEC 信号空闲时间选项。
								   该参数可以是@ref CEC_SFT_Option 的值 */

} CEC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup CEC_Exported_Constants
  * @{
  */

/** @defgroup CEC_Signal_Free_Time
  * @{
  */
#define CEC_SignalFreeTime_Standard     ((uint32_t)0x00000000) /*!< CEC  信号空闲时间标准         */
#define CEC_SignalFreeTime_1T           ((uint32_t)0x00000001) /*!< CEC  1.5 标称数据位周期     */
#define CEC_SignalFreeTime_2T           ((uint32_t)0x00000002) /*!< CEC  2.5 标称数据位周期     */
#define CEC_SignalFreeTime_3T           ((uint32_t)0x00000003) /*!< CEC  3.5 标称数据位周期     */
#define CEC_SignalFreeTime_4T           ((uint32_t)0x00000004) /*!< CEC  4.5 标称数据位周期     */
#define CEC_SignalFreeTime_5T           ((uint32_t)0x00000005) /*!< CEC  5.5 标称数据位周期     */
#define CEC_SignalFreeTime_6T           ((uint32_t)0x00000006) /*!< CEC  6.5 标称数据位周期     */
#define CEC_SignalFreeTime_7T           ((uint32_t)0x00000007) /*!< CEC  7.5 标称数据位周期     */
#define IS_CEC_SIGNAL_FREE_TIME(TIME) (((TIME) == CEC_SignalFreeTime_Standard) || \
                                       ((TIME) == CEC_SignalFreeTime_1T)|| \
                                       ((TIME) == CEC_SignalFreeTime_2T)|| \
                                       ((TIME) == CEC_SignalFreeTime_3T)|| \
                                       ((TIME) == CEC_SignalFreeTime_4T)|| \
                                       ((TIME) == CEC_SignalFreeTime_5T)|| \
                                       ((TIME) == CEC_SignalFreeTime_6T)|| \
                                       ((TIME) == CEC_SignalFreeTime_7T))
/**
  * @}
  */

/** @defgroup CEC_RxTolerance
  * @{
  */
#define CEC_RxTolerance_Standard        ((uint32_t)0x00000000) /*!< 标准容差            */
#define CEC_RxTolerance_Extended        CEC_CFGR_RXTOL         /*!< 扩展容差范围            */
#define IS_CEC_RX_TOLERANCE(TOLERANCE) (((TOLERANCE) == CEC_RxTolerance_Standard) || \
                                        ((TOLERANCE) == CEC_RxTolerance_Extended))
/**
  * @}
  */

/** @defgroup CEC_Stop_Reception
  * @{
  */
#define CEC_StopReception_Off           ((uint32_t)0x00000000) /*!< 位上升错误 (BRE) 时无 RX 停止 */
#define CEC_StopReception_On            CEC_CFGR_BRESTP        /*!< RX 停止位上升错误 (BRE)   */
#define IS_CEC_STOP_RECEPTION(RECEPTION) (((RECEPTION) == CEC_StopReception_On) || \
        ((RECEPTION) == CEC_StopReception_Off))
/**
  * @}
  */

/** @defgroup CEC_Bit_Rising_Error_Generation
  * @{
  */
#define CEC_BitRisingError_Off          ((uint32_t)0x00000000) /*!< 位上升错误生成已关闭 */
#define CEC_BitRisingError_On           CEC_CFGR_BREGEN        /*!< 位上升错误生成开启  */
#define IS_CEC_BIT_RISING_ERROR(ERROR) (((ERROR) == CEC_BitRisingError_Off) || \
                                        ((ERROR) == CEC_BitRisingError_On))
/**
  * @}
  */

/** @defgroup CEC_Long_Bit_Error_Generation
  * @{
  */
#define CEC_LongBitPeriodError_Off      ((uint32_t)0x00000000)  /*!< 长位周期错误生成已关闭 */
#define CEC_LongBitPeriodError_On       CEC_CFGR_LREGEN         /*!< 长位周期错误生成开启  */
#define IS_CEC_LONG_BIT_PERIOD_ERROR(ERROR) (((ERROR) == CEC_LongBitPeriodError_Off) || \
        ((ERROR) == CEC_LongBitPeriodError_On))
/**
  * @}
  */

/** @defgroup CEC_BDR_No_Gen
  * @{
  */
#define CEC_BRDNoGen_Off      ((uint32_t)0x00000000)  /*!< 广播位上升错误生成已关闭 */
#define CEC_BRDNoGen_On       CEC_CFGR_BRDNOGEN       /*!< 广播比特上升错误生成开启  */
#define IS_CEC_BDR_NO_GEN_ERROR(ERROR) (((ERROR) == CEC_BRDNoGen_Off) || \
                                        ((ERROR) == CEC_BRDNoGen_On))
/**
  * @}
  */

/** @defgroup CEC_SFT_Option
  * @{
  */
#define CEC_SFTOption_Off              ((uint32_t)0x00000000)  /*!< SFT 选项已关闭                   */
#define CEC_SFTOption_On               CEC_CFGR_SFTOPT         /*!< SFT 选项打开                    */
#define IS_CEC_SFT_OPTION(OPTION) (((OPTION) == CEC_SFTOption_Off) || \
                                   ((OPTION) == CEC_SFTOption_On))
/**
  * @}
  */

/** @defgroup CEC_Own_Address
  * @{
  */
#define IS_CEC_ADDRESS(ADDRESS)         ((ADDRESS) < 0x10)

/**
  * @}
  */

/** @defgroup CEC_Interrupt_Configuration_definition
  * @{
  */
#define CEC_IT_TXACKE                   CEC_IER_TXACKEIE
#define CEC_IT_TXERR                    CEC_IER_TXERRIE
#define CEC_IT_TXUDR                    CEC_IER_TXUDRIE
#define CEC_IT_TXEND                    CEC_IER_TXENDIE
#define CEC_IT_TXBR                     CEC_IER_TXBRIE
#define CEC_IT_ARBLST                   CEC_IER_ARBLSTIE
#define CEC_IT_RXACKE                   CEC_IER_RXACKEIE
#define CEC_IT_LBPE                     CEC_IER_LBPEIE
#define CEC_IT_SBPE                     CEC_IER_SBPEIE
#define CEC_IT_BRE                      CEC_IER_BREIEIE
#define CEC_IT_RXOVR                    CEC_IER_RXOVRIE
#define CEC_IT_RXEND                    CEC_IER_RXENDIE
#define CEC_IT_RXBR                     CEC_IER_RXBRIE

#define IS_CEC_IT(IT) ((((IT) & (uint32_t)0xFFFFE000) == 0x00) && ((IT) != 0x00))

#define IS_CEC_GET_IT(IT) (((IT) == CEC_IT_TXACKE) || \
                           ((IT) == CEC_IT_TXERR)|| \
                           ((IT) == CEC_IT_TXUDR)|| \
                           ((IT) == CEC_IT_TXEND)|| \
                           ((IT) == CEC_IT_TXBR)|| \
                           ((IT) == CEC_IT_ARBLST)|| \
                           ((IT) == CEC_IT_RXACKE)|| \
                           ((IT) == CEC_IT_LBPE)|| \
                           ((IT) == CEC_IT_SBPE)|| \
                           ((IT) == CEC_IT_BRE)|| \
                           ((IT) == CEC_IT_RXOVR)|| \
                           ((IT) == CEC_IT_RXEND)|| \
                           ((IT) == CEC_IT_RXBR))
/**
  * @}
  */

/** @defgroup CEC_ISR_register_flags_definition
  * @{
  */
#define CEC_FLAG_TXACKE                 CEC_ISR_TXACKE
#define CEC_FLAG_TXERR                  CEC_ISR_TXERR
#define CEC_FLAG_TXUDR                  CEC_ISR_TXUDR
#define CEC_FLAG_TXEND                  CEC_ISR_TXEND
#define CEC_FLAG_TXBR                   CEC_ISR_TXBR
#define CEC_FLAG_ARBLST                 CEC_ISR_ARBLST
#define CEC_FLAG_RXACKE                 CEC_ISR_RXACKE
#define CEC_FLAG_LBPE                   CEC_ISR_LBPE
#define CEC_FLAG_SBPE                   CEC_ISR_SBPE
#define CEC_FLAG_BRE                    CEC_ISR_BRE
#define CEC_FLAG_RXOVR                  CEC_ISR_RXOVR
#define CEC_FLAG_RXEND                  CEC_ISR_RXEND
#define CEC_FLAG_RXBR                   CEC_ISR_RXBR

#define IS_CEC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFE000) == 0x00) && ((FLAG) != 0x00))

#define IS_CEC_GET_FLAG(FLAG) (((FLAG) == CEC_FLAG_TXACKE) || \
                               ((FLAG) == CEC_FLAG_TXERR)|| \
                               ((FLAG) == CEC_FLAG_TXUDR)|| \
                               ((FLAG) == CEC_FLAG_TXEND)|| \
                               ((FLAG) == CEC_FLAG_TXBR)|| \
                               ((FLAG) == CEC_FLAG_ARBLST)|| \
                               ((FLAG) == CEC_FLAG_RXACKE)|| \
                               ((FLAG) == CEC_FLAG_LBPE)|| \
                               ((FLAG) == CEC_FLAG_SBPE)|| \
                               ((FLAG) == CEC_FLAG_BRE)|| \
                               ((FLAG) == CEC_FLAG_RXOVR)|| \
                               ((FLAG) == CEC_FLAG_RXEND)|| \
                               ((FLAG) == CEC_FLAG_RXBR))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* 导出的函数 ------------------------------------------------------- */

/*  用于将 CEC 配置设置为默认复位状态的函数 *****/
void CEC_DeInit(void);

/* CEC_Initialization 和配置功能 *****************************/
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct); // 根据CEC_InitStruct中指定的参数，初始化CEC外设设备。
void CEC_StructInit(CEC_InitTypeDef* CEC_InitStruct); // 用默认值填充每个CEC_InitStruct成员。
void CEC_Cmd(FunctionalState NewState); // 启用或禁用CEC外设设备。
void CEC_ListenModeCmd(FunctionalState NewState); // 启用或禁用CEC侦听模式。
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress); // 定义CEC设备的自有地址。
void CEC_OwnAddressClear(void); // 清除CEC设备的自有地址。

/* CEC_Data 传输功能 ***********************************************/
void CEC_SendData(uint8_t Data); // 通过CEC外设设备传输单个数据。
uint8_t CEC_ReceiveData(void); // 返回CEC外设设备最近接收的数据。
void CEC_StartOfMessage(void); // 启动新消息
void CEC_EndOfMessage(void); // 用EOM位传输消息。

/* CEC_Interrupts 和标志管理功能 ******************************/
void CEC_ITConfig(uint16_t CEC_IT, FunctionalState NewState); // 启用或禁用选定的CEC中断。
FlagStatus CEC_GetFlagStatus(uint16_t CEC_FLAG); // 获取CEC标志状态。
void CEC_ClearFlag(uint32_t CEC_FLAG); // 清除CEC的挂起标志。
ITStatus CEC_GetITStatus(uint16_t CEC_IT); // 检查指定的CEC中断是否已发生。
void CEC_ClearITPendingBit(uint16_t CEC_IT); // 清除CEC的中断挂起位。
#endif /* STM32F446xx */
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_CEC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
