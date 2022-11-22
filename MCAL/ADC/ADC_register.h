
#ifndef MCAL_ADC_ADC_REGISTER_H_
#define MCAL_ADC_ADC_REGISTER_H_

#define ADMUX                *((volatile u8*) 0x27)           /* ADC Multiplexer Selection Register */
#define ADMUX_ADLAR			 5                                /* ADC Left Adjust Result bit */

#define ADCSRA               *((volatile u8*) 0x26)           /* ADC Control and Status Register A */
#define ADCSRA_ADEN          7                                /* ADC Enable bit */
#define ADCSRA_ADSC          6                                /* ADC Start Conversion bit */
#define ADCSRA_ADATE         5                                /* ADC Auto Trigger Enable bit */
#define ADCSRA_ADIF			 4                                /* ADC Interrupt Flag */
#define ADCSRA_ADIE          3                                /* ADC Interrupt Enable bit */


#define ADCH                 *((volatile u8*) 0x25)           /* ADC Data Register - Low */
#define ADC_LH               *((volatile u16*) 0x24)          /* ADC Data Register - Low and High */

#define SFIOR				 *((volatile u8*) 0x50)           /* Special Function IO Register */

#endif
