#include "control.h"
#include "timer.h"
#include "ccd.h"
u8 Flag_Target;

//����Ϊ5ms���жϿ���
void TIM2_IRQHandler(void) 
{
	if (TIM2->SR&0X0001) 
	{
		TIM2->SR&=~(1<<0); 
		Flag_Target=!Flag_Target; 
		if(Flag_Target)	
			RD_TSL();               
		else 
			getCCDMedian();			          
	}
}


