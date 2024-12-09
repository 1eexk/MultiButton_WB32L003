/**
 * @file    wb32l003_lpuart.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the LPUART firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_LPUART_H
#define __WB32L003_LPUART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup LPUART
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  LPUART Init Structure definition  
  */
typedef struct
{
  uint32_t LPUART_ClkSel;            /*!< Specifies the clock Source.
                                          This parameter can be a value of @ref LPUART_Clock_Source */

  uint32_t LPUART_BandDouble;        /*!< Specifies doubled baudrate Enable or Disable
                                          This parameter can be a value of @ref LPUART_BandDouble */

  uint32_t LPUART_BaudRateMode;      /*!< Specifies the baud rate configuration source for the LPUART
                                          This parameter can be a value of @ref LPUART_BaudRate_Mode */

  uint32_t LPUART_BaudRate;          /*!< This member configures the LPUART communication baud rate. */

  uint32_t LPUART_LowPower;          /*!< This member configures the LPUART LowPower mode Enable or Disable.
                                          This parameter can be a value of @ref LPUART_LowPower_Mode */

  uint32_t LPUART_ClkDivision;       /*!< Specifies the clock division.
                                          This parameter can be a value of @ref LPUART_Clock_Division */

  uint8_t LPUART_WordLength;         /*!< Specifies the number of data bits transmitted or received in a frame.
                                          This parameter can be a value of @ref LPUART_Word_Length */
} LPUART_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup LPUART_Exported_Constants
  * @{
  */

#define IS_LPUART_ALL_PERIPH(PERIPH)      (((PERIPH) == LPUART))

/** @defgroup LPUART_BandDouble 
  * @{
  */
#define LPUART_BandDouble_Enable          ((uint32_t)LPUART_SCON_DBAUD)
#define LPUART_BandDouble_Disable         ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup LPUART_BaudRate_Mode 
  * @{
  */
#define LPUART_BaudRateMode_Self          ((uint32_t)LPUART_BAUDCR_SELF_BRG)
#define LPUART_BaudRateMode_Tim           ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup LPUART_Word_Length 
  * @{
  */
#define LPUART_WordLength_8b              ((uint32_t)(0x01U << 6))
#define LPUART_WordLength_9b              ((uint32_t)(0x03U << 6))
/**
  * @}
  */


/** @defgroup LPUART_LowPower_Mode 
  * @{
  */
#define LPUART_LowPower_Enable            ((uint32_t)(0x01U << 10))
#define LPUART_LowPower_Disable           ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup LPUART_Clock_Source 
  * @{
  */
#define LPUART_ClkSel_PCLK                ((uint32_t)(0x01U << 11))
#define LPUART_ClkSel_LSE                 ((uint32_t)(0x02U << 11))
#define LPUART_ClkSel_LSI                 ((uint32_t)(0x03U << 11))
/**
  * @}
  */


 /** @defgroup LPUART_Clock_Division
  * @{
  */
#define LPUART_CLK_DIV1                   ((uint32_t)(0x07U << 13))
#define LPUART_CLK_DIV2                   ((uint32_t)(0x06U << 13))
#define LPUART_CLK_DIV4                   ((uint32_t)(0x05U << 13))
#define LPUART_CLK_DIV8                   ((uint32_t)(0x04U << 13))
#define LPUART_CLK_DIV16                  ((uint32_t)(0x03U << 13))
#define LPUART_CLK_DIV32                  ((uint32_t)(0x02U << 13))
#define LPUART_CLK_DIV64                  ((uint32_t)(0x01U << 13))
#define LPUART_CLK_DIV128                 ((uint32_t)(0x00U << 13))
/**
  * @}
  */


/** @defgroup LPUART_Parity 
  * @{
  */
#define LPUART_Parity_None                ((uint32_t)0x00)
#define LPUART_Parity_Odd                 ((uint32_t)0x01)
#define LPUART_Parity_Even                ((uint32_t)0x02)
/**
  * @}
  */


/** @defgroup LPUART_IT 
  * @{
  */
#define LPUART_IT_FE                      LPUART_SCON_FEEN
#define LPUART_IT_TI                      LPUART_SCON_TIEN
#define LPUART_IT_RI                      LPUART_SCON_RIEN
/**
  * @}
  */


/** @defgroup LPUART_Flags 
  * @{
  */
#define LPUART_FLAG_FE                    LPUART_INTSR_FE
#define LPUART_FLAG_TI                    LPUART_INTSR_TI
#define LPUART_FLAG_RI                    LPUART_INTSR_RI
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void LPUART_DeInit(LPUART_TypeDef* LPUARTx);
void LPUART_Init(LPUART_TypeDef* LPUARTx, LPUART_InitTypeDef* LPUART_InitStruct);
void LPUART_StructInit(LPUART_InitTypeDef* LPUART_InitStruct);
void LPUART_Cmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);
void LPUART_WriteData(LPUART_TypeDef* LPUARTx, uint8_t Data);
uint8_t LPUART_ReadData(LPUART_TypeDef* LPUARTx);
void LPUART_MultideviceCmd(LPUART_TypeDef* LPUARTx, FunctionalState NewState);
void LPUART_SetAddress(LPUART_TypeDef* LPUARTx, uint8_t LPUART_Address);
void LPUART_SetAddressMask(LPUART_TypeDef* LPUARTx, uint8_t LPUART_AddressMask);
void LPUART_ITConfig(LPUART_TypeDef* LPUARTx, uint32_t LPUART_IT, FunctionalState NewState);
FlagStatus LPUART_GetFlagStatus(LPUART_TypeDef* LPUARTx, uint32_t LPUART_FLAG);
void LPUART_ClearFlag(LPUART_TypeDef* LPUARTx, uint32_t LPUART_FLAG);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_LPUART_H */
