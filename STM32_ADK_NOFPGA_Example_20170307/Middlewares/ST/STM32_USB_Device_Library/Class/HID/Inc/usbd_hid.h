/**
  ******************************************************************************
  * @file    usbd_hid.h
  * @author  MCD Application Team
  * @version V2.4.1
  * @date    19-June-2015
  * @brief   Header file for the usbd_hid_core.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_HID_H
#define __USB_HID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "usbd_ioreq.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup USBD_HID
  * @brief This file is the Header file for usbd_hid.c
  * @{
  */ 


/** @defgroup USBD_HID_Exported_Defines
  * @{
  */ 
#define HID_EPIN_ADDR                 0x81
#define HID_EPOUT_ADDR                0x01
   
#define HID_EPIN_SIZE                 64
#define HID_EPOUT_SIZE                64
   
#define JUSB_DATA_HS_MAX_PACKET_SIZE                 512  /* Endpoint IN & OUT Packet size */
#define JUSB_DATA_FS_MAX_PACKET_SIZE                 64  /* Endpoint IN & OUT Packet size */

#define JUSB_DATA_HS_IN_PACKET_SIZE                  JUSB_DATA_HS_MAX_PACKET_SIZE
#define JUSB_DATA_HS_OUT_PACKET_SIZE                 JUSB_DATA_HS_MAX_PACKET_SIZE    
    
#define JUSB_DATA_FS_IN_PACKET_SIZE                  JUSB_DATA_FS_MAX_PACKET_SIZE
#define JUSB_DATA_FS_OUT_PACKET_SIZE                 JUSB_DATA_FS_MAX_PACKET_SIZE

// jesse
// 2 interfaces
#if 1
#define USB_HID_CONFIG_DESC_SIZ       55
#else
#define USB_HID_CONFIG_DESC_SIZ       32
#endif
#define USB_HID_DESC_SIZ              9
#define HID_MOUSE_REPORT_DESC_SIZE    74

#define HID_DESCRIPTOR_TYPE           0x21
#define HID_REPORT_DESC               0x22

#define HID_HS_BINTERVAL               0x07
#define HID_FS_BINTERVAL               0x0A
#define HID_POLLING_INTERVAL           0x0A

#define HID_REQ_SET_PROTOCOL          0x0B
#define HID_REQ_GET_PROTOCOL          0x03

#define HID_REQ_SET_IDLE              0x0A
#define HID_REQ_GET_IDLE              0x02

#define HID_REQ_SET_REPORT            0x09
#define HID_REQ_GET_REPORT            0x01
   
/*---------------------------------------------------------------------*/
/*  CDC definitions                                                    */
/*---------------------------------------------------------------------*/
#if 1

#define STM_GET_DATA_FROM_DEVICE    0x10
#define STM_SET_DATA_FROM_DEVICE    0x11
#define STM_COMM_GET_SENSOR_ID      0x01 // 8 bytes
// TEST for Bulk Transfer
#define STM_COMM_START_BULK_TRANSFER      0x46    // 1 byte        //2015.08.07
#define STM_COMM_STOP_BULK_TRANSFER       0x47    // 1 byte        //2015.08.07
   
#else
   
#define EFM32_GET_DATA_FROM_DEVICE    0x10
#define EFM32_SET_DATA_FROM_DEVICE    0x11
#define EFM32_COMM_GET_SENSOR_ID      0x01 // 8 bytes
// TEST for Bulk Transfer
#define EFM32_COMM_START_BULK_TRANSFER      0x46    // 1 byte        //2015.08.07
#define EFM32_COMM_STOP_BULK_TRANSFER       0x47    // 1 byte        //2015.08.07

#endif
   /**
  * @}
  */ 


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */
typedef enum
{
  HID_IDLE = 0,
  HID_BUSY,
}
HID_StateTypeDef; 


typedef struct _USBD_JUSB_Itf
{
  int8_t (* Init)          (void);
  int8_t (* DeInit)        (void);
  int8_t (* Control)       (uint8_t, uint8_t * , uint16_t, uint16_t);   
  int8_t (* Receive)       (uint8_t *, uint32_t *);  

}USBD_JUSB_ItfTypeDef;


typedef struct
{
  //uint8_t data[USB_MAX_EP0_SIZE];
  uint8_t data[2048];
  //uint32_t data[JUSB_DATA_HS_MAX_PACKET_SIZE/4];      /* Force 32bits alignment */
  uint8_t  CmdOpCode;
  uint8_t  CmdLength;
  
  uint8_t  *RxBuffer;  
  uint8_t  *TxBuffer;   
  uint32_t RxLength;
  uint32_t TxLength;    
  
  __IO uint32_t TxState;     
  __IO uint32_t RxState;  
}
USBD_HID_HandleTypeDef; 
/**
  * @}
  */ 


/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */ 

extern USBD_ClassTypeDef  USBD_HID;
#define USBD_HID_CLASS    &USBD_HID
/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */ 
uint8_t USBD_HID_SendReport (USBD_HandleTypeDef *pdev, 
                                 uint8_t *report,
                                 uint16_t len);

uint32_t USBD_HID_GetPollingInterval (USBD_HandleTypeDef *pdev);


uint8_t  USBD_JUSB_RegisterInterface  (USBD_HandleTypeDef   *pdev, 
                                      USBD_JUSB_ItfTypeDef *fops);

uint8_t  USBD_JUSB_SetTxBuffer        (USBD_HandleTypeDef   *pdev,
                                      uint8_t  *pbuff,
                                      uint16_t length);

uint8_t  USBD_JUSB_SetRxBuffer        (USBD_HandleTypeDef   *pdev,
                                      uint8_t  *pbuff);
  
uint8_t  USBD_JUSB_TransmitPacket     (USBD_HandleTypeDef *pdev);

uint8_t  USBD_JUSB_ReceivePacket      (USBD_HandleTypeDef *pdev);

uint8_t  USBD_IsDataReceived(void);

void  USBD_SetDataReceived(uint8_t received);
/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif  /* __USB_HID_H */
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
