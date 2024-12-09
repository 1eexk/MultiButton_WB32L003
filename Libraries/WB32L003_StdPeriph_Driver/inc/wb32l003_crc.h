/**
 * @file    wb32l003_crc.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the CRC firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_CRC_H
#define __WB32L003_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup CRC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup TEMPLATE_Exported_Constants
  * @{
  */

#define CRC_DataAddress (CRC_BASE + 0x80) /*!< 0x80 ~ 0xFF is allowable */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void CRC_InitResult(void);
void CRC_DeInit(void);
uint32_t CRC_Accumulate(const uint8_t *ptr_data, uint32_t bufferLength);
uint32_t CRC_Calculate(const uint8_t *ptr_data, uint32_t bufferLength);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_CRC_H */
