/**
 * @file    wb32l003_pwr.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the PWR firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_PWR_H
#define __WB32L003_PWR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants
  * @{
  */

/** @defgroup PWR_SLEEP_Mode_Entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI              ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE              ((uint8_t)0x02)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros
  * @{
  */
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPENTRY_WFI) || ((ENTRY) == PWR_SLEEPENTRY_WFE))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

void PWR_EnterSLEEPMode(uint8_t SLEEPEntry);
void PWR_EnterDEEPSLEEPMode(void);

void PWR_EnableSleepOnExit(void);
void PWR_DisableSleepOnExit(void);
void PWR_EnableSEVOnPend(void);
void PWR_DisableSEVOnPend(void);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_PWR_H */
