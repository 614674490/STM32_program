#include "queue_task.h"
#include "led.h"
#include "key.h"
#include "stdlib.h"

/* ====================================== �������API���� ============================================== */
/*  ������				       ����							����    							      ����ֵ                  ��ע        |
		xQueueSend()         �������         ����ʱ��(portMAX_DELAY)     pdPASS/errQueueFull    ���� ����  |
    xQueueSendToBack()	                     ͬ��                                                         |
		xQueueSendToFront()  ǰ�����            ͬ��                                                         |
		xQueueOverwrite()    �������           NULL                       ����д���� ������һ���ֵĴ���      |
		------------------------------------------------------------------------------------------------------|
		xQueueSendFromISR()         �������   xHigherPriorityTaskWoken    pdTURE/errQueueFull  �жϼ� ����   |
    xQueueSendToBackFromISR()	                      ͬ��     ���������Ƿ���������л�                     |
		xQueueSendToFrontFromISR()  ǰ�����            ͬ��                                                  |
		xQueueOverwriteFromISR()    �������            ͬ��               ����д���� ������һ���ֵĴ���      |
		------------------------------------------------------------------------------------------------------|
		xQueueReceive()   ��ȡ��ɾ����Ϣ      ����ʱ��                     pdTURE/pdFALSE      ���� ����    |
		xQueuePeek()      ��ȡ��ɾ����Ϣ                ͬ��                                                |
		------------------------------------------------------------------------------------------------------|
		xQueueReceiveFromISR()   ��ȡ��ɾ����Ϣ     ͬ��                      pdTURE/pdFALSE �жϼ� ����      |
		xQueuePeekFromISR()      ��ȡ��ɾ����Ϣ  xHigherPriorityTaskWoken   ���������Ƿ���������л�        |
    -------------------------------------  ��ע   --------------------------------------------------------|
		��ӷ�ʽ�� 1.ǰ�����  2.�������  3.��д���
		ISR:��Ҫͨ��xHigherPriorityTaskWoken������һ������ �ò������ݵ�ǰ������Ϣ�����ȼ���С 
		                                                   �����Ƿ���������л�
	  
*/
/* ===================================================================================================== */	
		        
		
	
QueueHandle_t Message_Queue;
TaskHandle_t QueueTask_Handler;

//��ѯMessage_Queue�����е��ܶ���������ʣ���������
void check_msg_queue(QueueHandle_t Message_Queue)
{
	  u8 msgq_remain_size;	//��Ϣ����ʣ���С
    u8 msgq_total_size;     //��Ϣ�����ܴ�С
    
    taskENTER_CRITICAL();   //�����ٽ���
    msgq_remain_size=uxQueueSpacesAvailable(Message_Queue);//�õ�����ʣ���С
    msgq_total_size=uxQueueMessagesWaiting(Message_Queue)+msgq_remain_size;//�õ������ܴ�С���ܴ�С=ʹ��+ʣ��ġ�
	  printf("Total Size:%d    Remain Size:%d\r\n",msgq_total_size,msgq_remain_size);
    taskEXIT_CRITICAL();    //�˳��ٽ���
}

void queue_task_creat(void)
{
	
	Message_Queue=xQueueCreate(MESSAGE_Q_NUM,USART_REC_LEN); //������ϢMessage_Queue,��������Ǵ��ڽ��ջ���������
	xTaskCreate((TaskFunction_t )queue_task,             
                (const char*    )"queue_task",           
                (uint16_t       )QUEUE_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )QUEUE_TASK_PRIO,        
                (TaskHandle_t*  )&QueueTask_Handler);  
}

void queue_task(void *pvParameters)
{
	char *rx_buffer;
	rx_buffer=(char *)malloc(sizeof(char)*USART_REC_LEN);
	while(1)
	{
		if(KEY_Scan(0)==KEY0_PRES)
		{
			if(xQueueReceive(Message_Queue,rx_buffer,portMAX_DELAY)==pdTRUE)   //������ϢMessage_Queue һֱ�ȴ� ���յ���Ϣ����������Ϣ�б���ɾ��
			{
				printf("queue_task receive message: %s\r\n",rx_buffer);
				free(rx_buffer);  //�ͷ��ڴ�
				rx_buffer=(char *)malloc(sizeof(char)*USART_REC_LEN);
				LED0=!LED0;
				check_msg_queue(Message_Queue);
			}
	  }
	}
}


