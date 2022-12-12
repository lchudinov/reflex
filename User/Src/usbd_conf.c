/**
  ******************************************************************************
  * @file    usbd_conf.c
  * @author  MCD Application Team 
  * @brief   This file implements the USB Device library callbacks and MSP
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019  STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usb_audio.h"
#include "board.h"
#include "usb_audio_descriptors.h"
#include "usbd_core.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
PCD_HandleTypeDef hpcd;

/* Private function prototypes -----------------------------------------------*/
static USBD_StatusTypeDef USBD_LL_Setup_Fifo(void);
/* Private functions ---------------------------------------------------------*/
  
/*******************************************************************************
                       PCD BSP Routines
*******************************************************************************/

/**
  * @brief  Initializes the PCD MSP.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_MspInit(PCD_HandleTypeDef *hpcd)
{
  USB_FS_GPIO->MODER |= (2 << (2 * USB_FS_DM_PIN)) | (2 << (2 * USB_FS_DP_PIN));
  USB_FS_GPIO->AFR[1] |= (USB_FS_PINS_AF << (4 * (USB_FS_DM_PIN - 8))) | (USB_FS_PINS_AF << (4 * (USB_FS_DP_PIN - 8)));
  USB_FS_GPIO->OSPEEDR |= (3 << (2 * USB_FS_DM_PIN)) | (3 << (2 * USB_FS_DP_PIN));
  
  RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
  // ??? RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; ???

  HAL_NVIC_SetPriority(OTG_FS_IRQn, USB_IRQ_PREPRIO, 0);    
  NVIC_EnableIRQ(OTG_FS_IRQn);
}

/**
  * @brief  De-Initializes the PCD MSP.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_MspDeInit(PCD_HandleTypeDef *hpcd)
{
  if(hpcd->Instance == USB_OTG_FS)
  {  
    RCC->AHB2ENR &= ~RCC_AHB2ENR_OTGFSEN;
  }
}

/*******************************************************************************
                       LL Driver Callbacks (PCD -> USB Device Library)
*******************************************************************************/

/**
  * @brief  SetupStage callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_SetupStage(hpcd->pData, (uint8_t *)hpcd->Setup);
}

/**
  * @brief  DataOut Stage callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  USBD_LL_DataOutStage(hpcd->pData, epnum, hpcd->OUT_ep[epnum].xfer_buff);
}

/**
  * @brief  DataIn Stage callback.
  * @param  hpcd: PCD handle
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  USBD_LL_DataInStage(hpcd->pData, epnum, hpcd->IN_ep[epnum].xfer_buff);
}

/**
  * @brief  SOF callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_SOF(hpcd->pData);
}

/**
  * @brief  Reset callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{   
  USBD_SpeedTypeDef speed = USBD_SPEED_FULL;
  
/*  
  // Set USB Current Speed
  switch(hpcd->Init.speed)
  {
  case PCD_SPEED_HIGH:
    speed = USBD_SPEED_HIGH;
    break;
    
  case PCD_SPEED_FULL:
    speed = USBD_SPEED_FULL;
    break;   
    
  default:
    speed = USBD_SPEED_FULL;
    break;
  }
*/
  
  /* Reset Device */
  USBD_LL_Reset(hpcd->pData);
  
  USBD_LL_SetSpeed(hpcd->pData, speed);
}

/**
  * @brief  Suspend callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_Suspend(hpcd->pData);
}

/**
  * @brief  Resume callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_Resume(hpcd->pData);
}

/**
  * @brief  ISOOUTIncomplete callback.
  * @param  hpcd: PCD handle 
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  USBD_LL_IsoOUTIncomplete(hpcd->pData, epnum);
}

/**
  * @brief  ISOINIncomplete callback.
  * @param  hpcd: PCD handle 
  * @param  epnum: Endpoint Number
  * @retval None
  */
void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
  USBD_LL_IsoINIncomplete(hpcd->pData, epnum);
}

/**
  * @brief  ConnectCallback callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_DevConnected(hpcd->pData);
}

/**
  * @brief  Disconnect callback.
  * @param  hpcd: PCD handle
  * @retval None
  */
void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
  USBD_LL_DevDisconnected(hpcd->pData);
}

/*******************************************************************************
                       LL Driver Interface (USB Device Library --> PCD)
*******************************************************************************/

/**
  * @brief  Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Init(USBD_HandleTypeDef *pdev)
{
  /* Set LL Driver parameters */
  hpcd.Instance                 = USB_OTG_FS;
  hpcd.Init.dev_endpoints       = 5;
  hpcd.Init.use_dedicated_ep1   = 0;
  hpcd.Init.ep0_mps             = 0x40;
  hpcd.Init.dma_enable          = 0;
  hpcd.Init.low_power_enable    = 0;
  hpcd.Init.phy_itface          = PCD_PHY_EMBEDDED;
  hpcd.Init.Sof_enable          = 1;
  hpcd.Init.speed               = PCD_SPEED_FULL;
  hpcd.Init.vbus_sensing_enable = 0;
  hpcd.Init.lpm_enable          = 0;
  
  /* Link The driver to the stack */
  hpcd.pData    = pdev;
  pdev->pData   = &hpcd;
  
  /* Initialize LL Driver */
  HAL_PCD_Init(&hpcd);
  
  //USBD_LL_Setup_Fifo();
  //HAL_PCDEx_SetRxFiFo(&hpcd, 0x80);
  //HAL_PCDEx_SetTxFiFo(&hpcd, 0, 0x40);
  //HAL_PCDEx_SetTxFiFo(&hpcd, 1, 0x80);

  return USBD_OK;
}


/**
  * @brief  De-Initializes the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_DeInit(USBD_HandleTypeDef *pdev)
{
  HAL_PCD_DeInit(pdev->pData);
  return USBD_OK;
}

/**
  * @brief  Starts the Low Level portion of the Device driver. 
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Start(USBD_HandleTypeDef *pdev)
{
  HAL_PCD_Start(pdev->pData);
  return USBD_OK;
}

/**
  * @brief  Stops the Low Level portion of the Device driver.
  * @param  pdev: Device handle
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Stop(USBD_HandleTypeDef *pdev)
{
  HAL_PCD_Stop(pdev->pData);
  return USBD_OK;
}

/**
  * @brief  Opens an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  ep_type: Endpoint Type
  * @param  ep_mps: Endpoint Max Packet Size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_OpenEP(USBD_HandleTypeDef *pdev,
                                  uint8_t ep_addr,
                                  uint8_t ep_type,
                                  uint16_t ep_mps)
{
  HAL_PCD_EP_Open(pdev->pData,
                  ep_addr,
                  ep_mps,
                  ep_type);
  
  return USBD_OK;
}

/**
  * @brief  Closes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_CloseEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  HAL_PCD_EP_Close(pdev->pData, ep_addr);
  USB_CLEAN_EP_AFTER_CLOSE(ep_addr);
  return USBD_OK;
}

/**
  * @brief  Flushes an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_FlushEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  HAL_PCD_EP_Flush(pdev->pData, ep_addr);
  return USBD_OK;
}

/**
  * @brief  Sets a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_StallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  HAL_PCD_EP_SetStall(pdev->pData, ep_addr);
  return USBD_OK;
}

/**
  * @brief  Clears a Stall condition on an endpoint of the Low Level Driver.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_ClearStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  HAL_PCD_EP_ClrStall(pdev->pData, ep_addr);
  return USBD_OK; 
}

/**
  * @brief  Returns Stall condition.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Stall (1: Yes, 0: No)
  */
uint8_t USBD_LL_IsStallEP(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  PCD_HandleTypeDef *hpcd = pdev->pData;
  
  if((ep_addr & 0x80) == 0x80)
  {
    return hpcd->IN_ep[ep_addr & 0x7F].is_stall;
  }
  else
  {
    return hpcd->OUT_ep[ep_addr & 0x7F].is_stall;
  }
}

/**
  * @brief  Assigns a USB address to the device.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_SetUSBAddress(USBD_HandleTypeDef *pdev, uint8_t dev_addr)
{
  HAL_PCD_SetAddress(pdev->pData, dev_addr);
  return USBD_OK; 
}

/**
  * @brief  Transmits data over an endpoint.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be sent
  * @param  size: Data size    
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_Transmit(USBD_HandleTypeDef *pdev, 
                                    uint8_t ep_addr,
                                    uint8_t *pbuf,
                                    uint16_t size)
{
  HAL_PCD_EP_Transmit(pdev->pData, ep_addr, pbuf, size);
  return USBD_OK;
}

/**
  * @brief  Prepares an endpoint for reception.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @param  pbuf: Pointer to data to be received
  * @param  size: Data size
  * @retval USBD Status
  */
USBD_StatusTypeDef USBD_LL_PrepareReceive(USBD_HandleTypeDef *pdev, 
                                          uint8_t ep_addr,
                                          uint8_t *pbuf,
                                          uint16_t size)
{
  HAL_PCD_EP_Receive(pdev->pData, ep_addr, pbuf, size);
  return USBD_OK;
}

/**
  * @brief  Returns the last transferred packet size.
  * @param  pdev: Device handle
  * @param  ep_addr: Endpoint Number
  * @retval Received Data Size
  */
uint32_t USBD_LL_GetRxDataSize(USBD_HandleTypeDef *pdev, uint8_t ep_addr)
{
  return HAL_PCD_EP_GetRxCount(pdev->pData, ep_addr);
}

/**
  * @brief  Delays routine for the USB Device Library.
  * @param  Delay: Delay in ms
  * @retval None
  */
void USBD_LL_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}
/**
  * @brief  Setup dynamically the fifo.
  * @retval Status OK
  */
static USBD_StatusTypeDef USBD_LL_Setup_Fifo(void)
{
  
  uint16_t tx_fifo_size[5]={0};/* TX_FIFO allocation*/
  uint8_t max_tx_ep_num = 0;/* The Max TX_EP_NUMBER*/
  uint16_t tx_fifo_used_size = 0; /* total usage of TX_FIFO*/
  uint16_t rx_fifo_size =0; /* total usage of RX_FIFO*/
  
  /* rx_fifo_size = (5 * number of control endpoints + 8) + ((largest USB packet used / 4) + 1 for status information) +
                    (2 * number of OUT endpoints) + 1 for Global NAK*/
#if USE_USB_AUDIO_PLAYBACK
  rx_fifo_size = 194;//146;//(USBD_AUDIO_CONFIG_PLAY_MAX_PACKET_SIZE>64)?(USBD_AUDIO_CONFIG_PLAY_MAX_PACKET_SIZE + 3U)/4:16;
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
 max_tx_ep_num = CONFIG_AUDIO_EP_SYNC&0x7F;
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
#else /* USE_USB_AUDIO_PLAYBACK */
 rx_fifo_size = 16;/*64(mps)/4*/
#endif /* USE_USB_AUDIO_PLAYBACK*/
 
#if  USE_USB_AUDIO_RECORDING   
 if((USB_AUDIO_CONFIG_RECORD_EP_IN&0x7F)>max_tx_ep_num)
 {
  max_tx_ep_num = USB_AUDIO_CONFIG_RECORD_EP_IN&0x7F;  
 }
 tx_fifo_size[USB_AUDIO_CONFIG_RECORD_EP_IN&0x7F] = (USBD_AUDIO_CONFIG_RECORD_MAX_PACKET_SIZE + 3U)/4;
#endif /* USE_USB_AUDIO_RECORDING */

  tx_fifo_used_size = (USB_AUDIO_GetConfigDescriptor(0)+3)/4 ;
  tx_fifo_size[0] = tx_fifo_used_size;
 
  for(int i = 1; i<= max_tx_ep_num; i++)
 {
   if(tx_fifo_size[i]<16)
   {
     tx_fifo_size[i] = 16;
   }
   tx_fifo_used_size += tx_fifo_size[i];
 }
 
 rx_fifo_size += (5*1/*number of control endpoints*/+8
                    +1/* for status information*/+2*6/*number of OUT endpoints*/+1/*for Global NAK*/);
 
  if(tx_fifo_used_size + rx_fifo_size<=USB_FIFO_WORD_SIZE)
  {
#if  USE_USB_AUDIO_RECORDING   
 tx_fifo_size[USB_AUDIO_CONFIG_RECORD_EP_IN&0x7F] += USB_FIFO_WORD_SIZE - (tx_fifo_used_size + rx_fifo_size);
#else /* USE_USB_AUDIO_RECORDING */
#if USE_USB_AUDIO_PLAYBACK
  rx_fifo_size = USB_FIFO_WORD_SIZE - tx_fifo_used_size;
#endif /* USE_USB_AUDIO_PLAYBACK */
#endif /* USE_USB_AUDIO_RECORDING */
  }
  else
  {
     Error_Handler();
  }
  
  
 HAL_PCDEx_SetRxFiFo(&hpcd, rx_fifo_size);
 for(int i = 0; i<= max_tx_ep_num; i++)
 {
   HAL_PCD_SetTxFiFo(&hpcd, i, tx_fifo_size[i]);
 }
 return USBD_OK;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
//------------------------------------------------------------------------------
void USB_FIFO_Setup(uint8_t USBMode)
{
  if (USBMode == USB_SOUND_CARD_MODE)
    USBD_LL_Setup_Fifo();
  else
  {
    HAL_PCDEx_SetRxFiFo(&hpcd, 0x80);
    HAL_PCDEx_SetTxFiFo(&hpcd, 0, 0x40);
    HAL_PCDEx_SetTxFiFo(&hpcd, 1, 0x80);
  }
}



