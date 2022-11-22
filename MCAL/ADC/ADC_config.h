
#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/*
 * Options:
 * 			AREF
 * 			AVCC
 * 			INTERNAL_2P56
 */
#define ADC_REFERENCE			AVCC

/*
 * Options:
 * 			RES_8_BITS
 * 			RES_10_BITS
 */
#define ADC_RESOLUTION			RES_8_BITS

/*
 * Options:
 * 			DIV_BY_2
 * 			DIV_BY_4
 * 			DIV_BY_8
 * 			DIV_BY_16
 * 			DIV_BY_32
 * 			DIV_BY_64
 * 			DIV_BY_128
 *
 */
#define ADC_PRESCALER			DIV_BY_128

/*
 * Options:
 * 			ENABLE
 * 			DISABLE
 */
#define ADC_AUTO_TRIG			DISABLE

/* Choose signal to automatically trigger the ADC if ADC_AUTO_TRIG is enabled
 * Options:
 * 			FREE_RUNNING
 * 			ANALOG_COMPARATOR
 * 			EXTI0_REQUEST
 * 			TIM0_CMPRE_MTCH
 * 			TIM0_OVRFLW
 * 			TIM_CMPRE_MTCH_B
 * 			TIM1_OVRFLW
 *          TIM1_CAPTURE
 */
#define ADC_TRIGGER_SIGNAL		FREE_RUNNING

/*
 * Options:
 * 			ENABLE
 * 			DISABLE
 */
#define ADC_INTERRUPT			DISABLE

#endif
