
#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_

void EEPROM_SendDataByte(u8 Copy_u8DataByte, u16 Copy_u16Address);

u8 EEPROM_ReadDataByte(u16 Copy_u16Address);

#endif
