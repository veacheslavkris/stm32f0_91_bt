
/*----- UART -----*/

typedef enum 
{
	CR_OFF,
	CR_ON

}CR_STATE;

typedef struct
{
	uint32_t uart_error_state;
	uint8_t chartoreceive;
	
} UartReceivedChar;

typedef enum 
{
	// STATE_SENDING_PREPARE,
	// STATE_DATA_SENDING,
	// STATE_LISTENING_PREPARE,
	// STATE_ANSW_LISTENING,
	// STATE_ANSW_DONE,
	// STATE_ERR_TIMEOUT,
	// STATE_ERR_FG_UART,
	// STATE_ERR_DATA,
	// STATE_DOWNTIME

	STATE_BT_ASKING_PREPARE,
	STATE_BT_ADDRESS_SENDING,
	STATE_BT_LISTENING_PREPARE,
	STATE_BT_ANSW_LISTENING,
	
	STATE_DT_ASKING_PREPARE,
	STATE_DT_ASK_SENDING,
	STATE_DT_LISTENING_PREPARE,
	STATE_DT_ANSW_LISTENING,
	
	STATE_AC_REPORTING_PREPARE,
	STATE_AC_REPORT_SENDING,
	
	STATE_SENDING_DONE,
	STATE_ANSW_DONE,
	STATE_ERR_TIMEOUT,
	STATE_ERR_FG_UART,
	STATE_ERR_DATA,
	STATE_DOWNTIME
	
}UartStateEnum;

typedef enum 
{
	BT_ASK,
	BT_ANS,
	DT_ASK,
	DT_ANS,
	AC_DTA
	
}UartDataTypeEnum;

typedef struct
{
	UartStateEnum enm_us;
	uint8_t str_us[UART_STATE_STRING_SIZE];
	
}UartState;

typedef struct
{
	uint32_t ary_size;
	uint32_t data_size;
	uint32_t ix_ary;
	uint8_t* p_ary_data;
	
}UartStructData;

typedef struct
{
	USART_TypeDef* pUart;
	UartState* uartState;
	UartStructData bufferRX;
	UartStructData bufferTX;
	uint8_t ary_uart_name[UART_NAME_SIZE];
	UartDataTypeEnum enm_dtyp;
	
}UartHandle;


























