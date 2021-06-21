
#define   dsp  0  //�Ƿ�ʹ��DSP���� 0Ϊ��ʹ��DSP
#define   white_num 100
#include "common.h"
#include "include.h"
#include "sci.h"
#include "delay.h"
#include "ov7725.h"
#include "imgprocess.h"
#include "globle.h"
#include "math.h"
#include "control.h"

#define h   CAMERA_H-1
#define w   CAMERA_W-1
void Direct_output();
u8 track_center(u16 (*white_array)[white_num],u16 *center,u8 *type);
u8 last[3]={1,1,40}; 
u16 output=80;
/**************************************����**********************************************************/
#if imgshow
u8 sobel(u8 (*img)[CAMERA_W],u16 tresh,u16 *center,u16 *set,u8 *type)
{
   u16 r;
   u16 cnt_white[w]={0};
   u16 white_array[CAMERA_H][white_num];
   u16 c,hi;
   int sum[h][20][1]={0};  //��¼ÿһ���������ĺ�
   int geshu[h][20][1]={0}; //��¼ÿһ�������ĸ���
   int zushu[h]={0};   //��¼ÿһ������������
   u16 i;
   int cnt_center[h]={0};//ȥ���ÿһ�����õ������������
   u16 cnt_zeroline=0;
   u16 cnt_oneline=0;          
   u16 cnt_twoline=0; 
   u16 cnt_threeline=0;
   u16 cnt_fourline=0;
   u16 center_oneline=0;
   u16 center_twoline=0;
   static  u16 cnt_cor=0;
#if dsp
  float fx,fy,grad;
  float x[9]={-1,0,1,-2,0,2,-1,0,1};
  float y[9]={1,2,1,0,0,0,-1,-2,-1};
#else 
  int fx,fy,grad;
#endif
 
 
#if dsp
    arm_matrix_instance_f32 xm = {9, 1, (float *)x}; 
    arm_matrix_instance_f32 fxm = {1, 1, &fx};
     arm_matrix_instance_f32 ym = {9, 1, y}; 
     arm_matrix_instance_f32 fym = {1, 1, &fy};
#endif
  for(c=1;c<h;c++)
  {
    cnt_white[c]=0;
    for(r=1;r<w;r++ )
    {  
#if dsp
       arm_matrix_instance_f32 imgm = {1, 9, (float *)(img-4)}; 
       arm_mat_mult_f32(&imgm,&xm,&fxm);
       arm_mat_mult_f32(&imgm,&ym,&fym);
#else
    fx=(int)(img[c+1][r-1])+((int)img[c+1][r])*2+(int)img[c+1][r+1]-(int)img[c-1][r-1]-((int)img[c-1][r])*2-(int)img[c-1][r+1];
    fy=(int)img[c-1][r+1]+((int)img[c][r+1])*2+(int)img[c+1][r+1]-(int)img[c-1][r-1]-((int)img[c][r-1])*2-(int)img[c+1][r-1];
#endif
     if(fx<0)
     {
       fx=-fx;
        
     }
     if(fy<0)
     {
        fy=-fy;
     }
     grad=fx+fy;
     
     if(grad>=tresh)
     {

  
      white_array[c][cnt_white[c]++]=r;  
      
     
     }
   
     
     
     
     

  
    
  } //end for for(r=1;r<w;r++)
  
} //end for for(c=1;c<h;c++)

//track_center(white_array,center,type);
for(c=1;c<h;c++)
  { 
    zushu[c]=0;
    for(hi=1;hi<cnt_white[c]+1;hi++)
    {
     
      if( white_array[c][hi+1]-white_array[c][hi]<=2)//�����������������2������Ϊ������������
      {
       sum[c][ zushu[c] ][0]+=white_array[c][hi];
       geshu[c][ zushu[c] ][0]++;
       
      }
      
      else
      {
        //uart_putchar(UART4,(u8)geshu[c][ zushu[c] ][0]);
        sum[c][ zushu[c] ][0]+=white_array[c][hi];
        geshu[c][ zushu[c]][0]++;
        zushu[c]++;
      }
       
      
      
      
      
    }// end for(h=0;h<20;h++)
  } //end for(c=0;c<CAMERA_H;i++
  
  
  /********************* ȥ��ֻ��һ����������������ֻ��һ������㣬����¼ÿһ����Ч�����������*********************************************/
  for(c=1;c<h;c++)
  { 
    cnt_center[c]=0;
    for(i=0;i<zushu[c]+1;i++)
    {
      
    if(geshu[c][i][0]>0)
     {
       sum[c][ cnt_center[c] ][0]=sum[c][i][0]; //��ȥ���
       geshu[c][ cnt_center[c] ][0] =geshu[c][i][0];
        cnt_center[c]++;//ȡ��ÿһ�����õĵ������
      
     }
    
      
     }
   //uart_putchar(UART4,(u8)cnt_center[c]);
   }
  
  /***************************����ÿһ�е���Ч�����������*****************************************/
  *center=0;
  for(c=5;c<h;c++)
  {
     if(cnt_center[c]==0)
    {
   
    
    
     cnt_zeroline++;

     }
    
    
     else if(cnt_center[c]==1)
    {
      cnt_oneline++;
      center_oneline+= (u16)sum[c][0][0]/(geshu[c][0][0]);
     }
    
    
    else if(cnt_center[c]==2)
    {
   
    
     center_twoline+= (u16)   ( (sum[c][0][0]/(geshu[c][0][0])  )  +  ( sum[c][1][0]/(geshu[c][1][0]))  )/2 ;
     
     cnt_twoline++;

     }
    
    else if(cnt_center[c]==3)
    {
   
    

     
     cnt_threeline++;

     }
     
     else if (cnt_center[c]==4)
    {
   
    
    
     cnt_fourline++;
 
     }
  
        
 }// end for(c=1;c<h;c++)
 
/*********************************************************************************************/
 
 if(cnt_twoline<10 && *type == 10)
 {
   cnt_cor++;
   
   if(cnt_cor>2)
   {
     cnt_cor=0;
     if(*center<*set)
     {
      *type=20;  //��ת
        *center=center_twoline/cnt_twoline;
     }
    else
     {
       *type=30;   //��ת
       *center=center_twoline/cnt_twoline;
    }
   }
 
 }
 
 
 
 
 else if (*type==20)
 {
   if(cnt_zeroline>10)
   {
     *type=21;
     resetpd();
  
   }
   else 
   {
     
   *center=center_twoline/cnt_twoline;
   }
   
 }
 
 
  else if (*type==30)
 {
   if(cnt_twoline<2)
   {
     *type=31;
     resetpd();
  
   }
   else 
   {
     
   *center=center_twoline/cnt_twoline;
   }
   
 }
 
 else if (*type==21 || *type==31)
 {
   *center=center_oneline/cnt_oneline;
   if(cnt_twoline>20)
   {
     *type=10; 
   }
 }
 
 

 
 else if(*type==10)
 {
   *center=center_twoline/cnt_twoline;
   *type=10;  //ֱ��
 }
 
 //uart_putchar(UART4,(u8)*center);
 //cnt_oneline=0;
// cnt_twoline=0;
 //cnt_threeline=0;
 //cnt_fourline=0;
  
  
 return 1;
}




/***********************************************************���㷨   ���䷨**********************************************************/


u8 type_detect(u8 (*img)[CAMERA_W],u16 tresh,u16 *center,u16 *set,u8 *type)
{
   u16 r;
   u16 c,wi;
   u16 geshu[CAMERA_H]={0};
   u16 line[CAMERA_H][6]={0};
   u16 cnt[CAMERA_H]={0};
   u16 i=1;
   u16 cnt_zeroline=0;
   u16 cnt_oneline=0;          
   u16 cnt_twoline=0; 
   u16 cnt_threeline=0;
   u16 cnt_fourline=0;
   u16 center_oneline=0;
   u16 center_twoline=0;
   static  u16 cnt_cor=0;
   wi=CAMERA_W-3;
   
   //�����ԵѰ��
   for(c=0;c<CAMERA_H;c++)
   {
     cnt[c]=0;
     for(r=0;r<wi;r++)
     {
      
         
         if(i%2) //����
         {
           if(img[c][r]>tresh )
             if(img[c][r+1]>tresh)
               if(img[c][r+2]>tresh)//���������жϣ�ȥ�����ŵ�
               {
                 line[c][cnt[c]]=r+1;//ȡ�м��
                 cnt[c]++;
                 i++;
               }
               
         }
         else //����
         {
           if(img[c][r]<tresh)
             if(img[c][r+1]<tresh)
               if(img[c][r+2]<tresh)
               {
                 line[c][cnt[c]]=r+1;
                 cnt[c]++;
                 i++;
               }
           
         }
       
       
       
     }
     geshu[c]=cnt[c];//��¼�����������
   }
   
   
   
   
   
  
  /***************************����ÿһ�е���Ч�����������*****************************************/
  *center=0;
  for(c=0;c<CAMERA_H;c++)
  {
     if(geshu[c]==0)
    {
   
    
    
     cnt_zeroline++;

     }
    
    
     else if(geshu[c]==1)
    {
      cnt_oneline++;
      
     }
    
    
    else if(geshu[c]==2)
    {
   
    
     center_twoline+= (u16)   ( line[c][0] +line[c][1])/2 ;
     
     cnt_twoline++;

     }
    
    else if(geshu[c]==3)
    {
   
    

     
     cnt_threeline++;

     }
     
     else if (geshu[c]==4)
    {
   
    
    
     cnt_fourline++;
 
     }
  
        
 }// end for(c=1;c<h;c++)
 
/*********************************************************************************************/
 
 if(cnt_twoline<10 && *type == 10)
 {
   cnt_cor++;
   
   if(cnt_cor>2)
   {
     cnt_cor=0;
     if(*center<*set)
     {
      *type=20;  //��ת
        *center=center_twoline/cnt_twoline;
     }
    else
     {
       *type=30;   //��ת
       *center=center_twoline/cnt_twoline;
    }
   }
 
 }
 
 
 
 
 else if (*type==20)
 {
   if(cnt_zeroline>10)
   {
     *type=21;
     resetpd();
  
   }
   else 
   {
     
   *center=center_twoline/cnt_twoline;
   }
   
 }
 
 
  else if (*type==30)
 {
   if(cnt_twoline<2)
   {
     *type=31;
     resetpd();
  
   }
   else 
   {
     
   *center=center_twoline/cnt_twoline;
   }
   
 }
 
 else if (*type==21 || *type==31)
 {
   *center=center_oneline/cnt_oneline;
   if(cnt_twoline>20)
   {
     *type=10; 
   }
 }
 
 

 
 else if(*type==10)
 {
   *center=center_twoline/cnt_twoline;
   *type=10;  //ֱ��
 }
 
 //uart_putchar(UART4,(u8)*center);
 //cnt_oneline=0;
// cnt_twoline=0;
 //cnt_threeline=0;
 //cnt_fourline=0;
  
  
 return 1;
}









/*******************************************************����λ������ͼ��ĳ����************************************************************************/

#else
u8 sobel(u8 (*img)[CAMERA_W],u8 (*imgout)[CAMERA_W],u16 tresh)
{
   u16 r;
   u16 cnt_white[w]={0};
   u16 white_array[CAMERA_H][white_num];
   u16 c,hi;
   int sum[h][20][1]={0};  //��¼ÿһ���������ĺ�
   int geshu[h][20][1]={0}; //��¼ÿһ�������ĸ���
   int zushu[h]={0};   //��¼ÿһ������������
   u16 i;
   int cnt_center[h]={0};//ȥ���ÿһ�����õ������������
   u16 cnt_oneline=0;          
   u16 cnt_twoline=0; 
   u16 center;
#if dsp
  float fx,fy,grad;
  float x[9]={-1,0,1,-2,0,2,-1,0,1};
  float y[9]={1,2,1,0,0,0,-1,-2,-1};
#else 
  int fx,fy,grad;
#endif
  
 
#if dsp
    arm_matrix_instance_f32 xm = {9, 1, (float *)x}; 
    arm_matrix_instance_f32 fxm = {1, 1, &fx};
     arm_matrix_instance_f32 ym = {9, 1, y}; 
     arm_matrix_instance_f32 fym = {1, 1, &fy};
#endif
  for(c=1;c<h;c++)
  {
    cnt_white[c]=0;
    for(r=1;r<w;r++ )
    {  
#if dsp
       arm_matrix_instance_f32 imgm = {1, 9, (float *)(img-4)}; 
       arm_mat_mult_f32(&imgm,&xm,&fxm);
       arm_mat_mult_f32(&imgm,&ym,&fym);
#else
    fx=(int)(img[c+1][r-1])+((int)img[c+1][r])*2+(int)img[c+1][r+1]-(int)img[c-1][r-1]-((int)img[c-1][r])*2-(int)img[c-1][r+1];
    fy=(int)img[c-1][r+1]+((int)img[c][r+1])*2+(int)img[c+1][r+1]-(int)img[c-1][r-1]-((int)img[c][r-1])*2-(int)img[c+1][r-1];
#endif
     if(fx<0)
     {
       fx=-fx;
        
     }
     if(fy<0)
     {
        fy=-fy;
     }
     grad=fx+fy;
     

    if(grad>=tresh)
     {
          imgout[c][r]=255;
          white_array[c][cnt_white[c]++]=r;  //cnt_white ÿһ���ж��ٸ��׵�
     }
    else 
     {
         imgout[c][r]=0;
      }

     
    
  
    
  } //end for for(r=1;r<w;r++)
  
} //end for for(c=1;c<h;c++)



//track_center(white_array,center,type);
for(c=1;c<h;c++)
  { 
    zushu[c]=0;
    for(hi=1;hi<cnt_white[c]+1;hi++)
    {
     
      if( white_array[c][hi+1]-white_array[c][hi]<=2)//�����������������2������Ϊ������������
      {
       sum[c][ zushu[c] ][0]+=white_array[c][hi];
       geshu[c][ zushu[c] ][0]++;
       
      }
      
      else
      {
        //uart_putchar(UART4,(u8)geshu[c][ zushu[c] ][0]);
        sum[c][
          zushu[c] ][0]+=white_array[c][hi];
        geshu[c][ zushu[c]][0]++;
        zushu[c]++;
      }
       
      
      
      
      
    }// end for(h=0;h<20;h++)
  } //end for(c=0;c<CAMERA_H;i++
  
  
  /********************* ȥ��ֻ��һ����������������ֻ��һ������㣬����¼ÿһ����Ч�����������*********************************************/
  for(c=1;c<h;c++)
  { 
    cnt_center[c]=0;
    for(i=0;i<zushu[c]+1;i++)
    {
      
    if(geshu[c][i][0]>0)
     {
       sum[c][ cnt_center[c] ][0]=sum[c][i][0]; //��ȥ���
       geshu[c][ cnt_center[c] ][0] =geshu[c][i][0];
        cnt_center[c]++;//ȡ��ÿһ�����õĵ������
      
     }
    
      
     }
   //uart_putchar(UART4,(u8)cnt_center[c]);
   }
  
  
    for(c=4;c<h;c++)
  {
    if(cnt_center[c]==0)
    {
     sent_frame(1000,0x01,0xa1,0xaa );
    sent_frame(c,0x01,0xa1,0xaa );//�������ڵ�����
    sent_frame(cnt_center[c],0x01,0xa1,0xaa );//���͸��е�����
    for(i=0;i<cnt_center[c];i++)
      {
        sent_frame(geshu[c][ i ][0],0x01,0xa1,0xaa );//���͸��е�ÿ��ĸ���
      }
   
    
     }
    
  else  if(cnt_center[c]==1)
    {
       sent_frame(1000,0x02,0xa1,0xaa );
       sent_frame(c,0x02,0xa1,0xaa );//�������ڵ�����
        sent_frame(cnt_center[c],0x02,0xa1,0xaa );//���͸��е�����
       for(i=0;i<cnt_center[c];i++)
        {
         sent_frame(geshu[c][ i ][0],0x02,0xa1,0xaa );//���͸��е�ÿ��ĸ���
        }
    
   
     }
    
     else  if(cnt_center[c]==2)
    {
      sent_frame(1000,0x03,0xa1,0xaa );
      sent_frame(c,0x03,0xa1,0xaa );//�������ڵ�����
      sent_frame(cnt_center[c],0x03,0xa1,0xaa );//���͸��е�����
      for(i=0;i<cnt_center[c];i++)
      {
        sent_frame(geshu[c][ i ][0],0x03,0xa1,0xaa );//���͸��е�ÿ��ĸ���
      }
    
     center= (u16)   ( (sum[c][0][0]/(geshu[c][0][0])  )  +  ( sum[c][1][0]/(geshu[c][1][0]))  )/2 ;
     imgout[c][center]=255;
   
     }
    
     else  if(cnt_center[c]==3)
    {
      sent_frame(1000,0x04,0xa1,0xaa );
       sent_frame(c,0x04,0xa1,0xaa );//�������ڵ�����
    sent_frame(cnt_center[c],0x04,0xa1,0xaa );//���͸��е�����
    for(i=0;i<cnt_center[c];i++)
      {
        sent_frame(geshu[c][ i ][0],0x04,0xa1,0xaa );//���͸��е�ÿ��ĸ���
      }
    
     
     }
    
     else  if(cnt_center[c]==4)
    {
      sent_frame(1000,0x05,0xa1,0xaa );
      sent_frame(c,0x05,0xa1,0xaa );//�������ڵ�����
      sent_frame(cnt_center[c],0x05,0xa1,0xaa );//���͸��е�����
      for(i=0;i<cnt_center[c];i++)
      {
        sent_frame(geshu[c][ i ][0],0x05,0xa1,0xaa );//���͸��е�ÿ��ĸ���
      }
   
     }
  }
  return 1;
}




/********************************************************************************************************************/
u8 outline(u8 (*img)[CAMERA_W],u8 (*imgout)[CAMERA_W],u16 tresh)
{
    u16 r;
   u16 c,wi;
   u16 geshu[CAMERA_H]={0};
   u16 line[CAMERA_H][6]={0};
   u16 cnt[CAMERA_H]={0};
   u16 i=1;;
   u16 cnt_zeroline=0;
   u16 cnt_oneline=0;          
   u16 cnt_twoline=0; 
   u16 cnt_threeline=0;
   u16 cnt_fourline=0;
   u16 center_oneline=0;
   u16 center_twoline=0;
   static  u16 cnt_cor=0;

   u16 center;
   wi=CAMERA_W-3;
   
   //�����ԵѰ��
   for(c=0;c<CAMERA_H;c++)
   {
     cnt[c]=0;
     for(r=0;r<wi;r++)
     {
         imgout[c][r]=0;
         
         if(i%2) //����
         {
           if(img[c][r]>tresh )
             if(img[c][r+1]>tresh)
               if(img[c][r+2]>tresh)//���������жϣ�ȥ�����ŵ�
               {
                 line[c][cnt[c]]=r+1;//ȡ�м��
                 imgout[c][r+1]=255;
                 cnt[c]++;
                 i++;
                
               }
               
         }
         else //����
         {
           if(img[c][r]<tresh)
             if(img[c][r+1]<tresh)
               if(img[c][r+2]<tresh)
               {
                 line[c][cnt[c]]=r+1;
                 imgout[c][r+1]=255;
                 cnt[c]++;
                 i++;
               }
           
         }
        
       
       
       
     }
     geshu[c]=cnt[c];//��¼�����������
   }
   
   
   /********************************/
  
  
    for(c=0;c<CAMERA_H;c++)
  {
    if(geshu[c]==0)
    {
     sent_frame(1000,0x01,0xa1,0xaa );
    sent_frame(c,0x01,0xa1,0xaa );//�������ڵ�����
    sent_frame(geshu[c],0x01,0xa1,0xaa );//���͸��е�����
    for(i=0;i<geshu[c];i++)
      {
        sent_frame(line[c][i],0x01,0xa1,0xaa );//���͸��е�ÿ��ĸ���
      }
   
    
     }
    
  else  if(geshu[c]==1)
    {
       sent_frame(1000,0x02,0xa1,0xaa );
       sent_frame(c,0x02,0xa1,0xaa );//�������ڵ�����
        sent_frame(geshu[c],0x02,0xa1,0xaa );//���͸��е�����
       for(i=0;i<geshu[c];i++)
        {
         sent_frame(line[c][ i ],0x02,0xa1,0xaa );//���͸��е�ÿ��ĸ���
        }
    
   
     }
    
     else  if(geshu[c]==2)
    {
      sent_frame(1000,0x03,0xa1,0xaa );
      sent_frame(c,0x03,0xa1,0xaa );//�������ڵ�����
      sent_frame(geshu[c],0x03,0xa1,0xaa );//���͸��е�����
      for(i=0;i<geshu[c];i++)
      {
        sent_frame(line[c][ i ],0x03,0xa1,0xaa );//���͸��е�ÿ��ĸ���
      }
    
     center= (u16)   ( line[c][0]+line[c][1] )/2 ;
     imgout[c][center]=255;
   
     }
    
     else  if(geshu[c]==3)
    {
      sent_frame(1000,0x04,0xa1,0xaa );
       sent_frame(c,0x04,0xa1,0xaa );//�������ڵ�����
    sent_frame(geshu[c],0x04,0xa1,0xaa );//���͸��е�����
    for(i=0;i<geshu[c];i++)
      {
        sent_frame(line[c][ i ],0x04,0xa1,0xaa );//���͸��е�ÿ��ĸ���
      }
    
     
     }
    
     else  if(geshu[c]==4)
    {
      sent_frame(1000,0x05,0xa1,0xaa );
      sent_frame(c,0x05,0xa1,0xaa );//�������ڵ�����
      sent_frame(geshu[c],0x05,0xa1,0xaa );//���͸��е�����
      for(i=0;i<geshu[c];i++)
      {
        sent_frame(line[c][ i ],0x05,0xa1,0xaa );//���͸��е�ÿ��ĸ���
      }
   
     }
  }
  return 1;
}
#endif

/**********************************************************************************************************/
















u8 track_center(u16 (*white_array)[white_num],u16 *center,u8 *type)

{
   u16 c,hi;
   int sum[h][20][1]={0};  //��¼ÿһ���������ĺ�
   int geshu[h][20][1]={0}; //��¼ÿһ�������ĸ���
   int zushu[h][1]={0};   //��¼ÿһ������������
   u16 i;
   int cnt_center[h]={0};//ȥ���ÿһ�����õ������������
   //u16 cnt_oneline=0;          
  // u16 cnt_twoline=0;  
   
   /****************��ȡÿһ��������������ĸ�����ÿһ����������������ĸ�����ÿһ��������ĺ�************************/
  for(c=1;c<h;c++)
  { 
    zushu[c][0]=0;
    for(hi=0;hi<white_num;hi++)
    {
     
      if( white_array[c][hi+1]-white_array[c][hi]<=2 )//�����������������2������Ϊ������������
      {
       sum[c][zushu[c][0]][0]+=white_array[c][hi];
       geshu[c][zushu[c][0]][0]++;
       
      }
      
      else
      {
        
        sum[c][++zushu[c][0]][0]+=white_array[c][hi];
        geshu[c][zushu[c][0]][0]++;
      }
       
      
      
      
      
    }// end for(h=0;h<20;h++)
  } //end for(c=0;c<CAMERA_H;i++
  
  
  /********************* ȥ��ֻ��һ����������������ֻ��һ������㣬����¼ÿһ����Ч�����������*********************************************/
  for(c=1;c<h;c++)
  {
    for(i=0;i<zushu[c][0];i++)
    {
      
    if(~geshu[c][i][0])
     {
       sum[c][cnt_center[c]][0]=sum[c][i][0]; //��ȥ���
       geshu[c][cnt_center[c]][0] =geshu[c][i][0];
        cnt_center[c]++;//ȡ��ÿһ�����õĵ�ĸ���
      
     }
    
      
     }
    
   }
  
  /***************************����ÿһ�е���Ч����������ۣ������ֱ�ߵĵ��м�ֵ*****************************************/
  for(c=1;c<h;c++)
  {
    if(cnt_center[c]==2)
    {
   
    
     // *center+=(sum[c][0][0]/geshu[c][0][0]  +sum[c][1][0]/geshu[c][1][0]);
     // cnt_twoline++;
      //*type=2;
      
    //*center=*center/cnt_twoline;
   // cnt_twoline=0;
    
    
  }
  
  
        
 }// end for function
 return 1;
}

/************��ȡ��̬��ֵ**********/

u8 yuzhi(u16 startj, u16 endi)
{
   u16 j=startj;
  u16 i,tempi,tempj,endj=159;
  u16 temp,JumpValue;
  u16 JumpValueTemp=80;  
  u16 space=4;
  i=endi-65;
  tempi=endi-60;
  tempj=endj-4; 
  for(;i<tempi;i++) 
  {              
    for(;j<tempj;j++) 
    {
      if(     (img_byte_buff1[i][j]<img_byte_buff1[i][j+space]-JumpValueTemp)
           && (img_byte_buff1[i][j+1]<img_byte_buff1[i][j+1+space]-JumpValueTemp)  )
       {
         temp=img_byte_buff1[i][j+space]-img_byte_buff1[i][j];
        JumpValue=JumpValue+temp;
         break;
       }
    } 
  }
  JumpValue=JumpValue/5;
  return JumpValue;   
}





/**************************************************************************
ƫ���㷨******************************************************************/
u16 shifting(u16 h_mid, u16 w_mid)
{
  u8 left_flag=0,right_flag=0;
  u16 mid_h,mid_w=80;
  u16 left_jump=0,right_jump=0;
  u16 mid,i,j,jump_v=80;
  
  mid_h=h_mid;
  mid_w=w_mid;
 
  /*****************ɨ��������****************/
for(j=5;j<155;j++)
{
  

 if((img_byte_buff1[h_mid-1][j]-img_byte_buff1[40][j+4]>jump_v)
           &&(img_byte_buff1[h_mid-1][j]-img_byte_buff1[40][j+4+2]>jump_v)) 
  {
    right_jump=j; 
    right_flag=1;
   // if((img_byte_buff1[h_mid-1][j+4]-img_byte_buff1[mid_h+1][j]>jump_v)
       //&&(img_byte_buff1[h_mid-1][j+4+2]-img_byte_buff1[mid_h+1][j]>jump_v))
   // {
   //  right_jump=j; 
  //  right_flag=1;
 //   }
  }  
 
  if((img_byte_buff1[mid_h][j+4]-img_byte_buff1[mid_h][j]>jump_v)
         &&(img_byte_buff1[mid_h][j+4+2]-img_byte_buff1[mid_h][j]>jump_v))
  {
    if((img_byte_buff1[mid_h+1][j+4]-img_byte_buff1[mid_h+1][j]>jump_v)
         &&(img_byte_buff1[mid_h+1][j+4+2]-img_byte_buff1[mid_h+1][j]>jump_v))
    {  
      left_jump=j;
    left_flag=1;
    }
}
}

 
 /********�жϸ������*****************/
 if((left_flag==1)&&(right_flag==1))
 {
   mid=((left_jump+right_jump)/2);  
 }
   else if((left_flag==1)&&(right_flag==0))
   {
     mid=(left_jump+52); 
   }
     else if( (left_flag==0)&&(right_flag==1))
     {
       mid=(right_jump-52);
     }
 return mid;
 
   
}


/*********************�����㷨************************/
u16 get_midpoint(u16 space1)
{
  u16 i,j,k,point,midpiancha;
  u16 midflag=0;
  u16 jump_vlaue=80;
  u16 left_jump[80]={0},right_jump[80]={0},mid[80];
  for(i=59;i>=30;i--)
  {
    for(j=0;j<159;j++)
    {
      if((img_byte_buff1[i][j+space1]-img_byte_buff1[i][j]>jump_vlaue)
         &&(img_byte_buff1[i][j+space1+2]-img_byte_buff1[i][j]>jump_vlaue))
      {
        left_jump[i]=j;    
      }
      else if((img_byte_buff1[i][j]-img_byte_buff1[i][j+space1]>jump_vlaue)
              &&(img_byte_buff1[i][j]-img_byte_buff1[i][j+space1+2]>jump_vlaue))
      {
        right_jump[i]=j;
        midflag=1;
      }
      if(midflag==1)
      {
       mid[i]=((left_jump[i]+right_jump[i])/2);      
      }     
    }
    k=mid[i]+k;
      
  }
  point=k/30;
  uart_putchar(UART4,point); 
  if(point-80>=0)
  {
    midpiancha=point-80;
  }
  else if(point-80<0)
  {
    midpiancha=80-point;
  }
  uart_putchar(UART4,40); 
 uart_putchar(UART4,midpiancha);  
 return point;
} 




////**********************************************************************************************************************
/**********************��ֵ�㷨*******************/
///***************************************************************************************************************************
u16 get_chazhi(u16 mid_adj,u16 img_adj )
{
    u8 j,i;
    u8 fir=25,sec=30,thr=35;
       u8 fir_mid,sec_mid,thr_mid,n,mid,zhuanwan;
    u8 fir_midl,sec_midl,thr_midl;
    u8 fir_midr,sec_midr,thr_midr;
    u8 mid1l=0,mid2l=0,mid3l=0;
    u8 mid1r=0,mid2r=0,mid3r=0;
    u8 jump_v=80,lastout[10]={40};
    /**********************/

    for(j=5;j<75;j++)
{
 if((img_byte_buff1[fir][j]-img_byte_buff1[fir][j+4]>jump_v)
           &&(img_byte_buff1[fir][j]-img_byte_buff1[fir][j+4+2]>jump_v)) 
  {
    if(j<=20)
      mid1r=0;
    else {
    mid1r=1;
    fir_midr=j;
    }
    }
  else if((img_byte_buff1[fir][j+4]-img_byte_buff1[fir][j]>jump_v)
         &&(img_byte_buff1[fir][j+4+2]-img_byte_buff1[fir][j]>jump_v))  
  {
   if(j>=60)
      mid1l=0;
   else {
    mid1l=1;
    fir_midl=j;
    }
  }
}


/*******/
 if((mid1r==1)&&(mid1l==1))
 {
   fir_mid=((fir_midl+fir_midr)/2);  
 }
   else if((mid1r==0)&&(mid1l==1))
   {
  fir_mid=(fir_midl+20);
   }
     else if( (mid1r==1)&&(mid1l==0))
     {
       fir_mid=(fir_midr-20);
     }
    else fir_mid=0;
/********************/
    
    
   for(j=5;j<75;j++)
{
 if((img_byte_buff1[sec][j]-img_byte_buff1[sec][j+4]>jump_v)
           &&(img_byte_buff1[sec][j]-img_byte_buff1[sec][j+4+2]>jump_v)) 
  {
   
    if(j<=20)
      mid2r=0;
    else {
    mid2r=1;
    sec_midr=j;
    }
    }
  else if((img_byte_buff1[sec][j+4]-img_byte_buff1[sec][j]>jump_v)
         &&(img_byte_buff1[sec][j+4+2]-img_byte_buff1[sec][j]>jump_v))  
  {
   if(j>=60)
      mid2l=0;
    else {
    mid2l=1;
    sec_midl=j;
    }
  }
}
/******/
 if((mid2r==1)&&(mid2l==1))
 {
   sec_mid=((sec_midl+sec_midr)/2);  
 }
   else if((mid2r==0)&&(mid2l==1))
   {
  sec_mid=(sec_midl+21);
   }
     else if( (mid2r==1)&&(mid2l==0))
     {
       sec_mid=(sec_midr-21);
     }
   else sec_mid=0;
    
 /**********************************/
      for(j=5;j<75;j++)
{
 if((img_byte_buff1[thr][j]-img_byte_buff1[thr][j+4]>jump_v)
           &&(img_byte_buff1[thr][j]-img_byte_buff1[thr][j+4+2]>jump_v)) 
  {
   
    if(j<=20)
      mid3r=0;
    else {
    mid3r=1;
    thr_midr=j;
    }
    }
  else if((img_byte_buff1[thr][j+4]-img_byte_buff1[thr][j]>jump_v)
         &&(img_byte_buff1[thr][j+4+2]-img_byte_buff1[thr][j]>jump_v))  
  {
    if(j>=60)
      mid3l=0;
    else {
    mid3l=1;
    thr_midl=j;
    }
  }
}
/******/
 if((mid3r==1)&&(mid3l==1))
 {
   thr_mid=((thr_midl+thr_midr)/2);  
 }
   else if((mid3r==0)&&(mid3l==1))
   {
  thr_mid=(thr_midl+22);
   }
     else if( (mid3r==1)&&(mid3l==0))
     {
       thr_mid=(thr_midr-22);
     } 
     else thr_mid=0;
/*****************/
 
     
     if(fir_mid==0&&sec_mid==0&&thr_mid==0)
     {
       mid=lastout[5];
       ruwan=2;
     }
     else if((fir_mid-thr_mid)>=30)
     {
       ruwan=1;
       mid=(fir_mid+sec_mid+thr_mid)/3;
     }
     else 
        mid=(fir_mid+sec_mid+thr_mid)/3;
     
   lastout[n%10]=mid;
   n++;
   
     return mid;

}



/**********************��ֵ��չ*******************************/
 u16 newway(u8 jumpv,u8 adji)
 {
    u8 j,i,k=0;
    u8 line[10]={6,8,10,20,22,24,26,34,36,38};
    u8  lineadd[10]={30,30,30,30,30,30,30,30,30,30};
 u8 lineadd2[10]={20,20,20,20,20,20,20,20,20,20};
    u8 linemid[10]={0};
    u8 linel[10]={0};
    u8 liner[10]={0};
    u8 flagl[10]={0};
    u8 flagr[10]={0};
    u8 midlast[2]={0};
    s16 temp; 
    u8 jump_v,adj,zhuanwan;
    u16 sum=0,n;
    
    jump_v=jumpv;
    adj=adji;
    
    for(i=0;i<=9;i++)
    { 
      
      if(i>=0&&i<=2)
      for(j=25;j<55;j++)
{
  
 if((img_byte_buff1[line[i]][j]-img_byte_buff1[line[i]][j+2]>jump_v)
           &&(img_byte_buff1[line[i]][j]-img_byte_buff1[line[i]][j+3]>jump_v)) 
  {
    if(j<=40)
      flagr[i]=0;
    else {
    flagr[i]=1;
    liner[i]=j;
    }
    }
  else if((img_byte_buff1[line[i]][j+2]-img_byte_buff1[line[i]][j]>jump_v)
         &&(img_byte_buff1[line[i]][j+3]-img_byte_buff1[line[i]][j]>jump_v))  
  {
   if(j>40)
      flagl[i]=0;
   else {
    flagl[i]=1;
    linel[i]=j;
    }
  }
 if (linel[i]-liner[i]>0)
 {
   flagr[i]=0;
 }
 
 
}
/******/
     else if(i>6)
      for(j=10;j<70;j++)
{
  
 if((img_byte_buff1[line[i]][j]-img_byte_buff1[line[i]][j+2]>jump_v)
           &&(img_byte_buff1[line[i]][j]-img_byte_buff1[line[i]][j+3]>jump_v)) 
  {
    if(j<40)
      flagr[i]=0;
    else {
    flagr[i]=1;
    liner[i]=j;
    }
    }
  else if((img_byte_buff1[line[i]][j+2]-img_byte_buff1[line[i]][j]>jump_v)
         &&(img_byte_buff1[line[i]][j+3]-img_byte_buff1[line[i]][j]>jump_v))  
  {
   if(j>=40)
      flagl[i]=0;
   else {
    flagl[i]=1;
    linel[i]=j;
    }
  }
 if (linel[i]-liner[i]>0)
 {
   flagr[i]=0;
 }
      }

/******/
     else if(i>2&&i<=6)
      for(j=5;j<75;j++)
{
  
 if((img_byte_buff1[line[i]][j]-img_byte_buff1[line[i]][j+2]>jump_v)
           &&(img_byte_buff1[line[i]][j]-img_byte_buff1[line[i]][j+3]>jump_v)) 
  {
    if(j<=40)
      flagr[i]=0;
    else {
    flagr[i]=1;
    liner[i]=j;
    }
    }
  else if((img_byte_buff1[line[i]][j+2]-img_byte_buff1[line[i]][j]>jump_v)
         &&(img_byte_buff1[line[i]][j+3]-img_byte_buff1[line[i]][j]>jump_v))  
  {
   if(j>40)
      flagl[i]=0;
   else {
    flagl[i]=1;
    linel[i]=j;
    }
  }
 if (linel[i]-liner[i]>0)
 {
   flagr[i]=0;
 }
      }
/******/
 if((flagr[i]==1)&&(flagl[i]==1))
 {
   linemid[i]=((linel[i]+liner[i])/2);  
 }
   else if((flagr[i]==0)&&(flagl[i]==1))
   {
  linemid[i]=(linel[i]+lineadd[i]);
   }
     else if( (flagr[i]==1)&&(flagl[i]==0))
     {
      linemid[i]=(liner[i]-lineadd2[i]);
     }
     else 
     {
    if(img_byte_buff1[line[i]][20]>=140&&img_byte_buff1[line[i]][40]>=140&&img_byte_buff1[line[i]][60]>=0)
    {
       linemid[i]=0; 
    zhuanwan=0;
    }
      else 
      {
        linemid[i]=0;
        zhuanwan=1;
      }
     }
    } 
  
  for(i=0;i<10;i++)
  {
    
    if(linemid[i])
    {
      linemid[i]+=40;
    }
  }
      
   for(i=3;i<=6;i++)
   {
     if(linemid[i])
     {
       sum=sum+linemid[i];
     }
    else k++;
   }
 output=sum/(4-k);

 
   if(output==0)
   {
     if((linemid[0]||linemid[1]||linemid[2])&&(linemid[7]==0||linemid[8]==0||linemid[9]==0))
     {
       
       if(zhuanwan==0)
       {
       if(linemid[0])
       output=linemid[0];
       else if(linemid[1])
         output=linemid[1];
       else if(linemid[2])
         output=linemid[2];
     }

       else if(zhuanwan==1)
     {
       if(last[0]>=88||last[1]>=88||last[2]>=88)
       {
         if(last[0]>=88)
       output=last[0];
       else if(last[1]>=88)
         output=last[1];
       else if(last[2]>=88)
               output=last[2]+15;
       }
       else if(last[0]<=72||last[1]<=72||last[2]<=72)
          {
         if(last[0]<=72)
       output=last[0];
       else if(last[1]<=72)
         output=last[1];
       else if(last[2]<=72)
               output=last[2];
       }
       else output=(last[0]+last[1]+last[2])/3;
     }
       
    }
   else if(zhuanwan==1)
   {
     if(last[0]>=90||last[1]>=88)
       output=last[0]+15;
     else if(last[0]<68||last[1]<70)
       output=last[0]-15;
       else output=(last[0]+last[1])/2;
   }
 
     }
   
 
  else   
  {
    last[0]=output;
  last[1]=last[0];
  last[2]=last[1];
  }
  
  
  if (output==0)
  {
    if(linemid[7])
    {
  output=linemid[8];
  midlast[0]=output;
    }
  if(linemid[8])
  {
    output=linemid[9];
    midlast[0]=output;
  }
  else output=last[0];
  
  
    
  }
  
  

///****** ��λ������
 /*   
   for(i=0;i<=9;i++)
uart_putchar(UART4,0xff); 
 for(i=0;i<=9;i++)
uart_putchar(UART4,linemid[i]); 
 for(i=0;i<=9;i++)
uart_putchar(UART4,0xff); 
 for(i=0;i<=9;i++)
uart_putchar(UART4,0xaa);  
 for(i=0;i<=9;i++)
uart_putchar(UART4,linel[i]); 
  for(i=0;i<=9;i++)
uart_putchar(UART4,0xff); 
 for(i=0;i<=9;i++)
uart_putchar(UART4,liner[i]); 

 for(i=0;i<=9;i++)
uart_putchar(UART4,output); 
 for(i=0;i<=19;i++)
uart_putchar(UART4,0xBB); 
 //�����е�ֵ 
   */
 /*for(i=0;i<10;i++)
  {
  img_byte_buff1[line[i]]  [ linemid[i] -40 ]=0;
  }
 img_byte_buff1[39]  [ output -40 ]=0;
  img_byte_buff1[39]  [ output -39 ]=255;
 sent_frame(last[0],0x06,0xa1,0xaa );
 sent_frame(last[1],0x07,0xa1,0xaa );*/
  return output;
  
}
      
      
      
      
      
      
      
  





    
/***************************ͼ����ԣ���ڻ��߱�ף�*****************************************/

/*
void imgtest()
{
  u8 i,j,k=0;
  for(i=0;i<=80;i++)
  {
    if(k>=255)
    {
      k=0;
    }
    for(j=0;j<=160;j++)
    {
      img_byte_buff1[i][j]=k;
   k++;   
    }
  }
  
}
*/