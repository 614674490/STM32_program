#include "adc.h"
#include "delay.h"

//��ʼ��ADC
//����ADC1��ͨ��0~7,��Ӧ��ϵ����
//ADC1_CH0-->PA0	
//ADC1_CH1-->PA1	
//ADC1_CH2-->PA2
//ADC1_CH3-->PA3	
//ADC1_CH4-->PA4	
//ADC1_CH5-->PA5	
//ADC1_CH6-->PA6
//ADC1_CH7-->PA7
void ADC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef  ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);  //ʹ��IO�ں�ADCʱ��
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;               //ģ����������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;    //PA0-1
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;       //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	 ADC_DeInit();                        //��ADC��Ϊȱʡֵ �˾䲻��ʡȥ ��Ȼ�޷�ʵ�ֶ�·ADC
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
//	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
	
	//��ʼ��ADC
	ADC_InitStructure.ADC_Resolution=ADC_Resolution_12b;  //12Ϊ����
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;            //ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;      //����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge=ADC_ExternalTrigConvEdge_None;   //�������
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;     //�����Ҷ���
	ADC_InitStructure.ADC_NbrOfConversion=2;               ///����ת��ͨ��
	ADC_Init(ADC1,&ADC_InitStructure);
	
	ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_1;  //����DMA
	ADC_CommonInitStructure.ADC_Mode=ADC_Mode_Independent;      //����ģʽ
	ADC_CommonInitStructure.ADC_Prescaler=ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz
	ADC_CommonInitStructure.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_5Cycles;  //���β���ʱ����Ϊ5������
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);  //480������
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_480Cycles);
	
	
	ADC_Cmd(ADC1,ENABLE);                                //ʹ��ADC1
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE); //Դ���ݱ仯ʱ ����DMA����
	ADC_DMACmd(ADC1,ENABLE);                          //ʹ��ADC��DMAͨ��
	ADC_SoftwareStartConv(ADC1);                //�����ADC
	
}


