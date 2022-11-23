
#include "../LIB/STD_TYPES.h"

#include "../MCAL/TIMER/TIM_interface.h"
#include "../MCAL/GIE/GIE_interface.h"

#include "RTOS_interface.h"
#include "RTOS_private.h"
#include "RTOS_config.h"

Task_t TaskArr[TASK_NUM] = {{NULL}};

void RTOS_voidStart(void)
{
	TIM_u8SetCallback(TIM0_COMPARE_MATCH, &voidScheduler);

	/* Enable Global Interrupt */
	GIE_voidEnable();

	TIM0_voidInit();
}

void RTOS_voidCreateTask(u8 Copy_u8Priority, u16 Copy_u16Periodicity, u16 Copy_u16FirstDelay, void (*Copy_pvTaskFuction)(void))
{
	TaskArr[Copy_u8Priority].Periodicity = Copy_u16Periodicity;
	TaskArr[Copy_u8Priority].pvTaskFunction = Copy_pvTaskFuction;
	TaskArr[Copy_u8Priority].State = TASK_ACTIVE;
}

static void voidScheduler(void)
{
	u8 Local_u8TaskCounter;

	for(Local_u8TaskCounter=0; Local_u8TaskCounter<TASK_NUM; Local_u8TaskCounter++)
	{
		if (TaskArr[Local_u8TaskCounter].State == TASK_ACTIVE)
		{
			if (TaskArr[Local_u8TaskCounter].FirstDelay == 0)
			{

				if (TaskArr[Local_u8TaskCounter].pvTaskFunction != NULL)
				{
					TaskArr[Local_u8TaskCounter].pvTaskFunction();
				}

				/* After the first delay is over, assign it the periodicity value - 1 */
				TaskArr[Local_u8TaskCounter].FirstDelay = TaskArr[Local_u8TaskCounter].Periodicity-1;
			}
			else
			{
				TaskArr[Local_u8TaskCounter].FirstDelay--;
			}
		}
		else
		{
			/* Do Nothing */
		}
	}
}

void RTOS_voidSuspendTask(u8 Copy_u8Priority)
{
	TaskArr[Copy_u8Priority].State = TASK_SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority)
{
	TaskArr[Copy_u8Priority].State = TASK_ACTIVE;
}

void RTOS_voidDeleteTask(u8 Copy_u8Priority)
{
	TaskArr[Copy_u8Priority].pvTaskFunction = NULL;
}

