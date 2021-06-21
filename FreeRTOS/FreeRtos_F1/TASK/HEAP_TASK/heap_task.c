#include "heap_task.h"
#include "key.h"

/* ====================== �ڴ������ص�API���� =================== */
/*
	pvPortMalloc()         �����ڴ�                                    |
	vPortFree()            �ͷ��ڴ�                                    |
	heap_1.c:          ֻ������ �����ͷ�                               |
	heap_2.c:          ������ ���ͷ� ���ײ�����Ƭ                      |
	heap_3.c:          ��malloc()��free()�����˷�װ �ṩ���̱߳���     |
	heap_4.c:          �ṩ�ڴ�ϲ��㷨 ��С���ڴ���Ƭ�������         |
	heap_5.c:          ������4��ͬ ���������ڴ�ѿ�Խ������������ڴ���|
	                   ����ȿ���ʹ���ڲ�RAMҲ��ʹ���ⲿRAM,           |
										 ����ֻ��ʹ������֮һ                            |
	���Ϻ�����Ч�ʾ�����malloc()��free()                               |
*/
/* ================================================================ */

TaskHandle_t HeapTask_Handler;


void heap_task(void *p_arg)
{
	u8 *buffer;		
	u8 times,key=0;
	printf("remain heap size : %d\r\n",xPortGetFreeHeapSize());  //��ȡʣ���ڴ��С
  while(1)
  {
		key=KEY_Scan(0);
		switch(key)
		{
			case KEY0_PRES:				
				buffer=pvPortMalloc(30);			//�����ڴ棬30���ֽ� ���������һ���ṹ���С��8�ֽڶ����С һ����10�ֽڴ�С
				printf("���뵽���ڴ��ַΪ:%#x\r\n",(int)buffer);
			  if(buffer!=NULL)					//buffer����,ʹ��buffer
				{
					times++;
					sprintf((char*)buffer,"User %d Times",times);//��buffer����дһЩ����
					printf("buffer:%s\r\n",buffer);
				}
				printf("remain heap size : %d\r\n",xPortGetFreeHeapSize());  //��ȡʣ���ڴ��С
				break;
			case KEY1_PRES:				
				if(buffer!=NULL)vPortFree(buffer);	//�ͷ��ڴ�
				buffer=NULL;
			  printf("free heap\r\n");
			  printf("remain heap size : %d\r\n",xPortGetFreeHeapSize());  //��ȡʣ���ڴ��С
				break;
		}
  }
}

//��ʼ����������
void heap_task_creat(void)
{
    //����TASK1����
    xTaskCreate((TaskFunction_t )heap_task,             
                (const char*    )"heap_task",           
                (uint16_t       )HEAP_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )HEAP_TASK_PRIO,        
                (TaskHandle_t*  )&HeapTask_Handler);   
}
