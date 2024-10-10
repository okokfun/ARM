/**
  ******************************************************************************
  * 文件:    stm32f4xx_dsi.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    DSI模块头文件.
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
#ifndef __STM32F4xx_DSI_H
#define __STM32F4xx_DSI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup DSI
  */
#if defined(STM32F469_479xx)
/* 导出的类型 ------------------------------------------------------------*/
/**
  * 简介:  DSI 初始化结构定义
  */
typedef struct {
    uint32_t AutomaticClockLaneControl; /*!< 自动时钟通道控制
										                    该参数可以是 @ref DSI_Automatic_Clk_Lane_Control 的任意值 */

    uint32_t TXEscapeCkdiv;             /*!< TX Escape 时钟分频
									                    	值 0 和 1 停止 TX_ESC 时钟生成                    */

    uint32_t NumberOfLanes;             /*!< 车道数
										                    此参数可以是 @ref DSI_Number_Of_Lanes 的任何值            */

} DSI_InitTypeDef;

/**
  * 简介:  DSI PLL 时钟结构定义
  */
typedef struct {
    uint32_t PLLNDIV; /*!< PLL 环路分割因子
					  此参数必须是 10 到 125 之间的值   */

    uint32_t PLLIDF;  /*!< PLL 输入分频因子
					  该参数可以是 @ref DSI_PLL_IDF 的任意值 */

    uint32_t PLLODF;  /*!< PLL 输出分频因子
					  该参数可以是 @ref DSI_PLL_ODF 的任意值 */

} DSI_PLLInitTypeDef;

/**
  * 简介:  DSI 视频模式配置
  */
typedef struct {
    uint32_t VirtualChannelID;             /*!< 虚拟频道 ID */

    uint32_t ColorCoding;                  /*!< LTDC接口的颜色编码
											该参数可以是 @ref DSI_Color_Coding 的任意值 */

    uint32_t LooselyPacked;                /*!< LTDC接口的颜色编码
											该参数可以是 @ref DSI_Color_Coding 的任意值 */

    uint32_t Mode;                         /*!< 视频模式类型
											该参数可以是 @ref DSI_Video_Mode_Type 的任意值 */

    uint32_t PacketSize;                   /*!< 视频包大小 */

    uint32_t NumberOfChunks;               /*!< 块数 */

    uint32_t NullPacketSize;               /*!< 空包大小 */

    uint32_t HSPolarity;                   /*!< HSYNC 引脚极性
											此参数可以是 @ref DSI_HSYNC_Polarity 的任何值 */

    uint32_t VSPolarity;                   /*!< VSYNC 引脚极性
											该参数可以是 @ref DSI_VSYNC_Polarity 的任何值 */

    uint32_t DEPolarity;                   /*!< 数据使能引脚极性
											此参数可以是 @ref DSI_DATA_ENABLE_Polarity 的任何值 */

    uint32_t HorizontalSyncActive;         /*!< 水平同步有效持续时间(以通道字节时钟周期为单位) */

    uint32_t HorizontalBackPorch;          /*!< 水平后沿持续时间(以通道字节时钟周期为单位) */

    uint32_t HorizontalLine;               /*!< 水平线持续时间(以通道字节时钟周期为单位) */

    uint32_t VerticalSyncActive;           /*!< 垂直同步有效持续时间 */

    uint32_t VerticalBackPorch;            /*!< 垂直后廊持续时间 */

    uint32_t VerticalFrontPorch;           /*!< 垂直前沿持续时间 */

    uint32_t VerticalActive;               /*!< 垂直活动持续时间 */

    uint32_t LPCommandEnable;              /*!< 低功耗命令使能
											此参数可以是 @ref DSI_LP_Command 的任何值 */

    uint32_t LPLargestPacketSize;          /*!< 在 VSA、VBP 和 VFP 区域期间可放入一行的低功耗最大数据包的大小(以字节为单位) */

    uint32_t LPVACTLargestPacketSize;      /*!< 在 VACT 区域期间可以放入一行的低功耗最大数据包的大小(以字节为单位) */

    uint32_t LPHorizontalFrontPorchEnable; /*!< 低功耗水平前沿使能
											此参数可以是 @ref DSI_LP_HFP 的任何值 */

    uint32_t LPHorizontalBackPorchEnable;  /*!< 低功耗水平后沿使能
										   此参数可以是 @ref DSI_LP_HBP 的任何值 */

    uint32_t LPVerticalActiveEnable;       /*!< 低功耗垂直有源使能
										  此参数可以是 @ref DSI_LP_VACT 的任何值 */

    uint32_t LPVerticalFrontPorchEnable;   /*!< 低功耗垂直前沿使能
											此参数可以是 @ref DSI_LP_VFP 的任何值 */

    uint32_t LPVerticalBackPorchEnable;    /*!< 低功耗垂直后沿使能
											该参数可以是 @ref DSI_LP_VBP 的任何值 */

    uint32_t LPVerticalSyncActiveEnable;   /*!< 低功耗垂直同步主动使能
											此参数可以是 @ref DSI_LP_VSYNC 的任何值 */

    uint32_t FrameBTAAcknowledgeEnable;    /*!< 帧总线周转确认启用
											此参数可以是 @ref DSI_FBTA_acknowledge 的任何值 */

} DSI_VidCfgTypeDef;

/**
  * 简介:  DSI 适配命令模式配置
  */
typedef struct {
    uint32_t VirtualChannelID;      /*!< 虚拟通道ID                                     */

    uint32_t ColorCoding;           /*!< LTDC接口的颜色编码
									该参数可以是 @ref DSI_Color_Coding 的任意值          */

    uint32_t CommandSize;           /*!< LTDC 写入内存命令的最大允许大小，以像素为单位。 
                                    此参数可以是 0x00 和 0xFFFF 之间的任何值              */

    uint32_t TearingEffectSource;   /*!< 撕裂效果源
                                    此参数可以是 @ref DSI_TearingEffectSource 的任何值   */

    uint32_t TearingEffectPolarity; /*!< 撕裂效果引脚极性
                                    此参数可以是 @ref DSI_TearingEffectPolarity 的任何值 */

    uint32_t HSPolarity;            /*!< HSYNC 引脚极性
                                    此参数可以是 @ref DSI_HSYNC_Polarity 的任何值        */

    uint32_t VSPolarity;            /*!< VSYNC 引脚极性
                                    该参数可以是 @ref DSI_VSYNC_Polarity 的任何值        */

    uint32_t DEPolarity;            /*!< 数据使能引脚极性
                                    此参数可以是 @ref DSI_DATA_ENABLE_Polarity 的任何值  */

    uint32_t VSyncPol;              /*!< LTDC 停止的 VSync 边沿
                                    此参数可以是 @ref DSI_Vsync_Polarity 的任何值        */

    uint32_t AutomaticRefresh;      /*!< 自动刷新模式
                                    该参数可以是 @ref DSI_AutomaticRefresh 的任意值      */

    uint32_t TEAcknowledgeRequest;  /*!< 撕裂效果确认请求启用
                                    该参数可以是 @ref DSI_TE_AcknowledgeRequest 的任何值 */
} DSI_CmdCfgTypeDef;

/**
  * 简介:  DSI命令传输模式配置
  */
typedef struct {
    uint32_t LPGenShortWriteNoP;  /*!< 通用短写零参数传输
								 此参数可以是 @ref DSI_LP_LPGenShortWriteNoP 的任何值  */

    uint32_t LPGenShortWriteOneP; /*!< 通用短写一参数传输
                                  此参数可以是 @ref DSI_LP_LPGenShortWriteOneP 的任何值 */

    uint32_t LPGenShortWriteTwoP; /*!< 通用短写两个参数传输
                                  该参数可以是 @ref DSI_LP_LPGenShortWriteTwoP 的任何值 */

    uint32_t LPGenShortReadNoP;   /*!< 通用短读零参数传输
                                  此参数可以是 @ref DSI_LP_LPGenShortReadNoP 的任何值   */

    uint32_t LPGenShortReadOneP;  /*!< 通用短读一参数传输
                                  此参数可以是 @ref DSI_LP_LPGenShortReadOneP 的任何值  */

    uint32_t LPGenShortReadTwoP;  /*!< 通用短读两个参数传输
                                  此参数可以是 @ref DSI_LP_LPGenShortReadTwoP 的任何值  */

    uint32_t LPGenLongWrite;      /*!< 通用长写传输
                                  此参数可以是 @ref DSI_LP_LPGenLongWrite 的任何值     */

    uint32_t LPDcsShortWriteNoP;  /*!< DCS 短写零参数传输
                                  此参数可以是 @ref DSI_LP_LPDcsShortWriteNoP 的任何值  */

    uint32_t LPDcsShortWriteOneP; /*!< DCS 短写一参数传输
                                  此参数可以是 @ref DSI_LP_LPDcsShortWriteOneP 的任何值 */

    uint32_t LPDcsShortReadNoP;   /*!< DCS 短读零参数传输
                                  此参数可以是 @ref DSI_LP_LPDcsShortReadNoP 的任何值   */

    uint32_t LPDcsLongWrite;      /*!< DCS 长写传输
                                  此参数可以是 @ref DSI_LP_LPDcsLongWrite 的任何值      */

    uint32_t LPMaxReadPacket;     /*!< 最大读取数据包大小传输
                                  此参数可以是 @ref DSI_LP_LPMaxReadPacket 的任何值     */

    uint32_t AcknowledgeRequest;  /*!< 确认请求启用
                                  此参数可以是 @ref DSI_AcknowledgeRequest 的任何值     */

} DSI_LPCmdTypeDef;

/**
  * 简介:  DSI PHY 时序定义
  */
typedef struct {
    uint32_t ClockLaneHS2LPTime;        /*!< D-PHY 时钟通道从高速传输到低功耗传输所需的最长时间 */

    uint32_t ClockLaneLP2HSTime;        /*!< D-PHY 时钟通道从低功耗到高速传输所需的最长时间 */

    uint32_t DataLaneHS2LPTime;         /*!< D-PHY 数据通道从高速传输到低功率传输所需的最长时间 */

    uint32_t DataLaneLP2HSTime;         /*!< D-PHY 数据通道从低功耗传输到高速传输所需的最长时间 */

    uint32_t DataLaneMaxReadTime;       /*!< 执行读取命令所需的最长时间 */

    uint32_t StopWaitTime;              /*!< 停止状态后请求高速传输的最短等待时间 */

} DSI_PHY_TimerTypeDef;

/**
  * 简介:  DSI 主机超时定义
  */
typedef struct {
    uint32_t TimeoutCkdiv;                 /*!< 超时时钟划分 */

    uint32_t HighSpeedTransmissionTimeout; /*!< 高速传输超时 */

    uint32_t LowPowerReceptionTimeout;     /*!< 低功率接收超时 */

    uint32_t HighSpeedReadTimeout;         /*!< 高速读取超时 */

    uint32_t LowPowerReadTimeout;          /*!< 低功耗读取超时 */

    uint32_t HighSpeedWriteTimeout;        /*!< 高速写入超时 */

    uint32_t HighSpeedWritePrespMode;      /*!< 高速写预处理模式
                                              此参数可以是 @ref DSI_HS_PrespMode */

    uint32_t LowPowerWriteTimeout;         /*!< 低速写入超时 */

    uint32_t BTATimeout;                   /*!< BTA 超时 */

} DSI_HOST_TimeoutTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup DSI_DCS_Command
  */
#define DSI_ENTER_IDLE_MODE       0x39
#define DSI_ENTER_INVERT_MODE     0x21
#define DSI_ENTER_NORMAL_MODE     0x13
#define DSI_ENTER_PARTIAL_MODE    0x12
#define DSI_ENTER_SLEEP_MODE      0x10
#define DSI_EXIT_IDLE_MODE        0x38
#define DSI_EXIT_INVERT_MODE      0x20
#define DSI_EXIT_SLEEP_MODE       0x11
#define DSI_GET_3D_CONTROL        0x3F
#define DSI_GET_ADDRESS_MODE      0x0B
#define DSI_GET_BLUE_CHANNEL      0x08
#define DSI_GET_DIAGNOSTIC_RESULT 0x0F
#define DSI_GET_DISPLAY_MODE      0x0D
#define DSI_GET_GREEN_CHANNEL     0x07
#define DSI_GET_PIXEL_FORMAT      0x0C
#define DSI_GET_POWER_MODE        0x0A
#define DSI_GET_RED_CHANNEL       0x06
#define DSI_GET_SCANLINE          0x45
#define DSI_GET_SIGNAL_MODE       0x0E
#define DSI_NOP                   0x00
#define DSI_READ_DDB_CONTINUE     0xA8
#define DSI_READ_DDB_START        0xA1
#define DSI_READ_MEMORY_CONTINUE  0x3E
#define DSI_READ_MEMORY_START     0x2E
#define DSI_SET_3D_CONTROL        0x3D
#define DSI_SET_ADDRESS_MODE      0x36
#define DSI_SET_COLUMN_ADDRESS    0x2A
#define DSI_SET_DISPLAY_OFF       0x28
#define DSI_SET_DISPLAY_ON        0x29
#define DSI_SET_GAMMA_CURVE       0x26
#define DSI_SET_PAGE_ADDRESS      0x2B
#define DSI_SET_PARTIAL_COLUMNS   0x31
#define DSI_SET_PARTIAL_ROWS      0x30
#define DSI_SET_PIXEL_FORMAT      0x3A
#define DSI_SET_SCROLL_AREA       0x33
#define DSI_SET_SCROLL_START      0x37
#define DSI_SET_TEAR_OFF          0x34
#define DSI_SET_TEAR_ON           0x35
#define DSI_SET_TEAR_SCANLINE     0x44
#define DSI_SET_VSYNC_TIMING      0x40
#define DSI_SOFT_RESET            0x01
#define DSI_WRITE_LUT             0x2D
#define DSI_WRITE_MEMORY_CONTINUE 0x3C
#define DSI_WRITE_MEMORY_START    0x2C

/** @defgroup DSI_Video_Mode_Type
  */
#define DSI_VID_MODE_NB_PULSES 0
#define DSI_VID_MODE_NB_EVENTS 1
#define DSI_VID_MODE_BURST     2
#define IS_DSI_VIDEO_MODE_TYPE(VideoModeType)       (((VideoModeType) == DSI_VID_MODE_NB_PULSES) || \
        ((VideoModeType) == DSI_VID_MODE_NB_EVENTS) || \
        ((VideoModeType) == DSI_VID_MODE_BURST))

/** @defgroup DSI_Color_Mode
  */
#define DSI_COLOR_MODE_FULL  0
#define DSI_COLOR_MODE_EIGHT DSI_WCR_COLM
#define IS_DSI_COLOR_MODE(ColorMode)                (((ColorMode) == DSI_COLOR_MODE_FULL) || ((ColorMode) == DSI_COLOR_MODE_EIGHT))

/** @defgroup DSI_ShutDown
  */
#define DSI_DISPLAY_ON  0
#define DSI_DISPLAY_OFF DSI_WCR_SHTDN
#define IS_DSI_SHUT_DOWN(ShutDown)                  (((ShutDown) == DSI_DISPLAY_ON) || ((ShutDown) == DSI_DISPLAY_OFF))

/** @defgroup DSI_LP_Command
  */
#define DSI_LP_COMMAND_DISABLE 0
#define DSI_LP_COMMAND_ENABLE  DSI_VMCR_LPCE
#define IS_DSI_LP_COMMAND(LPCommand)                (((LPCommand) == DSI_LP_COMMAND_DISABLE) || ((LPCommand) == DSI_LP_COMMAND_ENABLE))

/** @defgroup DSI_LP_HFP
  */
#define DSI_LP_HFP_DISABLE 0
#define DSI_LP_HFP_ENABLE  DSI_VMCR_LPHFPE
#define IS_DSI_LP_HFP(LPHFP)                        (((LPHFP) == DSI_LP_HFP_DISABLE) || ((LPHFP) == DSI_LP_HFP_ENABLE))

/** @defgroup DSI_LP_HBP
  */
#define DSI_LP_HBP_DISABLE 0
#define DSI_LP_HBP_ENABLE  DSI_VMCR_LPHBPE
#define IS_DSI_LP_HBP(LPHBP)                        (((LPHBP) == DSI_LP_HBP_DISABLE) || ((LPHBP) == DSI_LP_HBP_ENABLE))

/** @defgroup DSI_LP_VACT
  */
#define DSI_LP_VACT_DISABLE 0
#define DSI_LP_VACT_ENABLE  DSI_VMCR_LPVAE
#define IS_DSI_LP_VACTIVE(LPVActive)                (((LPVActive) == DSI_LP_VACT_DISABLE) || ((LPVActive) == DSI_LP_VACT_ENABLE))

/** @defgroup DSI_LP_VFP
  */
#define DSI_LP_VFP_DISABLE 0
#define DSI_LP_VFP_ENABLE  DSI_VMCR_LPVFPE
#define IS_DSI_LP_VFP(LPVFP)                        (((LPVFP) == DSI_LP_VFP_DISABLE) || ((LPVFP) == DSI_LP_VFP_ENABLE))

/** @defgroup DSI_LP_VBP
  */
#define DSI_LP_VBP_DISABLE 0
#define DSI_LP_VBP_ENABLE  DSI_VMCR_LPVBPE
#define IS_DSI_LP_VBP(LPVBP)                        (((LPVBP) == DSI_LP_VBP_DISABLE) || ((LPVBP) == DSI_LP_VBP_ENABLE))

/** @defgroup DSI_LP_VSYNC
  */
#define DSI_LP_VSYNC_DISABLE 0
#define DSI_LP_VSYNC_ENABLE  DSI_VMCR_LPVSAE
#define IS_DSI_LP_VSYNC(LPVSYNC)                    (((LPVSYNC) == DSI_LP_VSYNC_DISABLE) || ((LPVSYNC) == DSI_LP_VSYNC_ENABLE))

/** @defgroup DSI_FBTA_acknowledge
  */
#define DSI_FBTAA_DISABLE 0
#define DSI_FBTAA_ENABLE  DSI_VMCR_FBTAAE
#define IS_DSI_FBTAA(FrameBTAAcknowledge)           (((FrameBTAAcknowledge) == DSI_FBTAA_DISABLE) || ((FrameBTAAcknowledge) == DSI_FBTAA_ENABLE))

/** @defgroup DSI_TearingEffectSource
  */
#define DSI_TE_DSILINK  0
#define DSI_TE_EXTERNAL DSI_WCFGR_TESRC
#define IS_DSI_TE_SOURCE(TESource)                  (((TESource) == DSI_TE_DSILINK) || ((TESource) == DSI_TE_EXTERNAL))

/** @defgroup DSI_TearingEffectPolarity
  */
#define DSI_TE_RISING_EDGE  0
#define DSI_TE_FALLING_EDGE DSI_WCFGR_TEPOL
#define IS_DSI_TE_POLARITY(TEPolarity)              (((TEPolarity) == DSI_TE_RISING_EDGE) || ((TEPolarity) == DSI_TE_FALLING_EDGE))

/** @defgroup DSI_Vsync_Polarity
  */
#define DSI_VSYNC_FALLING 0
#define DSI_VSYNC_RISING  DSI_WCFGR_VSPOL
#define IS_DSI_VS_POLARITY(VSPolarity)              (((VSPolarity) == DSI_VSYNC_FALLING) || ((VSPolarity) == DSI_VSYNC_RISING))

/** @defgroup DSI_AutomaticRefresh
  */
#define DSI_AR_DISABLE 0
#define DSI_AR_ENABLE  DSI_WCFGR_AR
#define IS_DSI_AUTOMATIC_REFRESH(AutomaticRefresh)  (((AutomaticRefresh) == DSI_AR_DISABLE) || ((AutomaticRefresh) == DSI_AR_ENABLE))

/** @defgroup DSI_TE_AcknowledgeRequest
  */
#define DSI_TE_ACKNOWLEDGE_DISABLE 0
#define DSI_TE_ACKNOWLEDGE_ENABLE DSI_CMCR_TEARE
#define IS_DSI_TE_ACK_REQUEST(TEAcknowledgeRequest) (((TEAcknowledgeRequest) == DSI_TE_ACKNOWLEDGE_DISABLE) || ((TEAcknowledgeRequest) == DSI_TE_ACKNOWLEDGE_ENABLE))

/** @defgroup DSI_AcknowledgeRequest
  */
#define DSI_ACKNOWLEDGE_DISABLE 0
#define DSI_ACKNOWLEDGE_ENABLE DSI_CMCR_ARE
#define IS_DSI_ACK_REQUEST(AcknowledgeRequest)      (((AcknowledgeRequest) == DSI_ACKNOWLEDGE_DISABLE) || ((AcknowledgeRequest) == DSI_ACKNOWLEDGE_ENABLE))


/** @defgroup DSI_LP_LPGenShortWriteNoP
  */
#define DSI_LP_GSW0P_DISABLE 0
#define DSI_LP_GSW0P_ENABLE DSI_CMCR_GSW0TX
#define IS_DSI_LP_GSW0P(LP_GSW0P)                   (((LP_GSW0P) == DSI_LP_GSW0P_DISABLE) || ((LP_GSW0P) == DSI_LP_GSW0P_ENABLE))

/** @defgroup DSI_LP_LPGenShortWriteOneP
  */
#define DSI_LP_GSW1P_DISABLE 0
#define DSI_LP_GSW1P_ENABLE DSI_CMCR_GSW1TX
#define IS_DSI_LP_GSW1P(LP_GSW1P)                   (((LP_GSW1P) == DSI_LP_GSW1P_DISABLE) || ((LP_GSW1P) == DSI_LP_GSW1P_ENABLE))

/** @defgroup DSI_LP_LPGenShortWriteTwoP
  */
#define DSI_LP_GSW2P_DISABLE 0
#define DSI_LP_GSW2P_ENABLE DSI_CMCR_GSW2TX
#define IS_DSI_LP_GSW2P(LP_GSW2P)                   (((LP_GSW2P) == DSI_LP_GSW2P_DISABLE) || ((LP_GSW2P) == DSI_LP_GSW2P_ENABLE))

/** @defgroup DSI_LP_LPGenShortReadNoP
  */
#define DSI_LP_GSR0P_DISABLE 0
#define DSI_LP_GSR0P_ENABLE DSI_CMCR_GSR0TX
#define IS_DSI_LP_GSR0P(LP_GSR0P)                   (((LP_GSR0P) == DSI_LP_GSR0P_DISABLE) || ((LP_GSR0P) == DSI_LP_GSR0P_ENABLE))

/** @defgroup DSI_LP_LPGenShortReadOneP
  */
#define DSI_LP_GSR1P_DISABLE 0
#define DSI_LP_GSR1P_ENABLE DSI_CMCR_GSR1TX
#define IS_DSI_LP_GSR1P(LP_GSR1P)                   (((LP_GSR1P) == DSI_LP_GSR1P_DISABLE) || ((LP_GSR1P) == DSI_LP_GSR1P_ENABLE))

/** @defgroup DSI_LP_LPGenShortReadTwoP
  */
#define DSI_LP_GSR2P_DISABLE 0
#define DSI_LP_GSR2P_ENABLE DSI_CMCR_GSR2TX
#define IS_DSI_LP_GSR2P(LP_GSR2P)                   (((LP_GSR2P) == DSI_LP_GSR2P_DISABLE) || ((LP_GSR2P) == DSI_LP_GSR2P_ENABLE))

/** @defgroup DSI_LP_LPGenLongWrite
  */
#define DSI_LP_GLW_DISABLE 0
#define DSI_LP_GLW_ENABLE DSI_CMCR_GLWTX
#define IS_DSI_LP_GLW(LP_GLW)                       (((LP_GLW) == DSI_LP_GLW_DISABLE) || ((LP_GLW) == DSI_LP_GLW_ENABLE))

/** @defgroup DSI_LP_LPDcsShortWriteNoP
  */
#define DSI_LP_DSW0P_DISABLE 0
#define DSI_LP_DSW0P_ENABLE DSI_CMCR_DSW0TX
#define IS_DSI_LP_DSW0P(LP_DSW0P)                   (((LP_DSW0P) == DSI_LP_DSW0P_DISABLE) || ((LP_DSW0P) == DSI_LP_DSW0P_ENABLE))

/** @defgroup DSI_LP_LPDcsShortWriteOneP
  */
#define DSI_LP_DSW1P_DISABLE 0
#define DSI_LP_DSW1P_ENABLE DSI_CMCR_DSW1TX
#define IS_DSI_LP_DSW1P(LP_DSW1P)                   (((LP_DSW1P) == DSI_LP_DSW1P_DISABLE) || ((LP_DSW1P) == DSI_LP_DSW1P_ENABLE))

/** @defgroup DSI_LP_LPDcsShortReadNoP
  */
#define DSI_LP_DSR0P_DISABLE 0
#define DSI_LP_DSR0P_ENABLE DSI_CMCR_DSR0TX
#define IS_DSI_LP_DSR0P(LP_DSR0P)                   (((LP_DSR0P) == DSI_LP_DSR0P_DISABLE) || ((LP_DSR0P) == DSI_LP_DSR0P_ENABLE))

/** @defgroup DSI_LP_LPDcsLongWrite
  */
#define DSI_LP_DLW_DISABLE 0
#define DSI_LP_DLW_ENABLE DSI_CMCR_DLWTX
#define IS_DSI_LP_DLW(LP_DLW)                       (((LP_DLW) == DSI_LP_DLW_DISABLE) || ((LP_DLW) == DSI_LP_DLW_ENABLE))

/** @defgroup DSI_LP_LPMaxReadPacket
  */
#define DSI_LP_MRDP_DISABLE 0
#define DSI_LP_MRDP_ENABLE DSI_CMCR_MRDPS
#define IS_DSI_LP_MRDP(LP_MRDP)                     (((LP_MRDP) == DSI_LP_MRDP_DISABLE) || ((LP_MRDP) == DSI_LP_MRDP_ENABLE))

/** @defgroup DSI_HS_PrespMode
  */
#define DSI_HS_PM_DISABLE 0
#define DSI_HS_PM_ENABLE DSI_TCCR3_PM


/** @defgroup DSI_Automatic_Clk_Lane_Control
  */
#define DSI_AUTO_CLK_LANE_CTRL_DISABLE 0
#define DSI_AUTO_CLK_LANE_CTRL_ENABLE  DSI_CLCR_ACR
#define IS_DSI_AUTO_CLKLANE_CONTROL(AutoClkLane)    (((AutoClkLane) == DSI_AUTO_CLK_LANE_CTRL_DISABLE) || ((AutoClkLane) == DSI_AUTO_CLK_LANE_CTRL_ENABLE))

/** @defgroup DSI_Number_Of_Lanes
  */
#define DSI_ONE_DATA_LANE  0
#define DSI_TWO_DATA_LANES 1
#define IS_DSI_NUMBER_OF_LANES(NumberOfLanes)       (((NumberOfLanes) == DSI_ONE_DATA_LANE) || ((NumberOfLanes) == DSI_TWO_DATA_LANES))

/** @defgroup DSI_FlowControl
  */
#define DSI_FLOW_CONTROL_CRC_RX  DSI_PCR_CRCRXE
#define DSI_FLOW_CONTROL_ECC_RX  DSI_PCR_ECCRXE
#define DSI_FLOW_CONTROL_BTA     DSI_PCR_BTAE
#define DSI_FLOW_CONTROL_EOTP_RX DSI_PCR_ETRXE
#define DSI_FLOW_CONTROL_EOTP_TX DSI_PCR_ETTXE
#define DSI_FLOW_CONTROL_ALL     (DSI_FLOW_CONTROL_CRC_RX | DSI_FLOW_CONTROL_ECC_RX | \
                                  DSI_FLOW_CONTROL_BTA | DSI_FLOW_CONTROL_EOTP_RX | \
                                  DSI_FLOW_CONTROL_EOTP_TX)
#define IS_DSI_FLOW_CONTROL(FlowControl)            (((FlowControl) | DSI_FLOW_CONTROL_ALL) == DSI_FLOW_CONTROL_ALL)

/** @defgroup DSI_Color_Coding
  */
#define DSI_RGB565 ((uint32_t)0x00000000) /*!< 值 0x00000001 和 0x00000002 也可用于 RGB565 颜色模式配置 */
#define DSI_RGB666 ((uint32_t)0x00000003) /*!< 值 0x00000004 也可用于 RGB666 颜色模式配置                 */
#define DSI_RGB888 ((uint32_t)0x00000005)
#define IS_DSI_COLOR_CODING(ColorCoding)            ((ColorCoding) <= 5)


/** @defgroup DSI_LooselyPacked
  */
#define DSI_LOOSELY_PACKED_ENABLE  DSI_LCOLCR_LPE
#define DSI_LOOSELY_PACKED_DISABLE 0
#define IS_DSI_LOOSELY_PACKED(LooselyPacked)        (((LooselyPacked) == DSI_LOOSELY_PACKED_ENABLE) || ((LooselyPacked) == DSI_LOOSELY_PACKED_DISABLE))


/** @defgroup DSI_HSYNC_Polarity
  */
#define DSI_HSYNC_ACTIVE_HIGH       0
#define DSI_HSYNC_ACTIVE_LOW        DSI_LPCR_HSP
#define IS_DSI_HSYNC_POLARITY(HSYNC)                (((HSYNC) == DSI_HSYNC_ACTIVE_HIGH) || ((HSYNC) == DSI_HSYNC_ACTIVE_LOW))

/** @defgroup DSI_VSYNC_Polarity
  */
#define DSI_VSYNC_ACTIVE_HIGH       0
#define DSI_VSYNC_ACTIVE_LOW        DSI_LPCR_VSP
#define IS_DSI_VSYNC_POLARITY(VSYNC)                (((VSYNC) == DSI_VSYNC_ACTIVE_HIGH) || ((VSYNC) == DSI_VSYNC_ACTIVE_LOW))

/** @defgroup DSI_DATA_ENABLE_Polarity
  */
#define DSI_DATA_ENABLE_ACTIVE_HIGH 0
#define DSI_DATA_ENABLE_ACTIVE_LOW  DSI_LPCR_DEP
#define IS_DSI_DE_POLARITY(DataEnable)              (((DataEnable) == DSI_DATA_ENABLE_ACTIVE_HIGH) || ((DataEnable) == DSI_DATA_ENABLE_ACTIVE_LOW))

/** @defgroup DSI_PLL_IDF
  */
#define DSI_PLL_IN_DIV1 ((uint32_t)0x00000001)
#define DSI_PLL_IN_DIV2 ((uint32_t)0x00000002)
#define DSI_PLL_IN_DIV3 ((uint32_t)0x00000003)
#define DSI_PLL_IN_DIV4 ((uint32_t)0x00000004)
#define DSI_PLL_IN_DIV5 ((uint32_t)0x00000005)
#define DSI_PLL_IN_DIV6 ((uint32_t)0x00000006)
#define DSI_PLL_IN_DIV7 ((uint32_t)0x00000007)
#define IS_DSI_PLL_IDF(IDF)                         (((IDF) == DSI_PLL_IN_DIV1) || \
        ((IDF) == DSI_PLL_IN_DIV2) || \
        ((IDF) == DSI_PLL_IN_DIV3) || \
        ((IDF) == DSI_PLL_IN_DIV4) || \
        ((IDF) == DSI_PLL_IN_DIV5) || \
        ((IDF) == DSI_PLL_IN_DIV6) || \
        ((IDF) == DSI_PLL_IN_DIV7))

/** @defgroup DSI_PLL_ODF
  */
#define DSI_PLL_OUT_DIV1 ((uint32_t)0x00000000)
#define DSI_PLL_OUT_DIV2 ((uint32_t)0x00000001)
#define DSI_PLL_OUT_DIV4 ((uint32_t)0x00000002)
#define DSI_PLL_OUT_DIV8 ((uint32_t)0x00000003)
#define IS_DSI_PLL_ODF(ODF)                         (((ODF) == DSI_PLL_OUT_DIV1) || \
        ((ODF) == DSI_PLL_OUT_DIV2) || \
        ((ODF) == DSI_PLL_OUT_DIV4) || \
        ((ODF) == DSI_PLL_OUT_DIV8))
#define IS_DSI_PLL_NDIV(NDIV)                       ((10 <= (NDIV)) && ((NDIV) <= 125))

/** @defgroup DSI_Flags
  */
#define DSI_FLAG_TE    DSI_WISR_TEIF
#define DSI_FLAG_ER    DSI_WISR_ERIF
#define DSI_FLAG_BUSY  DSI_WISR_BUSY
#define DSI_FLAG_PLLLS DSI_WISR_PLLLS
#define DSI_FLAG_PLLL  DSI_WISR_PLLLIF
#define DSI_FLAG_PLLU  DSI_WISR_PLLUIF
#define DSI_FLAG_RRS   DSI_WISR_RRS
#define DSI_FLAG_RR    DSI_WISR_RRIF

#define IS_DSI_CLEAR_FLAG(FLAG) (((FLAG) == DSI_FLAG_TE) || ((FLAG) == DSI_FLAG_ER) || \
                                 ((FLAG) == DSI_FLAG_PLLL) || ((FLAG) == DSI_FLAG_PLLU) || \
                                 ((FLAG) == DSI_FLAG_RR))
#define IS_DSI_GET_FLAG(FLAG) (((FLAG) == DSI_FLAG_TE) || ((FLAG) == DSI_FLAG_ER) || \
                               ((FLAG) == DSI_FLAG_BUSY) || ((FLAG) == DSI_FLAG_PLLLS) || \
                               ((FLAG) == DSI_FLAG_PLLL) || ((FLAG) == DSI_FLAG_PLLU) || \
                               ((FLAG) == DSI_FLAG_RRS) || ((FLAG) == DSI_FLAG_RR))

/** @defgroup DSI_Interrupts
  */
#define DSI_IT_TE   DSI_WIER_TEIE
#define DSI_IT_ER   DSI_WIER_ERIE
#define DSI_IT_PLLL DSI_WIER_PLLLIE
#define DSI_IT_PLLU DSI_WIER_PLLUIE
#define DSI_IT_RR   DSI_WIER_RRIE

#define IS_DSI_IT(IT) (((IT) == DSI_IT_TE) || ((IT) == DSI_IT_ER) || \
                       ((IT) == DSI_IT_PLLL) || ((IT) == DSI_IT_PLLU) || \
                       ((IT) == DSI_IT_RR))

/** @defgroup DSI_SHORT_WRITE_PKT_Data_Type
  */
#define DSI_DCS_SHORT_PKT_WRITE_P0 ((uint32_t)0x00000005) /*!< DCS短写，无参数      */
#define DSI_DCS_SHORT_PKT_WRITE_P1 ((uint32_t)0x00000015) /*!< DCS短写，一个参数      */
#define DSI_GEN_SHORT_PKT_WRITE_P0 ((uint32_t)0x00000003) /*!< 通用短写，无参数  */
#define DSI_GEN_SHORT_PKT_WRITE_P1 ((uint32_t)0x00000013) /*!< 通用短写，一个参数  */
#define DSI_GEN_SHORT_PKT_WRITE_P2 ((uint32_t)0x00000023) /*!< 通用短写，两个参数 */
#define IS_DSI_SHORT_WRITE_PACKET_TYPE(MODE)        (((MODE) == DSI_DCS_SHORT_PKT_WRITE_P0) || \
        ((MODE) == DSI_DCS_SHORT_PKT_WRITE_P1) || \
        ((MODE) == DSI_GEN_SHORT_PKT_WRITE_P0) || \
        ((MODE) == DSI_GEN_SHORT_PKT_WRITE_P1) || \
        ((MODE) == DSI_GEN_SHORT_PKT_WRITE_P2))

/** @defgroup DSI_LONG_WRITE_PKT_Data_Type
  */
#define DSI_DCS_LONG_PKT_WRITE ((uint32_t)0x00000039) /*!< DCS长写     */
#define DSI_GEN_LONG_PKT_WRITE ((uint32_t)0x00000029) /*!< 通用长写 */
#define IS_DSI_LONG_WRITE_PACKET_TYPE(MODE)         (((MODE) == DSI_DCS_LONG_PKT_WRITE) || \
        ((MODE) == DSI_GEN_LONG_PKT_WRITE))

/** @defgroup DSI_SHORT_READ_PKT_Data_Type
  */
#define DSI_DCS_SHORT_PKT_READ    ((uint32_t)0x00000006) /*!< DCS 短读                    */
#define DSI_GEN_SHORT_PKT_READ_P0 ((uint32_t)0x00000004) /*!< 通用短读，无参数  */
#define DSI_GEN_SHORT_PKT_READ_P1 ((uint32_t)0x00000014) /*!< 通用短读，一个参数  */
#define DSI_GEN_SHORT_PKT_READ_P2 ((uint32_t)0x00000024) /*!< 通用短读，两个参数 */
#define IS_DSI_READ_PACKET_TYPE(MODE)               (((MODE) == DSI_DCS_SHORT_PKT_READ) || \
        ((MODE) == DSI_GEN_SHORT_PKT_READ_P0) || \
        ((MODE) == DSI_GEN_SHORT_PKT_READ_P1) || \
        ((MODE) == DSI_GEN_SHORT_PKT_READ_P2))

/** @defgroup DSI_Error_Data_Type
  */
#define DSI_ERROR_NONE 0
#define DSI_ERROR_ACK  ((uint32_t)0x00000001) /*!< 确认错误         */
#define DSI_ERROR_PHY  ((uint32_t)0x00000002) /*!< PHY 相关错误          */
#define DSI_ERROR_TX   ((uint32_t)0x00000004) /*!< 传输错误         */
#define DSI_ERROR_RX   ((uint32_t)0x00000008) /*!< 接收错误            */
#define DSI_ERROR_ECC  ((uint32_t)0x00000010) /*!< ECC errors                  */
#define DSI_ERROR_CRC  ((uint32_t)0x00000020) /*!< CRC error                   */
#define DSI_ERROR_PSE  ((uint32_t)0x00000040) /*!< 数据包大小错误          */
#define DSI_ERROR_EOT  ((uint32_t)0x00000080) /*!< 传输结束错误   */
#define DSI_ERROR_OVF  ((uint32_t)0x00000100) /*!< FIFO 溢出错误         */
#define DSI_ERROR_GEN  ((uint32_t)0x00000200) /*!< 通用 FIFO 相关错误 */

/** @defgroup DSI_Lane_Group
  */
#define DSI_CLOCK_LANE ((uint32_t)0x00000000)
#define DSI_DATA_LANES ((uint32_t)0x00000001)
#define IS_DSI_LANE_GROUP(Lane)                     (((Lane) == DSI_CLOCK_LANE) || ((Lane) == DSI_DATA_LANES))

/** @defgroup DSI_Communication_Delay
  */
#define DSI_SLEW_RATE_HSTX ((uint32_t)0x00000000)
#define DSI_SLEW_RATE_LPTX ((uint32_t)0x00000001)
#define DSI_HS_DELAY       ((uint32_t)0x00000002)
#define IS_DSI_COMMUNICATION_DELAY(CommDelay)       (((CommDelay) == DSI_SLEW_RATE_HSTX) || ((CommDelay) == DSI_SLEW_RATE_LPTX) || ((CommDelay) == DSI_HS_DELAY))

/** @defgroup DSI_CustomLane
  */
#define DSI_SWAP_LANE_PINS   ((uint32_t)0x00000000)
#define DSI_INVERT_HS_SIGNAL ((uint32_t)0x00000001)
#define IS_DSI_CUSTOM_LANE(CustomLane)              (((CustomLane) == DSI_SWAP_LANE_PINS) || ((CustomLane) == DSI_INVERT_HS_SIGNAL))

/** @defgroup DSI_Lane_Select
  */
#define DSI_CLOCK_LANE ((uint32_t)0x00000000)
#define DSI_DATA_LANE0 ((uint32_t)0x00000001)
#define DSI_DATA_LANE1 ((uint32_t)0x00000002)
#define IS_DSI_LANE(Lane)                           (((Lane) == DSI_CLOCK_LANE) || ((Lane) == DSI_DATA_LANE0) || ((Lane) == DSI_DATA_LANE1))

/** @defgroup DSI_PHY_Timing
  */
#define DSI_TCLK_POST    ((uint32_t)0x00000000)
#define DSI_TLPX_CLK     ((uint32_t)0x00000001)
#define DSI_THS_EXIT     ((uint32_t)0x00000002)
#define DSI_TLPX_DATA    ((uint32_t)0x00000003)
#define DSI_THS_ZERO     ((uint32_t)0x00000004)
#define DSI_THS_TRAIL    ((uint32_t)0x00000005)
#define DSI_THS_PREPARE  ((uint32_t)0x00000006)
#define DSI_TCLK_ZERO    ((uint32_t)0x00000007)
#define DSI_TCLK_PREPARE ((uint32_t)0x00000008)
#define IS_DSI_PHY_TIMING(Timing)                   (((Timing) == DSI_TCLK_POST   ) || \
        ((Timing) == DSI_TLPX_CLK    ) || \
        ((Timing) == DSI_THS_EXIT    ) || \
        ((Timing) == DSI_TLPX_DATA   ) || \
        ((Timing) == DSI_THS_ZERO    ) || \
        ((Timing) == DSI_THS_TRAIL   ) || \
        ((Timing) == DSI_THS_PREPARE ) || \
        ((Timing) == DSI_TCLK_ZERO   ) || \
        ((Timing) == DSI_TCLK_PREPARE))
#define IS_DSI_ALL_PERIPH(PERIPH) ((PERIPH) == DSI)

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* 初始化和配置功能 *********************************/
void DSI_DeInit(DSI_TypeDef *DSIx); // 将 DSI 外设寄存器取消初始化为其默认复位值。
void DSI_Init(DSI_TypeDef *DSIx, DSI_InitTypeDef* DSI_InitStruct, DSI_PLLInitTypeDef *PLLInit); // 将 DSIx 外设寄存器取消初始化为其默认复位值。
void DSI_StructInit(DSI_InitTypeDef* DSI_InitStruct, DSI_HOST_TimeoutTypeDef* DSI_HOST_TimeoutInitStruct); // 用默认值填充每个 DSI_InitStruct 成员。
void DSI_SetGenericVCID(DSI_TypeDef *DSIx, uint32_t VirtualChannelID); // 配置通用接口回读的虚拟通道ID。
void DSI_ConfigVideoMode(DSI_TypeDef *DSIx, DSI_VidCfgTypeDef *VidCfg); // 选择视频模式并配置相应的参数
void DSI_ConfigAdaptedCommandMode(DSI_TypeDef *DSIx, DSI_CmdCfgTypeDef *CmdCfg); // 选择适应的命令模式并配置相应的参数
void DSI_ConfigCommand(DSI_TypeDef *DSIx, DSI_LPCmdTypeDef *LPCmd); // 配置命令传输模式:高速或低功率，并在数据包传输后启用/禁用确认请求
void DSI_ConfigFlowControl(DSI_TypeDef *DSIx, uint32_t FlowControl); // 配置流量控制参数
void DSI_ConfigPhyTimer(DSI_TypeDef *DSIx, DSI_PHY_TimerTypeDef *PhyTimers); // 配置 DSI PHY计时器参数
void DSI_ConfigHostTimeouts(DSI_TypeDef *DSIx, DSI_HOST_TimeoutTypeDef *HostTimeouts); // 配置 DSI HOST超时参数
void DSI_PatternGeneratorStart(DSI_TypeDef *DSIx, uint32_t Mode, uint32_t Orientation); // 开始测试模式生成
void DSI_PatternGeneratorStop(DSI_TypeDef *DSIx); // 停止测试模式生成
void DSI_Start(DSI_TypeDef *DSIx); // 启动DSI模块
void DSI_Stop(DSI_TypeDef *DSIx); // 停止DSI模块
void DSI_Refresh(DSI_TypeDef *DSIx); // 在命令模式下刷新显示
void DSI_ColorMode(DSI_TypeDef *DSIx, uint32_t ColorMode); // 控制视频模式中的显示颜色模式
void DSI_Shutdown(DSI_TypeDef *DSIx, uint32_t Shutdown); // 控制视频模式下的显示器关闭

/* 与 STM32F4XX 标准外设库版本号 V1.6.0 兼容的别名 */
#define DSI_ConfigLowPowerCommand DSI_ConfigCommand

/* 数据传输管理功能 ****************************************/
void DSI_ShortWrite(DSI_TypeDef *DSIx, uint32_t ChannelID, uint32_t Mode, uint32_t Param1, uint32_t Param2); // DCS或通用短写命令
void DSI_LongWrite(DSI_TypeDef *DSIx, uint32_t ChannelID, uint32_t Mode, uint32_t NbParams, uint32_t Param1, uint8_t* ParametersTable); // DCS或通用长写命令
void DSI_Read(DSI_TypeDef *DSIx, uint32_t ChannelNbr, uint8_t* Array, uint32_t Size, uint32_t Mode, uint32_t DCSCmd, uint8_t* ParametersTable); // 读取命令(DCS或通用)

/* 低功耗功能 ********************************************************/
void DSI_EnterULPMData(DSI_TypeDef *DSIx); // 在D-PHY PLL运行的情况下进入ULPM(超低功率模式)(只有数据通道在ULPM中)
void DSI_ExitULPMData(DSI_TypeDef *DSIx); // 在D-PHY PLL运行的情况下退出ULPM(超低功率模式)(只有数据通道在ULPM中)
void DSI_EnterULPM(DSI_TypeDef *DSIx); // 在D-PHY PLL关闭的情况下进入ULPM(超低功率模式)(数据和时钟通道都在ULPM中)
void DSI_ExitULPM(DSI_TypeDef *DSIx); // 在D-PHY PLL关闭的情况下退出ULPM(超低功率模式)(数据和时钟通道都在ULPM中)
void DSI_SetSlewRateAndDelayTuning(DSI_TypeDef *DSIx, uint32_t CommDelay, uint32_t Lane, uint32_t Value); // 设置回转率和延迟调整
void DSI_SetLowPowerRXFilter(DSI_TypeDef *DSIx, uint32_t Frequency); // 低功率接收滤波器调谐
void DSI_SetSDD(DSI_TypeDef *DSIx, FunctionalState State); // 激活所有车道上的其他当前路径，以满足MIPI D-PHY规范中定义的SDDTx参数
void DSI_SetLanePinsConfiguration(DSI_TypeDef *DSIx, uint32_t CustomLane, uint32_t Lane, FunctionalState State); // 自定义通道管脚配置
void DSI_SetPHYTimings(DSI_TypeDef *DSIx, uint32_t Timing, FunctionalState State, uint32_t Value);
void DSI_ForceTXStopMode(DSI_TypeDef *DSIx, uint32_t Lane, FunctionalState State); // 强制时钟/数据通道处于TX停止模式
void DSI_ForceRXLowPower(DSI_TypeDef *DSIx, FunctionalState State); // 强制LP接收器处于低功率模式
void DSI_ForceDataLanesInRX(DSI_TypeDef *DSIx, FunctionalState State); // BTA后强制数据通道处于RX模式
void DSI_SetPullDown(DSI_TypeDef *DSIx, FunctionalState State); // 启用车道上的下拉按钮，以防止未使用时出现浮动状态
void DSI_SetContentionDetectionOff(DSI_TypeDef *DSIx, FunctionalState State); // 关闭数据通道上的竞争检测

/* 中断和标志管理功能 **********************************/
void DSI_ITConfig(DSI_TypeDef* DSIx, uint32_t DSI_IT, FunctionalState NewState); // 启用或禁用指定的DSI中断。
FlagStatus DSI_GetFlagStatus(DSI_TypeDef* DSIx, uint16_t DSI_FLAG); // 检查是否设置了指定的DSI标志。
void DSI_ClearFlag(DSI_TypeDef* DSIx, uint16_t DSI_FLAG); // 清除指定的DSI标志。
ITStatus DSI_GetITStatus(DSI_TypeDef* DSIx, uint32_t DSI_IT); // 检查指定的DSIx中断是否已发生。
void DSI_ClearITPendingBit(DSI_TypeDef* DSIx, uint32_t DSI_IT); // 清除DSIx中断挂起位。
void DSI_ConfigErrorMonitor(DSI_TypeDef *DSIx, uint32_t ActiveErrors); // 启用错误监视器标志

#endif /* STM32F469_479xx */


#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_DSI_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
