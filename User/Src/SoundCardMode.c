/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#include "SoundCardMode.h"
#include "DSP.h"
#include "I2C.h"
#include "I2C_Memory.h"
#include "Delay.h"
#include "MemoryMap.h"
#include "usbd_audio.h"


static TransferType TransferInst;


void SoundCardApplication(void)
{
  //uint8_t ConfigMap[] = {0};
  //BootDSPConfig(ConfigMap);
}
//------------------------------------------------------------------------------
void BootDSPConfig(uint8_t *ConfigMap)
{
  uint32_t MemoryAdr = JoinBytesIntoValue(&ConfigMap[BLOCK_CONF_ADR_OFFSET], BLOCK_CONF_ADR_SIZE);
  //uint16_t ConfigSize = (uint16_t)JoinBytesIntoValue(&ConfigMap[BLOCK_CONF_SIZE_OFFSET], BLOCK_CONF_SIZE_SIZE);
  
  TransferInst.Size = DSP_FIRST_OPER_DESC_OFFSET;
  TransferInst.Address = MemoryAdr;
  Memory_Read(&TransferInst);
  
  uint16_t BootOperCount = JoinBytesIntoValue(&TransferInst.Data[DSP_OPERATIONS_COUNT_OFFSET], DSP_OPERATIONS_COUNT_SIZE);
  ICInfoType DSP;
  DSPMethodsType DSPMethods;
  InitDSPStructs(&DSP, &DSPMethods, TransferInst.Data);
  
  if (DSPMethods.IsReady(&DSP) == DEVICE_READY)
  {
    DelayInit(DELAY_TIMER_DSP_PSC, DELAY_TIMER_DSP_ARR);
    
    MemoryAdr += DSP_FIRST_OPER_DESC_OFFSET;
    for (uint16_t i = 0; i < BootOperCount; i++)
    {
      TransferInst.Size = DSP_OPER_DATA_OFFSET;
      TransferInst.Address = MemoryAdr;
      Memory_Read(&TransferInst);
      
      uint8_t OperDescriptor[DSP_OPER_DATA_OFFSET];
      memcpy(OperDescriptor, TransferInst.Data, DSP_OPER_DATA_OFFSET);
      
      //TransferInst.Address = JoinBytesIntoValue(&OperDescriptor[DSP_OPER_ADR_OFFSET], DSP_OPER_ADR_SIZE);
      uint32_t DSPIntAdr = JoinBytesIntoValue(&OperDescriptor[DSP_OPER_ADR_OFFSET], DSP_OPER_ADR_SIZE);
      uint16_t TxSize = (uint16_t)JoinBytesIntoValue(&OperDescriptor[DSP_OPER_DATA_SIZE_OFFSET], DSP_OPER_DATA_SIZE_SIZE);
      TransferInst.Size = TxSize;
      MemoryAdr += DSP_OPER_DATA_OFFSET;
      
      if (OperDescriptor[DSP_OPER_ADR_INCR_OFFSET] == DSP_REGISTER_DATA_ADR_INCR)
      {        
        if ((OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_WRITE) || (OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_POLL))
        {
          TransferInst.Address = MemoryAdr;
          Memory_Read(&TransferInst);
          //Memory_Read(TransferInst.Size, MemoryAdr, TransferInst.Data);
        }
        else if (OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_CLEAR)
          memset(TransferInst.Data, 0, TransferInst.Size);
        
        TransferInst.Address = DSPIntAdr;
        
        if ((OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_WRITE)
         || (OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_CLEAR))
        {          
          DSPMethods.Write(&DSP, &TransferInst);
          Delay();
        }
        else if (OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_POLL)
        {
          uint8_t PollSize = TransferInst.Size;
          uint8_t *PollData = malloc(PollSize * sizeof(*PollData));
          if (!PollData)
            Error_Handler();
          
          for(uint8_t j = 0; j < PollSize; j++)
            PollData[j] = TransferInst.Data[j];
          
          uint8_t PollCycle = 0;
          while(PollCycle < ADAU_POLL_CYCLE_COUNT)
          {
            Delay();
            DSPMethods.Read(&DSP, &TransferInst);
            
            uint8_t DataMatch = 1;
            for(uint8_t j = 0; j < PollSize; j++)
            {
              if ((TransferInst.Data[j] & PollData[j]) != PollData[j])
              {
                DataMatch = 0;
                break;
              }
            }
            
            if (DataMatch == 1)
              break;
            
            TransferInst.Size = PollSize;
            PollCycle++;
          }
          
          free(PollData);
          
          if (PollCycle >= ADAU_POLL_CYCLE_COUNT)
          {
            //ErrorHandler(DSP_DISCONNECTED);
            break;
          }
        }
        
        MemoryAdr += TxSize;
      }
      else //if (OperDescriptor[DSP_OPER_ADR_INCR_OFFSET] == DSP_PARAMETER_DATA_ADR_INCR or DSP_PROGRAM_DATA_ADR_INCR)
      {
        uint16_t WriteCount = TransferInst.Size / OperDescriptor[DSP_OPER_ADR_INCR_OFFSET];
        TransferInst.Size = OperDescriptor[DSP_OPER_ADR_INCR_OFFSET];
        
        if (OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_CLEAR)
          memset(TransferInst.Data, 0, TransferInst.Size);
        
        for (uint16_t j = 0; j < WriteCount; j++)
        {
          if (OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_WRITE)
          {
            TransferInst.Address = MemoryAdr;
            Memory_Read(&TransferInst);
            //Memory_Read(TransferInst.Size, MemoryAdr, TransferInst.Data);
            MemoryAdr += OperDescriptor[DSP_OPER_ADR_INCR_OFFSET];
          }
          
          if ((OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_WRITE)
           || (OperDescriptor[DSP_OPER_ID_OFFSET] == DSP_CLEAR))
          {
            TransferInst.Address = DSPIntAdr;
            DSPMethods.Write(&DSP, &TransferInst);
            Delay();
          }
          
          TransferInst.Size = OperDescriptor[DSP_OPER_ADR_INCR_OFFSET];
          DSPIntAdr++;
          //TransferInst.Address++;
        }
      }
    }
  }
  else
    Error_Handler();
}


