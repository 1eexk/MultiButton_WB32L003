/**
 * @file    wb32l003_gpio.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the GPIO firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_gpio.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO
  * @brief GPIO driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions
  * @{
  */

/**
  * @brief  De-initializes the GPIOx peripheral registers to their default reset values.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  if (GPIOx == GPIOA)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, DISABLE);
  }
  else if (GPIOx == GPIOB)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOB, DISABLE);
  }
  else if (GPIOx == GPIOC)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOC, DISABLE);
  }
  else if (GPIOx == GPIOD)
  {
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOD, DISABLE);
  }
}

/**
  * @brief  Initializes the GPIOx peripheral according to the PinConfig.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to be initialized.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @param  PinConfig: The port bit configuration.
  *         This parameter must be a combination of one GPIO_MODE_x flag, one GPIO_OTYPE_x flag,
  *         one GPIO_PUPD_x flag, one GPIO_DRV_x flag, one GPIO_SPEED_x flag and one GPIO_AFx flag.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t PinConfig)
{
  uint32_t tmp;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  for (offset = 0; offset < GPIO_NUMBER; offset++)
  {
    if (((0x01U << offset) & GPIO_Pin) != 0)
    {
      /* Configure the GPIO direction */
      tmp = GPIOx->DIRCR;
      tmp &= ~(0x01U << offset);
      tmp |= (((PinConfig >> 28) & 0x01) << offset);
      GPIOx->DIRCR = tmp;

      /* Configure the GPIO output mode */
      tmp = GPIOx->OTYPER;
      tmp &= ~(0x01 << offset);
      tmp |= (((PinConfig >> 24) & 0x01) << offset);
      GPIOx->OTYPER = tmp;

      /* Configure the GPIO voltage slew rate */
      tmp = GPIOx->SLEWCR;
      tmp &= ~(0x01 << offset);
      tmp |= (((PinConfig >> 20) & 0x01) << offset);
      GPIOx->SLEWCR = tmp;

      /* Configure GPIO pull-up and drop-down resistors */
      tmp = GPIOx->PUPDR;
      tmp &= ~(0x03 << (offset * 2));
      tmp |= (((PinConfig >> 16) & 0x03) << (offset * 2));
      GPIOx->PUPDR = tmp;

      /* Configure GPIO drive strength */
      tmp = GPIOx->DRVCR;
      tmp &= ~(0x01 << offset);
      tmp |= (((PinConfig >> 12) & 0x01) << offset);
      GPIOx->DRVCR = tmp;

      tmp = GPIOx->AFR;
      tmp &= ~(0x0FU << (offset * 4));
      /* Configure Alternate function mapped with the current IO */
      tmp |= ((PinConfig & GPIO_AF_Mask) << (offset * 4));
      GPIOx->AFR = tmp;
    }
  }
}

/**
  * @brief  Configure gpio alternate function of any pins for a dedicated port.
  * @note   Possible values are from AF0 to AF15 depending on target.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bits to configure.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @param  Alternate: This parameter can be GPIO_AFx where x can be (0..15).
  * @retval None
  */
void GPIO_SetAFPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Alternate)
{
  uint32_t tmp;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  for (offset = 0; offset < GPIO_NUMBER; offset++)
  {
    if (((0x01U << offset) & GPIO_Pin) != 0)
    {
      /* Configure Alternate function mapped with the current IO */
      tmp = GPIOx->AFR;
      tmp &= ~(0x0FU << (offset * 4));
      tmp |= ((Alternate & GPIO_AF_Mask) << (offset * 4));
      GPIOx->AFR = tmp;
    }
  }
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }

  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO input data port.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->IDR);
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

  if (((GPIOx->ODR) & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }

  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  return ((uint16_t)GPIOx->ODR);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODSET = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODCLR = GPIO_Pin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @param  BitVal: Specifies the value to be written to the selected bit.
  *         This parameter can be one of the BitAction enum values:
  *         @arg @ref Bit_RESET: to clear the port pin
  *         @arg @ref Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal));

  if (BitVal != Bit_RESET)
  {
    GPIOx->ODSET = GPIO_Pin;
  }
  else
  {
    GPIOx->ODCLR = GPIO_Pin;
  }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  PortVal: Specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR = PortVal;
}

/**
  * @brief  Toggle data value for several pin of specified port.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_ToggleBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR ^= GPIO_Pin;
}

/**
  * @brief  Configure the drive current of several pins for a specified port.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be configured.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @param  Current: Specifies the drive current.
  *         This parameter can be one of the following values:
  *         @arg @ref GPIO_DRV_HIGH: High driving strength.
  *         @arg @ref GPIO_DRV_LOW: Low driving strength
  * @retval None
  */
void GPIO_DriveCurrentConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Current)
{
  uint32_t tmp;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  for (offset = 0; offset < GPIO_NUMBER; offset++)
  {
    if (((0x01U << offset) & GPIO_Pin) != 0)
    {
      /* Configure GPIO drive strength */
      tmp = GPIOx->DRVCR;
      tmp &= ~(0x01 << offset);
      tmp |= (((Current >> 12) & 0x01) << offset);
      GPIOx->DRVCR = tmp;
    }
  }
}

/**
  * @brief  Handles the configuration of GPIO_Pin's EXTI.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be configured.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @param  EXTI_Config: The port bit configuration.
  *         This parameter must be a combination of one @ref GPIO_EXTI_define GPIO_EXTI_x flags.
  * @retval None
  */
void GPIO_EXTIConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t EXTI_Config)
{
  uint32_t tmp;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  for (offset = 0; offset < GPIO_NUMBER; offset++)
  {
    if (((0x01U << offset) & GPIO_Pin) != 0)
    {
      tmp = GPIOx->INTTYPCR;
      tmp &= ~(0x01 << offset);
      tmp |= (((EXTI_Config >> 9) & 0x01) << offset);
      GPIOx->INTTYPCR = tmp;

      tmp = GPIOx->INTANY;
      tmp &= ~(0x01 << offset);
      tmp |= (((EXTI_Config >> 11) & 0x01) << offset);
      GPIOx->INTANY = tmp;

      tmp = GPIOx->INTPOLCR;
      tmp &= ~(0x01 << offset);
      tmp |= (((EXTI_Config >> 10) & 0x01) << offset);
      GPIOx->INTPOLCR = tmp;

      tmp = GPIOx->INTEN;
      tmp &= ~(0x01 << offset);
      tmp |= (((EXTI_Config >> 8) & 0x01) << offset);
      GPIOx->INTEN = tmp;
    }
  }
}

/**
  * @brief  Handles the configuration of GPIO debounce.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be configured.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @param  DebounceConfig: The port bit configuration.
  *         This parameter must be a combination of one GPIO_DB_x flags.
  * @retval None
  */
void GPIO_DebounceConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t DebounceConfig)
{
  uint32_t tmp, tmp2;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  for (offset = 0; offset < GPIO_NUMBER; offset++)
  {
    if (((0x01U << offset) & GPIO_Pin) != 0)
    {
      tmp = GPIOx->INDBEN;
      tmp &= ~(0x01U << offset);
      tmp2 = GPIOx->DBCLKCR;

      if (DebounceConfig & GPIO_DB_ENABLE)
      {
        /* Configure debounce clock divider for Input function IO */
        tmp2 = (DebounceConfig & GPIO_DBCLKCR_DBCLK_DIV_Msk) << GPIO_DBCLKCR_DBCLK_DIV_Pos;
        /* Enable debounce clock for Input function IO */
        tmp2 |= 0x01 << GPIO_DBCLKCR_DBCLKEN_Pos;

        tmp |= (0x01 << offset);
      }
      else if (DebounceConfig & GPIO_DB_SYNC_ENABLE)
      {
        /* Disable debounce clock for Input function IO */
        tmp2 &= ~(0x01 << GPIO_DBCLKCR_DBCLKEN_Pos);

        /* Configure two level sync function for Input function IO */
        tmp &= ~(0x01 << GPIO_INDBEN_SYNC_EN_Pos);
        tmp |= (0x01 << 8);
      }

      GPIOx->INDBEN = tmp;

      /* Enable debounce function clock */
      if ((GPIOx->INDBEN & GPIO_INDBEN_PxDIDB) == 0x0U)
      {
        /* Disable debounce clock for Input function IO */
        tmp2 &= ~(0x01U << GPIO_DBCLKCR_DBCLKEN_Pos);
      }

      GPIOx->DBCLKCR = tmp2;
    }
  }
}

/**
  * @brief  Checks whether the specified GPIO_Pin's EXTI line flag is set or not.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the pins flag to check.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval The new state of GPIO_Pin's EXTI line (SET or RESET).
  */
FlagStatus GPIO_EXTI_GetFlagStatus(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if (GPIOx->MSKINTSR & GPIO_Pin)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief  Clears the GPIO_Pin's EXTI line pending flags.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins flags to clear.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_EXTI_ClearFlag(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->INTCLR = GPIO_Pin;
}

/**
  * @brief  Checks that the interrupt of the EXTI line for the specified GPIO Pin is enabled.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to check.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval The new state of interrupt enabled for the GPIO_Pin's EXTI line (SET or RESET).
  */
ITStatus GPIO_EXTI_GetIT(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if (GPIOx->INTEN & GPIO_Pin)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief  Clears the GPIO_Pin's EXTI line pending bits.
  * @param  GPIOx: Where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the GPIO_Pin's EXTI lines to clear.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_EXTI_ClearIT(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->INTEN &= (~(GPIO_Pin));
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
