#ifndef _timer_h
#define _timer_h
#include "sys.h"    //�������Ѿ������˶���ͷ�ļ�
#include "stm32f10x_tim.h"
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
extern  u8 led_bit;
#endif



