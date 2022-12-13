/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2019
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#ifndef __SAI_H
#define __SAI_H


#include "board.h"


#define   SAI_IRQ_PRIORITY                       ((uint32_t)2)



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

void SAI_MasterInit_I2S(uint8_t AudioResolution);

void SAI_MasterInit_TDM(uint8_t AudioResolution, uint8_t ChnlCount);

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


