
#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

/* ADC Resolution Options */
#define RES_8_BITS			              8
#define RES_10_BITS			              10

/* ADC Reference Options */
#define AREF                              0b00111111
#define AVCC                              0b01111111
#define INTERNAL_2P56                     0b11111111

/* ADC Auto Trigger Signal Options */
#define FREE_RUNNING	                  0b00011111
#define ANALOG_COMPARATOR                 0b00111111
#define EXTI0_REQUEST	                  0b01011111
#define TIM0_CMPRE_MTCH	                  0b01111111
#define TIM0_OVRFLW		                  0b10011111
#define TIM_CMPRE_MTCH_B                  0b10111111
#define TIM1_OVRFLW		                  0b11011111
#define TIM1_CAPTURE		              0b11111111

/* ADC states */
#define ADC_IDLE				              0
#define ADC_BUSY				              1

#define ASYNC_CHAIN_CONVERSION            0
#define ASYNC_SINGLE_CONVERSION           1

typedef enum
{
	DIV_BY_2 = 1  ,
	DIV_BY_4  ,
	DIV_BY_8  ,
	DIV_BY_16 ,
	DIV_BY_32 ,
	DIV_BY_64 ,
	DIV_BY_128
}Prescaler_t;


#endif
