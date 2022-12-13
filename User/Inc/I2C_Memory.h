/*
********************************************************************************
* COPYRIGHT(c) ��� ���� � ��ϻ, 2020
* 
* ����������� ����������� ��������������� �� �������� ���� ����� (as is).
* ��� ��������������� �������� ������ �����������.
********************************************************************************
*/


#ifndef __I2C_MEMORY_H
#define __I2C_MEMORY_H


#include "board.h"


void Memory_Write(TransferType* Transfer);

void Memory_Read(TransferType* Transfer);

uint8_t Memory_IsReady(void);

uint32_t Memory_GetConfigSize(void);

void Memory_EraseConfig(void);


#endif //__I2C_MEMORY_H

