#include "sem.h"
#include "delay.h"
#include "task_start.h"
#include "led.h"
OS_TCB High_TaskTCB;
CPU_STK HIGH_TASK_STK[HIGH_STK_SIZE];

OS_TCB Middle_TaskTCB;
CPU_STK MIDDLE_TASK_STK[MIDDLE_STK_SIZE];

OS_TCB Low_TaskTCB;
CPU_STK LOW_TASK_STK[LOW_STK_SIZE];
/* =====================��غ���======================= */
/*                                                       |
    OSSemCreate()	           //����һ���ź���            |
		OSSemDel()	             //ɾ���ź���                |
		OSSemPend()	             //�ȴ��ź���                |
		OSSemPendAbort()	       //ȡ���ȴ�                  |
		OSSemPost()	             //�ͷ��ź���                |
		OSSemSet()	             //ǿ������һ���ź���        |
		//�����ź���                                         |
		OSMutexCreate()	           //����һ���ź���          |
		OSMutexDel()	             //ɾ���ź���              |
		OSMutexPend()	             //�ȴ��ź���              |
		OSMutexPendAbort()	       //ȡ���ȴ�                |
		OSMutexPost()	             //�ͷ��ź���              |
		//������Ƕ�ź���                                     |
		OSTaskSemPend()	           //����һ���ź���          |
		OSTaskSemPendAbort()	     //ȡ���ȴ�                |
		OSTaskSemPost()	           //�ͷ��ź���              |
		OSTaskSemSet()             //ǿ�����������ź�������  |
*/
/* ==================================================== */

/*                      �ź�������                         */
/* OS_SEM_CTR=1->�������ź��� ֻ����һ��������ʹ�����Դ 
   OS_SEM_CTR=n->�������ź��� ����n������ͬʱ���ʹ�����Դ
	 �������ź��� ��ֹ���ȼ���ת ��0 1 n֮��
	 ������Ƕ�ź��� ���ź������ô��� ��ʵ������ͬ��
*/

/*   �ź����������� OSSemPend->���������Ƿ�ִ��   */
/*
	OS_OPT_PEND_BLOCKING     ָ���ź�����Чʱ ��������Եȴ��ź���	 ����ʱ ��������ִ��
	OS_OPT_PEND_NON_BLOCKING ָ���ź�����Чʱ ����ֱ�ӷ���  �����Կ�ִ��
*/
/* ================= �ź�����; =========================== */
/*
   1.ʵ����������Դ: ÿ����Դ���ж�Ӧ���ź��� ֻ�е�һ����
     ���ø���Դ���ź��� �ſɶ���Դ���з���
	 2.ʵ������ͬ��: ���󲻵��ź��� ��ִ������ ����һ������
	   �����ź���������Ż������ź��� ������������һ�����񴥷�
	 3.���ȼ���ת:������������ʱ �ͼ��������ź��� �м��� �߼���
	   �ź��� �߼��ȴ��ͼ��ͷ��ź����ſ�ִ�� �ڴ��ڼ� �м������
		 ��ϵͼ�����ִ�� �����ڸ߼�����ִ�� �������ź����ɽ����
		 �ȼ���ת����
*/
/* ======================================================== */
u8 share_resource[30];   //������Դ��
OS_SEM	MY_SEM;	
OS_SEM	SYNC_SEM;	
OS_MUTEX	TEST_MUTEX;
void sem_task_create(void)
{
	OS_ERR err;
	OSSemCreate ((OS_SEM*	)&MY_SEM,
                 (CPU_CHAR*	)"MY_SEM",
                 (OS_SEM_CTR)1,		
                 (OS_ERR*	)&err);
	
	OSSemCreate ((OS_SEM*	)&SYNC_SEM,
                 (CPU_CHAR*	)"SYNC_SEM",
                 (OS_SEM_CTR)0,		             //��ʼ�ź���Ϊ0
                 (OS_ERR*	)&err);
	OSMutexCreate((OS_MUTEX*	)&TEST_MUTEX,   //�����ź���
				  (CPU_CHAR*	)"TEST_MUTEX",
                  (OS_ERR*		)&err);
}

void sem_share(char str[])
{
	OS_ERR err;
	OSSemPend(&MY_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); 	//�����ź���
	memcpy(share_resource,str,strlen(str)); //������Դ����������
	delay_ms(300);
	printf("%s\r\n",share_resource);	//�������������Դ������	
	OSSemPost (&MY_SEM,OS_OPT_POST_1,&err);				//�����ź���
}

void mutex_test_task_creat()
{
	OS_ERR err;
	//����HIGH����
	OSTaskCreate((OS_TCB 	* )&High_TaskTCB,		
				 (CPU_CHAR	* )"High task", 		
                 (OS_TASK_PTR )high_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )HIGH_TASK_PRIO,     
                 (CPU_STK   * )&HIGH_TASK_STK[0],	
                 (CPU_STK_SIZE)HIGH_STK_SIZE/10,	
                 (CPU_STK_SIZE)HIGH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);			
	//����MIDDLE����
	OSTaskCreate((OS_TCB 	* )&Middle_TaskTCB,		
				 (CPU_CHAR	* )"Middle task", 		
                 (OS_TASK_PTR )middle_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MIDDLE_TASK_PRIO,     
                 (CPU_STK   * )&MIDDLE_TASK_STK[0],	
                 (CPU_STK_SIZE)MIDDLE_STK_SIZE/10,	
                 (CPU_STK_SIZE)MIDDLE_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		
	//����LOW����
	OSTaskCreate((OS_TCB 	* )&Low_TaskTCB,		
				 (CPU_CHAR	* )"Low task", 		
                 (OS_TASK_PTR )low_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )LOW_TASK_PRIO,     
                 (CPU_STK   * )&LOW_TASK_STK[0],	
                 (CPU_STK_SIZE)LOW_STK_SIZE/10,	
                 (CPU_STK_SIZE)LOW_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);					 
}

//�����ȼ������������
void high_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);   		//��ʱ500ms
		printf("high task Pend Mutex\r\n");
		OSMutexPend (&TEST_MUTEX,0,OS_OPT_PEND_BLOCKING,0,&err);	//���󻥳��ź���
		printf("high task Running!\r\n");
		LED1 = ~LED1;
		OSMutexPost(&TEST_MUTEX,OS_OPT_POST_NONE,&err);				//�ͷŻ����ź���
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);   		//��ʱ500ms
	}
}

//�е����ȼ������������
void middle_task(void *p_arg)
{	
	OS_ERR err;
	
	while(1)
	{
		printf("middle task Running!\r\n");
		LED0 = ~LED0;
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_PERIODIC,&err);   //��ʱ1s
	}
}

//�����ȼ������������
void low_task(void *p_arg)
{	
	static u32 times;
	OS_ERR err;
	while(1)
	{
		OSMutexPend (&TEST_MUTEX,0,OS_OPT_PEND_BLOCKING,0,&err);//���󻥳��ź���
		printf("low task Running!\r\n");
		for(times=0;times<10000000;times++)
		{
			OSSched();											//�����������
		}
		OSMutexPost(&TEST_MUTEX,OS_OPT_POST_NONE,&err);			//�ͷŻ����ź���
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_PERIODIC,&err);   	//��ʱ1s
	}
}
