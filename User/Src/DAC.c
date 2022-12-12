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




#include "DAC.h"
#include "stm32f4xx_hal.h"


void DAC_Init(void)
{
  DAC_OUT_GPIO->MODER |= (3 << (2 * DAC_OUT_PIN));
  
  RCC->APB1ENR |= RCC_APB1ENR_DACEN;
  DAC->CR = DAC_CR_EN1;
  HAL_Delay(1);
  DAC->DHR12R1 = DAC_MIN_VALUE;
}
//------------------------------------------------------------------------------
void DAC_SetValuePercent(uint8_t ValPercent)
{
  uint16_t DACValue = ((DAC_MAX_VALUE - DAC_MIN_VALUE) * ValPercent) / 100;
  
  DAC->DHR12R1 = DACValue & 0x0FFF;
}