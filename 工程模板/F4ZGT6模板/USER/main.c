#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void)
{ 
	LED_Init();		        //初始化LED端口
	delay_init(168);		  //初始化延时函?
	while(1)
	{
		LED=0;
		delay_ms(500);
		LED=1;
		delay_ms(500);
	}
}

