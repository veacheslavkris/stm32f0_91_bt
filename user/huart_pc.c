#include "huart_pc.h"
#include "uart_states.h"


	#define PC_UART_MODE_ENUM					(pcUartHandle.pUartMode->enm_mode)
	#define PC_UART_FUNC_STATE_ENUM		(pcUartHandle.pUartFuncState->enm_funcstate)


	UartHandle pcUartHandle;

	uint8_t ary_dt_tx_data[SIZE_OF_HUART_BUFFER_ARY]; 
	uint8_t ary_dt_rx_data[SIZE_OF_HUART_BUFFER_ARY]; 

void HUartPc_Init()
{
	pcUartHandle.pUart = UART_PC;
	
	
	pcUartHandle.bufferTX.ary_size = SIZE_OF_HUART_BUFFER_ARY;
	pcUartHandle.bufferTX.p_ary_data = ary_dt_tx_data;
	
	pcUartHandle.bufferRX.ary_size = SIZE_OF_HUART_BUFFER_ARY;
	pcUartHandle.bufferRX.p_ary_data = ary_dt_rx_data;
	
	pcUartHandle.ary_uart_name[0] = 'P';
	pcUartHandle.ary_uart_name[1] = 'C';
	pcUartHandle.ary_uart_name[2] = ' ';

	ClearDataRx(&pcUartHandle);
}

UartHandle* GetPcUartHandle(void)
{
	return &pcUartHandle;
}

/******************************************************************************/
/*                 MODES AND SUBSTATES OF UARTS : GETTING                     */
/******************************************************************************/


/******************************************************************************/
/*                          MODES OF UARTS : CHECK                            */
/******************************************************************************/

uint32_t IsMode_DT_Request(void)
{
	return (PC_UART_MODE_ENUM == MODE_DT_REQUEST);
}

uint32_t IsMode_AC_Report(void)
{
	return (PC_UART_MODE_ENUM == MODE_AC_REPORT);
}

uint32_t IsMode_UPc_Idle(void)
{
	return (PC_UART_MODE_ENUM == MODE_IDLE);
}

/******************************************************************************/
/*                   FUNCTION STATES OF PC UARTS : CHECK                      */
/******************************************************************************/
uint32_t IsFuncState_uartPc_PrepareSending()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_PREPARE_SENDING);
}

uint32_t IsFuncState_uartPc_Sending()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_SENDING);
}

uint32_t IsFuncState_uartPc_TcntSent()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_TCNT_SENT);
}

uint32_t IsFuncState_uartPc_TC()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_TC);
}

uint32_t IsFuncState_uartPc_PrepareReceiving()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_PREPARE_RECEIVING);
}

uint32_t IsFuncState_uartPc_Receiving()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_RECEIVING);
}

uint32_t IsFuncState_uartPc_TcntReceived()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_TCNT_RECEIVED);
}

uint32_t IsFuncState_uartPc_Free()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_FREE);
}

uint32_t IsFuncState_uartPc_ErrTimeout()
{
		return (PC_UART_FUNC_STATE_ENUM == FST_ERR_TIMEOUT);
}

/******************************************************************************/
/*                 FUNCTION STATES OF PC UARTS : SETTING                      */
/******************************************************************************/

void SetPc_Mode_FuncState(UartMode* pUartMode, UartFuncState* pUartFuncState)
{
	SetUartModeFuncState(&pcUartHandle, pUartMode, pUartFuncState);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void PrepareAcReportForPc(UartHandle* pBtUartHandle)
{
	
	uint32_t ix = 0;
	uint32_t bt_rx_data_size = pBtUartHandle->bufferRX.data_size;

	
	ClearDataTx(&pcUartHandle);
	
	for(ix = 0; ix < bt_rx_data_size; ix++)
	{
		pcUartHandle.bufferTX.p_ary_data[ix] = pBtUartHandle->bufferRX.p_ary_data[ix];
	}
	
	pcUartHandle.bufferTX.p_ary_data[ix++]=0x0D;
	
	pcUartHandle.bufferTX.data_size = bt_rx_data_size + 1;
	
}


