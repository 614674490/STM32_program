#include "stm32f10x.h"
#include "sys.h"
#include "led.h"
#include "delay.h"     //������ʱ����ͷ�ļ�
int main()
{
	LED_Init();        //LED��ʼ��
	delay_init();     //��ʱ������ʼ��
	while(1)
	{
		/*************λ������********************/
		/*LED0=1;
		LED1=0;
		delay_ms(500);      //��ʱ500ms
		LED1=1;
		LED0=0;
		delay_ms(500);*/
		/***************************�⺯����*********************/
		GPIO_SetBits(GPIOB,GPIO_Pin_5);                   //��PB5��λ�ߵ�ƽ
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);                   //��PE5��λ�ߵ�ƽ
		delay_ms(500);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);                   //��PB5��λ�ߵ�ƽ
		GPIO_SetBits(GPIOE,GPIO_Pin_5);                   //��PE5��λ�ߵ�ƽ
		delay_ms(500);
	}
}


