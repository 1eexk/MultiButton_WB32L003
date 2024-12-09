/**
 * @file    wb32l003_gpio.h
 * @author  WestberryTech Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the GPIO firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_GPIO_H
#define __WB32L003_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants
  * @{
  */

#ifdef WB32L003Fx
  #define GPIO_NUMBER                       8U
#elif defined(WB32L003Kx)
  #define GPIO_NUMBER                       16U
#endif

/** 
  * @brief  GPIO Bit SET and Bit RESET enumeration 
  */
typedef enum
{
  Bit_RESET = 0,
  Bit_SET
} BitAction;

/** @defgroup GPIO_Pins_Define 
  * @{
  */
#define GPIO_Pin_0                          ((uint16_t)0x0001) /*!< GPIO Pin 0 */
#define GPIO_Pin_1                          ((uint16_t)0x0002) /*!< GPIO Pin 1 */
#define GPIO_Pin_2                          ((uint16_t)0x0004) /*!< GPIO Pin 2 */
#define GPIO_Pin_3                          ((uint16_t)0x0008) /*!< GPIO Pin 3 */
#define GPIO_Pin_4                          ((uint16_t)0x0010) /*!< GPIO Pin 4 */
#define GPIO_Pin_5                          ((uint16_t)0x0020) /*!< GPIO Pin 5 */
#define GPIO_Pin_6                          ((uint16_t)0x0040) /*!< GPIO Pin 6 */
#define GPIO_Pin_7                          ((uint16_t)0x0080) /*!< GPIO Pin 7 */
#define GPIO_Pin_All                        ((uint16_t)0x00FF) /*!< GPIO All pins */
/**
  * @}
  */


/** @defgroup GPIO_MODE_Define
  * @{
  */
#define GPIO_MODE_IN                        ((uint32_t)0x00000000U) /*!< Input mode */
#define GPIO_MODE_OUT                       ((uint32_t)0x10000000U) /*!< Output mode */
/**
  * @}
  */


/** @defgroup GPIO_OTYPE_Define
  * @{
  */
#define GPIO_OTYPE_PP                       ((uint32_t)0x00000000U) /*!< Output push-pull */
#define GPIO_OTYPE_OD                       ((uint32_t)0x01000000U) /*!< Output open-drain */
/**
  * @}
  */


/** @defgroup GPIO_SPEED_Define
  * @{
  */
#define GPIO_SPEED_LOW                      ((uint32_t)0x00000000U) /*!< Low speed */
#define GPIO_SPEED_HIGH                     ((uint32_t)0x00100000U) /*!< High speed */
/**
  * @}
  */


/** @defgroup GPIO_PUPD_Define
  * @{
  */
#define GPIO_PUPD_NOPULL                    ((uint32_t)0x00000000U) /*!< No pull resistor */
#define GPIO_PUPD_UP                        ((uint32_t)0x00010000U) /*!< Pull up resistor enabled */
#define GPIO_PUPD_DOWN                      ((uint32_t)0x00020000U) /*!< Pull down resistor enabled */
/**
  * @}
  */


/** @defgroup GPIO_DRV_Define
  * @{
  */
#define GPIO_DRV_HIGH                       ((uint32_t)0x00000000U) /*!< High drive capability */
#define GPIO_DRV_LOW                        ((uint32_t)0x00001000U) /*!< Low drive capability */
/**
  * @}
  */


/** @defgroup GPIO_EXTI_Define
  * @{
  */
#define GPIO_EXTI_IT_DISABLE                ((uint32_t)0x00000000U) /*!< Disable EXTI Interrupt */
#define GPIO_EXTI_IT_ENABLE                 ((uint32_t)0x00000100U) /*!< Enable EXTI Interrupt */
#define GPIO_EXTI_TRIGGER_EDGE              ((uint32_t)0x00000000U) /*!< Edge triggered interrupt */
#define GPIO_EXTI_TRIGGER_LEVEL             ((uint32_t)0x00000200U) /*!< Level triggered interrupt */
#define GPIO_EXTI_TRIGGER_LOW               ((uint32_t)0x00000000U) /*!< Low level triggered interrupt */
#define GPIO_EXTI_TRIGGER_HIGH              ((uint32_t)0x00000400U) /*!< Low level triggered interrupt */
#define GPIO_EXTI_TRIGGER_FALLING           ((uint32_t)0x00000000U) /*!< Falling edge triggered interrupt */
#define GPIO_EXTI_TRIGGER_RISSING           ((uint32_t)0x00000400U) /*!< Rising edge triggered interrupt */
#define GPIO_EXTI_TRIGGER_RISSING_FALLING   ((uint32_t)0x00000800U) /*!< Rising and falling edge triggered interrupt */
#define GPIO_EXTI_Mask                      ((uint32_t)0x00000F00U)
/**
  * @}
  */


/** @defgroup GPIO_DB_Define
  * @{
  */
#define GPIO_DB_DISABLE                     ((uint32_t)0x00000000U) /*!< Disable Debounce function */
#define GPIO_DB_ENABLE                      ((uint32_t)0x00000010U) /*!< Enable Debounce function */
#define GPIO_DB_SYNC_DISABLE                ((uint32_t)0x00000000U) /*!< Disable two-level synchronization */
#define GPIO_DB_SYNC_ENABLE                 ((uint32_t)0x00000020U) /*!< Enable two-level synchronization */
#define GPIO_DB_CLK_DIV_1                   ((uint32_t)0x00000000U)
#define GPIO_DB_CLK_DIV_2                   ((uint32_t)0x00000001U)
#define GPIO_DB_CLK_DIV_4                   ((uint32_t)0x00000002U)
#define GPIO_DB_CLK_DIV_8                   ((uint32_t)0x00000003U)
#define GPIO_DB_CLK_DIV_16                  ((uint32_t)0x00000004U)
#define GPIO_DB_CLK_DIV_32                  ((uint32_t)0x00000005U)
#define GPIO_DB_CLK_DIV_64                  ((uint32_t)0x00000006U)
#define GPIO_DB_CLK_DIV_128                 ((uint32_t)0x00000007U)
#define GPIO_DB_CLK_DIV_256                 ((uint32_t)0x00000008U)
#define GPIO_DB_CLK_DIV_512                 ((uint32_t)0x00000009U)
#define GPIO_DB_CLK_DIV_1024                ((uint32_t)0x0000000AU)
#define GPIO_DB_CLK_DIV_2048                ((uint32_t)0x0000000BU)
#define GPIO_DB_CLK_DIV_4096                ((uint32_t)0x0000000CU)
#define GPIO_DB_CLK_DIV_8192                ((uint32_t)0x0000000DU)
#define GPIO_DB_CLK_DIV_16384               ((uint32_t)0x0000000EU)
#define GPIO_DB_CLK_DIV_32768               ((uint32_t)0x0000000FU)
#define GPIO_DB_Mask                        ((uint32_t)0x000000FFU)
/**
  * @}
  */


/** @defgroup GPIO_AF_Define
  * @{
  */
#define GPIO_AF0                            ((uint32_t)0x00000000U)
#define GPIO_AF1                            ((uint32_t)0x00000001U)
#define GPIO_AF2                            ((uint32_t)0x00000002U)
#define GPIO_AF3                            ((uint32_t)0x00000003U)
#define GPIO_AF4                            ((uint32_t)0x00000004U)
#define GPIO_AF5                            ((uint32_t)0x00000005U)
#define GPIO_AF6                            ((uint32_t)0x00000006U)
#define GPIO_AF7                            ((uint32_t)0x00000007U)
#define GPIO_AF8                            ((uint32_t)0x00000008U)
#define GPIO_AF9                            ((uint32_t)0x00000009U)
#define GPIO_AF10                           ((uint32_t)0x0000000AU)
#define GPIO_AF11                           ((uint32_t)0x0000000BU)
#define GPIO_AF12                           ((uint32_t)0x0000000CU)
#define GPIO_AF13                           ((uint32_t)0x0000000DU)
#define GPIO_AF14                           ((uint32_t)0x0000000EU)
#define GPIO_AF15                           ((uint32_t)0x0000000FU)
#define GPIO_AF_Mask                        ((uint32_t)0x0000000FU)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define IS_GPIO_ALL_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7))

#define IS_GPIO_PIN(PIN) (((PIN) & 0x000000FF) != (uint32_t)0x00)

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

/* Exported functions --------------------------------------------------------*/

void GPIO_DeInit(GPIO_TypeDef *GPIOx);
void GPIO_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t PinConfig);
void GPIO_SetAFPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Alternate);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t PortVal);
void GPIO_ToggleBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_DriveCurrentConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Current);
void GPIO_EXTIConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t EXTI_Config);
void GPIO_DebounceConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t DebounceConfig);
FlagStatus GPIO_EXTI_GetFlagStatus(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_EXTI_ClearFlag(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
ITStatus GPIO_EXTI_GetIT(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_EXTI_ClearIT(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_GPIO_H */
