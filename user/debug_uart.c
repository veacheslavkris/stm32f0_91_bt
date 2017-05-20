#include "debug_uart.h"

#define MODE_ENUMS_COUNT 			5
#define FUNC_SATE_ENUMS_COUNT 11


/******************************************************************************/
/*                   MODES AND SUBSTATES OF UARTS : INIT                      */
/******************************************************************************/


DbgUartMode UartMode_BT_Request =	{MODE_BT_REQUEST,	"MODE_BT_REQUEST."};
DbgUartMode UartMode_DT_Request =	{MODE_DT_REQUEST,	"MODE_DT_REQUEST."};
DbgUartMode UartMode_AC_Report =	{MODE_AC_REPORT,	"MODE_AC_REPORT.."};
DbgUartMode UartMode_Idle =				{MODE_IDLE,				"MODE_IDLE......."};
DbgUartMode UartMode_Error =			{MODE_ERROR,			"MODE_ERROR......"};


DbgUartFuncState UartFState_PrepareSending =		{FST_PREPARE_SENDING,							"FST_PREPARE_SENDING....."};
DbgUartFuncState UartFState_Sending =						{FST_SENDING,											"FST_SENDING............."};
DbgUartFuncState UartFState_TermCntSent =				{FST_TRMNL_CNT_SENT,							"FST_TRMNL_CNT_SENT......"};
DbgUartFuncState UartFState_TransmitComplete =	{FST_TRANSMIT_COMPLETE,						"FST_TRANSMIT_COMPLETE..."};
DbgUartFuncState UartFState_PrepareReceiving =	{FST_PREPARE_RECEIVING,						"FST_PREPARE_RECEIVING..."};
DbgUartFuncState UartFState_Receiving =					{FST_RECEIVING,										"FST_RECEIVING..........."};
DbgUartFuncState UartFState_TermCntReceiving =	{FST_TRMNL_CNT_RECEIVED,					"FST_TRMNL_CNT_RECEIVED.."};
DbgUartFuncState UartFState_Free =							{FST_FREE,												"FST_FREE................"};
DbgUartFuncState UartFState_ErrFg =							{FST_ERR_FG,											"FST_ERR_FG.............."};
DbgUartFuncState UartFState_ErrData =						{FST_ERR_DATA,										"FST_ERR_DATA............"};
DbgUartFuncState UartFState_ErrTimeout =				{FST_ERR_TIMEOUT,									"FST_ERR_TIMEOUT........."};							


DbgUartMode ary_dbg_modes[MODE_ENUMS_COUNT];
DbgUartFuncState ary_dbg_funstates[FUNC_SATE_ENUMS_COUNT];


DbgCheckPointsPath dbg_ary_check_points;


void DebugUart_Init(void)
{
	ary_dbg_modes[0] = UartMode_BT_Request;
	ary_dbg_modes[1] = UartMode_DT_Request;
	ary_dbg_modes[2] = UartMode_AC_Report;
	ary_dbg_modes[3] = UartMode_Idle;
	ary_dbg_modes[4] = UartMode_Error;
	
	ary_dbg_funstates[0] = UartFState_PrepareSending;
	ary_dbg_funstates[1] = UartFState_Sending;
	ary_dbg_funstates[2] = UartFState_TermCntSent;
	ary_dbg_funstates[3] = UartFState_TransmitComplete;
	ary_dbg_funstates[4] = UartFState_PrepareReceiving;
	ary_dbg_funstates[5] = UartFState_Receiving;
	ary_dbg_funstates[6] = UartFState_TermCntReceiving;
	ary_dbg_funstates[7] = UartFState_Free;
	ary_dbg_funstates[8] = UartFState_ErrFg;
	ary_dbg_funstates[9] = UartFState_ErrData;
	ary_dbg_funstates[10] = UartFState_ErrTimeout;
	
	dbg_ary_check_points.ix = 0;
	dbg_ary_check_points.max_size = ARY_CHK_POINTS_COUNT;
}





void dbg_clear_dbg_cps_path(DbgCheckPointsPath* p_dbg_cps_path)
{
	
	
	
	uint32_t row_ix = 0;
	uint32_t col_ix = 0;
	
	uint32_t row_size = ARY_CHK_POINTS_COUNT;
	uint32_t col_size = UART_STATE_RECORD_SIZE;
	

	
	for(row_ix = 0; row_ix < row_size; row_ix++)
	{
		for(col_ix = 0; col_ix < col_size; col_ix++)
		{
			p_dbg_cps_path->ary_dbg_chk_pts[row_ix][col_ix]='.';
		}
		
	}
	
	p_dbg_cps_path->ix = 0;

}


//__INLINE void dbg_set_check_point(DbgControlPointEnmStr cp_enm_str)
//{
//	uint8_t chr;
//	uint32_t chr_ix;
//	uint32_t str_size = ENUM_NAME_SIZE -6;
//	
////	if(ary_cps.ix<ary_cps.max_size)
////	{
////		ary_cps.ary_check_points[ary_cps.ix].control_point = cp;
////		ary_cps.ary_check_points[ary_cps.ix].cycle = cycle_number;
////		ary_cps.ix++;
////	}
////	
//	
//	if(stc_dbg_path.ix < stc_dbg_path.max_size)
//	{
//		chr = cycle_number + 0x30;
//		
//		stc_dbg_path.ary_dbg_chk_pts_path[stc_dbg_path.ix][0] = chr;
//		stc_dbg_path.ary_dbg_chk_pts_path[stc_dbg_path.ix][1] = ' ';
//		stc_dbg_path.ary_dbg_chk_pts_path[stc_dbg_path.ix][2] = '-';
//		stc_dbg_path.ary_dbg_chk_pts_path[stc_dbg_path.ix][3] = ' ';
//	}
//	
//	for(chr_ix = 0; chr_ix<str_size; chr_ix++)
//	{
//		stc_dbg_path.ary_dbg_chk_pts_path[stc_dbg_path.ix][chr_ix+4] = cp_enm_str.ary_name[chr_ix];
//	
//	}
//	
//	stc_dbg_path.ix++;
//	
//}




void dbg_set_check_point(UartHandle* phUart, DbgCheckPointsPath* p_dbg_path, uint32_t cycle_number)
{
	
	//	|8|_|-|_|  |_|_|_|   |_|_|_|...|_|_|_|
	//  cycles_n  uart_name   mode_name
	//      4         3            16
	
	
	
	uint8_t chr;
	uint32_t chr_ix;
	uint32_t str_size;
	uint32_t col_ix = 0; 
	uint32_t row_ix = p_dbg_path->ix;
	
	
	if(p_dbg_path->ix >= p_dbg_path->max_size) p_dbg_path->ix = 0;
		
	
	chr = cycle_number + 0x30;
	
	p_dbg_path->ary_dbg_chk_pts[row_ix][col_ix++] = chr; // cycle number
	p_dbg_path->ary_dbg_chk_pts[row_ix][col_ix++] = ' ';
	p_dbg_path->ary_dbg_chk_pts[row_ix][col_ix++] = '-';
	p_dbg_path->ary_dbg_chk_pts[row_ix][col_ix++] = ' ';
	
	
	// load uart name
	str_size = 3; //UART_NAME_SIZE = 8;
	for(chr_ix = 0; chr_ix<str_size; chr_ix++)
	{
//		p_dbg_path->ary_dbg_chk_pts[row_ix][col_ix++] = phUart->ary_uart_name[chr_ix];
	}

	// load enum name
	str_size = UART_MODE_NAME_SIZE;// 16 ;
	for(chr_ix = 0; chr_ix<str_size; chr_ix++)
	{
//		p_dbg_path->ary_dbg_chk_pts[row_ix][col_ix++] = phUart->pUartMode->ary_mode_name[chr_ix];
	}
	
	p_dbg_path->ix++;
	
}



void DebugUartSetCheckPoint(UartHandle* phUart, uint32_t cycle_number)
{
	uint32_t ix_uart_enm = 0;
	uint32_t ix_uart_fst = 0;
	
	uint32_t chr_ix;
	uint32_t str_size;
	uint32_t col_ix = 0; 
	uint32_t row_ix = dbg_ary_check_points.ix;
	
	
	
	// if ary_check_points full begin from start
	if(dbg_ary_check_points.ix >= dbg_ary_check_points.max_size) dbg_ary_check_points.ix = 0;
	
	// set cycle number
	dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = (cycle_number + 0x30); // cycle number [0]
	dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = ' '; //[1]
	dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = '-'; //[2]
	dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = ' '; //[3]
	

	// set uart name
	if(phUart->uart_enm == UART_BT)
	{
		dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = 'B'; //[4]
		dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = 'T'; //[5]
	}
	else if(phUart->uart_enm == UART_PC)
	{
		dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = 'P'; //[4]
		dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = 'C'; //[5]
	}
	else 
	{
		dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = '?'; //[4]
		dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = '?'; //[5]
	}
	
	dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = ' '; //[6]
	dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = '-'; //[7]
	dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = ' '; //[8]
		
	// find UartModeEnum 
	for(ix_uart_enm = 0; ix_uart_enm < MODE_ENUMS_COUNT; ix_uart_enm++)
	{
		if(phUart->uart_mode_enm == ary_dbg_modes[ix_uart_enm].enm_mode) break; 
	}

	// find UartFuncStateEnum
	for(ix_uart_fst = 0; ix_uart_fst < FUNC_SATE_ENUMS_COUNT; ix_uart_fst++)
	{
		if(phUart->uart_func_state_enm == ary_dbg_funstates[ix_uart_fst].enm_funcstate) break; 
	}

	if(ix_uart_enm < MODE_ENUMS_COUNT)
	{
		// set enum name
		str_size = UART_MODE_NAME_SIZE;// 16 ;
		for(chr_ix = 0; chr_ix < str_size; chr_ix++)
		{
			dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = ary_dbg_modes[ix_uart_enm].ary_mode_name[chr_ix];
		}
	}
	else 
	{
		dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = '?'; 
	}
	
	dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++]=':'; //[9] or [24]
	
	if(ix_uart_fst < FUNC_SATE_ENUMS_COUNT)
	{
			// set enum name
		str_size = UART_SUBSTATE_NAME_SIZE;// 24 ;
		for(chr_ix = 0; chr_ix < str_size; chr_ix++)
		{
			dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = ary_dbg_funstates[ix_uart_fst].ary_fst_name[chr_ix];
		}
	}
	else 
	{
		dbg_ary_check_points.ary_dbg_chk_pts[row_ix][col_ix++] = '?'; // [10], [25], [48]
	}
	
	dbg_ary_check_points.ix++;

}

