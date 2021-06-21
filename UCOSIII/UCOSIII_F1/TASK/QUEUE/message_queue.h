#ifndef _message_queue_h
#define _message_queue_h
#include "includes.h"
#include "sys.h"

#define KEYMSG_Q_NUM	1	//������Ϣ���е�����
#define DATAMSG_Q_NUM	10	//�������ݵ���Ϣ���е�����
#define TASK_Q_NUM	4		//�������ڽ���Ϣ���еĳ���

extern OS_Q KEY_Msg;				//����һ����Ϣ���У����ڰ�����Ϣ���ݣ�ģ����Ϣ����
extern OS_Q DATA_Msg;				//����һ����Ϣ���У����ڷ�������

void message_queue_task_creat(void);
void check_msg_queue(OS_Q Msg); 
#endif

