/**
 * @file    wb32l003_flash.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the FLASH firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_FLASH_H
#define __WB32L003_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup FLASH
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  FLASH Status  
  */
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_ERPC,
  FLASH_ERROR_ERPROT,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
} FLASH_Status;

/* Exported constants --------------------------------------------------------*/

/** @addtogroup FLASH_Private_Constants
  * @{
  */

#define FLASH_TIMEOUT_VALUE                    50000U
#define FLASH_REGUNLOCK_KEY1                   0x5A5AU
#define FLASH_REGUNLOCK_KEY2                   0xA5A5U

/**
  * @}
  */

/** @defgroup FLASH_Exported_Constants
  * @{
  */

/** @defgroup FLASH_Flag_definition
  * @{
  */
#define FLASH_FLAG_BUSY                        FLASH_CR_BUSY /*!< FLASH Busy flag */
/**
  * @}
  */


/** @defgroup FLASH_Interrupt_definition
  * @{
  */
#define FLASH_IT_ALARM_ERASE_PROTADDR         (FLASH_IFR_IF1 | FLASH_CR_IE_1) /*!< The address to be erased is protectd interrupt flag */
#define FLASH_IT_ALARM_ERASE_PCADDR           (FLASH_IFR_IF0 | FLASH_CR_IE_0) /*!< The address to be erased is PC interrupt flag */
/**
  * @}
  */


/** @defgroup FLASH_Page_Size
  * @{
  */ 
#define FLASH_PAGE_SIZE                        0x200U
#define FLASH_SIZE_32K                         0x8000U
#define FLASH_SIZE_64K                         0x10000U
#define FLASH_ALLPAGE_SELECTED                 0xFFFFFFFFU
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void FLASH_OP_Unlock(uint32_t PageAddr);
void FLASH_OP_Lock(uint32_t PageAddr);
void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
void FLASH_ClearITPendingBit(uint32_t FLASH_IT);
FlagStatus FLASH_GetITStatus(uint32_t Flag);
FlagStatus FLASH_GetFlagStatus(uint32_t Flag);
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);
FLASH_Status FLASH_ProgramByte(uint32_t Addr, uint8_t Data);
FLASH_Status FLASH_ProgramHalfWord(uint32_t Addr, uint16_t Data);
FLASH_Status FLASH_ProgramWord(uint32_t Addr, uint32_t Data);
FLASH_Status FLASH_EraseChip(void);
FLASH_Status FLASH_ErasePage(uint32_t PageAddr);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_FLASH_H */
