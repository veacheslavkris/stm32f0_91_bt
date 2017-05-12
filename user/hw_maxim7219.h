#ifndef HW_MAXIM7219_H
#define HW_MAXIM7219_H

#include "stm32f091xc.h"
#include "gpio.h"





void LatchMax7219Off(void);
void LatchMax7219On(void);
void ClkMax7219Off(void);
void ClkMax7219On(void);
void SetDataPin(uint32_t val);
//void HwMax7219_InitRcc(void);

void HwMax7219_InitGpio(void);






#endif


