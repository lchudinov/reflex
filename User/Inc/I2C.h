/*
********************************************************************************
* COPYRIGHT(c) ��� ���� � ��ϻ, 2020
* 
* ����������� ����������� ��������������� �� �������� ���� ����� (as is).
* ��� ��������������� �������� ������ �����������.
********************************************************************************
*/


#ifndef __I2C_H
#define __I2C_H


#include "board.h"


#define       I2C_DEVICE_READY             1



void I2C_Init(void);

void I2C_Write(ICInfoType *ICInfo, TransferType* Transfer);

void I2C_Read(ICInfoType *ICInfo, TransferType* Transfer);

uint8_t I2C_IsReady(ICInfoType *ICInfo);

void I2C_SendBusAdr(uint8_t Address);

void I2C_StartWrite(ICInfoType *ICInfo, uint32_t InternalAdr);


#endif //__I2C_H


