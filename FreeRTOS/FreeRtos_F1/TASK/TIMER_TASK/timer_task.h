#ifndef _timer_task_h
#define  _timer_task_h
#include "start_task.h"
#include "timers.h"


extern TimerHandle_t 	AutoReloadTimer_Handle;			//���ڶ�ʱ�����
extern TimerHandle_t	OneShotTimer_Handle;			//���ζ�ʱ�����

void AutoReloadCallback(TimerHandle_t xTimer); 	//���ڶ�ʱ���ص�����
void OneShotCallback(TimerHandle_t xTimer);		//���ζ�ʱ���ص�����

#endif



