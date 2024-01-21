/**
  ******************************************************************************
  * 文件:    stm32f4xx_sai.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 SAI 固件库的所有功能原型.
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
#ifndef __STM32F4xx_SAI_H
#define __STM32F4xx_SAI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SAI
  * @{
  */
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || \
defined (STM32F401xx) || defined (STM32F411xE) || defined (STM32F446xx) || defined (STM32F469_479xx) || \
defined (STM32F413_423xx)
/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  SAI Block初始化结构定义
  */
typedef struct {
    uint32_t SAI_AudioMode;           /*!< 指定 SAI 块音频模式。
                                          该参数可以是@ref SAI_Block_Mode 的值 */

    uint32_t SAI_Protocol;             /*!< 指定 SAI 块协议。
                                          该参数可以是@ref SAI_Block_Protocol 的值 */

    uint32_t SAI_DataSize;            /*!< 指定 SAI 块数据大小。
                                         该参数可以是@ref SAI_Block_Data_Size的值。
										                     注意当选择AC'97或SPDIF协议时，该值将被忽略。*/

    uint32_t SAI_FirstBit;            /*!< 指定数据传输是从 MSB 位还是 LSB 位开始。
                                         该参数可以是@ref SAI_Block_MSB_LSB_transmission的值。
										                     注意当选择AC’97或SPDIF协议时，该值没有意义。*/

    uint32_t SAI_ClockStrobing;       /*!< 指定 SAI Block 时钟选通边沿敏感度。
                                          该参数可以是@ref SAI_Block_Clock_Strobing 的值 */

    uint32_t SAI_Synchro;             /*!< 指定 SAI 块同步
                                          该参数可以是@ref SAI_Block_Synchronization 的值 */

    uint32_t SAI_SynchroExt;          /*!< 指定 SAI 外部输出同步，此设置对 BlockA 和 BlockB 通用
                                          该参数可以是@ref SAI_Block_SyncExt 的值
										                      @注意:如果使用相同 SAI 的两个音频块，则该参数必须为每个音频块设置为相同的值  */

    uint32_t SAI_OUTDRIV;             /*!< 指定何时驱动 SAI 模块输出。
                                          此参数可以是@ref SAI_Block_Output_Drive 的值
										                      @注意此值必须在启用音频块之前但在音频块配置之后设置。 */

    uint32_t SAI_NoDivider;           /*!< 指定主时钟是否将被分频。
                                          该参数可以是@ref SAI_Block_NoDivider 的值 */

    uint32_t SAI_MasterDivider;       /*!< 指定 SAI 块主时钟分频器。
                                          @注意主时钟频率根据以下公式计算: MCLK_x = SAI_CK_x/(MCKDIV[3:0]*2)*/

    uint32_t SAI_FIFOThreshold;       /*!< 指定 SAI 块 FIFO 阈值。
                                          该参数可以是@ref SAI_Block_Fifo_Threshold 的值 */
} SAI_InitTypeDef;

/**
  * 简介:  SAI Block Frame Init结构定义
  */
typedef struct {
    uint32_t SAI_FrameLength;         /*!< 指定帧长度，即每个音频帧的 SCK 时钟数。
                                          此参数必须是 8 到 256 之间的数字。
                                          @note 如果主时钟 MCLK_x 引脚声明为输出，则帧长度应对齐到等于 2 的幂的数字，以便在音频帧中保持整数个 MCLK 脉冲按位时钟。
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/

    uint32_t SAI_ActiveFrameLength;   /*!< 指定帧同步活动电平长度。
                                          此参数指定音频帧中 FS 信号有效电平的比特时钟数 (SCK + 1) 长度。
                                          此参数必须是 1 到 128 之间的数字。
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/

    uint32_t SAI_FSDefinition;        /*!< 指定帧同步定义。
                                          该参数可以是 @ref SAI_Block_FS_Definition 的值
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/

    uint32_t SAI_FSPolarity;          /*!< 指定帧同步极性。
                                          该参数可以是 @ref SAI_Block_FS_Polarity 的值
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/

    uint32_t SAI_FSOffset;            /*!< 指定帧同步偏移。
                                          该参数可以是 @ref SAI_Block_FS_Offset 的值
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/
} SAI_FrameInitTypeDef;

/**
  * 简介:    SAI Block Slot Init 结构定义
  */
typedef struct {
    uint32_t SAI_FirstBitOffset;      /*!< 指定槽中第一个数据传输位的位置。
                                          此参数必须是 0 到 24 之间的数字。
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/

    uint32_t SAI_SlotSize;            /*!< 指定插槽大小。
                                          该参数可以是@ref SAI_Block_Slot_Size 的值
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/

    uint32_t SAI_SlotNumber;          /*!< 指定音频帧中的槽数。
                                          此参数必须是 1 到 16 之间的数字。
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/

    uint32_t SAI_SlotActive;          /*!< 指定音频帧中将被激活的插槽。
                                          这个参数可以是@ref SAI_Block_Slot_Active的值
                                          @note 选择AC'97或SPDIF协议时，该值将被忽略。*/
} SAI_SlotInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SAI_Exported_Constants
  * @{
  */

#if defined(STM32F446xx)
#define IS_SAI_PERIPH(PERIPH) (((PERIPH) == SAI1) || ((PERIPH) == SAI2))

#define IS_SAI_BLOCK_PERIPH(PERIPH) (((PERIPH) == SAI1_Block_A) || \
                                     ((PERIPH) == SAI1_Block_B) || \
                                     ((PERIPH) == SAI2_Block_A) || \
                                     ((PERIPH) == SAI2_Block_B))
#endif /* STM32F446xx */

#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE) || defined(STM32F413_423xx) || defined (STM32F469_479xx)

#define IS_SAI_PERIPH(PERIPH) ((PERIPH) == SAI1)

#define IS_SAI_BLOCK_PERIPH(PERIPH) (((PERIPH) == SAI1_Block_A) || \
                                     ((PERIPH) == SAI1_Block_B))
#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE || STM32F413_423xx || STM32F469_479xx */

/** @defgroup SAI_Block_Mode
  * @{
  */
#define SAI_Mode_MasterTx               ((uint32_t)0x00000000)
#define SAI_Mode_MasterRx               ((uint32_t)0x00000001)
#define SAI_Mode_SlaveTx                ((uint32_t)0x00000002)
#define SAI_Mode_SlaveRx                ((uint32_t)0x00000003)
#define IS_SAI_BLOCK_MODE(MODE) (((MODE) == SAI_Mode_MasterTx) || \
                                 ((MODE) == SAI_Mode_MasterRx) || \
                                 ((MODE) == SAI_Mode_SlaveTx)  || \
                                 ((MODE) == SAI_Mode_SlaveRx))
/**
  * @}
  */

/** @defgroup SAI_Block_Protocol
  * @{
  */
#define SAI_Free_Protocol                 ((uint32_t)0x00000000)
#define SAI_SPDIF_Protocol                ((uint32_t)SAI_xCR1_PRTCFG_0)
#define SAI_AC97_Protocol                 ((uint32_t)SAI_xCR1_PRTCFG_1)
#define IS_SAI_BLOCK_PROTOCOL(PROTOCOL) (((PROTOCOL) == SAI_Free_Protocol)  || \
        ((PROTOCOL) == SAI_SPDIF_Protocol) || \
        ((PROTOCOL) == SAI_AC97_Protocol))
/**
  * @}
  */

/** @defgroup SAI_Block_Data_Size
  * @{
  */
#define SAI_DataSize_8b                   ((uint32_t)0x00000040)
#define SAI_DataSize_10b                  ((uint32_t)0x00000060)
#define SAI_DataSize_16b                  ((uint32_t)0x00000080)
#define SAI_DataSize_20b                  ((uint32_t)0x000000A0)
#define SAI_DataSize_24b                  ((uint32_t)0x000000C0)
#define SAI_DataSize_32b                  ((uint32_t)0x000000E0)
#define IS_SAI_BLOCK_DATASIZE(DATASIZE) (((DATASIZE) == SAI_DataSize_8b)  || \
        ((DATASIZE) == SAI_DataSize_10b) || \
        ((DATASIZE) == SAI_DataSize_16b) || \
        ((DATASIZE) == SAI_DataSize_20b) || \
        ((DATASIZE) == SAI_DataSize_24b) || \
        ((DATASIZE) == SAI_DataSize_32b))
/**
  * @}
  */

/** @defgroup SAI_Block_MSB_LSB_transmission
  * @{
  */
#define SAI_FirstBit_MSB                  ((uint32_t)0x00000000)
#define SAI_FirstBit_LSB                  ((uint32_t)SAI_xCR1_LSBFIRST)
#define IS_SAI_BLOCK_FIRST_BIT(BIT) (((BIT) == SAI_FirstBit_MSB) || \
                                     ((BIT) == SAI_FirstBit_LSB))
/**
  * @}
  */

/** @defgroup SAI_Block_Clock_Strobing
  * @{
  */
#define SAI_ClockStrobing_FallingEdge     ((uint32_t)0x00000000)
#define SAI_ClockStrobing_RisingEdge      ((uint32_t)SAI_xCR1_CKSTR)
#define IS_SAI_BLOCK_CLOCK_STROBING(CLOCK) (((CLOCK) == SAI_ClockStrobing_FallingEdge) || \
        ((CLOCK) == SAI_ClockStrobing_RisingEdge))
/**
  * @}
  */

/** @defgroup SAI_Block_Synchronization
  * @{
  */
#define SAI_Asynchronous                   ((uint32_t)0x00000000)
#define SAI_Synchronous                    ((uint32_t)SAI_xCR1_SYNCEN_0)
#define SAI_Synchronous_Ext                ((uint32_t)SAI_xCR1_SYNCEN_1)
#define IS_SAI_BLOCK_SYNCHRO(SYNCHRO)      (((SYNCHRO) == SAI_Synchronous) || \
        ((SYNCHRO) == SAI_Asynchronous) || \
        ((SYNCHRO) == SAI_Synchronous_Ext))
/**
  * @}
  */

/** @defgroup SAI_Block_SyncExt SAI External synchronisation
  * @{
  */
#define SAI_SyncExt_Disable                ((uint32_t)0x00000000)
#define SAI_SyncExt_OutBlockA_Enable       ((uint32_t)SAI_GCR_SYNCOUT_0)
#define SAI_SyncExt_OutBlockB_Enable       ((uint32_t)SAI_GCR_SYNCOUT_1)
#define IS_SAI_BLOCK_SYNCEXT(SYNCHRO)      (((SYNCHRO) == SAI_SyncExt_Disable) || \
        ((SYNCHRO) == SAI_SyncExt_OutBlockA_Enable)|| \
        ((SYNCHRO) == SAI_SyncExt_OutBlockB_Enable))
/**
  * @}
  */

/** @defgroup SAI_Block_Output_Drive
  * @{
  */
#define SAI_OutputDrive_Disabled          ((uint32_t)0x00000000)
#define SAI_OutputDrive_Enabled           ((uint32_t)SAI_xCR1_OUTDRIV)
#define IS_SAI_BLOCK_OUTPUT_DRIVE(DRIVE) (((DRIVE) == SAI_OutputDrive_Disabled) || \
        ((DRIVE) == SAI_OutputDrive_Enabled))
/**
  * @}
  */



/** @defgroup SAI_Block_NoDivider
  * @{
  */
#define SAI_MasterDivider_Enabled         ((uint32_t)0x00000000)
#define SAI_MasterDivider_Disabled        ((uint32_t)SAI_xCR1_NODIV)
#define IS_SAI_BLOCK_NODIVIDER(NODIVIDER) (((NODIVIDER) == SAI_MasterDivider_Enabled) || \
        ((NODIVIDER) == SAI_MasterDivider_Disabled))
/**
  * @}
  */


/** @defgroup SAI_Block_Master_Divider
  * @{
  */
#define IS_SAI_BLOCK_MASTER_DIVIDER(DIVIDER) ((DIVIDER) <= 15)

/**
  * @}
  */

/** @defgroup SAI_Block_Frame_Length
  * @{
  */
#define IS_SAI_BLOCK_FRAME_LENGTH(LENGTH) ((8 <= (LENGTH)) && ((LENGTH) <= 256))

/**
  * @}
  */

/** @defgroup SAI_Block_Active_FrameLength
  * @{
  */
#define IS_SAI_BLOCK_ACTIVE_FRAME(LENGTH) ((1 <= (LENGTH)) && ((LENGTH) <= 128))

/**
  * @}
  */

/** @defgroup SAI_Block_FS_Definition
  * @{
  */
#define SAI_FS_StartFrame                 ((uint32_t)0x00000000)
#define I2S_FS_ChannelIdentification      ((uint32_t)SAI_xFRCR_FSDEF)
#define IS_SAI_BLOCK_FS_DEFINITION(DEFINITION) (((DEFINITION) == SAI_FS_StartFrame) || \
        ((DEFINITION) == I2S_FS_ChannelIdentification))
/**
  * @}
  */

/** @defgroup SAI_Block_FS_Polarity
  * @{
  */
#define SAI_FS_ActiveLow                  ((uint32_t)0x00000000)
#define SAI_FS_ActiveHigh                 ((uint32_t)SAI_xFRCR_FSPO)
#define IS_SAI_BLOCK_FS_POLARITY(POLARITY) (((POLARITY) == SAI_FS_ActiveLow) || \
        ((POLARITY) == SAI_FS_ActiveHigh))
/**
  * @}
  */

/** @defgroup SAI_Block_FS_Offset
  * @{
  */
#define SAI_FS_FirstBit                   ((uint32_t)0x00000000)
#define SAI_FS_BeforeFirstBit             ((uint32_t)SAI_xFRCR_FSOFF)
#define IS_SAI_BLOCK_FS_OFFSET(OFFSET) (((OFFSET) == SAI_FS_FirstBit) || \
                                        ((OFFSET) == SAI_FS_BeforeFirstBit))
/**
  * @}
  */

/** @defgroup SAI_Block_Slot_FirstBit_Offset
  * @{
  */
#define IS_SAI_BLOCK_FIRSTBIT_OFFSET(OFFSET) ((OFFSET) <= 24)

/**
  * @}
  */

/** @defgroup SAI_Block_Slot_Size
* @{
*/
#define SAI_SlotSize_DataSize             ((uint32_t)0x00000000)
#define SAI_SlotSize_16b                  ((uint32_t)SAI_xSLOTR_SLOTSZ_0)
#define SAI_SlotSize_32b                  ((uint32_t)SAI_xSLOTR_SLOTSZ_1)
#define IS_SAI_BLOCK_SLOT_SIZE(SIZE) (((SIZE) == SAI_SlotSize_DataSize) || \
                                      ((SIZE) == SAI_SlotSize_16b)      || \
                                      ((SIZE) == SAI_SlotSize_32b))

/**
  * @}
  */

/** @defgroup SAI_Block_Slot_Number
  * @{
  */
#define IS_SAI_BLOCK_SLOT_NUMBER(NUMBER) ((1 <= (NUMBER)) && ((NUMBER) <= 16))

/**
  * @}
  */

/** @defgroup SAI_Block_Slot_Active
  * @{
  */
#define SAI_Slot_NotActive           ((uint32_t)0x00000000)
#define SAI_SlotActive_0             ((uint32_t)0x00010000)
#define SAI_SlotActive_1             ((uint32_t)0x00020000)
#define SAI_SlotActive_2             ((uint32_t)0x00040000)
#define SAI_SlotActive_3             ((uint32_t)0x00080000)
#define SAI_SlotActive_4             ((uint32_t)0x00100000)
#define SAI_SlotActive_5             ((uint32_t)0x00200000)
#define SAI_SlotActive_6             ((uint32_t)0x00400000)
#define SAI_SlotActive_7             ((uint32_t)0x00800000)
#define SAI_SlotActive_8             ((uint32_t)0x01000000)
#define SAI_SlotActive_9             ((uint32_t)0x02000000)
#define SAI_SlotActive_10            ((uint32_t)0x04000000)
#define SAI_SlotActive_11            ((uint32_t)0x08000000)
#define SAI_SlotActive_12            ((uint32_t)0x10000000)
#define SAI_SlotActive_13            ((uint32_t)0x20000000)
#define SAI_SlotActive_14            ((uint32_t)0x40000000)
#define SAI_SlotActive_15            ((uint32_t)0x80000000)
#define SAI_SlotActive_ALL           ((uint32_t)0xFFFF0000)

#define IS_SAI_SLOT_ACTIVE(ACTIVE) ((ACTIVE) != 0)

/**
  * @}
  */

/** @defgroup SAI_Mono_Streo_Mode
  * @{
  */
#define SAI_MonoMode                      ((uint32_t)SAI_xCR1_MONO)
#define SAI_StreoMode                     ((uint32_t)0x00000000)
#define IS_SAI_BLOCK_MONO_STREO_MODE(MODE) (((MODE) == SAI_MonoMode) ||\
        ((MODE) == SAI_StreoMode))
/**
  * @}
  */

/** @defgroup SAI_TRIState_Management
  * @{
  */
#define SAI_Output_NotReleased              ((uint32_t)0x00000000)
#define SAI_Output_Released                 ((uint32_t)SAI_xCR2_TRIS)
#define IS_SAI_BLOCK_TRISTATE_MANAGEMENT(STATE) (((STATE) == SAI_Output_NotReleased) ||\
        ((STATE) == SAI_Output_Released))
/**
  * @}
  */

/** @defgroup SAI_Block_Fifo_Threshold
  * @{
  */
#define SAI_Threshold_FIFOEmpty           ((uint32_t)0x00000000)
#define SAI_FIFOThreshold_1QuarterFull    ((uint32_t)0x00000001)
#define SAI_FIFOThreshold_HalfFull        ((uint32_t)0x00000002)
#define SAI_FIFOThreshold_3QuartersFull   ((uint32_t)0x00000003)
#define SAI_FIFOThreshold_Full            ((uint32_t)0x00000004)
#define IS_SAI_BLOCK_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == SAI_Threshold_FIFOEmpty)         || \
        ((THRESHOLD) == SAI_FIFOThreshold_1QuarterFull)  || \
        ((THRESHOLD) == SAI_FIFOThreshold_HalfFull)      || \
        ((THRESHOLD) == SAI_FIFOThreshold_3QuartersFull) || \
        ((THRESHOLD) == SAI_FIFOThreshold_Full))
/**
  * @}
  */

/** @defgroup SAI_Block_Companding_Mode
  * @{
  */
#define SAI_NoCompanding                  ((uint32_t)0x00000000)
#define SAI_ULaw_1CPL_Companding          ((uint32_t)0x00008000)
#define SAI_ALaw_1CPL_Companding          ((uint32_t)0x0000C000)
#define SAI_ULaw_2CPL_Companding          ((uint32_t)0x0000A000)
#define SAI_ALaw_2CPL_Companding          ((uint32_t)0x0000E000)
#define IS_SAI_BLOCK_COMPANDING_MODE(MODE)    (((MODE) == SAI_NoCompanding)        || \
        ((MODE) == SAI_ULaw_1CPL_Companding) || \
        ((MODE) == SAI_ALaw_1CPL_Companding) || \
        ((MODE) == SAI_ULaw_2CPL_Companding) || \
        ((MODE) == SAI_ALaw_2CPL_Companding))
/**
  * @}
  */

/** @defgroup SAI_Block_Mute_Value
  * @{
  */
#define SAI_ZeroValue                     ((uint32_t)0x00000000)
#define SAI_LastSentValue                 ((uint32_t)SAI_xCR2_MUTEVAL)
#define IS_SAI_BLOCK_MUTE_VALUE(VALUE)    (((VALUE) == SAI_ZeroValue)     || \
        ((VALUE) == SAI_LastSentValue))
/**
  * @}
  */

/** @defgroup SAI_Block_Mute_Frame_Counter
  * @{
  */
#define IS_SAI_BLOCK_MUTE_COUNTER(COUNTER) ((COUNTER) <= 63)

/**
  * @}
  */

/** @defgroup SAI_Block_Interrupts_Definition
  * @{
  */
#define SAI_IT_OVRUDR                     ((uint32_t)SAI_xIMR_OVRUDRIE)
#define SAI_IT_MUTEDET                    ((uint32_t)SAI_xIMR_MUTEDETIE)
#define SAI_IT_WCKCFG                     ((uint32_t)SAI_xIMR_WCKCFGIE)
#define SAI_IT_FREQ                       ((uint32_t)SAI_xIMR_FREQIE)
#define SAI_IT_CNRDY                      ((uint32_t)SAI_xIMR_CNRDYIE)
#define SAI_IT_AFSDET                     ((uint32_t)SAI_xIMR_AFSDETIE)
#define SAI_IT_LFSDET                     ((uint32_t)SAI_xIMR_LFSDETIE)

#define IS_SAI_BLOCK_CONFIG_IT(IT) (((IT) == SAI_IT_OVRUDR)  || \
                                    ((IT) == SAI_IT_MUTEDET) || \
                                    ((IT) == SAI_IT_WCKCFG)  || \
                                    ((IT) == SAI_IT_FREQ)    || \
                                    ((IT) == SAI_IT_CNRDY)   || \
                                    ((IT) == SAI_IT_AFSDET)  || \
                                    ((IT) == SAI_IT_LFSDET))
/**
  * @}
  */

/** @defgroup SAI_Block_Flags_Definition
  * @{
  */
#define SAI_FLAG_OVRUDR                   ((uint32_t)SAI_xSR_OVRUDR)
#define SAI_FLAG_MUTEDET                  ((uint32_t)SAI_xSR_MUTEDET)
#define SAI_FLAG_WCKCFG                   ((uint32_t)SAI_xSR_WCKCFG)
#define SAI_FLAG_FREQ                     ((uint32_t)SAI_xSR_FREQ)
#define SAI_FLAG_CNRDY                    ((uint32_t)SAI_xSR_CNRDY)
#define SAI_FLAG_AFSDET                   ((uint32_t)SAI_xSR_AFSDET)
#define SAI_FLAG_LFSDET                   ((uint32_t)SAI_xSR_LFSDET)

#define IS_SAI_BLOCK_GET_FLAG(FLAG) (((FLAG) == SAI_FLAG_OVRUDR)  || \
                                     ((FLAG) == SAI_FLAG_MUTEDET) || \
                                     ((FLAG) == SAI_FLAG_WCKCFG)  || \
                                     ((FLAG) == SAI_FLAG_FREQ)    || \
                                     ((FLAG) == SAI_FLAG_CNRDY)   || \
                                     ((FLAG) == SAI_FLAG_AFSDET)  || \
                                     ((FLAG) == SAI_FLAG_LFSDET))

#define IS_SAI_BLOCK_CLEAR_FLAG(FLAG) (((FLAG) == SAI_FLAG_OVRUDR)  || \
                                       ((FLAG) == SAI_FLAG_MUTEDET) || \
                                       ((FLAG) == SAI_FLAG_WCKCFG)  || \
                                       ((FLAG) == SAI_FLAG_FREQ)    || \
                                       ((FLAG) == SAI_FLAG_CNRDY)   || \
                                       ((FLAG) == SAI_FLAG_AFSDET)  || \
                                       ((FLAG) == SAI_FLAG_LFSDET))
/**
  * @}
  */

/** @defgroup SAI_Block_Fifo_Status_Level
  * @{
  */
#define SAI_FIFOStatus_Empty              ((uint32_t)0x00000000)
#define SAI_FIFOStatus_Less1QuarterFull   ((uint32_t)0x00010000)
#define SAI_FIFOStatus_1QuarterFull       ((uint32_t)0x00020000)
#define SAI_FIFOStatus_HalfFull           ((uint32_t)0x00030000)
#define SAI_FIFOStatus_3QuartersFull      ((uint32_t)0x00040000)
#define SAI_FIFOStatus_Full               ((uint32_t)0x00050000)

#define IS_SAI_BLOCK_FIFO_STATUS(STATUS) (((STATUS) == SAI_FIFOStatus_Less1QuarterFull ) || \
        ((STATUS) == SAI_FIFOStatus_HalfFull)          || \
        ((STATUS) == SAI_FIFOStatus_1QuarterFull)      || \
        ((STATUS) == SAI_FIFOStatus_3QuartersFull)     || \
        ((STATUS) == SAI_FIFOStatus_Full)              || \
        ((STATUS) == SAI_FIFOStatus_Empty))
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 SAI 配置设置为默认复位状态的函数 *****/
void SAI_DeInit(SAI_TypeDef* SAIx); // 将 SAIx 外设寄存器取消初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void SAI_Init(SAI_Block_TypeDef* SAI_Block_x, SAI_InitTypeDef* SAI_InitStruct); // 根据 SAI_InitStruct 中指定的参数初始化 SAI Block x 外设。
void SAI_FrameInit(SAI_Block_TypeDef* SAI_Block_x, SAI_FrameInitTypeDef* SAI_FrameInitStruct); // 根据 SAI_FrameInitStruct 中指定的参数初始化 SAI Block Audio 帧。
void SAI_SlotInit(SAI_Block_TypeDef* SAI_Block_x, SAI_SlotInitTypeDef* SAI_SlotInitStruct); // 根据 SAI_SlotInitStruct 中指定的参数初始化 SAI Block 音频 Slot。
void SAI_StructInit(SAI_InitTypeDef* SAI_InitStruct); // 用默认值填充每个 SAI_InitStruct 成员。
void SAI_FrameStructInit(SAI_FrameInitTypeDef* SAI_FrameInitStruct); // 用默认值填充每个 SAI_FrameInitStruct 成员。
void SAI_SlotStructInit(SAI_SlotInitTypeDef* SAI_SlotInitStruct); // 用默认值填充每个 SAI_SlotInitStruct 成员。

void SAI_Cmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState); // 启用或禁用指定的 SAI Block 外设。
void SAI_MonoModeConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_Mono_StreoMode); // 为选定的 SAI 模块配置单声道模式。
void SAI_TRIStateConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_TRIState); // 为选定的 SAI 块配置数据线上的 TRIState 管理。
void SAI_CompandingModeConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_CompandingMode); // 为选定的 SAI 模块配置压扩模式。
void SAI_MuteModeCmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState); // 启用或禁用选定 SAI 模块的静音模式。
void SAI_MuteValueConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_MuteValue); // 为选定的 SAI 模块配置静音值。
void SAI_MuteFrameCounterConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_MuteCounter); // 启用或禁用选定 SAI 模块的静音模式。
void SAI_FlushFIFO(SAI_Block_TypeDef* SAI_Block_x); // 重新初始化 FIFO 指针
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
defined(STM32F469_479xx) || defined(STM32F413_423xx) || defined(STM32F446xx)
void SAI_BlockSynchroConfig(SAI_InitTypeDef* SAI_InitStruct, SAI_TypeDef* SAIx); // 配置 SAI Block 同步模式
#endif /* STM32F427xx || STM32F437xx || STM32F429xx || STM32F439xx || STM32F469_479xx || STM32F413_423xx || STM32F446xx */
/* 数据传输功能 ***************************************************/
void SAI_SendData(SAI_Block_TypeDef* SAI_Block_x, uint32_t Data); // 通过 SAI 模块 x 外设传输数据。
uint32_t SAI_ReceiveData(SAI_Block_TypeDef* SAI_Block_x); // 返回 SAI 模块 x 外设最近接收到的数据。

/* DMA 传输管理功能 *****************************************/
void SAI_DMACmd(SAI_Block_TypeDef* SAI_Block_x, FunctionalState NewState); // 启用或禁用 SAI Block x DMA 接口。

/* 中断和标志管理功能 **********************************/
void SAI_ITConfig(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT, FunctionalState NewState); // 启用或禁用指定的 SAI 块中断。
FlagStatus SAI_GetFlagStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG); // 检查是否设置了指定的 SAI 块 x 标志。
void SAI_ClearFlag(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_FLAG); // 清除指定的 SAI Block x 标志。
ITStatus SAI_GetITStatus(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT); // 检查指定的 SAI Block x 中断是否发生。
void SAI_ClearITPendingBit(SAI_Block_TypeDef* SAI_Block_x, uint32_t SAI_IT); // 清除 SAI Block x 中断挂起位。
FunctionalState SAI_GetCmdStatus(SAI_Block_TypeDef* SAI_Block_x); // 返回指定 SAI 块 x 的 EN 位的状态。
uint32_t SAI_GetFIFOStatus(SAI_Block_TypeDef* SAI_Block_x); // 返回当前 SAI 块 x FIFO 填充级别。

#endif /* STM32F40_41xxx || STM32F427_437xx || STM32F429_439xx || STM32F401xx || STM32F411xE || STM32F446xx || STM32F469_479xx */
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_SAI_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
