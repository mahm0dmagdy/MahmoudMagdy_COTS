/*
 * EEPROM_interface.h
 *
 * Created: 11/28/2023 3:36:06 PM
 *  Author: mahmo
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


uint8 EEPROM_u8WriteDataByte(uint16 Copy_u16LocalAddress, uint8 Copy_u8DataByte);
uint8 EEPROM_u8ReadDataByte(uint16 Copy_u16LocalAddress, uint8* Copy_u8DataByte);



#endif /* EEPROM_INTERFACE_H_ */