
#ifndef MCAL_UART_UART_REGISTER_H_
#define MCAL_UART_UART_REGISTER_H_

#define  UDR                       *((volatile u8*)0x2C)   /** USART I/O Data Register **/

#define  UCSRA                     *((volatile u8*)0x2B)   /** USART Control and Status Register A **/
#define  UCSRA_RXC                 7                       /* UART Receive Complete Bit */
#define  UCSRA_TXC                 6                       /* UART Transmit Complete Bit */
#define  UCSRA_UDRE                5                       /* UART Data Register Empty Bit */
#define  UCSRA_FE                  4                       /* Frame Error Bit */
#define  UCSRA_DOR                 3                       /* Data Overrun Bit */
#define  UCSRA_PE                  2                       /* Parity Error Bit */
#define  UCSRA_U2X                 1                       /* Double UART Transmission Speed */
#define  UCSRA_MPCM                0                       /* Multi-Processor Communication Mode*/


#define  UCSRB                     *((volatile u8*)0x2A)   /** USART Control and Status Register B **/
#define  UCSRB_RXCIE               7                       /* Rx Complete Interrupt Enable bit */
#define  UCSRB_TXCIE               6                       /* Tx Complete Interrupt Enable bit */
#define  UCSRB_UDRIE               5                       /* UART Data Register Empty Interrupt Enable bit */
#define  UCSRB_RXEN                4                       /* Receiver Enable bit */
#define  UCSRB_TXEN                3                       /* Transmitter Enable bit */
#define  UCSRB_UCSZ2               2                       /* Character Size */
#define  UCSRB_RXB8                1                       /* Receive Data Bit 8 */
#define  UCSRB_TXB8                0                       /* Transmit Data Bit 8 */


#define  UCSRC                     *((volatile u8*)0x40)   /** USART Control and Status Register C **/
#define  UCSRC_URSEL               7                       /*  */
#define  UCSRC_UMSEL               6                       /*  */
#define  UCSRC_UPM1                5                       /*  */
#define  UCSRC_UPM0                4                       /*  */
#define  UCSRC_USBS                3                       /*  */
#define  UCSRC_UCSZ1               2                       /*  */
#define  UCSRC_UCSZ0               1                       /*  */
#define  UCSRC_UCPOL               0                       /*  */


#define  UBRRH                     *((volatile u8*)0x40)	/** USART Baud Rate Register High **/
#define  UBRRL                     *((volatile u8*)0x29)	/** USART Baud Rate Register Low **/

#endif /* MCAL_UART_UART_REGISTER_H_ */
