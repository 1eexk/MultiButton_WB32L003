/**
 * @file    wb32l003_vcmp.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the VCMP firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_VCMP_H
#define __WB32L003_VCMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup VCMP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  VCMP Init structure definition
  */
typedef struct
{
  uint32_t VcapDiv;       /*!< Specifies the VCMP VCAPDIV divider, @ref VCMP_VCAP_Division_Slection */
  uint32_t NegPinSel;     /*!< Negative input select, @ref VCMP_InPut_Selection*/
  uint32_t PosPinSel;     /*!< Positive input select, @ref VCMP_InPut_Selection */
  uint32_t Filter_Enable; /*!< Filter counter Enable or Disable, @ref VCMP_Filter_Function_Selection*/
  uint32_t Filter_Clk;    /*!< Filter clk select, @ref VCMP_Filter_Clock_Selection*/
  uint32_t Fliter_Num;    /*!< Filter counter number. Min_Data >= 0x00 and Max_Data = 0xFFFF*/
} VCMP_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup VCMP_Exported_Constants
  * @{
  */

/** @defgroup VCMP_Enable_definitions
  * @{
  */
#define VCMP_VCAPDIV_ENABLE            VCMP_CR0_VCAPDIV_EN /*!< VCMP VC DIVIDED ENABLE */
#define VCMP_VCAPDIV_DISABLE           (0x0U)              /*!< VCMP VC DIVIDED DISABLE */

#define VCMP_INT_ENABLE                VCMP_CR1_INT_EN     /*!< VCMP INTERRUPT ENABLE */
#define VCMP_INT_DISABLE               (0x0U)              /*!< VCMP INTERRUPT DISABLE */

#define VCMP_ENABLE                    VCMP_CR1_VCEN       /*!< VCMP ENABLE */
#define VCMP_DISABLE                   (0x0U)              /*!< VCMP DISABLE */
/**
  * @}
  */

/** @defgroup VCMP_VCAP_Division_Slection
  * @{
  */
#define VCMP_1P4_VCAPDIV               (0x00U) /*!< Specifies the VCMP 1/4 VCAP */
#define VCMP_2P4_VCAPDIV               (0x01U) /*!< Specifies the VCMP 2/4 VCAP */
#define VCMP_3P4_VCAPDIV               (0x02U) /*!< Specifies the VCMP 3/4 VCAP */
#define VCMP_4P4_VCAPDIV               (0x03U) /*!< Specifies the VCMP VCAP not divided */

#define IS_VCMP_VCAPDIV(VCMP_VCAPDIV)  (((VCMP_VCAPDIV) == VCMP_1P4_VCAPDIV) || ((VCMP_VCAPDIV) == VCMP_2P4_VCAPDIV) || \
                                        ((VCMP_VCAPDIV) == VCMP_3P4_VCAPDIV) || ((VCMP_VCAPDIV) == VCMP_4P4_VCAPDIV))
/**
  * @}
  */

/** @defgroup VCMP_Input_Selection
  * @{
  */
#define VCMP_INPUT_0                   (0x00U)
#define VCMP_INPUT_1                   (0x01U)
#define VCMP_INPUT_2                   (0x02U)
#define VCMP_INPUT_VCAPDIV             (0x03U)

#define IS_VCMP_INPUT(VCMP_INPUT)      (((VCMP_INPUT) == VCMP_INPUT_0) || ((VCMP_INPUT) == VCMP_INPUT_1) || \
                                        ((VCMP_INPUT) == VCMP_INPUT_2) || ((VCMP_INPUT) == VCMP_INPUT_VCAPDIV))
/**
  * @}
  */

/** @defgroup VCMP_Filter_Function_Selection
  * @{
  */
#define VCMP_FILTER_ENABLE             VCMP_CR1_FLTEN /*!< VCMP FILTER ENABLE */
#define VCMP_FILTER_DISABLE            (0x0U)         /*!< VCMP FILTER DISABLE */

#define IS_VCMP_FILTER_ENABLE(FILTER)  (((FILTER) == VCMP_FILTER_ENABLE) || ((FILTER) == VCMP_FILTER_DISABLE))
#define IS_VCMP_FILTER_NUM(FILTER_NUM) (((FILTER_NUM) >= 0U) && ((FILTER_NUM) <= 0xFFFFU)) 
/**
  * @}
  */

/** @defgroup VCMP_Interrupt_Trigger_Selection
  * @{
  */
#define VCMP_HIGH_INT                  VCMP_CR1_HIGHINTEN /*!< VCMP INTERRUPT HIGHT LEVEL TRIGER ENABLE */
#define VCMP_RISE_INT                  VCMP_CR1_RISEINTEN /*!< VCMP INTERRUPT RISE TRIGER ENABLE */
#define VCMP_FALL_INT                  VCMP_CR1_FALLINTEN /*!< VCMP INTERRUPT FALL TRIGER ENABLE */
#define VCMP_INT_MASK                  (VCMP_HIGH_INT | VCMP_RISE_INT | VCMP_FALL_INT)

#define IS_VCMP_INT(VCMP_INT)          (((VCMP_INT) == VCMP_HIGH_INT) || ((VCMP_INT) == VCMP_RISE_INT) || \
                                        ((VCMP_INT) == VCMP_FALL_INT))
/**
  * @}
  */

/** @defgroup VCMP_Filter_Clock_Selection
  * @{
  */
#define VCMP_FILTER_CLK_NONE                 (0x00U)                                 /*!< VCMP Filter clock select NONE */
#define VCMP_FILTER_CLK_PCLK                 (0x01U << VCMP_CR1_VCMP_FLTCLK_SEL_Pos) /*!< VCMP Filter clock select PCLK */
#define VCMP_FILTER_CLK_LSI                  (0x02U << VCMP_CR1_VCMP_FLTCLK_SEL_Pos) /*!< VCMP Filter clock select LSI */

#define IS_VCMP_FILTER_CLOCK(FILTER_CLOCK)   (((FILTER_CLOCK) == VCMP_FILTER_CLK_NONE) || \
                                              ((FILTER_CLOCK) == VCMP_FILTER_CLK_PCLK) || \
                                              ((FILTER_CLOCK) == VCMP_FILTER_CLK_LSI))
/**
  * @}
  */

/** @defgroup VCMP_Out_Configuration
  * @{
  */
#define VCMP_OUTCFG_INV_PAD                  (0x01 << VCMP_OUTCFG_INV_PAD_Pos)
#define VCMP_OUTCFG_TIM1_BKE                 (0x01 << VCMP_OUTCFG_TIM1BKE_Pos)
#define VCMP_OUTCFG_TIM1CH4_GATE             (0x01 << VCMP_OUTCFG_TIM1CH4_EN_Pos)
#define VCMP_OUTCFG_INV_TIM1CH4_GATE         (0x01 << VCMP_OUTCFG_INV_TIM1CH4_Pos)
#define VCMP_OUTCFG_TIM1CH3_GATE             (0x01 << VCMP_OUTCFG_TIM1CH3_EN_Pos)
#define VCMP_OUTCFG_INV_TIM1CH3_GATE         (0x01 << VCMP_OUTCFG_INV_TIM1CH3_Pos)
#define VCMP_OUTCFG_TIM1CH2_GATE             (0x01 << VCMP_OUTCFG_TIM1CH2_EN_Pos)
#define VCMP_OUTCFG_INV_TIM1CH2_GATE         (0x01 << VCMP_OUTCFG_INV_TIM1CH2_Pos)
#define VCMP_OUTCFG_TIM1CH1_GATE             (0x01 << VCMP_OUTCFG_TIM1CH1_EN_Pos)
#define VCMP_OUTCFG_INV_TIM1CH1_GATE         (0x01 << VCMP_OUTCFG_INV_TIM1CH1_Pos)
#define VCMP_OUTCFG_PCA_EXTCLK_EN            (0x01 << VCMP_OUTCFG_PCAECI_EN_Pos)
#define VCMP_OUTCFG_PCA_CAP0_EN              (0x01 << VCMP_OUTCFG_PCACAP0_EN_Pos)
#define VCMP_OUTCFG_INV_PCA                  (0x01 << VCMP_OUTCFG_INV_PCA_Pos)
#define VCMP_OUTCFG_LPTIM_EXTCLK_EN          (0x01 << VCMP_OUTCFG_LPTIMEXT_EN_Pos)
#define VCMP_OUTCFG_LPTIM_GATE               (0x01 << VCMP_OUTCFG_LPTIM_EN_Pos)
#define VCMP_OUTCFG_TIM11_GATE               (0x01 << VCMP_OUTCFG_TIM11_EN_Pos)
#define VCMP_OUTCFG_TIM10_GATE               (0x01 << VCMP_OUTCFG_TIM10_EN_Pos)
#define VCMP_OUTCFG_INV_LPTIM_TIM10_11       (0x01 << VCMP_OUTCFG_INV_TIMX_Pos)

#define VCMP_OUTCFG_MSK                      (0x7FFFFU)
#define IS_VCMP_OUTCFG(OUTCFG)               (((OUTCFG) & VCMP_OUTCFG_MSK) != 0x0000U)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void VCMP_DeInit(void);
void VCMP_Init(VCMP_InitTypeDef *InitStruct);
void VCMP_ITConfig(uint32_t Config, FunctionalState NewState);
void VCMP_ITCmd(FunctionalState NewState);
void VCMP_OutputConfig(uint32_t Config, FunctionalState NewState);
FlagStatus VCMP_GetFlagStatus(void);
ITStatus VCMP_GetITStatus(void);
void VCMP_ClearITPendingBit(void);
void VCMP_ClearFlag(void);
FlagStatus VCMP_GetOutputStatus(void);
void VCMP_Cmd(FunctionalState NewState);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_VCMP_H */
