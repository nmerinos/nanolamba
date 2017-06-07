/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/main.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    01-July-2015
  * @brief   This example describes how to configure and use GPIOs through 
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "utils.h"



uint8_t LocalTxBuffer[2048];

/* Private typedef -----------------------------------------------------------*/



/* Private define ------------------------------------------------------------*/
// Jesse
#define LOOP_FOR_FRAME  10
//#define LOOP_FOR_FRAME  2000
//#define LOOP_FOR_FRAME  7582
//#define FPS_REPORT
#define FLASH_USER_START_ADDR   				ADDR_FLASH_SECTOR_12   			/* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     				ADDR_FLASH_SECTOR_13   			/* End @ of user Flash area */
#define DATA_32                 						((uint32_t)0x12345678)



/* Private macro -------------------------------------------------------------*/




/* Private variables ---------------------------------------------------------*/
/* Sensor Control SPI CS - PA4 */
GPIO_InitTypeDef GPIO_Sensor_Control_CS;

/* I2C handler declaration */
I2C_HandleTypeDef I2cHandle;

/* SPI handler declaration */
SPI_HandleTypeDef SpiHandle;
SPI_HandleTypeDef SpiSensorDataHandle;

/* USB handler declaration */
USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;

uint8_t aRxBuffer[BUFFERSIZE];
uint8_t aTxBuffer[BUFFERSIZE];
uint8_t reBuffer[2048];
uint8_t MySensorID[5];

uint16_t tempPixelData=0;
uint16_t currentIntegTime=0;
uint32_t timerCountforSensorID=0;
volatile int mainState = NORMAL_STATE;
volatile int returnState = NORMAL_STATE;
volatile int messageIn = 0;
volatile int flagVsync = 0;														// Sensor's Vsync interrupt flag
volatile int flagHsync = 0;														// Sensor's Hsync interrupt flag
volatile int bulkState = 0;														// UBS Bluk mode, Frame data send to USB(PC HOST).
volatile int flagRxSpi = 0;

int uartBufCount = 0;
int sBufCount=0;
int dBufCount=0;
int shiftCount=0;
int chkSum=0;
int kCount, jCount, mCount;
int flagHsyncCount=0;
int serialCmdCount=0;

_CommonMsg msgBody;

/* Timer handler declaration */
TIM_HandleTypeDef    TimHandle;

static void SystemClock_Config(void);
static void SPI_CTR_Config(void);
static void SPI_Recv_Config(void);
static void EXTI_VSync_Config(void);
static void EXTI_HSync_Config(void);


/**
  * @brief  Main program
  * @param  None
  * @retval None
*/
int main(void)
{

	HAL_Init();

	/* Configure the system clock to 168 MHz */
	SystemClock_Config();
	
	/* Init Device Library */
	USBD_Init(&USBD_Device, &HID_Desc, 0);
	
	/* Add Supported Class */
	USBD_RegisterClass(&USBD_Device, USBD_HID_CLASS);
	
	/* Add CDC Interface Class */
	USBD_JUSB_RegisterInterface(&USBD_Device, &USBD_JUSB_fops);
	
	/* Start Device Process */
	USBD_Start(&USBD_Device);
	
	__HAL_RCC_GPIOB_CLK_ENABLE(); 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	
	SPI_CTR_Config();
	SPI_Recv_Config();
	if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	if(HAL_SPI_Init(&SpiSensorDataHandle) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
  
	while (HAL_SPI_GetState(&SpiHandle) != HAL_SPI_STATE_READY)
	{
	} 
	while (HAL_SPI_GetState(&SpiSensorDataHandle) != HAL_SPI_STATE_READY)
	{
	} 

	/* Configure LED */
	BSP_LED_Init(LED1); 
	BSP_LED_Off(LED1);
	
	/* Configure VSync/HSync GPIO interrupt */
	EXTI_VSync_Config();
	EXTI_HSync_Config();	

	/* Set initial value to sensor */
	setSensorInitValue();
	
	/* VSync interrupt enable */
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);

	/* Start the TIM Base generation in interrupt mode */
	if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
	{
		Error_Handler();
	}

	/* Turn on LED ceremony for ADK board */
	for(int tempCount=0; tempCount<20; tempCount++)
	{
		BSP_LED_Toggle(LED1);
		HAL_Delay(50);
	}
	BSP_LED_Off(LED1);

	/* Initial mainState value */ 
	mainState = FRAME_SYNC_STATE;
				
	/* Infinite loop */
	while (1)
	{          
		switch(mainState)
		{
			case NORMAL_STATE:
			break;

			case MESSAGE_PROCESS_STATE:
				returnState =  GlobalMessageHandler();

				if ( returnState < 0 )
					Error_Handler();
				else if (returnState == CONTINUE_CAPTURE_STATE)
					mainState = CONTINUE_CAPTURE_STATE;
				else if (returnState == SINGLE_CAPTURE_STATE)
					mainState = SINGLE_CAPTURE_STATE;
				else
					mainState = NORMAL_STATE;
			break;

			case SINGLE_CAPTURE_STATE:
				mainState = NORMAL_STATE;
			break;

			case FRAME_SYNC_STATE:
				aTxBuffer[0] = (APOLLO_MODE_SELECTION << 1) + 1; aTxBuffer[1] = POWER_ON_WAITING_MODE;
				HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, 2, 5000);
				memset(aRxBuffer, 0, BUFFERSIZE);
				memset(reBuffer, 0, sizeof(reBuffer));
				HAL_Delay(10);
				
				while(1)
				{
					BSP_LED_Toggle(LED1);
					aTxBuffer[0] = (APOLLO_MODE_SELECTION << 1) + 1; aTxBuffer[1] = CONTINUOUS_FRAME_MODE;						
					HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, 2, 5000);
					
					HAL_Delay(1);						
					
					/* Check the frame form Sensor frame data */
					if( (aRxBuffer[9] == 0x00) && (aRxBuffer[10] == 0x00) && (aRxBuffer[11] == 0x00) && (aRxBuffer[12] == 0x7F) && (aRxBuffer[13] == 0xFF) && (aRxBuffer[14] == 0xFF))
					//if( (aRxBuffer[10] == 0x00) && (aRxBuffer[11] == 0x00) && (aRxBuffer[12] == 0x00) && (aRxBuffer[13] == 0x7F) && (aRxBuffer[14] == 0xFF) && (aRxBuffer[15] == 0xFF))
					{
						memset(aRxBuffer, 0, BUFFERSIZE);
						mainState = CONTINUE_CAPTURE_STATE;						
						BSP_LED_Off(LED1);
						break;
					}
					else
					{
						aTxBuffer[0] = (APOLLO_MODE_SELECTION << 1) + 1; aTxBuffer[1] = POWER_ON_WAITING_MODE;
						HAL_SPI_TransmitReceive(&SpiHandle, (uint8_t *)aTxBuffer, (uint8_t *)aRxBuffer, 2, 5000);
						memset(aRxBuffer, 0, BUFFERSIZE);
						HAL_Delay(2);
					}					
					flagVsync=0;
				}	
			break;

			case CONTINUE_CAPTURE_STATE:					
				
			  	/* Check flagVSync */
			  	if(flagVsync == 1)
		  		{
					for(kCount=0; kCount<32; kCount++)
					{
						memcpy(reBuffer+(kCount*64), aRxBuffer+12+48+(112*kCount), 64);
						//memcpy(reBuffer+(kCount*64), aRxBuffer+(112*kCount+1), 64);
					}
					
					/* USB transmit, Bulk mode */
					if (bulkState == 1)
					{
						USBD_JUSB_SetTxBuffer(&USBD_Device, reBuffer, 2048);
						USBD_JUSB_TransmitPacket(&USBD_Device);

						USBD_HID_HandleTypeDef *hcdc = USBD_Device.pClassData;
						while(1)
						{								
							if(hcdc->TxState == 0)
							  break;
						}						
						memset(reBuffer, 0, 2048);							
					}					
					flagVsync = 0;
			  	}
            break;

			default:
			break;
		}
	}                
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  //RCC_OscInitStruct.PLL.PLLN = 360;					// 180Mhz
  RCC_OscInitStruct.PLL.PLLN = 336;						// 168Mhz, De for USB FS interface
  //RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;			// 180Mhz
  RCC_OscInitStruct.PLL.PLLP = 2;						// 168Mhz for USB FS interface
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  // ***********************************************************
  // Jesse - usb port is not working if below function is called
  /* Activate the Over-Drive mode */
  //HAL_PWREx_EnableOverDrive();
    
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}


/* Apollo sensor control SPI, Master */ 
void SPI_CTR_Config(void)
{
	/*##-1- Configure the SPI peripheral #################################*/
	/* Set the SPI parameters */
	SpiHandle.Instance					= SPIx;
	SpiHandle.Init.Mode					= SPI_MODE_MASTER;
	SpiHandle.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_32;
	SpiHandle.Init.Direction			= SPI_DIRECTION_2LINES;
	SpiHandle.Init.CLKPhase				= SPI_PHASE_1EDGE;
	SpiHandle.Init.CLKPolarity			= SPI_POLARITY_LOW;
	SpiHandle.Init.CRCCalculation		= SPI_CRCCALCULATION_DISABLE;
	SpiHandle.Init.CRCPolynomial		= 7;
	SpiHandle.Init.DataSize				= SPI_DATASIZE_8BIT;
	SpiHandle.Init.FirstBit				= SPI_FIRSTBIT_MSB;
	SpiHandle.Init.NSS					= SPI_NSS_SOFT;
	SpiHandle.Init.TIMode				= SPI_TIMODE_DISABLE;
}

/* Apollo sensor data SPI, Slave */ 
void SPI_Recv_Config(void)
{
	/*##-1- Configure the SPI peripheral #######################################*/
	/* Set the SPI parameters */
	SpiSensorDataHandle.Instance				= SPIa;
	SpiSensorDataHandle.Init.Mode 				= SPI_MODE_SLAVE;
	SpiSensorDataHandle.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_2;
	SpiSensorDataHandle.Init.Direction			= SPI_DIRECTION_2LINES_RXONLY;
	SpiSensorDataHandle.Init.CLKPhase			= SPI_PHASE_1EDGE;
	SpiSensorDataHandle.Init.CLKPolarity		= SPI_POLARITY_HIGH;
	SpiSensorDataHandle.Init.CRCCalculation		= SPI_CRCCALCULATION_DISABLE;
	SpiSensorDataHandle.Init.CRCPolynomial		= 7;
	SpiSensorDataHandle.Init.DataSize			= SPI_DATASIZE_8BIT;
	SpiSensorDataHandle.Init.FirstBit			= SPI_FIRSTBIT_MSB;
	SpiSensorDataHandle.Init.NSS				= SPI_NSS_SOFT;
	SpiSensorDataHandle.Init.TIMode				= SPI_TIMODE_DISABLE;
}


/*void I2C_Config(void)
{
	I2cHandle.Instance				= I2Cx;
	I2cHandle.Init.AddressingMode	= I2C_ADDRESSINGMODE_7BIT;
	I2cHandle.Init.ClockSpeed		= 100000;
	I2cHandle.Init.DualAddressMode	= I2C_DUALADDRESS_DISABLE;
	I2cHandle.Init.DutyCycle		= I2C_DUTYCYCLE_2;
	I2cHandle.Init.GeneralCallMode	= I2C_GENERALCALL_DISABLE;
	I2cHandle.Init.NoStretchMode	= I2C_NOSTRETCH_DISABLE;
	I2cHandle.Init.OwnAddress1		= MY_I2C_ADDRESS;
	I2cHandle.Init.OwnAddress2		= 0xFF;
}*/

/* PG10 External Interrupt config */
static void EXTI_VSync_Config(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	__HAL_RCC_GPIOD_CLK_ENABLE();

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = GPIO_PIN_1;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
	//HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* PG11 External Interrupt config */
static void EXTI_HSync_Config(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	/* Enable GPIOG clock */
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/* Configure PC13 pin as input floating */
	GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = GPIO_PIN_2;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Enable and set EXTI15_10 Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(EXTI2_IRQn, 1, 1);
	//HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
	//BSP_LED_On(LED1);
}
     
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef * I2cHandle)
{
	//BSP_LED_On(LED1);
}
     
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
	//BSP_LED_On(LED1);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * hspi)
{
	//BSP_LED_Toggle(LED1);
	flagRxSpi = 1;
}

/**
  * @brief  TxRx Transfer completed callback.
  * @param  hspi: SPI handle.
  * @note   This example shows a simple way to report end of Interrupt TxRx transfer, and 
  *         you can add your own implementation. 
  * @retval None
  */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	//BSP_LED_On(LED1);
}

/**
  * @brief  SPI error callbacks.
  * @param  hspi: SPI handle
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @retval None
  */
 void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
{
	//BSP_LED_On(LED2);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
}

void Error_Handler(void)
{  
	while(1)
	{
		BSP_LED_On(LED1);
		HAL_Delay(100);
		BSP_LED_Off(LED1);
		HAL_Delay(100);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{ 
	switch(GPIO_Pin)
	{
		case GPIO_PIN_1:
			//BSP_LED_Toggle(LED1);
			HAL_SPI_Receive(&SpiSensorDataHandle, aRxBuffer, 3597, 5000);
			flagVsync = 1;
		break;
		case GPIO_PIN_2:
			flagHsync = 1;
		break;
		default:
		break;
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
}

void USBMessageHandler(void)
{
	uint8_t ret = USBD_IsDataReceived();
	if(ret == 1)  // start bulk transfer
	{
		bulkState = 1;
		USBD_SetDataReceived(0);	
	}
	else if(ret == 2)// stop bulk transfer
	{    
		bulkState = 2;
		USBD_SetDataReceived(0);
	}
}



void nop(int count)
{
  while(count)
  {
  	__NOP();
	count--;
  }
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
