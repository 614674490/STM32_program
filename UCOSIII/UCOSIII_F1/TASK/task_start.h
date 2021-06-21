#ifndef _task_start_h_
#define _task_start_h_
#include "includes.h"
#include "sys.h"
extern float float_num;
//UCOSIII���������ȼ��û�������ʹ�ã�ALIENTEK
//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()

//�������ȼ�    
#define START_TASK_PRIO		3
//�����ջ��С  
#define START_STK_SIZE 		512
//������ƿ�
extern OS_TCB StartTaskTCB;
//�����ջ	
extern CPU_STK START_TASK_STK[START_STK_SIZE];  //��ջ��С=START_STK_SIZE*4�ֽ�
//������
void start_task(void *p_arg);
void start_Task_create(void);

//�������ȼ�
#define LED0_TASK_PRIO		4
//�����ջ��С	
#define LED0_STK_SIZE 		128
//������ƿ�
extern OS_TCB Led0TaskTCB;
//�����ջ	
extern CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
void led0_task(void *p_arg);
void led0_task_create(void);

//�������ȼ�
#define LED1_TASK_PRIO		5
//�����ջ��С	
#define LED1_STK_SIZE 		128  //*4���ֽ�
//������ƿ�
extern OS_TCB Led1TaskTCB;
//�����ջ	
extern CPU_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *p_arg);
void led1_task_create(void);

//�������ȼ�
#define FLOAT_TASK_PRIO		6
//�����ջ��С
#define FLOAT_STK_SIZE		128
//������ƿ�
extern OS_TCB	FloatTaskTCB;
//�����ջ
extern __align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//������
void float_task(void *p_arg);
void float_test_task_create(void);

//�������ȼ�
#define HIGH_TASK_PRIO			7
//�����ջ��С	
#define HIGH_STK_SIZE 			128
//������ƿ�
extern OS_TCB High_TaskTCB;
//�����ջ	
extern CPU_STK HIGH_TASK_STK[HIGH_STK_SIZE];
void high_task(void *p_arg);


//�������ȼ�
#define MIDDLE_TASK_PRIO		8
//�����ջ��С	
#define MIDDLE_STK_SIZE 		128
//������ƿ�
extern OS_TCB Middle_TaskTCB;
//�����ջ	
extern CPU_STK MIDDLE_TASK_STK[MIDDLE_STK_SIZE];
void middle_task(void *p_arg);

//�������ȼ�
#define LOW_TASK_PRIO			9
//�����ջ��С	
#define LOW_STK_SIZE 			128
//������ƿ�
extern OS_TCB Low_TaskTCB;
//�����ջ	
extern CPU_STK LOW_TASK_STK[LOW_STK_SIZE];
void low_task(void *p_arg);

//�������ȼ�
#define MAIN_TASK_PRIO		10
//�����ջ��С	
#define MAIN_STK_SIZE 		128
//������ƿ�
extern OS_TCB Main_TaskTCB;
//�����ջ	
extern CPU_STK MAIN_TASK_STK[MAIN_STK_SIZE];
void main_task(void *p_arg);

//�������ȼ�
#define KEYPROCESS_TASK_PRIO 	11
//�����ջ��С	
#define KEYPROCESS_STK_SIZE 	128
//������ƿ�
extern OS_TCB Keyprocess_TaskTCB;
//�����ջ	
extern CPU_STK KEYPROCESS_TASK_STK[KEYPROCESS_STK_SIZE];
//������
void Keyprocess_task(void *p_arg);

//�������ȼ�
#define FLAG_MAIN_TASK_PRIO		12
//�����ջ��С	
#define FLAG_MAIN_STK_SIZE 		128
//������ƿ�
extern OS_TCB FLAG_Main_TaskTCB;
//�����ջ	
extern CPU_STK FLAG_MAIN_TASK_STK[MAIN_STK_SIZE];
void flag_main_task(void *p_arg);

//�������ȼ�
#define FLAGSPROCESS_TASK_PRIO	13
//�����ջ��С	
#define FLAGSPROCESS_STK_SIZE 	128
//������ƿ�
extern OS_TCB Flagsprocess_TaskTCB;
//�����ջ	
extern CPU_STK FLAGSPROCESS_TASK_STK[FLAGSPROCESS_STK_SIZE];
//������
void flagsprocess_task(void *p_arg);

//�������ȼ�
#define MULTI_MAIN_TASK_PRIO		14
//�����ջ��С	
#define MULTI_MAIN_STK_SIZE 		128
//������ƿ�
extern OS_TCB MULTI_MAIN_TaskTCB;
//�����ջ	
extern CPU_STK MULTI_MAIN_TASK_STK[MULTI_MAIN_STK_SIZE];
void multi_main_task(void *p_arg);

//�������ȼ�
#define MULTI_TASK_PRIO		15
//�����ջ��С	
#define MULTI_STK_SIZE 		128
//������ƿ�
extern OS_TCB Multi_TaskTCB;
//�����ջ	
extern CPU_STK MULTI_TASK_STK[MULTI_STK_SIZE];
void multi_task(void *p_arg);

//�������ȼ�
#define MEMORY_MAIN_TASK_PRIO		16
//�����ջ��С	
#define MEMORY_MAIN_STK_SIZE 		128
//������ƿ�
extern OS_TCB MEMORY_MAIN_TaskTCB;
//�����ջ	
extern CPU_STK MEMORY_MAIN_TASK_STK[MULTI_MAIN_STK_SIZE];
void memory_main_task(void *p_arg);

//�������ȼ�
#define MEMORY_TASK_PRIO		17
//�����ջ��С	
#define MEMORY_STK_SIZE 		128
//������ƿ�
extern OS_TCB MEMORY_TaskTCB;
//�����ջ	
extern CPU_STK MEMORY_TASK_STK[MULTI_STK_SIZE];
void memory_task(void *p_arg);

//�������ȼ�
#define CAN1_TASK_PRIO		18
//�����ջ��С	
#define CAN1_STK_SIZE 		128
//������ƿ�
extern OS_TCB CAN1_TaskTCB;
//�����ջ	
extern CPU_STK CAN1_TASK_STK[CAN1_STK_SIZE];
void can1_task(void *p_arg);
void can1_task_creat(void);

/* ==================== ������ ======================== */
#define IS_OPEN_LED0_TASK   1
#define IS_OPEN_LED1_TASK   0
#define IS_OPEN_FLOAT_TASK  0
#define IS_OPEN_tmr1_TASK   0
#define IS_OPEN_tmr2_TASK   0
#define IS_OPEN_sem_TASK    0
#define IS_OPEN_mutex_test_TASK 0
#define IS_OPEN_message_queue_TASK 0
#define IS_OPEN_flag_TASK 0
#define IS_OPEN_pendmulti_TASK 0
#define IS_OPEN_memory_TASK 0
#define IS_OPEN_can1_TASK    1
/* ======================================================= */

/*           ��ʼ������                         */
void BSP_Init(void);
#endif


