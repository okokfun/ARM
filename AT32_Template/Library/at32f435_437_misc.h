/**
  **************************************************************************
  * @file     at32f435_437_misc.h
  * @brief    at32f435_437 misc header file
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_MISC_H
#define __AT32F435_437_MISC_H

#ifdef __cplusplus
extern "C" {
#endif


/* includes ------------------------------------------------------------------*/
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_Periph_driver
  * @{
  */

/** @addtogroup MISC
  * @{
  */

/** @defgroup MISC_Vector_Table_Base_Address
  * @{
  */
#define NVIC_VECTTAB_RAM                 ((uint32_t)0x20000000) /*!< nvic vector table based ram address */
#define NVIC_VECTTAB_FLASH               ((uint32_t)0x08000000) /*!< nvic vector table based flash address */

/**
  * @}
  */

/** @defgroup MISC_exported_Types
  * @{
  */

/**
  * @brief nvic interrupt priority group
  */
typedef enum {
    NVIC_Priority_Group_0                  = ((uint32_t)0x7), /*!< 0 bits for preemption priority, 4 bits for subpriority */
    NVIC_Priority_Group_1                  = ((uint32_t)0x6), /*!< 1 bits for preemption priority, 3 bits for subpriority */
    NVIC_Priority_Group_2                  = ((uint32_t)0x5), /*!< 2 bits for preemption priority, 2 bits for subpriority */
    NVIC_Priority_Group_3                  = ((uint32_t)0x4), /*!< 3 bits for preemption priority, 1 bits for subpriority */
    NVIC_Priority_Group_4                  = ((uint32_t)0x3)  /*!< 4 bits for preemption priority, 0 bits for subpriority */
} NVIC_Priority_Group_Type;

/**
  * @brief nvic low power mode
  */
typedef enum {
    NVIC_LP_SLEEPONEXIT                    = 0x02, /*!< enable sleep-on-exit feature */
    NVIC_LP_SLEEPDEEP                      = 0x04, /*!< enable sleep-deep output signal when entering sleep mode */
    NVIC_LP_SEVONPEND                      = 0x10  /*!< send event on pending */
} NVIC_LowPower_Mode_Type;

/**
  * @brief systick clock source
  */
typedef enum {
    Systick_Clock_Source_AHBCLK_DIV8       = ((uint32_t)0x00000000), /*!< systick clock source from core clock div8 */
    Systick_Clock_Source_AHBCLK_NODIV      = ((uint32_t)0x00000004)  /*!< systick clock source from core clock */
} Systick_Clock_Source_Type;

/**
  * @}
  */

/** @defgroup MISC_exported_functions
  * @{
  */

void NVIC_System_Reset(void);
void NVIC_IRQ_Enable(IRQn_Type irqn, uint32_t preempt_priority, uint32_t sub_priority);
void NVIC_IRQ_Disable(IRQn_Type irqn);
void NVIC_Priority_Group_Config(NVIC_Priority_Group_Type priority_group);
void NVIC_Vector_Table_Set(uint32_t base, uint32_t offset);
void NVIC_LowPower_Mode_Config(NVIC_LowPower_Mode_Type lp_Mode, confirm_state new_state);
void Systick_Clock_Source_Config(Systick_Clock_Source_Type source);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
