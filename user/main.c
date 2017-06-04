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
	volatile uint8_t an_char;

	StructDecToBcd structDecToBcd;

	UartHandle* phPcUart = 0;
	UartHandle* phBtUart = 0;

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
				StartSendUartData_IT(phBtUart);
			}
			else if(IsFuncState_uartBt_Sending())
			{
			}
			else if(IsFuncState_uartBt_TcntSent())
			{
			}
			else if(IsFuncState_uartBt_TC())
			{		
				SetBt_FuncState(FST_PREPARE_RECEIVING, cycle_cnt);
			}
			else if(IsFuncState_uartBt_PrepareReceiving())
			{
				// prepare timeout of answer
				START_BT_TIMEOUT;
				SetBt_FuncState(FST_RECEIVING, cycle_cnt);

			}
			else if(IsFuncState_uartBt_Receiving())
			{
					
					while((IsMode_BT_Request())&&(IsFuncState_uartBt_Receiving()))
					{
						// check for timeout
						if(IS_BT_TIMEOUT_DONE)
						{
							SetBt_FuncState(FST_ERR_TIMEOUT, cycle_cnt);
						}
						
						// did we get as minimum 1 char ? 
						if(phBtUart->bufferRX.ix_ary > 0)
						{
							// as minimum 1 char we have got
							if(phBtUart->bufferRX.ix_ary == 1)
							{
								// we have got 1 char
								// using this char we select expecting answer size 
								if(SetBtRxDataSize() == 0)
								{
									// not expected first answer char
									SetBt_FuncState(FST_ERR_DATA, cycle_cnt);
								}
							}
							else if(IsBtRxDataFull()) 
							{
								SetBt_FuncState(FST_TRMNL_CNT_RECEIVED, cycle_cnt);

							}
							
						} 
					
					}// while MODE_BT_REQUEST && FST_RECEIVING
					
					
			}
			else if(IsFuncState_uartBt_TcntReceived())
			{	
				SetBt_Mode_FuncState(MODE_IDLE, FST_FREE, cycle_cnt);

				SetPc_Mode_FuncState(MODE_AC_REPORT, FST_PREPARE_SENDING, cycle_cnt);
			}
			else if(IsFuncState_uartBt_ErrTimeout())
			{
				SetBt_Mode_FuncState(MODE_IDLE, FST_FREE, cycle_cnt);
				show_err_on_display_0();
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
				DebugUartSetCheckPoint(GetPcUartHandle(), cycle_cnt);
			}
			else if(IsFuncState_uartPc_TC())
			{	
					//		else if(IS_PC_UART_STATE_SENDING_DONE)
					//		{
					//			set_pc_uart_state_downtime();
					//		}		

				DebugUartSetCheckPoint(GetPcUartHandle(), cycle_cnt);

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
				prepare_ac_report_for_pc();
				
				StartSendUartData_IT(phPcUart);

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
				SetPc_Mode_FuncState(MODE_IDLE, FST_FREE, cycle_cnt);
			}
		}
		
		if((IsMode_UBt_Idle())&&(IsMode_UPc_Idle()))
		{
			
			
//			if(systick_count == 0)
//			{
//				delay_systick(1000);
//				structDecToBcd.dec = ++max7219_cnt;
//				
//				ConvertDecToBcd(&structDecToBcd);
//				Max7219_DisplayBcdArray(structDecToBcd.ary_bcd);
//				
//			}
			
			
		
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
	
	phBtUart = GetBtUartHandle();
	phPcUart = GetPcUartHandle();
	
}


/******************************************************************************/
/*                               Date Time Set                                */
/******************************************************************************/



/******************************************************************************/
/*                        Begin Uart Transmision                              */
/******************************************************************************/
void StartSendUartData_IT(UartHandle* phUart)
{
	phUart->uart_func_state_enm = FST_SENDING;
	DebugUartSetCheckPoint(phUart, cycle_cnt);
	
	
	phUart->bufferTX.ix_ary = 0;
	
	phUart->pUart->TDR =  phUart->bufferTX.p_ary_data[phUart->bufferTX.ix_ary++];
	
	phUart->pUart->CR1 |= USART_CR1_TXEIE;		/* enable TXE interrupt */
	
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void prepare_ac_report_for_pc(void)
{
	
	PrepareAcReportForPc(phBtUart);
	
}

void uart_bt_request_prepare_sending(void)
{ 
	
	
	structDecToBcd.dec = cycle_cnt;
	
	ConvertDecToBcd(&structDecToBcd);
	
	Max7219_DisplayBcdArray(structDecToBcd.ary_bcd);
	
	ClearDataRx(phBtUart);
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
	if(bt_ms_wait > 0)bt_ms_wait--;
}


void EXTI4_15_IRQHandler(void)
{
  if ((EXTI->PR & EXTI_PR_PR13) == EXTI_PR_PR13)  /* Check line 13 has triggered the IT */
  {
    EXTI->PR |= EXTI_PR_PR13; /* Clear the pending bit */
	
		cycle_cnt++;
		
		SetBt_Mode_FuncState(MODE_BT_REQUEST, FST_PREPARE_SENDING, cycle_cnt);
		
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
		pHUart->uart_func_state_enm = FST_TRANSMIT_COMPLETE;
		DebugUartSetCheckPoint(pHUart, cycle_cnt);

	}
	else if(pUart->ISR & USART_ISR_RXNE)	// RXNE STATE
	{
		if(pHUart->uart_func_state_enm == FST_RECEIVING) // IS RECEIVING STATE
		{
			UartReceivedChar* structReceivedChar = UartGetReceivedChar(pUart);
			pHUart->bufferRX.p_ary_data[pHUart->bufferRX.ix_ary++] = structReceivedChar->chartoreceive;
		}
		else
		{
			an_char = (uint8_t)(pUart->RDR);
		}
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
				DebugUartSetCheckPoint(pHUart, cycle_cnt);
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
