#include "timer_task.h"
#include "key.h"
#include "led.h"

/* ====================================== �����ʱ�����API���� ======================================== */
/*
		xTimerCreate()                    ������ʱ��(Ĭ�ϲ�����)                                              |
    xTimerCreateStatic()              ��̬������ʱ��                                                      |       
 	  xTimerStart()	                    ������ʱ��                                                          |
    xTimerStartFromISR()              ������ʱ��(�жϼ�)	                                              	|
		xTimerStop()                      ֹͣ��ʱ��                                                          |
		xTimerStopFromISR()               ֹͣ��ʱ��(�жϼ�)                                                  |
		xTimerReset()                     ��λ��ʱ��                                                          |
    xTimerResetFromISR		            ��λ��ʱ��(�жϼ�)                                                  |
*/
/* ===================================================================================================== */
TaskHandle_t TimerControlTask_Handler;
TimerHandle_t 	AutoReloadTimer_Handle;			//���ڶ�ʱ�����
TimerHandle_t	OneShotTimer_Handle;			//���ζ�ʱ�����

void timercontrol_task(void *pvParameters)
{
	 u8 key;
	//ֻ��������ʱ���������ɹ��˲��ܶ�����в���
	while(1)
	{
		if((AutoReloadTimer_Handle!=NULL)&&(OneShotTimer_Handle!=NULL))
		{
			key = KEY_Scan(0);
			switch(key)
			{
				case KEY0_PRES:     //��key1���µĻ���������ʱ��
					xTimerStart(AutoReloadTimer_Handle,0);	//�������ڶ�ʱ�� �ڶ�������Ϊ����ʱ��
				  xTimerStart(OneShotTimer_Handle,0);		//�������ζ�ʱ��
					printf("������ʱ��1��2\r\n");
					break;
				case KEY1_PRES:		//��key1���»��͹رն�ʱ��
					xTimerStop(AutoReloadTimer_Handle,0); 	//�ر����ڶ�ʱ��
					xTimerStop(OneShotTimer_Handle,0); 		//�رյ��ζ�ʱ��
					printf("�رն�ʱ��1��2\r\n");
					break;	
			}
		}
	}
}

void timercontrol_task_creat(void)
{
	//����������ڶ�ʱ��
    AutoReloadTimer_Handle=xTimerCreate((const char*		)"AutoReloadTimer",
									    (TickType_t			)1000,
							            (UBaseType_t		)pdTRUE,
							            (void*				)1,
							            (TimerCallbackFunction_t)AutoReloadCallback); //���ڶ�ʱ��������1s(1000��ʱ�ӽ���)������ģʽ
    //�������ζ�ʱ��
	OneShotTimer_Handle=xTimerCreate((const char*			)"OneShotTimer",
							         (TickType_t			)2000,     //2000*1ms=2s
							         (UBaseType_t			)pdFALSE,  //���ζ�ʱ��
							         (void*					)2,           //ID��
							         (TimerCallbackFunction_t)OneShotCallback); //���ζ�ʱ��������2s(2000��ʱ�ӽ���)������ģʽ		��ʱ���ص�����			  
    //������ʱ����������
    xTaskCreate((TaskFunction_t )timercontrol_task,             
                (const char*    )"timercontrol_task",           
                (uint16_t       )TIMERCONTROL_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TIMERCONTROL_TASK_PRIO,        
                (TaskHandle_t*  )&TimerControlTask_Handler);    
}

//���ڶ�ʱ���Ļص�����
void AutoReloadCallback(TimerHandle_t xTimer)
{
	LED0=!LED0;
}

//���ζ�ʱ���Ļص�����
void OneShotCallback(TimerHandle_t xTimer)
{
	LED1=!LED1;
  printf("��ʱ��2���н���\r\n");
}
