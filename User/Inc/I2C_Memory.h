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


#ifndef __I2C_MEMORY_H
#define __I2C_MEMORY_H


#include "board.h"


void Memory_Write(TransferType* Transfer);

void Memory_Read(TransferType* Transfer);

uint8_t Memory_IsReady(void);

uint32_t Memory_GetConfigSize(void);

void Memory_EraseConfig(void);


#endif //__I2C_MEMORY_H

