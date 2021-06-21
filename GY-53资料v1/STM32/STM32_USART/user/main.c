#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "string.h"
 #include "LED.h"
 /*
 Keil: MDK5.10.0.2
MCU:stm32f103c8
Ӳ���ӷ���
GY-53---STM32
1��GY-53_RX---STM32_TX,STM32��λ������A5 45 EA ��ģ��  �����������
2��STM32_TX---FT232,STM32�������ϴ�����λ��
3��GY-53_TX---STM32_RX������ģ������
���˵��:
�ó�����ô��ڷ�ʽ��ȡģ��rgb���ݣ�������115200

ע���жϺ���λ��stm32f10x_it.c
��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_X;
  
  /* 4����ռ���ȼ���4����Ӧ���ȼ� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /*��ռ���ȼ��ɴ���жϼ���͵��ж�*/
	/*��Ӧ���ȼ����ȼ�ִ��*/
	NVIC_X.NVIC_IRQChannel = USART1_IRQn;//�ж�����
  NVIC_X.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
  NVIC_X.NVIC_IRQChannelSubPriority = 0;//��Ӧ���ȼ�
  NVIC_X.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж���Ӧ
  NVIC_Init(&NVIC_X);
}
void send_com(u8 data)  //���������ֽ�
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=data;//�����ֽ�
	USART_Send(bytes,3);//����֡ͷ�������ֽڡ�У���
}

int main(void)
{
  u8 sum=0,i=0;  //sum�����ж�У���
	int16_t data=0;
	uint16_t distance=0;
	delay_init(72);
	NVIC_Configuration();
	Usart_Int(9600);
	delay_ms(500);//�ȴ�ģ���ʼ�����
	send_com(0x45);//���Ͷ�rgbָ��  ����Ϊ���������������
	while(1)
	{
		if(Receive_ok)//���ڽ������
		{
			for(sum=0,i=0;i<(re_Buf_Data[3]+4);i++)//rgb_data[3]=3   [3]+4:���յ���������
			sum+=re_Buf_Data[i];
			if(sum==re_Buf_Data[i])//У����ж�   //Byte7ǰ�������ۼӺ�
			{
				distance=re_Buf_Data[4]<<8|re_Buf_Data[5];   //�������
				//send_3out(&re_Buf_Data[4],3,0x15);//�ϴ�����λ��
			}
			Receive_ok=0;//����������ϱ�־
		}
	}
}
