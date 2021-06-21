/**
  ******************************************************************************
  * @file    hw_config.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Hardware Configuration & Setup
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/

#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_istr.h"
#include "hw_config.h"
#include "usb_pwr.h" 
#include "usart.h"  
#include "string.h"	
#include "stdarg.h"		 
#include "stdio.h"	

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
_usb_usart_fifo uu_txfifo;			//USB���ڷ���FIFO�ṹ�壬��hw_config.h����
 
u8  USART_PRINTF_Buffer[USB_USART_REC_LEN];//usb_printf���ͻ�����

//�����ƴ���1������ͨ�����飩�������ݵķ��� ������USB���⴮�ڽ��ܵ�������
u8 USB_USART_RX_BUF[USB_USART_REC_LEN]; //���ܻ���,���USART_REC_LEN���ֽ�

u16 USB_USART_RX_STA=0;       		

extern LINE_CODING linecoding;		//USB���⴮��������Ϣ(������ λ��) ��usb_prop.c����

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : Set_System
* Description    : Configures Main system clocks & power
* Input          : None.
* Return         : None.
*******************************************************************************/
//USB�����жϷ�����
void USBWakeUp_IRQHandler(void) 
{
	EXTI_ClearITPendingBit(EXTI_Line18);//���USB�����жϱ�־λ
} 
//USB�жϴ�����
void USB_LP_CAN1_RX0_IRQHandler(void) 
{
	USB_Istr();
} 

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz)
* Input          : None.
* Return         : None.
*******************************************************************************/
//USBʱ�����ú���,USBclk=48Mhz@HCLK=72Mhz
void Set_USBClock(void)
{
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);	//USBclk=PLLclk/1.5=48Mhz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);	 //USBʱ��ʹ��
} 

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
 	printf("usb enter low power mode\r\n");
	bDeviceState=SUSPENDED;//bDeviceState��¼USB����״̬,��usb_pwr.c���涨��
} 

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
	DEVICE_INFO *pInfo=&Device_Info;
	printf("leave low power mode\r\n"); 
	if (pInfo->Current_Configuration!=0)bDeviceState=CONFIGURED; 
	else bDeviceState = ATTACHED; 
} 


/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{ 	
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure; 
	/* Configure the EXTI line 18 connected internally to the USB IP */
	EXTI_ClearITPendingBit(EXTI_Line18);		//  ��������18�ϵ��ж�
	EXTI_InitStructure.EXTI_Line = EXTI_Line18; 	// USB resume from suspend mode
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//line 18��ʱ�������ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 	

	/* Enable the USB interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;//��2,���ȼ���֮
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USB Wake-up interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;   //��2,���ȼ����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&NVIC_InitStructure);  	
}

/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable
* Input          : None.
* Return         : Status
*******************************************************************************/
//USB�ӿ�����(����1.5K��������,ALIENTEK��M3ϵ�п�����,����Ҫ����,�̶�����������)
//NewState:DISABLE,������,ENABLE,����
void USB_Cable_Config (FunctionalState NewState)
{ 
	if (NewState!=DISABLE)printf("usb pull up enable\r\n"); 
	else printf("usb pull up disable\r\n"); 
}


//USBʹ������/����   enable:0,�Ͽ�;1,��������	
void USB_Port_Set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //ʹ��PORTAʱ��	 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//�˳��ϵ�ģʽ
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  //�ϵ�ģʽ
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		PAout(12)=0;	    		  
	}
} 


/*******************************************************************************
* Function Name  :  USART_Config.
* Description    :  Configure the EVAL_COM1 according to the line coding structure.
* Input          :  None.
* Return         :  Configuration status
                    TRUE : configuration done with success
                    FALSE : configuration aborted.
*******************************************************************************/
//USB COM�ڵ�������Ϣ,ͨ���˺�����ӡ����
bool USART_Config(void)
{
	uu_txfifo.readptr=0;	//��ն�ָ��
	uu_txfifo.writeptr=0;	//���дָ��
	USB_USART_RX_STA=0;		//USB USART����״̬����
	printf("linecoding.format:%d\r\n",linecoding.format);
  	printf("linecoding.paritytype:%d\r\n",linecoding.paritytype);
	printf("linecoding.datatype:%d\r\n",linecoding.datatype);
	printf("linecoding.bitrate:%d\r\n",linecoding.bitrate);
	return (TRUE);
} 

/*******************************************************************************
* Function Name  : USB_To_USART_Send_Data.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
* Return         : none.
*******************************************************************************/
//�����USB���⴮�ڽ��յ������� ����:databuffer:���ݻ�����,Nb_bytes:���յ����ֽ���
void USB_To_USART_Send_Data(u8* data_buffer, u8 Nb_bytes)
{ 
    u8 i; u8 res;
    for(i=0;i<Nb_bytes;i++)
    {  
        res=data_buffer[i]; 
        if((USB_USART_RX_STA&0x8000)==0)	//����δ���
        {
            if(USB_USART_RX_STA&0x4000)	//���յ���0x0d
            {
                 if(res!=0x0a)USB_USART_RX_STA=0;	//�������¿�ʼ
                 else USB_USART_RX_STA|=0x8000;	//���������
             }else //��û�յ�0X0D
             {	
                  if(res==0x0d)USB_USART_RX_STA|=0x4000;//��ǽ��յ���0X0d
                  else
                  {       	          
                        USB_USART_RX_BUF[USB_USART_RX_STA&0X3FFF]=res;USB_USART_RX_STA++; 	   
                        if(USB_USART_RX_STA>(USB_USART_REC_LEN-1))USB_USART_RX_STA=0;//��������
                   }					
             }
         }   
     }
}

//����һ�ֽ����ݵ�USB���⴮��
//����ʵ����ֻд�˷��͵�FIFO ���ջ�����EP1_IN_Callbackʵ�������USB
void USB_USART_SendData(u8 data)
{
	uu_txfifo.buffer[uu_txfifo.writeptr]=data;
	uu_txfifo.writeptr++;
	if(uu_txfifo.writeptr==USB_USART_TXFIFO_SIZE)//����buf��С��,����.
	{
		uu_txfifo.writeptr=0;
	} 
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

  Device_Serial0 = *(uint32_t*)ID1;
  Device_Serial1 = *(uint32_t*)ID2;
  Device_Serial2 = *(uint32_t*)ID3;  

  Device_Serial0 += Device_Serial2;

  if (Device_Serial0 != 0)
  {
    IntToUnicode (Device_Serial0, &Virtual_Com_Port_StringSerial[2] , 8);
    IntToUnicode (Device_Serial1, &Virtual_Com_Port_StringSerial[18], 4);
  }
}

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;
  
  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2* idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2* idx] = (value >> 28) + 'A' - 10; 
    }
    
    value = value << 4;
    
    pbuf[ 2* idx + 1] = 0;
  }
}
//usb���⴮��,printf����
//ȷ��һ�η������ݲ�����USB_USART_REC_LEN�ֽ�
void usb_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART_PRINTF_Buffer,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART_PRINTF_Buffer);//�˴η������ݵĳ���
	for(j=0;j<i;j++)//ѭ����������
	{
		USB_USART_SendData(USART_PRINTF_Buffer[j]); 
	}
} 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
