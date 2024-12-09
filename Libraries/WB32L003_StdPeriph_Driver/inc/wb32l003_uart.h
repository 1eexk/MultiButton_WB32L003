/**
 * @file    wb32l003_uart.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the UART firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_UART_H
#define __WB32L003_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  UART Init Structure definition  
  */
typedef struct
{
  uint32_t UART_BandDouble;       /*!< Specifies doubled baudrate Enable or Disable
                                       This parameter can be a value of @ref UART_BandDouble */

  uint32_t UART_BaudRateMode;     /*!< Specifies the baud rate configuration source for the UART
                                       This parameter can be a value of @ref UART_BaudRate_Mode */

  uint32_t UART_BaudRate;         /*!< This member configures the UART communication baud rate. */

  uint8_t UART_WordLength;        /*!< Specifies the number of data bits transmitted or received in a frame.
                                       This parameter can be a value of @ref UART_Word_Length */
} UART_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup UART_Exported_Constants
  * @{
  */

#define IS_UART_ALL_PERIPH(PERIPH)   (((PERIPH) == UART1) || \
                                      ((PERIPH) == UART2))

/** @defgroup UART_Word_Length 
  * @{
  */
#define UART_WordLength_8b           ((uint32_t)(0x01U << 6))
#define UART_WordLength_9b           ((uint32_t)(0x03U << 6))
/**
  * @}
  */


/** @defgroup UART_BandDouble 
  * @{
  */
#define UART_BandDouble_Enable       ((uint32_t)UART_SCON_DBAUD)
#define UART_BandDouble_Disable      ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup UART_BaudRate_Mode 
  * @{
  */
#define UART_BaudRateMode_Self       ((uint32_t)UART_BAUDCR_SELF_BRG)
#define UART_BaudRateMode_Tim        ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup UART_Parity 
  * @{
  */
#define UART_Parity_None             ((uint32_t)0x00)
#define UART_Parity_Odd              ((uint32_t)0x01)
#define UART_Parity_Even             ((uint32_t)0x02)
/**
  * @}
  */


/** @defgroup UART_IT 
  * @{
  */
#define UART_IT_FE                   UART_SCON_FEEN
#define UART_IT_TI                   UART_SCON_TIEN
#define UART_IT_RI                   UART_SCON_RIEN
/**
  * @}
  */


/** @defgroup UART_Flags 
  * @{
  */
#define UART_FLAG_FE                 UART_INTSR_FE
#define UART_FLAG_TI                 UART_INTSR_TI
#define UART_FLAG_RI                 UART_INTSR_RI
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void UART_DeInit(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_WriteData(UART_TypeDef* UARTx, uint8_t Data);
uint8_t UART_ReadData(UART_TypeDef* UARTx);
void UART_MultideviceCmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_SetAddress(UART_TypeDef* UARTx, uint8_t UART_Address);
void UART_SetAddressMask(UART_TypeDef* UARTx, uint8_t UART_AddressMask);
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_ITConfig(UART_TypeDef* UARTx, uint8_t UART_IT, FunctionalState NewState);
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint32_t UART_FLAG);
void UART_ClearFlag(UART_TypeDef* UARTx, uint32_t UART_FLAG);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_UART_H */
