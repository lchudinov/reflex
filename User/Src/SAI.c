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



#include "SAI.h"
#include "stm32f4xx_hal_cortex.h"
#include "usb_audio_constants.h"

static uint16_t LastTransferSize = 0;
static SAISettings SAISets;



void SAI_InitSettings(SAISettings *Settings)
{
  SAISets.BclkFsRatio = Settings->BclkFsRatio;
  SAISets.BclkPol = Settings->BclkPol;
  SAISets.TdmLrMode = Settings->TdmLrMode;
  SAISets.Format = Settings->Format;
}
//------------------------------------------------------------------------------
void SAI_PLLSAIConfig(uint32_t AudioFrequency)
{
  RCC->CR &= ~RCC_CR_PLLSAION;
  while((RCC->CR & RCC_CR_PLLSAIRDY) == RCC_CR_PLLSAIRDY);

  RCC->DCKCFGR &= ~RCC_DCKCFGR_PLLSAIDIVQ;
  
  switch(AudioFrequency)
  {
    //48, 96, 192
    default:
      RCC->PLLSAICFGR = SAI_MCLK_49_152MHz;
    break;
    
    case USB_AUDIO_CONFIG_FREQ_44_1_K:
      {
        if (SAISets.Format != SAI_SPDIF)
        {
          RCC->PLLSAICFGR = RCC_PLLSAICFGR_PLLSAIQ_1 | (0x1AD << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3;
          RCC->DCKCFGR |= 0x12 << RCC_DCKCFGR_PLLSAIDIVQ_Pos;
        }
        else
          RCC->PLLSAICFGR = SAI_MCLK_22_5792MHz;
      }
    break;
    
    case USB_AUDIO_CONFIG_FREQ_88_2_K:
      if (SAISets.Format != SAI_SPDIF)
        RCC->PLLSAICFGR = SAI_MCLK_22_5792MHz;
      else
        RCC->PLLSAICFGR = SAI_MCLK_45_1584MHz;
    break;
    
    case USB_AUDIO_CONFIG_FREQ_176_4_K:
      RCC->PLLSAICFGR = SAI_MCLK_45_1584MHz;
    break;
  }
    
  RCC->CR |= RCC_CR_PLLSAION;
  while((RCC->CR & RCC_CR_PLLSAIRDY) != RCC_CR_PLLSAIRDY);
}
//------------------------------------------------------------------------------
void SAI_ChangeFrequency(uint32_t AudioFrequency)
{
  SAI_MASTER->CR1 &= ~SAI_xCR1_MCKDIV;
  
  uint32_t NewMCKDIV = 0;
  
  if ((AudioFrequency != USB_AUDIO_CONFIG_FREQ_44_1_K)
   && (AudioFrequency != USB_AUDIO_CONFIG_FREQ_88_2_K)
   && (AudioFrequency != USB_AUDIO_CONFIG_FREQ_176_4_K))
  {
    NewMCKDIV = (2 - (AudioFrequency / 48000 / 2));
    if (SAISets.Format == SAI_SPDIF)
      NewMCKDIV -= 1;
    
    NewMCKDIV <<= SAI_xCR1_MCKDIV_Pos;
  }
  
  SAI_MASTER->CR1 |= NewMCKDIV;
}
//------------------------------------------------------------------------------
void SAI_ExternalSyncInit(void)
{
  EXT_SYNC_GPIO->MODER |= (2 << (2 * EXT_SYNC_PIN));
  EXT_SYNC_GPIO->AFR[1] |= (EXT_SYNC_AF << (4 * (EXT_SYNC_PIN - 8)));
  RCC->DCKCFGR |= RCC_DCKCFGR_SAI1SRC_0 | RCC_DCKCFGR_SAI1SRC_1;
}
//------------------------------------------------------------------------------
uint16_t SAI_GetLastTransferSize(void)
{
  return LastTransferSize;
}
//------------------------------------------------------------------------------
uint16_t SAI_GetRemainingTxSize(void)
{
  return SAI_MASTER_DMA_STREAM->NDTR;
}
//------------------------------------------------------------------------------
void SAI_MasterDMAPrepareTx(uint16_t *Data, uint16_t Size)
{
  SAI_DMAPrepareTx(SAI_MASTER_DMA_STREAM, Data, Size);
  LastTransferSize = Size;
}
//------------------------------------------------------------------------------
void SAI_SlaveDMAPrepareTx(uint16_t *Data, uint16_t Size)
{
  SAI_DMAPrepareTx(SAI_SLAVE_DMA_STREAM, Data, Size);
}
//------------------------------------------------------------------------------
void SAI_DMAPrepareTx(DMA_Stream_TypeDef *DMAStream, uint16_t *Data, uint16_t Size)
{
  DMAStream->NDTR = Size;
  DMAStream->M0AR = (uint32_t)(&Data[0]);
  DMAStream->CR |= DMA_SxCR_EN;
}
//------------------------------------------------------------------------------
void SAI_Enable(SAI_Block_TypeDef *SAIBlock)
{
  SAIBlock->CR1 |= SAI_xCR1_SAIEN;
  while((SAIBlock->CR1 & SAI_xCR1_SAIEN) != SAI_xCR1_SAIEN);
}
//------------------------------------------------------------------------------
// 1 - mute, 0 - unmute
void SAI_Mute(SAI_Block_TypeDef *SAIBlock, uint8_t MuteFlag)
{
  if (MuteFlag)
    SAIBlock->CR2 |= SAI_xCR2_MUTE;
  else
    SAIBlock->CR2 &= ~SAI_xCR2_MUTE;
}
//------------------------------------------------------------------------------
void SAI_Disable(SAI_Block_TypeDef *SAIBlock)
{
  SAIBlock->CR1 &= ~SAI_xCR1_SAIEN;
  while((SAIBlock->CR1 & SAI_xCR1_SAIEN) == SAI_xCR1_SAIEN);
}
//------------------------------------------------------------------------------
void SAI_MasterInit(uint8_t AudioResolution, uint8_t ChnlCount)
{
  RCC->APB2ENR |= RCC_APB2ENR_SAI1EN;
  while((RCC->APB2ENR & RCC_APB2ENR_SAI1EN) != RCC_APB2ENR_SAI1EN);
  
  SAI_Disable(SAI_MASTER);
  
  switch(SAISets.Format)
  {
    case SAI_I2S:
    default:
      SAI_Init_I2S(SAI_MASTER, AudioResolution);
    break;
    
    case SAI_TDM:
      SAI_Init_TDM(SAI_MASTER, AudioResolution, ChnlCount);
    break;
    
    case SAI_SPDIF:
      SAI_MASTER->CR1 = SAI_xCR1_PRTCFG_0;
    break;
  }  
}
//------------------------------------------------------------------------------
void SAI_MasterSetSlaveSync(void)
{
  SAI_MASTER->CR1 |= SAI_xCR1_MODE_1;
  if (SAISets.BclkPol == CKSTR_1_FALLING)
    SAI_MASTER->CR1 |= SAI_xCR1_CKSTR;
}
//------------------------------------------------------------------------------
void SAI_SlaveInit(uint8_t AudioResolution)
{
  SAI_Disable(SAI_SLAVE);
  SAI_SLAVE->CR1 = SAI_xCR1_MODE_1 | SAI_xCR1_SYNCEN_0;
  SAI_Init_I2S(SAI_SLAVE, AudioResolution);
}
//------------------------------------------------------------------------------
void SAI_Init_I2S(SAI_Block_TypeDef *SAIBlock, uint8_t AudioResolution)
{
  SAIBlock->CR2 = SAI_xCR2_FTH_0;
  SAIBlock->FRCR = SAI_xFRCR_FSOFF | SAI_xFRCR_FSDEF;
  
  if (SAISets.BclkPol == CKSTR_1_FALLING)
    SAIBlock->CR1 |= SAI_xCR1_CKSTR;
  
  SAIBlock->CR1 &= ~(SAI_xCR1_DS_2 | SAI_xCR1_DS_1 | SAI_xCR1_DS_0);

  if (AudioResolution == 16)
  {
    SAIBlock->CR1 |= SAI_xCR1_DS_2;
    
    if (SAISets.BclkFsRatio == BCLK_Fs_RES_DEPENDENT)
    {
      SAIBlock->FRCR |= (0x0F << SAI_xFRCR_FSALL_Pos) | (0x1F << SAI_xFRCR_FRL_Pos);
      SAIBlock->SLOTR = (((1 << 0) | (1 << 1)) << SAI_xSLOTR_SLOTEN_Pos) | (0x01 << SAI_xSLOTR_NBSLOT_Pos) | SAI_xSLOTR_SLOTSZ_0;
    }
    else //if (SAISets.BclkFsRatio == BCLK_Fs_FIXED)
    {
      SAIBlock->FRCR |= (0x1F << SAI_xFRCR_FSALL_Pos) | (0x3F << SAI_xFRCR_FRL_Pos);
      SAIBlock->SLOTR = (((1 << 0) | (1 << 2)) << SAI_xSLOTR_SLOTEN_Pos) | (0x03 << SAI_xSLOTR_NBSLOT_Pos) | SAI_xSLOTR_SLOTSZ_0;
    }
  }
  else
  {
    SAIBlock->FRCR |= (0x1F << SAI_xFRCR_FSALL_Pos) | (0x3F << SAI_xFRCR_FRL_Pos);
    SAIBlock->CR1 |= SAI_xCR1_DS_2 | SAI_xCR1_DS_1 | SAI_xCR1_DS_0;
    SAIBlock->SLOTR = (((1 << 0) | (1 << 1)) << SAI_xSLOTR_SLOTEN_Pos) | (0x01 << SAI_xSLOTR_NBSLOT_Pos) | SAI_xSLOTR_SLOTSZ_1;
  } 

  SAIBlock->CR1 |= SAI_xCR1_OUTDRIV;
}
//------------------------------------------------------------------------------
void SAI_Init_TDM(SAI_Block_TypeDef *SAIBlock, uint8_t AudioResolution, uint8_t ChnlCount)
{
  if (AudioResolution == 24)
    AudioResolution = 32;
  
  SAIBlock->CR2 = SAI_xCR2_FTH_0;
  
  uint16_t FrameLength = AudioResolution * ChnlCount;
  if ((AudioResolution == 16) && (SAISets.BclkFsRatio == BCLK_Fs_FIXED))
    FrameLength *= 2;
  
  if (SAISets.TdmLrMode == TDM_LR_PULSE)
    SAIBlock->FRCR = SAI_xFRCR_FSOFF | SAI_xFRCR_FSPOL | \
    ((0x00 << SAI_xFRCR_FSALL_Pos) | ((FrameLength - 1) << SAI_xFRCR_FRL_Pos));
  else //if (SAISets.TdmLrMode == TDM_LR_CLOCK)
    SAIBlock->FRCR = SAI_xFRCR_FSDEF | \
    ((FrameLength / 2 - 1) << SAI_xFRCR_FSALL_Pos) | ((FrameLength - 1) << SAI_xFRCR_FRL_Pos);
  
  if (SAISets.BclkPol == CKSTR_1_FALLING)
    SAIBlock->CR1 |= SAI_xCR1_CKSTR;
  
  SAIBlock->CR1 &= ~(SAI_xCR1_DS_2 | SAI_xCR1_DS_1 | SAI_xCR1_DS_0);
  
  uint16_t SlotMask = 0;
  for (uint8_t i = 0; i < ChnlCount; i++)
    SlotMask |= 1 << i;
  
  if (AudioResolution == 16)
  {
    SAIBlock->CR1 |= SAI_xCR1_DS_2;
    
    if (SAISets.BclkFsRatio == BCLK_Fs_FIXED)
    {
      ChnlCount *= 2;
      SlotMask = 0;
      for (uint8_t i = 0; i < ChnlCount; i+= 2)
        SlotMask |= 1 << i;
    }
    
    SAIBlock->SLOTR = (SlotMask << SAI_xSLOTR_SLOTEN_Pos) | ((ChnlCount - 1) << SAI_xSLOTR_NBSLOT_Pos) | SAI_xSLOTR_SLOTSZ_0;
  }
  else
  {
    SAIBlock->CR1 |= SAI_xCR1_DS_2 | SAI_xCR1_DS_1 | SAI_xCR1_DS_0;
    SAIBlock->SLOTR = (SlotMask << SAI_xSLOTR_SLOTEN_Pos) | ((ChnlCount - 1) << SAI_xSLOTR_NBSLOT_Pos) | SAI_xSLOTR_SLOTSZ_1;
  } 

  SAIBlock->CR1 |= SAI_xCR1_OUTDRIV;
}
//------------------------------------------------------------------------------
void SAI_DMAEnable(SAI_Block_TypeDef *SAIBlock)
{
  SAIBlock->CR1 |= SAI_xCR1_DMAEN;
}
//------------------------------------------------------------------------------
void SAI_MasterDMAInit(uint8_t AudioResolution)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
  while((RCC->AHB1ENR & RCC_AHB1ENR_DMA2EN) != RCC_AHB1ENR_DMA2EN);
  
  SAI_DMAInit(SAI_MASTER_DMA_STREAM, AudioResolution);
  
  SAI_MASTER_DMA_STREAM->CR |= DMA_SxCR_TCIE;
  SAI_MASTER_DMA_STREAM->PAR = (uint32_t)(&(SAI_MASTER->DR));
  
  HAL_NVIC_SetPriority(SAI_MASTER_DMA_IRQ, SAI_IRQ_PRIORITY, 0);
  HAL_NVIC_EnableIRQ(SAI_MASTER_DMA_IRQ);    
}
//------------------------------------------------------------------------------
void SAI_SlaveDMAInit(uint8_t AudioResolution)
{
  SAI_DMAInit(SAI_SLAVE_DMA_STREAM, AudioResolution);
  SAI_SLAVE_DMA_STREAM->PAR = (uint32_t)(&(SAI_SLAVE->DR));
}
//------------------------------------------------------------------------------
void SAI_DMAInit(DMA_Stream_TypeDef *DMAStream, uint8_t AudioResolution)
{  
  DMAStream->CR = DMA_SxCR_PL_1 | DMA_SxCR_MINC | DMA_SxCR_DIR_0;
  
  if (AudioResolution == 16)
    DMAStream->CR |= DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0;
  else
    DMAStream->CR |= DMA_SxCR_MSIZE_1 | DMA_SxCR_PSIZE_1;
      
  DMAStream->FCR = DMA_SxFCR_DMDIS | DMA_SxFCR_FTH;
}
//------------------------------------------------------------------------------
void SAI_DMAChangeDataSize(DMA_Stream_TypeDef *DMAStream, uint8_t Resolution)
{ 
  //SAI_DMAChangeDataSize вызывается в прерывании по окончанию передачи (TC)
  //поток уже неактивен, поэтому можно изменять регистр CR.
    
  DMAStream->CR &= ~(DMA_SxCR_MSIZE_Msk | DMA_SxCR_PSIZE_Msk);
  
  if (Resolution == 16)
    DMAStream->CR |= DMA_SxCR_MSIZE_0 | DMA_SxCR_PSIZE_0;
  else
    DMAStream->CR |= DMA_SxCR_MSIZE_1 | DMA_SxCR_PSIZE_1;
}
//------------------------------------------------------------------------------
void SAI_MasterGPIOInit(void)
{
  SAI_MASTER_MCLK_GPIO->MODER |= (2 << (2 * SAI_MASTER_MCK_PIN));
  SAI_MASTER_MCLK_GPIO->AFR[0] |= (SAI_MASTER_MCLK_SCK_SD_FS_AF << (4 * SAI_MASTER_MCK_PIN));
  SAI_MASTER_MCLK_GPIO->OSPEEDR |= (3 << (2 * SAI_MASTER_MCK_PIN));
  
  SAI_MASTER_SCK_FS_GPIO->MODER |= (2 << (2 * SAI_MASTER_SCK_PIN)) | (2 << (2 * SAI_MASTER_FS_PIN));
  SAI_MASTER_SCK_FS_GPIO->AFR[1] |= (SAI_MASTER_MCLK_SCK_SD_FS_AF << (4 * (SAI_MASTER_SCK_PIN - 8))) | \
                                  (SAI_MASTER_MCLK_SCK_SD_FS_AF << (4 * (SAI_MASTER_FS_PIN - 8)));
  
  SAI_MASTER_SCK_FS_GPIO->OSPEEDR |= (3 << (2 * SAI_MASTER_SCK_PIN)) | (3 << (2 * SAI_MASTER_FS_PIN));

  SAI_MASTER_SD_GPIO->MODER |= (2 << (2 * SAI_MASTER_SD_PIN));
  SAI_MASTER_SD_GPIO->AFR[1] |= (SAI_MASTER_MCLK_SCK_SD_FS_AF << (4 * (SAI_MASTER_SD_PIN - 8)));
  SAI_MASTER_SD_GPIO->OSPEEDR |= (3 << (2 * SAI_MASTER_SD_PIN));
}
//------------------------------------------------------------------------------
void SAI_SlaveGPIOInit(void)
{
  SAI_SLAVE_SD_GPIO->MODER |= (2 << (2 * SAI_SLAVE_SD_PIN));
  SAI_SLAVE_SD_GPIO->AFR[0] |= (SAI_SLAVE_SD_AF << (4 * SAI_SLAVE_SD_PIN));
  SAI_SLAVE_SD_GPIO->OSPEEDR |= (3 << (2 * SAI_SLAVE_SD_PIN));
}






