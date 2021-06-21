/******************** ��Ұ�ʿ ********************
 * �ļ���       ��adc.c
 * ����         ��ad������������
 *
 * ʵ��ƽ̨     ��LQ K60������
 *                ang PTB11  Gyto PTB10  Z PTE24
 *
 * ����          DAQI
**********************************************************************************/

#include "include.h"


tADC_Config Master_Adc_Config;          //�ýṹ���������Ҫ��ADC/PGA����

volatile struct ADC_MemMap *ADCx[2] = {ADC0_BASE_PTR, ADC1_BASE_PTR}; //��������ָ�����鱣�� ADCx �ĵ�ַ

/******************** ��Ұ�ʿ ********************
*
*  �������ƣ�adc_init
*  ����˵����AD��ʼ����ʹ��ʱ��,��ʼ��PTE24 PTB10 PTB11Ϊad����

*  �޸�ʱ�䣺2013-4-7
*************************************************************************/
volatile uint32 Gyro_sum,Gravity_sum;
volatile uint16 Gyro_,Gravity_;
void adc_init(void)
{
    SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );        //����ADC0ʱ��
    SIM_SOPT7 &= ~(SIM_SOPT7_ADC0ALTTRGEN_MASK  | SIM_SOPT7_ADC0PRETRGSEL_MASK);
    SIM_SOPT7 = SIM_SOPT7_ADC0TRGSEL(0);
    SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
    PORT_PCR_REG(PORTE_BASE_PTR, 24) =  PORT_PCR_MUX(0);    //��ʼ��PTE24Ϊad����
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
    PORT_PCR_REG(PORTB_BASE_PTR, 2) =  PORT_PCR_MUX(0);    //��ʼ�� PTB2Ϊad����
    
    SIM_SCGC3 |= (SIM_SCGC3_ADC1_MASK );
    SIM_SOPT7 &= ~(SIM_SOPT7_ADC1ALTTRGEN_MASK  | SIM_SOPT7_ADC1PRETRGSEL_MASK) ;
    SIM_SOPT7 = SIM_SOPT7_ADC1TRGSEL(0);
    
//    PORT_PCR_REG(PORTB_BASE_PTR, 10) =  PORT_PCR_MUX(0);
    PORT_PCR_REG(PORTB_BASE_PTR, 11) =  PORT_PCR_MUX(0);    //��ʼ�� PTB11Ϊad����

   
}
uint16 CCD_value(void)     //������һ·ģ������ADֵ������ ��ֵ
{
    u16  temp;
    
    temp=ad_once(ADC1, AD15, ADC_12bit);
    return (temp);
}
uint16 Gyro_value(void)     
{
//  u16 Gyro[20];

  Gyro_sum=0;
  uint8 i;
  for(i=0;i<20;i++)
  {
    Gyro_=ad_once(ADC0, AD12, ADC_16bit);
    Gyro_sum+=Gyro_;
  }//20��ת��ȡƽ��ֵ����ͨ�˲�
  Gyro_= Gyro_sum/20;
   
    return (Gyro_);
} 
uint16 Gravity_value(void)     
{
 // u16 Gravity[20];
//  u16 Gravity_;
  
  Gravity_sum=0;
//  Gyro_sum=0��
  uint8 i;
  for(i=0;i<20;i++)
  {
    Gravity_=ad_once(ADC0, AD17, ADC_12bit);
    Gravity_sum+=Gravity_;
  }//20��ת��ȡƽ��ֵ����ͨ�˲�
  Gravity_= Gravity_sum/20;
   
    return (Gravity_);
} 
/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�ad_once
*  ����˵�����ɼ�һ��һ·ģ������ADֵ
*  ����˵����ADCn        ģ��ţ� ADC0�� ADC1��
*            ADC_Channel ͨ����
*            ADC_nbit    ���ȣ� ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ��
*  �������أ��޷��Ž��ֵ
*  �޸�ʱ�䣺2012-2-10
*  ��    ע���ο����ݴ�ѧ�����̣�Bͨ���������������������
*************************************************************************/
u16 ad_once(ADCn adcn, ADC_Ch ch, ADC_nbit bit) //�ɼ�ĳ·ģ������ADֵ
{
    u16 result = 0;

    adc_start(adcn, ch, bit);	  //����ADCת��

    while (( ADC_SC1_REG(ADCx[adcn], 0 ) & ADC_SC1_COCO_MASK ) != ADC_SC1_COCO_MASK);
    result = ADC_R_REG(ADCx[adcn], 0);
    ADC_SC1_REG(ADCx[adcn], 0) &= ~ADC_SC1_COCO_MASK;
    return result;
}

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�adc_start
*  ����˵��������adc���������Bͨ�������������������������
*  ����˵����ADCx        ģ��ţ� ADC0�� ADC1��
*            ADC_Channel ͨ����
*            ADC_nbit    ���ȣ� ADC_8bit,ADC_12bit, ADC_10bit, ADC_16bit ��
*  �������أ���
*  �޸�ʱ�䣺2012-2-10
*  ��    ע���޸����ݴ�ѧ������
*************************************************************************/
void adc_start(ADCn adcn, ADC_Ch ch, ADC_nbit bit)
{

    Master_Adc_Config.STATUS1A = AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH( ch );

    //��ʼ��ADCĬ������
    Master_Adc_Config.CONFIG1  = ADLPC_NORMAL
                                 | ADC_CFG1_ADIV(ADIV_4)
                                 | ADLSMP_LONG
                                 | ADC_CFG1_MODE(bit)
                                 | ADC_CFG1_ADICLK(ADICLK_BUS);
    Master_Adc_Config.CONFIG2  = MUXSEL_ADCA    //MUXSEL_ADCA
                                 | ADACKEN_DISABLED
                                 | ADHSC_HISPEED
                                 | ADC_CFG2_ADLSTS(ADLSTS_20) ;

    Master_Adc_Config.COMPARE1 = 0x1234u ;                 //����ֵ
    Master_Adc_Config.COMPARE2 = 0x5678u ;                 //����ֵ

    adc_config_alt(ADCx[adcn], &Master_Adc_Config);       // ���� ADCn
}

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�adc_stop
*  ����˵����ֹͣADCת��
*  ����˵����ADCx        ģ��ţ� ADC0�� ADC1��
*            ADC_Channel ͨ����
*  �������أ���
*  �޸�ʱ�䣺2012-2-10
*  ��    ע���޸����ݴ�ѧ������
*************************************************************************/
void adc_stop(ADCn adcn)
{
    Master_Adc_Config.STATUS1A = AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(Module_disabled);
    adc_config_alt(ADCx[adcn], &Master_Adc_Config);  // ����ADC0
}


/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�adc_config_alt
*  ����˵������adc�Ĵ����ṹ�����ý�adc�Ĵ���
*  ����˵����adcmap      adc��ַ�Ĵ�����ַ��ADC0_BASE_PTR,ADC1_BASE_PTR��
*            ADC_CfgPtr  ��� �Ĵ���ֵ�Ľṹ��
*  �������أ���
*  �޸�ʱ�䣺2012-2-10
*  ��    ע���޸Ĺٷ����̵�����
*************************************************************************/
void adc_config_alt(ADC_MemMapPtr adcmap, tADC_ConfigPtr ADC_CfgPtr)
{
    ADC_CFG1_REG(adcmap) = ADC_CfgPtr->CONFIG1;
    ADC_CFG2_REG(adcmap) = ADC_CfgPtr->CONFIG2;
    ADC_CV1_REG(adcmap)  = ADC_CfgPtr->COMPARE1;
    ADC_CV2_REG(adcmap)  = ADC_CfgPtr->COMPARE2;
    ADC_SC2_REG(adcmap)  = ADC_CfgPtr->STATUS2;
    ADC_SC3_REG(adcmap)  = ADC_CfgPtr->STATUS3;
    ADC_PGA_REG(adcmap)  = ADC_CfgPtr->PGA;
    ADC_SC1_REG(adcmap, A) = ADC_CfgPtr->STATUS1A;
    ADC_SC1_REG(adcmap, B) = ADC_CfgPtr->STATUS1B;
}



