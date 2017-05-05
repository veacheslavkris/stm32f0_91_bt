 /* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"



/**
  * @brief  This function enables the peripheral clocks on GPIO port A,
  *         configures GPIO PA5 in output mode for the Green LED pin
  * @param  None
  * @retval None
  */
void  ConfigureGPIO(void)
{  
  /* (1) Enable the peripheral clock of GPIOA */
  /* (2) Select output mode (01) on GPIOA pin 5 */
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* (1) */  
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER5)) | (GPIO_MODER_MODER5_0); /* (2) */  
	
	// RS-485 : DE / RE
//	MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER4, GPIO_MODER_MODER4_0);
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER4)) | (GPIO_MODER_MODER4_0);   
		
//	CLEAR_BIT(GPIOA->OTYPER, GPIO_OTYPER_OT_4);
	GPIOA->OTYPER&=~GPIO_OTYPER_OT_4;
		
//	MODIFY_REG(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEEDR4, (~GPIO_OSPEEDR_OSPEEDR4));
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~(GPIO_OSPEEDR_OSPEEDR4));
	
//	MODIFY_REG(GPIOA->PUPDR, GPIO_PUPDR_PUPDR4, (~GPIO_PUPDR_PUPDR4));
	GPIOA->PUPDR = (GPIOA->PUPDR & ~(GPIO_PUPDR_PUPDR4));
}

/**
  * @brief  This function enables the peripheral clocks on GPIO port C (for USER BUTTON)
  *         configures the EXTI register and NVIC IRQ.
  *         PC13 is kept in the default configuration (input,no pull-up, no pull-down)
  *         SYSCFG_EXTICR4 is set at x010: PC[x] pin (SYSCFG_EXTICR4_EXTI13_PC) value to select Port C for EXTI13 
  * @param  None
  * @retval None
  */
void  ConfigureExternalIT(void)
{  
  /* (1) Enable the peripheral clock of GPIOC */ 
  /* (2) Select Port C for pin 13 external interrupt by writing SYSCFG_EXTICR4_EXTI13_PC in EXTI13 */
  /* (3) Configure the corresponding mask bit in the EXTI_IMR register */
  /* (4) Not Configure the Trigger Selection bits of the Interrupt line on rising edge*/
  /* (5) Configure the Trigger Selection bits of the Interrupt line on falling edge*/
  
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
	
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; /* (1) */
  SYSCFG->EXTICR[3] &= (uint16_t)~SYSCFG_EXTICR4_EXTI13; /* (2) */
	SYSCFG->EXTICR[3] |= (uint16_t)SYSCFG_EXTICR4_EXTI13_PC; /* (2) */
	
	EXTI->IMR = EXTI_IMR_MR13; /* (3) */ 
//  EXTI->RTSR = EXTI_RTSR_TR13; // EXTI_IMR_MR13; /* (4) */
  EXTI->FTSR = EXTI_FTSR_TR13; // EXTI_IMR_MR13; /* (5) */ Press button
  
  /* Configure NVIC for External Interrupt */
  /* (6) Enable Interrupt on EXTI4_15_IRQn (EXTI0_1) */
  /* (7) Set priority for EXTI4_15_IRQn (EXTI0_1) */
  NVIC_EnableIRQ(EXTI4_15_IRQn); /* (6) */
  NVIC_SetPriority(EXTI4_15_IRQn,0); /* (7) */
}

