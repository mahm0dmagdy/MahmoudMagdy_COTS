/*
 * TIMERS_private.h
 *
 * Created: 9/30/2023 11:29:58 AM
 *  Author: mahmo
 */ 


#ifndef TIMERS_PRIVATE_H_
#define TIMERS_PRIVATE_H_

#define WDT_PRESCALER_MASK 0b11111000
#define	WDT_16   0b000
#define	WDT_32   0b001
#define	WDT_64   0b010
#define	WDT_128  0b011
#define	WDT_256  0b100
#define	WDT_512  0b101
#define	WDT_1024 0b110
#define	WDT_2048 0b111

#define NORMAL		1u
#define CTC			2u
#define PWM			3u
#define FASTPWM		4u

#define PRESCALER_MASK   0b11111000
#define DIVISION_BY_1    0b001
#define DIVISION_BY_4    0b011
#define DIVISION_BY_8    0b010
#define DIVISION_BY_64   0b011
#define DIVISION_BY_256  0b110
#define DIVISION_BY_1024 0b110

#define OC0_MASK         0b11001111
#define INVERTING        0b00110000
#define NONINVERTING     0b00100000

#define DISCONNECTED     0u

#define SET              0b00110000
#define TOGGLE           0b00010000
#define CLEAR            0b00100000

#endif /* TIMERS_PRIVATE_H_ */