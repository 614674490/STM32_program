#include "adc.h"
#define TSL_SI    PAout(3)   //SI  
#define TSL_CLK   PAout(2)   //CLK 
/**************************************************************************
函数功能：延时
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void Dly_us(void)
{
   int ii;    
   for(ii=0;ii<10;ii++);      
}
/**************************************************************************
函数功能：CCD数据采集 连续曝光法
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
 void RD_TSL(void) 
{
 u8 i=0,tslp=0;
  TSL_CLK=1;
  TSL_SI=0; 		//产生第129个CLK以结束本次采样
  Dly_us();			
      
  TSL_SI=1; 
  TSL_CLK=0;
  Dly_us();
      
  TSL_CLK=1;
  TSL_SI=0;
  Dly_us(); 
  for(i=0;i<128;i++)//在每个CLK下降沿时采集一个像素 共采集128个像素
  { 
    TSL_CLK=0; 
    Dly_us();  //调节曝光时间
		Dly_us();  //调节曝光时间
    ADV[tslp]=(Get_Adc(8))>>4;
    ++tslp;
    TSL_CLK=1;
     Dly_us();
  }  
}
/**************************************************************************
函数功能：ACD初始化电池电压检测
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void  Adc_Init(void)
{    
  //先初始化IO口
 	RCC->APB2ENR|=1<<3;    //使能PORTb口时钟 
	GPIOB->CRL&=0XFFFFFFF0;//PB1 anolog输入 
	RCC->APB2ENR|=1<<9;    //ADC1时钟使能	  
	RCC->APB2RSTR|=1<<9;   //ADC1复位
	RCC->APB2RSTR&=~(1<<9);//复位结束	    
	RCC->CFGR&=~(3<<14);   //分频因子清零	
	//SYSCLK/DIV2=12M ADC时钟设置为12M,ADC最大时钟不能超过14M!
	//否则将导致ADC准确度下降! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //工作模式清零
	ADC1->CR1|=0<<16;      //独立工作模式  
	ADC1->CR1&=~(1<<8);    //非扫描模式	  
	ADC1->CR2&=~(1<<1);    //单次转换模式
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //软件控制转换  
	ADC1->CR2|=1<<20;      //使用用外部触发(SWSTART)!!!	必须使用一个事件来触发
	ADC1->CR2&=~(1<<11);   //右对齐	 
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1&=0<<20;     //1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道4的采样时间
	ADC1->SMPR2&=0XFFFFFF0F; //采样时间清空	  
	ADC1->SMPR2|=7<<3;      // 239.5周期,提高采样时间可以提高精确度	 

	ADC1->CR2|=1<<0;	    //开启AD转换器	 
	ADC1->CR2|=1<<3;        //使能复位校准  
	while(ADC1->CR2&1<<3);  //等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC1->CR2|=1<<2;        //开启AD校准	   
	while(ADC1->CR2&1<<2);  //等待校准结束 
}		

/**************************************************************************
函数功能：AD采样
入口参数：ADC1 的通道
返回  值：AD转换结果
**************************************************************************/
u16 Get_Adc(u8 ch)   
{
	//设置转换序列	  		 
	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //启动规则转换通道 
	while(!(ADC1->SR&1<<1));//等待转换结束	 	   
	return ADC1->DR;		//返回adc值	
}

/**************************************************************************
函数功能：读取电池电压 
入口参数：无
返回  值：电池电压 
**************************************************************************/
int Get_battery_volt(void)   
{  
	int Volt;//电池电压
	Volt=Get_Adc(Battery_Ch)*3.3*11*100/4096;	//电阻分压，具体根据原理图简单分析可以得到	
	return Volt;
}

/**************************************************************************
函数功能：CCD数据采集
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void CCD(void)   
{  
	int i,j;
	usart1_send(0xff);			
   for(i=0; i<100;i++) 
  { 
    RD_TSL();           
   	j=0;
		for(j=0;j<128;j++)
		{
    if(ADV[j] ==0XFF)  ADV[j]--;    
    usart1_send(ADV[j]);
    }   
	}
}
/**************************************************************************
函数功能：线性CCD初始化
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void  ccd_Init(void)
{    
//先初始化IO口
	RCC->APB2ENR|=1<<2;    //使能PORTA口时钟 
 	RCC->APB2ENR|=1<<3;    //使能PORTB口时钟 
	GPIOB->CRL&=0XFFFFFFF0;//PB0 anolog输入 	 
 	 
	GPIOA->CRL&=0XFFFF00FF;//PA2 3 
	GPIOA->CRL|=0X00002200;//PA2 3 推挽输出 2MHZ   
	 
	RCC->APB2ENR|=1<<9;    //ADC1时钟使能	  
	RCC->APB2RSTR|=1<<9;   //ADC1复位
	RCC->APB2RSTR&=~(1<<9);//复位结束	    
	RCC->CFGR&=~(3<<14);   //分频因子清零	
	//SYSCLK/DIV2=12M ADC时钟设置为12M,ADC最大时钟不能超过14M!
	//否则将导致ADC准确度下降! 
	RCC->CFGR|=2<<14;      	 

	ADC1->CR1&=0XF0FFFF;   //工作模式清零
	ADC1->CR1|=0<<16;      //独立工作模式  
	ADC1->CR1&=~(1<<8);    //非扫描模式	  
	ADC1->CR2&=~(1<<1);    //单次转换模式
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //软件控制转换  
	ADC1->CR2|=1<<20;      //使用用外部触发(SWSTART)!!!	必须使用一个事件来触发
	ADC1->CR2&=~(1<<11);   //右对齐	 
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1&=0<<20;     //1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道7的采样时间
	ADC1->SMPR2&=0XF0FFFFFF;//通道8采样时间清空	  
	ADC1->SMPR2|=7<<24;      //通道8  239.5周期,提高采样时间可以提高精确度	 

	ADC1->CR2|=1<<0;	    //开启AD转换器	 
	ADC1->CR2|=1<<3;        //使能复位校准  
	while(ADC1->CR2&1<<3);  //等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC1->CR2|=1<<2;        //开启AD校准	   
	while(ADC1->CR2&1<<2);  //等待校准结束
	delay_ms(1);
}		


/**************************************************************************
函数功能：电磁传感器采样初始化
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void  ele_Init(void)
{    
//先初始化IO口
	RCC->APB2ENR|=1<<2;    //使能PORTA口时钟 
 	RCC->APB2ENR|=1<<3;    //使能PORTB口时钟 
	GPIOB->CRL&=0XFFFFFFF0;//PB0 anolog输入 	 
	GPIOA->CRL&=0XFFFF00FF;//PA2 3 
   
	 
	RCC->APB2ENR|=1<<9;    //ADC1时钟使能	  
	RCC->APB2RSTR|=1<<9;   //ADC1复位
	RCC->APB2RSTR&=~(1<<9);//复位结束	    
	RCC->CFGR&=~(3<<14);   //分频因子清零	
	//SYSCLK/DIV2=12M ADC时钟设置为12M,ADC最大时钟不能超过14M!
	//否则将导致ADC准确度下降! 
	RCC->CFGR|=2<<14;      	 

	ADC1->CR1&=0XF0FFFF;   //工作模式清零
	ADC1->CR1|=0<<16;      //独立工作模式  
	ADC1->CR1&=~(1<<8);    //非扫描模式	  
	ADC1->CR2&=~(1<<1);    //单次转换模式
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //软件控制转换  
	ADC1->CR2|=1<<20;      //使用用外部触发(SWSTART)!!!	必须使用一个事件来触发
	ADC1->CR2&=~(1<<11);   //右对齐	 
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1&=0<<20;     //1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道7的采样时间
	ADC1->SMPR2&=0XF0FF00FF;//通道8采样时间清空	  
	ADC1->SMPR2|=7<<24;      //通道8  239.5周期,提高采样时间可以提高精确度	 

	ADC1->CR2|=1<<0;	    //开启AD转换器	 
	ADC1->CR2|=1<<3;        //使能复位校准  
	while(ADC1->CR2&1<<3);  //等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC1->CR2|=1<<2;        //开启AD校准	   
	while(ADC1->CR2&1<<2);  //等待校准结束
	delay_ms(1);
}		


