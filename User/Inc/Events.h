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



#ifndef __EVENTS_H
#define __EVENTS_H


#include "board.h"


void Events_InitGPIOs(void);

void Event_FreqChanged(uint32_t AudioFrequency);

void Event_ResChanged(uint8_t AudioResolution);

void Event_MuteChanged(uint8_t MuteFlag);


#endif //__EVENTS_H