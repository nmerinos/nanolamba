/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/stm32f4xx_hal_msp.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    01-July-2015
  * @brief   HAL MSP module.    
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
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
	if (huart->Instance == USARTx)
	{
		GPIO_InitTypeDef  GPIO_InitStruct;  
		
		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		USARTx_TX_GPIO_CLK_ENABLE();
		USARTx_RX_GPIO_CLK_ENABLE();
		/* Enable USART1 clock */
		USARTx_CLK_ENABLE(); 

		/*##-2- Configure peripheral GPIO ##########################################*/  
		/* UART TX GPIO pin configuration  */
		GPIO_InitStruct.Pin       = USARTx_TX_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = USARTx_TX_AF;

		HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

		/* UART RX GPIO pin configuration  */
		GPIO_InitStruct.Pin = USARTx_RX_PIN;
		GPIO_InitStruct.Alternate = USARTx_RX_AF;

		HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

		HAL_NVIC_SetPriority(USARTx_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(USARTx_IRQn);
	}
	else if (huart->Instance == USARTy)
	{
		GPIO_InitTypeDef  GPIO_InitStruct;  
		
		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		USARTy_TX_GPIO_CLK_ENABLE();
		USARTy_RX_GPIO_CLK_ENABLE();
		/* Enable USART1 clock */
		USARTy_CLK_ENABLE(); 

		/*##-2- Configure peripheral GPIO ##########################################*/  
		/* UART TX GPIO pin configuration  */
		GPIO_InitStruct.Pin       = USARTy_TX_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = USARTy_TX_AF;

		HAL_GPIO_Init(USARTy_TX_GPIO_PORT, &GPIO_InitStruct);

		/* UART RX GPIO pin configuration  */
		GPIO_InitStruct.Pin = USARTy_RX_PIN;
		GPIO_InitStruct.Alternate = USARTy_RX_AF;

		HAL_GPIO_Init(USARTy_RX_GPIO_PORT, &GPIO_InitStruct);

		HAL_NVIC_SetPriority(USARTy_IRQn, 2, 1);
		HAL_NVIC_EnableIRQ(USARTy_IRQn);
	}

}

/**
  * @brief UART MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);

  /*##-3- Disable the NVIC for UART ##########################################*/
  HAL_NVIC_DisableIRQ(USARTx_IRQn);
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct;

	if(hspi->Instance == SPIa)
	{
#ifdef SPI_DMA_COMM
		static DMA_HandleTypeDef hdma_tx;
		static DMA_HandleTypeDef hdma_rx;
#endif
		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		SPIa_SCK_GPIO_CLK_ENABLE();
		SPIa_MISO_GPIO_CLK_ENABLE();
		SPIa_MOSI_GPIO_CLK_ENABLE();
		/* Enable SPI clock */
		SPIa_CLK_ENABLE();
#ifdef SPI_DMA_COMM
		DMAx_CLK_ENABLE();
#endif

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* SPI CS GPIO pin configuration */
		GPIO_InitStruct.Pin			= SPIa_CS_PIN;
		GPIO_InitStruct.Mode		= GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull		= GPIO_PULLUP;
		GPIO_InitStruct.Speed		= GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate	= SPIa_CS_AF;
		HAL_GPIO_Init(SPIa_CS_GPIO_PORT, &GPIO_InitStruct);
		//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_SET);

		/* SPI SCK GPIO pin configuration */
		GPIO_InitStruct.Pin			= SPIa_SCK_PIN;
		GPIO_InitStruct.Mode		= GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull		= GPIO_PULLUP;
		GPIO_InitStruct.Speed		= GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate	= SPIa_SCK_AF;
		HAL_GPIO_Init(SPIa_SCK_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MISO GPIO pin configuration */
		GPIO_InitStruct.Pin			= SPIa_MISO_PIN;					//PE13, TX
		GPIO_InitStruct.Alternate	= SPIa_MISO_AF;
		HAL_GPIO_Init(SPIa_MISO_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MOSI GPIO pin configuration */
		GPIO_InitStruct.Pin = SPIa_MOSI_PIN;						//PE14, RX
		GPIO_InitStruct.Alternate = SPIa_MOSI_AF;
		HAL_GPIO_Init(SPIa_MOSI_GPIO_PORT, &GPIO_InitStruct);

#ifdef SPI_DMA_COMM
		/*##-3- Configure the DMA streams ##########################################*/
		/* Configure the DMA handler for Transmission process */
		hdma_tx.Instance					= SPIa_TX_DMA_STREAM;
		hdma_tx.Init.Channel				= SPIa_TX_DMA_CHANNEL;
		hdma_tx.Init.Direction				= DMA_MEMORY_TO_PERIPH;
		hdma_tx.Init.PeriphInc				= DMA_PINC_DISABLE;
		hdma_tx.Init.MemInc					= DMA_MINC_ENABLE;
		hdma_tx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
		hdma_tx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE;
		hdma_tx.Init.Mode					= DMA_NORMAL;
		hdma_tx.Init.Priority				= DMA_PRIORITY_LOW;
		hdma_tx.Init.FIFOMode				= DMA_FIFOMODE_DISABLE;         
		hdma_tx.Init.FIFOThreshold			= DMA_FIFO_THRESHOLD_FULL;
		hdma_tx.Init.MemBurst				= DMA_MBURST_INC4;
		hdma_tx.Init.PeriphBurst			= DMA_PBURST_INC4;
		HAL_DMA_Init(&hdma_tx);
		/* Associate the initialized DMA handle to the the SPI handle */
		__HAL_LINKDMA(hspi, hdmatx, hdma_tx);

		/* Configure the DMA handler for Transmission process */
		hdma_rx.Instance					= SPIa_RX_DMA_STREAM;
		hdma_rx.Init.Channel				= SPIa_RX_DMA_CHANNEL;
		hdma_rx.Init.Direction				= DMA_PERIPH_TO_MEMORY;
		hdma_rx.Init.PeriphInc				= DMA_PINC_DISABLE;
		hdma_rx.Init.MemInc					= DMA_MINC_ENABLE;
		hdma_rx.Init.PeriphDataAlignment	= DMA_PDATAALIGN_BYTE;
		hdma_rx.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE;
		hdma_rx.Init.Mode					= DMA_NORMAL;
		hdma_rx.Init.Priority				= DMA_PRIORITY_HIGH;
		hdma_rx.Init.FIFOMode				= DMA_FIFOMODE_DISABLE;         
		hdma_rx.Init.FIFOThreshold			= DMA_FIFO_THRESHOLD_FULL;
		hdma_rx.Init.MemBurst				= DMA_MBURST_INC4;
		hdma_rx.Init.PeriphBurst			= DMA_PBURST_INC4;
		HAL_DMA_Init(&hdma_rx);
		/* Associate the initialized DMA handle to the the SPI handle */
		__HAL_LINKDMA(hspi, hdmarx, hdma_rx);
#endif

		/*##-3- Configure the NVIC for SPI #########################################*/
#ifdef SPI_DMA_COMM
		/* NVIC configuration for DMA transfer complete interrupt (SPI3_TX) */
		HAL_NVIC_SetPriority(SPIa_DMA_TX_IRQn, 1, 1);
		HAL_NVIC_EnableIRQ(SPIa_DMA_TX_IRQn);
		/* NVIC configuration for DMA transfer complete interrupt (SPI3_RX) */
		HAL_NVIC_SetPriority(SPIa_DMA_RX_IRQn, 0, 3);   
		HAL_NVIC_EnableIRQ(SPIa_DMA_RX_IRQn);
#else
		/* NVIC for SPI */
		HAL_NVIC_SetPriority(SPIa_IRQn, 1, 1);
		HAL_NVIC_EnableIRQ(SPIa_IRQn);
#endif
	}
	else if(hspi->Instance == SPIx)
	{
		/*##-1- Enable peripherals and GPIO Clocks #################################*/
		/* Enable GPIO TX/RX clock */
		SPIx_CS_GPIO_CLK_ENABLE();
		SPIx_SCK_GPIO_CLK_ENABLE();
		SPIx_MISO_GPIO_CLK_ENABLE();
		SPIx_MOSI_GPIO_CLK_ENABLE();
		/* Enable SPI clock */
		SPIx_CLK_ENABLE();

		/*##-2- Configure peripheral GPIO ##########################################*/
		/* SPI CS GPIO pin configuration */
		GPIO_InitStruct.Pin       = SPIx_CS_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = SPIx_CS_AF;

		HAL_GPIO_Init(SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

		/* SPI SCK GPIO pin configuration */
		GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
		GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull      = GPIO_PULLUP;
		GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = SPIx_SCK_AF;

		HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MISO GPIO pin configuration */
		GPIO_InitStruct.Pin = SPIx_MISO_PIN;
		GPIO_InitStruct.Alternate = SPIx_MISO_AF;

		HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);

		/* SPI MOSI GPIO pin configuration */
		GPIO_InitStruct.Pin = SPIx_MOSI_PIN;
		GPIO_InitStruct.Alternate = SPIx_MOSI_AF;

		HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);

		/*##-3- Configure the NVIC for SPI #########################################*/
		/* NVIC for SPI */
		HAL_NVIC_SetPriority(SPIx_IRQn, 2, 1);
		HAL_NVIC_EnableIRQ(SPIx_IRQn);
	}
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  /*##-1- Reset peripherals ##################################################*/
  SPIx_FORCE_RESET();
  SPIx_RELEASE_RESET();
  
  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* Configure SPI SCK As alternate fruction */
  HAL_GPIO_DeInit(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN);
  /* Configure SPI MISO as alternat funtion */
  HAL_GPIO_DeInit(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN);
  /* Configure SPI MOSI as a alternate function */
  HAL_GPIO_DeInit(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN);
  
  /*##-3- Disable the NVIC for SPI ###########################################*/
  HAL_NVIC_DisableIRQ(SPIx_IRQn);
}

/**
  * @brief I2C MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - DMA configuration for transmission request by peripheral 
  *           - NVIC configuration for DMA interrupt request enable
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  I2Cx_SCL_GPIO_CLK_ENABLE();
  I2Cx_SDA_GPIO_CLK_ENABLE();
  /* Enable I2C1 clock */
  I2Cx_CLK_ENABLE(); 
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* I2C TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = I2Cx_SCL_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = I2Cx_SCL_AF;
  
  HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);
    
  /* I2C RX GPIO pin configuration  */
  GPIO_InitStruct.Pin 		= I2Cx_SDA_PIN;
  GPIO_InitStruct.Alternate = I2Cx_SDA_AF;
    
  HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
    
  /*##-3- Configure the NVIC for I2C #########################################*/   
  /* NVIC for I2C1 */
  HAL_NVIC_SetPriority(I2Cx_ER_IRQn, 3, 5);
  HAL_NVIC_EnableIRQ(I2Cx_ER_IRQn);
  HAL_NVIC_SetPriority(I2Cx_EV_IRQn, 3, 6);
  HAL_NVIC_EnableIRQ(I2Cx_EV_IRQn);
}

/**
  * @brief I2C MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO, DMA and NVIC configuration to their default state
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{
  /*##-1- Reset peripherals ##################################################*/
  I2Cx_FORCE_RESET();
  I2Cx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks ################################*/
  /* Configure I2C Tx as alternate function  */
  HAL_GPIO_DeInit(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN);
  /* Configure I2C Rx as alternate function  */
  HAL_GPIO_DeInit(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN);
  
  /*##-3- Disable the NVIC for I2C ###########################################*/
  HAL_NVIC_DisableIRQ(I2Cx_ER_IRQn);
  HAL_NVIC_DisableIRQ(I2Cx_EV_IRQn);
}

/**
  * @brief TIM MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	/* 1- Enable peripherals and GPIO Clocks */
	TIMx_CLK_ENABLE();

	/* 2- Configure the NVIC for TIMx */
	/* Set the TIMx priority */
	HAL_NVIC_SetPriority(TIMx_IRQn, 1, 0);

	HAL_NVIC_EnableIRQ(TIMx_IRQn);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
