#include "timer.h"
#include "led.h"
u8 led_bit=0;
void TIM2_Int_Init(u16 arr,u16 psc)   //�Զ���װ�غ�Ԥ��Ƶϵ��
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   //ʹ�ܶ�ʱ��2
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;            //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;         //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);         //ʹ�ܶ�ʱ��2�ĸ����ж�
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;   //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;          //��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(TIM2,ENABLE);    
}

/********��д��ʱ��2�жϷ�����***200ms**********************/	
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)     //���TIM2�����ж��Ƿ���
	{
		if(led_bit)
		  led=!led;
			
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);      //���TIM2���±�־λ
	}
}





