/**
  ************************* Copyright **********************
  *
  *          (C) Copyright 2023,txt1994,China, GCU.
  *                    All Rights Reserved
  *
  *                 https://github.com/txt1994
  *			        email:linguangyuan88@icloud.com
  *
  * FileName     : delay.c
  * Version      : v1.0
  * Author       : txt1994
  * Date         : 2023-03-16
  * Description  :
  * Function List:

  **********************************************************
 */
#include "delay.h"

/* delay variable */
static __IO uint32_t fac_us;
static __IO uint32_t fac_ms;

/* delay macros */
#define STEP_DELAY_MS                    50

/**
  * @brief  initialize delay function
  * @param  无
  * @retval 无
  */
void delay_Init(void) {
    /* configure systick */
    systick_Clock_Source_Config(SYSTICK_Clock_Source_AHBCLK_NODIV);
    fac_us = system_core_clock / (1000000U);
    fac_ms = fac_us * (1000U);
}

/**
  * @brief  inserts a delay time.
  * @param  nus: 指定delay time length, in microsecond.
  * @retval 无
  */
void delay_us(uint32_t nus) {
    uint32_t temp = 0;
    SysTick->LOAD = (uint32_t)(nus * fac_us);
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_Enable_Msk ;

    do {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16)));

    SysTick->CTRL &= ~SysTick_CTRL_Enable_Msk;
    SysTick->VAL = 0x00;
}

/**
  * @brief  inserts a delay time.
  * @param  nms: 指定delay time length, in milliseconds.
  * @retval 无
  */
void delay_ms(uint16_t nms) {
    uint32_t temp = 0;

    while(nms) {
        if(nms > STEP_DELAY_MS) {
            SysTick->LOAD = (uint32_t)(STEP_DELAY_MS * fac_ms);
            nms -= STEP_DELAY_MS;
        } else {
            SysTick->LOAD = (uint32_t)(nms * fac_ms);
            nms = 0;
        }

        SysTick->VAL = 0x00;
        SysTick->CTRL |= SysTick_CTRL_Enable_Msk;

        do {
            temp = SysTick->CTRL;
        } while((temp & 0x01) && !(temp & (1 << 16)));

        SysTick->CTRL &= ~SysTick_CTRL_Enable_Msk;
        SysTick->VAL = 0x00;
        SysTick_Config(1000);
    }
}

/**
  * @brief  inserts a delay time.
  * @param  sec: 指定delay time, in seconds.
  * @retval 无
  */
void delay_sec(uint16_t sec) {
    uint16_t index;

    for(index = 0; index < sec; index++) {
        delay_ms(500);
        delay_ms(500);
    }
}
