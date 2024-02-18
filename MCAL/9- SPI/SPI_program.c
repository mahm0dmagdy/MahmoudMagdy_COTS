/*
 * SPI_program.c
 *
 * Created: 11/30/2023 6:02:00 PM
 *  Author: mahmo
 */ 

#include "../../Library/BIT_MATH.h"
#include "../../Library/STD_TYPES.h"
#include "../../Library/defines.h"

#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_reg.h"
#include "SPI_private.h"

void SPI_voidInit(){
	
	#if SPI_NODE == MASTER
	SET_BIT(SPCR,SPCR_MSTR);
	
		#if SPI_PRESCALER == DIVISION_BY_128
		SET_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);
		
		#elif  SPI_PRESCALER == DIVISION_BY_4
		CLR_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);
		
		#elif  SPI_PRESCALER == DIVISION_BY_16
		SET_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);
		
		#elif  SPI_PRESCALER == DIVISION_BY_64
		CLR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		CLR_BIT(SPSR,SPSR_SPI2X);
		
		#elif  SPI_PRESCALER == DIVISION_BY_2
		CLR_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
		
		#elif  SPI_PRESCALER == DIVISION_BY_8
		SET_BIT(SPCR,SPCR_SPR0);
		CLR_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
		
		#elif  SPI_PRESCALER == DIVISION_BY_32
		CLR_BIT(SPCR,SPCR_SPR0);
		SET_BIT(SPCR,SPCR_SPR1);
		SET_BIT(SPSR,SPSR_SPI2X);
		
		#else
		#error Wrong SPI_PRESCALER configuration option
		#endif
		
	#elif SPI_NODE == SLAVE
	CLR_BIT(SPCR,SPCR_MSTR);
	
	#else
	#error Wrong SPI_NODE configuration option
	#endif
	
	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);		
}

uint8 SPI_u8Transceive(uint8 Copy_u8Data){
	SPDR = Copy_u8Data;
	while(GET_BIT(SPSR,SPSR_SPIF) == 0);
	return SPDR;
}