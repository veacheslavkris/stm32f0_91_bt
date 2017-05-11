#ifndef HARDWARE_H
#define HARDWARE_H

#include "stm32f091xc.h"
#include "gpio.h"
//#include "uart8.h"
#include "hw_maxim7219.h"


#define LED_GREEN_A5_D_POS 		5
#define LED_GREEN_A5_B_POS		GPIO_ODR_5

//#define PIN_CLK_PA0_D_POS			((uint32_t)0)
//#define PIN_DOUT_PA1_D_POS		((uint32_t)1)
//#define PIN_LATCH_PA4_D_POS		((uint32_t)4)

//#define PIN_CLK			PIN_CLK_PA0_D_POS
//#define PIN_DOUT		PIN_DOUT_PA1_D_POS
//#define PIN_LATCH		PIN_LATCH_PA4_D_POS



#define BTN_C13_PIN_POS 			13

void HWInitGpio(void);

void init_rcc(void);


//void init_led_gpio(void);
//void init_I2C_gpio(void);
//void init_max7219_gpio(void);

//void init_btn_interrupt(void);



















#endif



