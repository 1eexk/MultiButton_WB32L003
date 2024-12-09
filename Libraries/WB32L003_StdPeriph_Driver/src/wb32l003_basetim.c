/**
 * @file    wb32l003_basetim.c
 * @author  WestberryTech Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the BaseTIM firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_basetim.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup BaseTIM 
  * @brief BaseTIM driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup TIM_Private_Defines
  * @{
  */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup TIM_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TIMx peripheral registers to their default reset values.
  * @param  TIMx: where x can be 10 and 11 to select the BaseTIM peripheral.
  * @retval None
  */
void BaseTim_DeInit(BASETIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));
 
  RCC_APBPeriphResetCmd(RCC_APBPeriph_BASETIM, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_BASETIM, DISABLE);
}

/**
  * @brief  Initializes the BaseTIMx Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: where x can be 1 to 8 to select the BaseTIM peripheral.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for the 
  *         specified BaseTIM peripheral.
  * @retval None
  */
void BaseTim_Init(BASETIM_TypeDef* TIMx, BaseTim_InitTypeDef* BaseTim_InitStruct)
{
  uint32_t tmpcr = 0;

  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));

  tmpcr = TIMx->CR;

  tmpcr &= 0x0;
  tmpcr |= (BaseTim_InitStruct->BaseTim_Gate | BaseTim_InitStruct->BaseTim_GatePolarity |
            BaseTim_InitStruct->BaseTim_Tog | BaseTim_InitStruct->BaseTim_Function |
            BaseTim_InitStruct->BaseTim_AutoReload | BaseTim_InitStruct->BaseTim_CountLevel |
            BaseTim_InitStruct->BaseTim_CountMode | BaseTim_InitStruct->BaseTim_Prescaler);
  TIMx->CR = tmpcr;

  TIMx->BGLOAD = BaseTim_InitStruct->BaseTim_BGLoad;
}

void BaseTim_Cmd(BASETIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));

  if (NewState != DISABLE)
  {
    /* Enable the BaseTIM */
    TIMx->CR |= BASETIM_CR_TR;
  }
  else
  {
    /* Disable the BaseTIM */
    TIMx->CR &= (~(uint32_t)BASETIM_CR_TR);
  }
}

void BaseTim_ITConfig(BASETIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIMx->CR |= BASETIM_CR_INTEN;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIMx->CR &= (~(uint32_t)BASETIM_CR_INTEN);
  }

}

uint32_t BaseTim_GetCounter(BASETIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));

  return TIMx->CNT;
}

void BaseTim_SetLoad(BASETIM_TypeDef* TIMx, uint16_t load)
{
  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));

  TIMx->LOAD = load;
}

void BaseTim_SetBkLoad(BASETIM_TypeDef* TIMx, uint16_t bgLoad)
{
  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));

  TIMx->BGLOAD = bgLoad;
}

FlagStatus BaseTim_GetFlagStatus(BASETIM_TypeDef* TIMx)
{
  ITStatus bitstatus = RESET; 

  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));

  if ((TIMx->MSKINTSR & 0x01) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

void BaseTim_ClearFlag(BASETIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_BaseTIM_ALL_PERIPH(TIMx));

  TIMx->INTCLR |= BASETIM_INTCLR_INTCLR;
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

