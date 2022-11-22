
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_register.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


static void (*EXTI_pvIntCallback[3]) (void) = {NULL};


void EXTI_voidInt0Init(void)
{
	/* Choose triggering option */
	MCUCR &= 0b11111100;
	MCUCR |= INT0_SENSE;

	/* Enable Specific interrupt */
	SET_BIT(GICR, GICR_INT0);
}

void EXTI_voidInt1Init(void)
{
	/* Choose triggering option */
	MCUCR &= 0b11110011;
	MCUCR |= (INT1_SENSE<<2);

#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC11);
	CLR_BIT(MCUCR, MCUCR_ISC10);

#elif INT1_SENSE == ON_CHANGE
	CLR_BIT(MCUCR, MCUCR_ISC11);
	SET_BIT(MCUCR, MCUCR_ISC10);

#elif INT1_SENSE == FALLING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC11);
	CLR_BIT(MCUCR, MCUCR_ISC10);

#elif INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC11);
	SET_BIT(MCUCR, MCUCR_ISC10);

#else
#error "Wrong INT1 sense configuration option!"
#endif

	/* Enable Specific interrupt */

}

void EXTI_voidInt2Init(void)
{
	/* Choose triggering option */
#if INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR, MCUCSR_INT2);

#elif INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR, MCUCSR_INT2);

#else
#error "Wrong INT2 sense configuration option!"
#endif

	/* Enable Specific interrupt */

}

u8 EXTI_u8SetSense(u8 Copy_u8IntNumber, u8 Copy_u8SenseMode)
{
	u8 Local_u8ErrorStatus = OK;

	if (EXTI_INT0 == Copy_u8IntNumber)
	{
		switch(Copy_u8SenseMode)
		{
		case LOW_LEVEL: CLR_BIT(MCUCR, MCUCR_ISC01); CLR_BIT(MCUCR, MCUCR_ISC00); break;
		case ON_CHANGE: CLR_BIT(MCUCR, MCUCR_ISC01); SET_BIT(MCUCR, MCUCR_ISC00); break;
		case FALLING_EDGE: SET_BIT(MCUCR, MCUCR_ISC01); CLR_BIT(MCUCR, MCUCR_ISC00); break;
		case RISING_EDGE: SET_BIT(MCUCR, MCUCR_ISC01); SET_BIT(MCUCR, MCUCR_ISC00); break;
		default: Local_u8ErrorStatus = NOK;
		}
	}
	else if (EXTI_INT1 == Copy_u8IntNumber)
	{
		switch(Copy_u8SenseMode)
		{
		case LOW_LEVEL: CLR_BIT(MCUCR, MCUCR_ISC11); CLR_BIT(MCUCR, MCUCR_ISC10); break;
		case ON_CHANGE: CLR_BIT(MCUCR, MCUCR_ISC11); SET_BIT(MCUCR, MCUCR_ISC10); break;
		case FALLING_EDGE: SET_BIT(MCUCR, MCUCR_ISC11); CLR_BIT(MCUCR, MCUCR_ISC10); break;
		case RISING_EDGE: SET_BIT(MCUCR, MCUCR_ISC11); SET_BIT(MCUCR, MCUCR_ISC10); break;
		default: Local_u8ErrorStatus = NOK;
		}
	}
	else if (EXTI_INT2 == Copy_u8IntNumber)
	{
		switch(Copy_u8SenseMode)
		{
		case FALLING_EDGE: CLR_BIT(MCUCSR, MCUCSR_INT2); break;
		case RISING_EDGE: SET_BIT(MCUCSR, MCUCSR_INT2); break;
		default: Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

u8 EXTI_u8EnableInt(u8 Copy_u8IntNumber)
{
	u8 Local_u8ErrorStatus = OK;

	switch(Copy_u8IntNumber)
	{
	case EXTI_INT0: SET_BIT(GICR, GICR_INT0); break;
	case EXTI_INT1: SET_BIT(GICR, GICR_INT1); break;
	case EXTI_INT2: SET_BIT(GICR, GICR_INT2); break;
	default: Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

u8 EXTI_u8DisableInt(u8 Copy_u8IntNumber)
{
	u8 Local_u8ErrorStatus = OK;

	switch(Copy_u8IntNumber)
	{
	case EXTI_INT0: CLR_BIT(GICR, GICR_INT0); break;
	case EXTI_INT1: CLR_BIT(GICR, GICR_INT1); break;
	case EXTI_INT2: CLR_BIT(GICR, GICR_INT2); break;
	default: Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

u8 EXTI_u8SetCallbackFn(u8 Copy_u8IntNumber, void (*Copy_pvFunction)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if (Copy_pvFunction != NULL)
	{
		if(Copy_u8IntNumber < 3)
		{
			EXTI_pvIntCallback[Copy_u8IntNumber] = Copy_pvFunction;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

/***************************** EXTI ISRs **************************/

void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if (EXTI_pvIntCallback[0] != NULL)
	{
		EXTI_pvIntCallback[0]();
	}
}

void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if (EXTI_pvIntCallback[1] != NULL)
	{
		EXTI_pvIntCallback[1]();
	}
}

void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if (EXTI_pvIntCallback[2] != NULL)
	{
		EXTI_pvIntCallback[2]();
	}
}
