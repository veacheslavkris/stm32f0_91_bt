#ifndef HUART_BT_H
#define HUART_BT_H
#include "uart_states.h"

#define UART_BT USART7

#define SIZE_OF_BT_ADDRESS_DATA 26

void HUartBt_Init(void);

UartHandle* GetBtUartHandle(void);


//UartFuncStateEnum BtUartFuncStateEnum(void);
//UartModeEnum BtUartModeEnum(void);

uint32_t IsMode_BT_Request(void);

uint32_t IsMode_UBt_Idle(void);


uint32_t IsFuncState_uartBt_PrepareSending(void);
uint32_t IsFuncState_uartBt_Sending(void);
uint32_t IsFuncState_uartBt_TcntSent(void);
uint32_t IsFuncState_uartBt_TC(void);
uint32_t IsFuncState_uartBt_PrepareReceiving(void);
uint32_t IsFuncState_uartBt_Receiving(void);
uint32_t IsFuncState_uartBt_TcntReceived(void);
uint32_t IsFuncState_uartBt_Free(void);
uint32_t IsFuncState_uartBt_ErrTimeout(void);

void SetBt_Mode_FuncState(UartMode* pUartMode, UartFuncState* pUartFuncState);

uint32_t IsBtRxDataFull(void);
void SetBtRxDataSize(uint32_t size);






#endif


