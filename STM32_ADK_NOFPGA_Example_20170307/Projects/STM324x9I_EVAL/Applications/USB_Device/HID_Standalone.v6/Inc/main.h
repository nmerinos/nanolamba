/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    01-July-2015
  * @brief   Header for main.c module
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H



/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_hid.h"
#include "usbd_apollo_interface.h"
#include "stm324x9i_eval.h"
#include "stdio.h"
#include "core_cmInstr.h"



/* Exported types --
----------------------------------------------------------*/
typedef struct CommonMsg
{
	uint8_t source;
	uint8_t dest;
	uint8_t addr;
	uint8_t length;
	uint8_t reply;
	uint8_t rxBuf[2048];
	uint8_t txBuf[2048];
} _CommonMsg;

extern _CommonMsg msgBody;
extern volatile int messageIn;
extern volatile int mainState;
extern SPI_HandleTypeDef SpiSensorDataHandle;
extern SPI_HandleTypeDef SpiHandle;
extern UART_HandleTypeDef UartHandleBlue;
extern uint8_t MySensorID[5];						// this array declared at main.c


/* Exported constants --------------------------------------------------------*/
#define TRUE									1
#define FALSE									0
#define YES										1
#define NO										0
#define READ_DEVICE								1
#define WRITE_DEVICE							0

/********************************* CC2541 UART *********************************/
#define USARTy                      			UART7								
#define USARTy_CLK_ENABLE()            			__HAL_RCC_UART7_CLK_ENABLE();	/* Definition for USARTy clock resources */
#define USARTy_RX_GPIO_CLK_ENABLE()     		__HAL_RCC_GPIOE_CLK_ENABLE()
#define USARTy_TX_GPIO_CLK_ENABLE()     		__HAL_RCC_GPIOE_CLK_ENABLE() 
#define USARTy_FORCE_RESET()           			__HAL_RCC_UART7_FORCE_RESET()
#define USARTy_RELEASE_RESET()					__HAL_RCC_UART7_RELEASE_RESET()

#define USARTy_TX_PIN               			GPIO_PIN_8						/* Definition for USARTy Pins */
#define USARTy_TX_GPIO_PORT            			GPIOE
#define USARTy_TX_AF                   			GPIO_AF8_UART7
#define USARTy_RX_PIN                   		GPIO_PIN_7
#define USARTy_RX_GPIO_PORT             		GPIOE
#define USARTy_RX_AF                    		GPIO_AF8_UART7

#define USARTy_IRQn								UART7_IRQn						/* Definition for USARTy's NVIC */
#define USARTy_IRQHandler						UART7_IRQHandler

//********************************* Debug UART /*********************************/
#define USARTx                          		USART3                                 
#define USARTx_CLK_ENABLE()            			__HAL_RCC_USART3_CLK_ENABLE();	/* Definition for USARTx clock resources */
#define USARTx_RX_GPIO_CLK_ENABLE()     		__HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()     		__HAL_RCC_GPIOD_CLK_ENABLE() 
#define USARTx_FORCE_RESET()            		__HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()          		__HAL_RCC_USART3_RELEASE_RESET()

#define USARTx_TX_PIN                   		GPIO_PIN_8						/* Definition for USARTx Pins */
#define USARTx_TX_GPIO_PORT             		GPIOD
#define USARTx_TX_AF                    		GPIO_AF7_USART3
#define USARTx_RX_PIN                   		GPIO_PIN_9
#define USARTx_RX_GPIO_PORT             		GPIOD
#define USARTx_RX_AF                    		GPIO_AF7_USART3

#define USARTx_IRQn								USART3_IRQn						/* Definition for USARTx's NVIC */
#define USARTx_IRQHandler						USART3_IRQHandler


/* SPI DMA Communication */
#define SPI_DMA_COMM

/* SPIx --> Apollo sensor controll SPI port */
#define SPIx									SPI3
#define SPIx_CLK_ENABLE()						__HAL_RCC_SPI3_CLK_ENABLE()
#define SPIx_CS_GPIO_CLK_ENABLE()				__HAL_RCC_GPIOA_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()				__HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()				__HAL_RCC_GPIOC_CLK_ENABLE() 
#define SPIx_MOSI_GPIO_CLK_ENABLE()     		__HAL_RCC_GPIOC_CLK_ENABLE()
#define SPIx_FORCE_RESET()						__HAL_RCC_SPI3_FORCE_RESET()
#define SPIx_RELEASE_RESET()					__HAL_RCC_SPI3_RELEASE_RESET()
#define SPIx_CS_PIN								GPIO_PIN_4                           
#define SPIx_CS_GPIO_PORT						GPIOA
#define SPIx_CS_AF								GPIO_AF6_SPI3
#define SPIx_SCK_PIN							GPIO_PIN_10
#define SPIx_SCK_GPIO_PORT						GPIOC
#define SPIx_SCK_AF								GPIO_AF6_SPI3
#define SPIx_MISO_PIN							GPIO_PIN_11
#define SPIx_MISO_GPIO_PORT						GPIOC
#define SPIx_MISO_AF							GPIO_AF6_SPI3
#define SPIx_MOSI_PIN							GPIO_PIN_12
#define SPIx_MOSI_GPIO_PORT						GPIOC
#define SPIx_MOSI_AF							GPIO_AF6_SPI3
#define SPIx_IRQn								SPI3_IRQn						/* Definition for SPIx's NVIC */
#define SPIx_IRQHandler							SPI3_IRQHandler

/* SPIa --> Apollo sensor frame SPI port */
#define SPIa									SPI4							/* Definition for SPIx clock resources */
#define SPIa_CLK_ENABLE()						__HAL_RCC_SPI4_CLK_ENABLE()
#ifdef SPI_DMA_COMM
#define DMAx_CLK_ENABLE()						__HAL_RCC_DMA2_CLK_ENABLE()
#endif
#define SPIa_SCK_GPIO_CLK_ENABLE()				__HAL_RCC_GPIOE_CLK_ENABLE()
#define SPIa_MISO_GPIO_CLK_ENABLE()				__HAL_RCC_GPIOE_CLK_ENABLE() 
#define SPIa_MOSI_GPIO_CLK_ENABLE()				__HAL_RCC_GPIOE_CLK_ENABLE()
#define SPIa_FORCE_RESET()						__HAL_RCC_SPI4_FORCE_RESET()
#define SPIa_RELEASE_RESET()					__HAL_RCC_SPI4_RELEASE_RESET()
#define SPIa_CS_PIN								GPIO_PIN_11                     /* Definition for SPIx Pins */
#define SPIa_CS_GPIO_PORT						GPIOE
#define SPIa_CS_AF								GPIO_AF5_SPI4
#define SPIa_SCK_PIN							GPIO_PIN_12
#define SPIa_SCK_GPIO_PORT						GPIOE
#define SPIa_SCK_AF								GPIO_AF5_SPI4
#define SPIa_MISO_PIN							GPIO_PIN_13
#define SPIa_MISO_GPIO_PORT						GPIOE
#define SPIa_MISO_AF							GPIO_AF5_SPI4
#define SPIa_MOSI_PIN							GPIO_PIN_14
#define SPIa_MOSI_GPIO_PORT						GPIOE
#define SPIa_MOSI_AF							GPIO_AF5_SPI4
#define SPIa_IRQn								SPI4_IRQn                       /* Definition for SPIx's NVIC */
#define SPIa_IRQHandler							SPI4_IRQHandler
#ifdef SPI_DMA_COMM
#define SPIa_TX_DMA_CHANNEL						DMA_CHANNEL_4
#define SPIa_TX_DMA_STREAM						DMA2_Stream1
#define SPIa_RX_DMA_CHANNEL						DMA_CHANNEL_4
#define SPIa_RX_DMA_STREAM						DMA2_Stream0
#define SPIa_DMA_TX_IRQn						DMA2_Stream1_IRQn
#define SPIa_DMA_RX_IRQn						DMA2_Stream0_IRQn
#define SPIa_DMA_TX_IRQHandler					DMA2_Stream1_IRQHandler
#define SPIa_DMA_RX_IRQHandler					DMA2_Stream0_IRQHandler
#endif

//#define BUFFERSIZE                       (COUNTOF(aTxBuffer) - 1)             /* Size of buffer */
#define BUFFERSIZE                       3596									//3584+12

/* User can use this section to tailor I2Cx/I2Cx instance used and associated resources */
#define I2Cx                            		I2C1                            /* Definition for I2Cx clock resources */
#define I2Cx_CLK_ENABLE()						__HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()				__HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()				__HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_FORCE_RESET()						__HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()					__HAL_RCC_I2C1_RELEASE_RESET()

#define I2Cx_SCL_PIN							GPIO_PIN_6                      /* Definition for I2Cx Pins */
#define I2Cx_SCL_GPIO_PORT						GPIOB
#define I2Cx_SCL_AF								GPIO_AF4_I2C1
#define I2Cx_SDA_PIN							GPIO_PIN_7
#define I2Cx_SDA_GPIO_PORT						GPIOB
#define I2Cx_SDA_AF								GPIO_AF4_I2C1

#define I2Cx_EV_IRQn							I2C1_EV_IRQn                    /* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQHandler						I2C1_EV_IRQHandler
#define I2Cx_ER_IRQn							I2C1_ER_IRQn
#define I2Cx_ER_IRQHandler						I2C1_ER_IRQHandler


#define TXBUFFERSIZE                    		(COUNTOF(aTxBuffer) - 1)        /* Size of Transmission buffer */
#define RXBUFFERSIZE                    		TXBUFFERSIZE                    /* Size of Reception buffer */

#define MY_I2C_ADDRESS                  		0x54

/* MAINSTATE */
#define NORMAL_STATE							0xF1							// Normal state
#define MESSAGE_PROCESS_STATE           		0xF2							// Message processing 
#define SINGLE_CAPTURE_STATE            		0xF3							// For single capture mode
#define CONTINUE_CAPTURE_STATE          		0xF4							// For continuous capture mode
#define VSYNC_BULK_STATE						0xF5
#define FRAME_SYNC_STATE						0xF6							// Synchronize time of acquisition for SPI interface

/* Message handler message type for Apollo sensor */
#define APOLLO_MODE_SELECTION           		0x00
#define APOLLO_INTEG_TIME_UP            		0x01
#define APOLLO_INTEG_TIME_DOWN          		0x02
#define APOLLO_BLANK_TIME_UP            		0x03
#define APOLLO_BLANK_TIME_DOWN          		0x04
#define APOLLO_START_ROW						0x05
#define APOLLO_START_COL						0x06
#define APOLLO_NUMBER_ROW_READ					0x07
#define APOLLO_NUMBER_COL_READ					0x08
#define APOLLO_ADC								0x09
#define APOLLO_GAIN								0x0a
#define APOLLO_TEST_VALUE               		0x0b
#define APOLLO_SENSOR_ID_01             		0x0d
#define APOLLO_SENSOR_ID_02             		0x0e
#define APOLLO_SENSOR_ID_03             		0x0f
#define APOLLO_SENSOR_ID_04             		0x10
#define APOLLO_SENSOR_ID_05             		0x11
#define APOLLO_INTEG_TIME_TOTAL         		0x21
#define APOLLO_BLANK_TIME_TOTAL					0x22

/* Apollo sensor acquisition mode */
#define POWER_SAVING_MODE						0x00
#define POWER_ON_WAITING_MODE           		0x01
#define SINGLE_FRAME_MODE						0x02
#define CONTINUOUS_FRAME_MODE           		0x03

/* Message handler source and destination definition */
#define PC_USB									0x21
#define EXT_MCU_I2C								0x23
#define EXT_MCU_UART							0x24
#define EXT_MCU_SPI								0x25

#define APOLLO_SENSOR_CTRL_SPI					0x34
#define APOLLO_SENSOR_DATA_SPI					0x35
#define STM32_ONBOARD_CONTROL					0x36

/* Generation message type */
#define USB_TO_SENSOR_CMD						0x41
#define USB_TO_DS1086_CMD						0x42
#define SENSOR_TO_USB_DATA

/* Commands for USB communication */
#define EFM32_COMM_NO_OP						0x00							// 8 bytes
#define EFM32_COMM_GET_SENSOR_ID				0x01							// 8 bytes
#define EFM32_COMM_GET_SENSOR_DATA				0x02							// 2048 bytes
#define EFM32_COMM_SET_ACQUIRE_MODE				0x03							// 1(single=sw trigger), 2(continous),3(time-interval),4(hw trigger)
#define EFM32_COMM_GET_LOW_EXPOSURE_TIME		0x04							// 1 byte
#define EFM32_COMM_GET_UPPER_EXPOSURE_TIME		0x24							// 1 byte
#define EFM32_COMM_SET_LOW_EXPOSURE_TIME		0x05							// 1 byte
#define EFM32_COMM_SET_UPPER_EXPOSURE_TIME		0x25							// 1 byte
#define EFM32_COMM_GET_SENSOR_STATUS			0x06							// 1 byte
#define EFM32_COMM_GET_CONTROLLER_STATUS		0x07							// 1 byte
#define EFM32_COMM_GET_LED_STATUS				0x08							// 4 bytes
#define EFM32_COMM_SET_LED_STATUS				0x09							// 2 bytes
#define EFM32_COMM_GET_ERROR					0x0a							// 1 byte
#define EFM32_COMM_GET_SPECTRUM					0x0b							// 2048 bytes (actually 4 * wavelength rage (711)) about 3000 bytes
#define EFM32_COMM_GET_XYZ						0x0c							// 12 bytes
#define EFM32_COMM_GET_AMBIENT					0x0d							// 4 bytes
#define EFM32_COMM_SET_MCU_MODE					0x0e							// 1 byte
#define EFM32_COMM_SET_ROI_START_POS			0x11							// 4 bytes
#define EFM32_COMM_SET_ROI_SIZE					0x12							// 4 bytes
#define EFM32_COMM_SET_ADC_RANGE				0x13							// 1 byte
#define EFM32_COMM_SET_AMP_GAIN_RESOLUTION		0x14							// 1 byte
#define EFM32_COMM_INIT_ACQ						0x16							// 1 byte
#define EFM32_COMM_FIN_ACQ						0x17							// 1 byte
#define EFM32_COMM_READ_REGISTER				0x18							// 1 byte
#define EFM32_COMM_WRITE_REGISTER				0x19							// 1 byte
#define EFM32_COMM_SET_LED_TOGGLE				0x20							// 2 bytes
#define EFM32_COMM_SET_LOW_BLANK_TIME			0x21							// 1 byte
#define EFM32_COMM_SET_UPPER_BLANK_TIME			0x22							// 1 byte
#define EFM32_COMM_GET_ADC_RANGE				0x23							// 1 byte
#define EFM32_COMM_GET_LOW_BLANK_TIME			0x26							// 1 byte
#define EFM32_COMM_GET_UPPER_BLANK_TIME			0x27							// 1 byte
#define EFM32_COMM_GET_AMP_GAIN_RESOLUTION		0x28							// 1 byte

// added by KSLEE, 2014.07.08, for TitanSensorTester (register I/O test)
#define EFM32_COMM_GET_TEST_BYTE				0x29    						// 1 byte        
#define EFM32_COMM_GET_START_ROW				0x2a    						// 1 byte        
#define EFM32_COMM_SET_START_ROW				0x31    						// 1 byte        
#define EFM32_COMM_GET_START_COL				0x2b    						// 1 byte        
#define EFM32_COMM_SET_START_COL				0x32    						// 1 byte        
#define EFM32_COMM_GET_NUMB_ROW					0x2c    						// 1 byte        
#define EFM32_COMM_SET_NUMB_ROW					0x33    						// 1 byte        
#define EFM32_COMM_GET_NUMB_COL					0x2d    						// 1 byte        
#define EFM32_COMM_SET_NUMB_COL					0x34    						// 1 byte         

// On-board processings
#define EFM32_COMM_GET_FRAME_AVERAGE			0x35    						// 1 byte        //2014.08.01
#define EFM32_COMM_SET_FRAME_AVERAGE			0x36    						// 1 byte        //2014.08.01
#define EFM32_COMM_BURST_MODE_TEST				0x37    						// 1 byte        //2014.08.03
#define EFM32_COMM_GET_DARK_FRAME				0x38    						// 1 byte        //2014.08.05
#define EFM32_COMM_SET_DARK_CORRECTION_MODE		0x39    						// 1 byte        //2014.08.05
#define EFM32_COMM_GET_DARK_CORRECTION_MODE		0x3a    						// 1 byte        //2014.08.05

#define EFM32_COMM_SET_POI_COUNT				0x40    						// 1 byte        //2014.08.08
#define EFM32_COMM_GET_POI_COUNT				0x41    						// 1 byte        //2014.08.08
#define EFM32_COMM_CLEAR_POI_INDEX_LIST			0x42    						// 1 byte         // 2014.08.11
#define EFM32_COMM_SET_POI_INDEX_LIST			0x43    						// 1 byte        //2014.08.08
#define EFM32_COMM_GET_POI_INDEX_LIST			0x44    						// 1 byte        //2014.08.08
#define EFM32_COMM_GET_POI_DATA					0x45    						// 1 byte        //2014.08.08

#define EFM32_COMM_SET_EXPOSURE_TIME			0x50    						// 1 integer    // 2014.09.05
#define EFM32_COMM_SET_BLANK_TIME				0x51    						// 1 integer    // 2014.09.05
#define EFM32_COMM_GET_SENSOR_DATA_TEST			0x81							// 2048 bytes

#define EFM32_COMM_REBOOT						0xff							// 1 byte


/* Definition for TIMx clock resources */
#define TIMx									TIM3
#define TIMx_CLK_ENABLE							__HAL_RCC_TIM3_CLK_ENABLE
/* Definition for TIMx's NVIC */
#define TIMx_IRQn								TIM3_IRQn
#define TIMx_IRQHandler							TIM3_IRQHandler



     
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* Base address of the Flash sectors Bank 1 */
#define ADDR_FLASH_SECTOR_0						((uint32_t)0x08000000) 			/* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     				((uint32_t)0x08004000) 			/* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     				((uint32_t)0x08008000) 			/* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     				((uint32_t)0x0800C000) 			/* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     				((uint32_t)0x08010000) 			/* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     				((uint32_t)0x08020000) 			/* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     				((uint32_t)0x08040000) 			/* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     				((uint32_t)0x08060000) 			/* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     				((uint32_t)0x08080000) 			/* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     				((uint32_t)0x080A0000) 			/* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    				((uint32_t)0x080C0000) 			/* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    				((uint32_t)0x080E0000) 			/* Base @ of Sector 11, 128 Kbytes */

/* Base address of the Flash sectors Bank 2 */
#define ADDR_FLASH_SECTOR_12     				((uint32_t)0x08100000) 			/* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_13     				((uint32_t)0x08104000) 			/* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_14     				((uint32_t)0x08108000) 			/* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_15     				((uint32_t)0x0810C000) 			/* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_16     				((uint32_t)0x08110000) 			/* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_17     				((uint32_t)0x08120000) 			/* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_18     				((uint32_t)0x08140000) 			/* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_19     				((uint32_t)0x08160000) 			/* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_20     				((uint32_t)0x08180000) 			/* Base @ of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_21     				((uint32_t)0x081A0000)			/* Base @ of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_22     				((uint32_t)0x081C0000) 			/* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_23     				((uint32_t)0x081E0000) 			/* Base @ of Sector 11, 128 Kbytes */
	


/* Exported functions ------------------------------------------------------- */
int GenPreProcMsg(uint8_t messageType, uint8_t addr, uint16_t value, uint8_t readOrWrite);
void USBMessageHandler(void);
int DebugCmdHandler(uint8_t *cmd);
int GlobalMessageHandler(void);
void nop(int count);
void Error_Handler(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
