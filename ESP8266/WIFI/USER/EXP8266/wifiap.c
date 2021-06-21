#include "wifiap.h"
#include "gpio.h"
uint8_t Wifi_Server_Send_Flag=0;
// ���� ���� �˿�
//0:�ɹ� 1:ʧ��
uint8_t Set_Server(uint8_t* SSID,uint8_t* PASS,uint8_t* portnum )
{
	printf("Set Up Server Message:\r\n");
	
	memset(USART2_TX_BUF,0,BUFFLEN);
	sprintf((char*)USART2_TX_BUF,"AT+CWSAP=\"%s\",\"%s\",1,4",SSID,PASS);//���������� ͨ����Ϊ1 ���ܷ�ʽΪWPA2 PSK
	if(!atk_8266_send_cmd(USART2_TX_BUF,"OK",100))
		printf("�����������ɹ�\r\n");
	else 
		return 1;
	
	/*if(!atk_8266_send_cmd("AT+CIPMUX=1","OK",100))
		printf("���������ӳɹ�\r\n");    //Ҫ����Ϊ������ģʽ ���뿪��������
	else
		return 1;*/
	
	memset(USART2_TX_BUF,0,BUFFLEN);
	sprintf((char*)USART2_TX_BUF,"AT+CIPSERVER=1,%s",portnum);//����Server ���ö˿ں�
	if(!atk_8266_send_cmd(USART2_TX_BUF,"OK",100))
		printf("���ö˿ںųɹ�\r\n");
	else
		return 1;
	printf("Server Message:\r\n");
	printf("IP: 192.168.4.1  SSID: %s  PASS: %s  portnum: %s\r\n",SSID,PASS,portnum);
	printf("\r\n");
	LED1_ON();
	return 0;
}

void Wifi_Ap_Init()
{
	if(WIFI_Init(2,1,"Honor 10","1893193446"));  //����������
	{
		HAL_Delay(8000);
	  Set_Server("ATK-ESP8266","1659823781","8086");   //���ӷ�����
	}
	AP_STA_MODE=0;
	memset(USART2_RX_BUF,0,BUFFLEN);  //��ս�������
	USART2_RX_STA=0;
}

//TCP������Ϣ
//���� ���� ID��
void TCP_Server_Send(uint8_t *p,uint8_t id)
{
	int times=0;
	uint8_t length=0;
	printf("Data Send Message:\r\n");
	if(atk_8266_send_cmd("AT+CIPMODE=1","OK",100)) printf("Enter Clear Trans  Failed\r\n");//����ģʽΪ��͸��	
	else printf("Enter Clear Trans  Successed\r\n");
	length=strlen((const char*)p);
  memset(USART2_TX_BUF,0,BUFFLEN);
	sprintf((char*)USART2_TX_BUF,"AT+CIPSEND=%d,%d",id,length);//����Server ���ö˿ں�
  
		if(!atk_8266_send_cmd(USART2_TX_BUF,"OK",100))  //�������� 
		{
			printf("Wait Send Data......\r\n");
			atk_8266_send_data(p);
			printf("Data Send Success\r\n");  //�������ݳɹ�
		}
		else 
		{
			printf("Data Send Failed\r\n");  //��������ʧ�ܡ�
		}
	
	if(!atk_8266_quit_trans()) 
	{
		printf("Exit Clear Trans  Successed\r\n");   //����������֮���˳�͸�� ����ATָ��ģʽ ���������������
	}
  else printf("Exit Clear Trans  Failed\r\n");
	printf("\r\n");
}
	
