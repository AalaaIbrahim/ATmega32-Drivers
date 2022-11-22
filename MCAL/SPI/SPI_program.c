
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_register.h"
//#include "SPI_private.h"
//#include "SPI_config.h"

void SPI_voidMasterInit(void)
{
	/* Master Initialization */
	SET_BIT(SPCR, SPCR_MSTR);

	/* Select Clock: prescaler div by 16 */
	SET_BIT(SPCR, SPCR_SPR0);
	CLR_BIT(SPCR, SPCR_SPR1);
	CLR_BIT(SPSR, SPSR_SPI2X);

	/* Enable SPI */
	SET_BIT(SPCR, SPCR_SPE);
}

void SPI_voidSlaveInit(void)
{
	/* Slave Initialization */
	CLR_BIT(SPCR, SPCR_MSTR);

	/* Enable SPI */
	SET_BIT(SPCR, SPCR_SPE);
}

u8 SPI_u8Transceive(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;

	/* Todo: Add timeout */
	while(GET_BIT(SPCR, SPCR_SPIE) == 0);

	return SPDR;
}
