#ifndef _queue_task_h
#define _queue_task_h
#include "start_task.h"
#include "queue.h"
 
#define MESSAGE_Q_NUM   10   	//�������ݵ���Ϣ���е����� 

extern QueueHandle_t Message_Queue;	//��Ϣ���о��
void check_msg_queue(QueueHandle_t Message_Queue);
#endif

