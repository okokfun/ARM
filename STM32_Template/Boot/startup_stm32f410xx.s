;******************** (C) COPYRIGHT 2016 STMicroelectronics ********************
;* File Name          : startup_stm32f410xx.s
;* Author             : MCD Application Team
;* @version           : V1.8.0
;* @date              : 09-November-2016
;* Description        : STM32F410xx devices vector table for MDK-ARM toolchain. 
;*                      此模块执行以下操作:
;*                      - 设置初始 SP
;*                      - 设置初始PC == Reset_Handler
;*                      - 配置具有异常 ISR 地址的矢量表条目
;*                      - 分支到C库中的__main(最终调用main())。
;*                      重置后，CortexM4 处理器处于线程模式，优先级为特权，栈设置为主。
;* <<< 在上下文菜单中使用配置向导 >>>   
;*******************************************************************************
; 
;* Redistribution and use in source and binary forms, with or without modification,
;* are permitted provided that the following conditions are met:
;*   1. Redistributions of source code must retain the above copyright notice,
;*      this list of conditions and the following disclaimer.
;*   2. Redistributions in binary form must reproduce the above copyright notice,
;*      this list of conditions and the following disclaimer in the documentation
;*      and/or other materials provided with the distribution.
;*   3. Neither the name of STMicroelectronics nor the names of its contributors
;*      may be used to endorse or promote products derived from this software
;*      without specific prior written permission.
;*
;* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
;* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
;* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
;* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
;* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
;* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
;* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; 
;*******************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> 堆配置
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp               ; 栈顶
                DCD     Reset_Handler              ; 重置处理程序
                DCD     NMI_Handler                ; NMI 处理程序
                DCD     HardFault_Handler          ; 硬故障处理程序
                DCD     MemManage_Handler          ; MPU故障处理程序
                DCD     BusFault_Handler           ; 总线故障处理程序
                DCD     UsageFault_Handler         ; 使用故障处理程序
                DCD     0                          ; 保留部分
                DCD     0                          ; 保留部分
                DCD     0                          ; 保留部分
                DCD     0                          ; 保留部分
                DCD     SVC_Handler                ; SVCall 处理程序
                DCD     DebugMon_Handler           ; Debug Monitor 处理程序
                DCD     0                          ; 保留部分
                DCD     PendSV_Handler             ; PendSV 处理程序
                DCD     SysTick_Handler            ; SysTick 处理程序

                ; 外部中断
                DCD     WWDG_IRQHandler                   ; Window WatchDog
                DCD     PVD_IRQHandler                    ; PVD through EXTI Line detection
                DCD     TAMP_STAMP_IRQHandler             ; Tamper and TimeStamps through the EXTI line
                DCD     RTC_WKUP_IRQHandler               ; RTC Wakeup through the EXTI line
                DCD     FLASH_IRQHandler                  ; FLASH
                DCD     RCC_IRQHandler                    ; RCC
                DCD     EXTI0_IRQHandler                  ; EXTI Line0
                DCD     EXTI1_IRQHandler                  ; EXTI Line1
                DCD     EXTI2_IRQHandler                  ; EXTI Line2
                DCD     EXTI3_IRQHandler                  ; EXTI Line3
                DCD     EXTI4_IRQHandler                  ; EXTI Line4
                DCD     DMA1_Stream0_IRQHandler           ; DMA1 Stream 0
                DCD     DMA1_Stream1_IRQHandler           ; DMA1 Stream 1
                DCD     DMA1_Stream2_IRQHandler           ; DMA1 Stream 2
                DCD     DMA1_Stream3_IRQHandler           ; DMA1 Stream 3
                DCD     DMA1_Stream4_IRQHandler           ; DMA1 Stream 4
                DCD     DMA1_Stream5_IRQHandler           ; DMA1 Stream 5
                DCD     DMA1_Stream6_IRQHandler           ; DMA1 Stream 6
                DCD     ADC_IRQHandler                    ; ADC1, ADC2 and ADC3s
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     EXTI9_5_IRQHandler                ; External Line[9:5]s
                DCD     TIM1_BRK_TIM9_IRQHandler          ; TIM1 Break and TIM9
                DCD     TIM1_UP_IRQHandler                ; TIM1 Update
                DCD     TIM1_TRG_COM_TIM11_IRQHandler     ; TIM1 Trigger and Commutation and TIM11
                DCD     TIM1_CC_IRQHandler                ; TIM1 Capture Compare
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     I2C1_EV_IRQHandler                ; I2C1 事件
                DCD     I2C1_ER_IRQHandler                ; I2C1 错误
                DCD     I2C2_EV_IRQHandler                ; I2C2 事件
                DCD     I2C2_ER_IRQHandler                ; I2C2 错误
                DCD     SPI1_IRQHandler                   ; SPI1
                DCD     SPI2_IRQHandler                   ; SPI2
                DCD     USART1_IRQHandler                 ; USART1
                DCD     USART2_IRQHandler                 ; USART2
                DCD     0                                 ; 保留部分
                DCD     EXTI15_10_IRQHandler              ; External Line[15:10]s
                DCD     RTC_Alarm_IRQHandler              ; RTC Alarm (A and B) through EXTI Line
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     DMA1_Stream7_IRQHandler           ; DMA1 Stream7
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     TIM5_IRQHandler                   ; TIM5
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     TIM6_DAC_IRQHandler               ; TIM6 and DAC
                DCD     0                                 ; 保留部分
                DCD     DMA2_Stream0_IRQHandler           ; DMA2 Stream 0
                DCD     DMA2_Stream1_IRQHandler           ; DMA2 Stream 1
                DCD     DMA2_Stream2_IRQHandler           ; DMA2 Stream 2
                DCD     DMA2_Stream3_IRQHandler           ; DMA2 Stream 3
                DCD     DMA2_Stream4_IRQHandler           ; DMA2 Stream 4
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     DMA2_Stream5_IRQHandler           ; DMA2 Stream 5
                DCD     DMA2_Stream6_IRQHandler           ; DMA2 Stream 6
                DCD     DMA2_Stream7_IRQHandler           ; DMA2 Stream 7
                DCD     USART6_IRQHandler                 ; USART6
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     RNG_IRQHandler                    ; RNG
                DCD     FPU_IRQHandler                    ; FPU
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     SPI5_IRQHandler                   ; SPI5
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     0                                 ; 保留部分
                DCD     FMPI2C1_EV_IRQHandler             ; FMPI2C1 Event
                DCD     FMPI2C1_ER_IRQHandler             ; FMPI2C1 Error
                DCD     LPTIM1_IRQHandler                 ; LP TIM1

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; 重置处理程序
Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]
        IMPORT  SystemInit
        IMPORT  __main

                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; 伪异常处理程序(可以修改的无限循环)

NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                   [WEAK]
                EXPORT  PVD_IRQHandler                    [WEAK]
                EXPORT  TAMP_STAMP_IRQHandler             [WEAK]
                EXPORT  RTC_WKUP_IRQHandler               [WEAK]
                EXPORT  FLASH_IRQHandler                  [WEAK]
                EXPORT  RCC_IRQHandler                    [WEAK]
                EXPORT  EXTI0_IRQHandler                  [WEAK]
                EXPORT  EXTI1_IRQHandler                  [WEAK]
                EXPORT  EXTI2_IRQHandler                  [WEAK]
                EXPORT  EXTI3_IRQHandler                  [WEAK]
                EXPORT  EXTI4_IRQHandler                  [WEAK]
                EXPORT  DMA1_Stream0_IRQHandler           [WEAK]
                EXPORT  DMA1_Stream1_IRQHandler           [WEAK]
                EXPORT  DMA1_Stream2_IRQHandler           [WEAK]
                EXPORT  DMA1_Stream3_IRQHandler           [WEAK]
                EXPORT  DMA1_Stream4_IRQHandler           [WEAK]
                EXPORT  DMA1_Stream5_IRQHandler           [WEAK]
                EXPORT  DMA1_Stream6_IRQHandler           [WEAK]
                EXPORT  ADC_IRQHandler                    [WEAK]
                EXPORT  EXTI9_5_IRQHandler                [WEAK]
                EXPORT  TIM1_BRK_TIM9_IRQHandler          [WEAK]
                EXPORT  TIM1_UP_IRQHandler                [WEAK]
                EXPORT  TIM1_TRG_COM_TIM11_IRQHandler     [WEAK]
                EXPORT  TIM1_CC_IRQHandler                [WEAK]
                EXPORT  I2C1_EV_IRQHandler                [WEAK]
                EXPORT  I2C1_ER_IRQHandler                [WEAK]
                EXPORT  I2C2_EV_IRQHandler                [WEAK]
                EXPORT  I2C2_ER_IRQHandler                [WEAK]
                EXPORT  SPI1_IRQHandler                   [WEAK]
                EXPORT  SPI2_IRQHandler                   [WEAK]
                EXPORT  USART1_IRQHandler                 [WEAK]
                EXPORT  USART2_IRQHandler                 [WEAK]
                EXPORT  EXTI15_10_IRQHandler              [WEAK]
                EXPORT  RTC_Alarm_IRQHandler              [WEAK]
                EXPORT  DMA1_Stream7_IRQHandler           [WEAK]
                EXPORT  TIM5_IRQHandler                   [WEAK]
                EXPORT  TIM6_DAC_IRQHandler               [WEAK]
                EXPORT  DMA2_Stream0_IRQHandler           [WEAK]
                EXPORT  DMA2_Stream1_IRQHandler           [WEAK]
                EXPORT  DMA2_Stream2_IRQHandler           [WEAK]
                EXPORT  DMA2_Stream3_IRQHandler           [WEAK]
                EXPORT  DMA2_Stream4_IRQHandler           [WEAK]
                EXPORT  DMA2_Stream4_IRQHandler           [WEAK]
                EXPORT  DMA2_Stream5_IRQHandler           [WEAK]
                EXPORT  DMA2_Stream6_IRQHandler           [WEAK]
                EXPORT  DMA2_Stream7_IRQHandler           [WEAK]
                EXPORT  USART6_IRQHandler                 [WEAK]
                EXPORT  RNG_IRQHandler                    [WEAK]
                EXPORT  FPU_IRQHandler                    [WEAK]
                EXPORT  SPI5_IRQHandler                   [WEAK]
                EXPORT  FMPI2C1_EV_IRQHandler             [WEAK]
                EXPORT  FMPI2C1_ER_IRQHandler             [WEAK]
                EXPORT  LPTIM1_IRQHandler                [WEAK]

WWDG_IRQHandler
PVD_IRQHandler
TAMP_STAMP_IRQHandler
RTC_WKUP_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Stream0_IRQHandler
DMA1_Stream1_IRQHandler
DMA1_Stream2_IRQHandler
DMA1_Stream3_IRQHandler
DMA1_Stream4_IRQHandler
DMA1_Stream5_IRQHandler
DMA1_Stream6_IRQHandler
ADC_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_TIM9_IRQHandler
TIM1_UP_IRQHandler
TIM1_TRG_COM_TIM11_IRQHandler
TIM1_CC_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
EXTI15_10_IRQHandler
RTC_Alarm_IRQHandler
DMA1_Stream7_IRQHandler
TIM5_IRQHandler
TIM6_DAC_IRQHandler
DMA2_Stream0_IRQHandler
DMA2_Stream1_IRQHandler
DMA2_Stream2_IRQHandler
DMA2_Stream3_IRQHandler
DMA2_Stream4_IRQHandler
DMA2_Stream5_IRQHandler
DMA2_Stream6_IRQHandler
DMA2_Stream7_IRQHandler
USART6_IRQHandler
RNG_IRQHandler
FPU_IRQHandler
SPI5_IRQHandler
FMPI2C1_EV_IRQHandler
FMPI2C1_ER_IRQHandler
LPTIM1_IRQHandler

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; 用户栈和堆初始化
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
