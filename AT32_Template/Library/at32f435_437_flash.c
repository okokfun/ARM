/**
  **************************************************************************
  * @file     at32f435_437_flash.c
  * @brief    contains all the functions for the flash firmware library
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

/** @defgroup FLASH
  * @brief FLASH driver modules
  */

#ifdef FLASH_MODULE_EnableD

/** @defgroup FLASH_private_functions
  */

/**
  * @brief  check whether the specified flash flag is set or not.
  * @param  FLASH_flag: 指定flash flag to check.
  *         该参数可以是 one of flash flag status:
  *         - FLASH_OBF_FLAG
  *         - FLASH_ODF_FLAG
  *         - FLASH_PRGMERR_FLAG
  *         - FLASH_EPPERR_FLAG
  *         - FLASH_Bank1_OBF_FLAG
  *         - FLASH_Bank1_ODF_FLAG
  *         - FLASH_Bank1_PRGMERR_FLAG
  *         - FLASH_Bank1_EPPERR_FLAG
  *         - FLASH_Bank2_OBF_FLAG
  *         - FLASH_Bank2_ODF_FLAG
  *         - FLASH_Bank2_PRGMERR_FLAG
  *         - FLASH_Bank2_EPPERR_FLAG
  *         - FLASH_USDERR_FLAG
  * @retval the new state of FLASH_flag (SET or RESET).
  */
flag_status FLASH_Flag_Get(uint32_t FLASH_flag) {
    flag_status status = RESET;
    uint32_t flag_position;
    flag_position = FLASH_flag & 0x70000000;
    FLASH_flag &= 0x8FFFFFFF;

    switch(flag_position) {
        case 0x00000000:
            if(FLASH->sts & FLASH_flag)
                status = SET;

            break;

        case 0x10000000:
            if(FLASH->sts2 & FLASH_flag)
                status = SET;

            break;

        case 0x40000000:
            if(FLASH->usd & FLASH_flag)
                status = SET;

            break;

        default:
            break;
    }

    /* return the new state of FLASH_flag (SET or RESET) */
    return status;
}

/**
  * @brief  clear the flash flag.
  * @param  FLASH_flag: 指定flash flags to clear.
  *         该参数可以是以下值的任意组合:
  *         - FLASH_ODF_FLAG
  *         - FLASH_PRGMERR_FLAG
  *         - FLASH_EPPERR_FLAG
  *         - FLASH_Bank1_ODF_FLAG
  *         - FLASH_Bank1_PRGMERR_FLAG
  *         - FLASH_Bank1_EPPERR_FLAG
  *         - FLASH_Bank2_ODF_FLAG
  *         - FLASH_Bank2_PRGMERR_FLAG
  *         - FLASH_Bank2_EPPERR_FLAG
  * @retval 无
  */
void FLASH_Flag_Clear(uint32_t FLASH_flag) {
    uint32_t flag_position;
    flag_position = FLASH_flag & 0x70000000;
    FLASH_flag &= 0x8FFFFFFF;

    switch(flag_position) {
        case 0x00000000:
            FLASH->sts = FLASH_flag;
            break;

        case 0x10000000:
            FLASH->sts2 = FLASH_flag;
            break;

        default:
            break;
    }
}

/**
  * @brief  return the flash operation status.
  * @param  无
  * @retval status: the returned value can be: FLASH_OPERATE_BUSY,
  *         FLASH_PROGRAM_ERROR, FLASH_EPP_ERROR or FLASH_OPERATE_DONE.
  */
FLASH_Status_Type FLASH_Operation_Status_Get(void) {
    FLASH_Status_Type FLASH_status = FLASH_OPERATE_DONE;

    if(FLASH->sts_bit.obf != RESET) {
        FLASH_status = FLASH_OPERATE_BUSY;
    } else if(FLASH->sts_bit.prgmerr != RESET) {
        FLASH_status = FLASH_PROGRAM_ERROR;
    } else if(FLASH->sts_bit.epperr != RESET) {
        FLASH_status = FLASH_EPP_ERROR;
    } else {
        FLASH_status = FLASH_OPERATE_DONE;
    }

    /* return the flash status */
    return FLASH_status;
}

/**
  * @brief  return the flash bank1 operation status.
  * @param  无
  * @retval status: the returned value can be: FLASH_OPERATE_BUSY,
  *         FLASH_PROGRAM_ERROR, FLASH_EPP_ERROR or FLASH_OPERATE_DONE.
  */
FLASH_Status_Type FLASH_Bank1_Operation_Status_Get(void) {
    FLASH_Status_Type FLASH_status = FLASH_OPERATE_DONE;

    if(FLASH->sts_bit.obf != RESET) {
        FLASH_status = FLASH_OPERATE_BUSY;
    } else if(FLASH->sts_bit.prgmerr != RESET) {
        FLASH_status = FLASH_PROGRAM_ERROR;
    } else if(FLASH->sts_bit.epperr != RESET) {
        FLASH_status = FLASH_EPP_ERROR;
    } else {
        FLASH_status = FLASH_OPERATE_DONE;
    }

    /* return the flash status */
    return FLASH_status;
}

/**
  * @brief  return the flash bank2 operation status.
  * @param  无
  * @retval status: the returned value can be: FLASH_OPERATE_BUSY,
  *         FLASH_PROGRAM_ERROR, FLASH_EPP_ERROR or FLASH_OPERATE_DONE.
  */
FLASH_Status_Type FLASH_Bank2_Operation_Status_Get(void) {
    FLASH_Status_Type FLASH_status = FLASH_OPERATE_DONE;

    if(FLASH->sts2_bit.obf != RESET) {
        FLASH_status = FLASH_OPERATE_BUSY;
    } else if(FLASH->sts2_bit.prgmerr != RESET) {
        FLASH_status = FLASH_PROGRAM_ERROR;
    } else if(FLASH->sts2_bit.epperr != RESET) {
        FLASH_status = FLASH_EPP_ERROR;
    } else {
        FLASH_status = FLASH_OPERATE_DONE;
    }

    /* return the flash status */
    return FLASH_status;
}

/**
  * @brief  wait for flash operation complete or timeout.
  * @param  time_Out: flash operation timeout
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Operation_Wait_For(uint32_t time_Out) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;
    /* check for the flash status */
    status = FLASH_Operation_Status_Get();

    while((status == FLASH_OPERATE_BUSY) && (time_Out != 0x00)) {
        status = FLASH_Operation_Status_Get();
        time_Out--;
    }

    if(time_Out == 0x00) {
        status = FLASH_OPERATE_TIMEOUT;
    }

    /* return the status */
    return status;
}

/**
  * @brief  wait for flash bank1 operation complete or timeout.
  * @param  time_Out: flash operation timeout
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Bank1_Operation_Wait_For(uint32_t time_Out) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;
    /* check for the flash status */
    status = FLASH_Bank1_Operation_Status_Get();

    while((status == FLASH_OPERATE_BUSY) && (time_Out != 0x00)) {
        status = FLASH_Bank1_Operation_Status_Get();
        time_Out--;
    }

    if(time_Out == 0x00) {
        status = FLASH_OPERATE_TIMEOUT;
    }

    /* return the operation status */
    return status;
}

/**
  * @brief  wait for flash bank2 operation complete or timeout.
  * @param  time_Out: flash operation timeout
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Bank2_Operation_Wait_For(uint32_t time_Out) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;
    /* check for the flash status */
    status = FLASH_Bank2_Operation_Status_Get();

    while((status == FLASH_OPERATE_BUSY) && (time_Out != 0x00)) {
        status = FLASH_Bank2_Operation_Status_Get();
        time_Out--;
    }

    if(time_Out == 0x00) {
        status = FLASH_OPERATE_TIMEOUT;
    }

    /* return the operation status */
    return status;
}

/**
  * @brief  unlock the flash controller.
  * @param  无
  * @retval 无
  */
void FLASH_Unlock(void) {
    FLASH->unlock = FLASH_Unlock_KEY1;
    FLASH->unlock = FLASH_Unlock_KEY2;
    FLASH->unlock2 = FLASH_Unlock_KEY1;
    FLASH->unlock2 = FLASH_Unlock_KEY2;
}

/**
  * @brief  unlock the flash bank1 controller.
  * @param  无
  * @retval 无
  */
void FLASH_Bank1_unlock(void) {
    FLASH->unlock = FLASH_Unlock_KEY1;
    FLASH->unlock = FLASH_Unlock_KEY2;
}

/**
  * @brief  unlock the flash bank2 controller.
  * @param  无
  * @retval 无
  */
void FLASH_Bank2_unlock(void) {
    FLASH->unlock2 = FLASH_Unlock_KEY1;
    FLASH->unlock2 = FLASH_Unlock_KEY2;
}

/**
  * @brief  lock the flash controller.
  * @param  无
  * @retval 无
  */
void FLASH_Lock(void) {
    FLASH->ctrl_bit.oplk = TRUE;
    FLASH->ctrl2_bit.oplk = TRUE;
}

/**
  * @brief  lock the flash bank1 controller.
  * @param  无
  * @retval 无
  */
void FLASH_Bank1_lock(void) {
    FLASH->ctrl_bit.oplk = TRUE;
}

/**
  * @brief  lock the flash bank2 controller.
  * @param  无
  * @retval 无
  */
void FLASH_Bank2_lock(void) {
    FLASH->ctrl2_bit.oplk = TRUE;
}

/**
  * @brief  erase a specified flash sector.
  * @param  sector_Address: the sector address to be erased.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Sector_Erase(uint32_t sector_Address) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    if((sector_Address >= FLASH_Bank1_Start_Addr) && (sector_Address <= FLASH_Bank1_End_Addr)) {
        FLASH->ctrl_bit.secers = TRUE;
        FLASH->addr = sector_Address;
        FLASH->ctrl_bit.erstr = TRUE;

        /* wait for operation to be completed */
        status = FLASH_Bank1_Operation_Wait_For(ERASE_TIMEOUT);

        /* disable the secers bit */
        FLASH->ctrl_bit.secers = FALSE;
    } else if((sector_Address >= FLASH_Bank2_Start_Addr) && (sector_Address <= FLASH_Bank2_End_Addr)) {
        FLASH->ctrl2_bit.secers = TRUE;
        FLASH->addr2 = sector_Address;
        FLASH->ctrl2_bit.erstr = TRUE;

        /* wait for operation to be completed */
        status = FLASH_Bank2_Operation_Wait_For(ERASE_TIMEOUT);

        /* disable the secers bit */
        FLASH->ctrl2_bit.secers = FALSE;
    }

    /* return the erase status */
    return status;
}

/**
  * @brief  erase a specified flash block.
  * @param  block_Address: the block address to be erased.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Block_Erase(uint32_t block_Address) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    if((block_Address >= FLASH_Bank1_Start_Addr) && (block_Address <= FLASH_Bank1_End_Addr)) {
        FLASH->ctrl_bit.blkers = TRUE;
        FLASH->addr = block_Address;
        FLASH->ctrl_bit.erstr = TRUE;

        /* wait for operation to be completed */
        status = FLASH_Bank1_Operation_Wait_For(ERASE_TIMEOUT);

        /* disable the blkers bit */
        FLASH->ctrl_bit.blkers = FALSE;
    } else if((block_Address >= FLASH_Bank2_Start_Addr) && (block_Address <= FLASH_Bank2_End_Addr)) {
        FLASH->ctrl2_bit.blkers = TRUE;
        FLASH->addr2 = block_Address;
        FLASH->ctrl2_bit.erstr = TRUE;

        /* wait for operation to be completed */
        status = FLASH_Bank2_Operation_Wait_For(ERASE_TIMEOUT);

        /* disable the blkers bit */
        FLASH->ctrl2_bit.blkers = FALSE;
    }

    /* return the erase status */
    return status;
}

/**
  * @brief  erase flash all internal sectors.
  * @param  无
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Internal_All_Erase(void) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    FLASH->ctrl_bit.bankers = TRUE;
    FLASH->ctrl_bit.erstr = TRUE;

    /* wait for operation to be completed */
    status = FLASH_Bank1_Operation_Wait_For(ERASE_TIMEOUT);

    /* disable the bankers bit */
    FLASH->ctrl_bit.bankers = FALSE;

    if(status == FLASH_OPERATE_DONE) {
        /* if the previous operation is completed, continue to erase bank2 */
        FLASH->ctrl2_bit.bankers = TRUE;
        FLASH->ctrl2_bit.erstr = TRUE;

        /* wait for operation to be completed */
        status = FLASH_Bank2_Operation_Wait_For(ERASE_TIMEOUT);

        /* disable the bankers bit */
        FLASH->ctrl2_bit.bankers = FALSE;
    }

    /* return the erase status */
    return status;
}

/**
  * @brief  erase flash bank1 sectors.
  * @param  无
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Bank1_Erase(void) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    FLASH->ctrl_bit.bankers = TRUE;
    FLASH->ctrl_bit.erstr = TRUE;

    /* wait for operation to be completed */
    status = FLASH_Bank1_Operation_Wait_For(ERASE_TIMEOUT);

    /* disable the bankers bit */
    FLASH->ctrl_bit.bankers = FALSE;

    /* return the erase status */
    return status;
}

/**
  * @brief  erase flash bank2 sectors.
  * @param  无
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Bank2_Erase(void) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    FLASH->ctrl2_bit.bankers = TRUE;
    FLASH->ctrl2_bit.erstr = TRUE;

    /* wait for operation to be completed */
    status = FLASH_Bank2_Operation_Wait_For(ERASE_TIMEOUT);

    /* disable the bankers bit */
    FLASH->ctrl2_bit.bankers = FALSE;

    /* return the erase status */
    return status;
}

/**
  * @brief  erase the flash user system data.
  * @note   this functions erase all user system data except the fap byte.
  *         the eopb0 byte value change to 0xFF, sram size maybe change too.
  * @param  无
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_User_System_Data_Erase(void) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;
    uint16_t fap_val = FAP_RELIEVE_KEY;

    /* get the flash access protection status */
    if(FLASH_Fap_Status_Get() != RESET) {
        fap_val = 0x0000;
    }

    /* unlock the user system data */
    FLASH->usd_unlock = FLASH_Unlock_KEY1;
    FLASH->usd_unlock = FLASH_Unlock_KEY2;

    while(FLASH->ctrl_bit.usdulks == RESET);

    /* erase the user system data */
    FLASH->ctrl_bit.usders = TRUE;
    FLASH->ctrl_bit.erstr = TRUE;

    /* wait for operation to be completed */
    status = FLASH_Operation_Wait_For(ERASE_TIMEOUT);

    /* disable the usders bit */
    FLASH->ctrl_bit.usders = FALSE;

    if((status == FLASH_OPERATE_DONE) && (fap_val == FAP_RELIEVE_KEY)) {
        /* enable the user system data programming operation */
        FLASH->ctrl_bit.usdprgm = TRUE;

        /* restore the last flash access protection value */
        USD->fap = (uint16_t)fap_val;

        /* wait for operation to be completed */
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);

        /*disable the usdprgm bit */
        FLASH->ctrl_bit.usdprgm = FALSE;
    }

    /* return the status */
    return status;
}

/**
  * @brief  config the extend sram byte eopb0 in user system data.
  * @note   the 256kb and below capacity mcu only support FLASH_Eopb0_SRAM_384K,
  *         FLASH_Eopb0_SRAM_448K or FLASH_Eopb0_SRAM_512K.
  * @param  data: the eopb0 value.
  *         该参数可以是以下值之一:
  *         - FLASH_Eopb0_SRAM_512K
  *         - FLASH_Eopb0_SRAM_448K
  *         - FLASH_Eopb0_SRAM_384K
  *         - FLASH_Eopb0_SRAM_320K
  *         - FLASH_Eopb0_SRAM_256K
  *         - FLASH_Eopb0_SRAM_192K
  *         - FLASH_Eopb0_SRAM_128K
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Eopb0_Config(FLASH_Usd_Eopb0_Type data) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    /* unlock the user system data */
    FLASH->usd_unlock = FLASH_Unlock_KEY1;
    FLASH->usd_unlock = FLASH_Unlock_KEY2;

    while(FLASH->ctrl_bit.usdulks == RESET);

    /* enable the user system data programming operation */
    FLASH->ctrl_bit.usdprgm = TRUE;

    /* restore the default eopb0 value */
    USD->eopb0 = (uint16_t)data;

    /* wait for operation to be completed */
    status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);

    /*disable the usdprgm bit */
    FLASH->ctrl_bit.usdprgm = FALSE;

    /* return the status */
    return status;
}

/**
  * @brief  program a word at a specified address.
  * @param  address: 指定address to be programmed, word alignment is recommended.
  * @param  data: 指定data to be programmed.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Word_program(uint32_t address, uint32_t data) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    if((address >= FLASH_Bank1_Start_Addr) && (address <= FLASH_Bank1_End_Addr)) {
        FLASH->ctrl_bit.fprgm = TRUE;
        *(__IO uint32_t*)address = data;
        /* wait for operation to be completed */
        status = FLASH_Bank1_Operation_Wait_For(PROGRAMMING_TIMEOUT);

        /* disable the fprgm bit */
        FLASH->ctrl_bit.fprgm = FALSE;
    } else if((address >= FLASH_Bank2_Start_Addr) && (address <= FLASH_Bank2_End_Addr)) {
        FLASH->ctrl2_bit.fprgm = TRUE;
        *(__IO uint32_t*)address = data;
        /* wait for operation to be completed */
        status = FLASH_Bank2_Operation_Wait_For(PROGRAMMING_TIMEOUT);

        /* disable the fprgm bit */
        FLASH->ctrl2_bit.fprgm = FALSE;
    }

    /* return the program status */
    return status;
}

/**
  * @brief  program a halfword at a specified address.
  * @param  address: 指定address to be programmed, halfword alignment is recommended.
  * @param  data: 指定data to be programmed.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_halfword_program(uint32_t address, uint16_t data) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    if((address >= FLASH_Bank1_Start_Addr) && (address <= FLASH_Bank1_End_Addr)) {
        FLASH->ctrl_bit.fprgm = TRUE;
        *(__IO uint16_t*)address = data;
        /* wait for operation to be completed */
        status = FLASH_Bank1_Operation_Wait_For(PROGRAMMING_TIMEOUT);

        /* disable the fprgm bit */
        FLASH->ctrl_bit.fprgm = FALSE;
    } else if((address >= FLASH_Bank2_Start_Addr) && (address <= FLASH_Bank2_End_Addr)) {
        FLASH->ctrl2_bit.fprgm = TRUE;
        *(__IO uint16_t*)address = data;
        /* wait for operation to be completed */
        status = FLASH_Bank2_Operation_Wait_For(PROGRAMMING_TIMEOUT);

        /* disable the fprgm bit */
        FLASH->ctrl2_bit.fprgm = FALSE;
    }

    /* return the program status */
    return status;
}

/**
  * @brief  program a byte at a specified address.
  * @note   this function cannot be used to program spim.
  * @param  address: 指定address to be programmed.
  * @param  data: 指定data to be programmed.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Byte_program(uint32_t address, uint8_t data) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    if((address >= FLASH_Bank1_Start_Addr) && (address <= FLASH_Bank1_End_Addr)) {
        FLASH->ctrl_bit.fprgm = TRUE;
        *(__IO uint8_t*)address = data;
        /* wait for operation to be completed */
        status = FLASH_Bank1_Operation_Wait_For(PROGRAMMING_TIMEOUT);

        /* disable the fprgm bit */
        FLASH->ctrl_bit.fprgm = FALSE;
    } else if((address >= FLASH_Bank2_Start_Addr) && (address <= FLASH_Bank2_End_Addr)) {
        FLASH->ctrl2_bit.fprgm = TRUE;
        *(__IO uint8_t*)address = data;
        /* wait for operation to be completed */
        status = FLASH_Bank2_Operation_Wait_For(PROGRAMMING_TIMEOUT);

        /* disable the fprgm bit */
        FLASH->ctrl2_bit.fprgm = FALSE;
    }

    /* return the program status */
    return status;
}

/**
  * @brief  program a halfword at a specified user system data address.
  * @param  address: 指定address to be programmed.
  * @param  data: 指定data to be programmed.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_User_System_Data_program(uint32_t address, uint8_t data) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    if(address == USD_BASE) {
        if(data != 0xA5)
            return FLASH_OPERATE_DONE;
    }

    /* unlock the user system data */
    FLASH->usd_unlock = FLASH_Unlock_KEY1;
    FLASH->usd_unlock = FLASH_Unlock_KEY2;

    while(FLASH->ctrl_bit.usdulks == RESET);

    /* enable the user system data programming operation */
    FLASH->ctrl_bit.usdprgm = TRUE;
    *(__IO uint16_t*)address = data;

    /* wait for operation to be completed */
    status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);

    /* disable the usdprgm bit */
    FLASH->ctrl_bit.usdprgm = FALSE;

    /* return the user system data program status */
    return status;
}

/**
  * @brief  config erase/program protection for the desired sectors.
  * @param  sector_bits:
  *         the pointer of the address of the sectors to be erase/program protected.
  *         general bit 0~31 every bit is used to protect the 4KB bytes, bit 62~32
  *         every bit is used to protect the 128KB bytes
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_EPP_Set(uint32_t *sector_bits) {
    uint16_t epp_data[4] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    FLASH_Status_Type status = FLASH_OPERATE_DONE;
    sector_bits[0] = (uint32_t)(~sector_bits[0]);
    epp_data[0] = (uint16_t)((sector_bits[0] >> 0) & 0xFF);
    epp_data[1] = (uint16_t)((sector_bits[0] >> 8) & 0xFF);
    epp_data[2] = (uint16_t)((sector_bits[0] >> 16) & 0xFF);
    epp_data[3] = (uint16_t)((sector_bits[0] >> 24) & 0xFF);

    /* unlock the user system data */
    FLASH->usd_unlock = FLASH_Unlock_KEY1;
    FLASH->usd_unlock = FLASH_Unlock_KEY2;

    while(FLASH->ctrl_bit.usdulks == RESET);

    FLASH->ctrl_bit.usdprgm = TRUE;
    USD->epp0 = epp_data[0];
    /* wait for operation to be completed */
    status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);

    if(status == FLASH_OPERATE_DONE) {
        USD->epp1 = epp_data[1];
        /* wait for operation to be completed */
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);
    }

    if(status == FLASH_OPERATE_DONE) {
        USD->epp2 = epp_data[2];
        /* wait for operation to be completed */
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);
    }

    if(status == FLASH_OPERATE_DONE) {
        USD->epp3 = epp_data[3];
        /* wait for operation to be completed */
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);
    }

    sector_bits[1] = (uint32_t)(~sector_bits[1]);
    epp_data[0] = (uint16_t)((sector_bits[1] >> 0) & 0xFF);
    epp_data[1] = (uint16_t)((sector_bits[1] >> 8) & 0xFF);
    epp_data[2] = (uint16_t)((sector_bits[1] >> 16) & 0xFF);
    epp_data[3] = (uint16_t)((sector_bits[1] >> 24) & 0xFF);

    if(status == FLASH_OPERATE_DONE) {
        USD->epp4 = epp_data[0];
        /* wait for operation to be completed */
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);
    }

    if(status == FLASH_OPERATE_DONE) {
        USD->epp5 = epp_data[1];
        /* wait for operation to be completed */
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);
    }

    if(status == FLASH_OPERATE_DONE) {
        USD->epp6 = epp_data[2];
        /* wait for operation to be completed */
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);
    }

    if(status == FLASH_OPERATE_DONE) {
        USD->epp7 = epp_data[3];
        /* wait for operation to be completed */
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);
    }

    /* disable the usdprgm bit */
    FLASH->ctrl_bit.usdprgm = FALSE;

    /* return the erase/program protection operation status */
    return status;
}

/**
  * @brief  return the flash erase/program protection status.
  * @param  sector_bits: pointer to get the epps register.
  * @retval 无
  */
void FLASH_EPP_Status_Get(uint32_t *sector_bits) {
    /* return the flash erase/program protection register value */
    sector_bits[0] = (uint32_t)(FLASH->epps0);
    sector_bits[1] = (uint32_t)(FLASH->epps1);
}

/**
  * @brief  enable or disable the flash access protection.
  * @note   if the user has already programmed the other user system data before calling
  *         this function, must re-program them since this function erase all user system data.
  * @param  new_state: new state of the flash access protection.
  *         该参数可以是: TRUE or FALSE.
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_Fap_Enable(confirm_state new_state) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    /* unlock the user system data */
    FLASH->usd_unlock = FLASH_Unlock_KEY1;
    FLASH->usd_unlock = FLASH_Unlock_KEY2;

    while(FLASH->ctrl_bit.usdulks == RESET);

    FLASH->ctrl_bit.usders = TRUE;
    FLASH->ctrl_bit.erstr = TRUE;
    /* wait for operation to be completed */
    status = FLASH_Operation_Wait_For(ERASE_TIMEOUT);

    /* disable the usders bit */
    FLASH->ctrl_bit.usders = FALSE;

    if(status == FLASH_OPERATE_DONE) {
        /* enable the user system data programming operation */
        FLASH->ctrl_bit.usdprgm = TRUE;

        /* restore the default eopb0 value */
        USD->eopb0 = (uint16_t)0x0002;

        /* Wait for operation to be completed */
        status = FLASH_Operation_Wait_For(ERASE_TIMEOUT);

        if(new_state == FALSE) {
            USD->fap = FAP_RELIEVE_KEY;
            /* Wait for operation to be completed */
            status = FLASH_Operation_Wait_For(ERASE_TIMEOUT);
        }

        /* disable the usdprgm bit */
        FLASH->ctrl_bit.usdprgm = FALSE;
    }

    /* return the flash access protection operation status */
    return status;
}

/**
  * @brief  check the flash access protection status.
  * @param  无
  * @retval flash access protection status(SET or RESET)
  */
flag_status FLASH_Fap_Status_Get(void) {
    return (flag_status)FLASH->usd_bit.fap;
}

/**
  * @brief  program the flash system setting byte in usd: WDT_ato_en / depslp_rst / stdby_rst / btopt.
  * @param  usd_ssb: the system setting byte
  * @note   this parameter usd_ssb must contain a combination of all the following 6 types of data
  *         type 1: WDT_ato_en, select the wdt auto start
  *         this data can be one of the following values:
  *         - USD_WDT_ATO_Disable: disable wdt auto start
  *         - USD_WDT_ATO_Enable: enable wdt auto start
  *         type 2: depslp_rst, reset event when entering deepsleep mode.
  *         this data can be one of the following values:
  *         - USD_DEPSLP_NO_RST: no reset generated when entering in deepsleep
  *         - USD_DEPSLP_RST: reset generated when entering in deepsleep
  *         type 3: stdby_rst, reset event when entering standby mode.
  *         this data can be one of the following values:
  *         - USD_STDBY_NO_RST: no reset generated when entering in standby
  *         - USD_STDBY_RST: reset generated when entering in standby
  *         type 4: btopt, at startup,if boot pins are set in boot from user flash position,selected the device boot from bank1/bank2.
  *         this data can be one of the following values:
  *         - FLASH_BOOT_FROM_BANK1:boot from bank1
  *         - FLASH_BOOT_FROM_BANK2:boot from bank 2 or bank 1
  *         type 5: WDT_depslp, wdt stop/continue count when entering in deepsleep.
  *         this data can be one of the following values:
  *         - USD_WDT_DEPSLP_CONTINUE: wdt continue count
  *         - USD_WDT_DEPSLP_STOP: wdt stop count
  *         type 6: WDT_stdby, wdt stop/continue count when entering in standby.
  *         this data can be one of the following values:
  *         - USD_WDT_STDBY_CONTINUE: wdt continue count
  *         - USD_WDT_STDBY_STOP: wdt stop count
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_SSB_Set(uint8_t usd_ssb) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    /* unlock the user system data */
    FLASH->usd_unlock = FLASH_Unlock_KEY1;
    FLASH->usd_unlock = FLASH_Unlock_KEY2;

    while(FLASH->ctrl_bit.usdulks == RESET);

    /* enable the user system data programming operation */
    FLASH->ctrl_bit.usdprgm = TRUE;

    USD->ssb = usd_ssb;
    /* wait for operation to be completed */
    status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);

    /* disable the usdprgm bit */
    FLASH->ctrl_bit.usdprgm = FALSE;

    /* return the user system data program status */
    return status;
}

/**
  * @brief  return the flash system setting byte status.
  * @param  无
  * @retval values from FLASH_usd register: WDT_ato_en(bit0), depslp_rst(bit1),
  *         stdby_rst(bit2) and btopt(bit3).
  */
uint8_t FLASH_SSB_Status_Get(void) {
    /* return the system setting byte status */
    return (uint8_t)(FLASH->usd >> 2);
}

/**
  * @brief  enable or disable the specified flash interrupts.
  * @param  FLASH_int: 指定flash interrupt sources to be enabled or disabled.
  *         该参数可以是以下值的任意组合:
  *         - FLASH_ERR_INT
  *         - FLASH_ODF_INT
  *         - FLASH_Bank1_ERR_INT
  *         - FLASH_Bank1_ODF_INT
  *         - FLASH_Bank2_ERR_INT
  *         - FLASH_Bank2_ODF_INT
  * @param  new_state: new state of the specified flash interrupts.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void FLASH_Interrupt_Enable(uint32_t FLASH_int, confirm_state new_state) {
    if(FLASH_int & FLASH_Bank1_ERR_INT)
        FLASH->ctrl_bit.errie = new_state;

    if(FLASH_int & FLASH_Bank1_ODF_INT)
        FLASH->ctrl_bit.odfie = new_state;

    if(FLASH_int & FLASH_Bank2_ERR_INT)
        FLASH->ctrl2_bit.errie = new_state;

    if(FLASH_int & FLASH_Bank2_ODF_INT)
        FLASH->ctrl2_bit.odfie = new_state;
}

/**
  * @brief  enable security library function.
  * @param  pwd: slib password
  *         start_sector: security library start sector
  *         inst_Start_sector: security library i-bus area start sector
  *         end_sector: security library end sector
  * @retval status: the returned value can be: FLASH_PROGRAM_ERROR,
  *         FLASH_EPP_ERROR, FLASH_OPERATE_DONE or FLASH_OPERATE_TIMEOUT.
  */
FLASH_Status_Type FLASH_sLib_Enable(uint32_t pwd, uint16_t start_sector, uint16_t inst_Start_sector, uint16_t end_sector) {
    uint32_t slib_range;
    FLASH_Status_Type status = FLASH_OPERATE_DONE;

    /*check range param limits*/
    if((start_sector >= inst_Start_sector) || ((inst_Start_sector > end_sector) && \
            (inst_Start_sector != 0xFFFF)) || (start_sector > end_sector))
        return FLASH_PROGRAM_ERROR;

    /* unlock slib cfg register */
    FLASH->slib_unlock = SLIB_UNLOCK_KEY;

    while(FLASH->slib_misc_sts_bit.slib_ulkf == RESET);

    /* configure slib, set pwd and range */
    FLASH->slib_Set_pwd = pwd;
    status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);

    if(status == FLASH_OPERATE_DONE) {
        slib_range = ((uint32_t)(end_sector << 16) & FLASH_sLib_End_SECTOR) | (start_sector & FLASH_sLib_Start_SECTOR);
        FLASH->slib_Set_range0 = slib_range;
        status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);

        if(status == FLASH_OPERATE_DONE) {
            slib_range = (inst_Start_sector & FLASH_sLib_INST_Start_SECTOR) | 0x80000000;
            FLASH->slib_Set_range1 = slib_range;
            status = FLASH_Operation_Wait_For(PROGRAMMING_TIMEOUT);
        }
    }

    return status;
}

/**
  * @brief  disable slib when slib enabled.
  * @param  pwd: slib password
  * @retval success or error
  */
error_status FLASH_sLib_Disable(uint32_t pwd) {
    FLASH_Status_Type status = FLASH_OPERATE_DONE;
    /* write password to disable slib */
    FLASH->slib_pwd_clr = pwd;

    status = FLASH_Operation_Wait_For(ERASE_TIMEOUT);

    if(status == FLASH_OPERATE_DONE) {
        if(FLASH->slib_misc_sts_bit.slib_pwd_ok)
            return SUCCESS;
        else
            return ERROR;
    }

    return ERROR;
}

/**
 * @brief  get remaining count of slib(range: 256~0).
 * @param  无
 * @retval uint32_t
 */
uint32_t FLASH_sLib_Remaining_Count_Get(void) {
    return (uint32_t)FLASH->slib_misc_sts_bit.slib_rcnt;
}

/**
  * @brief  get the slib state.
  * @param  无
  * @retval SET or RESET
  */
flag_status FLASH_sLib_State_Get(void) {
    if(FLASH->slib_sts0_bit.slib_enf)
        return SET;
    else
        return RESET;
}

/**
 * @brief  get the start sector of slib.
 * @param  无
 * @retval uint16_t
 */
uint16_t FLASH_sLib_Start_Sector_Get(void) {
    return (uint16_t)FLASH->slib_sts1_bit.slib_ss;
}

/**
 * @brief  get the instruction start sector of slib.
 * @param  无
 * @retval uint16_t
 */
uint16_t FLASH_sLib_Inststart_Sector_Get(void) {
    return (uint16_t)FLASH->slib_sts2_bit.slib_inst_ss;
}

/**
 * @brief  get the end sector of slib.
 * @param  无
 * @retval uint16_t
 */
uint16_t FLASH_sLib_End_Sector_Get(void) {
    return (uint16_t)FLASH->slib_sts1_bit.slib_es;
}

/**
  * @brief  flash crc calibration in main block.
  * @param  start_sector: crc calibration start sector number
  *         sector_cnt: crc calibration sector count
  * @retval uint32: crc calibration result
  */
uint32_t FLASH_CRC_Calibrate(uint32_t start_sector, uint32_t sector_cnt) {
    FLASH->CRC_Ctrl_bit.CRC_ss = start_sector;
    FLASH->CRC_Ctrl_bit.CRC_sn = sector_cnt;
    FLASH->CRC_Ctrl_bit.CRC_strt = TRUE;
    FLASH_Operation_Wait_For(OPERATION_TIMEOUT);
    return FLASH->CRC_chkr;
}

/**
  * @brief  flash non-zero wait area boost enable.
  * @param  new_state: new state of the flash non-zero wait area boost operation.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void FLASH_NZW_Boost_Enable(confirm_state new_state) {
    FLASH->psr_bit.nzw_bst = new_state;
}

/**
  * @brief  flash continue read enable.
  * @param  new_state: new state of the flash continue read enable operation.
  *         该参数可以是: TRUE or FALSE.
  * @retval 无
  */
void FLASH_Continue_Read_Enable(confirm_state new_state) {
    FLASH->contr_bit.fcontr_en = new_state;
}

#endif
