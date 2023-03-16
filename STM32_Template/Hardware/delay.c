/**
  ************************* Copyright **********************
  *
  *          (C) Copyright 2022,txt1994,China, GCU.
  *                    All Rights Reserved
  *
  *                 https://github.com/txt1994
  *			        email:linguangyuan88@gmail.com
  *
  * FileName     : delay.c
  * Version      : v1.0
  * Author       : txt1994
  * Date         : 2022-10-18
  * Description  :
  * Function List:

  **********************************************************
 */
#include "delay.h"
#include "sys.h"

static uint8_t  fac_us = 0; //us延时倍乘数
static uint16_t fac_ms = 0; //ms延时倍乘数,在ucos下,代表每个节拍的ms数

//初始化延迟函数
//当使用ucos的时候,此函数会初始化ucos的时钟节拍
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init(uint8_t SYSCLK) {

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SYSCLK / 8;		//不论是否使用ucos,fac_us都需要使用
    fac_ms = (uint16_t)fac_us * 1000; //非ucos下,代表每个ms需要的systick时钟数
}

//延时nus
//nus为要延时的us数.
//注意:nus的值,不要大于798915us
void delay_us(uint32_t nus) {
    uint32_t temp;
    SysTick->LOAD = nus * fac_us; //时间加载
    SysTick->VAL = 0x00;      //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;        //开始倒数

    do {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16))); //等待时间到达

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     //关闭计数器
    SysTick->VAL = 0X00;      //清空计数器
}

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对168M条件下,nms<=798ms
void delay_xms(uint16_t nms) {
    uint32_t temp;
    SysTick->LOAD = (uint32_t)nms * fac_ms; //时间加载(SysTick->LOAD为24bit)
    SysTick->VAL = 0x00;          //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;        //开始倒数

    do {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16))); //等待时间到达

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     //关闭计数器
    SysTick->VAL = 0x00;      //清空计数器
}
//延时nms
//nms:0~65535
void delay_ms(uint16_t nms) {
    uint8_t repeat = nms / 540;	//这里用540,是考虑到某些客户可能超频使用,
    //比如超频到248M的时候,delay_xms最大只能延时541ms左右了
    uint16_t remain = nms % 540;

    while(repeat) {
        delay_xms(540);
        repeat--;
    }

    if(remain)delay_xms(remain);
}
