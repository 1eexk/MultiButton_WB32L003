/**
 * @file    wb32l003_iwdg.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the IWDG firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_IWDG_H
#define __WB32L003_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup IWDG_Exported_Constants
  * @{
  */

/**
  * @brief  IWDG Key Register value
  */
#define IWDG_UNLOCK_KEY                 ((uint32_t)0x55AA6699)   /*!< IWDG REG Write Access UNLOCK */
#define IWDG_LOCK_KEY                   ((uint32_t)0x55AA6698)   /*!< IWDG REG Write Access LOCK */
#define IWDG_START_ENABLE               ((uint32_t)0x00000055)   /*!< IWDG Enable */
#define IWDG_RELOAD_REFRESH             ((uint32_t)0x000000AA)   /*!< IWDG Peripheral Enable */

#define IWDG_MODE_RESET                 ((uint32_t)0x00000000)   /*!< IWDG reset mode */
#define IWDG_MODE_INT                   ((uint32_t)0x00000010)   /*!< IWDG interrupt mode */
#define IWDG_MODE_MASK                  ((uint32_t)0x00000010)   /*!< IWDG mode mask */

#define IWDG_IT_DISABLE                 ((uint32_t)0x00000000)   /*!< IWDG interrupt disable */
#define IWDG_IT_ENABLE                  ((uint32_t)0x00000100)   /*!< IWDG interrupt enable */
#define IWDG_IT_MASK                    ((uint32_t)0x00000100)   /*!< IWDG interrupt mask */

#define IWDG_RLR_MAX                    IWDG_RLOAD_IWDGRLOAD     /*!< Watchdog counter reload max value */


/** @defgroup IWDG_IT
  * @{
  */
#define IWDG_IT_GOVF                    IWDG_SR_IWDGOVF_Msk
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define IWDG_ENABLE_WRITE_ACCESS()  \
  do {                              \
    IWDG->UNLOCK = IWDG_UNLOCK_KEY; \
  } while (0)

#define IWDG_DISABLE_WRITE_ACCESS() \
  do {                              \
    IWDG->UNLOCK = IWDG_LOCK_KEY;   \
  } while (0)

/* Exported functions --------------------------------------------------------*/

void IWDG_Init(uint32_t IWDG_Config, FunctionalState NewState);
void IWDG_SetReload(uint32_t Reload);
void IWDG_ReloadCounter(void);
void IWDG_Start(void);
FlagStatus IWDG_GetITStatus(uint32_t IWDG_IT);
void IWDG_ClearITPendingBit(uint32_t IWDG_IT);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_IWDG_H */
