
#include "../../LIB/STD_TYPES.h"
#include <util/delay.h>

#include "../../MCAL/TWI/TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"

/**
 * @param Copy_u8DataByte: data to write to eeprom
 * @param Copy_u16Address: 10-bit address
 */
void EEPROM_SendDataByte(u8 Copy_u8DataByte, u16 Copy_u16Address)
{
	u8 Local_u8SlaveAddress = (0b1010000 | (PIN_A2_CONNECTION<<2) | (Copy_u16Address>>8));

	/* Send Start Condition */
	TWI_SendStartCond();

	/* Send EEPROM and Block address */
	TWI_SendSlaveAddressWithWrite(Local_u8SlaveAddress);

	/* Send Byte address */
	TWI_MasterWriteDataByte((u8)Copy_u16Address);

	/* Write the Data */
	TWI_MasterWriteDataByte(Copy_u8DataByte);

	/* Send Stop Condition */
	TWI_SendStopCond();

	/* EEPROM takes 10 ms to receive data byte */
	_delay_ms(10);
}

u8 EEPROM_ReadDataByte(u16 Copy_u16Address)
{
	u8 Local_u8DataByte;
	u8 Local_u8SlaveAddress = (0b1010000 | (PIN_A2_CONNECTION<<2) | (Copy_u16Address>>8));

	/* Send Start Condition */
	TWI_SendStartCond();

	/* Send EEPROM and Block address */
	TWI_SendSlaveAddressWithWrite(Local_u8SlaveAddress);

	/* Send Byte address */
	TWI_MasterWriteDataByte((u8)Copy_u16Address);

	/* Send Repeated start */
	TWI_SendRepeatedStart();

	/* Send address with read */
	TWI_SendSlaveAddressWithRead(Local_u8SlaveAddress);

	/* Read the data */
	TWI_MasterReadDataByte(&Local_u8DataByte);

	return Local_u8DataByte;
}

