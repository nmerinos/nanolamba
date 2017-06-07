/**
  ******************************************************************************
  * @file    usbd_hid.c
  * @author  MCD Application Team
  * @version V2.4.1
  * @date    19-June-2015
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                HID Class  Description
  *          =================================================================== 
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Joystick
  *             - Collection : Application 
  *      
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *           
  *      
  *  @endverbatim
  *
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_hid.h"
#include "usbd_desc.h"
#include "usbd_ctlreq.h"

// Test
#include "stm324x9i_eval.h"

#define USE_BULK_TRANSFER
//#undef USE_BULK_TRANSFER

#define LOOP_FOR_FRAME  10
//#define LOOP_FOR_FRAME  2000
//#define LOOP_FOR_FRAME  7582

uint8_t EpOutDataReceived = 0;
uint16_t countOfFrameData = 0;
extern USBD_HandleTypeDef  USBD_Device;

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_HID 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup USBD_HID_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_Defines
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 




/** @defgroup USBD_HID_Private_FunctionPrototypes
  * @{
  */


static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx);

static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx);

static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req);

static uint8_t  USBD_LibUSBComm_EP0_TxReady (USBD_HandleTypeDef *pdev);

static uint8_t  USBD_LibUSBComm_EP0_RxReady (USBD_HandleTypeDef *pdev);

static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  USBD_HID_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  *USBD_HID_GetHSCfgDesc (uint16_t *length);

static uint8_t  *USBD_HID_GetFSCfgDesc (uint16_t *length);

//static uint8_t  *USBD_HID_GetOtherSpeedCfgDesc (uint16_t *length);

static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length);


#if 0
static uint8_t  USBD_LibUSBComm_SOF (USBD_HandleTypeDef *pdev);

static uint8_t  USBD_LibUSBComm_IsoINIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t  USBD_LibUSBComm_IsoOutIncomplete (USBD_HandleTypeDef *pdev, uint8_t epnum);

static uint8_t * USBD_LibUSBComm_GetUsrStrDescriptor(struct _USBD_HandleTypeDef *pdev, uint8_t index,  uint16_t *length)
#endif
/**
  * @}
  */ 

/** @defgroup USBD_HID_Private_Variables
  * @{
  */ 

USBD_ClassTypeDef  USBD_HID = 
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  USBD_LibUSBComm_EP0_TxReady, /*EP0_TxReady*/  
  USBD_LibUSBComm_EP0_RxReady, /*EP0_RxReady*/
  USBD_HID_DataIn, /*DataIn*/
  USBD_HID_DataOut, /*DataOut*/
  NULL, //USBD_LibUSBComm_SOF, /*SOF */
  NULL, //USBD_LibUSBComm_IsoINIncomplete,
  NULL, //USBD_LibUSBComm_IsoOutIncomplete,      
  USBD_HID_GetHSCfgDesc,
  USBD_HID_GetFSCfgDesc, 
  USBD_HID_GetHSCfgDesc,
  USBD_HID_GetDeviceQualifierDesc,
};

/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgHSDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,                                 /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,          /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,              /* wTotalLength: Bytes returned */
  0x00,
  0x02,                                 /*bNumInterfaces: 2 interface*/
  //0x01,                                 /*bNumInterfaces: 1 interface*/
  0x01,                                 /*bConfigurationValue: Configuration value*/
  0x00,                                 /*iConfiguration: Index of string descriptor describing
                                        the configuration*/
  0x80,                                 /* bmAttributes: self powered */
  0x32,                                 /*MaxPower 100 mA: this current is used for detecting Vbus*/
  /* 09 */
  
  /*---------------------------------------------------------------------------*/
  /*Interface Descriptor */
  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  //0x0A,   /* bInterfaceClass: CDC */
  0xFF,
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */
  /* 18 */
  
  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  HID_EPOUT_ADDR,                        /* bEndpointAddress */
#ifndef USE_BULK_TRANSFER
  0x03,          /*bmAttributes: Interrupt endpoint - This field describes the endpoint attributes */
  //0x01,                              /* bmAttributes: USBD_EP_TYPE_ISOC */
#else
  0x02,                              /* bmAttributes: Bulk */
#endif
  LOBYTE(JUSB_DATA_HS_OUT_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(JUSB_DATA_HS_OUT_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */
  /* 25 */
  
  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  HID_EPIN_ADDR,                         /* bEndpointAddress */
#ifndef USE_BULK_TRANSFER
  0x03,          /*bmAttributes: Interrupt endpoint - This field describes the endpoint attributes */
  //0x01,                              /* bmAttributes: USBD_EP_TYPE_ISOC */
#else
  0x02,                              /* bmAttributes: Bulk */
#endif
  LOBYTE(JUSB_DATA_HS_IN_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(JUSB_DATA_HS_IN_PACKET_SIZE),
  0x00,                               /* bInterval: ignore for Bulk transfer */
  /* 32 */
    
#if 1
  //////////////////////////////////////
  /*---------------------------------------------------------------------------*/
  /*Interface Descriptor */
  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x01,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  //0x0A,   /* bInterfaceClass: CDC */
  0xFF,   /* vender specific */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */
  /* 41 */

  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  0x02,                        /* bEndpointAddress */
#ifndef USE_BULK_TRANSFER
  0x03,          /*bmAttributes: Interrupt endpoint - This field describes the endpoint attributes */
  //0x01,                              /* bmAttributes: USBD_EP_TYPE_ISOC */
#else
  0x02,                              /* bmAttributes: Bulk - This field describes the endpoint attributes */
#endif
  LOBYTE(JUSB_DATA_FS_OUT_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(JUSB_DATA_FS_OUT_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */
  /* 48 */

  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  0x82,                         /* bEndpointAddress */
#ifndef USE_BULK_TRANSFER
  0x03,          /*bmAttributes: Interrupt endpoint - This field describes the endpoint attributes */
  //0x01,                              /* bmAttributes: USBD_EP_TYPE_ISOC */
#else
  0x02,                              /* bmAttributes: Bulk */
#endif
  LOBYTE(JUSB_DATA_FS_IN_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(JUSB_DATA_FS_IN_PACKET_SIZE),
  0x00
  /* 55 */
#endif
} ;


/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgFSDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,                                 /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,          /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,              /* wTotalLength: Bytes returned */
  0x00,
  0x02,                                 /*bNumInterfaces: 2 interface*/
  //0x01,                                 /*bNumInterfaces: 1 interface*/
  0x01,                                 /*bConfigurationValue: Configuration value*/
  0x00,                                 /*iConfiguration: Index of string descriptor describing
                                        the configuration*/
  0x80,                                 /* bmAttributes: self powered */
  0x32,                                 /*MaxPower 100 mA: this current is used for detecting Vbus*/
  /* 09 */
  
  /*---------------------------------------------------------------------------*/
  /*Interface Descriptor */
  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  //0x0A,   /* bInterfaceClass: CDC */
  0xFF,   /* vender specific */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */
  /* 18 */
   
  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  HID_EPOUT_ADDR,                        /* bEndpointAddress */
#ifndef USE_BULK_TRANSFER
  0x03,          /*bmAttributes: Interrupt endpoint - This field describes the endpoint attributes */
  //0x01,                              /* bmAttributes: USBD_EP_TYPE_ISOC */
#else
  0x02,                              /* bmAttributes: Bulk - This field describes the endpoint attributes */
#endif
  LOBYTE(JUSB_DATA_FS_OUT_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(JUSB_DATA_FS_OUT_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */
  /* 25 */
  
  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  HID_EPIN_ADDR,                         /* bEndpointAddress */
#ifndef USE_BULK_TRANSFER
  0x03,          /*bmAttributes: Interrupt endpoint - This field describes the endpoint attributes */
  //0x01,                              /* bmAttributes: USBD_EP_TYPE_ISOC */
#else
  0x02,                              /* bmAttributes: Bulk */
#endif
  LOBYTE(JUSB_DATA_FS_IN_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(JUSB_DATA_FS_IN_PACKET_SIZE),
  0x00,                               /* bInterval: ignore for Bulk transfer */
  /* 32 */
  
#if 1
  //////////////////////////////////////
  /*---------------------------------------------------------------------------*/
  /*Interface Descriptor */
  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x01,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  //0x0A,   /* bInterfaceClass: CDC */
  0xFF,   /* vender specific */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */
  /* 41 */

  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  0x02,                        /* bEndpointAddress */
#ifndef USE_BULK_TRANSFER
  0x03,          /*bmAttributes: Interrupt endpoint - This field describes the endpoint attributes */
  //0x01,                              /* bmAttributes: USBD_EP_TYPE_ISOC */
#else
  0x02,                              /* bmAttributes: Bulk - This field describes the endpoint attributes */
#endif
  LOBYTE(JUSB_DATA_FS_OUT_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(JUSB_DATA_FS_OUT_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */
  /* 48 */

  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  0x82,                         /* bEndpointAddress */
#ifndef USE_BULK_TRANSFER
  0x03,          /*bmAttributes: Interrupt endpoint - This field describes the endpoint attributes */
  //0x01,                              /* bmAttributes: USBD_EP_TYPE_ISOC */
#else
  0x02,                              /* bmAttributes: Bulk */
#endif
  LOBYTE(JUSB_DATA_FS_IN_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(JUSB_DATA_FS_IN_PACKET_SIZE),
  0x00
  /* 55 */
#endif
} ;


/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_Desc[USB_HID_DESC_SIZ]  __ALIGN_END  =
{
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE]  __ALIGN_END =
{
  0x05,   0x01,
  0x09,   0x02,
  0xA1,   0x01,
  0x09,   0x01,
  
  0xA1,   0x00,
  0x05,   0x09,
  0x19,   0x01,
  0x29,   0x03,
  
  0x15,   0x00,
  0x25,   0x01,
  0x95,   0x03,
  0x75,   0x01,
  
  0x81,   0x02,
  0x95,   0x01,
  0x75,   0x05,
  0x81,   0x01,
  
  0x05,   0x01,
  0x09,   0x30,
  0x09,   0x31,
  0x09,   0x38,
  
  0x15,   0x81,
  0x25,   0x7F,
  0x75,   0x08,
  0x95,   0x03,
  
  0x81,   0x06,
  0xC0,   0x09,
  0x3c,   0x05,
  0xff,   0x09,
  
  0x01,   0x15,
  0x00,   0x25,
  0x01,   0x75,
  0x01,   0x95,
  
  0x02,   0xb1,
  0x22,   0x75,
  0x06,   0x95,
  0x01,   0xb1,
  
  0x01,   0xc0
}; 

/**
  * @}
  */ 

/** @defgroup USBD_HID_Private_Functions
  * @{
  */ 

/**
  * @brief  USBD_HID_Init
  *         Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx)
{
  uint8_t ret = 0;
  USBD_HID_HandleTypeDef   *hhid;
  
  if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
  {  
    /* Open EP IN */
    USBD_LL_OpenEP(pdev,
                   HID_EPIN_ADDR,
#ifndef USE_BULK_TRANSFER
                   USBD_EP_TYPE_INTR,                 
                   //USBD_EP_TYPE_ISOC,
#else
                   USBD_EP_TYPE_BULK,
#endif
                   JUSB_DATA_HS_IN_PACKET_SIZE);
    
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev,
                   HID_EPOUT_ADDR,
#ifndef USE_BULK_TRANSFER
                   USBD_EP_TYPE_INTR,
                   //USBD_EP_TYPE_ISOC,
#else
                   USBD_EP_TYPE_BULK,
#endif
                   JUSB_DATA_HS_OUT_PACKET_SIZE);
  }
  else
  {
    /* Open EP IN */
    USBD_LL_OpenEP(pdev,
                   HID_EPIN_ADDR,
#ifndef USE_BULK_TRANSFER
                   USBD_EP_TYPE_INTR,
                   //USBD_EP_TYPE_ISOC,
#else
                   USBD_EP_TYPE_BULK,
#endif
                   JUSB_DATA_FS_IN_PACKET_SIZE);
    
    /* Open EP OUT */
    USBD_LL_OpenEP(pdev,
                   HID_EPOUT_ADDR,
#ifndef USE_BULK_TRANSFER
                   USBD_EP_TYPE_INTR,
                   //USBD_EP_TYPE_ISOC,
#else
                   USBD_EP_TYPE_BULK,
#endif
                   JUSB_DATA_FS_OUT_PACKET_SIZE);
  }
  
  pdev->pClassData = USBD_malloc(sizeof (USBD_HID_HandleTypeDef));
  
  if(pdev->pClassData == NULL)
  {
    ret = 1; 
  }
  else
  {
    hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;
    
    /* Init  physical Interface components */
    ((USBD_JUSB_ItfTypeDef *)pdev->pUserData)->Init();
    
    /* Init Xfer states */
    hhid->TxState =0;
    hhid->RxState =0;
    
    if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
    {      
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             HID_EPOUT_ADDR,
                             hhid->RxBuffer,
                             JUSB_DATA_HS_OUT_PACKET_SIZE);
    }
    else
    {
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             HID_EPOUT_ADDR,
                             hhid->RxBuffer,
                             JUSB_DATA_FS_OUT_PACKET_SIZE);
    }
  }
  
  return ret;
}

/**
  * @brief  USBD_HID_Init
  *         DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx)
{
  /* Close HID EPs */
  USBD_LL_CloseEP(pdev,
                  HID_EPIN_ADDR);
  
  /* Close HID EPs */
  USBD_LL_CloseEP(pdev,
                  HID_EPOUT_ADDR);
  
  /* FRee allocated memory */
  if(pdev->pClassData != NULL)
  {
    ((USBD_JUSB_ItfTypeDef *)pdev->pUserData)->DeInit();
    USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  } 
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req)
{
  //uint16_t len = 0;
  //uint8_t  *pbuf = NULL;
  uint8_t ret = USBD_OK;
  USBD_HID_HandleTypeDef *hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;

  static uint8_t ifalt = 0;
  
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :
    if (req->wLength)
    {
      // EP0 IN
      if (req->bmRequest & 0x80)
      {
        // for managing Control request
        ((USBD_JUSB_ItfTypeDef *)pdev->pUserData)->Control(req->bRequest,
                                                           (uint8_t *)hhid->data,
                                                           req->wLength,
														   req->wValue);
                                                           //req->wIndex);
          USBD_CtlSendData (pdev, 
                            (uint8_t *)hhid->data,
                            req->wLength);
      }
      // EP0 OUT
      else
      {
        hhid->CmdOpCode = req->bRequest;
        hhid->CmdLength = req->wLength;
        
        USBD_CtlPrepareRx (pdev, 
                           (uint8_t *)hhid->data,
                           req->wLength);
      }     
    }
    else
    {
      // for managing Control request
      ((USBD_JUSB_ItfTypeDef *)pdev->pUserData)->Control(req->bRequest,
                                                         (uint8_t*)req,
                                                         0,
														 req->wValue);
                                                         //req->wIndex);
        //for testing bulk transfer to Host
        // this is moved to usbd_apollo_interface.c
        //USBD_SetDataReceived(1);
    }
    break;
    
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        &ifalt,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      break;
    }
    
  default: 
    break;

  }
  
  return ret;
}

// EP0 IN
/**
  * @brief  USBD_AUDIO_EP0_TxReady
  *         handle EP0 TRx Ready event
  * @param  pdev: device instance
  * @retval status
  */
static uint8_t  USBD_LibUSBComm_EP0_TxReady (USBD_HandleTypeDef *pdev)
{
  /* Only OUT control data are processed */
  return USBD_OK;
}

/**
  * @brief  USBD_LibUSBComm_EP0_RxReady
  *         handle EP0 Rx Ready event
  * @param  pdev: device instance
  * @retval status
  */
// EP0 OUT
static uint8_t  USBD_LibUSBComm_EP0_RxReady (USBD_HandleTypeDef *pdev)
{
  USBD_HID_HandleTypeDef   *hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum)
{ 
  USBD_HID_HandleTypeDef   *hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  if(pdev->pClassData != NULL)
  {
    hhid->TxState = 0;
    
    return USBD_OK;
  }
  else
  {
    return USBD_FAIL;
  }
}

/**
  * @brief  USBD_HID_DataOut
  *         handle data OUT Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataOut (USBD_HandleTypeDef *pdev, uint8_t epnum)
{
  USBD_HID_HandleTypeDef   *hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  /* Get the received data length */
  hhid->RxLength = USBD_LL_GetRxDataSize (pdev, epnum);
  
  /* USB data will be immediately processed, this allow next USB traffic being 
  NAKed till the end of the application Xfer */
  if(pdev->pClassData != NULL)
  {
    // do something with receiced data
    ((USBD_JUSB_ItfTypeDef *)pdev->pUserData)->Receive(hhid->RxBuffer, &hhid->RxLength);
    
    USBD_SetDataReceived(1);

    return USBD_OK;
  }
  else
  {
    return USBD_FAIL;
  }
}

/**
  * @brief  USBD_HID_GetCfgDesc 
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetHSCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgHSDesc);
  return USBD_HID_CfgHSDesc;
}

static uint8_t  *USBD_HID_GetFSCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgFSDesc);
  return USBD_HID_CfgFSDesc;
}


/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_DeviceQualifierDesc);
  return USBD_HID_DeviceQualifierDesc;
}


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


/**
  * @brief  USBD_HID_SendReport 
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport     (USBD_HandleTypeDef  *pdev, 
                                 uint8_t *report,
                                 uint16_t len)
{
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef*)pdev->pClassData;
  
  if (pdev->dev_state == USBD_STATE_CONFIGURED )
  {
    USBD_LL_Transmit (pdev, 
                      HID_EPIN_ADDR,                                      
                      report,
                      len);
  }
  return USBD_OK;
}


/**
  * @brief  USBD_HID_GetPollingInterval 
  *         return polling interval from endpoint descriptor
  * @param  pdev: device instance
  * @retval polling interval
  */
uint32_t USBD_HID_GetPollingInterval (USBD_HandleTypeDef *pdev)
{
  uint32_t polling_interval = 0;

  /* HIGH-speed endpoints */
  if(pdev->dev_speed == USBD_SPEED_HIGH)
  {
   /* Sets the data transfer polling interval for high speed transfers. 
    Values between 1..16 are allowed. Values correspond to interval 
    of 2 ^ (bInterval-1). This option (8 ms, corresponds to HID_HS_BINTERVAL */
    polling_interval = (((1 <<(HID_HS_BINTERVAL - 1)))/8);
  }
  else   /* LOW and FULL-speed endpoints */
  {
    /* Sets the data transfer polling interval for low and full 
    speed transfers */
    polling_interval =  HID_FS_BINTERVAL;
  }
  
  return ((uint32_t)(polling_interval));
}


/**
* @brief  USBD_CDC_RegisterInterface
  * @param  pdev: device instance
  * @param  fops: CD  Interface callback
  * @retval status
  */
uint8_t  USBD_JUSB_RegisterInterface  (USBD_HandleTypeDef   *pdev, 
                                      USBD_JUSB_ItfTypeDef *fops)
{
  uint8_t  ret = USBD_FAIL;
  
  if(fops != NULL)
  {
    pdev->pUserData= fops;
    ret = USBD_OK;    
  }
  
  return ret;
}


/**
  * @brief  USBD_CDC_SetTxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Tx Buffer
  * @retval status
  */
uint8_t  USBD_JUSB_SetTxBuffer  (USBD_HandleTypeDef   *pdev,
                                uint8_t  *pbuff,
                                uint16_t length)
{
  USBD_HID_HandleTypeDef   *hcdc = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  hcdc->TxBuffer = pbuff;
  hcdc->TxLength = length;  
  
  return USBD_OK;  
}


/**
  * @brief  USBD_CDC_SetRxBuffer
  * @param  pdev: device instance
  * @param  pbuff: Rx Buffer
  * @retval status
  */
uint8_t  USBD_JUSB_SetRxBuffer  (USBD_HandleTypeDef   *pdev,
                                   uint8_t  *pbuff)
{
  USBD_HID_HandleTypeDef   *hcdc = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  hcdc->RxBuffer = pbuff;
  
  return USBD_OK;
}

/**
  * @brief  USBD_CDC_DataOut
  *         Data received on non-control Out endpoint
  * @param  pdev: device instance
  * @param  epnum: endpoint number
  * @retval status
  */
uint8_t  USBD_JUSB_TransmitPacket(USBD_HandleTypeDef *pdev)
{      
  USBD_HID_HandleTypeDef   *hcdc = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  if(pdev->pClassData != NULL)
  {
    if(hcdc->TxState == 0)
    {
      /* Tx Transfer in progress */
      hcdc->TxState = 1;
      
#if 1
        /* Transmit next packet */
        USBD_LL_Transmit(pdev,
                         HID_EPIN_ADDR,
                         hcdc->TxBuffer,
                         hcdc->TxLength);    
#else
      // for testing simulation mode
      /* set count to data */
      if(countOfFrameData < 10)
        hcdc->TxBuffer[2047] = countOfFrameData;
      else if(countOfFrameData >= 10 && countOfFrameData < 100)
      {
        hcdc->TxBuffer[2046] = countOfFrameData / 10;
        hcdc->TxBuffer[2047] = countOfFrameData % 10;
      }
      else if(countOfFrameData >= 100 && countOfFrameData < 1000)
      {
        hcdc->TxBuffer[2045] = countOfFrameData / 100;
        hcdc->TxBuffer[2046] = (countOfFrameData / 10) % 10;
        hcdc->TxBuffer[2047] = countOfFrameData % 10;
      }
      else if(countOfFrameData >= 1000 && countOfFrameData < 9999)
      {
        hcdc->TxBuffer[2044] = countOfFrameData / 1000;
        hcdc->TxBuffer[2045] = (countOfFrameData / 100) % 10;
        hcdc->TxBuffer[2046] = (countOfFrameData % 100) / 10;
        hcdc->TxBuffer[2047] = countOfFrameData % 10;
      }

      if(countOfFrameData < LOOP_FOR_FRAME)
      {
        /* Transmit next packet */
        USBD_LL_Transmit(pdev,
                         HID_EPIN_ADDR,
                         hcdc->TxBuffer,
                         hcdc->TxLength);
        countOfFrameData++;
      }
      
      
      if(countOfFrameData == LOOP_FOR_FRAME)
      {
        countOfFrameData = 0;
      }      
#endif

      return USBD_OK;
    }
    else
    {
      return USBD_BUSY;
    }
  }
  else
  {
    return USBD_FAIL;
  }
}


/**
  * @brief  USBD_CDC_ReceivePacket
  *         prepare OUT Endpoint for reception
  * @param  pdev: device instance
  * @retval status
  */
uint8_t  USBD_JUSB_ReceivePacket(USBD_HandleTypeDef *pdev)
{      
  USBD_HID_HandleTypeDef   *hcdc = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  /* Suspend or Resume USB Out process */
  if(pdev->pClassData != NULL)
  {
    if(pdev->dev_speed == USBD_SPEED_HIGH  ) 
    {      
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             HID_EPOUT_ADDR,
                             hcdc->RxBuffer,
                             JUSB_DATA_HS_OUT_PACKET_SIZE);
    }
    else
    {
      /* Prepare Out endpoint to receive next packet */
      USBD_LL_PrepareReceive(pdev,
                             HID_EPOUT_ADDR,
                             hcdc->RxBuffer,
                             JUSB_DATA_FS_OUT_PACKET_SIZE);
    }
    return USBD_OK;
  }
  else
  {
    return USBD_FAIL;
  }
}
/**
  * @}
  */ 


uint8_t    USBD_IsDataReceived(void)
{
  return EpOutDataReceived;
}

void    USBD_SetDataReceived(uint8_t received)
{
  EpOutDataReceived = received;
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
