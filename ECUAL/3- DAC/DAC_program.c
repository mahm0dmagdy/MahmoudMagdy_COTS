/*
 * program.c
 *
 * Created: 9/15/2023 10:38:12 PM
 *  Author: mahmo

 */ 
#include "../../Library/defines.h"
#include "../../Library/STD_TYPES.h"
#include "DAC_interface.h"
#include "../../MCAL/2- PORT/PORT_reg.h"
#include "../../MCAL/1- DIO/DIO_interface.h"

void DAC_voidSetAnalogVolt(uint16 Copy_u16Volt){
	//f32 Local_f32StepSize = 0.02;
	DIO_u8SetPortValue(PORTC,(Copy_u16Volt/0.02));
}