#include "stm32f10x.h" 
#include "sys.h" 
#include "delay.h"
#include "led.h"
#include "key.h"
#include "spi.h"
#include "oled.h"
#include "rc522.h"
#include "timer.h"
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	LED_Init();
	OLED_GPIO_Init();
	OLED_Init();
	KEY_Init();
	while(RC522_Init());   //�ȴ���ʼ���ɹ�
	OLED_Display();
	TIM2_Int_Init(1999,7199);     //200ms   ���Ƶ�
	while(1)
	{
		RFID_Handle(2);  //��ȡ����2
	}
		
	
}






