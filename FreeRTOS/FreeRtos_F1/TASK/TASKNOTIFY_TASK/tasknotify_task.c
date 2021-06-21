#include "tasknotify_task.h"
#include "string.h"
#include "semaphore.h"
#include "led.h"
#include "key.h"
#include "event_task.h"

/* ====================================== ����֪ͨ���API���� ========================================== */
/*  ������				       ����							����    							      ����ֵ                  ��ע        |
    --------------------------------------����֪ͨ--------------------------------------------------------|
		xTaskNotify()        ����֪ͨ   eAvtion(������·���) pdFAIL/pdPASS  ��ֵ֪ͨ ��������������ԭֵ֪ͨ  |
    xTaskNotifyGive()	   ����֪ͨ    ԭֵ֪ͨ+1                          pdPASS               ������      |
		xTaskNotifyAndQuery()����֪ͨ                                      pdFAIL/pdPASS        ����ԭֵ      |
		���Ϻ������ж�Ӧ���жϼ�����
		---------------------------------------��ȡ֪ͨ-------------------------------------------------------|
		ulTaskNotifyTake()   ��ȡ����֪ͨ   pdTRUE(����)/pdFALSE(��һ)     ����֮ǰ��ֵ֪ͨ                   |
		xTaskNotifyWait()    ��ȡ����֪ͨ        4                          pdFALSE/pdTRUE                    |
		ע��1.xTaskNotifyGive() ulTaskNotifyTake()������ģ���ֵ�ͼ������ź���                                |
		    2.xTaskNotify() xTaskNotifyWait()������ģ����Ϣ������¼���־��                                   |
		3.������֪ͨģ�����Щ���� Ч�ʸ���ԭ���� ������ֻ֪ͨ����һ���������� ����֪ͨ������Ϊ����ʧ�ܶ����� |
		4.configUSE_TASK_NOTIFICATIONS=1->��������֪ͨ
*/
/* ===================================================================================================== */	

TaskHandle_t TaskNotify_Binary_SemaPhore_Handler;   //ģ���ֵ�ź���

TaskHandle_t TaskNotify_SemapGiveTask_Handler;     //�������ź���
TaskHandle_t TaskNotify_SemapTakeTask_Handler;

TaskHandle_t Task1Task_Handler;   //��Ϣ����
TaskHandle_t Keyprocess_Handler;

TaskHandle_t TaskNotify_EventSetBit_Handler;  //�¼���־��
TaskHandle_t TaskNotify_EventGroupTask_Handler;

void TaskNotify_Binary_SemaPhore_task(void *pvParameters)
{
	u8 len=0;
	u32 NotifyValue;
	while(1)
	{
		NotifyValue=ulTaskNotifyTake(pdTRUE,portMAX_DELAY);	//��ȡ����֪ͨ ��ȡ��ֵ֪ͨ����
	  if(NotifyValue==1)									//����֮ǰ������ֵ֪ͨΪ1��˵������֪ͨ��Ч
		{
				len=USART_RX_STA&0x3fff;						//�õ��˴ν��յ������ݳ���
				USART_RX_BUF[len]='\0';							//�����ַ�����β����
				led_command=CommandProcess(USART_RX_BUF);		//�������
				if(led_command!=ERROR_COMMAND)
				{
					printf("����Ϊ:%s\r\n",USART_RX_BUF);
					switch(led_command)						//��������
					{
						case LED0_ON: 
							LED0=0;
							break;
						case LED0_OFF:
							LED0=1;
							break;
						case LED1_ON:
							LED1=0;
							break;
						case LED1_OFF:
							LED1=1;
							break;
					}
				}
				else
				{
					printf("��Ч���������������!!\r\n");
				}
				USART_RX_STA=0;
				memset(USART_RX_BUF,0,USART_REC_LEN);			//���ڽ��ջ���������
		}
	}
}

//�ͷż������ź���������
void TaskNotify_SemapGive_task(void *pvParameters)
{
	u8 key;
	while(1)
	{
		key=KEY_Scan(0);           	//ɨ�谴��
		if(TaskNotify_SemapTakeTask_Handler!=NULL)
		{
			if(key==KEY0_PRES)
			{  //����ΪҪ���͵�������  ֵ֪ͨ+1
				xTaskNotifyGive(TaskNotify_SemapTakeTask_Handler);//��������֪ͨ ֻ�ܷ���pdPASS ���еķ���֪ͨ�������۷���ʧ�ܻ��ǳɹ� ����������
				LED0=!LED0;
			}
	  }
	}
}

//��ȡ�������ź���������
void TaskNotify_SemapTake_task(void *pvParameters)
{
  u32 NotifyValue;
	while(1)
	{
		if(KEY_Scan(0)==KEY1_PRES)
		{
			NotifyValue=ulTaskNotifyTake(pdFALSE,portMAX_DELAY);//��ȡ����֪ͨ ��ȡ�� ��������ɺ�ֵ֪ͨ-1
			printf("SemapTake_task: count_semaphore_value=%d\r\n",NotifyValue-1);
		}
	}
}

//task1������
void task1_task(void *pvParameters)
{
	u8 key;
  BaseType_t err;
	while(1)
	{
		key=KEY_Scan(0);            			//ɨ�谴��
    if((Keyprocess_Handler!=NULL)&&(key))   
    {
			err=xTaskNotify((TaskHandle_t	)Keyprocess_Handler,		//��������֪ͨ��������
							(uint32_t		)key,						//����ֵ֪ͨ
							(eNotifyAction	)eSetValueWithoutOverwrite);	//��д�ķ�ʽ��������֪ͨ ģ����Ϣ����ʱ  ����ΪeSetValueWithoutOverwrite/eSetValueWithOverwrite
			if(err==pdFAIL)
			{
				printf("����֪ͨ����ʧ��\r\n");
			}
    }
    vTaskDelay(10);          
	}
}


//Keyprocess_task����
void Keyprocess_task(void *pvParameters)
{
	uint32_t NotifyValue;
	BaseType_t err;
	
	while(1)
	{
		err=xTaskNotifyWait((uint32_t	)0x00,				//���뺯����ʱ���������bit
							(uint32_t	)ULONG_MAX,			//�˳�������ʱ��������е�bit 0xffffffff
							(uint32_t*	)&NotifyValue,		//��������ֵ֪ͨ
							(TickType_t	)portMAX_DELAY);	//����ʱ��
		if(err==pdTRUE)				//��ȡ����֪ͨ�ɹ�
		{
			switch((u8)NotifyValue)
			{
				case KEY1_PRES:	
             LED1=!LED1;
					   break;
				case KEY0_PRES:		
             LED0=!LED0;
             break;
			}
		}
	}
}

//�����¼�λ������
void TaskNotify_eventsetbit_task(void *pvParameters)
{
	u8 key;

	while(1)
	{
		
		if(TaskNotify_EventGroupTask_Handler!=NULL)
		{
			key=KEY_Scan(0);
			switch(key)
			{
				case KEY0_PRES:
					xTaskNotify((TaskHandle_t	)TaskNotify_EventGroupTask_Handler,//��������֪ͨ��������
								(uint32_t		)EVENTBIT_0,			//Ҫ���µ�bit
								(eNotifyAction	)eSetBits);				//����ָ����bit
					break;
				case KEY1_PRES:
					xTaskNotify((TaskHandle_t	)TaskNotify_EventGroupTask_Handler,//��������֪ͨ��������
								(uint32_t		)EVENTBIT_1,			//Ҫ���µ�bit
								(eNotifyAction	)eSetBits);				//����ָ����bit
					break;	
			}
		}
        vTaskDelay(10); //��ʱ10ms��Ҳ����10��ʱ�ӽ���
	}
}

//�¼���־�鴦������
void TaskNotify_eventgroup_task(void *pvParameters)
{
	u8 enevtvalue;
	static u8 event0flag,event1flag;
	uint32_t NotifyValue;
	BaseType_t err;
	while(1)
	{
	//��ȡ����ֵ֪ͨ
		err=xTaskNotifyWait((uint32_t	)0x00,				//���뺯����ʱ���������bit
							(uint32_t	)ULONG_MAX,			//�˳�������ʱ��������е�bit
							(uint32_t*	)&NotifyValue,		//��������ֵ֪ͨ
							(TickType_t	)portMAX_DELAY);	//����ʱ��
		
		if(err==pdPASS)	   //����֪ͨ��ȡ�ɹ�
		{
			if((NotifyValue&EVENTBIT_0)!=0)			//�¼�0����	
			{
				event0flag=1;	
			}				
			else if((NotifyValue&EVENTBIT_1)!=0)	//�¼�1����	
			{
				event1flag=1;
			}
			enevtvalue=event0flag|(event1flag<<1);	//ģ���¼���־��ֵ
			printf("����ֵ֪ͨΪ:%d\r\n",enevtvalue);
			
			if((event0flag==1)&&(event1flag==1))	//�����¼���ͬʱ����
			{
				LED1=!LED1;	
				event0flag=0;								//��־����
				event1flag=0;
				enevtvalue=event0flag|(event1flag<<1);	//ģ���¼���־��ֵ
				printf("����ֵ֪ͨΪ:%d\r\n",enevtvalue);
			}
		}
		else
		{
			printf("����֪ͨ��ȡʧ��\r\n");
		}
	}
}

void TaskNotify_task_creat(void)
{
	#if TASKNOTIFY_BINARY_SEMAPHORE
	xTaskCreate((TaskFunction_t )TaskNotify_Binary_SemaPhore_task,     
                (const char*    )"TaskNotify_Binary_SemaPhore_task",   
                (uint16_t       )TASKNOTIFY_BINARY_SEMAPHORE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASKNOTIFY_BINARY_SEMAPHORE_TASK_PRIO,
                (TaskHandle_t*  )&TaskNotify_Binary_SemaPhore_Handler); 
	#endif
								
	#if TASKNOTIFY_COUNT_SEMAPHORE

		 //�����ͷ��ź�������
    xTaskCreate((TaskFunction_t )TaskNotify_SemapGive_task,             
                (const char*    )"tasknotify_semapgive_task",           
                (uint16_t       )TASKNOTIFY_SEMAPGIVE_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASKNOTIFY_SEMAPGIVE_TASK_PRIO,        
                (TaskHandle_t*  )&TaskNotify_SemapGiveTask_Handler);   
    //������ȡ�ź�������
    xTaskCreate((TaskFunction_t )TaskNotify_SemapTake_task,     
                (const char*    )"semaptake_task",   
                (uint16_t       )TASKNOTIFY_SEMAPTAKE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASKNOTIFY_SEMAPTAKE_TASK_PRIO,
                (TaskHandle_t*  )&TaskNotify_SemapTakeTask_Handler); 
		#endif
		
		#if TASKNOTIFY_FIFO
		 //����TASK1����
    xTaskCreate((TaskFunction_t )task1_task,             
                (const char*    )"task1_task",           
                (uint16_t       )TASK1_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASK1_TASK_PRIO,        
                (TaskHandle_t*  )&Task1Task_Handler);   
    //����������������
    xTaskCreate((TaskFunction_t )Keyprocess_task,     
                (const char*    )"keyprocess_task",   
                (uint16_t       )KEYPROCESS_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )KEYPROCESS_TASK_PRIO,
                (TaskHandle_t*  )&Keyprocess_Handler); 
		#endif
								
		#if TASKNOTIFY_EVENT
		//���������¼�λ������
    xTaskCreate((TaskFunction_t )TaskNotify_eventsetbit_task,             
                (const char*    )"TaskNotify_eventsetbit_task",           
                (uint16_t       )TASKNOTIFY_EVENTSETBIT_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASKNOTIFY_EVENTSETBIT_TASK_PRIO,        
                (TaskHandle_t*  )&TaskNotify_EventSetBit_Handler);   	
    //�����¼���־�鴦������
    xTaskCreate((TaskFunction_t )TaskNotify_eventgroup_task,             
                (const char*    )"TaskNotify_eventgroup_task",           
                (uint16_t       )TASKNOTIFY_EVENTGROUP_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASKNOTIFY_EVENTGROUP_TASK_PRIO,        
                (TaskHandle_t*  )&TaskNotify_EventGroupTask_Handler);    
		#endif
}


