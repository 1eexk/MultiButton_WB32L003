/**
 * @file    wb32l003_syscon.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the SYSCON firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_SYSCON_H
#define __WB32L003_SYSCON_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSCON
  * @brief SYSCON driver modules
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup SYSCON_Exported_Constants
  * @{
  */

#define SYSCON_KEY_UNLOCK        (0x5A69)

#define SYSCON_DEFAULT           (0x00U)
#define SYSCON_UART1_RXD         (0x01U)
#define SYSCON_UART2_RXD         (0x02U)
#define SYSCON_LPUART_RXD        (0x03U)
#define SYSCON_LSI               (0x04U)

#define SYSCON_SPINCS_SEL_0      (0x01U << 0)
#define SYSCON_SPINCS_SEL_1      (0x01U << 1)
#define SYSCON_SPINCS_SEL_2      (0x01U << 2)
#define SYSCON_SPINCS_SEL_3      (0x01U << 3)
#define SYSCON_SPINCS_SEL_4      (0x01U << 10)

#define SYSCON_TIMETR_SEL_0      (0x01U << 16)
#define SYSCON_TIMETR_SEL_1      (0x01U << 17)
#define SYSCON_TIMETR_SEL_2      (0x01U << 18)
#define SYSCON_TIMETR_SEL_3      (0x01U << 19)
#define SYSCON_TIMETR_SEL_4      (0x01U << 23)

#define SYSCON_TIM_ETR_LOWLEVEL  (0x00000000U)
#define SYSCON_TIM_ETR_PA1       (SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PA2       (SYSCON_TIMETR_SEL_1)
#define SYSCON_TIM_ETR_PA3       (SYSCON_TIMETR_SEL_1 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PB4       (SYSCON_TIMETR_SEL_2)
#define SYSCON_TIM_ETR_PB5       (SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PC3       (SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_1)
#define SYSCON_TIM_ETR_PC4       (SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_1 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PC5       (SYSCON_TIMETR_SEL_3)
#define SYSCON_TIM_ETR_PC6       (SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PC7       (SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_1)
#define SYSCON_TIM_ETR_PD1       (SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_1 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PD2       (SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_2)
#define SYSCON_TIM_ETR_PD3       (SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PD4       (SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_1)
#define SYSCON_TIM_ETR_PD6       (SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_1 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PA4       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PB0       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_1)
#define SYSCON_TIM_ETR_PB1       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_1 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PB2       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_2)
#define SYSCON_TIM_ETR_PB3       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PB6       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_1)
#define SYSCON_TIM_ETR_PB7       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_2 | SYSCON_TIMETR_SEL_1 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PC0       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_3)
#define SYSCON_TIM_ETR_PC1       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PC2       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_1)
#define SYSCON_TIM_ETR_PD0       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_1 | SYSCON_TIMETR_SEL_0)
#define SYSCON_TIM_ETR_PD7       (SYSCON_TIMETR_SEL_4 | SYSCON_TIMETR_SEL_3 | SYSCON_TIMETR_SEL_2)

#define SYSCON_SPI_NCS_HIGHLEVEL (0x00000000U)
#define SYSCON_SPI_NCS_PA1       (SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PA2       (SYSCON_SPINCS_SEL_1)
#define SYSCON_SPI_NCS_PA3       (SYSCON_SPINCS_SEL_1 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PB4       (SYSCON_SPINCS_SEL_2)
#define SYSCON_SPI_NCS_PB5       (SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PC3       (SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_1)
#define SYSCON_SPI_NCS_PC4       (SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_1 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PC5       (SYSCON_SPINCS_SEL_3)
#define SYSCON_SPI_NCS_PC6       (SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PC7       (SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_1)
#define SYSCON_SPI_NCS_PD1       (SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_1 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PD2       (SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_2)
#define SYSCON_SPI_NCS_PD3       (SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PD4       (SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_1)
#define SYSCON_SPI_NCS_PD6       (SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_1 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PA4       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PB0       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_1)
#define SYSCON_SPI_NCS_PB1       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_1 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PB2       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_2)
#define SYSCON_SPI_NCS_PB3       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PB6       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_1)
#define SYSCON_SPI_NCS_PB7       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_2 | SYSCON_SPINCS_SEL_1 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PC0       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_3)
#define SYSCON_SPI_NCS_PC1       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PC2       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_1)
#define SYSCON_SPI_NCS_PD0       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_1 | SYSCON_SPINCS_SEL_0)
#define SYSCON_SPI_NCS_PD7       (SYSCON_SPINCS_SEL_4 | SYSCON_SPINCS_SEL_3 | SYSCON_SPINCS_SEL_2)

#define SYSCON_CLKFAILBRKEN      SYSCON_TIM1CR_CLKFAILBRKEN
#define SYSCON_DSLPBRKEN         SYSCON_TIM1CR_DSLPBRKEN

#define SYSCON_OCOUT_LOWLEVEL    SYSCON_TIM1CR_TIM1BRKOUTCFG
#define SYSCON_OCOUT_BYTIM1      (0x00U)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define SYSCON_REGWR_LOCK()   (SYSCON->UNLOCK = (0x2AD5334C << SYSCON_UNLOCK_KEY_Pos) & SYSCON_UNLOCK_KEY)
#define SYSCON_REGWR_UNLOCK() (SYSCON->UNLOCK = SYSCON_UNLOCK_UNLOCK | (0x2AD5334C << SYSCON_UNLOCK_KEY_Pos))

/** @brief Macro to disable deep sleep mode in debug mode, allow to debug deep sleep mode.
  * @note  In debug mode, CPU will not enter deep sleep mode
  */
#define SYSCON_DBGDEEPSLEEP_ENABLE()                                                                \
  do {                                                                                              \
    SYSCON_REGWR_UNLOCK();                                                                          \
    SET_BIT(SYSCON->CFGR0, SYSCON_CFGR0_DBGDLSP_DIS | (SYSCON_CFGR0_KEY << SYSCON_CFGR0_KEY_Pos));  \
    SYSCON_REGWR_LOCK();                                                                            \
  } while (0)

/** @brief Macro to enable deep sleep mode in debug mode, debug mode will quit in deep sleep mode.
  * @note  In debug mode, deep sleep mode will make debug mode quit
  */
#define SYSCON_DBGDEEPSLEEP_DISABLE()                                                                  \
  do {                                                                                                 \
    SYSCON_REGWR_UNLOCK();                                                                             \
    CLEAR_WPBIT(SYSCON->CFGR0, SYSCON_CFGR0_DBGDLSP_DIS, (SYSCON_CFGR0_KEY << SYSCON_CFGR0_KEY_Pos));  \
    SYSCON_REGWR_LOCK();                                                                               \
  } while (0)

/** @brief Macro to enable cpu lock up function.
  */
#define SYSCON_LOCKUP_ENABLE()                                                                   \
  do {                                                                                           \
    SYSCON_REGWR_UNLOCK();                                                                       \
    SET_BIT(SYSCON->CFGR0, SYSCON_CFGR0_LOCKUPEN | (SYSCON_CFGR0_KEY << SYSCON_CFGR0_KEY_Pos));  \
    SYSCON_REGWR_LOCK();                                                                         \
  } while (0)

/** @brief Macro to disable cpu lock up function.
  */
#define SYSCON_LOCKUP_DISABLE()                                                                     \
  do {                                                                                              \
    SYSCON_REGWR_UNLOCK();                                                                          \
    CLEAR_WPBIT(SYSCON->CFGR0, SYSCON_CFGR0_LOCKUPEN, (SYSCON_CFGR0_KEY << SYSCON_CFGR0_KEY_Pos));  \
    SYSCON_REGWR_LOCK();                                                                            \
  } while (0)

/** @brief Macro to config PAD interrupt mode as AUTO for deep sleep:.
  */
#define SYSCON_DEEPSLEEP_PADINT_AUTO()                                                                            \
  do {                                                                                                            \
    SYSCON_REGWR_UNLOCK();                                                                                        \
    CLEAR_WPBIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADDLSPCON, (SYSCON_UNLOCK_KEY << SYSCON_PORTINTCR_KEY_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                          \
  } while (0)

/** @brief Macro to config PAD interrupt mode as ACTIVE for deep sleep.
  */
#define SYSCON_DEEPSLEEP_PADINT_ACTIVE()                                                                         \
  do {                                                                                                           \
    SYSCON_REGWR_UNLOCK();                                                                                       \
    SET_BIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADDLSPCON | (SYSCON_UNLOCK_KEY << SYSCON_PORTINTCR_KEY_Pos));   \
    CLEAR_WPBIT(SYSCON->PORTINTCR, SYSCON_PORTINTCR_PADINTSEL, (SYSCON_UNLOCK_KEY << SYSCON_PORTINTCR_KEY_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                         \
  } while (0)

/** @brief Macro to select low power timer gate signal input source from gpio.
  * @param SOURCE: source for LPTIM gate input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: LPTIM_GATE alternate function is low power timer gate signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is low power timer gate signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is low power timer gate signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is low power timer gate signal input source
  */
#define SYSCON_LPTIM_GATE(SOURCE)                                                                             \
  do {                                                                                                        \
    SYSCON_REGWR_UNLOCK();                                                                                    \
    MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_LPTIM_GATE_SEL, ((SOURCE) << SYSCON_PORTCR_LPTIM_GATE_SEL_Pos)); \
    SYSCON_REGWR_UNLOCK();                                                                                    \
  } while (0)

/** @brief Macro to select timer11 gate signal input source from gpio.
  * @param SOURCE: source for TIM11 gate input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM11_GATE alternate function is timer11 gate signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is timer11 gate signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is timer11 gate signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is timer11 gate signal input source
  */
#define SYSCON_TIM11_GATE(SOURCE)                                                                             \
  do {                                                                                                        \
    SYSCON_REGWR_UNLOCK();                                                                                    \
    MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_TIM11_GATE_SEL, ((SOURCE) << SYSCON_PORTCR_TIM11_GATE_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                      \
  } while (0)

/** @brief Macro to select timer10 gate signal input source from gpio.
  * @param SOURCE: source for TIM10 gate input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM10_GATE alternate function is timer10 gate signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is timer10 gate signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is timer10 gate signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is timer10 gate signal input source
  */
#define SYSCON_TIM10_GATE(SOURCE)                                                                             \
  do {                                                                                                        \
    SYSCON_REGWR_UNLOCK();                                                                                    \
    MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_TIM10_GATE_SEL, ((SOURCE) << SYSCON_PORTCR_TIM10_GATE_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                      \
  } while (0)

/** @brief Macro to select spi slave mode NCS signal input source from gpio.
  * @param SOURCE: source for spi NCS signal input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_SPI_NCS_HIGHLEVEL: high level is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PA1: PA1 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PA2: PA2 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PA3: PA3 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PB4: PB4 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PB5: PB5 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PC3: PC3 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PC4: PC4 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PC5: PC5 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PC6: PC6 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PC7: PC7 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PD1: PD1 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PD2: PD2 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PD3: PD3 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PD4: PD4 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PD6: PD6 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PA4: PA4 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PB0: PB0 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PB1: PB1 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PB2: PB2 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PB3: PB3 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PB6: PB6 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PB7: PB7 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PC0: PC0 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PC1: PC1 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PC2: PC2 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PD0: PD0 is spi NCS input source
  *        @arg @ref SYSCON_SPI_NCS_PD7: PD7 is spi NCS input source
  */
#define SYSCON_SPINCS(SOURCE)                                       \
  do {                                                              \
    SYSCON_REGWR_UNLOCK();                                          \
    MODIFY_REG(SYSCON->PORTCR, SYSCON_PORTCR_SPINCS_SEL, (SOURCE)); \
    SYSCON_REGWR_LOCK();                                            \
  } while (0)

/** @brief Macro to select pca cap4 signal input source from gpio.
  * @param SOURCE: source for pca cap4 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: PCA_CH4 alternate function is pca cap4 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap4 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is pca cap4 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap4 signal input source
  */
#define SYSCON_PCA_CAP4(SOURCE)                                                                        \
  do {                                                                                                 \
    SYSCON_REGWR_UNLOCK();                                                                             \
    MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP4_SEL, ((SOURCE) << SYSCON_PCACR_PCA_CAP4_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                               \
  } while (0)

/** @brief Macro to select pca cap3 signal input source from gpio.
  * @param SOURCE: source for pca cap3 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: PCA_CH3 alternate function is pca cap3 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap3 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is pca cap3 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap3 signal input source
  */
#define SYSCON_PCA_CAP3(SOURCE)                                                                        \
  do {                                                                                                 \
    SYSCON_REGWR_UNLOCK();                                                                             \
    MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP3_SEL, ((SOURCE) << SYSCON_PCACR_PCA_CAP3_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                               \
  } while (0)

/** @brief Macro to select pca cap2 signal input source from gpio.
  * @param SOURCE: source for pca cap2 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: PCA_CH2 alternate function is pca cap2 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap2 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is pca cap2 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap2 signal input source
  */
#define SYSCON_PCA_CAP2(SOURCE)                                                                        \
  do {                                                                                                 \
    SYSCON_REGWR_UNLOCK();                                                                             \
    MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP2_SEL, ((SOURCE) << SYSCON_PCACR_PCA_CAP2_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                               \
  } while (0)

/** @brief Macro to select pca cap1 signal input source from gpio.
  * @param SOURCE: source for pca cap1 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: PCA_CH1 alternate function is pca cap1 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap1 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is pca cap1 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap1 signal input source
  */
#define SYSCON_PCA_CAP1(SOURCE)                                                                        \
  do {                                                                                                 \
    SYSCON_REGWR_UNLOCK();                                                                             \
    MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP1_SEL, ((SOURCE) << SYSCON_PCACR_PCA_CAP1_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                               \
  } while (0)

/** @brief Macro to select pca cap0 signal input source from gpio.
  * @param SOURCE: source for pca cap0 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: PCA_CH0 alternate function is pca cap0 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is pca cap0 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is pca cap0 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is pca cap0 signal input source
  */
#define SYSCON_PCA_CAP0(SOURCE)                                                                        \
  do {                                                                                                 \
    SYSCON_REGWR_UNLOCK();                                                                             \
    MODIFY_REG(SYSCON->PCACR, SYSCON_PCACR_PCA_CAP0_SEL, ((SOURCE) << SYSCON_PCACR_PCA_CAP0_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                               \
  } while (0)

/** @brief Macro to select timer1 break signal input source from other peripheral.
  * @param SOURCE: source for timer1 break signal input
  *        This parameter can be any combination the following values:
  *        @arg @ref SYSCON_CLKFAILBRKEN: clock fail is timer1 break signal input source
  *        @arg @ref SYSCON_DSLPBRKEN: deep sleep is timer1 break signal input source
  */
#define SYSCON_TIM1_BREAKIN_SEL(SOURCE)                                                         \
  do {                                                                                          \
    SYSCON_REGWR_UNLOCK();                                                                      \
    MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_CLKFAILBRKEN | SYSCON_TIM1CR_DSLPBRKEN, (SOURCE)); \
    SYSCON_REGWR_LOCK();                                                                        \
  } while (0)

/** @brief Macro to configure timer1 ocxp/ocxnp output signal when break.
  * @param CONFIG: config ocxp/ocxnp output signal when break received
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_OCOUT_LOWLEVEL: ocxp/ocxnp output low level when break received
  *        @arg @ref SYSCON_OCOUT_BYTIM1: ocxp/ocxnp output controlled by timer1 configuration when break received
  */
#define SYSCON_TIM1_BREAKOUT_CFG(CONFIG)                               \
  do {                                                                 \
    SYSCON_REGWR_UNLOCK();                                             \
    MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1BRKOUTCFG, (CONFIG)); \
    SYSCON_REGWR_LOCK();                                               \
  } while (0)

/** @brief Macro to select timer1 etr signal input source from gpio.
  * @param SOURCE: source for timer1 etr input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_TIM_ETR_LOWLEVEL: low level is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PA1: PA1 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PA2: PA2 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PA3: PA3 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB4: PB4 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB5: PB5 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC3: PC3 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC4: PC4 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC5: PC5 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC6: PC6 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC7: PC7 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD1: PD1 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD2: PD2 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD3: PD3 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD4: PD4 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD6: PD6 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PA4: PA4 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB0: PB0 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB1: PB1 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB2: PB2 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB3: PB3 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB6: PB6 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB7: PB7 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC0: PC0 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC1: PC1 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC2: PC2 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD0: PD0 is timer1 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD7: PD7 is timer1 etr input source
  */
#define SYSCON_TIM1ETR_SEL(SOURCE)                                   \
  do {                                                               \
    SYSCON_REGWR_UNLOCK();                                           \
    MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1ETR_SEL, (SOURCE)); \
    SYSCON_REGWR_LOCK();                                             \
  } while (0)

/** @brief Macro to select tim1 ch4 signal input source from gpio.
  * @param SOURCE: source for tim1 ch4 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM1_CH4 alternate function is tim1 ch4 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is tim1 ch4 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is tim1 ch4 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch4 signal input source
  *        @arg @ref SYSCON_LSI: LSI is tim1 ch4 signal input source
  */
#define SYSCON_TIM1CH4IN_SEL(SOURCE)                                                                        \
  do {                                                                                                      \
    SYSCON_REGWR_UNLOCK();                                                                                  \
    MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1CH4IN_SEL, ((SOURCE) << SYSCON_TIM1CR_TIM1CH4IN_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                    \
  } while (0)

/** @brief Macro to select tim1 ch3 signal input source from gpio.
  * @param SOURCE: source for tim1 ch3 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM1_CH3 alternate function is tim1 ch3 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is tim1 ch3 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is tim1 ch3 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch3 signal input source
  *        @arg @ref SYSCON_LSI: LSI is tim1 ch3 signal input source
  */
#define SYSCON_TIM1CH3IN_SEL(SOURCE)                                                                        \
  do {                                                                                                      \
    SYSCON_REGWR_UNLOCK();                                                                                  \
    MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1CH3IN_SEL, ((SOURCE) << SYSCON_TIM1CR_TIM1CH3IN_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                    \
  } while (0)

/** @brief Macro to select tim1 ch2 signal input source from gpio.
  * @param SOURCE: source for tim1 ch2 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM1_CH2 alternate function is tim1 ch2 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is tim1 ch2 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is tim1 ch2 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch2 signal input source
  *        @arg @ref SYSCON_LSI: LSI is tim1 ch2 signal input source
  */
#define SYSCON_TIM1CH2IN_SEL(SOURCE)                                                                        \
  do {                                                                                                      \
    SYSCON_REGWR_UNLOCK();                                                                                  \
    MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1CH2IN_SEL, ((SOURCE) << SYSCON_TIM1CR_TIM1CH2IN_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                    \
  } while (0)

/** @brief Macro to select tim1 ch1 signal input source from gpio.
  * @param SOURCE: source for tim1 ch1 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM1_CH1 alternate function is tim1 ch1 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is tim1 ch1 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is tim1 ch1 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim1 ch1 signal input source
  *        @arg @ref SYSCON_LSI: LSI is tim1 ch1 signal input source
  */
#define SYSCON_TIM1CH1IN_SEL(SOURCE)                                                                        \
  do {                                                                                                      \
    SYSCON_REGWR_UNLOCK();                                                                                  \
    MODIFY_REG(SYSCON->TIM1CR, SYSCON_TIM1CR_TIM1CH1IN_SEL, ((SOURCE) << SYSCON_TIM1CR_TIM1CH1IN_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                    \
  } while (0)

/** @brief Macro to select timer2 etr signal input source from gpio.
  * @param SOURCE: source for timer2 etr input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_TIM_ETR_LOWLEVEL: low level is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PA1: PA1 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PA2: PA2 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PA3: PA3 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB4: PB4 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB5: PB5 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC3: PC3 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC4: PC4 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC5: PC5 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC6: PC6 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC7: PC7 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD1: PD1 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD2: PD2 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD3: PD3 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD4: PD4 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD6: PD6 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PA4: PA4 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB0: PB0 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB1: PB1 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB2: PB2 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB3: PB3 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB6: PB6 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PB7: PB7 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC0: PC0 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC1: PC1 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PC2: PC2 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD0: PD0 is timer2 etr input source
  *        @arg @ref SYSCON_TIM_ETR_PD7: PD7 is timer2 etr input source
  */
#define SYSCON_TIM2ETR_SEL(SOURCE)                                   \
  do {                                                               \
    SYSCON_REGWR_UNLOCK();                                           \
    MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2ETR_SEL, (SOURCE)); \
    SYSCON_REGWR_LOCK();                                             \
  } while (0)

/** @brief Macro to select tim2 ch4 signal input source from gpio.
  * @param SOURCE: source for tim2 ch4 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM2_CH4 alternate function is tim2 ch4 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is tim2 ch4 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is tim2 ch4 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch4 signal input source
  *        @arg @ref SYSCON_LSI: LSI is tim2 ch4 signal input source
  */
#define SYSCON_TIM2CH4IN_SEL(SOURCE)                                                                        \
  do {                                                                                                      \
    SYSCON_REGWR_UNLOCK();                                                                                  \
    MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2CH4IN_SEL, ((SOURCE) << SYSCON_TIM2CR_TIM2CH4IN_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                    \
  } while (0)

/** @brief Macro to select tim2 ch3 signal input source from gpio.
  * @param SOURCE: source for tim2 ch3 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM2_CH3 alternate function is tim2 ch3 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is tim2 ch3 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is tim2 ch3 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch3 signal input source
  *        @arg @ref SYSCON_LSI: LSI is tim2 ch3 signal input source
  */
#define SYSCON_TIM2CH3IN_SEL(SOURCE)                                                                        \
  do {                                                                                                      \
    SYSCON_REGWR_UNLOCK();                                                                                  \
    MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2CH3IN_SEL, ((SOURCE) << SYSCON_TIM2CR_TIM2CH3IN_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                    \
  } while (0)

/** @brief Macro to select tim2 ch2 signal input source from gpio.
  * @param SOURCE: source for tim2 ch2 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM2_CH2 alternate function is tim2 ch2 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is tim2 ch2 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is tim2 ch2 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch2 signal input source
  *        @arg @ref SYSCON_LSI: LSI is tim2 ch2 signal input source
  */
#define SYSCON_TIM2CH2IN_SEL(SOURCE)                                                                        \
  do {                                                                                                      \
    SYSCON_REGWR_UNLOCK();                                                                                  \
    MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2CH2IN_SEL, ((SOURCE) << SYSCON_TIM2CR_TIM2CH2IN_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                    \
  } while (0)

/** @brief Macro to select tim2 ch1 signal input source from gpio.
  * @param SOURCE: source for tim2 ch1 input
  *        This parameter can be one of the following values:
  *        @arg @ref SYSCON_DEFAULT: TIM2_CH1 alternate function is tim2 ch1 signal input source
  *        @arg @ref SYSCON_UART1_RXD: UART1_RXD alternate function is tim2 ch1 signal input source
  *        @arg @ref SYSCON_UART2_RXD: UART2_RXD alternate function is tim2 ch1 signal input source
  *        @arg @ref SYSCON_LPUART_RXD: LPUART_RXD alternate function is tim2 ch1 signal input source
  *        @arg @ref SYSCON_LSI: LSI is tim2 ch1 signal input source
  */
#define SYSCON_TIM2CH1IN_SEL(SOURCE)                                                                        \
  do {                                                                                                      \
    SYSCON_REGWR_UNLOCK();                                                                                  \
    MODIFY_REG(SYSCON->TIM2CR, SYSCON_TIM2CR_TIM2CH1IN_SEL, ((SOURCE) << SYSCON_TIM2CR_TIM2CH1IN_SEL_Pos)); \
    SYSCON_REGWR_LOCK();                                                                                    \
  } while (0)

/* Exported functions --------------------------------------------------------*/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_SYSCON_H */
