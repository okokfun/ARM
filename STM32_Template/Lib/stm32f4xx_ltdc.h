/**
  ******************************************************************************
  * 文件:    stm32f4xx_ltdc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 LTDC 固件库的所有功能原型.
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
#ifndef __STM32F4xx_LTDC_H
#define __STM32F4xx_LTDC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup LTDC
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  LTDC Init structure definition
  */
typedef struct {
    uint32_t LTDC_HSPolarity;                 /*!< 配置水平同步极性。
                                                  该参数可以是 @ref LTDC_HSPolarity 的一个值 */

    uint32_t LTDC_VSPolarity;                 /*!< 配置垂直同步极性。
                                                  该参数可以是 @ref LTDC_VSPolarity 的一个值 */

    uint32_t LTDC_DEPolarity;                 /*!< 配置数据使能极性。 此参数可以是 @ref LTDC_DEPolarity 的值之一 */

    uint32_t LTDC_PCPolarity;                 /*!< 配置像素时钟极性。 该参数可以是 @ref LTDC_PCPolarity 的值之一 */

    uint32_t LTDC_HorizontalSync;             /*!< 配置水平同步宽度的数量。 该参数的范围必须是 0x000 到 0xFFF。 */

    uint32_t LTDC_VerticalSync;               /*!< 配置垂直同步高度的个数。 此参数的范围必须为 0x000 到 0x7FF。 */

    uint32_t LTDC_AccumulatedHBP;             /*!< 配置累积的水平后廊宽度。
                                                  此参数的范围必须从 LTDC_HorizontalSync 到 0xFFF。 */

    uint32_t LTDC_AccumulatedVBP;             /*!< 配置累积的垂直后廊高度。
                                                  此参数的范围必须从 LTDC_VerticalSync 到 0x7FF。 */

    uint32_t LTDC_AccumulatedActiveW;         /*!< 配置累积的活动宽度。 这个参数
                                                  范围必须从 LTDC_AccumulatedHBP 到 0xFFF。 */

    uint32_t LTDC_AccumulatedActiveH;         /*!< 配置累积的活动高度。 这个参数
                                                  范围必须从 LTDC_AccumulatedVBP 到 0x7FF。 */

    uint32_t LTDC_TotalWidth;                 /*!< 配置总宽度。 此参数的范围必须从 LTDC_AccumulatedActiveW 到 0xFFF。 */

    uint32_t LTDC_TotalHeigh;                 /*!< 配置总高度。 此参数的范围必须从 LTDC_AccumulatedActiveH 到 0x7FF。 */

    uint32_t LTDC_BackgroundRedValue;         /*!< 配置背景红色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_BackgroundGreenValue;       /*!< 配置背景绿色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_BackgroundBlueValue;       /*!< 配置背景蓝色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */
} LTDC_InitTypeDef;

/**
  * 简介:  LTDC层结构定义
  */
typedef struct {
    uint32_t LTDC_HorizontalStart;            /*!< 配置窗口水平起始位置。
                                                  该参数的范围必须是 0x000 到 0xFFF。 */

    uint32_t LTDC_HorizontalStop;             /*!< 配置窗口水平停止位置。
                                                  该参数的范围必须是 0x0000 到 0xFFFF。 */

    uint32_t LTDC_VerticalStart;              /*!< 配置窗口垂直起始位置。
                                                  该参数的范围必须是 0x000 到 0xFFF。 */

    uint32_t LTDC_VerticalStop;               /*!< 配置窗口垂直停止位置。
                                                  该参数的范围必须是 0x0000 到 0xFFFF。 */

    uint32_t LTDC_PixelFormat;                /*!< 指定像素格式。
												  该参数可以是 @ref LTDC_Pixelformat 的值之一 */

    uint32_t LTDC_ConstantAlpha;              /*!< 指定用于混合的常量 alpha。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_DefaultColorBlue;           /*!< 配置默认的蓝色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_DefaultColorGreen;          /*!< 配置默认绿色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_DefaultColorRed;            /*!< 配置默认红色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_DefaultColorAlpha;          /*!< 配置默认的 alpha 值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_BlendingFactor_1;           /*!< 选择混合因子 1。此参数可以是 @ref LTDC_BlendingFactor1 的值之一 */

    uint32_t LTDC_BlendingFactor_2;           /*!< 选择混合因子 2。此参数可以是 @ref LTDC_BlendingFactor2 的值之一 */

    uint32_t LTDC_CFBStartAdress;             /*!< 配置颜色帧缓冲区地址 */

    uint32_t LTDC_CFBLineLength;              /*!< 配置颜色帧缓冲区行长度。
                                                  该参数的范围必须是 0x0000 到 0x1FFF。 */

    uint32_t LTDC_CFBPitch;                   /*!< 以字节为单位配置颜色帧缓冲区间距。
                                                  该参数的范围必须是 0x0000 到 0x1FFF。 */

    uint32_t LTDC_CFBLineNumber;              /*!< 指定帧缓冲区中的行数。
                                                  此参数的范围必须为 0x000 到 0x7FF。 */
} LTDC_Layer_InitTypeDef;

/**
  * 简介:  LTDC职位结构定义
  */
typedef struct {
    uint32_t LTDC_POSX;                         /*!<  当前 X 位置 */
    uint32_t LTDC_POSY;                         /*!<  当前 Y 位置 */
} LTDC_PosTypeDef;

/**
  * 简介:  LTDC RGB结构定义
  */
typedef struct {
    uint32_t LTDC_BlueWidth;                        /*!< 蓝色宽度 */
    uint32_t LTDC_GreenWidth;                       /*!< 绿色宽度 */
    uint32_t LTDC_RedWidth;                         /*!< 红色宽度 */
} LTDC_RGBTypeDef;

/**
  * 简介:  LTDC颜色键控结构定义
  */
typedef struct {
    uint32_t LTDC_ColorKeyBlue;               /*!< 配置颜色键蓝色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_ColorKeyGreen;              /*!< 配置颜色键绿色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_ColorKeyRed;                /*!< 配置颜色键红色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */
} LTDC_ColorKeying_InitTypeDef;

/**
  * 简介:  LTDC CLUT结构定义
  */
typedef struct {
    uint32_t LTDC_CLUTAdress;                 /*!< 配置 CLUT 地址。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_BlueValue;                  /*!< 配置蓝色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_GreenValue;                 /*!< 配置绿色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */

    uint32_t LTDC_RedValue;                   /*!< 配置红色值。
                                                  此参数的范围必须为 0x00 到 0xFF。 */
} LTDC_CLUT_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup LTDC_Exported_Constants
  */

/** @defgroup LTDC_SYNC
  */
#define LTDC_HorizontalSYNC               ((uint32_t)0x00000FFF)
#define LTDC_VerticalSYNC                 ((uint32_t)0x000007FF)

#define IS_LTDC_HSYNC(HSYNC) ((HSYNC) <= LTDC_HorizontalSYNC)
#define IS_LTDC_VSYNC(VSYNC) ((VSYNC) <= LTDC_VerticalSYNC)
#define IS_LTDC_AHBP(AHBP)  ((AHBP) <= LTDC_HorizontalSYNC)
#define IS_LTDC_AVBP(AVBP) ((AVBP) <= LTDC_VerticalSYNC)
#define IS_LTDC_AAW(AAW)   ((AAW) <= LTDC_HorizontalSYNC)
#define IS_LTDC_AAH(AAH) ((AAH) <= LTDC_VerticalSYNC)
#define IS_LTDC_TOTALW(TOTALW) ((TOTALW) <= LTDC_HorizontalSYNC)
#define IS_LTDC_TOTALH(TOTALH) ((TOTALH) <= LTDC_VerticalSYNC)

/** @defgroup LTDC_HSPolarity
  */
#define LTDC_HSPolarity_AL                ((uint32_t)0x00000000)                /*!< 水平同步低电平有效。 */
#define LTDC_HSPolarity_AH                LTDC_GCR_HSPOL                        /*!< 水平同步高电平有效。 */

#define IS_LTDC_HSPOL(HSPOL) (((HSPOL) == LTDC_HSPolarity_AL) || \
                              ((HSPOL) == LTDC_HSPolarity_AH))

/** @defgroup LTDC_VSPolarity
  */
#define LTDC_VSPolarity_AL                ((uint32_t)0x00000000)                /*!< 垂直同步低电平有效。 */
#define LTDC_VSPolarity_AH                LTDC_GCR_VSPOL                        /*!< 垂直同步高电平有效。 */

#define IS_LTDC_VSPOL(VSPOL) (((VSPOL) == LTDC_VSPolarity_AL) || \
                              ((VSPOL) == LTDC_VSPolarity_AH))

/** @defgroup LTDC_DEPolarity
  */
#define LTDC_DEPolarity_AL                ((uint32_t)0x00000000)                /*!< 数据使能，低电平有效。 */
#define LTDC_DEPolarity_AH                LTDC_GCR_DEPOL                        /*!< 数据使能，高电平有效。 */

#define IS_LTDC_DEPOL(DEPOL) (((DEPOL) ==  LTDC_VSPolarity_AL) || \
                              ((DEPOL) ==  LTDC_DEPolarity_AH))

/** @defgroup LTDC_PCPolarity
  */
#define LTDC_PCPolarity_IPC               ((uint32_t)0x00000000)                /*!< 输入像素时钟。 */
#define LTDC_PCPolarity_IIPC              LTDC_GCR_PCPOL                        /*!< 反相输入像素时钟。 */

#define IS_LTDC_PCPOL(PCPOL) (((PCPOL) ==  LTDC_PCPolarity_IPC) || \
                              ((PCPOL) ==  LTDC_PCPolarity_IIPC))

/** @defgroup LTDC_Reload
  */
#define LTDC_IMReload                     LTDC_SRCR_IMR                         /*!< 立即重新加载。 */
#define LTDC_VBReload                     LTDC_SRCR_VBR                         /*!< 垂直消隐重装。 */

#define IS_LTDC_RELOAD(RELOAD) (((RELOAD) == LTDC_IMReload) || \
                                ((RELOAD) == LTDC_VBReload))

/** @defgroup LTDC_Back_Color
  */
#define LTDC_Back_Color                   ((uint32_t)0x000000FF)

#define IS_LTDC_BackBlueValue(BBLUE)    ((BBLUE) <= LTDC_Back_Color)
#define IS_LTDC_BackGreenValue(BGREEN)  ((BGREEN) <= LTDC_Back_Color)
#define IS_LTDC_BackRedValue(BRED)      ((BRED) <= LTDC_Back_Color)

/** @defgroup LTDC_Position
  */
#define LTDC_POS_CY                       LTDC_CPSR_CYPOS
#define LTDC_POS_CX                       LTDC_CPSR_CXPOS

#define IS_LTDC_GET_POS(POS) (((POS) <= LTDC_POS_CY))

/** @defgroup LTDC_LIPosition
  */
#define IS_LTDC_LIPOS(LIPOS) ((LIPOS) <= 0x7FF)

/** @defgroup LTDC_CurrentStatus
  */
#define LTDC_CD_VDES                     LTDC_CDSR_VDES
#define LTDC_CD_HDES                     LTDC_CDSR_HDES
#define LTDC_CD_VSYNC                    LTDC_CDSR_VSYNCS
#define LTDC_CD_HSYNC                    LTDC_CDSR_HSYNCS

#define IS_LTDC_GET_CD(CD) (((CD) == LTDC_CD_VDES) || ((CD) == LTDC_CD_HDES) || \
                            ((CD) == LTDC_CD_VSYNC) || ((CD) == LTDC_CD_HSYNC))

/** @defgroup LTDC_Interrupts
  */
#define LTDC_IT_LI                      LTDC_IER_LIE
#define LTDC_IT_FU                      LTDC_IER_FUIE
#define LTDC_IT_TERR                    LTDC_IER_TERRIE
#define LTDC_IT_RR                      LTDC_IER_RRIE

#define IS_LTDC_IT(IT) ((((IT) & (uint32_t)0xFFFFFFF0) == 0x00) && ((IT) != 0x00))


/** @defgroup LTDC_Flag
  */
#define LTDC_FLAG_LI                     LTDC_ISR_LIF
#define LTDC_FLAG_FU                     LTDC_ISR_FUIF
#define LTDC_FLAG_TERR                   LTDC_ISR_TERRIF
#define LTDC_FLAG_RR                     LTDC_ISR_RRIF

#define IS_LTDC_FLAG(FLAG) (((FLAG) == LTDC_FLAG_LI) || ((FLAG) == LTDC_FLAG_FU) || \
                            ((FLAG) == LTDC_FLAG_TERR) || ((FLAG) == LTDC_FLAG_RR))

/** @defgroup LTDC_Pixelformat
  */
#define LTDC_Pixelformat_ARGB8888                  ((uint32_t)0x00000000)
#define LTDC_Pixelformat_RGB888                    ((uint32_t)0x00000001)
#define LTDC_Pixelformat_RGB565                    ((uint32_t)0x00000002)
#define LTDC_Pixelformat_ARGB1555                  ((uint32_t)0x00000003)
#define LTDC_Pixelformat_ARGB4444                  ((uint32_t)0x00000004)
#define LTDC_Pixelformat_L8                        ((uint32_t)0x00000005)
#define LTDC_Pixelformat_AL44                      ((uint32_t)0x00000006)
#define LTDC_Pixelformat_AL88                      ((uint32_t)0x00000007)

#define IS_LTDC_Pixelformat(Pixelformat) (((Pixelformat) == LTDC_Pixelformat_ARGB8888) || ((Pixelformat) == LTDC_Pixelformat_RGB888)   || \
        ((Pixelformat) == LTDC_Pixelformat_RGB565)   || ((Pixelformat) == LTDC_Pixelformat_ARGB1555) || \
        ((Pixelformat) == LTDC_Pixelformat_ARGB4444) || ((Pixelformat) == LTDC_Pixelformat_L8)       || \
        ((Pixelformat) == LTDC_Pixelformat_AL44)     || ((Pixelformat) == LTDC_Pixelformat_AL88))


/** @defgroup LTDC_BlendingFactor1
  */
#define LTDC_BlendingFactor1_CA                       ((uint32_t)0x00000400)
#define LTDC_BlendingFactor1_PAxCA                    ((uint32_t)0x00000600)

#define IS_LTDC_BlendingFactor1(BlendingFactor1) (((BlendingFactor1) == LTDC_BlendingFactor1_CA) || ((BlendingFactor1) == LTDC_BlendingFactor1_PAxCA))

/** @defgroup LTDC_BlendingFactor2
  */
#define LTDC_BlendingFactor2_CA                       ((uint32_t)0x00000005)
#define LTDC_BlendingFactor2_PAxCA                    ((uint32_t)0x00000007)

#define IS_LTDC_BlendingFactor2(BlendingFactor2) (((BlendingFactor2) == LTDC_BlendingFactor2_CA) || ((BlendingFactor2) == LTDC_BlendingFactor2_PAxCA))

/** @defgroup LTDC_LAYER_Config
  */
#define LTDC_STOPPosition                 ((uint32_t)0x0000FFFF)
#define LTDC_STARTPosition                ((uint32_t)0x00000FFF)

#define LTDC_DefaultColorConfig           ((uint32_t)0x000000FF)
#define LTDC_ColorFrameBuffer             ((uint32_t)0x00001FFF)
#define LTDC_LineNumber                   ((uint32_t)0x000007FF)

#define IS_LTDC_HCONFIGST(HCONFIGST) ((HCONFIGST) <= LTDC_STARTPosition)
#define IS_LTDC_HCONFIGSP(HCONFIGSP) ((HCONFIGSP) <= LTDC_STOPPosition)
#define IS_LTDC_VCONFIGST(VCONFIGST)  ((VCONFIGST) <= LTDC_STARTPosition)
#define IS_LTDC_VCONFIGSP(VCONFIGSP) ((VCONFIGSP) <= LTDC_STOPPosition)

#define IS_LTDC_DEFAULTCOLOR(DEFAULTCOLOR) ((DEFAULTCOLOR) <= LTDC_DefaultColorConfig)

#define IS_LTDC_CFBP(CFBP) ((CFBP) <= LTDC_ColorFrameBuffer)
#define IS_LTDC_CFBLL(CFBLL) ((CFBLL) <= LTDC_ColorFrameBuffer)

#define IS_LTDC_CFBLNBR(CFBLNBR) ((CFBLNBR) <= LTDC_LineNumber)

/** @defgroup LTDC_colorkeying_Config
  */
#define LTDC_colorkeyingConfig            ((uint32_t)0x000000FF)

#define IS_LTDC_CKEYING(CKEYING) ((CKEYING) <= LTDC_colorkeyingConfig)

/** @defgroup LTDC_CLUT_Config
  */
#define LTDC_CLUTWR                       ((uint32_t)0x000000FF)

#define IS_LTDC_CLUTWR(CLUTWR)  ((CLUTWR) <= LTDC_CLUTWR)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/*  Function used to set the LTDC configuration to the default reset state *****/
void LTDC_DeInit(void); // 将 LTDC 外设寄存器去初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void LTDC_Init(LTDC_InitTypeDef* LTDC_InitStruct); // 根据 LTDC_InitStruct 中指定的参数初始化 LTDC 外设。
void LTDC_StructInit(LTDC_InitTypeDef* LTDC_InitStruct); // 用其默认值填充每个 LTDC_InitStruct 成员。
void LTDC_Cmd(FunctionalState NewState); // 启用或禁用 LTDC 控制器。
void LTDC_DitherCmd(FunctionalState NewState); // 启用或禁用抖动。
LTDC_RGBTypeDef LTDC_GetRGBWidth(void); // 获取抖动 RGB 宽度。
void LTDC_RGBStructInit(LTDC_RGBTypeDef* LTDC_RGB_InitStruct); // 用每个 LTDC_RGBStruct 成员的默认值填充该成员。
void LTDC_LIPConfig(uint32_t LTDC_LIPositionConfig); // 定义线路中断的位置。
void LTDC_ReloadConfig(uint32_t LTDC_Reload); // 使用新参数重新加载图层寄存器
void LTDC_LayerInit(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_Layer_InitTypeDef* LTDC_Layer_InitStruct); // 根据 LTDC_LayerStruct 中指定的参数初始化 LTDC 层。
void LTDC_LayerStructInit(LTDC_Layer_InitTypeDef * LTDC_Layer_InitStruct); // 用每个 LTDC_Layer_InitStruct 成员的默认值填充该成员。
void LTDC_LayerCmd(LTDC_Layer_TypeDef* LTDC_Layerx, FunctionalState NewState); // 启用或禁用 LTDC_Layer控制器。
LTDC_PosTypeDef LTDC_GetPosStatus(void); // 获取当前位置。
void LTDC_PosStructInit(LTDC_PosTypeDef* LTDC_Pos_InitStruct); // 用每个 LTDC_Pos_InitStruct 成员的默认值填充该成员。
FlagStatus LTDC_GetCDStatus(uint32_t LTDC_CD); // 检查是否设置了指定的 LTDC 标志。
void LTDC_ColorKeyingConfig(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_ColorKeying_InitTypeDef* LTDC_colorkeying_InitStruct, FunctionalState NewState); // 设置和配置颜色键控。
void LTDC_ColorKeyingStructInit(LTDC_ColorKeying_InitTypeDef* LTDC_colorkeying_InitStruct); // 用每个 LTDC_colorkeying_InitStruct 成员的默认值填充其默认值。
void LTDC_CLUTCmd(LTDC_Layer_TypeDef* LTDC_Layerx, FunctionalState NewState); // 启用或禁用 CLUT。
void LTDC_CLUTInit(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_CLUT_InitTypeDef* LTDC_CLUT_InitStruct); // 配置 CLUT。
void LTDC_CLUTStructInit(LTDC_CLUT_InitTypeDef* LTDC_CLUT_InitStruct); // 用每个 LTDC_CLUT_InitStruct 成员的默认值填充该成员。
void LTDC_LayerPosition(LTDC_Layer_TypeDef* LTDC_Layerx, uint16_t OffsetX, uint16_t OffsetY); // 重新配置图层位置。
void LTDC_LayerAlpha(LTDC_Layer_TypeDef* LTDC_Layerx, uint8_t ConstantAlpha); // 重新配置常量 alpha。
void LTDC_LayerAddress(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t Address); // 重新配置图层地址。
void LTDC_LayerSize(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t Width, uint32_t Height); // 重新配置图层大小。
void LTDC_LayerPixelFormat(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t PixelFormat); // 重新配置图层像素格式。

/* 中断和标记管理功能 **********************************/
void LTDC_ITConfig(uint32_t LTDC_IT, FunctionalState NewState); // 启用或禁用指定的 LTDC 的中断。
FlagStatus LTDC_GetFlagStatus(uint32_t LTDC_FLAG); // 检查是否设置了指定的 LTDC 标志。
void LTDC_ClearFlag(uint32_t LTDC_FLAG); // 清除 LTDC 的挂起标志。
ITStatus LTDC_GetITStatus(uint32_t LTDC_IT); // 检查指定的 LTDC 的中断是否发生。
void LTDC_ClearITPendingBit(uint32_t LTDC_IT); // 清除 LTDC 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_LTDC_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
