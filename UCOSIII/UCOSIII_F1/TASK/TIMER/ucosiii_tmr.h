#ifndef ucosiii_tmr_h
#define  ucosiii_tmr_h
#include "sys.h"
#include "includes.h"
extern OS_TMR 	tmr1;		//��ʱ��1
extern OS_TMR	tmr2;		//��ʱ��2
void tmr1_callback(void *p_tmr, void *p_arg); 	//��ʱ��1�ص�����
void tmr2_callback(void *p_tmr, void *p_arg);	//��ʱ��2�ص�����
void tmr1_task_create(void);
void tmr2_task_create(void);
#endif
