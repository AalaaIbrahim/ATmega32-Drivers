
#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_

typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWriteError,
	SlaveAddressReadError,
	MasterWriteByteError,
	MasterReadByteError,
	StopConditionError
}TWI_Error_Status;

/* pass 0 as argument if master will not be addressed */
void TWI_voidMasterInit(u8 Copy_u8Address);

void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress);

TWI_Error_Status TWI_SendStartCond(void);

TWI_Error_Status TWI_SendRepeatedStart(void);

TWI_Error_Status TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

TWI_Error_Status TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

TWI_Error_Status TWI_MasterWriteDataByte(u8 Copy_u8DataByte);

TWI_Error_Status TWI_MasterReadDataByte(u8* Copy_u8DataByte);

void TWI_SendStopCond(void);

#endif
