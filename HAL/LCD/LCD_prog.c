
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <util/delay.h>

#include "../../HAL/LCD/LCD_interface.h"
#include "../../HAL/LCD/LCD_config.h"
#include "../../HAL/LCD/LCD_private.h"
#include "../../MCAL/DIO/DIO_interface.h"

u8 LCD_u8Init(void)
{
	u8 Local_u8ErrorStatus = OK;

	/* Wait more than 30ms */
	_delay_ms(40);

	//	LCD_u8SendCmd(LCD_FUNCTION_SET);
	//
	//	LCD_u8SendCmd(LCD_DISPLAY_CTRL);
	//
	//	LCD_u8SendCmd(LCD_SET_ENTRY_MODE);

	/*Function set command: 2 lines, 5*8 Font size*/
	LCD_u8SendCmd(0b00111000);

	/*Display on off control: display enable, disable cursor, no blink cursor*/
	LCD_u8SendCmd(0b00001100);

	/*Clear display*/
	LCD_u8SendCmd(LCD_DISPLAY_CLR);


	return Local_u8ErrorStatus;
}

static u8 LCD_u8SendCmd(u8 Copy_u8Command)
{
	u8 Local_u8ErrorStatus = OK;

	/* Indicate writing info */
	DIO_u8SetPinVal(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_PIN_LOW);

	/* Indicate we are writing a command */
	DIO_u8SetPinVal(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_PIN_LOW);

	/* Write the command itself to the data port */
	DIO_u8SetPortVal(LCD_DATA_PORT, Copy_u8Command);

	/* Send the enable pulse to latch the info on data and control ports */
	DIO_u8SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, DIO_PIN_LOW);

	return Local_u8ErrorStatus;
}

u8 LCD_u8SendData(u8 Copy_u8Data)
{
	u8 Local_u8ErrorStatus = OK;

	/* Indicate writing info */
	DIO_u8SetPinVal(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_PIN_LOW);

	/* Indicate we are writing data */
	DIO_u8SetPinVal(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_PIN_HIGH);

	/* Write the command itself to the data port */
	DIO_u8SetPortVal(LCD_DATA_PORT, Copy_u8Data);

	/* Send the enable pulse to latch the info on data and control ports */
	DIO_u8SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinVal(LCD_CONTROL_PORT, LCD_E_PIN, DIO_PIN_LOW);

	return Local_u8ErrorStatus;
}

u8 LCD_u8WriteStr(const char* Copy_pcData)
{
	u8 Local_u8ErrorStatus = OK;
	u8 Local_u8Counter = 0;

	if(Copy_pcData != NULL)
	{
		while(Copy_pcData[Local_u8Counter] != '\0')
		{
			LCD_u8SendData(Copy_pcData[Local_u8Counter++]);
		}
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}

u8 LCD_u8GoToXY(u8 Copy_u8XPosition, u8 Copy_u8YPosition)
{
	u8 Local_u8ErrorStatus = OK;
	u8 Local_u8Address;

	if(Copy_u8XPosition < 2)
	{
		if(Copy_u8XPosition == LCD_LINE_ONE) 	  Local_u8Address = Copy_u8YPosition;
		else if(Copy_u8XPosition == LCD_LINE_TWO) Local_u8Address = Copy_u8YPosition + 0x40;

		LCD_u8SendCmd(Local_u8Address+128);
	}
	else /* position out of range */
	{
		Local_u8ErrorStatus = NOK;
	}

	return Local_u8ErrorStatus;
}


u8 LCD_u8WriteSpecialChar(u8* Copy_pu8SpecialChar, u8 Copy_u8Location)
{
	u8 Local_u8ErrorStatus = OK;
	u8 Local_u8Iterator;

	if(Copy_pu8SpecialChar != NULL)
	{
		if(Copy_u8Location<8)
		{
			/* Command 0x40 and onwards forces the device to point CGRAM address */
			LCD_u8SendCmd (0x40 + (Copy_u8Location*8));

			/* Write 8 byte for generation of 1 character */
			for(Local_u8Iterator=0; Local_u8Iterator<8; Local_u8Iterator++)
			{
				LCD_u8SendData(Copy_pu8SpecialChar[Local_u8Iterator]);
			}
		}
	}

	LCD_u8SendData(Copy_u8Location);

	return Local_u8ErrorStatus;
}

u8 LCD_u8WriteNumber(u32 Copy_u32Number)
{
	u8 Local_u8ErrorStatus = OK;
	/* Max u32 num has 10 digits */
	u8 Local_pu8digits[10];

	/* Max u32 num has 10 digits + End of string character */
	u8 Local_pu8ReverseDigits[11];
	u8 Local_u8Iterator = 0, num_digits = 0;

	while(Copy_u32Number > 0)
	{
		Local_pu8digits[Local_u8Iterator++] = Copy_u32Number%10;
		Copy_u32Number /= 10;
		num_digits = Local_u8Iterator;
	}

	/* Reverse Array */
	for(Local_u8Iterator=0; Local_u8Iterator<num_digits; Local_u8Iterator++)
	{
		Local_pu8ReverseDigits[Local_u8Iterator] = Local_pu8digits[num_digits-1-Local_u8Iterator] + '0';
	}

	/* Add '\0' at the end of char array to be treated as string */
	Local_pu8ReverseDigits[num_digits] = '\0';

	/* Write the number as string to the LCD */
	LCD_u8WriteStr((char*)Local_pu8ReverseDigits);


	return Local_u8ErrorStatus;
}

