#ifndef _key_h
#define _key_h
#include "sys.h"
/******λ����*************/
#define KEY0 PBin(4)
#define KEY1 PBin(5)
//#define WK_UP PAin(0)
/****************�⺯��******************///���·�������
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)     //��ȡ����1

#define KEY0_PRES 1      //����0���£�����1
#define KEY1_PRES 3      //����0���£�����1
#define WK_UP_PRES 2     //����1���·���2

void KEY_Init(void);     //IO�ڳ�ʼ��
u8 KEY_Scan(u8 mode);    //����ɨ�躯��

#endif


