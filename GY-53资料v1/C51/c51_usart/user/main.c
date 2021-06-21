#include <reg52.h>
#include "usart.h"
#include "iic.h"  
/*
Ӳ���ӷ���
GY-53---c51
1��GY-53_RX---c51_TX,c51��λ������A5 45 EA ��ģ��
2��c51_TX---FT232,STM32�������ϴ�����λ��
3��GY-53_TX---c51_RX������ģ��Ƕ�����
���˵��:
�ó�����ô��ڷ�ʽ��ȡģ�����ݣ�������9600

ע���жϺ���λ��stc_it.c
��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
void send_com(u8 datas)
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=datas;//�����ֽ�
	USART_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
}

int main(void)
{

    u8 sum=0,i=0;
	uint16_t distance=0;
	Usart_Int(9600);
	send_com(0x45);//���Ͷ���λ��ָ��
 	while(1)
	{
		if(Receive_ok)//���ڽ������
		{
			for(sum=0,i=0;i<(re_Buf_Data[3]+4);i++)//rgb_data[3]=3
			sum+=re_Buf_Data[i];
			if(sum==re_Buf_Data[i])//У����ж�
			{
				distance=re_Buf_Data[4]<<8|re_Buf_Data[5];
				send_3out(&re_Buf_Data[4],3,0x15);//�ϴ�����λ��
			}
			Receive_ok=0;//����������ϱ�־
		}	
	}
}
