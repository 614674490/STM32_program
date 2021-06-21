/**************************************************************************
 ** �������ڣ�  2012-11-2                                                 *
 ** �ļ���  ��  isr.c                                                     *
 ** �汾    ��	                                                          *
 ** ƽ̨    ��  ����������MK60DN512ZVLQ10��Сϵͳ��                       *
 ** �����б�	                                                          *
 ** ����������  OV7620����ͷ���ݲɼ�                                      *
 ** ������  ��  ���������� yullion.taobao.com                                                *
 ** �޸���ʷ��                                                            *
 ** @��Ȩ���У� ���������� yullion.taobao.com                                                *
 ** �Ա��꣺    yullion.taobao.com                                        *
 **************************************************************************/

/*******************************************************************************************
��ӭ�����Ա���  ����������  yullion.taobao.com
K60�Ա�����     http://item.taobao.com/item.htm?spm=a1z10.1.w4.18.rMwvaU&id=21039172293
********************************************************************************************/

#include "common.h"
#include "include.h"
#include "isr.h"
#include "dma.h"
#include "calculation.h"

u8 TIME0flag_5ms  = 0 ;
u8 TIME0flag_10ms = 0 ;
u8 TIME0flag_15ms = 0 ;
u8 TIME0flag_20ms = 0 ;
u8 TIME0flag_80ms = 0 ; 
u8 TIME1flag_20ms = 0 ;
u8 TIME1flag_1ms  = 0 ;
u8  TimeCount = 0 ;
int zhilitime_count=0  ;
u8 zhili_flag=1;

u8 TIME0flag_d1ms  = 0 ;
u8 TIME0flag_d2ms  = 0 ;
u8 TIME0flag_d3ms  = 0 ;
u8 TIME0flag_d4ms = 0 ;
u8 TIME0flag_d5ms = 0 ;
//u8 TIME0flag_20ms = 0 ;

int countl;
int countr;

extern int     g_nSpeedControlPeriod;
extern int g_nDirectionControlPeriod;
extern int dier_count_period;

volatile u8  pit_flag = 0;
volatile u32 dma_int_count = 0;

/******************************************************************************/
unsigned char Pix_Data[V][H] = {0};                                     //�ɼ����� ���е�ͼ������
unsigned char V_Cnt=0;                                                  //�вɼ�����
unsigned char Is_SendPhoto=0;                                           //ͼ���ͱ�־
unsigned char FieldCounter=1;                                           //�ж���ż��
/******************************************************************************/
#ifdef TIAOSHI    //����ģʽ
//���ڵ���ʱִ�еĳ���Σ����ͳ����е�ͼ������
/*************************************************************************
*  �������ƣ�DMA_CH4_Handler
*  ����˵����DMAͨ��4���жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺
*  ��    ע��
*************************************************************************/

void DMA_CH4_Handler(void)
{
//DMA_IRQ_CLEAN(DMA_CH4);                                 //���ͨ�������жϱ�־λ    (���������ٴν����ж�)
 //DMA_DIS(DMA_CH4);                                       //�ɼ���H�����ݺ�������DMA�жϣ�ֹͣDMA���䡣���ж��д�DMA����

    //���ڵ����õ�
    //if(V_Cnt == 160)
     // Is_SendPhoto = 1;
}
   
/************************************************************************/
//�������
//���жϴ�����
void PORTA_IRQHandler()
{
   extern u8 Camera_Flag;
   u8 n;
       n = 10;
    if(PORTA_ISFR & (1 << n))         //PTA10�����ж�
    {
        PORTA_ISFR  |= (1 << n);        //д1���жϱ�־λ
        countl++;
    }
    n = 12;
    if(PORTA_ISFR & (1 << n))         //PTA11�����ж�
    {
        PORTA_ISFR  |= (1 << n);        //д1���жϱ�־λ
        countr++;
    }
 
      
}

//���жϴ�����
void PORTB_IRQHandler()
{
  extern u8 Camera_Flag;
if(PORTB_ISFR & (1<<0))                                 //PTB0�����ж�,���ж�
    {
      
        PORTB_ISFR  = ~0;  
      if(Camera_Flag==1)
      {
        DMA_DADDR(DMA_CH4)=(u32)Pix_Data;
          DMA_EN(DMA_CH4);
          
        PORTA_ISFR  = ~0; 
         Camera_Flag=0;
      
      //DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTD_BYTE0_IN, Pix_Data, PTC0, DMA_BYTE1,H, DMA_rising_keepon); 
        //DMAͨ��4��ʼ����PTC0�����ش���DMA���䣬Դ��ַΪPTD_BYTE0_IN��Ŀ�ĵ�ַΪ��Pix_Data ��ÿ�δ���1Byte������H�κ�ֹͣ���䣬Ŀ�ĵ�ַ���ֲ��䣬�ر�ͨ��CHn Ӳ������
        enable_irq(87);   //ʹ�����ж�				//���ͼ��ɼ���
       disable_irq(88);  
         V_Cnt=0;                                           //�вɼ���������
      }
      
      else if (Camera_Flag== 0)
         {
           disable_irq(87);
           disable_irq(88);
           Camera_Flag=0;
         }
     //ż�� 
    }
      
      
  
      
      
      
      /************************************************************************/
    }


#endif










/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�PIT0_IRQHandler
*  ����˵����PIT0 ��ʱ�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-18    �Ѳ���
*  ��    ע��
*************************************************************************/


extern int zhijiao_2ms_nb;
int zhijiao_count;
void PIT0_IRQHandler(void)
{
  static u8 TimeCount ; 
  static unsigned char TimerCnt20ms = 0;
  PIT_Flag_Clear(PIT0);       //���жϱ�־λ
  extern u8 IntegrationTime ;             //�ع�ʱ��
  extern void StartIntegration(void);   
  if(zhijiao_2ms_nb)
  {
    zhijiao_count++;   
  }
 // static unsigned char TimerCnt20ms = 0;
  u8 integration_piont;

  TIME1flag_1ms = 1 ;
   
  TimerCnt20ms++;

 //IntegrationTime=19;
  integration_piont = 10 - IntegrationTime; 
  if(integration_piont >= 2) {      /* �ع�ʱ��С��2�򲻽������ع� */
      if(integration_piont == TimerCnt20ms)

      StartIntegration();//�ع⿪ʼ
 

  /* �����ع�ʱ�����20ms�����ڵ��ع��*/
 
        

  }
  if(TimerCnt20ms >= 20) {
    TimerCnt20ms = 0;
    TIME1flag_20ms = 1;
  }
  
  
  
  
  
  TimeCount ++ ;
  if(zhili_flag==1)
  {
  zhilitime_count++;
  }
  //TimerCnt20ms++ ; 


  
  
  
  if(TimeCount>= 5 )
   {
 
     TIME0flag_d5ms = 1;

     // if(g_nDirectionControlPeriod>=10)
     //  g_nDirectionControlPeriod=0;
   
     TimeCount = 0;

 } 
  
   
   
   else if(TimeCount ==1 ){
     
     TIME0flag_d1ms = 1;
     
     

 } 
   
   
   
   
   else if(TimeCount ==2 ){
     
     //g_nDirectionControlPeriod=g_nDirectionControlPeriod+5;
     //Direct_output();
     
     TIME0flag_d2ms = 1;

  } 
   else if(TimeCount ==3 ){
     TIME0flag_d3ms = 1;
     
  }
  else if(TimeCount ==4 ){
     TIME0flag_d4ms = 1;
  }
  


   
}

void FTM0_IRQHandler()
{
  
  extern u16 bianmaqi_count;
uint8 Status;
Status=FTM0_STATUS;
FTM1_STATUS=0x00;//���жϱ�־λ
bianmaqi_count++;
}



void DMA_CH0_Handler(void)
{

    //DMAͨ��0
    printf("DMA_CH0_Handler\n");
    DMA_IRQ_CLEAN(DMA_CH0);                             //���ͨ�������жϱ�־λ    (���������ٴν����ж�)
    DMA_EN(DMA_CH0);                                    //ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����)

}

/*************************************************************************
*                             ����Ƕ��ʽ����������
*
*  �������ƣ�PIT1_IRQHandler
*  ����˵����PIT1��ʱ�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-9-18    �Ѳ���
*  ��    ע��
*************************************************************************/
void PIT1_IRQHandler(void)
{
   PIT_Flag_Clear(PIT1);       //���жϱ�־λ
    disable_irq(69);            //PIT1
    disable_irq(87);            //PORTA
    extern short int vlnow;
    extern short int vrnow;
    vlnow=(short int)(countl);
    vrnow=(short int)(countr);
    extern int16 Vnow;
    Vnow=(vlnow+vrnow)>>1;
    countl=0;countr=0;
 //   E6A2_debug_PrinttoScreen();
 //   bt_debug_speed();
    speedCorr_PID();
    enable_irq(87);             //PORTA
    enable_irq(69);             //PIT1
  

}



extern float DIR_CONTROL_P;
extern float DIR_CONTROL_D;

u8 Rx_Count=0;
u8 Rx_Buff[20];
void USART2_IRQHandler()
{
  u8 i=0;u8 tmp;
  float j = 1.0;float temp=0;
  extern int16 VS;
  uart_irq_DIS(UART2);
 // DIR_CONTROL_P=
  tmp = uart_getchar(UART2);
  if(tmp != '/')
  {
    Rx_Buff[Rx_Count] = tmp;
    Rx_Count++;
  }else
  {
    Rx_Buff[Rx_Count] = '/';
    
    /*START*/
    i=0;
    while(!((Rx_Buff[i]>='0')&&(Rx_Buff[i]<='9')))i++;
    temp = Rx_Buff[i] - '0';i++;
    while((Rx_Buff[i]!='/') && (i<10))
    {
      
      if(Rx_Buff[i]=='.')
        j=0.1;
      else
      {
        if(j!=1.0)
        {
          temp = temp + (Rx_Buff[i] - '0') * j;
          j=j*0.1;
        }
        else
          temp = temp * 10 + Rx_Buff[i] - '0';
      }
      i++;
      
    }
    if(Rx_Buff[0]=='P')
      DIR_CONTROL_P = temp * (-1);
    if(Rx_Buff[0]=='D')
      DIR_CONTROL_D = temp *(-1);
    if(Rx_Buff[0]=='V')
      VS = (int16)temp;
    
    
    /*END*/
    Rx_Count = 0;
    uart_sendStr(UART2, Rx_Buff);
    memset(Rx_Buff, 0, sizeof(Rx_Buff));
    printf("%lf\r\n",0.5);
  }
  

uart_irq_EN(UART2);
}