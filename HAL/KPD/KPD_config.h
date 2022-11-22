
#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_

#define	KPD_PORT		DIO_PORT_B

/* Keypad column pins */
#define KPD_COL1        DIO_PIN_0
#define KPD_COL2        DIO_PIN_1
#define KPD_COL3        DIO_PIN_2
#define KPD_COL4        DIO_PIN_3

/* Keypad row pins */
#define KPD_ROW1        DIO_PIN_4
#define KPD_ROW2        DIO_PIN_5
#define KPD_ROW3        DIO_PIN_6
#define KPD_ROW4        DIO_PIN_7

#define KEYPAD			{{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','='},{'*','0','#','A'}}

#endif
