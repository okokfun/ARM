/**
  ******************************************************************************
  * 文件:    stm32f4xx_spi.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    此文件提供固件功能，用于管理串行外围接口(SPI)的以下功能:
  *           + 初始化和配置
  *           + 数据传输函数
  *           + 硬件CRC计算
  *           + DMA传输管理
  *           + 中断和标志管理
  *
@verbatim

 ===================================================================
                  ##### 如何使用这个驱动程序 #####
 ===================================================================
 [..]
   (#) 使用以下功能启用外设时钟
       RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE) for SPI1
       RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE) for SPI2
       RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE) for SPI3
       RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE) for SPI4
       RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE) for SPI5
       RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE) for SPI6.

   (#) 使用 RCC_AHB1PeriphClockCmd() 函数启用 SCK、MOSI、MISO 和 NSS GPIO 时钟。
        在 I2S 模式下，如果使用外部时钟源，则还应启用 I2S CKIN 引脚 GPIO时钟。

   (#) 外设设备替代函数:
       (++) 使用 GPIO_PinAFConfig() 函数将管脚连接到所需外设设备的复用功能(AF)
       
       (++) 通过以下方式在复用功能中配置所需引脚:
            GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
			
       (++) 通过 GPIO_PuPd、GPIO_OType 和 GPIO_Speed 成员选择类型、上拉/下拉和输出速度
	   
       (++) 调用 GPIO_Init() 函数在 I2S 模式下，如果使用外部时钟源，
            则 I2S 的 CKIN 引脚也应该配置为复用 Push-pull - pull-up模式。

   (#) 使用 SPI_Init() 函数对极性、相位、第一数据、波特率预分频器、从机管理、外围模式和 CRC 多项式值进行编程。
       在 I2S 模式下，使用 I2S_Init() 函数编程模式，标准，数据格式，
       MCLK输出，音频频率和极性。对于 I2S 模式，请确保:
       (++) I2S PLL is configured using the functions
            RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S), RCC_PLLI2SCmd(ENABLE) and
            RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY);
			
       (++) 外部时钟源使用函数 RCC_I2SCLKConfig(RCC_I2S2CLKSource_Ext) 配置，
            并在 stm32f4xx_conf.h 文件中正确设置定义常量 I2S_EXTERNAL_CLOCK_VAL 之后配置。

   (#) 如果需要使用中断模式，可以使用 SPI_ITConfig() 函数启用 NVIC 和相应的中断。

   (#) 当使用 DMA 模式时
       (++) 使用 DMA_Init() 函数配置 DMA
       (++) 使用 SPI_I2S_DMACmd() 函数激活所需的通道请求

   (#) 使用 SPI_Cmd() 函数启用 SPI 或使用 I2S_Cmd() 启用 I2S。

   (#) 当使用 DMA 模式时，使用 DMA_Cmd() 函数启用 DMA。

   (#) 可选地，您可以启用/配置以下参数，而无需重新初始化(即不需要再次调用 SPI_Init() 函数):
       (++) 当双向模式(SPI_Direction_1Line_Rx 或 SPI_Direction_1Line_Tx) 被编程为使用
            SPI_Init() 函数的数据方向参数时，可以使用 SPI_BiDirectionalLineConfig() 函数
            在 SPI_Direction_Tx 或 SPI_Direction_Rx 之间切换。
			
       (++) 当 SPI_NSS_Soft 被选择为使用 SPI_Init() 函数的 Slave Select Management 参数时，
            可以使用 SPI_NSSInternalSoftwareConfig() 函数来管理NSS内部信号。
			
       (++) 使用 SPI_DataSizeConfig() 函数重新配置数据大小
	   
       (++) 使用 SPI_SSOutputCmd() 函数启用或禁用 SS输出

    (#) 要使用 CRC 硬件计算功能，请参阅外设 CRC 硬件计算小节。


 [..] 可以在I2S全双工模式下使用 SPI，在这种情况下，每个 SPI 外设都能够使用两条数据线
      同时管理发送和接收数据。每个 SPI 外设都有一个名为 I2Sxext 的扩展块
      (即。I2S2ext用于 SPI2, I2S3ext用于 SPI3)。
      扩展块不是一个完整的SPI IP，它只是作为I2S的slave来实现全双工模式。扩展块使用与主块相同的时钟源。
      要配置I2S全双工，您必须:

      (#) 在 I2S 模式下配置 SPIx (I2S_Init() 函数)如上所述。

      (#) 使用传递给 I2S_Init() 函数的相同结构调用 I2S_FullDuplexConfig() 函数。

      (#) 为 SPIx调用 I2S_Cmd()，然后为它的扩展块调用。

      (#) 要配置中断或DMA 请求以及获取/清除标志状态，请为扩展块使用 I2Sxext 实例。

 [..] 可以用 I2Sxext 实例调用的函数有: I2S_Cmd()， I2S_FullDuplexConfig()， SPI_I2S_ReceiveData()，
      SPI_I2S_SendData()， SPI_I2S_DMACmd()， SPI_I2S_ITConfig()， SPI_I2S_GetFlagStatus()，
      SPI_I2S_ClearFlag()， SPI_I2S_GetITStatus()和SPI_I2S_ClearITPendingBit()。

      示例: 在全双工模式下使用 SPI3 (SPI3是主Tx, I2S3ext是从Rx):

      RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
      I2S_StructInit(&I2SInitStruct);
      I2SInitStruct.Mode = I2S_Mode_MasterTx;
      I2S_Init(SPI3, &I2SInitStruct);
      I2S_FullDuplexConfig(SPI3ext, &I2SInitStruct)
      I2S_Cmd(SPI3, ENABLE);
      I2S_Cmd(SPI3ext, ENABLE);
      ...
      while (SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_TXE) == RESET)
      {}
      SPI_I2S_SendData(SPI3, txdata[i]);
      ...
      while (SPI_I2S_GetFlagStatus(I2S3ext, SPI_FLAG_RXNE) == RESET)
      {}
      rxdata[i] = SPI_I2S_ReceiveData(I2S3ext);
      ...

 [..]
   (@) 在I2S 模式下:如果I2S使用外部时钟作为源时钟，则需要启用 Stm32f4xx_conf.h
       文件中的define I2S_EXTERNAL_CLOCK_VAL，并将其设置为源时钟频率(单位为 Hz)。

   (@) 在SPI模式下:要使用 SPI TI模式，在调用 SPI_Init() 函数之后调用 SPI_TIModeCmd() 函数。

@endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_spi.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup SPI
  * 简介: SPI 驱动模块
  */

/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* SPI registers Masks */
#define CR1_CLEAR_MASK            ((uint16_t)0x3040)
#define I2SCFGR_CLEAR_MASK        ((uint16_t)0xF040)

/* RCC PLLs masks */
#define PLLCFGR_PPLR_MASK         ((uint32_t)0x70000000)
#define PLLCFGR_PPLN_MASK         ((uint32_t)0x00007FC0)

#define SPI_CR2_FRF               ((uint16_t)0x0010)
#define SPI_SR_TIFRFE             ((uint16_t)0x0100)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/

/** @defgroup SPI_Private_Functions
  */

/** @defgroup SPI_Group1 初始化和配置函数
 *  简介   初始化和配置函数
 *
@verbatim
 ===============================================================================
             ##### 初始化和配置函数 #####
 ===============================================================================
 [..] 本节提供了一组函数，允许初始化SPI方向、SPI模式、SPI数据大小、
	  SPI极性、SPI相位、SPI NSS管理、SPI波特率预分级器、SPI第一位和SPI CRC多项式。

 [..] SPI_Init() 函数遵循主模式和从模式的SPI配置过程(这些过程的详细信息可参阅参考手册(RM0090))。

@endverbatim
  */

/**
  * 简介:  将 SPIx 外设寄存器取消初始化为其缺省复位值。
  * 参数:  SPIx: 选择 SPIx/I2Sx外设，其中x在SPI模式下为1、2、3、4、5或6，在I2S 模式下为2或3。
  *
  * 注意:   扩展的I2S块(即。I2S2ext和I2S3ext块)在相对
			      I2S外设去初始化时被去初始化(扩展块的时钟由I2S外设时钟管理)。
  *
  * 返回值: 无
  */
void SPI_I2S_DeInit(SPI_TypeDef* SPIx) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    if (SPIx == SPI1) {
        /* 使能SPI1 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
        /* 释放SPI1 from 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
    } else if (SPIx == SPI2) {
        /* 使能SPI2 复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
        /* 释放SPI2 from 复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
    } else if (SPIx == SPI3) {
        /* 使能SPI3 复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
        /* 释放SPI3 from 复位状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
    } else if (SPIx == SPI4) {
        /* 使能SPI4 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI4, ENABLE);
        /* 释放SPI4 from 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI4, DISABLE);
    } else if (SPIx == SPI5) {
        /* 使能SPI5 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI5, ENABLE);
        /* 释放SPI5 from 复位状态 */
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI5, DISABLE);
    } else {
        if (SPIx == SPI6) {
            /* 使能SPI6 复位状态 */
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI6, ENABLE);
            /* 释放SPI6 from 复位状态 */
            RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI6, DISABLE);
        }
    }
}

/**
  * 简介:  根据SPI_InitStruct中的指定参数初始化SPIx外设设备。
  * 
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 
  * 参数:  SPI_InitStruct: 指向SPI_InitTypeDef结构的指针，该结构包含指定SPI外设的配置信息。
  * 
  * 返回值: 无
  */
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct) {
    uint16_t tmpreg = 0;

    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    /* 检查 the SPI parameters */
    assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
    assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
    assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
    assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
    assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
    assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
    assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
    assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));

    /*---------------------------- SPIx CR1 配置 ------------------------*/
    /* 获取SPIx CR1 值 */
    tmpreg = SPIx->CR1;
    /* 清除 BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA 位 */
    tmpreg &= CR1_CLEAR_MASK;
    /* 配置 SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
       master/salve mode, CPOL and CPHA */
    /* 设置 BIDImode, BIDIOE and RxONLY bits 根据 SPI_Direction 值 */
    /* 设置 SSM, SSI and MSTR bits 根据 SPI_Mode and SPI_NSS values */
    /* 设置 LSBFirst bit 根据 SPI_FirstBit 值 */
    /* 设置 BR bits 根据 SPI_BaudRatePrescaler 值 */
    /* 设置 CPOL bit 根据 SPI_CPOL 值 */
    /* 设置 CPHA bit 根据 SPI_CPHA 值 */
    tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
                         SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |
                         SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |
                         SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit);
    /* 写入SPIx CR1 */
    SPIx->CR1 = tmpreg;

    /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
    SPIx->I2SCFGR &= (uint16_t)~((uint16_t)SPI_I2SCFGR_I2SMOD);
    /*---------------------------- SPIx CRCPOLY 配置 --------------------*/
    /* 写入SPIx CRCPOLY */
    SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
}

/**
  * 简介:  根据I2S_InitStruct中指定的参数初始化 SPIx 外设。
  * 
  * 参数:  SPIx: 其中x可以是2或3，以选择 SPI外设设备(在I2S 模式下配置)。
  * 
  * 参数:  I2S_InitStruct: 指向I2S_InitTypeDef结构的指针，
  *        该结构包含I2S 模式下配置的指定SPI外设的配置信息。
  *
  * 注意:   该函数计算获得最精确音频频率所需的最佳预标器(取决于 I2S时钟源、锁相环值和产品配置)。
  *         但如果预分频器值大于511，则将配置默认值(0x02)。
  *
  * 注意:   如果I2S使用外部时钟作为源时钟，则应启用 Stm32f4xx_conf.h文件中
  *         的define I2S_EXTERNAL_CLOCK_VAL，并将其设置为源时钟频率的值(单位为 Hz)。
  *
  * 返回值: 无
  */
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct) {
    uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
    uint32_t tmp = 0, i2sclk = 0;
    #ifndef I2S_EXTERNAL_CLOCK_VAL
    uint32_t pllm = 0, plln = 0, pllr = 0;
    #endif /* I2S_EXTERNAL_CLOCK_VAL */

    /* 检查I2S参数 */
    assert_param(IS_SPI_23_PERIPH(SPIx));
    assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
    assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
    assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
    assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
    assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
    assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));

    /*----------------------- SPIx I2SCFGR & I2SPR 配置 -----------------*/
    /* 清除 I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN 位 */
    SPIx->I2SCFGR &= I2SCFGR_CLEAR_MASK;
    SPIx->I2SPR = 0x0002;

    /* 获取I2SCFGr 寄存器值 */
    tmpreg = SPIx->I2SCFGR;

    /* 如果必须写入默认值，请重新初始化i2sdiv和i2sodd*/
    if(I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default) {
        i2sodd = (uint16_t)0;
        i2sdiv = (uint16_t)2;
    }
    /* 如果请求的音频频率不是默认值，则计算预分频器 */
    else {
        /* 检查 the frame length (For the Prescaler computing) *******************/
        if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b) {
            /* Packet length is 16 位 */
            packetlength = 1;
        } else {
            /* Packet length is 32 位 */
            packetlength = 2;
        }

        /* 获取I2S源时钟频率  ****************************************/

        /* 如果必须使用外部 I2S 时钟，则应在项目配置或 stm32f4x_conf.h 文件中设置此定义 */
        #ifdef I2S_EXTERNAL_CLOCK_VAL

        /* 将外部时钟设置为 I2S 时钟源 */
        if ((RCC->CFGR & RCC_CFGR_I2SSRC) == 0) {
            RCC->CFGR |= (uint32_t)RCC_CFGR_I2SSRC;
        }

        /* 设置 I2S 时钟到外部时钟值 */
        i2sclk = I2S_EXTERNAL_CLOCK_VAL;

        #else /* 没有定义外部 I2S 时钟源 */

        /* 将 PLLI2S 设置为 I2S 时钟源 */
        if ((RCC->CFGR & RCC_CFGR_I2SSRC) != 0) {
            RCC->CFGR &= ~(uint32_t)RCC_CFGR_I2SSRC;
        }

        /* 获取PLLI2SN 值 */
        plln = (uint32_t)(((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SN) >> 6) & \
                          (RCC_PLLI2SCFGR_PLLI2SN >> 6));

        /* 获取PLLI2SR 值 */
        pllr = (uint32_t)(((RCC->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> 28) & \
                          (RCC_PLLI2SCFGR_PLLI2SR >> 28));

        /* 获取PLLM 值 */
        pllm = (uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM);

        if((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) == RCC_PLLCFGR_PLLSRC_HSE) {
            /* 获取I2S source clock 值 */
            i2sclk = (uint32_t)(((HSE_VALUE / pllm) * plln) / pllr);
        } else {
            /* 获取I2S source clock 值 */
            i2sclk = (uint32_t)(((HSI_VALUE / pllm) * plln) / pllr);
        }

        #endif /* I2S_EXTERNAL_CLOCK_VAL */

        /* 根据 MCLK 输出状态，使用浮点计算实数除法器 */
        if(I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable) {
            /* 启用MCLK输出 */
            tmp = (uint16_t)(((((i2sclk / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
        } else {
            /* 禁用MCLK输出 */
            tmp = (uint16_t)(((((i2sclk / (32 * packetlength)) * 10 ) / I2S_InitStruct->I2S_AudioFreq)) + 5);
        }

        /* Remove the flatting point */
        tmp = tmp / 10;

        /* 检查 the parity of the divider */
        i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

        /* Compute the i2sdiv prescaler */
        i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

        /* 获取Mask for the Odd bit (SPI_I2SPR[8]) 寄存器 */
        i2sodd = (uint16_t) (i2sodd << 8);
    }

    /* Test if the divider is 1 or 0 or greater than 0xFF */
    if ((i2sdiv < 2) || (i2sdiv > 0xFF)) {
        /* 设置 default values */
        i2sdiv = 2;
        i2sodd = 0;
    }

    /* 写入SPIx I2SPR register the computed 值 */
    SPIx->I2SPR = (uint16_t)((uint16_t)i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOutput));

    /* 配置 I2S with the SPI_InitStruct values */
    tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(I2S_InitStruct->I2S_Mode | \
                         (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                                    (uint16_t)I2S_InitStruct->I2S_CPOL))));

    #if defined(SPI_I2SCFGR_ASTRTEN)

    if((I2S_InitStruct->I2S_Standard  == I2S_Standard_PCMShort) || (I2S_InitStruct->I2S_Standard  == I2S_Standard_PCMLong)) {
        /* 写入SPIx I2SCFGR */
        SPIx->I2SCFGR = tmpreg | SPI_I2SCFGR_ASTRTEN;
    }

    #else
    /* 写入SPIx I2SCFGR */
    SPIx->I2SCFGR = tmpreg ;
    #endif
}

/**
  * 简介:  用其默认值填充每个SPI_InitStruct成员。
  * 参数:  SPI_InitStruct: 指向将被初始化的SPI_InitTypeDef结构的指针。
  * 返回值: 无
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct) {
    /*--------------- 重置SPI初始化结构参数值 -----------------*/
    /* 初始化 SPI_Direction 成员 */
    SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    /* 初始化 SPI_Mode 成员 */
    SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
    /* 初始化 SPI_DataSize 成员 */
    SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
    /* 初始化 SPI_CPOL 成员 */
    SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
    /* 初始化 SPI_CPHA 成员 */
    SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
    /* 初始化 SPI_NSS 成员 */
    SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
    /* 初始化 SPI_BaudRatePrescaler 成员 */
    SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    /* 初始化 SPI_FirstBit 成员 */
    SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
    /* 初始化 SPI_CRCPolynomial 成员 */
    SPI_InitStruct->SPI_CRCPolynomial = 7;
}

/**
  * 简介:  用每个I2S_InitStruct成员的默认值填充每个成员。
  * 参数:  I2S_InitStruct: 指向I2S_InitTypeDef结构的指针，该结构将被初始化。
  * 返回值: 无
  */
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct) {
    /*--------------- 重置I2S init结构参数值 -----------------*/
    /* 初始化 I2S_Mode 成员 */
    I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;

    /* 初始化 I2S_Standard 成员 */
    I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;

    /* 初始化 I2S_DataFormat 成员 */
    I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;

    /* 初始化 I2S_MCLKOutput 成员 */
    I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;

    /* 初始化 I2S_AudioFreq 成员 */
    I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;

    /* 初始化 I2S_CPOL 成员 */
    I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}

/**
  * 简介:  启用或禁用指定的SPI外设。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 参数:  NewState: SPIx外设设备的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 SPI 外设 */
        SPIx->CR1 |= SPI_CR1_SPE;
    } else {
        /* 禁用被选中的 SPI 外设 */
        SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_SPE);
    }
}

/**
  * 简介:  启用或禁用指定的SPI外设(在I2S 模式下)。
  * 参数:  SPIx: 其中x可以是2或3以选择 SPI外设设备(或I2Sxext用于全双工模式)。
  * 参数:  NewState: 新状态-> SPIx 外设.
  *         此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SPI_23_PERIPH_EXT(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 SPI peripheral (in I2S mode) */
        SPIx->I2SCFGR |= SPI_I2SCFGR_I2SE;
    } else {
        /* 禁用被选中的 SPI peripheral in I2S mode */
        SPIx->I2SCFGR &= (uint16_t)~((uint16_t)SPI_I2SCFGR_I2SE);
    }
}

/**
  * 简介:  配置所选 SPI 的数据大小。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 参数:  SPI_DataSize: 指定SPI data size.
  *          此参数可以是以下值之一:
  *            @arg SPI_DataSize_16b: Set data frame format to 16bit
  *            @arg SPI_DataSize_8b: Set data frame format to 8bit
  * 返回值: 无
  */
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DATASIZE(SPI_DataSize));
    /* 清除 DFF 位 */
    SPIx->CR1 &= (uint16_t)~SPI_DataSize_16b;
    /* Set new DFF bit 值 */
    SPIx->CR1 |= SPI_DataSize;
}

/**
  * 简介:  为指定的SPI选择双向模式下的数据传输方向。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 参数:  SPI_Direction: 指定data transfer direction in bidirectional mode.
  *          此参数可以是以下值之一:
  *            @arg SPI_Direction_Tx: Selects Tx transmission direction
  *            @arg SPI_Direction_Rx: Selects Rx receive direction
  * 返回值: 无
  */
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_DIRECTION(SPI_Direction));

    if (SPI_Direction == SPI_Direction_Tx) {
        /* 设置 Tx only mode */
        SPIx->CR1 |= SPI_Direction_Tx;
    } else {
        /* 设置 Rx only mode */
        SPIx->CR1 &= SPI_Direction_Rx;
    }
}

/**
  * 简介:  通过软件在内部配置所选SPI的NSS引脚。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 参数:  SPI_NSSInternalSoft: 指定SPI NSS internal state.
  *          此参数可以是以下值之一:
  *            @arg SPI_NSSInternalSoft_Set: Set NSS pin internally
  *            @arg SPI_NSSInternalSoft_Reset: Reset NSS pin internally
  * 返回值: 无
  */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));

    if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset) {
        /* Set NSS pin internally by software */
        SPIx->CR1 |= SPI_NSSInternalSoft_Set;
    } else {
        /* Reset NSS pin internally by software */
        SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
    }
}

/**
  * 简介:  启用或禁用所选 SPI 的 SS 输出。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 参数:  NewState: 新状态-> SPIx SS output.
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用被选定的 SPI SS output */
        SPIx->CR2 |= (uint16_t)SPI_CR2_SSOE;
    } else {
        /* 禁用被选中的 SPI SS output */
        SPIx->CR2 &= (uint16_t)~((uint16_t)SPI_CR2_SSOE);
    }
}

/**
  * 简介:  启用或禁用 SPIx/I2Sx DMA 接口。
  *
  * 注意:   This function can be called only after the SPI_Init() function has
  *         been called.
  * 注意:   When TI mode is selected, the control bits SSM, SSI, CPOL and CPHA
  *         are not taken into consideration and are configured by hardware
  *         respectively to the TI mode requirements.
  *
  * 参数:  SPIx: where x can be 1, 2, 3, 4, 5 or 6
  * 参数:  NewState: 新状态-> selected SPI TI communication mode.
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPI_TIModeCmd(SPI_TypeDef* SPIx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 TI mode for the selected SPI 外设 */
        SPIx->CR2 |= SPI_CR2_FRF;
    } else {
        /* 禁用 TI mode for the selected SPI 外设 */
        SPIx->CR2 &= (uint16_t)~SPI_CR2_FRF;
    }
}

/**
  * 简介:  根据I2S_InitStruct中的指定参数，使用扩展名 I2Sxext 为 I2Sx 外设配置全双工模式。
  * 参数:  I2Sxext: where x can be  2 or 3 to select the I2S peripheral extension block.
  * 参数:  I2S_InitStruct: pointer to an I2S_InitTypeDef structure that
  *         contains the configuration information for the specified I2S peripheral
  *         extension.
  *
  * 注意:   The structure pointed by I2S_InitStruct parameter should be the same
  *         used for the master I2S 外设. In this case, if the master is
  *         configured as transmitter, the slave will be receiver and vice versa.
  *         Or you can force a different mode by modifying the field I2S_Mode to the
  *         value I2S_SlaveRx or I2S_SlaveTx independently of the master configuration.
  *
  * 注意:   The I2S full duplex extension can be configured in slave mode only.
  *
  * 返回值: 无
  */
void I2S_FullDuplexConfig(SPI_TypeDef* I2Sxext, I2S_InitTypeDef* I2S_InitStruct) {
    uint16_t tmpreg = 0, tmp = 0;

    /* 检查I2S参数 */
    assert_param(IS_I2S_EXT_PERIPH(I2Sxext));
    assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
    assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
    assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
    assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));

    /*----------------------- SPIx I2SCFGR & I2SPR 配置 -----------------*/
    /* 清除 I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN 位 */
    I2Sxext->I2SCFGR &= I2SCFGR_CLEAR_MASK;
    I2Sxext->I2SPR = 0x0002;

    /* 获取I2SCFGr 寄存器值 */
    tmpreg = I2Sxext->I2SCFGR;

    /* 获取mode to be configured for the extended I2S */
    if ((I2S_InitStruct->I2S_Mode == I2S_Mode_MasterTx) || (I2S_InitStruct->I2S_Mode == I2S_Mode_SlaveTx)) {
        tmp = I2S_Mode_SlaveRx;
    } else {
        if ((I2S_InitStruct->I2S_Mode == I2S_Mode_MasterRx) || (I2S_InitStruct->I2S_Mode == I2S_Mode_SlaveRx)) {
            tmp = I2S_Mode_SlaveTx;
        }
    }


    /* 配置 I2S with the SPI_InitStruct values */
    tmpreg |= (uint16_t)((uint16_t)SPI_I2SCFGR_I2SMOD | (uint16_t)(tmp | \
                         (uint16_t)(I2S_InitStruct->I2S_Standard | (uint16_t)(I2S_InitStruct->I2S_DataFormat | \
                                    (uint16_t)I2S_InitStruct->I2S_CPOL))));

    /* 写入SPIx I2SCFGR */
    I2Sxext->I2SCFGR = tmpreg;
}


/** @defgroup SPI_Group2 数据传输函数
 *  简介   数据传输函数
 *
@verbatim
 ===============================================================================
                      ##### 数据传输函数 #####
 ===============================================================================

 [..] 本节提供了一组允许管理SPI数据传输的函数。在接收中，数据被接收，
	  然后存储到一个内部Rx缓冲区中。在传输中，数据在传输之前首先存储到内部Tx缓冲区中。

 [..] SPI_DR 寄存器的读取访问可以使用 SPI_I2S_ReceiveData()
	  函数完成，并返回Rx缓冲值。而对SPI_DR的写入访问可以使用
	  SPI_I2S_SendData() 函数来完成，并将写入的数据存储到Tx缓冲器中。

@endverbatim
  */

/**
  * 简介:  返回 SPIx/I2Sx 外设最近接收到的数据。
  * 参数:  SPIx: 选择 SPIx/I2Sx外设，其中x可以是：
				 在SPI模式下为1、2、3、4、5或6，在I2S 模式下
				 为2或3，或者在I2S全双工模式下为I2Sxext。
  * 返回值: The value of 接收的数据。
  */
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));

    /* 返回data in the DR 寄存器 */
    return SPIx->DR;
}

/**
  * 简介:  通过 SPIx/I2Sx 外设传输数据。
  * 参数:  SPIx: 选择 SPIx/I2Sx外设设备，其中x可以是：
				 在SPI模式下为1、2、3、4、5或6，在I2S 模式下为2或3，
				 或者在I2S全双工模式下为I2Sxext。
  * 参数:  Data: 要传输的数据。
  * 返回值: 无
  */
void SPI_I2S_SendData(SPI_TypeDef* SPIx, uint16_t Data) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));

    /* 在DR 寄存器中写入要发送的数据 */
    SPIx->DR = Data;
}


/** @defgroup SPI_Group3 硬件CRC计算函数
 *  简介   硬件CRC计算函数
 *
@verbatim
 ===============================================================================
                 ##### 硬件CRC计算函数 #####
 ===============================================================================

 [..] 本节提供了一组允许管理SPI CRC硬件计算的函数

 [..] 通过以下程序，可以使用CRC进行SPI通信:
   (#) 使用 SPI_Init() 函数对数据方向、极性、相位、第一数据、波特率预分频器、
        从机管理、外围模式和CRC多项式值进行编程。
   (#) 使用 SPI_CalculateCRC() 函数启用CRC计算。
   (#) 使用 SPI_Cmd() 函数启用 SPI
   (#) 在将最后的数据写入TX缓冲区之前，使用 SPI_TransmitCRC() 函数
        设置CRCNext位，以指示在传输最后的数据后，应传输CRC。
   (#) 在传输最后一个数据后，SPI传输CRC。SPI_CR1_CRCNEXT位复位。
        还将接收CRC并与SPI_RXCRCR值进行比较。
        如果该值不匹配，则设置SPI_FLAG_CRCERR标志，并在启用 SPI_I2S_IT_ERR中断时生成中断。

 [..]
   (@) 建议不要在通信期间读取计算的CRC值。

   (@) 当SPI处于从属模式时，请注意仅当时钟稳定时，即当时钟处于稳定状态时，才启用CRC计算。
       否则，可能会进行错误的CRC计算。事实上，一旦设置了CRCEN，
        CRC就对SCK从机输入时钟敏感，这与SPE位的值无关。

   (@) 对于高比特率频率，在传输CRC时要小心。
       由于在CRC传输阶段使用的CPU周期数必须尽可能低，
        因此禁止调用CRC传输序列中的软件功能，以避免最后数据和CRC接收中的错误。
       事实上，CRCNEXT位必须在最后数据传输/接收结束之前写入。

   (@) 对于高比特率频率，建议使用 DMA 模式，以避免由于CPU访问影响SPI带宽而导致SPI速度性能下降。

   (@) 当STM32F4xx配置为从机并且使用 NSS硬件模式时，NSS引脚需要在数据相位和CRC相位之间保持低电平。

   (@) 当SPI在启用CRC功能的从属模式下配置时，即使NSS引脚上应用了高电平，也会进行CRC计算。
       例如，在通信主机交替寻址从机的多从机环境中，可能会发生这种情况。

   (@) 在从设备取消选择(NSS上的高电平)和新的从设备选择(NSC上的低电平)之间，
        应清除主设备和从设备侧的CRC值，以便重新同步主设备和从属设备进行各自的CRC计算。

   (@) 要清除CRC，请遵循以下程序:
       (#@) 使用 SPI_Cmd() 函数禁用 SPI
       (#@) 使用 SPI_CalculateCRC() 函数禁用CRC计算。
       (#@) 使用 SPI_CalculateCRC() 函数启用CRC计算。
       (#@) 使用 SPI_Cmd() 函数启用 SPI。

@endverbatim
  */

/**
  * 简介:  启用或禁用传输字节的CRC值计算。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 参数:  NewState: SPIx CRC值计算的新状态。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的SPI CRC计算 */
        SPIx->CR1 |= SPI_CR1_CRCEN;
    } else {
        /* 禁用所选SPI CRC计算 */
        SPIx->CR1 &= (uint16_t)~((uint16_t)SPI_CR1_CRCEN);
    }
}

/**
  * 简介:  传输SPIx CRC值。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 返回值: 无
  */
void SPI_TransmitCRC(SPI_TypeDef* SPIx) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    /* 启用选定的SPI CRC传输 */
    SPIx->CR1 |= SPI_CR1_CRCNEXT;
}

/**
  * 简介:  返回指定SPI的发送或接收CRC 寄存器值。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 参数:  SPI_CRC: 指定要读取的CRC 寄存器。
  *          此参数可以是以下值之一:
  *            @arg SPI_CRC_Tx: 选择Tx CRC 寄存器
  *            @arg SPI_CRC_Rx: 选择Rx CRC 寄存器
  * 返回值: 所选CRC 寄存器值。
  */
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC) {
    uint16_t crcreg = 0;
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));
    assert_param(IS_SPI_CRC(SPI_CRC));

    if (SPI_CRC != SPI_CRC_Rx) {
        /* 获取Tx CRC 寄存器 */
        crcreg = SPIx->TXCRCR;
    } else {
        /* 获取Rx CRC 寄存器 */
        crcreg = SPIx->RXCRCR;
    }

    /* 返回selected CRC 寄存器 */
    return crcreg;
}

/**
  * 简介:  返回指定SPI的CRC多项式寄存器值。
  * 参数:  SPIx: 其中x可以是1、2、3、4、5或6，以选择 SPI外设设备。
  * 返回值: CRC多项式寄存器值。
  */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH(SPIx));

    /* 返回CRC polynomial 寄存器 */
    return SPIx->CRCPR;
}


/** @defgroup SPI_Group4 DMA传输管理 功能
 *  简介   DMA传输管理 功能
  *
@verbatim
 ===============================================================================
                   ##### DMA传输管理功能 #####
 ===============================================================================

@endverbatim
  */

/**
  * 简介:  启用或禁用 SPIx/I2Sx DMA 接口。
  * 参数:  SPIx: 选择 SPIx/I2Sx外设设备，其中x可以是：在SPI模式下为1、2、3、4、5或6，
				 在I2S 模式下为2或3，或者在I2S全双工模式下为I2Sxext。
  * 参数:  SPI_I2S_DMAReq: 指定要启用或禁用的SPI DMA传输请求。
  *          此参数可以是以下值的任意组合:
  *            @arg SPI_I2S_DMAReq_Tx: Tx缓冲区DMA传输请求
  *            @arg SPI_I2S_DMAReq_Rx: Rx缓冲区DMA传输请求
  * 参数:  NewState: 新状态-> 选择的SPI DMA传输请求。
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPI_I2S_DMAREQ(SPI_I2S_DMAReq));

    if (NewState != DISABLE) {
        /* 启用被选定的 SPI DMA requests */
        SPIx->CR2 |= SPI_I2S_DMAReq;
    } else {
        /* 禁用被选中的 SPI DMA requests */
        SPIx->CR2 &= (uint16_t)~SPI_I2S_DMAReq;
    }
}


/** @defgroup SPI_Group5 中断和标记管理函数
 *  简介   中断和标记管理函数
  *
@verbatim
 ===============================================================================
            ##### 中断和标记管理函数 #####
 ===============================================================================

 [..] 本节提供了一组函数，允许配置SPI中断源并检查或清除标志或挂起位状态。
      用户应确定在其应用程序中将使用哪种模式来管理通信:轮询模式、中断模式或DMA 模式。

 *** 轮询模式 ***
 ====================
[..] 在轮询模式下，SPI/I2S通信可通过9个标志进行管理:
  (#) SPI_I2S_FLAG_TXE : 指示发送缓冲寄存器的状态
  (#) SPI_I2S_FLAG_RXNE : 指示接收缓冲寄存器的状态
  (#) SPI_I2S_FLAG_BSY : 指示SPI通信层的状态。
  (#) SPI_FLAG_CRCERR : 指示是否发生CRC计算错误
  (#) SPI_FLAG_MODF : 指示是否发生模式故障
  (#) SPI_I2S_FLAG_OVR : 指示是否发生超限错误
  (#) I2S_FLAG_TIFRFE: 指示发生帧格式错误。
  (#) I2S_FLAG_UDR: 指示发生欠载错误。
  (#) I2S_FLAG_CHSIDE: 表示通道侧。

  (@) 不要使用BSY标志来处理每个数据传输或接收。最好使用 TXE和RXNE标志。

 [..] 在此模式下，建议使用以下函数:
   (+) FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
   (+) void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);

 *** 中断模式 ***
 ======================
 [..] 在中断模式下，SPI通信可由3个中断源和7个挂起位管理:
   (+) Pending Bits:
	 (##) SPI_I2S_IT_TXE：指示发送缓冲寄存器的状态
	 (##) SPI_I2S_IT_RXNE：指示接收缓冲寄存器的状态
	 (##) SPI_IT_CRCERR：指示是否发生CRC计算错误(仅在SPI模式下可用)
	 (##) SPI_IT_MODF：指示是否发生模式故障错误(仅适用于 SPI模式)
	 (##) SPI_I2S_IT_OVR：指示是否发生超限错误
	 (##) I2S_IT_UDR：指示发生欠载错误(仅在I2S 模式下可用)。
	 (##) I2S_FLAG_TIFRFE：指示发生帧格式错误(仅在TI模式下可用)。

   (+) 中断源:
(##)SPI_I2S_IT_TXE：指定Tx缓冲区空中断的中断源。
(##)SPI_I2S_IT_RXNE：指定Rx缓冲区非空中断的中断源。
(##)SPI_I2S_IT_ERR：指定错误中断的中断源。

 [..] 在此模式下，建议使用以下函数:
   (+) void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
   (+) ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
   (+) void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);

 *** DMA 模式 ***
 ================
 [..] 在DMA 模式下，SPI通信可以通过2个DMA通道请求进行管理:
   (#) SPI_I2S_DMAReq_Tx: 指定Tx缓冲区DMA传输请求
   (#) SPI_I2S_DMAReq_Rx: 指定Rx缓冲区DMA传输请求

 [..] 在此模式下，建议使用以下函数:
   (+) void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState
       NewState);

@endverbatim
  */

/**
  * 简介:  启用或禁用指定的 SPI/I2S 中断。
  * 参数:  SPIx: 选择 SPIx/I2Sx外设设备，其中x可以是：
				在SPI模式下为1、2、3、4、5或6，在I2S 模式下为2或3，
				或者在I2S全双工模式下为I2Sxext。
  * 参数:  SPI_I2S_IT: 指定要启用或禁用的SPI中断源。
  *          此参数可以是以下值之一:
  *            @arg SPI_I2S_IT_TXE: Tx缓冲区空中断掩码
  *            @arg SPI_I2S_IT_RXNE: Rx缓冲区空中断掩码
  *            @arg SPI_I2S_IT_ERR: 错误中断 mask
  * 参数:  NewState: 新状态-> specified SPI interrupt.
  *          此参数可以是: ENABLE或DISABLE。
  * 返回值: 无
  */
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState) {
    uint16_t itpos = 0, itmask = 0 ;

    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SPI_I2S_CONFIG_IT(SPI_I2S_IT));

    /* 获取SPI IT index */
    itpos = SPI_I2S_IT >> 4;

    /* 设置 IT mask */
    itmask = (uint16_t)1 << (uint16_t)itpos;

    if (NewState != DISABLE) {
        /* 启用被选定的 SPI 中断 */
        SPIx->CR2 |= itmask;
    } else {
        /* 禁用被选中的 SPI 中断 */
        SPIx->CR2 &= (uint16_t)~itmask;
    }
}

/**
  * 简介:  检查是否设置了指定的SPIx/I2Sx标志。
  * 参数:  SPIx: To select the SPIx/I2Sx peripheral, where x can be: 1, 2, 3, 4, 5 or 6
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
  * 参数:  SPI_I2S_FLAG: 指定SPI flag to check.
  *          此参数可以是以下值之一:
  *            @arg SPI_I2S_FLAG_TXE: Transmit buffer empty flag.
  *            @arg SPI_I2S_FLAG_RXNE: Receive buffer not empty flag.
  *            @arg SPI_I2S_FLAG_BSY: Busy flag.
  *            @arg SPI_I2S_FLAG_OVR: Overrun flag.
  *            @arg SPI_FLAG_MODF: Mode Fault flag.
  *            @arg SPI_FLAG_CRCERR: CRC Error flag.
  *            @arg SPI_I2S_FLAG_TIFRFE: Format Error.
  *            @arg I2S_FLAG_UDR: Underrun Error flag.
  *            @arg I2S_FLAG_CHSIDE: Channel Side flag.
  * 返回值: 新状态-> SPI_I2S_FLAG (SET or RESET).
  */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG) {
    FlagStatus bitstatus = RESET;
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));

    /* 检查 the status of the specified SPI flag */
    if ((SPIx->SR & SPI_I2S_FLAG) != (uint16_t)RESET) {
        /* SPI_I2S_FLAG 被设置 */
        bitstatus = SET;
    } else {
        /* SPI_I2S_FLAG  被重置 */
        bitstatus = RESET;
    }

    /* 返回SPI_I2S_FLAG 状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 SPIx CRC 错误 (CRCERR) 标志。
  * 参数:  SPIx：选择 SPIx/I2Sx外设设备，其中x可以是：
			SPI模式下的1、2、3、4、5或6，I2S 模式下的2或3，I2S全双工模式下的I2Sxext。
  * 参数:  SPI_I2S_FLAG：指定要清除的SPI标志。
  *			此功能仅清除CRCERR标志。
  *				@arg SPI_FLAG_CERRR:CRC错误标志。
  *
  * 注意:   OVR(OverRun error)标志由软件序列清除：对SPI_DR 寄存器(SPI_I2S_ReceiveData())进行
			读取操作，然后对SPI_SR 寄存器(SPI_I2S_GetFlagStatus())执行读取操作。
  * 注意:   通过对SPI_SR 寄存器的读取操作(SPI_I2S_GetFlagStatus())清除UDR(运行不足错误)标志。
  * 注意:   MODF(模式故障)标志由软件序列清除：对SPI_SR 寄存器(SPI_I2S_GetFlagStatus())
			进行读/写操作，然后对SPI_CR1寄存器(SPI_Cmd()进行写操作以启用 SPI)。
  * 返回值: 无
  */
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG) {
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_SPI_I2S_CLEAR_FLAG(SPI_I2S_FLAG));

    /* 清除 selected SPI CRC Error (CRCERR) flag */
    SPIx->SR = (uint16_t)~SPI_I2S_FLAG;
}

/**
  * 简介:  检查指定的 SPIx/I2Sx 中断是否发生。
  * 参数:  SPIx: To select the SPIx/I2Sx peripheral, where x can be: 1, 2, 3, 4, 5 or 6
  *         in SPI mode or 2 or 3 in I2S mode or I2Sxext for I2S full duplex mode.
  * 参数:  SPI_I2S_IT: 指定要检查的SPI中断源。
  *          此参数可以是以下值之一:
  *            @arg SPI_I2S_IT_TXE: Transmit buffer empty interrupt.
  *            @arg SPI_I2S_IT_RXNE: Receive buffer not empty interrupt.
  *            @arg SPI_I2S_IT_OVR: Overrun interrupt.
  *            @arg SPI_IT_MODF: Mode Fault interrupt.
  *            @arg SPI_IT_CRCERR: CRC Error interrupt.
  *            @arg I2S_IT_UDR: Underrun interrupt.
  *            @arg SPI_I2S_IT_TIFRFE: Format Error interrupt.
  * 返回值: 新状态-> SPI_I2S_IT (SET or RESET).
  */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT) {
    ITStatus bitstatus = RESET;
    uint16_t itpos = 0, itmask = 0, enablestatus = 0;

    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_SPI_I2S_GET_IT(SPI_I2S_IT));

    /* 获取SPI_I2S_IT index */
    itpos = 0x01 << (SPI_I2S_IT & 0x0F);

    /* 获取SPI_I2S_IT IT mask */
    itmask = SPI_I2S_IT >> 4;

    /* 设置 IT mask */
    itmask = 0x01 << itmask;

    /* 获取SPI_I2S_IT enable bit 状态 */
    enablestatus = (SPIx->CR2 & itmask) ;

    /* 检查指定SPI中断的状态 */
    if (((SPIx->SR & itpos) != (uint16_t)RESET) && enablestatus) {
        /* SPI_I2S_IT 被设置 */
        bitstatus = SET;
    } else {
        /* SPI_I2S_IT  被重置 */
        bitstatus = RESET;
    }

    /* 返回SPI_I2S_IT 状态 */
    return bitstatus;
}

/**
  * 简介:  清除SPIx CRC错误(CRCERR)中断挂起位。
  * 参数:  SPIx: 选择 SPIx/I2Sx外设设备，其中x可以是:SPI模式下的1、2、3、4、5或6，
  *         I2S 模式下的2或3，或I2S全双工模式下的I2Sxext。
  * 参数:  SPI_I2S_IT: 指定要清除的SPI中断挂起位。
  *         此函数仅清除CRCERR中断挂起位。
  *            @arg SPI_IT_CRCERR: CRC错误中断。
  *
  * 注意:   OVR (OverRun Error) interrupt pending bit is cleared by software
  *          sequence: a read operation to SPI_DR register (SPI_I2S_ReceiveData())
  *          followed by a read operation to SPI_SR register (SPI_I2S_GetITStatus()).
  * 注意:   UDR (UnderRun Error) interrupt pending bit is cleared by a read
  *          operation to SPI_SR register (SPI_I2S_GetITStatus()).
  * 注意:   MODF(模式故障)中断挂起位通过软件序列清除:
  *          对SPI_SR 寄存器(SPI_I2S_GetITStatus())执行读/写操作，
  *             然后对SPI_CR1寄存器(SPI-Cmd())进行写操作，以启用 SPI。
  * 返回值: 无
  */
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT) {
    uint16_t itpos = 0;
    /* 检查参数 */
    assert_param(IS_SPI_ALL_PERIPH_EXT(SPIx));
    assert_param(IS_SPI_I2S_CLEAR_IT(SPI_I2S_IT));

    /* 获取SPI_I2S IT index */
    itpos = 0x01 << (SPI_I2S_IT & 0x0F);

    /* 清除 selected SPI CRC Error (CRCERR) interrupt pending 位 */
    SPIx->SR = (uint16_t)~itpos;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
