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

#include "systick.h"

#define BT_TIMEOUT_MS	8000



//// ------- Date Time Request
const uint8_t DT_REQ_LENGTH = 7;
uint8_t ary_dt_req[DT_REQ_LENGTH]={'<','?','t','i','m','e','!'};

const uint8_t DT_ANSW_LENGTH = 11;
uint8_t ary_dt_answer[DT_ANSW_LENGTH];		
		
/*------------- SysTick -------------*/
volatile uint32_t bt_timeout_start;



/******************************************************************************/
/*                        ProcessUartIrq CHECK STATE                          */
/******************************************************************************/






/******************************************************************************/
/*                                  FUNCTIONS                                 */
/******************************************************************************/

__STATIC_INLINE uint32_t IsBtTimoutDone(void)
{
	return ( GetTicksSince(bt_timeout_start) >= BT_TIMEOUT_MS );
}

__STATIC_INLINE void StartBtTimout(void)
{
	bt_timeout_start = GetSystickCount();
}

/*-------------  Functions  -------------*/
void prepare_ac_report_for_pc(void);
void prepare_dt_asking_pc(void);

void init_uarts(void);

void uart_bt_request_prepare_sending(void);


/*------------- Begin Uart Transmision ------------*/
void StartSendUartData_IT(UartHandle* phUart);


void ProcessUartIrq(UartHandle* pHUart);

void init_converter(void);
void init_time(void);
