#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	KEY_Init();     //�����˿ڳ�ʼ��  ���ǳ�ʼ��IO��Ϊ����                             ��һ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);    //ʹ��SYSCFGʱ��
	/****************GPIOB4*************************************/
	/*****************����IO�����ж��ߵ�ӳ���ϵ************************/             //������
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource5);  //PA5--Line5
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);  //PA0--Line0
	
	/*****************����EXTI 5****************/                                 //���Ĳ�
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;    //�ж�������
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;    //ʹ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;    //ѡ���ⲿ�жϣ������¼��жϣ�
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;   //��������ģʽ �����½��ش��� ѡ�񴥷���ʽ
	EXTI_Init(&EXTI_InitStructure);
	
	/***********************�����жϷ���*****************************/
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;          //ѡ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;           //ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  //������ռ���ȼ�Ϊ2 ��ֵ���ܳ���2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;        //������Ӧ���ȼ�Ϊ2
	NVIC_Init(&NVIC_InitStructure);
	
	/*****************����EXTI 5****************/                                 //���Ĳ�
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;    //�ж�������
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;    //ʹ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;    //ѡ���ⲿ�жϣ������¼��жϣ�
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;   //��������ģʽ �����½��ش��� ѡ�񴥷���ʽ
	EXTI_Init(&EXTI_InitStructure);
	
	/***********************�����жϷ���*****************************/
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;          //ѡ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;           //ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;  //������ռ���ȼ�Ϊ2 ��ֵ���ܳ���2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;        //������Ӧ���ȼ�Ϊ2
	NVIC_Init(&NVIC_InitStructure);
	
}
	
/******************��д�жϷ�����****************************/
void EXTI9_5_IRQHandler  (void)     //  �ⲿ�ж�5�������
{
	if(KEY0==0)
	{
		LED=!LED;
	}
	EXTI_ClearITPendingBit(EXTI_Line5);     //����жϱ�־λ
}

void EXTI0_IRQHandler  (void)     //  �ⲿ�ж�5�������
{
	if(WK_UP==0)
	{
		LED=!LED;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);     //����жϱ�־λ
}



