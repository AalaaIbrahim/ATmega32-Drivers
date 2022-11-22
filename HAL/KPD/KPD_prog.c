
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_config.h"
#include "KPD_private.h"


u8 KPD_u8GetPressed(void)
{
	u8 Local_u8PressedKey = NO_KEY_PRESSED;
	u8 Local_u8RowIterator, Local_u8ColIterator;
	u8 Local_u8RowValue;

	/* Array of key values in the keypad */
	u8 Local_pu8Keypad[4][4] = KEYPAD;
	/* Array of the keypad's column and row pins */
	u8 Local_pu8KeypadPins[] = KPD_PINS;

	for(Local_u8ColIterator = 0; Local_u8ColIterator<4; Local_u8ColIterator++)
	{
		/* Activate the current column */
		DIO_u8SetPinVal(KPD_PORT, Local_pu8KeypadPins[Local_u8ColIterator], DIO_PIN_HIGH);

		for(Local_u8RowIterator = 4; Local_u8RowIterator<8; Local_u8RowIterator++)
		{
			DIO_u8GetPinVal(KPD_PORT, Local_pu8KeypadPins[Local_u8RowIterator], &Local_u8RowValue);
			if(Local_u8RowValue == DIO_PIN_LOW)
			{
				Local_u8PressedKey = Local_pu8Keypad[Local_u8RowIterator-ROW_START_INDEX][Local_u8ColIterator];

				/* Wait until the key is released */
				while(Local_u8RowValue == DIO_PIN_LOW)
				{
					DIO_u8GetPinVal(KPD_PORT, Local_pu8KeypadPins[Local_u8RowIterator], &Local_u8RowValue);
				}

				return Local_u8PressedKey;
			}
		}

		/* Deactivate the current column */
		DIO_u8SetPinVal(KPD_PORT, Local_pu8KeypadPins[Local_u8ColIterator], DIO_PIN_LOW);
	}

	return Local_u8PressedKey;
}
