/**
  ******************************************************************************
  * @file    usb_audio_user.h
  * @author  MCD Application Team 
  * @brief   USB audio application configuration.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_AUDIO_USER_H
#define __USB_AUDIO_USER_H

#ifdef __cplusplus
 extern "C" {
#endif
/* includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "usb_audio_constants.h"
#include "audio_node.h"
#include "usb_audio_user_cfg.h"

/* Exported constants & exported MACRO --------------------------------------------------------*/
/* definition of the USB IRQ priority and the USB FIFO size in word */
#define USB_IRQ_PREPRIO 3U
#ifdef USE_USB_FS
#define USB_FIFO_WORD_SIZE  320U
#else  /*  USE_USB_FS */
#define USB_FIFO_WORD_SIZE  1024U
#endif  /*  USE_USB_FS */

   
#if USE_USB_AUDIO_PLAYBACK

/*playback computing the max and the min frequency */  
#if USB_AUDIO_CONFIG_PLAY_USE_FREQ_192_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MAX   USB_AUDIO_CONFIG_FREQ_192_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_96_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MAX   USB_AUDIO_CONFIG_FREQ_96_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_48_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MAX   USB_AUDIO_CONFIG_FREQ_48_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_44_1_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MAX   USB_AUDIO_CONFIG_FREQ_44_1_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_32_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MAX   USB_AUDIO_CONFIG_FREQ_32_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_16_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MAX   USB_AUDIO_CONFIG_FREQ_16_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_8_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MAX   USB_AUDIO_CONFIG_FREQ_8_K
#else
#error "Playback frequency is missed"
#endif 

#if USB_AUDIO_CONFIG_PLAY_USE_FREQ_8_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MIN   USB_AUDIO_CONFIG_FREQ_8_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_16_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MIN   USB_AUDIO_CONFIG_FREQ_16_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_32_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MIN   USB_AUDIO_CONFIG_FREQ_32_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_44_1_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MIN   USB_AUDIO_CONFIG_FREQ_44_1_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_48_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MIN   USB_AUDIO_CONFIG_FREQ_48_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_96_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MIN   USB_AUDIO_CONFIG_FREQ_96_K
#elif USB_AUDIO_CONFIG_PLAY_USE_FREQ_192_K
#define USB_AUDIO_CONFIG_PLAY_FREQ_MIN   USB_AUDIO_CONFIG_FREQ_192_K
#endif 
/* Macro to compute the count of supported frequency */
#define USB_AUDIO_CONFIG_PLAY_FREQ_COUNT              (USB_AUDIO_CONFIG_PLAY_USE_FREQ_192_K + USB_AUDIO_CONFIG_PLAY_USE_FREQ_176_4_K + USB_AUDIO_CONFIG_PLAY_USE_FREQ_96_K +\
                                                       USB_AUDIO_CONFIG_PLAY_USE_FREQ_88_2_K + USB_AUDIO_CONFIG_PLAY_USE_FREQ_48_K + USB_AUDIO_CONFIG_PLAY_USE_FREQ_44_1_K +\
                                                        USB_AUDIO_CONFIG_PLAY_USE_FREQ_32_K + USB_AUDIO_CONFIG_PLAY_USE_FREQ_16_K +\
                                                          USB_AUDIO_CONFIG_PLAY_USE_FREQ_8_K)
#define USB_AUDIO_CONFIG_PLAY_DEF_FREQ                USB_AUDIO_CONFIG_PLAY_FREQ_MAX

#if ((USB_AUDIO_CONFIG_PLAY_FREQ_COUNT)>1)
#define USE_AUDIO_USB_PLAY_MULTI_FREQUENCIES 1
#endif 

#endif /*USE_AUDIO_PLAYBACK*/

 
/* defining the max packet length*/
#if USE_USB_AUDIO_PLAYBACK
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
#define USBD_AUDIO_CONFIG_PLAY_MAX_PACKET_SIZE ((uint16_t)(AUDIO_USB_MAX_PACKET_SIZE((USB_AUDIO_CONFIG_PLAY_FREQ_MAX+ 1),\
      USB_AUDIO_CONFIG_PLAY_CHANNEL_COUNT,\
      USB_AUDIO_CONFIG_PLAY_RES_BYTE)))
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
#define USBD_AUDIO_CONFIG_PLAY_MAX_PACKET_SIZE ((uint16_t)(AUDIO_USB_MAX_PACKET_SIZE((USB_AUDIO_CONFIG_PLAY_FREQ_MAX),\
      USB_AUDIO_CONFIG_PLAY_CHANNEL_COUNT,\
      USB_AUDIO_CONFIG_PLAY_RES_BYTE)))
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
#endif /* USE_USB_AUDIO_PLAYBACK */



/* Exported types ------------------------------------------------------------*/
/* Exported function ---------------------------------------------------------*/
   uint16_t USB_AUDIO_GetConfigDescriptor(uint8_t **desc);
   void Error_Handler(void);
#ifdef __cplusplus
}
#endif

#endif /* __USB_AUDIO_USER_H */
 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
