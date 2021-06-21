
#ifndef __5110_H__
#define __5110_H__
/************************************************************************
*   ��Ҫʹ�õĺ���

*    ��ʾһ������0<x<14  0<Y<6
     LCD_printc_my(unsigned char x, unsigned char y, unsigned char c_dat)��

*    ��ʾһ����ĸ0<x<14  0<Y<6
     void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat)
      ����LCD_printc(unsigned char x, unsigned char y, 'A')

*   ��ʾһ��0-255����0<x<14  0<Y<6   ����ռ3λ
    LCD_display_8int(unsigned char x, unsigned char y, unsigned char c_dat) ;

*   ��ʾһ��0-65535����0<x<14  0<Y<6 ����ռ5λ
   LCD_display_16int(unsigned char x, unsigned char y, unsigned int c_dat);


*  
*  ��    ע��
*************************************************************************/

#include "common.h"
#include "gpio.h"

//*******************5110Һ������*********************************
#define LCD_CLK_HIGH()          gpio_set (PORTA, 25, 1)
#define LCD_CLK_LOW()     	gpio_set (PORTA, 25, 0)

#define LCD_DIN_HIGH()    	gpio_set (PORTA, 26, 1)
#define LCD_DIN_LOW()      	gpio_set (PORTA, 26, 0)

#define LCD_DC_HIGH()      	gpio_set (PORTA, 27, 1)
#define LCD_DC_LOW()      	gpio_set (PORTA, 27, 0)

#define LCD_CS_HIGH()      	gpio_set (PORTA, 28, 1)
#define LCD_CS_LOW()     	gpio_set (PORTA, 28, 0)

#define LCD_RST_HIGH()     	gpio_set (PORTA, 29, 1)
#define LCD_RST_LOW()      	gpio_set (PORTA, 29, 0)


/*--------------------------------------------------------------*/
//ָ��궨��
#define X_Col_Addr     0x80		//��λ����0��ָ��(����ʼ��ַ)(0 - 83)
#define Y_Page_Addr    0x40		//��λ����0ҳָ��(ҳ��ʼ��ַ)(0 - 5)

/*--------------------------------------------------------------*/
//���ܺ궨��
//Һ����λ
#define LCD_reset_hard	LCD_RST_LOW(); LCD_RST_HIGH()	//Ӳ����λ

//�������
#define LCD_write_cmd(cmd)	LCD_write_byte(cmd, 0)	//д��ָ��
#define LCD_write_dat(dat)	LCD_write_byte(dat, 1)	//д������

/*--------------------------------------------------------------*/
//��������
void LCD_write_byte(unsigned char wbyte, unsigned char dat_cmd);//д���ֽ�
//��������(��DDRAM)
void LCD_clr_scr(void);
/*--------------------------------------------------------------*/
//��ʾ����
//num:	0 - 5
void LCD_clr_row(unsigned char num);
/*--------------------------------------------------------------*/
//Һ���ֽڶ�λ(1*1)
//Һ���滮:
//x: 0 - 83
//y: 0 - 5
int LCD_pos_byte(int x, int y);
//��ʾ����
void LCD_display_16int(unsigned char x, unsigned char y, unsigned int c_dat);
void LCD_display_8int(unsigned char x, unsigned char y, unsigned char c_dat) ;
/*--------------------------------------------------------------*/
//Һ���ַ����(6*8����)
//x: 0 - 13
//y: 0 - 5
void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat);
void LCD_printc_my(unsigned char x, unsigned char y, unsigned char c_dat);
/*--------------------------------------------------------------*/
//Һ���ַ������(6*8����)
//x: 0 - 13
//y: 0 - 5
void LCD_prints(unsigned char x, unsigned char y, unsigned char *s_dat);

/*--------------------------------------------------------------*/
//��ʼ��LCD5110
void LCD5110_Init(void);				
/*--------------------------------------------------------------*/

#endif

