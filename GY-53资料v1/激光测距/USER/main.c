#include "stm32f10x.h" 
#include "sys.h" 
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "oled.h"
#include "key.h"

//���������ֽ�
//�����ʽ��0xA5+command+sum
void send_com(u8 data)   //���������ֽ�
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=data;
	USART_Send(bytes,3);         //����֡ͷ ���� У���
}
 int main(void)
{
	u8 sum,i;  //sum�����ж�У���
	u16 distance;
	u8 k;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	                         //���ڳ�ʼ��Ϊ9600
	LED_Init();
	delay_init();
	KEY_Init();
	OLED_GPIO_Init();                            //OLED��ʼ��
  OLED_Init();
	delay_ms(500);                            //�ȴ�ģ���ʼ�����
	send_com(0x45);//���Ͷ�rgbָ��  ����Ϊ���������������
	led=1;
	OLED_P8x16Str(0,0,"Mode:");
	OLED_P8x16Str(0,2,"KEY0:normal");
	OLED_P8x16Str(0,4,"WK_UP:fast");
	OLED_P8x16Str(32,6,"mm");
	while(1)
	{
//		if(Receive_ok)  //���ڽ������
//		{
//			for(sum=0,i=0;i<(re_Buf_Data[3]+4);i++) //rgb_data[3]=3   [3]+4:���յ���������
//			{
//				sum+=re_Buf_Data[i];
//			  if(sum==re_Buf_Data[i])//У����ж�   //Byte7ǰ�������ۼӺ�
//			  {
//			  	distance=re_Buf_Data[4]<<8|re_Buf_Data[5];   //�������  ��λΪmm
//					OLED_ShowNum(0,2,distance,4,16);
//					led=!led;
//			  }
//			  Receive_ok=0;     //���ݽ��մ������
//		  } 
//	  }
		k=KEY_Scan(0);     //��֧��������
		if(k==KEY0_PRES)
		{
			send_com(0x53);        //�߾��Ȳ���
		}
		if(k==WK_UP_PRES)
		{
			send_com(0x51);        //���ٲ���
		}
		if(USART_RX_STA&0x8000)
		{
			if((USART_RX_BUF[0]==0x5a)&&(USART_RX_BUF[1]==0x5a))
			{
				distance=USART_RX_BUF[4]<<8|USART_RX_BUF[5];   //�������  ��λΪmm
			  OLED_ShowNum(0,6,distance,4,16);
				switch (USART_RX_BUF[6])
				{
					case 0x03:
						OLED_P8x16Str(40,0,"normal");
					  break;
					case 0x02:
						OLED_P8x16Str(40,0,"high  ");
					  break;
					case 0x01:
						OLED_P8x16Str(40,0,"fast  ");
					  break;
					case 0x00:
						OLED_P8x16Str(40,0,"long  ");
					  break;
				}
			}
			USART_RX_STA=0;
		}
  }
}


