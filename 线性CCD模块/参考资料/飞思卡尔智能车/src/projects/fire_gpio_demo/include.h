#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include �û��Զ����ͷ�ļ�
 */

#include  "gpio.h"       //IO�ڲ���
#include  "uart.h"      //����
#include  "lptmr.h"     //�͹��Ķ�ʱ��(��ʱ)
#include  "led.h"     //�͹��Ķ�ʱ��(��ʱ)
#include  "5110.h"     
#include  "PIT.h"
#include "exti.h"
#include  "PIT.h"
#include  "AT24C02.h"
#include  "ftm.h"
#include  "spi.h"
#include "NRF24L0.h"
#include  "adc.h"
#include  "angle.h"
#include "math.h"
#include  "delay.h"

//#define Gravity_Offest  1952         //����м�ֵ
#define Gravity_Max     2942         //������ֵ
#define Gravity_Min     962          //�����Сֵ
#define Gravity_Ratio   0.05787      //��Ǳ���ֵ������ɽǶ�

#define Gyro_Ratio     0.000262      //�����ǻ������ֵ������ɽǶ�

#define  MOTOR_OUT_DEAD_VAL    0
#define  Speed_Control_Period 20    //�ٶȿ������ڣ�20����
#define  SpeedOutLimit        18
#define  DirectionOutLimit    16




/*
const uint16   Gyto_Q =1;//�������˲��е���Ҫϵ������������
const uint16   Gravity_R =300;
volatile uint16 Gravity_Offest;    //�������ٶ��м�ֵ
volatile uint16 Gravity_Max;       //�������ٶ����ֵ
volatile uint16 Gravity_Min;       //�������ٶ���Сֵ
volatile float  Gravity_Ratio;     //�������ٶȱ���ֵ
volatile uint16 Gyto0_Offest;      //������0�м�ֵ
volatile float Gyto0_Angle_Ratio;  //������0�������ֵ������ɻ���
volatile float Gyto0_Speed_Ratio;  //������0�������ֵ���������ٶȡ�����ϵ��
*/

#endif  //__INCLUDE_H__
