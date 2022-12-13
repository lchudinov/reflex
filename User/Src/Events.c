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


#include "Events.h"
#include "usb_audio_constants.h"



void Events_InitGPIOs(void)
{
  FREQ_EVENT_GPIO->MODER |= (1 << (2 * FREQ_EVENT_1_PIN)) | (1 << (2 * FREQ_EVENT_2_PIN)) |\
                            (1 << (2 * RES_EVENT_2_PIN));
  
  RES_EVENT_1_GPIO->MODER |= (1 << (2 * RES_EVENT_1_PIN)) | (1 << (2 * FREQ_EVENT_3_PIN));
  
  LED_GPIO->MODER |= 1 << (2 * LED_PIN);
}
//------------------------------------------------------------------------------
void Event_FreqChanged(uint32_t AudioFrequency)
{
  switch(AudioFrequency)
  {
    case USB_AUDIO_CONFIG_FREQ_44_1_K:
      FREQ_EVENT_3_GPIO->ODR &= ~FREQ_EVENT_3_PIN_MASK;
      FREQ_EVENT_GPIO->ODR &= ~FREQ_EVENT_MASK;
    break;
      
    case USB_AUDIO_CONFIG_FREQ_88_2_K:
      FREQ_EVENT_3_GPIO->ODR |= FREQ_EVENT_3_PIN_MASK;
      FREQ_EVENT_GPIO->ODR &= ~FREQ_EVENT_1_PIN_MASK;
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_2_PIN_MASK;
    break;
          
    case USB_AUDIO_CONFIG_FREQ_96_K:
      FREQ_EVENT_3_GPIO->ODR &= ~FREQ_EVENT_3_PIN_MASK;
      FREQ_EVENT_GPIO->ODR &= ~FREQ_EVENT_1_PIN_MASK;
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_2_PIN_MASK;
    break;
    
    case USB_AUDIO_CONFIG_FREQ_176_4_K:
      FREQ_EVENT_3_GPIO->ODR |= FREQ_EVENT_3_PIN_MASK;
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_MASK;
    break;
    
    case USB_AUDIO_CONFIG_FREQ_192_K:
      FREQ_EVENT_3_GPIO->ODR &= ~FREQ_EVENT_3_PIN_MASK;
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_MASK;
    break;
    
    case USB_AUDIO_CONFIG_FREQ_48_K:
    default:
      FREQ_EVENT_3_GPIO->ODR &= ~FREQ_EVENT_3_PIN_MASK;
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_1_PIN_MASK;
      FREQ_EVENT_GPIO->ODR &= ~FREQ_EVENT_2_PIN_MASK;
    break;
  }
}
//------------------------------------------------------------------------------
void Event_ResChanged(uint8_t AudioResolution)
{
  if (AudioResolution == 16)
  {
    RES_EVENT_1_GPIO->ODR &= ~RES_EVENT_1_PIN_MASK;
    RES_EVENT_2_GPIO->ODR &= ~RES_EVENT_2_PIN_MASK;
  }
  else if (AudioResolution == 24)
  {
    RES_EVENT_1_GPIO->ODR |= RES_EVENT_1_PIN_MASK;
    RES_EVENT_2_GPIO->ODR &= ~RES_EVENT_2_PIN_MASK;
  }
  else if (AudioResolution == 32)
  {
    RES_EVENT_1_GPIO->ODR &= ~RES_EVENT_1_PIN_MASK;
    RES_EVENT_2_GPIO->ODR |= RES_EVENT_2_PIN_MASK;
  }
}
//------------------------------------------------------------------------------
void Event_MuteChanged(uint8_t MuteFlag)
{
  if (MuteFlag)
    LED_GPIO->ODR |= 1 << LED_PIN;
  else
    LED_GPIO->ODR &= ~(1 << LED_PIN);
}



