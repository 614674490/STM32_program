#include "list_task.h"
#include "key.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
//�б�ı������ڴӶ��ͬ���ȼ��ľ��������в�����һ��Ҫ���е�����

/* ====================== �б�&�б��� ====================== */
/*     
                             �б�
														 uxNumberOfItems  �б�����Ŀ
														 pxIndex          ��ǰָ��
														 xListEnd
														 
                             �б���
	                         xItemValue
	                           pxNext
	                         pxPrevious
	                           pvOwner    �������ƿ�TCB
	                         pvContainer  �����б�
	                         
													    MINI
	                         xItemValue
	                           pxNext
	                         pxPrevious
*/
/* =========================================================== */									 
TaskHandle_t ListTask_Handler;

List_t TestList;		//�������б�
ListItem_t ListItem1;	//�������б���1
ListItem_t ListItem2;	//�������б���2
ListItem_t ListItem3;

void list_task(void *pvParameters)
{
	//u16 list_task_num=0;
//	//��һ������ʼ���б���б���
	vListInitialise(&TestList);
	vListInitialiseItem(&ListItem1);
	vListInitialiseItem(&ListItem2);
	
	ListItem1.xItemValue=40;			//ListItem1�б���ֵΪ40
	ListItem2.xItemValue=60;			//ListItem2�б���ֵΪ60
	ListItem3.xItemValue=50;			//ListItem3�б���ֵΪ50
	
	//�ڶ�������ӡ�б�������б���ĵ�ַ
	printf("/*******************�б���б����ַ*******************/\r\n");
	printf("��Ŀ                              ��ַ				    \r\n");
	printf("TestList                          %#x					\r\n",(int)&TestList);
	printf("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);
	printf("TestList->xListEnd                %#x					\r\n",(int)(&TestList.xListEnd));
	printf("ListItem1                         %#x					\r\n",(int)&ListItem1);
	printf("ListItem2                         %#x					\r\n",(int)&ListItem2);
	printf("ListItem3                         %#x					\r\n",(int)&ListItem3);
	printf("/************************����**************************/\r\n");
	printf("�����б�1\r\n");

	vListInsert(&TestList,&ListItem1);		//�����б���ListItem1
	
	printf("/******************����б���ListItem1*****************/\r\n");
	printf("��Ŀ                              ��ַ				    \r\n");
	printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
	printf("/*******************ǰ�������ӷָ���********************/\r\n");
	printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
	printf("/************************����**************************/\r\n");
	printf("����KEY0������!\r\n\r\n\r\n");
	while(KEY_Scan(0)!=KEY0_PRES) delay_ms(10);					//�ȴ�KEY0������
	//���Ĳ������б�TestList����б���ListItem2����ͨ�����ڴ�ӡ����
	//�б����г�Ա����pxNext��pxPrevious��ֵ��ͨ��������ֵ�۲��б�
	//�����б��е����������
	vListInsert(&TestList,&ListItem2);	//�����б���ListItem2
	printf("/******************����б���ListItem2*****************/\r\n");
	printf("��Ŀ                              ��ַ				    \r\n");
	printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
	printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
	printf("/*******************ǰ�������ӷָ���********************/\r\n");
	printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
	printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
	printf("/************************����**************************/\r\n");
	printf("����KEY0������!\r\n\r\n\r\n");
	while(KEY_Scan(0)!=KEY0_PRES) delay_ms(10);					//�ȴ�KEY0������
	
	//���岽�����б�TestList����б���ListItem3����ͨ�����ڴ�ӡ����
	//�б����г�Ա����pxNext��pxPrevious��ֵ��ͨ��������ֵ�۲��б�
	//�����б��е����������
	vListInsert(&TestList,&ListItem3);	//�����б���ListItem3
	printf("/******************����б���ListItem3*****************/\r\n");
	printf("��Ŀ                              ��ַ				    \r\n");
	printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
	printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
	printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
	printf("/*******************ǰ�������ӷָ���********************/\r\n");
	printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
	printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
	printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
	printf("/************************����**************************/\r\n");
	printf("����KEY1��ɾ��!\r\n\r\n\r\n");
	while(KEY_Scan(0)!=KEY1_PRES) delay_ms(10);					//�ȴ�KEY_UP������
	
	//��������ɾ��ListItem2����ͨ�����ڴ�ӡ�����б����г�Ա����pxNext��
	//pxPrevious��ֵ��ͨ��������ֵ�۲��б������б��е����������
	uxListRemove(&ListItem2);						//ɾ��ListItem2
	printf("/******************ɾ���б���ListItem2*****************/\r\n");
	printf("��Ŀ                              ��ַ				    \r\n");
	printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
	printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
	printf("/*******************ǰ�������ӷָ���********************/\r\n");
	printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
	printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
	printf("/************************����**************************/\r\n");
	printf("����KEY1������!\r\n\r\n\r\n");
	while(KEY_Scan(0)!=KEY1_PRES) delay_ms(10);					//�ȴ�KEY_UP������
	
	//���߲���ɾ��ListItem2����ͨ�����ڴ�ӡ�����б����г�Ա����pxNext��
	//pxPrevious��ֵ��ͨ��������ֵ�۲��б������б��е����������
	TestList.pxIndex=TestList.pxIndex->pxNext;			//pxIndex�����һ�����pxIndex�ͻ�ָ��ListItem1��
	vListInsertEnd(&TestList,&ListItem2);				//�б�ĩβ����б���ListItem2
	printf("/***************��ĩβ����б���ListItem2***************/\r\n");
	printf("��Ŀ                              ��ַ				    \r\n");
	printf("TestList->pxIndex                 %#x					\r\n",(int)TestList.pxIndex);
	printf("TestList->xListEnd->pxNext        %#x					\r\n",(int)(TestList.xListEnd.pxNext));
	printf("ListItem2->pxNext                 %#x					\r\n",(int)(ListItem2.pxNext));
	printf("ListItem1->pxNext                 %#x					\r\n",(int)(ListItem1.pxNext));
	printf("ListItem3->pxNext                 %#x					\r\n",(int)(ListItem3.pxNext));
	printf("/*******************ǰ�������ӷָ���********************/\r\n");
	printf("TestList->xListEnd->pxPrevious    %#x					\r\n",(int)(TestList.xListEnd.pxPrevious));
	printf("ListItem2->pxPrevious             %#x					\r\n",(int)(ListItem2.pxPrevious));
	printf("ListItem1->pxPrevious             %#x					\r\n",(int)(ListItem1.pxPrevious));
	printf("ListItem3->pxPrevious             %#x					\r\n",(int)(ListItem3.pxPrevious));
	printf("/************************����**************************/\r\n\r\n\r\n");
//	while(1)
//	{
//      list_task_num++;
//			taskENTER_CRITICAL();           //�����ٽ���->����   taskENTER_CRITICAL_From_ISR->�жϼ�
//			printf("list_task run %d times\r\n",list_task_num);
//			taskEXIT_CRITICAL();            //�˳��ٽ���      taskEXIT_CRITICAL_From_ISR->�жϼ�
//			delay_ms(10);
//	}
}

void list_task_creat(void)
{
	//����LIST����
    xTaskCreate((TaskFunction_t )list_task,     
                (const char*    )"list_task",   
                (uint16_t       )LIST_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )LIST_TASK_PRIO,
                (TaskHandle_t*  )&ListTask_Handler); 
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
}

