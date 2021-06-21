#include "task_start.h"
#include "includes.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "os_cfg.h"
#include <os_app_hooks.h>
#include "key.h"
#include "ucosiii_tmr.h"
#include "sem.h"
#include "message_queue.h"
#include "flag.h"
#include "pendmulti.h"
#include "memory.h"
#include "can.h"
OS_TCB StartTaskTCB;   //������ƿ�
CPU_STK START_TASK_STK[START_STK_SIZE];   //�����ջ
//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
	OSStatTaskCPUUsageInit(&err);  	//ͳ������ ->os_cfg.h:����һЩ��������ĺ궨�� ���� ʱ�ӽ��� ��ʱ��5������               
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ�� ���ͬ���ȼ�����������
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		

/*#if OS_CFG_APP_HOOKS_EN   //ʹ�ܹ��Ӻ���->os_app_hooks.c
	App_OS_SetAllHooks();   //�ڿ�������Ĺ��Ӻ����в��ܳ����ÿ����������ȴ�̬�Ĵ��� ����CPU����������
#endif*/
  //��ʱ�����񴴽�
	#if IS_OPEN_tmr1_TASK  //��ʱ��
	tmr1_task_create();
	#endif
	
	#if IS_OPEN_tmr2_TASK
	tmr2_task_create();
	#endif

	OS_CRITICAL_ENTER();	//�����ٽ���
	
	#if IS_OPEN_sem_TASK   //������
	sem_task_create();
	#endif
	
	#if IS_OPEN_LED0_TASK
	led0_task_create();
	#endif
	
	#if IS_OPEN_LED1_TASK
	led1_task_create();
	#endif
	
	#if IS_OPEN_FLOAT_TASK
	float_test_task_create();
	#endif
	
	#if IS_OPEN_mutex_test_TASK  //�����ź���
	mutex_test_task_creat();
	#endif
	
	#if IS_OPEN_message_queue_TASK  //��Ϣ����
	message_queue_task_creat();
	#endif
	
	#if IS_OPEN_flag_TASK   //�¼���־λ
	flag_task_create();
	#endif
	
	#if IS_OPEN_pendmulti_TASK  //�ȴ�����ں˶���
	pendmulti_task_creat();
	#endif
	
	#if IS_OPEN_memory_TASK   //�ڴ�����
	memory_task_creat();
	#endif
	
	#if IS_OPEN_can1_TASK  //����can1����
	can1_task_creat();
	#endif
	
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}

//������ʼ����
//�������жϷ�������е������񴴽�����
void start_Task_create(void)
{
	OS_ERR err;
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ���(ʱ�ӽ���(OS_CFG_TICK_RATE_HZ=200)/10)*5ms  1:1��ʱ��Ƭ->����=n*5ms
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
}

void BSP_Init(void)
{
	delay_init();       //��ʱ��ʼ��
	LED_Init();         //LED��ʼ��
	KEY_Init();
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,0);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�жϷ�������
	uart_init(115200);    //���ڲ���������
}


