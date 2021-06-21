#include "led_task.h"
#include "led.h"
#include "usart.h"
OS_TCB LedTaskTCB;
CPU_STK LED_TASK_STK[LED_STK_SIZE];

void led_task(void *p_arg)
{
	OS_ERR err;          //���ڷ��ش�����Ϣ
	CPU_SR_ALLOC();        //Ϊ�˽����ٽ�����д�Ĵ���  
	p_arg = p_arg;
	while(1)
	{
		OS_CRITICAL_ENTER();//����-�ٽ���
		printf("led task running\r\n");
		OS_CRITICAL_EXIT();	//�˳��ٽ���	 
		LED=!LED;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ500ms*/
	}

}

//����LED0����
void led_task_create(void)
{
	OS_ERR err;
	OSTaskCreate((OS_TCB 	* )&LedTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"led task", 		    //��������
                 (OS_TASK_PTR )led_task,   //������
                 (void		* )0,					    //���ݸ��������Ĳ���
                 (OS_PRIO	  )LED_TASK_PRIO,   //�������ȼ�  
                 (CPU_STK   * )&LED_TASK_STK[0],		//�����ջ����ַ
                 (CPU_STK_SIZE)LED_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)LED_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					     //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
}


