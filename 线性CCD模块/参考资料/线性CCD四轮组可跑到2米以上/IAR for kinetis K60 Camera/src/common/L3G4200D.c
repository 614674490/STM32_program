#include "common.h"
#include "L3G4200D.h"


  /*******************************/
void DATA_printf(uchar *s,short temp_data)
{   float temp_dis;
    temp_dis=(float)temp_data*0.07;  //ת���ɵ�λ  ��/��
	temp_data=(int)temp_dis;
	if(temp_data<0){
	temp_data=-temp_data;
    *s='-';
	}
	else *s=' ';
    *++s =temp_data/100+0x30;
    temp_data=temp_data%100;     //ȡ������
    *++s =temp_data/10+0x30;
    temp_data=temp_data%10;      //ȡ������
    *++s =temp_data+0x30; 	
}

