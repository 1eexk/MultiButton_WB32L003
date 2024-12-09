/**
 * @file    wb32l003_flash.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the FLASH firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_flash.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup FLASH 
  * @brief FLASH driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup FLASH_Private_Constants
  * @{
  */
#define FLASH_OP_READ               (0x00000000)
#define FLASH_OP_PROGRAM            (FLASH_CR_OP_0)
#define FLASH_OP_SECTORERASE        (FLASH_CR_OP_1)
#define FLASH_OP_CHIPERASE          (FLASH_CR_OP_0 | FLASH_CR_OP_1)
#define DUMMY_ADDERSS               (0x00002000)
#define DUMMY_DATA                  (0x5555AAAA)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void FLASH_OP_Delay(uint32_t Ticks);

/* Private functions ---------------------------------------------------------*/

/** @defgroup FLASH_Private_Functions
  * @{
  */

/**
  * @brief  Delay n ticks.
  * @param  Ticks: Number of ticks to delay.
  * @retval None
  */
static void FLASH_OP_Delay(uint32_t Ticks)
{
  while (Ticks--) ;
}

/**
  * @brief  Lock the FLASH Page Erase/Write access.
  * @param  PageAddr: Set the page address to lock erase/write protect.
  *         This parameter can be set 0xFFFFFFFF which means lock all pages.
  * @retval None
  */
void FLASH_OP_Unlock(uint32_t PageAddr)
{
  int state;

  state = __get_PRIMASK();
  __disable_irq();

  if (PageAddr < FLASH_SIZE_32K)
  {
    FLASH_Unlock();
    SET_BIT(FLASH->SLOCK0, 0x01 << (PageAddr >> 10));
    FLASH_Lock();
  }
  else if (PageAddr < FLASH_SIZE_64K)
  {
    FLASH_Unlock();
    SET_BIT(FLASH->SLOCK1, 0x01 << ((PageAddr >> 10) - 32));
    FLASH_Lock();
  }
  else if (PageAddr == FLASH_ALLPAGE_SELECTED)
  {
    FLASH_Unlock();
    SET_BIT(FLASH->SLOCK0, 0xFFFFFFFFU);
    FLASH_Lock();

    FLASH_Unlock();
    SET_BIT(FLASH->SLOCK1, 0xFFFFFFFFU);
    FLASH_Lock();
  }

  if (!state)
  {
    __enable_irq();
  }
}

/**
  * @brief  Unlock the FLASH Page Erase/Write access.
  * @param  PageAddr: Set the page address to lock erase/write protect.
  *         This parameter can be set 0xFFFFFFFF which means lock all pages.
  * @retval None
  */
void FLASH_OP_Lock(uint32_t PageAddr)
{
  int state;

  state = __get_PRIMASK();
  __disable_irq();

  if (PageAddr < FLASH_SIZE_32K)
  {
    FLASH_Unlock();
    CLEAR_BIT(FLASH->SLOCK0, 0x01 << (PageAddr >> 10));
    FLASH_Lock();
  }
  else if (PageAddr < FLASH_SIZE_64K)
  {
    FLASH_Unlock();
    CLEAR_BIT(FLASH->SLOCK1, 0x01 << ((PageAddr >> 10) - 32));
    FLASH_Lock();
  }
  else if (PageAddr == FLASH_ALLPAGE_SELECTED)
  {
    FLASH_Unlock();
    CLEAR_BIT(FLASH->SLOCK0, 0xFFFFFFFFU);
    FLASH_Lock();

    FLASH_Unlock();
    CLEAR_BIT(FLASH->SLOCK1, 0xFFFFFFFFU);
    FLASH_Lock();
  }

  if (!state)
  {
    __enable_irq();
  }
}

/**
  * @brief  Unlock the FLASH controller register write-protect.
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
  int state;

  state = __get_PRIMASK();
  __disable_irq();

  FLASH->BYPASS = FLASH_REGUNLOCK_KEY1;
  FLASH->BYPASS = FLASH_REGUNLOCK_KEY2;

  if (!state)
  {
    __enable_irq();
  }
}

/**
  * @brief  Lock the FLASH controller register write-protect.
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
  int state;

  state = __get_PRIMASK();
  __disable_irq();

  FLASH->BYPASS = FLASH_REGUNLOCK_KEY1;
  FLASH->BYPASS = 0x00;

  if (!state)
  {
    __enable_irq();
  }
}

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: FLASH interrupts.
  *         This parameter can be any combination of the following values:
  *         @arg @ref FLASH_IT_ALARM_ERASE_PROTADDR: The address to be erased is protectd interrupt source.
  *         @arg @ref FLASH_IT_ALARM_ERASE_PCADDR: The address to be erased is PC interrupt source.
  * @retval none
  */ 
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    FLASH_Unlock();
    FLASH->CR |= (FLASH_IT & FLASH_CR_IE_Msk);
    FLASH_Lock();
  }
  else
  {
    FLASH_Unlock();
    FLASH->CR &= ~(FLASH_IT & FLASH_CR_IE_Msk);
    FLASH_Lock();
  }
}

/**
  * @brief  Clear the specified FLASH interrupt flag.
  * @param  FLASH_IT: specifies the FLASH interrupt flags to clear.
  *         This parameter can be any combination of the following values:
  *         @arg @ref FLASH_FLAG_ALARM_ERASE_PROTADDR: The address to be erased is protectd interrupt flag
  *         @arg @ref FLASH_FLAG_ALARM_ERASE_PCADDR: The address to be erased is PC interrupt source
  * @retval none
  */
void FLASH_ClearITPendingBit(uint32_t FLASH_IT)
{
  FLASH_Unlock();
  FLASH->ICLR &= ~((FLASH_IT & (FLASH_ICLR_ICLR0_Msk | FLASH_ICLR_ICLR1_Msk)));
  FLASH_Lock();
}

/**
  * @brief  Checks whether the specified FLASH interrupt has occurred or not.
  * @param  FLASH_IT: specifies the FLASH interrupt source to check.
  *         This parameter can be:
  *         @arg @ref FLASH_IT_ALARM_ERASE_PROTADDR: Flash erase protection alarm interrupt flag.
  *         @arg @ref FLASH_IT_ALARM_ERASE_PCADDR: Flash erase PC address alarm interrupt flag.
  * @retval The new state of the FLASH flag (SET or RESET).
  */
FlagStatus FLASH_GetITStatus(uint32_t FLASH_IT)
{
  FlagStatus bitstatus = RESET;

  if (FLASH->CR & (FLASH_IT & FLASH_CR_IE_Msk))
  {
    if ((FLASH->IFR & (FLASH_IT & (FLASH_IFR_IF0_Msk | FLASH_IFR_IF1_Msk))) != (uint32_t)RESET)
    {
      bitstatus = SET;
    }
  }

  return bitstatus;
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  Flag: specifies the FLASH flag to check.
  *         This parameter can be:
  *         @arg @ref FLASH_FLAG_BUSY: FLASH busy flag.
  * @retval The new state of the FLASH flag (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t Flag)
{
  FlagStatus bitstatus = RESET;

  if (Flag == FLASH_FLAG_BUSY)
  {
    if ((FLASH->CR & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY)
    {
      bitstatus = SET;
    }
  }
  
  return bitstatus;
}

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  Timeout: maximum flash operation timeout
  * @retval FLASH_Status
  */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  while (FLASH_GetFlagStatus(FLASH_FLAG_BUSY) == SET)
  {
    if (!(Timeout--))
    {
      return FLASH_TIMEOUT;
    }
  }

  return flashstatus;
}

/**
  * @brief  Program a byte (8-bit) at a specified address.
  * @param  Addr: specify the address to be programmed.
  * @param  Data: specify the data to be programmed.
  * @retval None
  */
FLASH_Status FLASH_ProgramByte(uint32_t Addr, uint8_t Data)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (flashstatus == FLASH_COMPLETE)
  {
    int state;

    state = __get_PRIMASK();
    __disable_irq();

    FLASH_OP_Unlock(FLASH_ALLPAGE_SELECTED);

    FLASH_Unlock();
    MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_PROGRAM);
    M8(Addr) = Data;
    FLASH_Lock();

    FLASH_OP_Delay(0xFFF);

    flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    FLASH_OP_Lock(FLASH_ALLPAGE_SELECTED);

    CLEAR_BIT(FLASH->CR, FLASH_CR_OP);

    if (!state)
    {
      __enable_irq();
    }
  }

  return flashstatus;
}

/**
  * @brief  Program a half-word (16-bit) at a specified address.
  * @param  Addr: specify the address to be programmed.
  * @param  Data: specify the data to be programmed.
  * @retval None
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Addr, uint16_t Data)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (flashstatus == FLASH_COMPLETE)
  {
    int state;

    state = __get_PRIMASK();
    __disable_irq();

    FLASH_OP_Unlock(FLASH_ALLPAGE_SELECTED);

    FLASH_Unlock();
    MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_PROGRAM);
    M16(Addr) = Data;
    FLASH_Lock();

    FLASH_OP_Delay(0xFFF);

    flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    FLASH_OP_Lock(FLASH_ALLPAGE_SELECTED);

    CLEAR_BIT(FLASH->CR, FLASH_CR_OP);

    if (!state)
    {
      __enable_irq();
    }
  }

  return flashstatus;
}

/**
  * @brief  Program a word (32-bit) at a specified address.
  * @param  Addr: specify the address to be programmed.
  * @param  Data: specify the data to be programmed.
  * @retval None
  */
FLASH_Status FLASH_ProgramWord(uint32_t Addr, uint32_t Data)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (flashstatus == FLASH_COMPLETE)
  {
    int state;

    state = __get_PRIMASK();
    __disable_irq();

    FLASH_OP_Unlock(FLASH_ALLPAGE_SELECTED);

    FLASH_Unlock();
    MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_PROGRAM);
    M32(Addr) = Data;
    FLASH_Lock();

    FLASH_OP_Delay(0xFFF);

    flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    FLASH_OP_Lock(FLASH_ALLPAGE_SELECTED);

    CLEAR_BIT(FLASH->CR, FLASH_CR_OP);

    if (!state)
    {
      __enable_irq();
    }
  }

  return flashstatus;
}

/**
  * @brief  Full erase of FLASH memory Bank 
  * @param  None
  * @retval None
  */
FLASH_Status FLASH_EraseChip(void)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (flashstatus == FLASH_COMPLETE)
  {
    int state;

    state = __get_PRIMASK();
    __disable_irq();

    FLASH_OP_Unlock(FLASH_ALLPAGE_SELECTED);

    FLASH_Unlock();
    MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_CHIPERASE);
    M32(DUMMY_ADDERSS) = DUMMY_DATA;
    FLASH_Lock();

    FLASH_OP_Delay(0x1FFFF);

    flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    FLASH_OP_Lock(FLASH_ALLPAGE_SELECTED);

    CLEAR_BIT(FLASH->CR, FLASH_CR_OP);

    if (!state)
    {
      __enable_irq();
    }
  }

  return flashstatus;
}

/**
  * @brief  Erase the specified FLASH memory page
  * @param  PageAddr: FLASH page to erase
  *         The value of this parameter depend on device used within the same series      
  * @retval None
  */
FLASH_Status FLASH_ErasePage(uint32_t PageAddr)
{
  FLASH_Status flashstatus = FLASH_COMPLETE;

  flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);

  if (flashstatus == FLASH_COMPLETE)
  {
    int state;

    state = __get_PRIMASK();
    __disable_irq();

    FLASH_OP_Unlock(PageAddr);

    FLASH_Unlock();
    MODIFY_REG(FLASH->CR, FLASH_CR_OP, FLASH_OP_SECTORERASE);
    M32(PageAddr) = DUMMY_DATA;
    FLASH_Lock();

    FLASH_OP_Delay(0x1FFFF);

    flashstatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);
    FLASH_OP_Lock(PageAddr);

    CLEAR_BIT(FLASH->CR, FLASH_CR_OP);

    if (!state)
    {
      __enable_irq();
    }
  }

  return flashstatus;
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
