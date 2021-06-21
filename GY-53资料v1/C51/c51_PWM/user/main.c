#include <reg52.h>
#include "usart.h"
#include "iic.h"  
/*
Ӳ���ӷ���
GY-53----C51
PWM_input---P3^7
C51---FT232
TX ---RX
RX ---TX
���˵����
�ó������PWM���ж�ȡ���� ,����=�ߵ�ƽʱ��(us)/10

��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
void TIME0_Int(uint32_t BaudRatePrescaler)
{
	 TMOD |= 0x01;//��ʱ��0��������ʽ1��16λ����
     TH0   =0; 
	 TL0   =0;
	 ET0 =0;
  
}
void delay(unsigned int x)
{
	while(x--);
}
sbit PWM_pin=P3^7;
int main(void)
{
	unsigned char  raw_data[9]={0};
	unsigned int buf=0,distance=0;
	Usart_Int(9600);   
	TIME0_Int();
	while(PWM_pin);	 //�ȴ�����
 	while(1)
	{
	  while(!PWM_pin); //�ȴ����ͣ�������ʱ
	  ET0=1;
	  TR0=1;
	  while(PWM_pin);//�ȴ����ߣ��رն�ʱ
	  TR0=0x0;
	  ET0=0x0;

	  buf=(unsigned int)TH0<<8|TL0;	 //��ȡ��ʱ������
	  distance=(float)buf/110.592*12;//����ת��Ϊ���룬��ʱ����һ��ʱ��Ϊ12/11.0592������us������=ʱ��(us)/10
	  raw_data[0] =distance>>8;
	  raw_data[1] =	distance;
	  raw_data[2] =2; //ģ��Ĭ��ģʽ
	  send_3out(raw_data,3,0x15);//�ϴ�����λ��
	   TH0   =0x0; 
	   TL0   =0x0;
	 
	}
}
