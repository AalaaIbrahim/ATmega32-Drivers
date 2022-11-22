
#ifndef MCAL_TWI_TWI_PRIVATE_H_
#define MCAL_TWI_TWI_PRIVATE_H_

#define  TWI_ENABLE                           1
#define  TWI_DISABLE                          2

/* Status codes for Master transmitter mode (prescaler bits are zero) */
#define  MSTR_TX_START                        0x08
#define  MSTR_TX_REP_START                    0x10
#define  MSTR_TX_ADD_W_ACK                    0x18
#define  MSTR_TX_ADD_W_NACK                   0x20
#define  MSTR_TX_DATA_ACK                     0x28
#define  MSTR_TX_DATA_NACK                    0x30
#define  MSTR_TX_ARB_LOST_ADD_W_DATA  		  0x38		  		  /* Arbitration lost in SLA+W or data bytes */

/* Status codes for Master receiver mode (prescaler bits are zero) */
#define  MSTR_RX_ARB_LOST_ADD_R_NACK          0x38                /* Arbitration lost in SLA+R or NACK bit */
#define  MSTR_RX_ADD_R_ACK                    0x40                /* SLA+R has been transmitted and Ack received */
#define  MSTR_RX_ADD_R_NACK                   0x48                /* SLA+R has been transmitted and NACK received */
#define  MSTR_RX_DATA_ACK                     0x50                /* Data byte has been received and ACK returned */
#define  MSTR_RX_DATA_NACK                    0x58                /* Data byte has been received and NACK returned */

/* Status codes for Slave receiver mode (prescaler bits are zero) */
#define  SLV_RX_OWN_SLA_W_ACK                 0x60                /* Own SLA+W has been received and ACK returned */
#define  SLV_RX_ARB_LOST_AS_MSTR              0x68                /* Arbitration lost in SLA+W as master, own SLA+W received, ACK returned */
#define  SLV_RX_GENERAL_CALL_ACK              0x70                /* General call address received, ACK returned */
#define  SLV_RX_ARB_LOST_GEN_CALL_ACK         0x78                /* Arbitration lost in SLA+R/W as master, general call received, ACK returned */
#define  SLV_RX_SLA_W_ACK                     0x80                /* Previously addressed with own SLA+W, data received, ACK returned */
#define  SLV_RX_SLA_W_NACK                    0x88                /* Previously addressed with own SLA+W, data received, NACK returned */
#define  SLV_RX_GEN_CALL_ACK                  0x90                /* Previously addressed with general call, data received, ACK returned */
#define  SLV_RX_GEN_CALL_NACK                 0x98                /* Previously addressed with general call, data received, NACK returned */
#define  SLV_RX_STOP_REP_STRT                 0xa0                /* A stop condition or repeated start condition received while still addressed as slave */

/* Status codes for Slave Transmitter mode (prescaler bits are zero) */
#define  SLV_TX_SLA_R_ACK                     0xa8                 /* Own SLA+R has been received and ACK has been returned */
#define  SLV_TX_ARB_LOST_AS_MSTR              0xb0                 /* Arbitration lost in SLA+R/W as master, own SLA+R received, ACK returned  */
#define  SLV_TX_DATA_TX_ACK                   0xb8                 /* Data byte in TWDR transmitted, ACK received */
#define  SLV_TX_DATA_TX_NACK                  0xc0                 /* Data byte in TWDR transmitted, NACK received */
#define  SLV_TX_LAST_DATA_TX_ACK              0xc8                 /* Last data byte in TWDR transmitted (TWEA + "0"), ACK received */

/* Miscellaneous States */
#define  TWI_STATE_NO_INFO                    0xf8                /* No relevant state info available (TWINT = 0) */
#define  TWI_STATE_BUS_ERROR                  0x00                /* Bus error due to illegal start or stop condition */


/* Used to mask the pre-scaler bits and to read the TWI status value */
#define  TWI_PRESCALER_MASK					  0XFC

typedef enum
{
	TWI_NO_PRESCALER,
	TWI_DIV_BY_4,
	TWI_DIV_BY_16,
	TWI_DIV_BY_64
}TWI_prescaler_t;

#endif
