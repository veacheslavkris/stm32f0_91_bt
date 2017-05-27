#include "DecBcdCharConverter.h"



void ConvertDecToBcd(StructDecToBcd*  structDecToBcd)
{
	uint32_t ix;
	uint32_t digits_count = structDecToBcd->digits_count;
	uint32_t cur_power;
	uint32_t tmp_power;
	uint32_t dec = structDecToBcd->dec;

	// zeroed array 
	for (ix = 0; ix < digits_count; ix++)
	{
		structDecToBcd->ary_bcd[ix] = 0;
	}

	// ix is also dec_power 
	for (ix = digits_count - 1; ix > 0; ix--)
	{
		tmp_power = ix;
		cur_power = 1;
		
		// form current investigated power of dec
		while (tmp_power)
		{
			cur_power *= 10;

			tmp_power--;
		}

		tmp_power = 0;

		// count of current power
		while (dec >= cur_power)
		{
			tmp_power++;
			dec -= cur_power;
		}

		structDecToBcd->ary_bcd[ix] = tmp_power;


	}

	structDecToBcd->ary_bcd[0] = dec;





	

}





