/**
 * @file    wb32l003_uart.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the UART firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_uart.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup UART
  * @brief UART driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup UART_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the UARTx peripheral registers to their default reset values.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @retval None
  */
void UART_DeInit(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  if (UARTx == UART1)
  {
    RCC_APBPeriphResetCmd(RCC_APBPeriph_UART1, ENABLE);
    RCC_APBPeriphResetCmd(RCC_APBPeriph_UART1, DISABLE);
  }
  else if (UARTx == UART2)
  {
    RCC_APBPeriphResetCmd(RCC_APBPeriph_UART2, ENABLE);
    RCC_APBPeriphResetCmd(RCC_APBPeriph_UART2, DISABLE);
  }
}

/**
  * @brief  Initializes the UARTx peripheral according to the specified
  *         parameters in the UART_InitStruct.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         that contains the configuration information for the specified 
  *         UART peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  uint32_t divider, apbclock, tmp;
  RCC_ClocksTypeDef RCC_ClocksStatus;

  RCC_GetClocksFreq(&RCC_ClocksStatus);
  apbclock = RCC_ClocksStatus.APBCLK_Frequency;

  tmp = UARTx->SCON;
  tmp &= (~(UART_SCON_DBAUD | UART_SCON_FEEN | UART_SCON_SM0_SM1 | UART_SCON_SM2));
  tmp |= UART_InitStruct->UART_BandDouble | UART_InitStruct->UART_WordLength;
  UARTx->SCON = tmp;

  if (UART_InitStruct->UART_BaudRateMode == UART_BaudRateMode_Self)
  {
    divider = (((UART_InitStruct->UART_BandDouble ? 1 : 0) + 1) * apbclock) / (32 * UART_InitStruct->UART_BaudRate) - 1;
    UARTx->BAUDCR = (divider |  UART_InitStruct->UART_BaudRateMode);
  }
}

/**
  * @brief  Fills each UART_InitStruct member with its default value.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
  /* UART_InitStruct members default value */
  UART_InitStruct->UART_BandDouble = UART_BandDouble_Enable;
  UART_InitStruct->UART_BaudRate = 115200;
  UART_InitStruct->UART_WordLength = UART_WordLength_8b;
  UART_InitStruct->UART_BaudRateMode = UART_BaudRateMode_Self;
}

/**
  * @brief  Enables or disables the specified UART peripheral.
  * @param  UARTx: Select the UART peripheral. 
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  NewState: new state of the UARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected UART by setting the EN bit in the SCON register */
    UARTx->SCON |= UART_SCON_REN;
  }
  else
  {
    /* Disable the selected UART by clearing the EN bit in the SCON register */
    UARTx->SCON &= (~UART_SCON_REN);
  }
}

/**
  * @brief  Write data to SBUF register.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  Data: the data to write.
  * @retval None
  */
void UART_WriteData(UART_TypeDef* UARTx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  UARTx->SBUF = Data & (0xFF);
}

/**
  * @brief  Read data from SBUF register.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @retval The received data
  */
uint8_t UART_ReadData(UART_TypeDef* UARTx)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  return (UARTx->SBUF & 0xFF);
}

/**
  * @brief  Enables or disables the UARTx's IrDA Mode.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  NewState: new state of the IrDA Mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  
  if (NewState != DISABLE) {
    UARTx->IRDACR |= UART_IRDACR_IREN_Msk;
  }
  else {
    UARTx->IRDACR &= ~UART_IRDACR_IREN_Msk;
  }
}

/**
  * @brief  Enables or disables the UARTx's interrupts.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
  *         This parameter can be a combination of the following values:
  *         @arg @ref UART_IT_FEFN
  *         @arg @ref UART_IT_TIEN
  *         @arg @ref UART_IT_RIEN
  * @param  NewState: new state of the interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ITConfig(UART_TypeDef* UARTx, uint8_t UART_IT, FunctionalState NewState)
{
  if (NewState != DISABLE) 
  {
    UARTx->SCON |= UART_IT;
  }
  else 
  {
    UARTx->SCON &= (~UART_IT);
  }
}

/**
  * @brief  Enables or disables the UARTx's Multidevice function.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  NewState: new state of the UART Multidevice function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_MultideviceCmd(UART_TypeDef* UARTx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  if (NewState != DISABLE) 
  {
    UARTx->SCON |= UART_SCON_SM2;
  }
  else 
  {
    UARTx->SCON &= (~UART_SCON_SM2);
  }
}

/**
  * @brief  Sets the address of the UART node.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  UART_Address: Indicates the address of the UART node.
  * @retval None
  */
void UART_SetAddress(UART_TypeDef* UARTx, uint8_t UART_Address)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
    
  /* Set the UART address node */
  UARTx->SADDR = UART_Address;
}

/**
  * @brief  Sets the address mask of the UART node.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  UART_AddressMask: Indicates the address mask of the UART node.
  * @retval None
  */
void UART_SetAddressMask(UART_TypeDef* UARTx, uint8_t UART_AddressMask)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
    
  /* Set the UART address node */
  UARTx->SADEN = UART_AddressMask;
}

/**
  * @brief  Checks whether the specified UART flag is set or not.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  UART_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *         @arg @ref UART_FLAG_FE: Busy flag.
  *         @arg @ref UART_FLAG_TI: Transmit FIFO Not Full flag.
  *         @arg @ref UART_FLAG_RI: Transmit FIFO Empty flag.
  * @retval The new state of UART_FLAG (SET or RESET).
  */
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint32_t UART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));

  FlagStatus bitstatus = RESET;

  if ((UARTx->INTSR & UART_FLAG) != (uint32_t)RESET)
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
  * @brief  Clear the specified UART flag.
  * @param  UARTx: Pointer to selected UART peripheral.
  *         This parameter can be one of the following values:
  *         UART1, UART2.
  * @param  UART_FLAG: specifies the flag to clear.
  *         This parameter can be one of the following values:
  *         @arg @ref UART_FLAG_FE: Busy flag.
  *         @arg @ref UART_FLAG_TI: Transmit FIFO Not Full flag.
  *         @arg @ref UART_FLAG_RI: Transmit FIFO Empty flag.
  * @retval The new state of UART_FLAG (SET or RESET).
  */
void UART_ClearFlag(UART_TypeDef* UARTx, uint32_t UART_FLAG)
{
  /* Check the parameters */
  assert_param(IS_UART_ALL_PERIPH(UARTx));
  
  UARTx->INTCLR |= UART_FLAG;
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
