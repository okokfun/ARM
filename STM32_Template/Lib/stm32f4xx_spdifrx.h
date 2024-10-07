/**
  ******************************************************************************
  * 文件:    stm32f4xx_spdifrx.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 SPDIFRX 固件库的所有功能原型.
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
#ifndef __STM32F4xx_SPDIFRX_H
#define __STM32F4xx_SPDIFRX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup SPDIFRX
  */
#if defined(STM32F446xx)
/* Exported types ------------------------------------------------------------*/
/**
  * 简介:  SPDIFRX Init structure definition
  */
typedef struct {
    uint32_t SPDIFRX_InputSelection;           /*!< 指定 SPDIFRX 输入选择。
                                                 该参数可以是 @ref SPDIFRX_Input_Selection 的值 */

    uint32_t SPDIFRX_Retries;                  /*!< 指定在同步阶段允许的最大重试次数。
                                                 该参数可以是 @ref SPDIFRX_Max_Retries 的值 */

    uint32_t SPDIFRX_WaitForActivity;          /*!< 指定等待 SPDIFRX 选定输入的活动。
                                                 此参数可以是 @ref SPDIFRX_Wait_For_Activity 的值。 */

    uint32_t SPDIFRX_ChannelSelection;         /*!< 指定控制流是从通道 A 还是 B 获取通道状态。
                                                 该参数可以是 @ref SPDIFRX_Channel_Selection 的值 */

    uint32_t SPDIFRX_DataFormat;               /*!< 指定数据样本格式(LSB、MSB、...)。
                                                 该参数可以是 @ref SPDIFRX_Data_Format 的值 */

    uint32_t SPDIFRX_StereoMode;               /*!< 指定外设设备是处于立体声还是单声道模式。
                                                 该参数可以是 @ref SPDIFRX_Stereo_Mode 的值 */
} SPDIFRX_InitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup SPDIFRX_Exported_Constants
  */
#define IS_SPDIFRX_PERIPH(PERIPH) (((PERIPH) == SPDIFRX))

/** @defgroup SPDIFRX_Input_Selection SPDIFRX Input Selection
  */
#define SPDIFRX_Input_IN0               ((uint32_t)0x00000000)
#define SPDIFRX_Input_IN1               ((uint32_t)0x00010000)
#define SPDIFRX_Input_IN2               ((uint32_t)0x00020000)
#define SPDIFRX_Input_IN3               ((uint32_t)0x00030000)
#define IS_SPDIFRX_INPUT_SELECT(INPUT)  (((INPUT) == SPDIFRX_Input_IN1) || \
        ((INPUT) == SPDIFRX_Input_IN2) || \
        ((INPUT) == SPDIFRX_Input_IN3)  || \
        ((INPUT) == SPDIFRX_Input_IN0))

/** @defgroup SPDIFRX_Max_Retries SPDIFRX Max Retries
  */
#define SPDIFRX_1MAX_RETRIES               ((uint32_t)0x00000000)
#define SPDIFRX_4MAX_RETRIES               ((uint32_t)0x00001000)
#define SPDIFRX_16MAX_RETRIES              ((uint32_t)0x00002000)
#define SPDIFRX_64MAX_RETRIES              ((uint32_t)0x00003000)
#define IS_SPDIFRX_MAX_RETRIES(RET)   (((RET) == SPDIFRX_1MAX_RETRIES) || \
                                       ((RET) == SPDIFRX_4MAX_RETRIES) || \
                                       ((RET) == SPDIFRX_16MAX_RETRIES)  || \
                                       ((RET) == SPDIFRX_64MAX_RETRIES))

/** @defgroup SPDIFRX_Wait_For_Activity SPDIFRX Wait For Activity
  */
#define SPDIFRX_WaitForActivity_Off                 ((uint32_t)0x00000000)
#define SPDIFRX_WaitForActivity_On                  ((uint32_t)SPDIFRX_CR_WFA)
#define IS_SPDIFRX_WAIT_FOR_ACTIVITY(VAL)    (((VAL) == SPDIFRX_WaitForActivity_On) || \
        ((VAL) == SPDIFRX_WaitForActivity_Off))

/** @defgroup SPDIFRX_ChannelSelection SPDIFRX Channel Selection
  */
#define SPDIFRX_Select_Channel_A      ((uint32_t)0x00000000)
#define SPDIFRX_Select_Channel_B      ((uint32_t)SPDIFRX_CR_CHSEL)
#define IS_SPDIFRX_CHANNEL(CHANNEL)   (((CHANNEL) == SPDIFRX_Select_Channel_A) || \
                                       ((CHANNEL) == SPDIFRX_Select_Channel_B))

/** @defgroup SPDIFRX_Block_Synchronization SPDIFRX Block Synchronization
  */
#define SPDIFRX_LSB_DataFormat                   ((uint32_t)0x00000000)
#define SPDIFRX_MSB_DataFormat                   ((uint32_t)0x00000010)
#define SPDIFRX_32BITS_DataFormat                ((uint32_t)0x00000020)
#define IS_SPDIFRX_DATA_FORMAT(FORMAT)    (((FORMAT) == SPDIFRX_LSB_DataFormat) || \
        ((FORMAT) == SPDIFRX_MSB_DataFormat) || \
        ((FORMAT) == SPDIFRX_32BITS_DataFormat))

/** @defgroup SPDIFRX_StereoMode SPDIFRX StereoMode
  */
#define SPDIFRX_StereoMode_Disabled          ((uint32_t)0x00000000)
#define SPDIFRX_StereoMode_Enabled           ((uint32_t)SPDIFRX_CR_RXSTEO)
#define IS_STEREO_MODE(MODE)  (((MODE) == SPDIFRX_StereoMode_Disabled) || \
                               ((MODE) == SPDIFRX_StereoMode_Enabled))

/** @defgroup SPDIFRX_State SPDIFRX State
  */
#define SPDIFRX_STATE_IDLE    ((uint32_t)0x00000000)
#define SPDIFRX_STATE_SYNC    ((uint32_t)0x00000001)
#define SPDIFRX_STATE_RCV     ((uint32_t)SPDIFRX_CR_SPDIFEN)
#define IS_SPDIFRX_STATE(STATE)    (((STATE) == SPDIFRX_STATE_IDLE) || \
                                    ((STATE) == SPDIFRX_STATE_SYNC) || \
                                    ((STATE) == SPDIFRX_STATE_RCV))

/** @defgroup SPDIFRX_Interrupts_Definition SPDIFRX Interrupts Definition
  */
#define SPDIFRX_IT_RXNE                       ((uint32_t)SPDIFRX_IMR_RXNEIE)
#define SPDIFRX_IT_CSRNE                      ((uint32_t)SPDIFRX_IMR_CSRNEIE)
#define SPDIFRX_IT_PERRIE                     ((uint32_t)SPDIFRX_IMR_PERRIE)
#define SPDIFRX_IT_OVRIE                      ((uint32_t)SPDIFRX_IMR_OVRIE)
#define SPDIFRX_IT_SBLKIE                     ((uint32_t)SPDIFRX_IMR_SBLKIE)
#define SPDIFRX_IT_SYNCDIE                    ((uint32_t)SPDIFRX_IMR_SYNCDIE)
#define SPDIFRX_IT_IFEIE                      ((uint32_t)SPDIFRX_IMR_IFEIE )
#define IS_SPDIFRX_CONFIG_IT(IT)    (((IT) == SPDIFRX_IT_RXNE)   || \
                                     ((IT) == SPDIFRX_IT_CSRNE)   || \
                                     ((IT) == SPDIFRX_IT_PERRIE)  || \
                                     ((IT) == SPDIFRX_IT_OVRIE)   || \
                                     ((IT) == SPDIFRX_IT_SBLKIE)  || \
                                     ((IT) == SPDIFRX_IT_SYNCDIE) || \
                                     ((IT) == SPDIFRX_IT_IFEIE))

/** @defgroup SPDIFRX_Flags_Definition SPDIFRX Flags Definition
  */
#define SPDIFRX_FLAG_RXNE                   ((uint32_t)SPDIFRX_SR_RXNE)
#define SPDIFRX_FLAG_CSRNE                  ((uint32_t)SPDIFRX_SR_CSRNE)
#define SPDIFRX_FLAG_PERR                   ((uint32_t)SPDIFRX_SR_PERR)
#define SPDIFRX_FLAG_OVR                    ((uint32_t)SPDIFRX_SR_OVR)
#define SPDIFRX_FLAG_SBD                    ((uint32_t)SPDIFRX_SR_SBD)
#define SPDIFRX_FLAG_SYNCD                  ((uint32_t)SPDIFRX_SR_SYNCD)
#define SPDIFRX_FLAG_FERR                   ((uint32_t)SPDIFRX_SR_FERR)
#define SPDIFRX_FLAG_SERR                   ((uint32_t)SPDIFRX_SR_SERR)
#define SPDIFRX_FLAG_TERR                   ((uint32_t)SPDIFRX_SR_TERR)
#define IS_SPDIFRX_FLAG(FLAG)    (((FLAG) == SPDIFRX_FLAG_RXNE) || ((FLAG) == SPDIFRX_FLAG_CSRNE) || \
                                  ((FLAG) == SPDIFRX_FLAG_PERR) || ((FLAG) == SPDIFRX_FLAG_OVR) || \
                                  ((FLAG) == SPDIFRX_SR_SBD) || ((FLAG) == SPDIFRX_SR_SYNCD) || \
                                  ((FLAG) == SPDIFRX_SR_FERR) || ((FLAG) == SPDIFRX_SR_SERR) || \
                                  ((FLAG) == SPDIFRX_SR_TERR))
#define IS_SPDIFRX_CLEAR_FLAG(FLAG)    (((FLAG) == SPDIFRX_FLAG_PERR) || ((FLAG) == SPDIFRX_FLAG_OVR)   || \
                                        ((FLAG) == SPDIFRX_SR_SBD) || ((FLAG) == SPDIFRX_SR_SYNCD))


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 SPDIFRX 配置设置为默认复位状态的函数 *****/
void SPDIFRX_DeInit(void); // 将 SPDIFRXx 外设寄存器取消初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void SPDIFRX_Init(SPDIFRX_InitTypeDef* SPDIFRX_InitStruct); // 根据 SPDIFRX_InitStruct 中指定的参数初始化 SPDIFRX 外设。
void SPDIFRX_StructInit(SPDIFRX_InitTypeDef* SPDIFRX_InitStruct); // 用其默认值填充每个 SPDIFRX_InitStruct 成员。
void SPDIFRX_Cmd(uint32_t SPDIFRX_State); // 启用或禁用 SPDIFRX 外设。
void SPDIFRX_SetPreambleTypeBit(FunctionalState NewState); // 启用或禁用 SPDIFRX 帧 x 位。
void SPDIFRX_SetUserDataChannelStatusBits(FunctionalState NewState); // 启用或禁用 SPDIFRX 帧 x 位。
void SPDIFRX_SetValidityBit(FunctionalState NewState); // 启用或禁用 SPDIFRX 帧 x 位。
void SPDIFRX_SetParityBit(FunctionalState NewState); // 启用或禁用 SPDIFRX 帧 x 位。

/* 数据传输功能 ***************************************************/
uint32_t SPDIFRX_ReceiveData(void);

/* DMA传输管理功能 *****************************************/
void SPDIFRX_RxDMACmd(FunctionalState NewState); // 启用或禁用 SPDIFRX DMA 接口 (RX)。
void SPDIFRX_CbDMACmd(FunctionalState NewState); // 启用或禁用 SPDIFRX DMA 接口(控制缓冲区)。

/* 中断和标志管理功能 **********************************/
void SPDIFRX_ITConfig(uint32_t SPDIFRX_IT, FunctionalState NewState); // 启用或禁用指定的 SPDIFRX 块中断。
FlagStatus SPDIFRX_GetFlagStatus(uint32_t SPDIFRX_FLAG); // 检查是否设置了指定的 SPDIFRX 标志。
void SPDIFRX_ClearFlag(uint32_t SPDIFRX_FLAG); // 清除指定的 SPDIFRX 标志。
ITStatus SPDIFRX_GetITStatus(uint32_t SPDIFRX_IT); // 检查指定的 SPDIFRX 中断是否发生。
void SPDIFRX_ClearITPendingBit(uint32_t SPDIFRX_IT); // 清除 SPDIFRX 中断挂起位。

#endif /* STM32F446xx */


#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_SPDIFRX_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
