#include "stm32f4xx.h"
#include "led.h"
#include <stdio.h>
void Delay(__IO uint32_t nCount);  //��������
uint8_t I2C_Test(void);
int main(void)
{
  LED_GPIO_Config();                  //GPIO�ܽų�ʼ��
  while (1)
  {
    LED1_ON;
    LED2_ON;
    Delay(0XFFFFFF);
    LED1_OFF;
    LED2_OFF;
    Delay(0XFFFFFF);
  }
}
/********************************************************************************************
*�������ƣ�void Delay(__IO uint32_t nCount)
*
*��ڲ�������
*
*���ڲ�������
*
*����˵������ʱ����
*******************************************************************************************/
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}





