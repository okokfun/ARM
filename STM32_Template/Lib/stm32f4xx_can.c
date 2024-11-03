/**
  ******************************************************************************
  * 文件:    stm32f4xx_can.c
  * 作者:    MCD Application Team
  * 版本:    V1.8.0
  * 日期:    04-November-2016
  * 简介:    该文件提供固件功能来管理控制器局域网 (CAN) 外设设备的以下功能:
  *           + 初始化和配置
  *           + CAN 帧传输
  *           + CAN 帧接收
  *           + 操作模式切换
  *           + 错误管理
  *           + 中断和标志
  *
@verbatim
 ===============================================================================
                        ##### 如何使用此驱动程序 #####
 ===============================================================================
    [..]
      (#) 使用启用 CAN 控制器接口时钟
           RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE); 用于 CAN1
           和 RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE); 用于 CAN2

      -@- 如果您只使用 CAN2，则必须启用 CAN1 时钟。

      (#) CAN 引脚配置
        (++) 使用以下函数启用 CAN GPIO 的时钟:
             RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);

        (++) 使用以下函数将涉及的 CAN 引脚连接到 AF9
             GPIO_PinAFConfig(GPIOx, GPIO_PinSourcex, GPIO_AF_CANx);

        (++) 通过调用函数 GPIO_Init() 将这些 CAN 引脚配置为复用功能模式;

      (#) 使用 CAN_Init() 和 CAN_FilterInit() 函数初始化和配置 CAN。

      (#) 使用 CAN_Transmit() 函数传输所需的 CAN 帧。

      (#) 使用 CAN_TransmitStatus() 函数检查 CAN 帧的传输。

      (#) 使用 CAN_CancelTransmit() 函数取消 CAN 帧的传输。

      (#) 使用 CAN_Receive() 函数接收 CAN 帧。

      (#) 使用 CAN_FIFORelease() 函数释放接收 FIFO。

      (#) 使用 CAN_MessagePending() 函数返回挂起的接收帧数。

      (#) 要控制 CAN 事件，您可以使用以下两种方法之一:
        (++) 使用 CAN_GetFlagStatus() 函数检查 CAN 标志。
        
        (++) 在初始化阶段通过函数 CAN_ITConfig() 和 CAN_GetITStatus() 函数在中断例程中使用 CAN 中断来检查事件是否发生。
             检查标志后，您应该使用 CAN_ClearFlag() 函数清除它。 在检查中断事件后，您应该使用 CAN_ClearITPendingBit() 函数将其清除。

@endverbatim

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
#include "stm32f4xx_can.h"
#include "stm32f4xx_rcc.h"

/** @addtogroup STM32F4xx_StdPeriph_Driver
  */

/** @defgroup CAN
  * 简介: CAN 驱动模块
  */
/* Private typedef -----------------------------------------------------------*/
/* 私有宏 ------------------------------------------------------------*/

/* CAN主控制寄存器位 */
#define MCR_DBF           ((uint32_t)0x00010000) /* software master reset */

/* CAN邮箱传输请求 */
#define TMIDxR_TXRQ       ((uint32_t)0x00000001) /* Transmit mailbox request */

/* CAN过滤器主寄存器位 */
#define FMR_FINIT         ((uint32_t)0x00000001) /* Filter init mode */

/* INAK超时位 */
#define INAK_TIMEOUT      ((uint32_t)0x0000FFFF)
/* SLAK超时位 */
#define SLAK_TIMEOUT      ((uint32_t)0x0000FFFF)

/* Flags在 TSR 寄存器 */
#define CAN_FLAGS_TSR     ((uint32_t)0x08000000)
/* Flags在 RF1R 寄存器 */
#define CAN_FLAGS_RF1R    ((uint32_t)0x04000000)
/* Flags在 RF0R 寄存器 */
#define CAN_FLAGS_RF0R    ((uint32_t)0x02000000)
/* Flags在 MSR 寄存器 */
#define CAN_FLAGS_MSR     ((uint32_t)0x01000000)
/* Flags在 ESR 寄存器 */
#define CAN_FLAGS_ESR     ((uint32_t)0x00F00000)

/* 邮箱定义 */
#define CAN_TXMAILBOX_0   ((uint8_t)0x00)
#define CAN_TXMAILBOX_1   ((uint8_t)0x01)
#define CAN_TXMAILBOX_2   ((uint8_t)0x02)

#define CAN_MODE_MASK     ((uint32_t) 0x00000003)

/* 私有宏 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有函数原型 -----------------------------------------------*/
/* 私有函数 ---------------------------------------------------------*/
static ITStatus CheckITStatus(uint32_t CAN_Reg, uint32_t It_Bit);

/** @defgroup CAN_Private_Functions
  */

/** @defgroup CAN_Group1 初始化和配置函数
 *  简介    初始化和配置函数
 *
@verbatim
 ===============================================================================
              ##### 初始化和配置函数 #####
 ===============================================================================
    [..] 本节提供的功能允许
      (+) 初始化 CAN 外设设备: 预分频器、操作模式、执行重新同步的最大时间量、
            位段1和2中的时间量以及许多其他模式。
          有关更多详细信息，请参阅 @ref CAN_InitTypeDef。

      (+) 配置 CAN 接收滤波器。

      (+) 为从属 CAN 选择启动组过滤器。

      (+) 启用或禁用 CAN 的调试冻结模式

      (+) 启用或禁用 CAN 时间触发器操作通信模式

@endverbatim
  */

/**
  * 简介:  用于将 CAN 配置设置为默认复位状态的函数
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 无.
  */
void CAN_DeInit(CAN_TypeDef* CANx) {
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    if (CANx == CAN1) {
        /* 启用 CAN1重置状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, ENABLE);
        /* 从复位状态释放 CAN1 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN1, DISABLE);
    }

    #if defined(STM32F413_423xx)
    else if(CANx == CAN2) {
        /* 启用 CAN2 重置状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, ENABLE);
        /* 从复位状态释放 CAN2 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, DISABLE);
    }

    else { /* CAN3 仅适用于 STM32F413_423xx */
        /* 启用 CAN3 重置状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN3, ENABLE);
        /* 从复位状态释放 CAN3 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN3, DISABLE);
    }

    #else
    else {
        /* 启用 CAN2 重置状态 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, ENABLE);
        /* 从复位状态释放 CAN2 */
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_CAN2, DISABLE);
    }

    #endif /* STM32F413_423xx */
}

/**
  * 简介:  根据 CAN_InitStruct 中指定的参数初始化外设 CAN 的寄存器
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  CAN_InitStruct: 指向包含 CAN 外设设备配置信息的 CAN_InitTypeDef 结构的指针。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 常量表示初始化成功，即 CAN_InitStatus_Failed 或 CAN_InitStatus_Success。
  */
uint8_t CAN_Init(CAN_TypeDef* CANx, CAN_InitTypeDef* CAN_InitStruct) {
    uint8_t InitStatus = CAN_InitStatus_Failed;
    uint32_t wait_ack = 0x00000000;
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TTCM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_ABOM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_AWUM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_NART));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_RFLM));
    assert_param(IS_FUNCTIONAL_STATE(CAN_InitStruct->CAN_TXFP));
    assert_param(IS_CAN_MODE(CAN_InitStruct->CAN_Mode));
    assert_param(IS_CAN_SJW(CAN_InitStruct->CAN_SJW));
    assert_param(IS_CAN_BS1(CAN_InitStruct->CAN_BS1));
    assert_param(IS_CAN_BS2(CAN_InitStruct->CAN_BS2));
    assert_param(IS_CAN_PRESCALER(CAN_InitStruct->CAN_Prescaler));

    /* 退出睡眠模式 */
    CANx->MCR &= (~(uint32_t)CAN_MCR_SLEEP);

    /* 请求初始化 */
    CANx->MCR |= CAN_MCR_INRQ ;

    /* 等待确认 */
    while (((CANx->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) && (wait_ack != INAK_TIMEOUT)) {
        wait_ack++;
    }

    /* 检查确认 */
    if ((CANx->MSR & CAN_MSR_INAK) != CAN_MSR_INAK) {
        InitStatus = CAN_InitStatus_Failed;
    } else {
        /* 设置 时间触发通信模式 */
        if (CAN_InitStruct->CAN_TTCM == ENABLE) {
            CANx->MCR |= CAN_MCR_TTCM;
        } else {
            CANx->MCR &= ~(uint32_t)CAN_MCR_TTCM;
        }

        /* 设置 自动总线关闭管理 */
        if (CAN_InitStruct->CAN_ABOM == ENABLE) {
            CANx->MCR |= CAN_MCR_ABOM;
        } else {
            CANx->MCR &= ~(uint32_t)CAN_MCR_ABOM;
        }

        /* 设置 自动唤醒模式 */
        if (CAN_InitStruct->CAN_AWUM == ENABLE) {
            CANx->MCR |= CAN_MCR_AWUM;
        } else {
            CANx->MCR &= ~(uint32_t)CAN_MCR_AWUM;
        }

        /* 设置 无自动重发 */
        if (CAN_InitStruct->CAN_NART == ENABLE) {
            CANx->MCR |= CAN_MCR_NART;
        } else {
            CANx->MCR &= ~(uint32_t)CAN_MCR_NART;
        }

        /* 设置 接收 FIFO锁定模式 */
        if (CAN_InitStruct->CAN_RFLM == ENABLE) {
            CANx->MCR |= CAN_MCR_RFLM;
        } else {
            CANx->MCR &= ~(uint32_t)CAN_MCR_RFLM;
        }

        /* 设置 传输FIFO优先级 */
        if (CAN_InitStruct->CAN_TXFP == ENABLE) {
            CANx->MCR |= CAN_MCR_TXFP;
        } else {
            CANx->MCR &= ~(uint32_t)CAN_MCR_TXFP;
        }

        /* 设置 bit timing 寄存器 */
        CANx->BTR = (uint32_t)((uint32_t)CAN_InitStruct->CAN_Mode << 30) | \
                    ((uint32_t)CAN_InitStruct->CAN_SJW << 24) | \
                    ((uint32_t)CAN_InitStruct->CAN_BS1 << 16) | \
                    ((uint32_t)CAN_InitStruct->CAN_BS2 << 20) | \
                    ((uint32_t)CAN_InitStruct->CAN_Prescaler - 1);

        /* 请求休假初始化 */
        CANx->MCR &= ~(uint32_t)CAN_MCR_INRQ;

        /* 等待确认 */
        wait_ack = 0;

        while (((CANx->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) && (wait_ack != INAK_TIMEOUT)) {
            wait_ack++;
        }

        /* ...and 检查确认d */
        if ((CANx->MSR & CAN_MSR_INAK) == CAN_MSR_INAK) {
            InitStatus = CAN_InitStatus_Failed;
        } else {
            InitStatus = CAN_InitStatus_Success ;
        }
    }

    /* 在此步骤中，返回初始化状态 */
    return InitStatus;
}

#if defined(STM32F413_423xx)
/**
  * 简介:  根据 CAN_FilterInitStruct 中的指定参数配置 CAN 接收滤波器。
  * 
  * 参数:  CANx: 其中 x 可以是1或3，以选择 CAN 外设设备。
  * 
  * 参数:  CAN_FilterInitStruct: 指向包含配置信息的 CAN_FilterInitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void CAN_FilterInit(CAN_TypeDef* CANx, CAN_FilterInitTypeDef* CAN_FilterInitStruct) {
    uint32_t filter_number_bit_pos = 0;
    /* 检查参数 */
    assert_param(IS_CAN_FILTER_NUMBER(CAN_FilterInitStruct->CAN_FilterNumber));
    assert_param(IS_CAN_FILTER_MODE(CAN_FilterInitStruct->CAN_FilterMode));
    assert_param(IS_CAN_FILTER_SCALE(CAN_FilterInitStruct->CAN_FilterScale));
    assert_param(IS_CAN_FILTER_FIFO(CAN_FilterInitStruct->CAN_FilterFIFOAssignment));
    assert_param(IS_FUNCTIONAL_STATE(CAN_FilterInitStruct->CAN_FilterActivation));

    filter_number_bit_pos = ((uint32_t)1) << CAN_FilterInitStruct->CAN_FilterNumber;

    /* 过滤器的初始化模式 */
    CANx->FMR |= FMR_FINIT;

    /* 过滤器停用 */
    CANx->FA1R &= ~(uint32_t)filter_number_bit_pos;

    /* 过滤器刻度 */
    if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_16bit) {
        /* 滤波器的16位刻度 */
        CANx->FS1R &= ~(uint32_t)filter_number_bit_pos;

        /* 前16位标识符和前16位掩码 */
        /* 或第一个16位标识符和第二个16位标识 */
        CANx->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdLow) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);

        /* 第二个16位标识符和第二个16-位掩码 */
        /* 或第三个16位标识符和第四个16位标识 */
        CANx->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh);
    }

    if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_32bit) {
        /* 过滤器的32位刻度 */
        CANx->FS1R |= filter_number_bit_pos;
        /* 32位标识符或第一个32位标识符 */
        CANx->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);
        /* 32位掩码或第二个32位标识符 */
        CANx->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdLow);
    }

    /* 过滤器模式 */
    if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask) {
        /* 过滤器的 Id/Mask 模式 */
        CANx->FM1R &= ~(uint32_t)filter_number_bit_pos;
    } else { /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
        /*筛选器的标识符列表模式*/
        CANx->FM1R |= (uint32_t)filter_number_bit_pos;
    }

    /* 过滤器 FIFO 分配 */
    if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO0) {
        /* 过滤器的 FIFO 0 分配 */
        CANx->FFA1R &= ~(uint32_t)filter_number_bit_pos;
    }

    if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO1) {
        /* 过滤器的 FIFO 1 分配 */
        CANx->FFA1R |= (uint32_t)filter_number_bit_pos;
    }

    /* 过滤器激活 */
    if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE) {
        CANx->FA1R |= filter_number_bit_pos;
    }

    /* Leave the 过滤器的初始化模式 */
    CANx->FMR &= ~FMR_FINIT;
}
#else
/**
  * 简介:  根据 CAN_FilterInitStruct 中的指定参数配置 CAN 接收滤波器。
  * 
  * 参数:  CAN_FilterInitStruct: 指向包含配置信息的 CAN_FilterInitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void CAN_FilterInit(CAN_FilterInitTypeDef* CAN_FilterInitStruct) {
    uint32_t filter_number_bit_pos = 0;
    /* 检查参数 */
    assert_param(IS_CAN_FILTER_NUMBER(CAN_FilterInitStruct->CAN_FilterNumber));
    assert_param(IS_CAN_FILTER_MODE(CAN_FilterInitStruct->CAN_FilterMode));
    assert_param(IS_CAN_FILTER_SCALE(CAN_FilterInitStruct->CAN_FilterScale));
    assert_param(IS_CAN_FILTER_FIFO(CAN_FilterInitStruct->CAN_FilterFIFOAssignment));
    assert_param(IS_FUNCTIONAL_STATE(CAN_FilterInitStruct->CAN_FilterActivation));

    filter_number_bit_pos = ((uint32_t)1) << CAN_FilterInitStruct->CAN_FilterNumber;

    /* 过滤器的初始化模式 */
    CAN1->FMR |= FMR_FINIT;

    /* 过滤器停用 */
    CAN1->FA1R &= ~(uint32_t)filter_number_bit_pos;

    /* 过滤器刻度 */
    if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_16bit) {
        /* 滤波器的16位刻度 */
        CAN1->FS1R &= ~(uint32_t)filter_number_bit_pos;

        /* 前16位标识符和前16位掩码 */
        /* 或第一个16位标识符和第二个16位标识 */
        CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdLow) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);

        /* 第二个16位标识符和第二个16-位掩码 */
        /* 或第三个16位标识符和第四个16位标识 */
        CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh);
    }

    if (CAN_FilterInitStruct->CAN_FilterScale == CAN_FilterScale_32bit) {
        /* 过滤器的32位刻度 */
        CAN1->FS1R |= filter_number_bit_pos;
        /* 32位标识符或第一个32位标识符 */
        CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterIdLow);
        /* 32位掩码或第二个32位标识符 */
        CAN1->sFilterRegister[CAN_FilterInitStruct->CAN_FilterNumber].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdHigh) << 16) |
            (0x0000FFFF & (uint32_t)CAN_FilterInitStruct->CAN_FilterMaskIdLow);
    }

    /* 过滤器模式 */
    if (CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdMask) {
        /*过滤器的 Id/Mask 模式*/
        CAN1->FM1R &= ~(uint32_t)filter_number_bit_pos;
    } else { /* CAN_FilterInitStruct->CAN_FilterMode == CAN_FilterMode_IdList */
        /*筛选器的标识符列表模式*/
        CAN1->FM1R |= (uint32_t)filter_number_bit_pos;
    }

    /* 过滤器 FIFO 分配 */
    if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO0) {
        /* 过滤器的 FIFO 0 分配 */
        CAN1->FFA1R &= ~(uint32_t)filter_number_bit_pos;
    }

    if (CAN_FilterInitStruct->CAN_FilterFIFOAssignment == CAN_Filter_FIFO1) {
        /* 过滤器的 FIFO 1 分配 */
        CAN1->FFA1R |= (uint32_t)filter_number_bit_pos;
    }

    /* 过滤器激活 */
    if (CAN_FilterInitStruct->CAN_FilterActivation == ENABLE) {
        CAN1->FA1R |= filter_number_bit_pos;
    }

    /* Leave the 过滤器的初始化模式 */
    CAN1->FMR &= ~FMR_FINIT;
}
#endif /* STM32F413_423xx */

/**
  * 简介:  把 CAN_InitStruct 中的每一个参数按缺省值填入
  * 
  * 参数:  CAN_InitStruct: 指向将被初始化的 CAN_InitTypeDef 结构的指针。
  * 
  * 返回值: 无
  */
void CAN_StructInit(CAN_InitTypeDef* CAN_InitStruct) {
    /* 重置 CAN初始化结构参数值 */

    /* 初始化 时间触发通信模式 */
    CAN_InitStruct->CAN_TTCM = DISABLE;

    /* 初始化 自动总线关闭管理 */
    CAN_InitStruct->CAN_ABOM = DISABLE;

    /* 初始化 自动唤醒模式 */
    CAN_InitStruct->CAN_AWUM = DISABLE;

    /* 初始化 无自动重发 */
    CAN_InitStruct->CAN_NART = DISABLE;

    /* 初始化 接收 FIFO锁定模式*/
    CAN_InitStruct->CAN_RFLM = DISABLE;

    /* 初始化 传输FIFO优先级 */
    CAN_InitStruct->CAN_TXFP = DISABLE;

    /* 初始化 CAN_Mode 成员 */
    CAN_InitStruct->CAN_Mode = CAN_Mode_Normal;

    /* 初始化 CAN_SJW 成员 */
    CAN_InitStruct->CAN_SJW = CAN_SJW_1tq;

    /* 初始化 CAN_BS1 成员 */
    CAN_InitStruct->CAN_BS1 = CAN_BS1_4tq;

    /* 初始化 CAN_BS2 成员 */
    CAN_InitStruct->CAN_BS2 = CAN_BS2_3tq;

    /* 初始化 CAN_Prescaler 成员 */
    CAN_InitStruct->CAN_Prescaler = 1;
}

#if defined(STM32F413_423xx)
/**
  * 简介:  把 CAN_InitStruct 中的每一个参数按缺省值填入
  * 
  * 参数:  CANx: 其中 x 可以是1或3，以选择 CAN 外设设备。
  * 
  * 参数:  CAN_BankNumber: 从1..27中选择启动从组过滤器。
  * 
  * 返回值: 无
  */
void CAN_SlaveStartBank(CAN_TypeDef* CANx, uint8_t CAN_BankNumber) {
    /* 检查参数 */
    assert_param(IS_CAN_BANKNUMBER(CAN_BankNumber));

    /* Enter 过滤器的初始化模式 */
    CANx->FMR |= FMR_FINIT;

    /* 选择这个启动从组 */
    CANx->FMR &= (uint32_t)0xFFFFC0F1 ;
    CANx->FMR |= (uint32_t)(CAN_BankNumber) << 8;

    /* Leave 过滤器的初始化模式 */
    CANx->FMR &= ~FMR_FINIT;
}
#else
/**
  * 简介:  选择从 CAN 的起始组过滤器。
  * 
  * 参数:  CAN_BankNumber: 从1..27中选择启动从组过滤器。
  * 
  * 返回值: 无
  */
void CAN_SlaveStartBank(uint8_t CAN_BankNumber) {
    /* 检查参数 */
    assert_param(IS_CAN_BANKNUMBER(CAN_BankNumber));

    /* Enter 过滤器的初始化模式 */
    CAN1->FMR |= FMR_FINIT;

    /* 选择这个启动从组 */
    CAN1->FMR &= (uint32_t)0xFFFFC0F1 ;
    CAN1->FMR |= (uint32_t)(CAN_BankNumber) << 8;

    /* Leave 过滤器的初始化模式 */
    CAN1->FMR &= ~FMR_FINIT;
}
#endif /* STM32F413_423xx */
/**
  * 简介:  启用或禁用 CAN 的 DBG 冻结。
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  NewState: CAN 外设设备的新状态。
  *          此参数可以是: ENABLE(调试期间 CAN 接收/传输被冻结。仍可以正常访问/控制接收 FIFO)
  *                       或 DISABLE(CAN在调试期间工作)。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 无
  */
void CAN_DBGFreeze(CAN_TypeDef* CANx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用调试冻结  */
        CANx->MCR |= MCR_DBF;
    } else {
        /* 禁用调试冻结 */
        CANx->MCR &= ~MCR_DBF;
    }
}


/**
  * 简介:  启用或禁用 CAN Time TriggerOperation 通信模式。
  * 
  * 注意:   DLC必须编程为8，以便通过 CAN 总线发送时间戳(2字节)。
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  NewState: 模式新状态。 此参数可以是: ENABLE 或 DISABLE。
  *         启用时，在8字节消息的最后两个数据字节中发送时间戳(Time[15:0])值:数据字节6中的 Time[7:0]，数据字节7中的 Time[15:8]。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 无
  */
void CAN_TTComModeCmd(CAN_TypeDef* CANx, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用 TTCM 模式 */
        CANx->MCR |= CAN_MCR_TTCM;

        /* Set TGT 位 */
        CANx->sTxMailBox[0].TDTR |= ((uint32_t)CAN_TDT0R_TGT);
        CANx->sTxMailBox[1].TDTR |= ((uint32_t)CAN_TDT1R_TGT);
        CANx->sTxMailBox[2].TDTR |= ((uint32_t)CAN_TDT2R_TGT);
    } else {
        /* 禁用 TTCM 模式 */
        CANx->MCR &= (uint32_t)(~(uint32_t)CAN_MCR_TTCM);

        /* 重置 TGT 位 */
        CANx->sTxMailBox[0].TDTR &= ((uint32_t)~CAN_TDT0R_TGT);
        CANx->sTxMailBox[1].TDTR &= ((uint32_t)~CAN_TDT1R_TGT);
        CANx->sTxMailBox[2].TDTR &= ((uint32_t)~CAN_TDT2R_TGT);
    }
}


/** @defgroup CAN_Group2 CAN 帧传输功能
 *  简介    CAN 帧传输功能
 *
@verbatim
 ===============================================================================
                ##### CAN 帧传输功能 #####
 ===============================================================================
    [..] 本节提供的功能允许
      (+) 启动并传输 CAN 帧信息(如果邮箱为空)。
      (+) 检查 CAN 帧的传输状态
      (+) 取消传输请求

@endverbatim
  */

/**
  * 简介:  开始一个消息的传输
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  TxMessage: 指向包含 CAN Id、CAN DLC 和 CAN 数据的结构的指针。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 用于传输的邮箱的编号，如果没有空邮箱，则为 CAN_TxStatus_NoMailBox。
  */
uint8_t CAN_Transmit(CAN_TypeDef* CANx, CanTxMsg* TxMessage) {
    uint8_t transmit_mailbox = 0;
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_IDTYPE(TxMessage->IDE));
    assert_param(IS_CAN_RTR(TxMessage->RTR));
    assert_param(IS_CAN_DLC(TxMessage->DLC));

    /* 选择一个空传输邮箱 */
    if ((CANx->TSR & CAN_TSR_TME0) == CAN_TSR_TME0) {
        transmit_mailbox = 0;
    } else if ((CANx->TSR & CAN_TSR_TME1) == CAN_TSR_TME1) {
        transmit_mailbox = 1;
    } else if ((CANx->TSR & CAN_TSR_TME2) == CAN_TSR_TME2) {
        transmit_mailbox = 2;
    } else {
        transmit_mailbox = CAN_TxStatus_NoMailBox;
    }

    if (transmit_mailbox != CAN_TxStatus_NoMailBox) {
        /* 设置Id */
        CANx->sTxMailBox[transmit_mailbox].TIR &= TMIDxR_TXRQ;

        if (TxMessage->IDE == CAN_Id_Standard) {
            assert_param(IS_CAN_STDID(TxMessage->StdId));
            CANx->sTxMailBox[transmit_mailbox].TIR |= ((TxMessage->StdId << 21) | \
                    TxMessage->RTR);
        } else {
            assert_param(IS_CAN_EXTID(TxMessage->ExtId));
            CANx->sTxMailBox[transmit_mailbox].TIR |= ((TxMessage->ExtId << 3) | \
                    TxMessage->IDE | \
                    TxMessage->RTR);
        }

        /* 设置 DLC */
        TxMessage->DLC &= (uint8_t)0x0000000F;
        CANx->sTxMailBox[transmit_mailbox].TDTR &= (uint32_t)0xFFFFFFF0;
        CANx->sTxMailBox[transmit_mailbox].TDTR |= TxMessage->DLC;

        /* 设置数据字段 */
        CANx->sTxMailBox[transmit_mailbox].TDLR = (((uint32_t)TxMessage->Data[3] << 24) |
                ((uint32_t)TxMessage->Data[2] << 16) |
                ((uint32_t)TxMessage->Data[1] << 8) |
                ((uint32_t)TxMessage->Data[0]));
        CANx->sTxMailBox[transmit_mailbox].TDHR = (((uint32_t)TxMessage->Data[7] << 24) |
                ((uint32_t)TxMessage->Data[6] << 16) |
                ((uint32_t)TxMessage->Data[5] << 8) |
                ((uint32_t)TxMessage->Data[4]));
        /* 请求传输 */
        CANx->sTxMailBox[transmit_mailbox].TIR |= TMIDxR_TXRQ;
    }

    return transmit_mailbox;
}

/**
  * 简介:  检查消息传输的状态
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  TransmitMailbox: 用于传输的邮箱的编号。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: CAN_TxStatus_Ok如果 CAN 驱动器传输消息，
  *         则在其他情况下CAN_Tx Status_Failed(CAN_Tx-Status_失败)。
  */
uint8_t CAN_TransmitStatus(CAN_TypeDef* CANx, uint8_t TransmitMailbox) {
    uint32_t state = 0;

    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_TRANSMITMAILBOX(TransmitMailbox));

    switch (TransmitMailbox) {
        case (CAN_TXMAILBOX_0):
            state =   CANx->TSR &  (CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_TME0);
            break;

        case (CAN_TXMAILBOX_1):
            state =   CANx->TSR &  (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_TME1);
            break;

        case (CAN_TXMAILBOX_2):
            state =   CANx->TSR &  (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_TME2);
            break;

        default:
            state = CAN_TxStatus_Failed;
            break;
    }

    switch (state) {
        /* 传输挂起  */
        case (0x0):
            state = CAN_TxStatus_Pending;
            break;

        /* 传输失败  */
        case (CAN_TSR_RQCP0 | CAN_TSR_TME0):
            state = CAN_TxStatus_Failed;
            break;

        case (CAN_TSR_RQCP1 | CAN_TSR_TME1):
            state = CAN_TxStatus_Failed;
            break;

        case (CAN_TSR_RQCP2 | CAN_TSR_TME2):
            state = CAN_TxStatus_Failed;
            break;

        /* 传输成功  */
        case (CAN_TSR_RQCP0 | CAN_TSR_TXOK0 | CAN_TSR_TME0):
            state = CAN_TxStatus_Ok;
            break;

        case (CAN_TSR_RQCP1 | CAN_TSR_TXOK1 | CAN_TSR_TME1):
            state = CAN_TxStatus_Ok;
            break;

        case (CAN_TSR_RQCP2 | CAN_TSR_TXOK2 | CAN_TSR_TME2):
            state = CAN_TxStatus_Ok;
            break;

        default:
            state = CAN_TxStatus_Failed;
            break;
    }

    return (uint8_t) state;
}

/**
  * 简介:  取消一个传输请求
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  Mailbox: 邮箱编号
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 无
  */
void CAN_CancelTransmit(CAN_TypeDef* CANx, uint8_t Mailbox) {
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_TRANSMITMAILBOX(Mailbox));

    /* 中止传输 */
    switch (Mailbox) {
        case (CAN_TXMAILBOX_0):
            CANx->TSR |= CAN_TSR_ABRQ0;
            break;

        case (CAN_TXMAILBOX_1):
            CANx->TSR |= CAN_TSR_ABRQ1;
            break;

        case (CAN_TXMAILBOX_2):
            CANx->TSR |= CAN_TSR_ABRQ2;
            break;

        default:
            break;
    }
}


/** @defgroup CAN_Group3 CAN 帧接收功能
 *  简介    CAN 帧接收功能
 *
@verbatim
 ===============================================================================
                ##### CAN 帧接收功能 #####
 ===============================================================================
    [..] 本节提供的功能允许
        (+) 接收正确的 CAN 帧

        (+) 释放指定的接收 FIFO(2个 FIFO可用)

        (+) 返回等待接收的 CAN 帧的数量

@endverbatim
  */

/**
  * 简介:  接收一个消息
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  FIFONumber: 接收 FIFO 编号、CAN_FIFO0 或 CAN_FFIFO1。
  * 
  * 参数:  RxMessage: 指向包含 CAN Id、CAN DLC、CAN 数据和 FMI 编号的结构接收帧的指针。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 无
  */
void CAN_Receive(CAN_TypeDef* CANx, uint8_t FIFONumber, CanRxMsg* RxMessage) {
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONumber));
    /* 获取 Id */
    RxMessage->IDE = (uint8_t)0x04 & CANx->sFIFOMailBox[FIFONumber].RIR;

    if (RxMessage->IDE == CAN_Id_Standard) {
        RxMessage->StdId = (uint32_t)0x000007FF & (CANx->sFIFOMailBox[FIFONumber].RIR >> 21);
    } else {
        RxMessage->ExtId = (uint32_t)0x1FFFFFFF & (CANx->sFIFOMailBox[FIFONumber].RIR >> 3);
    }

    RxMessage->RTR = (uint8_t)0x02 & CANx->sFIFOMailBox[FIFONumber].RIR;
    /* 获取 DLC */
    RxMessage->DLC = (uint8_t)0x0F & CANx->sFIFOMailBox[FIFONumber].RDTR;
    /* 获取 FMI */
    RxMessage->FMI = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDTR >> 8);
    /* 获取数据字段 */
    RxMessage->Data[0] = (uint8_t)0xFF & CANx->sFIFOMailBox[FIFONumber].RDLR;
    RxMessage->Data[1] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 8);
    RxMessage->Data[2] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 16);
    RxMessage->Data[3] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDLR >> 24);
    RxMessage->Data[4] = (uint8_t)0xFF & CANx->sFIFOMailBox[FIFONumber].RDHR;
    RxMessage->Data[5] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 8);
    RxMessage->Data[6] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 16);
    RxMessage->Data[7] = (uint8_t)0xFF & (CANx->sFIFOMailBox[FIFONumber].RDHR >> 24);

    /* 释放FIFO */
    /* 释放FIFO0 */
    if (FIFONumber == CAN_FIFO0) {
        CANx->RF0R |= CAN_RF0R_RFOM0;
    }
    /* 释放 FIFO1 */
    else { /* FIFONumber == CAN_FIFO1 */
        CANx->RF1R |= CAN_RF1R_RFOM1;
    }
}

/**
  * 简介:  释放一个 FIFO
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  FIFONumber: 要释放的 FIFO，CAN_FIFO0 或 CAN_FFIFO1。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 无
  */
void CAN_FIFORelease(CAN_TypeDef* CANx, uint8_t FIFONumber) {
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONumber));

    /* 释放FIFO0 */
    if (FIFONumber == CAN_FIFO0) {
        CANx->RF0R |= CAN_RF0R_RFOM0;
    }
    /* 释放FIFO1 */
    else { /* FIFONumber == CAN_FIFO1 */
        CANx->RF1R |= CAN_RF1R_RFOM1;
    }
}

/**
  * 简介:  返回挂号的信息数量
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  FIFONumber: 接收 FIFO 编号、CAN_FIFO0 或 CAN_FFIFO1。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: NbMessage : 这是挂起消息的数量。
  */
uint8_t CAN_MessagePending(CAN_TypeDef* CANx, uint8_t FIFONumber) {
    uint8_t message_pending = 0;
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_FIFO(FIFONumber));

    if (FIFONumber == CAN_FIFO0) {
        message_pending = (uint8_t)(CANx->RF0R & (uint32_t)0x03);
    } else if (FIFONumber == CAN_FIFO1) {
        message_pending = (uint8_t)(CANx->RF1R & (uint32_t)0x03);
    } else {
        message_pending = 0;
    }

    return message_pending;
}


/** @defgroup CAN_Group4 CAN 操作模式功能
 *  简介    CAN 操作模式功能
 *
@verbatim
 ===============================================================================
                    ##### CAN 操作模式功能 #####
 ===============================================================================
    [..] 本节提供的功能允许选择 CAN 操作模式
        (+) 睡眠模式

        (+) 正常模式

        (+) 初始化模式

@endverbatim
  */


/**
  * 简介:  选择 CAN 操作模式。
  * 
  * 参数:  CAN_OperatingMode: CAN 工作模式。
  *         此参数可以是 @ref can_OperatingMode_TypeDef枚举之一。
  * 
  * 返回值: 请求模式的状态，可以是
  *         - CAN_ModeStatus_Failed:  CAN 无法进入特定模式
  *         - CAN_ModeStatus_Success: CAN 成功进入特定模式
  */
uint8_t CAN_OperatingModeRequest(CAN_TypeDef* CANx, uint8_t CAN_OperatingMode) {
    uint8_t status = CAN_ModeStatus_Failed;

    /* INAK 或 SLAK位超时 */
    uint32_t timeout = INAK_TIMEOUT;

    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_OPERATING_MODE(CAN_OperatingMode));

    if (CAN_OperatingMode == CAN_OperatingMode_Initialization) {
        /* 请求初始化 */
        CANx->MCR = (uint32_t)((CANx->MCR & (uint32_t)(~(uint32_t)CAN_MCR_SLEEP)) | CAN_MCR_INRQ);

        /* 等待确认 */
        while (((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_INAK) && (timeout != 0)) {
            timeout--;
        }

        if ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_INAK) {
            status = CAN_ModeStatus_Failed;
        } else {
            status = CAN_ModeStatus_Success;
        }
    } else  if (CAN_OperatingMode == CAN_OperatingMode_Normal) {
        /* 请求休假初始化 and sleep mode  and enter Normal mode */
        CANx->MCR &= (uint32_t)(~(CAN_MCR_SLEEP | CAN_MCR_INRQ));

        /* 等待确认 */
        while (((CANx->MSR & CAN_MODE_MASK) != 0) && (timeout != 0)) {
            timeout--;
        }

        if ((CANx->MSR & CAN_MODE_MASK) != 0) {
            status = CAN_ModeStatus_Failed;
        } else {
            status = CAN_ModeStatus_Success;
        }
    } else  if (CAN_OperatingMode == CAN_OperatingMode_Sleep) {
        /* 请求睡眠模式 */
        CANx->MCR = (uint32_t)((CANx->MCR & (uint32_t)(~(uint32_t)CAN_MCR_INRQ)) | CAN_MCR_SLEEP);

        /* 等待确认 */
        while (((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_SLAK) && (timeout != 0)) {
            timeout--;
        }

        if ((CANx->MSR & CAN_MODE_MASK) != CAN_MSR_SLAK) {
            status = CAN_ModeStatus_Failed;
        } else {
            status = CAN_ModeStatus_Success;
        }
    } else {
        status = CAN_ModeStatus_Failed;
    }

    return  (uint8_t) status;
}

/**
  * 简介:  CAN 进入低功耗模式
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 如果进入睡眠，CAN_Sleep_Ok，否则 CAN_Sleep_Failed。
  */
uint8_t CAN_Sleep(CAN_TypeDef* CANx) {
    uint8_t sleepstatus = CAN_Sleep_Failed;

    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* 请求睡眠模式 */
    CANx->MCR = (((CANx->MCR) & (uint32_t)(~(uint32_t)CAN_MCR_INRQ)) | CAN_MCR_SLEEP);

    /* 睡眠模式状态 */
    if ((CANx->MSR & (CAN_MSR_SLAK | CAN_MSR_INAK)) == CAN_MSR_SLAK) {
        /* Sleep mode not entered */
        sleepstatus =  CAN_Sleep_Ok;
    }

    /* 返回睡眠模式状态 */
    return (uint8_t)sleepstatus;
}

/**
  * 简介:  从休眠模式唤醒CAN 外设设备。
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: CAN_WakeUp_Ok(如果睡眠模式离开)，否则 CAN_WakeUp_Failed(CAN_WakeUp_失败)。
  */
uint8_t CAN_WakeUp(CAN_TypeDef* CANx) {
    uint32_t wait_slak = SLAK_TIMEOUT;
    uint8_t wakeupstatus = CAN_WakeUp_Failed;

    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* 唤醒请求 */
    CANx->MCR &= ~(uint32_t)CAN_MCR_SLEEP;

    /* 睡眠模式状态 */
    while(((CANx->MSR & CAN_MSR_SLAK) == CAN_MSR_SLAK) && (wait_slak != 0x00)) {
        wait_slak--;
    }

    if((CANx->MSR & CAN_MSR_SLAK) != CAN_MSR_SLAK) {
        /* 唤醒完成:睡眠模式已退出 */
        wakeupstatus = CAN_WakeUp_Ok;
    }

    /* 返回唤醒状态 */
    return (uint8_t)wakeupstatus;
}


/** @defgroup CAN_Group5 CAN 总线错误管理功能
 *  简介    CAN 总线错误管理功能
 *
@verbatim
 ===============================================================================
                ##### CAN 总线错误管理功能 #####
 ===============================================================================
    [..] 本节提供的功能允许
        (+) 返回 CANx 的最后一个错误代码(LEC)

        (+) 返回 CANx 接收错误计数器(REC)

        (+) 返回9位 CANx 传输错误计数器(TEC)的 LSB。

    -@- 如果TEC大于255，则 CAN 处于总线关闭状态。
    -@- 如果REC或 TEC大于96，则会出现错误警告标志。
    -@- 如果REC或 TEC大于127，则会出现错误被动标志。

@endverbatim
  */

/**
  * 简介:  返回 CANx 的最后一个错误代码 (LEC)。
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 返回值: 错误代码:
  *          - CAN_ERRORCODE_NoErr:无错误
  *          - CAN_ERRORCODE_StuffErr:填充错误
  *          - CAN_ERRORCODE_FormErr:表单错误
  *          - CAN_ERRORCODE_ACKErr:确认错误
  *          - CAN_ERRORCODE_BitRecessiveErr:位隐藏错误
  *          - CAN_ERRORCODE_BitDominantErr:位主导错误
  *          - CAN_ERRORCODE_CRCErr: CRC 错误
  *          - CAN_ERRORCODE_SoftwareSetErr:软件设置错误
  */
uint8_t CAN_GetLastErrorCode(CAN_TypeDef* CANx) {
    uint8_t errorcode = 0;

    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* 获取错误代码 */
    errorcode = (((uint8_t)CANx->ESR) & (uint8_t)CAN_ESR_LEC);

    /* 返回错误代码 */
    return errorcode;
}

/**
  * 简介:  返回 CANx 接收错误计数器 (REC)。
  * 
  * 注意:   如果在接收过程中出现错误，此计数器将根据 CAN 标准定义的错误条件增加1或8。
  *             每次成功接收后，计数器将递减1，如果其值高于128，则重置为120。
  *         当计数器值超过127时，CAN 控制器进入错误被动状态。
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: CAN 接收错误计数器。
  */
uint8_t CAN_GetReceiveErrorCounter(CAN_TypeDef* CANx) {
    uint8_t counter = 0;

    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* 获取接收错误计数器*/
    counter = (uint8_t)((CANx->ESR & CAN_ESR_REC) >> 24);

    /* 返回接收错误计数器*/
    return counter;
}


/**
  * 简介:  返回 9 位 CANx 发送错误计数器 (TEC) 的 LSB。
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: 9位 CAN传输错误计数器的 LSB。
  */
uint8_t CAN_GetLSBTransmitErrorCounter(CAN_TypeDef* CANx) {
    uint8_t counter = 0;

    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));

    /* 获取9位 CANx 传输错误计数器(TEC)的 LSB*/
    counter = (uint8_t)((CANx->ESR & CAN_ESR_TEC) >> 16);

    /* 返回9位 CANx 传输错误计数器(TEC)的 LSB */
    return counter;
}

/** @defgroup CAN_Group6 中断和标记管理函数
 *  简介   中断和标记管理函数
 *
@verbatim
 ===============================================================================
              ##### 中断和标记管理函数 #####
 ===============================================================================

     [..] 本节提供的功能允许 配置 CAN 中断并获取状态、清除标志和中断挂起位。

          CAN提供14个中断源和15个标志:


  *** 标志 ***
  =============
    [..] 这15个标志可分为4组:

      (+) 发送标志
        (++) CAN_FLAG_RQCP0,
        (++) CAN_FLAG_RQCP1,
        (++) CAN_FLAG_RQCP2  : 执行最后一个请求(传输或中止)时，请求已完成 MailBoxes 0、1和2标志集。

      (+) 接收标志


        (++) CAN_FLAG_FMP0,
        (++) CAN_FLAG_FMP1   : FIFO 0 和1消息挂起标志设置为表示消息在接收 FIFO 中挂起。
                               这些标志仅由硬件清除。

        (++) CAN_FLAG_FF0,
        (++) CAN_FLAG_FF1    : FIFO 0 和1满标志
                               当三条消息存储在选定的 FIFO 中时设置。

        (++) CAN_FLAG_FOV0
        (++) CAN_FLAG_FOV1   : FIFO 0 和1溢出标志
                               当接收到新消息并在 FIFO 已满时通过过滤器时设置。

      (+) 操作模式标志

        (++) CAN_FLAG_WKU    : 唤醒标志
                               设置为在 CAN 硬件处于休眠模式时检测到 SOF 位的信号。

        (++) CAN_FLAG_SLAK   : 睡眠确认标志
                               设置为发出 CAN已进入休眠模式的信号。

      (+) Error Flags

        (++) CAN_FLAG_EWG    : 错误警告标志
                               达到警告限制时设置(接收错误计数器或传输错误计数器大于96)。
                               此标志仅由硬件清除。

        (++) CAN_FLAG_EPV    : 错误被动标志
                               当达到错误被动限制时设置(接收错误计数器或传输错误计数器大于127)。
                               此标志仅由硬件清除。

        (++) CAN_FLAG_BOF    : 总线关闭标志
                               当 CAN 进入总线关闭状态时设置。TEC 溢出大于255时进入总线关闭状态。
                               此标志仅由硬件清除。

        (++) CAN_FLAG_LEC    : 上次错误代码标志
                               set如果信息传输(接收或传输)出错，且错误代码被保留。

  *** 中断 ***
  ==================
    [..] 14个中断可分为4组:

      (+) 传输中断

        (++) CAN_IT_TME   :  传输邮箱空中断如果启用，则当没有传输邮箱的传输请求挂起时，此中断源将挂起。

      (+) 接收中断

        (++) CAN_IT_FMP0,
        (++) CAN_IT_FMP1    :  FIFO 0 和 FIFO1消息挂起中断
                                    如果启用，当消息在接收 FIFO 中挂起时，这些中断源将挂起。
                                    相应的中断挂起位仅由硬件清除。

        (++) CAN_IT_FF0,
        (++) CAN_IT_FF1     :  如果启用 FIFO 0 和 FIFO1 完全中断，
                                    则当三条消息存储在选定的 FIFO 中时，这些中断源处于挂起状态。

        (++) CAN_IT_FOV0,
        (++) CAN_IT_FOV1    :  FIFO 0 和 FIFO1溢出中断(如果启用)，
                                    当 FIFO 已满时接收到新消息并通过过滤器时，这些中断源处于待定状态。

      (+) 操作模式中断

        (++) CAN_IT_WKU     :  唤醒中断
                                    如果启用，则当 CAN 硬件处于休眠模式时检测到 SOF 位时，此中断源处于挂起状态。

        (++) CAN_IT_SLK     :  睡眠确认中断
                                    如果启用，当 CAN 进入休眠模式时，此中断源处于待定状态。

      (+) 错误中断

        (++) CAN_IT_EWG : 错误警告中断
                               如果启用，当达到警告极限时，该中断源被挂起(接收错误计数器或发送错误计数器=96)。

        (++) CAN_IT_EPV : 错误被动中断
                               如果启用，当达到错误被动限制(接收错误计数器或发送错误计数器>127)时，这个中断源被挂起。

        (++) CAN_IT_BOF : 总线关闭中断
                               如果启用，当 CAN 进入总线关闭状态时，这个中断源被挂起。总线关闭状态是在 TEC 溢出时进入的，大于255。
                               这个标志只能由硬件来清除。

        (++) CAN_IT_LEC : 最后的错误代码中断
                               如果启用，当信息在传输(接收或发送)过程中出现错误，并且错误代码被保留时，这个中断源将被挂起。

        (++) CAN_IT_ERR : 错误中断
                               如果启用，当有错误情况发生时，该中断源将被挂起。

    [...] 管理 CAN 控制器的事件。

         用户应该确定在他的应用程序中使用哪种模式来管理 CAN 控制器事件。管理 CAN 控制器的事件。轮询模式或中断模式。

      (#) 在轮询模式下，建议使用以下函数。
        (++) CAN_GetFlagStatus() : 检查是否发生了标志事件。
        (++) CAN_ClearFlag() : 清除标志事件。



      (#) 在中断模式下，建议使用以下函数。
        (++) CAN_ITConfig() : 启用或禁用中断源。
        (++) CAN_GetITStatus() : 检查是否发生中断。
        (++) CAN_ClearITPendingBit() : 清除中断挂起的位 (相应的标志)。
        -@@- 这个函数对CAN_IT_FMP0 和 CAN_IT_FMP1 中断等待位没有影响，因为它们只被硬件清除。

通过www.DeepL.com/Translator(免费版)翻译

@endverbatim
  */
/**
  * 简介: 启用或停用指定的 CANx 中断。
  * 
  * 参数: CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  CAN_IT: 指定要启用或禁用的 CAN 中断源。
  *        这个参数可以是:
  *             @参数CAN_IT_TME: 发送邮箱空中断。
  *             @arg CAN_IT_FMP0: FIFO 0消息等待中断。
  *             @arg CAN_IT_FF0: FIFO 0已满 中断
  *             @arg CAN_IT_FOV0:FIFO 0超限中断
  *             @arg CAN_IT_FMP1: FIFO 1消息等待中断
  *             @arg CAN_IT_FF1: FIFO 1满了 中断
  *             @arg CAN_IT_FOV1: FIFO 1超限中断
  *             @arg CAN_IT_WKU: 唤醒中断
  *             @arg CAN_IT_SLK: 睡眠确认中断
  *             @arg CAN_IT_EWG: 错误警告中断
  *             @arg CAN_IT_EPV: 错误被动中断
  *             @arg CAN_IT_BOF: 总线关闭中断
  *             @arg CAN_IT_LEC: 最后的错误代码中断
  *             @arg CAN_IT_ERR: 错误中断
  * 
  * 参数:  NewState: CAN 中断的新状态。
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  *          此参数可以是: ENABLE 或 DISABLE。
  * 
  * 返回值: 无
  */
void CAN_ITConfig(CAN_TypeDef* CANx, uint32_t CAN_IT, FunctionalState NewState) {
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_IT(CAN_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        /* 启用选定的 CANx 中断 */
        CANx->IER |= CAN_IT;
    } else {
        /* 禁用选定的 CANx 中断 */
        CANx->IER &= ~CAN_IT;
    }
}
/**
  * 简介:  检查指定的 CAN 标志位被设置与否
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  CAN_FLAG: 指定要检查的标志。
  *          此参数可以是以下值之一:
  *            @arg CAN_FLAG_RQCP0: 请求邮箱0标志
  *            @arg CAN_FLAG_RQCP1: 请求邮箱1标志
  *            @arg CAN_FLAG_RQCP2: 请求邮箱2标志
  *            @arg CAN_FLAG_FMP0: FIFO 0消息等待标志
  *            @arg CAN_FLAG_FF0: FIFO 0满标志
  *            @arg CAN_FLAG_FOV0: FIFO 0超限标志
  *            @arg CAN_FLAG_FMP1: FIFO 1消息等待标志
  *            @arg CAN_FLAG_FF1: FIFO 1满标志
  *            @arg CAN_FLAG_FOV1: FIFO 1超限标志
  *            @arg CAN_FLAG_WKU: 唤醒标志
  *            @arg CAN_FLAG_SLAK: 睡眠确认标志
  *            @arg CAN_FLAG_EWG: 错误警告标志
  *            @arg CAN_FLAG_EPV: 错误被动标志
  *            @arg CAN_FLAG_BOF: 总线关闭标志
  *            @arg CAN_FLAG_LEC: 最后的错误代码标志
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: CAN_FLAG 的新状态(SET 或 RESET)。
  */
FlagStatus CAN_GetFlagStatus(CAN_TypeDef* CANx, uint32_t CAN_FLAG) {
    FlagStatus bitstatus = RESET;

    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_GET_FLAG(CAN_FLAG));


    if((CAN_FLAG & CAN_FLAGS_ESR) != (uint32_t)RESET) {
        /* 检查指定的 CAN 标志的状态 */
        if ((CANx->ESR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET) {
            /* CAN_FLAG 被设置 */
            bitstatus = SET;
        } else {
            /* CAN_FLAG 被重置 */
            bitstatus = RESET;
        }
    } else if((CAN_FLAG & CAN_FLAGS_MSR) != (uint32_t)RESET) {
        /* 检查指定的 CAN 标志的状态 */
        if ((CANx->MSR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET) {
            /* CAN_FLAG 被设置 */
            bitstatus = SET;
        } else {
            /* CAN_FLAG 被重置 */
            bitstatus = RESET;
        }
    } else if((CAN_FLAG & CAN_FLAGS_TSR) != (uint32_t)RESET) {
        /* 检查指定的 CAN 标志的状态 */
        if ((CANx->TSR & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET) {
            /* CAN_FLAG 被设置 */
            bitstatus = SET;
        } else {
            /* CAN_FLAG 被重置 */
            bitstatus = RESET;
        }
    } else if((CAN_FLAG & CAN_FLAGS_RF0R) != (uint32_t)RESET) {
        /* 检查指定的 CAN 标志的状态 */
        if ((CANx->RF0R & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET) {
            /* CAN_FLAG 被设置 */
            bitstatus = SET;
        } else {
            /* CAN_FLAG 被重置 */
            bitstatus = RESET;
        }
    } else { /* If(CAN_FLAG & CAN_FLAGS_RF1R != (uint32_t)RESET) */
        /* 检查指定的 CAN 标志的状态 */
        if ((uint32_t)(CANx->RF1R & (CAN_FLAG & 0x000FFFFF)) != (uint32_t)RESET) {
            /* CAN_FLAG 被设置 */
            bitstatus = SET;
        } else {
            /* CAN_FLAG 被重置 */
            bitstatus = RESET;
        }
    }

    /* 返回 CAN_FLAG状态 */
    return  bitstatus;
}

/**
  * 简介:  清除 CAN 的待处理标志位
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  CAN_FLAG: 指定要清除的标志。
  *          此参数可以是以下值之一:
  *            @arg CAN_FLAG_RQCP0: 请求邮箱0标志
  *            @arg CAN_FLAG_RQCP1: 请求邮箱1标志
  *            @arg CAN_FLAG_RQCP2: 请求邮箱2标志
  *            @arg CAN_FLAG_FF0: FIFO 0满标志
  *            @arg CAN_FLAG_FOV0: FIFO 0超限标志
  *            @arg CAN_FLAG_FF1: FIFO 1满标志
  *            @arg CAN_FLAG_FOV1: FIFO 1超限标志
  *            @arg CAN_FLAG_WKU: 唤醒标志
  *            @arg CAN_FLAG_SLAK: 睡眠确认标志
  *            @arg CAN_FLAG_LEC:最后的错误代码标志
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 返回值: 无
  */
void CAN_ClearFlag(CAN_TypeDef* CANx, uint32_t CAN_FLAG) {
    uint32_t flagtmp = 0;
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_CLEAR_FLAG(CAN_FLAG));

    if (CAN_FLAG == CAN_FLAG_LEC) { /* ESR 寄存器 */
        /* 清除选定的 CAN 标志 */
        CANx->ESR = (uint32_t)RESET;
    } else { /* MSR或 TSR或 RF0R或 RF1R */
        flagtmp = CAN_FLAG & 0x000FFFFF;

        if ((CAN_FLAG & CAN_FLAGS_RF0R) != (uint32_t)RESET) {
            /* 接收标志 */
            CANx->RF0R = (uint32_t)(flagtmp);
        } else if ((CAN_FLAG & CAN_FLAGS_RF1R) != (uint32_t)RESET) {
            /* 接收标志 */
            CANx->RF1R = (uint32_t)(flagtmp);
        } else if ((CAN_FLAG & CAN_FLAGS_TSR) != (uint32_t)RESET) {
            /* 发送标志 */
            CANx->TSR = (uint32_t)(flagtmp);
        } else { /* If((CAN_FLAG & CAN_FLAGS_MSR)!=(uint32_t)RESET) */
            /* 操作模式标志 */
            CANx->MSR = (uint32_t)(flagtmp);
        }
    }
}

/**
  * 简介:  检查指定的 CAN 中断发生与否
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  CAN_IT: 指定要检查的 CAN 中断源。
  *          此参数可以是以下值之一:
  *            @arg CAN_IT_TME: 发送邮箱空中断。
  *            @arg CAN_IT_FMP0: FIFO 0消息等待中断。
  *            @arg CAN_IT_FF0: FIFO 0已满 中断
  *            @arg CAN_IT_FOV0: FIFO 0超限中断
  *            @arg CAN_IT_FMP1: FIFO 1消息等待中断
  *            @arg CAN_IT_FF1: FIFO 1满了中断
  *            @arg CAN_IT_FOV1: FIFO 1超限中断
  *            @arg CAN_IT_WKU: 唤醒中断
  *            @arg CAN_IT_SLK: 睡眠确认中断
  *            @arg CAN_IT_EWG: 错误警告中断
  *            @arg CAN_IT_EPV: 错误被动中断
  *            @arg CAN_IT_BOF: 总线关闭中断
  *            @arg CAN_IT_LEC: 最后的错误代码中断
  *            @arg CAN_IT_ERR: 错误中断
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 
  * 返回值: CAN_IT 的当前状态(SET 或 RESET)。
  */
ITStatus CAN_GetITStatus(CAN_TypeDef* CANx, uint32_t CAN_IT) {
    ITStatus itstatus = RESET;
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_IT(CAN_IT));

    /* 检查中断使能位 */
    if((CANx->IER & CAN_IT) != RESET) {
        /* 在中断被启用的情况下, .... */
        switch (CAN_IT) {
            case CAN_IT_TME:
                /* 检查 CAN_TSR_RQCPx 位 */
                itstatus = CheckITStatus(CANx->TSR, CAN_TSR_RQCP0 | CAN_TSR_RQCP1 | CAN_TSR_RQCP2);
                break;

            case CAN_IT_FMP0:
                /* 检查 CAN_RF0R_FMP0 位 */
                itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FMP0);
                break;

            case CAN_IT_FF0:
                /* 检查 CAN_RF0R_FULL0 位 */
                itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FULL0);
                break;

            case CAN_IT_FOV0:
                /* 检查 CAN_RF0R_FOVR0 位 */
                itstatus = CheckITStatus(CANx->RF0R, CAN_RF0R_FOVR0);
                break;

            case CAN_IT_FMP1:
                /* 检查 CAN_RF1R_FMP1 位 */
                itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FMP1);
                break;

            case CAN_IT_FF1:
                /* 检查 CAN_RF1R_FULL1 位 */
                itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FULL1);
                break;

            case CAN_IT_FOV1:
                /* 检查 CAN_RF1R_FOVR1 位 */
                itstatus = CheckITStatus(CANx->RF1R, CAN_RF1R_FOVR1);
                break;

            case CAN_IT_WKU:
                /* 检查 CAN_MSR_WKUI 位 */
                itstatus = CheckITStatus(CANx->MSR, CAN_MSR_WKUI);
                break;

            case CAN_IT_SLK:
                /* 检查 CAN_MSR_SLAKI 位 */
                itstatus = CheckITStatus(CANx->MSR, CAN_MSR_SLAKI);
                break;

            case CAN_IT_EWG:
                /* 检查 CAN_ESR_EWGF 位 */
                itstatus = CheckITStatus(CANx->ESR, CAN_ESR_EWGF);
                break;

            case CAN_IT_EPV:
                /* 检查 CAN_ESR_EPVF 位 */
                itstatus = CheckITStatus(CANx->ESR, CAN_ESR_EPVF);
                break;

            case CAN_IT_BOF:
                /* 检查 CAN_ESR_BOFF 位 */
                itstatus = CheckITStatus(CANx->ESR, CAN_ESR_BOFF);
                break;

            case CAN_IT_LEC:
                /* 检查 CAN_ESR_LEC 位 */
                itstatus = CheckITStatus(CANx->ESR, CAN_ESR_LEC);
                break;

            case CAN_IT_ERR:
                /* 检查 CAN_MSR_ERRI 位 */
                itstatus = CheckITStatus(CANx->MSR, CAN_MSR_ERRI);
                break;

            default:
                /* 如果出现错误，返回 RESET */
                itstatus = RESET;
                break;
        }
    } else {
        /* 如果中断未被启用，则返回 RESET */
        itstatus  = RESET;
    }

    /* 返回 CAN_IT状态 */
    return  itstatus;
}

/**
  * 简介:  清除 CAN 的中断待处理标志位
  * 
  * 参数:  CANx: 其中 x 可以是1、2 或3，以选择 can 外设设备。
  * 
  * 参数:  CAN_IT: 指定要清除的中断等待位。
  *          此参数可以是以下值之一:
  *            @arg CAN_IT_TME: 发送邮箱空中断。
  *            @arg CAN_IT_FF0: FIFO 0已满中断
  *            @arg CAN_IT_FOV0: FIFO 0超限中断
  *            @arg CAN_IT_FF1: FIFO 1满了中断
  *            @arg CAN_IT_FOV1: FIFO 1超限中断
  *            @arg CAN_IT_WKU: 唤醒中断
  *            @arg CAN_IT_SLK: 睡眠确认中断
  *            @arg CAN_IT_EWG: 错误警告中断
  *            @arg CAN_IT_EPV: 错误被动中断
  *            @arg CAN_IT_BOF: 总线关闭中断
  *            @arg CAN_IT_LEC: 最后的错误代码中断
  *            @arg CAN_IT_ERR: 错误中断
  * 
  * 注意:   CAN3 外设设备仅适用于 STM32F413_423xx 设备
  * 返回值: 无
  */
void CAN_ClearITPendingBit(CAN_TypeDef* CANx, uint32_t CAN_IT) {
    /* 检查参数 */
    assert_param(IS_CAN_ALL_PERIPH(CANx));
    assert_param(IS_CAN_CLEAR_IT(CAN_IT));

    switch (CAN_IT) {
        case CAN_IT_TME:
            /* 清除 CAN_TSR_RQCPx (rc_w1)*/
            CANx->TSR = CAN_TSR_RQCP0 | CAN_TSR_RQCP1 | CAN_TSR_RQCP2;
            break;

        case CAN_IT_FF0:
            /* 清除 CAN_RF0R_FULL0 (rc_w1)*/
            CANx->RF0R = CAN_RF0R_FULL0;
            break;

        case CAN_IT_FOV0:
            /* 清除 CAN_RF0R_FOVR0 (rc_w1)*/
            CANx->RF0R = CAN_RF0R_FOVR0;
            break;

        case CAN_IT_FF1:
            /* 清除 CAN_RF1R_FULL1 (rc_w1)*/
            CANx->RF1R = CAN_RF1R_FULL1;
            break;

        case CAN_IT_FOV1:
            /* 清除 CAN_RF1R_FOVR1 (rc_w1)*/
            CANx->RF1R = CAN_RF1R_FOVR1;
            break;

        case CAN_IT_WKU:
            /* 清除 CAN_MSR_WKUI (rc_w1)*/
            CANx->MSR = CAN_MSR_WKUI;
            break;

        case CAN_IT_SLK:
            /* 清除 CAN_MSR_SLAKI (rc_w1)*/
            CANx->MSR = CAN_MSR_SLAKI;
            break;

        case CAN_IT_EWG:
            /* 清除 CAN_MSR_ERRI (rc_w1) */
            CANx->MSR = CAN_MSR_ERRI;
            /* 注意相应的标志被硬件清除，这取决于CAN 总线状态。*/
            break;

        case CAN_IT_EPV:
            /* 清除 CAN_MSR_ERRI (rc_w1) */
            CANx->MSR = CAN_MSR_ERRI;
            /* 注意相应的标志被硬件清除，这取决于CAN 总线状态。*/
            break;

        case CAN_IT_BOF:
            /* 清除 CAN_MSR_ERRI (rc_w1) */
            CANx->MSR = CAN_MSR_ERRI;
            /* 注意相应的标志被硬件清除，这取决于CAN 总线状态。*/
            break;

        case CAN_IT_LEC:
            /* 清除 LEC 位 */
            CANx->ESR = RESET;
            /* 清除 CAN_MSR_ERRI (rc_w1) */
            CANx->MSR = CAN_MSR_ERRI;
            break;

        case CAN_IT_ERR:
            /*清除 LEC 位 */
            CANx->ESR = RESET;
            /* 清除 CAN_MSR_ERRI (rc_w1) */
            CANx->MSR = CAN_MSR_ERRI;
            /* 注:BOFF、EPVF和EWGF 标志由硬件根据 CAN 总线状态进行清除。*/
            break;

        default:
            break;
    }
}


/**
  * 简介:  检查 CAN 中断是否已经发生。
  * 
  * 参数:  CAN_Reg: 指定要检查的 CAN 中断寄存器。
  * 
  * 参数:  It_Bit: 指定要检查的中断源位。
  * 
  * 返回值: CAN 中断的新状态(SET 或 RESET)。
  */
static ITStatus CheckITStatus(uint32_t CAN_Reg, uint32_t It_Bit) {
    ITStatus pendingbitstatus = RESET;

    if ((CAN_Reg & It_Bit) != (uint32_t)RESET) {
        /* CAN_IT被设置 */
        pendingbitstatus = SET;
    } else {
        /* CAN_IT被重置 */
        pendingbitstatus = RESET;
    }

    return pendingbitstatus;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
