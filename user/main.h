//#include "stm32f0xx.h"

#include "stm32f091xc.h"


#include "sys_clock.h" 
#include "rtc_lse_32768.h"
#include "maxim_7219.h"
#include "pc13btn.h"
#include "pa5_led.h"
#include "uart8.h"
#include "uart7.h"
#include "debug_uart.h"

#include "huart_bt.h"
#include "huart_pc.h"
#include "DecBcdCharConverter.h"



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

void init_uarts(void);

void delay_systick(uint32_t ms);

void uart_bt_request_prepare_sending(void);


/*------------- Begin Uart Transmision ------------*/
void StartSendUartData_IT(UartHandle* phUart);


void ProcessUartIrq(UartHandle* pHUart);

void init_converter(void);
void init_time(void);
