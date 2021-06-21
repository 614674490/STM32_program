#include "can.h"
#include "includes.h"
#include "can_task.h"
#include "led.h"
CanRxMsg RxMessage;
//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:CAN_SJW_1tq~ CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.   ��Χ:CAN_BS2_1tq~CAN_BS2_8tq;
//tbs1:ʱ���1��ʱ�䵥Ԫ.   ��Χ:CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024;  tq=(brp)*tpclk1
//������=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//mode:CAN_Mode_Normal,��ͨģʽ;CAN_Mode_LoopBack,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ36M,�������CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);
//������Ϊ:36M/((8+9+1)*4)=500Kbps
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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //ʹ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;     //��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;          //TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;     //��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;          //RX
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
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
	
	CAN_FilterInitStructure.CAN_FilterNumber=0;                         //������0
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask;       //����λģʽ   
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit;      //λ�� 32
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;                    //32ΪID
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;                //32λMASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;  //���䵽FIFO 0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;                //���������0 �����޷���������
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	#if CAN_RX0_INT_ENABLE
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);                              //��Ϣ�Һ��ж�����
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  #endif
	return 0;
}

#if CAN_RX0_INT_ENABLE   //ʹ��RX0�ж�
//�жϷ�����
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	OS_ERR err;
	OSIntEnter();
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)   //ȷ���Ƿ���յ���Ϣ
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
		OSSemPost(&CAN1_SEM,OS_OPT_POST_1,&err);//�����ź��� 
	}
	OSIntExit();
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
	TxMessage.ExtId=0x00;                     //��չ��ʶ��
	TxMessage.StdId=0x201;                     //��׼��ʶ��
	TxMessage.IDE=CAN_Id_Standard;            //��׼֡
	TxMessage.RTR=CAN_RTR_Data;               //����֡
	TxMessage.DLC=len;                        //���ݳ���
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
	for(i=0;i<8;i++)
	buf[i]=RxMessage.Data[i];
	return RxMessage.DLC;
}




