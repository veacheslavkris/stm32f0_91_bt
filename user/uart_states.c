/* Includes ------------------------------------------------------------------*/
#include "uart_states.h"

void SetUartModeFuncState(UartHandle* phUart, UartModeEnum uart_mode_enm, UartFuncStateEnum uart_funcstate_enm)
{
	phUart->uart_mode_enm = uart_mode_enm;
	phUart->uart_func_state_enm = uart_funcstate_enm;
}

void SetUartFuncState(UartHandle* phUart, UartFuncStateEnum uart_funcstate_enm)
{
	phUart->uart_func_state_enm = uart_funcstate_enm;
}


void ClearDataRx(UartHandle* phUart)
{
	clear_data_char_array(phUart->bufferRX.p_ary_data, phUart->bufferRX.ary_size);
	
	phUart->bufferRX.ix_ary = 0;
	phUart->bufferRX.data_size = 0;
}

void ClearDataTx(UartHandle* phUart)
{
	clear_data_char_array(phUart->bufferTX.p_ary_data, phUart->bufferTX.ary_size);
	
	phUart->bufferTX.ix_ary = 0;
	phUart->bufferTX.data_size = 0;
}

__INLINE void clear_data_char_array(uint8_t* p_ary, uint32_t size_ary)
{
	uint32_t ix_ary = 0;
	
	for(ix_ary = 0; ix_ary < size_ary; ix_ary++)
	{
		p_ary[ix_ary] = '*';
	}
}








