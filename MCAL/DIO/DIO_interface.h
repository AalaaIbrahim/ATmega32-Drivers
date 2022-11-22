
#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_

#define DIO_PORT_IN		0x0
#define DIO_PORT_OUT	0xff

#define DIO_PORT_LOW	0x0
#define DIO_PORT_HIGH	0xff

typedef enum
{
	DIO_PORT_A,
	DIO_PORT_B,
	DIO_PORT_C,
	DIO_PORT_D
}Port_t;

typedef enum
{
	DIO_PIN_0,
	DIO_PIN_1,
	DIO_PIN_2,
	DIO_PIN_3,
	DIO_PIN_4,
	DIO_PIN_5,
	DIO_PIN_6,
	DIO_PIN_7
}Pin_t;

typedef enum
{
	DIO_PIN_IN,
	DIO_PIN_OUT
}PinDirection_t;

typedef enum
{
	DIO_PIN_LOW,
	DIO_PIN_HIGH
}PinValue_t;

/**
 * @def function to configure a single DIO pin as input/output
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Pin the pin number in the given port
 * @return error status
 */
u8 DIO_u8SetPinDir(u8 Copy_u8Port,u8 Copy_u8Pin, u8 Copy_u8Dir);

/**
 * @def function to configure an entire DIO port as input/output
 * @param Copy_u8Port the required port
 * @param Copy_u8Dir the desired direction whether input or output
 * @return error status
 */
u8 DIO_u8SetPortDir(u8 Copy_u8Port, u8 Copy_u8Dir);

/**
 * @def function to configure a single DIO pin as input/output
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Pin the pin number in the given port
 * @param Copy_u8Value desired value (high or low) to set the pin to
 * @return error status
 */
u8 DIO_u8SetPinVal(u8 Copy_u8Port,u8 Copy_u8Pin, u8 Copy_u8Value);

/**
 * @def function to configure a single DIO pin as input/output
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Pin the pin number in the given port
 * @param Copy_u8Value desired value (high or low) to set the entire port to
 * @return error status
 */
u8 DIO_u8SetPortVal(u8 Copy_u8Port, u8 Copy_u8Value);

/**
 * @def function to get the value of a single DIO pin whether high or low
 * @param Copy_u8Port the port of the required pin
 * @param Copy_u8Pin the pin number in the given port
 * @param Copy_pu8Val pointer to a variable to store pin value (0-255)
 * @return error status
 */
u8 DIO_u8GetPinVal(u8 Copy_u8Port,u8 Copy_u8Pin, u8* Copy_pu8Val);
u8 DIO_u8TogglePin(u8 Copy_u8Port,u8 Copy_u8Pin);

#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
