/**
  ******************************************************************************
  * 文件:    stm32f4xx_ltdc.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能，以管理LTDC控制器(LTDC)外设的以下功能:
  *           + 初始化和配置
  *           + 中断和标志管理
  *
  *  @verbatim

 ===============================================================================
                      ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..]
        (#) 使用
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_LTDC, ENABLE) 函数启用LTDC时钟。

        (#) 配置LTDC
          (++) 按照面板数据手册配置所需的Pixel时钟
          (++) 配置同步时序。VSYNC, HSYNC, 垂直和水平的后序，活动数据区和前序时序
          (++) 在LTDC_GCR 寄存器中配置同步信号和时钟极性

        (#) 配置Layer1/2参数
          (++) 在LTDC_LxWHPCR和 LTDC_WVPCR 寄存器中配置层窗口的水平和垂直位置。层窗口必须在活动数据区。
          (++) LTDC_LxPFCR 寄存器中的像素输入格式
          (++) LTDC_LxCFBAR 寄存器中的彩色帧缓冲器起始地址
          (++) LTDC_LxCFBAR 寄存器中的彩色帧缓冲区的行长和间距。LTDC_LxCFBLR 寄存器中的彩色帧缓冲区的行长和间距
          (++) LTDC_LxCFBLR 寄存器中彩色帧缓冲器的行数。LTDC_LxCFBLNR 寄存器中彩色帧缓冲区的行数
          (++) 如果需要的话，用 RGB值和地址加载CLUT 在LTDC_LxCLUTWR 寄存器中。
          (++) 如果需要，在LTDC_LxCLUTWR 寄存器中分别配置默认颜色和混合系数。
               分别在LTDC_LxDCCR和 LTDC_LxBFCR 寄存器中配置默认颜色和混合系数

          (++) 如果需要，可以分别在LTDC_GCR和 LTDC_LxBFCR 寄存器中启用抖动和抠色功能。
               在LTDC_GCR和 LTDC_LxCKCR 寄存器中分别启用抖动和抠色。它也可以被启用 也可以在运行中启用。

        (#) 在LTDC_LxCR 寄存器中启用Layer1/2，必要时启用 CLUT

        (#) 通过LTDC_SRCR 寄存器将影子寄存器重新加载到活动寄存器。(#) 通过LTDC_SRCR 寄存器将影子寄存器重新载入活动寄存器。
          -@- 除了CLUT之外，所有的层参数都可以被即时修改。
              新的配置必须立即被重新加载 或在垂直消隐期间通过配置LTDC_SRCR 寄存器重新加载新的配置。
        (#) 调用LTDC_Cmd()来启用LTDC控制器。

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
#include "stm32f4xx_ltdc.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup LTDC
  * 简介: LTDC 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

#define GCR_MASK                     ((uint32_t)0x0FFE888F)  /* LTDC GCR Mask */


/** @defgroup LTDC_Private_Functions
  */

/** @defgroup LTDC_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
            ##### 初始化和配置函数 #####
 ===============================================================================
    [..]  本节提供的功能允许:
        (+) 初始化和配置LTDC
        (+) 启用或禁用抖动
        (+) 定义线路中断的位置
        (+) 用新参数重新加载层寄存器
        (+) 初始化并配置第1层和第2层
        (+) 设置和配置颜色键控功能
        (+) 配置并启用或禁用 CLUT

@endverbatim
  */

/**
  * 简介:  将 LTDC 外设寄存器去初始化为其默认复位值。
  * 参数:  无
  * 返回值: 无
  */
void LTDC_DeInit(void) {
    /* 使能LTDC 复位状态 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_LTDC, ENABLE);
    /* 释放LTDC from 复位状态 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_LTDC, DISABLE);
}

/**
  * 简介:  根据 LTDC_InitStruct 中指定的参数初始化LTDC 外设。
  * 注意:   这个功能只有在禁用LTDC 的情况下才能使用。
  * 参数:  LTDC_InitStruct: 指向 LTDC_InitTypeDef 结构的指针，
  *                         该结构包含指定 LTDC 外设的配置信息。
  * 返回值: 无
  */
void LTDC_Init(LTDC_InitTypeDef* LTDC_InitStruct) {
    uint32_t horizontalsync = 0;
    uint32_t accumulatedHBP = 0;
    uint32_t accumulatedactiveW = 0;
    uint32_t totalwidth = 0;
    uint32_t backgreen = 0;
    uint32_t backred = 0;

    /* 检查 函数参数 */
    assert_param(IS_LTDC_HSYNC(LTDC_InitStruct->LTDC_HorizontalSync));
    assert_param(IS_LTDC_VSYNC(LTDC_InitStruct->LTDC_VerticalSync));
    assert_param(IS_LTDC_AHBP(LTDC_InitStruct->LTDC_AccumulatedHBP));
    assert_param(IS_LTDC_AVBP(LTDC_InitStruct->LTDC_AccumulatedVBP));
    assert_param(IS_LTDC_AAH(LTDC_InitStruct->LTDC_AccumulatedActiveH));
    assert_param(IS_LTDC_AAW(LTDC_InitStruct->LTDC_AccumulatedActiveW));
    assert_param(IS_LTDC_TOTALH(LTDC_InitStruct->LTDC_TotalHeigh));
    assert_param(IS_LTDC_TOTALW(LTDC_InitStruct->LTDC_TotalWidth));
    assert_param(IS_LTDC_HSPOL(LTDC_InitStruct->LTDC_HSPolarity));
    assert_param(IS_LTDC_VSPOL(LTDC_InitStruct->LTDC_VSPolarity));
    assert_param(IS_LTDC_DEPOL(LTDC_InitStruct->LTDC_DEPolarity));
    assert_param(IS_LTDC_PCPOL(LTDC_InitStruct->LTDC_PCPolarity));
    assert_param(IS_LTDC_BackBlueValue(LTDC_InitStruct->LTDC_BackgroundBlueValue));
    assert_param(IS_LTDC_BackGreenValue(LTDC_InitStruct->LTDC_BackgroundGreenValue));
    assert_param(IS_LTDC_BackRedValue(LTDC_InitStruct->LTDC_BackgroundRedValue));

    /* 设置同步大小 */
    LTDC->SSCR &= ~(LTDC_SSCR_VSH | LTDC_SSCR_HSW);
    horizontalsync = (LTDC_InitStruct->LTDC_HorizontalSync << 16);
    LTDC->SSCR |= (horizontalsync | LTDC_InitStruct->LTDC_VerticalSync);

    /*设置累积后廊 */
    LTDC->BPCR &= ~(LTDC_BPCR_AVBP | LTDC_BPCR_AHBP);
    accumulatedHBP = (LTDC_InitStruct->LTDC_AccumulatedHBP << 16);
    LTDC->BPCR |= (accumulatedHBP | LTDC_InitStruct->LTDC_AccumulatedVBP);

    /* 设置累计活动宽度 */
    LTDC->AWCR &= ~(LTDC_AWCR_AAH | LTDC_AWCR_AAW);
    accumulatedactiveW = (LTDC_InitStruct->LTDC_AccumulatedActiveW << 16);
    LTDC->AWCR |= (accumulatedactiveW | LTDC_InitStruct->LTDC_AccumulatedActiveH);

    /* 设置总宽度 */
    LTDC->TWCR &= ~(LTDC_TWCR_TOTALH | LTDC_TWCR_TOTALW);
    totalwidth = (LTDC_InitStruct->LTDC_TotalWidth << 16);
    LTDC->TWCR |= (totalwidth | LTDC_InitStruct->LTDC_TotalHeigh);

    LTDC->GCR &= (uint32_t)GCR_MASK;
    LTDC->GCR |=  (uint32_t)(LTDC_InitStruct->LTDC_HSPolarity | LTDC_InitStruct->LTDC_VSPolarity | \
                             LTDC_InitStruct->LTDC_DEPolarity | LTDC_InitStruct->LTDC_PCPolarity);

    /* 设置背景颜色值 */
    backgreen = (LTDC_InitStruct->LTDC_BackgroundGreenValue << 8);
    backred = (LTDC_InitStruct->LTDC_BackgroundRedValue << 16);

    LTDC->BCCR &= ~(LTDC_BCCR_BCBLUE | LTDC_BCCR_BCGREEN | LTDC_BCCR_BCRED);
    LTDC->BCCR |= (backred | backgreen | LTDC_InitStruct->LTDC_BackgroundBlueValue);
}

/**
  * 简介:  用其默认值填充每个 LTDC_InitStruct 成员。
  * 参数:  LTDC_InitStruct: 指向 LTDC_InitTypeDef 结构的指针，该结构将被初始化。
  * 返回值: 无
  */
void LTDC_StructInit(LTDC_InitTypeDef* LTDC_InitStruct) {
    /*--------------- 重置LTCC 初始化结构参数值 ----------------*/
    LTDC_InitStruct->LTDC_HSPolarity = LTDC_HSPolarity_AL;      /*!< 初始化这个 LTDC_HSPolarity           成员 */
    LTDC_InitStruct->LTDC_VSPolarity = LTDC_VSPolarity_AL;      /*!< 初始化这个 LTDC_VSPolarity           成员 */
    LTDC_InitStruct->LTDC_DEPolarity = LTDC_DEPolarity_AL;      /*!< 初始化这个 LTDC_DEPolarity           成员 */
    LTDC_InitStruct->LTDC_PCPolarity = LTDC_PCPolarity_IPC;     /*!< 初始化这个 LTDC_PCPolarity           成员 */
    LTDC_InitStruct->LTDC_HorizontalSync = 0x00;                /*!< 初始化这个 LTDC_HorizontalSync       成员 */
    LTDC_InitStruct->LTDC_VerticalSync = 0x00;                  /*!< 初始化这个 LTDC_VerticalSync         成员 */
    LTDC_InitStruct->LTDC_AccumulatedHBP = 0x00;                /*!< 初始化这个 LTDC_AccumulatedHBP       成员 */
    LTDC_InitStruct->LTDC_AccumulatedVBP = 0x00;                /*!< 初始化这个 LTDC_AccumulatedVBP       成员 */
    LTDC_InitStruct->LTDC_AccumulatedActiveW = 0x00;            /*!< 初始化这个 LTDC_AccumulatedActiveW   成员 */
    LTDC_InitStruct->LTDC_AccumulatedActiveH = 0x00;            /*!< 初始化这个 LTDC_AccumulatedActiveH   成员 */
    LTDC_InitStruct->LTDC_TotalWidth = 0x00;                    /*!< 初始化这个 LTDC_TotalWidth           成员 */
    LTDC_InitStruct->LTDC_TotalHeigh = 0x00;                    /*!< 初始化这个 LTDC_TotalHeigh           成员 */
    LTDC_InitStruct->LTDC_BackgroundRedValue = 0x00;            /*!< 初始化这个 LTDC_BackgroundRedValue   成员 */
    LTDC_InitStruct->LTDC_BackgroundGreenValue = 0x00;          /*!< 初始化这个 LTDC_BackgroundGreenValue 成员 */
    LTDC_InitStruct->LTDC_BackgroundBlueValue = 0x00;           /*!< 初始化这个 LTDC_BackgroundBlueValue  成员 */
}

/**
  * 简介:  启用或禁用 LTDC 控制器。
  * 参数:  NewState: 新状态-> LTDC 外设.
  *   此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void LTDC_Cmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能LTDC by setting LTDCEN 位 */
        LTDC->GCR |= (uint32_t)LTDC_GCR_LTDCEN;
    } else {
        /* 通过清除LTDCEN禁用LTCC位 */
        LTDC->GCR &= ~(uint32_t)LTDC_GCR_LTDCEN;
    }
}

/**
  * 简介:  启用或禁用抖动。
  * 参数:  NewState: 新状态-> Dither.
  *   此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void LTDC_DitherCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能通过设置 DTEN抖动位 */
        LTDC->GCR |= (uint32_t)LTDC_GCR_DTEN;
    } else {
        /* 通过清除DTEN禁用抖动位 */
        LTDC->GCR &= ~(uint32_t)LTDC_GCR_DTEN;
    }
}

/**
  * 简介:  获取抖动 RGB 宽度。
  * 参数:  LTDC_RGB_InitStruct: 指向LTDC_RGBTypeDef 结构的指针，该结构含有 Dither RGB宽度。
  * 返回值: 无
  */

LTDC_RGBTypeDef LTDC_GetRGBWidth(void) {
    LTDC_RGBTypeDef LTDC_RGB_InitStruct;

    LTDC->GCR &= (uint32_t)GCR_MASK;

    LTDC_RGB_InitStruct.LTDC_BlueWidth = (uint32_t)((LTDC->GCR >> 4) & 0x7);
    LTDC_RGB_InitStruct.LTDC_GreenWidth = (uint32_t)((LTDC->GCR >> 8) & 0x7);
    LTDC_RGB_InitStruct.LTDC_RedWidth = (uint32_t)((LTDC->GCR >> 12) & 0x7);

    return LTDC_RGB_InitStruct;
}

/**
  * 简介:  用每个LTDC_RGBStruct 成员的默认值填充该成员。
  * 参数:  LTDC_RGB_InitStruct: 指向LTDC_RGBTypeDef 结构的指针，该结构将被初始化。
  * 返回值: 无
  */
void LTDC_RGBStructInit(LTDC_RGBTypeDef* LTDC_RGB_InitStruct) {
    LTDC_RGB_InitStruct->LTDC_BlueWidth = 0x02;
    LTDC_RGB_InitStruct->LTDC_GreenWidth = 0x02;
    LTDC_RGB_InitStruct->LTDC_RedWidth = 0x02;
}


/**
  * 简介:    定义线路中断的位置。
  * 参数:  LTDC_LIPositionConfig: 线路中断位置。
  * 返回值: 无
  */
void LTDC_LIPConfig(uint32_t LTDC_LIPositionConfig) {
    /* 检查参数 */
    assert_param(IS_LTDC_LIPOS(LTDC_LIPositionConfig));

    /* 设置线路中断位置 */
    LTDC->LIPCR = (uint32_t)LTDC_LIPositionConfig;
}

/**
  * 简介:  使用新参数重新加载图层寄存器
  * 参数:  LTDC_Reload: 指定重载的类型。
  *   此参数可以是以下值之一:
  *     @arg LTDC_IMReload: 竖直消隐重装。
  *     @arg LTDC_VBReload: 立即重新加载。
  * 返回值: 无
  */
void LTDC_ReloadConfig(uint32_t LTDC_Reload) {
    /* 检查参数 */
    assert_param(IS_LTDC_RELOAD(LTDC_Reload));

    /* 设置重新加载类型 */
    LTDC->SRCR = (uint32_t)LTDC_Reload;
}


/**
  * 简介:  根据 LTDC_LayerStruct 中指定的参数初始化 LTDC 层。
  * 注意:  这个功能只有在禁用LTDC 的情况下才能使用。
  * 参数:  LTDC_layerx: 选择要配置的层，这个参数可以是以下值之一: 
  *                     LTDC_Layer1, LTDC_Layer2。
  * 参数:  LTDC_LayerStruct: 指向 LTDC_LayerTypeDef 结构的指针，
  *                          该结构包含指定 LTDC 的配置信息。
  * 返回值: 无
  */
void LTDC_LayerInit(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_Layer_InitTypeDef* LTDC_Layer_InitStruct) {
    uint32_t whsppos = 0;
    uint32_t wvsppos = 0;
    uint32_t dcgreen = 0;
    uint32_t dcred = 0;
    uint32_t dcalpha = 0;
    uint32_t cfbp = 0;

    /* 检查参数 */
    assert_param(IS_LTDC_Pixelformat(LTDC_Layer_InitStruct->LTDC_PixelFormat));
    assert_param(IS_LTDC_BlendingFactor1(LTDC_Layer_InitStruct->LTDC_BlendingFactor_1));
    assert_param(IS_LTDC_BlendingFactor2(LTDC_Layer_InitStruct->LTDC_BlendingFactor_2));
    assert_param(IS_LTDC_HCONFIGST(LTDC_Layer_InitStruct->LTDC_HorizontalStart));
    assert_param(IS_LTDC_HCONFIGSP(LTDC_Layer_InitStruct->LTDC_HorizontalStop));
    assert_param(IS_LTDC_VCONFIGST(LTDC_Layer_InitStruct->LTDC_VerticalStart));
    assert_param(IS_LTDC_VCONFIGSP(LTDC_Layer_InitStruct->LTDC_VerticalStop));
    assert_param(IS_LTDC_DEFAULTCOLOR(LTDC_Layer_InitStruct->LTDC_DefaultColorBlue));
    assert_param(IS_LTDC_DEFAULTCOLOR(LTDC_Layer_InitStruct->LTDC_DefaultColorGreen));
    assert_param(IS_LTDC_DEFAULTCOLOR(LTDC_Layer_InitStruct->LTDC_DefaultColorRed));
    assert_param(IS_LTDC_DEFAULTCOLOR(LTDC_Layer_InitStruct->LTDC_DefaultColorAlpha));
    assert_param(IS_LTDC_CFBP(LTDC_Layer_InitStruct->LTDC_CFBPitch));
    assert_param(IS_LTDC_CFBLL(LTDC_Layer_InitStruct->LTDC_CFBLineLength));
    assert_param(IS_LTDC_CFBLNBR(LTDC_Layer_InitStruct->LTDC_CFBLineNumber));

    /* 配置水平启动和停止位置 */
    whsppos = LTDC_Layer_InitStruct->LTDC_HorizontalStop << 16;
    LTDC_Layerx->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
    LTDC_Layerx->WHPCR = (LTDC_Layer_InitStruct->LTDC_HorizontalStart | whsppos);

    /* 配置垂直启动和停止位置 */
    wvsppos = LTDC_Layer_InitStruct->LTDC_VerticalStop << 16;
    LTDC_Layerx->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
    LTDC_Layerx->WVPCR  = (LTDC_Layer_InitStruct->LTDC_VerticalStart | wvsppos);

    /* 指定像素格式 */
    LTDC_Layerx->PFCR &= ~(LTDC_LxPFCR_PF);
    LTDC_Layerx->PFCR = (LTDC_Layer_InitStruct->LTDC_PixelFormat);

    /* 配置默认颜色值 */
    dcgreen = (LTDC_Layer_InitStruct->LTDC_DefaultColorGreen << 8);
    dcred = (LTDC_Layer_InitStruct->LTDC_DefaultColorRed << 16);
    dcalpha = (LTDC_Layer_InitStruct->LTDC_DefaultColorAlpha << 24);
    LTDC_Layerx->DCCR &=  ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
    LTDC_Layerx->DCCR = (LTDC_Layer_InitStruct->LTDC_DefaultColorBlue | dcgreen | \
                         dcred | dcalpha);

    /* 指定常量alpha值 */
    LTDC_Layerx->CACR &= ~(LTDC_LxCACR_CONSTA);
    LTDC_Layerx->CACR = (LTDC_Layer_InitStruct->LTDC_ConstantAlpha);

    /* 指定混合因子 */
    LTDC_Layerx->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
    LTDC_Layerx->BFCR = (LTDC_Layer_InitStruct->LTDC_BlendingFactor_1 | LTDC_Layer_InitStruct->LTDC_BlendingFactor_2);

    /* 配置彩色帧缓冲区起始地址 */
    LTDC_Layerx->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
    LTDC_Layerx->CFBAR = (LTDC_Layer_InitStruct->LTDC_CFBStartAdress);

    /* 以字节为单位配置彩色帧缓冲区间距 */
    cfbp = (LTDC_Layer_InitStruct->LTDC_CFBPitch << 16);
    LTDC_Layerx->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
    LTDC_Layerx->CFBLR  = (LTDC_Layer_InitStruct->LTDC_CFBLineLength | cfbp);

    /* 配置帧缓冲区行号 */
    LTDC_Layerx->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
    LTDC_Layerx->CFBLNR  = (LTDC_Layer_InitStruct->LTDC_CFBLineNumber);
}

/**
  * 简介:  用每个 LTDC_Layer_InitStruct 成员的默认值填充该成员。
  * 参数:  LTDC_Layer_InitStruct: 指向 LTDC_LayerTypeDef 结构的指针，该结构将被初始化。
  * 返回值: 无
  */
void LTDC_LayerStructInit(LTDC_Layer_InitTypeDef * LTDC_Layer_InitStruct) {
    /*--------------- 重置层结构参数值 -------------------*/

    /*!< 初始化水平限制成员 */
    LTDC_Layer_InitStruct->LTDC_HorizontalStart = 0x00;
    LTDC_Layer_InitStruct->LTDC_HorizontalStop = 0x00;

    /*!< 初始化垂直限制成员 */
    LTDC_Layer_InitStruct->LTDC_VerticalStart = 0x00;
    LTDC_Layer_InitStruct->LTDC_VerticalStop = 0x00;

    /*!< 初始化像素格式成员 */
    LTDC_Layer_InitStruct->LTDC_PixelFormat = LTDC_Pixelformat_ARGB8888;

    /*!< 初始化常量alpha值 */
    LTDC_Layer_InitStruct->LTDC_ConstantAlpha = 0xFF;

    /*!< 初始化默认颜色值 */
    LTDC_Layer_InitStruct->LTDC_DefaultColorBlue = 0x00;
    LTDC_Layer_InitStruct->LTDC_DefaultColorGreen = 0x00;
    LTDC_Layer_InitStruct->LTDC_DefaultColorRed = 0x00;
    LTDC_Layer_InitStruct->LTDC_DefaultColorAlpha = 0x00;

    /*!< 初始化混合因子 */
    LTDC_Layer_InitStruct->LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_PAxCA;
    LTDC_Layer_InitStruct->LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_PAxCA;

    /*!< 初始化帧缓冲区起始地址 */
    LTDC_Layer_InitStruct->LTDC_CFBStartAdress = 0x00;

    /*!< 初始化帧缓冲区间距和行长度 */
    LTDC_Layer_InitStruct->LTDC_CFBLineLength = 0x00;
    LTDC_Layer_InitStruct->LTDC_CFBPitch = 0x00;

    /*!< 初始化帧缓冲行号 */
    LTDC_Layer_InitStruct->LTDC_CFBLineNumber = 0x00;
}


/**
  * 简介:  启用或禁用LTDC_Layer控制器。
  * 参数:  LTDC_layerx: 选择要配置的层，
  *         这个参数可以是以下值之一:
  *         LTDC_Layer1, LTDC_Layer2
  * 参数:  NewState: 新状态-> LTDC_Layer 外设.
  *        此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void LTDC_LayerCmd(LTDC_Layer_TypeDef* LTDC_Layerx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能通过设置LEN 的 LTCC_Layer位 */
        LTDC_Layerx->CR |= (uint32_t)LTDC_LxCR_LEN;
    } else {
        /* 通过清除LEN禁用LTCC_Layer位 */
        LTDC_Layerx->CR &= ~(uint32_t)LTDC_LxCR_LEN;
    }
}


/**
  * 简介:  获取当前位置。
  * 参数:  LTDC_Pos_InitStruct: 指向包含当前位置的 LTDC_PosTypeDef 结构的指针。
  * 返回值: 无
  */
LTDC_PosTypeDef LTDC_GetPosStatus(void) {
    LTDC_PosTypeDef LTDC_Pos_InitStruct;

    LTDC->CPSR &= ~(LTDC_CPSR_CYPOS | LTDC_CPSR_CXPOS);

    LTDC_Pos_InitStruct.LTDC_POSX = (uint32_t)(LTDC->CPSR >> 16);
    LTDC_Pos_InitStruct.LTDC_POSY = (uint32_t)(LTDC->CPSR & 0xFFFF);

    return LTDC_Pos_InitStruct;
}

/**
  * 简介:  用每个LTDC_Pos_InitStruct 成员的默认值填充该成员。
  * 参数:  LTDC_Pos_InitStruct: 指向LTDC_PosTypeDef 结构的指针，该结构将被初始化。
  * 返回值: 无
  */
void LTDC_PosStructInit(LTDC_PosTypeDef* LTDC_Pos_InitStruct) {
    LTDC_Pos_InitStruct->LTDC_POSX = 0x00;
    LTDC_Pos_InitStruct->LTDC_POSY = 0x00;
}

/**
  * 简介:  检查是否设置了指定的 LTDC 标志。
  * 
  * 参数:  LTDC_CD: 指定要检查的标志。
  *   此参数可以是以下值之一:
  *     @arg LTDC_CD_VDES:  垂直数据启用的当前状态。
  *     @arg LTDC_CD_HDES:  水平数据启用的当前状态。
  *     @arg LTDC_CD_VSYNC: 垂直同步当前状态。
  *     @arg LTDC_CD_HSYNC: 水平同步化的当前状态。
  * 
  * 返回值: 新状态-> LTDC_CD (SET or RESET).
  */
FlagStatus LTDC_GetCDStatus(uint32_t LTDC_CD) {
    FlagStatus bitstatus;

    /* 检查参数 */
    assert_param(IS_LTDC_GET_CD(LTDC_CD));

    if ((LTDC->CDSR & LTDC_CD) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  设置和配置颜色键控。
  * 参数:  LTDC_colorkeying_InitStruct: 指向LTDC_ColorKeying_InitTypeDef 结构的指针，
  *                                     该结构包含颜色键控配置。
  * 参数:  LTDC_layerx: 选择要配置的层，这个参数可以是以下值之一: 
  *                     LTDC_Layer1, LTDC_Layer2
  * 返回值: 无
  */
void LTDC_ColorKeyingConfig(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_ColorKeying_InitTypeDef* LTDC_colorkeying_InitStruct, FunctionalState NewState) {
    uint32_t ckgreen = 0;
    uint32_t ckred = 0;

    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_LTDC_CKEYING(LTDC_colorkeying_InitStruct->LTDC_ColorKeyBlue));
    assert_param(IS_LTDC_CKEYING(LTDC_colorkeying_InitStruct->LTDC_ColorKeyGreen));
    assert_param(IS_LTDC_CKEYING(LTDC_colorkeying_InitStruct->LTDC_ColorKeyRed));

    if (NewState != DISABLE) {
        /* 使能通过设置 COLKEN设置LTDC颜色键控位 */
        LTDC_Layerx->CR |= (uint32_t)LTDC_LxCR_COLKEN;

        /* 设置颜色关键帧值 */
        ckgreen = (LTDC_colorkeying_InitStruct->LTDC_ColorKeyGreen << 8);
        ckred = (LTDC_colorkeying_InitStruct->LTDC_ColorKeyRed << 16);
        LTDC_Layerx->CKCR  &= ~(LTDC_LxCKCR_CKBLUE | LTDC_LxCKCR_CKGREEN | LTDC_LxCKCR_CKRED);
        LTDC_Layerx->CKCR |= (LTDC_colorkeying_InitStruct->LTDC_ColorKeyBlue | ckgreen | ckred);
    } else {
        /* 通过清除 COLKEN禁用LTCC颜色键控位 */
        LTDC_Layerx->CR &= ~(uint32_t)LTDC_LxCR_COLKEN;
    }

    /* 重新加载阴影寄存器 */
    LTDC->SRCR = LTDC_IMReload;
}

/**
  * 简介:  用每个LTDC_colorkeying_InitStruct 成员的默认值填充其默认值。
  * 参数:  LTDC_colorkeying_InitStruct: 指向LTDC_ColorKeying_InitTypeDef 结构
  *                                     的指针，它将被初始化,被初始化。
  * 返回值: 无
  */
void LTDC_ColorKeyingStructInit(LTDC_ColorKeying_InitTypeDef* LTDC_colorkeying_InitStruct) {
    /*!< 初始化颜色键控值 */
    LTDC_colorkeying_InitStruct->LTDC_ColorKeyBlue = 0x00;
    LTDC_colorkeying_InitStruct->LTDC_ColorKeyGreen = 0x00;
    LTDC_colorkeying_InitStruct->LTDC_ColorKeyRed = 0x00;
}


/**
  * 简介:  启用或禁用 CLUT。
  * 参数:  LTDC_layerx: 选择要配置的层，这个参数可以是以下值之一:
  *        LTDC_Layer1, LTDC_Layer2
  * 参数:  NewState: 新状态-> 此参数可以是: 
  *        ENABLE 或 DISABLE。
  * 返回值: 无
  */
void LTDC_CLUTCmd(LTDC_Layer_TypeDef* LTDC_Layerx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 使能CLUT by setting CLUTEN 位 */
        LTDC_Layerx->CR |= (uint32_t)LTDC_LxCR_CLUTEN;
    } else {
        /* 通过清除 CLUTEN禁用 CLUT位 */
        LTDC_Layerx->CR &= ~(uint32_t)LTDC_LxCR_CLUTEN;
    }

    /* 重新加载阴影寄存器 */
    LTDC->SRCR = LTDC_IMReload;
}

/**
  * 简介:  配置 CLUT。
  * 参数: LTDC_CLUT_InitStruct: 指向包含 CLUT配置的
  *                              LTDC_CLUT_InitTypeDef 结构的指针。
  * 参数:  LTDC_layerx: 选择要配置的层，这个参数可以是以
  *                     下值之一: LTDC_Layer1, LTDC_Layer2
  * 返回值: 无
  */
void LTDC_CLUTInit(LTDC_Layer_TypeDef* LTDC_Layerx, LTDC_CLUT_InitTypeDef* LTDC_CLUT_InitStruct) {
    uint32_t green = 0;
    uint32_t red = 0;
    uint32_t clutadd = 0;

    /* 检查参数 */
    assert_param(IS_LTDC_CLUTWR(LTDC_CLUT_InitStruct->LTDC_CLUTAdress));
    assert_param(IS_LTDC_CLUTWR(LTDC_CLUT_InitStruct->LTDC_RedValue));
    assert_param(IS_LTDC_CLUTWR(LTDC_CLUT_InitStruct->LTDC_GreenValue));
    assert_param(IS_LTDC_CLUTWR(LTDC_CLUT_InitStruct->LTDC_BlueValue));

    /* 指定CLUT 地址和 RGB值 */
    green = (LTDC_CLUT_InitStruct->LTDC_GreenValue << 8);
    red = (LTDC_CLUT_InitStruct->LTDC_RedValue << 16);
    clutadd = (LTDC_CLUT_InitStruct->LTDC_CLUTAdress << 24);
    LTDC_Layerx->CLUTWR  = (clutadd | LTDC_CLUT_InitStruct->LTDC_BlueValue | \
                            green | red);
}

/**
  * 简介:  用每个LTDC_CLUT_InitStruct 成员的默认值填充该成员。
  * 参数:  LTDC_CLUT_InitStruct: 指向LTDC_CLUT_InitTypeDef 结构的指针，该结构将被初始化。
  * 返回值: 无
  */
void LTDC_CLUTStructInit(LTDC_CLUT_InitTypeDef* LTDC_CLUT_InitStruct) {
    /*!< Initialize the CLUT address and RGB values */
    LTDC_CLUT_InitStruct->LTDC_CLUTAdress = 0x00;
    LTDC_CLUT_InitStruct->LTDC_BlueValue = 0x00;
    LTDC_CLUT_InitStruct->LTDC_GreenValue = 0x00;
    LTDC_CLUT_InitStruct->LTDC_RedValue = 0x00;
}

/**
  * 简介:  重新配置图层位置。
  * 参数:  OffsetX:从活动宽度开始的水平偏移。
  * 参数:  OffsetY: 从开始活动的高度开始的垂直偏移。
  * 参数:  LTDC_layerx: 选择要配置的层，这个参数可以是以下值之一:
  *       LTDC_Layer1, LTDC_Layer2。
  * 返回值: 在层位置重新配置后，必须重新加载阴影寄存器的值。
  */
void LTDC_LayerPosition(LTDC_Layer_TypeDef* LTDC_Layerx, uint16_t OffsetX, uint16_t OffsetY) {
    uint32_t tempreg, temp;
    uint32_t horizontal_start;
    uint32_t horizontal_stop;
    uint32_t vertical_start;
    uint32_t vertical_stop;

    LTDC_Layerx->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
    LTDC_Layerx->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);

    /* 重新配置水平和垂直起始位置 */
    tempreg = LTDC->BPCR;
    horizontal_start = (tempreg >> 16) + 1 + OffsetX;
    vertical_start = (tempreg & 0xFFFF) + 1 + OffsetY;

    /* 重新配置水平和垂直停止位置 */
    /* 获取每像素的字节数 */

    tempreg = LTDC_Layerx->PFCR;

    if (tempreg == LTDC_Pixelformat_ARGB8888) {
        temp = 4;
    } else if (tempreg == LTDC_Pixelformat_RGB888) {
        temp = 3;
    } else if ((tempreg == LTDC_Pixelformat_ARGB4444) ||
               (tempreg == LTDC_Pixelformat_RGB565)    ||
               (tempreg == LTDC_Pixelformat_ARGB1555)  ||
               (tempreg == LTDC_Pixelformat_AL88)) {
        temp = 2;
    } else {
        temp = 1;
    }

    tempreg = LTDC_Layerx->CFBLR;
    horizontal_stop = (((tempreg & 0x1FFF) - 3) / temp) + horizontal_start - 1;

    tempreg = LTDC_Layerx->CFBLNR;
    vertical_stop = (tempreg & 0x7FF) + vertical_start - 1;

    LTDC_Layerx->WHPCR = horizontal_start | (horizontal_stop << 16);
    LTDC_Layerx->WVPCR = vertical_start | (vertical_stop << 16);
}

/**
  * 简介:  重新配置常量 alpha。
  * 参数:  ConstantAlpha: 恒定的阿尔法值。
  * 参数:  LTDC_layerx: 选择要配置的层，这个参数可以是以下值之一:
  *        LTDC_Layer1, LTDC_Layer2。
  * 返回值: 在恒定阿尔法重新配置后，必须重新加载影子寄存器的值。
  */
void LTDC_LayerAlpha(LTDC_Layer_TypeDef* LTDC_Layerx, uint8_t ConstantAlpha) {
    /* 重新配置常数alpha值 */
    LTDC_Layerx->CACR = ConstantAlpha;
}

/**
  * 简介:  重新配置图层地址。
  * 参数:  Address:彩色帧缓冲器的起始地址。
  * 参数:  LTDC_layerx: 选择要配置的层，
  *        这个参数可以是以下值之一: LTDC_Layer1, 
  *                                LTDC_Layer2。
  * 返回值:在层地址重新配置后，必须重新加载影子寄存器的值。
  */
void LTDC_LayerAddress(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t Address) {
    /* Re配置彩色帧缓冲区起始地址 */
    LTDC_Layerx->CFBAR = Address;
}

/**
  * 简介:  重新配置图层大小。
  * 参数:  Width: 图层窗口宽度。
  * 参数:  Height: 图层窗口的高度。
  * 参数:  LTDC_layerx: 选择要配置的图层，这个参数可以是以下值之一:
  *        LTDC_Layer1, LTDC_Layer2。
  * 返回值: 在层大小重新配置后，必须重新加载影子寄存器的值。
  */
void LTDC_LayerSize(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t Width, uint32_t Height) {
    uint8_t temp;
    uint32_t tempreg;
    uint32_t horizontal_start;
    uint32_t horizontal_stop;
    uint32_t vertical_start;
    uint32_t vertical_stop;

    tempreg = LTDC_Layerx->PFCR;

    if (tempreg == LTDC_Pixelformat_ARGB8888) {
        temp = 4;
    } else if (tempreg == LTDC_Pixelformat_RGB888) {
        temp = 3;
    } else if ((tempreg == LTDC_Pixelformat_ARGB4444) || \
               (tempreg == LTDC_Pixelformat_RGB565)    || \
               (tempreg == LTDC_Pixelformat_ARGB1555)  || \
               (tempreg == LTDC_Pixelformat_AL88)) {
        temp = 2;
    } else {
        temp = 1;
    }

    /* 更新水平和垂直停止 */
    tempreg = LTDC_Layerx->WHPCR;
    horizontal_start = (tempreg & 0x1FFF);
    horizontal_stop = Width + horizontal_start - 1;

    tempreg = LTDC_Layerx->WVPCR;
    vertical_start = (tempreg & 0x1FFF);
    vertical_stop = Height + vertical_start - 1;

    LTDC_Layerx->WHPCR = horizontal_start | (horizontal_stop << 16);
    LTDC_Layerx->WVPCR = vertical_start | (vertical_stop << 16);

    /* Re以字节为单位配置彩色帧缓冲区间距 */
    LTDC_Layerx->CFBLR  = ((Width * temp) << 16) | ((Width * temp) + 3);

    /* Re配置帧缓冲区行号 */
    LTDC_Layerx->CFBLNR  = Height;

}

/**
  * 简介:  重新配置图层像素格式。
  * 参数:  PixelFormat:重新配置像素格式，
  *         这个参数可以是以下值之一: 
  *                               @ref LTDC_Pixelformat。
  * 参数:  LTDC_layerx: 选择要配置的图层，
  *         这个参数可以是以下值之一: 
  *                               LTDC_Layer1, 
  *                               LTDC_Layer2。
  * 返回值: 阴影寄存器值的重新加载必须在层像素格式重新配置后应用。
  */
void LTDC_LayerPixelFormat(LTDC_Layer_TypeDef* LTDC_Layerx, uint32_t PixelFormat) {
    uint8_t temp;
    uint32_t tempreg;

    tempreg = LTDC_Layerx->PFCR;

    if (tempreg == LTDC_Pixelformat_ARGB8888) {
        temp = 4;
    } else if (tempreg == LTDC_Pixelformat_RGB888) {
        temp = 3;
    } else if ((tempreg == LTDC_Pixelformat_ARGB4444) || \
               (tempreg == LTDC_Pixelformat_RGB565)    || \
               (tempreg == LTDC_Pixelformat_ARGB1555)  || \
               (tempreg == LTDC_Pixelformat_AL88)) {
        temp = 2;
    } else {
        temp = 1;
    }

    tempreg = (LTDC_Layerx->CFBLR >> 16);
    tempreg = (tempreg / temp);

    if (PixelFormat == LTDC_Pixelformat_ARGB8888) {
        temp = 4;
    } else if (PixelFormat == LTDC_Pixelformat_RGB888) {
        temp = 3;
    } else if ((PixelFormat == LTDC_Pixelformat_ARGB4444) || \
               (PixelFormat == LTDC_Pixelformat_RGB565)    || \
               (PixelFormat == LTDC_Pixelformat_ARGB1555)  || \
               (PixelFormat == LTDC_Pixelformat_AL88)) {
        temp = 2;
    } else {
        temp = 1;
    }

    /* Re以字节为单位配置彩色帧缓冲区间距 */
    LTDC_Layerx->CFBLR  = ((tempreg * temp) << 16) | ((tempreg * temp) + 3);

    /* Re配置彩色帧缓冲区起始地址 */
    LTDC_Layerx->PFCR = PixelFormat;

}


/** @defgroup LTDC_Group2 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
            ##### 中断和标记管理函数 #####
 ===============================================================================

    [..] 本节提供的功能允许配置LTDC中断，并获得状态，清除标志和中断等待位。

    [..] LTDC提供了4个中断源和4个标志。

    *** 标志 ***
    =============
    [..]
      (+) LTDC_FLAG_LI:线路中断标志。
      (+) LTDC_FLAG_FU: FIFO Underrun 中断标志。
      (+) LTDC_FLAG_TERR:传输错误中断标志。
      (+) LTDC_FLAG_RR: 寄存器重新加载中断标志。

    *** 中断 ***
    ==================
    [..]
      (+) LTDC_IT_LI: 当达到一个编程的线路时，会产生线路中断。线路中断的位置是在LTDC_LIPR 寄存器中编程的。
      (+) LTDC_IT_FU: 当从一个空层FIFO请求一个像素时，产生FIFO Underrun中断。
      (+) LTDC_IT_TERR: 传输错误中断是在数据传输过程中发生AHB总线错误时产生的。
      (+) LTDC_IT_RR:当在垂直消隐期间执行影子寄存器重新加载时，产生寄存器重新加载中断。

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 LTDC 的中断。
  * 参数:  LTDC_IT: 指定要启用或禁用的 LTDC 中断源。
  *   此参数可以是以下值的任意组合:
  *         @arg LTDC_IT_LI:    线路中断使能。
  *         @arg LTDC_IT_FU:    FIFO Underrun中断启用。
  *         @arg LTDC_IT_TERR:  传输错误中断启用。
  *         @arg LTDC_IT_RR:    寄存器重新加载中断使能。
  * 参数: NewState 新状态->指定的 LTDC 中断。
  *       此参数可以是: ENABLE 或 DISABLE。
  * 返回值: 无
  */
void LTDC_ITConfig(uint32_t LTDC_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_LTDC_IT(LTDC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        LTDC->IER |= LTDC_IT;
    } else {
        LTDC->IER &= (uint32_t)~LTDC_IT;
    }
}

/**
  * 简介:  检查是否设置了指定的 LTDC 标志。
  * 参数:  LTDC_FLAG: 指定要检查的标志。
  *   此参数可以是以下值之一:
  *     @arg LTDC_FLAG_LI: 线路中断标志。
  *     @arg LTDC_FLAG_FU: FIFO Underrun 中断标志。
  *     @arg LTDC_FLAG_TERR: 传输错误中断标志。
  *     @arg LTDC_FLAG_RR: 寄存器重新加载中断标志。
  * 返回值: 新状态-> LTDC_FLAG (SET or RESET).
  */
FlagStatus LTDC_GetFlagStatus(uint32_t LTDC_FLAG) {
    FlagStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_LTDC_FLAG(LTDC_FLAG));

    if ((LTDC->ISR & LTDC_FLAG) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 LTDC 的挂起标志。
  * 参数:  LTDC_FLAG: 指定要清除的标志。
  *   此参数可以是以下值的任意组合:
  *     @arg LTDC_FLAG_LI: 线路中断标志。
  *     @arg LTDC_FLAG_FU: FIFO Underrun 中断标志。
  *     @arg LTDC_FLAG_TERR: 传输错误中断标志。
  *     @arg LTDC_FLAG_RR: 寄存器重新加载中断标志。
  * 返回值: 无
  */
void LTDC_ClearFlag(uint32_t LTDC_FLAG) {
    /* 检查参数 */
    assert_param(IS_LTDC_FLAG(LTDC_FLAG));

    /* 清除相应的 LTDC 标志 */
    LTDC->ICR = (uint32_t)LTDC_FLAG;
}

/**
  * 简介:  检查指定的 LTDC 的中断是否发生。
  * 参数:  LTDC_IT: 指定要检查的 LTDC中断源。
  *   此参数可以是以下值之一:
  *     @arg LTDC_IT_LI:    线路中断使能。
  *     @arg LTDC_IT_FU: FIFO Underrun 中断使能。
  *     @arg LTDC_IT_TERR: 传输错误中断启用。
  *     @arg LTDC_IT_RR: 寄存器重新加载中断启用。
  * 返回值: The 新状态-> LTDC_IT (SET or RESET).
  */
ITStatus LTDC_GetITStatus(uint32_t LTDC_IT) {
    ITStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_LTDC_IT(LTDC_IT));

    if ((LTDC->ISR & LTDC_IT) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    if (((LTDC->IER & LTDC_IT) != (uint32_t)RESET) && (bitstatus != (uint32_t)RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除 LTDC 的中断挂起位。
  * 参数:  LTDC_IT: 指定要清除的中断等待位。
  *   此参数可以是以下值的任意组合:
  *     @arg LTDC_IT_LIE:    Line 中断.
  *     @arg LTDC_IT_FUIE:   FIFO 欠载 中断.
  *     @arg LTDC_IT_TERRIE: Transfer 错误中断.
  *     @arg LTDC_IT_RRIE:   Register 重载中断.
  * 返回值: 无
  */
void LTDC_ClearITPendingBit(uint32_t LTDC_IT) {
    /* 检查参数 */
    assert_param(IS_LTDC_IT(LTDC_IT));

    /* 清除相应的 LTDC 中断 */
    LTDC->ICR = (uint32_t)LTDC_IT;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
