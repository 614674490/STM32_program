/******************** ��Ұ�ʿ ********************
 * �ļ���       ��FTM.h
 * ����         ��FTM������������
 *
 * ʵ��ƽ̨     ��LQ K60������
 *               PWMռ��FTM1��CH0��CH1��CH2��CH3ͨ������PTC1��PTC2��PTC3��PTC4����
 *
 * ����          DAQI
**********************************************************************************/

#ifndef _FTM_H_
#define _FTM_H_
/*
#define FTM_CnV_REG(FTM0_BASE_PTR, 0)  L_PWM_GO
#define FTM_CnV_REG(FTM0_BASE_PTR, 1)  L_PWM_BACK
#define FTM_CnV_REG(FTM0_BASE_PTR, 2)  R_PWM_GO
#define FTM_CnV_REG(FTM0_BASE_PTR, 3)  R_PWM_BACK
*/

void FTM_PWM_init(void);
void L_PWM_GO(uint16 duty);
void L_PWM_BACK(uint16 duty);
void R_PWM_GO(uint16 duty);
void R_PWM_BACK(uint16 duty);

void FTM_QUAD_init(void);



#endif  //_FTM_H_





