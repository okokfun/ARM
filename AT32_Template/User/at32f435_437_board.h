/**
  **************************************************************************
  * @file     at32f435_437_board.c
  * @brief    header file for at-start board. set of firmware functions to
  *           manage leds and push-button. initialize delay function.
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#ifndef __AT32F435_437_BOARD_H
#define __AT32F435_437_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "at32f435_437.h"

/** @addtogroup AT32F435_437_board
  */

/** @addtogroup BOARD
  */

/** @defgroup BOARD_Pins_definition
  */

/**
  * this header include define support list:
  *   1. at-start-f435 v1.x board
  *   2. at-start-f437 v1.x board
  * if define AT_Start_F435_V1, the header file support at-start-f437 v1.x board
  * if define AT_Start_F437_V1, the header file support at-start-f437 v1.x board
  */

#if !defined (AT_Start_F435_V1) && !defined (AT_Start_F437_V1)
#error "please select first the board at-start device used in your application (in at32f435_437_board.h file)"
#endif

/******************** define led ********************/
typedef enum {
    LED2                                   = 0,
    LED3                                   = 1,
    LED4                                   = 2
} led_Type;

#define LED_Num                          3

#if defined (AT_Start_F435_V1) || defined (AT_Start_F437_V1)
#define LED2_PIN                         GPIO_Pins_13
#define LED2_GPIO                        GPIOD
#define LED2_GPIO_CRM_CLK                CRM_GPIOD_Periph_CLOCK

#define LED3_PIN                         GPIO_Pins_14
#define LED3_GPIO                        GPIOD
#define LED3_GPIO_CRM_CLK                CRM_GPIOD_Periph_CLOCK

#define LED4_PIN                         GPIO_Pins_15
#define LED4_GPIO                        GPIOD
#define LED4_GPIO_CRM_CLK                CRM_GPIOD_Periph_CLOCK
#endif

/**************** define print uart ******************/
#define PRINT_UART                       USART1
#define PRINT_UART_CRM_CLK               CRM_USART1_Periph_CLOCK
#define PRINT_UART_TX_PIN                GPIO_Pins_9
#define PRINT_UART_TX_GPIO               GPIOA
#define PRINT_UART_TX_GPIO_CRM_CLK       CRM_GPIOA_Periph_CLOCK
#define PRINT_UART_TX_Pin_SOURCE         GPIO_Pins_SOURCE9
#define PRINT_UART_TX_Pin_MUX_Num        GPIO_MUX_7

/******************* define button *******************/
typedef enum {
    USER_BUTTON                            = 0,
    NO_BUTTON                              = 1
} button_Type;

#define USER_BUTTON_PIN                  GPIO_Pins_0
#define USER_BUTTON_PORT                 GPIOA
#define USER_BUTTON_CRM_CLK              CRM_GPIOA_Periph_CLOCK

/** @defgroup BOARD_exported_functions
  */

/******************** functions ********************/
void at32_board_Init(void);

/* led operation function */
void at32_led_Init(led_Type led);
void at32_led_ON(led_Type led);
void at32_led_off(led_Type led);
void at32_led_toggle(led_Type led);

/* button operation function */
void at32_button_Init(void);
button_Type at32_button_press(void);
uint8_t at32_button_state(void);

/* delay function */
void delay_Init(void);
void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
void delay_sec(uint16_t sec);

/* printf uart init function */
void uart_print_Init(uint32_t baudrate);

#ifdef __cplusplus
}
#endif

#endif

