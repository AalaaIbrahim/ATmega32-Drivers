
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIM_interface.h"
#include "TIM_register.h"
#include "TIM_private.h"
#include "TIM_config.h"

static void (*TIM_pvCallbackFunctions[8])(void) = {NULL};

/*********************** Timer 0 *********************/
void TIM0_voidInit(void)
{
	/* Choose timer's wave generation mode */
	TCCR0 &= TIMER0_MODE_MASK;
	TCCR0 |= TIM0_MODE;

	/* Output Compare Match Interrupt Enable */
	//SET_BIT(TIMSK, TIMSK_OCIE0);
	/*  */

	/* temp: fast pwm. Clear on compare match,set on top */
	SET_BIT(TCCR0, 5);
	CLR_BIT(TCCR0, 4);

	/* Select timer clock */
	TCCR0 &= TIM0_CLK_MASK;
	TCCR0 |= TIM0_CLOCK_SELECT;
}

void TIM0_voidSetCompareMatchValue(u8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}


/*********************** Timer 1 *********************/
void TIM1_voidInit(void)
{
	/* Set timer 1 mode */
	TCCR1 &= TIMER1_MODE_MASK;
	TCCR1 |= TIM1_MODE;

#if TIM1_MODE == TIM1_FAST_PWM
	/* Set output compare mode */
	TCCR1A &= OC1A_MODE_MASK;
	TCCR1A |= OC1A_NONINVERTING;

#endif

#if INPUT_CAPTURE_INTERRUPT == ENABLE
	/* Set Trigger Source */
#if INPUT_CAPTURE_TRIGGER_INITIAL == ICU_RISING_EDGE
	SET_BIT(TCCR1B, TCCR1B_ICRS1);

#elif INPUT_CAPTURE_TRIGGER_INITIAL == ICU_FALLING_EDGE
	CLR_BIT(TCCR1B, TCCR1B_ICRS1);

#else
#error "Invalid Input Capture Trigger Source"
#endif

	/* Enable ICR interrupt */
	SET_BIT(TIMSK, TIMSK_TICIE1);
#endif

	/* Select timer clock */
	TCCR1B &= 0b11111000;
	TCCR1B |= TIM1_CLOCK_SELECT;

}

void TIM1_voidChannelACompareMatchValue(u16 Copy_u16Value)
{
	OCR1A = Copy_u16Value;
}

void TIM1_voidSetICRValue(u16 Copy_u16Value)
{
	ICR1 = Copy_u16Value;
}

void TIM_voidSetTimer1Value(u16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}


u16 TIM_voidGetTimer1Value(void)
{
	return TCNT1;
}

u8 ICU_voidSetTriggerEdge (u8 Copy_u8Edge)
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_u8Edge == ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B, TCCR1B_ICRS1);
	}
	else if(Copy_u8Edge == ICU_RISING_EDGE)
	{
		CLR_BIT(TCCR1B, TCCR1B_ICRS1);
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

u16 ICU_u16ReadInputCapture (void)
{
	return ICR1;
}

/*********************************************************************************/
u8 TIM_u8SetInterruptState(u8 Copy_u8InterruptID, u8 Copy_u8InterruptState)
{
	u8 Local_u8ErrorStatus = OK;

	switch (Copy_u8InterruptState)
	{
	case TIM_INTERRUPT_ENABLE:
		switch (Copy_u8InterruptID)
		{
		case TIM2_COMPARE_MATCH			 : SET_BIT(TIMSK, TIMSK_OCIE2); break;
		case TIM2_OVERFLOW				 : SET_BIT(TIMSK, TIMSK_TOIE2); break;
		case TIM1_CAPTURE_EVENT			 : SET_BIT(TIMSK, TIMSK_TICIE1); break;
		case TIM1_COMPARE_MATCH_CHANNEL_A: SET_BIT(TIMSK, TIMSK_OCIE1B); break;
		case TIM1_COMPARE_MATCH_CHANNEL_B: SET_BIT(TIMSK, TIMSK_OCIE1A); break;
		case TIM1_OVERFLOW				 : SET_BIT(TIMSK, TIMSK_TOIE1); break;
		case TIM0_COMPARE_MATCH			 : SET_BIT(TIMSK, TIMSK_OCIE0); break;
		case TIM0_OVERFLOW               : SET_BIT(TIMSK, TIMSK_TOIE0); break;
		default: Local_u8ErrorStatus = NOK;
		}
		break;

		case TIM_INTERRUPT_DISABLE:
			switch (Copy_u8InterruptID)
			{
			case TIM2_COMPARE_MATCH			 : CLR_BIT(TIMSK, TIMSK_OCIE2); break;
			case TIM2_OVERFLOW				 : CLR_BIT(TIMSK, TIMSK_TOIE2); break;
			case TIM1_CAPTURE_EVENT			 : CLR_BIT(TIMSK, TIMSK_TICIE1); break;
			case TIM1_COMPARE_MATCH_CHANNEL_A: CLR_BIT(TIMSK, TIMSK_OCIE1A); break;
			case TIM1_COMPARE_MATCH_CHANNEL_B: CLR_BIT(TIMSK, TIMSK_OCIE1B); break;
			case TIM1_OVERFLOW				 : CLR_BIT(TIMSK, TIMSK_TOIE1); break;
			case TIM0_COMPARE_MATCH			 : CLR_BIT(TIMSK, TIMSK_OCIE0); break;
			case TIM0_OVERFLOW               : CLR_BIT(TIMSK, TIMSK_TOIE0); break;
			default: Local_u8ErrorStatus = NOK;
			}
			break;

			default: Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}


u8 TIM_u8SetCallback(u8 Copy_u8InterruptID, void (*Copy_pvCallbackFunction)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if (Copy_pvCallbackFunction != NULL)
	{
		if((Copy_u8InterruptID>= 0) && (Copy_u8InterruptID <8))
		{
			TIM_pvCallbackFunctions[Copy_u8InterruptID] = Copy_pvCallbackFunction;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}

/**************************** ISRs **************************/
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	if (TIM_pvCallbackFunctions[TIM2_COMPARE_MATCH] != NULL)
	{
		TIM_pvCallbackFunctions[TIM2_COMPARE_MATCH]();
	}
}

void __vector_5 (void) __attribute__((signal));
void __vector_5 (void)
{
	if (TIM_pvCallbackFunctions[TIM2_OVERFLOW] != NULL)
	{
		TIM_pvCallbackFunctions[TIM2_OVERFLOW]();
	}
}

void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if (TIM_pvCallbackFunctions[TIM1_CAPTURE_EVENT] != NULL)
	{
		TIM_pvCallbackFunctions[TIM1_CAPTURE_EVENT]();
	}
}

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	if (TIM_pvCallbackFunctions[TIM1_COMPARE_MATCH_CHANNEL_A] != NULL)
	{
		TIM_pvCallbackFunctions[TIM1_COMPARE_MATCH_CHANNEL_A]();
	}
}

void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	if (TIM_pvCallbackFunctions[TIM1_COMPARE_MATCH_CHANNEL_B] != NULL)
	{
		TIM_pvCallbackFunctions[TIM1_COMPARE_MATCH_CHANNEL_B]();
	}
}

void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if (TIM_pvCallbackFunctions[TIM1_OVERFLOW] != NULL)
	{
		TIM_pvCallbackFunctions[TIM1_OVERFLOW]();
	}
}

void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if (TIM_pvCallbackFunctions[TIM0_COMPARE_MATCH] != NULL)
	{
		TIM_pvCallbackFunctions[TIM0_COMPARE_MATCH]();
	}
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if (TIM_pvCallbackFunctions[TIM0_OVERFLOW] != NULL)
	{
		TIM_pvCallbackFunctions[TIM0_OVERFLOW]();
	}
}
