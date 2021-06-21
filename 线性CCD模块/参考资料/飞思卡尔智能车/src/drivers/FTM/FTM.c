/******************** ��Ұ�ʿ ********************
 * �ļ���       ��FTM.c
 * ����         ��FTM������������
 *
 * ʵ��ƽ̨     ��LQ K60������
 *               PWMռ��FTM1��CH0��CH1��CH2��CH3ͨ������PTC1��PTC2��PTC3��PTC4����
 *
 * ����          DAQI
**********************************************************************************/

#include "include.h"


/*********** FTMn_CHn PWM�����ʼ������ ***********/
/*
        --FTM0--  --FTM1--  --FTM2--
CH0       PTC1      PTA8      PTA10
CH1       PTC2      PTA9      PTA11
CH2       PTC3       ��         ��
CH3       PTC4       ��         ��
CH4       PTD4       ��         ��
CH5       PTD5       ��         ��
CH6       PTD6       ��         ��
CH7       PTD7       ��         ��

����ʾû��
*/


/*************************************************************************
*                   ��Ұ�ʿ          
*
*  �������ƣ�FTM_PWM_init
*  ����˵������ʼ��FTM��PWM����CH0��CH1��CH2��CH3ͨ����������Ƶ��Ϊ1ms
*  ����˵�������ö˿�����Ϊ PTC1 PTC2 PTC3 PTC4
*  �������أ���
*  �޸�ʱ�䣺2013-4-3
*  ��    ע��ͬһ��FTM����ͨ����PWMƵ����һ����
*************************************************************************/

void FTM_PWM_init(void)
{
   // SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;                          //ʹ��PORTCʱ��
    PORT_PCR_REG(PORTC_BASE_PTR, 1) = PORT_PCR_MUX(4);  // PTC1
    PORT_PCR_REG(PORTC_BASE_PTR, 2) = PORT_PCR_MUX(4);  // PTC2
    PORT_PCR_REG(PORTC_BASE_PTR, 3) = PORT_PCR_MUX(4);  // PTC3
    PORT_PCR_REG(PORTC_BASE_PTR, 4) = PORT_PCR_MUX(4);  // PTC4
    SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;                           //ʹ��FTM0ʱ��
    FTM0_MODE|= FTM_MODE_WPDIS_MASK;// д������ֹ
    //����������ض���PWM ģʽMSB=1��ELSB:ELSA=10
    FTM0_C0SC |= FTM_CnSC_ELSB_MASK;//ELSB=1��ELSA=0������룬�ȸߺ��
    FTM0_C0SC &= ~FTM_CnSC_ELSA_MASK;
    FTM0_C0SC |= FTM_CnSC_MSB_MASK;//MSB=1��ģʽѡ����ض���
    FTM0_C1SC |= FTM_CnSC_ELSB_MASK;//ELSB=1��ELSA=0������룬�ȸߺ��
    FTM0_C1SC &= ~FTM_CnSC_ELSA_MASK;
    FTM0_C1SC |= FTM_CnSC_MSB_MASK;//MSB=1��ģʽѡ����ض���
    FTM0_C2SC |= FTM_CnSC_ELSB_MASK;//ELSB=1��ELSA=0������룬�ȸߺ��
    FTM0_C2SC &= ~FTM_CnSC_ELSA_MASK;
    FTM0_C2SC |= FTM_CnSC_MSB_MASK;//MSB=1��ģʽѡ����ض���
    FTM0_C3SC |= FTM_CnSC_ELSB_MASK;//ELSB=1��ELSA=0������룬�ȸߺ��
    FTM0_C3SC &= ~FTM_CnSC_ELSA_MASK;
    FTM0_C3SC |= FTM_CnSC_MSB_MASK;//MSB=1��ģʽѡ����ض���
    FTM0_SC=0x0c;//�жϽ�ֹ,CLKS=01ʱ��Դ��������ʱ��48MHz��PS=100;16 ��Ƶ��õ�3MHz,CPWMS=0����������
    FTM0_MODE&=~1;//FTM0 ʹ�� 
    FTM0_OUTMASK=0Xf0;// ͨ��CH0��CH1��CH2��CH3 �����������������ͨ��
    FTM0_QDCTRL&=~FTM_QDCTRL_QUADEN_MASK;// ��ֹ��������ģʽ
    FTM0_COMBINE=0;//DECAPEN=0 ��˫���ز�׽��ֹ�� COMBINE=0 ��������
    FTM0_CNTIN=0;//FTM0 ��������ʼֵΪ 0
    FTM0_MOD=599;// ����ֵ������Ϊ�� MOD-CNTIN+1 �� * ʱ������ =0.4ms 
    FTM0_C0V=0;//�ߵ�ƽ0ms
    FTM0_C1V=0;//�ߵ�ƽ0ms
    FTM0_C2V=0;//�ߵ�ƽ0ms
    FTM0_C3V=0;//�ߵ�ƽ0ms
    FTM0_CNT=100;                                               
}

/*************************************************************************
*                   ��Ұ�ʿ          
*  ����˵����ռ�ձȿ��ơ�void L_PWM_GO(uint8 duty)������duty  0-1000;��ֵԽ���ٶ�Խ��
*  ����˵�������ö˿�����Ϊ PTC1 PTC2 PTC3 PTC4
*  �������أ���
*  �޸�ʱ�䣺2013-4-3
*  ��    ע��ͬһ��FTM����ͨ����PWMƵ����һ����
*************************************************************************/

void R_PWM_BACK(uint16 duty)
{
  uint16 speed;
  speed=duty*3;
  FTM0_C2V=speed;
  
}
void R_PWM_GO(uint16 duty)
{
  uint16 speed;
  speed=duty*3;
  FTM0_C3V=speed;
}
void L_PWM_GO(uint16 duty)
{
  uint16 speed;
  speed=duty*3;
  FTM0_C1V=speed;

}
void L_PWM_BACK(uint16 duty)
{
  uint16 speed;
  speed=duty*3;
  FTM0_C0V=speed;

}

/*************************************************************************
*                   ��Ұ�ʿ          
*
*  �������ƣ�FTM_QUAD_init
*  ����˵������������
*  ����˵����PTA10 ����ΪFTM2_PHA ����;PTA11 ����ΪFTM2_PHB ����  �������ֱ�����
             PTA8 ����ΪFTM1_PHA ����; PTA9 ����ΪFTM1_PHB ����  �������ֱ�����

*  ����������������Ϊ���������Ҳ����Ϊ����������������ʱ���������ۼӼ�����
MOD �󣬼����ص�CNTIN����ʱTOF ��λ����TOFDIR λҲ��1����ʾ����������������
ʱ�����������ݼ���������CNTIN ��ΪMOD ʱ��TOF ��1����TOFDIR Ϊ0����ʾ���������
*

*  �޸�ʱ�䣺2013-4-6
*  ��    ע��ͬһ��FTM����ͨ����PWMƵ����һ����
*************************************************************************/
void FTM_QUAD_init(void)
{
//  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;                          //ʹ��PORTAʱ��
  PORTA_PCR10= PORT_PCR_MUX(6); // ��������PTA10 ����ΪFTM2_PHA ����
  PORTA_PCR11= PORT_PCR_MUX(6); // ��������PTA11 ����ΪFTM2_PHB ����
  SIM_SCGC3|=SIM_SCGC3_FTM2_MASK;//ʹ��FTM2 ʱ��
  FTM2_MODE|= FTM_MODE_WPDIS_MASK;// д������ֹ
  FTM2_QDCTRL|=FTM_QDCTRL_QUADMODE_MASK;//AB ��ͬʱȷ������ͼ���ֵ
  FTM2_CNTIN=0;//FTM0 ��������ʼֵΪ 0
  FTM2_MOD=65535;// ����ֵ
  FTM2_QDCTRL|=FTM_QDCTRL_QUADEN_MASK;// ���� FTM2 ��������ģʽ
  FTM2_MODE |= FTM_MODE_FTMEN_MASK;//FTM2EN =1
  FTM2_CNT=0;
  
  PORTA_PCR8= PORT_PCR_MUX(6); // ��������PTA10 ����ΪFTM2_PHA ����
  PORTA_PCR9= PORT_PCR_MUX(6); // ��������PTA11 ����ΪFTM2_PHB ����
  SIM_SCGC6|=SIM_SCGC6_FTM1_MASK;//ʹ��FTM1 ʱ��
  FTM1_MODE|= FTM_MODE_WPDIS_MASK;// д������ֹ
  FTM1_QDCTRL|=FTM_QDCTRL_QUADMODE_MASK;//AB ��ͬʱȷ������ͼ���ֵ
  FTM1_CNTIN=0;//FTM0 ��������ʼֵΪ 0
  FTM1_MOD=65535;// ����ֵ
  FTM1_QDCTRL|=FTM_QDCTRL_QUADEN_MASK;// ���� FTM  ��������ģʽ
  FTM1_MODE |= FTM_MODE_FTMEN_MASK;//FTM1EN =1
  FTM1_CNT=0;
  
}