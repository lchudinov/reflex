/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/



#include "I2C_Memory.h"
#include "I2C.h"
#include "MemoryMap.h"


static ICInfoType MemoryIC = { UNDEFINED_VALUE, EEPROM_ADDRESS, UNDEFINED_VALUE, MEMORY_IC_ADDRESS_BYTES };



void Memory_Write(TransferType* Transfer)
{
  I2C_Write(&MemoryIC, Transfer);
}
//------------------------------------------------------------------------------
void Memory_Read(TransferType* Transfer)
{
  I2C_Read(&MemoryIC, Transfer);
}
//------------------------------------------------------------------------------
uint8_t Memory_IsReady(void)
{
  return I2C_IsReady(&MemoryIC);
}
//------------------------------------------------------------------------------
uint32_t Memory_GetConfigSize(void)
{
  TransferType Transfer;
  Transfer.Size = BOOT_IMAGE_SIZE_SIZE;
  Transfer.Address = BOOT_IMAGE_SIZE_OFFSET;
  I2C_Read(&MemoryIC, &Transfer);
  return JoinBytesIntoValue(Transfer.Data, BOOT_IMAGE_SIZE_SIZE);
}
//------------------------------------------------------------------------------
void Memory_EraseConfig(void)
{
  uint32_t SizeValue = Memory_GetConfigSize();
  if (SizeValue != 0xFFFFFFFF)
  {
    SizeValue = SizeValue / EEPROM_PAGE_SIZE +1;
    
    TransferType Transfer;
    Transfer.Size = EEPROM_PAGE_SIZE;
    Transfer.Address = 0;
    for (uint8_t i = 0; i < EEPROM_PAGE_SIZE; i++)
      Transfer.Data[i] = 0xFF;
    
    for (uint16_t i = 0; i < SizeValue; i++)
    {
      while(Memory_IsReady() != I2C_DEVICE_READY);
      I2C_Write(&MemoryIC, &Transfer);
      Transfer.Address += EEPROM_PAGE_SIZE;
    }
  }
}


