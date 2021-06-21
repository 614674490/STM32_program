#include "stm32f10x.h" 
#include "sys.h" 
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "iic.h"
#include "ks103.h"
#include "usart2.h"
#include "key.h"
#include "string.h"
int main(void)
{
	u8 k;
	u8 flag=0;
	u32 distance=0;
	delay_init();
	LED_Init();
	Ks103_Init();
	KEY_Init();
	Ks103_Write_byte(SlaveAddress1,Res_2,Noise_Reduction_2);//һ������
	delay_ms(2000);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);
	USART2_Init(9600);                            //KS103Ĭ��ģ���� 9600
	while(1)
	{
		k=KEY_Scan(0);
		if(k==KEY0_PRES) flag=!flag;  //Ĭ�����¶Ȳ���  PB5�ڿ���NVIC�жϺ󲻿���
		/*IICģʽ*/
		if(flag)
		{
			if(Read_Ks103_Data(SlaveAddress1,Temp0_5m))
			{
				distance=Read_Ks103_Data(SlaveAddress1,Temp0_5m);
		    printf("IIC_YT:distance=%dmm\r\n",distance);
			}
		}
		else
		{
			if(distance!=Read_Ks103_Data(SlaveAddress1,Notemp0_5m))   //�жϻ�ȡֵ�Ƿ���ȷ
			{
				distance=Read_Ks103_Data(SlaveAddress1,Notemp0_5m);
				printf("IIC_NT:distance=%dmm\r\n",distance);
			}
	  }
		/*����ģʽ ��ʱ������*/
		/*Send_Command(Notemp0_5m);         //���;���̽������
		if(USART_RX_STA&0x8000)
		{
			distance=USART_RX_BUF[0]<<8|USART_RX_BUF[1];
			printf("TTL:distance=%dmm\r\n",distance);
			USART_RX_STA=0;
			memset(USART_RX_BUF,0,strlen((char *)USART_RX_BUF));
		}*/
	}

}


