#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "task.h"
int main(void)
{ 
	OS_ERR err;
	CPU_SR_ALLOC();
	
	BSP_Init();
	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//����-�ٽ���
	start_Task_create();	//������ʼ����
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}

