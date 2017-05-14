/* Includes ------------------------------------------------------------------*/
#include "uart.h"

void InitUart_7_8(void)
{
	/* Enable the peripheral clock of GPIOC */
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	
	Configure_GPIO_USART7_BT();
	Configure_USART7_BT();
	Configure_GPIO_USART8_PC();
	Configure_USART8_PC();
	Configure_USART_7_8_IT();

}

// BT connection
void Configure_GPIO_USART7_BT(void)
{
  /* Enable the peripheral clock of GPIOC */
//  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	
  /* GPIO configuration for USART7 signals */
  /* (1) Select AF mode (10) on PC0 and PC1 */
  /* (2) AF1 for USART7 signals */
  GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER0|GPIO_MODER_MODER1))\
                 | (GPIO_MODER_MODER0_1 | GPIO_MODER_MODER1_1); /* (1) */
  GPIOC->AFR[0] = (GPIOC->AFR[0] &~ (GPIO_AFRL_AFRL0 | GPIO_AFRL_AFRL1))\
//                  | (1) | (1 << (1 * 4)); /* (2) */
									| 0x0011; /* 0001 0001 (2) */
									
}

void Configure_USART7_BT(void)
{
  /* Enable the peripheral clock USART7 */
  RCC->APB2ENR |= RCC_APB2ENR_USART7EN;

  /* Configure USART7 */
  /* (1) oversampling by 16, 38400 baud */
  /* (2) 8 data bit, 1 start bit, 1 stop bit, no parity, transmit/receive */
 	USART7->BRR = 6000000 / 38400; /* (1) */
	
	USART7->CR1 = USART_CR1_TE |USART_CR1_RE | USART_CR1_UE; /* (2) */
	
  /* polling idle frame Transmission */
	while((USART7->ISR & USART_ISR_TC) != USART_ISR_TC)
  { 
    /* add time out here for a robust application */
  }
  	
	USART7->ICR |= USART_ICR_TCCF;		/* clear TC flag */
 
	USART7->CR1 |= USART_CR1_TCIE;		/* enable TC interrupt */
	USART7->CR1 |= USART_CR1_RXNEIE;	/* enable RXNE interrupt */
		
	//Configure_USART_7_8_IT
}



void Configure_GPIO_USART8_PC(void)
{
  /* Enable the peripheral clock of GPIOC */
//  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	
  /* GPIO configuration for USART8 signals */
  /* (1) Select AF mode (10) on PC2 and PC3 */
  /* (2) AF2 for USART8 signals */
  GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER2 | GPIO_MODER_MODER3))\
                 | (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1); /* (1) */
  GPIOC->AFR[0] = (GPIOC->AFR[0] &~ (GPIO_AFRL_AFRL2 | GPIO_AFRL_AFRL3))\
//                  | (2 << (2 * 4)) | (2 << (3 * 4)); /* (2) */
									| 0x2200; /* 0010 0010 0000 0000 (2) */
									
}

void Configure_USART8_PC(void)
{
  /* Enable the peripheral clock USART8 */
  RCC->APB2ENR |= RCC_APB2ENR_USART8EN;

  /* Configure USART8 */
  /* (1) oversampling by 16, 9600 baud */
  /* (2) 8 data bit, 1 start bit, 1 stop bit, no parity, transmit/receive */
 	USART8->BRR = 6000000 / 9600; /* (1) */

	USART8->CR1 = USART_CR1_TE |USART_CR1_RE | USART_CR1_UE; /* (2) */

	
  /* polling idle frame Transmission */
	while((USART8->ISR & USART_ISR_TC) != USART_ISR_TC)
  { 
    /* add time out here for a robust application */
  }
  	
	USART8->ICR |= USART_ICR_TCCF;		/* clear TC flag */
 
	USART8->CR1 |= USART_CR1_TCIE;		/* enable TC interrupt */
	USART8->CR1 |= USART_CR1_RXNEIE;	/* enable RXNE interrupt */
		
	// Configure_USART_7_8_IT
}



void Configure_USART_7_8_IT()
{
  /* Configure IT */
  /* (3) Set priority for USART7_IRQn */
  /* (4) Enable USART7_IRQn */
  NVIC_SetPriority(USART3_8_IRQn, 0); /* (3) */
  NVIC_EnableIRQ(USART3_8_IRQn); /* (4) */
}
