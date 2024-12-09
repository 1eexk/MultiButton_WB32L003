/**
 * @file    wb32l003_rcc.h
 * @author  WestberryTech Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the RCC firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_RCC_H
#define __WB32L003_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t SYSCLK_Frequency; /*!< returns MAINCLK clock frequency expressed in Hz */
  uint32_t AHBCLK_Frequency; /*!< returns AHBCLK clock frequency expressed in Hz */
  uint32_t APBCLK_Frequency; /*!< returns APB1CLK clock frequency expressed in Hz */
} RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants
  * @{
  */

/** @defgroup RCC_HSI_Value
  * @{
  */
#define HSI_VALUE_24M                       ((uint32_t)24000000) /*!< Value of the Internal high speed oscillator value 24MHz */
#define HSI_VALUE_22M                       ((uint32_t)22120000) /*!< Value of the Internal high speed oscillator value 22.12MHz */
#define HSI_VALUE_16M                       ((uint32_t)16000000) /*!< Value of the Internal high speed oscillator value 16MHz */
#define HSI_VALUE_8M                        ((uint32_t)8000000)  /*!< Value of the Internal high speed oscillator value 8MHz */
#define HSI_VALUE_4M                        ((uint32_t)4000000)  /*!< Value of the Internal high speed oscillator value 4MHz */
/**
  * @}
  */


/** @defgroup RCC_LSI_Value
  * @{
  */
#define LSI_VALUE_38K                       ((uint32_t)38400)    /*!< Value of the Internal low speed oscillator value 38.4KHz */
#define LSI_VALUE_32K                       ((uint32_t)32768)    /*!< Value of the Internal low speed oscillator value 32.768KHz */
/**
  * @}
  */

 
/** @defgroup RCC_LSI_Startup_Value
  * @{
  */
#define RCC_LSI_STARTUP_4CYCLE              ((uint32_t)(0x00U << RCC_LSICR_LSISTARTUP_Pos)) /*!< Startup time 4 cycles */
#define RCC_LSI_STARTUP_16CYCLE             ((uint32_t)(0x01U << RCC_LSICR_LSISTARTUP_Pos)) /*!< Startup time 16  cycles */
#define RCC_LSI_STARTUP_64CYCLE             ((uint32_t)(0x02U << RCC_LSICR_LSISTARTUP_Pos)) /*!< Startup time 64  cycles */
#define RCC_LSI_STARTUP_256CYCLE            ((uint32_t)(0x03U << RCC_LSICR_LSISTARTUP_Pos)) /*!< Startup time 256 cycles */
/**
  * @}
  */

/** @defgroup RCC_HSE
  * @{
  */
#define RCC_HSE_OFF                         ((uint32_t)0x00) /*!< HSE clock deactivation */
#define RCC_HSE_ON                          ((uint32_t)0x01) /*!< HSE clock activation */
#define RCC_HSE_BYPASS                      ((uint32_t)0x02) /*!< HSE clock bypass */
#define RCC_HSE_DEFAULT                     ((uint32_t)0x03)
/**
  * @}
  */


/** @defgroup RCC_LSE
  * @{
  */
#define RCC_LSE_OFF                         ((uint32_t)0x00) /*!< LSE clock deactivation */
#define RCC_LSE_ON                          ((uint32_t)0x01) /*!< LSE clock activation */
#define RCC_LSE_BYPASS                      ((uint32_t)0x02) /*!< LSE clock bypass */
#define RCC_LSE_DEFAULT                     ((uint32_t)0x03)
/**
  * @}
  */


/** @defgroup SYSCLK_Source 
  * @{
  */
#define RCC_SYSCLKSource_HSI                ((uint32_t)(0x01U << RCC_SYSCLKSEL_CLKSW_Pos))
#define RCC_SYSCLKSource_HSE                ((uint32_t)(0x02U << RCC_SYSCLKSEL_CLKSW_Pos))
#define RCC_SYSCLKSource_LSI                ((uint32_t)(0x04U << RCC_SYSCLKSEL_CLKSW_Pos))
#define RCC_SYSCLKSource_LSE                ((uint32_t)(0x08U << RCC_SYSCLKSEL_CLKSW_Pos))
/**
  * @}
  */


/** @defgroup RCC_AHBCLKDiv 
  * @{
  */
#define RCC_AHBCLKDiv1                      ((uint32_t)0x00)
#define RCC_AHBCLKDiv2                      ((uint32_t)0x01)
/**
  * @}
  */


/** @defgroup RCC_APBCLKDiv 
  * @{
  */
#define RCC_APBCLKDiv1                      ((uint32_t)0x00)
#define RCC_APBCLKDiv2                      ((uint32_t)0x01)
/**
  * @}
  */


/** @defgroup RCC_MCO_Source
  * @{
  */
#define RCC_MCOSOURCE_HSI                   ((uint32_t)(0x00U << RCC_MCOCR_MCOSEL_Pos))
#define RCC_MCOSOURCE_HSE                   ((uint32_t)(0x01U << RCC_MCOCR_MCOSEL_Pos))
#define RCC_MCOSOURCE_LSI                   ((uint32_t)(0x02U << RCC_MCOCR_MCOSEL_Pos))
#define RCC_MCOSOURCE_LSE                   ((uint32_t)(0x03U << RCC_MCOCR_MCOSEL_Pos))
#define RCC_MCOSOURCE_SYSCLK                ((uint32_t)(0x04U << RCC_MCOCR_MCOSEL_Pos))
#define RCC_MCOSOURCE_HCLK                  ((uint32_t)(0x05U << RCC_MCOCR_MCOSEL_Pos))
/**
  * @}
  */


/** @defgroup RCC_MCOHCLk_DIV
  * @{
  */
#define RCC_MCOHCLkDiv1                     ((uint32_t)0x00)
#define RCC_MCOHCLkDiv2                     ((uint32_t)0x01)
/**
  * @}
  */


/** @defgroup AHB_Peripheral 
  * @{
  */
#define RCC_AHBPeriph_GPIOA                 ((uint32_t)(0x01U << 0))
#define RCC_AHBPeriph_GPIOB                 ((uint32_t)(0x01U << 1))
#define RCC_AHBPeriph_GPIOC                 ((uint32_t)(0x01U << 2))
#define RCC_AHBPeriph_GPIOD                 ((uint32_t)(0x01U << 3))
#define RCC_AHBPeriph_CRC                   ((uint32_t)(0x01U << 4))
#define RCC_AHBPeriph_FLASH                 ((uint32_t)(0x01U << 8))
#define RCC_AHBPeriph_ALL                   ((uint32_t)0x0000011F)
/**
  * @}
  */


/** @defgroup APB_Peripheral 
  * @{
  */
#define RCC_APBPeriph_UART1                 ((uint32_t)(0x01U << 0))
#define RCC_APBPeriph_UART2                 ((uint32_t)(0x01U << 1))
#define RCC_APBPeriph_I2C                   ((uint32_t)(0x01U << 2))
#define RCC_APBPeriph_LPUART                ((uint32_t)(0x01U << 3))
#define RCC_APBPeriph_SPI                   ((uint32_t)(0x01U << 4))
#define RCC_APBPeriph_LPTIM                 ((uint32_t)(0x01U << 5))
#define RCC_APBPeriph_BASETIM               ((uint32_t)(0x01U << 6))
#define RCC_APBPeriph_SYSCON                ((uint32_t)(0x01U << 7))
#define RCC_APBPeriph_PCA                   ((uint32_t)(0x01U << 8))
#define RCC_APBPeriph_OWIRE                 ((uint32_t)(0x01U << 9))
#define RCC_APBPeriph_TIM1                  ((uint32_t)(0x01U << 10))
#define RCC_APBPeriph_TIM2                  ((uint32_t)(0x01U << 11))
#define RCC_APBPeriph_WWDG                  ((uint32_t)(0x01U << 12))
#define RCC_APBPeriph_ADC                   ((uint32_t)(0x01U << 13))
#define RCC_APBPeriph_AWK                   ((uint32_t)(0x01U << 14))
#define RCC_APBPeriph_RTC                   ((uint32_t)(0x01U << 15))
#define RCC_APBPeriph_CLKTRIM               ((uint32_t)(0x01U << 16))
#define RCC_APBPeriph_IWDG                  ((uint32_t)(0x01U << 17))
#define RCC_APBPeriph_LVDVC                 ((uint32_t)(0x01U << 18))
#define RCC_APBPeriph_BEEP                  ((uint32_t)(0x01U << 19))
#define RCC_APBPeriph_DBG                   ((uint32_t)(0x01U << 20))
#define RCC_APBPeriph_ALL                   ((uint32_t)0x001FFFFF)
/**
  * @}
  */


/** @defgroup RCC_Reset_Flag 
  * @{
  */
#define RCC_RSTFLAG_MCURST                  ((uint32_t)(0x01U << 0))
#define RCC_RSTFLAG_CPURST                  ((uint32_t)(0x01U << 1))
#define RCC_RSTFLAG_WWDGRST                 ((uint32_t)(0x01U << 2))
#define RCC_RSTFLAG_IWDGRST                 ((uint32_t)(0x01U << 3))
#define RCC_RSTFLAG_LVDRST                  ((uint32_t)(0x01U << 4))
#define RCC_RSTFLAG_PORRST                  ((uint32_t)(0x01U << 5))
#define RCC_RSTFLAG_LOCKUPRST               ((uint32_t)(0x01U << 6))
#define RCC_RSTFLAG_PADRST                  ((uint32_t)(0x01U << 7))
#define RCC_RSTFLAG_SFTRST                  ((uint32_t)(0x01U << 8))
/**
  * @}
  */


/** @defgroup RCC_HSI_Calibration_Config
  * @{
  */
#define HSI24M_TRIM_ADDR                    ((uint32_t)0x180000A0)
#define HSI22M_TRIM_ADDR                    ((uint32_t)0x180000A2)
#define HSI16M_TRIM_ADDR                    ((uint32_t)0x180000A4)
#define HSI8M_TRIM_ADDR                     ((uint32_t)0x180000A6)
#define HSI4M_TRIM_ADDR                     ((uint32_t)0x180000A8)

#define HSI24M_TC_ADDR                      ((uint32_t)0x18000090)
#define HSI22M_TC_ADDR                      ((uint32_t)0x18000092)
#define HSI16M_TC_ADDR                      ((uint32_t)0x18000094)
#define HSI8M_TC_ADDR                       ((uint32_t)0x18000096)
#define HSI4M_TC_ADDR                       ((uint32_t)0x18000098)

#define RCC_HSITRIM_24M                     (*(uint16_t *)(HSI24M_TRIM_ADDR))
#define RCC_HSITRIM_22M                     (*(uint16_t *)(HSI22M_TRIM_ADDR))
#define RCC_HSITRIM_16M                     (*(uint16_t *)(HSI16M_TRIM_ADDR))
#define RCC_HSITRIM_8M                      (*(uint16_t *)(HSI8M_TRIM_ADDR))
#define RCC_HSITRIM_4M                      (*(uint16_t *)(HSI4M_TRIM_ADDR))

#define RCC_HSITC_24M                       (*(uint16_t *)(HSI24M_TC_ADDR))
#define RCC_HSITC_22M                       (*(uint16_t *)(HSI22M_TC_ADDR))
#define RCC_HSITC_16M                       (*(uint16_t *)(HSI16M_TC_ADDR))
#define RCC_HSITC_8M                        (*(uint16_t *)(HSI8M_TC_ADDR))
#define RCC_HSITC_4M                        (*(uint16_t *)(HSI4M_TC_ADDR))

#define RCC_HSICALIBRATION_DEFAULT          ((uint32_t)0x00000312)
/**
  * @}
  */


/** @defgroup RCC_LSI_Calibration_Config
  * @{
  */
#define LSI38K_TRIM_ADDR                    ((uint32_t)0x180000B4)
#define LSI32K_TRIM_ADDR                    ((uint32_t)0x180000B0)

#define LSI38K_TC_ADDR                      ((uint32_t)0x180000BC)
#define LSI32K_TC_ADDR                      ((uint32_t)0x180000B8)

#define RCC_LSITRIM_38K                     (*(uint16_t *)(LSI38K_TRIM_ADDR))
#define RCC_LSITRIM_32K                     (*(uint16_t *)(LSI32K_TRIM_ADDR))

#define RCC_LSITC_38K                       (*(uint16_t *)(LSI38K_TC_ADDR))
#define RCC_LSITC_32K                       (*(uint16_t *)(LSI32K_TC_ADDR))

#define RCC_LSICALIBRATION_DEFAULT          0x0000007FU
/**
  * @}
  */


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define IS_HSI_VALUE(VALUE) (((VALUE) == HSI_VALUE_24M) || \
                             ((VALUE) == HSI_VALUE_22M) || \
                             ((VALUE) == HSI_VALUE_16M) || \
                             ((VALUE) == HSI_VALUE_8M) || \
                             ((VALUE) == HSI_VALUE_4M))

#define IS_LSI_VALUE(VALUE) (((VALUE) == LSI_VALUE_38K) || \
                             ((VALUE) == LSI_VALUE_32K))

#define IS_RCC_LSI_STARTUP(TIME) (((TIME) == RCC_LSI_STARTUP_4CYCLE) || \
                                  ((TIME) == RCC_LSI_STARTUP_16CYCLE) || \
                                  ((TIME) == RCC_LSI_STARTUP_64CYCLE) || \
                                  ((TIME) == RCC_LSI_STARTUP_256CYCLE))

#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || \
                         ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_BYPASS) || \
                         ((HSE) == RCC_HSE_DEFAULT))

#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || \
                         ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_BYPASS) || \
                         ((LSE) == RCC_LSE_DEFAULT))

#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSource_LSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_LSE))

#define IS_RCC_AHBCLKDiv(DIV)     (((int32_t)(DIV) > 0) && ((DIV) <= 510))

#define IS_RCC_APBCLKDiv(DIV)     (((int32_t)(DIV) > 0) && ((DIV) <= 510))

#define IS_RCC_MCO_HCLkDiv(DIV)   (((int32_t)(DIV) > 0) && ((DIV) <= 510))

#define IS_RCC_MCO_SOURCE(SOURCE) (((SOURCE) == RCC_MCOSOURCE_HSI) || \
                                   ((SOURCE) == RCC_MCOSOURCE_HSE) || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSI) || \
                                   ((SOURCE) == RCC_MCOSOURCE_LSE) || \
                                   ((SOURCE) == RCC_MCOSOURCE_SYSCLK) || \
                                   ((SOURCE) == RCC_MCOSOURCE_HCLK))

#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & RCC_AHBPeriph_ALL) != 0))

#define IS_RCC_APB_PERIPH(PERIPH) ((((PERIPH) & RCC_APBPeriph_ALL) != 0))

#define IS_RCC_RESET_FLAG(FLAG)   (((FLAG) == RCC_RSTFLAG_MCURST) || \
                                   ((FLAG) == RCC_RSTFLAG_CPURST) || \
                                   ((FLAG) == RCC_RSTFLAG_WWDGRST) || \
                                   ((FLAG) == RCC_RSTFLAG_IWDGRST) || \
                                   ((FLAG) == RCC_RSTFLAG_LVDRST) || \
                                   ((FLAG) == RCC_RSTFLAG_PORRST) || \
                                   ((FLAG) == RCC_RSTFLAG_LOCKUPRST) || \
                                   ((FLAG) == RCC_RSTFLAG_PADRST) || \
                                   ((FLAG) == RCC_RSTFLAG_SFTRST))
/* Exported functions --------------------------------------------------------*/

void RCC_DeInit(void);

void RCC_HSIConfig(uint32_t HSI_Value, FunctionalState NewState);
void RCC_LSIConfig(uint32_t LSI_Value, uint32_t LSI_StartUPTime, FunctionalState NewState);
void RCC_HSEConfig(uint32_t RCC_HSE);
void RCC_LSEConfig(uint32_t RCC_LSE);

void RCC_HSEDriveCurrentConfig(uint32_t Current);
void RCC_HSEStartTimeConfig(uint32_t Time);
void RCC_LSEDriveCurrentConfig(uint32_t Current);
void RCC_LSEStartTimeConfig(uint32_t Time);

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);
void RCC_AHBCLKConfig(uint32_t RCC_AHBCLKDiv);
void RCC_APBCLKConfig(uint32_t RCC_APBCLKDiv);

void RCC_MCOConfig(uint32_t RCC_MCOSource, uint32_t RCC_MCOHCLKDiv);
void RCC_MCOCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef *RCC_Clocks);

void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APBPeriphClockCmd(uint32_t RCC_APBPeriph, FunctionalState NewState);
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APBPeriphResetCmd(uint32_t RCC_APBPeriph, FunctionalState NewState);
void RCC_RTCPeriphResetCmd(FunctionalState NewState);

FlagStatus RCC_GetResetFlagStatus(uint32_t RCC_RSTFLAG);
void RCC_ClearResetFlags(uint32_t RCC_RSTFLAG);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_RCC_H */
