
#ifndef MCAL_TWI_TWI_REGISTER_H_
#define MCAL_TWI_TWI_REGISTER_H_

#define TWCR                      *((volatile u8*)0x56)
#define TWCR_TWINT                7                     /* TWI interrupt flag */
#define TWCR_TWEA                 6                     /* TWI enable acknowledge bit */
#define TWCR_TWSTA                5                     /* TWI start condition bit */
#define TWCR_TWSTO                4                     /* TWI stop condition bit */
#define TWCR_TWWC                 3                     /* TWI write collision flag */
#define TWCR_TWEN                 2                     /* TWI Enable bit */
#define TWCR_TWIE                 0                     /* TWI interrupt enable */


#define TWSR                      *((volatile u8*)0x21)
#define TWDR                      *((volatile u8*)0x23)
#define TWAR                      *((volatile u8*)0x22)
#define TWAR_TWGCE				  0						/* TWI General call recognition enable bit */

#define TWBR                      *((volatile u8*)0x20)	/* TWI bit data register */

#endif

/*
 * quadcopter:
 *  can't use wifi module (high delay)
 *  use bluetooth in short range
 *  use ir or zigbee
 */
