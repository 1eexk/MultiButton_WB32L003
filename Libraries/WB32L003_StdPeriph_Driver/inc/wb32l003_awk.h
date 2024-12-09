/**
 * @file    wb32l003_awk.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the AWK firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_AWK_H
#define __WB32L003_AWK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup AWK
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  AWK Init structure definition
  */
typedef struct
{
  uint32_t AWK_CLK_SEL;   /*!< Specifies AWK timer clock.*/
  uint32_t AWK_HSE_PRSC;  /*!< Specifies AWK HSE clock divider value.*/
  uint32_t AWK_DIV_SEL;   /*!< Specifies AWK timer clock divider value.*/
  uint32_t AWK_RLOAD_VAL; /*!< Specifies AWK period value to be loaded into the counter value immediately through RLOAD register.*/
} AWK_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup AWK_Exported_Constants
  * @{
  */

/** @defgroup  
  * @{
  */
#define AWK_CLK_SEL_STOP                       (0x00U << 5) /*!< Select AWK Clock stop */
#define AWK_CLK_SEL_LSI                        (0x01U << 5) /*!< Select AWK Clock lsi */
#define AWK_CLK_SEL_HSE                        (0x02U << 5) /*!< Select AWK Clock hse  */
#define AWK_CLK_SEL_LSE                        (0x03U << 5) /*!< Select AWK Clock lse  */

#define IS_AWK_CLK_SEL(SEL)                    (((SEL) == AWK_CLK_SEL_STOP) || \
                                                ((SEL) == AWK_CLK_SEL_LSI) || \
                                                ((SEL) == AWK_CLK_SEL_HSE) || \
                                                ((SEL) == AWK_CLK_SEL_LSE))
/**
  * @}
  */

/** @defgroup  AWK_HSE_PRSC
  * @{
  */
#define IS_AWK_HSE_PRSC(PRSC)                  (((PRSC) < 0xFFF))
/**
  * @}
  */

/** @defgroup  AWK_RLOAD_VAL
  * @{
  */
#define IS_AWK_RLOAD_VAL(VAL)                  (((VAL) < 0xFF))
/**
  * @}
  */

/** @defgroup  AWK_DIV_SEL
  * @{
  */
#define AWK_CLOCK_DIV_2                        (0x00000000U)
#define AWK_CLOCK_DIV_4                        (AWK_CR_DIVSEL_0)
#define AWK_CLOCK_DIV_8                        (AWK_CR_DIVSEL_1)
#define AWK_CLOCK_DIV_16                       (AWK_CR_DIVSEL_1 | AWK_CR_DIVSEL_0)
#define AWK_CLOCK_DIV_32                       (AWK_CR_DIVSEL_2)
#define AWK_CLOCK_DIV_64                       (AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_0)
#define AWK_CLOCK_DIV_128                      (AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_1)
#define AWK_CLOCK_DIV_256                      (AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_1 | AWK_CR_DIVSEL_0)
#define AWK_CLOCK_DIV_512                      (AWK_CR_DIVSEL_3)
#define AWK_CLOCK_DIV_1024                     (AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_0)
#define AWK_CLOCK_DIV_2048                     (AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_1)
#define AWK_CLOCK_DIV_4096                     (AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_1 | AWK_CR_DIVSEL_0)
#define AWK_CLOCK_DIV_8192                     (AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_2)
#define AWK_CLOCK_DIV_16384                    (AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_0)
#define AWK_CLOCK_DIV_32768                    (AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_1)
#define AWK_CLOCK_DIV_65536                    (AWK_CR_DIVSEL_3 | AWK_CR_DIVSEL_2 | AWK_CR_DIVSEL_1 | AWK_CR_DIVSEL_0)

#define IS_AWK_DIV_SEL(DIV)                    (((DIV) < 0xF))
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void AWK_DeInit(void);
void AWK_Init(AWK_InitTypeDef* AWK_InitStruct);
void AWK_StructInit(AWK_InitTypeDef* AWK_InitStruct);
void AWK_Cmd(FunctionalState NewState);
FlagStatus AWK_GetFlagStatus(void);
void AWK_ClearFlag(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_AWK_H */
