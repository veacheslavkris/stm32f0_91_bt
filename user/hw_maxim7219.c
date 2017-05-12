#include "hw_maxim7219.h"

/******************************************************************************/
/*                        PORTS AND PINS DEFINITION                          */
/******************************************************************************/
// PA0
GPIO_TypeDef* PORT_CLK = GPIOA;
uint32_t PIN_CLK_POS = 0;

// PA1
GPIO_TypeDef* PORT_DOUT  = GPIOA;
uint32_t PIN_DOUT_POS = 1;

//PA4
GPIO_TypeDef* PORT_LATCH = GPIOA;
uint32_t PIN_LATCH_POS = 4;

void LatchMax7219Off(void)
{
//	GPIOB->BRR = GPIO_BRR_BR_0;
	PORT_LATCH->BRR = 1 << PIN_LATCH_POS;
}
//

void LatchMax7219On(void)
{
//	GPIOB->BSRR = GPIO_BSRR_BS_0;
	PORT_LATCH->BSRR = 1 << PIN_LATCH_POS;
}
//

void ClkMax7219Off(void)
{
//	GPIOC->BRR = GPIO_BRR_BR_0;

	PORT_CLK->BRR = 1 << PIN_CLK_POS;
}
//

void ClkMax7219On(void)
{
//	GPIOC->BSRR = GPIO_BSRR_BS_0;
	
	PORT_CLK->BSRR = 1 << PIN_CLK_POS;
}
//

void SetDataPin(uint32_t val)
{
//	if(val) GPIOC->BSRR = GPIO_BSRR_BS_1;
//	else GPIOC->BRR = GPIO_BRR_BR_1;
	
	if(val) PORT_DOUT->BSRR = 1 << PIN_DOUT_POS;
	else PORT_DOUT->BRR = 1 << PIN_DOUT_POS;
}
//

//void HwMax7219_InitRcc(void)
//{
//	// MAXIM7219
//	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//}

void HwMax7219_InitGpio(void)
{
		// MAXIM7219
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	GpioSetModeOutputStrong(GPIOA, PIN_CLK_POS, OSPEEDR_HIGH);
	GpioSetModeOutputStrong(GPIOA, PIN_DOUT_POS, OSPEEDR_HIGH);
	GpioSetModeOutputStrong(GPIOA, PIN_LATCH_POS, OSPEEDR_HIGH);


}









