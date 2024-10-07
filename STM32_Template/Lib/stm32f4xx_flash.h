/**
  ******************************************************************************
  * 文件:    stm32f4xx_flash.h
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件包含 FLASH 固件库的所有功能原型.
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
#ifndef __STM32F4xx_FLASH_H
#define __STM32F4xx_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @addtogroup FLASH
  */

/* Exported types ------------------------------------------------------------*/
/**
  * 简介: 闪存状态
  */
typedef enum {
    FLASH_BUSY = 1,
    FLASH_ERROR_RD,
    FLASH_ERROR_PGS,
    FLASH_ERROR_PGP,
    FLASH_ERROR_PGA,
    FLASH_ERROR_WRP,
    FLASH_ERROR_PROGRAM,
    FLASH_ERROR_OPERATION,
    FLASH_COMPLETE
} FLASH_Status;

/* Exported constants --------------------------------------------------------*/

/** @defgroup FLASH_Exported_Constants
  */

/** @defgroup Flash_Latency
  */
#define FLASH_Latency_0                ((uint8_t)0x0000)  /*!< FLASH 零延迟周期      */
#define FLASH_Latency_1                ((uint8_t)0x0001)  /*!< FLASH 一个延迟周期       */
#define FLASH_Latency_2                ((uint8_t)0x0002)  /*!< FLASH Two 延迟周期      */
#define FLASH_Latency_3                ((uint8_t)0x0003)  /*!< FLASH Three 延迟周期    */
#define FLASH_Latency_4                ((uint8_t)0x0004)  /*!< FLASH Four 延迟周期     */
#define FLASH_Latency_5                ((uint8_t)0x0005)  /*!< FLASH Five 延迟周期     */
#define FLASH_Latency_6                ((uint8_t)0x0006)  /*!< FLASH Six 延迟周期      */
#define FLASH_Latency_7                ((uint8_t)0x0007)  /*!< FLASH Seven 延迟周期    */
#define FLASH_Latency_8                ((uint8_t)0x0008)  /*!< FLASH Eight 延迟周期    */
#define FLASH_Latency_9                ((uint8_t)0x0009)  /*!< FLASH Nine 延迟周期     */
#define FLASH_Latency_10               ((uint8_t)0x000A)  /*!< FLASH Ten 延迟周期      */
#define FLASH_Latency_11               ((uint8_t)0x000B)  /*!< FLASH Eleven 延迟周期   */
#define FLASH_Latency_12               ((uint8_t)0x000C)  /*!< FLASH Twelve 延迟周期   */
#define FLASH_Latency_13               ((uint8_t)0x000D)  /*!< FLASH Thirteen 延迟周期 */
#define FLASH_Latency_14               ((uint8_t)0x000E)  /*!< FLASH Fourteen 延迟周期 */
#define FLASH_Latency_15               ((uint8_t)0x000F)  /*!< FLASH Fifteen 延迟周期 */


#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0)  || \
                                   ((LATENCY) == FLASH_Latency_1)  || \
                                   ((LATENCY) == FLASH_Latency_2)  || \
                                   ((LATENCY) == FLASH_Latency_3)  || \
                                   ((LATENCY) == FLASH_Latency_4)  || \
                                   ((LATENCY) == FLASH_Latency_5)  || \
                                   ((LATENCY) == FLASH_Latency_6)  || \
                                   ((LATENCY) == FLASH_Latency_7)  || \
                                   ((LATENCY) == FLASH_Latency_8)  || \
                                   ((LATENCY) == FLASH_Latency_9)  || \
                                   ((LATENCY) == FLASH_Latency_10) || \
                                   ((LATENCY) == FLASH_Latency_11) || \
                                   ((LATENCY) == FLASH_Latency_12) || \
                                   ((LATENCY) == FLASH_Latency_13) || \
                                   ((LATENCY) == FLASH_Latency_14) || \
                                   ((LATENCY) == FLASH_Latency_15))

/** @defgroup FLASH_Voltage_Range
  */
#define VoltageRange_1        ((uint8_t)0x00)  /*!< 器件工作范围: 1.8V 至 2.1V */
#define VoltageRange_2        ((uint8_t)0x01)  /*!< 器件工作范围: 2.1V to 2.7V */
#define VoltageRange_3        ((uint8_t)0x02)  /*!< 器件工作范围: 2.7V to 3.6V */
#define VoltageRange_4        ((uint8_t)0x03)  /*!< 器件工作范围: 2.7V 至 3.6V + 外部 Vpp */

#define IS_VOLTAGERANGE(RANGE)(((RANGE) == VoltageRange_1) || \
                               ((RANGE) == VoltageRange_2) || \
                               ((RANGE) == VoltageRange_3) || \
                               ((RANGE) == VoltageRange_4))

/** @defgroup FLASH_Sectors
  */
#define FLASH_Sector_0     ((uint16_t)0x0000) /*!< 扇区号 0   */
#define FLASH_Sector_1     ((uint16_t)0x0008) /*!< 扇区号 1   */
#define FLASH_Sector_2     ((uint16_t)0x0010) /*!< 扇区号 2   */
#define FLASH_Sector_3     ((uint16_t)0x0018) /*!< 扇区号 3   */
#define FLASH_Sector_4     ((uint16_t)0x0020) /*!< 扇区号 4   */
#define FLASH_Sector_5     ((uint16_t)0x0028) /*!< 扇区号 5   */
#define FLASH_Sector_6     ((uint16_t)0x0030) /*!< 扇区号 6   */
#define FLASH_Sector_7     ((uint16_t)0x0038) /*!< 扇区号 7   */
#define FLASH_Sector_8     ((uint16_t)0x0040) /*!< 扇区号 8   */
#define FLASH_Sector_9     ((uint16_t)0x0048) /*!< 扇区号 9   */
#define FLASH_Sector_10    ((uint16_t)0x0050) /*!< 扇区号 10  */
#define FLASH_Sector_11    ((uint16_t)0x0058) /*!< 扇区号 11  */
#define FLASH_Sector_12    ((uint16_t)0x0080) /*!< 扇区号 12  */
#define FLASH_Sector_13    ((uint16_t)0x0088) /*!< 扇区号 13  */
#define FLASH_Sector_14    ((uint16_t)0x0090) /*!< 扇区号 14  */
#define FLASH_Sector_15    ((uint16_t)0x0098) /*!< 扇区号 15  */
#define FLASH_Sector_16    ((uint16_t)0x00A0) /*!< 扇区号 16  */
#define FLASH_Sector_17    ((uint16_t)0x00A8) /*!< 扇区号 17  */
#define FLASH_Sector_18    ((uint16_t)0x00B0) /*!< 扇区号 18  */
#define FLASH_Sector_19    ((uint16_t)0x00B8) /*!< 扇区号 19  */
#define FLASH_Sector_20    ((uint16_t)0x00C0) /*!< 扇区号 20  */
#define FLASH_Sector_21    ((uint16_t)0x00C8) /*!< 扇区号 21  */
#define FLASH_Sector_22    ((uint16_t)0x00D0) /*!< 扇区号 22  */
#define FLASH_Sector_23    ((uint16_t)0x00D8) /*!< 扇区号 23  */
#define IS_FLASH_SECTOR(SECTOR) (((SECTOR) == FLASH_Sector_0)   || ((SECTOR) == FLASH_Sector_1)   ||\
                                 ((SECTOR) == FLASH_Sector_2)   || ((SECTOR) == FLASH_Sector_3)   ||\
                                 ((SECTOR) == FLASH_Sector_4)   || ((SECTOR) == FLASH_Sector_5)   ||\
                                 ((SECTOR) == FLASH_Sector_6)   || ((SECTOR) == FLASH_Sector_7)   ||\
                                 ((SECTOR) == FLASH_Sector_8)   || ((SECTOR) == FLASH_Sector_9)   ||\
                                 ((SECTOR) == FLASH_Sector_10)  || ((SECTOR) == FLASH_Sector_11)  ||\
                                 ((SECTOR) == FLASH_Sector_12)  || ((SECTOR) == FLASH_Sector_13)  ||\
                                 ((SECTOR) == FLASH_Sector_14)  || ((SECTOR) == FLASH_Sector_15)  ||\
                                 ((SECTOR) == FLASH_Sector_16)  || ((SECTOR) == FLASH_Sector_17)  ||\
                                 ((SECTOR) == FLASH_Sector_18)  || ((SECTOR) == FLASH_Sector_19)  ||\
                                 ((SECTOR) == FLASH_Sector_20)  || ((SECTOR) == FLASH_Sector_21)  ||\
                                 ((SECTOR) == FLASH_Sector_22)  || ((SECTOR) == FLASH_Sector_23))

#if defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F469_479xx)
#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x081FFFFF)) ||\
                                   (((ADDRESS) >= 0x1FFF7800) && ((ADDRESS) <= 0x1FFF7A0F)))
#endif /* STM32F427_437xx || STM32F429_439xx || STM32F469_479xx */

#if defined (STM32F40_41xxx) || defined(STM32F412xG)
#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x080FFFFF)) ||\
                                   (((ADDRESS) >= 0x1FFF7800) && ((ADDRESS) <= 0x1FFF7A0F)))
#endif /* STM32F40_41xxx || STM32F412xG */

#if defined (STM32F401xx)
#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0803FFFF)) ||\
                                   (((ADDRESS) >= 0x1FFF7800) && ((ADDRESS) <= 0x1FFF7A0F)))
#endif /* STM32F401xx */

#if defined (STM32F411xE) || defined (STM32F446xx)
#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0807FFFF)) ||\
                                   (((ADDRESS) >= 0x1FFF7800) && ((ADDRESS) <= 0x1FFF7A0F)))
#endif /* STM32F411xE || STM32F446xx */

#if defined (STM32F410xx)
#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0801FFFF)) ||\
                                   (((ADDRESS) >= 0x1FFF7800) && ((ADDRESS) <= 0x1FFF7A0F)))
#endif /* STM32F410xx */

#if defined(STM32F413_423xx)
#define IS_FLASH_ADDRESS(ADDRESS) ((((ADDRESS) >= 0x08000000) && ((ADDRESS) <= 0x0817FFFF)) ||\
                                   (((ADDRESS) >= 0x1FFF7800) && ((ADDRESS) <= 0x1FFF7BDF)))
#endif /* STM32F413_423xx */

/** @defgroup Option_Bytes_Write_Protection
  */
#define OB_WRP_Sector_0       ((uint32_t)0x00000001) /*!< Sector0 的写保护     */
#define OB_WRP_Sector_1       ((uint32_t)0x00000002) /*!< 写保护 Sector1     */
#define OB_WRP_Sector_2       ((uint32_t)0x00000004) /*!< 写保护 Sector2     */
#define OB_WRP_Sector_3       ((uint32_t)0x00000008) /*!< 写保护 Sector3     */
#define OB_WRP_Sector_4       ((uint32_t)0x00000010) /*!< 写保护 Sector4     */
#define OB_WRP_Sector_5       ((uint32_t)0x00000020) /*!< 写保护 Sector5     */
#define OB_WRP_Sector_6       ((uint32_t)0x00000040) /*!< 写保护 Sector6     */
#define OB_WRP_Sector_7       ((uint32_t)0x00000080) /*!< 写保护 Sector7     */
#define OB_WRP_Sector_8       ((uint32_t)0x00000100) /*!< 写保护 Sector8     */
#define OB_WRP_Sector_9       ((uint32_t)0x00000200) /*!< 写保护 Sector9     */
#define OB_WRP_Sector_10      ((uint32_t)0x00000400) /*!< 写保护 Sector10    */
#define OB_WRP_Sector_11      ((uint32_t)0x00000800) /*!< 写保护 Sector11    */
#define OB_WRP_Sector_12      ((uint32_t)0x00000001) /*!< 写保护 Sector12    */
#define OB_WRP_Sector_13      ((uint32_t)0x00000002) /*!< 写保护 Sector13    */
#define OB_WRP_Sector_14      ((uint32_t)0x00000004) /*!< 写保护 Sector14    */
#define OB_WRP_Sector_15      ((uint32_t)0x00000008) /*!< 写保护 Sector15    */
#define OB_WRP_Sector_16      ((uint32_t)0x00000010) /*!< 写保护 Sector16    */
#define OB_WRP_Sector_17      ((uint32_t)0x00000020) /*!< 写保护 Sector17    */
#define OB_WRP_Sector_18      ((uint32_t)0x00000040) /*!< 写保护 Sector18    */
#define OB_WRP_Sector_19      ((uint32_t)0x00000080) /*!< 写保护 Sector19    */
#define OB_WRP_Sector_20      ((uint32_t)0x00000100) /*!< 写保护 Sector20    */
#define OB_WRP_Sector_21      ((uint32_t)0x00000200) /*!< 写保护 Sector21    */
#define OB_WRP_Sector_22      ((uint32_t)0x00000400) /*!< 写保护 Sector22    */
#define OB_WRP_Sector_23      ((uint32_t)0x00000800) /*!< 写保护 Sector23    */
#define OB_WRP_Sector_All     ((uint32_t)0x00000FFF) /*!< 写保护  all Sectors */

#define IS_OB_WRP(SECTOR)((((SECTOR) & (uint32_t)0xFFFFF000) == 0x00000000) && ((SECTOR) != 0x00000000))

/** @defgroup  Selection_Protection_Mode
  */
#define OB_PcROP_Disable   ((uint8_t)0x00) /*!< 禁用 PcROP，nWPRi 位用于扇区 i 上的写保护 */
#define OB_PcROP_Enable    ((uint8_t)0x80) /*!< 启用用于扇区 i 上的 PCRoP 保护的 PcROP、nWPRi 位  */
#define IS_OB_PCROP_SELECT(PCROP) (((PCROP) == OB_PcROP_Disable) || ((PCROP) == OB_PcROP_Enable))

/** @defgroup Option_Bytes_PC_ReadWrite_Protection
  */
#define OB_PCROP_Sector_0        ((uint32_t)0x00000001) /*!< PC 读/写保护 Sector0      */
#define OB_PCROP_Sector_1        ((uint32_t)0x00000002) /*!< PC 读/写保护 Sector1      */
#define OB_PCROP_Sector_2        ((uint32_t)0x00000004) /*!< PC 读/写保护 Sector2      */
#define OB_PCROP_Sector_3        ((uint32_t)0x00000008) /*!< PC 读/写保护 Sector3      */
#define OB_PCROP_Sector_4        ((uint32_t)0x00000010) /*!< PC 读/写保护 Sector4      */
#define OB_PCROP_Sector_5        ((uint32_t)0x00000020) /*!< PC 读/写保护 Sector5      */
#define OB_PCROP_Sector_6        ((uint32_t)0x00000040) /*!< PC 读/写保护 Sector6      */
#define OB_PCROP_Sector_7        ((uint32_t)0x00000080) /*!< PC 读/写保护 Sector7      */
#define OB_PCROP_Sector_8        ((uint32_t)0x00000100) /*!< PC 读/写保护 Sector8      */
#define OB_PCROP_Sector_9        ((uint32_t)0x00000200) /*!< PC 读/写保护 Sector9      */
#define OB_PCROP_Sector_10       ((uint32_t)0x00000400) /*!< PC 读/写保护 Sector10     */
#define OB_PCROP_Sector_11       ((uint32_t)0x00000800) /*!< PC 读/写保护 Sector11     */
#define OB_PCROP_Sector_12       ((uint32_t)0x00000001) /*!< PC 读/写保护 Sector12     */
#define OB_PCROP_Sector_13       ((uint32_t)0x00000002) /*!< PC 读/写保护 Sector13     */
#define OB_PCROP_Sector_14       ((uint32_t)0x00000004) /*!< PC 读/写保护 Sector14     */
#define OB_PCROP_Sector_15       ((uint32_t)0x00000008) /*!< PC 读/写保护 Sector15     */
#define OB_PCROP_Sector_16       ((uint32_t)0x00000010) /*!< PC 读/写保护 Sector16     */
#define OB_PCROP_Sector_17       ((uint32_t)0x00000020) /*!< PC 读/写保护 Sector17     */
#define OB_PCROP_Sector_18       ((uint32_t)0x00000040) /*!< PC 读/写保护 Sector18     */
#define OB_PCROP_Sector_19       ((uint32_t)0x00000080) /*!< PC 读/写保护 Sector19     */
#define OB_PCROP_Sector_20       ((uint32_t)0x00000100) /*!< PC 读/写保护 Sector20     */
#define OB_PCROP_Sector_21       ((uint32_t)0x00000200) /*!< PC 读/写保护 Sector21     */
#define OB_PCROP_Sector_22       ((uint32_t)0x00000400) /*!< PC 读/写保护 Sector22     */
#define OB_PCROP_Sector_23       ((uint32_t)0x00000800) /*!< PC 读/写保护 Sector23     */
#define OB_PCROP_Sector_All      ((uint32_t)0x00000FFF) /*!< PC 读/写保护 all Sectors  */
#define IS_OB_PCROP(SECTOR)((((SECTOR) & (uint32_t)0xFFFFF000) == 0x00000000) && ((SECTOR) != 0x00000000))

/** @defgroup FLASH_Option_Bytes_Read_Protection
  */
#define OB_RDP_Level_0   ((uint8_t)0xAA)
#define OB_RDP_Level_1   ((uint8_t)0x55)
/*#define OB_RDP_Level_2   ((uint8_t)0xCC)*/ /*!< 警告:启用 2 级读保护时，无法再回到 1 级或 0 级 */
#define IS_OB_RDP(LEVEL) (((LEVEL) == OB_RDP_Level_0)||\
                          ((LEVEL) == OB_RDP_Level_1))/*||\
((LEVEL) == OB_RDP_Level_2))*/

/** @defgroup FLASH_Option_Bytes_IWatchdog
  */
#define OB_IWDG_SW                     ((uint8_t)0x20)  /*!< 选择软件 IWDG */
#define OB_IWDG_HW                     ((uint8_t)0x00)  /*!< 已选择硬件 IWDG */
#define IS_OB_IWDG_SOURCE(SOURCE) (((SOURCE) == OB_IWDG_SW) || ((SOURCE) == OB_IWDG_HW))

/** @defgroup FLASH_Option_Bytes_nRST_STOP
  */
#define OB_STOP_NoRST                  ((uint8_t)0x40) /*!< 进入 STOP 时不产生复位 */
#define OB_STOP_RST                    ((uint8_t)0x00) /*!< 进入 STOP 时产生复位 */
#define IS_OB_STOP_SOURCE(SOURCE) (((SOURCE) == OB_STOP_NoRST) || ((SOURCE) == OB_STOP_RST))


/** @defgroup FLASH_Option_Bytes_nRST_STDBY
  */
#define OB_STDBY_NoRST                 ((uint8_t)0x80) /*!< 进入 STANDBY 时不产生复位 */
#define OB_STDBY_RST                   ((uint8_t)0x00) /*!< 进入 STANDBY 时产生复位 */
#define IS_OB_STDBY_SOURCE(SOURCE) (((SOURCE) == OB_STDBY_NoRST) || ((SOURCE) == OB_STDBY_RST))

/** @defgroup FLASH_BOR_Reset_Level
  */
#define OB_BOR_LEVEL3          ((uint8_t)0x00)  /*!< 电源电压范围为 2.70 至 3.60 V */
#define OB_BOR_LEVEL2          ((uint8_t)0x04)  /*!< 电源电压范围为 2.40 to 2.70 V */
#define OB_BOR_LEVEL1          ((uint8_t)0x08)  /*!< 电源电压范围为 2.10 to 2.40 V */
#define OB_BOR_OFF             ((uint8_t)0x0C)  /*!< 电源电压范围为 1.62 to 2.10 V */
#define IS_OB_BOR(LEVEL) (((LEVEL) == OB_BOR_LEVEL1) || ((LEVEL) == OB_BOR_LEVEL2) ||\
                          ((LEVEL) == OB_BOR_LEVEL3) || ((LEVEL) == OB_BOR_OFF))

/** @defgroup FLASH_Dual_Boot
  */
#define OB_Dual_BootEnabled   ((uint8_t)0x10) /*!< 双银行启动启用                            */
#define OB_Dual_BootDisabled  ((uint8_t)0x00) /*!< 双银行启动启用，始终在用户闪存上启动 */
#define IS_OB_BOOT(BOOT) (((BOOT) == OB_Dual_BootEnabled) || ((BOOT) == OB_Dual_BootDisabled))

/** @defgroup FLASH_Interrupts
  */
#define FLASH_IT_EOP                   ((uint32_t)0x01000000)  /*!< FLASH 操作结束中断源 */
#define FLASH_IT_ERR                   ((uint32_t)0x02000000)  /*!< 错误中断源 */
#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFCFFFFFF) == 0x00000000) && ((IT) != 0x00000000))

/** @defgroup FLASH_Flags
  */
#define FLASH_FLAG_EOP                 ((uint32_t)0x00000001)  /*!< FLASH 操作结束标志               */
#define FLASH_FLAG_OPERR               ((uint32_t)0x00000002)  /*!< FLASH 操作错误标志                */
#define FLASH_FLAG_WRPERR              ((uint32_t)0x00000010)  /*!< FLASH 写保护错误标志          */
#define FLASH_FLAG_PGAERR              ((uint32_t)0x00000020)  /*!< FLASH 编程对齐错误标志    */
#define FLASH_FLAG_PGPERR              ((uint32_t)0x00000040)  /*!< FLASH 编程并行错误标志  */
#define FLASH_FLAG_PGSERR              ((uint32_t)0x00000080)  /*!< FLASH 编程序列错误标志     */
#define FLASH_FLAG_RDERR               ((uint32_t)0x00000100)  /*!< 读保护错误标志 (PCROP)        */
#define FLASH_FLAG_BSY                 ((uint32_t)0x00010000)  /*!< FLASH 忙碌标志                           */
#define IS_FLASH_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFE0C) == 0x00000000) && ((FLAG) != 0x00000000))
#define IS_FLASH_GET_FLAG(FLAG)  (((FLAG) == FLASH_FLAG_EOP)    || ((FLAG) == FLASH_FLAG_OPERR)  || \
                                  ((FLAG) == FLASH_FLAG_WRPERR) || ((FLAG) == FLASH_FLAG_PGAERR) || \
                                  ((FLAG) == FLASH_FLAG_PGPERR) || ((FLAG) == FLASH_FLAG_PGSERR) || \
                                  ((FLAG) == FLASH_FLAG_BSY)    || ((FLAG) == FLASH_FLAG_RDERR))

/** @defgroup FLASH_Program_Parallelism
  */
#define FLASH_PSIZE_BYTE           ((uint32_t)0x00000000)
#define FLASH_PSIZE_HALF_WORD      ((uint32_t)0x00000100)
#define FLASH_PSIZE_WORD           ((uint32_t)0x00000200)
#define FLASH_PSIZE_DOUBLE_WORD    ((uint32_t)0x00000300)
#define CR_PSIZE_MASK              ((uint32_t)0xFFFFFCFF)

/** @defgroup FLASH_Keys
  */
#define RDP_KEY                  ((uint16_t)0x00A5)
#define FLASH_KEY1               ((uint32_t)0x45670123)
#define FLASH_KEY2               ((uint32_t)0xCDEF89AB)
#define FLASH_OPT_KEY1           ((uint32_t)0x08192A3B)
#define FLASH_OPT_KEY2           ((uint32_t)0x4C5D6E7F)

/**
  * 简介:    ACR 寄存器字节 0 (Bits[7:0]) 基地址
  */
#define ACR_BYTE0_ADDRESS           ((uint32_t)0x40023C00)
/**
  * 简介:    OPTCR 寄存器字节  0 (Bits[7:0]) 基地址
  */
#define OPTCR_BYTE0_ADDRESS         ((uint32_t)0x40023C14)
/**
  * 简介:    OPTCR 寄存器字节  1 (Bits[15:8]) 基地址
  */
#define OPTCR_BYTE1_ADDRESS         ((uint32_t)0x40023C15)
/**
  * 简介:    OPTCR 寄存器字节 2 (Bits[23:16]) 基地址
  */
#define OPTCR_BYTE2_ADDRESS         ((uint32_t)0x40023C16)
/**
  * 简介:    OPTCR 寄存器字节  3 (Bits[31:24]) 基地址
  */
#define OPTCR_BYTE3_ADDRESS         ((uint32_t)0x40023C17)

/**
  * 简介:    OPTCR1 寄存器字节  0 (Bits[7:0]) 基地址
  */
#define OPTCR1_BYTE2_ADDRESS         ((uint32_t)0x40023C1A)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* FLASH接口配置功能 ************************************/
void FLASH_SetLatency(uint32_t FLASH_Latency); // 设置代码延迟值。
void FLASH_PrefetchBufferCmd(FunctionalState NewState); // 启用或禁用预取缓冲区。
void FLASH_InstructionCacheCmd(FunctionalState NewState); // 启用或禁用指令缓存功能。
void FLASH_DataCacheCmd(FunctionalState NewState); // 启用或禁用数据缓存功能。
void FLASH_InstructionCacheReset(void); // 重置指令缓存。
void FLASH_DataCacheReset(void); // 重置数据缓存。

/* 闪存编程功能 *****************************************/
void         FLASH_Unlock(void); // 解锁 FLASH 控制寄存器访问。
void         FLASH_Lock(void); // 锁定 FLASH 控制寄存器访问。
FLASH_Status FLASH_EraseSector(uint32_t FLASH_Sector, uint8_t VoltageRange); // 擦除指定的 FLASH 扇区。
FLASH_Status FLASH_EraseAllSectors(uint8_t VoltageRange); // 擦除所有 FLASH 扇区。
FLASH_Status FLASH_EraseAllBank1Sectors(uint8_t VoltageRange); // 擦除 Bank 1 中的所有 FLASH 扇区。
FLASH_Status FLASH_EraseAllBank2Sectors(uint8_t VoltageRange); // 擦除 Bank 2 中的所有 FLASH 扇区。
FLASH_Status FLASH_ProgramDoubleWord(uint32_t Address, uint64_t Data); // 在指定地址编程双字(64 位)。
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data); // 在指定地址编程一个字(32 位)。
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data); // 在指定地址编程半字(16 位)。
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data); // 在指定地址编程一个字节(8 位)。

/* 选项字节编程功能 *****************************************/
void         FLASH_OB_Unlock(void); // 解锁 FLASH 选项控制寄存器访问。
void         FLASH_OB_Lock(void); // 上锁 FLASH 选项控制寄存器访问
void         FLASH_OB_WRPConfig(uint32_t OB_WRP, FunctionalState NewState); // 为 Flash 的前 1 Mb 启用或禁用所需扇区的写保护。
void         FLASH_OB_WRP1Config(uint32_t OB_WRP, FunctionalState NewState); // 为闪存的第二个 1 Mb 启用或禁用所需扇区的写保护。
void         FLASH_OB_PCROPSelectionConfig(uint8_t OB_PcROP); // 选择保护模式 (SPRMOD)。
void         FLASH_OB_PCROPConfig(uint32_t OB_PCROP, FunctionalState NewState); // 为 Flash 的前 1 MB 启用或禁用所需扇区的读/写保护 (PCROP)。
void         FLASH_OB_PCROP1Config(uint32_t OB_PCROP, FunctionalState NewState); // 启用或禁用所需扇区的读/写保护 (PCROP)。
void         FLASH_OB_RDPConfig(uint8_t OB_RDP); // 设置读保护级别。
void         FLASH_OB_UserConfig(uint8_t OB_IWDG, uint8_t OB_STOP, uint8_t OB_STDBY); // 对 FLASH 用户选项字节进行编程:IWDG_SW / RST_STOP / RST_STDBY。
void         FLASH_OB_BORConfig(uint8_t OB_BOR); // 设置 BOR 级别。
void         FLASH_OB_BootConfig(uint8_t OB_BOOT); // 配置双组引导。
FLASH_Status FLASH_OB_Launch(void); // 启动选项字节加载。
uint8_t      FLASH_OB_GetUser(void); // 返回 FLASH 用户选项字节值。
uint16_t     FLASH_OB_GetWRP(void); // 返回 FLASH 写保护选项字节值。
uint16_t     FLASH_OB_GetWRP1(void); // 返回 FLASH 写保护选项字节值。
uint16_t     FLASH_OB_GetPCROP(void); // 返回 FLASH PC 读/写保护选项字节值。
uint16_t     FLASH_OB_GetPCROP1(void); // 返回 FLASH PC 读/写保护选项字节值。
FlagStatus   FLASH_OB_GetRDP(void); // 返回 FLASH 读保护级别。
uint8_t      FLASH_OB_GetBOR(void); // 返回 FLASH BOR 级别。

/* 中断和标志管理功能 **********************************/
void         FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState); // 启用或禁用指定的 FLASH 中断。
FlagStatus   FLASH_GetFlagStatus(uint32_t FLASH_FLAG); // 检查是否设置了指定的 FLASH 标志。
void         FLASH_ClearFlag(uint32_t FLASH_FLAG); // 清除 FLASH 的挂起标志。
FLASH_Status FLASH_GetStatus(void); // 返回闪存状态。
FLASH_Status FLASH_WaitForLastOperation(void); // 等待 FLASH 操作完成。

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_FLASH_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
