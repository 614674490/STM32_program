/******************** 唐野岐士 ********************
 * 文件名       ：AT24C02.c
 * 描述         ：AT24C02芯片操作函数定义
 *
 * 实验平台     ：LQ K60开发板
 *                SCL PTD4  SDA  PTD6
 *
 * 作者          DAQI
**********************************************************************************/
#include "common.h"
#include "include.h"

//初始化IIC
void IIC_Init(void)
{					     
 	PORT_PCR_REG(PORTX[PORTD], 4) = PORT_PCR_MUX(1);
        GPIO_PDDR_REG(GPIOx[PORTD]) |= (1 <<4);    //  确定引脚为输出
        PORT_PCR_REG(PORTX[PORTD], 6) = PORT_PCR_MUX(1);
        GPIO_PDDR_REG(GPIOx[PORTD]) |= (1 <<6);    //  确定引脚为输出
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_2us();
        delay_2us();
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_2us();
        delay_2us();
	IIC_SCL_L;//钳住I2C总线，准备发送或接收数据 
}
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_2us();
        delay_2us();
	IIC_SCL_H; 
	IIC_SDA_H;//发送I2C总线结束信号
	delay_2us();
        delay_2us();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8 IIC_Wait_Ack(void)
{
	uint8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
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
	IIC_SCL_L;//时钟输出0 	   
	return 0;  
} 

//产生ACK应答
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
//不产生ACK应答		    
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
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uint8 txd)
{                        
    uint8 t;   
    SDA_OUT(); 	    
    IIC_SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {      
        if((txd&0x80)<<7)
        IIC_SDA_H;
        else
        IIC_SDA_L;  
        txd<<=1; 	  
        delay_2us();   //对TEA5767这三个延时都是必须的
	IIC_SCL_H;
        delay_2us(); 
	IIC_SCL_L;	
	delay_2us();
    }	 
} 
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA设置为输入
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
    IIC_NAck();//发送nACK
    else
    IIC_Ack(); //发送ACK   
    return receive;
}
//初始化IIC接口
void AT24CXX_Init(void)
{
	IIC_Init();
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
uint8 AT24CXX_ReadOneByte(uint16 ReadAddr)
{				  
    uint8 temp=0;		  	    																 
    IIC_Start();  
    IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	   
    IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //发送低地址
    IIC_Wait_Ack();	    
    IIC_Start();  	 	   
    IIC_Send_Byte(0XA1);           //进入接收模式			   
    IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件	    
    return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(uint16 WriteAddr,uint8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
    IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 	 
    IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //发送低地址
    IIC_Wait_Ack(); 	 										  		   
    IIC_Send_Byte(DataToWrite);     //发送字节							   
    IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
    delayms(10);	 
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(uint16 WriteAddr,uint32 DataToWrite,u8 Len)
{  	
	uint8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}
//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
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
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
uint8 AT24CXX_Check(void)
{
	uint8 temp;
	temp=AT24CXX_ReadOneByte(255);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
	AT24CXX_WriteOneByte(255,0X55);
	temp=AT24CXX_ReadOneByte(255);	  
	if(temp==0X55)return 0;
	}
	return 1;											  
}