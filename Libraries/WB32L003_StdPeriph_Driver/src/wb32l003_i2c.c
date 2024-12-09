/**
 * @file    wb32l003_i2c.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the I2C firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_i2c.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C
  * @brief I2C driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup I2C_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the I2C peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void I2C_DeInit(void)
{
  RCC_APBPeriphResetCmd(RCC_APBPeriph_I2C, ENABLE);
  RCC_APBPeriphResetCmd(RCC_APBPeriph_I2C, DISABLE);
}

/**
  * @brief  Initializes the I2C peripheral according to the specified 
  *         parameters in the I2C_InitStruct.
  * @param  I2C_InitStruct: Pointer to I2C initialization structure.
  * @retval None
  */
void I2C_Init(I2C_InitTypeDef *I2C_InitStruct)
{
  RCC_ClocksTypeDef RCC_Clocks;
  uint32_t tmpcon = 0;

  /* Check the parameters */
  assert_param(IS_I2C_SLAVE_MODE(I2C_InitStruct->slave));
  assert_param(IS_I2C_MASTER_MODE(I2C_InitStruct->master));
  assert_param(IS_I2C_BROAD_ACK(I2C_InitStruct->broadack));

  /* Disable I2C peripheral */
  I2C->CR &= ~I2C_CR_ENS;

  /* Set I2C baud rate */
  
  RCC_GetClocksFreq(&RCC_Clocks);
  tmpcon = RCC_Clocks.APBCLK_Frequency / 1000;
  tmpcon = (uint32_t)((tmpcon - ((I2C_InitStruct->speedclock) << 3)) / ((I2C_InitStruct->speedclock) << 3));

  if (I2C_InitStruct->slave != I2C_SLAVE_MODE_DISABLE)
  {
    I2C->CR |= I2C_CR_AA;
    I2C->ADDR |= (uint8_t)(I2C_InitStruct->slaveAddr << 0x01);

    /* General call configuration */
    if (I2C_InitStruct->broadack != I2C_BROAD_ACK_DISABLE)
      I2C->ADDR |= I2C_ADDR_GC;
    else
      I2C->ADDR &= ~I2C_ADDR_GC;
  }
  else
  {
    I2C->CR &= ~I2C_CR_AA;
  }

  if (I2C_InitStruct->master != I2C_MASTER_MODE_DISABLE)
  {
    I2C->BAUDCR = tmpcon & I2C_BAUDCR_TM;
    I2C->TIMRUN |= I2C_TIMRUN_TME;
  }

  /* I2C high speed mode configuration */
  if (I2C_InitStruct->speedclock < 400)
    I2C->CR &= ~I2C_CR_H1M;
  else
    I2C->CR |= I2C_CR_H1M;
}

/**
  * @brief  Configures the I2C slave address.
  * @param  SlaveAddress: specifies the I2C slave address.
  * @retval None
  */
void I2C_SlaveAddressConfig(uint32_t SlaveAddress)
{
  I2C->ADDR = (uint32_t)(0xFF & (SlaveAddress << 1));
}

/**
  * @brief  Configures I2C high speed mode.
  * @param  NewState: The new state of the I2C high speed mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_HighSpeedModeCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    I2C->CR |= I2C_CR_H1M;
  }
  else
  {
    I2C->CR &= ~I2C_CR_H1M;
  }
}

/**
  * @brief  Writes I2C CR register for switching I2C bus status.
  * @param  I2C_STA: The new state of the I2C start status.
  *         This parameter can be: I2C_STA_0 or I2C_STA_1.
  * @param  I2C_STO: The new state of the I2C stop status.
  *         This parameter can be: I2C_STO_0 or I2C_STO_1.
  * @param  I2C_AA: The new state of the I2C ack status.
  *         This parameter can be: I2C_AA_0 or I2C_AA_1.
  * @note   This function will clear SI bit of CR register, 
  *         and you should switch I2C status accoring to description of user manual.
  * @retval None
  */
void I2C_SwitchStatus(uint8_t I2C_STA, uint8_t I2C_STO, uint8_t I2C_AA)
{
  /* Check the parameters */
  assert_param(IS_I2C_STA(I2C_STA));
  assert_param(IS_I2C_STO(I2C_STO));
  assert_param(IS_I2C_AA(I2C_AA));

  uint32_t temp_reg = I2C->CR;
  
  /* Clear CR configuration for switching status */
  temp_reg &= I2C_CR_Status_Mask;
  
  /* Write CR register */
  temp_reg |= (I2C_STA | I2C_STO | I2C_AA);

  /* Update CR register */
  I2C->CR = temp_reg;
}

/**
  * @brief  Sets or clears I2C peripheral start status.
  * @param  NewState: The new state of the I2C start status.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Start(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    I2C->CR |= I2C_CR_STA;
  }
  else
  {
    I2C->CR &= ~I2C_CR_STA;
  }
}

/**
  * @brief  Sets or clears I2C peripheral stop status.
  * @param  NewState: The new state of the I2C stop status.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Stop(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    I2C->CR |= I2C_CR_STO;
    I2C->CR &= ~I2C_CR_SI;
  }
  else
  {
    I2C->CR &= ~I2C_CR_STO;
  }
}

/**
  * @brief  Sets or clears I2C peripheral ACK status.
  * @param  NewState: The new state of the I2C ack status.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ACK(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    I2C->CR |= I2C_CR_AA;
  }
  else
  {
    I2C->CR &= ~I2C_CR_AA;
  }
}

/**
  * @brief  Enables or disables I2C peripheral.
  * @param  NewState: The new state of the I2C peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    I2C->CR |= I2C_CR_ENS;
  }
  else
  {
    I2C->CR &= ~I2C_CR_ENS;
  }
}

/**
  * @brief  Enables or disables the general ack.
  * @param  NewState: The new state of the general ack function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_AckGeneralCallCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    I2C->ADDR |= I2C_ADDR_GC;
  }
  else
  {
    I2C->ADDR &= (~I2C_ADDR_GC);
  }
}

/**
  * @brief  Reads data from data register.
  * @param  pData: pointer to reveive date buffer.
  * @retval None
  */
void I2C_ReceiveByte(uint8_t *pData)
{
  *pData = I2C->DATA;
}

/**
  * @brief  Write one byte data.
  * @param  I2C_DataCmd: the data and command to send.
  * @retval None.
  */
void I2C_WriteByte(uint8_t I2C_DataCmd)
{
  I2C->DATA = I2C_DataCmd;
}

/**
  * @brief  Write the slave address byte by the direction.
  * @param  Address: specifies the slave address to write.
  * @param  I2C_Direction: specifies whether the I2C device will be a Transmitter
  *         or a Receiver. 
  *         This parameter can be one of the following values
  *         @arg @ref I2C_Direction_Transmitter: Transmitter mode
  *         @arg @ref I2C_Direction_Receiver: Receiver mode
  * @retval None
  */
void I2C_WriteAddress(uint8_t Address, uint8_t I2C_Direction)
{
  /* Check the parameters */
  assert_param(IS_I2C_DIRECTION(I2C_Direction));

  if (I2C_Direction != I2C_Direction_Transmitter)
  {
    /* Set the address bit0 for read */
    Address |= I2C_Direction_Receiver;
  }
  else
  {
    /* Reset the address bit0 for write */
    Address &= ~((uint8_t)I2C_Direction_Receiver);
  }

  I2C->DATA = Address;
}

/**
  * @brief  Gets the last I2C module status flag.
  * @param  None
  * @retval An I2C Status enumeration value:
  *         - I2C_SUCCESS: Get the i2c module status
  *         - I2C_WAITING: Can't get the i2c module status 
  */
I2CStatus I2C_CheckFlag(uint32_t *I2C_Flag)
{
  I2CStatus status = I2C_WAITING;

  if ((I2C->CR & I2C_CR_SI) == I2C_CR_SI)
  {
    /* Read the I2Cx status register */
    *I2C_Flag = I2C->SR;
    /* I2C_SUCCESS: Get the i2c module status */
    status = I2C_SUCCESS;
  }

  /* Return status */
  return status;
}

/**
  * @brief  Checks whether I2C interrupt has occurred or not.
  * @param  None
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus I2C_GetITStatus(void)
{
  ITStatus bitstatus = RESET;

  /* Check the status of the specified I2C flag */
  if ((I2C->CR & I2C_CR_SI) != (uint32_t)RESET)
  {
    /* I2C interrupt flag is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C interrupt flag is reset */
    bitstatus = RESET;
  }

  /* Return the I2C interrupt flag status */
  return bitstatus;
}

/**
  * @brief  Clears I2C interrupt pending bit.
  * @param  None
  * @retval None
  */
void I2C_ClearITPendingBit(void)
{
  /* Clear interrupt flag */
  I2C->CR &= ~I2C_CR_SI;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
