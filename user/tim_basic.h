#include "stdint.h"
#include "stm32f091xc.h"

#define TIMB TIM7
#define TIMB_START TIMB->CR1|= TIM_CR1_CEN
#define TIMB_STOP TIMB->CR1&= ~(TIM_CR1_CEN)


void InitTimBasic(void);

