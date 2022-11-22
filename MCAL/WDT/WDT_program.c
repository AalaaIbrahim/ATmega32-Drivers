
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "WDT_private.h"
#include "WDT_interface.h"
#include "WDT_register.h"

void WDT_voidSleep(u8 Copy_u8SleepTime)
{
	/* Clear the prescaler bits */
	WDTCR &= 0b11111000;

	/* Set the required prescaler */
	WDTCR |= Copy_u8SleepTime;
}

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR, WDTCR_WDE);
}

void WDT_voidDisable(void)
{
	/* write a logic one to WDE and WDTOE bits in the same operation */
	WDTCR |= 0b00011000;

	/* clear wde bit */
	WDTCR = 0;
}
