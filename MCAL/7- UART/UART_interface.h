/*
 * UART_interface.h
 *
 * Created: 10/19/2023 2:32:56 PM
 *  Author: mahmo
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_voidInit(void);
void UART_voidTransmit(uint8 Copy_u8Data);
uint8 UART_voidReceiveData(void);



#endif /* UART_INTERFACE_H_ */