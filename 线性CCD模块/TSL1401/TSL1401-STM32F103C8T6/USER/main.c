#include "include.h"
//�ο���վ�� https://blog.csdn.net/weixin_42108484/article/details/102815123
int main(void)
{
	LED_Init();
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
	CCD_Init();
	OLED_Init();
	Screen_Init();
	TIM2_Init_ms(5);
	while(1)
	{
		OLED_Show_CCD();
		Debug(Multi_CCD_Data);
	}
}
