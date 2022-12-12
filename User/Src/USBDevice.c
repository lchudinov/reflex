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



#include "USBDevice.h"
#include "usbd_audio_if.h"
#include "usbd_desc.h"
#include "usbd_customhid.h"
#include "usbd_customhid_if.h"


USBD_HandleTypeDef USBD_Device;
extern USBD_AUDIO_InterfaceCallbacksfTypeDef audio_class_interface;
uint8_t PrevXferDone = 1;
static uint8_t USBDataBuf[USB_MESSAGE_LENGTH];
static volatile uint8_t USBStatus = USB_PORT_IDLE;


void USBDevice_Init(uint8_t USBMode)
{
  USBD_Init(&USBD_Device, &Device_Desc, 0);
  USB_FIFO_Setup(USBMode);
  
  if (USBMode == USB_SOUND_CARD_MODE)
  {
    USBD_RegisterClass(&USBD_Device, USBD_AUDIO_CLASS);
    USBD_AUDIO_RegisterInterface(&USBD_Device, &audio_class_interface);
  }
  else
    USBD_RegisterClass(&USBD_Device, &USBD_CUSTOM_HID);
  
  USBD_Start(&USBD_Device);
}
//------------------------------------------------------------------------------
void USBDevice_RecPacket(uint8_t *Packet)
{
  for (uint8_t i = 0; i < USB_MESSAGE_LENGTH; i++)
    USBDataBuf[i] = *(Packet + i);
  
  switch(*(USBDataBuf + USB_CMD_INDEX))
  {
    case USB_CMD_GET_STATUS:
      {
        USBDataBuf[USB_DATA_INDEX] = USBStatus;
        USBDevice_WhileNotReadyToSend();
        USBDevice_SendData((uint8_t *)USBDataBuf);
      }
    break;
    
    case USB_CMD_MEMORY_WRITE:
      USBStatus |= USB_PORT_WRITE_CONFIG;
    break;
    
    case USB_CMD_BOOT_CONFIG:
      USBStatus |= USB_PORT_BOOT_CONFIG;
    break;
    
    case USB_CMD_MEMORY_ERASE:
      USBStatus |= USB_PORT_MEMORY_ERASE;
    break;
    
    case USB_CMD_GET_ID:
      {
        USBDataBuf[USB_DATA_CONTROLLER_ID_INDEX] = SUPER_PRIMEv2_ID;
        USBDataBuf[USB_DATA_FIRMWARE_INDEX] = FIRMWARE_VERSION_BYTE_1;
        USBDataBuf[USB_DATA_FIRMWARE_INDEX + 1] = FIRMWARE_VERSION_BYTE_2;
        USBDataBuf[USB_DATA_FIRMWARE_INDEX + 2] = FIRMWARE_VERSION_BYTE_3;
        USBDataBuf[USB_DATA_FIRMWARE_INDEX + 3] = FIRMWARE_VERSION_BYTE_4;
        //USBDataBuf[USB_DATA_MEMORY_SIZE_INDEX] = MEMORY_SIZE;
        //USBDataBuf[USB_DATA_MEMORY_SIZE_INDEX + 1] = MEMORY_SIZE_UINTS;
        USBDataBuf[USB_DATA_HARDWARE_INDEX] = HARDWARE_VERSION;
        if ((USBStatus & USB_PORT_MEMORY_DETECTED) == USB_PORT_MEMORY_DETECTED)
          USBDataBuf[USB_DATA_MEMORY_DETECT_INDEX] = MEMORY_CHIP_DETECTED;
        else
          USBDataBuf[USB_DATA_MEMORY_DETECT_INDEX] = 0;
        USBDevice_WhileNotReadyToSend();
        USBDevice_SendData((uint8_t *)USBDataBuf);
      }
    break;
    
    default:
    break;
  }  
}
//------------------------------------------------------------------------------
void USBDevice_SendData(uint8_t *Data)
{ 
  USBD_CUSTOM_HID_SendReport(&USBD_Device, Data, USB_MESSAGE_LENGTH);
  PrevXferDone = 0;
}
//------------------------------------------------------------------------------
volatile uint8_t* USBDevice_GetStatus(void)
{
  return &USBStatus;
}
//------------------------------------------------------------------------------
void USBDevice_ClearStatus(uint8_t StatusFlag)
{
  USBStatus &= ~StatusFlag;
}
//------------------------------------------------------------------------------
void USBDevice_SetStatus(uint8_t StatusFlag)
{
  USBStatus |= StatusFlag;
}
//------------------------------------------------------------------------------
uint8_t* USBDevice_GetPacket(void)
{
  return USBDataBuf;
}
//------------------------------------------------------------------------------
void USBDevice_WhileNotReadyToSend(void)
{
  while(PrevXferDone != 1);
}

