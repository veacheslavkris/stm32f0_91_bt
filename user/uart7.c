#include "uart7.h"

#define GPIO_UART				GPIOC
#define PIN_TX_D_POS		0
#define PIN_RX_D_POS		1
#define ALT_FUNC				ALT_FUNC_1

#define USART						USART7


void Uart7_Init(void)
{
	/* Enable the peripheral clock of GPIOC */
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	
	GpioSetModeUart(GPIO_UART, PIN_TX_D_POS, PIN_RX_D_POS, ALT_FUNC);

	/* Enable the peripheral clock USART8 */
  RCC->APB2ENR |= RCC_APB2ENR_USART7EN;
	UartConfigBrrTeReUe(USART, 6000000, 38400);
	
	UartConfig_TC_TXNE_IE_Enable(USART);
	UartConfig_InitInterrupts(USART3_8_IRQn, 0);

}



