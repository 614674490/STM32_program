#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "spi.h"
#include "rc522.h"

int main(void)
 {		
	 u8 status,i;
	 	u16 temp;
	 	unsigned char data1[16] = {0x12,0x34,0x56,0x78,0xED,0xCB,0xA9,0x87,0x12,0x34,0x56,0x78,0x01,0xFE,0x01,0xFE};
//M1����ĳһ��дΪ���¸�ʽ����ÿ�ΪǮ�����ɽ��տۿ�ͳ�ֵ����
//4�ֽڽ����ֽ���ǰ����4�ֽڽ��ȡ����4�ֽڽ�1�ֽڿ��ַ��1�ֽڿ��ַȡ����1�ֽڿ��ַ��1�ֽڿ��ַȡ�� 
unsigned char data2[4]  = {0,0,0,0x01};
unsigned char DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 
	 unsigned char g_ucTempbuf[20]; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	  
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	LED_Init();
	SPI2_Init();
	 InitRc522();
  while(1)
	{
		/*
		  status = PcdRequest(PICC_REQALL, g_ucTempbuf);//Ѱ��
      if (status != MI_OK)
      {      
					PcdReset();
					PcdAntennaOff(); 
					PcdAntennaOn(); 
					continue;
       }		     
//			printf("��������:");
//      for(i=0;i<2;i++)
//			{
//					temp=g_ucTempbuf[i];
//					printf("%X",temp);
//						
//			}
////////////////////////////////////////////////////						
      status = PcdAnticoll(g_ucTempbuf);//����ײ
      if (status != MI_OK)    
			{			continue;   	}
//			printf("�����кţ�");	//�����ն���ʾ,
//			for(i=0;i<4;i++)
//			{
//					temp=g_ucTempbuf[i];
//				  printf("%X",temp);
//						
//			}
//         printf("\r\n");
///////////////////////////////////////////////////////////
         status = PcdSelect(g_ucTempbuf);//ѡ����Ƭ
         if (status != MI_OK)
         {    continue;    }
         
         status = PcdAuthState(PICC_AUTHENT1A, 4, DefaultKey, g_ucTempbuf);//��֤��Ƭ����
         if (status != MI_OK)
         {    continue;    }
         
//         status = PcdWrite(4, data1);//д��
//         if (status != MI_OK)
//         {    continue;    }
				 */
while(1)
		{
         status = PcdRequest(PICC_REQALL, g_ucTempbuf);//Ѱ��
         if (status != MI_OK)
         {   
     PcdReset();
     PcdAntennaOff(); 
     PcdAntennaOn(); 
			  continue;
         }
		 status = PcdAnticoll(g_ucTempbuf);//����ײ
         if (status != MI_OK)
         {    continue;    }
		status = PcdSelect(g_ucTempbuf);//ѡ����Ƭ
         if (status != MI_OK)
         {    continue;    }
         
         status = PcdAuthState(PICC_AUTHENT1A, 4, DefaultKey, g_ucTempbuf);//��֤��Ƭ����
         if (status != MI_OK)
         {    continue;    }


//         status = PcdValue(PICC_DECREMENT,4,data2);//�ۿ�
//         if (status != MI_OK)
//         {    continue;    }
//		 
//         status = PcdBakValue(4, 5);//�鱸��
//         if (status != MI_OK)
//         {    continue;    }
         
         status = PcdRead(4, g_ucTempbuf);//����
         if (status != MI_OK)
         {    continue;    }
        	//printf("�����飺");	//�����ն���ʾ,
         for(i=0;i<16;i++)
					{
						temp=g_ucTempbuf[i];
						printf("%X",temp);
						
					}

		 printf("\n");
			 		         
		 PcdHalt();
		}
	}	 
} 

