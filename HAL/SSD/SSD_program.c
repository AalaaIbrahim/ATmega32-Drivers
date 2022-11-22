
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "../../HAL/SSD/SSD_interface.h"


u8 SSD_Values[10] =
{
		0b11000000,     /* zero */
		0b11111001,     /* one  */
		0b10100100,     /* two  */
		0b10110000,     /* three */
		0b10011001,     /* four */
		0b10010010,     /* five */
		0b10000010,     /* six  */
		0b11111000,     /* seven */
		0b10000000,     /* eight */
		0b10010000      /* nine */
};

u8 SSD_u8EnableSSD(SSD_t* Copy_pu8SSDInfo)
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pu8SSDInfo != NULL)
	{
		DIO_u8SetPinDir(Copy_pu8SSDInfo->EnablePort, Copy_pu8SSDInfo->EnablePin, DIO_PIN_OUT);

		if(Copy_pu8SSDInfo->ComType == CommonAnode)
		{
			DIO_u8SetPinVal(Copy_pu8SSDInfo->EnablePort, Copy_pu8SSDInfo->EnablePin, DIO_PIN_HIGH);
		}
		else if(Copy_pu8SSDInfo->ComType == CommonCathode)
		{
			DIO_u8SetPinVal(Copy_pu8SSDInfo->EnablePort, Copy_pu8SSDInfo->EnablePin, DIO_PIN_LOW);
		}
		else
		{
			u8 Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		u8 Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

u8 SSD_u8DisableSSD(SSD_t* Copy_pu8SSDInfo)
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pu8SSDInfo != NULL)
	{
		DIO_u8SetPinDir(Copy_pu8SSDInfo->EnablePort, Copy_pu8SSDInfo->EnablePin, DIO_PIN_OUT);

		if(Copy_pu8SSDInfo->ComType == CommonAnode)
		{
			DIO_u8SetPinVal(Copy_pu8SSDInfo->EnablePort, Copy_pu8SSDInfo->EnablePin, DIO_PIN_LOW);
		}
		else if(Copy_pu8SSDInfo->ComType == CommonCathode)
		{
			DIO_u8SetPinVal(Copy_pu8SSDInfo->EnablePort, Copy_pu8SSDInfo->EnablePin, DIO_PIN_HIGH);
		}
		else
		{
			u8 Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		u8 Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

u8 SSD_u8DisplayNum(SSD_t* Copy_pu8SSDInfo, u8 Copy_u8Number)
{
	u8 Local_u8ErrorStatus = OK;

	if(Copy_pu8SSDInfo != NULL)
	{
		DIO_u8SetPortDir(Copy_pu8SSDInfo->Port, DIO_PORT_HIGH);

		if(Copy_pu8SSDInfo->ComType == CommonAnode)
		{
			DIO_u8SetPortVal(Copy_pu8SSDInfo->Port, SSD_Values[Copy_u8Number]);
		}
		else if(Copy_pu8SSDInfo->ComType == CommonCathode)
		{
			DIO_u8SetPortVal(Copy_pu8SSDInfo->Port, ~(SSD_Values[Copy_u8Number]));
		}
		else
		{
			u8 Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		u8 Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}
