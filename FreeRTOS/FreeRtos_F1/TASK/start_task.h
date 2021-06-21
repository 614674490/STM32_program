#ifndef _start_task_h
#define _start_task_h
#include "FreeRTOS.h"
#include "task.h"


//0��������ȼ� ���ڿ������������ ����ԽС ���ȼ�Խ��

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
extern TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);
void start_task_creat(void);
	
//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		128
//������
extern TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);
void led0_task_creat(void);

//�������ȼ�
#define LIST_TASK_PRIO		3
//�����ջ��С	
#define LIST_STK_SIZE 		128  
//������
extern TaskHandle_t ListTask_Handler;
//������
void list_task(void *pvParameters);
void list_task_creat(void);


//�������ȼ�
#define API_TASK_PRIO		3
//�����ջ��С	
#define API_STK_SIZE 		256  
//������
extern TaskHandle_t ApiTask_Handler;
//������
void api_task(void *pvParameters);
void api_task_creat(void);


//�������ȼ�
#define QUEUE_TASK_PRIO		4
//�����ջ��С	
#define QUEUE_STK_SIZE 		256  
//������
extern TaskHandle_t QueueTask_Handler;
//������
void queue_task(void *pvParameters);
void queue_task_creat(void);

//�������ȼ�
#define BINARY_SEMAPHORE_TASK_PRIO 5
//�����ջ��С	
#define BINARY_SEMAPHORE_STK_SIZE  256 
//������
extern TaskHandle_t Binary_SemaPhore_Handler;
//������
void Binary_SemaPhore_task(void *pvParameters);
void SemaPhore_task_creat(void);

//�������ȼ�
#define SEMAPGIVE_TASK_PRIO		6
//�����ջ��С	
#define SEMAPGIVE_STK_SIZE 		256  
//������
extern TaskHandle_t SemapGiveTask_Handler;
//������
void SemapGive_task(void *pvParameters);

//�������ȼ�
#define SEMAPTAKE_TASK_PRIO 	7
//�����ջ��С	
#define SEMAPTAKE_STK_SIZE  	256 
//������
extern TaskHandle_t SemapTakeTask_Handler;
//������
void SemapTake_task(void *pvParameters);

//�������ȼ�
#define RECURSIVE_SEMAPHORE_TASK_PRIO 8
//�����ջ��С	
#define RECURSIVE_SEMAPHORE_STK_SIZE  256 
//������
extern TaskHandle_t Recursive_SemaPhore_Handler;
//������
void Recursive_SemaPhore_task(void *pvParameters);

//�������ȼ�
#define TIMERCONTROL_TASK_PRIO	9
//�����ջ��С	
#define TIMERCONTROL_STK_SIZE 	256  
//������
extern TaskHandle_t TimerControlTask_Handler;
//������
void timercontrol_task(void *pvParameters);
void timercontrol_task_creat(void);


//�������ȼ�
#define EVENTSETBIT_TASK_PRIO	10
//�����ջ��С	
#define EVENTSETBIT_STK_SIZE 	256  
//������
extern TaskHandle_t EventSetBit_Handler;
//������
void eventsetbit_task(void *pvParameters);

//�������ȼ�
#define EVENTGROUP_TASK_PRIO	11
//�����ջ��С	
#define EVENTGROUP_STK_SIZE 	256  
//������
extern TaskHandle_t EventGroupTask_Handler;
//������
void eventgroup_task(void *pvParameters);
void event_task_creat(void);

//�������ȼ�
#define HEAP_TASK_PRIO	12
//�����ջ��С	
#define HEAP_STK_SIZE 	128
//������
extern TaskHandle_t HeapTask_Handler;
//������
void heap_task(void *p_arg);
void heap_task_creat(void);

//�������ȼ�
#define TASKNOTIFY_BINARY_SEMAPHORE_TASK_PRIO 13
//�����ջ��С	
#define TASKNOTIFY_BINARY_SEMAPHORE_STK_SIZE  256 
//������
extern TaskHandle_t TaskNotify_Binary_SemaPhore_Handler;
//������
void TaskNotify_Binary_SemaPhore_task(void *pvParameters);

//�������ȼ�
#define TASKNOTIFY_SEMAPGIVE_TASK_PRIO		14
//�����ջ��С	
#define TASKNOTIFY_SEMAPGIVE_STK_SIZE 		256  
//������
extern TaskHandle_t TaskNotify_SemapGiveTask_Handler;
//������
void TaskNotify_SemapGive_task(void *pvParameters);

//�������ȼ�
#define TASKNOTIFY_SEMAPTAKE_TASK_PRIO 	15
//�����ջ��С	
#define TASKNOTIFY_SEMAPTAKE_STK_SIZE  	256 
//������
extern TaskHandle_t TaskNotify_SemapTakeTask_Handler;
//������
void TaskNotify_SemapTake_task(void *pvParameters);

//�������ȼ�
#define TASK1_TASK_PRIO		16
//�����ջ��С	
#define TASK1_STK_SIZE 		256  
//������
extern TaskHandle_t Task1Task_Handler;
//������
void task1_task(void *pvParameters);

//�������ȼ�
#define KEYPROCESS_TASK_PRIO 17
//�����ջ��С	
#define KEYPROCESS_STK_SIZE  256 
//������
extern TaskHandle_t Keyprocess_Handler;
//������
void Keyprocess_task(void *pvParameters);

//�������ȼ�
#define TASKNOTIFY_EVENTSETBIT_TASK_PRIO	18
//�����ջ��С	
#define TASKNOTIFY_EVENTSETBIT_STK_SIZE 	256  
//������
extern TaskHandle_t TaskNotify_EventSetBit_Handler;
//������
void TaskNotify_eventsetbit_task(void *pvParameters);

//�������ȼ�
#define TASKNOTIFY_EVENTGROUP_TASK_PRIO	19
//�����ջ��С	
#define TASKNOTIFY_EVENTGROUP_STK_SIZE 	256  
//������
extern TaskHandle_t TaskNotify_EventGroupTask_Handler;
//������
void TaskNotify_eventgroup_task(void *pvParameters);

void TaskNotify_task_creat(void);

#define IS_OPEN_LED0_TASK       0
#define IS_OPEN_list_TASK       0
#define IS_OPEN_api_TASK        0
#define IS_OPEN_queue_TASK      0
#define IS_OPEN_semaphore_TASK  0
#define IS_OPEN_timers_TASK     0
#define IS_OPEN_event_TASK      0
#define IS_OPEN_heap_TASK       0
#define IS_OPEN_tasknotify_TASK 0
void FreeRTOS_Init(void);
#endif





