
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_interface.h"
#include "UART_register.h"
#include "UART_private.h"
#include "UART_config.h"

static u8 Global_u8UARTState = UART_IDLE;

static u8 Global_u8Char2Transmit;

static char* Global_pcTxStr = NULL;

static u8* Global_pu8ReceivedChar = NULL;

static u16 Global_u16RxBufferSize;

static u8 Global_u8UDRIntSource = 5;

static u8 Global_u8RxIntSource = 5;

static u16 Global_u16TxChainIndex = 0;

static u16 Global_u16RxChainIndex = 0;

static void (*UART_pvCallbackFunctions[3])(void) = {NULL};


void UART_voidInit(void)
{
	u8 Local_u8UCSRC = 0X80, Local_u8UBRRH = 0;
	u16 Local_u16BaudRate;

	SET_BIT(Local_u8UCSRC, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRC, UCSRC_UCSZ0);

	/* The Value to store in the Baud Rate Registers */
	Local_u16BaudRate = (u32)UART_OSC_FREQ/((u16)UART_BAUD_RATE*16);

#if USART_MODE == USART_SYNCHRONOUS
	SET_BIT(Local_u8UCSRC, UCSRC_UMSEL);

#elif USART_MODE == USART_ASYNCHRONOUS
	/* Default */

#else
#error " "
#endif

#if MULTI_PROCESSOR_COMM == DISABLE
	CLR_BIT(UCSRA, UCSRA_MPCM);

#elif MULTI_PROCESSOR_COMM == ENABLE
	SET_BIT(UCSRA, UCSRA_MPCM);

#else
#error " "
#endif

#if UART_SPEED == UART_NORMAL_SPEED
	CLR_BIT(UCSRA, UCSRA_U2X);
	UBRRL = (u8)(Local_u16BaudRate-1);
	UBRRH = (Local_u16BaudRate-1)>>8;

#elif UART_SPEED == UART_DOUBLE_SPEED
	SET_BIT(UCSRA, UCSRA_U2X);
	UBRRL = (u8)(2*Local_u16BaudRate-1);
	UBRRH = (2*Local_u16BaudRate-1)>>8;

#else
#error "Invalid Choice for UART speed"
#endif

#if UART_PARITY == UART_PARITY_DISABLED
	CLR_BIT(Local_u8UCSRC, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC, UCSRC_UPM1);

#elif UART_PARITY == UART_EVEN_PARITY
	CLR_BIT(Local_u8UCSRC, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC, UCSRC_UPM1);

#elif UART_PARITY == UART_ODD_PARITY
	SET_BIT(Local_u8UCSRC, UCSRC_UPM0);
	SET_BIT(Local_u8UCSRC, UCSRC_UPM1);

#else
#error
#endif

#if UART_STOP_BITS == ONE_STOP_BIT
	/* default */
#elif UART_STOP_BITS == TWO_STOP_BITS
	SET_BIT(Local_u8UCSRC, UCSRC_USBS);
#else
#error "Invalid choice for stop bits"
#endif

	UCSRC = Local_u8UCSRC;

	/* Enable Transmission and Reception */
	SET_BIT(UCSRB, UCSRB_RXEN);
	SET_BIT(UCSRB, UCSRB_TXEN);

}

/*------------------------------------------------------------------------------------------------------*/

u8 UART_voidSendCharSync(u8 Copy_u8Char)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32Counter = 0;

	/* Wait until Data register is empty */
	while(!GET_BIT(UCSRA, UCSRA_UDRE) && (Local_u32Counter != UART_TIMEOUT))
	{
		Local_u32Counter++;
	}

	if (Local_u32Counter < UART_TIMEOUT)
	{
		/* Copy the character into the data register */
		UDR = Copy_u8Char;
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}

/*------------------------------------------------------------------------------------------------------*/

u8 UART_u8ReceiveCharSync(u8* Copy_pu8Character)
{
	u8 Local_u32ErrorState = OK;
	u32 Local_u32Counter = 0;

	/* Wait until reception is complete */
	while(GET_BIT(UCSRA, UCSRA_RXC) && (Local_u32Counter != UART_TIMEOUT))
	{
		Local_u32Counter++;
	}

	if (Local_u32Counter < UART_TIMEOUT) {*Copy_pu8Character = UDR;}		/* Read the data register */

	else {Local_u32ErrorState = NOK;}

	return Local_u32ErrorState;
}

/*------------------------------------------------------------------------------------------------------*/

u8 UART_voidSendCharAsync(u8 Copy_u8Char, void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if (Global_u8UARTState == UART_IDLE)
	{
		if (Copy_pvNotificationFunc != NULL)
		{
			/* Change UART state to busy so it can't be used before it is ready again */
			Global_u8UARTState = UART_BUSY;

			/* Copy value to global pointer to be accessed in ISR */
			Global_u8Char2Transmit = Copy_u8Char;

			/* Set the Callback Function */
			UART_pvCallbackFunctions[TXC_INTERRUPT] = Copy_pvNotificationFunc;

			/* Identify Source of UDRE Interrupt */
			Global_u8UDRIntSource = SEND_CHAR_ASYNC;

			/* Enable the "USART Data Register Empty" Interrupt */
			SET_BIT(UCSRB, UCSRB_UDRIE);
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

/*------------------------------------------------------------------------------------------------------*/

u8 UART_u8ReceiveCharAsync(u8* Copy_pu8Char, void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if (Global_u8UARTState == UART_IDLE)
	{
		if ((Copy_pu8Char != NULL) && (Copy_pvNotificationFunc != NULL))
		{
			/* Change UART state to busy so it can't be used before it is ready again */
			Global_u8UARTState = UART_BUSY;

			/* Use global pointer to be accessed in ISR */
			Global_pu8ReceivedChar = Copy_pu8Char;

			/* Set the Callback Function */
			UART_pvCallbackFunctions[RXC_INTERRUPT] = Copy_pvNotificationFunc;

			/* Identify Source of RXC Interrupt */
			Global_u8RxIntSource = RECEIVE_CHAR_ASYNC;

			/* Enable the Receive Complete Interrupt */
			SET_BIT(UCSRB, UCSRB_RXCIE);
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

/*------------------------------------------------------------------------------------------------------*/

u8 UART_u8SendStrSync(const char* Copy_pcData)
{
	u8 Local_u8ErrorStatus = OK;
	u16 Local_u16Index = 0;

	if (Copy_pcData != NULL)
	{
		/* loop until end of string */
		while(*Copy_pcData != '\0')
		{
			/* Send characters successively */
			Local_u8ErrorStatus = UART_voidSendCharSync(Copy_pcData[Local_u16Index++]);

			if(Local_u8ErrorStatus == NOK) return Local_u8ErrorStatus;
		}
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------*/

u8 UART_u8ReceiveBufferSync(u16 Copy_u16BufferSize, u8* Copy_pu8DataBuffer)
{
	u8 Local_u8ErrorStatus = OK;
	u16 Local_u16Iterator;

	if (Copy_pu8DataBuffer != NULL)
	{
		for(Local_u16Iterator = 0; Local_u16Iterator < Copy_u16BufferSize; Local_u16Iterator++)
		{
			/* Receive characters successively */
			Local_u8ErrorStatus = UART_u8ReceiveCharSync(&Copy_pu8DataBuffer[Local_u16Iterator]);

			if(Local_u8ErrorStatus == NOK) return Local_u8ErrorStatus;
		}
	}
	else
	{
		Local_u8ErrorStatus = NULL_PTR;
	}

	return Local_u8ErrorStatus;
}

/*------------------------------------------------------------------------------------------------------*/

u8 UART_u8SendStrAsync(const char* Copy_pcData, void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if (Global_u8UARTState == UART_IDLE)
	{
		if ((Copy_pcData != NULL) && (Copy_pvNotificationFunc != NULL))
		{
			/* Change UART state to busy so it can't be used before it is ready again */
			Global_u8UARTState = UART_BUSY;

			/* Use global pointer to be accessed in ISR */
			Global_pcTxStr = Copy_pcData;

			/* Initialize the transmitted string index */
			Global_u16TxChainIndex = 0;

			/* Assign the notification function to the USART Transmission Complete ISR */
			UART_pvCallbackFunctions[TXC_INTERRUPT] = Copy_pvNotificationFunc;

			/* Identify Source of UDRE Interrupt */
			Global_u8UDRIntSource = RECEIVE_STR_ASYNC;

			/* Enable the Data Register Empty Interrupt */
			SET_BIT(UCSRB, UCSRB_UDRIE);
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

/*------------------------------------------------------------------------------------------------------*/

u8 UART_u8ReceiveBufferAsync(u8* Copy_pu8DataBuffer, u16 Copy_u16BufferSize, void (*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorStatus = OK;

	if (Global_u8UARTState == UART_IDLE)
	{
		if ((Copy_pu8DataBuffer != NULL) && (Copy_pvNotificationFunc != NULL))
		{
			Global_u8UARTState = UART_BUSY;

			Global_pu8ReceivedChar = Copy_pu8DataBuffer;

			Global_u16RxBufferSize = Copy_u16BufferSize;

			Global_u8RxIntSource = RECEIVE_STR_ASYNC;

			/* Set the callback function */
			UART_pvCallbackFunctions[RXC_INTERRUPT] = Copy_pvNotificationFunc;

			/* Initialize the receiving buffer index */
			Global_u16RxChainIndex = 0;

			/* Enable the Receive Complete interrupt */
			SET_BIT(UCSRB, UCSRB_RXCIE);
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


/************ USART Rx Complete ISR ***********/
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{

	if(Global_u8RxIntSource == RECEIVE_CHAR_ASYNC)
	{
		/* Disable RXC Interrupt */
		CLR_BIT(UCSRB, UCSRB_RXCIE);

		/* Read the data register */
		*Global_pu8ReceivedChar = UDR;

		/* Reset the UART state back to idle */
		Global_u8UARTState = UART_IDLE;

		/* Call the notification function if provided */
		if (UART_pvCallbackFunctions[RXC_INTERRUPT] != NULL)
		{
			UART_pvCallbackFunctions[RXC_INTERRUPT]();
		}
	}
	else if (Global_u8RxIntSource == RECEIVE_STR_ASYNC)
	{
		/* Read the data register */
		Global_pu8ReceivedChar[Global_u16RxBufferSize++] = UDR;

		if (Global_u16RxChainIndex == Global_u16RxBufferSize)
		{
			/* Disable RXC Interrupt */
			CLR_BIT(UCSRB, UCSRB_RXCIE);

			/* Reset the UART state back to idle */
			Global_u8UARTState = UART_IDLE;

			/* Call the notification function if provided */
			if (UART_pvCallbackFunctions[RXC_INTERRUPT] != NULL)
			{
				UART_pvCallbackFunctions[RXC_INTERRUPT]();
			}
		}
	}

}

/******** USART Data Register Empty ISR ********/
void __vector_14 (void) __attribute__((signal));
void __vector_14 (void)
{
	/* In case sending a single character asynchronously triggered the ISR */
	if(Global_u8UDRIntSource == SEND_CHAR_ASYNC)
	{
		/* Disable UDRE Interrupt */
		CLR_BIT(UCSRB, UCSRB_UDRIE);

		/* Copy the character into the data register */
		UDR = Global_u8Char2Transmit;

		/* Enable Transmission Complete Interrupt */
		SET_BIT(UCSRB, UCSRB_TXCIE);

	}

	/* In case sending a string asynchronously triggered the ISR */
	else if (Global_u8UDRIntSource == SEND_STR_ASYNC)
	{
		/* Copy characters successively into the data register */
		UDR = Global_pcTxStr[Global_u16TxChainIndex];

		if (Global_pcTxStr[Global_u16TxChainIndex] == '\0')  //end of string
		{
			/* Disable UDRE Interrupt */
			CLR_BIT(UCSRB, UCSRB_UDRIE);

			/* Enable Transmission Complete Interrupt */
			SET_BIT(UCSRB, UCSRB_TXCIE);
		}
		else
		{
			Global_u16TxChainIndex++;
		}
	}
}

/************ USART Tx Complete ISR ***********/
void __vector_15 (void) __attribute__((signal));
void __vector_15 (void)
{
	/* In case sending a single character asynchronously triggered the ISR */
	if(Global_u8UDRIntSource == SEND_CHAR_ASYNC)
	{
		/* Disable Transmission Complete Interrupt */
		CLR_BIT(UCSRB, UCSRB_TXCIE);

		/* Indicate UART is back to idle state and can be used again */
		Global_u8UARTState = UART_IDLE;

		/* Call the notification function if given */
		if (UART_pvCallbackFunctions[TXC_INTERRUPT] != NULL)
		{
			UART_pvCallbackFunctions[TXC_INTERRUPT]();
		}
	}

	/* In case sending a string asynchronously triggered the ISR */
	else if (Global_u8UDRIntSource == SEND_STR_ASYNC)
	{
		/* Disable Transmission Complete Interrupt */
		CLR_BIT(UCSRB, UCSRB_TXCIE);

		/* Indicate UART is back to idle state and can be used again */
		Global_u8UARTState = UART_IDLE;

		/* Call the notification function if given */
		if (UART_pvCallbackFunctions[TXC_INTERRUPT] != NULL)
		{
			UART_pvCallbackFunctions[TXC_INTERRUPT]();
		}
	}
}
