#include "dma.h"

u16 DMA2_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ��� 	    
//DMAx�ĸ�ͨ������
//����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
//�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7
//chx:DMAͨ��ѡ��,@ref DMA_channel DMA_Channel_0~DMA_Channel_7
//par:�����ַ
//mar:�洢����ַ
//ndtr:���ݴ�����  
void MYDMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 DMA_CHx,u32 cpar,u32 cmar,u16 cndtr)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	if((u32)DMA_Streamx>(u32)DMA2)    //�õ���ǰ��������������DMA1����DMA2
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);      //ʹ��DMA1ʱ��
	else
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);      //ʹ��DMA1ʱ��
	
	DMA2_MEM_LEN=cndtr;                                   	//�����õ�ֵ����Cndtr
	
	DMA_DeInit(DMA_Streamx);
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}//�ȴ�DMA������ 
	
	DMA_InitStructure.DMA_Channel=DMA_CHx;               //ͨ��ѡ��
	DMA_InitStructure.DMA_PeripheralBaseAddr=cpar;           //DMA�������ַ
	DMA_InitStructure.DMA_Memory0BaseAddr=cmar;              //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralToMemory;     //���ݴ��䷽�� �����赽�ڴ�
	DMA_InitStructure.DMA_BufferSize=cndtr;                   //DMAͨ����DMA�����С
	DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;    //�������ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;   //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;    //�������ݿ��Ϊ32λ
	DMA_InitStructure.DMA_MemoryDataSize=DMA_PeripheralDataSize_HalfWord;   //�洢�����ݿ��Ϊ32λ   ����Ϊ32λ�������Ӱ�쵽ADC�����ֵ����
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;             //������ѭ������ģʽ �����ڶ�·ADC
	DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;     //�����������ȼ� ��
	DMA_InitStructure.DMA_FIFOMode=DISABLE;               //�ر�FIFOģʽ
	DMA_InitStructure.DMA_FIFOThreshold=DMA_FIFOThreshold_Full;//FIFO��ֵ����Ϊ��
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
	DMA_Init(DMA_Streamx,&DMA_InitStructure);               //��ʼ��
}

//����һ��DMA����
//DMA_Streamx:DMA������,DMA1_Stream0~7/DMA2_Stream0~7 
//ndtr:���ݴ�����  
void MYDMA_Enable(DMA_Stream_TypeDef *DMA_Streamx)
{
	DMA_Cmd(DMA_Streamx,DISABLE);                            //�ر�
	
	while (DMA_GetCmdStatus(DMA_Streamx) != DISABLE){}	//ȷ��DMA���Ա�����
		
	DMA_SetCurrDataCounter(DMA_Streamx,DMA2_MEM_LEN);    //DMAͨ��DMA�����С
	
	DMA_Cmd(DMA_Streamx,ENABLE);                           //ʹ��
}




