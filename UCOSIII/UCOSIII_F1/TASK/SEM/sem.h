#ifndef _sem_h
#define _sem_h
#include "includes.h"
#include "sys.h"
extern u8 share_resource[30];   //������Դ��

extern OS_SEM	MY_SEM;		//����һ���ź��������ڷ��ʹ�����Դ
extern OS_SEM	SYNC_SEM; //��������ͬ�
extern OS_MUTEX	TEST_MUTEX;		//����һ�������ź��� ������ȼ���ת
void sem_task_create(void); 
void mutex_test_task_creat(void);
void sem_share(char str[]);
#endif

