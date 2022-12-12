/*
********************************************************************************
* This file is a part of firmware for Reflex module
* (USB_I2S_PRIME_SUPER modification)
*
* Copyright (c) 2021 ChipDip. <https://www.chipdip.ru>
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



#ifndef __DAC_H
#define __DAC_H


#include "board.h"

#define   DAC_MIN_VALUE                    0x0000//0x00E0
#define   DAC_MAX_VALUE                    0x0FFF//0x0F1C


void DAC_Init(void);

void DAC_SetValuePercent(uint8_t DACValue);


#endif//__DAC_H