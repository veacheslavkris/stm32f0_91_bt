#include "debug.h"

//DbgCheckPointsPath stc_dbg_path = {0, ARY_CPS_PATH_COUNT};

																							
void dbg_clear_dbg_cps_path(DbgCheckPointsPath* p_dbg_cps_path)
{
	
	
	
	uint32_t row_ix = 0;
	uint32_t col_ix = 0;
	
	uint32_t row_size = ARY_CPS_PATH_COUNT;
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
		p_dbg_path->ary_dbg_chk_pts[row_ix][col_ix++] = phUart->ary_uart_name[chr_ix];
	}

	// load enum name
	str_size = UART_MODE_NAME_SIZE;// 16 ;
	for(chr_ix = 0; chr_ix<str_size; chr_ix++)
	{
		p_dbg_path->ary_dbg_chk_pts[row_ix][col_ix++] = phUart->pUartMode->ary_mode_name[chr_ix];
	}
	
	p_dbg_path->ix++;
	
}


