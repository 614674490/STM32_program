#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void)
{ 
	LED_Init();		        //��ʼ��LED�˿�
	delay_init(168);		  //��ʼ����ʱ���
	while(1)
	{
		LED=0;
		delay_ms(500);
		LED=1;
		delay_ms(500);
	}
}

