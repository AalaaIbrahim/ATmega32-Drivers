
#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

/* EXTI Sense Control Options */
#define LOW_LEVEL            0b00
#define ON_CHANGE            0b01
#define FALLING_EDGE         0b10
#define RISING_EDGE          0b11

/* EXTI Sense Control bit Masks */
#define EXTI0_SENSE_MASK		 0b11111100
#define EXTI1_SENSE_MASK		 0b11110011

#endif
