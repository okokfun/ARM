/**
  ******************************************************************************
  * 文件:    stm32f4xx_dsi.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，用于管理显示串行接口(DSI)的以下功能:
  *           + 初始化和配置
  *           + 数据传输管理功能
  *           + 低功耗功能
  *           + 中断和标志管理
  *
@verbatim

 ===================================================================
                  ##### 如何使用这个驱动程序 #####
 ===================================================================
 [..]

@endverbatim
  *
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
#include "stm32f4xx_dsi.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */
/** @addtogroup DSI
  * 简介: DSI 驱动模块
  */
#if defined(STM32F469_479xx)

/* Private types -------------------------------------------------------------*/
/* 私有宏s -----------------------------------------------------------*/
/** @addtogroup DSI_Private_Constants
  */
#define DSI_TIMEOUT_VALUE ((uint32_t)1000)  /* 1s */

#define DSI_ERROR_ACK_MASK (DSI_ISR0_AE0 | DSI_ISR0_AE1 | DSI_ISR0_AE2 | DSI_ISR0_AE3 | \
                            DSI_ISR0_AE4 | DSI_ISR0_AE5 | DSI_ISR0_AE6 | DSI_ISR0_AE7 | \
                            DSI_ISR0_AE8 | DSI_ISR0_AE9 | DSI_ISR0_AE10 | DSI_ISR0_AE11 | \
                            DSI_ISR0_AE12 | DSI_ISR0_AE13 | DSI_ISR0_AE14 | DSI_ISR0_AE15)
#define DSI_ERROR_PHY_MASK (DSI_ISR0_PE0 | DSI_ISR0_PE1 | DSI_ISR0_PE2 | DSI_ISR0_PE3 | DSI_ISR0_PE4)
#define DSI_ERROR_TX_MASK  DSI_ISR1_TOHSTX
#define DSI_ERROR_RX_MASK  DSI_ISR1_TOLPRX
#define DSI_ERROR_ECC_MASK (DSI_ISR1_ECCSE | DSI_ISR1_ECCME)
#define DSI_ERROR_CRC_MASK DSI_ISR1_CRCE
#define DSI_ERROR_PSE_MASK DSI_ISR1_PSE
#define DSI_ERROR_EOT_MASK DSI_ISR1_EOTPE
#define DSI_ERROR_OVF_MASK DSI_ISR1_LPWRE
#define DSI_ERROR_GEN_MASK (DSI_ISR1_GCWRE | DSI_ISR1_GPWRE | DSI_ISR1_GPTXE | DSI_ISR1_GPRDE | DSI_ISR1_GPRXE)

#define DSI_MAX_RETURN_PKT_SIZE ((uint32_t)0x00000037) /*!< Maximum return packet 配置*/

/* 私有变量 ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* 私有宏s ------------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
static void DSI_ConfigPacketHeader(DSI_TypeDef *DSIx, uint32_t ChannelID, uint32_t DataType, uint32_t Data0, uint32_t Data1);
/* 私有函数 ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup DSI_Exported_Functions
  */

/** @defgroup DSI_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
                ##### 初始化和配置函数 #####
 ===============================================================================
    [..]  本节提供的功能允许:
      (+) 初始化并配置 DSI
      (+) 解除对 DSI 的初始化

@endverbatim
  */

/**
  * 简介:  将 DSI 外设寄存器取消初始化为其默认复位值。
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 返回值: 无
  */
void DSI_DeInit(DSI_TypeDef *DSIx) {
    /* 禁用 DSI wrapper */
    DSIx->WCR &= ~DSI_WCR_DSIEN;

    /* 禁用 DSI host */
    DSIx->CR &= ~DSI_CR_EN;

    /* D-PHY 时钟和数字禁用 */
    DSIx->PCTLR &= ~(DSI_PCTLR_CKE | DSI_PCTLR_DEN);

    /* 关闭DSI PLL */
    DSIx->WRPCR &= ~DSI_WRPCR_PLLEN;

    /* 禁用 regulator */
    DSIx->WRPCR &= ~DSI_WRPCR_REGEN;

    /* 检查参数 */
    assert_param(IS_DSI_ALL_PERIPH(DSIx));

    if(DSIx == DSI) {
        /* 使能DSI 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_DSI, ENABLE);
        /* 释放DSI from 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_DSI, DISABLE);
    }
}

/**
  * 简介: 将 DSIx 外设寄存器取消初始化为其默认复位值。
  * 
  * 参数: DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数: DSI_InitStruct: 指向 DSI_InitTypeDef 结构的指针。
  *                       该结构包含指定 DSI 外设的配置信息。
  * 
  * 参数: DSI_InitTIMStruct: 指向 DSI_TIMTypeDef 结构的指针，
  *                          该结构包含指定 DSI 定时器的配置信息。
  * 
  * 返回值: 无
  */
void DSI_Init(DSI_TypeDef *DSIx, DSI_InitTypeDef* DSI_InitStruct, DSI_PLLInitTypeDef *PLLInit) {
    uint32_t unitIntervalx4 = 0;
    uint32_t tempIDF = 0;

    /* 检查函数参数 */
    assert_param(IS_DSI_PLL_NDIV(PLLInit->PLLNDIV));
    assert_param(IS_DSI_PLL_IDF(PLLInit->PLLIDF));
    assert_param(IS_DSI_PLL_ODF(PLLInit->PLLODF));
    assert_param(IS_DSI_AUTO_CLKLANE_CONTROL(DSI_InitStruct->AutomaticClockLaneControl));
    assert_param(IS_DSI_NUMBER_OF_LANES(DSI_InitStruct->NumberOfLanes));

    /**************** 打开调节器并启用 DSI PLL ****************/

    /* 启用监管者 */
    DSIx->WRPCR |= DSI_WRPCR_REGEN;

    /* 等待调节器准备就绪 */
    while(DSI_GetFlagStatus(DSIx, DSI_FLAG_RRS) == RESET )
    {}

    /* 设置PPLL分频因子 */
    DSIx->WRPCR &= ~(DSI_WRPCR_PLL_NDIV | DSI_WRPCR_PLL_IDF | DSI_WRPCR_PLL_ODF);
    DSIx->WRPCR |= (((PLLInit->PLLNDIV) << 2) | ((PLLInit->PLLIDF) << 11) | ((PLLInit->PLLODF) << 16));

    /* 启用 DSI PLL */
    DSIx->WRPCR |= DSI_WRPCR_PLLEN;

    /* 等待PLL锁定 */
    while(DSI_GetFlagStatus(DSIx, DSI_FLAG_PLLLS) == RESET)
    {}

    /*************************** 设置PHY参数 ***************************/

    /* D-PHY 时钟和数字启用*/
    DSIx->PCTLR |= (DSI_PCTLR_CKE | DSI_PCTLR_DEN);

    /* Clock lane 配置*/
    DSIx->CLCR &= ~(DSI_CLCR_DPCC | DSI_CLCR_ACR);
    DSIx->CLCR |= (DSI_CLCR_DPCC | DSI_InitStruct->AutomaticClockLaneControl);

    /* 配置活动数据通道的数量 */
    DSIx->PCONFR &= ~DSI_PCONFR_NL;
    DSIx->PCONFR |= DSI_InitStruct->NumberOfLanes;

    /************************ 设置 DSI 时钟参数 ************************/
    /* 设置 TTX转义时钟分频因子 */
    DSIx->CCR &= ~DSI_CCR_TXECKDIV;
    DSIx->CCR = DSI_InitStruct->TXEscapeCkdiv;

    /* 以0.25 ns为单位计算高速模式下的位周期(UIX4) */
    /* 方程式为 : UIX4 = IntegerPart( (1000/F_PHY_Mhz) * 4 )          */
    /* Where : F_PHY_Mhz = (NDIV * HSE_Mhz) / (IDF * ODF)                    */
    tempIDF = (PLLInit->PLLIDF > 0) ? PLLInit->PLLIDF : 1;
    unitIntervalx4 = (4000000 * tempIDF * (1 << PLLInit->PLLODF)) / ((HSE_VALUE / 1000) * PLLInit->PLLNDIV);

    /* 设置高速模式下的位周期 */
    DSIx->WPCR[0] &= ~DSI_WPCR0_UIX4;
    DSIx->WPCR[0] |= unitIntervalx4;

    /****************************** 错误管理 *****************************/
    /* 禁用所有错误中断 */
    DSIx->IER[0] = 0;
    DSIx->IER[1] = 0;
}

/**
  * 简介: 用默认值填充每个 DSI_InitStruct 成员。
  * 
  * 参数: DSI_InitStruct: 指向 DSI_InitTypeDef 结构的指针，该结构将被初始化。
  * 
  * 返回值: 无
  */
void DSI_StructInit(DSI_InitTypeDef* DSI_InitStruct, DSI_HOST_TimeoutTypeDef* DSI_HOST_TimeoutInitStruct) {
    /*--------------- 重置 DSI初始化结构参数值 ---------------*/
    /* 初始化 AutomaticClockLaneControl 成员 */
    DSI_InitStruct->AutomaticClockLaneControl = DSI_AUTO_CLK_LANE_CTRL_DISABLE;
    /* 初始化 NumberOfLanes 成员 */
    DSI_InitStruct->NumberOfLanes = DSI_ONE_DATA_LANE;
    /* 初始化TX Escape时钟分区 */
    DSI_InitStruct->TXEscapeCkdiv = 0;

    /*--------------- 重置 DSI 定时初始化结构参数值 -------*/
    /* 初始化 TimeoutCkdiv 成员 */
    DSI_HOST_TimeoutInitStruct->TimeoutCkdiv = 0;
    /* 初始化 HighSpeedTransmissionTimeout 成员 */
    DSI_HOST_TimeoutInitStruct->HighSpeedTransmissionTimeout = 0;
    /* 初始化 LowPowerReceptionTimeout 成员 */
    DSI_HOST_TimeoutInitStruct->LowPowerReceptionTimeout = 0;
    /* 初始化 HighSpeedReadTimeout 成员 */
    DSI_HOST_TimeoutInitStruct->HighSpeedReadTimeout = 0;
    /* 初始化 LowPowerReadTimeout 成员 */
    DSI_HOST_TimeoutInitStruct->LowPowerReadTimeout = 0;
    /* 初始化 HighSpeedWriteTimeout 成员 */
    DSI_HOST_TimeoutInitStruct->HighSpeedWriteTimeout = 0;
    /* 初始化 HighSpeedWritePrespMode 成员 */
    DSI_HOST_TimeoutInitStruct->HighSpeedWritePrespMode = 0;
    /* 初始化 LowPowerWriteTimeout 成员 */
    DSI_HOST_TimeoutInitStruct->LowPowerWriteTimeout = 0;
    /* 初始化 BTATimeout 成员 */
    DSI_HOST_TimeoutInitStruct->BTATimeout = 0;
}

/**
  * 简介:  配置通用接口回读的虚拟通道ID。
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  VirtualChannelID: 虚拟通道ID
  * 
  * 返回值: 无
  */
void DSI_SetGenericVCID(DSI_TypeDef *DSIx, uint32_t VirtualChannelID) {
    /* 更新 GVCID 寄存器 */
    DSIx->GVCIDR &= ~DSI_GVCIDR_VCID;
    DSIx->GVCIDR |= VirtualChannelID;
}

/**
  * 简介:  选择视频模式并配置相应的参数
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  VidCfg: 指向一个包含 DSI视频模式配置参数的 DSI_VidCfgTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void DSI_ConfigVideoMode(DSI_TypeDef *DSIx, DSI_VidCfgTypeDef *VidCfg) {
    /* 检查参数 */
    assert_param(IS_DSI_COLOR_CODING(VidCfg->ColorCoding));
    assert_param(IS_DSI_VIDEO_MODE_TYPE(VidCfg->Mode));
    assert_param(IS_DSI_LP_COMMAND(VidCfg->LPCommandEnable));
    assert_param(IS_DSI_LP_HFP(VidCfg->LPHorizontalFrontPorchEnable));
    assert_param(IS_DSI_LP_HBP(VidCfg->LPHorizontalBackPorchEnable));
    assert_param(IS_DSI_LP_VACTIVE(VidCfg->LPVerticalActiveEnable));
    assert_param(IS_DSI_LP_VFP(VidCfg->LPVerticalFrontPorchEnable));
    assert_param(IS_DSI_LP_VBP(VidCfg->LPVerticalBackPorchEnable));
    assert_param(IS_DSI_LP_VSYNC(VidCfg->LPVerticalSyncActiveEnable));
    assert_param(IS_DSI_FBTAA(VidCfg->FrameBTAAcknowledgeEnable));
    assert_param(IS_DSI_DE_POLARITY(VidCfg->DEPolarity));
    assert_param(IS_DSI_VSYNC_POLARITY(VidCfg->VSPolarity));
    assert_param(IS_DSI_HSYNC_POLARITY(VidCfg->HSPolarity));

    /* 检查仅在18位模式下的 LooselyPacked 变体 */
    if(VidCfg->ColorCoding == DSI_RGB666) {
        assert_param(IS_DSI_LOOSELY_PACKED(VidCfg->LooselyPacked));
    }

    /* 通过重置 CMDM 和 DSIM 来选择视频模式位 */
    DSIx->MCR &= ~DSI_MCR_CMDM;
    DSIx->WCFGR &= ~DSI_WCFGR_DSIM;

    /* 配置视频模式传输类型 */
    DSIx->VMCR &= ~DSI_VMCR_VMT;
    DSIx->VMCR |= VidCfg->Mode;

    /* 配置视频数据包大小 */
    DSIx->VPCR &= ~DSI_VPCR_VPSIZE;
    DSIx->VPCR |= VidCfg->PacketSize;

    /* 设置要通过 DSI 链接传输的块数 */
    DSIx->VCCR &= ~DSI_VCCR_NUMC;
    DSIx->VCCR |= VidCfg->NumberOfChunks;

    /* 设置空数据包的大小 */
    DSIx->VNPCR &= ~DSI_VNPCR_NPSIZE;
    DSIx->VNPCR |= VidCfg->NullPacketSize;

    /* 选择这个 LTCC 接口流量的虚拟通道 */
    DSIx->LVCIDR &= ~DSI_LVCIDR_VCID;
    DSIx->LVCIDR |= VidCfg->VirtualChannelID;

    /* 配置控制信号的极性 */
    DSIx->LPCR &= ~(DSI_LPCR_DEP | DSI_LPCR_VSP | DSI_LPCR_HSP);
    DSIx->LPCR |= (VidCfg->DEPolarity | VidCfg->VSPolarity | VidCfg->HSPolarity);

    /* 选择这个主机的颜色编码 */
    DSIx->LCOLCR &= ~DSI_LCOLCR_COLC;
    DSIx->LCOLCR |= VidCfg->ColorCoding;

    /* 选择这个包装的颜色编码 */
    DSIx->WCFGR &= ~DSI_WCFGR_COLMUX;
    DSIx->WCFGR |= ((VidCfg->ColorCoding) << 1);

    /* 启用/禁用松散封装变体到18位配置*/
    if(VidCfg->ColorCoding == DSI_RGB666) {
        DSIx->LCOLCR &= ~DSI_LCOLCR_LPE;
        DSIx->LCOLCR |= VidCfg->LooselyPacked;
    }

    /* 设置通道字节时钟周期内水平同步激活(HSA) */
    DSIx->VHSACR &= ~DSI_VHSACR_HSA;
    DSIx->VHSACR |= VidCfg->HorizontalSyncActive;

    /* 设置通道字节时钟周期中的水平反向通道(HBP) */
    DSIx->VHBPCR &= ~DSI_VHBPCR_HBP;
    DSIx->VHBPCR |= VidCfg->HorizontalBackPorch;

    /* 设置通道字节时钟周期中的总线路时间(HLINE=HSA+HBP+HACT+HFP) */
    DSIx->VLCR &= ~DSI_VLCR_HLINE;
    DSIx->VLCR |= VidCfg->HorizontalLine;

    /* 设置垂直同步激活(VSA) */
    DSIx->VVSACR &= ~DSI_VVSACR_VSA;
    DSIx->VVSACR |= VidCfg->VerticalSyncActive;

    /* 设置垂直后门(VBP)*/
    DSIx->VVBPCR &= ~DSI_VVBPCR_VBP;
    DSIx->VVBPCR |= VidCfg->VerticalBackPorch;

    /* 设置垂直前廊(VFP)*/
    DSIx->VVFPCR &= ~DSI_VVFPCR_VFP;
    DSIx->VVFPCR |= VidCfg->VerticalFrontPorch;

    /* 设置垂直活动期 */
    DSIx->VVACR &= ~DSI_VVACR_VA;
    DSIx->VVACR |= VidCfg->VerticalActive;

    /* 配置命令传输模式 */
    DSIx->VMCR &= ~DSI_VMCR_LPCE;
    DSIx->VMCR |= VidCfg->LPCommandEnable;

    /* 低功耗最大数据包大小 */
    DSIx->LPMCR &= ~DSI_LPMCR_LPSIZE;
    DSIx->LPMCR |= ((VidCfg->LPLargestPacketSize) << 16);

    /* 低功率 VACT 最大数据包大小 */
    DSIx->LPMCR &= ~DSI_LPMCR_VLPSIZE;
    DSIx->LPMCR |= VidCfg->LPVACTLargestPacketSize;

    /* 使能 HFP 期LP转换 */
    DSIx->VMCR &= ~DSI_VMCR_LPHFPE;
    DSIx->VMCR |= VidCfg->LPHorizontalFrontPorchEnable;

    /* 使能 HBP 期间的 LP转换 */
    DSIx->VMCR &= ~DSI_VMCR_LPHBPE;
    DSIx->VMCR |= VidCfg->LPHorizontalBackPorchEnable;

    /* 使能 VACT 期间的 LP转换 */
    DSIx->VMCR &= ~DSI_VMCR_LPVAE;
    DSIx->VMCR |= VidCfg->LPVerticalActiveEnable;

    /* 使能 VFP 期间的 LP转换 */
    DSIx->VMCR &= ~DSI_VMCR_LPVFPE;
    DSIx->VMCR |= VidCfg->LPVerticalFrontPorchEnable;

    /* 使能 VBP 时期的 LP转换 */
    DSIx->VMCR &= ~DSI_VMCR_LPVBPE;
    DSIx->VMCR |= VidCfg->LPVerticalBackPorchEnable;

    /* 使能垂直同步周期中的 LP转换 */
    DSIx->VMCR &= ~DSI_VMCR_LPVSAE;
    DSIx->VMCR |= VidCfg->LPVerticalSyncActiveEnable;

    /* 启用在帧结束时请求确认响应 */
    DSIx->VMCR &= ~DSI_VMCR_FBTAAE;
    DSIx->VMCR |= VidCfg->FrameBTAAcknowledgeEnable;
}

/**
  * 简介:  选择适应的命令模式并配置相应的参数
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  CmdCfg: 指向一个包含 DSI命令模式配置参数的 DSI_CmdCfgTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void DSI_ConfigAdaptedCommandMode(DSI_TypeDef *DSIx, DSI_CmdCfgTypeDef *CmdCfg) {
    /* 检查参数 */
    assert_param(IS_DSI_COLOR_CODING(CmdCfg->ColorCoding));
    assert_param(IS_DSI_TE_SOURCE(CmdCfg->TearingEffectSource));
    assert_param(IS_DSI_TE_POLARITY(CmdCfg->TearingEffectPolarity));
    assert_param(IS_DSI_AUTOMATIC_REFRESH(CmdCfg->AutomaticRefresh));
    assert_param(IS_DSI_VS_POLARITY(CmdCfg->VSyncPol));
    assert_param(IS_DSI_TE_ACK_REQUEST(CmdCfg->TEAcknowledgeRequest));
    assert_param(IS_DSI_DE_POLARITY(CmdCfg->DEPolarity));
    assert_param(IS_DSI_VSYNC_POLARITY(CmdCfg->VSPolarity));
    assert_param(IS_DSI_HSYNC_POLARITY(CmdCfg->HSPolarity));

    /* 通过设置 CMDM 和 DSIM选择命令模式位 */
    DSIx->MCR |= DSI_MCR_CMDM;
    DSIx->WCFGR &= ~DSI_WCFGR_DSIM;
    DSIx->WCFGR |= DSI_WCFGR_DSIM;

    /* 选择这个 LTCC 接口流量的虚拟通道 */
    DSIx->LVCIDR &= ~DSI_LVCIDR_VCID;
    DSIx->LVCIDR |= CmdCfg->VirtualChannelID;

    /* 配置控制信号的极性 */
    DSIx->LPCR &= ~(DSI_LPCR_DEP | DSI_LPCR_VSP | DSI_LPCR_HSP);
    DSIx->LPCR |= (CmdCfg->DEPolarity | CmdCfg->VSPolarity | CmdCfg->HSPolarity);

    /* 选择这个主机的颜色编码 */
    DSIx->LCOLCR &= ~DSI_LCOLCR_COLC;
    DSIx->LCOLCR |= CmdCfg->ColorCoding;

    /* 选择这个包装的颜色编码 */
    DSIx->WCFGR &= ~DSI_WCFGR_COLMUX;
    DSIx->WCFGR |= ((CmdCfg->ColorCoding) << 1);

    /* 配置写入内存命令允许的最大大小 */
    DSIx->LCCR &= ~DSI_LCCR_CMDSIZE;
    DSIx->LCCR |= CmdCfg->CommandSize;

    /* 配置撕裂效果来源和极性，并选择刷新模式 */
    DSIx->WCFGR &= ~(DSI_WCFGR_TESRC | DSI_WCFGR_TEPOL | DSI_WCFGR_AR | DSI_WCFGR_VSPOL);
    DSIx->WCFGR |= (CmdCfg->TearingEffectSource | CmdCfg->TearingEffectPolarity | CmdCfg->AutomaticRefresh | CmdCfg->VSyncPol);

    /* 配置撕裂效应确认请求 */
    DSIx->CMCR &= ~DSI_CMCR_TEARE;
    DSIx->CMCR |= CmdCfg->TEAcknowledgeRequest;

    /* 启用撕裂效果中断 */
    DSI_ITConfig(DSIx, DSI_IT_TE, ENABLE);
    /* 启用刷新中断结束 */
    DSI_ITConfig(DSIx, DSI_IT_ER, ENABLE);
}

/**
  * 简介:  配置命令传输模式:高速或低功率，并在数据包传输后启用/禁用确认请求
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  LPCmd: 指向包含 DSI命令传输模式配置参数的 DSI_LPCmdTypeDef 结构的指针
  * 
  * 返回值: 无
  */
void DSI_ConfigCommand(DSI_TypeDef *DSIx, DSI_LPCmdTypeDef *LPCmd) {
    assert_param(IS_DSI_LP_GSW0P(LPCmd->LPGenShortWriteNoP));
    assert_param(IS_DSI_LP_GSW1P(LPCmd->LPGenShortWriteOneP));
    assert_param(IS_DSI_LP_GSW2P(LPCmd->LPGenShortWriteTwoP));
    assert_param(IS_DSI_LP_GSR0P(LPCmd->LPGenShortReadNoP));
    assert_param(IS_DSI_LP_GSR1P(LPCmd->LPGenShortReadOneP));
    assert_param(IS_DSI_LP_GSR2P(LPCmd->LPGenShortReadTwoP));
    assert_param(IS_DSI_LP_GLW(LPCmd->LPGenLongWrite));
    assert_param(IS_DSI_LP_DSW0P(LPCmd->LPDcsShortWriteNoP));
    assert_param(IS_DSI_LP_DSW1P(LPCmd->LPDcsShortWriteOneP));
    assert_param(IS_DSI_LP_DSR0P(LPCmd->LPDcsShortReadNoP));
    assert_param(IS_DSI_LP_DLW(LPCmd->LPDcsLongWrite));
    assert_param(IS_DSI_LP_MRDP(LPCmd->LPMaxReadPacket));
    assert_param(IS_DSI_ACK_REQUEST(LPCmd->AcknowledgeRequest));

    /* 选择高速或低功率进行命令传输 */
    DSIx->CMCR &= ~(DSI_CMCR_GSW0TX | \
                    DSI_CMCR_GSW1TX | \
                    DSI_CMCR_GSW2TX | \
                    DSI_CMCR_GSR0TX | \
                    DSI_CMCR_GSR1TX | \
                    DSI_CMCR_GSR2TX | \
                    DSI_CMCR_GLWTX  | \
                    DSI_CMCR_DSW0TX | \
                    DSI_CMCR_DSW1TX | \
                    DSI_CMCR_DSR0TX | \
                    DSI_CMCR_DLWTX  | \
                    DSI_CMCR_MRDPS);
    DSIx->CMCR |= (LPCmd->LPGenShortWriteNoP  | \
                   LPCmd->LPGenShortWriteOneP | \
                   LPCmd->LPGenShortWriteTwoP | \
                   LPCmd->LPGenShortReadNoP   | \
                   LPCmd->LPGenShortReadOneP  | \
                   LPCmd->LPGenShortReadTwoP  | \
                   LPCmd->LPGenLongWrite      | \
                   LPCmd->LPDcsShortWriteNoP  | \
                   LPCmd->LPDcsShortWriteOneP | \
                   LPCmd->LPDcsShortReadNoP   | \
                   LPCmd->LPDcsLongWrite      | \
                   LPCmd->LPMaxReadPacket);

    /* 配置每次数据包传输后的确认请求 */
    DSIx->CMCR &= ~DSI_CMCR_ARE;
    DSIx->CMCR |= LPCmd->AcknowledgeRequest;
}

/**
  * 简介:  配置流量控制参数
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  FlowControl: 要启用的流量控制功能。
  *                      此参数可以是 @ref DSI_FlowControl 的任意组合。
  * 
  * 返回值: 无
  */
void DSI_ConfigFlowControl(DSI_TypeDef *DSIx, uint32_t FlowControl) {
    /* 检查参数 */
    assert_param(IS_DSI_FLOW_CONTROL(FlowControl));

    /* 设置 DSI Host Protocol Configuration 寄存器 */
    DSIx->PCR &= ~DSI_FLOW_CONTROL_ALL;
    DSIx->PCR |= FlowControl;
}

/**
  * 简介:  配置 DSI PHY 计时器参数
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  PhyTimers: 包含 DSI PHY 计时参数的 DSI_PHY_TimerTypeDef 结构
  * 
  * 返回值: 无
  */
void DSI_ConfigPhyTimer(DSI_TypeDef *DSIx, DSI_PHY_TimerTypeDef *PhyTimers) {
    uint32_t maxTime = 0;

    maxTime = (PhyTimers->ClockLaneLP2HSTime > PhyTimers->ClockLaneHS2LPTime) ? PhyTimers->ClockLaneLP2HSTime : PhyTimers->ClockLaneHS2LPTime;

    /* 时钟通道计时器配置*/
    /* 在自动时钟通道控制模式下，DSI 主机可以关闭两个高速传输之间的时钟通道。
       为此，DSI 主机计算时钟通道从高速变为低功率和从低功率变为高速所需的时间。
       此定时由 DSI 主机时钟通道定时器配置寄存器(DSI_CLTCR)中的 HS2LP_TIME 和 LP2HS_TIME 配置。
       但是 DSI 主机不是在计算 LP2HS_TIME+HS2LP_TIME，而是在计算2 x HS2LP_ TIME。

       解决方法：配置HS2LP_TIME 和 LP2HS_TIME，使其具有相同的值，即 HS2LP_ TIME 或LP2HS_ TIME的最大值。
    */
    DSIx->CLTCR &= ~(DSI_CLTCR_LP2HS_TIME | DSI_CLTCR_HS2LP_TIME);
    DSIx->CLTCR |= (maxTime | ((maxTime) << 16));

    /* 数据通道计时器配置*/
    DSIx->DLTCR &= ~(DSI_DLTCR_MRD_TIME | DSI_DLTCR_LP2HS_TIME | DSI_DLTCR_HS2LP_TIME);
    DSIx->DLTCR |= (PhyTimers->DataLaneMaxReadTime | ((PhyTimers->DataLaneLP2HSTime) << 16) | ((PhyTimers->DataLaneHS2LPTime) << 24));

    /* 配置停止状态后请求HS传输的等待时间 */
    DSIx->PCONFR &= ~DSI_PCONFR_SW_TIME;
    DSIx->PCONFR |= ((PhyTimers->StopWaitTime) << 8);
}

/**
  * 简介:  配置 DSI HOST超时参数
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  HostTimeouts: 包含 DSI 主机超时参数的 DSI_HOST_TimeoutTypeDef 结构
  * 
  * 返回值: 无
  */
void DSI_ConfigHostTimeouts(DSI_TypeDef *DSIx, DSI_HOST_TimeoutTypeDef *HostTimeouts) {
    /* 设置超时时钟分频因子 */
    DSIx->CCR &= ~DSI_CCR_TOCKDIV;
    DSIx->CCR = ((HostTimeouts->TimeoutCkdiv) << 8);

    /* High-speed 传输超时 */
    DSIx->TCCR[0] &= ~DSI_TCCR0_HSTX_TOCNT;
    DSIx->TCCR[0] |= ((HostTimeouts->HighSpeedTransmissionTimeout) << 16);

    /* Low-power 接收超时 */
    DSIx->TCCR[0] &= ~DSI_TCCR0_LPRX_TOCNT;
    DSIx->TCCR[0] |= HostTimeouts->LowPowerReceptionTimeout;

    /* High-speed 读超时 */
    DSIx->TCCR[1] &= ~DSI_TCCR1_HSRD_TOCNT;
    DSIx->TCCR[1] |= HostTimeouts->HighSpeedReadTimeout;

    /* Low-power 读超时 */
    DSIx->TCCR[2] &= ~DSI_TCCR2_LPRD_TOCNT;
    DSIx->TCCR[2] |= HostTimeouts->LowPowerReadTimeout;

    /* High-speed 写入超时 */
    DSIx->TCCR[3] &= ~DSI_TCCR3_HSWR_TOCNT;
    DSIx->TCCR[3] |= HostTimeouts->HighSpeedWriteTimeout;

    /* High-speed 写预处理模式 */
    DSIx->TCCR[3] &= ~DSI_TCCR3_PM;
    DSIx->TCCR[3] |= HostTimeouts->HighSpeedWritePrespMode;

    /* Low-speed 写入超时 */
    DSIx->TCCR[4] &= ~DSI_TCCR4_LPWR_TOCNT;
    DSIx->TCCR[4] |= HostTimeouts->LowPowerWriteTimeout;

    /* BTA 超时 */
    DSIx->TCCR[5] &= ~DSI_TCCR5_BTA_TOCNT;
    DSIx->TCCR[5] |= HostTimeouts->BTATimeout;
}

/**
  * 简介:  启动 DSI 模块
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  *               DSI 的配置信息。
  * 
  * 返回值: 无
  */
void DSI_Start(DSI_TypeDef *DSIx) {
    /* 启用 DSI 主机 */
    DSIx->CR |= DSI_CR_EN;
    /* 启用 DSI 包装 */
    DSIx->WCR |= DSI_WCR_DSIEN;
}

/**
  * 简介:  停止 DSI 模块
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 返回值: 无
  */
void DSI_Stop(DSI_TypeDef *DSIx) {
    /* 禁用 DSI 主机 */
    DSIx->CR &= ~DSI_CR_EN;

    /* 禁用 DSI 包装 */
    DSIx->WCR &= ~DSI_WCR_DSIEN;
}

/**
  * 简介:  在命令模式下刷新显示
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  *               DSI 的配置信息。
  * 
  * 返回值: 无
  */
void DSI_Refresh(DSI_TypeDef *DSIx) {
    /* Update the display */
    DSIx->WCR |= DSI_WCR_LTDCEN;
}

/**
  * 简介:  控制视频模式中的显示颜色模式
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  ColorMode: 颜色模式(全色或8色)。
  *                    此参数可以是 @ref DSI_Color_Mode 的任何值
  * 
  * 返回值: 无
  */
void DSI_ColorMode(DSI_TypeDef *DSIx, uint32_t ColorMode) {
    /* 检查参数 */
    assert_param(IS_DSI_COLOR_MODE(ColorMode));

    /* 更新显示颜色模式 */
    DSIx->WCR &= ~DSI_WCR_COLM;
    DSIx->WCR |= ColorMode;
}

/**
  * 简介:  控制视频模式下的显示器关闭
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  Shutdown: 关闭(显示器打开或显示器关闭)。
  *                   此参数可以是 @ref DSI_ShutDown 的任何值
  * 
  * 返回值: 无
  */
void DSI_Shutdown(DSI_TypeDef *DSIx, uint32_t Shutdown) {
    /* 检查参数 */
    assert_param(IS_DSI_SHUT_DOWN(Shutdown));

    /* 更新显示Shutdown */
    DSIx->WCR &= ~DSI_WCR_SHTDN;
    DSIx->WCR |= Shutdown;
}


/** @defgroup 数据传输管理功能
 *  简介    DSI 数据传输管理功能
 *
@verbatim
 ===============================================================================
                #####  数据传输管理功能  #####
 ===============================================================================
@endverbatim
  */

/**
  * 简介:  DCS或通用短写命令
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  ChannelID: 虚拟通道ID.
  * 
  * 参数:  Mode: DSI短分组数据类型。
  *               此参数可以是 @ref DSI_SHORT_WRITE_PKT_Data_Type.
  * 
  * 参数:  Param1: DSC命令或第一个通用参数。
  *                 此参数可以是 @ref DSI_DCS_Command 或通用命令代码.
  * 
  * 参数:  Param2: DSC 参数或第二个通用参数。
  * 
  * 返回值: 无
  */
void DSI_ShortWrite(DSI_TypeDef *DSIx,
                    uint32_t ChannelID,
                    uint32_t Mode,
                    uint32_t Param1,
                    uint32_t Param2) {
    /* 检查参数 */
    assert_param(IS_DSI_SHORT_WRITE_PACKET_TYPE(Mode));

    /* 等待命令FIFO 为空 */
    while((DSIx->GPSR & DSI_GPSR_CMDFE) == 0)
    {}

    /* 配置用于发送具有 0 或 1 参数的短 DCS 命令的数据包 */
    DSI_ConfigPacketHeader(DSIx,
                           ChannelID,
                           Mode,
                           Param1,
                           Param2);
}

/**
  * 简介:  DCS或通用长写命令
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  ChannelID: 虚拟通道ID.
  * 
  * 参数:  Mode: DSI长数据包数据类型。
  *               此参数可以是 @ref DSI_LONG_WRITE_PKT_Data_Type.
  * 
  * 参数:  NbParams: 参数的数量。
  * 
  * 参数:  Param1: DSC命令或第一个通用参数。
  *                 此参数可以是 @ref DSI_DCS_Command 或通用命令代码
  * 
  * 参数:  ParametersTable: 指向参数值表的指针。
  * 
  * 返回值: 无
  */
void DSI_LongWrite(DSI_TypeDef *DSIx,
                   uint32_t ChannelID,
                   uint32_t Mode,
                   uint32_t NbParams,
                   uint32_t Param1,
                   uint8_t* ParametersTable) {
    uint32_t uicounter = 0;

    /* 检查参数 */
    assert_param(IS_DSI_LONG_WRITE_PACKET_TYPE(Mode));

    /* 等待命令FIFO 为空 */
    while((DSIx->GPSR & DSI_GPSR_CMDFE) == 0)
    {}

    /* 设置有效载荷字节 1 上的 DCS 代码十六进制，以及写入 FIFO 命令上的其他参数*/
    while(uicounter < NbParams) {
        if(uicounter == 0x00) {
            DSIx->GPDR = (Param1 | \
                          ((uint32_t)(*(ParametersTable + uicounter)) << 8) | \
                          ((uint32_t)(*(ParametersTable + uicounter + 1)) << 16) | \
                          ((uint32_t)(*(ParametersTable + uicounter + 2)) << 24));
            uicounter += 3;
        } else {
            DSIx->GPDR = ((*(ParametersTable + uicounter)) | \
                          ((uint32_t)(*(ParametersTable + uicounter + 1)) << 8) | \
                          ((uint32_t)(*(ParametersTable + uicounter + 2)) << 16) | \
                          ((uint32_t)(*(ParametersTable + uicounter + 3)) << 24));
            uicounter += 4;
        }
    }

    /* 配置发送长DCS命令的数据包 */
    DSI_ConfigPacketHeader(DSIx,
                           ChannelID,
                           Mode,
                           ((NbParams + 1) & 0x00FF),
                           (((NbParams + 1) & 0xFF00) >> 8));
}

/**
  * 简介:  读取命令(DCS或通用)
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  ChannelNbr: 虚拟通道ID
  * 
  * 参数:  Array: 指向存储回读操作有效负载的缓冲区的指针。
  * 
  * 参数:  Size:要读取的数据大小(字节)。
  * 
  * 参数:  Mode:DSI读取数据包数据类型。
  *               此参数可以是 @ref DSI_SHORT_READ_PKT_Data_Type.
  * 
  * 参数:  DCSCmd: DCS get/read command.
  * 
  * 参数:  ParametersTable: 指向参数值表的指针。
  * 
  * 返回值: 无
  */
void DSI_Read(DSI_TypeDef *DSIx,
              uint32_t ChannelNbr,
              uint8_t* Array,
              uint32_t Size,
              uint32_t Mode,
              uint32_t DCSCmd,
              uint8_t* ParametersTable) {

    /* 检查参数 */
    assert_param(IS_DSI_READ_PACKET_TYPE(Mode));

    if(Size > 2) {
        /* 设置最大返回数据包大小 */
        DSI_ShortWrite(DSIx, ChannelNbr, DSI_MAX_RETURN_PKT_SIZE, ((Size) & 0xFF), (((Size) >> 8) & 0xFF));
    }

    /* 配置数据包读取命令 */
    if (Mode == DSI_DCS_SHORT_PKT_READ) {
        DSI_ConfigPacketHeader(DSIx, ChannelNbr, Mode, DCSCmd, 0);
    } else if (Mode == DSI_GEN_SHORT_PKT_READ_P0) {
        DSI_ConfigPacketHeader(DSIx, ChannelNbr, Mode, 0, 0);
    } else if (Mode == DSI_GEN_SHORT_PKT_READ_P1) {
        DSI_ConfigPacketHeader(DSIx, ChannelNbr, Mode, ParametersTable[0], 0);
    } else { /* DSI_GEN_SHORT_PKT_READ_P2 */
        DSI_ConfigPacketHeader(DSIx, ChannelNbr, Mode, ParametersTable[0], ParametersTable[1]);
    }

    /* 检查有效负载读取 FIFO不是空的 */
    while((DSIx->GPSR & DSI_GPSR_PRDFE) == DSI_GPSR_PRDFE)
    {}

    /* 获取第一个字节 */
    *((uint32_t *)Array) = (DSIx->GPDR);

    if (Size > 4) {
        Size -= 4;
        Array += 4;
    }

    /* 获取剩余字节(如果有) */
    while(((int)(Size)) > 0) {
        if((DSIx->GPSR & DSI_GPSR_PRDFE) == 0) {
            *((uint32_t *)Array) = (DSIx->GPDR);
            Size -= 4;
            Array += 4;
        }
    }
}

/**
  * 简介:  通用 DSI 数据包头配置
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 参数:  ChannelID: 虚拟通道头数据包的 ID
  * 
  * 参数:  DataType: 头数据包的数据包数据类型
  *                   此参数可以是以下任意值:
  *                      @ref DSI_SHORT_WRITE_PKT_Data_Type
  *                   or @ref DSI_LONG_WRITE_PKT_Data_Type
  *                   or @ref DSI_SHORT_READ_PKT_Data_Type
  *                   or DSI_MAX_RETURN_PKT_SIZE
  * 
  * 参数:  Data0: 字数LSB
  * 
  * 参数:  Data1: 字数MSB
  * 
  * 返回值: 无
  */
static void DSI_ConfigPacketHeader(DSI_TypeDef *DSIx,
                                   uint32_t ChannelID,
                                   uint32_t DataType,
                                   uint32_t Data0,
                                   uint32_t Data1) {
    /* 用新信息更新 DSI 数据包头 */
    DSIx->GHCR = (DataType | (ChannelID << 6) | (Data0 << 8) | (Data1 << 16));
}


/** @defgroup DSI_Group3 低功耗功能
 *  简介    DSI低功耗管理功能
 *
@verbatim
 ===============================================================================
                   ##### 低功耗函数 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  在 D-PHY PLL运行的情况下进入 ULPM(超低功率模式)(只有数据通道在 ULPM 中)
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 返回值: 无
  */
void DSI_EnterULPMData(DSI_TypeDef *DSIx) {
    /* 数据通道上的 ULPS请求 */
    DSIx->PUCR |= DSI_PUCR_URDL;


    /* 等待，直到 D-PHY活动通道进入 ULPM */
    if((DSIx->PCONFR & DSI_PCONFR_NL) == DSI_ONE_DATA_LANE) {
        while((DSIx->PSR & DSI_PSR_UAN0) != 0)
        {}
    } else { /* DSI_TWO_DATA_LANES */
        while((DSIx->PSR & (DSI_PSR_UAN0 | DSI_PSR_UAN1)) != 0)
        {}
    }
}

/**
  * 简介:  在 D-PHY PLL运行的情况下退出ULPM(超低功率模式)(只有数据通道在 ULPM 中)
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 返回值: 无
  */
void DSI_ExitULPMData(DSI_TypeDef *DSIx) {
    /* Exit ULPS on Data Lanes */
    DSIx->PUCR |= DSI_PUCR_UEDL;

    /* 等到所有活动车道都离开ULPM */
    if((DSIx->PCONFR & DSI_PCONFR_NL) == DSI_ONE_DATA_LANE) {
        while((DSIx->PSR & DSI_PSR_UAN0) != DSI_PSR_UAN0)
        {}
    } else { /* DSI_TWO_DATA_LANES */
        while((DSIx->PSR & (DSI_PSR_UAN0 | DSI_PSR_UAN1)) != (DSI_PSR_UAN0 | DSI_PSR_UAN1))
        {}
    }

    /* 取消断言ULPM请求和 ULPM退出位 */
    DSIx->PUCR = 0;
}

/**
  * 简介:  在 D-PHY PLL关闭的情况下进入 ULPM(超低功率模式)(数据和时钟通道都在 ULPM 中)
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 返回值: 无
  */
void DSI_EnterULPM(DSI_TypeDef *DSIx) {
    /* 时钟通道配置：不再有HS请求 */
    DSIx->CLCR &= ~DSI_CLCR_DPCC;

    /* 在停止 DSIPHY 时钟源之前，使用系统PLL 作为字节通道时钟源 */
    RCC_DSIClockSourceConfig(RCC_DSICLKSource_PLLR);

    /* 时钟和数据通道上的 ULPS请求 */
    DSIx->PUCR |= (DSI_PUCR_URCL | DSI_PUCR_URDL);

    /* 等到所有活动车道都离开ULPM */
    if((DSIx->PCONFR & DSI_PCONFR_NL) == DSI_ONE_DATA_LANE) {
        while((DSIx->PSR & (DSI_PSR_UAN0 | DSI_PSR_UANC)) != 0)
        {}
    } else { /* DSI_TWO_DATA_LANES */
        while((DSIx->PSR & (DSI_PSR_UAN0 | DSI_PSR_UAN1 | DSI_PSR_UANC)) != 0)
        {}
    }

    /* 关闭DSI PLL */
    DSIx->WRPCR &= ~DSI_WRPCR_PLLEN;
}

/**
  * 简介:  在 D-PHY PLL关闭的情况下退出ULPM(超低功率模式)(数据和时钟通道都在 ULPM 中)
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 返回值: 无
  */
void DSI_ExitULPM(DSI_TypeDef *DSIx) {
    /* Turn on the DSI PLL */
    DSIx->WRPCR |= DSI_WRPCR_PLLEN;

    /* 等待PLL锁定 */
    while(DSI_GetFlagStatus(DSIx, DSI_FLAG_PLLLS) == RESET)
    {}

    /* 在时钟和数据通道上退出ULPS */
    DSIx->PUCR |= (DSI_PUCR_UECL | DSI_PUCR_UEDL);

    /* 等到所有活动车道都离开ULPM */
    if((DSIx->PCONFR & DSI_PCONFR_NL) == DSI_ONE_DATA_LANE) {
        while((DSIx->PSR & (DSI_PSR_UAN0 | DSI_PSR_UANC)) != (DSI_PSR_UAN0 | DSI_PSR_UANC))
        {}
    } else { /* DSI_TWO_DATA_LANES */
        while((DSIx->PSR & (DSI_PSR_UAN0 | DSI_PSR_UAN1 | DSI_PSR_UANC)) != (DSI_PSR_UAN0 | DSI_PSR_UAN1 | DSI_PSR_UANC))
        {}
    }

    /* 取消断言ULPM请求和 ULPM退出位 */
    DSIx->PUCR = 0;

    /* 将RCC 中的字节时钟源从系统PLL切换到 D-PHY */
    RCC_DSIClockSourceConfig(RCC_DSICLKSource_PHY);

    /* 将时钟通道配置恢复到 HS */
    DSIx->CLCR |= DSI_CLCR_DPCC;
}

/**
  * 简介:  开始测试模式生成
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  Mode: 图形生成器模式
  *          此参数可以是以下值之一:
  *           0 : 颜色条(水平或垂直)
  *           1 : BER模式(仅垂直)
  * 
  * 参数:  Orientation: 图案生成器方向
  *          此参数可以是以下值之一:
  *           0 : 垂直颜色条
  *           1 : 水平颜色条
  * 
  * 返回值: 无
  */
void DSI_PatternGeneratorStart(DSI_TypeDef *DSIx, uint32_t Mode, uint32_t Orientation) {

    /* 配置图形生成器模式和方向 */
    DSIx->VMCR &= ~(DSI_VMCR_PGM | DSI_VMCR_PGO);
    DSIx->VMCR |= ((Mode << 20) | (Orientation << 24));

    /* 使能通过设置PGE的模式生成器位 */
    DSIx->VMCR |= DSI_VMCR_PGE;

}

/**
  * 简介:  停止测试模式生成
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 返回值: 无
  */
void DSI_PatternGeneratorStop(DSI_TypeDef *DSIx) {
    /* 通过清除PGE禁用模式生成器位 */
    DSIx->VMCR &= ~DSI_VMCR_PGE;
}

/**
  * 简介:  设置回转率和延迟调整
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 参数:  CommDelay: 通信延迟有待调整。
  *                    此参数可以是 @ref DSI_Communication_Delay
  * 
  * 参数:  Lane: 在时钟或数据通道之间进行选择。
  *               此参数可以是 @ref DSI_Lane_Group
  * 
  * 参数:  Value: 转换率或延迟的自定义值
  * 
  * 返回值: 无
  */
void DSI_SetSlewRateAndDelayTuning(DSI_TypeDef *DSIx, uint32_t CommDelay, uint32_t Lane, uint32_t Value) {
    /* 检查函数参数 */
    assert_param(IS_DSI_COMMUNICATION_DELAY(CommDelay));
    assert_param(IS_DSI_LANE_GROUP(Lane));

    switch(CommDelay) {
        case DSI_SLEW_RATE_HSTX:
            if(Lane == DSI_CLOCK_LANE) {
                /* 时钟通道上的高速传输回转速率控制 */
                DSIx->WPCR[1] &= ~DSI_WPCR1_HSTXSRCCL;
                DSIx->WPCR[1] |= Value << 16;
            } else { /* DSI_DATA_LANES */
                /* 数据通道上的高速传输回转速率控制 */
                DSIx->WPCR[1] &= ~DSI_WPCR1_HSTXSRCDL;
                DSIx->WPCR[1] |= Value << 18;
            }

            break;

        case DSI_SLEW_RATE_LPTX:
            if(Lane == DSI_CLOCK_LANE) {
                /* 时钟通道上的低功率传输回转速率补偿 */
                DSIx->WPCR[1] &= ~DSI_WPCR1_LPSRCCL;
                DSIx->WPCR[1] |= Value << 6;
            } else { /*  DSI_DATA_LANES */
                /* 数据通道上的低功率传输回转速率补偿 */
                DSIx->WPCR[1] &= ~DSI_WPCR1_LPSRCDL;
                DSIx->WPCR[1] |= Value << 8;
            }

            break;

        case DSI_HS_DELAY:
            if(Lane == DSI_CLOCK_LANE) {
                /* 时钟通道上的高速传输延迟 */
                DSIx->WPCR[1] &= ~DSI_WPCR1_HSTXDCL;
                DSIx->WPCR[1] |= Value;
            } else { /* DSI_DATA_LANES */
                /* 数据通道上的高速传输延迟 */
                DSIx->WPCR[1] &= ~DSI_WPCR1_HSTXDDL;
                DSIx->WPCR[1] |= Value << 2;
            }

            break;

        default:
            break;
    }
}

/**
  * 简介:  低功率接收滤波器调谐
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 参数:  Frequency: LPRX 输入低通滤波器的截止频率
  * 
  * 返回值: 无
  */
void DSI_SetLowPowerRXFilter(DSI_TypeDef *DSIx, uint32_t Frequency) {
    /* 低功率RX低通滤波调谐 */
    DSIx->WPCR[1] &= ~DSI_WPCR1_LPRXFT;
    DSIx->WPCR[1] |= Frequency << 25;
}

/**
  * 简介:  激活所有车道上的其他当前路径，以满足MIPI D-PHY规范中定义的 SDDTx 参数
  * 
  * 参数:  hdsi: 指向 DSI_HandleTypeDef 结构的指针，该结构包含
  *               DSI 的配置信息。
  * 
  * 参数:  State: ENABLE or DISABLE
  * 
  * 返回值: 无
  */
void DSI_SetSDD(DSI_TypeDef *DSIx, FunctionalState State) {
    /* 检查函数参数 */
    assert_param(IS_FUNCTIONAL_STATE(State));

    /* 激活/禁用所有车道上的附加当前路径 */
    DSIx->WPCR[1] &= ~DSI_WPCR1_SDDC;
    DSIx->WPCR[1] |= ((uint32_t)State << 12);
}

/**
  * 简介:  自定义通道管脚配置
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 参数:  CustomLane: 要应用于选定车道的功能。
  *                     此参数可以是 @ref DSI_CustomLane
  * 
  * 参数:  Lane: 在时钟或数据通道0 或数据通道1 之间进行选择。
  *               此参数可以是 @ref DSI_Lane_Select
  * 
  * 参数:  State: ENABLE or DISABLE
  * 
  * 返回值: 无
  */
void DSI_SetLanePinsConfiguration(DSI_TypeDef *DSIx, uint32_t CustomLane, uint32_t Lane, FunctionalState State) {
    /* 检查函数参数 */
    assert_param(IS_DSI_CUSTOM_LANE(CustomLane));
    assert_param(IS_DSI_LANE(Lane));
    assert_param(IS_FUNCTIONAL_STATE(State));

    switch(CustomLane) {
        case DSI_SWAP_LANE_PINS:
            if(Lane == DSI_CLOCK_LANE) {
                /* 交换时钟通道上的引脚 */
                DSIx->WPCR[0] &= ~DSI_WPCR0_SWCL;
                DSIx->WPCR[0] |= ((uint32_t)State << 6);
            } else if(Lane == DSI_DATA_LANE0) {
                /* 交换数据通道0上的引脚 */
                DSIx->WPCR[0] &= ~DSI_WPCR0_SWDL0;
                DSIx->WPCR[0] |= ((uint32_t)State << 7);
            } else { /* DSI_DATA_LANE1 */
                /* 交换数据通道1上的引脚 */
                DSIx->WPCR[0] &= ~DSI_WPCR0_SWDL1;
                DSIx->WPCR[0] |= ((uint32_t)State << 8);
            }

            break;

        case DSI_INVERT_HS_SIGNAL:
            if(Lane == DSI_CLOCK_LANE) {
                /* 反转时钟通道上的 HS信号 */
                DSIx->WPCR[0] &= ~DSI_WPCR0_HSICL;
                DSIx->WPCR[0] |= ((uint32_t)State << 9);
            } else if(Lane == DSI_DATA_LANE0) {
                /* 反转数据通道0上的 HS信号 */
                DSIx->WPCR[0] &= ~DSI_WPCR0_HSIDL0;
                DSIx->WPCR[0] |= ((uint32_t)State << 10);
            } else { /* DSI_DATA_LANE1 */
                /* 反转数据通道1上的 HS信号 */
                DSIx->WPCR[0] &= ~DSI_WPCR0_HSIDL1;
                DSIx->WPCR[0] |= ((uint32_t)State << 11);
            }

            break;

        default:
            break;
    }
}

/**
  * 简介:  为PHY设置自定义定时
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 参数:  Timing: 要调整的PHY定时。
  *                 此参数可以是 @ref DSI_PHY_Timing
  * 
  * 参数:  State: ENABLE or DISABLE
  * 
  * 参数:  Value: 计时的自定义值
  * 
  * 返回值: 无
  */
void DSI_SetPHYTimings(DSI_TypeDef *DSIx, uint32_t Timing, FunctionalState State, uint32_t Value) {
    /* 检查函数参数 */
    assert_param(IS_DSI_PHY_TIMING(Timing));
    assert_param(IS_FUNCTIONAL_STATE(State));

    switch(Timing) {
        case DSI_TCLK_POST:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_TCLKPOSTEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 27);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[4] &= ~DSI_WPCR4_TCLKPOST;
                DSIx->WPCR[4] |= Value;
            }

            break;

        case DSI_TLPX_CLK:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_TLPXCEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 26);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[3] &= ~DSI_WPCR3_TLPXC;
                DSIx->WPCR[3] |= Value;
            }

            break;

        case DSI_THS_EXIT:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_THSEXITEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 25);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[3] &= ~DSI_WPCR3_THSEXIT;
                DSIx->WPCR[3] |= Value;
            }

            break;

        case DSI_TLPX_DATA:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_TLPXDEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 24);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[3] &= ~DSI_WPCR3_TLPXD;
                DSIx->WPCR[3] |= Value;
            }

            break;

        case DSI_THS_ZERO:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_THSZEROEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 23);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[3] &= ~DSI_WPCR3_THSZERO;
                DSIx->WPCR[3] |= Value;
            }

            break;

        case DSI_THS_TRAIL:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_THSTRAILEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 22);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[2] &= ~DSI_WPCR2_THSTRAIL;
                DSIx->WPCR[2] |= Value;
            }

            break;

        case DSI_THS_PREPARE:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_THSPREPEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 21);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[2] &= ~DSI_WPCR2_THSPREP;
                DSIx->WPCR[2] |= Value;
            }

            break;

        case DSI_TCLK_ZERO:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_TCLKZEROEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 20);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[2] &= ~DSI_WPCR2_TCLKZERO;
                DSIx->WPCR[2] |= Value;
            }

            break;

        case DSI_TCLK_PREPARE:
            /* 启用/禁用自定义计时设置 */
            DSIx->WPCR[0] &= ~DSI_WPCR0_TCLKPREPEN;
            DSIx->WPCR[0] |= ((uint32_t)State << 19);

            if(State) {
                /* 设置自定义值 */
                DSIx->WPCR[2] &= ~DSI_WPCR2_TCLKPREP;
                DSIx->WPCR[2] |= Value;
            }

            break;

        default:
            break;
    }
}

/**
  * 简介:  强制时钟/数据通道处于 TX停止模式
  * 
  * 参数:  DSIx: 指向 DSI 寄存器基址的指针
  * 
  * 参数:  Lane: 在时钟或数据通道之间进行选择。
  *               此参数可以是 @ref DSI_Lane_Group
  * 
  * 参数:  State: ENABLE or DISABLE
  * 
  * 返回值: 无
  */
void DSI_ForceTXStopMode(DSI_TypeDef *DSIx, uint32_t Lane, FunctionalState State) {
    /* 检查函数参数 */
    assert_param(IS_DSI_LANE_GROUP(Lane));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if(Lane == DSI_CLOCK_LANE) {
        /* 在 TX停止模式下强制/展开时钟通道 */
        DSIx->WPCR[0] &= ~DSI_WPCR0_FTXSMCL;
        DSIx->WPCR[0] |= ((uint32_t)State << 12);
    } else { /* DSI_DATA_LANES */
        /* 在 TX停止模式下强制/展开数据通道 */
        DSIx->WPCR[0] &= ~DSI_WPCR0_FTXSMDL;
        DSIx->WPCR[0] |= ((uint32_t)State << 13);
    }
}

/**
  * 简介:  强制LP接收器处于低功率模式
  * 
  * 参数:  hdsi: 指向 DSI_HandleTypeDef 结构的指针，该结构包含 DSI 的配置信息。
  * 
  * 参数:  State: ENABLE or DISABLE
  * 
  * 返回值: 无
  */
void DSI_ForceRXLowPower(DSI_TypeDef *DSIx, FunctionalState State) {
    /* 检查函数参数 */
    assert_param(IS_FUNCTIONAL_STATE(State));

    /* 低功率模式下的强制/不强制LP接收器 */
    DSIx->WPCR[1] &= ~DSI_WPCR1_FLPRXLPM;
    DSIx->WPCR[1] |= ((uint32_t)State << 22);
}

/**
  * 简介:  BTA后强制数据通道处于RX模式
  * 
  * 参数:  hdsi: 指向 DSI_HandleTypeDef 结构的指针，该结构包含 DSI 的配置信息。
  * 
  * 参数:  State: ENABLE or DISABLE
  * 
  * 返回值: 无
  */
void DSI_ForceDataLanesInRX(DSI_TypeDef *DSIx, FunctionalState State) {
    /* 检查函数参数 */
    assert_param(IS_FUNCTIONAL_STATE(State));

    /* RX模式下的强制数据通道 */
    DSIx->WPCR[0] &= ~DSI_WPCR0_TDDL;
    DSIx->WPCR[0] |= ((uint32_t)State << 16);
}

/**
  * 简介:  启用车道上的下拉按钮，以防止未使用时出现浮动状态
  * 
  * 参数:  hdsi: 指向 DSI_HandleTypeDef 结构的指针，该结构包含
  *               DSI 的配置信息。
  * 
  * 参数:  State: ENABLE or DISABLE
  * 
  * 返回值: 无
  */
void DSI_SetPullDown(DSI_TypeDef *DSIx, FunctionalState State) {
    /* 检查函数参数 */
    assert_param(IS_FUNCTIONAL_STATE(State));

    /* 启用/禁用通道下拉 */
    DSIx->WPCR[0] &= ~DSI_WPCR0_PDEN;
    DSIx->WPCR[0] |= ((uint32_t)State << 18);
}

/**
  * 简介:  关闭数据通道上的竞争检测
  * 
  * 参数:  hdsi: 指向 DSI_HandleTypeDef 结构的指针，该结构包含
  *               DSI 的配置信息。
  * 
  * 参数:  State: ENABLE or DISABLE
  * 
  * 返回值: 无
  */
void DSI_SetContentionDetectionOff(DSI_TypeDef *DSIx, FunctionalState State) {
    /* 检查函数参数 */
    assert_param(IS_FUNCTIONAL_STATE(State));

    /* 关闭数据通道时的争用检测 */
    DSIx->WPCR[0] &= ~DSI_WPCR0_CDOFFDL;
    DSIx->WPCR[0] |= ((uint32_t)State << 14);
}


/** @defgroup DSI_Group4 中断和标记管理函数
  *  简介   中断和标记管理函数
  *
@verbatim
 ===============================================================================
            ##### 中断和标记管理函数 #####
 ===============================================================================

 [..] 本节提供了一组函数，允许配置 DSI 中断源并检查或清除标志或挂起位状态。
      用户应确定在其应用程序中将使用哪种模式来管理通信:轮询模式或中断模式。

 *** 轮询模式 ***
 ====================
[..] 在轮询模式下，DSI 通信可以由8个标志管理:
  (#)DSI_FLAG_TE: 撕裂效果中断标志
  (#)DSI_FLAG_ER: 刷新中断结束标志
  (#)DSI_FLAG_BUSY: 忙标志
  (#)DSI_FLAG_PLLLS: PLL锁定状态
  (#)DSI_FLAG_PLLL: PLL锁定中断标志
  (#)DSI_FLAG_PLLU: PLL解锁中断标志
  (#)DSI_FLAG_RRS: 调节器就绪状态。
  (#)DSI_FLAG_RR: 调节器就绪中断标志。


 [..] 在此模式下，建议使用以下函数:
   (+) FlagStatus DSI_GetFlagStatus(DSI_TypeDef* DSIx, uint32_t DSI_FLAG);
   (+) void DSI_ClearFlag(DSI_TypeDef* DSIx, uint32_t DSI_FLAG);

 *** 中断模式 ***
 ======================
 [..] 在中断模式下，SPI 通信可由3个中断源管理和7个挂起位:
  (+)挂起位:
  (##)DSI_IT_TE: 撕裂效果中断标志
  (##)DSI_IT_ER: 刷新中断结束标志
  (##)DSI_IT_PLLL: PLL锁定中断标志
  (##)DSI_IT_PLLU: PLL解锁中断标志
  (##)DSI_IT_RR: 调节器就绪中断标志。
  (+) 中断源:
  (##)DSI_IT_TE: 撕裂效果中断启用
  (##)DSI_IT_ER:刷新中断结束启用
  (##)DSI_IT_PLLL:PLL锁定中断启用
  (##)DSI_IT_PLLU: PLL解锁中断启用
  (##)DSI_IT_RR: 调节器就绪中断启用
  [..]在此模式下，建议使用以下功能:
   (+) void DSI_ITConfig(DSI_TypeDef* DSIx, uint32_t DSI_IT, FunctionalState NewState);
   (+) ITStatus DSI_GetITStatus(DSI_TypeDef* DSIx, uint32_t DSI_IT);
   (+) void DSI_ClearITPendingBit(DSI_TypeDef* DSIx, uint32_t DSI_IT);

@endverbatim
  */

/**
  * 简介: 启用或禁用指定的 DSI 中断。
  * 
  * 参数: DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数: DSI_IT: 指定要启用或禁用的 DSI 中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg DSI_IT_TE: 撕裂效果中断
  *            @arg DSI_IT_ER: 刷新中断结束
  *            @arg DSI_IT_PLLL: PLL锁定中断
  *            @arg DSI_IT_PLLU: PLL解锁中断
  *            @arg DSI_IT_RR: 调节器就绪中断
  * 
  * 参数:  NewState: 指定 DSI 中断的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DSI_ITConfig(DSI_TypeDef* DSIx, uint32_t DSI_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DSI_ALL_PERIPH(DSIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_DSI_IT(DSI_IT));

    if(NewState != DISABLE) {
        /* 启用所选 DSI 中断 */
        DSIx->WIER |= DSI_IT;
    } else {
        /* 禁用所选 DSI 中断 */
        DSIx->WIER &= ~DSI_IT;
    }
}

/**
  * 简介: 检查是否设置了指定的 DSI标志。
  * 
  * 参数: DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数: DSI_FLAG: 指定要检查的 SPI标志。
  *          此参数可以是以下值之一:
  *          @arg DSI_FLAG_TE: 撕裂效果中断标志
  *          @arg DSI_FLAG_ER: 刷新中断结束标志
  *          @arg DSI_FLAG_BUSY: 忙标志
  *          @arg DSI_FLAG_PLLLS: PLL锁定状态
  *          @arg DSI_FLAG_PLLL: PLL锁定中断标志
  *          @arg DSI_FLAG_PLLU: PLL解锁中断标志
  *          @arg DSI_FLAG_RRS: 调节器就绪标志
  *          @arg DSI_FLAG_RR: 调节器就绪中断标志
  * 
  * 返回值: DSI_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus DSI_GetFlagStatus(DSI_TypeDef* DSIx, uint16_t DSI_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_DSI_ALL_PERIPH(DSIx));
    assert_param(IS_DSI_GET_FLAG(DSI_FLAG));

    /* 检查指定 DSI标志的状态 */
    if((DSIx->WISR & DSI_FLAG) != (uint32_t)RESET) {
        /* DSI_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* DSI_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回 DSI_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介: 清除指定的 DSI标志。
  * 
  * 参数: DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数: DSI_FLAG: 指定要清除的 SPI标志。
  *          此参数可以是以下值之一:
  *            @arg DSI_FLAG_TE   : 撕裂效果中断标志
  *            @arg DSI_FLAG_ER   : 刷新中断结束标志
  *            @arg DSI_FLAG_PLLL: PLL锁定中断标志
  *            @arg DSI_FLAG_PLLU: PLL解锁中断标志
  *            @arg DSI_FLAG_RR: 调节器就绪中断标志
  * 
  * 返回值: 无
  */
void DSI_ClearFlag(DSI_TypeDef* DSIx, uint16_t DSI_FLAG) {
    /* 检查参数 */
    assert_param(IS_DSI_ALL_PERIPH(DSIx));
    assert_param(IS_DSI_CLEAR_FLAG(DSI_FLAG));

    /* 清除选定 DSI标志 */
    DSIx->WIFCR = (uint32_t)DSI_FLAG;
}

/**
  * 简介: 检查指定的 DSIx 中断是否已发生。
  * 
  * 参数: DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数: DSI_IT: 指定要检查的 DSI 中断源。
  *          此参数可以是以下值之一:
  *          @arg DSI_IT_TE    : 撕裂效果中断
  *          @arg DSI_IT_ER    : 刷新中断结束
  *          @arg DSI_IT_PLLL  : PLL锁定中断
  *          @arg DSI_IT_PLLU  : PLL解锁中断
  *          @arg DSI_IT_RR: 调节器就绪中断
  * 
  * 返回值: 新状态-> SPI_I2S_IT (SET or RESET).
  */
ITStatus DSI_GetITStatus(DSI_TypeDef* DSIx, uint32_t DSI_IT) {
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_DSI_ALL_PERIPH(DSIx));
    assert_param(IS_DSI_IT(DSI_IT));

    /* 获取 DSI_IT enable bit 状态 */
    enablestatus = (DSIx->WIER & DSI_IT);

    /* 检查指定 SPI 中断的状态 */
    if (((DSIx->WISR & DSI_IT) != (uint32_t)RESET) && enablestatus) {
        /* DSI_IT 被设置 */
        bitstatus = SET;
    } else {
        /* DSI_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回 DSI_IT 状态 */
    return bitstatus;
}

/**
  * 简介: 清除DSIx 中断挂起位。
  * 
  * 参数: DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数: DSI_IT: 指定要清除的 DSI 中断源。
  *        此参数可以是以下值之一:
  *            @arg DSI_IT_TE:撕裂效果中断
  *            @arg DSI_IT_ER:刷新中断结束
  *            @arg DSI_IT_PLLL:PLL锁定中断
  *            @arg DSI_IT_PLLU:PLL解锁中断
  *            @arg DSI_IT_RR:调节器就绪中断
  * 
  * 返回值: 无
  */
void DSI_ClearITPendingBit(DSI_TypeDef* DSIx, uint32_t DSI_IT) {
    /* 检查参数 */
    assert_param(IS_DSI_ALL_PERIPH(DSIx));
    assert_param(IS_DSI_IT(DSI_IT));

    /* 清除被选择的 DSI interrupt pending 位 */
    DSIx->WIFCR = (uint32_t)DSI_IT;
}

/**
  * 简介:  启用错误监视器标志
  * 
  * 参数:  DSIx: 要选择 DSIx 外设，其中 x 可以是不同的 DSI 实例
  * 
  * 参数:  ActiveErrors: 指示将启用哪些错误中断。
  *                      此参数可以是 @ref DSI_Error_Data_Type 的任意组合。
  * 
  * 返回值: 无
  */
void DSI_ConfigErrorMonitor(DSI_TypeDef *DSIx, uint32_t ActiveErrors) {
    DSIx->IER[0] = 0;
    DSIx->IER[1] = 0;

    if((ActiveErrors & DSI_ERROR_ACK) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[0] |= DSI_ERROR_ACK_MASK;
    }

    if((ActiveErrors & DSI_ERROR_PHY) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[0] |= DSI_ERROR_PHY_MASK;
    }

    if((ActiveErrors & DSI_ERROR_TX) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[1] |= DSI_ERROR_TX_MASK;
    }

    if((ActiveErrors & DSI_ERROR_RX) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[1] |= DSI_ERROR_RX_MASK;
    }

    if((ActiveErrors & DSI_ERROR_ECC) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[1] |= DSI_ERROR_ECC_MASK;
    }

    if((ActiveErrors & DSI_ERROR_CRC) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[1] |= DSI_ERROR_CRC_MASK;
    }

    if((ActiveErrors & DSI_ERROR_PSE) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[1] |= DSI_ERROR_PSE_MASK;
    }

    if((ActiveErrors & DSI_ERROR_EOT) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[1] |= DSI_ERROR_EOT_MASK;
    }

    if((ActiveErrors & DSI_ERROR_OVF) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[1] |= DSI_ERROR_OVF_MASK;
    }

    if((ActiveErrors & DSI_ERROR_GEN) != RESET) {
        /* 启用选定错误的中断生成 */
        DSIx->IER[1] |= DSI_ERROR_GEN_MASK;
    }
}


#endif /* STM32F469_479xx */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
