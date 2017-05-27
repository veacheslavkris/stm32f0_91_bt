#ifndef DEBUG_UART_H
#define DEBUG_UART_H

#include "stm32f091xc.h"
//#include "stdint.h"
#include "uart_states.h"


#define UART_MODE_NAME_SIZE			16
#define UART_SUBSTATE_NAME_SIZE	24


#define ARY_CHK_POINTS_COUNT 200
#define UART_STATE_RECORD_SIZE 64


typedef struct
{
	UartModeEnum enm_mode;
	uint8_t ary_mode_name[UART_MODE_NAME_SIZE];
	
}DbgUartMode;

typedef struct
{
	UartFuncStateEnum enm_funcstate;
	uint8_t ary_fst_name[UART_SUBSTATE_NAME_SIZE];

}DbgUartFuncState;




typedef struct
{
	uint32_t ix; // curr_row
	uint32_t max_size;
	
	uint8_t ary_dbg_chk_pts [ARY_CHK_POINTS_COUNT][UART_STATE_RECORD_SIZE];

} DbgCheckPointsPath;







void DebugUart_Init(void);
void DebugUartSetCheckPoint(UartHandle* phUart, uint32_t cycle_number);

void dbg_clear_dbg_cps_path(DbgCheckPointsPath* p_dbg_cps_path);
void dbg_set_check_point(UartHandle* phUart, DbgCheckPointsPath* p_dbg_path, uint32_t cycle_number); 

#endif











