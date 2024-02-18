/*
 * ADC_program.c
 *
 * Created: 9/17/2023 2:02:31 AM
 *  Author: mahmo
 */ 
#include "../../Library/BIT_MATH.h"
#include "../../Library/STD_TYPES.h"
#include "../../Library/defines.h"

#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_reg.h"

static uint16* ADC_pu16ConversionResult = NULL;
static void(*ADC_pvNotificationFunc)(void) = NULL; 
static uint8 ADC_u8BusyFLag = IDLE;
static ADC_ChainConv_t* ADC_pstChainData = NULL;
static uint8 ADC_u8ChannelCounter;
static uint8 ADC_u8IntReason;

void ADC_voidInit(){
	#if ADC_u8REF_VOLT == AREF_REF
		CLR_BIT(ADMUX,ADMUX_REFS0);
		CLR_BIT(ADMUX,ADMUX_REFS1);
	
	#elif ADC_u8REF_VOLT == AVCC_REF
		SET_BIT(ADMUX,ADMUX_REFS0);
		CLR_BIT(ADMUX,ADMUX_REFS1);

	#elif ADC_u8REF_VOLT == INTERNAL_2560mV_REF
		SET_BIT(ADMUX,ADMUX_REFS0);
		SET_BIT(ADMUX,ADMUX_REFS1);

	#else 
		#error Wrong ADC_u8REF_VOLT configuration option
	#endif 
	
	#if ADC_u8RESOLUTION  == EIGHT_BITS
		SET_BIT(ADMUX,ADMUX_ADLAR);
		
	#elif ADC_u8RESOLUTION == TEN_BITS
		CLR_BIT(ADMUX,ADMUX_ADLAR);
		
	#else 
		#error Wrong ADC_u8RESOLUTION configuration option	
	#endif
	
	#if ADC_u8INT_ENABLE  == DISABLED
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
		
	#elif ADC_u8INT_ENABLE == ENABLED
		SET_BIT(ADCSRA,ADCSRA_ADIE);
		
	#else 
		#error Wrong ADC_u8INT_ENABLE configuration option 
	#endif
	
	/*configure prescaler bits*/
		ADCSRA &= PRESCALER_MASK;
		ADCSRA |= ADC_u8PRESCALER_VAL;
		
	/*ADC Enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);	
}

uint8 ADC_u8StartConversionSynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result){
	uint8 Local_u8ErrorState = OK;

	if(Copy_pu16Result != NULL){

		/*Check if ADC is not busy*/
		if(ADC_u8BusyFLag == IDLE){
			uint32 Local_u32TimeoutCounter = 0;

			/*ADC is now busy*/
			ADC_u8BusyFLag = BUSY;
	
	/*configure the analog channel*/
	ADMUX &= CHANNEL_MASK;
	ADMUX |= Copy_u8Channel;
	
	/*Start the conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);
	
	/*wait until the conversion is complete or the timeout is passed*/
	while(GET_BIT(ADCSRA,ADCSRA_ADIF) == 0 && (Local_u32TimeoutCounter < ADC_u32TIMEOUT)){
		Local_u32TimeoutCounter++;
	}
	if(Local_u32TimeoutCounter >= ADC_u32TIMEOUT){
		/*Loop is broken because  flag isn't raised until timeout is passed*/
		Local_u8ErrorState = TIMEOUT_ERR;
	}
	else{
		/*Loop is broken because flag is raised before the timeout*/
		
		/*Clear the conversion complete flag*/
		SET_BIT(ADCSRA,ADCSRA_ADIF);
		
		#if   ADC_u8RESOLUTION == EIGHT_BITS
		*Copy_pu16Result = ADCH; 
		#elif ADC_u8RESOLUTION == TEN_BITS
		*Copy_pu16Result = ADC;
		#endif
		/*ADC is now IDLE*/
		ADC_u8BusyFLag = IDLE;
		}
	}
	else{
		/*ADC was busy, Assign the error state*/
		Local_u8ErrorState = BUSY_STATE_ERR;
	}
	}
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
	
}

uint8 ADC_u8StartSingleConversionAsynch(uint8 Copy_u8Channel, uint16* Copy_pu16Result, void (*Copy_pvNotificationFunc)(void)){
	uint8 Local_u8ErrorState = OK;
	if((Copy_pu16Result != NULL) && (Copy_pvNotificationFunc != NULL)){
		
	/*Check if ADC is not busy*/
	if(ADC_u8BusyFLag == IDLE){
		

		/*ADC is now busy*/
		ADC_u8BusyFLag = BUSY;
		
		ADC_u8IntReason = SINGLE_CONV_ASYNCH;

		/*Initialize the result pointer globally*/
		ADC_pu16ConversionResult = Copy_pu16Result;
		
		/*Initialize the notification function globally*/
		ADC_pvNotificationFunc = Copy_pvNotificationFunc;
		
		/*configure the analog channel*/
		ADMUX &= CHANNEL_MASK;
		ADMUX |= Copy_u8Channel;
		
		/*Start the conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		
		/*Enable the ADC conversion complete interrupt*/
		SET_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else{
		Local_u8ErrorState = BUSY_STATE_ERR;
	}
	}
	
	else{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}


uint8 ADC_u8StartChainConversionAsynch(ADC_ChainConv_t* Copy_pstChain){
	uint8 Local_u8ErrorState = OK;
	if( (Copy_pstChain != NULL) && (Copy_pstChain->ChainArr != NULL) && (Copy_pstChain->NotificationFunc != NULL) && (Copy_pstChain->ResultArr != NULL) ){
		/*Check if ADC is busy*/
		if(ADC_u8BusyFLag == IDLE)
		{
		/*ADC is now busy*/	  
		ADC_u8BusyFLag = BUSY;
		
		ADC_u8IntReason = CHAIN_CONV_ASYNCH;

		
		/*Initial the global chain data*/
		ADC_pstChainData = Copy_pstChain;
		ADC_u8ChannelCounter = 0u;
		
		/*Start the first channel*/
		ADMUX &= CHANNEL_MASK;
		ADMUX |= ADC_pstChainData->ChainArr[ADC_u8ChannelCounter];
		
		/*Start the first conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		
		/*Enable ADC conversion complete interrupt*/
		SET_BIT(ADCSRA,ADCSRA_ADIE);
		
		}
		
		else
		{
			Local_u8ErrorState = BUSY_STATE_ERR;
		}
}
else
{
	Local_u8ErrorState = NULL_PTR_ERR;
}
}


/**
* @brief ADC conversion complete ISR
*/
void __vector_16 (void)  __attribute__((signal));

void __vector_16 (void)
{
	if(ADC_u8IntReason == SINGLE_CONV_ASYNCH){
		if(ADC_pu16ConversionResult != NULL)
		{
			#if   ADC_u8RESOLUTION == EIGHT_BITS
			*ADC_pu16ConversionResult = ADCH;
			#elif ADC_u8RESOLUTION == TEN_BITS
			*ADC_pu16ConversionResult = ADC;
			#endif
			
			/*Disable the ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
			
			/*ADC is now IDLE*/
			ADC_u8BusyFLag =IDLE;
			
			/*Invoke the application notification function*/
			if(ADC_pvNotificationFunc != NULL){
				ADC_pvNotificationFunc();
			}
			
			else{
				/*Notification function pointer is NULL*/
			}
		}
		
		else{
			/*Conversion result pointer is NULL*/
		}
	}
	else  /*Interrupt is due to chain conversion*/
	{
		#if ADC_u8RESOLUTION == EIGHT_BITS
		ADC_pstChainData->ResultArr[ADC_u8ChannelCounter] = ADCH;
		#elif ADC_u8RESOLUTION == TEN_BITS
		ADC_pstChainData->ResultArr[ADC_u8ChannelCounter] = ADC;
		#endif
		
		/*channel counter increment*/
		ADC_u8ChannelCounter++;
		if(ADC_u8ChannelCounter < ADC_pstChainData->ChainSize)
		{
			/*Chain is not finished yet*/
			/*Start the next conversion*/
			
			ADMUX &= CHANNEL_MASK;
			ADMUX |= ADC_pstChainData->ChainArr[ADC_u8ChannelCounter];
			
			/*Start the conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			
		}
		else
		{
			/*Chain is finished*/
			/*ADC is now IDLE*/
			ADC_u8BusyFLag = IDLE;
			
			/*Disable the ADC interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
			
			/*Invoke the notification function*/
			if(ADC_pstChainData->NotificationFunc != NULL){
				ADC_pstChainData->NotificationFunc();
			}
			else{
				/*do nothing*/
			}
		}
	}
}
