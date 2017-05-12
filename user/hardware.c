#include "hardware.h"

void init_rcc(void)
{
	// led gpio
//	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* (1) */ 

//	// MAXIM7219
//	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	// BTN_C13, UART
//	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; 
	
//	HwMax7219_InitRcc();
}
//

void HWInitGpio()
{
//	init_rcc();
//	init_led_gpio();
//	init_I2C_gpio();
//	init_max7219_gpio();
//	init_btn_interrupt();
//	init_uart8();
	HwMax7219_InitGpio();
	
}
//

//void init_led_gpio(void)
//{
//	GpioSetModeOutputStrong(GPIOA, LED_GREEN_A5_D_POS, OSPEEDR_MEDIUM);
//}
//

//void init_I2C_gpio(void)
//{
//  /* (1) Open drain for I2C signals */
//  /* (2) AF1 for I2C signals */
//  /* (3) Select AF mode (10) on PB10 and PB11 */
//	
//	GpioSetModeI2C(GPIOB, 10, ALT_FUNC_1);
//	GpioSetModeI2C(GPIOB, 11, ALT_FUNC_1);
//}
//

//void init_max7219_gpio(void)
//{
//	GpioSetModeOutputStrong(GPIOC, PIN_CLK, OSPEEDR_MEDIUM);
//	GpioSetModeOutputStrong(GPIOC, PIN_DOUT, OSPEEDR_MEDIUM);
//	GpioSetModeOutputStrong(GPIOB, PIN_LATCH, OSPEEDR_MEDIUM);
//}
//

//void init_btn_interrupt(void)
//{
////		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
//	  RCC->APB2ENR|=RCC_APB2ENR_SYSCFGEN;
//		
//		GpioSetInterruptMode(EXTI_PC, BTN_C13_PIN_POS, EDGE_RISING_FALLING_ITR);

//		NVIC_EnableIRQ(EXTI4_15_IRQn); /* (6) */
//		NVIC_SetPriority(EXTI4_15_IRQn,0); /* (7) */
//}
//








