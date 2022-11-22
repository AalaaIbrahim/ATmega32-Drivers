
#ifndef HAL_SW_SW_INTERFACE_H_
#define HAL_SW_SW_INTERFACE_H_


typedef struct
{
	u8 Port;
	u8 Pin;
	u8 PullType;
	u8 SelfLocking;
}SW_t;

typedef enum
{
	SW_PullUp,
	SW_PullDown,
}SW_Pull_t;

typedef enum
{
	SW_NotPressed,
	SW_Pressed,
}SW_State;


u8 SW_u8ReadSwitch(SW_t* Copy_pSW_tSwitch, u8* Copy_pu8SwitchState);

#endif
