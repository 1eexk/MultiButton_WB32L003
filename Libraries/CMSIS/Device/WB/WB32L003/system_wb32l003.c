 /**
 * @file     system_wb32l003.c
 * @brief    CMSIS Device System Source File for
 *           WB32L003 Device Series
 * @version  V0.0.4
 * @date     23-April-2023
 */
/*!< 
   1. This file provides two functions and one global variable to be called from
       user application:
        - SystemInit(): Setups the system clock (System clock source, AHB/APB
                        prescalers). This function is called at startup just
                        after reset and before branch to main program. This call
                        is made inside the "startup_wb32l003_xx.s" file.
  
        - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
                                    by the user application to setup the SysTick
                                    timer or configure other parameters.
  
        - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
                                   be called whenever the core clock is changed
                                   during program execution.
  
   2. After each device reset the HSI (4 MHz) is used as system clock source.
      Then SystemInit() function is called, in "startup_wb32l003_xx.s" file, to
      configure the system clock before to branch to main program.
  
   4. The default value of HSE crystal is set to 8 MHz (or other values, depending on
      the crystal used), refer to "HSE_VALUE".
      When HSE is used as system clock source directly and you are using different
      crystal you have to adapt the HSE value to your own configuration.
 */


/** @addtogroup WB32L003_System_Private_Includes
  * @{
  */
#include "wb32l003.h"

/**
  * @}
  */


/** @addtogroup WB32L003_System_Private_Defines
  * @{
  */


/**
  * @}
  */

#if !defined  (HSI_VALUE_24M) 
  #define HSI_VALUE_24M        ((uint32_t)24000000) /*!< Value of the Internal oscillator select 24MHz */
#endif /* HSI_VALUE_24M */

#if !defined  (HSI_VALUE_22M) 
  #define HSI_VALUE_22M        ((uint32_t)22120000) /*!< Value of the Internal oscillator select 22.12MHz */
#endif /* HSI_VALUE_22M */

#if !defined  (HSI_VALUE_16M)
  #define HSI_VALUE_16M        ((uint32_t)16000000) /*!< Value of the Internal oscillator select 16MHz */
#endif /* HSI_VALUE_16M */

#if !defined  (HSI_VALUE_8M)
  #define HSI_VALUE_8M         ((uint32_t)8000000) /*!< Value of the Internal oscillator select 8MHz */
#endif /* HSI_VALUE_8M */

#if !defined  (HSI_VALUE_4M)
  #define HSI_VALUE_4M         ((uint32_t)4000000) /*!< Value of the Internal oscillator select 4MHz */
#endif /* HSI_VALUE_4M */

/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */ 
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00000000U /*!< Vector Table base offset field. */

#if defined(MAINCLK_FREQ_HSE) && ((HSE_VALUE < 4000000) || (HSE_VALUE > 24000000))
  #error "The MAINCLK_FREQ_HSE macro can only be defined if the external crystal is 4~24MHz!"
#endif

#if defined(MAINCLK_FREQ_HSI) && (HSI_VALUE != 4000000) && (HSI_VALUE != 8000000) && (HSI_VALUE != 16000000)  && (HSI_VALUE != 22120000)  && (HSI_VALUE != 24000000)
  #error "The MAINCLK_FREQ_HSI macro can only be defined if the internal crystal is 4MHz/8MHz/16MHz/22.12MHz/24MHz!"
#endif

#if defined(MAINCLK_FREQ_LSE) && (LSE_VALUE != 32768)
  #error "The MAINCLK_FREQ_LSE macro can only be defined if the external crystal is 32.768KHz!"
#endif

#if defined(MAINCLK_FREQ_LSI) && (LSI_VALUE != 32768) && (LSI_VALUE != 38400)
  #error "The MAINCLK_FREQ_LSI macro can only be defined if the external crystal is 32.768KHz/38.4KHz!"
#endif

/**
  * @}
  */

/** @addtogroup WB32L003_System_Private_Variables
  * @{
  */

/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
#ifdef MAINCLK_FREQ_HSE
  uint32_t SystemCoreClock = HSE_VALUE;      /*!< System Clock Frequency (Core Clock) */
#elif defined MAINCLK_FREQ_HSI
  uint32_t SystemCoreClock = HSI_VALUE;      /*!< System Clock Frequency (Core Clock) */
#elif defined MAINCLK_FREQ_LSE
  uint32_t SystemCoreClock = LSE_VALUE;      /*!< System Clock Frequency (Core Clock) */
#elif defined MAINCLK_FREQ_LSI
  uint32_t SystemCoreClock = LSI_VALUE;      /*!< System Clock Frequency (Core Clock) */
#else
  uint32_t SystemCoreClock = 4000000;        /*!< System Clock Frequency (Core Clock) */
#endif

/**
  * @}
  */


/** @addtogroup WB32L003_System_Private_Functions
  * @{
  */
static void SetSysClock(void);

#ifdef MAINCLK_FREQ_HSE
  static void SetSysClockToHSE(void);
#elif defined MAINCLK_FREQ_HSI
  static void SetSysClockToHSI(void);
#elif defined MAINCLK_FREQ_LSE
  static void SetSysClockToLSE(void);
#elif defined MAINCLK_FREQ_LSI
  static void SetSysClockToLSI(void);
#endif


/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSIEN bit, Reset HSEEN, HSEBYP, LSIEN*/
  RCC->UNLOCK = RCC_UNLOCK_UNLOCK | (0x2AD5334C << RCC_UNLOCK_KEY_Pos);
  RCC->SYSCLKCR = RCC_SYSCLKCR_HSIEN | (0x5A69 << RCC_SYSCLKCR_KEY_Pos);
  RCC->UNLOCK = (0x2AD5334C << RCC_UNLOCK_KEY_Pos) & RCC_UNLOCK_KEY;

  /* Reset HCLK and PCLK div bits */
  RCC->HCLKDIV = 0x00000000;
  RCC->PCLKDIV = 0x0000000;

  /* Reset AHB and APB module */
  RCC->HCLKEN = 0x00000100;
  RCC->PCLKEN = 0x00000000;

  /* Reset MCO bits */
  RCC->MCOCR = 0x00000000;

  SetSysClock();
  
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_MEMORY_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
  SCB->VTOR = FLASH_MEMORY_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif 
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *           
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.         
  *     
  * @note   - The system frequency computed by this function is not the real 
  *           frequency in the chip. It is calculated based on the predefined 
  *           constant and the selected clock source:
  *             
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE_xxM(*)
  *                                              
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *         
  *         (*) HSI_VALUE_xxM is a constant defined in system_wb32l003.c file (default value
  *             4 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.   
  *    
  *         (**) HSE_VALUE is a constant defined in system_wb32l003.c file (default value
  *              8 MHz, depending on the product used), user has to ensure
  *              that HSE_VALUE is same as the real frequency of the crystal used.
  *              Otherwise, this function may have wrong result.
  *                
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint32_t tmp = 0U;
    
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW;
  
  switch (tmp)
  {
    case RCC_SYSCLKSource_HSI:  /* HSI used as system clock */
      if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_24M)
      {
        SystemCoreClock = HSI_VALUE_24M;
      }
      else if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_22M)
      {
        SystemCoreClock = HSI_VALUE_22M;
      }
      else if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_16M)
      {
        SystemCoreClock = HSI_VALUE_16M;
      }
      else if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_8M)
      {
        SystemCoreClock = HSI_VALUE_8M;
      }
      else if ((uint32_t)((RCC->HSICR & RCC_HSICR_HSITRIM) >> RCC_HSICR_HSITRIM_Pos) == RCC_HSITRIM_4M)
      {
        SystemCoreClock = HSI_VALUE_4M;
      }
      else
      {
        SystemCoreClock = HSI_VALUE_4M;
      }
      break;
    case RCC_SYSCLKSource_HSE:  /* HSE used as system clock */
      SystemCoreClock = HSE_VALUE;
      break;
    case RCC_SYSCLKSource_LSI:  /* LSI used as system clock */
      SystemCoreClock = LSI_VALUE;
      break;
    case RCC_SYSCLKSource_LSE:  /* LSE used as system clock */
      SystemCoreClock = LSE_VALUE;
      break;
    default:
      SystemCoreClock = HSI_VALUE_4M;
      break;
  }
  
  /* Compute HCLK clock frequency ----------------*/
  /* Get HCLK prescaler and caculate HCLK clock frequency*/
  if ((RCC->HCLKDIV & RCC_HCLKDIV_AHBCKDIV) != 0)
    SystemCoreClock = (SystemCoreClock >> 1) / (RCC->HCLKDIV & RCC_HCLKDIV_AHBCKDIV);
}

/**
  * @brief  Configures the main clock frequency, AHBCLK, APB1CLK and APB2CLK prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
#ifdef MAINCLK_FREQ_HSE
  SetSysClockToHSE();
#elif defined MAINCLK_FREQ_HSI
  SetSysClockToHSI();
#elif defined MAINCLK_FREQ_LSE
  SetSysClockToLSE();
#elif defined MAINCLK_FREQ_LSI
  SetSysClockToLSI();
#endif
}

#ifdef MAINCLK_FREQ_HSE
/**
  * @brief  Selects HSE as sys clock source and configure AHBCLK, APB1CLK
  *         and APB2CLK prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToHSE(void)
{
  RCC_HSEDriveCurrentConfig(7);
  RCC_HSEStartTimeConfig(3);
  RCC_HSEConfig(RCC_HSE_ON);

  /* wait HSE clock ready */
  while ((RCC->HSECR & RCC_HSECR_HSERDY) == RESET);
  
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

  /* Wait till clock switch is ready */
  while ((RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW) != RCC_SYSCLKSource_HSE);
  
  SystemCoreClock = HSE_VALUE;
  
  RCC_AHBCLKConfig(RCC_AHBCLKDiv1);
  RCC_APBCLKConfig(RCC_APBCLKDiv1);
}

#elif defined MAINCLK_FREQ_HSI
/**
  * @brief  Selects HSI as sys clock source and configure AHBCLK, APB1CLK
  *         and APB2CLK prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToHSI(void)
{
  RCC_HSIConfig(HSI_VALUE, ENABLE);

  /* wait HSI clock ready */
  while ((RCC->HSICR & RCC_HSICR_HSIRDY) == RESET);

  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

  /* Wait till clock switch is ready */
  while ((RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW) != RCC_SYSCLKSource_HSI);
  
  SystemCoreClock = HSI_VALUE;
  
  RCC_AHBCLKConfig(RCC_AHBCLKDiv1);
  RCC_APBCLKConfig(RCC_APBCLKDiv1);
}

#elif defined MAINCLK_FREQ_LSE
/**
  * @brief  Selects LSE as sys clock source and configure AHBCLK, APB1CLK
  *         and APB2CLK prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToLSE(void)
{
  RCC_LSEDriveCurrentConfig(15);
  RCC_LSEStartTimeConfig(3);
  RCC_LSEConfig(RCC_LSE_ON);

  /* wait LSE clock ready */
  while ((RCC->LSECR & RCC_LSECR_LSERDY) == RESET);
  
  RCC_SYSCLKConfig(RCC_SYSCLKSource_LSE);

  /* Wait till clock switch is ready */
  while ((RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW) != RCC_SYSCLKSource_LSE);
  
  SystemCoreClock = LSE_VALUE;
  
  RCC_AHBCLKConfig(RCC_AHBCLKDiv1);
  RCC_APBCLKConfig(RCC_APBCLKDiv1);
}

#elif defined MAINCLK_FREQ_LSI
/**
  * @brief  Selects LSI as sys clock source and configure AHBCLK, APB1CLK
  *         and APB2CLK prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockToLSI(void)
{
  RCC_LSIConfig(LSI_VALUE, RCC_LSI_STARTUP_64CYCLE, ENABLE);

  /* wait LSI clock ready */
  while ((RCC->LSICR & RCC_LSICR_LSIRDY) == RESET);

  RCC_SYSCLKConfig(RCC_SYSCLKSource_LSI);

  /* Wait till clock switch is ready */
  while ((RCC->SYSCLKSEL & RCC_SYSCLKSEL_CLKSW) != RCC_SYSCLKSource_LSI);
  
  SystemCoreClock = LSI_VALUE;
  
  RCC_AHBCLKConfig(RCC_AHBCLKDiv1);
  RCC_APBCLKConfig(RCC_APBCLKDiv1);
}
#endif

/**
  * @}
  */
