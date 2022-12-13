/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#include "I2C.h"


//400 кГц @ 168 MHz
void I2C_Init(void)
{
  I2C_GPIO->OTYPER |= (1 << I2C_SCL_PIN) | (1 << I2C_SDA_PIN);
  I2C_GPIO->AFR[0] |= (I2C_SCL_AF << (4 * I2C_SCL_PIN)) | (I2C_SDA_AF << (4 * I2C_SDA_PIN));
  I2C_GPIO->MODER |= (2 << (2 * I2C_SCL_PIN)) | (2 << (2 * I2C_SDA_PIN));
  
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
  I2C_PORT->CR2 = I2C_CR2_FREQ_5 | I2C_CR2_FREQ_3 | I2C_CR2_FREQ_1;
  I2C_PORT->TRISE = 0x0D;
  I2C_PORT->CCR = I2C_CCR_FS | I2C_CCR_DUTY | 0x05;
  I2C_PORT->OAR1 = (1 << 14);
  I2C_PORT->CR1 = I2C_CR1_PE;
}
//------------------------------------------------------------------------------
void I2C_Write(ICInfoType *ICInfo, TransferType* Transfer)
{
  I2C_StartWrite(ICInfo, Transfer->Address);
  
  uint8_t *DataArray = &(Transfer->Data[0]);
  uint16_t BytesNum = Transfer->Size;
  
  while(BytesNum)
  {
    I2C_PORT->DR = *DataArray;
    while(!(I2C_PORT->SR1 & I2C_SR1_BTF));
        
    *DataArray++;
    BytesNum--;
  }
  
  I2C_PORT->CR1 |= I2C_CR1_STOP;
  I2C_PORT->SR1;
}
//------------------------------------------------------------------------------
void I2C_Read(ICInfoType *ICInfo, TransferType* Transfer)
{
  I2C_StartWrite(ICInfo, Transfer->Address);
    
  I2C_SendBusAdr(((ICInfo->BusAddress) << 1) | 0x01);
  I2C_PORT->CR1 |= I2C_CR1_ACK;
  while(!(I2C_PORT->SR1 & I2C_SR1_ADDR));
  I2C_PORT->SR2;
    
  uint8_t *DataArray = &(Transfer->Data[0]);
  uint16_t BytesNum = Transfer->Size;
  
  do
  {
    while(!(I2C_PORT->SR1 & I2C_SR1_RXNE)); 
    *DataArray = I2C_PORT->DR;
    if (BytesNum != 1)
      I2C_PORT->CR1 |= I2C_CR1_ACK;
    
    *DataArray++;
    BytesNum--;
    if (BytesNum == 1)
    {
      I2C_PORT->CR1 &= ~I2C_CR1_ACK;
      I2C_PORT->CR1 |= I2C_CR1_STOP;
    }
  }
  while(BytesNum);
  
  I2C_PORT->SR1;
}
//------------------------------------------------------------------------------
uint8_t I2C_IsReady(ICInfoType *ICInfo)
{
  uint8_t Status = I2C_DEVICE_READY;
  
  I2C_SendBusAdr((ICInfo->BusAddress) << 1);
  while((!(I2C_PORT->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF))));
  I2C_PORT->SR2;
  
  if ((I2C_PORT->SR1 & I2C_SR1_AF) == I2C_SR1_AF)
  {
    I2C_PORT->SR1 &= ~I2C_SR1_AF;
    Status = 0;
  }
  
  I2C_PORT->CR1 |= I2C_CR1_STOP;
  
  return Status;
}
//------------------------------------------------------------------------------
void I2C_StartWrite(ICInfoType *ICInfo, uint32_t InternalAdr)
{
  I2C_SendBusAdr((ICInfo->BusAddress) << 1);
  while(!(I2C_PORT->SR1 & I2C_SR1_ADDR));
  I2C_PORT->SR2;
  
  for (uint8_t i = 0; i < (ICInfo->InternalAdrBytes); i++)
  {
    I2C_PORT->DR = (uint8_t)(InternalAdr >> (8 * (ICInfo->InternalAdrBytes - 1 - i)));
    while(!(I2C_PORT->SR1 & I2C_SR1_BTF));
  }
}
//------------------------------------------------------------------------------
void I2C_SendBusAdr(uint8_t Address)
{
  I2C_PORT->CR1 |= I2C_CR1_START;
  while(!(I2C_PORT->SR1 & I2C_SR1_SB));
  I2C_PORT->DR = Address;
}




