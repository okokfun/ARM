/*!
    文件:    gd32f4xx_dci.c
    简介:   DCI driver

    版本: 2016-08-15, V1.0.0, firmware for GD32F4xx
    版本: 2018-12-12, V2.0.0, firmware for GD32F4xx
    版本: 2020-09-30, V2.1.0, firmware for GD32F4xx
    版本: 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx_dci.h"

/*!
    简介:    DCI deinit
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_DeInit(void) {
    RCU_Periph_Reset_Enable(RCU_DCIRST);
    RCU_Periph_Reset_Disable(RCU_DCIRST);
}

/*!
    简介:    initialize DCI registers
    参数[输入]:  DCI_Struct: DCI parameter initialization structure
                members of the structure and the member values are shown as below:
                capture_mode    : DCI_Capture_Mode_CONTINUOUS, DCI_Capture_Mode_SNAPSHOT
                colck_polarity  : DCI_CK_Polarity_FALLING, DCI_CK_Polarity_RISING
                hsync_polarity  : DCI_HSYNC_Polarity_LOW, DCI_HSYNC_Polarity_HIGH
                vsync_polarity  : DCI_VSYNC_Polarity_LOW, DCI_VSYNC_Polarity_HIGH
                frame_rate      : DCI_Frame_RATE_ALL, DCI_Frame_RATE_1_2, DCI_Frame_RATE_1_4
                interface_format: DCI_Interface_FORMAT_8BITS, DCI_Interface_FORMAT_10BITS,
                                      DCI_Interface_FORMAT_12BITS, DCI_Interface_FORMAT_14BITS
    参数[输出]:  无
    返回值:      无
*/
void DCI_Init(DCI_Parameter_Struct *DCI_Struct) {
    uint32_t reg = 0U;
    /* disable capture function and DCI */
    DCI_CTL &= ~(DCI_CTL_CAP | DCI_CTL_DCIEN);
    /* configure DCI parameter */
    reg |= DCI_Struct->capture_mode;
    reg |= DCI_Struct->clock_polarity;
    reg |= DCI_Struct->hsync_polarity;
    reg |= DCI_Struct->vsync_polarity;
    reg |= DCI_Struct->frame_rate;
    reg |= DCI_Struct->interface_format;

    DCI_CTL = reg;
}

/*!
    简介:    enable DCI function
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Enable(void) {
    DCI_CTL |= DCI_CTL_DCIEN;
}

/*!
    简介:    disable DCI function
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Disable(void) {
    DCI_CTL &= ~DCI_CTL_DCIEN;
}

/*!
    简介:    enable DCI capture
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Capture_Enable(void) {
    DCI_CTL |= DCI_CTL_CAP;
}

/*!
    简介:    disable DCI capture
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Capture_Disable(void) {
    DCI_CTL &= ~DCI_CTL_CAP;
}

/*!
    简介:    enable DCI jpeg mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Jpeg_Enable(void) {
    DCI_CTL |= DCI_CTL_JM;
}

/*!
    简介:    disable DCI jpeg mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Jpeg_Disable(void) {
    DCI_CTL &= ~DCI_CTL_JM;
}

/*!
    简介:    enable cropping window function
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Crop_Window_Enable(void) {
    DCI_CTL |= DCI_CTL_WDEN;
}

/*!
    简介:    disable cropping window function
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Crop_Window_Disable(void) {
    DCI_CTL &= ~DCI_CTL_WDEN;
}

/*!
    简介:    configure DCI cropping window
    参数[输入]:  start_x: window horizontal start position
    参数[输入]:  start_y: window vertical start position
    参数[输入]:  size_width: window horizontal size
    参数[输入]:  size_height: window vertical size
    参数[输出]:  无
    返回值:      无
*/
void DCI_Crop_Window_Config(uint16_t start_x, uint16_t start_y, uint16_t size_width, uint16_t size_height) {
    DCI_CWSPOS = ((uint32_t)start_x | ((uint32_t)start_y << 16));
    DCI_CWSZ = ((uint32_t)size_width | ((uint32_t)size_height << 16));
}

/*!
    简介:    enable embedded synchronous mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Embedded_Sync_Enable(void) {
    DCI_CTL |= DCI_CTL_ESM;
}

/*!
    简介:    disble embedded synchronous mode
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void DCI_Embedded_Sync_Disable(void) {
    DCI_CTL &= ~DCI_CTL_ESM;
}
/*!
    简介:    config synchronous codes in embedded synchronous mode
    参数[输入]:  frame_start: frame start code in embedded synchronous mode
    参数[输入]:  line_start: line start code in embedded synchronous mode
    参数[输入]:  line_end: line end code in embedded synchronous mode
    参数[输入]:  frame_end: frame end code in embedded synchronous mode
    参数[输出]:  无
    返回值:      无
*/
void DCI_Sync_Codes_Config(uint8_t frame_start, uint8_t line_start, uint8_t line_end, uint8_t frame_end) {
    DCI_SC = ((uint32_t)frame_start | ((uint32_t)line_start << 8) | ((uint32_t)line_end << 16) | ((uint32_t)frame_end << 24));
}

/*!
    简介:    config synchronous codes unmask in embedded synchronous mode
    参数[输入]:  frame_start: frame start code unmask bits in embedded synchronous mode
    参数[输入]:  line_start: line start code unmask bits in embedded synchronous mode
    参数[输入]:  line_end: line end code unmask bits in embedded synchronous mode
    参数[输入]:  frame_end: frame end code unmask bits in embedded synchronous mode
    参数[输出]:  无
    返回值:      无
*/
void DCI_Sync_Codes_Unmask_Config(uint8_t frame_start, uint8_t line_start, uint8_t line_end, uint8_t frame_end) {
    DCI_SCUMSK = ((uint32_t)frame_start | ((uint32_t)line_start << 8) | ((uint32_t)line_end << 16) | ((uint32_t)frame_end << 24));
}

/*!
    简介:    read DCI data register
    参数[输入]:  无
    参数[输出]:  无
    返回值:     data
*/
uint32_t DCI_Data_Read(void) {
    return DCI_DATA;
}

/*!
    简介:    get specified flag
    参数[输入]:  flag:
      参数:         DCI_Flag_HS: HS line status
      参数:         DCI_Flag_VS: VS line status
      参数:         DCI_Flag_FV: FIFO valid
      参数:         DCI_Flag_EF: end of frame flag
      参数:         DCI_Flag_OVR: FIFO overrun flag
      参数:         DCI_Flag_ESE: embedded synchronous error flag
      参数:         DCI_Flag_VSYNC: vsync flag
      参数:         DCI_Flag_EL: end of line flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus DCI_Flag_Get(uint32_t flag) {
    uint32_t stat = 0U;

    if(flag >> 31) {
        /* get flag status from DCI_STAT1 register */
        stat = DCI_STAT1;
    } else {
        /* get flag status from DCI_STAT0 register */
        stat = DCI_STAT0;
    }

    if(flag & stat) {
        return SET;
    } else {
        return RESET;
    }
}

/*!
    简介:    enable specified DCI interrupt
    参数[输入]:  interrupt:
      参数:         DCI_INT_EF: end of frame interrupt
      参数:         DCI_INT_OVR: FIFO overrun interrupt
      参数:         DCI_INT_ESE: embedded synchronous error interrupt
      参数:         DCI_INT_VSYNC: vsync interrupt
      参数:         DCI_INT_EL: end of line interrupt
    参数[输出]:  无
    返回值:      无
*/
void DCI_Interrupt_Enable(uint32_t interrupt) {
    DCI_INTEN |= interrupt;
}

/*!
    简介:    disable specified DCI interrupt
    参数[输入]:  interrupt:
      参数:         DCI_INT_EF: end of frame interrupt
      参数:         DCI_INT_OVR: FIFO overrun interrupt
      参数:         DCI_INT_ESE: embedded synchronous error interrupt
      参数:         DCI_INT_VSYNC: vsync interrupt
      参数:         DCI_INT_EL: end of line interrupt
    参数[输出]:  无
    返回值:      无
*/
void DCI_Interrupt_Disable(uint32_t interrupt) {
    DCI_INTEN &= ~interrupt;
}

/*!
    简介:    clear specified interrupt flag
    参数[输入]:  int_flag:
      参数:         DCI_INT_EF: end of frame interrupt
      参数:         DCI_INT_OVR: FIFO overrun interrupt
      参数:         DCI_INT_ESE: embedded synchronous error interrupt
      参数:         DCI_INT_VSYNC: vsync interrupt
      参数:         DCI_INT_EL: end of line interrupt
    参数[输出]:  无
    返回值:      无
*/
void DCI_Interrupt_Flag_Clear(uint32_t int_flag) {
    DCI_INTC |= int_flag;
}

/*!
    简介:    get specified interrupt flag
    参数[输入]:  int_flag:
      参数:         DCI_INT_Flag_EF: end of frame interrupt flag
      参数:         DCI_INT_Flag_OVR: FIFO overrun interrupt flag
      参数:         DCI_INT_Flag_ESE: embedded synchronous error interrupt flag
      参数:         DCI_INT_Flag_VSYNC: vsync interrupt flag
      参数:         DCI_INT_Flag_EL: end of line interrupt flag
    参数[输出]:  无
    返回值:     FlagStatus: SET or RESET
*/
FlagStatus DCI_Interrupt_Flag_Get(uint32_t int_flag) {
    if(RESET == (DCI_INTF & int_flag)) {
        return RESET;
    } else {
        return SET;
    }
}


