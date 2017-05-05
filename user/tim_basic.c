#include "stm32f0xx.h"
#include "tim_basic.h"



void InitTimBasic(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM7EN;
	TIMB->CR1 = 0;
	TIMB->CNT = 0;
	TIMB->PSC = 12 - 1;
	TIMB->ARR = 999;
	
	TIMB->DIER |= TIM_DIER_UIE;
	
	NVIC_SetPriority(TIM7_IRQn,0);
	NVIC_EnableIRQ(TIM7_IRQn);
			
}


