/**
  ******************************************************************************
  * 文件:    stm32f4xx_fsmc.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 FSMC 固件库的所有功能原型.
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
#ifndef __STM32F4xx_FSMC_H
#define __STM32F4xx_FSMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup FSMC
  */

/* Exported types ------------------------------------------------------------*/

/**
  * 简介:  NOR/SRAM Bank 的时序参数
  */
typedef struct {
    uint32_t FSMC_AddressSetupTime;       /*!< 定义 HCLK 周期数以配置地址设置时间的持续时间。
                                              此参数可以是 0 到 0xF 之间的值。
                                              @note 此参数不适用于同步 NOR 闪存。 */

    uint32_t FSMC_AddressHoldTime;        /*!< 定义 HCLK 周期数以配置地址保持时间的持续时间。
                                              此参数可以是 0 到 0xF 之间的值。
                                              @note 此参数不适用于同步 NOR 闪存。*/

    uint32_t FSMC_DataSetupTime;          /*!< 定义 HCLK 周期数以配置数据建立时间的持续时间。
                                              此参数可以是 0 到 0xFF 之间的值。
                                              @note 此参数用于 SRAM、ROM 和异步多路复用 NOR 闪存。 */

    uint32_t FSMC_BusTurnAroundDuration;  /*!< 定义 HCLK 周期数以配置总线周转的持续时间。
                                              此参数可以是 0 到 0xF 之间的值。
                                              @note 此参数仅用于多路复用的 NOR 闪存。*/

    uint32_t FSMC_CLKDivision;            /*!< 定义 CLK 时钟输出信号的周期，以 HCLK 周期数表示。
                                              此参数可以是 1 到 0xF 之间的值。
                                              @note 此参数不用于异步 NOR Flash、SRAM 或 ROM 访问。 */

    uint32_t FSMC_DataLatency;            /*!< 定义在获取第一个数据之前向内存发出的内存时钟周期数。
                                              参数值取决于内存类型，如下所示:
                                               - 如果是 CRAM，它必须设置为 0
                                               - 不关心异步 NOR、SRAM 或 ROM 访问
                                               - 在同步突发模式启用的 NOR 闪存中，它可能假定一个介于 0 和 0xF 之间的值 */

    uint32_t FSMC_AccessMode;             /*!< 指定异步访问模式。
                                              此参数可以是 @ref FSMC_Access_Mode 的值 */
} FSMC_NORSRAMTimingInitTypeDef;

/**
  * 简介:  FSMC NOR/SRAM Init 结构定义
  */
typedef struct {
    uint32_t FSMC_Bank;                /*!< 指定将使用的 NOR/SRAM 存储区。
                                           该参数可以是 @ref FSMC_NORSRAM_Bank 的值 */

    uint32_t FSMC_DataAddressMux;      /*!< 指定地址和数据值是否在数据总线上复用。
                                           该参数可以是 @ref FSMC_Data_Address_Bus_Multiplexing 的值 */

    uint32_t FSMC_MemoryType;          /*!< 指定连接到相应存储库的外部存储器的类型。
                                           该参数可以是 @ref FSMC_Memory_Type 的值 */

    uint32_t FSMC_MemoryDataWidth;     /*!< 指定外部存储设备宽度。
                                           该参数可以是 @ref FSMC_Data_Width 的值 */

    uint32_t FSMC_BurstAccessMode;     /*!< 启用或禁用 Flash 存储器的突发访问模式，仅对同步突发 Flash 存储器有效。
                                           该参数可以是 @ref FSMC_Burst_Access_Mode 的值 */

    uint32_t FSMC_AsynchronousWait;     /*!< 在异步传输期间启用或禁用等待信号，仅对异步闪存有效。
                                           该参数可以是 @ref FSMC_AsynchronousWait 的值 */

    uint32_t FSMC_WaitSignalPolarity;  /*!< 指定等待信号极性，仅在突发模式下访问 Flash 时有效。
                                           此参数可以是 @ref FSMC_Wait_Signal_Polarity 的值 */

    uint32_t FSMC_WrapMode;            /*!< 启用或禁用 Flash 存储器的 Wrapped Burst 访问模式，仅在以 Burst 模式访问 Flash 存储器时有效。
                                           该参数可以是 @ref FSMC_Wrap_Mode 的值 */

    uint32_t FSMC_WaitSignalActive;    /*!< 指定等待信号是在等待状态前一个时钟周期还是在等待状态期间由存储器置位，仅在以突发模式访问存储器时有效。
                                           该参数可以是 @ref FSMC_Wait_Timing 的值 */

    uint32_t FSMC_WriteOperation;      /*!< 启用或禁用 FSMC 在选定存储区中的写操作。
                                           此参数可以是 @ref FSMC_Write_Operation 的值 */

    uint32_t FSMC_WaitSignal;          /*!< 通过等待信号启用或禁用等待状态插入，对突发模式下的闪存访问有效。
                                           此参数可以是 @ref FSMC_Wait_Signal 的值 */

    uint32_t FSMC_ExtendedMode;        /*!< 启用或禁用扩展模式。
                                           此参数可以是 @ref FSMC_Extended_Mode 的值 */

    uint32_t FSMC_WriteBurst;          /*!< 启用或禁用写入突发操作。
                                           此参数可以是 @ref FSMC_Write_Burst 的值 */

    FSMC_NORSRAMTimingInitTypeDef* FSMC_ReadWriteTimingStruct; /*!< 如果不使用扩展模式，则用于写入和读取访问的时序参数*/

    FSMC_NORSRAMTimingInitTypeDef* FSMC_WriteTimingStruct;     /*!< 使用扩展模式时写访问的时序参数*/
} FSMC_NORSRAMInitTypeDef;

/**
  * 简介:  FSMC NAND 和 PCCARD Bank 的时序参数
  */
typedef struct {
    uint32_t FSMC_SetupTime;      /*!< 定义在命令断言之前设置地址的 HCLK 周期数，
									                以便对公共/属性或 I/O 存储空间进行 NAND
									                闪存读取或写入访问(取决于要配置的存储空间时序)。
                                     此参数可以是 0 到 0xFF 之间的值。*/

    uint32_t FSMC_WaitSetupTime;  /*!< 定义最小 HCLK 周期数，以断言 NAND 闪存读取或写入访问公共/属性或 I/O 存储空间的命令(取决于要配置的存储空间时序)。
                                      此参数可以是 0x00 到 0xFF 之间的数字 */

    uint32_t FSMC_HoldSetupTime;  /*!< 定义在命令取消断言后对公共/属性或 I/O 内存空间进行读取或写入访问(取决于要配置的内存空间时序)的 HCLK 时钟周期数 )。
                                      此参数可以是 0x00 到 0xFF 之间的数字 */

    uint32_t FSMC_HiZSetupTime;   /*!< 定义在对公共/属性或 I/O 存储器空间进行
									                NAND 闪存写入访问后数据总线保持在 HiZ 的
									                HCLK 时钟周期数(取决于要配置的存储器空间时序)。
                                      此参数可以是 0x00 到 0xFF 之间的数字 */
} FSMC_NAND_PCCARDTimingInitTypeDef;

/**
  * 简介:  FSMC NAND Init 结构定义
  */
typedef struct {
    uint32_t FSMC_Bank;              /*!< 指定将使用的 NAND 存储区。
                                       该参数可以是 @ref FSMC_NAND_Bank 的值 */

    uint32_t FSMC_Waitfeature;      /*!< 启用或禁用 NAND 存储库的等待功能。
                                        此参数可以是 @ref FSMC_Wait_feature 的任何值 */

    uint32_t FSMC_MemoryDataWidth;  /*!< 指定外部存储设备宽度。
                                        该参数可以是 @ref FSMC_Data_Width 的任何值 */

    uint32_t FSMC_ECC;              /*!< 启用或禁用 ECC 计算。
                                        该参数可以是 @ref FSMC_ECC 的任意值 */

    uint32_t FSMC_ECCPageSize;      /*!< 定义扩展 ECC 的页面大小。
                                        该参数可以是 @ref FSMC_ECC_Page_Size 的任意值 */

    uint32_t FSMC_TCLRSetupTime;    /*!< 定义 HCLK 周期数以配置 CLE 低和 RE 低之间的延迟。
                                        此参数可以是 0 到 0xFF 之间的值。 */

    uint32_t FSMC_TARSetupTime;     /*!< 定义 HCLK 周期数以配置 ALE 低电平和 RE 低电平之间的延迟。
                                        此参数可以是 0x0 和 0xFF 之间的数字 */

    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct;   /*!< FSMC 公共空间时序 */

    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct; /*!< FSMC 属性空间时序 */
} FSMC_NANDInitTypeDef;

/**
  * 简介:  FSMC PCCARD Init 结构定义
  */
typedef struct {
    uint32_t FSMC_Waitfeature;    /*!< 启用或禁用存储库的等待功能。
                                     此参数可以是 @ref FSMC_Wait_feature 的任何值 */

    uint32_t FSMC_TCLRSetupTime;  /*!< 定义 HCLK 周期数以配置 CLE 低和 RE 低之间的延迟。
                                      此参数可以是 0 到 0xFF 之间的值。 */

    uint32_t FSMC_TARSetupTime;   /*!< 定义 HCLK 周期数以配置 ALE 低电平和 RE 低电平之间的延迟。
                                      此参数可以是 0x0 和 0xFF 之间的数字 */


    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_CommonSpaceTimingStruct; /*!< FSMC 公共空间时序 */

    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_AttributeSpaceTimingStruct;  /*!< FSMC 属性空间时序 */

    FSMC_NAND_PCCARDTimingInitTypeDef*  FSMC_IOSpaceTimingStruct; /*!< FSMC IO 空间时序 */
} FSMC_PCCARDInitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup FSMC_Exported_Constants
  */

/** @defgroup FSMC_NORSRAM_Bank
  */
#define FSMC_Bank1_NORSRAM1                      ((uint32_t)0x00000000)
#define FSMC_Bank1_NORSRAM2                      ((uint32_t)0x00000002)
#define FSMC_Bank1_NORSRAM3                      ((uint32_t)0x00000004)
#define FSMC_Bank1_NORSRAM4                      ((uint32_t)0x00000006)

/** @defgroup FSMC_NAND_Bank
  */
#define FSMC_Bank2_NAND                          ((uint32_t)0x00000010)
#define FSMC_Bank3_NAND                          ((uint32_t)0x00000100)

/** @defgroup FSMC_PCCARD_Bank
  */
#define FSMC_Bank4_PCCARD                        ((uint32_t)0x00001000)
#define IS_FSMC_NORSRAM_BANK(BANK) (((BANK) == FSMC_Bank1_NORSRAM1) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM2) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM3) || \
                                    ((BANK) == FSMC_Bank1_NORSRAM4))

#define IS_FSMC_NAND_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                                 ((BANK) == FSMC_Bank3_NAND))

#define IS_FSMC_GETFLAG_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                                    ((BANK) == FSMC_Bank3_NAND) || \
                                    ((BANK) == FSMC_Bank4_PCCARD))

#define IS_FSMC_IT_BANK(BANK) (((BANK) == FSMC_Bank2_NAND) || \
                               ((BANK) == FSMC_Bank3_NAND) || \
                               ((BANK) == FSMC_Bank4_PCCARD))

/** @defgroup FSMC_NOR_SRAM_Controller
  */

/** @defgroup FSMC_Data_Address_Bus_Multiplexing
  */
#define FSMC_DataAddressMux_Disable                ((uint32_t)0x00000000)
#define FSMC_DataAddressMux_Enable                 ((uint32_t)0x00000002)
#define IS_FSMC_MUX(MUX) (((MUX) == FSMC_DataAddressMux_Disable) || \
                          ((MUX) == FSMC_DataAddressMux_Enable))

/** @defgroup FSMC_Memory_Type
  */
#define FSMC_MemoryType_SRAM                     ((uint32_t)0x00000000)
#define FSMC_MemoryType_PSRAM                    ((uint32_t)0x00000004)
#define FSMC_MemoryType_NOR                      ((uint32_t)0x00000008)
#define IS_FSMC_MEMORY(MEMORY) (((MEMORY) == FSMC_MemoryType_SRAM) || \
                                ((MEMORY) == FSMC_MemoryType_PSRAM)|| \
                                ((MEMORY) == FSMC_MemoryType_NOR))

/** @defgroup FSMC_Data_Width
  */
#define FSMC_MemoryDataWidth_8b                  ((uint32_t)0x00000000)
#define FSMC_MemoryDataWidth_16b                 ((uint32_t)0x00000010)
#define IS_FSMC_MEMORY_WIDTH(WIDTH) (((WIDTH) == FSMC_MemoryDataWidth_8b) || \
                                     ((WIDTH) == FSMC_MemoryDataWidth_16b))

/** @defgroup FSMC_Burst_Access_Mode
  */
#define FSMC_BurstAccessMode_Disable             ((uint32_t)0x00000000)
#define FSMC_BurstAccessMode_Enable              ((uint32_t)0x00000100)
#define IS_FSMC_BURSTMODE(STATE) (((STATE) == FSMC_BurstAccessMode_Disable) || \
                                  ((STATE) == FSMC_BurstAccessMode_Enable))

/** @defgroup FSMC_AsynchronousWait
  */
#define FSMC_AsynchronousWait_Disable            ((uint32_t)0x00000000)
#define FSMC_AsynchronousWait_Enable             ((uint32_t)0x00008000)
#define IS_FSMC_ASYNWAIT(STATE) (((STATE) == FSMC_AsynchronousWait_Disable) || \
                                 ((STATE) == FSMC_AsynchronousWait_Enable))

/** @defgroup FSMC_Wait_Signal_Polarity
  */
#define FSMC_WaitSignalPolarity_Low              ((uint32_t)0x00000000)
#define FSMC_WaitSignalPolarity_High             ((uint32_t)0x00000200)
#define IS_FSMC_WAIT_POLARITY(POLARITY) (((POLARITY) == FSMC_WaitSignalPolarity_Low) || \
        ((POLARITY) == FSMC_WaitSignalPolarity_High))

/** @defgroup FSMC_Wrap_Mode
  */
#define FSMC_WrapMode_Disable                    ((uint32_t)0x00000000)
#define FSMC_WrapMode_Enable                     ((uint32_t)0x00000400)
#define IS_FSMC_WRAP_MODE(MODE) (((MODE) == FSMC_WrapMode_Disable) || \
                                 ((MODE) == FSMC_WrapMode_Enable))

/** @defgroup FSMC_Wait_Timing
  */
#define FSMC_WaitSignalActive_BeforeWaitState    ((uint32_t)0x00000000)
#define FSMC_WaitSignalActive_DuringWaitState    ((uint32_t)0x00000800)
#define IS_FSMC_WAIT_SIGNAL_ACTIVE(ACTIVE) (((ACTIVE) == FSMC_WaitSignalActive_BeforeWaitState) || \
        ((ACTIVE) == FSMC_WaitSignalActive_DuringWaitState))

/** @defgroup FSMC_Write_Operation
  */
#define FSMC_WriteOperation_Disable                     ((uint32_t)0x00000000)
#define FSMC_WriteOperation_Enable                      ((uint32_t)0x00001000)
#define IS_FSMC_WRITE_OPERATION(OPERATION) (((OPERATION) == FSMC_WriteOperation_Disable) || \
        ((OPERATION) == FSMC_WriteOperation_Enable))

/** @defgroup FSMC_Wait_Signal
  */
#define FSMC_WaitSignal_Disable                  ((uint32_t)0x00000000)
#define FSMC_WaitSignal_Enable                   ((uint32_t)0x00002000)
#define IS_FSMC_WAITE_SIGNAL(SIGNAL) (((SIGNAL) == FSMC_WaitSignal_Disable) || \
                                      ((SIGNAL) == FSMC_WaitSignal_Enable))

/** @defgroup FSMC_Extended_Mode
  */
#define FSMC_ExtendedMode_Disable                ((uint32_t)0x00000000)
#define FSMC_ExtendedMode_Enable                 ((uint32_t)0x00004000)

#define IS_FSMC_EXTENDED_MODE(MODE) (((MODE) == FSMC_ExtendedMode_Disable) || \
                                     ((MODE) == FSMC_ExtendedMode_Enable))

/** @defgroup FSMC_Write_Burst
  */
#define FSMC_WriteBurst_Disable                  ((uint32_t)0x00000000)
#define FSMC_WriteBurst_Enable                   ((uint32_t)0x00080000)
#define IS_FSMC_WRITE_BURST(BURST) (((BURST) == FSMC_WriteBurst_Disable) || \
                                    ((BURST) == FSMC_WriteBurst_Enable))

/** @defgroup FSMC_Address_Setup_Time
  */
#define IS_FSMC_ADDRESS_SETUP_TIME(TIME) ((TIME) <= 0xF)

/** @defgroup FSMC_Address_Hold_Time
  */
#define IS_FSMC_ADDRESS_HOLD_TIME(TIME) ((TIME) <= 0xF)

/** @defgroup FSMC_Data_Setup_Time
  */
#define IS_FSMC_DATASETUP_TIME(TIME) (((TIME) > 0) && ((TIME) <= 0xFF))

/** @defgroup FSMC_Bus_Turn_around_Duration
  */
#define IS_FSMC_TURNAROUND_TIME(TIME) ((TIME) <= 0xF)

/** @defgroup FSMC_CLK_Division
  */
#define IS_FSMC_CLK_DIV(DIV) ((DIV) <= 0xF)

/** @defgroup FSMC_Data_Latency
  */
#define IS_FSMC_DATA_LATENCY(LATENCY) ((LATENCY) <= 0xF)

/** @defgroup FSMC_Access_Mode
  */
#define FSMC_AccessMode_A                        ((uint32_t)0x00000000)
#define FSMC_AccessMode_B                        ((uint32_t)0x10000000)
#define FSMC_AccessMode_C                        ((uint32_t)0x20000000)
#define FSMC_AccessMode_D                        ((uint32_t)0x30000000)
#define IS_FSMC_ACCESS_MODE(MODE) (((MODE) == FSMC_AccessMode_A) || \
                                   ((MODE) == FSMC_AccessMode_B) || \
                                   ((MODE) == FSMC_AccessMode_C) || \
                                   ((MODE) == FSMC_AccessMode_D))


/** @defgroup FSMC_NAND_PCCARD_Controller
  */

/** @defgroup FSMC_Wait_feature
  */
#define FSMC_Waitfeature_Disable                 ((uint32_t)0x00000000)
#define FSMC_Waitfeature_Enable                  ((uint32_t)0x00000002)
#define IS_FSMC_WAIT_FEATURE(FEATURE) (((FEATURE) == FSMC_Waitfeature_Disable) || \
                                       ((FEATURE) == FSMC_Waitfeature_Enable))


/** @defgroup FSMC_ECC
  */
#define FSMC_ECC_Disable                         ((uint32_t)0x00000000)
#define FSMC_ECC_Enable                          ((uint32_t)0x00000040)
#define IS_FSMC_ECC_STATE(STATE) (((STATE) == FSMC_ECC_Disable) || \
                                  ((STATE) == FSMC_ECC_Enable))

/** @defgroup FSMC_ECC_Page_Size
  */
#define FSMC_ECCPageSize_256Bytes                ((uint32_t)0x00000000)
#define FSMC_ECCPageSize_512Bytes                ((uint32_t)0x00020000)
#define FSMC_ECCPageSize_1024Bytes               ((uint32_t)0x00040000)
#define FSMC_ECCPageSize_2048Bytes               ((uint32_t)0x00060000)
#define FSMC_ECCPageSize_4096Bytes               ((uint32_t)0x00080000)
#define FSMC_ECCPageSize_8192Bytes               ((uint32_t)0x000A0000)
#define IS_FSMC_ECCPAGE_SIZE(SIZE) (((SIZE) == FSMC_ECCPageSize_256Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_512Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_1024Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_2048Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_4096Bytes) || \
                                    ((SIZE) == FSMC_ECCPageSize_8192Bytes))

/** @defgroup FSMC_TCLR_Setup_Time
  */
#define IS_FSMC_TCLR_TIME(TIME) ((TIME) <= 0xFF)

/** @defgroup FSMC_TAR_Setup_Time
  */
#define IS_FSMC_TAR_TIME(TIME) ((TIME) <= 0xFF)

/** @defgroup FSMC_Setup_Time
  */
#define IS_FSMC_SETUP_TIME(TIME) ((TIME) <= 0xFF)

/** @defgroup FSMC_Wait_Setup_Time
  */
#define IS_FSMC_WAIT_TIME(TIME) ((TIME) <= 0xFF)

/** @defgroup FSMC_Hold_Setup_Time
  */
#define IS_FSMC_HOLD_TIME(TIME) ((TIME) <= 0xFF)

/** @defgroup FSMC_HiZ_Setup_Time
  */
#define IS_FSMC_HIZ_TIME(TIME) ((TIME) <= 0xFF)

/** @defgroup FSMC_Interrupt_sources
  */
#define FSMC_IT_RisingEdge                       ((uint32_t)0x00000008)
#define FSMC_IT_Level                            ((uint32_t)0x00000010)
#define FSMC_IT_FallingEdge                      ((uint32_t)0x00000020)
#define IS_FSMC_IT(IT) ((((IT) & (uint32_t)0xFFFFFFC7) == 0x00000000) && ((IT) != 0x00000000))
#define IS_FSMC_GET_IT(IT) (((IT) == FSMC_IT_RisingEdge) || \
                            ((IT) == FSMC_IT_Level) || \
                            ((IT) == FSMC_IT_FallingEdge))

/** @defgroup FSMC_Flags
  */
#define FSMC_FLAG_RisingEdge                     ((uint32_t)0x00000001)
#define FSMC_FLAG_Level                          ((uint32_t)0x00000002)
#define FSMC_FLAG_FallingEdge                    ((uint32_t)0x00000004)
#define FSMC_FLAG_FEMPT                          ((uint32_t)0x00000040)
#define IS_FSMC_GET_FLAG(FLAG) (((FLAG) == FSMC_FLAG_RisingEdge) || \
                                ((FLAG) == FSMC_FLAG_Level) || \
                                ((FLAG) == FSMC_FLAG_FallingEdge) || \
                                ((FLAG) == FSMC_FLAG_FEMPT))

#define IS_FSMC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFF8) == 0x00000000) && ((FLAG) != 0x00000000))



/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* NOR/SRAM 控制器功能 **********************************************/
void FSMC_NORSRAMDeInit(uint32_t FSMC_Bank); // 将 FSMC NAND 存储体寄存器取消初始化为其默认重置值。
void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct); // 根据FSMC_NANDInitStruct 中指定的参数初始化 FSMC NAND 库。
void FSMC_NORSRAMStructInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct); // 用其默认值填充每个 FSMC_NANDInitStruct 成员。
void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState); // 启用或禁用指定的 NOR/SRAM 内存库。

/* NAND 控制器功能 **************************************************/
void FSMC_NANDDeInit(uint32_t FSMC_Bank); // 取消初始化 FSMC NOR/SRAM 组寄存器到其默认复位值。
void FSMC_NANDInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct); // 根据FSMC_NANDInitStruct 中指定的参数初始化 FSMC NAND 库。
void FSMC_NANDStructInit(FSMC_NANDInitTypeDef* FSMC_NANDInitStruct); // 用其默认值填充每个 FSMC_NANDInitStruct 成员。
void FSMC_NANDCmd(uint32_t FSMC_Bank, FunctionalState NewState); // 启用或禁用指定的 NAND 内存库。
void FSMC_NANDECCCmd(uint32_t FSMC_Bank, FunctionalState NewState); // 启用或禁用 FSMC NAND ECC 功能。
uint32_t FSMC_GetECC(uint32_t FSMC_Bank); // 返回纠错码寄存器值。

/* PCCARD 控制器功能 ************************************************/
void FSMC_PCCARDDeInit(void); // 取消初始化 FSMC PCCARD 银行寄存器到其默认重置值。
void FSMC_PCCARDInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct); // 根据FSMC_PCCARDInitStruct 中指定的参数初始化 FSMC PCCARD 库。
void FSMC_PCCARDStructInit(FSMC_PCCARDInitTypeDef* FSMC_PCCARDInitStruct); // 用每个 FSMC_PCCARDInitStruct 成员的默认值填充该成员。
void FSMC_PCCARDCmd(FunctionalState NewState); // 启用或禁用 PCCARD 存储体。

/* 中断和标志管理功能 **********************************/
void FSMC_ITConfig(uint32_t FSMC_Bank, uint32_t FSMC_IT, FunctionalState NewState); // 启用或禁用指定的 FSMC 中断。
FlagStatus FSMC_GetFlagStatus(uint32_t FSMC_Bank, uint32_t FSMC_FLAG); // 检查是否设置了指定的 FSMC 标志。
void FSMC_ClearFlag(uint32_t FSMC_Bank, uint32_t FSMC_FLAG); // 清除 FSMC 的挂起标志。
ITStatus FSMC_GetITStatus(uint32_t FSMC_Bank, uint32_t FSMC_IT); // 检查指定的 FSMC 中断是否发生。
void FSMC_ClearITPendingBit(uint32_t FSMC_Bank, uint32_t FSMC_IT); // 清除 FSMC 的中断挂起位。

#ifdef __cplusplus
}
#endif

#endif /*__STM32F4xx_FSMC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
