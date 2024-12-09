/**
 * @file    wb32l003_beep.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the BEEP firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_BEEP_H
#define __WB32L003_BEEP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup BEEP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  BEEP Init structure definition  
  */
typedef struct
{  
  uint32_t BEEP_ClkSel;           /*!< Specifies beep clock.
                                       This parameter can be a value of @ref BEEP_ClkSel */
  
  uint32_t BEEP_Prescaler;        /*!< Specifies beep clock output divider.
                                       This parameter can be a value between 0 to 0xFFF */
  
  uint32_t BEEP_OutDiv;           /*!< Specifies beep clock frequency select.
                                       This parameter can be a value of @ref BEEP_OutDiv */
  
} BEEP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup BEEP_Exported_Constants
  * @{
  */

#define IS_BEEP_ALL_PERIPH(PERIPH)   (((PERIPH) == BEEP))

/** @defgroup BEEP_ClkSel
  * @{
  */
#define BEEP_ClkSel_STOP             ((uint32_t)(0x00U << BEEP_CSR_CLKSEL_Pos))
#define BEEP_ClkSel_LSI              ((uint32_t)(0x01U << BEEP_CSR_CLKSEL_Pos))
#define BEEP_ClkSel_HSE              ((uint32_t)(0x02U << BEEP_CSR_CLKSEL_Pos))
#define BEEP_ClkSel_PCLK             ((uint32_t)(0x03U << BEEP_CSR_CLKSEL_Pos))
/**
  * @}
  */


/** @defgroup BEEP_OutDiv 
  * @{
  */
#define BEEP_OutDiv8                 ((uint32_t)(0x00U << BEEP_CSR_BEEPSEL_Pos))
#define BEEP_OutDiv4                 ((uint32_t)(0x01U << BEEP_CSR_BEEPSEL_Pos))
#define BEEP_OutDiv2                 ((uint32_t)(0x02U << BEEP_CSR_BEEPSEL_Pos))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define IS_BEEP_CLK_SEL(SEL)         (((SEL) == BEEP_ClkSel_STOP) || \
                                      ((SEL) == BEEP_ClkSel_LSI) || \
                                      ((SEL) == BEEP_ClkSel_HSE) || \
                                      ((SEL) == BEEP_ClkSel_PCLK))

#define IS_BEEP_PRESCALER(PRESCALER) ((PRESCALER) < 4096)

#define IS_BEEP_OUT_DIV(DIV)         (((DIV) == BEEP_OutDiv2) || \
                                      ((DIV) == BEEP_OutDiv4) || \
                                      ((DIV) == BEEP_OutDiv8))

/* Exported functions --------------------------------------------------------*/

void BEEP_DeInit(BEEP_TypeDef* BEEPx);
void BEEP_Init(BEEP_TypeDef* BEEPx, BEEP_InitTypeDef *BEEP_InitStruct);
void BEEP_Cmd(BEEP_TypeDef* BEEPx, FunctionalState NewState);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_BEEP_H */
