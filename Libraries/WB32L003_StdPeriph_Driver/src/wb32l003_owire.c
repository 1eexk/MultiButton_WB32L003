/**
 * @file    wb32l003_owire.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the OWIRE firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_owire.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup OWIRE 
  * @brief OWIRE driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup OWIRE_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the OWIRE peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void OWIRE_DeInit(void)
{
  RCC_APBPeriphResetCmd(RCC_APBPeriph_OWIRE, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_OWIRE, DISABLE);
}

/**
  * @brief  Initializes the OWIRE mode according to the specified parameters in
  *         the OWIRE_InitTypeDef and create the associated handler.
  * @param  OWIRE_InitStruct: pointer to a OWIRE_InitTypeDef structure
  *         that contains the configuration information for the specified 
  *         OWIRE peripheral.
  * @retval None
  */
void OWIRE_Init(OWIRE_InitTypeDef *OWIRE_InitStruct)
{
  uint32_t apbclock, cnt;
  RCC_ClocksTypeDef RCC_ClocksStatus;

  RCC_GetClocksFreq(&RCC_ClocksStatus);
  apbclock = RCC_ClocksStatus.APBCLK_Frequency;
  cnt = (apbclock > 1000000) ? (apbclock / 1000000) : 1;

  /* Set the OWIRE Communication parameters */
  OWIRE->CR = (OWIRE_InitStruct->ClockDiv | OWIRE_InitStruct->DataSize | OWIRE_InitStruct->FirstBit | OWIRE_InitStruct->ReadMode);
  OWIRE->NFCR = (OWIRE_InitStruct->NoiseFilterClk | OWIRE_InitStruct->NoiseFilterEn);
  OWIRE->RSTCNT = OWIRE_InitStruct->ResetCounter * cnt;
  OWIRE->PRESCNT = OWIRE_InitStruct->PresencePulseCounter * cnt;
  OWIRE->BITRATECNT = OWIRE_InitStruct->BitRateCounter * cnt;
  OWIRE->DRVCNT = OWIRE_InitStruct->DriveCounter * cnt;
  OWIRE->RDSMPCNT = OWIRE_InitStruct->ReadSamplingCounter * cnt;
  OWIRE->RECCNT = OWIRE_InitStruct->RecoverCounter * cnt;
}

/**
  * @brief  Enables or disables the specified OWIRE peripheral.
  * @param  NewState: new state of the OWIRE peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OWIRE_Cmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the OWIRE peripheral */
    OWIRE->CR |= OWIRE_CR_EN_Msk;
  }
  else
  {
    /* Disable the OWIRE peripheral */
    OWIRE->CR &= ~(OWIRE_CR_EN_Msk);
  }
}

/**
  * @brief  Enables or disables the specified OWIRE interrupts.
  * @param  OWIRE_IT: specifies the OWIRE interrupts sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *         @arg @ref OWIRE_IT_ACKERROR: Slave answer error interrupt flag.
  *         @arg @ref OWIRE_IT_INITDONE: Initialization completion interrupt flag.
  *         @arg @ref OWIRE_IT_TXDONE: Send complete interrupt flag.
  *         @arg @ref OWIRE_IT_RXDONE: Receiving complete interrupt flag.
  * @param  NewState: new state of the OWIRE interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void OWIRE_ITConfig(uint32_t OWIRE_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    OWIRE->INTEN |= OWIRE_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    OWIRE->INTEN &= (uint32_t)~OWIRE_IT;
  }
}

/**
  * @brief  Read one data from DATA register.
  * @retval The read data.
  */
uint8_t OWIRE_ReadData(void)
{
  return (uint8_t)OWIRE->DATA;
}

/**
  * @brief  Write one data to DATA register.
  * @param  Data: The data to write.
  * @retval None
  */
void OWIRE_WriteData(uint8_t Data)
{
  OWIRE->DATA = Data;
}

/**
  * @brief  Write command to CMD register.
  * @param  Command: Specifies the command to write.
  *         This parameter can be one of the following values:
  *         @arg @ref OWIRE_COMMAND_INIT
  *         @arg @ref OWIRE_COMMAND_TX
  *         @arg @ref OWIRE_COMMAND_RX
  * @retval None
  */
void OWIRE_WriteCommand(uint8_t Command)
{
  OWIRE->CMD = Command;
}

/**
  * @brief  Checks whether the specified the OWIRE flag is set or not.
  * @param  OWIRE_FLAG: Specifies the OWIRE flag to check.
  *         This parameter can be one of the following values:
  *         @arg @ref OWIRE_FLAG_ACKERROR: Slave answer error flag.
  *         @arg @ref OWIRE_FLAG_INITDONE: Initialization completion flag.
  *         @arg @ref OWIRE_FLAG_TXDONE: Send complete flag.
  *         @arg @ref OWIRE_FLAG_RXDONE: Receiving complete flag.
  * @retval The new state of OWIRE_FLAG (SET or RESET).
  */
FlagStatus OWIRE_GetFlagStatus(uint32_t OWIRE_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the status of the specified OWIRE flag */
  if (OWIRE->SR & OWIRE_FLAG)
  {
    /* OWIRE_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* OWIRE_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the OWIRE_FLAG status */
  return bitstatus;
}

/**
  * @brief  Clears the OWIRE's pending flags.
  * @param  OWIRE_FLAG: specifies the flag bit to clear.
  *         This parameter can be any combination of the following values:
  *         @arg @ref OWIRE_FLAG_ACKERROR: Slave answer error flag.
  *         @arg @ref OWIRE_FLAG_INITDONE: Initialization completion flag.
  *         @arg @ref OWIRE_FLAG_TXDONE: Send complete flag.
  *         @arg @ref OWIRE_FLAG_RXDONE: Receiving complete flag.
  * @retval None
  */
void OWIRE_ClearFlag(uint32_t OWIRE_FLAG)
{
  /* Clear the flags */
  OWIRE->INTCLR = OWIRE_FLAG;
}

/**
  * @brief  Checks whether the OWIRE interrupt has occurred or not.
  * @param  OWIRE_IT: specifies the OWIRE interrupt source to check.
  *         This parameter can be one of the following values:
  *         @arg @ref OWIRE_IT_ACKERROR: Slave answer error interrupt flag.
  *         @arg @ref OWIRE_IT_INITDONE: Initialization completion interrupt flag.
  *         @arg @ref OWIRE_IT_TXDONE: Send complete interrupt flag.
  *         @arg @ref OWIRE_IT_RXDONE: Receiving complete interrupt flag.
  * @retval The new state of the OWIRE_IT(SET or RESET).
  */
ITStatus OWIRE_GetITStatus(uint32_t OWIRE_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t itstatus = 0x0, itenable = 0x0;

  itstatus = OWIRE->SR & OWIRE_IT;

  itenable = OWIRE->INTEN & OWIRE_IT;
  if ((itstatus != (uint32_t)RESET) && (itenable != (uint32_t)RESET))
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
  * @brief  Clears the OWIRE's interrupt pending bits.
  * @param  OWIRE_IT: Specifies the OWIRE's interrupt to clear.
  *         This parameter can be one of the following values:
  *         @arg @ref OWIRE_IT_ACKERROR: Slave answer error interrupt flag.
  *         @arg @ref OWIRE_IT_INITDONE: Initialization completion interrupt flag.
  *         @arg @ref OWIRE_IT_TXDONE: Send complete interrupt flag.
  *         @arg @ref OWIRE_IT_RXDONE: Receiving complete interrupt flag.
  * @retval None
  */
void OWIRE_ClearITPendingBit(uint32_t OWIRE_IT)
{
  OWIRE->INTCLR = OWIRE_IT;
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
