/*
 * program.c
 *
 *  Created on: Aug 26, 2022
 *      Author: ME
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_interface.h"

#include "DIO_register.h"

/**
 * @def function to configure a single DIO pin as input/output
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Pin the pin number in the given port
 * @return error status
 */
u8 DIO_u8SetPinDir(u8 Copy_u8Port,u8 Copy_u8Pin, u8 Copy_u8Dir)
{
	u8 Local_u8ErrorStatus = OK;
	switch(Copy_u8Port)
	{
	case DIO_PORT_A:
		if(Copy_u8Dir == DIO_PIN_IN) CLR_BIT(DDRA, Copy_u8Pin);
		else if (Copy_u8Dir == DIO_PIN_OUT) SET_BIT(DDRA, Copy_u8Pin);
		else Local_u8ErrorStatus = NOK; break;

	case DIO_PORT_B:
		if(Copy_u8Dir == DIO_PIN_IN) CLR_BIT(DDRB, Copy_u8Pin);
		else if (Copy_u8Dir == DIO_PIN_OUT) SET_BIT(DDRB, Copy_u8Pin);
		else Local_u8ErrorStatus = NOK;	break;

	case DIO_PORT_C:
		if(Copy_u8Dir == DIO_PIN_IN) CLR_BIT(DDRC, Copy_u8Pin);
		else if (Copy_u8Dir == DIO_PIN_OUT) SET_BIT(DDRC, Copy_u8Pin);
		else Local_u8ErrorStatus = NOK;	break;

	case DIO_PORT_D:
		if(Copy_u8Dir == DIO_PIN_IN) CLR_BIT(DDRD, Copy_u8Pin);
		else if (Copy_u8Dir == DIO_PIN_OUT) SET_BIT(DDRD, Copy_u8Pin);
		else Local_u8ErrorStatus = NOK;	break;

	default : Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}

/**
 * @def function to configure an entire DIO port as input/output
 * @param Copy_u8Port the required port
 * @param Copy_u8Dir the desired direction whether input or output
 * @return error status
 */
u8 DIO_u8SetPortDir(u8 Copy_u8Port, u8 Copy_u8Dir)
{
	u8 Local_u8ErrorStatus = OK;

	switch (Copy_u8Port)
	{
	case DIO_PORT_A: DDRA = Copy_u8Dir; break;
	case DIO_PORT_B: DDRB = Copy_u8Dir; break;
	case DIO_PORT_C: DDRC = Copy_u8Dir; break;
	case DIO_PORT_D: DDRD = Copy_u8Dir; break;
	default : Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

/**
 * @def function to configure a single DIO pin as input/output
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Pin the pin number in the given port
 * @return error status
 */
u8 DIO_u8SetPinVal(u8 Copy_u8Port,u8 Copy_u8Pin, u8 Copy_u8Value)
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_u8Pin >= 0 && Copy_u8Pin <= 7)
	{
		if(Copy_u8Value == DIO_PIN_LOW)
		{
			switch (Copy_u8Port)
			{
			case DIO_PORT_A: PORTA &= ~(1<<Copy_u8Pin); break;
			case DIO_PORT_B: PORTB &= ~(1<<Copy_u8Pin); break;
			case DIO_PORT_C: PORTC &= ~(1<<Copy_u8Pin); break;
			case DIO_PORT_D: PORTD &= ~(1<<Copy_u8Pin); break;
			default : Local_u8ErrorStatus = NOK;
			}
		}
		else if(Copy_u8Value == DIO_PIN_HIGH)
		{
			switch (Copy_u8Port)
			{
			case DIO_PORT_A: PORTA |= (1<<Copy_u8Pin); break;
			case DIO_PORT_B: PORTB |= (1<<Copy_u8Pin); break;
			case DIO_PORT_C: PORTC |= (1<<Copy_u8Pin); break;
			case DIO_PORT_D: PORTD |= (1<<Copy_u8Pin); break;
			default : Local_u8ErrorStatus = NOK;
			}
		}
		else Local_u8ErrorStatus = NOK;
	}
	else Local_u8ErrorStatus = NOK;

	return Local_u8ErrorStatus;
}

/**
 * @def function to configure a single DIO pin as input/output
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Value the desired value to set the entire port to
 * @return error status
 */
u8 DIO_u8SetPortVal(u8 Copy_u8Port, u8 Copy_u8Value)
{
	u8 Local_u8ErrorStatus = OK;

	switch (Copy_u8Port)
	{
	case DIO_PORT_A: PORTA = Copy_u8Value; break;
	case DIO_PORT_B: PORTB = Copy_u8Value; break;
	case DIO_PORT_C: PORTC = Copy_u8Value; break;
	case DIO_PORT_D: PORTD = Copy_u8Value; break;
	default : Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

/**
 * @def function to get the value of a single DIO pin whether high or low
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Pin the pin number in the given port
 * @param Copy_pu8Val pointer to a variable to store pin value
 * @return error status
 */
u8 DIO_u8GetPinVal(u8 Copy_u8Port,u8 Copy_u8Pin, u8* Copy_pu8Val)
{
	u8 Local_u8ErrorStatus = OK;

	if((Copy_pu8Val != NULL) && (Copy_u8Pin >= 0 && Copy_u8Pin <= 7))
	{
		switch (Copy_u8Port)
		{
		case DIO_PORT_A: *Copy_pu8Val = GET_BIT(PINA,Copy_u8Pin); break;
		case DIO_PORT_B: *Copy_pu8Val = GET_BIT(PINB,Copy_u8Pin); break;
		case DIO_PORT_C: *Copy_pu8Val = GET_BIT(PINC,Copy_u8Pin); break;
		case DIO_PORT_D: *Copy_pu8Val = GET_BIT(PIND,Copy_u8Pin); break;
		default : Local_u8ErrorStatus = NOK;
		}
	}
	else Local_u8ErrorStatus = NOK;

	return Local_u8ErrorStatus;
}

/**
 * @def function to toggle the value of a single DIO pin (from high or low and vice versa)
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Pin the pin number in the given port
 * @return error status
 */
u8 DIO_u8TogglePin(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 Local_u8ErrorStatus = OK;

	if((Copy_u8Pin >= 0) && (Copy_u8Pin <= 7))
	{
		switch (Copy_u8Port)
		{
		case DIO_PORT_A: GET_BIT(PINA,Copy_u8Pin)? CLR_BIT(PORTA,Copy_u8Pin): SET_BIT(PORTA,Copy_u8Pin); break;
		case DIO_PORT_B: GET_BIT(PINB,Copy_u8Pin)? CLR_BIT(PORTB,Copy_u8Pin): SET_BIT(PORTB,Copy_u8Pin); break;
		case DIO_PORT_C: GET_BIT(PINC,Copy_u8Pin)? CLR_BIT(PORTC,Copy_u8Pin): SET_BIT(PORTC,Copy_u8Pin); break;
		case DIO_PORT_D: GET_BIT(PIND,Copy_u8Pin)? CLR_BIT(PORTD,Copy_u8Pin): SET_BIT(PORTD,Copy_u8Pin); break;
		default : Local_u8ErrorStatus = NOK;
		}
	}
	else Local_u8ErrorStatus = NOK;

	return Local_u8ErrorStatus;
}
