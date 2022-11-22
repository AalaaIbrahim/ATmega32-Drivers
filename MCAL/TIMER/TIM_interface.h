
#ifndef MCAL_TIMER_TIM_INTERFACE_H_
#define MCAL_TIMER_TIM_INTERFACE_H_

typedef enum
{
	ICU_RISING_EDGE,
	ICU_FALLING_EDGE
}Trigger_t;

typedef enum
{
	TIM2_COMPARE_MATCH			,
	TIM2_OVERFLOW				,
	TIM1_CAPTURE_EVENT			,
	TIM1_COMPARE_MATCH_CHANNEL_A,
	TIM1_COMPARE_MATCH_CHANNEL_B,
	TIM1_OVERFLOW				,
	TIM0_COMPARE_MATCH			,
	TIM0_OVERFLOW
}Timer_Interrupts_t;

typedef enum
{
	TIM_INTERRUPT_ENABLE,
	TIM_INTERRUPT_DISABLE
}Timer_Interrupt_State_t;

void TIM0_voidInit(void);

void TIM0_voidSetCompareMatchValue(u8 Copy_u8Value);

void TIM1_voidInit(void);

void TIM1_voidChannelACompareMatchValue(u16 Copy_u16Value);

void TIM1_voidSetICRValue(u16 Copy_u16Value);

void TIM_voidSetTimer1Value(u16 Copy_u16Value);

u16 TIM_voidGetTimer1Value(void);

u8 ICU_voidSetTriggerEdge (u8 Copy_u8Edge);

void ICU_voidEnableInterrupt (void);
void ICU_voidDisableInterrupt (void);

u16 ICU_u16ReadInputCapture (void);


u8 TIM_u8SetInterruptState(u8 Copy_u8InterruptID, u8 Copy_u8InterruptState);
u8 TIM_u8SetCallback(u8 Copy_u8InterruptID, void (*Copy_pvCallbackFunction)(void));

#endif
