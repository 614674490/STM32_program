#include "led.h"
#include "stm32f10x.h"
#include "task_start.h"
#include "delay.h"
#include "key.h"
#include "ucosiii_tmr.h"
#include "usart.h"
#include "sem.h"
#include "message_queue.h"
#include "can.h"
u8 led0_task_str[]="led0 running";
u8 led1_task_str[]="led1 running";
float float_num=0.01;
OS_TCB Led0TaskTCB;
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];

OS_TCB Led1TaskTCB;
CPU_STK LED1_TASK_STK[LED1_STK_SIZE];

 OS_TCB	FloatTaskTCB;
__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					
  GPIO_SetBits(GPIOB,GPIO_Pin_0);						

	
}

//led0������
void led0_task(void *p_arg)
{
	static u8 flag=0;
	static u16 led0_task_num=0;
	u8 canbuf[8]={0,1,2,3,4,5,6,7};
	u8 key,*pbuf,size;
	OS_ERR err;          //���ڷ��ش�����Ϣ
	
	CPU_SR_ALLOC();        //Ϊ�˽����ٽ�����д�Ĵ���  
	p_arg = p_arg;
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)
		{
			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,1);
			flag=1;
			
		}
		else if(key==KEY0_PRES)
		{
			CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,0);
			flag=0;
		}
		if(flag)
		{
			Can_Send_Msg(canbuf,8);         //���Ͱ˸��ֽ�
			flag=0;
		}
//		if(key==KEY1_PRES)
//		{
//			OSTaskSemPost(&Led1TaskTCB,OS_OPT_POST_1,&err);
//			printf("led0_task:%d\r\n",Led1TaskTCB.SemCtr);
//			//OSSemPend(&SYNC_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); 	//�����ź��� ��Ctr>1ʱ ��������ɹ� ÿ�ɹ�һ�� Ctr-1 ����ʧ�� ����ִ�к������� ��Ϊ0ʱ ����������ٴ� ��СΪ-1 һ����⵽������ ������ִ������
//		  //printf("led0_task:%d\r\n",SYNC_SEM.Ctr);      //��ʾ�ź���ֵ
//			
//		}

		//sem_share(led0_task_str);
		/*led0_task_num++;
		printf("led0_task��ִ��%d��\r\n",led0_task_num);
		if(led0_task_num==5)
		{
			//OSTaskDel((OS_TCB*)&Led1TaskTCB,&err);	//����1ִ��5�˺�ɾ��������2  ��һ������Ϊ0��ɾ������(����&)
			//printf("led0_task Del led1_task\r\n");
			OS_TaskSuspend((OS_TCB*)&Led1TaskTCB,&err);		//����led1_task
			printf("led0_task Suspend led1_task\r\n");
			
		}
		else if(led0_task_num==10)
		{
			OS_TaskResume((OS_TCB*)&Led1TaskTCB,&err);		//����led1_task  Ϊ0���������
			printf("led0_task Resume led1_task\r\n");
		}*/
		
		/*LED0=0;
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ200ms
		LED0=1;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ500ms*/
	}
}

//led1������
void led1_task(void *p_arg)
{
	static u16 led1_task_num=0;
	OS_ERR err;          //���ڷ��ش�����Ϣ
	u8 key;
	CPU_SR_ALLOC();        //Ϊ�˽����ٽ�����д�Ĵ���  
	p_arg = p_arg;
	while(1)
	{
		//sem_share(led1_task_str);
		key = KEY_Scan(0);
		if(key==KEY0_PRES)   //����һ ������ʱ��1
		{
			OSTaskSemPend(0,OS_OPT_PEND_BLOCKING,0,&err);
			printf("led0_task:%d\r\n",Led1TaskTCB.SemCtr);
			
			//OSSemPost (&SYNC_SEM,OS_OPT_POST_1,&err);				//�����ź��� ÿ����һ�� �ź���+1
			//printf("led1_task:%d\r\n",SYNC_SEM.Ctr);      //��ʾ�ź���ֵ
			/*OSTmrStart(&tmr1,&err);
			OS_CRITICAL_ENTER();	//�����ٽ���
			printf("������ʱ��1\r\n");
			OS_CRITICAL_EXIT();		//�˳��ٽ���*/
		}
		else if(key==KEY1_PRES)  //2������ʱ��2  ���ζ�ʱ�� �������Զ��ر�
		{
			/*OSTmrStop(&tmr1,OS_OPT_TMR_NONE,0,&err);	//�رն�ʱ��1
      OSTmrStart(&tmr2,&err);
			OS_CRITICAL_ENTER();	//�����ٽ���
			printf("�رն�ʱ��1\r\n������ʱ��2\r\n");
			OS_CRITICAL_EXIT();		//�˳��ٽ���*/
		}
		LED1=!LED1;
	}
}

//�����������
void float_task(void *p_arg)
{
	CPU_SR_ALLOC();        //Ϊ�˽����ٽ�����д�Ĵ���  
	 p_arg = p_arg;             //��ֹ����������	
	while(1)
	{
		float_num+=0.01f;
		OS_CRITICAL_ENTER();	//�����ٽ���
		printf("Float:float_num��ֵΪ: %.4f\r\n",float_num);
		OS_CRITICAL_EXIT();		//�˳��ٽ���
		delay_ms(1000);			//��ʱ500ms   //�������ʱ���������ٽ����� ��һֱ��ӡ���� �����Ч��
	}
}

//����LED0����
void led0_task_create(void)
{
	OS_ERR err;
	OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"led0 task", 		    //��������
                 (OS_TASK_PTR )led0_task,   //������
                 (void		* )0,					    //���ݸ��������Ĳ���
                 (OS_PRIO	  )LED0_TASK_PRIO,   //�������ȼ�  
                 (CPU_STK   * )&LED0_TASK_STK[0],		//�����ջ����ַ
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)LED0_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					     //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
}

//����LED1����
void led1_task_create(void)
{
  OS_ERR err;
	OSTaskCreate((OS_TCB 	* )&Led1TaskTCB,		
				 (CPU_CHAR	* )"led1 task", 		
                 (OS_TASK_PTR )led1_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LED1_TASK_PRIO,     	
                 (CPU_STK   * )&LED1_TASK_STK[0],	
                 (CPU_STK_SIZE)LED1_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED1_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
}

//���������������
void float_test_task_create(void)
{
	OS_ERR err;
	OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,		
				 (CPU_CHAR	* )"float test task", 		
                 (OS_TASK_PTR )float_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )FLOAT_TASK_PRIO,     	
                 (CPU_STK   * )&FLOAT_TASK_STK[0],	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
}


