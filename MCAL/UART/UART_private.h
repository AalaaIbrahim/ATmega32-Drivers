
#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#define UART_OSC_FREQ					 8000000UL

#define UART_TIMEOUT					 100000

/* UART Mode Select options */
#define USART_SYNCHRONOUS                4
#define USART_ASYNCHRONOUS               5

/* UART Frame parity options */
#define UART_PARITY_DISABLED             1
#define UART_EVEN_PARITY                 2
#define UART_ODD_PARITY                  3

/* UART Frame stop bits options */
#define ONE_STOP_BIT                     1
#define TWO_STOP_BITS                    2

/* UART Baud Rate options */
#define BAUD_RATE_2400                   2400
#define BAUD_RATE_4800                   4800
#define BAUD_RATE_9600                   9600
#define BAUD_RATE_14400                  14400

typedef enum
{
	UART_IDLE,
	UART_BUSY
}UART_STATE_t;

typedef enum
{
	RXC_INTERRUPT,
	UDRE_INTERRUPT,
	TXC_INTERRUPT
}UART_Interrupts_t;

typedef enum
{
	SEND_CHAR_ASYNC,
	SEND_STR_ASYNC
}UART_UDRE_Inerrupt_Sources_t;

typedef enum
{
	RECEIVE_CHAR_ASYNC,
	RECEIVE_STR_ASYNC
}UART_RXC_Inerrupt_Sources_t;

#endif
