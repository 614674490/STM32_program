#include "key.h"
#include "delay.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��

	//��ʼ��PA^5 ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//KEY0
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;       //����
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;    //��������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA
	

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;    //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
}
	
//���������������ذ���ֵ
//mode=0 ��֧����������=1֧��������
//KEY0���·���1 KEY1���·���2
//KEY0�����ȼ�����KEY1
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;   //�����ɿ���־��ÿ�ε��øú���ʱ�������ִֻ��һ��
	if(mode) key_up=1;
	if(key_up&&(KEY0==0||WK_UP==1))
	{
		delay_ms(50);   //��ʱ����
		key_up=0;
		if(KEY0==0) return KEY0_PRES;
		else if(WK_UP==1) return WK_UP_PRES;
	}
	else if(KEY0==1&&WK_UP==0)  key_up=1;
	return 0;    //�ް������� ����1
}

	
			
	


