/**
 * @file    wb32l003_basetim.h
 * @author  WestberryTech Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the base TIM firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_BASETIM_H
#define __WB32L003_BASETIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup BASETIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  BaseTim Init structure definition
  * @note   This structure is used for TIM10 and TIM11.
  */
typedef struct
{
  uint32_t BaseTim_Gate;         /*!< Specifies gate function enable or disable.
                                      This parameter can be a value of @ref BaseTim_Gate_Enable_Disable */

  uint32_t BaseTim_GatePolarity; /*!< Specifies gate polarity high or low.
                                      This parameter can be a value of @ref BaseTim_GatePolarity */

  uint32_t BaseTim_Tog;          /*!< Specifies tog function enable or disable.
                                      This parameter can be a value of @ref BaseTim_Tog_Enable_Disable */

  uint32_t BaseTim_Function;     /*!< Specifies Counter/Timer function selection.
                                      This parameter can be a value of @ref BaseTim_Function_Count_Timer */

  uint32_t BaseTim_AutoReload;   /*!< Specifies Timer auto reload enable or disable.
                                      This parameter can be a value of @ref BaseTim_AutoReload */

  uint32_t BaseTim_CountLevel;   /*!< Specifies Timer maxim counter value is 0xFFFF or 0xFFFFFFFF.
                                      This parameter can be a value of @ref BaseTim_CountLevel */

  uint32_t BaseTim_CountMode;    /*!< Specifies Timer oneshot or repeat mode.
                                      This parameter can be a value of @ref BaseTim_CountMode */

  uint32_t BaseTim_Prescaler;    /*!< Specifies the prescaler value used to divide the BaseTim clock.
                                      This parameter can be a value of @ref BaseTim_Prescaler */

  uint32_t BaseTim_BGLoad;       /*!< Specifies the period value to be loaded into the active
                                      CNT value immediately through LOAD register or periodly through BGLOAD register
                                      refer to mode specified by BaseTim_AutoReload.
                                      Period caculation = (MaxCntLevel - Period)/((BaseTim clock)/Prescaler)
                                      This parameter can be a number between Min_Data = 0x00000000 and Max_Data = 0xFFFFFFFF.  */
} BaseTim_InitTypeDef;

/* Exported Constants --------------------------------------------------------*/

/** @defgroup TIM_Exported_constants 
  * @{
  */

#define IS_BaseTIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM10) || \
                                       ((PERIPH) == TIM11))

/** @defgroup BaseTim_Gate_Enable_Disable 
  * @{
  */
#define BaseTim_Gate_Enable           ((uint32_t)(0x01U << 10))
#define BaseTim_Gate_Disable          ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup BaseTim_GatePolarity 
  * @{
  */
#define BaseTim_GatePolarity_Low      ((uint32_t)(0x01U << 11))
#define BaseTim_GatePolarity_High     ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup BaseTim_Tog_Enable_Disable 
  * @{
  */
#define BaseTim_Tog_Enable            ((uint32_t)(0x01U << 9))
#define BaseTim_Tog_Disable           ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup BaseTim_Function_Count_Timer
  * @{
  */
#define BaseTim_Function_Count        ((uint32_t)(0x01U << 8))
#define BaseTim_Function_Timer        ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup BaseTim_AutoReload 
  * @{
  */
#define BaseTim_AutoReload_Enable     ((uint32_t)(0x01U << 6))
#define BaseTim_AutoReload_Disable    ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup BaseTim_CountLevel 
  * @{
  */
#define BaseTim_CountLevel_32BIT      ((uint32_t)(0x01U << 4))
#define BaseTim_CountLevel_16BIT      ((uint32_t)0x00)
/**
  * @}
  */


/** @defgroup BaseTim_CountMode 
  * @{
  */
#define BaseTim_CountMode_OneShot     ((uint32_t)(0x01U << 3))
#define BaseTim_CountMode_Repeat      ((uint32_t)0x00)
/**
  * @}
  */

/** @defgroup BaseTim_Prescaler 
  * @{
  */
#define BaseTim_Prescaler_DIV1        ((uint32_t)0x00)
#define BaseTim_Prescaler_DIV2        ((uint32_t)0x01)
#define BaseTim_Prescaler_DIV4        ((uint32_t)0x02)
#define BaseTim_Prescaler_DIV8        ((uint32_t)0x03)
#define BaseTim_Prescaler_DIV16       ((uint32_t)0x04)
#define BaseTim_Prescaler_DIV32       ((uint32_t)0x05)
#define BaseTim_Prescaler_DIV64       ((uint32_t)0x06)
#define BaseTim_Prescaler_DIV128      ((uint32_t)0x07)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
void BaseTim_DeInit(BASETIM_TypeDef* TIMx);
void BaseTim_Init(BASETIM_TypeDef* TIMx, BaseTim_InitTypeDef* BaseTim_InitStruct);
void BaseTim_Cmd(BASETIM_TypeDef* TIMx, FunctionalState NewState);
void BaseTim_ITConfig(BASETIM_TypeDef* TIMx, FunctionalState NewState);
uint32_t BaseTim_GetCounter(BASETIM_TypeDef* TIMx);
void BaseTim_SetLoad(BASETIM_TypeDef* TIMx, uint16_t load);
void BaseTim_SetBkLoad(BASETIM_TypeDef* TIMx, uint16_t bgLoad);
FlagStatus BaseTim_GetFlagStatus(BASETIM_TypeDef* TIMx);
void BaseTim_ClearFlag(BASETIM_TypeDef* TIMx);


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_BASETIM_H */
