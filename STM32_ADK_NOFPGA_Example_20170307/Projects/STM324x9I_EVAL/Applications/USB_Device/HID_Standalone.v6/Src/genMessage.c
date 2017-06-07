#include "main.h"
#include "string.h"
#include "utils.h"

extern uint32_t startTick;

extern uint8_t reBuffer[2048];
extern uint8_t aRxBuffer[BUFFERSIZE];

uint8_t usbRxBuff[10];
uint8_t usbTxBuff[10];


int GlobalMessageHandler(void)
{	
	HAL_NVIC_DisableIRQ(EXTI1_IRQn);

	switch (msgBody.dest)
	{	
		case APOLLO_SENSOR_CTRL_SPI:
		{
			if(msgBody.addr == APOLLO_MODE_SELECTION)
			{
				if (msgBody.rxBuf[0] < 0x04)
				{					
					if(msgBody.rxBuf[0] == CONTINUOUS_FRAME_MODE)
					{
						if( (mainState != CONTINUE_CAPTURE_STATE) && (mainState != FRAME_SYNC_STATE) )
						{
							mainState = CONTINUE_CAPTURE_STATE;
						}
					}
					else if (msgBody.rxBuf[0] == POWER_ON_WAITING_MODE)
					{
						mainState = NORMAL_STATE;
					}
					else
						return NORMAL_STATE;
				}        
				else
				{
					return -4;
				}
			}
			else if(msgBody.addr == APOLLO_INTEG_TIME_UP)
			{
				if(msgBody.reply == YES)		// Get register value and return
				{
					usbTxBuff[0] = (APOLLO_INTEG_TIME_UP << 1); usbTxBuff[1] = 0;
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = usbRxBuff[1];
				}
				else							// Set register value
				{
					usbTxBuff[0] = (APOLLO_INTEG_TIME_UP << 1) + 1; usbTxBuff[1] = msgBody.rxBuf[0];
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = 0;
				}
			}
			else if(msgBody.addr == APOLLO_INTEG_TIME_DOWN)
			{
				if(msgBody.reply == YES)		// Get register value and return
				{
					usbTxBuff[0] = (APOLLO_INTEG_TIME_DOWN << 1); usbTxBuff[1] = 0;
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = usbRxBuff[1];
				}
				else							// Set register value
				{
					usbTxBuff[0] = (APOLLO_INTEG_TIME_DOWN << 1) + 1; usbTxBuff[1] = msgBody.rxBuf[0];
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = 0;
				}
			}
			else if(msgBody.addr == APOLLO_BLANK_TIME_UP)
			{
				if(msgBody.reply == YES)		// Get register value and return
				{
					usbTxBuff[0] = (APOLLO_BLANK_TIME_UP << 1); usbTxBuff[1] = 0;
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = usbRxBuff[1];
				}
				else							// Set register value
				{
					usbTxBuff[0] = (APOLLO_BLANK_TIME_UP << 1) + 1; usbTxBuff[1] = msgBody.rxBuf[0];
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = 0;
				}
			}
			else if(msgBody.addr == APOLLO_BLANK_TIME_DOWN)
			{
				if(msgBody.reply == YES)		// Get register value and return
				{
					usbTxBuff[0] = (APOLLO_BLANK_TIME_DOWN << 1); usbTxBuff[1] = 0;
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = usbRxBuff[1];
				}
				else							// Set register value
				{
					usbTxBuff[0] = (APOLLO_BLANK_TIME_DOWN << 1) + 1; usbTxBuff[1] = msgBody.rxBuf[0];
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = 0;
				}
			}
			else if(msgBody.addr == APOLLO_ADC)
			{
				if(msgBody.reply == YES)		// Get register value and return
				{
					usbTxBuff[0] = (APOLLO_ADC << 1); usbTxBuff[1] = 0;
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = usbRxBuff[1];
				}
				else							// Set register value
				{
					usbTxBuff[0] = (APOLLO_ADC << 1) + 1; usbTxBuff[1] = msgBody.rxBuf[0];
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = 0;
				}
			}
			else if(msgBody.addr == APOLLO_GAIN)
			{
				if(msgBody.reply == YES)		// Get register value and return
				{
					usbTxBuff[0] = (APOLLO_GAIN << 1); usbTxBuff[1] = 0;
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = usbRxBuff[1];
				}
				else							// Set register value
				{
					usbTxBuff[0] = (APOLLO_GAIN << 1) + 1; usbTxBuff[1] = msgBody.rxBuf[0];
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
					msgBody.txBuf[0] = 0;
				}
			}
			else if(msgBody.addr == APOLLO_TEST_VALUE)
			{
				usbTxBuff[0] = (APOLLO_TEST_VALUE << 1); usbTxBuff[1] = 0;
				HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
				msgBody.txBuf[0] = usbRxBuff[1];
			}
			else if(msgBody.addr == APOLLO_SENSOR_ID_01)
			{
				usbTxBuff[0] = (APOLLO_SENSOR_ID_01 << 1); usbTxBuff[1] = 0;
				HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
				msgBody.txBuf[0] = usbRxBuff[1];
				usbTxBuff[0] = (APOLLO_SENSOR_ID_02 << 1); usbTxBuff[1] = 0;
				HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
				msgBody.txBuf[1] = usbRxBuff[1];
				usbTxBuff[0] = (APOLLO_SENSOR_ID_03 << 1); usbTxBuff[1] = 0;
				HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
				msgBody.txBuf[2] = usbRxBuff[1];
				usbTxBuff[0] = (APOLLO_SENSOR_ID_04 << 1); usbTxBuff[1] = 0;
				HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
				msgBody.txBuf[3] = usbRxBuff[1];
				usbTxBuff[0] = (APOLLO_SENSOR_ID_05 << 1); usbTxBuff[1] = 0;
				HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)usbTxBuff, (uint8_t *)usbRxBuff, 2, 5000);
				msgBody.txBuf[4] = usbRxBuff[1];
			}
		}
		break;

	case STM32_ONBOARD_CONTROL:
		break;
		
	default:
	  break;
	}

	HAL_NVIC_EnableIRQ(EXTI1_IRQn);

	return 0;
}

int GenPreProcMsg(uint8_t messageType, uint8_t addr, uint16_t value, uint8_t readOrWrite)
{  	
	memset(&msgBody, 0, sizeof(msgBody));

	switch (messageType)
	{	
		case USB_TO_SENSOR_CMD:
		{
			if(addr == APOLLO_MODE_SELECTION)
			{
				if (value < 0x04)
				{
					msgBody.source = PC_USB;
					msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
					msgBody.length = 1;
					msgBody.addr= APOLLO_MODE_SELECTION;
					msgBody.rxBuf[0] = (uint8_t)value;
				}        
				else
					return -1;
			}
			else if(addr == APOLLO_INTEG_TIME_UP)
			{
				msgBody.source = PC_USB;
				msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
				msgBody.length = 1;
				msgBody.addr = APOLLO_INTEG_TIME_UP;
				msgBody.rxBuf[0] = (uint8_t)(value >> 8);
			}
			else if(addr == APOLLO_INTEG_TIME_DOWN)
			{
				msgBody.source = PC_USB;
				msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
				msgBody.length = 1;
				msgBody.addr = APOLLO_INTEG_TIME_DOWN;
				msgBody.rxBuf[0] = (uint8_t)(value >> 8);
			}
			else if(addr == APOLLO_BLANK_TIME_UP)
			{
				msgBody.source = PC_USB;
				msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
				msgBody.length = 1;
				msgBody.addr = APOLLO_BLANK_TIME_UP;
				msgBody.rxBuf[0] = (uint8_t)(value >> 8);
			}
			else if(addr == APOLLO_BLANK_TIME_DOWN)
			{
				msgBody.source = PC_USB;
				msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
				msgBody.length = 1;
				msgBody.addr = APOLLO_BLANK_TIME_DOWN;
				msgBody.rxBuf[0] = (uint8_t)(value >> 8);
			}
			else if(addr == APOLLO_ADC)
			{
				msgBody.source = PC_USB;
				msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
				msgBody.length = 1;
				msgBody.addr = APOLLO_ADC;
				msgBody.reply = readOrWrite;
				msgBody.rxBuf[0] = (uint8_t)value;
			}
			else if(addr == APOLLO_TEST_VALUE)
			{
				msgBody.source = PC_USB;
				msgBody.dest = APOLLO_SENSOR_CTRL_SPI;
				msgBody.length = 1;
				msgBody.addr = APOLLO_TEST_VALUE;
				msgBody.reply = readOrWrite;
				msgBody.rxBuf[0] = (uint8_t)(value >> 8);
			}
		}
		break;
	}

	mainState = MESSAGE_PROCESS_STATE;
	return 0;
}

