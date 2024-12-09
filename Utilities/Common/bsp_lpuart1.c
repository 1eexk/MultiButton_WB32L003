#include "bsp_lpuart1.h"
#include "wb32l003.h"

/**
  * @name   print_init
  * @brief  Initializes the LPUART peripheral.
  * @param  apbclk: Specifies the clock frequency of the APB where the UART resides.
  * @param  baud: Specifies the baud rate for communication.
  * @retval None
  */
void print_init(uint32_t baud)
{
    /* Enable GPIOD and LPUART clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD,  ENABLE);
    RCC_APBPeriphClockCmd(RCC_APBPeriph_LPUART, ENABLE);

    /* Reset LPUART */
    RCC_APBPeriphResetCmd(RCC_APBPeriph_LPUART, ENABLE);
    RCC_APBPeriphResetCmd(RCC_APBPeriph_LPUART, DISABLE);

    /*
        PD0 LPUART_TX
    */
    GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_PUPD_NOPULL | GPIO_OTYPE_PP | GPIO_SPEED_HIGH | GPIO_AF5);

    /* Configure LPUART */
    LPUART_InitTypeDef Print_InitStruct;
    LPUART_StructInit(&Print_InitStruct);
    LPUART_Init(LPUART, &Print_InitStruct);
    LPUART_Cmd(LPUART, ENABLE);
}
