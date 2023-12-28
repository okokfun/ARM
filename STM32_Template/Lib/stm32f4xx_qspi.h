/**
  ******************************************************************************
  * 文件:    stm32f4xx_qspi.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 QSPI 固件库的所有功能原型.
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
#ifndef __STM32F4XX_QUADSPI_H
#define __STM32F4XX_QUADSPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup QSPI
  * @{
  */
#if defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx) || defined(STM32F469_479xx)
/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  QSPI通信配置初始化结构定义
  */
typedef struct {

    uint32_t QSPI_ComConfig_FMode;            /* 指定功能模式
                                           该参数可以是@ref QSPI_ComConfig_Functional_Mode 的值*/

    uint32_t QSPI_ComConfig_DDRMode;          /* 指定双倍数据速率模式
                                           该参数可以是@ref QSPI_ComConfig_DoubleDataRateMode 的值*/

    uint32_t QSPI_ComConfig_DHHC;            /* 指定延迟半 Hclk 周期
                                           该参数可以是@ref QSPI_ComConfig_DelayHalfHclkCycle 的值*/

    uint32_t QSPI_ComConfig_SIOOMode;         /* 指定仅发送指令一次模式
                                           该参数可以是@ref QSPI_ComConfig_SendInstructionOnlyOnceMode 的值*/

    uint32_t QSPI_ComConfig_DMode;            /* 指定数据模式
                                           该参数可以是@ref QSPI_ComConfig_DataMode 的值*/

    uint32_t QSPI_ComConfig_DummyCycles;      /* 指定虚拟循环数。
                                            此参数可以是 0x00 和 0x1F 之间的数字 */

    uint32_t QSPI_ComConfig_ABSize;           /* 指定备用字节大小
                                           该参数可以是@ref QSPI_ComConfig_AlternateBytesSize 的值*/

    uint32_t QSPI_ComConfig_ABMode;           /* 指定备用字节模式
                                           该参数可以是@ref QSPI_ComConfig_AlternateBytesMode 的值*/

    uint32_t QSPI_ComConfig_ADSize;           /* 指定地址大小
                                           该参数可以是@ref QSPI_ComConfig_AddressSize 的值*/

    uint32_t QSPI_ComConfig_ADMode;           /* 指定地址模式
                                           该参数可以是@ref QSPI_ComConfig_AddressMode 的值*/

    uint32_t QSPI_ComConfig_IMode;            /* 指定指令模式
                                           该参数可以是@ref QSPI_ComConfig_InstructionMode 的值*/

    uint32_t QSPI_ComConfig_Ins;      /* 指定指令模式
                                           该参数可以是@ref QSPI_ComConfig_Instruction 的值*/

} QSPI_ComConfig_InitTypeDef;

/**
  * 简介:  QSPI Init structure definition
  */
typedef struct {
    uint32_t QSPI_SShift;    /* 指定样本移位
                               该参数可以是@ref QSPI_Sample_Shift 的值*/

    uint32_t QSPI_Prescaler; /* 指定用于分频 QSPI 时钟的预分频器值。
                               此参数可以是 0x00 到 0xFF 之间的数字 */

    uint32_t QSPI_CKMode;    /* 指定时钟模式
                               该参数可以是@ref QSPI_Clock_Mode 的值*/

    uint32_t QSPI_CSHTime;   /* 指定片选高电平时间
                               该参数可以是@ref QSPI_ChipSelectHighTime 的值*/

    uint32_t QSPI_FSize;     /* 指定闪存大小。
                                QSPI_FSize+1 实际上是寻址闪存所需的地址位数。
                                间接模式下闪存容量最高可达 4GB(使用 32 位寻址)，但内存映射模式下的可寻址空间限制为 512MB
                                此参数可以是 0x00 和 0x1F 之间的数字 */
    uint32_t QSPI_FSelect;   /* 指定将使用的 Flash，
                                  该参数可以是@ref QSPI_Fash_Select 的值*/
    uint32_t QSPI_DFlash;    /* 指定双闪存模式状态
                                  该参数可以是@ref QSPI_Dual_Flash 的值*/
} QSPI_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup QSPI_Exported_Constants
  * @{
  */

/** @defgroup QSPI_Sample_Shift
  * @{
  */
#define QSPI_SShift_NoShift                        ((uint32_t)0x00000000)
#define QSPI_SShift_HalfCycleShift                 ((uint32_t)QUADSPI_CR_SSHIFT)
#define IS_QSPI_SSHIFT(SSHIFT)      (((SSHIFT) == QSPI_SShift_NoShift) ||  ((SSHIFT) == QSPI_SShift_HalfCycleShift))
/* Legacy Defines */
#define QUADSPI_CR_SSHIFT_0    QUADSPI_CR_SSHIFT
/**
  * @}
  */

/** @defgroup QSPI_Prescaler
  * @{
  */
#define IS_QSPI_PRESCALER(PRESCALER) (((PRESCALER) <= 0xFF))
/**
  * @}
  */

/** @defgroup QSPI_Clock_Mode
  * @{
  */
#define QSPI_CKMode_Mode0           ((uint32_t)0x00000000)
#define QSPI_CKMode_Mode3           ((uint32_t)QUADSPI_DCR_CKMODE)
#define IS_QSPI_CKMODE(CKMode)      (((CKMode) == QSPI_CKMode_Mode0) || ((CKMode) == QSPI_CKMode_Mode3))
/**
  * @}
  */

/** @defgroup QSPI_ChipSelectHighTime
  * @{
  */
#define QSPI_CSHTime_1Cycle           ((uint32_t)0x00000000)
#define QSPI_CSHTime_2Cycle           ((uint32_t)QUADSPI_DCR_CSHT_0)
#define QSPI_CSHTime_3Cycle           ((uint32_t)QUADSPI_DCR_CSHT_1)
#define QSPI_CSHTime_4Cycle           ((uint32_t)QUADSPI_DCR_CSHT_0 | QUADSPI_DCR_CSHT_1)
#define QSPI_CSHTime_5Cycle           ((uint32_t)QUADSPI_DCR_CSHT_2)
#define QSPI_CSHTime_6Cycle           ((uint32_t)QUADSPI_DCR_CSHT_2 | QUADSPI_DCR_CSHT_0)
#define QSPI_CSHTime_7Cycle           ((uint32_t)QUADSPI_DCR_CSHT_2 | QUADSPI_DCR_CSHT_1)
#define QSPI_CSHTime_8Cycle           ((uint32_t)QUADSPI_DCR_CSHT)
#define IS_QSPI_CSHTIME(CSHTIME)    (((CSHTIME) == QSPI_CSHTime_1Cycle) || \
                                     ((CSHTIME) == QSPI_CSHTime_2Cycle) || \
                                     ((CSHTIME) == QSPI_CSHTime_3Cycle) || \
                                     ((CSHTIME) == QSPI_CSHTime_4Cycle) || \
                                     ((CSHTIME) == QSPI_CSHTime_5Cycle) || \
                                     ((CSHTIME) == QSPI_CSHTime_6Cycle) || \
                                     ((CSHTIME) == QSPI_CSHTime_7Cycle) || \
                                     ((CSHTIME) == QSPI_CSHTime_8Cycle))
/**
  * @}
  */

/** @defgroup QSPI_Flash_Size
  * @{
  */
#define IS_QSPI_FSIZE(FSIZE)         (((FSIZE) <= 0x1F))
/**
  * @}
  */

/** @defgroup QSPI_Fash_Select
  * @{
  */
#define QSPI_FSelect_1           ((uint32_t)0x00000000)
#define QSPI_FSelect_2           ((uint32_t)QUADSPI_CR_FSEL)
#define IS_QSPI_FSEL(FLA)    (((FLA) == QSPI_FSelect_1) || ((FLA) == QSPI_FSelect_2))
/**
  * @}
  */

/** @defgroup QSPI_Dual_Flash
  * @{
  */
#define QSPI_DFlash_Disable           ((uint32_t)0x00000000)
#define QSPI_DFlash_Enable            ((uint32_t)QUADSPI_CR_DFM)
#define IS_QSPI_DFM(FLA)    (((FLA) == QSPI_DFlash_Enable) || ((FLA) == QSPI_DFlash_Disable))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_Functional_Mode
  * @{
  */
#define QSPI_ComConfig_FMode_Indirect_Write     ((uint32_t)0x00000000)
#define QSPI_ComConfig_FMode_Indirect_Read      ((uint32_t)QUADSPI_CCR_FMODE_0)
#define QSPI_ComConfig_FMode_Auto_Polling       ((uint32_t)QUADSPI_CCR_FMODE_1)
#define QSPI_ComConfig_FMode_Memory_Mapped      ((uint32_t)QUADSPI_CCR_FMODE)
#define IS_QSPI_FMODE(FMODE)                  (((FMODE) == QSPI_ComConfig_FMode_Indirect_Write) || \
        ((FMODE) == QSPI_ComConfig_FMode_Indirect_Read) || \
        ((FMODE) == QSPI_ComConfig_FMode_Auto_Polling) || \
        ((FMODE) == QSPI_ComConfig_FMode_Memory_Mapped))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_DoubleDataRateMode
  * @{
  */
#define QSPI_ComConfig_DDRMode_Disable           ((uint32_t)0x00000000)
#define QSPI_ComConfig_DDRMode_Enable            ((uint32_t)QUADSPI_CCR_DDRM)
#define IS_QSPI_DDRMODE(DDRMODE)    (((DDRMODE) == QSPI_ComConfig_DDRMode_Disable) || \
                                     ((DDRMODE) == QSPI_ComConfig_DDRMode_Enable))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_DelayHalfHclkCycle
  * @{
  */
#define QSPI_ComConfig_DHHC_Disable           ((uint32_t)0x00000000)
#define QSPI_ComConfig_DHHC_Enable            ((uint32_t)QUADSPI_CCR_DHHC)
#define IS_QSPI_DHHC(DHHC)          (((DHHC) == QSPI_ComConfig_DHHC_Disable) || \
                                     ((DHHC) == QSPI_ComConfig_DHHC_Enable))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_SendInstructionOnlyOnceMode
  * @{
  */
#define QSPI_ComConfig_SIOOMode_Disable           ((uint32_t)0x00000000)
#define QSPI_ComConfig_SIOOMode_Enable            ((uint32_t)QUADSPI_CCR_SIOO)
#define IS_QSPI_SIOOMODE(SIOOMODE)    (((SIOOMODE) == QSPI_ComConfig_SIOOMode_Disable) || \
                                       ((SIOOMODE) == QSPI_ComConfig_SIOOMode_Enable))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_DataMode
  * @{
  */
#define QSPI_ComConfig_DMode_NoData          ((uint32_t)0x00000000)
#define QSPI_ComConfig_DMode_1Line           ((uint32_t)QUADSPI_CCR_DMODE_0)
#define QSPI_ComConfig_DMode_2Line           ((uint32_t)QUADSPI_CCR_DMODE_1)
#define QSPI_ComConfig_DMode_4Line           ((uint32_t)QUADSPI_CCR_DMODE)
#define IS_QSPI_DMODE(DMODE)        (((DMODE) == QSPI_ComConfig_DMode_NoData) || \
                                     ((DMODE) == QSPI_ComConfig_DMode_1Line) || \
                                     ((DMODE) == QSPI_ComConfig_DMode_2Line) || \
                                     ((DMODE) == QSPI_ComConfig_DMode_4Line))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_AlternateBytesSize
  * @{
  */
#define QSPI_ComConfig_ABSize_8bit            ((uint32_t)0x00000000)
#define QSPI_ComConfig_ABSize_16bit           ((uint32_t)QUADSPI_CCR_ABSIZE_0)
#define QSPI_ComConfig_ABSize_24bit           ((uint32_t)QUADSPI_CCR_ABSIZE_1)
#define QSPI_ComConfig_ABSize_32bit           ((uint32_t)QUADSPI_CCR_ABSIZE)
#define IS_QSPI_ABSIZE(ABSIZE)      (((ABSIZE) == QSPI_ComConfig_ABSize_8bit) || \
                                     ((ABSIZE) == QSPI_ComConfig_ABSize_16bit) || \
                                     ((ABSIZE) == QSPI_ComConfig_ABSize_24bit) || \
                                     ((ABSIZE) == QSPI_ComConfig_ABSize_32bit))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_AlternateBytesMode
  * @{
  */
#define QSPI_ComConfig_ABMode_NoAlternateByte          ((uint32_t)0x00000000)
#define QSPI_ComConfig_ABMode_1Line                    ((uint32_t)QUADSPI_CCR_ABMODE_0)
#define QSPI_ComConfig_ABMode_2Line                    ((uint32_t)QUADSPI_CCR_ABMODE_1)
#define QSPI_ComConfig_ABMode_4Line                    ((uint32_t)QUADSPI_CCR_ABMODE)
#define IS_QSPI_ABMODE(ABMODE)      (((ABMODE) == QSPI_ComConfig_ABMode_NoAlternateByte) || \
                                     ((ABMODE) == QSPI_ComConfig_ABMode_1Line) || \
                                     ((ABMODE) == QSPI_ComConfig_ABMode_2Line) || \
                                     ((ABMODE) == QSPI_ComConfig_ABMode_4Line))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_AddressSize
  * @{
  */
#define QSPI_ComConfig_ADSize_8bit            ((uint32_t)0x00000000)
#define QSPI_ComConfig_ADSize_16bit           ((uint32_t)QUADSPI_CCR_ADSIZE_0)
#define QSPI_ComConfig_ADSize_24bit           ((uint32_t)QUADSPI_CCR_ADSIZE_1)
#define QSPI_ComConfig_ADSize_32bit           ((uint32_t)QUADSPI_CCR_ADSIZE)
#define IS_QSPI_ADSIZE(ADSIZE)      (((ADSIZE) == QSPI_ComConfig_ADSize_8bit) || \
                                     ((ADSIZE) == QSPI_ComConfig_ADSize_16bit) || \
                                     ((ADSIZE) == QSPI_ComConfig_ADSize_24bit) || \
                                     ((ADSIZE) == QSPI_ComConfig_ADSize_32bit))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_AddressMode
  * @{
  */
#define QSPI_ComConfig_ADMode_NoAddress          ((uint32_t)0x00000000)
#define QSPI_ComConfig_ADMode_1Line              ((uint32_t)QUADSPI_CCR_ADMODE_0)
#define QSPI_ComConfig_ADMode_2Line              ((uint32_t)QUADSPI_CCR_ADMODE_1)
#define QSPI_ComConfig_ADMode_4Line              ((uint32_t)QUADSPI_CCR_ADMODE)
#define IS_QSPI_ADMODE(ADMODE)        (((ADMODE) == QSPI_ComConfig_ADMode_NoAddress) || \
                                       ((ADMODE) == QSPI_ComConfig_ADMode_1Line) || \
                                       ((ADMODE) == QSPI_ComConfig_ADMode_2Line) || \
                                       ((ADMODE) == QSPI_ComConfig_ADMode_4Line))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_InstructionMode
  * @{
  */
#define QSPI_ComConfig_IMode_NoInstruction          ((uint32_t)0x00000000)
#define QSPI_ComConfig_IMode_1Line                  ((uint32_t)QUADSPI_CCR_IMODE_0)
#define QSPI_ComConfig_IMode_2Line                  ((uint32_t)QUADSPI_CCR_IMODE_1)
#define QSPI_ComConfig_IMode_4Line                  ((uint32_t)QUADSPI_CCR_IMODE)
#define IS_QSPI_IMODE(IMODE)        (((IMODE) == QSPI_ComConfig_IMode_NoInstruction) || \
                                     ((IMODE) == QSPI_ComConfig_IMode_1Line) || \
                                     ((IMODE) == QSPI_ComConfig_IMode_2Line) || \
                                     ((IMODE) == QSPI_ComConfig_IMode_4Line))
/**
  * @}
  */

/** @defgroup QSPI_ComConfig_Instruction
  * @{
  */
#define IS_QSPI_INSTRUCTION(INSTRUCTION)           ((INSTRUCTION) <= 0xFF)
/**
  * @}
  */

/** @defgroup QSPI_InterruptsDefinition
  * @{
  */
#define QSPI_IT_TO                (uint32_t)(QUADSPI_CR_TOIE | QUADSPI_SR_TOF)
#define QSPI_IT_SM                (uint32_t)(QUADSPI_CR_SMIE | QUADSPI_SR_SMF)
#define QSPI_IT_FT                (uint32_t)(QUADSPI_CR_FTIE | QUADSPI_SR_FTF)
#define QSPI_IT_TC                (uint32_t)(QUADSPI_CR_TCIE | QUADSPI_SR_TCF)
#define QSPI_IT_TE                (uint32_t)(QUADSPI_CR_TEIE | QUADSPI_SR_TEF)
#define IS_QSPI_IT(IT)   ((((IT) & 0xFFE0FFE0) == 0) && ((IT) != 0))
#define IS_QSPI_CLEAR_IT(IT)   ((((IT) & 0xFFE4FFE4) == 0) && ((IT) != 0))
/**
  * @}
  */

/** @defgroup QSPI_FlagsDefinition
  * @{
  */
#define QSPI_FLAG_TO                  QUADSPI_SR_TOF
#define QSPI_FLAG_SM                  QUADSPI_SR_SMF
#define QSPI_FLAG_FT                  QUADSPI_SR_FTF
#define QSPI_FLAG_TC                  QUADSPI_SR_TCF
#define QSPI_FLAG_TE                  QUADSPI_SR_TEF
#define QSPI_FLAG_BUSY                QUADSPI_SR_BUSY
#define IS_QSPI_GET_FLAG(FLAG)   (((FLAG) == QSPI_FLAG_TO) || ((FLAG) == QSPI_FLAG_SM) || \
                                  ((FLAG) == QSPI_FLAG_FT) || ((FLAG) == QSPI_FLAG_TC) || \
                                  ((FLAG) == QSPI_FLAG_TE) || ((FLAG) == QSPI_FLAG_BUSY))
#define IS_QSPI_CLEAR_FLAG(FLAG)  (((FLAG) == QSPI_FLAG_TO) || ((FLAG) == QSPI_FLAG_SM) || \
                                   ((FLAG) == QSPI_FLAG_TC) ||  ((FLAG) == QSPI_FLAG_TE))

/**
  * @}
  */

/** @defgroup QSPI_Polling_Match_Mode
  * @{
  */
#define QSPI_PMM_AND                 ((uint32_t)0x00000000)
#define QSPI_PMM_OR                  ((uint32_t)QUADSPI_CR_PMM)
#define IS_QSPI_PMM(PMM)      (((PMM) == QSPI_PMM_AND) || ((PMM) == QSPI_PMM_OR))
/**
  * @}
  */

/** @defgroup QSPI_Polling_Interval
  * @{
  */
#define IS_QSPI_PIR(PIR)                 ((PIR) <= QUADSPI_PIR_INTERVAL)
/**
  * @}
  */

/** @defgroup QSPI_Timeout
  * @{
  */
#define IS_QSPI_TIMEOUT(TIMEOUT)         ((TIMEOUT) <= QUADSPI_LPTR_TIMEOUT)
/**
  * @}
  */

/** @defgroup QSPI_DummyCycle
  * @{
  */
#define IS_QSPI_DCY(DCY)                 ((DCY) <= 0x1F)
/**
  * @}
  */

/** @defgroup QSPI_FIFOThreshold
  * @{
  */
#define IS_QSPI_FIFOTHRESHOLD(FIFOTHRESHOLD)        ((FIFOTHRESHOLD) <= 0x0F)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* 初始化和配置功能 *********************************/
void QSPI_DeInit(void); // 将 QSPI 外设寄存器取消初始化为其默认复位值。
void QSPI_Init(QSPI_InitTypeDef* QSPI_InitStruct); // 根据 QSPI_InitStruct 中指定的参数初始化 QSPI 外设。
void QSPI_StructInit(QSPI_InitTypeDef* QSPI_InitStruct); // 用其默认值填充每个 QSPI_InitStruct 成员。
void QSPI_ComConfig_Init(QSPI_ComConfig_InitTypeDef* QSPI_ComConfig_InitStruct); // 根据 QSPI_ComConfig_InitStruct 中指定的参数初始化 QSPI CCR。
void QSPI_ComConfig_StructInit(QSPI_ComConfig_InitTypeDef* QSPI_ComConfig_InitStruct); // 用其默认值填充每个 QSPI_ComConfig_InitStruct 成员。
void QSPI_Cmd(FunctionalState NewState); // 启用或禁用 QSPI 外设。
void QSPI_AutoPollingMode_Config(uint32_t QSPI_Match, uint32_t QSPI_Mask, uint32_t QSPI_Match_Mode);  // 配置 QSPI 自动轮询模式。
void QSPI_AutoPollingMode_SetInterval(uint32_t QSPI_Interval); // 设置自动轮询阶段两次读取之间的 CLK 周期数。
void QSPI_MemoryMappedMode_SetTimeout(uint32_t QSPI_Timeout); // 设置内存映射模式下的超时值
void QSPI_SetAddress(uint32_t QSPI_Address); // 设置地址的值
void QSPI_SetAlternateByte(uint32_t QSPI_AlternateByte); // 设置备用字节的值
void QSPI_SetFIFOThreshold(uint32_t QSPI_FIFOThreshold); // 设置 FIFO 阈值
void QSPI_SetDataLength(uint32_t QSPI_DataLength); // 设置要传输的字节数
void QSPI_TimeoutCounterCmd(FunctionalState NewState); // 启用或禁用超时计数器。
void QSPI_AutoPollingModeStopCmd(FunctionalState NewState); // 发生匹配时启用或禁用自动轮询模式停止。
void QSPI_AbortRequest(void); // 中止正在进行的命令序列。
void QSPI_DualFlashMode_Cmd(FunctionalState NewState); // 启用或禁用 QSPI 双闪存模式。

/* 数据传输功能 ***************************************************/
void     QSPI_SendData8(uint8_t Data); // 通过 QSPI 外设传输 8 位数据。
void     QSPI_SendData16(uint16_t Data); // 通过 QSPI 外设传输 16 位数据。
void     QSPI_SendData32(uint32_t Data); // 通过 QSPI 外设传输 32 位数据。
uint8_t  QSPI_ReceiveData8(void); // 返回 QSPI 外设最近接收到的 8 位数据。
uint16_t QSPI_ReceiveData16(void); // 返回 QSPI 外设最近接收到的 16 位数据。
uint32_t QSPI_ReceiveData32(void); // 返回 QSPI 外设最近接收到的 32 位数据。

/* DMA传输管理功能 *****************************************/
void QSPI_DMACmd(FunctionalState NewState); // 启用或禁用间接模式的 DMA。

/* 中断和标志管理功能 **********************************/
void       QSPI_ITConfig(uint32_t QSPI_IT, FunctionalState NewState); // 启用或禁用指定的 QSPI 中断。
uint32_t   QSPI_GetFIFOLevel(void); // 返回当前 QSPI FIFO 填充级别。
FlagStatus QSPI_GetFlagStatus(uint32_t QSPI_FLAG); // 检查是否设置了指定的 QSPI 标志。
void       QSPI_ClearFlag(uint32_t QSPI_FLAG); // 清除 QSPI 标志。
ITStatus   QSPI_GetITStatus(uint32_t QSPI_IT); // 检查指定的 QSPI 中断是否发生。
void       QSPI_ClearITPendingBit(uint32_t QSPI_IT); // 清除 QSPI 的中断挂起位。
uint32_t   QSPI_GetFMode(void); // 返回 QSPI 功能模式。

#endif /* STM32F412xG || STM32F413_423xx || STM32F446xx || STM32F469_479xx */
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4XX_QUADSPI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
