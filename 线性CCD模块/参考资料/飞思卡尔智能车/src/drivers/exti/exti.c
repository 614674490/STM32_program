/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��exti.c
 * ����         ��EXTI�ⲿGPIO�ж�����
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/

#include "include.h"



/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�exti_init
*  ����˵����EXTI�ⲿGPIO�жϳ�ʼ��
*  ����˵����PORTx       �˿ںţ�PORTA,PORTB,PORTC,PORTD,PORTE��
*            n           �˿�����
*            exti_cfg    ����ѡ�����������ѡ��
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע��
*************************************************************************/
uint8 k;
void  exti_init(PORTx portx, u8 n, exti_cfg cfg)
{
    SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << portx);    //����PORTx�˿�

    PORT_PCR_REG(PORTX[portx], n) = PORT_PCR_MUX(1) | PORT_PCR_IRQC(cfg & 0x7f ) | PORT_PCR_PE_MASK | ((cfg & 0x80 ) >> 7); // ����GPIO , ȷ������ģʽ ,������������������
    GPIO_PDDR_REG(GPIOx[portx]) &= ~(1 << n);       //����ģʽ
    enable_irq(portx + 87);                         //ʹ��PORT�жϣ�PORTA��ISR�жϺ�Ϊ87
}


/*************************************************************************
*                             ��Ұ�ʿ
*                              freescale���ƽ����
*  �������ƣ�key_init
*  ����˵����������ʼ��
*  KEY1 PTC8   KEY2  PTC14
*  �������أ���
*  �޸�ʱ�䣺2013-4-2
*  ��    ע��
*************************************************************************/
void key_init(void)
{
  PORT_PCR_REG(PORTX[PORTC], 6) = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // GPIO���� , �ڲ�����
  PORT_PCR_REG(PORTX[PORTC], 14) = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // GPIO���� , �ڲ�����
  GPIO_PDDR_REG(GPIOx[PORTC]) &= ~(1 <<6);    //  ȷ������Ϊ����
  GPIO_PDDR_REG(GPIOx[PORTC]) &= ~(1 << 14);    // ȷ������Ϊ����
}
/*************************************************************************
*                             ��Ұ�ʿ
*                              freescale���ƽ����
*  �������ƣ�key1  key2
*  ����˵��������ɨ��
*  KEY1 PTC8   KEY2  PTC14
*  �������أ���
*  �޸�ʱ�䣺2013-4-2
*  ��    ע��
*************************************************************************/
void key1(void)
{ 
  if(GPIO_Get(PORTC,6)==0)
    delayms(30);
  if(GPIO_Get(PORTC,6)==0)
  {
    while(!(GPIO_Get(PORTC,6)));
          k=1;
  }
}
void key2(void)
{ 
  if(GPIO_Get(PORTC,14)==0)
    delayms(30);
  if(GPIO_Get(PORTC,14)==0)
  {
    while(!(GPIO_Get(PORTC,14)));
          LED_turn(LED3);
  }
} 
