/**
  ************************* Copyright **********************
  *
  *          (C) Copyright 2022,txt1994,China, GCU.
  *                    All Rights Reserved
  *
  *                 https://github.com/txt1994
  *			        email:linguangyuan88@icloud.com
  *
  * FileName     : led.c
  * Version      : v1.0
  * Author       : txt1994
  * Date         : 2022-10-18
  * Description  :
  * Function List:

  **********************************************************
 */

#include "stm32f4xx_conf.h"

void Led_Init(void) {
    RCC_AHB1PeriphClockCmd(RCC_Periph, ENABLE);
    GPIO_InitTypeDef GPIO_Stururce;
    GPIO_Stururce.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Stururce.GPIO_OType = GPIO_OType_PP;
    GPIO_Stururce.GPIO_Pin = LED1_PIN | LED2_PIN;
    GPIO_Stururce.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Stururce.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(LED_PORT, &GPIO_Stururce);

    GPIO_SetBits(LED_PORT, LED1_PIN | LED2_PIN);
}
