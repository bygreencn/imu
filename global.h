#ifndef __GLOBAL_DEFS__
#define __GLOBAL_DEFS__

#define USE_STDPERIPH_DRIVER
#define STM32F10X_HD
#include "stm32f10x.h"
#include <stdio.h>

#include "pressure.h"

#define BAUD_RATE 9600
#define I2C_TIMEOUT 0x1000

#define LED_ON() GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LED_OFF() GPIO_ResetBits(GPIOB,GPIO_Pin_9)

#endif
