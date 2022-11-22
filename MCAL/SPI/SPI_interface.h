
#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_

void SPI_voidMasterInit(void);

void SPI_voidSlaveInit(void);

u8 SPI_u8Transceive(u8 Copy_u8Data);

#endif
