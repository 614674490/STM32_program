#include "wifista.h"
#include "gpio.h"
uint8_t Wifi_Client_Send_Flag=0;
//STAģʽ�����ӵ�TCP������
//ipbuf:IP��ַ portnum:�˿ں�
//����ֵ: 0:�ɹ� 1��ʧ��
int Sta_Connect(uint8_t* ipbuf,uint8_t* portnum )
{
	int times=0;
	printf("TCP_Connect Message:\r\n");
	memset(USART2_TX_BUF,0,BUFFLEN);
	sprintf((char*)USART2_TX_BUF,"AT+CIPSTART=\"TCP\",\"%s\",%s",ipbuf,portnum);    //����Ŀ��TCP������
	while(!atk_8266_send_cmd((uint8_t *)USART2_TX_BUF,"OK",100)) 
	{
    times++;
		if(times==5)
			break;
	}
	if(times<5)
	{
		printf("TCP Connect Successed\r\n");
	  LED1_ON();
	}
	else
	{
		printf("TCP Connect Failed\r\n");
		return 1;
	}
	printf("\r\n");
  return 0;	
}

//TCP������Ϣ
//mode 0����Ϊ�ͻ��˷�����Ϣ 1����Ϊ������������Ϣ
void TCP_Client_Send(uint8_t *p)
{
	int times=0;
	printf("Data Send Message:\r\n");
	if(atk_8266_send_cmd("AT+CIPMODE=1","OK",100)) printf("Enter Clear Trans  Failed\r\n");//����ģʽΪ��͸��	
	else printf("Enter Clear Trans  Successed\r\n");


		if(!atk_8266_send_cmd("AT+CIPSEND",">",300))  //�������� 
		{
			printf("Wait Send Data......\r\n");
			atk_8266_send_data(p);
			printf("Data Send Success\r\n");  //�������ݳɹ�
		}
		else 
		{
			printf("Data Send Failed\r\n");  //��������ʧ�ܡ�
			printf("Unopen Send!\r\n");
			if(atk_8266_consta_check()) 
			{
				printf("TCP Connect Failed\r\n");//�õ�����״̬
				Sta_Connect("10.164.154.231","8080");
			}
			else printf("TCP Connect Successed\r\n");
		}
	
	if(!atk_8266_quit_trans()) 
	{
		printf("Exit Clear Trans  Successed\r\n");   //����������֮���˳�͸�� ����ATָ��ģʽ ���������������
	}
  else printf("Exit Clear Trans  Failed\r\n");
	printf("\r\n");
}
	
void Wifi_Sta_Init()
{
	if(WIFI_Init(1,0,"Honor 10","1893193446"));  //����������
	{
		HAL_Delay(8000);   //�ȴ�����  ʱ�䲻Ҫ̫��
	  //Sta_Connect("10.164.154.231","8080");   //���ӷ�����
	}
	AP_STA_MODE=1;
	memset(USART2_RX_BUF,0,BUFFLEN);  //��ս�������
	USART2_RX_STA=0;
	
}



