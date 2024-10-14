/**
  ******************************************************************************
  * 文件:    stm32f4xx_flash.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，以管理FLASH外设设备的以下功能:
  *            + FLASH 接口配置
  *            + FLASH编程
  *            + 选项字节编程
  *            + 中断和标志管理
  *
 @verbatim
 ===============================================================================
                        ##### 如何使用这个驱动程序 #####
 ===============================================================================
    [..]
      此驱动程序提供配置和编程所有 STM32F4xx 设备的闪存的功能。这些功能分为4组:

      (#) FLASH 接口配置功能: 该组包括以下功能的管理:
          (++) 设置延迟
          (++) 启用/禁用预取缓冲区
          (++) 启用/禁用指令缓存和数据缓存
          (++) 重置指令缓存和数据缓存

      (#) 闪存编程功能:该组包括擦除和编程主存储器所需的所有功能:
          (++) 锁定和解锁闪存界面
          (++) 擦除功能: 擦除扇区，擦除所有扇区
          (++) 程序功能: 字节、半字、字和双字

      (#) 选项字节编程功能: 该组包括管理选项字节所需的所有功能:
          (++) 设置/重置写保护
          (++) 设置读取保护级别
          (++) 设置BOR级别
          (++) 对用户选项字节进行编程
          (++) 启动选项字节加载程序

      (#) 中断和标记管理函数: 该组包括所有必要的功能:
          (++) 启用/禁用闪存中断源
          (++) 获取标志状态
          (++) 清除标志
          (++) 获取 FLASH 操作状态
          (++) 等待最后一次闪存操作
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
#include "stm32f4xx_flash.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup FLASH
  * 简介: FLASH 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/
#define SECTOR_MASK               ((uint32_t)0xFFFFFF07)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup FLASH_Private_Functions
  */

/** @defgroup FLASH_Group1 FLASH 接口配置功能
  *  简介   FLASH 接口配置功能
 *

@verbatim
 ===============================================================================
              ##### FLASH 接口配置功能 #####
 ===============================================================================
    [..]
      该组包括以下函数:
      (+) void FLASH_SetLatency(uint32_t FLASH_Latency)
          要从闪存正确读取数据，必须根据 CPU时钟频率(HCLK)和
          设备电源电压正确编程等待状态(LATENCY)的数量。
    [..]
      对于 STM32F405xx/07xx 和 STM32P415xx/17xx 设备
 +---------------------------------------------------------------------------------------+
 | Latency       |                HCLK时钟频率 (MHz)                                     |
 |               |-----------------------------------------------------------------------|
 |               |    电压范围      |    电压范围     | voltage range   | voltage range   |
 |               | 2.7 V - 3.6 V   |  2.4 V - 2.7 V  | 2.1 V - 2.4 V   | 1.8 V - 2.1 V   |
 |---------------|-----------------|-----------------|-----------------|-----------------|
 |0WS(1CPU cycle)|0 < HCLK <= 30   | 0 < HCLK <= 24  |0 < HCLK <= 22   |0 < HCLK <= 20   |
 |---------------|-----------------|-----------------|-----------------|-----------------|
 |1WS(2CPU cycle)|30 < HCLK <= 60  |24 < HCLK <= 48  |22 < HCLK <= 44  |20 < HCLK <= 40  |
 |---------------|-----------------|-----------------|-----------------|-----------------|
 |2WS(3CPU cycle)|60 < HCLK <= 90  |48 < HCLK <= 72  |44 < HCLK <= 66  |40 < HCLK <= 60  |
 |---------------|-----------------|-----------------|-----------------|-----------------|
 |3WS(4CPU cycle)|90 < HCLK <= 120 |72 < HCLK <= 96  |66 < HCLK <= 88  |60 < HCLK <= 80  |
 |---------------|-----------------|-----------------|-----------------|-----------------|
 |4WS(5CPU cycle)|120< HCLK <= 150 |96 < HCLK <= 120 |88 < HCLK <= 110 |80 < HCLK <= 100 |
 |---------------|-----------------|-----------------|-----------------|-----------------|
 |5WS(6CPU cycle)|150< HCLK <= 168 |120< HCLK <= 144 |110 < HCLK <= 132|100 < HCLK <= 120|
 |---------------|-----------------|-----------------|-----------------|-----------------|
 |6WS(7CPU cycle)|      NA         |144< HCLK <= 168 |132 < HCLK <= 154|120 < HCLK <= 140|
 |---------------|-----------------|-----------------|-----------------|-----------------|
 |7WS(8CPU cycle)|      NA         |      NA         |154 < HCLK <= 168|140 < HCLK <= 160|
 +---------------|-----------------|-----------------|-----------------|-----------------+

    [..]
      For STM32F42xxx/43xxx devices
 +-------------------------------------------------------------------------------------+
 | Latency       |                HCLK clock frequency (MHz)                           |
 |               |---------------------------------------------------------------------|
 |               |    电压范围    |    电压范围    | voltage range   | voltage range   |
 |               | 2.7 V - 3.6 V  | 2.4 V - 2.7 V  | 2.1 V - 2.4 V   | 1.8 V - 2.1 V   |
 |---------------|----------------|----------------|-----------------|-----------------|
 |0WS(1CPU cycle)|0 < HCLK <= 30  |0 < HCLK <= 24  |0 < HCLK <= 22   |0 < HCLK <= 20   |
 |---------------|----------------|----------------|-----------------|-----------------|
 |1WS(2CPU cycle)|30 < HCLK <= 60 |24 < HCLK <= 48 |22 < HCLK <= 44  |20 < HCLK <= 40  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |2WS(3CPU cycle)|60 < HCLK <= 90 |48 < HCLK <= 72 |44 < HCLK <= 66  |40 < HCLK <= 60  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |3WS(4CPU cycle)|90 < HCLK <= 120|72 < HCLK <= 96 |66 < HCLK <= 88  |60 < HCLK <= 80  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |4WS(5CPU cycle)|120< HCLK <= 150|96 < HCLK <= 120|88 < HCLK <= 110 |80 < HCLK <= 100 |
 |---------------|----------------|----------------|-----------------|-----------------|
 |5WS(6CPU cycle)|120< HCLK <= 180|120< HCLK <= 144|110 < HCLK <= 132|100 < HCLK <= 120|
 |---------------|----------------|----------------|-----------------|-----------------|
 |6WS(7CPU cycle)|      NA        |144< HCLK <= 168|132 < HCLK <= 154|120 < HCLK <= 140|
 |---------------|----------------|----------------|-----------------|-----------------|
 |7WS(8CPU cycle)|      NA        |168< HCLK <= 180|154 < HCLK <= 176|140 < HCLK <= 160|
 |---------------|----------------|----------------|-----------------|-----------------|
 |8WS(9CPU cycle)|      NA        |      NA        |176 < HCLK <= 180|160 < HCLK <= 168|
 +-------------------------------------------------------------------------------------+

    [..]
    For STM32F401x devices
 +-------------------------------------------------------------------------------------+
 | Latency       |                HCLK clock frequency (MHz)                           |
 |               |---------------------------------------------------------------------|
 |               |    电压范围    |    电压范围    | voltage range   | voltage range   |
 |               | 2.7 V - 3.6 V  | 2.4 V - 2.7 V  | 2.1 V - 2.4 V   | 1.8 V - 2.1 V   |
 |---------------|----------------|----------------|-----------------|-----------------|
 |0WS(1CPU cycle)|0 < HCLK <= 30  |0 < HCLK <= 24  |0 < HCLK <= 22   |0 < HCLK <= 20   |
 |---------------|----------------|----------------|-----------------|-----------------|
 |1WS(2CPU cycle)|30 < HCLK <= 60 |24 < HCLK <= 48 |22 < HCLK <= 44  |20 < HCLK <= 40  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |2WS(3CPU cycle)|60 < HCLK <= 84 |48 < HCLK <= 72 |44 < HCLK <= 66  |40 < HCLK <= 60  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |3WS(4CPU cycle)|      NA        |72 < HCLK <= 84 |66 < HCLK <= 84  |60 < HCLK <= 80  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |4WS(5CPU cycle)|      NA        |      NA        |      NA         |80 < HCLK <= 84  |
 +-------------------------------------------------------------------------------------+

    [..]
    For STM32F410xx/STM32F411xE devices
 +-------------------------------------------------------------------------------------+
 | Latency       |                HCLK clock frequency (MHz)                           |
 |               |---------------------------------------------------------------------|
 |               |    电压范围    |    电压范围    | voltage range   | voltage range   |
 |               | 2.7 V - 3.6 V  | 2.4 V - 2.7 V  | 2.1 V - 2.4 V   | 1.8 V - 2.1 V   |
 |---------------|----------------|----------------|-----------------|-----------------|
 |0WS(1CPU cycle)|0 < HCLK <= 30  |0 < HCLK <= 24  |0 < HCLK <= 18   |0 < HCLK <= 16   |
 |---------------|----------------|----------------|-----------------|-----------------|
 |1WS(2CPU cycle)|30 < HCLK <= 64 |24 < HCLK <= 48 |18 < HCLK <= 36  |16 < HCLK <= 32  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |2WS(3CPU cycle)|64 < HCLK <= 90 |48 < HCLK <= 72 |36 < HCLK <= 54  |32 < HCLK <= 48  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |3WS(4CPU cycle)|90 < HCLK <= 100|72 < HCLK <= 96 |54 < HCLK <= 72  |48 < HCLK <= 64  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |4WS(5CPU cycle)|      NA        |96 < HCLK <= 100|72 < HCLK <= 90  |64 < HCLK <= 80  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |5WS(6CPU cycle)|      NA        |       NA       |90 < HCLK <= 100 |80 < HCLK <= 96  |
 |---------------|----------------|----------------|-----------------|-----------------|
 |6WS(7CPU cycle)|      NA        |       NA       |        NA       |96 < HCLK <= 100 |
 +-------------------------------------------------------------------------------------+

 [..]
 +-------------------------------------------------------------------------------------------------------------------+
 |               |    电压范围    |    电压范围    | voltage range   | voltage range   | voltage range 2.7 V - 3.6 V |
 |               | 2.7 V - 3.6 V  | 2.4 V - 2.7 V  | 2.1 V - 2.4 V   | 1.8 V - 2.1 V   | with External Vpp = 9V      |
 |---------------|----------------|----------------|-----------------|-----------------|-----------------------------|
 |Max Parallelism|      x32       |               x16                |       x8        |          x64                |
 |---------------|----------------|----------------|-----------------|-----------------|-----------------------------|
 |PSIZE[1:0]     |      10        |               01                 |       00        |           11                |
 +-------------------------------------------------------------------------------------------------------------------+

      -@- On STM32F405xx/407xx and STM32F415xx/417xx devices:
           (++) when VOS = '0' Scale 2 mode, 最大值 fHCLK = 144MHz.
           (++) when VOS = '1' Scale 1 mode, 最大值 fHCLK = 168MHz.
          [..]
          On STM32F42xxx/43xxx devices:
           (++) when VOS[1:0] = '0x01' Scale 3 mode, fHCLK的最大值为120MHz。
           (++) when VOS[1:0] = '0x10' Scale 2 mode, 如果OverDrive OFF，fHCLK的最大值为144MHz，如果OverDrive ON，则为168MHz。
           (++) when VOS[1:0] = '0x11' Scale 1 mode, 如果OverDrive OFF，fHCLK的最大值为168MHz，如果OverDrive ON，则为180MHz。
          [..]
          On STM32F401x devices:
           (++) when VOS[1:0] = '0x01' Scale 3 mode, fHCLK的最大值为60MHz。
           (++) when VOS[1:0] = '0x10' Scale 2 mode, fHCLK的最大值为84MHz。
          [..]
          On STM32F410xx/STM32F411xE devices:
           (++) when VOS[1:0] = '0x01' Scale 3 mode, fHCLK的最大值为64MHz。
           (++) when VOS[1:0] = '0x10' Scale 2 mode, fHCLK的最大值为84MHz。
           (++) when VOS[1:0] = '0x11' Scale 1 mode, fHCLK的最大值为100MHz。

        有关更多详细信息，请参阅产品数据表
           您可以使用 PWR_MainRegulatorModeConfig() 函数来控制VOS位。

      (+) void FLASH_PrefetchBufferCmd(FunctionalState NewState)
      (+) void FLASH_InstructionCacheCmd(FunctionalState NewState)
      (+) void FLASH_DataCacheCmd(FunctionalState NewState)
      (+) void FLASH_InstructionCacheReset(void)
      (+) void FLASH_DataCacheReset(void)

    [..]
      这些功能不需要解锁顺序。

@endverbatim
  */

/**
  * 简介:  设置代码延迟值。
  * 
  * 参数:  FLASH_Latency: 指定FLASH Latency值。
  *          此参数可以是以下值之一:
  *            @arg FLASH_Latency_0: FLASH Zero 延迟周期
  *            @arg FLASH_Latency_1: FLASH One 延迟周期
  *            @arg FLASH_Latency_2: FLASH Two 延迟周期
  *            @arg FLASH_Latency_3: FLASH Three 延迟周期
  *            @arg FLASH_Latency_4: FLASH Four 延迟周期
  *            @arg FLASH_Latency_5: FLASH Five 延迟周期
  *            @arg FLASH_Latency_6: FLASH Six 延迟周期
  *            @arg FLASH_Latency_7: FLASH Seven 延迟周期
  *            @arg FLASH_Latency_8: FLASH Eight 延迟周期
  *            @arg FLASH_Latency_9: FLASH Nine 延迟周期
  *            @arg FLASH_Latency_10: FLASH Teen 延迟周期
  *            @arg FLASH_Latency_11: FLASH Eleven 延迟周期
  *            @arg FLASH_Latency_12: FLASH Twelve 延迟周期
  *            @arg FLASH_Latency_13: FLASH Thirteen 延迟周期
  *            @arg FLASH_Latency_14: FLASH Fourteen 延迟周期
  *            @arg FLASH_Latency_15: FLASH 十五个延迟周期
  *
  * 注意: 对于 STM32F405xx/407xx、STM32F2F415xx/417xx、ST M32F401xx/411xE/STM32F 412xG 和
  *       STM32V413_423xx 设备，此参数可以是介于 FLASH_Latency_0 和 FLASH_Latency_7 之间的值。
  *
  * 注意: 对于 STM32F42xxx/43xxx 设备，此参数可以是介于 FLASH_Latency_0 和 FLASH_Latency_15 之间的值。
  *
  * 返回值: 无
  */
void FLASH_SetLatency(uint32_t FLASH_Latency) {
    /* 检查参数 */
    assert_param(IS_FLASH_LATENCY(FLASH_Latency));

    /* Perform Byte access to FLASH_ACR[8:0] to set the Latency 值 */
    *(__IO uint8_t *)ACR_BYTE0_ADDRESS = (uint8_t)FLASH_Latency;
}

/**
  * 简介:  启用或禁用预取缓冲区。
  * 
  * 参数:  NewState: 预取缓冲区的新状态。
  *          此参数可以是: ENABLE or DISABLE.
  * 
  * 返回值: 无
  */
void FLASH_PrefetchBufferCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* 启用或禁用预取缓冲区 */
    if(NewState != DISABLE) {
        FLASH->ACR |= FLASH_ACR_PRFTEN;
    } else {
        FLASH->ACR &= (~FLASH_ACR_PRFTEN);
    }
}

/**
  * 简介:  启用或禁用指令缓存功能。
  * 
  * 参数:  NewState: 指令缓存的新状态。
  *          此参数可以是: ENABLE or DISABLE.
  * 
  * 返回值: 无
  */
void FLASH_InstructionCacheCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE) {
        FLASH->ACR |= FLASH_ACR_ICEN;
    } else {
        FLASH->ACR &= (~FLASH_ACR_ICEN);
    }
}

/**
  * 简介:  启用或禁用数据缓存函数。
  * 
  * 参数:  NewState: 数据缓存的新状态。
  *          此参数可以是: ENABLE or DISABLE.
  * 
  * 返回值: 无
  */
void FLASH_DataCacheCmd(FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE) {
        FLASH->ACR |= FLASH_ACR_DCEN;
    } else {
        FLASH->ACR &= (~FLASH_ACR_DCEN);
    }
}

/**
  * 简介:  重置指令缓存。
  * 
  * 注意:   仅当"指令缓存"被禁用时，才能使用此函数。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void FLASH_InstructionCacheReset(void) {
    FLASH->ACR |= FLASH_ACR_ICRST;
}

/**
  * 简介:  重置数据缓存。
  * 注意:   只有在禁用数据缓存时才能使用此功能。
  * 参数:  无
  * 返回值: 无
  */
void FLASH_DataCacheReset(void) {
    FLASH->ACR |= FLASH_ACR_DCRST;
}


/** @defgroup FLASH_Group2 闪存编程功能
 *  简介   闪存编程功能
 *
@verbatim
 ===============================================================================
                ##### 闪存编程功能 #####
 ===============================================================================
    [..]
      该组包括以下函数:
      (+) void FLASH_Unlock(void)
      (+) void FLASH_Lock(void)
      (+) FLASH_Status FLASH_EraseSector(uint32_t FLASH_Sector, uint8_t VoltageRange)
      (+) FLASH_Status FLASH_EraseAllSectors(uint8_t VoltageRange)
      (+) FLASH_Status FLASH_ProgramDoubleWord(uint32_t Address, uint64_t Data)
      (+) FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
      (+) FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
      (+) FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data)
          以下功能只能用于 STM32F42xxx/43xxx 设备。
      (+) FLASH_Status FLASH_EraseAllBank1Sectors(uint8_t VoltageRange)
      (+) FLASH_Status FLASH_EraseAllBank2Sectors(uint8_t VoltageRange)
    [..]
      擦除或程序的任何操作都应遵循以下步骤:
          (#) 调用 FLASH_Unlock() 函数以启用 FLASH 控制寄存器访问
          (#) 调用所需函数擦除扇区或程序数据
          (#) 调用 FLASH_Lock() 函数以禁用 FLASH 控制寄存器
               访问(建议用于保护FLASH内存免受可能的不必要操作)

@endverbatim
  */

/**
  * 简介:  解锁 FLASH 控制寄存器访问。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void FLASH_Unlock(void) {
    if((FLASH->CR & FLASH_CR_LOCK) != RESET) {
        /* 授权闪存寄存器访问 */
        FLASH->KEYR = FLASH_KEY1;
        FLASH->KEYR = FLASH_KEY2;
    }
}

/**
  * 简介:  锁定 FLASH 控制寄存器访问。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void FLASH_Lock(void) {
    /* 设置 LOCK Bit to lock the FLASH Registers access */
    FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * 简介:  擦除指定的 FLASH 扇区。
  *
  * 注意:   如果同时请求擦除和程序操作，则擦除操作将在程序操作之前执行。
  *
  * 参数:  FLASH_Sector: 要擦除的扇区编号。
  *
  *  @note  对于 STM32F405xx/407xx 和 STM32V415xx/417xx 设备，
  *         此参数可以是介于 FLASH_Sector_0 和 FLASH_Sentor_11之间的值。
  *
  *         对于 STM32F42xxx/43xxx 设备此参数可以是FLASH_Sector_0 和 FLASH_Sector_23之间的值。
  *
  *         对于 STM32F401xx 设备，此参数可以是介于 FLASH_Sector_0 和 FLASH_Sctor_5 之间的值。
  *
  *         对于 STM32F411xE 和 STM32V412xG设备，此参数可以是介于
  *         FLASH_Sector_0 和 FLASH_Sctor_7 之间的值。
  *
  *         对于 STM32F410xx 设备，此参数可以是介于 FLASH_Sector_0 和 FLASH_Sctor_4之间的值。
  *
  *         对于 STM32F413_423xx 设备，此参数可以是介于 FLASH_Sector_0 和 FLASH_Sctor_15 之间的值。
  *
  * 参数:  VoltageRange: 定义擦除并行度的设备电压范围。
  *          此参数可以是以下值之一:
  *             @arg VoltageRange_1: 当设备电压范围为1.8V至2.1V时，
  *                                  将以字节(8位)方式进行操作。
  *             @arg VoltageRange_2: 当设备电压范围为2.1V至2.7V时，
  *                                  将以半字(16位)进行操作。
  *             @arg VoltageRange_3: 当设备电压范围为2.7V至3.6V时，
  *                                  将以字(32位)进行操作。
  *             @arg VoltageRange_4: 当器件电压范围为2.7V至3.6V+外部Vpp时，
  *                                  将通过双字(64位)进行操作。
  *
  * 返回值: FLASH Status: 返回的值可以是:FLASH_BUSY、FLASH_ERROR_PROGRAM、
  *                       FLASH_ARROR_WRP、FLASHE_ERROR_OPERATION或FLASH_COMPLETE。
  */
FLASH_Status FLASH_EraseSector(uint32_t FLASH_Sector, uint8_t VoltageRange) {
    uint32_t tmp_psize = 0x0;
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_FLASH_SECTOR(FLASH_Sector));
    assert_param(IS_VOLTAGERANGE(VoltageRange));

    if(VoltageRange == VoltageRange_1) {
        tmp_psize = FLASH_PSIZE_BYTE;
    } else if(VoltageRange == VoltageRange_2) {
        tmp_psize = FLASH_PSIZE_HALF_WORD;
    } else if(VoltageRange == VoltageRange_3) {
        tmp_psize = FLASH_PSIZE_WORD;
    } else {
        tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
    }

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        /* 如果上一次操作完成，则继续擦除扇区 */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= tmp_psize;
        FLASH->CR &= SECTOR_MASK;
        FLASH->CR |= FLASH_CR_SER | FLASH_Sector;
        FLASH->CR |= FLASH_CR_STRT;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果擦除操作完成，则禁用 SER位 */
        FLASH->CR &= (~FLASH_CR_SER);
        FLASH->CR &= SECTOR_MASK;
    }

    /* 返回Erase 状态 */
    return status;
}

/**
  * 简介:  擦除所有 FLASH 扇区。
  *
  * 注意:   如果同时请求擦除和程序操作，则擦除操作将在程序操作之前执行。
  *
  * 参数:  VoltageRange: 定义擦除并行度的设备电压范围。
  *          此参数可以是以下值之一:
  *            @arg VoltageRange_1: 当设备电压范围为 1.8V 至 2.1V 时，操作将通过字节(8位)完成
  *            @arg VoltageRange_2: 当设备电压范围为 2.1V 至 2.7V 时，操作将通过半字(16位)完成
  *            @arg VoltageRange_3: 当设备电压范围为 2.7V 至 3.6V 时，操作将通过字(32位)完成
  *            @arg VoltageRange_4: 当设备电压范围为 2.7V 至 3.6V+ 外部 Vpp 时，操作将通过双字(64位)完成
  *
  * 返回值: FLASH Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseAllSectors(uint8_t VoltageRange) {
    uint32_t tmp_psize = 0x0;
    FLASH_Status status = FLASH_COMPLETE;

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();
    assert_param(IS_VOLTAGERANGE(VoltageRange));

    if(VoltageRange == VoltageRange_1) {
        tmp_psize = FLASH_PSIZE_BYTE;
    } else if(VoltageRange == VoltageRange_2) {
        tmp_psize = FLASH_PSIZE_HALF_WORD;
    } else if(VoltageRange == VoltageRange_3) {
        tmp_psize = FLASH_PSIZE_WORD;
    } else {
        tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
    }

    if(status == FLASH_COMPLETE) {
        /* 如果上一次操作完成，则继续擦除所有扇区 */
        #if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx)
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= tmp_psize;
        FLASH->CR |= (FLASH_CR_MER1 | FLASH_CR_MER2);
        FLASH->CR |= FLASH_CR_STRT;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果擦除操作完成，则禁用 MER 位 */
        FLASH->CR &= ~(FLASH_CR_MER1 | FLASH_CR_MER2);
        #endif /* STM32F427_437xx ||  STM32F429_439xx ||  STM32F469_479xx */

        #if defined(STM32F40_41xxx) || defined(STM32F401xx) || defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F412xG) || defined(STM32F413_423xx) || defined(STM32F446xx)
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= tmp_psize;
        FLASH->CR |= FLASH_CR_MER;
        FLASH->CR |= FLASH_CR_STRT;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果擦除操作完成，则禁用 MER 位 */
        FLASH->CR &= (~FLASH_CR_MER);
        #endif /* STM32F40_41xxx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F412xG || STM32F413_423xx || STM32F446xx */

    }

    /* 返回Erase 状态 */
    return status;
}

/**
  * 简介:  擦除 Bank 1 中的所有 FLASH 扇区。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 设备。
  *
  * 注意:   如果同时请求擦除和程序操作，则擦除操作将在程序操作之前执行。
  *
  * 参数:  VoltageRange: 定义擦除并行度的设备电压范围。
  *          此参数可以是以下值之一:
  *            @arg VoltageRange_1: 当设备电压范围为 1.8V 至 2.1V 时，操作将通过字节(8位)完成
  *            @arg VoltageRange_2: 当设备电压范围为 2.1V 至 2.7V 时，操作将通过半字(16位)完成
  *            @arg VoltageRange_3: 当设备电压范围为 2.7V 至 3.6V 时，操作将通过字(32位)完成
  *            @arg VoltageRange_4: 当设备电压范围为 2.7V 至 3.6V+ 外部 Vpp 时，操作将通过双字(64位)完成
  *
  * 返回值: FLASH Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseAllBank1Sectors(uint8_t VoltageRange) {
    uint32_t tmp_psize = 0x0;
    FLASH_Status status = FLASH_COMPLETE;

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();
    assert_param(IS_VOLTAGERANGE(VoltageRange));

    if(VoltageRange == VoltageRange_1) {
        tmp_psize = FLASH_PSIZE_BYTE;
    } else if(VoltageRange == VoltageRange_2) {
        tmp_psize = FLASH_PSIZE_HALF_WORD;
    } else if(VoltageRange == VoltageRange_3) {
        tmp_psize = FLASH_PSIZE_WORD;
    } else {
        tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
    }

    if(status == FLASH_COMPLETE) {
        /* 如果上一次操作完成，则继续擦除所有扇区 */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= tmp_psize;
        FLASH->CR |= FLASH_CR_MER1;
        FLASH->CR |= FLASH_CR_STRT;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果擦除操作完成，则禁用 MER 位 */
        FLASH->CR &= (~FLASH_CR_MER1);

    }

    /* 返回Erase 状态 */
    return status;
}


/**
  * 简介:  擦除 Bank 2 中的所有 FLASH 扇区。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 设备。
  *
  * 注意:   如果同时请求擦除和程序操作，则擦除操作将在程序操作之前执行。
  *
  * 参数:  VoltageRange: 定义擦除并行度的设备电压范围。
  *          此参数可以是以下值之一:
  *            @arg VoltageRange_1: 当设备电压范围为 1.8V 至 2.1V 时，操作将通过字节(8位)完成
  *            @arg VoltageRange_2: 当设备电压范围为 2.1V 至 2.7V 时，操作将通过半字(16位)完成
  *            @arg VoltageRange_3: 当设备电压范围为 2.7V 至 3.6V 时，操作将通过字(32位)完成
  *            @arg VoltageRange_4: 当设备电压范围为 2.7V 至 3.6V+ 外部 Vpp 时，操作将通过双字(64位)完成
  *
  * 返回值: FLASH Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseAllBank2Sectors(uint8_t VoltageRange) {
    uint32_t tmp_psize = 0x0;
    FLASH_Status status = FLASH_COMPLETE;

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();
    assert_param(IS_VOLTAGERANGE(VoltageRange));

    if(VoltageRange == VoltageRange_1) {
        tmp_psize = FLASH_PSIZE_BYTE;
    } else if(VoltageRange == VoltageRange_2) {
        tmp_psize = FLASH_PSIZE_HALF_WORD;
    } else if(VoltageRange == VoltageRange_3) {
        tmp_psize = FLASH_PSIZE_WORD;
    } else {
        tmp_psize = FLASH_PSIZE_DOUBLE_WORD;
    }

    if(status == FLASH_COMPLETE) {
        /* 如果上一次操作完成，则继续擦除所有扇区 */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= tmp_psize;
        FLASH->CR |= FLASH_CR_MER2;
        FLASH->CR |= FLASH_CR_STRT;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果擦除操作完成，则禁用 MER 位 */
        FLASH->CR &= (~FLASH_CR_MER2);

    }

    /* 返回Erase 状态 */
    return status;
}

/**
  * 简介:  在指定地址编程双字(64 位)。
  * 
  * 注意:   当设备电压范围为 2.7V 至 3.6V 且存在外部Vpp时，必须使用此函数。
  *
  * 注意:   如果同时请求擦除和程序操作，则擦除操作将在程序操作之前执行。
  *
  * 参数:  Address: 指定要编程的地址。
  * 
  * 参数:  Data: 指定要编程的数据。
  * 
  * 返回值: FLASH Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramDoubleWord(uint32_t Address, uint64_t Data) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_FLASH_ADDRESS(Address));

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        /* 如果上一个操作已完成，则继续对新数据进行编程 */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= FLASH_PSIZE_DOUBLE_WORD;
        FLASH->CR |= FLASH_CR_PG;

        *(__IO uint64_t*)Address = Data;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果程序操作完成，禁用 PG 位 */
        FLASH->CR &= (~FLASH_CR_PG);
    }

    /* 返回Program 状态 */
    return status;
}

/**
  * 简介:  在指定地址编程一个字(32 位)。
  *
  * 注意:   当设备电压范围为 2.7V 至 3.6V 时，必须使用此函数。
  *
  * 注意:   如果同时请求擦除和程序操作，则擦除操作将在程序操作之前执行。
  *
  * 参数:  Address: 指定要编程的地址。
  *         此参数可以是程序内存区域或OTP区域中的任何地址。
  * 
  * 参数:  Data: 指定要编程的数据。
  * 
  * 返回值: FLASH Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_FLASH_ADDRESS(Address));

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        /* 如果上一个操作已完成，则继续对新数据进行编程 */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= FLASH_PSIZE_WORD;
        FLASH->CR |= FLASH_CR_PG;

        *(__IO uint32_t*)Address = Data;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果程序操作完成，禁用 PG 位 */
        FLASH->CR &= (~FLASH_CR_PG);
    }

    /* 返回Program 状态 */
    return status;
}

/**
  * 简介:  在指定地址编程半字(16 位)。
  * 
  * 注意:   当设备电压范围为2.1V至3.6V时，必须使用此函数。
  *
  * 注意:   如果同时请求擦除和程序操作，则擦除操作将在程序操作之前执行。
  *
  * 参数:  Address: 指定要编程的地址。
  *         此参数可以是程序内存区域或OTP区域中的任何地址。
  * 
  * 参数:  Data: 指定要编程的数据。
  * 
  * 返回值: FLASH Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_FLASH_ADDRESS(Address));

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        /* 如果上一个操作已完成，则继续对新数据进行编程 */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= FLASH_PSIZE_HALF_WORD;
        FLASH->CR |= FLASH_CR_PG;

        *(__IO uint16_t*)Address = Data;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果程序操作完成，禁用 PG 位 */
        FLASH->CR &= (~FLASH_CR_PG);
    }

    /* 返回Program 状态 */
    return status;
}

/**
  * 简介:  在指定地址编程一个字节(8 位)。
  * 
  * 注意:   此功能可在所有设备电源电压范围内使用。
  *
  * 注意:   如果同时请求擦除和程序操作，则擦除操作将在程序操作之前执行。
  *
  * 参数:  Address: 指定要编程的地址。
  *         此参数可以是程序内存区域或OTP区域中的任何地址。
  * 
  * 参数:  Data: 指定要编程的数据。
  * 
  * 返回值: FLASH Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_FLASH_ADDRESS(Address));

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        /* 如果上一个操作已完成，则继续对新数据进行编程 */
        FLASH->CR &= CR_PSIZE_MASK;
        FLASH->CR |= FLASH_PSIZE_BYTE;
        FLASH->CR |= FLASH_CR_PG;

        *(__IO uint8_t*)Address = Data;

        /* 等待最后一次操作完成 */
        status = FLASH_WaitForLastOperation();

        /* 如果程序操作完成，禁用 PG 位 */
        FLASH->CR &= (~FLASH_CR_PG);
    }

    /* 返回Program 状态 */
    return status;
}


/** @defgroup FLASH_Group3 选项字节编程功能
 *  简介   选项字节编程功能
 *
@verbatim
 ===============================================================================
                ##### 选项字节编程功能 #####
 ===============================================================================
    [..]
      该组包括以下函数:
      (+) void FLASH_OB_Unlock(void)
      (+) void FLASH_OB_Lock(void)
      (+) void FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState)
      (+) void FLASH_OB_WRP1Config(uint32_t OB_WRP, FunctionalState NewState)
      (+) void FLASH_OB_PCROPSelectionConfig(uint8_t OB_PCROPSelect)
      (+) void FLASH_OB_PCROPConfig(uint32_t OB_PCROP, FunctionalState NewState)
      (+) void FLASH_OB_PCROP1Config(uint32_t OB_PCROP, FunctionalState NewState)
      (+) void FLASH_OB_RDPConfig(uint8_t OB_RDP)
      (+) void FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY)
      (+) void FLASH_OB_BORConfig(uint8_t OB_BOR)
      (+) FLASH_Status FLASH_ProgramOTP(uint32_t Address, uint32_t Data)
      (+) FLASH_Status FLASH_OB_Launch(void)
      (+) uint32_t FLASH_OB_GetUser(void)
      (+) uint8_t FLASH_OB_GetWRP(void)
      (+) uint8_t FLASH_OB_GetWRP1(void)
      (+) uint8_t FLASH_OB_GetPCROP(void)
      (+) uint8_t FLASH_OB_GetPCROP1(void)
      (+) uint8_t FLASH_OB_GetRDP(void)
      (+) uint8_t FLASH_OB_GetBOR(void)
    [..]
      以下功能只能用于 STM32F42xxx/43xxx 设备。
      (+) void FLASH_OB_BootConfig(uint8_t OB_BOOT)
    [..]
     擦除或程序的任何操作都应遵循以下步骤:
      (#) 调用FLASH_OB_Unlock() 函数以启用FLASH选项控制寄存器访问

      (#) 调用一个或多个函数来编程所需的选项字节:
        (++) void FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState)
             => 启用/禁用所需的扇区写保护
        (++) void FLASH_OB_RDPConfig(uint8_t OB_RDP) => 设置所需的读取保护级别
        (++) void FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY)
             => 配置用户选项字节。
        (++) void FLASH_OB_BORConfig(uint8_t OB_BOR) => 设置BOR级别

      (#)正确写入所有需要编程的选项字节后，
           调用FLASH_OB_Launch() 函数启动选项字节编程过程。
      -@-将IWDG模式从HW更改为SW或从SW更改为 HW时，
           需要进行系统重置以使更改生效。
      (#)调用FLASH_OB_Lock() 函数以禁用FLASH选项控制寄存器访问
          (建议用于保护选项字节免受可能不需要的操作)

@endverbatim
  */

/**
  * 简介:  解锁闪存选项控制寄存器访问。
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void FLASH_OB_Unlock(void) {
    if((FLASH->OPTCR & FLASH_OPTCR_OPTLOCK) != RESET) {
        /* Authorizes the Option Byte register programming */
        FLASH->OPTKEYR = FLASH_OPT_KEY1;
        FLASH->OPTKEYR = FLASH_OPT_KEY2;
    }
}

/**
  * 简介:  上锁 FLASH 选项控制寄存器访问
  * 
  * 参数:  无
  * 
  * 返回值: 无
  */
void FLASH_OB_Lock(void) {
    /* 设置用于锁定FLASH选项字节寄存器访问的OPTLOCK位 */
    FLASH->OPTCR |= FLASH_OPTCR_OPTLOCK;
}

/**
  * 简介:  为 Flash 的前 1 Mb 启用或禁用所需扇区的写保护。
  *
  * 注意:   选择内存读取保护级别(RDP级别=1)时，如果连接了CortexM4调试功能
  *         或在RAM 中执行引导代码，则无法对闪存扇区i进行编程或擦除，即使nWRPi=1
  * 注意:   当PCROP模式处于活动状态(SPRMOD=1)时，nWRPi位的活动值被反转。
  *
  * 参数:  OB_WRP: 指定要写保护或不保护的扇区。
  *          此参数可以是以下值之一:
  *            @arg OB_WRP: OB_WRP_Sector0 和 OB_WRP _Sector11 之间的值
  *            @arg OB_WRP_Sector_All
  * 
  * 参数:  Newstate: 写保护的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_OB_WRP(OB_WRP));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        if(NewState != DISABLE) {
            *(__IO uint16_t*)OPTCR_BYTE2_ADDRESS &= (~OB_WRP);
        } else {
            *(__IO uint16_t*)OPTCR_BYTE2_ADDRESS |= (uint16_t)OB_WRP;
        }
    }
}

/**
  * 简介:  为闪存的第二个 1 Mb 启用或禁用所需扇区的写保护。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 设备。
  *
  * 注意:   选择内存读取保护时(RDP级别=1)，如果连接了CortexM4调试功能或
  *         在RAM 中执行引导代码，则无法编程或擦除闪存扇区i，即使nWRPi=1
  * 
  * 注意:   当PCROP模式处于活动状态(SPRMOD=1)时，nWRPi位的活动值被反转。
  *
  * 参数:  OB_WRP: 指定要写保护或不保护的扇区。
  *          此参数可以是以下值之一:
  *            @arg OB_WRP: OB_WRP_Sector12 和OB_WRP _Sector23之间的值
  *            @arg OB_WRP_Sector_All
  * 
  * 参数:  Newstate: 写保护的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FLASH_OB_WRP1Config(uint32_t OB_WRP, FunctionalState NewState) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_OB_WRP(OB_WRP));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        if(NewState != DISABLE) {
            *(__IO uint16_t*)OPTCR1_BYTE2_ADDRESS &= (~OB_WRP);
        } else {
            *(__IO uint16_t*)OPTCR1_BYTE2_ADDRESS |= (uint16_t)OB_WRP;
        }
    }
}

/**
  * 简介:  选择保护模式 (SPRMOD)。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 和 STM32V401xx/411xE设备。
  *
  * 注意:   PCROP激活后，无法修改选项字节。
  *         全局读取保护修改级别(级别1 到级别0)出现异常
  * 注意:   一旦SPRMOD位处于活动状态，就不可能取消保护受保护扇区
  *
  * 注意:   读取受保护扇区将设置 RDERR标志，写入受保护扇区将设置WRPERR标志
  *
  * 注意:   激活PCROP功能时应采取一些预防措施:
  *            当PCROP模式激活时，nWRPi位的激活值被反转，这意味着如果 SPRMOD=1
  *            WRPi=1(默认值)，则用户扇区i受读/写保护。
  *            为了避免为不需要的扇区激活PCROP模式，请遵循以下安全顺序:
  *            -使用FLASH_OB_PCROP_Config(OB_PCROP Sector_all，Disable) 函数为所有扇区禁用 PCROP
  *               对于Bank1或对于Bank2的 FLASH_OB_PCROP_Sector_All，DISABLE) 函数
  *            -使用FLASH_OB_PCROPConfig(Sector i，Enable) 功能为所需扇区i启用 PCROP
  *            -激活PCROP模式FLASH_OB_PCROPSelectionConfig() 功能。
  *
  * 参数:  OB_PCROP:  选择nWPRi位的保护模式
  *          此参数可以是以下值之一:
  *            @arg OB_PcROP_Disable: nWRPi控制各个用户扇区的写保护。
  *            @arg OB_PcROP_Enable: nWRPi控制各个用户扇区的读写保护(PCROP)。
  * 
  * 返回值: 无
  */
void FLASH_OB_PCROPSelectionConfig(uint8_t OB_PcROP) {
    uint8_t optiontmp = 0xFF;

    /* 检查参数 */
    assert_param(IS_OB_PCROP_SELECT(OB_PcROP));

    /* Mask SPRMOD 位 */
    optiontmp =  (uint8_t)((*(__IO uint8_t *)OPTCR_BYTE3_ADDRESS) & (uint8_t)0x7F);
    /* Update Option Byte */
    *(__IO uint8_t *)OPTCR_BYTE3_ADDRESS = (uint8_t)(OB_PcROP | optiontmp);
}

/**
  * 简介:  为 Flash 的前 1 MB 启用或禁用所需扇区的读/写保护 (PCROP)。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx、STM32F2F401xx/411xE STM32F112xG 和 STM32P413_423xx 设备。
  *
  * 参数:  OB_PCROP: 指定要读/写保护或不保护的扇区。
  *          此参数可以是以下值之一:
  *            @arg OB_PCROP: STM32F42xxx/43xxx 设备的OB_PCROP_Sector0 和
  *                           OB_PCROP_Sector11之间的值，STM32V401xx/411xE设备的
  *                           OB-PCROP_Sector0 和OB-PCROP_Sector5 之间的值。
  *            @arg OB_PCROP_Sector_All
  * 
  * 参数:  Newstate: 写保护的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FLASH_OB_PCROPConfig(uint32_t OB_PCROP, FunctionalState NewState) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_OB_PCROP(OB_PCROP));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        if(NewState != DISABLE) {
            *(__IO uint16_t*)OPTCR_BYTE2_ADDRESS |= (uint16_t)OB_PCROP;
        } else {
            *(__IO uint16_t*)OPTCR_BYTE2_ADDRESS &= (~OB_PCROP);
        }
    }
}

/**
   * 简介: 启用或禁用所需扇区的读/写保护 (PCROP)。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 设备。
  *
  * 参数:  OB_PCROP: 指定要读/写保护或不保护的扇区。
  *          此参数可以是以下值之一:
  *            @arg OB_PCROP: OB_PCROP_Sector12 和OB_PCROP_Sector23之间的值
  *            @arg OB_PCROP_Sector_All
  * 参数:  Newstate: 写保护的新状态。
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void FLASH_OB_PCROP1Config(uint32_t OB_PCROP, FunctionalState NewState) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_OB_PCROP(OB_PCROP));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        if(NewState != DISABLE) {
            *(__IO uint16_t*)OPTCR1_BYTE2_ADDRESS |= (uint16_t)OB_PCROP;
        } else {
            *(__IO uint16_t*)OPTCR1_BYTE2_ADDRESS &= (~OB_PCROP);
        }
    }
}


/**
  * 简介:  设置读保护级别。
  * 参数:  OB_RDP: 指定读取保护级别。
  *          此参数可以是以下值之一:
  *             @arg OB_RDP_Level_0:无保护
  *             @arg OB_RDP_Level_1:内存的读取保护
  *             @arg OB_RDP_Level_2:全芯片保护
  *
  * 警告:启用OB_RDP级别2时，无法返回级别1或0
  *
  * 返回值: 无
  */
void FLASH_OB_RDPConfig(uint8_t OB_RDP) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_OB_RDP(OB_RDP));

    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        *(__IO uint8_t*)OPTCR_BYTE1_ADDRESS = OB_RDP;

    }
}

/**
  * 简介:  对 FLASH 用户选项字节进行编程:IWDG_SW / RST_STOP / RST_STDBY。
  * 
  * 参数:  OB_IWDG: 选择IWDG模式
  *          此参数可以是以下值之一:
  *            @arg OB_IWDG_SW: 已选择软件IWDG
  *            @arg OB_IWDG_HW: 已选择硬件IWDG
  * 
  * 参数:  OB_STOP: 进入停止模式时重置事件。
  *         此参数可以是以下值之一:
  *             @arg OB_STOP_NoRST:输入STOP时未生成重置
  *             @arg OB_STOP_RST:输入STOP时生成重置
  * 
  * 参数:  OB_STDBY:进入待机模式时重置事件。
  *         此参数可以是以下值之一:
  *             @arg OB_STDBY_NoRST:输入STANDBY时未生成重置
  *             @arg OB_STDBY_RST:输入STANDBY时生成重置
  * 
  * 返回值: 无
  */
void FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY) {
    uint8_t optiontmp = 0xFF;
    FLASH_Status status = FLASH_COMPLETE;

    /* 检查参数 */
    assert_param(IS_OB_IWDG_SOURCE(OB_IWDG));
    assert_param(IS_OB_STOP_SOURCE(OB_STOP));
    assert_param(IS_OB_STDBY_SOURCE(OB_STDBY));

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();

    if(status == FLASH_COMPLETE) {
        #if defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F469_479xx)
        /* Mask OPTLOCK, OPTSTRT, BOR_LEV and BFB2 位 */
        optiontmp =  (uint8_t)((*(__IO uint8_t *)OPTCR_BYTE0_ADDRESS) & (uint8_t)0x1F);
        #endif /* STM32F427_437xx ||  STM32F429_439xx ||  STM32F469_479xx */

        #if defined(STM32F40_41xxx) || defined(STM32F401xx) || defined(STM32F410xx) || defined(STM32F411xE) || defined(STM32F446xx)
        /* Mask OPTLOCK, OPTSTRT and BOR_LEV 位 */
        optiontmp =  (uint8_t)((*(__IO uint8_t *)OPTCR_BYTE0_ADDRESS) & (uint8_t)0x0F);
        #endif /* STM32F40_41xxx || STM32F401xx || STM32F410xx || STM32F411xE || STM32F446xx */

        /* Update User Option Byte */
        *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS = OB_IWDG | (uint8_t)(OB_STDBY | (uint8_t)(OB_STOP | ((uint8_t)optiontmp)));
    }
}

/**
  * 简介:  配置双组引导。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 设备。
  *
  * 参数:  OB_BOOT: 指定 Dual Bank Boot Option字节。
  *          此参数可以是以下值之一:
  *            @arg OB_Dual_BootEnabled: 双排启动已启用
  *            @arg OB_Dual_BootDisabled: 双排启动已禁用
  * 
  * 返回值: 无
  */
void FLASH_OB_BootConfig(uint8_t OB_BOOT) {
    /* 检查参数 */
    assert_param(IS_OB_BOOT(OB_BOOT));

    /* Set Dual Bank Boot */
    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS &= (~FLASH_OPTCR_BFB2);
    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= OB_BOOT;

}

/**
  * 简介:  设置 BOR 级别。
  * 
  * 参数:  OB_BOR: 指定选项字节BOR重置级别。
  *          此参数可以是以下值之一:
  *             @arg OB_BOR_LEVEL3:电源电压范围为2.7至3.6 V
  *             @arg OB_BOR_LEVEL2:电源电压范围为2.4至2.7 V
  *             @arg OB_BOR_LEVEL1:电源电压范围为2.1至2.4 V
  *             @arg OB_BOR_OFF:电源电压范围为1.62至2.1 V
  * 
  * 返回值: 无
  */
void FLASH_OB_BORConfig(uint8_t OB_BOR) {
    /* 检查参数 */
    assert_param(IS_OB_BOR(OB_BOR));

    /* 设置 BOR Level */
    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS &= (~FLASH_OPTCR_BOR_LEV);
    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= OB_BOR;

}

/**
  * 简介:  启动选项字节加载。
  * 
  * 参数:  无
  * 
  * 返回值: FLASH Status: 返回的值可以是:FLASH_BUSY、FLASH_ERROR_PROGRAM、
  *                       FLASH_ARROR_WRP、FLASHE_ERROR_OPERATION或FLASH_COMPLETE。
  */
FLASH_Status FLASH_OB_Launch(void) {
    FLASH_Status status = FLASH_COMPLETE;

    /* 设置 OPTSTRT bit in OPTCR 寄存器 */
    *(__IO uint8_t *)OPTCR_BYTE0_ADDRESS |= FLASH_OPTCR_OPTSTRT;

    /* 等待最后一次操作完成 */
    status = FLASH_WaitForLastOperation();

    return status;
}

/**
  * 简介:  返回 FLASH 用户选项字节值。
  * 
  * 参数:  无
  * 
  * 返回值: FLASH用户选项字节值:IWDG_SW(位0)、RST_STOP(位1)和 RST_STDBY(位2)。
  */
uint8_t FLASH_OB_GetUser(void) {
    /* 返回User Option Byte */
    return (uint8_t)(FLASH->OPTCR >> 5);
}

/**
  * 简介:  返回 FLASH 写保护选项字节值。
  * 
  * 参数:  无
  * 
  * 返回值: 闪存写保护选项字节值
  */
uint16_t FLASH_OB_GetWRP(void) {
    /* 返回FLASH write protection寄存器值 */
    return (*(__IO uint16_t *)(OPTCR_BYTE2_ADDRESS));
}

/**
  * 简介:  返回 FLASH 写保护选项字节值。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 设备。
  *
  * 参数:  无
  * 
  * 返回值: 闪存写保护选项字节值
  */
uint16_t FLASH_OB_GetWRP1(void) {
    /* 返回FLASH write protection寄存器值 */
    return (*(__IO uint16_t *)(OPTCR1_BYTE2_ADDRESS));
}

/**
  * 简介:  返回 FLASH PC 读/写保护选项字节值。
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 设备 and STM32F401xx/411xE devices.
  *
  * 参数:  无
  * 
  * 返回值: FLASH PC读/写保护选项字节值
  */
uint16_t FLASH_OB_GetPCROP(void) {
    /* 返回FLASH PC Read/write protection寄存器值 */
    return (*(__IO uint16_t *)(OPTCR_BYTE2_ADDRESS));
}

/**
  * 简介:  Returns FLASH PC读/写保护选项字节值.
  *
  * 注意:   此函数只能用于 STM32F42xxx/43xxx 设备。
  *
  * 参数:  无
  * 
  * 返回值: FLASH PC读/写保护选项字节值
  */
uint16_t FLASH_OB_GetPCROP1(void) {
    /* 返回FLASH write protection寄存器值 */
    return (*(__IO uint16_t *)(OPTCR1_BYTE2_ADDRESS));
}

/**
  * 简介:  返回 FLASH 读保护级别。
  * 
  * 参数:  无
  * 
  * 返回值: 闪存读取保护状态:
  *           - SET, 当OB_RDP_Level_1或OB_RDP_Level_2被设置时。
  *           - RESET, 当OB_RDP_Level_0被设置时。
  */
FlagStatus FLASH_OB_GetRDP(void) {
    FlagStatus readstatus = RESET;

    if ((*(__IO uint8_t*)(OPTCR_BYTE1_ADDRESS) != (uint8_t)OB_RDP_Level_0)) {
        readstatus = SET;
    } else {
        readstatus = RESET;
    }

    return readstatus;
}

/**
  * 简介:  返回 FLASH BOR 级别。
  * 
  * 参数:  无
  * 
  * 返回值: 闪存BOR级别:
  *       - OB_BOR_LEVEL3:电源电压范围为2.7至3.6 V
  *       - OB_BOR_LEVEL2:电源电压范围为2.4至2.7 V
  *       - OB_BOR_LEVEL1:电源电压范围为2.1至2.4 V
  *       - OB_BOR_OFF:电源电压范围为1.62至2.1 V
  */
uint8_t FLASH_OB_GetBOR(void) {
    /* 返回FLASH BOR level */
    return (uint8_t)(*(__IO uint8_t *)(OPTCR_BYTE0_ADDRESS) & (uint8_t)0x0C);
}


/** @defgroup FLASH_Group4 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
              ##### 中断和标记管理函数 #####
 ===============================================================================
@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 FLASH 中断。
  * 
  * 参数:  FLASH_IT: 指定要启用或禁用的 FLASH中断源。
  *          此参数可以是以下值的任意组合:
  *            @arg FLASH_IT_ERR: 闪存错误中断
  *            @arg FLASH_IT_EOP: 闪存操作结束中断
  * 
  * 返回值: 无
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_FLASH_IT(FLASH_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE) {
        /* 启用中断源 */
        FLASH->CR |= FLASH_IT;
    } else {
        /* 禁用中断源 */
        FLASH->CR &= ~(uint32_t)FLASH_IT;
    }
}

/**
  * 简介:  检查是否设置了指定的 FLASH 标志。
  * 
  * 参数:  FLASH_FLAG: 指定要检查的 FLASH标志。
  *          此参数可以是以下值之一:
  *             @arg FLASH_FLAG_EOP:FLASH 操作结束标志
  *             @arg FLASH_FLAG_OPERR:FLASH 操作错误标志
  *             @arg FLASH_FLAG_WRPERR:FLASH写保护错误标志
  *             @arg FLASH_FLAG_PGAERR:FLASH编程校准错误标志
  *             @arg FLASH_FLAG_PGPERR:FLASH编程并行性错误标志
  *             @arg FLASH_FLAG_PGSERR:FLASH编程序列错误标志
  *             @arg FLASH_FLAG_RDERR:FLASH(PCROP)读保护错误标志(STM32F42xx/43xxx 和 STM32F2F401xx/411xE设备)
  *             @arg FLASH_FLAG_BSY:FLASH Busy标志
  * 
  * 返回值: FLASH_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_FLASH_GET_FLAG(FLASH_FLAG));

    if((FLASH->SR & FLASH_FLAG) != (uint32_t)RESET) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    /* 返回new state of FLASH_FLAG (SET or RESET) */
    return bitstatus;
}

/**
  * 简介:  清除 FLASH 的挂起标志。
  * 
  * 参数:  FLASH_FLAG: 指定要清除的 FLASH标志。
  *          此参数可以是以下值的任意组合:
  *            @arg FLASH_FLAG_EOP:FLASH 操作结束标志
  *            @arg FLASH_FLAG_OPERR:FLASH 操作错误标志
  *            @arg FLASH_FLAG_WRPERR:FLASH写保护错误标志
  *            @arg FLASH_FLAG_PGAERR:FLASH编程校准错误标志
  *            @arg FLASH_FLAG_PGPERR:FLASH编程并行性错误标志
  *            @arg FLASH_FLAG_PGSERR:FLASH编程序列错误标志
  *            @arg FLASH_FLAG_RDERR:闪存读取保护错误标志(STM32F42xx/43xxx 和 STM32V401xx/411xE设备)
  * 
  * 返回值: 无
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG) {
    /* 检查参数 */
    assert_param(IS_FLASH_CLEAR_FLAG(FLASH_FLAG));

    /* 清除 flags */
    FLASH->SR = FLASH_FLAG;
}

/**
  * 简介:  返回闪存状态。
  * 
  * 参数:  无
  * 
  * 返回值: FLASH_Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_RD, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_GetStatus(void) {
    FLASH_Status flashstatus = FLASH_COMPLETE;

    if((FLASH->SR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY) {
        flashstatus = FLASH_BUSY;
    } else {
        if((FLASH->SR & FLASH_FLAG_WRPERR) != (uint32_t)0x00) {
            flashstatus = FLASH_ERROR_WRP;
        } else {
            if((FLASH->SR & FLASH_FLAG_RDERR) != (uint32_t)0x00) {
                flashstatus = FLASH_ERROR_RD;
            } else {
                if((FLASH->SR & (uint32_t)0xE0) != (uint32_t)0x00) {
                    flashstatus = FLASH_ERROR_PROGRAM;
                } else {
                    if((FLASH->SR & FLASH_FLAG_OPERR) != (uint32_t)0x00) {
                        flashstatus = FLASH_ERROR_OPERATION;
                    } else {
                        flashstatus = FLASH_COMPLETE;
                    }
                }
            }
        }
    }

    /* 返回FLASH 状态 */
    return flashstatus;
}

/**
  * 简介:  等待 FLASH 操作完成。
  * 
  * 参数:  无
  * 
  * 返回值: FLASH Status: 返回值可以是: FLASH_BUSY, FLASH_ERROR_PROGRAM,
  *                       FLASH_ERROR_WRP, FLASH_ERROR_OPERATION or FLASH_COMPLETE.
  */
FLASH_Status FLASH_WaitForLastOperation(void) {
    __IO FLASH_Status status = FLASH_COMPLETE;

    /* 检查 FLASH 状态 */
    status = FLASH_GetStatus();

    /* 通过对要重置的BUSY标志进行轮询，等待FLASH 操作完成。
       即使FLASH 操作失败，BUSY标志也将重置，并设置错误标志 */
    while(status == FLASH_BUSY) {
        status = FLASH_GetStatus();
    }

    /* 返回操作状态 */
    return status;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
