#include "semaphore.h"
#include "led.h"
#include "usart.h"
#include "string.h"
#include "key.h"
#include "delay.h"
/* ====================================== �ź������API���� ============================================== */
/*  ������				       ����							����    							      ����ֵ                  ��ע        |
    --------------------------------------��ֵ�ź���------------------------------------------------------|
		xSemaphoreCreateBinary()          ��̬������ֵ�ź���(Ĭ����Ч)   �����ɹ��Ķ�ֵ�ź������             |
    xSemaphoreCreateBinaryStatic()	  ��̬������ֵ�ź���                                                  |
		xSemaphoreGive()                  �ͷ��ź���          pdPASS/errQueueFull ���ݹ黥���ź�����  ����  |
		xSemaphoreGiveFromISR()           ���ͷŶ�ֵ�ͼ������ź���      ͬ��           �����л�  �жϼ�       |
		xSemaphoreTake()          ��ȡ��ֵ ���� �����ź���  ����ʱ��    pdTURE/pdFALSE      ����            |
    xSemaphoreCreateBinaryFromISR()	 ��ȡ��ֵ ���� �ź���           pdPASS/pdFALSE  �жϼ� �����л�       |
		---------------------------------------�����ź���-----------------------------------------------------|
		xSemaphoreCreateCounting()        �����������ź���(��ʼֵ)     �����ɹ��ļ������ź������             |
		xSemaphoreCreateCountingStatic()              ͬ��                                                    |
		ע�������¼�����(��ʼֵ=0)����Դ����(��ʼֵ>0)                                                        |
		---------------------------------------�����ź���-----------------------------------------------------|
		xSemaphoreCreateMutex()        ���������ź���(Ĭ����Ч)  �����ɹ��Ļ����ź������                     |
		xSemaphoreCreateMutexStatic()   ��̬����                                                              |
		ע����ֹ���ȼ���ת������                                                                              |
				��������ISR��                                                                                     |
        SemaphoreHandle_t MutexSemaphore;	//�����ź���                                                    |
        MutexSemaphore=xSemaphoreCreateMutex();			                                                     	|
				����(�ݹ�)�����ź��� ��һ�������л�ȡ��Ҫ�ͷŸ��ź��� ��������֮��һ��Ҫ�ͷ�                    |			                                                     	|
    ---------------------------------------�ݹ黥���ź���-------------------------------------------------|
		xSemaphoreCreateRecursiveMutex() ��̬�����ݹ黥���ź���(Ĭ����Ч)                                     |
		xSemaphoreCreateRecursiveMutexStatic() ��̬����                                                       |
		xSemaphoreTakeRecursive()              ��ȡ�ݹ黥���ź���                                             |
		xSemaphoreGiveRecursive()              �ͷŵݹ黥���ź���                                             |
		ע��1.(�ݹ�)�����ź�����������ISR��                                                                   |
		    2.(�ݹ�)�����ź���һ��Ҫ��ͬһ�������л�ȡ���ͷ�(�Ȼ�ȡ���ͷ�)                                    |
				3.�ݹ黥���ź�����ȡ�������� ֻ����ͬһ���������ͷ�ͬ���Ĵ��� �ſɱ����������ȡ                  |
				  ��Ȼÿ���ͷŶ���ɹ� ��ֻ�������һ���ͷ� ���������ĵ����ź����ͷź��� ��������¶���           |
					��ȡ��������һ                                                                                  |
*/
/* ===================================================================================================== */	
LED_COMMAND led_command=ERROR_COMMAND;
SemaphoreHandle_t Binary_Semaphore;	    //��ֵ�ź������
TaskHandle_t Binary_SemaPhore_Handler;  //������

SemaphoreHandle_t Count_Semaphore;  //�������ź������
TaskHandle_t SemapGiveTask_Handler;
TaskHandle_t SemapTakeTask_Handler;

SemaphoreHandle_t Recursive_Semaphore;  //�ݹ黥���ź���
TaskHandle_t Recursive_SemaPhore_Handler;
 
//������������ַ�������ת��������ֵ
//str������
//����ֵ: 0XFF�������������ֵ������ֵ
LED_COMMAND CommandProcess(u8 *str)
{
	LED_COMMAND led_command=ERROR_COMMAND;
	if(strcmp((char*)str,"LED0 ON")==0) led_command=LED0_ON;
	else if(strcmp((char*)str,"LED0 OFF")==0) led_command=LED0_OFF;
	else if(strcmp((char*)str,"LED1 ON")==0) led_command=LED1_ON;
	else if(strcmp((char*)str,"LED1 OFF")==0) led_command=LED1_OFF;
	else led_command=ERROR_COMMAND;
	return led_command;
}

void Binary_SemaPhore_task(void *pvParameters)
{
	u8 len=0;
	BaseType_t err=pdFALSE;   //�洢��ȡ�ź���ʱ�ķ���ֵ
	while(1)
	{
		if(Binary_Semaphore!=NULL)
		{
			err=xSemaphoreTake(Binary_Semaphore,portMAX_DELAY);	//��ȡ�ź���
			if(err==pdTRUE)										//��ȡ�ź����ɹ�
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
}

//�ͷż������ź���������
void SemapGive_task(void *pvParameters)
{
	u8 key;
    u8 semavalue;
	BaseType_t err;
	while(1)
	{
		key=KEY_Scan(0);           	//ɨ�谴��
		if(Count_Semaphore!=NULL)  	//�������ź��������ɹ�
		{
		  if(key==KEY0_PRES)
			{
				err=xSemaphoreGive(Count_Semaphore);//�ͷż������ź���
				if(err==pdFALSE)
				{
					printf("�ź����ͷ�ʧ��!!!\r\n");
				}
				semavalue=uxSemaphoreGetCount(Count_Semaphore);	//��ȡ�������ź���ֵ
				printf("SemapGive_task: count_semaphore_value=%d\r\n",semavalue);
			}
		}
	}
}

//��ȡ�������ź���������
void SemapTake_task(void *pvParameters)
{
  u8 num;
  u8 semavalue;
	while(1)
	{
		if(KEY_Scan(0)==KEY1_PRES)
		{
			xSemaphoreTake(Count_Semaphore,portMAX_DELAY); 	//�ȴ���ֵ�ź���
			num++;
			semavalue=uxSemaphoreGetCount(Count_Semaphore); 	//��ȡ��ֵ�ź���ֵ
			printf("SemapTake_task: count_semaphore_value=%d\r\n",semavalue);
		}
	}
}

void Recursive_SemaPhore_task(void *pvParameters)
{
	BaseType_t err;
	u8 take_nums=0;
	while(1)
	{
		if(KEY_Scan(0)==KEY0_PRES)
		{
			err=xSemaphoreTakeRecursive(Recursive_Semaphore,portMAX_DELAY);
			if(err==pdPASS)
			{
				take_nums++;
				printf("take_nums :  %d\r\n",take_nums);
			}
			else
			{
				printf("Take Failed\r\n");
			}
		}
		else if(KEY_Scan(0)==KEY1_PRES)
		{
			err=xSemaphoreGiveRecursive(Recursive_Semaphore);
			if(err==pdPASS)
			{
				take_nums--;
				printf("take_nums :  %d\r\n",take_nums);  //ֻ�����һ���ͷŲ����������ͷųɹ� ��������ſɻ�ȡ���ź���
			}
			else
			{
				printf("This Task not Take Recursive_Semaphore\r\n");
			}
		}
	}
}
void SemaPhore_task_creat(void)
{
    #if IS_OPEN_binary_semaphore_TASK
	  //������ֵ�ź���
	  Binary_Semaphore=xSemaphoreCreateBinary();	
    xTaskCreate((TaskFunction_t )Binary_SemaPhore_task,     
                (const char*    )"Binary_SemaPhore_task",   
                (uint16_t       )BINARY_SEMAPHORE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )BINARY_SEMAPHORE_TASK_PRIO,
                (TaskHandle_t*  )&Binary_SemaPhore_Handler); 
		#endif
		#if IS_OPEN_count_semaphore_TASK
		//�����������ź���
	  Count_Semaphore=xSemaphoreCreateCounting(255,0);	//������ֵ ��ʼֵ
		 //�����ͷ��ź�������
    xTaskCreate((TaskFunction_t )SemapGive_task,             
                (const char*    )"semapgive_task",           
                (uint16_t       )SEMAPGIVE_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )SEMAPGIVE_TASK_PRIO,        
                (TaskHandle_t*  )&SemapGiveTask_Handler);   
    //������ȡ�ź�������
    xTaskCreate((TaskFunction_t )SemapTake_task,     
                (const char*    )"semaptake_task",   
                (uint16_t       )SEMAPTAKE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )SEMAPTAKE_TASK_PRIO,
                (TaskHandle_t*  )&SemapTakeTask_Handler); 
		#endif
		
		#if IS_OPEN_recursive_semaphore_TASK
		Recursive_Semaphore=xSemaphoreCreateRecursiveMutex();
		xTaskCreate((TaskFunction_t )Recursive_SemaPhore_task,     
                (const char*    )"Recursive_SemaPhore_task",   
                (uint16_t       )RECURSIVE_SEMAPHORE_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )RECURSIVE_SEMAPHORE_TASK_PRIO,
                (TaskHandle_t*  )&Recursive_SemaPhore_Handler);
		#endif
}

