#include "common.h"
#include "include.h"
#include "sci.h"
#include "isr.h"
#include "imgprocess.h"
#include "globle.h"
#include "motor.h"
#include "servo.h"
#define  T_average 6 //��ʼ�������������Ĵ���
u8 img_bin_buff[CAMERA_H][CAMERA_W] ; //��ֵ��ͼ����
                            //������
                //����������������
void main(void)
{
        
	LED_init();        					
        led(LED0,LED_OFF); 
        sci_init(UART4);
       // exti_init(PORTC,10,rising_down);
        Servo_init();
        Motor_init();
        Handle(0);
        while(1)
	{
         FTM_PWM_Duty(FTM1, CH0,450); 
          
          
        }
}