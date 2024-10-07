/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.8.0
  * 日期:    04-November-2016
  * 简介:   主中断服务例程。
  *          此文件为所有异常处理程序和外设设备中断服务例程提供模板。
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
#include "stm32f4xx_it.h"

/** @addtogroup Template_Project
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * 简介:  This function handles NMI exception.
  * @param  无
  * @retval 无
  */
void NMI_Handler(void) {
}

/**
  * 简介:  This function handles Hard Fault exception.
  * @param  无
  * @retval 无
  */
void HardFault_Handler(void) {
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
    }
}

/**
  * 简介:  This function handles Memory Manage exception.
  * @param  无
  * @retval 无
  */
void MemManage_Handler(void) {
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
    }
}

/**
  * 简介:  This function handles Bus Fault exception.
  * @param  无
  * @retval 无
  */
void BusFault_Handler(void) {
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}

/**
  * 简介:  This function handles Usage Fault exception.
  * @param  无
  * @retval 无
  */
void UsageFault_Handler(void) {
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
    }
}

/**
  * 简介:  This function handles SVCall exception.
  * @param  无
  * @retval 无
  */
void SVC_Handler(void) {
}

/**
  * 简介:  This function handles Debug Monitor exception.
  * @param  无
  * @retval 无
  */
void DebugMon_Handler(void) {
}

/**
  * 简介:  This function handles PendSVC exception.
  * @param  无
  * @retval 无
  */
void PendSV_Handler(void) {
}

/**
  * 简介:  This function handles SysTick Handler.
  * @param  无
  * @retval 无
  */
void SysTick_Handler(void) {
    // TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * 简介:  This function handles PPP interrupt request.
  * @param  无
  * @retval 无
  */
/*void PPP_IRQHandler(void)
{
}*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
