/**
  ******************************************************************************
  * 文件:    stm32f4xx_fmc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件包含 FMC 固件库的所有功能原型.
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
#ifndef __STM32F4xx_FMC_H
#define __STM32F4xx_FMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup FMC
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  NOR/SRAM Bank 的时序参数
  */
typedef struct {
    uint32_t FMC_AddressSetupTime;       /*!< 定义 HCLK 周期数以配置地址设置时间的持续时间。
                                            此参数可以是 0 到 15 之间的值。
                                            @note 此参数不适用于同步 NOR 闪存。 */

    uint32_t FMC_AddressHoldTime;        /*!< 定义 HCLK 周期数以配置地址保持时间的持续时间。
                                              此参数可以是 1 到 15 之间的值。
                                              @note 此参数不适用于同步 NOR 闪存。*/

    uint32_t FMC_DataSetupTime;          /*!< 定义 HCLK 周期数以配置数据建立时间的持续时间。
                                              此参数可以是 1 到 255 之间的值。
                                              @note 此参数用于 SRAM、ROM 和异步多路复用 NOR 闪存。 */

    uint32_t FMC_BusTurnAroundDuration;  /*!< 定义 HCLK 周期数以配置总线周转的持续时间。
                                              此参数可以是 0 到 15 之间的值。
                                              @note 此参数仅用于多路复用的 NOR 闪存。 */

    uint32_t FMC_CLKDivision;            /*!< 定义 CLK 时钟输出信号的周期，以 HCLK 周期数表示。
                                              此参数可以是 1 到 15 之间的值。
                                              @note 此参数不用于异步 NOR Flash、SRAM 或 ROM 访问。 */

    uint32_t FMC_DataLatency;            /*!< 定义在获取第一个数据之前向内存发出的内存时钟周期数。
                                              参数值取决于内存类型，如下所示:
                                               - 如果是 CRAM，它必须设置为 0
                                               - 不关心异步 NOR、SRAM 或 ROM 访问
                                               - 在同步突发模式启用的 NOR 闪存中，它可能假定一个介于 0 和 15 之间的值 */

    uint32_t FMC_AccessMode;             /*!< 指定异步访问模式。
                                              该参数可以是 @ref FMC_Access_Mode 的值 */
} FMC_NORSRAMTimingInitTypeDef;

/**
  * 简介:  FMC NOR/SRAM Init 结构定义
  */
typedef struct {
    uint32_t FMC_Bank;                /*!< 指定将使用的 NOR/SRAM 存储区。
                                           该参数可以是 @ref FMC_NORSRAM_Bank 的值 */

    uint32_t FMC_DataAddressMux;      /*!< 指定地址和数据值是否在数据总线上复用。
                                           该参数可以是 @ref FMC_Data_Address_Bus_Multiplexing 的值 */

    uint32_t FMC_MemoryType;          /*!< 指定连接到相应存储库的外部存储器的类型。
                                           该参数可以是 @ref FMC_Memory_Type 的值 */

    uint32_t FMC_MemoryDataWidth;     /*!< 指定外部存储设备宽度。
                                           该参数可以是 @ref FMC_NORSRAM_Data_Width 的值 */

    uint32_t FMC_BurstAccessMode;     /*!< 启用或禁用 Flash 存储器的突发访问模式，仅对同步突发 Flash 存储器有效。
                                           该参数可以是 @ref FMC_Burst_Access_Mode 的值 */

    uint32_t FMC_WaitSignalPolarity;  /*!< 指定等待信号极性，仅在突发模式下访问 Flash 时有效。
                                           此参数可以是 @ref FMC_Wait_Signal_Polarity 的值 */

    uint32_t FMC_WrapMode;            /*!< 启用或禁用 Flash 存储器的 Wrapped Burst 访问模式，仅在以 Burst 模式访问 Flash 存储器时有效。
                                           该参数可以是 @ref FMC_Wrap_Mode 的值 */

    uint32_t FMC_WaitSignalActive;    /*!< 指定等待信号是在等待状态前一个时钟周期还是在等待状态期间由存储器置位，仅在以突发模式访问存储器时有效。
                                           该参数可以是 @ref FMC_Wait_Timing 的值 */

    uint32_t FMC_WriteOperation;      /*!< 启用或禁用 FMC 在所选存储区中的写操作。
                                           该参数可以是 @ref FMC_Write_Operation 的值 */

    uint32_t FMC_WaitSignal;          /*!< 通过等待信号启用或禁用等待状态插入，对突发模式下的闪存访问有效。
                                           此参数可以是 @ref FMC_Wait_Signal 的值 */

    uint32_t FMC_ExtendedMode;        /*!< 启用或禁用扩展模式。
                                           该参数可以是 @ref FMC_Extended_Mode 的值 */

    uint32_t FMC_AsynchronousWait;     /*!< 在异步传输期间启用或禁用等待信号，仅对异步闪存有效。
                                           该参数可以是 @ref FMC_AsynchronousWait 的值 */

    uint32_t FMC_WriteBurst;          /*!< 启用或禁用写入突发操作。
                                           该参数可以是 @ref FMC_Write_Burst 的值 */

    uint32_t FMC_ContinousClock;       /*!< 启用或禁用 FMC 时钟输出到外部存储设备。
                                           该参数仅通过 FMC_BCR1 寄存器启用，与 FMC_BCR2..4 寄存器无关。
                                           该参数可以是 @ref FMC_Continous_Clock 的值 */

    FMC_NORSRAMTimingInitTypeDef* FMC_ReadWriteTimingStruct; /*!< 如果不使用扩展模式，则用于写入和读取访问的时序参数*/

    FMC_NORSRAMTimingInitTypeDef* FMC_WriteTimingStruct;     /*!< 使用扩展模式时写访问的时序参数*/
} FMC_NORSRAMInitTypeDef;

/**
  * 简介:  FMC NAND 和 PCCARD Bank 的时序参数
  */
typedef struct {
    uint32_t FMC_SetupTime;      /*!< 定义在命令断言之前设置地址的 HCLK 周期数，
									以便对公共/属性或 I/O 内存空间进行 NAND 闪存读取或写入访问(取决于要配置的内存空间时序)。
                                    此参数可以是 0 到 255 之间的值。*/

    uint32_t FMC_WaitSetupTime;  /*!< 定义最小的 HCLK 周期数，以断言 NAND 闪存读取或写入访问公共/属性或 I/O 内存空间的命令(取决于要配置的内存空间时序)。
                                    此参数可以是 0 到 255 之间的数字 */

    uint32_t FMC_HoldSetupTime;  /*!< 定义 HCLK 时钟周期数以在命令取消断言后保持地址(和用于写访问的数据)，
									以便对公共/属性或 I/O 存储空间进行 NAND
									闪存读取或写入访问(取决于要存储的存储空间时序) 配置)。
                                    此参数可以是 0 到 255 之间的数字 */

    uint32_t FMC_HiZSetupTime;   /*!< 定义在对公共/属性或 I/O 存储器空间进行 NAND
									闪存写入访问后数据总线保持在 HiZ 的 HCLK 时钟周期数(取决于要配置的存储器空间时序)。
                                    此参数可以是 0 到 255 之间的数字 */
} FMC_NAND_PCCARDTimingInitTypeDef;

/**
  * 简介:  FMC NAND Init结构定义
  */
typedef struct {
    uint32_t FMC_Bank;              /*!< 指定将使用的 NAND 存储区。
                                       该参数可以是 @ref FMC_NAND_Bank 的值 */

    uint32_t FMC_Waitfeature;      /*!< 启用或禁用 NAND 存储库的等待功能。
                                        该参数可以是 @ref FMC_Wait_feature 的任意值 */

    uint32_t FMC_MemoryDataWidth;  /*!< 指定外部存储设备宽度。
                                        该参数可以是 @ref FMC_NAND_Data_Width 的任意值 */

    uint32_t FMC_ECC;              /*!< 启用或禁用 ECC 计算。
                                        该参数可以是 @ref FMC_ECC 的任意值 */

    uint32_t FMC_ECCPageSize;      /*!< 定义扩展 ECC 的页面大小。
                                        该参数可以是 @ref FMC_ECC_Page_Size 的任意值 */

    uint32_t FMC_TCLRSetupTime;    /*!< 定义 HCLK 周期数以配置 CLE 低和 RE 低之间的延迟。
                                        此参数可以是 0 到 255 之间的值。 */

    uint32_t FMC_TARSetupTime;     /*!< 定义 HCLK 周期数以配置 ALE 低电平和 RE 低电平之间的延迟。
                                        此参数可以是 0 到 255 之间的数字 */

    FMC_NAND_PCCARDTimingInitTypeDef*  FMC_CommonSpaceTimingStruct;   /*!< FMC 公共空间时序 */

    FMC_NAND_PCCARDTimingInitTypeDef*  FMC_AttributeSpaceTimingStruct; /*!< FMC 属性空间时序 */
} FMC_NANDInitTypeDef;

/**
  * 简介:  FMC PCCARD Init 结构定义
  */
typedef struct {
    uint32_t FMC_Waitfeature;    /*!< 启用或禁用存储库的等待功能。
                                    该参数可以是 @ref FMC_Wait_feature 的任意值 */

    uint32_t FMC_TCLRSetupTime;  /*!< 定义 HCLK 周期数以配置 CLE 低和 RE 低之间的延迟。
                                    此参数可以是 0 到 255 之间的值。 */

    uint32_t FMC_TARSetupTime;   /*!< 定义 HCLK 周期数以配置 ALE 低电平和 RE 低电平之间的延迟。
                                    此参数可以是 0 到 255 之间的数字 */


    FMC_NAND_PCCARDTimingInitTypeDef*  FMC_CommonSpaceTimingStruct; /*!< FMC 公共空间时序 */

    FMC_NAND_PCCARDTimingInitTypeDef*  FMC_AttributeSpaceTimingStruct;  /*!< FMC 属性空间时序 */

    FMC_NAND_PCCARDTimingInitTypeDef*  FMC_IOSpaceTimingStruct; /*!< FMC IO 空间时序 */
} FMC_PCCARDInitTypeDef;

/**
  * 简介:  FMC SDRAM Bank 的时序参数
  */
typedef struct {
    uint32_t FMC_LoadToActiveDelay;      /*!< 以内存时钟周期数定义加载模式寄存器命令与活动或刷新命令之间的延迟。
                                            此参数可以是 1 到 16 之间的值。 */

    uint32_t FMC_ExitSelfRefreshDelay;   /*!< 以内存时钟周期数定义从释放自刷新命令到发出激活命令的延迟。
                                            此参数可以是 1 到 16 之间的值。 */

    uint32_t FMC_SelfRefreshTime;        /*!< 以内存时钟周期数定义最小自刷新周期。
                                            此参数可以是 1 到 16 之间的值。 */

    uint32_t FMC_RowCycleDelay;          /*!< 定义刷新命令和激活命令之间的延迟以及两个连续刷新命令之间的延迟(以内存时钟周期数计)。
                                            此参数可以是 1 到 16 之间的值。 */

    uint32_t FMC_WriteRecoveryTime;      /*!< 以内存时钟周期数定义写恢复时间。
                                            此参数可以是 1 到 16 之间的值。 */

    uint32_t FMC_RPDelay;                /*!< 以内存时钟周期数定义预充电命令与其他命令之间的延迟。
                                            此参数可以是 1 到 16 之间的值。 */

    uint32_t FMC_RCDDelay;               /*!< 以内存时钟周期数定义激活命令和读/写命令之间的延迟。
                                             此参数可以是 1 到 16 之间的值。 */
} FMC_SDRAMTimingInitTypeDef;

/**
  * 简介:  FMC SDRAM Bank 的命令参数
  */


typedef struct {
    uint32_t FMC_CommandMode;            /*!< 定义发给 SDRAM 设备的命令。
                                            此参数可以是 @ref FMC_Command_Mode 的值。 */

    uint32_t FMC_CommandTarget;          /*!< 定义将向哪个银行(1 或 2)发出命令。
                                            此参数可以是 @ref FMC_Command_Target 的值。 */

    uint32_t FMC_AutoRefreshNumber;      /*!< 定义在自动刷新模式下发出的连续自动刷新命令的数量。
                                            此参数可以是 1 到 16 之间的值。 */

    uint32_t FMC_ModeRegisterDefinition; /*!< 定义 SDRAM 模式寄存器内容 */
} FMC_SDRAMCommandTypeDef;

/**
  * 简介:  FMC SDRAM Init 结构定义
  */
typedef struct {
    uint32_t FMC_Bank;                   /*!< 指定将使用的 SDRAM 内存条。
											该参数可以是 @ref FMC_SDRAM_Bank 的值 */

    uint32_t FMC_ColumnBitsNumber;       /*!< 定义列地址的位数。
											此参数可以是 @ref FMC_ColumnBits_Number 的值。 */

    uint32_t FMC_RowBitsNumber;          /*!< 定义列地址的位数。
											此参数可以是 @ref FMC_RowBits_Number 的值。 */

    uint32_t FMC_SDMemoryDataWidth;        /*!< 定义存储设备宽度。
											此参数可以是 @ref FMC_SDMemory_Data_Width 的值。 */

    uint32_t FMC_InternalBankNumber;     /*!< 定义列地址的位数。
                                            该参数可以是 @ref FMC_InternalBank_Number。 */

    uint32_t FMC_CASLatency;             /*!< 以内存时钟周期数定义 SDRAM CAS 延迟。
                                            该参数可以是 @ref FMC_CAS_Latency 的值。 */

    uint32_t FMC_WriteProtection;        /*!< 使 SDRAM bank 能够在写模式下被访问。
                                            此参数可以是 @ref FMC_Write_Protection 的值。 */

    uint32_t FMC_SDClockPeriod;          /*!< 为两个 SDRAM Bank 定义 SDRAM 时钟周期，它们允许在更改频率之前禁用时钟。
                                            该参数可以是 @ref FMC_SDClock_Period 的值。 */

    uint32_t FMC_ReadBurst;              /*!< 该位使 SDRAM 控制器能够在 CAS 延迟期间预测下一个读取命令，并将数据存储在读取 FIFO 中。
                                            此参数可以是 @ref FMC_Read_Burst 的值。 */

    uint32_t FMC_ReadPipeDelay;          /*!< 定义读取数据路径上的系统时钟周期延迟。
                                            此参数可以是 @ref FMC_ReadPipe_Delay 的值。 */

    FMC_SDRAMTimingInitTypeDef* FMC_SDRAMTimingStruct;   /*!< 写入和读取访问的时序参数*/
} FMC_SDRAMInitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup FMC_Exported_Constants
  */

/** @defgroup FMC_NORSRAM_Bank
  */
#define FMC_Bank1_NORSRAM1                      ((uint32_t)0x00000000)
#define FMC_Bank1_NORSRAM2                      ((uint32_t)0x00000002)
#define FMC_Bank1_NORSRAM3                      ((uint32_t)0x00000004)
#define FMC_Bank1_NORSRAM4                      ((uint32_t)0x00000006)

#define IS_FMC_NORSRAM_BANK(BANK) (((BANK) == FMC_Bank1_NORSRAM1) || \
                                   ((BANK) == FMC_Bank1_NORSRAM2) || \
                                   ((BANK) == FMC_Bank1_NORSRAM3) || \
                                   ((BANK) == FMC_Bank1_NORSRAM4))

/** @defgroup FMC_NAND_Bank
  */
#define FMC_Bank2_NAND                          ((uint32_t)0x00000010)
#define FMC_Bank3_NAND                          ((uint32_t)0x00000100)

#define IS_FMC_NAND_BANK(BANK) (((BANK) == FMC_Bank2_NAND) || \
                                ((BANK) == FMC_Bank3_NAND))

/** @defgroup FMC_PCCARD_Bank
  */
#define FMC_Bank4_PCCARD                        ((uint32_t)0x00001000)

/** @defgroup FMC_SDRAM_Bank
  */
#define FMC_Bank1_SDRAM                    ((uint32_t)0x00000000)
#define FMC_Bank2_SDRAM                    ((uint32_t)0x00000001)

#define IS_FMC_SDRAM_BANK(BANK) (((BANK) == FMC_Bank1_SDRAM) || \
                                 ((BANK) == FMC_Bank2_SDRAM))



/** @defgroup FMC_NOR_SRAM_Controller
  */

/** @defgroup FMC_Data_Address_Bus_Multiplexing
  */
#define FMC_DataAddressMux_Disable                ((uint32_t)0x00000000)
#define FMC_DataAddressMux_Enable                 ((uint32_t)0x00000002)

#define IS_FMC_MUX(MUX) (((MUX) == FMC_DataAddressMux_Disable) || \
                         ((MUX) == FMC_DataAddressMux_Enable))

/** @defgroup FMC_Memory_Type
  */
#define FMC_MemoryType_SRAM                     ((uint32_t)0x00000000)
#define FMC_MemoryType_PSRAM                    ((uint32_t)0x00000004)
#define FMC_MemoryType_NOR                      ((uint32_t)0x00000008)

#define IS_FMC_MEMORY(MEMORY) (((MEMORY) == FMC_MemoryType_SRAM) || \
                               ((MEMORY) == FMC_MemoryType_PSRAM)|| \
                               ((MEMORY) == FMC_MemoryType_NOR))

/** @defgroup FMC_NORSRAM_Data_Width
  */
#define FMC_NORSRAM_MemoryDataWidth_8b                  ((uint32_t)0x00000000)
#define FMC_NORSRAM_MemoryDataWidth_16b                 ((uint32_t)0x00000010)
#define FMC_NORSRAM_MemoryDataWidth_32b                 ((uint32_t)0x00000020)

#define IS_FMC_NORSRAM_MEMORY_WIDTH(WIDTH) (((WIDTH) == FMC_NORSRAM_MemoryDataWidth_8b)  || \
        ((WIDTH) == FMC_NORSRAM_MemoryDataWidth_16b) || \
        ((WIDTH) == FMC_NORSRAM_MemoryDataWidth_32b))

/** @defgroup FMC_Burst_Access_Mode
  */
#define FMC_BurstAccessMode_Disable             ((uint32_t)0x00000000)
#define FMC_BurstAccessMode_Enable              ((uint32_t)0x00000100)

#define IS_FMC_BURSTMODE(STATE) (((STATE) == FMC_BurstAccessMode_Disable) || \
                                 ((STATE) == FMC_BurstAccessMode_Enable))

/** @defgroup FMC_AsynchronousWait
  */
#define FMC_AsynchronousWait_Disable            ((uint32_t)0x00000000)
#define FMC_AsynchronousWait_Enable             ((uint32_t)0x00008000)

#define IS_FMC_ASYNWAIT(STATE) (((STATE) == FMC_AsynchronousWait_Disable) || \
                                ((STATE) == FMC_AsynchronousWait_Enable))

/** @defgroup FMC_Wait_Signal_Polarity
  */
#define FMC_WaitSignalPolarity_Low              ((uint32_t)0x00000000)
#define FMC_WaitSignalPolarity_High             ((uint32_t)0x00000200)

#define IS_FMC_WAIT_POLARITY(POLARITY) (((POLARITY) == FMC_WaitSignalPolarity_Low) || \
                                        ((POLARITY) == FMC_WaitSignalPolarity_High))

/** @defgroup FMC_Wrap_Mode
  */
#define FMC_WrapMode_Disable                    ((uint32_t)0x00000000)
#define FMC_WrapMode_Enable                     ((uint32_t)0x00000400)

#define IS_FMC_WRAP_MODE(MODE) (((MODE) == FMC_WrapMode_Disable) || \
                                ((MODE) == FMC_WrapMode_Enable))

/** @defgroup FMC_Wait_Timing
  */
#define FMC_WaitSignalActive_BeforeWaitState    ((uint32_t)0x00000000)
#define FMC_WaitSignalActive_DuringWaitState    ((uint32_t)0x00000800)

#define IS_FMC_WAIT_SIGNAL_ACTIVE(ACTIVE) (((ACTIVE) == FMC_WaitSignalActive_BeforeWaitState) || \
        ((ACTIVE) == FMC_WaitSignalActive_DuringWaitState))

/** @defgroup FMC_Write_Operation
  */
#define FMC_WriteOperation_Disable                     ((uint32_t)0x00000000)
#define FMC_WriteOperation_Enable                      ((uint32_t)0x00001000)

#define IS_FMC_WRITE_OPERATION(OPERATION) (((OPERATION) == FMC_WriteOperation_Disable) || \
        ((OPERATION) == FMC_WriteOperation_Enable))

/** @defgroup FMC_Wait_Signal
  */
#define FMC_WaitSignal_Disable                  ((uint32_t)0x00000000)
#define FMC_WaitSignal_Enable                   ((uint32_t)0x00002000)

#define IS_FMC_WAITE_SIGNAL(SIGNAL) (((SIGNAL) == FMC_WaitSignal_Disable) || \
                                     ((SIGNAL) == FMC_WaitSignal_Enable))

/** @defgroup FMC_Extended_Mode
  */
#define FMC_ExtendedMode_Disable                ((uint32_t)0x00000000)
#define FMC_ExtendedMode_Enable                 ((uint32_t)0x00004000)

#define IS_FMC_EXTENDED_MODE(MODE) (((MODE) == FMC_ExtendedMode_Disable) || \
                                    ((MODE) == FMC_ExtendedMode_Enable))

/** @defgroup FMC_Write_Burst
  */
#define FMC_WriteBurst_Disable                  ((uint32_t)0x00000000)
#define FMC_WriteBurst_Enable                   ((uint32_t)0x00080000)

#define IS_FMC_WRITE_BURST(BURST) (((BURST) == FMC_WriteBurst_Disable) || \
                                   ((BURST) == FMC_WriteBurst_Enable))

/** @defgroup FMC_Continous_Clock
  */
#define FMC_CClock_SyncOnly                     ((uint32_t)0x00000000)
#define FMC_CClock_SyncAsync                    ((uint32_t)0x00100000)

#define IS_FMC_CONTINOUS_CLOCK(CCLOCK) (((CCLOCK) == FMC_CClock_SyncOnly) || \
                                        ((CCLOCK) == FMC_CClock_SyncAsync))

/** @defgroup FMC_Address_Setup_Time
  */
#define IS_FMC_ADDRESS_SETUP_TIME(TIME) ((TIME) <= 15)

/** @defgroup FMC_Address_Hold_Time
  */
#define IS_FMC_ADDRESS_HOLD_TIME(TIME) (((TIME) > 0) && ((TIME) <= 15))

/** @defgroup FMC_Data_Setup_Time
  */
#define IS_FMC_DATASETUP_TIME(TIME) (((TIME) > 0) && ((TIME) <= 255))

/** @defgroup FMC_Bus_Turn_around_Duration
  */
#define IS_FMC_TURNAROUND_TIME(TIME) ((TIME) <= 15)

/** @defgroup FMC_CLK_Division
  */
#define IS_FMC_CLK_DIV(DIV) (((DIV) > 0) && ((DIV) <= 15))

/** @defgroup FMC_Data_Latency
  */
#define IS_FMC_DATA_LATENCY(LATENCY) ((LATENCY) <= 15)

/** @defgroup FMC_Access_Mode
  */
#define FMC_AccessMode_A                        ((uint32_t)0x00000000)
#define FMC_AccessMode_B                        ((uint32_t)0x10000000)
#define FMC_AccessMode_C                        ((uint32_t)0x20000000)
#define FMC_AccessMode_D                        ((uint32_t)0x30000000)

#define IS_FMC_ACCESS_MODE(MODE) (((MODE) == FMC_AccessMode_A)  || \
                                  ((MODE) == FMC_AccessMode_B) || \
                                  ((MODE) == FMC_AccessMode_C) || \
                                  ((MODE) == FMC_AccessMode_D))


/** @defgroup FMC_NAND_PCCARD_Controller
  */

/** @defgroup FMC_Wait_feature
  */
#define FMC_Waitfeature_Disable                 ((uint32_t)0x00000000)
#define FMC_Waitfeature_Enable                  ((uint32_t)0x00000002)

#define IS_FMC_WAIT_FEATURE(FEATURE) (((FEATURE) == FMC_Waitfeature_Disable) || \
                                      ((FEATURE) == FMC_Waitfeature_Enable))

/** @defgroup FMC_NAND_Data_Width
  */
#define FMC_NAND_MemoryDataWidth_8b             ((uint32_t)0x00000000)
#define FMC_NAND_MemoryDataWidth_16b            ((uint32_t)0x00000010)

#define IS_FMC_NAND_MEMORY_WIDTH(WIDTH) (((WIDTH) == FMC_NAND_MemoryDataWidth_8b) || \
        ((WIDTH) == FMC_NAND_MemoryDataWidth_16b))

/** @defgroup FMC_ECC
  */
#define FMC_ECC_Disable                         ((uint32_t)0x00000000)
#define FMC_ECC_Enable                          ((uint32_t)0x00000040)

#define IS_FMC_ECC_STATE(STATE) (((STATE) == FMC_ECC_Disable) || \
                                 ((STATE) == FMC_ECC_Enable))

/** @defgroup FMC_ECC_Page_Size
  */
#define FMC_ECCPageSize_256Bytes                ((uint32_t)0x00000000)
#define FMC_ECCPageSize_512Bytes                ((uint32_t)0x00020000)
#define FMC_ECCPageSize_1024Bytes               ((uint32_t)0x00040000)
#define FMC_ECCPageSize_2048Bytes               ((uint32_t)0x00060000)
#define FMC_ECCPageSize_4096Bytes               ((uint32_t)0x00080000)
#define FMC_ECCPageSize_8192Bytes               ((uint32_t)0x000A0000)

#define IS_FMC_ECCPAGE_SIZE(SIZE) (((SIZE) == FMC_ECCPageSize_256Bytes)   || \
                                   ((SIZE) == FMC_ECCPageSize_512Bytes)  || \
                                   ((SIZE) == FMC_ECCPageSize_1024Bytes) || \
                                   ((SIZE) == FMC_ECCPageSize_2048Bytes) || \
                                   ((SIZE) == FMC_ECCPageSize_4096Bytes) || \
                                   ((SIZE) == FMC_ECCPageSize_8192Bytes))

/** @defgroup FMC_TCLR_Setup_Time
  */
#define IS_FMC_TCLR_TIME(TIME) ((TIME) <= 255)

/** @defgroup FMC_TAR_Setup_Time
  */
#define IS_FMC_TAR_TIME(TIME) ((TIME) <= 255)

/** @defgroup FMC_Setup_Time
  */
#define IS_FMC_SETUP_TIME(TIME) ((TIME) <= 255)

/** @defgroup FMC_Wait_Setup_Time
  */
#define IS_FMC_WAIT_TIME(TIME) ((TIME) <= 255)

/** @defgroup FMC_Hold_Setup_Time
  */
#define IS_FMC_HOLD_TIME(TIME) ((TIME) <= 255)

/** @defgroup FMC_HiZ_Setup_Time
  */
#define IS_FMC_HIZ_TIME(TIME) ((TIME) <= 255)



/** @defgroup FMC_NOR_SRAM_Controller
  */

/** @defgroup FMC_ColumnBits_Number
  */
#define FMC_ColumnBits_Number_8b           ((uint32_t)0x00000000)
#define FMC_ColumnBits_Number_9b           ((uint32_t)0x00000001)
#define FMC_ColumnBits_Number_10b          ((uint32_t)0x00000002)
#define FMC_ColumnBits_Number_11b          ((uint32_t)0x00000003)

#define IS_FMC_COLUMNBITS_NUMBER(COLUMN) (((COLUMN) == FMC_ColumnBits_Number_8b)  || \
        ((COLUMN) == FMC_ColumnBits_Number_9b)  || \
        ((COLUMN) == FMC_ColumnBits_Number_10b) || \
        ((COLUMN) == FMC_ColumnBits_Number_11b))


/** @defgroup FMC_RowBits_Number
  */
#define FMC_RowBits_Number_11b             ((uint32_t)0x00000000)
#define FMC_RowBits_Number_12b             ((uint32_t)0x00000004)
#define FMC_RowBits_Number_13b             ((uint32_t)0x00000008)

#define IS_FMC_ROWBITS_NUMBER(ROW) (((ROW) == FMC_RowBits_Number_11b) || \
                                    ((ROW) == FMC_RowBits_Number_12b) || \
                                    ((ROW) == FMC_RowBits_Number_13b))


/** @defgroup FMC_SDMemory_Data_Width
  */
#define FMC_SDMemory_Width_8b                ((uint32_t)0x00000000)
#define FMC_SDMemory_Width_16b               ((uint32_t)0x00000010)
#define FMC_SDMemory_Width_32b               ((uint32_t)0x00000020)

#define IS_FMC_SDMEMORY_WIDTH(WIDTH) (((WIDTH) == FMC_SDMemory_Width_8b)  || \
                                      ((WIDTH) == FMC_SDMemory_Width_16b) || \
                                      ((WIDTH) == FMC_SDMemory_Width_32b))


/** @defgroup FMC_InternalBank_Number
  */
#define FMC_InternalBank_Number_2          ((uint32_t)0x00000000)
#define FMC_InternalBank_Number_4          ((uint32_t)0x00000040)

#define IS_FMC_INTERNALBANK_NUMBER(NUMBER) (((NUMBER) == FMC_InternalBank_Number_2) || \
        ((NUMBER) == FMC_InternalBank_Number_4))



/** @defgroup FMC_CAS_Latency
  */
#define FMC_CAS_Latency_1                  ((uint32_t)0x00000080)
#define FMC_CAS_Latency_2                  ((uint32_t)0x00000100)
#define FMC_CAS_Latency_3                  ((uint32_t)0x00000180)

#define IS_FMC_CAS_LATENCY(LATENCY) (((LATENCY) == FMC_CAS_Latency_1) || \
                                     ((LATENCY) == FMC_CAS_Latency_2) || \
                                     ((LATENCY) == FMC_CAS_Latency_3))


/** @defgroup FMC_Write_Protection
  */
#define FMC_Write_Protection_Disable       ((uint32_t)0x00000000)
#define FMC_Write_Protection_Enable        ((uint32_t)0x00000200)

#define IS_FMC_WRITE_PROTECTION(WRITE) (((WRITE) == FMC_Write_Protection_Disable) || \
                                        ((WRITE) == FMC_Write_Protection_Enable))



/** @defgroup FMC_SDClock_Period
  */
#define FMC_SDClock_Disable                ((uint32_t)0x00000000)
#define FMC_SDClock_Period_2               ((uint32_t)0x00000800)
#define FMC_SDClock_Period_3               ((uint32_t)0x00000C00)

#define IS_FMC_SDCLOCK_PERIOD(PERIOD) (((PERIOD) == FMC_SDClock_Disable) || \
                                       ((PERIOD) == FMC_SDClock_Period_2) || \
                                       ((PERIOD) == FMC_SDClock_Period_3))


/** @defgroup FMC_Read_Burst
  */
#define FMC_Read_Burst_Disable             ((uint32_t)0x00000000)
#define FMC_Read_Burst_Enable              ((uint32_t)0x00001000)

#define IS_FMC_READ_BURST(RBURST) (((RBURST) == FMC_Read_Burst_Disable) || \
                                   ((RBURST) == FMC_Read_Burst_Enable))


/** @defgroup FMC_ReadPipe_Delay
  */
#define FMC_ReadPipe_Delay_0               ((uint32_t)0x00000000)
#define FMC_ReadPipe_Delay_1               ((uint32_t)0x00002000)
#define FMC_ReadPipe_Delay_2               ((uint32_t)0x00004000)

#define IS_FMC_READPIPE_DELAY(DELAY) (((DELAY) == FMC_ReadPipe_Delay_0) || \
                                      ((DELAY) == FMC_ReadPipe_Delay_1) || \
                                      ((DELAY) == FMC_ReadPipe_Delay_2))


/** @defgroup FMC_LoadToActive_Delay
  */
#define IS_FMC_LOADTOACTIVE_DELAY(DELAY) (((DELAY) > 0) && ((DELAY) <= 16))

/** @defgroup FMC_ExitSelfRefresh_Delay
  */
#define IS_FMC_EXITSELFREFRESH_DELAY(DELAY) (((DELAY) > 0) && ((DELAY) <= 16))

/** @defgroup FMC_SelfRefresh_Time
  */
#define IS_FMC_SELFREFRESH_TIME(TIME) (((TIME) > 0) && ((TIME) <= 16))

/** @defgroup FMC_RowCycle_Delay
  */
#define IS_FMC_ROWCYCLE_DELAY(DELAY) (((DELAY) > 0) && ((DELAY) <= 16))

/** @defgroup FMC_Write_Recovery_Time
  */
#define IS_FMC_WRITE_RECOVERY_TIME(TIME) (((TIME) > 0) && ((TIME) <= 16))

/** @defgroup FMC_RP_Delay
  */
#define IS_FMC_RP_DELAY(DELAY) (((DELAY) > 0) && ((DELAY) <= 16))

/** @defgroup FMC_RCD_Delay
  */
#define IS_FMC_RCD_DELAY(DELAY) (((DELAY) > 0) && ((DELAY) <= 16))


/** @defgroup FMC_Command_Mode
  */
#define FMC_Command_Mode_normal            ((uint32_t)0x00000000)
#define FMC_Command_Mode_CLK_Enabled       ((uint32_t)0x00000001)
#define FMC_Command_Mode_PALL              ((uint32_t)0x00000002)
#define FMC_Command_Mode_AutoRefresh       ((uint32_t)0x00000003)
#define FMC_Command_Mode_LoadMode          ((uint32_t)0x00000004)
#define FMC_Command_Mode_Selfrefresh       ((uint32_t)0x00000005)
#define FMC_Command_Mode_PowerDown         ((uint32_t)0x00000006)

#define IS_FMC_COMMAND_MODE(COMMAND) (((COMMAND) == FMC_Command_Mode_normal)      || \
                                      ((COMMAND) == FMC_Command_Mode_CLK_Enabled) || \
                                      ((COMMAND) == FMC_Command_Mode_PALL)        || \
                                      ((COMMAND) == FMC_Command_Mode_AutoRefresh) || \
                                      ((COMMAND) == FMC_Command_Mode_LoadMode)    || \
                                      ((COMMAND) == FMC_Command_Mode_Selfrefresh) || \
                                      ((COMMAND) == FMC_Command_Mode_PowerDown))


/** @defgroup FMC_Command_Target
  */
#define FMC_Command_Target_bank2           ((uint32_t)0x00000008)
#define FMC_Command_Target_bank1           ((uint32_t)0x00000010)
#define FMC_Command_Target_bank1_2         ((uint32_t)0x00000018)

#define IS_FMC_COMMAND_TARGET(TARGET) (((TARGET) == FMC_Command_Target_bank1) || \
                                       ((TARGET) == FMC_Command_Target_bank2) || \
                                       ((TARGET) == FMC_Command_Target_bank1_2))


/** @defgroup FMC_AutoRefresh_Number
  */
#define IS_FMC_AUTOREFRESH_NUMBER(NUMBER) (((NUMBER) > 0) && ((NUMBER) <= 16))


/** @defgroup FMC_ModeRegister_Definition
  */
#define IS_FMC_MODE_REGISTER(CONTENT) ((CONTENT) <= 8191)



/** @defgroup FMC_Mode_Status
  */
#define FMC_NormalMode_Status                     ((uint32_t)0x00000000)
#define FMC_SelfRefreshMode_Status                FMC_SDSR_MODES1_0
#define FMC_PowerDownMode_Status                  FMC_SDSR_MODES1_1

#define IS_FMC_MODE_STATUS(STATUS) (((STATUS) == FMC_NormalMode_Status)       || \
                                    ((STATUS) == FMC_SelfRefreshMode_Status)  || \
                                    ((STATUS) == FMC_PowerDownMode_Status))




/** @defgroup FMC_Interrupt_sources
  */
#define FMC_IT_RisingEdge                       ((uint32_t)0x00000008)
#define FMC_IT_Level                            ((uint32_t)0x00000010)
#define FMC_IT_FallingEdge                      ((uint32_t)0x00000020)
#define FMC_IT_Refresh                          ((uint32_t)0x00004000)

#define IS_FMC_IT(IT) ((((IT) & (uint32_t)0xFFFFBFC7) == 0x00000000) && ((IT) != 0x00000000))
#define IS_FMC_GET_IT(IT) (((IT) == FMC_IT_RisingEdge)  || \
                           ((IT) == FMC_IT_Level)       || \
                           ((IT) == FMC_IT_FallingEdge) || \
                           ((IT) == FMC_IT_Refresh))

#define IS_FMC_IT_BANK(BANK) (((BANK) == FMC_Bank2_NAND)   || \
                              ((BANK) == FMC_Bank3_NAND)   || \
                              ((BANK) == FMC_Bank4_PCCARD) || \
                              ((BANK) == FMC_Bank1_SDRAM)  || \
                              ((BANK) == FMC_Bank2_SDRAM))

/** @defgroup FMC_Flags
  */
#define FMC_FLAG_RisingEdge                     ((uint32_t)0x00000001)
#define FMC_FLAG_Level                          ((uint32_t)0x00000002)
#define FMC_FLAG_FallingEdge                    ((uint32_t)0x00000004)
#define FMC_FLAG_FEMPT                          ((uint32_t)0x00000040)
#define FMC_FLAG_Refresh                        FMC_SDSR_RE
#define FMC_FLAG_Busy                           FMC_SDSR_BUSY

#define IS_FMC_GET_FLAG(FLAG) (((FLAG) == FMC_FLAG_RisingEdge)       || \
                               ((FLAG) == FMC_FLAG_Level)            || \
                               ((FLAG) == FMC_FLAG_FallingEdge)      || \
                               ((FLAG) == FMC_FLAG_FEMPT)            || \
                               ((FLAG) == FMC_FLAG_Refresh)          || \
                               ((FLAG) == FMC_SDSR_BUSY))

#define IS_FMC_GETFLAG_BANK(BANK) (((BANK) == FMC_Bank2_NAND)    || \
                                   ((BANK) == FMC_Bank3_NAND)    || \
                                   ((BANK) == FMC_Bank4_PCCARD)  || \
                                   ((BANK) == FMC_Bank1_SDRAM)   || \
                                   ((BANK) == FMC_Bank2_SDRAM)   || \
                                   ((BANK) == (FMC_Bank1_SDRAM | FMC_Bank2_SDRAM)))

#define IS_FMC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFF8) == 0x00000000) && ((FLAG) != 0x00000000))



/** @defgroup FMC_Refresh_count
  */
#define IS_FMC_REFRESH_COUNT(COUNT) ((COUNT) <= 8191)




/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* NOR/SRAM 控制器功能 **********************************************/
void FMC_NORSRAMDeInit(uint32_t FMC_Bank); // 将 FMC NOR/SRAM 组寄存器取消初始化为其默认复位值。
void FMC_NORSRAMInit(FMC_NORSRAMInitTypeDef* FMC_NORSRAMInitStruct); // 根据 FMC_NORSRAMInitStruct 中指定的参数初始化 FMC NOR/SRAM Bank。
void FMC_NORSRAMStructInit(FMC_NORSRAMInitTypeDef* FMC_NORSRAMInitStruct); // 用默认值填充每个 FMC_NORSRAMInitStruct 成员。
void FMC_NORSRAMCmd(uint32_t FMC_Bank, FunctionalState NewState); // 启用或禁用指定的 NOR/SRAM 存储库。

/* NAND 控制器功能 **************************************************/
void     FMC_NANDDeInit(uint32_t FMC_Bank); // 将 FMC NAND Banks 寄存器取消初始化为其默认复位值。
void     FMC_NANDInit(FMC_NANDInitTypeDef* FMC_NANDInitStruct); // 根据 FMC_NANDInitStruct 中指定的参数初始化 FMC NAND Bank。
void     FMC_NANDStructInit(FMC_NANDInitTypeDef* FMC_NANDInitStruct); // 用默认值填充每个 FMC_NANDInitStruct 成员
void     FMC_NANDCmd(uint32_t FMC_Bank, FunctionalState NewState); // 启用或禁用指定的 NAND Memory Bank。
void     FMC_NANDECCCmd(uint32_t FMC_Bank, FunctionalState NewState); // 启用或禁用 FMC NAND ECC 功能。
uint32_t FMC_GetECC(uint32_t FMC_Bank); // 返回纠错码寄存器值。

/* PCCARD 控制器功能 ************************************************/
void FMC_PCCARDDeInit(void); // 将 FMC PCCARD 组寄存器取消初始化为其默认复位值。
void FMC_PCCARDInit(FMC_PCCARDInitTypeDef* FMC_PCCARDInitStruct); // 根据 FMC_PCCARDInitStruct 中指定的参数初始化 FMC PCCARD Bank。
void FMC_PCCARDStructInit(FMC_PCCARDInitTypeDef* FMC_PCCARDInitStruct); // 用默认值填充每个 FMC_PCCARDInitStruct 成员。
void FMC_PCCARDCmd(FunctionalState NewState); // 启用或禁用 PCCARD 存储库。

/* SDRAM 控制器功能 ************************************************/
void     FMC_SDRAMDeInit(uint32_t FMC_Bank); // 将 FMC SDRAM 组寄存器取消初始化为其默认复位值。
void     FMC_SDRAMInit(FMC_SDRAMInitTypeDef* FMC_SDRAMInitStruct); // 根据 FMC_SDRAMInitStruct 中指定的参数初始化 FMC SDRAM Bank
void     FMC_SDRAMStructInit(FMC_SDRAMInitTypeDef* FMC_SDRAMInitStruct); // 用默认值填充每个 FMC_SDRAMInitStruct 成员。
void     FMC_SDRAMCmdConfig(FMC_SDRAMCommandTypeDef* FMC_SDRAMCommandStruct); // 配置访问设备时发出的 SDRAM 内存命令。
uint32_t FMC_GetModeStatus(uint32_t SDRAM_Bank); // 返回指示的 FMC SDRAM 组模式状态。
void     FMC_SetRefreshCount(uint32_t FMC_Count); // 定义 SDRAM 内存刷新率
void     FMC_SetAutoRefresh_Number(uint32_t FMC_Number); // 设置连续 SDRAM 内存自动刷新命令的数量。
void     FMC_SDRAMWriteProtectionConfig(uint32_t SDRAM_Bank, FunctionalState NewState); // 启用或禁用对指定 FMC SDRAM Bank 的写保护。

/* 中断和标志管理功能 **********************************/
void       FMC_ITConfig(uint32_t FMC_Bank, uint32_t FMC_IT, FunctionalState NewState); // 启用或禁用指定的 FMC 中断。
FlagStatus FMC_GetFlagStatus(uint32_t FMC_Bank, uint32_t FMC_FLAG); // 检查是否设置了指定的 FMC 标志。
void       FMC_ClearFlag(uint32_t FMC_Bank, uint32_t FMC_FLAG); // 清除 FMC 的挂起标志。
ITStatus   FMC_GetITStatus(uint32_t FMC_Bank, uint32_t FMC_IT); // 检查是否发生了指定的 FMC 中断。
void       FMC_ClearITPendingBit(uint32_t FMC_Bank, uint32_t FMC_IT); // 清除 FMC 的中断挂起位

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_FMC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
