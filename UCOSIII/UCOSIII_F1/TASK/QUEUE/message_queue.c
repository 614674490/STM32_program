#include "message_queue.h"
#include "task_start.h"
#include "key.h"
#include "led.h"
#include "usart.h"
OS_Q KEY_Msg;
OS_TCB Keyprocess_TaskTCB;
CPU_STK KEYPROCESS_TASK_STK[KEYPROCESS_STK_SIZE];

OS_Q DATA_Msg;				//����һ����Ϣ���У����ڷ�������

OS_TCB Main_TaskTCB;
CPU_STK MAIN_TASK_STK[MAIN_STK_SIZE];

/* =====================��غ���======================= */
/*                                                       |
    OSQCreate()	           //����һ����Ϣ����            |
		OSQDel()	             //ɾ����Ϣ����                |
		OSQFlush()	             //�����Ϣ����              |
		OSQPend()	            //�ȴ���Ϣ����                 |
		OSQPendPost()	        //ȡ���ȴ���Ϣ����             |
		OSQPost()	            //����Ϣ���з���һ����Ϣ       |
		//�����ڽ���Ϣ����                                   |->OS_CFG_TASK_Q_EN=1
		OSTaskQPend()	           //����һ����Ϣ����          |
		OSTaskQPendAbort()	     //ȡ���ȴ�                  |
		OSTaskQPost()	           //������Ϣ                  |
		OSTaskQFlush()            //����������Ϣ����       |
*/
/* ==================================================== */
void message_queue_task_creat()
{
	OS_ERR err;
	//������Ϣ����KEY_Msg
	OSQCreate ((OS_Q*		)&KEY_Msg,	//��Ϣ����
                (CPU_CHAR*	)"KEY Msg",	//��Ϣ��������
                (OS_MSG_QTY	)KEYMSG_Q_NUM,	//��Ϣ���г��ȣ���������Ϊ1 ���������
                (OS_ERR*	)&err);		//������
		//������Ϣ����DATA_Msg
	OSQCreate ((OS_Q*		)&DATA_Msg,	
                (CPU_CHAR*	)"DATA Msg",	
                (OS_MSG_QTY	)DATAMSG_Q_NUM,	
                (OS_ERR*	)&err);	
	//������������
	OSTaskCreate((OS_TCB 	* )&Keyprocess_TaskTCB,		
				 (CPU_CHAR	* )"Keyprocess task", 		
                 (OS_TASK_PTR )Keyprocess_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )KEYPROCESS_TASK_PRIO,     
                 (CPU_STK   * )&KEYPROCESS_TASK_STK[0],	
                 (CPU_STK_SIZE)KEYPROCESS_STK_SIZE/10,	
                 (CPU_STK_SIZE)KEYPROCESS_STK_SIZE,		
                 (OS_MSG_QTY  )TASK_Q_NUM,		//����MsgKeyprocess_Task��Ҫʹ���ڽ���Ϣ���У���Ϣ���г���Ϊ4						
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);	
  OSTaskCreate((OS_TCB 	* )&Main_TaskTCB,		
				 (CPU_CHAR	* )"Main task", 		
                 (OS_TASK_PTR )main_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MAIN_TASK_PRIO,     
                 (CPU_STK   * )&MAIN_TASK_STK[0],	
                 (CPU_STK_SIZE)MAIN_STK_SIZE/10,	
                 (CPU_STK_SIZE)MAIN_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);									 
}
//�������������������
void Keyprocess_task(void *p_arg)
{	
	u8 *key,*pbuf;
	OS_MSG_SIZE size;
	OS_ERR err;
	while(1)
	{
		//������ϢKEY_Msg
		key=OSQPend((OS_Q*			)&KEY_Msg,   
					(OS_TICK		)0,
                    (OS_OPT			)OS_OPT_PEND_BLOCKING, //����ģʽ
                    (OS_MSG_SIZE*	)&size,		
                    (CPU_TS*		)0,                 //ʱ���
                    (OS_ERR*		)&err);
		switch(*key)
		{
			case KEY1_PRES:		
				pbuf=OSTaskQPend((OS_TICK		)0,
                      (OS_OPT		)OS_OPT_PEND_BLOCKING,
                      (OS_MSG_SIZE*	)&size,
                      (CPU_TS*		)0,
                      (OS_ERR*      )&err );
			printf("Keyprocess_TaskTCB::%s\r\n",pbuf);  //��ӡ���յ�����Ϣ
		  free(pbuf);  //�ͷ��ڴ�
				break;
			case KEY0_PRES:		
				/*pbuf=OSQPend((OS_Q*			)&DATA_Msg,   
					(OS_TICK		)0,
										 (OS_OPT			)OS_OPT_PEND_BLOCKING, //����ģʽ
										 (OS_MSG_SIZE*	)&size,		
										 (CPU_TS*		)0,                 //ʱ���
										 (OS_ERR*		)&err);
		printf("DATA_Msg:%s\r\n",pbuf);  //��ӡ���յ�����Ϣ
		free(pbuf);  //�ͷ��ڴ�*/
				break;
		}
	}
}

//�������������
void main_task(void *p_arg)
{
	static u8 num=0;
	char *message_test;
	char *q;
	u8 key;
	OS_ERR err;
	
	while(1)
	{
		key = KEY_Scan(0);  //ɨ�谴��
		if(key)
		{
			
			//������Ϣ
			OSQPost((OS_Q*		)&KEY_Msg,		
					(void*		)&key,               //��������
					(OS_MSG_SIZE)1,                //�����ֽ���
					(OS_OPT		)OS_OPT_POST_FIFO,   //��Ϣ���Ͳ�������
					(OS_ERR*	)&err);
		//������Ϣ->��һ�������� ���Ͷ�����Ϣ
					if(key==KEY1_PRES)
					{
						/*message_test=(char *)malloc(10);  //����mallocʱ Ҫ��ħ�������Use MicroLIB ��ѡ
						num++;
						sprintf((char*)message_test,"message:%d",num);	//��ʾDATA_Msg��Ϣ�����ܵĴ�С 
						OSQPost((OS_Q*		)&DATA_Msg,		
								(void*		)message_test,
								(OS_MSG_SIZE)10,
								(OS_OPT		)OS_OPT_POST_FIFO+OS_OPT_POST_ALL,  //LIFO ����ȳ�  FIFO �Ƚ��ȳ�  ALL������Ϣ���͸����еȴ������� ���FIFO��LIFOʹ�� Ĭ����FIFO
								(OS_ERR*	)&err);
						if(err != OS_ERR_NONE) //Ҫ����malloc ��free�������Ϣ�ķ��ͺͽ��� ��Ȼ֮ǰ����Ϣ�ᱻ�������Ϣ���� Ч��������LIFO �� FIFO��ѡ�� ��������ΪALL ����Ϣ���͸��ȴ����������ȼ���ߵ�����
		        {
							free(message_test);	//�ͷ��ڴ�
						  printf("DATA_Msg:messag queue have fulled\r\n");  //��ʾ��Ϣ��������
		        }
						check_msg_queue(DATA_Msg);  //��ʾ��Ϣ������������ʣ������*/

					}
					else if(key==KEY0_PRES)
					{
						q=(char *)malloc(10);  //����mallocʱ Ҫ��ħ�������Use MicroLIB ��ѡ
						num++;
						sprintf((char*)q,"message:%d",num);	//��ʾDATA_Msg��Ϣ�����ܵĴ�С 
						OSTaskQPost((OS_TCB*	)&Keyprocess_TaskTCB,	//Keyprocess_TaskTCB������Ϣ
                    (void*		)q,
                    (OS_MSG_SIZE)10,
                    (OS_OPT		)OS_OPT_POST_LIFO,
					  (OS_ERR*	)&err);
						if(err != OS_ERR_NONE) //Ҫ����malloc ��free�������Ϣ�ķ��ͺͽ��� ��Ȼ֮ǰ����Ϣ�ᱻ�������Ϣ���� Ч��������LIFO �� FIFO��ѡ�� ��������ΪALL ����Ϣ���͸��ȴ����������ȼ���ߵ�����
		        {
							free(q);	//�ͷ��ڴ�
							printf("messag queue have fulled\r\n");  //��ʾ��Ϣ��������
		        }
						printf("Keyprocess_TaskTCB:Total Size:%d  remain Size:%d\r\n",Keyprocess_TaskTCB.MsgQ.NbrEntriesSize,Keyprocess_TaskTCB.MsgQ.NbrEntriesSize-Keyprocess_TaskTCB.MsgQ.NbrEntries);
					}
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);   //��ʱ10ms  ��ʱ����� ��Ȼ���ղ�����Ϣ
		
	}
}

//��ѯDATA_Msg��Ϣ�����е��ܶ���������ʣ���������
void check_msg_queue(OS_Q Msg)
{
	CPU_SR_ALLOC();
	u8 msgq_remain_size;	//��Ϣ����ʣ���С
	OS_CRITICAL_ENTER();	//�����ٽ��
	msgq_remain_size = Msg.MsgQ.NbrEntriesSize-Msg.MsgQ.NbrEntries; //ʣ����=����-ʹ����
	printf("Total Size:%d  remain Size:%d\r\n",DATA_Msg.MsgQ.NbrEntriesSize,msgq_remain_size);
	OS_CRITICAL_EXIT();		//�˳��ٽ��
}
