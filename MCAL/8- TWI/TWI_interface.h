/*
 * TWI_interface.h
 *
 * Created: 11/9/2023 4:11:05 PM
 *  Author: mahmo
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum
{
	  NoError=0,
	  NullPtrErr,
	  StartCondErr,
	  RepStartCondErr,
	  SlaveAddressWithWriteErr,
	  SlaveAddressWithReadErr,
	  MstrWriteByteWithAchErr,
	  MstrReadByteWithAchErr,
}TWI_ERROR_t;

void TWI_voidMasterInit(uint8 Copy_u8Address);
void TWI_voidSlaveInit(uint8 Copy_u8Address);

TWI_ERROR_t TWI_SendStartCondition(void);
TWI_ERROR_t TWI_SendRepeatedStart(void);

TWI_ERROR_t TWI_SendSlaveAddressWithWrite(uint8 Copy_u8SlaveAddress);
TWI_ERROR_t TWI_SendSlaveAddressWithRead(uint8 Copy_u8SlaveAddress);

TWI_ERROR_t TWI_MstrWriteDataByte(uint8 Copy_u8DataByte);
TWI_ERROR_t TWI_MstrReadDataByte(uint8* Copy_u8DataByte);

void TWI_SendStopCondition(void);


#endif /* TWI_INTERFACE_H_ */