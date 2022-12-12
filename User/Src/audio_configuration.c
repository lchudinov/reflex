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



#include "audio_configuration.h"
#include "usbd_audio.h"
#include "SAI.h"
#include "I2C.h"
#include "I2C_Memory.h"
#include "Events.h"
#include "DAC.h"



static uint8_t AudioConfiguration = 0; // was 0xFF
static uint8_t VolumeFeature = 0;
static uint8_t SyncMode = 0;
static uint8_t SAICountUsed = 2;
static uint8_t ChannelsPairs = 2;
static uint8_t ChnlsData[CHANNELS_PREPARE_DATA_BUF_SIZE];


static USBDSettings USBInfo =
{
  .IDs = { LOBYTE(USB_VID_ST), HIBYTE(USB_VID_ST), LOBYTE(USB_PID_CHIPDIP), HIBYTE(USB_PID_CHIPDIP) },
  .ManufactString = USB_MANUFAC_DEFAULT,
  .DevNameString = USB_DEVICE_NAME_DEFAULT,
};


void SetAudioConfigDependedFuncs(AUDIO_SpeakerNode_t *speaker)
{
  switch(AudioConfiguration)
  {
    
    case AUDIO_CONFIG_2_0_SPDIF:
      speaker->SpeakerPlay = Play_SAIMaster;
      speaker->SpeakerPrepareData = PrepareSPDIF_24bitData;
    break;
    
    case AUDIO_CONFIG_3_1:
    case AUDIO_CONFIG_4_0_QUADRO:
    case AUDIO_CONFIG_7_1:
      speaker->SpeakerPlay = Play_SAIMasterAndSlave;
      speaker->SpeakerPrepareData = PrepareMultiChannelData;
    break;
  
    default:
      speaker->SpeakerPlay = Play_SAIMaster;
      speaker->SpeakerPrepareData = 0;
    break;
  }
}
//------------------------------------------------------------------------------
void Play_SAIMaster(uint16_t *Data, uint16_t Size, uint8_t ResByte)
{
  if (ResByte == 3)
    ResByte = 4;
  
  uint16_t TxSize = Size / CONFIG_2_0_SAI_COUNT / ResByte;
  
  SAI_MasterDMAPrepareTx(Data, TxSize);
  SAI_DMAEnable(SAI_MASTER);
}
//------------------------------------------------------------------------------
void Play_SAIMasterAndSlave(uint16_t *Data, uint16_t Size, uint8_t ResByte)
{
  if (ResByte == 3)
    ResByte = 4;
  
  uint16_t TxSize = Size / ChannelsPairs / ResByte;

  SAI_MasterDMAPrepareTx(&Data[0], TxSize);
  SAI_SlaveDMAPrepareTx(&Data[(ResByte / 2) * TxSize], TxSize);
  
  SAI_DMAEnable(SAI_SLAVE);
  SAI_DMAEnable(SAI_MASTER);
}
//------------------------------------------------------------------------------
void PrepareSPDIF_24bitData(uint8_t* AudioData, uint16_t Size, uint8_t ResInBytes)
{
  for (uint16_t i = 0; i < Size; i += 4)
    (*(uint32_t *)((uint32_t)&AudioData[i])) >>= 8;
}
//------------------------------------------------------------------------------
void PrepareMultiChannelData(uint8_t* AudioData, uint16_t Size, uint8_t ResInBytes)
{  
  uint16_t ChnlPairSize = Size / ChannelsPairs;
    
  if (ResInBytes == 3)
    ResInBytes = 4;
  
  uint8_t DataIncrement = ResInBytes * ChannelsPairs * 2;
  uint8_t BytesPerSAI = DataIncrement / ChannelsPairs;
  
  for (uint16_t i = 0; i < Size; i += DataIncrement)
  {
    uint16_t BaseAddr = i / ChannelsPairs;
    
    for (uint8_t ChnlPair = 0; ChnlPair < ChannelsPairs; ChnlPair++)
    {
      uint16_t ChnlPairOffset = ChnlPair * ChnlPairSize;
      uint16_t DataOffset = ChnlPair * BytesPerSAI;
      
      ChnlsData[ChnlPairOffset + BaseAddr] =     AudioData[i + DataOffset];
      ChnlsData[ChnlPairOffset + BaseAddr + 1] = AudioData[i + DataOffset + 1];
      ChnlsData[ChnlPairOffset + BaseAddr + 2] = AudioData[i + DataOffset + 2];
      ChnlsData[ChnlPairOffset + BaseAddr + 3] = AudioData[i + DataOffset + 3];
      
      if (ResInBytes == 4)
      {
        ChnlsData[ChnlPairOffset + BaseAddr + 4] = AudioData[i + DataOffset + 4];
        ChnlsData[ChnlPairOffset + BaseAddr + 5] = AudioData[i + DataOffset + 5];
        ChnlsData[ChnlPairOffset + BaseAddr + 6] = AudioData[i + DataOffset + 6];
        ChnlsData[ChnlPairOffset + BaseAddr + 7] = AudioData[i + DataOffset + 7];
      }
    }
  }
  
  memcpy(AudioData, ChnlsData, Size);
}
//------------------------------------------------------------------------------
void AudioChangeFrequency(uint32_t AudioFrequency)
{
  SAI_Disable(SAI_MASTER);
  if (SAICountUsed == 2)
    SAI_Disable(SAI_SLAVE);
    
  if (SyncMode == MASTER_INT_SYNC)
  {
    SAI_PLLSAIConfig(AudioFrequency);
    SAI_ChangeFrequency(AudioFrequency);
  }
  
  Event_FreqChanged(AudioFrequency);
    
  if (SAICountUsed == 2)
    SAI_Enable(SAI_SLAVE);
  
  SAI_Enable(SAI_MASTER);
}
//------------------------------------------------------------------------------
void AudioChangeResolution(uint8_t AudioResolution)
{
  SAI_Disable(SAI_MASTER);
  
  if (AudioConfiguration < AUDIO_CONFIG_TDM_START_INDEX)
  {
    if (SAICountUsed == 2)
      SAI_Disable(SAI_SLAVE);
  
    SAI_Init_I2S(SAI_MASTER, AudioResolution);
    SAI_DMAChangeDataSize(SAI_MASTER_DMA_STREAM, AudioResolution);
  
    if (SAICountUsed == 2)
    {
      SAI_Init_I2S(SAI_SLAVE, AudioResolution);
      SAI_DMAChangeDataSize(SAI_SLAVE_DMA_STREAM, AudioResolution);
      SAI_Enable(SAI_SLAVE);
    }
  }
  else if (AudioConfiguration == AUDIO_CONFIG_2_0_SPDIF)
    SAI_DMAChangeDataSize(SAI_MASTER_DMA_STREAM, AudioResolution);
  else
  {
    SAI_Init_TDM(SAI_MASTER, AudioResolution, 2 * ChannelsPairs);
    SAI_DMAChangeDataSize(SAI_MASTER_DMA_STREAM, AudioResolution);
  }
  
  SAI_Enable(SAI_MASTER);
  
  Event_ResChanged(AudioResolution);
}
//------------------------------------------------------------------------------
void AudioOutMute(uint8_t MuteFlag)
{
  SAI_Mute(SAI_MASTER, MuteFlag);
  
  if (SAICountUsed == 2)
    SAI_Mute(SAI_SLAVE, MuteFlag);
  
  Event_MuteChanged(MuteFlag);
}
//------------------------------------------------------------------------------
uint16_t GetRemainingTxSize(void)
{
  uint16_t TxSize = SAI_GetRemainingTxSize();
  
  if ((AudioConfiguration >= AUDIO_CONFIG_TDM_START_INDEX) && (AudioConfiguration != AUDIO_CONFIG_2_0_SPDIF))
    TxSize /= ChannelsPairs;
  
  return TxSize;
}
//------------------------------------------------------------------------------
uint16_t GetLastTxSize(void)
{
  uint16_t TxSize = SAI_GetLastTransferSize();
  
  if ((AudioConfiguration >= AUDIO_CONFIG_TDM_START_INDEX) && (AudioConfiguration != AUDIO_CONFIG_2_0_SPDIF))
    TxSize /= ChannelsPairs;
  
  return TxSize;
}
//------------------------------------------------------------------------------
void AudioOutInit(uint32_t AudioFrequency, uint8_t AudioResolution)
{
  if (SyncMode == MASTER_INT_SYNC)
    SAI_PLLSAIConfig(AudioFrequency);
  else if (SyncMode == MASTER_EXT_SYNC)
    SAI_ExternalSyncInit();
  
  SAI_MasterGPIOInit();
  SAI_MasterDMAInit(AudioResolution);
  
  if ((AudioConfiguration < AUDIO_CONFIG_TDM_START_INDEX)
   || (AudioConfiguration == AUDIO_CONFIG_2_0_SPDIF))
  {
    SAI_MasterInit(AudioResolution, ChannelsPairs);
  
    if (SAICountUsed == 2)
    {
      SAI_SlaveGPIOInit();
      SAI_SlaveDMAInit(AudioResolution);
      SAI_SlaveInit(AudioResolution);
      SAI_Enable(SAI_SLAVE);
    }
  }
  else
    SAI_MasterInit(AudioResolution, 2 * ChannelsPairs);
  
  if (SyncMode == MASTER_INT_SYNC)
    SAI_ChangeFrequency(AudioFrequency);
  else if (SyncMode == SLAVE_SYNC)
    SAI_MasterSetSlaveSync();
  
  Event_FreqChanged(AudioFrequency);
  Event_ResChanged(AudioResolution);
  
  SAI_Enable(SAI_MASTER);
}
//------------------------------------------------------------------------------
void PlayDescriptionInit(AUDIO_Description_t *Description)
{
  uint8_t AudioConf = AudioConfiguration;
  
  if (AudioConf == AUDIO_CONFIG_2_0_SPDIF)
    AudioConf = AUDIO_CONFIG_2_0_STEREO;
  else if (AudioConf >= AUDIO_CONFIG_TDM_START_INDEX)
    AudioConf -= AUDIO_CONFIG_TDM_START_INDEX;
  
  switch(AudioConf)
  {
    case AUDIO_CONFIG_2_0_STEREO_32_BIT:
    case AUDIO_CONFIG_2_0_STEREO:
    default:
      Description->channels_count = CONFIG_2_0_STEREO_CHANNEL_COUNT;
      Description->channels_map = CONFIG_2_0_STEREO_CHANNEL_MAP;
    break;
    
    case AUDIO_CONFIG_3_1:
      Description->channels_count = CONFIG_3_1_CHANNEL_COUNT;
      Description->channels_map = CONFIG_3_1_CHANNEL_MAP;
    break;
    
    case AUDIO_CONFIG_4_0_QUADRO:
      Description->channels_count = CONFIG_4_0_QUADRO_CHANNEL_COUNT;
      Description->channels_map = CONFIG_4_0_QUADRO_CHANNEL_MAP;
    break;
    
    case AUDIO_CONFIG_7_1:
      Description->channels_count = CONFIG_7_1_SURROUND_CHANNEL_COUNT;
      Description->channels_map = CONFIG_7_1_SURROUND_CHANNEL_MAP;
    break;
  }
    
  Description->resolution = CONFIG_RES_BYTE_24;//CONFIG_RES_BYTE_16;
  Description->frequency = CONFIG_2_0_FREQUENCY_DEFAULT;
  Description->audio_type = USBD_AUDIO_FORMAT_TYPE_PCM;
  Description->audio_volume_db_256 = VOLUME_SPEAKER_DEFAULT_DB_256;
  Description->audio_mute = 0;
  
  if (AudioConf == AUDIO_CONFIG_2_0_STEREO_32_BIT)
  {
    Description->resolution = CONFIG_RES_BYTE_32;
    Description->frequency = CONFIG_2_0_32BIT_FREQUENCY_DEFAULT;
  }
  else if ((AudioConfiguration == AUDIO_CONFIG_7_1) || (AudioConfiguration == AUDIO_CONFIG_7_1_TDM))
    Description->resolution = CONFIG_RES_BYTE_16;
}
//------------------------------------------------------------------------------
uint8_t GetAudioConfiguration(void)
{
  return AudioConfiguration;
}
//------------------------------------------------------------------------------
uint8_t GetVolumeFeature(void)
{
  return VolumeFeature;
}
//------------------------------------------------------------------------------
void MakeSerialNumber(uint32_t *Buffer)
{
  Buffer[0] = (*(uint32_t*)DEVICE_ID1) + (*(uint32_t*)DEVICE_ID3);
  Buffer[1] = (((*(uint32_t*)DEVICE_ID2) >> 16) + AudioConfiguration);
  
  if (VolumeFeature != 0)
    Buffer[1] += AUDIO_CONFIG_HWV_START_INDEX;
  
  Buffer[1] <<= 16;
}
//------------------------------------------------------------------------------
uint8_t *GetUSB_IDs(void)
{
  return USBInfo.IDs;
}
//------------------------------------------------------------------------------
uint8_t *GetManufactString(void)
{
  return USBInfo.ManufactString;
}
//------------------------------------------------------------------------------
uint8_t *GetAudioDevName(void)
{
  return USBInfo.DevNameString;
}
//------------------------------------------------------------------------------
void AudioConfig_Init(void)
{
  SAISettings Settings;
  Settings.BclkFsRatio = BCLK_Fs_RES_DEPENDENT;
  Settings.BclkPol = CKSTR_1_FALLING;
  Settings.TdmLrMode = TDM_LR_PULSE;
  Settings.Format = SAI_I2S;
  
  // why would we need to read CONFIG_GPIO->IDR
  AudioConfiguration = CONFIG_GPIO->IDR & AUDIO_CONFIG_MASK;
      
  switch(AudioConfiguration)
  {
    case (AUDIO_CONFIG_1_MASK | AUDIO_CONFIG_3_MASK):
      AudioConfiguration = AUDIO_CONFIG_2_0_STEREO_32_BIT;
      SAICountUsed = 1;
      ChannelsPairs = 1;
    break;
   
    case AUDIO_CONFIG_MASK:
    default:
      AudioConfiguration = AUDIO_CONFIG_2_0_STEREO;
      SAICountUsed = 1;
      ChannelsPairs = 1;
    break;
    
    case (AUDIO_CONFIG_2_MASK | AUDIO_CONFIG_3_MASK):
      AudioConfiguration = AUDIO_CONFIG_3_1;
      ChannelsPairs = 2;
    break;
    
    case AUDIO_CONFIG_3_MASK:
      AudioConfiguration = AUDIO_CONFIG_4_0_QUADRO;
      ChannelsPairs = 2;
    break;
    
    case AUDIO_CONFIG_1_MASK:
      AudioConfiguration = AUDIO_CONFIG_7_1;
      ChannelsPairs = 4;
    break;
    
    case 0:
      AudioConfiguration = AUDIO_CONFIG_2_0_SPDIF;
      SAICountUsed = 1;
      ChannelsPairs = 1;
      Settings.Format = SAI_SPDIF;
    break;    
  }
  
  if ((AudioConfiguration != AUDIO_CONFIG_2_0_SPDIF)
  && ((CONFIG_GPIO->IDR & (1 << TDM_MODE_PIN)) != (1 << TDM_MODE_PIN)))
  {
    AudioConfiguration += AUDIO_CONFIG_TDM_START_INDEX;
    SAICountUsed = 1;
    Settings.Format = SAI_TDM;
    
    TDM_LR_CLK_MODE_GPIO->PUPDR |= (1 << (2 * TDM_LR_CLK_MODE_PIN));
    while((TDM_LR_CLK_MODE_GPIO->PUPDR & (1 << (2 * TDM_LR_CLK_MODE_PIN))) != (1 << (2 * TDM_LR_CLK_MODE_PIN)));
  }
  
  uint16_t SyncConfig = CONFIG_GPIO->IDR & SYNC_MODE_MASK;
  switch (SyncConfig)
  {
    case SYNC_MODE_MASK:
    default:
      SyncMode = MASTER_INT_SYNC;
    break;
    
    case SYNC_MODE_2_MASK:
      SyncMode = MASTER_EXT_SYNC;
    break;
    
    case SYNC_MODE_1_MASK:
      SyncMode = SLAVE_SYNC;
    break;
  }
  
  if ((BCLK_Fs_RATIO_GPIO->IDR & (1 << BCLK_Fs_RATIO_PIN)) != (1 << BCLK_Fs_RATIO_PIN))
    Settings.BclkFsRatio = BCLK_Fs_FIXED;
  
  if ((BCLK_POLARITY_GPIO->IDR & (1 << BCLK_POLARITY_PIN)) != (1 << BCLK_POLARITY_PIN))
    Settings.BclkPol = CKSTR_0_RISING;
  
  if ((AudioConfiguration != AUDIO_CONFIG_2_0_SPDIF)
  && ((CONFIG_GPIO->IDR & (1 << TDM_MODE_PIN)) != (1 << TDM_MODE_PIN)))
  {
    if ((TDM_LR_CLK_MODE_GPIO->IDR & (1 << TDM_LR_CLK_MODE_PIN)) != (1 << TDM_LR_CLK_MODE_PIN))
      Settings.TdmLrMode = TDM_LR_CLOCK;
  }
  
  if ((HW_VOL_CTRL_GPIO->IDR & (1 << HW_VOL_CTRL_PIN)) != (1 << HW_VOL_CTRL_PIN))
  {
    VolumeFeature = USBD_AUDIO_CONTROL_FEATURE_UNIT_VOLUME;
    DAC_Init();
  }
  
  SAI_InitSettings(&Settings);
  
  BootConfig();
}
//------------------------------------------------------------------------------
void BootConfig(void)
{
  if (Memory_IsReady() == I2C_DEVICE_READY)
  {
    if (Memory_GetConfigSize() != 0xFFFFFFFF)
    {
      BootControllerConfig();
    }
  }
}
//------------------------------------------------------------------------------
void BootControllerConfig(void)
{
  TransferType MemTransfer;
  
  MemTransfer.Address = CONTROLLER_CONF_ADR_OFFSET;
  MemTransfer.Size = CONTROLLER_CONF_MAP_SIZE;  
  Memory_Read(&MemTransfer);
  uint16_t ConfigAddress = (uint16_t)JoinBytesIntoValue(MemTransfer.Data, CONTROLLER_CONF_ADR_SIZE);
    
  MemTransfer.Address = ConfigAddress + CONTROLLER_VID_OFFSET;
  MemTransfer.Size = FIRST_AUDIO_NAME_MAP_OFFSET - CONTROLLER_VID_OFFSET;
  Memory_Read(&MemTransfer);
  
  for (uint8_t i = 0 ; i < (CONTROLLER_VID_SIZE + CONTROLLER_PID_SIZE); i++)
    USBInfo.IDs[i] = MemTransfer.Data[i];
  
  uint8_t StringSize = MemTransfer.Data[CONTROLLER_MANUFACT_SIZE_OFFSET - CONTROLLER_VID_OFFSET];
  
  for (uint8_t i = 0 ; i < StringSize; i++)
    USBInfo.ManufactString[i] = MemTransfer.Data[CONTROLLER_MANUFACT_OFFSET - CONTROLLER_VID_OFFSET + i];
  
  MemTransfer.Address = ConfigAddress + FIRST_AUDIO_NAME_MAP_OFFSET + AudioConfiguration * AUDIO_NAME_MAP_SIZE;
  MemTransfer.Size = AUDIO_NAME_MAP_SIZE;
  Memory_Read(&MemTransfer);
  
  for (uint8_t i = 0 ; i < MemTransfer.Data[AUDIO_NAME_SIZE_OFFSET]; i++)
  {
    USBInfo.DevNameString[i] = MemTransfer.Data[AUDIO_NAME_OFFSET + i];
    if ((i == 0) && (USBInfo.DevNameString[0] == 0xFF))
    {
      USBInfo.DevNameString[0] = 0x00;
      break;
    }
  }
}



