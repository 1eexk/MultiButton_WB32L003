/**
 * @file    wb32l003_adc.h
 * @author  Westberry Application Team
 * @version V0.0.4
 * @date    23-April-2023
 * @brief   This file contains all the functions prototypes for the ADC firmware
 *          library.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WB32L003_ADC_H
#define __WB32L003_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"

/** @addtogroup WB32L003_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  ADC Init structure definition
  */
typedef struct
{
  uint32_t ADC_SamplingTime;        /*!< Specifies ADC sample time.
                                         This parameter can be a value of @ref ADC_Sample_Duty */

  uint32_t ADC_SingleChannelSel;    /*!< Specifies ADC channel select in single conversion mode.
                                         This parameter can be a value of @ref ADC_Single_Channel_Selection */

  uint32_t ADC_ClkSel;              /*!< Specifies ADC clock select.
                                         This parameter can be a value of @ref ADC_Clock_Selection */

  uint32_t ADC_SingleContinueMode;  /*!< Specifies ADC single/continue converstion mode select.
                                         This parameter can be a value of @ref ADC_Single/Continue_Mode_Selection */

  uint32_t ADC_AutoAccumulation;    /*!< Specifies ADC conversion result auto accumulation.
                                         This parameter can be a value of @ref ADC_Auto_Accumulation */

  uint32_t ADC_CircleMode;          /*!< Specifies whether the conversion is performed in circle mode or normal mode for multichannel
                                         This parameter can be a value of @ref ADC_Circle_Mode_Selection */

  uint32_t ADC_ConversionTimes;     /*!< Specifies the number of all channels' conversions in continue mode.
                                         This parameter can be a value between 0x00 to 0xFF */

  uint32_t ADC_ContinueChannelSel;  /*!< Specifies channels to be converted in multchannel conversion mode.
                                         This parameter can be a value of @ref ADC_Continue_Channel_Selection */

  uint32_t ADC_ExternalTrigConv1;   /*!< Selects the external interrupt 1 used to trigger the conversion.
                                         If set to ADC_SOFTWARE_START, external triggers are disabled.
                                         If set to external trigger source, triggering is on interrupt flag rising edge.
                                         This parameter can be a value of @ref ADC_External_Trigger_Source1_Selection */

  uint32_t ADC_ExternalTrigConv2;   /*!< Selects the external interrupt 2 used to trigger the conversion.
                                         If set to ADC_SOFTWARE_START, external triggers are disabled.
                                         If set to external trigger source, triggering is on interrupt flag rising edge.
                                         This parameter can be a value of @ref ADC_External_Trigger_Source2_Selection */
} ADC_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */

/** @defgroup ADC_Sample_Duty
  * @{
  */
#define ADC_SAMPLE_4CYCLE              0x00U   /*!< ADC Sample 4 cycles           */
#define ADC_SAMPLE_8CYCLE              0x800UL /*!< ADC Sample 8 cycles           */

#define IS_ADC_SAMPLE_CYCLE(CYLCE)     (((CYLCE) == ADC_SAMPLE_4CYCLE) || ((CYLCE) == ADC_SAMPLE_8CYCLE))
/**
  * @}
  */

/** @defgroup ADC_Single_Channel_Selection
  * @{
  */
#define ADC_SINGLE_CHANNEL_0           (0x00000000U)                                                   /*!< Select ADC channel 0 in single mode           */
#define ADC_SINGLE_CHANNEL_1           (ADC_CR0_SEL_0)                                                 /*!< Select ADC channel 1 in single mode           */
#define ADC_SINGLE_CHANNEL_2           (ADC_CR0_SEL_1)                                                 /*!< Select ADC channel 2 in single mode           */
#define ADC_SINGLE_CHANNEL_3           (ADC_CR0_SEL_1 | ADC_CR0_SEL_0)                                 /*!< Select ADC channel 3 in single mode           */
#define ADC_SINGLE_CHANNEL_4           (ADC_CR0_SEL_2)                                                 /*!< Select ADC channel 4 in single mode           */
#define ADC_SINGLE_CHANNEL_5           (ADC_CR0_SEL_2 | ADC_CR0_SEL_0)                                 /*!< Select ADC channel 5 in single mode           */
#define ADC_SINGLE_CHANNEL_6           (ADC_CR0_SEL_2 | ADC_CR0_SEL_1)                                 /*!< Select ADC channel 6 in single mode           */
#define ADC_SINGLE_CHANNEL_7           (ADC_CR0_SEL_2 | ADC_CR0_SEL_1 | ADC_CR0_SEL_0)                 /*!< Select ADC channel 7(VCAP) in single mode     */

#define ADC_SINGLE_CHANNEL_8           (ADC_CR0_SEL_3)                                                 /*!< Select ADC channel 8 in single mode           */
#define ADC_SINGLE_CHANNEL_9           (ADC_CR0_SEL_3 | ADC_CR0_SEL_0)                                 /*!< Select ADC channel 9 in single mode           */
#define ADC_SINGLE_CHANNEL_10          (ADC_CR0_SEL_3 | ADC_CR0_SEL_1)                                 /*!< Select ADC channel 10 in single mode          */
#define ADC_SINGLE_CHANNEL_11          (ADC_CR0_SEL_3 | ADC_CR0_SEL_1 | ADC_CR0_SEL_0)                 /*!< Select ADC channel 11 in single mode          */
#define ADC_SINGLE_CHANNEL_12          (ADC_CR0_SEL_3 | ADC_CR0_SEL_2)                                 /*!< Select ADC channel 12 in single mode          */
#define ADC_SINGLE_CHANNEL_13          (ADC_CR0_SEL_3 | ADC_CR0_SEL_2 | ADC_CR0_SEL_0)                 /*!< Select ADC channel 13 in single mode          */
#define ADC_SINGLE_CHANNEL_14          (ADC_CR0_SEL_3 | ADC_CR0_SEL_2 | ADC_CR0_SEL_1)                 /*!< Select ADC channel 14 in single mode          */
#define ADC_SINGLE_CHANNEL_15          (ADC_CR0_SEL_3 | ADC_CR0_SEL_2 | ADC_CR0_SEL_1 | ADC_CR0_SEL_0) /*!< Select ADC channel 15 in single mode          */

#define IS_ADC_SINGLE_CHANNEL(CHANNEL) (((CHANNEL) == ADC_SINGLE_CHANNEL_0) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_1) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_2) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_3) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_4) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_5) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_6) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_7) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_8) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_9) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_10) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_11) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_12) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_13) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_14) ||  \
                                        ((CHANNEL) == ADC_SINGLE_CHANNEL_15))
/**
  * @}
  */

/** @defgroup ADC_Clock_Selection
  * @{
  */
#define ADC_CLOCK_PCLK_DIV1             (0x00000000U)                                            /*!< Select ADC clock PCLK          */
#define ADC_CLOCK_PCLK_DIV2             (ADC_CR0_CLKSEL_0)                                       /*!< Select ADC clock PCLK/2        */
#define ADC_CLOCK_PCLK_DIV4             (ADC_CR0_CLKSEL_1)                                       /*!< Select ADC clock PCLK/4        */
#define ADC_CLOCK_PCLK_DIV8             (ADC_CR0_CLKSEL_1 | ADC_CR0_CLKSEL_0)                    /*!< Select ADC clock PCLK/8        */
#define ADC_CLOCK_PCLK_DIV16            (ADC_CR0_CLKSEL_2)                                       /*!< Select ADC clock PCLK/16       */
#define ADC_CLOCK_PCLK_DIV32            (ADC_CR0_CLKSEL_2 | ADC_CR0_CLKSEL_0)                    /*!< Select ADC clock PCLK/32       */
#define ADC_CLOCK_PCLK_DIV64            (ADC_CR0_CLKSEL_2 | ADC_CR0_CLKSEL_1)                    /*!< Select ADC clock PCLK/64       */
#define ADC_CLOCK_PCLK_DIV128           (ADC_CR0_CLKSEL_2 | ADC_CR0_CLKSEL_1 | ADC_CR0_CLKSEL_0) /*!< Select ADC clock PCLK/128      */

#define IS_ADC_CLOCK_PCLK_DIV(CLOCK)    (((CLOCK) == ADC_CLOCK_PCLK_DIV1) || ((CLOCK) == ADC_CLOCK_PCLK_DIV2) ||   \
                                         ((CLOCK) == ADC_CLOCK_PCLK_DIV4) || ((CLOCK) == ADC_CLOCK_PCLK_DIV8) ||   \
                                         ((CLOCK) == ADC_CLOCK_PCLK_DIV16) || ((CLOCK) == ADC_CLOCK_PCLK_DIV32) || \
                                         ((CLOCK) == ADC_CLOCK_PCLK_DIV64) || ((CLOCK) == ADC_CLOCK_PCLK_DIV128))
/**
  * @}
  */

/** @defgroup ADC_Single/Continue_Mode_Selection
  * @{
  */
#define ADC_MODE_SINGLE                 (0x00000000U) /*!< Select ADC single mode   */
#define ADC_MODE_CONTINUE               (ADC_CR1_CT)  /*!< Select ADC continue mode */

#define IS_ADC_SINGLEMODE(MODE)         (((MODE) == ADC_MODE_SINGLE) || ((MODE) == ADC_MODE_CONTINUE))
/**
  * @}
  */

/** @defgroup ADC_Compare_Mode
  * @{
  */
#define ADC_None_Threshold_Compare      (0x00000000) /*!< Disable Comparation with threshold  */
#define ADC_Low_Threshold_Compare       (0x01 << 12) /*!< Compare with high threshold  */
#define ADC_High_Threshold_Compare      (0x01 << 13) /*!< Compare with low threshold   */
#define ADC_Range_Threshold_Compare     (0x01 << 14) /*!< Compare with range threshold */

#define ADC_Threshold_Comapre_Mask      (ADC_Low_Threshold_Compare | ADC_High_Threshold_Compare | ADC_Range_Threshold_Compare)
#define ADC_Threshold_Compare_All       ADC_Threshold_Comapre_Mask
/**
  * @}
  */

/** @defgroup ADC_Auto_Accumulation
  * @{
  */
#define ADC_AUTOACC_DISABLE             (0x00000000U)
#define ADC_AUTOACC_ENABLE              (ADC_CR1_RACC_EN) /*!< Auto accumulation enable       */

#define IS_ADC_ACCMULATION(ACC)         (((ACC) == ADC_AUTOACC_ENABLE) || ((ACC) == ADC_AUTOACC_DISABLE))
/**
  * @}
  */

/** @defgroup ADC_Circle_Mode_Selection
  * @{
  */
#define ADC_MULTICHANNEL_NONCIRCLE      (0x00000000U)
#define ADC_MULTICHANNEL_CIRCLE         (ADC_CR2_CIRCLE_MODE) /*!< ADC multichannel conversion circle mode   */

#define IS_ADC_CIRCLEMODE(MODE)         (((MODE) == ADC_MULTICHANNEL_NONCIRCLE) || ((MODE) == ADC_MULTICHANNEL_CIRCLE))
/**
  * @}
  */

/** @defgroup ADC_Continue_Channel_Selection
  * @{
  */
#define ADC_CONTINUE_CHANNEL_0           (ADC_CR2_CHEN_0)  /*!< Select ADC channel 0 in continue mode          */
#define ADC_CONTINUE_CHANNEL_1           (ADC_CR2_CHEN_1)  /*!< Select ADC channel 1 in continue mode          */
#define ADC_CONTINUE_CHANNEL_2           (ADC_CR2_CHEN_2)  /*!< Select ADC channel 2 in continue mode          */
#define ADC_CONTINUE_CHANNEL_3           (ADC_CR2_CHEN_3)  /*!< Select ADC channel 3 in continue mode          */
#define ADC_CONTINUE_CHANNEL_4           (ADC_CR2_CHEN_4)  /*!< Select ADC channel 4 in continue mode          */
#define ADC_CONTINUE_CHANNEL_5           (ADC_CR2_CHEN_5)  /*!< Select ADC channel 5 in continue mode          */
#define ADC_CONTINUE_CHANNEL_6           (ADC_CR2_CHEN_6)  /*!< Select ADC channel 6 in continue mode          */
#define ADC_CONTINUE_CHANNEL_7           (ADC_CR2_CHEN_7)  /*!< Select ADC channel 7(VCAP) in continue mode    */

#define ADC_CONTINUE_CHANNEL_8           (ADC_CR2_CHEN_8 )  /*!< Select ADC channel 8  in continue mode        */
#define ADC_CONTINUE_CHANNEL_9           (ADC_CR2_CHEN_9 )  /*!< Select ADC channel 9  in continue mode        */
#define ADC_CONTINUE_CHANNEL_10          (ADC_CR2_CHEN_10)  /*!< Select ADC channel 10 in continue mode        */
#define ADC_CONTINUE_CHANNEL_11          (ADC_CR2_CHEN_11)  /*!< Select ADC channel 11 in continue mode        */
#define ADC_CONTINUE_CHANNEL_12          (ADC_CR2_CHEN_12)  /*!< Select ADC channel 12 in continue mode        */
#define ADC_CONTINUE_CHANNEL_13          (ADC_CR2_CHEN_13)  /*!< Select ADC channel 13 in continue mode        */
#define ADC_CONTINUE_CHANNEL_14          (ADC_CR2_CHEN_14)  /*!< Select ADC channel 14 in continue mode        */
#define ADC_CONTINUE_CHANNEL_15          (ADC_CR2_CHEN_15)  /*!< Select ADC channel 15 in continue mode        */

#define ADC_CONTINUE_CHANNEL_ALL         (0x0FF000FF)

#define IS_ADC_CONTINUE_CHANNEL(CHANNEL) (((CHANNEL) & ADC_CONTINUE_CHANNEL_ALL) != 0x0000)
#define IS_ADC_CHANNEL(CHANNEL)          ((IS_ADC_SINGLE_CHANNEL(CHANNEL)) || (IS_ADC_CONTINUE_CHANNEL(CHANNEL)))
/**
  * @}
  */

/** @defgroup ADC_Interrupts
  * @{
  */
#define ADC_IT_CONTINUE                  ADC_INTEN_CONT_IEN /*!< ADC End of Continue Conversion interrupt source */
#define ADC_IT_RANGE_THRESHOLD           ADC_INTEN_REG_IEN /*!< ADC conversion data in defined range interrupt source */
#define ADC_IT_HIGH_THRESHOLD            ADC_INTEN_HHT_IEN /*!< ADC conversion data above threshold interrupt source */
#define ADC_IT_LOW_THRESHOLD             ADC_INTEN_LLT_IEN /*!< ADC conversion data below threshold interrupt source */

#define ADC_IT_CHANNEL15                 ADC_INTEN_ADCXIEN_15 /*!< ADC End of channel 15 conversion interrupt source */
#define ADC_IT_CHANNEL14                 ADC_INTEN_ADCXIEN_14 /*!< ADC End of channel 14 conversion interrupt source */
#define ADC_IT_CHANNEL13                 ADC_INTEN_ADCXIEN_13 /*!< ADC End of channel 13 conversion interrupt source */
#define ADC_IT_CHANNEL12                 ADC_INTEN_ADCXIEN_12 /*!< ADC End of channel 12 conversion interrupt source */
#define ADC_IT_CHANNEL11                 ADC_INTEN_ADCXIEN_11 /*!< ADC End of channel 11 conversion interrupt source */
#define ADC_IT_CHANNEL10                 ADC_INTEN_ADCXIEN_10 /*!< ADC End of channel 10 conversion interrupt source */
#define ADC_IT_CHANNEL9                  ADC_INTEN_ADCXIEN_9  /*!< ADC End of channel 9 conversion interrupt source */
#define ADC_IT_CHANNEL8                  ADC_INTEN_ADCXIEN_8  /*!< ADC End of channel 8 conversion interrupt source */

#define ADC_IT_CHANNEL7                  ADC_INTEN_ADCXIEN_7 /*!< ADC End of channel 7 conversion interrupt source */
#define ADC_IT_CHANNEL6                  ADC_INTEN_ADCXIEN_6 /*!< ADC End of channel 6 conversion interrupt source */
#define ADC_IT_CHANNEL5                  ADC_INTEN_ADCXIEN_5 /*!< ADC End of channel 5 conversion interrupt source */
#define ADC_IT_CHANNEL4                  ADC_INTEN_ADCXIEN_4 /*!< ADC End of channel 4 conversion interrupt source */
#define ADC_IT_CHANNEL3                  ADC_INTEN_ADCXIEN_3 /*!< ADC End of channel 3 conversion interrupt source */
#define ADC_IT_CHANNEL2                  ADC_INTEN_ADCXIEN_2 /*!< ADC End of channel 2 conversion interrupt source */
#define ADC_IT_CHANNEL1                  ADC_INTEN_ADCXIEN_1 /*!< ADC End of channel 1 conversion interrupt source */
#define ADC_IT_CHANNEL0                  ADC_INTEN_ADCXIEN_0 /*!< ADC End of channel 0 conversion interrupt source */
#define ADC_IT_MASK                     (0xFFFFFUL) /*!< ADC interrupt mask */

#define IS_ADC_IT(ADC_IT)               (((ADC_IT) & ADC_IT_MASK) != 0x00000)
/**
  * @}
  */

/** @defgroup ADC_Raw_Interrupt_Flags 
  * @{
  */
#define ADC_RAWINTFLAG                  ADC_RAWINTSR_CONT_INTF /*!< ADC End of Continue Conversion raw interrupt flag */
#define ADC_RAWINTFLAG_RANGE_THRESHOLD  ADC_RAWINTSR_REG_INTF  /*!< ADC conversion data in defined range raw interrupt flag */
#define ADC_RAWINTFLAG_HIGH_THRESHOLD   ADC_RAWINTSR_HHT_INTF  /*!< ADC conversion data above threshold raw interrupt flag */
#define ADC_RAWINTFLAG_LOW_THERSHOLD    ADC_RAWINTSR_LLT_INTF  /*!< ADC conversion data below threshold raw interrupt flag */

#define ADC_RAWINTFLAG_CHANNEL15        ADC_RAWINTSR_ADCRIS_15 /*!< ADC End of channel 15 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL14        ADC_RAWINTSR_ADCRIS_14 /*!< ADC End of channel 14 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL13        ADC_RAWINTSR_ADCRIS_13 /*!< ADC End of channel 13 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL12        ADC_RAWINTSR_ADCRIS_12 /*!< ADC End of channel 12 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL11        ADC_RAWINTSR_ADCRIS_11 /*!< ADC End of channel 11 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL10        ADC_RAWINTSR_ADCRIS_10 /*!< ADC End of channel 10 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL9         ADC_RAWINTSR_ADCRIS_9  /*!< ADC End of channel 9 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL8         ADC_RAWINTSR_ADCRIS_8  /*!< ADC End of channel 8 conversion raw interrupt flag */

#define ADC_RAWINTFLAG_CHANNEL7         ADC_RAWINTSR_ADCRIS_7 /*!< ADC End of channel 7 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL6         ADC_RAWINTSR_ADCRIS_6 /*!< ADC End of channel 6 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL5         ADC_RAWINTSR_ADCRIS_5 /*!< ADC End of channel 5 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL4         ADC_RAWINTSR_ADCRIS_4 /*!< ADC End of channel 4 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL3         ADC_RAWINTSR_ADCRIS_3 /*!< ADC End of channel 3 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL2         ADC_RAWINTSR_ADCRIS_2 /*!< ADC End of channel 2 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL1         ADC_RAWINTSR_ADCRIS_1 /*!< ADC End of channel 1 conversion raw interrupt flag */
#define ADC_RAWINTFLAG_CHANNEL0         ADC_RAWINTSR_ADCRIS_0 /*!< ADC End of channel 0 conversion raw interrupt flag */

#define ADC_RAWINTFLAG_CHANNEL_ALL      (ADC_RAWINTFLAG_CHANNEL0 | ADC_RAWINTFLAG_CHANNEL1 | ADC_RAWINTFLAG_CHANNEL2 | ADC_RAWINTFLAG_CHANNEL3 | \
                                         ADC_RAWINTFLAG_CHANNEL4 | ADC_RAWINTFLAG_CHANNEL5 | ADC_RAWINTFLAG_CHANNEL6 | ADC_RAWINTFLAG_CHANNEL7 | \
                                         ADC_RAWINTFLAG_CHANNEL8 | ADC_RAWINTFLAG_CHANNEL9 | ADC_RAWINTFLAG_CHANNEL10 | ADC_RAWINTFLAG_CHANNEL11 | \
                                         ADC_RAWINTFLAG_CHANNEL12 | ADC_RAWINTFLAG_CHANNEL13 | ADC_RAWINTFLAG_CHANNEL14 | ADC_RAWINTFLAG_CHANNEL15)
#define IS_ADC_RAWINTFLAG(FLAG)         (((FLAG) & ADC_RAWINTFLAG_LOW_THERSHOLD) | \
                                         ((FLAG) & ADC_RAWINTFLAG_LOW_THERSHOLD) | \
                                         ((FLAG) & ADC_RAWINTFLAG_LOW_THERSHOLD) | \
                                         ((FLAG) & ADC_RAWINTFLAG_LOW_THERSHOLD) | \
                                         ((FLAG) & ADC_RAWINTFLAG_CHANNEL_ALL))
/**
  * @}
  */

/** @defgroup ADC_Interrupt_Flags
  * @{
  */
#define ADC_INTFLAG                     ADC_MSKINTSR_CONT_MIF /*!< ADC End of Continue Conversion interrupt flag */
#define ADC_INTFLAG_RANGE_THRESHOLD     ADC_MSKINTSR_REG_MIF  /*!< ADC conversion data in defined range interrupt flag */
#define ADC_INTFLAG_HIGH_THRESHOLD      ADC_MSKINTSR_HHT_MIF  /*!< ADC conversion data above threshold interrupt flag */
#define ADC_INTFLAG_LOW_THERSHOLD       ADC_MSKINTSR_LLT_MIF  /*!< ADC conversion data below threshold interrupt flag */

#define ADC_INTFLAG_CHANNEL15           ADC_MSKINTSR_ADCMIS_15 /*!< ADC End of channel15 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL14           ADC_MSKINTSR_ADCMIS_14 /*!< ADC End of channel14 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL13           ADC_MSKINTSR_ADCMIS_13 /*!< ADC End of channel13 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL12           ADC_MSKINTSR_ADCMIS_12 /*!< ADC End of channel12 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL11           ADC_MSKINTSR_ADCMIS_11 /*!< ADC End of channel11 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL10           ADC_MSKINTSR_ADCMIS_10 /*!< ADC End of channel10 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL9            ADC_MSKINTSR_ADCMIS_9  /*!< ADC End of channel9 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL8            ADC_MSKINTSR_ADCMIS_8  /*!< ADC End of channel8 conversion interrupt flag */

#define ADC_INTFLAG_CHANNEL7            ADC_MSKINTSR_ADCMIS_7 /*!< ADC End of channel 7 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL6            ADC_MSKINTSR_ADCMIS_6 /*!< ADC End of channel 6 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL5            ADC_MSKINTSR_ADCMIS_5 /*!< ADC End of channel 5 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL4            ADC_MSKINTSR_ADCMIS_4 /*!< ADC End of channel 4 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL3            ADC_MSKINTSR_ADCMIS_3 /*!< ADC End of channel 3 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL2            ADC_MSKINTSR_ADCMIS_2 /*!< ADC End of channel 2 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL1            ADC_MSKINTSR_ADCMIS_1 /*!< ADC End of channel 1 conversion interrupt flag */
#define ADC_INTFLAG_CHANNEL0            ADC_MSKINTSR_ADCMIS_0 /*!< ADC End of channel 0 conversion interrupt flag */

#define ADC_INTFLAG_CHANNEL_ALL         (ADC_INTFLAG_CHANNEL0 | ADC_INTFLAG_CHANNEL1 | ADC_INTFLAG_CHANNEL2 | ADC_INTFLAG_CHANNEL3 | \
                                         ADC_INTFLAG_CHANNEL4 | ADC_INTFLAG_CHANNEL5 | ADC_INTFLAG_CHANNEL6 | ADC_INTFLAG_CHANNEL7 | \
                                         ADC_INTFLAG_CHANNEL8 | ADC_INTFLAG_CHANNEL9 | ADC_INTFLAG_CHANNEL10 | ADC_INTFLAG_CHANNEL11 | \
                                         ADC_INTFLAG_CHANNEL12 | ADC_INTFLAG_CHANNEL13 | ADC_INTFLAG_CHANNEL14 | ADC_INTFLAG_CHANNEL15)
#define IS_ADC_INTFLAG(FLAG)            (((FLAG) & ADC_INTFLAG_LOW_THERSHOLD) | \
                                         ((FLAG) & ADC_INTFLAG_LOW_THERSHOLD) | \
                                         ((FLAG) & ADC_INTFLAG_LOW_THERSHOLD) | \
                                         ((FLAG) & ADC_INTFLAG_LOW_THERSHOLD) | \
                                         ((FLAG) & ADC_INTFLAG_CHANNEL_ALL))
/**
  * @}
  */

/** @defgroup ADC_External_Trigger_Source1_Selection
  * @{
  */
#define ADC_SOFTWARE_START              (0x00000000U)
#define ADC_EXTTRIG1_TIM10              (ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_TIM11              (ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_TIM1               (ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_LPTIM              (ADC_CR1_TRIGS0_2)
#define ADC_EXTTRIG1_TIM1_TRGO          (ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_TIM2_TRGO          (ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_TIM2_INT           (ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_UART1_INT          (ADC_CR1_TRIGS0_3)
#define ADC_EXTTRIG1_UART2_INT          (ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_LPUART_INT         (ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_VC0_INT            (ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_NC                 (ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2)
#define ADC_EXTTRIG1_RTC_INT            (ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PCA_INT            (ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_SPI_INT            (ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PA1_INT            (ADC_CR1_TRIGS0_4)
#define ADC_EXTTRIG1_PA2_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PA3_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_PB4_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PB5_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_2)
#define ADC_EXTTRIG1_PC3_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PC4_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PC5_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_PC6_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_3)
#define ADC_EXTTRIG1_PC7_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PD1_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_PD2_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PD3_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2)
#define ADC_EXTTRIG1_PD4_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PD5_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_PD6_INT            (ADC_CR1_TRIGS0_4 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)

#define ADC_EXTTRIG1_PA4_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PB0_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_PB1_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PB2_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_2)
#define ADC_EXTTRIG1_PB3_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PB6_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_PB7_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_2 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PC0_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_3)
#define ADC_EXTTRIG1_PC1_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PC2_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_1)
#define ADC_EXTTRIG1_PD0_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_1 | ADC_CR1_TRIGS0_0)
#define ADC_EXTTRIG1_PD7_INT            (ADC_CR1_TRIGS0_5 | ADC_CR1_TRIGS0_3 | ADC_CR1_TRIGS0_2)
#define ADC_EXTTRIG1_MASK               (0x1F | 0x10000)

#define IS_ADC_EXTRIG1(EXTRIG)          ((((EXTRIG) & ADC_EXTTRIG1_MASK) != 0x0000) || ((EXTRIG) == ADC_SOFTWARE_START))
/**
  * @}
  */

/** @defgroup ADC_External_Trigger_Source2_Selection
  * @{
  */
#define ADC_EXTTRIG2_TIM10              (ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_TIM11              (ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_TIM1               (ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_LPTIM              (ADC_CR1_TRIGS1_2 |)
#define ADC_EXTTRIG2_TIM1_TRGO          (ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_TIM2_TRGO          (ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_TIM2_INT           (ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_UART0_INT          (ADC_CR1_TRIGS1_3)
#define ADC_EXTTRIG2_UART1_INT          (ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_LPUART_INT         (ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_VC0_INT            (ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_NC                 (ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2)
#define ADC_EXTTRIG2_RTC_INT            (ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PCA_INT            (ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_SPI_INT            (ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PA1_INT            (ADC_CR1_TRIGS1_4)
#define ADC_EXTTRIG2_PA2_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PA3_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_PB4_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PB5_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_2)
#define ADC_EXTTRIG2_PC3_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PC4_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PC5_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_PC6_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_3)
#define ADC_EXTTRIG2_PC7_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PD1_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_PD2_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PD3_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2)
#define ADC_EXTTRIG2_PD4_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PD5_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_PD6_INT            (ADC_CR1_TRIGS1_4 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)

#define ADC_EXTTRIG2_PA4_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PB0_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_PB1_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PB2_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_2)
#define ADC_EXTTRIG2_PB3_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PB6_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_PB7_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_2 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PC0_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_3)
#define ADC_EXTTRIG2_PC1_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PC2_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_1)
#define ADC_EXTTRIG2_PD0_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_1 | ADC_CR1_TRIGS1_0)
#define ADC_EXTTRIG2_PD7_INT            (ADC_CR1_TRIGS1_5 | ADC_CR1_TRIGS1_3 | ADC_CR1_TRIGS1_2)
#define ADC_EXTTRIG2_MASK               (0x3E0 | 0x20000)

#define IS_ADC_EXTRIG2(EXTRIG)          ((((EXTRIG) & ADC_EXTTRIG2_MASK) != 0x0000) || ((EXTRIG) == ADC_SOFTWARE_START))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

void ADC_DeInit(void);
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct);
void ADC_Cmd(FunctionalState NewState);
void ADC_ITConfig(uint32_t ADC_IT, FunctionalState NewState);
void ADC_SoftwareStartConvCmd(FunctionalState NewState);
FlagStatus ADC_GetSoftwareStartConvStatus(void);
uint16_t ADC_GetConversionValue(uint32_t Chnannel);
uint32_t ADC_GetAccValue(void);
FlagStatus ADC_GetFlagStatus(uint16_t ADC_FLAG);
FlagStatus ADC_GetRawFlagStatus(uint16_t ADC_FLAG);
ITStatus ADC_GetITStatus(uint16_t ADC_IT);
void ADC_ClearFlag(uint16_t ADC_FLAG);
void ADC_ClearITPendingBit(uint16_t ADC_IT);
void ADC_ThresholdsConfig(uint16_t LowThreshold, uint16_t HighThreshold);
void ADC_ThresholdsCompareCmd(uint16_t Threshold_Config, FunctionalState NewState);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__WB32L003_ADC_H */
