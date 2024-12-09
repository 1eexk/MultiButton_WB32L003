/**
 * @file    wb32l003_pwr.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the PWR firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_pwr.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR 
  * @brief PWR driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions
  * @{
  */

/**
  * @brief Enters Sleep mode.
  * @note  In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param SLEEPEntry: Specifies if SLEEP mode is entered with WFI or WFE instruction.
  *        When WFI entry is used, tick interrupt have to be disabled if not desired as 
  *        the interrupt wake up source.
  *        This parameter can be one of the following values:
  *        @arg @ref PWR_SLEEPENTRY_WFI: enter SLEEP mode with WFI instruction
  *        @arg @ref PWR_SLEEPENTRY_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSLEEPMode(uint8_t SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_SLEEP_ENTRY(SLEEPEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* Select SLEEP mode entry -------------------------------------------------*/
  if (SLEEPEntry == PWR_SLEEPENTRY_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE();
    __WFE();
  }
}

/**
  * @brief  Enters Deep Sleep mode. 
  * @note   In Deep Sleep mode, all I/O pins keep the same state as in Run mode.
  * @retval None
  */
void PWR_EnterDEEPSLEEPMode(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  /* This option is used to ensure that store operations are completed */
#if defined(__CC_ARM)
  __force_stores();
#endif
  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @brief  Indicates Sleep-On-Exit when returning from Handler mode to Thread mode. 
  * @note   Set SLEEPONEXIT bit of SCR register. When this bit is set, the processor 
  *         re-enters SLEEP mode when an interruption handling is over.
  *         Setting this bit is useful when the processor is expected to run only on
  *         interruptions handling.         
  * @retval None
  */
void PWR_EnableSleepOnExit(void)
{
  /* Set SLEEPONEXIT bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Disables Sleep-On-Exit feature when returning from Handler mode to Thread mode. 
  * @note   Clears SLEEPONEXIT bit of SCR register. When this bit is set, the processor 
  *         re-enters SLEEP mode when an interruption handling is over.          
  * @retval None
  */
void PWR_DisableSleepOnExit(void)
{
  /* Clear SLEEPONEXIT bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPONEXIT_Msk));
}

/**
  * @brief  Enables CORTEX M0+ SEVONPEND bit. 
  * @note   Sets SEVONPEND bit of SCR register. When this bit is set, this causes 
  *         WFE to wake up when an interrupt moves from inactive to pended.
  * @retval None
  */
void PWR_EnableSEVOnPend(void)
{
  /* Set SEVONPEND bit of Cortex System Control Register */
  SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
}

/**
  * @brief  Disables CORTEX M0+ SEVONPEND bit. 
  * @note   Clears SEVONPEND bit of SCR register. When this bit is set, this causes 
  *         WFE to wake up when an interrupt moves from inactive to pended.         
  * @retval None
  */
void PWR_DisableSEVOnPend(void)
{
  /* Clear SEVONPEND bit of Cortex System Control Register */
  CLEAR_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SEVONPEND_Msk));
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
