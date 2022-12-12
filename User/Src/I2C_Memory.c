/*
********************************************************************************
* This file is a part of firmware for Reflex module
* (USB_I2S_PRIME_SUPER modification)
*
* Copyright (c) 2020 ChipDip. <https://www.chipdip.ru>
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License. 
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


