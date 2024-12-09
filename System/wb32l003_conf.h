/**
  * @file    Project/WB32L003_StdPeriph_Template/wb32l003_conf.h
  * @author  Westberry Application Team
  * @version V0.0.4
  * @date    05-January-2023
  * @brief   Library configuration file.
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_CONF_H
#define __WB32L003_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
#include "wb32l003_gpio.h"
#include "wb32l003_rcc.h"
#include "wb32l003_tim.h"
#include "wb32l003_flash.h"
#include "wb32l003_uart.h"
#include "wb32l003_basetim.h"
#include "wb32l003_lpuart.h"
#include "wb32l003_pca.h"
#include "wb32l003_beep.h"
#include "wb32l003_adc.h"
#include "wb32l003_lptim.h"
#include "wb32l003_vcmp.h"
#include "wb32l003_lvd.h"
#include "wb32l003_i2c.h"
#include "wb32l003_iwdg.h"
#include "wb32l003_wwdg.h"
#include "wb32l003_spi.h"
#include "wb32l003_syscon.h"
#include "wb32l003_rtc.h"
#include "wb32l003_crc.h"
#include "wb32l003_awk.h"
#include "wb32l003_owire.h"
#include "wb32l003_pwr.h"
#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __WB32L003_CONF_H */
