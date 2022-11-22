
#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_

/*
 * Options:
 *			USART_SYNCHRONOUS
 *			USART_ASYNCHRONOUS
 */
#define USART_MODE					USART_ASYNCHRONOUS

/*
 * Options:
 * 			BAUD_RATE_2400
 * 			BAUD_RATE_4800
 * 			BAUD_RATE_9600
 * 			BAUD_RATE_14400
 */
#define UART_BAUD_RATE              BAUD_RATE_9600

/*
 * Options:
 *			UART_PARITY_DISABLED
 *			UART_EVEN_PARITY
 *			UART_ODD_PARITY
 */
#define UART_PARITY					UART_PARITY_DISABLED

/*
 * Options:
 * 			ONE_STOP_BIT
 * 			TWO_STOP_BITS
 */
#define UART_STOP_BITS				ONE_STOP_BIT

/*
 * Options:
 * 			UART_NORMAL_SPEED
 * 			UART_DOUBLE_SPEED
 */
#define UART_SPEED					UART_NORMAL_SPEED

/**
 * Options:
 * 			ENABLE
 * 			DISABLE
 */
#define MULTI_PROCESSOR_COMM		DISABLE

#endif
