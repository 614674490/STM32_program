#ifndef _memory_h
#define _memory_h
#include "includes.h"
#include "sys.h"

//����һ���洢��
extern OS_MEM INTERNAL_MEM;	
//�洢���д洢������
#define INTERNAL_MEM_NUM		5
//ÿ���洢���С
//����һ��ָ�����ռ��4�ֽ����Կ�Ĵ�Сһ��ҪΪ4�ı���
//���ұ������һ��ָ�����(4�ֽ�)ռ�õĿռ�,����Ļ��洢�鴴�����ɹ�
#define INTERNAL_MEMBLOCK_SIZE	100 

//�洢�����ڴ�أ�ʹ���ڲ�RAM
extern __align(4) CPU_INT08U Internal_RamMemp[INTERNAL_MEM_NUM][INTERNAL_MEMBLOCK_SIZE];

void memory_task_creat(void);

#endif



