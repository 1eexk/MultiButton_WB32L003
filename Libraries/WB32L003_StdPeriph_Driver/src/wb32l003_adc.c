/**
 * @file    wb32l003_adc.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the ADC firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_adc.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC 
  * @brief ADC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup ADC_Private_Defines
  * @{
  */

#define CR0_CONFIG_CLEAR_Msk              (ADC_CR0_SAM_Msk | ADC_CR0_SEL_Msk | ADC_CR0_CLKSEL_Msk)
#define CR1_CONFIG_CLEAR_Msk              (ADC_CR1_RACC_EN_Msk | ADC_CR1_TRIGS0_Msk | ADC_CR1_TRIGS1_Msk)
#define CR2_CONFIG_CLEAR_Msk              (ADC_CR2_CIRCLE_MODE_Msk | ADC_CR2_ADCCNT_Msk | ADC_CR2_CHEN_Msk)

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ADC_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the ADC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void ADC_DeInit(void)
{
  RCC_APBPeriphResetCmd(RCC_APBPeriph_ADC, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_ADC, DISABLE);
}

/**
  * @brief  Initializes the ADC peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct)
{
  uint32_t tmpreg0 = 0;
  uint32_t tmpreg1 = 0;
  uint32_t tmpreg2 = 0;

  /* Check the parameters */
  assert_param(IS_ADC_SAMPLE_CYCLE(ADC_InitStruct->ADC_SamplingTime));
  assert_param(IS_ADC_CLOCK_PCLK_DIV(ADC_InitStruct->ADC_ClkSel));
  assert_param(IS_ADC_SINGLEMODE(ADC_InitStruct->ADC_SingleContinueMode));
  assert_param(IS_ADC_ACCMULATION(ADC_InitStruct->ADC_AutoAccumulation));
  assert_param(IS_ADC_CIRCLEMODE(ADC_InitStruct->ADC_CircleMode));
  assert_param(IS_ADC_EXTRIG1(ADC_InitStruct->ADC_ExternalTrigConv1));
  assert_param(IS_ADC_EXTRIG2(ADC_InitStruct->ADC_ExternalTrigConv2));

  /*  - Clear ADC configuration  */
  ADC->CR0 &= ~CR0_CONFIG_CLEAR_Msk;
  ADC->CR1 &= ~CR1_CONFIG_CLEAR_Msk;
  ADC->CR2 &= ~CR2_CONFIG_CLEAR_Msk;

  /* Configuration of ADC */
  tmpreg0 |= ((ADC_InitStruct->ADC_SamplingTime) | (ADC_InitStruct->ADC_ClkSel));
  /* Continuous conversion or Single conversion selection */
  tmpreg1 |= ADC_InitStruct->ADC_SingleContinueMode;
  if (ADC_InitStruct->ADC_CircleMode == ADC_MULTICHANNEL_NONCIRCLE)
  {
    if (ADC_InitStruct->ADC_SingleContinueMode == ADC_MODE_SINGLE)
    {
      assert_param(IS_ADC_SINGLE_CHANNEL(ADC_InitStruct->ADC_SingleChannelSel));
      /* Set ADC single channel */
      tmpreg0 |= ADC_InitStruct->ADC_SingleChannelSel;
    }
    else if (ADC_InitStruct->ADC_SingleContinueMode == ADC_MODE_CONTINUE)
    {
      assert_param(IS_ADC_CONTINUE_CHANNEL(ADC_InitStruct->ADC_ContinueChannelSel));
      /* Set ADC continue channels and the all conversion numbers of these channels */
      tmpreg2 |= (((ADC_InitStruct->ADC_ConversionTimes - 1) << 8) | ADC_InitStruct->ADC_ContinueChannelSel);
    }
  }
  else
  {
    /* ADC circle mode selection, only useful for the continue channels */
    tmpreg2 |= ((ADC_InitStruct->ADC_CircleMode) | (ADC_InitStruct->ADC_ContinueChannelSel));
  }

  /* Auto accumulation enable or disable*/
  tmpreg1 |= ADC_InitStruct->ADC_AutoAccumulation;

  /* Software trigger conversion or external interrupt trigger*/
  tmpreg1 |= (ADC_InitStruct->ADC_ExternalTrigConv1 | ADC_InitStruct->ADC_ExternalTrigConv2);

  /* Update the configuration register */
  ADC->CR0 = tmpreg0;
  ADC->CR1 = tmpreg1;
  ADC->CR2 = tmpreg2;
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @param  ADC_InitStruct : pointer to an ADC_InitTypeDef structure which will be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */
  ADC_InitStruct->ADC_SamplingTime = ADC_SAMPLE_4CYCLE;

  ADC_InitStruct->ADC_SingleChannelSel = ADC_SINGLE_CHANNEL_0;

  ADC_InitStruct->ADC_ClkSel = ADC_CLOCK_PCLK_DIV1;

  ADC_InitStruct->ADC_SingleContinueMode = ADC_MODE_SINGLE;

  ADC_InitStruct->ADC_AutoAccumulation = ADC_AUTOACC_DISABLE;

  ADC_InitStruct->ADC_CircleMode = ADC_MULTICHANNEL_NONCIRCLE;

  ADC_InitStruct->ADC_ContinueChannelSel = ADC_CONTINUE_CHANNEL_0;

  ADC_InitStruct->ADC_ExternalTrigConv1 = ADC_SOFTWARE_START;

  ADC_InitStruct->ADC_ExternalTrigConv2 = ADC_SOFTWARE_START;
}

/**
  * @brief  Enables or disables the ADC peripheral.
  * @param  NewState: The new state of the ADC peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the  ADC peripheral */
    ADC->CR0 |= ADC_CR0_ADCEN_Msk;
  }
  else
  {
    /* Disable the  ADC peripheral */
    ADC->CR0 &= ~ADC_CR0_ADCEN_Msk;
  }
}

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled. 
  *         This parameter can be any combination of the following values:
  *         @arg @ref ADC_IT_CONTINUE: ADC End of Continue Conversion interrupt
  *         @arg @ref ADC_IT_RANGE_THRESHOLD: ADC conversion data in defined range interrupt
  *         @arg @ref ADC_IT_HIGH_THRESHOLD: ADC conversion data above threshold interrupt
  *         @arg @ref ADC_IT_LOW_THRESHOLD: ADC conversion data below threshold interrupt
  *         @arg @ref ADC_IT_CHANNEL15: ADC End of channel 15 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL14: ADC End of channel 14 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL13: ADC End of channel 13 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL12: ADC End of channel 12 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL11: ADC End of channel 11 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL10: ADC End of channel 10 conversion interrupt 
  *         @arg @ref ADC_IT_CHANNEL9: ADC End of channel 9 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL8: ADC End of channel 8 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL7: ADC End of channel 7 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL6: ADC End of channel 6 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL5: ADC End of channel 5 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL4: ADC End of channel 4 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL3: ADC End of channel 3 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL2: ADC End of channel 2 conversion interrupt 
  *         @arg @ref ADC_IT_CHANNEL1: ADC End of channel 1 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL0: ADC End of channel 0 conversion interrupt
  * @param  NewState: The new state of the specified ADC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(uint32_t ADC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_IT(ADC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADC->INTEN |= ADC_IT;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADC->INTEN &= ~ADC_IT;
  }
}

/**
  * @brief  Enables or disables the selected ADC software start conversion.
  * @param  NewState: The new state of the selected ADC software start conversion.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_SoftwareStartConvCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Start ADC conversion by software */
    ADC->CR0 |= ADC_CR0_START;
  }
  else
  {
    /* Stop ADC conversion by software */
    ADC->CR0 &= ~ADC_CR0_START;
  }
}

/**
  * @brief  Gets the selected ADC Software start conversion Status.
  * @param  None
  * @retval The new state of ADC software start conversion (SET or RESET).
  */
FlagStatus ADC_GetSoftwareStartConvStatus(void)
{
  FlagStatus bitstatus = RESET;
  /* Check the status of SWSTART bit */
  if ((ADC->CR0 & ADC_CR0_START) != (uint32_t)RESET)
  {
    /* SWSTART bit is set */
    bitstatus = SET;
  }
  else
  {
    /* SWSTART bit is reset */
    bitstatus = RESET;
  }
  /* Return the SWSTART bit status */
  return bitstatus;
}

/**
  * @brief  Returns the last ADC conversion result data for regular channel.
  * @param  Channel: Selected channel to get ADC conversion value.
  *         This parameter can be one of the following values:
  *         @arg @ref ADC_SINGLE_CHANNEL_0: ADC channel 0 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_1: ADC channel 1 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_2: ADC channel 2 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_3: ADC channel 3 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_4: ADC channel 4 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_5: ADC channel 5 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_6: ADC channel 6 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_7: ADC channel 7 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_8: ADC channel 8 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_9: ADC channel 9 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_10: ADC channel 10 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_11: ADC channel 11 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_12: ADC channel 12 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_13: ADC channel 13 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_14: ADC channel 14 in single mode
  *         @arg @ref ADC_SINGLE_CHANNEL_15: ADC channel 15 in single mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_0: ADC channel 0 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_1: ADC channel 1 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_2: ADC channel 2 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_3: ADC channel 3 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_4: ADC channel 4 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_5: ADC channel 5 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_6: ADC channel 6 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_7: ADC channel 7 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_8: ADC channel 8 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_9: ADC channel 9 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_10: ADC channel 10 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_11: ADC channel 11 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_12: ADC channel 12 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_13: ADC channel 13 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_14: ADC channel 14 in continue mode
  *         @arg @ref ADC_CONTINUE_CHANNEL_15: ADC channel 15 in continue mode
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(uint32_t Channel)
{
  uint16_t tmpADCvalue = 0;
  /* Check the parameters */
  assert_param(IS_ADC_CHANNEL(Channel));

  /* Return the selected ADC conversion value */
  if ((ADC->CR1 & ADC_CR1_CT_Msk) == RESET)
  {
    /* If ADC is set to single mode */
    tmpADCvalue = ADC->RESULT;
  }
  else
  {
    /* Return ADC converted value */
    switch (Channel)
    {
      case ADC_CONTINUE_CHANNEL_0:
        tmpADCvalue = ADC->RESULT0;
        break;
      case ADC_CONTINUE_CHANNEL_1:
        tmpADCvalue = ADC->RESULT1;
        break;
      case ADC_CONTINUE_CHANNEL_2:
        tmpADCvalue = ADC->RESULT2;
        break;
      case ADC_CONTINUE_CHANNEL_3:
        tmpADCvalue = ADC->RESULT3;
        break;
      case ADC_CONTINUE_CHANNEL_4:
        tmpADCvalue = ADC->RESULT4;
        break;
      case ADC_CONTINUE_CHANNEL_5:
        tmpADCvalue = ADC->RESULT5;
        break;
      case ADC_CONTINUE_CHANNEL_6:
        tmpADCvalue = ADC->RESULT6;
        break;
      case ADC_CONTINUE_CHANNEL_7:
        tmpADCvalue = ADC->RESULT7;
        break;
      case ADC_CONTINUE_CHANNEL_8:
        tmpADCvalue = ADC->RESULT8;
        break;
      case ADC_CONTINUE_CHANNEL_9:
        tmpADCvalue = ADC->RESULT9;
        break;
      case ADC_CONTINUE_CHANNEL_10:
        tmpADCvalue = ADC->RESULT10;
        break;
      case ADC_CONTINUE_CHANNEL_11:
        tmpADCvalue = ADC->RESULT11;
        break;
      case ADC_CONTINUE_CHANNEL_12:
        tmpADCvalue = ADC->RESULT12;
        break;
      case ADC_CONTINUE_CHANNEL_13:
        tmpADCvalue = ADC->RESULT13;
        break;
      case ADC_CONTINUE_CHANNEL_14:
        tmpADCvalue = ADC->RESULT14;
        break;
      case ADC_CONTINUE_CHANNEL_15:
        tmpADCvalue = ADC->RESULT15;
        break;
      default:
        tmpADCvalue = 0;
        break;
    }
  }
  return tmpADCvalue;
}

/**
  * @brief  Gets ADC accumulation conversion result.
  * @note   This function is only valid when RACC_EN is set. 
  * @param  None
  * @retval ADC accumulation conversion data
  */
uint32_t ADC_GetAccValue(void)
{
  uint32_t tmpADCvalue;

  tmpADCvalue = ADC->RESULT_ACC;

  return tmpADCvalue;
}

/**
  * @brief  Checks whether the specified ADC interrupt is set or not.
  * @param  ADC_IT: specifies the ADC interrupt sources to check.
  *         This parameter can be any combination of the following values:
  *         @arg @ref ADC_IT_CONTINUE: ADC End of Continue Conversion interrupt
  *         @arg @ref ADC_IT_RANGE_THRESHOLD: ADC conversion data in defined range interrupt
  *         @arg @ref ADC_IT_HIGH_THRESHOLD: ADC conversion data above threshold interrupt
  *         @arg @ref ADC_IT_LOW_THRESHOLD: ADC conversion data below threshold interrupt
  *         @arg @ref ADC_IT_CHANNEL15: ADC End of channel 15 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL14: ADC End of channel 14 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL13: ADC End of channel 13 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL12: ADC End of channel 12 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL11: ADC End of channel 11 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL10: ADC End of channel 10 conversion interrupt 
  *         @arg @ref ADC_IT_CHANNEL9: ADC End of channel 9 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL8: ADC End of channel 8 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL7: ADC End of channel 7 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL6: ADC End of channel 6 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL5: ADC End of channel 5 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL4: ADC End of channel 4 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL3: ADC End of channel 3 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL2: ADC End of channel 2 conversion interrupt 
  *         @arg @ref ADC_IT_CHANNEL1: ADC End of channel 1 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL0: ADC End of channel 0 conversion interrupt
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
ITStatus ADC_GetITStatus(uint16_t ADC_IT)
{
  ITStatus bitstatus = RESET;
  uint16_t itstatus = 0;
  uint16_t itenable = 0;
  
  /* Check the parameters */
  assert_param(IS_ADC_IT(ADC_IT));

  /* Check the status of the specified ADC intrrupt */
  itstatus = ADC->MSKINTSR & ADC_IT;
  itenable = ADC->INTEN & ADC_IT;

  if ((itenable & itstatus) != (uint16_t)RESET)
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
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADC_FLAG: specifies the flag to check. 
  *         This parameter can be any combination of the following values:
  *         @arg @ref ADC_INTFLAG：ADC End of Continue Conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_RANGE_THRESHOLD：ADC conversion data in defined range interrupt flag 
  *         @arg @ref ADC_INTFLAG_HIGH_THRESHOLD：ADC conversion data above threshold interrupt flag 
  *         @arg @ref ADC_INTFLAG_LOW_THERSHOLD：ADC conversion data below threshold interrupt flag 
  *         @arg @ref ADC_INTFLAG_CHANNEL15: ADC End of channel 15 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL14: ADC End of channel 14 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL13: ADC End of channel 13 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL12: ADC End of channel 12 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL11: ADC End of channel 11 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL10: ADC End of channel 10 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL9: ADC End of channel 9 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL8: ADC End of channel 8 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL7：ADC End of channel7 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL6：ADC End of channel6 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL5：ADC End of channel5 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL4：ADC End of channel4 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL3：ADC End of channel3 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL2：ADC End of channel2 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL1：ADC End of channel1 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL0：ADC End of channel0 conversion interrupt flag
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(uint16_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_INTFLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADC->MSKINTSR & ADC_FLAG) != (uint16_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return bitstatus;
}

/**
  * @brief  Clears the ADC pending interrupt bits.
  * @param  ADC_IT: specifies the ADC interrupt sources to clear. 
  *         This parameter can be any combination of the following values:
  *         @arg @ref ADC_IT_CONTINUE: ADC End of Continue Conversion interrupt
  *         @arg @ref ADC_IT_RANGE_THRESHOLD: ADC conversion data in defined range interrupt
  *         @arg @ref ADC_IT_HIGH_THRESHOLD: ADC conversion data above threshold interrupt
  *         @arg @ref ADC_IT_LOW_THRESHOLD: ADC conversion data below threshold interrupt
  *         @arg @ref ADC_IT_CHANNEL15: ADC End of channel 15 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL14: ADC End of channel 14 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL13: ADC End of channel 13 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL12: ADC End of channel 12 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL11: ADC End of channel 11 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL10: ADC End of channel 10 conversion interrupt 
  *         @arg @ref ADC_IT_CHANNEL9: ADC End of channel 9 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL8: ADC End of channel 8 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL7: ADC End of channel 7 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL6: ADC End of channel 6 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL5: ADC End of channel 5 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL4: ADC End of channel 4 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL3: ADC End of channel 3 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL2: ADC End of channel 2 conversion interrupt 
  *         @arg @ref ADC_IT_CHANNEL1: ADC End of channel 1 conversion interrupt
  *         @arg @ref ADC_IT_CHANNEL0: ADC End of channel 0 conversion interrupt
  * @retval None
  */
void ADC_ClearITPendingBit(uint16_t ADC_IT)
{
  /* Check the parameters */
  assert_param(IS_ADC_IT(ADC_IT));

  /* Clear the selected ADC interrupts */
  ADC->INTCLR |= (uint16_t)ADC_IT;
}

/**
  * @brief  Clears the ADC pending interrupt flags.
  * @param  ADC_FLAG: specifies the flag to clear. 
  *         This parameter can be one of the following values:
  *         @arg @ref ADC_INTFLAG： ADC End of Continue Conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_RANGE_THRESHOLD：ADC conversion data in defined range interrupt flag 
  *         @arg @ref ADC_INTFLAG_HIGH_THRESHOLD：ADC conversion data above threshold interrupt flag 
  *         @arg @ref ADC_INTFLAG_LOW_THERSHOLD：ADC conversion data below threshold interrupt flag 
  *         @arg @ref ADC_INTFLAG_CHANNEL15: ADC End of channel 15 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL14: ADC End of channel 14 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL13: ADC End of channel 13 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL12: ADC End of channel 12 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL11: ADC End of channel 11 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL10: ADC End of channel 10 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL9: ADC End of channel 9 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL8: ADC End of channel 8 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL7：ADC End of channel7 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL6：ADC End of channel6 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL5：ADC End of channel5 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL4：ADC End of channel4 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL3：ADC End of channel3 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL2：ADC End of channel2 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL1：ADC End of channel1 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL0：ADC End of channel0 conversion interrupt flag
  * @retval None
  */
void ADC_ClearFlag(uint16_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_INTFLAG(ADC_FLAG));

  /* Clear the selected ADC flags */
  ADC->INTCLR |= (uint16_t)ADC_FLAG;
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADC_FLAG: specifies the flag to check. 
  *         This parameter can be any combination of the following values:
  *         @arg @ref ADC_INTFLAG： ADC End of Continue Conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_RANGE_THRESHOLD：ADC conversion data in defined range interrupt flag 
  *         @arg @ref ADC_INTFLAG_HIGH_THRESHOLD：ADC conversion data above threshold interrupt flag 
  *         @arg @ref ADC_INTFLAG_LOW_THERSHOLD：ADC conversion data below threshold interrupt flag 
  *         @arg @ref ADC_INTFLAG_CHANNEL15: ADC End of channel 15 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL14: ADC End of channel 14 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL13: ADC End of channel 13 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL12: ADC End of channel 12 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL11: ADC End of channel 11 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL10: ADC End of channel 10 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL9: ADC End of channel 9 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL8: ADC End of channel 8 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL7：ADC End of channel7 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL6：ADC End of channel6 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL5：ADC End of channel5 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL4：ADC End of channel4 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL3：ADC End of channel3 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL2：ADC End of channel2 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL1：ADC End of channel1 conversion interrupt flag
  *         @arg @ref ADC_INTFLAG_CHANNEL0：ADC End of channel0 conversion interrupt flag
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetRawFlagStatus(uint16_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_ADC_RAWINTFLAG(ADC_FLAG));

  /* Check the status of the specified ADC flag */
  if ((ADC->RAWINTSR & ADC_FLAG) != (uint16_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return bitstatus;
}

/**
  * @brief  Configures the high and low thresholds of the analog watchdog.
  * @param  LowThreshold: the ADC analog watchdog Low threshold value.
  *         This parameter must be a 12bit value.
  * @param  HighThreshold: the ADC analog watchdog High threshold value.
  *         This parameter must be a 12bit value.
  * @retval None
  */
void ADC_ThresholdsConfig(uint16_t LowThreshold, uint16_t HighThreshold)
{
  /* Set the ADC high threshold */
  ADC->HT = HighThreshold;
  /* Set the ADC low threshold */
  ADC->LT = LowThreshold;
}

/**
  * @brief  Enables or disables the thresholds to compare with the function of analog watchdog.
  * @param  Threshold_Config: the ADC analog watchdog threshold configuration.
  *         This parameter can be any combination of the following values:
  *         @arg @ref ADC_High_Threshold_Compare: ADC high threshold compare
  *         @arg @ref ADC_Low_Threshold_Compare: ADC low threshold compare
  *         @arg @ref ADC_Range_Threshold_Compare: ADC range threshold compare 
  * @param  NewState: The new state of the selected ADC software starts conversion.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ThresholdsCompareCmd(uint16_t Threshold_Config, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    ADC->CR1 |= Threshold_Config;
  }
  else
  {
    ADC->CR1 &= ~Threshold_Config;
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
