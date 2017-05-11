#ifndef HW_MAXIM7219_H
#define HW_MAXIM7219_H

#include "stm32f091xc.h"





//#define PIN_CLK_PA0_D_POS			((uint32_t)0)
//#define PIN_DOUT_PA1_D_POS		((uint32_t)1)
//#define PIN_LATCH_PA4_D_POS		((uint32_t)4)





void HWInitMax7219Gpio( GPIO_TypeDef* PORT_CLK,   uint32_t PIN_CLK_D_POS, 
												GPIO_TypeDef* PORT_DOUT,  uint32_t PIN_DOUT_D_POS,  
												GPIO_TypeDef* PORT_LATCH, uint32_t PIN_LATCH_D_POS);



void LatchMax7219Off(void);
void LatchMax7219On(void);
void ClkMax7219Off(void);
void ClkMax7219On(void);
void SetDataPin(uint32_t val);









#endif


