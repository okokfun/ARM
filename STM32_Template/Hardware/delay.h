/**
  ************************ Copyright ***************
  *           (C) Copyright 2022,txt1994,China, GCU.
  *                  All Rights Reserved
  *
  *				https://github.com/txt1994
  *				email:linguangyuan88@icloud.com
  *
  * FileName     : delay.h
  * Version      : v1.0
  * Author       : txt1994
  * Date         : 2022-10-18
  * Description  :
  * Function List:

  ******************************************************
**/

#ifndef __DELAY_H_
#define __DELAY_H_

#include "stm32f4xx_conf.h"

void delay_init(uint8_t SYSCLK);
void delay_ms(uint16_t nms);

void delay_us(uint32_t nus);

#endif
