/**
 * @file    wb32l003_pca.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the PCA firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_PCA_H
#define __WB32L003_PCA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup PCA
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  PCA Configuration Structure definition
  * @note   This structure is for PCA
  */
typedef struct
{
  uint32_t ClkSrcSel;       /*!< Specifies input capture clock source.
                                 This parameter can be a value of @ref PCA_Clock_Source_Selection */

  uint32_t RunInIdleMode;   /*!< PCA is enabled or disabled in IDLE mode.
                                 This parameter can be a value of @ref PCA_Run_In_Idle_Mode */
} PCA_BaseInitTypeDef;

/**
  * @brief  PCA Input Capture Configuration Structure definition
  */
typedef struct
{
  uint32_t ICPolarity;     /*!< Specifies the active edge of the input signal.
                                This parameter can be a value of @ref PCA_Input_Capture_Polarity_Selection */

  uint32_t Channel;        /*!< Specifies the PCA output channel.
                                This parameter can be a value of @ref PCA_Channel. */
} PCA_IC_InitTypeDef;

/**
  * @brief  PCA Output Compare Configuration Structure definition
  */
typedef struct
{
  uint32_t CompareEnable;  /*!< Specifies the output compare function enable or disable.
                                This parameter can be a value of @ref PCA_Output_Compare_Enable */

  uint32_t TogEnable;      /*!< Specifies tog function enable or disable.
                                TogEnable & PwmEnable must not be enabled at the same time.
                                This parameter can be a value of @ref PCA_Toggle_Enable */

  uint32_t PwmEnable;      /*!< Specifies tog function enable or disable.
                                TogEnable & PwmEnable must not be enabled at the same time.
                                This parameter can be a value of @ref PCA_Pwm_Enable */

  uint32_t Period;         /*!< Specifies the period value compared with CNT register.
                                Period caculation = Period/(PCA clock)
                                This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF. */

  uint32_t Channel;        /*!< Specifies the PCA output channel.
                                This parameter can be a value of @ref PCA_Channel. */

} PCA_OC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup PCA_Exported_Constants
  * @{
  */

/** @defgroup PCA_Clock_Source_Selection
  * @{
  */
#define PCA_CLOCK_SOURCE_PCLKDIV32        0x00000000U                                     /*!< Specify PCLK divider 32 as pca input clock source */
#define PCA_CLOCK_SOURCE_PCLKDIV16        (PCA_MOD_CPS_0)                                 /*!< Specify PCLK divider 16 as pca input clock source */
#define PCA_CLOCK_SOURCE_PCLKDIV8         (PCA_MOD_CPS_1)                                 /*!< Specify PCLK divider 8 as pca input clock source */
#define PCA_CLOCK_SOURCE_PCLKDIV4         (PCA_MOD_CPS_1 | PCA_MOD_CPS_0)                 /*!< Specify PCLK divider 4 as pca input clock source */
#define PCA_CLOCK_SOURCE_PCLKDIV2         (PCA_MOD_CPS_2)                                 /*!< Specify PCLK divider 2 as pca input clock source */
#define PCA_CLOCK_SOURCE_TIM10_OVERFLOW   (PCA_MOD_CPS_2 | PCA_MOD_CPS_0)                 /*!< Specify TIM10 overflow as pca input clock source */
#define PCA_CLOCK_SOURCE_TIM11_OVERFLOW   (PCA_MOD_CPS_2 | PCA_MOD_CPS_1)                 /*!< Specify TIM11 overflow as pca input clock source */
#define PCA_CLOCK_SOURCE_ECI              (PCA_MOD_CPS_2 | PCA_MOD_CPS_1 | PCA_MOD_CPS_0) /*!< Specify ECI as pca input clock source */

#define IS_PCA_CLOCK_COURCE(CLOCK_SOURCE) (((CLOCK_SOURCE) == PCA_CLOCK_SOURCE_PCLKDIV32) || ((CLOCK_SOURCE) == PCA_CLOCK_SOURCE_PCLKDIV16)    || \
                                           ((CLOCK_SOURCE) == PCA_CLOCK_SOURCE_PCLKDIV8) || ((CLOCK_SOURCE) == PCA_CLOCK_SOURCE_PCLKDIV4)      || \
                                           ((CLOCK_SOURCE) == PCA_CLOCK_SOURCE_PCLKDIV2) || ((CLOCK_SOURCE) == PCA_CLOCK_SOURCE_TIM10_OVERFLOW) || \
                                           ((CLOCK_SOURCE) == PCA_CLOCK_SOURCE_TIM11_OVERFLOW) || ((CLOCK_SOURCE) == PCA_CLOCK_SOURCE_ECI))
/**
  * @}
  */

/** @defgroup PCA_Run_In_Idle_Mode
  * @{
  */
#define PCA_IDLEMODE_DISABLE              (0x00000000)
#define PCA_IDLEMODE_ENABLE               (0x00000080)

#define IS_PCA_IDLEMODE(IDLE_MODE)        (((IDLE_MODE) == PCA_IDLEMODE_DISABLE) || ((IDLE_MODE) == PCA_IDLEMODE_ENABLE))
/**
  * @}
  */

/** @defgroup PCA_Input_Capture_Polarity_Selection
  * @note CCAPMx(1,2,3,4)'s position is same as CCAPM0
  * @{
  */
#define PCA_INPUT_POLARITY_NONE                (0x00000000)
#define PCA_INPUT_POLARITY_FALLING             (PCA_CCAPM0_CAPN)
#define PCA_INPUT_POLARITY_RISING              (PCA_CCAPM0_CAPP)
#define PCA_INPUT_POLARITY_BOTH                (PCA_CCAPM0_CAPN | PCA_CCAPM0_CAPP)

#define IS_PCA_INPUT_POLARATY(INPUT_POLARATY)  (((INPUT_POLARATY) == PCA_INPUT_POLARITY_NONE) || ((INPUT_POLARATY) == PCA_INPUT_POLARITY_FALLING) || \
                                                ((INPUT_POLARATY) == PCA_INPUT_POLARITY_RISING) || ((INPUT_POLARATY) == PCA_INPUT_POLARITY_BOTH))
/**
  * @}
  */

/** @defgroup PCA_Interrupt_Flags
  * @{
  */
#define PCA_FLAG_CC0                      (PCA_CR_CCF0)
#define PCA_FLAG_CC1                      (PCA_CR_CCF1)
#define PCA_FLAG_CC2                      (PCA_CR_CCF2)
#define PCA_FLAG_CC3                      (PCA_CR_CCF3)
#define PCA_FLAG_CC4                      (PCA_CR_CCF4)
#define PCA_FLAG_OVERFLOW                 (PCA_CR_CF)

#define IS_PCA_FLAG(FLAG)                 (((FLAG) == PCA_FLAG_CC0) || ((FLAG) == PCA_FLAG_CC1) || \
                                           ((FLAG) == PCA_FLAG_CC2) || ((FLAG) == PCA_FLAG_CC3) || \
                                           ((FLAG) == PCA_FLAG_CC4) || ((FLAG) == PCA_FLAG_OVERFLOW))
/**
  * @}
  */

/** @defgroup PCA_Interrupt
  * @{
  */
#define PCA_IT_CC0                        (0x01)
#define PCA_IT_CC1                        (0x02)
#define PCA_IT_CC2                        (0x04)
#define PCA_IT_CC3                        (0x08)
#define PCA_IT_CC4                        (0x10)
#define PCA_IT_OVERFLOW                   (0x80)

#define IS_PCA_IT(PCA_IT)                 (((PCA_IT) == PCA_IT_CC0) || ((PCA_IT) == PCA_IT_CC1) || \
                                           ((PCA_IT) == PCA_IT_CC2) || ((PCA_IT) == PCA_IT_CC3) || \
                                           ((PCA_IT) == PCA_IT_CC4) || ((PCA_IT) == PCA_IT_OVERFLOW))
/**
  * @}
  */

/** @defgroup PCA_Channel
  * @{
  */
#define PCA_CHANNEL_0                     (0x01)
#define PCA_CHANNEL_1                     (0x02)
#define PCA_CHANNEL_2                     (0x04)
#define PCA_CHANNEL_3                     (0x08)
#define PCA_CHANNEL_4                     (0x10)
#define PCA_CHANNEL_MASK                  (0x1F)

#define IS_PCA_CHANNEL(CHANNEL)           (((CHANNEL) & PCA_CHANNEL_MASK) != 0x00)
/**
  * @}
  */

/** @defgroup PCA_Output_Compare_Enable
  * @{
  */
#define PCA_OC_ENABLE                     (PCA_CCAPM0_ECOM) /*!< Output compare function enable */
#define PCA_OC_DISABLE                    0x00000000U       /*!< Output compare function disable */

#define IS_PCA_OC_ENABLE(OC_ENABLE)       (((OC_ENABLE) == PCA_OC_ENABLE) || ((OC_ENABLE) == PCA_OC_DISABLE))
/**
  * @}
  */

/** @defgroup PCA_Toggle_Enable
  * @{
  */
#define PCA_TOG_ENABLE                    (PCA_CCAPM0_MAT | PCA_CCAPM0_TOG) /*!< Toggle function enable */
#define PCA_TOG_DISABLE                   0x00000000U                       /*!< Toggle function disable */

#define IS_PCA_TOG_ENABLE(TOG_ENABLE)     (((TOG_ENABLE) == PCA_TOG_ENABLE) || ((TOG_ENABLE) == PCA_TOG_DISABLE))
/**
  * @}
  */

/** @defgroup PCA_Pwm_Enable
  * @{
  */
#define PCA_PWM_ENABLE                    (PCA_CCAPM0_PWM) /*!< Pwm function enable */
#define PCA_PWM_DISABLE                   0x00000000U      /*!< Pwm function disable */

#define IS_PCA_PWM_ENABLE(PWM_ENABLE)     (((PWM_ENABLE) == PCA_PWM_ENABLE) || ((PWM_ENABLE) == PCA_PWM_DISABLE))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void PCA_BaseInit(PCA_BaseInitTypeDef *PCA_InitStruct);
void PCA_OC_Config(PCA_OC_InitTypeDef *OC_Config);
void PCA_IC_Config(PCA_IC_InitTypeDef *IC_Config);
uint16_t PCA_GetCompareValue(uint32_t Channel);
void PCA_Cmd(FunctionalState NewState);
void PCA_OC_Cmd(uint32_t Channel, FunctionalState NewState);
void PCA_OC_INVCmd(uint32_t Channel, FunctionalState NewState);
void PCA_DeInit(void);
void PCA_ITConfig(uint8_t PCA_IT, FunctionalState NewState);
FlagStatus PCA_GetFlagStatus(uint8_t PCA_FLAG);
ITStatus PCA_GetITStatus(uint8_t PCA_IT);
void PCA_ClearITPendingBit(uint8_t PCA_IT);
void PCA_ClearFlag(uint8_t PCA_FLAG);
void PCA_SetPWMDuty(uint32_t Channel, uint8_t Duty);
void PCA_IC0_TriggerConfig(uint32_t PCA_Trigger_ICPolarity);
void PCA_IC1_TriggerConfig(uint32_t PCA_Trigger_ICPolarity);
void PCA_IC2_TriggerConfig(uint32_t PCA_Trigger_ICPolarity);
void PCA_IC3_TriggerConfig(uint32_t PCA_Trigger_ICPolarity);
void PCA_IC4_TriggerConfig(uint32_t PCA_Trigger_ICPolarity);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_PCA_H */
