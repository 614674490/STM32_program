/**
  ******************************************************************************
  * @file    usb_endp.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Endpoint routines
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
extern  uint8_t USART_Rx_Buffer[];
extern uint32_t USART_Rx_ptr_out;
extern uint32_t USART_Rx_length;
extern uint8_t  USB_Tx_State;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback (void)
{
	u16 USB_Tx_ptr; u16 USB_Tx_length; 
	if(uu_txfifo.readptr==uu_txfifo.writeptr)return;	//??????????????????????????
	if(uu_txfifo.readptr<uu_txfifo.writeptr)		//????????????,??????<??????
	{
		USB_Tx_length=uu_txfifo.writeptr-uu_txfifo.readptr;	//????????????????????
	}else USB_Tx_length=USB_USART_TXFIFO_SIZE-uu_txfifo.readptr;//??????>??????????????????????
	if(USB_Tx_length>VIRTUAL_COM_PORT_DATA_SIZE)	//????64????
	{
		USB_Tx_length=VIRTUAL_COM_PORT_DATA_SIZE;//????????????????
	}
	USB_Tx_ptr=uu_txfifo.readptr;		//????????????
	uu_txfifo.readptr+=USB_Tx_length;		//??????????
	if(uu_txfifo.readptr>=USB_USART_TXFIFO_SIZE)	//??????????
	{
		uu_txfifo.readptr=0;
	} 
	UserToPMABufferCopy(&uu_txfifo.buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);//????????
	SetEPTxCount(ENDP1, USB_Tx_length); //????????1????????????
	SetEPTxValid(ENDP1); //????????1????????
}

/*******************************************************************************
* Function Name  : EP3_OUT_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP3_OUT_Callback(void)
{
  uint16_t USB_Rx_Cnt;
  
  /* Get the received data buffer and update the counter */
  USB_Rx_Cnt = USB_SIL_Read(EP3_OUT, USB_Rx_Buffer);
  
  /* USB data will be immediately processed, this allow next USB traffic being 
  NAKed till the end of the USART Xfer */
  
  USB_To_USART_Send_Data(USB_Rx_Buffer, USB_Rx_Cnt);
 
  /* Enable the receive of data on EP3 */
  SetEPRxValid(ENDP3);
}


/*******************************************************************************
* Function Name  : SOF_Callback / INTR_SOFINTR_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
//????????????????,????????????1ms??1????????
void SOF_Callback(void)
{
	static uint32_t FrameCount = 0;
	if(bDeviceState == CONFIGURED)
	{
		if (FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL)
		{ 
			FrameCount = 0;//????????????
			EP1_IN_Callback();//????EP1_IN_Callback????????TX??????????USB 
		}
	}  
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

