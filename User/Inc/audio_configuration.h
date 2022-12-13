/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2019, 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/




#ifndef __AUDIO_CONFIGURATION_H
#define __AUDIO_CONFIGURATION_H


#include "board.h"
#include "audio_node.h"
#include "usb_audio_constants.h"
#include "audio_speaker_node.h"
#include "MemoryMap.h"



#define   USE_USB_AUDIO_CLASS_10                 1

#define   ALTERNATE_SETTING_16_BIT               1
#define   ALTERNATE_SETTING_24_BIT               2

#define   CONFIG_RES_BIT_16                      16
#define   CONFIG_RES_BYTE_16                     2

#define   CONFIG_RES_BIT_24                      24
#define   CONFIG_RES_BYTE_24                     3

#define   CONFIG_RES_BIT_32                      32
#define   CONFIG_RES_BYTE_32                     4


#define   CONFIG_2_0_STEREO_CHANNEL_COUNT        2
#define   CONFIG_2_0_STEREO_CHANNEL_MAP          0x03
#define   CONFIG_2_0_STEREO_16_BIT_FREQ_COUNT    4
#define   CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT    3
#define   CONFIG_2_0_STEREO_32_BIT_FREQ_COUNT    1
#define   CONFIG_2_0_STEREO_16_BIT_MAX_PACKET    ((192 + 2) * CONFIG_2_0_STEREO_CHANNEL_COUNT * CONFIG_RES_BYTE_16)
#define   CONFIG_2_0_STEREO_24_BIT_MAX_PACKET    ((96 + 2) * CONFIG_2_0_STEREO_CHANNEL_COUNT * CONFIG_RES_BYTE_24)
#define   CONFIG_2_0_STEREO_32_BIT_MAX_PACKET    ((96 + 2) * CONFIG_2_0_STEREO_CHANNEL_COUNT * CONFIG_RES_BYTE_32)
#define   CONFIG_2_0_SAI_COUNT                   1
#define   CONFIG_2_0_FREQUENCY_DEFAULT           USB_AUDIO_CONFIG_FREQ_48_K
#define   CONFIG_2_0_32BIT_FREQUENCY_DEFAULT     USB_AUDIO_CONFIG_FREQ_96_K

#define   CONFIG_3_1_CHANNEL_COUNT               4
#define   CONFIG_3_1_CHANNEL_MAP                 0x0F
#define   CONFIG_3_1_16_BIT_FREQ_COUNT           3
#define   CONFIG_3_1_24_BIT_FREQ_COUNT           2
#define   CONFIG_3_1_16_BIT_MAX_PACKET           ((96 + 2) * CONFIG_3_1_CHANNEL_COUNT * CONFIG_RES_BYTE_16)
#define   CONFIG_3_1_24_BIT_MAX_PACKET           ((48 + 2) * CONFIG_3_1_CHANNEL_COUNT * CONFIG_RES_BYTE_24)

#define   CONFIG_4_0_QUADRO_CHANNEL_COUNT        4
#define   CONFIG_4_0_QUADRO_CHANNEL_MAP          0x33
#define   CONFIG_4_0_QUADRO_16_BIT_FREQ_COUNT    3
#define   CONFIG_4_0_QUADRO_24_BIT_FREQ_COUNT    2
#define   CONFIG_4_0_QUADRO_16_BIT_MAX_PACKET    ((96 + 2) * CONFIG_4_0_QUADRO_CHANNEL_COUNT * CONFIG_RES_BYTE_16)
#define   CONFIG_4_0_QUADRO_24_BIT_MAX_PACKET    ((48 + 2) * CONFIG_4_0_QUADRO_CHANNEL_COUNT * CONFIG_RES_BYTE_24)
#define   CONFIG_4_0_SAI_COUNT                   2

#define   CONFIG_7_1_SURROUND_CHANNEL_COUNT      8
#define   CONFIG_7_1_SURROUND_CHANNEL_MAP        0xFF
#define   CONFIG_7_1_SURROUND_16_BIT_FREQ_COUNT  2
#define   CONFIG_7_1_SURROUND_16_BIT_MAX_PACKET  ((48 + 2) * CONFIG_7_1_SURROUND_CHANNEL_COUNT * CONFIG_RES_BYTE_16)

#define   DEVICE_ID1                             ((uint32_t)0x1FFF7A10)
#define   DEVICE_ID2                             ((uint32_t)0x1FFF7A14)
#define   DEVICE_ID3                             ((uint32_t)0x1FFF7A18)

#define   USB_AUDIO_CONFIG_SAI_MAX_COUNT         CONFIG_4_0_SAI_COUNT
#define   USB_AUDIO_CONFIG_PLAY_BUFFER_SIZE      ((1024 * 10) * USB_AUDIO_CONFIG_SAI_MAX_COUNT)

#define   AUDIO_CONFIG_2_0_STEREO_32_BIT         0
#define   AUDIO_CONFIG_2_0_STEREO                1
#define   AUDIO_CONFIG_3_1                       2
#define   AUDIO_CONFIG_4_0_QUADRO                3
#define   AUDIO_CONFIG_7_1                       4
#define   AUDIO_CONFIG_TDM_START_INDEX           5
#define   AUDIO_CONFIG_2_0_STEREO_32_BIT_TDM     (AUDIO_CONFIG_2_0_STEREO_32_BIT + AUDIO_CONFIG_TDM_START_INDEX)
#define   AUDIO_CONFIG_2_0_STEREO_TDM            (AUDIO_CONFIG_2_0_STEREO + AUDIO_CONFIG_TDM_START_INDEX)
#define   AUDIO_CONFIG_3_1_TDM                   (AUDIO_CONFIG_3_1 + AUDIO_CONFIG_TDM_START_INDEX)
#define   AUDIO_CONFIG_4_0_QUADRO_TDM            (AUDIO_CONFIG_4_0_QUADRO + AUDIO_CONFIG_TDM_START_INDEX)
#define   AUDIO_CONFIG_7_1_TDM                   (AUDIO_CONFIG_7_1 + AUDIO_CONFIG_TDM_START_INDEX)

#define   CHANNELS_PREPARE_DATA_BUF_SIZE         ((48 + 2) * CONFIG_7_1_SURROUND_CHANNEL_COUNT * (CONFIG_RES_BYTE_24 + 1))//1024


enum SYNC_MODES
{
  MASTER_INT_SYNC,
  MASTER_EXT_SYNC,
  SLAVE_SYNC,
};


typedef struct
{
  uint8_t IDs[CONTROLLER_VID_SIZE + CONTROLLER_PID_SIZE];
  //uint8_t ManufactSize;
  uint8_t ManufactString[USB_MANUFACTURE_MAX_LENGTH];
  //uint8_t DevNameSize;
  uint8_t DevNameString[USB_DEVICE_NAME_MAX_LENGTH];
  
} USBDSettings;



void SetAudioConfigDependedFuncs(AUDIO_SpeakerNode_t *speaker);

void Play_SAIMaster(uint16_t *Data, uint16_t Size, uint8_t ResByte);

void Play_SAIMasterAndSlave(uint16_t *Data, uint16_t Size, uint8_t ResByte);

void PrepareMultiChannelData(uint8_t* AudioData, uint16_t Size, uint8_t ResInBytes);

void AudioChangeFrequency(uint32_t AudioFrequency);

void AudioChangeResolution(uint8_t AudioResolution);

void AudioOutMute(uint8_t MuteFlag);

uint16_t GetRemainingTxSize(void);

uint16_t GetLastTxSize(void);

void AudioOutInit(uint32_t AudioFrequency, uint8_t AudioResolution);

void PlayDescriptionInit(AUDIO_Description_t *Description);

uint8_t GetAudioConfiguration(void);

void MakeSerialNumber(uint32_t *Buffer);

uint8_t *GetUSB_IDs(void);

uint8_t *GetManufactString(void);

uint8_t *GetAudioDevName(void);

void AudioConfig_Init(void);

void BootConfig(void);

void BootControllerConfig(void);



#endif // __AUDIO_CONFIGURATION_H

