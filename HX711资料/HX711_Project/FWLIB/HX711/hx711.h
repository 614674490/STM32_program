#ifndef _hx711_h
#define _hx711_h
#include "sys.h"
#define DOUT PBin(6)     //������
#define SCLK PBout(7)    //ʱ����

/* ������ ʱ���� �ߵ͵�ƽ */
#define DOUT_High   DOUT=1
#define DOUT_Low    DOUT=0
#define SCLK_High   SCLK=1
#define SCLK_Low    SCLK=0

//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
#define GapValue 370.0f

void HX711_Init(void);
long HX711_Read(void);
void Get_Gross_Weight(void);
void Get_Net_Weight(void);
long filter(void);
extern  long Gross_Weight ;   //ë��
extern long Net_Weight ;              //����
extern u8 Flag_Error;
extern long Init_Gross_Weight;  //��ʼƤ��
extern long All_Weight;
#endif


