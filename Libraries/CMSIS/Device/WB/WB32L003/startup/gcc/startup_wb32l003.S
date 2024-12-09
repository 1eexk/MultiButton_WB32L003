/******************************************************************************
 * @file     startup_wb32l003.S
 * @brief    CMSIS Core Device Startup File for
 *           WB32F10x Device Series
 * @version  V0.0.4
 * @date     23-April-2023
 ******************************************************************************/
/*
 * Copyright (c) 2020 - 2023 Westberry Technology Corp., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

                .syntax  unified
                .arch    armv6-m

                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
__Vectors:
                .long    __StackTop                         /*     Top of Stack */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVCall Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */

                /* Interrupts */
                .long    GPIOA_IRQHandler                   /*  0: GPIOA      */
                .long    GPIOB_IRQHandler                   /*  1: GPIOB      */
                .long    GPIOC_IRQHandler                   /*  2: GPIOC      */
                .long    GPIOD_IRQHandler                   /*  3: GPIOD      */
                .long    FLASH_IRQHandler                   /*  4: FLASH      */
                .long    0                                  /*  5: Reserved   */
                .long    UART1_IRQHandler                   /*  6: UART1      */
                .long    UART2_IRQHandler                   /*  7: UART2      */
                .long    LPUART_IRQHandler                  /*  8: LPUART     */
                .long    0                                  /*  9: Reserved   */
                .long    SPI_IRQHandler                     /* 10: SPI        */
                .long    0                                  /* 11: Reserved   */
                .long    I2C_IRQHandler                     /* 12: I2C        */
                .long    0                                  /* 13: Reserved   */
                .long    TIM10_IRQHandler                   /* 14: TIM10      */
                .long    TIM11_IRQHandler                   /* 15: TIM11      */
                .long    LPTIM_IRQHandler                   /* 16: LPTIM      */
                .long    0                                  /* 17: Reserved   */
                .long    TIM1_IRQHandler                    /* 18: TIM1       */
                .long    TIM2_IRQHandler                    /* 19: TIM2       */
                .long    0                                  /* 20: Reserved   */
                .long    PCA_IRQHandler                     /* 21: PCA        */
                .long    WWDG_IRQHandler                    /* 22: WWDG       */
                .long    IWDG_IRQHandler                    /* 23: IWDG       */
                .long    ADC_IRQHandler                     /* 24: ADC        */
                .long    LVD_IRQHandler                     /* 25: LVD        */
                .long    VCMP_IRQHandler                    /* 26: VCMP         */
                .long    0                                  /* 27: Reserved   */
                .long    AWK_IRQHandler                     /* 28: AWK        */
                .long    OWIRE_IRQHandler                   /* 29: OWIRE      */
                .long    RTC_IRQHandler                     /* 30: RTC        */
                .long    CLKTRIM_IRQHandler                 /* 31: CLKTRIM    */

__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors


                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
Reset_Handler:
                bl       SystemInit

                ldr      r4, =__copy_table_start__
                ldr      r5, =__copy_table_end__

.L_loop0:
                cmp      r4, r5
                bge      .L_loop0_done
                ldr      r1, [r4]
                ldr      r2, [r4, #4]
                ldr      r3, [r4, #8]

.L_loop0_0:
                subs     r3, #4
                blt      .L_loop0_0_done
                ldr      r0, [r1, r3]
                str      r0, [r2, r3]
                b        .L_loop0_0

.L_loop0_0_done:
                adds     r4, #12
                b        .L_loop0

.L_loop0_done:

                ldr      r3, =__zero_table_start__
                ldr      r4, =__zero_table_end__

.L_loop2:
                cmp      r3, r4
                bge      .L_loop2_done
                ldr      r1, [r3]
                ldr      r2, [r3, #4]
                movs     r0, 0

.L_loop2_0:
                subs     r2, #4
                blt      .L_loop2_0_done
                str      r0, [r1, r2]
                b        .L_loop2_0
.L_loop2_0_done:

                adds     r3, #8
                b        .L_loop2
.L_loop2_done:

                bl       _start

                .size    Reset_Handler, . - Reset_Handler


                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
Default_Handler:
                b        .
                .size    Default_Handler, . - Default_Handler

/* Macro to define default exception/interrupt handlers.
 * Default handler are weak symbols with an endless loop.
 * They can be overwritten by real handlers.
 */
                .macro   Set_Default_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm


/* Default exception/interrupt handler */

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  HardFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  GPIOA_IRQHandler
                Set_Default_Handler  GPIOB_IRQHandler
                Set_Default_Handler  GPIOC_IRQHandler
                Set_Default_Handler  GPIOD_IRQHandler
                Set_Default_Handler  FLASH_IRQHandler
                Set_Default_Handler  UART1_IRQHandler
                Set_Default_Handler  UART2_IRQHandler
                Set_Default_Handler  LPUART_IRQHandler
                Set_Default_Handler  SPI_IRQHandler
                Set_Default_Handler  I2C_IRQHandler
                Set_Default_Handler  TIM10_IRQHandler
                Set_Default_Handler  TIM11_IRQHandler
                Set_Default_Handler  LPTIM_IRQHandler
                Set_Default_Handler  TIM1_IRQHandler
                Set_Default_Handler  TIM2_IRQHandler
                Set_Default_Handler  PCA_IRQHandler
                Set_Default_Handler  WWDG_IRQHandler
                Set_Default_Handler  IWDG_IRQHandler
                Set_Default_Handler  ADC_IRQHandler
                Set_Default_Handler  LVD_IRQHandler
                Set_Default_Handler  VCMP_IRQHandler
                Set_Default_Handler  AWK_IRQHandler
                Set_Default_Handler  OWIRE_IRQHandler
                Set_Default_Handler  RTC_IRQHandler
                Set_Default_Handler  CLKTRIM_IRQHandler


                .end
