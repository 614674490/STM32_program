#include "common.h"
#include "wifista.h"
#include "gpio.h"
#include "stdio.h"
uint8_t AP_STA_MODE=0;  //0:AP 1:STA
uint8_t AP_STA_SWITCH=0;
//���Ӷ˿ں�:8086,�������޸�Ϊ�����˿�.
const uint8_t* portnum="8086";		 

//WIFI STAģʽ,����Ҫȥ���ӵ�·�������߲���,��������Լ���·��������,�����޸�.
const uint8_t* wifista_ssid="Honor 10";			//·����SSID��
const uint8_t* wifista_encryption="wpawpa2_aes";	//wpa/wpa2 aes���ܷ�ʽ
const uint8_t* wifista_password="18931983446"; 	//��������

//WIFI APģʽ,ģ���������߲���,�������޸�.
const uint8_t* wifiap_ssid="ATK-ESP8266";			//����SSID��
const uint8_t* wifiap_encryption="wpawpa2_aes";	//wpa/wpa2 aes���ܷ�ʽ
const uint8_t* wifiap_password="12345678"; 		//�������� 

/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//5�ּ��ܷ�ʽ
const uint8_t *ATK_ESP8266_ECN_TBL[5]={"OPEN","WEP","WPA_PSK","WPA2_PSK","WPA_WAP2_PSK"};
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//usmart֧�ֲ���
//���յ���ATָ��Ӧ�����ݷ��ظ����Դ���
//mode:0,������USART3_RX_STA;
//     1,����USART3_RX_STA;
void atk_8266_at_response(uint8_t mode)
{
	if(USART2_RX_STA)		//���յ�һ��������
	{ 
		USART2_RX_BUF[RX_LEN]=0;//��ӽ�����
		printf("%s",USART2_RX_BUF);	//���͵�����
		if(mode)USART2_RX_STA=0;
	} 
}

//ATK-ESP8266���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
uint8_t* atk_8266_check_cmd(uint8_t *str)
{
	
	char *strx=0;
	if(USART2_RX_STA)		//���յ�һ��������
	{ 
		USART2_RX_BUF[RX_LEN]=0;//��ӽ�����
		strx=strstr((const char*)USART2_RX_BUF,(const char*)str);//��a�ַ�����鿴�Ƿ���b�ַ��� ������״η���b�ַ���������a�ַ���
		memset(USART2_RX_BUF,0,BUFFLEN);  //��ս�������
		USART2_RX_STA=0;
	} 
	return (uint8_t*)strx;
}

//��ATK-ESP8266��������
//cmd:���͵������ַ���
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)  back:0�����ؽ�����Ϣ 1:���ؽ�����Ϣ
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
uint8_t atk_8266_send_cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime)
{
	uint8_t res=0; 
	USART2_RX_STA=0;
	u2_printf("%s\r\n",cmd);	//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			HAL_Delay(10);//10ms
			if(USART2_RX_STA)//���յ��ڴ���Ӧ����
			{
				
				if(atk_8266_check_cmd(ack))
				{
					
					printf("ack:%s\r\n",(uint8_t*)ack);
					break;//�õ���Ч���� 
				}
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 

//��ATK-ESP8266����ָ������
//������װ
void atk_8266_send_data(uint8_t *data)
{
	u2_printf("%s",data);	//��������
	HAL_Delay(20);   //�˴�Ҫ����ʱ �������˳�͸��ָ���ͻ
}

//ATK-ESP8266�˳�͸��ģʽ
//����ֵ:0,�˳��ɹ�;
//       1,�˳�ʧ��
uint8_t atk_8266_quit_trans(void)
{
	while((USART2->SR&0X40)==0);	//�ȴ����Ϳ�
	USART2->DR='+';      
	HAL_Delay(15);					//���ڴ�����֡ʱ��(10ms)
	while((USART2->SR&0X40)==0);	//�ȴ����Ϳ�
	USART2->DR='+';      
	HAL_Delay(15);					//���ڴ�����֡ʱ��(10ms)
	while((USART2->SR&0X40)==0);	//�ȴ����Ϳ�
	USART2->DR='+';      
	HAL_Delay(500);					//�ȴ�500ms
	return atk_8266_send_cmd("AT","OK",20);//�˳�͸���ж�.
}

//��ȡATK-ESP8266ģ���AP+STA����״̬
//����ֵ:0��δ����;1,���ӳɹ�
uint8_t atk_8266_apsta_check(void)
{
	if(atk_8266_quit_trans())return 0;			//�˳�͸�� 
	atk_8266_send_cmd("AT+CIPSTATUS",":",50);	//����AT+CIPSTATUSָ��,��ѯ����״̬
	if(atk_8266_check_cmd("+CIPSTATUS:0")&&
		 atk_8266_check_cmd("+CIPSTATUS:1")&&
		 atk_8266_check_cmd("+CIPSTATUS:2")&&
		 atk_8266_check_cmd("+CIPSTATUS:4"))
		return 0;
	else return 1;
}

//��ȡATK-ESP8266ģ�������״̬
//����ֵ:0,δ����;1,���ӳɹ�.
uint8_t atk_8266_consta_check(void)
{
	uint8_t res;
	if(atk_8266_quit_trans()) return 1;			//�˳�͸�� 
	res=atk_8266_send_cmd("AT+CIPSTATUS","3",50);	//����AT+CIPSTATUSָ��,��ѯ����״̬
	return res;
}

//��ȡClient ip��ַ
//ipbuf:ip��ַ���������
void atk_8266_get_wanip(uint8_t* ipbuf)
{
	uint8_t *p,*p1;
		if(atk_8266_send_cmd("AT+CIFSR","OK",50))//��ȡWAN IP��ַʧ��
		{
			ipbuf[0]=0;
			return;
		}		
		p=atk_8266_check_cmd("\"");
		p1=(uint8_t*)strstr((const char*)(p+1),"\"");
		*p1=0;
		sprintf((char*)ipbuf,"%s",p+1);	
}

//WIFIģ���ʼ������
//work_mode:ģʽѡ��  1:STAģʽ(Ĭ��TCP���� ���ڴ�ģʽ�¿��Կ���͸��) 2:APģʽ 3:AP+STAģʽ
//con_mode:����ģʽѡ�� 0�������ӣ�1��������
//wifista_ssid:���������� wifista_password:����
//����ֵ 0��ʧ�� 1:�ɹ�
int WIFI_Init(int work_mode,int con_mode,uint8_t* wifista_ssid,uint8_t* wifista_password)
{
	int times=0;
	atk_8266_send_cmd("AT+RST","OK",20);  //ÿ���ϵ�������� ��ֹESP8266��æ���޷��ظ���Ϣ
	printf("Init Message:\r\n");
	while(atk_8266_send_cmd("AT","OK",20))//���WIFIģ���Ƿ�����
	{
		times++;
		atk_8266_quit_trans();//�˳�͸��
		atk_8266_send_cmd("AT+CIPMODE=0","OK",200);  //�ر�͸��ģʽ	
		HAL_Delay(1000);
		if(times>1) break;
	} 
	if(times>1) 
	{
		printf("No WIFI\r\n");
		return 0;
	}
	if (atk_8266_send_cmd("ATE0","OK",20))  //�رջ���
	{
		printf("Close Back Display Failed\r\n");
		return 0;
	}
	else printf("Close Back Display Successed\r\n");
	switch (work_mode)
	{
		case 1:  if(!atk_8266_send_cmd("AT+CWMODE=1","OK",50)) printf("Mode:STA\r\n");break;		//����WIFI STAģʽ
		case 2:  if(!atk_8266_send_cmd("AT+CWMODE=2","OK",50)) printf("Mode:AP\r\n");break;		//����WIFI APģʽ
		case 3:  if(!atk_8266_send_cmd("AT+CWMODE=3","OK",50)) printf("Mode:STA+AP\r\n");break;		//����WIFI AP+STAģʽ
	}
	if(work_mode!=1)
	{
	  if(atk_8266_send_cmd("AT+RST","OK",20)) return 0;		//DHCP�������ر�(��APģʽ��Ч) 
		else printf("Wait Rst\r\n");
	  HAL_Delay(3000);   //�ȴ�����
	}
	
	//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!! 
	if(work_mode!=2)  //��APģʽ�²ſɽ�������
	{
	
			memset(USART2_TX_BUF,0,BUFFLEN);
			sprintf((char*)USART2_TX_BUF,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);//�������߲���:ssid,����
			if(atk_8266_send_cmd(USART2_TX_BUF,"WIFI GOT IP",300))   //����ֵ�ǣ��� 
			{
				printf("Wifi Already  Connected\r\n");
			}
			else 
			{
				printf("WIFI Connect Successed\r\n");
				printf("WIFI Message:\r\n");
				atk_8266_send_cmd("AT+CIFSR","+",10);
			}
	}
	
	if(con_mode==0)
	{
	  if(atk_8266_send_cmd("AT+CIPMUX=0","OK",20)) 
		{
			printf("Set Connect_mode Failed\r\n");
			return 0;   //������
		}
		else printf("Connect_mode: Single connect\r\n");
	}
  else if(con_mode==1)
	{
			if(atk_8266_send_cmd("AT+CIPMUX=1","OK",20)) 
			{
				printf("Set Connect_mode Failed\r\n");
				return 0;   //������
			}
		  else printf("Connect_mode: Serval connect\r\n");
	}
	printf("WIFI Init Successed\r\n");
	printf("\r\n");
	LED0_ON();
	return 1;
}

//ģʽת��
void Mode_Switch()
{
	if(AP_STA_SWITCH)
		{
			if(AP_STA_MODE==0)
			{
			  printf("START SWITCH  AP->STA\r\n");
			  if(!atk_8266_send_cmd("AT+RST","OK",20))
		     printf("Wait Rst\r\n");
	      HAL_Delay(3000);   //�ȴ�����
			  Wifi_Sta_Init();
			}
			else
			{
				printf("START SWITCH  SAT->AP\r\n");
				if(!atk_8266_send_cmd("AT+RST","OK",20)) 
		     printf("Wait Rst\r\n");
	      HAL_Delay(3000);   //�ȴ�����
				Wifi_Ap_Init();
			}
			AP_STA_SWITCH=0;
		}
}




