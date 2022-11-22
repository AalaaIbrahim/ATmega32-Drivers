
#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

typedef enum
{
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2
}EXTI_INT_t;

typedef enum
{
	LOW_LEVEL,
	ON_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}EXTI_SenseMode_t;


/*              Function Prototypes           */

void EXTI_voidInt0Init(void);
void EXTI_voidInt1Init(void);
void EXTI_voidInt2Init(void);

u8 EXTI_u8SetSense(u8 Copy_u8IntNumber, u8 Copy_u8SenseMode);
u8 EXTI_u8EnableInt(u8 Copy_u8IntNumber);
u8 EXTI_u8DisableInt(u8 Copy_u8IntNumber);

u8 EXTI_u8SetCallbackFn(u8 Copy_u8IntNumber, void (*Copy_pvFunction)(void));

#endif
