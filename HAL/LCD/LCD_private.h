
#ifndef HAL_LCD_LCD_PRIVATE_H_
#define HAL_LCD_LCD_PRIVATE_H_


/************** LCD initialization commands ***************/
#define	 LCD_DISPLAY_CTRL			0X01
#define	 LCD_FUNCTION_SET			0X01
#define	 LCD_SET_ENTRY_MODE			0X01
#define	 LCD_DISPLAY_CLR			0X01



typedef enum
{
	LCD_DATA_4BIT,
	LCD_DATA_8BIT
}LCD_DATA_LEN_t;

typedef enum
{
	LCD_ONE_LINE,
	LCD_TWO_LINE
}LCD_LINE_NUM_t;

typedef enum
{
	LCD_5_7,
	LCD_5_10
}LCD_FONT_t;

static u8 LCD_u8SendCmd(u8 Copy_u8Command);

#endif
