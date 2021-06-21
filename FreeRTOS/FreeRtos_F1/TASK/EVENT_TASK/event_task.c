#include "event_task.h"
#include "led.h"
#include "key.h"

/* ====================================== �¼���־�����API���� ======================================== */
/*
		xEventGroupCreate()                    �����¼���־��                                                 |
    xEventGroupCreateStatic()              ��̬����                                                       |       
 	  xEventGroupSetBits()	                 �趨��־λΪ1                                                  |
    xEventGroupSetBitsFromISR()            �趨��־λΪ1(�жϼ�)	                                      	|
		xEventGroupClearBits()	               �趨��־λΪ0                                                  |
    xEventGroupClearBitsFromISR()          �趨��־λΪ0(�жϼ�)	                                      	|
		xEventGroupWaitBits()                  �ȴ�ָ�����¼���־λ                                           |
*/
/* ===================================================================================================== */

EventGroupHandle_t EventGroupHandler;
TaskHandle_t EventSetBit_Handler;
TaskHandle_t EventGroupTask_Handler;

//�����¼�λ������
void eventsetbit_task(void *pvParameters)
{
	u8 key;
	EventBits_t NewValue;
	while(1)
	{
		if(EventGroupHandler!=NULL)
		{
			key=KEY_Scan(0);
			switch(key)
			{
				case KEY0_PRES:
					xEventGroupSetBits(EventGroupHandler,EVENTBIT_0);
				  NewValue=xEventGroupGetBits(EventGroupHandler);	//��ȡ�¼����ֵ
				  printf("set eventbit eventvalue:%d\r\n",NewValue);
					break;
				case KEY1_PRES:
					xEventGroupSetBits(EventGroupHandler,EVENTBIT_1);
				  NewValue=xEventGroupGetBits(EventGroupHandler);	//��ȡ�¼����ֵ
				  printf("event deal eventvalue:%d\r\n",NewValue);
					break;	
			}
		}
        vTaskDelay(10); //��ʱ10ms��Ҳ����10��ʱ�ӽ���
	}
}

//�¼���־�鴦������
void eventgroup_task(void *pvParameters)
{
	EventBits_t EventValue;
	while(1)
	{

		if(EventGroupHandler!=NULL)
		{
			//�ȴ��¼����е���Ӧ�¼�λ
			EventValue=xEventGroupWaitBits((EventGroupHandle_t	)EventGroupHandler,	  //�¼���־����	
										   (EventBits_t			)EVENTBIT_ALL,                        //�¼���־λ
										   (BaseType_t			)pdTRUE,				                      //ʱ��λ�Ƿ����� pdTRUE->����
										   (BaseType_t			)pdTRUE,                              //�ȴ�ȫ����־λ���������־λ��1 pdTRUE->ȫ��
								       (TickType_t			)portMAX_DELAY);	                    //����ʱ�� ΪportMAX_DELA���������
			printf("event deal eventvalue:%d\r\n",EventValue);
			LED1=!LED1;	
		
		}
	}
}

void event_task_creat(void)
{
	 //�����¼���־��
	EventGroupHandler=xEventGroupCreate();	 //�����¼���־��
	
	//���������¼�λ������
    xTaskCreate((TaskFunction_t )eventsetbit_task,             
                (const char*    )"eventsetbit_task",           
                (uint16_t       )EVENTSETBIT_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )EVENTSETBIT_TASK_PRIO,        
                (TaskHandle_t*  )&EventSetBit_Handler);   	
    //�����¼���־�鴦������
    xTaskCreate((TaskFunction_t )eventgroup_task,             
                (const char*    )"eventgroup_task",           
                (uint16_t       )EVENTGROUP_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )EVENTGROUP_TASK_PRIO,        
                (TaskHandle_t*  )&EventGroupTask_Handler);  
}
