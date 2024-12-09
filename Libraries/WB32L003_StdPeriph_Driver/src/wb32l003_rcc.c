/**
 * @file    wb32l003_rcc.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the RCC firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_rcc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup RCC 
  * @brief RCC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* RCC_RegisterWrite_Unlock Unlock RCC write-protected registers */
#define RCC_REGWR_LOCK()                              (RCC->UNLOCK = (0x2AD5334C << RCC_UNLOCK_KEY_Pos) & RCC_UNLOCK_KEY)
#define RCC_REGWR_UNLOCK()                            (RCC->UNLOCK = RCC_UNLOCK_UNLOCK | (0x2AD5334C << RCC_UNLOCK_KEY_Pos))

/* RCC_RegisterWrite_Unlock Unlock RCC write-protected registers */
#define RCC_SYSTEMCR_UNLOCK_KEY                       ((uint32_t)0x5A69)
#define RCC_SYSTEMCR_UNLOCK_Pos                       ((uint32_t)16)

#define RCC_SET_KEYBIT(REG, BIT)                      ((REG) |= (BIT | (RCC_SYSTEMCR_UNLOCK_KEY << RCC_SYSTEMCR_UNLOCK_Pos)))         
#define RCC_MODIFY_KEYREG(REG, CLEARMASK, SETVALUE)   WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETVALUE | (RCC_SYSTEMCR_UNLOCK_KEY << RCC_SYSTEMCR_UNLOCK_Pos))))
#define RCC_WRITE_KEYREG(REG, VAL)                    ((REG) = (VAL | (RCC_SYSTEMCR_UNLOCK_KEY << RCC_SYSTEMCR_UNLOCK_Pos)))
#define RCC_CLEAR_KEYBIT(REG, CLEARMASK)              WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (RCC_SYSTEMCR_UNLOCK_KEY << RCC_SYSTEMCR_UNLOCK_Pos)))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup RCC_Private_Functions
  * @{
  */

/**
  * @brief  Resets the RCC clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *         - HSI ON and used as system clock source
  *         - HSE are OFF
  *         - AHB, APB prescaler set to 1.
  *         - MCO OFF
  * @note   This function does not modify the configuration of the
  *         - Peripheral clocks
  *         - LSI, LSE clocks
  * @retval None
  */
void RCC_DeInit(void)
{
  RCC_REGWR_UNLOCK();

  /* HSI ENABLE */
  RCC_SET_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HSIEN);

  /* Wait till HSI is ready */
  while ((RCC->HSICR & RCC_HSICR_HSIRDY) == RESET);
  
  /* Reset SYSCLKSEL register */
  RCC_WRITE_KEYREG(RCC->SYSCLKSEL, RCC_SYSCLKSource_HSI);

  /* Wait till clock switch is ready */
  while ((RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW) != RCC_SYSCLKSource_HSI);

  /* Reset HSE Config*/
  RCC_CLEAR_KEYBIT(RCC->SYSCLKCR, (RCC_SYSCLKCR_HSEEN | RCC_SYSCLKCR_HSEBYP));

  /* Wait till HSE is disable */
  while ((RCC->HSECR & RCC_HSECR_HSERDY) != RESET);

  /* Reset LSIEN bits */
  RCC_CLEAR_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LSIEN);

  /* Wait till LSI is disable */
  while ((RCC->LSICR & RCC_LSICR_LSIRDY) != RESET);

  /* Reset MCO Config */
  RCC_WRITE_KEYREG(RCC->MCOCR, 0x0);

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the Internal High Speed oscillator (HSI).
  * @param  HSI_Value: The HSI frequency value.
  *         This parameter can be one of the following values:
  *         @arg @ref HSI_VALUE_24M
  *         @arg @ref HSI_VALUE_22M
  *         @arg @ref HSI_VALUE_16M
  *         @arg @ref HSI_VALUE_8M 
  *         @arg @ref HSI_VALUE_4M 
  * @param  NewState: new state of the HSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   The SYSTEM register write-protection function should be disabled before using this function.
  * @retval None
  */
void RCC_HSIConfig(const uint32_t HSI_Value, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_HSI_VALUE(HSI_Value));

  uint32_t HSITrimValue = 0, HSITCValue = 0;

  RCC_REGWR_UNLOCK();

  /* ENABLE HSI */
  if (NewState != DISABLE)
  {
    if (HSI_Value == HSI_VALUE_24M)
    {
      HSITrimValue = RCC_HSITRIM_24M;
      HSITCValue = RCC_HSITC_24M;
    }
    else if (HSI_Value == HSI_VALUE_22M)
    {
      HSITrimValue = RCC_HSITRIM_22M;
      HSITCValue = RCC_HSITC_22M;
    }
    else if (HSI_Value == HSI_VALUE_16M)
    {
      HSITrimValue = RCC_HSITRIM_16M;
      HSITCValue = RCC_HSITC_16M;
    }
    else if (HSI_Value == HSI_VALUE_8M)
    {
      HSITrimValue = RCC_HSITRIM_8M;
      HSITCValue = RCC_HSITC_8M;
    }
    else if (HSI_Value == HSI_VALUE_4M)
    {
      HSITrimValue = RCC_HSITRIM_4M;
      HSITCValue = RCC_HSITC_4M;
    }
    
    RCC_MODIFY_KEYREG(RCC->HSICR, RCC_HSICR_HSITRIM_Msk, HSITrimValue);
    RCC_MODIFY_KEYREG(RCC->HSITC, 0xFFFF, HSITCValue);

    RCC_SET_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HSIEN);
  }
  else
  {
    RCC_CLEAR_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HSIEN);
  }

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the Internal low Speed oscillator (LSI).
  * @param  LSI_Value: The LSI frequency value.
  *         This parameter can be one of the following values:
  *         @arg @ref LSI_VALUE_38K
  *         @arg @ref LSI_VALUE_32K
  * @param  LSI_StartUPTime: The LSI startup time.
  *         This parameter can be one of the following values:
  *         @arg @ref RCC_LSI_STARTUP_4CYCLE
  *         @arg @ref RCC_LSI_STARTUP_16CYCLE
  *         @arg @ref RCC_LSI_STARTUP_64CYCLE
  *         @arg @ref RCC_LSI_STARTUP_256CYCLE
  * @param  NewState: new state of the LSI.
  *         This parameter can be: ENABLE or DISABLE.
  * @note   The SYSTEM register write-protection function should be disabled before using this function.
  * @retval None
  */
void RCC_LSIConfig(uint32_t LSI_Value, uint32_t LSI_StartUPTime, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_LSI_VALUE(LSI_Value));
  assert_param(IS_RCC_LSI_STARTUP(LSI_StartUPTime));

  RCC_REGWR_UNLOCK();

#ifdef WB32L003Fx
  uint32_t LSITrimValue = 0;

  if (NewState != DISABLE)
  {
    if (LSI_Value == LSI_VALUE_38K)
    {
      LSITrimValue = RCC_LSITRIM_38K;
    }
    else if (LSI_Value == LSI_VALUE_32K)
    {
      LSITrimValue = RCC_LSITRIM_32K;
    }
    
    /* Write LSI StartUP Time */
    RCC_MODIFY_KEYREG(RCC->LSICR, RCC_LSICR_LSISTARTUP_Msk, LSI_StartUPTime);
    /* Write LSI Calibration Value */
    RCC_MODIFY_KEYREG(RCC->LSICR, RCC_LSICR_LSITRIM_Msk, LSITrimValue);

    RCC_SET_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LSIEN);
  }
  else
  {
    RCC_CLEAR_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LSIEN);
  }
#elif defined(WB32L003Kx)
  uint32_t LSITrimValue = 0, LSITCValue = 0;

  if (NewState != DISABLE)
  {
    if (LSI_Value == LSI_VALUE_38K)
    {
      LSITrimValue = RCC_LSITRIM_38K;
      LSITCValue = RCC_LSITC_38K;
    }
    else if (LSI_Value == LSI_VALUE_32K)
    {
      LSITrimValue = RCC_LSITRIM_32K;
      LSITCValue = RCC_LSITC_32K;
    }
    
    /* Write LSI StartUP Time */
    RCC_MODIFY_KEYREG(RCC->LSICR, RCC_LSICR_LSISTARTUP_Msk, LSI_StartUPTime);
    /* Write LSI Calibration Value */
    RCC_MODIFY_KEYREG(RCC->LSICR, RCC_LSICR_LSITRIM_Msk, LSITrimValue);
    RCC_MODIFY_KEYREG(RCC->LSITC, 0xFFFF, LSITCValue);

    RCC_SET_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LSIEN);
  }
  else
  {
    RCC_CLEAR_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_LSIEN);
  }
#endif

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the External High Speed oscillator (HSE).
  * @param  RCC_HSE: Specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *         @arg @ref RCC_HSE_OFF
  *         @arg @ref RCC_HSE_ON
  *         @arg @ref RCC_HSE_BYPASS
  *         @arg @ref RCC_HSE_DEFAULT
  * @note   The SYSTEM register write-protection function should be disabled before using this function.
  * @retval None
  */
void RCC_HSEConfig(uint32_t RCC_HSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_HSE(RCC_HSE));

  RCC_REGWR_UNLOCK();

  if ((RCC_HSE) == RCC_HSE_ON)
  {
    RCC_SET_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HSEEN | RCC_SYSCLKCR_HSEPORT);
  }
  else if ((RCC_HSE) == RCC_HSE_OFF)
  {
    RCC_CLEAR_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HSEEN | RCC_SYSCLKCR_HSEPORT);
  }
  else if ((RCC_HSE) == RCC_HSE_BYPASS)
  {
    RCC_SET_KEYBIT(RCC->SYSCLKCR, RCC_SYSCLKCR_HSEBYP);
  }
  else
  {
    RCC_CLEAR_KEYBIT(RCC->SYSCLKCR, (RCC_SYSCLKCR_HSEEN | RCC_SYSCLKCR_HSEBYP | RCC_SYSCLKCR_HSEPORT));
  }

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the External Low Speed oscillator (LSE).
  * @param  RCC_LSE: Specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *         @arg @ref RCC_LSE_OFF
  *         @arg @ref RCC_LSE_ON
  *         @arg @ref RCC_LSE_BYPASS
  *         @arg @ref RCC_LSE_DEFAULT 
  * @note   The SYSTEM register write-protection function should be disabled before using this function.
  * @retval None
  */
void RCC_LSEConfig(uint32_t RCC_LSE)
{
  /* Check the parameters */
  assert_param(IS_RCC_LSE(RCC_LSE));

  RCC_REGWR_UNLOCK();

  if ((RCC_LSE) == RCC_LSE_ON)
  {
    RCC_SET_KEYBIT(RCC->LSECR, RCC_LSECR_LSEEN | RCC_LSECR_LSEPORT);
  }
  else if ((RCC_LSE) == RCC_LSE_OFF)
  {
    RCC_CLEAR_KEYBIT(RCC->LSECR, RCC_LSECR_LSEAON);
    RCC_CLEAR_KEYBIT(RCC->LSECR, RCC_LSECR_LSEEN | RCC_LSECR_LSEPORT);
    RCC_SET_KEYBIT(RCC->LSECR, RCC_LSECR_LSEAON);
  }
  else if ((RCC_LSE) == RCC_LSE_BYPASS)
  {
    RCC_SET_KEYBIT(RCC->LSECR, RCC_LSECR_LSEBYP);
  }
  else
  {
    RCC_CLEAR_KEYBIT(RCC->LSECR, RCC_LSECR_LSEAON);
    RCC_CLEAR_KEYBIT(RCC->LSECR, RCC_LSECR_LSEEN | RCC_LSECR_LSEPORT | RCC_LSECR_LSEBYP);
    RCC_SET_KEYBIT(RCC->LSECR, RCC_LSECR_LSEAON);
  }

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the drive current of High Speed oscillator (HSE).
  * @param  Current: specifies the drive current.
  * @note   The SYSTEM register write-protection function should be disabled before using this function.
  *         This parameter can be a value of 0-7.
  * @retval None
  */
void RCC_HSEDriveCurrentConfig(uint32_t Current)
{
  RCC_REGWR_UNLOCK();

  RCC_MODIFY_KEYREG(RCC->HSECR, RCC_HSECR_HSEDRV_Msk, Current);

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the start time of High Speed oscillator (HSE).
  * @param  Time: specifies the start time.
  * @note   The SYSTEM register write-protection function should be disabled before using this function.
  *         This parameter can be a value of 0-3.
  * @retval None
  */
void RCC_HSEStartTimeConfig(uint32_t Time)
{
  RCC_REGWR_UNLOCK();

  RCC_MODIFY_KEYREG(RCC->HSECR, RCC_HSECR_HSESTARTUP_Msk, Time << RCC_HSECR_HSESTARTUP_Pos);

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the drive current of Low Speed oscillator (LSE).
  * @param  Current: specifies the drive current.
  * @note   The SYSTEM register write-protection function should be disabled before using this function.
  *         This parameter can be a value of 0-15.
  * @retval None
  */
void RCC_LSEDriveCurrentConfig(uint32_t Current)
{
  RCC_REGWR_UNLOCK();

  RCC_MODIFY_KEYREG(RCC->LSECR, RCC_LSECR_LSEDRV_Msk, Current);

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the start time of Low Speed oscillator (LSE).
  * @param  Time: specifies the start time.
  * @note   The SYSTEM register write-protection function should be disabled before using this function.
  *         This parameter can be a value of 0-3.
  * @retval None
  */
void RCC_LSEStartTimeConfig(uint32_t Time)
{
  RCC_REGWR_UNLOCK();

  RCC_MODIFY_KEYREG(RCC->LSECR, RCC_LSECR_LSESTARTUP_Msk, Time << RCC_LSECR_LSESTARTUP_Pos);

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the SYS Clock (SYSCLK).
  * @param  RCC_SYSCLKSource: specifies the clock source used as system clock.
  *         This parameter can be one of the following values:
  *         @arg @ref RCC_SYSCLKSource_HSI: HSI selected as system clock.
  *         @arg @ref RCC_SYSCLKSource_HSE: HSE selected as system clock.
  *         @arg @ref RCC_SYSCLKSource_LSI: LSI selected as system clock.
  *         @arg @ref RCC_SYSCLKSource_LSE: LSE selected as system clock.
  * @retval None
  */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
  /* Check the parameters */
  assert_param(IS_RCC_SYSCLK_SOURCE(RCC_SYSCLKSource));

  RCC_REGWR_UNLOCK();

  RCC_MODIFY_KEYREG(RCC->SYSCLKSEL, RCC_SYSCLKSEL_CLKSW_Msk, RCC_SYSCLKSource);

  RCC_REGWR_LOCK();
}

/**
  * @brief  Configures the AHB clock (AHBCLK).
  * @param  RCC_AHBCLKDiv: defines the AHB clock divider. This clock is derived from
  *         the system clock (SYSCLK).
  *         This parameter can be a value of 1-510, The allowed values are an even number from 2 to 510 and 1.
  * @retval None
  */
void RCC_AHBCLKConfig(uint32_t RCC_AHBCLKDiv)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHBCLKDiv(RCC_AHBCLKDiv));

  RCC->HCLKDIV = (RCC_AHBCLKDiv >> 1);
}

/**
  * @brief  Configures the APB clock (APBCLK).
  * @param  RCC_APBCLKDiv: defines the APB clock divider. This clock is derived from
  *         the AHB clock (HCLK).
  *         This parameter can be a value of 1-510, The allowed values are an even number from 2 to 510 and 1.
  * @retval None
  */
void RCC_APBCLKConfig(uint32_t RCC_APBCLKDiv)
{
  /* Check the parameters */
  assert_param(IS_RCC_APBCLKDiv(RCC_APBCLKDiv));

  RCC->PCLKDIV = (RCC_APBCLKDiv >> 1);
}

/**
  * @brief  Selects the clock source to output on MCO pin.
  * @param  RCC_MCOSource: specifies the clock source to output.
  *         This parameter can be one of the following values:
  *         @arg @ref RCC_MCOSOURCE_HSI: HSI selected as MCO clock
  *         @arg @ref RCC_MCOSOURCE_HSE: HSE selected as MCO clock
  *         @arg @ref RCC_MCOSOURCE_LSI: LSI selected as MCO clock
  *         @arg @ref RCC_MCOSOURCE_LSE: LSE selected as MCO clock
  *         @arg @ref RCC_MCOSOURCE_SYSCLK: SYSCLK selected as MCO clock
  *         @arg @ref RCC_MCOSOURCE_HCLK: HCLK selected as MCO clock
  * @param  RCC_MCOHCLKDiv: specifies the MCO DIV.
  *         This parameter can be a value of 1-510, The allowed values are an even number from 2 to 510 and 1.
  * @note   MCO pin should be configured in alternate function mode.
  * @retval None
  */
void RCC_MCOConfig(uint32_t RCC_MCOSource, uint32_t RCC_MCOHCLKDiv)
{
  /* Check the parameters */
  assert_param(IS_RCC_MCO_SOURCE(RCC_MCOSource));
  assert_param(IS_RCC_MCO_HCLkDiv(RCC_MCOHCLKDiv));

  RCC->MCOCR |= (RCC_MCOSource | (RCC_MCOHCLKDiv >> 1));
}

/**
  * @brief  Enable or Disable the MCO Clock output.
  * @param  NewState: new state of the MCO.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_MCOCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    RCC->MCOCR |= RCC_MCOCR_MCOEN;
  }
  else
  {
    RCC->MCOCR &= (~RCC_MCOCR_MCOEN);
  }
}

/**
  * @brief  Returns the frequencies of different on chip clocks.
  * @param  RCC_Clocks: pointer to a RCC_ClocksTypeDef structure which will hold
  *         the clocks frequencies.
  * @retval None
  */
void RCC_GetClocksFreq(RCC_ClocksTypeDef *RCC_Clocks)
{
  uint32_t tmp = 0, AHBDiv, APBDiv;
  uint32_t SystemClock;

  /* Get SYSCLK source */
  tmp = RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW_Msk;

  switch (tmp)
  {
    case RCC_SYSCLKSource_HSI:
      if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_24M)
      {
        SystemClock = HSI_VALUE_24M;
      }
      else if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_22M)
      {
        SystemClock = HSI_VALUE_22M;
      }
      else if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_16M)
      {
        SystemClock = HSI_VALUE_16M;
      }
      else if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_8M)
      {
        SystemClock = HSI_VALUE_8M;
      }
      else if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_4M)
      {
        SystemClock = HSI_VALUE_4M;
      }
      else
      {
        SystemClock = HSI_VALUE_4M;
      }
      break;
   case RCC_SYSCLKSource_HSE:
     SystemClock = HSE_VALUE;
     break;
   case RCC_SYSCLKSource_LSI:
     SystemClock = LSI_VALUE;
     break;
   case RCC_SYSCLKSource_LSE:
     SystemClock = LSE_VALUE;
     break;
    default:
      SystemClock = HSI_VALUE_4M;
      break;
  }

  AHBDiv = RCC->HCLKDIV & RCC_HCLKDIV_AHBCKDIV;
  APBDiv = RCC->PCLKDIV & RCC_PCLKDIV_APBCKDIV;

  if (AHBDiv != 0)
  {
    RCC_Clocks->AHBCLK_Frequency = ((SystemClock >> 1) / AHBDiv);
    RCC_Clocks->SYSCLK_Frequency = RCC_Clocks->AHBCLK_Frequency;
  }
  else
  {
    RCC_Clocks->AHBCLK_Frequency = SystemClock;
    RCC_Clocks->SYSCLK_Frequency = RCC_Clocks->AHBCLK_Frequency;
  }

  if (APBDiv != 0)
  {
    RCC_Clocks->APBCLK_Frequency = ((RCC_Clocks->AHBCLK_Frequency >> 1) / APBDiv);
  }
  else
  {
    RCC_Clocks->APBCLK_Frequency = RCC_Clocks->AHBCLK_Frequency;
  }
}

/**
  * @brief  Enables or disables the AHB peripheral clock.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *         @arg @ref RCC_AHBPeriph_GPIOA
  *         @arg @ref RCC_AHBPeriph_GPIOB
  *         @arg @ref RCC_AHBPeriph_GPIOC
  *         @arg @ref RCC_AHBPeriph_GPIOD
  *         @arg @ref RCC_AHBPeriph_CRC
  *         @arg @ref RCC_AHBPeriph_FLASH
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));

  if (NewState != DISABLE)
  {
    RCC->HCLKEN |= RCC_AHBPeriph;
  }
  else
  {
    RCC->HCLKEN &= (~RCC_AHBPeriph);
  }
}

/**
  * @brief  Enables or disables the APB peripheral clock.
  * @param  RCC_APBPeriph: specifies the APB peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *         @arg @ref RCC_APBPeriph_UART1
  *         @arg @ref RCC_APBPeriph_UART2
  *         @arg @ref RCC_APBPeriph_I2C
  *         @arg @ref RCC_APBPeriph_LPUART
  *         @arg @ref RCC_APBPeriph_SPI
  *         @arg @ref RCC_APBPeriph_LPTIM
  *         @arg @ref RCC_APBPeriph_BASETIM
  *         @arg @ref RCC_APBPeriph_SYSCON
  *         @arg @ref RCC_APBPeriph_PCA
  *         @arg @ref RCC_APBPeriph_OWIRE
  *         @arg @ref RCC_APBPeriph_TIM1
  *         @arg @ref RCC_APBPeriph_TIM2
  *         @arg @ref RCC_APBPeriph_WWDG
  *         @arg @ref RCC_APBPeriph_ADC
  *         @arg @ref RCC_APBPeriph_AWK
  *         @arg @ref RCC_APBPeriph_RTC
  *         @arg @ref RCC_APBPeriph_CLKTRIM
  *         @arg @ref RCC_APBPeriph_IWDG
  *         @arg @ref RCC_APBPeriph_LVDVC
  *         @arg @ref RCC_APBPeriph_BEEP
  *         @arg @ref RCC_APBPeriph_DBG
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APBPeriphClockCmd(uint32_t RCC_APBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));

  if (NewState != DISABLE)
  {
    RCC->PCLKEN |= RCC_APBPeriph;
  }
  else
  {
    RCC->PCLKEN &= (~RCC_APBPeriph);
  }
}

/**
  * @brief  Forces or releases AHB peripheral reset.
  * @param  RCC_AHBPeriph: specifies the AHB peripheral to reset.
  *         This parameter can be any combination of the following values:
  *         @arg @ref RCC_AHBPeriph_GPIOA
  *         @arg @ref RCC_AHBPeriph_GPIOB
  *         @arg @ref RCC_AHBPeriph_GPIOC
  *         @arg @ref RCC_AHBPeriph_GPIOD
  *         @arg @ref RCC_AHBPeriph_CRC
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_AHBPeriphResetCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));

  uint32_t tmp = RCC_AHBPeriph << 24;

  RCC_REGWR_UNLOCK();

  if (NewState != DISABLE)
  {
    RCC->PERIRST |= tmp;
  }
  else
  {
    RCC->PERIRST &= (~tmp);
  }

  RCC_REGWR_LOCK();
}

/**
  * @brief  Forces or releases APB peripheral reset.
  * @param  RCC_APBPeriph: specifies the APB peripheral to reset.
  *         This parameter can be any combination of the following values:
  *         @arg @ref RCC_APBPeriph_UART1
  *         @arg @ref RCC_APBPeriph_UART2
  *         @arg @ref RCC_APBPeriph_I2C
  *         @arg @ref RCC_APBPeriph_LPUART
  *         @arg @ref RCC_APBPeriph_SPI
  *         @arg @ref RCC_APBPeriph_LPTIM
  *         @arg @ref RCC_APBPeriph_BASETIM
  *         @arg @ref RCC_APBPeriph_SYSCON
  *         @arg @ref RCC_APBPeriph_PCA
  *         @arg @ref RCC_APBPeriph_OWIRE
  *         @arg @ref RCC_APBPeriph_TIM1
  *         @arg @ref RCC_APBPeriph_TIM2
  *         @arg @ref RCC_APBPeriph_WWDG
  *         @arg @ref RCC_APBPeriph_ADC
  *         @arg @ref RCC_APBPeriph_AWK
  *         @arg @ref RCC_APBPeriph_CLKTRIM
  *         @arg @ref RCC_APBPeriph_LVDVC
  *         @arg @ref RCC_APBPeriph_BEEP
  *         @arg @ref RCC_APBPeriph_DBG
  * @param  NewState: new state of the specified peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_APBPeriphResetCmd(uint32_t RCC_APBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_APB_PERIPH(RCC_APBPeriph));

  RCC_REGWR_UNLOCK();

  if (NewState != DISABLE)
  {
    RCC->PERIRST |= RCC_APBPeriph;
  }
  else
  {
    RCC->PERIRST &= ~RCC_APBPeriph;
  }

  RCC_REGWR_LOCK();
}

/**
  * @brief  Forces or releases RTC peripheral reset.
  * @param  NewState: new state of the RTC peripheral reset.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RCC_RTCPeriphResetCmd(FunctionalState NewState)
{
  uint32_t rcc_rtcrst;

  RCC_REGWR_UNLOCK();

  if (NewState != DISABLE)
  {
    RCC->RTCRST |= (0x01 | (RCC_SYSTEMCR_UNLOCK_KEY << RCC_SYSTEMCR_UNLOCK_Pos));
  }
  else
  {
    rcc_rtcrst = RCC->RTCRST;
    rcc_rtcrst &= (~0x01);
    rcc_rtcrst |= (RCC_SYSTEMCR_UNLOCK_KEY << RCC_SYSTEMCR_UNLOCK_Pos);
    RCC->RTCRST = rcc_rtcrst;
  }

  RCC_REGWR_LOCK();
}

/**
  * @brief  Checks whether the specified RCC reset flag is set or not.
  * @param  RCC_RSTFLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *         @arg @ref RCC_RSTFLAG_MCURST: MCU reset-option byte reload.
  *         @arg @ref RCC_RSTFLAG_CPURST: CPU reset-no option byte reload.
  *         @arg @ref RCC_RSTFLAG_WWDGRST: Window Watchdog reset.
  *         @arg @ref RCC_RSTFLAG_IWDGRST: Independent Watchdog reset.
  *         @arg @ref RCC_RSTFLAG_LVDRST: Low Voltage Detect reset.
  *         @arg @ref RCC_RSTFLAG_PORRST: PowerON reset.
  *         @arg @ref RCC_RSTFLAG_LOCKUPRST: CPU Lockup reset.
  *         @arg @ref RCC_RSTFLAG_PADRST: Pad reset.
  *         @arg @ref RCC_RSTFLAG_SFTRST: Software reset.
  * @retval The new state of RCC_RSTFLAG (SET or RESET).
  */
FlagStatus RCC_GetResetFlagStatus(uint32_t RCC_RSTFLAG)
{
  /* Check the parameters */
  assert_param(IS_RCC_RESET_FLAG(RCC_RSTFLAG));

  FlagStatus bitstatus = RESET;

  if ((RCC->RSTSR & RCC_RSTFLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Clear the specified RCC reset flag.
  * @param  RCC_RSTFLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *         @arg @ref RCC_RSTFLAG_MCURST: MCU reset-option byte reload.
  *         @arg @ref RCC_RSTFLAG_CPURST: CPU reset-no option byte reload.
  *         @arg @ref RCC_RSTFLAG_WWDGRST: Window Watchdog reset.
  *         @arg @ref RCC_RSTFLAG_IWDGRST: Independent Watchdog reset.
  *         @arg @ref RCC_RSTFLAG_LVDRST: Low Voltage Detect reset.
  *         @arg @ref RCC_RSTFLAG_PORRST: PowerON reset.
  *         @arg @ref RCC_RSTFLAG_LOCKUPRST: CPU Lockup reset.
  *         @arg @ref RCC_RSTFLAG_PADRST: Pad reset.
  *         @arg @ref RCC_RSTFLAG_SFTRST: Software reset.
  * @retval None.
  */
void RCC_ClearResetFlags(uint32_t RCC_RSTFLAG)
{
  /* Check the parameters */
  assert_param(IS_RCC_RESET_FLAG(RCC_RSTFLAG));
  
  RCC->RSTSR &= (~RCC_RSTFLAG);
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
