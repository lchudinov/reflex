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


#ifndef __SAI_H
#define __SAI_H


#include "board.h"


#define   SAI_IRQ_PRIORITY                 ((uint32_t)2)

#define   SAI_MCLK_49_152MHz               (RCC_PLLSAICFGR_PLLSAIQ_0 | RCC_PLLSAICFGR_PLLSAIQ_1 | RCC_PLLSAICFGR_PLLSAIQ_2 | \
                                           (0x158 << RCC_PLLSAICFGR_PLLSAIN_Pos) | RCC_PLLSAICFGR_PLLSAIM_3)

#define   SAI_MCLK_22_5792MHz              (RCC_PLLSAICFGR_PLLSAIQ_2 | RCC_PLLSAICFGR_PLLSAIQ_3 | (0xED << RCC_PLLSAICFGR_PLLSAIN_Pos) | \
                                           RCC_PLLSAICFGR_PLLSAIM_0 | RCC_PLLSAICFGR_PLLSAIM_1 | RCC_PLLSAICFGR_PLLSAIM_2)

#define   SAI_MCLK_45_1584MHz              (RCC_PLLSAICFGR_PLLSAIQ_1 | RCC_PLLSAICFGR_PLLSAIQ_2 | (0xED << RCC_PLLSAICFGR_PLLSAIN_Pos) | \
                                           RCC_PLLSAICFGR_PLLSAIM_0 | RCC_PLLSAICFGR_PLLSAIM_1 | RCC_PLLSAICFGR_PLLSAIM_2)


enum BCLK_FsRatioModes
{
  BCLK_Fs_RES_DEPENDENT = 0,
  BCLK_Fs_FIXED,
};

enum BCLK_PolModes
{
  CKSTR_0_RISING = 0,
  CKSTR_1_FALLING = 1,
};

enum TDM_LR_Modes
{
  TDM_LR_PULSE = 0,
  TDM_LR_CLOCK = 1,
};

enum SAIFormats
{
  SAI_I2S = 0,
  SAI_TDM,
  SAI_SPDIF,
};

typedef struct
{
  uint8_t BclkFsRatio;
  uint8_t TdmLrMode;
  uint8_t BclkPol;
  uint8_t Format;
  
} SAISettings;


void SAI_InitSettings(SAISettings *Settings);

void SAI_PLLSAIConfig(uint32_t AudioFrequency);

void SAI_ChangeFrequency(uint32_t AudioFrequency);

void SAI_ExternalSyncInit(void);

uint16_t SAI_GetLastTransferSize(void);

uint16_t SAI_GetRemainingTxSize(void);

void SAI_MasterDMAPrepareTx(uint16_t *Data, uint16_t Size);

void SAI_SlaveDMAPrepareTx(uint16_t *Data, uint16_t Size);

void SAI_DMAPrepareTx(DMA_Stream_TypeDef *DMAStream, uint16_t *Data, uint16_t Size);

void SAI_Enable(SAI_Block_TypeDef *SAIBlock);

void SAI_Mute(SAI_Block_TypeDef *SAIBlock, uint8_t MuteFlag);

void SAI_Disable(SAI_Block_TypeDef *SAIBlock);

void SAI_MasterInit(uint8_t AudioResolution, uint8_t ChnlCount);

void SAI_MasterSetSlaveSync(void);

void SAI_SlaveInit(uint8_t AudioResolution);

void SAI_Init_I2S(SAI_Block_TypeDef *SAIBlock, uint8_t AudioResolution);

void SAI_Init_TDM(SAI_Block_TypeDef *SAIBlock, uint8_t AudioResolution, uint8_t ChnlCount);

void SAI_DMAEnable(SAI_Block_TypeDef *SAIBlock);

void SAI_MasterDMAInit(uint8_t AudioResolution);

void SAI_SlaveDMAInit(uint8_t AudioResolution);

void SAI_DMAInit(DMA_Stream_TypeDef *DMAStream, uint8_t AudioResolution);

void SAI_DMAChangeDataSize(DMA_Stream_TypeDef *DMAStream, uint8_t Resolution);

void SAI_MasterGPIOInit(void);

void SAI_SlaveGPIOInit(void);



#endif // __SAI_H


