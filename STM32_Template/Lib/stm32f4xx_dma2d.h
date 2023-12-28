/**
  ******************************************************************************
  * 文件:    stm32f4xx_dma2d.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 DMA2D 固件库的所有功能原型.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_DMA2D_H
#define __STM32F4xx_DMA2D_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup DMA2D
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  DMA2D Init 结构定义
  */
typedef struct {
    uint32_t DMA2D_Mode;                           /*!< 配置 DMA2D 传输模式。
												                           该参数可以是@ref DMA2D_MODE 的一个值 */

    uint32_t DMA2D_CMode;                          /*!< 配置输出图像的颜色格式。
												                           该参数可以是@ref DMA2D_CMODE 的一个值 */

    uint32_t DMA2D_OutputBlue;                     /*!< 配置输出图像的蓝色值。
                          												 此参数必须范围:
                                                   - 如果选择 ARGB8888 颜色模式，则从 0x00 到 0xFF
                          												 - 如果选择 RGB888 颜色模式，则从 0x00 到 0xFF
                          												 - 如果选择 RGB565 颜色模式，则从 0x00 到 0x1F
                          												 - 如果选择 ARGB1555 颜色模式，则从 0x00 到 0x1F
                          												 - 如果选择 ARGB4444 颜色模式，则从 0x00 到 0x0F  */

    uint32_t DMA2D_OutputGreen;                    /*!< 配置输出图像的绿色值。
                          												 此参数必须范围:
                          												 - 如果选择 ARGB8888 颜色模式，则从 0x00 到 0xFF
                          												 - 如果选择了 RGB888 颜色模式，则从 0x00 到 0xFF
                          												 - 如果选择了 RGB565 颜色模式，则从 0x00 到 0x2F
                          												 - 如果选择 ARGB1555 颜色模式，则从 0x00 到 0x1F
                          												 - 如果选择 ARGB4444 颜色模式，则从 0x00 到 0x0F  */

    uint32_t DMA2D_OutputRed;                      /*!< 配置输出图像的红色值。
                          												 此参数必须范围:
                          												 - 如果选择 ARGB8888 颜色模式，则从 0x00 到 0xFF
                          												 - 如果选择 RGB888 颜色模式，则从 0x00 到 0xFF
                          												 - 如果选择 RGB565 颜色模式，则从 0x00 到 0x1F
                          												 - 如果选择 ARGB1555 颜色模式，则从 0x00 到 0x1F
                          												 - 如果选择 ARGB4444 颜色模式，则从 0x00 到 0x0F  */

    uint32_t DMA2D_OutputAlpha;                    /*!< 配置输出颜色的 alpha 通道。
                          												 此参数必须范围:
                          												 - 如果选择 ARGB8888 颜色模式，则从 0x00 到 0xFF
                          												 - 如果选择 ARGB1555 颜色模式，则从 0x00 到 0x01
                          												 - 如果选择 ARGB4444 颜色模式，则从 0x00 到 0x0F  */

    uint32_t DMA2D_OutputMemoryAdd;                /*!< 指定内存地址。 
                                                   此参数的范围必须为 0x00000000 到 0xFFFFFFFF。 */

    uint32_t DMA2D_OutputOffset;                   /*!< 指定偏移值。 
                                                   该参数的范围必须是 0x0000 到 0x3FFF。 */

    uint32_t DMA2D_NumberOfLine;                   /*!< 配置要转移的区域的线路数。
												                           此参数的范围必须为 0x0000 到 0xFFFF */

    uint32_t DMA2D_PixelPerLine;                   /*!< 配置要传输的区域的每行像素数。
												                           该参数的范围必须是 0x0000 到 0x3FFF */
} DMA2D_InitTypeDef;

typedef struct {
    uint32_t DMA2D_FGMA;                           /*!< 配置 DMA2D 前台内存地址。
												                            此参数的范围必须为 0x00000000 到 0xFFFFFFFF。*/

    uint32_t DMA2D_FGO;                            /*!< 配置 DMA2D 前景偏移。
												                            该参数的范围必须是 0x0000 到 0x3FFF。 */

    uint32_t DMA2D_FGCM;                           /*!< 配置 DMA2D 前景色模式。
												                            该参数可以是@ref DMA2D_FGCM 的一个值 */

    uint32_t DMA2D_FG_CLUT_CM;                     /*!< 配置 DMA2D 前景 CLUT 颜色模式。
												                            该参数可以是@ref DMA2D_FG_CLUT_CM 的一个值 */

    uint32_t DMA2D_FG_CLUT_SIZE;                   /*!< 配置 DMA2D 前台 CLUT 大小。
												                            此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t DMA2D_FGPFC_ALPHA_MODE;               /*!< 配置 DMA2D 前景 alpha 模式。
												                            该参数可以是@ref DMA2D_FGPFC_ALPHA_MODE 的一个值 */

    uint32_t DMA2D_FGPFC_ALPHA_VALUE;              /*!< 指定 DMA2D 前景 alpha 值必须在 0x00 到 0xFF 的范围内。 */

    uint32_t DMA2D_FGC_BLUE;                       /*!< 指定 DMA2D 前景蓝色值必须在 0x00 到 0xFF 的范围内。 */

    uint32_t DMA2D_FGC_GREEN;                      /*!< 指定 DMA2D 前景绿色值必须在 0x00 到 0xFF 的范围内。 */

    uint32_t DMA2D_FGC_RED;                        /*!< 指定 DMA2D 前景红色值必须在 0x00 到 0xFF 的范围内。 */

    uint32_t DMA2D_FGCMAR;                         /*!< 配置 DMA2D 前台 CLUT 内存地址。
												                            此参数的范围必须为 0x00000000 到 0xFFFFFFFF。 */
} DMA2D_FG_InitTypeDef;

typedef struct {
    uint32_t DMA2D_BGMA;                           /*!< 配置 DMA2D 后台内存地址。
												                            此参数的范围必须为 0x00000000 到 0xFFFFFFFF。 */

    uint32_t DMA2D_BGO;                            /*!< 配置 DMA2D 背景偏移。
												                            该参数的范围必须是 0x0000 到 0x3FFF。 */

    uint32_t DMA2D_BGCM;                           /*!< 配置 DMA2D 背景颜色模式。
												                            该参数可以是@ref DMA2D_FGCM 的一个值 */

    uint32_t DMA2D_BG_CLUT_CM;                     /*!< 配置 DMA2D 背景 CLUT 颜色模式。
												                            该参数可以是@ref DMA2D_FG_CLUT_CM 的一个值 */

    uint32_t DMA2D_BG_CLUT_SIZE;                   /*!< 配置 DMA2D 背景 CLUT 大小。
												                            此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t DMA2D_BGPFC_ALPHA_MODE;               /*!< 配置 DMA2D 背景 alpha 模式。
												                            该参数可以是@ref DMA2D_FGPFC_ALPHA_MODE 的一个值 */

    uint32_t DMA2D_BGPFC_ALPHA_VALUE;              /*!< 指定 DMA2D 背景 alpha 值必须在 0x00 到 0xFF 的范围内。 */

    uint32_t DMA2D_BGC_BLUE;                       /*!< 指定 DMA2D 背景蓝色值必须在 0x00 到 0xFF 的范围内。 */

    uint32_t DMA2D_BGC_GREEN;                      /*!< 指定 DMA2D 背景绿色值必须在 0x00 到 0xFF 的范围内。 */

    uint32_t DMA2D_BGC_RED;                        /*!< 指定 DMA2D 背景红色值必须在 0x00 到 0xFF 的范围内。 */

    uint32_t DMA2D_BGCMAR;                         /*!< 配置 DMA2D 后台 CLUT 内存地址。
												                            此参数的范围必须为 0x00000000 到 0xFFFFFFFF。 */
} DMA2D_BG_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup DMA2D_Exported_Constants
  * @{
  */

/** @defgroup DMA2D_MODE
  * @{
  */
#define DMA2D_M2M                            ((uint32_t)0x00000000)
#define DMA2D_M2M_PFC                        ((uint32_t)0x00010000)
#define DMA2D_M2M_BLEND                      ((uint32_t)0x00020000)
#define DMA2D_R2M                            ((uint32_t)0x00030000)

#define IS_DMA2D_MODE(MODE) (((MODE) == DMA2D_M2M) || ((MODE) == DMA2D_M2M_PFC) || \
                             ((MODE) == DMA2D_M2M_BLEND) || ((MODE) == DMA2D_R2M))


/**
  * @}
  */

/** @defgroup DMA2D_CMODE
  * @{
  */
#define DMA2D_ARGB8888                       ((uint32_t)0x00000000)
#define DMA2D_RGB888                         ((uint32_t)0x00000001)
#define DMA2D_RGB565                         ((uint32_t)0x00000002)
#define DMA2D_ARGB1555                       ((uint32_t)0x00000003)
#define DMA2D_ARGB4444                       ((uint32_t)0x00000004)

#define IS_DMA2D_CMODE(MODE_ARGB) (((MODE_ARGB) == DMA2D_ARGB8888) || ((MODE_ARGB) == DMA2D_RGB888) || \
                                   ((MODE_ARGB) == DMA2D_RGB565) || ((MODE_ARGB) == DMA2D_ARGB1555) || \
                                   ((MODE_ARGB) == DMA2D_ARGB4444))

/**
  * @}
  */

/** @defgroup DMA2D_OUTPUT_COLOR
  * @{
  */
#define DMA2D_Output_Color                 ((uint32_t)0x000000FF)

#define IS_DMA2D_OGREEN(OGREEN) ((OGREEN) <= DMA2D_Output_Color)
#define IS_DMA2D_ORED(ORED)     ((ORED) <= DMA2D_Output_Color)
#define IS_DMA2D_OBLUE(OBLUE)   ((OBLUE) <= DMA2D_Output_Color)
#define IS_DMA2D_OALPHA(OALPHA) ((OALPHA) <= DMA2D_Output_Color)

/**
  * @}
  */

/** @defgroup DMA2D_OUTPUT_OFFSET
  * @{
  */
#define DMA2D_OUTPUT_OFFSET      ((uint32_t)0x00003FFF)

#define IS_DMA2D_OUTPUT_OFFSET(OOFFSET) ((OOFFSET) <= DMA2D_OUTPUT_OFFSET)

/**
  * @}
  */

/** @defgroup DMA2D_SIZE
  * @{
  */
#define DMA2D_pixel          ((uint32_t)0x00003FFF)
#define DMA2D_Line           ((uint32_t)0x0000FFFF)

#define IS_DMA2D_LINE(LINE)  ((LINE) <= DMA2D_Line)
#define IS_DMA2D_PIXEL(PIXEL) ((PIXEL) <= DMA2D_pixel)

/**
  * @}
  */

/** @defgroup DMA2D_OFFSET
  * @{
  */
#define OFFSET               ((uint32_t)0x00003FFF)

#define IS_DMA2D_FGO(FGO)  ((FGO) <= OFFSET)

#define IS_DMA2D_BGO(BGO)  ((BGO) <= OFFSET)

/**
  * @}
  */


/** @defgroup DMA2D_FGCM
  * @{
  */
#define CM_ARGB8888        ((uint32_t)0x00000000)
#define CM_RGB888          ((uint32_t)0x00000001)
#define CM_RGB565          ((uint32_t)0x00000002)
#define CM_ARGB1555        ((uint32_t)0x00000003)
#define CM_ARGB4444        ((uint32_t)0x00000004)
#define CM_L8              ((uint32_t)0x00000005)
#define CM_AL44            ((uint32_t)0x00000006)
#define CM_AL88            ((uint32_t)0x00000007)
#define CM_L4              ((uint32_t)0x00000008)
#define CM_A8              ((uint32_t)0x00000009)
#define CM_A4              ((uint32_t)0x0000000A)

#define IS_DMA2D_FGCM(FGCM) (((FGCM) == CM_ARGB8888) || ((FGCM) == CM_RGB888) || \
                             ((FGCM) == CM_RGB565) || ((FGCM) == CM_ARGB1555) || \
                             ((FGCM) == CM_ARGB4444) || ((FGCM) == CM_L8) || \
                             ((FGCM) == CM_AL44) || ((FGCM) == CM_AL88) || \
                             ((FGCM) == CM_L4) || ((FGCM) == CM_A8) || \
                             ((FGCM) == CM_A4))

#define IS_DMA2D_BGCM(BGCM) (((BGCM) == CM_ARGB8888) || ((BGCM) == CM_RGB888) || \
                             ((BGCM) == CM_RGB565) || ((BGCM) == CM_ARGB1555) || \
                             ((BGCM) == CM_ARGB4444) || ((BGCM) == CM_L8) || \
                             ((BGCM) == CM_AL44) || ((BGCM) == CM_AL88) || \
                             ((BGCM) == CM_L4) || ((BGCM) == CM_A8) || \
                             ((BGCM) == CM_A4))

/**
  * @}
  */

/** @defgroup DMA2D_FG_CLUT_CM
  * @{
  */
#define CLUT_CM_ARGB8888        ((uint32_t)0x00000000)
#define CLUT_CM_RGB888          ((uint32_t)0x00000001)

#define IS_DMA2D_FG_CLUT_CM(FG_CLUT_CM) (((FG_CLUT_CM) == CLUT_CM_ARGB8888) || ((FG_CLUT_CM) == CLUT_CM_RGB888))

#define IS_DMA2D_BG_CLUT_CM(BG_CLUT_CM) (((BG_CLUT_CM) == CLUT_CM_ARGB8888) || ((BG_CLUT_CM) == CLUT_CM_RGB888))

/**
  * @}
  */

/** @defgroup DMA2D_FG_COLOR_VALUE
  * @{
  */
#define COLOR_VALUE             ((uint32_t)0x000000FF)

#define IS_DMA2D_FG_CLUT_SIZE(FG_CLUT_SIZE) ((FG_CLUT_SIZE) <= COLOR_VALUE)

#define IS_DMA2D_FG_ALPHA_VALUE(FG_ALPHA_VALUE) ((FG_ALPHA_VALUE) <= COLOR_VALUE)
#define IS_DMA2D_FGC_BLUE(FGC_BLUE) ((FGC_BLUE) <= COLOR_VALUE)
#define IS_DMA2D_FGC_GREEN(FGC_GREEN) ((FGC_GREEN) <= COLOR_VALUE)
#define IS_DMA2D_FGC_RED(FGC_RED) ((FGC_RED) <= COLOR_VALUE)

#define IS_DMA2D_BG_CLUT_SIZE(BG_CLUT_SIZE) ((BG_CLUT_SIZE) <= COLOR_VALUE)

#define IS_DMA2D_BG_ALPHA_VALUE(BG_ALPHA_VALUE) ((BG_ALPHA_VALUE) <= COLOR_VALUE)
#define IS_DMA2D_BGC_BLUE(BGC_BLUE) ((BGC_BLUE) <= COLOR_VALUE)
#define IS_DMA2D_BGC_GREEN(BGC_GREEN) ((BGC_GREEN) <= COLOR_VALUE)
#define IS_DMA2D_BGC_RED(BGC_RED) ((BGC_RED) <= COLOR_VALUE)

/**
  * @}
  */

/** DMA2D_FGPFC_ALPHA_MODE
  * @{
  */
#define NO_MODIF_ALPHA_VALUE       ((uint32_t)0x00000000)
#define REPLACE_ALPHA_VALUE        ((uint32_t)0x00000001)
#define COMBINE_ALPHA_VALUE        ((uint32_t)0x00000002)

#define IS_DMA2D_FG_ALPHA_MODE(FG_ALPHA_MODE) (((FG_ALPHA_MODE) ==  NO_MODIF_ALPHA_VALUE) || \
        ((FG_ALPHA_MODE) == REPLACE_ALPHA_VALUE) || \
        ((FG_ALPHA_MODE) == COMBINE_ALPHA_VALUE))

#define IS_DMA2D_BG_ALPHA_MODE(BG_ALPHA_MODE) (((BG_ALPHA_MODE) ==  NO_MODIF_ALPHA_VALUE) || \
        ((BG_ALPHA_MODE) == REPLACE_ALPHA_VALUE) || \
        ((BG_ALPHA_MODE) == COMBINE_ALPHA_VALUE))

/**
  * @}
  */

/** @defgroup DMA2D_Interrupts
  * @{
  */
#define DMA2D_IT_CE                      DMA2D_CR_CEIE
#define DMA2D_IT_CTC                     DMA2D_CR_CTCIE
#define DMA2D_IT_CAE                     DMA2D_CR_CAEIE
#define DMA2D_IT_TW                      DMA2D_CR_TWIE
#define DMA2D_IT_TC                      DMA2D_CR_TCIE
#define DMA2D_IT_TE                      DMA2D_CR_TEIE

#define IS_DMA2D_IT(IT) (((IT) == DMA2D_IT_CTC) || ((IT) == DMA2D_IT_CAE) || \
                         ((IT) == DMA2D_IT_TW) || ((IT) == DMA2D_IT_TC) || \
                         ((IT) == DMA2D_IT_TE) || ((IT) == DMA2D_IT_CE))

/**
  * @}
  */

/** @defgroup DMA2D_Flag
  * @{
  */
#define DMA2D_FLAG_CE                      DMA2D_ISR_CEIF
#define DMA2D_FLAG_CTC                     DMA2D_ISR_CTCIF
#define DMA2D_FLAG_CAE                     DMA2D_ISR_CAEIF
#define DMA2D_FLAG_TW                      DMA2D_ISR_TWIF
#define DMA2D_FLAG_TC                      DMA2D_ISR_TCIF
#define DMA2D_FLAG_TE                      DMA2D_ISR_TEIF


#define IS_DMA2D_GET_FLAG(FLAG) (((FLAG) == DMA2D_FLAG_CTC) || ((FLAG) == DMA2D_FLAG_CAE) || \
                                 ((FLAG) == DMA2D_FLAG_TW) || ((FLAG) == DMA2D_FLAG_TC) || \
                                 ((FLAG) == DMA2D_FLAG_TE) || ((FLAG) == DMA2D_FLAG_CE))


/**
  * @}
  */

/** @defgroup DMA2D_DeadTime
  * @{
  */
#define DEADTIME                  ((uint32_t)0x000000FF)

#define IS_DMA2D_DEAD_TIME(DEAD_TIME) ((DEAD_TIME) <= DEADTIME)


#define LINE_WATERMARK            DMA2D_LWR_LW

#define IS_DMA2D_LineWatermark(LineWatermark) ((LineWatermark) <= LINE_WATERMARK)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  用于将 DMA2D 配置设置为默认复位状态的函数 *****/
void DMA2D_DeInit(void); // 将 DMA2D 外设寄存器取消初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void DMA2D_Init(DMA2D_InitTypeDef* DMA2D_InitStruct); // 根据 DMA2D_InitStruct 中指定的参数初始化 DMA2D 外设。
void DMA2D_StructInit(DMA2D_InitTypeDef* DMA2D_InitStruct); // 用默认值填充每个DMA2D_InitStruct成员。
void DMA2D_StartTransfer(void); // 启动 DMA2D 传输。
void DMA2D_AbortTransfer(void); // 中止 DMA2D 传输。
void DMA2D_Suspend(FunctionalState NewState); // 停止或继续 DMA2D 传输。
void DMA2D_FGConfig(DMA2D_FG_InitTypeDef* DMA2D_FG_InitStruct); // 根据 DMA2D_FGStruct 中的指定参数配置 Foreground。
void DMA2D_FG_StructInit(DMA2D_FG_InitTypeDef* DMA2D_FG_InitStruct); // 用默认值填充每个 DMA2D_FGStruct 成员。
void DMA2D_BGConfig(DMA2D_BG_InitTypeDef* DMA2D_BG_InitStruct); // 根据 DMA2D_BGStruct 中的指定参数配置背景。
void DMA2D_BG_StructInit(DMA2D_BG_InitTypeDef* DMA2D_BG_InitStruct); // 用默认值填充每个 DMA2D_BGStruct 成员。
void DMA2D_FGStart(FunctionalState NewState); // 开始自动加载 CLUT 或中止传输。
void DMA2D_BGStart(FunctionalState NewState); // 开始自动加载 CLUT 或中止传输。
void DMA2D_DeadTimeConfig(uint32_t DMA2D_DeadTime, FunctionalState NewState); // 配置 DMA2D 死区时间。
void DMA2D_LineWatermarkConfig(uint32_t DMA2D_LWatermarkConfig); // 定义线路水印的配置。

/* 中断和标志管理功能 **********************************/
void DMA2D_ITConfig(uint32_t DMA2D_IT, FunctionalState NewState); // 启用或禁用指定 DMA2D 的中断。
FlagStatus DMA2D_GetFlagStatus(uint32_t DMA2D_FLAG); // 检查是否设置了指定的 DMA2D 标志。
void DMA2D_ClearFlag(uint32_t DMA2D_FLAG); // 清除 DMA2D 的挂起标志。
ITStatus DMA2D_GetITStatus(uint32_t DMA2D_IT); // 检查指定的 DMA2D 的中断是否发生。
void DMA2D_ClearITPendingBit(uint32_t DMA2D_IT); // 清除 DMA2D 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_DMA2D_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
