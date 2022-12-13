/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/



#ifndef __DSP_H
#define __DSP_H


#include "board.h"

#define   DEVICE_READY                     1

#define   DSP_REGISTER_DATA_ADR_INCR       0
#define   DSP_PARAMETER_DATA_ADR_INCR      4
#define   DSP_PROGRAM_DATA_ADR_INCR        5

#define   ADAU1701_DSP_CORE_CTRL           0x081C
#define   ADAU1701_SAFELOAD_ADR_0          0x0815
#define   ADAU1701_SAFELOAD_DATA_0         0x0810
#define   ADAU1701_DSP_CORE_IST            (1 << 5)

#define   ADAU1761_SAFELOAD_DATA_START_ADR 0x01
#define   ADAU1761_SAFELOAD_PARAM_ADR      0x06
#define   ADAU1761_SAFELOAD_NUMLOAD        0x07

#define   ADAU_POLL_CYCLE_COUNT            160

#define   ADAU_SAFELOAD_PARAM_MAX_COUNT    5


#define   TAS3251_CHNL_FILTER_PARAM_COUNT  4
#define   TAS3251_CHANGE_PAGE              0x00
#define   TAS3251_ZERO_PAGE                0x00
#define   TAS3251_CHANGE_BOOK              0x7F
#define   TAS3251_DSP_BOOK                 0x8C
#define   TAS3251_SWAP_PAGE                0x23
#define   TAS3251_SWAP_ADDRESS             0x14
#define   TAS3251_SWAP_FLAG                ((uint32_t) 0x00000001)

#define   PCM5x4x_CHANGE_PAGE              0x00
#define   PCM5x4x_CRAM_CTRL_PAGE           0x2C
#define   PCM5x4x_CRAM_CTRL_REG            0x01

#define   PCM5x4x_AMDC_BIT                 (1 << 2)
#define   PCM5x4x_ACSW_BIT                 (1 << 0)
#define   PCM5x4x_CRAM_SWITCH_CMD          (PCM5x4x_AMDC_BIT | PCM5x4x_ACSW_BIT)
#define   PCM5x4x_ACSW_POLL_CYCLE_COUNT    100

#define   AD19xx_READY_CHECK_ADDRESS       1

#define   DSP_DATA_MASK_OFFSET             0
#define   DSP_NEW_DATA_OFFSET              1



enum DSP_IC
{ 
  DSP_IC_ADAU1701 = 1,
  DSP_IC_ADAU1761,
  DSP_IC_TAS3251,
  DSP_IC_AD19xx,
  DSP_IC_SSM3582,
  PCM5x4x_I2C_ID,
};

enum DSP_OPERATION
{ 
  DSP_WRITE,
  DSP_READ,
  DSP_CLEAR,
  DSP_POLL,
};

enum DSP_WRITE_TYPE
{ 
  DSP_SAFELOAD,
  DSP_BLOCK_WRITE,
  DSP_READ_MODIFY_WRITE,
};

typedef struct
{
  uint8_t (*IsReady)(ICInfoType *ICInfo);
  void (*Write)(ICInfoType *ICInfo, TransferType* Transfer);
  void (*Read)(ICInfoType *ICInfo, TransferType* Transfer);
  
} DSPMethodsType;


void InitDSPStructs(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, uint8_t *DSPConf);

void ADAU1701_SafeLoad(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, TransferType* Transfer);

void ADAU1761_SafeLoad(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, TransferType* Transfer);

void TAS3251_SwapCommand(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, TransferType* Transfer);

void PCM5x4xSwitchBuffers(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, TransferType* Transfer);


#endif //__DSP_H



