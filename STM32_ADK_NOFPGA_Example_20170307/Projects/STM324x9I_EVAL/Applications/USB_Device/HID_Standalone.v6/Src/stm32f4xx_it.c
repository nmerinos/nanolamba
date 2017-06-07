/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    01-July-2015
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f4xx_it.h"
#include "usbd_apollo_interface.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_EXTI
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CURSOR_STEP     5
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd;
uint8_t HID_Buffer[4];
uint8_t Apollo_Buffer[1024];
extern USBD_HandleTypeDef USBD_Device;
extern SPI_HandleTypeDef SpiSensorDataHandle;
extern UART_HandleTypeDef UartHandle;
extern UART_HandleTypeDef UartHandleBlue;
extern TIM_HandleTypeDef TimHandle;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	static __IO uint32_t counter=0;
	HAL_IncTick();

	// Jesse
	USBMessageHandler();

#if 0
  /* check Joystick state every polling interval (10ms) */
  //if (counter++ == 6) // every 6 ms is minimum sleep time for bulk transfer in this example
  if (counter++ == USBD_HID_GetPollingInterval(&USBD_Device))
  {  
#if 1
    /* Initiate next USB packet transfer once UART completes transfer (transmitting data over Tx line) */
    /* EP OUT */
    USBD_JUSB_ReceivePacket(&USBD_Device);
#else
    //GetPointerData(HID_Buffer);
    GetPointerData(Apollo_Buffer);
    
    /* send data though IN endpoint*/
#if 0
    if((HID_Buffer[1] != 0) || (HID_Buffer[2] != 0))
    {
      USBD_HID_SendReport(&USBD_Device, HID_Buffer, 4);
    }
#else
    if((Apollo_Buffer[0] != 0) || (Apollo_Buffer[512] != 0))
    {
      USBD_HID_SendReport(&USBD_Device, Apollo_Buffer, 1024);
    }
#endif
#endif
    counter =0;
  }
#endif
  //Toggle_Leds();
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(WAKEUP_BUTTON_PIN);
}

void EXTI1_IRQHandler(void)
{
 	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
 	//__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
 	//HAL_GPIO_EXTI_Callback(GPIO_PIN_1);
}

void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
	//HAL_GPIO_EXTI_Callback(GPIO_PIN_2);
}

/**
  * @brief  This function handles External lines 15 to 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
	//HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
}

/**
  * @brief  This function handles USB-On-The-Go FS or HS global interrupt request.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_FS
void OTG_FS_IRQHandler(void)
#else
void OTG_HS_IRQHandler(void)
#endif
{

  HAL_PCD_IRQHandler(&hpcd);
}

/**
  * @brief  This function handles USB OTG FS or HS Wakeup IRQ Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_FS  
void OTG_FS_WKUP_IRQHandler(void)
#else  
void OTG_HS_WKUP_IRQHandler(void)
#endif
{
  if((&hpcd)->Init.low_power_enable)
  {
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));  
    
    /* Configures system clock after wake-up from STOP: enable HSE, PLL and select 
    PLL as system clock source (HSE and PLL are disabled in STOP mode) */
    
    __HAL_RCC_HSE_CONFIG(RCC_HSE_ON);
    
    /* Wait till HSE is ready */  
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET)
    {}
    
    /* Enable the main PLL. */
    __HAL_RCC_PLL_ENABLE();
    
    /* Wait till PLL is ready */  
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET)
    {}
    
    /* Select PLL as SYSCLK */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_SYSCLKSOURCE_PLLCLK);
    
    while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_PLL)
    {}
    
    /* ungate PHY clock */
     __HAL_PCD_UNGATE_PHYCLOCK((&hpcd)); 
  }
#ifdef USE_USB_FS
  /* Clear EXTI pending Bit*/
  __HAL_USB_OTG_FS_WAKEUP_EXTI_CLEAR_FLAG();
#else
    /* Clear EXTI pending Bit*/
  __HAL_USB_OTG_HS_WAKEUP_EXTI_CLEAR_FLAG();
#endif
  
}

#ifdef SPI_DMA_COMM
void SPIa_DMA_RX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiSensorDataHandle.hdmarx);
}

void SPIa_DMA_TX_IRQHandler(void)
{
	HAL_DMA_IRQHandler(SpiSensorDataHandle.hdmatx);
}
#endif

void USARTx_IRQHandler(void)
{
}

void USARTy_IRQHandler(void)
{
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
  void TIMx_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TimHandle);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
