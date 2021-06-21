#include "start_task.h"
#include "led_task.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "list_task.h"
#include "key.h"
#include "api.h"
#include "queue_task.h"
#include "semaphore.h"
#include "timer_task.h"
#include "event_task.h"
#include "heap_task.h"
#include "tasknotify_task.h"
/* ====================== ���������ص�API���� =================== */
/*
	vTaskSuspend()         �������                                    |
	vTaskResume()          ����ָ�                                    |
	vTaskResumeFromISR()   ���ж����������ָ�                        |
	˵������vTaskResumeFromISR()�� ������ֵΪpdTRUE                    |
	����ҪportYIELD_FROM_ISR(pdTRUE)�����������л� pdFALSE����Ҫ       |
*/
/* ================================================================ */
TaskHandle_t StartTask_Handler;
//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���->����   taskENTER_CRITICAL_From_ISR->�жϼ�
	
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���      taskEXIT_CRITICAL_From_ISR->�жϼ�
}

void start_task_creat()
{
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������  
		#if IS_OPEN_LED0_TASK
	  led0_task_creat();
	  #endif
								
    #if IS_OPEN_list_TASK
		list_task_creat();
		#endif
								
		#if IS_OPEN_api_TASK
		api_task_creat();
		#endif
								
		#if IS_OPEN_queue_TASK
		queue_task_creat();
		#endif
								
		#if IS_OPEN_semaphore_TASK
		SemaPhore_task_creat();
		#endif
		
		#if IS_OPEN_timers_TASK
		timercontrol_task_creat();
		#endif
		
		#if IS_OPEN_event_TASK
		event_task_creat();
		#endif
		
		#if IS_OPEN_heap_TASK
		heap_task_creat();
		#endif
		
		#if IS_OPEN_tasknotify_TASK
		TaskNotify_task_creat();
		#endif
}

void FreeRTOS_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4->16����ռ���ȼ� FreeRTOS�޷����������ȼ� ��ռ��4û�������ȼ�	 
	delay_init();	    				//��ʱ������ʼ��	  
	uart_init(115200);					//��ʼ������
	LED_Init();		  
	KEY_Init();
}
