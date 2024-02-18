/*
 * KERNEL_interface.h
 *
 * Created: 2/2/2024 5:55:15 PM
 *  Author: mahmo
 */ 


#ifndef KERNEL_INTERFACE_H_
#define KERNEL_INTERFACE_H_

void RTOS_voidStart(void);

uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority,uint16 Copy_u16Periodicity,uint16 Copy_u16FirstDelay,void (*Copy_pvTaskFunc)(void));

void RTOS_voidSuspendTask(uint8 Copy_u8Priority);
void RTOS_voidResumeTask(uint8 Copy_u8Priority);
void RTOS_voidDeleteTask(uint8 Copy_u8Priority);

#endif /* KERNEL_INTERFACE_H_ */