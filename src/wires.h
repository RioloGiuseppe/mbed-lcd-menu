#ifndef __WIRES__
#define __WIRES__

#include "mbed.h"

#define LCD_CE PB_15
#define LCD_DC PB_4
#define LCD_DIN PB_14
#define LCD_CLK PB_5
#define LCD_LGT PB_13

#define LED_1 PC_5
#define LED_2 PB_12
#define LED_3 PC_6
#define LED_4 PA_11
#define LED_5 PA_12

#define SW_CENTRAL PA_9
#define SW_UP PC_7
#define SW_DOWN PB_10

enum DeviceStates
{
    Pairing,
    Programming,
    Working
};

typedef struct
{
    uint8_t addr[5];
    uint8_t nt_name[26];
} nt_message;

#endif