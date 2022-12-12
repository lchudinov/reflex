/*
********************************************************************************
* This file is a part of firmware for Reflex module
* (USB_I2S_PRIME_SUPER modification)
*
* Copyright (c) 2019 - 2020 ChipDip. <https://www.chipdip.ru>
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



#ifndef __USB_AUDIO_DESCRIPTORS_H
#define __USB_AUDIO_DESCRIPTORS_H



#define   CONFIG_2_0_STEREO_DESCRIPTOR_SIZE      (128 + 67)
#define   CONFIG_2_0_STEREO_AC_TOTAL_SIZE        40

#define   CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE   (119 + 3 + 3)

#define   CONFIG_3_1_DESCRIPTOR_SIZE             (127 + 58)
#define   CONFIG_3_1_AC_TOTAL_SIZE               42

#define   CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE      (127 + 58)
#define   CONFIG_4_0_QUADRO_AC_TOTAL_SIZE        42

#define   CONFIG_5_1_SURROUND_DESCRIPTOR_SIZE    (127 + 54)
#define   CONFIG_5_1_SURROUND_AC_TOTAL_SIZE      44

#define   CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE    (127 + 1)
#define   CONFIG_7_1_SURROUND_AC_TOTAL_SIZE      46

#define   CONFIG_2_0_SPDIF_DESCRIPTOR_SIZE       (128)
#define   CONFIG_2_0_SPDIF_AC_TOTAL_SIZE         40

#define   CONFIG_TERMINAL_INPUT_ID               0x12
#define   CONFIG_UNIT_FEATURE_ID                 0x16
#define   CONFIG_TERMINAL_OUTPUT_ID              0x14

#define   CONFIG_AUDIO_STREAMING_INTERFACE       1
#define   CONFIG_AUDIO_EP_OUT                    0x01
#define   CONFIG_AUDIO_EP_SYNC                   0x81
#define   CONFIG_AUDIO_FEEDBACK_REFRESH          0x07





uint8_t* GetProductString(void);



#endif // __USB_AUDIO_DESCRIPTORS_H


