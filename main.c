/* Includes ------------------------------------------------------------------*/
#include "wb32l003.h"
#include "bsp_lpuart1.h"
#include "multi_button.h"

//控制按键
#define BTN1_PORT       GPIOD
#define BTN1_PIN        GPIO_Pin_3

#define LED1_PORT       GPIOD
#define LED1_PIN        GPIO_Pin_2
#define LED2_PORT       GPIOD
#define LED2_PIN        GPIO_Pin_0
#define LED3_PORT       GPIOC
#define LED3_PIN        GPIO_Pin_6

#define LED1_TOGGLE     GPIO_ToggleBits(  LED1_PORT, LED1_PIN)
#define LED2_TOGGLE     GPIO_ToggleBits(  LED2_PORT, LED2_PIN)
#define LED3_TOGGLE     GPIO_ToggleBits(  LED3_PORT, LED3_PIN)


const uint8_t btn1_id = 0;
struct Button btn1;
uint8_t btn_state = 0;

uint8_t read_button_GPIO(uint8_t button_id)
{
	/* you can share the GPIO read function with multiple Buttons */
	switch(button_id)
	{
		case btn1_id:
            btn_state = GPIO_ReadInputDataBit(BTN1_PORT, BTN1_PIN);
			return btn_state;
		default:
			return 0;
	}
}

void ButtonTicks_Init(void)
{   
    // Configure SysTick to run at 200Hz
    if(SysTick_Config(SystemCoreClock/200))
    {
        while(1);
    }
}

int cnt = 0;
int main()
{
	static PressEvent btn1_event_val;

    // Init btn1/LED GPIO
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD|RCC_AHBPeriph_GPIOC, ENABLE);
    GPIO_Init(BTN1_PORT, BTN1_PIN, GPIO_MODE_IN | GPIO_SPEED_HIGH);
    GPIO_Init(LED1_PORT, LED1_PIN, GPIO_MODE_OUT | GPIO_OTYPE_PP | GPIO_PUPD_UP | GPIO_DRV_HIGH | GPIO_SPEED_HIGH);
    GPIO_Init(LED2_PORT, LED2_PIN, GPIO_MODE_OUT | GPIO_OTYPE_PP | GPIO_PUPD_UP | GPIO_DRV_HIGH | GPIO_SPEED_HIGH);
    GPIO_Init(LED3_PORT, LED3_PIN, GPIO_MODE_OUT | GPIO_OTYPE_PP | GPIO_PUPD_UP | GPIO_DRV_HIGH | GPIO_SPEED_HIGH);

	button_init(&btn1, read_button_GPIO, 0, btn1_id);
	button_start(&btn1);

	/* 
     * make the timer invoking the button_ticks() interval 5ms.
	 * This function is implemented by yourself.
    */
	// __timer_start(button_ticks, 0, 5);
    ButtonTicks_Init();

	while(1)
	{
		if(btn1_event_val != get_button_event(&btn1)) {
			btn1_event_val = get_button_event(&btn1);

			if(btn1_event_val == SINGLE_CLICK) {
				//do something
                LED1_TOGGLE;
			} else if(btn1_event_val == LONG_PRESS_START) {
				//do something
                LED2_TOGGLE;
			} else if(btn1_event_val == LONG_PRESS_HOLD) {
				//do something
                LED3_TOGGLE;
			}
		}
	}
}

void SysTick_Handler(void)
{
    button_ticks();
}

/*********************************************END OF FILE**********************/
