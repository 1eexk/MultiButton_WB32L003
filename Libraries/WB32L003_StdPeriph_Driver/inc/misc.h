/**
 * @file    misc.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the miscellaneous
 *          firmware library functions (add-on to CMSIS functions).
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MISC_H
#define __MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup MISC
  * @{
  */


/** @defgroup MISC_Exported_Constants
  * @{
  */


/** @defgroup SysTick_clock_source 
  * @{
  */

#define SysTick_CLKSource_HCLK_Div4   ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK        ((uint32_t)0x00000004)
#define IS_SYSTICK_CLK_SOURCE(SOURCE) (((SOURCE) == SysTick_CLKSource_HCLK) || \
                                       ((SOURCE) == SysTick_CLKSource_HCLK_Div4))
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup MISC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup MISC_Exported_Functions
  * @{
  */

void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
void SysTick_DelayNticks(uint32_t Ticks);
void SysTick_DelayUs(uint32_t Us);
void SysTick_DelayMs(uint32_t Ms);

#ifdef __cplusplus
}
#endif

#endif /* __MISC_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
