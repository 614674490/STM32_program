#ifndef _pendmulti_h
#define _pendmulti_h
#include "includes.h"
#include "sys.h"

extern OS_SEM	Test_Sem1;			//�ź���1		
extern OS_Q	Test_Q;				//��Ϣ����						
#define QUEUE_NUM		10	//��Ϣ���г���
#define CORE_OBJ_NUM	2	//�ں˶��������һ��2����1���ź�����һ����Ϣ����					

void pendmulti_task_creat(void);
#endif


