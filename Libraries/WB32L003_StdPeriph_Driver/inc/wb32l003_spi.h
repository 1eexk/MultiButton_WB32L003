/**
 * @file    wb32l003_spi.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the SPI firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_SPI_H
#define __WB32L003_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  SPI Init structure definition  
  */
typedef struct
{
  uint8_t SPI_TransferMode;
  uint8_t SPI_CPOL;
  uint8_t SPI_CPHA;
  uint8_t SPI_BaudRatePrescaler;
} SPI_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */

/** @defgroup SPI_Mode
  * @{
  */
#define SPI_MODE_SLAVE                      ((uint8_t)0x00U)
#define SPI_MODE_MASTER                     ((uint8_t)SPI_CR_MSTR)
/**
  * @}
  */


/** @defgroup SPI_Clock_Polarity 
  * @{
  */
#define SPI_CPOL_Low                        ((uint8_t)0x00U)
#define SPI_CPOL_High                       ((uint8_t)SPI_CR_CPOL)
/**
  * @}
  */


/** @defgroup SPI_Clock_Phase 
  * @{
  */
#define SPI_CPHA_1Edge                      ((uint8_t)0x00U)
#define SPI_CPHA_2Edge                      ((uint8_t)SPI_CR_CPHA)
/**
  * @}
  */


/** @defgroup SPI_NSS_management
  * @{
  */
#define SPI_NSS_MODE_HIGH                   ((uint8_t)SPI_SSN_SSN)
#define SPI_NSS_MODE_LOW                    ((uint8_t)0x00U)
/**
  * @}
  */


/** @defgroup SPI_BaudRate_Prescaler
  * @{
  */
#define SPI_BAUD_RATE_PRESCALER_2           ((uint8_t)0x00U)
#define SPI_BAUD_RATE_PRESCALER_4           ((uint8_t)SPI_CR_SPR0)
#define SPI_BAUD_RATE_PRESCALER_8           ((uint8_t)SPI_CR_SPR1)
#define SPI_BAUD_RATE_PRESCALER_16          ((uint8_t)(SPI_CR_SPR0 | SPI_CR_SPR1))
#define SPI_BAUD_RATE_PRESCALER_32          ((uint8_t)SPI_CR_SPR2)
#define SPI_BAUD_RATE_PRESCALER_64          ((uint8_t)(SPI_CR_SPR2 | SPI_CR_SPR0))
#define SPI_BAUD_RATE_PRESCALER_128         ((uint8_t)(SPI_CR_SPR2 | SPI_CR_SPR1))
/**
  * @}
  */


/** @defgroup SPI_Flags_definition
  * @{
  */
#define SPI_FLAG_SPIF                       ((uint8_t)SPI_SR_SPIF)  /* SPI status flag: Tx ok flag */
#define SPI_FLAG_WCOL                       ((uint8_t)SPI_SR_WCOL)  /* SPI status flag: write conflict  flag */
#define SPI_FLAG_SSERR                      ((uint8_t)SPI_SR_SSERR) /* SPI Error flag: Slave SSN flag */
#define SPI_FLAG_MDF                        ((uint8_t)SPI_SR_MDF)   /* SPI Error flag: Master Mode error flag */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define IS_SPI_MODE(MODE) (((MODE) == SPI_MODE_SLAVE) || \
                           ((MODE) == SPI_MODE_MASTER))

#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))

#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))

#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_MODE_HIGH) || \
                         ((NSS) == SPI_NSS_MODE_LOW))

#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BAUD_RATE_PRESCALER_2)  || \
                                              ((PRESCALER) == SPI_BAUD_RATE_PRESCALER_4)  || \
                                              ((PRESCALER) == SPI_BAUD_RATE_PRESCALER_8)  || \
                                              ((PRESCALER) == SPI_BAUD_RATE_PRESCALER_16) || \
                                              ((PRESCALER) == SPI_BAUD_RATE_PRESCALER_32) || \
                                              ((PRESCALER) == SPI_BAUD_RATE_PRESCALER_64) || \
                                              ((PRESCALER) == SPI_BAUD_RATE_PRESCALER_128))

#define IS_SPI_ALL_PERIPH(PERIPH) ((PERIPH) == SPI)

/* Exported functions --------------------------------------------------------*/

void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState);
void SPI_NSSConfig(SPI_TypeDef *SPIx, FunctionalState NewState);
uint8_t SPI_ReadData(SPI_TypeDef *SPIx);
void SPI_WriteData(SPI_TypeDef *SPIx, uint8_t Data);
FlagStatus SPI_GetFlagStatus(SPI_TypeDef *SPIx, uint8_t SPI_FLAG);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_SPI_H */
