
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../HAL/SW/SW_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"


u8 SW_u8ReadSwitch(SW_t* Copy_pSW_tSwitch, u8* Copy_pu8SwitchState)
{
	u8 Local_u8ErrorStatus = OK;
	u8* Local_pu8SwitchValue;
	u32 Local_u32Counter;

	if((Copy_pSW_tSwitch != NULL) && (Copy_pu8SwitchState != NULL))
	{
		DIO_u8GetPinVal(Copy_pSW_tSwitch->Port, Copy_pSW_tSwitch->Pin, Local_pu8SwitchValue);

		if(Copy_pSW_tSwitch->PullType == SW_PullUp)
		{
			*Copy_pu8SwitchState = ~(*Local_pu8SwitchValue);
		}
		else if(Copy_pSW_tSwitch->PullType == SW_PullDown)
		{
			*Copy_pu8SwitchState = *Local_pu8SwitchValue;
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}

		/* Delay for debouncing */
		for(Local_u32Counter=0; Local_u32Counter<100000; Local_u32Counter++);

	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}
