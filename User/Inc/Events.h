/*
********************************************************************************
* COPYRIGHT(c) ��� ���� � ��ϻ, 2020
* 
* ����������� ����������� ��������������� �� �������� ���� ����� (as is).
* ��� ��������������� �������� ������ �����������.
********************************************************************************
*/



#ifndef __EVENTS_H
#define __EVENTS_H


#include "board.h"


void Events_InitGPIOs(void);

void Event_FreqChanged(uint32_t AudioFrequency);

void Event_ResChanged(uint8_t AudioResolution);

void Event_MuteChanged(uint8_t MuteFlag);


#endif //__EVENTS_H