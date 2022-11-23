
#ifndef RTOS_RTOS_PRIVATE_H_
#define RTOS_RTOS_PRIVATE_H_

typedef struct
{
	u8 State;
	u16 FirstDelay;
	u16 Periodicity;
	void (*pvTaskFunction)(void);
}Task_t;

#define TASK_ACTIVE				0
#define TASK_SUSPENDED			1

static void voidScheduler(void);

#endif
