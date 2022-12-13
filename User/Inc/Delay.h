/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/



#ifndef __DELAY_H
#define __DELAY_H


#include "board.h"


#define   DELAY_TIMER                      TIM13
#define   DELAY_TIMER_ENR                  APB1ENR
#define   DELAY_TIMER_CLK_EN               RCC_APB1ENR_TIM13EN

#define   DELAY_TIME_ELAPSED               1
#define   DELAY_SYNC                       0
#define   DELAY_ASYNC                      1


void DelayInit(uint16_t psc, uint16_t arr);

void Delay(void);


#endif//__DELAY_H