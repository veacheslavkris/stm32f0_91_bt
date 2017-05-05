#include "stdint.h"

#define LED_GREEN_A5_PIN	GPIO_ODR_5

#define LED_ON			GPIOA->BSRR = GPIO_BSRR_BS_5
#define LED_OFF			GPIOA->BRR = GPIO_BRR_BR_5
#define LED_TOGGLE	GPIOA->ODR ^= LED_GREEN_A5_PIN;

void LedBlockIndicating(uint32_t ms_on, uint32_t ms_off, uint32_t ms_frq);


extern void delay_led_ms(uint32_t ms);

















