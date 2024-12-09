/**
 * @file    wb32l003_beep.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the BEEP firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_beep.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup BEEP
  * @brief BEEP driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup BEEP_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the BEEP peripheral registers to their default reset values.
  * @param  BEEPx: Pointer to selected BEEP peripheral.
  *         This parameter can be one of the following values:
  *         BEEP.
  * @retval None
  */
void BEEP_DeInit(BEEP_TypeDef* BEEPx)
{
  /* Check the parameters */
  assert_param(IS_BEEP_ALL_PERIPH(BEEPx));

  if (BEEPx == BEEP)
  {
    RCC_APBPeriphResetCmd(RCC_APBPeriph_BEEP, ENABLE);
    RCC_APBPeriphResetCmd(RCC_APBPeriph_BEEP, DISABLE);
  }
}

/**
  * @brief  Initializes the BEEP peripheral according to the specified 
  *         parameters in the BEEP_InitStruct.
  * @param  BEEPx: Pointer to selected BEEP peripheral.
  *         This parameter can be one of the following values:
  *         BEEP.
  * @param  BEEP_InitStruct: Pointer to BEEP initialization struct
  * @retval None
  */
void BEEP_Init(BEEP_TypeDef* BEEPx, BEEP_InitTypeDef *BEEP_InitStruct)
{

  /* Check the parameters */
  assert_param(IS_BEEP_ALL_PERIPH(BEEPx));
  assert_param(IS_BEEP_CLK_SEL(BEEP_InitStruct.BEEP_ClkSel));
  assert_param(IS_BEEP_PRESCALER(BEEP_InitStruct.BEEP_Prescaler));
  assert_param(IS_BEEP_OUT_DIV(BEEP_InitStruct.BEEP_OutDiv));

  /* Confiog BEEP peripheral */
  BEEPx->CSR &= (~(BEEP_CSR_CLKSEL_Msk | BEEP_CSR_BEEPSEL_Msk | BEEP_CSR_BEEPDIV_Msk));
  BEEPx->CSR |= (BEEP_InitStruct->BEEP_ClkSel | BEEP_InitStruct->BEEP_OutDiv | BEEP_InitStruct->BEEP_Prescaler);
}

/**
  * @brief  Enables or disables BEEP peripheral.
  * @param  BEEPx: Pointer to selected BEEP peripheral.
  *         This parameter can be one of the following values:
  *         BEEP.
  * @param  NewState: The new state of the BEEP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BEEP_Cmd(BEEP_TypeDef* BEEPx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_BEEP_ALL_PERIPH(BEEPx));

  if (NewState != DISABLE)
  {
    BEEP->CSR |= BEEP_CSR_BEEPEN;
  }
  else 
  {
    BEEP->CSR &= ~BEEP_CSR_BEEPEN;
  }
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
