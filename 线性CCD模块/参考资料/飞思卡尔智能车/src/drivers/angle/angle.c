/******************** ��Ұ�ʿ ********************
 * �ļ���       ��angle.c

 *
 * ʵ��ƽ̨     ��LQ K60������
 *                ang PTB11  Gyto PTB10  Z PTE24
 *
 * ����          DAQI
**********************************************************************************/

#include "include.h"
uint8 angle[15000];
uint8 Speed[2];
uint8 ccd[32];
/*******************    �Ƕȼ�����ز���**********************/

uint16  Gyro_Offest;        //�������м�ֵ
uint16  Gravity_Offest;
float Voltage_Gyro;     //AD�ɼ���������ֵ
float Voltage_Gravity;  //AD�ɼ���������ֵ
float GravityAngle;     //���ٶȼƼ�����ĽǶ�ֵ����λ  �Ƕ�
float GyroAngleSpeed;   //�����Ǽ����  ���ٶ�ֵ����λ �Ƕ�/����
float NowCarAngle;      //�Ƕȹ���ֵ�����ڿ������˲�
float RealCarAngle;     //�Ƕ����ֵ�����ڿ������˲�
float NowCarAngle_PP;   //����ֵ������ڿ������˲�
float RealCarAngle_PP;   //���ֵ������ڿ������˲�
float GyroAngle_QQ;     //�����Ƿ�����ڿ������˲�
float GravityAngle_RR;  //���ٶȼƷ�����ڿ������˲�
float Kg;               //����������ϵ�������ڿ������˲�
float Car_Angle_Set ;   //����趨ֵ�����ٶ��趨ֵ���ٶ�ʵ��ֵ��ֵȷ��

/****************      ���������ز���   *******************/

float AngleControlOut;    //��ǿ������
float K_AngleControlOut;   //ֱ������ϵ��
float AngleControl_P;    //��ǿ��Ʋ������ظ�ϵ��
float AngleControl_D;    //��ǿ��Ʋ���������ϵ��
uint16 Encoder_Right;
uint16 Encoder_Left;
float Speed_Right;        //������  ���ֳ��٣�����20���룬δ���κ�����ϵ��
float Speed_Left;         //������  ���ֳ��٣�����20���룬δ���κ�����ϵ��
float Speed_Set;          //��ģ�ٶȸ���ֵ��ͬ�������ٶ����Ӧ һ��ΪCCD�ɼ��ز���������һ����
float Car_Speed;          //��ģʵ���ٶȣ����ұ������ٶ���ӵ�һ��
uint8 Speed_Flag;
uint8 SpeedFlag;
float Speed_S;
float Speed_X;
float Speed_Control_P;    //�ٶȿ��Ʋ���������ϵ��
float Speed_Control_I;    //�ٶȿ��Ʋ���������ϵ��

//float Speed_Control_D;

float SpeedControlIntegral;//�ٶȻ�����,λ��
float SpeedControlOutNew;  
float SpeedControlOutOld;
float SpeedControlOut;     //�ٶȿ������
float K_SpeedControlOut;      //�ٶȿ������
float  DirectionControlOutNew;  
float  DirectionControlOutOld;   
float  DirectionControlOut;      //����������
float  Dir_Control_P;            //������Ʋ���
uint8 SpeedControlPeriod;  //�ٶȿ������ڣ�ÿ�����Ӽ�һ��ʹ����⻬
float MotorControlOut_Right;//���ֵ�������Ϊ���ֲ�����Ӻ�����ֱ���͵����
float MotorControlOut_Left; //���ֵ�������Ϊ���ֲ�����Ӻ�����ֱ���͵����
float Speed_Delt;
//float Speed_Delt_Old;
uint16 time_flag;
/****************      ����CCD��ز���   *******************/

uint16 Loction[120];         //�������CCD��ֵ��ǰ�ĸ��ͺ��ĸ����ݲ�̫׼ȷ����ɾ��
float Integration_Set;       //�ع����趨ֵ
float Integration_Real;      //�ع���ʵ��ֵ
uint16 Integration_Middle;   //�����м䷧ֵ����Ȩ֮��
uint8  Line_left;            //������λ�ã���Χ0-64
uint8  Line_right;            //�Ҳ����λ�ã���Χ0-64
float  Integration_time;    //�ع�ʱ�� 0��20����
float  LeftRightAdd;        //���Һ���λ��֮����ڵ���ת����ٶ��趨
float  LeftRightSub;        //���Һ���λ��֮�ͣ����ڵ���ת����ٶ��趨

uint8 barrier;

float GyroAngle;   
uint16 flag;
uint16 flag_w;
uint16 angle_max;
uint16 angle_min;

void Kalman_Filter(void)                    //�������˲�����  
{
  Voltage_Gyro=Gyro_value();
  Voltage_Gravity=Gravity_value();
  
  Voltage_Gyro=Gyro_Offest-Voltage_Gyro;
  Voltage_Gravity-=Gravity_Offest;
  if(Voltage_Gyro>1700)
  {
    Voltage_Gyro=1700;    
  }
  if(Voltage_Gyro<-1700)
  {
    Voltage_Gyro=-1700;
  }                                   //��ֵ������ֹ�����ǵ����ݹ������
  GyroAngleSpeed=Voltage_Gyro*Gyro_Ratio;
  GyroAngle+=GyroAngleSpeed;
//  flag=GyroAngle;
  GravityAngle=Voltage_Gravity*Gravity_Ratio;
 // GravityAngle_RR=((GravityAngle-RealCarAngle)*24+2)*((GravityAngle-RealCarAngle)*24+2);
  NowCarAngle=RealCarAngle+GyroAngleSpeed;                   //����ֵ
  NowCarAngle_PP=RealCarAngle_PP+GyroAngle_QQ;              //���Ʒ���
  Kg=sqrt(NowCarAngle_PP/(NowCarAngle_PP+GravityAngle_RR)); //�������ϵ��
  RealCarAngle=NowCarAngle+Kg*(GravityAngle-NowCarAngle);    //����ֵ����
  RealCarAngle_PP=(1-Kg)*NowCarAngle_PP;                     //����ֵ����

}
void AngleControl(void)                 //ֱ�����ƣ�ÿ����һ��
{
 AngleControlOut=(Car_Angle_Set-RealCarAngle)*AngleControl_P+(0-GyroAngleSpeed)*AngleControl_D; 
}

void MotorSpeedOut(void)              //��������ÿ����һ��     
{
//  MotorControlOut_Left=AngleControlOut*K_AngleControlOut+SpeedControlOut*K_SpeedControlOut+DirectionControlOut;
// MotorControlOut_Right=AngleControlOut*K_AngleControlOut+SpeedControlOut*K_SpeedControlOut-DirectionControlOut;
  MotorControlOut_Left=AngleControlOut*K_AngleControlOut+SpeedControlOut*K_SpeedControlOut+DirectionControlOut;
  MotorControlOut_Right=AngleControlOut*K_AngleControlOut+SpeedControlOut*K_SpeedControlOut-DirectionControlOut;
//  MotorControlOut_Right*=1.08;
  if(RealCarAngle>60)
  {
    MotorControlOut_Left=0;
    MotorControlOut_Right=0;
  }
  if(RealCarAngle<-60)
  {
    MotorControlOut_Left=0;
    MotorControlOut_Right=0;
  }
  if(MotorControlOut_Right>=0)
  {
    MotorControlOut_Right+=MOTOR_OUT_DEAD_VAL;
    if(MotorControlOut_Right>150)
    MotorControlOut_Right=150;
    R_PWM_BACK(MotorControlOut_Right);
    R_PWM_GO(0);
  }
  if(MotorControlOut_Right<0)
  {
    MotorControlOut_Right-=MOTOR_OUT_DEAD_VAL;
    if(MotorControlOut_Right<-150)
    MotorControlOut_Right=-150;
    R_PWM_GO((0-MotorControlOut_Right));
    R_PWM_BACK(0);
  }
  if(MotorControlOut_Left>=0)
  {
    MotorControlOut_Left+=MOTOR_OUT_DEAD_VAL;
    
    if(MotorControlOut_Left>150)
    MotorControlOut_Left=150;
    L_PWM_BACK(MotorControlOut_Left);
    L_PWM_GO(0);
  }
  if(MotorControlOut_Left<0)
  {
    MotorControlOut_Left-=MOTOR_OUT_DEAD_VAL;
    if(MotorControlOut_Left<-150)
    MotorControlOut_Left=-150;
    L_PWM_GO((0-MotorControlOut_Left));
    L_PWM_BACK(0);
  }
}
void Get_Speed(void)                //����������ʵʱ�ٶȣ��������������
{
  float fP,fI;
  Encoder_Right=FTM1_CNT;
  FTM1_CNT=0;
  Encoder_Left=FTM2_CNT;
  FTM2_CNT=0;
  if(Encoder_Right>30000)
  {
    Speed_Right=(Encoder_Right-65535);
  }
  if(Encoder_Right<=30000)
  {
    Speed_Right=Encoder_Right;
  }
  if(Encoder_Left>30000)
  {
    Speed_Left=(65535-Encoder_Left);
  }
  if(Encoder_Left<=30000)
  {
    Speed_Left=0-Encoder_Left;
  }
  Car_Speed=(Speed_Right+Speed_Left)*0.5;
//  if(Car_Speed<0)
//      Speed[1]=0-Car_Speed;
//  else
//  {
//      Speed[1]=Car_Speed;
//   }
//  Speed[0]=Speed_Set;
  
//  if(NRF24L01_TxPacket(Speed)==TX_OK)
//        {
//          LED_turn(LED3);
//        }
//  Speed_Delt_Old=Speed_Delt;
  Speed_Delt=Speed_Set-Car_Speed;
  if(Speed_Delt>0)
   Speed_Flag=0; 
  if((Speed_Delt<=0)&&(Speed_Set>45))
  {
    Speed_Flag++;
    if((Speed_Delt>=-8)&&(Speed_Flag>=15))
        asm("nop"); 
    else
        SpeedControlIntegral-=0.64;
    if(SpeedControlIntegral<=10)
        SpeedControlIntegral=10;
  }
  if(Speed_Delt<-15)
    Speed_Delt=-15;
  
    
  fP=Speed_Delt*Speed_Control_P;
  if((Speed_Delt<30)&&(Speed_Delt>-30))
  {
  fI=Speed_Delt*Speed_Control_I;
  SpeedControlIntegral+=fI;
  }
  if(Speed_Delt>10)
  {
    SpeedControlIntegral+=0.4;
  }
//  fD=(Speed_Delt-Speed_Delt_Old)*Speed_Control_D;
  SpeedControlOutOld=SpeedControlOutNew;
  SpeedControlOutNew=fP+SpeedControlIntegral;
}
void SpeedControlOutput(void)         
{
  float Value;
  Value=SpeedControlOutNew-SpeedControlOutOld;
  if(Value>SpeedOutLimit)
      Value=SpeedOutLimit;
  if(Value<-SpeedOutLimit)
      Value=-SpeedOutLimit;            //�ٶ����������ֵ������ֹ�ٶ�ͻ��̫��ˤ��
 // SpeedControlOut=Value*(SpeedControlPeriod+1)/Speed_Control_Period+SpeedControlOutOld;
  SpeedControlOut=Value*0.5+SpeedControlOutOld;
  
}

void CCD_Init(void)
{
  gpio_init(PORTC,18,GPO,0);
  gpio_init(PORTC,19,GPO,0);
}
void StartIntegration(void)   //�ع⺯��,�����λ����
{
  uint8 i;
  TSL_SI_High;
  delayus();
  TSL_CLK_High;
  delayus();
  TSL_SI_Low;
  delayus();
  SamplingDelay();
  TSL_CLK_Low;
  delayus();
  for(i=1;i<128;i++)
  {
    TSL_CLK_High;
    SamplingDelay();  
    TSL_CLK_Low;
    delayus();
  }
  TSL_CLK_High;
  delayus();
  TSL_CLK_Low;
}

void Get_Loction(void)       //�õ�С��λ�ã���120�����ݵ㣬���ƺ�ʱ�߰�΢�롣
{  
  
  uint8 i;
//  Integration_sum=0;
  TSL_SI_High;
  delayus();
  TSL_CLK_High;
  delayus();
  TSL_SI_Low;
  delayus();
 // Loction[0]=CCD_value();
// Integration_sum+=CCD_value();
  TSL_CLK_Low;
  delayus();
  for(i=0;i<4;i++)
  {
    TSL_CLK_High;
    SamplingDelay(); 
    TSL_CLK_Low;
    delayus();
  }
  for(i=0;i<120;i++)
  {
    TSL_CLK_High;
    delayus();
    Loction[i]=CCD_value();
 //   Integration_sum+=CCD_value();
    TSL_CLK_Low;
    delayus();
  }
  for(i=0;i<4;i++)
  {
    TSL_CLK_High;
    SamplingDelay(); 
    TSL_CLK_Low;
    delayus();
  }
//  Integration_Real=Integration_sum/128;
  
  TSL_CLK_High;
  delayus();
  TSL_CLK_Low;
  
}
void Loction_Filter(void)     //С��λ�ô�����ȡ���Ҳ���ߡ����������ع�ʱ�䡢�������Ӧ����������
{
  uint8 i,j,k;
  uint32 Integration_sum_Black,Integration_sum_White;
  uint32 Integration_sum;
  j=0;
  k=0;
  Integration_sum_Black=0;
  Integration_sum_White=0;
  Integration_sum=0;
  for(i=0;i<120;i++)
  {
    Integration_sum+=Loction[i];
  }
  Integration_Real=Integration_sum/120;    //�����ʵ���ع���
  Integration_time+=(Integration_Set-Integration_Real)*0.0005; //����������ع�ʱ�� 
  if(Integration_time>=18)
    Integration_time=18;
  if(Integration_time<=1)
    Integration_time=1;      //�ع�ʱ�����ƴ��� 
  
  for(i=0;i<120;i++)
  {
    if(Loction[i]<=Integration_Real-5)
    {
       Integration_sum_Black+=Loction[i];
       j++;
    }
    if(Loction[i]>Integration_Real+5)
    {
       Integration_sum_White+=Loction[i];
       k++;
    }
    Integration_Middle=(Integration_sum_Black/j+Integration_sum_White/k)/2;   //��Ȩ�ó��м䷧ֵ
  }
  if((Loction[58]<Integration_Middle)&&(Loction[59]<Integration_Middle)&&(Loction[60]<Integration_Middle)&&(Loction[61]<Integration_Middle))
  {
    for(i=59;i>=1;i--)
    {
      if((Loction[i]>Integration_Middle)&&(Loction[i-1]>Integration_Middle))
      {
       Line_left=80;
       break;
      }
    }
    for(j=60;j<=119;j++)
    {
      if((Loction[j]>Integration_Middle)&&(Loction[j+1]>Integration_Middle))
      {
      Line_right=80;
      break;
      }
    }
    if((i<=40)&&(j>=80))
       barrier=1;
  }  //����м��ĸ����ݵ�Ϊ���ߣ���������ʼ��ȡ���ߣ���������һ����˵����Ӧ��÷���ת
  if(!((Loction[58]<Integration_Middle)&&(Loction[59]<Integration_Middle)&&(Loction[60]<Integration_Middle)&&(Loction[61]<Integration_Middle)))
  {    
    for(i=59;i>=1;i--)
    {
  
       if((Loction[i]<Integration_Middle)&&(Loction[i-1]<Integration_Middle))
       {
        Line_left=59-i;
        break;
        }
    }    
   if(i<=1)
     Line_left=60;
  for(i=60;i<=118;i++)
  {
    if((Loction[i]<Integration_Middle)&&(Loction[i+1]<Integration_Middle))
    {
      Line_right=i-60;
      break;
    }
  }
  if(i>=118)
     Line_right=60;
  }
  //��ȡ���Һ���
  DirectionControlOutOld=DirectionControlOutNew;
  
  LeftRightAdd= Line_left+Line_right;
  LeftRightSub= Line_left-Line_right;
  DirectionControlOutNew=LeftRightSub*Dir_Control_P/LeftRightAdd; 
  
  
  
}
void DirectionControlOutput(void)
{
  float Value;
  Value=DirectionControlOutNew-DirectionControlOutOld;
  if(Value>DirectionOutLimit)
    Value=DirectionOutLimit;
  if(Value<-DirectionOutLimit)
    Value=-DirectionOutLimit;
  DirectionControlOut=Value*(SpeedControlPeriod+1)/Speed_Control_Period+DirectionControlOutOld;
}
void CarControl(void)
{
    Kalman_Filter();
    AngleControl();
    SpeedControlOutput();
    DirectionControlOutput();
    SpeedControlPeriod++;
    
    if(SpeedControlPeriod==(19-(uint8)Integration_time))
    StartIntegration();
    if(SpeedControlPeriod==19)
    Get_Loction();
    if(SpeedControlPeriod==20)
    {  
      Loction_Filter();
      
      Get_Speed();
      
      SpeedControlPeriod=0;
    }
    MotorSpeedOut();
//  }
 
  
  
/*  if(SpeedControlPeriod==1)
    convery_ccd0();
  if(SpeedControlPeriod==5)
    convery_ccd1();
  if(SpeedControlPeriod==9)
    convery_ccd2();
  if(SpeedControlPeriod==13)
    convery_ccd3();*/

}
  
void convery_ccd0(void)
{
  uint8 i;
  for(i=0;i<4;i++)
    ccd[i]=0;
  for(i=4;i<32;i++)
  {
    ccd[i]=Loction[i-4]/6;
  }
  if(NRF24L01_TxPacket(ccd)==TX_OK)
  LED_turn(LED0);
}
void convery_ccd1(void)
{
  uint8 i;
  for(i=0;i<32;i++)
  {
    ccd[i]=Loction[i+28]/6;
  }
  if(NRF24L01_TxPacket(ccd)==TX_OK)
  LED_turn(LED1);
}
void convery_ccd2(void)
{
  uint8 i;
  for(i=0;i<32;i++)
  {
    ccd[i]=Loction[i+60]/6;
  }
  if(NRF24L01_TxPacket(ccd)==TX_OK)
  LED_turn(LED2);
}
void convery_ccd3(void)
{
  uint8 i;
  for(i=0;i<28;i++)
  {
    ccd[i]=Loction[i+92]/6;
  }
  for(i=0;i<4;i++)
    ccd[i+28]=0;
  if(NRF24L01_TxPacket(ccd)==TX_OK)
  LED_turn(LED3); 
}
