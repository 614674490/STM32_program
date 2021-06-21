#include "ccd.h"
#include "adc.h"	
#include "usart.h"
#include "string.h"
#include "math.h"
#include "delay.h"
#include "dma.h"
u16 ccd_adc;
ccdData_Type ccd_piexl[128]={0};
ccdData_Type Median,Threshold;   //����CCD  ���
ccdData_Type Last_Median;
ccdData_Type Left_Side,Right_Side;

//CCD��ʼ��
void CCD_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //PA.1 �˿����� SI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.1
	GPIO_SetBits(GPIOA,GPIO_Pin_2);						 //PA.1 �����
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //PA.3 �˿�����, �������  CLK
	GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
	GPIO_SetBits(GPIOA,GPIO_Pin_3); 						 //PA.3	�����
	
	#if DMA_Tran //����DMA����
	ADC1_init();
	MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)&ccd_adc,10); 
	
	#else
	ADC_init();
	#endif
	
}


//��ʱ�����������ع�ʱ�� *
void Dly_us(int a)
{
   int ii;    
   for(ii=0;ii<a;ii++);      
}


//����ʱ�����ζ�ȡCCD�����ģ���ѹֵ *
void RD_TSL(void) 
{
	u8 i=0,tslp=0;
  TSL_CLK=1;
  TSL_SI=0; 		//������129��CLK�Խ������β���
  Dealy;
	
  TSL_SI=1; 
  TSL_CLK=0;
	Dealy;
	
  TSL_CLK=1;
  TSL_SI=0;     //ʹSI����һ���½��� AO��ʼ�ɼ�ģ������
	Dealy;
	
  for(i=0;i<128;i++)//��ÿ��CLK�½���ʱ�ɼ�һ������ ���ɼ�128������
  { 
    TSL_CLK=0; 			//CLK���� ÿ���½��زɼ�һ������
		Dealy;
		#if DMA_Tran //����DMA����
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		ccd_piexl[tslp++]=(ccdData_Type)ccd_adc*0.0625;
		ADC_SoftwareStartConvCmd(ADC1, DISABLE);
		#else
    ccd_piexl[tslp++]=(ccdData_Type)(Get_Adc(1))*0.0625;   //(Get_Adc(1))>>4
		#endif
    TSL_CLK=1;
		Dealy;
  }
}

//����CCDȡ��ֵ
void getCCDMedian(void)
{ 
	 static u16 i,j;
	 static ccdData_Type Left,Right;
	 static ccdData_Type value1_max,value1_min;
	
	 value1_max=ccd_piexl[0];  //��̬��ֵ�㷨����ȡ������Сֵ
   for(i=5;i<123;i++)   //���߸�ȥ��5����
   {
      if(value1_max<=ccd_piexl[i])
				value1_max=ccd_piexl[i];
   }
	 value1_min=ccd_piexl[0];  //��Сֵ
   for(i=5;i<123;i++) 
   {
      if(value1_min>=ccd_piexl[i])
				value1_min=ccd_piexl[i];
   }
   Threshold=(value1_max+value1_min)/2;	  //���������������ȡ����ֵ
	 for(i = 5;i<118; i++)   //Ѱ�����������
	 {
			if(ccd_piexl[i]>Threshold&&ccd_piexl[i+1]>Threshold&&ccd_piexl[i+2]>Threshold&&ccd_piexl[i+3]<Threshold&&ccd_piexl[i+4]<Threshold&&ccd_piexl[i+5]<Threshold)
			{	//ȥ��3���������ص��ë��
				Left=i;
				Left_Side=Left;
				break;	
			}
	 }
	 for(j = 118;j>5; j--)//Ѱ���ұ�������
   {    
			if(ccd_piexl[j]<Threshold&&ccd_piexl[j+1]<Threshold&&ccd_piexl[j+2]<Threshold&&ccd_piexl[j+3]>Threshold&&ccd_piexl[j+4]>Threshold&&ccd_piexl[j+5]>Threshold)
			{	//ȥ��3���������ص��ë��
				Right=j;
				Right_Side=Right;
				break;
			}
   }
	Median=(Right+Left)/2;//��������λ��
	if(fabs(Median-Last_Median)>70)   //�������ߵ�ƫ����̫��
		Median=Last_Median;    //��ȡ��һ�ε�ֵ
	Last_Median=Median;  //������һ�ε�ƫ��
}


