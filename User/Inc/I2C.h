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


#ifndef __I2C_H
#define __I2C_H


#include "board.h"


#define       I2C_DEVICE_READY             1



void I2C_Init(void);

void I2C_Write(ICInfoType *ICInfo, TransferType* Transfer);

void I2C_Read(ICInfoType *ICInfo, TransferType* Transfer);

uint8_t I2C_IsReady(ICInfoType *ICInfo);

void I2C_SendBusAdr(uint8_t Address);

void I2C_StartWrite(ICInfoType *ICInfo, uint32_t InternalAdr);


#endif //__I2C_H


