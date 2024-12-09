/**
 * @file    wb32l003_wwdg.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the WWDG firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_WWDG_H
#define __WB32L003_WWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup WWDG
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup WWDG_Exported_Constants
  * @{
  */

/** @defgroup WWDG_Prescaler
  * @{
  */
#define WWDG_PRESCALER_MIN                  ((uint32_t)0x00000000U) /*!< WWDG clock Prescaler MIN */
#define WWDG_PRESCALER_MAX                  ((uint32_t)0x000FFFFFU) /*!< WWDG clock Prescaler MAX*/
/**
  * @}
  */


/** @defgroup WWDG_WindowAndReload
  * @{
  */
#define WWDG_WINDOW_MIN                     ((uint8_t)0x00000010U)
#define WWDG_WINDOW_MAX                     ((uint8_t)0x000000FFU)
#define WWDG_RELOAD_MIN                     ((uint8_t)0x00000020U)
#define WWDG_RELOAD_MAX                     ((uint8_t)0x000000FFU)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define IS_WWDG_PRESCALER_VALUE(VALUE) ((VALUE) <= WWDG_PRESCALER_MAX)

#define IS_WWDG_WINDOW_VALUE(VALUE) (((VALUE) >= WWDG_WINDOW_MIN) && \
                                     ((VALUE) <= WWDG_WINDOW_MAX))

#define IS_WWDG_RELOAD_VALUE(VALUE) (((VALUE) >= WWDG_RELOAD_MIN) && \
                                     ((VALUE) <= WWDG_RELOAD_MAX))

/* Exported functions --------------------------------------------------------*/

void WWDG_DeInit(void);
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(uint8_t WindowValue);
void WWDG_IT_Cmd(FunctionalState NewState);
void WWDG_SetCounter(uint8_t Counter);
void WWDG_Cmd(FunctionalState NewState);
FlagStatus WWDG_GetFlagStatus(void);
void WWDG_ClearFlag(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_WWDG_H */
