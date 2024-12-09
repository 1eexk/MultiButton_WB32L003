/**
 * @file    wb32l003_rtc.h
 * @author  WestberryTech Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the RTC firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_RTC_H
#define __WB32L003_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
  uint8_t RTC_Hours;   /*!< Specifies the RTC Time Hour.
                            This parameter must be set to a value in the 1-12 range
                            if the RTC_HourFormat_12 is selected or 0-23 range
                            if the RTC_HourFormat_24 is selected. */

  uint8_t RTC_Minutes; /*!< Specifies the RTC Time Minutes.
                            This parameter must be set to a value in the 0-59 range. */

  uint8_t RTC_Seconds; /*!< Specifies the RTC Time Seconds.
                            This parameter must be set to a value in the 0-59 range. */

  uint8_t RTC_H12;     /*!< Specifies the RTC AM/PM Time.
                            This parameter can be a value of @ref RTC_AM_PM_Definitions */
} RTC_TimeTypeDef;

/**
  * @brief  RTC Date structure definition
  */
typedef struct
{
  uint32_t RTC_Year;    /*!< Specifies the RTC Date Year.
                             This parameter must be a number between Min_Data = 00 and Max_Data = 99 */

  uint8_t RTC_Month;    /*!< Specifies the RTC Date Month (in BCD format).
                             This parameter can be a value of @ref RTC_Month_Date_Definitions */

  uint8_t RTC_Date;     /*!< Specifies the RTC Date.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 31 */

  uint8_t RTC_WeekDay;  /*!< Specifies the RTC Date WeekDay.
                             This parameter can be a value of @ref RTC_WeekDay_Definitions */

  uint8_t RTC_Cen;      /*!< Specifies the RTC Date century. */

} RTC_DateTypeDef;

/**
  * @brief  RTC ALARM Enable structure definition
  */
typedef struct
{
  uint32_t Year_Enable;    /*!< Set year or not .
                                This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
  uint32_t Month_Enable;   /*!< Set month or not .
                                This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
  uint32_t Date_Enable;    /*!< Set date or not .
                                This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
  uint32_t WeekDay_Enable; /*!< Set week or not .
                                This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
  uint32_t Sen_Enable;     /*!< Set sen or not .
                                This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
  uint32_t Hours_Enable;   /*!< Set hour or not .
                                This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
  uint32_t Minutes_Enable; /*!< Set minute or not .
                                This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
  uint32_t Seconds_Enable; /*!< Set second or not .
                                This parameter can be a value of @ref RTC_AlarmEnable_Definitions */
} RTC_AlarmEnableTypeDef;

/**
  * @brief  RTC Alarm structure definition
  */
typedef struct
{
  RTC_AlarmEnableTypeDef Alarm_Enable; /*!< Specifies the RTC Alarm Enable members */
  RTC_DateTypeDef RTC_AlarmDate;       /*!< Specifies the RTC Alarm Date members */
  RTC_TimeTypeDef RTC_AlarmTime;       /*!< Specifies the RTC Alarm Time members */
} RTC_AlarmTypeDef;

/**
  * @brief  RTC Init structures definition
  */
typedef struct
{
  uint32_t RTC_HourFormat; /*!< Specifies the RTC Hour Format.
                                This parameter can be a value of @ref RTC_Hour_Formats */
  uint32_t RTC_CLKSEL;
  uint32_t RTC_HSEDIV;
} RTC_InitTypeDef;

/**
  * @brief  Time Handle Structure definition
  */
typedef struct
{
  RTC_InitTypeDef InitStruct;   /*!< RTC required parameters  */
  RTC_DateTypeDef DateToUpdate; /*!< Current date set by user and updated automatically  */
} RTC_HandleTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Exported_Constants
  * @{
  */

/** @defgroup RTC_Hour_Formats
  * @{
  */
#define RTC_HOURFORMAT_24             RTC_CR_FMT
#define RTC_HOURFORMAT_12             0x00000000U
#define IS_RTC_HOUR_FORMAT(FORMAT)    (((FORMAT) == RTC_HOURFORMAT_12) || \
                                       ((FORMAT) == RTC_HOURFORMAT_24))
/**
  * @}
  */

/** @defgroup RTC_Time_Definitions
  * @{
  */
#define IS_RTC_HOUR12(HOUR)           (((HOUR) > 0) && ((HOUR) <= 12))
#define IS_RTC_HOUR24(HOUR)           ((HOUR) <= 23)
#define IS_RTC_MINUTES(MINUTES)       ((MINUTES) <= 59)
#define IS_RTC_SECONDS(SECONDS)       ((SECONDS) <= 59)
/**
  * @}
  */

/** @defgroup RTC_AM_PM_Definitions
  * @{
  */
#define RTC_H12_AM                    ((uint8_t)0x00)
#define RTC_H12_PM                    ((uint8_t)0x01)
#define IS_RTC_H12(PM)                (((PM) == RTC_H12_AM) || ((PM) == RTC_H12_PM))
/**
  * @}
  */

/** @defgroup RTC_Year_Date_Definitions
  * @{
  */
#define IS_RTC_YEAR(YEAR) ((YEAR) <= 99)
/**
  * @}
  */

/** @defgroup RTC_Month_Date_Definitions
  * @{
  */
/* Coded in BCD format */
#define RTC_Month_January             ((uint8_t)0x01)
#define RTC_Month_February            ((uint8_t)0x02)
#define RTC_Month_March               ((uint8_t)0x03)
#define RTC_Month_April               ((uint8_t)0x04)
#define RTC_Month_May                 ((uint8_t)0x05)
#define RTC_Month_June                ((uint8_t)0x06)
#define RTC_Month_July                ((uint8_t)0x07)
#define RTC_Month_August              ((uint8_t)0x08)
#define RTC_Month_September           ((uint8_t)0x09)
#define RTC_Month_October             ((uint8_t)0x10)
#define RTC_Month_November            ((uint8_t)0x11)
#define RTC_Month_December            ((uint8_t)0x12)
#define IS_RTC_MONTH(MONTH)           (((MONTH) >= 1) && ((MONTH) <= 12))
#define IS_RTC_DATE(DATE)             (((DATE) >= 1) && ((DATE) <= 31))
#define IS_RTC_CEN(CEN)               ((CEN) <= 1)
/**
  * @}
  */

/** @defgroup RTC_WeekDay_Definitions
  * @{
  */
#define RTC_Weekday_Monday            ((uint8_t)0x00)
#define RTC_Weekday_Tuesday           ((uint8_t)0x01)
#define RTC_Weekday_Wednesday         ((uint8_t)0x02)
#define RTC_Weekday_Thursday          ((uint8_t)0x03)
#define RTC_Weekday_Friday            ((uint8_t)0x04)
#define RTC_Weekday_Saturday          ((uint8_t)0x05)
#define RTC_Weekday_Sunday            ((uint8_t)0x06)
#define IS_RTC_WEEKDAY(WEEKDAY)       (((WEEKDAY) == RTC_Weekday_Monday)    || \
                                       ((WEEKDAY) == RTC_Weekday_Tuesday)   || \
                                       ((WEEKDAY) == RTC_Weekday_Wednesday) || \
                                       ((WEEKDAY) == RTC_Weekday_Thursday)  || \
                                       ((WEEKDAY) == RTC_Weekday_Friday)    || \
                                       ((WEEKDAY) == RTC_Weekday_Saturday)  || \
                                       ((WEEKDAY) == RTC_Weekday_Sunday))
/**
  * @}
  */

/** @defgroup RTC_Input_parameter_format_definitions
  * @{
  */
#define RTC_Format_BIN                ((uint32_t)0x000000000)
#define RTC_Format_BCD                ((uint32_t)0x000000001)
#define IS_RTC_FORMAT(FORMAT)         (((FORMAT) == RTC_Format_BIN) || ((FORMAT) == RTC_Format_BCD))

/**
  * @}
  */

/** @defgroup RTC_CLOCK_SOURCE_Definitions
  * @{
  */
#define RTC_CLOCK_LSE                 (0x00UL << RTC_CLKCR_RTCCKSEL_Pos)
#define RTC_CLOCK_LSI                 (0x01UL << RTC_CLKCR_RTCCKSEL_Pos)
#define RTC_CLOCK_HSE                 (0x02UL << RTC_CLKCR_RTCCKSEL_Pos)
#define IS_RTC_CLK_SOURCE(CLK)        (((CLK) == RTC_CLOCK_LSE) ||  \
                                       ((CLK) == RTC_CLOCK_LSI) || \
                                       ((CLK) == RTC_CLOCK_HSE))
/**
  * @}
  */

/** @defgroup RTC_CLOCK_HSE_DIV_Definitions
  * @{
  */
#define IS_RTC_HSE_DIV(DIV) (((DIV) <= 0x7F))
/**
  * @}
  */

/** @defgroup RTC_Interrupts_Definitions
  * @{
  */
#define RTC_IT_ALR2                   ((uint32_t)0x00000020)
#define RTC_IT_ALR1                   ((uint32_t)0x00000010)

#define IS_RTC_CONFIG_IT(IT)          (((IT) != (uint32_t)RESET) && (((IT)&0xFFFFFFCF) == (uint32_t)RESET))
#define IS_RTC_GET_IT(IT)             (((IT) == RTC_IT_ALR1) || ((IT) == RTC_IT_ALR1))
#define IS_RTC_CLEAR_IT(IT)           (((IT) != (uint32_t)RESET) && (((IT)&0xFFFFFFCF) == (uint32_t)RESET))
/**
  * @}
  */

/** @defgroup RTC_Alarms_Definitions Alarms Definitions
  * @{
  */
#define RTC_ALARM_1 0x00U
#define RTC_ALARM_2 0x01U
/**
  * @}
  */

/** @defgroup  RTC_CLK SOURCE Definitions
  * @{
  */
#define RTC_CLK_SOURCE_LSE            (0x00000000)
#define RTC_CLK_SOURCE_LSI            (0x00010000)
#define RTC_CLK_SOURCE_HSEDIV         (0x00020000)
/**
  * @}
  */

/** @defgroup RTC_Alarm2_PERIOD Definitions 
  * @{
  */
#define RTC_ALARM2_CLOSE              ((uint8_t)0x00) /*!< RTC ALARM2 disabled                   */
#define RTC_ALARM2_1S                 ((uint8_t)0x01) /*!< RTC ALARM2 cycle time set 1s          */
#define RTC_ALARM2_1P2S               ((uint8_t)0x02) /*!< RTC ALARM2 cycle time set 1/2s        */
#define RTC_ALARM2_1P4S               ((uint8_t)0x03) /*!< RTC ALARM2 cycle time set 1/4s        */
#define RTC_ALARM2_1P8S               ((uint8_t)0x04) /*!< RTC ALARM2 cycle time set 1/8s        */
#define RTC_ALARM2_1P16S              ((uint8_t)0x05) /*!< RTC ALARM2 cycle time set 1/16s       */
#define RTC_ALARM2_1P32S              ((uint8_t)0x06) /*!< RTC ALARM2 cycle time set 1/32s       */
#define RTC_ALARM2_1P64S              ((uint8_t)0x07) /*!< RTC ALARM2 cycle time set 1/64s       */
#define RTC_ALARM2_1P128S             ((uint8_t)0x08) /*!< RTC ALARM2 cycle time set 1/128s      */
#define RTC_ALARM2_10S                ((uint8_t)0x09) /*!< RTC ALARM2 cycle time set 108s        */
#define RTC_ALARM2_30S                ((uint8_t)0x0A) /*!< RTC ALARM2 cycle time set 30s         */
#define RTC_ALARM2_1M                 ((uint8_t)0x0B) /*!< RTC ALARM2 cycle time set 1 MINUTS    */
#define RTC_ALARM2_30M                ((uint8_t)0x0C) /*!< RTC ALARM2 cycle time set 30 MINUTS   */
#define RTC_ALARM2_60M                ((uint8_t)0x0D) /*!< RTC ALARM2 cycle time set 60 MINUTS   */
#define RTC_ALARM2_12H                ((uint8_t)0x0E) /*!< RTC ALARM2 cycle time set 12 HOURS    */
#define RTC_ALARM2_24H                ((uint8_t)0x0F) /*!< RTC ALARM2 cycle time set 24 HOURS    */
#define IS_RTC_ALARM_2_PERIOD(PERIOD) (((PERIOD) == RTC_ALARM2_CLOSE)  || \
                                       ((PERIOD) == RTC_ALARM2_1S)     || \
                                       ((PERIOD) == RTC_ALARM2_1P2S)   || \
                                       ((PERIOD) == RTC_ALARM2_1P4S)   || \
                                       ((PERIOD) == RTC_ALARM2_1P8S)   || \
                                       ((PERIOD) == RTC_ALARM2_1P16S)  || \
                                       ((PERIOD) == RTC_ALARM2_1P32S)  || \
                                       ((PERIOD) == RTC_ALARM2_1P64S)  || \
                                       ((PERIOD) == RTC_ALARM2_1P128S) || \
                                       ((PERIOD) == RTC_ALARM2_10S)    || \
                                       ((PERIOD) == RTC_ALARM2_10S)    || \
                                       ((PERIOD) == RTC_ALARM2_1M)     || \
                                       ((PERIOD) == RTC_ALARM2_30M)    || \
                                       ((PERIOD) == RTC_ALARM2_60M)    || \
                                       ((PERIOD) == RTC_ALARM2_12H)    || \
                                       ((PERIOD) == RTC_ALARM2_24H))
/**
  * @}
  */

/** @defgroup RTC_Flags_Definitions Flags Definitions
  * @{
  */
#define RTC_FLAG_ALR2F                RTC_ISR_ALM2_F /* Alarm 2 flag */
#define RTC_FLAG_ALR1F                RTC_ISR_ALM1_F /* Alarm 1 flag */
#define RTC_FLAG_RSF                  RTC_ISR_RSF    /* Registers Synchronized flag */
#define RTC_FLAG_WAITF                RTC_ISR_WAITF  /* Initialization mode flag  */
#define RTC_FLAG_WAIT                 RTC_ISR_WAIT   /* Shift operation pending flag */
#define IS_RTC_GET_FLAG(FLAG)         (((FLAG) == RTC_FLAG_ALR2F) || \
                                       ((FLAG) == RTC_FLAG_ALR1F) || \
                                       ((FLAG) == RTC_FLAG_RSF)   || \
                                       ((FLAG) == RTC_FLAG_WAITF) || \
                                       ((FLAG) == RTC_FLAG_WAIT))
/**
  * @}
  */

/** @defgroup RTC_Calib_period Definitions
  * @{
  */
#define RTC_CalibPeriod_60sec         ((uint32_t)0x00000000) /*!<  if RTCCLK = 32768 Hz, calibration period is 60s  */
#define RTC_CalibPeriod_30sec         ((uint32_t)0x00000100) /*!<  if RTCCLK = 32768 Hz, calibration period is 30s  */
#define RTC_CalibPeriod_15sec         ((uint32_t)0x00000200) /*!<  if RTCCLK = 32768 Hz, calibration period is 15s  */
#define RTC_CalibPeriod_6sec          ((uint32_t)0x00000300) /*!<  if RTCCLK = 32768 Hz, calibration period is 6s  */
#define IS_RTC_CALIB_PERIOD(PERIOD)   (((PERIOD) == RTC_CalibPeriod_60sec) || \
                                       ((PERIOD) == RTC_CalibPeriod_30sec) || \
                                       ((PERIOD) == RTC_CalibPeriod_15sec) || \
                                       ((PERIOD) == RTC_CalibPeriod_6sec))
/**
  * @}
  */

/** @defgroup RTC_calib_Minus_pulses Definitions
  * @{
  */
#define IS_RTC_CALIB_MINUS(VALUE) ((VALUE) <= 0x0000007F)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


/* Initialization and Configuration functions *********************************/
ErrorStatus RTC_Init(RTC_InitTypeDef *RTC_InitStruct);

void RTC_WriteProtectionCmd(FunctionalState NewState);
ErrorStatus RTC_EnterInitMode(void);
void RTC_ExitInitMode(void);
ErrorStatus RTC_WaitForSynchro(void);
void RTC_BypassShadowCmd(FunctionalState NewState);

/* Time and Date configuration functions **************************************/
ErrorStatus RTC_SetTime(uint32_t RTC_Format, RTC_TimeTypeDef *RTC_TimeStruct);
void RTC_TimeStructInit(RTC_TimeTypeDef *RTC_TimeStruct);
void RTC_GetTime(uint32_t RTC_Format, RTC_TimeTypeDef *RTC_TimeStruct);
ErrorStatus RTC_SetDate(uint32_t RTC_Format, RTC_DateTypeDef *RTC_DateStruct);
void RTC_DateStructInit(RTC_DateTypeDef *RTC_DateStruct);
void RTC_GetDate(uint32_t RTC_Format, RTC_DateTypeDef *RTC_DateStruct);

/* Alarms (Alarm 1 and Alarm 2) configuration functions  **********************/
void RTC_SetAlarm1(uint32_t RTC_Format, RTC_AlarmTypeDef *RTC_AlarmStruct);
void RTC_AlarmStructInit(RTC_AlarmTypeDef *RTC_AlarmStruct);
void RTC_Alarm1Cmd(FunctionalState NewState);
void RTC_GetAlarm1(uint32_t RTC_Format, RTC_AlarmTypeDef *RTC_AlarmStruct);
ErrorStatus RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState);
void RTC_SetALARM2Period(uint32_t Period);

/* Output pin Configuration function ******************************************/
void RTC_1HZ_Config(FunctionalState NewState);

/* Digital Calibration configuration functions *********************************/
void RTC_CalibConfig(uint32_t RTC_CalibPeriod, uint32_t RTC_CalibMinusPulsesValue);

/* Interrupts and flags management functions **********************************/
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState);
ITStatus RTC_GetITStatus(uint32_t RTC_IT);
void RTC_ClearITPendingBit(uint32_t RTC_IT);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __WB32L003_RTC_H */
