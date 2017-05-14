#include "uart7.h"

#define GPIO_UART				GPIOC
#define PIN_TX_D_POS		0
#define PIN_RX_D_POS		1
#define ALT_FUNC				ALT_FUNC_1

#define UART						USART7


void Uart7_Init(void)
{
	/* Enable the peripheral clock of GPIOC */
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	
	GpioSetModeUart(GPIO_UART, PIN_TX_D_POS, PIN_RX_D_POS, ALT_FUNC);

	/* Enable the peripheral clock USART8 */
  RCC->APB2ENR |= RCC_APB2ENR_USART7EN;
	UartConfigBrrTeReUe(UART, 6000000, 38400);

}



