/**
  **************************************************************************
  * @file     at32f435_437_dma.c
  * @brief    contains all the functions for the dma firmware library
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

/** @defgroup DMA
  * @brief DMA driver modules
  */

#ifdef DMA_MODULE_EnableD

/** @defgroup DMA_private_functions
  */

/**
  * @brief  reset dmax channely register.
  * @param  dmax_Channely:
  *         该参数可以是以下值之一:
  *         - DMA1_ChanneL1
  *         - DMA1_ChanneL2
  *         - DMA1_ChanneL3
  *         - DMA1_ChanneL4
  *         - DMA1_ChanneL5
  *         - DMA1_ChanneL6
  *         - DMA1_ChanneL7
  *         - DMA2_ChanneL1
  *         - DMA2_ChanneL2
  *         - DMA2_ChanneL3
  *         - DMA2_ChanneL4
  *         - DMA2_ChanneL5
  *         - DMA2_ChanneL6
  *         - DMA2_ChanneL7
  * @retval 无.
  */
void DMA_Reset(DMA_Channel_Type *dmax_Channely) {
    uint32_t temp = 0;
    dmax_Channely->ctrl_bit.chen = FALSE;
    dmax_Channely->ctrl = 0;
    dmax_Channely->dtcnt = 0;
    dmax_Channely->paddr = 0;
    dmax_Channely->maddr = 0;

    temp = (uint32_t)dmax_Channely;

    if((temp & 0x6FF) < 0x608) {
        /* dma1 channel */
        DMA1->clr |= (uint32_t)(0x0F << ((((temp & 0xFF) - 0x08) / 0x14) * 4));
    } else if((temp & 0x6FF) < 0x688) {
        /* dma2 channel */
        DMA2->clr |= (uint32_t)(0x0F << ((((temp & 0xFF) - 0x08) / 0x14) * 4));
    }
}

/**
  * @brief  set the number of data to be transferred.
  * @param  dmax_Channely:
  *         该参数可以是以下值之一:
  *         - DMA1_ChanneL1
  *         - DMA1_ChanneL2
  *         - DMA1_ChanneL3
  *         - DMA1_ChanneL4
  *         - DMA1_ChanneL5
  *         - DMA1_ChanneL6
  *         - DMA1_ChanneL7
  *         - DMA2_ChanneL1
  *         - DMA2_ChanneL2
  *         - DMA2_ChanneL3
  *         - DMA2_ChanneL4
  *         - DMA2_ChanneL5
  *         - DMA2_ChanneL6
  *         - DMA2_ChanneL7
  * @param  data_Number: the number of data to be transferred (0x0000~0xFFFF).
  * @retval 无.
  */
void DMA_Data_Number_Set(DMA_Channel_Type *dmax_Channely, uint16_t data_Number) {
    dmax_Channely->dtcnt = data_Number;
}

/**
  * @brief  get the number of data to be transferred.
  * @param  dmax_Channely:
  *         该参数可以是以下值之一:
  *         - DMA1_ChanneL1
  *         - DMA1_ChanneL2
  *         - DMA1_ChanneL3
  *         - DMA1_ChanneL4
  *         - DMA1_ChanneL5
  *         - DMA1_ChanneL6
  *         - DMA1_ChanneL7
  *         - DMA2_ChanneL1
  *         - DMA2_ChanneL2
  *         - DMA2_ChanneL3
  *         - DMA2_ChanneL4
  *         - DMA2_ChanneL5
  *         - DMA2_ChanneL6
  *         - DMA2_ChanneL7
  * @retval the number value.
  */
uint16_t DMA_Data_Number_Get(DMA_Channel_Type *dmax_Channely) {
    return (uint16_t)dmax_Channely->dtcnt;
}

/**
  * @brief  enable or disable dma interrupt.
  * @param  dmax_Channely:
  *         该参数可以是以下值之一:
  *         - DMA1_ChanneL1
  *         - DMA1_ChanneL2
  *         - DMA1_ChanneL3
  *         - DMA1_ChanneL4
  *         - DMA1_ChanneL5
  *         - DMA1_ChanneL6
  *         - DMA1_ChanneL7
  *         - DMA2_ChanneL1
  *         - DMA2_ChanneL2
  *         - DMA2_ChanneL3
  *         - DMA2_ChanneL4
  *         - DMA2_ChanneL5
  *         - DMA2_ChanneL6
  *         - DMA2_ChanneL7
  * @param  DMA_int:
  *         该参数可以是以下值的任意组合:
  *         - DMA_FDT_INT
  *         - DMA_HDT_INT
  *         - DMA_DTERR_INT
  * @param  new_state (TRUE or FALSE)
  * @retval 无.
  */
void DMA_Interrupt_Enable(DMA_Channel_Type *dmax_Channely, uint32_t DMA_int, confirm_state new_state) {
    if(new_state != FALSE) {
        dmax_Channely->ctrl |= DMA_int;
    } else {
        dmax_Channely->ctrl &= ~DMA_int;
    }
}

/**
  * @brief  enable or disable dma channel.
  * @param  dmax_Channely:
  *         该参数可以是以下值之一:
  *         - DMA1_ChanneL1
  *         - DMA1_ChanneL2
  *         - DMA1_ChanneL3
  *         - DMA1_ChanneL4
  *         - DMA1_ChanneL5
  *         - DMA1_ChanneL6
  *         - DMA1_ChanneL7
  *         - DMA2_ChanneL1
  *         - DMA2_ChanneL2
  *         - DMA2_ChanneL3
  *         - DMA2_ChanneL4
  *         - DMA2_ChanneL5
  *         - DMA2_ChanneL6
  *         - DMA2_ChanneL7
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void DMA_Channel_Enable(DMA_Channel_Type *dmax_Channely, confirm_state new_state) {
    dmax_Channely->ctrl_bit.chen = new_state;
}

/**
  * @brief  dma flag get.
  * @param  DMA_flag
  *         - DMA1_GL1_FLAG        - DMA1_FDT1_FLAG        - DMA1_HDT1_FLAG        - DMA1_DTERR1_FLAG
  *         - DMA1_GL2_FLAG        - DMA1_FDT2_FLAG        - DMA1_HDT2_FLAG        - DMA1_DTERR2_FLAG
  *         - DMA1_GL3_FLAG        - DMA1_FDT3_FLAG        - DMA1_HDT3_FLAG        - DMA1_DTERR3_FLAG
  *         - DMA1_GL4_FLAG        - DMA1_FDT4_FLAG        - DMA1_HDT4_FLAG        - DMA1_DTERR4_FLAG
  *         - DMA1_GL5_FLAG        - DMA1_FDT5_FLAG        - DMA1_HDT5_FLAG        - DMA1_DTERR5_FLAG
  *         - DMA1_GL6_FLAG        - DMA1_FDT6_FLAG        - DMA1_HDT6_FLAG        - DMA1_DTERR6_FLAG
  *         - DMA1_GL7_FLAG        - DMA1_FDT7_FLAG        - DMA1_HDT7_FLAG        - DMA1_DTERR7_FLAG
  *         - DMA2_GL1_FLAG        - DMA2_FDT1_FLAG        - DMA2_HDT1_FLAG        - DMA2_DTERR1_FLAG
  *         - DMA2_GL2_FLAG        - DMA2_FDT2_FLAG        - DMA2_HDT2_FLAG        - DMA2_DTERR2_FLAG
  *         - DMA2_GL3_FLAG        - DMA2_FDT3_FLAG        - DMA2_HDT3_FLAG        - DMA2_DTERR3_FLAG
  *         - DMA2_GL4_FLAG        - DMA2_FDT4_FLAG        - DMA2_HDT4_FLAG        - DMA2_DTERR4_FLAG
  *         - DMA2_GL5_FLAG        - DMA2_FDT5_FLAG        - DMA2_HDT5_FLAG        - DMA2_DTERR5_FLAG
  *         - DMA2_GL6_FLAG        - DMA2_FDT6_FLAG        - DMA2_HDT6_FLAG        - DMA2_DTERR6_FLAG
  *         - DMA2_GL7_FLAG        - DMA2_FDT7_FLAG        - DMA2_HDT7_FLAG        - DMA2_DTERR7_FLAG
  * @retval state of dma flag.
  */
flag_status DMA_Flag_Get(uint32_t dmax_flag) {
    uint32_t temp = 0;

    if(dmax_flag > 0x10000000) {
        temp = DMA2->sts;
    } else {
        temp = DMA1->sts;
    }

    if((temp & dmax_flag) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  dma flag clear.
  * @param  DMA_flag
  *         该参数可以是以下值之一:
  *         - DMA1_GL1_FLAG        - DMA1_FDT1_FLAG        - DMA1_HDT1_FLAG        - DMA1_DTERR1_FLAG
  *         - DMA1_GL2_FLAG        - DMA1_FDT2_FLAG        - DMA1_HDT2_FLAG        - DMA1_DTERR2_FLAG
  *         - DMA1_GL3_FLAG        - DMA1_FDT3_FLAG        - DMA1_HDT3_FLAG        - DMA1_DTERR3_FLAG
  *         - DMA1_GL4_FLAG        - DMA1_FDT4_FLAG        - DMA1_HDT4_FLAG        - DMA1_DTERR4_FLAG
  *         - DMA1_GL5_FLAG        - DMA1_FDT5_FLAG        - DMA1_HDT5_FLAG        - DMA1_DTERR5_FLAG
  *         - DMA1_GL6_FLAG        - DMA1_FDT6_FLAG        - DMA1_HDT6_FLAG        - DMA1_DTERR6_FLAG
  *         - DMA1_GL7_FLAG        - DMA1_FDT7_FLAG        - DMA1_HDT7_FLAG        - DMA1_DTERR7_FLAG
  *         - DMA2_GL1_FLAG        - DMA2_FDT1_FLAG        - DMA2_HDT1_FLAG        - DMA2_DTERR1_FLAG
  *         - DMA2_GL2_FLAG        - DMA2_FDT2_FLAG        - DMA2_HDT2_FLAG        - DMA2_DTERR2_FLAG
  *         - DMA2_GL3_FLAG        - DMA2_FDT3_FLAG        - DMA2_HDT3_FLAG        - DMA2_DTERR3_FLAG
  *         - DMA2_GL4_FLAG        - DMA2_FDT4_FLAG        - DMA2_HDT4_FLAG        - DMA2_DTERR4_FLAG
  *         - DMA2_GL5_FLAG        - DMA2_FDT5_FLAG        - DMA2_HDT5_FLAG        - DMA2_DTERR5_FLAG
  *         - DMA2_GL6_FLAG        - DMA2_FDT6_FLAG        - DMA2_HDT6_FLAG        - DMA2_DTERR6_FLAG
  *         - DMA2_GL7_FLAG        - DMA2_FDT7_FLAG        - DMA2_HDT7_FLAG        - DMA2_DTERR7_FLAG
  * @retval 无.
  */
void DMA_Flag_Clear(uint32_t dmax_flag) {
    if(dmax_flag > ((uint32_t)0x10000000)) {
        DMA2->clr = (uint32_t)(dmax_flag & 0x0FFFFFFF);
    } else {
        DMA1->clr = dmax_flag;
    }
}

/**
  * @brief  dma init config with its default value.
  * @param  DMA_Init_struct: pointer to a DMA_Init_Type structure which will be initialized.
  * @retval 无.
  */
void DMA_Default_Para_Init(DMA_Init_Type *DMA_Init_struct) {
    DMA_Init_struct->Peripheral_Base_Addr = 0;
    DMA_Init_struct->Memory_Base_Addr = 0;
    DMA_Init_struct->direction = DMA_Dir_PERIPHERAL_To_MEMORY;
    DMA_Init_struct->Buffer_Size = 0;
    DMA_Init_struct->Peripheral_Inc_Enable = FALSE;
    DMA_Init_struct->Memory_Inc_Enable = FALSE;
    DMA_Init_struct->Peripheral_Data_Width = DMA_Peripheral_Data_Width_BYTE;
    DMA_Init_struct->Memory_Data_Width = DMA_Memory_Data_Width_BYTE;
    DMA_Init_struct->Loop_Mode_Enable = FALSE;
    DMA_Init_struct->priority = DMA_Priority_LOW;
}

/**
  * @brief  dma init.
  * @param  dmax_Channely:
  *         该参数可以是以下值之一:
  *         - DMA1_ChanneL1
  *         - DMA1_ChanneL2
  *         - DMA1_ChanneL3
  *         - DMA1_ChanneL4
  *         - DMA1_ChanneL5
  *         - DMA1_ChanneL6
  *         - DMA1_ChanneL7
  *         - DMA2_ChanneL1
  *         - DMA2_ChanneL2
  *         - DMA2_ChanneL3
  *         - DMA2_ChanneL4
  *         - DMA2_ChanneL5
  *         - DMA2_ChanneL6
  *         - DMA2_ChanneL7
  * @param  DMA_Init_struct: pointer to a DMA_Init_Type structure.
  * @retval 无.
  */
void DMA_Init(DMA_Channel_Type *dmax_Channely, DMA_Init_Type *DMA_Init_struct) {
    /* clear ctrl register dtd bit and m2m bit */
    dmax_Channely->ctrl &= 0xbfef;
    dmax_Channely->ctrl |= DMA_Init_struct->direction;

    dmax_Channely->ctrl_bit.chpl = DMA_Init_struct->priority;
    dmax_Channely->ctrl_bit.mwidth = DMA_Init_struct->Memory_Data_Width;
    dmax_Channely->ctrl_bit.pwidth = DMA_Init_struct->Peripheral_Data_Width;
    dmax_Channely->ctrl_bit.mincm = DMA_Init_struct->Memory_Inc_Enable;
    dmax_Channely->ctrl_bit.pincm = DMA_Init_struct->Peripheral_Inc_Enable;
    dmax_Channely->ctrl_bit.lm = DMA_Init_struct->Loop_Mode_Enable;
    dmax_Channely->dtcnt_bit.cnt = DMA_Init_struct->Buffer_Size;
    dmax_Channely->paddr = DMA_Init_struct->Peripheral_Base_Addr;
    dmax_Channely->maddr = DMA_Init_struct->Memory_Base_Addr;
}
/**
  * @brief  dmamux init.
  * @param  DMA_x: pointer to a DMA_Type structure, can be DMA1 or DMA2.
  * @param  DMAMUX_Channelx:
  *         该参数可以是以下值之一:
  *         - DMA1MUX_ChanneL1
  *         - DMA1MUX_ChanneL2
  *         - DMA1MUX_ChanneL3
  *         - DMA1MUX_ChanneL4
  *         - DMA1MUX_ChanneL5
  *         - DMA1MUX_ChanneL6
  *         - DMA1MUX_ChanneL7
  *         - DMA2MUX_ChanneL1
  *         - DMA2MUX_ChanneL2
  *         - DMA2MUX_ChanneL3
  *         - DMA2MUX_ChanneL4
  *         - DMA2MUX_ChanneL5
  *         - DMA2MUX_ChanneL6
  *         - DMA2MUX_ChanneL7
  * @param  DMAMUX_req_sel:
  *         该参数可以是以下值之一:
  *         - DMAMUX_DMAREQ_ID_REQ_G1       - DMAMUX_DMAREQ_ID_REQ_G2       - DMAMUX_DMAREQ_ID_REQ_G3       - DMAMUX_DMAREQ_ID_REQ_G4
  *         - DMAMUX_DMAREQ_ID_ADC1         - DMAMUX_DMAREQ_ID_ADC2         - DMAMUX_DMAREQ_ID_ADC3         - DMAMUX_DMAREQ_ID_DAC1
  *         - DMAMUX_DMAREQ_ID_DAC2         - DMAMUX_DMAREQ_ID_TMR6_OVERFLOW- DMAMUX_DMAREQ_ID_TMR7_OVERFLOW- DMAMUX_DMAREQ_ID_SPI1_RX
  *         - DMAMUX_DMAREQ_ID_SPI1_TX      - DMAMUX_DMAREQ_ID_SPI2_RX      - DMAMUX_DMAREQ_ID_SPI2_TX      - DMAMUX_DMAREQ_ID_SPI3_RX
  *         - DMAMUX_DMAREQ_ID_SPI3_TX      - DMAMUX_DMAREQ_ID_SPI4_RX      - DMAMUX_DMAREQ_ID_SPI4_TX      - DMAMUX_DMAREQ_ID_I2S2_Ext_RX
  *         - DMAMUX_DMAREQ_ID_I2S2_Ext_TX  - DMAMUX_DMAREQ_ID_I2S3_Ext_RX  - DMAMUX_DMAREQ_ID_I2S3_Ext_TX  - DMAMUX_DMAREQ_ID_I2C1_RX
  *         - DMAMUX_DMAREQ_ID_I2C1_TX      - DMAMUX_DMAREQ_ID_I2C2_RX      - DMAMUX_DMAREQ_ID_I2C2_TX      - DMAMUX_DMAREQ_ID_I2C3_RX
  *         - DMAMUX_DMAREQ_ID_I2C3_TX      - DMAMUX_DMAREQ_ID_USART1_RX    - DMAMUX_DMAREQ_ID_USART1_TX    - DMAMUX_DMAREQ_ID_USART2_RX
  *         - DMAMUX_DMAREQ_ID_USART2_TX    - DMAMUX_DMAREQ_ID_USART3_RX    - DMAMUX_DMAREQ_ID_USART3_TX    - DMAMUX_DMAREQ_ID_UART4_RX
  *         - DMAMUX_DMAREQ_ID_UART4_TX     - DMAMUX_DMAREQ_ID_UART5_RX     - DMAMUX_DMAREQ_ID_UART5_TX     - DMAMUX_DMAREQ_ID_USART6_RX
  *         - DMAMUX_DMAREQ_ID_USART6_TX    - DMAMUX_DMAREQ_ID_UART7_RX     - DMAMUX_DMAREQ_ID_UART7_TX     - DMAMUX_DMAREQ_ID_UART8_RX
  *         - DMAMUX_DMAREQ_ID_UART8_TX     - DMAMUX_DMAREQ_ID_SDIO1        - DMAMUX_DMAREQ_ID_SDIO2        - DMAMUX_DMAREQ_ID_QSPI1
  *         - DMAMUX_DMAREQ_ID_QSPI2        - DMAMUX_DMAREQ_ID_TMR1_CH1     - DMAMUX_DMAREQ_ID_TMR1_CH2     - DMAMUX_DMAREQ_ID_TMR1_CH3
  *         - DMAMUX_DMAREQ_ID_TMR1_CH4     - DMAMUX_DMAREQ_ID_TMR1_OVERFLOW- DMAMUX_DMAREQ_ID_TMR1_TRIG    - DMAMUX_DMAREQ_ID_TMR1_COM
  *         - DMAMUX_DMAREQ_ID_TMR8_CH1     - DMAMUX_DMAREQ_ID_TMR8_CH2     - DMAMUX_DMAREQ_ID_TMR8_CH3     - DMAMUX_DMAREQ_ID_TMR8_CH4
  *         - DMAMUX_DMAREQ_ID_TMR8_UP      - DMAMUX_DMAREQ_ID_TMR8_TRIG    - DMAMUX_DMAREQ_ID_TMR8_COM     - DMAMUX_DMAREQ_ID_TMR2_CH1
  *         - DMAMUX_DMAREQ_ID_TMR2_CH2     - DMAMUX_DMAREQ_ID_TMR2_CH3     - DMAMUX_DMAREQ_ID_TMR2_CH4     - DMAMUX_DMAREQ_ID_TMR2_OVERFLOW
  *         - DMAMUX_DMAREQ_ID_TMR2_TRIG    - DMAMUX_DMAREQ_ID_TMR3_CH1     - DMAMUX_DMAREQ_ID_TMR3_CH2     - DMAMUX_DMAREQ_ID_TMR3_CH3
  *         - DMAMUX_DMAREQ_ID_TMR3_CH4     - DMAMUX_DMAREQ_ID_TMR3_OVERFLOW- DMAMUX_DMAREQ_ID_TMR3_TRIG    - DMAMUX_DMAREQ_ID_TMR4_CH1
  *         - DMAMUX_DMAREQ_ID_TMR4_CH2     - DMAMUX_DMAREQ_ID_TMR4_CH3     - DMAMUX_DMAREQ_ID_TMR4_CH4     - DMAMUX_DMAREQ_ID_TMR4_OVERFLOW
  *         - DMAMUX_DMAREQ_ID_TMR4_TRIG    - DMAMUX_DMAREQ_ID_TMR5_CH1     - DMAMUX_DMAREQ_ID_TMR5_CH2     - DMAMUX_DMAREQ_ID_TMR5_CH3
  *         - DMAMUX_DMAREQ_ID_TMR5_CH4     - DMAMUX_DMAREQ_ID_TMR5_OVERFLOW- DMAMUX_DMAREQ_ID_TMR5_TRIG    - DMAMUX_DMAREQ_ID_TMR20_CH1
  *         - DMAMUX_DMAREQ_ID_TMR20_CH2    - DMAMUX_DMAREQ_ID_TMR20_CH3    - DMAMUX_DMAREQ_ID_TMR20_CH4    - DMAMUX_DMAREQ_ID_TMR20_OVERFLOW
  *         - DMAMUX_DMAREQ_ID_TMR20_TRIG   - DMAMUX_DMAREQ_ID_TMR20_HALL   - DMAMUX_DMAREQ_ID_DVP
  * @retval 无.
  */
void DMA_Flexible_Config(DMA_Type* DMA_x, DMAMUX_Channel_Type *DMAMUX_Channelx, DMAMUX_Requst_ID_sel_Type DMAMUX_req_sel) {
    DMA_x->muxsel_bit.tblsel = TRUE;
    DMAMUX_Channelx->muxctrl_bit.reqsel = DMAMUX_req_sel;
}

/**
  * @brief  enable or disable the dmamux.
  * @param  DMA_x: pointer to a DMA_Type structure, can be DMA1 or DMA2.
  * @param  new_state (TRUE or FALSE) .
  * @retval 无.
  */
void DMAMUX_Enable(DMA_Type *DMA_x, confirm_state new_state) {
    DMA_x->muxsel_bit.tblsel = new_state;
}

/**
  * @brief  dmamux init.
  * @param  DMAMUX_Channelx:
  *         该参数可以是以下值之一:
  *         - DMA1MUX_ChanneL1
  *         - DMA1MUX_ChanneL2
  *         - DMA1MUX_ChanneL3
  *         - DMA1MUX_ChanneL4
  *         - DMA1MUX_ChanneL5
  *         - DMA1MUX_ChanneL6
  *         - DMA1MUX_ChanneL7
  *         - DMA2MUX_ChanneL1
  *         - DMA2MUX_ChanneL2
  *         - DMA2MUX_ChanneL3
  *         - DMA2MUX_ChanneL4
  *         - DMA2MUX_ChanneL5
  *         - DMA2MUX_ChanneL6
  *         - DMA2MUX_ChanneL7
  * @param  DMAMUX_req_sel:
  *         该参数可以是以下值之一:
  *         - DMAMUX_DMAREQ_ID_REQ_G1       - DMAMUX_DMAREQ_ID_REQ_G2       - DMAMUX_DMAREQ_ID_REQ_G3       - DMAMUX_DMAREQ_ID_REQ_G4
  *         - DMAMUX_DMAREQ_ID_ADC1         - DMAMUX_DMAREQ_ID_ADC2         - DMAMUX_DMAREQ_ID_ADC3         - DMAMUX_DMAREQ_ID_DAC1
  *         - DMAMUX_DMAREQ_ID_DAC2         - DMAMUX_DMAREQ_ID_TMR6_OVERFLOW- DMAMUX_DMAREQ_ID_TMR7_OVERFLOW- DMAMUX_DMAREQ_ID_SPI1_RX
  *         - DMAMUX_DMAREQ_ID_SPI1_TX      - DMAMUX_DMAREQ_ID_SPI2_RX      - DMAMUX_DMAREQ_ID_SPI2_TX      - DMAMUX_DMAREQ_ID_SPI3_RX
  *         - DMAMUX_DMAREQ_ID_SPI3_TX      - DMAMUX_DMAREQ_ID_SPI4_RX      - DMAMUX_DMAREQ_ID_SPI4_TX      - DMAMUX_DMAREQ_ID_I2S2_Ext_RX
  *         - DMAMUX_DMAREQ_ID_I2S2_Ext_TX  - DMAMUX_DMAREQ_ID_I2S3_Ext_RX  - DMAMUX_DMAREQ_ID_I2S3_Ext_TX  - DMAMUX_DMAREQ_ID_I2C1_RX
  *         - DMAMUX_DMAREQ_ID_I2C1_TX      - DMAMUX_DMAREQ_ID_I2C2_RX      - DMAMUX_DMAREQ_ID_I2C2_TX      - DMAMUX_DMAREQ_ID_I2C3_RX
  *         - DMAMUX_DMAREQ_ID_I2C3_TX      - DMAMUX_DMAREQ_ID_USART1_RX    - DMAMUX_DMAREQ_ID_USART1_TX    - DMAMUX_DMAREQ_ID_USART2_RX
  *         - DMAMUX_DMAREQ_ID_USART2_TX    - DMAMUX_DMAREQ_ID_USART3_RX    - DMAMUX_DMAREQ_ID_USART3_TX    - DMAMUX_DMAREQ_ID_UART4_RX
  *         - DMAMUX_DMAREQ_ID_UART4_TX     - DMAMUX_DMAREQ_ID_UART5_RX     - DMAMUX_DMAREQ_ID_UART5_TX     - DMAMUX_DMAREQ_ID_USART6_RX
  *         - DMAMUX_DMAREQ_ID_USART6_TX    - DMAMUX_DMAREQ_ID_UART7_RX     - DMAMUX_DMAREQ_ID_UART7_TX     - DMAMUX_DMAREQ_ID_UART8_RX
  *         - DMAMUX_DMAREQ_ID_UART8_TX     - DMAMUX_DMAREQ_ID_SDIO1        - DMAMUX_DMAREQ_ID_SDIO2        - DMAMUX_DMAREQ_ID_QSPI1
  *         - DMAMUX_DMAREQ_ID_QSPI2        - DMAMUX_DMAREQ_ID_TMR1_CH1     - DMAMUX_DMAREQ_ID_TMR1_CH2     - DMAMUX_DMAREQ_ID_TMR1_CH3
  *         - DMAMUX_DMAREQ_ID_TMR1_CH4     - DMAMUX_DMAREQ_ID_TMR1_OVERFLOW- DMAMUX_DMAREQ_ID_TMR1_TRIG    - DMAMUX_DMAREQ_ID_TMR1_COM
  *         - DMAMUX_DMAREQ_ID_TMR8_CH1     - DMAMUX_DMAREQ_ID_TMR8_CH2     - DMAMUX_DMAREQ_ID_TMR8_CH3     - DMAMUX_DMAREQ_ID_TMR8_CH4
  *         - DMAMUX_DMAREQ_ID_TMR8_UP      - DMAMUX_DMAREQ_ID_TMR8_TRIG    - DMAMUX_DMAREQ_ID_TMR8_COM     - DMAMUX_DMAREQ_ID_TMR2_CH1
  *         - DMAMUX_DMAREQ_ID_TMR2_CH2     - DMAMUX_DMAREQ_ID_TMR2_CH3     - DMAMUX_DMAREQ_ID_TMR2_CH4     - DMAMUX_DMAREQ_ID_TMR2_OVERFLOW
  *         - DMAMUX_DMAREQ_ID_TMR2_TRIG    - DMAMUX_DMAREQ_ID_TMR3_CH1     - DMAMUX_DMAREQ_ID_TMR3_CH2     - DMAMUX_DMAREQ_ID_TMR3_CH3
  *         - DMAMUX_DMAREQ_ID_TMR3_CH4     - DMAMUX_DMAREQ_ID_TMR3_OVERFLOW- DMAMUX_DMAREQ_ID_TMR3_TRIG    - DMAMUX_DMAREQ_ID_TMR4_CH1
  *         - DMAMUX_DMAREQ_ID_TMR4_CH2     - DMAMUX_DMAREQ_ID_TMR4_CH3     - DMAMUX_DMAREQ_ID_TMR4_CH4     - DMAMUX_DMAREQ_ID_TMR4_OVERFLOW
  *         - DMAMUX_DMAREQ_ID_TMR4_TRIG    - DMAMUX_DMAREQ_ID_TMR5_CH1     - DMAMUX_DMAREQ_ID_TMR5_CH2     - DMAMUX_DMAREQ_ID_TMR5_CH3
  *         - DMAMUX_DMAREQ_ID_TMR5_CH4     - DMAMUX_DMAREQ_ID_TMR5_OVERFLOW- DMAMUX_DMAREQ_ID_TMR5_TRIG    - DMAMUX_DMAREQ_ID_TMR20_CH1
  *         - DMAMUX_DMAREQ_ID_TMR20_CH2    - DMAMUX_DMAREQ_ID_TMR20_CH3    - DMAMUX_DMAREQ_ID_TMR20_CH4    - DMAMUX_DMAREQ_ID_TMR20_OVERFLOW
  *         - DMAMUX_DMAREQ_ID_TMR20_TRIG   - DMAMUX_DMAREQ_ID_TMR20_HALL   - DMAMUX_DMAREQ_ID_DVP
  * @retval 无.
  */
void DMAMUX_Init(DMAMUX_Channel_Type *DMAMUX_Channelx, DMAMUX_Requst_ID_sel_Type DMAMUX_req_sel) {
    DMAMUX_Channelx->muxctrl_bit.reqsel = DMAMUX_req_sel;
}

/**
  * @brief  dmamux sync init struct config with its default value.
  * @param  DMAMUX_Sync_Init_struct: pointer to a DMAMUX_Sync_Init_Type structure which will be initialized.
  * @retval 无.
  */
void DMAMUX_Sync_Default_Para_Init(DMAMUX_Sync_Init_Type *DMAMUX_Sync_Init_struct) {
    DMAMUX_Sync_Init_struct->Sync_Enable = FALSE;
    DMAMUX_Sync_Init_struct->Sync_Event_Enable = FALSE;
    DMAMUX_Sync_Init_struct->Sync_Polarity = DMAMUX_Sync_Polarity_Disable;
    DMAMUX_Sync_Init_struct->Sync_Request_Number = 0x0;
    DMAMUX_Sync_Init_struct->Sync_Signal_Sel = (DMAMUX_Sync_ID_sel_Type)0;
}

/**
  * @brief  dmamux synchronization config.
  * @param  DMAMUX_Channelx:
  *         该参数可以是以下值之一:
  *         - DMA1MUX_ChanneL1
  *         - DMA1MUX_ChanneL2
  *         - DMA1MUX_ChanneL3
  *         - DMA1MUX_ChanneL4
  *         - DMA1MUX_ChanneL5
  *         - DMA1MUX_ChanneL6
  *         - DMA1MUX_ChanneL7
  *         - DMA2MUX_ChanneL1
  *         - DMA2MUX_ChanneL2
  *         - DMA2MUX_ChanneL3
  *         - DMA2MUX_ChanneL4
  *         - DMA2MUX_ChanneL5
  *         - DMA2MUX_ChanneL6
  *         - DMA2MUX_ChanneL7
  * @param  DMAMUX_Sync_Init_struct: ointer to a DMAMUX_Sync_Init_Type structure.
  * @retval 无.
  */
void DMAMUX_Sync_Config(DMAMUX_Channel_Type *DMAMUX_Channelx, DMAMUX_Sync_Init_Type *DMAMUX_Sync_Init_struct) {
    DMAMUX_Channelx->muxctrl_bit.syncsel = DMAMUX_Sync_Init_struct->Sync_Signal_Sel;
    DMAMUX_Channelx->muxctrl_bit.syncpol = DMAMUX_Sync_Init_struct->Sync_Polarity;
    DMAMUX_Channelx->muxctrl_bit.reqcnt  = DMAMUX_Sync_Init_struct->Sync_Request_Number;
    DMAMUX_Channelx->muxctrl_bit.evtgen  = DMAMUX_Sync_Init_struct->Sync_Event_Enable;
    DMAMUX_Channelx->muxctrl_bit.syncen  = DMAMUX_Sync_Init_struct->Sync_Enable;
}

/**
  * @brief  dmamux request generator init struct config with its default value.
  * @param  DMAMUX_Gen_Init_struct: pointer to a DMAMUX_Gen_Init_Type structure which will be initialized.
  * @retval 无.
  */
void DMAMUX_Generator_Default_Para_Init(DMAMUX_Gen_Init_Type *DMAMUX_Gen_Init_struct) {
    DMAMUX_Gen_Init_struct->Gen_Enable         = FALSE;
    DMAMUX_Gen_Init_struct->Gen_Polarity       = DMAMUX_Gen_Polarity_Disable;
    DMAMUX_Gen_Init_struct->Gen_Request_Number = 0x0;
    DMAMUX_Gen_Init_struct->Gen_Signal_Sel     = (DMAMUX_Gen_ID_sel_Type)0x0;
}

/**
  * @brief  dmamux request generator init.
  * @param  DMAMUX_Gen_x :
  *         该参数可以是以下值之一:
  *         - DMA1MUX_GENERATOR1
  *         - DMA1MUX_GENERATOR2
  *         - DMA1MUX_GENERATOR3
  *         - DMA1MUX_GENERATOR4
  *         - DMA2MUX_GENERATOR1
  *         - DMA2MUX_GENERATOR2
  *         - DMA2MUX_GENERATOR3
  *         - DMA2MUX_GENERATOR4
  * @param  DMAMUX_Gen_Init_struct: pointer to a DMAMUX_Gen_Init_Type structure which will be initialized.
  * @retval 无.
  */
void DMAMUX_Generator_Config(DMAMUX_Generator_Type *DMAMUX_Gen_x, DMAMUX_Gen_Init_Type *DMAMUX_Gen_Init_struct) {
    DMAMUX_Gen_x->gctrl_bit.sigsel  = DMAMUX_Gen_Init_struct->Gen_Signal_Sel;
    DMAMUX_Gen_x->gctrl_bit.gpol    = DMAMUX_Gen_Init_struct->Gen_Polarity;
    DMAMUX_Gen_x->gctrl_bit.greqcnt = DMAMUX_Gen_Init_struct->Gen_Request_Number;
    DMAMUX_Gen_x->gctrl_bit.gen     = DMAMUX_Gen_Init_struct->Gen_Enable;
}

/**
  * @brief  enable or disable the dmamux sync interrupts.
  * @param  DMAMUX_Channelx:
  *         该参数可以是以下值之一:
  *         - DMA1MUX_ChanneL1
  *         - DMA1MUX_ChanneL2
  *         - DMA1MUX_ChanneL3
  *         - DMA1MUX_ChanneL4
  *         - DMA1MUX_ChanneL5
  *         - DMA1MUX_ChanneL6
  *         - DMA1MUX_ChanneL7
  *         - DMA2MUX_ChanneL1
  *         - DMA2MUX_ChanneL2
  *         - DMA2MUX_ChanneL3
  *         - DMA2MUX_ChanneL4
  *         - DMA2MUX_ChanneL5
  *         - DMA2MUX_ChanneL6
  *         - DMA2MUX_ChanneL7
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void DMAMUX_Sync_Interrupt_Enable(DMAMUX_Channel_Type *DMAMUX_Channelx, confirm_state new_state) {
    if(new_state != FALSE) {
        DMAMUX_Channelx->muxctrl_bit.syncovien = TRUE;
    } else {
        DMAMUX_Channelx->muxctrl_bit.syncovien = FALSE;
    }
}

/**
  * @brief  enable or disable the dmamux request generator interrupts.
  * @param  DMAMUX_Gen_x : pointer to a DMAMUX_Generator_Type structure.
  *         该参数可以是以下值之一:
  *         - DMA1MUX_GENERATOR1
  *         - DMA1MUX_GENERATOR2
  *         - DMA1MUX_GENERATOR3
  *         - DMA1MUX_GENERATOR4
  *         - DMA2MUX_GENERATOR1
  *         - DMA2MUX_GENERATOR2
  *         - DMA2MUX_GENERATOR3
  *         - DMA2MUX_GENERATOR4
  * @param  new_state (TRUE or FALSE).
  * @retval 无.
  */
void DMAMUX_Generator_Interrupt_Enable(DMAMUX_Generator_Type *DMAMUX_Gen_x, confirm_state new_state) {
    if(new_state != FALSE) {
        DMAMUX_Gen_x->gctrl_bit.trgovien = TRUE;
    } else {
        DMAMUX_Gen_x->gctrl_bit.trgovien = FALSE;
    }
}

/**
  * @brief  dmamux sync flag get.
  * @param  DMA_x : pointer to a DMA_Type structure, can be DMA1 or DMA2.
  * @param  flag
  *         该参数可以是以下值的任意组合:
  *         - DMAMUX_Sync_OV1_FLAG
  *         - DMAMUX_Sync_OV2_FLAG
  *         - DMAMUX_Sync_OV3_FLAG
  *         - DMAMUX_Sync_OV4_FLAG
  *         - DMAMUX_Sync_OV5_FLAG
  *         - DMAMUX_Sync_OV6_FLAG
  *         - DMAMUX_Sync_OV7_FLAG
  * @retval state of dmamux sync flag.
  */
flag_status DMAMUX_Sync_Flag_Get(DMA_Type *DMA_x, uint32_t flag) {
    if((DMA_x->muxsyncsts & flag) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  dmamux sync flag clear.
  * @param  DMA_x : pointer to a DMA_Type structure, can be DMA1 or DMA2.
  * @param  flag
  *         该参数可以是以下值的任意组合:
  *         - DMAMUX_Sync_OV1_FLAG
  *         - DMAMUX_Sync_OV2_FLAG
  *         - DMAMUX_Sync_OV3_FLAG
  *         - DMAMUX_Sync_OV4_FLAG
  *         - DMAMUX_Sync_OV5_FLAG
  *         - DMAMUX_Sync_OV6_FLAG
  *         - DMAMUX_Sync_OV7_FLAG
  * @retval 无.
  */
void DMAMUX_Sync_Flag_Clear(DMA_Type *DMA_x, uint32_t flag) {
    DMA_x->muxsyncclr = flag;
}

/**
  * @brief  dmamux request generator flag get.
  * @param  DMA_x : pointer to a DMA_Type structure, can be DMA1 or DMA2.
  * @param  flag
  *         该参数可以是以下值的任意组合:
  *         - DMAMUX_Gen_Trig_OV1_FLAG
  *         - DMAMUX_Gen_Trig_OV2_FLAG
  *         - DMAMUX_Gen_Trig_OV3_FLAG
  *         - DMAMUX_Gen_Trig_OV4_FLAG
  * @retval state of dmamux sync flag.
  */
flag_status DMAMUX_Generator_Flag_Get(DMA_Type *DMA_x, uint32_t flag) {
    if((DMA_x->muxgsts & flag) != RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  dmamux request generator flag clear.
  * @param  DMA_x : pointer to a DMA_Type structure, can be DMA1 or DMA2.
  * @param  flag
  *         该参数可以是以下值的任意组合:
  *         - DMAMUX_Gen_Trig_OV1_FLAG
  *         - DMAMUX_Gen_Trig_OV2_FLAG
  *         - DMAMUX_Gen_Trig_OV3_FLAG
  *         - DMAMUX_Gen_Trig_OV4_FLAG
  * @retval 无.
  */
void DMAMUX_Generator_Flag_Clear(DMA_Type *DMA_x, uint32_t flag) {
    DMA_x->muxgclr = flag;
}

#endif
