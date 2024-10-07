/**
  ******************************************************************************
  * 文件:    stm32f4xx_dma.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 DMA 固件库的所有功能原型.
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
#ifndef __STM32F4xx_DMA_H
#define __STM32F4xx_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup DMA
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  DMA Init structure definition
  */
typedef struct {
    uint32_t DMA_Channel;            /*!< 指定用于指定流的通道。
                                        该参数可以是 @ref DMA_channel 的值 */

    uint32_t DMA_PeripheralBaseAddr; /*!< 指定 DMAy Streamx 的外设基地址。 */

    uint32_t DMA_Memory0BaseAddr;    /*!< 指定 DMAy Streamx 的内存 0 基地址。
                                        此内存是未启用双缓冲模式时使用的默认内存。 */

    uint32_t DMA_DIR;                /*!< 指定数据是从内存传输到外设、从内存传输到内存还是从外设传输到内存。
                                        该参数可以是 @ref DMA_data_transfer_direction 的值 */

    uint32_t DMA_BufferSize;         /*!< 指定指定 Stream 的缓冲区大小，以数据为单位。
                                        根据传输方向，数据单元等于 DMA_PeripheralDataSize 或 DMA_MemoryDataSize 成员中设置的配置。 */

    uint32_t DMA_PeripheralInc;      /*!< 指定外设地址寄存器是否应该递增。
                                        该参数可以是 @ref DMA_peripheral_incremented_mode 的值 */

    uint32_t DMA_MemoryInc;          /*!< 指定内存地址寄存器是否应该递增。
                                        该参数可以是 @ref DMA_memory_incremented_mode 的值 */

    uint32_t DMA_PeripheralDataSize; /*!< 指定外设数据宽度。
                                        该参数可以是 @ref DMA_peripheral_data_size 的值 */

    uint32_t DMA_MemoryDataSize;     /*!< 指定内存数据宽度。
                                        该参数可以是 @ref DMA_memory_data_size 的值 */

    uint32_t DMA_Mode;               /*!< 指定 DMAy Streamx 的操作模式。
                                        该参数可以是 @ref DMA_circular_normal_mode @note
										                    如果在选定的Stream上配置了内存到内存的数据传输，则不能使用循环缓冲区模式 */

    uint32_t DMA_Priority;           /*!< 指定 DAY Stream 的软件优先级。
                                        该参数可以是 @ref DMA_priority_level 的值 */

    uint32_t DMA_FIFOMode;          /*!< 指定是否将 FIFO 模式或 Direct 模式用于指定的 Stream。
                                        该参数可以是 @ref DMA_fifo_direct_mode 的值 @note
										                  如果在选定的 Stream 上配置了内存到内存的数据传输，
                                        则不能使用 Direct 模式(禁用 FIFO 模式) */

    uint32_t DMA_FIFOThreshold;      /*!< 指定 FIFO 阈值级别。
                                        该参数可以是 @ref DMA_fifo_threshold_level 的值 */

    uint32_t DMA_MemoryBurst;        /*!< 指定内存传输的突发传输配置。
                                        它指定在单个不可中断事务中要传输的数据量。
										                    该参数可以是 @ref DMA_memory_burst @note 的值只有在启用地址增量模式时才可以使用突发模式。*/

    uint32_t DMA_PeripheralBurst;    /*!< 指定外设传输的突发传输配置。
                                        它指定在单个不可中断事务中要传输的数据量。
										                    这个参数可以是 @ref DMA_peripheral_burst @note 突发模式只有在地址增量模式被启用的情况下才有可能。 */
} DMA_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA_Exported_Constants
  */
#define IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Stream0) || \
                                   ((PERIPH) == DMA1_Stream1) || \
                                   ((PERIPH) == DMA1_Stream2) || \
                                   ((PERIPH) == DMA1_Stream3) || \
                                   ((PERIPH) == DMA1_Stream4) || \
                                   ((PERIPH) == DMA1_Stream5) || \
                                   ((PERIPH) == DMA1_Stream6) || \
                                   ((PERIPH) == DMA1_Stream7) || \
                                   ((PERIPH) == DMA2_Stream0) || \
                                   ((PERIPH) == DMA2_Stream1) || \
                                   ((PERIPH) == DMA2_Stream2) || \
                                   ((PERIPH) == DMA2_Stream3) || \
                                   ((PERIPH) == DMA2_Stream4) || \
                                   ((PERIPH) == DMA2_Stream5) || \
                                   ((PERIPH) == DMA2_Stream6) || \
                                   ((PERIPH) == DMA2_Stream7))

#define IS_DMA_ALL_CONTROLLER(CONTROLLER) (((CONTROLLER) == DMA1) || \
        ((CONTROLLER) == DMA2))

/** @defgroup DMA_channel
  */
#define DMA_Channel_0                     ((uint32_t)0x00000000)
#define DMA_Channel_1                     ((uint32_t)0x02000000)
#define DMA_Channel_2                     ((uint32_t)0x04000000)
#define DMA_Channel_3                     ((uint32_t)0x06000000)
#define DMA_Channel_4                     ((uint32_t)0x08000000)
#define DMA_Channel_5                     ((uint32_t)0x0A000000)
#define DMA_Channel_6                     ((uint32_t)0x0C000000)
#define DMA_Channel_7                     ((uint32_t)0x0E000000)

#define IS_DMA_CHANNEL(CHANNEL) (((CHANNEL) == DMA_Channel_0) || \
                                 ((CHANNEL) == DMA_Channel_1) || \
                                 ((CHANNEL) == DMA_Channel_2) || \
                                 ((CHANNEL) == DMA_Channel_3) || \
                                 ((CHANNEL) == DMA_Channel_4) || \
                                 ((CHANNEL) == DMA_Channel_5) || \
                                 ((CHANNEL) == DMA_Channel_6) || \
                                 ((CHANNEL) == DMA_Channel_7))


/** @defgroup DMA_data_transfer_direction
  */
#define DMA_DIR_PeripheralToMemory        ((uint32_t)0x00000000)
#define DMA_DIR_MemoryToPeripheral        ((uint32_t)0x00000040)
#define DMA_DIR_MemoryToMemory            ((uint32_t)0x00000080)

#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_DIR_PeripheralToMemory ) || \
                                     ((DIRECTION) == DMA_DIR_MemoryToPeripheral)  || \
                                     ((DIRECTION) == DMA_DIR_MemoryToMemory))


/** @defgroup DMA_data_buffer_size
  */
#define IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))


/** @defgroup DMA_peripheral_incremented_mode
  */
#define DMA_PeripheralInc_Enable          ((uint32_t)0x00000200)
#define DMA_PeripheralInc_Disable         ((uint32_t)0x00000000)

#define IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Enable) || \
        ((STATE) == DMA_PeripheralInc_Disable))


/** @defgroup DMA_memory_incremented_mode
  */
#define DMA_MemoryInc_Enable              ((uint32_t)0x00000400)
#define DMA_MemoryInc_Disable             ((uint32_t)0x00000000)

#define IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Enable) || \
                                        ((STATE) == DMA_MemoryInc_Disable))


/** @defgroup DMA_peripheral_data_size
  */
#define DMA_PeripheralDataSize_Byte       ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord   ((uint32_t)0x00000800)
#define DMA_PeripheralDataSize_Word       ((uint32_t)0x00001000)

#define IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte)  || \
        ((SIZE) == DMA_PeripheralDataSize_HalfWord) || \
        ((SIZE) == DMA_PeripheralDataSize_Word))


/** @defgroup DMA_memory_data_size
  */
#define DMA_MemoryDataSize_Byte           ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord       ((uint32_t)0x00002000)
#define DMA_MemoryDataSize_Word           ((uint32_t)0x00004000)

#define IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte)  || \
                                       ((SIZE) == DMA_MemoryDataSize_HalfWord) || \
                                       ((SIZE) == DMA_MemoryDataSize_Word ))


/** @defgroup DMA_circular_normal_mode
  */
#define DMA_Mode_Normal                   ((uint32_t)0x00000000)
#define DMA_Mode_Circular                 ((uint32_t)0x00000100)

#define IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Normal ) || \
                           ((MODE) == DMA_Mode_Circular))


/** @defgroup DMA_priority_level
  */
#define DMA_Priority_Low                  ((uint32_t)0x00000000)
#define DMA_Priority_Medium               ((uint32_t)0x00010000)
#define DMA_Priority_High                 ((uint32_t)0x00020000)
#define DMA_Priority_VeryHigh             ((uint32_t)0x00030000)

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_Low )   || \
                                   ((PRIORITY) == DMA_Priority_Medium) || \
                                   ((PRIORITY) == DMA_Priority_High)   || \
                                   ((PRIORITY) == DMA_Priority_VeryHigh))


/** @defgroup DMA_fifo_direct_mode
  */
#define DMA_FIFOMode_Disable              ((uint32_t)0x00000000)
#define DMA_FIFOMode_Enable               ((uint32_t)0x00000004)

#define IS_DMA_FIFO_MODE_STATE(STATE) (((STATE) == DMA_FIFOMode_Disable ) || \
                                       ((STATE) == DMA_FIFOMode_Enable))


/** @defgroup DMA_fifo_threshold_level
  */
#define DMA_FIFOThreshold_1QuarterFull    ((uint32_t)0x00000000)
#define DMA_FIFOThreshold_HalfFull        ((uint32_t)0x00000001)
#define DMA_FIFOThreshold_3QuartersFull   ((uint32_t)0x00000002)
#define DMA_FIFOThreshold_Full            ((uint32_t)0x00000003)

#define IS_DMA_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == DMA_FIFOThreshold_1QuarterFull ) || \
        ((THRESHOLD) == DMA_FIFOThreshold_HalfFull)      || \
        ((THRESHOLD) == DMA_FIFOThreshold_3QuartersFull) || \
        ((THRESHOLD) == DMA_FIFOThreshold_Full))


/** @defgroup DMA_memory_burst
  */
#define DMA_MemoryBurst_Single            ((uint32_t)0x00000000)
#define DMA_MemoryBurst_INC4              ((uint32_t)0x00800000)
#define DMA_MemoryBurst_INC8              ((uint32_t)0x01000000)
#define DMA_MemoryBurst_INC16             ((uint32_t)0x01800000)

#define IS_DMA_MEMORY_BURST(BURST) (((BURST) == DMA_MemoryBurst_Single) || \
                                    ((BURST) == DMA_MemoryBurst_INC4)  || \
                                    ((BURST) == DMA_MemoryBurst_INC8)  || \
                                    ((BURST) == DMA_MemoryBurst_INC16))


/** @defgroup DMA_peripheral_burst
  */
#define DMA_PeripheralBurst_Single        ((uint32_t)0x00000000)
#define DMA_PeripheralBurst_INC4          ((uint32_t)0x00200000)
#define DMA_PeripheralBurst_INC8          ((uint32_t)0x00400000)
#define DMA_PeripheralBurst_INC16         ((uint32_t)0x00600000)

#define IS_DMA_PERIPHERAL_BURST(BURST) (((BURST) == DMA_PeripheralBurst_Single) || \
                                        ((BURST) == DMA_PeripheralBurst_INC4)  || \
                                        ((BURST) == DMA_PeripheralBurst_INC8)  || \
                                        ((BURST) == DMA_PeripheralBurst_INC16))


/** @defgroup DMA_fifo_status_level
  */
#define DMA_FIFOStatus_Less1QuarterFull   ((uint32_t)0x00000000 << 3)
#define DMA_FIFOStatus_1QuarterFull       ((uint32_t)0x00000001 << 3)
#define DMA_FIFOStatus_HalfFull           ((uint32_t)0x00000002 << 3)
#define DMA_FIFOStatus_3QuartersFull      ((uint32_t)0x00000003 << 3)
#define DMA_FIFOStatus_Empty              ((uint32_t)0x00000004 << 3)
#define DMA_FIFOStatus_Full               ((uint32_t)0x00000005 << 3)

#define IS_DMA_FIFO_STATUS(STATUS) (((STATUS) == DMA_FIFOStatus_Less1QuarterFull ) || \
                                    ((STATUS) == DMA_FIFOStatus_HalfFull)          || \
                                    ((STATUS) == DMA_FIFOStatus_1QuarterFull)      || \
                                    ((STATUS) == DMA_FIFOStatus_3QuartersFull)     || \
                                    ((STATUS) == DMA_FIFOStatus_Full)              || \
                                    ((STATUS) == DMA_FIFOStatus_Empty))

/** @defgroup DMA_flags_definition
  */
#define DMA_FLAG_FEIF0                    ((uint32_t)0x10800001)
#define DMA_FLAG_DMEIF0                   ((uint32_t)0x10800004)
#define DMA_FLAG_TEIF0                    ((uint32_t)0x10000008)
#define DMA_FLAG_HTIF0                    ((uint32_t)0x10000010)
#define DMA_FLAG_TCIF0                    ((uint32_t)0x10000020)
#define DMA_FLAG_FEIF1                    ((uint32_t)0x10000040)
#define DMA_FLAG_DMEIF1                   ((uint32_t)0x10000100)
#define DMA_FLAG_TEIF1                    ((uint32_t)0x10000200)
#define DMA_FLAG_HTIF1                    ((uint32_t)0x10000400)
#define DMA_FLAG_TCIF1                    ((uint32_t)0x10000800)
#define DMA_FLAG_FEIF2                    ((uint32_t)0x10010000)
#define DMA_FLAG_DMEIF2                   ((uint32_t)0x10040000)
#define DMA_FLAG_TEIF2                    ((uint32_t)0x10080000)
#define DMA_FLAG_HTIF2                    ((uint32_t)0x10100000)
#define DMA_FLAG_TCIF2                    ((uint32_t)0x10200000)
#define DMA_FLAG_FEIF3                    ((uint32_t)0x10400000)
#define DMA_FLAG_DMEIF3                   ((uint32_t)0x11000000)
#define DMA_FLAG_TEIF3                    ((uint32_t)0x12000000)
#define DMA_FLAG_HTIF3                    ((uint32_t)0x14000000)
#define DMA_FLAG_TCIF3                    ((uint32_t)0x18000000)
#define DMA_FLAG_FEIF4                    ((uint32_t)0x20000001)
#define DMA_FLAG_DMEIF4                   ((uint32_t)0x20000004)
#define DMA_FLAG_TEIF4                    ((uint32_t)0x20000008)
#define DMA_FLAG_HTIF4                    ((uint32_t)0x20000010)
#define DMA_FLAG_TCIF4                    ((uint32_t)0x20000020)
#define DMA_FLAG_FEIF5                    ((uint32_t)0x20000040)
#define DMA_FLAG_DMEIF5                   ((uint32_t)0x20000100)
#define DMA_FLAG_TEIF5                    ((uint32_t)0x20000200)
#define DMA_FLAG_HTIF5                    ((uint32_t)0x20000400)
#define DMA_FLAG_TCIF5                    ((uint32_t)0x20000800)
#define DMA_FLAG_FEIF6                    ((uint32_t)0x20010000)
#define DMA_FLAG_DMEIF6                   ((uint32_t)0x20040000)
#define DMA_FLAG_TEIF6                    ((uint32_t)0x20080000)
#define DMA_FLAG_HTIF6                    ((uint32_t)0x20100000)
#define DMA_FLAG_TCIF6                    ((uint32_t)0x20200000)
#define DMA_FLAG_FEIF7                    ((uint32_t)0x20400000)
#define DMA_FLAG_DMEIF7                   ((uint32_t)0x21000000)
#define DMA_FLAG_TEIF7                    ((uint32_t)0x22000000)
#define DMA_FLAG_HTIF7                    ((uint32_t)0x24000000)
#define DMA_FLAG_TCIF7                    ((uint32_t)0x28000000)

#define IS_DMA_CLEAR_FLAG(FLAG) ((((FLAG) & 0x30000000) != 0x30000000) && (((FLAG) & 0x30000000) != 0) && \
                                 (((FLAG) & 0xC002F082) == 0x00) && ((FLAG) != 0x00))

#define IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA_FLAG_TCIF0)  || ((FLAG) == DMA_FLAG_HTIF0)  || \
                               ((FLAG) == DMA_FLAG_TEIF0)  || ((FLAG) == DMA_FLAG_DMEIF0) || \
                               ((FLAG) == DMA_FLAG_FEIF0)  || ((FLAG) == DMA_FLAG_TCIF1)  || \
                               ((FLAG) == DMA_FLAG_HTIF1)  || ((FLAG) == DMA_FLAG_TEIF1)  || \
                               ((FLAG) == DMA_FLAG_DMEIF1) || ((FLAG) == DMA_FLAG_FEIF1)  || \
                               ((FLAG) == DMA_FLAG_TCIF2)  || ((FLAG) == DMA_FLAG_HTIF2)  || \
                               ((FLAG) == DMA_FLAG_TEIF2)  || ((FLAG) == DMA_FLAG_DMEIF2) || \
                               ((FLAG) == DMA_FLAG_FEIF2)  || ((FLAG) == DMA_FLAG_TCIF3)  || \
                               ((FLAG) == DMA_FLAG_HTIF3)  || ((FLAG) == DMA_FLAG_TEIF3)  || \
                               ((FLAG) == DMA_FLAG_DMEIF3) || ((FLAG) == DMA_FLAG_FEIF3)  || \
                               ((FLAG) == DMA_FLAG_TCIF4)  || ((FLAG) == DMA_FLAG_HTIF4)  || \
                               ((FLAG) == DMA_FLAG_TEIF4)  || ((FLAG) == DMA_FLAG_DMEIF4) || \
                               ((FLAG) == DMA_FLAG_FEIF4)  || ((FLAG) == DMA_FLAG_TCIF5)  || \
                               ((FLAG) == DMA_FLAG_HTIF5)  || ((FLAG) == DMA_FLAG_TEIF5)  || \
                               ((FLAG) == DMA_FLAG_DMEIF5) || ((FLAG) == DMA_FLAG_FEIF5)  || \
                               ((FLAG) == DMA_FLAG_TCIF6)  || ((FLAG) == DMA_FLAG_HTIF6)  || \
                               ((FLAG) == DMA_FLAG_TEIF6)  || ((FLAG) == DMA_FLAG_DMEIF6) || \
                               ((FLAG) == DMA_FLAG_FEIF6)  || ((FLAG) == DMA_FLAG_TCIF7)  || \
                               ((FLAG) == DMA_FLAG_HTIF7)  || ((FLAG) == DMA_FLAG_TEIF7)  || \
                               ((FLAG) == DMA_FLAG_DMEIF7) || ((FLAG) == DMA_FLAG_FEIF7))


/** @defgroup DMA_interrupt_enable_definitions
  */
#define DMA_IT_TC                         ((uint32_t)0x00000010)
#define DMA_IT_HT                         ((uint32_t)0x00000008)
#define DMA_IT_TE                         ((uint32_t)0x00000004)
#define DMA_IT_DME                        ((uint32_t)0x00000002)
#define DMA_IT_FE                         ((uint32_t)0x00000080)

#define IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFF61) == 0x00) && ((IT) != 0x00))


/** @defgroup DMA_interrupts_definitions
  */
#define DMA_IT_FEIF0                      ((uint32_t)0x90000001)
#define DMA_IT_DMEIF0                     ((uint32_t)0x10001004)
#define DMA_IT_TEIF0                      ((uint32_t)0x10002008)
#define DMA_IT_HTIF0                      ((uint32_t)0x10004010)
#define DMA_IT_TCIF0                      ((uint32_t)0x10008020)
#define DMA_IT_FEIF1                      ((uint32_t)0x90000040)
#define DMA_IT_DMEIF1                     ((uint32_t)0x10001100)
#define DMA_IT_TEIF1                      ((uint32_t)0x10002200)
#define DMA_IT_HTIF1                      ((uint32_t)0x10004400)
#define DMA_IT_TCIF1                      ((uint32_t)0x10008800)
#define DMA_IT_FEIF2                      ((uint32_t)0x90010000)
#define DMA_IT_DMEIF2                     ((uint32_t)0x10041000)
#define DMA_IT_TEIF2                      ((uint32_t)0x10082000)
#define DMA_IT_HTIF2                      ((uint32_t)0x10104000)
#define DMA_IT_TCIF2                      ((uint32_t)0x10208000)
#define DMA_IT_FEIF3                      ((uint32_t)0x90400000)
#define DMA_IT_DMEIF3                     ((uint32_t)0x11001000)
#define DMA_IT_TEIF3                      ((uint32_t)0x12002000)
#define DMA_IT_HTIF3                      ((uint32_t)0x14004000)
#define DMA_IT_TCIF3                      ((uint32_t)0x18008000)
#define DMA_IT_FEIF4                      ((uint32_t)0xA0000001)
#define DMA_IT_DMEIF4                     ((uint32_t)0x20001004)
#define DMA_IT_TEIF4                      ((uint32_t)0x20002008)
#define DMA_IT_HTIF4                      ((uint32_t)0x20004010)
#define DMA_IT_TCIF4                      ((uint32_t)0x20008020)
#define DMA_IT_FEIF5                      ((uint32_t)0xA0000040)
#define DMA_IT_DMEIF5                     ((uint32_t)0x20001100)
#define DMA_IT_TEIF5                      ((uint32_t)0x20002200)
#define DMA_IT_HTIF5                      ((uint32_t)0x20004400)
#define DMA_IT_TCIF5                      ((uint32_t)0x20008800)
#define DMA_IT_FEIF6                      ((uint32_t)0xA0010000)
#define DMA_IT_DMEIF6                     ((uint32_t)0x20041000)
#define DMA_IT_TEIF6                      ((uint32_t)0x20082000)
#define DMA_IT_HTIF6                      ((uint32_t)0x20104000)
#define DMA_IT_TCIF6                      ((uint32_t)0x20208000)
#define DMA_IT_FEIF7                      ((uint32_t)0xA0400000)
#define DMA_IT_DMEIF7                     ((uint32_t)0x21001000)
#define DMA_IT_TEIF7                      ((uint32_t)0x22002000)
#define DMA_IT_HTIF7                      ((uint32_t)0x24004000)
#define DMA_IT_TCIF7                      ((uint32_t)0x28008000)

#define IS_DMA_CLEAR_IT(IT) ((((IT) & 0x30000000) != 0x30000000) && \
                             (((IT) & 0x30000000) != 0) && ((IT) != 0x00) && \
                             (((IT) & 0x40820082) == 0x00))

#define IS_DMA_GET_IT(IT) (((IT) == DMA_IT_TCIF0) || ((IT) == DMA_IT_HTIF0)  || \
                           ((IT) == DMA_IT_TEIF0) || ((IT) == DMA_IT_DMEIF0) || \
                           ((IT) == DMA_IT_FEIF0) || ((IT) == DMA_IT_TCIF1)  || \
                           ((IT) == DMA_IT_HTIF1) || ((IT) == DMA_IT_TEIF1)  || \
                           ((IT) == DMA_IT_DMEIF1)|| ((IT) == DMA_IT_FEIF1)  || \
                           ((IT) == DMA_IT_TCIF2) || ((IT) == DMA_IT_HTIF2)  || \
                           ((IT) == DMA_IT_TEIF2) || ((IT) == DMA_IT_DMEIF2) || \
                           ((IT) == DMA_IT_FEIF2) || ((IT) == DMA_IT_TCIF3)  || \
                           ((IT) == DMA_IT_HTIF3) || ((IT) == DMA_IT_TEIF3)  || \
                           ((IT) == DMA_IT_DMEIF3)|| ((IT) == DMA_IT_FEIF3)  || \
                           ((IT) == DMA_IT_TCIF4) || ((IT) == DMA_IT_HTIF4)  || \
                           ((IT) == DMA_IT_TEIF4) || ((IT) == DMA_IT_DMEIF4) || \
                           ((IT) == DMA_IT_FEIF4) || ((IT) == DMA_IT_TCIF5)  || \
                           ((IT) == DMA_IT_HTIF5) || ((IT) == DMA_IT_TEIF5)  || \
                           ((IT) == DMA_IT_DMEIF5)|| ((IT) == DMA_IT_FEIF5)  || \
                           ((IT) == DMA_IT_TCIF6) || ((IT) == DMA_IT_HTIF6)  || \
                           ((IT) == DMA_IT_TEIF6) || ((IT) == DMA_IT_DMEIF6) || \
                           ((IT) == DMA_IT_FEIF6) || ((IT) == DMA_IT_TCIF7)  || \
                           ((IT) == DMA_IT_HTIF7) || ((IT) == DMA_IT_TEIF7)  || \
                           ((IT) == DMA_IT_DMEIF7)|| ((IT) == DMA_IT_FEIF7))


/** @defgroup DMA_peripheral_increment_offset
  */
#define DMA_PINCOS_Psize                  ((uint32_t)0x00000000)
#define DMA_PINCOS_WordAligned            ((uint32_t)0x00008000)

#define IS_DMA_PINCOS_SIZE(SIZE) (((SIZE) == DMA_PINCOS_Psize) || \
                                  ((SIZE) == DMA_PINCOS_WordAligned))


/** @defgroup DMA_flow_controller_definitions
  */
#define DMA_FlowCtrl_Memory               ((uint32_t)0x00000000)
#define DMA_FlowCtrl_Peripheral           ((uint32_t)0x00000020)

#define IS_DMA_FLOW_CTRL(CTRL) (((CTRL) == DMA_FlowCtrl_Memory) || \
                                ((CTRL) == DMA_FlowCtrl_Peripheral))


/** @defgroup DMA_memory_targets_definitions
  */
#define DMA_Memory_0                      ((uint32_t)0x00000000)
#define DMA_Memory_1                      ((uint32_t)0x00080000)

#define IS_DMA_CURRENT_MEM(MEM) (((MEM) == DMA_Memory_0) || ((MEM) == DMA_Memory_1))


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 DMA 配置设置为默认复位状态的函数 *****/
void DMA_DeInit(DMA_Stream_TypeDef* DMAy_Streamx); // 将 DMAy Streamx 寄存器取消初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void DMA_Init(DMA_Stream_TypeDef* DMAy_Streamx, DMA_InitTypeDef* DMA_InitStruct); // 根据 DMA_InitStruct 结构中的指定参数初始化 DMAy Streamx。
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct); // 用默认值填充每个 DMA_InitStruct 成员。
void DMA_Cmd(DMA_Stream_TypeDef* DMAy_Streamx, FunctionalState NewState); // 启用或禁用指定的 DMAy Streamx。

/* 可选配置功能 *******************************************/
void DMA_PeriphIncOffsetSizeConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_Pincos); /* 设置 PINC(外设增量地址模式)位时，
																							配置外设地址是否应随数据大小(使用 PSIZE 位配置)或等于 4 的固定偏移量(32 位对齐地址)递增。*/
void DMA_FlowControllerConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FlowCtrl); // 当禁用 DMAy Streamx 时，配置下一个事务(外设或内存)的流控制器。

/* 数据计数器功能 *****************************************************/
void DMA_SetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx, uint16_t Counter); // 写入要在 DMAy Streamx 上传输的数据单元的数量。
uint16_t DMA_GetCurrDataCounter(DMA_Stream_TypeDef* DMAy_Streamx); // 返回当前 DMAy Streamx 传输中剩余数据单元的数量。

/* 双缓冲模式功能 ***********************************************/
void DMA_DoubleBufferModeConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t Memory1BaseAddr,
                                uint32_t DMA_CurrentMemory); // 当禁用 DMAy Streamx 时，配置双缓冲模式和当前内存目标。
void DMA_DoubleBufferModeCmd(DMA_Stream_TypeDef* DMAy_Streamx, FunctionalState NewState); // 启用或禁用选定 DMA 流的双缓冲模式。
void DMA_MemoryTargetConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t MemoryBaseAddr,
                            uint32_t DMA_MemoryTarget); // 为双缓冲区模式下的下一个缓冲区传输配置内存地址(用于动态使用)。
uint32_t DMA_GetCurrentMemoryTarget(DMA_Stream_TypeDef* DMAy_Streamx); // 返回双缓冲区传输使用的当前内存目标。

/* 中断和标志管理功能 **********************************/
FunctionalState DMA_GetCmdStatus(DMA_Stream_TypeDef* DMAy_Streamx); // 返回指定 DMAy Streamx 的 EN 位的状态。
uint32_t DMA_GetFIFOStatus(DMA_Stream_TypeDef* DMAy_Streamx); // 返回当前的 DMAy Streamx FIFO 填充级别。
FlagStatus DMA_GetFlagStatus(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FLAG); // 检查是否设置了指定的 DMAy Streamx 标志。
void DMA_ClearFlag(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_FLAG); // 清除 DMAy Streamx 的挂起标志。
void DMA_ITConfig(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT, FunctionalState NewState); // 启用或禁用指定的 DMAy Streamx 中断。
ITStatus DMA_GetITStatus(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT); // 检查是否发生了指定的 DMAy Streamx 中断。
void DMA_ClearITPendingBit(DMA_Stream_TypeDef* DMAy_Streamx, uint32_t DMA_IT); // 清除 DMAy Streamx 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_DMA_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
