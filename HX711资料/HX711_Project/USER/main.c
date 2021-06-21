#include "stm32f10x.h" 
#include "sys.h" 
#include "delay.h"
#include "led.h"
#include "oled.h"
#include "hx711.h"
#include "key.h"

 int main(void)
{
	delay_init();
	LED_Init();
	OLED_GPIO_Init();
  OLED_Init();
	KEY_Init(); 
	HX711_Init();
	delay_ms(1000);  //�ȴ�hx711ģ���ȶ�
	Get_Gross_Weight();
	Init_Gross_Weight=Gross_Weight;
	Gross_Weight=0;
	OLED_Display();
	while(1)
	{
		Get_Net_Weight();
		OLED_ShowNum(32,2,Net_Weight,4,16);  //��ʾ����
		OLED_ShowNum(32,6,All_Weight,4,16);  //��ʾ����
		if(Flag_Error)
		{
			led=0;   //ָʾ������������
		}
		else
		{
			led=1;
		}
		if(KEY0==0)  //ȥ��ë��
		{
			delay_ms(50);
			if(KEY0==0)
			{
			  Get_Gross_Weight();   //ȥƤ
				OLED_P8x16Str(0,4,"Del Gross");
			}              
		}
		else if(KEY1==0)  //����ë��
		{
			delay_ms(50);
			if(KEY1==0)
			{
				Gross_Weight=0;
				OLED_P8x16Str(0,4,"Inc Gross");
			}
		}
	}
}


