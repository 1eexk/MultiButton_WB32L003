/**
 * @file    wb32l003_spi.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the SPI firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_spi.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup SPI 
  * @brief SPI driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SPI_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the SPIx peripheral registers to their default reset values.
  * @param  SPIx: Pointer to selected SPI peripheral.
  *         This parameter can be one of the following values:
  *         SPI.
  * @retval None
  */
void SPI_DeInit(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if (SPIx == SPI)
  {
    RCC_APBPeriphResetCmd(RCC_APBPeriph_SPI, ENABLE);
    RCC_APBPeriphResetCmd(RCC_APBPeriph_SPI, DISABLE);
  }
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *         parameters in the SPI_InitStruct.
  * @param  SPIx: Pointer to selected SPI peripheral.
  *         This parameter can be one of the following values:
  *         SPI.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure
  *         that contains the configuration information for the specified 
  *         SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_TransferMode));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));

  SPIx->CR = SPI_InitStruct->SPI_TransferMode |
             SPI_InitStruct->SPI_CPOL |
             SPI_InitStruct->SPI_CPHA |
             SPI_InitStruct->SPI_BaudRatePrescaler;
}

/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: Pointer to selected SPI peripheral.
  *         This parameter can be one of the following values:
  *         SPI.
  * @param  NewState: new state of the SPIx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    SPIx->CR |= SPI_CR_SPEN;
  }
  else
  {
    SPIx->CR &= ~SPI_CR_SPEN;
  }
}

/**
  * @brief  Enables or disables the specified slave select line.
  * @param  SPIx: Pointer to selected SPI peripheral.
  *         This parameter can be one of the following values:
  *         SPI.
  * @param  NewState: new state of the slave select line.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_NSSConfig(SPI_TypeDef *SPIx, FunctionalState NewState)
{
  if (NewState != DISABLE) {
    SPIx->SSN &= ~SPI_SSN_SSN;
  }
  else {
    SPIx->SSN |= SPI_SSN_SSN;
  }
}

/**
  * @brief  Read one data from DATA register.
  * @param  SPIx: Pointer to selected SPI peripheral.
  *         This parameter can be one of the following values:
  *         SPI.
  * @retval The read data.
  */
uint8_t SPI_ReadData(SPI_TypeDef *SPIx)
{
  return SPIx->DATA;
}

/**
  * @brief  Write one data to DATA register.
  * @param  SPIx: Pointer to selected SPI peripheral.
  *         This parameter can be one of the following values:
  *         SPI.
  * @param  Data: The data to write.
  * @retval None
  */
void SPI_WriteData(SPI_TypeDef *SPIx, uint8_t Data)
{
  SPIx->DATA = Data;
}

/**
  * @brief  Checks whether the specified SPIx flag is set or not.
  * @param  SPIx: Pointer to selected SPI peripheral.
  *         This parameter can be one of the following values:
  *         SPI.
  * @param  SPI_FLAG: specifies the SPI flag to check.
  *         This parameter can be one of the following values:
  *         @arg @ref SPI_FLAG_SPIF: End of transmission flag.
  *         @arg @ref SPI_FLAG_WCOL: Write conflict flag.
  *         @arg @ref SPI_FLAG_SSERR: Slave mode SSN error flag.
  *         @arg @ref SPI_FLAG_MDF: Host mode error flag.
  * @retval The new state of SPI_FLAG (SET or RESET).
  */
FlagStatus SPI_GetFlagStatus(SPI_TypeDef *SPIx, uint8_t SPI_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the status of the specified SPI flag */
  if (SPIx->SR & SPI_FLAG)
  {
    /* SPI_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_FLAG status */
  return  bitstatus;
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
