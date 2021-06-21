/************************************ ��Ұ�ʿ ********************
 * �ļ���       ��nrf24l01.h
 * ����         ��nrf24l01.hоƬ������������
 *
 * ʵ��ƽ̨     ��LQ K60������
 *                IRQ PTE25  CSN PTE27  MOSI PTD13   CE PTE28  SCK PTD12    MISO PTD14
 *   
 * ����          DAQI
**********************************************************************************/
/************************************ ע������ ********************

      1  ��Ҫ�õ��ĺ���
      void NRF24L01_Init(void);//��ʼ��
      void RX_Mode(void);//����Ϊ����ģʽ
      void TX_Mode(void);//����Ϊ����ģʽ

      uint8 NRF24L01_TxPacket(uint8 *txbuf);//����һ����������   ��������λ���Ѷ�TX_PLOAD_WIDTH
     ���ø�ʽ��if(NRF24L01_TxPacket(tmp_buf)==TX_OK)   ��Ϊ���ͳɹ�

     uint8 NRF24L01_RxPacket(uint8 *rxbuf);//����һ����������    ��������λ���Ѷ�RX_PLOAD_WIDTH
     ���ø�ʽ�� if(NRF24L01_RxPacket(tmp_buf)==0)     ��Ϊ���յ���Ϣ

     2  ��û�н��ն�ʱ�����Ͳ����ܳɹ�����NRF24L01_TxPacket(tmp_buf)��=TX_OK


**********************************************************************************/


#ifndef _NRF24L0_H_
#define _NRF24L0_H_     1

#include "spi.h"

//NRF24L01�Ĵ�����������
#define NRF24L01_READ_REG        0x00  //�����üĴ���,��5λΪ�Ĵ�����ַ
#define NRF24L01_WRITE_REG       0x20  //д���üĴ���,��5λΪ�Ĵ�����ַ
#define NRF24L01_RD_RX_PLOAD     0x61  //��RX��Ч����,1~32�ֽ�
#define NRF24L01_WR_TX_PLOAD     0xA0  //дTX��Ч����,1~32�ֽ�
#define NRF24L01_FLUSH_TX        0xE1  //���TX FIFO�Ĵ���.����ģʽ����
#define NRF24L01_FLUSH_RX        0xE2  //���RX FIFO�Ĵ���.����ģʽ����
#define NRF24L01_REUSE_TX_PL     0xE3  //����ʹ����һ������,CEΪ��,���ݰ������Ϸ���.
#define NRF24L01_NOP             0xFF  //�ղ���,����������״̬�Ĵ���
//SPI(NRF24L01)�Ĵ�����ַ
#define CONFIG          0x00  //���üĴ�����ַ;bit0:1����ģʽ,0����ģʽ;bit1:��ѡ��;bit2:CRCģʽ;bit3:CRCʹ��;
                              //bit4:�ж�MAX_RT(�ﵽ����ط������ж�)ʹ��;bit5:�ж�TX_DSʹ��;bit6:�ж�RX_DRʹ��
#define EN_AA           0x01  //ʹ���Զ�Ӧ����  bit0~5,��Ӧͨ��0~5
#define EN_RXADDR       0x02  //���յ�ַ����,bit0~5,��Ӧͨ��0~5
#define SETUP_AW        0x03  //���õ�ַ���(��������ͨ��):bit1,0:00,3�ֽ�;01,4�ֽ�;02,5�ֽ�;
#define SETUP_RETR      0x04  //�����Զ��ط�;bit3:0,�Զ��ط�������;bit7:4,�Զ��ط���ʱ 250*x+86us
#define RF_CH           0x05  //RFͨ��,bit6:0,����ͨ��Ƶ��;
#define RF_SETUP        0x06  //RF�Ĵ���;bit3:��������(0:1Mbps,1:2Mbps);bit2:1,���书��;bit0:�������Ŵ�������
#define STATUS          0x07  //״̬�Ĵ���;bit0:TX FIFO����־;bit3:1,��������ͨ����(���:6);bit4,�ﵽ�����ط�
                              //bit5:���ݷ�������ж�;bit6:���������ж�;
#define MAX_TX  		0x10  //�ﵽ����ʹ����ж�
#define TX_OK   		0x20  //TX��������ж�
#define RX_OK   		0x40  //���յ������ж�

#define OBSERVE_TX      0x08  //���ͼ��Ĵ���,bit7:4,���ݰ���ʧ������;bit3:0,�ط�������
#define CD              0x09  //�ز����Ĵ���,bit0,�ز����;
#define RX_ADDR_P0      0x0A  //����ͨ��0���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P1      0x0B  //����ͨ��1���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P2      0x0C  //����ͨ��2���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P3      0x0D  //����ͨ��3���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P4      0x0E  //����ͨ��4���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P5      0x0F  //����ͨ��5���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define TX_ADDR         0x10  //���͵�ַ(���ֽ���ǰ),ShockBurstTMģʽ��,RX_ADDR_P0��˵�ַ���
#define RX_PW_P0        0x11  //��������ͨ��0��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P1        0x12  //��������ͨ��1��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P2        0x13  //��������ͨ��2��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P3        0x14  //��������ͨ��3��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P4        0x15  //��������ͨ��4��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P5        0x16  //��������ͨ��5��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define FIFO_STATUS     0x17  //FIFO״̬�Ĵ���;bit0,RX FIFO�Ĵ����ձ�־;bit1,RX FIFO����־;bit2,3,����
                              //bit4,TX FIFO�ձ�־;bit5,TX FIFO����־;bit6,1,ѭ��������һ���ݰ�.0,��ѭ��;
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NRF24L01_IRQ   GPIO_Get(PORTE,25)

#define Set_NRF24L01_CE   GPIO_SET(PORTE,28,1)
#define Clr_NRF24L01_CE   GPIO_SET(PORTE,28,0)

#define Set_NRF24L01_CSN   GPIO_SET(PORTE,26,1)
#define Clr_NRF24L01_CSN    GPIO_SET(PORTE,26,0)

//24L01���ͽ������ݿ�ȶ���
#define TX_ADR_WIDTH    5   //5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH    5   //5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH  2  //32�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH  2  //32�ֽڵ��û����ݿ��



void NRF24L01_Init(void);//��ʼ��
void RX_Mode(void);//����Ϊ����ģʽ
void TX_Mode(void);//����Ϊ����ģʽ
uint8 NRF24L01_Write_Buf(uint8 reg, uint8 *pBuf, uint8 u8s);//д������
uint8 NRF24L01_Read_Buf(uint8 reg, uint8 *pBuf, uint8 u8s);//��������		  
uint8 NRF24L01_Read_Reg(uint8 reg);			//���Ĵ���
uint8 NRF24L01_Write_Reg(uint8 reg, uint8 value);//д�Ĵ���
uint8 NRF24L01_Check(void);//���24L01�Ƿ����
uint8 NRF24L01_TxPacket(uint8 *txbuf);//����һ����������
uint8 NRF24L01_RxPacket(uint8 *rxbuf);//����һ����������


#endif      //_NRF24L0_H_