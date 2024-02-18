/*
 * KERNEL_program.c
 *
 * Created: 2/2/2024 5:55:34 PM
 *  Author: mahmo
 */ 
#include "../../Library/BIT_MATH.h"
#include "../../Library/defines.h"
#include "../../Library/STD_TYPES.h"

#include "../../MCAL/6- TIMERS/TIMERS_interface.h"

#include "KERNEL_config.h"
#include "KERNEL_interface.h"
#include "KERNEL_private.h"

//This line effectively creates an array of Task_t struct, where each struct is initialized with all its members set to zero.
static Task_t SystemTasks[TASK_NUM] = {{0}};

void RTOS_voidStart(void){
	TIMER0_voidInit();
    TIMER0_voidSetComp(250);	
	TIMERS_u8SetCallBack(TIMER0_COMP, &Scheduler);
}

uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority,uint16 Copy_u16Periodicity,uint16 Copy_u16FirstDelay,void (*Copy_pvTaskFunc)(void)){
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvTaskFunc != NULL){
		if(SystemTasks[Copy_u8Priority].TaskFunc == NULL){
			SystemTasks[Copy_u8Priority].periodicity = Copy_u16Periodicity;
			SystemTasks[Copy_u8Priority].TaskFunc = Copy_pvTaskFunc;
			SystemTasks[Copy_u8Priority].SuspendState = TASK_RESUMED;
			SystemTasks[Copy_u8Priority].FirstDelay = Copy_u16FirstDelay;
		}
	else{
		/*Priority is used before, Can't over right*/
		Local_u8ErrorState = NOK;
	}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}

static void Scheduler(void){
	uint8 Local_u8TaskCounter;
	
	for(Local_u8TaskCounter=0; Local_u8TaskCounter<TASK_NUM; Local_u8TaskCounter++){
	if(SystemTasks[Local_u8TaskCounter].TaskFunc != NULL){
	if((SystemTasks[Local_u8TaskCounter].SuspendState == TASK_RESUMED)){
	if((SystemTasks[Local_u8TaskCounter].FirstDelay== 0)){
		
					/*Invoke the task function*/
					SystemTasks[Local_u8TaskCounter].TaskFunc();
					
					/*Assign first delay to be equal to the periodicity*/
					SystemTasks[Local_u8TaskCounter].FirstDelay = SystemTasks[Local_u8TaskCounter].periodicity -1;
		}
		else{
			SystemTasks[Local_u8TaskCounter].FirstDelay --;
		}
	}
	else{
		/*The function is null, Function is deleted*/
	}

	}
}

}
void RTOS_voidSuspendTask(uint8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority].SuspendState = TASK_SUSPENDED;
}
void RTOS_voidResumeTask(uint8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority].SuspendState = TASK_RESUMED;
}

void RTOS_voidDeleteTask(uint8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority].TaskFunc = NULL;
}

