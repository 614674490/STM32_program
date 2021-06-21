#ifndef __SCI_H__
#define __SCI_H__

#include "common.h"
#include "gpio.h"
#include "ov7725.h"
#define  sci_datalenth  4   //�յ�һ֡�е�����λ
#define  sci_outdatalenth 5
#define Width 160
#define Hight 80
extern void SentIMG(void);
extern u8 sci_indata[6];//���յ�һ֡�������� 6λ={��λ��־λ+��λ����λ}
extern s16 sci_cmd_data[40][3];
//extern void sci_init(UARTn uartn);
extern void sent_frame(s16 dec,u8 function_code,u8 start_flag,u8 stop_flag );
extern void sci_inprocess(void);
extern void sent_image( );
extern void sent_image1(void);
extern void sci_vscope(u8 ch0,u8 ch1,u8 ch2,u8 ch3,u8 ch4);
#endif  //__SCI_H__