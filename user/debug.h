#ifndef DEBUG_H
#define DEBUG_H

#include "stm32f091xc.h"
#include "stdint.h"



#ifndef _UART_
	#include "uart.h"
#endif

#define ARY_CPS_PATH_COUNT 500
#define UART_ENUM_NAME_SIZE 32


typedef struct
{
	uint32_t ix;
	uint32_t max_size;
	
	uint8_t ary_dbg_chk_pts [ARY_CPS_PATH_COUNT][UART_ENUM_NAME_SIZE];
} DbgCheckPointsPath;





// clear DbgCheckPointsPath
void dbg_clear_dbg_cps_path(DbgCheckPointsPath* p_dbg_cps_path);
void dbg_set_check_point(UartHandle* phUart, DbgCheckPointsPath* p_dbg_path, uint32_t cycle_number); 

#endif











