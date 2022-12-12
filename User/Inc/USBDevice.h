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


#ifndef __USBDEVICE_H
#define __USBDEVICE_H


#include "board.h"


#define   USB_MESSAGE_LENGTH               0x40

#define   USB_REPORT_ID_INDEX              0
#define   USB_CMD_INDEX                    0x01 
#define   USB_SUBCMD_INDEX                 0x02
#define   USB_DATA_INDEX                   0x03


#define   USB_CMD_GET_STATUS               0
#define   USB_CMD_MEMORY_WRITE             1
#define   USB_CMD_BOOT_CONFIG              2
#define   USB_CMD_MEMORY_ERASE             3
#define   USB_CMD_GET_ID                   4

#define   USB_SUBCMD_DATA_BLOCK_START      0
#define   USB_SUBCMD_DATA_BLOCK_NEXT       1
#define   USB_SUBCMD_DATA_BLOCK_END        2
#define   USB_SUBCMD_DATA_BLOCK_START_END  3

#define   USB_DATA_ADDRESS_OFFSET          USB_DATA_INDEX//0
#define   USB_DATA_ADDRESS_SIZE            4
#define   USB_DATA_SIZE_OFFSET             (USB_DATA_ADDRESS_OFFSET + USB_DATA_ADDRESS_SIZE)
#define   USB_DATA_SIZE_SIZE               1
#define   USB_DATA_DATA_OFFSET             (USB_DATA_SIZE_OFFSET + USB_DATA_SIZE_SIZE)

#define   USB_DATA_CONTROLLER_ID_INDEX     USB_DATA_INDEX
#define   USB_DATA_FIRMWARE_INDEX          (USB_DATA_CONTROLLER_ID_INDEX + 1)
#define   USB_DATA_MEMORY_SIZE_INDEX       (USB_DATA_FIRMWARE_INDEX + 4)
#define   USB_DATA_HARDWARE_INDEX          (USB_DATA_MEMORY_SIZE_INDEX + 2)
#define   USB_DATA_MEMORY_DETECT_INDEX     (USB_DATA_HARDWARE_INDEX + 1)

//Status
#define   USB_PORT_IDLE                    0
#define   USB_PORT_WRITE_CONFIG            (1 << 1)
#define   USB_PORT_BOOT_CONFIG             (1 << 2)
#define   USB_PORT_MEMORY_ERASE            (1 << 3)
#define   USB_PORT_MEMORY_DETECTED         (1 << 6)
#define   USB_PORT_BUSY_TO_RECEIVE         (1 << 7)

#define   MEMORY_CHIP_DETECTED             1


void USBDevice_Init(uint8_t USBMode);

void USBDevice_RecPacket(uint8_t *Packet);

void USBDevice_SendData(uint8_t *Data);

volatile uint8_t* USBDevice_GetStatus(void);

void USBDevice_ClearStatus(uint8_t StatusFlag);

void USBDevice_SetStatus(uint8_t StatusFlag);

uint8_t* USBDevice_GetPacket(void);

void USBDevice_WhileNotReadyToSend(void);


#endif //__USBDEVICE_H


