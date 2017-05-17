#include "huart_bt.h"

	#define BT_UART_MODE_ENUM					(btUartHandle.pUartMode->enm_mode)
	#define BT_UART_FUNC_STATE_ENUM		(btUartHandle.pUartFuncState->enm_funcstate)


	UartHandle btUartHandle;

	uint8_t ary_bt_tx_data_1[SIZE_OF_BT_ADDRESS_DATA] = {"AT+RNAME? 0000,11,111281\r\n"}; 
	uint8_t ary_bt_tx_data_2[SIZE_OF_BT_ADDRESS_DATA] = {"AT+RNAME? 6c8f,b5,7b9846\r\n"};

	uint8_t ary_bt_rx_data[SIZE_OF_HUART_BUFFER_ARY]; 



	
void HUartBt_Init()
{
	btUartHandle.pUart = UART_BT;

	btUartHandle.bufferTX.ary_size = SIZE_OF_BT_ADDRESS_DATA;
	btUartHandle.bufferTX.p_ary_data = ary_bt_tx_data_1;
	btUartHandle.bufferTX.data_size = SIZE_OF_BT_ADDRESS_DATA;
	
	btUartHandle.bufferRX.ary_size = SIZE_OF_HUART_BUFFER_ARY;
	btUartHandle.bufferRX.p_ary_data = ary_bt_rx_data;
	
	btUartHandle.ary_uart_name[0] = 'B';
	btUartHandle.ary_uart_name[1] = 'T';
	btUartHandle.ary_uart_name[2] = ' ';
	
	ClearDataRx(&btUartHandle);
}
//

UartHandle* GetBtUartHandle()
{
	return &btUartHandle; 
}
//

/******************************************************************************/
/*                 MODES AND SUBSTATES OF UARTS : GETTING                     */
/******************************************************************************/



/******************************************************************************/
/*                          MODES OF UARTS : CHECK                            */
/******************************************************************************/

uint32_t IsMode_BT_Request(void)
{
	return (BT_UART_MODE_ENUM == MODE_BT_REQUEST);
}

uint32_t IsMode_UBt_Idle(void)
{
	return (BT_UART_MODE_ENUM == MODE_IDLE);
}

/******************************************************************************/
/*                   FUNCTION STATES OF BT UARTS : CHECK                      */
/******************************************************************************/

uint32_t IsFuncState_uartBt_PrepareSending()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_PREPARE_SENDING);
}

uint32_t IsFuncState_uartBt_Sending()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_SENDING);
}

uint32_t IsFuncState_uartBt_TcntSent()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_TCNT_SENT);
}

uint32_t IsFuncState_uartBt_TC()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_TC);
}

uint32_t IsFuncState_uartBt_PrepareReceiving()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_PREPARE_RECEIVING);
}

uint32_t IsFuncState_uartBt_Receiving()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_RECEIVING);
}

uint32_t IsFuncState_uartBt_TcntReceived()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_TCNT_RECEIVED);
}

uint32_t IsFuncState_uartBt_Free()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_FREE);
}

uint32_t IsFuncState_uartBt_ErrTimeout()
{
	return (BT_UART_FUNC_STATE_ENUM == FST_ERR_TIMEOUT);
}

/******************************************************************************/
/*                 FUNCTION STATES OF BT UARTS : SETTING                      */
/******************************************************************************/

void SetBt_Mode_FuncState(UartMode* pUartMode, UartFuncState* pUartFuncState)
{
	SetUartModeFuncState(&btUartHandle, pUartMode, pUartFuncState);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

uint32_t IsBtRxDataFull()
{ 
//	return ((UBtRxBuffDataSize() > 0) && (UBtRxBuff_ix_ary() == UBtRxBuffDataSize()));
	
	return ((btUartHandle.bufferRX.data_size > 0) && (btUartHandle.bufferRX.ix_ary == btUartHandle.bufferRX.data_size));
}


// select and set correct size of receive_buffer
void SelectBtRxDataSize(void)
{
	// we have got 1 char
	// using this char we select expecting answer size 
	uint8_t first_char = 	btUartHandle.bufferRX.p_ary_data[0];	
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
	
	btUartHandle.bufferRX.data_size = rx_buff_size;
}
























