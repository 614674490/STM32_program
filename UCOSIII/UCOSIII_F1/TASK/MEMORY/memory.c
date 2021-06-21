#include "memory.h"
#include "task_start.h"
#include "key.h"

/* =====================��غ���======================= */
/*                                                       |
    OSMemCreate()           //����һ���洢����           |
		OSMemGet()	             //�Ӵ洢���л��һ���洢��  |
		OSMemPut()	             //�黹�洢��                |
*/
/* ==================================================== */

// �ŵ㣺����malloc()��free(),��ʽ�洢����Ƭ�� ���²��ܷ��䵽���ʴ�С�������洢��
// ȱ�㣺����Բ����� ֻ���Կ�Ϊ��λ���з�����ͷ� ÿ��Ĵ�С�ǹ̶���

//ע�⣺��Ҫ���ڴ�����֮�����ͷ��ڴ� ��ʱ������ڴ�й¶
OS_MEM INTERNAL_MEM;
__align(4) CPU_INT08U Internal_RamMemp[INTERNAL_MEM_NUM][INTERNAL_MEMBLOCK_SIZE];

OS_TCB MEMORY_MAIN_TaskTCB;
CPU_STK MEMORY_MAIN_TASK_STK[MULTI_MAIN_STK_SIZE];

OS_TCB MEMORY_TaskTCB;
CPU_STK MEMORY_TASK_STK[MULTI_STK_SIZE];
 
void memory_task_creat()
{
	OS_ERR err;
	//����һ���洢����
	OSMemCreate((OS_MEM*	)&INTERNAL_MEM,
				(CPU_CHAR*	)"Internal Mem",
				(void*		)&Internal_RamMemp[0][0],  //�洢������ַ
				(OS_MEM_QTY	)INTERNAL_MEM_NUM,       //�洢������
				(OS_MEM_SIZE)INTERNAL_MEMBLOCK_SIZE, //���С
				(OS_ERR*	)&err);
		//����������
	OSTaskCreate((OS_TCB*     )&MEMORY_MAIN_TaskTCB,		
				 (CPU_CHAR*   )"Main task", 		
                 (OS_TASK_PTR )memory_main_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )MEMORY_MAIN_TASK_PRIO,     
                 (CPU_STK*    )&MEMORY_MAIN_TASK_STK[0],	
                 (CPU_STK_SIZE)MEMORY_MAIN_STK_SIZE/10,	
                 (CPU_STK_SIZE)MEMORY_MAIN_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//����һ���ڴ��������
	OSTaskCreate((OS_TCB*     )&MEMORY_TaskTCB,		
				 (CPU_CHAR*   )"MemManage task", 		
                 (OS_TASK_PTR )memory_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )MEMORY_TASK_PRIO,     
                 (CPU_STK*    )&MEMORY_TASK_STK[0],	
                 (CPU_STK_SIZE)MEMORY_STK_SIZE/10,	
                 (CPU_STK_SIZE)MEMORY_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
}

//�������������
void memory_main_task(void *p_arg)
{
	u8 key;
	static u8 internal_memget_num=0;
	CPU_INT08U *internal_buf;
	OS_ERR err;
	while(1)
	{
		key = KEY_Scan(0);  //ɨ�谴��
		switch(key)
		{
			case KEY0_PRES:
				internal_buf=OSMemGet((OS_MEM*)&INTERNAL_MEM,
								      (OS_ERR*)&err);
				if(err == OS_ERR_NONE) //�ڴ�����ɹ�
				{
					printf("internal_buf�ڴ�����֮��ĵ�ַΪ:%#x\r\n",(u32)(internal_buf));
					internal_memget_num++;
					printf("INTERNAL_MEM Use %d times\r\n",internal_memget_num);
				}
				if(err == OS_ERR_MEM_NO_FREE_BLKS) //�ڴ�鲻��
				{
					printf("INTERNAL_MEM Empty!\r\n");
				}
				break;
			case KEY1_PRES:
				if(internal_buf != NULL) //internal_buf��Ϊ�վ��ͷ��ڴ�
				{
					OSMemPut((OS_MEM*	)&INTERNAL_MEM,		//�ͷ��ڴ�
							 (void*		)internal_buf,
							 (OS_ERR* 	)&err);
					printf("internal_buf�ڴ��ͷ�֮��ĵ�ַΪ:%#x\r\n",(u32)(internal_buf));
							 printf("Memory Put success!\r\n");
				}
				break;
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);   //��ʱ10ms
	}
}

//�ڴ��������
void memory_task(void *p_arg)
{
	OS_ERR err;
	static u16 last_total=0;
	static u16 last_remain=0;
	while(1)
	{
		if(INTERNAL_MEM.NbrMax!=last_total)
		{
			printf("Total: %d\r\n",INTERNAL_MEM.NbrMax);
			last_total=INTERNAL_MEM.NbrMax;
		}
		if(INTERNAL_MEM.NbrFree!=last_remain)
		{
			printf("Remain: %d\r\n",INTERNAL_MEM.NbrFree);
			last_remain=INTERNAL_MEM.NbrFree;
		}
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_PERIODIC,&err);//��ʱ100ms
	}
}
