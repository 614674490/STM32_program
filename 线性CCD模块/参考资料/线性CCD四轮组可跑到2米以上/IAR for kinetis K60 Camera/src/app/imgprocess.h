#ifndef __IMGPROCESS_H
#define __IMGPROCESS_H 

#include"include.h"
#define imgshow 0 //0����ֻʹ��ͼ����Թ��ܣ�������ͼ�񣬵������ݣ���1�����������У���PID���ܳ���
#if imgshow
extern u8 sobel(u8 (*img)[CAMERA_W],u16 tresh,u16 *center,u16 *set,u8 *type);//sobel���㷨
extern u8 type_detect(u8 (*img)[CAMERA_W],u16 tresh,u16 *center,u16 *set,u8 *type);//�������㷨
#else 
extern u8 sobel(u8 (*img)[CAMERA_W],u8 (*imgout)[CAMERA_W],u16 tresh);//sobel���㷨
extern u8 outline(u8 (*img)[CAMERA_W],u8 (*imgout)[CAMERA_W],u16 tresh);//�������㷨
#endif
typedef enum 
{
    RUNWAY_NOTINIT=0,
	RUNWAY_STRAIGHT,			//ֱ��
	RUNWAY_TURNLEFT,				//��ת
	RUNWAY_TURNRIGHT,				//��ת
	RUNWAYSTOPLINE,				//ֹͣ��
	RUNWAY_CROSS,				//ʮ��·��
	
}RUNWAY_STATE;

#endif
