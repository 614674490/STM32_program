#include "hx711.h"
#include "delay.h"
#define  filter_times 2
long Init_Gross_Weight=0;  //��ʼƤ��
long All_Weight=0;         //������
long Gross_Weight = 0;
long Net_Weight = 0;
u8 Flag_Error=0;

/* ----------------------------- */
/* HX711 ��ʱ����                */
/* ----------------------------- */
void Hx711_Delay()
{
	__NOP();         //һ����������
}
/* ----------------------------- */
/* HX711 SCLK DOUT���ų�ʼ��     */
/* DOUT PB6                      */
/* SCLK PB7                      */
/* ----------------------------- */
void HX711_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//SCLK
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//DOUT
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;  //��������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

/* ----------------------------- */
/* ��ȡHX711                     */
/* 128����                       */
/* ----------------------------- */
long HX711_Read()
{
  long value;
	char i;
	DOUT_High;  //����������
	Hx711_Delay();
	SCLK_Low;   //����������
	value=0;
	while(DOUT);     //�ȴ�����
	for(i=0;i<24;i++)
	{
		SCLK_High;
		value<<=1;
		SCLK_Low;
		if(DOUT)  //�ж��Ƿ�����
			value++;
	}
	SCLK_High;
	value=value^0x800000;//��25�������½�����ʱ��ת������
	Hx711_Delay();
	SCLK_Low;
	return value;
}

/* ----------------------------- */
/* ��ȡëƤ����                  */
/* ----------------------------- */
void Get_Gross_Weight()
{
	  Gross_Weight=HX711_Read();
	  Gross_Weight-=Init_Gross_Weight;
}

/* ----------------------------- */
/* ��ȡʵ������                  */
/* ----------------------------- */
void Get_Net_Weight()
{
	All_Weight=filter();  //��ֹ����ͻ��
	Net_Weight=All_Weight-Gross_Weight;
	if(All_Weight>=0)  //����ʵ������  ���ش����� ���ؿ϶�������
	{
		Net_Weight = (unsigned int)((float)Net_Weight/GapValue); 	//����ʵ���ʵ������ ��λ��g
		All_Weight= (unsigned int)((float)All_Weight/GapValue);
		if(All_Weight>4900)  //��ǰ����
			Flag_Error=1;
		else
			Flag_Error=0;
	}
	else    //���ý��б��� ż������ָ���
	{
		Flag_Error=1;
		Net_Weight=0;
		All_Weight=0;
	}
}

/* �޷�ƽ���˲� */
long filter()
{
	long  last_value=0;  //�ϴβɼ�ֵ
	long  new_value=0;   //��ǰ�ɼ�ֵ
	long  sum=0;
	char count;
	for(count=0;count<filter_times;count++)
  {
		new_value=HX711_Read()-Init_Gross_Weight; 
		if(new_value<0&&last_value>=0) 
			new_value=last_value; 
		sum+=new_value; 
      	last_value=new_value;
  }
  return (long)((float)sum/(float)filter_times); 
}
	





