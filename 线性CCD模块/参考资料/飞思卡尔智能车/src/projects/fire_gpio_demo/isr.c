/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.c
 * ����         ���жϴ�������
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
*�������ƣ�PIT0_IRQHandler
*�������ڲⶨ׼ȷ��ʱ
*��Ҫ���ڲⶨһ�γ����ִ��ʱ��
����PIT_LDVAL��ʼֵ  PIT_CVALʵ��ֵ�� ��ֵ��PIT_LDVAL�𽥵ݼ�   32 λ
**************************************************************************/

uint16 time;
uint16 time1,time2;
uint16 ge;
void PIT0_IRQHandler(void)
{
   CarControl();
   PIT_Flag_Clear(PIT0);
}

/*************************************************************************
*�������ƣ�NRF24L01_IRQHandler
*����:��������ģ�����ģʽ���ж϶�ȡ����ֵ

**************************************************************************/         
void NRF24L01_IRQHandler(void)
{
  PORTE_ISFR |= (1<<25);
  uint8 sta;
  sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ
  NRF24L01_Write_Reg(NRF24L01_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־ 
//  if(sta&RX_OK)//���յ�����
//  {
//	NRF24L01_Read_Buf(NRF24L01_RD_RX_PLOAD,R_tmp_buf,RX_PLOAD_WIDTH);//��ȡ����
//	NRF24L01_Write_Reg(NRF24L01_FLUSH_RX,0xff);//���RX FIFO�Ĵ���
//  //      LED_turn(LED3);
//  }
}

