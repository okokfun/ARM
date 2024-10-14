/**
  ******************************************************************************
  * 文件:    stm32f4xx_dfsdm.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能来管理用于 Sigma Delta 调制器
			 (DFSDM) 外设的数字滤波器的以下功能:
  *           + 初始化函数。
  *           + 配置函数。
  *           + 中断和标志管理函数。
  *
  *  @verbatim
  *
================================================================================
                   ##### 如何使用此驱动程序 #####
================================================================================
 [..]

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
#include "stm32f4xx_dfsdm.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup DFSDM
  * 简介: DFSDM 驱动模块
  */
#if defined(STM32F412xG) || defined(STM32F413_423xx)

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* 私有宏s -----------------------------------------------------------*/

#define CHCFGR_INIT_CLEAR_MASK               (uint32_t) 0xFFFE0F10
/* 私有宏s ------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup DFSDM_Private_Functions
  */

/** @defgroup DFSDM_Group1 初始化功能
 *  简介   初始化功能
 *
@verbatim
 ===============================================================================
                             初始化功能
 ===============================================================================
  本节提供的功能允许:
   - 取消初始化DFSDM
   - 初始化DFSDM串行通道收发器
   - 初始化DFSDM筛选器

@endverbatim
  */

/**
  * 简介:  将DFSDM 外围寄存器取消初始化为其默认重置值。
  * 
  * 参数:  无.
  * 
  * 返回值: 无.
  *
  */
void DFSDM_DeInit(void) {
    /* 使能LPTx 复位状态 */
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_DFSDM1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_DFSDM1, DISABLE);
    #if defined(STM32F413_423xx)
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_DFSDM2, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_DFSDM2, DISABLE);
    #endif /* STM32F413_423xx */
}

/**
  * 简介:  根据 DFSDM_TranceiverInit 中的指定参数初始化DFSDM串行通道收发器。
  * 
  * 参数:  DFSDM_Channelx: 指定要选择的通道。
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_Channel0 : DFSDM 1 Channel 0
  *            @arg DFSDM1_Channel1 : DFSDM 1 Channel 1
  *            @arg DFSDM1_Channel2 : DFSDM 1 Channel 2
  *            @arg DFSDM1_Channel3 : DFSDM 1 Channel 3
  *            @arg DFSDM2_Channel0 : DFSDM 2 Channel 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel1 : DFSDM 2 Channel 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel2 : DFSDM 2 Channel 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel3 : DFSDM 2 Channel 3 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel4 : DFSDM 2 Channel 4 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel5 : DFSDM 2 Channel 5 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel6 : DFSDM 2 Channel 6 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel7 : DFSDM 2 Channel 7 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_TransceiverInitStruct: 指向包含指定通道配置信息的 DFSDM_TranceiverInitTypeDef
  *                                     结构的指针。
  * 
  * 返回值: 无
  * 
  * 注意:   必须禁用所选频道才能使用此函数。
  */
void DFSDM_TransceiverInit(DFSDM_Channel_TypeDef* DFSDM_Channelx, DFSDM_TransceiverInitTypeDef* DFSDM_TransceiverInitStruct) {
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_CHANNEL(DFSDM_Channelx));
    assert_param(IS_DFSDM_INTERFACE(DFSDM_TransceiverInitStruct->DFSDM_Interface));
    assert_param(IS_DFSDM_Input_MODE(DFSDM_TransceiverInitStruct->DFSDM_Input));
    assert_param(IS_DFSDM_Redirection_STATE(DFSDM_TransceiverInitStruct->DFSDM_Redirection));
    assert_param(IS_DFSDM_PACK_MODE(DFSDM_TransceiverInitStruct->DFSDM_PackingMode));
    assert_param(IS_DFSDM_CLOCK(DFSDM_TransceiverInitStruct->DFSDM_Clock));
    assert_param(IS_DFSDM_DATA_RIGHT_BIT_SHIFT(DFSDM_TransceiverInitStruct->DFSDM_DataRightShift));
    assert_param(IS_DFSDM_OFFSET(DFSDM_TransceiverInitStruct->DFSDM_Offset));
    assert_param(IS_DFSDM_CLK_DETECTOR_STATE(DFSDM_TransceiverInitStruct->DFSDM_CLKAbsenceDetector));
    assert_param(IS_DFSDM_SC_DETECTOR_STATE(DFSDM_TransceiverInitStruct->DFSDM_ShortCircuitDetector));

    /* 获取DFSDM Channelx CHCFGR1 值 */
    tmpreg1 = DFSDM_Channelx->CHCFGR1;

    /* 清除 SITP, CKABEN, SCDEN and SPICKSEL 位 */
    tmpreg1 &= CHCFGR_INIT_CLEAR_MASK;

    /* 根据 DFSDM_Interface 值设置或重置 SITP 位 */
    /* 设置或重置 SPICKSEL bits 根据 DFSDM_Clock 值 */
    /* 设置或重置 DATMPX bits 根据 DFSDM_InputMode 值 */
    /* 设置或重置 CHINSEL bits 根据 DFSDM_Redirection 值 */
    /* 设置或重置 DATPACK bits 根据 DFSDM_PackingMode 值 */
    /* 设置或重置 CKABEN bit 根据 DFSDM_CLKAbsenceDetector 值 */
    /* 设置或重置 SCDEN bit 根据 DFSDM_ShortCircuitDetector 值 */
    tmpreg1 |= (DFSDM_TransceiverInitStruct->DFSDM_Interface |
                DFSDM_TransceiverInitStruct->DFSDM_Clock |
                DFSDM_TransceiverInitStruct->DFSDM_Input |
                DFSDM_TransceiverInitStruct->DFSDM_Redirection |
                DFSDM_TransceiverInitStruct->DFSDM_PackingMode |
                DFSDM_TransceiverInitStruct->DFSDM_CLKAbsenceDetector |
                DFSDM_TransceiverInitStruct->DFSDM_ShortCircuitDetector);

    /* 写入DFSDM Channelx CHCFGR1R */
    DFSDM_Channelx->CHCFGR1 = tmpreg1;

    /* 获取DFSDM Channelx CHCFGR2 值 */
    tmpreg2 = DFSDM_Channelx->CHCFGR2;

    /* 清除 DTRBS and OFFSET 位 */
    tmpreg2 &= ~(DFSDM_CHCFGR2_DTRBS | DFSDM_CHCFGR2_OFFSET);

    /* 设置或重置 DTRBS bits 根据 DFSDM_DataRightShift 值 */
    /* 设置或重置 OFFSET bits 根据 DFSDM_Offset 值 */
    tmpreg2 |= (((DFSDM_TransceiverInitStruct->DFSDM_DataRightShift) << 3 ) |
                ((DFSDM_TransceiverInitStruct->DFSDM_Offset) << 8 ));

    /* 写入DFSDM Channelx CHCFGR1R */
    DFSDM_Channelx->CHCFGR2 = tmpreg2;
}

/**
  * 简介:  使用默认值填充每个 DFSDM_TranceiverInitStruct 成员。
  * 
  * 参数:  DFSDM_TransceiverInitStruct : 指向包含指定通道配置信息的 DFSDM_TranceiverInitTypeDef
  *                                      结构的指针。
  * 
  * 返回值: 无
  */
void DFSDM_TransceiverStructInit(DFSDM_TransceiverInitTypeDef* DFSDM_TransceiverInitStruct) {
    /* 默认串行接口选择具有上升沿到频闪数据的 SPI */
    DFSDM_TransceiverInitStruct->DFSDM_Interface = DFSDM_Interface_SPI_FallingEdge;

    /* 来自内部DFSDM_CKOUT输出的时钟被选为默认串行时钟 */
    DFSDM_TransceiverInitStruct->DFSDM_Clock = DFSDM_Clock_Internal;

    /* 未选择数据右位偏移作为默认数据右位移位 */
    DFSDM_TransceiverInitStruct->DFSDM_DataRightShift = 0x0;

    /* 没有选择偏移作为默认偏移 */
    DFSDM_TransceiverInitStruct->DFSDM_Offset = 0x0;

    /* 时钟缺失检测器启用为默认状态 */
    DFSDM_TransceiverInitStruct->DFSDM_CLKAbsenceDetector = DFSDM_CLKAbsenceDetector_Enable;
}

/**
  * 简介:  根据 DFSDM_FilterInitStruct 中的指定参数初始化DFSDMx筛选器。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_FilterInitStruct: 指向 DFSDM_FilterInitTypeDef 结构的指针，
  *                                该结构包含指定筛选器的配置信息。
  * 
  * 返回值: 无
  *
  * 注意:   必须禁用所选过滤器才能使用此功能。
  */
void DFSDM_FilterInit(DFSDM_Filter_TypeDef* DFSDMx, DFSDM_FilterInitTypeDef* DFSDM_FilterInitStruct) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_SINC_ORDER(DFSDM_FilterInitStruct->DFSDM_SincOrder));
    assert_param(IS_DFSDM_SINC_OVRSMPL_RATIO(DFSDM_FilterInitStruct->DFSDM_FilterOversamplingRatio));
    assert_param(IS_DFSDM_INTG_OVRSMPL_RATIO(DFSDM_FilterInitStruct->DFSDM_IntegratorOversamplingRatio));

    /* 获取DFSDMx FCR 值 */
    tmpreg1 = DFSDMx->FLTFCR;

    /* 清除 FORD, FOSR and IOSR 位 */
    tmpreg1 &= ~(DFSDM_FLTFCR_FORD | DFSDM_FLTFCR_FOSR | DFSDM_FLTFCR_IOSR);

    /* 设置或重置 FORD bits 根据 DFSDM_SincOrder 值 */
    /* 设置或重置 FOSR bits 根据 DFSDM_FilterOversamplingRatio 值 */
    /* 设置或重置 IOSR bits 根据 DFSDM_IntegratorOversamplingRatio 值 */
    tmpreg1 |= (DFSDM_FilterInitStruct->DFSDM_SincOrder |
                ((DFSDM_FilterInitStruct->DFSDM_FilterOversamplingRatio - 1) << 16) |
                (DFSDM_FilterInitStruct->DFSDM_IntegratorOversamplingRatio - 1));

    /* 写入DFSDMx FCR */
    DFSDMx->FLTFCR = tmpreg1;
}

/**
  * 简介:  用默认值填充每个 DFSDM_FilterInitStruct 成员。
  * 
  * 参数:  DFSDM_FilterInitStruct: 指向将被初始化的 DFSDM_FilterInitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void DFSDM_FilterStructInit(DFSDM_FilterInitTypeDef* DFSDM_FilterInitStruct) {
    /* Order = 3 被选为默认的 sinc Order */
    DFSDM_FilterInitStruct->DFSDM_SincOrder = DFSDM_SincOrder_Sinc3;

    /* 默认过采样比选择Ratio = 64 */
    DFSDM_FilterInitStruct->DFSDM_FilterOversamplingRatio  = 64 ;

    /* 默认积分器过采样比选择Ratio = 4 */
    DFSDM_FilterInitStruct->DFSDM_IntegratorOversamplingRatio = 4;
}


/** @defgroup DFSDM_Group2 配置功能
 *  简介   配置功能
 *
@verbatim
 ===============================================================================
                       配置功能
 ===============================================================================
    本节提供的功能允许 configure DFSDM:
    - 启用/禁用(DFSDM 外围，通道，过滤器)
    - 配置时钟输出
    - 配置用于转换的注入/常规通道
    - 配置短路检测器
    - 配置模拟看门狗滤波器

@endverbatim
  */

#if defined(STM32F412xG)
/**
  * 简介:  启用或停用 DFSDM 外设。
  * 
  * 参数:  NewState: DFSDM 接口的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_Command(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 ENABLE 位 */
        DFSDM1_Channel0 -> CHCFGR1 |= DFSDM_CHCFGR1_DFSDMEN;
    } else {
        /* 重设 ENABLE 位 */
        DFSDM1_Channel0 -> CHCFGR1 &= ~(DFSDM_CHCFGR1_DFSDMEN);
    }
}
#endif /* STM32F412xG */

#if defined(STM32F413_423xx)
/**
  * 简介:  启用或禁用 DFSDM 外设.
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 参数:  NewState: DFSDM 接口的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_Cmd(uint32_t Instance, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(Instance == 1) {
        if (NewState != DISABLE) {
            /* 设置 ENABLE 位 */
            DFSDM1_Channel0 -> CHCFGR1 |= DFSDM_CHCFGR1_DFSDMEN;
        } else {
            /* 重设 ENABLE 位 */
            DFSDM1_Channel0 -> CHCFGR1 &= ~(DFSDM_CHCFGR1_DFSDMEN);
        }
    } else { /* DFSDM2 */
        if (NewState != DISABLE) {
            /* 设置 ENABLE 位 */
            DFSDM2_Channel0 -> CHCFGR1 |= DFSDM_CHCFGR1_DFSDMEN;
        } else {
            /* 重设 ENABLE 位 */
            DFSDM2_Channel0 -> CHCFGR1 &= ~(DFSDM_CHCFGR1_DFSDMEN);
        }
    }
}
#endif /* STM32F413_423xx */
/**
  * 简介:  启用或禁用指定的 DFSDM串行通道x。
  * 
  * 参数:  DFSDM_Channelx: 指定要选择的通道。
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_Channel0 : DFSDM 1 Channel 0
  *            @arg DFSDM1_Channel1 : DFSDM 1 Channel 1
  *            @arg DFSDM1_Channel2 : DFSDM 1 Channel 2
  *            @arg DFSDM1_Channel3 : DFSDM 1 Channel 3
  *            @arg DFSDM2_Channel0 : DFSDM 2 Channel 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel1 : DFSDM 2 Channel 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel2 : DFSDM 2 Channel 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel3 : DFSDM 2 Channel 3 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel4 : DFSDM 2 Channel 4 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel5 : DFSDM 2 Channel 5 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel6 : DFSDM 2 Channel 6 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel7 : DFSDM 2 Channel 7 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  NewState: DFSDM串行通道x的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_ChannelCmd(DFSDM_Channel_TypeDef* DFSDM_Channelx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_CHANNEL(DFSDM_Channelx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 ENABLE 位 */
        DFSDM_Channelx->CHCFGR1 |= DFSDM_CHCFGR1_CHEN;
    } else {
        /* 重设 ENABLE 位 */
        DFSDM_Channelx->CHCFGR1 &= ~(DFSDM_CHCFGR1_CHEN);
    }
}

/**
  * 简介:  启用或禁用指定的 DFSDMx 过滤器。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  NewState: 所选DFSDM模块的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_FilterCmd(DFSDM_Filter_TypeDef* DFSDMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 ENABLE 位 */
        DFSDMx->FLTCR1 |= DFSDM_FLTCR1_DFEN;
    } else {
        /* 重设 ENABLE 位 */
        DFSDMx->FLTCR1 &= ~(DFSDM_FLTCR1_DFEN);
    }
}

#if defined(STM32F412xG)
/**
  * 简介:  配置输出串行时钟分频器。
  * 
  * 参数:  DFSDM_ClkOutDivision: 定义输出串行时钟的分频器
  *         此参数的值可以介于1和256之间。
  * 
  * 返回值: 无
  * 
  * 注意:   如果分频器=1，输出的串行时钟就会停止。在默认情况下，串行输出时钟是停止的。
  */
void DFSDM_ConfigClkOutputDivider(uint32_t DFSDM_ClkOutDivision) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_CLOCK_OUT_DIVIDER(DFSDM_ClkOutDivision));

    /* 获取DFSDM_Channel0 CHCFGR1 值 */
    tmpreg1 = DFSDM1_Channel0 -> CHCFGR1;

    /* 清除 CKOUTDIV 位 */
    tmpreg1 &= (uint32_t)(~DFSDM_CHCFGR1_CKOUTDIV);

    /* 设置或重置 CKOUTDIV 位 */
    tmpreg1 |= (uint32_t)((DFSDM_ClkOutDivision - 1) << 16);

    /* 写入DFSDM Channel0 CHCFGR1 */
    DFSDM1_Channel0 -> CHCFGR1 = tmpreg1;
}

/**
  * 简介:  配置输出串行时钟源.
  * 
  * 参数:  DFSDM_ClkOutSource: 定义输出串行时钟的分频器
  *         此参数的值可以是:
  *            @arg DFSDM_ClkOutSource_SysClock
  *            @arg DFSDM_ClkOutSource_AudioClock
  * 
  * 返回值: 无
  */
void DFSDM_ConfigClkOutputSource(uint32_t DFSDM_ClkOutSource) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_CLOCK_OUT_SOURCE(DFSDM_ClkOutSource));

    /* 获取DFSDM_Channel0 CHCFGR1 值 */
    tmpreg1 = DFSDM1_Channel0 -> CHCFGR1;

    /* 清除 CKOUTSRC 位 */
    tmpreg1 &= ~(DFSDM_CHCFGR1_CKOUTSRC);

    /* 设置或重置 CKOUTSRC 位 */
    tmpreg1 |= DFSDM_ClkOutSource;

    /* 写入DFSDM Channel0 CHCFGR1 */
    DFSDM1_Channel0 -> CHCFGR1 = tmpreg1;
}
#endif /* STM32F412xG */
#if defined(STM32F413_423xx)
/**
  * 简介:  配置输出串行时钟分频器。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  DFSDM_ClkOutDivision: 定义输出串行时钟的分频器
  *         此参数的值可以介于1和256之间。
  * 
  * 返回值: 无
  * 
  * 注意:   如果分频器=1，输出的串行时钟就会停止。在默认情况下，串行输出时钟是停止的。
  */
void DFSDM_ConfigClkOutputDivider(uint32_t Instance, uint32_t DFSDM_ClkOutDivision) {
    uint32_t tmpreg1 = 0;

    if(Instance == 1) {
        /* 检查参数 */
        assert_param(IS_DFSDM_CLOCK_OUT_DIVIDER(DFSDM_ClkOutDivision));

        /* 获取DFSDM_Channel0 CHCFGR1 值 */
        tmpreg1 = DFSDM1_Channel0 -> CHCFGR1;

        /* 清除 CKOUTDIV 位 */
        tmpreg1 &= (uint32_t)(~DFSDM_CHCFGR1_CKOUTDIV);

        /* 设置或重置 CKOUTDIV 位 */
        tmpreg1 |= (uint32_t)((DFSDM_ClkOutDivision - 1) << 16);

        /* 写入DFSDM Channel0 CHCFGR1 */
        DFSDM1_Channel0 -> CHCFGR1 = tmpreg1;
    } else { /* DFSDM2 */
        /* 检查参数 */
        assert_param(IS_DFSDM_CLOCK_OUT_DIVIDER(DFSDM_ClkOutDivision));

        /* 获取DFSDM_Channel0 CHCFGR1 值 */
        tmpreg1 = DFSDM2_Channel0 -> CHCFGR1;

        /* 清除 CKOUTDIV 位 */
        tmpreg1 &= (uint32_t)(~DFSDM_CHCFGR1_CKOUTDIV);

        /* 设置或重置 CKOUTDIV 位 */
        tmpreg1 |= (uint32_t)((DFSDM_ClkOutDivision - 1) << 16);

        /* 写入DFSDM Channel0 CHCFGR1 */
        DFSDM2_Channel0 -> CHCFGR1 = tmpreg1;
    }
}

/**
  * 简介:  配置输出串行时钟源.
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  DFSDM_ClkOutSource: 定义输出串行时钟的分频器
  *         此参数的值可以是:
  *            @arg DFSDM_ClkOutSource_SysClock
  *            @arg DFSDM_ClkOutSource_AudioClock
  * 
  * 返回值: 无
  */
void DFSDM_ConfigClkOutputSource(uint32_t Instance, uint32_t DFSDM_ClkOutSource) {
    uint32_t tmpreg1 = 0;

    if(Instance == 1) {
        /* 检查参数 */
        assert_param(IS_DFSDM_CLOCK_OUT_SOURCE(DFSDM_ClkOutSource));

        /* 获取DFSDM_Channel0 CHCFGR1 值 */
        tmpreg1 = DFSDM1_Channel0 -> CHCFGR1;

        /* 清除 CKOUTSRC 位 */
        tmpreg1 &= ~(DFSDM_CHCFGR1_CKOUTSRC);

        /* 设置或重置 CKOUTSRC 位 */
        tmpreg1 |= DFSDM_ClkOutSource;

        /* 写入DFSDM Channel0 CHCFGR1 */
        DFSDM1_Channel0 -> CHCFGR1 = tmpreg1;
    } else { /* DFSDM2 */
        /* 检查参数 */
        assert_param(IS_DFSDM_CLOCK_OUT_SOURCE(DFSDM_ClkOutSource));

        /* 获取DFSDM_Channel0 CHCFGR1 值 */
        tmpreg1 = DFSDM2_Channel0 -> CHCFGR1;

        /* 清除 CKOUTSRC 位 */
        tmpreg1 &= ~(DFSDM_CHCFGR1_CKOUTSRC);

        /* 设置或重置 CKOUTSRC 位 */
        tmpreg1 |= DFSDM_ClkOutSource;

        /* 写入DFSDM Channel0 CHCFGR1 */
        DFSDM2_Channel0 -> CHCFGR1 = tmpreg1;
    }
}
#endif /* STM32F413_423xx */
/**
  * 简介:  对指定的 DFSDM_Channelx启用或禁用指定的Break_i siganl。
  * 
  * 参数:  DFSDM_Channelx: 指定要选择的通道。
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_Channel0 : DFSDM 1 Channel 0
  *            @arg DFSDM1_Channel1 : DFSDM 1 Channel 1
  *            @arg DFSDM1_Channel2 : DFSDM 1 Channel 2
  *            @arg DFSDM1_Channel3 : DFSDM 1 Channel 3
  *            @arg DFSDM2_Channel0 : DFSDM 2 Channel 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel1 : DFSDM 2 Channel 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel2 : DFSDM 2 Channel 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel3 : DFSDM 2 Channel 3 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel4 : DFSDM 2 Channel 4 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel5 : DFSDM 2 Channel 5 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel6 : DFSDM 2 Channel 6 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel7 : DFSDM 2 Channel 7 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_SCDBreak_i: 其中i可以是0到3之间的值，以选择指定的中断信号。
  * 
  * 参数:  NewState: 所选DFSDM_SCDBreak_i的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_ConfigBRKAnalogWatchDog(DFSDM_Channel_TypeDef* DFSDM_Channelx, uint32_t DFSDM_SCDBreak_i, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_CHANNEL(DFSDM_Channelx));
    assert_param(IS_DFSDM_SCD_BREAK_SIGNAL(DFSDM_SCDBreak_i));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 BKSCD[i] 位 */
        DFSDM_Channelx -> CHAWSCDR |= DFSDM_SCDBreak_i;
    } else {
        /* 重设 BKSCD[i] 位 */
        DFSDM_Channelx -> CHAWSCDR &= ~(DFSDM_SCDBreak_i);
    }
}

/**
  * 简介:  对指定的 DFSDM_Channelx启用或禁用指定的Break_i siganl。
  * 
  * 参数:  DFSDM_Channelx: 指定要选择的通道。
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_Channel0 : DFSDM 1 Channel 0
  *            @arg DFSDM1_Channel1 : DFSDM 1 Channel 1
  *            @arg DFSDM1_Channel2 : DFSDM 1 Channel 2
  *            @arg DFSDM1_Channel3 : DFSDM 1 Channel 3
  *            @arg DFSDM2_Channel0 : DFSDM 2 Channel 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel1 : DFSDM 2 Channel 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel2 : DFSDM 2 Channel 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel3 : DFSDM 2 Channel 3 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel4 : DFSDM 2 Channel 4 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel5 : DFSDM 2 Channel 5 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel6 : DFSDM 2 Channel 6 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel7 : DFSDM 2 Channel 7 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_SCDBreak_i: 其中i可以是0到3之间的值，以选择指定的中断信号。
  * 
  * 参数:  NewState: 所选DFSDM_SCDBreak_i的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_ConfigBRKShortCircuitDetector(DFSDM_Channel_TypeDef* DFSDM_Channelx, uint32_t DFSDM_SCDBreak_i, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_CHANNEL(DFSDM_Channelx));
    assert_param(IS_DFSDM_SCD_BREAK_SIGNAL(DFSDM_SCDBreak_i));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 设置 BKSCD[i] 位 */
        DFSDM_Channelx -> CHAWSCDR |= DFSDM_SCDBreak_i;
    } else {
        /* 重设 BKSCD[i] 位 */
        DFSDM_Channelx -> CHAWSCDR &= ~(DFSDM_SCDBreak_i);
    }
}

/**
  * 简介:  为选定的 DFSDM_Channelx定义短路检测器的阈值计数器。
  * 
  * 参数:  DFSDM_Channelx: 指定要选择的通道。
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_Channel0 : DFSDM 1 Channel 0
  *            @arg DFSDM1_Channel1 : DFSDM 1 Channel 1
  *            @arg DFSDM1_Channel2 : DFSDM 1 Channel 2
  *            @arg DFSDM1_Channel3 : DFSDM 1 Channel 3
  *            @arg DFSDM2_Channel0 : DFSDM 2 Channel 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel1 : DFSDM 2 Channel 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel2 : DFSDM 2 Channel 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel3 : DFSDM 2 Channel 3 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel4 : DFSDM 2 Channel 4 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel5 : DFSDM 2 Channel 5 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel6 : DFSDM 2 Channel 6 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel7 : DFSDM 2 Channel 7 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_SCDThreshold: 阈值计数器，此参数可以是0到255 之间的值。
  * 
  * 返回值: 无
  */
void DFSDM_ConfigShortCircuitThreshold(DFSDM_Channel_TypeDef* DFSDM_Channelx, uint32_t DFSDM_SCDThreshold) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_CHANNEL(DFSDM_Channelx));
    assert_param(IS_DFSDM_CSD_THRESHOLD_VALUE(DFSDM_SCDThreshold));

    /* 获取DFSDM_Channelx AWSCDR 值 */
    tmpreg1 = DFSDM_Channelx -> CHAWSCDR;

    /* 清除 SCDT 位 */
    tmpreg1 &= ~(DFSDM_CHAWSCDR_SCDT);

    /* 设置或重置 SCDT 位 */
    tmpreg1 |= DFSDM_SCDThreshold;

    /* 写入DFSDM Channelx AWSCDR */
    DFSDM_Channelx -> CHAWSCDR = tmpreg1;
}

/**
  * 简介:  选择所选DFSDMx的模拟看门狗要保护的通道，并选择是否启用快速模拟看门犬。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_AWDChannelx: 其中 x 可以是0到7 之间的值，以选择 DFSDM通道。
  * 
  * 参数:  DFSDM_AWDFastMode: 模拟看门狗快速模式。
  *         此参数可以是 @ref DFSDM_AWD_Fast_Mode_Selection的值。
  * 
  * 返回值: 无
  */
void DFSDM_ConfigAnalogWatchdog(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_AWDChannelx, uint32_t DFSDM_AWDFastMode) {
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_AWD_CHANNEL(DFSDM_AWDChannelx));
    assert_param(IS_DFSDM_AWD_MODE(DFSDM_AWDFastMode));

    /* 获取DFSDMx CR2 值 */
    tmpreg1 = DFSDMx -> FLTCR2;

    /* 清除 AWDCH 位 */
    tmpreg1 &= ~(DFSDM_FLTCR2_AWDCH);

    /* 设置或重置 AWDCH 位 */
    tmpreg1 |= DFSDM_AWDChannelx;

    /* 写入DFSDMx CR2 寄存器 */
    DFSDMx -> FLTCR2 |= tmpreg1;

    /* 获取DFSDMx CR1 值 */
    tmpreg2 = DFSDMx->FLTCR1;

    /* 清除 AWFSEL 位 */
    tmpreg2 &= ~(DFSDM_FLTCR1_AWFSEL);

    /* 设置或重置 AWFSEL 位 */
    tmpreg2 |= DFSDM_AWDFastMode;

    /* 写入DFSDMx CR1 寄存器 */
    DFSDMx->FLTCR1 = tmpreg2;
}

/**
  * 简介:  选择要由所选DFSDMx的模拟看门狗保护的通道要使用的模式.
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_ExtremChannelx: 其中 x 可以是0到7 之间的值，以选择要连接到极端探测器的通道。
  * 
  * 返回值: 无
  */
void DFSDM_SelectExtremesDetectorChannel(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_ExtremChannelx) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_EXTREM_CHANNEL(DFSDM_ExtremChannelx));

    /* 获取DFSDMx CR2 值 */
    tmpreg1 = DFSDMx -> FLTCR2;

    /* 清除 EXCH 位 */
    tmpreg1 &= ~(DFSDM_FLTCR2_EXCH);

    /* 设置或重置 AWDCH 位 */
    tmpreg1 |= DFSDM_ExtremChannelx;

    /* 写入DFSDMx CR2 寄存器 */
    DFSDMx -> FLTCR2 = tmpreg1;
}

/**
  * 简介:  通过DFSDMx返回常规转换数据。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 转换后的常规数据。
  * 
  * 注意:   此函数返回带符号的值。
  */
int32_t DFSDM_GetRegularConversionData(DFSDM_Filter_TypeDef* DFSDMx) {
    uint32_t reg = 0;
    int32_t  value = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    /* 获取常规通道的数据寄存器值 */
    reg = DFSDMx -> FLTRDATAR;

    /* Extract conversion 值 */
    value = (((reg & 0xFFFFFF00) >> 8));

    /* 返回conversion result */
    return  value;
}

/**
  * 简介:  通过DFSDMx返回注入的转换数据。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 转换后的常规数据。
  * 
  * 注意:   此函数返回带符号的值。
  */
int32_t DFSDM_GetInjectedConversionData(DFSDM_Filter_TypeDef* DFSDMx) {
    uint32_t reg = 0;
    int32_t  value = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    /* 获取常规通道的数据寄存器值 */
    reg = DFSDMx -> FLTJDATAR;

    /* Extract conversion 值 */
    value = ((reg & 0xFFFFFF00) >> 8);

    /* 返回conversion result */
    return  value;
}

/**
  * 简介:  返回由DFSDMx转换的最大值。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 最高转换值。
  * 
  * 注意:   此函数返回带符号的值。
  */
int32_t DFSDM_GetMaxValue(DFSDM_Filter_TypeDef* DFSDMx) {
    int32_t value = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    value = ((DFSDMx -> FLTEXMAX) >> 8);
    /* 返回highest converted 值 */
    return value;
}

/**
  * 简介:  返回由DFSDMx转换的最小值。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 最低转换值。
  * 
  * 注意:   此函数返回带符号的值。
  */
int32_t DFSDM_GetMinValue(DFSDM_Filter_TypeDef* DFSDMx) {
    int32_t value = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    value = ((DFSDMx -> FLTEXMIN) >> 8);
    /* 返回lowest conversion 值 */
    return value;
}

/**
  * 简介:  返回DFSDMx在其上捕获最高转换数据的通道数。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 最高转换值。
  */
int32_t DFSDM_GetMaxValueChannel(DFSDM_Filter_TypeDef* DFSDMx) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    /* 返回highest converted 值 */
    return  ((DFSDMx -> FLTEXMAX) & (~DFSDM_FLTEXMAX_EXMAXCH));
}

/**
  * 简介:  返回DFSDMx在其上捕获最低转换数据的通道数。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 最低转换值。
  */
int32_t DFSDM_GetMinValueChannel(DFSDM_Filter_TypeDef* DFSDMx) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    /* 返回lowest converted 值 */
    return  ((DFSDMx -> FLTEXMIN) & (~DFSDM_FLTEXMIN_EXMINCH));
}

/**
  * 简介:  返回DFSDMx的转换时间(以28位计时器为单位)。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 转换时间。
  */
uint32_t DFSDM_GetConversionTime(DFSDM_Filter_TypeDef* DFSDMx) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    /* 返回lowest converted 值 */
    return  ((DFSDMx -> FLTCNVTIMR >> 4) & 0x0FFFFFFF);
}

/**
  * 简介:  通过为指定的 DFSDM_Channelx 设置Sinc滤波器顺序和过采样率，为模拟看门狗配置Sinc滤波器。
  * 
  * 参数:  DFSDM_Channelx: 指定要选择的通道。
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_Channel0 : DFSDM 1 Channel 0
  *            @arg DFSDM1_Channel1 : DFSDM 1 Channel 1
  *            @arg DFSDM1_Channel2 : DFSDM 1 Channel 2
  *            @arg DFSDM1_Channel3 : DFSDM 1 Channel 3
  *            @arg DFSDM2_Channel0 : DFSDM 2 Channel 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel1 : DFSDM 2 Channel 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel2 : DFSDM 2 Channel 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel3 : DFSDM 2 Channel 3 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel4 : DFSDM 2 Channel 4 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel5 : DFSDM 2 Channel 5 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel6 : DFSDM 2 Channel 6 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel7 : DFSDM 2 Channel 7 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_AWDSincOrder: Sinc筛选器顺序此参数的值可以是 @ref DFSDM_AWD_Scic_order。
  * 
  * 参数:  DFSDM_AWDSincOverSampleRatio: 滤波器过采样率，此参数的值可以介于1和32之间。
  * 
  * 返回值: 无
  */
void DFSDM_ConfigAWDFilter(DFSDM_Channel_TypeDef* DFSDM_Channelx, uint32_t DFSDM_AWDSincOrder, uint32_t DFSDM_AWDSincOverSampleRatio) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_CHANNEL(DFSDM_Channelx));
    assert_param(IS_DFSDM_AWD_SINC_ORDER(DFSDM_AWDSincOrder));
    assert_param(IS_DFSDM_AWD_OVRSMPL_RATIO(DFSDM_AWDSincOverSampleRatio));

    /* 获取DFSDM_Channelx CHAWSCDR 值 */
    tmpreg1 = DFSDM_Channelx -> CHAWSCDR;

    /* 清除 FORD and FOSR 位 */
    tmpreg1 &= ~(DFSDM_CHAWSCDR_AWFORD | DFSDM_CHAWSCDR_AWFOSR);

    /* 设置或重置 SCDT 位 */
    tmpreg1 |= (DFSDM_AWDSincOrder | ((DFSDM_AWDSincOverSampleRatio - 1) << 16)) ;

    /* 写入DFSDM Channelx CHAWSCDR */
    DFSDM_Channelx -> CHAWSCDR = tmpreg1;
}

/**
  * 简介:  返回channelx的最后一个模拟看门狗过滤器转换结果数据。
  * 
  * 参数:  DFSDM_Channelx: 指定要选择的通道。
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_Channel0 : DFSDM 1 Channel 0
  *            @arg DFSDM1_Channel1 : DFSDM 1 Channel 1
  *            @arg DFSDM1_Channel2 : DFSDM 1 Channel 2
  *            @arg DFSDM1_Channel3 : DFSDM 1 Channel 3
  *            @arg DFSDM2_Channel0 : DFSDM 2 Channel 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel1 : DFSDM 2 Channel 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel2 : DFSDM 2 Channel 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel3 : DFSDM 2 Channel 3 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel4 : DFSDM 2 Channel 4 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel5 : DFSDM 2 Channel 5 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel6 : DFSDM 2 Channel 6 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_Channel7 : DFSDM 2 Channel 7 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 数据转换值。
  */
uint32_t DFSDM_GetAWDConversionValue(DFSDM_Channel_TypeDef* DFSDM_Channelx) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_CHANNEL(DFSDM_Channelx));

    /* 返回last analog watchdog filter conversion 值 */
    return  DFSDM_Channelx -> CHWDATAR;
}


/**
  * 简介:  为所选DFSDMx的模拟看门狗配置高阈值和低阈值。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_HighThreshold: 高阈值。此参数的值可以介于0 和0xFFFFFF之间。
  * 
  * 参数:  DFSDM_LowThreshold: 低阈值。此参数的值可以介于0 和0xFFFFFF之间。
  * 
  * 返回值: 无.
  * 
  * 注意:   在信道收发器监测(模拟看门狗快速模式启用)的情况下，
  *         与模拟看门犬滤波器输出相比，只有较高的16位定义了16位阈值。
  */
void DFSDM_SetAWDThreshold(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_HighThreshold, uint32_t DFSDM_LowThreshold) {
    uint32_t tmpreg1 = 0;
    uint32_t tmpreg2 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_HIGH_THRESHOLD(DFSDM_HighThreshold));
    assert_param(IS_DFSDM_LOW_THRESHOLD(DFSDM_LowThreshold));

    /* 获取DFSDMx AWHTR 值 */
    tmpreg1 = DFSDMx -> FLTAWHTR;

    /* 清除 AWHT 位 */
    tmpreg1 &= ~(DFSDM_FLTAWHTR_AWHT);

    /* 设置或重置 AWHT 位 */
    tmpreg1 |= (DFSDM_HighThreshold  << 8 );

    /* 写入DFSDMx AWHTR 寄存器 */
    DFSDMx -> FLTAWHTR = tmpreg1;

    /* 获取DFSDMx AWLTR 值 */
    tmpreg2 = DFSDMx -> FLTAWLTR;

    /* 清除 AWLTR 位 */
    tmpreg2 &= ~(DFSDM_FLTAWLTR_AWLT);

    /* 设置或重置 AWLTR 位 */
    tmpreg2 |= (DFSDM_LowThreshold  << 8 );

    /* 写入DFSDMx AWLTR 寄存器 */
    DFSDMx -> FLTAWLTR = tmpreg2;
}

/**
  * 简介:  为选定的 DFSDMx选择注入通道。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_InjectedChannelx: 其中 x 可以是0到7 之间的值，以选择要配置为注入通道的通道。
  * 
  * 返回值: 无
  * 
  * 注意:   用户最多可以选择8个频道。
  */
void DFSDM_SelectInjectedChannel(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_InjectedChannelx) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_INJECT_CHANNEL(DFSDM_InjectedChannelx));

    /* 获取DFSDMx JCHGR 值 */
    tmpreg1 = DFSDMx -> FLTJCHGR;

    /* 清除 JCHGR 位 */
    tmpreg1 &= ~(DFSDM_FLTJCHGR_JCHG);

    /* 设置或重置 JCHGR 位 */
    tmpreg1 |= DFSDM_InjectedChannelx;

    /* 写入DFSDMx JCHGR 寄存器 */
    DFSDMx -> FLTJCHGR |= tmpreg1;
}

/**
  * 简介:  为选定的 DFSDMx选择常规频道。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_RegularChannelx: 其中 x 可以是0到7 之间的值，以选择要配置为常规通道的通道。
  * 
  * 返回值: 无
  * 
  * 注意:   用户只能选择一个频道。
  */
void DFSDM_SelectRegularChannel(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_RegularChannelx) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_REGULAR_CHANNEL(DFSDM_RegularChannelx));

    /* 获取DFSDMx CR1 值 */
    tmpreg1 = DFSDMx -> FLTCR1;

    /* 清除 RCH 位 */
    tmpreg1 &= ~(DFSDM_FLTCR1_RCH);

    /* 设置或重置 RCH 位 */
    tmpreg1 |= DFSDM_RegularChannelx;

    /* 写入DFSDMx CR1 寄存器 */
    DFSDMx -> FLTCR1 = tmpreg1;
}

/**
  * 简介:  为选定 DFSDMx的注入通道组启动软件启动。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 无
  */
void DFSDM_StartSoftwareInjectedConversion(DFSDM_Filter_TypeDef* DFSDMx) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    /* Write 1 to DFSDMx CR1 RSWSTAR 位 */
    DFSDMx -> FLTCR1 |=  DFSDM_FLTCR1_JSWSTART;
}

/**
  * 简介:  启动选定 DFSDMx的常规频道的软件启动。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 无
  */
void DFSDM_StartSoftwareRegularConversion(DFSDM_Filter_TypeDef* DFSDMx) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    /* Write 1 to DFSDMx CR1 RSWSTAR 位 */
    DFSDMx -> FLTCR1 |=  DFSDM_FLTCR1_RSWSTART;
}

/**
  * 简介:  选择触发信号以启动所选DFSDMx的注入转换。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_InjectedTrigger: 触发信号。
  *         此参数的值可以是: @ref DFSDM_Injected_Trigger_signal
  * 
  * 参数:  DFSDM_TriggerEdge: 选定触发器的边缘
  *         此参数的值可以是: @ref DFSDM_Trigger_Edge_selection
  * 
  * 返回值: 无.
  * 
  * 注意:   只有在禁用过滤器时才能使用此函数，请使用 DFSDM_FilterCmd()禁用过滤器。
  */
void DFSDM_ConfigInjectedTrigger(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_Trigger, uint32_t DFSDM_TriggerEdge) {
    uint32_t tmpreg1 = 0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));

    if (DFSDMx == DFSDM0) {
        assert_param(IS_DFSDM0_INJ_TRIGGER(DFSDM_Trigger));
    } else {
        assert_param(IS_DFSDM1_INJ_TRIGGER(DFSDM_Trigger));
    }

    assert_param(IS_DFSDM_TRIGGER_EDGE(DFSDM_TriggerEdge));

    /* 获取DFSDMx CR1 值 */
    tmpreg1 = DFSDMx -> FLTCR1;

    /* 清除 JEXTSEL & JEXTEN 位 */
    tmpreg1 &= ~(DFSDM_FLTCR1_JEXTSEL | DFSDM_FLTCR1_JEXTEN);

    /* 设置或重置 JEXTSEL & JEXTEN 位 */
    tmpreg1 |= (DFSDM_Trigger | DFSDM_TriggerEdge);

    /* 写入DFSDMx CR1 寄存器 */
    DFSDMx -> FLTCR1 = tmpreg1;
}

/**
  * 简介:  当在DFSDM0中由软件启动的注入转换时，同步启动注入转换。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 无
  * 
  * 注意:   只有在禁用过滤器时才能使用此函数，请使用 DFSDM_FilterCmd()禁用过滤器。
  */
void DFSDM_SynchronousFilter0InjectedStart(DFSDM_Filter_TypeDef* DFSDMx) {
    /* 检查参数 */
    assert_param(IS_DFSDM_SYNC_FILTER(DFSDMx));

    /* Write 1 to DFSDMx CR1 JSYNC 位 */
    DFSDMx -> FLTCR1 |=  DFSDM_FLTCR1_JSYNC;
}

/**
  * 简介:  当在DFSDM0中由软件启动的常规转换时，同步启动常规转换。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 返回值: 无
  * 
  * 注意:   只有在禁用过滤器时才能使用此函数，请使用 DFSDM_FilterCmd()禁用过滤器。
  */
void DFSDM_SynchronousFilter0RegularStart(DFSDM_Filter_TypeDef* DFSDMx) {
    /* 检查参数 */
    assert_param(IS_DFSDM_SYNC_FILTER(DFSDMx));

    /* Write 1 to DFSDMx CR1 RSYNC 位 */
    DFSDMx -> FLTCR1 |=  DFSDM_FLTCR1_RSYNC;
}

/**
  * 简介:  启用或禁用选定过滤器DFSDMx的常规转换的继续模式。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  NewState: 连续模式的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_RegularContinuousModeCmd(DFSDM_Filter_TypeDef* DFSDMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 RCONT 位 */
        DFSDMx -> FLTCR1 |=  DFSDM_FLTCR1_RCONT;
    } else {
        /* 禁用 RCONT 位 */
        DFSDMx -> FLTCR1 &=  ~(DFSDM_FLTCR1_RCONT);
    }
}

/**
  * 简介:  启用或禁用所选过滤器DFSDMx的快速模式。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  NewState: 快速模式的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  * 
  * 注意:   如果在连续模式下仅选择了一个通道(通过执行常规转换或在仅选择一个
  *         通道的情况下执行注入转换)，则可以通过启用快速模式将采样率提高数倍。
  * 
  * 注意:   只有在禁用过滤器时才能使用此函数，请使用 DFSDM_FilterCmd()禁用过滤器。
  */
void DFSDM_FastModeCmd(DFSDM_Filter_TypeDef* DFSDMx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 FAST 位 */
        DFSDMx -> FLTCR1 |=  DFSDM_FLTCR1_FAST;
    } else {
        /* 禁用 FAST 位 */
        DFSDMx -> FLTCR1 &=  ~(DFSDM_FLTCR1_FAST);
    }
}

/**
  * 简介:  为选定的 DFSDMx选择注入转换模式。
  *        注入转换可以在单模式或扫描模式下运行。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_InjectConvMode: 注入转换模式，此参数可以是:
  *             @arg DFSDM_InjectConvMode_Single
  *             @arg DFSDM_InjectConvMode_Scan
  * 
  * 返回值: 无.
  * 
  * 注意:   只有在禁用过滤器时才能使用此函数，请使用 DFSDM_FilterCmd()禁用过滤器。
  */
void DFSDM_SelectInjectedConversionMode(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_InjectConvMode) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_INJ_CONV_MODE(DFSDM_InjectConvMode));

    /* 清除 JSCAN 位 */
    DFSDMx -> FLTCR1 &= ~(DFSDM_FLTCR1_JSCAN);

    /* 写入DFSDMx CR1 寄存器 */
    DFSDMx -> FLTCR1 |= DFSDM_InjectConvMode;
}

/**
  * 简介:  启用或禁用 DMA以读取所选滤波器DFSDMx的注入信道组的数据。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_DMAConversionMode: 选择要配置为DMA读取的模式。
  *            @arg DFSDM_DMAConversionMode_Regular:  DMA通道已启用/禁用，用于读取数据以进行常规转换
  *            @arg DFSDM_DMAConversionMode_Injected: 启用/禁用 DMA通道以读取注入转换的数据
  * 
  * 参数:  NewState: DMA信道的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无.
  * 
  * 注意:   只有在禁用过滤器时才能使用此函数，请使用 DFSDM_FilterCmd()禁用过滤器。
  */
void DFSDM_DMATransferConfig(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_DMAConversionMode, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_CONVERSION_MODE(DFSDM_DMAConversionMode));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 JDMAEN or RDMAEN 位 */
        DFSDMx -> FLTCR1 |=  (DFSDM_FLTCR1_JDMAEN << DFSDM_DMAConversionMode) ;
    } else {
        /* 禁用 JDMAEN or RDMAEN 位 */
        DFSDMx -> FLTCR1 &=  ~(DFSDM_FLTCR1_JDMAEN << DFSDM_DMAConversionMode);
    }
}

/** @defgroup DFSDM_Group3 中断和标记管理函数
 *  简介    中断和标记管理函数
 *
@verbatim
 ===============================================================================
                  中断和标记管理函数
 ===============================================================================
  本节提供的功能允许配置 DFSDM 中断，获取状态和清除标志位。

  LPT提供7个标志和中断源(只有配备编码器模式接口的 LPT 外设设备上才有2个标志和干扰源)

  标志和中断源:
  =============================
  1. 注入的转换结束。
  2. 常规转换结束。
  3. 注入的数据超限。
  4. 常规数据超限。
  5. 模拟看门狗。
  6. 短路检测器。
  7. 通道时钟缺失

  - 要启用一个特定的中断源，请使用 "DFSDM_ITConfig"、"DFSDM_ITClockAbsenceCmd "
    和 "DFSDM_ITShortCircuitDetectorCmd "函数。
  - 要检查是否发生了中断，可调用 "DFSDM_GetITStatus"、"DFSDM_GetClockAbsenceITStatusfunction "
    和 "DFSDM_GetShortCircuitITStatus "函数并读取返回值。
  - 要获得一个标志状态，请调用 "DFSDM_GetFlagStatus"、"DFSDM_GetClockAbsenceFlagStatus"、
    "DFSDM_GetShortCircuitFlagStatus "和 "DFSDM_GetWatchdogFlagStatus "函数并读取返回值。
  - 要清除一个标志或一个中断，请使用 DFSDM_ClearFlag,DFSDM_ClearClockAbsenceFlag。
    DFSDM_ClearShortCircuitFlag,DFSDM_ClearAnalogWatchdogFlag等函数来清除一个标志或中断。
    相应的标志(中断)。

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 DFSDMx中断。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_IT: 指定要启用或禁用的 DFSDM 中断源。
  *         此参数可以是以下值的任意组合:
    *           @arg DFSDM_IT_JEOC:注入转换结束中断源
    *           @arg DFSDM_IT_REOC:常规转换结束中断源
    *           @arg DFSDM_IT_JOVR:注入的数据溢出中断源
    *           @arg DFSDM_IT_ROVR:常规数据溢出中断源
    *           @arg DFSDM_IT_AWD:模拟看门狗中断源
    * 
  * 参数:  NewState:DFSDM 中断的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_ITConfig(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_IT(DFSDM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用中断源 */
        DFSDMx->FLTCR2 |= DFSDM_IT;
    } else {
        /* 禁用中断源 */
        DFSDMx->FLTCR2 &= ~(DFSDM_IT);
    }
}

#if defined(STM32F412xG)
/**
  * 简介:  启用或禁用时钟缺失中断。
  * 
  * 参数:  NewState: 中断的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_ITClockAbsenceCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用中断源 */
        DFSDM1_0->FLTCR2 |= DFSDM_IT_CKAB;
    } else {
        /* 禁用中断源 */
        DFSDM1_0->FLTCR2 &= ~(DFSDM_IT_CKAB);
    }
}

/**
  * 简介:  启用或禁用短路检测器中断。
  * 
  * 参数:  NewState: 中断的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_ITShortCircuitDetectorCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用中断源 */
        DFSDM1_0->FLTCR2 |= DFSDM_IT_SCD;
    } else {
        /* 禁用中断源 */
        DFSDM1_0->FLTCR2 &= ~(DFSDM_IT_SCD);
    }
}
#endif /* STM32F412xG */

#if defined(STM32F413_423xx)
/**
  * 简介:  启用或禁用时钟缺失中断。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  NewState: 中断的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_ITClockAbsenceCmd(uint32_t Instance, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(Instance == 1) {
        if (NewState != DISABLE) {
            /* 启用中断源 */
            DFSDM1_0->FLTCR2 |= DFSDM_IT_CKAB;
        } else {
            /* 禁用中断源 */
            DFSDM1_0->FLTCR2 &= ~(DFSDM_IT_CKAB);
        }
    } else { /* DFSDM2 */
        if (NewState != DISABLE) {
            /* 启用中断源 */
            DFSDM2_0->FLTCR2 |= DFSDM_IT_CKAB;
        } else {
            /* 禁用中断源 */
            DFSDM2_0->FLTCR2 &= ~(DFSDM_IT_CKAB);
        }
    }
}

/**
  * 简介:  启用或禁用短路检测器中断。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  NewState: 中断的新状态。
  *         此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void DFSDM_ITShortCircuitDetectorCmd(uint32_t Instance, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(Instance == 1) {
        if (NewState != DISABLE) {
            /* 启用中断源 */
            DFSDM1_0->FLTCR2 |= DFSDM_IT_SCD;
        } else {
            /* 禁用中断源 */
            DFSDM1_0->FLTCR2 &= ~(DFSDM_IT_SCD);
        }
    } else { /* DFSDM2 */
        if (NewState != DISABLE) {
            /* 启用中断源 */
            DFSDM2_0->FLTCR2 |= DFSDM_IT_SCD;
        } else {
            /* 禁用中断源 */
            DFSDM2_0->FLTCR2 &= ~(DFSDM_IT_SCD);
        }
    }

}
#endif /* STM32F413_423xx */

/**
  * 简介:  检查是否设置了指定的 DFSDM标志。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  LPT_FLAG: 指定要检查的标志。
  *         此参数可以是以下值的任意组合:
  *            @arg DFSDM_FLAG_JEOC:注入转换结束标志
  *            @arg DFSDM_FLAG_REOC:常规转换结束标志
  *            @arg DFSDM_FLAG_JOVR:注入的数据溢出标志
  *            @arg DFSDM_FLAG_ROVR:常规数据溢出标志
  *            @arg DFSDM_FLAG_AWD:模拟看门狗标志
  *            @arg DFSDM_FLAG_JCIP:注入的转换正在进行状态
  *            @arg DFSDM_FLAG_RCIP:定期转换进行中状态
  * 
  * 返回值: 无
  */
FlagStatus DFSDM_GetFlagStatus(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_FLAG) {
    ITStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_FLAG(DFSDM_FLAG));

    if ((DFSDMx->FLTISR & DFSDM_FLAG) != RESET ) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

#if defined(STM32F412xG)
/**
  * 简介:  检查是否设置了指定的时钟缺失通道标志。
  * 
  * 参数:  DFSDM_FLAG_CLKAbsence: 指定要检查的标志。
  *         此参数可以是 @ref DFSDM_Clock_Absence_Flag_Definition的值
  * 
  * 返回值: 无
  */
FlagStatus DFSDM_GetClockAbsenceFlagStatus(uint32_t DFSDM_FLAG_CLKAbsence) {
    ITStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_DFSDM_CLK_ABS_FLAG(DFSDM_FLAG_CLKAbsence));

    if((DFSDM1_0->FLTISR & DFSDM_FLAG_CLKAbsence) != RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  检查是否设置了指定的短路通道检测器标志。
  * 
  * 参数:  DFSDM_FLAG_SCD: 指定要检查的标志。
  *         此参数可以是 @ref DFSDM_SCD_Flag_Definition的值
  * 
  * 返回值: 无
  */
FlagStatus DFSDM_GetShortCircuitFlagStatus(uint32_t DFSDM_FLAG_SCD) {
    ITStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_DFSDM_SCD_FLAG(DFSDM_FLAG_SCD));

    if ((DFSDM1_0->FLTISR & DFSDM_FLAG_SCD) != RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}
#endif /* STM32F412xG */
#if defined(STM32F413_423xx)
/**
  * 简介:  检查是否设置了指定的时钟缺失通道标志。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  DFSDM_FLAG_CLKAbsence: 指定要检查的标志。
  *         此参数可以是 @ref DFSDM_Clock_Absence_Flag_Definition的值
  * 
  * 返回值: 无
  */
FlagStatus DFSDM_GetClockAbsenceFlagStatus(uint32_t Instance, uint32_t DFSDM_FLAG_CLKAbsence) {
    ITStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_DFSDM_CLK_ABS_FLAG(DFSDM_FLAG_CLKAbsence));

    if(Instance == 1) {
        if((DFSDM1_0->FLTISR & DFSDM_FLAG_CLKAbsence) != RESET) {
            bitstatus = SET;
        } else {
            bitstatus = RESET;
        }
    } else { /* DFSDM2 */
        /* 检查参数 */
        assert_param(IS_DFSDM_CLK_ABS_FLAG(DFSDM_FLAG_CLKAbsence));

        if((DFSDM2_0->FLTISR & DFSDM_FLAG_CLKAbsence) != RESET) {
            bitstatus = SET;
        } else {
            bitstatus = RESET;
        }
    }

    return bitstatus;
}

/**
  * 简介:  检查是否设置了指定的短路通道检测器标志。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  DFSDM_FLAG_SCD: 指定要检查的标志。
  *         此参数可以是 @ref DFSDM_SCD_Flag_Definition的值
  * 
  * 返回值: 无
  */
FlagStatus DFSDM_GetShortCircuitFlagStatus(uint32_t Instance, uint32_t DFSDM_FLAG_SCD) {
    ITStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_DFSDM_SCD_FLAG(DFSDM_FLAG_SCD));

    if(Instance == 1) {
        if ((DFSDM1_0->FLTISR & DFSDM_FLAG_SCD) != RESET) {
            bitstatus = SET;
        } else {
            bitstatus = RESET;
        }
    } else { /* DFSDM2 */
        if ((DFSDM2_0->FLTISR & DFSDM_FLAG_SCD) != RESET) {
            bitstatus = SET;
        } else {
            bitstatus = RESET;
        }
    }

    return bitstatus;
}
#endif /* STM32F413_423xx */
/**
  * 简介:  检查是否设置了指定的看门狗阈值标志。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_AWDChannelx: 其中 x 可以是0到7 之间的值，以选择 DFSDM通道。
  * 
  * 参数:  DFSDM_Threshold: 指定阈值。
  *         此参数可以是 @ref DFSDM_Threshold_Selection的值。
  * 
  * 返回值: 无
  */
FlagStatus DFSDM_GetWatchdogFlagStatus(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_AWDChannelx, uint8_t DFSDM_Threshold) {
    ITStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_Threshold(DFSDM_Threshold));
    assert_param(IS_DFSDM_AWD_CHANNEL(DFSDM_AWDChannelx));

    if ((DFSDMx->FLTAWSR & ((DFSDM_AWDChannelx >> 16) << DFSDM_Threshold) ) != RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  清除DFSDMx的挂起标志。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_CLEARF: 指定要清除的挂起位。
  *         此参数可以是以下值的任意组合:
  *            @arg DFSDM_CLEARF_JOVR: 注入的数据溢出清除标志
  *            @arg DFSDM_CLEARF_ROVR: 常规数据溢出清除标志
  * 
  * 返回值: 无
  */
void DFSDM_ClearFlag(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_CLEARF) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_CLEAR_FLAG(DFSDM_CLEARF));

    /* 清除 pending Flag 位 */
    DFSDMx->FLTICR |= DFSDM_CLEARF;
}

#if defined(STM32F412xG)
/**
  * 简介:  清除DFSDMx的挂起时钟缺失通道标志。
  * 
  * 参数:  DFSDM_CLEARF_CLKAbsence: 指定要清除的挂起位。
  *         此参数可以是 @ref DFSDM_Clear_ClockAbs_Flag_Definition的任意组合
  * 
  * 返回值: 无
  */
void DFSDM_ClearClockAbsenceFlag(uint32_t DFSDM_CLEARF_CLKAbsence) {
    /* 检查参数 */
    assert_param(IS_DFSDM_CLK_ABS_CLEARF(DFSDM_CLEARF_CLKAbsence));

    /* 清除 IT pending Flag 位 */
    DFSDM1_0->FLTICR |= DFSDM_CLEARF_CLKAbsence;
}

/**
  * 简介:  清除DFSDMx的挂起短路通道标志。
  * 
  * 参数:  DFSDM_CLEARF_SCD: 指定要清除的挂起位。
  *         此参数可以是 @ref DFSDM_Clear_Short_Circuit_Flag_Definition的任意组合
  * 
  * 返回值: 无
  */
void DFSDM_ClearShortCircuitFlag(uint32_t DFSDM_CLEARF_SCD) {
    /* 检查参数 */
    assert_param(IS_DFSDM_SCD_CHANNEL_FLAG(DFSDM_CLEARF_SCD));

    /* 清除 pending Flag 位 */
    DFSDM1_0->FLTICR |= DFSDM_CLEARF_SCD;
}
#endif /* STM32F412xG */

#if defined(STM32F413_423xx)
/**
  * 简介:  清除DFSDMx的挂起时钟缺失通道标志。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  DFSDM_CLEARF_CLKAbsence: 指定要清除的挂起位。
  *         此参数可以是 @ref DFSDM_Clear_ClockAbs_Flag_Definition的任意组合
  * 
  * 返回值: 无
  */
void DFSDM_ClearClockAbsenceFlag(uint32_t Instance, uint32_t DFSDM_CLEARF_CLKAbsence) {
    /* 检查参数 */
    assert_param(IS_DFSDM_CLK_ABS_CLEARF(DFSDM_CLEARF_CLKAbsence));

    if(Instance == 1) {
        /* 清除 IT pending Flag 位 */
        DFSDM1_0->FLTICR |= DFSDM_CLEARF_CLKAbsence;
    } else { /* DFSDM2 */
        /* 清除 IT pending Flag 位 */
        DFSDM2_0->FLTICR |= DFSDM_CLEARF_CLKAbsence;
    }
}

/**
  * 简介:  清除DFSDMx的挂起短路通道标志。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  DFSDM_CLEARF_SCD: 指定要清除的挂起位。
  *         此参数可以是 @ref DFSDM_Clear_Short_Circuit_Flag_Definition的任意组合
  * 
  * 返回值: 无
  */
void DFSDM_ClearShortCircuitFlag(uint32_t Instance, uint32_t DFSDM_CLEARF_SCD) {
    /* 检查参数 */
    assert_param(IS_DFSDM_SCD_CHANNEL_FLAG(DFSDM_CLEARF_SCD));

    if(Instance == 1) {
        /* 清除 pending Flag 位 */
        DFSDM1_0->FLTICR |= DFSDM_CLEARF_SCD;
    } else {
        /* 清除 pending Flag 位 */
        DFSDM2_0->FLTICR |= DFSDM_CLEARF_SCD;
    }
}
#endif /* STM32F413_423xx */
/**
  * 简介:  清除DFSDMx的挂起模拟监视器通道标志。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_AWDChannelx: 其中 x 可以是0到7 之间的值，以选择 DFSDM通道。
  * 
  * 参数:  DFSDM_Threshold: 指定阈值。
  *         此参数可以是 @ref DFSDM_Threshold_Selection的值。
  * 
  * 返回值: 无
  */
void DFSDM_ClearAnalogWatchdogFlag(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_AWDChannelx, uint8_t DFSDM_Threshold) {
    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_Threshold(DFSDM_Threshold));
    assert_param(IS_DFSDM_AWD_CHANNEL(DFSDM_AWDChannelx));

    if ((DFSDMx->FLTAWSR & ((DFSDM_AWDChannelx >> 16) << DFSDM_Threshold) ) != RESET) {
        /* 清除 pending Flag 位 */
        DFSDMx->FLTAWCFR |= (DFSDM_AWDChannelx >> 16) << DFSDM_Threshold;
    }
}

/**
  * 简介:  检查指定的 DFSDM 中断是否已发生。
  * 
  * 参数:  DFSDMx: 指定要选择的筛选器:
  *         此参数可以是以下值之一:
  *            @arg DFSDM1_0 : DFSDM 1 Filter 0
  *            @arg DFSDM1_1 : DFSDM 1 Filter 1
  *            @arg DFSDM2_0 : DFSDM 2 Filter 0 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_1 : DFSDM 2 Filter 1 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_2 : DFSDM 2 Filter 2 (仅适用于 STM32F413_423xx 设备)
  *            @arg DFSDM2_3 : DFSDM 2 Filter 3 (仅适用于 STM32F413_423xx 设备)
  * 
  * 参数:  DFSDM_IT: 指定要检查的 DFSDM 中断源。
  *            @arg DFSDM_IT_JEOC: 注入的转换中断源的结束
  *            @arg DFSDM_IT_REOC: 常规转换结束 中断源
  *            @arg DFSDM_IT_JOVR: 注入的数据超限中断源
  *            @arg DFSDM_IT_ROVR: 常规数据超限中断源
  *            @arg DFSDM_IT_AWD : 模拟看门狗中断源
  * 
  * 返回值: DFSDM_IT 的新状态(SET 或 RESET)。
  */
ITStatus DFSDM_GetITStatus(DFSDM_Filter_TypeDef* DFSDMx, uint32_t DFSDM_IT) {
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    /* 检查参数 */
    assert_param(IS_DFSDM_ALL_FILTER(DFSDMx));
    assert_param(IS_DFSDM_IT(DFSDM_IT));

    /* 获取中断状态位值 */
    itstatus = DFSDMx->FLTISR & DFSDM_IT;

    /* 检查中断是否已启用 */
    itenable = DFSDMx->FLTCR2 & DFSDM_IT;

    if ((itstatus != RESET) && (itenable != RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

#if defined(STM32F412xG)
/**
  * 简介:  检查指定的"时钟缺失"通道中断是否已发生。
  * 
  * 参数:  DFSDM_IT_CLKAbsence: 指定在哪个通道上检查中断源。
  *         此参数可以是 @ref DFSDM_Clock_Absence_Interrupt_Definition的值。
  * 
  * 返回值: DFSDM_IT 的新状态(SET 或 RESET)。
  * 
  * 注意:   时钟缺失中断仅由DFSDM0处理。
  */
ITStatus DFSDM_GetClockAbsenceITStatus(uint32_t DFSDM_IT_CLKAbsence) {
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    /* 检查参数 */
    assert_param(IS_DFSDM_CLK_ABS_IT(DFSDM_IT_CLKAbsence));

    /* 获取中断状态位值 */
    itstatus = DFSDM0->FLTISR & DFSDM_IT_CLKAbsence;

    /* 检查中断是否已启用 */
    itenable = DFSDM0->FLTCR2 & DFSDM_IT_CKAB;

    if ((itstatus != RESET) && (itenable != RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  检查指定的短路通道中断是否已经发生。
  * 
  * 参数:  DFSDM_IT_SCR: 指定在哪个通道上检查中断源。
  *         这个参数可以是 @ref DFSDM_SCD_Interrupt_Definition的一个值。
  * 
  * 返回值: DFSDM_IT 的新状态(SET 或 RESET)。
  * 
  * 注意:   短路中断仅由DFSDM0处理。
  */
ITStatus DFSDM_GetShortCircuitITStatus(uint32_t DFSDM_IT_SCR) {
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    /* 检查参数 */
    assert_param(IS_DFSDM_SCD_IT(DFSDM_IT_SCR));

    /* 获取中断状态位值 */
    itstatus = DFSDM0->FLTISR & DFSDM_IT_SCR;

    /* 检查中断是否已启用 */
    itenable = DFSDM0->FLTCR2 & DFSDM_IT_SCD;

    if ((itstatus != RESET) && (itenable != RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}
#endif /* STM32F412xG */

#if defined(STM32F413_423xx)
/**
  * 简介:  检查指定的"时钟缺失"通道中断是否已发生。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  DFSDM_IT_CLKAbsence: 指定在哪个通道上检查中断源。
  *         此参数可以是 @ref DFSDM_Clock_Absence_Interrupt_Definition的值。
  * 
  * 返回值: DFSDM_IT 的新状态(SET 或 RESET)。
  * 
  * 注意:   时钟缺失中断仅由DFSDM0处理。
  */
ITStatus DFSDM_GetClockAbsenceITStatus(uint32_t Instance, uint32_t DFSDM_IT_CLKAbsence) {
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    /* 检查参数 */
    assert_param(IS_DFSDM_CLK_ABS_IT(DFSDM_IT_CLKAbsence));

    if(Instance == 1) {
        /* 获取中断状态位值 */
        itstatus = DFSDM1_0->FLTISR & DFSDM_IT_CLKAbsence;
        /* 检查中断是否已启用 */
        itenable = DFSDM1_0->FLTCR2 & DFSDM_IT_CKAB;
    } else {
        /* 获取中断状态位值 */
        itstatus = DFSDM2_0->FLTISR & DFSDM_IT_CLKAbsence;
        /* 检查中断是否已启用 */
        itenable = DFSDM1_0->FLTCR2 & DFSDM_IT_CKAB;
    }

    if ((itstatus != RESET) && (itenable != RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

/**
  * 简介:  检查指定的短路通道中断是否已经发生。
  * 
  * 参数:  Instance: 选择 DFSDM 的实例
  *         此参数可以是: 1 or 2.
  * 
  * 参数:  DFSDM_IT_SCR: 指定在哪个通道上检查中断源。
  *         这个参数可以是 @ref DFSDM_SCD_Interrupt_Definition的一个值。
  * 
  * 返回值: DFSDM_IT 的新状态(SET 或 RESET)。
  * 
  * 注意:   短路中断只由滤波器 0 处理。
  */
ITStatus DFSDM_GetShortCircuitITStatus(uint32_t Instance, uint32_t DFSDM_IT_SCR) {
    ITStatus bitstatus = RESET;
    uint32_t itstatus = 0x0, itenable = 0x0;

    /* 检查参数 */
    assert_param(IS_DFSDM_SCD_IT(DFSDM_IT_SCR));

    if(Instance == 1) {
        /* 获取中断状态位值 */
        itstatus = DFSDM1_0->FLTISR & DFSDM_IT_SCR;

        /* 检查中断是否已启用 */
        itenable = DFSDM1_0->FLTCR2 & DFSDM_IT_SCD;
    } else { /* DFSDM2 */
        /* 获取中断状态位值 */
        itstatus = DFSDM2_0->FLTISR & DFSDM_IT_SCR;

        /* 检查中断是否已启用 */
        itenable = DFSDM2_0->FLTCR2 & DFSDM_IT_SCD;
    }

    if ((itstatus != RESET) && (itenable != RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

#endif /* STM32F413_423xx */

#endif /* STM32F412xG || STM32F413_423xx */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
