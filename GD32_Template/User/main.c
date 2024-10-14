/**
  ************************* Copyright ********************** 
  *
  *          (C) Copyright 2022,txt1994,China, GCU.
  *                    All Rights Reserved
  *                              
  *                 https://github.com/txt1994
  *			        email:linguangyuan88@icloud.com
  *    
  * FileName     : main.c   
  * Version      : v1.0		
  * Author       : txt1994			
  * Date         : 2022-10-18         
  * Description  :    
  * Function List:  

  **********************************************************
 */
#include "gd32f4xx.h"                   // Device header

static uint8_t us = 0;
static uint16_t ms = 0;

void Delay_init(uint8_t Mhz) {
    Systick_CLKsource_Set(SYSTICK_CLKSOURCE_HCLK_DIV8);

    us = Mhz / 8;
    ms = (uint16_t)us * 1000;
}

void Delay_us(uint16_t dly) { // 1800
    uint32_t tmp;

    //SysTick->CALIB = SysTick_CALIB_SKEW_Pos;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开启计数器
    SysTick->LOAD = (uint32_t)ms * dly; // 1.8s
    SysTick->VAL = 0;

    do {
        tmp = SysTick->CTRL;

    } while(tmp&0x01 && !(tmp&(1 << 16)));

    SysTick->VAL = 0;
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
}

void Delay_ms(uint32_t dly) { // 1800

    uint32_t tmp;

    //SysTick->CALIB = SysTick_CALIB_SKEW_Pos;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; // 开启计数器
    SysTick->LOAD = ms * dly; // 1.8s
    SysTick->VAL = 0;

    do {
        tmp = SysTick->CTRL;

    } while(tmp&0x01 && !(tmp&(1 << 16)));

    SysTick->VAL = 0;
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // 关闭计数器
}

int main(void) {
    SysTick_Config(168000);
    return 0;
}
