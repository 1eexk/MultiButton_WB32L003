/**
 * @file    wb32l003_vcmp.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the VCMP firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_vcmp.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup VCMP
  * @brief VCMP driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup VCMP_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the VCMP peripheral.
  * @param  None
  * @retval None
  */
void VCMP_DeInit(void)
{
  RCC_APBPeriphResetCmd(RCC_APBPeriph_LVDVC, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_LVDVC, DISABLE);
}

/**
  * @brief  Initializes the VCMP according to the specified parameters in the
  *         VCMP_HandleTypeDef. 
  * @param  InitStruct: Pointer to a VCMP_InitTypeDef structure that contains
  *         the configuration information for the specified VCMP module.
  * @retval None
  */
void VCMP_Init(VCMP_InitTypeDef *InitStruct)
{
  /* Check the parameters */
  assert_param(IS_VCMP_VCAPDIV(InitStruct->VcapDiv));
  assert_param(IS_VCMP_INPUT(InitStruct->NegPinSel));
  assert_param(IS_VCMP_INPUT(InitStruct->PosPinSel));
  assert_param(IS_VCMP_FILTER_ENABLE(InitStruct->Filter_Enable));

  /* Write CR0 */
  WRITE_REG(VCMP->CR0, (((InitStruct->VcapDiv) << VCMP_CR0_VCAPDIV_Pos) |
                        ((InitStruct->NegPinSel) << VCMP_CR0_NINSEL_Pos) |
                        (InitStruct->PosPinSel) | (VCMP_VCAPDIV_ENABLE)));

  /* Write to CR1 about filter */
  if (InitStruct->Filter_Enable != VCMP_FILTER_ENABLE)
  {
    CLEAR_BIT(VCMP->CR1, VCMP_FILTER_ENABLE);
  }
  else
  {
    /* Check the parameters */
    assert_param(IS_VCMP_FILTER_NUM(InitStruct->Fliter_Num));
    assert_param(IS_VCMP_FILTER_CLOCK(InitStruct->Filter_Clk));
    /* Update CR1 with filter configuration */
    SET_BIT(VCMP->CR1, (((InitStruct->Fliter_Num) << VCMP_CR1_FLT_NUM_Pos) |
                      (InitStruct->Filter_Clk) | VCMP_FILTER_ENABLE));
    if ((InitStruct->Filter_Clk) == VCMP_FILTER_CLK_NONE)
      CLEAR_BIT(VCMP->CR1, VCMP_CR1_VCMP_FLTCLK_SEL);
  }
}

/**
  * @brief  Enables or disables the specified VCMP interrupts.
  * @param  VCMP_INT: VCMP interrupt configuration
  *         This parameter can be any combination of the following values;
  *         @arg @ref VCMP_HIGH_INT: VCMP filter ouput high level interrupt.
  *         @arg @ref VCMP_RISE_INT: VCMP filter ouput rise interrupt.
  *         @arg @ref VCMP_FALL_INT: VCMP filter ouput fall interrupt.
  * @param  NewState: The new state of the specifed VCMP interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void VCMP_ITConfig(uint32_t VCMP_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_VCMP_INT(VCMP_INT));

  if (NewState != DISABLE)
  {
    SET_BIT(VCMP->CR1, VCMP_INT);
  }
  else
  {
    CLEAR_BIT(VCMP->CR1, VCMP_INT);
  }
}

/**
  * @brief  Enables or disables VCMP interrupt.
  * @param  NewState: The new state of the VCMP interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void VCMP_ITCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SET_BIT(VCMP->CR1, VCMP_INT_ENABLE);
  }
  else
  {
    CLEAR_BIT(VCMP->CR1, VCMP_INT_ENABLE);
  }
}

/**
  * @brief  Enables or disables the specified VCMP outputs.
  * @param  OutputConfig: VCMP output configuration
  *         This parameter can be any combination of the following values:
  *         @arg @ref VCMP_OUTCFG_INV_PAD: VCMP inverse filter output exported to VCMP_OUT channel.
  *         @arg @ref VCMP_OUTCFG_TIM1_BKE: VCMP filter output exported to TIM1 brake control.
  *         @arg @ref VCMP_OUTCFG_TIM1CH4_GATE: VCMP filter output exported to TIM1 capture channel 4 enable.
  *         @arg @ref VCMP_OUTCFG_INV_TIM1CH4_GATE: VCMP inverse filter output exported to TIM1 capture channel 4.
  *         @arg @ref VCMP_OUTCFG_TIM1CH3_GATE: VCMP filter output exported to TIM1 capture channel 3 enable.
  *         @arg @ref VCMP_OUTCFG_INV_TIM1CH3_GATE: VCMP inverse filter output exported to TIM1 capture channel 3.
  *         @arg @ref VCMP_OUTCFG_TIM1CH2_GATE: VCMP filter output exported to TIM1 capture channel 2 enable.
  *         @arg @ref VCMP_OUTCFG_INV_TIM1CH2_GATE: VCMP inverse filter output exported to TIM1 capture channel 2.
  *         @arg @ref VCMP_OUTCFG_TIM1CH1_GATE: VCMP filter output exported to TIM1 capture channel 1 enable.
  *         @arg @ref VCMP_OUTCFG_INV_TIM1CH1_GATE: VCMP inverse filter output exported to TIM1 capture channel 1.
  *         @arg @ref VCMP_OUTCFG_PCA_EXTCLK_EN: VCMP filter output exported to PCA ECI clock.
  *         @arg @ref VCMP_OUTCFG_PCA_CAP0_EN: VCMP filter output exported to PCA capture channel 0.
  *         @arg @ref VCMP_OUTCFG_INV_PCA: VCMP filter output exported to PCA inverse.
  *         @arg @ref VCMP_OUTCFG_LPTIM_EXTCLK_EN: VCMP filter output exported to LPTIM EXT clock
  *         @arg @ref VCMP_OUTCFG_LPTIM_GATE: VCMP filter output exported to LPTIM gate control.
  *         @arg @ref VCMP_OUTCFG_TIM11_GATE: VCMP filter output exported to TIM11 gate control.
  *         @arg @ref VCMP_OUTCFG_TIM10_GATE: VCMP filter output exported to TIM10 gate control.
  *         @arg @ref VCMP_OUTCFG_INV_LPTIM_TIM10_11: VCMP filter output exported to LPTIM, TIM10, TIM11 inverse gate control. 
  * @param  NewState: The new state of the specified VCMP outputs.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void VCMP_OutputConfig(uint32_t OutputConfig, FunctionalState NewState)
{
  /* config the VCMP output */
  assert_param(IS_VCMP_OUTCFG(OutputConfig));

  if (NewState != DISABLE)
  {
    SET_BIT(VCMP->OUTCFG, (OutputConfig & VCMP_OUTCFG_MSK));
  }
  else
  {
    CLEAR_BIT(VCMP->OUTCFG, (OutputConfig & VCMP_OUTCFG_MSK));
  }
}

/**
  * @brief  Checks whether VCMP interrupt flag is set or reset.
  * @param  None
  * @retval The new state of VCMP interrupt flag (SET or RESET).
  */
FlagStatus VCMP_GetFlagStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((VCMP->SR & VCMP_SR_INTF))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the interrupt flag status */
  return bitstatus;
}

/**
  * @brief  Checks whether VCMP interrupt is set or reset.
  * @param  None
  * @retval The new state of VCMP interrupt(SET or RESET).
  */
ITStatus VCMP_GetITStatus(void)
{
  ITStatus bitstatus = RESET;

  if ((VCMP->SR & VCMP_SR_INTF) && (VCMP->CR1 & VCMP_INT_ENABLE))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the interrupt status */
  return bitstatus;
}

/**
  * @brief  Clears VCMP interrupt flag.
  * @param  None
  * @retval None
  */
void VCMP_ClearFlag(void)
{
  CLEAR_BIT(VCMP->SR, VCMP_SR_INTF);
}

/**
  * @brief  Clears VCMP interrupt.
  * @param  None
  * @retval None
  */
void VCMP_ClearITPendingBit(void)
{
  CLEAR_BIT(VCMP->SR, VCMP_SR_INTF);
}

/**
  * @brief  Checks VCMP output is set or reset.
  * @param  None
  * @retval The new state of VCMP_OUTPUT (SET or RESET).
  */
FlagStatus VCMP_GetOutputStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((VCMP->SR & VCMP_SR_VCMP_FLOUT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the VCMP output status */
  return bitstatus;
}

/**
  * @brief  Enables or disables VCMP peripheral(write access to VCMP_CR1 registers).
  * @param  NewState: The new state of the VCMP peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void VCMP_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    SET_BIT(VCMP->CR1, VCMP_ENABLE);
  }
  else
  {
    CLEAR_BIT(VCMP->CR1, VCMP_ENABLE);
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
