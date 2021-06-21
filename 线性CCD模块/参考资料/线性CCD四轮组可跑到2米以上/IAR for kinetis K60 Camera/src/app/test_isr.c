/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.c
 * ����         ���жϴ�������
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/



#include "common.h"
#include "include.h"
#include "DMA.h"
#include "SCI.h"
#include <stdbool.h>
volatile u16 Vnum=0;
void USART4False_IRQHandler()
{
  uart_putchar(UART4,0xbb);
  uart_putchar(UART4,0xbb);
}

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�HardFault_Handler
*  ����˵����Ӳ���Ϸ��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-4    �Ѳ���
*  ��    ע��������LED��˸��ָʾ������Ӳ���Ϸ�
*************************************************************************/
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****Ӳ���Ϸô���!!!*****\r\n\n");
    }
}



void USART4_IRQHandler(void)
{
	
	static int i;
	bool  frame_flag=0;
	unsigned char sci_temp;
        DisableInterrupts;
	sci_temp=uart_getchar(UART4);
	 if(frame_flag)
		{
			sci_indata[i++]=sci_temp;
		}
		if(sci_temp==0x7b)//7b={
		{
			frame_flag=1;
			i=0;
		}
		if(sci_temp==0x7d)//7d=}
		{
			frame_flag=0;
			i=0;
			sci_inprocess();
		}
         EnableInterrupts;
}

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�PORTA_IRQHandler
*  ����˵����PORTA�˿��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�Լ���ʼ�������
*************************************************************************/
void PORTA_IRQHandler()
{
    u8  n = 0;    //���ź�
	
	//static u8  imagerow=0; //����Ҫ�����������CAMERA_H9
        static u16 row=0; //��¼���ڵ�����
    /*==============================================================================
	ע�⣺
		���жϷ������ж�ǰ�棬�����ȼ��������жϡ�
		���ж��û������ȫ����return��ȷ�����������жϵ��û�����
	
	==============================================================================*/
    n = 27;											//���ж�
    if(PORTA_ISFR & (1 << n))           			//PTA27�����ж�
    {
        
        /*  ����Ϊ�û�����  */
		
		//���ж���Ҫ�ж��ǳ��������ǳ���ʼ
		if(img_flag == IMG_START)					//��Ҫ��ʼ�ɼ�ͼ��
		{
			DMA_DADDR(CAMERA_DMA_CH)= (u32)IMG_BUFF;//���ϻָ�Ŀ�ĵ�ַ
			DMA_EN(CAMERA_DMA_CH);            		//ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����)
                      
		}
        PORTA_ISFR  = ~0;        			        //���ж��ȫ����Ҫ���жϱ�־λ
		return;										//���жϴ����ˣ��Ͳ���Ҫ�������ж�
		
        /*  ����Ϊ�û�����  */
    }
	
    //==============================================================================
    if(img_flag != IMG_GATHER)						//ֻ��ͼ���ڲɼ��У��Ŵ������ж�
	{
                PORTA_ISFR  = ~0;  
		return;
	}

    
    n = 26;
    if(PORTA_ISFR & (1 << n))                       //PTA26�������ж�
    {
        PORTA_ISFR  = ~0;        			//д1���жϱ�־λ
        /*  ����Ϊ�û�����  */
        
#if CAMERA_DMA_ERROR
			DMA_DADDR(CAMERA_DMA_CH)  +=  CAMERA_DMA_ERROR ;		//���ϻָ�Ŀ�ĵ�ַ
#endif
	if(row<=CAMERA_H)//row==data_table[imagerow])//�����ǰ������Ӧ�òɼ�
         {
	    DMA_EN(CAMERA_DMA_CH); //ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����)
            //imagerow++;
         } 
        else
        {
          DMA_DIS(CAMERA_DMA_CH);            		//��ֹͨ��Ӳ��DMA����
                       
			disable_irq(87); 						//�ر�PTA���ж�
                        img_flag = IMG_FINISH;//���ͼ��ɼ����
                        row=0;
        }
     
        row++;
		
       /*  ����Ϊ�û�����  */
    }
    
    PORTA_ISFR  = ~0;        			//д1���жϱ�־λ
}



/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�PIT0_IRQHandler
*  ����˵����PIT0 ��ʱ�жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-18    �Ѳ���
*  ��    ע��
*************************************************************************/
void PIT0_IRQHandler(void)
{
        sent_frame(1000,0x06,0xa1,0xaa);
	Site_type site={10,70};
	//disable_irq(87); 							//�ر�PTA���ж�
	LCD_Num_8x16_C(site,Vnum,BLUE,RED);		//��ʾʵ�ʲɼ�������
	Vnum=0;
	//enable_irq(87); 							//����PTA���ж�
    PIT_Flag_Clear(PIT0);       				//���жϱ�־λ
	
}

