/**
 * @file    wb32l003_wwdg.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the WWDG firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_wwdg.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup WWDG 
  * @brief WWDG driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup WWDG_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WWDG_DeInit(void)
{
  RCC_APBPeriphResetCmd(RCC_APBPeriph_WWDG, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_WWDG, DISABLE);
}

/**
  * @brief  Sets the WWDG Prescaler.
  * @param  WWDG_Prescaler: specifies the WWDG Prescaler.
  * @retval None
  */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_WWDG_PRESCALER_VALUE(WWDG_Prescaler));
  /* Clear PRSC[19:0] bits */
  tmpreg = WWDG->CR & (uint32_t)(~WWDG_CR_PRSC_Msk);
  /* Set PRSC[19:0] bits according to WWDG_Prescaler value */
  tmpreg |= (WWDG_Prescaler << WWDG_CR_PRSC_Pos) & WWDG_CR_PRSC_Msk;
  /* Store the new value */
  WWDG->CR = tmpreg;
}

/**
  * @brief  Sets the WWDG window value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  *         This parameter value must be lower than 0x80.
  * @retval None
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
  /* Clear WINCMP[7:0] bits */
  tmpreg = WWDG->CR & (uint32_t)(~(WWDG_CR_WINCMP_Msk));

  /* Set WINCMP[7:0] bits according to WindowValue value */
  tmpreg |= (WindowValue << WWDG_CR_WINCMP_Pos) & (uint32_t)WWDG_CR_WINCMP_Msk;

  /* Store the new value */
  WWDG->CR = tmpreg;
}

/**
  * @brief  Enables or disable the WWDG's interrupt.
  * @param  NewState: The new state of the WWDG's interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WWDG_IT_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    WWDG->INTEN |= WWDG_INTEN_WWDGIEN;
  }
  else
  {
    WWDG->INTEN &= ~WWDG_INTEN_WWDGIEN_Msk;
  }
}

/**
  * @brief  Sets the WWDG counter value.
  * @param  Counter: specifies the watchdog counter value.
  *         This parameter must be a number between 0x40 and 0x7F.
  * @retval None
  */
void WWDG_SetCounter(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_RELOAD_VALUE(Counter));
  /* Write to WWDG_RLOAD[7:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->RLOAD = (Counter << WWDG_RLOAD_RLOAD_Pos) & WWDG_RLOAD_RLOAD_Msk;
}

/**
  * @brief  Enables or disables the WWDG peripheral.
  * @param  NewState: The new state of the WWDG peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WWDG_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Set WWDGEN bit */
    WWDG->CR |= WWDG_CR_WWDGEN;
  }
  else
  {
    /* Clear WWDGEN bit */
    WWDG->CR &= ~WWDG_CR_WWDGEN_Msk;
  }
}

/**
  * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
  * @param  None
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
  */
FlagStatus WWDG_GetFlagStatus(void)
{
  return (FlagStatus)(WWDG->SR);
}

/**
  * @brief  Clears Early Wakeup interrupt flag.
  * @param  None
  * @retval None
  */
void WWDG_ClearFlag(void)
{
  WWDG->INTCLR = (uint32_t)SET;
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
