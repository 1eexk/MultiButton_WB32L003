/**
 * @file    wb32l003_i2c.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the I2C firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_I2C_H
#define __WB32L003_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  I2C Initial Configuration Structure definition
  */
typedef struct
{
  uint32_t master;            /*!< Master mode enable/disable.
                                   This parameter can be a value of @ref I2C_Master_Mode */

  uint32_t slave;             /*!< Slave mode enable/disable.
                                   This parameter can be a value of @ref I2C_Slave_Mode */

  uint32_t slaveAddr;         /*!< Slave address */

  uint32_t speedclock;        /*!< I2c speed clock set, speed=Pclk/(8*(baudcr+1)),uint khz*/

  uint32_t broadack;          /*!< Ack enable or disable when as slave.
                                   This parameter can be a value of @ref I2C_BROAD */
} I2C_InitTypeDef;


/**
  * @brief  I2CStatus enum definition
  */
typedef enum 
{
  I2C_ERROR   = 0, /*!<No i2c status flag       */
  I2C_OK      = 1, /*!<No i2c error status flag */
  I2C_SUCCESS = 2, /*!<Waited i2c status flag   */
  I2C_WAITING = 3  /*!<Waiting i2c status flag  */
} I2CStatus;

/* Exported constants --------------------------------------------------------*/

/** @defgroup I2C_Exported_Constants
  * @{
  */

/** @defgroup I2C_Master_Mode
  * @{
  */
#define I2C_MASTER_MODE_DISABLE         ((uint32_t)0x00000000U)
#define I2C_MASTER_MODE_ENABLE          ((uint32_t)0x00000001U)

#define IS_I2C_MASTER_MODE(MASTER_MODE) (((MASTER_MODE) == I2C_MASTER_MODE_DISABLE) ||\
                                         ((MASTER_MODE) == I2C_MASTER_MODE_ENABLE))
/**
  * @}
  */

/** @defgroup I2C_Slave_Mode
  * @{
  */
#define I2C_SLAVE_MODE_ENABLE           ((uint32_t)0x00000000U)
#define I2C_SLAVE_MODE_DISABLE          ((uint32_t)0x00000001U)

#define IS_I2C_SLAVE_MODE(SLAVE_MODE)   (((SLAVE_MODE) == I2C_SLAVE_MODE_ENABLE) || \
                                         ((SLAVE_MODE) == I2C_SLAVE_MODE_DISABLE))
/**
  * @}
  */

/** @defgroup I2C_BROAD
  * @{
  */
#define I2C_BROAD_ACK_ENABLE            ((uint32_t)0x00000000U)
#define I2C_BROAD_ACK_DISABLE           ((uint32_t)0x00000001U)

#define IS_I2C_BROAD_ACK(BROAD_ACK)     (((BROAD_ACK) == I2C_BROAD_ACK_ENABLE) ||\
                                         ((BROAD_ACK) == I2C_BROAD_ACK_DISABLE))
/**
  * @}
  */

/** @defgroup I2C_HIGH_RATE
  * @{
  */
#define I2C_HIGH_RATE_ENABLE            ((uint32_t)0x00000000U)
#define I2C_HIGH_RATE_DISABLE           I2C_CR_H1M
/**
  * @}
  */

/** @defgroup I2C_Direction_definition
  * @{
  */
#define I2C_Direction_Transmitter       ((uint8_t)0x00)
#define I2C_Direction_Receiver          ((uint8_t)0x01)

#define IS_I2C_DIRECTION(I2C_Direction) (((I2C_Direction) == I2C_Direction_Transmitter) || \
                                         ((I2C_Direction) == I2C_Direction_Receiver))
/**
  * @}
  */

/** @defgroup I2C_Status_Switching_definition
  * @{
  */
#define I2C_STA_0                       ((uint8_t)(0x00))
#define I2C_STA_1                       ((uint8_t)(0x01 << 5))
#define I2C_STO_0                       ((uint8_t)(0x00))
#define I2C_STO_1                       ((uint8_t)(0x01 << 4))
#define I2C_AA_0                        ((uint8_t)(0x00))
#define I2C_AA_1                        ((uint8_t)(0x01 << 2))
#define I2C_CR_Status_Mask              ((uint8_t)(0xC3))

#define IS_I2C_STA(I2C_STA)             (((I2C_STA) == I2C_STA_0) || ((I2C_STA) == I2C_STA_1))
#define IS_I2C_STO(I2C_STO)             (((I2C_STO) == I2C_STO_0) || ((I2C_STO) == I2C_STO_1))
#define IS_I2C_AA(I2C_AA)               (((I2C_AA) == I2C_AA_0) || ((I2C_AA) == I2C_AA_1))
/**
  * @}
  */

/** @defgroup I2C_Flag_definition
  * @{
  */
#define I2C_FLAG_ERROR_UNDER            ((uint32_t)0x00000000U)
#define I2C_FLAG_USELESS                ((uint32_t)0x000000F8U)

#define I2C_FLAG_MASTER_TX_START        ((uint32_t)0x00000008U)
#define I2C_FLAG_MASTER_TX_RESTART      ((uint32_t)0x00000010U)
#define I2C_FLAG_MASTER_TX_SLAW_ACK     ((uint32_t)0x00000018U)
#define I2C_FLAG_MASTER_TX_SLAW_NOACK   ((uint32_t)0x00000020U)
#define I2C_FLAG_MASTER_TX_DATA_ACK     ((uint32_t)0x00000028U)
#define I2C_FLAG_MASTER_TX_DATA_NOACK   ((uint32_t)0x00000030U)
#define I2C_FLAG_MASTER_TX_LOST_SCL     ((uint32_t)0x00000038U)

#define I2C_FLAG_MASTER_RX_START        ((uint32_t)0x00000008U)
#define I2C_FLAG_MASTER_RX_RESTART      ((uint32_t)0x00000010U)
#define I2C_FLAG_MASTER_RX_SLAW_ACK     ((uint32_t)0x00000040U)
#define I2C_FLAG_MASTER_RX_SLAW_NOACK   ((uint32_t)0x00000048U)
#define I2C_FLAG_MASTER_RX_DATA_ACK     ((uint32_t)0x00000050U)
#define I2C_FLAG_MASTER_RX_DATA_NOACK   ((uint32_t)0x00000058U)
#define I2C_FLAG_MASTER_RX_LOST_SCL     ((uint32_t)0x00000038U)

#define I2C_FLAG_SLAVE_TX_SLAW_ACK      ((uint32_t)0x000000A8U)
#define I2C_FLAG_SLAVE_TX_DATA_ACK      ((uint32_t)0x000000B8U)
#define I2C_FLAG_SLAVE_TX_DATA_NOACK    ((uint32_t)0x000000C0U)
#define I2C_FLAG_SLAVE_TX_DATA_LAST     ((uint32_t)0x000000C8U)
#define I2C_FLAG_SLAVE_TX_LOST_SCL      ((uint32_t)0x000000B0U)

#define I2C_FLAG_SLAVE_RX_SLAW_ACK      ((uint32_t)0x00000060U)
#define I2C_FLAG_SLAVE_RX_BROAD_ACK     ((uint32_t)0x00000070U)
#define I2C_FLAG_SLAVE_RX_SDATA_ACK     ((uint32_t)0x00000080U)
#define I2C_FLAG_SLAVE_RX_SDATA_NOACK   ((uint32_t)0x00000088U)
#define I2C_FLAG_SLAVE_RX_BDATA_ACK     ((uint32_t)0x00000090U)
#define I2C_FLAG_SLAVE_RX_BDATA_NOACK   ((uint32_t)0x00000098U)
#define I2C_FLAG_SLAVE_RX_SA_LOST_SCL   ((uint32_t)0x00000068U)
#define I2C_FLAG_SLAVE_RX_BA_LOST_SCL   ((uint32_t)0x00000078U)
#define I2C_FLAG_SLAVE_STOP_RESTART     ((uint32_t)0x000000A0U)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void I2C_DeInit(void);
void I2C_Init(I2C_InitTypeDef *I2C_InitStruct);
void I2C_SlaveAddressConfig(uint32_t SlaveAddress);
void I2C_HighSpeedModeCmd(FunctionalState NewState);
void I2C_SwitchStatus(uint8_t I2C_STA, uint8_t I2C_STO, uint8_t I2C_AA);
void I2C_Start(FunctionalState NewState);
void I2C_Stop(FunctionalState NewState);
void I2C_ACK(FunctionalState NewState);
void I2C_Cmd(FunctionalState NewState);
void I2C_AckGeneralCallCmd(FunctionalState NewState);
void I2C_ReceiveByte(uint8_t *pData);
void I2C_WriteByte(uint8_t I2C_DataCmd);
void I2C_WriteAddress(uint8_t Address, uint8_t I2C_Direction);
I2CStatus I2C_CheckFlag(uint32_t *I2C_Flag);
ITStatus I2C_GetITStatus(void);
void I2C_ClearITPendingBit(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_I2C_H */
