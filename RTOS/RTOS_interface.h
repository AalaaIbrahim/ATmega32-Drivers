
#ifndef RTOS_RTOS_INTERFACE_H_
#define RTOS_RTOS_INTERFACE_H_

void RTOS_voidStart(void);

void RTOS_voidCreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, u16 Copy_u16FirstDelay, void (*Copy_pvTaskFuction)(void));

void RTOS_voidSuspendTask(u8 Copy_u8Priority);

void RTOS_voidResumeTask(u8 Copy_u8Priority);

void RTOS_voidDeleteTask(u8 Copy_u8Priority);

#endif
