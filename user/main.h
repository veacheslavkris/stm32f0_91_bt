#include "stm32f0xx.h"
//#include "stm32f091xc.h"

#include "stdint.h"
#include "sys_clock.h" 
#include "uart.h"
#include "uart8.h"
#include "uart7.h"
#include "rtc.h"
#include "maxim_7219.h"
#include "pc13btn.h"
#include "pa5_led.h"


//#include "debug.h"


#ifdef UDEBUG
	DbgCheckPointsPath stc_dbg_path = {0, ARY_CPS_PATH_COUNT};
	uint32_t cycle=0;
#endif

//// ------- Date Time Request
const uint8_t DT_REQ_LENGTH = 7;
uint8_t ary_dt_req[DT_REQ_LENGTH]={'<','?','t','i','m','e','!'};

const uint8_t DT_ANSW_LENGTH = 11;
uint8_t ary_dt_answer[DT_ANSW_LENGTH];		
		


#define SIZE_OF_HUART_BUFFER_ARY 50
#define SIZE_OF_BT_ADDRESS_DATA 26


/*------------- EXTERN Functions -------------*/
extern void ConfigureGPIO(void);
extern void ConfigureExternalIT(void);


uint8_t ary_bt_tx_data_1[SIZE_OF_BT_ADDRESS_DATA] = {"AT+RNAME? 0000,11,111281\r\n"}; 
uint8_t ary_bt_tx_data_2[SIZE_OF_BT_ADDRESS_DATA] = {"AT+RNAME? 6c8f,b5,7b9846\r\n"};


uint8_t ary_bt_rx_data[SIZE_OF_HUART_BUFFER_ARY]; 

uint8_t ary_dt_tx_data[SIZE_OF_HUART_BUFFER_ARY]; 
uint8_t ary_dt_rx_data[SIZE_OF_HUART_BUFFER_ARY]; 

UartHandle btUartHandle;
UartHandle pcUartHandle;

void clear_data_rx(UartHandle* phUart);
void clear_data_char_array(uint8_t* p_ary, uint32_t size_ary);

/*------------- SysTick -------------*/
volatile uint32_t systick_ms_count = 0;
volatile uint32_t bt_ms_wait = 0;
volatile uint32_t led_ms_wait = 0;


/*------------- Set Uart Handler State Functions  -------------*/


__INLINE void _set_uart_mode_funcstate(UartHandle* phUart, UartMode* p_mode, UartFuncState* p_funcstate)
{
	phUart->pUartMode = p_mode;
	phUart->pUartFuncState = p_funcstate;
}

__INLINE void set_uart_funcstate(UartHandle* phUart, UartFuncState* p_funcstate)
{
	phUart->pUartFuncState = p_funcstate;
}

/******************************************************************************/
/*                        ProcessUartIrq CHECK STATE                          */
/******************************************************************************/

__INLINE uint32_t IsSetFlag_TC_uart(USART_TypeDef* pUART)
{
//	return ((pUART->ISR & USART_ISR_TC) == USART_ISR_TC);
	return (pUART->ISR & USART_ISR_TC);
}

__INLINE uint32_t IsSetFlag_RXNE_uart(USART_TypeDef* pUART)
{
//	return ((pUART->ISR & USART_ISR_RXNE) == USART_ISR_RXNE );
	return (pUART->ISR & USART_ISR_RXNE);
}

__INLINE uint32_t IsSetFlag_TXE_uart(USART_TypeDef* pUART)
{
//	return ((pUART->ISR & USART_ISR_TXE) == USART_ISR_TXE);
	return (pUART->ISR & USART_ISR_TXE);
}

__INLINE uint32_t IsFuncState_RECEIVING_of(UartHandle* pHUart)
{
	return (pHUart->pUartFuncState->enm_funcstate == FST_RECEIVING);
}

__INLINE uint32_t IsFuncState_SENDING_of(UartHandle* pHUart)
{
	return (pHUart->pUartFuncState->enm_funcstate == FST_SENDING);
}


/******************************************************************************/
/*                   MODES AND SUBSTATES OF UARTS : INIT                      */
/******************************************************************************/


UartMode UartMode_BT_Request =	{MODE_BT_REQUEST,	"MODE_BT_REQUEST."};
UartMode UartMode_DT_Request =	{MODE_DT_REQUEST,	"MODE_DT_REQUEST."};
UartMode UartMode_AC_Report =		{MODE_AC_REPORT,	"MODE_AC_REPORT.."};
UartMode UartMode_Idle =				{MODE_IDLE,				"MODE_IDLE......."};
UartMode UartMode_Error =				{MODE_ERROR,			"MODE_ERROR......"};


UartFuncState UartFState_PrepareSending =		{FST_PREPARE_SENDING,		"FST_PREPARE_SENDING....."};
UartFuncState UartFState_Sending =					{FST_SENDING,						"FST_SENDING............."};
UartFuncState UartFState_TcSending =				{FST_TCNT_SENT,					"FST_TCNT_SENT..........."};
UartFuncState UartFState_TC =								{FST_TC,								"FST_TC.................."};
UartFuncState UartFState_PrepareReceiving =	{FST_PREPARE_RECEIVING,	"FST_PREPARE_RECEIVING..."};
UartFuncState UartFState_Receiving =				{FST_RECEIVING,					"FST_RECEIVING..........."};
UartFuncState UartFState_TcReceiving =			{FST_TCNT_RECEIVED,			"FST_TCNT_RECEIVED......."};
UartFuncState UartFState_Free =							{FST_FREE,							"FST_FREE................"};
UartFuncState UartFState_ErrFg =						{FST_ERR_FG,						"FST_ERR_FG.............."};
UartFuncState UartFState_ErrData =					{FST_ERR_DATA,					"FST_ERR_DATA............"};
UartFuncState UartFState_ErrTimeout =				{FST_ERR_TIMEOUT,				"FST_ERR_TIMEOUT........."};

/******************************************************************************/
/*                 MODES AND SUBSTATES OF UARTS : GETTING                     */
/******************************************************************************/


__INLINE UartModeEnum BtUartModeEnum(void)
{
	return btUartHandle.pUartMode->enm_mode;
}

__INLINE UartFuncStateEnum BtUartFuncStateEnum(void)
{
	return btUartHandle.pUartFuncState->enm_funcstate;
}

__INLINE UartModeEnum PcUartModeEnum(void)
{
	return pcUartHandle.pUartMode->enm_mode;
}

__INLINE UartFuncStateEnum PcUartFuncStateEnum(void)
{
	return pcUartHandle.pUartFuncState->enm_funcstate;
}



/******************************************************************************/
/*                          MODES OF UARTS : CHECK                            */
/******************************************************************************/


__INLINE uint32_t IsMode_BT_Request(void)
{
	return (BtUartModeEnum() == MODE_BT_REQUEST);
}

__INLINE uint32_t IsMode_DT_Request(void)
{
	return (PcUartModeEnum() == MODE_DT_REQUEST);
}


__INLINE uint32_t IsMode_AC_Report(void)
{
	return (PcUartModeEnum() == MODE_AC_REPORT);
}


__INLINE uint32_t IsMode_UBt_Idle(void)
{
	return (BtUartModeEnum() == MODE_IDLE);
}

__INLINE uint32_t IsMode_UPc_Idle(void)
{
	return (PcUartModeEnum() == MODE_IDLE);
}

/******************************************************************************/
/*                   FUNCTION STATES OF BT UARTS : CHECK                      */
/******************************************************************************/

__INLINE uint32_t IsFuncState_uartBt_PrepareSending()
{
		return (BtUartFuncStateEnum() == FST_PREPARE_SENDING);
}

__INLINE uint32_t IsFuncState_uartBt_Sending()
{
		return (BtUartFuncStateEnum() == FST_SENDING);
}

__INLINE uint32_t IsFuncState_uartBt_TcntSent()
{
		return (BtUartFuncStateEnum() == FST_TCNT_SENT);
}

__INLINE uint32_t IsFuncState_uartBt_TC()
{
		return (BtUartFuncStateEnum() == FST_TC);
}

__INLINE uint32_t IsFuncState_uartBt_PrepareReceiving()
{
		return (BtUartFuncStateEnum() == FST_PREPARE_RECEIVING);
}

__INLINE uint32_t IsFuncState_uartBt_Receiving()
{
		return (BtUartFuncStateEnum() == FST_RECEIVING);
}

__INLINE uint32_t IsFuncState_uartBt_TcntReceived()
{
		return (BtUartFuncStateEnum() == FST_TCNT_RECEIVED);
}

__INLINE uint32_t IsFuncState_uartBt_Free()
{
		return (BtUartFuncStateEnum() == FST_FREE);
}

__INLINE uint32_t IsFuncState_uartBt_ErrTimeout()
{
		return (BtUartFuncStateEnum() == FST_ERR_TIMEOUT);
}

/******************************************************************************/
/*                   FUNCTION STATES OF PC UARTS : CHECK                      */
/******************************************************************************/
__INLINE uint32_t IsFuncState_uartPc_PrepareSending()
{
		return (PcUartFuncStateEnum() == FST_PREPARE_SENDING);
}

__INLINE uint32_t IsFuncState_uartPc_Sending()
{
		return (PcUartFuncStateEnum() == FST_SENDING);
}

__INLINE uint32_t IsFuncState_uartPc_TcntSent()
{
		return (PcUartFuncStateEnum() == FST_TCNT_SENT);
}

__INLINE uint32_t IsFuncState_uartPc_TC()
{
		return (PcUartFuncStateEnum() == FST_TC);
}

__INLINE uint32_t IsFuncState_uartPc_PrepareReceiving()
{
		return (PcUartFuncStateEnum() == FST_PREPARE_RECEIVING);
}

__INLINE uint32_t IsFuncState_uartPc_Receiving()
{
		return (PcUartFuncStateEnum() == FST_RECEIVING);
}

__INLINE uint32_t IsFuncState_uartPc_TcntReceived()
{
		return (PcUartFuncStateEnum() == FST_TCNT_RECEIVED);
}

__INLINE uint32_t IsFuncState_uartPc_Free()
{
		return (PcUartFuncStateEnum() == FST_FREE);
}

__INLINE uint32_t IsFuncState_uartPc_ErrTimeout()
{
		return (PcUartFuncStateEnum() == FST_ERR_TIMEOUT);
}




/******************************************************************************/
/*                 FUNCTION STATES OF BT UARTS : SETTING                      */
/******************************************************************************/

__INLINE void _set_funcstate_of_bt_request_mode(UartFuncState* pUartFuncState)
{
	_set_uart_mode_funcstate(&btUartHandle, &UartMode_BT_Request, pUartFuncState);
}

__INLINE void set_mode_bt_request_prepare_sending(void) 
{	
	_set_funcstate_of_bt_request_mode(&UartFState_PrepareSending);
}

__INLINE void set_mode_bt_request_sending(void) 
{	
	_set_funcstate_of_bt_request_mode(&UartFState_Sending);
}

__INLINE void set_mode_bt_request_tc_sent(void) 
{
	_set_funcstate_of_bt_request_mode(&UartFState_TcSending);
}

__INLINE void set_mode_bt_request_tc(void) 
{	
	_set_funcstate_of_bt_request_mode(&UartFState_TC);
}

__INLINE void set_mode_bt_request_prepare_receiving(void) 
{	
	_set_funcstate_of_bt_request_mode(&UartFState_PrepareReceiving);
}

__INLINE void set_mode_bt_request_receiving(void) 
{	
	_set_funcstate_of_bt_request_mode(&UartFState_Receiving);
}

__INLINE void set_mode_bt_request_tc_receiving(void) 
{
	_set_funcstate_of_bt_request_mode(&UartFState_TcReceiving);
}

__INLINE void set_mode_bt_request_sst_free(void) 
{	
	_set_funcstate_of_bt_request_mode(&UartFState_Free);
}

/******************************************************************************/
/*                 FUNCTION STATES OF PC UARTS : SETTING                      */
/******************************************************************************/

/*------------- Set DT Report Functions  -------------*/

__INLINE void _set_funcstate_of_dt_request_mode(UartFuncState* pUartFuncState)
{
	_set_uart_mode_funcstate(&pcUartHandle, &UartMode_DT_Request, pUartFuncState);
}

__INLINE void set_mode_dt_request_prepare_sending(void) 
{	
	_set_funcstate_of_dt_request_mode(&UartFState_PrepareSending);
}

__INLINE void set_mode_dt_request_sending(void) 
{	
	_set_funcstate_of_dt_request_mode(&UartFState_Sending);
}

__INLINE void set_mode_dt_request_tc_sent(void) 
{
	_set_funcstate_of_dt_request_mode(&UartFState_TcSending);
}

__INLINE void set_mode_dt_request_tc(void) 
{	
	_set_funcstate_of_dt_request_mode(&UartFState_TC);
}

__INLINE void set_mode_dt_request_prepare_receiving(void) 
{	
	_set_funcstate_of_dt_request_mode(&UartFState_PrepareReceiving);
}

__INLINE void set_mode_dt_request_receiving(void) 
{	
	_set_funcstate_of_dt_request_mode(&UartFState_Receiving);
}

__INLINE void set_mode_dt_request_tc_receiving(void) 
{
	_set_funcstate_of_dt_request_mode(&UartFState_TcReceiving);
}

__INLINE void set_mode_dt_request_sst_free(void) 
{	
	_set_funcstate_of_dt_request_mode(&UartFState_Free);
}
/*------------- Set AC Report Functions  -------------*/

__INLINE void _set_funcstate_of_ac_report_mode(UartFuncState* pUartFuncState)
{
	_set_uart_mode_funcstate(&pcUartHandle, &UartMode_AC_Report, pUartFuncState);
}

__INLINE void set_mode_ac_report_prepare_sending(void) 
{	
	_set_funcstate_of_ac_report_mode(&UartFState_PrepareSending);
}

__INLINE void set_mode_ac_report_sending(void) 
{	
	_set_funcstate_of_ac_report_mode(&UartFState_Sending);
}

__INLINE void set_mode_ac_report_tc_sending(void) 
{
	_set_funcstate_of_ac_report_mode(&UartFState_TcSending);
}

__INLINE void set_mode_ac_report_tc(void) 
{	
	_set_funcstate_of_ac_report_mode(&UartFState_TC);
}

__INLINE void set_mode_ac_report_sst_free(void) 
{	
	_set_funcstate_of_ac_report_mode(&UartFState_Free);
}

/*------------- Set Idle Functions  -------------*/

__INLINE void set_mode_ubt_idle(void) 
{	
	_set_uart_mode_funcstate(&btUartHandle, &UartMode_Idle, &UartFState_Free);
}

__INLINE void set_mode_upc_idle(void) 
{	
	_set_uart_mode_funcstate(&pcUartHandle, &UartMode_Idle, &UartFState_Free);
}

/*------------- Set Error Functions  -------------*/

__INLINE void set_mode_ubt_timeout_err(void) 
{	
	_set_uart_mode_funcstate(&btUartHandle, &UartMode_Error, &UartFState_ErrTimeout);
}

__INLINE void set_mode_upc_timeout_err(void) 
{	
	_set_uart_mode_funcstate(&pcUartHandle, &UartMode_Error, &UartFState_ErrTimeout);
}

/******************************************************************************/
/*                                  FUNCTIONS                                 */
/******************************************************************************/

__INLINE uint32_t IsBtTimeoutDone()
{
	return (bt_ms_wait == 0);
}

__INLINE void StartBtTimeout(uint32_t timeout_ms)
{
	bt_ms_wait = timeout_ms;
}

__INLINE uint32_t UBtRxBuff_ix_ary(void)
{
	return btUartHandle.bufferRX.ix_ary;
}

__INLINE uint32_t UBtRxBuffDataSize(void)
{
	return btUartHandle.bufferRX.data_size;
}

__INLINE uint8_t get_bt_rx_buff_char_at_ix(uint32_t ix) {	return btUartHandle.bufferRX.p_ary_data[ix]; }

__INLINE void set_bt_rx_buff_size(uint32_t size){ btUartHandle.bufferRX.data_size = size;}

__INLINE uint32_t is_bt_rx_data_full()
{ 
	return ((UBtRxBuffDataSize() > 0) && (UBtRxBuff_ix_ary() == UBtRxBuffDataSize()));
}

// select and set correct size of receive_buffer
void select_bt_rx_buff_size(void)
{
	// we have got 1 char
	// using this char we select expecting answer size 
	uint8_t first_char = 	get_bt_rx_buff_char_at_ix(0);	
	uint32_t rx_buff_size = 0;
	
	if(first_char =='+')
	{
		rx_buff_size = 7;
	}
	else if(first_char =='F')
	{
		rx_buff_size = 4;
	}
	else if(first_char =='E')
	{
		rx_buff_size = 9;
	}
	
	set_bt_rx_buff_size(rx_buff_size);

}








/*-------------  Functions  -------------*/
void prepare_ac_report_for_pc(void);
void prepare_dt_asking_pc(void);


void init_uart_handles(void);
void clear_data_char_array(uint8_t* p_ary, uint32_t size_ary);
void clear_data_rx(UartHandle* phUart);
void clear_data_tx(UartHandle* phUart);

void delay_systick(uint32_t ms);

/*------------- Begin Uart Transmision ------------*/
void StartSendUartData_IT(UartHandle* phUart);

uint8_t bt_dev_number = 0;	

volatile uint32_t bp;

void ProcessUartIrq(UartHandle* pHUart)
{
	USART_TypeDef* pUart = pHUart->pUart;
	
	if(IsSetFlag_TC_uart(pUart))
	{
		pUart->ICR |= USART_ICR_TCCF;		
		
		set_uart_funcstate(pHUart, &UartFState_TC);
	}
	else if(IsSetFlag_RXNE_uart(pUart))
	{
		UartReceivedChar* structReceivedChar = UartGetReceivedChar(pUart);
				
		if(IsFuncState_RECEIVING_of(pHUart))
		{
			pHUart->bufferRX.p_ary_data[pHUart->bufferRX.ix_ary++] = structReceivedChar->chartoreceive;
		}
	}
	else if(IsSetFlag_TXE_uart(pUart))
	{
		if(IsFuncState_SENDING_of(pHUart))
		{
			if(pHUart->bufferTX.ix_ary < pHUart->bufferTX.data_size)	
			{
				pUart->TDR = pHUart->bufferTX.p_ary_data[pHUart->bufferTX.ix_ary++];
			}
			else
			{
				pUart->CR1 &= ~USART_CR1_TXEIE;
				set_uart_funcstate(pHUart, &UartFState_TcSending);
			}
		}
	}

}

