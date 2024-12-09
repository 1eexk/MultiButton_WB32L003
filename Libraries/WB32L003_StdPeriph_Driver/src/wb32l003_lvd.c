/**
 * @file    wb32l003_lvd.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the LVD firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_lvd.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup LVD 
  * @brief LVD driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup LVD_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the LVD peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void LVD_DeInit(void)
{
  RCC_APBPeriphResetCmd(RCC_APBPeriph_LVDVC, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_LVDVC, DISABLE);
}

/**
  * @brief  Enables or disables the LVD digital filter.
  * @param  NewState: The new state of the LVD digital filter.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_DIGFLT_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    LVD->CR |= LVD_CR_FLTEN;
  }
  else
  {
    LVD->CR &= ~LVD_CR_FLTEN;
  }
}

/**
  * @brief  Initializes the LVD Unit according to the specified
  *         parameters in the LVD_InitTypeDef.
  * @param  InitStruct: Pointer to LVD initialization structure that contains
  *         the configuration information for the specified LVD module.
  * @retval None
  */
void LVD_Init(LVD_InitTypeDef *InitStruct)
{
  /* Check the parameters */
  assert_param(IS_LVD_VOLLEVEL(InitStruct->VoltageLevel));
  assert_param(IS_LVD_ACTION(InitStruct->Action));
  assert_param(IS_LVD_TRIGGER(InitStruct->TriggerSel));
  assert_param(IS_LVD_FLTCLK(InitStruct->FltClkSel));

  /* Reset LVD configuration */
  CLEAR_BIT(LVD->CR, LVD_CR_ALL_Msk);
  /* Update LVD configuration register */
  SET_BIT(LVD->CR, InitStruct->VoltageLevel | InitStruct->Action | InitStruct->TriggerSel);

  if (InitStruct->FltClkSel != LVD_FLTCLK_DISABLE)
  {
    assert_param(IS_LVD_FLTNUM(InitStruct->FltNum));
    SET_BIT(LVD->CR, InitStruct->FltClkSel | (InitStruct->FltNum << LVD_CR_FLT_NUM_Pos));
    /* Enables the LVD digital filter */
    LVD->CR |= LVD_CR_FLTEN;
  }
}

/**
  * @brief  Enables or disables the LVD peripheral.
  * @param  NewState: The new state of the LVD peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    LVD->CR |= LVD_CR_LVDEN;
  }
  else
  {
    LVD->CR &= ~LVD_CR_LVDEN;
  }
}

/**
  * @brief  Enables or disables LVD interrupt.
  * @param  NewState: The new state of LVD interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LVD_ITCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    LVD->CR |= LVD_CR_INT_EN;
  }
  else
  {
    LVD->CR &= ~LVD_CR_INT_EN;
  }
}

/**
  * @brief  Checks whether LVD interrupt flag is set or not.
  * @param  None
  * @retval The new state of LVD interrupt flag (SET or RESET).
  */
FlagStatus LVD_GetFlagStatus(void)
{
  FlagStatus bitstatus = RESET;

  /* Check the status of the specified LVD flag */
  if ((LVD->SR & LVD_SR_INTF))
  {
    /* LVD flag is set */
    bitstatus = SET;
  }
  else
  {
    /* LVD flag is reset */
    bitstatus = RESET;
  }
  /* Return the LVD flag status */
  return bitstatus;
}

/**
  * @brief  Checks whether LVD interrupt is set or not.
  * @param  None
  * @retval The new state of LVD interrupt (SET or RESET).
  */
ITStatus LVD_GetITStatus(void)
{
  ITStatus bitstatus = RESET;

  /* Check the status of LVD interrupt */
  if ((LVD->SR & LVD_SR_INTF) && (LVD->CR & LVD_CR_INT_EN))
  {
    /* LVD interrupt is set */
    bitstatus = SET;
  }
  else
  {
    /* LVD interrupt is reset */
    bitstatus = RESET;
  }
  /* Return the LVD interrupt status */
  return bitstatus;
}

/**
  * @brief  Clears the LVD interrupt bit.
  * @param  None
  * @retval None
  */
void LVD_ClearITPendingBit(void)
{
  LVD->SR = 0x00;
}

/**
  * @brief  Clears the LVD flag.
  * @param  None
  * @retval None
  */
void LVD_ClearFlag(void)
{
  LVD->SR = 0x00;
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
