/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/Src/usbd_cdc_interface.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    01-July-2015
  * @brief   Source file for USBD CDC interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define APP_RX_DATA_SIZE  2048
#define APP_TX_DATA_SIZE  2048

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t UserRxBuffer[APP_RX_DATA_SIZE];/* Received Data over USB are stored in this buffer */
uint8_t UserTxBuffer[APP_TX_DATA_SIZE];/* Received Data over UART (CDC interface) are stored in this buffer */

uint32_t UserTxBufPtrIn = 0;/* Increment this pointer or roll it back to
                               start address when data are received over USART */
uint32_t UserTxBufPtrOut = 0; /* Increment this pointer or roll it back to
                                 start address when data are sent over USB */

//uint8_t g_pBuffer[5]; // test sensor id
uint8_t g_pBuffer[2048];

/* UART handler declaration */
//UART_HandleTypeDef UartHandle;

/* USB handler declaration */
extern USBD_HandleTypeDef  USBD_Device;

/* Private function prototypes -----------------------------------------------*/
static int8_t JUSB_Itf_Init(void);
static int8_t JUSB_Itf_DeInit(void);
static int8_t JUSB_Itf_Control(uint8_t cmd, uint8_t* pbuf, uint16_t length, uint16_t value);
static int8_t JUSB_Itf_Receive(uint8_t* pbuf, uint32_t *Len);
//static void Error_Handler(void);

USBD_JUSB_ItfTypeDef USBD_JUSB_fops = 
{
	JUSB_Itf_Init,
	JUSB_Itf_DeInit,
	JUSB_Itf_Control,
	JUSB_Itf_Receive
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CDC media low layer      
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t JUSB_Itf_Init(void)
{ 
	/*##-5- Set Application Buffers ############################################*/
	USBD_JUSB_SetTxBuffer(&USBD_Device, UserTxBuffer, 0);
	USBD_JUSB_SetRxBuffer(&USBD_Device, UserRxBuffer);
	
	return (USBD_OK);
}

/**
  * @brief  CDC_Itf_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t JUSB_Itf_DeInit(void)
{
#if 0
  /* DeInitialize the UART peripheral */
  if(HAL_UART_DeInit(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
#endif
  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code            
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t JUSB_Itf_Control (uint8_t cmd, uint8_t* pbuf, uint16_t length, uint16_t value)
{
	//printf("\n\r [RECV] From USB C:0x%02X, V:0x%04X, L:%d, D:0x%02X", cmd, value, length, pbuf[0]);	
	msgBody.source = PC_USB;
	msgBody.length = (uint8_t)length;	
	msgBody.rxBuf[0] = (uint8_t)value;	
	//USBD_SetDataReceived(cmd); 

#if 1
	switch (cmd)
	{
		case STM_COMM_START_BULK_TRANSFER:
			if(length != 0)
			{
				memcpy(pbuf, msgBody.txBuf, 2048);
				// become continuous mode
			}
			//for testing bulk transfer to Host with control msg
			else
			{
				//memset(UserTxBuffer, 4, 2048);
				//USBD_JUSB_SetTxBuffer(&USBD_Device, UserTxBuffer, 2048);
				USBD_SetDataReceived(1);   
			}
			break;

		case STM_COMM_STOP_BULK_TRANSFER:
			if(length != 0)
			{
				memset(pbuf, 0, 2048);
			}
			//for testing bulk transfer to Host with control msg
			else
			{
				//memset(UserTxBuffer, 0, 2048);
				//USBD_JUSB_SetTxBuffer(&USBD_Device, UserTxBuffer, 2048);
				USBD_SetDataReceived(2);
			}
			break;

		case EFM32_COMM_NO_OP:	
			USBD_SetDataReceived(0);
			break;

		case EFM32_COMM_GET_SENSOR_ID:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_SENSOR_ID_01;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 5);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;

		case EFM32_COMM_GET_SENSOR_DATA:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_ACQUIRE_MODE:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_MODE_SELECTION;			
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_ACQUIRE_MODE;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_LOW_EXPOSURE_TIME:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_INTEG_TIME_DOWN;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_UPPER_EXPOSURE_TIME:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_INTEG_TIME_UP;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_LOW_EXPOSURE_TIME:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_INTEG_TIME_DOWN;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_LOW_EXPOSURE_TIME;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_UPPER_EXPOSURE_TIME:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_INTEG_TIME_UP;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_SENSOR_STATUS:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_CONTROLLER_STATUS:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_LED_STATUS:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_LED_STATUS:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_ERROR:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_SPECTRUM:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_XYZ:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_AMBIENT:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_MCU_MODE:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_LOW_BLANK_TIME:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_BLANK_TIME_DOWN;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_LOW_BLANK_TIME;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_UPPER_BLANK_TIME:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_BLANK_TIME_UP;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_UPPER_BLANK_TIME;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_LOW_BLANK_TIME:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_BLANK_TIME_DOWN;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_UPPER_BLANK_TIME:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_BLANK_TIME_UP;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_ROI_START_POS:
			break;
			
		case EFM32_COMM_SET_ROI_SIZE:
			break;
			
		case EFM32_COMM_SET_ADC_RANGE:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_ADC;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_ADC_RANGE;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_ADC_RANGE:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_ADC;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_AMP_GAIN_RESOLUTION:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_GAIN;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_AMP_GAIN_RESOLUTION;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_AMP_GAIN_RESOLUTION:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_GAIN;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_INIT_ACQ:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_FIN_ACQ:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_READ_REGISTER:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_WRITE_REGISTER:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_LED_TOGGLE:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_TEST_BYTE:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_TEST_VALUE;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_START_ROW:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_START_ROW;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_START_ROW:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_START_ROW;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_START_ROW;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_START_COL:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_START_COL;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_START_COL:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_START_COL;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_START_COL;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_NUMB_ROW:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_NUMBER_ROW_READ;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_NUMB_ROW:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_NUMBER_ROW_READ;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_NUMB_ROW;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_NUMB_COL:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = YES;
			msgBody.addr = APOLLO_NUMBER_COL_READ;
			GlobalMessageHandler();
			memcpy(pbuf, msgBody.txBuf, msgBody.length);
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 1);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_NUMB_COL:
			msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
			msgBody.reply = NO;
			msgBody.addr = APOLLO_NUMBER_COL_READ;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_SET_NUMB_COL;
			//USBD_JUSB_SetTxBuffer(&USBD_Device, msgBody.txBuf, 0);
			//ret = USBD_JUSB_TransmitPacket(&USBD_Device);
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_FRAME_AVERAGE:
			msgBody.dest = STM32_ONBOARD_CONTROL;
			msgBody.reply = YES;
			msgBody.addr = EFM32_COMM_GET_FRAME_AVERAGE;
			GlobalMessageHandler();
			pbuf[0] = msgBody.txBuf[0];
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_FRAME_AVERAGE:
			msgBody.dest = STM32_ONBOARD_CONTROL;
			msgBody.reply = NO;
			msgBody.addr = EFM32_COMM_SET_FRAME_AVERAGE;
			GlobalMessageHandler();
			pbuf[0] = EFM32_COMM_GET_FRAME_AVERAGE;
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_BURST_MODE_TEST:
			USBD_SetDataReceived(0);
			break;

		case EFM32_COMM_GET_DARK_FRAME:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_DARK_CORRECTION_MODE:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_DARK_CORRECTION_MODE:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_POI_COUNT:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_POI_COUNT:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_CLEAR_POI_INDEX_LIST:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_POI_INDEX_LIST:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_POI_INDEX_LIST:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_POI_DATA:
			USBD_SetDataReceived(0);
			break;

		case EFM32_COMM_SET_EXPOSURE_TIME:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_SET_BLANK_TIME:
			USBD_SetDataReceived(0);
			break;
			
		case EFM32_COMM_GET_SENSOR_DATA_TEST:
			USBD_SetDataReceived(0);
			break;

		case EFM32_COMM_REBOOT:
			USBD_SetDataReceived(0);
			break;

		default:
			USBD_SetDataReceived(0);
			break;
	}
#endif 
	return (USBD_OK);
}

// ********************************** NO USE START *********************************************************
#if 0
/**
  * @brief  Rx Transfer completed callback
  * @param  huart: UART handle
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	BSP_LED_Init(LED2);
	
	/* Increment Index for buffer writing */
	UserTxBufPtrIn++;
	
	/* To avoid buffer overflow */
	if(UserTxBufPtrIn == APP_RX_DATA_SIZE)
	{
		UserTxBufPtrIn = 0;
	}
	
	/* Start another reception: provide the buffer pointer with offset and the buffer size */
	HAL_UART_Receive_IT(huart, (uint8_t *)(UserTxBuffer + UserTxBufPtrIn), 1);
}
#endif
// ********************************** NO USE END *********************************************************

/**
  * @brief  CDC_Itf_DataRx
  *         Data received over USB OUT endpoint are sent over CDC interface 
  *         through this function.
  * @param  Buf: Buffer of data to be transmitted
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t JUSB_Itf_Receive(uint8_t* Buf, uint32_t *Len)
{
	//HAL_UART_Transmit_DMA(&UartHandle, Buf, *Len);
	//USBD_JUSB_SetRxBuffer(&USBD_Device, UserRxBuffer);
	
	/* Prepare Out endpoint to receive next packet */
	USBD_JUSB_ReceivePacket(&USBD_Device);
	
	// for simulation of sending data
	//for testing bulk transfer to Host with bulk msg
  
 	return (USBD_OK);
}

// ********************************** NO USE START *********************************************************
#if 0
/**
  * @brief  Tx Transfer completed callback
  * @param  huart: UART handle
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	BSP_LED_Init(LED3);
	/* Initiate next USB packet transfer once UART completes transfer (transmitting data over Tx line) */
	USBD_JUSB_ReceivePacket(&USBD_Device);
}

/**
  * @brief  UART error callbacks
  * @param  UartHandle: UART handle
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
	/* Transfer error occured in reception and/or transmission process */
	Error_Handler();
}
#endif
// ********************************** NO USE END *********************************************************




/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
//static void Error_Handler(void)
//{
//  /* Add your own code here */
//}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
