/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��delay.h
 * ����         ��ģ����ʱ����ͷ�ļ�
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/


#ifndef __DELAY_H__
#define __DELAY_H__

#include "common.h"

void  delayms(uint32  ms);
void  delay_2us(void);//��ʱ2us
void  delay_1us(void);//��ʱ1us
void SamplingDelay(void);
void  delayus(void);

#endif