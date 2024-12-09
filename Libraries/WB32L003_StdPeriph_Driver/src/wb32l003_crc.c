/**
 * @file    wb32l003_crc.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the CRC firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_crc.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC 
  * @brief CRC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup CRC_Private_Functions
  * @{
  */

/**
  * @brief  Initialize CRC caculation.
  * @retval None
  */
void CRC_InitResult(void)
{
  WRITE_REG(CRC->RESULT, CRC_RESULT_RESULT);
}

/**
  * @brief  DeInitializes the CRC peripheral.
  * @retval void
  */
void CRC_DeInit(void)
{
  /* Resets the CRC calculation unit */
  RCC_AHBPeriphResetCmd(RCC_AHBPeriph_CRC, ENABLE);
  RCC_AHBPeriphResetCmd(RCC_AHBPeriph_CRC, DISABLE);
}

/**
  * @brief  Computes the 16-bit CRC of 8-bit data buffer using combination
  *         of the previous CRC value and the new one.
  * @param  hcrc: pointer to a CRC_HandleTypeDef structure that contains
  *         the configuration information for CRC
  * @param  pBuffer: pointer to the buffer containing the data to be computed
  * @param  bufferLength: length of the buffer to be computed (defined in word, 4 bytes)
  * @retval 16-bit CRC
  */
uint32_t CRC_Accumulate(const uint8_t *pBuffer, uint32_t bufferLength)
{
  uint32_t index = 0U;
  
  /* Enter Data to the CRC calculator */
  for(index = 0U; index < bufferLength; index++)
  {
    *(uint8_t*)(CRC_DataAddress) = *pBuffer++;
  }
    
  /* Return the CRC computed value */
  return (CRC->RESULT & CRC_RESULT_RESULT_Msk);
}

/**
  * @brief  Computes the 16-bit CRC of 8-bit data buffer independently
  *         of the previous CRC value.
  * @param  pBuffer: Pointer to the buffer containing the data to be computed
  * @param  bufferLength: Length of the buffer to be computed (defined in word, 4 bytes)
  * @retval 16-bit CRC
  */
uint32_t CRC_Calculate(const uint8_t *pBuffer, uint32_t bufferLength)
{
  uint32_t index = 0U;

  /* Reset CRC Calculation Unit */
  RCC_AHBPeriphResetCmd(RCC_AHBPeriph_CRC, ENABLE);
  RCC_AHBPeriphResetCmd(RCC_AHBPeriph_CRC, DISABLE);

  CRC_InitResult();
  
  /* Enter Data to the CRC calculator */
  for(index = 0U; index < bufferLength; index++)
  {
    *(uint8_t*)(CRC_DataAddress) = *pBuffer++;
  }
  
  /* Return the CRC computed value */
  return (CRC->RESULT & CRC_RESULT_RESULT_Msk);
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
