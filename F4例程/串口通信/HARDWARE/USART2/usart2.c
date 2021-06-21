#include "usart2.h"

u8 USART2_RX_BUF[USART2_REC_LEN]; //���������洢���յ������ݣ���USART3_REC_LENΪ����ܽ��յ��ֽ��޶�
u16 USART2_RX_STA=0;         		//����״̬���	 0-14λΪ�����ֽ�����15λ������ɱ�־λ
u16 len;                        //��¼���鳤��
u8 flag=0;                      //���������ɱ�־λ
void usart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	//���ڶ���Ӧ���Ÿ���
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;            //����
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;       //�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;   //�ٶ� 100MHZ
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  //��Ӳ��������
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;                //����żУ��λ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;              //һ��ֹͣλ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;          //8λ����
	USART_Init(USART2,&USART_InitStructure);
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
	
	//Usart2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

u16 len;
u8 flag;
void USART2_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)         //���յ�����
	{
		res=USART_ReceiveData(USART2);
		if(!flag)
		{
			USART2_RX_BUF[USART2_RX_STA&0x7fff]=res;                      //��¼���յ���ֵ
			len=(++USART2_RX_STA)&0x7fff;
		}
		if(USART2_RX_BUF[0]!=0xaa)
			USART2_RX_STA=0;
		else
		{
			if(res==0x55)
			{
				flag=1;                      //��ֹͣ����Ľ���
				USART2_RX_STA|=0x8000;
			}
		}
		if((USART2_RX_STA&0x7fff)>USART2_REC_LEN)
			USART2_RX_STA|=0x8000;                        //ǿ�ƽ������
		USART_ClearITPendingBit(USART2,USART_IT_RXNE );
	}
}





