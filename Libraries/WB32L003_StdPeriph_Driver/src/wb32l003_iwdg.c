/**
 * @file    wb32l003_iwdg.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the IWDG firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_iwdg.h"
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup IWDG 
  * @brief IWDG driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup IWDG_Private_Functions
  * @{
  */

/**
  * @brief  Initialize the IWDG according to the specified IWDG_Config.
  * @param  IWDG_Config: Specify configuration parameters for the IWDG.
  *         This parameter can be any combination of the following values:
  *         @arg IWDG_MODE_RESET
  *         @arg IWDG_MODE_INT
  *         @arg IWDG_IT_DISABLE
  *         @arg IWDG_IT_ENABLE
  * @param  NewState: new state of the IWDG peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void IWDG_Init(uint32_t IWDG_Config, FunctionalState NewState)
{
  uint32_t temp;

  IWDG_ENABLE_WRITE_ACCESS();

  temp = IWDG->CFGR;

  temp &= ~(IWDG_CFGR_IWDGMODE_Msk | IWDG_CFGR_IWDGINTMSK_Msk | IWDG_CFGR_IWDGRUNF_Msk);

  if ((IWDG_Config & IWDG_MODE_MASK) == IWDG_MODE_INT)
  {
    temp |= (0x01UL << IWDG_CFGR_IWDGMODE_Pos);
  }

  if ((IWDG_Config & IWDG_IT_MASK) == IWDG_IT_DISABLE)
  {
    temp |= (0x01UL << IWDG_CFGR_IWDGINTMSK_Pos);
  }

  if (NewState != DISABLE)
  {
    temp |= (0x01UL << IWDG_CFGR_IWDGRUNF_Pos);
  }

  IWDG->CFGR = temp;

  IWDG_DISABLE_WRITE_ACCESS();
}

/**
  * @brief  Sets IWDG Reload value.
  * @param  Reload: specifies the IWDG Reload value.
  *         This parameter must be a number between 0 and 0xFFFFF.
  * @retval None
  */
void IWDG_SetReload(uint32_t Reload)
{
  IWDG_ENABLE_WRITE_ACCESS();
  IWDG->RLOAD = Reload;
  IWDG_DISABLE_WRITE_ACCESS();
}

/**
  * @brief  Reloads IWDG counter with value defined in the reload register.
  * @param  None
  * @retval None
  */
void IWDG_ReloadCounter(void)
{
  IWDG_ENABLE_WRITE_ACCESS();
  if (IWDG->CFGR & IWDG_CFGR_IWDGRUNF_Msk)
  {
    IWDG->CMDCR = IWDG_RELOAD_REFRESH;
  }
  IWDG_DISABLE_WRITE_ACCESS();
}

/**
  * @brief  IWDG starts running.
  * @param  None
  * @retval None
  */
void IWDG_Start(void)
{
  IWDG_ENABLE_WRITE_ACCESS();
  IWDG->CMDCR = IWDG_START_ENABLE;
  IWDG_DISABLE_WRITE_ACCESS();
}

/**
  * @brief  Checks whether the specified IWDG interrupt flag is set or not.
  * @param  IWDG_IT: specifies the interrupt flag to check.
  *         This parameter can be one of the following values:
  *         @arg @ref IWDG_IT_GOVF: The overflow of the IWDG was interrupted
  * @retval The new state of IWDG_IT (SET or RESET).
  */
FlagStatus IWDG_GetITStatus(uint32_t IWDG_IT)
{
  FlagStatus bitstatus = RESET;

  if ((IWDG->SR & IWDG_IT_GOVF) != (uint32_t)RESET)
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
  * @brief  Clears the IWDG's interrupt pending bits.
  * @param  IWDG_IT: specifies the interrupt pending bit to clear.
  *         This parameter can be a combination of the following values:
  *         @arg @ref IWDG_IT_GOVF: The overflow of the IWDG was interrupted
  * @retval None.
  */
void IWDG_ClearITPendingBit(uint32_t IWDG_IT)
{
  IWDG_ENABLE_WRITE_ACCESS();
  IWDG->INTCLR = IWDG_IT;
  IWDG_DISABLE_WRITE_ACCESS();
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
