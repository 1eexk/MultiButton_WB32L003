/**
 * @file    wb32l003_pca.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the PCA firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_pca.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup PCA
  * @brief PCA driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PCA_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the PCA peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void PCA_DeInit(void)
{
  RCC_APBPeriphResetCmd(RCC_APBPeriph_PCA, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_PCA, DISABLE);
}

/**
  * @brief  Enables or disables the PCA peripheral.
  * @param  NewState: The new state of the PCA peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PCA_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    PCA->CR |= PCA_CR_CR;
  }
  else
  {
    PCA->CR &= ~PCA_CR_CR;
  }
}

/**
  * @brief  Initializes the PCA Unit basic function according to the specified parameters 
  *         in the PCA_HandleTypeDef.
  * @param  PCA_InitStruct : Ponter to PCA base initialization structure.
  * @retval None
  */
void PCA_BaseInit(PCA_BaseInitTypeDef *PCA_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_PCA_CLOCK_COURCE(PCA_InitStruct->ClkSrcSel));
  assert_param(IS_PCA_IDLEMODE(PCA_InitStruct->RunInIdleMode));

  /* Reset all PCA function */
  PCA->CR &= ~PCA_CR_CR;
  PCA->MOD &= ~(PCA_MOD_CFIE | PCA_MOD_CPS | PCA_MOD_CIDL);

  /* Set the Pca configuration */
  PCA->MOD = PCA_InitStruct->ClkSrcSel | PCA_InitStruct->RunInIdleMode;
}

/**
  * @brief  Initializes the PCA output compare Channels according to the specified
  *         parameters in the PCA_OC_InitTypeDef.
  * @param  OC_Config : Pointer to PCA output compare configuration structure.
  * @retval None
  */
void PCA_OC_Config(PCA_OC_InitTypeDef *OC_Config)
{
  /* Check the parameters */
  assert_param(IS_PCA_OC_ENABLE(OC_Config->CompareEnable));
  assert_param(IS_PCA_TOG_ENABLE(OC_Config->TogEnable));
  assert_param(IS_PCA_PWM_ENABLE(OC_Config->PwmEnable));

  if ((OC_Config->Channel & PCA_CHANNEL_0) != RESET)
  {
    /* PCA Channel0 input capture configuration */
    /* Enable output compare and toggle function */
    MODIFY_REG(PCA->CCAPM0, PCA_CCAPM0_ECOM | PCA_CCAPM0_MAT | PCA_CCAPM0_TOG | PCA_CCAPM0_PWM,
               OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);

    /* Setting period */
    WRITE_REG(PCA->CCAP0H, OC_Config->Period);
  }
  if ((OC_Config->Channel & PCA_CHANNEL_1) != RESET)
  {
    /*PCA Channel1 input capture configuration */
    /* Enable output compare and toggle function */
    MODIFY_REG(PCA->CCAPM1, PCA_CCAPM1_ECOM | PCA_CCAPM1_MAT | PCA_CCAPM1_TOG | PCA_CCAPM1_PWM,
               OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);

    /* Setting period */
    WRITE_REG(PCA->CCAP1H, OC_Config->Period);
  }
  if ((OC_Config->Channel & PCA_CHANNEL_2) != RESET)
  {
    /* TI2 Channel2 input capture configuration */
    /* Enable output compare and toggle function */
    MODIFY_REG(PCA->CCAPM2, PCA_CCAPM2_ECOM | PCA_CCAPM2_MAT | PCA_CCAPM2_TOG | PCA_CCAPM2_PWM,
               OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);

    /* Setting period */
    WRITE_REG(PCA->CCAP2H, OC_Config->Period);
  }
  if ((OC_Config->Channel & PCA_CHANNEL_3) != RESET)
  {
    /* TI3 Channel3 input capture configuration */
    /* Enable output compare and toggle function */
    MODIFY_REG(PCA->CCAPM3, PCA_CCAPM3_ECOM | PCA_CCAPM3_MAT | PCA_CCAPM3_TOG | PCA_CCAPM3_PWM,
               OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);

    /* Setting period */
    WRITE_REG(PCA->CCAP3H, OC_Config->Period);
  }
  if ((OC_Config->Channel & PCA_CHANNEL_4) != RESET)
  {
    /* TI4 Channel4 input capture configuration */
    /* Enable output compare and toggle function */
    MODIFY_REG(PCA->CCAPM4, PCA_CCAPM4_ECOM | PCA_CCAPM4_MAT | PCA_CCAPM4_TOG | PCA_CCAPM4_PWM,
               OC_Config->CompareEnable | OC_Config->TogEnable | OC_Config->PwmEnable);

    /* Setting period */
    WRITE_REG(PCA->CCAP4H, OC_Config->Period);
  }
}

/**
  * @brief  Enables or disables the PCA output compare generation.
  * @param  Channel : PCA Channel associated with the capture compare register.
  *         This parameter can any combination of the following values:
  *         @arg @ref PCA_CHANNEL_0: Capture/Compare channel0
  *         @arg @ref PCA_CHANNEL_1: Capture/Compare channel1
  *         @arg @ref PCA_CHANNEL_2: Capture/Compare channel2
  *         @arg @ref PCA_CHANNEL_3: Capture/Compare channel3
  *         @arg @ref PCA_CHANNEL_4: Capture/Compare channel4
  * @param  NewState: The new state of the specified PCA channel output compare generation.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
*/
void PCA_OC_Cmd(uint32_t Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_PCA_CHANNEL(Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    PCA->POCR |= Channel;
  }
  else
  {
    PCA->POCR &= ~Channel;
  }
}

/**
  * @brief  Enables or disables the PCA inverse output compare generation.
  * @param  Channel : PCA Channel associated with the capture compare register.
  *         This parameter can be any combination of the following values:
  *         @arg @ref PCA_CHANNEL_0: Capture/Compare channel0
  *         @arg @ref PCA_CHANNEL_1: Capture/Compare channel1
  *         @arg @ref PCA_CHANNEL_2: Capture/Compare channel2
  *         @arg @ref PCA_CHANNEL_3: Capture/Compare channel3
  *         @arg @ref PCA_CHANNEL_4: Capture/Compare channel4
  * @param  NewState: The new state of the specified PCA channle inverse output compare generation.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
*/
void PCA_OC_INVCmd(uint32_t Channel, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_PCA_CHANNEL(Channel));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    PCA->POCR |= (Channel << 8);
  }
  else
  {
    PCA->POCR &= ~(Channel << 8);
  }
}

/**
  * @brief  Initializes the PCA input capture Channels according to the specified
  *         parameters in the PCA_IC_InitTypeDef.
  * @param  IC_Config : Pointer to PCA input capture configuration structure.
  * @retval None
  */
void PCA_IC_Config(PCA_IC_InitTypeDef* IC_Config)
{
  /* Check the parameters */
  assert_param(IS_PCA_CHANNEL(IC_Config->Channel));
  assert_param(IS_PCA_INPUT_POLARATY(IC_Config->ICPolarity));

  if ((IC_Config->Channel & PCA_CHANNEL_0) != RESET)
  {
    /* TI0 Channel0 input capture configuration */
    PCA_IC0_TriggerConfig(IC_Config->ICPolarity);
  }
  if ((IC_Config->Channel & PCA_CHANNEL_1) != RESET)
  {
    /* TI1 Channel1 input capture configuration */
    PCA_IC1_TriggerConfig(IC_Config->ICPolarity);
  }
  if ((IC_Config->Channel & PCA_CHANNEL_2) != RESET)
  {
    /* TI2 Channel2 input capture configuration */
    PCA_IC2_TriggerConfig(IC_Config->ICPolarity);
  }
  if ((IC_Config->Channel & PCA_CHANNEL_3) != RESET)
  {
    /* TI3 Channel3 input capture configuration */
    PCA_IC3_TriggerConfig(IC_Config->ICPolarity);
  }
  if ((IC_Config->Channel & PCA_CHANNEL_4) != RESET)
  {
    /* TI4 Channel4 input capture configuration */
    PCA_IC4_TriggerConfig(IC_Config->ICPolarity);
  }
}

/**
  * @brief  Enables or disables the specified PCA interrupt.
  * @param  PCA_IT: specifies the PCA interrupt source to enable or disable.
  *         This parameter can be any combination of the following values:
  *         @arg @ref PCA_IT_CC0: Capture/Compare 0 interrupt
  *         @arg @ref PCA_IT_CC1: Capture/Compare 1 interrupt
  *         @arg @ref PCA_IT_CC2: Capture/Compare 2 interrupt
  *         @arg @ref PCA_IT_CC3: Capture/Compare 3 interrupt
  *         @arg @ref PCA_IT_CC4: Capture/Compare 4 interrupt  
  *         @arg @ref PCA_IT_OVERFLOW: Overflow interrupt
  * @param  NewState: The new state of the specified PCA interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PCA_ITConfig(uint8_t PCA_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_PCA_IT(PCA_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    if ((PCA_IT & PCA_IT_CC0) == PCA_IT_CC0)
      PCA->CCAPM0 |= PCA_CCAPM0_CCIE;
    if ((PCA_IT & PCA_IT_CC1) == PCA_IT_CC1)
      PCA->CCAPM1 |= PCA_CCAPM1_CCIE;
    if ((PCA_IT & PCA_IT_CC2) == PCA_IT_CC2)
      PCA->CCAPM2 |= PCA_CCAPM2_CCIE;
    if ((PCA_IT & PCA_IT_CC3) == PCA_IT_CC3)
      PCA->CCAPM3 |= PCA_CCAPM3_CCIE;
    if ((PCA_IT & PCA_IT_CC4) == PCA_IT_CC4)
      PCA->CCAPM4 |= PCA_CCAPM4_CCIE;
    if ((PCA_IT & PCA_IT_OVERFLOW) == PCA_IT_OVERFLOW)
      PCA->MOD |= PCA_MOD_CFIE;
  }
  else
  {
    if ((PCA_IT & PCA_IT_CC0) == PCA_IT_CC0)
      PCA->CCAPM0 &= ~PCA_CCAPM0_CCIE;
    if ((PCA_IT & PCA_IT_CC1) == PCA_IT_CC1)
      PCA->CCAPM1 &= ~PCA_CCAPM1_CCIE;
    if ((PCA_IT & PCA_IT_CC2) == PCA_IT_CC2)
      PCA->CCAPM2 &= ~PCA_CCAPM2_CCIE;
    if ((PCA_IT & PCA_IT_CC3) == PCA_IT_CC3)
      PCA->CCAPM3 &= ~PCA_CCAPM3_CCIE;
    if ((PCA_IT & PCA_IT_CC4) == PCA_IT_CC4)
      PCA->CCAPM4 &= ~PCA_CCAPM4_CCIE;
    if ((PCA_IT & PCA_IT_OVERFLOW) == PCA_IT_OVERFLOW)
      PCA->MOD &= ~PCA_MOD_CFIE;
  }
}

/**
  * @brief  Checks whether the specified PCA interrupt is set or not.
  * @param  PCA_FLAG: specifies the interrupt to check. 
  *         This parameter can be any combination of the following values:
  *         @arg @ref PCA_IT_CC0: PCA Capture/Compare 0 interrupt
  *         @arg @ref PCA_IT_CC1: PCA Capture/Compare 1 interrupt
  *         @arg @ref PCA_IT_CC2: PCA Capture/Compare 2 interrupt
  *         @arg @ref PCA_IT_CC3: PCA Capture/Compare 3 interrupt
  *         @arg @ref PCA_IT_CC4: PCA Capture/Compare 4 interrupt
  *         @arg @ref PCA_IT_OVERFLOW: PCA count overflow interrupt
  * @retval The new state of PCA_IT (SET or RESET).
  */
ITStatus PCA_GetITStatus(uint8_t PCA_IT)
{
  ITStatus bitstatus = RESET;
  uint16_t itstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_PCA_IT(PCA_IT));
  
  if ((PCA->CCAPM0 & PCA_CCAPM0_CCIE) && (PCA_IT & PCA_IT_CC0))
    itstatus |= PCA->CR & PCA_IT_CC0;
  if ((PCA->CCAPM1 & PCA_CCAPM1_CCIE) && (PCA_IT & PCA_IT_CC1))
    itstatus |= PCA->CR & PCA_IT_CC1;
  if ((PCA->CCAPM2 & PCA_CCAPM2_CCIE) && (PCA_IT & PCA_IT_CC2))
    itstatus |= PCA->CR & PCA_IT_CC2;
  if ((PCA->CCAPM3 & PCA_CCAPM3_CCIE) && (PCA_IT & PCA_IT_CC3))
    itstatus |= PCA->CR & PCA_IT_CC3;
  if ((PCA->CCAPM4 & PCA_CCAPM4_CCIE) && (PCA_IT & PCA_IT_CC4))
    itstatus |= PCA->CR & PCA_IT_CC4;
  if ((PCA->MOD & PCA_MOD_CFIE) && (PCA_IT & PCA_IT_OVERFLOW))
    itstatus |= PCA->CR & PCA_IT_OVERFLOW;
  
  if ((itstatus != (uint16_t)RESET))
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
  * @brief  Checks whether the specified PCA flag is set or not.
  * @param  PCA_FLAG: specifies the flag to check. 
  *         This parameter can be any combination of the following values:
  *         @arg @ref PCA_FLAG_CC0: PCA Capture/Compare 0 interrupt flag
  *         @arg @ref PCA_FLAG_CC1: PCA Capture/Compare 1 interrupt flag
  *         @arg @ref PCA_FLAG_CC2: PCA Capture/Compare 2 interrupt flag
  *         @arg @ref PCA_FLAG_CC3: PCA Capture/Compare 3 interrupt flag
  *         @arg @ref PCA_FLAG_CC4: PCA Capture/Compare 4 interrupt flag
  *         @arg @ref PCA_FLAG_OVERFLOW: PCA count overflow interrupt flag
  * @retval The new state of PCA_FLAG (SET or RESET).
  */
FlagStatus PCA_GetFlagStatus(uint8_t PCA_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_PCA_FLAG(PCA_FLAG));

  /* Check the status of the specified PCA flag */
  if ((PCA->CR & PCA_FLAG) != (uint16_t)RESET)
  {
    /* PCA_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* PCA_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the PCA_FLAG status */
  return bitstatus;
}

/**
  * @brief  Clears the PCA's interrupt pending bits.
  * @param  PCA_IT: specifies the PCA interrupt pending bits to clear.
  *         This parameter can be any combination of the following values:
  *         @arg @ref PCA_IT_CC0: PCA Capture/Compare 0 interrupt
  *         @arg @ref PCA_IT_CC1: PCA Capture/Compare 1 interrupt
  *         @arg @ref PCA_IT_CC2: PCA Capture/Compare 2 interrupt
  *         @arg @ref PCA_IT_CC3: PCA Capture/Compare 3 interrupt
  *         @arg @ref PCA_IT_CC4: PCA Capture/Compare 4 interrupt
  *         @arg @ref PCA_IT_OVERFLOW: PCA counter overflow interrupt
  * @retval None
  */
void PCA_ClearITPendingBit(uint8_t PCA_IT)
{
  /* Check the parameters */
  assert_param(IS_PCA_IT(PCA_IT));

  PCA->INTCLR |= PCA_IT;
}

/**
  * @brief  Clears the PCA's pending flags.
  * @param  PCA_FLAG: specifies the flags to clear. 
  *         This parameter can be one of the following values:
  *         @arg @ref PCA_FLAG_CC0: PCA Capture/Compare 0 interrupt flag
  *         @arg @ref PCA_FLAG_CC1: PCA Capture/Compare 1 interrupt flag
  *         @arg @ref PCA_FLAG_CC2: PCA Capture/Compare 2 interrupt flag
  *         @arg @ref PCA_FLAG_CC3: PCA Capture/Compare 3 interrupt flag
  *         @arg @ref PCA_FLAG_CC4: PCA Capture/Compare 4 interrupt flag
  *         @arg @ref PCA_FLAG_OVERFLOW: PCA count overflow interrupt flag
  * @retval None
  */
void PCA_ClearFlag(uint8_t PCA_FLAG)
{
  /* Check the parameters */
  assert_param(IS_PCA_FLAG(PCA_FLAG));

  PCA->INTCLR |= PCA_FLAG;
}

/**
  * @brief  Sets PCA PWM ouput duty cycle.
  * @param  Channel : PCA Channel associated with the capture compare register.
  *         This parameter can be any combination of the following values:
  *         @arg @ref PCA_CHANNEL_0: PCA Capture/Compare channel0
  *         @arg @ref PCA_CHANNEL_1: PCA Capture/Compare channel1
  *         @arg @ref PCA_CHANNEL_2: PCA Capture/Compare channel2
  *         @arg @ref PCA_CHANNEL_3: PCA Capture/Compare channel3
  *         @arg @ref PCA_CHANNEL_4: PCA Capture/Compare channel4
  * @param  Duty: PWM output duty configuration, the duty cycle will decrease 
  *         from 100% to 0.4% with the increase of Duty value from 0 to 255.
  * @retval None
  */
void PCA_SetPWMDuty(uint32_t Channel, uint8_t Duty)
{
  /* Check the parameters */
  assert_param(IS_PCA_CHANNEL(Channel));

  if ((Channel & PCA_CHANNEL_0) != RESET)
    PCA->CCAP0H = Duty;
  if ((Channel & PCA_CHANNEL_1) != RESET)
    PCA->CCAP1H = Duty;
  if ((Channel & PCA_CHANNEL_2) != RESET)
    PCA->CCAP2H = Duty;
  if ((Channel & PCA_CHANNEL_3) != RESET)
    PCA->CCAP3H = Duty;
  if ((Channel & PCA_CHANNEL_4) != RESET)
    PCA->CCAP4H = Duty;
}

/**
  * @brief  Configures the Channel0 (PCA Input capture).
  * @param  PCA_Trigger_ICPolarity: The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg @ref PCA_Trigger_ICPOLARITY_NONE
  *         @arg @ref PCA_Trigger_ICPOLARITY_RISING
  *         @arg @ref PCA_Trigger_ICPOLARITY_FALLING
  *         @arg @ref PCA_Trigger_ICPOLARITY_BOTHEDGE
  * @retval None
  */
void PCA_IC0_TriggerConfig(uint32_t PCA_Trigger_ICPolarity)
{
  /* Select the Polarity */
  MODIFY_REG(PCA->CCAPM0, PCA_CCAPM0_CAPP | PCA_CCAPM0_CAPN, PCA_Trigger_ICPolarity);
}

/**
  * @brief  Configures the Channel1 (PCA Input capture).
  * @param  PCA_Trigger_ICPolarity: The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg @ref PCA_Trigger_ICPOLARITY_NONE
  *         @arg @ref PCA_Trigger_ICPOLARITY_RISING
  *         @arg @ref PCA_Trigger_ICPOLARITY_FALLING
  *         @arg @ref PCA_Trigger_ICPOLARITY_BOTHEDGE
  * @retval None
  */
void PCA_IC1_TriggerConfig(uint32_t PCA_Trigger_ICPolarity)
{
  /* Select the Polarity */
  MODIFY_REG(PCA->CCAPM1, PCA_CCAPM1_CAPP | PCA_CCAPM1_CAPN, PCA_Trigger_ICPolarity);
}

/**
  * @brief  Configures the Channel2 (PCA Input capture).
  * @param  PCA_Trigger_ICPolarity: The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg @ref PCA_Trigger_ICPOLARITY_NONE
  *         @arg @ref PCA_Trigger_ICPOLARITY_RISING
  *         @arg @ref PCA_Trigger_ICPOLARITY_FALLING
  *         @arg @ref PCA_Trigger_ICPOLARITY_BOTHEDGE
  * @retval None
  */
void PCA_IC2_TriggerConfig(uint32_t PCA_Trigger_ICPolarity)
{
  /* Select the Polarity */
  MODIFY_REG(PCA->CCAPM2, PCA_CCAPM2_CAPP | PCA_CCAPM2_CAPN, PCA_Trigger_ICPolarity);
}

/**
  * @brief  Configures the Channel3 (PCA Input capture).
  * @param  PCA_Trigger_ICPolarity: The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg @ref PCA_Trigger_ICPOLARITY_NONE
  *         @arg @ref PCA_Trigger_ICPOLARITY_RISING
  *         @arg @ref PCA_Trigger_ICPOLARITY_FALLING
  *         @arg @ref PCA_Trigger_ICPOLARITY_BOTHEDGE
  * @retval None
  */
void PCA_IC3_TriggerConfig(uint32_t PCA_Trigger_ICPolarity)
{
  /* Select the Polarity */
  MODIFY_REG(PCA->CCAPM3, PCA_CCAPM3_CAPP | PCA_CCAPM3_CAPN, PCA_Trigger_ICPolarity);
}

/**
  * @brief  Configures the Channel4 (PCA Input capture).
  * @param  PCA_Trigger_ICPolarity: The Input Polarity.
  *         This parameter can be one of the following values:
  *         @arg @ref PCA_Trigger_ICPOLARITY_NONE
  *         @arg @ref PCA_Trigger_ICPOLARITY_RISING
  *         @arg @ref PCA_Trigger_ICPOLARITY_FALLING
  *         @arg @ref PCA_Trigger_ICPOLARITY_BOTHEDGE
  * @retval None
  */
void PCA_IC4_TriggerConfig(uint32_t PCA_Trigger_ICPolarity)
{
  /* Select the Polarity */
  MODIFY_REG(PCA->CCAPM4, PCA_CCAPM4_CAPP | PCA_CCAPM4_CAPN, PCA_Trigger_ICPolarity);
}

/**
  * @brief  Gets the PCA Capture Compare Register value on runtime
  * @param  Channel : PCA Channel associated with the capture compare register.
  *         This parameter can be one of the following values:
  *         @arg @ref PCA_CHANNEL_0: PCA Capture/Compare channel0
  *         @arg @ref PCA_CHANNEL_1: PCA Capture/Compare channel1
  *         @arg @ref PCA_CHANNEL_2: PCA Capture/Compare channel2
  *         @arg @ref PCA_CHANNEL_3: PCA Capture/Compare channel3
  *         @arg @ref PCA_CHANNEL_4: PCA Capture/Compare channel4
  * @retval 16-bit value of the capture/compare register (PCA_CCAPx)
  */
uint16_t PCA_GetCompareValue(uint32_t Channel)
{
  /* Check the parameters */
  assert_param(IS_PCA_CHANNEL(Channel));

  switch (Channel)
  {
    case PCA_CHANNEL_0:
      return PCA->CCAP0;
    case PCA_CHANNEL_1:
      return PCA->CCAP1;
    case PCA_CHANNEL_2:
      return PCA->CCAP2;
    case PCA_CHANNEL_3:
      return PCA->CCAP3;
    case PCA_CHANNEL_4:
      return PCA->CCAP4;
    default:
      return 0;
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
