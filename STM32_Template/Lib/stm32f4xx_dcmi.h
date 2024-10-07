/**
  ******************************************************************************
  * 文件:    stm32f4xx_dcmi.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 DCMI 固件库的所有功能原型.
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
#ifndef __STM32F4xx_DCMI_H
#define __STM32F4xx_DCMI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup DCMI
  */

/* Exported types ------------------------------------------------------------*/
/**
  * 简介:    DCMI 初始化结构定义
  */
typedef struct {
    uint16_t DCMI_CaptureMode;      /*!< 指定捕捉模式:连续或快照。
									                  该参数可以是 @ref DCMI_Capture_Mode 的值 */

    uint16_t DCMI_SynchroMode;      /*!< 指定同步模式:硬件或嵌入式。
									                  该参数可以是 @ref DCMI_Synchronization_Mode 的值 */

    uint16_t DCMI_PCKPolarity;      /*!< 指定像素时钟极性:下降或上升。
									                  该参数可以是 @ref DCMI_PIXCK_Polarity 的值 */

    uint16_t DCMI_VSPolarity;       /*!< 指定垂直同步极性:高或低。
									                  该参数可以是 @ref DCMI_VSYNC_Polarity 的值 */

    uint16_t DCMI_HSPolarity;       /*!< 指定水平同步极性:高或低。
									                  该参数可以是 @ref DCMI_HSYNC_Polarity 的值 */

    uint16_t DCMI_CaptureRate;      /*!< 指定帧捕获的频率:全部、1/2 或 1/4。
									                  该参数可以是 @ref DCMI_Capture_Rate 的值 */

    uint16_t DCMI_ExtendedDataMode; /*!< 指定数据宽度:8 位、10 位、12 位或 14 位。
									                  该参数可以是 @ref DCMI_Extended_Data_Mode 的值 */
} DCMI_InitTypeDef;

/**
  * 简介:    DCMI CROP Init 结构定义
  */
typedef struct {
    uint16_t DCMI_VerticalStartLine;      /*!< 指定图像捕获将从其开始的垂直起始行数。
											                    此参数可以是 0x00 和 0x1FFF 之间的值 */

    uint16_t DCMI_HorizontalOffsetCount;  /*!< 指定开始捕获之前要计数的像素时钟数。
											                    此参数可以是 0x00 和 0x3FFF 之间的值 */

    uint16_t DCMI_VerticalLineCount;      /*!< 指定要从起点捕获的行数。
											                    此参数可以是 0x00 和 0x3FFF 之间的值 */

    uint16_t DCMI_CaptureCount;           /*!< 指定要从同一行的起点捕获的像素时钟数。
											                    此参数可以是 0x00 和 0x3FFF 之间的值 */
} DCMI_CROPInitTypeDef;

/**
  * 简介:    DCMI 嵌入式同步代码初始化结构定义
  */
typedef struct {
    uint8_t DCMI_FrameStartCode; /*!< 指定帧起始分隔符的代码。 */
    uint8_t DCMI_LineStartCode;  /*!< 指定行起始分隔符的代码。 */
    uint8_t DCMI_LineEndCode;    /*!< 指定行尾分隔符的代码。 */
    uint8_t DCMI_FrameEndCode;   /*!< 指定帧结束分隔符的代码。 */
} DCMI_CodesInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DCMI_Exported_Constants
  */

/** @defgroup DCMI_Capture_Mode
  */
#define DCMI_CaptureMode_Continuous    ((uint16_t)0x0000) /*!< 接收到的数据通过 DMA 连续传输到目标存储器 */
#define DCMI_CaptureMode_SnapShot      ((uint16_t)0x0002) /*!< 激活后，接口等待帧开始，然后通过 DMA 传输单个帧 */
#define IS_DCMI_CAPTURE_MODE(MODE)(((MODE) == DCMI_CaptureMode_Continuous) || \
                                   ((MODE) == DCMI_CaptureMode_SnapShot))


/** @defgroup DCMI_Synchronization_Mode
  */
#define DCMI_SynchroMode_Hardware    ((uint16_t)0x0000) /*!< 硬件同步数据捕获(帧/行开始/停止)与 HSYNC/VSYNC 信号同步 */
#define DCMI_SynchroMode_Embedded    ((uint16_t)0x0010) /*!< 嵌入式同步数据捕获与嵌入在数据流中的同步代码同步 */
#define IS_DCMI_SYNCHRO(MODE)(((MODE) == DCMI_SynchroMode_Hardware) || \
                              ((MODE) == DCMI_SynchroMode_Embedded))


/** @defgroup DCMI_PIXCK_Polarity
  */
#define DCMI_PCKPolarity_Falling    ((uint16_t)0x0000) /*!< 像素时钟在下降沿有效*/
#define DCMI_PCKPolarity_Rising     ((uint16_t)0x0020) /*!< 像素时钟在上升沿有效 */
#define IS_DCMI_PCKPOLARITY(POLARITY)(((POLARITY) == DCMI_PCKPolarity_Falling) || \
                                      ((POLARITY) == DCMI_PCKPolarity_Rising))


/** @defgroup DCMI_VSYNC_Polarity
  */
#define DCMI_VSPolarity_Low     ((uint16_t)0x0000) /*!< 垂直同步有效低 */
#define DCMI_VSPolarity_High    ((uint16_t)0x0080) /*!< 垂直同步有效高 */
#define IS_DCMI_VSPOLARITY(POLARITY)(((POLARITY) == DCMI_VSPolarity_Low) || \
                                     ((POLARITY) == DCMI_VSPolarity_High))


/** @defgroup DCMI_HSYNC_Polarity
  */
#define DCMI_HSPolarity_Low     ((uint16_t)0x0000) /*!< 水平同步有效 低 */
#define DCMI_HSPolarity_High    ((uint16_t)0x0040) /*!< 水平同步高电平有效 */
#define IS_DCMI_HSPOLARITY(POLARITY)(((POLARITY) == DCMI_HSPolarity_Low) || \
                                     ((POLARITY) == DCMI_HSPolarity_High))


/** @defgroup DCMI_Capture_Rate
  */
#define DCMI_CaptureRate_All_Frame     ((uint16_t)0x0000) /*!< 捕获所有帧 */
#define DCMI_CaptureRate_1of2_Frame    ((uint16_t)0x0100) /*!< 捕获的每个交替帧 */
#define DCMI_CaptureRate_1of4_Frame    ((uint16_t)0x0200) /*!< 捕获 4 帧中的一帧 */
#define IS_DCMI_CAPTURE_RATE(RATE) (((RATE) == DCMI_CaptureRate_All_Frame) || \
                                    ((RATE) == DCMI_CaptureRate_1of2_Frame) ||\
                                    ((RATE) == DCMI_CaptureRate_1of4_Frame))


/** @defgroup DCMI_Extended_Data_Mode
  */
#define DCMI_ExtendedDataMode_8b     ((uint16_t)0x0000) /*!< 接口在每个像素时钟上捕获 8 位数据 */
#define DCMI_ExtendedDataMode_10b    ((uint16_t)0x0400) /*!< 接口在每个像素时钟上捕获 10 位数据 */
#define DCMI_ExtendedDataMode_12b    ((uint16_t)0x0800) /*!< 接口在每个像素时钟上捕获 12 位数据 */
#define DCMI_ExtendedDataMode_14b    ((uint16_t)0x0C00) /*!< 接口在每个像素时钟上捕获 14 位数据 */
#define IS_DCMI_EXTENDED_DATA(DATA)(((DATA) == DCMI_ExtendedDataMode_8b) || \
                                    ((DATA) == DCMI_ExtendedDataMode_10b) ||\
                                    ((DATA) == DCMI_ExtendedDataMode_12b) ||\
                                    ((DATA) == DCMI_ExtendedDataMode_14b))


/** @defgroup DCMI_interrupt_sources
  */
#define DCMI_IT_FRAME    ((uint16_t)0x0001)
#define DCMI_IT_OVF      ((uint16_t)0x0002)
#define DCMI_IT_ERR      ((uint16_t)0x0004)
#define DCMI_IT_VSYNC    ((uint16_t)0x0008)
#define DCMI_IT_LINE     ((uint16_t)0x0010)
#define IS_DCMI_CONFIG_IT(IT) ((((IT) & (uint16_t)0xFFE0) == 0x0000) && ((IT) != 0x0000))
#define IS_DCMI_GET_IT(IT) (((IT) == DCMI_IT_FRAME) || \
                            ((IT) == DCMI_IT_OVF) || \
                            ((IT) == DCMI_IT_ERR) || \
                            ((IT) == DCMI_IT_VSYNC) || \
                            ((IT) == DCMI_IT_LINE))


/** @defgroup DCMI_Flags
  */
/**
  * 简介:    DCMI SR 寄存器
  */
#define DCMI_FLAG_HSYNC     ((uint16_t)0x2001)
#define DCMI_FLAG_VSYNC     ((uint16_t)0x2002)
#define DCMI_FLAG_FNE       ((uint16_t)0x2004)
/**
  * 简介:    DCMI RISR 寄存器
  */
#define DCMI_FLAG_FRAMERI    ((uint16_t)0x0001)
#define DCMI_FLAG_OVFRI      ((uint16_t)0x0002)
#define DCMI_FLAG_ERRRI      ((uint16_t)0x0004)
#define DCMI_FLAG_VSYNCRI    ((uint16_t)0x0008)
#define DCMI_FLAG_LINERI     ((uint16_t)0x0010)
/**
  * 简介:    DCMI MISR 寄存器
  */
#define DCMI_FLAG_FRAMEMI    ((uint16_t)0x1001)
#define DCMI_FLAG_OVFMI      ((uint16_t)0x1002)
#define DCMI_FLAG_ERRMI      ((uint16_t)0x1004)
#define DCMI_FLAG_VSYNCMI    ((uint16_t)0x1008)
#define DCMI_FLAG_LINEMI     ((uint16_t)0x1010)
#define IS_DCMI_GET_FLAG(FLAG) (((FLAG) == DCMI_FLAG_HSYNC) || \
                                ((FLAG) == DCMI_FLAG_VSYNC) || \
                                ((FLAG) == DCMI_FLAG_FNE) || \
                                ((FLAG) == DCMI_FLAG_FRAMERI) || \
                                ((FLAG) == DCMI_FLAG_OVFRI) || \
                                ((FLAG) == DCMI_FLAG_ERRRI) || \
                                ((FLAG) == DCMI_FLAG_VSYNCRI) || \
                                ((FLAG) == DCMI_FLAG_LINERI) || \
                                ((FLAG) == DCMI_FLAG_FRAMEMI) || \
                                ((FLAG) == DCMI_FLAG_OVFMI) || \
                                ((FLAG) == DCMI_FLAG_ERRMI) || \
                                ((FLAG) == DCMI_FLAG_VSYNCMI) || \
                                ((FLAG) == DCMI_FLAG_LINEMI))

#define IS_DCMI_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFFE0) == 0x0000) && ((FLAG) != 0x0000))


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/*  用于将 DCMI 配置设置为默认复位状态的函数 ****/
void DCMI_DeInit(void); // 将 DCMI 寄存器取消初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void DCMI_Init(DCMI_InitTypeDef* DCMI_InitStruct); // 根据 DCMI_InitStruct 中指定的参数初始化 DCMI。
void DCMI_StructInit(DCMI_InitTypeDef* DCMI_InitStruct); // 用默认值填充每个 DCMI_InitStruct 成员。
void DCMI_CROPConfig(DCMI_CROPInitTypeDef* DCMI_CROPInitStruct); // 根据 DCMI_CROPInitStruct 中指定的参数初始化 DCMI 外设 CROP 模式。
void DCMI_CROPCmd(FunctionalState NewState); // 启用或禁用 DCMI 裁剪功能。
void DCMI_SetEmbeddedSynchroCodes(DCMI_CodesInitTypeDef* DCMI_CodesInitStruct); // 设置嵌入式同步代码。
void DCMI_JPEGCmd(FunctionalState NewState); // 启用或禁用 DCMI JPEG 格式。

/* 图像捕捉功能 ****************************************************/
void DCMI_Cmd(FunctionalState NewState); // 启用或禁用 DCMI 接口。
void DCMI_CaptureCmd(FunctionalState NewState); // 启用或禁用 DCMI 捕获。
uint32_t DCMI_ReadData(void); // 读取存储在 DR 寄存器中的数据。

/* 中断和标志管理功能 **********************************/
void DCMI_ITConfig(uint16_t DCMI_IT, FunctionalState NewState); // 启用或禁用 DCMI 接口中断。
FlagStatus DCMI_GetFlagStatus(uint16_t DCMI_FLAG); // 检查是否设置了 DCMI 接口标志。
void DCMI_ClearFlag(uint16_t DCMI_FLAG); // 清除 DCMI 的挂起标志。
ITStatus DCMI_GetITStatus(uint16_t DCMI_IT); // 检查是否发生了 DCMI 中断。
void DCMI_ClearITPendingBit(uint16_t DCMI_IT); // 清除 DCMI 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_DCMI_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
