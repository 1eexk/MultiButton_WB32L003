/******************************************************************************/
/* RETARGET.C: 'Retarget' layer for target-dependent low level functions      */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005 Keil Software. All rights reserved.                     */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <stdio.h>
#include "wb32l003.h"


#pragma import(__use_no_semihosting_swi)

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int ch, FILE *f) {

  LPUART->SCON |= LPUART_SCON_TIEN;
  LPUART->SBUF = (ch & 0xFF);
  while (!(LPUART->INTSR & LPUART_INTSR_TI));
  LPUART->INTCLR |= LPUART_INTCLR_TICLR_Msk;
  LPUART->SCON &= (~LPUART_SCON_TIEN);

  return ch;
}

int fgetc(FILE *f) {
  uint8_t ch;

  LPUART->SCON |= LPUART_SCON_RIEN;
  while (!(LPUART->INTSR & LPUART_INTSR_RI));
  ch = (LPUART->SBUF & 0xFF);
  LPUART->INTCLR |= LPUART_INTCLR_RICLR_Msk;
  LPUART->SCON &= (~LPUART_SCON_RIEN);

  return ch;
}

int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}

void _ttywrch(int ch) {
}

int __backspace()
{
  return 0;
}

void _sys_exit(int return_code) {
  while (1);    /* endless loop */
}
