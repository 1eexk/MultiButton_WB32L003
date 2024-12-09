/**
 * @file    wb32l003_lptim.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the LPTIM firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_lptim.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup LPTIM 
  * @brief LPTIM driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup LPTIM_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the LPTIM peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void LPTIM_DeInit(void)
{
  RCC_APBPeriphResetCmd(RCC_APBPeriph_LPTIM, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_LPTIM, DISABLE);
}

/**
  * @brief  Low Power Time base configuration
  * @param  Base_InitStruct : Pointer to LPTIM_BaseInitTypeDef structure that 
  *         contains the configuration information for the specified LPTIM module.
  * @retval None
  */
void LPTIM_BaseInit(LPTIM_BaseInitTypeDef *Base_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_LPTIM_GATE_ENABLE(Base_InitStruct->GateEnable));
  assert_param(IS_LPTIM_GATE_LEVEL(Base_InitStruct->GateLevel));
  assert_param(IS_LPTIM_TOG(Base_InitStruct->TogEnable));
  assert_param(IS_LPTIM_COUNTER(Base_InitStruct->CntTimSel));
  assert_param(IS_LPTIM_AUTORELOAD(Base_InitStruct->AutoReload));
  assert_param(IS_LPTIM_CLOCK_SOURCE(Base_InitStruct->ClkSel));

  /* Reset all low power timer function */
  LPTIM->CR &= ~LPTIM_CR_ALL_Msk;
  /* Update LPTIM configuration register */
  LPTIM->CR = Base_InitStruct->GateLevel | Base_InitStruct->GateEnable | Base_InitStruct->TogEnable |
              Base_InitStruct->CntTimSel | Base_InitStruct->AutoReload | Base_InitStruct->ClkSel;

  /*Wait for synchronization */
  while ((LPTIM->CR & (LPTIM_CR_WT_FLAG)) == (LPTIM_CR_WT_FLAG))
    ;

  /* Set LPTIM counter value */
  if (Base_InitStruct->AutoReload == LPTIM_AUTORELOAD_ENABLE)
    LPTIM->BGLOAD = Base_InitStruct->Period;
  else
    LPTIM->LOAD = Base_InitStruct->Period;
}

/**
  * @brief  Enables or disables the LPTIM time clock.
  * @param  NewState: The new state of the LPTIM peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIM_TCKCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the  LPTIM time clock */
    LPTIM->CR |= LPTIM_CR_TCK_EN;
  }
  else
  {
    /* Disable the LPTIM time clock */
    LPTIM->CR &= ~LPTIM_CR_TCK_EN;
  }
}

/**
  * @brief  Enables or disables the LPTIM peripheral.
  * @param  NewState: The new state of the LPTIM peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIM_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the  LPTIM peripheral */
    LPTIM->CR |= LPTIM_CR_TIM_RUN;
  }
  else
  {
    /* Disable the LPTIM peripheral */
    LPTIM->CR &= ~LPTIM_CR_TIM_RUN;
  }
}

/**
  * @brief  Enables or disables the LPTIM interrupt.
  * @param  NewState: The new state of LPTIM interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIM_ITCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the LPTIM interrupt */
    LPTIM->CR |= LPTIM_CR_INT_EN;
  }
  else
  {
    /* Disable the LPTIM interrupt */
    LPTIM->CR &= ~LPTIM_CR_INT_EN;
  }
}

/**
  * @brief  Checks whether the LPTIM interrupt flag is set or not.
  * @param  None
  * @retval The new state of LPTIM interrupt flag(SET or RESET).
  */
FlagStatus LPTIM_GetFlagStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((LPTIM->INTSR & LPTIM_INTSR_INTF))
  {
   /* LPTIM interrupt flag is set */
    bitstatus = SET;
  }
  else
  {
    /* LPTIM interrupt flag is reset */
    bitstatus = RESET;
  }
  /* Return the LPTIM interrupt flag status */
  return bitstatus;
}

/**
  * @brief  Checks whether the LPTIM interrupt is set or not.
  * @param  None
  * @retval The new state of LPTIM interrupt (SET or RESET).
  */
ITStatus LPTIM_GetITStatus(void)
{
  ITStatus bitstatus = RESET;

  if ((LPTIM->INTSR & LPTIM_INTSR_INTF) && (LPTIM->CR & LPTIM_CR_INT_EN))
  {
    /* LPTIM interrupt is set */
    bitstatus = SET;
  }
  else
  {
    /* LPTIM interrupt is reset */
    bitstatus = RESET;
  }
  /* Return the LPTIM interrupt status */
  return bitstatus;
}

/**
  * @brief  Clears the LPTIM pending interrupt flag.
  * @param  None
  * @retval None
  */
void LPTIM_ClearFlag(void)
{
  /* Clear the LPTIM interrupt flag */
  LPTIM->INTCLR |= (uint32_t)LPTIM_INTCLR_ICLR;
}

/**
  * @brief  Clears the LPTIM pending interrupt bit.
  * @param  None
  * @retval None
  */
void LPTIM_ClearITPendingBit(void)
{
  /* Clear the LPTIM interrupt */
  LPTIM->INTCLR |= (uint32_t)LPTIM_INTCLR_ICLR;
}

/**
  * @brief  Sets the LPTIM counter register value on runtime.
  * @param  Counter: Counter value.
  * @retval None
  */
void LPTIM_SetCounter(uint32_t Counter)
{
  while ((LPTIM->CR & LPTIM_CR_WT_FLAG) == LPTIM_CR_WT_FLAG)
    ;
  WRITE_REG(LPTIM->LOAD, Counter);
  while ((LPTIM->CR & LPTIM_CR_WT_FLAG) == LPTIM_CR_WT_FLAG)
    ;
  WRITE_REG(LPTIM->BGLOAD, Counter);
}

/**
  * @brief  Gets LPTIM counter.
  * @param  None
  * @retval Counter value
  */
uint32_t LPTIM_GetCounter(void)
{
  return LPTIM->CNTVAL;
}

/**
  * @brief  Enables or disables the LPTIM gate function.
  * @param  NewState: The new state of LPTIM gate function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIM_GateCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the LPTIM gate function */
    LPTIM->CR |= LPTIM_CR_INT_EN;
  }
  else
  {
    /* Disable the LPTIM gate funtion */
    LPTIM->CR &= ~LPTIM_CR_INT_EN;
  }
}

/**
  * @brief  Enables or disables the LPTIM toggle function.
  * @param  NewState: The new state of LPTIM toggle function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPTIM_ToggleCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the LPTIM toggle function */
    LPTIM->CR |= LPTIM_CR_TOG_EN;
  }
  else
  {
    /* Disable the LPTIM toggle funtion */
    LPTIM->CR &= ~LPTIM_CR_TOG_EN;
  }
}

/**
  * @brief  Sets gate level high or low.
  * @param  Level: Gate level configuartion.
  *         This param can be LPTIM_GATELEVEL_HIGH or LPTIM_GATELEVEL_LOW.
  * @retval None
  */
void LPTIM_SetGateLevel(uint32_t Level)
{
  if (Level == LPTIM_GATELEVEL_HIGH)
  {
    /* Set the LPTIM gate high level */
    LPTIM->CR |= LPTIM_CR_GATE_P;
  }
  else
  {
    /* Set the LPTIM gate low level */
    LPTIM->CR &= ~LPTIM_CR_GATE_P;
  }
}

/**
  * @brief  Waits for LPTIM WT sync finish.
  * @param  None
  * @retval The new state of syns finish (SET or RESET).
  */
FlagStatus LPTIM_GetSyncFlag(void)
{
  FlagStatus bitstatus = RESET;

  if ((LPTIM->CR & (LPTIM_CR_WT_FLAG)) == LPTIM_CR_WT_FLAG)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
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
