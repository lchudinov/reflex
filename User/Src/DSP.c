/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/




#include "DSP.h"
#include "MemoryMap.h"
#include "I2C.h"
//#include "LogicIOLines.h"
#include "Delay.h"
//#include "SPI_DSP.h"


void InitDSPStructs(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, uint8_t *DSPConf)
{
  ICInfo->ID = DSPConf[DSP_ID_OFFSET];
  ICInfo->BusAddress = DSPConf[DSP_BUS_ADR_OFFSET];
  ICInfo->ChipSelect = DSPConf[DSP_CS_GPIO_NUM_OFFSET];
  ICInfo->InternalAdrBytes = 1;
  if ((ICInfo->ID == DSP_IC_ADAU1701) || (ICInfo->ID == DSP_IC_ADAU1761))
    ICInfo->InternalAdrBytes = 2;
  
  if (DSPConf[DSP_INTERFACE_TYPE_OFFSET] == I2C_INTERFACE)
  {
    DSPMethods->IsReady = I2C_IsReady;
    DSPMethods->Write = I2C_Write;
    DSPMethods->Read = I2C_Read;
  }
/*  
  else if (DSPConf[DSP_INTERFACE_TYPE_OFFSET] == SPI_INTERFACE)
  {
    ICInfo->InterfaceType = SPI_INTERFACE;
    DSPMethods->InterfaceLinesEnable = ActivateSPILines;
    DSPMethods->InterfaceLinesDisable = DeActivateSPILines;
    DSPMethods->IsReady = SPI_DSP_IsReady;
    DSPMethods->Write = SPI_DSP_Write;
    DSPMethods->Read = SPI_DSP_Read;
  }
*/
}
//------------------------------------------------------------------------------
void ADAU1701_SafeLoad(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, TransferType* Transfer)
{
  TransferType SafeLoad;
  
  for (uint8_t i = 0; i < Transfer->Size; i++)
  {
    uint16_t ParamAdr = (uint16_t)(Transfer->Address + i);
    
    SafeLoad.Address = ADAU1701_SAFELOAD_ADR_0 + i;
    SafeLoad.Size = 2;
    SafeLoad.Data[0] = ParamAdr >> 8;
    SafeLoad.Data[1] = ParamAdr;
    DSPMethods->Write(ICInfo, &SafeLoad);
    Delay();
    
    SafeLoad.Address = ADAU1701_SAFELOAD_DATA_0 + i;
    SafeLoad.Size = 5;
    SafeLoad.Data[0] = 0;
    SafeLoad.Data[1] = Transfer->Data[i * DSP_PARAMETER_DATA_ADR_INCR];
    SafeLoad.Data[2] = Transfer->Data[i * DSP_PARAMETER_DATA_ADR_INCR + 1];
    SafeLoad.Data[3] = Transfer->Data[i * DSP_PARAMETER_DATA_ADR_INCR + 2];
    SafeLoad.Data[4] = Transfer->Data[i * DSP_PARAMETER_DATA_ADR_INCR + 3];
    DSPMethods->Write(ICInfo, &SafeLoad);
    Delay();
  }
  
  SafeLoad.Address = ADAU1701_DSP_CORE_CTRL;
  SafeLoad.Size = 2;
  SafeLoad.Data[0] = 0;
  DSPMethods->Read(ICInfo, &SafeLoad);
  Delay();
  
  SafeLoad.Size = 2;
  SafeLoad.Data[1] |= ADAU1701_DSP_CORE_IST;
  DSPMethods->Write(ICInfo, &SafeLoad);
  Delay();
}
//------------------------------------------------------------------------------
void ADAU1761_SafeLoad(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, TransferType* Transfer)
{
  TransferType SafeLoad;
  
  for (uint8_t i = 0; i < Transfer->Size; i++)
  {   
    SafeLoad.Address = ADAU1761_SAFELOAD_DATA_START_ADR + i;
    SafeLoad.Size = DSP_PARAMETER_DATA_ADR_INCR;
    SafeLoad.Data[0] = Transfer->Data[i * DSP_PARAMETER_DATA_ADR_INCR];
    SafeLoad.Data[1] = Transfer->Data[i * DSP_PARAMETER_DATA_ADR_INCR + 1];
    SafeLoad.Data[2] = Transfer->Data[i * DSP_PARAMETER_DATA_ADR_INCR + 2];
    SafeLoad.Data[3] = Transfer->Data[i * DSP_PARAMETER_DATA_ADR_INCR + 3];
    DSPMethods->Write(ICInfo, &SafeLoad);
    Delay();
  }
  
  uint16_t ParamAdr = (uint16_t)(Transfer->Address - 1);
  
  SafeLoad.Address = ADAU1761_SAFELOAD_PARAM_ADR;
  SafeLoad.Size = DSP_PARAMETER_DATA_ADR_INCR;
  SafeLoad.Data[0] = 0;
  SafeLoad.Data[1] = 0;
  SafeLoad.Data[2] = ParamAdr >> 8;
  SafeLoad.Data[3] = ParamAdr;
  DSPMethods->Write(ICInfo, &SafeLoad);
  Delay();
  
  SafeLoad.Address = ADAU1761_SAFELOAD_NUMLOAD;
  SafeLoad.Size = DSP_PARAMETER_DATA_ADR_INCR;
  SafeLoad.Data[0] = 0;
  SafeLoad.Data[1] = 0;
  SafeLoad.Data[2] = 0;
  SafeLoad.Data[3] = (uint8_t)Transfer->Size;
  DSPMethods->Write(ICInfo, &SafeLoad);
  Delay();
}
//------------------------------------------------------------------------------
void TAS3251_SwapCommand(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, TransferType* Transfer)
{
  Transfer->Address = TAS3251_CHANGE_PAGE;
  Transfer->Size = 1;
  Transfer->Data[0] = TAS3251_ZERO_PAGE;
  DSPMethods->Write(ICInfo, Transfer);
  Delay();
  
  Transfer->Address = TAS3251_CHANGE_BOOK;
  Transfer->Size = 1;
  Transfer->Data[0] = TAS3251_DSP_BOOK;
  DSPMethods->Write(ICInfo, Transfer);
  Delay();
  
  Transfer->Address = TAS3251_CHANGE_PAGE;
  Transfer->Size = 1;
  Transfer->Data[0] = TAS3251_SWAP_PAGE;
  DSPMethods->Write(ICInfo, Transfer);
  Delay();
  
  Transfer->Address = TAS3251_SWAP_ADDRESS;
  Transfer->Size = 4;
  Transfer->Data[0] = TAS3251_SWAP_FLAG >> 24;
  Transfer->Data[1] = TAS3251_SWAP_FLAG >> 16;
  Transfer->Data[2] = TAS3251_SWAP_FLAG >> 8;
  Transfer->Data[3] = TAS3251_SWAP_FLAG;
  DSPMethods->Write(ICInfo, Transfer);
  Delay();
}
//------------------------------------------------------------------------------
void PCM5x4xSwitchBuffers(ICInfoType *ICInfo, DSPMethodsType *DSPMethods, TransferType* Transfer)
{
  Transfer->Address = PCM5x4x_CHANGE_PAGE;
  Transfer->Size = 1;
  Transfer->Data[0] = PCM5x4x_CRAM_CTRL_PAGE;
  DSPMethods->Write(ICInfo, Transfer);
  Delay();
  
  Transfer->Address = PCM5x4x_CRAM_CTRL_REG;
  Transfer->Size = 1;
  Transfer->Data[0] = PCM5x4x_CRAM_SWITCH_CMD;
  DSPMethods->Write(ICInfo, Transfer);
  
  uint8_t PollCycle = 0;
  while(PollCycle < PCM5x4x_ACSW_POLL_CYCLE_COUNT)
  {
    Transfer->Size = 1;
    
    Delay();
    DSPMethods->Read(ICInfo, Transfer);

    if ((Transfer->Data[0] & PCM5x4x_ACSW_BIT) != PCM5x4x_ACSW_BIT)
      break;
            
    PollCycle++;
  }
}


