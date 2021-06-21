#include "led_task.h"
#include "led.h"
#include "delay.h"
TaskHandle_t LED0Task_Handler;
//LED0������ 
void led0_task(void *pvParameters)
{
	//u16 led0_task_num=0;
    while(1)
    {
//			led0_task_num++;
//			taskENTER_CRITICAL();           //�����ٽ���->����   taskENTER_CRITICAL_From_ISR->�жϼ�
//			printf("led0_task run %d times\r\n",led0_task_num);
//			taskEXIT_CRITICAL();            //�˳��ٽ���      taskEXIT_CRITICAL_From_ISR->�жϼ�
//			delay_ms(10);
			// portDISABLE_INTERRUPTS();   //�ر�5-15֮����ж�
			 // printf("led0 task running\r\n");
        LED0=~LED0;
			  delay_ms(500);               //delay_xms()��������������� 5-15֮����жϲ������� �ȵ��ٴο����жϺ�Ż�����
			//portENABLE_INTERRUPTS();   //�ر�5-15֮����ж�
        //vTaskDelay(500);   
    }
}   

void led0_task_creat()
{
	 //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);  
}

