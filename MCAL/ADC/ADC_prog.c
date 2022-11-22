
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_register.h"
#include "ADC_private.h"
#include "ADC_config.h"

static void (*ADC_pvCallback)(void) = NULL;

static u8* ADC_pu8Reading = NULL;

static u8 ADC_ConversionState = ADC_IDLE;

static Chain_t* ADC_GlobalChain;

static u8 ADC_ISRsource;

static u8 ChainIndex = 0;



void ADC_voidInit(void)
{
	/* Set ADC configuration */
#if ADC_RESOLUTION == RES_8_BITS
	SET_BIT(ADMUX, ADMUX_ADLAR);

#elif ADC_RESOLUTION == RES_10_BITS
	CLR_BIT(ADMUX, ADMUX_ADLAR);

#else
#error "Undefined Resolution!"
#endif

	/* Reference voltage selection */
	ADMUX &= 0b00111111;
	ADMUX |= ADC_REFERENCE;

	/* Set triggering mode */
#if ADC_AUTO_TRIG == ENABLE
	SET_BIT(ADCSRA, ADCSRA_ADATE);
	/* Select Triggering Signal */
	SFIOR &= 0b00011111;
	SFIOR |= ADC_TRIGGER_SIGNAL;

#elif ADC_AUTO_TRIG == DISABLE
	CLR_BIT(ADCSRA, ADCSRA_ADATE);

#else
#error " "
#endif

	/* Enable or Disable interrupt on complete conversion */
#if ADC_INTERRUPT == ENABLE
	SET_BIT(ADCSRA, ADCSRA_ADIE);

#elif ADC_INTERRUPT == DISABLE
	CLR_BIT(ADCSRA, ADCSRA_ADIE);

#else
#error " "
#endif

	/* Set pre-scaler */
	ADCSRA &= 0b11111000;
	ADCSRA |= ADC_PRESCALER;

	/* Enable ADC peripheral */
	SET_BIT(ADCSRA, ADCSRA_ADEN);

}

u16 ADC_u8GetChannelReading(u8 Copy_u8Channel)
{
	/* Select ADC Channel */
	ADMUX &= 0b11100000;
	ADMUX |= Copy_u8Channel;

	if(ADC_AUTO_TRIG == DISABLE)
	{
		/* Start Conversion */
		SET_BIT(ADCSRA, ADCSRA_ADSC);

		/* Wait until conversion is complete */
		while(!GET_BIT(ADCSRA, ADCSRA_ADIF));

		/* Clear the Conversion Complete Flag */
		SET_BIT(ADCSRA, ADCSRA_ADIF);
	}

#if ADC_RESOLUTION == RES_8_BITS
	return (u16)ADCH;

#elif ADC_RESOLUTION == RES_10_BITS
	return ADC_LH;

#endif

}

u8 ADC_u8StartConversionAsync(u8 Copy_u8Channel, u8* Copy_pu8Reading, void (*Copy_pvNotificationCallback)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if(ADC_ConversionState == ADC_IDLE)
	{
		if((Copy_pu8Reading != NULL) && (Copy_pvNotificationCallback != NULL))
		{
			ADC_ConversionState = ADC_BUSY;

			/* To indicate to the ISR that the interrupt came from a single async conversion */
			ADC_ISRsource = ASYNC_SINGLE_CONVERSION;

			ADC_pu8Reading = Copy_pu8Reading;

			ADC_pvCallback = Copy_pvNotificationCallback;

			/* Select ADC Channel */
			ADMUX &= 0b11100000;
			ADMUX |= Copy_u8Channel;

			/* Start Conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/* Enable ADC Interrupt */
			SET_BIT(ADCSRA, ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorStatus = NULL_PTR;
		}
	}
	else
	{
		Local_u8ErrorStatus = BUSY_FUNCTION;
	}

	return Local_u8ErrorStatus;
}

u8 ADC_u8StartChainAsync(Chain_t *Copy_chain)
{
	u8 Local_u8ErrorState = OK;

	if (Copy_chain != NULL)
	{
		if (ADC_ConversionState == ADC_IDLE)
		{
			/* Change Conversion State to indicate the ADC is busy */
			ADC_ConversionState = ADC_BUSY;

			/* To indicate to the ISR that the interrupt came from a chain async conversion */
			ADC_ISRsource = ASYNC_CHAIN_CONVERSION;

			/* Store the chain parameters passed by user in global chain */
			ADC_GlobalChain = Copy_chain;

			/* Make sure the chain index is initialized with zero */
			ChainIndex = 0;

			/* Select ADC Channel */
			ADMUX &= 0b11100000;
			ADMUX |= *(ADC_GlobalChain -> ChannelArray);

			/* Start Conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);

			/* Enable ADC Interrupt */
			SET_BIT(ADCSRA, ADCSRA_ADIE);

		}
		else
		{
			Local_u8ErrorState = BUSY_FUNCTION;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR;
	}

	return Local_u8ErrorState;
}

u8 ADC_u8SetCallback(void (*Copy_pvFunction)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if (Copy_pvFunction != NULL)
	{
		ADC_pvCallback = Copy_pvFunction;
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

/*----------------------------------------------------------------------------------*/
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{

	//	if (ADC_pvCallback != NULL)
	//	{
	//		ADC_pvCallback();
	//	}

	if (ADC_ISRsource == ASYNC_SINGLE_CONVERSION)
	{
		*ADC_pu8Reading = ADCH;

		/* Indicate the ADC peripheral is Idle */
		ADC_ConversionState = ADC_IDLE;

		/* Invoke the callback function */
		if (ADC_pvCallback != NULL)
		{
			ADC_pvCallback();
		}

		/* Disable Interrupt */
		CLR_BIT(ADCSRA, ADCSRA_ADIE);

		/* Clear Asynchronous single conversion flag */
		ADC_ISRsource = 0;
	}
	else if(ADC_ISRsource == ASYNC_CHAIN_CONVERSION)
	{

		ADC_GlobalChain -> ResultArray[ChainIndex++] = ADCH;

		if (ChainIndex < ADC_GlobalChain -> ChainSize)
		{
			/* Select new ADC Channel */
			ADMUX &= 0b11100000;
	 		ADMUX |= ADC_GlobalChain -> ChannelArray[ChainIndex];

			/* Start Conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);
		}
		else
		{
			/* Indicate the ADC peripheral is Idle */
			ADC_ConversionState = ADC_IDLE;

			/* Clear Asynchronous chain conversion flag */
			ADC_ISRsource = 0;

			if ((ADC_GlobalChain -> NotificationFunction) != NULL)
			{
				/* Call Notification function */
				ADC_GlobalChain -> NotificationFunction();
			}

			/* Disable Interrupt */
			CLR_BIT(ADCSRA, ADCSRA_ADIE);
		}
	}
}
