/*
 * SPI_register.h
 *
 *  Created on: Sep 26, 2022
 *      Author: ME
 */

#ifndef MCAL_SPI_SPI_REGISTER_H_
#define MCAL_SPI_SPI_REGISTER_H_

#define  SPDR                     *((volatile u8*)0x2f)
#define  SPDR_                    7
#define  SPDR_                    6
#define  SPDR_                    5
#define  SPDR_                    4
#define  SPDR_                    3
#define  SPDR_                    2
#define  SPDR_                    1
#define  SPDR_                    0


#define  SPSR                     *((volatile u8*)0x2e)
#define  SPSR_SPIF                7
#define  SPSR_WCOL                6
#define  SPSR_SPI2X               0


#define  SPCR                     *((volatile u8*)0x2d)
#define  SPCR_SPIE                7
#define  SPCR_SPE                 6
#define  SPCR_DORD                5
#define  SPCR_MSTR                4
#define  SPCR_CPOL                3
#define  SPCR_CPHA                2
#define  SPCR_SPR1                1
#define  SPCR_SPR0                0



#endif /* MCAL_SPI_SPI_REGISTER_H_ */
