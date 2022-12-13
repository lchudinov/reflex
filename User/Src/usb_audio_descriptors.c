/*
********************************************************************************
* This file is a part of firmware for Reflex module
* (USB_I2S_PRIME_SUPER modification)
*
* Copyright (c) 2019 - 2021 ChipDip. <https://www.chipdip.ru>
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License. 
********************************************************************************
*/

#include "usbd_def.h"
#include "usbd_audio.h"
#include "usb_audio_descriptors.h"
#include "audio_configuration.h"

////////////////////////////////////////////////////////////////////////////////
//--------------------------------Mute Control----------------------------------
////////////////////////////////////////////////////////////////////////////////

//------------------------------Stereo 2.0 16, 24 bit---------------------------
const uint8_t USBD_AUDIO_Config_2_0_Stereo[CONFIG_2_0_STEREO_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_2_0_STEREO_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_2_0_STEREO_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_2_0_STEREO_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_2_0_STEREO_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_2_0_STEREO_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0A,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  
  //-------------------------16 bit---------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_16_BIT,                     /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_2_0_STEREO_16_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_2_0_STEREO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_16,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_16,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_2_0_STEREO_16_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_176_4_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_192_K),
  //(0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_2_0_STEREO_16_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_2_0_STEREO_16_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */ 
    
  //-------------------------24 bit---------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_24_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_2_0_STEREO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_24,              /* bSubFrameSize :  3 Bytes per frame (24bits) */
  CONFIG_RES_BIT_24,               /* bBitResolution (24-bits per sample) */ 
  CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  //(0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_2_0_STEREO_24_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_2_0_STEREO_24_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
} ;

//------------------------------Stereo 2.0 32 bit---------------------------
const uint8_t USBD_AUDIO_Config_2_0_Stereo_32_bit[CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_2_0_STEREO_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_2_0_STEREO_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_2_0_STEREO_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0A,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //-------------------------32 bit---------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x01,                                         /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_2_0_STEREO_32_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_2_0_STEREO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_32,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_32,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_2_0_STEREO_32_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  //(0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_2_0_STEREO_32_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_2_0_STEREO_32_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  0x00,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */ 
} ;

//------------------------------Stereo 3.1--------------------------------------
const uint8_t USBD_AUDIO_Config_3_1[CONFIG_3_1_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_3_1_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_3_1_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_3_1_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_3_1_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_3_1_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_3_1_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_3_1_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0C,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */  
  0,                                            /* bmaControls(3) */ 
  0,                                            /* bmaControls(4) */ 
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //---------------------------16 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_16_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_3_1_16_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_3_1_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_16,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_16,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_3_1_16_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_3_1_16_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_3_1_16_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
  
  //---------------------------24 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_24_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_3_1_24_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_3_1_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_24,              /* bSubFrameSize :  3 Bytes per frame (24bits) */
  CONFIG_RES_BIT_24,               /* bBitResolution (24-bits per sample) */ 
  CONFIG_3_1_24_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_3_1_24_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_3_1_24_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */ 
} ;

//------------------------------Quadro 4.0--------------------------------------
const uint8_t USBD_AUDIO_Config_4_0_Quadro[CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_4_0_QUADRO_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_4_0_QUADRO_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_4_0_QUADRO_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_4_0_QUADRO_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_4_0_QUADRO_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0C,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */  
  0,                                            /* bmaControls(3) */
  0,                                            /* bmaControls(4) */  
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //---------------------------16 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_16_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_4_0_QUADRO_16_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_4_0_QUADRO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_16,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_16,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_4_0_QUADRO_16_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_4_0_QUADRO_16_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_4_0_QUADRO_16_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
  
  //---------------------------24 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_24_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_4_0_QUADRO_24_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_4_0_QUADRO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_24,              /* bSubFrameSize :  3 Bytes per frame (24bits) */
  CONFIG_RES_BIT_24,               /* bBitResolution (24-bits per sample) */ 
  CONFIG_4_0_QUADRO_24_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_4_0_QUADRO_24_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_4_0_QUADRO_24_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */ 
} ;

//------------------------------Surround 7.1--------------------------------------
const uint8_t USBD_AUDIO_Config_7_1_Surround[CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_7_1_SURROUND_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_7_1_SURROUND_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_7_1_SURROUND_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_7_1_SURROUND_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_7_1_SURROUND_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x10,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */  
  0,                                            /* bmaControls(3) */
  0,                                            /* bmaControls(4) */    
  0,                                            /* bmaControls(5) */
  0,                                            /* bmaControls(6) */    
  0,                                            /* bmaControls(7) */
  0,                                            /* bmaControls(8) */    
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //---------------------------16 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_16_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_7_1_SURROUND_16_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_7_1_SURROUND_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_16,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_16,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_7_1_SURROUND_16_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_7_1_SURROUND_16_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_7_1_SURROUND_16_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
};

//------------------------------Stereo 2.0 SPDIF 24 bit---------------------------
const uint8_t USBD_AUDIO_Config_2_0_SPDIF[CONFIG_2_0_SPDIF_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_2_0_SPDIF_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_2_0_SPDIF_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_2_0_SPDIF_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_2_0_SPDIF_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_2_0_STEREO_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0A,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //-------------------------24 bit---------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_24_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_2_0_STEREO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_24,              /* bSubFrameSize :  3 Bytes per frame (24bits) */
  CONFIG_RES_BIT_24,               /* bBitResolution (24-bits per sample) */ 
  CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  //(0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_2_0_STEREO_24_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_2_0_STEREO_24_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
};
////////////////////////////////////////////////////////////////////////////////
//---------------------------Mute and Volume Control----------------------------
////////////////////////////////////////////////////////////////////////////////

//------------------------------Stereo 2.0 16, 24 bit---------------------------
const uint8_t USBD_AUDIO_Config_2_0_Stereo_HWV[CONFIG_2_0_STEREO_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_2_0_STEREO_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_2_0_STEREO_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_2_0_STEREO_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_2_0_STEREO_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_2_0_STEREO_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0A,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE | USBD_AUDIO_CONTROL_FEATURE_UNIT_VOLUME,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  
  //-------------------------16 bit---------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_16_BIT,                     /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_2_0_STEREO_16_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_2_0_STEREO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_16,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_16,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_2_0_STEREO_16_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_176_4_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_192_K),
  //(0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_2_0_STEREO_16_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_2_0_STEREO_16_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */ 
    
  //-------------------------24 bit---------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_24_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_2_0_STEREO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_24,              /* bSubFrameSize :  3 Bytes per frame (24bits) */
  CONFIG_RES_BIT_24,               /* bBitResolution (24-bits per sample) */ 
  CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  //(0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_2_0_STEREO_24_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_2_0_STEREO_24_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
} ;

//------------------------------Stereo 2.0 32 bit---------------------------
const uint8_t USBD_AUDIO_Config_2_0_Stereo_32_bit_HWV[CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_2_0_STEREO_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_2_0_STEREO_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_2_0_STEREO_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0A,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE | USBD_AUDIO_CONTROL_FEATURE_UNIT_VOLUME,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //-------------------------32 bit---------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x01,                                         /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_2_0_STEREO_32_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_2_0_STEREO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_32,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_32,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_2_0_STEREO_32_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  //(0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_2_0_STEREO_32_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_2_0_STEREO_32_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  0x00,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */ 
} ;

//------------------------------Stereo 3.1--------------------------------------
const uint8_t USBD_AUDIO_Config_3_1_HWV[CONFIG_3_1_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_3_1_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_3_1_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_3_1_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_3_1_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_3_1_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_3_1_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_3_1_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0C,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE | USBD_AUDIO_CONTROL_FEATURE_UNIT_VOLUME,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */  
  0,                                            /* bmaControls(3) */ 
  0,                                            /* bmaControls(4) */ 
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //---------------------------16 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_16_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_3_1_16_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_3_1_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_16,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_16,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_3_1_16_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_3_1_16_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_3_1_16_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
  
  //---------------------------24 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_24_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_3_1_24_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_3_1_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_24,              /* bSubFrameSize :  3 Bytes per frame (24bits) */
  CONFIG_RES_BIT_24,               /* bBitResolution (24-bits per sample) */ 
  CONFIG_3_1_24_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_3_1_24_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_3_1_24_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */ 
} ;

//------------------------------Quadro 4.0--------------------------------------
const uint8_t USBD_AUDIO_Config_4_0_Quadro_HWV[CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_4_0_QUADRO_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_4_0_QUADRO_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_4_0_QUADRO_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_4_0_QUADRO_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_4_0_QUADRO_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0C,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE | USBD_AUDIO_CONTROL_FEATURE_UNIT_VOLUME,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */  
  0,                                            /* bmaControls(3) */
  0,                                            /* bmaControls(4) */  
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //---------------------------16 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_16_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_4_0_QUADRO_16_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_4_0_QUADRO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_16,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_16,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_4_0_QUADRO_16_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_4_0_QUADRO_16_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_4_0_QUADRO_16_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
  
  //---------------------------24 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_24_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_4_0_QUADRO_24_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_4_0_QUADRO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_24,              /* bSubFrameSize :  3 Bytes per frame (24bits) */
  CONFIG_RES_BIT_24,               /* bBitResolution (24-bits per sample) */ 
  CONFIG_4_0_QUADRO_24_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_4_0_QUADRO_24_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_4_0_QUADRO_24_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */ 
} ;

//------------------------------Surround 7.1--------------------------------------
const uint8_t USBD_AUDIO_Config_7_1_Surround_HWV[CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_7_1_SURROUND_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_7_1_SURROUND_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_7_1_SURROUND_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_7_1_SURROUND_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_7_1_SURROUND_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x10,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE | USBD_AUDIO_CONTROL_FEATURE_UNIT_VOLUME,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */  
  0,                                            /* bmaControls(3) */
  0,                                            /* bmaControls(4) */    
  0,                                            /* bmaControls(5) */
  0,                                            /* bmaControls(6) */    
  0,                                            /* bmaControls(7) */
  0,                                            /* bmaControls(8) */    
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //---------------------------16 bit-------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_16_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_7_1_SURROUND_16_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_7_1_SURROUND_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_16,              /* bSubFrameSize :  2 Bytes per frame (16bits) */
  CONFIG_RES_BIT_16,               /* bBitResolution (16-bits per sample) */ 
  CONFIG_7_1_SURROUND_16_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  /* (0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_7_1_SURROUND_16_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_7_1_SURROUND_16_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
};

//------------------------------Stereo 2.0 SPDIF 24 bit---------------------------
const uint8_t USBD_AUDIO_Config_2_0_SPDIF_HWV[CONFIG_2_0_SPDIF_DESCRIPTOR_SIZE] =
{
  /* Configuration 1 */
  0x09,                                         /* bLength */
  USB_DESC_TYPE_CONFIGURATION,                  /* bDescriptorType */
  LOBYTE(CONFIG_2_0_SPDIF_DESCRIPTOR_SIZE),    /* wTotalLength  */
  HIBYTE(CONFIG_2_0_SPDIF_DESCRIPTOR_SIZE),      
  0x02,                                         /* bNumInterfaces */
  0x01,                                         /* bConfigurationValue */
  0x00,                                         /* iConfiguration */
  0x80,                                         /* bmAttributes  BUS Powred*/
  0x32,                                         /* bMaxPower = 100 mA*/
  /* 09 byte*/
  
  /* Standard AC Interface Descriptor: Audio control interface*/
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  0x00,                                         /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOCONTROL,                  /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /* Class-Specific AC Interface Header Descriptor */
  
  0x09,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_HEADER,                         /* bDescriptorSubtype */
  LOBYTE(USBD_AUDIO_ADC_BCD),                          /* 1.00 */                     /* bcdADC */
  HIBYTE(USBD_AUDIO_ADC_BCD),
  LOBYTE(CONFIG_2_0_SPDIF_AC_TOTAL_SIZE),      /* wTotalLength*/
  HIBYTE(CONFIG_2_0_SPDIF_AC_TOTAL_SIZE),
  0x01,                                         /*  streaming interface count */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* Audio streaming interface for  play  */
  /* 9 byte*/

  /* USB OUT Terminal for play session */
  /* Input Terminal Descriptor */
  USBD_AUDIO_INPUT_TERMINAL_DESC_SIZE,               /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_INPUT_TERMINAL,                 /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),         /* wTerminalType USBD_AUDIO_TERMINAL_IO_USB_STREAMING   0x0101 */
  HIBYTE(USBD_AUDIO_TERMINAL_IO_USB_STREAMING),
  0x00,                                         /* bAssocTerminal */
  CONFIG_2_0_STEREO_CHANNEL_COUNT,              /* bNrChannels */
  LOBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),   /* wChannelConfig*/
  HIBYTE(CONFIG_2_0_STEREO_CHANNEL_MAP),
  0x00,                                         /* iChannelNames */
  0x00,                                         /* iTerminal */
  /* 12 byte*/
  
  /* USB Play control feature */
  /* Feature Unit Descriptor*/
  0x0A,                                           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_FEATURE_UNIT,                   /* bDescriptorSubtype */
  CONFIG_UNIT_FEATURE_ID,        /* bUnitID */
  CONFIG_TERMINAL_INPUT_ID,      /* bSourceID: IT 02 */
  0x01,                                         /* bControlSize */
  /* @TODO add volume  controle on L/R channel */
  USBD_AUDIO_CONTROL_FEATURE_UNIT_MUTE | USBD_AUDIO_CONTROL_FEATURE_UNIT_VOLUME,      /* bmaControls(0) */
  0,                                            /* bmaControls(1) */
  0,                                            /* bmaControls(2) */
  0x00,                                         /* iTerminal */
  /* 10 byte*/
  
  /*USB Play : Speaker Terminal */
  /* Output Terminal Descriptor */
  USBD_AUDIO_OUTPUT_TERMINAL_DESC_SIZE,                                         /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_AC_SUBTYPE_OUTPUT_TERMINAL,                /* bDescriptorSubtype */
  CONFIG_TERMINAL_OUTPUT_ID,     /* bTerminalID */
  LOBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),        /* wTerminalType  0x0301*/
  HIBYTE(USBD_AUDIO_TERMINAL_O_SPEAKER),
  0x00,                                         /* bAssocTerminal */
  CONFIG_UNIT_FEATURE_ID,        /* bSourceID FU 06*/
  0x00,                                         /* iTerminal */
  /* 09 byte*/

  /* USB play Standard AS Interface Descriptor - Audio Streaming Zero Bandwith */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  0x00,                                         /* bAlternateSetting */
  0x00,                                         /* bNumEndpoints */
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  //-------------------------24 bit---------------------------------------------
  
  /* USB play Standard AS Interface Descriptors - Audio streaming operational */
  /* Standard AS Interface Descriptor */
  USBD_AUDIO_STANDARD_INTERFACE_DESC_SIZE,                    /* bLength */
  USB_DESC_TYPE_INTERFACE,                      /* bDescriptorType */
  CONFIG_AUDIO_STREAMING_INTERFACE,          /* bInterfaceNumber */
  ALTERNATE_SETTING_24_BIT,                  /* bAlternateSetting */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK 
  0x02,                                         /* bNumEndpoints */
#else
  0x01,                                         /* bNumEndpoints */
#endif 
  USBD_AUDIO_CLASS_CODE,                       /* bInterfaceClass */
  USBD_AUDIO_INTERFACE_SUBCLASS_AUDIOSTREAMING,                /* bInterfaceSubClass */
  USBD_AUDIO_INTERFACE_PROTOCOL_UNDEFINED,                     /* bInterfaceProtocol */
  0x00,                                         /* iInterface */
  /* 09 byte*/
  
  /*Class-Specific AS Interface Descriptor */
  USBD_AUDIO_AS_CS_INTERFACE_DESC_SIZE,          /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_GENERAL,                      /* bDescriptorSubtype */
  CONFIG_TERMINAL_INPUT_ID,      /* bTerminalLink */
  0x01,                                         /* bDelay */
  LOBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),                     /* wFormatTag USBD_AUDIO_FORMAT_TYPE_PCM  0x0001*/
  HIBYTE(USBD_AUDIO_FORMAT_TYPE_PCM),
  /* 07 byte*/

    /*  Audio Type I Format descriptor */
  USBD_USBD_AUDIO_FORMAT_TYPE_I_DESC_SIZE(CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT),/* bLength */
  USBD_AUDIO_DESC_TYPE_CS_INTERFACE,              /* bDescriptorType */
  USBD_AUDIO_CS_SUBTYPE_AS_FORMAT_TYPE,                  /* bDescriptorSubtype */
  USBD_AUDIO_FORMAT_TYPE_I,                          /* bFormatType */ 
  CONFIG_2_0_STEREO_CHANNEL_COUNT,         /* bNrChannels */
  CONFIG_RES_BYTE_24,              /* bSubFrameSize :  3 Bytes per frame (24bits) */
  CONFIG_RES_BIT_24,               /* bBitResolution (24-bits per sample) */ 
  CONFIG_2_0_STEREO_24_BIT_FREQ_COUNT,      /* bSamFreqType only one frequency supported */ 
 /* Audio sampling frequency coded on 3 bytes */
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_44_1_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_48_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_88_2_K),
  AUDIO_SAMPLE_FREQ(USB_AUDIO_CONFIG_FREQ_96_K),
  //(0x08 + USB_AUDIO_CONFIG_PLAY_FREQ_COUNT * 3) byte*/
  
  /* USB Play data ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_OUT,                /* bEndpointAddress 1 out endpoint*/
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  USBD_EP_TYPE_ISOC|USBD_EP_ATTR_ISOC_ASYNC,    /* bmAttributes */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  LOBYTE(CONFIG_2_0_STEREO_24_BIT_MAX_PACKET),/* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(CONFIG_2_0_STEREO_24_BIT_MAX_PACKET),
  0x01,                                         /* bInterval */
  0x00,                                         /* bRefresh */
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK          /* when feedback is used */
  CONFIG_AUDIO_EP_SYNC,                /* bSynchAddress */
#else /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  0x00,                                         /* bSynchAddress */
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK*/
  /* 09 byte*/
  
  /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_SPECIFIC_DATA_ENDPOINT_DESC_SIZE,           /* bLength */
  USBD_AUDIO_DESC_TYPE_CS_ENDPOINT,               /* bDescriptorType */
  USBD_AUDIO_SPECIFIC_EP_DESC_SUBTYPE_GENERAL,                       /* bDescriptor */
  USBD_AUDIO_AS_CONTROL_SAMPLING_FREQUENCY,          /* bmAttributes */
  0x00,                                         /* bLockDelayUnits */
  0x00,                                         /* wLockDelay */
  0x00,
  /* 07 byte*/
  
#if USE_AUDIO_PLAYBACK_USB_FEEDBACK
  /*next descriptor specific for synch ep */
  /* USB Play feedback ep  */
  /* Standard AS Isochronous Audio Data Endpoint Descriptor*/
  USBD_AUDIO_STANDARD_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_DESC_TYPE_ENDPOINT,                       /* bDescriptorType */
  CONFIG_AUDIO_EP_SYNC,                /* bEndpointAddress 1 out endpoint*/
  USBD_EP_TYPE_ISOC,                            /* bmAttributes */
  LOBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),        /* wMaxPacketSize in Bytes (Freq(Samples)*2(Stereo)*2(HalfWord)) */
  HIBYTE(AUDIO_FEEDBACK_EP_PACKET_SIZE),
  0x01,                                         /* bInterval */
  CONFIG_AUDIO_FEEDBACK_REFRESH,       /* bRefresh */
  0,                                            /* bSynchAddress */
  /* 09 byte*/
#endif /* USE_AUDIO_PLAYBACK_USB_FEEDBACK */
};


const uint8_t* PRODUCT_STRINGS[] = {"REFLEX Stereo 2.0 32 bit",
                                   "REFLEX Stereo 2.0",
                                   "REFLEX Stereo 3.1",
                                   "REFLEX Quadro 4.0",
                                   "REFLEX Surround 7.1",
                                   "REFLEX Stereo 2.0 32 bit TDM",
                                   "REFLEX Stereo 2.0 TDM",
                                   "REFLEX Stereo 3.1 TDM",
                                   "REFLEX Quadro 4.0 TDM",
                                   "REFLEX Surround 7.1 TDM",
                                   "REFLEX Stereo 2.0 SPDIF",};

const uint16_t  DESCRIPTOR_SIZE[] = {CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE,
                                     CONFIG_2_0_STEREO_DESCRIPTOR_SIZE,
                                     CONFIG_3_1_DESCRIPTOR_SIZE,
                                     CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE,
                                     CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE,
                                     CONFIG_2_0_SPDIF_DESCRIPTOR_SIZE,};

//------------------------------------------------------------------------------
uint16_t USB_AUDIO_GetConfigDescriptor(uint8_t **desc)
{ 
  uint8_t AudioConfig = GetAudioConfiguration();
  uint8_t VolumeCtrl = GetVolumeFeature();
  
  if ((AudioConfig >= AUDIO_CONFIG_TDM_START_INDEX)
   && (AudioConfig != AUDIO_CONFIG_2_0_SPDIF))
    AudioConfig -= AUDIO_CONFIG_TDM_START_INDEX;
  
  if(desc)
  { 
    if (VolumeCtrl == 0)
    {
      *desc = (uint8_t *)USBD_AUDIO_Config_2_0_SPDIF;
      
      switch(AudioConfig)
      {
        case AUDIO_CONFIG_2_0_STEREO_32_BIT:
          *desc = (uint8_t *)USBD_AUDIO_Config_2_0_Stereo_32_bit;
        break;
        
        case AUDIO_CONFIG_3_1:
          *desc = (uint8_t *)USBD_AUDIO_Config_3_1;
        break;
        
        case AUDIO_CONFIG_4_0_QUADRO:
          *desc = (uint8_t *)USBD_AUDIO_Config_4_0_Quadro;
        break;
        
        case AUDIO_CONFIG_7_1:
          *desc = (uint8_t *)USBD_AUDIO_Config_7_1_Surround;
        break;
        
        case AUDIO_CONFIG_2_0_SPDIF:
          *desc = (uint8_t *)USBD_AUDIO_Config_2_0_SPDIF;
        break;   
        
        case AUDIO_CONFIG_2_0_STEREO:
        default:
          *desc = (uint8_t *)USBD_AUDIO_Config_2_0_Stereo;
        break;     
      }
    }
    else
    {      
      switch(AudioConfig)
      {
        case AUDIO_CONFIG_2_0_STEREO_32_BIT:
          *desc = (uint8_t *)USBD_AUDIO_Config_2_0_Stereo_32_bit_HWV;
        break;
        
        case AUDIO_CONFIG_3_1:
          *desc = (uint8_t *)USBD_AUDIO_Config_3_1_HWV;
        break;
        
        case AUDIO_CONFIG_4_0_QUADRO:
          *desc = (uint8_t *)USBD_AUDIO_Config_4_0_Quadro_HWV;
        break;
        
        case AUDIO_CONFIG_7_1:
          *desc = (uint8_t *)USBD_AUDIO_Config_7_1_Surround_HWV;
        break;
        
        case AUDIO_CONFIG_2_0_SPDIF:
          *desc = (uint8_t *)USBD_AUDIO_Config_2_0_SPDIF_HWV;
        break;

        case AUDIO_CONFIG_2_0_STEREO:
        default:
          *desc = (uint8_t *)USBD_AUDIO_Config_2_0_Stereo_HWV;
        break;
      }
    }
  }
  
  if (AudioConfig != AUDIO_CONFIG_2_0_SPDIF)  
    return (DESCRIPTOR_SIZE[AudioConfig]);
  else
    return (DESCRIPTOR_SIZE[AUDIO_CONFIG_TDM_START_INDEX]);
}
//------------------------------------------------------------------------------
uint8_t* GetProductString(void)
{
  return (uint8_t*)PRODUCT_STRINGS[GetAudioConfiguration()];
}
//------------------------------------------------------------------------------


