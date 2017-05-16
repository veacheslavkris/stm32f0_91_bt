#include "stm32f0xx.h"
//#include "stm32f091xc.h"

#include "stdint.h"
#include "sys_clock.h" 
#include "uart_states.h"
#include "uart8.h"
#include "uart7.h"
#include "rtc.h"
#include "maxim_7219.h"
#include "pc13btn.h"
#include "pa5_led.h"
#include "huart_bt.h"
#include "huart_pc.h"



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
		
/*------------- SysTick -------------*/
volatile uint32_t bt_ms_wait = 0;
volatile uint32_t led_ms_wait = 0;

/******************************************************************************/
/*                        ProcessUartIrq CHECK STATE                          */
/******************************************************************************/

__INLINE uint32_t IsSetFlag_TC_uart(USART_TypeDef* pUART)
{
	return (pUART->ISR & USART_ISR_TC);
}

__INLINE uint32_t IsSetFlag_RXNE_uart(USART_TypeDef* pUART)
{
	return (pUART->ISR & USART_ISR_RXNE);
}

__INLINE uint32_t IsSetFlag_TXE_uart(USART_TypeDef* pUART)
{
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

/*-------------  Functions  -------------*/
void prepare_ac_report_for_pc(void);
void prepare_dt_asking_pc(void);

void init_uart_handles(void);

void delay_systick(uint32_t ms);


/*------------- Begin Uart Transmision ------------*/
void StartSendUartData_IT(UartHandle* phUart);


void ProcessUartIrq(UartHandle* pHUart);



