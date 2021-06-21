#include "common.h"
#include "include.h"
#include "sci.h"
#include "isr.h"
#include "imgprocess.h"
#include "globle.h"
#include "control.h"
#include "ENCODER.h"
#include "gpio.h"
#include "dma.h"

void Encoder_init(void)
{
  DMA_count_Init_irq(DMA_CH0, PTA4, 1000000, DMA_rising_up);                   //���벶�������ֶ������жϡ�
  pit_init_ms_M(PIT0,200);                                                 //��ʼ��PIT�ж�

}




