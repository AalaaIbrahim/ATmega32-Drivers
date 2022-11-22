/*
 * TIM_register.h
 *
 *  Created on: Sep 20, 2022
 *      Author: ME
 */

#ifndef MCAL_TIMER_TIM_REGISTER_H_
#define MCAL_TIMER_TIM_REGISTER_H_


/******************* Timer 0 ***********************/
#define  TCCR0                    *((volatile u8*)0x53)
#define  TCCR0_WGM00				6			/* waveform generation mode bit 0 */
#define  TCCR0_WGM01				3
#define  TCCR0_CS02					2			/* prescaler bit 2 */
#define  TCCR0_CS01					1
#define  TCCR0_CS00					0

#define  OCR0                     *((volatile u8*)0x5c)			/* Output compare register */

#define  TIMSK                    *((volatile u8*)0x59)
#define  TIMSK_TOIE0				0
#define  TIMSK_OCIE0				1							/* Output compare 0 interrupt enable */
#define  TIMSK_TOIE1                2
#define  TIMSK_OCIE1B               3
#define  TIMSK_OCIE1A               4
#define  TIMSK_TICIE1				5							/* input capture interrupt enable */
#define  TIMSK_TOIE2                6
#define  TIMSK_OCIE2                7


/******************* Timer 1 ***********************/
#define  TCCR1                     *((volatile u16*)0x4e)
#define  TCCR1A                    *((volatile u8*)0x4f)
#define  TCCR1B                    *((volatile u8*)0x4e)
#define  TCCR1A_WGM10				0			/* waveform generation mode bit 0 */
#define  TCCR1A_WGM11				1
#define  TCCR1A_COM1A0				6				/* prescaler bit 2 */
#define  TCCR1A_COM1A1				7

#define  TCCR1B_ICRS1				6				/* Input capture edge select */
#define  TCCR1B_WGM13				4
#define  TCCR1B_WGM12				3

#define  ICR1                      *((volatile u16*)0x46)

#define  OCR1A                     *((volatile u16*)0x4a)			/* Output compare register */

#define  TCNT1					   *((volatile u16*)0x4c)
//#define  TIMSK                    *((volatile u8*)0x59)
//#define  TIMSK_OCIE0				1                           /* Output compare 0 interrupt enable */

#endif /* MCAL_TIMER_TIM_REGISTER_H_ */
