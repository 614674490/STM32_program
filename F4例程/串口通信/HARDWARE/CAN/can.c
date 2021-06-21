#include "can.h"
#include "led.h"
#include "usart2.h"
//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:CAN_SJW_1tq~ CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.   ��Χ:CAN_BS2_1tq~CAN_BS2_8tq;
//tbs1:ʱ���1��ʱ�䵥Ԫ.   ��Χ:CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024; tq=(brp)*tpclk1
//������=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//mode:CAN_Mode_Normal,��ͨģʽ;CAN_Mode_LoopBack,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ42M,�������CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);
//������Ϊ:42M/((6+7+1)*6)=500Kbps
//����ֵ:0,��ʼ��OK;
//    ����,��ʼ��ʧ��; 
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{
	CAN_InitTypeDef        CAN_InitStructuure;
	GPIO_InitTypeDef       GPIO_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	#if CAN_RX0_INT_ENABLE 
	NVIC_InitTypeDef  		NVIC_InitStructure;
  #endif
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);    //ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;     //��������  PA11--RX PA12--TX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_11;   
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//���Ÿ���ӳ������
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11|GPIO_PinSource12,GPIO_AF_CAN1);
	
	//CAN��Ԫ����
	CAN_InitStructuure.CAN_ABOM=DISABLE;                 //����Զ����߹���
	CAN_InitStructuure.CAN_AWUM=DISABLE;                 //˯��ģʽͨ���������
	CAN_InitStructuure.CAN_Mode=mode;                    //0:��ͨģʽ 1:ѭ��ģʽ
	CAN_InitStructuure.CAN_NART=ENABLE;                  //��ֹ�����Զ�����
	CAN_InitStructuure.CAN_RFLM=DISABLE;                 //���Ĳ����� �µĸ��Ǿɵ�
	CAN_InitStructuure.CAN_TTCM=DISABLE;                 //��ʱ�䴥��ģʽ
	CAN_InitStructuure.CAN_TXFP=DISABLE;                 //���ȼ��ɱ��ı�־������
	//���ò�����
	CAN_InitStructuure.CAN_BS1=tbs1;                     //Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructuure.CAN_BS2=	tbs2;                    //Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructuure.CAN_Prescaler=brp;                //��Ƶϵ��(Fdiv)Ϊbrp+1	
	CAN_InitStructuure.CAN_SJW=tsjw;                     //����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
	
	CAN_Init(CAN1,&CAN_InitStructuure);                   //��ʼ��CAN1
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;                         //��������0 ����λ��Ĳ�ͬ ÿ������������ṩ1��32λ������ ���� ����16λ������
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;       //����λģʽ   FBM0=0  
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;      //λ�� 32  FSC0=1
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;                    //32ΪID   ��ʶ��ģʽ�µ�ID
	CAN_FilterInitStructure.CAN_FilterIdLow=0x036F;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;                //32λMASK  ����λģʽ�µ�ID
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x01F8;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;  //���䵽FIFO 0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;                //����ɸѡ��
	/*ÿ�����������������Ĵ��� �ֱ��Ǳ�־���Ĵ���������λ�Ĵ���
	  ���μĴ���������Ϊ�ߵ�ֵ����Ӧ�ı�־���Ĵ�����λΪ����ƥ��λ
		��ʵ �Ĵ��������ID��������ɸѡ��ID ���Ĵ�����������Σ����룩ֻ��������ƥ��Ĺ����� ������������
		�����������������ָID����Щλ�Ǳ���ƥ��λ ��Щλ�ǲ��ع���λ
		��16λģʽ������32λ�Ĵ������ֳ����ĸ�16λ�Ĵ��� ������ģʽ�� ��16λΪ���� ��16λΪID
		���ߵĹ�ϵ��32Bit����ͬ��ֻ�������ݵĿ�ȷ����˱仯
		
		32Bit������λģʽ�� �����Ĵ����ֱ�Ϊ��־���Ĵ���������λ�Ĵ���
		32Bit���б�ģʽ�� �����Ĵ�����Ϊ��־���Ĵ��� ֻҪ���յ���ID��
											����һ���Ĵ�����ֵ��ȫ��ͬ���ɽ��ܸ��豸���͵�����
		16bit������λģʽ�� �����Ĵ����ĵͰ�λ�ֱ���32bit�б�־�������� ���߰�λ��32Bit������λ������
		                    ֻҪ��ϵ������ݷ�������һ���Ĵ�����Ҫ�� �Ϳ��Խ�������
		16Bit���б�ģʽ�� ����32λ�Ĵ����ֳ�4��16λ�ļĴ��� ֻҪ���յ���ID��4���е�һ��ֵ��ȫƥ�� ��ɽ�������
		*/
		/*����32λ����ģʽ      List:FFFF 0000
		                        Mask:FF00 FF00     //��˼�ǽ��յ���ID��ʽ����ΪFFxx00xx
				  32λ�б�ģʽ      List:FFFF 0000
					                  Mask:FF00 FF00     //��˼�ǽ��յ���ID������FFFF 0000Ҳ������FF00 FF00
				  16λ����ģʽ      List:FFFF 0FF0
		                        Mask:FF00 FF00     //��˼�ǽ��յ���ID��ʽ����ΪxFFx����FFxx
					16λ�б�ģʽ      List:FFFF 0FF0
		                        Mask:FF00 FF00     //��˼�ǽ��յ���ID������ FFFF/0FF0/FF00/FF00
		*/
		/*ID�ĵ�һ�����ã�����CAN���ٲã� IDֵԽ�� �������ȼ�Խ��
		  ID�ĵڶ������ã����ɸѡ���� �趨ID�Ľ��շ�Χ ���˵�����Ҫ��ID��Ϣ
		*/
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	#if CAN_RX0_INT_ENABLE
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);                              //��Ϣ�Һ��ж�����
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  #endif
	return 0;
}

#if CAN_RX0_INT_ENABLE   //ʹ��RX0�ж�
//�жϷ�����
void CAN1_RX0_IRQHandler(void)
{
	int i=0;
	CanRxMsg RxMessage;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)==SET)
	{
	  CAN_Receive(CAN1,0,&RxMessage);    //�洢���յ�����Ϣ
		for(i=0;i<len;i++)                 //len<=8
		{
			USART_SendData(USART2,RxMessage.Data[i]);		
			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���		�þ䲻��ʡ����		 
		}
		USART_SendData(USART2,len);		
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���		�þ䲻��ʡ����	
		LED=!LED;
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	}
}
#endif

//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 Can_Send_Msg(u8* msg,u8 len)
{
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	//�ٲö�
	TxMessage.ExtId=0x00;                     //��չ��ʶ��   0x168
	TxMessage.StdId=0x00;                     //��׼��ʶ��
	TxMessage.RTR=CAN_RTR_Data;               //����֡
	//���ƶ�  IDE DLC r0         r1 r0 DLC
	TxMessage.IDE=CAN_Id_Standard;            //��׼֡
	TxMessage.DLC=len;                        //���ݳ���
	//���ݶ�
	for(i=0;i<len;i++)
	TxMessage.Data[i]=msg[i];
	mbox=CAN_Transmit(CAN1,&TxMessage);
	i=0;
	while((CAN_TransmitStatus(CAN1,mbox)==CAN_TxStatus_Failed)&&(i<0xfff)) i++;     //�ȴ����ͽ���
	if(i>=0xfff) return 1;   //����ʧ��
	return 0;                //���ͳɹ�
}

//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 Can_Receive_Msg(u8 *buf)
{
	u32 i;
	CanRxMsg RxMessage;
	if(CAN_MessagePending(CAN1,CAN_FIFO0)==0) return 0;          //û�н��յ����� ����0
	CAN_Receive(CAN1,0,&RxMessage);    //�洢���յ�����Ϣ
	for(i=0;i<RxMessage.DLC;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}




