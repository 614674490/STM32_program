#ifndef _usart2_h
#define _usart2_h
#include "sys.h"

#define USART2_REC_LEN  200  	//�����������ֽ��� 200
extern u8  USART2_RX_BUF[USART2_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�
extern u16 USART2_RX_STA;         		//����״̬���	 0-14λΪ�����ֽ�����15λ������ɱ�־λ
extern u16 len;
extern u8 flag;
void usart2_init(u32 bound);

#endif


