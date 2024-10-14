/**
  ************************ Copyright ***************
  *           (C) Copyright 2023,txt1994,China, GCU.
  *                  All Rights Reserved
  *
  *				https://github.com/txt1994
  *				email:linguangyuan88@icloud.com
  *
  * FileName     : delay.h
  * Version      : v1.0
  * Author       : txt1994
  * Date         : 2023-03-16
  * Description  :
  * Function List:

  ******************************************************
**/

#ifndef __DELAY_H_
#define __DELAY_H_

#include "stdio.h"
#include "at32f435_437.h"

void delay_Init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void delay_sec(uint16_t sec);

#endif
