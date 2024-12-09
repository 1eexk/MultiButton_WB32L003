/**
 * @file    wb32l003_lvd.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the LVD firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_LVD_H
#define __WB32L003_LVD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup LVD
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  LVD Configuration Structure definition
  * @note   This structure is for LVD
  */
typedef struct
{
  uint32_t FltClkSel;     /*!< Specifies filter clock.
                               This parameter can be a value of @ref LVD_Filter_Clock_Selection */

  uint32_t VoltageLevel;  /*!< Specifies voltage level for LVD.
                               This parameter can be a value of @ref LVD_Voltage_Level */

  uint32_t TriggerSel;    /*!< Specifies trigger selection for LVD.
                               This parameter can be a value of @ref LVD_Trigger_Selection */

  uint32_t Action;        /*!< Specifies low voltage detection action.
                               This parameter can be a value of @ref LVD_Action_After_Detection */

  uint32_t FltNum;        /*!< Specifies the filter number for digital filter.
                               This parameter can be a value between 0x0000 to 0xFFFF */

} LVD_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup LVD_Exported_constants
  * @{
  */

/** @defgroup LVD_Filter_Clock_Selection
  * @{
  */
#define LVD_FLTCLK_DISABLE          (0x00000000U)         /*!< Digital filter clock select */
#define LVD_FLTCLK_PCLK             (LVD_CR_FLTCLK_SEL_0) /*!< Digital filter clock select PCLK */
#define LVD_FLTCLK_LSI              (LVD_CR_FLTCLK_SEL_1) /*!< Digital filter clock select LSI */

#define IS_LVD_FLTCLK(FLTCLK)       (((FLTCLK) == LVD_FLTCLK_DISABLE) || \
                                     ((FLTCLK) == LVD_FLTCLK_PCLK) || \
                                     ((FLTCLK) == LVD_FLTCLK_LSI))
#define IS_LVD_FLTNUM(FLTNUM)       (((FLTNUM) >= 0U) && ((FLTNUM) <= 0xFFFFU))
/**
  * @}
  */

/** @defgroup LVD_Trigger_Selection
  * @{
  */
#define LVD_TRIGGER_HIGHLEVEL       (VCMP_CR1_HIGHINTEN)                                           /*!< Trigger select highlevel */
#define LVD_TRIGGER_RISING          (VCMP_CR1_RISEINTEN)                                           /*!< Trigger select rising edge */
#define LVD_TRIGGER_FALLING         (VCMP_CR1_FALLINTEN)                                           /*!< Trigger select falling edge */
#define LVD_TRIGGER_BOTHEDGE        (VCMP_CR1_RISEINTEN | VCMP_CR1_FALLINTEN)                      /*!< Trigger select both edge */
#define LVD_TRIGGER_ALL             (VCMP_CR1_HIGHINTEN | VCMP_CR1_RISEINTEN | VCMP_CR1_FALLINTEN) /*!< Trigger select both edge and highlevel */

#define IS_LVD_TRIGGER(LVD_TRIGGER) (((LVD_TRIGGER) == LVD_TRIGGER_HIGHLEVEL) || \
                                     ((LVD_TRIGGER) == LVD_TRIGGER_RISING) || \
                                     ((LVD_TRIGGER) == LVD_TRIGGER_FALLING) || \
                                     ((LVD_TRIGGER) == LVD_TRIGGER_BOTHEDGE) || \
                                     ((LVD_TRIGGER) == LVD_TRIGGER_ALL))
/**
  * @}
  */

/** @defgroup LVD_Voltage_Level
  * @{
  */
#define LVD_VOLLEVEL_0              (0x00000000U)
#define LVD_VOLLEVEL_1              (LVD_CR_DIV_SEL_0)
#define LVD_VOLLEVEL_2              (LVD_CR_DIV_SEL_1)
#define LVD_VOLLEVEL_3              (LVD_CR_DIV_SEL_0 | LVD_CR_DIV_SEL_1)
#define LVD_VOLLEVEL_4              (LVD_CR_DIV_SEL_2)
#define LVD_VOLLEVEL_5              (LVD_CR_DIV_SEL_0 | LVD_CR_DIV_SEL_2)
#define LVD_VOLLEVEL_6              (LVD_CR_DIV_SEL_2 | LVD_CR_DIV_SEL_1)
#define LVD_VOLLEVEL_7              (LVD_CR_DIV_SEL_2 | LVD_CR_DIV_SEL_1 | LVD_CR_DIV_SEL_0)

#define LVD_VOLLEVEL_8              (LVD_CR_DIV_SEL_3)
#define LVD_VOLLEVEL_9              (LVD_CR_DIV_SEL_3 | LVD_CR_DIV_SEL_0)
#define LVD_VOLLEVEL_A              (LVD_CR_DIV_SEL_3 | LVD_CR_DIV_SEL_1)

#define IS_LVD_VOLLEVEL(VOLLEVE)    (((VOLLEVE) == LVD_VOLLEVEL_0) || ((VOLLEVE) == LVD_VOLLEVEL_1) || \
                                     ((VOLLEVE) == LVD_VOLLEVEL_2) || ((VOLLEVE) == LVD_VOLLEVEL_3) || \
                                     ((VOLLEVE) == LVD_VOLLEVEL_4) || ((VOLLEVE) == LVD_VOLLEVEL_5) || \
                                     ((VOLLEVE) == LVD_VOLLEVEL_6) || ((VOLLEVE) == LVD_VOLLEVEL_7) || \
                                     ((VOLLEVE) == LVD_VOLLEVEL_8) || ((VOLLEVE) == LVD_VOLLEVEL_9) || \
                                     ((VOLLEVE) == LVD_VOLLEVEL_A))
/**
  * @}
  */

/** @defgroup LVD_Action_After_Detection
  * @{
  */
#define LVD_ACTION_INTERRUPT        (0x00000000U) /*!< LVD module generate interrupt after detection */
#define LVD_ACTION_RESET            (LVD_CR_ACT)  /*!< LVD module generate reset after detection */

#define IS_LVD_ACTION(ACTION)       (((ACTION) == LVD_ACTION_INTERRUPT) || \
                                     ((ACTION) == LVD_ACTION_RESET))
/**
  * @}
  */

/**
  * @}
  */
 
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void LVD_DIGFLT_Cmd(FunctionalState NewState);
void LVD_Init(LVD_InitTypeDef *InitStruct);
void LVD_Cmd(FunctionalState NewState);
void LVD_DeInit(void);
void LVD_ITCmd(FunctionalState NewState);
FlagStatus LVD_GetFlagStatus(void);
ITStatus LVD_GetITStatus(void);
void LVD_ClearITPendingBit(void);
void LVD_ClearFlag(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_LVD_H */
