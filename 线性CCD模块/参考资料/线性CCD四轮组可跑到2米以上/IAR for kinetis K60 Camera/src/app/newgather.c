

#include "common.h"
#include "include.h"
#include "sci.h"
#include "DMA.h"
u8 img_bin_buff[CAMERA_H][CAMERA_W]; //ͼ����λ��


void main(void)
{
        unsigned int  i,j;
	         					//��ʼ�������ñ���Ϊ��ɫ
	Ov7725_Init((u8 *)img_bin_buff);          	//����ͷ��ʼ��
        sci_init(UART4);
       // LED_init();
        for(i=0;i<CAMERA_H;i++)
  {
           for(j=0;j<CAMERA_W;j++)
    {
      
          img_bin_buff[i][j]=j;
      
     
     }
      
  }
  sent_image(img_bin_buff);
          while(1)
	{
	    //led(LED0,LED_ON);
                   img_flag = IMG_START;					//��ʼ�ɼ�ͼ��
                    PORTA_ISFR=~0;							//д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
                    enable_irq(87); 						//����PTA���ж�
                while(img_flag != IMG_FINISH);
           
            //led(LED0,LED_OFF);
            
	    sent_image(img_bin_buff);
            PORTA_ISFR=~0;	
          // enable_irq(87); 
		
		
	}
}
