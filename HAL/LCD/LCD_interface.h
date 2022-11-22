
#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_

typedef enum {LCD_LINE_ONE, LCD_LINE_TWO} LCD_LINE_POS;

u8 LCD_u8Init(void);
u8 LCD_u8SendData(u8 Copy_u8Data);
u8 LCD_u8GoToXY(u8 Copy_u8XPosition, u8 Copy_u8YPosition);
u8 LCD_u8WriteStr(const char* Copy_pcData);
u8 LCD_u8WriteSineWave(const char* Copy_pcData);
u8 LCD_u8WriteSpecialChar(u8* Copy_pu8SpecialChar, u8 Copy_u8Location);
u8 LCD_u8WriteNumber(u32 Copy_u32Number);

#endif
