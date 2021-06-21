/******************** ��Ұ�ʿ ********************
 * �ļ���       ��nrf24l01.c
 * ����         ��nrf24l01оƬ������������
 *
 * ʵ��ƽ̨     ��LQ K60������
 *                IRQ PTE25  CSN PTE26  MOSI PTD13   CE PTE28  SCK PTD12    MISO PTD14
 *
 * ����          DAQI
**********************************************************************************/
#include "include.h"

const uint8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const uint8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ

//��ʼ��24L01��IO��
void NRF24L01_Init(void)
{
    PORT_PCR_REG(PORTX[PORTE], 26) = PORT_PCR_MUX(1);
    GPIO_PDDR_REG(GPIOx[PORTE]) |= (1 <<26);    //  ȷ������Ϊ���
    PORT_PCR_REG(PORTX[PORTE], 28) = PORT_PCR_MUX(1);
    GPIO_PDDR_REG(GPIOx[PORTE]) |= (1 <<28);    //  ȷ������Ϊ���
    PORT_PCR_REG(PORTX[PORTE], 25) = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // GPIO���� , �ڲ�����
    GPIO_PDDR_REG(GPIOx[PORTE]) &= ~(1 <<25);    //  ȷ������Ϊ����

    spi_init(MASTER);   //��ʼ��SPI
	
    Clr_NRF24L01_CE;	 //ʹ��24L01  NRF24L01_CE
    Set_NRF24L01_CSN;    //SPIƬѡȡ�� NRF24L01_CSN	 		  
}

//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
uint8 NRF24L01_Check(void)
{
	
  uint8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
  uint8 i;
	   	 
  NRF24L01_Write_Buf(NRF24L01_WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
  NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
  for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
  if(i!=5)return 1;//���24L01����	
  return 0;		 //��⵽24L01
}	
//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
uint8 NRF24L01_Write_Reg(uint8 reg,uint8 value)
{
    uint8 status;	
    Clr_NRF24L01_CSN;                 //ʹ��SPI����
    status =SPIx_ReadWriteByte(reg);//���ͼĴ����� 
    SPIx_ReadWriteByte(value);      //д��Ĵ�����ֵ
    Set_NRF24L01_CSN;                 //��ֹSPI����	   
    return(status);       			//����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
uint8 NRF24L01_Read_Reg(uint8 reg)
{
    u8 reg_val;	    
    Clr_NRF24L01_CSN;          //ʹ��SPI����		
    SPIx_ReadWriteByte(reg);   //���ͼĴ�����
    reg_val=SPIx_ReadWriteByte(0XFF);//��ȡ�Ĵ�������
    Set_NRF24L01_CSN;          //��ֹSPI����		    
    return(reg_val);           //����״ֵ̬
}	
//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
uint8 NRF24L01_Read_Buf(uint8 reg,uint8 *pBuf,uint8 len)
{
    uint8 status,u8_ctr;	       
    Clr_NRF24L01_CSN;           //ʹ��SPI����
    status=SPIx_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
    for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPIx_ReadWriteByte(0XFF);//��������
    Set_NRF24L01_CSN;       //�ر�SPI����
    return status;        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
uint8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
    uint8 status,u8_ctr;	    
    Clr_NRF24L01_CSN;          //ʹ��SPI����
    status = SPIx_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPIx_ReadWriteByte(*pBuf++); //д������	 
    Set_NRF24L01_CSN;       //�ر�SPI����
    return status;          //���ض�����״ֵ̬
}
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
uint8 NRF24L01_TxPacket(uint8 *txbuf)
{
     uint8 sta;  
     Clr_NRF24L01_CE;
     NRF24L01_Write_Buf(NRF24L01_WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
     Set_NRF24L01_CE;//��������	   
     while(NRF24L01_IRQ!=0);//�ȴ��������
     sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
     NRF24L01_Write_Reg(NRF24L01_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
     if(sta&MAX_TX)//�ﵽ����ط�����
     {
	NRF24L01_Write_Reg(NRF24L01_FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
	return MAX_TX; 
     }
    if(sta&TX_OK)//�������
    {
	return TX_OK;
    }
    return 0xff;//����ԭ����ʧ��
}
//����NRF24L01��ȡһ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
uint8 NRF24L01_RxPacket(u8 *rxbuf)
{
    u8 sta;		    							      
    sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    	 
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+STATUS,sta); //���TX_DS��MAX_RT�жϱ�־
   if(sta&RX_OK)//���յ�����
   {
       NRF24L01_Read_Buf(NRF24L01_RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
       NRF24L01_Write_Reg(NRF24L01_FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
       return 0; 
    }	   
    return 1;//û�յ��κ�����
}	

//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
void RX_Mode(void)
{
    exti_init(PORTE, 25, falling_up);
    delay_2us();
    
    Clr_NRF24L01_CE;	  
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��    
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  	 
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+RF_CH,40);	     //����RFͨ��Ƶ��		  
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��   
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
    Set_NRF24L01_CE; //CEΪ��,�������ģʽ 
}
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void TX_Mode(void)
{	
//    PORT_PCR_REG(PORTX[PORTE], 25) = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // GPIO���� , �ڲ�����
//    GPIO_PDDR_REG(GPIOx[PORTE]) &= ~(1 <<25);    //  ȷ������Ϊ����
//    disable_irq(PORTE+87);
//    delay_2us();
    
    Clr_NRF24L01_CE;	    
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  
	
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
    Set_NRF24L01_CE;//CEΪ��,10us����������
}		  
							 




