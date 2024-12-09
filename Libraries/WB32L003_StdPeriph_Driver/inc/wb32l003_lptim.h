/**
 * @file    wb32l003_lptim.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the LPTIM firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_LPTIM_H
#define __WB32L003_LPTIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup LPTIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  LPTIM Time base Configuration Structure definition
  * @note   This structure is for LPTIM   
  */
typedef struct
{
  uint32_t GateEnable;         /*!< Specifies gate function enable or disable.
                                    This parameter can be a value of @ref LPTIM_Gate_Enable */
  
  uint32_t GateLevel;          /*!< Specifies gate level high or low.
                                    This parameter can be a value of @ref LPTIM_Gate_Level_Selection */
  
  uint32_t ClkSel;             /*!< Specifies low power timer clock.
                                   This parameter can be a value of @ref LPTIM_Clock_Source_Selection */
  
  uint32_t TogEnable;          /*!< Specifies tog function enable or disable.
                                    This parameter can be a value of @ref LPTIM_Toggle_Enable */
  
  uint32_t CntTimSel;          /*!< Specifies Counter/Timer function selection.
                                    This parameter can be a value of @ref LPTIM_Counter/Timer_Selection */
  
  uint32_t AutoReload;         /*!< Specifies Timer auto reload enable or disable.
                                    This parameter can be a value of @ref LPTIM_Auto_Reload */

  uint32_t Period;             /*!< Specifies the period value to be loaded into the active
                                    CNT value immediately through LOAD register or periodly through BGLOAD register
                                    refer to mode specified by LPTIM_AutoReload.
                                    Period caculation = (MaxCntLevel - Period)/(LPTIM clock)
                                    This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */
} LPTIM_BaseInitTypeDef;

 /* Exported constants --------------------------------------------------------*/

 /** @defgroup LPTIM_Exported_Constants
  * @{
  */

/** @defgroup LPTIM_Gate_Enable
  * @{
  */
#define LPTIM_GATE_ENABLE                   (LPTIM_CR_GATE_EN) /*!< Gate function enable */
#define LPTIM_GATE_DISABLE                  0x00000000U        /*!< Gate function disable */

#define IS_LPTIM_GATE_ENABLE(GATE)          (((GATE) == LPTIM_GATE_ENABLE) || \
                                             ((GATE) == LPTIM_GATE_DISABLE))
/**
  * @}
  */

/** @defgroup LPTIM_Gate_Level_Selection
  * @{
  */
#define LPTIM_GATELEVEL_LOW                 (LPTIM_CR_GATE_P) /*!< Specify gatelevel low for gate input */
#define LPTIM_GATELEVEL_HIGH                0x00000000U       /*!< Specify gatelevel high for gate input */

#define IS_LPTIM_GATE_LEVEL(GATE_LEVEL)     (((GATE_LEVEL) == LPTIM_GATELEVEL_LOW) || \
                                             ((GATE_LEVEL) == LPTIM_GATELEVEL_HIGH))
/**
  * @}
  */

/** @defgroup LPTIM_Clock_Source_Selection
  * @{
  */
#define LPTIM_CLOCK_SOURCE_PCLK             0x00000000U                               /*!< Specify PCLK as lptim clock source */
#define LPTIM_CLOCK_SOURCE_LSE              (LPTIM_CR_TCK_SEL_1)                      /*!< Specify LSE as lptim clock source */
#define LPTIM_CLOCK_SOURCE_LSI              (LPTIM_CR_TCK_SEL_1 | LPTIM_CR_TCK_SEL_0) /*!< Specify LSI as lptim clock source */

#define IS_LPTIM_CLOCK_SOURCE(CLOCK_SOURCE) (((CLOCK_SOURCE) == LPTIM_CLOCK_SOURCE_PCLK) || \
                                             ((CLOCK_SOURCE) == LPTIM_CLOCK_SOURCE_LSE)  || \
                                             ((CLOCK_SOURCE) == LPTIM_CLOCK_SOURCE_LSI))
/**
  * @}
  */

/** @defgroup LPTIM_Toggle_Enable
  * @{
  */
#define LPTIM_TOG_ENABLE                    (LPTIM_CR_TOG_EN) /*!< Tog function enable */
#define LPTIM_TOG_DISABLE                   0x00000000U       /*!< Tog function disable */

#define IS_LPTIM_TOG(TOG)                   (((TOG) == LPTIM_TOG_ENABLE) || \
                                             ((TOG) == LPTIM_TOG_DISABLE))
/**
  * @}
  */

/** @defgroup LPTIM_Counter/Timer_Selection
  * @{
  */
#define LPTIM_COUNTER_SELECT                (LPTIM_CR_CT_SEL) /*!< Counter function select */
#define LPTIM_TIMER_SELECT                  0x00000000U       /*!< Timer function select */

#define IS_LPTIM_COUNTER(COUNTER)           (((COUNTER) == LPTIM_COUNTER_SELECT) || \
                                             ((COUNTER) == LPTIM_TIMER_SELECT))
/**
  * @}
  */

/** @defgroup LPTIM_Auto_Reload
  * @{
  */
#define LPTIM_AUTORELOAD_ENABLE             (LPTIM_CR_MODE) /*!< Auto reload mode enable */
#define LPTIM_AUTORELOAD_DISABLE            0x00000000U     /*!< Auto reload mode disable */

#define IS_LPTIM_AUTORELOAD(AUTORELOAD)     (((AUTORELOAD) == LPTIM_AUTORELOAD_ENABLE) || \
                                             ((AUTORELOAD) == LPTIM_AUTORELOAD_DISABLE))
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

void LPTIM_DeInit(void);
void LPTIM_BaseInit(LPTIM_BaseInitTypeDef *Base_InitStruct);
void LPTIM_TCKCmd(FunctionalState NewState);
void LPTIM_Cmd(FunctionalState NewState);
void LPTIM_ITCmd(FunctionalState NewState);
FlagStatus LPTIM_GetFlagStatus(void);
ITStatus LPTIM_GetITStatus(void);
void LPTIM_ClearFlag(void);
void LPTIM_ClearITPendingBit(void);
void LPTIM_SetCounter(uint32_t Counter);
uint32_t LPTIM_GetCounter(void);
void LPTIM_GateCmd(FunctionalState NewState);
void LPTIM_ToggleCmd(FunctionalState NewState);
void LPTIM_SetGateLevel(uint32_t Level);
FlagStatus LPTIM_GetSyncFlag(void);

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_LPTIM_H */
