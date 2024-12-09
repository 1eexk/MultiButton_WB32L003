/**
 * @file    wb32l003_owire.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the OWIRE firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_OWIRE_H
#define __WB32L003_OWIRE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup OWIRE
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief OWIRE Init Structure definition
  */
typedef struct
{
  uint32_t ClockDiv;             /*!< Specifies the prescaler value which will be
                                      used to configure the counter clock.
                                      This parameter can be a value of @ref OWIRE_Clock_Divider */

  uint32_t FirstBit;             /*!< Specifies whether data transfers start from MSB or LSB bit.
                                       This parameter can be a value of @ref OWIRE_MSB_LSB_Transmission */

  uint32_t DataSize;             /*!< Specifies the OWIRE data size.
                                      This parameter can be a value of @ref OWIRE_Data_Size */

  uint32_t ReadMode;             /*!< Specifies if the time of reading 0 is the same as writing 0.
                                      This parameter can be a value of @ref OWIRE_Read_Mode */

  uint32_t NoiseFilterEn;        /*!< Specifies whether the filter is enabled.
                                      This parameter can be a value of @ref OWIRE_Noise_Filter_Enable */

  uint32_t NoiseFilterClk;       /*!< Specifies the clock source of the noise filter.
                                      This parameter can be a value of @ref OWIRE_Noise_Filter_Clock */

  uint32_t ResetCounter;         /*!< Specifies the Reset Counter(us) which will be
                                      used to configure the time slot of reset. */

  uint32_t PresencePulseCounter; /*!< Specifies the Presence Pulse Counter(us) which will be
                                      used to configure the time slot of presense pulse. */

  uint32_t BitRateCounter;       /*!< Specifies the Bit Rate Counter(us) which will be
                                      used to configure the bit rate. */

  uint32_t DriveCounter;         /*!< Specifies the Drive Counter(us) which will be
                                      used to configure the time slot of driving. */

  uint32_t ReadSamplingCounter;  /*!< Specifies the Read Sampling Counter(us) which will be
                                      used to configure the time slot of read sampling. */

  uint32_t RecoverCounter;       /*!< Specifies the Recover Counter(us) which will be
                                      used to configure the time slot of recovering. */
} OWIRE_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup OWIRE_Exported_Constants
  * @{
  */

/** @defgroup OWIRE_Data_Size
  * @{
  */
#define OWIRE_DATASIZE_1BIT          0x00000000U
#define OWIRE_DATASIZE_8BIT          OWIRE_CR_SIZE_Msk
/**
  * @}
  */


/** @defgroup OWIRE_MSB_LSB_Transmission
  * @{
  */
#define OWIRE_FIRSTBIT_LSB           0x00000000U
#define OWIRE_FIRSTBIT_MSB           OWIRE_CR_MSBFIRST_Msk
/**
  * @}
  */


/** @defgroup OWIRE_Clock_Divider
  * @{
  */
#define OWIRE_CLOCK_DIVIDER_1        0x00000000U
#define OWIRE_CLOCK_DIVIDER_2        (0x1U << OWIRE_CR_CLKDIV_Pos)
#define OWIRE_CLOCK_DIVIDER_4        (0x2U << OWIRE_CR_CLKDIV_Pos)
#define OWIRE_CLOCK_DIVIDER_16       (0x3U << OWIRE_CR_CLKDIV_Pos)
/**
  * @}
  */


/** @defgroup OWIRE_Read_Mode
  * @{
  */
#define OWIRE_RDMODE_0               0x00000000U
#define OWIRE_RDMODE_1               OWIRE_CR_RDMODE_Msk
/**
  * @}
  */


/** @defgroup OWIRE_Noise_Filter_Clock
  * @{
  */
#define OWIRE_NOISE_FILTER_CLK_DIV_1 0x00000000U
#define OWIRE_NOISE_FILTER_CLK_DIV_2 (0x1U << OWIRE_NFCR_NFDIV_Pos)
#define OWIRE_NOISE_FILTER_CLK_DIV_4 (0x2U << OWIRE_NFCR_NFDIV_Pos)
#define OWIRE_NOISE_FILTER_CLK_DIV_8 (0x3U << OWIRE_NFCR_NFDIV_Pos)
/**
  * @}
  */


/** @defgroup OWIRE_Noise_Filter_Enable
  * @{
  */
#define OWIRE_NOISE_FILTER_ENABLE    (0x1U << OWIRE_NFCR_NFEN_Pos)
#define OWIRE_NOISE_FILTER_DISABLE   0x00000000U
/**
  * @}
  */


/** @defgroup OWIRE_Command
  * @{
  */
#define OWIRE_COMMAND_INIT           (0x1U << OWIRE_CMD_CMD_Pos)
#define OWIRE_COMMAND_TX             (0x2U << OWIRE_CMD_CMD_Pos)
#define OWIRE_COMMAND_RX             (0x3U << OWIRE_CMD_CMD_Pos)
/**
  * @}
  */


/** @defgroup OWIRE_Flags
  * @{
  */
#define OWIRE_FLAG_ACKERROR          ((uint32_t)OWIRE_SR_ACKERR_Msk)
#define OWIRE_FLAG_INITDONE          ((uint32_t)OWIRE_SR_INITDONE_Msk)
#define OWIRE_FLAG_TXDONE            ((uint32_t)OWIRE_SR_TXDONE_Msk)
#define OWIRE_FLAG_RXDONE            ((uint32_t)OWIRE_SR_RXDONE_Msk)
/**
  * @}
  */


/** @defgroup OWIRE_Interrupt_definition
  * @{
  */
#define OWIRE_IT_ACKERROR            ((uint32_t)OWIRE_INTEN_ACKERREN_Msk)
#define OWIRE_IT_INIT                ((uint32_t)OWIRE_INTEN_INITEN_Msk)
#define OWIRE_IT_TXDONE              ((uint32_t)OWIRE_INTEN_TXDONEEN_Msk)
#define OWIRE_IT_RXDONE              ((uint32_t)OWIRE_INTEN_RXDONEEN_Msk)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void OWIRE_DeInit(void);
void OWIRE_Init(OWIRE_InitTypeDef *OWIRE_InitStruct);
void OWIRE_Cmd(FunctionalState NewState);
void OWIRE_ITConfig(uint32_t OWIRE_IT, FunctionalState NewState);
uint8_t OWIRE_ReadData(void);
void OWIRE_WriteData(uint8_t Data);
void OWIRE_WriteCommand(uint8_t Command);
FlagStatus OWIRE_GetFlagStatus(uint32_t OWIRE_FLAG);
void OWIRE_ClearFlag(uint32_t OWIRE_FLAG);
ITStatus OWIRE_GetITStatus(uint32_t OWIRE_IT);
void OWIRE_ClearITPendingBit(uint32_t OWIRE_IT);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_OWIRE_H */
