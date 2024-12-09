/**
 * @file    misc.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the miscellaneous firmware functions (add-on
 *          to CMSIS functions).
 */

/* Includes ------------------------------------------------------------------*/
#include "misc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup MISC 
  * @brief MISC driver modules
  * @{
  */

/** @defgroup MISC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */ 

/** @defgroup MISC_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup MISC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup MISC_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup MISC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup MISC_Private_Functions
  * @{
  */

/**
  * @brief  Configures the SysTick clock source.
  * @param  SysTick_CLKSource: specifies the SysTick clock source.
  *         This parameter can be one of the following values:
  *         @arg @ref SysTick_CLKSource_HCLK_Div4: AHB clock divided by 4 selected as SysTick clock source.
  *         @arg @ref SysTick_CLKSource_HCLK: AHB clock selected as SysTick clock source.
  * @retval None
  */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
  /* Check the parameters */
  assert_param(IS_SYSTICK_CLK_SOURCE(SysTick_CLKSource));
  if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
  {
    SysTick->CTRL |= SysTick_CLKSource_HCLK;
  }
  else
  {
    SysTick->CTRL &= SysTick_CLKSource_HCLK_Div4;
  }
}

/**
  * @brief  Delay n ticks.
  * @param  Ticks: Number of ticks to delay.
  * @note   Since SysTick_LOAD is a 24-bit register,
  *         the n_ticks must be less than 16777216.
  * @retval None
  */
__WEAK void SysTick_DelayNticks(uint32_t Ticks)
{
  uint32_t status;
  /* Configure the reload value */
  SysTick->LOAD = Ticks;
  /* Clear the counter */
  SysTick->VAL = 0x00;
  /* The core clock as clock source and enable SysTick */
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
  /* Wait for count to 0 */
  do {
    status = SysTick->CTRL;
  } while ((status & SysTick_CTRL_ENABLE_Msk) &&
           (!(status & SysTick_CTRL_COUNTFLAG_Msk)));
  /* Disable SysTick */
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  Delay n Us.
  * @param  Us: Number of Us to delay.
  * @note   None
  * @retval None
  */
__WEAK void SysTick_DelayUs(uint32_t Us)
{
  SysTick->LOAD = SystemCoreClock / 1000000;
  SysTick->VAL = 0x00;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
  while (Us--)
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
      ;
  SysTick->CTRL = 0x00;
}

/**
  * @brief  Delay n Ms.
  * @param  Ms: Number of Ms to delay.
  * @note   None
  * @retval None
  */
__WEAK void SysTick_DelayMs(uint32_t Ms)
{
  SysTick->LOAD = SystemCoreClock / 1000;
  SysTick->VAL = 0x00;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
  while (Ms--)
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
      ;
  SysTick->CTRL = 0x00;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
