/* Includes ------------------------------------------------------------------*/
#include "uart_states.h"


void _set_uart_mode_funcstate(UartHandle* phUart, UartMode* p_mode, UartFuncState* p_funcstate)
{
	phUart->pUartMode = p_mode;
	phUart->pUartFuncState = p_funcstate;
}

void set_uart_funcstate(UartHandle* phUart, UartFuncState* p_funcstate)
{
	phUart->pUartFuncState = p_funcstate;
}


void clear_data_rx(UartHandle* phUart)
{
	clear_data_char_array(phUart->bufferRX.p_ary_data, phUart->bufferRX.ary_size);
	
	phUart->bufferRX.ix_ary = 0;
	phUart->bufferRX.data_size = 0;
}

void clear_data_tx(UartHandle* phUart)
{
	clear_data_char_array(phUart->bufferTX.p_ary_data, phUart->bufferTX.ary_size);
	

	phUart->bufferTX.ix_ary = 0;
	phUart->bufferTX.data_size = 0;
}

void clear_data_char_array(uint8_t* p_ary, uint32_t size_ary)
{
	uint32_t ix_ary = 0;
	
	for(ix_ary = 0; ix_ary < size_ary; ix_ary++)
	{
		p_ary[ix_ary] = '*';
	}
}








