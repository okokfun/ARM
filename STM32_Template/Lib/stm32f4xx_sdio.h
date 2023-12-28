/**
  ******************************************************************************
  * 文件:    stm32f4xx_sdio.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 SDIO 固件库的所有功能原型.
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
#ifndef __STM32F4xx_SDIO_H
#define __STM32F4xx_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup SDIO
  * @{
  */

/* Exported types ------------------------------------------------------------*/

typedef struct {
    uint32_t SDIO_ClockEdge;            /*!< 指定进行位捕获的时钟转换。
                                            该参数可以是@ref SDIO_Clock_Edge 的值 */

    uint32_t SDIO_ClockBypass;          /*!< 指定是启用还是禁用 SDIO 时钟分频器旁路。
                                            该参数可以是@ref SDIO_Clock_Bypass 的值 */

    uint32_t SDIO_ClockPowerSave;       /*!< 指定当总线空闲时是启用还是禁用 SDIO 时钟输出。
                                            该参数可以是@ref SDIO_Clock_Power_Save 的值 */

    uint32_t SDIO_BusWide;              /*!< 指定 SDIO 总线宽度。
                                            该参数可以是@ref SDIO_Bus_Wide 的值 */

    uint32_t SDIO_HardwareFlowControl;  /*!< 指定是启用还是禁用 SDIO 硬件流控制。
                                            该参数可以是@ref SDIO_Hardware_Flow_Control 的值 */

    uint8_t SDIO_ClockDiv;              /*!< 指定 SDIO 控制器的时钟频率。
                                            此参数可以是 0x00 和 0xFF 之间的值。 */

} SDIO_InitTypeDef;

typedef struct {
    uint32_t SDIO_Argument;  /*!< 指定作为命令消息的一部分发送到卡的 SDIO 命令参数。
								如果命令包含参数，则必须在将命令写入命令寄存器之前将其加载到该寄存器中 */

    uint32_t SDIO_CmdIndex;  /*!< 指定 SDIO 命令索引。 它必须低于 0x40。 */

    uint32_t SDIO_Response;  /*!< 指定 SDIO 响应类型。
                                 该参数可以是@ref SDIO_Response_Type 的值 */

    uint32_t SDIO_Wait;      /*!< 指定是启用还是禁用 SDIO 等待中断请求。
                                 该参数可以是@ref SDIO_Wait_Interrupt_State 的值 */

    uint32_t SDIO_CPSM;      /*!< 指定是启用还是禁用 SDIO 命令路径状态机 (CPSM)。
                                 该参数可以是@ref SDIO_CPSM_State 的值 */
} SDIO_CmdInitTypeDef;

typedef struct {
    uint32_t SDIO_DataTimeOut;    /*!< 指定卡总线时钟周期中的数据超时周期。 */

    uint32_t SDIO_DataLength;     /*!< 指定要传输的数据字节数。 */

    uint32_t SDIO_DataBlockSize;  /*!< 指定块传输的数据块大小。
                                      该参数可以是@ref SDIO_Data_Block_Size 的值 */

    uint32_t SDIO_TransferDir;    /*!< 指定数据传输方向，传输是读取还是写入。
                                      该参数可以是@ref SDIO_Transfer_Direction 的值 */

    uint32_t SDIO_TransferMode;   /*!< 指定数据传输是流模式还是块模式。
                                      该参数可以是@ref SDIO_Transfer_Type 的值 */

    uint32_t SDIO_DPSM;           /*!< 指定是启用还是禁用 SDIO 数据路径状态机 (DPSM)。
                                      该参数可以是@ref SDIO_DPSM_State 的值 */
} SDIO_DataInitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup SDIO_Exported_Constants
  * @{
  */

/** @defgroup SDIO_Clock_Edge
  * @{
  */
#define SDIO_ClockEdge_Rising               ((uint32_t)0x00000000)
#define SDIO_ClockEdge_Falling              ((uint32_t)0x00002000)
#define IS_SDIO_CLOCK_EDGE(EDGE) (((EDGE) == SDIO_ClockEdge_Rising) || \
                                  ((EDGE) == SDIO_ClockEdge_Falling))
/**
  * @}
  */

/** @defgroup SDIO_Clock_Bypass
  * @{
  */
#define SDIO_ClockBypass_Disable             ((uint32_t)0x00000000)
#define SDIO_ClockBypass_Enable              ((uint32_t)0x00000400)
#define IS_SDIO_CLOCK_BYPASS(BYPASS) (((BYPASS) == SDIO_ClockBypass_Disable) || \
                                      ((BYPASS) == SDIO_ClockBypass_Enable))
/**
  * @}
  */

/** @defgroup SDIO_Clock_Power_Save
  * @{
  */
#define SDIO_ClockPowerSave_Disable         ((uint32_t)0x00000000)
#define SDIO_ClockPowerSave_Enable          ((uint32_t)0x00000200)
#define IS_SDIO_CLOCK_POWER_SAVE(SAVE) (((SAVE) == SDIO_ClockPowerSave_Disable) || \
                                        ((SAVE) == SDIO_ClockPowerSave_Enable))
/**
  * @}
  */

/** @defgroup SDIO_Bus_Wide
  * @{
  */
#define SDIO_BusWide_1b                     ((uint32_t)0x00000000)
#define SDIO_BusWide_4b                     ((uint32_t)0x00000800)
#define SDIO_BusWide_8b                     ((uint32_t)0x00001000)
#define IS_SDIO_BUS_WIDE(WIDE) (((WIDE) == SDIO_BusWide_1b) || ((WIDE) == SDIO_BusWide_4b) || \
                                ((WIDE) == SDIO_BusWide_8b))

/**
  * @}
  */

/** @defgroup SDIO_Hardware_Flow_Control
  * @{
  */
#define SDIO_HardwareFlowControl_Disable    ((uint32_t)0x00000000)
#define SDIO_HardwareFlowControl_Enable     ((uint32_t)0x00004000)
#define IS_SDIO_HARDWARE_FLOW_CONTROL(CONTROL) (((CONTROL) == SDIO_HardwareFlowControl_Disable) || \
        ((CONTROL) == SDIO_HardwareFlowControl_Enable))
/**
  * @}
  */

/** @defgroup SDIO_Power_State
  * @{
  */
#define SDIO_PowerState_OFF                 ((uint32_t)0x00000000)
#define SDIO_PowerState_ON                  ((uint32_t)0x00000003)
#define IS_SDIO_POWER_STATE(STATE) (((STATE) == SDIO_PowerState_OFF) || ((STATE) == SDIO_PowerState_ON))
/**
  * @}
  */


/** @defgroup SDIO_Interrupt_sources
  * @{
  */
#define SDIO_IT_CCRCFAIL                    ((uint32_t)0x00000001)
#define SDIO_IT_DCRCFAIL                    ((uint32_t)0x00000002)
#define SDIO_IT_CTIMEOUT                    ((uint32_t)0x00000004)
#define SDIO_IT_DTIMEOUT                    ((uint32_t)0x00000008)
#define SDIO_IT_TXUNDERR                    ((uint32_t)0x00000010)
#define SDIO_IT_RXOVERR                     ((uint32_t)0x00000020)
#define SDIO_IT_CMDREND                     ((uint32_t)0x00000040)
#define SDIO_IT_CMDSENT                     ((uint32_t)0x00000080)
#define SDIO_IT_DATAEND                     ((uint32_t)0x00000100)
#define SDIO_IT_STBITERR                    ((uint32_t)0x00000200)
#define SDIO_IT_DBCKEND                     ((uint32_t)0x00000400)
#define SDIO_IT_CMDACT                      ((uint32_t)0x00000800)
#define SDIO_IT_TXACT                       ((uint32_t)0x00001000)
#define SDIO_IT_RXACT                       ((uint32_t)0x00002000)
#define SDIO_IT_TXFIFOHE                    ((uint32_t)0x00004000)
#define SDIO_IT_RXFIFOHF                    ((uint32_t)0x00008000)
#define SDIO_IT_TXFIFOF                     ((uint32_t)0x00010000)
#define SDIO_IT_RXFIFOF                     ((uint32_t)0x00020000)
#define SDIO_IT_TXFIFOE                     ((uint32_t)0x00040000)
#define SDIO_IT_RXFIFOE                     ((uint32_t)0x00080000)
#define SDIO_IT_TXDAVL                      ((uint32_t)0x00100000)
#define SDIO_IT_RXDAVL                      ((uint32_t)0x00200000)
#define SDIO_IT_SDIOIT                      ((uint32_t)0x00400000)
#define SDIO_IT_CEATAEND                    ((uint32_t)0x00800000)
#define IS_SDIO_IT(IT) ((((IT) & (uint32_t)0xFF000000) == 0x00) && ((IT) != (uint32_t)0x00))
/**
  * @}
  */

/** @defgroup SDIO_Command_Index
  * @{
  */
#define IS_SDIO_CMD_INDEX(INDEX)            ((INDEX) < 0x40)
/**
  * @}
  */

/** @defgroup SDIO_Response_Type
  * @{
  */
#define SDIO_Response_No                    ((uint32_t)0x00000000)
#define SDIO_Response_Short                 ((uint32_t)0x00000040)
#define SDIO_Response_Long                  ((uint32_t)0x000000C0)
#define IS_SDIO_RESPONSE(RESPONSE) (((RESPONSE) == SDIO_Response_No) || \
                                    ((RESPONSE) == SDIO_Response_Short) || \
                                    ((RESPONSE) == SDIO_Response_Long))
/**
  * @}
  */

/** @defgroup SDIO_Wait_Interrupt_State
  * @{
  */
#define SDIO_Wait_No                        ((uint32_t)0x00000000) /*!< SDIO 无等待，已启用 TimeOut */
#define SDIO_Wait_IT                        ((uint32_t)0x00000100) /*!< SDIO 等待中断请求 */
#define SDIO_Wait_Pend                      ((uint32_t)0x00000200) /*!< SDIO 等待传输结束 */
#define IS_SDIO_WAIT(WAIT) (((WAIT) == SDIO_Wait_No) || ((WAIT) == SDIO_Wait_IT) || \
                            ((WAIT) == SDIO_Wait_Pend))
/**
  * @}
  */

/** @defgroup SDIO_CPSM_State
  * @{
  */
#define SDIO_CPSM_Disable                    ((uint32_t)0x00000000)
#define SDIO_CPSM_Enable                     ((uint32_t)0x00000400)
#define IS_SDIO_CPSM(CPSM) (((CPSM) == SDIO_CPSM_Enable) || ((CPSM) == SDIO_CPSM_Disable))
/**
  * @}
  */

/** @defgroup SDIO_Response_Registers
  * @{
  */
#define SDIO_RESP1                          ((uint32_t)0x00000000)
#define SDIO_RESP2                          ((uint32_t)0x00000004)
#define SDIO_RESP3                          ((uint32_t)0x00000008)
#define SDIO_RESP4                          ((uint32_t)0x0000000C)
#define IS_SDIO_RESP(RESP) (((RESP) == SDIO_RESP1) || ((RESP) == SDIO_RESP2) || \
                            ((RESP) == SDIO_RESP3) || ((RESP) == SDIO_RESP4))
/**
  * @}
  */

/** @defgroup SDIO_Data_Length
  * @{
  */
#define IS_SDIO_DATA_LENGTH(LENGTH) ((LENGTH) <= 0x01FFFFFF)
/**
  * @}
  */

/** @defgroup SDIO_Data_Block_Size
  * @{
  */
#define SDIO_DataBlockSize_1b               ((uint32_t)0x00000000)
#define SDIO_DataBlockSize_2b               ((uint32_t)0x00000010)
#define SDIO_DataBlockSize_4b               ((uint32_t)0x00000020)
#define SDIO_DataBlockSize_8b               ((uint32_t)0x00000030)
#define SDIO_DataBlockSize_16b              ((uint32_t)0x00000040)
#define SDIO_DataBlockSize_32b              ((uint32_t)0x00000050)
#define SDIO_DataBlockSize_64b              ((uint32_t)0x00000060)
#define SDIO_DataBlockSize_128b             ((uint32_t)0x00000070)
#define SDIO_DataBlockSize_256b             ((uint32_t)0x00000080)
#define SDIO_DataBlockSize_512b             ((uint32_t)0x00000090)
#define SDIO_DataBlockSize_1024b            ((uint32_t)0x000000A0)
#define SDIO_DataBlockSize_2048b            ((uint32_t)0x000000B0)
#define SDIO_DataBlockSize_4096b            ((uint32_t)0x000000C0)
#define SDIO_DataBlockSize_8192b            ((uint32_t)0x000000D0)
#define SDIO_DataBlockSize_16384b           ((uint32_t)0x000000E0)
#define IS_SDIO_BLOCK_SIZE(SIZE) (((SIZE) == SDIO_DataBlockSize_1b) || \
                                  ((SIZE) == SDIO_DataBlockSize_2b) || \
                                  ((SIZE) == SDIO_DataBlockSize_4b) || \
                                  ((SIZE) == SDIO_DataBlockSize_8b) || \
                                  ((SIZE) == SDIO_DataBlockSize_16b) || \
                                  ((SIZE) == SDIO_DataBlockSize_32b) || \
                                  ((SIZE) == SDIO_DataBlockSize_64b) || \
                                  ((SIZE) == SDIO_DataBlockSize_128b) || \
                                  ((SIZE) == SDIO_DataBlockSize_256b) || \
                                  ((SIZE) == SDIO_DataBlockSize_512b) || \
                                  ((SIZE) == SDIO_DataBlockSize_1024b) || \
                                  ((SIZE) == SDIO_DataBlockSize_2048b) || \
                                  ((SIZE) == SDIO_DataBlockSize_4096b) || \
                                  ((SIZE) == SDIO_DataBlockSize_8192b) || \
                                  ((SIZE) == SDIO_DataBlockSize_16384b))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Direction
  * @{
  */
#define SDIO_TransferDir_ToCard             ((uint32_t)0x00000000)
#define SDIO_TransferDir_ToSDIO             ((uint32_t)0x00000002)
#define IS_SDIO_TRANSFER_DIR(DIR) (((DIR) == SDIO_TransferDir_ToCard) || \
                                   ((DIR) == SDIO_TransferDir_ToSDIO))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Type
  * @{
  */
#define SDIO_TransferMode_Block             ((uint32_t)0x00000000)
#define SDIO_TransferMode_Stream            ((uint32_t)0x00000004)
#define IS_SDIO_TRANSFER_MODE(MODE) (((MODE) == SDIO_TransferMode_Stream) || \
                                     ((MODE) == SDIO_TransferMode_Block))
/**
  * @}
  */

/** @defgroup SDIO_DPSM_State
  * @{
  */
#define SDIO_DPSM_Disable                    ((uint32_t)0x00000000)
#define SDIO_DPSM_Enable                     ((uint32_t)0x00000001)
#define IS_SDIO_DPSM(DPSM) (((DPSM) == SDIO_DPSM_Enable) || ((DPSM) == SDIO_DPSM_Disable))
/**
  * @}
  */

/** @defgroup SDIO_Flags
  * @{
  */
#define SDIO_FLAG_CCRCFAIL                  ((uint32_t)0x00000001)
#define SDIO_FLAG_DCRCFAIL                  ((uint32_t)0x00000002)
#define SDIO_FLAG_CTIMEOUT                  ((uint32_t)0x00000004)
#define SDIO_FLAG_DTIMEOUT                  ((uint32_t)0x00000008)
#define SDIO_FLAG_TXUNDERR                  ((uint32_t)0x00000010)
#define SDIO_FLAG_RXOVERR                   ((uint32_t)0x00000020)
#define SDIO_FLAG_CMDREND                   ((uint32_t)0x00000040)
#define SDIO_FLAG_CMDSENT                   ((uint32_t)0x00000080)
#define SDIO_FLAG_DATAEND                   ((uint32_t)0x00000100)
#define SDIO_FLAG_STBITERR                  ((uint32_t)0x00000200)
#define SDIO_FLAG_DBCKEND                   ((uint32_t)0x00000400)
#define SDIO_FLAG_CMDACT                    ((uint32_t)0x00000800)
#define SDIO_FLAG_TXACT                     ((uint32_t)0x00001000)
#define SDIO_FLAG_RXACT                     ((uint32_t)0x00002000)
#define SDIO_FLAG_TXFIFOHE                  ((uint32_t)0x00004000)
#define SDIO_FLAG_RXFIFOHF                  ((uint32_t)0x00008000)
#define SDIO_FLAG_TXFIFOF                   ((uint32_t)0x00010000)
#define SDIO_FLAG_RXFIFOF                   ((uint32_t)0x00020000)
#define SDIO_FLAG_TXFIFOE                   ((uint32_t)0x00040000)
#define SDIO_FLAG_RXFIFOE                   ((uint32_t)0x00080000)
#define SDIO_FLAG_TXDAVL                    ((uint32_t)0x00100000)
#define SDIO_FLAG_RXDAVL                    ((uint32_t)0x00200000)
#define SDIO_FLAG_SDIOIT                    ((uint32_t)0x00400000)
#define SDIO_FLAG_CEATAEND                  ((uint32_t)0x00800000)
#define IS_SDIO_FLAG(FLAG) (((FLAG)  == SDIO_FLAG_CCRCFAIL) || \
                            ((FLAG)  == SDIO_FLAG_DCRCFAIL) || \
                            ((FLAG)  == SDIO_FLAG_CTIMEOUT) || \
                            ((FLAG)  == SDIO_FLAG_DTIMEOUT) || \
                            ((FLAG)  == SDIO_FLAG_TXUNDERR) || \
                            ((FLAG)  == SDIO_FLAG_RXOVERR) || \
                            ((FLAG)  == SDIO_FLAG_CMDREND) || \
                            ((FLAG)  == SDIO_FLAG_CMDSENT) || \
                            ((FLAG)  == SDIO_FLAG_DATAEND) || \
                            ((FLAG)  == SDIO_FLAG_STBITERR) || \
                            ((FLAG)  == SDIO_FLAG_DBCKEND) || \
                            ((FLAG)  == SDIO_FLAG_CMDACT) || \
                            ((FLAG)  == SDIO_FLAG_TXACT) || \
                            ((FLAG)  == SDIO_FLAG_RXACT) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOHE) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOHF) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOF) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOF) || \
                            ((FLAG)  == SDIO_FLAG_TXFIFOE) || \
                            ((FLAG)  == SDIO_FLAG_RXFIFOE) || \
                            ((FLAG)  == SDIO_FLAG_TXDAVL) || \
                            ((FLAG)  == SDIO_FLAG_RXDAVL) || \
                            ((FLAG)  == SDIO_FLAG_SDIOIT) || \
                            ((FLAG)  == SDIO_FLAG_CEATAEND))

#define IS_SDIO_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFF3FF800) == 0x00) && ((FLAG) != (uint32_t)0x00))

#define IS_SDIO_GET_IT(IT) (((IT)  == SDIO_IT_CCRCFAIL) || \
                            ((IT)  == SDIO_IT_DCRCFAIL) || \
                            ((IT)  == SDIO_IT_CTIMEOUT) || \
                            ((IT)  == SDIO_IT_DTIMEOUT) || \
                            ((IT)  == SDIO_IT_TXUNDERR) || \
                            ((IT)  == SDIO_IT_RXOVERR) || \
                            ((IT)  == SDIO_IT_CMDREND) || \
                            ((IT)  == SDIO_IT_CMDSENT) || \
                            ((IT)  == SDIO_IT_DATAEND) || \
                            ((IT)  == SDIO_IT_STBITERR) || \
                            ((IT)  == SDIO_IT_DBCKEND) || \
                            ((IT)  == SDIO_IT_CMDACT) || \
                            ((IT)  == SDIO_IT_TXACT) || \
                            ((IT)  == SDIO_IT_RXACT) || \
                            ((IT)  == SDIO_IT_TXFIFOHE) || \
                            ((IT)  == SDIO_IT_RXFIFOHF) || \
                            ((IT)  == SDIO_IT_TXFIFOF) || \
                            ((IT)  == SDIO_IT_RXFIFOF) || \
                            ((IT)  == SDIO_IT_TXFIFOE) || \
                            ((IT)  == SDIO_IT_RXFIFOE) || \
                            ((IT)  == SDIO_IT_TXDAVL) || \
                            ((IT)  == SDIO_IT_RXDAVL) || \
                            ((IT)  == SDIO_IT_SDIOIT) || \
                            ((IT)  == SDIO_IT_CEATAEND))

#define IS_SDIO_CLEAR_IT(IT) ((((IT) & (uint32_t)0xFF3FF800) == 0x00) && ((IT) != (uint32_t)0x00))

/**
  * @}
  */

/** @defgroup SDIO_Read_Wait_Mode
  * @{
  */
#define SDIO_ReadWaitMode_DATA2             ((uint32_t)0x00000000)
#define SDIO_ReadWaitMode_CLK               ((uint32_t)0x00000001)
#define IS_SDIO_READWAIT_MODE(MODE) (((MODE) == SDIO_ReadWaitMode_CLK) || \
                                     ((MODE) == SDIO_ReadWaitMode_DATA2))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/*  用于将 SDIO 配置设置为默认复位状态的函数 ****/
void SDIO_DeInit(void); // 将SDIO外设寄存器去初始化为其默认复位值。

/* 初始化和配置功能 *********************************/
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct); // 根据SDIO_InitStruct中指定的参数初始化SDIO外设。
void SDIO_StructInit(SDIO_InitTypeDef* SDIO_InitStruct); // 用每个SDIO_InitStruct成员的默认值填充其默认值。
void SDIO_ClockCmd(FunctionalState NewState); // 启用或禁用 SDIO 时钟。
void SDIO_SetPowerState(uint32_t SDIO_PowerState); // 设置控制器的电源状态。
uint32_t SDIO_GetPowerState(void); // 获取控制器的电源状态。

/* 命令路径状态机 (CPSM) 管理功能 *********************/
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct); // 根据SDIO_CmdInitStruct中指定的参数初始化SDIO命令并发送命令。
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef* SDIO_CmdInitStruct); // 用每个SDIO_CmdInitStruct成员的默认值填充该成员。
uint8_t SDIO_GetCommandResponse(void); // 返回接收到响应的最后一个命令的命令索引
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP); // 返回从卡收到的对最后一个命令的响应。

/* 数据路径状态机 (DPSM) 管理功能 ************************/
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct); // 根据SDIO_DataInitStruct中指定的参数初始化 SDIO 数据路径。
void SDIO_DataStructInit(SDIO_DataInitTypeDef* SDIO_DataInitStruct); // 用每个SDIO_DataInitStruct成员的默认值填充每个成员。
uint32_t SDIO_GetDataCounter(void); // 返回要传输的剩余数据字节数。
uint32_t SDIO_ReadData(void); // 从Rx FIFO读取一个数据字。
void SDIO_WriteData(uint32_t Data); // 将一个数据字写入 Tx FIFO。
uint32_t SDIO_GetFIFOCount(void); // 返回要写入 FIFO 或从 FIFO 读取的剩余字数。

/* SDIO IO Cards 模式管理功能 ************************************/
void SDIO_StartSDIOReadWait(FunctionalState NewState); // 启动 SD I/O 读取等待操作。
void SDIO_StopSDIOReadWait(FunctionalState NewState); // 停止 SD I/O 读取等待操作。
void SDIO_SetSDIOReadWaitMode(uint32_t SDIO_ReadWaitMode); // 设置插入读取等待间隔的两个选项之一。
void SDIO_SetSDIOOperation(FunctionalState NewState); // 启用或禁用 SD I/O 模式操作。
void SDIO_SendSDIOSuspendCmd(FunctionalState NewState); // 启用或禁用 SD I/O 模式挂起命令发送。

/* CE-ATA模式管理功能 *******************************************/
void SDIO_CommandCompletionCmd(FunctionalState NewState); // 启用或禁用命令完成信号。
void SDIO_CEATAITCmd(FunctionalState NewState); // 启用或禁用 CE-ATA 中断。
void SDIO_SendCEATACmd(FunctionalState NewState); // 发送 CE-ATA 命令 (CMD61)。

/* DMA 传输管理功能 *****************************************/
void SDIO_DMACmd(FunctionalState NewState); // 启用或禁用 SDIO DMA 请求。

/* 中断和标志管理功能 **********************************/
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState); // 启用或禁用 SDIO 中断。
FlagStatus SDIO_GetFlagStatus(uint32_t SDIO_FLAG); // 检查是否设置了指定的 SDIO 标志。
void SDIO_ClearFlag(uint32_t SDIO_FLAG); // 清除 SDIO 的挂起标志。
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT); // 检查指定的 SDIO 中断是否发生。
void SDIO_ClearITPendingBit(uint32_t SDIO_IT); // 清除 SDIO 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_SDIO_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
