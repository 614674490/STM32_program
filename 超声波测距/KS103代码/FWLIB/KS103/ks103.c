#include "ks103.h"
#include "iic.h"
#include "delay.h"
#include "usart2.h"

void Ks103_Init(void)
{
	IIC_Init();
}
/*************************MODE���� IICģʽ*******************/
//KS103д����
//������ַ
//�Ĵ�����ַ
//�����ֽ�
void Ks103_Write_byte(u8 SlaveAddress,u8 ResAddress,u8 command)
{
	  IIC_Start();                   
    IIC_Send_Byte(SlaveAddress);  
 
    while(IIC_Wait_Ack());
 
    IIC_Send_Byte(ResAddress);   
 
    while(IIC_Wait_Ack());                          
                                  
    IIC_Send_Byte(command);      
 
    while(IIC_Wait_Ack());                                
    IIC_Stop();                    
}

//KS103������
//���ض�ȡ����  16λ����
u8 Ks103_Read_byte(u8 SlaveAddress,u8 ResAddress)
{
	  u8 data=0;
	  IIC_Start();    
    IIC_Send_Byte(SlaveAddress);    
 
    while(IIC_Wait_Ack());
    IIC_Send_Byte(ResAddress);
 
    while(IIC_Wait_Ack());                        
    IIC_Start();
    IIC_Send_Byte(SlaveAddress+1);   
     
    while(IIC_Wait_Ack());
 
    delay_us(50);
 
    data=IIC_Read_Byte(0);
 
    IIC_Stop();  
     
    return data;
}


//�ı�������ַ
void Change_Addr(u8 OldAdddr,u8 NewAddr)
{ 
    delay_ms(2000);
    Ks103_Write_byte(OldAdddr,0x02,0x9a);             //??????0x00;
    delay_ms(1);
    Ks103_Write_byte(OldAdddr,0x02,0x92);
    delay_ms(1);
    Ks103_Write_byte(OldAdddr,0x02,0x9e);
    delay_ms(1);
    Ks103_Write_byte(OldAdddr,0x02,NewAddr);
    delay_ms(500);
}

//��ȡ����  mm   0xe8 0x02 0xb0/0xb4
//                        �����¶Ȳ��� ���¶Ȳ���  0-5m
u32 Read_Ks103_Data(u8 SlaveAddress,u8 command)
{
	u32 distance=0;
	int count=800;
	Ks103_Write_byte(SlaveAddress,0x02,command);
	//delay_ms(1);                                        //��ȫ��ʱ  �����¶Ȳ���̽��
	delay_ms(90);                                       //���¶Ȳ���̽��
	while(--count||!SCL)                   //ͨ����ѯSCL��״̬������ʶ��̽���Ƿ����
	{
		;
	}
	distance=Ks103_Read_byte(SlaveAddress,0x02);
  distance<<=8;
  distance+=Ks103_Read_byte(SlaveAddress,0x03);
	return distance;
}

float Get_Data(u32 data,u8 n)       //�˲��������
{
	u8 i;
	u32 sum=0;
	float value;
	for(i=0;i<n;i++) 
	{
		data=Read_Ks103_Data(SlaveAddress1,Notemp0_5m);             //�����¶Ȳ���
		sum+=data;
	}
	value=sum/n;
	return value;
}


/*************************MODE��GND ����ģʽ*******************************/
void Send_Command(u8 command)
{
	USART2_SendByte(SlaveAddress1);   //����Ĭ��������ַ
	delay_us(80);               //��ʱ20-100us
	USART2_SendByte(0x02);         //���ͼĴ���2�ĵ�ַ
	delay_us(80);
	USART2_SendByte(command);
	delay_ms(90);                    //��ʱ80ms �ȴ�����̽�����
}




