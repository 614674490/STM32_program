#include "timer.h"
#include "led.h"
/************ͨ�ö�ʱ��2��ʼ������*****************/
void TIM2_Int_Init(u16 arr,u16 psc)   //�Զ���װ�غ�Ԥ��Ƶϵ��
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);   //ʹ�ܶ�ʱ��2
	
	TIM_TimeBaseStructure.TIM_ClockDivision=0;                 //TIM_CKD_DIV1  ����ʱ�ӷָ�:TDTS = Tck_tim
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
	
	TIM_Cmd(TIM2,ENABLE);                               //ʹ�ܶ�ʱ��2
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		  LED=!LED;//DS1��ת
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}

/************TIM2 PWM���ֳ�ʼ������**************/
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ�ܶ�ʱ��2ʱ��
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //ʹ��GPIO���� ����ʹ��AFIOʱ��
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);   //�˿ڸ���

	//����������� ���TIM2_CH1��PWM����   PA0
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;       //����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	 
	//��ʼ��TIM2
	TIM_TimeBaseStructure.TIM_ClockDivision=0;                 //TIM_CKD_DIV1  ����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;            //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;         //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	//��ʼ����ʱ��2ͨ��2������Ƚϲ���
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM2;           //PWMģʽ2
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_High;    //�ߵ�ƽ��Ч ���Ƚ��������Ϊ��
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);                     //�������ϲ�����ʼ��TIM2 OC2
	/*����������PWMģʽ2 ��CNT>CCRʱΪ�ߵ�ƽ С����Ϊ�͵�ƽ,CCRԽС,ռ�ձȾ�Խ�󣨸ߵ�ƽ����ʱ��Խ����*/
	
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);     //ʹ�ܶ�ʱ��2��CCR1��Ԥװ�ض�ʱ��
	
	TIM_Cmd(TIM2,ENABLE);                                //ʹ�ܶ�ʱ��2
}
	
	



