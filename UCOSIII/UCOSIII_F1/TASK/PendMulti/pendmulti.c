#include "pendmulti.h"
#include "led.h"
#include "key.h"
#include "task_start.h"
//ͬʱ�ȴ�����ں˶���->�����Ϣ���к���Ϣ�� ���ܵȴ���������ź������¼���־�� OS_CFG_PEND_MULTI_EN=1u
OS_TCB MULTI_MAIN_TaskTCB;
CPU_STK MULTI_MAIN_TASK_STK[MULTI_MAIN_STK_SIZE];

OS_TCB Multi_TaskTCB;
CPU_STK MULTI_TASK_STK[MULTI_STK_SIZE];

OS_SEM	Test_Sem1;			//�ź���1		
OS_Q	Test_Q;				//��Ϣ����	
void pendmulti_task_creat(void)
{
	OS_ERR err;
	//�����ź���Test_Sem1
	OSSemCreate ((OS_SEM*	)&Test_Sem1,
                 (CPU_CHAR*	)"Test_Sem1",
                 (OS_SEM_CTR)0,		
                 (OS_ERR*	)&err);
	//������Ϣ����
	OSQCreate ((OS_Q*		)&Test_Q,	//��Ϣ����
                (CPU_CHAR*	)"KEY Msg",	//��Ϣ��������
                (OS_MSG_QTY	)QUEUE_NUM,	//��Ϣ���г���
                (OS_ERR*	)&err);		//������
	//����TASK1����
	OSTaskCreate((OS_TCB 	* )&MULTI_MAIN_TaskTCB,		
				 (CPU_CHAR	* )"Multi main task", 		
                 (OS_TASK_PTR )multi_main_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MULTI_MAIN_TASK_PRIO,     
                 (CPU_STK   * )&MULTI_MAIN_TASK_STK[0],	
                 (CPU_STK_SIZE)MULTI_MAIN_STK_SIZE/10,	
                 (CPU_STK_SIZE)MULTI_MAIN_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);				
	//����MULTI��������
	OSTaskCreate((OS_TCB 	* )&Multi_TaskTCB,		
				 (CPU_CHAR	* )"Multi task", 		
                 (OS_TASK_PTR )multi_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MULTI_TASK_PRIO,     
                 (CPU_STK   * )&MULTI_TASK_STK[0],	
                 (CPU_STK_SIZE)MULTI_STK_SIZE/10,	
                 (CPU_STK_SIZE)MULTI_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
}
//����1��������
void multi_main_task(void *p_arg)
{
	u8 key;
	OS_ERR err;
	char *pbuf;
	static u8 msg_num;
	
	while(1)
	{
		key = KEY_Scan(0);  //ɨ�谴��
		switch(key)
		{
			case KEY1_PRES:
				OSSemPost(&Test_Sem1,OS_OPT_POST_1,&err);//�����ź���1
				break;
			case KEY0_PRES:
				pbuf=(char *)malloc(8);	//�����ڴ�
				msg_num++;
				sprintf((char*)pbuf,"multi %d",msg_num);
				//������Ϣ
				OSQPost((OS_Q*		)&Test_Q,		
						(void*		)pbuf,
						(OS_MSG_SIZE)10,
						(OS_OPT		)OS_OPT_POST_FIFO,
						(OS_ERR*	)&err);
						if(err != OS_ERR_NONE) //Ҫ����malloc ��free�������Ϣ�ķ��ͺͽ��� ��Ȼ֮ǰ����Ϣ�ᱻ�������Ϣ���� Ч��������LIFO �� FIFO��ѡ�� ��������ΪALL ����Ϣ���͸��ȴ����������ȼ���ߵ�����
		        {
							free(pbuf);	//�ͷ��ڴ�
						  printf("messag queue have fulled\r\n");  //��ʾ��Ϣ��������
		        }
				break;
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);   //��ʱ10ms
	}
}

//�ȴ�����ں˶����������
void multi_task(void *p_arg)
{	
	OS_ERR err;
	OS_OBJ_QTY index=0;   ///��¼���������Ŀ
	OS_PEND_DATA pend_multi_tbl[CORE_OBJ_NUM];	   //�����ں˶�������
	
	pend_multi_tbl[0].PendObjPtr=(OS_PEND_OBJ*)&Test_Sem1;  //��ʼ���ں˶���
	pend_multi_tbl[1].PendObjPtr=(OS_PEND_OBJ*)&Test_Q;
	
	while(1)
	{
		index=OSPendMulti((OS_PEND_DATA*	)pend_multi_tbl,	
						  (OS_OBJ_QTY		)CORE_OBJ_NUM,	//�ȴ��ں�����
						  (OS_TICK		   	)0,		   //��ʱֵ
						  (OS_OPT         	)OS_OPT_PEND_BLOCKING,
						  (OS_ERR*			)&err);
		printf("REQUST OBJ NUM:%d",index);
		if(pend_multi_tbl[1].RdyObjPtr==(OS_PEND_OBJ*)&Test_Q)  //pend_multi_tbl[n]. ����������ں˶����������Ϣ
		{
			printf("%s\r\n",pend_multi_tbl[1].RdyMsgPtr);
		}
		else if(pend_multi_tbl[0].PendObjPtr==(OS_PEND_OBJ*)&Test_Sem1)
		{
			printf("Test Sem1\r\n");
		}
		LED0=!LED0;
		
	}
}



	


