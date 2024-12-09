;/**************************************************************************//**
; * @file     startup_wbewf003.s
; * @brief    CMSIS Core Device Startup File for
; *           wbewf003 Device
; * @version  V0.0.4
; * @date     23-April-2023
; ******************************************************************************/
;/*
; * Copyright (c) 2020 - 2023 Westberry Technology (ChangZhou) Corp., Ltd. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

                MODULE   ?cstartup

                ;; Forward declaration of sections.
                SECTION  CSTACK:DATA:NOROOT(3)

                SECTION  .intvec:CODE:NOROOT(2)

                EXTERN   __iar_program_start
                EXTERN   SystemInit
                PUBLIC   __vector_table
                PUBLIC   __vector_table_0x1c
                PUBLIC   __Vectors
                PUBLIC   __Vectors_End
                PUBLIC   __Vectors_Size

                DATA

__vector_table
                DCD      sfe(CSTACK)              ;     Top of Stack
                DCD      Reset_Handler            ;     Reset Handler
                DCD      NMI_Handler              ; -14 NMI Handler
                DCD      HardFault_Handler        ; -13 Hard Fault Handler
                DCD      0                        ;     Reserved
                DCD      0                        ;     Reserved
                DCD      0                        ;     Reserved
__vector_table_0x1c
                DCD      0                        ;     Reserved
                DCD      0                        ;     Reserved
                DCD      0                        ;     Reserved
                DCD      0                        ;     Reserved
                DCD      SVC_Handler              ;  -5 SVCall Handler
                DCD      0                        ;     Reserved
                DCD      0                        ;     Reserved
                DCD      PendSV_Handler           ;  -2 PendSV Handler
                DCD      SysTick_Handler          ;  -1 SysTick Handler

                ; Interrupts
                DCD     GPIOA_IRQHandler          ;  0: GPIOA
                DCD     GPIOB_IRQHandler          ;  1: GPIOB
                DCD     GPIOC_IRQHandler          ;  2: GPIOC
                DCD     GPIOD_IRQHandler          ;  3: GPIOD
                DCD     FLASH_IRQHandler          ;  4: FLASH
                DCD     0                         ;  5: Reserved
                DCD     UART1_IRQHandler          ;  6: UART1
                DCD     UART2_IRQHandler          ;  7: UART2
                DCD     LPUART_IRQHandler         ;  8: LPUART
                DCD     0                         ;  9: Reserved
                DCD     SPI_IRQHandler            ; 10: SPI
                DCD     0                         ; 11: Reserved
                DCD     I2C_IRQHandler            ; 12: I2C
                DCD     0                         ; 13: Reserved
                DCD     TIM10_IRQHandler          ; 14: TIM10
                DCD     TIM11_IRQHandler          ; 15: TIM11
                DCD     LPTIM_IRQHandler          ; 16: LPTIM
                DCD     0                         ; 17: Reserved
                DCD     TIM1_IRQHandler           ; 18: TIM1
                DCD     TIM2_IRQHandler           ; 19: TIM2
                DCD     0                         ; 20: Reserved
                DCD     PCA_IRQHandler            ; 21: PCA
                DCD     WWDG_IRQHandler           ; 22: WWDG
                DCD     IWDG_IRQHandler           ; 23: IWDG
                DCD     ADC_IRQHandler            ; 24: ADC
                DCD     LVD_IRQHandler            ; 25: LVD
                DCD     VCMP_IRQHandler           ; 26: VCMP
                DCD     0                         ; 27: Reserved
                DCD     AWK_IRQHandler            ; 28: AWK
                DCD     OWIRE_IRQHandler          ; 29: OWIRE
                DCD     RTC_IRQHandler            ; 30: RTC
                DCD     CLKTRIM_IRQHandler        ; 31: CLKTRIM

__Vectors_End

__Vectors       EQU      __vector_table
__Vectors_Size  EQU      __Vectors_End - __Vectors


                THUMB

; Reset Handler

                PUBWEAK  Reset_Handler
                SECTION  .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =__iar_program_start
                BX       R0


                PUBWEAK NMI_Handler
                PUBWEAK HardFault_Handler
                PUBWEAK SVC_Handler
                PUBWEAK PendSV_Handler
                PUBWEAK SysTick_Handler

                PUBWEAK GPIOA_IRQHandler
                PUBWEAK GPIOB_IRQHandler
                PUBWEAK GPIOC_IRQHandler
                PUBWEAK GPIOD_IRQHandler
                PUBWEAK FLASH_IRQHandler
                PUBWEAK UART1_IRQHandler
                PUBWEAK UART2_IRQHandler
                PUBWEAK LPUART_IRQHandler
                PUBWEAK SPI_IRQHandler
                PUBWEAK I2C_IRQHandler
                PUBWEAK TIM10_IRQHandler
                PUBWEAK TIM11_IRQHandler
                PUBWEAK LPTIM_IRQHandler
                PUBWEAK TIM1_IRQHandler
                PUBWEAK TIM2_IRQHandler
                PUBWEAK PCA_IRQHandler
                PUBWEAK WWDG_IRQHandler
                PUBWEAK IWDG_IRQHandler
                PUBWEAK ADC_IRQHandler
                PUBWEAK LVD_IRQHandler
                PUBWEAK VCMP_IRQHandler
                PUBWEAK AWK_IRQHandler
                PUBWEAK OWIRE_IRQHandler
                PUBWEAK RTC_IRQHandler
                PUBWEAK CLKTRIM_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
HardFault_Handler
SVC_Handler
PendSV_Handler
SysTick_Handler

GPIOA_IRQHandler
GPIOB_IRQHandler
GPIOC_IRQHandler
GPIOD_IRQHandler
FLASH_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
LPUART_IRQHandler
SPI_IRQHandler
I2C_IRQHandler
TIM10_IRQHandler
TIM11_IRQHandler
LPTIM_IRQHandler
TIM1_IRQHandler
TIM2_IRQHandler
PCA_IRQHandler
WWDG_IRQHandler
IWDG_IRQHandler
ADC_IRQHandler
LVD_IRQHandler
VCMP_IRQHandler
AWK_IRQHandler
OWIRE_IRQHandler
RTC_IRQHandler
CLKTRIM_IRQHandler
Default_Handler
                B        .


                END
