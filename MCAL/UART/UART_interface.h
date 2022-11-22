
#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

void UART_voidInit(void);

u8 UART_voidSendCharSync(u8 Copy_u8Char);

u8 UART_u8ReceiveCharSync(u8* Copy_pu8Character);

u8 UART_voidSendCharAsync(u8 Copy_u8Char, void (*Copy_pvNotificationFunc)(void));

u8 UART_u8ReceiveCharAsync(u8* Copy_pu8Char, void (*Copy_pvNotificationFunc)(void));

u8 UART_u8SendStrSync(const char* Copy_pcData);

u8 UART_u8ReceiveBufferSync(u16 Copy_u16BufferSize, u8* Copy_pu8DataBuffer);

u8 UART_u8SendStrAsync(const char* Copy_pcData, void (*Copy_pvNotificationFunc)(void));

u8 UART_u8ReceiveBufferAsync(u8* Copy_pu8DataBuffer, u16 Copy_u16BufferSize, void (*Copy_pvNotificationFunc)(void));

//u8 UART_u8CallbackFunction(void (*Copy_pvFunc)(void));

#endif
