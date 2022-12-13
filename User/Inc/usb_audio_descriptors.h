/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2019, 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/






#ifndef __USB_AUDIO_DESCRIPTORS_H
#define __USB_AUDIO_DESCRIPTORS_H



#define   CONFIG_2_0_STEREO_DESCRIPTOR_SIZE      (128 + 58)
#define   CONFIG_2_0_STEREO_AC_TOTAL_SIZE        40

#define   CONFIG_32_BIT_STEREO_DESCRIPTOR_SIZE   (119)

#define   CONFIG_3_1_DESCRIPTOR_SIZE             (127 + 55)
#define   CONFIG_3_1_AC_TOTAL_SIZE               42

#define   CONFIG_4_0_QUADRO_DESCRIPTOR_SIZE      (127 + 55)
#define   CONFIG_4_0_QUADRO_AC_TOTAL_SIZE        42

#define   CONFIG_5_1_SURROUND_DESCRIPTOR_SIZE    (127 + 54)
#define   CONFIG_5_1_SURROUND_AC_TOTAL_SIZE      44

#define   CONFIG_7_1_SURROUND_DESCRIPTOR_SIZE    (127 + 1)
#define   CONFIG_7_1_SURROUND_AC_TOTAL_SIZE      46

#define   CONFIG_TERMINAL_INPUT_ID               0x12
#define   CONFIG_UNIT_FEATURE_ID                 0x16
#define   CONFIG_TERMINAL_OUTPUT_ID              0x14

#define   CONFIG_AUDIO_STREAMING_INTERFACE       1
#define   CONFIG_AUDIO_EP_OUT                    0x01
#define   CONFIG_AUDIO_EP_SYNC                   0x81
#define   CONFIG_AUDIO_FEEDBACK_REFRESH          0x07





uint8_t* GetProductString(void);



#endif // __USB_AUDIO_DESCRIPTORS_H


