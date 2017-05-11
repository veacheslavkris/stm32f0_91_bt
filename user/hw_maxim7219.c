#include "hw_maxim7219.h"

GPIO_TypeDef* PORT_CLK;
GPIO_TypeDef* PORT_DOUT;
GPIO_TypeDef* PORT_LATCH;

uint32_t PIN_CLK_POS;
uint32_t PIN_DOUT_POS;
uint32_t PIN_LATCH_POS;

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

void HWInitMax7219Gpio( GPIO_TypeDef* P_CLK, uint32_t PIN_CLK_D_POS, GPIO_TypeDef* P_DOUT, uint32_t PIN_DOUT_D_POS, GPIO_TypeDef* P_LATCH, uint32_t PIN_LATCH_D_POS)
{
	PORT_CLK = P_CLK;
	PORT_DOUT = P_DOUT;
	PORT_LATCH = P_LATCH;
	
	PIN_CLK_POS = PIN_CLK_D_POS;
	PIN_DOUT_POS = PIN_DOUT_D_POS;
	PIN_LATCH_POS = PIN_LATCH_D_POS;
}











