
#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

/*
 * Options:
 *         DIO_PORT_A
 *         DIO_PORT_B
 *         DIO_PORT_C
 *         DIO_PORT_D
 */
#define LCD_DATA_PORT		DIO_PORT_C
#define LCD_CONTROL_PORT	DIO_PORT_A


/*************************************
 * Options:
 *         DIO_PIN_0
 *         DIO_PIN_1
 *         DIO_PIN_2
 *         DIO_PIN_3
 *         DIO_PIN_4
 *         DIO_PIN_5
 *         DIO_PIN_6
 *         DIO_PIN_7
 *************************************/
#define LCD_RS_PIN         DIO_PIN_5
#define LCD_RW_PIN         DIO_PIN_6
#define LCD_E_PIN          DIO_PIN_7


/****************************************
 *      Options:
 * 		                   LCD_DATA_4BIT
 * 		                   LCD_DATA_8BIT
 *
 ****************************************/
#define LCD_DATA_LEN       LCD_DATA_8BIT


/****************************************
 * Options:
 * 		   LCD_ONE_LINE
 * 		   LCD_TWO_LINE
 ****************************************/
#define LCD_LINE_NUM       LCD_TWO_LINE


/*
 * Options:
 * 		   LCD_5_7
 * 		   LCD_5_10
 */
#define LCD_FONT	       LCD_5_7


#endif
