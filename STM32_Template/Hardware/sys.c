/**
  ************************* Copyright **********************
  *
  *          (C) Copyright 2022,txt1994,China, GCU.
  *                    All Rights Reserved
  *
  *                 https://github.com/txt1994
  *			        email:linguangyuan88@icloud.com
  *
  * FileName     : sys.c
  * Version      : v1.0
  * Author       : txt1994
  * Date         : 2022-10-18
  * Description  :
  * Function List:

  **********************************************************
 */
#include "sys.h"

//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI
__asm void WFI_SET(void) {
    WFI;
}
//关闭所有中断(但是不包括fault 和 NMI中断)
__asm void INTX_DISABLE(void) {
    CPSID   I
    BX      LR
}
//开启所有中断
__asm void INTX_ENABLE(void) {
    CPSIE   I
    BX      LR
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) {
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
