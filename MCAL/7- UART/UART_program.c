/*
 * UART_program.c
 *
 * Created: 10/19/2023 2:32:40 PM
 *  Author: mahmo
 */ 
#include "../../Library/BIT_MATH.h"
#include "../../Library/STD_TYPES.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_reg.h"


void UART_voidInit(void){
	
	uint8 Local_u8UCSRAVal = 0u;
	
	/*Transmitter enable*/
	SET_BIT(UCSRB,UCSRB_TXEN);
	
	/*Receiver enable*/
	SET_BIT(UCSRB,UCSRB_RXEN);

	/*Asynch mode*/
	CLR_BIT(Local_u8UCSRAVal,UCSRC_UMSEL);

	/*Disable parity*/
	CLR_BIT(Local_u8UCSRAVal,UCSRC_UPM0);	
	CLR_BIT(Local_u8UCSRAVal,UCSRC_UPM1);
	
	/*1 stop bit*/
	CLR_BIT(Local_u8UCSRAVal,UCSRC_USBS);

	/*Character size: 8 bits*/
	SET_BIT(Local_u8UCSRAVal,UCSRC_UCSZ0);
	SET_BIT(Local_u8UCSRAVal,UCSRC_UCSZ1);

	/*Register select: UCSRC*/
	SET_BIT(Local_u8UCSRAVal,UCSRC_URSEL);
	UCSRC = Local_u8UCSRAVal;
	
	/*Baud rate: 9600bps*/
	UBRRL = 103u;
}

void UART_voidTransmit(uint8 Copy_u8Data){
	/*Wait until transmit buffer is ready*/
	while( ( GET_BIT(UCSRA,UCSRA_UDRE) ) == 0 );
	UDR = Copy_u8Data;
}

uint8 UART_voidReceive(void){
	/*wait until there is data in the receive buffer*/
	while( (GET_BIT(UCSRA,UCSRA_RXC) )== 0);
	return UDR;
}
