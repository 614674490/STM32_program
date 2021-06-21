#include "api.h"
#include "key.h"
#include "delay.h"
#include "string.h"
#include "timer.h"

/* ==================== ͳ����������ʱ���Լ���ռ�ٷֱ� =================== */
/*
	1.���ڼ����ʱ�Ӿ���Ҫ����ϵͳʱ��10-20��(HZ)->ʱ��
	2.ʵ������ʱ��=���д���(FreeRTOSRunTimeTicks)*50us(TIM����)
	3.�궨�� FreeRTOS������ʱ�������״̬�ռ��йص�����ѡ��(3�����غ궨�� 1��ȫ�ֱ��� 1������)
	4.�ڵ���ʱʹ�� ƽ��ʹ�÷ǳ���ʱ
*/
/* ======================================================================= */

//                           ����
/*
	��������״̬��B������̬  R������̬/����̬  S������̬  D��ɾ��̬
*/
char InfoBuffer[1000];	
TaskHandle_t ApiTask_Handler;

void api_task(void *pvParameters)
{
	#if DEBUG
	u32 TotalRunTime;
	UBaseType_t ArraySize,x;
	TaskStatus_t *StatusArray;
	
	//�ڶ���������vTaskGetInfo()��ʹ��
	TaskHandle_t TaskHandle;  //ָ��	 
	TaskStatus_t TaskStatus; //�ṹ��
	
	//������������eTaskGetState()��ʹ��	
	eTaskState TaskState;
	char TaskInfo[10];
	
	//���岽������vTaskGetRunTimeStats()��ʹ��
	char RunTimeInfo[400];		//������������ʱ����Ϣ
	
	//��һ��������uxTaskGetSystemState()��ʹ��
	printf("/********��һ��������uxTaskGetSystemState()��ʹ��**********/\r\n");
	ArraySize=uxTaskGetNumberOfTasks();		//��ȡϵͳ��������
	StatusArray=pvPortMalloc(ArraySize*sizeof(TaskStatus_t));//�����ڴ�
	if(StatusArray!=NULL)					//�ڴ�����ɹ�
	{
		ArraySize=uxTaskGetSystemState((TaskStatus_t* 	)StatusArray, 	//������Ϣ�洢����
									   (UBaseType_t		)ArraySize, 	//������Ϣ�洢�����С
								       (uint32_t*		)&TotalRunTime);//����ϵͳ�ܵ�����ʱ��
		printf("TaskName\t\tPriority\t\tTaskNumber\t\t\r\n");
		for(x=0;x<ArraySize;x++)
		{
			//ͨ�����ڴ�ӡ����ȡ����ϵͳ������й���Ϣ�������������ơ�
			//�������ȼ��������š�
			printf("%s\t\t%d\t\t\t%d\t\t\t\r\n",				
					StatusArray[x].pcTaskName,
					(int)StatusArray[x].uxCurrentPriority,
					(int)StatusArray[x].xTaskNumber);
			
		}
	}
	vPortFree(StatusArray);	//�ͷ��ڴ�
	printf("/**************************����***************************/\r\n");
	printf("����KEY0������!\r\n\r\n\r\n");
	while(KEY_Scan(0)!=KEY0_PRES) delay_ms(10);		//�ȴ�KEY_UP������
	

	
	printf("/************�ڶ���������vTaskGetInfo()��ʹ��**************/\r\n");
	TaskHandle=xTaskGetHandle("api_task");			//������������ȡ��������
	//��ȡLED0_Task��������Ϣ
	vTaskGetInfo((TaskHandle_t	)TaskHandle, 		//������
				 (TaskStatus_t*	)&TaskStatus, 		//������Ϣ�ṹ��
				 (BaseType_t	)pdTRUE,			//����ͳ�������ջ��ʷ��Сʣ���С
			     (eTaskState	)eInvalid);			//�����Լ���ȡ��������׳̬
	//ͨ�����ڴ�ӡ��ָ��������й���Ϣ��
	printf("������:                %s\r\n",TaskStatus.pcTaskName);
	printf("������:              %d\r\n",(int)TaskStatus.xTaskNumber);
	printf("����״̬:              %d\r\n",TaskStatus.eCurrentState);
	printf("����ǰ���ȼ�:        %d\r\n",(int)TaskStatus.uxCurrentPriority);
	printf("��������ȼ�:          %d\r\n",(int)TaskStatus.uxBasePriority);
	printf("�����ջ����ַ:        %#x\r\n",(int)TaskStatus.pxStackBase);
	printf("�����ջ��ʷʣ����Сֵ:%d\r\n",TaskStatus.usStackHighWaterMark);
	printf("/**************************����***************************/\r\n");
	printf("����KEY0������!\r\n\r\n\r\n");
	while(KEY_Scan(0)!=KEY0_PRES) delay_ms(10);		//�ȴ�KEY_UP������
	
	
	printf("/***********������������eTaskGetState()��ʹ��*************/\r\n");
	TaskHandle=xTaskGetHandle("api_task");		//������������ȡ��������
	TaskState=eTaskGetState(TaskHandle);			//��ȡquery_task���������׳̬
	memset(TaskInfo,0,10);						//����ڴ�
	switch((int)TaskState)
	{
		case 0:
			sprintf(TaskInfo,"Running");
			break;
		case 1:
			sprintf(TaskInfo,"Ready");
			break;
		case 2:
			sprintf(TaskInfo,"Suspend");
			break;
		case 3:
			sprintf(TaskInfo,"Delete");
			break;
		case 4:
			sprintf(TaskInfo,"Invalid");
			break;
	}
	printf("����״ֵ̬:%d,��Ӧ��״̬Ϊ:%s\r\n",TaskState,TaskInfo);
	printf("/**************************����**************************/\r\n");
	printf("����KEY0������!\r\n\r\n\r\n");
	while(KEY_Scan(0)!=KEY0_PRES) delay_ms(10);		//�ȴ�KEY_UP������
	
	//���Ĳ�������vTaskList()��ʹ��	
	printf("/*************���Ĳ�������vTaskList()��ʹ��*************/\r\n");
	vTaskList(InfoBuffer);							//��ȡ�����������Ϣ
	printf("%s\r\n",InfoBuffer);					//ͨ�����ڴ�ӡ�����������Ϣ
	printf("/**************************����**************************/\r\n");
	while(KEY_Scan(0)!=KEY0_PRES) delay_ms(10);		//�ȴ�KEY_UP������
	
	printf("/*************���岽������vTaskGetRunTimeStats()��ʹ��*************/\r\n");
	memset(RunTimeInfo,0,400);				//��Ϣ����������
	vTaskGetRunTimeStats(RunTimeInfo);		//��ȡ��������ʱ����Ϣ
	printf("������\t\t����ʱ��\t������ռ�ٷֱ�\r\n");
	printf("%s\r\n",RunTimeInfo);   //ʵ������ʱ��=����*50us
	printf("/**************************����**************************/\r\n");
	#endif
}

void api_task_creat(void)
{
	 xTaskCreate((TaskFunction_t )api_task,     
                (const char*    )"api_task",   
                (uint16_t       )API_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )API_TASK_PRIO,
                (TaskHandle_t*  )&ApiTask_Handler); 
}


