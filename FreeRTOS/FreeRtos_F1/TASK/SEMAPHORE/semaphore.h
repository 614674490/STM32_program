#ifndef _semaphore_h
#define _semaphore_h
#include "start_task.h"
#include "semphr.h"

/*               �ź������Ϳ���                 */
#define IS_OPEN_binary_semaphore_TASK    0
#define IS_OPEN_count_semaphore_TASK     0
#define IS_OPEN_recursive_semaphore_TASK 0

typedef enum 
{
	LED0_ON,
	LED0_OFF,
	LED1_ON,
	LED1_OFF,
	ERROR_COMMAND
}LED_COMMAND;

LED_COMMAND CommandProcess(u8 *str);

extern LED_COMMAND led_command;
extern SemaphoreHandle_t Binary_Semaphore;	//��ֵ�ź������
extern SemaphoreHandle_t Count_Semaphore;  //�������ź������
extern SemaphoreHandle_t Recursive_Semaphore;  //�ݹ黥���ź���
#endif



