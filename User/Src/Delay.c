/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/



#include "Delay.h"



void DelayInit(uint16_t psc, uint16_t arr)
{
  RCC->DELAY_TIMER_ENR |= DELAY_TIMER_CLK_EN;
  DELAY_TIMER->PSC = psc;
  DELAY_TIMER->ARR = arr;
  DELAY_TIMER->EGR = TIM_EGR_UG;  
  DELAY_TIMER->SR = 0;
  DELAY_TIMER->CR1 = TIM_CR1_OPM;
    
  RCC->DELAY_TIMER_ENR &= ~DELAY_TIMER_CLK_EN;
}
//------------------------------------------------------------------------------
void Delay(void)
{
  RCC->DELAY_TIMER_ENR |= DELAY_TIMER_CLK_EN;
  DELAY_TIMER->CR1 |= TIM_CR1_CEN;
  
  while((DELAY_TIMER->SR & TIM_SR_UIF) != TIM_SR_UIF);
  
  DELAY_TIMER->SR = 0;
  RCC->DELAY_TIMER_ENR &= ~DELAY_TIMER_CLK_EN;
}






