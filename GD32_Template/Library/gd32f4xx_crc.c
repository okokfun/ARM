/*!
    文件:    gd32f4xx_crc.c
    简介:   CRC driver

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

#include "gd32f4xx_crc.h"

#define CRC_Data_RESET_VALUE      ((uint32_t)0xFFFFFFFFU)
#define CRC_FDATA_RESET_VALUE     ((uint32_t)0x00000000U)

/*!
    简介:      deinit CRC 计算单元
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void CRC_DeInit(void) {
    CRC_DATA  = CRC_Data_RESET_VALUE;
    CRC_FDATA = CRC_FDATA_RESET_VALUE;
    CRC_CTL   = (uint32_t)CRC_CTL_RST;
}

/*!
    简介:      reset data register(CRC_DATA) to the value of 0xFFFFFFFF
    参数[输入]:  无
    参数[输出]:  无
    返回值:      无
*/
void CRC_Data_Register_Reset(void) {
    CRC_CTL |= (uint32_t)CRC_CTL_RST;
}

/*!
    简介:      read the value of the data register
    参数[输入]:  无
    参数[输出]:  无
    返回值:     32-bit value of the data register
*/
uint32_t CRC_Data_Register_Read(void) {
    uint32_t data;
    data = CRC_DATA;
    return (data);
}

/*!
    简介:      read the value of the free data register
    参数[输入]:  无
    参数[输出]:  无
    返回值:     8-bit value of the free data register
*/
uint8_t CRC_Free_Data_Register_Read(void) {
    uint8_t fdata;
    fdata = (uint8_t)CRC_FDATA;
    return (fdata);
}

/*!
    简介:      write data to the free data register
    参数[输入]:  free_data: specified 8-bit data
    参数[输出]:  无
    返回值:      无
*/
void CRC_Free_Data_Register_Write(uint8_t free_data) {
    CRC_FDATA = (uint32_t)free_data;
}

/*!
    简介:      calculate the CRC value of a 32-bit data
    参数[输入]:  sdata: specified 32-bit data
    参数[输出]:  无
    返回值:     32-bit value calculated by CRC
*/
uint32_t CRC_Single_Data_Calculate(uint32_t sdata) {
    CRC_DATA = sdata;
    return (CRC_DATA);
}

/*!
    简介:      calculate the CRC value of an array of 32-bit values
    参数[输入]:  array: pointer to an array of 32-bit values
    参数[输入]:  size: size of the array
    参数[输出]:  无
    返回值:     32-bit value calculated by CRC
*/
uint32_t CRC_Block_Data_Calculate(uint32_t array[], uint32_t size) {
    uint32_t index;

    for(index = 0U; index < size; index++) {
        CRC_DATA = array[index];
    }

    return (CRC_DATA);
}
