
#ifndef MCAL_EXTI_EXTI_CONFIG_H_
#define MCAL_EXTI_EXTI_CONFIG_H_

/*
 * Options:
 * 			LOW_LEVEL
 * 			ON_CHANGE
 * 			FALLING_EDGE
 * 			RISING_EDGE
 */
#define INT0_SENSE		RISING_EDGE
#define INT1_SENSE		FALLING_EDGE

/*
 * Options:
 * 			FALLING_EDGE
 * 			RISING_EDGE
 */
#define INT2_SENSE		FALLING_EDGE

/*
 * EXTIs initial state
 * Options:
 * 			EXTI_ENABLE
 * 			EXTI_DISABLE
 */
#define EXTI0_STATE     EXTI_DISABLE
#define EXTI1_STATE     EXTI_DISABLE
#define EXTI2_STATE     EXTI_DISABLE

#endif
