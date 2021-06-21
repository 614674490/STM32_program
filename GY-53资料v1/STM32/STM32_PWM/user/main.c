#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "string.h"
 #include "LED.h"
 /*
 Keil: MDK5.10.0.2
MCU:stm32f103c8
Ӳ���ӷ���
GY-53---STM32
1��GY-53_PWM---STM32_PA0
2��STM32_TX---FT232_RX,STM32�������ϴ�����λ��

���˵��:
�ó������PWM��ʽ��ȡģ�����ݣ�����=�ߵ�ƽʱ��(ms)*100��������9600

��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_X;
  
  /* 4����ռ���ȼ���4����Ӧ���ȼ� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /*��ռ���ȼ��ɴ���жϼ���͵��ж�*/
	/*��Ӧ���ȼ����ȼ�ִ��*/
	NVIC_X.NVIC_IRQChannel = USART1_IRQn;//�ж�����
  NVIC_X.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
  NVIC_X.NVIC_IRQChannelSubPriority = 0;//��Ӧ���ȼ�
  NVIC_X.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж���Ӧ
  NVIC_Init(&NVIC_X);
}
void gpio_Input(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
}
int main(void)
{
	uint8_t datas[3]={0};
	uint16_t distance=0;
	float time=0.0f;
	delay_init(72);
	NVIC_Configuration();
	Usart_Int(9600);
	gpio_Input();
	delay_ms(500);//�ȴ�ģ���ʼ�����
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));//�ȴ�����
	while(1)
	{
		while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));//�ȴ����߿�ʼ��ʱ
		start_Time();
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));//�ȴ����ͣ�ֹͣ��ʱ
		Get_Time(&time);//�õ���msΪ��λ��ʱ��
		distance=time*100;//���볤��=pwmʱ��(ms)*100
		datas[0]=distance>>8;
		datas[1]=distance;
		datas[2]=2;//ģ��Ĭ��ģʽΪ 2
		send_3out(datas,3,0x15);//����pwm��������Ϊ50ms�������Ϊ2M��time���Ϊ20ms���������㹻ʱ�佫����ͨ�����ڷ���
		
	}
}
