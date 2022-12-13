/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#include "Events.h"
#include "usb_audio_constants.h"



void Events_InitGPIOs(void)
{
  FREQ_EVENT_GPIO->MODER |= (1 << (2 * FREQ_EVENT_1_PIN)) | (1 << (2 * FREQ_EVENT_2_PIN)) |\
                            (1 << (2 * RES_EVENT_PIN));
  
  LED_GPIO->MODER |= 1 << (2 * LED_PIN);
}
//------------------------------------------------------------------------------
void Event_FreqChanged(uint32_t AudioFrequency)
{
  FREQ_EVENT_GPIO->ODR &= ~FREQ_EVENT_MASK;
    
  switch(AudioFrequency)
  {
    case USB_AUDIO_CONFIG_FREQ_44_1_K:
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_44100;
    break;
      
    case USB_AUDIO_CONFIG_FREQ_48_K:
    default:
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_48000;
    break;
          
    case USB_AUDIO_CONFIG_FREQ_96_K:
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_96000;
    break;
      
    case USB_AUDIO_CONFIG_FREQ_192_K:
      FREQ_EVENT_GPIO->ODR |= FREQ_EVENT_192000;
    break;
  }
}
//------------------------------------------------------------------------------
void Event_ResChanged(uint8_t AudioResolution)
{
  if (AudioResolution == 16)
    RES_EVENT_GPIO->ODR &= ~RES_EVENT_24BIT;
  else
    RES_EVENT_GPIO->ODR |= RES_EVENT_24BIT;
}
//------------------------------------------------------------------------------
void Event_MuteChanged(uint8_t MuteFlag)
{
  if (MuteFlag)
    LED_GPIO->ODR |= 1 << LED_PIN;
  else
    LED_GPIO->ODR &= ~(1 << LED_PIN);
}



