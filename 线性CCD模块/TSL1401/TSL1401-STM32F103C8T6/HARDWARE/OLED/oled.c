#include "oled.h"
#include "delay.h"
#include "ssd1331.h"
#include "bank.h"
#include "color.h"
#include "string.h"
#include "ccd.h"
#include "debug.h"
void Screen_Init(void)
{
	ssd1331_display_Chinese(12*1,0,0,MediumOrchid);
	ssd1331_display_Chinese(12*2,0,1,MediumOrchid);
	ssd1331_display_Chinese(12*3,0,2,MediumOrchid);
	ssd1331_display_Chinese(12*4,0,3,MediumOrchid);
	ssd1331_display_Chinese(12*5,0,4,MediumOrchid);
	ssd1331_display_Chinese(12*6,0,5,MediumOrchid);
	
	ssd1331_DrawRectangle(0,38,94,50,Grey,White);//14
	
	ssd1331_display_string(0,51,(u8 *)("TS:"),FONT_1206,RosyBrown,DisOverlay_Display);
	ssd1331_display_string(36,51,(u8 *)("."),FONT_1206,Yellow,DisOverlay_Display);
	ssd1331_display_string(48,51,(u8 *)("MD:"),FONT_1206,RosyBrown,DisOverlay_Display);
	ssd1331_display_string(84,51,(u8 *)("."),FONT_1206,Yellow,DisOverlay_Display);
}
//OLED��ʾCCD��Ϣ
void OLED_Show_CCD(void)
{
	#if !DEBUG_MODE
		#if Single_Line	//��ʱ��ʾ����֮�������,��ֻ��Ӧ����һ������,����ˢ��Ч�ʸ�
			ssd1331_fill_black(0,39,Left_Side*0.75,49,White);
			ssd1331_fill_black(Right_Side*0.75,39,95,49,White);
			ssd1331_fill_black(Left_Side*0.75,39,Right_Side*0.75,49,Black);
		#else	//��ʱ����ԭʼ����,��Ӧʵ�����,����ˢ��Ч�ʵ�
			u8 i;
			for(i = 0;i<128; i++)
					ssd1331_fill_black(i*0.75,39,i*0.75,49,White*(ccd_piexl[i]>Threshold));//12
		#endif
	#endif
	ssd1331_display_number(18,51,Threshold,3,FONT_1206,Golden,DisOverlay_Display);
	ssd1331_display_number(40,51,(Threshold-(u8)Threshold)*10,1,FONT_1206,Golden,DisOverlay_Display);
	ssd1331_display_number(66,51,Median,3,FONT_1206,Golden,DisOverlay_Display);
	ssd1331_display_number(88,51,(Median-(u8)Median)*10,1,FONT_1206,Golden,DisOverlay_Display);
}
/**
 *	��ɫ
 *	�ٴ����������ɫ��Ч
**/
void ssd1331_set_color(ColorType Color)
{
	Write_Data(Color>>8); //RRRRRGGG
	Write_Data(Color);		//GGGBBBBB
}
/*
********************************************************************************
*	�� �� ��: ssd1331_draw_point
*	����˵��: ��ָ��λ�û�1�����ص�
*	��    ��:
*	chXpos,chYpos : ��������
*	hwColor  ��������ɫ
*	�� �� ֵ: ��
********************************************************************************
*/
void ssd1331_draw_point(uint8_t chXpos, uint8_t chYpos, ColorType hwColor) 
{
	if (chXpos >= Max_Column || chYpos >= Max_Row) 
	{
		return;
	}
  //set column point
  Set_Column_Address(chXpos,chXpos);	//������ʼ�ͽ���COLUMN��ַ
  //set row point
  Set_Row_Address(chYpos,chYpos);			//���ָ��������ʼ�ͽ���ROW��ַ
  //fill 16bit colour
	ssd1331_set_color(hwColor);
}
/*
********************************************************************************
*	�� �� ��: ssd1331_clear_screen
*	����˵��: ָ����ɫ����
*	��    ��:
*	Color  ��������ɫ
*	�� �� ֵ: ��
********************************************************************************
*/
void ssd1331_clear_screen(ColorType Color)  
{
	Fill_RAM(Color>>8,Color);
}
/*
********************************************************************************
*	�� �� ��: ssd1331_clear_screen
*	����˵��: �����
*	��    ��:
*	Color  ��������ɫ
*	�� �� ֵ: ��
********************************************************************************
*/
void ssd1331_fill_black(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2,ColorType Color)  
{
	Fill_Block(_usX1,_usX2,_usY1,_usY2,Color>>8,Color);
}
/*
********************************************************************************
*	�� �� ��: ssd1331_clear_screen
*	����˵��: �鸴��
*	��    ��:
*	�� �� ֵ: ��
********************************************************************************
*/
void ssd1331_copy(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 ,uint16_t _usY2,uint16_t _usX3 , uint16_t _usY3) 
{
	copy(_usX1,_usY1,_usX2,_usY2,_usX3,_usY3);
}
/*
********************************************************************************
*	�� �� ��: ssd1331_DrawLine
*	����˵��: ���� Bresenham �㷨����2��仭һ��ֱ�ߡ�
*	��    ��:
*	_usX1, _usY1 ����ʼ������
*	_usX2, _usY2 ����ֹ��Y����
*	_ucColor  ��������ɫ
*	�� �� ֵ: ��
********************************************************************************
*/
void ssd1331_DrawLine(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2 , ColorType _ucColor)
{
	int32_t dx , dy ;
	int32_t tx , ty ;
	int32_t inc1 , inc2 ;
	int32_t d , iTag ;
	int32_t x , y ;

	/* ���� Bresenham �㷨����2��仭һ��ֱ�� */

	ssd1331_draw_point(_usX1 , _usY1 , _ucColor);

	/* ��������غϣ���������Ķ�����*/
	if ( _usX1 == _usX2 && _usY1 == _usY2 )
	{
		return;
	}

	iTag = 0 ;
	/* dx = abs ( _usX2 - _usX1 ); */
	if (_usX2 >= _usX1)
	{
		dx = _usX2 - _usX1;
	}
	else
	{
		dx = _usX1 - _usX2;
	}

	/* dy = abs ( _usY2 - _usY1 ); */
	if (_usY2 >= _usY1)
	{
		dy = _usY2 - _usY1;
	}
	else
	{
		dy = _usY1 - _usY2;
	}

	if ( dx < dy )   /*���dyΪ�Ƴ������򽻻��ݺ����ꡣ*/
	{
		uint16_t temp;
		iTag = 1 ;
		temp = _usX1; _usX1 = _usY1; _usY1 = temp;
		temp = _usX2; _usX2 = _usY2; _usY2 = temp;
		temp = dx; dx = dy; dy = temp;
	}
	tx = _usX2 > _usX1 ? 1 : -1 ;    /* ȷ������1���Ǽ�1 */
	ty = _usY2 > _usY1 ? 1 : -1 ;
	x = _usX1 ;
	y = _usY1 ;
	inc1 = 2 * dy ;
	inc2 = 2 * ( dy - dx );
	d = inc1 - dx ;
	while ( x != _usX2 )     /* ѭ������ */
	{
		if ( d < 0 )
		{
			d += inc1 ;
		}
		else
		{
			y += ty ;
			d += inc2 ;
		}
		if ( iTag )
		{
			ssd1331_draw_point ( y , x , _ucColor) ;
		}
		else
		{
			ssd1331_draw_point ( x , y , _ucColor) ;
		}
		x += tx ;
	}
}
//������
void ssd1331_draw_v_line(uint8_t chXpos, uint8_t chYpos, uint8_t chHeight, ColorType hwColor)
{	
	uint16_t i, y1 = MIN(chYpos + chHeight, Max_Row - 1);

	if (chXpos >= Max_Column || chYpos >= Max_Row) {
		return;
	}
	
    for (i = chYpos; i < y1; i ++) {
        ssd1331_draw_point(chXpos, i, hwColor);
    }
}
//������
void ssd1331_draw_h_line(uint8_t chXpos, uint8_t chYpos, uint8_t chWidth, ColorType hwColor)
{	
	uint16_t i, x1 = MIN(chXpos + chWidth, Max_Column- 1);

	if (chXpos >= Max_Column || chYpos >= Max_Row) {
		return;
	}
	
    for (i = chXpos; i < x1; i ++) {
        ssd1331_draw_point(i, chYpos, hwColor);
    }
}
/*
********************************************************************************
*	�� �� ��: ssd1331_DrawRectangle
*	����˵��: ����һ������(�����)
*	��    ��:
*	_usX, _usY ��Բ������
*	_usRadius ���뾶
*	_ucColor  ��������ɫ
*	�� �� ֵ: ��
********************************************************************************
*/
void ssd1331_DrawRectangle(uint16_t _usX1 , uint16_t _usY1 , uint16_t _usX2 , uint16_t _usY2, ColorType _lineColor,ColorType _areaColor)
{
	Draw_Rectangle(_usX1,_usY1,_usX2,_usY2,_lineColor>>11,_lineColor>>5&0x1f,_lineColor&0x1f,_areaColor>>11,_areaColor>>5&0x1f,_areaColor&0x1f);
}
/*
********************************************************************************
*	�� �� ��: ssd1331_DrawCircle
*	����˵��: ����һ��Բ��
*	��    ��:
*	_usX, _usY ��Բ������
*	_usRadius ���뾶
*	_ucColor  ��������ɫ
*	�� �� ֵ: ��
********************************************************************************
*/
void ssd1331_DrawCircle(uint16_t _usX, uint16_t _usY, uint16_t _usRadius, ColorType _ucColor)
{
	int32_t  D;			/* Decision Variable */
	uint32_t  CurX;	/* ��ǰ X ֵ */
	uint32_t  CurY;	/* ��ǰ Y ֵ */
	
	D = 3 - (_usRadius << 1);
	CurX = 0;
	CurY = _usRadius;
	
	while (CurX <= CurY)
	{
		ssd1331_draw_point(_usX + CurX, _usY + CurY, _ucColor);
		ssd1331_draw_point(_usX + CurX, _usY - CurY, _ucColor);
		ssd1331_draw_point(_usX - CurX, _usY + CurY, _ucColor);
		ssd1331_draw_point(_usX - CurX, _usY - CurY, _ucColor);
		ssd1331_draw_point(_usX + CurY, _usY + CurX, _ucColor);
		ssd1331_draw_point(_usX + CurY, _usY - CurX, _ucColor);
		ssd1331_draw_point(_usX - CurY, _usY + CurX, _ucColor);
		ssd1331_draw_point(_usX - CurY, _usY - CurX, _ucColor);
	
		if (D < 0)
		{
			D += (CurX << 2) + 6;
		}
		else
		{
			D += ((CurX - CurY) << 2) + 10;
			CurY--;
		}
		CurX++;
	}
}
/*
********************************************************************************
*	�� �� ��: ssd1331_display_char
*	����˵��: ��ʾһ���ַ�
*	��    ��:
*	chXpos, chXpos ���������(����)
*	chChr  ���ַ�
*	chSize ���ַ���С
*	hwColor��������ɫ
* mode   ��1:���ӷ�ʽ 0:�ǵ��ӷ�ʽ
*	�� �� ֵ: ��
********************************************************************************
*/
void ssd1331_display_char(uint8_t chXpos, uint8_t chYpos, uint8_t chChr, uint8_t chSize, ColorType hwColor,uint8_t mode)
{       
	uint8_t i, j, chSize1;
	uint8_t chYpos0 = chYpos; //��¼��ʼ��
	unsigned char *PtrData=NULL,chTemp;

	if (chXpos >= Max_Column || chYpos >= Max_Row) 
	{
		return;
	}
	switch (chSize)
	{
		case FONT_1206 :
		{
			PtrData = &oled_asc2_1206[chChr - 0x20][0]; 
			chSize1= chSize;	
			break;
		}
		case FONT_1608 :
		{
			PtrData = &oled_asc2_1608[chChr - 0x20][0]; 
			chSize1= chSize;	
			break;
		}
		case FONT_1612 :
		{
			PtrData = &oled_asc2_1612[chChr - 0x30][0]; 
			chSize1= 16;	
			break;
		}
		case FONT_3216 :
		{
			PtrData = &oled_asc2_3216[chChr - 0x30][0]; 
			chSize1= 32;	
			break;
		}
	}
//				��j��
//        --------------->| ��i��	
//        --------------->|	
//        --------------->|	
//              .				  .	
//         		  .				  .	
//         			.				  .	
//        --------------->|	
//                        ��	
//          	
	PtrData--;
  for (i = 0; i < chSize; i ++) //����Ϊ��λ ����������												
	{			                                                                
		PtrData++;    
		chTemp = *PtrData;		
    for (j = 0; j < 8*sizeof(char); j ++)//ÿ����ֵռ8bit ����0x__            
		{ 
			if (chTemp& 0x80)                                                
			{                                                                     
				ssd1331_draw_point(chXpos, chYpos, hwColor);                        
			}           
			else if(mode==0)
				ssd1331_draw_point(chXpos,chYpos,Black);
			chTemp <<= 1; //��λ��ǰ ��λ�ں� ��ֵ�������������е�ǰ�еı�����ʾ    
			chYpos ++;    //���ۼ� ÿһλ������֮�󶼻�ռ��OLED��1�����ص�
			
			if ((chYpos - chYpos0) == chSize1) //ÿ��chSize�� ��n�б������
			{
				chYpos = chYpos0; //��ֵ�ָ���ֵ
				chXpos ++;				//����+1 
				break;						//�˳���ǰ��ɨ��ѭ�� ��ʼ������һ��ɨ�� �˾�ִ�д�������chSize���� ����ѭ�������޹�
			}
			
		}  	 
  } 
}
/* ��ʾ�ַ��� */
void ssd1331_display_string(uint8_t chXpos, uint8_t chYpos, uint8_t *pchString, uint8_t chSize, ColorType hwColor,uint8_t mode)
{
	uint8_t chXpos0=chXpos;
	if (chXpos >= Max_Column || chYpos >= Max_Row) 
	{
		return;
	}
  while (*pchString != '\0') 
	{
		if (chXpos > (Max_Column - chSize / 2)) 
		{
			chXpos = 0;
			chYpos += chSize;
			if (chYpos > (Max_Row - chSize))
			{
				chYpos = chXpos = 0;
				Clear_Screen;
			}
		}
		if(*pchString=='\n')//���з���
	  {         
	    chYpos+=chSize;
			chXpos=chXpos0;
		  pchString++; 
	  }
		else
		{
			ssd1331_display_char(chXpos, chYpos, *pchString, chSize, hwColor,mode);
			pchString ++; 
			chXpos += chSize / 2;
		}
	} 
}
//����Ļ��������ʾ�ַ��� �����ACSII��
void ssd1331_display_string_screen_center(uint16_t Width,uint16_t Height,uint8_t *pchString, uint8_t chSize, ColorType hwColor,uint8_t mode)
{
	uint8_t chYpos,chXpos;
	uint16_t length = strlen((char *)(pchString))*(chSize/2);
	uint16_t height = chSize;
	if(length<Width)  //�ܳ��Ȳ��ᳬ����Ļ���
	{
		chYpos = (Height-height)/2;
		chXpos = (Width - length)/2;
		ssd1331_display_string(chXpos,chYpos,pchString,chSize,hwColor,mode);
	}
	else
	{
		if((length)%(Width))
			height=(length)/(Width)*chSize+chSize;
		else
			height=(length)/(Width)*chSize;
		chXpos=0;
		chYpos = (Height - height)/2;
		ssd1331_display_string(chXpos,chYpos,pchString,chSize,hwColor,mode);
	}
}
/* ��ʾ�������� */
void ssd1331_display_Chinese(uint8_t chXpos, uint8_t chYpos, uint8_t no, ColorType hwColor)
{
	uint8_t i, j;
	uint8_t Temp = 0, chYpos0 = chYpos;

	for (i = 0; i < 24; i ++) 
	{
		Temp = HEBUST[no][i];
		for (j = 0; j < 8; j ++) 
		{
			if (Temp & 0x80) 
			{
				ssd1331_draw_point(chXpos, chYpos, hwColor);
			}
			Temp <<= 1;
			chYpos ++;
			if ((chYpos - chYpos0) == 16) 
			{
				chYpos = chYpos0;
				chXpos ++;
				break;
			}
		}
	}
}
//m^n����
u32 ssd1331_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void ssd1331_display_number(u8 x,u8 y,u32 num,u8 len,u8 size,ColorType Color,uint8_t mode)
{
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/ssd1331_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				ssd1331_display_char(x+(size/2)*t,y,' ',size,Color,mode);
				continue;
			}else enshow=1; 
		 	 
		}
	 	ssd1331_display_char(x+(size/2)*t,y,temp+'0',size,Color,mode); 
	}
} 
/*
********************************************************************************
*	�� �� ��: ssd1331_draw_bitmap
*	����˵��: ��ָ��λ�û�һ��ͼƬ ��ʾ�ڰ�ͼ ��ɫ�Զ���
*	��    ��:
*	chXpos,chYpos : ��������
*	pchBmp������ָ��
*	chWidth,chHeight��ͼƬ��С
*	hwColor  ��������ɫ
*	�� �� ֵ: ��
* ˵    ����ȡģ�������pctolcd2002��ͼƬ��С�����½�ͼƬʱͼƬ�Ŀ�Ⱥ͸߶�
*	ȡģ��ʽ������ʽ��˳��
********************************************************************************
*/
void ssd1331_draw_bitmap(uint8_t *pchBmp,uint8_t chXpos, uint8_t chYpos, ColorType hwColor)
{
	uint16_t chWidth = *pchBmp;
	uint16_t chHeight = *(pchBmp+1);
	uint8_t *pchTemp = pchBmp+2;
	uint16_t i, j, byteWidth = (chWidth + 7) / 8;

  for(j = 0; j < chHeight; j ++)
	{
    for(i = 0; i < chWidth; i ++ ) 
		{
			if(*(pchTemp + j * byteWidth + i / 8) & (128 >> (i & 7))) /* �����ж���ģ����Щλ��1��������Ӧ��ɫ���� */
			{
				ssd1331_draw_point(chXpos + i, chYpos + j, hwColor);
      }
    }
  }
}
//��ʾԭͼ
void ssd1331_draw_64Kpattern(uint8_t *pchBmp,uint8_t chXpos, uint8_t chYpos)
{
	Show_64k_Pattern(pchBmp+2,chXpos,chXpos+(*pchBmp)-1,chYpos,chYpos+(*(pchBmp+1))-1);
}
void ssd1331_vertical_scroll(uint8_t scrollingDirection, uint8_t row_perStep, uint16_t timeStepms)
{
	Vertical_Scroll(scrollingDirection,row_perStep,timeStepms);
}
void OLED_Init(void)
{
  unsigned char i;
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	 
 	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);	

 #if OLED_MODE==1
 
 	GPIO_InitStructure.GPIO_Pin =0xFF; 
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,0xFF); 

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;			
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOG,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);						

 #else
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_8;			
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1| GPIO_Pin_8);						

 #endif
	OLED_RST_Clr();
	for(i=0;i<250;i++)
	{
		uOLED_Delay(250);
	}
	OLED_RST_Set();
  Set_Display_On_Off(0x00);		    													// Display Off (0x00/0x01)
	Set_Remap_Format(0x72);																		// Set Horizontal Address Increment  0x72(rgb)0x74(bgr)
	Set_Start_Line(0x00);			           										 	// Set Mapping RAM Display Start Line (0x00~0x3F)
	Set_Display_Offset(0x00);		            									// Shift Mapping RAM Counter (0x00~0x7F)
	Set_Display_Mode(0x00);			       			 									// Normal Display Mode (0x00/0x01/0x02/0x03)
	Set_Multiplex_Ratio(0x3F);		            								// 1/128 Duty (0x0F~0x7F)
	Set_Master_Configuration(0x8e);            								// set master configuration
	Set_Power_Saving_Mode(0x0b);              	 							// set power save
	Set_Reset_Pre_charge_period(0x31);         								// phase 1 and 2 period adjustment
	Set_Oscillator_Frequency_Clock_Divider(0xf0);							// display clock divider / oscillator frequency
	Set_Second_Pre_charge_Speed_of_Color(0x64, 0x78, 0x64);		// Set Second Pre-change Speed For Color
	Set_Pre_charge_Level(0x3a);                								// Set Pre-Change Level
	Set_VCOMH(0x3e);			               											// Set Common Pins Deselect Voltage Level as 0.82*VCC
	Set_Master_Current(0x06);	        												// Set Scale Factor of Segment Output Current Control	 Brightness
  Set_Contrast_Color(0x91,0x50,0x7d);												// Set Contrast of Color A (Red) B (Green) C (Blue)	                 
  Set_Display_On_Off(0x01);		        											// Display On (0x00/0x01)
	//Fill_Enable_Disable(1);																		// Enable Fill	
	Fill_RAM(0x00,0x00);			        												// Clear Screen
}

