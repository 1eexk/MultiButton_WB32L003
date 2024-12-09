/**
 * @file    wb32l003_lpuart.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the LPUART firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_lpuart.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup LPUART
  * @brief LPUART driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup LPUART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the LPUARTx peripheral registers to their default reset values.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
  * @retval None
  */
void LPUART_DeInit(LPUART_TypeDef* LPUARTx)
{
  if (LPUARTx == LPUART)
  {
    RCC_APBPeriphResetCmd(RCC_APBPeriph_LPUART, ENABLE);
    RCC_APBPeriphResetCmd(RCC_APBPeriph_LPUART, DISABLE);
  }
}

/**
  * @brief  Initializes the LPUARTx peripheral according to the specified
  *         parameters in the LPUART_InitStruct.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
  * @param  LPUART_InitStruct: pointer to a LPUART_InitTypeDef structure
  *         that contains the configuration information for the specified
  *         LPUART peripheral.
  * @retval None
  */
void LPUART_Init(LPUART_TypeDef* LPUARTx, LPUART_InitTypeDef* LPUART_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  uint32_t tmpScon, divider, sclkClock = 0;
  RCC_ClocksTypeDef RCC_ClocksStatus;

  RCC_GetClocksFreq(&RCC_ClocksStatus);

  tmpScon = LPUARTx->SCON;
  tmpScon &= 0x0;
  tmpScon |= LPUART_InitStruct->LPUART_ClkSel | LPUART_InitStruct->LPUART_WordLength;

  /* LPUART works normally  */
  if(LPUART_InitStruct->LPUART_LowPower == LPUART_LowPower_Disable)
  {
    tmpScon |= LPUART_InitStruct->LPUART_BandDouble;
    LPUARTx->SCON = tmpScon;

    if(LPUART_InitStruct->LPUART_ClkSel == LPUART_ClkSel_PCLK)
    {
      sclkClock = RCC_ClocksStatus.APBCLK_Frequency;
    }
    else if (LPUART_InitStruct->LPUART_ClkSel == LPUART_ClkSel_LSE)
    {
      sclkClock = 32768;
    }
    else if (LPUART_InitStruct->LPUART_ClkSel == LPUART_ClkSel_LSI)
    {
      sclkClock = 32768;
    }

    if (LPUART_InitStruct->LPUART_BaudRateMode == LPUART_BaudRateMode_Self)
    {
      divider = (((LPUART_InitStruct->LPUART_BandDouble ? 1 : 0) + 1) * sclkClock) / (32 * LPUART_InitStruct->LPUART_BaudRate) - 1;
      LPUARTx->BAUDCR = divider | LPUART_BAUDCR_SELF_BRG;
    }
  }
  else if (LPUART_InitStruct->LPUART_LowPower == LPUART_LowPower_Enable)
  {
    tmpScon |= (LPUART_InitStruct->LPUART_ClkDivision | LPUART_InitStruct->LPUART_LowPower);
    LPUARTx->SCON = tmpScon;
  }
}

/**
  * @brief  Fills each LPUART_InitStruct member with its default value.
  * @param  LPUART_InitStruct: pointer to a LPUART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void LPUART_StructInit(LPUART_InitTypeDef* LPUART_InitStruct)
{
  /* LPUART_InitStruct members default value */
  LPUART_InitStruct->LPUART_ClkSel = LPUART_ClkSel_PCLK;
  LPUART_InitStruct->LPUART_BandDouble = LPUART_BandDouble_Enable;
  LPUART_InitStruct->LPUART_BaudRateMode = LPUART_BaudRateMode_Self;
  LPUART_InitStruct->LPUART_BaudRate = 115200;
  LPUART_InitStruct->LPUART_LowPower = LPUART_LowPower_Disable;
  LPUART_InitStruct->LPUART_ClkDivision = LPUART_CLK_DIV1;
  LPUART_InitStruct->LPUART_WordLength = LPUART_WordLength_8b;
}

/**
  * @brief  Enables or disables the specified LPUART peripheral.
  * @param  LPUARTx: Select the LPUART peripheral.
  *         This parameter can be one of the following values: LPUART.
  * @param  NewState: new state of the LPUARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_Cmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  if (NewState != DISABLE)
  {
    /* Enable the selected LPUART by setting the EN bit in the SCON register */
    LPUARTx->SCON |= (LPUART_SCON_REN | LPUART_SCON_EN);
  }
  else
  {
    /* Disable the selected LPUART by clearing the EN bit in the SCON register */
    LPUARTx->SCON &= ~(LPUART_SCON_REN | LPUART_SCON_EN);
  }
}

/**
  * @brief  Write data to SBUF register.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
  *         This parameter can be one of the following values: LPUART.
  * @param  Data: the data to write.
  * @retval None
  */
void LPUART_WriteData(LPUART_TypeDef* LPUARTx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  LPUARTx->SBUF = (Data & 0xFF);
}

/**
  * @brief  Read data from SBUF register.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
  *         This parameter can be one of the following values: LPUART.
  * @retval The received data
  */
uint8_t LPUART_ReadData(LPUART_TypeDef* LPUARTx)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  return ((LPUARTx->SBUF) & 0xFF);
}

/**
  * @brief  Enables or disables the LPUARTx's interrupts.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
  *         This parameter can be one of the following values: LPUART.
  * @param  LPUART_IT: specifies the LPUART interrupt sources to be enabled or disabled.
  *         This parameter can be a combination of the following values:
  *         @arg @ref LPUART_IT_FE: LPUART receive error interrupt.
  *         @arg @ref LPUART_IT_TI: LPUART transmit complate interrupt.
  *         @arg @ref LPUART_IT_RI: LPUART receive complate interrupt.
  * @param  NewState: new state of the interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_ITConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  if (NewState != DISABLE)
  {
    LPUARTx->SCON |= LPUART_IT;
  }
  else
  {
    LPUARTx->SCON &= (~LPUART_IT);
  }
}

/**
  * @brief  Enables or disables the LPUARTx's Multidevice function.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
  *         This parameter can be one of the following values: LPUART.
  * @param  NewState: new state of the UART Multidevice function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void LPUART_MultideviceCmd(LPUART_TypeDef *LPUARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  if (NewState != DISABLE)
  {
    LPUARTx->SCON |= LPUART_SCON_SM2;
  }
  else
  {
    LPUARTx->SCON &= (~LPUART_SCON_SM2);
  }
}

/**
  * @brief  Sets the address of the LPUART node.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
 *          This parameter can be one of the following values: LPUART.
  * @param  LPUART_Address: Indicates the address of the LPUART node.
  * @retval None
  */
void LPUART_SetAddress(LPUART_TypeDef *LPUARTx, uint8_t LPUART_Address)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  /* Set the UART address node */
  LPUARTx->SADDR = LPUART_Address;
}

/**
  * @brief  Sets the address mask of the LPUART node.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
 *          This parameter can be one of the following values: LPUART.
  * @param  LPUART_AddressMask: Indicates the address mask of the LPUART node.
  * @retval None
  */
void LPUART_SetAddressMask(LPUART_TypeDef *LPUARTx, uint8_t LPUART_AddressMask)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  /* Set the UART address node */
  LPUARTx->SADEN = LPUART_AddressMask;
}

/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  LPUARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values: LPUART.
  * @param  UART_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *         @arg @ref LPUART_FLAG_FE: LPUART receive error interrupt flag.
  *         @arg @ref LPUART_FLAG_TI: LPUART transmit complate interrupt flag.
  *         @arg @ref LPUART_FLAG_RI: LPUART receive complate interrupt flag.
  * @retval The new state of LPUART_FLAG (SET or RESET).
  */
FlagStatus LPUART_GetFlagStatus(LPUART_TypeDef* LPUARTx, uint32_t LPUART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  FlagStatus bitstatus = RESET;

  if ((LPUARTx->INTSR & LPUART_FLAG) != (uint32_t)RESET)
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
  * @brief  Clear the specified LPUART flag.
  * @param  LPUARTx: Pointer to selected LPUART peripheral.
  *         This parameter can be one of the following values: LPUAERT.
  * @param  LPUART_FLAG: specifies the flag to clear.
  *         This parameter can be one of the following values:
  *         @arg @ref LPUART_FLAG_FE: LPUART receive error interrupt flag.
  *         @arg @ref LPUART_FLAG_TI: LPUART transmit complate interrupt flag.
  *         @arg @ref LPUART_FLAG_RI: LPUART receive complate interrupt flag.
  * @retval None.
  */
void LPUART_ClearFlag(LPUART_TypeDef* LPUARTx, uint32_t LPUART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_LPUART_ALL_PERIPH(LPUARTx));

  LPUARTx->INTCLR |= LPUART_FLAG;
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
