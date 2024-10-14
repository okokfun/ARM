/**
  ************************ Copyright ***************
  *           (C) Copyright 2022,txt1994,China, GCU.
  *                  All Rights Reserved
  *
  *				https://github.com/txt1994
  *				email:linguangyuan88@icloud.com
  *
  * FileName     : led.h
  * Version      : v1.0
  * Author       : txt1994
  * Date         : 2022-10-18
  * Description  :
  * Function List:

  ******************************************************
**/

#ifndef __LED_H_
#define __LED_H_

#define LED_PORT	GPIOF
#define LED1_PIN	GPIO_Pin_9
#define LED2_PIN	GPIO_Pin_10

#define	RCC_Periph 	RCC_AHB1Periph_GPIOF

void Led_Init(void);

#endif
