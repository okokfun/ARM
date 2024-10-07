/**
  **************************************************************************
  * @file     at32f435_437_i2c.c
  * @brief    contains all the functions for the i2c firmware library
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

#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_Periph_driver
  */

/** @defgroup I2C
  * @brief I2C driver modules
  */

#ifdef I2C_MODULE_EnableD

/** @defgroup I2C_private_functions
  */

/**
  * @brief  reset the i2c register
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @retval 无
  */
void I2C_Reset(I2C_Type *I2C_x) {
    if(I2C_x == I2C1) {
        CRM_Periph_Reset(CRM_I2C1_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_I2C1_Periph_Reset, FALSE);
    } else if(I2C_x == I2C2) {
        CRM_Periph_Reset(CRM_I2C2_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_I2C2_Periph_Reset, FALSE);
    } else if(I2C_x == I2C3) {
        CRM_Periph_Reset(CRM_I2C3_Periph_Reset, TRUE);
        CRM_Periph_Reset(CRM_I2C3_Periph_Reset, FALSE);
    }
}

/**
  * @brief  init i2c digit filters and clock control register.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  dfilters: number of digit filters (0x00~0x0F).
  * @param  clk: i2c clock control register (0x00000000~0xFFFFFFFF).
  * @retval 无
  */
void I2C_Init(I2C_Type *I2C_x, uint8_t dfilters, uint32_t clk) {
    /* disable i2c peripheral */
    I2C_x->ctrl1_bit.i2cen = FALSE;

    /* write clkctrl register*/
    I2C_x->clkctrl = clk;

    /* write digital filter register*/
    I2C_x->ctrl1_bit.dflt = dfilters;
}

/**
  * @brief  config i2c own address 1.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  mode: i2c address mode.
  *         该参数可以是以下值之一:
  *         - I2C_Address_Mode_7BIT: 7bit address.
  *         - I2C_Address_Mode_10BIT: 10bit address.
  * @param  address: own address 1, such as 0xB0.
  * @retval 无
  */
void I2C_Own_Address1_Set(I2C_Type *I2C_x, I2C_Address_Mode_Type mode, uint16_t address) {
    /* config address mode */
    I2C_x->oaddr1_bit.addr1mode = mode;

    /* config address */
    I2C_x->oaddr1_bit.addr1 = address & 0x03FF;

    /* enable address */
    I2C_x->oaddr1_bit.addr1en = TRUE;
}

/**
  * @brief  config i2c own address 2 and mask.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  address: own address 1, such as 0xC0.
  * @param  mask: own address 2 mask.
  *         该参数可以是以下值之一:
  *         - I2C_Addr2_NOMASK: compare bit      [7:1].
  *         - I2C_Addr2_MASK01: only compare bit [7:2].
  *         - I2C_Addr2_MASK02: only compare bit [7:2].
  *         - I2C_Addr2_MASK03: only compare bit [7:3].
  *         - I2C_Addr2_MASK04: only compare bit [7:4].
  *         - I2C_Addr2_MASK05: only compare bit [7:5].
  *         - I2C_Addr2_MASK06: only compare bit [7:6].
  *         - I2C_Addr2_MASK07: only compare bit [7].
  * @retval 无
  */
void I2C_Own_Address2_Set(I2C_Type *I2C_x, uint8_t address, I2C_Addr2_Mask_Type mask) {
    I2C_x->oaddr2_bit.addr2mask = mask;

    I2C_x->oaddr2_bit.addr2 = (address >> 1) & 0x7F;
}

/**
  * @brief  enable or 禁用自己的地址2.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Own_Address2_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->oaddr2_bit.addr2en = new_state;
}

/**
  * @brief  enable or disable smbus mode.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  mode: smbus device mode.
  *         该参数可以是以下值之一:
  *         - I2C_SmBus_Mode_DEVICE: smbus device.
  *         - I2C_SmBus_Mode_HOST: smbus host.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_SmBus_Enable(I2C_Type *I2C_x, I2C_SmBus_Mode_Type mode, confirm_state new_state) {
    switch (mode) {
        case I2C_SmBus_Mode_DEVICE:
            I2C_x->ctrl1_bit.devaddren = new_state;
            break;

        case I2C_SmBus_Mode_HOST:
            I2C_x->ctrl1_bit.haddren = new_state;
            break;

        default:
            break;
    }
}

/**
  * @brief  enable or disable peripheral.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl1_bit.i2cen = new_state;
}

/**
  * @brief  enable or disable clock stretch.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Clock_Stretch_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl1_bit.stretch = (!new_state);
}

/**
  * @brief  enable or disable ack.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void I2C_ACK_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl2_bit.nacken  = (!new_state);
}

/**
  * @brief  enable or disable 10-bit address mode (master transfer).
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Addr10_Mode_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl2_bit.addr10 = new_state;
}

/**
  * @brief  config the slave address to be transmitted.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  address: slave address.
  * @retval 无
  */
void I2C_Transfer_Addr_Set(I2C_Type *I2C_x, uint16_t address) {
    I2C_x->ctrl2_bit.saddr = address & 0x03FF;
}

/**
  * @brief  get the slave address to be transmitted.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @retval slave address
  */
uint16_t I2C_Transfer_Addr_Get(I2C_Type *I2C_x) {
    return I2C_x->ctrl2_bit.saddr;
}

/**
  * @brief  config the master transfer direction.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  I2C_direction: transfer request direction.
  *         该参数可以是以下值之一:
  *         - I2C_Dir_Transmit: master 请求写入传输.
  *         - I2C_Dir_Receive: master 请求读取传输.
  * @retval 无
  */
void I2C_Transfer_Dir_Set(I2C_Type *I2C_x, I2C_Transfer_Dir_Type I2C_direction) {
    I2C_x->ctrl2_bit.dir = I2C_direction;
}

/**
  * @brief  slave get the i2c transfer direction.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @retval the value of the slave direction
  *         - I2C_Dir_Transmit: master 请求写入传输, slave enters receiver mode.
  *         - I2C_Dir_Receive: master 请求读取传输, slave enters transmitter mode.
  */
I2C_Transfer_Dir_Type I2C_Transfer_Dir_Get(I2C_Type *I2C_x) {
    if (I2C_x->sts_bit.sdir == 0) {
        return I2C_Dir_Transmit;
    } else {
        return I2C_Dir_Receive;
    }
}

/**
  * @brief  get the i2c slave matched address.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @retval slave matched address.
  */
uint8_t I2C_Matched_Addr_Get(I2C_Type *I2C_x) {
    return (I2C_x->sts_bit.addr << 1);
}

/**
  * @brief  enable or disable auto send stop mode.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Auto_Stop_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl2_bit.astopen = new_state;
}

/**
  * @brief  enable or disable cnt reload mode.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Reload_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl2_bit.rlden = new_state;
}

/**
  * @brief  config the transfer cnt .
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  cnt: transfer cnt.
  * @retval 无
  */
void I2C_CNT_Set(I2C_Type *I2C_x, uint8_t cnt) {
    I2C_x->ctrl2_bit.cnt = cnt;
}

/**
  * @brief  enable or disable read 10-bit header, this mode
  *         only used in 10-bit address mode read.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Addr10_header_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl2_bit.readh10 = new_state;
}

/**
  * @brief  enable or 禁用常规呼叫模式.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_General_Call_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl1_bit.gcaen = new_state;
}

/**
  * @brief  drives the smbus alert pin high or low.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  level
  *         该参数可以是以下值之一:
  *         - I2C_SmBus_Alert_LOW: smbus alert set low.
  *         - I2C_SmBus_Alert_HIGH: smbus alert set high.
  * @retval 无
  */
void I2C_SmBus_Alert_Set(I2C_Type *I2C_x, I2C_SmBus_Alert_Set_Type level) {
    I2C_x->ctrl1_bit.smbalert = level;
}

/**
  * @brief  enable or disable slave data control.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Slave_Data_Ctrl_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl1_bit.sctrl = new_state;
}

/**
  * @brief  enable or disable pec calculate.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_PEC_Calculate_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl1_bit.pecen = new_state;
}

/**
  * @brief  enable or disable pec transfer.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_PEC_Transmit_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->ctrl2_bit.pecten = new_state;
}

/**
  * @brief  get the i2c pec value.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @retval the value of the pec.
  */
uint8_t I2C_PEC_Value_Get(I2C_Type *I2C_x) {
    return (uint8_t)(I2C_x->pec_bit.pecval);
}

/**
  * @brief  config the i2c bus timeout.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  timeout: timeout (0x0000~0x0FFF).
  * @retval 无
  */
void I2C_TimeOut_Set(I2C_Type *I2C_x, uint16_t timeout) {
    I2C_x->timeout_bit.totime = timeout;
}

/**
  * @brief  config the bus timeout detcet level.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  level
  *         该参数可以是以下值之一:
  *         - I2C_TimeOut_Detcet_HIGH: detect high level timeout.
  *         - I2C_TimeOut_Detcet_LOW: detect low level timeout.
  * @retval 无
  */
void I2C_TimeOut_Detcet_Set(I2C_Type *I2C_x, I2C_TimeOut_Detcet_Type mode) {
    I2C_x->timeout_bit.tomode = mode;
}

/**
  * @brief  enable or disable bus timeout.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_TimeOut_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->timeout_bit.toen = new_state;
}

/**
  * @brief  config the i2c extend bus timeout.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  timeout: extend timeout (0x0000~0x0FFF).
  * @retval 无
  */
void I2C_Ext_TimeOut_Set(I2C_Type *I2C_x, uint16_t timeout) {
    I2C_x->timeout_bit.exttime = timeout;
}

/**
  * @brief  enable or disable extend bus timeout.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Ext_TimeOut_Enable(I2C_Type *I2C_x, confirm_state new_state) {
    I2C_x->timeout_bit.exten = new_state;
}

/**
  * @brief  enable or disable interrupts.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  I2C_int: interrupts sources.
  *         该参数可以是以下值之一:
  *         - I2C_TD_INT: transmit data interrupt.
  *         - I2C_RD_INT: receive data interrupt.
  *         - I2C_Addr_INT: address match interrupt.
  *         - I2C_ACKFIAL_INT: ack fail interrupt.
  *         - I2C_Stop_INT: stop detect interrupt.
  *         - I2C_TDC_INT:  transmit data complete interrupt.
  *         - I2C_ERR_INT: bus error interrupt.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_Interrupt_Enable(I2C_Type *I2C_x, uint32_t source, confirm_state new_state) {
    if (new_state != FALSE) {
        I2C_x->ctrl1 |= source;
    } else {
        I2C_x->ctrl1 &= (uint32_t)~source;
    }
}

/**
  * @brief  get interrupt status
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  source
  *         该参数可以是以下值之一:
  *         - I2C_TD_INT: transmit data interrupt.
  *         - I2C_RD_INT: receive data interrupt.
  *         - I2C_Addr_INT: address match interrupt.
  *         - I2C_ACKFIAL_INT: ack fail interrupt.
  *         - I2C_Stop_INT: stop detect interrupt.
  *         - I2C_TDC_INT:  transmit data complete interrupt.
  *         - I2C_ERR_INT: bus error interrupt.
  * @retval flag_status (SET or RESET)
  */
flag_status I2C_Interrupt_Get(I2C_Type *I2C_x, uint16_t source) {
    if((I2C_x->ctrl1 & source) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  enable or disable dma requests.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  DMA_req: dma transfer request.
  *         该参数可以是以下值之一:
  *         - I2C_DMA_Request_TX: dma transmit request.
  *         - I2C_DMA_Request_RX: dma receive request.
  * @param  new_state (TRUE or FALSE).
  * @retval 无
  */
void I2C_DMA_Enable(I2C_Type *I2C_x, I2C_DMA_Request_Type DMA_req, confirm_state new_state) {
    if(DMA_req == I2C_DMA_Request_TX) {
        I2C_x->ctrl1_bit.dmaten = new_state;
    } else {
        I2C_x->ctrl1_bit.dmaren = new_state;
    }
}

/**
  * @brief  config data transfer.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  address: slave address.
  * @param  cnt: transfer conuter(0~255)
  * @param  rld_stop: config reload and gen stop condition mode.
  *         该参数可以是以下值之一:
  *         - I2C_Auto_Stop_Mode: auto generate stop mode.
  *         - I2C_SOFT_Stop_Mode: soft generate stop mode.
  *         - I2C_Reload_Mode:  reload mode.
  * @param  start: config gen start condition mode.
  *         该参数可以是以下值之一:
  *         - I2C_WITHOUT_Start: transfer data without start condition.
  *         - I2C_Gen_Start_Read: read data and generate start.
  *         - I2C_Gen_Start_Write: send data and generate start.
  * @retval 无
  */
void I2C_Transmit_Set(I2C_Type *I2C_x, uint16_t address, uint8_t cnt, I2C_Reload_Stop_Mode_Type rld_stop, I2C_Start_Mode_Type start) {
    uint32_t temp;

    /* copy ctrl2 value to temp */
    temp = I2C_x->ctrl2;

    /* clear ctrl2_bit specific bits */
    temp &= ~0x03FF67FF;

    /* transfer mode and address set */
    temp |= address | rld_stop | start;

    /* transfer counter set */
    temp |= (uint32_t)cnt << 16;

    /* update ctrl2 value */
    I2C_x->ctrl2 = temp;
}

/**
  * @brief  generate start condition.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @retval 无
  */
void I2C_Start_Generate(I2C_Type *I2C_x) {
    I2C_x->ctrl2_bit.genstart = TRUE;
}

/**
  * @brief  generate stop condition.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @retval 无
  */
void I2C_Stop_Generate(I2C_Type *I2C_x) {
    I2C_x->ctrl2_bit.genstop = TRUE;
}

/**
  * @brief  send a byte through the i2c periph.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  data: byte to be transmitted.
  * @retval 无
  */
void I2C_Data_Send(I2C_Type *I2C_x, uint8_t data) {
    I2C_x->txdt = data;
}

/**
  * @brief  receive a byte through the i2c periph.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @retval the value of the received data.
  */
uint8_t I2C_Data_Receive(I2C_Type *I2C_x) {
    return (uint8_t)I2C_x->rxdt;
}

/**
  * @brief  get flag status.
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  flag: 指定flag to check.
  *         该参数可以是以下值之一:
  *         - I2C_TDBE_FLAG: transmit data buffer empty flag.
  *         - I2C_TDIS_FLAG: send interrupt status.
  *         - I2C_RDBF_FLAG: receive data buffer full flag.
  *         - I2C_AddrF_FLAG: 0~7 bit address match flag.
  *         - I2C_ACKFAIL_FLAG: acknowledge failure flag.
  *         - I2C_STOPF_FLAG: stop condition generation complete flag.
  *         - I2C_TDC_FLAG: transmit data complete flag.
  *         - I2C_TCRLD_FLAG: transmission is complete, waiting to load data.
  *         - I2C_BUSERR_FLAG: bus error flag.
  *         - I2C_ARLOST_FLAG: arbitration lost flag.
  *         - I2C_OUF_FLAG: overflow or underflow flag.
  *         - I2C_PECERR_FLAG: pec receive error flag.
  *         - I2C_TMOUT_FLAG: smbus timeout flag.
  *         - I2C_ALERTF_FLAG: smbus alert flag.
  *         - I2C_BUSYF_FLAG: bus busy flag transmission mode.
  *         - I2C_SDIR_FLAG: slave data transmit direction.
  * @retval the new state of flag (SET or RESET).
  */
flag_status I2C_Flag_Get(I2C_Type *I2C_x, uint32_t flag) {
    if((I2C_x->sts & flag) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  clear flag status
  * @param  I2C_x: to select the i2c peripheral.
  *         该参数可以是以下值之一:
  *         I2C1, I2C2, I2C3.
  * @param  flag: 指定flag to clear.
  *         该参数可以是以下值的任意组合:
  *         - I2C_AddrF_FLAG: 0~7 bit address match flag.
  *         - I2C_ACKFAIL_FLAG: acknowledge failure flag.
  *         - I2C_STOPF_FLAG: stop condition generation complete flag.
  *         - I2C_BUSERR_FLAG: bus error flag.
  *         - I2C_ARLOST_FLAG: arbitration lost flag.
  *         - I2C_OUF_FLAG: overflow or underflow flag.
  *         - I2C_PECERR_FLAG: pec receive error flag.
  *         - I2C_TMOUT_FLAG: smbus timeout flag.
  *         - I2C_ALERTF_FLAG: smbus alert flag.
  * @retval 无
  */
void I2C_Flag_Clear(I2C_Type *I2C_x, uint32_t flag) {
    I2C_x->clr = flag;
}

#endif
