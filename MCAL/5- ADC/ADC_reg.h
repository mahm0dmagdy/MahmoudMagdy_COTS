/*
 * ADC_reg.h
 *
 * Created: 9/17/2023 2:03:32 AM
 *  Author: mahmo
 */ 


#ifndef ADC_REG_H_
#define ADC_REG_H_

#define ADMUX			*((volatile uint8*)0x27)     /*ADC multiplexer selection register*/
#define ADMUX_REFS1		 7							 /*Reference Selection Bit1*/
#define ADMUX_REFS0		 6   						 /*Reference Selection Bit0*/
#define ADMUX_ADLAR		 5						     /*Write one to ADLAR to left adjust the result. Otherwise, the result is right adjusted*/

#define SFIOR *((volatile uint8*)0x50)
#define ADTS2 7u
#define ADTS1 6u
#define ADTS0 5u

#define ADCSRA			*((volatile uint8*)0x26)
#define ADCSRA_ADEN		7
#define ADCSRA_ADSC		6
#define ADCSRA_ADATE    5
#define ADCSRA_ADIF		4
#define ADCSRA_ADIE		3


#define ADCH *((volatile uint8*)0x25)	/*data high register*/
#define ADCL *((volatile uint8*)0x24)	/*data low register */
#define ADC  *((volatile uint16*)0x24)   /*ADC data register */






#endif /* ADC_REG_H_ */