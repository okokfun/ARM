/*!
    文件:    gd32f4xx_crc.h
    简介:   definitions for the CRC

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

#ifndef GD32F4XX_CRC_H
#define GD32F4XX_CRC_H

#include "gd32f4xx.h"

/* CRC definitions */
#define CRC                            CRC_BASE                        /*!< CRC base address */

/* registers definitions */
#define CRC_DATA                       REG32(CRC + 0x00000000U)        /*!< CRC data register */
#define CRC_FDATA                      REG32(CRC + 0x00000004U)        /*!< CRC free data register */
#define CRC_CTL                        REG32(CRC + 0x00000008U)        /*!< CRC control register */

/* bits definitions */
/* CRC_DATA */
#define CRC_Data_DATA                  BITS(0,31)                      /*!< CRC calculation result bits */

/* CRC_FDATA */
#define CRC_FDATA_FDATA                BITS(0,7)                       /*!< CRC free data bits */

/* CRC_CTL */
#define CRC_CTL_RST                    BIT(0)                          /*!< CRC reset CRC_DATA register bit */


/* function declarations */
/* deinit CRC 计算单元 */
void CRC_DeInit(void);

/* reset data register(CRC_DATA) to the value of 0xFFFFFFFF */
void CRC_Data_Register_Reset(void);
/* read the value of the data register */
uint32_t CRC_Data_Register_Read(void);

/* read the value of the free data register */
uint8_t CRC_Free_Data_Register_Read(void);
/* write data to the free data register */
void CRC_Free_Data_Register_Write(uint8_t free_data);

/* calculate the CRC value of a 32-bit data */
uint32_t CRC_Single_Data_Calculate(uint32_t sdata);
/* calculate the CRC value of an array of 32-bit values */
uint32_t CRC_Block_Data_Calculate(uint32_t array[], uint32_t size);

#endif /* GD32F4XX_CRC_H */
