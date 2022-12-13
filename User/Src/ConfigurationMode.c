/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#include "ConfigurationMode.h"
#include "I2C.h"
#include "I2C_Memory.h"
#include "USBDevice.h"
#include "MemoryMap.h"


static TransferType Transfer;



void ConfigurationApplication(void)
{
  if ((*USBDevice_GetStatus()) != USB_PORT_IDLE)
  {
    if (((*USBDevice_GetStatus()) & USB_PORT_WRITE_CONFIG) == USB_PORT_WRITE_CONFIG)
    {
      USBDevice_ClearStatus(USB_PORT_WRITE_CONFIG);
       
      uint8_t *NewData = (uint8_t *)USBDevice_GetPacket();
      if ((*(NewData + USB_SUBCMD_INDEX)) == USB_SUBCMD_DATA_BLOCK_START)
      { 
        MemTransferInit(NewData);
      }
      else if ((*(NewData + USB_SUBCMD_INDEX)) == USB_SUBCMD_DATA_BLOCK_NEXT)
      {
        MemTransferUpdate(NewData);
      }
      else if ((*(NewData + USB_SUBCMD_INDEX)) == USB_SUBCMD_DATA_BLOCK_END)
      {
        USBDevice_SetStatus(USB_PORT_BUSY_TO_RECEIVE);
          
        MemTransferUpdate(NewData);
        while(Memory_IsReady() != I2C_DEVICE_READY);
        Memory_Write(&Transfer);
                  
        USBDevice_ClearStatus(USB_PORT_BUSY_TO_RECEIVE);
      }
      else if ((*(NewData + USB_SUBCMD_INDEX)) == USB_SUBCMD_DATA_BLOCK_START_END)
      {
        USBDevice_SetStatus(USB_PORT_BUSY_TO_RECEIVE);
          
        MemTransferInit(NewData);        
        while(Memory_IsReady() != I2C_DEVICE_READY);
        Memory_Write(&Transfer);
        
        USBDevice_ClearStatus(USB_PORT_BUSY_TO_RECEIVE);
      }
    }
      
    else if (((*USBDevice_GetStatus()) & USB_PORT_BOOT_CONFIG) == USB_PORT_BOOT_CONFIG)
    {
      USBDevice_ClearStatus(USB_PORT_BOOT_CONFIG);
    }
      
    else if (((*USBDevice_GetStatus()) & USB_PORT_MEMORY_ERASE) == USB_PORT_MEMORY_ERASE)
    {
      USBDevice_ClearStatus(USB_PORT_MEMORY_ERASE);
      //USBDevice_SetStatus(USB_PORT_BUSY_TO_RECEIVE);
        
      //Memory_EraseConfig();
       
      //USBDevice_ClearStatus(USB_PORT_BUSY_TO_RECEIVE);
    }
  }    
}
//------------------------------------------------------------------------------
void MemTransferUpdate(uint8_t *Data)
{
  uint16_t CurSize = Transfer.Size;
  for (uint8_t i = 0; i < Data[USB_DATA_SIZE_OFFSET]; i++)
    Transfer.Data[CurSize + i] = Data[USB_DATA_DATA_OFFSET + i];
  
  Transfer.Size += Data[USB_DATA_SIZE_OFFSET];
}
//------------------------------------------------------------------------------
void MemTransferInit(uint8_t *Data)
{
  Transfer.Address = JoinBytesIntoValue(&Data[USB_DATA_ADDRESS_OFFSET], MEMORY_ADDRESS_SIZE_USED);
  Transfer.Size = Data[USB_DATA_SIZE_OFFSET];
  for (uint8_t i = 0; i < Data[USB_DATA_SIZE_OFFSET]; i++)
    Transfer.Data[i] = Data[USB_DATA_DATA_OFFSET + i];
}


