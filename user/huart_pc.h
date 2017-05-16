#ifndef HUART_PC_H
#define HUART_PC_H
#include "uart_states.h"

#define UART_PC USART8

void HUartPc_Init(void);

UartHandle* GetPcUartHandle(void);

uint32_t IsMode_DT_Request(void);

uint32_t IsMode_AC_Report(void);

uint32_t IsMode_UPc_Idle(void);

uint32_t IsFuncState_uartPc_PrepareSending(void);
uint32_t IsFuncState_uartPc_Sending(void);
uint32_t IsFuncState_uartPc_TcntSent(void);
uint32_t IsFuncState_uartPc_TC(void);
uint32_t IsFuncState_uartPc_PrepareReceiving(void);
uint32_t IsFuncState_uartPc_Receiving(void);
uint32_t IsFuncState_uartPc_TcntReceived(void);
uint32_t IsFuncState_uartPc_Free(void);
uint32_t IsFuncState_uartPc_ErrTimeout(void);

void SetPc_Mode_FuncState(UartMode* pUartMode, UartFuncState* pUartFuncState);

void PrepareAcReportForPc(UartHandle* pBtUartHandle);



#endif


