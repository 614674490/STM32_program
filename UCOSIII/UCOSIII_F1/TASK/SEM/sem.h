#ifndef _sem_h
#define _sem_h
#include "includes.h"
#include "sys.h"
extern u8 share_resource[30];   //共享资源区

extern OS_SEM	MY_SEM;		//定义一个信号量，用于访问共享资源
extern OS_SEM	SYNC_SEM; //用于任务同?
extern OS_MUTEX	TEST_MUTEX;		//定义一个互斥信号量 解决优先级反转
void sem_task_create(void); 
void mutex_test_task_creat(void);
void sem_share(char str[]);
#endif

