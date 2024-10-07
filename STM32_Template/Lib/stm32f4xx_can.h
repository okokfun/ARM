/**
  ******************************************************************************
  * 文件:    stm32f4xx_can.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 CAN 固件库的所有功能原型.
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
#ifndef __STM32F4xx_CAN_H
#define __STM32F4xx_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup CAN
  */

/* Exported types ------------------------------------------------------------*/
#if defined(STM32F413_423xx)
#define IS_CAN_ALL_PERIPH(PERIPH) (((PERIPH) == CAN1) || \
                                   ((PERIPH) == CAN2) || \
                                   ((PERIPH) == CAN3))
#else
#define IS_CAN_ALL_PERIPH(PERIPH) (((PERIPH) == CAN1) || \
                                   ((PERIPH) == CAN2))
#endif /* STM32F413_423xx */

/**
  * 简介:  CAN初始化结构定义
  */
typedef struct {
    uint16_t CAN_Prescaler;   /*!< 指定时间段的长度。
								              它的范围从 1 到 1024。 */

    uint8_t CAN_Mode;         /*!< 指定 CAN 操作模式。
								              该参数可以是 @ref CAN_operating_mode 的值 */

    uint8_t CAN_SJW;          /*!< 指定 CAN 硬件允许延长或缩短位以执行重新同步的最大时间量。
								              该参数可以是 @ref CAN_synchronisation_jump_width 的值 */

    uint8_t CAN_BS1;          /*!< 指定位段 1 中的时间量子数。
								              该参数可以是 @ref CAN_time_quantum_in_bit_segment_1 的值 */

    uint8_t CAN_BS2;          /*!< 指定位段 2 中的时间量数。
								              该参数可以是 @ref CAN_time_quantum_in_bit_segment_2 的值 */

    FunctionalState CAN_TTCM; /*!< 启用或禁用时间触发通信模式。
								              此参数可以设置为 ENABLE 或 DISABLE。 */

    FunctionalState CAN_ABOM;  /*!< 启用或禁用自动总线关闭管理。
								              此参数可以设置为 ENABLE 或 DISABLE。 */

    FunctionalState CAN_AWUM;  /*!< 启用或禁用自动唤醒模式。
								              此参数可以设置为 ENABLE 或 DISABLE。 */

    FunctionalState CAN_NART;  /*!< 启用或禁用非自动重传模式。
								              此参数可以设置为 ENABLE 或 DISABLE。 */

    FunctionalState CAN_RFLM;  /*!< 启用或禁用接收 FIFO 锁定模式。
								              此参数可以设置为 ENABLE 或 DISABLE。 */

    FunctionalState CAN_TXFP;  /*!< 启用或禁用发送 FIFO 优先级。
								              此参数可以设置为 ENABLE 或 DISABLE。 */
} CAN_InitTypeDef;

/**
  * 简介:  CAN过滤器初始化结构定义
  */
typedef struct {
    uint16_t CAN_FilterIdHigh;         /*!< 指定过滤器标识号(MSB 用于 32 位配置，第一个用于 16 位配置)。
										此参数可以是 0x0000 和 0xFFFF 之间的值 */

    uint16_t CAN_FilterIdLow;          /*!< 指定过滤器标识号(32 位配置的 LSB，16 位配置的第二个)。
										此参数可以是 0x0000 和 0xFFFF 之间的值 */

    uint16_t CAN_FilterMaskIdHigh;     /*!< 根据模式指定过滤器掩码号或标识号(MSB 用于 32 位配置，第一个用于 16 位配置)。
                                       此参数可以是 0x0000 和 0xFFFF 之间的值*/

    uint16_t CAN_FilterMaskIdLow;      /*!< 根据模式指定过滤器掩码号或标识号(LSB 用于 32 位配置，第二个用于 16 位配置)。
                                       此参数可以是 0x0000 和 0xFFFF 之间的值 */

    uint16_t CAN_FilterFIFOAssignment; /*!< 指定将分配给过滤器的 FIFO(0 或 1)。
                                       该参数可以是 @ref CAN_filter_FIFO 的值 */

    uint8_t CAN_FilterNumber;          /*!< 指定将被初始化的过滤器。 
                                       它的范围从 0 到 13。 */

    uint8_t CAN_FilterMode;            /*!< 指定要初始化的过滤器模式。
                                       该参数可以是 @ref CAN_filter_mode 的值 */

    uint8_t CAN_FilterScale;           /*!< 指定过滤器比例。
                                       该参数可以是 @ref CAN_filter_scale 的值 */

    FunctionalState CAN_FilterActivation; /*!< 启用或禁用过滤器。
                                       此参数可以设置为 ENABLE 或 DISABLE。 */
} CAN_FilterInitTypeDef;

/**
  * 简介:  CAN Tx 报文结构定义
  */
typedef struct {
    uint32_t StdId;  /*!< 指定标准标识符。
						         此参数可以是 0 到 0x7FF 之间的值。 */

    uint32_t ExtId;  /*!< 指定扩展标识符。
                     此参数可以是 0 到 0x1FFFFFFF 之间的值。 */

    uint8_t IDE;     /*!< 指定将要传输的消息的标识符类型。 
                     该参数可以是 @ref CAN_identifier_type 的值 */

    uint8_t RTR;     /*!< 指定将要传输的消息的帧类型。 
                     该参数可以是 @ref CAN_remote_transmission_request 的值 */

    uint8_t DLC;     /*!< 指定将被传输的帧的长度。 
                     此参数可以是 0 到 8 之间的值 */

    uint8_t Data[8]; /*!< 包含要传输的数据。 
                     它的范围从 0 到 0xFF。 */
} CanTxMsg;

/**
  * 简介:  CAN Rx 报文结构定义
  */
typedef struct {
    uint32_t StdId;  /*!< 指定标准标识符。
						         此参数可以是 0 到 0x7FF 之间的值。 */

    uint32_t ExtId;  /*!< 指定扩展标识符。
                     此参数可以是 0 到 0x1FFFFFFF 之间的值。 */

    uint8_t IDE;     /*!< 指定将接收的消息的标识符类型。
                     该参数可以是 @ref CAN_identifier_type 的值 */

    uint8_t RTR;     /*!< 指定接收消息的帧类型。
                     该参数可以是 @ref CAN_remote_transmission_request 的值 */

    uint8_t DLC;     /*!< 指定将接收的帧的长度。
                     此参数可以是 0 到 8 之间的值 */

    uint8_t Data[8]; /*!< 包含要接收的数据。
                     它的范围从 0 到 0xFF。 */

    uint8_t FMI;     /*!< 指定存储在邮箱中的消息通过的过滤器的索引。
                     此参数可以是 0 到 0xFF 之间的值 */
} CanRxMsg;

/* Exported constants --------------------------------------------------------*/

/** @defgroup CAN_Exported_Constants
  */

/** @defgroup CAN_InitStatus
  */
#define CAN_InitStatus_Failed              ((uint8_t)0x00) /*!< CAN 初始化失败 */
#define CAN_InitStatus_Success             ((uint8_t)0x01) /*!< CAN初始化OK */


/* Legacy defines */
#define CANINITFAILED    CAN_InitStatus_Failed
#define CANINITOK        CAN_InitStatus_Success

/** @defgroup CAN_operating_mode
  */
#define CAN_Mode_Normal             ((uint8_t)0x00)  /*!< 正常模式 */
#define CAN_Mode_LoopBack           ((uint8_t)0x01)  /*!< 环回模式 */
#define CAN_Mode_Silent             ((uint8_t)0x02)  /*!< 静音模式 */
#define CAN_Mode_Silent_LoopBack    ((uint8_t)0x03)  /*!< 环回结合静音模式 */

#define IS_CAN_MODE(MODE) (((MODE) == CAN_Mode_Normal) || \
                           ((MODE) == CAN_Mode_LoopBack)|| \
                           ((MODE) == CAN_Mode_Silent) || \
                           ((MODE) == CAN_Mode_Silent_LoopBack))


/**
 * @defgroup CAN_operating_mode
 */
#define CAN_OperatingMode_Initialization  ((uint8_t)0x00) /*!< 初始化模式 */
#define CAN_OperatingMode_Normal          ((uint8_t)0x01) /*!< 正常模式 */
#define CAN_OperatingMode_Sleep           ((uint8_t)0x02) /*!< 睡眠模式 */


#define IS_CAN_OPERATING_MODE(MODE) (((MODE) == CAN_OperatingMode_Initialization) ||\
                                     ((MODE) == CAN_OperatingMode_Normal)|| \
                                     ((MODE) == CAN_OperatingMode_Sleep))

/**
  * @defgroup CAN_operating_mode_status
  */
#define CAN_ModeStatus_Failed    ((uint8_t)0x00)                /*!< CAN进入特定模式失败 */
#define CAN_ModeStatus_Success   ((uint8_t)!CAN_ModeStatus_Failed)   /*!< CAN进入特定模式成功 */

/** @defgroup CAN_synchronisation_jump_width
  */
#define CAN_SJW_1tq                 ((uint8_t)0x00)  /*!< 1个时间量 */
#define CAN_SJW_2tq                 ((uint8_t)0x01)  /*!< 2个时间量 */
#define CAN_SJW_3tq                 ((uint8_t)0x02)  /*!< 3 个时间量 */
#define CAN_SJW_4tq                 ((uint8_t)0x03)  /*!< 4 个时间量 */

#define IS_CAN_SJW(SJW) (((SJW) == CAN_SJW_1tq) || ((SJW) == CAN_SJW_2tq)|| \
                         ((SJW) == CAN_SJW_3tq) || ((SJW) == CAN_SJW_4tq))

/** @defgroup CAN_time_quantum_in_bit_segment_1
  */
#define CAN_BS1_1tq                 ((uint8_t)0x00)  /*!< 1 个时间量 */
#define CAN_BS1_2tq                 ((uint8_t)0x01)  /*!< 2 个时间量 */
#define CAN_BS1_3tq                 ((uint8_t)0x02)  /*!< 3 个时间量 */
#define CAN_BS1_4tq                 ((uint8_t)0x03)  /*!< 4 个时间量 */
#define CAN_BS1_5tq                 ((uint8_t)0x04)  /*!< 5 个时间量 */
#define CAN_BS1_6tq                 ((uint8_t)0x05)  /*!< 6 个时间量 */
#define CAN_BS1_7tq                 ((uint8_t)0x06)  /*!< 7 个时间量 */
#define CAN_BS1_8tq                 ((uint8_t)0x07)  /*!< 8 个时间量 */
#define CAN_BS1_9tq                 ((uint8_t)0x08)  /*!< 9 个时间量 */
#define CAN_BS1_10tq                ((uint8_t)0x09)  /*!< 10 个时间量 */
#define CAN_BS1_11tq                ((uint8_t)0x0A)  /*!< 11 个时间量 */
#define CAN_BS1_12tq                ((uint8_t)0x0B)  /*!< 12 个时间量 */
#define CAN_BS1_13tq                ((uint8_t)0x0C)  /*!< 13 个时间量 */
#define CAN_BS1_14tq                ((uint8_t)0x0D)  /*!< 14 个时间量 */
#define CAN_BS1_15tq                ((uint8_t)0x0E)  /*!< 15 个时间量 */
#define CAN_BS1_16tq                ((uint8_t)0x0F)  /*!< 16 个时间量 */

#define IS_CAN_BS1(BS1) ((BS1) <= CAN_BS1_16tq)

/** @defgroup CAN_time_quantum_in_bit_segment_2
  */
#define CAN_BS2_1tq                 ((uint8_t)0x00)  /*!< 1 个时间量 */
#define CAN_BS2_2tq                 ((uint8_t)0x01)  /*!< 2 个时间量 */
#define CAN_BS2_3tq                 ((uint8_t)0x02)  /*!< 3 个时间量 */
#define CAN_BS2_4tq                 ((uint8_t)0x03)  /*!< 4 个时间量 */
#define CAN_BS2_5tq                 ((uint8_t)0x04)  /*!< 5 个时间量 */
#define CAN_BS2_6tq                 ((uint8_t)0x05)  /*!< 6 个时间量 */
#define CAN_BS2_7tq                 ((uint8_t)0x06)  /*!< 7 个时间量 */
#define CAN_BS2_8tq                 ((uint8_t)0x07)  /*!< 8 个时间量 */

#define IS_CAN_BS2(BS2) ((BS2) <= CAN_BS2_8tq)

/** @defgroup CAN_clock_prescaler
  */
#define IS_CAN_PRESCALER(PRESCALER) (((PRESCALER) >= 1) && ((PRESCALER) <= 1024))

/** @defgroup CAN_filter_number
  */
#define IS_CAN_FILTER_NUMBER(NUMBER) ((NUMBER) <= 27)

/** @defgroup CAN_filter_mode
  */
#define CAN_FilterMode_IdMask       ((uint8_t)0x00)  /*!< 标识符/掩码模式 */
#define CAN_FilterMode_IdList       ((uint8_t)0x01)  /*!< 标识符列表模式 */

#define IS_CAN_FILTER_MODE(MODE) (((MODE) == CAN_FilterMode_IdMask) || \
                                  ((MODE) == CAN_FilterMode_IdList))

/** @defgroup CAN_filter_scale
  */
#define CAN_FilterScale_16bit       ((uint8_t)0x00) /*!< 两个 16 位滤波器 */
#define CAN_FilterScale_32bit       ((uint8_t)0x01) /*!< 一个 32 位过滤器 */

#define IS_CAN_FILTER_SCALE(SCALE) (((SCALE) == CAN_FilterScale_16bit) || \
                                    ((SCALE) == CAN_FilterScale_32bit))

/** @defgroup CAN_filter_FIFO
  */
#define CAN_Filter_FIFO0             ((uint8_t)0x00)  /*!< 过滤器 x 的过滤器 FIFO 0 分配 */
#define CAN_Filter_FIFO1             ((uint8_t)0x01)  /*!< 过滤器 x 的过滤器 FIFO 1 分配 */
#define IS_CAN_FILTER_FIFO(FIFO) (((FIFO) == CAN_FilterFIFO0) || \
                                  ((FIFO) == CAN_FilterFIFO1))

/* Legacy defines */
#define CAN_FilterFIFO0  CAN_Filter_FIFO0
#define CAN_FilterFIFO1  CAN_Filter_FIFO1

/** @defgroup CAN_Start_bank_filter_for_slave_CAN
  */
#define IS_CAN_BANKNUMBER(BANKNUMBER) (((BANKNUMBER) >= 1) && ((BANKNUMBER) <= 27))

/** @defgroup CAN_Tx
  */
#define IS_CAN_TRANSMITMAILBOX(TRANSMITMAILBOX) ((TRANSMITMAILBOX) <= ((uint8_t)0x02))
#define IS_CAN_STDID(STDID)   ((STDID) <= ((uint32_t)0x7FF))
#define IS_CAN_EXTID(EXTID)   ((EXTID) <= ((uint32_t)0x1FFFFFFF))
#define IS_CAN_DLC(DLC)       ((DLC) <= ((uint8_t)0x08))

/** @defgroup CAN_identifier_type
  */
#define CAN_Id_Standard             ((uint32_t)0x00000000)  /*!< 标准 ID */
#define CAN_Id_Extended             ((uint32_t)0x00000004)  /*!< 扩展 ID */
#define IS_CAN_IDTYPE(IDTYPE) (((IDTYPE) == CAN_Id_Standard) || \
                               ((IDTYPE) == CAN_Id_Extended))

/* Legacy defines */
#define CAN_ID_STD      CAN_Id_Standard
#define CAN_ID_EXT      CAN_Id_Extended

/** @defgroup CAN_remote_transmission_request
  */
#define CAN_RTR_Data                ((uint32_t)0x00000000)  /*!< 数据框 */
#define CAN_RTR_Remote              ((uint32_t)0x00000002)  /*!< 远程框架 */
#define IS_CAN_RTR(RTR) (((RTR) == CAN_RTR_Data) || ((RTR) == CAN_RTR_Remote))

/* Legacy defines */
#define CAN_RTR_DATA     CAN_RTR_Data
#define CAN_RTR_REMOTE   CAN_RTR_Remote

/** @defgroup CAN_transmit_constants
  */
#define CAN_TxStatus_Failed         ((uint8_t)0x00)/*!< CAN 传输失败 */
#define CAN_TxStatus_Ok             ((uint8_t)0x01) /*!< CAN 传输成功 */
#define CAN_TxStatus_Pending        ((uint8_t)0x02) /*!< CAN 传输未决 */
#define CAN_TxStatus_NoMailBox      ((uint8_t)0x04) /*!< CAN 单元未提供空邮箱 */
/* Legacy defines */
#define CANTXFAILED                  CAN_TxStatus_Failed
#define CANTXOK                      CAN_TxStatus_Ok
#define CANTXPENDING                 CAN_TxStatus_Pending
#define CAN_NO_MB                    CAN_TxStatus_NoMailBox

/** @defgroup CAN_receive_FIFO_number_constants
  */
#define CAN_FIFO0                 ((uint8_t)0x00) /*!< CAN FIFO 0 用于接收 */
#define CAN_FIFO1                 ((uint8_t)0x01) /*!< CAN FIFO 1 用于接收 */

#define IS_CAN_FIFO(FIFO) (((FIFO) == CAN_FIFO0) || ((FIFO) == CAN_FIFO1))

/** @defgroup CAN_sleep_constants
  */
#define CAN_Sleep_Failed     ((uint8_t)0x00) /*!< CAN 未进入睡眠模式 */
#define CAN_Sleep_Ok         ((uint8_t)0x01) /*!< CAN进入睡眠模式 */

/* Legacy defines */
#define CANSLEEPFAILED   CAN_Sleep_Failed
#define CANSLEEPOK       CAN_Sleep_Ok

/** @defgroup CAN_wake_up_constants
  */
#define CAN_WakeUp_Failed        ((uint8_t)0x00) /*!< CAN 没有离开睡眠模式 */
#define CAN_WakeUp_Ok            ((uint8_t)0x01) /*!< CAN 离开睡眠模式 */

/* Legacy defines */
#define CANWAKEUPFAILED   CAN_WakeUp_Failed
#define CANWAKEUPOK       CAN_WakeUp_Ok

/**
  * @defgroup CAN_Error_Code_constants
  */
#define CAN_ErrorCode_NoErr           ((uint8_t)0x00) /*!< 没有错误 */
#define	CAN_ErrorCode_StuffErr        ((uint8_t)0x10) /*!< Stuff Error */
#define	CAN_ErrorCode_FormErr         ((uint8_t)0x20) /*!< Form Error */
#define	CAN_ErrorCode_ACKErr          ((uint8_t)0x30) /*!< Acknowledgment Error */
#define	CAN_ErrorCode_BitRecessiveErr ((uint8_t)0x40) /*!< Bit Recessive Error */
#define	CAN_ErrorCode_BitDominantErr  ((uint8_t)0x50) /*!< Bit Dominant Error */
#define	CAN_ErrorCode_CRCErr          ((uint8_t)0x60) /*!< CRC Error  */
#define	CAN_ErrorCode_SoftwareSetErr  ((uint8_t)0x70) /*!< Software Set Error */

/** @defgroup CAN_flags
  */
/* 如果标志为0x3XXXXXXX，则表示它可以与can_GetFlagStatus()和can_ClearFlag() 函数一起使用。 */
/* 如果标志为0x1XXXXXXX，则表示它只能与can_GetFlagStatus() 函数一起使用。  */

/* 传输标志 */
#define CAN_FLAG_RQCP0             ((uint32_t)0x38000001) /*!< 请求MailBox0标志 */
#define CAN_FLAG_RQCP1             ((uint32_t)0x38000100) /*!< 请求MailBox1标志 */
#define CAN_FLAG_RQCP2             ((uint32_t)0x38010000) /*!< 请求MailBox2标志 */

/* 接收标志 */
#define CAN_FLAG_FMP0              ((uint32_t)0x12000003) /*!< FIFO 0消息等待标志 */
#define CAN_FLAG_FF0               ((uint32_t)0x32000008) /*!< FIFO 0满标志            */
#define CAN_FLAG_FOV0              ((uint32_t)0x32000010) /*!< FIFO 0超限标志         */
#define CAN_FLAG_FMP1              ((uint32_t)0x14000003) /*!< FIFO 1消息等待标志 */
#define CAN_FLAG_FF1               ((uint32_t)0x34000008) /*!< FIFO 1满标志            */
#define CAN_FLAG_FOV1              ((uint32_t)0x34000010) /*!< FIFO 1超限标志         */

/* 操作模式标志 */
#define CAN_FLAG_WKU               ((uint32_t)0x31000008) /*!< 唤醒标志 */
#define CAN_FLAG_SLAK              ((uint32_t)0x31000012) /*!< 睡眠确认标志 */
/* @note 当SLAK中断被禁用(SLKIE=0)时，无法对SLAKI进行轮询。
          在这种情况下，可以轮询SLAK位。*/

/* 错误标志 */
#define CAN_FLAG_EWG               ((uint32_t)0x10F00001) /*!< 错误警告标志   */
#define CAN_FLAG_EPV               ((uint32_t)0x10F00002) /*!< 错误被动标志   */
#define CAN_FLAG_BOF               ((uint32_t)0x10F00004) /*!< 总线关闭标志        */
#define CAN_FLAG_LEC               ((uint32_t)0x30F00070) /*!< 上次错误代码标志 */

#define IS_CAN_GET_FLAG(FLAG) (((FLAG) == CAN_FLAG_LEC)  || ((FLAG) == CAN_FLAG_BOF)   || \
                               ((FLAG) == CAN_FLAG_EPV)  || ((FLAG) == CAN_FLAG_EWG)   || \
                               ((FLAG) == CAN_FLAG_WKU)  || ((FLAG) == CAN_FLAG_FOV0)  || \
                               ((FLAG) == CAN_FLAG_FF0)  || ((FLAG) == CAN_FLAG_FMP0)  || \
                               ((FLAG) == CAN_FLAG_FOV1) || ((FLAG) == CAN_FLAG_FF1)   || \
                               ((FLAG) == CAN_FLAG_FMP1) || ((FLAG) == CAN_FLAG_RQCP2) || \
                               ((FLAG) == CAN_FLAG_RQCP1)|| ((FLAG) == CAN_FLAG_RQCP0) || \
                               ((FLAG) == CAN_FLAG_SLAK ))

#define IS_CAN_CLEAR_FLAG(FLAG)(((FLAG) == CAN_FLAG_LEC) || ((FLAG) == CAN_FLAG_RQCP2) || \
                                ((FLAG) == CAN_FLAG_RQCP1)  || ((FLAG) == CAN_FLAG_RQCP0) || \
                                ((FLAG) == CAN_FLAG_FF0)  || ((FLAG) == CAN_FLAG_FOV0) ||\
                                ((FLAG) == CAN_FLAG_FF1) || ((FLAG) == CAN_FLAG_FOV1) || \
                                ((FLAG) == CAN_FLAG_WKU) || ((FLAG) == CAN_FLAG_SLAK))


/** @defgroup CAN_interrupts
  */
#define CAN_IT_TME                  ((uint32_t)0x00000001) /*!< Transmit mailbox empty Interrupt*/

/* 接收中断 */
#define CAN_IT_FMP0                 ((uint32_t)0x00000002) /*!< FIFO 0 message pending Interrupt*/
#define CAN_IT_FF0                  ((uint32_t)0x00000004) /*!< FIFO 0 full Interrupt*/
#define CAN_IT_FOV0                 ((uint32_t)0x00000008) /*!< FIFO 0 overrun Interrupt*/
#define CAN_IT_FMP1                 ((uint32_t)0x00000010) /*!< FIFO 1 message pending Interrupt*/
#define CAN_IT_FF1                  ((uint32_t)0x00000020) /*!< FIFO 1 full Interrupt*/
#define CAN_IT_FOV1                 ((uint32_t)0x00000040) /*!< FIFO 1 overrun Interrupt*/

/* 操作模式中断 */
#define CAN_IT_WKU                  ((uint32_t)0x00010000) /*!< Wake-up Interrupt*/
#define CAN_IT_SLK                  ((uint32_t)0x00020000) /*!< Sleep acknowledge Interrupt*/

/* 错误中断 */
#define CAN_IT_EWG                  ((uint32_t)0x00000100) /*!< Error warning Interrupt*/
#define CAN_IT_EPV                  ((uint32_t)0x00000200) /*!< Error passive Interrupt*/
#define CAN_IT_BOF                  ((uint32_t)0x00000400) /*!< Bus-off Interrupt*/
#define CAN_IT_LEC                  ((uint32_t)0x00000800) /*!< Last error code Interrupt*/
#define CAN_IT_ERR                  ((uint32_t)0x00008000) /*!< Error Interrupt*/

/* 名为中断的标志:仅为FW兼容性而保留 */
#define CAN_IT_RQCP0   CAN_IT_TME
#define CAN_IT_RQCP1   CAN_IT_TME
#define CAN_IT_RQCP2   CAN_IT_TME


#define IS_CAN_IT(IT)        (((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FMP0)  ||\
                              ((IT) == CAN_IT_FF0)  || ((IT) == CAN_IT_FOV0)  ||\
                              ((IT) == CAN_IT_FMP1) || ((IT) == CAN_IT_FF1)   ||\
                              ((IT) == CAN_IT_FOV1) || ((IT) == CAN_IT_EWG)   ||\
                              ((IT) == CAN_IT_EPV)  || ((IT) == CAN_IT_BOF)   ||\
                              ((IT) == CAN_IT_LEC)  || ((IT) == CAN_IT_ERR)   ||\
                              ((IT) == CAN_IT_WKU)  || ((IT) == CAN_IT_SLK))

#define IS_CAN_CLEAR_IT(IT) (((IT) == CAN_IT_TME) || ((IT) == CAN_IT_FF0)    ||\
                             ((IT) == CAN_IT_FOV0)|| ((IT) == CAN_IT_FF1)    ||\
                             ((IT) == CAN_IT_FOV1)|| ((IT) == CAN_IT_EWG)    ||\
                             ((IT) == CAN_IT_EPV) || ((IT) == CAN_IT_BOF)    ||\
                             ((IT) == CAN_IT_LEC) || ((IT) == CAN_IT_ERR)    ||\
                             ((IT) == CAN_IT_WKU) || ((IT) == CAN_IT_SLK))


/* Exported macro ------------------------------------------------------------*/
/* 导出的函数 --------------------------------------------------------*/

/*  用于将 CAN 配置设置为默认复位状态的函数 *****/
void CAN_DeInit(CAN_TypeDef* CANx);

/* 初始化和配置功能 *********************************/
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct); // 根据 CAN_InitStruct 中指定的参数初始化外设 CAN 的寄存器
#if defined(STM32F413_423xx)
void CAN_FilterInit(CAN_TypeDef* CANx, CAN_FilterInitTypeDef* CAN_FilterInitStruct); // 根据 CAN_FilterInitStruct 中指定的参数初始化外设 CAN 的寄存器
#else
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct);
#endif /* STM32F413_423xx */
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct); // 把 CAN_InitStruct 中的每一个参数按缺省值填入
#if defined(STM32F413_423xx)
void CAN_SlaveStartBank(CAN_TypeDef* CANx, uint8_t CAN_BankNumber); // 选择从 CAN 的起始组过滤器。
#else
void CAN_SlaveStartBank(uint8_t CAN_BankNumber);
#endif /* STM32F413_423xx */
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState); // 启用或禁用 CAN 的 DBG 冻结。
void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState); // 启用或禁用 CAN Time TriggerOperation 通信模式。

/* CAN 帧传输功能 ******************************************/
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage); // 开始一个消息的传输
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox); // 检查消息传输的状态
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox); // 取消一个传输请求

/* CAN 帧接收功能 *********************************************/
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage); // 接收一个消息
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber); // 释放一个 FIFO
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber); // 返回挂号的信息数量

/* 操作模式功能 **************************************************/
uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode); // 选择 CAN 操作模式。
uint8_t CAN_Sleep(CAN_TypeDef* CANx); //  CAN 进入低功耗模式
uint8_t CAN_WakeUp(CAN_TypeDef* CANx); // 将 CAN 唤醒

/* CAN 总线错误管理功能 *****************************************/
uint8_t CAN_GetLastErrorCode(CAN_TypeDef* CANx); // 返回 CANx 的最后一个错误代码 (LEC)。
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef* CANx); // 返回 CANx 接收错误计数器 (REC)。
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx); // 返回 9 位 CANx 发送错误计数器 (TEC) 的 LSB。

/* 中断和标志管理功能 **********************************/
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState); // 使能或者失能指定的 CAN 中断
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG); // 检查指定的 CAN 标志位被设置与否
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG); // 清除 CAN 的待处理标志位
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT); // 检查指定的 CAN 中断发生与否
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT); // 清除 CAN 的中断待处理标志位

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_CAN_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
