#include "stm32f10x.h" 
#include "sys.h" 
#include "key.h"
#include "delay.h"
#include "led.h"
#include "start_task.h"

int main(void)
{
	 FreeRTOS_Init();
	 start_task_creat();
	 vTaskStartScheduler();          //�����������
	 while(1);
}
