/*
********************************************************************************
* COPYRIGHT(c) ЗАО «ЧИП и ДИП», 2019, 2020
* 
* Программное обеспечение предоставляется на условиях «как есть» (as is).
* При распространении указание автора обязательно.
********************************************************************************
*/



#ifndef __BOARD_H
#define __BOARD_H


#include "stm32f446xx.h"

//USB
#define   USB_FS_GPIO                      GPIOA
#define   USB_FS_DM_PIN                    11
#define   USB_FS_DP_PIN                    12
#define   USB_FS_PINS_AF                   10
//SAI1 - master
#define   SAI_MASTER                       SAI1_Block_B
#define   SAI_MASTER_MCLK_GPIO             GPIOC
#define   SAI_MASTER_MCK_PIN               0
#define   SAI_MASTER_SCK_FS_GPIO           GPIOB
#define   SAI_MASTER_SCK_PIN               12
#define   SAI_MASTER_FS_PIN                9
#define   SAI_MASTER_SD_GPIO               GPIOA
#define   SAI_MASTER_SD_PIN                9
#define   SAI_MASTER_MCLK_SCK_SD_FS_AF     6
#define   SAI_MASTER_DMA_STREAM            DMA2_Stream5
#define   SAI_MASTER_DMA_CHANNEL           0
#define   SAI_MASTER_DMA_IRQ               DMA2_Stream5_IRQn
//SAI2 - slave
#define   SAI_SLAVE                        SAI1_Block_A
#define   SAI_SLAVE_SD_GPIO                GPIOB
#define   SAI_SLAVE_SD_PIN                 2
#define   SAI_SLAVE_SD_AF                  6
#define   SAI_SLAVE_DMA_STREAM             DMA2_Stream1
#define   SAI_SLAVE_DMA_CHANNEL            0
//#define   SAI_SLAVE_DMA_IRQ                DMA2_Stream1_IRQn

//I2C
#define   I2C_GPIO                         GPIOB
#define   I2C_PORT                         I2C1
#define   I2C_SCL_PIN                      6 //pcb marking 4
#define   I2C_SCL_AF                       4
#define   I2C_SDA_PIN                      7 //pcb marking 5
#define   I2C_SDA_AF                       4

//GPIO
#define   MEMORY_ERASE_GPIO                GPIOD
#define   MEMORY_ERASE_PIN                 2 //pcb marking 1

#define   CONFIG_GPIO                      GPIOC
#define   CONFIG_1_PIN                     3  //pcb marking 6
#define   CONFIG_2_PIN                     2  //pcb marking 7
#define   CONFIG_3_PIN                     1  //pcb marking 8
#define   CONFIG_4_PIN                     15 //pcb marking 9
#define   CONFIG_5_PIN                     14 //pcb marking 10
#define   CONFIG_6_PIN                     13 //pcb marking 11

#define   CONFIG_MODE_GPIO                 GPIOB
#define   CONFIG_MODE_PIN                  8 //pcb marking 12

#define   FREQ_EVENT_GPIO                  GPIOB
#define   FREQ_EVENT_1_PIN                 0 //pcb marking 26
#define   FREQ_EVENT_2_PIN                 1 //pcb marking 25
#define   FREQ_EVENT_MASK                  ((1 << FREQ_EVENT_1_PIN) | (1 << FREQ_EVENT_2_PIN))
#define   FREQ_EVENT_44100                 0
#define   FREQ_EVENT_48000                 (1 << FREQ_EVENT_1_PIN)
#define   FREQ_EVENT_96000                 (1 << FREQ_EVENT_2_PIN)
#define   FREQ_EVENT_192000                FREQ_EVENT_MASK

#define   RES_EVENT_GPIO                   GPIOB
#define   RES_EVENT_PIN                    5 //pcb marking 3
#define   RES_EVENT_16BIT                  0
#define   RES_EVENT_24BIT                  (1 << RES_EVENT_PIN)

#define   EXT_SYNC_GPIO                    GPIOC
#define   EXT_SYNC_PIN                     9 //pcb marking EXT CLK
#define   EXT_SYNC_AF                      5

#define   LED_GPIO                         GPIOC
#define   LED_PIN                          8

#define   AUDIO_CONFIG_1_PIN               CONFIG_1_PIN
#define   AUDIO_CONFIG_2_PIN               CONFIG_2_PIN
#define   AUDIO_CONFIG_3_PIN               CONFIG_3_PIN
#define   TDM_MODE_PIN                     CONFIG_4_PIN
#define   SYNC_MODE_PIN_1                  CONFIG_5_PIN
#define   SYNC_MODE_PIN_2                  CONFIG_6_PIN

#define   AUDIO_CONFIG_1_MASK              (1 << AUDIO_CONFIG_1_PIN)
#define   AUDIO_CONFIG_2_MASK              (1 << AUDIO_CONFIG_2_PIN)
#define   AUDIO_CONFIG_3_MASK              (1 << AUDIO_CONFIG_3_PIN)
#define   AUDIO_CONFIG_MASK                (AUDIO_CONFIG_1_MASK | AUDIO_CONFIG_2_MASK | AUDIO_CONFIG_3_MASK)

#define   SYNC_MODE_1_MASK                 (1 << SYNC_MODE_PIN_1)
#define   SYNC_MODE_2_MASK                 (1 << SYNC_MODE_PIN_2)
#define   SYNC_MODE_MASK                   (SYNC_MODE_1_MASK | SYNC_MODE_2_MASK)

#define   USER_GPIO_COUNT                  8
#define   DSP_INTERFACE_COUNT              3

#define   I2C_INTERFACE                    0
#define   SPI_INTERFACE                    1

#define   FIRMWARE_VERSION_BYTE_1          0x00
#define   FIRMWARE_VERSION_BYTE_2          0x01
#define   FIRMWARE_VERSION_BYTE_3          0x00
#define   FIRMWARE_VERSION_BYTE_4          0x00

#define   HARDWARE_VERSION                 0x02

#define   SUPER_PRIMEv2_ID                 3

#define   M_BITS_UINTS                     0
#define   K_BITS_UINTS                     1

//#define   MEMORY_SIZE                      512
//#define   MEMORY_SIZE_UINTS                K_BITS_UINTS

#define   EEPROM_ADDRESS                   0x50
#define   EEPROM_PAGE_SIZE                 128
#define   MEMORY_ADDRESS_SIZE_USED         3
#define   MEMORY_IC_ADDRESS_BYTES          2

#define   UNDEFINED_VALUE                  0xFF

#define   USB_VID_ST                       0x0483
#define   USB_PID_CHIPDIP                  0xA210
#define   USB_MANUFACTURE_MAX_LENGTH       20
#define   USB_DEVICE_NAME_MAX_LENGTH       40

#define   USB_MANUFAC_DEFAULT              "ChipDip."
#define   USB_DEVICE_NAME_DEFAULT          '\0'
//#define   USB_MANUFAC_SIZE_DEFAULT         8


#define   DELAY_TIMER_DSP_PSC              39
#define   DELAY_TIMER_DSP_ARR              29


typedef struct
{
  uint32_t Address;
  uint16_t Size;
  uint8_t  Data[EEPROM_PAGE_SIZE];
  
} TransferType;


typedef struct
{
  uint8_t ID;
  uint8_t BusAddress;
  uint8_t ChipSelect;
  uint8_t InternalAdrBytes;

} ICInfoType;


enum USBModes
{
  USB_HID_MODE,
  USB_SOUND_CARD_MODE,
};



void USB_I2S_Init(void);

uint32_t JoinBytesIntoValue(uint8_t *Data, uint8_t Size);


#endif //__BOARD_H


