
#ifndef HAL_SSD_SSD_INTERFACE_H_
#define HAL_SSD_SSD_INTERFACE_H_

typedef struct
{
	u8 ComType;
	u8 Port;
	u8 EnablePort;
	u8 EnablePin;
}SSD_t;

typedef enum
{
	SSD_ZERO ,
	SSD_ONE  ,
	SSD_TWO  ,
	SSD_THREE,
	SSD_FOUR ,
	SSD_FIVE ,
	SSD_SIX  ,
	SSD_SEVEN,
	SSD_EIGHT,
	SSD_NINE
}SSD_Value_t;


typedef enum
{
	CommonAnode,
	CommonCathode
}SSD_Common_t;

u8 SSD_u8EnableSSD(SSD_t* Copy_pu8SSDInfo);
u8 SSD_u8DisableSSD(SSD_t* Copy_pu8SSDInfo);
u8 SSD_u8DisplayNum(SSD_t* Copy_pu8SSDInfo, u8 Copy_u8Number);

#endif
