/**
 * @file    wb32l003_rtc.c
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file provides all the RTC firmware functions.
 */

/* Includes ------------------------------------------------------------------*/
#include "wb32l003_rtc.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC
  * @brief RTC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Masks Definition */
#define RTC_TIME_RESERVED_MASK    ((uint32_t)0x073F7F7F)
#define RTC_DATE_RESERVED_MASK    ((uint32_t)0x00FF9F3F)
#define RTC_WeekDay_RESERVED_MASK ((uint32_t)0x07000000)
#define RTC_INIT_MASK             ((uint32_t)RTC_ISR_WAIT_Msk)
#define RTC_ISR_INITF             ((uint32_t)RTC_ISR_WAITF)
#define RTC_ISR_INIT              ((uint32_t)RTC_ISR_WAIT)
#define RTC_RSF_MASK              ((uint32_t)0xFFFFFFFA)
#define RTC_FLAGS_MASK            ((uint32_t)(RTC_FLAG_ALR2F | RTC_FLAG_ALR1F | RTC_FLAG_RSF | \
                                              RTC_FLAG_WAITF | RTC_FLAG_WAIT))

#define INITMODE_TIMEOUT          ((uint32_t)0x00010000)
#define SYNCHRO_TIMEOUT           ((uint32_t)0x00020000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint8_t RTC_ByteToBcd2(uint8_t Value);
static uint8_t RTC_Bcd2ToByte(uint8_t Value);

/* Private functions ---------------------------------------------------------*/
/** @defgroup RTC_Private_Functions
  * @{
  */ 

/**
  * @brief  Initializes the RTC registers according to the specified parameters 
  *         in RTC_InitStruct.
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure that contains 
  *         the configuration information for the RTC peripheral.
  * @note   The RTC Prescaler register is write protected and can be written in 
  *         initialization mode only.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC registers are initialized.
  *         - ERROR: RTC registers are not initialized.
  */
ErrorStatus RTC_Init(RTC_InitTypeDef* RTC_InitStruct)
{
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
  assert_param(IS_RTC_CLK_SOURCE(RTC_InitStruct->RTC_CLKSEL));
  assert_param(IS_RTC_HSE_DIV(RTC_InitStruct->RTC_HSEDIV));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  RTC->CR |= (uint32_t)0x00000100;
  RTC->CLKCR |= (uint32_t)0x00100000;
  
  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  } 
  else
  {
    /* Clear RTC CR FMT Bit */
    RTC->CR &= ((uint32_t)~(RTC_CR_FMT));
    /* Set RTC_CR register */
    RTC->CR |= ((uint32_t)(RTC_InitStruct->RTC_HourFormat));

    /* Set RTC_CLKCT register */
    RTC->CLKCR |= ((uint32_t)(RTC_InitStruct->RTC_CLKSEL));

    if (RTC_InitStruct->RTC_CLKSEL == RTC_CLOCK_HSE)
    {
      /* Set RTC_CLKCT register */
      RTC->CLKCR |= ((uint32_t)(RTC_InitStruct->RTC_HSEDIV));
    }

    /* Exit Initialization mode */
    RTC_ExitInitMode();

    status = SUCCESS;
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF; 
  
  return status;
}

/**
  * @brief  Enables or disables the RTC registers write protection.
  * @note   Writing a wrong key reactivates the write protection.
  * @note   The protection mechanism is not affected by system reset.
  * @param  NewState: new state of the write protection.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WriteProtectionCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the write protection for RTC registers */
    RTC->WPR = 0xFF;
  }
  else
  {
    /* Disable the write protection for RTC registers */
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
  }
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @note   The RTC Initialization mode is write protected, use the
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC is in Init mode.
  *         - ERROR: RTC is not in Init mode.
  */
ErrorStatus RTC_EnterInitMode(void)
{
  __IO uint32_t initcounter = 0x00;
  ErrorStatus status = ERROR;
  uint32_t initstatus = 0x00;

  /* Check if the Initialization mode is set */
  if ((RTC->ISR & RTC_ISR_INITF) == (uint32_t)RESET)
  {
    /* Set the Initialization mode */
    RTC->ISR = (uint32_t)RTC_INIT_MASK;

    /* Wait till RTC is in INIT state and if Time out is reached exit */
    do
    {
      initstatus = RTC->ISR & RTC_ISR_INITF;
      initcounter++;
    } while ((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));

    if ((RTC->ISR & RTC_ISR_INITF) != RESET)
    {
      status = SUCCESS;
    }
    else
    {
      status = ERROR;
    }
  }
  else
  {
    status = SUCCESS;
  }

  return (status);
}

/**
  * @brief  Exits the RTC Initialization mode.
  * @note   When the initialization sequence is complete, the calendar restarts 
  *         counting after 4 RTCCLK cycles.
  * @note   The RTC Initialization mode is write protected, use the 
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @param  None
  * @retval None
  */
void RTC_ExitInitMode(void)
{
  /* Exit Initialization mode */
  RTC->ISR &= (uint32_t)~RTC_ISR_INIT;
}

/**
  * @brief  Waits until the RTC Time and Date registers (RTC_TR and RTC_DR) are
  *         synchronized with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the 
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function. 
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC registers are synchronised.
  *         - ERROR: RTC registers are not synchronised.
  */
ErrorStatus RTC_WaitForSynchro(void)
{
  __IO uint32_t synchrocounter = 0;
  ErrorStatus status = ERROR;
  uint32_t synchrostatus = 0x00;

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Clear RSF flag */
  RTC->ISR &= (uint32_t)RTC_RSF_MASK;

  /* Wait the registers to be synchronised */
  do
  {
    synchrostatus = RTC->ISR & RTC_ISR_RSF;
    synchrocounter++;
  } while ((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));

  if ((RTC->ISR & RTC_ISR_RSF) != RESET)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;

  return (status);
}

/**
  * @brief  Enables or Disables the Bypass Shadow feature.
  * @note   When the Bypass Shadow is enabled the calendar value are taken
  *         directly from the Calendar counter.
  * @param  NewState: new state of the Bypass Shadow feature.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_BypassShadowCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  if (NewState != DISABLE)
  {
    /* Set the BYPSHAD bit */
    RTC->CR |= (uint8_t)RTC_CR_BYPSHAD;
  }
  else
  {
    /* Reset the BYPSHAD bit */
    RTC->CR &= (uint8_t)~RTC_CR_BYPSHAD;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Set the RTC current time.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *         This parameter can be  one of the following values:
  *         @arg @ref RTC_Format_BIN: Binary data format.
  *         @arg @ref RTC_Format_BCD: BCD data format.
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that contains
  *         the time configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC Time register is configured.
  *         - ERROR: RTC Time register is not configured.
 */
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef *RTC_TimeStruct)
{
  uint32_t tmpreg = 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  if (RTC_Format == RTC_Format_BIN)
  {
    if ((RTC->CR & RTC_CR_FMT) == (uint32_t)RESET)
    {
      assert_param(IS_RTC_HOUR12(RTC_TimeStruct->RTC_Hours));
      assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
    }
    else
    {
      RTC_TimeStruct->RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_TimeStruct->RTC_Hours));
    }
    assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
  }
  else
  {
    if ((RTC->CR & RTC_CR_FMT) == (uint32_t)RESET)
    {
      tmpreg = RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
      assert_param(IS_RTC_HOUR12(tmpreg));
      assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
    }
    else
    {
      RTC_TimeStruct->RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
    }
    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds)));
  }

  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpreg = (((uint32_t)(RTC_TimeStruct->RTC_Hours) << 16) |
              ((uint32_t)(RTC_TimeStruct->RTC_Minutes) << 8) |
              ((uint32_t)RTC_TimeStruct->RTC_Seconds) |
              ((uint32_t)(RTC_TimeStruct->RTC_H12) << 21));
  }
  else
  {
    tmpreg = (uint32_t)(((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Hours) << 16) |
                        ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Minutes) << 8) |
                        ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Seconds)) |
                        (((uint32_t)RTC_TimeStruct->RTC_H12) << 21));
  }

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }
  else
  {
    /* Set the RTC_TR register */
    RTC->TIME = (uint32_t)(tmpreg & RTC_TIME_RESERVED_MASK) | (RTC->TIME & (RTC_TIME_WEEK));

    /* Exit Initialization mode */
    RTC_ExitInitMode();

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if ((RTC->CR & RTC_CR_BYPSHAD) == RESET)
    {
      if (RTC_WaitForSynchro() == ERROR)
      {
        status = ERROR;
      }
      else
      {
        status = SUCCESS;
      }
    }
    else
    {
      status = SUCCESS;
    }
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF; 
    
  return status;
}

/**
  * @brief  Fills each RTC_TimeStruct member with its default value
  *         (Time = 00h:00min:00sec).
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure which will be 
  *         initialized.
  * @retval None
  */
void RTC_TimeStructInit(RTC_TimeTypeDef* RTC_TimeStruct)
{
  /* Time = 00h:00min:00sec */
  RTC_TimeStruct->RTC_H12 = RTC_H12_AM;
  RTC_TimeStruct->RTC_Hours = 0;
  RTC_TimeStruct->RTC_Minutes = 0;
  RTC_TimeStruct->RTC_Seconds = 0; 
}

/**
  * @brief  Get the RTC current Time.
  * @param  RTC_Format: specifies the format of the returned parameters.
  *         This parameter can be  one of the following values:
  *         @arg @ref RTC_Format_BIN: Binary data format.
  *         @arg @ref RTC_Format_BCD: BCD data format.
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that will 
  *         contain the returned current time configuration.
  * @retval None
  */
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef* RTC_TimeStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the RTC_TR register */
  tmpreg = (uint32_t)(RTC->TIME & RTC_TIME_RESERVED_MASK);

  /* Fill the structure fields with the read parameters */
  if ((RTC->CR & RTC_CR_FMT) == (uint32_t)RESET)
  { // 12h
    RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & (RTC_TIME_HOUR19)) >> 16);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)((tmpreg & (RTC_TIME_MIN)) >> 8);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)(tmpreg & (RTC_TIME_SEC));
    RTC_TimeStruct->RTC_H12 = (uint8_t)((tmpreg & (RTC_TIME_H20_PA)) >> 21);
  }
  else
  { // 24h
    RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & (RTC_TIME_HOUR19 | RTC_TIME_H20_PA)) >> 16);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)((tmpreg & (RTC_TIME_MIN)) >> 8);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)(tmpreg & (RTC_TIME_SEC));
    RTC_TimeStruct->RTC_H12 = 0;
  }
  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_TimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds);
  }
}

/**
  * @brief  Set the RTC current date.
  * @param  RTC_Format: specifies the format of the entered parameters.
  *         This parameter can be  one of the following values:
  *         @arg @ref RTC_Format_BIN: Binary data format.
  *         @arg @ref RTC_Format_BCD: BCD data format.
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure that contains 
  *         the date configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC Date register is configured.
  *         - ERROR: RTC Date register is not configured.
  */
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef *RTC_DateStruct)
{
  uint32_t tmpregDATE = 0;
  uint32_t tmpregTIME = 0;
  ErrorStatus status = ERROR;
  
  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  if ((RTC_Format == RTC_Format_BIN) && ((RTC_DateStruct->RTC_Month & 0x10) == 0x10))
  {
    RTC_DateStruct->RTC_Month = (RTC_DateStruct->RTC_Month & (uint32_t)~(0x10)) + 0x0A;
  }
  if (RTC_Format == RTC_Format_BIN)
  {
    assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
    assert_param(IS_RTC_MONTH(RTC_DateStruct->RTC_Month));
    assert_param(IS_RTC_DATE(RTC_DateStruct->RTC_Date));
    assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->RTC_WeekDay));
  }
  else
  {
    assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year)));

    tmpregDATE = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
    assert_param(IS_RTC_MONTH(tmpregDATE));

    tmpregDATE = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
    assert_param(IS_RTC_DATE(tmpregDATE));

    tmpregDATE = RTC_Bcd2ToByte(RTC_DateStruct->RTC_WeekDay);
    assert_param(IS_RTC_DATE(tmpregDATE));
  }
  assert_param(IS_RTC_CEN(RTC_DateStruct->RTC_Cen));

  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpregDATE = ((((uint32_t)RTC_DateStruct->RTC_Year) << 16) |
                  (((uint32_t)RTC_DateStruct->RTC_Month) << 8) |
                  ((uint32_t)RTC_DateStruct->RTC_Date) |
                  (((uint32_t)RTC_DateStruct->RTC_Cen) << 15));

    tmpregTIME = (((uint32_t)RTC_DateStruct->RTC_WeekDay) << 24);
  }
  else
  {
    tmpregDATE = (((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Year) << 16) |
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Month) << 8) |
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Date)) |
                  ((uint32_t)RTC_DateStruct->RTC_Cen << 15));

    tmpregTIME = (((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_WeekDay)) << 24);
  }
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Set Initialization mode */
  if (RTC_EnterInitMode() == ERROR)
  {
    status = ERROR;
  }
  else
  {
    /* Set the RTC_DR register */
    RTC->DATE = (uint32_t)(tmpregDATE & RTC_DATE_RESERVED_MASK);
    RTC->TIME |= (uint32_t)(tmpregTIME & RTC_WeekDay_RESERVED_MASK);

    /* Exit Initialization mode */
    RTC_ExitInitMode(); 

    /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
    if ((RTC->CR & RTC_CR_BYPSHAD) == RESET)
    {
    if(RTC_WaitForSynchro() == ERROR)
    {
      status = ERROR;
    }
    else
    {
      status = SUCCESS;
    }
  }
    else
    {
      status = SUCCESS;
    }
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;   
  
  return status;
}

/**
  * @brief  Fills each RTC_DateStruct member with its default value
  *         (Monday, January 01 xx00).
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure which will be 
  *         initialized.
  * @retval None
  */
void RTC_DateStructInit(RTC_DateTypeDef* RTC_DateStruct)
{
  /* Monday, January 01 xx00 */
  RTC_DateStruct->RTC_Cen = 1;
  RTC_DateStruct->RTC_WeekDay = RTC_Weekday_Monday;
  RTC_DateStruct->RTC_Date = 1;
  RTC_DateStruct->RTC_Month = RTC_Month_January;
  RTC_DateStruct->RTC_Year = 0;
}

/**
  * @brief  Get the RTC current date. 
  * @param  RTC_Format: specifies the format of the returned parameters.
  *         This parameter can be one of the following values:
  *         @arg @ref RTC_Format_BIN: Binary data format.
  *         @arg @ref RTC_Format_BCD: BCD data format.
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure that will 
  *         contain the returned current date configuration.
  * @retval None
  */
void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef* RTC_DateStruct)
{
  uint32_t tmpregDATE = 0;
  uint32_t tmpregTIME = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the RTC_TR register */
  tmpregDATE = (uint32_t)(RTC->DATE & RTC_DATE_RESERVED_MASK);
  tmpregTIME = (uint32_t)(RTC->TIME & RTC_TIME_RESERVED_MASK);

  /* Fill the structure fields with the read parameters */
  RTC_DateStruct->RTC_Year = (uint8_t)((tmpregDATE & (RTC_DATE_YEAR)) >> 16);
  RTC_DateStruct->RTC_Month = (uint8_t)((tmpregDATE & (RTC_DATE_MONTH)) >> 8);
  RTC_DateStruct->RTC_Date = (uint8_t)(tmpregDATE & (RTC_DATE_DAY));
  RTC_DateStruct->RTC_Cen = (uint8_t)((tmpregDATE & (RTC_DATE_CEN)) >> 15);
  RTC_DateStruct->RTC_WeekDay = (uint8_t)((tmpregTIME & (RTC_TIME_WEEK)) >> 24);

  /* Check the input parameters format */
  if (RTC_Format == RTC_Format_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_DateStruct->RTC_Year = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year);
    RTC_DateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
    RTC_DateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
    RTC_DateStruct->RTC_WeekDay = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_WeekDay);
  }
}

/**
  * @brief  Set the specified RTC Alarm1.
  * @note   The Alarm1 register can only be written when the corresponding Alarm
  *         is disabled (Use the RTC_AlarmCmd(DISABLE)).
  * @param  RTC_Format: specifies the format of the returned parameters.
  *         This parameter can be one of the following values:
  *         @arg @ref RTC_Format_BIN: Binary data format.
  *         @arg @ref RTC_Format_BCD: BCD data format.
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that
  *         contains the alarm configuration parameters.
  * @retval None
  */
void RTC_SetAlarm1(uint32_t RTC_Format, RTC_AlarmTypeDef *RTC_AlarmStruct)
{
  uint32_t tmpregTime = 0;
  uint32_t tmpregDate = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  if ((RTC_Format == RTC_Format_BIN) && ((RTC_AlarmStruct->RTC_AlarmDate.RTC_Month & 0x10) == 0x10))
  {
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = (RTC_AlarmStruct->RTC_AlarmDate.RTC_Month & (uint32_t) ~(0x10)) + 0x0A;
  }
  if (RTC_Format == RTC_Format_BIN)
  {
    assert_param(IS_RTC_YEAR(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year));
    assert_param(IS_RTC_MONTH(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month));
    assert_param(IS_RTC_DATE(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date));
    assert_param(IS_RTC_WEEKDAY(RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay));
  }
  else
  {
    assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year)));

    tmpregDate = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month);
    assert_param(IS_RTC_MONTH(tmpregDate));

    tmpregDate = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date);
    assert_param(IS_RTC_DATE(tmpregDate));

    tmpregDate = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay);
    assert_param(IS_RTC_DATE(tmpregDate));
  }
  assert_param(IS_RTC_CEN(RTC_AlarmStruct->RTC_AlarmDate.RTC_Cen));

  if (RTC_Format == RTC_Format_BIN)
  {
    if ((RTC->CR & RTC_CR_FMT) == (uint32_t)RESET)
    {
      assert_param(IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
      assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
    }
    else
    {
      assert_param(IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
      RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
    }
    assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));
    assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));
  }
  else
  {
    if ((RTC->CR & RTC_CR_FMT) == (uint32_t)RESET)
    {
      RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
      assert_param(IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
      assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
    }
    else
    {
      RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = 0x00;
      assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours)));
    }

    assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes)));
    assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)));
  }

  /* Check the input parameters format */
  if (RTC_Format != RTC_Format_BIN)
  {
    tmpregTime = (((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) |
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) |
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds) |
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 21) |
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay) << 24));

    tmpregDate = (((uint32_t)(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year) << 16) |
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month) << 8) |
                  ((uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Date) |
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmDate.RTC_Cen) << 15));
  }
  else
  {
    tmpregTime = (((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16) |
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8) |
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds)) |
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay) << 24) |
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 21));

    tmpregDate = (((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year) << 16) |
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month) << 8) |
                  ((uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date)) |
                  ((uint32_t)(RTC_AlarmStruct->RTC_AlarmDate.RTC_Cen) << 15));
  }

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Configure the Alarm register */
  RTC->ALM1TIME = (uint32_t)tmpregTime;
  RTC->ALM1DATE = (uint32_t)tmpregDate |
                  (RTC_AlarmStruct->Alarm_Enable.Year_Enable << RTC_ALM1DATE_ALMYEAREN_Pos) |
                  (RTC_AlarmStruct->Alarm_Enable.Month_Enable << RTC_ALM1DATE_ALMMONEN_Pos) |
                  (RTC_AlarmStruct->Alarm_Enable.Date_Enable << RTC_ALM1DATE_ALMDAYEN_Pos) |
                  (RTC_AlarmStruct->Alarm_Enable.WeekDay_Enable << RTC_ALM1DATE_ALMWEEKEN_Pos) |
                  (RTC_AlarmStruct->Alarm_Enable.Hours_Enable << RTC_ALM1DATE_ALMHOUREN_Pos) |
                  (RTC_AlarmStruct->Alarm_Enable.Minutes_Enable << RTC_ALM1DATE_ALMMINEN_Pos) |
                  (RTC_AlarmStruct->Alarm_Enable.Seconds_Enable << RTC_ALM1DATE_ALMSECEN_Pos) |
                  (RTC_AlarmStruct->Alarm_Enable.Sen_Enable << RTC_ALM1DATE_ALCEN_Pos);

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Fills each RTC_AlarmStruct member with its default value
  *         (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
  *         all fields are masked).
  * @param  RTC_AlarmStruct: pointer to a @ref RTC_AlarmTypeDef structure which
  *         will be initialized.
  * @retval None
  */
void RTC_Alarm1StructInit(RTC_AlarmTypeDef *RTC_AlarmStruct)
{
  /* Alarm Time Settings : Time = 00h:00mn:00sec */
  RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = 0;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = 0;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = 0;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay = 0;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_Cen = 0;
}

/**
  * @brief  Get the RTC Alarm value and masks.
  * @param  RTC_Format: specifies the format of the output parameters.
  *         This parameter can be one of the following values:
  *         @arg @ref RTC_Format_BIN: Binary data format.
  *         @arg @ref RTC_Format_BCD: BCD data format.
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that will 
  *         contains the output alarm configuration values.
  * @retval None
  */
void RTC_GetAlarm1(uint32_t RTC_Format, RTC_AlarmTypeDef *RTC_AlarmStruct)
{
  uint32_t tmpregTIME = 0;
  uint32_t tmpregDATE = 0;

  /* Check the parameters */
  assert_param(IS_RTC_FORMAT(RTC_Format));

  /* Get the RTC_ALRMxR register */
  tmpregTIME = (uint32_t)(RTC->ALM1TIME);
  tmpregDATE = (uint32_t)(RTC->ALM1DATE);

  /* Fill the structure with the read parameters */
  if ((RTC->CR & RTC_CR_FMT) == (uint32_t)RESET)
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint32_t)(tmpregTIME & RTC_TIME_HOUR19) >> RTC_ALM1TIME_ALHOUR19_Pos;
  else
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint32_t)(tmpregTIME & (RTC_TIME_HOUR19 | RTC_TIME_H20_PA)) >> RTC_ALM1TIME_ALHOUR19_Pos;

  RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint32_t)(tmpregTIME & RTC_TIME_MIN) >> RTC_ALM1TIME_ALMIN_Pos;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint32_t)(tmpregTIME & RTC_TIME_SEC) >> RTC_ALM1TIME_ALSEC_Pos;
  RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = (uint32_t)(tmpregTIME & RTC_TIME_H20_PA) >> RTC_ALM1TIME_ALH20_PA_Pos;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = (uint32_t)(tmpregDATE & RTC_DATE_YEAR) >> RTC_ALM1DATE_ALYEAR_Pos;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = (uint32_t)(tmpregDATE & RTC_DATE_MONTH) >> RTC_ALM1DATE_ALMONTH_Pos;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = (uint32_t)(tmpregDATE & RTC_DATE_DAY) >> RTC_ALM1DATE_ALDAY_Pos;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay = (uint32_t)(tmpregTIME & RTC_TIME_WEEK) >> RTC_ALM1TIME_ALWEEK_Pos;
  RTC_AlarmStruct->RTC_AlarmDate.RTC_Cen = (uint32_t)(tmpregDATE & RTC_DATE_CEN) >> RTC_ALM1DATE_ALCEN_Pos;

  RTC_AlarmStruct->Alarm_Enable.Year_Enable = (uint32_t)(tmpregDATE & RTC_ALM1DATE_ALMYEAREN) >> RTC_ALM1DATE_ALMYEAREN_Pos;
  RTC_AlarmStruct->Alarm_Enable.Month_Enable = (uint32_t)(tmpregDATE & RTC_ALM1DATE_ALMMONEN) >> RTC_ALM1DATE_ALMMONEN_Pos;
  RTC_AlarmStruct->Alarm_Enable.Date_Enable = (uint32_t)(tmpregDATE & RTC_ALM1DATE_ALMDAYEN) >> RTC_ALM1DATE_ALMDAYEN_Pos;
  RTC_AlarmStruct->Alarm_Enable.WeekDay_Enable = (uint32_t)(tmpregDATE & RTC_ALM1DATE_ALMWEEKEN) >> RTC_ALM1DATE_ALMWEEKEN_Pos;
  RTC_AlarmStruct->Alarm_Enable.Hours_Enable = (uint32_t)(tmpregDATE & RTC_ALM1DATE_ALMHOUREN) >> RTC_ALM1DATE_ALMHOUREN_Pos;
  RTC_AlarmStruct->Alarm_Enable.Minutes_Enable = (uint32_t)(tmpregDATE & RTC_ALM1DATE_ALMMINEN) >> RTC_ALM1DATE_ALMMINEN_Pos;
  RTC_AlarmStruct->Alarm_Enable.Seconds_Enable = (uint32_t)(tmpregDATE & RTC_ALM1DATE_ALMSECEN) >> RTC_ALM1DATE_ALMSECEN_Pos;
  RTC_AlarmStruct->Alarm_Enable.Sen_Enable = (uint32_t)(tmpregDATE & RTC_ALM1DATE_ALCEN_Msk) >> RTC_ALM1DATE_ALCEN_Pos;

  if (RTC_Format == RTC_Format_BIN)
  {
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_WeekDay);
  }
}

/**
  * @brief  Enables or disables the specified RTC Alarm.
  * @param  NewState: new state of the specified alarm.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_Alarm1Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* Configure the Alarm state */
  if (NewState != DISABLE)
  {
    RTC->CR |= (uint32_t)0x40;
  }
  else
  {
    /* Disable the Alarm in RTC_CR register */
    RTC->CR &= (uint32_t)~0x40;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Set the specified RTC Alarm2.
  * @param  Period the Alarm2 cycle time set.
  *         This parameter can be a value of @ref RTC_Alarm2_PERIOD
  * @retval None
  */
void RTC_SetALARM2Period(uint32_t Period)
{
  /* Check the parameters */
  assert_param(IS_RTC_ALARM_2_PERIOD(Period));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  RTC->ALM2PRD = (uint32_t)Period;

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Deactive the specified 1HZ out
  * @param  NewState: the 1HZ out enable  or disable.
  *         This parameter can be one of the following values:
  *         @arg @ref DISABLE
  *         @arg @ref ENABLE
  * @retval None
  */
void RTC_1HZ_Config(FunctionalState NewState)
{
  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  /* In case of interrupt mode is used, the interrupt source must disabled */
  if (NewState != DISABLE)
  {
    RTC->CR |= 0x02;
  }
  else
  {
    RTC->CR &= ~0x02;
  }

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Configures the Calibration Settings.
  * @param  RTC_CalibPeriod :
  * @param  RTC_CalibMinusPulsesValue:
  * @retval An ErrorStatus enumeration value:
  *         - SUCCESS: RTC Calib registers are configured.
  *         - ERROR: RTC Calib registers are not configured.
  */
void RTC_CalibConfig(uint32_t RTC_CalibPeriod, uint32_t RTC_CalibMinusPulsesValue)
{
  /* Check the parameters */
  assert_param(IS_RTC_CALIB_PERIOD(RTC_CalibPeriod));
  assert_param(IS_RTC_CALIB_MINUS(RTC_CalibMinusPulsesValue));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  RTC->RCLKTRIM = (RTC_CalibPeriod << RTC_CLKTRIM_MODE_1_0_Pos) | (RTC_CalibMinusPulsesValue);

  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifies the flag to check.
  *         This parameter can be one of the following values:
  *         @arg @ref RTC_FLAG_ALR2F: Alarm 2 flag.
  *         @arg @ref RTC_FLAG_ALR1F: Alarm 1 flag.
  *         @arg @ref RTC_FLAG_RSF: Registers Synchronized flag.
  *         @arg @ref RTC_FLAG_WAITF: Initialization mode flag.
  *         @arg @ref RTC_FLAG_WAIT: Shift operation pending flag.
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
FlagStatus RTC_GetFlagStatus(uint32_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG));

  /* Get all the flags */
  tmpreg = (uint32_t)(RTC->ISR & RTC_FLAGS_MASK);

  /* Return the status of the flag */
  if ((tmpreg & RTC_FLAG) != (uint32_t)RESET)
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
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  RTC_IT: specifies the RTC interrupt sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *         @arg @ref RTC_IT_ALR2:  Alarm 2 interrupt. 
  *         @arg @ref RTC_IT_ALR1:  Alarm 1 interrupt.
  * @param  NewState: new state of the specified RTC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_CONFIG_IT(RTC_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Disable the write protection for RTC registers */
  RTC->WPR = 0xCA;
  RTC->WPR = 0x53;

  if (NewState != DISABLE)
  {
    /* Configure the Interrupts in the RTC_CR register */
    RTC->CR |= (uint32_t)(RTC_IT);
  }
  else
  {
    /* Configure the Interrupts in the RTC_CR register */
    RTC->CR &= (uint32_t) ~(RTC_IT);
  }
  /* Enable the write protection for RTC registers */
  RTC->WPR = 0xFF;
}

/**
  * @brief  Clears the RTC's interrupt pending bits.
  * @param  RTC_IT: specifies the RTC interrupt pending bit to clear.
  *         This parameter can be any combination of the following values:
  *         @arg @ref RTC_IT_ALR2: Alarm 2 interrupt.
  *         @arg @ref RTC_IT_ALR1: Alarm 1 interrupt.
  * @retval None
  */
void RTC_ClearITPendingBit(uint32_t RTC_IT)
{

  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_IT(RTC_IT));

  /* Clear the interrupt pending bits in the RTC_ISR register */
  RTC->INTCLR |= RTC_IT;
}

/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  Value: Byte to be converted.
  * @retval Converted byte
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
  uint8_t bcdhigh = 0;
  
  while (Value >= 10)
  {
    bcdhigh++;
    Value -= 10;
  }
  
  return  ((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value: BCD value to be converted.
  * @retval Converted word
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
  uint8_t tmp = 0;
  tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (Value & (uint8_t)0x0F));
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
