
#include "include.h"

/*************************************************************************
*                             ��Ұ�ʿ
*                              freescale���ƽ����

*  ����ʱ�䣺2013-3-29     
*   ϵͳ�ں�Ƶ��96M   BUS_clock  48M   Flex_Clock 48M  Flash_Clock 24M
* 


*    LED����˵��
*    LED0  PTA14  LED1  PTA15   LED2  PTA16   LED0  PTA17

*    5110����˵��
    CLK   PTA25  DIN  PTA26    DC PTA27  CS PTA28  RST PTA29

*   ��������˵��         //��������д���� exti.c�У������Ժ�ĳ��ⲿ�ж�
    K2 PTB20   K3  PTB21  K4  PTB22  K5  PTB0  K6  PTB6  K7  PTB8
    
*   AT24C02����˵��  
    SCL PTD4  SDA  PTD6

*   ���pwm���  PTC1  PTC2  PTC3  PTC4
    
*    nrf24l01����˵��
    IRQ PTE25  CSN PTE26  MOSI PTD13   CE PTE28  SCK PTD12    MISO PTD14

*   �����������������˵��
      FTM2_PHA  PTA10    FTM2_PHB   PTA11  FTM1_QD_PHA  PTA8  FTM1_QD_PHB  PTA9

*   Gyto PTB2    Gravity PTE24

*  ����CCD����˵��
*  SI PTC18  SCK PTC19  A0 PTB11
*************************************************************************/
extern volatile uint8 angle[15000];

extern volatile uint8 Speed[2];
extern volatile uint8 ccd[32];
extern volatile uint16 angle_max;
extern volatile uint16 angle_min;
//extern volatile uint8 flag;
//extern volatile uint16 n;
//extern volatile uint16 Gyto0_Offest1[1000];
//extern volatile uint16 temp;
//extern volatile float Gyto0_Speed_Ratio;  //������0�������ֵ���������ٶȡ�����ϵ��
//extern volatile float o;

/*******************    �Ƕȼ�����ز���**********************/

extern volatile uint16   Gyro_Offest;     //�������м�ֵ
extern volatile uint16   Gravity_Offest;  //����м�ֵ
extern volatile float Voltage_Gyro;       //AD�ɼ���������ֵ   
extern volatile float Voltage_Gravity;    //AD�ɼ���������ֵ
extern volatile float GravityAngle;       //���ٶȼƼ�����ĽǶ�ֵ����λ  ��
extern volatile float GyroAngleSpeed;     //�����Ǽ����  ���ٶ�ֵ����λ ��/����
extern volatile float NowCarAngle;        //�Ƕȹ���ֵ�����ڿ������˲�
extern volatile float RealCarAngle;      //�Ƕ����ֵ�����ڿ������˲�
extern volatile float NowCarAngle_PP;    //����ֵ������ڿ������˲�
extern volatile float RealCarAngle_PP;   //���ֵ������ڿ������˲�
extern volatile float GyroAngle_QQ;     //�����Ƿ�����ڿ������˲�
extern volatile float GravityAngle_RR;   //���ٶȼƷ�����ڿ������˲�
extern volatile float Kg;               //����������ϵ�������ڿ������˲�
extern volatile float Car_Angle_Set ;   //����趨ֵ��ʵ������Ϊ��

/****************      ���������ز���   *******************/

extern volatile float AngleControlOut;    //��ǿ������
extern volatile float K_AngleControlOut;   //ֱ������ϵ��
extern volatile float AngleControl_P;    //��ǿ��Ʋ������ظ�ϵ��
extern volatile float AngleControl_D;    //��ǿ��Ʋ���������ϵ��
extern volatile uint16 Encoder_Right;
extern volatile uint16 Encoder_Left;
extern volatile float Speed_Right;       //������  ���ֳ��٣�����20���룬δ���κ�����ϵ��  
extern volatile float Speed_Left;        //������  ���ֳ��٣�����20���룬δ���κ�����ϵ��
extern volatile float Speed_Set;         //��ģ�ٶȸ���ֵ��ͬ�������ٶ����Ӧ һ��ΪCCD�ɼ��ز���������һ����
extern volatile float Car_Speed;         //��ģʵ���ٶȣ����ұ������ٶ���ӵ�һ��
extern volatile uint8 Speed_Flag;
extern volatile uint8 SpeedFlag;
extern volatile float Speed_S;
extern volatile float Speed_X;
extern volatile float Speed_Control_P;   //�ٶȿ��Ʋ���������ϵ��
extern volatile float Speed_Control_I;   //�ٶȿ��Ʋ���������ϵ��

//extern volatile float Speed_Control_D;

extern volatile float SpeedControlIntegral;//�ٶȻ�����,λ��
extern volatile float SpeedControlOutNew;  
extern volatile float SpeedControlOutOld;   
extern volatile float SpeedControlOut;      //�ٶȿ������
extern volatile uint8 SpeedControlPeriod;   //�ٶȿ������ڣ�ÿ���Ӽ�һ��ʹ����⻬
extern volatile float K_SpeedControlOut;      //�ٶȿ������
extern volatile float  DirectionControlOutNew;  
extern volatile float  DirectionControlOutOld;   
extern volatile float  DirectionControlOut;      //�ٶȿ������
extern volatile float  Dir_Control_P;            //������Ʋ���

extern volatile float MotorControlOut_Right;//���ֵ�������Ϊ���ֲ�����Ӻ�����ֱ���͵����
extern volatile float MotorControlOut_Left; //���ֵ�������Ϊ���ֲ�����Ӻ�����ֱ���͵����
extern volatile float Speed_Delt;
extern volatile uint16 time_flag;
/****************      ����CCD��ز���   *******************/
extern volatile uint16 Loction[120];       //�������CCD��ֵ��ǰ�ĸ��ͺ��ĸ����ݲ�̫׼ȷ����ɾ��
extern volatile float Integration_Set;     //�ع����趨ֵ
extern volatile float Integration_Real;    //�ع���ʵ��ֵ
extern volatile float  Integration_time;    //�ع�ʱ�� 0��20����
extern volatile uint16 Integration_Middle;   //�����м䷧ֵ����Ȩ֮��
extern volatile uint8  Line_left;            //������λ�ã���Χ0-60
extern volatile uint8  Line_right;           //�Ҳ����λ�ã���Χ0-60
extern volatile float  LeftRightAdd;         //���Һ���λ��֮����ڵ���ת����ٶ��趨
extern volatile float  LeftRightSub;         //���Һ���λ��֮�ͣ����ڵ���ת����ٶ��趨

extern volatile uint8 barrier;

//FTM2_CNT ���ֱ���������
extern volatile uint16 time,time1;
extern volatile float GyroAngle;
extern volatile uint16 ge;
extern volatile uint16 flag;
extern volatile uint16 flag_w;
extern volatile float Speed_Delt_Old;
void Kalman_Parameter_init(void)
{
  RealCarAngle_PP=0.01;
  GyroAngle_QQ=0.0001;
  GravityAngle_RR=100000;
  RealCarAngle=0;
  NowCarAngle=0;
}
void Motor_Parameter_init(void)
{
  time_flag=0;
//  AngleControl_P=9.8;
//  AngleControl_D=90;
  K_AngleControlOut=1;
  K_SpeedControlOut=0;
  AngleControl_P=7.8;
  AngleControl_D=80;
  Car_Angle_Set=0;
  DirectionControlOutNew=0;
  DirectionControlOutOld=0;
  DirectionControlOut=0;
  Integration_Set=1000;
  Integration_time=5;
  SpeedControlIntegral=0;
  Speed_Set=0;
//  Speed_Control_I=0.04;
  Speed_Control_P=0.7;
  Speed_Control_I=0.2;
//  Speed_Control_D=0.1;
  SpeedControlOut=0;
  SpeedControlPeriod=0;
  Dir_Control_P=0;

}
void all_init(void)
{
  uint8 k;
  Speed_Flag=0;
  Speed_S=0;
  Speed_X=0;
  Speed_Delt=0;
  uint32 Gyro_Offest_Sum,Gravity_Offest_Sum;
  Gyro_Offest_Sum=0;
  Gravity_Offest_Sum=0;
  LCD5110_Init();  //5110Һ����ʼ��
  delayms(10);
  key_init();     //������ʼ��
  LED_init();
//  AT24CXX_Init();  // AT24C01��ʼ��
  delayms(100);
  adc_init();
  delayms(10);
//  NRF24L01_Init();
//  delayms(100);
//  TX_Mode();
//  delayms(1000);
  for(k=0;k<200;k++)
  {
    Gyro_Offest_Sum+=Gyro_value();
    Gravity_Offest_Sum+=Gravity_value();
  }
  Gyro_Offest=Gyro_Offest_Sum/200;        
  Gravity_Offest=Gravity_Offest_Sum/200; 
  CCD_Init();
  pit_init(PIT0,48000);
  delayms(100);
  led(LED3,LED_ON);
  FTM_PWM_init();
  FTM_QUAD_init();
}
  
void main(void)
{
  ge=0;
  uint16 i,j;
  float Speed_Rights; 
  
    
  flag_w=0;
  flag=0;
  DisableInterrupts;
  Motor_Parameter_init();
  Kalman_Parameter_init();
  all_init();
  EnableInterrupts;

  
  delayms(1000);
  delayms(1000);
  K_AngleControlOut=0.95;
  K_SpeedControlOut=0.1;
  delayms(100);
  K_AngleControlOut=0.9;
  K_SpeedControlOut=0.2;
  delayms(100);
  K_AngleControlOut=0.85;
  K_SpeedControlOut=0.3;
  delayms(100);
  K_AngleControlOut=0.8;
  K_SpeedControlOut=0.5;
  delayms(100);
//  K_AngleControlOut=0.75;
//  K_SpeedControlOut=0.5;
  K_AngleControlOut=0.75;
  K_SpeedControlOut=0.9;
  delayms(100);
  Speed_Set=15;
  delayms(500);
  Dir_Control_P=32;
  Speed_Set=30;
  delayms(500);
  Speed_Set=45;
  delayms(500);
  Speed_Set=60;
  delayms(500);
  Speed_Set=70;
  delayms(500);
  led(LED2,LED_ON);

   Dir_Control_P=32;

  while(1); 
 }


