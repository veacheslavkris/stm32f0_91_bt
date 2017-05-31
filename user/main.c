/**
  ******************************************************************************
  * @file    01_HWInterruptSelection/main.c 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    19-June-2015
  * @brief   This code example shows how to configure a GPIO to use it
  *          as external interrupt
  *
 ===============================================================================
                    #####       MCU Resources     #####
 ===============================================================================
   - PA0, PC9

 ===============================================================================
                    ##### How to use this example #####
 ===============================================================================
    - this file must be inserted in a project containing  the following files :
      o system_stm32f0xx.c, startup_stm32f072xb.s
      o stm32f0xx.h to get the register definitions
      o CMSIS files
    

 ===============================================================================
                    ##### How to test this example #####
 ===============================================================================
    - push the User button, this toggles the green led

  *    
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "stm32f0xx.h"
#include "main.h"

/** @addtogroup STM32F0_Snippets
  * @{
  */



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
	volatile uint32_t systick_count = 0;
	volatile uint32_t cycle_cnt = 0;
	volatile uint32_t max7219_cnt = 0;

	StructDecToBcd structDecToBcd;

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f072xb.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
	SetSysClock();

	SystemCoreClockUpdate();

	SysTick_Config(SystemCoreClock/1000);/* 1ms config with HSE 8MHz/system 48Mhz*/
	
	if(!IsRTC_Run()) 
	{
		RtcLse32768_Init();
		init_time();
	}
	
	
	
	init_converter();
	
	LedPA5_Init();
	
	Max7219_Init();
	Max7219_ClearAllDigits();
	

	
	delay_systick(1000);
	
	Max7219_ShowAtPositionNumber(0,0);
	Max7219_ShowAtPositionNumber(4,0);
	

	


	BtnPc13_Init();

	init_uarts();	
	
	

  while (1) /* Infinite loop */
  {

		if(IsMode_BT_Request())
		{
			if(IsFuncState_uartBt_PrepareSending())
			{
				uart_bt_request_prepare_sending();
				
				SetBt_Mode_FuncState(MODE_IDLE, FST_FREE, cycle_cnt);

				
					//		if(IS_BT_UART_STATE_ASKING_PREPARE)
					//		{
					//			clear_data_rx(&btUartHandle);
					//		
					//			set_bt_uart_state_address_sending();
					//			StartSendUartData_IT(&btUartHandle);
					//	
					//		}
			}
			else if(IsFuncState_uartBt_Sending())
			{
			}
			else if(IsFuncState_uartBt_TcntSent())
			{
			}
			else if(IsFuncState_uartBt_TC())
			{		
			}
			else if(IsFuncState_uartBt_PrepareReceiving())
			{
					//		else if(IS_BT_UART_STATE_LISTENING_PREPARE)
					//		{
					//			// prepare timeout of answer
					//			START_BT_TIMEOUT;
					//			set_bt_uart_state_answ_listening();
					//		}
			}
			else if(IsFuncState_uartBt_Receiving())
			{
					//		else if(IS_BT_UART_STATE_ANSW_LISTENING)
					//		{
					//			while(IS_BT_UART_STATE_ANSW_LISTENING)
					//			{
					//				// check for timeout
					//				if(IS_BT_TIMEOUT_DONE)
					//				{
					//					set_bt_uart_state_err_timeout();
					//				}
					//				
					//				// did we get as minimum 1 char ? 
					//				if(BT_RX_BUFF_IX_ARY > 0)
					//				{
					//					// as minimum 1 char we have got
					//					if(BT_RX_BUFF_IX_ARY == 1)
					//					{
					//						// we have got 1 char
					//						// using this char we select expecting answer size 
					//						select_bt_rx_buff_size();
					//						
					//						if( BT_RX_BUFF_DATA_SIZE == 0)
					//						{
					//							// not expected first answer char
					//							set_bt_uart_state_err_data();
					//						}
					//					} //if(dtAnswerStruct.data_size == 0)
					//					else if(BT_RX_BUFF_IX_ARY == BT_RX_BUFF_DATA_SIZE) //if(dtAnswerStruct.data_size > 0)
					//					{
					//						set_bt_uart_state_answ_done();
					//					} //else //if(dtAnswerStruct.data_size > 0)
					//				} //if(dtAnswerStruct.ix_ary > 0)
					//			} //while(STATE_DT_ANSW_GET == curState)
					//		}
			}
			else if(IsFuncState_uartBt_TcntReceived())
			{	
					//		else if(IS_BT_UART_STATE_ANSW_DONE)
					//		{
					//			set_bt_uart_state_downtime();
					//			set_pc_uart_state_ac_reporting_prepare();
					//		}
			}
			else if(IsFuncState_uartBt_ErrTimeout())
			{
					//		else if(IS_BT_UART_STATE_ERR_TIMEOUT)
					//		{
					//			LedBlockIndicating(100,100,10);
					//			set_bt_uart_state_downtime();
					//		}
			}
		}
		
		
		if(IsMode_DT_Request())
		{
			if(IsFuncState_uartPc_PrepareSending())
			{
					//		if(IS_PC_UART_STATE_DT_ASKING_PREPARE)
					//		{
					//			prepare_dt_asking_pc();
					//			set_pc_uart_state_dt_ask_sending();
					//			StartSendUartData_IT(&pcUartHandle);
					//		}
			}
			else if(IsFuncState_uartPc_Sending())
			{
			}
			else if(IsFuncState_uartPc_TcntSent())
			{
			}
			else if(IsFuncState_uartPc_TC())
			{	
					//		else if(IS_PC_UART_STATE_SENDING_DONE)
					//		{
					//			set_pc_uart_state_downtime();
					//		}				
			}
			else if(IsFuncState_uartPc_PrepareReceiving())
			{
					//		else if(IS_PC_UART_STATE_DT_LISTENING_PREPARE)
					//		{
					//			set_pc_uart_state_downtime();
					//		}
			}
			else if(IsFuncState_uartPc_Receiving())
			{
			}
			else if(IsFuncState_uartPc_TcntReceived())
			{	
			}
			else if(IsFuncState_uartPc_ErrTimeout())
			{
			
			}
		}
		else if(IsMode_AC_Report())
		{
			if(IsFuncState_uartPc_PrepareSending())
			{
					//		else if(IS_PC_UART_STATE_AC_REPORTING_PREPARE)
					//		{
					//			prepare_ac_report_for_pc();
					//			set_pc_uart_state_ac_report_sending();
					//			StartSendUartData_IT(&pcUartHandle);
					//		}
			}
			else if(IsFuncState_uartPc_Sending())
			{
			}
			else if(IsFuncState_uartPc_TcntSent())
			{
			}
			else if(IsFuncState_uartPc_TC())
			{		
			}
		}
		
		if((IsMode_UBt_Idle())&&(IsMode_UPc_Idle()))
		{
			LED_ON;
			
			if(systick_count == 0)
			{
				delay_systick(1000);
				structDecToBcd.dec = ++max7219_cnt;
				
				ConvertDecToBcd(&structDecToBcd);
				Max7219_DisplayBcdArray(LEFT_ZERO, structDecToBcd.ary_bcd);
				
			}
		
		}
		
		
		
















		
	
//		while((IS_PC_UART_STATE_DOWNTIME)&&(IS_BT_UART_STATE_DOWNTIME))
//		{
//				LED_TOGGLE;
//				delay_led_ms(1000);
//		}

		
		
  }
}

/******************************************************************************/
/*                                  GENERAL                                   */
/******************************************************************************/
void init_time(void)
{
	/* Date Time Structure from PC
		
	byte[] ary_date_time = new byte[11];
		
	ary_date_time[0] = (byte)'$';
	ary_date_time[1] = Hours;          // hours
	ary_date_time[2] = Minutes;           // minutes
	ary_date_time[3] = Seconds;           // seconds
	ary_date_time[4] = (byte)'w';   
	ary_date_time[5] = WeekDay;           // weekday
	ary_date_time[6] = (byte)'%';
	ary_date_time[7] = Day;           // Month
	ary_date_time[8] = Month;           // Day
	ary_date_time[9] = Year;           // Year
	ary_date_time[10] = (byte)'!';
		
	*/
	
	
	uint8_t ary_date_time[11];
	ary_date_time[0] = '$';
	ary_date_time[1] = 18;		// hours
	ary_date_time[2] = 30;		// minutes
	ary_date_time[3] = 00;		// seconds
	ary_date_time[4] = 'w';   
	ary_date_time[5] = 3;			// weekday
	ary_date_time[6] = '%';
	ary_date_time[7] = 31;		// Month
	ary_date_time[8] = 5;			// Day
	ary_date_time[9] = 17;		// Year
	ary_date_time[10] = '!';
	
	RtcSetDateTime(ary_date_time);
}



void init_converter()
{
	structDecToBcd.digits_count = 10;
}

/******************************************************************************/
/*                               SYS TICK TIMER                               */
/******************************************************************************/

void delay_systick(uint32_t ms)
{
	systick_count = ms;
	
	while(systick_count > 0) continue;
}

/******************************************************************************/
/*                             Init UART Handles                              */
/******************************************************************************/

void init_uarts()
{
	
	DebugUart_Init();
	
	Uart8_Init();
	Uart7_Init();
		
	HUartBt_Init();
	SetBt_Mode_FuncState(MODE_IDLE, FST_FREE, cycle_cnt);
		
	HUartPc_Init();
	SetPc_Mode_FuncState(MODE_IDLE, FST_FREE, cycle_cnt);
}


/******************************************************************************/
/*                               Date Time Set                                */
/******************************************************************************/



/******************************************************************************/
/*                        Begin Uart Transmision                              */
/******************************************************************************/
void StartSendUartData_IT(UartHandle* phUart)
{
	phUart->bufferTX.ix_ary = 0;
	
	phUart->pUart->TDR =  phUart->bufferTX.p_ary_data[phUart->bufferTX.ix_ary++];
	
	phUart->pUart->CR1 |= USART_CR1_TXEIE;		/* enable RXNE interrupt */
	
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void prepare_ac_report_for_pc(void)
{
	
	PrepareAcReportForPc(GetBtUartHandle());
	
}

void uart_bt_request_prepare_sending(void)
{ 
	
	structDecToBcd.dec = cycle_cnt;
	
	ConvertDecToBcd(&structDecToBcd);
	
	Max7219_DisplayBcdArray(LEFT_ZERO, structDecToBcd.ary_bcd);
//	Max7219_ShowAtPositionNumber(0, cycle_cnt);
	
	

}

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f072xb.s).                                               */
/******************************************************************************/

void SysTick_Handler(void)
{
	if(systick_count > 0)systick_count--;
}


void EXTI4_15_IRQHandler(void)
{
  if ((EXTI->PR & EXTI_PR_PR13) == EXTI_PR_PR13)  /* Check line 13 has triggered the IT */
  {
    EXTI->PR |= EXTI_PR_PR13; /* Clear the pending bit */

		
		cycle_cnt++;
		
		
		SetBt_Mode_FuncState(MODE_BT_REQUEST, FST_PREPARE_SENDING, cycle_cnt);
		
		led_ms_wait = 0;
		LED_TOGGLE;	
		

  }
  else /* Should never occur */
  {
  }
}

/******************************************************************************/
/*                       USART 7-8 Exceptions Handlers                        */
/******************************************************************************/
void ProcessUartIrq(UartHandle* pHUart)
{
	USART_TypeDef* pUart = pHUart->pUart;
	
	if(pUart->ISR & USART_ISR_TC)	// TRANSMIT COMPLETE STATE
	{
		pUart->ICR |= USART_ICR_TCCF;		
		SetUartFuncState(pHUart, FST_TRANSMIT_COMPLETE);
	}
	else if(pUart->ISR & USART_ISR_RXNE)	// RXNE STATE
	{
		UartReceivedChar* structReceivedChar = UartGetReceivedChar(pUart);
				
		if(pHUart->uart_func_state_enm == FST_RECEIVING) // IS RECEIVING STATE
		{
			pHUart->bufferRX.p_ary_data[pHUart->bufferRX.ix_ary++] = structReceivedChar->chartoreceive;
		}
		// else as state is not receiving ignore received data
	}
	else if(pUart->ISR & USART_ISR_TXE)	// TXE STATE
	{
		if(pHUart->uart_func_state_enm == FST_SENDING) // IS SENDING STATE
		{
			if(pHUart->bufferTX.ix_ary < pHUart->bufferTX.data_size)	// SENDING IS NOT COMPLETE
			{
				pUart->TDR = pHUart->bufferTX.p_ary_data[pHUart->bufferTX.ix_ary++];
			}
			else // TERMINAL COUNT IS BEING SENT, SENDING IS COMPLETE
			{
				pUart->CR1 &= ~USART_CR1_TXEIE;
				pHUart->uart_func_state_enm = FST_TRMNL_CNT_SENT;
			}
		}
	}

}

void USART3_8_IRQHandler(void)
{
	ProcessUartIrq(GetBtUartHandle());

	ProcessUartIrq(GetPcUartHandle());
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
