#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "usart2.h"
#include "can.h"
int main(void)
{ 
	u8 i,t;
	u8 canbuf[8];
	delay_init(168);		  //��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           //����Ϊ��2��  2λ��ռ 2λ��Ӧ
	LED_Init();		        //��ʼ��LED�˿�
	usart2_init(115200);
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);  //500Kpbs ����ģʽ
	while(1)
	{
		if(USART2_RX_STA&0x8000)
		 {
			 Can_Send_Msg(USART2_RX_BUF,len);     //����ȡ������ͨ��CAN���͸�����
			 USART2_RX_STA=0;
			 flag=0;
		 }//CANһ��������ܷ���/����8������
//		 t=Can_Receive_Msg(canbuf);
//		 if(t)  //���յ�����
//		 {
//			 for(i=0;i<t;i++)
//			 {
//				 USART_SendData(USART2,canbuf[i]);		
//				 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���		�þ䲻��ʡ����		 
//			 }
//		 }
	}
}

