
#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

typedef enum
{
	ADC0_SINGLE_ENDED,
	ADC1_SINGLE_ENDED,
	ADC2_SINGLE_ENDED,
	ADC3_SINGLE_ENDED,
	ADC4_SINGLE_ENDED,
	ADC5_SINGLE_ENDED,
	ADC6_SINGLE_ENDED,
	ADC7_SINGLE_ENDED,

	/* Differential Channels */
	ADC0_ADC0_10X,
	ADC1_ADC0_10X,
	ADC0_ADC0_200X,
	ADC1_ADC0_200X,
	ADC2_ADC2_10X,
	ADC3_ADC2_10X,
	ADC2_ADC2_200X,
	ADC3_ADC2_200X,
	ADC0_ADC1,
	ADC1_ADC1,
	ADC2_ADC1,
	ADC3_ADC1,
	ADC4_ADC1,
	ADC5_ADC1,
	ADC6_ADC1,
	ADC7_ADC1,
	ADC0_ADC2,
	ADC1_ADC2,
	ADC2_ADC2,
	ADC3_ADC2,
	ADC4_ADC2,
	ADC5_ADC2,
	/*************************/

    VBG_SINGLE_ENDED,
	GND_SINGLE_ENDED
}ADC_CHANNEL_t;

typedef struct
{
	u8* ChannelArray;
	u8* ResultArray;
	u8 ChainSize;
	void (*NotificationFunction)(void);
}Chain_t;

/************** Function Prototypes **************/
void ADC_voidInit(void);

u16 ADC_u8GetChannelReading(u8 Copy_u8Channel);

u8 ADC_u8StartConversionAsync(u8 Copy_u8Channel, u8* Copy_pu8Reading, void (*Copy_pvNotificationCallback)(void));

u8 ADC_u8StartChainAsync(Chain_t *Copy_chain);

u8 ADC_u8SetCallback(void (*Copy_pvFunction)(void));

#endif
