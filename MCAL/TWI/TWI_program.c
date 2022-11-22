
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TWI_interface.h"
#include "TWI_register.h"
#include "TWI_private.h"
#include "TWI_config.h"

/* pass 0 as argument if master will not be addressed */
void TWI_voidMasterInit(u8 Copy_u8Address)
{
	/* Set Clock to 400kbps */
	TWBR = 2;

	TWSR &= TWI_PRESCALER_MASK;
	TWSR |= TWI_NO_PRESCALER;

	/* Set Master address (if provided) */
	if (Copy_u8Address != 0)
	{
		TWAR = Copy_u8Address << 1;

#if GET_GENERAL_CALL == TWI_ENABLE
		SET_BIT(TWAR, TWAR_TWGCE);
#elif GET_GENERAL_CALL == TWI_DISABLE
		CLR_BIT(TWAR, TWAR_TWGCE);
#endif

	}

	/* Enable TWI */
	SET_BIT(TWCR, TWCR_TWEN);

}


void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress)
{
	/* Initialize the node address */
	TWAR = Copy_u8SlaveAddress << 1;

	/* Enable TWI */
	SET_BIT(TWCR, TWCR_TWEN);
}

TWI_Error_Status TWI_SendStartCond(void)
{
	TWI_Error_Status Local_ErrorStatus = NoError;

	/* Send Start Condition on the bus */
	SET_BIT(TWCR, TWCR_TWSTA);

	/* Clear the interrupt flag to start the previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again (previous operation is complete) */
	while(GET_BIT(TWCR, TWCR_TWINT)==0);

	/* Check the status to make sure the correct operation was made */
	if((TWSR & TWI_PRESCALER_MASK) != MSTR_TX_START)
	{
		Local_ErrorStatus = StartConditionError;
	}

	return Local_ErrorStatus;
}

TWI_Error_Status TWI_SendRepeatedStart(void)
{
	TWI_Error_Status Local_ErrorStatus = NoError;

	/* Send Start Condition on the bus */
	SET_BIT(TWCR, TWCR_TWSTA);

	/* Clear the interrupt flag to start the previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again (previous operation is complete) */
	while(GET_BIT(TWCR, TWCR_TWINT)==0);

	/* Check the status to make sure the correct operation was made */
	if((TWSR & TWI_PRESCALER_MASK) != MSTR_TX_REP_START)
	{
		Local_ErrorStatus = RepeatedStartError;
	}

	return Local_ErrorStatus;
}

TWI_Error_Status TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_Error_Status Local_ErrorStatus = NoError;

	/* Clear Start Condition bit */
	CLR_BIT(TWCR, TWCR_TWSTA);

	/* Set the slave address in the MS 7 bits of data register */
	TWDR = Copy_u8SlaveAddress << 1;

	/* Clear the interrupt flag to start the previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again (previous operation is complete) */
	while(GET_BIT(TWCR, TWCR_TWINT)==0);

	/* Check the status to make sure the correct operation was made */
	if((TWSR & TWI_PRESCALER_MASK) != MSTR_TX_ADD_W_ACK)
	{
		Local_ErrorStatus = SlaveAddressWriteError;
	}

	return Local_ErrorStatus;
}

TWI_Error_Status TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_Error_Status Local_ErrorStatus = NoError;

	/* Clear Start Condition bit */
	CLR_BIT(TWCR, TWCR_TWSTA);

	/* Set the slave address in the MS 7 bits of data register */
	TWDR = Copy_u8SlaveAddress << 1;
	SET_BIT(TWDR, 0); //for read operation

	/* Clear the interrupt flag to start the previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again (previous operation is complete) */
	while(GET_BIT(TWCR, TWCR_TWINT)==0);

	/* Check the status to make sure the correct operation was made */
	if((TWSR & TWI_PRESCALER_MASK) != MSTR_RX_ADD_R_ACK)
	{
		Local_ErrorStatus = SlaveAddressReadError;
	}


	return Local_ErrorStatus;
}

TWI_Error_Status TWI_MasterWriteDataByte(u8 Copy_u8DataByte)
{
	TWI_Error_Status Local_ErrorStatus = NoError;

	/* Set the slave address in the MS 7 bits of data register */
	TWDR = Copy_u8DataByte;

	/* Clear the interrupt flag to start the previous operation */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again (previous operation is complete) */
	while(GET_BIT(TWCR, TWCR_TWINT)==0);

	/* Check the status to make sure the correct operation was made */
	if((TWSR & TWI_PRESCALER_MASK) != MSTR_TX_DATA_ACK)
	{
		Local_ErrorStatus = MasterWriteByteError;
	}

	return Local_ErrorStatus;
}

TWI_Error_Status TWI_MasterReadDataByte(u8* Copy_u8DataByte)
{
	TWI_Error_Status Local_ErrorStatus = NoError;

	/* Enable master sending acknowledge bit after receiving the data */
	SET_BIT(TWCR, TWCR_TWEA);

	/* Clear the interrupt flag to allow slave to send data */
	SET_BIT(TWCR, TWCR_TWINT);

	/* Wait until the interrupt flag is raised again (previous operation is complete) */
	while(GET_BIT(TWCR, TWCR_TWINT)==0);

	/* Check the status to make sure the correct operation was made */
	if((TWSR & TWI_PRESCALER_MASK) != MSTR_RX_DATA_ACK)
	{
		Local_ErrorStatus = MasterReadByteError;
	}
	else
	{
		/* read the received data */
		TWDR = *Copy_u8DataByte;
	}

	return Local_ErrorStatus;
}

void TWI_SendStopCond(void)
{
	/* Send Stop Condition on the bus */
	SET_BIT(TWCR, TWCR_TWSTO);

	/* Clear the interrupt flag to start the previous operation */
	SET_BIT(TWCR, TWCR_TWINT);
}
