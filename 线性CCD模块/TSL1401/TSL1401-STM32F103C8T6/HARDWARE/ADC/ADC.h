#ifndef __ADC_H
#define __ADC_H	 
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"

extern u16 adc_value;

void ADC1_init(void);
void ADC_init(void);
u16 Get_Adc(u8 ch);//���ADCֵ  ch:ͨ��ֵ 0~3
u16 Get_Adc_Averge(u8 ch,u8 times);

		 				    
#endif
