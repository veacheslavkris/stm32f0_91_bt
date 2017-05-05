#include "led.h"
#include "stm32f091xc.h"




void LedBlockIndicating(uint32_t ms_on, uint32_t ms_off, uint32_t frq)
{
	uint32_t count;
	
	for(count = 0; count < frq; count++)
	{
		LED_ON;
		delay_led_ms(ms_on);
		
		LED_OFF;
		delay_led_ms(ms_off);
	}

}







