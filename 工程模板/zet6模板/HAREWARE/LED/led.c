#include "led.h"
#include "stm32f10x.h"
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //��ʼ���ò���
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;            //�����IO��
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;    //IO���ٶ�Ϊ50MHZ
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;    //�������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��GPIOB\E��ʱ��
	GPIO_Init(GPIOB,&GPIO_InitStructure);             //�������ò�����ʼ��GPIOB��
	GPIO_SetBits(GPIOB,GPIO_Pin_5);                   //��PB5��λ�ߵ�ƽ
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);             //�������ò�����ʼ��GPIOE��
	GPIO_SetBits(GPIOE,GPIO_Pin_5);                   //��PE5��λ�ߵ�ƽ
	
}


