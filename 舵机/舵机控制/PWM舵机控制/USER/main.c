#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "OLED_I2C.h"
#include<string.h>
#include<stdio.h>
/************************************************
 ALIENTEKս��STM32������ʵ��9
 PWM���ʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

	
 int main(void)
 {	
 	u16 led0pwmval=0;
  unsigned char PWMStr[20];
	unsigned char AngleStr[20];
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
 	TIM3_PWM_Init(1999,719);	 //����Ƶ��PWMƵ��=72000000/900=80Khz
	I2C_Configuration();
	OLED_Init();
	OLED_CLS();//����
  while(1)
	{
		u8 i=0;
		int angle=0;
		/*
		for(i=0;i<6;i++)
		{
			switch(i)
			{
				case 0:led0pwmval=1750;break;//0  0.5ms
				case 1:led0pwmval=1950;break;//45  1ms
				case 2:led0pwmval=1850;break;//90  1.5ms
				case 3:led0pwmval=1900;break;//135	2ms
				case 4:led0pwmval=1950;break;//180	2.5ms
				case 5:led0pwmval=1784; break;//30
			}
			
			//led0pwmval=(int)2000*(1-( ( 2.5-(angle/90.0) )/20.0 )  )-1;
			TIM_SetCompare2(TIM3,led0pwmval);
			//angle=30*(i+1);
			delay_ms(1600);
		}
		*/
		for(i=0;i<=6;i++)
		{
			angle=30*i;
			led0pwmval=(int)(2000*(1-( ( 2.5-(angle/90.0) )/20.0 )  ))-1;
			//printf("pwm=:%d\n",led0pwmval);
			sprintf(PWMStr,"%d",led0pwmval);
			sprintf(AngleStr,"%d",angle);
			OLED_ShowStr(0,0,"         ",2);//����
			OLED_ShowStr(0,0,"pwm=",2);
			OLED_ShowStr(48,0,PWMStr,2);
			OLED_ShowStr(0,2,"         ",2);//����
			OLED_ShowStr(0,2,"angle=",2);
			OLED_ShowStr(48,2,AngleStr,2);
			TIM_SetCompare2(TIM3,led0pwmval);
			delay_ms(1000);
		}
	}	 
}