#ifndef _spi_h
#define _spi_h
#include "sys.h"
#include "stm32f10x_spi.h"


void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�


#endif


