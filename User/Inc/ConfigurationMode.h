/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/


#ifndef __CONFIGURATION_MODE_H
#define __CONFIGURATION_MODE_H


#include "board.h"



void ConfigurationApplication(void);

void MemTransferUpdate(uint8_t *Data);

void MemTransferInit(uint8_t *Data);


#endif //__CONFIGURATION_MODE_H