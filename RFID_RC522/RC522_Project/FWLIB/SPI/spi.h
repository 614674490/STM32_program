#ifndef _spi_h
#define _spi_h
#include "sys.h"
#include "stm32f10x_spi.h"


void SPI2_Init(void);			 //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI总线读写一个字节


#endif


