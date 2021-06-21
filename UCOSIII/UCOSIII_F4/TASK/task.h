#ifndef _task_h
#define _task_h
#include "includes.h"
#include "sys.h"

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
#define LED_TASK_PRIO		4
//�����ջ��С	
#define LED_STK_SIZE 		128
//������ƿ�
extern OS_TCB LedTaskTCB;
//�����ջ	
extern CPU_STK LED_TASK_STK[LED_STK_SIZE];
void led_task(void *p_arg);
void led_task_create(void);

#define IS_OPEN_LED_TASK 1

void BSP_Init(void);

#endif


