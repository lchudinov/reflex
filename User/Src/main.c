/*
********************************************************************************
* This file is a part of firmware for Reflex module
* (USB_I2S_PRIME_SUPER modification)
*
* Copyright (c) 2019 - 2021 ChipDip. <https://www.chipdip.ru>
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


#include "usb_audio.h"
#include "audio_configuration.h"
#include "I2C.h"
#include "I2C_Memory.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal.h"
#include "usbd_conf.h"
#include "USBDevice.h"
#include "SoundCardMode.h"
#include "ConfigurationMode.h"
#include "Events.h"


void (*Application)(void);


int main(void)
{
  USB_I2S_Init();
  
  while (1)
  {
    __WFI();
    Application();
  }
}
//------------------------------------------------------------------------------
void USB_I2S_Init(void)
{
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  HAL_InitTick(TICK_INT_PRIORITY);
  
  //HSE, PLL 168 MHz
  FLASH->ACR = FLASH_ACR_LATENCY_5WS | FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN;
  
  RCC->CR |= RCC_CR_HSEON;
  while((RCC->CR & RCC_CR_HSERDY) == 0);
    
  RCC->PLLCFGR = RCC_PLLCFGR_PLLR_1 | RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_2 | \
                 RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_8 | RCC_PLLCFGR_PLLM_3;
    
  RCC->CFGR = RCC_CFGR_PPRE2_DIV2 | RCC_CFGR_PPRE1_DIV4;
    
  RCC->CR |= RCC_CR_PLLON;
  while((RCC->CR & RCC_CR_PLLRDY) == 0);
  
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL);
  
  //добавить для всех используемых выводов
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;
  while((RCC->AHB1ENR & (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN))
                     != (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN));
    
  //выводы конфигурации
  MEMORY_ERASE_GPIO->PUPDR |= 1 << (2 * MEMORY_ERASE_PIN);
    
  CONFIG_GPIO->PUPDR |= (1 << (2 * AUDIO_CONFIG_1_PIN)) | (1 << (2 * AUDIO_CONFIG_2_PIN)) | \
                        (1 << (2 * AUDIO_CONFIG_3_PIN)) | (1 << (2 * TDM_MODE_PIN)) | \
                        (1 << (2 * SYNC_MODE_PIN_1)) | (1 << (2 * SYNC_MODE_PIN_2)) | \
                        (1 << (2 * HW_VOL_CTRL_PIN));
  
  BCLK_Fs_RATIO_GPIO->PUPDR |= 1 << (2 * BCLK_Fs_RATIO_PIN);
  
  CONFIG_MODE_GPIO->PUPDR |= (1 << (2 * CONFIG_MODE_PIN)) | (1 << (2 * BCLK_POLARITY_PIN));
  while((CONFIG_MODE_GPIO->PUPDR & (1 << (2 * CONFIG_MODE_PIN))) != (1 << (2 * CONFIG_MODE_PIN)));
  
  I2C_Init();
  
  uint8_t USBMode = (CONFIG_MODE_GPIO->IDR & (1 << CONFIG_MODE_PIN)) >> CONFIG_MODE_PIN;
  if (USBMode == USB_SOUND_CARD_MODE)
  {
    Events_InitGPIOs();
    AudioConfig_Init();
    Application = SoundCardApplication;
  }
  else
  {
    Application = ConfigurationApplication;
    
    if (Memory_IsReady() == I2C_DEVICE_READY)
    {
      if ((MEMORY_ERASE_GPIO->IDR & (1 << MEMORY_ERASE_PIN)) != (1 << MEMORY_ERASE_PIN))
        Memory_EraseConfig();
      
      USBDevice_SetStatus(USB_PORT_MEMORY_DETECTED);
    }
  }
  
  USBDevice_Init(USBMode);
}
//------------------------------------------------------------------------------
void Error_Handler(void)
{
   
}
//------------------------------------------------------------------------------
void USBD_error_handler(void)
{
  Error_Handler();
}
//------------------------------------------------------------------------------
uint32_t JoinBytesIntoValue(uint8_t *Data, uint8_t Size)
{
  uint32_t Result = 0;
  
  for (uint8_t i = 0; i < Size; i++)
    Result |= (*(Data + i)) << (i * 8);
  
  return Result;
}


