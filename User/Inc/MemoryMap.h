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


#ifndef __MEMORY_MAP_H
#define __MEMORY_MAP_H


#include "Board.h"


#define   BLOCK_CONFIGURATION_SIZE         2
#define   ID_SIZE                          1
#define   ADDRESS_IN_DSP_SIZE              4

//MEMORY_MAP_TABLE
#define   BOOT_START_ADDRESS               0
#define   BOOT_IMAGE_SIZE_OFFSET           BOOT_START_ADDRESS
#define   BOOT_IMAGE_SIZE_SIZE             4
#define   BOOT_IMAGE_MAKER_VER_OFFSET      (BOOT_IMAGE_SIZE_OFFSET + BOOT_IMAGE_SIZE_SIZE)
#define   BOOT_IMAGE_MAKER_VER_SIZE        2
#define   MEMORY_MAP_TABLE_SIZE_OFFSET     (BOOT_IMAGE_MAKER_VER_OFFSET + BOOT_IMAGE_MAKER_VER_SIZE)
#define   MEMORY_MAP_TABLE_SIZE_SIZE       2
#define   CONTROLLER_CONF_ADR_OFFSET       (MEMORY_MAP_TABLE_SIZE_OFFSET + MEMORY_MAP_TABLE_SIZE_SIZE)
#define   CONTROLLER_CONF_ADR_SIZE         2
#define   CONTROLLER_CONF_SIZE_OFFSET      (CONTROLLER_CONF_ADR_OFFSET + CONTROLLER_CONF_ADR_SIZE)
#define   CONTROLLER_CONF_SIZE_SIZE        BLOCK_CONFIGURATION_SIZE
#define   FIRST_BLOCK_CONF_MAP_OFFSET      (CONTROLLER_CONF_SIZE_OFFSET + CONTROLLER_CONF_SIZE_SIZE)
#define   CONTROLLER_CONF_MAP_SIZE         (CONTROLLER_CONF_ADR_SIZE + CONTROLLER_CONF_SIZE_SIZE)

//BLOCK_CONFIGURATION_MAP
#define   BLOCK_ID_OFFSET                  0
#define   BLOCK_ID_SIZE                    ID_SIZE
#define   BLOCK_AUDIO_CONF_NUM_OFFSET      (BLOCK_ID_OFFSET + BLOCK_ID_SIZE)
#define   BLOCK_AUDIO_CONF_NUM_SIZE        1
#define   BLOCK_CONF_ADR_OFFSET            (BLOCK_AUDIO_CONF_NUM_OFFSET + BLOCK_AUDIO_CONF_NUM_SIZE)
#define   BLOCK_CONF_ADR_SIZE              3
#define   BLOCK_CONF_SIZE_OFFSET           (BLOCK_CONF_ADR_OFFSET + BLOCK_CONF_ADR_SIZE)
#define   BLOCK_CONF_SIZE_SIZE             BLOCK_CONFIGURATION_SIZE
#define   BLOCK_CONF_MAP_SIZE              (BLOCK_ID_SIZE + BLOCK_AUDIO_CONF_NUM_SIZE + BLOCK_CONF_ADR_SIZE + BLOCK_CONF_SIZE_SIZE)

//CONTROLLER_CONFIGURATION
#define   CONTROLLER_ID_OFFSET             0
#define   CONTROLLER_ID_SIZE               ID_SIZE
#define   CONTROLLER_GPIO_CONF_OFFSET      (CONTROLLER_ID_OFFSET + CONTROLLER_ID_SIZE)
#define   CONTROLLER_GPIO_CONF_SIZE        (USER_GPIO_COUNT + DSP_INTERFACE_COUNT)
#define   CONTROLLER_RESERVED_OFFSET       (CONTROLLER_GPIO_CONF_OFFSET + CONTROLLER_GPIO_CONF_SIZE)
#define   CONTROLLER_RESERVED_SIZE         8
#define   CONTROLLER_VID_OFFSET            (CONTROLLER_RESERVED_OFFSET + CONTROLLER_RESERVED_SIZE)
#define   CONTROLLER_VID_SIZE              2
#define   CONTROLLER_PID_OFFSET            (CONTROLLER_VID_OFFSET + CONTROLLER_VID_SIZE)
#define   CONTROLLER_PID_SIZE              2
#define   CONTROLLER_MANUFACT_SIZE_OFFSET  (CONTROLLER_PID_OFFSET + CONTROLLER_PID_SIZE)
#define   CONTROLLER_MANUFACT_SIZE_SIZE    1
#define   CONTROLLER_MANUFACT_OFFSET       (CONTROLLER_MANUFACT_SIZE_OFFSET + CONTROLLER_MANUFACT_SIZE_SIZE)
#define   CONTROLLER_MANUFACT_SIZE         USB_MANUFACTURE_MAX_LENGTH
#define   FIRST_AUDIO_NAME_MAP_OFFSET      (CONTROLLER_MANUFACT_OFFSET + CONTROLLER_MANUFACT_SIZE)

//AUDIO_NAME_MAP
#define   AUDIO_NAME_SIZE_OFFSET           0
#define   AUDIO_NAME_SIZE_SIZE             1
#define   AUDIO_NAME_OFFSET                (AUDIO_NAME_SIZE_OFFSET + AUDIO_NAME_SIZE_SIZE)
#define   AUDIO_NAME_SIZE                  USB_DEVICE_NAME_MAX_LENGTH
#define   AUDIO_NAME_MAP_SIZE              (AUDIO_NAME_SIZE_SIZE + AUDIO_NAME_SIZE)



#endif //__MEMORY_MAP_H

