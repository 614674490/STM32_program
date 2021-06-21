/******************** ��Ұ�ʿ ********************
 * �ļ���       ��AT24C02.c
 * ����         ��AT24C02оƬ������������
 *
 * ʵ��ƽ̨     ��LQ K60������
 *                SCL PTD4  SDA  PTD6
 *
 * ����          DAQI
**********************************************************************************/


#ifndef _AT24C02_H_
#define _AT24C02_H_

#define  SDA_OUT()  GPIO_PDDR_REG(GPIOx[PORTD]) |= (1 <<6)
#define  SDA_IN()   PORT_PCR_REG(PORTX[PORTD], 6) |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; GPIO_PDDR_REG(GPIOx[PORTD]) &= ~(1 <<6)
#define  IIC_SDA_L  GPIO_SET(PORTD,6,0)
#define  IIC_SDA_H  GPIO_SET(PORTD,6,1)
#define  IIC_SCL_L  GPIO_SET(PORTD,4,0)
#define  IIC_SCL_H  GPIO_SET(PORTD,4,1)
#define  READ_SDA   GPIO_Get(PORTD,6)


void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
uint8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(uint8 txd);
u8 IIC_Read_Byte(unsigned char ack);
void AT24CXX_Init(void);
uint8 AT24CXX_ReadOneByte(uint16 ReadAddr);
void AT24CXX_WriteOneByte(uint16 WriteAddr,uint8 DataToWrite);
void AT24CXX_WriteLenByte(uint16 WriteAddr,uint32 DataToWrite,u8 Len);
uint32 AT24CXX_ReadLenByte(uint16 ReadAddr,u8 Len);
uint8 AT24CXX_Check(void);

#endif  //_AT24C02_H_