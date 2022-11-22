
#ifndef MCAL_TIMER_TIM_PRIVATE_H_
#define MCAL_TIMER_TIM_PRIVATE_H_


#define TIMER0_MODE_MASK		0b10110111
#define TIM0_NORMAL             0
#define TIM0_PWM                0b01000000
#define TIM0_CTC                0b00001000
#define TIM0_FAST_PWM           0b01001000


#define TIMER1_MODE_MASK							0xfce7
#define TIM1_NORMAL             					0xfce7
#define TIM1_PWM_PHASE_CORRECT_8BIT                 0xfde7
#define TIM1_PWM_PHASE_CORRECT_9BIT                 0xfee7
#define TIM1_PWM_PHASE_CORRECT_10BIT                0xffe7
#define TIM1_CTC_OCR1A_TOP         					0xfcef
#define TIM1_FAST_PWM_8BIT         					0xfdef
#define TIM1_FAST_PWM_9BIT         					0xfeef
#define TIM1_FAST_PWM_10BIT        					0xffef
#define TIM1_PWM_PHASE_FREQ_CORRECT_ICR1_TOP        0xfcf7
#define TIM1_PWM_PHASE_FREQ_CORRECT_OCR1A_TOP       0xfdf7
#define TIM1_PWM_PHASE_CORRECT_ICR1_TOP             0xfef7
#define TIM1_PWM_PHASE_CORRECT_OCR1A_TOP            0xfff7
#define TIM1_CTC_ICR1_TOP         					0xfcff
#define TIM1_FAST_PWM_ICR1_TOP          		    0xfeff
#define TIM1_FAST_PWM_OCR1A_TOP         		    0xffff




/* Timer 1 Channel A Compare Output Modes in case of fast PWM */
#define OC1A_MODE_MASK          0b00111111
#define OC1A_DISCONNECTED       0b00111111
#define OC1A_TOGGLE_PIN         0b01111111
#define OC1A_NONINVERTING       0b10111111
#define OC1A_INVERTING          0b11111111

#define TIM0_CLK_MASK			0b11111000

typedef enum
{
	TIM_NO_CLOCK             ,
    TIM_DIV_BY_1             ,
    TIM_DIV_BY_8             ,
    TIM_DIV_BY_64            ,
    TIM_DIV_BY_256           ,
    TIM_DIV_BY_1024          ,
    TIM_EXTERNAL_FALLING_EDGE,
    TIM_EXTERNAL_RISING_EDGE
}TIM_CLK_SELECT_t;

#define TIM_CONC(b7,b6,b5,b4,b3,b2,b1,b0)					TIM_CONC_HELPER(b7,b6,b5,bb4,b3,b2,b1,b0)
#define TIM_CONC_HELPER(b7,b6,b5,bb4,b3,b2,b1,b0)			0b##b7##b6##b5##b4##b3##b2##b1##b0



#endif
