#ifndef _usart2_h
#define _usart2_h
#include "sys.h"

#define USART2_MAX_RECV_LEN		200					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		200					//����ͻ����ֽ���
#define USART2_RX_EN 			1					//0,������;1,����.

extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern u16 USART2_RX_STA;   						//��������״̬

void USART2_Init(u32 bound);				//����2��ʼ�� 
void TIM2_Set(u8 sta);
void TIM2_Init(u16 arr,u16 psc);
void USART2_SendByte(u8 Data);
void USART2_Write(u8* data,u16 len);
void SendAT(u8 *dat,u16 num);
void SendATData(u8 *dat);

#endif











