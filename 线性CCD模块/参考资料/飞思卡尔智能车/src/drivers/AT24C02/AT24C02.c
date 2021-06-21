/******************** ��Ұ�ʿ ********************
 * �ļ���       ��AT24C02.c
 * ����         ��AT24C02оƬ������������
 *
 * ʵ��ƽ̨     ��LQ K60������
 *                SCL PTD4  SDA  PTD6
 *
 * ����          DAQI
**********************************************************************************/
#include "common.h"
#include "include.h"

//��ʼ��IIC
void IIC_Init(void)
{					     
 	PORT_PCR_REG(PORTX[PORTD], 4) = PORT_PCR_MUX(1);
        GPIO_PDDR_REG(GPIOx[PORTD]) |= (1 <<4);    //  ȷ������Ϊ���
        PORT_PCR_REG(PORTX[PORTD], 6) = PORT_PCR_MUX(1);
        GPIO_PDDR_REG(GPIOx[PORTD]) |= (1 <<6);    //  ȷ������Ϊ���
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_2us();
        delay_2us();
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_2us();
        delay_2us();
	IIC_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
}
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_2us();
        delay_2us();
	IIC_SCL_H; 
	IIC_SDA_H;//����I2C���߽����ź�
	delay_2us();
        delay_2us();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8 IIC_Wait_Ack(void)
{
	uint8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	delay_1us();	   
	IIC_SCL_H;
        delay_1us();
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;//ʱ�����0 	   
	return 0;  
} 

//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_L;
	delay_2us();
	IIC_SCL_H;
	delay_2us();
	IIC_SCL_L;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;
	delay_2us();
	IIC_SCL_H;
	delay_2us();
	IIC_SCL_L;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(uint8 txd)
{                        
    uint8 t;   
    SDA_OUT(); 	    
    IIC_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {      
        if((txd&0x80)<<7)
        IIC_SDA_H;
        else
        IIC_SDA_L;  
        txd<<=1; 	  
        delay_2us();   //��TEA5767��������ʱ���Ǳ����
	IIC_SCL_H;
        delay_2us(); 
	IIC_SCL_L;	
	delay_2us();
    }	 
} 
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
        delay_2us();
	IIC_SCL_H;
        receive<<=1;
        if(READ_SDA)receive++;   
	delay_1us(); 
    }					 
    if (!ack)
    IIC_NAck();//����nACK
    else
    IIC_Ack(); //����ACK   
    return receive;
}
//��ʼ��IIC�ӿ�
void AT24CXX_Init(void)
{
	IIC_Init();
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
uint8 AT24CXX_ReadOneByte(uint16 ReadAddr)
{				  
    uint8 temp=0;		  	    																 
    IIC_Start();  
    IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	   
    IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
    IIC_Wait_Ack();	    
    IIC_Start();  	 	   
    IIC_Send_Byte(0XA1);           //�������ģʽ			   
    IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
    return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(uint16 WriteAddr,uint8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
    IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 	 
    IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
    IIC_Wait_Ack(); 	 										  		   
    IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
    IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
    delayms(10);	 
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(uint16 WriteAddr,uint32 DataToWrite,u8 Len)
{  	
	uint8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}
//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
uint32 AT24CXX_ReadLenByte(uint16 ReadAddr,u8 Len)
{  	
	uint8 t;
	uint32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
uint8 AT24CXX_Check(void)
{
	uint8 temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
	AT24CXX_WriteOneByte(255,0X55);
	temp=AT24CXX_ReadOneByte(255);	  
	if(temp==0X55)return 0;
	}
	return 1;											  
}