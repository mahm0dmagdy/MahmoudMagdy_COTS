/*
 * KERNEL_private.h
 *
 * Created: 2/2/2024 5:54:43 PM
 *  Author: mahmo
 */ 

#define TASK_SUSPENDED 1
#define TASK_RESUMED   0

#ifndef KERNEL_PRIVATE_H_
#define KERNEL_PRIVATE_H_

typedef struct  
{
	uint16 periodicity;
	uint16 FirstDelay;
	void (*TaskFunc)(void);
	uint8 SuspendState;
}Task_t;

static void Scheduler(void);
#endif /* KERNEL_PRIVATE_H_ */