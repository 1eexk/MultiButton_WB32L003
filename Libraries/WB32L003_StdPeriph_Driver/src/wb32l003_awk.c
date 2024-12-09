/**
 * @file    wb32l003_awk.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the AWK firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_awk.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup AWK 
  * @brief AWK driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup AWK_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the AWK peripheral registers to their default reset values.
  * @retval None
  */
void AWK_DeInit(void)
{
  RCC_AHBPeriphResetCmd(RCC_APBPeriph_AWK,ENABLE);
  RCC_AHBPeriphResetCmd(RCC_APBPeriph_AWK,DISABLE);
}

/**
  * @brief  Initializes the AWK peripheral according to the specified parameters
  *         in the AWK_InitStruct.
  * @param  AWK_InitStruct: pointer to an AWK_InitTypeDef structure that contains
  *         the configuration information for the AWK peripheral.
  * @retval None
  */
void AWK_Init(AWK_InitTypeDef * AWK_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_AWK_CLK_SEL(AWK_InitStruct->AWK_CLK_SEL));
  assert_param(IS_AWK_HSE_PRSC(AWK_InitStruct->AWK_HSE_PRSC));
  assert_param(IS_AWK_RLOAD_VAL(AWK_InitStruct->AWK_RLOAD_VAL));
  assert_param(IS_AWK_DIV_SEL(AWK_InitStruct->AWK_DIV_SEL));
 
  AWK->CR = 0x00000000;
  AWK->INTCLR |= 0x00000001;

  AWK->CR |= AWK_InitStruct->AWK_CLK_SEL;
  if(AWK_InitStruct->AWK_CLK_SEL == AWK_CLK_SEL_HSE)
    AWK->CR |= AWK_InitStruct->AWK_HSE_PRSC;
  AWK->CR |= AWK_InitStruct->AWK_DIV_SEL;
  AWK->RLOAD = AWK_InitStruct->AWK_RLOAD_VAL;
}

/**
  * @brief  Enables or disables the AWK peripheral.
  * @param  NewState: new state of the AWK peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void AWK_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the  AWK peripheral */
    AWK->CR |= AWK_CR_AWKEN;
  }
  else
  {
    /* Disable the  AWK peripheral */
    AWK->CR &= ~AWK_CR_AWKEN;
  }
}

/**
  * @brief  Checks whether the specified AWK flag is set or not.
  * @retval The new state of AWK_FLAG (SET or RESET).
  */
FlagStatus AWK_GetFlagStatus(void)
{
  FlagStatus bitstatus = RESET;
  /* Check the status of the specified AWK flag */
  if ((AWK->SR & AWK_SR_AWUF) == (uint16_t)AWK_SR_AWUF)
  {
    /* AWK_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* AWK_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the AWK_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the AWK pending flag.
  * @retval None
  */
void AWK_ClearFlag(void)
{
  /* Clear the selected AWK flag */
  AWK->INTCLR |= (uint32_t)AWK_INTCLR_INTCLR;
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
