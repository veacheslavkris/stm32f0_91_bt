#ifndef DEC_BCD_CHAR_CONVERTER_H
#define DEC_BCD_CHAR_CONVERTER_H

#include "stm32f091xc.h"
#include "ctype.h"


#define ARY_BCD_SIZE	10


typedef struct 
{
	uint32_t dec;
	uint32_t digits_count;
	uint8_t ary_bcd[ARY_BCD_SIZE];
}StructDecToBcd;



void ConvertDecToBcd(StructDecToBcd*  structDecToBcd);
















#endif




