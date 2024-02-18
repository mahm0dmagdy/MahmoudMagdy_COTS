/*
 * EEPROM_program.c
 *
 * Created: 11/28/2023 3:35:45 PM
 *  Author: mahmo
 */ 

#include "../../Library/BIT_MATH.h"
#include "../../Library/STD_TYPES.h"
#include "../../Library/defines.h"
#include <util/delay.h>

#include "../../MCAL/8- TWI/TWI_interface.h" 

#include "EEPROM_config.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"


uint8 EEPROM_u8WriteDataByte(uint16 Copy_u16LocalAddress, uint8 Copy_u8DataByte){
	uint8 Local_u8ErrState = OK;
	
	if(Copy_u16LocalAddress <= EEPROM_MAX_ADDRESS){
		uint8 Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (EEPROM_A2_CONNECTION << 2u) | (uint8)(Copy_u16LocalAddress>>8u);
		TWI_SendStartCondition();
		
		/*Send the address packet with fixed address and the A2 connection and the first 2 bits of location address*/
		TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);
		
		/*Send a data packet with the least 8 bits of the location address */
		TWI_MstrWriteDataByte((uint8)Copy_u16LocalAddress);
		
		/*Send a data packet with the required data byte to be written into the memory*/
		TWI_MstrWriteDataByte(Copy_u8DataByte);
		
		TWI_SendStopCondition();
		
		/*Wait 10ms for the EEPROM write cycle*/
		_delay_ms(10);
		}
		
	else{
		Local_u8ErrState = NOK;
	}
	return Local_u8ErrState;
}
uint8 EEPROM_u8ReadDataByte(uint16 Copy_u16LocalAddress, uint8* Copy_u8DataByte){
uint8 Local_u8ErrState = OK;

if(Copy_u8DataByte != NULL){
if(Copy_u16LocalAddress <= EEPROM_MAX_ADDRESS){
	uint8 Local_u8AddressPacket = EEPROM_FIXED_ADDRESS | (EEPROM_A2_CONNECTION << 2u) | (uint8)(Copy_u16LocalAddress>>8u);
	TWI_SendStartCondition();
	
	/*Send the address packet with fixed address and the A2 connection and the first 2 bits of location address*/
	TWI_SendSlaveAddressWithRead(Local_u8AddressPacket);
	
	/*Send a data packet with the least 8 bits of the location address */
	TWI_MstrWriteDataByte((uint8)Copy_u16LocalAddress);
	
	/*Send repeated start to change to read request*/
	TWI_SendRepeatedStart();
	
	/*send the address packet again after the repeated start, but with read request*/
	TWI_SendSlaveAddressWithRead(Local_u8AddressPacket);
	
	TWI_MstrReadDataByte(Copy_u8DataByte);
	
	TWI_SendStopCondition();
}

else{
	Local_u8ErrState = NOK;
}
}else{
	Local_u8ErrState = NULL_PTR_ERR;
}
return Local_u8ErrState;	
}
