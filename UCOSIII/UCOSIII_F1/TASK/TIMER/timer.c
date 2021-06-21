#include "ucosiii_tmr.h"
#include "led.h"
#include "usart.h"
OS_TMR 	tmr1;		//��ʱ��1
OS_TMR	tmr2;		//��ʱ��2

void tmr1_task_create()
{
	OS_ERR err;
	//������ʱ��1
	OSTmrCreate((OS_TMR		*)&tmr1,		//��ʱ��1
                (CPU_CHAR	*)"tmr1",	//��ʱ������  OS_CFG_TMR_TASK_RATE_HZ=100 1/100=10ms->ʱ��ֱ���(>=5ms)
                (OS_TICK	 )20,			//20*10=200ms  ��ʼ���ӳ�ʱ�� �ӳ�֮�� �Ž��붨ʱ���ж�ģʽ
                (OS_TICK	 )100,    //100*10=1000ms                  ����ֵ
                (OS_OPT		 )OS_OPT_TMR_PERIODIC, //����ģʽ
                (OS_TMR_CALLBACK_PTR)tmr1_callback,//��ʱ��1�ص�����
                (void	    *)0,			//����Ϊ0
                (OS_ERR	    *)&err);		//���صĴ�����
}

void tmr2_task_create()
{
	OS_ERR err;  //��ͨ��OSTmrStart()�����´������ζ�ʱ��
	//������ʱ��2
	OSTmrCreate((OS_TMR		*)&tmr2,		//��ʱ��1
                (CPU_CHAR	*)"tmr2",	//��ʱ������  OS_CFG_TMR_TASK_RATE_HZ=100 1/100=10ms->ʱ��ֱ���(>=5ms)
                (OS_TICK	 )200,			//200*10=2000ms 
                (OS_TICK	 )0,   
                (OS_OPT		 )OS_OPT_TMR_ONE_SHOT, //���ζ�ʱ�� û������
                (OS_TMR_CALLBACK_PTR)tmr2_callback,//��ʱ��1�ص�����
                (void	    *)0,			//����Ϊ0
                (OS_ERR	    *)&err);		//���صĴ�����
}


/* �ڻص������� Ӧ�����κ�ɾ���������ʱ����ĺ��� */

/* =====================��غ���======================= */
/*                                                       |
    OSTmrCreate()	           //������ʱ��                |
		OSTmrDel()	             //ɾ����ʱ��                |
		OSTmrRemainGet()	       //��ȡ��ʱ��ʣ��ʱ��        |
		OSTmrStart()	           //������ʱ��                |
		OSTmrStateGet()	         //��ȡ��ǰ��ʱ��״̬        |
		OSTmrStop()	             //ֹͣ��ʱ��                |
*/
/* ===================================================== */

//��ʱ��1�Ļص�����
void tmr1_callback(void *p_tmr, void *p_arg)
{
	static u8 tmr1_num=0;
	tmr1_num++;		//��ʱ��1ִ�д�����1
	LED1=!LED1;
}

//��ʱ��2�Ļص�����
void tmr2_callback(void *p_tmr,void *p_arg)
{
	static u8 tmr2_num = 0;
	CPU_SR_ALLOC();        //Ϊ�˽����ٽ�����д�Ĵ���  
	tmr2_num++;		//��ʱ��2ִ�д�����1
	OS_CRITICAL_ENTER();	//�����ٽ���
	printf("��ʱ��2���н���\r\n");
	OS_CRITICAL_EXIT();		//�˳��ٽ���
}


