#include "flag.h"
#include "led.h"
#include "key.h"
#include "task_start.h"

//�¼���־�飺���ڽ��ж������ͬ��ʵ��
/* =====================��غ���======================= */
/*                                                       |
    OSFlagCreate()	         //����һ���¼���־��        |
		OSFlagDel()	             //ɾ��                      |
		OSFlagPend()	             //�ȴ�                    |
		OSFlagPendAbort()	       //ȡ���ȴ�                  |
		OSFlagPost()	             //������־                |
		OSFlagPendGetFlagsRdy()//��ȡʹ����������¼���־    |
*/
/* ==================================================== */

/* =================== OSFlagPend =================== */
/*
	OS_OPT_PEND_FLAG_SET_ALL  //�ȴ����б�־λ��λ
	OS_OPT_PEND_FLAG_CLR_ALL  //�ȴ����б�־λ����
	OS_OPT_PEND_FLAG_SET_ANY  //�ȴ��κα�־λ��λ
	OS_OPT_PEND_FLAG_CLR_ANY  //�ȴ��κα�־λ����
	
	OS_OPT_PEND_FLAG_CONSUME  //�����Ƿ������¼���־��״̬
	OS_OPT_PEND_NON_BLOCKING  //��־λ����������ʱ����������
	OS_OPT_PEND_BLOCKING      //��־λ����������ʱ��������
*/
/* ================================================== */
OS_FLAG_GRP	EventFlags;		//����һ���¼���־��

OS_TCB FLAG_Main_TaskTCB;
CPU_STK FLAG_MAIN_TASK_STK[MAIN_STK_SIZE];

OS_TCB Flagsprocess_TaskTCB;
CPU_STK FLAGSPROCESS_TASK_STK[FLAGSPROCESS_STK_SIZE];
void flag_task_create()
{
	OS_ERR err;
	//����һ���¼���־��
	OSFlagCreate((OS_FLAG_GRP*)&EventFlags,		//ָ���¼���־��
                 (CPU_CHAR*	  )"Event Flags",	//����
                 (OS_FLAGS	  )KEYFLAGS_VALUE,	//�¼���־���ʼֵ
                 (OS_ERR*  	  )&err);			//������
	//����������
	OSTaskCreate((OS_TCB*     )&FLAG_Main_TaskTCB,		
				 (CPU_CHAR*   )"Flag Main task", 		
                 (OS_TASK_PTR )flag_main_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )FLAG_MAIN_TASK_PRIO,     
                 (CPU_STK*    )&FLAG_MAIN_TASK_STK[0],	
                 (CPU_STK_SIZE)FLAG_MAIN_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLAG_MAIN_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);						
	//����MSGDIS����
	OSTaskCreate((OS_TCB*     )&Flagsprocess_TaskTCB,		
				 (CPU_CHAR*   )"Flagsprocess task", 		
                 (OS_TASK_PTR )flagsprocess_task, 			
                 (void* 	  )0,					
                 (OS_PRIO	  )FLAGSPROCESS_TASK_PRIO,     
                 (CPU_STK* 	  )&FLAGSPROCESS_TASK_STK[0],	
                 (CPU_STK_SIZE)FLAGSPROCESS_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLAGSPROCESS_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void* 	  )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR* 	  )&err);
}

//�������������
void flag_main_task(void *p_arg)
{
	u8 key;
	OS_FLAGS flags_num;
	OS_ERR err;
	while(1)
	{
		key = KEY_Scan(0);  //ɨ�谴��
		if(key == KEY0_PRES)
		{
			//���¼���־��EventFlags���ͱ�־
			flags_num=OSFlagPost((OS_FLAG_GRP*)&EventFlags,
								 (OS_FLAGS	  )KEY0_FLAG,
								 (OS_OPT	  )OS_OPT_POST_FLAG_SET,    //��Ӧ��־λ��λ OS_OPT_POST_FLAG_CLR �Ա�־λ����
					       (OS_ERR*	  )&err);
			printf("�¼���־��EventFlags��ֵ:%d\r\n",flags_num);
		}
		else if(key == KEY1_PRES)
		{
			//���¼���־��EventFlags���ͱ�־
			flags_num=OSFlagPost((OS_FLAG_GRP*)&EventFlags,
								 (OS_FLAGS	  )KEY1_FLAG,                 
								 (OS_OPT	  )OS_OPT_POST_FLAG_SET,    //��Ӧ��־λ��λ
								 (OS_ERR*     )&err);
			printf("�¼���־��EventFlags��ֵ:%d\r\n",flags_num);
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);   //��ʱ10ms
	}
}

//�¼���־�鴦������
void flagsprocess_task(void *p_arg)
{
	OS_ERR err; 
	while(1)
	{
		//�ȴ��¼���־��
		OSFlagPend((OS_FLAG_GRP*)&EventFlags,
				   (OS_FLAGS	)KEY0_FLAG+KEY1_FLAG,
		     	   (OS_TICK     )0,
				   (OS_OPT	    )OS_OPT_PEND_FLAG_SET_ALL+OS_OPT_PEND_FLAG_CONSUME+OS_OPT_PEND_BLOCKING,  //�ȴ����б�־λ��λ ����ϴμ�¼(����ջ�һֱ����)
				   (CPU_TS*     )0,
				   (OS_ERR*	    )&err);
		LED1 = ~LED1;    //�������������� �ſɴ������¼�
		printf("�¼���־��EventFlags��ֵ:%d\r\n",EventFlags.Flags);
	}
}


